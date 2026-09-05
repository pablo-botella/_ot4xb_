//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
#define PXERROR( n , m , d )  px->GenError();px->SetErrorSubSystem("ot4xb"); \
                              px->SetErrorOperation("TGXbStack::"  ##m  "()"); \
                              px->SetErrorDescription( d ); \
                              px->SetErrorGenCode(0x10201000 + n);
// -----------------------------------------------------------------------------------------------------------------
static void TGXbStack_Init( TXbClsParams * px );
static void TGXbStack_Destroy( TXbClsParams * px );
static void TGXbStack_Head( TXbClsParams * px );
static void TGXbStack_Tail( TXbClsParams * px );
static void TGXbStack_Pop( TXbClsParams * px );
static void TGXbStack_Push( TXbClsParams * px );
static void TGXbStack_Add( TXbClsParams * px );
static void TGXbStack_SEval( TXbClsParams * px );
static void TGXbStack_QEval( TXbClsParams * px );
static void TGXbStack_Count( TXbClsParams * px );
static void TGXbStack_pCriticalSection( TXbClsParams * px );
static void TGXbStack_Lock( TXbClsParams * px );
static void TGXbStack_UnLock( TXbClsParams * px );
//----------------------------------------------------------------------------------------------------------------------
static ContainerHandle __conco__tgstack__  = NULLCONTAINER;
//----------------------------------------------------------------------------------------------------------------------
class TGXbItem  
{
  public:
     TGXbItem  * m_pNext;
     TGXbItem  * m_pPrev;
     ContainerHandle m_pData;
     void * operator new( unsigned int );
     void operator delete( void * p);
};
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: TGXbStack
            | _slug_: tgxbstack
            | class-function: TGXBSTACK
            | category: container/stack
            | desc: Low-level double-ended container that stores Xbase++ values in an internal C++ linked list.
            | note: TGXbStack keeps references to the values pushed into the stack. By default it is not
              synchronized and must not be used from more than one thread at the same time unless the caller
              provides its own synchronization. Use :new(.T.) to synchronize the public operations with an
              internal CriticalSection for multithread use.
            | note: This is a low-level utility; callers that use :Lock() directly must always pair it with
              :UnLock().
            | note: The methods raise an ot4xb error when they are called on an object whose internal stack was
              destroyed or not properly initialized.
   | _kw_: stack, deque, double ended, container list, push pop
   }}*/
XPPRET XPPENTRY TGXBSTACK(XppParamList pl)
{
   ContainerHandle conco = _conClsObj("TGXbStack");
   // ---------------------------------------------------------------------------------
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName( "TGXbStack" );
      /*{{|:**BEGIN CLASS  TGXbStack** }}*/
      pc->EXPORTED();
      // ---------------------------------------------------------------------------------
      /*{{|ivar_: - VAR _m__pt_
               | type: Numeric
               | desc_: Internal instance variable holding the pointer to the native stack object.
               | note: Internal state, not meant to be manipulated outside the class.
      }}*/
      pc->Var("_m__pt_"); 
      /*{{|property_: - PROPERTY pCriticalSection
               | type: `Numeric | NIL`
               | desc_: Read-only pointer to the internal CriticalSection when synchronized mode is active,
                 NIL otherwise.
               | note: Read-only property.
      }}*/
      pc->ROProperty("pCriticalSection" , TGXbStack_pCriticalSection); 
      // ---------------------------------------------------------------------------------
      /*{{|method_: - METHOD new( [lSyncMode] )
               | return: oStack
               | desc_: Creates the object and initializes its internal stack. With lSyncMode == .T. the
                 public operations are synchronized with an internal CriticalSection for multithread use.
               | note: The underlying ::init() method can not be called explicitly on an already initialized
                 object; doing so raises an error and destroys the internal stack.
      }}*/
      pc->Method("init"     , TGXbStack_Init,1);
      /*{{|method_: - METHOD Destroy()
               | return: NIL
               | desc_: Destroys the internal stack and releases stored container references. Call it when
                 the stack is no longer needed so internal resources are not left alive unnecessarily.
      }}*/
      pc->Method("Destroy"  , TGXbStack_Destroy);
      /*{{|method_: - METHOD Head()
               | return: xValue
               | desc_: Returns the value at the top/head of the stack without removing it.
      }}*/
      pc->Method("Head"     , TGXbStack_Head);
      /*{{|method_: - METHOD Tos() | return: xValue | desc_: Alias of ::Head(). }}*/
      pc->Method("Tos"      , TGXbStack_Head);
      /*{{|method_: - METHOD Tail()
               | return: xValue
               | desc_: Returns the value at the tail/bottom of the stack without removing it.
      }}*/
      pc->Method("Tail"     , TGXbStack_Tail);
      /*{{|method_: - METHOD Pop()
               | return: xValue
               | desc_: Removes and returns the value at the head/top of the stack.
      }}*/
      pc->Method("Pop"      , TGXbStack_Pop);
      /*{{|method_: - METHOD Push( xValue )
               | return: nCount
               | desc_: Adds xValue at the head/top of the stack and returns the new item count.
      }}*/
      pc->Method("Push"     , TGXbStack_Push,1);
      /*{{|method_: - METHOD Add( xValue )
               | return: nCount
               | desc_: Adds xValue at the tail/bottom of the stack and returns the new item count.
      }}*/
      pc->Method("Add"      , TGXbStack_Add,1);
      /*{{|method_: - METHOD Count() | return: nCount | desc_: Returns the current item count. }}*/
      pc->Method("Count"    , TGXbStack_Count);
      /*{{|method_: - METHOD SEval( [bEval [, xCargo]] )
               | return: `aValues | NIL`
               | desc_: Without parameters, returns the stack contents as an array from head to tail. With a
                 codeblock, evaluates it for each item from head to tail as bEval( xValue, xCargo, nIndex,
                 nCount ), with nIndex starting at 0.
      }}*/
      pc->Method("SEval"    , TGXbStack_SEval,2);
      /*{{|method_: - METHOD QEval( [bEval [, xCargo]] )
               | return: `aValues | NIL`
               | desc_: Without parameters, returns the stack contents as an array from head to tail. With a
                 codeblock, evaluates it for each item from tail to head as bEval( xValue, xCargo, nIndex,
                 nCount ), with nIndex starting at 0.
      }}*/
      pc->Method("QEval"    , TGXbStack_QEval,2);
      /*{{|method_: - METHOD Lock()
               | return: NIL
               | desc_: Enters the internal CriticalSection when the stack was created in synchronized mode.
      }}*/
      pc->Method("Lock"     , TGXbStack_Lock);
      /*{{|method_: - METHOD UnLock()
               | return: NIL
               | desc_: Leaves the internal CriticalSection when the stack was created in synchronized mode.
      }}*/
      /*{{|:**END CLASS** }}*/
      pc->Method("UnLock"   , TGXbStack_UnLock);
      // ---------------------------------------------------------------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   // ---------------------------------------------------------------------------------
   _conReturn(pl,conco);
   _conRelease(conco);
}
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_Init( TXbClsParams * px )
{
   TGXbStack * psc;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc != NULL )
   {
      PXERROR( 1 , "init" , "TGXbStack:init() can not be called explicity"); 
      delete psc; px->SetSelfC(NULL); 
   }
   else
   {
      psc = (TGXbStack * ) new TGXbStack; 
      px->SetSelfC( (void *) psc); 
      if( px->GetParamBool(1) ) psc->SyncMode();
      px->PutReturnSelf();
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_Destroy( TXbClsParams * px )
{
   TGXbStack * psc = (TGXbStack *) 0;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc == NULL ){PXERROR( 2, "Destroy" , "Object destroyed or not properly initialized."); return;}
   delete psc; px->SetSelfC(NULL);
}
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_Head( TXbClsParams * px )
{
   TGXbStack * psc = (TGXbStack *) 0;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc == NULL ){PXERROR( 2, "Head" , "Object destroyed or not properly initialized."); return;}
   psc->Lock();                
   __try{   px->PutReturn( psc->Head() ); 
        } __finally{ psc->UnLock(); }
}
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_Tail( TXbClsParams * px )
{
   TGXbStack * psc = (TGXbStack *) 0;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc == NULL ){PXERROR( 2, "Tail" , "Object destroyed or not properly initialized."); return;}
   psc->Lock();                
   __try{   px->PutReturn( psc->Tail() ); 
        } __finally{ psc->UnLock(); }
}
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_Pop( TXbClsParams * px )
{
   TGXbStack * psc = (TGXbStack *) 0;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc == NULL ){PXERROR( 2, "Pop" , "Object destroyed or not properly initialized."); return;}
   psc->Lock();                
   __try{ 
          ContainerHandle con = psc->Pop();
          px->PutReturn( con ); 
          if( con ) _conRelease(con);
        } __finally{ psc->UnLock(); }
}
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_Push( TXbClsParams * px )
{
   TGXbStack * psc = (TGXbStack *) 0;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc == NULL ){PXERROR( 2, "Push" , "Object destroyed or not properly initialized."); return;}
   psc->Lock();                
   __try{   psc->Push(_conNew(px->GetParam(1)));
            px->PutReturnLong( psc->Count() ); 
        } __finally{ psc->UnLock(); }
}
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_Add( TXbClsParams * px )
{
   TGXbStack * psc = (TGXbStack *) 0;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc == NULL ){PXERROR( 2, "Add" , "Object destroyed or not properly initialized."); return;}
   psc->Lock();                
   __try{   psc->Add(_conNew(px->GetParam(1)));
            px->PutReturnLong( psc->Count() ); 
        } __finally{ psc->UnLock(); }
}
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_Count( TXbClsParams * px )
{
   TGXbStack * psc = (TGXbStack *) 0;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc == NULL ){PXERROR( 2, "Count" , "Object destroyed or not properly initialized."); return;}
   psc->Lock();                
   __try{   px->PutReturnLong( psc->Count() ); 
        } __finally{ psc->UnLock(); }
}
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_pCriticalSection( TXbClsParams * px )
{
   TGXbStack * psc = (TGXbStack *) 0;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc == NULL ){PXERROR( 2, "pCriticalSection" , "Object destroyed or not properly initialized."); return;}
   psc->Lock();                
   __try{   if( psc->m_pcs != NULL ) px->PutReturnLong( (LONG) ((void*) psc->m_pcs) ); 
        } __finally{ psc->UnLock(); }
}
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_SEval( TXbClsParams * px )
{
   TGXbStack * psc = (TGXbStack *) 0;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc == NULL ){PXERROR( 2, "SEval" , "Object destroyed or not properly initialized."); return;}
   psc->Lock();                
   __try{   if( px->PCount() == 0 ) psc->ToXbArray(px->GetReturn(),FALSE);
            else 
            if( px->CheckParamType(1, XPP_BLOCK) )
            {                      
               psc->StackEval( px->GetParam(1) , ( (px->PCount() > 1 ) ? px->GetParam(2) : px->GetReturn() ) );
            }
        } __finally{ psc->UnLock(); }
}
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_QEval( TXbClsParams * px )
{
   TGXbStack * psc = (TGXbStack *) 0;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc == NULL ){PXERROR( 2, "QEval" , "Object destroyed or not properly initialized."); return;}
   psc->Lock();                
   __try{   if( px->PCount() == 0 ) psc->ToXbArray(px->GetReturn(),FALSE);
            else 
            if( px->CheckParamType(1, XPP_BLOCK) )
            {                      
               psc->ReverseEval( px->GetParam(1) , ((px->PCount() > 1) ? px->GetParam(2) : px->GetReturn() ) );
            }
        } __finally{ psc->UnLock(); }
}
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_Lock( TXbClsParams * px )
{
   TGXbStack * psc = (TGXbStack *) 0;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc == NULL ){PXERROR( 2, "Lock" , "Object destroyed or not properly initialized."); return;}
   psc->Lock();                
}
//----------------------------------------------------------------------------------------------------------------------
static void TGXbStack_UnLock( TXbClsParams * px )
{
   TGXbStack * psc = (TGXbStack *) 0;
   psc = (TGXbStack * ) px->GetSelfC();
   if( psc == NULL ){PXERROR( 2, "UnLock" , "Object destroyed or not properly initialized."); return;}
   psc->UnLock();                
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void * TGXbItem::operator new( unsigned int n ){return _xgrab(n);}
//----------------------------------------------------------------------------------------------------------------------
void TGXbItem::operator delete( void * p)
{
   TGXbItem * pSelf;
   pSelf = ( TGXbItem * ) p;
   if( pSelf->m_pData != NULLCONTAINER ) _conRelease( pSelf->m_pData);
   _xfree(p);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void * TGXbStack::operator new( unsigned int n )
{
   TGXbStack * pSelf;
   pSelf = ( TGXbStack * ) _xgrab(n);
   pSelf->m_pTop      = 0;
   pSelf->m_pBottom   = 0;
   pSelf->m_nCount    = 0;             
   pSelf->m_pcs       = 0;
   return ( void * ) pSelf;
}
//----------------------------------------------------------------------------------------------------------------------
void TGXbStack::operator delete( void * p)
{
  TGXbStack * pSelf;
  pSelf = ( TGXbStack * ) p;
  if( pSelf->m_pcs != 0 ){EnterCriticalSection(pSelf->m_pcs);}
  
  while( pSelf->m_nCount != 0)
  {
     ContainerHandle con = pSelf->Pop();
     if(con != NULLCONTAINER ) _conRelease(con);
  }
  if( pSelf->m_pcs != 0 )
  {
    CRITICAL_SECTION * pcs;
    pcs = pSelf->m_pcs;
    pSelf->m_pcs = 0;
    DeleteCriticalSection(pcs);
    _xfree( (void *) pcs );
  }
  _xfree(p);
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TGXbStack::Head(void)
{
    if( m_pTop == 0 ) return 0;
    return m_pTop->m_pData;
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TGXbStack::Tail(void)
{
    if( m_pBottom == 0 ) return 0;
    return m_pBottom->m_pData;
}
//----------------------------------------------------------------------------------------------------------------------
void TGXbStack::Add( ContainerHandle con )
{
   TGXbItem * pItem = new TGXbItem;
   pItem->m_pData = con;
   
   if( m_nCount == 0 )  m_pTop    = pItem;
   else
   {
      pItem->m_pPrev = m_pBottom;
      m_pBottom->m_pNext  = pItem;
   }
   m_pBottom = pItem;
   m_nCount++;
}
//----------------------------------------------------------------------------------------------------------------------
void TGXbStack::Push( ContainerHandle con )
{
   TGXbItem * pItem = new TGXbItem;
   pItem->m_pData = con;
   
   if( m_nCount == 0 )  m_pBottom    = pItem;
   else
   {
      pItem->m_pNext = m_pTop;
      m_pTop->m_pPrev  = pItem;
   }
   m_pTop = pItem;
   m_nCount++;
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TGXbStack::Pop( void)
{
   ContainerHandle con = NULLCONTAINER;
   if( m_nCount > 0 )
   {
      TGXbItem * pItem = m_pTop;
      m_pTop = pItem->m_pNext;
      m_nCount--;
      if( m_pTop != NULL ) m_pTop->m_pPrev = NULL;
      else m_pBottom    = NULL;
      con = pItem->m_pData; pItem->m_pData = NULLCONTAINER;
      delete pItem;
   }
   return con;
}
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
void TGXbStack::StackEval( ContainerHandle conBlock , ContainerHandle conCargo)
{
   TGXbItem * pItem;
   UINT     n;
   ContainerHandle conLen  = _conPutNL(NULLCONTAINER,m_nCount);
   ContainerHandle conN    = NULLCONTAINER;
   ContainerHandle con     = NULLCONTAINER;
   ContainerHandle conData = NULLCONTAINER;
   for( pItem = m_pTop,n=0; pItem != 0; pItem = pItem->m_pNext , n++ )
   {
       conData = pItem->m_pData;
       if( conData != NULLCONTAINER )
       {
          con     = _conPut( con , NULLCONTAINER);
          conN    = _conPutNL(conN,(LONG) n);
          _conEvalB( con, conBlock,4,conData,conCargo,conN,conLen);
       }
   }
   if( conLen != NULLCONTAINER ) _conRelease(conLen);
   if( conN   != NULLCONTAINER ) _conRelease(conN);
   if( con    != NULLCONTAINER ) _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
void TGXbStack::ReverseEval( ContainerHandle conBlock , ContainerHandle conCargo)
{
   TGXbItem * pItem;
   UINT     n;
   ContainerHandle conLen  = _conPutNL(NULLCONTAINER,m_nCount);
   ContainerHandle conN    = NULLCONTAINER;
   ContainerHandle con     = NULLCONTAINER;
   ContainerHandle conData = NULLCONTAINER;
   for( pItem = m_pBottom , n=0; pItem != 0; pItem = pItem->m_pPrev , n++ )
   {
       conData = pItem->m_pData;
       if( conData != NULLCONTAINER )
       {
          con     = _conPut( con , NULLCONTAINER);
          conN    = _conPutNL(conN,(LONG) n);
          _conEvalB( con, conBlock,4,conData,conCargo,conN,conLen);
       }
   }
   if( conLen != NULLCONTAINER ) _conRelease(conLen);
   if( conN   != NULLCONTAINER ) _conRelease(conN);
   if( con    != NULLCONTAINER ) _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
void TGXbStack::ToXbArray( ContainerHandle conRet , BOOL bReverse)
{                    
   if( conRet != NULLCONTAINER ) 
   {
      TGXbItem * pItem;                               
      UINT     n;
      ContainerHandle cona    = _conNewArray(1,m_nCount);
      if( bReverse ) 
      {
         for( pItem = m_pBottom , n=1; pItem != 0; pItem = pItem->m_pPrev , n++ )
         {
             if( pItem->m_pData != NULLCONTAINER )
             {  
                ContainerHandle con = _conPut( NULLCONTAINER , pItem->m_pData);
                _conArrayPut(cona,con,n,0);
                _conRelease(con);
             }
         }
      }
      else
      {
         for( pItem = m_pTop,n=1; pItem != 0; pItem = pItem->m_pNext , n++ )
         {
             if( pItem->m_pData != NULLCONTAINER )
             {  
                ContainerHandle con = _conPut( NULLCONTAINER , pItem->m_pData);
                _conArrayPut(cona,con,n,0);
                _conRelease(con);
             }
         }
      }
      _conPut(conRet,cona);
      _conRelease(cona);
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TGXbStack::SyncMode( void )
{
  CRITICAL_SECTION * pcs;
  if( m_pcs != 0 ){return;}
  pcs = (CRITICAL_SECTION *) _xgrab( sizeof(CRITICAL_SECTION) );
  InitializeCriticalSection(pcs);
  m_pcs = pcs;
}
//----------------------------------------------------------------------------------------------------------------------
void TGXbStack::Lock(void){ if( m_pcs != 0 )EnterCriticalSection(m_pcs);}
//----------------------------------------------------------------------------------------------------------------------
void TGXbStack::UnLock(void){if(m_pcs != 0 )LeaveCriticalSection(m_pcs);}
//----------------------------------------------------------------------------------------------------------------------

