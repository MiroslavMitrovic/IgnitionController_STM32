@echo off
echo Build started on %DATE% at %TIME%
:: Capture the start time
set "startTime=%TIME%"

echo "Removing build folder!"
rmdir /s /q "build"
echo "Removing done!"
echo "Creating build dependencies...."
cmake -G "Unix Makefiles" -S . -B build -DCMAKE_BUILD_TYPE="Debug" -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-gcc.cmake" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON  
echo "Build started, good luck!"
cmake --build build
echo Build finished on %DATE% at %TIME%
:: Capture the end time
set "endTime=%TIME%"
:: Convert start time to seconds (ignores centiseconds)
for /f "tokens=1-3 delims=:,." %%a in ("%startTime%") do (
    set /a startSeconds=%%a*3600 + %%b*60 + %%c
)
:: Convert end time to seconds (ignores centiseconds)
for /f "tokens=1-3 delims=:,." %%a in ("%endTime%") do (
    set /a endSeconds=%%a*3600 + %%b*60 + %%c
)

:: Calculate the duration
set /a duration=endSeconds - startSeconds

echo build took: %duration% seconds