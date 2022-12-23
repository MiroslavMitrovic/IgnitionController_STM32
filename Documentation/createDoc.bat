@echo on

:: kill HTML Help process, in case it is open 
taskkill /im "hh.exe" /f /fi "STATUS eq RUNNING" > nul

:: Cleanup 
if exist *.chm del *.chm

::set pahth to perl 
SET PERL_EXE=C:\tools\Perl\perl\bin\perl.exe

::set tools 
SET GRAPHVIZ_DOT=C:/tools/Graphviz/bin/dot.exe
SET DOXYGEN_EXE=C:/tools/doxygen/bin/doxygen.exe
SET PLANTUML_JAR=C:/tools/PlantUML/plantuml.jar
SET HHC_EXE=C:/tools/hhc/hhc.exe
SET HHC_PATH=d:/Projects/git/STM/IgnitionController_STM32/Documentation/html/index.hhp
::set directories
SET INPUT_DIR1=d:/Projects/git/STM/IgnitionController_STM32/Core
SET PROJECT_NAME=IgnitionController

SET IMG_PATH1=./images
::java -jar %PLANTUML_JAR% -v -o "%IMG_PATH1%" "%INPUT_DIR1%/**.(c|cpp|doc|h|md|markdown)"
%DOXYGEN_EXE% project.doxy 

::generate .chm file 
::hhc ./html/index.hhp
::Cleanup after 
rd html /s/q 
PAUSE 

