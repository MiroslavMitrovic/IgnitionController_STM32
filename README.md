# IgnitionController_STM32

## Ignition controller implementation for  4T Single Cylinder/V-Twin motorcycle. 

- Generated documentation is available in .\IgnitionController_STM32\Documentation\Ignition_Controller.chm
- Requirements are available in .\IgnitionController_STM32\Design\Requirements\IgnitionControllerRequriements.txt
- Architecture is done with Rational Software architect, and project is available at .\IgnitionController_STM32\Design\

##Addition of CMake build toolchain 
Command for build configuration generation is : 
cmake -G "Unix Makefiles" -S . -B build -DCMAKE_BUILD_TYPE="Debug" -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-gcc.cmake" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 
Command for build is : 
cmake --build build  
