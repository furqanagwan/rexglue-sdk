import importlib.util
from pathlib import Path
import tempfile
import unittest

spec = importlib.util.spec_from_file_location('check_docs', Path(__file__).parents[1] / 'check_docs.py')
check_docs = importlib.util.module_from_spec(spec)
spec.loader.exec_module(check_docs)


class CheckDocsTests(unittest.TestCase):
    def test_repository_handoff_documents_resolve(self):
        self.assertEqual(check_docs.check(), [])

    def test_broken_links_and_paths_are_reported(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'docs').mkdir()
            (root / 'scripts').mkdir()
            (root / 'scripts' / 'real.py').write_text('')
            (root / 'README.md').write_text(
                '[ok](scripts/real.py) [bad](docs/missing.md) [web](https://example.com)\n'
                '`scripts/real.py` `scripts/gone.py` `src/xenia/upstream.cc` `tests/<name>.cpp`\n')
            problems = check_docs.check(root)
            self.assertEqual(len(problems), 2, problems)
            self.assertIn('broken link docs/missing.md', problems[0])
            self.assertIn('missing path scripts/gone.py', problems[1])


if __name__ == '__main__':
    unittest.main()
