# Gaming Runtime deployment smoke for a minimal SDK title (RG-GDK-022).
#
#   gdk_smoke.ps1 -Title <gdk_smoke_title.exe> -Rexglue <rexglue.exe>
#                 [-Mode Unpackaged|Registered|Installed]
#
# Every mode copies the built title into a fresh loose layout and writes its
# MicrosoftGame.config and images with `rexglue init gameconfig`, as a title
# project would. Titles run with a system-only PATH, as on a clean machine.
#
# Unpackaged (CTest gdk.smoke_unpackaged):
#   * the title runs: the runtime is ready, the process has no package
#     identity and uninitializes cleanly;
#   * without rexruntime.dll, or with a foreign DLL in its place, Windows
#     refuses to start the title (STATUS_DLL_NOT_FOUND,
#     STATUS_ENTRYPOINT_NOT_FOUND) rather than run it half-loaded;
#   * with a malformed MicrosoftGame.config the unpackaged runtime reports
#     0x8924010B and the title stops.
# Registered (CTest gdk.smoke_registered): `wdapp register` of the layout.
# Installed (CTest gdk.smoke_installed): `makepkg genmap` + `makepkg pack /pc`
#   to an MSIXVC, then `wdapp install`.
# Both deployment modes launch with `wdapp launch <AUMID>`, require the
# package's identity in the process, then remove the package, deploy it again
# and require the save counter the title keeps under Saved Games (where ReXApp
# keeps user data, outside the package) to carry over, and finally remove it.
# They change the user's installed apps, so they run only when
# REXGLUE_GDK_DEPLOY_SMOKE=1 (Developer Mode is needed to register).
#
# Exit 0 = pass, 1 = fail, 77 = skipped.
param(
    [Parameter(Mandatory)] [string] $Title,
    [Parameter(Mandatory)] [string] $Rexglue,
    [ValidateSet('Unpackaged', 'Registered', 'Installed')] [string] $Mode = 'Unpackaged'
)
$ErrorActionPreference = 'Stop'

$identityName = 'ReXGlue.GdkSmoke'
$exeName = Split-Path -Leaf $Title
$gdkBin = Join-Path ${env:ProgramFiles(x86)} 'Microsoft GDK\bin'
$wdapp = Join-Path $gdkBin 'wdapp.exe'
$makepkg = Join-Path $gdkBin 'makepkg.exe'
$savedGames = (New-Object -ComObject Shell.Application).Namespace('shell:SavedGames').Self.Path
$saveDir = Join-Path $savedGames 'rexglue_gdk_smoke'
$work = Join-Path ([IO.Path]::GetTempPath()) "rexglue_gdk_smoke_$($Mode.ToLower())"
$script:failed = $false

function Pass([string] $what) { Write-Host "PASS $what" }
function Fail([string] $what) { Write-Host "FAIL $what"; $script:failed = $true }

# Loader and CRT failures must not leave dialogs on the desktop.
Add-Type -Namespace RexSmoke -Name Native -MemberDefinition @'
[System.Runtime.InteropServices.DllImport("kernel32.dll")]
public static extern uint SetErrorMode(uint mode);
'@
[void] [RexSmoke.Native]::SetErrorMode(0x0001 -bor 0x0002 -bor 0x8000)

function Read-Report([string] $path) {
    $report = @{}
    if (Test-Path $path) {
        foreach ($line in Get-Content $path) {
            $key, $value = $line -split ': ', 2
            $report[$key] = $value
        }
    }
    return $report
}

function New-Layout([string] $to, [switch] $NoConfig) {
    if (Test-Path $to) { Remove-Item -Recurse -Force $to }
    New-Item -ItemType Directory -Force $to | Out-Null
    Get-ChildItem (Split-Path -Parent $Title) -File |
        Where-Object { $_.Extension -notin '.png', '.pdb' -and
            $_.Name -notin 'MicrosoftGame.config', 'gdk_smoke_result.txt' } |
        Copy-Item -Destination $to
    if ($NoConfig) { return }
    & $Rexglue init gameconfig --output-dir $to --identity-name $identityName `
        --publisher 'CN=ReXGlue Smoke' --display-name 'ReXGlue GDK smoke' `
        --publisher-display-name 'ReXGlue' --executable $exeName | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "rexglue init gameconfig failed ($LASTEXITCODE)" }
}

function Invoke-Title([string] $exe) {
    $report = Join-Path (Split-Path -Parent $exe) 'gdk_smoke_result.txt'
    Remove-Item -Force -ErrorAction SilentlyContinue $report
    # CreateProcess, not ShellExecute, so the child inherits the error mode.
    $info = New-Object System.Diagnostics.ProcessStartInfo $exe
    $info.UseShellExecute = $false
    $info.WorkingDirectory = Split-Path -Parent $exe
    # An SDK installed elsewhere on PATH must not stand in for the layout's DLLs.
    $info.EnvironmentVariables['PATH'] = "$env:SystemRoot\System32;$env:SystemRoot"
    $process = [System.Diagnostics.Process]::Start($info)
    if (-not $process.WaitForExit(90000)) {
        $process.Kill()
        return @{ exit = 'timeout'; report = @{} }
    }
    return @{ exit = $process.ExitCode; report = (Read-Report $report) }
}

function Test-Unpackaged {
    try {
        New-Layout "$work\title"
        $run = Invoke-Title "$work\title\$exeName"
        $r = $run.report
        if ($run.exit -eq 0 -and $r.runtime -eq 'ready' -and $r.appx -eq 'none' -and
            $r.packaged -eq 'no' -and $r.uninitialized -eq 'yes') {
            Pass 'unpackaged launch: runtime ready, no package identity, clean uninitialize'
        } else {
            Fail "unpackaged launch: exit $($run.exit), report $($r | ConvertTo-Json -Compress)"
        }

        New-Layout "$work\nodll"
        Remove-Item "$work\nodll\rexruntime*.dll"
        $run = Invoke-Title "$work\nodll\$exeName"
        if ($run.exit -eq -1073741515 -and $run.report.Count -eq 0) {
            Pass 'missing rexruntime.dll: the loader refuses to start the title (0xC0000135)'
        } else {
            Fail "missing rexruntime.dll: exit $($run.exit)"
        }

        # A rexruntime.dll from something else lacks the title's imports.
        New-Layout "$work\wrongdll"
        $dll = Get-ChildItem "$work\wrongdll\rexruntime*.dll" | Select-Object -First 1
        Copy-Item -Force "$env:SystemRoot\System32\version.dll" $dll.FullName
        $run = Invoke-Title "$work\wrongdll\$exeName"
        if ($run.exit -eq -1073741511 -and $run.report.Count -eq 0) {
            Pass 'mismatched rexruntime.dll: the loader refuses to start the title (0xC0000139)'
        } else {
            Fail "mismatched rexruntime.dll: exit $($run.exit)"
        }

        # An unpackaged XGameRuntimeInitialize reads the config beside the exe.
        New-Layout "$work\badconfig" -NoConfig
        Set-Content -Encoding utf8 "$work\badconfig\MicrosoftGame.config" '<Game configVersion="1"><Identity'
        $run = Invoke-Title "$work\badconfig\$exeName"
        if ($run.exit -eq 1 -and $run.report.runtime -eq 'config error' -and
            $run.report.message -match '0x8924010B') {
            Pass 'malformed MicrosoftGame.config: config error 0x8924010B, the title stops'
        } else {
            Fail ("malformed MicrosoftGame.config: exit $($run.exit), report " +
                ($run.report | ConvertTo-Json -Compress))
        }
    } finally {
        Remove-Item -Recurse -Force -ErrorAction SilentlyContinue $work, $saveDir
    }
}

function Remove-Smoke {
    foreach ($package in Get-AppxPackage -Name $identityName) {
        $verb = if ($Mode -eq 'Installed') { 'uninstall' } else { 'unregister' }
        & $wdapp $verb $package.PackageFullName | Out-Null
    }
    return -not (Get-AppxPackage -Name $identityName)
}

function Deploy-And-Launch([string] $label, [string] $source) {
    if ($Mode -eq 'Installed') {
        & $wdapp install $source | ForEach-Object { Write-Host "  wdapp: $_" }
    } else {
        & $wdapp register $source | ForEach-Object { Write-Host "  wdapp: $_" }
    }
    if ($LASTEXITCODE -ne 0) { Fail "$label deploy: wdapp exit $LASTEXITCODE"; return $null }
    $package = Get-AppxPackage -Name $identityName
    if (-not $package) { Fail "$label deploy: no package $identityName"; return $null }
    Pass "$label deploy: $($package.PackageFullName) at $($package.InstallLocation)"

    # The title reports beside itself, or beside its save when the installed
    # package's folder is read-only.
    $reports = @((Join-Path $package.InstallLocation 'gdk_smoke_result.txt'),
        (Join-Path $saveDir 'gdk_smoke_result.txt'))
    $reports | ForEach-Object { Remove-Item -Force -ErrorAction SilentlyContinue $_ }
    $aumid = "$($package.PackageFamilyName)!Game"
    & $wdapp launch $aumid | ForEach-Object { Write-Host "  wdapp: $_" }
    $deadline = (Get-Date).AddSeconds(90)
    $r = @{}
    while ((Get-Date) -lt $deadline -and -not $r.exit) {
        Start-Sleep -Milliseconds 250
        foreach ($path in $reports) {
            $candidate = Read-Report $path
            if ($candidate.exit) { $r = $candidate }
        }
    }
    if ($r.runtime -eq 'ready' -and $r.appx -eq $package.PackageFullName -and
        $r.uninitialized -eq 'yes' -and $r.exit -eq '0') {
        Pass ("$label launch ${aumid}: runtime ready in package $($r.appx); GDK " +
            "installation identity: $($r.packaged) $($r.package)")
    } else {
        Fail "$label launch ${aumid}: report $($r | ConvertTo-Json -Compress)"
    }
    return $r
}

function Test-Deployment {
    if ($env:REXGLUE_GDK_DEPLOY_SMOKE -ne '1') {
        Write-Host "SKIP set REXGLUE_GDK_DEPLOY_SMOKE=1 to deploy a test app ($Mode)"
        exit 77
    }
    if (-not (Remove-Smoke)) { Fail 'a previous smoke package could not be removed'; return }
    Remove-Item -Recurse -Force -ErrorAction SilentlyContinue $saveDir
    try {
        New-Layout "$work\layout"
        $source = "$work\layout"
        if ($Mode -eq 'Installed') {
            & $makepkg genmap /f "$work\layout.xml" /d "$work\layout" | Out-Null
            if ($LASTEXITCODE -ne 0) { Fail "makepkg genmap: exit $LASTEXITCODE"; return }
            New-Item -ItemType Directory -Force "$work\out" | Out-Null
            # makepkg reports on stderr; keep it as text rather than stopping.
            $ErrorActionPreference = 'Continue'
            $output = & $makepkg pack /f "$work\layout.xml" /d "$work\layout" /pd "$work\out" /pc /loggable 2>&1 |
                ForEach-Object { "$_" }
            $exit = $LASTEXITCODE
            $ErrorActionPreference = 'Stop'
            $output | Where-Object { $_ -match '^Failure' } | ForEach-Object { Write-Host "  validator: $_" }
            $source = Get-ChildItem "$work\out\*.msixvc" | Select-Object -First 1 -ExpandProperty FullName
            if ($exit -ne 0 -or -not $source) { Fail "makepkg pack /pc: exit $exit"; return }
            $hash = (Get-FileHash -Algorithm SHA256 $source).Hash
            Pass "makepkg pack /pc: $(Split-Path -Leaf $source) ($((Get-Item $source).Length) bytes, SHA-256 $hash)"
        }

        $first = Deploy-And-Launch 'first' $source
        if (Remove-Smoke) { Pass 'remove: package gone' } else { Fail 'remove: package still present' }
        $second = Deploy-And-Launch 'redeploy' $source
        if ($first -and $second -and $first.save -eq '1' -and $second.save -eq '2') {
            Pass 'save data under Saved Games survived removing and redeploying the package (1 -> 2)'
        } else {
            Fail "save data across redeploy: first '$($first.save)', second '$($second.save)'"
        }
    } finally {
        if (-not (Remove-Smoke)) { Fail 'cleanup: package still present' }
        Remove-Item -Recurse -Force -ErrorAction SilentlyContinue $work, $saveDir
    }
}

if ($Mode -eq 'Unpackaged') { Test-Unpackaged } else { Test-Deployment }
if ($script:failed) { exit 1 }
exit 0
