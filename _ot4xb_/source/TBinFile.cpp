//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
#define PXERROR( n , m , d )  px->GenError();px->SetErrorSubSystem("ot4xb"); \
                              px->SetErrorOperation("TBinFile::"  ##m  "()"); \
                              px->SetErrorDescription( d ); \
                              px->SetErrorGenCode(0x00105000 + n);
//----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
static void TBinFile_GetAccessAndShare( TXbClsParams * px , ULONG npa,DWORD * pdwa , ULONG nps,DWORD * pdws );
static void TBinFile_GetSecurityAttrib( TXbClsParams * px , ULONG np, SECURITY_ATTRIBUTES* psl,SECURITY_ATTRIBUTES** ppsa);
//-----------------------------------------------------------------------------------------------------------------------
static void TBinFile_init( TXbClsParams * px );    // 1 // ::New([hFile]) -> Self
static void TBinFile_Release( TXbClsParams * px ); // 0 // ::Release() -> Self
static void TBinFile_Close( TXbClsParams * px );   // 0 // ::Close() -> Self
static void TBinFile_Open( TXbClsParams * px );    // 3 //  ::Open(cFName,[cAccess],[cShare]) -> lOk
static void TBinFile_hFile( TXbClsParams * px );   // 0 //  ? ::hFile -> nHandle | NIL
static void TBinFile_Create( TXbClsParams * px );  // 7 //
      // ::Create(1 cFName,2[cAccess],3[cShare], 4[pSecurity|lInherit],5[dwFunc],6[dwAttrib],7[hTemplate]) -> lOk
static void TBinFile_Read( TXbClsParams * px );
static void TBinFile_Write( TXbClsParams * px );
static void TBinFile_GoTo( TXbClsParams * px );
static void TBinFile_GetPos( TXbClsParams * px );
static void TBinFile_SetEof( TXbClsParams * px );
static void TBinFile_Commit( TXbClsParams * px );
static void TBinFile_ReadLine( TXbClsParams * px ); // ReadLine( @lEof,@lEol ) -> cLine
static void TBinFile_ReadMimeHeader(TXbClsParams * px); // ReadMimeHeader( @lEof,@lEoh ) -> cLine
static void TBinFile_ResetBuffer( TXbClsParams * px ); // ResetBuffer( [nSize] )
static void TBinFile_LoadBuffer( TXbClsParams * px ); // LoadBuffer(@lEof,lSkip = .T.) -> nBytes
static void TBinFile_PeekBytesFromBuffer( TXbClsParams * px ); // PeekBytesFromBuffer(nBytes= 0) -> cString
//----------------------------------------------------------------------------------------------------------------------
static int split_stg_path( LPSTR pPath , TList* pList)
{
   if( !( pPath && pList ) )
   {
      return -1;
   }
   BOOL bBadChars = FALSE;
   DWORD nMaxComponent = 0;   
   DWORD cb = 0;
   char  ch = 0;
   while( pPath[cb] )
   {
      if( pPath[cb] == '\\')
      {
         nMaxComponent++;
         if( ch == '\\' )
         {
            bBadChars = TRUE;         
         }
      }
      if( ((BYTE) pPath[cb]) < 0x1F )
      {
         bBadChars = TRUE;
      }
      ch = pPath[cb]; 
      cb++;
   }
   if( ! cb ){ return -1; }
   if( bBadChars ){ return -1; }   
   if( nMaxComponent == 0 )
   {
      pList->Add( ansi2w(pPath,(int) cb) );
      return 1;
   }
   if( pPath[0] == '\\' ){pPath++; cb--;}
   if( ! cb ){ return -1; }
   BOOL  bIsStream = (BOOL) ( pPath[(cb-1)] == '\\' ? 0 : 1 );
   if(!bIsStream){pPath++; cb--; }
   if( ! cb ){ return -1; }   
   LPSTR p = pPath;
   DWORD n;
   int nn = 0;
   for(n=0;n < cb;n++,nn++)
   {
      if( pPath[n] == '\\')
      {
         pList->Add( (void*) ansi2w(p,nn) );
         nn = -1;
         p = _mk_ptr_(LPSTR,pPath,n+1);
      }
   }   
   pList->Add( (void*) ansi2w(p,(int)nn) );   
   return (int) ( bIsStream ? 1 : 0 );
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( LMEMOSTGWRITE ) // lMemoStgWrite( cStgFile , cName , cBuffer , lAppend := .F.) -> lOk
{
   TXppParamList xpp(pl,4);
   xpp[0]->PutBool( FALSE );   
   if( !( xpp[1]->CheckType( XPP_CHARACTER ) && xpp[2]->CheckType( XPP_CHARACTER) ) )
   {
      return;
   }
   LPWSTR stg_filename = xpp[1]->StrDupW();
   if( stg_filename )
   {
      IStorage* stg = 0;   
      HRESULT result = StgIsStorageFile( stg_filename );
      
      if( result == S_OK )
      {
         StgOpenStorageEx(stg_filename, STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,STGFMT_ANY ,0,0,0,IID_IStorage,(void**) &stg);      
      }
      else if( result == STG_E_FILENOTFOUND  )
      {
         StgCreateStorageEx(stg_filename, STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,STGFMT_STORAGE,0,0,0,IID_IStorage,(void**) &stg);
      }
      _xfree( (void*) stg_filename ); stg_filename = 0;
      if( stg )
      {
         TList name_list;
         TList storage_list;         
         LPWSTR pwStreamName = 0;
         int nListType = split_stg_path( xpp[2]->LockStr(), &name_list );
         if( nListType < 0 )
         {
            goto label_release_file_stg;
         }
         DWORD n,nn;
         pwStreamName = (LPWSTR) ( nListType == 0  ? 0 : name_list.Pop() );
                  
         for( n=0,nn = name_list.Count() ; n < nn && stg ; n++ )
         {
            IStorage* parent = stg;
            stg = 0;
            storage_list.Add( (void*) parent );
            LPWSTR pw = (LPWSTR) name_list.Get(n);
            if( pw )
            {
               if( FAILED( parent->OpenStorage( pw,0,STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,0,0,&stg ) ) )
               {
                  stg = 0;
                  if( FAILED( parent->CreateStorage(pw,STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_FAILIFTHERE,0,0,&stg) ) )
                  {
                     stg = 0;
                     goto label_release_file_stg;
                  }
               }
            }
         }
         if( !pwStreamName )
         {
            xpp[0]->PutBool(TRUE);            
            goto label_release_file_stg;         
         }
         if( stg ) // probably always TRUE at this point of the code but ...
         {
            if( xpp[3]->CheckType(XPP_NUMERIC) && (xpp[3]->GetLong() == -1) )
            {
               if ( SUCCEEDED( stg->DestroyElement(pwStreamName) ) )
               {
                  xpp[0]->PutBool(TRUE);
               }
               goto label_release_file_stg;
            }
            IStream* ps = 0;
            if( FAILED( stg->OpenStream(pwStreamName,0,STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,0,&ps) ) )
            {
               ps = 0;
               if( FAILED( stg->CreateStream(pwStreamName,STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,0,0,&ps)))
               {
                  ps = 0;
               }
            }
            if( !ps )
            {
               goto label_release_file_stg;
            }
            if( xpp[4]->GetBool() )
            {
               LARGE_INTEGER liMove; liMove.QuadPart = 0LL;
               ps->Seek(liMove,STREAM_SEEK_END,0);
            }
            else
            {
               ULARGE_INTEGER liSize; liSize.QuadPart = 0LL;
               ps->SetSize(liSize);
            }
            DWORD cb = 0;
            void* pBytes = (void*) xpp[3]->LockStr(&cb);
            if( SUCCEEDED( ps->Write(pBytes,cb,0) ) )
            {
               xpp[0]->PutBool(TRUE);
            }
            xpp[3]->UnlockStr();
            ps->Release();
         }
         
         label_release_file_stg: ;
         if( pwStreamName )
         {
            _xfree( (void*) pwStreamName );
         }
         while( name_list.Count() )
         {
            LPWSTR pw = (LPWSTR) name_list.Pop();
            if( pw )
            {
               _xfree( (void*) pw);
            }
         }
         if( stg )
         {
            stg->Release();
            stg = 0;
         }
         while( storage_list.Count() )
         {
            stg = (IStorage*) storage_list.Pop();
            if( stg ){ stg->Release(); }
            stg = 0;
         }
      }
   }   
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( CMEMOSTGREAD ) // cMemoStgRead( cStgFile , cName , nStart = 0 , nBytes = -1) -> cBuffer
{
   TXppParamList xpp(pl,4);
   if( !( xpp[1]->CheckType( XPP_CHARACTER ) && xpp[2]->CheckType( XPP_CHARACTER) ) )
   {
      return;
   }
   LPWSTR stg_filename = xpp[1]->StrDupW();
   if( stg_filename )
   {
      IStorage* stg = 0;   
      HRESULT result = StgIsStorageFile( stg_filename );
      
      if( result == S_OK )
      {
         StgOpenStorageEx(stg_filename, STGM_DIRECT|STGM_READ|STGM_SHARE_EXCLUSIVE,STGFMT_ANY ,0,0,0,IID_IStorage,(void**) &stg);      
      }
      _xfree( (void*) stg_filename ); stg_filename = 0;
      if( stg )
      {
         TList name_list;
         TList storage_list;         
         LPWSTR pwStreamName = 0;
         int nListType = split_stg_path( xpp[2]->LockStr(), &name_list );
         if( nListType != 1 )
         {
            goto label_release_file_stg;
         }
         DWORD n,nn;
         pwStreamName = (LPWSTR) ( nListType == 0  ? 0 : name_list.Pop() );
         if( !pwStreamName )
         {
            goto label_release_file_stg;         
         }         
                  
         for( n=0,nn = name_list.Count() ; n < nn && stg ; n++ )
         {
            IStorage* parent = stg;
            stg = 0;
            storage_list.Add( (void*) parent );
            LPWSTR pw = (LPWSTR) name_list.Get(n);
            if( pw )
            {
               if( FAILED( parent->OpenStorage( pw,0,STGM_DIRECT|STGM_READ|STGM_SHARE_EXCLUSIVE,0,0,&stg ) ) )
               {
                  stg = 0;
                  goto label_release_file_stg;
               }
            }
         }
         if( stg ) // probably always TRUE at this point of the code but ...
         {
            void* buffer = 0;         
            IStream* ps = 0;
            if( FAILED( stg->OpenStream(pwStreamName,0,STGM_DIRECT|STGM_READ|STGM_SHARE_EXCLUSIVE,0,&ps) ) )
            {
               ps = 0;
            }
            if( !ps )
            {
               goto label_release_file_stg;
            }
            
            LARGE_INTEGER liMove; liMove.QuadPart = 0LL;                        
            LONGLONG llStart    = xpp[3]->GetQWord();
            LONGLONG llMaxRead  = ( xpp[4]->CheckType(XPP_NUMERIC) ? xpp[4]->GetQWord() : -1LL );
            ULARGE_INTEGER liSize; liSize.QuadPart = 0LL;            
            LARGE_INTEGER li; li.QuadPart = 0LL;                        
            ps->Seek(liMove,STREAM_SEEK_END,&liSize);
            li.HighPart = (LONG) liSize.HighPart;
            li.LowPart  = liSize.LowPart;
            if( llMaxRead < 0 )
            {
               llMaxRead = li.QuadPart;
            }
            if( llStart >= 0 )
            {
               if (llMaxRead > (li.QuadPart - llStart))
               {
                  llMaxRead = (li.QuadPart - llStart);
               }
               if ((llMaxRead > 0x20000000LL) || (llMaxRead < 0))
               {
                  // > 512 MB
               }
               else
               {
                  liMove.QuadPart = llStart;
                  li.QuadPart = llMaxRead;
                  ps->Seek(liMove, STREAM_SEEK_SET, 0);

                  DWORD dwRead = li.LowPart;
                  if (dwRead == 0)
                  {
                     xpp[0]->PutStr("");
                  }
                  else
                  {

                     try
                     {
                        buffer = _xgrab(dwRead);
                     }
                     catch (...)
                     {
                        ; //buffer = 0;
                     }
                     if (buffer)
                     {

                        DWORD dw = 0;
                        if (SUCCEEDED(ps->Read(buffer, dwRead, &dw)))
                        {
                           xpp[0]->PutStrLen((LPSTR)buffer, dw);
                        }
                     }
                  }
               }
            }

            if( buffer )
            {
               _xfree( buffer);
               buffer = 0;
            }        
            ps->Release();
         }
         
         label_release_file_stg: ;
         if( pwStreamName )
         {
            _xfree( (void*) pwStreamName );
         }
         while( name_list.Count() )
         {
            LPWSTR pw = (LPWSTR) name_list.Pop();
            if( pw )
            {
               _xfree( (void*) pw);
            }
         }
         if( stg )
         {
            stg->Release();
            stg = 0;
         }
         while( storage_list.Count() )
         {
            stg = (IStorage*) storage_list.Pop();
            if( stg ){ stg->Release(); }
            stg = 0;
         }
      }
   }   
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( LMEMOSTGIMPORT ) // lMemoStgImport( cStgFile , cName , cInputFile,lAppend) -> lOk
{
   TXppParamList xpp(pl,4);
   xpp[0]->PutBool( FALSE );   
   if( !( xpp[1]->CheckType( XPP_CHARACTER ) && xpp[2]->CheckType( XPP_CHARACTER) && xpp[3]->CheckType(XPP_CHARACTER | XPP_NUMERIC)) )
   {
      return;
   }
   LPWSTR stg_filename = xpp[1]->StrDupW();
   if( stg_filename )
   {
      IStorage* stg = 0;   
      HRESULT result = StgIsStorageFile( stg_filename );
      
      if( result == S_OK )
      {
         StgOpenStorageEx(stg_filename, STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,STGFMT_ANY ,0,0,0,IID_IStorage,(void**) &stg);      
      }
      else if( result == STG_E_FILENOTFOUND  )
      {
         StgCreateStorageEx(stg_filename, STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,STGFMT_STORAGE,0,0,0,IID_IStorage,(void**) &stg);
      }
      _xfree( (void*) stg_filename ); stg_filename = 0;
      if( stg )
      {
         TList name_list;
         TList storage_list;         
         LPWSTR pwStreamName = 0;
         int nListType = split_stg_path( xpp[2]->LockStr(), &name_list );
         if( nListType < 0 )
         {
            goto label_release_file_stg;
         }
         DWORD n,nn;
         pwStreamName = (LPWSTR) ( nListType == 0  ? 0 : name_list.Pop() );
                  
         for( n=0,nn = name_list.Count() ; n < nn && stg ; n++ )
         {
            IStorage* parent = stg;
            stg = 0;
            storage_list.Add( (void*) parent );
            LPWSTR pw = (LPWSTR) name_list.Get(n);
            if( pw )
            {
               if( FAILED( parent->OpenStorage( pw,0,STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,0,0,&stg ) ) )
               {
                  stg = 0;
                  if( FAILED( parent->CreateStorage(pw,STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_FAILIFTHERE,0,0,&stg) ) )
                  {
                     stg = 0;
                     goto label_release_file_stg;
                  }
               }
            }
         }
         if( !pwStreamName )
         {
            xpp[0]->PutBool(TRUE);            
            goto label_release_file_stg;         
         }
         if( stg ) // probably always TRUE at this point of the code but ...
         {
            IStream* ps = 0;
            if( FAILED( stg->OpenStream(pwStreamName,0,STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,0,&ps) ) )
            {
               ps = 0;
               if( FAILED( stg->CreateStream(pwStreamName,STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,0,0,&ps)))
               {
                  ps = 0;
               }
            }
            if( !ps )
            {
               goto label_release_file_stg;
            }
            if( xpp[4]->GetBool() )
            {
               LARGE_INTEGER liMove; liMove.QuadPart = 0LL;
               ps->Seek(liMove,STREAM_SEEK_END,0);
            }
            else
            {
               ULARGE_INTEGER liSize; liSize.QuadPart = 0LL;
               ps->SetSize(liSize);
            }
            
            TBinFile file;
            
            if( xpp[3]->CheckType(XPP_NUMERIC) )
            {
               file.InitFromHandle( (HANDLE) xpp[3]->GetDWord() );
            }
            else if( xpp[3]->CheckType(XPP_CHARACTER) )
            {
               file.Open( xpp[3]->LockStr(),GENERIC_READ);
               xpp[3]->UnlockStr();               
            }
            if( file.IsValidHandle() )
            {
               file.ResetBuffer( 0x100000 );
               BOOL bEof = FALSE;
               BOOL bOk = TRUE;
               do
               {
                  if( file.LoadBuffer(&bEof) )
                  {
                     if( FAILED( ps->Write( file.m_pBuffer , file.m_dwBuffLen,0) ) )
                     {
                        bOk = FALSE;
                     }
                  }
               } while( bOk && (!bEof) );
               file.Close();
               xpp[0]->PutBool(bOk);
            }
            ps->Release();
         }
         
         label_release_file_stg: ;
         if( pwStreamName )
         {
            _xfree( (void*) pwStreamName );
         }
         while( name_list.Count() )
         {
            LPWSTR pw = (LPWSTR) name_list.Pop();
            if( pw )
            {
               _xfree( (void*) pw);
            }
         }
         if( stg )
         {
            stg->Release();
            stg = 0;
         }
         while( storage_list.Count() )
         {
            stg = (IStorage*) storage_list.Pop();
            if( stg ){ stg->Release(); }
            stg = 0;
         }
      }
   }   
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( LMEMOSTGEXPORT ) // lMemoStgExport( cStgFile , cName , cOutputFile) -> lOk
{
   TXppParamList xpp(pl,4);
   if( !( xpp[1]->CheckType( XPP_CHARACTER ) && xpp[2]->CheckType( XPP_CHARACTER) && xpp[3]->CheckType( XPP_CHARACTER) ))
   {
      return;
   }
   LPWSTR stg_filename = xpp[1]->StrDupW();
   if( stg_filename )
   {
      IStorage* stg = 0;   
      HRESULT result = StgIsStorageFile( stg_filename );
      
      if( result == S_OK )
      {
         StgOpenStorageEx(stg_filename, STGM_DIRECT|STGM_READ|STGM_SHARE_EXCLUSIVE,STGFMT_ANY ,0,0,0,IID_IStorage,(void**) &stg);      
      }
      _xfree( (void*) stg_filename ); stg_filename = 0;
      if( stg )
      {
         TList name_list;
         TList storage_list;         
         LPWSTR pwStreamName = 0;
         int nListType = split_stg_path( xpp[2]->LockStr(), &name_list );
         if( nListType != 1 )
         {
            goto label_release_file_stg;
         }
         DWORD n,nn;
         pwStreamName = (LPWSTR) ( nListType == 0  ? 0 : name_list.Pop() );
         if( !pwStreamName )
         {
            goto label_release_file_stg;         
         }         
                  
         for( n=0,nn = name_list.Count() ; n < nn && stg ; n++ )
         {
            IStorage* parent = stg;
            stg = 0;
            storage_list.Add( (void*) parent );
            LPWSTR pw = (LPWSTR) name_list.Get(n);
            if( pw )
            {
               if( FAILED( parent->OpenStorage( pw,0,STGM_DIRECT|STGM_READ|STGM_SHARE_EXCLUSIVE,0,0,&stg ) ) )
               {
                  stg = 0;
                  goto label_release_file_stg;
               }
            }
         }
         if( stg ) // probably always TRUE at this point of the code but ...
         {
            void* buffer = 0;         
            IStream* ps = 0;
            if( FAILED( stg->OpenStream(pwStreamName,0,STGM_DIRECT|STGM_READ|STGM_SHARE_EXCLUSIVE,0,&ps) ) )
            {
               ps = 0;
            }
            if( !ps )
            {
               goto label_release_file_stg;
            }
            
            TBinFile file;
            file.Create(xpp[3]->LockStr(),GENERIC_WRITE,0,0,CREATE_ALWAYS);
            xpp[3]->UnlockStr();               
            if( file.IsValidHandle() )
            {
               file.ResetBuffer( 0x100000 );
               BOOL bEof = FALSE;
               BOOL bOk = TRUE;
               do
               {
                  if( ps->Read(file.m_pBuffer,file.m_dwBuffSize,&file.m_dwBuffLen) == 0 )
                  {
                     bOk = file.SaveBuffer();
                     bEof = (file.m_dwBuffLen < file.m_dwBuffSize);
                  }
                  else
                  {
                     bOk = FALSE;
                  }
               } while( bOk && (!bEof) );
               file.Close();
               xpp[0]->PutBool(bOk);
            }            
            if( buffer )
            {
               _xfree( buffer);
               buffer = 0;
            }        
            ps->Release();
         }
         
         label_release_file_stg: ;
         if( pwStreamName )
         {
            _xfree( (void*) pwStreamName );
         }
         while( name_list.Count() )
         {
            LPWSTR pw = (LPWSTR) name_list.Pop();
            if( pw )
            {
               _xfree( (void*) pw);
            }
         }
         if( stg )
         {
            stg->Release();
            stg = 0;
         }
         while( storage_list.Count() )
         {
            stg = (IStorage*) storage_list.Pop();
            if( stg ){ stg->Release(); }
            stg = 0;
         }
      }
   }   
}
// -----------------------------------------------------------------------------------------------------------------
static ContainerHandle memostg_enum( IStorage* stg  )
{
   ContainerHandle conr = NULLCONTAINER;
   IEnumSTATSTG* e = 0;
   if( SUCCEEDED( stg->EnumElements(0,0,0,&e) ) )
   {
      TList list;
      STATSTG item;
      while( e->Next(1,&item,0) == S_OK )
      {
         if(  (item.type == STGTY_STREAM) || (item.type == STGTY_STORAGE) )  
         {
            ContainerHandle cona = _conNewArray(1,4,0);
            LPSTR pn     = w2ansi((LPWSTR)item.pwcsName);
            _conArrayPutC(cona,pn,1,0);
            _conArrayPutNL(cona,(LONG) item.type, 2,0 );
            _xfree(pn);         
            list.Add( (void*) cona );                  
            switch( item.type )
            {
               case STGTY_STREAM:
               {
                  if( item.cbSize.HighPart | item.cbSize.LowPart  )
                  {
                     double nd = (double) ((DWORD) item.cbSize.HighPart );
                     nd  = (nd *  4294967296.00 ) + ((double) item.cbSize.LowPart);
                     _conArrayPutND(cona,nd,3,0);                     
                  }
                  else
                  {
                     _conArrayPutNL(cona,(LONG) item.cbSize.LowPart,3,0);
                  }
                  break;
               }
               case STGTY_STORAGE:
               {
                  IStorage* child = 0;            
                  if( SUCCEEDED( stg->OpenStorage(item.pwcsName ,0, STGM_READ|STGM_SHARE_EXCLUSIVE,0,0,&child) ) )
                  {
                     ContainerHandle con = memostg_enum(child);
                     if( con )
                     {
                        _conArrayPut( cona,con,4,0);
                        _conRelease(con);
                     }
                     child->Release();
                  }
                  break;            
               }
            }
         }
         CoTaskMemFree( item.pwcsName );
      }
      DWORD n;
      DWORD nn = list.Count();
      conr = _conNewArray(1, nn );
      for( n=0; n < nn; n++ )
      {
         ContainerHandle con = (ContainerHandle) list.Replace(n,0);
         if( con )
         {
            _conArrayPut(conr,con,n+1,0);
            _conRelease(con);
         }
      }      
      e->Release();
   } 
   return conr;
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( CMEMOSTGLIST   ) // cMemoStgList( cStgFile ) ->  { { name , type, size, subitems| NIL },... }
{
   TXppParamList xpp(pl,1);
   LPWSTR stg_filename = xpp[1]->StrDupW();
   if( stg_filename )
   {
      if( StgIsStorageFile( stg_filename ) == S_OK)
      {
         IStorage* stg = 0;
         HRESULT result = StgOpenStorageEx(stg_filename, STGM_DIRECT|STGM_READ|STGM_SHARE_EXCLUSIVE , STGFMT_ANY ,0,0,0,IID_IStorage,(void**) &stg);
         
         if( SUCCEEDED( result ) )
         {
            ContainerHandle con = memostg_enum(stg);
            if( con )
            {
               xpp[0]->Put(con);
               _conRelease(con);
            }
            stg->Release();
         }
      }
      _xfree( (void*) stg_filename );
   }
   
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CMEMOREADEX(XppParamList pl) // cMemoReadEx( cFile,dwOffset = 0, DWORD dwMaxBytes = -1,nFlags)
{
   TXppParamList xpp(pl,4);
   LPSTR  pFileName  = xpp[1]->LockStr();
   DWORD  dwFlags    = xpp[4]->GetDWord();
   if( pFileName )
   {
      DWORD  dwOffset   = ( xpp[2]->CheckType(XPP_NUMERIC) ? xpp[2]->GetDWord() : 0 );   
      DWORD  dwMaxBytes = ( xpp[3]->CheckType(XPP_NUMERIC) ? xpp[3]->GetDWord() : ((DWORD) -1) );      
      DWORD  dwRead     = 0;
      LPBYTE pBuffer    = pMemoReadEx2(pFileName,&dwRead,0,dwOffset,dwMaxBytes,dwFlags);
      if( pBuffer && dwRead)
      {
         if( dwFlags & 0x8000 ) // email header // stop at the first CRLF + CRLF
         {
            DWORD n;
            for( n=0; n < dwRead;n++ )
            {
               
               switch( pBuffer[n] )
               {
                  case 0x0D:
                  {
                     if( ( (dwRead-n) > 3 ) ?  _mk_ptr_(LPDWORD,pBuffer,n)[0] == 0x0A0D0A0D : 0)
                     {
                        dwRead = n; 
                     }
                     break;
                  }
                  case 0x0A:
                  {                  
                     if( ( (dwRead-n) > 1 ) ?  _mk_ptr_(LPWORD,pBuffer,n)[0] == 0x0A0A : 0)
                     {
                        dwRead = n;
                     }
                     break;                  
                  }
               }
            }
         }
         xpp[0]->PutStrLen((LPSTR) pBuffer, dwRead );
			xpp[2]->PutDWord( dwOffset + dwRead );
      }
      else
      {
         if( dwFlags != (DWORD) INVALID_HANDLE_VALUE )
         {
            xpp[0]->PutStr("");
         }
      }
      if( pBuffer)
      {
         _xfree( (void*) pBuffer );
         pBuffer = 0;
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LMEMOWRITE(XppParamList pl) // lMemoWrite( cFile , cBuffer , lAppend := .F. ) -> lOk
{
   BOOL bResult                 = FALSE;
   BOOL bAppend                 = _parl(pl,3);
   BOOL bFileNameByRef          = FALSE;
   ContainerHandle concFileName = _conTParam(pl,1,&bFileNameByRef, XPP_CHARACTER );
   if( concFileName )
   {
      LPSTR pFileName    = (LPSTR) NULL;
      ULONG cbFileName   = 0;
      if( ot4xb_conRLockC( concFileName ,&pFileName , &cbFileName ) == 0 )
      {
         BOOL bBufferByRef = FALSE;
         ContainerHandle concBuffer = _conTParam(pl,2,&bBufferByRef , XPP_CHARACTER );
         if( concBuffer )
         {
            LPSTR pBuffer      = (LPSTR) NULL;
            ULONG cbBuffer     = 0;
            if( ot4xb_conRLockC( concBuffer ,&pBuffer , &cbBuffer ) == 0 )
            {
               HANDLE hFile = CreateFile( pFileName ,  GENERIC_WRITE | GENERIC_READ , 0 , NULL,
                                          ( bAppend ? OPEN_ALWAYS : CREATE_ALWAYS ),
                                          FILE_ATTRIBUTE_NORMAL , NULL );
               if( hFile != INVALID_HANDLE_VALUE )
               {
                  DWORD dw = 0;
                  if( bAppend ) SetFilePointer( hFile , 0 , NULL , FILE_END);
                  bResult = WriteFile(hFile, pBuffer , cbBuffer , &dw , NULL);
                  CloseHandle( hFile );
               }
               ot4xb_conUnlockC( concBuffer );
            }
            if( !bBufferByRef ) _conRelease(concBuffer);
         }
         ot4xb_conUnlockC( concFileName );
      }
      if( !bFileNameByRef ) _conRelease(concFileName);
   }
   _retl(pl,bResult);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY TBINFILE(XppParamList pl)
{
   ContainerHandle conco = _conClsObj("TBinFile");
   // ---------------------------------------------------------------------------------
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName( "TBinFile" );
      pc->EXPORTED();
      pc->AddGwstStyleMembers();
      // ---------------------------------------------------------------------------------
      pc->ROProperty("hFile" , TBinFile_hFile);// ::hFile -> nHandle | NIL
      // ---------------------------------------------------------------------------------
      pc->Method( "init"         , TBinFile_init     , 1); // ::New([hFile]) -> Self
      pc->Method( "Release"      , TBinFile_Release     ); // ::Release() -> Self
      pc->Method( "Close"        , TBinFile_Close       ); // ::Close() -> Self
      pc->Method( "Open"         , TBinFile_Open     , 4); // ::Open(cFName,[cAccess],[cShare],[lOpenAlways]) -> lOk
      pc->Method( "Create"       , TBinFile_Create   , 7);
      // ::Create(1 cFName,2[cAccess],3[cShare], 4[pSecurity|lInherit],5[dwFunc],6[dwAttrib],7[hTemplate]) -> lOk
      pc->Method( "Read"         , TBinFile_Read     , 3); // ::Read( @ptEx,[nBytes] )->nBytes | NIL
      pc->Method( "Write"        , TBinFile_Write    , 2); // ::Write( @ptEx,[nBytes] )->nBytes | NIL
      pc->Method( "GetPos"       , TBinFile_GetPos   , 1 ); // ::GetPos(@uPos) -> uUpdatedPos
      pc->Method( "GoTo"         , TBinFile_GoTo     , 2 ); // ::GoTo(nSkip,nFrom)
      pc->MethodCB("GoBof"       , "{|s,nn| s:GoTo( nn , 0) }"); // #define FILE_BEGIN           0
      pc->MethodCB("SkipBytes"   , "{|s,nn| s:GoTo( nn , 1) }"); // #define FILE_CURRENT         1
      pc->MethodCB("GoEof"       , "{|s,nn| s:GoTo( nn , 2) }"); // #define FILE_END             2
      pc->Method("SetEof"        , TBinFile_SetEof );
      pc->Method("Commit"        , TBinFile_Commit );
      pc->Method("ReadLine"      , TBinFile_ReadLine , 2); // ReadLine( @lEof,@lEol ) -> cLine
	  pc->Method("ReadMimeHeader", TBinFile_ReadMimeHeader, 2); // ReadMimeHeader( @lEof,@lEoh ) -> cMimeHeader
      pc->Method("ResetBuffer"   , TBinFile_ResetBuffer , 1); // ResetBuffer( [nSize] )
      pc->Method("LoadBuffer"    , TBinFile_LoadBuffer  , 2); // LoadBuffer(@lEof,lSkip = .T.) -> nBytes
      pc->Method("PeekBytesFromBuffer", TBinFile_PeekBytesFromBuffer, 2); // PeekBytesFromBuffer(nRelOffset = 0, nBytes= 0) -> cString
      // ---------------------------------------------------------------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER )
      {
         if(pl){ _ret(pl); }
         return;
      }
   }
   // ---------------------------------------------------------------------------------
   if(pl) _conReturn(pl,conco);
   _conRelease(conco);
}
//-----------------------------------------------------------------------------------------------------------------------
static void TBinFile_init( TXbClsParams * px ) // 1 // ::New([hFile]) -> Self
{
   TBinFile_Release( px );
   if( px->CheckParamType(1,XPP_NUMERIC ) )
   {
      HANDLE hFile   =   (HANDLE) px->GetParamLong(1);
      if( hFile != INVALID_HANDLE_VALUE )
      {
         TBinFile * psc = new TBinFile;
         psc->InitFromHandle( hFile );
         px->SetSelfC((void*) psc );
      }
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TBinFile_Release( TXbClsParams * px ) // 0 // ::Release() -> Self
{
   TBinFile * psc     = (TBinFile*) px->GetSelfC();
   px->PutReturnSelf();
   if( psc )
   {
      delete psc; psc = NULL; px->SetSelfC(0);
   } // clean existing link
}
//-----------------------------------------------------------------------------------------------------------------------
static void TBinFile_Close( TXbClsParams * px )   // 0 // ::Close() -> Self
{
   TBinFile * psc     = (TBinFile*) px->GetSelfC();
   px->PutReturnSelf();
   if( psc )
   {
      psc->Close();
      delete psc; psc = NULL; px->SetSelfC(0);
   } // clean existing link
}
//-----------------------------------------------------------------------------------------------------------------------
static void TBinFile_Open( TXbClsParams * px )   // 3 //  ::Open(cFName,[cAccess],[cShare],lOpenAlways) -> lOk
{
   TBinFile * psc     = (TBinFile*) px->GetSelfC();
   px->PutReturnBool(FALSE);
   if( px->CheckParamType(1,XPP_CHARACTER) )
   {
      if( !psc ){ psc = new TBinFile; px->SetSelfC((void*) psc );}
      psc->Close();
      if( px->CheckParamType(1,XPP_CHARACTER) )
      {
         DWORD dwAccess,dwShare;
         TBinFile_GetAccessAndShare(px,2,&dwAccess,3,&dwShare);
         if( psc->Open(px->ParamLockStr(1),dwAccess,dwShare, px->GetParamBool(4) ) ) px->PutReturnBool( TRUE );
         else { delete psc; psc = NULL; px->SetSelfC( 0 ); }
         px->ParamUnlockStr(1);
         return;
      }
   }
   if( psc ) { delete psc; psc = NULL; px->SetSelfC(0); }
}
//-----------------------------------------------------------------------------------------------------------------------
// ::Create(1 cFName,2[cAccess],3[cShare], 4[pSecurity|lInherit],5[dwFunc],6[dwAttrib],7[hTemplate]) -> lOk
static void TBinFile_Create( TXbClsParams * px )
{
   TBinFile * psc      = (TBinFile*) px->GetSelfC();
   SECURITY_ATTRIBUTES sa;
   px->PutReturnBool(FALSE);
   if( px->CheckParamType(1,XPP_CHARACTER) )
   {
      if( !psc ){ psc = new TBinFile; px->SetSelfC( (void*) psc );}
      psc->Close();
      if( px->CheckParamType(1,XPP_CHARACTER) )
      {
         DWORD  dwAccess,dwShare;
         DWORD  dwFunc    = (px->CheckParamType(5,XPP_NUMERIC) ? px->GetParamDWord(5) : CREATE_ALWAYS );
         DWORD  dwFlags   = (px->CheckParamType(6,XPP_NUMERIC) ? px->GetParamDWord(6) : FILE_ATTRIBUTE_NORMAL );
         HANDLE hTemplate = (HANDLE) (px->CheckParamType(7,XPP_NUMERIC) ? px->GetParamDWord(7) : 0);
         LPSECURITY_ATTRIBUTES psa = (LPSECURITY_ATTRIBUTES) 0;
         TBinFile_GetSecurityAttrib(px,4,&sa,&psa);
         TBinFile_GetAccessAndShare(px,2,&dwAccess,3,&dwShare);
         if( psc->Create(px->ParamLockStr(1),dwAccess,dwShare,psa,dwFunc,dwFlags,hTemplate) ) px->PutReturnBool( TRUE );
         else { delete psc; psc = NULL; px->SetSelfC(0); }
         px->ParamUnlockStr(1);
         return;
      }
   }
   if( psc ) { delete psc; psc = NULL; px->SetSelfC(0); }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TBinFile_hFile( TXbClsParams * px )   // 0 //  ? ::hFile -> nHandle | NIL
{
   TBinFile * psc     = (TBinFile*) px->GetSelfC();
   if( psc )
   {
      if( psc->m_hFile ) px->PutReturnLong( (LONG) psc->m_hFile );
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TBinFile_GetAccessAndShare( TXbClsParams * px , ULONG npa,DWORD * pdwa , ULONG nps,DWORD * pdws )
{
   if( pdwa )
   {
      pdwa[0] = (GENERIC_READ | GENERIC_WRITE);
      if( px->CheckParamType(npa, XPP_LOGICAL) )
      {
         if( !px->GetParamBool(npa) ) pdwa[0] = 0;
      }
      else if( px->CheckParamType(npa, XPP_NUMERIC) ) pdwa[0] = px->GetParamDWord(npa);
      else if( px->CheckParamType(npa, XPP_CHARACTER) )
      {
         char sz[10];
         ULONG n;
         _bset( (LPBYTE) sz , 0 , 10 );
         px->ParamGetCL(npa,sz,9);
         pdwa[0] = 0;
         for( n = 0; n < 9; n++)
         {
            switch( sz[n] )
            {
               case 'r': ; case 'R': pdwa[0] |= GENERIC_READ  ; break;
               case 'w': ; case 'W': pdwa[0] |= GENERIC_WRITE ; break;
               default: break;
            }
         }
      }
   }

   if( pdws )
   {
      pdws[0] = 0;
      if( px->CheckParamType(nps, XPP_LOGICAL) )
      {
         if( px->GetParamBool(nps) ) pdws[0] = FILE_SHARE_READ | FILE_SHARE_WRITE ;
      }
      else if( px->CheckParamType(nps, XPP_NUMERIC) ) pdws[0] = px->GetParamDWord(nps);
      else if( px->CheckParamType(nps, XPP_CHARACTER) )
      {
         char sz[10];
         ULONG n;
         _bset( (LPBYTE) sz , 0 , 10 );
         px->ParamGetCL(nps,sz,9);
         pdws[0] = 0;
         for( n = 0; n < 9; n++)
         {
            switch( sz[n] )
            {
               case 'r': case 'R': pdws[0] |= FILE_SHARE_READ   ; break;
               case 'w': case 'W': pdws[0] |= FILE_SHARE_WRITE  ; break;
               case 'd': case 'D': pdws[0] |= FILE_SHARE_DELETE ; break;
               default: break;
            }
         }
      }
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TBinFile_GetSecurityAttrib( TXbClsParams * px , ULONG np, SECURITY_ATTRIBUTES* psl,SECURITY_ATTRIBUTES** ppsa)
{
   psl->nLength = sizeof(SECURITY_ATTRIBUTES);
   if( px->CheckParamType(np,XPP_LOGICAL) )
   {
      ppsa[0] = psl;
      psl->lpSecurityDescriptor = NULL;
      psl->bInheritHandle = px->GetParamBool(np);
      return;
   }
   else if( px->CheckParamType(np,XPP_NUMERIC | XPP_CHARACTER | XPP_ARRAY) )
   {
      SECURITY_ATTRIBUTES* p = (SECURITY_ATTRIBUTES*) px->ParamRLockStrEx(np);
      if( p )
      {
         ULONG nLen = px->ParamExLen(np);
         if( nLen >= sizeof( SECURITY_ATTRIBUTES ) )
         {
            ppsa[0] = psl;
            psl->lpSecurityDescriptor = p->lpSecurityDescriptor;
            psl->bInheritHandle = p->bInheritHandle;
         }
         px->ParamUnLockStrEx(np);
      }
   }
}
//-----------------------------------------------------------------------------------------------------------------------
// ::Read(NIL, nBytes [, @nRead] ) -> nBytes | NIL
static void TBinFile_Read( TXbClsParams * px ) // 3 // ::Read( @ptEx,[nBytes] , @ nRead  ) -> nBytes | NIL
{
   TBinFile * psc = (TBinFile*) px->GetSelfC();
   DWORD dw       = 0;
   if( psc )
   {
      if( px->CheckParamType(1,XPP_UNDEF ) && px->CheckParamType(2,XPP_NUMERIC) )
      {
         DWORD  dwSize = px->GetParamDWord(2);
         if( ((LONG) dwSize ) < 0 )
         {
            dwSize  = 0;
         }
         void * pBuffer = _xgrab( dwSize + 1 );
         if( ReadFile( psc->m_hFile , pBuffer , dwSize , &dw , NULL) )
         {
            px->PutReturnStrLen((LPSTR) pBuffer,dw);
         }
         _xfree( pBuffer);
         pBuffer = 0;
         px->PutParamDWord(3,dw);
         return;
      } 
     
            
      void * pBuffer = px->ParamWLockStrEx(1);
      if( pBuffer )
      {
         DWORD  dwSize = (DWORD) ( px->CheckParamType(2,XPP_NUMERIC) ? px->GetParamDWord(2) : px->ParamExLen(1));
         if( dwSize )
         {
            if( ReadFile( psc->m_hFile , pBuffer , dwSize , &dw , NULL) )
            {
               px->PutReturnDWord( dw );
            }
         }
         px->ParamUnLockStrEx(1);
      }
   }
   px->PutParamDWord(3,dw);         
}
//----------------------------------------------------------------------------------------------------------------------
static void TBinFile_Write( TXbClsParams * px ) // 3 // ::Write( @ptEx,[nBytes] , @ nRead  ) -> nBytes | NIL
{
   TBinFile * psc = (TBinFile*) px->GetSelfC();
   DWORD dw       = 0;
   if( psc )
   {
      void * pBuffer = px->ParamRLockStrEx(1);
      if( pBuffer )
      {
         DWORD  dwSize = (DWORD) ( px->CheckParamType(2,XPP_NUMERIC) ? px->GetParamDWord(2) : px->ParamExLen(1));
         if( dwSize )
         {
            if( WriteFile( psc->m_hFile , pBuffer , dwSize , &dw , NULL) )
            {
               px->PutReturnDWord( dw );
            }
         }
         px->ParamUnLockStrEx(1);
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TBinFile_GoTo( TXbClsParams * px ) // ::GoTo(nSkip,nFrom) -> lOk
{
   TBinFile * psc = (TBinFile*) px->GetSelfC();
   LONGLONG   q   =  -1;
   if( psc ) q = psc->SetFPointer64( px->GetParamQWord(1), px->GetParamDWord(2) );
   px->PutReturnBool( (BOOL) !(q == -1) );
}
//----------------------------------------------------------------------------------------------------------------------
static void TBinFile_GetPos( TXbClsParams * px ) // ::GetPos( @uPos ) -> ndPos | uPos
{
   TBinFile * psc = (TBinFile*) px->GetSelfC();
   if( psc )
   {
      LARGE_INTEGER li;
      li.QuadPart = psc->GetFPointer64();
      if( px->CheckParamType( 1 , XPP_CHARACTER ) )  px->PutParamQWord( 1 , li.QuadPart );
      else if( px->CheckParamType( 1 , XPP_ARRAY ) )
      {
         ContainerHandle cona = px->GetParam(1);
         if( _conGetArrayLen(cona) != 2 )
         {
            cona = _conNewArray( 1, 2 );
            px->PutParam( 1 , cona ) ;
            _conRelease( cona );
            cona = px->GetParam(1);
         }
         _conArrayPutNL(cona,(LONG) li.LowPart  , 1, 0);
         _conArrayPutNL(cona,(LONG) li.HighPart , 2, 0);
      }
      else
      {
         px->PutReturnDouble( (double) li.QuadPart );
         return;
         
      }

      px->PutReturn( px->GetParam(1) );
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TBinFile_SetEof( TXbClsParams * px )
{
   TBinFile * psc = (TBinFile*) px->GetSelfC();
   if( psc )
   {
      px->PutReturnBool(SetEndOfFile(psc->m_hFile));
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TBinFile_Commit( TXbClsParams * px )
{
   TBinFile * psc = (TBinFile*) px->GetSelfC();
   if( psc )
   {
      px->PutReturnBool(FlushFileBuffers(psc->m_hFile));
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TBinFile_ReadLine( TXbClsParams * px ) // ReadLine( @lEof,@lEol ) -> cLine
{
   TBinFile * psc = (TBinFile*) px->GetSelfC();
   if( psc )
   {
      DWORD dwLen = 0;
      BOOL bEof = FALSE;
      BOOL bEol = FALSE;
      LPBYTE p  = psc->ReadLine(&dwLen,&bEof,&bEol);
      if( p )
      {
         px->PutReturnStrLen((LPSTR) p,dwLen );
      }
      else
      {
         px->PutReturnStr("");
      }

      px->PutParamBool(1,bEof);
      px->PutParamBool(2,bEol);
   }
}

// --------------------------------------------------------------------------------------------------------------------------
static void TBinFile_ReadMimeHeader(TXbClsParams * px) // ReadMimeHeader( @lEof,@lEoh ) -> cLine
{
	TBinFile * psc = (TBinFile*)px->GetSelfC();
	if (psc)
	{
		DWORD dwLen = 0;
		BOOL bEof = FALSE;
		BOOL bEoh = FALSE;
		LPBYTE p = psc->ReadMimeHeader(&dwLen, &bEof, &bEoh);
		if (p)
		{
			px->PutReturnStrLen((LPSTR)p, dwLen);
		}
		else
		{
			px->PutReturnStr("");
		}

		px->PutParamBool(1, bEof);
		px->PutParamBool(2, bEoh);
	}
}


//----------------------------------------------------------------------------------------------------------------------
static void TBinFile_ResetBuffer( TXbClsParams * px ) // ResetBuffer( [nSize] )
{
   TBinFile * psc = (TBinFile*) px->GetSelfC();
   if( psc )
   {
      if( px->PCount() > 0 )
      {
         psc->ResetBuffer( px->GetParamDWord(1) );
      }
      else
      {
         psc->ResetBuffer();
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TBinFile_LoadBuffer( TXbClsParams * px ) // LoadBuffer(@lEof,lSkip = .T.) -> nBytes
{
   TBinFile * psc = (TBinFile*) px->GetSelfC();
   if( psc )
   {
      LONGLONG  q = psc->GetFPointer64();
      BOOL      bEof = FALSE;
      psc->LoadBuffer(&bEof);
      px->PutParamBool(1,bEof);
      if( px->CheckParamType(2,XPP_LOGICAL) && (!px->GetParamBool(2)))
      {
         psc->SetFPointer64(q);
      }
      px->PutReturnDWord( psc->m_dwBuffLen );
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TBinFile_PeekBytesFromBuffer( TXbClsParams * px ) // PeekBytesFromBuffer(nRelOffset = 0 , nBytes= 0) -> cString
{
   TBinFile * psc = (TBinFile*) px->GetSelfC();
   if( psc )
   {
      DWORD sh = px->GetParamDWord(1);
      DWORD cb = px->GetParamDWord(2);
      if( sh >= psc->m_dwBuffLen ){ cb = 0; }
      if( cb > ( psc->m_dwBuffLen - sh ) ){ cb = psc->m_dwBuffLen - sh; }
      LPBYTE p = psc->GetBaseBuffer();
      if( !p ){ return; }
      p = _mk_ptr_(LPBYTE,p,sh);
      px->PutReturnStrLen((LPSTR) p,cb);
   }
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL lMemoWrite(LPSTR pFileName,LPBYTE pBuffer, DWORD cb , BOOL bAppend)
{
   BOOL bResult = FALSE;
   HANDLE hFile = CreateFile( pFileName ,  GENERIC_WRITE | GENERIC_READ , 0 , NULL,
                                          ( bAppend ? OPEN_ALWAYS : CREATE_ALWAYS ),
                                          FILE_ATTRIBUTE_NORMAL , NULL );

   if( hFile != INVALID_HANDLE_VALUE )
   {
      DWORD dw = 0;
      if( bAppend ) SetFilePointer( hFile , 0 , NULL , FILE_END);
      if( cb == (DWORD) -1 ) cb = _xstrlen((LPSTR) pBuffer);
      bResult = WriteFile(hFile, pBuffer , cb , &dw , NULL);
      CloseHandle( hFile );
   }
   return bResult;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPBYTE pMemoRead(LPSTR pFileName, DWORD* pcb )
{
   DWORD dw,dwr;
   HANDLE hFile = CreateFile(pFileName , GENERIC_READ , 0 , NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
   LPBYTE p;
   if( hFile == INVALID_HANDLE_VALUE ) return 0;
   dw = SetFilePointer( hFile , 0 , 0, FILE_END);
   SetFilePointer( hFile , 0 , 0, FILE_BEGIN );
   p = (LPBYTE) _xgrab(dw + 2);
   ReadFile(hFile,p,dw,&dwr,0);
   CloseHandle( hFile );
   if( pcb ) *pcb = dwr;
   return p;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPBYTE pMemoReadEx(LPSTR pFileName, DWORD* pcb , LPBYTE pBuffer , DWORD dwOffset , DWORD dwMaxBytes )
{
   DWORD dw = 0;
   return pMemoReadEx2(pFileName,pcb,pBuffer,dwOffset,dwMaxBytes,dw);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPBYTE pMemoReadEx2(LPSTR pFileName, DWORD* pcb , LPBYTE pBuffer , DWORD dwOffset , DWORD dwMaxBytes , DWORD & dwFlags  )
{
   DWORD dw;
   DWORD dwr = 0;
   DWORD fshare_flags = ( (dwFlags & 1) ? 0 :  (FILE_SHARE_READ | FILE_SHARE_WRITE) );
   HANDLE hFile = CreateFile(pFileName , GENERIC_READ , fshare_flags , NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
   LPBYTE p = 0;
   DWORD dwBytesToRead;
   if( hFile == INVALID_HANDLE_VALUE )
   {
      if( dwFlags & 2 )
      {
         dwFlags = (DWORD) INVALID_HANDLE_VALUE;
      }
      return 0;
   }
   dw = SetFilePointer( hFile , 0 , 0, FILE_END);
   dwBytesToRead = ( (dwOffset > dw) ? 0 : dw - dwOffset );
   if( dwBytesToRead > dwMaxBytes ){ dwBytesToRead = dwMaxBytes; }
   if( dwBytesToRead )
   {
      p = ( pBuffer ? pBuffer : ((LPBYTE) _xgrab( dwBytesToRead + 2)) );
      SetFilePointer( hFile , dwOffset , 0 , FILE_BEGIN );
      ReadFile(hFile,p,dwBytesToRead,&dwr,0);
   }
   CloseHandle( hFile );
   if( pcb ) *pcb = dwr;
   return p;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD dwWriteLogData(LPSTR pFName, void* data , DWORD cb , LONGLONG* pLocator64 )
{
   DWORD dwLocator = 0;
   HANDLE hFile = CreateFile( pFName,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,0,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
   if( pLocator64 ){ pLocator64[0] = 0; }
   if( hFile != INVALID_HANDLE_VALUE )
   {
      if( data && cb )
      {
         LONG nn;      
         BOOL bOk = FALSE;
         LARGE_INTEGER  liSize; liSize.HighPart = 0; liSize.LowPart = cb;
         for( nn= 0; (nn < 20) && !bOk; nn++ )
         {
            LARGE_INTEGER  liStart;
            LARGE_INTEGER  li; 
            liStart.QuadPart = li.QuadPart = 0;
            if( SetFilePointerEx(hFile,li,&liStart,FILE_END) )
            {
               li.LowPart = cb; li.HighPart = 0;
               li.QuadPart += 16;
               if( LockFile(hFile,liStart.LowPart,liStart.HighPart,li.LowPart,li.HighPart) )
               {
                  DWORD dw = 0;
                  bOk = WriteFile(hFile,data,cb, &dw, 0);
                  if( bOk && (cb == dw) )
                  {
                     if( pLocator64 ){ pLocator64[0] = liStart.QuadPart; }
                     dwLocator = liStart.LowPart;
                  }
                  else
                  {
                     if( SetFilePointerEx(hFile,liStart,0,FILE_BEGIN ) )
                     {
                        SetEndOfFile(hFile);
                        nn = 100; // no more loops
                     }
                  }
                  UnlockFile(hFile,liStart.LowPart,liStart.HighPart,li.LowPart,li.HighPart);
               }
            }
         }
         if(!bOk){ Sleep(300); }
      }
      CloseHandle( hFile);
   }
   return dwLocator;
}
// -----------------------------------------------------------------------------------------------------------------
   
