"""Validate planning IDs, dependency DAG, issue bodies, source paths and readiness.

Run from the repository root. No GitHub credentials or third-party packages needed.
"""
import json
import hashlib
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
rows = json.loads((ROOT / "docs/roadmap/index.json").read_text(encoding="utf-8"))
by_id = {row["id"]: row for row in rows}
errors = []
expected = [f"RG-GDK-{i:03}" for i in range(1, len(rows) + 1)]
if [row["id"] for row in rows] != expected or len(by_id) != len(rows):
    errors.append("Planning IDs must be unique and sequential")
required = ["Planning ID", "Labels", "Objective", "Background", "Architecture Context",
            "Upstream Evidence", "Scope", "Out of Scope", "Relevant Files", "Tasks",
            "Dependencies", "Blocks", "Regression Risk", "Regression Tests",
            "Vendor Validation", "Acceptance Criteria", "Validation Commands",
            "Documentation Changes", "Agent Handoff Notes"]
visiting, visited = set(), set()


def visit(key):
    if key in visiting:
        errors.append(f"Dependency cycle at {key}")
        return
    if key in visited:
        return
    visiting.add(key)
    for dep in by_id[key]["depends_on"]:
        if dep not in by_id:
            errors.append(f"{key}: unknown dependency {dep}")
        else:
            visit(dep)
    visiting.remove(key)
    visited.add(key)


for row in rows:
    key = row["id"]
    visit(key)
    body = (ROOT / row["body_file"]).read_text(encoding="utf-8")
    for heading in required:
        if f"## {heading}\n" not in body:
            errors.append(f"{key}: missing section {heading}")
    deps = re.findall(r"^Depends on: (RG-GDK-\d{3})", body, re.MULTILINE)
    blocks = re.findall(r"^Blocks: (RG-GDK-\d{3})", body, re.MULTILINE)
    if deps != row["depends_on"]:
        errors.append(f"{key}: body dependencies differ from index")
    actual_blocks = [r["id"] for r in rows if key in r["depends_on"]]
    if blocks != actual_blocks or row["blocks"] != actual_blocks:
        errors.append(f"{key}: reverse dependencies inconsistent")
    # Closed issues may have deleted their own source paths (e.g. RG-GDK-023/024).
    for source in [] if row.get("state") == "closed" else row["files"]:
        if not (ROOT / source).exists():
            errors.append(f"{key}: source path does not exist: {source}")
    if "agent-ready" in row["labels"]:
        for dep in row["depends_on"]:
            if by_id.get(dep, {}).get("state") != "closed":
                errors.append(f"{key}: agent-ready with incomplete dependency {dep}")
    if row.get("url"):
        if not re.fullmatch(r"https://github.com/furqanagwan/rexglue-sdk/issues/\d+", row["url"]):
            errors.append(f"{key}: issue is outside authorized repository")

# Check relative documentation links, excluding remote URLs, anchors and code fragments.
paths = [ROOT / "README.md", ROOT / "AGENTS.md", *list((ROOT / "docs").rglob("*.md"))]
for path in paths:
    for target in re.findall(r"\]\(([^\s)]+)\)", path.read_text(encoding="utf-8")):
        if "://" in target or target.startswith("#"):
            continue
        local = target.split("#", 1)[0]
        if local and not (path.parent / local).exists():
            errors.append(f"{path.relative_to(ROOT)}: broken relative link {target}")

if errors:
    print("\n".join(errors))
    sys.exit(1)
print(f"Validated {len(rows)} sequential issues, acyclic dependencies, reverse links, "
      "readiness, source paths and relative documentation links.")

verification = ROOT / "docs/roadmap/github-verification.json"
if verification.exists():
    record = json.loads(verification.read_text(encoding="utf-8"))
    for check in record["issues"]:
        body = (ROOT / by_id[check["id"]]["body_file"]).read_text(encoding="utf-8")
        if check.get("body_sha256") != hashlib.sha256(body.encode("utf-8")).hexdigest():
            raise SystemExit(f"{check['id']}: publication verification is stale; verify live GitHub bodies")
    print("Stored publication verification hashes match local issue bodies.")
