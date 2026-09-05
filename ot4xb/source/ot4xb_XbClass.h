//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifndef _API_cpp_XbClass_h_
#define _API_cpp_XbClass_h_
//----------------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
#pragma pack(push , 4)
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TXbGenError
   | category: c-api/classes , ot4xb-api
   | desc: An Xbase++ Error object built from C++: the constructor creates it, the setters fill its members
     one by one, and Launch() hands it to the error block of the application, as a runtime error would. The
     object is released with the C++ instance, so the usual shape is a local: build, fill, Launch(), return.
     The `xpp_assert` macro of ot4xb_api.h is the one-line version of it.
   | example:
     if( !hFile )
     {
        TXbGenError e( 1, __FUNCTION__, "Cannot open the file" );
        e.filename( pFName );
        e.oscode( GetLastError() );
        e.Launch();
        return;
     | _kw_: Error object, raise error, ErrorBlock, gencode, C++ error
     } }}*/
class OT4XB_API TXbGenError
{
   public:
   /*{{|member_: `ContainerHandle m_cone` | desc_: The Error object. }}*/
   ContainerHandle     m_cone;
   /*{{|method_: `TXbGenError( int nCode, LPSTR pOperation, LPSTR pDescription )` | desc_: A new Error with
      subsystem "ot4xb", gencode **nCode**, and the given operation and description. }}*/
   TXbGenError(int nCode,LPSTR pOperation , LPSTR pDescription);
   /*{{|method_: `TXbGenError( void )` | desc_: A new, empty Error. }}*/
   TXbGenError(void);
   /*{{|method_: `~TXbGenError()` | desc_: Releases the Error object (the error block keeps its own
      reference when it was launched). }}*/
   ~TXbGenError();
   /*{{|method_: `void args( ContainerHandle cona )` | desc_: Sets :args to the array **cona**. }}*/
   void args(ContainerHandle cona);
   /*{{|method_: `void add_arg( ContainerHandle con )` | desc_: Appends a value to :args (created as an
      array when it is not one yet). }}*/
   void add_arg(ContainerHandle con);
   /*{{|method_: `void candefault( BOOL b )` | desc_: Sets :canDefault. }}*/
   void candefault( BOOL b );
   /*{{|method_: `void canretry( BOOL b )` | desc_: Sets :canRetry. }}*/
   void canretry( BOOL b );
   /*{{|method_: `void cansubstitute( BOOL b )` | desc_: Sets :canSubstitute. }}*/
   void cansubstitute( BOOL b );
   /*{{|method_: `void cargo( ContainerHandle con )` | desc_: Sets :cargo. }}*/
   void cargo(ContainerHandle con);
   /*{{|method_: `void description( LPSTR p )` | desc_: Sets :description. }}*/
   void description(LPSTR p );
   /*{{|method_: `void filename( LPSTR p )` | desc_: Sets :filename. }}*/
   void filename(LPSTR p);
   /*{{|method_: `void gencode( int i )` | desc_: Sets :genCode. }}*/
   void gencode(int i);
   /*{{|method_: `void operation( LPSTR p )` | desc_: Sets :operation. }}*/
   void operation(LPSTR p);
   /*{{|method_: `void oscode( int i )` | desc_: Sets :osCode. }}*/
   void oscode(int i);
   /*{{|method_: `void severity( int i )` | desc_: Sets :severity. }}*/
   void severity( int i);
   /*{{|method_: `void subcode( int i )` | desc_: Sets :subCode. }}*/
   void subcode(int i);
   /*{{|method_: `void subsystem( LPSTR p )` | desc_: Sets :subSystem. }}*/
   void subsystem(LPSTR p);
   /*{{|method_: `void tries( int val )` | desc_: Sets :tries. }}*/
   void tries(int val);
   /*{{|method_: `void Launch( void )` | desc_: Evaluates ErrorBlock() with the Error: the application's
      error handler runs in the calling thread. The result is discarded. }}*/
   void Launch(void);
};
/*{{end-cpp-class}}*/
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TXbClass
   | category: c-api/classes , ot4xb-api
   | desc: The class builder: an Xbase++ class defined from C++, member by member, and created with
     Create() through ClassCreate(). Every ot4xb class is built this way, inside its class function (see the
     `BEGIN_XBASE_CLASS` macro of ot4xb_api.h). The recipe: `new TXbClass`, ClassName(), the parents, the
     default scope (EXPORTED() etc.), then Var(), Method(), Property() and their variants, then Create() and
     `delete`. A method or property implemented in C is a `void fn( TXbClsParams* )`
     ({{ilink: <cpp-class TXbClsParams> TXbClsParams}} gives it Self, the parameters and the return value);
     the builder wraps it in a generated code block that calls it through `_xbmtpf1_`. A member can also be a
     code block given as text (the *CB and *_cbbs forms).
   | note: GWST classes, the structures mapped over memory, are built with the same object: GwstParent()
     switches it to structure mode, and Member_*(), Child(), the union and alignment calls lay the members
     out at increasing offsets; Create() then stores the layout in the shared class variables `_mc__mdef_`,
     `_mc__chdef_` and `_mc__size_`, which a derived structure inherits and continues from. Each member
     becomes a property whose access and assign are done in place by the `_GWST_XBSETGET_*` functions.
   | note: Class hooks let Xbase++ code take part in the creation of a class defined in C: AddClassHook()
     registers, by class name, an object (its :OnClassCreate( oTXbClass ) method is called) or a code block
     (evaluated with the TXbClass wrapper object), and Create() runs them before ClassCreate(), so they can
     add members. **m_bDisableHooks** skips them for one class.
   | example:
     _XPP_REG_FUN_( MYPOINT )                       // the class function
     {
        ContainerHandle conco = _conClsObj( "MyPoint" );
        if( conco == NULLCONTAINER )
        {
           TXbClass* pc = new TXbClass;
           pc->ClassName( "MyPoint" );
           pc->EXPORTED();
           pc->Var( "x" );
           pc->Var( "y" );
           pc->Method( "distance", MyPoint_distance, 1 );   // void MyPoint_distance( TXbClsParams* px )
           pc->PropertyCB( "isOrigin", "{|s| s:x == 0 .and. s:y == 0 }" );
           conco = pc->Create();
           delete pc;
        }
        _conReturn( pl, conco );
        _conRelease( conco );
     | _kw_: class builder, define class from C++, methods properties, GWST structure builder, ClassCreate
     } }}*/
class OT4XB_API TXbClass
{
   public:
       /*{{|member_: `BOOL m_bDisableHooks` | desc_: TRUE to skip the class hooks in Create(). }}*/
       BOOL                m_bDisableHooks;
       /*{{|member_: `DWORD m_dwClsCrc32` | desc_: CRC of the class name in lower case (the GWST name key). }}*/
       DWORD               m_dwClsCrc32;
       /*{{|member_: `DWORD m_dwClsHookHandle` | desc_: The hook entry of this class name, 0 when none is
          registered; set by ClassName(). }}*/
       DWORD               m_dwClsHookHandle;
       /*{{|member_: `ContainerHandle m_conClassName` | desc_: The class name as a Character container. }}*/
       ContainerHandle     m_conClassName;
       /*{{|member_: `TXbClsPItem* m_pLastParent` | desc_: The parents, last first. }}*/
       TXbClsPItem *       m_pLastParent;
       /*{{|member_: `TXbClsMItem* m_pLastMethod` | desc_: The methods and properties, last first. }}*/
       TXbClsMItem *       m_pLastMethod;
       /*{{|member_: `TXbClsVItem* m_pLastVar` | desc_: The variables, last first. }}*/
       TXbClsVItem *       m_pLastVar;
       /*{{|member_: `ULONG m_nParentCount` | desc_: Number of parents. }}*/
       ULONG               m_nParentCount;
       /*{{|member_: `ULONG m_nMethodCount` | desc_: Number of methods and properties. }}*/
       ULONG               m_nMethodCount;
       /*{{|member_: `ULONG m_nVarCount` | desc_: Number of variables. }}*/
       ULONG               m_nVarCount;
       /*{{|member_: `ULONG m_nDefaultScope` | desc_: The scope given to the members defined from now on
          (xppCLASS_EXPORTED by default). }}*/
       ULONG               m_nDefaultScope;
       /*{{|member_: `LPSTR m_szPrintfBuffer` | desc_: 1 KB work buffer of cbbs() and the block generators. }}*/
       LPSTR               m_szPrintfBuffer;
       /*{{|member_: `BOOL m_bGwst` | desc_: The class is a GWST structure (GwstParent() was called). }}*/
       BOOL                m_bGwst;
       /*{{|member_: `DWORD m_dwGwstOffset` | desc_: Offset of the next member; the structure size at the
          end. }}*/
       DWORD               m_dwGwstOffset;
       /*{{|member_: `BOOL m_bGwstUnion` | desc_: A union is open: the members share the current offset. }}*/
       BOOL                m_bGwstUnion;
       /*{{|member_: `DWORD m_dwGwstUnionSize` | desc_: Largest member of the open union. }}*/
       DWORD               m_dwGwstUnionSize;
       /*{{|member_: `BOOL m_bGwstReadOnly` | desc_: The members defined from now on get no assign. }}*/
       BOOL                m_bGwstReadOnly;
       /*{{|member_: `TXbClsGwstItem* m_pLastGwst` | desc_: The structure members, last first (the
          inherited ones included). }}*/
       TXbClsGwstItem *    m_pLastGwst;
       /*{{|member_: `ULONG m_nGwstChildCount` | desc_: Number of embedded structures (Child()). }}*/
       ULONG               m_nGwstChildCount;
       /*{{|member_: `ULONG m_nGwstCount` | desc_: Number of structure members. }}*/
       ULONG               m_nGwstCount;
       /*{{|method_: `static void InitHookList()` | desc_: Creates the class hook table; called once when ot4xb starts. }}*/
       static void InitHookList();
       /*{{|method_: `static void FreeHookList( void )` | desc_: Destroys the hook table at shutdown. }}*/
       static void FreeHookList(void);
       /*{{|method_: `static DWORD AddClassHook( LPSTR pClassName, ContainerHandle conoHook )` | desc_: Registers a hook for the class **pClassName**: an object with an :OnClassCreate( oTXbClass ) method, or a code block evaluated with that object. Several hooks per class are kept in order. Returns the hook entry, 0 for a bad argument. }}*/
       static DWORD  AddClassHook(LPSTR pClassName , ContainerHandle conoHook ); // ->dwHookId
       /*{{|method_: `static DWORD GetClassHookHandle( LPSTR pClassName )` | desc_: The hook entry registered for a class name, 0 when none. }}*/
       static DWORD  GetClassHookHandle(LPSTR pClassName);  // -> dwClassHookHandle
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void* operator new( unsigned int nSize )` | desc_: Allocates in the ot4xb heap and initialises every member (there is no constructor): create the builder with `new`. }}*/
       void * operator new( unsigned int nSize);
       /*{{|method_: `void operator delete( void* pp )` | desc_: Releases the class name, the parents, members and structure items, and frees the builder. }}*/
       void operator delete( void * pp );
       // ---------------------------------------------------------------------------------
       /*{{|method_: `ContainerHandle Create( ContainerHandle conco = NULLCONTAINER )` | desc_: Runs the class hooks, collects the parents, variables and methods and calls ClassCreate(): the new class object is returned in **conco** (a new container when NULLCONTAINER is given; release it). A GWST class also gets its layout stored in `_mc__size_`, `_mc__mdef_` and `_mc__chdef_`. NULLCONTAINER when ClassCreate() fails or no class name was set. }}*/
       ContainerHandle Create( ContainerHandle conco = NULLCONTAINER );
       // ---------------------------------------------------------------------------------
       /*{{|method_: `ContainerHandle CollectSuper( void )` | desc_: The array of parent class objects, in definition order (release it). }}*/
       ContainerHandle CollectSuper( void );
       /*{{|method_: `ContainerHandle CollectVars( void )` | desc_: The array of variable definitions for ClassCreate() (release it). }}*/
       ContainerHandle CollectVars( void );
       /*{{|method_: `ContainerHandle CollectMethods( void )` | desc_: The array of method definitions for ClassCreate() (release it). }}*/
       ContainerHandle CollectMethods( void );
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void ClassName( LPSTR pClassName )` | desc_: Sets the class name, computes its CRC and looks up its hooks. Required before Create(). }}*/
       void ClassName( LPSTR pClassName );
       /*{{|method_: `void Parent( LPSTR pName )` | desc_: Adds a parent class by name (its class object is obtained with `_conClsObjNew`). }}*/
       void Parent( LPSTR pName );
       /*{{|method_: `void _xparent_( ContainerHandle cono )` | desc_: Adds a parent given as a class object; the handle is taken over. }}*/
       void _xparent_( ContainerHandle cono );
       /*{{|method_: `void _xGwstParent_( ContainerHandle concoParent )` | desc_: GwstParent() with the parent as a class object: switches to structure mode, adds GWST (or the given GWST-derived class) as parent, declares the three `_mc__*` shared class variables, and copies the parent's member layout so that the new members continue after its size. }}*/
       void _xGwstParent_( ContainerHandle concoParent );
       /*{{|method_: `void GwstParent( LPSTR pParent = 0 )` | desc_: Makes the class a GWST structure: parent GWST when **pParent** is 0, or the named structure class, whose members are inherited and whose size becomes the starting offset. Call it before any Member_*(). }}*/
       void GwstParent( LPSTR pParent = 0 );
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void EXPORTED( void )` | desc_: Members defined from now on are EXPORTED (the default). }}*/
       void EXPORTED(void);
       /*{{|method_: `void HIDDEN( void )` | desc_: Members defined from now on are HIDDEN. }}*/
       void HIDDEN(void);
       /*{{|method_: `void PROTECTED( void )` | desc_: Members defined from now on are PROTECTED. }}*/
       void PROTECTED(void);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void _var_( LPSTR pName, ULONG nFlags )` | desc_: Adds a variable with explicit xppVAR_* and scope flags. }}*/
       void _var_( LPSTR pName, ULONG nFlags);
       /*{{|method_: `LPSTR _mkpf1Str_( XbCMethodType pf, ULONG nParams, LPSTR pExtra = 0 )` | desc_: Builds the text of the code block that calls the C function **pf** through `_xbmtpf1_`: `{|s,p1..pN,e,rt| ...}` with **nParams** formal parameters passed by reference and the literal **pExtra** (a comma-led list, e.g. ",5,\"x\"") appended as extra arguments. The result is in the ot4xb heap. A block returns the C result, or raises the error the C function generated. }}*/
       LPSTR _mkpf1Str_(XbCMethodType pf ,ULONG nParams , LPSTR pExtra = 0);
       /*{{|method_: `void _method_( LPSTR pName, ULONG nFlags, LPSTR pCbString )` | desc_: Adds a method with explicit xppMETHOD_* flags whose body is the macro-compiled code block **pCbString** (`{|s| NIL }` for 0). }}*/
       void _method_( LPSTR pName, ULONG nFlags, LPSTR pCbString );
       /*{{|method_: `void _property_( LPSTR pName, ULONG nFlags, LPSTR pCbString )` | desc_: Same for a property (access, assign or both by the flags): the block gets Self and, on assign, the value. }}*/
       void _property_( LPSTR pName, ULONG nFlags, LPSTR pCbString );
       /*{{|method_: `void _xmethod_( LPSTR pName, ULONG nFlags, ContainerHandle conb )` | desc_: Adds a method whose body is the code block **conb** (taken over; released and ignored when it is not a block). }}*/
       void _xmethod_( LPSTR pName, ULONG nFlags, ContainerHandle conb );
       /*{{|method_: `void _xproperty_( LPSTR pName, ULONG nFlags, ContainerHandle conb )` | desc_: Same for a property. }}*/
       void _xproperty_( LPSTR pName, ULONG nFlags, ContainerHandle conb );
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void AddGwstStyleMembers( void )` | desc_: Adds the pointer-style members of a class backed by a C++ object: the variable `_m__pt_` (the pointer, see TXbClsParams::GetSelfC()) and the methods `_lock_()` (returns it) and `_unlock_()`, which make the object usable wherever a GWST structure is (LockStrEx, the DLL call marshalling). }}*/
       void AddGwstStyleMembers(void);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void Var( LPSTR pName, ULONG nMoreFlags = 0 )` | desc_: Adds an instance variable with the current scope (plus **nMoreFlags**). }}*/
       void Var( LPSTR pName, ULONG nMoreFlags = 0);
       /*{{|method_: `void ClassVar( LPSTR pName, ULONG nMoreFlags = 0 )` | desc_: Adds a class variable. }}*/
       void ClassVar( LPSTR pName, ULONG nMoreFlags = 0);
       /*{{|method_: `void SharedClassVar( LPSTR pName, ULONG nMoreFlags = 0 )` | desc_: Adds a SHARED class variable (visible to the subclasses). }}*/
       void SharedClassVar( LPSTR pName, ULONG nMoreFlags = 0);
       /*{{|method_: `void Method( LPSTR pName, XbCMethodType pf, ULONG nParams = 0, LPSTR pExtra = 0 )` | desc_: Adds a method implemented by the C function **pf** (`void fn( TXbClsParams* )`), declared with **nParams** formal parameters; **pExtra** appends literal extra arguments the function reads with GetExtra*(). }}*/
       void Method( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       /*{{|method_: `void ClassMethod( LPSTR pName, XbCMethodType pf, ULONG nParams = 0, LPSTR pExtra = 0 )` | desc_: Same as a class method. }}*/
       void ClassMethod( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       /*{{|method_: `void MethodCB( LPSTR pName, LPSTR pCbString )` | desc_: Adds a method whose body is the code block text **pCbString**, `{|s, ...| ...}` with Self first. }}*/
       void MethodCB( LPSTR pName, LPSTR pCbString);
       /*{{|method_: `void Method_cbbs( LPSTR pName, LPSTR pCbString, ... )` | desc_: MethodCB() with the block text formatted printf-style from the arguments that follow. }}*/
       void Method_cbbs( LPSTR pName, LPSTR pCbString, ...);       
       /*{{|method_: `void ClassMethodCB( LPSTR pName, LPSTR pCbString )` | desc_: MethodCB() as a class method. }}*/
       void ClassMethodCB( LPSTR pName, LPSTR pCbString);
       /*{{|method_: `void ClassMethod_cbbs( LPSTR pName, LPSTR pCbString, ... )` | desc_: Method_cbbs() as a class method. }}*/
       void ClassMethod_cbbs( LPSTR pName, LPSTR pCbString, ...);              
       /*{{|method_: `void Property( LPSTR pName, XbCMethodType pf, ULONG nParams = 0, LPSTR pExtra = 0 )` | desc_: Adds a read-write property implemented by **pf**: the same function serves the access and the assign, and tells them apart by PCount() (0 on access, 1 with the value on assign). }}*/
       void Property( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       /*{{|method_: `void ClassProperty( LPSTR pName, XbCMethodType pf, ULONG nParams = 0, LPSTR pExtra = 0 )` | desc_: Same as a class property. }}*/
       void ClassProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       /*{{|method_: `void PropertyCB( LPSTR pName, LPSTR pCbString )` | desc_: Adds a read-write property with a code block body, `{|s, v| ...}`: v is present (PCount() > 1) on assign. }}*/
       void PropertyCB( LPSTR pName, LPSTR pCbString);
       /*{{|method_: `void Property_cbbs( LPSTR pName, LPSTR pCbString, ... )` | desc_: PropertyCB() with a printf-formatted block text. }}*/
       void Property_cbbs( LPSTR pName, LPSTR pCbString, ...);              
       /*{{|method_: `void PropertyCBMask( LPSTR pName, DWORD dwMask, LPSTR pVar )` | desc_: Adds a Logical property mapped to the bits **dwMask** of the numeric instance variable **pVar**: reading tests them, assigning sets or clears them. }}*/
       void PropertyCBMask( LPSTR pName, DWORD dwMask , LPSTR pVar );
       /*{{|method_: `void ClassPropertyCB( LPSTR pName, LPSTR pCbString )` | desc_: PropertyCB() as a class property. }}*/
       void ClassPropertyCB( LPSTR pName, LPSTR pCbString);
       /*{{|method_: `void ClassProperty_cbbs( LPSTR pName, LPSTR pCbString, ... )` | desc_: Property_cbbs() as a class property. }}*/
       void ClassProperty_cbbs( LPSTR pName, LPSTR pCbString,...);
       /*{{|method_: `void ClassPropertyCBMask( LPSTR pName, DWORD dwMask, LPSTR pVar )` | desc_: PropertyCBMask() as a class property over a class variable. }}*/
       void ClassPropertyCBMask( LPSTR pName, DWORD dwMask , LPSTR pVar );
       /*{{|method_: `void ROProperty( LPSTR pName, XbCMethodType pf, ULONG nParams = 0, LPSTR pExtra = 0 )` | desc_: A read-only (access only) property implemented by **pf**. }}*/
       void ROProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       /*{{|method_: `void ROClassProperty( LPSTR pName, XbCMethodType pf, ULONG nParams = 0, LPSTR pExtra = 0 )` | desc_: Same as a class property. }}*/
       void ROClassProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       /*{{|method_: `void ROPropertyCB( LPSTR pName, LPSTR pCbString )` | desc_: A read-only property with a code block body, `{|s| ...}`. }}*/
       void ROPropertyCB( LPSTR pName, LPSTR pCbString);
       /*{{|method_: `void ROProperty_cbbs( LPSTR pName, LPSTR pCbString, ... )` | desc_: ROPropertyCB() with a printf-formatted block text. }}*/
       void ROProperty_cbbs( LPSTR pName, LPSTR pCbString,...);
       /*{{|method_: `void ROClassPropertyCB( LPSTR pName, LPSTR pCbString )` | desc_: ROPropertyCB() as a class property. }}*/
       void ROClassPropertyCB( LPSTR pName, LPSTR pCbString);
       /*{{|method_: `void ROClassProperty_cbbs( LPSTR pName, LPSTR pCbString, ... )` | desc_: ROProperty_cbbs() as a class property. }}*/
       void ROClassProperty_cbbs( LPSTR pName, LPSTR pCbString,...);       
       /*{{|method_: `void WOProperty( LPSTR pName, XbCMethodType pf, ULONG nParams = 0, LPSTR pExtra = 0 )` | desc_: A write-only (assign only) property implemented by **pf**. }}*/
       void WOProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       /*{{|method_: `void WOClassProperty( LPSTR pName, XbCMethodType pf, ULONG nParams = 0, LPSTR pExtra = 0 )` | desc_: Same as a class property. }}*/
       void WOClassProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       /*{{|method_: `void WOPropertyCB( LPSTR pName, LPSTR pCbString )` | desc_: A write-only property with a code block body, `{|s, v| ...}`. }}*/
       void WOPropertyCB( LPSTR pName, LPSTR pCbString);
       /*{{|method_: `void WOProperty_cbbs( LPSTR pName, LPSTR pCbString, ... )` | desc_: WOPropertyCB() with a printf-formatted block text. }}*/
       void WOProperty_cbbs( LPSTR pName, LPSTR pCbString,...);
       /*{{|method_: `void WOClassPropertyCB( LPSTR pName, LPSTR pCbString )` | desc_: WOPropertyCB() as a class property. }}*/
       void WOClassPropertyCB( LPSTR pName, LPSTR pCbString);
       /*{{|method_: `void WOClassProperty_cbbs( LPSTR pName, LPSTR pCbString, ... )` | desc_: WOProperty_cbbs() as a class property. }}*/
       void WOClassProperty_cbbs( LPSTR pName, LPSTR pCbString,...);                     
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void GwstReadOnly( void )` | desc_: Structure members defined from now on are read-only properties. }}*/
       void GwstReadOnly(void);
       /*{{|method_: `void GwstReadWrite( void )` | desc_: Back to read-write members (the default). }}*/
       void GwstReadWrite(void);
       /*{{|method_: `void GwstBeginUnion( void )` | desc_: Opens a union: the members that follow all start at the current offset. }}*/
       void GwstBeginUnion(void);
       /*{{|method_: `void GwstEndUnion( void )` | desc_: Closes the union: the offset advances by its largest member. Create() closes an open union itself. }}*/
       void GwstEndUnion(void);
       /*{{|method_: `void GwstSkipBytes( ULONG nBytes )` | desc_: Leaves **nBytes** unnamed at the current offset (inside a union, counts them as a member of that size). }}*/
       void GwstSkipBytes(ULONG nBytes);
       /*{{|method_: `void GwstAdjustSize( ULONG nBytes )` | desc_: Makes the structure at least **nBytes** long (the offset, or the union, grows to it). }}*/
       void GwstAdjustSize( ULONG nBytes );
       /*{{|method_: `UINT GwstGetOffset( void )` | desc_: The current offset. }}*/
       UINT GwstGetOffset(void);
       /*{{|method_: `void GwstSetOffset( UINT nn )` | desc_: Sets the current offset, to overlay members by hand. }}*/
       void GwstSetOffset( UINT);
       /*{{|method_: `void GwstBack( void )` | desc_: Moves the offset back to the start of the last member, so that the next one overlays it. }}*/
       void GwstBack(void);
       /*{{|method_: `void GwstAlignNextMember( DWORD dwAlign )` | desc_: Rounds the current offset up to a multiple of **dwAlign** (2, 4, 8). }}*/
       void GwstAlignNextMember(DWORD dwAlign);
       /*{{|method_: `void _xchild_( LPSTR pName, ContainerHandle conco )` | desc_: Child() with the child structure given as a class object (taken over). }}*/
       void _xchild_(LPSTR pName , ContainerHandle conco );
       /*{{|method_: `void Child( LPSTR pName, LPSTR pClassName )` | desc_: Embeds a structure of the GWST class **pClassName** at the current offset, advancing it by that structure's size: **pName** becomes a read-only property returning the child object, which maps the bytes in place. }}*/
       void Child(LPSTR pName , LPSTR pClassName);
       /*{{|method_: `void Member( LPSTR pName, ULONG nMType, UINT nSize )` | desc_: Defines a structure member of **nSize** bytes at the current offset with the GWST member type **nMType** (a `__GWST_MEMBER_*__` constant), advancing the offset (or widening the open union). The member becomes a property whose access and assign call the `_GWST_XBSETGET_*` function of the type over the object's memory. The Member_*() functions below are the typed shortcuts. }}*/
       void Member(LPSTR pName , ULONG nMType, UINT nSize);
       /*{{|method_: `void Member_Bool( LPSTR pName )` | desc_: A 4-byte BOOL, read and written as Logical. }}*/
       void Member_Bool(LPSTR pName);
       /*{{|method_: `void Member_Byte( LPSTR pName )` | desc_: A BYTE (1 byte), as Numeric 0 to 255. }}*/
       void Member_Byte(LPSTR pName);
       /*{{|method_: `void Member_Word( LPSTR pName )` | desc_: A WORD (2 bytes), as unsigned Numeric. }}*/
       void Member_Word(LPSTR pName);
       /*{{|method_: `void Member_Int16( LPSTR pName )` | desc_: Same as Member_Word() (unsigned: use Member_SINT16() for a signed 16-bit value). }}*/
       void Member_Int16(LPSTR pName);
       /*{{|method_: `void Member_Short( LPSTR pName )` | desc_: Same as Member_Word(). }}*/
       void Member_Short(LPSTR pName);
       /*{{|method_: `void Member_DWord( LPSTR pName )` | desc_: A DWORD (4 bytes), as signed 32-bit Numeric (the LONG view: use Member_UINT32() for the unsigned range). }}*/
       void Member_DWord(LPSTR pName);
       /*{{|method_: `void Member_ULong( LPSTR pName )` | desc_: Same as Member_DWord(). }}*/
       void Member_ULong(LPSTR pName);
       /*{{|method_: `void Member_Long( LPSTR pName )` | desc_: Same as Member_DWord(). }}*/
       void Member_Long(LPSTR pName);
       /*{{|method_: `void Member_UInt( LPSTR pName )` | desc_: Same as Member_DWord(). }}*/
       void Member_UInt(LPSTR pName);
       /*{{|method_: `void Member_Int( LPSTR pName )` | desc_: Same as Member_DWord(). }}*/
       void Member_Int(LPSTR pName);
       /*{{|method_: `void Member_Int32( LPSTR pName )` | desc_: Same as Member_DWord(). }}*/
       void Member_Int32(LPSTR pName);
       /*{{|method_: `void Member_LParam( LPSTR pName )` | desc_: Same as Member_DWord(). }}*/
       void Member_LParam(LPSTR pName);
       /*{{|method_: `void Member_WParam( LPSTR pName )` | desc_: Same as Member_DWord(). }}*/
       void Member_WParam(LPSTR pName);
       /*{{|method_: `void Member_Pointer( LPSTR pName )` | desc_: A 32-bit pointer, read and written as Numeric. }}*/
       void Member_Pointer(LPSTR pName);
       /*{{|method_: `void Member_Pointer32( LPSTR pName )` | desc_: Same as Member_Pointer(). }}*/
       void Member_Pointer32(LPSTR pName);
       /*{{|method_: `void Member_Handle( LPSTR pName )` | desc_: A HANDLE (4 bytes), as Numeric. }}*/
       void Member_Handle(LPSTR pName);
       /*{{|method_: `void Member_hWnd( LPSTR pName )` | desc_: Same as Member_Handle(). }}*/
       void Member_hWnd(LPSTR pName);
       /*{{|method_: `void Member_hDC( LPSTR pName )` | desc_: Same as Member_Handle(). }}*/
       void Member_hDC(LPSTR pName);
       /*{{|method_: `void Member_pClipVar( LPSTR pName )` | desc_: A 4-byte slot holding a reference to an Xbase++ value (any type), kept alive by the structure. }}*/
       void Member_pClipVar(LPSTR pName);
       /*{{|method_: `void Member_CodeBlock( LPSTR pName )` | desc_: Same as Member_pClipVar(). }}*/
       void Member_CodeBlock(LPSTR pName);
       /*{{|method_: `void Member_lpXBase( LPSTR pName )` | desc_: Same as Member_pClipVar(). }}*/
       void Member_lpXBase(LPSTR pName);
       /*{{|method_: `void Member_Xbase( LPSTR pName )` | desc_: Same as Member_pClipVar(). }}*/
       void Member_Xbase(LPSTR pName);
       /*{{|method_: `void Member_XDate( LPSTR pName )` | desc_: An 8-byte member read and written as an Xbase++ Date. }}*/
       void Member_XDate(LPSTR pName);
       /*{{|method_: `void Member_DWord64( LPSTR pName )` | desc_: An 8-byte integer, read and written as an 8-byte Character (the QWORD convention). }}*/
       void Member_DWord64(LPSTR pName);
       /*{{|method_: `void Member_Double( LPSTR pName )` | desc_: A double (8 bytes), as Numeric. }}*/
       void Member_Double(LPSTR pName);
       /*{{|method_: `void Member_Float( LPSTR pName )` | desc_: A float (4 bytes), as Numeric. }}*/
       void Member_Float(LPSTR pName);
       /*{{|method_: `void Member_lpStr( LPSTR pName )` | desc_: A pointer to a zero-terminated string: read as the string it points to, written as the pointer. }}*/
       void Member_lpStr(LPSTR pName);
       /*{{|method_: `void Member_BinStr( LPSTR pName, UINT nSize )` | desc_: **nSize** raw bytes, read and written as a Character of exactly that length. }}*/
       void Member_BinStr(LPSTR pName , UINT nSize);
       /*{{|method_: `void Member_szStr( LPSTR pName, UINT nSize )` | desc_: A zero-terminated string of up to **nSize** bytes in place. }}*/
       void Member_szStr(LPSTR pName , UINT nSize);
       /*{{|method_: `void Member_szWStr( LPSTR pName, UINT nSize )` | desc_: A zero-terminated UTF-16 string of up to **nSize** characters in place (2 * nSize bytes), converted from and to ANSI. }}*/
       void Member_szWStr(LPSTR pName , UINT nSize);
       /*{{|method_: `void Member_DynSz( LPSTR pName )` | desc_: A pointer to a string that the structure allocates and frees itself when assigned. }}*/
       void Member_DynSz(LPSTR pName );
       /*{{|method_: `void Member_WordNet( LPSTR pName )` | desc_: A WORD in network byte order (big endian), as Numeric. }}*/
       void Member_WordNet(LPSTR pName );
       /*{{|method_: `void Member_DWordNet( LPSTR pName )` | desc_: A DWORD in network byte order, as Numeric. }}*/
       void Member_DWordNet(LPSTR pName );
       /*{{|method_: `void Member_XppGuiWnd( LPSTR pName )` | desc_: A window handle, read as the Xbase++ GUI object owning it and written from such an object. }}*/
       void Member_XppGuiWnd(LPSTR pName );
       /*{{|method_: `void Member_SINT8( LPSTR pName )` | desc_: A signed 8-bit integer, as Numeric. }}*/
       void Member_SINT8(LPSTR pName  );
       /*{{|method_: `void Member_SINT16( LPSTR pName )` | desc_: A signed 16-bit integer, as Numeric. }}*/
       void Member_SINT16(LPSTR pName );
       /*{{|method_: `void Member_UINT32( LPSTR pName )` | desc_: An unsigned 32-bit integer, as Numeric (0 to 4294967295). }}*/
       void Member_UINT32(LPSTR pName );
       /*{{|method_: `void Member_NINT64( LPSTR pName )` | desc_: A signed 64-bit integer, as Numeric. }}*/
       void Member_NINT64(LPSTR pName );
       /*{{|method_: `void Member_ByteBool( LPSTR pName )` | desc_: A 1-byte boolean, as Logical. }}*/
       void Member_ByteBool(LPSTR pName );
       /*{{|method_: `void Member_BitField( LPSTR pName, LPSTR pHolder, DWORD sh, DWORD cb, DWORD nBits = 32 )` | desc_: A property over **cb** bits starting at bit **sh** of the already defined member **pHolder**, a 32, 16 or 8-bit integer by **nBits**: reading extracts them, assigning replaces them. No offset is consumed. }}*/
       void Member_BitField(LPSTR pName , LPSTR pHolder , DWORD sh, DWORD cb , DWORD nBits = 32);
       /*{{|method_: `void Member_EmbededStructArray( LPSTR pName, LPSTR pCls, LPSTR pHolder, LPSTR pCounter, DWORD sh, DWORD cb )` | desc_: A method **pName( n )** returning the n-th (zero-based) structure of the GWST class **pCls** of an array embedded at offset **sh** with **cb** bytes per element, whose element count is the member **pCounter**; the child objects are cached in an instance variable `_array_<pName>`. Called without n it returns the address of the member **pHolder**. }}*/
       void Member_EmbededStructArray(LPSTR pName , LPSTR pCls , LPSTR pHolder, LPSTR pCounter, DWORD sh, DWORD cb);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `LPSTR cbbs( LPSTR s, ... )` | desc_: printf-style formatting into the builder's work buffer (1 KB): the text the *_cbbs functions build their blocks with. Valid until the next call. }}*/
       LPSTR cbbs(LPSTR s, ... );
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void opaque_prop_ansi2wide( LPSTR pName, DWORD offset )` | desc_: For a class backed by a C++ object (AddGwstStyleMembers()): a Character property over the `LPWSTR` field at **offset** in that object, converted from and to ANSI; assigning frees the previous string and allocates the new one. }}*/
       void opaque_prop_ansi2wide( LPSTR pName , DWORD offset );
       /*{{|method_: `void opaque_prop_ARGB( LPSTR pName, DWORD offset )` | desc_: Same for a `LONG` field (an ARGB colour, or any 32-bit value), as Numeric. }}*/
       void opaque_prop_ARGB( LPSTR pName , DWORD offset );
};
/*{{end-cpp-class}}*/
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TXbClsParams
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , ot4xb-api
   | desc: What a C method or property receives: the object built by `_xbmtpf1_` around the parameter list of
     the generated block, giving the function Self, the parameters, the extra literal arguments of the
     definition, the return value and an error slot, every one of them a
     {{ilink: <cpp-class TXbCPItem> TXbCPItem}} with typed accessors. A method is a
     `void fn( TXbClsParams* px )` registered with TXbClass::Method(); it reads `px->GetParam...( n )`, writes
     `px->PutReturn...()` and, to fail, calls GenError() and the SetError*() setters: the generated block then
     raises the Error instead of returning. For a class backed by a C++ object, GetSelfC() is the pointer
     kept in Self:_m__pt_.
   | note: A property function is called both for access (PCount() 0) and assign (PCount() 1, the value in
     parameter 1). Parameters are 1-based everywhere; an index out of range reads as 0, FALSE or
     NULLCONTAINER and writes nothing.
   | example:
     static void MyPoint_distance( TXbClsParams* px )   // METHOD distance( oOther )
     {
        ContainerHandle other = px->GetTParam( 1, XPP_OBJECT );
        if( !other )
        {
           px->GenError();
           px->SetErrorDescription( "MyPoint expected" );
           px->SetErrorArgs();
           return;
        }
        double dx = px->GetMemberDouble( "x" ) - _conGetNDMember( other, "x" );
        double dy = px->GetMemberDouble( "y" ) - _conGetNDMember( other, "y" );
        px->PutReturnDouble( sqrt( dx * dx + dy * dy ) );
     | _kw_: method parameters, C method, Self, return value, GenError, extra arguments
     } }}*/
class OT4XB_API TXbClsParams : public T_ot4xb_base
{
   public:
       /*{{|member_: `XppParamList m_pl` | desc_: The parameter list of the generated block. }}*/
       XppParamList        m_pl;
       /*{{|member_: `BOOL m_bResult` | desc_: TRUE until GenError() is called; the block returns the value
          when TRUE and raises the error otherwise. }}*/
       BOOL                m_bResult;
       /*{{|member_: `TXbCPItem* m_return` | desc_: The return value (a by-reference slot of the block). }}*/
       TXbCPItem *         m_return;
       /*{{|member_: `TXbCPItem* m_error` | desc_: The error slot, an Error object after GenError(). }}*/
       TXbCPItem *         m_error;
       /*{{|member_: `TXbCPItem* m_Self` | desc_: Self. }}*/
       TXbCPItem *         m_Self;
       /*{{|member_: `TXbCPItem** m_params` | desc_: The parameters (after ShiftParams(), the remaining
          ones). }}*/
       TXbCPItem **        m_params;
       /*{{|member_: `ULONG m_paramsCount` | desc_: Parameters passed by the caller (the PCount() of the
          method). }}*/
       ULONG               m_paramsCount;
       /*{{|member_: `TXbCPItem** m_eparams` | desc_: The extra arguments given as **pExtra** when the method
          was defined, 0 when none. }}*/
       TXbCPItem **        m_eparams;
       /*{{|member_: `ULONG m_eparamsCount` | desc_: Their number. }}*/
       ULONG               m_eparamsCount;
       /*{{|member_: `TXbCPItem** m_real` | desc_: Every slot of the block's parameter list, as received. }}*/
       TXbCPItem **        m_real;
       /*{{|member_: `ULONG m_realCount` | desc_: Their number. }}*/
       ULONG               m_realCount;
       /*{{|member_: `ULONG m_formalCount` | desc_: Formal parameters the method was declared with. }}*/
       ULONG               m_formalCount;
       /*{{|method_: `TXbClsParams( XppParamList pl )` | desc_: Splits the block's parameter list into Self, return, error, the parameters and the extras. Built by `_xbmtpf1_`, not by user code. }}*/
       TXbClsParams( XppParamList pl);
       /*{{|method_: `~TXbClsParams( void )` | desc_: Releases every item (unlocking what is locked); the return and error slots are references the block keeps. }}*/
       ~TXbClsParams( void );       
       // ---------------------------------------------------------------------------------       
       /*{{|method_: `void ShiftParams( LONG nParams )` | desc_: Drops **nParams** leading parameters from the view (negative: puts them back), so that a function serving several methods can skip the ones it has consumed. Clipped to the real count. }}*/
       void            ShiftParams(LONG nParams);
       /*{{|method_: `void ResetShiftParams( void )` | desc_: Back to the full parameter view. }}*/
       void            ResetShiftParams(void);
       /*{{|method_: `ULONG PCount( void )` | desc_: Parameters passed by the caller (in the current view). }}*/
       ULONG           PCount(void);
       /*{{|method_: `ULONG GetParamType( ULONG np )` | desc_: XPP_* type mask of parameter **np**, 0 out of range. }}*/
       ULONG           GetParamType(ULONG np);
       /*{{|method_: `BOOL CheckParamType( ULONG np, ULONG ulType )` | desc_: TRUE when parameter **np** has one of the types in **ulType**. }}*/
       BOOL            CheckParamType(ULONG np , ULONG ulType);
       /*{{|method_: `ContainerHandle GetTParam( ULONG np, ULONG ulType, BOOL* pbByRef = 0 )` | desc_: The container of parameter **np** when its type matches, NULLCONTAINER otherwise. Still owned by the item. }}*/
       ContainerHandle GetTParam( ULONG np , ULONG ulType , BOOL * pbByRef = 0);
       /*{{|method_: `ContainerHandle GetParam( ULONG np, BOOL* pbByRef = 0 )` | desc_: The container of parameter **np** (and whether it came by reference). Still owned by the item. }}*/
       ContainerHandle GetParam( ULONG np , BOOL * pbByRef = 0);
       /*{{|method_: `void PutParam( ULONG np, ContainerHandle con )` | desc_: Copies a value into parameter **np** (the caller's variable when passed by reference). }}*/
       void            PutParam( ULONG np , ContainerHandle con );
       /*{{|method_: `BOOL GetParamBool( ULONG np )` | desc_: Parameter **np** as Logical. }}*/
       BOOL            GetParamBool(ULONG np);
       /*{{|method_: `LONG GetParamLong( ULONG np )` | desc_: Parameter **np** as LONG. }}*/
       LONG            GetParamLong(ULONG np);
       /*{{|method_: `DWORD GetParamDWord( ULONG np )` | desc_: Parameter **np** as DWORD. }}*/
       DWORD           GetParamDWord(ULONG np);
       /*{{|method_: `LONGLONG GetParamQWord( ULONG np )` | desc_: Parameter **np** as a 64-bit integer (see TXbCPItem::GetQWord() for the accepted forms). }}*/
       LONGLONG        GetParamQWord(ULONG np);
       /*{{|method_: `WORD GetParamWord( ULONG np )` | desc_: Parameter **np** as WORD. }}*/
       WORD            GetParamWord(ULONG np);
       /*{{|method_: `DWORD GetParamLoHi2DWord( ULONG np )` | desc_: Parameters **np** and np + 1 as the low and high words of one DWORD. }}*/
       DWORD           GetParamLoHi2DWord(ULONG np);
       /*{{|method_: `double GetParamDouble( ULONG np )` | desc_: Parameter **np** as double. }}*/
       double          GetParamDouble(ULONG np);
       /*{{|method_: `FLOAT GetParamFloat( ULONG np )` | desc_: Parameter **np** as float. }}*/
       FLOAT           GetParamFloat(ULONG np);
       /*{{|method_: `HWND GetParamHWND( ULONG np )` | desc_: Parameter **np** as a window handle (a Numeric, or an object with :GetHWND()). }}*/
       HWND            GetParamHWND( ULONG np);
       /*{{|method_: `void PutParamBool( ULONG np, BOOL value )` | desc_: Stores a Logical in parameter **np**. }}*/
       void            PutParamBool(ULONG np       , BOOL     value );
       /*{{|method_: `void PutParamLong( ULONG np, LONG value )` | desc_: Stores a Numeric. }}*/
       void            PutParamLong(ULONG np       , LONG     value );
       /*{{|method_: `void PutParamDWord( ULONG np, DWORD value )` | desc_: Stores a Numeric. }}*/
       void            PutParamDWord(ULONG np      , DWORD    value );
       /*{{|method_: `void PutParamQWord( ULONG np, LONGLONG value )` | desc_: Stores an 8-byte Character (QWORD). }}*/
       void            PutParamQWord(ULONG np      , LONGLONG    value );
       /*{{|method_: `void PutParamWord( ULONG np, WORD value )` | desc_: Stores a Numeric. }}*/
       void            PutParamWord(ULONG np       , WORD     value );
       /*{{|method_: `void PutParamDWord2LoHi( ULONG np, DWORD value )` | desc_: Stores the low word in parameter **np** and the high word in np + 1. }}*/
       void            PutParamDWord2LoHi(ULONG np , DWORD    value );
       /*{{|method_: `void PutParamDouble( ULONG np, double value )` | desc_: Stores a Numeric. }}*/
       void            PutParamDouble(ULONG np     , double   value );
       /*{{|method_: `void PutParamFloat( ULONG np, FLOAT value )` | desc_: Stores a Numeric. }}*/
       void            PutParamFloat(ULONG np      , FLOAT    value );
       /*{{|method_: `LPSTR ParamStrDup( ULONG np, ULONG* pnLen = 0 )` | desc_: A zero-terminated copy of the Character parameter (free with _xfree), its length in **pnLen**; 0 when not a Character. }}*/
       LPSTR           ParamStrDup(ULONG np , ULONG * pnLen = 0);
       /*{{|method_: `LPWSTR ParamStrDupW( ULONG np, ULONG* pnBytes = 0 )` | desc_: A wide copy of the Character parameter (free with _xfree). }}*/
       LPWSTR          ParamStrDupW(ULONG np , ULONG * pnBytes = 0);
       /*{{|method_: `ULONG ParamGetCL( ULONG np, LPSTR pDst, ULONG nBuffSize )` | desc_: Copies up to **nBuffSize** bytes of the Character parameter into **pDst**; returns its length. }}*/
       ULONG           ParamGetCL(ULONG np , LPSTR pDst , ULONG nBuffSize);
       /*{{|method_: `LPSTR ParamLockStr( ULONG np, ULONG* pnSize = 0, BOOL bWrite = FALSE )` | desc_: Locks the Character parameter and returns its bytes (length in **pnSize**); 0 when not a Character. }}*/
       LPSTR           ParamLockStr(ULONG np , ULONG * pnSize = 0 , BOOL bWrite = FALSE );
       /*{{|method_: `void ParamUnlockStr( ULONG np )` | desc_: Releases the lock. }}*/
       void            ParamUnlockStr(ULONG np);
       /*{{|method_: `void ParamPutStrLen( ULONG np, LPSTR pStr, ULONG nLen )` | desc_: Stores **nLen** bytes as a Character. }}*/
       void            ParamPutStrLen(ULONG np,LPSTR pStr , ULONG nLen);
       /*{{|method_: `void ParamPutStr( ULONG np, LPSTR pStr )` | desc_: Stores a zero-terminated string as a Character. }}*/
       void            ParamPutStr(ULONG np,LPSTR pStr);
       /*{{|method_: `LPSTR ParamRLockStrEx( ULONG np )` | desc_: The bytes behind parameter **np** (Character, numeric array packed as integers, or object with _lock_()), for reading. See TXbCPItem::_LockStrEx_(). }}*/
       LPSTR           ParamRLockStrEx(ULONG np);
       /*{{|method_: `LPSTR ParamWLockStrEx( ULONG np )` | desc_: Same for writing (a packed array is written back on unlock). }}*/
       LPSTR           ParamWLockStrEx(ULONG np);
       /*{{|method_: `LPSTR ParamRLockStrExF( ULONG np )` | desc_: Read lock, array numbers as float. }}*/
       LPSTR           ParamRLockStrExF(ULONG np);
       /*{{|method_: `LPSTR ParamWLockStrExF( ULONG np )` | desc_: Write lock, array numbers as float. }}*/
       LPSTR           ParamWLockStrExF(ULONG np);
       /*{{|method_: `LPSTR ParamRLockStrExF8( ULONG np )` | desc_: Read lock, array numbers as double. }}*/
       LPSTR           ParamRLockStrExF8(ULONG np);
       /*{{|method_: `LPSTR ParamWLockStrExF8( ULONG np )` | desc_: Write lock, array numbers as double. }}*/
       LPSTR           ParamWLockStrExF8(ULONG np);
       /*{{|method_: `void ParamUnLockStrEx( ULONG np )` | desc_: Releases the extended lock. }}*/
       void            ParamUnLockStrEx(ULONG np);
       /*{{|method_: `ULONG ParamExLen( ULONG np )` | desc_: Bytes of the extended lock. }}*/
       ULONG           ParamExLen(ULONG np);
       // -------------
       /*{{|method_: `BOOL ParamGetGuid( ULONG np, GUID* pDst )` | desc_: Reads a GUID from the parameter (16 raw bytes, text form, or lockable bytes). }}*/
       BOOL            ParamGetGuid(ULONG np, GUID* pDst);
       /*{{|method_: `BOOL ParamPutGuid( ULONG np, GUID* pSrc, BOOL bBraces = FALSE )` | desc_: Stores a GUID as text. }}*/
       BOOL            ParamPutGuid(ULONG np, GUID* pSrc , BOOL bBraces = FALSE);
       // -------------
       /*{{|method_: `void Param_setprop_ansi2wide( ULONG np, LPWSTR* ppw )` | desc_: Replaces the wide string ***ppw** with a wide copy of the Character parameter (for a property setter). }}*/
       void            Param_setprop_ansi2wide( ULONG np , LPWSTR*  ppw );
       // ---------------------------------------------------------------------------------

       // ---------------------------------------------------------------------------------
       /*{{|method_: `ULONG ECount( void )` | desc_: Number of extra arguments (the **pExtra** literals of the definition). }}*/
       ULONG           ECount(void);
       /*{{|method_: `ULONG GetExtraType( ULONG np )` | desc_: Type mask of extra argument **np**. }}*/
       ULONG           GetExtraType(ULONG np);
       /*{{|method_: `BOOL CheckExtraType( ULONG np, ULONG ulType )` | desc_: TRUE when extra **np** has one of the types in **ulType**. }}*/
       BOOL            CheckExtraType(ULONG np , ULONG ulType);
       /*{{|method_: `ContainerHandle GetTExtra( ULONG np, ULONG ulType, BOOL* pbByRef = 0 )` | desc_: The container of extra **np** when its type matches. }}*/
       ContainerHandle GetTExtra( ULONG np , ULONG ulType , BOOL * pbByRef = 0);
       /*{{|method_: `ContainerHandle GetExtra( ULONG np, BOOL* pbByRef = 0 )` | desc_: The container of extra **np**. }}*/
       ContainerHandle GetExtra( ULONG np , BOOL * pbByRef = 0);
       /*{{|method_: `void PutExtra( ULONG np, ContainerHandle con )` | desc_: Copies a value into extra **np**. }}*/
       void            PutExtra( ULONG np , ContainerHandle con );
       /*{{|method_: `BOOL GetExtraBool( ULONG np )` | desc_: Extra **np** as Logical. }}*/
       BOOL            GetExtraBool(ULONG np);
       /*{{|method_: `LONG GetExtraLong( ULONG np )` | desc_: Extra **np** as LONG (the usual way to read an offset or an id given at definition time). }}*/
       LONG            GetExtraLong(ULONG np);
       /*{{|method_: `DWORD GetExtraDWord( ULONG np )` | desc_: Extra **np** as DWORD. }}*/
       DWORD           GetExtraDWord(ULONG np);
       /*{{|method_: `LONGLONG GetExtraQWord( ULONG np )` | desc_: Extra **np** as a 64-bit integer. }}*/
       LONGLONG        GetExtraQWord(ULONG np);
       /*{{|method_: `WORD GetExtraWord( ULONG np )` | desc_: Extra **np** as WORD. }}*/
       WORD            GetExtraWord(ULONG np);
       /*{{|method_: `DWORD GetExtraLoHi2DWord( ULONG np )` | desc_: Extras **np** and np + 1 as one DWORD. }}*/
       DWORD           GetExtraLoHi2DWord(ULONG np);
       /*{{|method_: `double GetExtraDouble( ULONG np )` | desc_: Extra **np** as double. }}*/
       double          GetExtraDouble(ULONG np);
       /*{{|method_: `FLOAT GetExtraFloat( ULONG np )` | desc_: Extra **np** as float. }}*/
       FLOAT           GetExtraFloat(ULONG np);
       /*{{|method_: `ULONG ExtraGetCL( ULONG np, LPSTR pDst, ULONG nBuffSize )` | desc_: Copies the Character extra into a buffer; returns its length. }}*/
       ULONG           ExtraGetCL(ULONG np , LPSTR pDst , ULONG nBuffSize);
       /*{{|method_: `void PutExtraBool( ULONG np, BOOL value )` | desc_: Stores a Logical in extra **np**. }}*/
       void            PutExtraBool(ULONG np       , BOOL     value );
       /*{{|method_: `void PutExtraLong( ULONG np, LONG value )` | desc_: Stores a Numeric. }}*/
       void            PutExtraLong(ULONG np       , LONG     value );
       /*{{|method_: `void PutExtraDWord( ULONG np, DWORD value )` | desc_: Stores a Numeric. }}*/
       void            PutExtraDWord(ULONG np      , DWORD    value );
       /*{{|method_: `void PutExtraQWord( ULONG np, LONGLONG value )` | desc_: Stores an 8-byte Character. }}*/
       void            PutExtraQWord(ULONG np      , LONGLONG    value );
       /*{{|method_: `void PutExtraWord( ULONG np, WORD value )` | desc_: Stores a Numeric. }}*/
       void            PutExtraWord(ULONG np       , WORD     value );
       /*{{|method_: `void PutExtraDWord2LoHi( ULONG np, DWORD value )` | desc_: Stores the low and high words in extras **np** and np + 1. }}*/
       void            PutExtraDWord2LoHi(ULONG np , DWORD    value );
       /*{{|method_: `void PutExtraDouble( ULONG np, double value )` | desc_: Stores a Numeric. }}*/
       void            PutExtraDouble(ULONG np     , double   value );
       /*{{|method_: `void PutExtraFloat( ULONG np, FLOAT value )` | desc_: Stores a Numeric. }}*/
       void            PutExtraFloat(ULONG np      , FLOAT    value );
       /*{{|method_: `LPSTR ExtraLockStr( ULONG np, ULONG* pnSize = 0, BOOL bWrite = FALSE )` | desc_: Locks the Character extra. }}*/
       LPSTR           ExtraLockStr(ULONG np , ULONG * pnSize = 0 , BOOL bWrite = FALSE );
       /*{{|method_: `void ExtraUnlockStr( ULONG np )` | desc_: Releases the lock. }}*/
       void            ExtraUnlockStr(ULONG np);
       /*{{|method_: `void ExtraPutStrLen( ULONG np, LPSTR pStr, ULONG nLen )` | desc_: Stores **nLen** bytes as a Character. }}*/
       void            ExtraPutStrLen(ULONG np,LPSTR pStr , ULONG nLen);
       /*{{|method_: `void ExtraPutStr( ULONG np, LPSTR pStr )` | desc_: Stores a zero-terminated string. }}*/
       void            ExtraPutStr(ULONG np,LPSTR pStr);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `ContainerHandle GetSelf( void )` | desc_: Self (owned by the item). }}*/
       ContainerHandle GetSelf(void);
       /*{{|method_: `void* GetSelfC( void )` | desc_: The C++ object behind Self: the value of the `_m__pt_` member (see TXbClass::AddGwstStyleMembers()), 0 when there is none. }}*/
       void * GetSelfC(void);
       /*{{|method_: `void SetSelfC( void* p )` | desc_: Stores the C++ object pointer in Self:_m__pt_. }}*/
       void SetSelfC(void *);
       /*{{|method_: `void PutReturnSelf( void )` | desc_: Returns Self (for chaining methods). }}*/
       void PutReturnSelf(void);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `ULONG GetReturnType( void )` | desc_: Type mask of the current return value. }}*/
       ULONG GetReturnType(void);
       /*{{|method_: `BOOL CheckReturnType( ULONG ulType )` | desc_: TRUE when the return value has one of the types in **ulType**. }}*/
       BOOL CheckReturnType(ULONG ulType);
       /*{{|method_: `ContainerHandle GetReturn( void )` | desc_: The return container, to be filled through the container API. }}*/
       ContainerHandle GetReturn(void);
       /*{{|method_: `void PutReturn( ContainerHandle con = 0 )` | desc_: Copies a value as the return value (NIL for 0). }}*/
       void PutReturn(ContainerHandle con = 0 );
       /*{{|method_: `BOOL GetReturnBool( void )` | desc_: The return value as Logical. }}*/
       BOOL GetReturnBool(void);
       /*{{|method_: `LONG GetReturnLong( void )` | desc_: The return value as LONG. }}*/
       LONG GetReturnLong(void);
       /*{{|method_: `DWORD GetReturnDWord( void )` | desc_: The return value as DWORD. }}*/
       DWORD GetReturnDWord(void);
       /*{{|method_: `LONGLONG GetReturnQWord( void )` | desc_: The return value as a 64-bit integer. }}*/
       LONGLONG GetReturnQWord(void);
       /*{{|method_: `WORD GetReturnWord( void )` | desc_: The return value as WORD. }}*/
       WORD GetReturnWord(void);
       /*{{|method_: `double GetReturnDouble( void )` | desc_: The return value as double. }}*/
       double GetReturnDouble(void);
       /*{{|method_: `FLOAT GetReturnFloat( void )` | desc_: The return value as float. }}*/
       FLOAT GetReturnFloat(void);
       /*{{|method_: `void PutReturnBool( BOOL value )` | desc_: Returns a Logical. }}*/
       void PutReturnBool(BOOL value );
       /*{{|method_: `void PutReturnLong( LONG value )` | desc_: Returns a Numeric. }}*/
       void PutReturnLong(LONG value );
       /*{{|method_: `void PutReturnDWord( DWORD value )` | desc_: Returns a Numeric. }}*/
       void PutReturnDWord(DWORD value );
       /*{{|method_: `void PutReturnQWord( LONGLONG value )` | desc_: Returns an 8-byte Character (QWORD). }}*/
       void PutReturnQWord(LONGLONG    value );
       /*{{|method_: `void PutReturnWord( WORD value )` | desc_: Returns a Numeric. }}*/
       void PutReturnWord(WORD value);
       /*{{|method_: `void PutReturnDouble( double value )` | desc_: Returns a Numeric. }}*/
       void PutReturnDouble(double value );
       /*{{|method_: `void PutReturnFloat( FLOAT value )` | desc_: Returns a Numeric. }}*/
       void PutReturnFloat(FLOAT value );
       /*{{|method_: `void PutReturnStrLen( LPSTR pStr, ULONG nLen )` | desc_: Returns **nLen** bytes as a Character. }}*/
       void PutReturnStrLen(LPSTR pStr , ULONG nLen);
       /*{{|method_: `void PutReturnStr( LPSTR pStr )` | desc_: Returns a zero-terminated string as a Character. }}*/
       void PutReturnStr(LPSTR pStr);
       /*{{|method_: `void PutReturnWStr( LPWSTR pWStr )` | desc_: Returns a wide string converted to ANSI. }}*/
       void PutReturnWStr(LPWSTR pWStr);
       /*{{|method_: `LPSTR LockReturnStr( ULONG* pnSize = 0, BOOL bWrite = FALSE )` | desc_: Locks the Character return value (after a PutReturn*), to fill it in place. }}*/
       LPSTR LockReturnStr(ULONG * pnSize = 0 , BOOL bWrite = FALSE );
       /*{{|method_: `void UnlockReturnStr( void )` | desc_: Releases the lock. }}*/
       void  UnlockReturnStr(void);
       // ------
       /*{{|method_: `BOOL GetReturnGuid( GUID* pDst )` | desc_: Reads a GUID from the return value. }}*/
       BOOL GetReturnGuid(GUID* pDst);
       /*{{|method_: `BOOL PutReturnGuid( GUID* pSrc, BOOL bBraces = FALSE )` | desc_: Returns a GUID as text. }}*/
       BOOL PutReturnGuid(GUID* pSrc , BOOL bBraces = FALSE);
       // ------       
       /*{{|method_: `void PutReturn_getprop_wide2ansi( LPWSTR* ppw )` | desc_: Returns the wide string ***ppw** converted to ANSI (for a property getter). }}*/
       void PutReturn_getprop_wide2ansi( LPWSTR* ppw );
       // ------
       /*{{|method_: `LPSTR ReturnRLockStrEx( void )` | desc_: Extended read lock of the return value. }}*/
       LPSTR ReturnRLockStrEx(void);
       /*{{|method_: `LPSTR ReturnWLockStrEx( void )` | desc_: Extended write lock of the return value. }}*/
       LPSTR ReturnWLockStrEx(void);
       /*{{|method_: `LPSTR ReturnRLockStrExF( void )` | desc_: Read lock, array numbers as float. }}*/
       LPSTR ReturnRLockStrExF(void);
       /*{{|method_: `LPSTR ReturnWLockStrExF( void )` | desc_: Write lock, array numbers as float. }}*/
       LPSTR ReturnWLockStrExF(void);
       /*{{|method_: `LPSTR ReturnRLockStrExF8( void )` | desc_: Read lock, array numbers as double. }}*/
       LPSTR ReturnRLockStrExF8(void);
       /*{{|method_: `LPSTR ReturnWLockStrExF8( void )` | desc_: Write lock, array numbers as double. }}*/
       LPSTR ReturnWLockStrExF8(void);
       /*{{|method_: `void ReturnUnLockStrEx( void )` | desc_: Releases the extended lock. }}*/
       void  ReturnUnLockStrEx(void);
       /*{{|method_: `ULONG ReturnExLen( void )` | desc_: Bytes of the extended lock. }}*/
       ULONG ReturnExLen(void);
       /*{{|method_: `BOOL ReturnNewObj( LPSTR pClassName, ContainerHandle p1, ... )` | desc_: Returns a new object of class **pClassName** created with :new( p1, ... ), the argument list ending with 0. The arguments stay the caller's. FALSE (and a NIL return) when the class does not exist or :new() gave no object. }}*/
       BOOL  ReturnNewObj(LPSTR pClassName, ContainerHandle p1 , ... );
       /*{{|method_: `BOOL ReturnNewObjR( LPSTR pClassName, ContainerHandle p1, ... )` | desc_: Same, releasing every argument container afterwards. }}*/
       BOOL  ReturnNewObjR(LPSTR pClassName, ContainerHandle p1 , ... );
       /*{{|method_: `void ReturnNewArray( DWORD nDim = 0, DWORD* pDim = 0 )` | desc_: Returns a new array with the **nDim** sizes in **pDim** (an empty array by default). }}*/
       void  ReturnNewArray(DWORD nDim = 0, DWORD* pDim = 0);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void GenError( void )` | desc_: Creates an Error object in the error slot and marks the call as failed: when the function returns, the generated block evaluates the error block with it instead of returning a value. Fill it with the SetError*() functions. }}*/
       void GenError(void);
       /*{{|method_: `ContainerHandle GetError( void )` | desc_: The error slot (the Error object after GenError()). }}*/
       ContainerHandle GetError(void);
       /*{{|method_: `void SetErrorArgs( void )` | desc_: Sets :args to an array with the parameters of the call. }}*/
       void SetErrorArgs(void);
       /*{{|method_: `void SetErrorArgs( ContainerHandle cona )` | desc_: Sets :args to the given array. }}*/
       void SetErrorArgs( ContainerHandle cona );
       /*{{|method_: `void SetErrorDescription( LPSTR p )` | desc_: Sets :description. }}*/
       void SetErrorDescription( LPSTR );
       /*{{|method_: `void SetErrorFilename( LPSTR p )` | desc_: Sets :filename. }}*/
       void SetErrorFilename( LPSTR );
       /*{{|method_: `void SetErrorGenCode( LONG n )` | desc_: Sets :genCode. }}*/
       void SetErrorGenCode( LONG );
       /*{{|method_: `void SetErrorOperation( LPSTR p )` | desc_: Sets :operation. }}*/
       void SetErrorOperation( LPSTR );
       /*{{|method_: `void SetErrorOsCode( LONG n )` | desc_: Sets :osCode. }}*/
       void SetErrorOsCode( LONG );
       /*{{|method_: `void SetErrorSeverity( LONG n )` | desc_: Sets :severity. }}*/
       void SetErrorSeverity( LONG );
       /*{{|method_: `void SetErrorSubCode( LONG n )` | desc_: Sets :subCode. }}*/
       void SetErrorSubCode( LONG );
       /*{{|method_: `void SetErrorSubSystem( LPSTR p )` | desc_: Sets :subSystem. }}*/
       void SetErrorSubSystem( LPSTR );
       // ---------------------------------------------------------------------------------
       /*{{|method_: `ULONG GetMemberType( LPSTR pName )` | desc_: Type mask of the member **pName** of Self. }}*/
       ULONG           GetMemberType(LPSTR pName);
       /*{{|method_: `BOOL CheckMemberType( LPSTR pName, ULONG ulType )` | desc_: TRUE when that member has one of the types in **ulType**. }}*/
       BOOL            CheckMemberType(LPSTR pName, ULONG ulType);
       /*{{|method_: `ContainerHandle GetTMember( LPSTR pName, ULONG ulType )` | desc_: A new container with the member when its type matches (release it). }}*/
       ContainerHandle GetTMember(LPSTR pName , ULONG ulType);
       /*{{|method_: `ContainerHandle GetMember( LPSTR pName )` | desc_: A new container with the value of the member (release it). }}*/
       ContainerHandle GetMember(LPSTR pName);
       /*{{|method_: `void PutMember( LPSTR pName, ContainerHandle con )` | desc_: Assigns a value to the member. }}*/
       void            PutMember(LPSTR pName, ContainerHandle con );
       /*{{|method_: `void PutMemberR( LPSTR pName, ContainerHandle con )` | desc_: Assigns and releases **con**. }}*/
       void            PutMemberR(LPSTR pName, ContainerHandle con );       
       /*{{|method_: `LPSTR GetMemberStr( LPSTR pName, ULONG* pnLen = 0 )` | desc_: A copy of the Character member (free with _xfree), its length in **pnLen**. }}*/
       LPSTR           GetMemberStr(LPSTR pName , ULONG * pnLen = 0);
       /*{{|method_: `LPWSTR GetMemberStr2W( LPSTR pName, ULONG* pnLen = 0 )` | desc_: A wide copy of the Character member (free with _xfree). }}*/
       LPWSTR          GetMemberStr2W(LPSTR pName , ULONG * pnLen = 0);       
       /*{{|method_: `BOOL GetMemberBool( LPSTR pName )` | desc_: The member as Logical. }}*/
       BOOL            GetMemberBool(LPSTR pName);
       /*{{|method_: `LONG GetMemberLong( LPSTR pName )` | desc_: The member as LONG. }}*/
       LONG            GetMemberLong(LPSTR pName);
       /*{{|method_: `DWORD GetMemberDWord( LPSTR pName )` | desc_: The member as DWORD. }}*/
       DWORD           GetMemberDWord(LPSTR pName);
       /*{{|method_: `WORD GetMemberWord( LPSTR pName )` | desc_: The member as WORD. }}*/
       WORD            GetMemberWord(LPSTR pName);
       /*{{|method_: `double GetMemberDouble( LPSTR pName )` | desc_: The member as double. }}*/
       double          GetMemberDouble(LPSTR pName);
       /*{{|method_: `FLOAT GetMemberFloat( LPSTR pName )` | desc_: The member as float. }}*/
       FLOAT           GetMemberFloat(LPSTR pName);
       /*{{|method_: `void PutMemberBool( LPSTR pName, BOOL value )` | desc_: Assigns a Logical to the member. }}*/
       void            PutMemberBool(LPSTR pName       , BOOL     value );
       /*{{|method_: `void PutMemberLong( LPSTR pName, LONG value )` | desc_: Assigns a Numeric. }}*/
       void            PutMemberLong(LPSTR pName       , LONG     value );
       /*{{|method_: `void PutMemberDWord( LPSTR pName, DWORD value )` | desc_: Assigns a Numeric. }}*/
       void            PutMemberDWord(LPSTR pName      , DWORD    value );
       /*{{|method_: `void PutMemberWord( LPSTR pName, WORD value )` | desc_: Assigns a Numeric. }}*/
       void            PutMemberWord(LPSTR pName       , WORD     value );
       /*{{|method_: `void PutMemberDouble( LPSTR pName, double value )` | desc_: Assigns a Numeric. }}*/
       void            PutMemberDouble(LPSTR pName     , double   value );
       /*{{|method_: `void PutMemberFloat( LPSTR pName, FLOAT value )` | desc_: Assigns a Numeric. }}*/
       void            PutMemberFloat(LPSTR pName      , FLOAT    value );
       /*{{|method_: `void MemberPutStrLen( LPSTR pName, LPSTR pStr, ULONG nLen )` | desc_: Assigns **nLen** bytes as a Character. }}*/
       void            MemberPutStrLen(LPSTR pName,LPSTR pStr , ULONG nLen);
       /*{{|method_: `void MemberPutStr( LPSTR pName, LPSTR pStr )` | desc_: Assigns a zero-terminated string. }}*/
       void            MemberPutStr(LPSTR pName,LPSTR pStr);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void* Lock( ULONG* pdwSize = 0 )` | desc_: Self:_lock_(): the bytes of a GWST structure or of a pointer-style object, their size in **pdwSize**. }}*/
       void*           Lock(ULONG* pdwSize = 0);
       /*{{|method_: `void Unlock( void )` | desc_: Self:_unlock_(). }}*/
       void            Unlock(void);
};
/*{{end-cpp-class}}*/
#pragma pack(pop)
#endif // __cplusplus
//----------------------------------------------------------------------------------------------------------------------
#endif