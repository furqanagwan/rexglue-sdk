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


if __name__ == '__main__':
    unittest.main()
