#!/usr/bin/env python3
"""Builds the precompiled Direct3D 12 DXBC shaders in src/graphics/shaders.

The sources are xenia-canary's XeSL/HLSL shaders pinned in
docs/upstream-tracking.md, plus local shaders such as resolve_downscale. Each
`name.<stage>.xesl` or `name.<stage>.hlsl` becomes
`bytecode/d3d12_5_1/name_<stage>.h` with the same FXC arguments as Canary's
`xenia-build buildshaders`, then goes through clang-format.

Usage:
  python scripts/build_shaders.py [--check] [name ...]

--check compiles into a temporary directory and fails if any bytecode differs
from the checked-in headers. Names select shaders by identifier (for example
resolve_full_32bpp_cs); all shaders are built when none are given.
"""

import argparse
import glob
import os
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SHADER_DIR = os.path.join(ROOT, 'src', 'graphics', 'shaders')
BYTECODE_DIR = os.path.join(SHADER_DIR, 'bytecode', 'd3d12_5_1')
STAGES = ('vs', 'hs', 'ds', 'gs', 'ps', 'cs')


def find_fxc():
  program_files = os.environ.get('ProgramFiles(x86)') or os.environ.get('ProgramFiles')
  if not program_files:
    return None
  paths = glob.glob(os.path.join(program_files, 'Windows Kits', '10', 'bin', '*', 'x64', 'fxc.exe'))
  version = lambda p: [int(x) for x in re.findall(r'\d+', p.split(os.sep)[-3])]
  return max(paths, key=version) if paths else None


def find_clang_format():
  path = shutil.which('clang-format')
  if path:
    return path
  path = os.path.join(os.environ.get('ProgramFiles', ''), 'LLVM', 'bin', 'clang-format.exe')
  return path if os.path.exists(path) else None


def shaders():
  for name in sorted(os.listdir(SHADER_DIR)):
    base, ext = os.path.splitext(name)
    if ext not in ('.xesl', '.hlsl'):
      continue
    stage = base.rpartition('.')[2]
    if stage in STAGES:
      yield name, base.replace('.', '_'), stage


def bytecode(path):
  with open(path, encoding='utf-8') as f:
    text = f.read()
  return [int(x) for x in re.findall(r'\d+', text[text.index('[] =') + 4:])]


def compile_shader(fxc, name, identifier, stage, out_path):
  # Canary doesn't pass /WX: it overrides #pragma warning, and FXC reports a
  # false uninitialized variable warning for early returns in some shaders.
  result = subprocess.run(
      [fxc, '/D', 'SHADING_LANGUAGE_HLSL_XE=1', '/Fh', out_path, '/T', stage + '_5_1', '/Vn',
       identifier, '/nologo', name],
      cwd=SHADER_DIR, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE, text=True)
  if result.returncode:
    sys.stderr.write(result.stderr)
    return False
  # FXC writes CRLF and trailing spaces; the repository keeps LF.
  with open(out_path, encoding='utf-8') as f:
    lines = [line.rstrip() for line in f.read().splitlines()]
  with open(out_path, 'w', encoding='utf-8', newline='\n') as f:
    f.write('\n'.join(lines) + '\n')
  return True


def main():
  parser = argparse.ArgumentParser(description=__doc__.split('\n')[0])
  parser.add_argument('--check', action='store_true',
                      help='compare with the checked-in bytecode instead of writing it')
  parser.add_argument('names', nargs='*', help='shader identifiers to build')
  args = parser.parse_args()

  fxc = find_fxc()
  if not fxc:
    print('ERROR: FXC not found; install the Windows 10/11 SDK', file=sys.stderr)
    return 1
  clang_format = None
  if not args.check:
    clang_format = find_clang_format()
    if not clang_format:
      print('ERROR: clang-format not found', file=sys.stderr)
      return 1

  selected = [s for s in shaders() if not args.names or s[1] in args.names]
  unknown = set(args.names) - {s[1] for s in selected}
  if unknown:
    print('ERROR: unknown shaders: ' + ', '.join(sorted(unknown)), file=sys.stderr)
    return 1

  failed = []
  with tempfile.TemporaryDirectory() as temp_dir:
    for name, identifier, stage in selected:
      out_path = os.path.join(temp_dir, identifier + '.h')
      if not compile_shader(fxc, name, identifier, stage, out_path):
        failed.append(identifier)
        continue
      checked_in = os.path.join(BYTECODE_DIR, identifier + '.h')
      if args.check:
        if not os.path.exists(checked_in) or bytecode(out_path) != bytecode(checked_in):
          failed.append(identifier)
        continue
      if os.path.exists(checked_in) and bytecode(out_path) == bytecode(checked_in):
        # Keep the header as is, only the comments could differ.
        continue
      subprocess.run([clang_format, '-i', '--style=file:' + os.path.join(ROOT, '.clang-format'),
                      out_path], check=True)
      shutil.copyfile(out_path, checked_in)
      print('- ' + name)

  print('%d of %d shaders %s with %s' % (len(selected) - len(failed), len(selected),
                                         'match' if args.check else 'built', fxc))
  if failed:
    print('FAILED: ' + ', '.join(failed), file=sys.stderr)
    return 1
  return 0


if __name__ == '__main__':
  sys.exit(main())
