"""Record an isolated baseline run. Exit zero means execution completed, not compatibility.

Private material and run artifacts stay outside Git. An explicit reviewer assessment
is required to turn a completed run into a compatibility pass.
"""
import argparse
import hashlib
import json
import math
from pathlib import Path
import platform
import shutil
import subprocess
import time
from datetime import datetime, timezone


def sha256(path):
    digest = hashlib.sha256()
    with Path(path).open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            digest.update(block)
    return digest.hexdigest()


def capture(output, command, material=None, timeout=60, title='unknown', metadata=None,
            extra_artifacts=()):
    output = Path(output)
    # Never overwrite an earlier run, including a failed one.
    output.mkdir(parents=True, exist_ok=False)
    record = dict(schema_version=1, timestamp=datetime.now(timezone.utc).isoformat(),
                  title=title, status='not-run', execution_status='not-run',
                  compatibility_status='not-run', command=command,
                  host=dict(os=platform.platform(), machine=platform.machine()),
                  environment=dict(gpu='unknown', driver='unknown', gdk='not used',
                                   compiler='unknown', windows_sdk='unknown',
                                   build='unknown', rendering_path='unknown',
                                   title_id='unknown', media_id='unknown',
                                   scene='unknown', owner='unknown'),
                  artifacts={}, material=None, reason=None)
    root = Path(__file__).resolve().parents[1]
    try:
        revision = subprocess.run(['git', '-C', str(root), 'rev-parse', 'HEAD'],
                                  capture_output=True, text=True)
        record['sdk_commit'] = revision.stdout.strip() if revision.returncode == 0 else 'unknown'
        status = subprocess.run(['git', '-C', str(root), 'status', '--porcelain'],
                                capture_output=True, text=True)
        record['sdk_worktree_status'] = status.stdout if status.returncode == 0 else 'unknown'
        record['working_directory'] = str(Path.cwd())
        if metadata:
            metadata = Path(metadata)
            record['metadata_sha256'] = sha256(metadata)
            environment = json.loads(metadata.read_text(encoding='utf-8-sig'))
            if not isinstance(environment, dict):
                raise ValueError('Metadata must be a JSON object')
            for key in record['environment']:
                if key in environment and not isinstance(environment[key], str):
                    raise ValueError(f'Metadata {key} must be a string')
            record['environment'].update(environment)
        names = [Path(path).name for path in extra_artifacts]
        if (len(names) != len(set(names)) or
                any(name in ('run.json', 'stdout.log', 'stderr.log') for name in names) or
                any(not Path(path).is_file() for path in extra_artifacts)):
            record.update(status='blocked', reason='An artifact is missing or has a duplicate/reserved name')
            return record
        if material:
            material = Path(material)
            if not material.is_file():
                record.update(status='blocked', reason='Required private material is missing')
                return record
            record['material'] = dict(name=material.name, bytes=material.stat().st_size,
                                      sha256=sha256(material))
        if not command:
            record.update(status='blocked', reason='No compiled title executable supplied')
            return record
        executable = Path(command[0]).resolve()
        if not executable.is_file():
            record.update(status='blocked', reason='Executable is missing (use an explicit path)')
            return record
        record['executable_sha256'] = sha256(executable)
        started = time.monotonic()
        with (output / 'stdout.log').open('wb') as stdout, (output / 'stderr.log').open('wb') as stderr:
            try:
                result = subprocess.run([str(executable), *command[1:]], stdout=stdout,
                                        stderr=stderr, timeout=timeout, shell=False)
                record['exit_code'] = result.returncode
                record['execution_status'] = 'completed' if result.returncode == 0 else 'failed'
                record['status'] = 'not-run' if result.returncode == 0 else 'fail'
                record['reason'] = ('Execution completed; compatibility requires review'
                                    if result.returncode == 0 else 'Process returned nonzero')
            except subprocess.TimeoutExpired:
                record.update(status='fail', execution_status='timeout', reason='Run timed out')
        record['duration_seconds'] = time.monotonic() - started
        for name in ['stdout.log', 'stderr.log']:
            record['artifacts'][name] = sha256(output / name)
        for artifact in extra_artifacts:
            source = Path(artifact)
            name = source.name
            destination = output / name
            shutil.copyfile(source, destination)
            record['artifacts'][name] = sha256(destination)
    except (OSError, ValueError) as error:
        record.update(status='blocked', reason=str(error))
    finally:
        (output / 'run.json').write_text(json.dumps(record, indent=2) + '\n', encoding='utf-8')
    return record


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', required=True)
    parser.add_argument('--material')
    parser.add_argument('--title', default='unknown')
    parser.add_argument('--metadata', help='JSON object describing build, hardware and scene')
    parser.add_argument('--artifact', action='append', default=[],
                        help='Copy a screenshot, PIX capture or log into the run (repeatable)')
    parser.add_argument('--timeout', type=float, default=60)
    parser.add_argument('command', nargs=argparse.REMAINDER)
    args = parser.parse_args()
    if not math.isfinite(args.timeout) or args.timeout <= 0:
        parser.error('--timeout must be finite and positive')
    command = args.command[1:] if args.command[:1] == ['--'] else args.command
    record = capture(args.output, command, args.material, args.timeout, args.title,
                     args.metadata, args.artifact)
    print(json.dumps(record, indent=2))
    return 0 if record['execution_status'] == 'completed' else 1


if __name__ == '__main__':
    raise SystemExit(main())
