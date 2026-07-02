@echo off

REM Ensure Python is installed
python --version >nul 2>&1
IF ERRORLEVEL 1 (
    py --version >nul 2>&1
    IF ERRORLEVEL 1 (
        echo Python was not found.
        echo Installing Python using winget...

        winget --version >nul 2>&1
        IF ERRORLEVEL 1 (
            echo winget was not found. Please install Python 3 manually from python.org and re-run setup.bat.
            exit /b 1
        )

        winget install Python.Python.3.14 --accept-package-agreements --accept-source-agreements

        echo.
        echo Python install completed.
        echo Please close and reopen this terminal, then run setup.bat again.
        exit /b 0
    )
)

echo Python found.

REM Check if vcpkg is already cloned, if not, clone it
IF NOT EXIST "vcpkg" (
    echo Cloning vcpkg...
    git clone https://github.com/microsoft/vcpkg.git
) ELSE (
    echo vcpkg already cloned
)

REM Bootstrap vcpkg if it hasn't been bootstrapped yet
IF NOT EXIST "vcpkg\vcpkg.exe" (
    echo Bootstrapping vcpkg...
    cd vcpkg
    call bootstrap-vcpkg.bat
    cd ..
) ELSE (
    echo vcpkg already bootstrapped
)

REM Install required dependencies based on vcpkg.json
echo Installing dependencies...
vcpkg\vcpkg install

REM Create build directory if it doesn't exist
IF NOT EXIST "build" (
    echo Creating build directory...
    mkdir build
) ELSE (
    echo Build directory already exists
)

echo Setup complete!
