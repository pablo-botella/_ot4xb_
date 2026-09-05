RapidJSON source folder:

The rapidjson folder contains an unmodified copy of the RapidJSON
library, taken from the master branch of its owners' repository:

https://github.com/Tencent/rapidjson

The copy corresponds exactly to commit
24b5e7a8b27f42fa16b96fc70aade9106cf7102f of 2025-02-05
("Fix out of bounds read with kParseValidateEncodingFlag"), the
head of master when it was copied on 2026-08-20. RapidJSON is a
header-only C++ library: this folder is the include/rapidjson/
tree of that commit. No file was modified, except that line
endings were converted from LF to CRLF, which is this project's
convention.

Note: the rapidjson.h version macros declare 1.1.0 because v1.1.0
(2016) is the last tagged release of RapidJSON; master is newer.

---------
RapidJSON:

RapidJSON is a fast JSON parser and generator for C++, with both
SAX and DOM style APIs.

RapidJSON belongs to its legitimate owners: Copyright (C) 2015
THL A29 Limited, a Tencent company, and Milo Yip. It is licensed
under the MIT License; the license text is at the top of each
header file.

The msinttypes headers (rapidjson/msinttypes/stdint.h and
inttypes.h, used only with old Microsoft Visual C++ compilers) are
copyright (c) 2006-2013 Alexander Chemeris, under the BSD license,
with Tencent Modifications copyright (C) 2015 THL A29 Limited.

Official web site and repository:
https://rapidjson.org/
https://github.com/Tencent/rapidjson
