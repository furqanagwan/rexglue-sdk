# Generates MicrosoftGame.config with `rexglue init gameconfig` and validates it
# against the installed GDK's GameConfigSchema.xsd (RG-GDK-022). Also proves the
# validator rejects a config the schema forbids, so a pass is meaningful.
#
#   validate_gameconfig.ps1 -Rexglue <rexglue.exe> -Schema <GameConfigSchema.xsd> -WorkDir <dir>
param(
    [Parameter(Mandatory)] [string] $Rexglue,
    [Parameter(Mandatory)] [string] $Schema,
    [Parameter(Mandatory)] [string] $WorkDir
)
$ErrorActionPreference = 'Stop'

function Test-Config([string] $path) {
    $settings = New-Object System.Xml.XmlReaderSettings
    $settings.ValidationType = [System.Xml.ValidationType]::Schema
    [void] $settings.Schemas.Add($null, $Schema)
    $errors = New-Object System.Collections.Generic.List[string]
    $settings.add_ValidationEventHandler({ param($s, $e) $errors.Add($e.Message) })
    $reader = [System.Xml.XmlReader]::Create($path, $settings)
    try { while ($reader.Read()) { } } finally { $reader.Close() }
    return , $errors
}

function Invoke-Generate([string] $dir, [string[]] $extra) {
    $arguments = @('init', 'gameconfig', '--output-dir', $dir,
        '--identity-name', 'ReXGlue.SchemaTest', '--publisher', 'CN=ReXGlue Tests, O=ReXGlue',
        '--display-name', 'Schema & <Test>', '--publisher-display-name', 'ReXGlue',
        '--executable', 'bin\schema_test.exe', '--description', 'Generated for validation') + $extra
    & $Rexglue @arguments | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "rexglue init gameconfig failed ($LASTEXITCODE): $extra" }
}

if (Test-Path $WorkDir) { Remove-Item -Recurse -Force $WorkDir }
$failed = $false

$cases = @(
    @{ Name = 'minimal'; Args = @() },
    @{ Name = 'with-ids'; Args = @('--title-id', '1A2B3C4D', '--msa-app-id', '000000004C27D3A1',
            '--store-id', '9NBLGGH4R315', '--package-version', '2.1.0.7') }
)
foreach ($case in $cases) {
    $dir = Join-Path $WorkDir $case.Name
    Invoke-Generate $dir $case.Args
    $config = Join-Path $dir 'MicrosoftGame.config'
    $errors = Test-Config $config
    if ($errors.Count -eq 0) {
        Write-Output "PASS $($case.Name): schema-valid"
    } else {
        $failed = $true
        Write-Output "FAIL $($case.Name): $($errors -join '; ')"
    }
    foreach ($png in 'StoreLogo', 'Square150x150Logo', 'Square44x44Logo', 'Square480x480Logo',
        'SplashScreen') {
        if (-not (Test-Path (Join-Path $dir "$png.png"))) {
            $failed = $true
            Write-Output "FAIL $($case.Name): missing $png.png"
        }
    }
}

# No invented service IDs in the minimal config.
$minimal = Get-Content -Raw (Join-Path $WorkDir 'minimal\MicrosoftGame.config')
foreach ($tag in 'TitleId', 'MSAAppId', 'StoreId', 'RequiresXboxLive') {
    if ($minimal -match "<$tag") {
        $failed = $true
        Write-Output "FAIL minimal: contains $tag"
    }
}

# A second run with different identity must not replace the config silently.
& $Rexglue init gameconfig --output-dir (Join-Path $WorkDir 'minimal') `
    --identity-name 'Other.Name' --publisher 'CN=Other' --display-name 'Other' `
    --publisher-display-name 'Other' --executable 'other.exe' | Out-Null
if ($LASTEXITCODE -eq 0) {
    $failed = $true
    Write-Output 'FAIL overwrite: a differing config was replaced without --force'
} else {
    Write-Output 'PASS overwrite: refused without --force'
}

# The validator itself must reject what the schema forbids.
$bad = Join-Path $WorkDir 'bad.config'
$minimal -replace 'Version="1.0.0.0"', 'Version="1.0"' | Set-Content -Encoding utf8 $bad
if ((Test-Config $bad).Count -gt 0) {
    Write-Output 'PASS negative: a bad Version is rejected by the schema'
} else {
    $failed = $true
    Write-Output 'FAIL negative: the schema accepted Version="1.0"'
}

if ($failed) { exit 1 }
exit 0
