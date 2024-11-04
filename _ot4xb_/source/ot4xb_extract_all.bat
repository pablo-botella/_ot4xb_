rd ot4xb_bin /s /q
md ot4xb_bin
rd ot4xb_source  /s /q
md ot4xb_source

7z x _ot4xb_001_007_007_002.zip  -o.\ot4xb_bin
7z x _ot4xb_001_007_007_002_source.zip  -o.\ot4xb_source

if exist "c:\util\ot4xb_autodeploy.bat" ( 
call "c:\util\ot4xb_autodeploy.bat"  %~dp0ot4xb_bin\  %~dp0ot4xb_source\  
) else (
cls                        
@echo '
@echo '
@echo '
@echo '
@echo '  - --------------------------------------------------------------------
@echo '  -   CREATE THE BATCH FILE "c:\util\ot4xb_autodeploy.bat"             -
@echo '  -   THAT WILL BE CALLED WITH THE FULL PATH OF OT4XB_BIN AS PARAMETER -
@echo '  -   SO YOU CAN CUSTOMIZE THE DEPLOYMENT ACORDING YOUR ENVIRONMENT    -
@echo '  - --------------------------------------------------------------------
@echo '
@echo '
@echo '
pause
)    



