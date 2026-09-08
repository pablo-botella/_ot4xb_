//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
#define PXERROR( n , m , d )  px->GenError();px->SetErrorSubSystem("ot4xb"); \
                              px->SetErrorOperation("TFileWriter::"  ##m  "()"); \
                              px->SetErrorDescription( d ); \
                              px->SetErrorGenCode(0x00105000 + n);
//----------------------------------------------------------------------------------------------------------------------

static void TFileWriter_init( TXbClsParams * px );               // 1 // ::New() -> Self
static void TFileWriter_Release( TXbClsParams * px );            // 0 // ::Release() -> Self
static void TFileWriter_Create( TXbClsParams * px );             // 1 //    BOOL   Create( LPSTR pFilename , BOOL bPreserveBuffer);
static void TFileWriter_AttachFileHandle( TXbClsParams * px );   // 1 //    void   AttachFileHandle( HANDLE hFile , BOOL bPreserveBuffer);
static void TFileWriter_DetachFileHandle( TXbClsParams * px );   // 0 //    HANDLE DetachFileHandle(void);
static void TFileWriter_GetFileHandle( TXbClsParams * px );      // 0 //    HANDLE GetFileHandle(void);
static void TFileWriter_Close( TXbClsParams * px );              // 0 //    void   Close(void);
static void TFileWriter_SetEncoderEngine( TXbClsParams * px );   // 2 //    BOOL   SetEncoderEngine( enc_e encoder , DWORD nFlags = 0 );
static void TFileWriter_SetCacheSize( TXbClsParams * px );       // 1 //    void   SetCacheSize( DWORD nBytes);
static void TFileWriter_Add( TXbClsParams * px );                // 2 //    BOOL   Add( LPBYTE p , int cb = - 1 );
static void TFileWriter_xml_ot4xb_wa_field_col(TXbClsParams * px);// 2 //    BOOL  BOOL   xml_ot4xb_wa_field_col(int wa , LPSTR fname);
static void TFileWriter_write_xml_node_from_value(TXbClsParams * px);// 1 value , 2 tag , 3 flags , 4node_name
static void TFileWriter_write_xml_value( TXbClsParams * px );// 1 value
static void TFileWriter_Write( TXbClsParams * px );              // 0 //    BOOL   Write(void);
static void TFileWriter_Commit( TXbClsParams * px );             // 0 //    void   Commit(void);
static void TFileWriter_buffer( TXbClsParams * px );
static void TFileWriter_buffer_len( TXbClsParams * px );
static void TFileWriter_file_size( TXbClsParams * px );
static void TFileWriter_truncate_buffer( TXbClsParams * px );

//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: TFileWriter
            | _slug_: tfilewriter
            | class-function: TFILEWRITER
            | category: filesystem
            | desc: Buffered file writer: data added through Add() is accumulated in a memory buffer, optionally
              transformed by an encoder engine (base64/uu/qp decode or ot4xb escaping), and written to a file
              created by the object or to an attached file handle. Includes helpers to write values as XML nodes.
            | note: A new writer starts in memory-only mode: added data stays in the internal buffer, readable
              through the buffer property. ::Create() or ::AttachFileHandle() switch the output to a file;
              ::Close() or ::DetachFileHandle() return the writer to memory-only mode.
            | note: The buffer and buffer_len properties are meant for the memory-only mode.
            | _kw_: TFileWriter, Class
   }}*/
XPPRET XPPENTRY TFILEWRITER(XppParamList pl)
{
   ContainerHandle conco = _conClsObj("TFileWriter");
   // ---------------------------------------------------------------------------------
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName( "TFileWriter" );
      /*{{|:**BEGIN CLASS  TFileWriter** }}*/
      pc->EXPORTED();
      pc->AddGwstStyleMembers();
      // ---------------------------------------------------------------------------------
      /*{{|class-property_: - CLASS PROPERTY e_enc_none
               | type: Numeric
               | desc_: Encoder engine id for ::SetEncoderEngine(): no transformation, ::Add() appends the
                 bytes exactly as given. A new writer starts with this engine selected.
      }}*/
      pc->ClassProperty_cbbs( "e_enc_none"          , "{|s| %i }" , TFileWriter::e_enc_none           );
      /*{{|class-property_: - CLASS PROPERTY e_enc_base64_decode
               | type: Numeric
               | desc_: Encoder engine id for ::SetEncoderEngine(): the data given to ::Add() is Base64
                 decoded before it is cached or written.
      }}*/
      pc->ClassProperty_cbbs( "e_enc_base64_decode" , "{|s| %i }" , TFileWriter::e_enc_base64_decode  );
      /*{{|class-property_: - CLASS PROPERTY e_enc_uu_decode
               | type: Numeric
               | desc_: Encoder engine id for ::SetEncoderEngine(): the data given to ::Add() is uudecoded
                 before it is cached or written.
      }}*/
      pc->ClassProperty_cbbs( "e_enc_uu_decode"     , "{|s| %i }" , TFileWriter::e_enc_uu_decode      );
      /*{{|class-property_: - CLASS PROPERTY e_enc_qp_decode
               | type: Numeric
               | desc_: Encoder engine id for ::SetEncoderEngine(): the data given to ::Add() is
                 quoted-printable decoded before it is cached or written; the nFlags value given to
                 ::SetEncoderEngine() is passed to the decoder.
      }}*/
      pc->ClassProperty_cbbs( "e_enc_qp_decode"     , "{|s| %i }" , TFileWriter::e_enc_qp_decode      );
      /*{{|class-property_: - CLASS PROPERTY e_enc_ot4xb_encode
               | type: Numeric
               | desc_: Encoder engine id for ::SetEncoderEngine(): the data given to ::Add() is escaped with
                 the ot4xb backslash notation (\n, \xNN, ...); the nFlags value given to ::SetEncoderEngine()
                 is passed to the encoder. The XML writer methods select this engine internally to escape
                 unsafe Character content.
      }}*/
	  pc->ClassProperty_cbbs("e_enc_ot4xb_encode", "{|s| %i }", TFileWriter::e_enc_ot4xb_encode);
      /*{{|class-property_: - CLASS PROPERTY e_enc_count
               | type: Numeric
               | desc_: Number of encoder engine ids; not an engine itself. ::SetEncoderEngine() accepts
                 values from e_enc_none up to, but not including, e_enc_count.
      }}*/
      pc->ClassProperty_cbbs( "e_enc_count"         , "{|s| %i }" , TFileWriter::e_enc_count          );

     // ---------------------------------------------------------------------------------      
      /*{{|method_: - `METHOD new()`
               | return: oWriter
               | desc_: Creates the internal C++ writer. A new writer starts in memory-only mode, with the
                 e_enc_none engine selected and a cache threshold of 1 MB.
      }}*/
      pc->Method( "init"             , TFileWriter_init              , 0 ); // ::New() -> Self
      /*{{|method_: - `METHOD Release()`
               | return: Self
               | desc_: Destroys the internal C++ writer. An active file target receives the pending cached
                 data and is closed. Later method calls on the object are ignored.
      }}*/
      pc->Method( "Release"          , TFileWriter_Release           , 0 ); // ::Release() -> Self
      /*{{|method_: - `METHOD Create( cFilename, [lPreserveBuffer] )`
               | return: lOk
               | desc_: Creates cFilename (an existing file is overwritten) and makes it the output target.
                 The memory cache is cleared first unless lPreserveBuffer is .T., which keeps already added
                 data to be written into the new file. When creation fails the writer stays in memory-only
                 mode and .F. is returned.
      }}*/
      pc->Method( "Create"           , TFileWriter_Create            , 2 ); //    BOOL   Create( LPSTR pFilename , BOOL bPreserveBuffer);
      /*{{|method_: - `METHOD AttachFileHandle( hFile, [lPreserveBuffer] )`
               | return: NIL
               | desc_: Makes hFile, an open Win32 file handle, the output target; the previous file target,
                 when active, is closed. The memory cache is cleared first unless lPreserveBuffer is .T.
                 Passing 0 or -1 leaves the writer in memory-only mode.
      }}*/
      pc->Method( "AttachFileHandle" , TFileWriter_AttachFileHandle  , 2 ); //    void   AttachFileHandle( HANDLE hFile , BOOL bPreserveBuffer);
      /*{{|method_: - `METHOD DetachFileHandle()`
               | return: hFile
               | desc_: Disconnects and returns the output file handle without closing it; the writer goes
                 back to memory-only mode. Cached data pending to be written is not flushed.
      }}*/
      pc->Method( "DetachFileHandle" , TFileWriter_DetachFileHandle  , 0 ); //    HANDLE DetachFileHandle(void);
      /*{{|method_: - `METHOD GetFileHandle()`
               | return: hFile
               | desc_: Returns the Win32 handle of the current output file, -1 when there is no file target.
      }}*/
      pc->Method( "GetFileHandle"    , TFileWriter_GetFileHandle     , 0 ); //    HANDLE GetFileHandle(void);
      /*{{|method_: - `METHOD Close()`
               | return: NIL
               | desc_: Flushes pending cached data, closes the output file and returns the writer to
                 memory-only mode.
      }}*/
      pc->Method( "Close"            , TFileWriter_Close             , 0 ); //    void   Close(void);
      /*{{|method_: - `METHOD SetEncoderEngine( nEncoder, [nFlags] )`
               | return: lOk
               | desc_: Selects the encoder engine applied by ::Add(): nEncoder is one of the e_enc_* class
                 constants and nFlags is kept with it, to be passed to the qp decoder or the ot4xb escape
                 encoder. Returns .F. and changes nothing when nEncoder is not a valid e_enc_* value.
      }}*/
      pc->Method( "SetEncoderEngine" , TFileWriter_SetEncoderEngine  , 2 ); //    BOOL   SetEncoderEngine( enc_e encoder , DWORD nFlags = 0 );
      /*{{|method_: - `METHOD SetCacheSize( nBytes )`
               | return: NIL
               | desc_: Sets the cache threshold: with a file target, ::Add() flushes the cache to the file
                 once it reaches nBytes. The default is 1 MB.
      }}*/
      pc->Method( "SetCacheSize"     , TFileWriter_SetCacheSize      , 1 ); //    void   SetCacheSize( DWORD nBytes);
      /*{{|method_: - `METHOD Add( cBytes )`
               | return: lOk
               | desc_: Passes the bytes of cBytes through the selected encoder engine and appends the result
                 to the memory cache; with a file target the cache is flushed to the file when it reaches
                 the cache threshold. Returns .F. when the file handle is no longer valid or the engine
                 rejects the data.
               | note: The method is registered with two parameters, but the second one is ignored: the full
                 length of cBytes is always processed.
      }}*/
      pc->Method( "Add"              , TFileWriter_Add               , 2 ); //    BOOL   Add( LPBYTE p , int cb = - 1 );
      /*{{|method_: - `METHOD xml_ot4xb_wa_field_col( nWorkArea, cFieldName )`
               | return: lOk
               | desc_: Reads field cFieldName from work area nWorkArea and writes it as an XML col node,
                 <col name="...">, with type and length attributes. Returns .F. when nWorkArea is 0 or the
                 field value cannot be obtained.
      }}*/
	  pc->Method( "xml_ot4xb_wa_field_col", TFileWriter_xml_ot4xb_wa_field_col, 2); //    BOOL   xml_ot4xb_wa_field_col(int wa , LPSTR fname);
      /*{{|method_: - `METHOD write_xml_node_from_value( xValue, [cTag], [nFlags], [cNodeName] )`
               | return: lOk
               | desc_: Writes xValue as an XML node, `<cTag>value</cTag>`; cTag defaults to "col" and
                 cNodeName, when given, is written as a name="..." attribute. Numeric, Logical, Date and
                 Character values are written; other types produce an empty node. Character content that
                 needs it is escaped or encoded, and marked with an enc="..." attribute.
               | note: With the default nFlags (0x01100000) leading and trailing spaces of Character values
                 are removed and unsafe content always uses the ot4xb escape notation.
               | flags: nFlags bits (default 0x01100000):
                 - `0x80000000` add the type attributes: `t="int|double|bool|string"`, `d="decimals"`, `cb="bytes"`
                 - `0x40000000` Logical as `true` / `false` instead of `1` / `0`
                 - `0x20000000` strip leading spaces of Character values
                 - `0x10000000` strip trailing spaces and record what was stripped as `lt="n"` / `rt="n"` attributes
                 - `0x01000000` strip leading and trailing spaces, no attributes
                 - `0x00100000` always use the ot4xb escape notation for unsafe content (never `enc="hex"` /
                   `enc="base64"`, which are chosen automatically otherwise when the unsafe share is high)
      }}*/
	  pc->Method( "write_xml_node_from_value", TFileWriter_write_xml_node_from_value, 4) ; //    BOOL   1 value , 2 tag , 3 flags , 4node_name
      /*{{|method_: - `METHOD write_xml_value( xValue )`
               | return: lOk
               | desc_: Writes the plain XML text form of xValue with no surrounding tag: Numeric with its
                 decimals, Logical as true or false, Date as YYYYMMDD, Character with the ot4xb escape
                 notation applied when the content holds XML-unsafe bytes. Other types write nothing.
      }}*/
	  pc->Method( "write_xml_value", TFileWriter_write_xml_value, 1 ); //    BOOL   1 value 
      /*{{|method_: - `METHOD Write()`
               | return: lOk
               | desc_: Flushes the cached bytes to the output file. In memory-only mode, or when the cache
                 is empty, it returns .T. without doing anything. On success the cache is cleared; when the
                 Win32 write fails or is incomplete the file pointer is restored and the cache is kept.
      }}*/
      pc->Method( "Write"            , TFileWriter_Write             , 0 ); //    BOOL   Write(void);
      /*{{|method_: - `METHOD Commit()`
               | return: NIL
               | desc_: Flushes the cached bytes and makes the OS write its file buffers to disk
                 (FlushFileBuffers). It does nothing in memory-only mode.
      }}*/
      pc->Method( "Commit"           , TFileWriter_Commit            , 0 ); //    void   Commit(void);
      /*{{|property_: - PROPERTY buffer
               | type: Character
               | desc_: Read-only. The memory cache contents: the data collected while the writer is in
                 memory-only mode. NIL when a file target is active.
      }}*/
      pc->ROProperty( "buffer"       , TFileWriter_buffer            , 0 ); //    
      /*{{|property_: - PROPERTY buffer_len
               | type: Numeric
               | desc_: Read-only. The memory cache length in bytes while in memory-only mode, -1 when a
                 file target is active.
      }}*/
      pc->ROProperty( "buffer_len"   , TFileWriter_buffer_len        , 0 ); //    
      /*{{|property_: - PROPERTY file_size
               | type: Numeric
               | desc_: Read-only. The current size of the output file, or 0 in memory-only mode or when
                 the file handle is not valid. Sizes of 2 GB and above are returned as a floating point
                 value.
      }}*/
      pc->ROProperty( "file_size"    , TFileWriter_file_size         , 0 ); //          
      /*{{|method_: - `METHOD truncate_buffer()`
               | return: NIL
               | desc_: Discards the memory cache contents; cached data not yet written to the file target
                 is thrown away.
      }}*/
      /*{{|:**END CLASS** }}*/
      pc->Method( "truncate_buffer"  , TFileWriter_truncate_buffer   , 0 ); //    truncate_buffer();
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
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
static void TFileWriter_init( TXbClsParams * px )               // 0 // ::New() -> Self
{
   TFileWriter_Release( px );
   px->SetSelfC((void*) new TFileWriter );
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_Release( TXbClsParams * px )            // 0 // ::Release() -> Self
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   px->PutReturnSelf();
   if( psc )
   {
      delete psc; psc = 0; px->SetSelfC(0);
   } // clean existing link
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_Create( TXbClsParams * px )             // 1 //    BOOL   Create( LPSTR pFilename )
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      px->PutReturnBool( psc->Create( px->ParamLockStr(1) , px->GetParamBool(2) ) );
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_AttachFileHandle( TXbClsParams * px )   // 1 //    void   AttachFileHandle( HANDLE hFile )
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      psc->AttachFileHandle( (HANDLE) px->GetParamLong(1) , px->GetParamBool(2));
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_DetachFileHandle( TXbClsParams * px )   // 0 //    HANDLE DetachFileHandle(void)
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      px->PutReturnLong( (LONG) psc->DetachFileHandle() );
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_GetFileHandle( TXbClsParams * px )      // 0 //    HANDLE GetFileHandle(void)
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      px->PutReturnLong( (LONG) psc->GetFileHandle() );
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_Close( TXbClsParams * px )              // 0 //    void   Close(void)
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      psc->Close();
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_SetEncoderEngine( TXbClsParams * px )   // 2 //    BOOL   SetEncoderEngine( enc_e encoder , DWORD nFlags = 0 )
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      px->PutReturnBool(psc->SetEncoderEngine(( TFileWriter::enc_e) px->GetParamLong(1) , px->GetParamDWord(2) ));
   }
}
// -----------------------------------------------------------------------------------------------------------------

static void TFileWriter_SetCacheSize( TXbClsParams * px )       // 1 //    void   SetCacheSize( DWORD nBytes)
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      psc->SetCacheSize(px->GetParamDWord(1));
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_Add( TXbClsParams * px )                // 2 //    BOOL   Add( LPBYTE p , int cb = - 1 )
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      DWORD  cb = 0;
      LPBYTE p  = (LPBYTE) px->ParamLockStr(1,&cb);
      px->PutReturnBool( psc->Add(p,cb) );
   }
}
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_xml_ot4xb_wa_field_col(TXbClsParams * px)// 2 //  BOOL   xml_ot4xb_wa_field_col(int wa, LPSTR fname);
{
	TFileWriter * psc = (TFileWriter*)px->GetSelfC();
	if (psc)
	{
		BOOL result = FALSE;
		int wa = px->GetParamLong(1);
		if (wa)
		{
			LPSTR pfn = px->ParamLockStr(2);
			if (pfn)
			{
				ContainerHandle con = _conGetFieldNC(wa, pfn, 0);
				if (con)
				{
					result = psc->write_xml_node_from_container_value(con, "col", 0xF0000000, pfn);
					_conRelease(con);
				}

			}
		}

		px->PutReturnBool(result);
	}
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_write_xml_node_from_value(TXbClsParams * px)// 1 value , 2 tag , 3 flags , 4node_name
{
	TFileWriter * psc = (TFileWriter*)px->GetSelfC();
	if (psc)
	{
		BOOL result = FALSE;
		DWORD flags = px->CheckParamType(3, XPP_NUMERIC) ? px->GetParamDWord(3) : 0x01100000;
		result = psc->write_xml_node_from_container_value(px->GetParam(1),px->ParamLockStr(2),flags, px->ParamLockStr(4) );
		px->PutReturnBool(result);
	}
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_write_xml_value( TXbClsParams * px )// 1 value
{
	TFileWriter * psc = (TFileWriter*) px->GetSelfC();
	if ( psc )
	{
		BOOL result = FALSE;
		result = psc->write_xml_value_from_container( px->GetParam( 1 ));
		px->PutReturnBool( result );
	}
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_Write( TXbClsParams * px )              // 0 //    BOOL   Write(void)
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      px->PutReturnBool( psc->Write() );
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_Commit( TXbClsParams * px )             // 0 //    void   Commit(void)
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
     psc->Commit();
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_buffer( TXbClsParams * px )
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      if( psc->m_memory_only )
      {
         LPSTR  p  = (LPSTR) psc->m_cache.GetBuffer();
         DWORD  cb = psc->m_cache.len();
         if( p && cb)
         {
            px->PutReturnStrLen(p,cb);
         }
         else
         {
            px->PutReturnStr("");
         }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_buffer_len( TXbClsParams * px )
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      if( psc->m_memory_only )
      {
         px->PutReturnLong( (LONG)  psc->m_cache.len() );
      }
      else
      {
         px->PutReturnLong(-1);
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_file_size( TXbClsParams * px )
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      if( psc->m_memory_only || (psc->m_file.m_hFile == INVALID_HANDLE_VALUE) || (psc->m_file.m_hFile == 0) )
      {
         px->PutReturnLong(0);
         return;
      }
      LONGLONG current = psc->m_file.GetFPointer64();
      psc->m_file.SetFPointer64(0,FILE_END);
      LARGE_INTEGER size;
      size.QuadPart = psc->m_file.GetFPointer64();
      psc->m_file.SetFPointer64(current);
      if( (size.HighPart == 0) && (size.LowPart < 0x80000000) )
      {
         px->PutReturnDWord( size.LowPart );
      }
      else
      {
         px->PutReturnDouble( (double) size.QuadPart );
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TFileWriter_truncate_buffer( TXbClsParams * px )
{
   TFileWriter * psc     = (TFileWriter*) px->GetSelfC();
   if( psc )
   {
      psc->m_cache._truncate_buffer_();
   }
}
// -----------------------------------------------------------------------------------------------------------------

