//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <xmllite.h>
// -----------------------------------------------------------------------------------------------------------------
#define EXPANDO_FORMAT_DEBUG                         1
#define EXPANDO_FORMAT_FLAT_ARRAY_KV_ITEMS  0x00000010
#define EXPANDO_FORMAT_ENFORCE_FLAT         0x00000020
#define EXPANDO_FORMAT_PRETTY               0x01000000
#define EXPANDO_FORMAT_ND_PRECISSION(x)     ((x & 0x0F) < 16)
#define EXPANDO_FORMAT_ND_FIXED             0x00100000
#define EXPANDO_FORMAT_ND_MINIMAL           0x00200000
// -----------------------------------------------------------------------------------------------------------------
HMODULE s_hdll_xmllite = 0;
typedef long(__stdcall* CreateXmlReader_ft)(REFIID, void**, IMalloc*);
CreateXmlReader_ft  s_fp_CreateXmlReader = 0;
//----------------------------------------------------------------------------------------------------------------------

BEGIN_NAMESPACE(ot4xb_expando)
// ---------------------------------------------------------------------------------
static void method_add_from_array(XppParamList pl);
static void method_iterate_cb(XppParamList pl);
// ---------------------------------------------------------------------------------
static void get_prop(TXppParamList& xpp);
static void set_prop(TXppParamList& xpp);
static void is_prop(TXppParamList& xpp);
static void remove_prop(TXppParamList& xpp);
static void set_prop_add(TXppParamList& xpp);
static void add_env_strings(TXppParamList& xpp);
static void add_ini_string(TXppParamList& xpp);
static void get_prop_index(TXppParamList& xpp);
// static void add_from_array(TXppParamList& xpp);
static void json_escape_self(TXppParamList& xpp);
// static void xml_escape_self(TXppParamList& xpp);
static void m_json_on_unserialize_pop(TXppParamList& xpp);
// static void m_xml_on_unserialize_pop(TXppParamList& xpp);
// static void xml_serialize_value(TZString& z, ContainerHandle con_value, DWORD pStack, DWORD nMoreFlags, DWORD nDepth);
// ---------------------------------------------------------------------------------

static void mc_envelope_from_xml(XppParamList  pl);
static void from_xml_worker_100(ContainerHandle conr, LPSTR pXmlSrc, DWORD cbXmlSrc, DWORD dwFlags);
class xml_node_100_t;
static void from_xml_xml_loop_100(ContainerHandle conr, IXmlReader* xml, DWORD dwFlags);
// ---------------------------------------------------------------------------------

static void method_get_prop(XppParamList pl) { TXppParamList xpp(pl); if ((xpp.PCount() > 3) && xpp[2]->CheckType(XPP_ARRAY) && xpp[3]->CheckType(XPP_CHARACTER | XPP_NUMERIC)) { get_prop(xpp); } }
static void method_set_prop(XppParamList pl) { TXppParamList xpp(pl); if ((xpp.PCount() > 3) && xpp[2]->CheckType(XPP_ARRAY) && xpp[3]->CheckType(XPP_CHARACTER | XPP_NUMERIC)) { set_prop(xpp); } }
static void method_is_prop(XppParamList pl) { TXppParamList xpp(pl); if ((xpp.PCount() > 3) && xpp[2]->CheckType(XPP_ARRAY) && xpp[3]->CheckType(XPP_CHARACTER | XPP_NUMERIC)) { is_prop(xpp); } }
static void method_remove_prop(XppParamList pl) { TXppParamList xpp(pl); if ((xpp.PCount() > 3) && xpp[2]->CheckType(XPP_ARRAY) && xpp[3]->CheckType(XPP_CHARACTER | XPP_NUMERIC)) { remove_prop(xpp); } }
static void method_set_prop_add(XppParamList pl) { TXppParamList xpp(pl); if ((xpp.PCount() > 3) && xpp[2]->CheckType(XPP_ARRAY) && xpp[3]->CheckType(XPP_CHARACTER | XPP_NUMERIC)) { set_prop_add(xpp); } }
static void method_add_env_strings(XppParamList pl) { TXppParamList xpp(pl); if ((xpp.PCount() > 3) && xpp[2]->CheckType(XPP_ARRAY) && xpp[3]->CheckType(XPP_CHARACTER | XPP_NUMERIC)) { add_env_strings(xpp); } }
static void method_add_ini_string(XppParamList pl) { TXppParamList xpp(pl); if ((xpp.PCount() > 3) && xpp[2]->CheckType(XPP_ARRAY) && xpp[3]->CheckType(XPP_CHARACTER | XPP_NUMERIC)) { add_ini_string(xpp); } }
static void method_json_escape_self(XppParamList pl) { TXppParamList xpp(pl); if ((xpp.PCount() > 3) && xpp[2]->CheckType(XPP_ARRAY) && xpp[3]->CheckType(XPP_CHARACTER | XPP_NUMERIC)) { json_escape_self(xpp); } }
static void method_get_prop_index(XppParamList pl) { TXppParamList xpp(pl); if ((xpp.PCount() > 3) && xpp[2]->CheckType(XPP_ARRAY) && xpp[3]->CheckType(XPP_CHARACTER | XPP_NUMERIC)) { get_prop_index(xpp); } }
static void method_m_json_on_unserialize_pop(XppParamList pl) { TXppParamList xpp(pl); if ((xpp.PCount() > 3) && xpp[2]->CheckType(XPP_ARRAY) && xpp[3]->CheckType(XPP_CHARACTER | XPP_NUMERIC)) { m_json_on_unserialize_pop(xpp); } }
static void method_add_from_server_cookie( XppParamList pl );
// ---------------------------------------------------------------------------------
// method_add_from_server_cookie( 1 Self , 2 cookie )
static void method_add_from_server_cookie( XppParamList pl )
{
   TXppParamList xpp( pl, 2 );
   ContainerHandle Self = xpp[ 1 ]->con();
   LPSTR server_cookie_string = xpp[ 2 ]->LockStrEx();

   if( server_cookie_string )
   {
      const char* cookie_start = (const char*) server_cookie_string;
      const char* cookie_end;

      auto add_cookie = [Self] ( const char* name, size_t name_len, const char* value, size_t value_len ) {
         // Realizar LTrim y RTrim para name
         while( name_len > 0 && *name == ' ' ) { name++; name_len--; }
         while( name_len > 0 && *( name + name_len - 1 ) == ' ' ) { name_len--; }
         while( value_len > 0 && *value == ' ' ) { value++; value_len--; }
         while( value_len > 0 && *( value + value_len - 1 ) == ' ' ) { value_len--; }

         // Crear los containers para key y value
         ContainerHandle k = _conPutCL( NULLCONTAINER, (LPSTR) name, name_len );
         ContainerHandle v = _conPutCL( NULLCONTAINER, (LPSTR) value, value_len );
         ContainerHandle r = _conNew( NULLCONTAINER );

         // Llamar al m�todo "set_prop" en el contenedor
         ContainerHandle pcon[ ] = { Self, k, v };
         _conCallMethodPa( r, "set_prop", 3, pcon );

         // Liberar los contenedores
         _conRelease( k );
         _conRelease( v );
         _conRelease( r );
      };

      // Procesar las cookies
      while( ( cookie_end = strchr( cookie_start, ';' ) ) != NULL )
      {
         const char* equal_sign = strchr( cookie_start, '=' );
         if( equal_sign && equal_sign < cookie_end )
         {
            size_t name_len = equal_sign - cookie_start;  // Longitud del nombre (antes del '=')
            size_t value_len = cookie_end - ( equal_sign + 1 );  // Longitud del valor (despu�s del '=' y antes del ';')
            add_cookie( cookie_start, name_len, equal_sign + 1, value_len );  // Llamada a add_cookie con la cookie actual
         }
         cookie_start = cookie_end + 1;  // Avanzamos al siguiente cookie
      }

      // Procesar la �ltima cookie (si no termina con ';')
      if( *cookie_start != '\0' )
      {
         const char* equal_sign = strchr( cookie_start, '=' );
         if( equal_sign )
         {
            size_t name_len = equal_sign - cookie_start;
            size_t value_len = strlen( cookie_start ) - ( equal_sign - cookie_start ) - 1;
            add_cookie( cookie_start, name_len, equal_sign + 1, value_len );  // Llamada para la �ltima cookie
         }
      }
   }
}




// ------------------------------------------------------------------------------------------------
// 2 @s:__m__props__  // 3 @s:__m__hash__ // 4 key
static DWORD find_prop(TXppParamList& xpp, DWORD* pCrc = 0, DWORD* pItemCount = 0, DWORD* pnnn = 0)
{
   DWORD crc = 0;
   DWORD* pdw_hash = (DWORD*)xpp[3]->LockStr();
   DWORD  cnt_hash = (xpp[3]->ExLen() >> 2);
   DWORD  cb_k = 0;
   LPBYTE k = (LPBYTE)xpp[4]->LockStr(&cb_k);
   DWORD pos = INFINITE;

   if (k && cb_k)
   {
      crc = dwCrc32Lower(0, k, cb_k);
   }
   if (crc && pdw_hash && cnt_hash)
   {
      pos = _dwscan(pdw_hash, cnt_hash, crc);
   }
   if (pCrc)
   {
      pCrc[0] = crc;
      if (pItemCount)
      {
         pItemCount[0] = cnt_hash;
      }
      if ((pos == INFINITE) && pnnn)
      {
         pnnn[0] = _dwscan(pdw_hash, cnt_hash, 0);
      }
   }
   xpp[3]->UnLockStrEx();
   xpp[4]->UnLockStrEx();
   return pos;
}
// ---------------------------------------------------------------------------------
static void get_prop(TXppParamList& xpp)
{
   DWORD pos = find_prop(xpp);
   if (pos != INFINITE)
   {
      _conArrayGet(xpp[2]->con(), xpp[0]->con(), pos + 1, 2, 0);
   }
}
// ---------------------------------------------------------------------------------
static void is_prop(TXppParamList& xpp)
{
   DWORD pos = find_prop(xpp);
   xpp[0]->PutBool(((pos == INFINITE) ? 0 : 1));
}
// ---------------------------------------------------------------------------------
static void get_prop_index(TXppParamList& xpp)
{
   DWORD pos = find_prop(xpp);
   xpp[0]->PutDWord(((pos == INFINITE) ? 0 : pos + 1));
}
// ---------------------------------------------------------------------------------
static void remove_prop(TXppParamList& xpp)
{
   DWORD pos = find_prop(xpp);
   if (pos != INFINITE)
   {
      _conArrayGet(xpp[2]->con(), xpp[0]->con(), pos + 1, 2, 0); // return old element
      ContainerHandle cona = _conNewArray(1, 2);
      _conArrayPut(xpp[2]->con(), cona, pos + 1, 0);
      _conRelease(cona); cona = NULLCONTAINER;
      DWORD cb = 0;
      DWORD* pdw_hash = (DWORD*)xpp[3]->LockStr(&cb, TRUE);
      pdw_hash[pos] = 0;
      xpp[3]->UnLockStrEx();
      return;
   }
}
// ---------------------------------------------------------------------------------
// 2 @s:__m__props__  // 3 @s:__m__hash__ // 4 k // 5 v
static void set_prop(TXppParamList& xpp)
{
   DWORD cnt = 0;
   DWORD crc = 0;
   DWORD nnn = 0;
   DWORD pos = find_prop(xpp, &crc, &cnt, &nnn);
   if (pos == INFINITE)
   {
      if (crc)
      {
         if (nnn == INFINITE)
         {
            pos = cnt;
            cnt++;
            _conResizeC(xpp[3]->con(), cnt * 4);
            _conResizeA(xpp[2]->con(), cnt);
         }
         else
         {
            pos = nnn;
         }
         ContainerHandle cona = _conNewArray(1, 2);
         _conArrayPut(cona, xpp[4]->con(), 1, 0);
         _conArrayPut(cona, xpp[5]->con(), 2, 0);
         _conArrayPut(xpp[2]->con(), cona, pos + 1, 0);
         _conRelease(cona); cona = NULLCONTAINER;
         DWORD cb = 0;
         DWORD* pdw_hash = (DWORD*)xpp[3]->LockStr(&cb, TRUE);
         pdw_hash[pos] = crc;
         xpp[3]->UnLockStrEx();
      }
      return;
   }
   _conArrayPut(xpp[2]->con(), xpp[5]->con(), pos + 1, 2, 0);
}
// ---------------------------------------------------------------------------------
// 2 @s:__m__props__  // 3 @s:__m__hash__ // 4 pEnvironment
static void add_env_strings(TXppParamList& xpp)
{
   LONG ht = _conCallLong("_HDICT_NEW");
   _conCallVoid("_HDICT_ADDPROPFROMARRAY", ht, xpp[2]->con());
   _conCallVoid("_HDICT_ADD_ENV_STRINGS", ht, xpp[4]->GetLong());
   ContainerHandle contmp = _conPutNL(NULLCONTAINER, 3);
   ContainerHandle cona = _conCallCon("_HDICT_ITERATE_CB", ht, contmp, xpp[3]->con());
   _conRelease(contmp); contmp = 0;
   _conCallVoid("_HDICT_DESTROY", ht); ht = 0;
   xpp[2]->Put(cona); _conRelease(cona); cona = 0;
}
// ---------------------------------------------------------------------------------
static void add_ini_string(TXppParamList& xpp)
{
   LONG ht = _conCallLong("_HDICT_NEW");
   _conCallVoid("_HDICT_ADDPROPFROMARRAY", ht, xpp[2]->con());
   _conCallVoid("_HDICT_ADDPROPFROMINISTRING", ht, xpp[4]->con(), xpp[5]->con());
   ContainerHandle contmp = _conPutNL(NULLCONTAINER, 3);
   ContainerHandle cona = _conCallCon("_HDICT_ITERATE_CB", ht, contmp, xpp[3]->con());
   _conRelease(contmp); contmp = 0;
   _conCallVoid("_HDICT_DESTROY", ht); ht = 0;
   xpp[2]->Put(cona); _conRelease(cona); cona = 0;
}
// ---------------------------------------------------------------------------------
// ot4xb_iterate_array_cb(1 array , 2 cb , 3 cargo ,4 flags)
// {|element,pos , cargo |    ..... }  -> result ignore unless 0x1000
// flags   0x0001  skip NIL
//         0x1000  replace value with codeblock result
// 

_XPP_REG_FUN_(OT4XB_ITERATE_ARRAY_CB)
{
   TXppParamList xpp(pl, 4);
   ContainerHandle cona = xpp[1]->CheckType(XPP_ARRAY) ? xpp[1]->con() : NULLCONTAINER;
   DWORD item_count = cona ? xpp[1]->con_size() : 0;
   ContainerHandle codeblock = xpp[2]->CheckType(XPP_BLOCK) ? xpp[2]->con() : NULLCONTAINER;
   ContainerHandle cargo = xpp[3]->con();
   DWORD flags = (DWORD)xpp[4]->GetDWord();
   if (codeblock && item_count)
   {
      DWORD item_pos;
      for (item_pos = 1; item_pos <= item_count; item_pos++)
      {
         ContainerHandle item = _conArrayGet(cona, NULLCONTAINER, item_pos, 0);
         if (item)
         {
            ContainerHandle con_item_pos = _conPutNL(NULLCONTAINER, item_pos);
            if (!((flags & 1) && _conCheckType(item, XPP_UNDEF)))
            {
               ContainerHandle tmp = _conNew(NULLCONTAINER);
               if (!_conEvalB(tmp, codeblock, 3, item, con_item_pos, cargo))
               {
                  if (flags && 0x1000) // store result
                  {
                     _conArrayPut(cona, tmp, item_pos, 0);
                  }
               }
               _conRelease(tmp); tmp = NULLCONTAINER;
            }
            _conRelease(item); item = NULLCONTAINER;
         }
      }
   }
}

// ---------------------------------------------------------------------------------
// method_iterate_cb(1 self,2 aprop,3 cb,4 cargo,5 flags)
// {|key,value,self,cargo |    ..... }  -> result ignore unless 0x1000
// flags   0x0001  skip NIL
//         0x1000  replace value with codeblock result
// 
static void method_iterate_cb(XppParamList pl)
{
   TXppParamList xpp(pl, 5);
   ContainerHandle self = xpp[1]->con();
   ContainerHandle cona = xpp[2]->CheckType(XPP_ARRAY) ? xpp[2]->con() : NULLCONTAINER;
   DWORD item_count = cona ? xpp[2]->con_size() : 0;
   ContainerHandle codeblock = xpp[3]->CheckType(XPP_BLOCK) ? xpp[3]->con() : NULLCONTAINER;
   ContainerHandle cargo = xpp[4]->con();
   DWORD flags = (DWORD)xpp[5]->GetDWord();
   if (codeblock && item_count)
   {
      DWORD item_pos;
      for (item_pos = 1; item_pos <= item_count; item_pos++)
      {
         ContainerHandle k = _conArrayGet(cona, NULLCONTAINER, item_pos, 1, 0);
         if (_conCheckType(k, XPP_CHARACTER))
         {
            ContainerHandle vv = _conArrayGet(cona, NULLCONTAINER, item_pos, 2, 0);
            if ((flags & 1) && _conCheckType(vv, XPP_UNDEF))
            {
               _conRelease(vv);
               vv = NULLCONTAINER;
            }
            if (vv)
            {
               ContainerHandle tmp = _conNew(NULLCONTAINER);
               if (!_conEvalB(tmp, codeblock, 4, k, vv, self, cargo))
               {
                  if (flags && 0x1000) // store result
                  {
                     _conArrayPut(cona, tmp, item_pos, 2, 0);
                  }
               }
               _conRelease(vv);
               vv = NULLCONTAINER;
            }
         }
         if (k)
         {
            _conRelease(k);
            k = NULLCONTAINER;
         }
      }
   }
}
// ---------------------------------------------------------------------------------
 // method_add_from_array( 1 Self , 2 src_array , 3 flags , 4 get_key_cb  , 5 cargo)
 // flags:  0 normal set_prop_add
 //         1 replace set_prop
 //    0x0008 each item contain an array with one or more items  // like html3:GetAllvars()
 //    0x0100 use get_key_cb //  k := eval(get_key_cb , element ) // v := element
static void method_add_from_array(XppParamList pl)
{
   TXppParamList xpp(pl, 5);
   DWORD flags = (DWORD)xpp[3]->GetDWord();
   DWORD item_count = ((xpp[1]->CheckType(XPP_OBJECT) && xpp[2]->CheckType(XPP_ARRAY)) ? xpp[2]->con_size() : 0);
   DWORD item_pos;
   ContainerHandle cona_ref = xpp[2]->con();
   ContainerHandle self_ref = xpp[1]->con();
   ContainerHandle con_tmp = _conNew(NULLCONTAINER);
   ContainerHandle con_key_ref = flags & 0x100 ? (xpp[4]->CheckType(XPP_BLOCK) ? xpp[4]->con() : NULLCONTAINER) : NULLCONTAINER;
   ContainerHandle con_cargo_ref = flags & 0x100 ? xpp[5]->con() : NULLCONTAINER;

   for (item_pos = 1; item_pos <= item_count; item_pos++)
   {
      ContainerHandle k = NULLCONTAINER;
      ContainerHandle vv = NULLCONTAINER;
      if (flags & 0x100)
      {
         if (con_key_ref)
         {
            vv = _conArrayGet(cona_ref, NULLCONTAINER, item_pos, 0);
            if (vv)
            {
               k = _conNew(k);
               if (_conEvalB(k, con_key_ref, 4, vv, item_pos, self_ref, con_cargo_ref))
               {
                  _conRelease(k);
                  k = NULLCONTAINER;
               }
            }
         }
      }
      else
      {
         k = _conArrayGet(cona_ref, NULLCONTAINER, item_pos, 1, 0);
         if (k)
         {
            vv = _conArrayGet(cona_ref, NULLCONTAINER, item_pos, 2, 0);
         }
      }
      if (k && vv)
      {
         ULONG t = 0;
         _conType(vv, &t);
         if ((t & XPP_ARRAY) && (flags & 8))
         {
            DWORD cnt = 0;
            DWORD pos;
            _conSizeA(vv, &cnt, 0);
            for (pos = 1; pos <= cnt; pos++)
            {
               ContainerHandle v = _conArrayGet(vv, NULLCONTAINER, pos, 0);
               if (v)
               {
                  ContainerHandle pcon[] = { self_ref,k,v };
                  if (flags & 1)
                  {
                     _conCallMethodPa(con_tmp, "set_prop", 3, pcon);
                  }
                  else
                  {
                     _conCallMethodPa(con_tmp, "set_prop_add", 3, pcon);
                  }
                  _conRelease(v); v = 0;
               }

            }
         }
         else
         {
            ContainerHandle pcon[] = { self_ref,k,vv };

            if (flags & 1)
            {
               _conCallMethodPa(con_tmp, "set_prop", 3, pcon);
            }
            else
            {
               _conCallMethodPa(con_tmp, "set_prop_add", 3, pcon);
            }

         }



      }
      if (k) { _conRelease(k);  k = NULLCONTAINER; }
      if (vv) { _conRelease(vv); vv = NULLCONTAINER; }
   }
   _conRelease(con_tmp); con_tmp = 0;
}
// ---------------------------------------------------------------------------------
int __cdecl __compare_LONG(void*, const void* p1, const void* p2)
{
   return _mk_ptr_(LPLONG, p1, 0)[0] - _mk_ptr_(LPLONG, p2, 0)[0];
}
// ---------------------------------------------------------------------------------      

// ---------------------------------------------------------------------------------    
// 1 nFlags, 2 props , 3 hash , 4 k=NIL , 5 value=NIL , 6 @cargo
static void m_json_on_unserialize_pop(TXppParamList& xpp)
{
   if (xpp[6]->CheckType(XPP_ARRAY))
   {
      DWORD nn = xpp[6]->con_size();
      DWORD n;

      for (n = 1; n < nn; n += 2)
      {
         _conArrayGet(xpp[6]->con(), xpp[4]->con(), n, 0);
         _conArrayGet(xpp[6]->con(), xpp[5]->con(), n + 1, 0);
         set_prop(xpp);
      }
      xpp[6]->Put(NULLCONTAINER);
   }
}
// ---------------------------------------------------------------------------------    
// 1 Self , 2 props , 3 nserial , 4 pStack , 5 Self	, 6 nMoreFlags	 , 7 nDepth
static void json_escape_self(TXppParamList& xpp)
{

   TZString z(4096);



   DWORD nSerial = xpp[3]->GetDWord();
   DWORD nMoreFlags = xpp[6]->GetDWord();
   DWORD nDepth = xpp[7]->GetDWord();
   DWORD bCute;
   TList* pStack = (TList*)xpp[4]->GetDWord();
   BOOL bDestroyStack = 0;

   if (nMoreFlags & EXPANDO_FORMAT_ENFORCE_FLAT)
   {
      nMoreFlags &= ~EXPANDO_FORMAT_PRETTY;
   }
   bCute = nMoreFlags & EXPANDO_FORMAT_PRETTY;

   if (bCute || (nMoreFlags & EXPANDO_FORMAT_ENFORCE_FLAT) ) { DWORD ddd;  z += "\r\n"; for (ddd = 0;  ddd < nDepth; ddd++) { z += "   "; } }
   z += "{";
   nDepth++;




   if (!pStack)
   {
      bDestroyStack = TRUE;
      pStack = new TList;
   }

   if (pStack->plocate((void*)nSerial, __compare_LONG, 0))
   {
      if (bCute) { DWORD ddd;  z += "\r\n"; for (ddd = 0;  ddd < nDepth; ddd++) { z += "   "; } }
      z.printf("\"recursion_detected\" : true ");
      goto after_dump_properties;
   }

   pStack->Add((void*)nSerial);

   if (xpp[2]->CheckType(XPP_ARRAY))
   {

      DWORD nCount = xpp[2]->con_size();
      DWORD n;
      ContainerHandle cona = xpp[2]->con();
      DWORD nn = 0;
      for (n = 1; n <= nCount; n++)
      {
         ContainerHandle con_key = _conNew(NULLCONTAINER);
         ContainerHandle con_value = _conNew(NULLCONTAINER);
         _conArrayGet(cona, con_key, n, 1, 0);
         _conArrayGet(cona, con_value, n, 2, 0);
         DWORD cbKey = 0;
         LPSTR pKey = 0;
         
         if (_conRLockC(con_key, &pKey, &cbKey) == 0)
         {
            if (bCute) { DWORD ddd;  z += "\r\n"; for (ddd = 0;  ddd < nDepth; ddd++) { z += "   "; } }
            if (nn) { z.AddChar(','); }
            nn++;
            z.printf("\"%s\" : ", pKey);
            json_ns::serialize_value(z, con_value, (DWORD)pStack, nMoreFlags, nDepth);
            _conUnlockC(con_key);
            pKey = 0;
         }
         _conReleaseM(con_key, con_value, 0);
      }
   }

   pStack->Pop();
   if (bDestroyStack)
   {
      delete pStack;
      pStack = 0;
   }

after_dump_properties:;
   nDepth--;
   if (bCute) { DWORD ddd;  z += "\r\n"; for (ddd = 0;  ddd < nDepth; ddd++) { z += "   "; } }
   z += "}";

   xpp[0]->PutStrLen(z._pt_(), z.len());
}
// ---------------------------------------------------------------------------------
// 2 @s:__m__props__  // 3 @s:__m__hash__ // 4 k // 5 v
static void set_prop_add(TXppParamList& xpp)
{
   DWORD cnt = 0;
   DWORD crc = 0;
   DWORD nnn = 0;
   DWORD pos = find_prop(xpp, &crc, &cnt, &nnn);
   if (pos == INFINITE)
   {
      if (crc)
      {
         if (nnn == INFINITE)
         {
            pos = cnt;
            cnt++;
            _conResizeC(xpp[3]->con(), cnt * 4);
            _conResizeA(xpp[2]->con(), cnt);
         }
         else
         {
            pos = nnn;
         }
         ContainerHandle cona = _conNewArray(1, 2);
         _conArrayPut(cona, xpp[4]->con(), 1, 0);
         _conArrayPut(cona, xpp[5]->con(), 2, 0);
         _conArrayPut(xpp[2]->con(), cona, pos + 1, 0);
         _conRelease(cona); cona = NULLCONTAINER;
         DWORD cb = 0;
         DWORD* pdw_hash = (DWORD*)xpp[3]->LockStr(&cb, TRUE);
         pdw_hash[pos] = crc;
         xpp[3]->UnLockStrEx();
      }
      return;
   }
   else
   {
      ContainerHandle cona = _conNew(NULLCONTAINER);
      _conArrayGet(xpp[2]->con(), cona, pos + 1, 2, 0);
      if (_conCheckType(cona, XPP_ARRAY))
      {
         ULONG ul = _conGetArrayLen(cona);
         _conResizeA(cona, ul + 1);
         _conArrayPut(cona, xpp[5]->con(), ul + 1, 0);
      }
      else
      {
         ContainerHandle con = cona;
         cona = _conNewArray(1, 2);
         _conArrayPut(cona, con, 1, 0);
         _conArrayPut(cona, xpp[5]->con(), 2, 0);
         _conRelease(con);
         con = NULLCONTAINER;
      }
      _conArrayPut(xpp[2]->con(), cona, pos + 1, 2, 0);
      _conRelease(cona);
      cona = NULLCONTAINER;
   }
}
// ---------------------------------------------------------------------------------
static void mc_envelope_from_xml(XppParamList  pl)   // self,uXml , dwFlags 
{
   TXppParamList xpp = TXppParamList(pl, 3);
   DWORD dwFlags = (xpp[3]->CheckType(XPP_NUMERIC) ? xpp[3]->GetDWord() : 0x100);
   if (!s_hdll_xmllite)
   {
      s_hdll_xmllite = LoadLibrary("xmllite.dll");
      if (s_hdll_xmllite)
      {
         s_fp_CreateXmlReader = (CreateXmlReader_ft)GetProcAddress(s_hdll_xmllite, "CreateXmlReader");
      }
   }
   if (s_fp_CreateXmlReader && xpp[2]->CheckType(XPP_CHARACTER) && (dwFlags & 0x100))
   {
      DWORD cbXmlSrc = 0;
      LPSTR pXmlSrc = xpp[2]->LockStr(&cbXmlSrc);
      from_xml_worker_100(xpp[0]->con(), pXmlSrc, cbXmlSrc, dwFlags);
   }
}
// ---------------------------------------------------------------------------------
class xml_node_100_t : public T_ot4xb_base
{
   public:
   xml_node_100_t* m_prev;
   xml_node_100_t* m_next;
   char             m_name[260];
   DWORD            m_type;
   ContainerHandle  m_con;
   ContainerHandle  m_attributes;
   DWORD            m_flags;
   // -----------------------------------------------
   xml_node_100_t(LPWSTR pNodeName = 0)
   {
      m_prev = 0;
      m_next = 0;
      ZeroMemory(m_name, sizeof(m_name));
      m_type = 0;
      m_con = 0;
      m_attributes = 0;
      m_flags = 0;
      if (pNodeName)
      {
         WideCharToMultiByte(ANSI_CHARSET, 0, pNodeName, lstrlenW(pNodeName), m_name, sizeof(m_name) - 1, 0, 0);
      }
   };
   // -----------------------------------------------
   ~xml_node_100_t()
   {
      if (m_next) { m_next->m_prev = m_prev; }
      if (m_prev) { m_prev->m_next = m_next; }
      if (m_con) { _conRelease(m_con); }
      if (m_attributes) { _conRelease(m_attributes); }
   };
   // -----------------------------------------------
   xml_node_100_t* push(LPWSTR pNodeName, DWORD dwFlags)
   {

      if (m_next) { return 0; } // must not happen
      m_next = new xml_node_100_t(pNodeName);
      m_next->m_prev = this;
      m_next->m_flags = dwFlags;
      return m_next;
   };
   // -----------------------------------------------
   void add_prop(LPSTR pName, ContainerHandle* pcon)
   {
      if (m_con) { _conType(m_con, &m_type); }
      else { m_type = 0; }
      if (pName && pcon)
      {
         if (!*pcon)
         {
            *pcon = _conNew(NULLCONTAINER);
         }
         if (!(m_type & XPP_OBJECT))
         {
            _conReleaseM(m_con, 0);
            m_con = _conNewObj("_OT4XB_EXPANDO_", 0);
            if (m_con) { _conType(m_con, &m_type); }
            else { m_type = 0; }
         }
         _conRelease(_conMCallConNR("set_prop_add", m_con, 2, _conPutC(0, pName), *pcon));
         *pcon = 0;
      }
      if (pcon)
      {
         _conReleaseM(*pcon, 0);
         *pcon = 0;
      }
   };
   // -----------------------------------------------
   xml_node_100_t* pop(void)
   {
      if (m_next) { return 0; } // must not happen
      if (!m_prev) { return 0; } // only if root
      xml_node_100_t* parent = m_prev;
      if (!m_con)
      {
         m_con = _conNewObj("_OT4XB_EXPANDO_", 0);
         if (m_con) { _conType(m_con, &m_type); }
         else { m_type = 0; }
      }
      merge_attributes();
      if (parent)
      {
         parent->add_prop(m_name, &m_con);
         delete this;
         return parent;
      }
      return 0;
   };
   // -----------------------------------------------
   void merge_attributes(void)
   {
      if (m_con) { _conType(m_con, &m_type); }
      else { m_type = 0; }
      if (m_attributes)
      {
         if (m_type & XPP_OBJECT)
         {
            if (m_flags & 0x2000)
            {
               _conRelease(_conMCallConNR("set_prop_add", m_con, 2, _conPutC(0, "m_attributes"), m_attributes));
               m_attributes = 0;
               return;
            }
            else
            {
               _conRelease(_conMCallConNR("add_from_array", m_con, 1, m_attributes));
               m_attributes = 0;
               return;
            }
         }
         _conRelease(m_attributes);
         m_attributes = 0;
      }
   }
   // -----------------------------------------------         
   void add_text(LPWSTR pw, DWORD cc)
   {
      int cb = 0;
      LPSTR p = w2ansi(pw, cc, &cb);

      if (m_con) { _conType(m_con, &m_type); }
      else { m_type = 0; }
      if (m_type & XPP_CHARACTER)
      {
         DWORD cb_src = 0;
         _conSizeC(m_con, &cb_src);
         _conResizeC(m_con, cb_src + cb);
         DWORD dw_new_str = 0;
         LPSTR p_new_str = 0;
         if (_conWLockC(m_con, &p_new_str, &dw_new_str) == 0)
         {
            if (dw_new_str == (cb_src + cb))
            {
               _bcopy(_mk_ptr_(LPBYTE, p_new_str, cb_src), (LPBYTE)p, cb);
            }
            _conUnlockC(m_con);
            dw_new_str = 0;
            p_new_str = 0;
         }
      }
      else
      {
         if (p && cb)
         {
            m_con = _conPutCL(m_con, p, cb);
         }
         else
         {
            m_con = _conPutC(m_con, "");
         }
      }
      if (p)
      {
         _xfree((void*)p);
         p = 0;
      }
   }

};
// ---------------------------------------------------------------------------------
static void from_xml_worker_100(ContainerHandle conr, LPSTR pXmlSrc, DWORD cbXmlSrc, DWORD dwFlags)
{
   IStream* pInput = 0;
   IXmlReader* pXmlReader = 0;
   dwFlags;
   __try
   {
      HRESULT result = 0;
      result = (*s_fp_CreateXmlReader)(__uuidof(IXmlReader), (void**)&pXmlReader, 0);
      if (SUCCEEDED(result))
      {
         if (_bscan((LPBYTE)pXmlSrc, cbXmlSrc, (BYTE)'<') < cbXmlSrc)
         {
            pInput = (IStream*)str2istream((void*)pXmlSrc, cbXmlSrc);
         }
         else
         {
            SHCreateStreamOnFileA(pXmlSrc, 0, &pInput);
         }
         if (pInput && pXmlReader)
         {
            result = pXmlReader->SetInput(pInput);
            if (SUCCEEDED(result))
            {
               from_xml_xml_loop_100(conr, pXmlReader, dwFlags);
            }
         }
      }
   } __finally
   {
      if (pXmlReader)
      {
         pXmlReader->Release();
         pXmlReader = 0;
      }
      if (pInput)
      {
         pInput->Release();
         pInput = 0;
      }
   }
}
// ---------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------
static void from_xml_xml_loop_100(ContainerHandle conr, IXmlReader* xml, DWORD dwFlags)
{
   xml_node_100_t* root = 0;
   xml_node_100_t* tos = 0;
   XmlNodeType nt;
   while (xml->Read(&nt) == S_OK)
   {
      switch (nt)
      {
         case XmlNodeType_Element:
         {
            LPWSTR pw = 0;
            if (FAILED(xml->GetLocalName((LPCWSTR*)&pw, 0)))
            {
               goto label_cleanup;
            }
            if (tos)
            {
               tos = tos->push(pw, dwFlags);
            }
            else
            {
               if (root)
               {
                  goto label_cleanup;
               }
               root = new xml_node_100_t(pw);
               tos = root;
               tos->m_flags = dwFlags;
            }
            if (dwFlags & 0x1000)
            {
               TList ls;
               if (xml->MoveToFirstAttribute() == S_OK)
               {
                  do
                  {
                     UINT    cbw = 0;
                     LPWSTR  pwstr = 0;
                     if ((xml->GetLocalName((LPCWSTR*)&pwstr, &cbw) == S_OK) && cbw)
                     {
                        void** item = (void**)_xgrab(16);
                        item[0] = (void*)w2ansi(pwstr, (int)cbw, _mk_ptr_(LPINT, item, 4));
                        cbw = 0; pwstr = 0;
                        if ((xml->GetValue((LPCWSTR*)&pwstr, &cbw) == S_OK) && cbw)
                        {
                           item[2] = (void*)w2ansi(pwstr, (int)cbw, _mk_ptr_(LPINT, item, 12));
                        }
                        ls.Add((void*)item);
                     }
                  } while (xml->MoveToNextAttribute() == S_OK);

                  DWORD dwCount = ls.Count();
                  DWORD dw;
                  tos->m_attributes = _conNewArray(2, dwCount, 2, 0);
                  for (dw = 0; dw < dwCount; dw++)
                  {
                     void** item = (void**)ls.Replace(dw, 0);
                     if (item)
                     {
                        ContainerHandle conKey = _conPutC(0, "");
                        ContainerHandle conValue = _conPutC(0, "");

                        if (item[0])
                        {
                           conKey = _conPutCL(conKey, (LPSTR)item[0], (ULONG)item[1]);
                           _xfree(item[0]);
                           item[0] = 0;
                        }
                        if (item[2])
                        {
                           conValue = _conPutCL(conValue, (LPSTR)item[2], (ULONG)item[3]);
                           _xfree(item[2]);
                           item[2] = 0;
                        }
                        _xfree((void*)item); item = 0;
                        _conArrayPut(tos->m_attributes, conKey, dw + 1, 1, 0);
                        _conArrayPut(tos->m_attributes, conValue, dw + 1, 2, 0);
                        _conReleaseM(conKey, conValue, 0);
                     }
                  }
               }
               xml->MoveToElement();
            }
            if (xml->IsEmptyElement())
            {
               if (tos)
               {
                  tos = tos->pop();
               }
               else
               {
                  goto label_cleanup;
               }
               break;
            }
            if (!tos)
            {
               goto label_cleanup;
            }
            break;
         }
         case XmlNodeType_CDATA:
         {
            if (!(dwFlags & 2))
            {
               break;
            }
         }
         case XmlNodeType_Text:
         {
            if (!tos)
            {
               goto label_cleanup;
            }
            UINT cc = 0;
            LPWSTR pw = 0;
            if (FAILED(xml->GetValue((LPCWSTR*)&pw, &cc)))
            {
               goto label_cleanup;
            }
            if (pw)
            {
               tos->add_text(pw, cc);
            }
            break;
         }
         case XmlNodeType_EndElement:
         {
            if (tos)
            {
               tos = tos->pop();
            }
            else
            {
               goto label_cleanup;
            }
            break;
         }
      }
   }
label_cleanup:;
   while (tos) // must not happen but we will be sure not abandoned items
   {
      if (tos == root)
      {
         tos = 0;
      }
      else
      {
         tos = tos->pop();
      }
   }
   if (root)
   {
      root->merge_attributes();
      if (dwFlags & 0x0001)
      {
         tos = root;
         root = new xml_node_100_t(0);
         root->add_prop(tos->m_name, &(tos->m_con));
         delete tos;
      }
      _conPut(conr, root->m_con);
      delete root;
      root = 0;
   }
}
// ---------------------------------------------------------------------------------
static void create_class(XppParamList pl)
{
   ContainerHandle conco = _conClsObj("_OT4XB_EXPANDO_");
   if (conco == NULLCONTAINER)
   {
      TXbClass* pc = new TXbClass; pc->ClassName("_OT4XB_EXPANDO_");
      pc->EXPORTED();
      pc->Var("__m__props__");
      pc->Var("__m__hash__");
      pc->Var("__m__flags__");
      pc->Var("__m__json_flags__");
      pc->Var("__m__serial__");
      pc->Var("__m__unserialize__info__");
      pc->Var("__m__cargo__");

      pc->MethodCB("init", "{|s,f|  s:ot4xb_expando_init(f) , s }");
      pc->Method_cbbs("ot4xb_expando_init", "{|s,f| s:__m__flags__ := f ,"
         "  s:__m__props__ := __anew() ,"
         " s:__m__hash__ := '',"
         " s:__m__serial__ := nFpCall(%i) ,"
         " s }", ot4xb_interlocked_next);
      // -----

      if (method_get_prop == 0) { ; }
      if (method_set_prop == 0) { ; }
      if (method_is_prop == 0) { ; }
      if (method_remove_prop == 0) { ; }
      if (method_get_prop_index == 0) { ; }
      if (method_set_prop_add == 0) { ; }
      if (method_add_env_strings == 0) { ; }
      if (method_add_ini_string == 0) { ; }
      if (method_add_from_array == 0) { ; }
      if (method_iterate_cb == 0) { ; }
      if (method_json_escape_self == 0) { ; }
      if (method_m_json_on_unserialize_pop == 0) { ; }
      if (mc_envelope_from_xml == 0) { ; }


      pc->Method_cbbs("get_prop", "{|s,k| XbFpCall(%i,s,@s:__m__props__,@s:__m__hash__,k  )  }", method_get_prop);
      pc->Method_cbbs("GetNoIVar", "{|s,k| XbFpCall(%i,s,@s:__m__props__,@s:__m__hash__,k  )  }", method_get_prop);
      pc->Method_cbbs("set_prop", "{|s,k,v|  XbFpCall(%i,s,@s:__m__props__,@s:__m__hash__,k,v)  }", method_set_prop);
      pc->Method_cbbs("SetNoIVar", "{|s,k,v|  XbFpCall(%i,s,@s:__m__props__,@s:__m__hash__,k,v)  }", method_set_prop);

      pc->Method_cbbs("is_prop", "{|s,k| XbFpCall(%i,s,@s:__m__props__,@s:__m__hash__,k  )  }", method_is_prop);
      pc->Method_cbbs("remove_prop", "{|s,k| XbFpCall(%i,s,@s:__m__props__,@s:__m__hash__,k  )  }", method_remove_prop);
      pc->Method_cbbs("find_prop_index", "{|s,k| XbFpCall(%i,s,@s:__m__props__,@s:__m__hash__,k  )  }", method_get_prop_index);

      // -----
      pc->Method_cbbs("set_prop_add", "{|s,k,v| XbFpCall(%i,s,@s:__m__props__,@s:__m__hash__,k,v)  }", method_set_prop_add);
      pc->Method_cbbs("add_env_strings", "{|s,p|XbFpCall(%i,s,@s:__m__props__,@s:__m__hash__,p)    , s}", method_add_env_strings);
      pc->Method_cbbs("add_ini_string", "{|s,p,dw|XbFpCall(%i,s,@s:__m__props__,@s:__m__hash__,p,dw) , s}", method_add_ini_string);
      pc->Method_cbbs("add_from_array", "{|s,aa,flags,get_key_cb,cargo|  XbFpCall(%i,s,aa,flags,get_key_cb,cargo) , s }", method_add_from_array);
      pc->Method_cbbs( "add_from_server_cookie", "{|s,str|  XbFpCall(%i,s,str) , s }", method_add_from_server_cookie );



      pc->Method_cbbs("iterate_cb", "{|s,cb,cargo,flags|  XbFpCall(%i,s,s:__m__props__,cb,cargo,flags) , s }", method_iterate_cb); // method_iterate_cb(1 self,2 aprop,3 cb,4 cargo,5 flags) 
                                                                                                                                        // {|key,value,self,cargo |    ..... }  -> result ignore unless 0x1000
      // -----
      pc->MethodCB("get_json_flags", "{|s| s:__m__json_flags__  }");
      pc->MethodCB("set_json_flags", "{|s,v| s:__m__json_flags__ := nOr(v)  }");
      pc->Method_cbbs("json_escape_self", "{|s,mf,depth,pStack| XbFpCall(%i,s,s:__m__props__,s:__m__serial__,pStack,s, nOr(mf,s:__m__json_flags__),depth)   }", method_json_escape_self);
      // -----
      pc->MethodCB("m_unserialize_step", "{|s,v| s:__m__cargo__ := __vmask( 0x20,s:__m__cargo__,__anew()) , aadd( s:__m__cargo__ , v) , s }");
      pc->Method_cbbs("m_on_unserialize_pop", "{|s| XbFpCall(%i,s,@s:__m__props__,@s:__m__hash__,NIL,NIL,@s:__m__cargo__),s}", method_m_json_on_unserialize_pop);
      // -----

      // -----
      pc->MethodCB("_clone", "{|s| o := s:New(),o:__m__props__:= aclone(s:__m__props__),o:__m__hash__:=s:__m__hash__,o:__m__flags__:=s:__m__flags__,o }");
      // -----
      pc->MethodCB("_ToArray", "{|s,kk| kk := s:__m__hash__ , aclone(  s:__m__props__  ) }");
      pc->MethodCB("_GetArray", "{|s| s:__m__props__   }");
      // -----
      pc->ClassMethod_cbbs("from_xml", "{|s,uXml,dwFlags| XbFpCall(%i,s,uXml , dwFlags )}", mc_envelope_from_xml);

      pc->ClassMethod_cbbs("json_serialize", "{|s,v,moreflags,ndepth,pStack| XbFpCall(%i,v,moreflags,ndepth,pStack) }", json_ns::serialize);
      // -----

      conco = pc->Create();
      delete pc;
      if (conco == NULLCONTAINER)
      {
         _ret(pl);
         return;
      }

   }
   _conReturn(pl, conco);
   _conRelease(conco);
}
// ---------------------------------------------------------------------------------


END_NAMESPACE()

//----------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(_OT4XB_EXPANDO_)
{
         ot4xb_expando::create_class(pl);
}
// -----------------------------------------------------------------------------------------------------------------
