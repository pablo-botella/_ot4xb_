#include "ot4xb.ch"
#include "ot4xb_except.ch"
#ifndef __ot4xb_app_defined
#define __ot4xb_app_defined
// ------------------------------------------------------------------------------------------------------------------------------
#xcommand BEGIN APPLICATION <app> CLASS DECLARATION =>                                             ;
function __app()                                                                                   ;
;return <app>()                                                                                    ;
;static CLASS __ot4xb__error__class__ FROM Error                                                   ;
;EXPORTED:                                                                                         ;
;   VAR aStack                                                                                     ;
;INLINE METHOD init(oError,lGrabStack)                                                             ;
;       local n,nl,cp,aa                                                                           ;
;                                                                                                  ;
;       local eb := ErrorBlock( {|_e| break(_e) } )                                                ;
;       BEGIN SEQUENCE                                                                             ;
;          ::Error:init()                                                                          ;
;          if Valtype(oError) == "O"                                                               ;
;          ::args := oError:args                                                                   ;
;          ::canDefault := oError:canDefault                                                       ;
;          ::canRetry := oError:canRetry                                                           ;
;          ::canSubstitute := oError:canSubstitute                                                 ;
;          ::cargo := oError:cargo                                                                 ;
;          ::description := oError:description                                                     ;
;          ::filename := oError:filename                                                           ;
;          ::genCode := oError:genCode                                                             ;
;          ::operation := oError:operation                                                         ;
;          ::osCode := oError:osCode                                                               ;
;          ::severity := oError:severity                                                           ;
;          ::subCode := oError:subCode                                                             ;
;          ::subSystem := oError:subSystem                                                         ;
;          ::thread := oError:thread                                                               ;
;          ::tries := oError:tries                                                                 ;
;          else                                                                                    ;
;          ::cargo := oError                                                                       ;
;          end                                                                                     ;
;          if !empty( lGrabStack)                                                                  ;
;          n := 0                                                                                  ;
;          aa := Array(0)                                                                          ;
;          while .T.                                                                               ;
;          cp := ProcName(n)                                                                       ;
;          if empty(cp)                                                                            ;
;          exit                                                                                    ;
;          end                                                                                     ;
;          nl := ProcLine(n)                                                                       ;
;          aadd( aa , __anew(cp,nl) )                                                              ;
;          n++                                                                                     ;
;          end                                                                                     ;
;          ::aStack := aa                                                                          ;
;          end                                                                                     ;
;       END SEQUENCE                                                                               ;
;       ErrorBlock(eb)                                                                             ;
;       return Self                                                                                ;
;INLINE METHOD json_escape_self()                                                                                     ;
;       local cc                                                                                                      ;
;       cc := CRLF + ' {'                                                                                             ;
;       cc += CRLF + '     "args"         :  ' +  _ot4xb_expando_():json_serialize( ::args          ,   0x01200000  ) ;
;       cc += CRLF + '    ,"canDefault"   :  ' +  _ot4xb_expando_():json_serialize( ::canDefault    ,   0x01200000  ) ;
;       cc += CRLF + '    ,"canRetry"     :  ' +  _ot4xb_expando_():json_serialize( ::canRetry      ,   0x01200000  ) ;
;       cc += CRLF + '    ,"canSubstitute":  ' +  _ot4xb_expando_():json_serialize( ::canSubstitute ,   0x01200000  ) ;
;       cc += CRLF + '    ,"cargo"        :  ' +  _ot4xb_expando_():json_serialize( ::cargo         ,   0x01200000  ) ;
;       cc += CRLF + '    ,"description"  :  ' +  _ot4xb_expando_():json_serialize( ::description   ,   0x01200000  ) ;
;       cc += CRLF + '    ,"filename"     :  ' +  _ot4xb_expando_():json_serialize( ::filename      ,   0x01200000  ) ;
;       cc += CRLF + '    ,"genCode"      :  ' +  _ot4xb_expando_():json_serialize( ::genCode       ,   0x01200000  ) ;
;       cc += CRLF + '    ,"operation"    :  ' +  _ot4xb_expando_():json_serialize( ::operation     ,   0x01200000  ) ;
;       cc += CRLF + '    ,"osCode"       :  ' +  _ot4xb_expando_():json_serialize( ::osCode        ,   0x01200000  ) ;
;       cc += CRLF + '    ,"severity"     :  ' +  _ot4xb_expando_():json_serialize( ::severity      ,   0x01200000  ) ;
;       cc += CRLF + '    ,"subCode"      :  ' +  _ot4xb_expando_():json_serialize( ::subCode       ,   0x01200000  ) ;
;       cc += CRLF + '    ,"subSystem"    :  ' +  _ot4xb_expando_():json_serialize( ::subSystem     ,   0x01200000  ) ;
;       cc += CRLF + '    ,"thread"       :  ' +  _ot4xb_expando_():json_serialize( ::thread        ,   0x01200000  ) ;
;       cc += CRLF + '    ,"tries"        :  ' +  _ot4xb_expando_():json_serialize( ::tries         ,   0x01200000  ) ;
;       cc += CRLF + '    ,"cargo"        :  ' +  _ot4xb_expando_():json_serialize( ::cargo         ,   0x01200000  ) ;
;       cc += CRLF + '    ,"aStack"       :  ' +  _ot4xb_expando_():json_serialize( ::aStack        ,   0x01200000  ) ;
;       cc += CRLF + ' } ' + CRLF                                                                                     ;
;       return cc                                                                                                     ;
;ENDCLASS                                                                                          ;
;CLASS <app>                                                                                       ;
;       EXPORTED:                                                                                  ;
;       CLASS VAR ini READONLY SHARED                                                              ;
;       CLASS VAR env READONLY SHARED                                                              ;
;       CLASS VAR cfg READONLY SHARED                                                              ;
;INLINE CLASS METHOD initclass                                                                     ;
;       if ::ini == NIL                                                                            ;
;          ::ini := _ot4xb_expando_():New()                                                        ;
;       end                                                                                        ;
;       if ::env == NIL                                                                            ;
;          ::env := _ot4xb_expando_():New()                                                        ;
;          ::env:add_env_strings()                                                                 ;
;       end                                                                                        ;
;       if ::cfg == NIL                                                                            ;
;          ::cfg := _ot4xb_expando_():New()                                                        ;
;       end                                                                                        ;
;       if IsMethod( self , "oninitclass")                                                         ;
;          ::OnInitClass()                                                                         ;
;       end                                                                                        ;
;       return Self                                                                                ;
;INLINE CLASS METHOD load_ini_file(cIniFile)                                                       ;
;          ::ini:add_ini_string( cMemoReadEx(cIniFile),2 )                                          ;
;       return Self                                                                                ;
;INLINE CLASS METHOD argv(n)                                                                       ;
;       return __apeek( GetProccessArgv() , n + iif( IsDebug(),1,0) )                              ;
;INLINE CLASS METHOD argc()                                                                        ;
;       static n := NIL                                                                            ;
;       DEFAULT n := ( Len( GetProccessArgv() ) - iif( IsDebug(),1,0) )                            ;
;       return n                                                                                   ;
;INLINE CLASS METHOD errornew( oError , lGrabStack )                                               ;
;       return __ot4xb__error__class__():new( oError , lGrabStack )                                ;
;INLINE CLASS METHOD throw(error,cDescription,lGrabStack)                                          ;
;       local s := Self                                                                            ;
;       local b := __vmask( 0x40 , errorblock() , {|_e| break(_e) } )                              ;
;       local e := NIL                                                                             ;
;       DEFAULT lGrabStack := .F.                                                                  ;
;       if __vmask( 0xC0 , error ) != NIL                                                          ;
;          if lGrabStack                                                                           ;
;             e := s:errornew(error,.T.)                                                           ;
;          else                                                                                    ;
;             e := error                                                                           ;
;          end                                                                                     ;
;          return eval(b,e)                                                                        ;
;       end                                                                                        ;
;       e := s:errornew(,lGrabStack)                                                               ;
;       e:severity := 2                                                                            ;
;       e:gencode := __vmask( 0x04 , error , -1 )                                                  ;
;       e:description := __vmask( 0x02 , cDescription , error , cPrintf("error: %i",e:gencode) )   ;
;       return eval(b,e)                                                                           ;
;INLINE CLASS METHOD __ftnow(lLocalTime)                                                           ;
;       local cft := ChrR(0,8)                                                                     ;
;       ft64_now(@cft,lLocalTime)                                                                  ;
;       return cft
// ------------------------------------------------------------------------------------------------------------------------------

#xcommand DECLARE APPLICATION BASE64 CLASS METHODS =>;
;EXPORTED:                                                                                          ;
;INLINE CLASS METHOD __b64dec( cStr)                                                                ;
;              local cSrc    := __vstr(cStr,"")                                                     ;
;              local nDstLen := @ot4xb:ot4xb_base64_decode_required_length( Len(cSrc) ) + 16        ;
;              local cDst    := ChrR(0,nDstLen )                                                    ;
;              if @ot4xb:ot4xb_base64_decode(cSrc,Len(cSrc),@cDst,@nDstLen) == 0                    ;
;                 return NIL                                                                        ;
;              end                                                                                  ;
;              return PeekStr(cDst,0,nDstLen )                                                      ;
;INLINE CLASS METHOD __b64enc( cStr , nFlags)                                                       ;
;              local cSrc    := __vstr(cStr,"")                                                     ;
;              local nDstLen := @ot4xb:ot4xb_base64_encode_required_length( Len(cSrc) ) + 16        ;
;              local cDst    := ChrR(0,nDstLen )                                                    ;
;              if @ot4xb:ot4xb_base64_encode(cSrc,Len(cSrc),@cDst,@nDstLen,__vdef(nFlags,0)) == 0   ;
;                 return NIL                                                                        ;
;              end                                                                                  ;
;              return PeekStr(cDst,0,nDstLen )


#xcommand DECLARE APPLICATION ERROR HANDLER CLASS METHODS =>;
;INLINE CLASS METHOD error_handler( e )                                         ;
;       local cc := ""                                                          ;
;       local eb                                                                ;
;       if e:genCode == 11                                                      ;
;          return 0                                                             ;
;       elseif e:genCode == 71   .and.  e:osCode  == 32  .and.  e:canDefault    ;
;          return .F.                                                           ;
;       elseif e:genCode == 78  .AND.  e:canDefault                             ;
;          return .F.                                                           ;
;       end                                                                     ;
;       eb := Errorblock({|e| break(e) })                                       ;
;       BEGIN SEQUENCE                                                          ;
;       cc := _ot4xb_expando_():json_serialize(e)                               ;
;       RECOVER                                                                 ;
;          cc := __vstr(cc,"")  + " ... error_handler() error"                  ;
;       END SEQUENCE                                                            ;
;       BEGIN SEQUENCE                                                          ;
;       ::log_out_error_string( cc )                                            ;
;       END SEQUENCE                                                            ;
;       errorblock(eb)                                                          ;
;       Break()                                                                 ;
;       return NIL

      
      
#xcommand DECLARE APPLICATION COUT CLASS METHODS =>                   ;
;INLINE CLASS METHOD QQOut()                                          ;
;       local np := PCount()                                          ;
;       local n                                                       ;
;       local cc := ""                                                ;
;       for n := 1 to np                                              ;
;          cc += var2char( PValue(n) ) + iif( n \< np, " " , "" )     ;
;       next                                                          ;
;       __printf(,"%s",cc)                                            ;
;       return Self                                                   ;
;INLINE CLASS METHOD QOut()                                           ;
;       local np := PCount()                                          ;
;       local n                                                       ;
;       local cc := ""                                                ;
;       for n := 1 to np                                              ;
;          cc += var2char( PValue(n) ) + iif( n \< np, " " , "" )     ;
;       next                                                          ;
;       __printf(,"\r\n%s",cc)                                        ;
;       return Self      
      
      
      

      
      
#endif