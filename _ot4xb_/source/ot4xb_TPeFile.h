/*
//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#ifndef _API_cpp_APIcpp_TPeFile_h_
#define _API_cpp_APIcpp_TPeFile_h_
#ifdef __cplusplus
#pragma pack(push , 4)             
// -----------------------------------------------------------------------------------------------------------------
typedef BOOL (* SECTIONENUMPROC)( LPSTR, IMAGE_SECTION_HEADER *, LPARAM );
typedef BOOL (* DLLENUMPROC    )( LPSTR, IMAGE_IMPORT_DESCRIPTOR *, LPARAM );
typedef BOOL (* IMPORTENUMPROC )( LPSTR, DWORD, IMAGE_THUNK_DATA *, LPARAM );
typedef BOOL (* EXPORTENUMPROC )( LPSTR, WORD, DWORD , LPARAM );
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API TPeFile : public T_ot4xb_base
{
   public:
	   void*  m_pBase;
	   HANDLE m_hFile;
	   HANDLE m_hMap;
	   DWORD  m_dwLastError;
	   LPSTR  m_pFileName;
	   DWORD  m_dwDummy; // 8 byte align
      // ---------------------------------------------------------------------------------
      TPeFile::TPeFile();
      TPeFile::~TPeFile();
      BOOL                    Open( LPSTR pFName);
      BOOL                    OpenImage( HMODULE hModule);
      void                    Close(void);
      BOOL                    MapFile(void);
      BOOL                    CloseImage(void);
      BOOL                    UnmapFileAndHold(void);
      IMAGE_DOS_HEADER *      GetDOSHeader(void);
      IMAGE_NT_HEADERS *      GetNTHeaders(void);
      IMAGE_OPTIONAL_HEADER * GetOptionalHeader(void);
      IMAGE_FILE_HEADER *     GetFileHeader(void);
      IMAGE_SECTION_HEADER *  GetSectionHeaders(void);
      void                    EnumSections( SECTIONENUMPROC fp, LPARAM lp );
      IMAGE_SECTION_HEADER *  FindSection( LPSTR id , BOOL bStr );
      IMAGE_DATA_DIRECTORY *  GetDataDirectory( DWORD dwIndex );
      DWORD                   RvaToVa( DWORD rva );
      void                    EnumImportDLLs( DLLENUMPROC fp, LPARAM lp );
      void                    EnumImports( LPSTR pDllName, IMPORTENUMPROC fp , LPARAM lp );
      void                    EnumExports( EXPORTENUMPROC fp, LPARAM lp );
};
// -----------------------------------------------------------------------------------------------------------------
#pragma pack(pop)
#endif // __cplusplus
#endif
// -----------------------------------------------------------------------------------------------------------------
*/