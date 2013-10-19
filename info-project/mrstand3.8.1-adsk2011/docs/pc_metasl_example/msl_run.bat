@echo off
setlocal

REM This is where to find mental ray executables
set MR=%ProgramFiles%\mental images\mental ray nt-x86-vc8sp1\bin

REM Set Visual Studio compilation variables
rem call "C:\Program Files\Microsoft Visual Studio 8\VC\vcvarsall.bat" 

REM Set environment variables needed for compiling shaders
REM - to find the ray3rc file
set MI_ROOT=.
REM - to avoid using wrong mental ray setup
set MI_RAY_INCPATH=


REM Calling mental ray
"%MR%/ray.exe" -ld_path ../../../nt-x86-vc8sp1/shaders -v 5 -x on -trace_depth 2 2 2 -resolution 640 480 -samples 0 1 -aspect 1.333333 %1 
REM Calling imf_disp to visualize the rendered image
start "preview" "%MR%/imf_disp.exe"  "msl_image.pic" 

endlocal
