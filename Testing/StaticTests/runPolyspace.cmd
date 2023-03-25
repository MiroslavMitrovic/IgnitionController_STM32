::Project Name Variable
set PROJECT_NAME="IgnitionController"
::Command to create and build project based on CMake JSON build description
polyspace-configure -prog %PROJECT_NAME% -compilation-database ./../../build/compile_commands.json -allow-overwrite -exclude-sources ./../../Core/Startup/startup_stm32f407vgtx.s
::Generate Startup command 
polyspace -generate-launching-script-for IgnitionController.psprj
::Run Launching command 
CALL ./%PROJECT_NAME%/launchingCommand.bat

echo Polyspace Analysis done! 

