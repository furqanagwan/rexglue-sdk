"""The title compatibility profile schema accepts ADR-009's example and rejects
the build-time errors its design lists (RG-GDK-013)."""
import json
from pathlib import Path
import tomllib
import unittest

import jsonschema

ROOT = Path(__file__).resolve().parents[2]
SCHEMA = json.loads((ROOT / 'docs' / 'compat-profile.schema.json').read_text(encoding='utf-8'))

VALID = '''
schema_version = 1

[[module]]
title_id = "415607FF"
xex_sha256 = "0000000000000000000000000000000000000000000000000000000000000000"
version = "1.0"
fixes = ["readback_resolve_full"]

[[module]]
title_id = "415607FF"
xex_sha256 = "1111111111111111111111111111111111111111111111111111111111111111"
disable = ["some_default_fix"]

[fix.readback_resolve_full]
evidence = "baseline run rg0xx; resolve readback test"
added = "2026-09-27"
'''


def errors(text):
    validator = jsonschema.Draft202012Validator(SCHEMA)
    return [error.message for error in validator.iter_errors(tomllib.loads(text))]


class CompatProfileSchemaTests(unittest.TestCase):
    def test_schema_is_a_valid_draft_2020_12_schema(self):
        jsonschema.Draft202012Validator.check_schema(SCHEMA)

    def test_adr_example_is_valid(self):
        self.assertEqual(errors(VALID), [])

    def test_build_time_errors_are_rejected(self):
        cases = {
            'unknown top-level key': VALID + 'global = true\n',
            'unknown module key': VALID.replace('version = "1.0"', 'region = "PAL"'),
            'unsupported schema version': VALID.replace('schema_version = 1', 'schema_version = 2'),
            'lowercase title id': VALID.replace('"415607FF"', '"415607ff"', 1),
            'short hash': VALID.replace('0' * 64, '0' * 63),
            'no hash binding': VALID.replace(
                'xex_sha256 = "' + '0' * 64 + '"\n', ''),
            'fix listed twice': VALID.replace('["readback_resolve_full"]',
                                              '["readback_resolve_full", "readback_resolve_full"]'),
            'fix without evidence': VALID.replace(
                'evidence = "baseline run rg0xx; resolve readback test"\n', ''),
            'fix name with capitals': VALID.replace('["readback_resolve_full"]', '["ReadbackFull"]'),
        }
        for name, text in cases.items():
            with self.subTest(name):
                self.assertNotEqual(errors(text), [], name)


if __name__ == '__main__':
    unittest.main()
