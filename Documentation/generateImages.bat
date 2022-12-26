::SCRIPT for generation of images using PLANT UML TOOL

@echo on

::set Paths for tools 
SET GRAPHVIZ_DOT=C:/tools/Graphviz/bin/dot.exe
SET DOXYGEN_EXE=C:/tools/doxygen/bin/doxygen.exe
SET PLANTUML_JAR=C:\tools\PlantUML\plantuml.jar


::set paths for generation 

SET INPUT_DIR1=d:\Projects\ReflowPreheater\ReflowPreheater\Core\Inc\
SET PROJECT_NAME= ReflowPreheater

::Set output folder for images 

SET IMG_PATH1=d:\Projects\ReflowPreheater\ReflowPreheater\Docs\images\

::generate PLANTUML images

java -jar %PLANTUML_JAR% -v -o "%IMG_PATH1%" "%INPUT_DIR1%*.(c|cpp|doc|h|md|markdown)"
pause 
