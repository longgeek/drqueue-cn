@echo off
set MI_ROOT=.\
rem - Setup the path in order to allow the shader DLLs to load dependencies from the 3ds Max folder.
set PATH=..\..\;%PATH%
raysat_3dsmax2014_64.exe