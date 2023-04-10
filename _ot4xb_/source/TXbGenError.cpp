//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
TXbGenError::TXbGenError(void){ m_cone = _conNewObj("ERROR",0); }
// -----------------------------------------------------------------------------------------------------------------
TXbGenError::TXbGenError(int nCode , LPSTR pOperation , LPSTR pDescription)
{
   m_cone = _conNewObj("ERROR",0);
   subsystem( "ot4xb" );
   gencode(nCode);
   operation(pOperation);
   description(pDescription);
}
// -----------------------------------------------------------------------------------------------------------------
TXbGenError::~TXbGenError(){if( m_cone ){_conRelease( m_cone ); m_cone = 0;}}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::args(ContainerHandle cona){_conSetMember(m_cone,"args",cona);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::add_arg(ContainerHandle con)
{
   ContainerHandle cona = _conNew(0);
   _conGetMember( m_cone,"args",cona);
   if( !_conCheckType(cona,XPP_ARRAY) )
   {
      _conRelease(cona); cona = _conNewArray(1,0);
   }
   DWORD nItems = _conGetArrayLen(cona);
   _conResizeA(cona,nItems+1);
   _conArrayPut(cona,con,nItems+1,0);
   _conSetMember(m_cone,"args",cona);
   _conRelease(cona); 
}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::candefault( BOOL b ){_conSetLMember(m_cone,"candefault",b);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::canretry( BOOL b ){_conSetLMember(m_cone,"canretry",b);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::cansubstitute( BOOL b ){_conSetLMember(m_cone,"cansubstitute",b);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::cargo(ContainerHandle con){_conSetMember(m_cone,"cargo",con);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::description(LPSTR p){_conSetCMember(m_cone,"description",p);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::filename(LPSTR p){_conSetCMember(m_cone,"filename",p);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::gencode(int i){_conSetNLMember(m_cone,"gencode",i);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::operation(LPSTR p){_conSetCMember(m_cone,"operation",p);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::oscode(int i){_conSetNLMember(m_cone,"oscode",i);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::severity( int i){_conSetNLMember(m_cone,"severity",i);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::subcode(int i){_conSetNLMember(m_cone,"subcode",i);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::subsystem(LPSTR p){_conSetCMember(m_cone,"subsystem",p);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::tries(int i){_conSetNLMember(m_cone,"tries",i);}
// -----------------------------------------------------------------------------------------------------------------
void TXbGenError::Launch(void)
{  
   ContainerHandle conr = _conNew(0);
   ContainerHandle conb = _conCallCon("ErrorBlock");
   _conEvalB(conr,conb,1,m_cone);
   _conReleaseM( conr, conb, 0);
}
// -----------------------------------------------------------------------------------------------------------------


