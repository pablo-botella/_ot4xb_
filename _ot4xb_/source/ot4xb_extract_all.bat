rd ot4xb_bin
md ot4xb_bin
rd ot4xb_source
md ot4xb_source
7z x _ot4xb_001_007_000_007.zip  -o.\ot4xb_bin
7z x _ot4xb_001_007_000_007_source.zip  -o.\ot4xb_source
if exists ot4xb_autodeploy.bat call ot4xb_autodeploy.bat


