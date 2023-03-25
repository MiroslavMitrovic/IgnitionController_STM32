::Project Name Variable
set PROJECT_NAME="IgnitionController"
::Command to create and build project based on CMake JSON build description
polyspace-configure -prog %PROJECT_NAME% -compilation-database ./../../build/compile_commands.json -allow-overwrite -exclude-sources ./../../Core/Startup/startup_stm32f407vgtx.s
::Generate Startup command 
polyspace -generate-launching-script-for IgnitionController.psprj
::Run Launching command 
CALL ./%PROJECT_NAME%/launchingCommand.bat

echo Polyspace Analysis done! 

echo Opening Polyspace Report
::command for opening the results 
polyspace -open ./%PROJECT_NAME%/results/ps_results.pscp
echo Report opened!
echo opening Polyspace Project 
::command for opening the project 
polyspace -open IgnitionController.psprj