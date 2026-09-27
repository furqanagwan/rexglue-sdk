import importlib.util
import json
from pathlib import Path
import sys
import tempfile
import unittest

spec = importlib.util.spec_from_file_location('capture_baseline', Path(__file__).parents[1] / 'capture_baseline.py')
capture = importlib.util.module_from_spec(spec)
spec.loader.exec_module(capture)


class BaselineTests(unittest.TestCase):
    def test_manifest_has_versioned_required_fields(self):
        schema = json.loads((Path(__file__).parents[2] / 'docs' /
                             'baseline-run.schema.json').read_text())
        with tempfile.TemporaryDirectory() as directory:
            record = capture.capture(Path(directory) / 'run', [])
            self.assertEqual(record['schema_version'], schema['properties']['schema_version']['const'])
            self.assertTrue(set(schema['required']).issubset(record))
            required_environment = schema['properties']['environment']['required']
            self.assertTrue(set(required_environment).issubset(record['environment']))

    def test_metadata_cannot_override_results(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            metadata = root / 'environment.json'
            metadata.write_text('{"status": "pass", "gpu": "fixture"}')
            result = capture.capture(root / 'valid', [], metadata=metadata)
            self.assertEqual(result['status'], 'blocked')
            self.assertEqual(result['environment']['gpu'], 'fixture')
            self.assertEqual(result['metadata_sha256'], capture.sha256(metadata))
            metadata.write_text('[]')
            result = capture.capture(root / 'invalid', [], metadata=metadata)
            self.assertEqual(result['status'], 'blocked')
            self.assertIsInstance(result['environment'], dict)
            metadata.write_text('{"gpu": []}')
            result = capture.capture(root / 'wrong_field_type', [], metadata=metadata)
            self.assertEqual(result['status'], 'blocked')
            self.assertEqual(result['environment']['gpu'], 'unknown')

    def test_outcomes_and_preservation(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            cases = [(['missing.exe'], None, 'blocked'),
                     ([sys.executable, '-c', 'pass'], root / 'missing.iso', 'blocked'),
                     ([sys.executable, '-c', 'raise SystemExit(7)'], None, 'fail'),
                     ([sys.executable, '-c', 'print("fixture")'], None, 'not-run')]
            for index, (command, material, expected) in enumerate(cases):
                output = root / str(index)
                record = capture.capture(output, command, material)
                self.assertEqual(record['status'], expected)
                self.assertEqual(record['compatibility_status'], 'not-run')
                before = (output / 'run.json').read_bytes()
                with self.assertRaises(FileExistsError):
                    capture.capture(output, command, material)
                self.assertEqual(before, (output / 'run.json').read_bytes())
                self.assertEqual(json.loads(before), record)

    def test_timeout_and_artifact_hash(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            result = capture.capture(root / 'timeout', [sys.executable, '-c', 'import time; time.sleep(10)'], timeout=.05)
            self.assertEqual(result['execution_status'], 'timeout')
            for n in ['one', 'two']:
                result = capture.capture(root / n, [sys.executable, '-c', 'print("repeatable")'])
                self.assertEqual(result['artifacts']['stdout.log'], capture.sha256(root / n / 'stdout.log'))
            self.assertEqual(capture.sha256(root / 'one/stdout.log'), capture.sha256(root / 'two/stdout.log'))

    def test_extra_artifacts_are_copied_and_hashed(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            screenshot = root / 'screen.png'
            screenshot.write_bytes(b'fixture screenshot')
            result = capture.capture(root / 'run', [sys.executable, '-c', 'pass'],
                                     extra_artifacts=[screenshot])
            self.assertEqual(result['artifacts']['screen.png'], capture.sha256(screenshot))
            self.assertEqual((root / 'run' / 'screen.png').read_bytes(), screenshot.read_bytes())
            duplicate = capture.capture(root / 'invalid', [sys.executable, '-c', 'pass'],
                                        extra_artifacts=[screenshot, screenshot])
            self.assertEqual(duplicate['status'], 'blocked')
            self.assertFalse((root / 'invalid' / 'stdout.log').exists())

    def test_run_for_duration_screenshots_and_collected_logs(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            logs = root / 'logs'
            logs.mkdir()
            (logs / 'old.log').write_text('earlier run')
            shots = []

            def fake_screenshot(path):
                shots.append(path.name)
                path.write_bytes(b'png')

            writer = ('import pathlib, sys, time; '
                      'pathlib.Path(sys.argv[1], "new.log").write_text("title log"); '
                      'time.sleep(30)')
            record = capture.capture(root / 'soak', [sys.executable, '-c', writer, str(logs)],
                                     run_for=1.5, screenshots_at=[0.5],
                                     collect_new=logs, take_screenshot=fake_screenshot)
            self.assertEqual(record['execution_status'], 'ran-for-duration')
            self.assertEqual(record['status'], 'not-run')
            self.assertIsNone(record['exit_code'])
            self.assertLess(record['duration_seconds'], 15)
            self.assertEqual(shots, ['screenshot-0.5s.png'])
            self.assertIn('screenshot-0.5s.png', record['artifacts'])
            self.assertEqual((root / 'soak' / 'collected-new.log').read_text(), 'title log')
            self.assertNotIn('collected-old.log', record['artifacts'])

            # A failed screenshot is recorded; the run goes on and the title is stopped.
            def broken_screenshot(path):
                raise OSError('no display')

            broken = capture.capture(root / 'noshot', [sys.executable, '-c', 'import time; time.sleep(30)'],
                                     run_for=1, screenshots_at=[0.2],
                                     take_screenshot=broken_screenshot)
            self.assertEqual(broken['execution_status'], 'ran-for-duration')
            self.assertEqual(len(broken['screenshot_errors']), 1)

            # A title that dies early is a failure, not a soak.
            early = capture.capture(root / 'early', [sys.executable, '-c', 'raise SystemExit(3)'],
                                    run_for=5)
            self.assertEqual(early['execution_status'], 'failed')
            self.assertEqual(early['status'], 'fail')
            self.assertEqual(early['exit_code'], 3)


if __name__ == '__main__':
    unittest.main()
