::Script for removal of compilation files to get clean files for push to git.

del /S .\Debug\*.o 
del /S .\Debug\*.d
del /S .\Debug\*.su 
@ECHO OFF

