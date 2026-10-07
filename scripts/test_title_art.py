"""Native title-art regression. Run in an x64 VS developer shell.

Uses original synthetic artwork only, then builds two external consumer EXEs
and checks their native icon resources, linker manifest and Shell extraction.
"""

import argparse
import ctypes
from ctypes import wintypes
import hashlib
import pathlib
import struct
import subprocess
import zlib


def run(*args, succeeds=True):
    result = subprocess.run([str(arg) for arg in args], capture_output=True, text=True)
    if (result.returncode == 0) != succeeds:
        raise RuntimeError(result.stdout + result.stderr)
    return result


def png():
    def chunk(kind, data):
        return struct.pack(">I", len(data)) + kind + data + struct.pack(">I", zlib.crc32(kind + data))

    # An opaque quadrants image; recognisable in Shell rather than a blank icon.
    rows = []
    for y in range(256):
        rows.append(b"\0" + b"".join(bytes((255 if x < 128 else 0, 255 if y < 128 else 0,
                                            96, 255)) for x in range(256)))
    return (b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", 256, 256, 8, 6, 0, 0, 0))
            + chunk(b"IDAT", zlib.compress(b"".join(rows))) + chunk(b"IEND", b""))


def check_native(exe):
    kernel = ctypes.WinDLL("kernel32", use_last_error=True)
    kernel.LoadLibraryExW.argtypes = [wintypes.LPCWSTR, wintypes.HANDLE, wintypes.DWORD]
    kernel.LoadLibraryExW.restype = wintypes.HMODULE
    kernel.FindResourceW.argtypes = [wintypes.HMODULE, ctypes.c_void_p, ctypes.c_void_p]
    kernel.FindResourceW.restype = ctypes.c_void_p
    kernel.FreeLibrary.argtypes = [wintypes.HMODULE]
    module = kernel.LoadLibraryExW(str(exe), None, 2)  # LOAD_LIBRARY_AS_DATAFILE
    if not module:
        raise ctypes.WinError(ctypes.get_last_error())
    try:
        assert kernel.FindResourceW(module, 1, 14), "RT_GROUP_ICON missing"
        assert kernel.FindResourceW(module, 1, 3), "RT_ICON missing"
        assert kernel.FindResourceW(module, 1, 24), "linker manifest lost"
    finally:
        kernel.FreeLibrary(module)
    shell = ctypes.WinDLL("shell32")
    shell.ExtractIconExW.argtypes = [wintypes.LPCWSTR, ctypes.c_int,
                                   ctypes.POINTER(wintypes.HICON), ctypes.POINTER(wintypes.HICON),
                                   wintypes.UINT]
    shell.ExtractIconExW.restype = wintypes.UINT
    user = ctypes.WinDLL("user32")
    user.DestroyIcon.argtypes = [wintypes.HICON]
    large, small = wintypes.HICON(), wintypes.HICON()
    try:
        # The API counts extracted handles: both requested sizes produce two.
        assert shell.ExtractIconExW(str(exe), 0, ctypes.byref(large), ctypes.byref(small), 1) == 2
        assert large.value and small.value, "Shell could not extract both icon sizes"
    finally:
        if large.value:
            user.DestroyIcon(large)
        if small.value:
            user.DestroyIcon(small)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rexglue", type=pathlib.Path, required=True)
    parser.add_argument("--work-dir", type=pathlib.Path, required=True)
    parser.add_argument("--helpers", type=pathlib.Path,
                        default=pathlib.Path(__file__).resolve().parents[1] / "cmake/rexglue_helpers.cmake")
    args = parser.parse_args()
    root = args.work_dir.resolve()
    root.mkdir(parents=True, exist_ok=True)
    image = root / "synthetic.png"
    image.write_bytes(png())
    art = root / "gdk"
    run(args.rexglue.resolve(), "title-art", "--image", image, "--output", art, "--force")
    expected = {"StoreLogo.png": (100, 100), "Square44x44Logo.png": (44, 44),
                "Square150x150Logo.png": (150, 150), "Square480x480Logo.png": (480, 480),
                "SplashScreen.png": (1920, 1080)}
    for name, size in expected.items():
        data = (art / name).read_bytes()
        assert data[:8] == b"\x89PNG\r\n\x1a\n"
        assert struct.unpack(">II", data[16:24]) == size
    sentinel = art / "MicrosoftGame.config"
    sentinel.write_text("Own title identity must be preserved", encoding="utf-8")
    before = {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in art.iterdir() if p.is_file()}
    run(args.rexglue.resolve(), "title-art", "--image", image, "--output", art, succeeds=False)
    after = {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in art.iterdir() if p.is_file()}
    assert before == after, "collision changed existing artwork or identity"
    run(args.rexglue.resolve(), "title-art", "--image", image, "--output", art, "--force")
    assert sentinel.read_text(encoding="utf-8") == "Own title identity must be preserved"
    (root / "main.cpp").write_text("int main() { return 0; }\n", encoding="utf-8")
    helpers = args.helpers.resolve().as_posix()
    (root / "CMakeLists.txt").write_text(
        f'cmake_minimum_required(VERSION 3.25)\nproject(TitleIconConsumer LANGUAGES CXX)\n'
        f'include("{helpers}")\n'
        'foreach(title base update)\n  add_executable(${title} main.cpp)\n'
        '  rexglue_embed_title_icon(${title} "${CMAKE_CURRENT_SOURCE_DIR}/gdk/Title.ico")\n'
        'endforeach()\n', encoding="utf-8")
    build = root / "build"
    run("cmake", "-S", root, "-B", build, "-G", "Ninja", "-DCMAKE_CXX_COMPILER=clang++")
    run("cmake", "--build", build)
    for title in ("base", "update"):
        check_native(build / (title + ".exe"))
    print("PASS: Shell extraction, ICON/GROUP_ICON/manifest, base and TU EXEs, image sizes and overwrite protection")


if __name__ == "__main__":
    main()
