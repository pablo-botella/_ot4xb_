//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
#define PXERROR( n , m , d )  px->GenError();px->SetErrorSubSystem("ot4xb"); \
                              px->SetErrorOperation("THDict::"  ##m  "()"); \
                              px->SetErrorDescription( d ); \
                              px->SetErrorGenCode(0x00300000 + n);
// -----------------------------------------------------------------------------------------------------------------
static void hdict_add_env_strings(  THashTable * pht , LPSTR pEnvironment );
//----------------------------------------------------------------------------------------------------------------------
static  void* lock_hdict( THashTable * pHt )
{
   if( pHt )
   {
      if( pHt->m_cs_cargo )
      {
         EnterCriticalSection((CRITICAL_SECTION*) pHt->m_cs_cargo );
         return pHt->m_cs_cargo;
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
static  void* lock_hdict( THtcsTable* pHt )
{
   if( pHt )
   {
      if( pHt->m_cs_cargo )
      {
         EnterCriticalSection((CRITICAL_SECTION*) pHt->m_cs_cargo );
         return pHt->m_cs_cargo;
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
static  void unlock_hdict( void* cs )
{
   if( cs )
   {
      LeaveCriticalSection((CRITICAL_SECTION*) cs);
   }
}
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-note-id}}*/
/*{{note-id: thdict-legacy-api
            | title_: THDict low-level functions }}*/
/*{{|:
Low-level hash dictionary functions used internally by OT4XB and exposed for advanced code. A dictionary is
addressed by a numeric handle returned by _hdict_new() or _hdictcs_new(). This family is a legacy API, to be
deprecated: a few legacy or helper paths still use it as an implementation shortcut, but new code should prefer
the newer containers where possible. THDict is not the backing store for _ot4xb_expando_.

The _hdict_* functions work on the dictionaries of _hdict_new(), whose character keys are compared
case-insensitively using the OT4XB ANSI lower-case table. The _hdictcs_* functions work on the dictionaries of
_hdictcs_new(), whose keys are compared case-sensitively. The functions without a _hdictcs_* twin take the
case-insensitive handles of _hdict_new().

Character keys preserve their byte length. Numeric and date keys are converted to internal string keys. Values
are stored as internal typed entries owned by the dictionary and are converted back to Xbase++ values when
read. A dictionary created by the caller must be released with _hdict_destroy() or _hdictcs_destroy().
}}*/
/*{{end-note-id}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_new
            | syntax_: `_hdict_new( [@pOld] [, nBuckets] [, nMaxPopulation] [, lSync] )`
            | category: container/dictionary
            | _kw_: dictionary, hash table, key value, create, case insensitive, hdict
   }}*/
/*{{|desc: Creates a new case-insensitive dictionary and returns its handle. When pOld holds the handle
      of an existing dictionary, that dictionary is destroyed first and, when pOld is passed by
      reference, the variable receives the new handle.
    | params:
    - `pOld` Numeric pointer - Optional handle of a dictionary to replace, or 0.
    - `nBuckets` Numeric - Optional initial number of hash buckets, rounded up to a power of two
      with a minimum of 8. The table grows automatically while entries are added.
    - `nMaxPopulation` Numeric - Reserved for growth tuning; the current version ignores it.
    - `lSync` Logical - .T. creates a synchronized dictionary that can be shared between threads.

    Returns Numeric pointer - Handle of the new dictionary.

    |note: When pOld is a synchronized dictionary, the new one reuses its synchronization and lSync is
      ignored.

    |seealso: See also: {{ilink: <function _hdictcs_new> _hdictcs_new}} }}*/
XPPRET XPPENTRY _HDICT_NEW( XppParamList pl )// (pOld,nBuckets,nMaxPopulation,lSync) -> pTHashTable
{
   THashTable * pHt  = reinterpret_cast<THashTable *>(_parLong(pl,1));
   void* cs = 0;
   cs = lock_hdict(pHt);
   if( pHt )
   {
      delete pHt;
   }
   pHt = new THashTable((DWORD) _parLong(pl,2),(DWORD) _parLong(pl,3) );
   pHt->m_pfnOnDestroyItem = THDictItem::_OnDestroyItem_;
   if( _parl(pl,4) && ( cs == 0) )
   {
      pHt->m_cs_cargo = _xgrab(sizeof(CRITICAL_SECTION));
      InitializeCriticalSection( (CRITICAL_SECTION*) pHt->m_cs_cargo );
   }
   else
   {
      pHt->m_cs_cargo = cs;
   }
   _stornl((LONG) pHt , pl,1,0);
   _retnl( pl , (LONG) pHt );
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdictcs_new
            | syntax_: `_hdictcs_new( [@pOld] [, nBuckets] [, nMaxPopulation] [, lSync] )`
            | category: container/dictionary
            | _kw_: dictionary, hash table, key value, create, case sensitive, hdict
   }}*/
/*{{|desc: Creates a new case-sensitive dictionary and returns its handle. When pOld holds the handle of
      an existing dictionary, that dictionary is destroyed first and, when pOld is passed by reference,
      the variable receives the new handle.
    | params:
    - `pOld` Numeric pointer - Optional handle of a dictionary to replace, or 0.
    - `nBuckets` Numeric - Optional initial number of hash buckets, rounded up to a power of two
      with a minimum of 8. The table grows automatically while entries are added.
    - `nMaxPopulation` Numeric - Reserved for growth tuning; the current version ignores it.
    - `lSync` Logical - .T. creates a synchronized dictionary that can be shared between threads.

    Returns Numeric pointer - Handle of the new dictionary.

    |note: When pOld is a synchronized dictionary, the new one reuses its synchronization and lSync is
      ignored.

    |seealso: See also: {{ilink: <function _hdict_new> _hdict_new}} }}*/
XPPRET XPPENTRY _HDICTCS_NEW( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>(_parLong(pl,1));
   void* cs = 0;
   cs = lock_hdict(pHt);
   if( pHt )
   {
      delete pHt;
   }
   pHt = new THtcsTable((DWORD) _parLong(pl,2),(DWORD) _parLong(pl,3) );
   pHt->m_pfnOnDestroyItem = THDictItem::_OnDestroyItem_;
   if( _parl(pl,4) && ( cs == 0) )
   {
      pHt->m_cs_cargo = _xgrab(sizeof(CRITICAL_SECTION));
      InitializeCriticalSection( (CRITICAL_SECTION*) pHt->m_cs_cargo );
   }
   else
   {
      pHt->m_cs_cargo = cs;
   }
   _stornl((LONG) pHt , pl,1,0);
   _retnl( pl , (LONG) pHt );
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_destroy
            | syntax_: `_hdict_destroy( @pHt )`
            | category: container/dictionary
            | _kw_: dictionary, destroy, release, hdict
   }}*/
/*{{|desc: Destroys a case-insensitive dictionary and every entry stored in it. When pHt is passed by
      reference the variable is set to 0.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().

    Returns Numeric - Always 0.

    |note: For a synchronized dictionary the synchronization resources are released as well.

    |seealso: See also: {{ilink: <function _hdict_new> _hdict_new}} }}*/
XPPRET XPPENTRY _HDICT_DESTROY( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parLong(pl,1) );
   void* cs = 0;
   cs = lock_hdict(pHt);
   if( pHt ) delete pHt;
   _stornl(0,pl,1,0);
   _retnl(pl,0);
   if( cs )
   {
      DeleteCriticalSection((CRITICAL_SECTION*) cs );
      _xfree(cs);
   }
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdictcs_destroy
            | syntax_: `_hdictcs_destroy( @pHt )`
            | category: container/dictionary
            | _kw_: dictionary, destroy, release, case sensitive, hdict
   }}*/
/*{{|desc: Destroys a case-sensitive dictionary and every entry stored in it. When pHt is passed by
      reference the variable is set to 0.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdictcs_new().

    Returns Numeric - Always 0.

    |note: For a synchronized dictionary the synchronization resources are released as well.

    |seealso: See also: {{ilink: <function _hdictcs_new> _hdictcs_new}} }}*/
XPPRET XPPENTRY _HDICTCS_DESTROY( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parLong(pl,1) );
   void* cs = 0;
   cs = lock_hdict(pHt);
   if( pHt ) delete pHt;
   _stornl(0,pl,1,0);
   _retnl(pl,0);
   if( cs )
   {
      DeleteCriticalSection((CRITICAL_SECTION*) cs );
      _xfree(cs);
   }
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_key_compare
            | syntax_: `_hdict_key_compare( xKey1, xKey2 )`
            | category: container/dictionary
            | _kw_: dictionary, compare keys, case insensitive, hdict
   }}*/
/*{{|desc: Compares two key values with the rules a case-insensitive dictionary applies to its keys and
      returns .T. when both resolve to the same key.
    | params:
    - `xKey1` Character/Numeric/Date - First key value.
    - `xKey2` Character/Numeric/Date - Second key value.

    Returns Logical - .T. when both values resolve to the same dictionary key.

    |note: A value of any other type is not a valid key. Two invalid keys compare as equal, and a valid
      key never matches an invalid one.

    |seealso: See also: {{ilink: <function _hdictcs_key_compare> _hdictcs_key_compare}} }}*/
XPPRET XPPENTRY _HDICT_KEY_COMPARE( XppParamList pl )
{
   THDictKey* phk1  = THDictKey::FromPl(pl,1);
   THDictKey* phk2  = THDictKey::FromPl(pl,2);
   int iCmp = 0;
   if( phk1 && phk2 ) iCmp = THashTable::Compare(phk1->m_pKey,phk1->m_cbKey,0,phk2->m_pKey,phk2->m_cbKey,0);
   else if( phk1 || phk2 ) iCmp = 1;
   if( phk1 ) delete phk1;
   if( phk2 ) delete phk2;
   _retl(pl,(BOOL) ( iCmp == 0 ) );
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdictcs_key_compare
            | syntax_: `_hdictcs_key_compare( xKey1, xKey2 )`
            | category: container/dictionary
            | _kw_: dictionary, compare keys, case sensitive, hdict
   }}*/
/*{{|desc: Compares two key values with the rules a case-sensitive dictionary applies to its keys and
      returns .T. when both resolve to the same key.
    | params:
    - `xKey1` Character/Numeric/Date - First key value.
    - `xKey2` Character/Numeric/Date - Second key value.

    Returns Logical - .T. when both values resolve to the same dictionary key.

    |note: A value of any other type is not a valid key. Two invalid keys compare as equal, and a valid
      key never matches an invalid one.

    |seealso: See also: {{ilink: <function _hdict_key_compare> _hdict_key_compare}} }}*/
XPPRET XPPENTRY _HDICTCS_KEY_COMPARE( XppParamList pl )
{
   THDictKey* phk1  = THDictKey::FromPl(pl,1);
   THDictKey* phk2  = THDictKey::FromPl(pl,2);
   int iCmp = 0;
   if( phk1 && phk2 ) iCmp = THtcsTable::Compare(phk1->m_pKey,phk1->m_cbKey,0,phk2->m_pKey,phk2->m_cbKey,0);
   else if( phk1 || phk2 ) iCmp = 1;
   if( phk1 ) delete phk1;
   if( phk2 ) delete phk2;
   _retl(pl,(BOOL) ( iCmp == 0 ) );
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_setprop
            | syntax_: `_hdict_setprop( pHt, xKey, xValue )`
            | category: container/dictionary
            | _kw_: dictionary, set value, put, store key, hdict
   }}*/
/*{{|desc: Stores a value in a case-insensitive dictionary. When an entry with the same key already
      exists, its value is replaced.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().
    - `xKey` Character/Numeric/Date - Key to store the value under. Other types are not valid keys
      and leave the dictionary unchanged.
    - `xValue` Any - Value to store. Character, Numeric, Logical, Date and NIL values are stored as
      copies; values of any other type (Array, Object, CodeBlock) are kept as Xbase++ values, so an Array
      or Object stays shared with the caller.

    Returns NIL

    |seealso: See also: {{ilink: <function _hdict_getprop> _hdict_getprop}} }}*/
XPPRET XPPENTRY _HDICT_SETPROP( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);

   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         BOOL bByRef = FALSE;
         ContainerHandle con = _conParam(pl,3,&bByRef);
         THDictItem* phi = new THDictItem(phk,con);
         if( !bByRef ) _conRelease(con);
         if( phi )
         {
            phi->AddToHashTable( pHt );

         }
         delete phk;
      }
   }
   _ret(pl);
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdictcs_setprop
            | syntax_: `_hdictcs_setprop( pHt, xKey, xValue )`
            | category: container/dictionary
            | _kw_: dictionary, set value, put, store key, case sensitive, hdict
   }}*/
/*{{|desc: Stores a value in a case-sensitive dictionary. When an entry with the same key already
      exists, its value is replaced.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdictcs_new().
    - `xKey` Character/Numeric/Date - Key to store the value under. Other types are not valid keys
      and leave the dictionary unchanged.
    - `xValue` Any - Value to store. Character, Numeric, Logical, Date and NIL values are stored as
      copies; values of any other type (Array, Object, CodeBlock) are kept as Xbase++ values, so an Array
      or Object stays shared with the caller.

    Returns NIL

    |seealso: See also: {{ilink: <function _hdictcs_getprop> _hdictcs_getprop}} }}*/
XPPRET XPPENTRY _HDICTCS_SETPROP( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         BOOL bByRef = FALSE;
         ContainerHandle con = _conParam(pl,3,&bByRef);
         THDictItem* phi = new THDictItem(phk,con);
         if( !bByRef ) _conRelease(con);
         if( phi )
         {
            phi->AddToHashTable( pHt );

         }
         delete phk;
      }
   }
   _ret(pl);
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static void hdict_add_env_strings(  THashTable * pht , LPSTR pEnvironment )
{
   void* cs = 0;   
   cs = lock_hdict(pht);

   if (pht && pEnvironment)
   {
      LPSTR p = pEnvironment;
      while (*p)
      {
         UINT  cb = 0;
         UINT  ns = 0;
         for (; p[cb]; cb++)
         {
            if ((!ns) && (p[cb] == '='))
            {
               if (cb) { ns = cb; }
            }
         }
         if ((((int)ns) > 0) && (cb > 2) && (cb > (ns + 1)))
         {
            THDictItem* phi = new THDictItem(p, ns, _mk_ptr_(LPSTR, p, (ns + 1)), cb - (ns + 1), TRUE);
            phi->AddToHashTable(pht);
         }
         p = _mk_ptr_(LPSTR, p, cb + 1);
      }
   }
   unlock_hdict(cs);
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_add_env_strings
            | syntax_: `_hdict_add_env_strings( pHt [, pEnvironment] )`
            | category: container/dictionary
            | _kw_: dictionary, environment variables, getenv, hdict
   }}*/
/*{{|desc: Adds environment variables to a case-insensitive dictionary, one Character entry per variable,
      keyed by the variable name. When pEnvironment is omitted or 0, the environment block of the current
      process is used and released internally.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().
    - `pEnvironment` Numeric pointer - Optional Windows environment block: "name=value" strings each
      followed by Chr(0), with an extra Chr(0) closing the list.

    Returns NIL

    |note: Variables with an empty value are skipped. Existing entries with the same name are replaced. }}*/
_XPP_REG_FUN_( _HDICT_ADD_ENV_STRINGS  )
{
   TXppParamList xpp(pl,2);
   THashTable * pht  = reinterpret_cast<THashTable *>( xpp[1]->GetLong() );
   LPSTR p = (LPSTR) xpp[2]->GetDWord();
   BOOL bReleaseEnvBlock = (BOOL) ( p ? 0 : 1 );
   if( bReleaseEnvBlock )
   {
       p = GetEnvironmentStrings();
   }
   hdict_add_env_strings( pht , p);
   if( bReleaseEnvBlock &&  p)
   {
      FreeEnvironmentStrings(p);
   }
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_from_zkdw
            | syntax_: `_hdict_from_zkdw( pHt, cZkdw )`
            | category: container/dictionary
            | _kw_: dictionary, ZKDW, import records, hdict
   }}*/
/*{{|desc: Imports a ZKDW buffer into a case-insensitive dictionary. Each record holds a 4-byte integer
      value, a 4-byte key length and the key bytes; every record becomes an integer Numeric entry stored
      under its Character key. Parsing stops at the first record that does not fit in the remaining bytes.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().
    - `cZkdw` Character - ZKDW buffer, usually produced by _hdict_iterate_cb() with operation 5.

    Returns Numeric - Number of entries imported.

    |seealso: See also: {{ilink: <function _hdict_iterate_cb> _hdict_iterate_cb}} }}*/
_XPP_REG_FUN_( _HDICT_FROM_ZKDW )
{
   TXppParamList xpp(pl,2);
   THashTable * pht  = reinterpret_cast<THashTable *>( xpp[1]->GetLong() );
   void* cs = 0;   cs = lock_hdict(pht);
   DWORD item_count = 0;
   if( pht )
   {
      DWORD  cb = 0;
      LPBYTE p  = (LPBYTE) xpp[2]->LockStr(&cb);
      while( cb > 8 )
      {
         DWORD value = _mk_ptr_(LPDWORD,p,0)[0];
         DWORD keycb = _mk_ptr_(LPDWORD,p,0)[1];
         cb -= 8;
         p   = _mk_ptr_(LPBYTE,p, 8 );
         if( (keycb <= cb) && ( keycb ) )
         {
            THDictItem* phi = new THDictItem((LPSTR) p,(UINT) keycb, value , TRUE );
            phi->AddToHashTable( pht);
            p   = _mk_ptr_(LPBYTE,p, keycb );
            cb -= keycb;
            item_count++;
         }
         else
         {
            cb = 0;
         }
      }
   }
   unlock_hdict(cs);
   xpp[0]->PutDWord(item_count);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_getprop
            | syntax_: `_hdict_getprop( pHt, xKey )`
            | category: container/dictionary
            | _kw_: dictionary, get value, lookup key, hdict
   }}*/
/*{{|desc: Returns the value stored under a key in a case-insensitive dictionary.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().
    - `xKey` Character/Numeric/Date - Key to look up.

    Returns Any - Stored value, or NIL when the key does not exist or the parameters are not valid.

    |note: A stored NIL value and a missing key both return NIL; use _hdict_isprop() to tell them apart.

    |seealso: See also: {{ilink: <function _hdict_setprop> _hdict_setprop}}

    |seealso: See also: {{ilink: <function _hdict_isprop> _hdict_isprop}} }}*/
XPPRET XPPENTRY _HDICT_GETPROP( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   ContainerHandle conr = _conNew(NULLCONTAINER);
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         THDictItem* phi = phk->Find( pHt );
         if( phi ) phi->ConPutValue(conr);
         delete phk;
      }
   }
   _conReturn(pl,conr); _conRelease(conr);
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdictcs_getprop
            | syntax_: `_hdictcs_getprop( pHt, xKey )`
            | category: container/dictionary
            | _kw_: dictionary, get value, lookup key, case sensitive, hdict
   }}*/
/*{{|desc: Returns the value stored under a key in a case-sensitive dictionary.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdictcs_new().
    - `xKey` Character/Numeric/Date - Key to look up.

    Returns Any - Stored value, or NIL when the key does not exist or the parameters are not valid.

    |note: A stored NIL value and a missing key both return NIL; use _hdictcs_isprop() to tell them
      apart.

    |seealso: See also: {{ilink: <function _hdictcs_setprop> _hdictcs_setprop}}

    |seealso: See also: {{ilink: <function _hdictcs_isprop> _hdictcs_isprop}} }}*/
XPPRET XPPENTRY _HDICTCS_GETPROP( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   ContainerHandle conr = _conNew(NULLCONTAINER);
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         THDictItem* phi = phk->Find( pHt );
         if( phi ) phi->ConPutValue(conr);
         delete phk;
      }
   }
   _conReturn(pl,conr); _conRelease(conr);
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_isprop
            | syntax_: `_hdict_isprop( pHt, xKey )`
            | category: container/dictionary
            | _kw_: dictionary, key exists, contains, hdict
   }}*/
/*{{|desc: Checks whether a key exists in a case-insensitive dictionary.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().
    - `xKey` Character/Numeric/Date - Key to look up.

    Returns Logical - .T. when the key exists, .F. otherwise or when the parameters are not valid.

    |seealso: See also: {{ilink: <function _hdict_getprop> _hdict_getprop}} }}*/
XPPRET XPPENTRY _HDICT_ISPROP( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   BOOL b = FALSE;
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         THDictItem* phi = phk->Find( pHt );
         if( phi ){ b = TRUE; }
         delete phk;
      }
   }
   _retl(pl,b);
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdictcs_isprop
            | syntax_: `_hdictcs_isprop( pHt, xKey )`
            | category: container/dictionary
            | _kw_: dictionary, key exists, contains, case sensitive, hdict
   }}*/
/*{{|desc: Checks whether a key exists in a case-sensitive dictionary.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdictcs_new().
    - `xKey` Character/Numeric/Date - Key to look up.

    Returns Logical - .T. when the key exists, .F. otherwise or when the parameters are not valid.

    |seealso: See also: {{ilink: <function _hdictcs_getprop> _hdictcs_getprop}} }}*/
XPPRET XPPENTRY _HDICTCS_ISPROP( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   BOOL b = FALSE;
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         THDictItem* phi = phk->Find( pHt );
         if( phi ){ b = TRUE; }
         delete phk;
      }
   }
   _retl(pl,b);
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_getprop_raw_
            | syntax_: `_hdict_getprop_raw_( pHt, xKey )`
            | category: container/dictionary
            | _kw_: dictionary, item address, internal item, hdict
   }}*/
/*{{|desc: Returns the address of the internal item that stores a key in a case-insensitive dictionary.
      This is an internal/diagnostic entry point.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().
    - `xKey` Character/Numeric/Date - Key to look up.

    Returns Numeric pointer - Address of the internal item, or 0 when the key does not exist.

    |note: The item belongs to the dictionary; the address becomes invalid as soon as the entry is
      replaced or removed or the dictionary is destroyed. }}*/
XPPRET XPPENTRY _HDICT_GETPROP_RAW_( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         _retnl(pl,(LONG) phk->Find( pHt ) );
         delete phk;
         goto TheEnd;
      }
   }
   _retnl(pl,0);
   TheEnd:;
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_removeprop
            | syntax_: `_hdict_removeprop( pHt, xKey )`
            | category: container/dictionary
            | _kw_: dictionary, remove key, delete entry, hdict
   }}*/
/*{{|desc: Removes an entry from a case-insensitive dictionary.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().
    - `xKey` Character/Numeric/Date - Key of the entry to remove.

    Returns Logical - .T. when the entry existed and was removed, .F. otherwise.

    |seealso: See also: {{ilink: <function _hdict_removeall> _hdict_removeall}} }}*/
XPPRET XPPENTRY _HDICT_REMOVEPROP( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   BOOL bOk = FALSE;
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         bOk = pHt->DeleteItem(phk->m_pKey , phk->m_cbKey);
         delete phk;
      }
   }
   _retl(pl,bOk);
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdictcs_removeprop
            | syntax_: `_hdictcs_removeprop( pHt, xKey )`
            | category: container/dictionary
            | _kw_: dictionary, remove key, delete entry, case sensitive, hdict
   }}*/
/*{{|desc: Removes an entry from a case-sensitive dictionary.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdictcs_new().
    - `xKey` Character/Numeric/Date - Key of the entry to remove.

    Returns Logical - .T. when the entry existed and was removed, .F. otherwise.

    |seealso: See also: {{ilink: <function _hdictcs_removeall> _hdictcs_removeall}} }}*/
XPPRET XPPENTRY _HDICTCS_REMOVEPROP( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parLong(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   BOOL bOk = FALSE;
   if( pHt )
   {
      THDictKey* phk  = THDictKey::FromPl(pl,2);
      if( phk )
      {
         bOk = pHt->DeleteItem(phk->m_pKey , phk->m_cbKey);
         delete phk;
      }
   }
   _retl(pl,bOk);
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_removeall
            | syntax_: `_hdict_removeall( pHt )`
            | category: container/dictionary
            | _kw_: dictionary, clear, remove all, hdict
   }}*/
/*{{|desc: Removes every entry from a case-insensitive dictionary. The dictionary itself remains usable.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().

    Returns NIL

    |seealso: See also: {{ilink: <function _hdict_destroy> _hdict_destroy}} }}*/
XPPRET XPPENTRY _HDICT_REMOVEALL( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parnl(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   if( pHt ) pHt->DeleteAllItems();
   _ret(pl);
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdictcs_removeall
            | syntax_: `_hdictcs_removeall( pHt )`
            | category: container/dictionary
            | _kw_: dictionary, clear, remove all, case sensitive, hdict
   }}*/
/*{{|desc: Removes every entry from a case-sensitive dictionary. The dictionary itself remains usable.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdictcs_new().

    Returns NIL

    |seealso: See also: {{ilink: <function _hdictcs_destroy> _hdictcs_destroy}} }}*/
XPPRET XPPENTRY _HDICTCS_REMOVEALL( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parnl(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   if( pHt ) pHt->DeleteAllItems();
   _ret(pl);
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_count
            | syntax_: `_hdict_count( pHt )`
            | category: container/dictionary
            | _kw_: dictionary, count, number of entries, hdict
   }}*/
/*{{|desc: Returns the number of entries stored in a case-insensitive dictionary.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().

    Returns Numeric - Number of entries, or NIL when pHt is 0. }}*/
XPPRET XPPENTRY _HDICT_COUNT( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parnl(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   if( pHt ){ _retnl(pl,pHt->m_nCount); goto TheEnd;}
   _ret(pl);
   TheEnd:;
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdictcs_count
            | syntax_: `_hdictcs_count( pHt )`
            | category: container/dictionary
            | _kw_: dictionary, count, number of entries, case sensitive, hdict
   }}*/
/*{{|desc: Returns the number of entries stored in a case-sensitive dictionary.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdictcs_new().

    Returns Numeric - Number of entries, or NIL when pHt is 0. }}*/
XPPRET XPPENTRY _HDICTCS_COUNT( XppParamList pl )
{
   THtcsTable * pHt  = reinterpret_cast<THtcsTable *>( _parnl(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   if( pHt ){ _retnl(pl,pHt->m_nCount); goto TheEnd;}
   _ret(pl);
   TheEnd:;
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_iterate_step
            | syntax_: `_hdict_iterate_step( pHt, @pIterator, @xValue, @cKey [, pFilter] )`
            | category: container/dictionary
            | _kw_: dictionary, iterate, next entry, iterator, hdict
   }}*/
/*{{|desc: Returns the entries of a case-insensitive dictionary one call at a time. Start with pIterator
      containing 0; while the function returns .T., xValue and cKey hold the current entry and pIterator
      the position for the next call. At the end the reference parameters are cleared and .F. is
      returned.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new(). Synchronized dictionaries
      are not supported: the function generates a runtime error for them.
    - `pIterator` Numeric pointer by reference - Iteration cursor. Pass 0 to start from the first
      entry.
    - `xValue` Any by reference - Receives the value of the current entry.
    - `cKey` Character by reference - Receives the key of the current entry.
    - `pFilter` Numeric pointer - Optional filter: a memory block holding a 4-byte callback address,
      a 4-byte text length and the text bytes. The callback receives ( pKey, cbKey, pText, cbText ) and
      entries are skipped while it returns 0.

    Returns Logical - .T. when an entry was delivered, .F. when the iteration is finished.

    |note: Do not add or remove entries between steps: pIterator addresses the internal entry, and
      removing it leaves the cursor pointing to freed memory.

    |seealso: See also: {{ilink: <function _hdict_iterate_cb> _hdict_iterate_cb}} }}*/
XPPRET XPPENTRY _HDICT_ITERATE_STEP( XppParamList pl )
{
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parnl(pl,1) );
   THashItem*   pItem  = reinterpret_cast<THashItem*>( _parnl(pl,2) );
   void* filter = reinterpret_cast<void*>( _parnl(pl,5,0) );
   LPSTR filter_string = 0;
   DWORD filter_cb     = 0;
   _PFN_HDICT_FILTER_ filter_fp = 0;
   if( pHt->m_cs_cargo )
   {
         TXbGenError e;
         e.subsystem( "OT4XB" );
         e.description("Operation not supported on Syncronized hash tables.");
         e.gencode(-1);
         e.operation( __FUNCTION__ );
         e.Launch();
         _ret(pl);
         return;
   }
   if( pHt )
   {

      if( !pItem ) pItem = pHt->m_pFirstItem;
      else pItem = pItem->m_pNext;

      if( filter && pItem  )
      {
         filter_fp = reinterpret_cast<_PFN_HDICT_FILTER_*>(filter)[0];
         filter_cb = reinterpret_cast<DWORD*>(filter)[1];
         filter_string = _mk_ptr_(LPSTR,filter,8);
         if( !(filter_fp && filter_string && filter_cb) ){ goto label_end_filter; }

         for( ; pItem ; pItem = pItem->m_pNext )
         {
            if( (*filter_fp)(pItem->m_pKey,pItem->m_cbKey,filter_string,filter_cb) )
            {
               goto label_end_filter;
            }
         }
      }
      label_end_filter: ;

      if( pItem )
      {
         THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
         if( phi )
         {
            BOOL bByRef = 0;
            ContainerHandle conItem = _conParam(pl,3,&bByRef);
            if( conItem && bByRef ) phi->ConPutValue(conItem);
            if( !bByRef ) _conRelease(conItem);
         }
         else _stor(pl,3,0);
         _stornl((LONG) pItem,pl,2,0);
         _storclen(pItem->m_pKey,pItem->m_cbKey,pl,4,0);
         _retl(pl,1);
         return;
      }
   }
   _stor(pl,2,0);
   _stor(pl,3,0);
   _stor(pl,4,0);
   _retl(pl,0);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// _HDICT_ITERATE_CB( pHt, cb , @cargo){|pos,key,val,cargo|lContinue } -> nCount
// TODO: _HDICT_ITERATE_CB() document new extra usage of the second param
// _HDICT_ITERATE_CB( pHt, 1 ) -> aKeys
// _HDICT_ITERATE_CB( pHt, 2 ) -> aValues
// _HDICT_ITERATE_CB( pHt, 3 , [3 @hashstr] ) -> { {key1,value1},...,{keyN,valueN} }
// _HDICT_ITERATE_CB( pHt, 4 , @cb ) ->  LPSTR pEnvironment
// _HDICT_ITERATE_CB( pHt, 5 , default_value ) ->  ZKDW string
// _HDICT_ITERATE_CB( pHt, 6 , default_value ) ->  RESET ZKDW TO DEFAULT VALUE

// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_iterate_cb
            | syntax_: `_hdict_iterate_cb( pHt, bEval [, xCargo] ) / _hdict_iterate_cb( pHt, nOp [, @xExtra] )`
            | category: container/dictionary
            | _kw_: dictionary, iterate, code block, export, for each, hdict
   }}*/
/*{{|desc: Iterates or exports a case-insensitive dictionary. When the second parameter is a CodeBlock
      it is evaluated as Eval( bEval, nPos, cKey, xValue, xCargo ) for every entry until it returns .F.,
      and the function returns the number of entries visited. When the second parameter is Numeric, one
      of the operations below runs instead.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().
    - `bEval` CodeBlock - Evaluated once per entry with the position, the key, the value and xCargo.
    - `xCargo` Any - Value passed as the fourth argument to every evaluation of bEval.
    - `nOp` Numeric - Operation to run, see below. xExtra is operation-dependent.
    | ops:
    - `1` returns an Array with the keys
    - `2` returns an Array with the values
    - `3` returns an Array of { cKey, xValue } pairs; when @xExtra is supplied it receives a Character
      buffer with a 4-byte checksum per key, in the same order as the pairs
    - `4` builds a buffer with the Character entries laid out as name, Chr(0), value, Chr(0) and four
      closing Chr(0) bytes, and returns its address; a third parameter is required and receives the byte
      size when passed by reference; release the buffer with _xfree(). Only entries whose value is a
      non-empty string are included
    - `5` returns the entries encoded as a ZKDW Character buffer, see _hdict_from_zkdw()
    - `6` resets every entry to an integer Numeric value, xExtra when it is Numeric or 0, and returns
      NIL

    Returns Numeric, Array, Character, Numeric pointer or NIL, depending on the second parameter.

    |note: Operation 5 writes the value of the entries that hold an integer Numeric value. Entries
      holding a Numeric value stored as a double are written with value 0. Entries of any other type are
      written with the xExtra value when it is Numeric, otherwise they are left out.

    |seealso: See also: {{ilink: <function _hdict_iterate_step> _hdict_iterate_step}}

    |seealso: See also: {{ilink: <function _hdict_from_zkdw> _hdict_from_zkdw}} }}*/
XPPRET XPPENTRY _HDICT_ITERATE_CB( XppParamList pl )
{
   ULONG nOp = ( (_partype(pl,2) & XPP_NUMERIC) ? _parLong(pl,2,0) : 0 );
   THashTable * pHt  = reinterpret_cast<THashTable *>( _parnl(pl,1) );
   void* cs = 0; cs = lock_hdict(pHt);
   LONG nCount = 0;
   if( pHt )
   {
      switch( nOp )
      {
         case 0:
         {
            BOOL bBlockByRef = FALSE;
            ContainerHandle conb = _conTParam( pl,2,&bBlockByRef,XPP_BLOCK);
            if( conb )
            {
               BOOL bCargoByRef = FALSE;
               ContainerHandle conCargo = _conParam( pl,3,&bCargoByRef);
               ContainerHandle conPos   = _conNew(NULLCONTAINER);
               ContainerHandle conKey   = _conNew(NULLCONTAINER);
               ContainerHandle conValue = _conNew(NULLCONTAINER);
               ContainerHandle conr     = _conNew(NULLCONTAINER);
               THashItem* pItem = pHt->m_pFirstItem;
               while( pItem )
               {
                  BOOL bContinue = TRUE;
                  THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
                  nCount++; _conPutNL(conPos,nCount);
                  _conPutCL(conKey,pItem->m_pKey,pItem->m_cbKey);
                  if( phi ) phi->ConPutValue(conValue); else _conPut(conValue,NULLCONTAINER);
                  _conEvalB(conr,conb,4,conPos,conKey,conValue,conCargo);
                  if( _conCheckType(conr, XPP_LOGICAL) ) _conGetL(conr,&bContinue);
                  if( bContinue ) pItem = pItem->m_pNext;
                  else pItem = 0;
               }
               _conReleaseM( conr,conPos,conKey,conValue,0);
               if(!bCargoByRef ) _conRelease( conCargo);
               if(!bBlockByRef ) _conRelease( conb );
            }
            break;
         }
         case 1: // array with keys
         {
            ContainerHandle cona = _conNewArray(1,pHt->m_nCount);
            THashItem* pItem = pHt->m_pFirstItem;
            while( pItem )
            {
               nCount++;
               _conArrayPutCL(cona,pItem->m_pKey,pItem->m_cbKey,nCount,0);
               pItem = pItem->m_pNext;
            }
            _conReturn(pl,cona);
            _conRelease(cona);
            goto TheEnd;
         }
         case 2: // array with values
         {
            ContainerHandle cona = _conNewArray(1,pHt->m_nCount);
            THashItem* pItem = pHt->m_pFirstItem;
            while( pItem )
            {
               THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
               nCount++;
               if( phi )
               {
                  ContainerHandle con_value = phi->ConPutValue();
                  _conArrayPut(cona,con_value,nCount,0);
                  _conRelease( con_value );
               }
               pItem = pItem->m_pNext;
            }
            _conReturn(pl,cona);
            _conRelease(cona);
            goto TheEnd;
         }
         case 3: // array with { key,values}
         {
            ContainerHandle cona = _conNewArray(2,pHt->m_nCount,2);
            THashItem* pItem = pHt->m_pFirstItem;
            DWORD* pdwcrc = 0;

            if( _partype(pl,0) >= 3 )
            {
               pdwcrc = (DWORD*) _xgrab( (pHt->m_nCount + 1 ) * sizeof(DWORD) );
            }

            while( pItem )
            {
               THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
               if( pdwcrc )
               {
                  pdwcrc[nCount] = pItem->m_dwCrc;
               }
               nCount++;
               _conArrayPutCL(cona,pItem->m_pKey,pItem->m_cbKey,nCount,1,0);
               if( phi )
               {
                  ContainerHandle con_value = phi->ConPutValue();
                  _conArrayPut(cona,con_value,nCount,2,0);
                  _conRelease( con_value );
               }
               pItem = pItem->m_pNext;
            }

            if( pdwcrc )
            {
               _storclen((LPSTR) pdwcrc, (ULONG) (pHt->m_nCount * sizeof(DWORD)),pl,3,0);
               _xfree( (void*) pdwcrc );
               pdwcrc = 0;
            }
            _conReturn(pl,cona);
            _conRelease(cona);
            goto TheEnd;
         }
         case 4: // -> LPSTR pEnvBlock
         {
            if( _partype(pl,0) < 3 ){ _ret(pl); goto TheEnd; }
            TByteStream z;
            THashItem* pItem = pHt->m_pFirstItem;
            DWORD dwzero = 0;
            while( pItem )
            {
               THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
               if( phi )
               {
                  if( (phi->m_nDataType == THDictItem::hdi_str) && phi->m_dwDataSize )
                  {
                     z.Add( (LPBYTE) phi->m_pKey );
                     z.Add( (LPBYTE) &dwzero , 1 );
                     z.Add( (LPBYTE) phi->m_pData );
                     z.Add( (LPBYTE) &dwzero , 1 );
                  }
               }
               pItem = pItem->m_pNext;
            }
            z.Add( (LPBYTE) &dwzero , 4 );
            UINT cb = 0;
            LPBYTE p  = z.Detach(&cb);
            _stornl((LONG) cb,pl,3,0);
            _retnl(pl,(LONG) p );
            goto TheEnd;
         }
         case 5: // ZKDW string
         {
            TByteStream s(65536,65536);
            THashItem* pItem = pHt->m_pFirstItem;
            BOOL  bDefaultValue = ( _partype(pl,3) & XPP_NUMERIC );
            DWORD dwDefault = (DWORD) ( bDefaultValue ? _parLong(pl,3,0) : 0 );
            while( pItem )
            {
               THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
               if( phi )
               {
                  switch( phi->m_nDataType )
                  {
                     case THDictItem::hdi_int :
                     {
                        s.append_DWORD( phi->m_dwExtra );
                        s.append_DWORD( phi->m_cbKey   );
                        s.Add( (LPBYTE) phi->m_pKey , phi->m_cbKey );
                        break;
                     }
                     case THDictItem::hdi_double:
                     {
                        double nd = 0.00;
                        if( (phi->m_dwDataSize == sizeof(double)) && phi->m_pData )
                        {
                           nd = reinterpret_cast<double*>( phi->m_pData )[0];
                        }
                        s.append_DWORD( phi->m_dwExtra );
                        s.append_DWORD( phi->m_cbKey   );
                        s.Add( (LPBYTE) phi->m_pKey , phi->m_cbKey );
                        break;
                     }
                     default:
                     {
                        if( bDefaultValue )
                        {
                           s.append_DWORD( dwDefault );
                           s.append_DWORD( phi->m_cbKey   );
                           s.Add( (LPBYTE) phi->m_pKey , phi->m_cbKey );
                           break;
                        }
                        break;
                     }
                  }

               }
               pItem = pItem->m_pNext;
            }
            ContainerHandle conr = _conPutCL( NULLCONTAINER , (LPSTR) s.GetBuffer() , s.len() );
            _conReturn(pl,conr);
            _conRelease(conr);
            goto TheEnd;
         }
         case 6: // reset ZKDW table
         {
            THashItem* pItem = pHt->m_pFirstItem;
            BOOL  bDefaultValue = ( _partype(pl,3) & XPP_NUMERIC );
            DWORD dwDefault = (DWORD) ( bDefaultValue ? _parLong(pl,3,0) : 0 );
            while( pItem )
            {
               THDictItem* phi = reinterpret_cast<THDictItem*>(pItem->m_pData);
               if( phi )
               {
                  if( phi->m_pData )
                  {
                     _xfree( phi->m_pData );
                     phi->m_pData = 0;
                  }
                  if( phi->m_nDataType == THDictItem::hdi_xbase && phi->m_dwExtra )
                  {
                     _conRelease( (ContainerHandle) phi->m_dwExtra );
                     phi->m_dwExtra = 0;
                  }
                  phi->m_pData       = 0;
                  phi->m_dwExtra     = dwDefault;
                  phi->m_nDataType   = THDictItem::hdi_int;
                  phi->m_dwDataSize  = sizeof(LONG);
               }
               pItem = pItem->m_pNext;
            }
            _ret(pl);
            goto TheEnd;
         }
      }
   }
   _retnl(pl,nCount);
   TheEnd: ;
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_addpropfromarray
            | syntax_: `_hdict_addpropfromarray( pHt, aPairs )`
            | category: container/dictionary
            | _kw_: dictionary, from array, key value pairs, hdict
   }}*/
/*{{|desc: Adds entries to a case-insensitive dictionary from an array of { xKey, xValue } pairs. The
      first element of each pair is the key; the second, when present, is the value (NIL otherwise).
      Existing entries with the same key are replaced.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().
    - `aPairs` Array - Array whose elements are arrays of the form { xKey [, xValue] }. Elements
      that are not arrays, or whose first element is not a valid key, are skipped.

    Returns NIL

    |note: The pair layout matches the array returned by _hdict_iterate_cb() with operation 3.

    |seealso: See also: {{ilink: <function _hdict_iterate_cb> _hdict_iterate_cb}} }}*/
XPPRET XPPENTRY _HDICT_ADDPROPFROMARRAY( XppParamList pl )
{
   TXppParamList xpp(pl,1);
   THashTable * pht  = reinterpret_cast<THashTable *>( xpp[1]->GetLong() );
   void* cs = 0; cs = lock_hdict(pht);
   if(pht && xpp[2]->CheckType(XPP_ARRAY) )
   {
      ContainerHandle cona = xpp[2]->Get();
      ULONG nItems = _conGetArrayLen(cona);
      ULONG n;
      for( n=1; n <= nItems; n++ )
      {
         ULONG nType = 0;
         _conTypeA(cona,&nType,n,0);
         if( nType & XPP_ARRAY )
         {
            ULONG nn = 0;
            _conSizeA(cona,&nn,n,0);
            if( nn > 0 )
            {
               THDictKey* phk  = 0;
               ContainerHandle con_k = _conNew(NULLCONTAINER);
               _conArrayGet(cona,con_k,n,1,0);
               phk  = THDictKey::FromXbItem(con_k);
               _conRelease(con_k);
               if( phk )
               {
                  THDictItem* phi = 0;
                  ContainerHandle con_v = _conNew(NULLCONTAINER);
                  if( nn > 1 ){ _conArrayGet(cona,con_v,n,2,0); }
                  phi = new THDictItem(phk,con_v);
                  if( phi ){phi->AddToHashTable(pht);}
                  delete phk;
                  _conRelease(con_v);
               }
            }
         }
      }
   }
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_add_http_headers
            | syntax_: `_hdict_add_http_headers( pHt, cHeaders )`
            | category: container/dictionary
            | _kw_: dictionary, http headers, parse headers, hdict
   }}*/
/*{{|desc: Parses HTTP-style header text and adds one Character entry per "Name: value" line to a
      case-insensitive dictionary. Lines are separated by CR and/or LF; blanks between the name and the
      colon and around the value are ignored.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().
    - `cHeaders` Character - Header lines formatted as "Name: value".

    Returns NIL

    |note: A line without a colon becomes an entry with an empty value. Repeated header names keep the
      last value. Continuation lines starting with blanks are not joined to the previous header. }}*/
_XPP_REG_FUN_( _HDICT_ADD_HTTP_HEADERS )
{
   TXppParamList xpp(pl,1);
   THashTable * pht  = reinterpret_cast<THashTable *>( xpp[1]->GetLong() );
   void* cs = 0; cs = lock_hdict(pht);
   LPSTR p = xpp[2]->LockStrEx();
   if (pht && p)
   {

      LPSTR k = 0;
      DWORD kcb = 0;
      DWORD ksp = 0; // spaces after the key
      LPSTR v = 0;
      DWORD vcb = 0;
      DWORD vsp = 0; // spaces after the value
      int status = 0; // 0 CRLF; 1 key ; 2 value blank ; 3 value ; 4 invalid
      char ch = 0;

      for (; *p; p++)
      {
         switch (*p)
         {
         case 0x0A:;
         case 0x0D:
         {
            kcb = kcb - ksp; ksp = 0;
            vcb = vcb - vsp; vsp = 0;
            if (kcb)
            {
               if (!vcb) { v = &ch; }
               THDictItem* phi = new THDictItem(k, kcb, v, vcb, TRUE);
               phi->AddToHashTable(pht);
            }
            k = 0; kcb = 0; v = 0; vcb = 0;
            status = 0;
            break;
         }
         case 0x20:
         {
            switch (status)
            {
            case 0: { status = 1; k = p; kcb = 1; ksp = 1; v = 0; vcb = 0; break; }
            case 1: { kcb++; ksp++; break; }
            case 2: { vcb = 1; v = p; vsp = 0; break; }
            case 3: { vcb++; vsp++; break; }
            }
            break;


         }
         case ':':
         {
            kcb = kcb - ksp; ksp = 0;
            if (!kcb) { status = 0; }
            switch (status)
            {
            case 0: { status = 4; k = 0; kcb = 0; ksp = 0; v = 0; vcb = 0; vsp = 0; break; }
            case 1: { status = 2; vcb = 0; v = _mk_ptr_(LPSTR, p, 1); break; }
            case 2: { status = 3; vcb = 1; v = p; vsp = 0; break; }
            case 3: { vcb++; break; }
            }
            break;
         }
         default:
         {
            switch (status)
            {
            case 0: { status = 1; k = p; kcb = 1; ksp = 0; v = 0; vcb = 0; vsp = 0; break; }
            case 1: { ksp = 0; kcb++; break; }
            case 2: { status = 3; v = p; vcb = 1; vsp = 0; break; }
            case 3: { vsp = 0; vcb++; break; }
            }
            break;
         }
         }
      }
      if ((status > 0) && (status < 4))
      {
         kcb = kcb - ksp; ksp = 0;
         vcb = vcb - vsp; vsp = 0;
         if (kcb)
         {
            if (!vcb) { v = &ch; }
            THDictItem* phi = new THDictItem(k, kcb, v, vcb, TRUE);
            phi->AddToHashTable(pht);
         }
      }
   }
   unlock_hdict(cs);
}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _hdict_addpropfroministring
            | syntax_: `_hdict_addpropfroministring( pHt, cIniText, nFlags )`
            | category: container/dictionary
            | _kw_: dictionary, ini, key=value, parse ini, hdict
   }}*/
/*{{|desc: Parses INI-style text and adds one Character entry per "key=value" line to a case-insensitive
      dictionary. Lines whose first non-blank character is ";" are comments, and "[section]" lines set
      the current section, used according to nFlags. Keys and section names are always trimmed.
    | params:
    - `pHt` Numeric pointer - Dictionary handle returned by _hdict_new().
    - `cIniText` Character - Text to parse, usually the content of an .ini file.
    - `nFlags` Numeric - Combination of the flags below; with 0, section lines are ignored.
    | flags:
    - `0x0001` prefix each key with the current section name, as in section\key
    - `0x0002` trim blanks around the values
    - `0x0004` with flag 0x0001, return an Array with the section names

    Returns Array/NIL - Array with the section names when nFlags contains both 0x0001 and 0x0004, NIL
      otherwise.

    |note: A line without "=" becomes an entry with an empty value. Empty lines are skipped. Existing
      entries with the same key are replaced. }}*/
_XPP_REG_FUN_( _HDICT_ADDPROPFROMINISTRING )
{

   TXppParamList xpp(pl,3);
   THashTable * pht  = reinterpret_cast<THashTable *>( xpp[1]->GetLong() );
   void* cs = 0; cs = lock_hdict(pht);
   DWORD dwFlags = xpp[3]->GetDWord();
   TList* pSectionList = 0;
   if( (dwFlags & 5) == 5 )
   {
      pSectionList = new TList;
   }


   if(pht && xpp[2]->CheckType(XPP_CHARACTER) )
   {
      LPSTR  pStr  = xpp[2]->StrDupA();
      TList* pList = TxtSplitLinesToTList(pStr,0x13);
      if( pList )
      {
         BYTE bt[256]; ZeroMemory(bt,256);
         bt[9] = bt[10] = bt[13] = bt[32] = 1;
         LPSTR pLastSection = 0;
         DWORD cbLastSection = 0;
         DWORD nCount = pList->Count();
         DWORD nItem;
         for( nItem = 0; nItem < nCount ; nItem++ )
         {
            LPSTR k = (LPSTR) pList->Get(nItem);
            if( k[0] == '[' )
            {
               if( dwFlags & 1 )
               {
                  k++;
                  DWORD cb = _xstrlen(k);
                  DWORD n = _bscan((LPBYTE) k , cb , (BYTE) ']' );
                  if( n < cb )
                  {
                     k[n] = 0;
                     cb = n;
                  }
                  cb = ByteMapTable_RTrimEx(bt,(LPBYTE)k,cb);
                  cb = ByteMapTable_LTrimEx(bt,(LPBYTE)k,cb);
                  _bcopy((LPBYTE) pStr, (LPBYTE) k , cb );
                  if( pSectionList )
                  {
                     pStr[cb] = 0;
                     pSectionList->Add( (void*) _xstrdup(pStr) );
                  }
                  pStr[cb] = '\\';
                  pLastSection = pStr;
                  cbLastSection = cb+1;
               }
            }
            else if( k[0] != ';' )
            {


               LPSTR v   = 0;
               DWORD cbv = 0;
               DWORD cbk = _xstrlen(k);
               DWORD n  = _bscan((LPBYTE) k , cbk , (BYTE) '=' );
               if( n < cbk )
               {
                  cbk   = n;
                  k[cbk] = 0;
                  v = _mk_ptr_( LPSTR,k,n+1);
                  if( dwFlags & 2 )
                  {
                     cbv = ByteMapTable_RTrimEx(bt,(LPBYTE)v,(DWORD) -1);
                     cbv = ByteMapTable_LTrimEx(bt,(LPBYTE)v,cbv);
                  }
                  else
                  {
                     cbv = _xstrlen(v);
                  }
               }
               if( cbk )
               {
                  cbk = ByteMapTable_RTrimEx(bt,(LPBYTE)k,cbk);
                  cbk = ByteMapTable_LTrimEx(bt,(LPBYTE)k,cbk);
               }

               if( pLastSection && cbk )
               {
                  _bcopy( _mk_ptr_( LPBYTE , pLastSection,cbLastSection) ,(LPBYTE)  k ,cbk + 1 );
                  k = pLastSection;
                  cbk += cbLastSection;
               }
               if( !v)
               {
                  n = 0;
                  v = _mk_ptr_(LPSTR,&n,0);
                  cbv = 0;
               }
               if( cbk )
               {

                  THDictItem* phi = new THDictItem(k,cbk,v,cbv,TRUE);
                  phi->AddToHashTable( pht);
               }
            }
         }
         delete pList;
      }
      _xfree( (void*) pStr );
   }
   unlock_hdict(cs);
   if( pSectionList )
   {
      xpp[0]->PutNewArray(1,pSectionList->Count(), 0);
      DWORD dwCount = pSectionList->Count();
      DWORD dw;
      for( dw=0; dw < dwCount; dw++ )
      {
         LPSTR p = (LPSTR) pSectionList->Replace(dw,0);
         if( p )
         {
            _conArrayPutC(xpp[0]->con(),p,dw+1,0);
            _xfree( (void*) p ); p = 0;
         }
      }
      delete pSectionList;
      pSectionList = 0;
   }

}
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: THDictEx
            | _slug_: thdictex
            | class-function: THDICTEX
            | category: container/dictionary
            | desc: Xbase++ wrapper class around a case-insensitive dictionary handle. It exposes explicit
              dictionary methods and virtual instance variables backed by the dictionary: assigning or reading
              an undeclared instance variable stores or returns a dictionary entry.
            | note: This class wraps the low-level _hdict_* functions and shares their legacy status. Call
              ::destroy() when the dictionary is no longer needed if the object lifetime is not otherwise
              controlled by the application.
            | example: ```
              local o := THDictEx():new()

              o:SetProp( "Name", "OT4XB" )
              ? o:GetProp( "name" )   // case-insensitive
              ? o:Name                // virtual member access

              o:destroy()
              ```
   | _kw_: dictionary, hash table, key value, class wrapper, hdict
   }}*/
BEGIN_XBASE_CLASS( THDICTEX )
{
   pc->EXPORTED();
   /*{{|ivar_: - VAR m_23D7C8B01AF14A059D83551121621B91
            | type: Numeric pointer
            | desc_: Internal instance variable holding the wrapped dictionary handle; read it with ::h().
   }}*/
   pc->Var("m_23D7C8B01AF14A059D83551121621B91");
   /*{{|method_: - `METHOD h()` | return: pHt | desc_: Returns the raw dictionary handle. }}*/
   pc->MethodCB("h","{|s| s:m_23D7C8B01AF14A059D83551121621B91 }");
   /*{{|method_: - `METHOD handle()` | return: pHt | desc_: Returns the raw dictionary handle, like ::h(). }}*/
   pc->MethodCB("handle","{|s| s:m_23D7C8B01AF14A059D83551121621B91 }");
   /*{{|method_: - `METHOD new( [lSync] )`
            | return: oDict
            | desc_: Creates the object and its underlying case-insensitive dictionary. lSync is passed to
              _hdict_new(); with .T. the dictionary is synchronized and can be shared between threads.
   }}*/
   pc->MethodCB("init"       ,"{|s,lSync| s:m_23D7C8B01AF14A059D83551121621B91 := _hdict_new(@s:m_23D7C8B01AF14A059D83551121621B91,NIL,NIL,lSync),s}");
   /*{{|method_: - `METHOD destroy()`
            | return: NIL
            | desc_: Destroys the wrapped dictionary and sets the handle member to NIL.
   }}*/
   pc->MethodCB("destroy"    ,"{|s| _HDICT_DESTROY(s:h()) , s:m_23D7C8B01AF14A059D83551121621B91 := NIL}");
   /*{{|method_: - `METHOD SetProp( xKey, xValue )`
            | return: NIL
            | desc_: Stores or replaces a value in the dictionary.
   }}*/
   pc->MethodCB("SetProp"   ,"{|s,k,v| _HDICT_SETPROP(s:h(),k,v) }");
   /*{{|method_: - `METHOD GetProp( xKey )`
            | return: `xValue | NIL`
            | desc_: Returns the value stored under a key, or NIL when the key does not exist.
   }}*/
   pc->MethodCB("GetProp"   ,"{|s,k| _HDICT_GETPROP(s:h(),k) }");
   /*{{|method_: - `METHOD SetNoIVar( cKey, xValue )`
            | return: NIL
            | desc_: Virtual instance-variable setter: assigning an undeclared instance variable stores the
              value in the dictionary.
   }}*/
   pc->MethodCB("SetNoIVar"  ,"{|s,k,v| _HDICT_SETPROP(s:h(),k,v) }");
   /*{{|method_: - `METHOD GetNoIVar( cKey )`
            | return: `xValue | NIL`
            | desc_: Virtual instance-variable getter: reading an undeclared instance variable returns the
              value stored under that name.
   }}*/
   pc->MethodCB("GetNoIVar"  ,"{|s,k| _HDICT_GETPROP(s:h(),k) }");
   /*{{|method_: - `METHOD IsProp( xKey )`
            | return: lExists
            | desc_: Returns .T. when the key exists in the dictionary.
   }}*/
   pc->MethodCB("IsProp"     ,"{|s,k| _HDICT_ISPROP(s:h(),k) }");
   /*{{|method_: - `METHOD RemoveProp( xKey )` | return: lRemoved | desc_: Removes one entry from the dictionary. }}*/
   pc->MethodCB("RemoveProp" ,"{|s,k| _HDICT_REMOVEPROP(s:h(),k) }");
   /*{{|method_: - `METHOD RemoveAll()` | return: NIL | desc_: Removes all entries from the dictionary. }}*/
   pc->MethodCB("RemoveAll"  ,"{|s| _HDICT_REMOVEALL(s:h()) }");
   /*{{|method_: - `METHOD Count()`
            | return: nCount
            | desc_: Returns the number of entries stored in the dictionary.
   }}*/
   pc->MethodCB("Count"      ,"{|s| _HDICT_COUNT(s:h()) }");
   /*{{|method_: - `METHOD AddFromArray( aPairs )`
            | return: NIL
            | desc_: Adds entries from an array of { xKey, xValue } pairs.
   }}*/
   pc->MethodCB("AddFromArray"     ,"{|s,aData| _HDICT_ADDPROPFROMARRAY(s:h(),aData) }");
   /*{{|method_: - `METHOD AddFromIniString( cIniText, nFlags )`
            | return: `aSections | NIL`
            | desc_: Adds entries parsed from INI-style text; see _hdict_addpropfroministring() for the flags
              and the returned value.
   }}*/
   pc->MethodCB("AddFromIniString" ,"{|s,cStr,flags| _HDICT_ADDPROPFROMINISTRING(s:h(),cStr,flags) }");
   /*{{|method_: - `METHOD AddEnvStrings( [pEnvironment] )`
            | return: NIL
            | desc_: Adds the environment variables of a Windows environment block or, when pEnvironment is
              omitted, of the current process.
   }}*/
   pc->MethodCB("AddEnvStrings" ,"{|s,pEnv| _HDICT_ADD_ENV_STRINGS(s:h(),pEnv) }");
   /*{{|method_: - `METHOD AddHttpHeaders( cHeaders )`
            | return: NIL
            | desc_: Adds HTTP-style header lines formatted as "Name: value".
   }}*/
   pc->MethodCB("AddHttpHeaders" ,"{|s,cStr| _HDICT_ADD_HTTP_HEADERS(s:h(),cStr,flags) }");
   /*{{|method_: - `METHOD ToArray()`
            | return: aPairs
            | desc_: Returns the entries as an array of { cKey, xValue } pairs, _hdict_iterate_cb() operation 3.
   }}*/
   pc->MethodCB("ToArray" ,"{|s| _HDICT_ITERATE_CB(s:h(),3) }");
   /*{{|method_: - `METHOD FromZkdw( cZkdw )`
            | return: nItems
            | desc_: Imports the records of a ZKDW buffer and returns the number of entries imported.
   }}*/
   pc->MethodCB("FromZkdw" ,"{|s,zkdw| _HDICT_FROM_ZKDW(s:h(),zkdw) }");
   /*{{|method_: - `METHOD ToZkdw( [nDefault] )`
            | return: cZkdw
            | desc_: Exports the entries as a ZKDW buffer, _hdict_iterate_cb() operation 5, with nDefault used
              for non-integer entries.
   }}*/
   pc->MethodCB("ToZkdw" ,"{|s,defval| _HDICT_ITERATE_CB(s:h(),5,defval) }");
   /*{{|method_: - `METHOD ResetZkdw( [nDefault] )`
            | return: NIL
            | desc_: Resets every entry to an integer Numeric value, nDefault or 0, _hdict_iterate_cb()
              operation 6.
   }}*/
   /*{{|:**END CLASS** }}*/
   pc->MethodCB("ResetZkdw" ,"{|s,defval| _HDICT_ITERATE_CB(s:h(),6,defval) }");
}
END_XBASE_CLASS
/*{{include-note-id: thdict-legacy-api}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
