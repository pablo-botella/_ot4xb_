
echo ---------    %0
echo %1
echo %2
echo ----------------------  
set "path=c:\util;%path%"
md %2builds
md %2builds\_ot4xb_001_007_000_007

md %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007
md %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007\include
md %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source
md %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
md %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source\ch

copy %2ot4xb.dll  %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007
copy %2ot4xb.lib  %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007
copy %2ot4xb_cpp.lib  %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007
copy %1*.txt %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007
copy %1ch\*.ch  %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007\include

copy %1ot4xb_extract_all.bat  %2builds\_ot4xb_001_007_000_007\ot4xb_extract_all.bat

%~d2
cd %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007
7za.exe a -y  ..\_ot4xb_001_007_000_007.zip  *
%~d1
cd %~dp1

copy %1..\ot4xb.sln %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source
copy %1ch\*.ch  %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source\ch
copy %1*.rc %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
copy %1*.txt %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
copy %1*.h %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
copy %1*.hpp %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
copy %1*.c %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
copy %1*.cpp %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
copy %1*.def %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
copy %1*.xbmac %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
copy %1*.versioninfo %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
copy %1*.bat %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
del %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source\BAT??????????????.bat
copy %1ot4xb.vcproj %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
%~d2
cd %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source
7za.exe a -y  ..\_ot4xb_001_007_000_007_source.zip   *

%~d1
cd %~dp1


if exist %2builds\SKIP_REMOVE_FILES.TXT goto SKIP_REMOVE_FILES
del %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007\*.* /q
del %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007\include\*.* /q
del %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\*.* /q
del %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source\*.* /q
del %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source\ch\*.* /q

rd %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007\include
rd %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source\ch
rd %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source\source
rd %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007_source
rd %2builds\_ot4xb_001_007_000_007\_ot4xb_001_007_000_007
rd %2builds\_ot4xb_001_007_000_007
:SKIP_REMOVE_FILES

