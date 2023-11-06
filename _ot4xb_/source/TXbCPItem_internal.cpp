//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
TXbCPItem::TXbCPItem(void)
{
   m_pl = 0;
   m_nRealPosition = 0;
   m_bInit = 0;
   m_nType = 0;
   m_nLockLen = 0;
   m_bByRef = 0;
   m_con = 0;
   m_pLockStr = 0;
   m_bLockW = 0;
   m_nCntType = 0;
   m_pComplex = 0;
   m_bStrLockEx = 0;
}
// -----------------------------------------------------------------------------------------------------------------
TXbCPItem::TXbCPItem(ContainerHandle _con, BOOL bByRef)
{
   m_pl = 0;
   m_nRealPosition = 0;
   m_bInit = 0;
   m_nType = 0;
   m_nLockLen = 0;
   m_bByRef = bByRef;
   m_con = _con;
   m_pLockStr = 0;
   m_bLockW = 0;
   m_nCntType = 0;
   m_pComplex = 0;
   m_bStrLockEx = 0;

}
//----------------------------------------------------------------------------------------------------------------------
TXbCPItem::TXbCPItem(XppParamList pl, ULONG n)
{
   m_pl = pl;
   m_nRealPosition = n;
   m_bInit = 0;
   m_nType = 0;
   m_nLockLen = 0;
   m_bByRef = 0;
   m_con = 0;
   m_pLockStr = 0;
   m_bLockW = 0;
   m_nCntType = 0;
   m_pComplex = 0;
   m_bStrLockEx = 0;
}
//----------------------------------------------------------------------------------------------------------------------
TXbCPItem::~TXbCPItem(void)
{
   UnLockStrEx();
   if (m_con)
   {
      if (!m_bByRef) { _conRelease(m_con); }
      m_con = 0;
   }
   m_pl = 0;
   m_nRealPosition = 0;
   m_bInit = 0;
   m_nType = 0;
   m_nLockLen = 0;
   m_bByRef = 0;
   m_pLockStr = 0;
   m_bLockW = 0;
   m_nCntType = 0;
   m_pComplex = 0;
   m_bStrLockEx = 0;

}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle TXbCPItem::detach(void)
{
   ContainerHandle _con;
   UnLockStrEx();
   _con = m_con;
   m_con = 0;
   m_pl = 0;
   m_nRealPosition = 0;
   m_bInit = 0;
   m_nType = 0;
   m_nLockLen = 0;
   m_bByRef = 0;
   m_pLockStr = 0;
   m_bLockW = 0;
   m_nCntType = 0;
   m_pComplex = 0;
   m_bStrLockEx = 0;
   return _con;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::init(void)
{
   if (!m_bInit)
   {
      if (m_pl && m_nRealPosition)
      {
         m_con = _conParam(m_pl, m_nRealPosition, &m_bByRef);
      }
      m_bInit = TRUE; // TODO: CHECK THIS!!!!!!!!!!!!!!!!
   }
}
//----------------------------------------------------------------------------------------------------------------------
ULONG TXbCPItem::GetType(void)
{
   ULONG n = 0;
   init();
   if (m_con == NULLCONTAINER) return 0;
   _conType(m_con, &n);
   return n;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TXbCPItem::CheckType(ULONG ulType) { return (BOOL)(ulType & GetType()); }
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbCPItem::GetT(ULONG ulType, BOOL* pbByRef) { return (CheckType(ulType) ? Get(pbByRef) : 0); }
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbCPItem::Get(BOOL* pbByRef) { init(); if (pbByRef) { pbByRef[0] = m_bByRef; } return m_con; }
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle TXbCPItem::con(void)
{
   init();
   if (!m_con) { m_bByRef = 0; m_con = _conNew(NULLCONTAINER); }
   return m_con;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::Put(ContainerHandle con) { init(); m_con = _conPut(m_con, con); }
// -----------------------------------------------------------------------------------------------------------------
void TXbCPItem::Put(TXbCPItem* p) { init(); m_con = _conPut(m_con, (p ? p->Get() : 0)); }
// -----------------------------------------------------------------------------------------------------------------
BOOL TXbCPItem::PutEmptyData(ULONG nType, LONG nLen, LONG nDec)
{
   if (m_pLockStr) return FALSE;
   m_con = _conPutEmptyData(m_con, nType, nLen, nDec);
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TXbCPItem::resize(ULONG nNewSize)
{
   if (m_pLockStr) return FALSE;
   m_nType = GetType();

   if (m_nType & XPP_CHARACTER)
   {
      return (BOOL)(_conResizeC(m_con, nNewSize) == 0);
   }
   if (m_nType & XPP_ARRAY)
   {
      return (BOOL)(_conResizeA(m_con, nNewSize) == 0);
   }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
ULONG TXbCPItem::con_size(void)
{
   ULONG nSize = 0;
   if (m_pLockStr) return 0;
   m_nType = GetType();
   if (m_nType & XPP_CHARACTER)
   {
      _conSizeC(m_con, &nSize);
      return nSize;
   }
   if (m_nType & XPP_ARRAY)
   {
      _conSizeA(m_con, &nSize, 0);
      return nSize;
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle TXbCPItem::operator[](DWORD n)
{
   if (!CheckType(XPP_ARRAY)) return 0;
   if (n < 0) return 0;
   if (n >= (int)con_size()) return 0;
   ContainerHandle p = _conNew(NULLCONTAINER);
   _conArrayGet(con(), p, n + 1, 0);
   return p;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TXbCPItem::GetBool(void)
{
   BOOL bValue = FALSE;
   init();
   if (m_con != NULLCONTAINER) { if (_conGetL(m_con, &bValue) == 0) return bValue; }
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
LONG TXbCPItem::GetLong(void)
{
   LONG nValue = 0;
   init();
   if (m_con != NULLCONTAINER) { if (_conGetLong(m_con, &nValue) == 0) return nValue; }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
HANDLE TXbCPItem::GetHandle(void) { return (HANDLE)GetLong(); }
//-----------------------------------------------------------------------------------------------------------------------
LONGLONG TXbCPItem::GetQWord(void)
{
   init();
   if (m_con != NULLCONTAINER)
   {
      if (CheckType(XPP_CHARACTER))
      {
         char sz[sizeof(LONGLONG)];
         LONGLONG* pq = (LONGLONG*)((void*)sz);
         _bset((LPBYTE)sz, 0, sizeof(LONGLONG));
         GetCL(sz, sizeof(LONGLONG));
         return pq[0];
      }
      else if (CheckType(XPP_NUMERIC))
      {
         if (CheckType(_xpp_DOUBLE)) return (LONGLONG)GetDouble();
         else return (LONGLONG)GetLong();
      }
      else if (CheckType(XPP_ARRAY))
      {
         if (_conGetArrayLen(m_con) == 2)
         {
            LARGE_INTEGER li;
            li.LowPart = _conArrayGetNL(m_con, 1, 0);
            li.HighPart = _conArrayGetNL(m_con, 2, 0);
            return li.QuadPart;
         }
      }
      else if (CheckType(XPP_OBJECT))
      {
         char sz[sizeof(LONGLONG)];
         LONGLONG* pq = (LONGLONG*)((void*)sz);
         _bset((LPBYTE)sz, 0, sizeof(LONGLONG));
         _conGetCLMember(m_con, "Q", sz, sizeof(LONGLONG));
         return pq[0];
      }
   }
   return (LONGLONG)0;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutQWord(LONGLONG q)
{
   init();
   PutStrLen((LPSTR)((void*)&q), sizeof(LONGLONG));
}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutQWordAsNumeric(LONGLONG value)
{
   if (value & 0xFFFFFFFF80000000ll)
   {
      PutDouble((double)value);
   }
   else
   {
      PutLong((LONG)(value & 0xFFFFFFFFll));
   }
}
//----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
DWORD TXbCPItem::GetDWord(void) { return (DWORD)GetLong(); }
//----------------------------------------------------------------------------------------------------------------------
WORD TXbCPItem::GetWord(void) { return (WORD)GetLong(); }
//----------------------------------------------------------------------------------------------------------------------
double TXbCPItem::GetDouble(void)
{
   double nValue = (double)0;
   init();
   if (m_con != NULLCONTAINER) { if (_conGetND(m_con, &nValue) == 0) return nValue; }
   return (double)0;
}
//----------------------------------------------------------------------------------------------------------------------
FLOAT TXbCPItem::GetFloat(void) { return (FLOAT)GetDouble(); }
// ---------------------------------------------------------------------------------------------------------------------
LONGLONG TXbCPItem::GetSqlStrMoney(void)
{
   LONGLONG qn = 0LL;
   init();
   if (m_con != NULLCONTAINER)
   {
      switch (GetType() & 0xFF)
      {
         case XPP_NUMERIC:
         {
            if (CheckType(_xpp_DOUBLE))
            {
               qn = llround(this->GetDouble() * 100.00);
            }
            else
            {
               qn = ((LONGLONG)GetLong()) * 100LL;
            }
            break;
         }
         case XPP_CHARACTER:
         {
            char buffer[1024];
            DWORD buffer_cb;
            ZeroMemory(buffer, sizeof(buffer));
            buffer_cb = GetCL(buffer, sizeof(buffer) - 1);
            __sqlstr_str2money(buffer, buffer_cb, qn);
            break;
         }
         default:
         {
            break;
         }
      }
   }
   return qn;

}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutBool(BOOL bValue)
{
   init();
   m_con = _conPutL(m_con, bValue);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutLong(LONG nValue)
{
   init();
   m_con = _conPutNL(m_con, nValue);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutDWord(DWORD nValue)
{
   init();
   m_con = _conPutNL(m_con, (LONG)nValue);
}
//-----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutWord(WORD nValue)
{
   init();
   m_con = _conPutNL(m_con, (WORD)nValue);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutDouble(double ndValue)
{
   init();
   m_con = _conPutND(m_con, ndValue);

}
// -----------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutSqlStrMoney(LONGLONG qn, DWORD flags, DWORD pad)
{
   char buffer[1024];
   DWORD buffer_cb;
   BOOL bMinus = (qn < 0LL ? 1 : 0);
   if (bMinus) { qn = qn * -1LL; }
   ZeroMemory(buffer, sizeof(buffer));
   buffer_cb = snprintf(buffer, sizeof(buffer) - 32, "%lli", qn);


   if (buffer_cb < 3)
   {
      buffer_cb = snprintf(buffer, sizeof(buffer) - 32, "%03.3lli", qn);
   }
   if ((buffer_cb > 2) && (buffer_cb < sizeof(buffer)))    // added this ALWAYS TRUE condition because intellisense fucking arround over a fake possible buffer overrun
   {
      buffer[buffer_cb] = buffer[buffer_cb - 1];
      buffer[buffer_cb - 1] = buffer[buffer_cb - 2];
      buffer[buffer_cb - 2] = '.';
      buffer_cb++;
   }

   if (bMinus)
   {
      if (!flags)
      {
         _bcopy_no_overlap(_mk_ptr_(LPBYTE, buffer, 1), _mk_ptr_(LPBYTE, buffer, 0), buffer_cb);
         buffer_cb++; buffer[buffer_cb] = 0;
         buffer[0] = '-';
      }
      else
      {
         if (flags & 2)
         {
            buffer[buffer_cb] = ' '; buffer_cb++; buffer[buffer_cb] = 0;
            buffer[buffer_cb] = (flags & 0x10 ? 'H' : 'C'); buffer_cb++; buffer[buffer_cb] = 0;
            if (flags & 0x20)
            {
               buffer[buffer_cb] = (flags & 0x10 ? 'b' : 'r');  buffer_cb++; buffer[buffer_cb] = 0;
            }
         }
      }
   }
   else
   {
      if (flags & 4)
      {
         buffer[buffer_cb] = ' '; buffer_cb++; buffer[buffer_cb] = 0;
         buffer[buffer_cb] = 'D'; buffer_cb++; buffer[buffer_cb] = 0;
         if (flags & 0x20)
         {
            buffer[buffer_cb] = 'b';  buffer_cb++; buffer[buffer_cb] = 0;
         }
      }
   }
   if (pad > buffer_cb)
   {
      pad -= buffer_cb;
      _bcopy_no_overlap(_mk_ptr_(LPBYTE, buffer, pad), _mk_ptr_(LPBYTE, buffer, 0), buffer_cb);
      _bset(_mk_ptr_(LPBYTE, buffer, 0), 0x20, pad);
      buffer_cb += pad;
   }
   PutStrLen(buffer, buffer_cb);

}
// -----------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutDoubleFormat(double ndValue, int nDigits, int nDec)
{
   init();
   m_con = _conPutNDF(m_con, ndValue, nDigits, nDec);
}
// -----------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutDateString(LPSTR ds)
{
   init();
   m_con = _conPutDS(m_con, ds);
}
// -----------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutJulianDate(DWORD dw)
{
   init();
   m_con = _conPutDJ(m_con, dw);
}
// -----------------------------------------------------------------------------------------------------------------
DWORD TXbCPItem::GetJulianDate(void)
{
   DWORD dw = 0;
   init();
   if (m_con != NULLCONTAINER)
   {
      if (_conGetDJ(m_con, &dw) == 0) return dw;
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
void TXbCPItem::GetDateString(LPSTR ds)
{
   init();
   if (ds)
   {
      ZeroMemory(ds, 8);
      if (m_con != NULLCONTAINER)
      {
         _conGetDS(m_con, ds);
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
LPCSTR TXbCPItem::GetDateString(void)
{
   LPCSTR ds = m_date_buffer;
   ZeroMemory(m_date_buffer, sizeof(m_date_buffer));
   GetDateString((LPSTR) ds);
   return ds;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutFloat(FLOAT nfValue)
{
   double ndValue = (double)nfValue;
   init();
   m_con = _conPutND(m_con, ndValue);
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbCPItem::StrDupA(ULONG* pnLen)
{
   LPSTR pDst = 0;
   ULONG nLen = 0;
   init();
   if (m_con != NULLCONTAINER)
   {
      LPSTR pSrc = 0;
      if (ot4xb_conRLockC(m_con, &pSrc, &nLen) == 0)
      {
         pDst = (LPSTR)_xgrab(nLen + 1);
         _bcopy((LPBYTE)pDst, (LPBYTE)pSrc, nLen);
         ot4xb_conUnlockC(m_con);
      }
   }
   if (pnLen != 0) pnLen[0] = nLen;
   return pDst;
}
//----------------------------------------------------------------------------------------------------------------------
LPWSTR TXbCPItem::StrDupW(ULONG* pnBytes)
{
   LPWSTR pw = 0;
   ULONG nLen = 0;
   ULONG nWBytes = 0;
   init();
   if (m_con != NULLCONTAINER)
   {
      LPSTR pSrc = 0;
      if (ot4xb_conRLockC(m_con, &pSrc, &nLen) == 0)
      {
         pw = ansi2w(pSrc, nLen, (int*)&nWBytes);
         ot4xb_conUnlockC(m_con);
      }
   }
   if (pnBytes != 0) pnBytes[0] = nWBytes;
   return pw;
}
// -----------------------------------------------------------------------------------------------------------------
BSTR TXbCPItem::StrDupBSTR(void)
{
   BSTR pw = 0;
   ULONG nLen = 0;
   init();
   if (m_con != NULLCONTAINER)
   {
      LPSTR pSrc = 0;
      if (ot4xb_conRLockC(m_con, &pSrc, &nLen) == 0)
      {
         pw = pAnsi2BSTR(pSrc, nLen);
         ot4xb_conUnlockC(m_con);
      }
   }
   return pw;
}

//----------------------------------------------------------------------------------------------------------------------
ULONG TXbCPItem::GetCL(LPSTR pDst, ULONG nBuffSize)
{
   ULONG nBytes = 0;
   if (pDst)
   {
      init();
      if (m_con != NULLCONTAINER)
      {
         _conGetCL(m_con, &nBytes, pDst, nBuffSize);
      }
   }
   return nBytes;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutStrLen(LPSTR pStr, ULONG nLen)
{
   init();
   m_con = _conPutCL(m_con, pStr, nLen);
}
// -----------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutBSTR2a(BSTR bs)
{
   init();
   if (bs)
   {
      int   cb = 0;
      LPSTR p = w2ansi((LPWSTR)bs, (int)SysStringLen(bs), &cb);
      if (p)
      {
         m_con = _conPutCL(m_con, p, (ULONG)cb);
         _xfree((void*)p);
         return;
      }
   }
   m_con = _conPutC(m_con, "");
}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutStr(LPSTR pStr)
{
   init();
   if (pStr)
   {
      m_con = _conPutC(m_con, pStr);
   }
   else
   {
      m_con = _conPutC(m_con, "");
   }
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbCPItem::LockStr(ULONG* pnSize, BOOL bWrite)
{
   init();
   if ((m_con == NULLCONTAINER) || (m_pLockStr != 0)) return (LPSTR)0;
   if (!CheckType(XPP_CHARACTER)) return (LPSTR)0;
   m_nLockLen = 0;
   m_bLockW = bWrite;
   if ((bWrite ? ot4xb_conWLockC(m_con, &m_pLockStr, &m_nLockLen) : ot4xb_conRLockC(m_con, &m_pLockStr, &m_nLockLen)) != 0)
   {
      m_pLockStr = 0; m_nLockLen = 0; m_bLockW = FALSE;
   }
   if (pnSize != 0) pnSize[0] = m_nLockLen;
   return m_pLockStr;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::UnlockStr(void)
{
   if (m_con == NULLCONTAINER) return;
   if (m_pLockStr == 0) return;
   m_pLockStr = 0; m_nLockLen = 0; m_bLockW = FALSE;
   ot4xb_conUnlockC(m_con);
}
//----------------------------------------------------------------------------------------------------------------------
HWND TXbCPItem::GetHWND(void)
{
   init();
   if (m_con == NULLCONTAINER)   return 0;
   if (CheckType(XPP_NUMERIC)) return (HWND)GetLong();
   if (CheckType(XPP_OBJECT)) return (HWND)_conMCallLong(m_con, "GetHWND");
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------
UINT TXbCPItem::ExLen(void) { return m_nLockLen; }
// -----------------------------------------------------------------------------------------------------------------
LPSTR TXbCPItem::LockStrEx(BOOL bWrite) { return _LockStrEx_(bWrite, 0); }
// -----------------------------------------------------------------------------------------------------------------
LPSTR TXbCPItem::RLockStrEx(void) { return _LockStrEx_(FALSE, 0); }
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbCPItem::WLockStrEx(void) { return _LockStrEx_(TRUE, 0); }
// -----------------------------------------------------------------------------------------------------------------
LPSTR TXbCPItem::RLockStrExF(void) { return _LockStrEx_(FALSE, 1); }
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbCPItem::WLockStrExF(void) { return _LockStrEx_(TRUE, 1); }
// -----------------------------------------------------------------------------------------------------------------
LPSTR TXbCPItem::RLockStrExF8(void) { return _LockStrEx_(FALSE, 2); }
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbCPItem::WLockStrExF8(void) { return _LockStrEx_(TRUE, 2); }
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbCPItem::_LockStrEx_(BOOL bWrite, DWORD nCntType)
{
   init();
   m_nType = GetType();
   m_nCntType = nCntType;

   if (m_pLockStr) return  NULL; // Nested Locks not allowed
   m_bStrLockEx = FALSE;
   if (!(m_nType & (XPP_NUMERIC | XPP_CHARACTER | XPP_ARRAY | XPP_OBJECT))) return NULL;
   else
   {
      if (m_nType & XPP_OBJECT)
      {
         m_pLockStr = (LPSTR)_conMCallLong(m_con, "_lock_", &m_nLockLen);
         m_bStrLockEx = TRUE;
         m_bLockW = bWrite;
         return m_pLockStr;
      }
      else if (m_nType & XPP_CHARACTER)
      {
         LockStr(NULL, bWrite);
         m_bStrLockEx = FALSE;
         m_bLockW = bWrite;
         return m_pLockStr;
      }
      else if (m_nType & XPP_NUMERIC)
      {
         LONG nn = 0;
         _conGetLong(m_con, &nn);
         m_nLockLen = 0;
         m_bStrLockEx = FALSE;
         return (LPSTR)nn;
      }
      else if (m_nType & XPP_ARRAY)
      {
         m_bStrLockEx = TRUE;
         m_bLockW = bWrite;
         m_pLockStr = _cona_LockStrEx_(m_con, &m_pComplex, &m_nLockLen, m_nCntType);
         if (!bWrite) _delete_complex_array_index_(&m_pComplex);
         return m_pLockStr;
      }
   }
   return NULL;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbCPItem::UnLockStrEx(void)
{
   if (m_pLockStr)
   {
      m_nType = GetType();
      if (m_nType & XPP_OBJECT)
      {
         _conMCallVoid(m_con, "_unlock_");
      }
      else if (m_nType & XPP_CHARACTER)
      {
         UnlockStr();
      }
      else if (m_nType & XPP_ARRAY)
      {
         if (m_pLockStr)
         {
            if (m_bLockW)
            {
               _cona_UnLockStrEx_(m_con, &m_pComplex, &m_pLockStr, m_nCntType, m_bLockW);
            }
            else
            {
               _xfree(m_pLockStr); m_pLockStr = 0;
            }
         }
      }
   }
   m_pLockStr = NULL;
   m_nLockLen = 0;
   m_bStrLockEx = FALSE;
   m_bLockW = FALSE;
   _delete_complex_array_index_(&m_pComplex); // por si acaso
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TXbCPItem::GetGuid(GUID* pDst)
{
   if (pDst)
   {
      if (CheckType(XPP_CHARACTER))
      {
         char sz[64];
         ZeroMemory(sz, 64);
         ULONG n = GetCL(sz, 64);
         if (n == sizeof(UUID)) { CopyMemory(pDst, sz, sizeof(UUID)); return TRUE; }
         if (n >= 36)
         {
            UUID Id;
            LPSTR pStr = sz;
            if (pStr[0] == '{')
            {
               pStr++;
               for (n = 0; pStr[n]; n++) { if (pStr[n] == '}') pStr[n] = 0; }
            }
            if (UuidFromString((LPBYTE)pStr, &Id) == RPC_S_OK)
            {
               CopyMemory(pDst, &Id, sizeof(UUID));
               return TRUE;
            }
         }
      }
      else
      {
         UUID* pId = (UUID*)RLockStrEx();
         if (pId) CopyMemory(pDst, pId, sizeof(UUID));
         UnLockStrEx();
         if (pId) return TRUE;
      }
   }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TXbCPItem::PutGuid(GUID* pSrc, BOOL bBraces)
{
   BOOL bOk = FALSE;
   if (pSrc)
   {
      LPBYTE  pStr = 0;
      bOk = (UuidToString(pSrc, &pStr) == RPC_S_OK);
      if (bOk)
      {
         if (bBraces)
         {
            char   sz[64];
            ZeroMemory(sz, 64);
            wsprintf(sz, "{%s}", pStr);
            PutStr(sz);
         }
         else   PutStr((LPSTR)pStr);
      }
      RpcStringFree(&pStr);
   }
   return bOk;
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR TXbCPItem::str(void)
{
   if (m_pLockStr) return m_pLockStr;
   return LockStr();
}
// -----------------------------------------------------------------------------------------------------------------
void TXbCPItem::setprop_ansi2wide(LPWSTR* ppw)
{
   if (*ppw) { _xfree((void*)*ppw); *ppw = 0; }
   if (CheckType(XPP_CHARACTER))
   {
      ULONG cb = 0;
      LPSTR p = LockStr(&cb);
      *ppw = ansi2w(p, cb);
      UnlockStr();
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TXbCPItem::getprop_wide2ansi(LPWSTR* ppw)
{
   if (*ppw)
   {
      LPSTR p = w2ansi(*ppw);
      PutStr(p);
      _xfree((void*)p);
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutDwArray(DWORD* pdw, DWORD cc)
{
   UnLockStrEx();
   if (!pdw) { cc = 0; }
   ContainerHandle cona = _conNewArray(1, cc);
   DWORD dw;
   for (dw = 0; dw < cc; dw++)
   {
      ContainerHandle con = _conPutNL(NULLCONTAINER, (LONG)pdw[dw]);
      int dm[2]; dm[0] = (int)(dw + 1); dm[1] = 0;
      _conArrayPutA(cona, con, dm);
      _conRelease(con);
   }
   Put(cona);
   _conRelease(cona);
}
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
void TXbCPItem::PutNewArray(ULONG nDim, ...)
{
   ContainerHandle cona = NULLCONTAINER;
   UnLockStrEx();
   _asm
   {
      mov eax, nDim
      and eax, eax
      jz  label_2
      mov eax, nDim
      shl eax, 2
      lea ecx, nDim
      add eax, ecx
      label_1 :
      push[eax]
         sub  eax, 4
         cmp  eax, ecx
         jae  label_1
         call _conNewArray
         mov  cona, eax
         mov  eax, nDim
         inc  eax
         shl eax, 2
         add esp, eax
         label_2 :
   }
   Put(cona);
   if (cona) { _conRelease(cona); }
}
// -----------------------------------------------------------------------------------------------------------------
