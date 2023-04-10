#ifndef __ot4xb_except_defined
//----------------------------------------------------------------------------------------------------------------------
#xcommand __try(<var> [, <nRetry> [,<nSleep>]]  )->( <expr1> [,<exprN>] ) => ;
   if __vmask(0x80,<var>)==NIL;                                              ;
;     <var> := _ot4xb_expando_():new()                                       ;
;  else                                                                      ;
;     <var>:init()                                                           ;
;  end                                                                       ;
; <var>:lOk := .F.                                                           ;
; <var>:nSleep  := nAnd( nOr(<nSleep>,0x100) , 0xFFF)                        ;
; <var>:eb      := ErrorBlock( {|_e| <var>:error := __app():errornew(_e,.T.) , break() }) ;
; <var>:nRetry  := nAnd(<nRetry>,0x0F) + 1                                   ;
; while <var>:nRetry  > 0                                                    ;
;    <var>:error := NIL                                                      ;
;    <var>:nRetry--                                                          ;
;    BEGIN SEQUENCE                                                          ;
;       <var>:result  := ( <expr1> [, <exprN>] )                             ;
;       <var>:lOk := .T.                                                     ;
;       <var>:nRetry := 0                                                    ;
;    END SEQUENCE                                                            ;
;    BEGIN SEQUENCE                                                          ;
;       if <var>:nRetry > 0                                                  ;
;          @kernel32:SleepEx(nAnd(<var>:nSleep,0xFFF),0)                     ;
;       end                                                                  ;
;    END SEQUENCE                                                            ;
; end                                                                        ;
; ErrorBlock( <var>:eb )
//----------------------------------------------------------------------------------------------------------------------
#xcommand __try__assert(<var> [, <nRetry> [,<nSleep>]]  )->( <expr1> [,<exprN>] ) =>               ;
  if __vmask(0x80,<var>)==NIL;                                                                     ;
;     <var> := _ot4xb_expando_():new()                                                             ;
;  else                                                                                            ;
;     <var>:init()                                                                                 ;
;  end                                                                                             ;
; <var>:lOk := .F.                                                                                 ;
; <var>:nSleep  := nAnd( nOr(<nSleep>,0x100) , 0xFFF)                                              ;
; <var>:eb      := ErrorBlock( {|_e| <var>:error := __app():errornew(_e,.T.) , break() })          ;
; <var>:nRetry  := nAnd(<nRetry>,0x0F) + 1                                                         ;
; while <var>:nRetry  > 0                                                                          ;
;    <var>:error := NIL                                                                            ;
;    <var>:nRetry--                                                                                ;
;    BEGIN SEQUENCE                                                                                ;
;       <var>:result  := ( <expr1> [, <exprN>] )                                                   ;
;       if empty(<var>:result)                                                                     ;
;          __app():throw( -1 , "Assertion Failed" )                                                ;
;       end                                                                                        ;
;       <var>:lOk := .T.                                                                           ;
;       <var>:nRetry := 0                                                                          ;
;    END SEQUENCE                                                                                  ;
;    BEGIN SEQUENCE                                                                                ;
;       if <var>:nRetry > 0                                                                        ;
;          @kernel32:SleepEx(nAnd(<var>:nSleep,0xFFF),0)                                           ;
;       end                                                                                        ;
;    END SEQUENCE                                                                                  ;
; end                                                                                              ;
; ErrorBlock( <var>:eb )
//----------------------------------------------------------------------------------------------------------------------
// intermediate expressions
#xtranslate ___end__if([ <expr1> [,<exprN>] ] )  =>    end
//----------------------------------------------------------------------------------------------------------------------
#xcommand __except(<var>  [, <cond1> [,<condN>]] )[->( <expr1> [,<exprN>] )]  [ -> <*more*>] =>     ;
  if !__vmask(8,__vpeek(<var>,":lOk"),.F.)                                          ;
[;      if ( <cond1> ) ]                                                            ;
[;      if ( <condN> ) ]                                                            ;
[;      ( <expr1> ) ]                                                               ;
[;      ( <exprN> ) ]                                                               ;
[;      <more> ]                                                                    ;
[;      ___end__if( <cond1> ) ]                                                     ;
[;      ___end__if( <condN> ) ]                                                     ;
; end
//----------------------------------------------------------------------------------------------------------------------
#xcommand __finally([<nothing>]) [ -> <*more*>] =>   <more>  ;
//----------------------------------------------------------------------------------------------------------------------
#xcommand __assert(<exp>) => ;
if empty(<exp>) ;
;   __app():throw( -1 , "Assertion Failed: " + <(exp)> ) ;
;end
//----------------------------------------------------------------------------------------------------------------------
#xcommand __assert(<exp> , <params,...> ) => ;
if empty(<exp>) ;
;   __app():throw(<params>) ;
;end
//----------------------------------------------------------------------------------------------------------------------
#xtranslate __succeeded(<v>) =>  __vmask(8,__vpeek(<v>,":lOk"),.F.)
#xtranslate __failed(<v>)    =>  ( ! __vmask(8,__vpeek(<v>,":lOk"),.F.) )
//----------------------------------------------------------------------------------------------------------------------
#endif