@echo off


rem ==========================================================================
rem delete all vcproject related files
rem ==========================================================================
del /s /q *.ncb *.user *.log
rem ==========================================================================


rem ==========================================================================
rem delete all binary files
rem ==========================================================================
md Product
cd Product
md Binary
cd Binary
del /s /q *.pdb *.ilk *.dll *.exe
cd ..
cd ..
rem ==========================================================================


rem ==========================================================================
rem delete all library files
rem ==========================================================================
md Product
cd Product
md Library
cd Library
del /s /q *.exp *.lib
cd ..
cd ..
rem ==========================================================================


rem ==========================================================================
rem delete all library files
rem ==========================================================================
md Product
cd Product
md Binary
cd Binary
del /s /q *.exp *.lib
cd ..
cd ..
rem ==========================================================================


rem ==========================================================================
rem delete all library files
rem ==========================================================================
md External
cd External
md WingSDK
cd WingSDK
md Library
cd Library
del /s /q *.exp *.lib
cd ..
cd ..
cd ..
rem ==========================================================================


rem ==========================================================================
rem delete external temporary files
rem ==========================================================================
rem ==========================================================================


rem ==========================================================================
rem delete temporary build files under Source
rem ==========================================================================
del /s /q Source\Debug\*.*
rmdir Source\Debug
del /s /q Source\Release\*.*
rmdir Source\Release
rem ==========================================================================


rem ==========================================================================
rem delete temporary build files under Tools
rem ==========================================================================
del /s /q Tools\Debug\*.*
rmdir Tools\Debug
del /s /q Tools\Release\*.*
rmdir Tools\Release
rem ==========================================================================


rem ==========================================================================
rem delete temporary build files under Product\Samples
rem ==========================================================================
del /s /q Product\Samples\Debug\*.*
rmdir Product\Samples\Debug
del /s /q Product\Samples\Release\*.*
rmdir Product\Samples\Release
rem ==========================================================================
