echo on 
echo ---------------------------------------------------*****************************
echo postbuild:
echo %~f0  %1  %2
echo ---------------------------------------------------*****************************

echo copy %1ot4xb.def  %2ot4xb.def
copy %1ot4xb.def  %2ot4xb.def
copy %1__mklib.bat  %2__mklib.bat
rem del %2ot4xb.lib

%~d2
CD %~dp2         
echo %~d2
echo %~dp2
C:\xpp19355\XPPW32\bin\aimplib.exe
C:\xpp19355\XPPW32\bin\aimplib.exe
C:\xpp19355\XPPW32\bin\aimplib.exe  ot4xb.def   /oot4xb.lib
           

%~d1
CD %~dp1

echo ---------------------------------------------------*****************************

                                      
@echo ----------------------------------------

@echo ----------------------------------------
IF EXIST C:\pli\ot4xb  copy %2ot4xb.dll        C:\pli\ot4xb\   
IF EXIST C:\pli\ot4xb  copy %2ot4xb.dll        C:\pli\ot4xb\   
IF EXIST C:\pli\ot4xb  copy %2ot4xbcpp.lib     C:\pli\ot4xb\   
IF EXIST C:\pli\ot4xb  copy %2ot4xb.lib        C:\pli\ot4xb\   
IF EXIST C:\pli\ot4xb  copy %1ch\*.ch          C:\pli\ot4xb\   


@echo ----------------------------------------

IF EXIST c:\util\ot4xb-deploy-release.bat call c:\util\ot4xb-deploy-release.bat   %1  %2

@echo ----------------------------------------

IF EXIST __mk_package.bat call __mk_package.bat  %1  %2

@echo ----------------------------------------

IF EXIST  versioninfo.log  type versioninfo.log
IF EXIST  versioninfo.log  del  versioninfo.log

@echo ----------------------------------------
