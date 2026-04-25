param(
    [Parameter(Mandatory = $true)]
    [string]$Source,

    [switch]$Run
)

$ErrorActionPreference = "Stop"

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$repoRoot = Split-Path -Parent $scriptDir
$sourcePath = [System.IO.Path]::GetFullPath((Join-Path (Get-Location) $Source))
$rootPath = [System.IO.Path]::GetFullPath($repoRoot)

if (-not (Test-Path -LiteralPath $sourcePath)) {
    Write-Error "Source file not found: $Source"
}

if (-not $sourcePath.StartsWith($rootPath, [System.StringComparison]::OrdinalIgnoreCase)) {
    Write-Error "Source file must be inside the repository: $sourcePath"
}

$relativeSource = $sourcePath.Substring($rootPath.Length).TrimStart('\', '/')
$relativeExe = [System.IO.Path]::ChangeExtension($relativeSource, ".exe")
$exePath = Join-Path (Join-Path $rootPath "bin") $relativeExe
$exeDir = Split-Path -Parent $exePath

New-Item -ItemType Directory -Force -Path $exeDir | Out-Null

g++ $sourcePath -o $exePath
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

Write-Host "Built $exePath"

if ($Run) {
    & $exePath
    exit $LASTEXITCODE
}
