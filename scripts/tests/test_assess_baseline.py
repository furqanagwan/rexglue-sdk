import importlib.util
from pathlib import Path
import sys
import tempfile
import unittest

scripts = Path(__file__).parents[1]
sys.path.insert(0, str(scripts))
import assess_baseline
import capture_baseline


class AssessmentTests(unittest.TestCase):
    def test_cannot_pass_failed_or_tampered_run(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            failed = root / 'failed'
            capture_baseline.capture(failed, [sys.executable, '-c', 'raise SystemExit(2)'])
            with self.assertRaisesRegex(ValueError, 'Only a completed run'):
                assess_baseline.assess(failed, root / 'false_pass.json', 'pass',
                                       'tester', 'Saw complete fixture output')
            self.assertFalse((root / 'false_pass.json').exists())

            completed = root / 'completed'
            capture_baseline.capture(completed, [sys.executable, '-c', 'print("scene")'])
            assessment = assess_baseline.assess(completed, root / 'review.json', 'pass',
                                                'tester', 'Verified expected fixture output')
            self.assertEqual(assessment['status'], 'pass')
            with self.assertRaises(FileExistsError):
                assess_baseline.assess(completed, root / 'review.json', 'pass',
                                       'tester', 'Duplicate assessment')
            (completed / 'stdout.log').write_text('changed')
            with self.assertRaisesRegex(ValueError, 'Artifact'):
                assess_baseline.assess(completed, root / 'tampered.json', 'pass',
                                       'tester', 'Verified expected fixture output')


if __name__ == '__main__':
    unittest.main()
