//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
#define PXERROR( n , m , d )  px->GenError();px->SetErrorSubSystem("OT4XB"); \
                              px->SetErrorOperation("TXbClass::"  ##m  "()"); \
                              px->SetErrorDescription( d ); \
                              px->SetErrorGenCode(0x00102000 + n);
//----------------------------------------------------------------------------------------------------------------------

static void TXbClass_cm_AddClassHook(TXbClsParams * px);
//----------------------------------------------------------------------------------------------------------------------
static void TXbClass_DisableHooks(TXbClsParams * px);
//----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Init(TXbClsParams * px);                  // 1 // ::init( cClassName )
static void TXbClass_Destroy(TXbClsParams * px);               //   // ::Destroy()
static void TXbClass_Create(TXbClsParams * px);               //   // ::Destroy()
static void TXbClass_Parent(TXbClsParams * px);                // 1 // ::_Parent(oParent)
static void TXbClass_GwstParent(TXbClsParams * px);            // 1 // ::_GwstParent(oParent)
static void TXbClass_Exported(TXbClsParams * px);              // 0 // ::_Exported()
static void TXbClass_Hidden(TXbClsParams * px);                // 0 // ::_Hidden()
static void TXbClass_Protected(TXbClsParams * px);             // 0 // ::_Protected()
static void TXbClass_Var(TXbClsParams * px);                   // 2 // ::_Var(cName, cExtraFlags)
static void TXbClass_ClassVar(TXbClsParams * px);              // 2 // ::_ClassVar(cName, cExtraFlags)
static void TXbClass_SharedClassVar(TXbClsParams * px);        // 2 // ::_SharedClassVar(cName, cExtraFlags)
static void TXbClass_Method(TXbClsParams * px);                // 2 // ::_Method(cName , uBlock)
static void TXbClass_ClassMethod(TXbClsParams * px);           // 2 // ::_ClassMethod(cName , uBlock)
static void TXbClass_Property(TXbClsParams * px);              // 2 // ::_Property(cName , uBlock)
static void TXbClass_ClassProperty(TXbClsParams * px);         // 2 // ::_ClassProperty(cName , uBlock)
static void TXbClass_ROProperty(TXbClsParams * px);            // 2 // ::_ROProperty(cName , uBlock)
static void TXbClass_ROClassProperty(TXbClsParams * px);       // 2 // ::_ROClassProperty(cName , uBlock)
static void TXbClass_WOProperty(TXbClsParams * px);            // 2 // ::_WOProperty(cName , uBlock)
static void TXbClass_WOClassProperty(TXbClsParams * px);       // 2 // ::_WOClassProperty(cName , uBlock)
static void TXbClass_AddGwstStyleMembers(TXbClsParams * px);   // 0 // ::_AddGwstStyleMembers()
static void TXbClass_GwstReadOnly(TXbClsParams * px);          // 0 // ::_GwstReadOnly()
static void TXbClass_GwstReadWrite(TXbClsParams * px);         // 0 // ::_GwstReadWrite()
static void TXbClass_GwstBeginUnion(TXbClsParams * px);        // 0 // ::_GwstBeginUnion()
static void TXbClass_GwstEndUnion(TXbClsParams * px);          // 0 // ::_GwstEndUnion()
static void TXbClass_GwstSkipBytes(TXbClsParams * px);         // 1 // ::_GwstSkipBytes( nBytes)
static void TXbClass_GwstAdjustSize(TXbClsParams * px);        // 1 // ::_GwstAdjustSize(nSize)
static void TXbClass_GwstAlignNextMember(TXbClsParams * px);   // 1 // ::_GwstAlignNextMember(nPack)
static void TXbClass_GwstGetOffset(TXbClsParams * px);         // 0 // ::_GwstGetOffset() -> nNextOffSet
static void TXbClass_GwstSetOffset(TXbClsParams * px);         // 1 // ::_GwstSetOffset(nOffset)
static void TXbClass_GwstBack(TXbClsParams * px);              // 0 // ::_GwstBack(nOffset)
static void TXbClass_Child(TXbClsParams * px);                 // 2 // ::_Child(cName,oClass)
static void TXbClass_Member(TXbClsParams * px);                // 3 // ::_Member(cName,nMType,nSize)
static void TXbClass_Member_Bool(TXbClsParams * px);           // 1 // ::_Member_Bool(cName)
static void TXbClass_Member_ByteBool(TXbClsParams * px);           // 1 // ::_Member_Bool(cName)
static void TXbClass_Member_Byte(TXbClsParams * px);           // 1 // ::_Member_Byte(cName)
static void TXbClass_Member_Word(TXbClsParams * px);           // 1 // ::_Member_Word(cName)
static void TXbClass_Member_Int16(TXbClsParams * px);          // 1 // ::_Member_Int16(cName)
static void TXbClass_Member_Short(TXbClsParams * px);          // 1 // ::_Member_Short(cName)
static void TXbClass_Member_DWord(TXbClsParams * px);          // 1 // ::_Member_DWord(cName)
static void TXbClass_Member_ULong(TXbClsParams * px);          // 1 // ::_Member_ULong(cName)
static void TXbClass_Member_Long(TXbClsParams * px);           // 1 // ::_Member_Long(cName)
static void TXbClass_Member_UInt(TXbClsParams * px);           // 1 // ::_Member_UInt(cName)
static void TXbClass_Member_Int(TXbClsParams * px);            // 1 // ::_Member_Int(cName)
static void TXbClass_Member_Int32(TXbClsParams * px);          // 1 // ::_Member_Int32(cName)
static void TXbClass_Member_LParam(TXbClsParams * px);         // 1 // ::_Member_LParam(cName)
static void TXbClass_Member_WParam(TXbClsParams * px);         // 1 // ::_Member_WParam(cName)
static void TXbClass_Member_Pointer(TXbClsParams * px);        // 1 // ::_Member_Pointer(cName)
static void TXbClass_Member_Pointer32(TXbClsParams * px);      // 1 // ::_Member_Pointer32(cName)
static void TXbClass_Member_Handle(TXbClsParams * px);         // 1 // ::_Member_Handle(cName)
static void TXbClass_Member_hWnd(TXbClsParams * px);           // 1 // ::_Member_hWnd(cName)
static void TXbClass_Member_hDC(TXbClsParams * px);            // 1 // ::_Member_hDC(cName)
static void TXbClass_Member_Xbase(TXbClsParams * px);          // 1 // ::_Member_Xbase(cName)
static void TXbClass_Member_DWord64(TXbClsParams * px);        // 1 // ::_Member_DWord64(cName)
static void TXbClass_Member_Double(TXbClsParams * px);         // 1 // ::_Member_Double(cName)
static void TXbClass_Member_Float(TXbClsParams * px);          // 1 // ::_Member_Float(cName)
static void TXbClass_Member_lpStr(TXbClsParams * px);          // 1 // ::_Member_lpStr(cName)
static void TXbClass_Member_BinStr(TXbClsParams * px);         // 2 // ::_Member_BinStr(cName,nSize)
static void TXbClass_Member_szStr(TXbClsParams * px);          // 2 // ::_Member_szStr(cName,nSize)
static void TXbClass_Member_szWStr(TXbClsParams * px);          // 2 // ::_Member_szWStr(cName,nSize)
static void TXbClass_Member_DynSz(TXbClsParams * px);          // 1 // ::_Member_DynSz(cName)
static void TXbClass_Member_SINT8(TXbClsParams * px);
static void TXbClass_Member_SINT16(TXbClsParams * px);
static void TXbClass_Member_UINT32(TXbClsParams * px);
static void TXbClass_Member_NINT64(TXbClsParams * px);
static void TXbClass_Member_XDate(TXbClsParams * px);
static void TXbClass_Member_BitField(TXbClsParams * px); // 5 // ::_Member_BitField(cName,cHolder,sh,cb,nBits)

//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_DWordNet(TXbClsParams * px);          // 1 // ::_Member_DWord(cName)
static void TXbClass_Member_WordNet(TXbClsParams * px);           // 1 // ::_Member_DWord(cName)
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_XppGuiWnd(TXbClsParams * px);           // 1 // ::_Member_XppGuiWnd(cName)
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_method_(TXbClsParams * px ,    TXbClass * psc , ULONG nFlags); // 2 // ::_Method...(cName , uBlock)
static void TXbClass_property_(TXbClsParams * px ,    TXbClass * psc , ULONG nFlags); // 2 // ::_Method...(cName , uBlock)
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: TXbClass
            | _slug_: txbclass
            | class-function: TXBCLASS
            | category: runtime/classes
            | desc: Low-level runtime class builder used by OT4XB to create its exported Xbase++ classes and GWST
              structure classes. TXbClass():new(cClassName) returns a builder; the declaration methods (_Parent,
              _Exported, _Var, _Method, _Member_*, the _Gwst* layout family) return Self so calls can be chained
              while declaring, and ::Create() builds and returns the finished class object. A new builder starts
              with exported member scope. The AddHook class method registers an object or codeblock hook that is
              evaluated when a matching class is created.
            | note: Most application code should use the dynamic class and structure commands of ot4xb.ch, which
              expand to calls on this builder. TXbClass is documented because it is exported and because many
              classes shipped by OT4XB are built with it.
            | note: Calling a method of an object whose native builder was never created, or was already
              destroyed, raises an OT4XB runtime error; only ::DisableHooks() silently does nothing in that state.
            | see-also: BEGIN DYNAMIC CLASS, BEGIN STRUCTURE
            | _kw_: class builder, create class, ClassCreate, runtime class, GWST builder
   }}*/
XPPRET XPPENTRY TXBCLASS( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("TXbClass");
   if( conco == NULLCONTAINER )
   {                               
      TXbClass * pc = new TXbClass;
      pc->m_bDisableHooks = TRUE;
      pc->ClassName("TXbClass");
      /*{{|:**BEGIN CLASS  TXbClass** }}*/
      pc->EXPORTED();
      pc->GwstReadWrite();
      pc->AddGwstStyleMembers();
      // ---------------------------
      // TXbClass()::AddHook( cClsName, oHook|bHook) -> dwHookId
      /*{{|class-method_: - CLASS METHOD AddHook( cClassName, `oHook | bHook` )
               | return: nHookId
               | desc_: Registers a hook evaluated when a class named cClassName is created through a TXbClass
                 builder: ::Create() evaluates the hooks registered for the class name just before building the
                 class object, unless hooks are disabled on that builder. An Object hook receives the builder
                 through its ::OnClassCreate( oTXbClass ) method; a CodeBlock hook is evaluated with the builder
                 as its only parameter. Several hooks can be registered for the same class name, and 0 is returned
                 when the parameters are not valid.
      }}*/
      pc->ClassMethod( "AddHook", TXbClass_cm_AddClassHook,2);

      /*{{|method_: - `METHOD DisableHooks()`
               | return: NIL
               | desc_: Disables class creation hooks for this builder: ::Create() will not evaluate the hooks
                 registered for the class name. See the AddHook class method.
      }}*/
      pc->Method( "DisableHooks"          , TXbClass_DisableHooks ); // ::DisableHooks()
      // ---------------------------
      /*{{|method_: - `METHOD new( cClassName )`
               | return: oBuilder
               | desc_: Creates the native builder of a class named cClassName. A new builder starts with exported
                 member scope. Initializing an already initialized object raises a runtime error.
               | note: A Numeric parameter instead of cClassName is an internal form attaching the object to an
                 existing native builder; it is how the builder object received by class creation hooks is built.
      }}*/
      pc->Method( "init"                  , TXbClass_Init               , 1 ); // ::init( cClassName )
      /*{{|method_: - `METHOD Destroy()`
               | return: Self
               | desc_: Destroys the underlying native builder. The object cannot be used afterwards.
      }}*/
      pc->Method( "Destroy"               , TXbClass_Destroy                ); // ::Destroy()
      /*{{|method_: - `METHOD Create()`
               | return: oClass
               | desc_: Creates and returns the Xbase++ class object from the declarations collected by the builder,
                 evaluating first the class creation hooks (see the AddHook class method). The builder is not
                 destroyed: call ::Destroy() when it is no longer needed.
      }}*/
      pc->Method( "Create"                , TXbClass_Create                 ); // ::Create()
      // ---------------------------
      /*{{|method_: - METHOD _Parent( `cParentClass | oParentClass` )
               | return: Self
               | desc_: Adds a parent class, given by name or as a class object.
      }}*/
      pc->Method( "_Parent"               , TXbClass_Parent             , 1 ); // ::_Parent(oParent)
      /*{{|method_: - METHOD _GwstParent( [`cParentClass | oParentClass`] )
               | return: Self
               | desc_: Marks the class being built as a GWST structure class. The parent structure class can be
                 given by name or as a class object and its binary layout is inherited, with the structure offset
                 starting after it; without parameter the class descends directly from GWST.
      }}*/
      pc->Method( "_GwstParent"           , TXbClass_GwstParent         , 1 ); // ::_GwstParent(oParent)
      // ---------------------------
      /*{{|method_: - `METHOD _Exported()`
               | return: Self
               | desc_: Sets to EXPORTED the member scope applied to the following declarations.
      }}*/
      pc->Method( "_Exported"             , TXbClass_Exported           , 0 ); // ::_Exported()
      /*{{|method_: - `METHOD _Hidden()`
               | return: Self
               | desc_: Sets to HIDDEN the member scope applied to the following declarations.
      }}*/
      pc->Method( "_Hidden"               , TXbClass_Hidden             , 0 ); // ::_Hidden()
      /*{{|method_: - `METHOD _Protected()`
               | return: Self
               | desc_: Sets to PROTECTED the member scope applied to the following declarations.
      }}*/
      pc->Method( "_Protected"            , TXbClass_Protected          , 0 ); // ::_Protected()
      // ---------------------------
      /*{{|method_: - `METHOD _Var( cName [, nExtraFlags] )`
               | return: Self
               | desc_: Adds an instance variable with the current member scope. nExtraFlags contains optional
                 attribute flags ORed into the variable declaration.
      }}*/
      pc->Method( "_Var"                  , TXbClass_Var                , 2 ); // ::_Var(cName, cExtraFlags)
      /*{{|method_: - `METHOD _ClassVar( cName [, nExtraFlags] )`
               | return: Self
               | desc_: Adds a class variable, living on the class object, with the current member scope. nExtraFlags
                 contains optional attribute flags ORed into the variable declaration.
      }}*/
      pc->Method( "_ClassVar"             , TXbClass_ClassVar           , 2 ); // ::_ClassVar(cName, cExtraFlags)
      /*{{|method_: - `METHOD _SharedClassVar( cName [, nExtraFlags] )`
               | return: Self
               | desc_: Adds a shared class variable, SHARED meaning the same as in the declarative CLASS VAR syntax.
                 nExtraFlags contains optional attribute flags ORed into the variable declaration.
      }}*/
      pc->Method( "_SharedClassVar"       , TXbClass_SharedClassVar     , 2 ); // ::_SharedClassVar(cName, cExtraFlags)
      // ---------------------------
      /*{{|method_: - METHOD _Method( cName, `cCodeBlock | bCodeBlock` )
               | return: Self
               | desc_: Adds an instance method with the current member scope, implemented by a code block receiving
                 the object as its first parameter followed by the call parameters. The implementation can be given
                 as a CodeBlock or as its source in a Character value, macro-compiled when the method is added.
      }}*/
      pc->Method( "_Method"              , TXbClass_Method              , 2 ); // ::_Method(cName , uBlock)
      /*{{|method_: - METHOD _ClassMethod( cName, `cCodeBlock | bCodeBlock` )
               | return: Self
               | desc_: Adds a class method, living on the class object. The implementation forms are those of
                 ::_Method().
      }}*/
      pc->Method( "_ClassMethod"         , TXbClass_ClassMethod         , 2 ); // ::_ClassMethod(cName , uBlock)
      /*{{|method_: - METHOD _Property( cName, `cCodeBlock | bCodeBlock` )
               | return: Self
               | desc_: Adds a read/write property with the current member scope, implemented by a code block
                 evaluated with the object to read the property and with the object plus the assigned value to
                 write it, as in `{|Self,v| iif( PCount() > 1, <write>, <read> ) }`. The implementation can be given
                 as a CodeBlock or as its source in a Character value, macro-compiled when the property is added.
      }}*/
      pc->Method( "_Property"            , TXbClass_Property            , 2 ); // ::_Property(cName , uBlock)
      /*{{|method_: - METHOD _ClassProperty( cName, `cCodeBlock | bCodeBlock` )
               | return: Self
               | desc_: Adds a read/write property living on the class object. The implementation forms are those of
                 ::_Property().
      }}*/
      pc->Method( "_ClassProperty"       , TXbClass_ClassProperty       , 2 ); // ::_ClassProperty(cName , uBlock)
      /*{{|method_: - METHOD _ROProperty( cName, `cCodeBlock | bCodeBlock` )
               | return: Self
               | desc_: Adds a read-only property: only the read side of ::_Property() is registered.
      }}*/
      pc->Method( "_ROProperty"          , TXbClass_ROProperty          , 2 ); // ::_ROProperty(cName , uBlock)
      /*{{|method_: - METHOD _ROClassProperty( cName, `cCodeBlock | bCodeBlock` )
               | return: Self
               | desc_: Adds a read-only property living on the class object.
      }}*/
      pc->Method( "_ROClassProperty"     , TXbClass_ROClassProperty     , 2 ); // ::_ROClassProperty(cName , uBlock)
      /*{{|method_: - METHOD _WOProperty( cName, `cCodeBlock | bCodeBlock` )
               | return: Self
               | desc_: Adds a write-only property: only the write side of ::_Property() is registered.
      }}*/
      pc->Method( "_WOProperty"          , TXbClass_WOProperty          , 2 ); // ::_WOProperty(cName , uBlock)
      /*{{|method_: - METHOD _WOClassProperty( cName, `cCodeBlock | bCodeBlock` )
               | return: Self
               | desc_: Adds a write-only property living on the class object.
      }}*/
      pc->Method( "_WOClassProperty"     , TXbClass_WOClassProperty     , 2 ); // ::_WOClassProperty(cName , uBlock)
      // ---------------------------
      /*{{|method_: - `METHOD _AddGwstStyleMembers()`
               | return: Self
               | desc_: Adds the GWST-style pointer support members: the instance variable _m__pt_ and the methods
                 :_lock_() and :_unlock_().
      }}*/
      pc->Method( "_AddGwstStyleMembers" , TXbClass_AddGwstStyleMembers , 0 ); // ::_AddGwstStyleMembers()
      // ---------------------------
      /*{{|method_: - `METHOD _GwstReadOnly()`
               | return: Self
               | desc_: Makes the following structure members generate read-only properties.
      }}*/
      pc->Method( "_GwstReadOnly"       , TXbClass_GwstReadOnly         , 0);  // ::_GwstReadOnly()
      /*{{|method_: - `METHOD _GwstReadWrite()`
               | return: Self
               | desc_: Makes the following structure members generate read/write properties.
      }}*/
      pc->Method( "_GwstReadWrite"      , TXbClass_GwstReadWrite        , 0);  // ::_GwstReadWrite()
      /*{{|method_: - `METHOD _GwstBeginUnion()`
               | return: Self
               | desc_: Starts a union: the following members are laid out at the same offset and the union takes
                 the size of its biggest member. Union blocks cannot be nested.
      }}*/
      pc->Method( "_GwstBeginUnion"     , TXbClass_GwstBeginUnion       , 0);  // ::_GwstBeginUnion()
      /*{{|method_: - `METHOD _GwstEndUnion()`
               | return: Self
               | desc_: Ends the union started by ::_GwstBeginUnion() and advances the structure offset by the
                 union size.
      }}*/
      pc->Method( "_GwstEndUnion"       , TXbClass_GwstEndUnion         , 0);  // ::_GwstEndUnion()
      /*{{|method_: - `METHOD _GwstSkipBytes( nBytes )`
               | return: Self
               | desc_: Advances the offset of the next member by nBytes bytes; inside a union it grows the union
                 size to at least nBytes bytes.
      }}*/
      pc->Method( "_GwstSkipBytes"      , TXbClass_GwstSkipBytes        , 1);  // ::_GwstSkipBytes( nBytes)
      /*{{|method_: - `METHOD _GwstAdjustSize( nSize )`
               | return: Self
               | desc_: Ensures the structure size reached so far is at least nSize bytes.
      }}*/
      pc->Method( "_GwstAdjustSize"     , TXbClass_GwstAdjustSize       , 1);  // ::_GwstAdjustSize(nSize)
      /*{{|method_: - `METHOD _GwstGetOffset()`
               | return: nOffset
               | desc_: Returns the offset where the next member will be placed.
      }}*/
      pc->Method( "_GwstGetOffset"      , TXbClass_GwstGetOffset        , 0);  // ::_GwstGetOffset() -> nNextOffSet
      /*{{|method_: - `METHOD _GwstSetOffset( nOffset )`
               | return: Self
               | desc_: Sets the offset where the next member will be placed.
      }}*/
      pc->Method( "_GwstSetOffset"      , TXbClass_GwstSetOffset        , 1);  // ::_GwstSetOffset(nOffset)
      /*{{|method_: - `METHOD _GwstBack()`
               | return: Self
               | desc_: Moves the offset back to the start of the last defined member, so the next member overlays
                 it.
      }}*/
      pc->Method( "_GwstBack"           , TXbClass_GwstBack             , 0);  // ::_GwstBack(nOffset)
      /*{{|method_: - `METHOD _GwstAlignNextMember( nPack )`
               | return: Self
               | desc_: Rounds the offset of the next member up to the next multiple of nPack bytes.
      }}*/
      pc->Method( "_GwstAlignNextMember", TXbClass_GwstAlignNextMember  , 1);  // ::_GwstAlignNextMember(nPack)
      // ---------------------------
      /*{{|method_: - METHOD _Child( cName, `cClass | oClass` )
               | return: Self
               | desc_: Embeds a child structure as member cName, its class given by name or as a class object. The
                 child takes its class size in the layout and a read-only property returning the child instance is
                 generated.
      }}*/
      pc->Method( "_Child"             , TXbClass_Child                 , 2);  // ::_Child(cName,oClass)
      /*{{|method_: - `METHOD _Member( cName, nMemberType, nSize )`
               | return: Self
               | desc_: Adds a raw structure member: nMemberType is the internal GWST member type and nSize its size
                 in bytes. The member is placed at the current offset, the offset advances nSize bytes (inside a
                 union the union size grows instead) and the member property is generated. The ::_Member_...()
                 helpers call it with the right type and size for each supported member type.
      }}*/
      pc->Method( "_Member"            , TXbClass_Member                , 3);  // ::_Member(cName,nMType,nSize)
      /*{{|method_: - `METHOD _Member_DWordNet( cName )`
               | return: Self
               | desc_: Adds a 4-byte integer member kept in network byte order, read and written as a host byte
                 order Numeric value.
               | see-also: MEMBER DWORDNET
      }}*/
      pc->Method( "_Member_DWordNet"   , TXbClass_Member_DWordNet       , 1);  // ::_Member_DWordNet(cName)
      /*{{|method_: - `METHOD _Member_WordNet( cName )`
               | return: Self
               | desc_: Adds a 2-byte integer member kept in network byte order, read and written as a host byte
                 order Numeric value.
               | see-also: MEMBER WORDNET
      }}*/
      pc->Method( "_Member_WordNet"    , TXbClass_Member_WordNet        , 1);  // ::_Member_WordNet(cName)
      /*{{|method_: - `METHOD _Member_Bool( cName )`
               | return: Self
               | desc_: Adds a 4-byte BOOL member, read and written as a Logical value.
               | see-also: MEMBER BOOL
      }}*/
      pc->Method( "_Member_Bool"       , TXbClass_Member_Bool           , 1);  // ::_Member_Bool(cName)
      /*{{|method_: - `METHOD _Member_ByteBool( cName )`
               | return: Self
               | desc_: Adds a 1-byte boolean member, read and written as a Logical value.
               | see-also: MEMBER BYTEBOOL
      }}*/
      pc->Method( "_Member_ByteBool"   , TXbClass_Member_ByteBool       , 1);  // ::_Member_Bool(cName)
      /*{{|method_: - `METHOD _Member_Byte( cName )`
               | return: Self
               | desc_: Adds a 1-byte unsigned integer member, read as a positive Numeric value, 0 to 255.
               | see-also: MEMBER BYTE
      }}*/
      pc->Method( "_Member_Byte"       , TXbClass_Member_Byte           , 1);  // ::_Member_Byte(cName)
      /*{{|method_: - `METHOD _Member_Word( cName )`
               | return: Self
               | desc_: Adds a 2-byte unsigned integer member, read as a positive Numeric value, 0 to 65535.
               | see-also: MEMBER WORD
      }}*/
      pc->Method( "_Member_Word"       , TXbClass_Member_Word           , 1);  // ::_Member_Word(cName)
      /*{{|method_: - `METHOD _Member_Int16( cName )`
               | return: Self
               | desc_: Adds a 2-byte unsigned integer member, exactly like ::_Member_Word().
               | see-also: MEMBER WORD
      }}*/
      pc->Method( "_Member_Int16"      , TXbClass_Member_Int16          , 1);  // ::_Member_Int16(cName)
      /*{{|method_: - `METHOD _Member_Short( cName )`
               | return: Self
               | desc_: Adds a 2-byte unsigned integer member, exactly like ::_Member_Word().
               | see-also: MEMBER WORD
      }}*/
      pc->Method( "_Member_Short"      , TXbClass_Member_Short          , 1);  // ::_Member_Short(cName)
      /*{{|method_: - `METHOD _Member_DWord( cName )`
               | return: Self
               | desc_: Adds a 4-byte integer member, read and written as an integer Numeric value; to keep the
                 internal storage as a 32-bit integer, values >= 0x80000000 are represented as negative.
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_DWord"      , TXbClass_Member_DWord          , 1);  // ::_Member_DWord(cName)
      /*{{|method_: - `METHOD _Member_ULong( cName )`
               | return: Self
               | desc_: Adds a 4-byte integer member, exactly like ::_Member_DWord().
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_ULong"      , TXbClass_Member_ULong          , 1);  // ::_Member_ULong(cName)
      /*{{|method_: - `METHOD _Member_Long( cName )`
               | return: Self
               | desc_: Adds a 4-byte integer member, exactly like ::_Member_DWord().
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_Long"       , TXbClass_Member_Long           , 1);  // ::_Member_Long(cName)
      /*{{|method_: - `METHOD _Member_UInt( cName )`
               | return: Self
               | desc_: Adds a 4-byte integer member, exactly like ::_Member_DWord().
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_UInt"       , TXbClass_Member_UInt           , 1);  // ::_Member_UInt(cName)
      /*{{|method_: - `METHOD _Member_Int( cName )`
               | return: Self
               | desc_: Adds a 4-byte integer member, exactly like ::_Member_DWord().
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_Int"        , TXbClass_Member_Int            , 1);  // ::_Member_Int(cName)
      /*{{|method_: - `METHOD _Member_Int32( cName )`
               | return: Self
               | desc_: Adds a 4-byte integer member, exactly like ::_Member_DWord().
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_Int32"      , TXbClass_Member_Int32          , 1);  // ::_Member_Int32(cName)
      /*{{|method_: - `METHOD _Member_LParam( cName )`
               | return: Self
               | desc_: Adds a 4-byte integer member, exactly like ::_Member_DWord().
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_LParam"     , TXbClass_Member_LParam         , 1);  // ::_Member_LParam(cName)
      /*{{|method_: - `METHOD _Member_WParam( cName )`
               | return: Self
               | desc_: Adds a 4-byte integer member, exactly like ::_Member_DWord().
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_WParam"     , TXbClass_Member_WParam         , 1);  // ::_Member_WParam(cName)
      /*{{|method_: - `METHOD _Member_Pointer( cName )`
               | return: Self
               | desc_: Adds a 4-byte pointer member, handled as a plain 32-bit value like ::_Member_DWord().
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_Pointer"    , TXbClass_Member_Pointer        , 1);  // ::_Member_Pointer(cName)
      /*{{|method_: - `METHOD _Member_Pointer32( cName )`
               | return: Self
               | desc_: Adds a 4-byte pointer member, exactly like ::_Member_Pointer().
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_Pointer32"  , TXbClass_Member_Pointer32      , 1);  // ::_Member_Pointer32(cName)
      /*{{|method_: - `METHOD _Member_Handle( cName )`
               | return: Self
               | desc_: Adds a 4-byte Win32 handle member, handled as a plain 32-bit value like ::_Member_DWord().
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_Handle"     , TXbClass_Member_Handle         , 1);  // ::_Member_Handle(cName)
      /*{{|method_: - `METHOD _Member_hWnd( cName )`
               | return: Self
               | desc_: Adds a 4-byte window handle member, exactly like ::_Member_Handle().
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_hWnd"       , TXbClass_Member_hWnd           , 1);  // ::_Member_hWnd(cName)
      /*{{|method_: - `METHOD _Member_hDC( cName )`
               | return: Self
               | desc_: Adds a 4-byte device context handle member, exactly like ::_Member_Handle().
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_hDC"        , TXbClass_Member_hDC            , 1);  // ::_Member_hDC(cName)
      /*{{|method_: - `METHOD _Member_Xbase( cName )`
               | return: Self
               | desc_: Adds a 4-byte member storing any Xbase++ value through an Xbase++ container kept in the
                 structure. The container is not released automatically: assign NIL to release it.
               | see-also: MEMBER PXBASEVAR
      }}*/
      pc->Method( "_Member_Xbase"      , TXbClass_Member_Xbase          , 1);  // ::_Member_Xbase(cName)
      /*{{|method_: - `METHOD _Member_DWord64( cName )`
               | return: Self
               | desc_: Adds an 8-byte unsigned integer member (QWORD), read as an 8-byte Character string; a
                 Numeric value can also be assigned.
               | see-also: MEMBER DWORD64
      }}*/
      pc->Method( "_Member_DWord64"    , TXbClass_Member_DWord64        , 1);  // ::_Member_DWord64(cName)
      /*{{|method_: - `METHOD _Member_Double( cName )`
               | return: Self
               | desc_: Adds an 8-byte floating point member, read and written as a Numeric value.
               | see-also: MEMBER DOUBLE
      }}*/
      pc->Method( "_Member_Double"     , TXbClass_Member_Double         , 1);  // ::_Member_Double(cName)
      /*{{|method_: - `METHOD _Member_Float( cName )`
               | return: Self
               | desc_: Adds a 4-byte floating point member, read and written as a Numeric value.
               | see-also: MEMBER FLOAT
      }}*/
      pc->Method( "_Member_Float"      , TXbClass_Member_Float          , 1);  // ::_Member_Float(cName)
      /*{{|method_: - `METHOD _Member_lpStr( cName )`
               | return: Self
               | desc_: Adds a 4-byte pointer member meant to hold the address of a C string; the member holds the
                 pointer itself as a Numeric value and the pointed text is not touched.
               | see-also: MEMBER LPSTR
      }}*/
      pc->Method( "_Member_lpStr"      , TXbClass_Member_lpStr          , 1);  // ::_Member_lpStr(cName)
      /*{{|method_: - `METHOD _Member_BinStr( cName, nSize )`
               | return: Self
               | desc_: Adds a binary string member of nSize bytes: a longer value is truncated, a shorter one is
                 padded with chr(0), and reading returns exactly nSize characters.
               | see-also: MEMBER BINSTR
      }}*/
      pc->Method( "_Member_BinStr"     , TXbClass_Member_BinStr         , 2);  // ::_Member_BinStr(cName,nSize)
      /*{{|method_: - `METHOD _Member_szStr( cName, nSize )`
               | return: Self
               | desc_: Adds a zero terminated string member of nSize bytes including the trailing chr(0); reading
                 returns the text up to the first chr(0).
               | see-also: MEMBER SZSTR
      }}*/
      pc->Method( "_Member_szStr"      , TXbClass_Member_szStr          , 2);  // ::_Member_szStr(cName,nSize)
      /*{{|method_: - `METHOD _Member_szWStr( cName, nSize )`
               | return: Self
               | desc_: Adds a zero terminated wide string member holding up to nSize wide characters; nSize * 2
                 bytes are reserved in the structure.
               | see-also: MEMBER SZWSTR
      }}*/
      pc->Method( "_Member_szWStr"     , TXbClass_Member_szWStr         , 2);  // ::_Member_szWStr(cName,nSize)
      /*{{|method_: - `METHOD _Member_DynSz( cName )`
               | return: Self
               | desc_: Adds a 4-byte pointer member managing its own text buffer: assigning a string allocates a
                 buffer holding it plus a trailing chr(0), reading returns the pointed text, and assigning NIL
                 releases the buffer.
               | see-also: MEMBER DYNSZ
      }}*/
      pc->Method( "_Member_DynSz"      , TXbClass_Member_DynSz          , 1);  // ::_Member_DynSz(cName)
      /*{{|method_: - `METHOD _Member_XppGuiWnd( cName )`
               | return: Self
               | desc_: Adds a 4-byte member holding the C++ window pointer of an Xbase++ GUI object: a Numeric
                 value is stored as is, an Object is asked for the pointer through its GetTwWinBaseCppPointer()
                 method, and reading returns the pointer as a Numeric value.
      }}*/
      pc->Method( "_Member_XppGuiWnd"  , TXbClass_Member_XppGuiWnd      , 1);  // ::_Member_XppGuiWnd(cName)
      /*{{|method_: - `METHOD _Member_SINT8( cName )`
               | return: Self
               | desc_: Adds a 1-byte signed integer member; reading sign extends and returns -128 to 127.
               | see-also: MEMBER BYTE
      }}*/
      pc->Method( "_Member_SINT8"      , TXbClass_Member_SINT8          , 1);
      /*{{|method_: - `METHOD _Member_SINT16( cName )`
               | return: Self
               | desc_: Adds a 2-byte signed integer member; reading sign extends and returns -32768 to 32767.
               | see-also: MEMBER WORD
      }}*/
      pc->Method( "_Member_SINT16"     , TXbClass_Member_SINT16         , 1);
      /*{{|method_: - `METHOD _Member_UINT32( cName )`
               | return: Self
               | desc_: Adds a 4-byte unsigned integer member; reading never returns a negative value, above
                 0x7FFFFFFF the member comes back as a floating point Numeric value.
               | see-also: MEMBER DWORD
      }}*/
      pc->Method( "_Member_UINT32"     , TXbClass_Member_UINT32         , 1);
      /*{{|method_: - `METHOD _Member_NINT64( cName )`
               | return: Self
               | desc_: Adds an 8-byte signed integer member, read as an 8-byte Character string. A Character,
                 Numeric, { nLow, nHigh } Array or Object value can be assigned.
               | see-also: MEMBER N_INT64
      }}*/
      pc->Method( "_Member_NINT64"     , TXbClass_Member_NINT64         , 1);
      /*{{|method_: - `METHOD _Member_XDate( cName )`
               | return: Self
               | desc_: Adds an 8-byte Date member stored as YYYYMMDD text, read and written as a Date value.
               | see-also: MEMBER XDATE
      }}*/
      pc->Method( "_Member_XDate"      , TXbClass_Member_XDate          , 1);
      /*{{|method_: - `METHOD _Member_BitField( cName, cHolder, nShift, nBits, nHolderBits )`
               | return: Self
               | desc_: Adds a read/write property cName exposing a bit field of another member: nBits bits starting
                 at bit nShift of the numeric member cHolder, whose bit width is nHolderBits (8, 16 or 32; any
                 other value selects 32). No structure bytes are reserved by this declaration.
      }}*/
      /*{{|:**END CLASS** }}*/
      pc->Method( "_Member_BitField"   , TXbClass_Member_BitField       , 5);      
      // pc->Method( "_Member_StructArray" , TXbClass_Member_StructArray, 5);            
      // ---------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Init(TXbClsParams * px)                  // 1 // ::init( cClassName | pTXbClass )
{
   if( px->CheckParamType(1,XPP_NUMERIC) )
   {
      px->SetSelfC( (void *) px->GetParamLong(1) );
   }
   else
   {
      TXbClass * psc = (TXbClass *) 0;
      psc = (TXbClass * ) px->GetSelfC();
      if( psc == NULL )
      {
         if( px->CheckParamType(1,XPP_CHARACTER) )
         {
            psc = (TXbClass * ) new TXbClass; px->SetSelfC( (void *) psc);
            psc->ClassName(px->ParamLockStr(1));
            psc->EXPORTED();
            px->ParamUnlockStr(1);
         }
      }
      else { PXERROR( 0 , "init" , "Object already initialized." ); }
   }
   px->PutReturnSelf();

}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_DisableHooks(TXbClsParams * px)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc ) psc->m_bDisableHooks = TRUE;
}
//----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Destroy(TXbClsParams * px)               //   // ::Destroy()
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Destroy" , "Object not properly initialized." ); }
   else
   {
      delete psc;
      px->SetSelfC( NULL);

      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Create(TXbClsParams * px)               //   // ::Destroy()
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Create" , "Object not properly initialized." ); }
   else psc->Create(px->GetReturn());
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Parent(TXbClsParams * px)                // 1 // ::_Parent(oParent)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Parent" , "Object not properly initialized." ); }
   else
   {
      if( px->CheckParamType( 1 , XPP_OBJECT ) ) psc->_xparent_( _conNew(px->GetParam(1)) );
      else if( px->CheckParamType( 1 , XPP_CHARACTER ) )
      {
         psc->Parent( px->ParamLockStr(1));
         px->ParamUnlockStr(1);
      }
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_GwstParent(TXbClsParams * px)            // 1 // ::_GwstParent(oParent)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_GwstParent" , "Object not properly initialized." ); }
   else
   {
      if( px->CheckParamType( 1 , XPP_OBJECT ) ) psc->_xGwstParent_( _conNew(px->GetParam(1)) );
      else if( px->CheckParamType( 1 , XPP_CHARACTER ) )
      {
         psc->GwstParent( px->ParamLockStr(1));
         px->ParamUnlockStr(1);
      }
      else psc->GwstParent( NULL );
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Exported(TXbClsParams * px)              // 0 // ::_Exported()
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Exported ", "Object not properly initialized." ); }
   else
   {
      psc->EXPORTED();
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Hidden(TXbClsParams * px)                // 0 // ::_Hidden()
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Hidden ", "Object not properly initialized." ); }
   else
   {
      psc->HIDDEN();
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Protected(TXbClsParams * px)             // 0 // ::_Protected()
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Protected ", "Object not properly initialized." ); }
   else
   {
      psc->PROTECTED();
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Var(TXbClsParams * px)                   // 2 // ::_Var(cName, cExtraFlags)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Var ", "Object not properly initialized." ); }
   else
   {
      if( px->CheckParamType( 1 , XPP_CHARACTER ) )
      {
         psc->Var( px->ParamLockStr(1) , px->GetParamDWord(2) );
         px->ParamUnlockStr(1);
      }
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_ClassVar(TXbClsParams * px)              // 2 // ::_ClassVar(cName, cExtraFlags)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_ClassVar ", "Object not properly initialized." ); }
   else
   {
      if( px->CheckParamType( 1 , XPP_CHARACTER ) )
      {
         psc->ClassVar( px->ParamLockStr(1) , px->GetParamDWord(2) );
         px->ParamUnlockStr(1);
      }
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_SharedClassVar(TXbClsParams * px)        // 2 // ::_SharedClassVar(cName, cExtraFlags)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_SharedClassVar ", "Object not properly initialized." ); }
   else
   {
      if( px->CheckParamType( 1 , XPP_CHARACTER ) )
      {
         psc->SharedClassVar( px->ParamLockStr(1) , px->GetParamDWord(2) );
         px->ParamUnlockStr(1);
      }
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_method_(TXbClsParams * px ,    TXbClass * psc , ULONG nFlags) // 2 // ::_Method...(cName , uBlock)
{
   nFlags |= psc->m_nDefaultScope;
   if( px->CheckParamType( 2 , XPP_CHARACTER ) )
   {
      psc->_method_(px->ParamLockStr(1) ,nFlags, px->ParamLockStr(2) );
      px->ParamUnlockStr(1);
      px->ParamUnlockStr(2);
   }
   else if( px->CheckParamType( 2 , XPP_BLOCK ) )
   {
      psc->_xmethod_(px->ParamLockStr(1),nFlags, _conNew(px->GetParam(2)) );
      px->ParamUnlockStr(1);
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Method(TXbClsParams * px)                // 2 // ::_Method(cName , uBlock)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Method ", "Object not properly initialized." ); }
   else
   {
      TXbClass_method_(px ,psc, xppMETHOD_INSTANCE );
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_ClassMethod(TXbClsParams * px)           // 2 // ::_ClassMethod(cName , uBlock)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_ClassMethod ", "Object not properly initialized." ); }
   else
   {
      TXbClass_method_(px ,psc, xppMETHOD_CLASS );
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_property_(TXbClsParams * px ,    TXbClass * psc , ULONG nFlags) // 2 // ::_Method...(cName , uBlock)
{
   nFlags |= psc->m_nDefaultScope;
   if( px->CheckParamType( 2 , XPP_CHARACTER ) )
   {
      psc->_property_(px->ParamLockStr(1) ,nFlags, px->ParamLockStr(2) );
      px->ParamUnlockStr(1);
      px->ParamUnlockStr(2);
   }
   else if( px->CheckParamType( 2 , XPP_BLOCK ) )
   {
      psc->_xproperty_(px->ParamLockStr(1),nFlags, _conNew(px->GetParam(2)) );
      px->ParamUnlockStr(1);
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Property(TXbClsParams * px)              // 2 // ::_Property(cName , uBlock)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Property ", "Object not properly initialized." ); }
   else
   {
      TXbClass_property_(px ,psc, ( xppMETHOD_INSTANCE | xppMETHOD_ACCESS | xppMETHOD_ASSIGN ) );
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_ClassProperty(TXbClsParams * px)         // 2 // ::_ClassProperty(cName , uBlock)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_ClassProperty ", "Object not properly initialized." ); }
   else
   {
      TXbClass_property_(px ,psc, ( xppMETHOD_CLASS | xppMETHOD_ACCESS | xppMETHOD_ASSIGN ) );
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_ROProperty(TXbClsParams * px)            // 2 // ::_ROProperty(cName , uBlock)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_ROProperty ", "Object not properly initialized." ); }
   else
   {
      TXbClass_property_(px ,psc, ( xppMETHOD_INSTANCE | xppMETHOD_ACCESS ) );
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_ROClassProperty(TXbClsParams * px)       // 2 // ::_ROClassProperty(cName , uBlock)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_ROClassProperty ", "Object not properly initialized." ); }
   else
   {
      TXbClass_property_(px ,psc, ( xppMETHOD_CLASS | xppMETHOD_ACCESS ) );
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_WOProperty(TXbClsParams * px)            // 2 // ::_WOProperty(cName , uBlock)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_WOProperty ", "Object not properly initialized." ); }
   else
   {
      TXbClass_property_(px ,psc, ( xppMETHOD_INSTANCE | xppMETHOD_ASSIGN ) );
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_WOClassProperty(TXbClsParams * px)       // 2 // ::_WOClassProperty(cName , uBlock)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_WOClassProperty ", "Object not properly initialized." ); }
   else
   {
      TXbClass_property_(px ,psc, ( xppMETHOD_CLASS | xppMETHOD_ASSIGN ) );
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_AddGwstStyleMembers(TXbClsParams * px)   // 0 // ::_AddGwstStyleMembers()
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_AddGwstStyleMembers ", "Object not properly initialized." ); }
   else
   {
      psc->AddGwstStyleMembers();
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_GwstReadOnly(TXbClsParams * px)          // 0 // ::_GwstReadOnly()
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_GwstReadOnly ", "Object not properly initialized." ); }
   else
   {
      psc->GwstReadOnly();
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_GwstReadWrite(TXbClsParams * px)         // 0 // ::_GwstReadWrite()
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_GwstReadWrite ", "Object not properly initialized." ); }
   else
   {
      psc->GwstReadWrite();
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_GwstBeginUnion(TXbClsParams * px)        // 0 // ::_GwstBeginUnion()
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_GwstBeginUnion ", "Object not properly initialized." ); }
   else
   {
      psc->GwstBeginUnion();
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_GwstEndUnion(TXbClsParams * px)          // 0 // ::_GwstEndUnion()
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_GwstEndUnion ", "Object not properly initialized." ); }
   else
   {
      psc->GwstEndUnion();
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_GwstSkipBytes(TXbClsParams * px)         // 1 // ::_GwstSkipBytes( nBytes)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_GwstSkipBytes ", "Object not properly initialized." ); }
   else
   {
      psc->GwstSkipBytes(px->GetParamDWord(1));
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_GwstAdjustSize(TXbClsParams * px)        // 1 // ::_GwstAdjustSize(nSize)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_GwstAdjustSize ", "Object not properly initialized." ); }
   else
   {
      psc->GwstAdjustSize(px->GetParamDWord(1));
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_GwstGetOffset(TXbClsParams * px)         // 0 // ::_GwstGetOffset() -> nNextOffSet
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_GwstGetOffset ", "Object not properly initialized." ); }
   else
   {
      px->PutReturnLong( psc->GwstGetOffset() );
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_GwstSetOffset(TXbClsParams * px)         // 1 // ::_GwstSetOffset(nOffset)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_GwstSetOffset ", "Object not properly initialized." ); }
   else
   {
      psc->GwstSetOffset(px->GetParamDWord(1));
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_GwstBack(TXbClsParams * px)              // 0 // ::_GwstBack(nOffset)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_GwstSetOffset ", "Object not properly initialized." ); }
   else
   {
      psc->GwstBack();
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_GwstAlignNextMember(TXbClsParams * px)              // 1 // ::_GwstAlignNextMember(nPack)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_GwstSetOffset ", "Object not properly initialized." ); }
   else
   {
      psc->GwstAlignNextMember( px->GetParamDWord(1));
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Child(TXbClsParams * px)                 // 2 // ::_Child(cName,oClass)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Child ", "Object not properly initialized." ); }
   else
   {
      if( px->CheckParamType( 2 , XPP_OBJECT ) )
      {
         psc->_xchild_(px->ParamLockStr(1), _conNew(px->GetParam(2)) );
         px->ParamUnlockStr(1);
      }
      else if( px->CheckParamType( 2 , XPP_CHARACTER ) )
      {
         psc->Child(px->ParamLockStr(1), px->ParamLockStr(2) );
         px->ParamUnlockStr(1);
         px->ParamUnlockStr(2);
      }
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member(TXbClsParams * px)                // 3 // ::_Member(cName,nMType,nSize)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member ", "Object not properly initialized." ); }
   else
   {
      psc->Member(px->ParamLockStr(1),px->GetParamDWord(2), px->GetParamDWord(3));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_DWordNet(TXbClsParams * px)           // 1 // ::_Member_Long(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Long", "Object not properly initialized." ); }
   else
   {
      psc->Member_DWordNet(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_WordNet(TXbClsParams * px)           // 1 // ::_Member_Long(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Long", "Object not properly initialized." ); }
   else
   {
      psc->Member_WordNet(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_ByteBool(TXbClsParams * px)           // 1 // ::_Member_ByteBool(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_ByteBool", "Object not properly initialized." ); }
   else
   {
      psc->Member_ByteBool(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Bool(TXbClsParams * px)           // 1 // ::_Member_Bool(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Bool", "Object not properly initialized." ); }
   else
   {
      psc->Member_Bool(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_BitField(TXbClsParams * px) // 5 // ::_Member_BitField(cName,cHolder,sh,cb,nBits)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_BitField", "Object not properly initialized." ); }
   else
   {
      psc->Member_BitField(  px->ParamLockStr(1) ,
                             px->ParamLockStr(2) ,
                             px->GetParamDWord(3),
                             px->GetParamDWord(4),
                             px->GetParamDWord(5)
                           );
      px->ParamUnlockStr(1);
      px->ParamUnlockStr(2);      
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Byte(TXbClsParams * px)           // 1 // ::_Member_Byte(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Byte", "Object not properly initialized." ); }
   else
   {
      psc->Member_Byte(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Word(TXbClsParams * px)           // 1 // ::_Member_Word(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Word", "Object not properly initialized." ); }
   else
   {
      psc->Member_Word(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_SINT8(TXbClsParams * px)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_SINT8", "Object not properly initialized." ); }
   else
   {
      psc->Member_SINT8(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_SINT16(TXbClsParams * px)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_SINT16", "Object not properly initialized." ); }
   else
   {
      psc->Member_SINT16(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_UINT32(TXbClsParams * px)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_UINT32", "Object not properly initialized." ); }
   else
   {
      psc->Member_UINT32(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_NINT64(TXbClsParams * px)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_NINT64", "Object not properly initialized." ); }
   else
   {
      psc->Member_NINT64(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Int16(TXbClsParams * px)          // 1 // ::_Member_Int16(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Int16", "Object not properly initialized." ); }
   else
   {
      psc->Member_Int16(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Short(TXbClsParams * px)          // 1 // ::_Member_Short(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Short", "Object not properly initialized." ); }
   else
   {
      psc->Member_Short(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_DWord(TXbClsParams * px)          // 1 // ::_Member_DWord(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_DWord", "Object not properly initialized." ); }
   else
   {
      psc->Member_DWord(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_ULong(TXbClsParams * px)          // 1 // ::_Member_ULong(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_ULong", "Object not properly initialized." ); }
   else
   {
      psc->Member_ULong(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Long(TXbClsParams * px)           // 1 // ::_Member_Long(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Long", "Object not properly initialized." ); }
   else
   {
      psc->Member_Long(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_UInt(TXbClsParams * px)           // 1 // ::_Member_UInt(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_UInt", "Object not properly initialized." ); }
   else
   {
      psc->Member_UInt(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Int(TXbClsParams * px)            // 1 // ::_Member_Int(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Int", "Object not properly initialized." ); }
   else
   {
      psc->Member_Int(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Int32(TXbClsParams * px)          // 1 // ::_Member_Int32(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Int32", "Object not properly initialized." ); }
   else
   {
      psc->Member_Int32(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_LParam(TXbClsParams * px)         // 1 // ::_Member_LParam(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_LParam", "Object not properly initialized." ); }
   else
   {
      psc->Member_LParam(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_WParam(TXbClsParams * px)         // 1 // ::_Member_WParam(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_WParam", "Object not properly initialized." ); }
   else
   {
      psc->Member_WParam(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Pointer(TXbClsParams * px)        // 1 // ::_Member_Pointer(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Pointer", "Object not properly initialized." ); }
   else
   {
      psc->Member_Pointer(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Pointer32(TXbClsParams * px)      // 1 // ::_Member_Pointer32(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Pointer32", "Object not properly initialized." ); }
   else
   {
      psc->Member_Pointer32(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Handle(TXbClsParams * px)         // 1 // ::_Member_Handle(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Handle", "Object not properly initialized." ); }
   else
   {
      psc->Member_Handle(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_hWnd(TXbClsParams * px)           // 1 // ::_Member_hWnd(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_hWnd", "Object not properly initialized." ); }
   else
   {
      psc->Member_hWnd(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_hDC(TXbClsParams * px)            // 1 // ::_Member_hDC(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_hDC", "Object not properly initialized." ); }
   else
   {
      psc->Member_hDC(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Xbase(TXbClsParams * px)          // 1 // ::_Member_Xbase(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Xbase", "Object not properly initialized." ); }
   else
   {
      psc->Member_Xbase(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_DWord64(TXbClsParams * px)        // 1 // ::_Member_DWord64(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_DWord64", "Object not properly initialized." ); }
   else
   {
      psc->Member_DWord64(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_XDate(TXbClsParams * px)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_XDate", "Object not properly initialized." ); }
   else
   {
      psc->Member_XDate(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Double(TXbClsParams * px)         // 1 // ::_Member_Double(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Double", "Object not properly initialized." ); }
   else
   {
      psc->Member_Double(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_Float(TXbClsParams * px)          // 1 // ::_Member_Float(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Float", "Object not properly initialized." ); }
   else
   {
      psc->Member_Float(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_lpStr(TXbClsParams * px)          // 1 // ::_Member_lpStr(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_lpStr", "Object not properly initialized." ); }
   else
   {
      psc->Member_lpStr(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_BinStr(TXbClsParams * px)         // 2 // ::_Member_BinStr(cName,nSize)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_BinStr", "Object not properly initialized." ); }
   else
   {
      psc->Member_BinStr(px->ParamLockStr(1),px->GetParamDWord(2));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_szStr(TXbClsParams * px)          // 2 // ::_Member_szStr(cName,nSize)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_szStr", "Object not properly initialized." ); }
   else
   {
      psc->Member_szStr(px->ParamLockStr(1),px->GetParamDWord(2));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_szWStr(TXbClsParams * px)          // 2 // ::_Member_szWStr(cName,nSize)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_szWStr", "Object not properly initialized." ); }
   else
   {
      psc->Member_szWStr(px->ParamLockStr(1),px->GetParamDWord(2));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_DynSz(TXbClsParams * px)          // 1 // ::_Member_DynSz(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_DynSz", "Object not properly initialized." ); }
   else
   {
      psc->Member_DynSz(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
static void TXbClass_Member_XppGuiWnd(TXbClsParams * px)          // 1 // ::_Member_XppGuiWnd(cName)
{
   TXbClass * psc;
   psc = (TXbClass*) px->GetSelfC();
   if( psc == NULL ){ PXERROR( 0 , "_Member_Member_XppGuiWnd", "Object not properly initialized." ); }
   else
   {
      psc->Member_XppGuiWnd(px->ParamLockStr(1));
      px->ParamUnlockStr(1);
      px->PutReturnSelf();
   }
}
//-----------------------------------------------------------------------------------------------------------------------
ULONG TXbClsParams::GetMemberType(LPSTR pName)
{
  ContainerHandle con = GetMember(pName);
  ULONG nType;
  _conType(con,&nType);
  _conRelease(con);
  return nType;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL  TXbClsParams::CheckMemberType(LPSTR pName, ULONG ulType){ return (GetMemberType(pName) & ulType);}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClsParams::GetTMember(LPSTR pName , ULONG ulType){ return _conTMember(GetSelf(),pName,ulType);}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClsParams::GetMember(LPSTR pName)
{
  ContainerHandle con = _conNew(NULLCONTAINER);
  _conGetMember(GetSelf(),pName,con);
  return con;
}
//----------------------------------------------------------------------------------------------------------------------
void  TXbClsParams::PutMember(LPSTR pName, ContainerHandle con ){ _conSetMember(GetSelf(),pName,con);}
//----------------------------------------------------------------------------------------------------------------------
void  TXbClsParams::PutMemberR(LPSTR pName, ContainerHandle con )
{
   _conSetMember(GetSelf(),pName,con);
   _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbClsParams::GetMemberStr(LPSTR pName , ULONG * pnLen){ return _pszMember( GetSelf(),pName, pnLen);}
// -----------------------------------------------------------------------------------------------------------------
LPWSTR TXbClsParams::GetMemberStr2W(LPSTR pName , ULONG * pnLen){ return _pszMember2W(GetSelf(),pName, pnLen);}
//----------------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::GetMemberBool(LPSTR pName){ return _conGetLMember(GetSelf(),pName);}
//----------------------------------------------------------------------------------------------------------------------
LONG TXbClsParams::GetMemberLong(LPSTR pName){ return _conGetNLMember(GetSelf(),pName);}
//----------------------------------------------------------------------------------------------------------------------
DWORD TXbClsParams::GetMemberDWord(LPSTR pName){ return (DWORD ) GetMemberLong(pName); }
//----------------------------------------------------------------------------------------------------------------------
WORD TXbClsParams::GetMemberWord(LPSTR pName){ return (WORD) GetMemberLong(pName); }
//----------------------------------------------------------------------------------------------------------------------
double TXbClsParams::GetMemberDouble(LPSTR pName)
{
   double nd = 0.00F;
   ContainerHandle con = GetTMember( pName , XPP_NUMERIC );
   if( con != NULLCONTAINER ){ _conGetND( con , &nd); _conRelease(con); }
   return nd;
}
//----------------------------------------------------------------------------------------------------------------------
FLOAT TXbClsParams::GetMemberFloat(LPSTR pName){ return (FLOAT) GetMemberDouble(pName); }
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutMemberBool(LPSTR pName,BOOL value){_conSetLMember( GetSelf(),pName,value);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutMemberLong(LPSTR pName , LONG  value ){_conSetNLMember( GetSelf(),pName,value);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutMemberDWord(LPSTR pName,DWORD value){ PutMemberLong(pName,(LONG) value);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutMemberWord(LPSTR pName , WORD value ){ PutMemberLong(pName,(LONG) value);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutMemberDouble(LPSTR pName , double   value )
{
   ContainerHandle con = _conPutND(NULLCONTAINER,value);
   PutMember(pName,con);
   _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutMemberFloat(LPSTR pName ,FLOAT value){PutMemberDouble(pName,(double) value );}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::MemberPutStrLen(LPSTR pName,LPSTR pStr , ULONG nLen)
{
   ContainerHandle con = _conPutCL(NULLCONTAINER,pStr,nLen);
   PutMember(pName,con);
   _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::MemberPutStr(LPSTR pName,LPSTR pStr)
{
   ContainerHandle con = _conPutC(NULLCONTAINER,pStr);
   PutMember(pName,con);
   _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
// TXbClass()::AddClassHook( cClsName, oHook) -> dwHookId
static void TXbClass_cm_AddClassHook(TXbClsParams * px)
{
   px->PutReturnDWord(TXbClass::AddClassHook( px->ParamLockStr(1) , px->GetTParam(2,XPP_OBJECT|XPP_BLOCK ) ) );
   px->ParamUnlockStr(1);
}
//----------------------------------------------------------------------------------------------------------------------
