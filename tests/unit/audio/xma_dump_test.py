"""Synthetic XMAD format checks; contains no captured title bytes."""
import struct
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[3] / "scripts"))
from xma_dump import load


class DumpFormat(unittest.TestCase):
    def read(self, content):
        with tempfile.TemporaryDirectory(prefix="rex-xmad-") as root:
            path = Path(root) / "synthetic.bin"
            path.write_bytes(content)
            return load(path)

    def test_two_buffers_and_previous_snapshot(self):
        header = b"XMAD" + bytes(64)
        for count in (2, 3):
            words, buffers = self.read(header + (struct.pack("<I", 2048) + bytes(2048)) * count)
            self.assertEqual(words, (0,) * 16)
            self.assertEqual([len(b) for b in buffers], [2048] * count)

    def test_empty_valid_buffers(self):
        self.assertEqual(self.read(b"XMAD" + bytes(72))[1], [b"", b""])

    def test_every_truncated_header(self):
        valid = b"XMAD" + bytes(72)
        for size in range(len(valid)):
            with self.subTest(size=size), self.assertRaises(ValueError):
                self.read(valid[:size])

    def test_bad_lengths_and_counts(self):
        for content in (b"XXXX" + bytes(72), b"XMAD" + bytes(64) + struct.pack("<I", 0xFFFFFFFF),
                        b"XMAD" + bytes(64) + struct.pack("<I", 2048) + bytes(1024),
                        b"XMAD" + bytes(64) + struct.pack("<I", 1) + bytes(5),
                        b"XMAD" + bytes(80)):
            with self.subTest(size=len(content)), self.assertRaises(ValueError):
                self.read(content)


if __name__ == "__main__":
    unittest.main()
