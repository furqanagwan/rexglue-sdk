[CmdletBinding()]
param(
  [Parameter(Mandatory=$true)][string]$WorkDirectory,
  [Parameter(Mandatory=$true)][string]$Compiler,
  [Parameter(Mandatory=$true)][string]$ResourceCompiler,
  [ValidateSet('Debug','Release')][string]$Configuration = 'Release'
)
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
$work = [IO.Path]::GetFullPath($WorkDirectory)
[IO.Directory]::CreateDirectory($work) | Out-Null
Add-Type -AssemblyName System.Drawing
$bitmap = New-Object Drawing.Bitmap(64,64,([Drawing.Imaging.PixelFormat]::Format32bppArgb))
$graphics = [Drawing.Graphics]::FromImage($bitmap)
try {
  $graphics.Clear([Drawing.Color]::FromArgb(255,32,96,192))
  $bitmap.Save((Join-Path $work 'input.png'), [Drawing.Imaging.ImageFormat]::Png)
} finally { $graphics.Dispose(); $bitmap.Dispose() }
& (Join-Path $PSScriptRoot 'BuildTitleArtwork.ps1') -InputPng (Join-Path $work 'input.png') -OutputDirectory (Join-Path $work 'art')
foreach ($expected in @(@('StoreLogo.png',100,100),@('Square150x150Logo.png',150,150),@('Square44x44Logo.png',44,44),@('Square480x480Logo.png',480,480),@('SplashScreen.png',1920,1080))) {
  $image = [Drawing.Image]::FromFile((Join-Path $work ('art\'+$expected[0])))
  try {
    if ($image.Width -ne $expected[1] -or $image.Height -ne $expected[2] -or $image.PixelFormat -ne [Drawing.Imaging.PixelFormat]::Format32bppArgb) { throw "Wrong GDK image dimensions/format: $($expected[0])" }
  } finally { $image.Dispose() }
}
$ico = [IO.File]::ReadAllBytes((Join-Path $work 'art\title.ico'))
if ([BitConverter]::ToUInt16($ico,2) -ne 1 -or [BitConverter]::ToUInt16($ico,4) -ne 7) { throw 'Invalid ICO header' }
foreach ($i in 0..6) {
  $entry = 6 + 16*$i
  $length = [BitConverter]::ToUInt32($ico,$entry+8)
  $offset = [BitConverter]::ToUInt32($ico,$entry+12)
  if ($offset+$length -gt $ico.Length) { throw 'Invalid ICO frame extent' }
}
$helpers = (Join-Path $root 'cmake\rexglue_helpers.cmake').Replace('\','/')
$icon = (Join-Path $work 'art\title.ico').Replace('\','/')
$cmake = @"
cmake_minimum_required(VERSION 3.25)
project(title_icon_consumer LANGUAGES CXX)
include("$helpers")
add_executable(title_icon main.cpp)
rexglue_add_title_icon(title_icon ICON "$icon")
"@
[IO.File]::WriteAllText((Join-Path $work 'CMakeLists.txt'),$cmake)
[IO.File]::WriteAllText((Join-Path $work 'main.cpp'),'int main() { return 0; }')
& cmake -S $work -B (Join-Path $work 'build') -G Ninja "-DCMAKE_CXX_COMPILER=$Compiler" "-DCMAKE_RC_COMPILER=$ResourceCompiler" "-DCMAKE_BUILD_TYPE=$Configuration"
if ($LASTEXITCODE -ne 0) { throw 'Icon consumer configure failed' }
& cmake --build (Join-Path $work 'build')
if ($LASTEXITCODE -ne 0) { throw 'Icon consumer build failed' }
Add-Type @'
using System;
using System.Runtime.InteropServices;
public static class TitleIconShell {
  [DllImport("shell32.dll", CharSet=CharSet.Unicode)] public static extern uint ExtractIconEx(string file, int index, out IntPtr large, out IntPtr small, uint count);
  [DllImport("user32.dll")] public static extern bool DestroyIcon(IntPtr icon);
}
'@
$large = [IntPtr]::Zero
$small = [IntPtr]::Zero
try {
  $count = [TitleIconShell]::ExtractIconEx((Join-Path $work 'build\title_icon.exe'),0,[ref]$large,[ref]$small,1)
  if ($count -eq 0 -or $large -eq [IntPtr]::Zero -or $small -eq [IntPtr]::Zero) { throw 'Windows could not extract the linked EXE icon' }
  $extracted = [Drawing.Icon]::FromHandle($large).ToBitmap()
  try {
    $color = $extracted.GetPixel([int]($extracted.Width/2),[int]($extracted.Height/2))
    if ($color.R -ne 32 -or $color.G -ne 96 -or $color.B -ne 192) { throw 'Shell extracted a generic/different icon' }
  } finally { $extracted.Dispose() }
} finally {
  if ($large -ne [IntPtr]::Zero) { [TitleIconShell]::DestroyIcon($large) | Out-Null }
  if ($small -ne [IntPtr]::Zero) { [TitleIconShell]::DestroyIcon($small) | Out-Null }
}
Write-Output 'GDK PNG sizes/formats, ICO frame bounds, external consumer and Windows icon extraction passed.'
