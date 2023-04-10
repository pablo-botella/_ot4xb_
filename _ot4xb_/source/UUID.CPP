//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _UUIDCREATE(XppParamList pl)
{
   UUID * pu;
   pu = (UUID *) _xgrab(sizeof(UUID));
   UuidCreate( pu );
   _retclen(pl,(LPSTR) pu,sizeof(UUID));
   _xfree((void*) pu);
}
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
namespace uuidcreatename_ns
{

	
	//----------------------------------------------------------------------------------------------------------------------
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
	//----------------------------------------------------------------------------------------------------------------------
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
	//----------------------------------------------------------------------------------------------------------------------
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
	//----------------------------------------------------------------------------------------------------------------------
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
}
// --------------------------------------------------------------------------------------------------------------------
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
XPPRET XPPENTRY CUUIDCREATENAME(XppParamList pl)
{
	uuidcreatename_ns::old_ot4xb_cuuidcreatename(pl);
}


// -----------------------------------------------------------------------------------------------------------------
