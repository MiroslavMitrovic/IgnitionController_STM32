cmake -G "Unix Makefiles" -S . -B build -DCMAKE_BUILD_TYPE="Debug" -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-gcc.cmake" -DCMAKE_EXPORT_COMPILE_COMMANDS=1

cmake --build build