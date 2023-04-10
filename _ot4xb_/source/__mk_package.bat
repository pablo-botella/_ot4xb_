
echo %1
echo %2
echo ----------------------
set "path=c:\util;%path%"
md %2builds
md %2builds\_ot4xb_001_007_000_005

md %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005
md %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005\include
md %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source
md %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
md %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source\ch

copy %2ot4xb.dll  %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005
copy %2ot4xb.lib  %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005
copy %2ot4xb_cpp.lib  %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005
copy %1*.txt %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005
copy %1ch\*.ch  %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005\include
7za.exe a -y  %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005.zip  %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005\*

copy %1..\ot4xb.sln %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source
copy %1ch\*.ch  %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source\ch
copy %1*.rc %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
copy %1*.txt %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
copy %1*.h %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
copy %1*.hpp %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
copy %1*.c %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
copy %1*.cpp %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
copy %1*.def %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
copy %1*.xbmac %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
copy %1*.versioninfo %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
copy %1*.bat %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
del %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source\BAT??????????????.bat
copy %1ot4xb.vcproj %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
7za.exe a -y  %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source.zip  %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\*




if exist %2builds\SKIP_REMOVE_FILES.TXT goto SKIP_REMOVE_FILES
del %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005\*.* /q
del %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005\include\*.* /q
del %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\*.* /q
del %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source\*.* /q
del %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source\ch\*.* /q

rd %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005\include
rd %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source\ch
rd %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source\source
rd %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005_source
rd %2builds\_ot4xb_001_007_000_005\_ot4xb_001_007_000_005
rd %2builds\_ot4xb_001_007_000_005
:SKIP_REMOVE_FILES

