/**
 * @file        tests/unit/ui/xui_runtime_test.cpp
 * @brief       Live XUI elements: visuals, anchoring, timelines, sounds, focus (RG-GDK-041)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include <rex/ui/xui/document.h>
#include <rex/ui/xui/runtime.h>
#include <rex/ui/xui/system_update.h>

#include "xui_test_data.h"

using namespace rex::ui::xui;
using Catch::Approx;

namespace {

const PropDef* Def(std::string_view cls, std::string_view name) {
  for (const ClassDef* c : ClassChain(FindClass(cls))) {
    for (const PropDef& def : c->props) {
      if (def.name == name) {
        return &def;
      }
    }
  }
  FAIL("no property " << name << " on " << cls);
  return nullptr;
}

using Props = std::vector<std::pair<std::string_view, Value>>;

Node MakeNode(std::string_view cls, Props props, std::vector<Node> children = {}) {
  Node node;
  node.class_name = std::string(cls);
  node.cls = FindClass(cls);
  REQUIRE(node.cls);
  auto bag = std::make_shared<PropertyBag>();
  for (auto& [name, value] : props) {
    bag->entries.push_back({Def(cls, name), std::move(value)});
  }
  node.props = bag;
  node.children = std::move(children);
  return node;
}

Value Str(std::string s) {
  return Value{std::move(s)};
}

Keyframe Key(int32_t frame, Value value, Interpolation interpolation = Interpolation::kLinear,
             int8_t ease_in = 0, int8_t ease_out = 0) {
  Keyframe k;
  k.frame = frame;
  k.interpolation = interpolation;
  k.ease_in = ease_in;
  k.ease_out = ease_out;
  k.values.push_back(std::move(value));
  return k;
}

Timeline Track(std::string target, std::vector<const PropDef*> path, std::vector<Keyframe> keys) {
  Timeline t;
  t.target_id = std::move(target);
  AnimatedProperty prop;
  prop.path = std::move(path);
  t.props.push_back(prop);
  t.keyframes = std::move(keys);
  return t;
}

NamedFrame Frame(std::string name, int32_t frame, FrameCommand command = FrameCommand::kPlay) {
  NamedFrame f;
  f.name = std::move(name);
  f.frame = frame;
  f.command = command;
  return f;
}

// A skin with a button visual (100x20) and a label visual named after its class.
Document MakeSkin() {
  auto fill = std::make_shared<PropertyBag>();
  fill->entries.push_back({Def("XuiFigureFill", "FillColor"), Value{Color{0xFF008A00}}});
  Node visual = MakeNode(
      "XuiVisual", {{"Id", Str("Btn")}, {"Width", Value{100.0f}}, {"Height", Value{20.0f}}},
      {
          MakeNode("XuiFigure", {{"Id", Str("hl")},
                                 {"Width", Value{100.0f}},
                                 {"Height", Value{20.0f}},
                                 {"Anchor", Value{uint32_t(15)}},
                                 {"Fill", Value{std::shared_ptr<const PropertyBag>(fill)}}}),
          MakeNode("XuiTextPresenter", {{"Id", Str("text_Label")},
                                        {"Width", Value{80.0f}},
                                        {"Anchor", Value{uint32_t(kAnchorLeft | kAnchorRight)}}}),
          MakeNode("XuiImagePresenter", {{"Id", Str("icon")},
                                         {"Position", Value{Vec3{90.0f, 0.0f, 0.0f}}},
                                         {"Width", Value{10.0f}},
                                         {"Anchor", Value{uint32_t(kAnchorRight)}}}),
          MakeNode("XuiSoundXAudio", {{"Id", Str("snd")}}),
      });
  const PropDef* opacity = Def("XuiFigure", "Opacity");
  visual.timelines.push_back(
      Track("hl", {opacity},
            {Key(0, Value{0.0f}), Key(5, Value{0.0f}, Interpolation::kEase, -100, 100),
             Key(15, Value{1.0f}), Key(16, Value{0.5f})}));
  visual.timelines.push_back(Track(
      "hl", {Def("XuiFigure", "Fill"), Def("XuiFigureFill", "FillColor")},
      {Key(0, Value{Color{0xFF008A00}}), Key(16, Value{Color{0xFF1CB61C}}, Interpolation::kNone)}));
  visual.timelines.push_back(Track(
      "snd", {Def("XuiSoundXAudio", "File")},
      {Key(0, Str(""), Interpolation::kNone), Key(5, Str("focus.xma"), Interpolation::kNone),
       Key(6, Str(""), Interpolation::kNone), Key(16, Str("press.xma"), Interpolation::kNone)}));
  visual.named_frames = {Frame("KillFocus", 0), Frame("EndKillFocus", 4, FrameCommand::kStop),
                         Frame("Focus", 5),     Frame("EndFocus", 15, FrameCommand::kStop),
                         Frame("Press", 16),    Frame("EndPress", 18, FrameCommand::kStop)};

  Node label = MakeNode("XuiVisual", {{"Id", Str("XuiLabel")}, {"Width", Value{100.0f}}},
                        {MakeNode("XuiTextPresenter", {{"Id", Str("Text")}})});
  Document skin;
  skin.root = MakeNode("XuiCanvas", {}, {std::move(visual), std::move(label)});
  return skin;
}

Node Button(std::string id, Props extra) {
  Props props = {{"Id", Str(std::move(id))},
                 {"Visual", Str("Btn")},
                 {"Width", Value{150.0f}},
                 {"Height", Value{20.0f}}};
  for (auto& p : extra) {
    props.push_back(std::move(p));
  }
  return MakeNode("XuiButton", std::move(props));
}

Document MakeScene() {
  Document doc;
  doc.root =
      MakeNode("XuiCanvas", {{"Width", Value{300.0f}}, {"Height", Value{200.0f}}},
               {MakeNode("XuiScene", {{"Id", Str("scene")}, {"Width", Value{300.0f}}},
                         {Button("a", {{"NavDown", Str("b")}}),
                          Button("b", {{"NavDown", Str("c")}, {"Show", Value{false}}}),
                          Button("c", {{"NavUp", Str("a")}}),
                          MakeNode("XuiLabel", {{"Id", Str("lbl")}, {"Text", Str("Hi")}})})});
  return doc;
}

struct Fixture {
  Document skin = MakeSkin();
  Document scene = MakeScene();
  std::vector<std::string> sounds;
  SceneContext context;
  std::unique_ptr<Element> root;

  Fixture() {
    context.skin = &skin;
    context.package = "hud/hud";
    context.play_sound = [this](std::string_view file, std::string_view) {
      sounds.emplace_back(file);
    };
    root = Element::Create(scene.root, context);
  }
  Element* Find(std::string_view id) { return root->FindById(id); }
};

}  // namespace

TEST_CASE("Controls take their skin visual and anchor it to their own size", "[xui]") {
  Fixture f;
  Element* a = f.Find("a");
  REQUIRE(a);
  Element* hl = a->FindById("hl");
  REQUIRE(hl);
  // The visual is 100 wide; the button is 150.
  CHECK(hl->width() == Approx(150.0f));
  CHECK(a->FindById("text_Label")->width() == Approx(130.0f));
  CHECK(a->FindById("icon")->position().x == Approx(140.0f));
  CHECK(a->FindById("icon")->width() == Approx(10.0f));
  // No Visual property: the visual named after the class.
  REQUIRE(f.Find("lbl")->FindById("Text"));
}

TEST_CASE("Timelines show frame 0 when built and play named frames with easing", "[xui]") {
  Fixture f;
  Element* a = f.Find("a");
  Element* hl = a->FindById("hl");
  CHECK(hl->GetFloat("Opacity", -1.0f) == Approx(0.0f));
  CHECK(f.sounds.empty());

  REQUIRE(a->Play("Focus"));
  CHECK(f.sounds == std::vector<std::string>{"focus.xma"});
  a->Advance(5.0);
  // Halfway through an ease-in -100 / ease-out 100 segment.
  CHECK(hl->GetFloat("Opacity") == Approx(0.75f));
  CHECK(a->playing());
  a->Advance(20.0);
  // EndFocus stops the playhead on its frame.
  CHECK_FALSE(a->playing());
  CHECK(a->frame() == Approx(15.0));
  CHECK(hl->GetFloat("Opacity") == Approx(1.0f));
  CHECK(f.sounds.size() == 1);
}

TEST_CASE("Sound cues fire once as the playhead crosses them", "[xui]") {
  Fixture f;
  Element* a = f.Find("a");
  REQUIRE(a->Play("Press"));
  a->Advance(1.0);
  a->Advance(5.0);
  CHECK(f.sounds == std::vector<std::string>{"press.xma"});
  CHECK_FALSE(a->Play("NoSuchFrame"));
}

TEST_CASE("Compound properties animate per element, not in the shared scene data", "[xui]") {
  Fixture f;
  Element* a = f.Find("a");
  Element* c = f.Find("c");
  a->Play("Press");
  auto fill_color = [](Element* e) {
    const Value* v = e->FindById("hl")->GetCompound("Fill")->Find("FillColor");
    return v->get<Color>()->argb;
  };
  CHECK(fill_color(a) == 0xFF1CB61C);
  CHECK(fill_color(c) == 0xFF008A00);
  // The skin document is untouched.
  const auto* doc_fill =
      f.skin.root.children[0].children[0].Find("Fill")->get<std::shared_ptr<const PropertyBag>>();
  CHECK((*doc_fill)->Find("FillColor")->get<Color>()->argb == 0xFF008A00);
}

TEST_CASE("Navigation passes over hidden controls and focus plays the visual", "[xui]") {
  Fixture f;
  Element* a = f.Find("a");
  Element* c = f.Find("c");
  CHECK(a->focusable());
  CHECK_FALSE(f.Find("b")->focusable());
  CHECK(a->Navigate(NavDirection::kDown) == c);
  CHECK(c->Navigate(NavDirection::kUp) == a);
  CHECK(c->Navigate(NavDirection::kDown) == nullptr);

  Element::MoveFocus(a, c);
  CHECK(c->frame() == Approx(5.0));
  CHECK(a->frame() == Approx(0.0));
  CHECK(f.sounds == std::vector<std::string>{"focus.xma"});
}

TEST_CASE("The XUI ease curve", "[xui]") {
  CHECK(EaseProgress(0.0f, -100, 100) == Approx(0.0f));
  CHECK(EaseProgress(1.0f, -100, 100) == Approx(1.0f));
  CHECK(EaseProgress(0.5f, 0, 0) == Approx(0.5f));
  CHECK(EaseProgress(0.25f, 0, 0) == Approx(0.25f));
  CHECK(EaseProgress(0.5f, -100, 100) == Approx(0.75f));
  CHECK(EaseProgress(0.5f, 100, -100) == Approx(0.25f));
}

TEST_CASE("Scene paths resolve by protocol, then the scene's package, then shared ones", "[xui]") {
  using namespace xui_test;
  SystemUpdate update;
  std::string error;
  REQUIRE(update.AddModule("hud", XexWithResource("hud", Xuiz({{"a.png", "A"}}), 0), &error));
  REQUIRE(update.AddModule("xam", XexWithResource("shrdres", Xuiz({{"b.png", "B"}}), 0), &error));
  REQUIRE(
      update.AddModule("huduiskin", XexWithResource("skin", Xuiz({{"c.png", "C"}}), 0), &error));
  auto text = [](std::span<const uint8_t> bytes) {
    return std::string(bytes.begin(), bytes.end());
  };
  CHECK(text(ResolveFile(update, "sharedres://b.png", "hud/hud")) == "B");
  CHECK(text(ResolveFile(update, "a.png", "hud/hud")) == "A");
  CHECK(text(ResolveFile(update, "c.png", "hud/hud")) == "C");
  CHECK(ResolveFile(update, "missing.png", "hud/hud").empty());
  CHECK(ResolveFile(update, "sharedres://a.png", "hud/hud").empty());
}

// Local only (REXGLUE_SYSTEM_UPDATE): the console's guide plays its blade shuffle.
TEST_CASE("The console's guide scene plays its tab transitions", "[xui][local]") {
  const char* path = std::getenv("REXGLUE_SYSTEM_UPDATE");
  if (!path || !*path) {
    SKIP("REXGLUE_SYSTEM_UPDATE is not set");
  }
  std::string error;
  auto update = SystemUpdate::Load(path, &error);
  REQUIRE(update);
  auto skin = ParseXur(update->Find("huduiskin/skin")->Find("skin.xur"), &error);
  REQUIRE(skin);
  auto guide = ParseXur(update->Find("hud/hud")->Find("GuideMain.xur"), &error);
  REQUIRE(guide);
  std::vector<std::string> sounds;
  SceneContext context;
  context.skin = &*skin;
  context.package = "hud/hud";
  context.play_sound = [&](std::string_view file, std::string_view package) {
    sounds.emplace_back(file);
    CHECK_FALSE(ResolveFile(*update, file, package).empty());
  };
  auto root = Element::Create(guide->root, context);
  Element* tabs = root->FindById("Tabscene");
  REQUIRE(tabs);
  Element* blade7 = root->FindById("Blade7");
  REQUIRE(blade7);
  const float x_before = blade7->position().x;
  REQUIRE(tabs->Play("2To3"));
  tabs->Advance(40.0);
  CHECK_FALSE(tabs->playing());
  CHECK(tabs->frame() == Approx(36.0));
  CHECK(blade7->position().x != Approx(x_before));
  CHECK(sounds == std::vector<std::string>{"BladeSwitch_2.xma"});
}
