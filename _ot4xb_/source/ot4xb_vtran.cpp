//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#define _CRT_SECURE_NO_DEPRECATE
#include <ot4xb_api.h>
extern BYTE _lower_ansi_char_table_[256];
//----------------------------------------------------------------------------------------------------------------------
#define __vtran_extra_str        0x00001
#define __vtran_extra_int        0x00002
#define __vtran_extra_float      0x00003
#define __vtran_extra_bool       0x00004



//----------------------------------------------------------------------------------------------------------------------

#define __vtran_type_case_upper       0x00010000
#define __vtran_type_case_lower       0x00020000
#define __vtran_type_align_left       0x00040000
#define __vtran_type_align_right      0x00080000
#define __vtran_type_ltrim            0x00100000
#define __vtran_type_rtrim            0x00200000
#define __vtran_type_from_left        0x00400000
#define __vtran_type_from_right       0x00800000
#define __vtran_type_dtos             0x01000000
#define __vtran_type_from_int         0x02000000
#define __vtran_type_from_double      0x04000000

#define __vtran_type_stringify        0x30000000

#define __vtran_type_stod             0x10000000
#define __vtran_type_to_int           0x20000000
#define __vtran_type_to_double        0x40000000

#define __vtran_type_char_max         0x04000000
#define __vtran_type_field_x          0x80000000
#define __vtran_readonly              0x40000000
#define __vtran_type_none             0
//----------------------------------------------------------------------------------------------------------------------
#define __vtran_bool_10               1
#define __vtran_bool_yes_no           2
#define __vtran_bool_YN               3
#define __vtran_bool_on_off           4
#define __vtran_bool_true_false       5
#define __vtran_bool_TF               6
#define __vtran_int_z                 7
// -----------------------------------------------------------------------------------------------------------------
#define __vtran_mask_read_none      0x00
#define __vtran_mask_read_mask      0x01
#define __vtran_mask_read_block     0x02

#define __vtran_mask_write_none     0x00
#define __vtran_mask_write_mask     0x10
#define __vtran_mask_write_block    0x20

// -----------------------------------------------------------------------------------------------------------------
#define __vtran_instance_flag_allow_any_function    1

// -----------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE( __vtran_ns )
// -----------------------------------------------------------------------------------------------------------------
typedef struct field_structure
{
   BYTE type;
   BYTE dec;
   WORD len;
} field_st, * field_ptr ;
// -----------------------------------------------------------------------------------------------------------------
typedef struct ft_item_structure
{
   BYTE type;
   BYTE dec;
   WORD len;
   char name[10];
   WORD pad;
   DWORD pos;
} ft_item_st, *ft_item_ptr ;
// -----------------------------------------------------------------------------------------------------------------
typedef struct table_struture
{
   DWORD dw_total_size;
   DWORD dw_item_count;
}  table_st , *table_ptr;
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
void transformation_pack(XppParamList pl);
void transformation_play(XppParamList pl);
void field_pack(XppParamList pl);
void field_unpack(XppParamList pl);
void field_table_pack(XppParamList pl);
// -----------------------------------------------------------------------------------------------------------------
ft_item_st * cona_field_table_pack(ContainerHandle cona , DWORD & field_count );
ContainerHandle parse_property_table_json_string( LPBYTE psz, DWORD cb );
DWORD pack_string( ContainerHandle con , LPSTR pAltString  , DWORD * pExtraFlags);
char unpack_field( field_st* fd , DWORD & len , DWORD & dec );
DWORD search_field( ft_item_st * f , DWORD fc , TXbCPItem* name  );
void process_string_and_put_return_value( TXbCPItem* result ,LPSTR & buffer , DWORD & buffer_size,DWORD & buffer_cb,DWORD dw_flags,field_st * fd, BOOL bStringify);
void transform_with_codeblock( TXbCPItem* result , ContainerHandle con_value, ContainerHandle con_block , field_st* fd);
LPSTR get_string(  TXbCPItem* item , DWORD & buffer_size , DWORD & buffer_cb ,  DWORD dw_flags , field_st * fd , BOOL bStringify);
void create_class_vtran( XppParamList pl);
namespace wa_ns { void create_class_vtran_workarea( XppParamList pl); }
namespace buffer_ns { void create_class_vtran_buffer( XppParamList pl); }
// -----------------------------------------------------------------------------------------------------------------
DWORD pack_string( ContainerHandle con , LPSTR pAltString , DWORD * pExtraFlags)
{
   BYTE  buffer[1024]; ZeroMemory(buffer,sizeof(buffer));
   DWORD count = 0;
   ULARGE_INTEGER items[64]; ZeroMemory( items , sizeof(items) );
   DWORD cb = 0;

   DWORD __dwExtraFlags__ = 0;

   if( !pExtraFlags ){ pExtraFlags = &__dwExtraFlags__; }

   pExtraFlags[0] = 0;

   if( con )
   {
      _conGetCL(con,&cb,(LPSTR) buffer, 255);
   }
   else
   {
      if( pAltString )
      {
         cb = _xstrlen(pAltString);
         if( cb > 1023){ cb = 1023;}
         _bcopy(buffer,(LPBYTE) pAltString,cb);
      }
   }
   LPBYTE p,pp;
   p = buffer;
   pp= _mk_ptr_(LPBYTE,p,256);
   items[count].LowPart = (DWORD) pp;
   for(; cb && (count < 60) ;p++,cb--)
   {
      if( *p == 44 )
      {
         if( items[count].HighPart < 8 )
         {
            pp = _mk_ptr_( LPBYTE , pp , 8 -  (items[count].HighPart ) );
         }

         count++;
         *pp = 0; pp++;
         items[count].LowPart = (DWORD) pp;
      }
      else if((*p > 64) && (*p < 91))
      {
         items[count].HighPart++;
         *pp = (*p) + 32; pp++;
      }
      else if(  ((*p > 47) && (*p < 59)) || ((*p > 96) && (*p < 123)) )
      {
         items[count].HighPart++;
         *pp = *p; pp++;
      }
   }
   DWORD dw = 0;
   DWORD dwItem;
   for( dwItem = 0; dwItem <= count; dwItem++ )
   {
      p   = (LPBYTE) items[dwItem].LowPart;
      cb  = items[dwItem].HighPart;
      if( p && (cb > 3) )
      {
         switch( _mk_ptr_(LPDWORD,p,0)[0] )
         {
            case 0x64616572 : // read
            {
               if( _mk_ptr_(LPDWORD,p,0)[1] == 0x796C6E6F ) // only
               {
                  dw |= __vtran_readonly;
               }
               break;
            }
            case 0x67696C61 : //alig
            {
               if( p[6] == 'r' )
               {
                  dw |= __vtran_type_align_right;
               }
               else if( p[6] == 'l' )
               {
                  dw |= __vtran_type_align_left;
               }
               break;
            }
            case 0x746c6c61 : //allt
            {
               dw |= __vtran_type_ltrim;
               dw |= __vtran_type_rtrim;
               break;
            }
            case 0x6972746C : //ltri
            {
               dw |= __vtran_type_ltrim;
               break;
            }
            case 0x69727472 : //rtri
            {
               dw |= __vtran_type_rtrim;
               break;
            }
            case 0x736f7464 : //dtos
            {
               dw |= __vtran_type_dtos;
               break;
            }
            case 0x736F746E :  // ntos
            {
                dw |= __vtran_type_stringify;
                break;
            }
            case 0x646F7473 : //stod
            {
               dw |= __vtran_type_stod;
               break;
            }
            case 0x65707075 : //uppe
            {
               dw |= __vtran_type_case_upper;
               break;
            }
            case 0x65776F6C : //lower
            {
               dw |= __vtran_type_case_lower;
               break;
            }
            case 0x68676972 : //right
            {
               dw |= __vtran_type_from_right;
               p = _mk_ptr_(LPBYTE,p,cb-2);
               dw |= ((chHex2Nibble(p[0]) << 4) & 0xF0 ) | (chHex2Nibble(p[1]) & 0x0F );
               break;
            }
            case 0x7466656C : //left
            {
               dw |= __vtran_type_from_left;
               p = _mk_ptr_(LPBYTE,p,cb-2);
               dw |= ((chHex2Nibble(p[0]) << 4) & 0xF0 ) | (chHex2Nibble(p[1]) & 0x0F );
               break;
            }
            case 0x3A386673 : //sf8:lldd // dd = decimals hex // ll = len hex
            {
               dw |= __vtran_type_from_double;
               p = _mk_ptr_(LPBYTE,p,4);
               dw |= ((chHex2Nibble(p[0]) << 4) & 0xF0 ) | (chHex2Nibble(p[1]) & 0x0F );
               dw |= ((((chHex2Nibble(p[2]) << 4) & 0xF0 ) | (chHex2Nibble(p[3]) & 0x0F )) << 8);
               break;
            }
            case 0x3A346973 : //si4:llz // flags = decimals hex // ll = len hex
            {
               dw |= __vtran_type_from_int;
               p = _mk_ptr_(LPBYTE,p,4);
               dw |= ((chHex2Nibble(p[0]) << 4) & 0xF0 ) | (chHex2Nibble(p[1]) & 0x0F );
               if( ((char) p[2]) == 'z' ){ dw |= 0x1000; }
               break;
            }
            case 0x3A346273 : //sb4:llH // flags = decimals hex // ll = len hex
            {
               dw |= __vtran_type_from_int;
               p = _mk_ptr_(LPBYTE,p,4);
               dw |= ((chHex2Nibble(p[0]) << 4) & 0xF0 ) | (chHex2Nibble(p[1]) & 0x0F );
               if( ((char) p[2]) == 'z' ){ dw |= (__vtran_int_z << 8 ); }
               break;
            }
            case 0x746E692A : // *int
            {
               pExtraFlags[0] = __vtran_extra_int;
               break;
            }
            case 0x6F6C662A : // *float
            {
               pExtraFlags[0] = __vtran_extra_float;
               break;
            }
            case 0x6F6F622A : // *bool
            {
               pExtraFlags[0] = __vtran_extra_bool;
               break;
            }
            case 0x7274732A : // *str
            {
               pExtraFlags[0] = __vtran_extra_str;
               break;
            }
            case 0x696F7473 : // stoi
            {
               dw |= __vtran_type_to_int;
               break;
            }
            case 0x626F7473 : // stob
            {
               dw |= __vtran_bool_10; // to BOOL
               break;
            }
            case 0x666F7473 : // stof
            {
               dw |= __vtran_type_to_double ;
               break;
            }
            case 0x3A733262 : // b2s: 10,yes,Y,on,true,T
            {
               dw |= __vtran_type_stringify;
               if( p[6] == '1' )
               {
                  dw |= __vtran_bool_10;
               }
               else if( p[6] == 'y' )
               {
                  if( p[7] == 'e' )
                  {
                     dw |= __vtran_bool_yes_no;
                  }
                  else
                  {
                     dw |= __vtran_bool_YN;
                  }
               }
               else if( p[6] == 'o' )
               {
                  dw |= __vtran_bool_on_off;
               }
               else if( p[6] == 't' )
               {
                  if( p[7] == 'r' )
                  {
                     dw |= __vtran_bool_true_false;
                  }
                  else
                  {
                     dw |= __vtran_bool_TF;
                  }
               }
               break;
            }
         }
      }
   }
   return dw;
}
// -----------------------------------------------------------------------------------------------------------------
void transformation_pack(XppParamList pl)
{
   TXppParamList xpp( pl,1);
   if( xpp[1]->CheckType( XPP_CHARACTER )  )
   {
      DWORD dw_flags = pack_string( xpp[1]->con() , 0,0);
      xpp[0]->PutDWord(dw_flags);
      return;
   }
   xpp[0]->Put( xpp[1]->con() );
   return;
}
// -----------------------------------------------------------------------------------------------------------------
void field_pack(XppParamList pl)
{
   TXppParamList xpp( pl,3);
   char bt[2]; xpp[1]->GetCL(bt,2); bt[1] = 0;
   DWORD dw_field = 0;
   field_st * fd = (field_st *) & dw_field;

   switch( bt[0] )
   {
      case 'c': ; case 'C': { fd->type = XPP_CHARACTER ;  fd->len = xpp[2]->GetWord(); break;}
      case 'm': ; case 'M': { fd->type = XPP_CHARACTER ;  fd->dec = 1; break;}
      case 'd': ; case 'D': { fd->type = XPP_DATE      ;  fd->len = 8; break;}
      case 'n': ; case 'N': { fd->type = XPP_NUMERIC   ;  fd->len = xpp[2]->GetWord(); fd->dec = LOBYTE(xpp[3]->GetLong()); break; }
      case 'l': ; case 'L': { fd->type = XPP_LOGICAL   ;  fd->len = 1; break;}
   }
   xpp[0]->PutDWord( dw_field);
}
// -----------------------------------------------------------------------------------------------------------------
void field_unpack(XppParamList pl)
{
   TXppParamList xpp( pl,3);
   char bt[2]; ZeroMemory( bt,sizeof(bt));
   DWORD dw_field =  xpp[1]->GetDWord();
   DWORD len = 0;
   DWORD dec = 0;
   bt[0] = unpack_field( (field_st *) & dw_field , len , dec );
   xpp[0]->PutStr(bt);
   xpp[2]->PutDWord(len);
   xpp[3]->PutDWord(dec);
}
// -----------------------------------------------------------------------------------------------------------------
char unpack_field( field_st* fd , DWORD & len , DWORD & dec )
{
   switch( fd->type )
   {
      case XPP_CHARACTER:
      {
         if( fd->dec )
         {
            len = 10;
            dec = 0;
            return 'M';
         }
         else
         {
            len = (DWORD) MAKELONG(fd->len,0);
            dec = 0;
            return 'C';
         }
      }
      case XPP_LOGICAL:
      {
         len = 1;
         dec = 0;
         return 'L';
      }
      case XPP_DATE:
      {
         len = 8;
         dec = 0;
         return 'D';
      }
      case XPP_NUMERIC:
      {
         len = (DWORD) MAKELONG(fd->len,0);
         dec = (DWORD) MAKELONG(MAKEWORD(fd->dec,0) ,0);
         return 'C';
      }
   }
   len = 0;
   dec = 0;
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
void field_table_pack(XppParamList pl)
{
   TXppParamList xpp( pl,1);

   if( xpp[1]->CheckType( XPP_ARRAY ) )
   {
      DWORD field_count = 0;
      ft_item_st *   f  = cona_field_table_pack( xpp[1]->con(),field_count);
      if( f )
      {
         xpp[0]->PutStrLen(_mk_ptr_(LPSTR,f,0) , field_count * sizeof(ft_item_st));
         _xfree((void*) f );
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
ft_item_st * cona_field_table_pack(ContainerHandle cona , DWORD & field_count )
{
   field_count = 0;
   if( _conCheckType(cona , XPP_ARRAY ) )
   {
      DWORD nfc = _conGetArrayLen(cona );
      ft_item_st * f = (ft_item_st * ) _xgrab(( nfc * sizeof(ft_item_st)) + 16 );
      DWORD n;
      for( n = 0; n < nfc; n++ )
      {
         _conArrayGetCL( cona , f[n].name , 11 , n+1, 1 , 0 );
         f[n].pad = 0;
         f[n].pos = n+1;
         char bt[2];
         _conArrayGetCL( cona ,bt,2, n+1, 2 , 0 );
         switch( bt[0] )
         {
            case 'c': ; case 'C': { f[n].type = XPP_CHARACTER ;  f[n].len = LOWORD(_conArrayGetNL(cona,n+1,3,0)); break;}
            case 'm': ; case 'M': { f[n].type = XPP_CHARACTER ;  f[n].dec = 1; break;}
            case 'd': ; case 'D': { f[n].type = XPP_DATE      ;  f[n].len = 8; break;}
            case 'n': ; case 'N':
            {
               f[n].type = XPP_NUMERIC   ;
               f[n].len = LOWORD( _conArrayGetNL(cona,n+1,3,0));
               f[n].dec = LOBYTE( _conArrayGetNL(cona,n+1,4,0));
               break;
            }
            case 'l': ; case 'L': { f[n].type = XPP_LOGICAL   ;  f[n].len = 1; break;}
         }
      }
      field_count = nfc;
      return f;
   }
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------

void process_string_and_put_return_value( TXbCPItem* result ,LPSTR & buffer , DWORD & buffer_size,DWORD & buffer_cb,DWORD dw_flags,field_st * fd,BOOL bStringify)
{

   if( !buffer )
   {
      if( (fd->type == 0) || ((fd->type == XPP_CHARACTER) && (fd->dec == 0)) )
      {
         result->PutStr("");
         return;
      }
      result->PutEmptyData((ULONG) fd->type,(LONG) fd->len , (LONG) fd->dec );
      return;
   }


   DWORD nFieldSize  = (DWORD) MAKELONG( fd->len , 0 );
   if( (fd->type == 0) || (  (fd->type==XPP_CHARACTER) && (fd->dec > 0)) )
   {
      nFieldSize = dw_flags & 0xFF;
   }
   if( fd->type & ( XPP_NUMERIC | XPP_DATE | XPP_LOGICAL ) )
   {
      dw_flags |= ( __vtran_type_ltrim | __vtran_type_rtrim ) ;
   }
   if( (fd->type == XPP_CHARACTER) && (fd->dec == 0) )
   {
      if( (buffer_size <= fd->len ) ||  (buffer_size <=  (dw_flags & 0xFF)) )
      {
         UINT nNewSize = (UINT) (MAKELONG( fd->len , 0 ) + 1);
         if( nNewSize <= (dw_flags & 0xFF)){ nNewSize = (dw_flags & 0xFF) +1; }
         buffer = (LPSTR) _xxgrow((void*) buffer , buffer_size , nNewSize );
         buffer_size = nNewSize;
      }
   }
   if( dw_flags & __vtran_type_case_upper ){ CharUpperBuffA(buffer,buffer_cb); }
   if( dw_flags & __vtran_type_case_lower ){ CharLowerBuffA(buffer,buffer_cb); }
   if( dw_flags & __vtran_type_ltrim ){ buffer_cb = ByteMapTable_LTrimEx(0,(LPBYTE) buffer, buffer_cb ); }
   if( dw_flags & __vtran_type_rtrim ){ buffer_cb = ByteMapTable_RTrimEx(0,(LPBYTE) buffer, buffer_cb ); }
   if( (dw_flags & __vtran_type_align_right) &&  nFieldSize && buffer_cb )
   {
      DWORD nd,ns;
      if( nFieldSize > buffer_cb )
      {
         nd = nFieldSize;
         ns = buffer_cb;
         while( nd && ns )
         {
            nd--; ns--;
            buffer[nd] = buffer[ns];
         }
         while( nd )
         {
            nd--;
            buffer[nd] = 0x20;
         }
      }
      else
      {
         if(nFieldSize < buffer_cb )
         {
            ns = buffer_cb - nFieldSize;
            for( nd = 0; ns < buffer_cb; ns++,nd++ )
            {
               buffer[nd] = buffer[ns];
            }
         }
      }
      buffer_cb = nFieldSize;
      buffer[buffer_cb] = 0;
   }
   if( dw_flags & __vtran_type_from_left   )
   {
      if(  (dw_flags & 0xFF) < buffer_cb )
      {
         buffer_cb = (dw_flags & 0xFF);
         buffer[buffer_cb] = 0;
      }
   }
   if( dw_flags & __vtran_type_from_right   )
   {
      if(  (dw_flags & 0xFF) < buffer_cb )
      {

         DWORD nd = 0;
         DWORD ns = buffer_cb - (dw_flags & 0xFF);
         for(; ns < buffer_cb; ns++,nd++ )
         {
            buffer[nd] = buffer[ns];
         }
         buffer[nd] = 0;
         buffer_cb  = nd;
      }
   }
   buffer[buffer_cb] = 0;
   if( bStringify )
   {
      fd->type = XPP_CHARACTER;
      fd->dec  = 0;
   }
   switch( fd->type )
   {
      case XPP_NUMERIC:
      {
         if( fd->dec)
         {
            double nd = atof(buffer);
            result->PutDoubleFormat( nd , (int) fd->len , (int) fd->dec );
         }
         else
         {
            LONG nl = atol(buffer);
            if( (nl < 0) && ( buffer[0] != '-') )
            {
               double nd = atof(buffer);
               result->PutDoubleFormat( nd , (int) fd->len , 0);
            }
            else
            {
               result->PutLong( nl );
            }
         }
         break;
      }
      case XPP_DATE:
      {
         result->PutDateString(buffer);
         break;
      }
      case XPP_LOGICAL:
      {
         BOOL b = (_bscan((LPBYTE) "Yy1Tt",5,(BYTE) buffer[0]) < 5)  ?  1 : 0 ;
         result->PutBool( b );
         break;
      }
      case XPP_CHARACTER:
      {
         if( fd->dec == 0 )
         {
            DWORD cb = ((DWORD) fd->len) & 0xFFFF;
            if( dw_flags & __vtran_type_align_left )
            {
               while( buffer_cb < cb )
               {
                  buffer[buffer_cb] = 0x20;
                  buffer_cb++;
                  buffer[buffer_cb] = 0;
               }
            }
            result->PutStrLen(buffer,buffer_cb );
            break;
         }
         // do not break to alow fall into default case if memo
      }
      default:  // no field or memo
      {
         result->PutStrLen(buffer,buffer_cb );
         break;
      }
   }
   _xfree( (void*) buffer );
   buffer = 0;
   buffer_size = 0;
   buffer_cb   = 0;
   return;
}
// -----------------------------------------------------------------------------------------------------------------
void transform_with_codeblock( TXbCPItem* result , ContainerHandle con_value, ContainerHandle con_block , field_st* fd)
{
   ContainerHandle con_f_type = _conPutC( NULLCONTAINER  ,  "" );
   ContainerHandle con_f_len  = _conPutNL( NULLCONTAINER ,  0  );
   ContainerHandle con_f_dec  = _conPutNL( NULLCONTAINER ,  0  );

   switch( fd->type )
   {
      case XPP_CHARACTER:
      {
         if( fd->dec )
         {
            _conPutC( con_f_type ,  "M" );
            _conPutNL( con_f_len , 10  );
         }
         else
         {
            _conPutC( con_f_type ,  "C" );
            _conPutNL( con_f_len , ((LONG) fd->len ) & 0xFFFF   );
         }
         break;
      }
      case XPP_LOGICAL:
      {
         _conPutC( con_f_type ,  "L" );
         _conPutNL( con_f_len ,  1  );
         break;
      }
      case XPP_DATE:
      {
         _conPutC( con_f_type ,  "D" );
         _conPutNL( con_f_len ,   8 );
         break;
      }
      case XPP_NUMERIC:
      {
         _conPutC( con_f_type ,  "N" );
         _conPutNL( con_f_len , ((LONG) fd->len ) & 0xFFFF   );
         _conPutNL( con_f_dec , ((LONG) fd->dec ) & 0xFF     );
         break;
      }
   }
   _conEvalB( result->con() , con_block , 4 , con_value , con_f_type , con_f_len , con_f_dec );
   _conReleaseM( con_f_type , con_f_len , con_f_dec , 0 );
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR get_string(  TXbCPItem* item , DWORD & buffer_size , DWORD & buffer_cb ,  DWORD dw_flags , field_st * fd , BOOL bStringify)
{
   LPSTR buffer = 0;
   DWORD nnn = (((LONG) fd->len) & 0xFFFF) + (((LONG) fd->dec) & 0xFF) + 1;
   DWORD len = (dw_flags & 0xFF );
   DWORD dec = ((dw_flags >> 8) & 0xFF );
   switch( item->GetType() & 0xFF )
   {
      case XPP_CHARACTER:
      {
         buffer_size = item->con_size();
         if( buffer_size  < nnn ){ buffer_size  = nnn; }
         buffer_size += 1;
         buffer = (LPSTR) _xgrab( buffer_size );
         buffer_cb   = item->GetCL( buffer,buffer_size );
         return buffer;
      }
      case XPP_DATE:
      {
         buffer_size = 16;
         if( buffer_size  < nnn ){ buffer_size  = nnn; }
         buffer_size += 1;
         buffer = (LPSTR) _xgrab( buffer_size );
         _conGetDS( item->con() ,buffer );
         buffer_cb = _xstrlen(buffer);
         return buffer;
      }
      case XPP_NUMERIC:
      {
         if( dw_flags & __vtran_type_from_double )
         {
            if( nnn < (len+dec+1) ){ nnn = (len+dec+1); }
            if( nnn < 128 ){ nnn = 128; }
            buffer_size = nnn;
            buffer = (LPSTR) _xgrab( buffer_size );
            char format[16]; ZeroMemory(format,sizeof(format));
            if( item->CheckType(_xpp_DOUBLE) )
            {
               double nd = item->GetDouble();
               wsprintf(format,"%%.%if" , dec);
               buffer_cb = sprintf(buffer,format, nd);
               return buffer;
            }
            LONG nl = item->GetLong();
            wsprintf(format,"%%i.%%0%i.%ii" , dec , dec);
            buffer_cb = sprintf(buffer,format, nl , 0);
            return buffer;
         }
         if( dw_flags & __vtran_type_from_int )
         {
            buffer_size = 128;
            if( buffer_size  < nnn ){ buffer_size  = nnn; }
            buffer = (LPSTR) _xgrab( buffer_size );
            LONG nl = item->GetLong();
            char format[16]; ZeroMemory(format,sizeof(format));
            if( (dec == __vtran_int_z) && len )
            {
               wsprintf(format,"%%0%i.%i%%i" , len ,  len );
               buffer_cb = sprintf(buffer,format, nl);
            }
            else
            {
               buffer_cb = sprintf(buffer,"%i", nl );
            }
            return buffer;
         }
         buffer = _conCallLpstr("str" , item->con() );
         buffer_cb = _xstrlen(buffer);
         buffer_size =  buffer_cb + 1;
         return buffer;
      }
      case XPP_LOGICAL:
      {
         buffer_size = 16;
         buffer = (LPSTR) _xgrab( buffer_size );

         dec = 0;
         if( bStringify )
         {
            dec = dw_flags | 7;
         }
         if(  item->GetBool() )
         {
            switch( dec )
            {
               case __vtran_bool_yes_no       : { _xstrcpy(buffer,"Yes");  return buffer; }
               case __vtran_bool_YN           : { _xstrcpy(buffer,"Y");    return buffer; }
               case __vtran_bool_on_off       : { _xstrcpy(buffer,"On");   return buffer; }
               case __vtran_bool_true_false   : { _xstrcpy(buffer,"True"); return buffer; }
               case __vtran_bool_TF           : { _xstrcpy(buffer,"T");    return buffer; }
            }
            _xstrcpy(buffer,"1");
            return buffer;
         }
         else
         {
            switch( dec )
            {
               case __vtran_bool_yes_no       : { _xstrcpy(buffer,"No");    return buffer; }
               case __vtran_bool_YN           : { _xstrcpy(buffer,"N");     return buffer; }
               case __vtran_bool_on_off       : { _xstrcpy(buffer,"Off");   return buffer; }
               case __vtran_bool_true_false   : { _xstrcpy(buffer,"False"); return buffer; }
               case __vtran_bool_TF           : { _xstrcpy(buffer,"F");     return buffer; }
            }
            _xstrcpy(buffer,"0");
            return buffer;
         }
      }
   }
   buffer_size = 0;
   buffer_cb   = 0;
   return 0;
}

// -----------------------------------------------------------------------------------------------------------------
void transformation_play(XppParamList pl)
{
   TXppParamList xpp( pl,3);
   DWORD dw_flags = 0;
   DWORD dw_field = xpp[3]->GetDWord() & (~( __vtran_readonly ));
   field_st * fd = (field_st *) & dw_field;
   BOOL bStringify = FALSE;
   DWORD dw_extra = 0;



   if( xpp[2]->CheckType(XPP_BLOCK) )
   {
      transform_with_codeblock(xpp[0],xpp[1]->con(),xpp[2]->con(),fd);
      return;
   }
   if( xpp[2]->CheckType(XPP_CHARACTER) )
   {
      dw_flags = pack_string( xpp[2]->con() , 0, &dw_extra);
   }
   else
   {
      dw_flags = xpp[2]->GetDWord();
   }

   if( (dw_flags & __vtran_type_stringify) == __vtran_type_stringify)
   {
      dw_flags =  dw_flags & (~__vtran_type_stringify);
      bStringify = TRUE;
   }


   if( dw_flags == __vtran_type_field_x )
   {
      if( !xpp[1]->CheckType( LOBYTE(fd->type) ) )
      {
         xpp[0]->Put(NULLCONTAINER);
         return;
      }
      switch( fd->type )
      {
         case XPP_CHARACTER:
         {
            if( fd->dec )
            {
               dw_flags = 0;
               break;
            }
            dw_flags = __vtran_type_align_left;
            break;
         }
         case XPP_NUMERIC:
         {
            if( fd->dec )
            {
               xpp[0]->PutDoubleFormat(xpp[1]->GetDouble(), LOWORD(fd->len) ,LOBYTE(fd->dec ) );
               return;
            }
            dw_flags = 0;
            break;
         }
         default:
         {
            dw_flags = 0;
            break;
         }
      }
   }

   if( dw_extra )
   {
      switch( dw_extra )
      {
         case __vtran_extra_str :
         {
            break;
         }
         case __vtran_extra_int :
         {
            break;
         }
         case __vtran_extra_float :
         {
            break;
         }
         case __vtran_extra_bool :
         {
            break;
         }
      }
   }


   if( !dw_flags )
   {  // no transformation
      xpp[0]->Put( xpp[1]->con() );
      return;
   }

   dw_field = xpp[3]->GetDWord();




   if(
        (dw_flags < __vtran_type_char_max ) ||
        ( ((dw_flags & __vtran_type_to_int ) || (dw_flags & __vtran_type_to_double)) && ( xpp[1]->GetType() & XPP_CHARACTER) )
   )
   {
      DWORD buffer_cb   = 0;
      DWORD buffer_size  = 0;
      LPSTR buffer      = get_string( xpp[1],buffer_size,buffer_cb,dw_flags , fd , bStringify );
      process_string_and_put_return_value( xpp[0],buffer,buffer_size,buffer_cb,dw_flags , fd,bStringify);
      return;
   }


   if( dw_flags & __vtran_type_stod )
   {
      if( (fd->type == XPP_DATE) || ( fd->type == 0) )
      {
         switch( xpp[1]->GetType() & 0xFF )
         {
            case XPP_DATE:
            {
               xpp[0]->Put( xpp[1]->con() );
               return;
            }
            case XPP_CHARACTER:
            {
               char sz[16]; ZeroMemory(sz,sizeof(sz));
               xpp[1]->GetCL(sz,15);
               xpp[0]->PutDateString(sz);
               return;
            }
            case XPP_NUMERIC:
            {
               FILETIME ft; ZeroMemory(&ft,sizeof(ft));
               ft64_SetUnixTime( &ft, xpp[1]->GetDWord() );
               LPSTR p = ft64_GetTs(&ft,"%04.4hu%02.2hu%02.2hu");
               xpp[0]->PutDateString(p);
               _xfree((void*) p );
               return;
            }
         }
         xpp[0]->PutDateString("");
         return;
      }
      xpp[0]->PutEmptyData((ULONG) fd->type , (LONG) fd->len , (LONG) fd->dec );
      return;
   }


   if( (dw_flags & __vtran_type_to_int ) || (  (dw_flags & __vtran_type_to_double) && ( xpp[1]->GetType() & (XPP_DATE|XPP_LOGICAL)) ) )
   {
      if( (fd->type == XPP_NUMERIC) || ( fd->type == 0) )
      {
         switch( xpp[1]->GetType() & 0xFF )
         {
            case XPP_DATE:
            {
               FILETIME ft; ZeroMemory(&ft,sizeof(ft));
               char sz[32]; ZeroMemory(sz,sizeof(sz));
               xpp[1]->GetDateString(sz);
               ft64_SetTs(&ft,sz,0);
               xpp[0]->PutDWord(ft64_GetUnixTime( &ft));
               return;
            }
            case XPP_CHARACTER:
            {
               int nInt = 0;
               char sz[64]; ZeroMemory(sz,sizeof(sz));
               UINT cb = (UINT) xpp[1]->GetCL(sz,sizeof(sz));
               if( cb )
               {
                  UINT n;
                  for( n = 0; n < cb; n++ ){if( (sz[n] == '.' ) || (sz[n] == '|' ) || (sz[n] == ',' ) ){sz[n] = 0;}}
                  nInt = atoi(sz);
               }
               xpp[1]->PutLong(nInt);
               return;
            }
            case XPP_NUMERIC:
            {
               xpp[0]->PutLong( xpp[1]->GetLong() );
               return;
            }
            case XPP_LOGICAL:
            {
               xpp[0]->PutLong( (xpp[1]->GetBool() ? 1 : 0 ) );
               return;
            }
         }
         xpp[0]->PutLong(0);
         return;
      }
      xpp[0]->PutEmptyData((ULONG) fd->type , (LONG) fd->len , (LONG) fd->dec );
      return;
   }
   if( dw_flags & __vtran_type_to_double )
   {
      if( (fd->type == XPP_NUMERIC) || ( fd->type == 0) )
      {
         double nd = 0.00;
         switch( xpp[1]->GetType() & 0xFF )
         {
            case XPP_CHARACTER:
            {
               char sz[64]; ZeroMemory(sz,sizeof(sz));
               UINT cb = (UINT) xpp[1]->GetCL(sz,sizeof(sz));
               if( cb ){nd = atof(sz);}
               break;
            }
            case XPP_NUMERIC:
            {
               nd = xpp[1]->GetDouble();
               break;
            }
         }
         if( fd->type )
         {
            xpp[0]->PutDoubleFormat(nd,(int) fd->len,(int) fd->dec );
         }
         else
         {
            xpp[0]->PutDouble(nd);
         }
         return;
      }
      xpp[0]->PutEmptyData((ULONG) fd->type , (LONG) fd->len , (LONG) fd->dec );
      return;
   }
   xpp[0]->Put( xpp[1]->con() );
   return;
}
// -----------------------------------------------------------------------------------------------------------------
static void parse_property_table_json_string__step(LPBYTE p, ContainerHandle cono )
{

   DWORD cb = _xstrlen((LPSTR) p);
   if( cb < 12){ return;}
   p++; cb--; p[cb] = 0; cb--; // remove " at both lr sides
   LPSTR pPropName = (LPSTR) p;
   DWORD n  = _bscan(p,cb,0x22);
   if( (n < 1) ||  (cb < (n+3))  ){ return; }
   if( p[n]   != 0x22 ){ return; }
   p[n] = 0;
   if( p[n+1] != 0x2C ){ return; }
   if( p[n+2] != 0x22 ){ return; }
   p  = _mk_ptr_( LPBYTE,p,n+3);
   cb -= ( n + 3) ;

   LPSTR pFieldName = (LPSTR) p;
   n  = _bscan(p,cb,0x22);
   if( (n < 1) ||  (cb < (n+3))  ){ return; }
   p[n] = 0;
   if( p[n+1] != 0x2C ){ return; }
   if( p[n+2] != 0x22 ){ return; }
   p  = _mk_ptr_( LPBYTE,p,n+3);
   cb -= ( n + 3) ;

   LPSTR pOnRead = (LPSTR) p;
   n  = _bscan(p,cb,0x22);
   if( cb < (n+3)  ){ return; }
   p[n] = 0;
   if( p[n+1] != 0x2C ){ return; }
   if( p[n+2] != 0x22 ){ return; }
   p  = _mk_ptr_( LPBYTE,p,n+3);
   cb -= ( n + 3) ;

   LPSTR pOnWrite = (LPSTR) p;
   p[cb] = 0;

   ContainerHandle con_item = _conNewObj("_OT4XB_EXPANDO_" , 0 );
   _conMCallVoid(con_item,"set_prop", "cName" ,  pPropName  );
   _conMCallVoid(con_item,"set_prop", "cField"    ,  pFieldName );
   _conMCallVoid(con_item,"set_prop", "r_vtran"   ,  pOnRead    );
   _conMCallVoid(con_item,"set_prop", "r_vtran_dw" ,   pack_string(0,pOnRead,0) );
   _conMCallVoid(con_item,"set_prop", "w_vtran"   ,  pOnWrite   );
   _conMCallVoid(con_item,"set_prop", "w_vtran_dw" ,   pack_string(0,pOnWrite,0) );
   _conRelease( _conMCallConNR( "set_prop", cono , 2 , _conPutC( 0,pPropName) , con_item ) );
}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle parse_property_table_json_string( LPBYTE psz, DWORD cb )
{
   if( cb == (DWORD) -1 )
   {
      cb = 0;
      if( psz ) { cb = _xstrlen((LPSTR) psz); }
   }
   ContainerHandle con_table = _conNewObj("_OT4XB_EXPANDO_" , 0 );
   if( psz && cb )
   {
      BYTE cht[256]; ZeroMemory(cht,sizeof(cht)); ByteMapTable_FillSeq(cht,(LPWORD) "AZaz09__@@\"\",,]]::++--..**",13);
      cb = (DWORD) ByteMapTable_RemoveUnsafe(cht,psz,cb) - 2; // remove the trailing ]]
      UINT rl;
      if( ((int) cb ) < 0 ){ cb = 0;}
      while( cb )
      {
         if( psz[0] == (BYTE) ',' ){ psz++; cb--; }
         if(!cb){ break;}
         rl = _bscan(psz,cb,']');
         psz[rl] = 0; // psz will be zero terminated
         if( rl == 0){ psz++;cb--; continue;}

         parse_property_table_json_string__step(psz, con_table );
         cb = ( (cb == rl) ? 0 : (cb-(rl+1)) );
         psz += rl+1;
      }
   }
   return con_table;
}
// -------------------------------------------------------------------
void __cdecl vtran_parse_property_table_array( XppParamList pl )
{


      TXppParamList xpp( pl,1);
      _conPutNewObj( xpp[0]->con() , "_OT4XB_EXPANDO_" , 0 );
      if(  xpp[1]->CheckType(XPP_ARRAY)  ) 
      {
         DWORD count = xpp[1]->con_size();
         DWORD pos;
         for( pos = 1; pos <= count; pos++ )
         {
           ContainerHandle con_item            = _conNewObj("_OT4XB_EXPANDO_" , 0 );
           ContainerHandle con_prop_name       = _conNew(0); 
           ContainerHandle con_field_name      = _conNew(0); 
           ContainerHandle con_transform_read  = _conNew(0); 
           ContainerHandle con_transform_write = _conNew(0); 

           _conArrayGet( xpp[1]->con() , con_prop_name        , pos , 1 , 0 );
           _conArrayGet( xpp[1]->con() , con_field_name       , pos , 2 , 0 );
           _conArrayGet( xpp[1]->con() , con_transform_read   , pos , 3 , 0 );
           _conArrayGet( xpp[1]->con() , con_transform_write  , pos , 4 , 0 );
           
           _conSetMember(con_item , "cName"   ,   con_prop_name       );
           _conSetMember(con_item , "cField"  ,   con_field_name      );
           _conSetMember(con_item , "r_vtran" ,   con_transform_read  );
           _conSetMember(con_item , "w_vtran" ,   con_transform_write );
           
           _conSetNLMember( con_item , "r_vtran_dw" ,  (LONG)  pack_string(con_transform_read  , 0 , 0 ) );
           _conSetNLMember( con_item , "w_vtran_dw" ,  (LONG)  pack_string(con_transform_write , 0 , 0 ) );
           
           DWORD cb = 0;
           char prop_name[256]; 
           ZeroMemory( prop_name , sizeof( prop_name ) ); 
           _conGetCL( con_prop_name , &cb , prop_name , sizeof( prop_name ) - 1 );
           _conSetMember( xpp[0]->con() ,  prop_name , con_item );

              
           _conRelease( con_item            ); con_item             = 0;
           _conRelease( con_prop_name       ); con_prop_name        = 0;
           _conRelease( con_field_name      ); con_field_name       = 0;
           _conRelease( con_transform_read  ); con_transform_read   = 0;
           _conRelease( con_transform_write ); con_transform_write  = 0;
         }
      }
}
// -----------------------------------------------------------------------------------------------------------------
void create_class_vtran( XppParamList pl)
{
   ContainerHandle conco = _conClsObj("__VTRAN");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;pc->ClassName("__VTRAN");
      pc->EXPORTED();
      pc->Var("__m__33A16CAE8F4D409AA7B272EA1E593F16" );
      // -----

      // -----
      pc->ClassMethod_cbbs( "transformation_pack"   , "{|s,trf | XbFpCall( 0x%08.8X , trf ) } "                           , transformation_pack );
      pc->ClassMethod_cbbs( "transformation_play"   , "{|s,val,trf,fld_def| XbFpCall( 0x%08.8X , val,trf,fld_def) } "     , transformation_play );
      pc->ClassMethod_cbbs( "field_pack"            , "{|s,cType,nLen,nDec| XbFpCall( 0x%08.8X ,cType,nLen,nDec) } "      , field_pack );
      pc->ClassMethod_cbbs( "field_unpack"          , "{|s,dw,nLen,nDec| XbFpCall( 0x%08.8X , dw,@nLen,@nDec) } "         , field_unpack );
      pc->ClassMethod_cbbs( "field_table_pack"      , "{|s,aDbStruct| XbFpCall( 0x%08.8X , aDbStruct) } "                 , field_table_pack );
      // -----
      pc->ClassMethod_cbbs( "workarea_setget"       , "{|s,wa,cTrTable,dwFlags| XbFpCall(0x%08.8X):New(wa,cTrTable,dwFlags)} " ,
                                                      wa_ns::create_class_vtran_workarea );
      // -----
      pc->ClassMethod_cbbs( "buffer_setget"       , "{|s,aFields,ttr,flags,buffer| XbFpCall(0x%08.8X):New(aFields,ttr,flags,buffer)} " ,
                                                      buffer_ns::create_class_vtran_buffer);
      // -----

      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER )
      {
         _ret(pl);
         return;
      }
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE(wa_ns)
   //----------------------------------------------------------------------------------------------------------------------
   void init_instance( XppParamList pl) // init_instance(wa,ttr,flags) -> data_expando
   {
      TXppParamList xpp( pl,3);
      DWORD dw_init_instance_flags = xpp[3]->GetDWord();
      int old_wa = 0;
      int wa = 0;
      ContainerHandle data = _conPutNewObj( xpp[0]->con() , "_OT4XB_EXPANDO_" , 0 );
      _conRelease( _conMCallConNR("set_prop", data , 2 , _conPutC( 0,"dw_instance_flags") , _conPutNL(0,dw_init_instance_flags)));
      _conRelease( _conMCallConNR("set_prop", data , 2 , _conPutC( 0,"method_table") , _conNewObj("_OT4XB_EXPANDO_" , 0 ) ));

      ContainerHandle con = 0;

      DWORD dw = 0;
      LPBYTE p = (LPBYTE) xpp[2]->LockStr(&dw);
      con = parse_property_table_json_string( p,dw);

      if( !con)
      {
         con = _conNewObj( "_OT4XB_EXPANDO_" , 0 );
      }
      _conRelease( _conMCallConNR("set_prop", data , 2 , _conPutC( 0,"prop_table") , con)); con = 0;
      if( xpp[1]->CheckType(XPP_CHARACTER) )
      {
         if( _conSetCWArea(xpp[1]->str(),&old_wa) == 0 )
         {
            wa = _conCallLong("SELECT");

         }
      }
      else if( xpp[1]->CheckType(XPP_NUMERIC) )
      {
         if( _conSetIWArea(xpp[1]->GetLong(),&old_wa) == 0 )
         {
            wa = _conCallLong("SELECT");
         }
      }
      else
      {
         wa = _conCallLong("SELECT");
      }
      if( wa )
      {
         _conRelease( _conMCallConNR("set_prop", data , 2 , _conPutC( 0,"cAlias") , _conCallCon("ALIAS")));


         ContainerHandle cona_structure  =  _conCallCon("DBSTRUCT");
         ContainerHandle con_field_table_string = _conNew(0);
         ContainerHandle con_field_table =  _conNewObj("_OT4XB_EXPANDO_" , 0 );
         DWORD field_count = 0;
         ft_item_st *   f  = cona_field_table_pack( cona_structure,field_count);
         if( f )
         {
            _conPutCL(con_field_table_string,_mk_ptr_(LPSTR,f,0),field_count * sizeof(ft_item_st));

            DWORD n;
            for( n = 0; n <  field_count; n++ )
            {
               DWORD fcb = 0; while(f[n].name[fcb] && (f[n].name[fcb] != 0x20)){ fcb++;}
               _conRelease( _conMCallConNR("set_prop", con_field_table , 2 ,_conPutCL(0,f[n].name,fcb),_conPutCL(0,_mk_ptr_(LPSTR,&f[n],0),sizeof(ft_item_st))));
            }
            _xfree((void*) f );
         }
         _conRelease( _conMCallConNR("set_prop", data , 2 , _conPutC( 0,"field_table_string") ,con_field_table_string )); con_field_table_string = 0;
         _conRelease( _conMCallConNR("set_prop", data , 2 , _conPutC( 0,"field_table") ,con_field_table)); con_field_table = 0;
         _conRelease( _conMCallConNR("set_prop", data , 2 , _conPutC( 0,"field_count") ,_conPutNL(0,field_count)));
         _conRelease( _conMCallConNR("set_prop", data , 2 , _conPutC( 0,"aStruct") ,cona_structure )); cona_structure = 0;

      }
      if( old_wa )
      {
         _conSetIWArea(old_wa,&wa);
      }
   }

   //----------------------------------------------------------------------------------------------------------------------
   TXbGenError * get_key_info( ContainerHandle data , char k[256] , ft_item_st * field , DWORD * r_vtran_pdw , DWORD * w_vtran_pdw , char workarea_name[256] )
   {
      DWORD cb = 0;
      ZeroMemory(workarea_name,sizeof(workarea_name));
      ZeroMemory(field,sizeof(ft_item_st));
      if( r_vtran_pdw ){ r_vtran_pdw[0] = 0; }
      if( w_vtran_pdw ){ w_vtran_pdw[0] = 0; }

      if(!k[0])
      {
         return new TXbGenError( -1, "vtran_workarea::var::get_key_info","key not provided");
      }

      ContainerHandle alias = _conMCallCon( data , "get_prop" , "cAlias" );
      _conGetCL(alias,&cb,workarea_name,sizeof(workarea_name));
      _conRelease(alias);alias = 0;
      if( !cb)
      {
          return new TXbGenError( -1, "vtran_workarea::var::get_key_info","ALIAS property not initializaed");
      }

      ContainerHandle field_table = _conMCallCon( data , "get_prop" , "field_table" );
      if( !_conCheckType( field_table , XPP_OBJECT) )
      {
         _conRelease(field_table);
         return new TXbGenError( -1, "vtran_workarea::var_access","field table not found");
      }

      ContainerHandle prop_list = _conMCallCon( data , "get_prop" , "prop_table" );
      ContainerHandle prop      = 0;
      if( _conCheckType( prop_list , XPP_OBJECT) )
      {
         prop = _conMCallCon( prop_list , "get_prop" , k );
         if( ! _conCheckType( prop , XPP_OBJECT) )
         {
            _conRelease(prop);
            prop = 0;
         }
      }
      _conRelease(prop_list); prop_list = 0;
      if( prop  )
      {
          if( r_vtran_pdw ){ r_vtran_pdw[0] = (DWORD) _conMCallLong(prop,"get_prop","r_vtran_dw"); }
          if( w_vtran_pdw ){ w_vtran_pdw[0] = (DWORD) _conMCallLong(prop,"get_prop","w_vtran_dw"); }
         ContainerHandle conField = _conMCallCon(prop,"get_prop","cField");
         if( _conCheckType( conField , XPP_CHARACTER ) )
         {
            conField = _conMCallConNR("get_prop", field_table ,1,conField);
            cb = 0;
            if( _conGetCL(conField,&cb,_mk_ptr_(LPSTR,field,0),sizeof(ft_item_st) )){ cb = 0; }
            if( cb != sizeof(ft_item_st) ){ ZeroMemory(field,sizeof(ft_item_st)); }
         }
         _conRelease(conField);conField = 0;
         _conRelease(prop); prop = 0;
      }
      if( field->pos == 0 )
      {
         ContainerHandle conField = _conMCallConNR("get_prop", field_table ,1,_conPutC(0,k) );
         cb = 0;
         if( _conGetCL(conField,&cb,_mk_ptr_(LPSTR,field,0),sizeof(ft_item_st) )){ cb = 0; }
         if( cb != sizeof(ft_item_st) ){ ZeroMemory(field,sizeof(ft_item_st)); }
         _conRelease(conField); conField = 0;
      }
      return 0;
   }
   // ---------------------------------------------------------------------------------------------------------------------
   void var_access( XppParamList pl)
   {
      TXppParamList xpp( pl,3);

      char key[256]; ZeroMemory(key,sizeof(key)); xpp[3]->GetCL(key,sizeof(key)-1);
      TXbGenError * e = 0;
      ft_item_st  field; ZeroMemory(&field,sizeof(field));
      DWORD  dwTran = 0;
      char workarea_name[256];


      e = get_key_info(xpp[2]->con(),key,&field,&dwTran,0,workarea_name);
      if( e ){ goto launch_error; }

      if( field.pos )
      {
         ContainerHandle con_value = _conMCallConNR("workarea_get_field_value_by_pos",xpp[1]->con(),1,_conPutNL( 0,field.pos));
         if( !con_value)
         {
            e = new TXbGenError( 26 , key,"error retrieving field");
            goto launch_error;
         }

         if( dwTran )
         {
            ContainerHandle pcon[4];
            pcon[0] = _conPutNL( 0 , (DWORD) transformation_play  );
            pcon[1] = _conNew(con_value);
            pcon[2] = _conPutNL(0,dwTran);
            pcon[3] = _conPutNL(0, _mk_ptr_(LPDWORD,&field,0)[0]  );

            con_value = _conNew(0);

            _conCallPa(con_value,"XbFpCall",4,pcon);
            _conRelease( pcon[0]);_conRelease( pcon[1]);_conRelease( pcon[2]);_conRelease( pcon[3]);
         }

         xpp[0]->Put( con_value );

         _conRelease( con_value ); con_value = 0;

      }
      else
      {
         e = new TXbGenError( 26 , key,"field not exist");
         goto launch_error;
      }

      launch_error: if( e ) { e->Launch();  delete e; e = 0; }

   }
   //----------------------------------------------------------------------------------------------------------------------

   void var_assign( XppParamList pl)
   {
      TXppParamList xpp( pl,4);

      char key[256]; ZeroMemory(key,sizeof(key)); xpp[3]->GetCL(key,sizeof(key)-1);
      TXbGenError * e = 0;
      ft_item_st  field; ZeroMemory(&field,sizeof(field));
      DWORD  dwTran = 0;
      char workarea_name[256];


      e = get_key_info(xpp[2]->con(),key,&field,0,&dwTran,workarea_name);
      if( e ){ goto launch_error; }
      //dwTran |= __vtran_type_field_x;

      if( field.pos )
      {
         ContainerHandle con_value = _conNew( xpp[4]->con() );
         if( dwTran )
         {
            ContainerHandle pcon[4];
            pcon[0] = _conPutNL( 0 , (DWORD) transformation_play  );
            pcon[1] = _conNew(con_value);
            pcon[2] = _conPutNL(0,dwTran);
            pcon[3] = _conPutNL(0, _mk_ptr_(LPDWORD,&field,0)[0]  );

            con_value = _conNew(0);

            _conCallPa(con_value,"XbFpCall",4,pcon);
            _conRelease( pcon[0]);_conRelease( pcon[1]);_conRelease( pcon[2]);_conRelease( pcon[3]);
         }


         _conRelease( _conMCallConNR("workarea_put_field_value_by_pos",xpp[1]->con(),2,_conPutNL( 0,field.pos) , con_value));
         con_value = 0;
      }
      else
      {
         e = new TXbGenError( 26 , key,"field not exist");
         goto launch_error;
      }

      launch_error: if( e ) { e->Launch();  delete e; e = 0; }

   }
   //----------------------------------------------------------------------------------------------------------------------
   // e1 = s:data() ,e2 = codeblock_if_any  , e3 = nTargetWorkArea
   static void generic_method( TXbClsParams * px)
   {
      px->PutReturn();

      int nTargetWorkArea  = px->GetExtraLong(3);
      if( nTargetWorkArea < 1 )
      {
         px->GenError();
         px->SetErrorSubSystem("ot4xb");
         px->SetErrorOperation("vtran_workarea::noMethod");
         px->SetErrorDescription( "Invalid WorkArea" );
         px->SetErrorGenCode(-1);
         return;
      }

      int nOldWorkArea = 0;

      if( _conSetIWArea(nTargetWorkArea, &nOldWorkArea ) )
      {
            px->GenError();
            px->SetErrorSubSystem("ot4xb");
            px->SetErrorOperation("vtran_workarea::noMethod");
            px->SetErrorDescription( "Invalid WorkArea" );
            px->SetErrorGenCode(-1);
            return;
      }

      DWORD np = px->PCount(); if( np > 20){ np = 20; }
      ContainerHandle pcon[24]; ZeroMemory( pcon , sizeof(pcon) );
      DWORD n;

      for( n = 0; n < np; n++ )
      {
         pcon[n] = px->GetParam(n+1);
      }
      if( px->CheckExtraType(2,XPP_BLOCK) )
      {
         pcon[0] = px->GetSelf();
         _conEvalBa( px->GetReturn() , px->GetExtra(2) ,np , pcon );
         if( nOldWorkArea ){ int i = 0; _conSetIWArea(nOldWorkArea, &i); }
         return;
      }
      char key[256]; ZeroMemory(key,sizeof(key)); px->ParamGetCL(1,key,sizeof(key)-1);
      if( px->CheckExtraType(1,XPP_OBJECT) )
      {
         DWORD dw_instance_flags = _conMCallLong( px->GetExtra(1) ,"get_prop" , "dw_instance_flags" );
         if( dw_instance_flags & __vtran_instance_flag_allow_any_function )
         {

             if( _ot4xb_find_sym_( key) )
             {
                _conCallPa(px->GetReturn(),key,np-1,&(pcon[1]));
                if( nOldWorkArea ){ int i = 0; _conSetIWArea(nOldWorkArea, &i); }
                return;
             }
          }
      }
      if( nOldWorkArea ){ int i = 0; _conSetIWArea(nOldWorkArea, &i); }

      px->GenError();
      px->SetErrorSubSystem("ot4xb");
      px->SetErrorOperation("vtran_workarea::noMethod");
      px->SetErrorDescription( "No method with this name" );
      px->SetErrorArgs();
      px->SetErrorGenCode(-1);

   }

   //----------------------------------------------------------------------------------------------------------------------
   void create_class_vtran_workarea( XppParamList pl)
   {
      ContainerHandle conco = _conClsObj("__VTRAN__WORKAREA");
      if( conco == NULLCONTAINER )
      {
         TXbClass * pc = new TXbClass;pc->ClassName("__VTRAN__WORKAREA");
         pc->EXPORTED();
         pc->Var("m_data_5690d701603d4c05849d8f605e91f1f0"  );
         // -----
         pc->Method_cbbs("GetNoIVar" , "{|s,k|  XbFpCall(0x%08.8X,s,s:m_data_5690d701603d4c05849d8f605e91f1f0,k)}",var_access );
         pc->Method_cbbs("SetNoIVar" , "{|s,k,v|XbFpCall(0x%08.8X,s,s:m_data_5690d701603d4c05849d8f605e91f1f0,k,v)}",var_assign);
         pc->Method("noMethod"       , generic_method , 16 ,
                      ",s:m_data_5690d701603d4c05849d8f605e91f1f0"
                      ",s:m_data_5690d701603d4c05849d8f605e91f1f0:method_table:get_prop(p1)"
                      ",select(__vstr(s:m_data_5690d701603d4c05849d8f605e91f1f0:cAlias,'1234567890'))" );


         pc->Method_cbbs("init"      , "{|s,wa,ttr,flags| s:m_data_5690d701603d4c05849d8f605e91f1f0 := XbFpCall(0x%08.8X,wa,ttr,flags) , s }",init_instance);
         // -----
         pc->MethodCB("json_escape_self", "{|s,pStack| s:m_data_5690d701603d4c05849d8f605e91f1f0:json_escape_self()}");
         pc->MethodCB("data" , "{|s,k,v|s:m_data_5690d701603d4c05849d8f605e91f1f0}");
         pc->MethodCB("cAlias" , "{|s|s:m_data_5690d701603d4c05849d8f605e91f1f0:cAlias}");
         pc->MethodCB("workarea_get_field_value_by_pos" , "{|s,n|   ( s:m_data_5690d701603d4c05849d8f605e91f1f0:cAlias )->( FieldGet(n) )}");
         pc->MethodCB("workarea_put_field_value_by_pos" , "{|s,n,v| ( s:m_data_5690d701603d4c05849d8f605e91f1f0:cAlias )->( FieldPut(n,v) )}");
         // -----
         conco = pc->Create();
         delete pc;
         if( conco == NULLCONTAINER )
         {
            _ret(pl);
            return;
         }
      }
      _conReturn(pl,conco);
      _conRelease(conco);
   }
   //----------------------------------------------------------------------------------------------------------------------
END_NAMESPACE()
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE(buffer_ns)
   //----------------------------------------------------------------------------------------------------------------------
      // e1 = dw_instance_flags ,e2 = codeblock_if_any
   static void generic_method( TXbClsParams * px)
   {
      px->PutReturn();

      DWORD np = px->PCount(); if( np > 20){ np = 20; }
      ContainerHandle pcon[24]; ZeroMemory( pcon , sizeof(pcon) );
      DWORD n;

      for( n = 0; n < np; n++ )
      {
         pcon[n] = px->GetParam(n+1);
      }
      if( px->CheckExtraType(2,XPP_BLOCK) )
      {
         pcon[0] = px->GetSelf();
         _conEvalBa( px->GetReturn() , px->GetExtra(2) ,np , pcon );
         return;
      }

      px->GenError();
      px->SetErrorSubSystem("ot4xb");
      px->SetErrorOperation("vtran_buffer::noMethod");
      px->SetErrorDescription( "No method with this name" );
      px->SetErrorArgs();
      px->SetErrorGenCode(-1);

   }
   //----------------------------------------------------------------------------------------------------------------------
   void __create_field_table_string__( XppParamList pl) // aFields
   {
      TXppParamList xpp( pl,1);
      xpp[0]->PutStr("");
      if(  xpp[1]->CheckType(XPP_ARRAY)  ) 
      {
         DWORD field_count = 0;
         ft_item_st *   f  = cona_field_table_pack( xpp[1]->con() ,field_count);
         if( f )
         {
            xpp[0]->PutStrLen( _mk_ptr_(LPSTR,f,0),field_count * sizeof(ft_item_st) );
         }
      }
   }
   //----------------------------------------------------------------------------------------------------------------------
   void __create_field_table_from_table_string__( XppParamList pl)  // fts
   {
      TXppParamList xpp( pl,2);
      _conPutNewObj( xpp[0]->con() , "_OT4XB_EXPANDO_" , 0 );
      if(  xpp[1]->CheckType(XPP_CHARACTER) &&  xpp[2]->CheckType(XPP_NUMERIC)  ) 
      {
         DWORD count = xpp[2]->GetDWord();
         if( xpp[1]->con_size() >=  ( sizeof(ft_item_st) * count ) )
         {
            DWORD pos;
            ft_item_st * f  = (ft_item_st *) ((void*) xpp[1]->LockStrEx()) ;
            if( f )
            {
               for( pos = 1; pos <= count; pos++ )
               {
                  _conSetCLMember( xpp[0]->con() , f[pos].name , _mk_ptr_( LPSTR , &f[pos] , 0 ) , sizeof(ft_item_st) );
               }
               xpp[1]->UnLockStrEx();
            }
         }
      }
   }
   //----------------------------------------------------------------------------------------------------------------------
   void create_class_vtran_buffer( XppParamList pl)
   {
      ContainerHandle conco = _conClsObj("__VTRAN__BUFFER");
      if( conco == NULLCONTAINER )
      {
         TXbClass * pc = new TXbClass;pc->ClassName("__VTRAN__BUFFER");
         pc->EXPORTED();
         pc->Var("m_data_5690d701603d4c05849d8f605e91f1f0"  );
         // -----
         
         pc->MethodCB("init"      , "{|s,aStruct, prop_table,nFlags, oBuffer,p5,p6,p7, m_data| m_data := _ot4xb_expando_():new() "
                                    ", s:m_data_5690d701603d4c05849d8f605e91f1f0 :=  m_data  "
                                    ", m_data:buffer := oBuffer "
                                    ", m_data:dw_instance_flags  := nOr( nFlags )"
                                    ", m_data:method_table       := _ot4xb_expando_():new() "
                                    ", m_data:prop_table         := s:__create_prop_table__( prop_table ) "
                                    ", m_data:aStruct            := iif( valtype( aStruct ) =='A', aStruct , Array() ) "
                                    ", m_data:field_count        := len( m_data:aStruct ) "
                                    ", m_data:field_table_string := s:__create_field_table_string__( m_data:aStruct )"
                                    ", m_data:field_table        := s:__create_field_table_from_table_string__(m_data:field_table_string , m_data:field_count ) "
                                    ", s }");

         pc->Method_cbbs("__create_prop_table__"                    , "{|s,ttr |  XbFpCall( 0x%08.8X, ttr  )  }" , vtran_parse_property_table_array );
         pc->Method_cbbs("__create_field_table_string__"            , "{|s,afld|  XbFpCall( 0x%08.8X, afld )  }" , __create_field_table_string__ );
         pc->Method_cbbs("__create_field_table_from_table_string__" , "{|s,fts |  XbFpCall( 0x%08.8X, fts  )  }" , __create_field_table_from_table_string__ );
         
         // -----

         pc->MethodCB("reset_buffer", "{|s,buffer| s:m_data_5690d701603d4c05849d8f605e91f1f0:buffer := _OT4XB_EXPANDO_():new() }");
         pc->MethodCB("set_buffer"  , "{|s,buffer| s:m_data_5690d701603d4c05849d8f605e91f1f0:buffer := __vmask(0x80,buffer, _OT4XB_EXPANDO_():new()) }");
         pc->MethodCB("get_buffer"  , "{|s,buffer| s:m_data_5690d701603d4c05849d8f605e91f1f0:buffer  }");
         // -----
         pc->Method_cbbs("get_prop"      , "{|s,k,v,oo,pp,kk,fd,flags,vv|"
                                           "  oo    := s:m_data_5690d701603d4c05849d8f605e91f1f0"
                                           ", pp    := oo:prop_table:get_prop(k)"
                                           ", flags := __vpeek( pp, \":r_vtran\", 0 )"
                                           ", kk    := __vpeek( pp, \":cField\", k)"
                                           ", fd    := oo:field_table:get_prop(kk)"
                                           ", vv    := oo:buffer:get_prop(kk)"
                                           ", XbFpCall( 0x%08.8X,vv,flags)  }" , transformation_play );
         // -----
         pc->Method_cbbs("set_prop"      , "{|s,k,v,oo,pp,kk,fd,flags,vv|"
                                           "  oo    := s:m_data_5690d701603d4c05849d8f605e91f1f0"
                                           ", pp    := oo:prop_table:get_prop(k)"
                                           ", flags := __vpeek( pp, \":w_vtran\", 0 )"
                                           ", kk    := __vpeek( pp, \":cField\", k)"
                                           ", fd    := oo:field_table:get_prop(kk)"
                                           ", vv    := XbFpCall( 0x%08.8X,v,flags,fd) " // transformation_play
                                           ", oo:buffer:set_prop(kk , vv) }" , transformation_play );





         pc->MethodCB("GetNoIVar" , "{|s,k|  s:get_prop(k) }" );
         pc->MethodCB("SetNoIVar" , "{|s,k|  s:set_prop(k) }" );

         pc->Method("noMethod"       , generic_method , 16 ,
                      ",nOr(s:m_data_5690d701603d4c05849d8f605e91f1f0:dw_instance_flags)"
                      ",s:m_data_5690d701603d4c05849d8f605e91f1f0:method_table:get_prop(p1)" );
         // -----
         pc->MethodCB("data" , "{|s,k,v|s:m_data_5690d701603d4c05849d8f605e91f1f0}");
         pc->MethodCB("json_escape_self", "{|s,pStack| s:m_data_5690d701603d4c05849d8f605e91f1f0:json_escape_self()}");
         // -----
         conco = pc->Create();
         delete pc;
         if( conco == NULLCONTAINER )
         {
            _ret(pl);
            return;
         }
      }
      _conReturn(pl,conco);
      _conRelease(conco);
   }

   //----------------------------------------------------------------------------------------------------------------------
END_NAMESPACE()
//----------------------------------------------------------------------------------------------------------------------









//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

END_NAMESPACE()
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(__VTRAN )
{
   if( _partype(pl,0) )
   {
      __vtran_ns::transformation_play(pl);
   }
   else
   {
      __vtran_ns::create_class_vtran(pl);
   }
}
// -----------------------------------------------------------------------------------------------------------------
