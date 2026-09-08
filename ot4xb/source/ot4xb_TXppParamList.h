//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TXppParamList
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , ot4xb-api
   | desc: The parameter list of an Xbase++ entry point, seen from C++: `xpp[n]` is the n-th parameter as a
     {{ilink: <cpp-class TXbCPItem> TXbCPItem}} with typed getters and setters, `xpp[0]` is the return value.
     The items are created on demand: a parameter beyond those passed, or beyond the formal count, is a fresh
     NIL container, so a missing optional parameter reads as NIL without any check. When the object goes out of
     scope the return value is handed to Xbase++ and every item is released (locks included), which is why
     the usual pattern is one `TXppParamList xpp( pl )` on the stack of the _XPP_REG_FUN_.
   | example:
     _XPP_REG_FUN_( MY_FUNCTION )
     {
        TXppParamList xpp( pl );
        LPSTR name = xpp[1]->LockStr();          // parameter 1 as a locked string
        LONG  n    = xpp[2]->GetLong();          // parameter 2 as a number (0 when NIL)
        xpp[0]->PutBool( do_something( name, n ) ); // the return value
     }
     | _kw_: TXppParamList, Class }}*/
class OT4XB_API TXppParamList : public T_ot4xb_base
{
   public:
       /*{{|member_: `XppParamList m_pl` | desc_: The Xbase++ parameter list, 0 for a stand-alone object. }}*/
       XppParamList        m_pl;
       /*{{|member_: `TXbCPItem** m_pItems` | desc_: The items, index 0 the return value; a slot is 0 until it
          is first asked for. }}*/
       TXbCPItem **        m_pItems;
       /*{{|member_: `ULONG m_nPCount` | desc_: Parameters actually passed by the caller. }}*/
       ULONG               m_nPCount;
       /*{{|member_: `ULONG m_nCapacity` | desc_: Slots allocated (grown as needed). }}*/
       ULONG               m_nCapacity;
       /*{{|member_: `ULONG m_nFormalCount` | desc_: Formal parameters of the function: the passed count or
          the constructor's value, whichever is larger. }}*/
       ULONG               m_nFormalCount;
       // ---------------------------------------------------------------------------------
       /*{{|method_: `TXppParamList( XppParamList pl = 0, ULONG nFormalCount = 0 )`
          | desc_: Wraps **pl**; the return value (item 0) is created at once as NIL, the parameters when
            they are first used. **nFormalCount** declares how many parameters the function has, so that the
            missing ones get their own NIL containers. }}*/
       TXppParamList( XppParamList pl = 0 , ULONG nFormalCount = 0);
       /*{{|method_: `~TXppParamList( void )` | desc_: Deletes every item (unlocking what is locked) and
          returns item 0 to Xbase++ through **m_pl** (a plain return when there is no item 0). }}*/
       ~TXppParamList( void );
       /*{{|method_: `void init_formal_params( void )` | desc_: Creates the containers of the return value and
          of every formal parameter now, so that they exist before the work is handed to another thread. }}*/
       void init_formal_params(void); // will be usefull for thread delegation
       /*{{|method_: `TXbCPItem* _get_( ULONG n )` | desc_: The item **n**, created when needed: bound to
          parameter n when n is within the passed count, a free NIL container otherwise. A negative n (as an
          int) addresses the slot formal count + |n|: scratch containers after the parameters. }}*/
        TXbCPItem* _get_(ULONG n);
       /*{{|method_: `TXbCPItem* operator[]( int n )` | desc_: _get_( n ). }}*/
        TXbCPItem* operator[]( int n );
       /*{{|method_: `ULONG PCount( void )` | desc_: Parameters passed by the caller. }}*/
        ULONG PCount(void);
       /*{{|method_: `DWORD Eval( UINT nParams = 0 )` | desc_: Evaluates the code block in parameter 1 with
          the next **nParams** parameters (2 to nParams + 1) as its arguments; the result of the block goes to
          the return value. Returns INFINITE when parameter 1 is not a code block, otherwise the result of
          _conEvalBa(). }}*/
        DWORD Eval(UINT nParams = 0);
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TXbCPItem
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , ot4xb-api , container
   | desc: One Xbase++ value handled from C++: a parameter of a {{ilink: <cpp-class TXppParamList> TXppParamList}}
     (bound lazily, with its by-reference flag), the return value, or any container the item is given. The
     getters convert the value to C types through the container API and return 0 or FALSE when the value
     cannot be converted; the setters replace the value, and on a parameter passed by reference that changes
     the caller's variable. A Character can be locked for direct access, and the LockStrEx family locks
     "anything with bytes": a Character, a numeric array packed into a buffer, or a GWST object through its
     _lock_() method. One lock at a time per item; the destructor unlocks.
     | _kw_: TXbCPItem, Class }}*/
class OT4XB_API TXbCPItem : public T_ot4xb_base
{
   public:
       /*{{|member_: `XppParamList m_pl` | desc_: The parameter list the item is bound to, 0 otherwise. }}*/
       XppParamList    m_pl;
       /*{{|member_: `ULONG m_nRealPosition` | desc_: Position in the parameter list (1-based; 0 for the return
          value). }}*/
       ULONG           m_nRealPosition;
       /*{{|member_: `BOOL m_bInit` | desc_: TRUE once the parameter has been fetched from the list. }}*/
       BOOL            m_bInit;               // typedef struct{
       /*{{|member_: `ULONG m_nType` | desc_: Type mask cached by the lock functions. }}*/
       ULONG           m_nType;               //  ULONG           nType;
       /*{{|member_: `ULONG m_nLockLen` | desc_: Bytes of the current lock. }}*/
       ULONG           m_nLockLen;            //  ULONG           nLen;
       /*{{|member_: `BOOL m_bByRef` | desc_: The parameter was passed by reference (setters write through to
          the caller's variable); for a wrapped container, that it is borrowed and must not be released. }}*/
       BOOL            m_bByRef;              //  BOOL            bByRef;
       /*{{|member_: `ContainerHandle m_con` | desc_: The container, 0 until bound or created. }}*/
       ContainerHandle m_con;                 //  ContainerHandle con;
       /*{{|member_: `LPSTR m_pLockStr` | desc_: The locked bytes, 0 when not locked. }}*/
       LPSTR           m_pLockStr;            //  LPSTR           pStr;
       /*{{|member_: `BOOL m_bLockW` | desc_: The current lock is a write lock. }}*/
       BOOL            m_bLockW;              //  BOOL            bWrite;
       /*{{|member_: `DWORD m_nCntType` | desc_: How a numeric array is packed by LockStrEx: 0 integers
          (bytes), 1 float, 2 double. }}*/
       DWORD           m_nCntType;            //  DWORD           nCntType; // 0 int/byte , 1 FLOAT
       /*{{|member_: `TList* m_pComplex` | desc_: Index of a locked nested array, used to write it back. }}*/
       TList *         m_pComplex;            //  TList *         pComplex;
       /*{{|member_: `BOOL m_bStrLockEx` | desc_: The current lock came from LockStrEx on an array or an
          object. }}*/
       BOOL            m_bStrLockEx;          // } CON_PLKSTREX;
       /*{{|member_: `char m_date_buffer[16]` | desc_: Where GetDateString() with no argument writes. }}*/
       char            m_date_buffer[16];
       // ---------------------------------------------------------------------------------
       /*{{|method_: `TXbCPItem( void )` | desc_: An empty item, no container until con() or a setter creates
          one. }}*/
       TXbCPItem( void );
       /*{{|method_: `TXbCPItem( XppParamList pl, ULONG n )` | desc_: The item of parameter **n** of **pl**,
          fetched on first use. }}*/
       TXbCPItem( XppParamList,ULONG  );
       /*{{|method_: `TXbCPItem( ContainerHandle con, BOOL bByRef )` | desc_: Wraps an existing container:
          owned and released with the item, or only borrowed with **bByRef**. }}*/
       TXbCPItem( ContainerHandle con , BOOL bByRef);
       /*{{|method_: `~TXbCPItem( void )` | desc_: Unlocks and releases the container (unless borrowed). }}*/
       ~TXbCPItem( void );
       /*{{|method_: `ContainerHandle detach( void )` | desc_: Unlocks and gives the container away: the item is
          left empty and the caller owns the handle. }}*/
       ContainerHandle detach(void);
       /*{{|method_: `void init( void )` | desc_: Fetches the parameter from the list (container and
          by-reference flag) the first time; every accessor calls it. }}*/
       void init(void );
       // ---------------------------------------------------------------------------------
       /*{{|method_: `ULONG GetType( void )` | desc_: The XPP_* type mask of the value, 0 without container. }}*/
       ULONG           GetType(void);
       /*{{|method_: `BOOL CheckType( ULONG ulType )` | desc_: TRUE when the type mask and **ulType** share a
          bit. }}*/
       BOOL            CheckType(ULONG ulType);
       /*{{|method_: `ContainerHandle GetT( ULONG ulType, BOOL* pbByRef = 0 )` | desc_: The container when its
          type matches **ulType**, 0 otherwise. }}*/
       ContainerHandle GetT( ULONG ulType , BOOL * pbByRef = 0);
       /*{{|method_: `ContainerHandle Get( BOOL* pbByRef = 0 )` | desc_: The container (0 when there is none)
          and, in **pbByRef**, whether it was passed by reference. Still owned by the item. }}*/
       ContainerHandle Get( BOOL * pbByRef = 0);
       /*{{|method_: `ContainerHandle con( void )` | desc_: The container, created as NIL when there is none. }}*/
       ContainerHandle con(void);
       /*{{|method_: `void Put( ContainerHandle con = 0 )` | desc_: Copies the value of **con** into the item
          (NIL for 0); the source handle stays the caller's. }}*/
       void            Put( ContainerHandle con = 0);
       /*{{|method_: `void Put( TXbCPItem* p )` | desc_: Copies the value of another item. }}*/
       void            Put( TXbCPItem* p);
       /*{{|method_: `BOOL GetBool( void )` | desc_: The value as a Logical; FALSE when it is not one. }}*/
       BOOL            GetBool(void);
       /*{{|method_: `LONG GetLong( void )` | desc_: The value as a LONG (Numeric truncated); 0 when it is not
          convertible. }}*/
       LONG            GetLong(void);
       /*{{|method_: `HANDLE GetHandle( void )` | desc_: GetLong() as a HANDLE. }}*/
       HANDLE          GetHandle( void);
       /*{{|method_: `LONGLONG GetQWord( void )` | desc_: A 64-bit integer from any of its Xbase++ forms: an
          8-byte Character, a Numeric, a two-element array {low, high}, or an object with an 8-byte string
          member Q. 0 otherwise. }}*/
       LONGLONG        GetQWord(void);
       /*{{|method_: `DWORD GetDWord( void )` | desc_: GetLong() as a DWORD. }}*/
       DWORD           GetDWord(void);
       /*{{|method_: `WORD GetWord( void )` | desc_: GetLong() as a WORD. }}*/
       WORD            GetWord(void);
       /*{{|method_: `double GetDouble( void )` | desc_: The value as a double; 0 when it is not convertible. }}*/
       double          GetDouble(void);
       /*{{|method_: `FLOAT GetFloat( void )` | desc_: GetDouble() as a FLOAT. }}*/
       FLOAT           GetFloat(void);
       /*{{|method_: `LONGLONG GetSqlStrMoney( void )` | desc_: The value as an amount in cents: a Numeric
          multiplied by 100 (rounded), or a Character parsed as a money string. 0 for other types. }}*/
	   LONGLONG         GetSqlStrMoney(void);
       /*{{|method_: `void PutSqlStrMoney( LONGLONG qn, DWORD flags, DWORD pad )`
          | desc_: Stores an amount in cents as a text with two decimals ("12.34"). **flags** 0 writes a
            leading '-' for a negative amount; with bit 2 (0x02) a negative amount is written unsigned with
            the suffix " C" (or " H" with 0x10, plus 'r' or 'b' with 0x20), and with bit 4 (0x04) a positive
            one gets " D" (plus 'b' with 0x20). **pad** left-pads the text with spaces up to that length. }}*/
	   void             PutSqlStrMoney(LONGLONG qn, DWORD flags, DWORD pad);
       /*{{|method_: `void PutBool( BOOL value )` | desc_: Stores a Logical. }}*/
       void            PutBool(BOOL value );
       /*{{|method_: `void PutLong( LONG value )` | desc_: Stores a Numeric. }}*/
       void            PutLong(LONG value );
       /*{{|method_: `void PutQWord( LONGLONG value )` | desc_: Stores the 8 bytes as a Character (the QWORD
          convention of ot4xb). }}*/
       void            PutQWord(LONGLONG value );
       /*{{|method_: `void PutQWordAsNumeric( LONGLONG value )` | desc_: Stores a Numeric: a LONG when the
          value fits in 32 bits with sign, a double otherwise. }}*/
       void            PutQWordAsNumeric(LONGLONG value);
       /*{{|method_: `void PutDWord( DWORD value )` | desc_: Stores a Numeric (as a signed LONG). }}*/
       void            PutDWord(DWORD value );
       /*{{|method_: `void PutWord( WORD value )` | desc_: Stores a Numeric. }}*/
       void            PutWord(WORD value );
       /*{{|method_: `void PutDouble( double value )` | desc_: Stores a Numeric. }}*/
       void            PutDouble(double value );
       /*{{|method_: `void PutDoubleFormat( double ndValue, int nDigits, int nDec )` | desc_: Stores a Numeric
          with the given width and decimals. }}*/
       void            PutDoubleFormat(double ndValue , int nDigits , int nDec );
       /*{{|method_: `void PutFloat( FLOAT value )` | desc_: Stores a Numeric. }}*/
       void            PutFloat(FLOAT value );
       /*{{|method_: `void PutDateString( LPSTR ds )` | desc_: Stores a Date from "YYYYMMDD". }}*/
       void            PutDateString( LPSTR ds );
       /*{{|method_: `void PutJulianDate( DWORD dw )` | desc_: Stores a Date from its Julian day number. }}*/
		 void            PutJulianDate( DWORD dw );
       /*{{|method_: `DWORD GetJulianDate( void )` | desc_: The Date as a Julian day number, 0 when it is not
          a Date. }}*/
		 DWORD           GetJulianDate( void);
       /*{{|method_: `LPCSTR GetDateString( void )` | desc_: The Date as "YYYYMMDD" in the item's own buffer
          (empty when it is not a Date). }}*/
       LPCSTR          GetDateString(void);
       /*{{|method_: `void GetDateString( LPSTR ds )` | desc_: Writes the Date as "YYYYMMDD" into the 8 bytes
          at **ds** (zeroes when it is not a Date). No terminator. }}*/
       void            GetDateString(LPSTR ds);
       /*{{|method_: `LPSTR StrDupA( ULONG* pnLen = 0 )` | desc_: A zero-terminated copy of the Character in
          the ot4xb heap (free with _xfree), its length in **pnLen**; 0 when the value is not a Character. }}*/
       LPSTR           StrDupA(ULONG * pnLen = 0);
       /*{{|method_: `LPWSTR StrDupW( ULONG* pnBytes = 0 )` | desc_: A wide copy of the Character (ANSI to
          UTF-16, free with _xfree), its size in bytes in **pnBytes**; 0 when not a Character. }}*/
       LPWSTR          StrDupW(ULONG * pnBytes = 0);
       /*{{|method_: `BSTR StrDupBSTR( void )` | desc_: The Character as a new BSTR (SysFreeString); 0 when not
          a Character. }}*/
       BSTR            StrDupBSTR(void);
       /*{{|method_: `ULONG GetCL( LPSTR p, ULONG nBuffSize )` | desc_: Copies up to **nBuffSize** bytes of the
          Character into **p** and returns the length of the value. }}*/
       ULONG           GetCL(LPSTR p , ULONG nBuffSize);
       /*{{|method_: `void PutStrLen( LPSTR pStr, ULONG nLen )` | desc_: Stores **nLen** bytes as a Character. }}*/
       void            PutStrLen(LPSTR pStr , ULONG nLen);
       /*{{|method_: `void PutStr( LPSTR pStr )` | desc_: Stores a zero-terminated string as a Character (an
          empty one for 0). }}*/
       void            PutStr(LPSTR pStr);
       /*{{|method_: `void PutBSTR2a( BSTR bs )` | desc_: Stores a BSTR converted to ANSI (an empty Character
          for 0). }}*/
       void            PutBSTR2a(BSTR bs);
       /*{{|method_: `LPSTR LockStr( ULONG* pnSize = 0, BOOL bWrite = FALSE )` | desc_: Locks the Character
          and returns its bytes (not zero-terminated; length in **pnSize**), for writing in place with
          **bWrite**. 0 when the value is not a Character or the item is already locked. }}*/
       LPSTR           LockStr( ULONG * pnSize = 0 , BOOL bWrite = FALSE );
       /*{{|method_: `void UnlockStr( void )` | desc_: Releases the lock of LockStr(). }}*/
       void            UnlockStr(void);
       /*{{|method_: `HWND GetHWND( void )` | desc_: A Numeric as a window handle, or the result of the
          :GetHWND() method of an object; 0 otherwise. }}*/
       HWND            GetHWND(void);
       /*{{|method_: `void PutDwArray( DWORD* pdw, DWORD cc )` | desc_: Stores an array of **cc** Numerics
          taken from **pdw** (an empty array for 0). }}*/
       void            PutDwArray(DWORD* pdw , DWORD cc);
       /*{{|method_: `void PutNewArray( ULONG nDim, ... )` | desc_: Stores a new array with the **nDim** sizes
          that follow (0 dimensions: NIL). }}*/
       void            PutNewArray(ULONG nDim,...);
       // --------------------------------
       /*{{|method_: `BOOL PutEmptyData( ULONG nType, LONG nLen = 0, LONG nDec = 0 )` | desc_: Stores an empty
          value of the given type and size (a blank Character of nLen bytes, an array of nLen elements, ...).
          FALSE while the item is locked. }}*/
       BOOL            PutEmptyData(ULONG nType,LONG nLen = 0, LONG nDec = 0);
       /*{{|method_: `BOOL resize( ULONG nNewSize )` | desc_: Resizes a Character (bytes) or an array
          (elements). FALSE for other types or while locked. }}*/
       BOOL            resize(ULONG nNewSize);
       /*{{|method_: `ULONG con_size( void )` | desc_: Bytes of a Character or elements of an array; 0 for
          other types or while locked. }}*/
       ULONG           con_size(void);
       // --------------------------------
       /*{{|method_: `ContainerHandle operator[]( DWORD n )` | desc_: A new container with a copy of element
          **n** (zero-based) of the array, to be released by the caller; 0 when the value is not an array or n
          is out of range. }}*/
       ContainerHandle operator[]( DWORD n );
       // --------------------------------
       /*{{|method_: `BOOL GetGuid( GUID* pDst )` | desc_: Reads a GUID from a 16-byte Character, from its text
          form (braces optional), or from the bytes of anything LockStrEx() can lock. }}*/
       BOOL            GetGuid(GUID* pDst);
       /*{{|method_: `BOOL PutGuid( GUID* pSrc, BOOL bBraces = FALSE )` | desc_: Stores the GUID as text,
          between braces with **bBraces**. }}*/
       BOOL            PutGuid(GUID* pSrc , BOOL bBraces = FALSE);
       // --------------------------------
       /*{{|method_: `LPSTR LockStrEx( BOOL bWrite = FALSE )` | desc_: _LockStrEx_( bWrite, 0 ). }}*/
       LPSTR           LockStrEx(BOOL bWrite = FALSE);
       /*{{|method_: `UINT ExLen( void )` | desc_: Bytes of the current lock. }}*/
       UINT            ExLen(void);
       /*{{|method_: `LPSTR _LockStrEx_( BOOL bWrite = FALSE, DWORD nCntType = 0 )`
          | desc_: The bytes behind any value: a Character is locked (LockStr()); a Numeric is returned as a
            pointer, no lock; an array is packed into a temporary buffer, its numbers as integers, floats or
            doubles by **nCntType** (0, 1, 2), and with **bWrite** the buffer is written back to the array
            on unlock; an object is asked for its bytes through its :_lock_() method (a GWST object, or one
            implementing _lock_/_unlock_). 0 for other types or when already locked. }}*/
       LPSTR           _LockStrEx_(BOOL bWrite = FALSE, DWORD nCntType = 0);
       /*{{|method_: `LPSTR RLockStrEx( void )` | desc_: Read lock, integers. }}*/
       LPSTR           RLockStrEx(void);
       /*{{|method_: `LPSTR WLockStrEx( void )` | desc_: Write lock, integers. }}*/
       LPSTR           WLockStrEx(void);
       /*{{|method_: `LPSTR RLockStrExF( void )` | desc_: Read lock, array numbers as float. }}*/
       LPSTR           RLockStrExF(void);
       /*{{|method_: `LPSTR WLockStrExF( void )` | desc_: Write lock, array numbers as float. }}*/
       LPSTR           WLockStrExF(void);
       /*{{|method_: `LPSTR RLockStrExF8( void )` | desc_: Read lock, array numbers as double. }}*/
       LPSTR           RLockStrExF8(void);
       /*{{|method_: `LPSTR WLockStrExF8( void )` | desc_: Write lock, array numbers as double. }}*/
       LPSTR           WLockStrExF8(void);
       /*{{|method_: `void UnLockStrEx( void )` | desc_: Releases whatever _LockStrEx_() locked, writing a
          packed array back when it was a write lock. }}*/
       void            UnLockStrEx(void);
       // --------------------------------
       /*{{|method_: `LPSTR str( void )` | desc_: The locked bytes, locking the Character for reading when it
          is not locked yet. }}*/
       LPSTR str(void);
       // --------------------------------
       /*{{|method_: `void setprop_ansi2wide( LPWSTR* ppw )` | desc_: For a property setter holding a wide
          string: frees the old one and stores a wide copy of the Character in ***ppw** (0 for a
          non-Character). }}*/
       void setprop_ansi2wide( LPWSTR*  ppw );
       /*{{|method_: `void getprop_wide2ansi( LPWSTR* ppw )` | desc_: For the matching getter: stores the wide
          string ***ppw** converted to ANSI as the item's value (nothing when it is 0). }}*/
       void getprop_wide2ansi( LPWSTR*  ppw );
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
