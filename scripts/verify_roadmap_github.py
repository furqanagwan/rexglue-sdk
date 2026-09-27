"""Read-only verification of published issue bodies, labels and dependencies.

Requires an authenticated gh CLI. Writes the local verification record only.
Run after deliberate issue/body updates; this script never changes GitHub.
"""
import hashlib
import json
from pathlib import Path
import subprocess
from datetime import datetime, timezone

ROOT = Path(__file__).resolve().parents[1]
REPO = "furqanagwan/rexglue-sdk"
rows = json.loads((ROOT / "docs/roadmap/index.json").read_text(encoding="utf-8"))
live = json.loads(subprocess.check_output(
    ["gh", "issue", "list", "--repo", REPO, "--state", "all", "--limit", "1000",
     "--json", "number,title,url,body,labels,state"], text=True, encoding="utf-8"))
by_number = {item["number"]: item for item in live}
by_id = {row["id"]: row for row in rows}
checks = []
for row in rows:
    item = by_number[row["number"]]
    body = (ROOT / row["body_file"]).read_text(encoding="utf-8")
    if item["body"].replace("\r\n", "\n").strip() != body.strip():
        raise SystemExit(f"{row['id']}: live issue body differs")
    if {label["name"] for label in item["labels"]} != set(row["labels"]):
        raise SystemExit(f"{row['id']}: live labels differ")
    if item["state"].lower() != row["state"]:
        raise SystemExit(f"{row['id']}: state changed; refresh index and readiness")
    if item["title"] != f"[{row['id']}] {row['title']}" or item["url"] != row["url"]:
        raise SystemExit(f"{row['id']}: title or URL differs")
    for dep in row["depends_on"]:
        if by_id[dep]["url"] not in item["body"]:
            raise SystemExit(f"{row['id']}: missing live prerequisite link {dep}")
        if "agent-ready" in row["labels"] and by_number[by_id[dep]["number"]]["state"] != "CLOSED":
            raise SystemExit(f"{row['id']}: incomplete live dependency {dep}")
    checks.append({"id": row["id"], "number": row["number"], "url": row["url"],
                   "body_matches": True, "labels_match": True, "state": item["state"],
                   "body_sha256": hashlib.sha256(body.encode("utf-8")).hexdigest(),
                   "dependencies": [by_id[d]["number"] for d in row["depends_on"]]})
record = {"verified_at": datetime.now(timezone.utc).isoformat(), "repo": REPO,
          "documentation_branch": "docs/windows-gdk-modernization-roadmap", "issues": checks}
(ROOT / "docs/roadmap/github-verification.json").write_text(
    json.dumps(record, indent=2) + "\n", encoding="utf-8")
print(f"Verified {len(checks)} live issue titles, states, bodies, labels and dependency links.")
