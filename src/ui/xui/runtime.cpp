/**
 * @file        ui/xui/runtime.cpp
 * @brief       Live XUI elements: skin visuals, anchoring, named-frame timelines, focus
 * (RG-GDK-041)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/ui/xui/runtime.h>

#include <algorithm>
#include <cmath>
#include <limits>

#include <rex/ui/xui/system_update.h>

namespace rex::ui::xui {
namespace {

// XuiElement's defaults for properties a scene leaves out.
constexpr float kDefaultWidth = 60.0f;
constexpr float kDefaultHeight = 30.0f;

// Where relative paths are looked for after the scene's own package: skin
// visuals name images and sounds kept in XAM's skin and shared packages.
constexpr std::string_view kFallbackPackages[] = {
    "xam/skin", "huduiskin/skin", "xam/xam", "xam/shrdres", "hud/hud", "gamerprofile/gp"};

float Lerp(float a, float b, float t) {
  return a + (b - a) * t;
}

uint32_t LerpColor(uint32_t a, uint32_t b, float t) {
  uint32_t out = 0;
  for (int shift = 0; shift < 32; shift += 8) {
    const float ca = float((a >> shift) & 0xFF);
    const float cb = float((b >> shift) & 0xFF);
    const uint32_t c = uint32_t(std::lround(std::clamp(Lerp(ca, cb, t), 0.0f, 255.0f)));
    out |= c << shift;
  }
  return out;
}

Value Interpolate(const Value& a, const Value& b, float t) {
  if (const float* fa = a.get<float>()) {
    if (const float* fb = b.get<float>()) {
      return Value{Lerp(*fa, *fb, t)};
    }
  }
  if (const Vec3* va = a.get<Vec3>()) {
    if (const Vec3* vb = b.get<Vec3>()) {
      return Value{Vec3{Lerp(va->x, vb->x, t), Lerp(va->y, vb->y, t), Lerp(va->z, vb->z, t)}};
    }
  }
  if (const Color* ca = a.get<Color>()) {
    if (const Color* cb = b.get<Color>()) {
      return Value{Color{LerpColor(ca->argb, cb->argb, t)}};
    }
  }
  if (const Quat* qa = a.get<Quat>()) {
    if (const Quat* qb = b.get<Quat>()) {
      // Normalized lerp along the shorter arc.
      const float dot = qa->x * qb->x + qa->y * qb->y + qa->z * qb->z + qa->w * qb->w;
      const float sign = dot < 0.0f ? -1.0f : 1.0f;
      Quat q{Lerp(qa->x, sign * qb->x, t), Lerp(qa->y, sign * qb->y, t),
             Lerp(qa->z, sign * qb->z, t), Lerp(qa->w, sign * qb->w, t)};
      const float length = std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
      if (length > 0.0f) {
        q = Quat{q.x / length, q.y / length, q.z / length, q.w / length};
      }
      return Value{q};
    }
  }
  // Bools, integers and strings hold until the next keyframe.
  return a;
}

// A property's value at `frame`: the keyframe at or before it, interpolated
// toward the next by the earlier keyframe's mode.
const Value* Evaluate(const Timeline& timeline, size_t prop, double frame, Value& scratch) {
  const std::vector<Keyframe>& keys = timeline.keyframes;
  if (keys.empty()) {
    return nullptr;
  }
  size_t at = 0;
  while (at + 1 < keys.size() && keys[at + 1].frame <= frame) {
    ++at;
  }
  const Keyframe& key = keys[at];
  if (frame <= key.frame || at + 1 == keys.size() || key.interpolation == Interpolation::kNone) {
    return &key.values[prop];
  }
  const Keyframe& next = keys[at + 1];
  float t = float((frame - key.frame) / double(next.frame - key.frame));
  if (key.interpolation == Interpolation::kEase) {
    t = EaseProgress(t, key.ease_in, key.ease_out);
  }
  scratch = Interpolate(key.values[prop], next.values[prop], t);
  return &scratch;
}

}  // namespace

std::span<const uint8_t> ResolveFile(const SystemUpdate& update, std::string_view path,
                                     std::string_view base_package) {
  struct Protocol {
    std::string_view prefix;
    std::string_view package;
  };
  constexpr Protocol kProtocols[] = {
      {"sharedres://", "xam/shrdres"}, {"xam://", "xam/xam"}, {"skin://", "xam/skin"}};
  for (const Protocol& protocol : kProtocols) {
    if (path.starts_with(protocol.prefix)) {
      const Package* package = update.Find(protocol.package);
      return package ? package->Find(path.substr(protocol.prefix.size()))
                     : std::span<const uint8_t>();
    }
  }
  if (const Package* base = update.Find(base_package)) {
    if (auto bytes = base->Find(path); !bytes.empty()) {
      return bytes;
    }
  }
  for (std::string_view fallback : kFallbackPackages) {
    if (const Package* package = update.Find(fallback)) {
      if (auto bytes = package->Find(path); !bytes.empty()) {
        return bytes;
      }
    }
  }
  return {};
}

float EaseProgress(float t, int8_t ease_in, int8_t ease_out) {
  // A cubic whose inner control values follow the ease settings: 0/0 is
  // linear, a negative ease-in starts fast, a positive ease-out ends slow.
  const float p1 = (1.0f - float(ease_in) / 100.0f) / 3.0f;
  const float p2 = 1.0f - (1.0f - float(ease_out) / 100.0f) / 3.0f;
  const float u = 1.0f - t;
  return 3.0f * u * u * t * p1 + 3.0f * u * t * t * p2 + t * t * t;
}

Element::Element(const Node& node, Element* parent, const SceneContext* context)
    : parent_(parent), context_(context), cls_(node.cls), class_name_(node.class_name) {
  if (node.props) {
    props_ = *node.props;
  }
}

Element::~Element() = default;

std::unique_ptr<Element> Element::Create(const Node& node, const SceneContext& context) {
  std::unique_ptr<Element> element(new Element(node, nullptr, &context));
  element->Build(node);
  element->design_parent_width_ = element->GetFloat("Width", kDefaultWidth);
  element->design_parent_height_ = element->GetFloat("Height", kDefaultHeight);
  return element;
}

void Element::Build(const Node& node) {
  const float own_width = GetFloat("Width", kDefaultWidth);
  const float own_height = GetFloat("Height", kDefaultHeight);
  // Controls take their visual's elements and timelines from the skin: the
  // named Visual, or the one named after the class.
  if (IsA("XuiControl") && context_->skin) {
    std::string_view visual_name = GetString("Visual");
    if (visual_name.empty()) {
      visual_name = class_name_;
    }
    for (const Node& visual : context_->skin->root.children) {
      if (visual.class_name == "XuiVisual" && visual.id() == visual_name) {
        ApplyVisual(visual);
        break;
      }
    }
  }
  for (const Node& child_node : node.children) {
    std::unique_ptr<Element> child(new Element(child_node, this, context_));
    child->design_parent_width_ = own_width;
    child->design_parent_height_ = own_height;
    child->Build(child_node);
    children_.push_back(std::move(child));
  }
  AddTimelines(node);
  ApplyFrame(0.0);
}

void Element::ApplyVisual(const Node& visual) {
  const Value* w = visual.Find("Width");
  const Value* h = visual.Find("Height");
  const float visual_width = w && w->get<float>() ? *w->get<float>() : kDefaultWidth;
  const float visual_height = h && h->get<float>() ? *h->get<float>() : kDefaultHeight;
  for (const Node& child_node : visual.children) {
    std::unique_ptr<Element> child(new Element(child_node, this, context_));
    child->design_parent_width_ = visual_width;
    child->design_parent_height_ = visual_height;
    child->Build(child_node);
    children_.push_back(std::move(child));
  }
  AddTimelines(visual);
}

void Element::AddTimelines(const Node& owner) {
  if (owner.timelines.empty() && owner.named_frames.empty()) {
    return;
  }
  timeline_sets_.push_back({&owner.timelines, &owner.named_frames});
}

Element* Element::AttachScene(const Node& node, const SceneContext& context) {
  auto owned = std::make_unique<SceneContext>(context);
  std::unique_ptr<Element> child(new Element(node, this, owned.get()));
  child->owned_context_ = std::move(owned);
  child->design_parent_width_ = GetFloat("Width", kDefaultWidth);
  child->design_parent_height_ = GetFloat("Height", kDefaultHeight);
  child->Build(node);
  children_.push_back(std::move(child));
  return children_.back().get();
}

std::string_view Element::id() const {
  return GetString("Id");
}

bool Element::IsA(std::string_view name) const {
  for (const ClassDef* cls = cls_; cls; cls = cls->base.empty() ? nullptr : FindClass(cls->base)) {
    if (cls->name == name) {
      return true;
    }
  }
  return false;
}

Element* Element::FindById(std::string_view wanted) {
  for (auto& child : children_) {
    if (child->id() == wanted) {
      return child.get();
    }
  }
  for (auto& child : children_) {
    if (Element* found = child->FindById(wanted)) {
      return found;
    }
  }
  return nullptr;
}

const Value* Element::Get(std::string_view name) const {
  for (const PropertyBag::Entry& entry : props_.entries) {
    if (entry.def && entry.def->name == name) {
      return &entry.value;
    }
  }
  return nullptr;
}

float Element::GetFloat(std::string_view name, float fallback) const {
  const Value* v = Get(name);
  const float* f = v ? v->get<float>() : nullptr;
  return f ? *f : fallback;
}

bool Element::GetBool(std::string_view name, bool fallback) const {
  const Value* v = Get(name);
  const bool* b = v ? v->get<bool>() : nullptr;
  return b ? *b : fallback;
}

uint32_t Element::GetUnsigned(std::string_view name, uint32_t fallback) const {
  const Value* v = Get(name);
  const uint32_t* u = v ? v->get<uint32_t>() : nullptr;
  return u ? *u : fallback;
}

int32_t Element::GetInteger(std::string_view name, int32_t fallback) const {
  const Value* v = Get(name);
  const int32_t* i = v ? v->get<int32_t>() : nullptr;
  return i ? *i : fallback;
}

uint32_t Element::GetColor(std::string_view name, uint32_t fallback) const {
  const Value* v = Get(name);
  const Color* c = v ? v->get<Color>() : nullptr;
  return c ? c->argb : fallback;
}

std::string_view Element::GetString(std::string_view name) const {
  const Value* v = Get(name);
  const std::string* s = v ? v->get<std::string>() : nullptr;
  return s ? std::string_view(*s) : std::string_view();
}

Vec3 Element::GetVector(std::string_view name, Vec3 fallback) const {
  const Value* v = Get(name);
  const Vec3* vec = v ? v->get<Vec3>() : nullptr;
  return vec ? *vec : fallback;
}

Quat Element::GetQuaternion(std::string_view name) const {
  const Value* v = Get(name);
  const Quat* q = v ? v->get<Quat>() : nullptr;
  return q ? *q : Quat{};
}

const PropertyBag* Element::GetCompound(std::string_view name) const {
  const Value* v = Get(name);
  const auto* bag = v ? v->get<std::shared_ptr<const PropertyBag>>() : nullptr;
  return bag ? bag->get() : nullptr;
}

const PropDef* Element::FindDef(std::string_view name) const {
  for (const ClassDef* cls : ClassChain(cls_)) {
    for (const PropDef& def : cls->props) {
      if (def.name == name) {
        return &def;
      }
    }
  }
  return nullptr;
}

void Element::Set(std::string_view name, Value value) {
  for (PropertyBag::Entry& entry : props_.entries) {
    if (entry.def && entry.def->name == name) {
      entry.value = std::move(value);
      return;
    }
  }
  if (const PropDef* def = FindDef(name)) {
    props_.entries.push_back({def, std::move(value)});
  }
}

namespace {

// Returns a copy of `bag` with the value at `path` (and array `index`) replaced.
std::shared_ptr<const PropertyBag> ReplaceInBag(const PropertyBag* bag,
                                                std::span<const PropDef* const> path, int32_t index,
                                                const Value& value) {
  auto copy = std::make_shared<PropertyBag>(bag ? *bag : PropertyBag{});
  PropertyBag::Entry* entry = nullptr;
  for (PropertyBag::Entry& e : copy->entries) {
    if (e.def == path[0]) {
      entry = &e;
      break;
    }
  }
  if (!entry) {
    copy->entries.push_back({path[0], Value{}});
    entry = &copy->entries.back();
  }
  if (path.size() > 1) {
    const auto* inner = entry->value.get<std::shared_ptr<const PropertyBag>>();
    entry->value.data = ReplaceInBag(inner ? inner->get() : nullptr, path.subspan(1), index, value);
  } else if (index >= 0) {
    const auto* list = entry->value.get<std::shared_ptr<const std::vector<Value>>>();
    auto items =
        std::make_shared<std::vector<Value>>(list && *list ? **list : std::vector<Value>());
    if (size_t(index) >= items->size()) {
      items->resize(size_t(index) + 1);
    }
    (*items)[size_t(index)] = value;
    entry->value.data = std::shared_ptr<const std::vector<Value>>(std::move(items));
  } else {
    entry->value = value;
  }
  return copy;
}

}  // namespace

void Element::SetPath(std::span<const PropDef* const> path, int32_t index, const Value& value) {
  if (path.empty()) {
    return;
  }
  if (path.size() == 1 && index < 0) {
    for (PropertyBag::Entry& entry : props_.entries) {
      if (entry.def == path[0]) {
        entry.value = value;
        return;
      }
    }
    props_.entries.push_back({path[0], value});
    return;
  }
  // Compound or indexed: replace a copy, since bags are shared with the scene.
  PropertyBag holder;
  holder.entries = props_.entries;
  auto updated = ReplaceInBag(&holder, path, index, value);
  props_.entries = updated->entries;
}

float Element::width() const {
  float w = GetFloat("Width", kDefaultWidth);
  if (!parent_ || design_parent_width_ <= 0.0f) {
    return w;
  }
  const uint32_t anchor = GetUnsigned("Anchor");
  const float parent_width = parent_->width();
  if ((anchor & kAnchorLeft) && (anchor & kAnchorRight)) {
    w += parent_width - design_parent_width_;
  } else if (anchor & kAnchorXScale) {
    w *= parent_width / design_parent_width_;
  }
  return std::max(w, 0.0f);
}

float Element::height() const {
  float h = GetFloat("Height", kDefaultHeight);
  if (!parent_ || design_parent_height_ <= 0.0f) {
    return h;
  }
  const uint32_t anchor = GetUnsigned("Anchor");
  const float parent_height = parent_->height();
  if ((anchor & kAnchorTop) && (anchor & kAnchorBottom)) {
    h += parent_height - design_parent_height_;
  } else if (anchor & kAnchorYScale) {
    h *= parent_height / design_parent_height_;
  }
  return std::max(h, 0.0f);
}

Vec3 Element::position() const {
  Vec3 p = GetVector("Position");
  if (!parent_) {
    return p;
  }
  const uint32_t anchor = GetUnsigned("Anchor");
  if (design_parent_width_ > 0.0f) {
    const float dw = parent_->width() - design_parent_width_;
    if ((anchor & kAnchorRight) && !(anchor & kAnchorLeft)) {
      p.x += dw;
    } else if (anchor & kAnchorXCenter) {
      p.x += dw / 2.0f;
    } else if (anchor & kAnchorXScale) {
      p.x *= parent_->width() / design_parent_width_;
    }
  }
  if (design_parent_height_ > 0.0f) {
    const float dh = parent_->height() - design_parent_height_;
    if ((anchor & kAnchorBottom) && !(anchor & kAnchorTop)) {
      p.y += dh;
    } else if (anchor & kAnchorYCenter) {
      p.y += dh / 2.0f;
    } else if (anchor & kAnchorYScale) {
      p.y *= parent_->height() / design_parent_height_;
    }
  }
  return p;
}

bool Element::HasNamedFrame(std::string_view name) const {
  for (const TimelineSet& set : timeline_sets_) {
    for (const NamedFrame& frame : *set.frames) {
      if (frame.name == name) {
        return true;
      }
    }
  }
  return false;
}

bool Element::Play(std::string_view name) {
  for (const TimelineSet& set : timeline_sets_) {
    for (const NamedFrame& frame : *set.frames) {
      if (frame.name != name) {
        continue;
      }
      frame_ = frame.frame;
      playing_ =
          frame.command != FrameCommand::kStop && frame.command != FrameCommand::kGoToAndStop;
      ApplyFrame(frame_);
      FireSounds(frame_, frame_, /*inclusive=*/true);
      return true;
    }
  }
  return false;
}

void Element::Advance(double frames) {
  if (playing_ && frames > 0.0) {
    const double from = frame_;
    double to = from + frames;
    // The first command the playhead crosses decides where it ends up.
    const NamedFrame* hit = nullptr;
    double last_frame = 0.0;
    for (const TimelineSet& set : timeline_sets_) {
      for (const NamedFrame& frame : *set.frames) {
        last_frame = std::max(last_frame, double(frame.frame));
        if (frame.frame > from && frame.frame <= to && frame.command != FrameCommand::kPlay &&
            (!hit || frame.frame < hit->frame)) {
          hit = &frame;
        }
      }
      for (const Timeline& timeline : *set.timelines) {
        if (!timeline.keyframes.empty()) {
          last_frame = std::max(last_frame, double(timeline.keyframes.back().frame));
        }
      }
    }
    if (hit) {
      to = hit->frame;
    } else if (to >= last_frame) {
      to = last_frame;
      playing_ = false;
    }
    FireSounds(from, to, /*inclusive=*/false);
    frame_ = to;
    if (hit) {
      switch (hit->command) {
        case FrameCommand::kStop:
          playing_ = false;
          break;
        case FrameCommand::kGoTo:
        case FrameCommand::kGoToAndPlay:
        case FrameCommand::kGoToAndStop: {
          const bool keep_playing = hit->command != FrameCommand::kGoToAndStop;
          const std::string target = hit->target;
          Play(target);
          playing_ = keep_playing;
          break;
        }
        case FrameCommand::kPlay:
          break;
      }
    }
    ApplyFrame(frame_);
  }
  for (auto& child : children_) {
    child->Advance(frames);
  }
}

void Element::ApplyFrame(double frame) {
  Value scratch;
  for (const TimelineSet& set : timeline_sets_) {
    for (const Timeline& timeline : *set.timelines) {
      Element* target = FindById(timeline.target_id);
      if (!target) {
        continue;
      }
      for (size_t p = 0; p < timeline.props.size(); ++p) {
        const AnimatedProperty& prop = timeline.props[p];
        if (prop.path.empty() || prop.path.back()->name == "File") {
          continue;  // unknown to the schema, or a sound cue
        }
        if (const Value* value = Evaluate(timeline, p, frame, scratch)) {
          target->SetPath(prop.path, prop.index, *value);
        }
      }
    }
  }
}

void Element::FireSounds(double from, double to, bool inclusive) {
  if (!context_->play_sound) {
    return;
  }
  for (const TimelineSet& set : timeline_sets_) {
    for (const Timeline& timeline : *set.timelines) {
      for (size_t p = 0; p < timeline.props.size(); ++p) {
        const AnimatedProperty& prop = timeline.props[p];
        if (prop.path.empty() || prop.path.back()->name != "File") {
          continue;
        }
        for (const Keyframe& key : timeline.keyframes) {
          const bool crossed = inclusive ? (key.frame >= from && key.frame <= to)
                                         : (key.frame > from && key.frame <= to);
          const std::string* file = key.values[p].get<std::string>();
          if (crossed && file && !file->empty()) {
            context_->play_sound(*file, context_->package);
          }
        }
      }
    }
  }
}

bool Element::focusable() const {
  return IsA("XuiControl") && !IsA("XuiScene") && visible() && GetBool("Enabled", true);
}

Element* Element::Navigate(NavDirection direction) {
  constexpr std::string_view kNames[] = {"NavUp", "NavDown", "NavLeft", "NavRight"};
  Element* scene = parent_;
  while (scene && !scene->IsA("XuiScene")) {
    scene = scene->parent_;
  }
  if (!scene) {
    return nullptr;
  }
  // Hidden or disabled controls pass navigation on in the same direction.
  Element* at = this;
  for (int hops = 0; hops < 64; ++hops) {
    const std::string_view target = at->GetString(kNames[int(direction)]);
    if (target.empty()) {
      return nullptr;
    }
    Element* next = scene->FindById(target);
    if (!next || next == this) {
      return nullptr;
    }
    if (next->focusable()) {
      return next;
    }
    at = next;
  }
  return nullptr;
}

void Element::MoveFocus(Element* from, Element* to, bool initial) {
  if (from && from != to) {
    if (!from->Play("KillFocus")) {
      from->Play("Normal");
    }
  }
  if (to) {
    if (!(initial && to->Play("InitFocus"))) {
      to->Play("Focus");
    }
  }
}

}  // namespace rex::ui::xui
