//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifndef _OT4XB_CH_
#define _OT4XB_CH_
#pragma library ("ot4xb.lib")
// ---------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_misc_commands  
     | category: commands , ot4xb.ch 
     | command_: SWAP a , b  |desc_:  Swap values between a and b
     | deprecated: kept for existing code only; do not use in new code
     | note: Not active when OT4XB_LEAN_AND_MEAN is defined before including ot4xb.ch: that define leaves
     | _kw_: commands, ot4xb.ch, DEFAULT, SWAP, SET VARIANT, misc
       out old things of little use that existing code may still rely on, and SWAP is one of them. }}*/

#ifndef OT4XB_LEAN_AND_MEAN
#xcommand SWAP  <a> , <b> 	=> TlsStackPush(<a>) ;
							       ; <a> := <b>      ;
							       ; <b> := TlsStackPop()
#endif

// ---------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_debug_commands  
     | category: commands , ot4xb.ch , debug
     | _kw_: commands, ot4xb.ch, assert, debug, SendLog, log with file line
     | command_: OT4XB ASSERT HEADER  |desc_:  throw an error if ot4xb.ch header is not compatible with the ot4xb.dll version }}*/

#xcommand OT4XB ASSERT HEADER => ;
if ( ot4xb() \< "001.008.000.000")  );
;   TlsStackPush(Error():New());
;   TlsStackTop():severity := 2;
;   TlsStackTop():description := "ot4xb header file require dll version 001.008.000.000 or above" ;
;   Eval( ErrorBlock() , TlsStackPop() );
;end


#ifndef CRLF
#define CRLF              (Chr(13)+Chr(10))
#endif

/*{{ topic: ot4xb_ch_misc_commands | command_: DEFAULT var := val |desc_:  Set default value to var if != NIL  }}*/

#xcommand DEFAULT <uVar1> := <uVal1> => ;
if <uVar1> == NIL ;
;  <uVar1> := <uVal1> ;
;end

// ---------------------------------------------------------------------------
#ifndef OT4XB_LEAN_AND_MEAN
/*{{ begin-topic }}*/
/*{{   topic: ot4xb_ch_deprecated_commands
     | category: commands , ot4xb.ch , deprecated
     | note: This commands was created in early versions of ot4xb colected from another old stuff, but causing more noise than benefit.
     | _kw_: commands, ot4xb.ch, deprecated, BYNAME, LEAN_AND_MEAN
        can de dissabled by defining **OT4XB_LEAN_AND_MEAN** before include **ot4xb.ch** }}*/ 

/*{{|xtranslate: BYNAME v [, vN ]   |desc_:  assign the parameters with name v to the object variables with same names  }}*/

#xtranslate BYNAME <V> [, <VN> ]     => ::<V> := <V> [; ::<VN> := <VN> ]

/*{{|xtranslate: BYNAME var DEFAULT val   |desc_:  assign the parameters with name var to the object variable with same name and default value if NIL }}*/
#xtranslate BYNAME <V> DEFAULT <Val> => ::<V> := iif(<V> == NIL , <Val> , <V> )

/*{{|xtranslate: BYNAME var IFNONIL |desc_:  assign the parameters with name var to the object variable with same name if parameter is not NIL   }}*/
#xtranslate BYNAME <V> IFNONIL =>  if <V> != NIL ; ::<V> := <V> ;  end

/*{{|xtranslate: StrTrim(n)  |desc_:  assign the parameters with name var to the object variable with same name and default value if NIL   }}*/
#xtranslate StrTrim(<n>)   =>  LTrim(Str(<n>))

/*{{ end-topic }}*/
#endif


// --------------------------------------------------------------------------- 
/*{{ note-id: expando-serialize-flags | title_: JSON serialization flags (EXPANDO_FORMAT_*)
   |: The nFlags of the expando JSON serialization is a combination (nOr) of these ot4xb.ch constants; the
     `_OT4XB_EXPANDO_FORMAT_*` pseudo-constants are the same values under their old names.

     - `EXPANDO_FORMAT_DEBUG` 1 - wrap every value in a JSON array tagged with its type letter (C, D, N, L, A...)
     - `EXPANDO_FORMAT_FLAT_ARRAY_KV_ITEMS` 0x00000010 - nested arrays one per line, without pretty printing
       their items
     - `EXPANDO_FORMAT_ENFORCE_FLAT` 0x00000020 - suppress pretty formatting inside expando object serialization
     - `EXPANDO_FORMAT_PRETTY` 0x01000000 - CRLF and indentation
     - `EXPANDO_FORMAT_ND_PRECISSION( n )` - number of decimal digits for doubles (bits 16-19; 15 when omitted)
     - `EXPANDO_FORMAT_ND_FIXED` 0x00100000 - doubles in fixed decimal notation ("%.Nf")
     - `EXPANDO_FORMAT_ND_MINIMAL` 0x00200000 - doubles in minimal representation without losing precision
       ("%.Ng"); the default of ::json_serialize() }}*/

#xtranslate _OT4XB_EXPANDO_FORMAT_DEBUG                  => 1
#xtranslate _OT4XB_EXPANDO_FORMAT_PRETTY                 => 0x01000000
#xtranslate _OT4XB_EXPANDO_FORMAT_ND_PRECISSION( <x> )   => nLShift( nAnd( <x> , 0x0F ) , 16 )
#xtranslate _OT4XB_EXPANDO_FORMAT_ND_FIXED               => 0x00100000
#xtranslate _OT4XB_EXPANDO_FORMAT_ND_MINIMAL             => 0x00200000

// --------------------------------------------------------------------------- 
/*{{function: _UuidCreate 
| note: The function UuidCreate() was included in xpprt1.dll in Xbase++ 1.9.355 , 
        so to avoid conflicts and mantain compatibility ot4xb.dll renamed to 
        _UuidCreate() and added a `#pragma Map( UUIDCREATE, "_UUIDCREATE" )` in ot4xb.ch.
        **OT4XB_LEAN_AND_MEAN** will dissable this function map }}*/
#ifndef OT4XB_LEAN_AND_MEAN
#pragma Map( UUIDCREATE, "_UUIDCREATE" )
#endif
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_debug_commands
   | command_: ### ot4xb_SendLog / ot4xb_SendFLog
   | syntax_: `ot4xb_SendLog( <params,...> )`
   | syntax_: `ot4xb_SendFLog( <params,...> )`
   | desc_: Debug logging that costs nothing in release builds: with OT4XB_DEBUG defined they expand to
     ot4xb_lSendLogStr( ... ) and ot4xb_lSendLogStrFL( __FILE__, __LINE__, ... ); without it both expand to
     nothing. The F form logs the source file and line of the call, and a preprocessor translation is the
     only way to get them right: `__FILE__` and `__LINE__` are expanded where the command is written, which
     no function called at run time could know.
   | params:
     - `params` The values to log, as accepted by ot4xb_lSendLogStr().
   | note: These two are an example: the natural thing is to write your own commands of this kind over the log
     functions, which also accept a source id other than the one ot4xb uses for itself.
   | see-also: {{ilink: <function ot4xb_lSendLogStr> ot4xb_lSendLogStr}}, {{ilink: <function ot4xb_lSendLogStrFL> ot4xb_lSendLogStrFL}} }}*/
#ifdef OT4XB_DEBUG
#ifndef OT4XB_ASSERT_ALL
#define OT4XB_ASSERT_ALL
#endif
#xtranslate ot4xb_SendFLog(<params,...>) => ot4xb_lSendLogStrFL( __FILE__ , __LINE__ , <params> )
#xtranslate ot4xb_SendLog(<params,...>)  => ot4xb_lSendLogStr( <params> )
#else
#xtranslate ot4xb_SendLog( <params,...>  )  =>
#xtranslate ot4xb_SendFLog( <params,...>  ) =>
#endif

//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_debug_commands
   |: ### Assert levels

     `OT4XB_ASSERT_LEVEL` selects which of the `_Assert_*` checks below are compiled in: 0 (the default) compiles
     none of them, 1 adds `_Assert_Range_`, 2 adds `_Assert_fp_`, 3 adds `_Assert_dll_fn_`. Defining
     `OT4XB_ASSERT_ALL` before including ot4xb.ch forces the level to 100 (everything), and `OT4XB_DEBUG` implies
     `OT4XB_ASSERT_ALL` and enables the `ot4xb_SendLog` / `ot4xb_SendFLog` translations. A check that is not
     compiled in expands to nothing (`NIL`). }}*/
#ifdef OT4XB_ASSERT_ALL
#ifdef OT4XB_ASSERT_LEVEL
#undef OT4XB_ASSERT_LEVEL
#endif
#define OT4XB_ASSERT_LEVEL   100
#endif
//----------------------------------------------------------------------------------------------------------------------
#ifndef OT4XB_ASSERT_LEVEL
#define OT4XB_ASSERT_LEVEL   0
#endif
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_debug_commands
   | command_: ### _Assert_Range_
   | syntax_: `_Assert_Range_( <value>, <min>, <max> )`
   | desc_: Raises an ot4xb error (severity 2, "Value out of range") when value is below min or above max; otherwise
     it yields value. Used by the generated structure member accessors (MEMBER BINSTR ... ARRAY) and available
     to your own code.
   | params:
     - `value` Value to check.
     - `min` Lowest accepted value.
     - `max` Highest accepted value.
   | note: Compiled in only with OT4XB_ASSERT_LEVEL > 0 (or OT4XB_ASSERT_ALL / OT4XB_DEBUG); otherwise it expands
     to NIL. }}*/
#if OT4XB_ASSERT_LEVEL > 0
#xtranslate _Assert_Range_(<v>,<min>,<max>) => iif( ((<v> \> <max>) .or. (<v> \< <min>)),;
            ( TlsStackPush(Error():New()) ,TlsStackTop():severity := 2,;
              TlsStackTop():description := "Value out of range" ,;
              Eval(ErrorBlock(),TlsStackPop() ) ),<v>)
#else
#xtranslate _Assert_Range_(<v>,<min>,<max>) => NIL
#endif
// -----------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_debug_commands
   | command_: ### _Assert_fp_
   | syntax_: `_Assert_fp_( <nFunctionPointer> )`
   | desc_: Raises an ot4xb error (severity 2, "Function is not declared") when the function pointer is 0: the check
     the DLL IMPORT family runs on the address returned by nGetProcAddress() before calling it.
   | params:
     - `nFunctionPointer` Numeric function pointer to check.
   | note: Compiled in only with OT4XB_ASSERT_LEVEL > 1 (or OT4XB_ASSERT_ALL / OT4XB_DEBUG); otherwise it expands
     to NIL. }}*/
#if OT4XB_ASSERT_LEVEL > 1
#xtranslate _Assert_fp_(<fp>) => iif( <fp> == 0,;
            ( TlsStackPush(Error():New()) ,TlsStackTop():severity := 2,;
              TlsStackTop():description := "Function is not declared" ,;
              Eval(ErrorBlock(),TlsStackPop() )),)
#else
#xtranslate _Assert_fp_(<fp>) => NIL
#endif
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_debug_commands
   | command_: ### _Assert_dll_fn_
   | syntax_: `_Assert_dll_fn_( <dll>, <function> )`
   | desc_: Raises an ot4xb error (severity 2, "Function X not found in dll Y") when nFpGet() cannot resolve the export
     `<function>` of the DLL `<dll>`: the check the `@dll:function( ... )` shorthand runs before calling
     ({{ilink: <topic quick_call_dll_functions> quick_call_dll_functions}}). Both names are written bare.
   | params:
     - `dll` DLL name.
     - `function` Export name.
   | note: Compiled in only with OT4XB_ASSERT_LEVEL > 2 (or OT4XB_ASSERT_ALL / OT4XB_DEBUG); otherwise it expands
     to NIL. }}*/
#if OT4XB_ASSERT_LEVEL > 2
#xtranslate _Assert_dll_fn_(<dll>,<fn>) => iif( nFpGet({<(dll)>,<(fn)>}) == 0,;
            ( TlsStackPush(Error():New()) ,TlsStackTop():severity := 2,;
              TlsStackTop():description := "Function "+<(fn)>+" not found in dll " + <(dll)> ,;
              Eval(ErrorBlock(),TlsStackPop() )),)
#else
#xtranslate _Assert_dll_fn_(<dll>,<fn>) => NIL
#endif
//----------------------------------------------------------------------------------------------------------------------
#define OT4XB_LOG_WND_CLASS  "11CBDBE2_0AF0_4713_B463_269FA6E2654B"
//----------------------------------------------------------------------------------------------------------------------
#define GWST_S_BASE  1
#define GWST_S_EXTRA 2
#define GWST_S_ALL   3
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### GwstArrayNext
   | syntax_: `GwstArrayNext( <oStructure> )`
   | desc_: Re-links a structure object to the next element of a C array of structures in memory: the address
     advances by the structure size, the memory is not copied. Usable anywhere.
   | params:
     - `oStructure` Structure object linked to the current element.
   | _kw_: commands, ot4xb.ch, BEGIN STRUCTURE, MEMBER, GWST, binary structure
   | see-also: GwstArrayPrev, gwst_sizeof }}*/
#xtranslate GwstArrayNext( <o> ) => <o>:_link_( <o>:_addressof_() + <o>:_sizeof_(),.F.)
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### GwstArrayPrev
   | syntax_: `GwstArrayPrev( <oStructure> )`
   | desc_: Re-links a structure object to the previous element of a C array of structures in memory: the address
     goes back by the structure size, the memory is not copied. Usable anywhere.
   | params:
     - `oStructure` Structure object linked to the current element.
   | see-also: GwstArrayNext, gwst_sizeof }}*/
#xtranslate GwstArrayPrev( <o> ) => <o>:_link_( <o>:_addressof_() - <o>:_sizeof_(),.F.)
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | _slug_: structure-commands
   | category: commands , ot4xb.ch
   | desc: Commands to define a binary structure class (GWST): a dynamic class that additionally describes a binary
     memory layout. BEGIN STRUCTURE ... END STRUCTURE define it, the MEMBER commands add the members in order,
     the auxiliary pseudo-functions adjust offsets and alignment. Every command here is a preprocessor command
     defined in ot4xb.ch.
   |: Every MEMBER command adds a member to the structure being defined and only makes sense between
     BEGIN STRUCTURE and END STRUCTURE. In all of them `<memberName>` is the name of the member being added.
   |: Auxiliary functions - #xtranslate pseudo-functions over the class builder, usable only inside a
     class or structure definition: `GwstAlignNextMember( n )`, `GwstGetOffset()`, `GwstSetOffset( n )`,
     `GwstSkipBytes( n )`. Each one is documented below. }}*/
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### GWSTSKIPBYTES
   | syntax_: `GWSTSKIPBYTES( <nBytes> )`
   | desc_: Advances the offset of the next member by nBytes bytes (padding); inside a union it grows the union size
     to at least nBytes bytes. Usable only inside a class or structure definition.
   | params:
     - `nBytes` Numeric - Bytes to skip.
   | see-also: GWSTGETOFFSET, GWSTSETOFFSET, GWSTALIGNNEXTMEMBER }}*/
#xtranslate GWSTSKIPBYTES( <n> ) => ooo:_GwstSkipBytes( <n> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### GWSTGETOFFSET
   | syntax_: `GWSTGETOFFSET()`
   | desc_: Returns the offset where the next member will be placed. Usable only inside a class or structure definition.
   | see-also: GWSTSETOFFSET, GWSTSKIPBYTES }}*/
#xtranslate GWSTGETOFFSET() => ooo:_GwstGetOffset()
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### GWSTSETOFFSET
   | syntax_: `GWSTSETOFFSET( <nOffset> )`
   | desc_: Sets the offset where the next member will be placed, so members can overlay earlier ones (unions) or
     leave gaps. Usable only inside a class or structure definition.
   | params:
     - `nOffset` Numeric - Byte offset of the next member.
   | see-also: GWSTGETOFFSET, GWSTBACK, BEGIN UNION }}*/
#xtranslate GWSTSETOFFSET( <n> ) => ooo:_GwstSetOffset( <n> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### GWSTALIGNNEXTMEMBER
   | syntax_: `GWSTALIGNNEXTMEMBER( <nPack> )`
   | desc_: Rounds the offset of the next member up to the next multiple of nPack bytes, the way a C compiler packs
     structure members. Usable only inside a class or structure definition.
   | params:
     - `nPack` Numeric - Alignment in bytes (1, 2, 4, 8).
   | see-also: GWSTSKIPBYTES, GWSTSETOFFSET }}*/
#xtranslate GWSTALIGNNEXTMEMBER( <n> ) => ooo:_GwstAlignNextMember( <n> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### GWSTBACK
   | syntax_: `GWSTBACK`
   | desc_: Moves the structure layout offset back by the size of the last defined member, so the next
     member overlays the same bytes. This can be useful to create inline unions.
   | example: ```
     MEMBER DYNSZ cSrc
     GWSTBACK
     MEMBER LPSTR pSrc
     ...
     END STRUCTURE
     ...
     o:cSrc := "This is a String"
     ? o:pSrc     // Return the memory pointer of cSrc
     ```
   | see-also: BEGIN UNION, MEMBER LPSTR DYNSZ
 }}*/
#xtranslate GWSTBACK() => ooo:_GwstBack()
/*{{ topic: ot4xb_ch_structure_commands | _note_: documented under GWSTBACK }}*/
#xcommand   GWSTBACK   => GWSTBACK()
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### GWSTPARENT
   | syntax_: `GWSTPARENT( [ <ParentStructure> ] )`
   | desc_: Marks the class being built as a GWST structure class. With a parent structure class (given by its class
     function) its binary layout is inherited and the offset of the new members starts after it; without
     parameter the class descends directly from GWST. BEGIN STRUCTURE emits it for you.
   | params:
     - `ParentStructure` Class function of the parent structure class; optional.
   | see-also: BEGIN STRUCTURE, NS_BEGIN DYNAMIC CLASS }}*/
#xtranslate GWSTPARENT( [ <p1> ] )  => ooo:_GwstParent( [ <p1>() ] )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### ADDGWSTSTYLEMEMBERS
   | syntax_: `ADDGWSTSTYLEMEMBERS()`
   | desc_: Adds the GWST-style pointer support members to a dynamic class that is not a structure: the instance
     variable _m__pt_ and the methods :_lock_() and :_unlock_(). Usable only inside a class definition.
   | see-also: BEGIN DYNAMIC CLASS, GWSTPARENT }}*/
#xtranslate ADDGWSTSTYLEMEMBERS() => ooo:AddGwstStyleMembers()
// -----------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### gwst_sizeof
   | syntax_: `gwst_sizeof( <Structure> )`
   | desc_: The byte size of a structure class: expands to `<Structure>():_mc__size_`. Usable anywhere.
   | params:
     - `Structure` Class function of the structure class.
   | see-also: BEGIN STRUCTURE }}*/
#xtranslate gwst_sizeof( <st> ) => (<st>():_mc__size_)
/*{{ topic: ot4xb_ch_misc_commands
   | command_: ### SET VARIANT TO STRING LOCALE
   | syntax_: `SET VARIANT TO STRING LOCALE INVARIANT`
   | syntax_: `SET VARIANT TO STRING LOCALE DEFAULT`
   | desc_: Selects the locale the calling thread uses when the library converts COM variant values, typically to
     strings: INVARIANT formats them the same way on any machine, regardless of the user regional settings
     ({{ilink: <c-function ot4xb_set_tls_variant_to_string_locale_invariant> ot4xb_set_tls_variant_to_string_locale_invariant}});
     DEFAULT goes back to the plain Windows behaviour driven by the regional settings
     ({{ilink: <c-function ot4xb_set_tls_variant_to_string_locale> ot4xb_set_tls_variant_to_string_locale}} with 0). }}*/
#xtranslate SET VARIANT TO STRING LOCALE INVARIANT => (@ot4xb:ot4xb_set_tls_variant_to_string_locale_invariant())
/*{{ topic: ot4xb_ch_misc_commands | _note_: documented under SET VARIANT TO STRING LOCALE }}*/
#xtranslate SET VARIANT TO STRING LOCALE DEFAULT   => (@ot4xb:ot4xb_set_tls_variant_to_string_locale(0))
//-----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | _slug_: dynamic-class-commands
   | category: commands , ot4xb.ch
   | desc: Commands to build a class at runtime: BEGIN DYNAMIC CLASS opens a class function that creates the class
     object through a TXbClass builder the first time it is called, the DYNAMIC ... commands register
     variables, properties and methods (codeblocks) on that builder, and END DYNAMIC CLASS creates the class
     object and returns it. Every command here is a preprocessor command defined in ot4xb.ch.
   |: A dynamic class is built at runtime: BEGIN DYNAMIC CLASS opens a class function that creates the
     class object through a TXbClass builder the first time it is called, the DYNAMIC ... commands register
     variables, properties and methods on that builder, and END DYNAMIC CLASS creates the class object and
     returns it. A structure class is a dynamic class that additionally describes a binary memory layout:
     | _kw_: commands, ot4xb.ch, BEGIN DYNAMIC CLASS, runtime class, dynamic class
     BEGIN STRUCTURE ... END STRUCTURE define it, adding the members with the MEMBER commands. }}*/
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### NS_BEGIN DYNAMIC CLASS
   | syntax_: `NS_BEGIN DYNAMIC CLASS <ClsName> [ FROM <Parent1> [, <ParentN>] ] [ local <local1>, ... ]`
   | desc_: Variant of BEGIN DYNAMIC CLASS that does not emit the `function <ClsName>()` statement: use
     it to build the class inside a function declared by hand. It still declares the working locals
     and returns the class object right away when the class already exists.
   | see-also: BEGIN DYNAMIC CLASS, END DYNAMIC CLASS, NS_BEGIN STRUCTURE
 }}*/
#xcommand NS_BEGIN DYNAMIC CLASS <Tag> [ FROM <p1> [, <pN>] ] [<*more*>] => ;
          ; local ooo ;
          ; local oClass := ClassObject(<(Tag)>);
          [;<more>] ;
          ; if oClass != NIL ;
          ; return oClass ;
          ; end ;
          ; ooo := TXbClass():New( <(Tag)>) ;
          [; ooo:Parent( <p1>() ) ];
          [; ooo:Parent( <pN>() )]
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### BEGIN DYNAMIC CLASS
   | syntax_: `BEGIN DYNAMIC CLASS <ClsName> [ FROM <Parent1> [, <ParentN>] ] [ local <local1>, ... ]`
   | desc_: Opens the definition of a dynamic class. It generates `function <ClsName>()`, the class
     function of the new class: the first call builds the class object through a TXbClass builder and
     returns it, later calls return the already created class object. The FROM clause lists the parent
     classes, each given by its own class function name. Any text after the parents is emitted
     verbatim inside the generated function before the class is built - typically a `local` statement
     declaring work variables used by COMPILE / INSERT code.
   | params:
     - `ClsName` Name of the class, and of the generated class function.
     - `Parent1` Class function of a parent class (it is called to obtain the parent class object).
   | see-also: END DYNAMIC CLASS, NS_BEGIN DYNAMIC CLASS, INLINE DYNAMIC CLASS, BEGIN STRUCTURE
 }}*/
#xcommand BEGIN DYNAMIC CLASS <Tag> [ FROM <p1> [, <pN>] ] [<*more*>] => ;
          function <Tag>() ;
          ; NS_BEGIN DYNAMIC CLASS <Tag> [ FROM <p1> [, <pN>] ] [<more>]
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### END DYNAMIC CLASS
   | syntax_: `END DYNAMIC CLASS`
   | desc_: Closes a dynamic class definition: the class object is created from everything registered
     on the builder, the builder is destroyed, and the class object is returned.
   | see-also: BEGIN DYNAMIC CLASS, END STRUCTURE
 }}*/
#xcommand END DYNAMIC CLASS => oClass := ooo:Create() ; ooo:Destroy() ; return oClass
//-----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### DYNAMIC VAR
   | syntax_: `DYNAMIC VAR <cVarName> [ FLAGS <nExtra> ]`
   | desc_: Adds an instance variable to the class being defined (expands to ::_Var()).
   | params:
     - `cVarName` Name of the variable.
     - `nExtra` Numeric - Optional attribute flags, see below.
   | flags: FLAGS `<nExtra>` is ORed into the attributes of the variable, on top of its kind and of the default
     scope of the class; the bits are the ones of ot4xb_constants.h:
     - `0x0001` xppCLASS_HIDDEN, `0x0002` xppCLASS_PROTECTED, `0x0003` xppCLASS_EXPORTED - access scope
     - `0x0010` xppVAR_ASSIGN_HIDDEN, `0x0020` xppVAR_ASSIGN_PROTECTED, `0x0030` xppVAR_ASSIGN_EXPORTED - assign scope
   | see-also: DYNAMIC CLASS VAR, DYNAMIC SHARED CLASS VAR, DYNAMIC PROPERTY }}*/
#xcommand DYNAMIC VAR                <cName>  [FLAGS <nExtra> ]    => ooo:_Var(<(cName)> [, <nExtra> ])
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### DYNAMIC CLASS VAR
   | syntax_: `DYNAMIC CLASS VAR <cVarName> [ FLAGS <nExtra> ]`
   | desc_: Adds a class variable, living on the class object, to the class being defined (expands to
     ::_ClassVar()).
   | params:
     - `cVarName` Name of the variable.
     - `nExtra` Numeric - Optional attribute flags, see below.
   | flags: FLAGS `<nExtra>` is ORed into the attributes of the variable, on top of its kind and of the default
     scope of the class; the bits are the ones of ot4xb_constants.h:
     - `0x0001` xppCLASS_HIDDEN, `0x0002` xppCLASS_PROTECTED, `0x0003` xppCLASS_EXPORTED - access scope
     - `0x0010` xppVAR_ASSIGN_HIDDEN, `0x0020` xppVAR_ASSIGN_PROTECTED, `0x0030` xppVAR_ASSIGN_EXPORTED - assign scope
   | see-also: DYNAMIC VAR, DYNAMIC SHARED CLASS VAR }}*/
#xcommand DYNAMIC CLASS VAR          <cName>  [FLAGS <nExtra> ]    => ooo:_ClassVar(<(cName)> [, <nExtra> ])
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### DYNAMIC SHARED CLASS VAR
   | syntax_: `DYNAMIC SHARED CLASS VAR <cVarName> [ FLAGS <nExtra> ]`
   | desc_: Adds a shared class variable to the class being defined (expands to ::_SharedClassVar()); SHARED
     means the same as in the declarative CLASS VAR syntax.
   | params:
     - `cVarName` Name of the variable.
     - `nExtra` Numeric - Optional attribute flags, see below.
   | flags: FLAGS `<nExtra>` is ORed into the attributes of the variable, on top of its kind and of the default
     scope of the class; the bits are the ones of ot4xb_constants.h:
     - `0x0001` xppCLASS_HIDDEN, `0x0002` xppCLASS_PROTECTED, `0x0003` xppCLASS_EXPORTED - access scope
     - `0x0010` xppVAR_ASSIGN_HIDDEN, `0x0020` xppVAR_ASSIGN_PROTECTED, `0x0030` xppVAR_ASSIGN_EXPORTED - assign scope
   | see-also: DYNAMIC VAR, DYNAMIC CLASS VAR }}*/
#xcommand DYNAMIC SHARED CLASS VAR   <cName>  [FLAGS <nExtra> ]    => ooo:_SharedClassVar(<(cName)> [, <nExtra> ])
//-----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### DYNAMIC PROPERTY
   | syntax_: `DYNAMIC [READONLY|WRITEONLY] [CLASS] PROPERTY <cName> BLOCK <uBlock>`
   | desc_: Adds a property implemented by a code block. The block is evaluated with the object as its
     only parameter to read the property, and with the object plus the assigned value to write it, as
     in `{|Self,v| iif( PCount() > 1, <write>, <read> ) }`. READONLY / WRITEONLY register the property
     as read-only / write-only; with CLASS the property lives on the class object instead of the
     instances.
   | params:
     - `cName` Name of the property.
     - `uBlock` CodeBlock - Implementation of the property.
   | see-also: DYNAMIC PROPERTY READ WRITE, DYNAMIC PROPERTY COMPILE, DYNAMIC VAR, DYNAMIC METHOD
 }}*/
#xcommand DYNAMIC PROPERTY           <cName>  BLOCK <uBlock>       => ooo:_Property( <(cName)> , <uBlock> )
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY }}*/
#xcommand DYNAMIC CLASS PROPERTY     <cName>  BLOCK <uBlock>       => ooo:_ClassProperty( <(cName)> , <uBlock> )
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY READ WRITE }}*/
#xcommand DYNAMIC READONLY PROPERTY           <cName>  BLOCK <uBlock>       => ooo:_ROProperty( <(cName)> , <uBlock> )
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY READ WRITE }}*/
#xcommand DYNAMIC READONLY CLASS PROPERTY     <cName>  BLOCK <uBlock>       => ooo:_ROClassProperty( <(cName)> , <uBlock> )
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY READ WRITE }}*/
#xcommand DYNAMIC WRITEONLY PROPERTY           <cName>  BLOCK <uBlock>       => ooo:_WOProperty( <(cName)> , <uBlock> )
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY READ WRITE }}*/
#xcommand DYNAMIC WRITEONLY CLASS PROPERTY     <cName>  BLOCK <uBlock>       => ooo:_WOClassProperty( <(cName)> , <uBlock> )
//-----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### DYNAMIC PROPERTY READ WRITE
   | syntax_: `DYNAMIC [CLASS] PROPERTY <cName> READ <rExp> [ WRITE <wExp> ]`
   | syntax_: `DYNAMIC [CLASS] PROPERTY <cName> WRITE <wExp>`
   | desc_: Sugar over the BLOCK form of DYNAMIC PROPERTY: READ and WRITE take Xbase++ expressions
     instead of a code block. The expressions are wrapped into `{|Self,v| ...}`, so `Self` (the
     object) and `v` (the value being assigned, in WRITE) are available inside them. With only READ
     the property is read-only; with only WRITE it is write-only.
   | see-also: DYNAMIC PROPERTY, DYNAMIC PROPERTY COMPILE, DYNAMIC PROPERTY IS MASK
 }}*/
#xcommand DYNAMIC  PROPERTY <cc>  READ <rr> WRITE <ww> => ;
                   ooo:_Property(<(cc)>, {|Self,v|iif( PCount() > 1 , <ww> , <rr> ) } )

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY READ WRITE }}*/
#xcommand DYNAMIC  CLASS PROPERTY <cc>  READ <rr> WRITE <ww> => ;
                   ooo:_ClassProperty(<(cc)>, {|Self,v|iif( PCount() > 1 , <ww> , <rr> ) } )
//-----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY READ WRITE }}*/
#xcommand DYNAMIC  PROPERTY <cc>  READ <rr>  => ;
                   ooo:_ROProperty(<(cc)>, {|Self| <rr>  } )

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY READ WRITE }}*/
#xcommand DYNAMIC  CLASS PROPERTY <cc>  READ <rr> => ;
                   ooo:_ROClassProperty(<(cc)>, {|Self| <rr> } )
//-----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY READ WRITE }}*/
#xcommand DYNAMIC  PROPERTY <cc>  WRITE <ww> => ;
                   ooo:_WOProperty(<(cc)>, {|Self,v| <ww> } )

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY READ WRITE }}*/
#xcommand DYNAMIC  CLASS PROPERTY <cc>  WRITE <ww> => ;
                   ooo:_WOClassProperty(<(cc)>, {|Self,v| <ww> } )
//-----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### DYNAMIC PROPERTY COMPILE
   | syntax_: `DYNAMIC [READONLY|WRITEONLY] [CLASS] PROPERTY <cName> COMPILE <cString> [INSERT <p1> [, <pN>]]`
   | syntax_: `DYNAMIC [CLASS] PROPERTY <cName> COMPILE READ <cRead> [WRITE <cWrite>] [INSERT <p1> [, <pN>]]`
   | syntax_: `DYNAMIC [CLASS] PROPERTY <cName> COMPILE WRITE <cWrite> [INSERT <p1> [, <pN>]]`
   | desc_: Like the BLOCK / READ / WRITE forms, but the implementation is given as a Character string
     with the source code, macro-compiled while the class is being built. In the first form `<cString>`
     holds the source of a whole code block; in the READ / WRITE forms `<cRead>` and `<cWrite>` hold just
     the expression source and are wrapped like the READ / WRITE expression forms. The INSERT clause
     formats the string first with `cPrintf( <cString>, <p1> [, <pN>] )`, so it can carry
     printf-style placeholders filled with values computed at class-building time.
   | see-also: DYNAMIC PROPERTY, DYNAMIC PROPERTY READ WRITE, DYNAMIC METHOD
 }}*/
#xcommand DYNAMIC PROPERTY                  <cName>  COMPILE <ss>  => ooo:_Property( <(cName)> , (&(<ss>))  )
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC CLASS PROPERTY            <cName>  COMPILE <ss>  => ooo:_ClassProperty( <(cName)> , (&(<ss>)) )
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC READONLY PROPERTY         <cName>  COMPILE <ss>  => ooo:_ROProperty( <(cName)> ,  (&(<ss>))  )
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC READONLY CLASS PROPERTY   <cName>  COMPILE <ss>  => ooo:_ROClassProperty( <(cName)> ,  (&(<ss>)) )
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC WRITEONLY PROPERTY        <cName>  COMPILE <ss>  => ooo:_WOProperty( <(cName)> ,  (&(<ss>))  )
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC WRITEONLY CLASS PROPERTY  <cName>  COMPILE <ss>  => ooo:_WOClassProperty( <(cName)> ,  (&(<ss>))  )
//-----------------------------------------------------------------------------------------------------------------------

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC PROPERTY                  <cName>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          DYNAMIC PROPERTY                  <cName>  COMPILE cPrintf( <(ss)> ,<p1> [,<pN>])
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC CLASS PROPERTY            <cName>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          DYNAMIC CLASS PROPERTY            <cName>  COMPILE cPrintf( <(ss)> ,<p1> [,<pN>])
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC READONLY PROPERTY         <cName>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          DYNAMIC READONLY PROPERTY         <cName>  COMPILE cPrintf( <(ss)> ,<p1> [,<pN>])
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC READONLY CLASS PROPERTY   <cName>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          DYNAMIC READONLY CLASS PROPERTY   <cName>  COMPILE cPrintf( <(ss)> ,<p1> [,<pN>])
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC WRITEONLY PROPERTY        <cName>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          DYNAMIC WRITEONLY PROPERTY        <cName>  COMPILE cPrintf( <(ss)> ,<p1> [,<pN>])
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC WRITEONLY CLASS PROPERTY  <cName>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          DYNAMIC WRITEONLY CLASS PROPERTY  <cName>  COMPILE cPrintf( <(ss)> ,<p1> [,<pN>])
//-----------------------------------------------------------------------------------------------------------------------

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC  PROPERTY <cc>  COMPILE READ <rr> WRITE <ww> => ;
          DYNAMIC  PROPERTY <cc>  COMPILE "{|Self,v|iif( PCount() > 1 ," + <ww> +"," +  <rr> +")}"

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC  CLASS PROPERTY <cc>  COMPILE READ <rr> WRITE <ww> => ;
          DYNAMIC  CLASS PROPERTY <cc>  COMPILE "{|Self,v|iif( PCount() > 1 ," + <ww> +"," +  <rr> +")}"

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC  PROPERTY <cc>  COMPILE READ <rr>  => ;
          DYNAMIC  READONLY PROPERTY <cc>  COMPILE "{|Self|" + <rr> +"}"

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC  CLASS PROPERTY <cc>  COMPILE READ <rr> => ;
          DYNAMIC  READONLY CLASS PROPERTY <cc>  COMPILE "{|Self|" + <rr> +"}"

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC  PROPERTY <cc>  COMPILE WRITE <ww> => ;
          DYNAMIC  WRITEONLY PROPERTY <cc>  COMPILE "{|Self,v|" + <ww> +"}"

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC  CLASS PROPERTY <cc>  COMPILE WRITE <ww> => ;
          DYNAMIC  WRITEONLY CLASS PROPERTY <cc>  COMPILE "{|Self,v|" + <ww> +"}"

//-----------------------------------------------------------------------------------------------------------------------


/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC  PROPERTY <cc>  COMPILE READ <rr> WRITE <ww> INSERT <p1> [, <pN>] => ;
          DYNAMIC  PROPERTY <cc>  COMPILE "{|Self,v|iif( PCount() > 1 ," + <ww> +"," +  <rr> +")}" ;
          INSERT <p1> [, <pN>]

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC  CLASS PROPERTY <cc>  COMPILE READ <rr> WRITE <ww> INSERT <p1> [, <pN>] => ;
          DYNAMIC  CLASS PROPERTY <cc>  COMPILE "{|Self,v|iif( PCount() > 1 ," + <ww> +"," +  <rr> +")}" ;
          INSERT <p1> [, <pN>]

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC  PROPERTY <cc>  COMPILE READ <rr>  INSERT <p1> [, <pN>]  => ;
          DYNAMIC  READONLY PROPERTY <cc>  COMPILE "{|Self|" + <rr> +"}" INSERT <p1> [, <pN>]

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC  CLASS PROPERTY <cc>  COMPILE READ <rr> INSERT <p1> [, <pN>]  => ;
          DYNAMIC  READONLY CLASS PROPERTY <cc>  COMPILE "{|Self|" + <rr> +"}" INSERT <p1> [, <pN>]

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC  PROPERTY <cc>  COMPILE WRITE <ww> INSERT <p1> [, <pN>]  => ;
          DYNAMIC  WRITEONLY PROPERTY <cc>  COMPILE "{|Self,v|" + <ww> +"}" INSERT <p1> [, <pN>]

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY COMPILE }}*/
#xcommand DYNAMIC  CLASS PROPERTY <cc>  COMPILE WRITE <ww> INSERT <p1> [, <pN>]  => ;
          DYNAMIC  WRITEONLY CLASS PROPERTY <cc>  COMPILE "{|Self,v|" + <ww> +"}" INSERT <p1> [, <pN>]
//-----------------------------------------------------------------------------------------------------------------------

/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### DYNAMIC PROPERTY IS MASK
   | syntax_: `DYNAMIC [CLASS] PROPERTY <cName> IS MASK <nMask> OF <var> [READONLY]`
   | desc_: Defines a Logical property mapping one or more bits of a Numeric member: reading returns
     `lAnd( ::<var>, <nMask> )`; assigning .T. sets the mask bits with nOr(), assigning .F. clears
     them with nAndNot(). With READONLY only the read side is generated.
   | params:
     - `cName` Name of the property.
     - `nMask` Integer constant containing the bits to set or get.
     - `var` Numeric member of the same class acting as a container for the flags.
   | see-also: PROPERTY IS MASK, DYNAMIC PROPERTY READ WRITE, DYNAMIC BITFIELD
 }}*/
#xcommand DYNAMIC PROPERTY <cc>  IS MASK <mask> OF <var> => ;
          DYNAMIC  PROPERTY <cc>  ;
          READ lAnd( ::<var> , <mask> ) ;
          WRITE (  ::<var> := iif(v,nOr( ::<var>,<mask>),nAndNot(::<var>,<mask>)) )

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY IS MASK }}*/
#xcommand DYNAMIC PROPERTY <cc>  IS MASK <mask> OF <var> READONLY => ;
          DYNAMIC  PROPERTY <cc>  ;
          READ lAnd( ::<var> , <mask> )

/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### DYNAMIC PROPERTY IS CONSTANT
   | syntax_: `DYNAMIC [CLASS] PROPERTY <cName> IS CONSTANT <uVal>`
   | desc_: Defines a read-only property returning the fixed value `<uVal>` (it expands to
     `DYNAMIC [CLASS] PROPERTY <cName> READ <uVal>`).
   | params:
     - `cName` Name of the constant.
     - `uVal` Value of the constant.
   | see-also: PROPERTY IS CONSTANT, DYNAMIC PROPERTY READ WRITE
 }}*/
#xcommand DYNAMIC PROPERTY <cc>  IS CONSTANT <val> => DYNAMIC  PROPERTY <cc> READ <val>
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY IS MASK }}*/
#xcommand DYNAMIC CLASS PROPERTY <cc>  IS MASK <mask> OF <var> => ;
          DYNAMIC  CLASS PROPERTY <cc>  ;
          READ lAnd( ::<var> , <mask> ) ;
          WRITE (  ::<var> := iif(v,nOr( ::<var>,<mask>),nAndNot(::<var>,<mask>)) )

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY IS MASK }}*/
#xcommand DYNAMIC CLASS PROPERTY <cc>  IS MASK <mask> OF <var> READONLY => ;
          DYNAMIC  CLASS PROPERTY <cc>  ;
          READ lAnd( ::<var> , <mask> )

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC PROPERTY IS CONSTANT }}*/
#xcommand DYNAMIC CLASS PROPERTY <cc>  IS CONSTANT <val> => DYNAMIC  CLASS PROPERTY <cc> READ <val>
//-----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### DYNAMIC METHOD
   | syntax_: `DYNAMIC [CLASS] METHOD <cName> BLOCK <uBlock>`
   | syntax_: `DYNAMIC [CLASS] METHOD <cName> COMPILE <cString> [INSERT <p1> [, <pN>]]`
   | desc_: Adds a method implemented by a code block, which receives the object as its first parameter
     followed by the call parameters. COMPILE takes the block source as a Character string instead,
     macro-compiled at class-building time, and INSERT formats that string first with
     `cPrintf( <cString>, <p1> [, <pN>] )`, as in DYNAMIC PROPERTY COMPILE. With CLASS the method is
     registered as a class method on the class object.
   | params:
     - `cName` Name of the method.
     - `uBlock` CodeBlock - Implementation of the method.
   | see-also: DYNAMIC PROPERTY, DYNAMIC PROPERTY COMPILE
 }}*/
#xcommand DYNAMIC METHOD             <cName>  BLOCK <uBlock>       => ooo:_Method( <(cName)> , <uBlock> )

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC METHOD }}*/
#xcommand DYNAMIC METHOD <cc>  COMPILE <ss>   => ;
          ooo:_Method( <(cc)> , (&( <(ss)>)) )

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC METHOD }}*/
#xcommand DYNAMIC METHOD <cc>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          ooo:_Method( <(cc)> , (&( cPrintf( <(ss)> ,<p1> [,<pN>]))) )

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC METHOD }}*/
#xcommand DYNAMIC CLASS METHOD       <cName>  BLOCK <uBlock>       => ooo:_ClassMethod( <(cName)> , <uBlock> )

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC METHOD }}*/
#xcommand DYNAMIC CLASS METHOD <cc>  COMPILE <ss>   => ;
          ooo:_ClassMethod( <(cc)> , (&( <(ss)>)) )

/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC METHOD }}*/
#xcommand DYNAMIC CLASS METHOD <cc>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          ooo:_ClassMethod( <(cc)> , (&( cPrintf( <(ss)> ,<p1> [,<pN>]))) )

//-----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands |: ## Structure definition commands }}*/
// internal: intermediate command used by BEGIN STRUCTURE and INLINE CLASS STRUCTURE; not part of the
// documented interface
#xcommand NS_BEGIN STRUCTURE <Tag> [EXTENDING <super> ]  [<*more*>] => ;
          NS_BEGIN DYNAMIC CLASS <Tag> [<more>] ;
          ; GWSTPARENT( [ <super> ] )
//-----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### BEGIN STRUCTURE
   | syntax_: `BEGIN STRUCTURE <ClassName> [ EXTENDING <SuperClass> ] [ local <local1>, ... ]`
   | desc_: Opens the definition of a structure class: a dynamic class (see BEGIN DYNAMIC CLASS) whose
     GWST parent is set, so it describes a binary memory layout built with the MEMBER commands.
     EXTENDING names the parent structure class whose layout is inherited; without it the structure
     descends directly from GWST.
   | params:
     - `ClassName` Name of the structure class being defined.
     - `SuperClass` Name of the parent structure class.
   | see-also: END STRUCTURE, NS_BEGIN STRUCTURE, INLINE CLASS STRUCTURE, BEGIN DYNAMIC CLASS
 }}*/
#xcommand BEGIN STRUCTURE <Tag> [EXTENDING <super> ]  [<*more*>] => ;
          function <Tag>() ;
          ; NS_BEGIN STRUCTURE <Tag> [EXTENDING <super> ]  [<more>]
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### INLINE CLASS STRUCTURE
   | syntax_: `INLINE CLASS STRUCTURE <Tag> [ EXTENDING <SuperClass> ] [ local <local1>, ... ]`
   | desc_: For use inside a declarative CLASS ... ENDCLASS block: defines an inline class method `<Tag>`
     whose body builds (once) and returns a structure class named `<OuterClass><Tag>_st`, where
     OuterClass is the name of the declaring class. EXTENDING works as in BEGIN STRUCTURE.
   | see-also: BEGIN STRUCTURE, INLINE DYNAMIC CLASS
 }}*/
#xcommand INLINE CLASS STRUCTURE <Tag> [EXTENDING <super> ]  [<*more*>] => ;
          INLINE CLASS METHOD <Tag>() ;
          ; NS_BEGIN STRUCTURE ( ::ClassName() + <(Tag)> + "_st") [EXTENDING <super> ]  [<more>]
// -----------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### INLINE DYNAMIC CLASS
   | syntax_: `INLINE DYNAMIC CLASS <Tag> [ FROM <Parent1> [, <ParentN>] ] [ local <local1>, ... ]`
   | desc_: For use inside a declarative CLASS ... ENDCLASS block: defines an inline class method `<Tag>`
     whose body builds (once) and returns a dynamic class named `<OuterClass>_<Tag>_cls`, where
     OuterClass is the name of the declaring class. The clauses work as in BEGIN DYNAMIC CLASS.
   | see-also: BEGIN DYNAMIC CLASS, INLINE CLASS STRUCTURE
 }}*/
#xcommand INLINE DYNAMIC CLASS <Tag> [ FROM <p1> [, <pN>] ]  [<*more*>] => ;
          INLINE CLASS METHOD <Tag>() ;
          ; NS_BEGIN DYNAMIC CLASS ( ::ClassName() + "_" + <(Tag)> + "_cls") [ FROM <p1> [, <pN>] ] [<more>]
//-----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### END STRUCTURE
   | syntax_: `END STRUCTURE`
   | desc_: Closes a structure definition. Identical to END DYNAMIC CLASS: the class object is created,
     the builder is destroyed and the class object is returned.
   | see-also: BEGIN STRUCTURE, END DYNAMIC CLASS
 }}*/
#xcommand END STRUCTURE => END DYNAMIC CLASS
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands |: ## Structure members }}*/
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER @
   | syntax_: `MEMBER @ <memberClass> <memberName>`
   | desc_: Embeds a child structure: `<memberClass>` is the class name of another gwst structure. Using
     this command you can create nested structures of any depth level.
   | params:
     - `memberClass` Class name of the child member.
     - `memberName` Name of the structure member.
   | note: `MEMBER @ FILETIME <memberName>` is special-cased in ot4xb.ch to embed a FILETIME64 child.
   | see-also: MEMBER POINTER32 LINK, BEGIN STRUCTURE
 }}*/
#xtranslate MEMBER @ FILETIME <m> => ooo:_Child( <(m)> , FILETIME64() )
/*{{ topic: ot4xb_ch_structure_commands | _note_: documented under MEMBER @ }}*/
#xcommand MEMBER @ <cls> <m> => ooo:_Child( <(m)> , <cls>() )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### BEGIN UNION
   | syntax_: `BEGIN UNION`
   | desc_: Members between BEGIN UNION and END UNION start at the same memory address, and the union
     takes the size of the biggest member inside it. Union clauses cannot be nested inside the same
     structure declaration, but a child member inside a union can have unions of its own.
   | example: ```
     BEGIN STRUCTURE <ClassName> [ EXTENDING <SuperClass> ]
     BEGIN UNION
     MEMBER <TYPE> AAA
     MEMBER <TYPE> BBB
     MEMBER <TYPE> CCC
     END UNION
     ...
     END STRUCTURE
     ```
   | see-also: END UNION, GWSTBACK, MEMBER @
 }}*/
#xcommand BEGIN UNION => ooo:_GwstBeginUnion()
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### END UNION
   | syntax_: `END UNION`
   | desc_: Closes a BEGIN UNION group of members.
   | see-also: BEGIN UNION
 }}*/
#xcommand END UNION   => ooo:_GwstEndUnion()
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER DWORDNET
   | syntax_: `MEMBER DWORDNET <memberName>`
   | desc_: At binary level stores a LONG value (4 bytes) in network byte order from / to an Xbase++
     Numeric value in host byte order. To preserve the internal storage as a 32-bit integer, values
     >= 0x80000000 are always represented as negative at Xbase++ level; you can use the function
     Long2Double() to obtain the unsigned representation.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER DWORD, MEMBER WORDNET
 }}*/
#xcommand MEMBER DWORDNET       <m> => ooo:_Member_DWordNet( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER WORDNET
   | syntax_: `MEMBER WORDNET <memberName>`
   | desc_: At binary level stores a WORD value (2 bytes) in network byte order from / to an Xbase++
     Numeric value in host byte order. All values are represented as positive at Xbase++ level; if
     you want to see the negative representation of values >= 0x8000 you can use the function
     ExtendSign16().
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER WORD, MEMBER DWORDNET
 }}*/
#xcommand MEMBER WORDNET        <m> => ooo:_Member_WordNet( <(m)> )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER BOOL
   | syntax_: `MEMBER BOOL <memberName>`
   | desc_: At binary level stores a BOOL value (4 bytes) from / to an Xbase++ Logical value.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER BYTEBOOL
 }}*/
#xcommand MEMBER BOOL           <m> => ooo:_Member_Bool( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER BYTE
   | syntax_: `MEMBER BYTE <memberName>`
   | desc_: At binary level stores a BYTE value from / to an Xbase++ Numeric value. All values are
     represented as positive at Xbase++ level; if you want to see the negative representation of
     values >= 0x80 you can use the function ExtendSign8().
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER U_INT8, MEMBER S_INT8, MEMBER WORD, ExtendSign8
 }}*/
#xcommand MEMBER BYTE           <m> => ooo:_Member_Byte( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER U_INT8
   | syntax_: `MEMBER U_INT8 <memberName>`
   | desc_: A 1-byte unsigned integer member, exactly like MEMBER BYTE: read as a positive Numeric value, 0 to 255.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER BYTE, MEMBER S_INT8 }}*/
#xcommand MEMBER U_INT8         <m> => ooo:_Member_Byte( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER WORD
   | syntax_: `MEMBER WORD <memberName>`
   | desc_: At binary level stores a WORD value (2 bytes) from / to an Xbase++ Numeric value. All
     values are represented as positive at Xbase++ level; if you want to see the negative
     representation of values >= 0x8000 you can use the function ExtendSign16().
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER U_INT16, MEMBER INT16, MEMBER SHORT, MEMBER S_INT16, MEMBER WORDNET, MEMBER DWORD, ExtendSign16
 }}*/
#xcommand MEMBER WORD           <m> => ooo:_Member_Word( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER INT16
   | syntax_: `MEMBER INT16 <memberName>`
   | desc_: A 2-byte unsigned integer member, exactly like MEMBER WORD: read as a positive Numeric value, 0 to
     65535 (use ExtendSign16() or MEMBER S_INT16 for a signed reading).
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER WORD, MEMBER S_INT16 }}*/
#xcommand MEMBER INT16          <m> => ooo:_Member_Int16( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER U_INT16
   | syntax_: `MEMBER U_INT16 <memberName>`
   | desc_: A 2-byte unsigned integer member, exactly like MEMBER WORD: read as a positive Numeric value, 0 to 65535.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER WORD, MEMBER S_INT16 }}*/
#xcommand MEMBER U_INT16        <m> => ooo:_Member_Word( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER SHORT
   | syntax_: `MEMBER SHORT <memberName>`
   | desc_: A 2-byte integer member expanded exactly like MEMBER WORD: at Xbase++ level the value is always
     positive, 0 to 65535; use ExtendSign16() or MEMBER S_INT16 to get the signed representation.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER WORD, MEMBER S_INT16, ExtendSign16 }}*/
#xcommand MEMBER SHORT          <m> => ooo:_Member_Short( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER DWORD
   | syntax_: `MEMBER DWORD <memberName>`
   | desc_: At binary level stores a LONG value (4 bytes) from / to an Xbase++ Numeric value. To
     preserve the internal storage as a 32-bit integer, values >= 0x80000000 are always represented
     as negative at Xbase++ level; you can use the function Long2Double() to obtain the unsigned
     representation.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER ULONG, MEMBER LONG, MEMBER UINT, MEMBER INT, MEMBER INT32, MEMBER S_INT32, MEMBER U_INT32, MEMBER DWORDNET, Long2Double
 }}*/
#xcommand MEMBER DWORD          <m> => ooo:_Member_DWord( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER S_INT32
   | syntax_: `MEMBER S_INT32 <memberName>`
   | desc_: A 4-byte integer member, exactly like MEMBER DWORD: values >= 0x80000000 are represented as negative.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER DWORD }}*/
#xcommand MEMBER S_INT32        <m> => ooo:_Member_DWord( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER ULONG
   | syntax_: `MEMBER ULONG <memberName>`
   | desc_: A 4-byte integer member, exactly like MEMBER DWORD: values >= 0x80000000 are represented as negative;
     use Long2Double() or MEMBER U_INT32 for the unsigned representation.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER DWORD, MEMBER U_INT32, Long2Double }}*/
#xcommand MEMBER ULONG          <m> => ooo:_Member_ULong( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER LONG
   | syntax_: `MEMBER LONG <memberName>`
   | desc_: A 4-byte integer member, exactly like MEMBER DWORD.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER DWORD }}*/
#xcommand MEMBER LONG           <m> => ooo:_Member_Long( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER UINT
   | syntax_: `MEMBER UINT <memberName>`
   | desc_: A 4-byte integer member, exactly like MEMBER DWORD: values >= 0x80000000 are represented as negative;
     use Long2Double() or MEMBER U_INT32 for the unsigned representation.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER DWORD, MEMBER U_INT32 }}*/
#xcommand MEMBER UINT           <m> => ooo:_Member_UInt( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER INT
   | syntax_: `MEMBER INT <memberName>`
   | desc_: A 4-byte integer member, exactly like MEMBER DWORD.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER DWORD }}*/
#xcommand MEMBER INT            <m> => ooo:_Member_Int( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER ENUM
   | syntax_: `MEMBER ENUM <memberName>`
   | desc_: A 4-byte integer member for C enum values, expanded exactly like MEMBER INT.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER INT, MEMBER DWORD }}*/
#xcommand MEMBER ENUM           <m> => ooo:_Member_Int( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER INT32
   | syntax_: `MEMBER INT32 <memberName>`
   | desc_: A 4-byte integer member, exactly like MEMBER DWORD.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER DWORD }}*/
#xcommand MEMBER INT32          <m> => ooo:_Member_Int32( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER LPARAM
   | syntax_: `MEMBER LPARAM <memberName>`
   | desc_: A 4-byte integer member holding a Win32 LPARAM, exactly like MEMBER DWORD.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER DWORD, MEMBER WPARAM }}*/
#xcommand MEMBER LPARAM         <m> => ooo:_Member_LParam( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER WPARAM
   | syntax_: `MEMBER WPARAM <memberName>`
   | desc_: A 4-byte integer member holding a Win32 WPARAM, exactly like MEMBER DWORD.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER DWORD, MEMBER LPARAM }}*/
#xcommand MEMBER WPARAM         <m> => ooo:_Member_WParam( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER POINTER
   | syntax_: `MEMBER POINTER <memberName>`
   | desc_: A 4-byte pointer member (POINTER32 member type in the structure metadata); read and written as a plain
     32-bit Numeric value like MEMBER DWORD.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER POINTER32, MEMBER POINTER32 LINK, MEMBER DWORD }}*/
#xcommand MEMBER POINTER        <m> => ooo:_Member_Pointer( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER POINTER32
   | syntax_: `MEMBER POINTER32 <memberName>`
   | desc_: A 4-byte pointer member, exactly like MEMBER POINTER; the name to use for the LINK clause.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER POINTER, MEMBER POINTER32 LINK }}*/
#xcommand MEMBER POINTER32      <m> => ooo:_Member_Pointer32( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER HANDLE
   | syntax_: `MEMBER HANDLE <memberName>`
   | desc_: A 4-byte Win32 handle member (HANDLE member type in the structure metadata); read and written as a plain
     32-bit Numeric value like MEMBER DWORD.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER HWND, MEMBER HDC, MEMBER DWORD }}*/
#xcommand MEMBER HANDLE         <m> => ooo:_Member_Handle( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER HWND
   | syntax_: `MEMBER HWND <memberName>`
   | desc_: A 4-byte window handle member, registered as a HANDLE member: read and written as a plain 32-bit Numeric
     value, like MEMBER HANDLE.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER HANDLE, MEMBER HDC }}*/
#xcommand MEMBER HWND           <m> => ooo:_Member_HWND( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER HDC
   | syntax_: `MEMBER HDC <memberName>`
   | desc_: A 4-byte device context handle member, registered as a HANDLE member: read and written as a plain 32-bit
     Numeric value, like MEMBER HANDLE.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER HANDLE, MEMBER HWND }}*/
#xcommand MEMBER HDC            <m> => ooo:_Member_HDC( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER PCLIPVAR
   | syntax_: `MEMBER PCLIPVAR <memberName>`
   | desc_: Stores and retrieves an Xbase++ value through an Xbase++ container kept in the structure (4 bytes),
     exactly like MEMBER PXBASEVAR; assign NIL to release the container.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER PXBASEVAR }}*/
#xcommand MEMBER PCLIPVAR       <m> => ooo:_Member_Xbase( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER PXBASEVAR
   | syntax_: `MEMBER PXBASEVAR <memberName>`
   | desc_: Stores and retrieves an Xbase++ value through an Xbase++ container kept in the structure
     (4 bytes). Assigning NIL releases the allocated container. The four names expand identically.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER PCLIPVAR, MEMBER CODEBLOCK, MEMBER LPXBASE, MEMBER DYNSZ
 }}*/
#xcommand MEMBER PXBASEVAR      <m> => ooo:_Member_Xbase( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER CODEBLOCK
   | syntax_: `MEMBER CODEBLOCK <memberName>`
   | desc_: Stores and retrieves an Xbase++ value (a codeblock, typically) through an Xbase++ container kept in the
     structure (4 bytes), exactly like MEMBER PXBASEVAR; assign NIL to release the container.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER PXBASEVAR }}*/
#xcommand MEMBER CODEBLOCK      <m> => ooo:_Member_Xbase( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER LPXBASE
   | syntax_: `MEMBER LPXBASE <memberName>`
   | desc_: Stores and retrieves an Xbase++ value through an Xbase++ container kept in the structure (4 bytes),
     exactly like MEMBER PXBASEVAR; assign NIL to release the container.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER PXBASEVAR }}*/
#xcommand MEMBER LPXBASE        <m> => ooo:_Member_Xbase( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER DWORD64
   | syntax_: `MEMBER DWORD64 <memberName>`
   | desc_: At binary level stores a 64-bit integer value (8 bytes) from / to an Xbase++ Character
     value of 8 bytes. You can also assign an Xbase++ Numeric value.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER N_INT64, MEMBER DOUBLE
 }}*/
#xcommand MEMBER DWORD64        <m> => ooo:_Member_DWord64( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER DOUBLE
   | syntax_: `MEMBER DOUBLE <memberName>`
   | desc_: At binary level stores a 64-bit (8 bytes) floating point value from / to an Xbase++
     Numeric value.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER FLOAT
 }}*/
#xcommand MEMBER DOUBLE         <m> => ooo:_Member_Double( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER FLOAT
   | syntax_: `MEMBER FLOAT <memberName>`
   | desc_: At binary level stores a 32-bit (4 bytes) floating point value from / to an Xbase++
     Numeric value.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER DOUBLE
 }}*/
#xcommand MEMBER FLOAT          <m> => ooo:_Member_Float( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER LPSTR
   | syntax_: `MEMBER LPSTR <memberName>`
   | desc_: A 4-byte pointer member meant to hold the address of a C string. At Xbase++ level the
     member holds the pointer itself as a Numeric value; the pointed text is not touched. Use the
     STRZ_READ / STR_READ_CB / DYNSZ companion clauses to work with the text.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER LPSTR STRZ_READ, MEMBER LPSTR STR_READ_CB, MEMBER LPSTR DYNSZ, MEMBER DYNSZ
 }}*/
#xcommand MEMBER LPSTR          <m> => ooo:_Member_LPSTR( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER DYNSZ
   | syntax_: `MEMBER DYNSZ <memberName>`
   | desc_: Assigning a string allocates a buffer holding it plus a trailing `\0` and stores the
     buffer pointer into the structure (4 bytes). Reading returns the pointed text up to the first
     `\0`. Assigning NIL releases the allocated memory.
   | params:
     - `memberName` Name of the structure member.
   | note: The buffer is not released automatically: assign NIL explicitly when you are done with
     this kind of member, or your application will leak heap memory.
   | see-also: MEMBER LPSTR, MEMBER LPSTR DYNSZ, MEMBER SZSTR, MEMBER PXBASEVAR
 }}*/
#xcommand MEMBER DYNSZ          <m> => ooo:_Member_DYNSZ( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER XDATE
   | syntax_: `MEMBER XDATE <memberName>`
   | desc_: An 8-byte Date member stored as YYYYMMDD text, read and written as an Xbase++ Date value.
   | params:
     - `memberName` Name of the structure member.
 }}*/
#xcommand MEMBER XDATE          <m> => ooo:_Member_XDate( <(m)> )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER S_INT8
   | syntax_: `MEMBER S_INT8 <memberName>`
   | desc_: A 1-byte signed integer member: reading sign extends and returns -128 to 127.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER BYTE, MEMBER U_INT8, ExtendSign8 }}*/
#xcommand MEMBER S_INT8       <m> => ooo:_Member_SINT8( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER S_INT16
   | syntax_: `MEMBER S_INT16 <memberName>`
   | desc_: A 2-byte signed integer member: reading sign extends and returns -32768 to 32767.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER WORD, MEMBER SHORT, ExtendSign16 }}*/
#xcommand MEMBER S_INT16      <m> => ooo:_Member_SINT16( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER U_INT32
   | syntax_: `MEMBER U_INT32 <memberName>`
   | desc_: A 4-byte unsigned integer member: reading never returns a negative value; above 0x7FFFFFFF the member
     comes back as a floating point Numeric value.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER DWORD, MEMBER ULONG }}*/
#xcommand MEMBER U_INT32      <m> => ooo:_Member_UINT32( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER N_INT64
   | syntax_: `MEMBER N_INT64 <memberName>`
   | desc_: An 8-byte signed integer member, read as an 8-byte Character string; a Character, Numeric,
     { nLow, nHigh } Array or an Object supplying its :q member (LARGE_INTEGER, ULARGE_INTEGER) can be assigned.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER DWORD64
 }}*/
#xcommand MEMBER N_INT64      <m> => ooo:_Member_NINT64( <(m)> )
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER BYTEBOOL
   | syntax_: `MEMBER BYTEBOOL <memberName>`
   | desc_: A boolean member stored in a single byte, read and written as an Xbase++ Logical value.
   | params:
     - `memberName` Name of the structure member.
   | see-also: MEMBER BOOL
 }}*/
#xcommand MEMBER BYTEBOOL     <m> => ooo:_Member_ByteBool( <(m)> )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands
   | command_: ### DYNAMIC BITFIELD
   | syntax_: `DYNAMIC BITFIELD <cName> FROM BYTE|WORD|DWORD <member> OFFSET <nBitOffset> BITS <nBits>`
   | desc_: Defines a property exposing a bit field of a numeric member: reading extracts `<nBits>` bits
     starting at bit `<nBitOffset>` of `<member>`; assigning writes the value back into those bits. The
     FROM type is the binary type of `<member>` (BYTE, WORD or DWORD). Defined in ot4xb.ch as a
     #xtranslate over `DYNAMIC PROPERTY ... BLOCK`.
   | params:
     - `cName` Name of the property.
     - `member` Numeric member of the same class holding the bits.
   | see-also: DYNAMIC PROPERTY IS MASK
 }}*/
#xtranslate DYNAMIC BITFIELD <f> FROM BYTE <m> OFFSET <sh> BITS <sz> ;
            =>;
            DYNAMIC PROPERTY <f> BLOCK  {|s,v| iif(PCount() > 1,;
                    s:<m> := @ot4xb:_b1_bf_set_(s:<m>,<sh>,<sz>,v) ,;
                  @ot4xb:_b1_bf_get_(s:<m>,<sh>,<sz>) )}
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC BITFIELD }}*/
#xtranslate DYNAMIC BITFIELD <f> FROM WORD <m> OFFSET <sh> BITS <sz> ;
            =>;
            DYNAMIC PROPERTY <f> BLOCK  {|s,v| iif(PCount() > 1,;
                    s:<m> := @ot4xb:_w_bf_set_(s:<m>,<sh>,<sz>,v) ,;
                  @ot4xb:_w_bf_get_(s:<m>,<sh>,<sz>) )}
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dynamic_class_commands | _note_: documented under DYNAMIC BITFIELD }}*/
#xtranslate DYNAMIC BITFIELD <f> FROM DWORD <m> OFFSET <sh> BITS <sz> ;
            =>;
            DYNAMIC PROPERTY <f> BLOCK  {|s,v| iif(PCount() > 1,;
                    s:<m> := @ot4xb:_dw_bf_set_(s:<m>,<sh>,<sz>,v) ,;
                  @ot4xb:_dw_bf_get_(s:<m>,<sh>,<sz>) )}
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER LPSTR DYNSZ
   | syntax_: `MEMBER LPSTR <memberName> DYNSZ <memberName2>`
   | syntax_: `MEMBER DYNSZ <memberName2> LPSTR <memberName>`
   | desc_: Declares the pointer member `<memberName>` and a DYNSZ member `<memberName2>` overlaid on the
     same 4 bytes (the expansion uses GWSTBACK): assigning a string to `<memberName2>` allocates the
     buffer, and reading `<memberName>` returns its address as a Numeric value. Both clause orders
     expand identically. Assigning NIL to `<memberName2>` releases the buffer (see MEMBER DYNSZ).
   | see-also: MEMBER LPSTR, MEMBER DYNSZ, GWSTBACK
 }}*/
#xcommand MEMBER LPSTR  <m> DYNSZ <m2> => MEMBER LPSTR <m> ;
                                          ; GWSTBACK() ;
                                          ; MEMBER DYNSZ <m2>
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands | _note_: documented under MEMBER LPSTR DYNSZ }}*/
#xcommand MEMBER DYNSZ  <m2> LPSTR <m> => MEMBER LPSTR <m> ;
                                          ; GWSTBACK() ;
                                          ; MEMBER DYNSZ <m2>
// -----------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER LPSTR STRZ_READ
   | syntax_: `MEMBER LPSTR <memberName> STRZ_READ <cPropName>`
   | desc_: Declares the pointer member `<memberName>` plus a read-only property `<cPropName>` returning
     the zero terminated string it points to, or an empty string when the pointer is 0.
   | see-also: MEMBER LPSTR, MEMBER LPSTR STR_READ_CB
 }}*/
#xcommand MEMBER LPSTR  <m> STRZ_READ <m2> => ;
                 MEMBER LPSTR <m> ;
                 ;DYNAMIC  READONLY PROPERTY <m2> BLOCK \{|s| iif( s:<m> == 0,"",PeekStr(s:<m>,0,-1))\}
// -----------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER LPSTR STR_READ_CB
   | syntax_: `MEMBER LPSTR <memberName> STR_READ_CB <cPropName> CBFROM <sizeMember>`
   | desc_: Declares the pointer member `<memberName>` plus a read-only property `<cPropName>` returning
     the text it points to, reading exactly the number of bytes held by member `<sizeMember>` (an empty
     string when the pointer is 0).
   | see-also: MEMBER LPSTR, MEMBER LPSTR STRZ_READ
 }}*/
#xcommand MEMBER LPSTR  <m> STR_READ_CB <m2> CBFROM <ms> => ;
                 MEMBER LPSTR <m> ;
                 ;DYNAMIC  READONLY PROPERTY <m2> BLOCK \{|s| iif( s:<m> == 0,"",PeekStr(s:<m>,0,s:<ms>))\}
// -----------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER POINTER32 LINK
   | syntax_: `MEMBER POINTER32 <memberName> LINK <cPropName> [ CLASS <StructClass> ]`
   | desc_: Declares the pointer member `<memberName>` plus a read-only property `<cPropName>` returning a
     new instance of structure class `<StructClass>` linked (`:_link_()`) to the address held in
     `<memberName>`, or NIL when the pointer is 0. Without the CLASS clause the instance is of the same
     class as the containing structure.
   | see-also: MEMBER LPSTR, MEMBER @
 }}*/
#xcommand MEMBER POINTER32 <m> LINK <m2> CLASS <cc> => ;
                 MEMBER POINTER32 <m> ;
                 ;DYNAMIC  READONLY PROPERTY <m2> BLOCK {|s| iif( s:<m> == 0,NIL,<cc>():New():_link_(s:<m>,.F.))}
// -----------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands | _note_: documented under MEMBER POINTER32 LINK }}*/
#xcommand MEMBER POINTER32 <m> LINK <m2> => ;
                 MEMBER POINTER32 <m> ;
                 ;DYNAMIC  READONLY PROPERTY <m2> BLOCK {|s| iif( s:<m> == 0,NIL,s:ClassObject():New():_link_(s:<m>,.F.))}
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER BINSTR
   | syntax_: `MEMBER BINSTR <memberName> SIZE <nSize>`
   | desc_: Stores a binary string of up to `<nSize>` characters: a longer value is truncated, a shorter
     one is padded with `\0`. Reading returns a string of exactly `<nSize>` characters.
   | params:
     - `memberName` Name of the structure member.
     - `nSize` Size reserved in the structure, in bytes.
   | see-also: MEMBER SZSTR, MEMBER DYNSZ
 }}*/
#xcommand MEMBER BINSTR  <m>  SIZE <n> => ooo:_Member_BINSTR( <(m)> , <n>)
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER SZSTR
   | syntax_: `MEMBER SZSTR <memberName> SIZE <nSize>`
   | desc_: Stores a zero terminated string of up to `<nSize>` characters including the trailing `\0`.
     Reading returns the text up to the first `\0` character.
   | params:
     - `memberName` Name of the structure member.
     - `nSize` Size reserved in the structure, in bytes.
   | see-also: MEMBER BINSTR, MEMBER SZWSTR, MEMBER DYNSZ
 }}*/
#xcommand MEMBER SZSTR   <m>  SIZE <n> => ooo:_Member_SZSTR( <(m)> , <n>)
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER SZWSTR
   | syntax_: `MEMBER SZWSTR <memberName> SIZE <nSize>`
   | desc_: A zero terminated wide (UTF-16) string member holding up to `<nSize>` wide characters: `<nSize>` * 2 bytes are
     reserved in the structure, the terminator included; reading returns the text up to the first zero
     character, converted to ANSI.
   | desc_: Like MEMBER SZSTR but the member holds a zero terminated wide string.
   | params:
     - `memberName` Name of the structure member.
     - `nSize` Size reserved in the structure.
   | see-also: MEMBER SZSTR
 }}*/
#xcommand MEMBER SZWSTR  <m>  SIZE <n> => ooo:_Member_SZWSTR( <(m)> , <n>)
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands
   | command_: ### DELEGATE METHOD WITH PARAMLIST
   | syntax_: `DELEGATE <oVar> METHOD <cMethod> WITH PARAMLIST`
   | desc_: Inside a CLASS declaration: defines the method `<cMethod>` as a forwarder to the same method of the object held
     in the instance variable `<oVar>`, passing along whatever parameters it received (any number; they are
     collected with PValue(), sent with {{ilink: <function lCallMethodPA> lCallMethodPA}} and written back, so
     by-reference parameters work) and returning its result.
   | params:
     - `oVar` Instance variable holding the object the call is delegated to.
     - `cMethod` Method name, the same on both sides.
   | _kw_: commands, ot4xb.ch, DELEGATE, TLS CLASS VAR, PROPERTY IS MASK, class helpers
   | see-also: DELEGATE METHOD, DELEGATE VAR }}*/
#xcommand DELEGATE <v> METHOD <cm> WITH PARAMLIST;
          =>;
          INLINE METHOD <cm>() ;
          ; local n;
          ; local np := PCount();
          ; local ap := Array(np);
          ; local xr := NIL;
          ; for n := 1 to np ;
          ;    ap\[n\] := PValue(n);
          ; next;
          ; if lCallMethodPA(::<v>,<(cm)>,ap,@xr);
          ;    for n := 1 to np ;
          ;       PValue(n,ap\[n\]) ;
          ;    next ;
          ; end;
          ; return xr
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands
   | command_: ### DELEGATE METHOD
   | syntax_: `DELEGATE <oVar> METHOD <cMethod>( [<p1>] [, <pN>] )`
   | desc_: Inside a CLASS declaration: defines the method `<cMethod>`( p1, ..., pN ) as `return ::<oVar>:<cMethod>( @p1, ..., @pN )`,
     the declared parameters forwarded by reference to the same method of the object in `<oVar>`.
   | params:
     - `oVar` Instance variable holding the object the call is delegated to.
     - `cMethod` Method name, the same on both sides.
     - `p1` The parameters of the method.
   | see-also: DELEGATE METHOD WITH PARAMLIST, DELEGATE VAR }}*/
#xcommand DELEGATE <v> METHOD <cm>( [<p1>] [,<pn>] );
          =>;
          INLINE METHOD <cm>( [<p1>] [,<pn>] ) ;
          ; return ::<v>:<cm>( [@<p1>] [,@<pn>] )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands
   | command_: ### DELEGATE VAR
   | syntax_: `DELEGATE <oVar> [CLASS] VAR <cName> [READONLY]`
   | syntax_: `DELEGATE [CLASS] VAR <cName> TO <expression> [READONLY]`
   | desc_: Inside a CLASS declaration: exposes as the (class) variable `<cName>` - an INLINE ACCESS ASSIGN method, or
     ACCESS only with READONLY - either the variable of the same name of the object held in `<oVar>`
     (`::<oVar>:<cName>`), or any `<expression>`: reading returns it, assigning stores into it.
   | params:
     - `oVar` Instance variable holding the object whose variable is exposed.
     - `cName` Name of the exposed variable.
     - `expression` Any assignable expression, with TO.
   | see-also: DELEGATE METHOD, PROPERTY IS MASK }}*/
#xcommand DELEGATE <v> VAR <cm>
          =>;
          INLINE ACCESS ASSIGN METHOD <cm>(v) ;
          ; if( PCount() > 0);
          ;    return ::<v>:<cm> := v ;
          ; end;
          ; return ::<v>:<cm>
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands | _note_: documented under DELEGATE VAR }}*/
#xcommand DELEGATE VAR <cm> TO <exp>
          =>;
          INLINE ACCESS ASSIGN METHOD <cm>(v) ;
          ; if( PCount() > 0);
          ;    return <exp>  := v ;
          ; end;
          ; return <exp>

//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands | _note_: documented under DELEGATE VAR }}*/
#xcommand DELEGATE <v> CLASS VAR <cm>
          =>;
          INLINE ACCESS ASSIGN CLASS METHOD <cm>(v) ;
          ; if( PCount() > 0);
          ;    return ::<v>:<cm> := v ;
          ; end;
          ; return ::<v>:<cm>
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands | _note_: documented under DELEGATE VAR }}*/
#xcommand DELEGATE CLASS VAR <cm> TO <exp>
          =>;
          INLINE ACCESS ASSIGN CLASS METHOD <cm>(v) ;
          ; if( PCount() > 0);
          ;    return <exp>  := v ;
          ; end;
          ; return <exp>

//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands | _note_: documented under DELEGATE VAR }}*/
#xcommand DELEGATE <v> VAR <cm> READONLY
          =>;
          INLINE ACCESS METHOD <cm>() ;
          ; return ::<v>:<cm>
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands | _note_: documented under DELEGATE VAR }}*/
#xcommand DELEGATE <v> CLASS VAR <cm> READONLY
          =>;
          INLINE ACCESS CLASS METHOD <cm>() ;
          ; return ::<v>:<cm>
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands | _note_: documented under DELEGATE VAR }}*/
#xcommand DELEGATE <v> VAR <cm> TO <exp> READONLY
          =>;
          INLINE ACCESS METHOD <cm>() ;
          ; return <exp>
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands | _note_: documented under DELEGATE VAR }}*/
#xcommand DELEGATE <v> CLASS VAR <cm> TO <exp>  READONLY
          =>;
          INLINE ACCESS CLASS METHOD <cm>() ;
          ; return <exp>
//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands
   | command_: ### TLS CLASS VAR
   | syntax_: `TLS CLASS <ClassName> VAR <cName>`
   | desc_: Inside a CLASS declaration: a class variable with one value per thread. It is an INLINE ACCESS ASSIGN CLASS
     METHOD storing the value in the thread's TLS dictionary under the key `<ClassName>::<cName>`
     ({{ilink: <function _hdict_setprop> _hdict_setprop}} / {{ilink: <function _hdict_getprop> _hdict_getprop}} on
     `Tls():_get_ht_handle_()`); reading in a thread that never assigned it gives NIL.
   | params:
     - `ClassName` The class, part of the key.
     - `cName` Name of the class variable.
   | see-also: DELEGATE VAR }}*/
#xcommand TLS CLASS <cls> VAR <m> => ;
          INLINE ACCESS ASSIGN CLASS METHOD <m>(v) ;
          ; local ht := Tls():_get_ht_handle_() ;
          ; local k  := <(cls)> + "::" + <(m)> ;
          ; if PCount() > 0 ;
          ;    _hdict_setprop(ht,k,v) ;
          ;    return NIL;
          ; end ;
          ; return _hdict_getprop(ht,k)
//----------------------------------------------------------------------------------------------------------------------
#define MAKEINTRESOURCE(n)    ( nAnd(n,0xFFFF) )
#define MAKEINTATOM(n)        ( nAnd(n,0xFFFF) )
//----------------------------------------------------------------------------------------------------------------------
#ifndef _OT4XB_EXCLUDE_WINAPI_CONSTANTS
//----------------------------------------------------------------------------------------------------------------------
// Constants for nGetDriveType()
#ifndef ___GETDRIVETYPE___
#define ___GETDRIVETYPE___
#define DRIVE_UNKNOWN     0
#define DRIVE_NO_ROOT_DIR 1
#define DRIVE_REMOVABLE   2
#define DRIVE_FIXED       3
#define DRIVE_REMOTE      4
#define DRIVE_CDROM       5
#define DRIVE_RAMDISK     6
#endif
//----------------------------------------------------------------------------------------------------------------------
#define CREATE_NEW                                1
#define CREATE_ALWAYS                             2
#define OPEN_EXISTING                             3
#define OPEN_ALWAYS                               4
#define TRUNCATE_EXISTING                         5
// ---------------------------------------------------------------------------
#define FILE_SHARE_READ                     0x00000001
#define FILE_SHARE_WRITE                    0x00000002
#define FILE_SHARE_DELETE                   0x00000004
#define FILE_ATTRIBUTE_READONLY             0x00000001
#define FILE_ATTRIBUTE_HIDDEN               0x00000002
#define FILE_ATTRIBUTE_SYSTEM               0x00000004
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020
#define FILE_ATTRIBUTE_DEVICE               0x00000040
#define FILE_ATTRIBUTE_NORMAL               0x00000080
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800
#define FILE_ATTRIBUTE_OFFLINE              0x00001000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000
#define FILE_ATTRIBUTE_ENCRYPTED            0x00004000
#define FILE_NOTIFY_CHANGE_FILE_NAME        0x00000001
#define FILE_NOTIFY_CHANGE_DIR_NAME         0x00000002
#define FILE_NOTIFY_CHANGE_ATTRIBUTES       0x00000004
#define FILE_NOTIFY_CHANGE_SIZE             0x00000008
#define FILE_NOTIFY_CHANGE_LAST_WRITE       0x00000010
#define FILE_NOTIFY_CHANGE_LAST_ACCESS      0x00000020
#define FILE_NOTIFY_CHANGE_CREATION         0x00000040
#define FILE_NOTIFY_CHANGE_SECURITY         0x00000100
#define FILE_ACTION_ADDED                   0x00000001
#define FILE_ACTION_REMOVED                 0x00000002
#define FILE_ACTION_MODIFIED                0x00000003
#define FILE_ACTION_RENAMED_OLD_NAME        0x00000004
#define FILE_ACTION_RENAMED_NEW_NAME        0x00000005
#define MAILSLOT_NO_MESSAGE                 dwminus(1)
#define MAILSLOT_WAIT_FOREVER               dwminus(1)
#define FILE_CASE_SENSITIVE_SEARCH          0x00000001
#define FILE_CASE_PRESERVED_NAMES           0x00000002
#define FILE_UNICODE_ON_DISK                0x00000004
#define FILE_PERSISTENT_ACLS                0x00000008
#define FILE_FILE_COMPRESSION               0x00000010
#define FILE_VOLUME_QUOTAS                  0x00000020
#define FILE_SUPPORTS_SPARSE_FILES          0x00000040
#define FILE_SUPPORTS_REPARSE_POINTS        0x00000080
#define FILE_SUPPORTS_REMOTE_STORAGE        0x00000100
#define FILE_VOLUME_IS_COMPRESSED           0x00008000
#define FILE_SUPPORTS_OBJECT_IDS            0x00010000
#define FILE_SUPPORTS_ENCRYPTION            0x00020000
#define FILE_NAMED_STREAMS                  0x00040000
#define FILE_READ_ONLY_VOLUME               0x00080000
// ---------------------------------------------------------------------------

#define FILE_READ_DATA            ( 0x0001 )    // file & pipe
#define FILE_LIST_DIRECTORY       ( 0x0001 )    // directory
#define FILE_WRITE_DATA           ( 0x0002 )    // file & pipe
#define FILE_ADD_FILE             ( 0x0002 )    // directory
#define FILE_APPEND_DATA          ( 0x0004 )    // file
#define FILE_ADD_SUBDIRECTORY     ( 0x0004 )    // directory
#define FILE_CREATE_PIPE_INSTANCE ( 0x0004 )    // named pipe
#define FILE_READ_EA              ( 0x0008 )    // file & directory
#define FILE_WRITE_EA             ( 0x0010 )    // file & directory
#define FILE_EXECUTE              ( 0x0020 )    // file
#define FILE_TRAVERSE             ( 0x0020 )    // directory
#define FILE_DELETE_CHILD         ( 0x0040 )    // directory
#define FILE_READ_ATTRIBUTES      ( 0x0080 )    // all
#define FILE_WRITE_ATTRIBUTES     ( 0x0100 )    // all
// ---------------------------------------------------------------------------
#define WinNT_h_DELETE         (0x010000)
#define WinNT_h_READ_CONTROL   (0x020000)
#define WinNT_h_WRITE_DAC      (0x040000)
#define WinNT_h_WRITE_OWNER    (0x080000)
#define WinNT_h_SYNCHRONIZE    (0x100000)
// ---------------------------------------------------------------------------
#ifndef STANDARD_RIGHTS_READ
#define STANDARD_RIGHTS_READ             WinNT_h_READ_CONTROL
#define STANDARD_RIGHTS_WRITE            WinNT_h_READ_CONTROL
#define STANDARD_RIGHTS_EXECUTE          WinNT_h_READ_CONTROL
#define STANDARD_RIGHTS_REQUIRED         dwfix(0x000F,0x0000)
#define STANDARD_RIGHTS_ALL              dwfix(0x001F,0x0000)
#define SPECIFIC_RIGHTS_ALL              dwfix(0x0000,0xFFFF)
#define ACCESS_SYSTEM_SECURITY           dwfix(0x0100,0x0000)
#define MAXIMUM_ALLOWED                  dwfix(0x0200,0x0000)
#endif
#ifndef GENERIC_READ
#define GENERIC_READ                     dwfix(0x8000,0x0000)
#define GENERIC_WRITE                    dwfix(0x4000,0x0000)
#define GENERIC_EXECUTE                  dwfix(0x2000,0x0000)
#define GENERIC_ALL                      dwfix(0x1000,0x0000)
#endif
// ------------
#define FILE_ALL_ACCESS      nOr(STANDARD_RIGHTS_REQUIRED , WinNT_h_SYNCHRONIZE , 0x1FF)
#define FILE_GENERIC_READ    nOr(STANDARD_RIGHTS_READ,FILE_READ_DATA,FILE_READ_ATTRIBUTES,FILE_READ_EA,WinNT_h_SYNCHRONIZE)
#define FILE_GENERIC_WRITE   nOr(STANDARD_RIGHTS_WRITE,FILE_WRITE_DATA,FILE_WRITE_ATTRIBUTES,FILE_WRITE_EA,FILE_APPEND_DATA,WinNT_h_SYNCHRONIZE)
#define FILE_GENERIC_EXECUTE nOr(STANDARD_RIGHTS_EXECUTE,FILE_READ_ATTRIBUTES,FILE_EXECUTE,WinNT_h_SYNCHRONIZE)
// ---------------------------------------------------------------------------
#ifndef HKEY_CLASSES_ROOT
#define HKEY_CLASSES_ROOT           dwfix(0x8000,0x0000)
#define HKEY_CURRENT_USER           dwfix(0x8000,0x0001)
#define HKEY_LOCAL_MACHINE          dwfix(0x8000,0x0002)
#define HKEY_USERS                  dwfix(0x8000,0x0003)
#define HKEY_PERFORMANCE_DATA       dwfix(0x8000,0x0004)
#define HKEY_PERFORMANCE_TEXT       dwfix(0x8000,0x0050)
#define HKEY_PERFORMANCE_NLSTEXT    dwfix(0x8000,0x0060)
#define HKEY_CURRENT_CONFIG         dwfix(0x8000,0x0005)
#define HKEY_DYN_DATA               dwfix(0x8000,0x0006)
#endif
// ---------------------------------------------------------------------------
#endif // _OT4XB_EXCLUDE_WINAPI_CONSTANTS
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands
   | _slug_: class-helper-commands
   | category: commands , ot4xb.ch
   | desc: Helpers for classes declared with the Xbase++ CLASS syntax (not dynamic classes): PROPERTY ... IS MASK and
     IS CONSTANT expand to INLINE ACCESS / ASSIGN methods over a bit mask of a variable or a constant value,
     with CLASS PROPERTY variants for class-level methods. Defined in ot4xb.ch. }}*/
/*{{ topic: ot4xb_ch_class_helper_commands
   | command_: ### PROPERTY IS MASK
   | syntax_: `[CLASS] PROPERTY <cName> IS MASK <nMask> OF <var> [ READONLY ]`
   | desc_: Creates an ACCESS / ASSIGN member of a CLASS or STRUCTURE that allows setting / getting
     flags of a numeric member through a Logical value: reading returns `lAnd( ::<var>, <nMask> )`;
     assigning .T. sets the mask bits with nOr(), assigning .F. clears them with nAndNot(). With
     READONLY only the ACCESS side is generated, and the CLASS form generates a class method working
     on a class variable. It expands to the declarative `INLINE ACCESS [ASSIGN] METHOD` syntax;
     inside a dynamic class or structure definition use DYNAMIC PROPERTY IS MASK instead.
   | params:
     - `cName` Name of the property.
     - `nMask` Integer constant containing the bits to set or get.
     - `var` Numeric member of the same STRUCTURE or CLASS acting as a container for the flags.
   | see-also: PROPERTY IS CONSTANT, DYNAMIC PROPERTY IS MASK
 }}*/
#xcommand PROPERTY <name>  IS MASK <mask> OF <var> => ;
          INLINE ACCESS ASSIGN METHOD <name>(bOnOff) ;
          ; if( PCount() > 0 ) ;
          ;   if( bOnOff ) ;
          ;      ::<var> := nOr( ::<var> , <mask> ) ;
          ;   else ;
          ;      ::<var> := nAndNot( ::<var> , <mask> )  ;
          ;   end ;
          ;   return bOnOff ;
          ;end ;
          ;return lAnd( ::<var> , <mask> )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands | _note_: documented under PROPERTY IS MASK }}*/
#xcommand PROPERTY <name>  IS MASK <mask> OF <var> READONLY => ;
          INLINE ACCESS METHOD <name>() ;
          ;return lAnd( ::<var> , <mask> )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands
   | command_: ### PROPERTY IS CONSTANT
   | syntax_: `[CLASS] PROPERTY <cName> IS CONSTANT <uVal>`
   | desc_: Creates an ACCESS member of a CLASS or STRUCTURE returning a fixed value. It expands to
     the declarative `INLINE ACCESS METHOD` syntax; inside a dynamic class or structure definition
     use DYNAMIC PROPERTY IS CONSTANT instead.
   | params:
     - `cName` Name of the constant.
     - `uVal` Value of the constant.
   | see-also: PROPERTY IS MASK, DYNAMIC PROPERTY IS CONSTANT
 }}*/
#xcommand PROPERTY <name>  IS CONSTANT <val> => ;
          INLINE ACCESS METHOD <name>() ;
          ; return <val>
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands | _note_: documented under PROPERTY IS MASK }}*/
#xcommand CLASS PROPERTY <name>  IS MASK <mask> OF <var> => ;
          INLINE ACCESS ASSIGN CLASS METHOD <name>(bOnOff) ;
          ; if( PCount() > 0 ) ;
          ;   if( bOnOff ) ;
          ;      ::<var> := nOr( ::<var> , <mask> ) ;
          ;   else ;
          ;      ::<var> := nAndNot( ::<var> , <mask> )  ;
          ;   end ;
          ;   return bOnOff ;
          ;end ;
          ;return lAnd( ::<var> , <mask> )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands | _note_: documented under PROPERTY IS MASK }}*/
#xcommand CLASS PROPERTY <name>  IS MASK <mask> OF <var> READONLY => ;
          INLINE ACCESS CLASS METHOD <name>() ;
          ;return lAnd( ::<var> , <mask> )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands | _note_: documented under PROPERTY IS CONSTANT }}*/
#xcommand CLASS PROPERTY <name>  IS CONSTANT <val> => ;
          INLINE ACCESS CLASS METHOD <name>() ;
          ; return <val>
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands |: ## Variable-length structures }}*/
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### BEGIN VARLEN STRUCTURE
   | syntax_: `BEGIN VARLEN STRUCTURE <ClassName>`
   | desc_: Opens a variable-length structure: a structure whose fixed binary part (defined with the
     ordinary MEMBER commands) is followed by variable-length members declared with VARLEN EXTRA
     MEMBER. It expands to BEGIN STRUCTURE plus the work locals used to compose the access members
     generated by END VARLEN STRUCTURE.
   | params:
     - `ClassName` Name of the structure class being defined.
   | see-also: VARLEN EXTRA MEMBER, END VARLEN STRUCTURE, BEGIN STRUCTURE
 }}*/
#xcommand BEGIN VARLEN STRUCTURE   <cn> => ;
          BEGIN STRUCTURE <cn> local _cgb_ , _cpb_ , _cfr_,_vls_;
          ; _cgb_ := "{|s|s:_read_() " ;
          ; _cpb_ := "{|s,v,nn| nn := %u,s:_write_(v,0,nn)," ;
          ; _cfr_ := "{|s,h,nn| s:_zeromemory_(),nn := FRead(h, @s:_m__pt_ , s:_sizeof_() ),"  ;
          ; _vls_ := "{|s| s:_sizeof_()"


/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### END VARLEN STRUCTURE
   | syntax_: `END VARLEN STRUCTURE`
   | desc_: Closes a variable-length structure and generates its access members: method :Get() returns
     the whole packed value (the fixed part followed by every extra member), :Put( cBuffer ) loads
     such a value back, :FRead( nHandle ) and :FWrite( nHandle ) read / write it from / to an open
     file, and the read-only property :_vl_size_ returns the total packed size. It ends with
     END STRUCTURE.
   | see-also: BEGIN VARLEN STRUCTURE, VARLEN EXTRA MEMBER
 }}*/
#xcommand END VARLEN STRUCTURE => ;
            _cgb_ += "}" ;
          ; _cpb_ += "s}" ;
          ; _cfr_ += "nn}" ;
          ; _vls_ += "}" ;
          ; DYNAMIC METHOD Get COMPILE ( _cgb_ ) ;
          ; DYNAMIC METHOD Put COMPILE ( _cpb_ ) INSERT GwstGetOffset() ;
          ; DYNAMIC METHOD FWrite BLOCK {|s,h| FWrite(h, s:Get())};
          ; DYNAMIC METHOD FRead  COMPILE ( _cfr_ ) ;
          ; DYNAMIC READONLY PROPERTY _vl_size_ COMPILE ( _vls_ ) ;
          ; END STRUCTURE

/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### VARLEN EXTRA MEMBER
   | syntax_: `VARLEN EXTRA MEMBER <cName> SIZE TO <sizeMember>`
   | desc_: Declares the variable-length member `<cName>`, stored after the fixed part of the structure;
     assigning a string to it also stores its length into the fixed member `<sizeMember>`. Internally
     it is a DYNAMIC VAR __`<cName>` exposed through a DYNAMIC PROPERTY `<cName>`.
   | params:
     - `cName` Name of the variable-length member.
     - `sizeMember` Numeric member of the fixed part keeping the current length of `<cName>`.
   | see-also: BEGIN VARLEN STRUCTURE, END VARLEN STRUCTURE
 }}*/
#xcommand VARLEN EXTRA MEMBER <cc> SIZE TO <sz> =>  ;
            DYNAMIC  VAR   __<cc> ;
          ; DYNAMIC  PROPERTY <cc> ;
                     READ iif(::__<cc> == NIL,"", ::__<cc>) ;
                     WRITE ( ::<sz> := Len(v) , ::__<cc> := v ) ;
          ; _cgb_ += cPrintf(" + s:%s",<(cc)>) ;
          ; _cpb_ += cPrintf("s:__%s := PeekStr(@v,@nn,s:%s ),", <(cc)> , <(sz)>) ;
          ; _cfr_ += cPrintf("s:__%s := ChrR(0,s:%s),FRead(h,@s:__%s,s:%s),",<(cc)>,<(sz)>,<(cc)>,<(sz)>) ;
          ; _vls_ += cPrintf(" + s:%s ",<(sz)>) ;
// -----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_class_helper_commands
   | command_: ### CLASS COMBINE XBP CLASS AND C++ CLASS
   | syntax_: `CLASS <NewClass> COMBINE XBP CLASS <XbpClass> AND C++ CLASS <CppClass>`
   | desc_: Declares `CLASS <NewClass> FROM <XbpClass>, <CppClass>` with `init`, `Create` and `Configure` methods that
     forward up to six parameters to the Xbp class and call the hooks of the C++-backed class around them:
     `::_after_xbase_init_()`, `::_after_xbase_create_()`, `::_before_xbase_configure_()` and
     `::_after_xbase_configure_()`. Write your own methods after it; the command emits the class header and
     the three methods, `EXPORTED:` included.
   | params:
     - `NewClass` Name of the class being declared.
     - `XbpClass` The Xbase++ GUI class to derive from (XbpDialog, XbpStatic, ...).
     - `CppClass` The ot4xb class that wraps the C++ side and provides the hooks. }}*/
#xcommand CLASS <cls> COMBINE XBP CLASS <xbp> AND C\+\+ CLASS  <cpp>  =>;
METHOD <cls>:init(p1,p2,p3,p4,p5,p6)     ;
;::<xbp>:init(p1,p2,p3,p4,p5,p6)          ;
;::_after_xbase_init_()                   ;
;return Self                              ;
;METHOD <cls>:Create(p1,p2,p3,p4,p5,p6)   ;
;::<xbp>:Create(p1,p2,p3,p4,p5,p6)        ;
;::_after_xbase_create_()                 ;
;return Self                              ;
;METHOD <cls>:Configure(p1,p2,p3,p4,p5,p6);
;::_before_xbase_configure_()             ;
;::<xbp>:Configure(p1,p2,p3,p4,p5,p6)     ;
;::_after_xbase_configure_()              ;
;return Self                              ;
;CLASS <cls> FROM <xbp> , <cpp>           ;
;EXPORTED:                                ;
;INLINE CLASS METHOD initclass            ;
;return Self                              ;
;METHOD init                              ;
;METHOD Create                            ;
;METHOD Configure
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------

#ifndef OT4XB_LEAN_AND_MEAN
//-----------------------------------------------------------------------------------------------------------------------

/*{{ note-id: as-qtype-aliases | title_: The AS `<type>` aliases of QTYPE codes (ot4xb.ch)
   |: In QTEMPLATE and DLL ... IMPORT declarations a parameter or return type is written `AS <type>`; each name
     is a pseudo-constant of ot4xb.ch expanding to the Qualified-call type code (QTYPE) it stands for:
     {{begin-md}}
     | AS name | QTYPE code |
     |---|---|
     | `AS VOID` | `__vo` |
     | `AS PXBASEVAR` | `__xb` |
     | `AS BOOL` | `__bo` |
     | `AS INT8` | `__sc` |
     | `AS CHAR` | same as AS INT8 |
     | `AS BYTE` | `__uc` |
     | `AS INT16` | `__ss` |
     | `AS SHORT` | same as AS INT16 |
     | `AS WORD` | `__us` |
     | `AS INT32` | `__sl` |
     | `AS INT` | same as AS INT32 |
     | `AS LONG` | same as AS INT32 |
     | `AS HANDLE` | same as AS INT32 |
     | `AS DWORD` | `__ul` |
     | `AS ULONG` | same as AS DWORD |
     | `AS UINT` | same as AS DWORD |
     | `AS INT64` | `__sq` |
     | `AS QWORD` | `__uq` |
     | `AS FLOAT` | `__f4` |
     | `AS DOUBLE` | `__f8` |
     | `AS POINTER` | `__pt` |
     | `AS PSL_OR_PT` | `?@sl` |
     | `AS POINTER32` | same as AS POINTER |
     | `AS LPSTR` | same as AS POINTER |
     | `AS LPBYTE` | same as AS POINTER |
     | `AS LPVOID` | same as AS POINTER |
     | `AS LPBOOL` | `_@bo` |
     | `AS LPINT8` | `_@sc` |
     | `AS LPCHAR` | same as AS LPINT8 |
     | `AS LPUINT8` | `_@uc` |
     | `AS LPINT16` | `_@ss` |
     | `AS LPSHORT` | same as AS LPINT16 |
     | `AS LPWORD` | `_@us` |
     | `AS LPINT32` | `_@sl` |
     | `AS LPLONG` | same as AS LPINT32 |
     | `AS LPDWORD` | `_@ul` |
     | `AS LPINT64` | `_@sq` |
     | `AS LPQWORD` | `_@uq` |
     | `AS LPFLOAT` | `_@f4` |
     | `AS LPDOUBLE` | `_@f8` |
     | `AS STR2WIDE` | `c_sw` |
     | `AS STR2WIDE_W` | `c@sw` |
     | `AS ZSTRING` | `c_sz` |
     | `AS HWND` | `__hw` |
     | `AS VARIANT` | `__vt` |
     | `AS WPARAM` | same as AS LONG |
     | `AS LPARAM` | same as AS LONG |
     | `AS LRESULT` | same as AS LONG |
     {{end-md}} }}*/
#xtranslate AS VOID                    => AS QTYPE "__vo"
#xtranslate AS PXBASEVAR               => AS QTYPE "__xb"
#xtranslate AS BOOL                    => AS QTYPE "__bo"
#xtranslate AS INT8                    => AS QTYPE "__sc"
#xtranslate AS CHAR                    => AS INT8
#xtranslate AS BYTE                    => AS QTYPE "__uc"
#xtranslate AS INT16                   => AS QTYPE "__ss"
#xtranslate AS SHORT                   => AS INT16
#xtranslate AS WORD                    => AS QTYPE "__us"
#xtranslate AS INT32                   => AS QTYPE "__sl"
#xtranslate AS INT                     => AS INT32
#xtranslate AS LONG                    => AS INT32
#xtranslate AS HANDLE                  => AS INT32
#xtranslate AS DWORD                   => AS QTYPE "__ul"
#xtranslate AS ULONG                   => AS DWORD
#xtranslate AS UINT                    => AS DWORD
#xtranslate AS INT64                   => AS QTYPE "__sq"
#xtranslate AS QWORD                   => AS QTYPE "__uq"
#xtranslate AS FLOAT                   => AS QTYPE "__f4"
#xtranslate AS DOUBLE                  => AS QTYPE "__f8"
#xtranslate AS POINTER                 => AS QTYPE "__pt"
#xtranslate AS PSL_OR_PT               => AS QTYPE "?@sl"
#xtranslate AS POINTER32               => AS POINTER
#xtranslate AS LPSTR                   => AS POINTER
#xtranslate AS LPBYTE                  => AS POINTER
#xtranslate AS LPVOID                  => AS POINTER
#xtranslate AS LPBOOL                  => AS QTYPE "_@bo"
#xtranslate AS LPINT8                  => AS QTYPE "_@sc"
#xtranslate AS LPCHAR                  => AS LPINT8
#xtranslate AS LPUINT8                 => AS QTYPE "_@uc"
#xtranslate AS LPINT16                 => AS QTYPE "_@ss"
#xtranslate AS LPSHORT                 => AS LPINT16
#xtranslate AS LPWORD                  => AS QTYPE "_@us"
#xtranslate AS LPINT32                 => AS QTYPE "_@sl"
#xtranslate AS LPLONG                  => AS LPINT32
#xtranslate AS LPDWORD                 => AS QTYPE "_@ul"
#xtranslate AS LPINT64                 => AS QTYPE "_@sq"
#xtranslate AS LPQWORD                 => AS QTYPE "_@uq"
#xtranslate AS LPFLOAT                 => AS QTYPE "_@f4"
#xtranslate AS LPDOUBLE                => AS QTYPE "_@f8"
#xtranslate AS STR2WIDE                => AS QTYPE "c_sw"
#xtranslate AS STR2WIDE_W              => AS QTYPE "c@sw"
#xtranslate AS ZSTRING                 => AS QTYPE "c_sz"
#xtranslate AS HWND                    => AS QTYPE "__hw"
#xtranslate AS VARIANT                 => AS QTYPE "__vt"
//----------------------------------------------------------------------------------------------------------------------
#xtranslate AS WPARAM  => AS LONG
#xtranslate AS LPARAM  => AS LONG
#xtranslate AS LRESULT => AS LONG
//-----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands
   | _slug_: dll-function-commands
   | category: commands , ot4xb.ch , function-pointer
   | desc: Commands that generate an Xbase++ function wrapping a call to a DLL export - the ot4xb counterpart of
     Alaska's DLLFUNCTION: the export is resolved with {{ilink: <function nGetProcAddress> nGetProcAddress}} and
     called through {{ilink: <function FpQCall> FpQCall}} with a Qualified-call type template (QTYPE) built from
     the `AS <type>` of the return value and of each parameter.
   |: They work, but they never mattered much: for the simple cases they cover there are lighter preprocessor
     forms - `@dll:function( params )` with the types inferred from the values, `@dll:[prototype]:function( params )`
     with an explicit QTYPE prototype, or a plain `#xtranslate` over one of them, for example
     `#xtranslate Rm.EndSession( <h> ) => @rstrtmgr:["__sl__sl"]:RmEndSession( <h> )`; the advantage of the
     preprocessor is that you include the .ch where you need it and that is all. Those forms are documented in
     {{ilink: <topic quick_call_dll_functions> quick_call_dll_functions}}. The whole set is NOT active when OT4XB_LEAN_AND_MEAN is defined before including
     ot4xb.ch.
   | _kw_: commands, ot4xb.ch, DLL IMPORT, DLL FUNCTION, DllFunction, wrapper, DELEGATED
   | include-note-id: as-qtype-aliases }}*/
/*{{ note-id: dll-import-intermediate-commands | title_: The intermediate commands behind DLL IMPORT
   |: The prototype form `DLL <cDll> IMPORT <retType> <fnName>( <type> <param>, ... )` is a `#xtranslate` that rewrites
     the declaration into `DLL <cDll> IMPORT <fnName> AS QTYPE <code> PARAM <param> AS QTYPE <code> ...`, and that
     PARAM form is what the eight `#xcommand`s below (IMPORT / XIMPORT, with and without STATIC and DELEGATED)
     expand into the generated function. They exist to get the prototype form without preprocessor conflicts;
     write the prototype form, not them. The `AS <type>` names go through the alias table
     ({{ilink: <note-id as-qtype-aliases> AS type aliases}}). }}*/
/*{{ topic: ot4xb_ch_dll_function_commands | note_: intermediate command of DLL IMPORT / XIMPORT, not to be written directly
   | see-also: {{ilink: <note-id dll-import-intermediate-commands> the intermediate commands}} }}*/
#xcommand DLL <cDll> IMPORT <fn> AS QTYPE <rt> ;
                     [  PARAM <p1> AS QTYPE <t1> ]  ;
                     [, PARAM <pN> AS QTYPE <tN> ]  ;
                     [SYMBOL <cfn>]  ;
                     [DEFAULT  <pp1> := <d1> ] ;
                     [,DEFAULT <ppN> := <dN> ] ;
                     => ;
function <fn>( [<p1>] [,<pN>] ) ;
;local _fp_ := nGetProcAddress( <(cDll)> , iif(<.cfn.>,<(cfn)>,<(fn)>) ) ;
[; DEFAULT <pp1> := <d1> ] ;
[; DEFAULT <ppN> := <dN> ] ;
; return ( _Assert_fp_( _fp_ ) , FpQCall( _fp_  ,<rt> [+ <t1>] [+ <tN>] [,@<p1>][,@<pN>]  ) )
// -----------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands | note_: intermediate command of DLL IMPORT / XIMPORT, not to be written directly
   | see-also: {{ilink: <note-id dll-import-intermediate-commands> the intermediate commands}} }}*/
#xcommand DELEGATED DLL <cDll> IMPORT <fn> AS QTYPE <rt> ;
                     [  PARAM <p1> AS QTYPE <t1> ]  ;
                     [, PARAM <pN> AS QTYPE <tN> ]  ;
                     [SYMBOL <cfn>]  ;
                     [DEFAULT  <pp1> := <d1> ] ;
                     [,DEFAULT <ppN> := <dN> ] ;
                     => ;
function <fn>( [<p1>] [,<pN>] ) ;
;local _fp_ := nGetProcAddress( <(cDll)> , iif(<.cfn.>,<(cfn)>,<(fn)>) ) ;
[; DEFAULT <pp1> := <d1> ] ;
[; DEFAULT <ppN> := <dN> ] ;
; return ( _Assert_fp_( _fp_ ) , Delegated_FpQCall( _fp_  ,<rt> [+ <t1>] [+ <tN>] [,@<p1>][,@<pN>]  ) )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands | note_: intermediate command of DLL IMPORT / XIMPORT, not to be written directly
   | see-also: {{ilink: <note-id dll-import-intermediate-commands> the intermediate commands}} }}*/
#xcommand STATIC DLL <cDll> IMPORT <fn> AS QTYPE <rt> ;
                        [  PARAM <p1> AS QTYPE <t1> ]  ;
                        [, PARAM <pN> AS QTYPE <tN> ]  ;
                        [SYMBOL <cfn>]  ;
                     [DEFAULT  <pp1> := <d1> ] ;
                     [,DEFAULT <ppN> := <dN> ] ;
                     => ;
static function <fn>( [<p1>] [,<pN>] ) ;
;local _fp_ := nGetProcAddress( <(cDll)> , iif(<.cfn.>,<(cfn)>,<(fn)>) ) ;
[; DEFAULT <pp1> := <d1> ] ;
[; DEFAULT <ppN> := <dN> ] ;
; return ( _Assert_fp_( _fp_ ) , FpQCall( _fp_  ,<rt> [+ <t1>] [+ <tN>] [,@<p1>][,@<pN>]  ) )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands | note_: intermediate command of DLL IMPORT / XIMPORT, not to be written directly
   | see-also: {{ilink: <note-id dll-import-intermediate-commands> the intermediate commands}} }}*/
#xcommand STATIC DELEGATED DLL <cDll> IMPORT <fn> AS QTYPE <rt> ;
                        [  PARAM <p1> AS QTYPE <t1> ]  ;
                        [, PARAM <pN> AS QTYPE <tN> ]  ;
                        [SYMBOL <cfn>]  ;
                     [DEFAULT  <pp1> := <d1> ] ;
                     [,DEFAULT <ppN> := <dN> ] ;
                     => ;
static function <fn>( [<p1>] [,<pN>] ) ;
;local _fp_ := nGetProcAddress( <(cDll)> , iif(<.cfn.>,<(cfn)>,<(fn)>) ) ;
[; DEFAULT <pp1> := <d1> ] ;
[; DEFAULT <ppN> := <dN> ] ;
; return ( _Assert_fp_( _fp_ ) , Delegated_FpQCall( _fp_  ,<rt> [+ <t1>] [+ <tN>] [,@<p1>][,@<pN>]  ) )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands | note_: intermediate command of DLL IMPORT / XIMPORT, not to be written directly
   | see-also: {{ilink: <note-id dll-import-intermediate-commands> the intermediate commands}} }}*/
#xcommand DLL <cDll> XIMPORT <fn> AS QTYPE <rt> ;
                     [  PARAM <p1> AS QTYPE <t1> ]  ;
                     [, PARAM <pN> AS QTYPE <tN> ]  ;
                     [SYMBOL <cfn>]     ;
                     [DEFAULT  <pp1> := <d1> ] ;
                     [,DEFAULT <ppN> := <dN> ] ;
                     => ;
function <fn>( [<p1>] [,<pN>] ) ;
; static _fp_ := NIL;
;if _fp_ == NIL  ;
;   _fp_ := nGetProcAddress( <(cDll)> , iif(<.cfn.>,<(cfn)>,<(fn)>) ) ;
;end ;
[; DEFAULT <pp1> := <d1> ] ;
[; DEFAULT <ppN> := <dN> ] ;
; return ( _Assert_fp_( _fp_ ) , FpQCall( _fp_  ,<rt> [+ <t1>] [+ <tN>] [,@<p1>][,@<pN>]  ) )
// -----------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands | note_: intermediate command of DLL IMPORT / XIMPORT, not to be written directly
   | see-also: {{ilink: <note-id dll-import-intermediate-commands> the intermediate commands}} }}*/
#xcommand DELEGATED DLL <cDll> XIMPORT <fn> AS QTYPE <rt> ;
                     [  PARAM <p1> AS QTYPE <t1> ]  ;
                     [, PARAM <pN> AS QTYPE <tN> ]  ;
                     [SYMBOL <cfn>]     ;
                     [DEFAULT  <pp1> := <d1> ] ;
                     [,DEFAULT <ppN> := <dN> ] ;
                     => ;
function <fn>( [<p1>] [,<pN>] ) ;
; static _fp_ := NIL;
;if _fp_ == NIL  ;
;   _fp_ := nGetProcAddress( <(cDll)> , iif(<.cfn.>,<(cfn)>,<(fn)>) ) ;
;end ;
[; DEFAULT <pp1> := <d1> ] ;
[; DEFAULT <ppN> := <dN> ] ;
; return ( _Assert_fp_( _fp_ ) , Delegated_FpQCall( _fp_  ,<rt> [+ <t1>] [+ <tN>] [,@<p1>][,@<pN>]  ) )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands | note_: intermediate command of DLL IMPORT / XIMPORT, not to be written directly
   | see-also: {{ilink: <note-id dll-import-intermediate-commands> the intermediate commands}} }}*/
#xcommand STATIC DLL <cDll> XIMPORT <fn> AS QTYPE <rt> ;
                        [  PARAM <p1> AS QTYPE <t1> ]  ;
                        [, PARAM <pN> AS QTYPE <tN> ]  ;
                        [SYMBOL <cfn>]    ;
                     [DEFAULT  <pp1> := <d1> ] ;
                     [,DEFAULT <ppN> := <dN> ] ;
                     => ;
static function <fn>( [<p1>] [,<pN>] ) ;
; static _fp_ := NIL;
;if _fp_ == NIL   ;
;   _fp_ := nGetProcAddress( <(cDll)> , iif(<.cfn.>,<(cfn)>,<(fn)>) ) ;
;end ;
[; DEFAULT <pp1> := <d1> ] ;
[; DEFAULT <ppN> := <dN> ] ;
; return ( _Assert_fp_( _fp_ ) , FpQCall( _fp_  ,<rt> [+ <t1>] [+ <tN>] [,@<p1>][,@<pN>]  ) )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands | note_: intermediate command of DLL IMPORT / XIMPORT, not to be written directly
   | see-also: {{ilink: <note-id dll-import-intermediate-commands> the intermediate commands}} }}*/
#xcommand STATIC DELEGATED DLL <cDll> XIMPORT <fn> AS QTYPE <rt> ;
                        [  PARAM <p1> AS QTYPE <t1> ]  ;
                        [, PARAM <pN> AS QTYPE <tN> ]  ;
                        [SYMBOL <cfn>]    ;
                     [DEFAULT  <pp1> := <d1> ] ;
                     [,DEFAULT <ppN> := <dN> ] ;
                     => ;
static function <fn>( [<p1>] [,<pN>] ) ;
; static _fp_ := NIL;
;if _fp_ == NIL   ;
;   _fp_ := nGetProcAddress( <(cDll)> , iif(<.cfn.>,<(cfn)>,<(fn)>) ) ;
;end ;
[; DEFAULT <pp1> := <d1> ] ;
[; DEFAULT <ppN> := <dN> ] ;
; return ( _Assert_fp_( _fp_ ) , Delegated_FpQCall( _fp_  ,<rt> [+ <t1>] [+ <tN>] [,@<p1>][,@<pN>]  ) )
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands
   | command_: ### QTEMPLATE
   | syntax_: `[local | static] QTEMPLATE <cTemplate> AS QTYPE <cRet> [ PARAM AS QTYPE <cT1> [, PARAM AS QTYPE <cTN>] ]`
   | desc_: Builds a Qualified-call template string by hand: assigns `<cRet> + <cT1> + ... + <cTN>` to the
     variable `<cTemplate>` (declaring it as local or static when the keyword is given), ready for FpQCall().
     The types are written with the `AS <type>` aliases or as `AS QTYPE "<code>"`.
   | params:
     - `cTemplate` Variable that receives the template string.
     - `cRet` QTYPE code of the return value.
     - `cT1` QTYPE code of each parameter, in order.
   | see-also: DLL IMPORT, FpQCall }}*/
#xcommand QTEMPLATE <qt> AS QTYPE <rt> [  PARAM AS QTYPE <t1> ]  [, PARAM AS QTYPE <tN> ]  => ;
; <qt> := <rt> [+ <t1>] [+ <tN>]
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands | _note_: documented under QTEMPLATE }}*/
#xcommand local QTEMPLATE <qt> AS QTYPE <rt> [  PARAM AS QTYPE <t1> ]  [, PARAM AS QTYPE <tN> ]  => ;
; local <qt> := <rt> [+ <t1>] [+ <tN>]
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands | _note_: documented under QTEMPLATE }}*/
#xcommand static QTEMPLATE <qt> AS QTYPE <rt> [  PARAM AS QTYPE <t1> ]  [, PARAM AS QTYPE <tN> ]  => ;
; static <qt> := <rt> [+ <t1>] [+ <tN>]
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands
   | command_: ### DLL IMPORT
   | syntax_: `[STATIC] [DELEGATED] DLL <cDll> IMPORT <retType> <fnName>( [<type1> <p1>] [, <typeN> <pN>] ) [ SYMBOL <cExport> ] [ DEFAULT <p> := <value> [, DEFAULT <pN> := <valueN>] ]`
   | desc_: Declares `function <fnName>( p1, ..., pN )` (a `static function` with STATIC) that calls the export
     `<cExport>` - by default the function name - of the DLL `<cDll>`, written like a C prototype:
     `DLL "mydll" IMPORT LPSTR MyFunction( LONG p1, DOUBLE p2 )`. The types are the `AS <type>` aliases of the
     table above without the `AS` (or a QTYPE code in quotes). Every call resolves the address with
     nGetProcAddress(), asserts it with _Assert_fp_() and calls it with FpQCall() and the template built from the
     return type and the parameter types; the parameters are passed by reference, so the pointer types get their
     values back. With DELEGATED the call goes through Delegated_FpQCall(): the DLL function is executed in the
     GUI thread. DEFAULT clauses give the parameters a default value.
   | params:
     - `cDll` DLL name, as for nGetProcAddress().
     - `retType` Type of the return value (`VOID` for none).
     - `fnName` Name of the generated Xbase++ function; the export name too, unless SYMBOL says otherwise.
     - `type1 p1` One parameter, type and name, in the order of the C prototype.
     - `cExport` Name of the export when it differs from fnName: a decorated (mangled) name, typically.
     - `DEFAULT p := value` Default for an omitted parameter.
   | see-also: DLL XIMPORT, QTEMPLATE }}*/
#xtranslate DLL <cDll> IMPORT <rt> <fn>( [<t1> <p1> ] [,<tN> <pN> ] ) ;
                     [<*more*>]  ;
                     => ;
DLL <cDll> IMPORT <fn> AS <rt> ;
                     [  PARAM <p1> AS <t1> ]  ;
                     [, PARAM <pN> AS <tN> ]  ;
                     <more>
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands | _note_: documented under DLL IMPORT }}*/
#xtranslate DELEGATED DLL <cDll> IMPORT <rt> <fn>( [<t1> <p1> ] [,<tN> <pN> ] ) ;
                     [<*more*>]  ;
                     => ;
DELEGATED DLL <cDll> IMPORT <fn> AS <rt> ;
                     [  PARAM <p1> AS <t1> ]  ;
                     [, PARAM <pN> AS <tN> ]  ;
                     <more>
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands
   | command_: ### DLL XIMPORT
   | syntax_: `[STATIC] [DELEGATED] DLL <cDll> XIMPORT <retType> <fnName>( [<type1> <p1>] [, <typeN> <pN>] ) [ SYMBOL <cExport> ] [ DEFAULT <p> := <value> [, DEFAULT <pN> := <valueN>] ]`
   | desc_: The variant of DLL IMPORT with a cached address: the export is resolved with nGetProcAddress() the
     first time the generated function runs and the address is kept in a static of the function; later calls
     reuse it, where DLL IMPORT resolves it on every call. Clauses and types are the same, SYMBOL included:
     `DLL "mydll" XIMPORT INT32 MyFunc( LONG p1 ) SYMBOL "?MyFunc@@YAHJ@Z"`.
   | see-also: DLL IMPORT }}*/
#xtranslate DLL <cDll> XIMPORT <rt> <fn>( [<t1> <p1> ] [,<tN> <pN> ] ) ;
                     [<*more*>]  ;
                     => ;
DLL <cDll> XIMPORT <fn> AS <rt> ;
                     [  PARAM <p1> AS <t1> ]  ;
                     [, PARAM <pN> AS <tN> ]  ;
                     <more>
// -----------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_dll_function_commands | _note_: documented under DLL XIMPORT }}*/
#xtranslate DELEGATED DLL <cDll> XIMPORT <rt> <fn>( [<t1> <p1> ] [,<tN> <pN> ] ) ;
                     [<*more*>]  ;
                     => ;
DELEGATED DLL <cDll> XIMPORT <fn> AS <rt> ;
                     [  PARAM <p1> AS <t1> ]  ;
                     [, PARAM <pN> AS <tN> ]  ;
                     <more>                               
                     
#endif
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: quick_call_dll_functions
   | _slug_: quick-call-dll-functions
   | category: commands , ot4xb.ch , function-pointer
   | desc: The `@dll:function( ... )` notation: call an export of a DLL right where you need it, with no wrapper
     function to declare. Two forms: types inferred from the values, or an explicit Qualified-call prototype.
     Together with a `#xtranslate` in a .ch of your own, for example
     `#xtranslate Rm.EndSession( <h> ) => @rstrtmgr:["__sl__sl"]:RmEndSession( <h> )`,
     it replaces the DLL IMPORT family for most uses:
     | _kw_: @dll, quick call, call dll export, FpQCall, DllCall, inline dll call
     include the .ch where you need it and that is all. }}*/
/*{{ topic: quick_call_dll_functions
   | command_: ### @dll:function( ... )
   | syntax_: `@<dll>:<function>( [<p1>] [, <pN>] )`
   | desc_: Calls the export `<function>` of the DLL `<dll>` through {{ilink: <function nFpCall> nFpCall}}, the
     argument types being inferred from the values passed (`@user32:MessageBeep( 0 )`). Both names are written
     bare, without quotes. With OT4XB_ASSERT_LEVEL above 2 the export is first checked with _Assert_dll_fn_(),
     which raises an error when the DLL or the function cannot be found.
   | params:
     - `dll` DLL name, without extension.
     - `function` Export name.
     - `p1` Arguments, converted from their Xbase++ types.
   | see-also: @dll:[prototype]:function( ... ), DLL IMPORT }}*/
#if OT4XB_ASSERT_LEVEL > 2
/*{{ topic: quick_call_dll_functions | _note_: documented under @dll:function( ... ) - the variant with the assert }}*/
#xtranslate @<dll>:<fn>([<p1>] [,<pn>] ) => ( _Assert_dll_fn_(<(dll)>,<(fn)>) , nFpCall( {<(dll)>,<(fn)>} [,<p1>] [,<pn>] ) )
#else
/*{{ topic: quick_call_dll_functions | _note_: documented under @dll:function( ... ) - the variant without the assert }}*/
#xtranslate @<dll>:<fn>([<p1>] [,<pn>] ) => nFpCall( {<(dll)>,<(fn)>} [,<p1>] [,<pn>] )
#endif
// -----------------------------------------------------------------------------------------------------------------
/*{{ topic: quick_call_dll_functions
   | command_: ### @dll:[prototype]:function( ... )
   | syntax_: `@<dll>:[<cPrototype>]:<function>( [<p1>] [, <pN>] )`
   | desc_: Calls the export `<function>` of the DLL `<dll>` through {{ilink: <function FpQCall> FpQCall}} with the
     Qualified-call prototype `<cPrototype>`, a QTYPE template string in quotes (`@kernel32:["__sl__sl"]:Sleep( 100 )`):
     the return value and every argument are converted exactly as the template says.
   | params:
     - `dll` DLL name, without extension.
     - `cPrototype` QTYPE template string: return type code followed by one code per parameter.
     - `function` Export name.
     - `p1` Arguments, converted as the template says.
   | see-also: @dll:function( ... ), QTEMPLATE, DLL IMPORT }}*/
#xtranslate @<dll>:\[<tp>\]:<fn>([<p1>] [,<pn>] ) => FpQCall( {<(dll)>,<(fn)>},<(tp)> [,<p1>] [,<pn>] )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER BINSTR DWORD ARRAY
   | syntax_: `MEMBER BINSTR <storageName> DWORD ARRAY <methodName> ITEMS <nItems>`
   | desc_: Adds a binary string member `<storageName>` of `<nItems>` * 4 bytes plus a method
     `<methodName>`( nIndex [, nValue] ) that reads or writes item nIndex of it as a DWORD (PeekDWord / PokeDWord):
     nIndex is 0-based and checked against 0 .. `<nItems>` - 1; with nValue the item is written, and the value
     is returned in both cases. The storage is locked during the access.
   | params:
     - `storageName` Name of the BINSTR member holding the items.
     - `methodName` Name of the accessor method generated for the items.
     - `nItems` Numeric - Number of items; fixes the member size.
   | see-also: MEMBER BINSTR, MEMBER BINSTR WORD ARRAY }}*/
#xtranslate MEMBER BINSTR <s> DWORD ARRAY <m> ITEMS <n> => ;
            ooo:_Member_BINSTR( <(s)> , <n> * 4 ) ;
            ; ooo:_Method( <(m)> , {|s,n,v| _Assert_Range_(n,0,(<n>-1)),   s:_lock_() , iif( PCount() > 2,;
                                            PokeDWord(s:_addressof_(<(s)>), n * 4,v),;
                                            v := PeekDWord(s:_addressof_(<(s)>), n * 4)),;
                                            s:_unlock_() , v } )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER BINSTR WORD ARRAY
   | syntax_: `MEMBER BINSTR <storageName> WORD ARRAY <methodName> ITEMS <nItems>`
   | desc_: Adds a binary string member `<storageName>` of `<nItems>` * 2 bytes plus a method
     `<methodName>`( nIndex [, nValue] ) that reads or writes item nIndex of it as a WORD (PeekWord / PokeWord):
     nIndex is 0-based and checked against 0 .. `<nItems>` - 1; with nValue the item is written, and the value
     is returned in both cases. The storage is locked during the access.
   | params:
     - `storageName` Name of the BINSTR member holding the items.
     - `methodName` Name of the accessor method generated for the items.
     - `nItems` Numeric - Number of items; fixes the member size.
   | see-also: MEMBER BINSTR, MEMBER BINSTR DWORD ARRAY }}*/
#xtranslate MEMBER BINSTR <s> WORD ARRAY <m> ITEMS <n> => ;
            ooo:_Member_BINSTR( <(s)> , <n> * 2 ) ;
            ; ooo:_Method( <(m)> , {|s,n,v| _Assert_Range_(n,0,(<n>-1)),   s:_lock_() , iif( PCount() > 2,;
                                            PokeWord(s:_addressof_(<(s)>), n * 2,v),;
                                            v := PeekWord(s:_addressof_(<(s)>), n * 2)),;
                                            s:_unlock_() , v } )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_structure_commands
   | command_: ### MEMBER BINSTR BYTE ARRAY
   | syntax_: `MEMBER BINSTR <storageName> BYTE ARRAY <methodName> ITEMS <nItems>`
   | desc_: Adds a binary string member `<storageName>` of `<nItems>` * 1 bytes plus a method
     `<methodName>`( nIndex [, nValue] ) that reads or writes item nIndex of it as a BYTE (PeekWord / PokeWord as written today):
     nIndex is 0-based and checked against 0 .. `<nItems>` - 1; with nValue the item is written, and the value
     is returned in both cases. The storage is locked during the access.
   | params:
     - `storageName` Name of the BINSTR member holding the items.
     - `methodName` Name of the accessor method generated for the items.
     - `nItems` Numeric - Number of items; fixes the member size.
   | see-also: MEMBER BINSTR, MEMBER BINSTR WORD ARRAY }}*/
#xtranslate MEMBER BINSTR <s> BYTE ARRAY <m> ITEMS <n> => ;
            ooo:_Member_BINSTR( <(s)> , <n>   ) ;
            ; ooo:_Method( <(m)> , {|s,n,v| _Assert_Range_(n,0,(<n>-1)),   s:_lock_() , iif( PCount() > 2,;
                                            PokeWord(s:_addressof_(<(s)>), n ,v),;
                                            v := PeekWord(s:_addressof_(<(s)>), n )),;
                                            s:_unlock_() , v } )
//----------------------------------------------------------------------------------------------------------------------

#ifndef OT4XB_LEAN_AND_MEAN
/*{{ topic: ot4xb_ch_with_object_commands
   | _tg_: with_object
   | _slug_: with-object-commands
   | category: commands , ot4xb.ch
   | deprecated: kept for existing code only; do not use in new code
   | desc: Harbour-style WITH OBJECT and ITERATE ARRAY commands over the per-thread with-object stack of ot4xb
     ({{ilink: <function WithObjectStackPush> WithObjectStackPush}} and friends): a pushed object is reachable
     as `with.item` or through the `.:` shorthand, and ITERATE ARRAY walks an array putting each item on top.
   |: They work well when everything works, but they lean on the preprocessor (a `::` after a logical operator
     can be caught by the `.:` rule) and can get in the way. The whole set is NOT active when
     OT4XB_LEAN_AND_MEAN is defined before including ot4xb.ch: that define exists to leave out old things of
     little use that existing code may still rely on, and these commands are among them.
   | note: The set was added to imitate Harbour's WITH OBJECT. In Harbour it is built into the language: the
     error handling and the stack know about it. Here it is a bolt-on over the preprocessor and a per-thread
     stack: pretty, and it works, but when something goes wrong inside it (an error, a Break, a forgotten END
     | _kw_: commands, ot4xb.ch, WITH OBJECT, ITERATE ARRAY, Harbour, deprecated
     WITH) it gets in the way more than it helps. }}*/
/*{{ topic: ot4xb_ch_with_object_commands
   | command_: ### ITERATE ARRAY
   | syntax_: `ITERATE ARRAY <aArray> [ VALID TYPES <type1> [, <typeN>] ] ... END ITERATE`
   | desc_: Loops over the items of aArray: starts an iterator on the with-object stack ({{ilink: <function OT4XB_ARRAY_ITERATOR>
     OT4XB_ARRAY_ITERATOR}}) and repeats the body while {{ilink: <function OT4XB_ARRAY_ITERATOR_STEP> OT4XB_ARRAY_ITERATOR_STEP}}
     loads the next item on top of the stack, where `with.item` reads it and `with.index` gives its 1-based index.
     VALID TYPES restricts the loop to the items whose type matches the nOr() of the given type flags.
   | params:
     - `aArray` Array to iterate.
     - `type1` Type flags, as accepted by OT4XB_ARRAY_ITERATOR_STEP(); optional.
   | see-also: END ITERATE, WITH OBJECT }}*/
#xcommand ITERATE ARRAY <a> ;
          [ VALID TYPES <t,...>] => ;
          OT4XB_ARRAY_ITERATOR( <a> ) ;
          ; while( OT4XB_ARRAY_ITERATOR_STEP( [nOr(<t>)] ) )
/*{{ topic: ot4xb_ch_with_object_commands
   | command_: ### END ITERATE
   | syntax_: `END ITERATE`
   | desc_: Closes an ITERATE ARRAY loop (expands to `end`).
   | see-also: ITERATE ARRAY }}*/
#xcommand END ITERATE => end
// -----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_with_object_commands
   | command_: ### WITH FRAME
   | syntax_: `WITH FRAME <nDepth> ... END FRAME <nDepth>`
   | desc_: Opens a protected frame around WITH OBJECT code: installs an error block that breaks out on any error, saves
     the current with-object stack depth in nDepth ({{ilink: <function WithObjectStackCount> WithObjectStackCount}})
     and opens a BEGIN SEQUENCE. END FRAME closes the sequence, unwinds the stack back to that depth
     ({{ilink: <function WithObjectStackRecover> WithObjectStackRecover}}) and restores the previous error block,
     so a frame abandoned by an error or a Break leaves the stack as it found it.
   | params:
     - `nDepth` A local that receives the stack depth at the frame start; pass the same one to END FRAME.
   | see-also: END FRAME, ON EXIT FRAME, WITH OBJECT NONIL }}*/
#xcommand WITH FRAME <v> =>;
WithObjectStackPush( ErrorBlock({|__e__| Break(__e__)}) ) ;
;<v> := WithObjectStackCount() ;
; BEGIN SEQUENCE
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_with_object_commands
   | command_: ### END FRAME
   | syntax_: `END FRAME <nDepth>`
   | desc_: Closes a WITH FRAME block: END SEQUENCE, stack unwound to nDepth, previous error block restored.
   | params:
     - `nDepth` The local given to WITH FRAME.
   | see-also: WITH FRAME }}*/
#xcommand END FRAME <v> =>;
; END SEQUENCE    ;
; WithObjectStackRecover( <v> ) ;
; ErrorBlock( WithObjectStackPop() )
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_with_object_commands
   | command_: ### ON EXIT FRAME
   | syntax_: `ON <lCondition> EXIT FRAME`
   | desc_: Leaves the enclosing WITH FRAME when lCondition is not empty (expands to a Break()).
   | params:
     - `lCondition` Any value; Empty() means stay.
   | see-also: WITH FRAME }}*/
#xcommand ON <b> EXIT FRAME => iif(Empty(<b>),, Break())
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_with_object_commands
   | command_: ### WITH OBJECT NONIL
   | syntax_: `WITH OBJECT <oObject> NONIL`
   | desc_: Pushes oObject on the with-object stack and BREAKs when it is NIL: to be used inside a WITH FRAME (or any
     BEGIN SEQUENCE), which then unwinds the stack.
   | params:
     - `oObject` Object (or any value) to push.
   | see-also: WITH OBJECT, WITH FRAME }}*/
#xcommand WITH OBJECT <o> NONIL =>;
 WithObjectStackPush(<o>);
 ; if WithObjectStackTop() == NIL ;
 ; BREAK ;
 ; end
//----------------------------------------------------------------------------------------------------------------------
/*{{ topic: ot4xb_ch_with_object_commands
   | command_: ### WITH OBJECT
   | syntax_: `WITH OBJECT <oObject> ... END WITH`
   | desc_: Pushes oObject on the with-object stack ({{ilink: <function WithObjectStackPush> WithObjectStackPush}}); until
     END WITH it is `with.item` and the target of the `.:` shorthand. Blocks nest: the outer objects stay below.
   | params:
     - `oObject` Object (or any value) to push.
   | see-also: END WITH, WITH OBJECT NONIL, WITH FRAME }}*/
#xcommand WITH OBJECT <o> => WithObjectStackPush(<o>)
/*{{ topic: ot4xb_ch_with_object_commands
   | command_: ### END WITH
   | syntax_: `END WITH`
   | desc_: Pops the top of the with-object stack ({{ilink: <function WithObjectStackPop> WithObjectStackPop}}).
   | see-also: WITH OBJECT }}*/
#xcommand END WITH => WithObjectStackPop()
/*{{ topic: ot4xb_ch_with_object_commands
   | command_: ### with.item
   | syntax_: `with.item`
   | desc_: The object on top of the with-object stack ({{ilink: <function WithObjectStackTop> WithObjectStackTop}}):
     the current WITH OBJECT, or the current item inside ITERATE ARRAY. `with.this` is the same thing.
   | see-also: with.this, with.index, .: }}*/
#xtranslate with.item =>WithObjectStackTop()
/*{{ topic: ot4xb_ch_with_object_commands
   | command_: ### with.this
   | syntax_: `with.this`
   | desc_: Same as `with.item`.
   | see-also: with.item }}*/
#xtranslate with.this =>WithObjectStackTop()
/*{{ topic: ot4xb_ch_with_object_commands
   | command_: ### with.index
   | syntax_: `with.index`
   | desc_: The 1-based index of the current item inside an ITERATE ARRAY loop ({{ilink: <function OT4XB_ARRAY_ITERATOR_INDEX>
     OT4XB_ARRAY_ITERATOR_INDEX}}).
   | see-also: ITERATE ARRAY, with.item }}*/
#xtranslate with.index =>OT4XB_ARRAY_ITERATOR_INDEX()
/*{{ topic: ot4xb_ch_with_object_commands
   | command_: ### .: message shorthand
   | syntax_: `.:<message>`
   | desc_: Sends a message to the object on top of the with-object stack: `.:DoIt()` is `WithObjectStackTop():DoIt()`.
     `..:`, `...:` and `....:` address the objects 1, 2 and 3 below the top, and `.:(<n>):<message>` the one n below.
   | see-also: with.item, WITH OBJECT }}*/
#xtranslate .:<*more*> => WithObjectStackTop():<more>
/*{{ topic: ot4xb_ch_with_object_commands | _note_: documented under .: message shorthand }}*/
#xtranslate ..:<*more*> => WithObjectStackTop(1):<more>
/*{{ topic: ot4xb_ch_with_object_commands | _note_: documented under .: message shorthand }}*/
#xtranslate ...:<*more*> => WithObjectStackTop(2):<more>
/*{{ topic: ot4xb_ch_with_object_commands | _note_: documented under .: message shorthand }}*/
#xtranslate ....:<*more*> => WithObjectStackTop(3):<more>
/*{{ topic: ot4xb_ch_with_object_commands | _note_: documented under .: message shorthand }}*/
#xtranslate .:(<n>):<*more*> => WithObjectStackTop(<n>):<more>
//----------------------------------------------------------------------------------------------------------------------
// This 3 lines would prevent confilcts within the logical operators and WITH OBJECT
// Many thanks to Andreas Gehrs-Pahl that foung the bug and the workarround
/*{{ topic: ot4xb_ch_with_object_commands |: The `.not. ::x`, `.and. ::x` and `.or. ::x` translations below keep a `::` written right after a
     logical operator from being caught by the `.:` rule (Self is restored explicitly); the three extra ones
     cover the cases the preprocessor joins without a blank. Thanks to Andreas Gehrs-Pahl for the bug and
     the workaround. }}*/
#xtranslate .not. ::<*more*> => .not. Self:<more>
/*{{ topic: ot4xb_ch_with_object_commands | _note_: documented in the note above }}*/
#xtranslate .and. ::<*more*> => .and. Self:<more>
/*{{ topic: ot4xb_ch_with_object_commands | _note_: documented in the note above }}*/
#xtranslate .or. ::<*more*> => .or.  Self:<more>
// ...... but sometimes the preprocessor not cath it correctly .....
// but this 3 ugly extra lines seems to work in all cases
/*{{ topic: ot4xb_ch_with_object_commands | _note_: documented in the note above }}*/
#xtranslate .notWithObjectStackTop()::<*more*> => .not. Self:<more>
/*{{ topic: ot4xb_ch_with_object_commands | _note_: documented in the note above }}*/
#xtranslate .andWithObjectStackTop()::<*more*> => .and. Self:<more>
/*{{ topic: ot4xb_ch_with_object_commands | _note_: documented in the note above }}*/
#xtranslate .orWithObjectStackTop()::<*more*> => .or. Self:<more>   
#endif
//----------------------------------------------------------------------------------------------------------------------
#ifndef _OT4XB_EXCLUDE_WINAPI_CONSTANTS
//----------------------------------------------------------------------------------------------------------------------

#ifndef LANG_NEUTRAL
#define LANG_NEUTRAL                     0x00
#define LANG_INVARIANT                   0x7f
#define LANG_AFRIKAANS                   0x36
#define LANG_ALBANIAN                    0x1c
#define LANG_ARABIC                      0x01
#define LANG_ARMENIAN                    0x2b
#define LANG_ASSAMESE                    0x4d
#define LANG_AZERI                       0x2c
#define LANG_BASQUE                      0x2d
#define LANG_BELARUSIAN                  0x23
#define LANG_BENGALI                     0x45
#define LANG_BOSNIAN                     0x1a
#define LANG_BULGARIAN                   0x02
#define LANG_CATALAN                     0x03
#define LANG_CHINESE                     0x04
#define LANG_CROATIAN                    0x1a
#define LANG_CZECH                       0x05
#define LANG_DANISH                      0x06
#define LANG_DIVEHI                      0x65
#define LANG_DUTCH                       0x13
#define LANG_ENGLISH                     0x09
#define LANG_ESTONIAN                    0x25
#define LANG_FAEROESE                    0x38
#define LANG_FARSI                       0x29
#define LANG_FINNISH                     0x0b
#define LANG_FRENCH                      0x0c
#define LANG_GALICIAN                    0x56
#define LANG_GEORGIAN                    0x37
#define LANG_GERMAN                      0x07
#define LANG_GREEK                       0x08
#define LANG_GUJARATI                    0x47
#define LANG_HEBREW                      0x0d
#define LANG_HINDI                       0x39
#define LANG_HUNGARIAN                   0x0e
#define LANG_ICELANDIC                   0x0f
#define LANG_INDONESIAN                  0x21
#define LANG_ITALIAN                     0x10
#define LANG_JAPANESE                    0x11
#define LANG_KANNADA                     0x4b
#define LANG_KASHMIRI                    0x60
#define LANG_KAZAK                       0x3f
#define LANG_KONKANI                     0x57
#define LANG_KOREAN                      0x12
#define LANG_KYRGYZ                      0x40
#define LANG_LATVIAN                     0x26
#define LANG_LITHUANIAN                  0x27
#define LANG_MACEDONIAN                  0x2f   // the Former Yugoslav Republic of Macedonia
#define LANG_MALAY                       0x3e
#define LANG_MALAYALAM                   0x4c
#define LANG_MALTESE                     0x3a
#define LANG_MANIPURI                    0x58
#define LANG_MAORI                       0x81
#define LANG_MARATHI                     0x4e
#define LANG_MONGOLIAN                   0x50
#define LANG_NEPALI                      0x61
#define LANG_NORWEGIAN                   0x14
#define LANG_ORIYA                       0x48
#define LANG_POLISH                      0x15
#define LANG_PORTUGUESE                  0x16
#define LANG_PUNJABI                     0x46
#define LANG_QUECHUA                     0x6b
#define LANG_ROMANIAN                    0x18
#define LANG_RUSSIAN                     0x19
#define LANG_SAMI                        0x3b
#define LANG_SANSKRIT                    0x4f
#define LANG_SERBIAN                     0x1a
#define LANG_SINDHI                      0x59
#define LANG_SLOVAK                      0x1b
#define LANG_SLOVENIAN                   0x24
#define LANG_SOTHO                       0x6c
#define LANG_SPANISH                     0x0a
#define LANG_SWAHILI                     0x41
#define LANG_SWEDISH                     0x1d
#define LANG_SYRIAC                      0x5a
#define LANG_TAMIL                       0x49
#define LANG_TATAR                       0x44
#define LANG_TELUGU                      0x4a
#define LANG_THAI                        0x1e
#define LANG_TSWANA                      0x32
#define LANG_TURKISH                     0x1f
#define LANG_UKRAINIAN                   0x22
#define LANG_URDU                        0x20
#define LANG_UZBEK                       0x43
#define LANG_VIETNAMESE                  0x2a
#define LANG_WELSH                       0x52
#define LANG_XHOSA                       0x34
#define LANG_ZULU                        0x35
#define SUBLANG_NEUTRAL                  0x00    // language neutral
#define SUBLANG_DEFAULT                  0x01    // user default
#define SUBLANG_SYS_DEFAULT              0x02    // system default
#define SUBLANG_ARABIC_SAUDI_ARABIA      0x01    // Arabic (Saudi Arabia)
#define SUBLANG_ARABIC_IRAQ              0x02    // Arabic (Iraq)
#define SUBLANG_ARABIC_EGYPT             0x03    // Arabic (Egypt)
#define SUBLANG_ARABIC_LIBYA             0x04    // Arabic (Libya)
#define SUBLANG_ARABIC_ALGERIA           0x05    // Arabic (Algeria)
#define SUBLANG_ARABIC_MOROCCO           0x06    // Arabic (Morocco)
#define SUBLANG_ARABIC_TUNISIA           0x07    // Arabic (Tunisia)
#define SUBLANG_ARABIC_OMAN              0x08    // Arabic (Oman)
#define SUBLANG_ARABIC_YEMEN             0x09    // Arabic (Yemen)
#define SUBLANG_ARABIC_SYRIA             0x0a    // Arabic (Syria)
#define SUBLANG_ARABIC_JORDAN            0x0b    // Arabic (Jordan)
#define SUBLANG_ARABIC_LEBANON           0x0c    // Arabic (Lebanon)
#define SUBLANG_ARABIC_KUWAIT            0x0d    // Arabic (Kuwait)
#define SUBLANG_ARABIC_UAE               0x0e    // Arabic (U.A.E)
#define SUBLANG_ARABIC_BAHRAIN           0x0f    // Arabic (Bahrain)
#define SUBLANG_ARABIC_QATAR             0x10    // Arabic (Qatar)
#define SUBLANG_AZERI_LATIN              0x01    // Azeri (Latin)
#define SUBLANG_AZERI_CYRILLIC           0x02    // Azeri (Cyrillic)
#define SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_LATIN 0x05 // Bosnian (Bosnia and Herzegovina - Latin)
#define SUBLANG_CHINESE_TRADITIONAL      0x01    // Chinese (Taiwan)
#define SUBLANG_CHINESE_SIMPLIFIED       0x02    // Chinese (PR China)
#define SUBLANG_CHINESE_HONGKONG         0x03    // Chinese (Hong Kong S.A.R., P.R.C.)
#define SUBLANG_CHINESE_SINGAPORE        0x04    // Chinese (Singapore)
#define SUBLANG_CHINESE_MACAU            0x05    // Chinese (Macau S.A.R.)
#define SUBLANG_CROATIAN_CROATIA         0x01    // Croatian (Croatia)
#define SUBLANG_CROATIAN_BOSNIA_HERZEGOVINA_LATIN 0x04 // Croatian (Bosnia and Herzegovina - Latin)
#define SUBLANG_DUTCH                    0x01    // Dutch
#define SUBLANG_DUTCH_BELGIAN            0x02    // Dutch (Belgian)
#define SUBLANG_ENGLISH_US               0x01    // English (USA)
#define SUBLANG_ENGLISH_UK               0x02    // English (UK)
#define SUBLANG_ENGLISH_AUS              0x03    // English (Australian)
#define SUBLANG_ENGLISH_CAN              0x04    // English (Canadian)
#define SUBLANG_ENGLISH_NZ               0x05    // English (New Zealand)
#define SUBLANG_ENGLISH_EIRE             0x06    // English (Irish)
#define SUBLANG_ENGLISH_SOUTH_AFRICA     0x07    // English (South Africa)
#define SUBLANG_ENGLISH_JAMAICA          0x08    // English (Jamaica)
#define SUBLANG_ENGLISH_CARIBBEAN        0x09    // English (Caribbean)
#define SUBLANG_ENGLISH_BELIZE           0x0a    // English (Belize)
#define SUBLANG_ENGLISH_TRINIDAD         0x0b    // English (Trinidad)
#define SUBLANG_ENGLISH_ZIMBABWE         0x0c    // English (Zimbabwe)
#define SUBLANG_ENGLISH_PHILIPPINES      0x0d    // English (Philippines)
#define SUBLANG_FRENCH                   0x01    // French
#define SUBLANG_FRENCH_BELGIAN           0x02    // French (Belgian)
#define SUBLANG_FRENCH_CANADIAN          0x03    // French (Canadian)
#define SUBLANG_FRENCH_SWISS             0x04    // French (Swiss)
#define SUBLANG_FRENCH_LUXEMBOURG        0x05    // French (Luxembourg)
#define SUBLANG_FRENCH_MONACO            0x06    // French (Monaco)
#define SUBLANG_GERMAN                   0x01    // German
#define SUBLANG_GERMAN_SWISS             0x02    // German (Swiss)
#define SUBLANG_GERMAN_AUSTRIAN          0x03    // German (Austrian)
#define SUBLANG_GERMAN_LUXEMBOURG        0x04    // German (Luxembourg)
#define SUBLANG_GERMAN_LIECHTENSTEIN     0x05    // German (Liechtenstein)
#define SUBLANG_ITALIAN                  0x01    // Italian
#define SUBLANG_ITALIAN_SWISS            0x02    // Italian (Swiss)
#define SUBLANG_KASHMIRI_SASIA           0x02    // Kashmiri (South Asia)
#define SUBLANG_KASHMIRI_INDIA           0x02    // For app compatibility only
#define SUBLANG_KOREAN                   0x01    // Korean (Extended Wansung)
#define SUBLANG_LITHUANIAN               0x01    // Lithuanian
#define SUBLANG_MALAY_MALAYSIA           0x01    // Malay (Malaysia)
#define SUBLANG_MALAY_BRUNEI_DARUSSALAM  0x02    // Malay (Brunei Darussalam)
#define SUBLANG_NEPALI_INDIA             0x02    // Nepali (India)
#define SUBLANG_NORWEGIAN_BOKMAL         0x01    // Norwegian (Bokmal)
#define SUBLANG_NORWEGIAN_NYNORSK        0x02    // Norwegian (Nynorsk)
#define SUBLANG_PORTUGUESE               0x02    // Portuguese
#define SUBLANG_PORTUGUESE_BRAZILIAN     0x01    // Portuguese (Brazilian)
#define SUBLANG_QUECHUA_BOLIVIA          0x01    // Quechua (Bolivia)
#define SUBLANG_QUECHUA_ECUADOR          0x02    // Quechua (Ecuador)
#define SUBLANG_QUECHUA_PERU             0x03    // Quechua (Peru)
#define SUBLANG_SAMI_NORTHERN_NORWAY     0x01    // Northern Sami (Norway)
#define SUBLANG_SAMI_NORTHERN_SWEDEN     0x02    // Northern Sami (Sweden)
#define SUBLANG_SAMI_NORTHERN_FINLAND    0x03    // Northern Sami (Finland)
#define SUBLANG_SAMI_LULE_NORWAY         0x04    // Lule Sami (Norway)
#define SUBLANG_SAMI_LULE_SWEDEN         0x05    // Lule Sami (Sweden)
#define SUBLANG_SAMI_SOUTHERN_NORWAY     0x06    // Southern Sami (Norway)
#define SUBLANG_SAMI_SOUTHERN_SWEDEN     0x07    // Southern Sami (Sweden)
#define SUBLANG_SAMI_SKOLT_FINLAND       0x08    // Skolt Sami (Finland)
#define SUBLANG_SAMI_INARI_FINLAND       0x09    // Inari Sami (Finland)
#define SUBLANG_SERBIAN_BOSNIA_HERZEGOVINA_LATIN    0x06 // Serbian (Bosnia and Herzegovina - Latin)
#define SUBLANG_SERBIAN_BOSNIA_HERZEGOVINA_CYRILLIC 0x07 // Serbian (Bosnia and Herzegovina - Cyrillic)
#define SUBLANG_SERBIAN_LATIN            0x02    // Serbian (Latin)
#define SUBLANG_SERBIAN_CYRILLIC         0x03    // Serbian (Cyrillic)
#define SUBLANG_SOTHO_NORTHERN_SOUTH_AFRICA 0x01    // Northern Sotho (South Africa)
#define SUBLANG_SPANISH                  0x01    // Spanish (Castilian)
#define SUBLANG_SPANISH_MEXICAN          0x02    // Spanish (Mexican)
#define SUBLANG_SPANISH_MODERN           0x03    // Spanish (Modern)
#define SUBLANG_SPANISH_GUATEMALA        0x04    // Spanish (Guatemala)
#define SUBLANG_SPANISH_COSTA_RICA       0x05    // Spanish (Costa Rica)
#define SUBLANG_SPANISH_PANAMA           0x06    // Spanish (Panama)
#define SUBLANG_SPANISH_DOMINICAN_REPUBLIC 0x07  // Spanish (Dominican Republic)
#define SUBLANG_SPANISH_VENEZUELA        0x08    // Spanish (Venezuela)
#define SUBLANG_SPANISH_COLOMBIA         0x09    // Spanish (Colombia)
#define SUBLANG_SPANISH_PERU             0x0a    // Spanish (Peru)
#define SUBLANG_SPANISH_ARGENTINA        0x0b    // Spanish (Argentina)
#define SUBLANG_SPANISH_ECUADOR          0x0c    // Spanish (Ecuador)
#define SUBLANG_SPANISH_CHILE            0x0d    // Spanish (Chile)
#define SUBLANG_SPANISH_URUGUAY          0x0e    // Spanish (Uruguay)
#define SUBLANG_SPANISH_PARAGUAY         0x0f    // Spanish (Paraguay)
#define SUBLANG_SPANISH_BOLIVIA          0x10    // Spanish (Bolivia)
#define SUBLANG_SPANISH_EL_SALVADOR      0x11    // Spanish (El Salvador)
#define SUBLANG_SPANISH_HONDURAS         0x12    // Spanish (Honduras)
#define SUBLANG_SPANISH_NICARAGUA        0x13    // Spanish (Nicaragua)
#define SUBLANG_SPANISH_PUERTO_RICO      0x14    // Spanish (Puerto Rico)
#define SUBLANG_SWEDISH                  0x01    // Swedish
#define SUBLANG_SWEDISH_FINLAND          0x02    // Swedish (Finland)
#define SUBLANG_URDU_PAKISTAN            0x01    // Urdu (Pakistan)
#define SUBLANG_URDU_INDIA               0x02    // Urdu (India)
#define SUBLANG_UZBEK_LATIN              0x01    // Uzbek (Latin)
#define SUBLANG_UZBEK_CYRILLIC           0x02    // Uzbek (Cyrillic)
#endif // LANG_NEUTRAL
#endif // _OT4XB_EXCLUDE_WINAPI_CONSTANTS
// -----------------------------------------------------------------------------------------------------------------
/*{{ note-id: com-helpers | title_: COM helpers of ot4xb.ch
   |: Small helpers for COM interop from Xbase++ code:

     - `__vtMissing__` - the 16-byte image of a VARIANT holding VT_ERROR / DISP_E_PARAMNOTFOUND (0x80020004):
       the value to pass for an omitted optional argument of an IDispatch call (Excel and the other Office
       automation servers want exactly that for every argument you leave out).
     - `__vtEmpty__` - the 16-byte image of an empty VARIANT (VT_EMPTY, all zero bytes).
     - `IUnknow.uuidof()`, `IDispatch.uuidof()`, `ISequentialStream.uuidof()`, `IStream.uuidof()` - pseudo-functions
       returning the IID of each interface as a binary UUID (UuidFromString of the well-known GUID), ready for
       {{ilink: <slug ot4xb_iunknow> OT4XB_IUNKNOW}}:QueryInterface(). }}*/
#define __vtMissing__  cHex2Bin( "0A000000000000000400028000000000" )
#define __vtEmpty__    ChrR(0,16)
#xtranslate IUnknow.uuidof() => UuidFromString("00000000-0000-0000-C000-000000000046")
#xtranslate IDispatch.uuidof() => UuidFromString("00020400-0000-0000-C000-000000000046")
#xtranslate ISequentialStream.uuidof() => UuidFromString("0C733A30-2A1C-11CE-ADE5-00AA0044773D")
#xtranslate IStream.uuidof() => UuidFromString("0000000C-0000-0000-C000-000000000046")
// -----------------------------------------------------------------------------------------------------------------
/*{{ function: ot4xb_dirty_dlgedit | _note_: the OT4XB_DDF_* flags and the OT4XB_DDN_* notification codes below are documented in the function }}*/
// ---- bits 0  - 1  MONITOR FLAGS ( MUTUALLY EXCLUSIVE )
#define OT4XB_DDF_MONITOR_DONTCARE   0x00000000    // DEFAULT
#define OT4XB_DDF_MONITOR_PRIMARY    0x00000001  // display in primary monitor
#define OT4XB_DDF_MONITOR_WINDOW     0x00000002  // display in Reference Window monitor
#define OT4XB_DDF_MONITOR_MOUSE      0x00000003  // display in mouse monitor
// ---- bit 2-3 ( MUTUALLY EXCLUSIVE )
#define OT4XB_DDF_DISPLAY_CENTERED   0x00000004
#define OT4XB_DDF_DISPLAY_MAXIMIZED  0x00000008
// ---- byte 1 coordinate system
#define OT4XB_DDF_COORD_SCREEN     0x00000000    // DEFAULT
// setting bit 0x10 or will reset monitor flags to OT4XB_DDF_MONITOR_DONTCARE
#define OT4XB_DDF_COORD_WINDOW     0x00000010
#define OT4XB_DDF_COORD_CLIENT     0x00000030
#define OT4XB_DDF_NOTASKBAR        0x00000100  // hide from task bar
#define OT4XB_DDF_CHILD            0x00000200  // hide from task bar
#define OT4XB_DDF_TITLE            0x00000800
#define OT4XB_DDF_DISABLEPARENT    0x00000400
#define OT4XB_DDF_CLIENT_EDGE      0x01000000  // draws a border arround the tab client window
// ----------
#define OT4XB_DDF_USETHREAD        0x00008000
#define OT4XB_DDF_TOP              0x00010000
#define OT4XB_DDF_DUMMYHIT         0x00020000
#define OT4XB_DDF_BTNTABSTOP       0x00040000
#define OT4XB_DDF_HOOKPARENT       0x00080000
// -----------
#define OT4XB_MSG_DIRTY_NOTIFY  "msg_845B1B1B_8F23_4D5C_80D6_CFBCEC3DC197"
#define OT4XB_DDN_CREATE_DLG       1
#define OT4XB_DDN_CREATE_TAB       2
#define OT4XB_DDN_CREATE_PAGE      3
#define OT4XB_DDN_CREATE_PGCON     4
#define OT4XB_DDN_CREATE_SAY       5
#define OT4XB_DDN_CREATE_CTRL      6
#define OT4XB_DDN_CREATE_BTN       7
#define OT4XB_DDN_BTNCLICK         8
// -----------------------------------------------------------------------------------------------------------------
/*{{ function: ot4xb_qloop | _note_: OT4XB_QLOOP_COMPILE_BLOCKS is documented in the nFlags parameter }}*/
#define OT4XB_QLOOP_COMPILE_BLOCKS  0x01000000
// -----------------------------------------------------------------------------------------------------------------
/*{{ note-id: hash-flags | title_: OT4XB_HASH flag constants (ot4xb.ch)
   |: The nFlags argument of the {{ilink: <slug ot4xb_hash> OT4XB_HASH}} methods is a combination (nOr) of these
     constants of ot4xb.ch:

     - `OT4XB_HASH_FLAGS_OUTPUT_HEX` 0x00000000
     - `OT4XB_HASH_FLAGS_OUTPUT_BIN` 0x00000001
     - `OT4XB_HASH_FLAGS_INPUT_STRING` 0x00000000
     - `OT4XB_HASH_FLAGS_INPUT_FILENAME` 0x00000010
     - `OT4XB_HASH_FLAGS_INPUT_HFILE` 0x00000020
     - `OT4XB_HASH_FLAGS_INPUT_START` 0x00000100
     - `OT4XB_HASH_FLAGS_INPUT_MAX_BYTES` 0x00000200
     - `OT4XB_HASH_FLAGS_INPUT_RESTORE_POS` 0x00001000
     - `OT4XB_HASH_FLAGS_GRANULARITY` 0x00010000 }}*/
#define OT4XB_HASH_FLAGS_OUTPUT_HEX             0x00000000
#define OT4XB_HASH_FLAGS_OUTPUT_BIN             0x00000001
#define OT4XB_HASH_FLAGS_INPUT_STRING           0x00000000
#define OT4XB_HASH_FLAGS_INPUT_FILENAME         0x00000010
#define OT4XB_HASH_FLAGS_INPUT_HFILE            0x00000020
#define OT4XB_HASH_FLAGS_INPUT_START            0x00000100
#define OT4XB_HASH_FLAGS_INPUT_MAX_BYTES        0x00000200
#define OT4XB_HASH_FLAGS_INPUT_RESTORE_POS      0x00001000
#define OT4XB_HASH_FLAGS_GRANULARITY            0x00010000
// -----------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------
#define EXPANDO_FORMAT_DEBUG                 1
#define EXPANDO_FORMAT_FLAT_ARRAY_KV_ITEMS    0x00000010
#define EXPANDO_FORMAT_ENFORCE_FLAT           0x00000020
#define EXPANDO_FORMAT_PRETTY                 0x01000000
#xtranslate EXPANDO_FORMAT_ND_PRECISSION( <x> )   => nLShift( nAnd( <x> , 0x0F ) , 16 )
#define EXPANDO_FORMAT_ND_FIXED               0x00100000
#define EXPANDO_FORMAT_ND_MINIMAL             0x00200000
// -----------------------------------------------------------------------------------------------------------------
/*{{ note-id: sql-type-flags | title_: SQL escape type flags (ot4xb_sql_type_flag.*)
   |: The `ot4xb_sql_type_flag.NAME` pseudo-constants of ot4xb.ch name the bits of the type flags parameter:

     - `ot4xb_sql_type_flag.none` 0
     - `ot4xb_sql_type_flag.LTrim` 0x000001
     - `ot4xb_sql_type_flag.RTrim` 0x000002
     - `ot4xb_sql_type_flag.AllTrim` 0x000003
     - `ot4xb_sql_type_flag.wildcard_escape` 0x000008
     - `ot4xb_sql_type_flag.LeftAlign` 0x000010
     - `ot4xb_sql_type_flag.RightAlign` 0x000020
     - `ot4xb_sql_type_flag.Truncate` 0x000100
     - `ot4xb_sql_type_flag.ToUtf8` 0x001000
     - `ot4xb_sql_type_flag.NotNull` 0x010000
     - `ot4xb_sql_type_flag.OvNull` 0x100000
     - `ot4xb_sql_type_flag.OvMin` 0x200000
     - `ot4xb_sql_type_flag.OvMax` 0x400000
     - `ot4xb_sql_type_flag.OvZero` 0x800000 }}*/
#xtranslate ot4xb_sql_type_flag.none                 =>    ( 0         ) 
#xtranslate ot4xb_sql_type_flag.LTrim                =>    ( 0x000001  ) 
#xtranslate ot4xb_sql_type_flag.RTrim                =>    ( 0x000002  ) 
#xtranslate ot4xb_sql_type_flag.AllTrim              =>    ( 0x000003  ) 
#xtranslate ot4xb_sql_type_flag.wildcard_escape      =>    ( 0x000008  ) 
#xtranslate ot4xb_sql_type_flag.LeftAlign            =>    ( 0x000010  ) 
#xtranslate ot4xb_sql_type_flag.RightAlign           =>    ( 0x000020  ) 
#xtranslate ot4xb_sql_type_flag.Truncate             =>    ( 0x000100  ) 
#xtranslate ot4xb_sql_type_flag.ToUtf8               =>    ( 0x001000  ) 
#xtranslate ot4xb_sql_type_flag.NotNull              =>    ( 0x010000  ) 
#xtranslate ot4xb_sql_type_flag.OvNull               =>    ( 0x100000  ) 
#xtranslate ot4xb_sql_type_flag.OvMin                =>    ( 0x200000  ) 
#xtranslate ot4xb_sql_type_flag.OvMax                =>    ( 0x400000  ) 
#xtranslate ot4xb_sql_type_flag.OvZero               =>    ( 0x800000  ) 


/*{{ note-id: sql-types | title_: SQL value types (ot4xb_sql_type.*)
   |: The `ot4xb_sql_type.NAME` pseudo-constants of ot4xb.ch name the SQL type codes:

     - `ot4xb_sql_type.Invalid` 0
     - `ot4xb_sql_type.TinyInt` 1
     - `ot4xb_sql_type.SmallInt` 2
     - `ot4xb_sql_type.MediumInt` 3
     - `ot4xb_sql_type.Int` 4
     - `ot4xb_sql_type.BigInt` 5
     - `ot4xb_sql_type.Decimal` 6
     - `ot4xb_sql_type.Float` 7
     - `ot4xb_sql_type.Double` 8
     - `ot4xb_sql_type.Bit` 9
     - `ot4xb_sql_type.Date` 10
     - `ot4xb_sql_type.Time` 11
     - `ot4xb_sql_type.DateTime` 12
     - `ot4xb_sql_type.TimeStamp` 13
     - `ot4xb_sql_type.Year` 14
     - `ot4xb_sql_type.Char` 15
     - `ot4xb_sql_type.VarChar` 16
     - `ot4xb_sql_type.Binary` 17
     - `ot4xb_sql_type.VarBinary` 18
     - `ot4xb_sql_type.TinyBlob` 19
     - `ot4xb_sql_type.Blob` 20
     - `ot4xb_sql_type.MediumBlob` 21
     - `ot4xb_sql_type.LongBlob` 22
     - `ot4xb_sql_type.TinyText` 23
     - `ot4xb_sql_type.Text` 24
     - `ot4xb_sql_type.MediumText` 25
     - `ot4xb_sql_type.LongText` 26
     - `ot4xb_sql_type.Enum` 27
     - `ot4xb_sql_type.Set` 28
     - `ot4xb_sql_type.Json` 29 }}*/
#xtranslate ot4xb_sql_type.Invalid      =>  (  0  )
#xtranslate ot4xb_sql_type.TinyInt      =>  (  1  )
#xtranslate ot4xb_sql_type.SmallInt     =>  (  2  )
#xtranslate ot4xb_sql_type.MediumInt    =>  (  3  )
#xtranslate ot4xb_sql_type.Int          =>  (  4  )
#xtranslate ot4xb_sql_type.BigInt       =>  (  5  )
#xtranslate ot4xb_sql_type.Decimal      =>  (  6  )
#xtranslate ot4xb_sql_type.Float        =>  (  7  )
#xtranslate ot4xb_sql_type.Double       =>  (  8  )
#xtranslate ot4xb_sql_type.Bit          =>  (  9  )
#xtranslate ot4xb_sql_type.Date         =>  ( 10  )
#xtranslate ot4xb_sql_type.Time         =>  ( 11  )
#xtranslate ot4xb_sql_type.DateTime     =>  ( 12  )
#xtranslate ot4xb_sql_type.TimeStamp    =>  ( 13  )
#xtranslate ot4xb_sql_type.Year         =>  ( 14  )
#xtranslate ot4xb_sql_type.Char         =>  ( 15  )
#xtranslate ot4xb_sql_type.VarChar      =>  ( 16  )
#xtranslate ot4xb_sql_type.Binary       =>  ( 17  )
#xtranslate ot4xb_sql_type.VarBinary    =>  ( 18  )
#xtranslate ot4xb_sql_type.TinyBlob     =>  ( 19  )
#xtranslate ot4xb_sql_type.Blob         =>  ( 20  )
#xtranslate ot4xb_sql_type.MediumBlob   =>  ( 21  )
#xtranslate ot4xb_sql_type.LongBlob     =>  ( 22  )
#xtranslate ot4xb_sql_type.TinyText     =>  ( 23  )
#xtranslate ot4xb_sql_type.Text         =>  ( 24  )
#xtranslate ot4xb_sql_type.MediumText   =>  ( 25  )
#xtranslate ot4xb_sql_type.LongText     =>  ( 26  )
#xtranslate ot4xb_sql_type.Enum         =>  ( 27  )
#xtranslate ot4xb_sql_type.Set          =>  ( 28  )
#xtranslate ot4xb_sql_type.Json         =>  ( 29  )

// -----------------------------------------------------------------------------------------------------------------
/*{{ note-id: regex-options | title_: Regular expression option flags (ot4xb_regex_option.*)
   |: The `ot4xb_regex_option.NAME` pseudo-constants of ot4xb.ch name the bits of the regex flag parameters.

     Syntax and compile options (nRegexFlags; the grammar bits are exclusive, `Gmask` masks them):
     - `ot4xb_regex_option.ECMAScript` 0x01
     - `ot4xb_regex_option.basic` 0x02
     - `ot4xb_regex_option.extended` 0x04
     - `ot4xb_regex_option.awk` 0x08
     - `ot4xb_regex_option.grep` 0x10
     - `ot4xb_regex_option.egrep` 0x20
     - `ot4xb_regex_option.Gmask` 0x3F
     - `ot4xb_regex_option.icase` 0x0100
     - `ot4xb_regex_option.nosubs` 0x0200
     - `ot4xb_regex_option.optimize` 0x0400
     - `ot4xb_regex_option.collate` 0x0800

     Match and format options (nRegexMatchFlags):
     - `ot4xb_regex_option.match_default` 0x0000
     - `ot4xb_regex_option.match_not_bol` 0x0001
     - `ot4xb_regex_option.match_not_eol` 0x0002
     - `ot4xb_regex_option.match_not_bow` 0x0004
     - `ot4xb_regex_option.match_not_eow` 0x0008
     - `ot4xb_regex_option.match_any` 0x0010
     - `ot4xb_regex_option.match_not_null` 0x0020
     - `ot4xb_regex_option.match_continuous` 0x0040
     - `ot4xb_regex_option.match_prev_avail` 0x0100
     - `ot4xb_regex_option.format_default` 0x0000
     - `ot4xb_regex_option.format_sed` 0x0400
     - `ot4xb_regex_option.format_no_copy` 0x0800
     - `ot4xb_regex_option.format_first_only` 0x1000
     - `ot4xb_regex_option.Match_not_null` 0x2000
     - `ot4xb_regex_option.Skip_zero_length` 0x4000

     The same bit values apply to the C exports called through the `@dll:function()` notation:
     `@ot4xb:ot4xb_regex_match( cPattern, cString, nRegexFlags, nRegexMatchFlags )` and
     `@ot4xb:ot4xb_regex_replace( ... )` ({{ilink: <c-function ot4xb_regex_match> ot4xb_regex_match}},
     {{ilink: <c-function ot4xb_regex_replace> ot4xb_regex_replace}}). }}*/
#xtranslate ot4xb_regex_option.ECMAScript => (0x01)
#xtranslate ot4xb_regex_option.basic      => (0x02)
#xtranslate ot4xb_regex_option.extended   => (0x04)
#xtranslate ot4xb_regex_option.awk        => (0x08)
#xtranslate ot4xb_regex_option.grep       => (0x10)
#xtranslate ot4xb_regex_option.egrep      => (0x20)
#xtranslate ot4xb_regex_option.Gmask      => (0x3F)
#xtranslate ot4xb_regex_option.icase      => (0x0100)
#xtranslate ot4xb_regex_option.nosubs     => (0x0200)
#xtranslate ot4xb_regex_option.optimize   => (0x0400)
#xtranslate ot4xb_regex_option.collate    => (0x0800)
//----------------------------------------------------------------------------------------------------------------------

#xtranslate ot4xb_regex_option.match_default      => 0x0000
#xtranslate ot4xb_regex_option.match_not_bol      => 0x0001
#xtranslate ot4xb_regex_option.match_not_eol      => 0x0002
#xtranslate ot4xb_regex_option.match_not_bow      => 0x0004
#xtranslate ot4xb_regex_option.match_not_eow      => 0x0008
#xtranslate ot4xb_regex_option.match_any          => 0x0010
#xtranslate ot4xb_regex_option.match_not_null     => 0x0020
#xtranslate ot4xb_regex_option.match_continuous   => 0x0040
#xtranslate ot4xb_regex_option.match_prev_avail   => 0x0100
#xtranslate ot4xb_regex_option.format_default     => 0x0000
#xtranslate ot4xb_regex_option.format_sed         => 0x0400
#xtranslate ot4xb_regex_option.format_no_copy     => 0x0800
#xtranslate ot4xb_regex_option.format_first_only  => 0x1000
#xtranslate ot4xb_regex_option.Match_not_null     => 0x2000
#xtranslate ot4xb_regex_option.Skip_zero_length   => 0x4000
// -----------------------------------------------------------------------------------------------------------------
#ifdef _OT4XB_MAP_WAPIST_FUNC_
#include "ot4xb_wapist_map.ch"
#endif
// -----------------------------------------------------------------------------------------------------------------
#endif // _OT4XB_CH_
