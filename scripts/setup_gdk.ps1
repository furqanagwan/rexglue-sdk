[CmdletBinding()]
param(
    [string] $Destination = (Join-Path $env:TEMP 'rexglue-gdk-260404'),
    [switch] $InstalledOnly
)

$ErrorActionPreference = 'Stop'
$edition = '260404'

function Test-GdkRoot([string] $Root) {
    if (-not $Root) { return $false }
    $header = Join-Path $Root 'windows/include/grdk.h'
    if (-not (Test-Path -LiteralPath $header -PathType Leaf)) { return $false }
    $selected = Select-String -LiteralPath $header -Pattern '^#define _GRDK_EDITION\s+260404\s*$'
    if (-not $selected) { return $false }
    foreach ($required in @('windows/include/XGameRuntime.h', 'windows/include/GameInput.h',
                             'windows/lib/x64/xgameruntime.lib')) {
        if (-not (Test-Path -LiteralPath (Join-Path $Root $required) -PathType Leaf)) { return $false }
    }
    return $true
}

if (Test-GdkRoot $env:GameDKCoreLatest) {
    (Resolve-Path -LiteralPath $env:GameDKCoreLatest).Path
    return
}
if ($InstalledOnly) {
    throw "An installed PC GDK $edition is required; set GameDKCoreLatest to its edition directory."
}

# Microsoft's public PC payload, pinned by release asset digest. Nothing from
# this payload is committed or added to SDK release artifacts.
$url = 'https://github.com/microsoft/GDK/releases/download/April-2026-Update-4-v2604.4.7897/GDK_2604.4.7897.zip'
$expectedHash = '3da3f104fa66bb3ee1299b3dc8c0a3ecac1cb56a4cf04136b8595942272017eb'
$taskRoot = [System.IO.Path]::GetFullPath($Destination)
$archive = Join-Path $taskRoot 'GDK_2604.4.7897.zip'
$payload = Join-Path $taskRoot 'payload'
$extracted = Join-Path $taskRoot 'extracted'
[void] (New-Item -ItemType Directory -Path $taskRoot -Force)
if (-not (Test-Path -LiteralPath $archive -PathType Leaf)) {
    Write-Host "Downloading the pinned public PC GDK $edition payload."
    Invoke-WebRequest -Uri $url -OutFile $archive
}
if ((Get-FileHash -LiteralPath $archive -Algorithm SHA256).Hash.ToLowerInvariant() -ne $expectedHash) {
    throw "GDK archive digest mismatch: $archive"
}
Expand-Archive -LiteralPath $archive -DestinationPath $payload -Force
$extractScripts = @(Get-ChildItem -LiteralPath $payload -Filter 'ExtractXboxOneDKs.ps1' -File -Recurse)
if ($extractScripts.Count -ne 1) { throw 'The pinned GDK payload must contain one extraction script.' }
& powershell -NoProfile -ExecutionPolicy Bypass -File $extractScripts[0].FullName `
    -SourcePath $payload -TargetDirectory $extracted | Out-Host
if ($LASTEXITCODE -ne 0) { throw "GDK extraction failed with exit code $LASTEXITCODE." }
$roots = @(Get-ChildItem -LiteralPath $extracted -Filter 'grdk.h' -File -Recurse |
    ForEach-Object { $_.Directory.Parent.Parent.FullName } |
    Where-Object { Test-GdkRoot $_ })
if ($roots.Count -ne 1) { throw "The extracted payload must contain one PC GDK $edition edition." }
$roots[0]
