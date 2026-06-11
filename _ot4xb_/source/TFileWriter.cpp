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

/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>TFileWriter</name>
      <category>file/binary</category>
      <description>
         Buffered writer that can write to a disk file, an attached Win32 file handle, or an internal memory buffer.
         It can also decode selected transfer encodings while data is being added.
      </description>
      <syntax>TFileWriter():new() -> oWriter</syntax>
      <class-properties>
         <property name="e_enc_none" type="numeric">No transfer decoding.</property>
         <property name="e_enc_base64_decode" type="numeric">Decode Base64 input before storing or writing it.</property>
         <property name="e_enc_uu_decode" type="numeric">Decode uuencoded input before storing or writing it.</property>
         <property name="e_enc_qp_decode" type="numeric">Decode quoted-printable input before storing or writing it.</property>
         <property name="e_enc_ot4xb_encode" type="numeric">Use the OT4XB internal encoder used by the XML writer helpers.</property>
         <property name="e_enc_count" type="numeric">Number of encoder identifiers.</property>
      </class-properties>
      <properties>
         <property name="buffer" type="character" access="readonly">Internal buffer contents when the writer is in memory-only mode.</property>
         <property name="buffer_len" type="numeric" access="readonly">Internal buffer length in memory-only mode; -1 when writing to a file handle.</property>
         <property name="file_size" type="numeric" access="readonly">Current output file size, or 0 in memory-only mode.</property>
      </properties>
      <methods>
         <method name="Release" syntax="::Release() -> Self">Releases the internal C++ writer object.</method>
         <method name="Create" syntax="::Create( cFilename, [lPreserveBuffer := .F.] ) -> lOk">Creates the target file. If creation fails the object remains in memory-only mode.</method>
         <method name="AttachFileHandle" syntax="::AttachFileHandle( hFile, [lPreserveBuffer := .F.] ) -> NIL">Uses an existing Win32 file handle as the output target.</method>
         <method name="DetachFileHandle" syntax="::DetachFileHandle() -> hFile">Detaches and returns the current file handle; the writer switches back to memory-only mode.</method>
         <method name="GetFileHandle" syntax="::GetFileHandle() -> hFile">Returns the current output file handle.</method>
         <method name="Close" syntax="::Close() -> NIL">Closes the current file target and switches back to memory-only mode.</method>
         <method name="SetEncoderEngine" syntax="::SetEncoderEngine( nEncoder, [nFlags := 0] ) -> lOk">Selects one of the e_enc_* transfer decoders.</method>
         <method name="SetCacheSize" syntax="::SetCacheSize( nBytes ) -> NIL">Changes the cache size used before flushing to the file target.</method>
         <method name="Add" syntax="::Add( cBytes, [nBytes] ) -> lOk">Adds bytes to the writer. The selected encoder is applied before the data is stored or flushed.</method>
         <method name="xml_ot4xb_wa_field_col" syntax="::xml_ot4xb_wa_field_col( nWorkArea, cFieldName ) -> lOk">Writes one work-area field value as an XML col node.</method>
         <method name="write_xml_node_from_value" syntax="::write_xml_node_from_value( xValue, cTag, [nFlags], [cNodeName] ) -> lOk">Writes an XML node for an Xbase++ value.</method>
         <method name="write_xml_value" syntax="::write_xml_value( xValue ) -> lOk">Writes an XML representation of an Xbase++ value.</method>
         <method name="Write" syntax="::Write() -> lOk">Flushes pending cached data to the file target. It is a no-op success in memory-only mode.</method>
         <method name="Commit" syntax="::Commit() -> NIL">Flushes pending data and commits the file buffers.</method>
         <method name="truncate_buffer" syntax="::truncate_buffer() -> NIL">Clears the internal memory cache.</method>
      </methods>
      <remarks>
         A newly created instance starts in memory-only mode. Use ::Create() or ::AttachFileHandle() to send output to
         a file. The readonly buffer helpers are intended for the memory-only mode.
      </remarks>
   </class>
</xbdoc>
*******************************************************************************************************************/

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
XPPRET XPPENTRY TFILEWRITER(XppParamList pl)
{
   ContainerHandle conco = _conClsObj("TFileWriter");
   // ---------------------------------------------------------------------------------
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName( "TFileWriter" );
      pc->EXPORTED();
      pc->AddGwstStyleMembers();
      // ---------------------------------------------------------------------------------
      pc->ClassProperty_cbbs( "e_enc_none"          , "{|s| %i }" , TFileWriter::e_enc_none           );
      pc->ClassProperty_cbbs( "e_enc_base64_decode" , "{|s| %i }" , TFileWriter::e_enc_base64_decode  );
      pc->ClassProperty_cbbs( "e_enc_uu_decode"     , "{|s| %i }" , TFileWriter::e_enc_uu_decode      );
      pc->ClassProperty_cbbs( "e_enc_qp_decode"     , "{|s| %i }" , TFileWriter::e_enc_qp_decode      );
	  pc->ClassProperty_cbbs("e_enc_ot4xb_encode", "{|s| %i }", TFileWriter::e_enc_ot4xb_encode);
      pc->ClassProperty_cbbs( "e_enc_count"         , "{|s| %i }" , TFileWriter::e_enc_count          );

     // ---------------------------------------------------------------------------------      
      pc->Method( "init"             , TFileWriter_init              , 0 ); // ::New() -> Self
      pc->Method( "Release"          , TFileWriter_Release           , 0 ); // ::Release() -> Self
      pc->Method( "Create"           , TFileWriter_Create            , 2 ); //    BOOL   Create( LPSTR pFilename , BOOL bPreserveBuffer);
      pc->Method( "AttachFileHandle" , TFileWriter_AttachFileHandle  , 2 ); //    void   AttachFileHandle( HANDLE hFile , BOOL bPreserveBuffer);
      pc->Method( "DetachFileHandle" , TFileWriter_DetachFileHandle  , 0 ); //    HANDLE DetachFileHandle(void);
      pc->Method( "GetFileHandle"    , TFileWriter_GetFileHandle     , 0 ); //    HANDLE GetFileHandle(void);
      pc->Method( "Close"            , TFileWriter_Close             , 0 ); //    void   Close(void);
      pc->Method( "SetEncoderEngine" , TFileWriter_SetEncoderEngine  , 2 ); //    BOOL   SetEncoderEngine( enc_e encoder , DWORD nFlags = 0 );
      pc->Method( "SetCacheSize"     , TFileWriter_SetCacheSize      , 1 ); //    void   SetCacheSize( DWORD nBytes);
      pc->Method( "Add"              , TFileWriter_Add               , 2 ); //    BOOL   Add( LPBYTE p , int cb = - 1 );
	  pc->Method( "xml_ot4xb_wa_field_col", TFileWriter_xml_ot4xb_wa_field_col, 2); //    BOOL   xml_ot4xb_wa_field_col(int wa , LPSTR fname);
	  pc->Method( "write_xml_node_from_value", TFileWriter_write_xml_node_from_value, 4) ; //    BOOL   1 value , 2 tag , 3 flags , 4node_name
	  pc->Method( "write_xml_value", TFileWriter_write_xml_value, 1 ); //    BOOL   1 value 
      pc->Method( "Write"            , TFileWriter_Write             , 0 ); //    BOOL   Write(void);
      pc->Method( "Commit"           , TFileWriter_Commit            , 0 ); //    void   Commit(void);
      pc->ROProperty( "buffer"       , TFileWriter_buffer            , 0 ); //    
      pc->ROProperty( "buffer_len"   , TFileWriter_buffer_len        , 0 ); //    
      pc->ROProperty( "file_size"    , TFileWriter_file_size         , 0 ); //          
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

