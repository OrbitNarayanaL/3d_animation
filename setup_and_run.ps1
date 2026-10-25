# 3D Character Creation Software - Setup and Run Script
# PowerShell Automation for Windows (MSVC + CMake + Python + PySide6)

param(
    [switch]$SkipVenv,
    [switch]$SkipBuild,
    [switch]$SkipDeps
)

Write-Host "==================================================" -ForegroundColor Cyan
Write-Host "3D Character Creation Software - Setup & Run" -ForegroundColor Cyan
Write-Host "==================================================" -ForegroundColor Cyan
Write-Host ""

# Function to check Python version
function Test-PythonVersion {
    try {
        $pythonVersion = python --version 2>&1
        Write-Host "Found: $pythonVersion" -ForegroundColor Green
        # Check if version is 3.10+
        if ($pythonVersion -match "Python 3\.(\d+)") {
            $minor = [int]$matches[1]
            if ($minor -ge 10) {
                return $true
            } else {
                Write-Host "WARNING: Python 3.10+ recommended. Current version may have compatibility issues." -ForegroundColor Yellow
                return $true
            }
        }
        return $false
    }
    catch {
        Write-Host "ERROR: Python not found. Please install Python 3.10+ and add to PATH." -ForegroundColor Red
        return $false
    }
}

# Function to setup virtual environment
function Setup-VirtualEnv {
    if ($SkipVenv) {
        Write-Host "Skipping virtual environment setup..." -ForegroundColor Yellow
        return $true
    }
    
    Write-Host "`n[1/4] Setting up Python virtual environment..." -ForegroundColor Cyan
    
    if (Test-Path "venv") {
        Write-Host "Virtual environment already exists." -ForegroundColor Green
    }
    else {
        Write-Host "Creating virtual environment..." -ForegroundColor Yellow
        try {
            python -m venv venv
            Write-Host "Virtual environment created successfully." -ForegroundColor Green
        }
        catch {
            Write-Host "ERROR: Failed to create virtual environment." -ForegroundColor Red
            return $false
        }
    }
    
    # Activate virtual environment
    Write-Host "Activating virtual environment..." -ForegroundColor Yellow
    try {
        & ".\venv\Scripts\Activate.ps1"
        Write-Host "Virtual environment activated." -ForegroundColor Green
    }
    catch {
        Write-Host "WARNING: Could not activate virtual environment via script. Trying alternative method..." -ForegroundColor Yellow
    }
    
    return $true
}

# Function to install dependencies
function Install-Dependencies {
    if ($SkipDeps) {
        Write-Host "Skipping dependency installation..." -ForegroundColor Yellow
        return $true
    }
    
    Write-Host "`n[2/4] Installing Python dependencies..." -ForegroundColor Cyan
    
    try {
        Write-Host "Upgrading pip..." -ForegroundColor Yellow
        python -m pip install --upgrade pip --quiet
        
        Write-Host "Installing PySide6 and numpy..." -ForegroundColor Yellow
        pip install PySide6 numpy --quiet
        
        Write-Host "Dependencies installed successfully." -ForegroundColor Green
        return $true
    }
    catch {
        Write-Host "ERROR: Failed to install dependencies." -ForegroundColor Red
        return $false
    }
}

# Function to build C++ extension
function Build-CPP {
    if ($SkipBuild) {
        Write-Host "Skipping C++ build..." -ForegroundColor Yellow
        return $true
    }
    
    Write-Host "`n[3/4] Building C++ extension with CMake..." -ForegroundColor Cyan
    
    # Check for CMake
    try {
        $cmakeVersion = cmake --version 2>&1 | Select-Object -First 1
        Write-Host "Found: $cmakeVersion" -ForegroundColor Green
    }
    catch {
        Write-Host "ERROR: CMake not found. Please install CMake 3.20+ and add to PATH." -ForegroundColor Red
        return $false
    }
    
    # Check for build directory
    if (-not (Test-Path "build")) {
        Write-Host "Creating build directory..." -ForegroundColor Yellow
        New-Item -ItemType Directory -Path "build" | Out-Null
    }
    
    # Navigate to build directory
    Push-Location "build"
    
    try {
        # Configure CMake
        Write-Host "Configuring CMake for Visual Studio 17 2022 (x64)..." -ForegroundColor Yellow
        cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
        
        if ($LASTEXITCODE -ne 0) {
            throw "CMake configuration failed"
        }
        Write-Host "CMake configuration completed." -ForegroundColor Green
        
        # Build
        Write-Host "Compiling (this may take several minutes)..." -ForegroundColor Yellow
        cmake --build . --config Release
        
        if ($LASTEXITCODE -ne 0) {
            throw "CMake build failed"
        }
        Write-Host "Build completed successfully." -ForegroundColor Green
        
        # Verify renderer.pyd was generated
        Pop-Location
        $pydPath = "python\api\renderer.pyd"
        if (Test-Path $pydPath) {
            Write-Host "Verification: renderer.pyd found at $pydPath" -ForegroundColor Green
            $pydSize = (Get-Item $pydPath).Length / 1MB
            Write-Host "Module size: $([math]::Round($pydSize, 2)) MB" -ForegroundColor Green
        }
        else {
            # Check in build directory
            $altPath = "build\lib\Release\renderer.pyd"
            if (Test-Path $altPath) {
                Write-Host "Copying renderer.pyd to python/api/..." -ForegroundColor Yellow
                Copy-Item $altPath $pydPath
                Write-Host "Verification: renderer.pyd copied successfully." -ForegroundColor Green
            }
            else {
                Write-Host "WARNING: renderer.pyd not found in expected locations." -ForegroundColor Yellow
                Write-Host "The application may run in fallback mode without native acceleration." -ForegroundColor Yellow
            }
        }
        
        return $true
    }
    catch {
        Write-Host "ERROR: Build failed - $_" -ForegroundColor Red
        Pop-Location
        return $false
    }
}

# Function to run application
function Run-Application {
    Write-Host "`n[4/4] Launching 3D Character Creation Software..." -ForegroundColor Cyan
    
    try {
        # Ensure we're in root directory
        if ((Get-Location).Path -like "*\build") {
            Set-Location ..
        }
        
        Write-Host "Starting application..." -ForegroundColor Green
        Write-Host "Press Ctrl+C to exit." -ForegroundColor Yellow
        Write-Host ""
        
        python python\app.py
        
        return $true
    }
    catch {
        Write-Host "ERROR: Failed to launch application." -ForegroundColor Red
        Write-Host $_.Exception.Message -ForegroundColor Red
        return $false
    }
}

# Main execution
try {
    # Check Python
    if (-not (Test-PythonVersion)) {
        exit 1
    }
    
    # Setup and build
    if (-not (Setup-VirtualEnv)) { exit 1 }
    if (-not (Install-Dependencies)) { exit 1 }
    if (-not (Build-CPP)) { exit 1 }
    
    # Run application
    Run-Application
}
catch {
    Write-Host "`nFATAL ERROR: $_" -ForegroundColor Red
    exit 1
}

Write-Host "`n==================================================" -ForegroundColor Cyan
Write-Host "Setup and execution complete." -ForegroundColor Cyan
Write-Host "==================================================" -ForegroundColor Cyan
