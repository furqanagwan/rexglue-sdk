"""Write a separate, non-overwriting assessment of a captured baseline run."""

import argparse
from datetime import datetime, timezone
import json
from pathlib import Path

from capture_baseline import sha256


def assess(run_directory, output, result, reviewer, reason):
    if result not in ('pass', 'fail', 'blocked'):
        raise ValueError('Assessment must be pass, fail or blocked')
    run_directory = Path(run_directory)
    manifest = run_directory / 'run.json'
    record = json.loads(manifest.read_text(encoding='utf-8'))
    if record.get('schema_version') != 1:
        raise ValueError('Unsupported run schema')
    if result == 'pass' and (record.get('execution_status') != 'completed' or
                             record.get('status') != 'not-run'):
        raise ValueError('Only a completed run can be assessed as passing')
    if not reviewer.strip() or not reason.strip():
        raise ValueError('Reviewer and evidence-based reason are required')
    for name, expected_hash in record.get('artifacts', {}).items():
        if Path(name).name != name or sha256(run_directory / name) != expected_hash:
            raise ValueError(f'Artifact is missing, changed or has an unsafe name: {name}')
    assessment = dict(schema_version=1,
                      timestamp=datetime.now(timezone.utc).isoformat(),
                      run_manifest_sha256=sha256(manifest), title=record['title'],
                      status=result, reviewer=reviewer, reason=reason,
                      artifacts=record['artifacts'])
    output = Path(output)
    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open('x', encoding='utf-8') as stream:
        json.dump(assessment, stream, indent=2)
        stream.write('\n')
    return assessment


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--run', required=True)
    parser.add_argument('--output', required=True)
    parser.add_argument('--status', choices=['pass', 'fail', 'blocked'], required=True)
    parser.add_argument('--reviewer', required=True)
    parser.add_argument('--reason', required=True)
    args = parser.parse_args()
    try:
        result = assess(args.run, args.output, args.status, args.reviewer, args.reason)
    except (OSError, ValueError, KeyError) as error:
        parser.error(str(error))
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    main()
