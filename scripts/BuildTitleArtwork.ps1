# Windows shell ICO and GDK ShellVisuals from caller-owned title artwork.
[CmdletBinding()]
param(
  [Parameter(Mandatory=$true)][string]$InputPng,
  [Parameter(Mandatory=$true)][string]$OutputDirectory
)
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
$sourcePath = (Resolve-Path -LiteralPath $InputPng).Path
$output = [IO.Path]::GetFullPath($OutputDirectory)
[IO.Directory]::CreateDirectory($output) | Out-Null
$source = [Drawing.Image]::FromFile($sourcePath)
function RenderPng([int]$Width, [int]$Height) {
  $bitmap = New-Object Drawing.Bitmap($Width, $Height, ([Drawing.Imaging.PixelFormat]::Format32bppArgb))
  $graphics = [Drawing.Graphics]::FromImage($bitmap)
  $stream = New-Object IO.MemoryStream
  try {
    $graphics.Clear([Drawing.Color]::Transparent)
    $graphics.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
    $graphics.PixelOffsetMode = [Drawing.Drawing2D.PixelOffsetMode]::HighQuality
    $scale = [Math]::Min($Width / $source.Width, $Height / $source.Height)
    $w = [Math]::Max(1, [int][Math]::Round($source.Width * $scale))
    $h = [Math]::Max(1, [int][Math]::Round($source.Height * $scale))
    $rectangle = New-Object Drawing.Rectangle(([int](($Width-$w)/2)), ([int](($Height-$h)/2)), $w, $h)
    $graphics.DrawImage($source, $rectangle)
    $bitmap.Save($stream, [Drawing.Imaging.ImageFormat]::Png)
    return ,$stream.ToArray()
  } finally {
    $stream.Dispose()
    $graphics.Dispose()
    $bitmap.Dispose()
  }
}
try {
  $sizes = @(16,24,32,48,64,128,256)
  $frames = @{}
  foreach ($size in $sizes) { $frames[$size] = RenderPng $size $size }
  $stream = New-Object IO.MemoryStream
  $writer = New-Object IO.BinaryWriter($stream)
  try {
    $writer.Write([uint16]0)
    $writer.Write([uint16]1)
    $writer.Write([uint16]$sizes.Count)
    $offset = 6 + 16 * $sizes.Count
    foreach ($size in $sizes) {
      $dimension = if ($size -eq 256) { 0 } else { $size }
      $writer.Write([byte]$dimension)
      $writer.Write([byte]$dimension)
      $writer.Write([byte]0)
      $writer.Write([byte]0)
      $writer.Write([uint16]1)
      $writer.Write([uint16]32)
      $writer.Write([uint32]$frames[$size].Length)
      $writer.Write([uint32]$offset)
      $offset += $frames[$size].Length
    }
    foreach ($size in $sizes) { $writer.Write([byte[]]$frames[$size]) }
    [IO.File]::WriteAllBytes((Join-Path $output 'title.ico'), $stream.ToArray())
  } finally { $writer.Dispose(); $stream.Dispose() }
  foreach ($image in @(
    @('StoreLogo.png',100,100), @('Square150x150Logo.png',150,150),
    @('Square44x44Logo.png',44,44), @('Square480x480Logo.png',480,480),
    @('SplashScreen.png',1920,1080)
  )) {
    [IO.File]::WriteAllBytes((Join-Path $output $image[0]), (RenderPng $image[1] $image[2]))
  }
} finally { $source.Dispose() }
Write-Output "Title artwork written to $output"
