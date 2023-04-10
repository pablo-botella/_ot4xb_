//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21
//----------------------------------------------------------------------------------------------------------------------
static inline DWORD rotate_left(DWORD x, DWORD n){ return ((x << n) | (x >> (32-n)));}
//----------------------------------------------------------------------------------------------------------------------
static inline DWORD F(DWORD x, DWORD y, DWORD z){return (x & y) | (~x & z);}
static inline DWORD G(DWORD x, DWORD y, DWORD z){return ((x & z) | (y & ~z));}
static inline DWORD H(DWORD x, DWORD y, DWORD z){return (x ^ y ^ z);}
static inline DWORD I(DWORD x, DWORD y, DWORD z){return (y ^ (x | ~z));}
//----------------------------------------------------------------------------------------------------------------------
static inline void FF(DWORD& a,DWORD b,DWORD c,DWORD d,DWORD x,DWORD s,DWORD ac)
{a += F(b, c, d) + x + ac; a = rotate_left (a, s) +b;}
//----------------------------------------------------------------------------------------------------------------------
static inline void GG(DWORD& a, DWORD b, DWORD c, DWORD d, DWORD x,DWORD s, DWORD ac)
{a += G(b, c, d) + x + ac;a = rotate_left (a, s) +b;}
// -----------------------------------------------------------------------------------------------------------------
static inline void HH(DWORD& a, DWORD b, DWORD c, DWORD d, DWORD x,DWORD s, DWORD ac)
{a += H(b, c, d) + x + ac; a = rotate_left (a, s) +b;}
// -----------------------------------------------------------------------------------------------------------------
static inline void II(DWORD& a, DWORD b, DWORD c, DWORD d,DWORD x,DWORD s,DWORD ac)
{a += I(b, c, d) + x + ac;a = rotate_left(a,s)+b;}
// -----------------------------------------------------------------------------------------------------------------
static void _encode_(LPBYTE pOut,DWORD* pIn,DWORD cb)
{
   DWORD dwi,dwo;
   for(dwi = dwo = 0; dwo < cb; dwi++, dwo += 4)
   {
      pOut[dwo]   = (BYTE) ( pIn[dwi]        & 0xFF);
      pOut[dwo+1] = (BYTE) ((pIn[dwi] >>  8) & 0xFF);
      pOut[dwo+2] = (BYTE) ((pIn[dwi] >> 16) & 0xFF);
      pOut[dwo+3] = (BYTE) ((pIn[dwi] >> 24) & 0xFF);
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void _decode_(DWORD *pdwo, BYTE *pi, DWORD cb)
{    
   DWORD i,j;
   for(i = 0,j = 0;j < cb;i++,j += 4)
   {
      pdwo[i] = ((DWORD)pi[j])|(((DWORD)pi[j+1])<<8)|(((DWORD)pi[j+2])<<16)|(((DWORD)pi[j+3])<< 24);
   }
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_md5_internal::init(void)
{
   m_pdwState[0] = 0x67452301; m_pdwState[1] = 0xEFCDAB89; m_pdwState[2] = 0x98BADCFE; m_pdwState[3] = 0x10325476;
   m_pdwCount[0] = m_pdwCount[1] = 0;
   _bset(m_pBuffer,0,64);
   _bset(m_pDigest,0,16);
   m_bFinalized = FALSE;
   m_bOk = TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
ot4xb_md5_internal::ot4xb_md5_internal(void){ init(); }
// -----------------------------------------------------------------------------------------------------------------
ot4xb_md5_internal::ot4xb_md5_internal(LPBYTE pStr,UINT cb){init();Update(pStr,cb);Finalize();}
// -----------------------------------------------------------------------------------------------------------------
ot4xb_md5_internal::ot4xb_md5_internal(HANDLE hFile){init();Update(hFile);Finalize();}
// -----------------------------------------------------------------------------------------------------------------
BOOL ot4xb_md5_internal::Update(LPBYTE pInput,UINT cb)
{
   DWORD dwii,dwbi,cbbf;
   if( m_bFinalized ){m_bOk = FALSE;}
   if(!m_bOk ){return FALSE;}
   dwbi = (DWORD)((m_pdwCount[0] >> 3) & 0x3F);
   if((m_pdwCount[0] += ((DWORD) cb << 3)) < ((DWORD) cb << 3) ) m_pdwCount[1]++;
   m_pdwCount[1] += ((DWORD) cb >> 29);
   cbbf = (64 - dwbi);
   if(cb >= cbbf)
   {
      _bcopy(_mk_ptr_(LPBYTE,m_pBuffer,dwbi) , pInput, cbbf);
      transform(m_pBuffer);
      for(dwii = cbbf; (dwii + 63) < cb; dwii += 64) transform(_mk_ptr_(LPBYTE,pInput,dwii));
      dwbi = 0;
   }
   else{ dwii=0; }
   _bcopy(_mk_ptr_(LPBYTE,m_pBuffer,dwbi),_mk_ptr_(LPBYTE,pInput,dwii),cb-dwii);
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL ot4xb_md5_internal::Update(HANDLE hFile)
{
   BYTE  bf[1024];
   DWORD dw  = 0;
   if(!m_bOk ){return FALSE;}
   while( ReadFile(hFile,bf,1024,&dw,NULL) )
   {
      if(!dw) return TRUE;
      if( !Update(bf,dw) ){ m_bOk = FALSE; return FALSE; }
   }
   m_bOk = FALSE;
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL ot4xb_md5_internal::Finalize(void)
{
   BYTE  bits[8];
   DWORD dwi,cbpd;
   BYTE  pd[64];  _bset(pd,0,64); pd[0] = 0x80;
  
   if( m_bFinalized ){m_bOk = FALSE;}
   if(!m_bOk ){return FALSE;}
   _encode_(bits,m_pdwCount,8);
   dwi  = (DWORD) ((m_pdwCount[0] >> 3) & 0x3f);
   cbpd = ( (dwi < 56) ? (56 - dwi) : (120 - dwi) );
   Update(pd,cbpd);
   Update(bits,8);
   _encode_(m_pDigest,m_pdwState,16);
   _bset(m_pBuffer,0,64);
   m_bFinalized = TRUE;
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_md5_internal::transform(LPBYTE pbk)
{
   DWORD a = m_pdwState[0];
   DWORD b = m_pdwState[1];
   DWORD c = m_pdwState[2];
   DWORD d = m_pdwState[3];
   DWORD x[16];            
   
   _decode_(x,pbk,64);
   if( m_bFinalized ){m_bOk = FALSE;}
   if(!m_bOk ){return;}
   FF(a, b, c, d, x[ 0], S11, 0xd76aa478); // 01
   FF(d, a, b, c, x[ 1], S12, 0xe8c7b756); // 02
   FF(c, d, a, b, x[ 2], S13, 0x242070db); // 03
   FF(b, c, d, a, x[ 3], S14, 0xc1bdceee); // 04
   FF(a, b, c, d, x[ 4], S11, 0xf57c0faf); // 05
   FF(d, a, b, c, x[ 5], S12, 0x4787c62a); // 06
   FF(c, d, a, b, x[ 6], S13, 0xa8304613); // 07
   FF(b, c, d, a, x[ 7], S14, 0xfd469501); // 08
   FF(a, b, c, d, x[ 8], S11, 0x698098d8); // 09
   FF(d, a, b, c, x[ 9], S12, 0x8b44f7af); // 10
   FF(c, d, a, b, x[10], S13, 0xffff5bb1); // 11
   FF(b, c, d, a, x[11], S14, 0x895cd7be); // 12
   FF(a, b, c, d, x[12], S11, 0x6b901122); // 13
   FF(d, a, b, c, x[13], S12, 0xfd987193); // 14
   FF(c, d, a, b, x[14], S13, 0xa679438e); // 15
   FF(b, c, d, a, x[15], S14, 0x49b40821); // 16
   GG(a, b, c, d, x[ 1], S21, 0xf61e2562); // 17
   GG(d, a, b, c, x[ 6], S22, 0xc040b340); // 18
   GG(c, d, a, b, x[11], S23, 0x265e5a51); // 19
   GG(b, c, d, a, x[ 0], S24, 0xe9b6c7aa); // 20
   GG(a, b, c, d, x[ 5], S21, 0xd62f105d); // 21
   GG(d, a, b, c, x[10], S22,  0x2441453); // 22
   GG(c, d, a, b, x[15], S23, 0xd8a1e681); // 23
   GG(b, c, d, a, x[ 4], S24, 0xe7d3fbc8); // 24
   GG(a, b, c, d, x[ 9], S21, 0x21e1cde6); // 25
   GG(d, a, b, c, x[14], S22, 0xc33707d6); // 26
   GG(c, d, a, b, x[ 3], S23, 0xf4d50d87); // 27
   GG(b, c, d, a, x[ 8], S24, 0x455a14ed); // 28
   GG(a, b, c, d, x[13], S21, 0xa9e3e905); // 29
   GG(d, a, b, c, x[ 2], S22, 0xfcefa3f8); // 30
   GG(c, d, a, b, x[ 7], S23, 0x676f02d9); // 31
   GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); // 32
   HH(a, b, c, d, x[ 5], S31, 0xfffa3942); // 33
   HH(d, a, b, c, x[ 8], S32, 0x8771f681); // 34
   HH(c, d, a, b, x[11], S33, 0x6d9d6122); // 35
   HH(b, c, d, a, x[14], S34, 0xfde5380c); // 36
   HH(a, b, c, d, x[ 1], S31, 0xa4beea44); // 37
   HH(d, a, b, c, x[ 4], S32, 0x4bdecfa9); // 38
   HH(c, d, a, b, x[ 7], S33, 0xf6bb4b60); // 39
   HH(b, c, d, a, x[10], S34, 0xbebfbc70); // 40
   HH(a, b, c, d, x[13], S31, 0x289b7ec6); // 41
   HH(d, a, b, c, x[ 0], S32, 0xeaa127fa); // 42
   HH(c, d, a, b, x[ 3], S33, 0xd4ef3085); // 43
   HH(b, c, d, a, x[ 6], S34,  0x4881d05); // 44
   HH(a, b, c, d, x[ 9], S31, 0xd9d4d039); // 45
   HH(d, a, b, c, x[12], S32, 0xe6db99e5); // 46
   HH(c, d, a, b, x[15], S33, 0x1fa27cf8); // 47
   HH(b, c, d, a, x[ 2], S34, 0xc4ac5665); // 48
   II(a, b, c, d, x[ 0], S41, 0xf4292244); // 49
   II(d, a, b, c, x[ 7], S42, 0x432aff97); // 50
   II(c, d, a, b, x[14], S43, 0xab9423a7); // 51
   II(b, c, d, a, x[ 5], S44, 0xfc93a039); // 52
   II(a, b, c, d, x[12], S41, 0x655b59c3); // 53
   II(d, a, b, c, x[ 3], S42, 0x8f0ccc92); // 54
   II(c, d, a, b, x[10], S43, 0xffeff47d); // 55
   II(b, c, d, a, x[ 1], S44, 0x85845dd1); // 56
   II(a, b, c, d, x[ 8], S41, 0x6fa87e4f); // 57
   II(d, a, b, c, x[15], S42, 0xfe2ce6e0); // 58
   II(c, d, a, b, x[ 6], S43, 0xa3014314); // 59
   II(b, c, d, a, x[13], S44, 0x4e0811a1); // 60
   II(a, b, c, d, x[ 4], S41, 0xf7537e82); // 61
   II(d, a, b, c, x[11], S42, 0xbd3af235); // 62
   II(c, d, a, b, x[ 2], S43, 0x2ad7d2bb); // 63
   II(b, c, d, a, x[ 9], S44, 0xeb86d391); // 64
   m_pdwState[0] += a; m_pdwState[1] += b; m_pdwState[2] += c; m_pdwState[3] += d;
   _bset((LPBYTE)(void*)x,0, 16 * sizeof(DWORD) );
}
// -----------------------------------------------------------------------------------------------------------------
LPBYTE ot4xb_md5_internal::raw_digest(void)
{
   if( !(m_bFinalized && m_bOk ) ){return 0;}
   return _bdup(m_pDigest,16);
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR ot4xb_md5_internal::hex_digest()
{  
   LPSTR p;
   DWORD dw;
   if( !(m_bFinalized && m_bOk ) ){return 0;}
   p = (LPSTR) _xgrab(33);
   for(dw=0; dw<16;dw++) wsprintf(_mk_ptr_(LPSTR,p,dw*2),"%02x",m_pDigest[dw]);
   return p;
}
// -----------------------------------------------------------------------------------------------------------------






