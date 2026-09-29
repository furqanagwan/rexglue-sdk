"""Inspect private XMAD captures from --xma_dump_dir; no game data is bundled."""
# Copyright (c) 2026 ReXGlue contributors. BSD-3-Clause; see LICENSE.
import struct
import sys


def bits(word, lo, n):
    return (word >> lo) & ((1 << n) - 1)


def load(path):
    with open(path, 'rb') as source:
        b = source.read(3 * 4095 * 2048 + 81)
    if len(b) < 76 or b[:4] != b'XMAD':
        raise ValueError('not a complete XMAD capture')
    words = struct.unpack('>16I', b[4:68])
    pos, bufs = 68, []
    while pos < len(b):
        if len(bufs) == 3 or pos + 4 > len(b):
            raise ValueError('invalid buffer table')
        (size,) = struct.unpack_from('<I', b, pos)
        pos += 4
        if size % 2048 or size > 4095 * 2048 or size > len(b) - pos:
            raise ValueError('invalid or truncated packet buffer')
        bufs.append(b[pos:pos + size])
        pos += size
    if len(bufs) not in (2, 3):
        raise ValueError('expected two input buffers and optional previous buffer')
    return words, bufs


def context(words):
    w0, w1, w2, w3, w4 = words[:5]
    return {
        'in0_packets': bits(w0, 0, 12), 'loop_count': bits(w0, 12, 8),
        'in0_valid': bits(w0, 20, 1), 'in1_valid': bits(w0, 21, 1),
        'out_blocks': bits(w0, 22, 5), 'out_write': bits(w0, 27, 5),
        'in1_packets': bits(w1, 0, 12), 'loop_subframe_end': bits(w1, 12, 2),
        'loop_subframe_skip': bits(w1, 17, 3), 'subframe_decode_count': bits(w1, 20, 4),
        'out_padding': bits(w1, 24, 3), 'sample_rate': bits(w1, 27, 2),
        'is_stereo': bits(w1, 29, 1), 'out_valid': bits(w1, 31, 1),
        'read_offset': bits(w2, 0, 26), 'error_status': bits(w2, 26, 5),
        'loop_start': bits(w3, 0, 26), 'loop_end': bits(w4, 0, 26),
        'current_buffer': bits(w4, 31, 1),
        'in0_ptr': words[5], 'in1_ptr': words[6],
    }


def packets(buf):
    for i in range(len(buf) // 2048):
        p = buf[i * 2048:(i + 1) * 2048]
        frames = p[0] >> 2
        offset = (((p[0] & 3) << 13) | (p[1] << 5) | (p[2] >> 3)) + 32
        yield i, frames, offset, p[2] & 7, p[3], p


def frame_sizes(p, first):
    """Frame lengths inside one packet, starting at the first frame offset."""
    data = int.from_bytes(p, 'big')
    total = 2048 * 8
    pos = first
    out = []
    while pos + 15 <= total:
        size = (data >> (total - pos - 15)) & 0x7FFF
        out.append(size)
        if size == 0 or size == 0x7FFF or pos + size > total:
            break
        # The last bit of a frame says whether another frame follows.
        more = (data >> (total - pos - size)) & 1
        pos += size
        if not more:
            break
    return out


if __name__ == '__main__':
    for path in sys.argv[1:]:
        words, bufs = load(path)
        c = context(words)
        print(path)
        print('  ' + ' '.join(f'{k}={v:#x}' if k.endswith('ptr') else f'{k}={v}' for k, v in c.items()))
        for n, buf in enumerate(bufs):
            print(f'  buffer {n}: {len(buf)} bytes')
            for i, frames, offset, meta, skip, p in packets(buf):
                sizes = frame_sizes(p, offset) if offset < 2048 * 8 else []
                print(f'    packet {i:3}: frames {frames:2} first {offset:5} meta {meta} skip {skip:3} '
                      f'sizes {sizes[:8]}{"..." if len(sizes) > 8 else ""} head {p[:8].hex()}')
