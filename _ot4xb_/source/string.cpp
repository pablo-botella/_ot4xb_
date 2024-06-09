//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma optimize( "t", on )
#include <ot4xb_api.h>
#include <regex>
#include <string>
#include <atlenc.h>
//----------------------------------------------------------------------------------------------------------------------
#define MSNIBBLE( ch ) (( ch >> (BYTE) 4) & (BYTE)0x0F)
#define LSNIBBLE( ch ) ( ch & (BYTE)0x0F)
//----------------------------------------------------------------------------------------------------------------------
static char  _pStaticYesNoChar_[] = "Y\0N\0";
// -----------------------------------------------------------------------------------------------------------------
static LONG _cHex2Bin_Ex_Mode_ = 1;
//----------------------------------------------------------------------------------------------------------------------
#include "crc32.hpp"
//----------------------------------------------------------------------------------------------------------------------
typedef union DWCHARUNION__union
{
   BYTE  ch[4];
   DWORD dw;
   int   i;
}  DWCHARUNION;
//----------------------------------------------------------------------------------------------------------------------
typedef union QWCHARUNION__union
{
   BYTE     ch[8];
   LONGLONG qw;
}  QWCHARUNION;
//----------------------------------------------------------------------------------------------------------------------
static BYTE __HEXNIBBLE__[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
// -----------------------------------------------------------------------------------------------------------------
static BYTE __DEFAULT_WHITE_SPACE_TABLE__[] = { 0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

// -----------------------------------------------------------------------------------------------------------------
static BYTE __SAFECHAR__[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                        0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
                        0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
// -----------------------------------------------------------------------------------------------------------------
static BYTE __NIBBLECHAR__[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
// ---------------------------------------------------------------------------------------------------------------------
static BYTE __TEMPLATE_09_AZ_NOCASE__[] = { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                                 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
                                 0x40, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
                                 0x60, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
                                 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
                                 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
                                 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
                                 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF };
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NCRC32(XppParamList pl) // nCRC32(nCRC32,cBuffer,[nLen],[[@]nStart]) -> nCRC32 | OnError -> NIL
{
   DWCHARUNION dwu;
   BOOL        bByRef;
   ContainerHandle conStr = _conParam(pl, 2, &bByRef);
   ULONG       nBuffLen, nLen;
   LPBYTE      pStr;
   ULONG       nStart = _parLong(pl, 4);

   if (ot4xb_conRLockC(conStr, (LPSTR*)&pStr, &nBuffLen) != 0) {
      if (!bByRef) {
         _conRelease(conStr);
      } _ret(pl); return;
   }
   if (nStart > 0)
   {
      if (nStart >= nBuffLen) {
         ot4xb_conUnlockC(conStr); if (!bByRef) {
            _conRelease(conStr);
         } _ret(pl); return;
      }
      nLen = ((_partype(pl, 3) & XPP_NUMERIC) ? (ULONG)_parLong(pl, 3) : nBuffLen - nStart);
      if (nStart + nLen > nBuffLen) {
         ot4xb_conUnlockC(conStr); if (!bByRef) {
            _conRelease(conStr);
         } _ret(pl); return;
      }
      pStr += nStart;  nBuffLen -= nStart;
   }
   else
   {
      nLen = ((_partype(pl, 3) & XPP_NUMERIC) ? (ULONG)_parLong(pl, 3) : nBuffLen);
      if (nLen > nBuffLen) {
         ot4xb_conUnlockC(conStr); if (!bByRef) {
            _conRelease(conStr);
         } _ret(pl); return;
      }
   }
   dwu.i = _parLong(pl, 1);
   dwu.dw = dwCrc32(dwu.dw, pStr, nLen);
   ot4xb_conUnlockC(conStr); if (!bByRef)_conRelease(conStr);
   _stornl(nStart + nLen, pl, 4, 0);
   _stornl(dwu.i, pl, 1, 0);
   _retnl(pl, dwu.i);
   return;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD __cdecl dwCrc8(DWORD dwCrc, char* data, int length);
XPPRET XPPENTRY NCRC8(XppParamList pl) // nCRC8(nCRC8,cBuffer,[nLen],[[@]nStart]) -> nCRC8 | OnError -> NIL
{
   DWCHARUNION dwu;
   BOOL        bByRef;
   ContainerHandle conStr = _conParam(pl, 2, &bByRef);
   ULONG       nBuffLen, nLen;
   LPBYTE      pStr;
   ULONG       nStart = _parLong(pl, 4);

   if (ot4xb_conRLockC(conStr, (LPSTR*)&pStr, &nBuffLen) != 0) {
      if (!bByRef) {
         _conRelease(conStr);
      } _ret(pl); return;
   }
   if (nStart > 0)
   {
      if (nStart >= nBuffLen) {
         ot4xb_conUnlockC(conStr); if (!bByRef) {
            _conRelease(conStr);
         } _ret(pl); return;
      }
      nLen = ((_partype(pl, 3) & XPP_NUMERIC) ? (ULONG)_parLong(pl, 3) : nBuffLen - nStart);
      if (nStart + nLen > nBuffLen) {
         ot4xb_conUnlockC(conStr); if (!bByRef) {
            _conRelease(conStr);
         } _ret(pl); return;
      }
      pStr += nStart;  nBuffLen -= nStart;
   }
   else
   {
      nLen = ((_partype(pl, 3) & XPP_NUMERIC) ? (ULONG)_parLong(pl, 3) : nBuffLen);
      if (nLen > nBuffLen) {
         ot4xb_conUnlockC(conStr); if (!bByRef) {
            _conRelease(conStr);
         } _ret(pl); return;
      }
   }
   dwu.i = _parLong(pl, 1);
   dwu.dw = dwCrc8(dwu.dw, (LPSTR)pStr, (int)nLen);
   ot4xb_conUnlockC(conStr); if (!bByRef)_conRelease(conStr);
   _stornl(nStart + nLen, pl, 4, 0);
   _stornl(dwu.i, pl, 1, 0);
   _retnl(pl, dwu.i);
   return;
}
//----------------------------------------------------------------------------------------------------------------------






//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CHRR(XppParamList pl) // ChrR(ch,...,n) // Ex: ? Chrr(13,10,2) //-> CRLF + CRLF
{
   ULONG nParams = (ULONG)_partype(pl, 0);
   if (nParams > 1)
   {
      ULONG nRep = (ULONG)_parLong(pl, nParams);
      ULONG nLen = (ULONG)((nParams - 1) * nRep);
      LPSTR pStr = (LPSTR)_xgrab(nLen);
      ULONG np;
      nParams--;
      for (np = 0; np < nParams; np++)
      {
         char ch = (char)_parLong(pl, np + 1);
         ULONG n, nn;
         for (nn = 0, n = np; nn < nRep; nn++, n += nParams) pStr[n] = ch;
      }
      _retclen(pl, pStr, nLen);
      _xfree((void*)pStr);
   }
   else if (nParams == 1) // Chrr(13) == Chr(13)
   {
      char ch = (char)_parLong(pl, 1);
      _retclen(pl, &ch, 1);
   }
   else _retc(pl, "");


}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY MKSCSTR(XppParamList pl) // MkScStr(nCh,cStr)
{

   CON_PLKSTREX plk;
   CHAR  ch = (CHAR)(_parLong(pl, 1, 0) & 0xFF);
   LPSTR pSrc = _conParamRLockStrEx(pl, 2, &plk);
   ULONG nLen = plk.nLen;
   ContainerHandle conr = _conPutC(NULLCONTAINER, "");
   if (pSrc && nLen)
   {

      WORD* pw = (WORD*)_xgrab(nLen * 2);
      ULONG n;
      for (n = 0; n < nLen; n++) pw[n] = MAKEWORD(ch, pSrc[n]);
      _conPutCL(conr, (LPSTR)pw, (nLen * 2));
      _xfree((void*)pw);
   }
   _conParamUnLockStrEx(&plk);
   _conReturn(pl, conr);
   _conRelease(conr);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LSTRBITSET(XppParamList pl) //lStrBitSet(1@cStr,2nBit[,3lNewSetting])
{
   ULONG nBit = (ULONG)_parLong(pl, 2);
   if (nBit > 0)
   {
      ULONG nByte = (ULONG)((nBit - 1) >> 3);
      BOOL  bByRef = FALSE;
      ContainerHandle conStr = _conParam(pl, 1, &bByRef);
      LPBYTE pStr = (LPBYTE)0;
      ULONG nLen = 0;
      BOOL  bWrite = (BOOL)(_partype(pl, 0) > 2);
      BYTE  chMask;
      BYTE ch;
      BOOL bOn;

      if (conStr == NULLCONTAINER) {
         _ret(pl); return;
      } // Error: missing 1st parameter
      if (bWrite)
      {
         if (ot4xb_conWLockC(conStr, (LPSTR*)&pStr, &nLen) != 0)
         {
            _ret(pl);
            if (!bByRef) _conRelease(conStr);
            return; // Error: error while locking the write pointer
         }
      }
      else if (ot4xb_conRLockC(conStr, (LPSTR*)&pStr, &nLen) != 0)
      {
         if (!bByRef) _conRelease(conStr);
         _ret(pl); return; // Error: error while locking the read pointer
      }
      if (nByte >= nLen)
      {
         ot4xb_conUnlockC(conStr);
         if (!bByRef) _conRelease(conStr);
         _retl(pl, FALSE); return; // .F. request position exceds the string length
      }
      chMask = (BYTE)((BYTE)(0x01) << (BYTE)((nBit - 1) - (nByte << 3)));
      ch = (BYTE)pStr[nByte];
      bOn = (BOOL)(ch & chMask);
      if (bWrite)
      {
         BOOL bSet = (BOOL)_parl(pl, 3);
         if (bSet) pStr[nByte] |= chMask;
         else if (bOn) pStr[nByte] ^= chMask;
      }
      ot4xb_conUnlockC(conStr);
      if (!bByRef) _conRelease(conStr);
      _retl(pl, bOn);
   }
   else _ret(pl);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LPSTRBITSET(XppParamList pl) //lPStrBitSet(1LPSTR,2nBit,[3lNewSetting],[4nLen])
{
   ULONG nBit = (ULONG)_parLong(pl, 2);
   if (nBit > 0)
   {
      ULONG nByte = (ULONG)((nBit - 1) >> 3);
      LPBYTE pStr = (LPBYTE)_parLong(pl, 1);
      ULONG nLen = (ULONG)((_partype(pl, 4) & XPP_NUMERIC) ? _parLong(pl, 4) : ((ULONG)-1));
      BOOL  bWrite = (BOOL)(_partype(pl, 3) & XPP_LOGICAL);
      BYTE  chMask;
      BYTE ch;
      BOOL bOn;

      if ((nByte >= nLen) || (pStr == 0))
      {
         _ret(pl); return; // Error request position exceds the string length
      }
      chMask = (BYTE)((BYTE)(0x01) << (BYTE)((nBit - 1) - (nByte << 3)));
      ch = (BYTE)pStr[nByte];
      bOn = (BOOL)(ch & chMask);
      if (bWrite)
      {
         BOOL bSet = (BOOL)_parl(pl, 3);
         if (bSet) pStr[nByte] |= chMask;
         else if (bOn) pStr[nByte] ^= chMask;
      }
      _retl(pl, bOn);
   }
   else _ret(pl);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CSTRBITNOT(XppParamList pl) //cStrBitNot(1@cStr)
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conTParam(pl, 1, &bByRef, XPP_CHARACTER);
   if (con != NULLCONTAINER)
   {
      LPSTR pStr = (LPSTR)0;
      ULONG nLen = 0;
      if (ot4xb_conWLockC(con, &pStr, &nLen) == 0)
      {
         ULONG n;
         CHAR  ch = -1;
         for (n = 0; n < nLen; n++) pStr[n] ^= ch;
         ot4xb_conUnlockC(con);
         _conReturn(pl, con);
         if (!bByRef) _conRelease(con);
      }
      else {
         if (!bByRef) {
            _conRelease(con);
         } _ret(pl); return;
      }
   }
   else {
      _ret(pl); return;
   }

}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PSTRBITNOT(XppParamList pl) //PStrBitNot(1pStr,2nLen) -> pStr
{
   LPSTR pStr = (LPSTR)_parLong(pl, 1);
   ULONG nLen = (ULONG)_parLong(pl, 2);
   if ((pStr != 0) && (nLen != 0))
   {
      ULONG n;
      CHAR  ch = -1;
      for (n = 0; n < nLen; n++) pStr[n] ^= ch;
   }
   _retnl(pl, (LONG)pStr);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CSTRBITOR(XppParamList pl) //cStrBitOR(1@cStr,2[@]cStr,3lRotate:=.F.)
{
   BOOL bOk = FALSE;
   BOOL bStrByRef = FALSE;
   BOOL bRotate = (BOOL)_parl(pl, 3);
   ContainerHandle conStr = _conTParam(pl, 1, &bStrByRef, XPP_CHARACTER);
   if (conStr != NULLCONTAINER)
   {
      BOOL bStr2ByRef = FALSE;
      ContainerHandle conStr2 = _conTParam(pl, 2, &bStr2ByRef, XPP_CHARACTER);
      if (conStr2 != NULLCONTAINER)
      {
         LPSTR pStr = (LPSTR)0;
         ULONG nLen = 0;
         LPSTR pStr2 = (LPSTR)0;
         ULONG nLen2 = 0;
         if (ot4xb_conWLockC(conStr, &pStr, &nLen) == 0)
         {
            if (ot4xb_conRLockC(conStr2, &pStr2, &nLen2) == 0)
            {
               ULONG n;
               if ((nLen <= nLen2) || (nLen2 == 0)) bRotate = FALSE;
               if (bRotate)
               {
                  ULONG nn = 0;
                  for (n = 0; n < nLen; n++) {
                     pStr[n] |= pStr2[nn]; nn++; if (nn >= nLen2) nn = 0;
                  }
               }
               else
               {
                  if (nLen > nLen2) nLen = nLen2;
                  for (n = 0; n < nLen; n++) pStr[n] |= pStr2[n];
               }
               ot4xb_conUnlockC(conStr2);
               bOk = TRUE;
            }
            ot4xb_conUnlockC(conStr);
         }
         if (!bStr2ByRef) _conRelease(conStr2);
      }
      if (bOk) _conReturn(pl, conStr); else _ret(pl);
      if (!bStrByRef) _conRelease(conStr);
      return;
   }
   _ret(pl);
   return;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CSTRBITXOR(XppParamList pl) //cStrBitXOR(1@cStr,2[@]cStr,3lRotate:=.F.)
{
   BOOL bOk = FALSE;
   BOOL bStrByRef = FALSE;
   BOOL bRotate = (BOOL)_parl(pl, 3);
   ContainerHandle conStr = _conTParam(pl, 1, &bStrByRef, XPP_CHARACTER);
   if (conStr != NULLCONTAINER)
   {
      BOOL bStr2ByRef = FALSE;
      ContainerHandle conStr2 = _conTParam(pl, 2, &bStr2ByRef, XPP_CHARACTER);
      if (conStr2 != NULLCONTAINER)
      {
         LPSTR pStr = (LPSTR)0;
         ULONG nLen = 0;
         LPSTR pStr2 = (LPSTR)0;
         ULONG nLen2 = 0;
         if (ot4xb_conWLockC(conStr, &pStr, &nLen) == 0)
         {
            if (ot4xb_conRLockC(conStr2, &pStr2, &nLen2) == 0)
            {
               ULONG n;
               if ((nLen <= nLen2) || (nLen2 == 0)) bRotate = FALSE;
               if (bRotate)
               {
                  ULONG nn = 0;
                  for (n = 0; n < nLen; n++) {
                     pStr[n] ^= pStr2[nn]; nn++; if (nn >= nLen2) nn = 0;
                  }
               }
               else
               {
                  if (nLen > nLen2) nLen = nLen2;
                  for (n = 0; n < nLen; n++) pStr[n] ^= pStr2[n];
               }
               ot4xb_conUnlockC(conStr2);
               bOk = TRUE;
            }
            ot4xb_conUnlockC(conStr);
         }
         if (!bStr2ByRef) _conRelease(conStr2);
      }
      if (bOk) _conReturn(pl, conStr); else _ret(pl);
      if (!bStrByRef) _conRelease(conStr);
      return;
   }
   _ret(pl);
   return;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CSTRBITAND(XppParamList pl) //cStrBitAND(1@cStr,2[@]cStr,3lRotate:=.F.)
{
   BOOL bOk = FALSE;
   BOOL bStrByRef = FALSE;
   BOOL bRotate = (BOOL)_parl(pl, 3);
   ContainerHandle conStr = _conTParam(pl, 1, &bStrByRef, XPP_CHARACTER);
   if (conStr != NULLCONTAINER)
   {
      BOOL bStr2ByRef = FALSE;
      ContainerHandle conStr2 = _conTParam(pl, 2, &bStr2ByRef, XPP_CHARACTER);
      if (conStr2 != NULLCONTAINER)
      {
         LPSTR pStr = (LPSTR)0;
         ULONG nLen = 0;
         LPSTR pStr2 = (LPSTR)0;
         ULONG nLen2 = 0;
         if (ot4xb_conWLockC(conStr, &pStr, &nLen) == 0)
         {
            if (ot4xb_conRLockC(conStr2, &pStr2, &nLen2) == 0)
            {
               ULONG n;
               if ((nLen <= nLen2) || (nLen2 == 0)) bRotate = FALSE;
               if (bRotate)
               {
                  ULONG nn = 0;
                  for (n = 0; n < nLen; n++) {
                     pStr[n] &= pStr2[nn]; nn++; if (nn >= nLen2) nn = 0;
                  }
               }
               else
               {
                  if (nLen > nLen2) nLen = nLen2;
                  for (n = 0; n < nLen; n++) pStr[n] &= pStr2[n];
               }
               ot4xb_conUnlockC(conStr2);
               bOk = TRUE;
            }
            ot4xb_conUnlockC(conStr);
         }
         if (!bStr2ByRef) _conRelease(conStr2);
      }
      if (bOk) _conReturn(pl, conStr); else _ret(pl);
      if (!bStrByRef) _conRelease(conStr);
      return;
   }
   _ret(pl);
   return;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PSTRBITOR(XppParamList pl) //PStrBitOR(1p1,2nl1, 3 p2 , 4 nl2 , 5 bRotate )
{
   LPSTR p1 = (LPSTR)_parLong(pl, 1);
   ULONG n1 = (ULONG)_parLong(pl, 2);
   LPSTR p2 = (LPSTR)_parLong(pl, 3);
   ULONG n2 = (ULONG)_parLong(pl, 4);
   BOOL bRotate = (BOOL)((n1 <= n2) ? FALSE : _parl(pl, 5));
   ULONG n, nn;

   if (p1 == 0) {
      _retnl(pl, 0); return;
   }
   if ((n1 == 0) || (n2 == 0) || (p2 == 0)) {
      _retnl(pl, (LONG)p1); return;
   }
   if (bRotate) for (n = nn = 0; n < n1; n++) {
      p1[n] |= p2[nn]; nn++; if (nn >= n2) nn = 0;
   }
   else if (n1 > n2) for (n = 0; n < n2; n++) p1[n] |= p2[n];
   else for (n = 0; n < n1; n++) p1[n] |= p2[n];
   _retnl(pl, (LONG)p1);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PSTRBITXOR(XppParamList pl) //PStrBitXOR(1p1,2nl1, 3 p2 , 4 nl2 , 5 bRotate )
{
   LPSTR p1 = (LPSTR)_parLong(pl, 1);
   ULONG n1 = (ULONG)_parLong(pl, 2);
   LPSTR p2 = (LPSTR)_parLong(pl, 3);
   ULONG n2 = (ULONG)_parLong(pl, 4);
   BOOL bRotate = (BOOL)((n1 <= n2) ? FALSE : _parl(pl, 5));
   ULONG n, nn;

   if (p1 == 0) {
      _retnl(pl, 0); return;
   }
   if ((n1 == 0) || (n2 == 0) || (p2 == 0)) {
      _retnl(pl, (LONG)p1); return;
   }
   if (bRotate) for (n = nn = 0; n < n1; n++) {
      p1[n] ^= p2[nn]; nn++; if (nn >= n2) nn = 0;
   }
   else if (n1 > n2) for (n = 0; n < n2; n++) p1[n] ^= p2[n];
   else for (n = 0; n < n1; n++) p1[n] ^= p2[n];
   _retnl(pl, (LONG)p1);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PSTRBITAND(XppParamList pl) //PStrBitAND(1p1,2nl1, 3 p2 , 4 nl2 , 5 bRotate )
{
   LPSTR p1 = (LPSTR)_parLong(pl, 1);
   ULONG n1 = (ULONG)_parLong(pl, 2);
   LPSTR p2 = (LPSTR)_parLong(pl, 3);
   ULONG n2 = (ULONG)_parLong(pl, 4);
   BOOL bRotate = (BOOL)((n1 <= n2) ? FALSE : _parl(pl, 5));
   ULONG n, nn;

   if (p1 == 0) {
      _retnl(pl, 0); return;
   }
   if ((n1 == 0) || (n2 == 0) || (p2 == 0)) {
      _retnl(pl, (LONG)p1); return;
   }
   if (bRotate) for (n = nn = 0; n < n1; n++) {
      p1[n] &= p2[nn]; nn++; if (nn >= n2) nn = 0;
   }
   else if (n1 > n2) for (n = 0; n < n2; n++) p1[n] &= p2[n];
   else for (n = 0; n < n1; n++) p1[n] &= p2[n];
   _retnl(pl, (LONG)p1);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NSTRBITCOUNT(XppParamList pl) //nStrBitCount(1@cStr)
{
   BOOL bByRef = FALSE;
   ContainerHandle conStr = _conParam(pl, 1, &bByRef);
   LPBYTE p = (LPBYTE)0;
   ULONG  nLen = 0;
   ULONG  nBits = 0;
   ULONG  nByte = 0;
   BYTE   chMask;

   if (conStr == NULLCONTAINER) {
      _retnl(pl, 0); return;
   }
   if (ot4xb_conRLockC(conStr, (LPSTR*)&p, &nLen) != 0)
   {
      if (!bByRef) _conRelease(conStr);
      _ret(pl); return; // Error: error while locking the read pointer
   }
   if (nLen > 0)
   {
      for (nByte = 0; nByte < nLen; nByte++)
      {
         if (p[nByte] != 0) for (chMask = 1; chMask != 0; chMask <<= 1) if ((p[nByte] & chMask) != 0) nBits++;
      }
   }
   ot4xb_conUnlockC(conStr);
   if (!bByRef) _conRelease(conStr);
   _retnl(pl, (LONG)nBits);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY ASTRBITS(XppParamList pl) //aStrBits(1@cStr)
{
   BOOL bByRef = FALSE;
   ContainerHandle conStr = _conParam(pl, 1, &bByRef);
   LPBYTE p = (LPBYTE)0;
   ULONG  nLen = 0;
   ULONG  nBits = 0;
   ULONG  nByte = 0;
   BYTE   chMask;
   ContainerHandle conaBits;

   if (conStr == NULLCONTAINER) {
      _retnl(pl, 0); return;
   }
   if (ot4xb_conRLockC(conStr, (LPSTR*)&p, &nLen) != 0)
   {
      if (!bByRef) _conRelease(conStr);
      _ret(pl); return; // Error: error while locking the read pointer
   }
   if (nLen != 0)
   {
      for (nByte = 0; nByte < nLen; nByte++)
      {
         if (p[nByte] != 0) for (chMask = 1; chMask != 0; chMask <<= 1) if ((p[nByte] & chMask) != 0) nBits++;
      }
   }
   conaBits = _conNewArray(1, nBits);
   if (nBits != 0)
   {
      ULONG n = 0;
      nBits = 0;
      for (nByte = 0; nByte < nLen; nByte++)
      {
         if (p[nByte] == 0) n += 8;
         else
         {
            for (chMask = 1; chMask != 0; chMask <<= 1, n++)
            {
               if ((p[nByte] & chMask) != 0)
               {
                  ContainerHandle con = _conPutNL(NULLCONTAINER, (LONG)n + 1);
                  nBits++;
                  _conArrayPut(conaBits, con, nBits, 0);
                  _conRelease(con);
               }
            }
         }
      }
   }
   ot4xb_conUnlockC(conStr);
   if (!bByRef) _conRelease(conStr);
   _conReturn(pl, conaBits);
   _conRelease(conaBits);
}
//----------------------------------------------------------------------------------------------------------------------
// calculate the CRC32 of a string
// dwCRC must be zero at the first call or the last CRC32 value from the last chunk if
// the CRC32 is calculated in some steps.
OT4XB_API DWORD dwCrc32(DWORD dwCRC, LPBYTE pStr, ULONG nLen)
{
   ULONG n;
   dwCRC = dwCRC ^ 0xFFFFFFFF;
   for (n = 0; n < nLen; n++) {
      dwCRC = C_R_C_32_TABLE[((int)dwCRC ^ (*pStr)) & 0xFF] ^ (dwCRC >> 8); pStr++;
   }

   return(dwCRC ^ 0xFFFFFFFF);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD dwCrc8(DWORD dwCrc, char* data, int length)
{
   char crc = (char)(dwCrc & 0xFF);
   char extract;
   char sum;
   for (int i = 0; i < length; i++)
   {
      extract = *data;
      for (char tempI = 8; tempI; tempI--)
      {
         sum = (crc ^ extract) & 0x01;
         crc >>= 1;
         if (sum)
            crc ^= 0x8C;
         extract >>= 1;
      }
      data++;
   }
   return (DWORD)(crc & 0xFF);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD dwCrc32WithTable(DWORD dwCRC, LPBYTE pStr, ULONG nLen, LPBYTE pTable)
{
   ULONG n;
   dwCRC = dwCRC ^ 0xFFFFFFFF;

   for (n = 0; n < nLen; n++, pStr++)
   {
      BYTE ch = pTable[*pStr];
      dwCRC = C_R_C_32_TABLE[((int)dwCRC ^ ch) & 0xFF] ^ (dwCRC >> 8);
   }
   return(dwCRC ^ 0xFFFFFFFF);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NOCOMMENT(XppParamList pl) // NoComment(<cString>) ->cString
{
   BOOL bByRef = FALSE;
   ContainerHandle conStr = _conTParam(pl, 1, &bByRef, XPP_CHARACTER);
   ContainerHandle conr = _conNew(NULLCONTAINER);
   if (conStr != NULLCONTAINER)
   {
      LPSTR pSrc = NULL;
      int nLen = 0;
      if (ot4xb_conRLockC(conStr, &pSrc, (ULONG*)&nLen) == 0)
      {
         int ns = 0;
         int nd = 0;
         LPSTR  pDst = (LPSTR)_xgrab(nLen + 1);
         while (ns < nLen)
         {
            if (pSrc[ns] == '/')
            {
               if (((WORD)((WORD*)(void*)(pSrc + ns))[0]) == 0x2F2F)  // '/'+'/'
               {
                  for (ns += 2; (ns < nLen) && (pSrc[ns] != 13) && (pSrc[ns] != 10); ns++);
               }
               else if (((WORD)((WORD*)(void*)(pSrc + ns))[0]) == 0x2A2F)  // '/'+'*'
               {
                  for (ns += 2; (ns < nLen) && (((WORD)((WORD*)(void*)(pSrc + ns))[0]) != 0x2F2A); ns++);
                  ns += 2;
               }
               else pDst[nd++] = pSrc[ns++];
            }
            else pDst[nd++] = pSrc[ns++];
         }
         _conPutCL(conr, pDst, nd);
         _xfree((void*)pDst);
         ot4xb_conUnlockC(conStr); pSrc = NULL;
      }
      if (!bByRef)  _conRelease(conStr);
   }
   _conReturn(pl, conr); _conRelease(conr);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BYTE chHex2Nibble(BYTE chHex)
{
   switch (chHex)
   {
      case '0': return(0);
      case '1': return(1);
      case '2': return(2);
      case '3': return(3);
      case '4': return(4);
      case '5': return(5);
      case '6': return(6);
      case '7': return(7);
      case '8': return(8);
      case '9': return(9);
      case 'A':; case 'a': return(10);
      case 'B':; case 'b': return(11);
      case 'C':; case 'c': return(12);
      case 'D':; case 'd': return(13);
      case 'E':; case 'e': return(14);
      case 'F':; case 'f': return(15);
   }
   return(0);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CBIN2HEX(XppParamList pl)
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conTParam(pl, 1, &bByRef, XPP_CHARACTER);
   ContainerHandle conr = _conNew(NULLCONTAINER);
   if (con != NULLCONTAINER)
   {
      LPSTR pBin = NULL;
      ULONG nCb = 0;
      if (ot4xb_conRLockC(con, &pBin, &nCb) == 0)
      {
         ULONG nHexSize = (nCb * 2);
         LPSTR pHex = (LPSTR)_xgrab(nHexSize + 1);
         LPSTR pp = pHex;
         ULONG n;
         for (n = 0; n < nCb; n++)
         {
            *pp++ = __HEXNIBBLE__[MSNIBBLE(pBin[n])];
            *pp++ = __HEXNIBBLE__[LSNIBBLE(pBin[n])];
         }
         ot4xb_conUnlockC(con);
         _conPutCL(conr, pHex, nHexSize);
         _xfree((void*)pHex);
      }
      if (!bByRef) _conRelease(con);
   }
   _conReturn(pl, conr);
   _conRelease(conr);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG ot4xb_CHEX2BIN_defmode_(LONG n)
{
   LONG nn = _cHex2Bin_Ex_Mode_;
   if ((n >= 0) && (n < 3)) _cHex2Bin_Ex_Mode_ = n;
   return nn;
}
//----------------------------------------------------------------------------------------------------------------------
// nExtended == 0 -> !nibbleChar == Chr(0)  && odd nibbles << 4
// nExtended == 1 -> !nibbleChar skiped
// nExtended == 2 -> !nibbleChar skiped &&  byte separator
XPPRET XPPENTRY CHEX2BIN(XppParamList pl)
{
   ULONG nEx = (ULONG)((_partype(pl, 2) & XPP_NUMERIC) ? _parLong(pl, 2, 0) : _cHex2Bin_Ex_Mode_);
   BOOL  bByRef = FALSE;
   ContainerHandle con = _conTParam(pl, 1, &bByRef, XPP_CHARACTER);
   ContainerHandle conr = _conNew(NULLCONTAINER);
   if (con != NULLCONTAINER)
   {
      LPBYTE pHex = NULL;
      ULONG nCb = 0;
      if (ot4xb_conRLockC(con, (LPSTR*)&pHex, &nCb) == 0)
      {
         LPBYTE pp = pHex;
         LPBYTE ppMax = _mk_ptr_(LPBYTE, pHex, nCb);
         LPBYTE pBin = (LPBYTE)_xgrab(((nEx == 2) ? nCb : (nCb >> 1)) + 1);
         LPBYTE p = pBin;
         ULONG cb = 0;
         BOOL  bh;

         for (bh = 0; pp < ppMax; pp++)
         {
            if (__NIBBLECHAR__[*pp] || (nEx == 0))
            {
               if (bh)
               {
                  *p = ((*p << 4) & 0xF0) | (__NIBBLECHAR__[*pp] & 0x0F);
                  p++; bh = 0;
               }
               else
               {
                  *p = (__NIBBLECHAR__[*pp] & 0x0F);
                  cb++; bh = 1;
               }
            }
            else if ((nEx == 2) && bh) {
               bh = 0; p++;
            }
         }
         ot4xb_conUnlockC(con);
         _conPutCL(conr, (LPSTR)pBin, cb);
         _xfree((void*)pBin);
      }
      if (!bByRef) _conRelease(con);
   }
   _conReturn(pl, conr);
   _conRelease(conr);
}

//----------------------------------------------------------------------------------------------------------------------
// TODO: add 3rd param with options about what to do when last token is empty and how to interpret quotes
XPPRET XPPENTRY TOKENIZE(XppParamList pl)
{
   CHAR  szSep[128];
   ULONG cbStr = _parclen(pl, 1);
   ULONG cbSep = _parclen(pl, 2);
   LPSTR pStr = _pszParam(pl, 1);
   LPSTR pSep = (LPSTR)szSep;
   LPSTR p;
   int   nLen;
   int iAt;
   ULONG n, nItems;
   TList* pList = new TList;
   ContainerHandle conr = NULLCONTAINER;


   if (cbSep == 0) {
      pSep[0] = ';'; pSep[1] = 0; cbSep = 1;
   }
   else  _parc(pSep, 128, pl, 2, 0);

   p = pStr; nLen = (int)cbStr;
   iAt = _xstrat(pSep, cbSep, p, cbStr);
   while (iAt != -1)
   {
      pList->Add((void*)iAt);
      nLen -= (iAt + (int)cbSep);
      p += (iAt + (int)cbSep);
      iAt = _xstrat(pSep, cbSep, p, nLen);

   }
   if (nLen > 0) pList->Add((void*)nLen);
   p = pStr;
   nItems = pList->Count();
   conr = _conNewArray(1, nItems);
   for (n = 0; n < nItems; n++)
   {
      ULONG ul = (ULONG)pList->Get(n);
      _conArrayPutCL(conr, p, ul, (n + 1), 0);
      p += (ul + cbSep);
   }
   delete pList; _xfree((void*)pStr);
   _conReturn(pl, conr);
   _conRelease(conr);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY TRIMQUOTES(XppParamList pl)
{
   LPSTR pStr = _pszParam(pl, 1);
   LPSTR pOut = NULL;
   if (pStr)
   {
      LPSTR pp;
      for (pOut = pStr; pOut[0] && ((pOut[0] == 0x20) || (pOut[0] == 0x22)); pOut++);
      for (pp = pOut; pp[0]; pp++);
      pp--;
      while ((pp > pOut) && ((pp[0] == 0x20) || (pp[0] == 0x22))) {
         pp[0] = 0; pp--;
      }
      _retc(pl, pOut);
      _xfree(pStr);
   }
   else _retc(pl, "");
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY TRIMZ(XppParamList pl)
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle conc = _conTParam(pl, 1, 0, XPP_CHARACTER);
   if (conc)
   {
      LPSTR pStr = 0;
      ULONG cb = 0;
      if (ot4xb_conRLockC(conc, &pStr, &cb) == 0)
      {
         _conPutC(conr, pStr);
         ot4xb_conUnlockC(conc);
      }
      _conRelease(conc);
   }
   _conReturn(pl, conr);
   _conRelease(conr);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY C5ALLTRIM(XppParamList pl)
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle conc = _conTParam(pl, 1, 0, XPP_CHARACTER);
   if (conc)
   {
      LPSTR pStr = 0;
      ULONG cb = 0;
      if (ot4xb_conRLockC(conc, &pStr, &cb) == 0)
      {
         for (; cb && (pStr[0] == 0 || pStr[0] == 32); cb--, pStr++);
         for (; cb && (pStr[(cb - 1)] == 0 || pStr[(cb - 1)] == 32); cb--);
         if (cb) _conPutCL(conr, pStr, cb);
         else _conPutC(conr, "");
         ot4xb_conUnlockC(conc);
      }
      _conRelease(conc);
   }
   _conReturn(pl, conr);
   _conRelease(conr);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY C5RTRIM(XppParamList pl)
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle conc = _conTParam(pl, 1, 0, XPP_CHARACTER);
   if (conc)
   {
      LPSTR pStr = 0;
      ULONG cb = 0;
      if (ot4xb_conRLockC(conc, &pStr, &cb) == 0)
      {
         for (; cb && (pStr[(cb - 1)] == 0 || pStr[(cb - 1)] == 32); cb--);
         if (cb) _conPutCL(conr, pStr, cb);
         else _conPutC(conr, "");
         ot4xb_conUnlockC(conc);
      }
      _conRelease(conc);
   }
   _conReturn(pl, conr);
   _conRelease(conr);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY C5LTRIM(XppParamList pl)
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle conc = _conTParam(pl, 1, 0, XPP_CHARACTER);
   if (conc)
   {
      LPSTR pStr = 0;
      ULONG cb = 0;
      if (ot4xb_conRLockC(conc, &pStr, &cb) == 0)
      {
         for (; cb && (pStr[0] == 0 || pStr[0] == 32); cb--, pStr++);
         if (cb) _conPutCL(conr, pStr, cb);
         else _conPutC(conr, "");
         ot4xb_conUnlockC(conc);
      }
      _conRelease(conc);
   }
   _conReturn(pl, conr);
   _conRelease(conr);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CQW2HEX(XppParamList  pl)
{
   ULONG ulType = _partype(pl, 1);
   QWCHARUNION qwu;
   BYTE        pHex[17];
   _bset(qwu.ch, 0, 8);
   if (ulType & XPP_NUMERIC)
   {
      if (ulType & _xpp_DOUBLE)  qwu.qw = (LONGLONG)_parnd(pl, 1, 0);
      else qwu.qw = (0x00000000FFFFFFFF & ((LONGLONG)_parLong(pl, 1, 0)));
   }
   else if (ulType & XPP_ARRAY)
   {
      qwu.qw = ((((LONGLONG)_parLong(pl, 1, 2, 0)) << 32) | (0x00000000FFFFFFFF & ((LONGLONG)_parLong(pl, 1, 1, 0))));
   }
   else
   {
      _bset(pHex, 0, 17);
      _parc((LPSTR)pHex, 17, pl, 1, 0);
      _bcopy(qwu.ch, pHex, 8);
      _bset(pHex, 0, 17);
   }
   pHex[0] = __HEXNIBBLE__[((qwu.ch[7] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[1] = __HEXNIBBLE__[(qwu.ch[7] & (BYTE)0x0F)];
   pHex[2] = __HEXNIBBLE__[((qwu.ch[6] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[3] = __HEXNIBBLE__[(qwu.ch[6] & (BYTE)0x0F)];
   pHex[4] = __HEXNIBBLE__[((qwu.ch[5] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[5] = __HEXNIBBLE__[(qwu.ch[5] & (BYTE)0x0F)];
   pHex[6] = __HEXNIBBLE__[((qwu.ch[4] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[7] = __HEXNIBBLE__[(qwu.ch[4] & (BYTE)0x0F)];
   pHex[8] = __HEXNIBBLE__[((qwu.ch[3] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[9] = __HEXNIBBLE__[(qwu.ch[3] & (BYTE)0x0F)];
   pHex[10] = __HEXNIBBLE__[((qwu.ch[2] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[11] = __HEXNIBBLE__[(qwu.ch[2] & (BYTE)0x0F)];
   pHex[12] = __HEXNIBBLE__[((qwu.ch[1] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[13] = __HEXNIBBLE__[(qwu.ch[1] & (BYTE)0x0F)];
   pHex[14] = __HEXNIBBLE__[((qwu.ch[0] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[15] = __HEXNIBBLE__[(qwu.ch[0] & (BYTE)0x0F)];
   pHex[16] = 0;
   _retc(pl, (LPSTR)pHex);
   return;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NHEX2QW(XppParamList  pl)
{
   char ss[8];
   BYTE        pHex[17];

   _parc((LPSTR)pHex, 17, pl, 1, 0);

   ss[0] = (BYTE)((chHex2Nibble(pHex[14]) << 4) & 0xF0);
   ss[0] |= (chHex2Nibble(pHex[15]) & 0x0F);
   ss[1] = (BYTE)((chHex2Nibble(pHex[12]) << 4) & 0xF0);
   ss[1] |= (chHex2Nibble(pHex[13]) & 0x0F);
   ss[2] = (BYTE)((chHex2Nibble(pHex[10]) << 4) & 0xF0);
   ss[2] |= (chHex2Nibble(pHex[11]) & 0x0F);
   ss[3] = (BYTE)((chHex2Nibble(pHex[8]) << 4) & 0xF0);
   ss[3] |= (chHex2Nibble(pHex[9]) & 0x0F);
   ss[4] = (BYTE)((chHex2Nibble(pHex[6]) << 4) & 0xF0);
   ss[4] |= (chHex2Nibble(pHex[7]) & 0x0F);
   ss[5] = (BYTE)((chHex2Nibble(pHex[4]) << 4) & 0xF0);
   ss[5] |= (chHex2Nibble(pHex[5]) & 0x0F);
   ss[6] = (BYTE)((chHex2Nibble(pHex[2]) << 4) & 0xF0);
   ss[6] |= (chHex2Nibble(pHex[3]) & 0x0F);
   ss[7] = (BYTE)((chHex2Nibble(pHex[0]) << 4) & 0xF0);
   ss[7] |= (chHex2Nibble(pHex[1]) & 0x0F);
   _retclen(pl, ss, 8);

   return;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CDOUBLE2HEX(XppParamList  pl)
{
   double nd = _parnd(pl, 1, 0);
   LPBYTE p = _mk_ptr_(LPBYTE, &nd, 0);
   BYTE   ph[17];
   ph[0] = __HEXNIBBLE__[((p[7] >> (BYTE)4) & (BYTE)0x0F)];
   ph[1] = __HEXNIBBLE__[(p[7] & (BYTE)0x0F)];
   ph[2] = __HEXNIBBLE__[((p[6] >> (BYTE)4) & (BYTE)0x0F)];
   ph[3] = __HEXNIBBLE__[(p[6] & (BYTE)0x0F)];
   ph[4] = __HEXNIBBLE__[((p[5] >> (BYTE)4) & (BYTE)0x0F)];
   ph[5] = __HEXNIBBLE__[(p[5] & (BYTE)0x0F)];
   ph[6] = __HEXNIBBLE__[((p[4] >> (BYTE)4) & (BYTE)0x0F)];
   ph[7] = __HEXNIBBLE__[(p[4] & (BYTE)0x0F)];
   ph[8] = __HEXNIBBLE__[((p[3] >> (BYTE)4) & (BYTE)0x0F)];
   ph[9] = __HEXNIBBLE__[(p[3] & (BYTE)0x0F)];
   ph[10] = __HEXNIBBLE__[((p[2] >> (BYTE)4) & (BYTE)0x0F)];
   ph[11] = __HEXNIBBLE__[(p[2] & (BYTE)0x0F)];
   ph[12] = __HEXNIBBLE__[((p[1] >> (BYTE)4) & (BYTE)0x0F)];
   ph[13] = __HEXNIBBLE__[(p[1] & (BYTE)0x0F)];
   ph[14] = __HEXNIBBLE__[((p[0] >> (BYTE)4) & (BYTE)0x0F)];
   ph[15] = __HEXNIBBLE__[(p[0] & (BYTE)0x0F)];
   ph[16] = 0;
   _retc(pl, (LPSTR)ph);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NHEX2DOUBLE(XppParamList  pl)
{
   double nd = 0.00F;
   LPBYTE p = _mk_ptr_(LPBYTE, &nd, 0);
   BYTE   ph[17];
   _bset(ph, 0, 17);
   _parc((LPSTR)ph, 17, pl, 1, 0);

   p[0] = ((chHex2Nibble(ph[14]) << 4) & 0xF0) | (chHex2Nibble(ph[15]) & 0x0F);
   p[1] = ((chHex2Nibble(ph[12]) << 4) & 0xF0) | (chHex2Nibble(ph[13]) & 0x0F);
   p[2] = ((chHex2Nibble(ph[10]) << 4) & 0xF0) | (chHex2Nibble(ph[11]) & 0x0F);
   p[3] = ((chHex2Nibble(ph[8]) << 4) & 0xF0) | (chHex2Nibble(ph[9]) & 0x0F);
   p[4] = ((chHex2Nibble(ph[6]) << 4) & 0xF0) | (chHex2Nibble(ph[7]) & 0x0F);
   p[5] = ((chHex2Nibble(ph[4]) << 4) & 0xF0) | (chHex2Nibble(ph[5]) & 0x0F);
   p[6] = ((chHex2Nibble(ph[2]) << 4) & 0xF0) | (chHex2Nibble(ph[3]) & 0x0F);
   p[7] = ((chHex2Nibble(ph[0]) << 4) & 0xF0) | (chHex2Nibble(ph[1]) & 0x0F);
   _retnd(pl, nd);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CDW2HEX(XppParamList  pl)
{
   DWCHARUNION dwu;
   BYTE        pHex[9];

   dwu.i = _parLong(pl, 1);
   pHex[0] = __HEXNIBBLE__[((dwu.ch[3] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[1] = __HEXNIBBLE__[(dwu.ch[3] & (BYTE)0x0F)];
   pHex[2] = __HEXNIBBLE__[((dwu.ch[2] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[3] = __HEXNIBBLE__[(dwu.ch[2] & (BYTE)0x0F)];
   pHex[4] = __HEXNIBBLE__[((dwu.ch[1] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[5] = __HEXNIBBLE__[(dwu.ch[1] & (BYTE)0x0F)];
   pHex[6] = __HEXNIBBLE__[((dwu.ch[0] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[7] = __HEXNIBBLE__[(dwu.ch[0] & (BYTE)0x0F)];
   pHex[8] = 0;
   _retc(pl, (LPSTR)pHex);
   return;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NHEX2DW(XppParamList  pl) // new behavior add nibles from the right
{
#ifndef _OT4XB_KEEP_OLD_NHEX2DW_BEHAVIOR
   TXppParamList xpp(pl);
   DWORD  dwNum = 0;
   if (xpp[1]->CheckType(XPP_CHARACTER))
   {
      ULONG  cb = 0;
      LPBYTE p = (LPBYTE)xpp[1]->LockStr(&cb);
      if (p && cb)
      {
         for (; *p && cb; p++, cb--)
         {
            DWORD nib = (DWORD)chHex2Nibble(*p);
            if (nib || (*p == (BYTE)'0'))
            {
               dwNum = (dwNum << 4) | nib;
            }
            else
            {
               if (*p != 0x20)
               {
                  dwNum = 0;
               }
            }
         }
      }
   }
   xpp[0]->PutLong(dwNum);

#else
   DWCHARUNION dwu;
   BYTE        pHex[9];

   _parc((LPSTR)pHex, 9, pl, 1);
   dwu.ch[0] = (BYTE)((chHex2Nibble(pHex[6]) << 4) & 0xF0);
   dwu.ch[0] |= (chHex2Nibble(pHex[7]) & 0x0F);

   dwu.ch[1] = (BYTE)((chHex2Nibble(pHex[4]) << 4) & 0xF0);
   dwu.ch[1] |= (chHex2Nibble(pHex[5]) & 0x0F);

   dwu.ch[2] = (BYTE)((chHex2Nibble(pHex[2]) << 4) & 0xF0);
   dwu.ch[2] |= (chHex2Nibble(pHex[3]) & 0x0F);

   dwu.ch[3] = (BYTE)((chHex2Nibble(pHex[0]) << 4) & 0xF0);
   dwu.ch[3] |= (chHex2Nibble(pHex[1]) & 0x0F);
   _retnl(pl, dwu.i);
#endif
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CW2HEX(XppParamList  pl)
{
   DWCHARUNION dwu;
   BYTE        pHex[9];

   dwu.i = _parLong(pl, 1);
   pHex[0] = __HEXNIBBLE__[((dwu.ch[3] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[1] = __HEXNIBBLE__[(dwu.ch[3] & (BYTE)0x0F)];
   pHex[2] = __HEXNIBBLE__[((dwu.ch[2] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[3] = __HEXNIBBLE__[(dwu.ch[2] & (BYTE)0x0F)];
   pHex[4] = __HEXNIBBLE__[((dwu.ch[1] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[5] = __HEXNIBBLE__[(dwu.ch[1] & (BYTE)0x0F)];
   pHex[6] = __HEXNIBBLE__[((dwu.ch[0] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[7] = __HEXNIBBLE__[(dwu.ch[0] & (BYTE)0x0F)];
   pHex[8] = 0;
   _retc(pl, (LPSTR)pHex + 4);
   return;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NHEX2W(XppParamList  pl)
{
   DWCHARUNION dwu;
   BYTE        pHex[9];

   _parc((LPSTR)pHex, 9, pl, 1);
   dwu.ch[0] = (BYTE)((chHex2Nibble(pHex[2]) << 4) & 0xF0);
   dwu.ch[0] |= (chHex2Nibble(pHex[3]) & 0x0F);

   dwu.ch[1] = (BYTE)((chHex2Nibble(pHex[0]) << 4) & 0xF0);
   dwu.ch[1] |= (chHex2Nibble(pHex[1]) & 0x0F);
   dwu.ch[2] = 0;
   dwu.ch[3] = 0;
   _retnl(pl, dwu.i);
   return;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CBYTE2HEX(XppParamList  pl)
{
   DWCHARUNION dwu;
   BYTE        pHex[9];

   dwu.i = _parLong(pl, 1);
   pHex[0] = __HEXNIBBLE__[((dwu.ch[3] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[1] = __HEXNIBBLE__[(dwu.ch[3] & (BYTE)0x0F)];
   pHex[2] = __HEXNIBBLE__[((dwu.ch[2] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[3] = __HEXNIBBLE__[(dwu.ch[2] & (BYTE)0x0F)];
   pHex[4] = __HEXNIBBLE__[((dwu.ch[1] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[5] = __HEXNIBBLE__[(dwu.ch[1] & (BYTE)0x0F)];
   pHex[6] = __HEXNIBBLE__[((dwu.ch[0] >> (BYTE)4) & (BYTE)0x0F)];
   pHex[7] = __HEXNIBBLE__[(dwu.ch[0] & (BYTE)0x0F)];
   pHex[8] = 0;
   _retc(pl, (LPSTR)(pHex + 6));
   return;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NHEX2BYTE(XppParamList  pl)
{
   DWCHARUNION dwu;
   BYTE        pHex[3];

   _parc((LPSTR)pHex, 9, pl, 1);
   dwu.ch[0] = (BYTE)((chHex2Nibble(pHex[0]) << 4) & 0xF0);
   dwu.ch[0] |= (chHex2Nibble(pHex[1]) & 0x0F);
   dwu.ch[1] = 0;
   dwu.ch[2] = 0;
   dwu.ch[3] = 0;
   _retnl(pl, dwu.i);
   return;
}
//----------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
// flags :
// 0x0001 = case insensitive
// 0x0002 = return found index ( first or last if flags & 4 ) 
// 0x0004 = stop at last ocurrence
// 0x0008 = implicit extra begin and end asterisks in mask
// 0x0010 = ltrim
// 0x0020 = rtrim
// 0x0040 = allow ^ at the begining as negation
// 0x0100 = use template characters
// 0x0200 = ot4xb_regex_match
// 0x8000 = ( without regexp) if ` ( character 96) at the begining the expression must exist
// 0x8000 = ( without regexp) if ~ ( character 126) at the begining the expression must not exist
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LSTRWILDCMP(XppParamList  pl) // lStrWildCmp( pWild , pStr , nFlags  ) -> lMatch
{
   return LSTRWILDCMPEX(pl);
}
XPPRET XPPENTRY LSTRWILDCMPEX(XppParamList  pl) // lStrWildCmpEx( pWild , pStr , nFlags , regex_flags , regex_match_flags  ) -> lMatch
{
   TXppParamList xpp(pl, 5);
   DWORD found = 0;
   DWORD flags = (xpp[3]->CheckType(XPP_LOGICAL) ? (xpp[3]->GetBool() ? 1 : 0) : xpp[3]->GetDWord());
   LPSTR pStr = xpp[2]->LockStr();
   LPBYTE tb = ((flags & 0x101) ? ((flags & 0x100) ? __TEMPLATE_09_AZ_NOCASE__ : _lower_ansi_char_table_) : 0);
   BOOL   use_regex = (flags & 0x200) ? 1 : 0;
   int regex_flags = 0;
   int  regex_match_flags = 0;

   if (use_regex)
   {
      regex_flags = xpp[5]->GetLong();
      if ((regex_flags & 0xFF) == 0)
      {
         regex_flags |= 1;
      }
      if (flags & 1)
      {
         regex_flags |= 0x100;
      }
      regex_match_flags = xpp[5]->GetLong();
   }

   if (pStr)
   {
      if (xpp[1]->CheckType(XPP_ARRAY))
      {
         DWORD count = _conGetArrayLen(xpp[1]->con());
         DWORD dw;
         for (dw = 1; dw <= count; dw++)
         {
            ContainerHandle con = _conNew(0);
            _conArrayGet(xpp[1]->con(), con, dw, 0);
            LPSTR pWild = 0;
            ULONG cbWild = 0;
            if (!ot4xb_conRLockC(con, &pWild, &cbWild))
            {
               BOOL b;
               if ((flags & 8) && (!use_regex))
               {
                  UINT cb = cbWild + 16;
                  LPSTR buffer = (LPSTR)_xgrab(cb);
                  sprintf_s(buffer, cb, "*%s*", pWild);
                  b = bStrWildCmpWithTableEx(buffer, pStr, tb, flags, 0, 0);
                  _xfree((void*)buffer);
                  buffer = 0;
               }
               else
               {
                  b = (use_regex ? ot4xb_regex_match(pWild, pStr, regex_flags, regex_match_flags) : bStrWildCmpWithTableEx(pWild, pStr, tb, flags, 0, 0));
               }
               if ((flags & 0x8000) && (!use_regex))
               {
                  if (b ? (*pWild == '~') : (*pWild == '`'))
                  {
                     found = 0;
                     count = 0;
                  }
                  else
                  {
                     if (b)
                     {
                        found = dw;
                     }
                  }
               }
               else
               {
                  if (b)
                  {
                     found = dw;
                     if (!(flags & 4))
                     {
                        count = 0;
                     }

                  }
               }
               ot4xb_conUnlockC(con);
            }
            _conRelease(con); con = 0;
         }
      }
      else
      {
         if (xpp[1]->CheckType(XPP_CHARACTER))
         {
            LPSTR pWild = xpp[1]->LockStr();

            BOOL b;
            if ((flags & 8) && (!use_regex))
            {
               UINT cb = xpp[1]->ExLen() + 16;
               LPSTR buffer = (LPSTR)_xgrab(cb);
               sprintf_s(buffer, cb, "*%s*", pWild);
               b = bStrWildCmpWithTableEx(buffer, pStr, tb, flags, 0, 0);
               _xfree((void*)buffer);
               buffer = 0;
            }
            else
            {
               b = use_regex ? ot4xb_regex_match(pWild, pStr, regex_flags, regex_match_flags) : bStrWildCmpWithTableEx(pWild, pStr, tb, flags);
            }
            if (b)
            {
               found = 1;
            }
         }
      }
   }
   xpp[2]->UnlockStr();
   if (flags & 2)
   {
      xpp[0]->PutDWord(found);
   }
   else
   {
      xpp[0]->PutBool(found);
   }
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CDW2BITS(XppParamList  pl) // cDw2Bits( nInt32 [,nLen]) -> cBits / 100111000 ...
{
   DWORD dw = (DWORD)_parLong(pl, 1);
   CHAR  sz[32];
   DWORD n;
   LPSTR p = sz + 32;
   DWORD nLen = (DWORD)_parLong(pl, 2);
   _bset((LPBYTE)sz, 0, 32);
   for (n = 1; n; n <<= 1) *--p = ((dw & n) ? '1' : '0');
   if ((nLen > 0) && (nLen < 32))
   {
      p = sz + (32 - nLen);
      _retclen(pl, p, nLen);
   }
   else _retclen(pl, sz, 32);
   return;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NBITS2DW(XppParamList  pl) // nBits2Dw( cBitStr ) -> nInt32
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conTParam(pl, 1, &bByRef, XPP_CHARACTER);
   LPSTR pStr;
   ULONG ul;
   DWORD dw = 0;
   if (con)
   {
      if (ot4xb_conRLockC(con, &pStr, &ul) == 0)
      {
         LPSTR p = pStr + ul;
         DWORD n = 1;
         while ((p > pStr) && n)
         {
            p--;
            if (p[0] == '1') dw |= n;
            n <<= 1;
         }
         ot4xb_conUnlockC(con);
      }
      if (!bByRef) _conRelease(con);
   }
   _retnl(pl, (LONG)dw);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CGENRNDSTR(XppParamList  pl) // cGenRndStr( nLen , lSafeChars = .F. | 1 lsafe chars , 2 lsafeandupperonly , 3 A-Z only )
{
   if (GetTlsHeapManager()->m_rnd_seed == 1)
   {
      GetTlsHeapManager()->m_rnd_seed = GetTickCount();
      srand(GetTlsHeapManager()->m_rnd_seed);
   }
   ULONG nSize = (ULONG)(_parnl(pl, 1) & 0x007FFFFF); // 8MB max
   LPSTR p = (LPSTR)_xgrab(nSize + 1);
   ULONG n;
   if (_parnl(pl, 2) == 2)
   {
      static const char szsc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
      for (n = 0; n < nSize; n++) p[n] = szsc[((UINT)(rand() % (sizeof(szsc) - 1)))];
   }
   else if (_parnl(pl, 2) == 3)
   {
      static const char szsc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      for (n = 0; n < nSize; n++) p[n] = szsc[((UINT)(rand() % (sizeof(szsc) - 1)))];
   }
   else if (_parl(pl, 2) || (_parnl(pl, 2) == 1))
   {
      static const char szsc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
      for (n = 0; n < nSize; n++) p[n] = szsc[((UINT)(rand() % (sizeof(szsc) - 1)))];
   }
   else {
      for (n = 0; n < nSize; n++) p[n] = (char)(rand() % 256);
   }
   _retclen(pl, p, nSize);
   _xfree((void*)p);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY OT4XB_NRAND(XppParamList  pl) // ot4xb_nRand( nMax )
{
   if (GetTlsHeapManager()->m_rnd_seed == 1)
   {
      GetTlsHeapManager()->m_rnd_seed = GetTickCount();
      srand(GetTlsHeapManager()->m_rnd_seed);
   }

   LONG n = _parnl(pl, 1);
   if (n < 1) {
      n = 1;
   }
   _retnl(pl, (LONG)(((double)rand() / (double)(RAND_MAX + 1)) * ((double)n)));
}
// -----------------------------------------------------------------------------------------------------------------

// dwFlags: 0x10 remove empty ( cb=0) lines| 0x20 remove lines starting with ; | 0x40 remove lines starting with [ | 1 LTrim |2 RTrim
// 0x200 reserved for aTxtSplitLines // split with
// 0x100 email header lines
OT4XB_API TList* TxtSplitLinesToTList(LPSTR pStr, DWORD dwFlags)
{
   return TxtSplitLinesToTListEx(pStr, dwFlags, 0);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API TList* TxtSplitLinesToTListEx(LPSTR pStr, DWORD dwFlags, DWORD* pdwSkip)
{
   DWORD dw = 0;
   TList* pList = new TList;
   BYTE bt[256]; ZeroMemory(bt, 256);
   bt[9] = bt[10] = bt[13] = bt[32] = 1;
   if (!pdwSkip) {
      pdwSkip = &dw;
   }
   if (dwFlags & 0x100)
   {
      dwFlags = 0x100;
   }
   if (pStr)
   {

      LPSTR p = pStr;
      pList->Add((void*)p);
      while (*p)
      {
         BOOL bAdd = FALSE;
         switch (*p)
         {
            case 13:
            {
               *p++ = 0;
               if (*p == 10)
               {
                  *p++ = 0;
               }
               if (dwFlags & 0x100) // email header
               {
                  if (*p == 13)
                  {  // stop scanning after CRLF + CRLF found
                     *p = 0;
                     if (p[1] == 10)
                     {
                        p++;
                        *p = 0;
                     }
                     pdwSkip[0] = (((DWORD)p) + 1) - ((DWORD)pStr);
                     break;
                  }
               }
               bAdd = TRUE;
               break;
            }
            case 10:
            {
               *p++ = 0;
               if (dwFlags & 0x100)  // email header
               {
                  if (*p == 10)
                  {  // stop scanning after LF + LF found
                     *p = 0;
                     pdwSkip[0] = (((DWORD)pStr) + 1) - ((DWORD)p);
                     break;
                  }
               }
               bAdd = TRUE;
               break;
            }
            default:
            {
               p++; break;
            }
         }
         if (bAdd)
         {
            if (dwFlags & 0xFF)
            {
               LPBYTE pp = (LPBYTE)pList->Tail();
               UINT cb = _xstrlen((LPSTR)pp);
               if (dwFlags & 2)
               {
                  cb = ByteMapTable_RTrimEx(bt, pp, cb);
               }
               if (dwFlags & 1)
               {
                  cb = ByteMapTable_LTrimEx(bt, pp, cb);
               }
               if (dwFlags & 3)
               {
                  pp[cb] = 0;
               }
               if (((!cb) && (dwFlags & 0x10)) || (cb && (dwFlags & 0x20) && (pp[0] == ';')) || (cb && (dwFlags & 0x40) && (pp[0] == '[')))
               {
                  pList->Pop();
               }

            }
            else if (dwFlags & 0x100)
            {
               if (((*p == 9) || (*p == 32)) && pList->Count())
               {
                  // use LF to join the new line with previous
                  LPBYTE pp = (LPBYTE)pList->Tail();
                  for (; pp < ((LPBYTE)p); pp++)
                  {
                     if (*pp == 0)
                     {
                        *pp = 10;
                     }
                  }
                  bAdd = FALSE;
               }

            }
            if (bAdd) // maybe dissabled by 0x100
            {
               pList->Add((void*)p);
            }
         }
      }
      if ((dwFlags & 0xFF) && pList->Count()) // ignore empty lines
      {
         LPBYTE pp = (LPBYTE)pList->Tail();
         UINT cb = _xstrlen((LPSTR)pp);
         if (dwFlags & 2)
         {
            cb = ByteMapTable_RTrimEx(bt, pp, cb);
         }
         if (dwFlags & 1)
         {
            cb = ByteMapTable_LTrimEx(bt, pp, cb);
         }
         if (dwFlags & 3)
         {
            pp[cb] = 0;
         }
         if ((!cb) && (dwFlags & 0x10)) {
            pList->Pop();
         }
      }

      if (dwFlags & 0x100)
      {
         DWORD n;
         DWORD nn = pList->Count();
         for (n = 0; n < nn; n++)
         {
            LPBYTE pp = (LPBYTE)pList->Get(n);
            int    cb = ByteMapTable_CondenseString(bt, pp, -1);
            cb = ByteMapTable_RTrimEx(bt, pp, cb);
            cb = ByteMapTable_LTrimEx(bt, pp, cb);
            pp[cb] = 0;
         }
      }



   }
   return pList;
}

// -----------------------------------------------------------------------------------------------------------------
// 
// dwFlags: 0x10 remove empty ( cb=0) lines| 0x20 remove lines starting with ; | 0x40 remove lines starting with [ | 1 LTrim |2 RTrim
// 0x200 for ini files  // 0x1200 like 0x200 but all elements using {k,v} pairs ; and [ going as k with empty string v
// 0x100 email header lines
// aSplitTxtLines( cText , nFlags , @nShift) -> aLines
XPPRET XPPENTRY ASPLITTXTLINES(XppParamList pl)
{
   ContainerHandle conr = NULLCONTAINER;
   LPSTR pStr = _pszParam(pl, 1);
   DWORD dwFlags = (DWORD)_parnl(pl, 2);
   DWORD dwShift = 0;
   if (pStr)
   {
      TList* pList = TxtSplitLinesToTListEx(pStr, dwFlags, &dwShift);
      _stornl((LONG)dwShift, pl, 3);
      if (pList)
      {
         ULONG n;
         ULONG nItems = pList->Count();
         switch (dwFlags & 0x300)
         {
            case 0x100:
            {
               conr = _conNewArray(2, nItems, 2);
               for (n = 0; n < nItems; n++)
               {
                  LPSTR k = (LPSTR)pList->Get(n);
                  LPSTR v = 0;
                  LPSTR p;
                  for (p = k; ((*p) && (v == 0)); p++)
                  {
                     if (*p == ':')
                     {
                        *p++ = 0;
                        while ((*p == 32) || (*p == 9))
                        {
                           *p++ = 0;
                        }
                        v = p;
                     }
                  }

                  _conArrayPutC(conr, k, (n + 1), 1, 0);
                  if (v)
                  {
                     _conArrayPutC(conr, v, (n + 1), 2, 0);
                  }
                  else
                  {
                     _conArrayPutC(conr, "", (n + 1), 2, 0);
                  }
               }
               break;
            }
            case 0x200:
            {
               conr = _conNewArray(2, nItems, 2);
               for (n = 0; n < nItems; n++)
               {
                  LPSTR k = (LPSTR)pList->Get(n);
                  LPSTR v = 0;
                  LPSTR p = k;
                  while ((*p == 32) || (*p == 9)) 
                  {
                     p++;
                  }
                  switch (*p)
                  {

                     case '[':
                     {
                        if (!(dwFlags & 0x40))
                        {
                           if (dwFlags & 0x1000)
                           {
                              _conArrayPutC(conr, p , (n + 1), 1, 0);
                              _conArrayPutC(conr, "", (n + 1), 2, 0);
                           }
                           else
                           {
                              _conArrayPutC(conr, p, (n + 1), 0);
                           }
                        }
                        break;
                     }
                     case ';':
                     {
                        if (!(dwFlags & 0x20))
                        {
                           if (dwFlags & 0x1000)
                           {
                              _conArrayPutC(conr, p, (n + 1), 1, 0);
                              _conArrayPutC(conr, "", (n + 1), 2, 0);
                           }
                           else
                           {
                              _conArrayPutC(conr, p, (n + 1), 0);
                           }
                        }
                        break;
                     }
                     case 0:
                     {
                        if (!(dwFlags & 0x10))
                        {
                           if (dwFlags & 0x1000)
                           {
                              _conArrayPutC(conr, p, (n + 1), 1, 0);
                              _conArrayPutC(conr, "", (n + 1), 2, 0);
                           }
                           else
                           {
                              _conArrayPutC(conr, "", (n + 1), 0);
                           }
                        }
                        break;
                     }
                     default:
                     {

                        for (p = k; ((*p) && (v == 0)); p++)
                        {
                           if (*p == '=')
                           {
                              *p++ = 0;
                              while ((*p == 32) || (*p == 9))
                              {
                                 *p++ = 0;
                              }
                              v = p;
                           }
                        }

                        _conArrayPutC(conr, k, (n + 1), 1, 0);
                        if (v)
                        {
                           _conArrayPutC(conr, v, (n + 1), 2, 0);
                        }
                        else
                        {
                           _conArrayPutC(conr, "", (n + 1), 2, 0);
                        }
                        break;
                     }
                  }
               }
               break;
            }
            default:
            {
               conr = _conNewArray(1, nItems);
               for (n = 0; n < nItems; n++)
               {
                  _conArrayPutC(conr, (LPSTR)pList->Get(n), (n + 1), 0);
               }
               break;
            }
         }
         delete pList;
      }
      _xfree((void*)pStr);
   }
   if (conr)
   {
      _conReturn(pl, conr);
      _conRelease(conr);
   }
   else
   {
      _ret(pl);
   }
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR ot4xb_urlencode(LPSTR pIn, DWORD cbIn, DWORD* pcbOut)
{
   DWORD cb = 0;
   LPSTR pOut = 0;
   if (pIn)
   {
      DWORD n;
      LPBYTE p, pp;
      cb = cbIn;
      p = (LPBYTE)pIn;
      for (n = 0; n < cbIn; n++, p++) {
         if (!__SAFECHAR__[*p]) cb += 2;
      }
      pOut = (LPSTR)_xgrab(cb + 1);
      p = (LPBYTE)pIn;
      pp = (LPBYTE)pOut;
      for (n = 0; n < cbIn; n++, p++)
      {
         if (__SAFECHAR__[*p]) *pp++ = *p;
         else
         {
            *pp++ = '%';
            *pp++ = __HEXNIBBLE__[MSNIBBLE(p[0])];
            *pp++ = __HEXNIBBLE__[LSNIBBLE(p[0])];
         }
      }
   }
   if (pcbOut) pcbOut[0] = cb;
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD ot4xb_urlencode_cb(LPBYTE pIn, DWORD cbIn)
{
   DWORD cb = 0;
   if (pIn)
   {
      DWORD n;
      cb = cbIn;
      for (n = 0; n < cbIn; n++, pIn++) {
         if (!__SAFECHAR__[*pIn]) cb += 2;
      }
   }
   return cb;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD ot4xb_urlencode_buffer(LPBYTE pIn, DWORD cbIn, LPBYTE pOut, DWORD cbOut)
{
   if (pIn && pOut)
   {
      DWORD cb = ot4xb_urlencode_cb(pIn, cbIn);
      if (cb > cbOut) {
         return (DWORD)-1;
      }
      for (; cbIn; cbIn--, pIn++)
      {
         if (__SAFECHAR__[*pIn]) {
            *pOut++ = *pIn;
         }
         else
         {
            *pOut++ = '%';
            *pOut++ = __HEXNIBBLE__[MSNIBBLE(pIn[0])];
            *pOut++ = __HEXNIBBLE__[LSNIBBLE(pIn[0])];
         }
      }
      return cb;
   }
   return (DWORD)-1;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL TZString_urlencode_add(TZString* psc, LPSTR pIn, DWORD cb)
{
   if (psc && pIn && cb)
   {
      LPBYTE p = (LPBYTE)pIn;
      DWORD n;
      for (n = 0; n < cb; n++, p++)
      {
         if (__SAFECHAR__[*p]) psc->AddChar((char)*p);
         else
         {
            psc->AddChar('%');
            psc->AddChar((char)__HEXNIBBLE__[MSNIBBLE(*p)]);
            psc->AddChar((char)__HEXNIBBLE__[LSNIBBLE(*p)]);
         }
      }
      return TRUE;
   }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL TZString_urlencode_add_con(TZString* psc, ContainerHandle con)
{
   BOOL bOk = FALSE;
   if (psc && _conCheckType(con, XPP_CHARACTER))
   {
      LPSTR p = 0;
      ULONG cb = 0;
      if (ot4xb_conRLockC(con, &p, &cb) == 0)
      {
         bOk = TZString_urlencode_add(psc, p, cb);
         ot4xb_conUnlockC(con);
      }
   }
   return bOk;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL TZString_add_con(TZString* psc, ContainerHandle con)
{
   BOOL bOk = FALSE;
   if (psc && _conCheckType(con, XPP_CHARACTER))
   {
      LPSTR p = 0;
      ULONG cb = 0;
      if (ot4xb_conRLockC(con, &p, &cb) == 0)
      {
         psc->Add(p);
         bOk = TRUE;
         ot4xb_conUnlockC(con);
      }
   }
   return bOk;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API int Bin2Hex_buffer(LPBYTE pb, UINT cb, LPSTR buffer, UINT buffer_cb)
{
   if (buffer_cb < (cb * 2))
   {
      return 0;
   }
   LPSTR pp = buffer;
   ULONG n;
   for (n = 0; n < cb; n++)
   {
      *pp++ = __HEXNIBBLE__[MSNIBBLE(pb[n])];
      *pp++ = __HEXNIBBLE__[LSNIBBLE(pb[n])];
   }
   return (cb * 2);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR pBin2Hex(LPBYTE pb, UINT cb)
{
   LPSTR ph = (LPSTR)_xgrab((cb * 2) + 1);
   Bin2Hex_buffer(pb, cb, ph, cb * 2);
   return ph;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPBYTE pHex2Bin(LPSTR ph, DWORD* pcb)
{
   ULONG cb = 0;
   LPBYTE pp, pb, p;
   BOOL  bh;

   for (pp = (LPBYTE)ph; *pp; pp++) {
      if (__NIBBLECHAR__[*pp]) {
         cb++;
      }
   }
   if (cb & 1) {
      cb++;
   }
   pb = (LPBYTE)_xgrab((cb >> 1) + 1);
   for (cb = 0, p = pb, bh = 0, pp = (LPBYTE)ph; *pp; pp++)
   {
      if (__NIBBLECHAR__[*pp])
      {
         if (bh) {
            *p = ((*p << 4) & 0xF0) | (__NIBBLECHAR__[*pp] & 0x0F); p++; bh = 0;
         }
         else {
            *p = (__NIBBLECHAR__[*pp] & 0x0F); cb++; bh = 1;
         }
      }
      else if (bh) {
         bh = 0; p++;
      }
   }
   if (pcb) pcb[0] = cb;
   return pb;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONGLONG pHex2i64(LPBYTE ph, DWORD cb)
{
   LONGLONG q = 0;
   if (!ph) return 0;
   if (cb & 0x80000000) {
      cb = _xstrlen((LPSTR)ph);
   }
   for (; (cb && (*ph)); cb--, ph++)
   {
      BYTE n = __NIBBLECHAR__[*ph];
      if (n) {
         q = ((q << 4) | (n & 0x0F));
      }
      else {
         if ((*ph == 'x') || (*ph == 'X')) {
            q = 0;
         }
      }
   }
   return q;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD pHex2i32(LPBYTE ph, DWORD cb)
{
   DWORD dw = 0;
   if (!ph) return 0;
   if (cb & 0x80000000) {
      cb = _xstrlen((LPSTR)ph);
   }
   for (; (cb && (*ph)); cb--, ph++)
   {
      BYTE n = __NIBBLECHAR__[*ph];
      if (n) {
         dw = ((dw << 4) | (n & 0x0F));
      }
      else {
         if ((*ph == 'x') || (*ph == 'X')) {
            dw = 0;
         }
      }
   }
   return dw;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD ByteMapTable_RTrimEx(LPBYTE pTable, LPBYTE pIn, DWORD cbIn)
{

   if (pTable == 0) {
      pTable = __DEFAULT_WHITE_SPACE_TABLE__;
   }
   if (!pIn) {
      return 0;
   }
   if (((int)cbIn) < 0) {
      cbIn = _xstrlen((LPSTR)pIn);
   }
   if (!cbIn) {
      return 0;
   }
   for (; cbIn; cbIn--)
   {
      if (pTable[(pIn[(cbIn - 1)])] == 0)
      {
         return cbIn;
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD ByteMapTable_LTrimEx(LPBYTE pTable, LPBYTE pIn, DWORD cbIn)
{

   if (pTable == 0) {
      pTable = __DEFAULT_WHITE_SPACE_TABLE__;
   }

   if (!pIn) {
      return 0;
   }
   if (((int)cbIn) < 0) {
      cbIn = _xstrlen((LPSTR)pIn);
   }
   if (!cbIn) {
      return 0;
   }


   DWORD n = 0;
   for (; ((n < cbIn) && pTable[(pIn[n])]); n++);
   if (n)
   {
      cbIn -= n;
      LPBYTE p = _mk_ptr_(LPBYTE, pIn, n);
      for (n = 0; n < cbIn; n++)
      {
         pIn[n] = p[n];
      }
   }
   return cbIn;
}
// -----------------------------------------------------------------------------------------------------------------

//StrTrimEx(1cStr,2cTrimChars,3nFlags,4chReplaceForCondenseSTRING) > cTrimmed string 
//      0x01 - Trim characters on the left side of the string
//      0x02 - Trim characters on the right side of the string
//      0x03 - Trim characters on both sides of the string
//      0x100 - Condense String
//      0x200 - Remove unsafe	( list is safe unless 0x1000 )
//      0x1000 - INVERT TABLE  if 0x200 only then list is unsafe

_XPP_REG_FUN_(STRTRIMEX)
{
   TXppParamList xpp(pl, 4);
   BYTE pTable[256];
   DWORD dwFlags = xpp[3]->GetDWord();
   DWORD dw;

   if ((dwFlags & 0x1200) == 0x1200)
   {
      for (dw = 0; dw < sizeof(pTable); dw++)
      {
         pTable[dw] = (BYTE)(dw & 0xFF);
      }
   }
   else
   {
      ZeroMemory(pTable, sizeof(pTable));
   }

   if (xpp[2]->CheckType(XPP_CHARACTER))
   {
      LPBYTE pt = (LPBYTE)xpp[2]->RLockStrEx();
      DWORD  cbt = xpp[2]->ExLen();
      if (pt && cbt)
      {
         if ((dwFlags & 0x1200) == 0x200)
         {
            for (; cbt; pt++, cbt--) {
               pTable[*pt] = *pt;
            }
         }
         else
         {
            if ((dwFlags & 0x1200) == 0x1200)
            {
               for (; cbt; pt++, cbt--) {
                  pTable[*pt] = 0;
               }
            }
            else
            {
               for (; cbt; pt++, cbt--) {
                  pTable[*pt] = 1;
               }
            }
         }
      }
      xpp[2]->UnLockStrEx();
   }
   DWORD   cb = 0;
   LPBYTE  p = (LPBYTE)xpp[1]->StrDupA(&cb);
   if (p)
   {
      if (dwFlags & 2)
      {
         cb = ByteMapTable_RTrimEx(pTable, p, cb);
      }
      if (dwFlags & 1)
      {
         cb = ByteMapTable_LTrimEx(pTable, p, cb);
      }
      if (dwFlags & 0x100)
      {
         BYTE ch = 0x20;
         xpp[4]->GetCL((LPSTR)&ch, 4);
         cb = ByteMapTable_CondenseString(pTable, p, cb, ch);
      }
      if (dwFlags & 0x200)
      {
         cb = ByteMapTable_RemoveUnsafe(pTable, p, cb);
      }
      xpp[0]->PutStrLen((LPSTR)p, cb);
      _xfree((void*)p);
   }
   else
   {
      xpp[0]->PutStr("");
   }
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void ByteMapTable_Add(LPBYTE pTable, LPBYTE pPos, LPBYTE pMap, DWORD cb)
{
   if (pTable && pPos && pMap && cb)
   {
      DWORD n;
      for (n = 0; n < cb; n++) {
         pTable[(pPos[n])] = pMap[n];
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL  ByteMapTable_IsSafeStr(LPBYTE pTable, LPBYTE p, int cb)
{
   BOOL bOk = TRUE;
   if (p)
   {
      if (cb == -1) {
         cb = _xstrlen((LPSTR)p);
      }
      for (; cb > 0; cb--, p++) {
         if (!pTable[(*p)]) {
            return FALSE;
         }
      }
   }
   return bOk;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API int  ByteMapTable_RemoveUnsafe(LPBYTE pTable, LPBYTE p, int cb)
{
   if (!(p && pTable)) {
      return 0;
   }
   LPBYTE pp = p;
   int n, nn;
   if (cb == -1) {
      cb = _xstrlen((LPSTR)p);
   }
   nn = cb;
   for (n = 0; n < nn; n++, p++)
   {
      if (pTable[*p])
      {
         *pp = pTable[*p];
         pp++;
      }
      else
      {
         *p = 0;
         cb--;
      }
   }
   return cb;
}
// -----------------------------------------------------------------------------------------------------------------
// remove dupe white spaces and replace with single chFill
OT4XB_API int  ByteMapTable_CondenseString(LPBYTE pTable, LPBYTE p, int cb, BYTE chFill)
{
   if (!(p && pTable)) {
      return 0;
   }
   LPBYTE pp = p;
   int n, nn;
   BOOL b = FALSE;
   if (cb == -1) {
      cb = _xstrlen((LPSTR)p);
   }
   nn = cb;
   for (n = 0; n < nn; n++, p++)
   {
      if (pTable[*p])
      {
         if (b)
         {
            *p = 0;
            cb--;
         }
         else
         {
            b = TRUE;
            *pp = (chFill ? chFill : *p);
            pp++;
         }
      }
      else
      {
         b = FALSE;
         *pp = *p;
         pp++;
      }
   }
   return cb;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void ByteMapTable_FillSeq(LPBYTE pTable, LPWORD pSeq, DWORD sc)
{
   if (pTable && pSeq && sc)
   {
      DWORD ss;
      for (ss = 0; ss < sc; ss++)
      {
         WORD n;
         WORD nn = MAKEWORD(HIBYTE(pSeq[ss]), 0);
         for (n = MAKEWORD(LOBYTE(pSeq[ss]), 0); n <= nn; n++)
         {
            pTable[n] = (n & 0xFF);
         }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD ByteMapTable_StrFindFlag(LPBYTE pSrc, int cb, int nStart, LPBYTE pTable, DWORD dwFlags)
{
   if (cb < 1) return (DWORD)-1;
   if (nStart < 0) nStart = 0;
   if (nStart >= cb) nStart = (cb - 1);
   if (pSrc && cb && pTable)
   {
      switch (dwFlags)
      {
         case 0x0001: // find next word
         {
            int n = nStart;
            if (n > 0) n++;
            if (n >= cb) return cb - 1;
            if (!pTable[(pSrc[n])])
            {
               while ((n < cb) && (!pTable[(pSrc[n])])) n++;
            }
            else
            {
               while ((n < cb) && (pTable[(pSrc[n])])) n++;
               while ((n < cb) && (!pTable[(pSrc[n])])) n++;
            }
            return n;
         }
         case 0x0002: // find prev word
         {
            int n = nStart;
            if (n > 0) n--;
            if (!pTable[(pSrc[n])])
            {
               while ((n > 0) && (!pTable[(pSrc[n])])) n--;
               if (n)
               {
                  while ((n > 0) && pTable[(pSrc[n])]) n--;
                  if (!pTable[(pSrc[n])]) n++;
               }
            }
            else
            {
               while (n && pTable[(pSrc[n])]) n--;
               if (!pTable[(pSrc[n])]) n++;
            }
            return n;
         }
      }
   }
   return (DWORD)-1;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR cp850_to_html(LPSTR pIn, UINT* pcbOut, DWORD dwFlags)
{
   TZString zs;
   LPSTR pOut = 0;
   zs.Add_cp850_to_html(pIn, dwFlags);
   pOut = zs.Detach(pcbOut, 0);
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR cp437_to_html(LPSTR pIn, UINT* pcbOut, DWORD dwFlags)
{
   TZString zs;
   LPSTR pOut = 0;
   zs.Add_cp437_to_html(pIn, dwFlags);
   pOut = zs.Detach(pcbOut, 0);
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR cp1252_to_html(LPSTR pIn, UINT* pcbOut, DWORD dwFlags)
{
   TZString zs;
   LPSTR pOut = 0;
   zs.Add_cp1252_to_html(pIn, dwFlags);
   pOut = zs.Detach(pcbOut, 0);
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR escape_to_xml(LPSTR pIn, UINT* pcbOut)
{
   TZString zs;
   LPSTR pOut = 0;
   zs.Add_to_xml(pIn);
   pOut = zs.Detach(pcbOut, 0);
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR escape_to_json(LPSTR pIn, int cb, UINT* pcbOut)
{
   TZString zs;
   LPSTR pOut = 0;
   zs.Add_to_json(pIn, cb);
   pOut = zs.Detach(pcbOut, 0);
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR ot4xbenc2bin(LPSTR pIn, UINT cb, UINT* pcbOut)
{
   LPSTR pOut = 0;
   UINT  cbo = 0;
   if (cb == INFINITE) cb = _xstrlen(pIn);
   if (pIn)
   {
      UINT n;
      pOut = (LPSTR)_xgrab(cb + 1);

      for (n = 0; n < cb; n++)
      {
         if ((pIn[n] == '\\') && ((n + 1) < cb))
         {
            n++;
            switch ((BYTE)pIn[n])
            {
               case 'x': // \x00
               {
                  BYTE hnib;
                  BYTE lnib;
                  n++; hnib = chHex2Nibble((n < cb) ? ((BYTE)pIn[n]) : 0);
                  n++; lnib = chHex2Nibble((n < cb) ? ((BYTE)pIn[n]) : 0);
                  pOut[cbo] = (char)((hnib << 4) | lnib);
                  cbo++;
                  break;
               }
               case 'd': // \d000
               {
                  char sz[4];
                  n++; sz[0] = ((n < cb) ? pIn[n] : 0);
                  n++; sz[1] = ((n < cb) ? pIn[n] : 0);
                  n++; sz[2] = ((n < cb) ? pIn[n] : 0);
                  sz[3] = 0;
                  pOut[cbo] = (char)(atoi(sz) & 0xFF);
                  cbo++;
                  break;
               }
               case '0':
               {
                  pOut[cbo] = 0; cbo++; break;
               } //  NULL
               case 's':
               {
                  pOut[cbo] = 0x20; cbo++; break;
               } //  space
               case 'q':
               {
                  pOut[cbo] = 0x22; cbo++; break;
               } //  Double Quote
               case 'a':
               {
                  pOut[cbo] = '\a'; cbo++; break;
               } //  Bell (alert)
               case 'b':
               {
                  pOut[cbo] = '\b'; cbo++; break;
               } //  Backspace
               case 'f':
               {
                  pOut[cbo] = '\f'; cbo++; break;
               } //  Formfeed
               case 'n':
               {
                  pOut[cbo] = '\n'; cbo++; break;
               } //  New line
               case 'r':
               {
                  pOut[cbo] = '\r'; cbo++; break;
               } //  Carriage return
               case 't':
               {
                  pOut[cbo] = '\t'; cbo++; break;
               } //  Horizontal tab
               case 'v':
               {
                  pOut[cbo] = '\v'; cbo++; break;
               } //  Vertical tab
               case '\\':
               {
                  pOut[cbo] = '\\'; cbo++; break;
               } //  Backslash
               default:
               {
                  pOut[cbo] = pIn[n]; cbo++; break;
               } //
            }
         }
         else {
            pOut[cbo] = pIn[n]; cbo++;
         } //
      }
   }
   if (pOut) {
      pOut[cbo] = 0;
   }
   if (pcbOut) pcbOut[0] = cbo;
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR bin2ot4xbenc_ta(LPSTR pIn, UINT cb, UINT* pcbOut, UINT* lt, UINT* rt)
{

   if (cb == ((UINT)-1)) {
      cb = _xstrlen(pIn);
   }
   lt[0] = 0; rt[0] = 0;
   while (pIn[0] == 0x20) {
      cb--; lt++; pIn = _mk_ptr_(LPSTR, pIn, 1);
   }
   while (cb && pIn[(cb - 1)] == 0x20) {
      cb--; rt++;
   }
   return bin2ot4xbenc(pIn, cb, pcbOut);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR bin2ot4xbenc(LPSTR pIn, UINT cb, UINT* pcbOut)
{
   if (cb == ((UINT)-1)) {
      cb = _xstrlen(pIn);
   }

   TZString z(cb);
   UINT n;
   for (n = 0; n < cb; n++)
   {
      BYTE ch = (BYTE)pIn[n];
      switch (ch)
      {
         case 0:
         {
            z.Add("\\0"); break;
         }
         case 0x20:
         {
            if (n == cb) {
               z.Add("\\s");
            }
            else
            {
               if (((BYTE)pIn[(n + 1)]) == ch) {
                  z.Add("\\s");
               }
               else {
                  z.AddChar((char)ch);
               }
            }
            break;
         }
         case '%':
         {
            z.Add("\\x25"); break;
         }
         case '&':
         {
            z.Add("\\x26"); break;
         }
         case '<':
         {
            z.Add("\\x3C"); break;
         }
         case '>':
         {
            z.Add("\\x3E"); break;
         }
         case '"':
         {
            z.Add("\\q"); break;
         } //  Double Quote
         case '\a':
         {
            z.Add("\\a"); break;
         } //  Bell (alert)
         case '\b':
         {
            z.Add("\\b"); break;
         } //  Backspace
         case '\f':
         {
            z.Add("\\f"); break;
         } //  Formfeed
         case '\n':
         {
            z.Add("\\n"); break;
         } //  New line
         case '\r':
         {
            z.Add("\\r"); break;
         } //  Carriage return
         case '\t':
         {
            z.Add("\\t"); break;
         } //  Horizontal tab
         case '\v':
         {
            z.Add("\\v"); break;
         } //  Vertical tab
         case '\\':
         {
            z.AddChar('\\'); z.AddChar('\\'); break;
         } //  Backslash
         default:
         {
            if ((ch < 32) || (ch > 127)) {
               z.printf("\\x%02.2X", ch);
            }
            else {
               z.AddChar((char)ch);
            }
            break;
         }
      }
   }
   return z.Detach(pcbOut);
}
// -----------------------------------------------------------------------------------------------------------------

// quot 0x22  - 5
// amp  0x26  - 4
// apos 0x27  - 5
// lt   0x3C  - 3
// gt   0x3E  - 3
// -----------------------------------------------------------------------------------------------------------------
// x_www_form_urlencoded_to_cp1252(LPSTR pIn , UINT cb, void** ppInfo) -> pString
// return a decoded string ( urldecode + utftoansi )
// optionally ppInfo will retrieve a pointer to x_www_form_cp1252_Header_t
// followed by nItems x_www_form_cp1252_KeyVal_t
// this info is marshalled inside pString only 1 pointer to release
static LPSTR x_www_form_urlencoded_internal(LPSTR pIn, UINT cb, void** ppInfo, BOOL u2a_convert)
{
   x_www_form_cp1252_Header_t* h = 0;
   LPSTR pOut = 0;
   UINT  nItemCount = 0;
   if (pIn) {
      if (((int)cb) < 0) {
         cb = _xstrlen(pIn);
      }
   }
   if (pIn && cb)
   {
      LPSTR p = pIn;
      UINT  n = 0;
      if (p[0] == '?') {
         n++;
      }
      if ((n < cb) && (p[n])) {
         nItemCount++;
      }
      for (; (n < cb) && p[n]; n++) {
         if (p[n] == '&') {
            nItemCount++;
         }
      }
   }
   if (!nItemCount) {
      if (ppInfo) {
         ppInfo[0] = 0;
      } return 0;
   }
   pOut = x_www_form_cp1252_Header_t::AllocStr(cb, nItemCount, h);
   if (ppInfo) {
      ppInfo[0] = (void*)h;
   }
   h->decode_and_parse_string(pIn, cb, u2a_convert);
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR x_www_form_urlencoded_to_cp1252(LPSTR pIn, UINT cb, void** ppInfo)
{
   return x_www_form_urlencoded_internal(pIn, cb, ppInfo, TRUE);
}
// -----------------------------------------------------------------------------------------------------------------
// content already as cp1252
OT4XB_API LPSTR x_www_form_urlencoded_ncp(LPSTR pIn, UINT cb, void** ppInfo)
{
   return x_www_form_urlencoded_internal(pIn, cb, ppInfo, FALSE);
}


// -----------------------------------------------------------------------------------------------------------------
x_www_form_cp1252_KeyVal_t* x_www_form_cp1252_KeyVal_t::next(void)
{
   return (x_www_form_cp1252_KeyVal_t*)_mk_ptr_(LPVOID, this, sizeof(x_www_form_cp1252_KeyVal_t));
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR x_www_form_cp1252_Header_t::AllocStr(UINT cb, UINT nItemCount, x_www_form_cp1252_Header_t*& ph)
{
   UINT cbb = cb + (nItemCount * 2) + 4;
   UINT cbt = cbb + sizeof(x_www_form_cp1252_Header_t) + (sizeof(x_www_form_cp1252_KeyVal_t) * (nItemCount + 1));
   void* p = _xgrab(cbt);
   ph = (x_www_form_cp1252_Header_t*)_mk_ptr_(LPVOID, p, cbb);
   ph->m_pBuffer = (LPSTR)p;
   ph->m_cbBuffer = cbt;
   ph->m_cbString = 0;
   ph->m_nItemCount = 0;
   return (LPSTR)p;
}
// -----------------------------------------------------------------------------------------------------------------
x_www_form_cp1252_KeyVal_t* x_www_form_cp1252_Header_t::first(void)
{
   return (x_www_form_cp1252_KeyVal_t*)_mk_ptr_(LPVOID, this, sizeof(x_www_form_cp1252_Header_t));
}
// -----------------------------------------------------------------------------------------------------------------
void x_www_form_cp1252_Header_t::decode_and_parse_string(LPSTR p, UINT cb, BOOL u2a_convert)
{
   if (cb < 1) {
      return;
   }
   if (*p == '?') {
      cb--; p++;
   }
   if (cb < 1) {
      return;
   }
   x_www_form_cp1252_KeyVal_t* k;
   LPSTR pOut = m_pBuffer;
   void* buffer = _xgrab(m_cbBuffer);
   for (k = first(); cb; k = k->next())
   {
      if (k->read_and_decode(p, cb, pOut, m_cbString, buffer, u2a_convert)) m_nItemCount++;
   }
   _xfree(buffer);
}
// -----------------------------------------------------------------------------------------------------------------
BOOL x_www_form_cp1252_KeyVal_t::read_and_decode(LPSTR& pIn, UINT& cbIn, LPSTR& pOut, UINT& cbOut, void* buffer, BOOL u2a_convert)
{
   if (!cbIn) {
      return 0;
   }
   LPSTR p = (LPSTR)buffer;
   UINT cb = 0;
   BOOL bk = FALSE;
   while (cbIn)
   {
      char ch = *pIn; pIn++; cbIn--;
      switch (ch)
      {
         case '\0':
         case '&':
         {
            goto label_exit_loop_1;
         }
         case '+':
         {
            p[cb] = 0x20; cb++; break;
         }
         case '\r':
         case '\n':
         case '\t':
         case 0x20:
         {
            break;
         } // ignore blank spaces and line feeds
         case '%':
         {
            if (cbIn < 2) {
               cbIn = 0; goto label_exit_loop_1;
            }
            BYTE hi = __NIBBLECHAR__[((BYTE)*pIn)]; pIn++; cbIn--;
            BYTE lo = __NIBBLECHAR__[((BYTE)*pIn)]; pIn++; cbIn--;
            if (hi && lo)
            {
               p[cb] = (char)(((hi << 4) & 0xF0) | (lo & 0x0F));
               cb++;
            }
            break;
         }
         case '=':
         {
            if (bk) // usually encoded but are allowed inside the value
            {
               p[cb] = ch; cb++;
            }
            else
            {
               bk = TRUE;
               p[cb] = 0; cb++;
               m_pKey = pOut;
               m_cbKey = cb - 1;
               _bcopy((LPBYTE)pOut, (LPBYTE)buffer, cb);
               pOut = _mk_ptr_(LPSTR, pOut, cb);
               cbOut += cb;
               p = (LPSTR)buffer; cb = 0;
            }
            break;
         }
         default:
         {
            p[cb] = ch; cb++; break;
         }
      }
   }
label_exit_loop_1:;
   if (!bk) {
      m_pKey = pOut; m_cbKey = 0; pOut[0] = 0; pOut++; cbOut++;
   }
   p[cb] = 0;
   if (cb)
   {
      if (u2a_convert)
      {
         int    cc = 0;
         LPWSTR pw = utf82w((LPSTR)buffer, cb, &cc);
         m_pVal = pOut;
         cb = WideCharToMultiByte(CP_ACP, 0, pw, cc, NULL, 0, 0, 0);
         m_cbVal = WideCharToMultiByte(CP_ACP, 0, pw, cc, m_pVal, cb + 1, 0, 0);
         pOut = _mk_ptr_(LPSTR, pOut, cb + 1);
         cbOut += cb + 1;
         _xfree((void*)pw);
      }
      else
      {
         m_pVal = pOut;
         _bcopy((LPBYTE)m_pVal, (LPBYTE)buffer, cb + 1);
         m_cbVal = cb + 1;
         pOut = _mk_ptr_(LPSTR, pOut, cb + 1);
         cbOut += cb + 1;
      }
   }
   else
   {
      m_pVal = pOut; m_cbVal = 0; pOut[0] = 0; pOut++; cbOut++;
   }
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR ot4xb_urldecode(LPSTR pIn, DWORD cbIn, DWORD* pcbOut)
{
   LPSTR pOut = 0;
   DWORD cb = 0;
   if (cbIn & 0x80000000) {
      cbIn = 0;
   } // disallow negative numbers

   if (pIn && cbIn)
   {
      LPSTR p = pOut = (LPSTR)_xgrab(cbIn + 2);
      while (cbIn)
      {
         char ch = *pIn; pIn++; cbIn--;
         switch (ch)
         {
            case '\0':
            {
               goto label_exit_loop_1;
            }
            case '+':
            {
               p[cb] = 0x20; cb++; break;
            }
            case '\r':
            case '\n':
            case '\t':
            case 0x20:
            {
               break;
            } // ignore blank spaces and line feeds
            case '%':
            {
               if (cbIn < 2) {
                  cbIn = 0; goto label_exit_loop_1;
               }
               BYTE hi = __NIBBLECHAR__[((BYTE)*pIn)]; pIn++; cbIn--;
               BYTE lo = __NIBBLECHAR__[((BYTE)*pIn)]; pIn++; cbIn--;
               if (hi && lo)
               {
                  p[cb] = (char)(((hi << 4) & 0xF0) | (lo & 0x0F));
                  cb++;
               }
               break;
            }
            default:
            {
               p[cb] = ch; cb++; break;
            }
         }
      }
   label_exit_loop_1:;
      p[cb] = 0;
   }
   if (pcbOut) {
      pcbOut[0] = cb;
   }
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------
#define lw_( ch ) ( (char) _lower_ansi_char_table_[ (BYTE) (ch) ] )
#define lwtb_( ch , tb) ( tb ? ( (char) tb[ (BYTE) (ch) ] ) : ch)
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL bStrWildCmp(LPSTR pWild, LPSTR pStr)
{
   return bStrWildCmpWithTableEx(pWild, pStr, 0, 0, 0, 0);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL bStrWildCmpEx(LPSTR pWild, LPSTR pStr, DWORD flags, DWORD, DWORD)
{
   return bStrWildCmpWithTableEx(pWild, pStr, 0, flags, 0, 0);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL bStrWildCmpWithTable(LPSTR pWild, LPSTR pStr, LPBYTE tb)
{
   return bStrWildCmpWithTableEx(pWild, pStr, tb, 0, 0, 0);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL bStrWildCmpWithTableEx(LPSTR pWild, LPSTR pStr, LPBYTE tb, DWORD flags, DWORD, DWORD)
{
   LPSTR cp = NULL;
   LPSTR mp = NULL;
   int   cb = -1;
   int   cbb = 0;
   BOOL  bTrue = TRUE;
   BOOL  bFalse = FALSE;


   if ((flags & 0x40) && (*pWild == '^'))
   {
      pWild++;
      bTrue = FALSE;
      bFalse = TRUE;
   }

   if ((flags & 0x8000) && ((*pWild == '~') || (*pWild == '`')))
   {
      pWild++;
   }


   if (flags & 0x10)
   {
      while (*pStr == 32)
      {
         pStr++; cb--;
      }
   }
   if (flags & 0x20)
   {
      for (cb = _xstrlen(pStr); cb && pStr[cb - 1] == 32; cb--);
   }

   while ((*pStr) && cb && (*pWild != '*'))
   {
      if ((lwtb_(*pWild, tb) != lwtb_(*pStr, tb)) && (*pWild != '?'))
      {
         return bFalse;
      }
      pWild++; pStr++; cb--;
   }
   while (*pStr && cb)
   {
      if (*pWild == '*')
      {
         pWild++;
         if (!*pWild)
         {
            return bTrue;
         }
         mp = pWild;
         cp = pStr + 1;
         cbb = cb - 1;

      }
      else
      {
         if ((lwtb_(*pWild, tb) == lwtb_(*pStr, tb)) || (*pWild == '?'))
         {
            pWild++; pStr++; cb--;
         }
         else
         {
            pWild = mp; pStr = cp++; cb = cbb--;
         }
      }
   }
   while (*pWild == '*') {
      pWild++;
   }
   return ((BOOL)!*pWild ? bTrue : bFalse);
}

// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL bAnyStrWildCmpI(TList* wild_list, LPSTR pStr)
{
   UINT n;
   UINT nn = wild_list->Count();
   for (n = 0; n < nn; n++)
   {
      if (bStrWildCmpWithTable((LPSTR)wild_list->Get(n), pStr, _lower_ansi_char_table_))
      {
         return TRUE;
      }
   }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL bStrWildCmpI(LPSTR pWild, LPSTR pStr)
{
   return bStrWildCmpWithTable(pWild, pStr, _lower_ansi_char_table_);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void ansi_capitalize(LPSTR p, int cb)
{
   if (!p) {
      return;
   }
   if (cb < 0) {
      cb = (int)_xstrlen(p);
   }
   BOOL bf = TRUE;
   for (; cb > 0; cb--, p++)
   {
      if (((BYTE)*p) > 32)
      {
         if (bf) {
            CharUpperBuff(p, 1); bf = FALSE;
         }
         else {
            CharLowerBuff(p, 1);
         }
      }
      else
      {
         bf = TRUE;
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL bIsNibble(char ch, DWORD* pNibble, int nNibble)
{
   BYTE b = __NIBBLECHAR__[(BYTE)ch];
   DWORD dw = ((b & 0x0F) << (nNibble * 4));
   if (!b)
   {
      return FALSE;
   }
   if (pNibble) {
      pNibble[0] = dw;
   }
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API int ansi_byte_to_utf8_urlenc(BYTE ch, LPBYTE buffer, int nLevel) // default 4// note : buffer must be able to alloc at least 12 characters
{
   BOOL b = FALSE;
   if (nLevel < 0)
   {
      b = (BOOL)(ch == '%');
   }
   else
   {
      if ((ch == 0x20) && (nLevel < 5)) {
         buffer[0] = (BYTE)'+'; return 1;
      }
      if (isalnum(ch)) {
         buffer[0] = ch; return 1;
      }
      b = (((ch < 33) || (ch > 126)) ? 1 : 0);
      if (nLevel > 4) {
         b = TRUE;
      }
      if (!b)
      {
         switch (ch)
         {
            case '+': case '%': case '^': case '&': case '`': case '{': case '}': case '|': case ']': case '[':
            case 0x22: case '<': case '>': case 0x5C:
            {
               b = TRUE; break;
            }
            case ':':  case '/': case '?': case '#':
            {
               b = (BOOL)(nLevel > 1); break;
            }
            default:
            {
               break;
            }
         }
      }
   }

   BYTE wsz[2]; ZeroMemory(wsz, sizeof(wsz));
   int  wcb = MultiByteToWideChar(1252, 0, (LPSTR)&ch, 1, (LPWSTR)wsz, 2);
   BYTE usz[16]; ZeroMemory(usz, sizeof(usz));
   int  ucb = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wsz, wcb, (LPSTR)usz, 16, 0, 0);
   int n;
   if (b)
   {
      for (n = 0; n < ucb; n++)
      {
         buffer[0] = (BYTE)'%';
         buffer[1] = __HEXNIBBLE__[MSNIBBLE(usz[n])];
         buffer[2] = __HEXNIBBLE__[LSNIBBLE(usz[n])];
         buffer = _mk_ptr_(LPBYTE, buffer, 3);
      }
      return (ucb * 3);
   }
   for (n = 0; n < ucb; n++) {
      buffer[n] = usz[n];
   }
   return ucb;
}
// -----------------------------------------------------------------------------------------------------------------
// like    QPDecode() from ATL but with flag 0x8000 to preserve hard CRLFs
OT4XB_API BOOL ot4xb_qp_decode(LPBYTE p, int cb, LPSTR p_out, int* pcb_out, DWORD dwFlags)
{
   if (!(dwFlags & 0x8000))
   {
      // let the atl QPDecode() do the work
      return QPDecode(p, cb, p_out, pcb_out, dwFlags);
   }
   if (!(p && cb && p_out && pcb_out))
   {
      return FALSE;
   }

   if (cb > *pcb_out)
   {
      return FALSE;
   }

   int cbo = 0;
   for (; cb > 0; cb--, p++)
   {
      if (*p == (BYTE)'=')
      {
         if (cb > 2)
         {
            if ((p[1] == 13) && (p[2] == 10))
            {
               cb -= 2;  p = _mk_ptr_(LPBYTE, p, 2);
            }
            else
            {
               if ((((p[1] >= 'A') && (p[1] <= 'F')) || ((p[1] >= '0') && (p[1] <= '9'))) &&
                  (((p[2] >= 'A') && (p[2] <= 'F')) || ((p[2] >= '0') && (p[2] <= '9'))))
               {
                  p_out[cbo] = (chHex2Nibble(p[1]) << 4) | chHex2Nibble(p[2]); cbo++;
                  cb -= 2;  p = _mk_ptr_(LPBYTE, p, 2);
               }
            }
         }
      }
      else
      {
         p_out[cbo] = (char)*p;
         cbo++;
      }
   }
   pcb_out[0] = cbo;
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API int ot4xb_qp_decode_required_length(int nSrcLen)
{
   return QPDecodeGetRequiredLength(nSrcLen);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API int ot4xb_base64_encode_required_length(int nSrcLen)
{
   return Base64EncodeGetRequiredLength(nSrcLen);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL ot4xb_base64_encode(LPBYTE pSrc, int nSrcLen, LPSTR szDest, int* pnDestLen, DWORD dwFlags)
{
   return Base64Encode(pSrc, nSrcLen, szDest, pnDestLen, dwFlags);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API int ot4xb_base64_decode_required_length(int nSrcLen)
{
   return Base64DecodeGetRequiredLength(nSrcLen);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL ot4xb_base64_decode(LPSTR szSrc, int nSrcLen, BYTE* pbDest, int* pnDestLen)
{
   return Base64Decode(szSrc, nSrcLen, pbDest, pnDestLen);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL ot4xb_uu_decode_required_length(int nSrcLen)
{
   return UUDecodeGetRequiredLength(nSrcLen);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL ot4xb_uu_decode(BYTE* pbSrcData, int nSrcLen, BYTE* pbDest, int* pnDestLen)
{
   return UUDecode(pbSrcData, nSrcLen, pbDest, pnDestLen);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR unescape_from_json(LPSTR pIn, UINT* pcbOut)
{
   TZString z;
   LPSTR pOut = 0;
   UINT  cbOut = 0;
   if (pIn)
   {
      LPSTR p = pIn;
      int status = 0;
      for (; *p && (status == 0); p++)
      {
         switch (*p)
         {
            case 0x09: case 0x10: case 0x13: case 0x20:
            {
               break;
            }
            case 0x22:
            {
               status = 1; break;
            }
            default:
            {
               status = -1; break;
            }
         }
      }
      if (status > 0)
      {
         WORD w = 0;
         for (; *p && (status > 0); p++)
         {
            if (status == 1)
            {
               switch (*p)
               {
                  case 0x22:
                  {
                     status = 0; break;
                  }
                  case '\\':
                  {
                     status = 2; break;
                  }
                  case 0x09: case 0x10: case 0x13:
                  {
                     break;
                  } // ignore unencoded tabs or CRLFs
                  default:
                  {
                     z.AddChar(*p);
                     break;
                  }
               }
            }
            else if (status == 2) // \ found
            {
               switch (*p)
               {
                  case 'u':
                  {
                     w = 0; status = 3; break;
                  }
                  case '\\':
                  {
                     z.AddChar(*p); status = 1; break;
                  }
                  case '/':
                  {
                     z.AddChar(*p); status = 1; break;
                  }
                  case 0x22:
                  {
                     z.AddChar(*p); status = 1; break;
                  }
                  case 'b':
                  {
                     z.AddChar(0x08); status = 1; break;
                  }
                  case 't':
                  {
                     z.AddChar(0x09); status = 1; break;
                  }
                  case 'n':
                  {
                     z.AddChar(0x0A); status = 1; break;
                  }
                  case 'f':
                  {
                     z.AddChar(0x0C); status = 1; break;
                  }
                  case 'r':
                  {
                     z.AddChar(0x0D); status = 1; break;
                  }
                  default:
                  {
                     status = -1;
                     break;
                  }
               }
            }
            else if ((status > 2) && (status < 7)) // \u found  3456
            {
               BYTE nibble = chHex2Nibble((BYTE)*p);
               if (nibble || (*p == '0'))
               {
                  w = (w << 4) | nibble;
                  status++;
                  if (status > 6)
                  {
                     char sz[8]; ZeroMemory(sz, sizeof(sz));
                     WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&w, 1, sz, sizeof(sz) - 1, 0, 0);
                     z.Add(sz);
                     status = 1;
                  }
               }
               else
               {
                  status = -1;
               }
            }
            else
            {
               status = -1;
            }
         }
         if (status == 0)
         {
            pOut = mb2mb(z.GetBuffer(), (int)z.len(), (int*)&cbOut, CP_UTF8, CP_ACP, 0, 0);
         }
      }
   }
   if (pcbOut)
   {
      pcbOut[0] = cbOut;
   }
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
DWORD rfc2047_hash2codepage(DWORD dwcph)
{
   switch (dwcph)
   {
      case 0xDC3AD16D:
      {
         return    37;
      } // IBM037
      case 0xDB3379B1:
      {
         return   437;
      } // IBM437
      case 0x6FB8D5E6:
      {
         return   500;
      } // IBM500
      case 0x8FD34379:
      {
         return   708;
      } // ASMO-708
      case 0x1D907033:
      {
         return   720;
      } // DOS-720
      case 0xD975C7E8:
      {
         return   737;
      } // ibm737
      case 0x531763C0:
      {
         return   775;
      } // ibm775
      case 0x1A17B2F0:
      {
         return   850;
      } // ibm850
      case 0xF419D3DC:
      {
         return   852;
      } // ibm852
      case 0x6A7D467F:
      {
         return   855;
      } // IBM855
      case 0x84732753:
      {
         return   857;
      } // ibm857
      case 0xF384AB96:
      {
         return   858;
      } // IBM00858
      case 0x313AE133:
      {
         return   860;
      } // IBM860
      case 0x463DD1A5:
      {
         return   861;
      } // ibm861
      case 0x9CAE9326:
      {
         return   862;
      } // DOS-862
      case 0xA833B089:
      {
         return   863;
      } // IBM863
      case 0x3657252A:
      {
         return   864;
      } // IBM864
      case 0x415015BC:
      {
         return   865;
      } // IBM865
      case 0x1F51EAD8:
      {
         return   866;
      } // cp866
      case 0x48E65997:
      {
         return   869;
      } // ibm869
      case 0x2821D072:
      {
         return   870;
      } // IBM870
      case 0x4D542171:
      {
         return   874;
      } // windows-874
      case 0x9F438A23:
      {
         return   875;
      } // cp875
      case 0x4BE552A4:
      {
         return   932;
      } // shift_jis
      case 0x354487BD:
      {
         return   936;
      } // gb2312
      case 0x6FB9286F:
      {
         return   949;
      } // ks_c_5601-1987
      case 0x8B622978:
      {
         return   950;
      } // big5
      case 0xE9EA7059:
      {
         return  1026;
      } // IBM1026
      case 0xCC8FB19B:
      {
         return  1047;
      } // IBM01047
      case 0x53294E0F:
      {
         return  1140;
      } // IBM01140
      case 0x242E7E99:
      {
         return  1141;
      } // IBM01141
      case 0xBD272F23:
      {
         return  1142;
      } // IBM01142
      case 0xCA201FB5:
      {
         return  1143;
      } // IBM01143
      case 0x54448A16:
      {
         return  1144;
      } // IBM01144
      case 0x2343BA80:
      {
         return  1145;
      } // IBM01145
      case 0xBA4AEB3A:
      {
         return  1146;
      } // IBM01146
      case 0xCD4DDBAC:
      {
         return  1147;
      } // IBM01147
      case 0x5DF2C63D:
      {
         return  1148;
      } // IBM01148
      case 0x2AF5F6AB:
      {
         return  1149;
      } // IBM01149
      case 0xC1409499:
      {
         return  1200;
      } // utf-16
      case 0x665924FF:
      {
         return  1201;
      } // unicodeFFFE
      case 0xB14C768A:
      {
         return  1250;
      } // windows-1250
      case 0xC64B461C:
      {
         return  1251;
      } // windows-1251
      case 0x5F4217A6:
      {
         return  1252;
      } // windows-1252
      case 0x28452730:
      {
         return  1253;
      } // windows-1253
      case 0xB621B293:
      {
         return  1254;
      } // windows-1254
      case 0xC1268205:
      {
         return  1255;
      } // windows-1255
      case 0x582FD3BF:
      {
         return  1256;
      } // windows-1256
      case 0x2F28E329:
      {
         return  1257;
      } // windows-1257
      case 0xBF97FEB8:
      {
         return  1258;
      } // windows-1258
      case 0xEF7BBFAE:
      {
         return  1361;
      } // Johab
      case 0x046E6B37:
      {
         return 10000;
      } // macintosh
      case 0xFDA39FA1:
      {
         return 10001;
      } // x-mac-japanese
      case 0x7127DDCB:
      {
         return 10002;
      } // x-mac-chinesetrad
      case 0xAB037EF6:
      {
         return 10003;
      } // x-mac-korean
      case 0x636316E2:
      {
         return 10004;
      } // x-mac-arabic
      case 0x2E509B57:
      {
         return 10005;
      } // x-mac-hebrew
      case 0x4316E1CF:
      {
         return 10006;
      } // x-mac-greek
      case 0x37F31003:
      {
         return 10007;
      } // x-mac-cyrillic
      case 0x4AEC3292:
      {
         return 10008;
      } // x-mac-chinesesimp
      case 0x5BB68F18:
      {
         return 10010;
      } // x-mac-romanian
      case 0xBCFEABC1:
      {
         return 10017;
      } // x-mac-ukrainian
      case 0x4EA582DD:
      {
         return 10021;
      } // x-mac-thai
      case 0xCECB6F84:
      {
         return 10029;
      } // x-mac-ce
      case 0xB5C89EA8:
      {
         return 10079;
      } // x-mac-icelandic
      case 0xE765D5FD:
      {
         return 10081;
      } // x-mac-turkish
      case 0x9FC25553:
      {
         return 10082;
      } // x-mac-croatian
      case 0xB9DDEA84:
      {
         return 20000;
      } // x-Chinese_CNS
      case 0xFF449943:
      {
         return 20001;
      } // x-cp20001
      case 0xE39C8FCC:
      {
         return 20002;
      } // x_Chinese-Eten
      case 0x114AF86F:
      {
         return 20003;
      } // x-cp20003
      case 0x8F2E6DCC:
      {
         return 20004;
      } // x-cp20004
      case 0xF8295D5A:
      {
         return 20005;
      } // x-cp20005
      case 0x308B459A:
      {
         return 20105;
      } // x-IA5
      case 0x02C0ADAF:
      {
         return 20106;
      } // x-IA5-German
      case 0x54385AC2:
      {
         return 20107;
      } // x-IA5-Swedish
      case 0x2BE4476B:
      {
         return 20108;
      } // x-IA5-Norwegian
      case 0xF038B127:
      {
         return 20127;
      } // us-ascii
      case 0xAA9AEAAB:
      {
         return 20261;
      } // x-cp20261
      case 0xA4416299:
      {
         return 20269;
      } // x-cp20269
      case 0xBCBF041E:
      {
         return 20273;
      } // IBM273
      case 0xBBD2C007:
      {
         return 20277;
      } // IBM277
      case 0x2B6DDD96:
      {
         return 20278;
      } // IBM278
      case 0xA22E496B:
      {
         return 20280;
      } // IBM280
      case 0xA5438D72:
      {
         return 20284;
      } // IBM284
      case 0xD244BDE4:
      {
         return 20285;
      } // IBM285
      case 0xBB35782A:
      {
         return 20290;
      } // IBM290
      case 0x2551ED89:
      {
         return 20297;
      } // IBM297
      case 0x5C4CDD53:
      {
         return 20420;
      } // IBM420
      case 0xC5458CE9:
      {
         return 20423;
      } // IBM423
      case 0x5B21194A:
      {
         return 20424;
      } // IBM424
      case 0xBEF68E3F:
      {
         return 20833;
      } // x-EBCDIC-KoreanExtended
      case 0xD185E04D:
      {
         return 20838;
      } // IBM-Thai
      case 0x3AE4F8F8:
      {
         return 20866;
      } // koi8-r
      case 0x5F26E0E4:
      {
         return 20871;
      } // IBM871
      case 0xAFB9CCBD:
      {
         return 20880;
      } // IBM880
      case 0x16C8D80D:
      {
         return 20905;
      } // IBM905
      case 0xB4B11B4D:
      {
         return 20924;
      } // IBM00924
      case 0x0ED82FBA:
      {
         return 20932;
      } // EUC-JP
      case 0x45DC64AC:
      {
         return 20936;
      } // x-cp20936
      case 0x9A22EFFA:
      {
         return 20949;
      } // x-cp20949
      case 0x114FD69E:
      {
         return 21025;
      } // cp1025
      case 0xA4806D5B:
      {
         return 21866;
      } // koi8-u
      case 0x4434A849:
      {
         return 28591;
      } // iso-8859-1
      case 0xDD3DF9F3:
      {
         return 28592;
      } // iso-8859-2
      case 0xAA3AC965:
      {
         return 28593;
      } // iso-8859-3
      case 0x345E5CC6:
      {
         return 28594;
      } // iso-8859-4
      case 0x43596C50:
      {
         return 28595;
      } // iso-8859-5
      case 0xDA503DEA:
      {
         return 28596;
      } // iso-8859-6
      case 0xAD570D7C:
      {
         return 28597;
      } // iso-8859-7
      case 0x3DE810ED:
      {
         return 28598;
      } // iso-8859-8
      case 0x4AEF207B:
      {
         return 28599;
      } // iso-8859-9
      case 0x62964307:
      {
         return 28603;
      } // iso-8859-13
      case 0x8BF5E632:
      {
         return 28605;
      } // iso-8859-15
      case 0x4AC13074:
      {
         return 29001;
      } // x-Europa
      case 0xA3FA31C1:
      {
         return 38598;
      } // iso-8859-8-i
      case 0xF90E5180:
      {
         return 50220;
      } // iso-2022-jp
      case 0x4A670F2B:
      {
         return 50221;
      } // csISO2022JP
   //case 0xF90E5180 : { return 50222; } // iso-2022-jp
      case 0x0E1B01ED:
      {
         return 50225;
      } // iso-2022-kr
      case 0x95B5568A:
      {
         return 50227;
      } // x-cp50227
   //case 0x0ED82FBA : { return 51932; } // euc-jp
      case 0x2515A990:
      {
         return 51936;
      } // EUC-CN
      case 0xF9CD7FD7:
      {
         return 51949;
      } // euc-kr
      case 0x66BD1860:
      {
         return 52936;
      } // hz-gb-2312
      case 0xC946F230:
      {
         return 54936;
      } // GB18030
      case 0x373E874E:
      {
         return 57002;
      } // x-iscii-de
      case 0x616420C8:
      {
         return 57003;
      } // x-iscii-be
      case 0x7A915106:
      {
         return 57004;
      } // x-iscii-ta
      case 0x7DFC951F:
      {
         return 57005;
      } // x-iscii-te
      case 0xBE9DC65A:
      {
         return 57006;
      } // x-iscii-as
      case 0x5719DB42:
      {
         return 57007;
      } // x-iscii-or
      case 0xB7CB5F98:
      {
         return 57008;
      } // x-iscii-ka
      case 0xE191F81E:
      {
         return 57009;
      } // x-iscii-ma
      case 0x01A4C4E9:
      {
         return 57010;
      } // x-iscii-gu
      case 0x1EFD9402:
      {
         return 57011;
      } // x-iscii-pa
      case 0xC780E71B:
      {
         return 65000;
      } // utf-7
      case 0x573FFA8A:
      {
         return 65001;
      } // utf-8



   }
   return (DWORD)0;
}
// -----------------------------------------------------------------------------------------------------------------
// =?codepage?BQ?string?=
extern "C" OT4XB_API LPSTR rfc2047decode(LPSTR pIn, UINT * pcbOut, DWORD nOutCodePage, DWORD nBlockSize)
{
   LPSTR pOut = 0;
   UINT  cbOut = 0;
   if (nBlockSize < 4096) {
      nBlockSize = 4096;
   }
   if (nBlockSize > 0x100000) {
      nBlockSize = 0x100000;
   }


   if (pIn)
   {
      xstream_t z(nBlockSize, nBlockSize);
      LPSTR p = pIn;
      LPSTR p1 = 0;
      DWORD dwcph = 0;
      DWORD dwcp = 0;
      for (; *p; p++)
      {
         if (p1)
         {
            if (*p == '?')
            {
               dwcp = rfc2047_hash2codepage(dwcph);
               if (dwcp && (p[1] == 'Q') || (p[1] == 'q') || (p[1] == 'B') || (p[1] == 'b'))
               {
                  if (p[2] == '?')
                  {
                     LPSTR ps = _mk_ptr_(LPSTR, p, 3);
                     DWORD cbs = 0;
                     for (; ps[cbs] && (ps[cbs] == '?' ? ps[cbs + 1] != '=' : 1); cbs++);
                     if (ps[cbs])
                     {
                        DWORD offset = z._offset_len_();
                        if ((p[1] == 'Q') || (p[1] == 'q'))
                        {
                           z.append_decode_qp(ps, (int)cbs, 0);
                        }
                        else
                        {
                           z.append_decode_base64(ps, (int)cbs);
                        }
                        int cbd = 0;
                        LPSTR pd = mb2mb((LPSTR)z._offset_ptr_(offset), (int)z._offset_len_(offset), &cbd, dwcp, nOutCodePage, 0, 0);
                        if (pd)
                        {
                           z._truncate_buffer_(offset);
                           z.append_buffer((void*)pd, (DWORD)cbd);
                           _xfree((void*)pd);
                        }
                        cbd = 0; pd = 0;
                        p = _mk_ptr_(LPSTR, ps, cbs + 1);
                        p1 = 0;
                        goto LabelEndLoop;
                     }
                  }
               }
               // if anything fail just add the string without decode
               p = p1; p1 = 0;
               for (; *p && (*p == '?' ? p[1] != '=' : 1); p++)
               {
                  z.append_BYTE((BYTE)*p);
               }
               if (*p && (*p == '?' ? p[1] == '=' : 0))
               {
                  z.append_BYTE((BYTE)*p);
                  p++;
                  z.append_BYTE((BYTE)*p);
               }
               goto LabelEndLoop;
            }
            else
            {
               dwcph = dwCrc32Lower(dwcph, (LPBYTE)p, 1);
            }
         }
         else
         {
            if (*p == '=')
            {
               if (p[1] == '?')
               {
                  p1 = p;
                  p++;
                  dwcph = 0;
                  goto LabelEndLoop;
               }
            }
            z.append_BYTE((BYTE)*p);
            goto LabelEndLoop;
         }
      LabelEndLoop:;
      }
      if (p1)
      {
         z.append_buffer((void*)p1, (DWORD)-1);
      }
      z.ansi_ZSafe();
      pOut = (LPSTR)z.Detach(&cbOut);
   }
   if (pcbOut) {
      pcbOut[0] = cbOut;
   }
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------
namespace base32_ns
{
   static char base32_rfc4648_alphabet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M','N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '2', '3', '4', '5', '6', '7' };
   static char base32_crockford_alphabet[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J','K', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z' };
   // --------------------------------------------------------------------------------------------------------------
   int crockford_char_to_index(char ch)
   {
      int index;
      if (ch == '=')
      {
         return -2;
      }
      if (ch >= 'a' && ch <= 'z')
      {
         ch = (ch - 'a' + 'A');
      }
      if (ch == 'O')
      {
         ch = '0';
      }
      if (ch == 'I' || ch == 'L')
      {
         ch = '1';

      }
      for (index = 0; index < 32; index++)
      {
         if (ch == base32_crockford_alphabet[index])
         {
            return index;
         }

      }
      return -1;
   }
   // --------------------------------------------------------------------------------------------------------------
   DWORD required_padding(int nBytes)
   {
      return (DWORD)("\0\6\4\3\1"[(nBytes % 5)] & 0x000F);
   }
   // --------------------------------------------------------------------------------------------------------------
   DWORD encode_required_size(DWORD cb)
   {
      return (cb * 8 + 4) / 5;
   }
   // --------------------------------------------------------------------------------------------------------------
   DWORD decode_required_size(DWORD cb)
   {
      return  (((cb + 7) / 8) * 5) + 1;
   }
   // --------------------------------------------------------------------------------------------------------------
   DWORD encode_5_bytes_block(LPSTR pDigitTable, LPBYTE& pSource, DWORD& cbSource, LPSTR& pDestination, DWORD& cbMaxDestination, DWORD& output_bytes_written) // input_size
   {
      BYTE input_block[5];
      DWORD input_size = ((cbSource < 5) ? cbSource : 5);
      char output_block[9];
      DWORD output_size = ((cbMaxDestination < 8) ? cbMaxDestination : 8);
      if (!input_size)
      {
         return 0;
      }
      ZeroMemory(input_block, sizeof(input_block));
      memcpy((void*)input_block, pSource, input_size);

      ZeroMemory(output_block, sizeof(output_block));

      // 00000 
      // 76543 210       || 0x1F = ?00011111?
      output_block[0] = (input_size > 0 ? pDigitTable[((input_block[0] >> 3) & 0x1F)] : '=');

      //        00011 
      // 76543  21076 54321 0       || 0x1C = 00011100    || 0x03 = 00000011
      output_block[1] = (input_size > 0 ? pDigitTable[((input_block[0] << 2) & 0x1C) | ((input_block[1] >> 6) & 0x03)] : '=');

      //     11111 
      // 76  54321 0                || 0x1F = ?00011111?
      output_block[2] = (input_size > 1 ? pDigitTable[((input_block[1] >> 1) & 0x1F)] : '=');

      //           12222 
      // 76  54321 07654 3210      ||  0x10 = 00010000         || 0x0F =  00001111   
      output_block[3] = (input_size > 1 ? pDigitTable[((input_block[1] << 4) & 0x10) | ((input_block[2] >> 4) & 0x0F)] : '=');

      //      22223 
      // 7654 32107 65432 10       || 0x1E =  00011110      || 0x01 = 00000001
      output_block[4] = (input_size > 2 ? pDigitTable[((input_block[2] << 1) & 0x1E) | ((input_block[3] >> 7) & 0x01)] : '=');

      //   33333                                                                                                                                 
      // 7 65432 10  || 0x1F = ?00011111?
      output_block[5] = (input_size > 3 ? pDigitTable[((input_block[3] >> 2) & 0x1F)] : '=');

      //         33444 
      // 7 65432 10765 43210   || 0x18 =  00011000      || 0x01 = 00000001
      output_block[6] = (input_size > 3 ? pDigitTable[((input_block[3] << 3) & 0x18) | ((input_block[4] >> 5) & 0x01)] : '=');

      //     44444
      // 765 43210      || 0x1F = ?00011111?
      output_block[7] = (input_size > 4 ? pDigitTable[((input_block[4]) & 0x1F)] : '=');

      memcpy((void*)pDestination, output_block, output_size);
      pDestination = _mk_ptr_(LPSTR, pDestination, output_size);
      cbMaxDestination -= output_size;
      output_bytes_written += output_size;
      pSource = _mk_ptr_(LPBYTE, pSource, input_size);
      cbSource -= input_size;
      return input_size;
   }
   // --------------------------------------------------------------------------------------------------------------
   DWORD encode_to_buffer(LPSTR pDigitTable, LPBYTE pSource, DWORD cbSource, LPSTR pDestination, DWORD cbMaxDestination) // output
   {
      DWORD bytes_written = 0;
      DWORD remaining_space = cbMaxDestination - 1;
      DWORD output_size = 0;
      while (remaining_space && encode_5_bytes_block(pDigitTable, pSource, cbSource, pDestination, remaining_space, bytes_written))
      {
         output_size += bytes_written;
         pDestination[0] = 0;
      }
      return bytes_written;
   }
   // --------------------------------------------------------------------------------------------------------------


 //				template <uint8_t I>
 //				static CPPCODEC_ALWAYS_INLINE constexpr uint8_t index(
 //					const uint8_t* b /*binary block*/) noexcept
 //				{
 //					static_assert(I >= 0 && I < encoded_block_size(),
 //						"invalid encoding symbol index in a block");
 //
 //					return (I == 0) ? ((b[0] >> 3) & 0x1F) // first 5 bits
 //						: (I == 1) ? (((b[0] << 2) & 0x1C) | ((b[1] >> 6) & 0x3))
 //						: (I == 2) ? ((b[1] >> 1) & 0x1F)
 //						: (I == 3) ? (((b[1] << 4) & 0x10) | ((b[2] >> 4) & 0xF))
 //						: (I == 4) ? (((b[2] << 1) & 0x1E) | ((b[3] >> 7) & 0x1))
 //						: (I == 5) ? ((b[3] >> 2) & 0x1F)
 //						: (I == 6) ? (((b[3] << 3) & 0x18) | ((b[4] >> 5) & 0x7))
 //						: /*I == 7*/ (b[4] & 0x1F); // last 5 bits;
 //				}
 //
 //				template <bool B>
 //				using uint8_if = typename std::enable_if<B, uint8_t>::type;
 //
 //				template <uint8_t I>
 //				static CPPCODEC_ALWAYS_INLINE constexpr
 //					uint8_if<I == 1 || I == 3 || I == 4 || I == 6> index_last(
 //						const uint8_t* b /*binary block*/) noexcept
 //				{
 //					return (I == 1) ? ((b[0] << 2) & 0x1C)     // abbreviated 2nd symbol
 //						: (I == 3) ? ((b[1] << 4) & 0x10)  // abbreviated 4th symbol
 //						: (I == 4) ? ((b[2] << 1) & 0x1E)  // abbreviated 5th symbol
 //						: /*I == 6*/ ((b[3] << 3) & 0x18); // abbreviated 7th symbol
 //				}
 //
 //				template <uint8_t I>
 //				static CPPCODEC_ALWAYS_INLINE
 //					uint8_if<I != 1 && I != 3 && I != 4 && I != 6> index_last(
 //						const uint8_t* /*binary block*/)
 //				{
 //					throw std::domain_error("invalid last encoding symbol index in a tail");
 //				}
 //
 //				template <typename Result, typename ResultState>
 //				static CPPCODEC_ALWAYS_INLINE void decode_block(
 //					Result& decoded, ResultState&, const alphabet_index_t* idx);
 //
 //				template <typename Result, typename ResultState>
 //				static CPPCODEC_ALWAYS_INLINE void decode_tail(
 //					Result& decoded, ResultState&, const alphabet_index_t* idx, size_t idx_len);
 //			};
 //
 //			//
 //			//     11111111 10101010 10110011  10111100 10010100
 //			// => 11111 11110 10101 01011 00111 01111 00100 10100
 //			//
 //
 //			template <typename CodecVariant>
 //			template <typename Result, typename ResultState>
 //			CPPCODEC_ALWAYS_INLINE void base32<CodecVariant>::decode_block(
 //				Result& decoded, ResultState& state, const alphabet_index_t* idx)
 //			{
 //				put(decoded, state, static_cast<uint8_t>(((idx[0] << 3) & 0xF8) | ((idx[1] >> 2) & 0x7)));
 //				put(decoded, state, static_cast<uint8_t>(((idx[1] << 6) & 0xC0) | ((idx[2] << 1) & 0x3E) | ((idx[3] >> 4) & 0x1)));
 //				put(decoded, state, static_cast<uint8_t>(((idx[3] << 4) & 0xF0) | ((idx[4] >> 1) & 0xF)));
 //				put(decoded, state, static_cast<uint8_t>(((idx[4] << 7) & 0x80) | ((idx[5] << 2) & 0x7C) | ((idx[6] >> 3) & 0x3)));
 //				put(decoded, state, static_cast<uint8_t>(((idx[6] << 5) & 0xE0) | (idx[7] & 0x1F)));
 //			}
 //
 //			template <typename CodecVariant>
 //			template <typename Result, typename ResultState>
 //			CPPCODEC_ALWAYS_INLINE void base32<CodecVariant>::decode_tail(
 //				Result& decoded, ResultState& state, const alphabet_index_t* idx, size_t idx_len)
 //			{
 //				if (idx_len == 1) {
 //					throw invalid_input_length(
 //						"invalid number of symbols in last base32 block: found 1, expected 2, 4, 5 or 7");
 //				}
 //				if (idx_len == 3) {
 //					throw invalid_input_length(
 //						"invalid number of symbols in last base32 block: found 3, expected 2, 4, 5 or 7");
 //				}
 //				if (idx_len == 6) {
 //					throw invalid_input_length(
 //						"invalid number of symbols in last base32 block: found 6, expected 2, 4, 5 or 7");
 //				}
 //
 //				// idx_len == 2: decoded size 1
 //				put(decoded, state, static_cast<uint8_t>(((idx[0] << 3) & 0xF8) | ((idx[1] >> 2) & 0x7)));
 //				if (idx_len == 2) {
 //					return;
 //				}
 //				// idx_len == 4: decoded size 2
 //				put(decoded, state, static_cast<uint8_t>(((idx[1] << 6) & 0xC0) | ((idx[2] << 1) & 0x3E) | ((idx[3] >> 4) & 0x1)));
 //				if (idx_len == 4) {
 //					return;
 //				}
 //				// idx_len == 5: decoded size 3
 //				put(decoded, state, static_cast<uint8_t>(((idx[3] << 4) & 0xF0) | ((idx[4] >> 1) & 0xF)));
 //				if (idx_len == 5) {
 //					return;
 //				}
 //				// idx_len == 7: decoded size 4
 //				put(decoded, state, static_cast<uint8_t>(((idx[4] << 7) & 0x80) | ((idx[5] << 2) & 0x7C) | ((idx[6] >> 3) & 0x3)));
 //			}
 //
 //		} // namespace detail
 //	} // namespace cppcodec
 //
 //#endif // CPPCODEC_DETAIL_BASE32
 //
}
// -------------------------------------------------------------------------------------------------------------------------------------
OT4XB_API int ot4xb_base32_encode_required_length(int nSrcLen)
{
   if (nSrcLen < 1)
   {
      return 0;
   }
   return (int)base32_ns::encode_required_size((int)nSrcLen);
}
// -------------------------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL ot4xb_base32_encode_with_table(LPSTR pTable, LPBYTE pSrc, int nSrcLen, LPSTR szDest, int* pnDestLen, DWORD)
{
   if (!pTable)
   {
      pTable = base32_ns::base32_crockford_alphabet;
   }
   if (nSrcLen < 1)
   {
      return FALSE;
   }
   if (pnDestLen[0] < ot4xb_base32_encode_required_length(nSrcLen))
   {
      return FALSE;
   }
   pnDestLen[0] = base32_ns::encode_to_buffer(pTable, pSrc, (DWORD)nSrcLen, szDest, pnDestLen[0]);
   return TRUE;
}
// -------------------------------------------------------------------------------------------------------------------------------------
// flags & 1 = insert CRLF every 76 chars
// split_data_uri( str , @header , flags ) -> body
_XPP_REG_FUN_(SPLIT_DATA_URI)
{
   TXppParamList xpp(pl, 3);
   DWORD cb = 0;
   LPSTR p = xpp[1]->LockStr(&cb);
   DWORD pos = 0;
   TZString str;
   DWORD flags = xpp[3]->GetDWord();
   for (; pos < cb && (!(p[pos] == ',')); pos++);
   if (pos < cb && (p[pos] == ','))
   {
      xpp[2]->PutStrLen(p, pos);
   }
   else
   {
      xpp[2]->PutStr("");
   }
   pos++;
   while (pos < cb && pos)
   {
      DWORD n;
      for (n = 0; pos < cb && n < 76; pos++, n++)
      {
         str.AddChar(p[pos]);
      }
      if (flags & 1)
      {
         str.AddChar(13);
         str.AddChar(10);
      }
   }
   xpp[0]->PutStrLen(str.GetBuffer(), str.len());

}

// -------------------------------------------------------------------------------------------------------------------------------------
// __b64enc( cStr, nFlags )
_XPP_REG_FUN_(__B64ENC)
{
   TXppParamList xpp(pl, 2);
   DWORD cb_source = 0;
   LPSTR p_source = xpp[1]->LockStr(&cb_source);
   DWORD cb_result = 0;
   if (p_source && ((int)cb_source) > 0)
   {
      int cb = ot4xb_base64_encode_required_length((int)cb_source);
      if (cb > 0)
      {
         cb = cb + 16;
         LPSTR buffer = (LPSTR)_xgrab(cb + 1);
         if (ot4xb_base64_encode((LPBYTE)p_source, (int)cb_source, buffer, &cb, xpp[2]->GetDWord()))
         {
            cb_result = (DWORD)cb;
            xpp[0]->PutStrLen(buffer, cb_result);
         }
         _xfree((void*)buffer);
         buffer = 0;
      }
   }
   if (!cb_result)
   {
      xpp[0]->PutStr("");
   }
}
// -------------------------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(__B64DEC)
{

   TXppParamList xpp(pl, 2);
   DWORD cb_source = 0;
   LPSTR p_source = xpp[1]->LockStr(&cb_source);
   DWORD cb_result = 0;
   if (p_source && ((int)cb_source) > 0)
   {
      int cb = ot4xb_base64_decode_required_length((int)cb_source);
      if (cb > 0)
      {
         LPSTR buffer = (LPSTR)_xgrab(cb + 1);
         if (ot4xb_base64_decode(p_source, (int)cb_source, (LPBYTE)buffer, &cb))
         {
            cb_result = (DWORD)cb;
            xpp[0]->PutStrLen(buffer, cb_result);
         }
         _xfree((void*)buffer);
         buffer = 0;
      }
   }
   if (!cb_result)
   {
      xpp[0]->PutStr("");
   }
}
// -------------------------------------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BOOL  OT4XB_API __cdecl ot4xb_regex_match(LPSTR pattern, LPSTR string_to_test, int flags, int match_flags)
{

   BOOL result;
   std::regex rgx(pattern, (std::regex::flag_type)flags);
   result = std::regex_match(string_to_test, rgx, (std::regex_constants::match_flag_type)match_flags);
   return result;
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
LPSTR OT4XB_API __cdecl ot4xb_regex_replace(LPSTR pattern, LPSTR input_string, LPSTR replacement, DWORD* pcb_out, int flags, int match_flags)
{
   LPSTR p = 0;
   size_t cb = 0;
   std::string text(input_string);
   std::regex rgx(pattern, (std::regex::flag_type)flags);
   std::string output_str = std::regex_replace(text, rgx, replacement, (std::regex_constants::match_flag_type)match_flags);

   cb = output_str.length();
   if (cb > 0)
   {
      p = (LPSTR)_xgrab(cb + 1);
      _bcopy((LPBYTE)p, (LPBYTE)output_str.c_str(), cb);
   }
   if (pcb_out)
   {
      *pcb_out = cb;
   }
   return p;

}
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ot4xb_regex_match(1 pattern, 2 string_to_test, 3 flags, 4 match_flags) -> lMatch
_XPP_REG_FUN_(OT4XB_REGEX_MATCH)
{
   BOOL result = FALSE;
   TXppParamList xpp(pl, 4);
   LPSTR pattern = xpp[1]->LockStr();
   LPSTR string_to_test = xpp[2]->LockStr();
   std::regex::flag_type flags = (std::regex::flag_type)xpp[3]->GetLong();
   std::regex_constants::match_flag_type match_flags = (std::regex_constants::match_flag_type)xpp[4]->GetLong();
   if (pattern && string_to_test)
   {
      std::regex rgx(pattern, flags);
      result = std::regex_match(string_to_test, rgx, match_flags);
   }
   xpp[0]->PutBool(result);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ot4xb_regex_replace(1 pattern, 2 input_string, 3 replacement, 4flags, 5 match_flags)
_XPP_REG_FUN_(OT4XB_REGEX_REPLACE)
{
   TXppParamList xpp(pl, 5);
   LPSTR pattern = xpp[1]->LockStr();
   LPSTR input_string = xpp[2]->LockStr();
   LPSTR replacement = xpp[3]->LockStr();
   std::regex::flag_type flags = (std::regex::flag_type)xpp[4]->GetLong();
   std::regex_constants::match_flag_type match_flags = (std::regex_constants::match_flag_type)xpp[5]->GetLong();

   std::string text(input_string);
   std::regex rgx(pattern, flags);
   std::string output_str = std::regex_replace(text, rgx, replacement, match_flags);

   xpp[0]->PutStrLen((LPSTR)output_str.c_str(), output_str.length());

}

