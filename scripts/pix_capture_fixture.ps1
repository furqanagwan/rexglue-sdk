# PIX for Windows capture of the synthetic D3D12 fixture (RG-GDK-028).
#
#   pix_capture_fixture.ps1 -Tests <gpu_tests.exe> [-Output <dir>] [-PixTool <pixtool.exe>]
#
# Launches gpu_tests "[.pix-capture]" under PIX, which captures one draw and
# one resolve programmatically, then checks:
#   * the fixture passed (the resolved texel is the drawn color);
#   * the saved capture's event list has the host markers PIX decodes: the
#     queue's "Frame N, submission M" events, a "Draw: ..." region holding the
#     DrawInstanced, and a "Resolve" region; nothing enabled gpu_debug_markers,
#     so this also proves PIX is detected;
#   * a replay with the D3D12 debug layer reports no errors;
#   * rexruntime.dll, rexgpu-xenos.dll and gpu_tests.exe import no PIX DLL, so
#     normal builds need no PIX runtime.
# Output (default: a fresh temp directory) receives the .wpix capture,
# events.csv, the fixture log, the debug-layer output and capture.json with
# the capture hash, PIX version, adapter, driver and SDK commit.
#
# Exit 0 = pass, 1 = fail, 77 = skipped (PIX for Windows is not installed).
param(
    [Parameter(Mandatory)] [string] $Tests,
    [string] $Output = (Join-Path ([IO.Path]::GetTempPath()) 'rexglue_pix_capture'),
    [string] $PixTool
)
$ErrorActionPreference = 'Stop'
$script:failed = $false
function Pass([string] $what) { Write-Host "PASS $what" }
function Fail([string] $what) { Write-Host "FAIL $what"; $script:failed = $true }

if (-not $PixTool) {
    # PIX installs side by side under a version directory; take the newest.
    $PixTool = Get-ChildItem (Join-Path $env:ProgramFiles 'Microsoft PIX') -Directory -ErrorAction SilentlyContinue |
        Sort-Object { [version] $_.Name } -Descending |
        ForEach-Object { Join-Path $_.FullName 'pixtool.exe' } |
        Where-Object { Test-Path $_ } | Select-Object -First 1
}
if (-not $PixTool -or -not (Test-Path $PixTool)) {
    Write-Host 'SKIP PIX for Windows is not installed (winget install Microsoft.PIX)'
    exit 77
}
$pixVersion = Split-Path -Leaf (Split-Path -Parent $PixTool)
$Tests = (Resolve-Path $Tests).Path
$bin = Split-Path -Parent $Tests

if (Test-Path $Output) { Remove-Item -Recurse -Force $Output }
New-Item -ItemType Directory -Force $Output | Out-Null
$Output = (Resolve-Path $Output).Path

# pixtool parses its own command line: option values are quoted after '='.
function Invoke-PixTool([string] $arguments, [string] $log) {
    $info = New-Object System.Diagnostics.ProcessStartInfo $PixTool
    $info.Arguments = "--log-file=`"$(Join-Path $Output $log)`" $arguments"
    $info.UseShellExecute = $false
    $info.RedirectStandardOutput = $true
    $info.RedirectStandardError = $true
    $process = [System.Diagnostics.Process]::Start($info)
    $stderr = $process.StandardError.ReadToEndAsync()
    $stdout = $process.StandardOutput.ReadToEnd()
    $process.WaitForExit()
    return @{ ExitCode = $process.ExitCode; Output = $stdout + $stderr.Result }
}

# 1. Capture. The fixture runs in Output so its result file lands there.
$env:REXGLUE_GPU_FIXTURE_LOG = Join-Path $Output 'fixture.log'
$capture = Invoke-PixTool ("launch `"$Tests`" --command-line=`"[.pix-capture] -o fixture-result.txt`" " +
    "--working-directory=`"$Output`" programmatic-capture --until-exit save-all-captures `"$Output`"") 'pixtool-capture.log'
Remove-Item Env:REXGLUE_GPU_FIXTURE_LOG
$result = Join-Path $Output 'fixture-result.txt'
$resultText = if (Test-Path $result) { Get-Content -Raw $result } else { '' }
if ($capture.ExitCode -eq 0 -and $resultText -match 'All tests passed' -and $resultText -notmatch 'skipped') {
    Pass 'fixture ran under PIX and resolved the drawn color'
} else {
    Write-Host $capture.Output
    Write-Host $resultText
    Fail "fixture under PIX (pixtool exit $($capture.ExitCode))"
}
$wpix = @(Get-ChildItem $Output -Filter *.wpix)
if ($wpix.Count -ne 1) {
    Fail "expected one capture, found $($wpix.Count)"
    exit 1
}
$wpix = $wpix[0].FullName

# 2. Event list: the markers PIX decoded.
$events = Join-Path $Output 'events.csv'
$list = Invoke-PixTool "open-capture `"$wpix`" save-event-list `"$events`"" 'pixtool-events.log'
if ($list.ExitCode -ne 0 -or -not (Test-Path $events)) {
    Write-Host $list.Output
    Fail 'event list export'
    exit 1
}
# "Queue ID, Parent, Name, Global ID", with a space after each comma, which
# Import-Csv doesn't take as the start of a quoted name.
$rows = Get-Content $events | Select-Object -Skip 1 | ForEach-Object {
    if ($_ -match '^(\d+), (-?\d+), ("(?:[^"]|"")*"|[^,]*), ') {
        [pscustomobject] @{ Id = $Matches[1]; Parent = $Matches[2]
                            Name = $Matches[3].Trim('"').Replace('""', '"') }
    }
}
$draw = $rows | Where-Object { $_.Name -like 'Draw: primitive type*' } | Select-Object -First 1
$checks = [ordered] @{
    'queue submission events' = [bool] ($rows | Where-Object { $_.Parent -eq '-1' -and $_.Name -match '^Frame \d+, submission \d+$' })
    'Draw region' = [bool] $draw
    'DrawInstanced inside the Draw region' = [bool] ($draw -and ($rows | Where-Object { $_.Name -eq 'DrawInstanced' -and $_.Parent -eq $draw.Id }))
    'Resolve region' = [bool] ($rows | Where-Object { $_.Name -eq 'Resolve' })
    'no legacy (deprecated) marker format' = -not ($rows | Where-Object { $_.Name -match 'deprecated' })
}
foreach ($check in $checks.GetEnumerator()) {
    if ($check.Value) { Pass $check.Key } else { Fail $check.Key }
}

# 3. Replay under the D3D12 debug layer.
$replay = Invoke-PixTool "open-capture `"$wpix`" run-debug-layer" 'pixtool-debug-layer.log'
Set-Content -Path (Join-Path $Output 'debug-layer.txt') -Value $replay.Output
$messages = @($replay.Output -split "`r?`n" | Where-Object { $_ -match 'D3D12 (ERROR|CORRUPTION|WARNING)|pixtool error' })
if ($replay.ExitCode -eq 0 -and $messages.Count -eq 0) {
    Pass 'debug-layer replay reported no messages'
} else {
    Write-Host $replay.Output
    Fail "debug-layer replay (exit $($replay.ExitCode), $($messages.Count) messages)"
}

# 4. No PIX runtime dependency in the normal build.
$objdump = (Get-Command llvm-objdump -ErrorAction SilentlyContinue).Source
if (-not $objdump) { $objdump = Join-Path $env:ProgramFiles 'LLVM\bin\llvm-objdump.exe' }
$importCheck = 'not checked (llvm-objdump not found)'
if (Test-Path $objdump) {
    # Debug builds add a "d" suffix (rexruntimed.dll).
    $binaries = @(@('rexruntime*.dll', 'rexgpu-*.dll') |
        ForEach-Object { Get-ChildItem -Path $bin -Filter $_ | ForEach-Object FullName }) + $Tests
    $pixImports = @($binaries | Where-Object { (& $objdump -p $_) -match 'DLL Name: WinPix' })
    if ($pixImports.Count -eq 0) {
        $importCheck = "no PIX imports in $($binaries.Count) binaries"
        Pass $importCheck
    } else {
        $importCheck = "PIX imported by $($pixImports -join ', ')"
        Fail $importCheck
    }
} else {
    Write-Host "NOTE import check $importCheck"
}

# 5. Manifest.
$log = if (Test-Path (Join-Path $Output 'fixture.log')) { Get-Content (Join-Path $Output 'fixture.log') } else { @() }
$adapter = ($log | Select-String 'DXGI adapter: (.*)$' | Select-Object -First 1).Matches.Groups[1].Value
$driver = ($log | Select-String 'driver ([0-9.]+)' | Select-Object -First 1).Matches.Groups[1].Value
$commit = (& git -C $PSScriptRoot rev-parse HEAD 2>$null)
[ordered] @{
    schema_version = 1
    timestamp = (Get-Date).ToUniversalTime().ToString('o')
    fixture = 'gpu_tests [.pix-capture]'
    sdk_commit = if ($commit) { $commit } else { 'unknown' }
    pix_version = $pixVersion
    adapter = if ($adapter) { $adapter } else { 'unknown' }
    driver = if ($driver) { $driver } else { 'unknown' }
    capture = Split-Path -Leaf $wpix
    capture_sha256 = (Get-FileHash -Algorithm SHA256 $wpix).Hash.ToLower()
    events = $rows.Count
    import_check = $importCheck
    result = if ($script:failed) { 'fail' } else { 'pass' }
} | ConvertTo-Json | Set-Content (Join-Path $Output 'capture.json')
Write-Host "Capture and records in $Output"
if ($script:failed) { exit 1 }
exit 0
