//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class ot4xb_md5_internal : public T_ot4xb_base
{
   public:
   // ---------------------------------------------------------------------------------
   DWORD m_pdwState[4];
   DWORD m_pdwCount[2];
   BYTE  m_pBuffer[64];
   BYTE  m_pDigest[16];
   BOOL  m_bFinalized;
   BOOL  m_bOk;
   // ---------------------------------------------------------------------------------
   ot4xb_md5_internal(void);
   ot4xb_md5_internal(LPBYTE pStr,UINT cb);
   ot4xb_md5_internal(HANDLE hFile);
   // ---------------------------------------------------------------------------------
   BOOL  Update(LPBYTE pInput,UINT cb);
   BOOL  Update(HANDLE hFile);
   BOOL  Finalize(void);
   // ---------------------------------------------------------------------------------
   LPBYTE raw_digest(void);  // digest as a 16-byte binary array
   LPSTR  hex_digest();      // digest as a 33-byte ascii-hex string
   // ---------------------------------------------------------------------------------
   void init(void);
   void transform(LPBYTE pBuffer);
   // ---------------------------------------------------------------------------------
};
