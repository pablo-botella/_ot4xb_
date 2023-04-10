//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifndef _API_cpp_TGStack_h_  
#define _API_cpp_TGStack_h_
//----------------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API TGXbStack
{
   public:

       TGXbItem  *  m_pTop;   
       TGXbItem  *  m_pBottom;
       UINT  m_nCount;
       CRITICAL_SECTION *  m_pcs;
       // ---------------------------------------------------------------------------------
       void * operator new( unsigned int );
       void operator delete( void * p);
       // ---------------------------------------------------------------------------------
       ContainerHandle Head( void );
       ContainerHandle Tail( void );
       ContainerHandle Pop( void );
       void Push( ContainerHandle );
       void Add( ContainerHandle );
       void StackEval( ContainerHandle,ContainerHandle);
       void ReverseEval( ContainerHandle,ContainerHandle);
       void ToXbArray(ContainerHandle, BOOL );
       UINT Count(void){ return m_nCount; }
       void SyncMode( void ); 
       void Lock(void);
       void UnLock(void);

};
//----------------------------------------------------------------------------------------------------------------------
#endif // __cplusplus
//----------------------------------------------------------------------------------------------------------------------
#endif








