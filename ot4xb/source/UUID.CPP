//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: UUIDCreate
            | syntax_: `UUIDCreate() -> cUuid16`
            | category: uuid
            | _kw_: UUIDCreate, Function
   }}*/
/*{{|desc: Creates a new UUID with the Windows RPC API UuidCreate() and returns it in raw binary form: a
      16-byte Character string holding the UUID structure image. Use UUIDToString() to convert this
      binary form to the standard textual form.

    Returns Character - The new UUID as a 16-byte binary string.

    |note: The exported C symbol is _UUIDCREATE; ot4xb.ch maps the UUIDCreate() call to it with
      `#pragma Map()`.

    |seealso: See also: {{ilink: <function UUIDCreateStr> UUIDCreateStr}}, {{ilink: <function UUIDToString> UUIDToString}}, {{ilink: <function UUIDFromString> UUIDFromString}}, {{ilink: <function cUuidCreateName> cUuidCreateName}} }}*/
XPPRET XPPENTRY _UUIDCREATE(XppParamList pl)
{
   UUID * pu;
   pu = (UUID *) _xgrab(sizeof(UUID));
   UuidCreate( pu );
   _retclen(pl,(LPSTR) pu,sizeof(UUID));
   _xfree((void*) pu);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: UUIDCreateStr
            | syntax_: `UUIDCreateStr() -> cUuid`
            | category: uuid
            | _kw_: UUIDCreateStr, Function
   }}*/
/*{{|desc: Creates a new UUID with the Windows RPC API UuidCreate() and returns its textual
      representation as produced by the RPC API UuidToString(): hexadecimal digits in the
      hyphen-separated "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx" layout, without braces.

    Returns Character - The new UUID as a 36-character string.

    |seealso: See also: {{ilink: <function UUIDCreate> UUIDCreate}}, {{ilink: <function UUIDToString> UUIDToString}}, {{ilink: <function cUuidCreateName> cUuidCreateName}} }}*/
XPPRET XPPENTRY UUIDCREATESTR(XppParamList pl)
{
   UUID * pu;
   LPSTR pRet;
   pu = (UUID *) _xgrab(sizeof(UUID));
   UuidCreate( pu );
   UuidToString(pu,(LPBYTE*)&pRet);
   _retc(pl,pRet);
   _xfree((void*) pu);
   RpcStringFree((LPBYTE*)&pRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: UUIDFromString
            | syntax_: `UUIDFromString( cUuid ) -> cUuid16 | NIL`
            | category: uuid
            | _kw_: UUIDFromString, Function
   }}*/
/*{{|desc: Parses a textual UUID with the Windows RPC API UuidFromString() and returns it in raw binary
      form: a 16-byte Character string holding the UUID structure image. The expected layout is
      "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"; a value wrapped in braces like
      "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}" is accepted too, the braces are stripped before parsing.
    | params:
    - `cUuid` Character - The UUID in textual form, with or without surrounding braces.

    Returns Character - The UUID as a 16-byte binary string, or NIL when cUuid is not a Character value
      or cannot be parsed as a UUID.

    |seealso: See also: {{ilink: <function UUIDToString> UUIDToString}}, {{ilink: <function UUIDCreate> UUIDCreate}}, {{ilink: <function UUIDCreateStr> UUIDCreateStr}} }}*/
XPPRET XPPENTRY UUIDFROMSTRING(XppParamList pl)
{          
   ContainerHandle conr = _conNew( NULLCONTAINER);
   LPSTR pBuffer = _pszParam(pl,1);
   if( pBuffer )
   {
      UUID Id;
      LPSTR pStr = pBuffer;
      if(pStr[0] == '{')
      {  
         ULONG n;
         pStr++; 
         for( n=0; pStr[n]; n++){ if( pStr[n] == '}' ) pStr[n] = 0; }
      }
      if( UuidFromString((LPBYTE)pStr,&Id) == RPC_S_OK ) _conPutCL( conr , (LPSTR)&Id,sizeof(UUID)); 
      _xfree((void*) pBuffer);
   }
   _conReturn(pl,conr); _conRelease(conr);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: UUIDToString
            | syntax_: `UUIDToString( cUuid16 ) -> cUuid | NIL`
            | category: uuid
            | _kw_: UUIDToString, Function
   }}*/
/*{{|desc: Converts a binary UUID, as returned by UUIDCreate() or UUIDFromString(), to its textual
      representation as produced by the Windows RPC API UuidToString(): hexadecimal digits in the
      hyphen-separated "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx" layout, without braces.
    | params:
    - `cUuid16` Character - The binary UUID; the first 16 bytes of the string are taken as the UUID
      structure image, the string length is not validated.

    Returns Character - The UUID as a 36-character string, or NIL when cUuid16 is not a Character value
      or the conversion fails.

    |seealso: See also: {{ilink: <function UUIDFromString> UUIDFromString}}, {{ilink: <function UUIDCreate> UUIDCreate}}, {{ilink: <function UUIDCreateStr> UUIDCreateStr}} }}*/
XPPRET XPPENTRY UUIDTOSTRING(XppParamList pl)
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conParam(pl,1,&bByRef);
   LPSTR pStr;
   UUID * pu;
   ULONG cb = 0;
   BOOL bOk;
   if( con == NULLCONTAINER) { _ret(pl); return;}
   if( ot4xb_conRLockC(con,(LPSTR*)&pu,&cb) != 0 )
   {
     if(!bByRef) _conRelease(con);
     _ret(pl);
     return;
   }
   bOk = (UuidToString(pu,(LPBYTE*)&pStr) == RPC_S_OK);
   ot4xb_conUnlockC(con); if(!bByRef) _conRelease(con);
   if(bOk) _retc(pl,(LPSTR) pStr); else _ret(pl);
   RpcStringFree((LPBYTE*)&pStr);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
namespace uuidcreatename_ns
{

	
	//----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: timestamp_and_uuid_48
            | syntax_: `void __cdecl timestamp_and_uuid_48( XppParamList pl )`
            | category: uuid/internal
            | _kw_: timestamp_and_uuid_48, Function
   }}*/
/*{{|desc: Worker for cUuidCreateNameEx() format 2. Returns to the Xbase++ caller the prefix taken from
      parameter 1 followed by 48 uppercase hexadecimal characters: the current FILETIME from
      GetSystemTimeAsFileTime() rendered high DWORD first (16 digits), then the 32 digits of a new
      UuidCreate() UUID in textual digit order. Composed with sprintf_s() in a 256-byte work buffer; the
      room for the prefix is 128 bytes.
    | params:
    - `pl` XppParamList - The Xbase++ parameter list; parameter 1 is the optional Character prefix.

    Returns void - The composed name is returned through pl with _retc(). }}*/
	void __cdecl  timestamp_and_uuid_48(XppParamList pl)
	{
		char buffer[256]; ZeroMemory(buffer, sizeof(buffer));
		LPBYTE p = _mk_ptr_(LPBYTE, buffer, _parc(buffer, sizeof(buffer) - 128, pl, 1, 0));
		UUID   uu;
		FILETIME ft;
		GetSystemTimeAsFileTime( &ft);
		UuidCreate(&uu);
		sprintf_s( (LPSTR) p,128,
			"%08.8X%08.8X%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
			ft.dwHighDateTime,ft.dwLowDateTime,
			uu.Data1, uu.Data2, uu.Data3, uu.Data4[0], uu.Data4[1], uu.Data4[2], uu.Data4[3], uu.Data4[4], uu.Data4[5], uu.Data4[6], uu.Data4[7] );
		_retc(pl, buffer);
		return;
	}
/*{{end-internal-function}}*/
	//----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: timestamp_and_uuid_40_base32hex
            | syntax_: `void __cdecl timestamp_and_uuid_40_base32hex( XppParamList pl )`
            | category: uuid/internal
            | _kw_: timestamp_and_uuid_40_base32hex, Function
   }}*/
/*{{|desc: Worker for cUuidCreateNameEx() format 3. Composes a 24-byte block: the current FILETIME from
      ft64_now() in big-endian byte order (8 bytes) followed by the 16 bytes of a new UuidCreate() UUID
      rearranged to textual digit order (Data1, Data2 and Data3 swapped to big-endian). The block is
      encoded with ot4xb_base32_encode_with_table() using the default Crockford alphabet - despite the
      _base32hex name - into 40 characters ending with one '=' pad, appended to the prefix taken from
      parameter 1. The room for the prefix in the 256-byte work buffer is 128 bytes.
    | params:
    - `pl` XppParamList - The Xbase++ parameter list; parameter 1 is the optional Character prefix.

    Returns void - The composed name is returned through pl with _retc(). }}*/
	void __cdecl  timestamp_and_uuid_40_base32hex(XppParamList pl) 
	{
		char buffer[256]; ZeroMemory(buffer, sizeof(buffer));
		char tmp[24 ];  ZeroMemory(tmp, sizeof(tmp));
		int  tmpcb = sizeof(tmp);
		int cb;
		LPBYTE p = _mk_ptr_(LPBYTE, buffer, _parc(buffer, sizeof(buffer) - 128, pl, 1, 0));
		
		BYTE  uu[16];
		FILETIME ft;
		ft64_now(&ft);
		UuidCreate( (UUID*)( (void*) &uu) );

		tmp[ 0]  = HIBYTE(HIWORD(ft.dwHighDateTime));
      tmp[ 1]  = LOBYTE(HIWORD(ft.dwHighDateTime));
      tmp[ 2]  = HIBYTE(LOWORD(ft.dwHighDateTime));  
      tmp[ 3]  = LOBYTE(LOWORD(ft.dwHighDateTime));  
      tmp[ 4]  = HIBYTE(HIWORD(ft.dwLowDateTime));
      tmp[ 5]  = LOBYTE(HIWORD(ft.dwLowDateTime));  
      tmp[ 6]  = HIBYTE(LOWORD(ft.dwLowDateTime));  
      tmp[ 7]  = LOBYTE(LOWORD(ft.dwLowDateTime));
		tmp[8]   = uu[3];
		tmp[9]   = uu[2];
		tmp[10]  = uu[1];
		tmp[11]  = uu[0];
		tmp[12]  = uu[5];
		tmp[13]  = uu[4];
		tmp[14]  = uu[7];
		tmp[15]  = uu[6];
		tmp[16]  = uu[8];
		tmp[17]  = uu[9];
		tmp[18]  = uu[10];
		tmp[19]  = uu[11];
		tmp[20]  = uu[12];
		tmp[21]  = uu[13];
		tmp[22]  = uu[14];
		tmp[23]  = uu[15];

      
		cb = 127;
		ot4xb_base32_encode_with_table(0, (LPBYTE)tmp, tmpcb,(LPSTR) p, &cb, 0);
		_retc(pl, buffer);

		return;
	}
/*{{end-internal-function}}*/
	//----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: newsequentialid
            | syntax_: `void __cdecl newsequentialid( XppParamList pl )`
            | category: uuid/internal
            | _kw_: newsequentialid, Function
   }}*/
/*{{|desc: Worker for cUuidCreateNameEx() format 1. Creates a UUID with UuidCreateSequential(),
      rearranges its 16 bytes to textual digit order (Data1, Data2 and Data3 swapped to big-endian) and
      appends them with Bin2Hex_buffer() as 32 uppercase hexadecimal characters to the prefix taken from
      parameter 1. The room for the prefix in the 256-byte work buffer is 223 bytes.
    | params:
    - `pl` XppParamList - The Xbase++ parameter list; parameter 1 is the optional Character prefix.

    Returns void - The composed name is returned through pl with _retc(). }}*/
   void __cdecl  newsequentialid(XppParamList pl)
	{
		char buffer[256]; ZeroMemory(buffer, sizeof(buffer));
		LPBYTE p = _mk_ptr_(LPBYTE, buffer, _parc(buffer, sizeof(buffer) - ((sizeof(UUID) * 2) + 1), pl, 1, 0));
		UUID   uu;
		LPBYTE s = (LPBYTE)((void*)&uu);
		BYTE   t[16];
		ZeroMemory(&uu, sizeof(UUID));

		UuidCreateSequential(&uu);

		t[3] = s[0];	t[2] = s[1];	t[1] = s[2];	t[0] = s[3];	t[5] = s[4];	t[4] = s[5];	t[7] = s[6];	t[6] = s[7];
		t[8] = s[8];	t[9] = s[9];	t[10] = s[10];	t[11] = s[11];	t[12] = s[12];	t[13] = s[13];	t[14] = s[14];	t[15] = s[15];

		Bin2Hex_buffer(t, 16, (LPSTR)p, ((sizeof(UUID) * 2) + 1));
		_retc(pl, buffer);
		return;
	}
/*{{end-internal-function}}*/
	//----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: old_ot4xb_cuuidcreatename
            | syntax_: `void __cdecl old_ot4xb_cuuidcreatename( XppParamList pl )`
            | category: uuid/internal
            | _kw_: old_ot4xb_cuuidcreatename, Function
   }}*/
/*{{|desc: Worker for cUuidCreateName() and for cUuidCreateNameEx() format 0, which is also the fallback
      for unlisted format values. Creates a UUID with UuidCreate(), renders it with the RPC API
      UuidToString() and appends it to the prefix taken from parameter 1 with the '-' separators removed:
      32 hexadecimal characters. The name is built in a 128-byte heap buffer; the room for the prefix is
      64 bytes.
    | params:
    - `pl` XppParamList - The Xbase++ parameter list; parameter 1 is the optional Character prefix.

    Returns void - The composed name is returned through pl with _retc(). }}*/
	void __cdecl  old_ot4xb_cuuidcreatename(XppParamList pl)
	{
		UUID   uu;
		LPBYTE pus = 0;
		LPSTR pBuffer = (LPSTR)_xgrab(128);
		LPSTR p = (LPSTR)(((DWORD)pBuffer) + ((DWORD)_parc(pBuffer, 64, pl, 1, 0)));
		LPSTR pp;
		ZeroMemory(&uu, sizeof(UUID)); UuidCreate(&uu); UuidToString(&uu, &pus);
		for (pp = (LPSTR)pus; pp[0]; pp++) { if (!(pp[0] == '-')) { p[0] = pp[0]; p++; } }
		RpcStringFree(&pus);
		_retc(pl, pBuffer);
		_xfree((void*)pBuffer);
	}
/*{{end-internal-function}}*/
}
// --------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cUuidCreateNameEx
            | syntax_: `cUuidCreateNameEx( [cPrefix], [nMode] ) -> cName`
            | category: uuid
            | _kw_: cUuidCreateNameEx, Function
   }}*/
/*{{|desc: Returns cPrefix followed by freshly generated UUID-based text in one of several formats
      selected by nMode. All formats produce separator-free text suitable for building names; formats 2
      and 3 start with a big-endian render of the current FILETIME, making those names sortable by
      creation time.
    | params:
    - `cPrefix` Character - Optional prefix copied verbatim in front of the generated text. The name
      is composed in a fixed work buffer; the room for the prefix is 64 bytes in format 0, 223 bytes in
      format 1 and 128 bytes in formats 2 and 3.
    - `nMode` Numeric - The output format, see the flag list; when missing or not a listed value,
      format 0 is used.
    | flags:
    - `0` Same output as cUuidCreateName(): a UuidCreate() UUID rendered by the RPC API
      UuidToString() with the '-' separators removed (32 hexadecimal characters).
    - `1` A UuidCreateSequential() UUID with Data1, Data2 and Data3 swapped to big-endian, rendered
      as 32 uppercase hexadecimal characters in textual digit order.
    - `2` The current FILETIME from GetSystemTimeAsFileTime(), high DWORD first, followed by a
      UuidCreate() UUID in textual digit order: 48 uppercase hexadecimal characters.
    - `3` The current FILETIME from ft64_now(), big-endian, followed by a UuidCreate() UUID in
      textual digit order: 24 bytes encoded as 40 characters of Crockford Base32 ('0'-'9' and uppercase
      letters excluding I, L, O and U), the last one a '=' pad.

    Returns Character - The composed name.

    |seealso: See also: {{ilink: <function cUuidCreateName> cUuidCreateName}}, {{ilink: <function UUIDCreate> UUIDCreate}}, {{ilink: <function UUIDCreateStr> UUIDCreateStr}} }}*/
XPPRET XPPENTRY CUUIDCREATENAMEEX(XppParamList pl)
{
	DWORD flags = (DWORD)_parnl(pl, 2);
	switch (flags)
	{
		case 0:
		{
			uuidcreatename_ns::old_ot4xb_cuuidcreatename(pl);
			break;
		}
		case 1: 
		{
			uuidcreatename_ns::newsequentialid(pl);
			break;
		}
		case 2:
		{
			uuidcreatename_ns::timestamp_and_uuid_48(pl);

			break;
		}
		case 3:
		{
			uuidcreatename_ns::timestamp_and_uuid_40_base32hex(pl);

			break;
		}
		default:
		{
			uuidcreatename_ns::old_ot4xb_cuuidcreatename(pl);
			break;
		}
	}
	
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cUuidCreateName
            | syntax_: `cUuidCreateName( [cPrefix] ) -> cName`
            | category: uuid
            | _kw_: cUuidCreateName, Function
   }}*/
/*{{|desc: Returns cPrefix followed by a freshly generated UuidCreate() UUID rendered by the RPC API
      UuidToString() with the '-' separators removed: 32 hexadecimal characters. Same output as
      cUuidCreateNameEx( cPrefix, 0 ).
    | params:
    - `cPrefix` Character - Optional prefix copied verbatim in front of the generated text; the room
      for it in the internal work buffer is 64 bytes.

    Returns Character - The composed name.

    |seealso: See also: {{ilink: <function cUuidCreateNameEx> cUuidCreateNameEx}}, {{ilink: <function UUIDCreateStr> UUIDCreateStr}}, {{ilink: <function UUIDCreate> UUIDCreate}} }}*/
XPPRET XPPENTRY CUUIDCREATENAME(XppParamList pl)
{
	uuidcreatename_ns::old_ot4xb_cuuidcreatename(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
