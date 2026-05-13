param(
    [switch]$Clean
)

$ErrorActionPreference = 'Stop'

# Determine repository root (script is in scripts/)
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$repoRoot = (Resolve-Path (Join-Path $scriptDir '..')).Path

if ($Clean) {
    Write-Host "Cleaning bin directory..."
    Remove-Item -LiteralPath (Join-Path $repoRoot 'bin') -Recurse -Force -ErrorAction SilentlyContinue
    Write-Host "Clean complete."
    exit 0
}

Write-Host "Repo root: $repoRoot"

# Find all C++ source files under practice/
$srcRoot = Join-Path $repoRoot 'practice'
$srcFiles = Get-ChildItem -Path $srcRoot -Recurse -Filter '*.cpp' -File -ErrorAction SilentlyContinue

if (-not $srcFiles) {
    Write-Host "No C++ source files found under practice/."
    exit 0
}

foreach ($src in $srcFiles) {
    # relative path from repo root (no leading slash)
    $rel = $src.FullName.Substring($repoRoot.Length + 1)
    $relDir = Split-Path $rel -Parent

    $outDir = Join-Path $repoRoot 'bin'
    if ($relDir -ne '') { $outDir = Join-Path $outDir $relDir }
    New-Item -ItemType Directory -Force -Path $outDir | Out-Null

    $base = [IO.Path]::GetFileNameWithoutExtension($src.Name)
    $outExe = Join-Path $outDir ($base + '.exe')

    Write-Host "Compiling $rel -> $outExe"
    & g++ -std=c++17 -O2 -pipe -o "$outExe" "$($src.FullName)"
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Compilation failed for $rel"
        exit $LASTEXITCODE
    }
}

Write-Host "Build complete. Compiled $(($srcFiles).Count) files into bin/"
