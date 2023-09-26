//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifndef _OT4XB_CH_
#define _OT4XB_CH_
#pragma library ("ot4xb.lib")
// ---------------------------------------------------------------------------
#xcommand SWAP  <a> , <b> 	=> TlsStackPush(<a>) ;
							       ; <a> := <b>      ;
							       ; <b> := TlsStackPop()

// ---------------------------------------------------------------------------
#xcommand OT4XB ASSERT HEADER => ;
if ( ot4xb() \< "001.006.004.076")  );
;   TlsStackPush(Error():New());
;   TlsStackTop():severity := 2;
;   TlsStackTop():description := "ot4xb header file require dll version 1.6.4.76 or above" ;
;   Eval( ErrorBlock() , TlsStackPop() );
;end

#ifndef CRLF
#define CRLF              (Chr(13)+Chr(10))
#endif
#ifdef OT4XB_1_6_2_COMPAT
#xcommand DEFAULT <uVar1> := <uVal1> => <uVar1> := iif( <uVar1> == NIL, <uVal1>, <uVar1> )
#else
#xcommand DEFAULT <uVar1> := <uVal1> => ;
if <uVar1> == NIL ;
;  <uVar1> := <uVal1> ;
;end
#endif
#xtranslate BYNAME <V> [, <VN> ]     => ::<V> := <V> [; ::<VN> := <VN> ]
#xtranslate BYNAME <V> DEFAULT <Val> => ::<V> := iif(<V> == NIL , <Val> , <V> )
#xtranslate BYNAME <V> IFNONIL =>  if <V> != NIL ; ::<V> := <V> ;  end
// #define MAX(x,y)  ( iif( x > y , x , y) )
// #define MIN(x,y)  ( iif( x < y , x , y) )
#xtranslate StrTrim(<n>)   =>  LTrim(Str(<n>))
// --------------------------------------------------------------------------- 
#xtranslate _OT4XB_EXPANDO_FORMAT_DEBUG                  => 1
#xtranslate _OT4XB_EXPANDO_FORMAT_PRETTY                 => 0x01000000
#xtranslate _OT4XB_EXPANDO_FORMAT_ND_PRECISSION( <x> )   => nLShift( nAnd( <x> , 0x0F ) , 16 )
#xtranslate _OT4XB_EXPANDO_FORMAT_ND_FIXED               => 0x00100000
#xtranslate _OT4XB_EXPANDO_FORMAT_ND_MINIMAL             => 0x00200000
// --------------------------------------------------------------------------- 
#pragma Map( UUIDCREATE, "_UUIDCREATE" )
//----------------------------------------------------------------------------------------------------------------------
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
#if OT4XB_ASSERT_LEVEL > 0
#xtranslate _Assert_Range_(<v>,<min>,<max>) => iif( ((<v> \> <max>) .or. (<v> \< <min>)),;
            ( TlsStackPush(Error():New()) ,TlsStackTop():severity := 2,;
              TlsStackTop():description := "Value out of range" ,;
              Eval(ErrorBlock(),TlsStackPop() ) ),<v>)
#else
#xtranslate _Assert_Range_(<v>,<min>,<max>) => NIL
#endif
// -----------------------------------------------------------------------------------------------------------------
#if OT4XB_ASSERT_LEVEL > 1
#xtranslate _Assert_fp_(<fp>) => iif( <fp> == 0,;
            ( TlsStackPush(Error():New()) ,TlsStackTop():severity := 2,;
              TlsStackTop():description := "Function is not declared" ,;
              Eval(ErrorBlock(),TlsStackPop() )),)
#else
#xtranslate _Assert_fp_(<fp>) => NIL
#endif
//----------------------------------------------------------------------------------------------------------------------
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
#xtranslate GwstArrayNext( <o> ) => <o>:_link_( <o>:_addressof_() + <o>:_sizeof_(),.F.)
#xtranslate GwstArrayPrev( <o> ) => <o>:_link_( <o>:_addressof_() - <o>:_sizeof_(),.F.)
//----------------------------------------------------------------------------------------------------------------------
#xtranslate GWSTSKIPBYTES( <n> ) => ooo:_GwstSkipBytes( <n> )
#xtranslate GWSTGETOFFSET() => ooo:_GwstGetOffset()
#xtranslate GWSTSETOFFSET( <n> ) => ooo:_GwstSetOffset( <n> )
#xtranslate GWSTALIGNNEXTMEMBER( <n> ) => ooo:_GwstAlignNextMember( <n> )
#xtranslate GWSTBACK() => ooo:_GwstBack()
#xcommand   GWSTBACK   => GWSTBACK()
#xtranslate GWSTPARENT( [ <p1> ] )  => ooo:_GwstParent( [ <p1>() ] )
#xtranslate ADDGWSTSTYLEMEMBERS() => ooo:AddGwstStyleMembers()
// -----------------------------------------------------------------------------------------------------------------
#xtranslate gwst_sizeof( <st> ) => (<st>():_mc__size_)
#xtranslate SET VARIANT TO STRING LOCALE INVARIANT => (@ot4xb:ot4xb_set_tls_variant_to_string_locale_invariant())
#xtranslate SET VARIANT TO STRING LOCALE DEFAULT   => (@ot4xb:ot4xb_set_tls_variant_to_string_locale(0))
//-----------------------------------------------------------------------------------------------------------------------
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
#xcommand BEGIN DYNAMIC CLASS <Tag> [ FROM <p1> [, <pN>] ] [<*more*>] => ;
          function <Tag>() ;
          ; NS_BEGIN DYNAMIC CLASS <Tag> [ FROM <p1> [, <pN>] ] [<more>]
//----------------------------------------------------------------------------------------------------------------------
#xcommand END DYNAMIC CLASS => oClass := ooo:Create() ; ooo:Destroy() ; return oClass
//-----------------------------------------------------------------------------------------------------------------------
#xcommand DYNAMIC VAR                <cName>  [FLAGS <nExtra> ]    => ooo:_Var(<(cName)> [, <nExtra> ])
#xcommand DYNAMIC CLASS VAR          <cName>  [FLAGS <nExtra> ]    => ooo:_ClassVar(<(cName)> [, <nExtra> ])
#xcommand DYNAMIC SHARED CLASS VAR   <cName>  [FLAGS <nExtra> ]    => ooo:_SharedClassVar(<(cName)> [, <nExtra> ])
//-----------------------------------------------------------------------------------------------------------------------
#xcommand DYNAMIC PROPERTY           <cName>  BLOCK <uBlock>       => ooo:_Property( <(cName)> , <uBlock> )
#xcommand DYNAMIC CLASS PROPERTY     <cName>  BLOCK <uBlock>       => ooo:_ClassProperty( <(cName)> , <uBlock> )
#xcommand DYNAMIC READONLY PROPERTY           <cName>  BLOCK <uBlock>       => ooo:_ROProperty( <(cName)> , <uBlock> )
#xcommand DYNAMIC READONLY CLASS PROPERTY     <cName>  BLOCK <uBlock>       => ooo:_ROClassProperty( <(cName)> , <uBlock> )
#xcommand DYNAMIC WRITEONLY PROPERTY           <cName>  BLOCK <uBlock>       => ooo:_WOProperty( <(cName)> , <uBlock> )
#xcommand DYNAMIC WRITEONLY CLASS PROPERTY     <cName>  BLOCK <uBlock>       => ooo:_WOClassProperty( <(cName)> , <uBlock> )
//-----------------------------------------------------------------------------------------------------------------------
#xcommand DYNAMIC  PROPERTY <cc>  READ <rr> WRITE <ww> => ;
                   ooo:_Property(<(cc)>, {|Self,v|iif( PCount() > 1 , <ww> , <rr> ) } )

#xcommand DYNAMIC  CLASS PROPERTY <cc>  READ <rr> WRITE <ww> => ;
                   ooo:_ClassProperty(<(cc)>, {|Self,v|iif( PCount() > 1 , <ww> , <rr> ) } )
//-----------------------------------------------------------------------------------------------------------------------
#xcommand DYNAMIC  PROPERTY <cc>  READ <rr>  => ;
                   ooo:_ROProperty(<(cc)>, {|Self| <rr>  } )

#xcommand DYNAMIC  CLASS PROPERTY <cc>  READ <rr> => ;
                   ooo:_ROClassProperty(<(cc)>, {|Self| <rr> } )
//-----------------------------------------------------------------------------------------------------------------------
#xcommand DYNAMIC  PROPERTY <cc>  WRITE <ww> => ;
                   ooo:_WOProperty(<(cc)>, {|Self,v| <ww> } )

#xcommand DYNAMIC  CLASS PROPERTY <cc>  WRITE <ww> => ;
                   ooo:_WOClassProperty(<(cc)>, {|Self,v| <ww> } )
//-----------------------------------------------------------------------------------------------------------------------
#xcommand DYNAMIC PROPERTY                  <cName>  COMPILE <ss>  => ooo:_Property( <(cName)> , (&(<ss>))  )
#xcommand DYNAMIC CLASS PROPERTY            <cName>  COMPILE <ss>  => ooo:_ClassProperty( <(cName)> , (&(<ss>)) )
#xcommand DYNAMIC READONLY PROPERTY         <cName>  COMPILE <ss>  => ooo:_ROProperty( <(cName)> ,  (&(<ss>))  )
#xcommand DYNAMIC READONLY CLASS PROPERTY   <cName>  COMPILE <ss>  => ooo:_ROClassProperty( <(cName)> ,  (&(<ss>)) )
#xcommand DYNAMIC WRITEONLY PROPERTY        <cName>  COMPILE <ss>  => ooo:_WOProperty( <(cName)> ,  (&(<ss>))  )
#xcommand DYNAMIC WRITEONLY CLASS PROPERTY  <cName>  COMPILE <ss>  => ooo:_WOClassProperty( <(cName)> ,  (&(<ss>))  )
//-----------------------------------------------------------------------------------------------------------------------

#xcommand DYNAMIC PROPERTY                  <cName>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          DYNAMIC PROPERTY                  <cName>  COMPILE cPrintf( <(ss)> ,<p1> [,<pN>])
#xcommand DYNAMIC CLASS PROPERTY            <cName>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          DYNAMIC CLASS PROPERTY            <cName>  COMPILE cPrintf( <(ss)> ,<p1> [,<pN>])
#xcommand DYNAMIC READONLY PROPERTY         <cName>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          DYNAMIC READONLY PROPERTY         <cName>  COMPILE cPrintf( <(ss)> ,<p1> [,<pN>])
#xcommand DYNAMIC READONLY CLASS PROPERTY   <cName>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          DYNAMIC READONLY CLASS PROPERTY   <cName>  COMPILE cPrintf( <(ss)> ,<p1> [,<pN>])
#xcommand DYNAMIC WRITEONLY PROPERTY        <cName>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          DYNAMIC WRITEONLY PROPERTY        <cName>  COMPILE cPrintf( <(ss)> ,<p1> [,<pN>])
#xcommand DYNAMIC WRITEONLY CLASS PROPERTY  <cName>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          DYNAMIC WRITEONLY CLASS PROPERTY  <cName>  COMPILE cPrintf( <(ss)> ,<p1> [,<pN>])
//-----------------------------------------------------------------------------------------------------------------------

#xcommand DYNAMIC  PROPERTY <cc>  COMPILE READ <rr> WRITE <ww> => ;
          DYNAMIC  PROPERTY <cc>  COMPILE "{|Self,v|iif( PCount() > 1 ," + <ww> +"," +  <rr> +")}"

#xcommand DYNAMIC  CLASS PROPERTY <cc>  COMPILE READ <rr> WRITE <ww> => ;
          DYNAMIC  CLASS PROPERTY <cc>  COMPILE "{|Self,v|iif( PCount() > 1 ," + <ww> +"," +  <rr> +")}"

#xcommand DYNAMIC  PROPERTY <cc>  COMPILE READ <rr>  => ;
          DYNAMIC  READONLY PROPERTY <cc>  COMPILE "{|Self|" + <rr> +"}"

#xcommand DYNAMIC  CLASS PROPERTY <cc>  COMPILE READ <rr> => ;
          DYNAMIC  READONLY CLASS PROPERTY <cc>  COMPILE "{|Self|" + <rr> +"}"

#xcommand DYNAMIC  PROPERTY <cc>  COMPILE WRITE <ww> => ;
          DYNAMIC  WRITEONLY PROPERTY <cc>  COMPILE "{|Self,v|" + <ww> +"}"

#xcommand DYNAMIC  CLASS PROPERTY <cc>  COMPILE WRITE <ww> => ;
          DYNAMIC  WRITEONLY CLASS PROPERTY <cc>  COMPILE "{|Self,v|" + <ww> +"}"

//-----------------------------------------------------------------------------------------------------------------------


#xcommand DYNAMIC  PROPERTY <cc>  COMPILE READ <rr> WRITE <ww> INSERT <p1> [, <pN>] => ;
          DYNAMIC  PROPERTY <cc>  COMPILE "{|Self,v|iif( PCount() > 1 ," + <ww> +"," +  <rr> +")}" ;
          INSERT <p1> [, <pN>]

#xcommand DYNAMIC  CLASS PROPERTY <cc>  COMPILE READ <rr> WRITE <ww> INSERT <p1> [, <pN>] => ;
          DYNAMIC  CLASS PROPERTY <cc>  COMPILE "{|Self,v|iif( PCount() > 1 ," + <ww> +"," +  <rr> +")}" ;
          INSERT <p1> [, <pN>]

#xcommand DYNAMIC  PROPERTY <cc>  COMPILE READ <rr>  INSERT <p1> [, <pN>]  => ;
          DYNAMIC  READONLY PROPERTY <cc>  COMPILE "{|Self|" + <rr> +"}" INSERT <p1> [, <pN>]

#xcommand DYNAMIC  CLASS PROPERTY <cc>  COMPILE READ <rr> INSERT <p1> [, <pN>]  => ;
          DYNAMIC  READONLY CLASS PROPERTY <cc>  COMPILE "{|Self|" + <rr> +"}" INSERT <p1> [, <pN>]

#xcommand DYNAMIC  PROPERTY <cc>  COMPILE WRITE <ww> INSERT <p1> [, <pN>]  => ;
          DYNAMIC  WRITEONLY PROPERTY <cc>  COMPILE "{|Self,v|" + <ww> +"}" INSERT <p1> [, <pN>]

#xcommand DYNAMIC  CLASS PROPERTY <cc>  COMPILE WRITE <ww> INSERT <p1> [, <pN>]  => ;
          DYNAMIC  WRITEONLY CLASS PROPERTY <cc>  COMPILE "{|Self,v|" + <ww> +"}" INSERT <p1> [, <pN>]
//-----------------------------------------------------------------------------------------------------------------------

#xcommand DYNAMIC PROPERTY <cc>  IS MASK <mask> OF <var> => ;
          DYNAMIC  PROPERTY <cc>  ;
          READ lAnd( ::<var> , <mask> ) ;
          WRITE (  ::<var> := iif(v,nOr( ::<var>,<mask>),nAndNot(::<var>,<mask>)) )

#xcommand DYNAMIC PROPERTY <cc>  IS MASK <mask> OF <var> READONLY => ;
          DYNAMIC  PROPERTY <cc>  ;
          READ lAnd( ::<var> , <mask> )

#xcommand DYNAMIC PROPERTY <cc>  IS CONSTANT <val> => DYNAMIC  PROPERTY <cc> READ <val>
//----------------------------------------------------------------------------------------------------------------------
#xcommand DYNAMIC CLASS PROPERTY <cc>  IS MASK <mask> OF <var> => ;
          DYNAMIC  CLASS PROPERTY <cc>  ;
          READ lAnd( ::<var> , <mask> ) ;
          WRITE (  ::<var> := iif(v,nOr( ::<var>,<mask>),nAndNot(::<var>,<mask>)) )

#xcommand DYNAMIC CLASS PROPERTY <cc>  IS MASK <mask> OF <var> READONLY => ;
          DYNAMIC  CLASS PROPERTY <cc>  ;
          READ lAnd( ::<var> , <mask> )

#xcommand DYNAMIC CLASS PROPERTY <cc>  IS CONSTANT <val> => DYNAMIC  CLASS PROPERTY <cc> READ <val>
//-----------------------------------------------------------------------------------------------------------------------
#xcommand DYNAMIC METHOD             <cName>  BLOCK <uBlock>       => ooo:_Method( <(cName)> , <uBlock> )

#xcommand DYNAMIC METHOD <cc>  COMPILE <ss>   => ;
          ooo:_Method( <(cc)> , (&( <(ss)>)) )

#xcommand DYNAMIC METHOD <cc>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          ooo:_Method( <(cc)> , (&( cPrintf( <(ss)> ,<p1> [,<pN>]))) )

#xcommand DYNAMIC CLASS METHOD       <cName>  BLOCK <uBlock>       => ooo:_ClassMethod( <(cName)> , <uBlock> )

#xcommand DYNAMIC CLASS METHOD <cc>  COMPILE <ss>   => ;
          ooo:_ClassMethod( <(cc)> , (&( <(ss)>)) )

#xcommand DYNAMIC CLASS METHOD <cc>  COMPILE <ss> INSERT <p1> [, <pN>]  => ;
          ooo:_ClassMethod( <(cc)> , (&( cPrintf( <(ss)> ,<p1> [,<pN>]))) )

//-----------------------------------------------------------------------------------------------------------------------
#xcommand NS_BEGIN STRUCTURE <Tag> [EXTENDING <super> ]  [<*more*>] => ;
          NS_BEGIN DYNAMIC CLASS <Tag> [<more>] ;
          ; GWSTPARENT( [ <super> ] )
//-----------------------------------------------------------------------------------------------------------------------
#xcommand BEGIN STRUCTURE <Tag> [EXTENDING <super> ]  [<*more*>] => ;
          function <Tag>() ;
          ; NS_BEGIN STRUCTURE <Tag> [EXTENDING <super> ]  [<more>]
//----------------------------------------------------------------------------------------------------------------------
#xcommand INLINE CLASS STRUCTURE <Tag> [EXTENDING <super> ]  [<*more*>] => ;
          INLINE CLASS METHOD <Tag>() ;
          ; NS_BEGIN STRUCTURE ( ::ClassName() + <(Tag)> + "_st") [EXTENDING <super> ]  [<more>]
// -----------------------------------------------------------------------------------------------------------------
#xcommand INLINE DYNAMIC CLASS <Tag> [ FROM <p1> [, <pN>] ]  [<*more*>] => ;
          INLINE CLASS METHOD <Tag>() ;
          ; NS_BEGIN DYNAMIC CLASS ( ::ClassName() + "_" + <(Tag)> + "_cls") [ FROM <p1> [, <pN>] ] [<more>]
//-----------------------------------------------------------------------------------------------------------------------
#xcommand END STRUCTURE => END DYNAMIC CLASS
//----------------------------------------------------------------------------------------------------------------------
#xtranslate MEMBER @ FILETIME <m> => ooo:_Child( <(m)> , FILETIME64() )
#xcommand MEMBER @ <cls> <m> => ooo:_Child( <(m)> , <cls>() )
//----------------------------------------------------------------------------------------------------------------------
#xcommand BEGIN UNION => ooo:_GwstBeginUnion()
#xcommand END UNION   => ooo:_GwstEndUnion()
//----------------------------------------------------------------------------------------------------------------------
#xcommand MEMBER DWORDNET       <m> => ooo:_Member_DWordNet( <(m)> )
#xcommand MEMBER WORDNET        <m> => ooo:_Member_WordNet( <(m)> )
//----------------------------------------------------------------------------------------------------------------------
#xcommand MEMBER BOOL           <m> => ooo:_Member_Bool( <(m)> )
#xcommand MEMBER BYTE           <m> => ooo:_Member_Byte( <(m)> )
#xcommand MEMBER U_INT8         <m> => ooo:_Member_Byte( <(m)> )
#xcommand MEMBER WORD           <m> => ooo:_Member_Word( <(m)> )
#xcommand MEMBER INT16          <m> => ooo:_Member_Int16( <(m)> )
#xcommand MEMBER U_INT16        <m> => ooo:_Member_Word( <(m)> )
#xcommand MEMBER SHORT          <m> => ooo:_Member_Short( <(m)> )
#xcommand MEMBER DWORD          <m> => ooo:_Member_DWord( <(m)> )
#xcommand MEMBER S_INT32        <m> => ooo:_Member_DWord( <(m)> )
#xcommand MEMBER ULONG          <m> => ooo:_Member_ULong( <(m)> )
#xcommand MEMBER LONG           <m> => ooo:_Member_Long( <(m)> )
#xcommand MEMBER UINT           <m> => ooo:_Member_UInt( <(m)> )
#xcommand MEMBER INT            <m> => ooo:_Member_Int( <(m)> )
#xcommand MEMBER ENUM           <m> => ooo:_Member_Int( <(m)> )
#xcommand MEMBER INT32          <m> => ooo:_Member_Int32( <(m)> )
#xcommand MEMBER LPARAM         <m> => ooo:_Member_LParam( <(m)> )
#xcommand MEMBER WPARAM         <m> => ooo:_Member_WParam( <(m)> )
#xcommand MEMBER POINTER        <m> => ooo:_Member_Pointer( <(m)> )
#xcommand MEMBER POINTER32      <m> => ooo:_Member_Pointer32( <(m)> )
#xcommand MEMBER HANDLE         <m> => ooo:_Member_Handle( <(m)> )
#xcommand MEMBER HWND           <m> => ooo:_Member_HWND( <(m)> )
#xcommand MEMBER HDC            <m> => ooo:_Member_HDC( <(m)> )
#xcommand MEMBER PCLIPVAR       <m> => ooo:_Member_Xbase( <(m)> )
#xcommand MEMBER PXBASEVAR      <m> => ooo:_Member_Xbase( <(m)> )
#xcommand MEMBER CODEBLOCK      <m> => ooo:_Member_Xbase( <(m)> )
#xcommand MEMBER LPXBASE        <m> => ooo:_Member_Xbase( <(m)> )
#xcommand MEMBER DWORD64        <m> => ooo:_Member_DWord64( <(m)> )
#xcommand MEMBER DOUBLE         <m> => ooo:_Member_Double( <(m)> )
#xcommand MEMBER FLOAT          <m> => ooo:_Member_Float( <(m)> )
#xcommand MEMBER LPSTR          <m> => ooo:_Member_LPSTR( <(m)> )
#xcommand MEMBER DYNSZ          <m> => ooo:_Member_DYNSZ( <(m)> )
#xcommand MEMBER XDATE          <m> => ooo:_Member_XDate( <(m)> )
//----------------------------------------------------------------------------------------------------------------------
#xcommand MEMBER S_INT8       <m> => ooo:_Member_SINT8( <(m)> )
#xcommand MEMBER S_INT16      <m> => ooo:_Member_SINT16( <(m)> )
#xcommand MEMBER U_INT32      <m> => ooo:_Member_UINT32( <(m)> )
#xcommand MEMBER N_INT64      <m> => ooo:_Member_NINT64( <(m)> )
#xcommand MEMBER BYTEBOOL     <m> => ooo:_Member_ByteBool( <(m)> )
//----------------------------------------------------------------------------------------------------------------------
#xtranslate DYNAMIC BITFIELD <f> FROM BYTE <m> OFFSET <sh> BITS <sz> ;
            =>;
            DYNAMIC PROPERTY <f> BLOCK  {|s,v| iif(PCount() > 1,;
                    s:<m> := @ot4xb:_b1_bf_set_(s:<m>,<sh>,<sz>,v) ,;
                  @ot4xb:_b1_bf_get_(s:<m>,<sh>,<sz>) )}
//----------------------------------------------------------------------------------------------------------------------
#xtranslate DYNAMIC BITFIELD <f> FROM WORD <m> OFFSET <sh> BITS <sz> ;
            =>;
            DYNAMIC PROPERTY <f> BLOCK  {|s,v| iif(PCount() > 1,;
                    s:<m> := @ot4xb:_w_bf_set_(s:<m>,<sh>,<sz>,v) ,;
                  @ot4xb:_w_bf_get_(s:<m>,<sh>,<sz>) )}
//----------------------------------------------------------------------------------------------------------------------
#xtranslate DYNAMIC BITFIELD <f> FROM DWORD <m> OFFSET <sh> BITS <sz> ;
            =>;
            DYNAMIC PROPERTY <f> BLOCK  {|s,v| iif(PCount() > 1,;
                    s:<m> := @ot4xb:_dw_bf_set_(s:<m>,<sh>,<sz>,v) ,;
                  @ot4xb:_dw_bf_get_(s:<m>,<sh>,<sz>) )}
//----------------------------------------------------------------------------------------------------------------------
#xcommand MEMBER LPSTR  <m> DYNSZ <m2> => MEMBER LPSTR <m> ;
                                          ; GWSTBACK() ;
                                          ; MEMBER DYNSZ <m2>
//----------------------------------------------------------------------------------------------------------------------
#xcommand MEMBER DYNSZ  <m2> LPSTR <m> => MEMBER LPSTR <m> ;
                                          ; GWSTBACK() ;
                                          ; MEMBER DYNSZ <m2>
// -----------------------------------------------------------------------------------------------------------------
#xcommand MEMBER LPSTR  <m> STRZ_READ <m2> => ;
                 MEMBER LPSTR <m> ;
                 ;DYNAMIC  READONLY PROPERTY <m2> BLOCK \{|s| iif( s:<m> == 0,"",PeekStr(s:<m>,0,-1))\}
// -----------------------------------------------------------------------------------------------------------------
#xcommand MEMBER LPSTR  <m> STR_READ_CB <m2> CBFROM <ms> => ;
                 MEMBER LPSTR <m> ;
                 ;DYNAMIC  READONLY PROPERTY <m2> BLOCK \{|s| iif( s:<m> == 0,"",PeekStr(s:<m>,0,s:<ms>))\}
// -----------------------------------------------------------------------------------------------------------------
#xcommand MEMBER POINTER32 <m> LINK <m2> CLASS <cc> => ;
                 MEMBER POINTER32 <m> ;
                 ;DYNAMIC  READONLY PROPERTY <m2> BLOCK {|s| iif( s:<m> == 0,NIL,<cc>():New():_link_(s:<m>,.F.))}
// -----------------------------------------------------------------------------------------------------------------
#xcommand MEMBER POINTER32 <m> LINK <m2> => ;
                 MEMBER POINTER32 <m> ;
                 ;DYNAMIC  READONLY PROPERTY <m2> BLOCK {|s| iif( s:<m> == 0,NIL,s:ClassObject():New():_link_(s:<m>,.F.))}
//----------------------------------------------------------------------------------------------------------------------
#xcommand MEMBER BINSTR  <m>  SIZE <n> => ooo:_Member_BINSTR( <(m)> , <n>)
#xcommand MEMBER SZSTR   <m>  SIZE <n> => ooo:_Member_SZSTR( <(m)> , <n>)
#xcommand MEMBER SZWSTR  <m>  SIZE <n> => ooo:_Member_SZWSTR( <(m)> , <n>)
//----------------------------------------------------------------------------------------------------------------------
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
#xcommand DELEGATE <v> METHOD <cm>( [<p1>] [,<pn>] );
          =>;
          INLINE METHOD <cm>( [<p1>] [,<pn>] ) ;
          ; return ::<v>:<cm>( [@<p1>] [,@<pn>] )
//----------------------------------------------------------------------------------------------------------------------
#xcommand DELEGATE <v> VAR <cm>
          =>;
          INLINE ACCESS ASSIGN METHOD <cm>(v) ;
          ; if( PCount() > 0);
          ;    return ::<v>:<cm> := v ;
          ; end;
          ; return ::<v>:<cm>
//----------------------------------------------------------------------------------------------------------------------
#xcommand DELEGATE VAR <cm> TO <exp>
          =>;
          INLINE ACCESS ASSIGN METHOD <cm>(v) ;
          ; if( PCount() > 0);
          ;    return <exp>  := v ;
          ; end;
          ; return <exp>

//----------------------------------------------------------------------------------------------------------------------
#xcommand DELEGATE <v> CLASS VAR <cm>
          =>;
          INLINE ACCESS ASSIGN CLASS METHOD <cm>(v) ;
          ; if( PCount() > 0);
          ;    return ::<v>:<cm> := v ;
          ; end;
          ; return ::<v>:<cm>
//----------------------------------------------------------------------------------------------------------------------
#xcommand DELEGATE CLASS VAR <cm> TO <exp>
          =>;
          INLINE ACCESS ASSIGN CLASS METHOD <cm>(v) ;
          ; if( PCount() > 0);
          ;    return <exp>  := v ;
          ; end;
          ; return <exp>

//----------------------------------------------------------------------------------------------------------------------
#xcommand DELEGATE <v> VAR <cm> READONLY
          =>;
          INLINE ACCESS METHOD <cm>() ;
          ; return ::<v>:<cm>
//----------------------------------------------------------------------------------------------------------------------
#xcommand DELEGATE <v> CLASS VAR <cm> READONLY
          =>;
          INLINE ACCESS CLASS METHOD <cm>() ;
          ; return ::<v>:<cm>
//----------------------------------------------------------------------------------------------------------------------
#xcommand DELEGATE <v> VAR <cm> TO <exp> READONLY
          =>;
          INLINE ACCESS METHOD <cm>() ;
          ; return <exp>
//----------------------------------------------------------------------------------------------------------------------
#xcommand DELEGATE <v> CLASS VAR <cm> TO <exp>  READONLY
          =>;
          INLINE ACCESS CLASS METHOD <cm>() ;
          ; return <exp>
//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
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
#xcommand PROPERTY <name>  IS MASK <mask> OF <var> READONLY => ;
          INLINE ACCESS METHOD <name>() ;
          ;return lAnd( ::<var> , <mask> )
//----------------------------------------------------------------------------------------------------------------------
#xcommand PROPERTY <name>  IS CONSTANT <val> => ;
          INLINE ACCESS METHOD <name>() ;
          ; return <val>
//----------------------------------------------------------------------------------------------------------------------
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
#xcommand CLASS PROPERTY <name>  IS MASK <mask> OF <var> READONLY => ;
          INLINE ACCESS CLASS METHOD <name>() ;
          ;return lAnd( ::<var> , <mask> )
//----------------------------------------------------------------------------------------------------------------------
#xcommand CLASS PROPERTY <name>  IS CONSTANT <val> => ;
          INLINE ACCESS CLASS METHOD <name>() ;
          ; return <val>
//----------------------------------------------------------------------------------------------------------------------
#xcommand BEGIN VARLEN STRUCTURE   <cn> => ;
          BEGIN STRUCTURE <cn> local _cgb_ , _cpb_ , _cfr_,_vls_;
          ; _cgb_ := "{|s|s:_read_() " ;
          ; _cpb_ := "{|s,v,nn| nn := %u,s:_write_(v,0,nn)," ;
          ; _cfr_ := "{|s,h,nn| s:_zeromemory_(),nn := FRead(h, @s:_m__pt_ , s:_sizeof_() ),"  ;
          ; _vls_ := "{|s| s:_sizeof_()"


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


//-----------------------------------------------------------------------------------------------------------------------
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
#xcommand QTEMPLATE <qt> AS QTYPE <rt> [  PARAM AS QTYPE <t1> ]  [, PARAM AS QTYPE <tN> ]  => ;
; <qt> := <rt> [+ <t1>] [+ <tN>]
//----------------------------------------------------------------------------------------------------------------------
#xcommand local QTEMPLATE <qt> AS QTYPE <rt> [  PARAM AS QTYPE <t1> ]  [, PARAM AS QTYPE <tN> ]  => ;
; local <qt> := <rt> [+ <t1>] [+ <tN>]
//----------------------------------------------------------------------------------------------------------------------
#xcommand static QTEMPLATE <qt> AS QTYPE <rt> [  PARAM AS QTYPE <t1> ]  [, PARAM AS QTYPE <tN> ]  => ;
; static <qt> := <rt> [+ <t1>] [+ <tN>]
//----------------------------------------------------------------------------------------------------------------------
#xtranslate DLL <cDll> IMPORT <rt> <fn>( [<t1> <p1> ] [,<tN> <pN> ] ) ;
                     [<*more*>]  ;
                     => ;
DLL <cDll> IMPORT <fn> AS <rt> ;
                     [  PARAM <p1> AS <t1> ]  ;
                     [, PARAM <pN> AS <tN> ]  ;
                     <more>
//----------------------------------------------------------------------------------------------------------------------
#xtranslate DELEGATED DLL <cDll> IMPORT <rt> <fn>( [<t1> <p1> ] [,<tN> <pN> ] ) ;
                     [<*more*>]  ;
                     => ;
DELEGATED DLL <cDll> IMPORT <fn> AS <rt> ;
                     [  PARAM <p1> AS <t1> ]  ;
                     [, PARAM <pN> AS <tN> ]  ;
                     <more>
//----------------------------------------------------------------------------------------------------------------------
#xtranslate DLL <cDll> XIMPORT <rt> <fn>( [<t1> <p1> ] [,<tN> <pN> ] ) ;
                     [<*more*>]  ;
                     => ;
DLL <cDll> XIMPORT <fn> AS <rt> ;
                     [  PARAM <p1> AS <t1> ]  ;
                     [, PARAM <pN> AS <tN> ]  ;
                     <more>
// -----------------------------------------------------------------------------------------------------------------
#xtranslate DELEGATED DLL <cDll> XIMPORT <rt> <fn>( [<t1> <p1> ] [,<tN> <pN> ] ) ;
                     [<*more*>]  ;
                     => ;
DELEGATED DLL <cDll> XIMPORT <fn> AS <rt> ;
                     [  PARAM <p1> AS <t1> ]  ;
                     [, PARAM <pN> AS <tN> ]  ;
                     <more>
//----------------------------------------------------------------------------------------------------------------------
#if OT4XB_ASSERT_LEVEL > 2
#xtranslate @<dll>:<fn>([<p1>] [,<pn>] ) => ( _Assert_dll_fn_(<(dll)>,<(fn)>) , nFpCall( {<(dll)>,<(fn)>} [,<p1>] [,<pn>] ) )
#else
#xtranslate @<dll>:<fn>([<p1>] [,<pn>] ) => nFpCall( {<(dll)>,<(fn)>} [,<p1>] [,<pn>] )
#endif
// -----------------------------------------------------------------------------------------------------------------
#xtranslate @<dll>:\[<tp>\]:<fn>([<p1>] [,<pn>] ) => FpQCall( {<(dll)>,<(fn)>},<(tp)> [,<p1>] [,<pn>] )
//----------------------------------------------------------------------------------------------------------------------
#xtranslate MEMBER BINSTR <s> DWORD ARRAY <m> ITEMS <n> => ;
            ooo:_Member_BINSTR( <(s)> , <n> * 4 ) ;
            ; ooo:_Method( <(m)> , {|s,n,v| _Assert_Range_(n,0,(<n>-1)),   s:_lock_() , iif( PCount() > 2,;
                                            PokeDWord(s:_addressof_(<(s)>), n * 4,v),;
                                            v := PeekDWord(s:_addressof_(<(s)>), n * 4)),;
                                            s:_unlock_() , v } )
//----------------------------------------------------------------------------------------------------------------------
#xtranslate MEMBER BINSTR <s> WORD ARRAY <m> ITEMS <n> => ;
            ooo:_Member_BINSTR( <(s)> , <n> * 2 ) ;
            ; ooo:_Method( <(m)> , {|s,n,v| _Assert_Range_(n,0,(<n>-1)),   s:_lock_() , iif( PCount() > 2,;
                                            PokeWord(s:_addressof_(<(s)>), n * 2,v),;
                                            v := PeekWord(s:_addressof_(<(s)>), n * 2)),;
                                            s:_unlock_() , v } )
//----------------------------------------------------------------------------------------------------------------------
#xtranslate MEMBER BINSTR <s> BYTE ARRAY <m> ITEMS <n> => ;
            ooo:_Member_BINSTR( <(s)> , <n>   ) ;
            ; ooo:_Method( <(m)> , {|s,n,v| _Assert_Range_(n,0,(<n>-1)),   s:_lock_() , iif( PCount() > 2,;
                                            PokeWord(s:_addressof_(<(s)>), n ,v),;
                                            v := PeekWord(s:_addressof_(<(s)>), n )),;
                                            s:_unlock_() , v } )
//----------------------------------------------------------------------------------------------------------------------
#xcommand ITERATE ARRAY <a> ;
          [ VALID TYPES <t,...>] => ;
          OT4XB_ARRAY_ITERATOR( <a> ) ;
          ; while( OT4XB_ARRAY_ITERATOR_STEP( [nOr(<t>)] ) )
#xcommand END ITERATE => end
// -----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
#xcommand WITH FRAME <v> =>;
WithObjectStackPush( ErrorBlock({|__e__| Break(__e__)}) ) ;
;<v> := WithObjectStackCount() ;
; BEGIN SEQUENCE
//----------------------------------------------------------------------------------------------------------------------
#xcommand END FRAME <v> =>;
; END SEQUENCE    ;
; WithObjectStackRecover( <v> ) ;
; ErrorBlock( WithObjectStackPop() )
//----------------------------------------------------------------------------------------------------------------------
#xcommand ON <b> EXIT FRAME => iif(Empty(<b>),, Break())
//----------------------------------------------------------------------------------------------------------------------
#xcommand WITH OBJECT <o> NONIL =>;
 WithObjectStackPush(<o>);
 ; if WithObjectStackTop() == NIL ;
 ; BREAK ;
 ; end
//----------------------------------------------------------------------------------------------------------------------
#xcommand WITH OBJECT <o> => WithObjectStackPush(<o>)
#xcommand END WITH => WithObjectStackPop()
#xtranslate with.item =>WithObjectStackTop()
#xtranslate with.this =>WithObjectStackTop()
#xtranslate with.index =>OT4XB_ARRAY_ITERATOR_INDEX()
#xtranslate .:<*more*> => WithObjectStackTop():<more>
#xtranslate ..:<*more*> => WithObjectStackTop(1):<more>
#xtranslate ...:<*more*> => WithObjectStackTop(2):<more>
#xtranslate ....:<*more*> => WithObjectStackTop(3):<more>
#xtranslate .:(<n>):<*more*> => WithObjectStackTop(<n>):<more>
//----------------------------------------------------------------------------------------------------------------------
// This 3 lines would prevent confilcts within the logical operators and WITH OBJECT
// Many thanks to Andreas Gehrs-Pahl that foung the bug and the workarround
#xtranslate .not. ::<*more*> => .not. Self:<more>
#xtranslate .and. ::<*more*> => .and. Self:<more>
#xtranslate .or. ::<*more*> => .or.  Self:<more>
// ...... but sometimes the preprocessor not cath it correctly .....
// but this 3 ugly extra lines seems to work in all cases
#xtranslate .notWithObjectStackTop()::<*more*> => .not. Self:<more>
#xtranslate .andWithObjectStackTop()::<*more*> => .and. Self:<more>
#xtranslate .orWithObjectStackTop()::<*more*> => .or. Self:<more>
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
#define __vtMissing__  cHex2Bin( "0A000000000000000400028000000000" )
#define __vtEmpty__    ChrR(0,16)
#xtranslate IUnknow.uuidof() => UuidFromString("00000000-0000-0000-C000-000000000046")
#xtranslate IDispatch.uuidof() => UuidFromString("00020400-0000-0000-C000-000000000046")
#xtranslate ISequentialStream.uuidof() => UuidFromString("0C733A30-2A1C-11CE-ADE5-00AA0044773D")
#xtranslate IStream.uuidof() => UuidFromString("0000000C-0000-0000-C000-000000000046")
// -----------------------------------------------------------------------------------------------------------------
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
#define OT4XB_QLOOP_COMPILE_BLOCKS  0x01000000
// -----------------------------------------------------------------------------------------------------------------
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
#define OT4XB_FPFLAGS_JSON_MINIMAL_ENCODING     0x08000000
#define OT4XB_FPFLAGS_JSON_CODEPAGE_OEM         0x01000000
#define OT4XB_FPFLAGS_JSON_CODEPAGE_UTF8        0x04000000
// ----------------------------------------------------------------------------------------------------------------
#define EXPANDO_FORMAT_DEBUG                 1
#define EXPANDO_FORMAT_FLAT_ARRAY_KV_ITEMS    0x00000010
#define EXPANDO_FORMAT_ENFORCE_FLAT           0x00000020
#define EXPANDO_FORMAT_PRETTY                 0x01000000
#xtranslate EXPANDO_FORMAT_ND_PRECISSION( <x> )   => nLShift( nAnd( <x> , 0x0F ) , 16 )
#define EXPANDO_FORMAT_ND_FIXED               0x00100000
#define EXPANDO_FORMAT_ND_MINIMAL             0x00200000
// -----------------------------------------------------------------------------------------------------------------
#ifdef _OT4XB_MAP_WAPIST_FUNC_
#include "ot4xb_wapist_map.ch"
#endif
// -----------------------------------------------------------------------------------------------------------------
#endif // _OT4XB_CH_