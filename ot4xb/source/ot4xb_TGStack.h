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
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TGXbStack
   | category: c-api/classes , container/stack
   | desc: A double-ended list of Xbase++ values (ContainerHandle) kept in C++: Push() and Pop() at the top,
     Add() at the bottom, and the whole list evaluated with a code block or copied to an array. The stack
     owns the containers it holds: what is left inside when it is deleted is released. It is the engine of the
     Xbase++ class {{ilink: <class TGXbStack> TGXbStack}}.
   | note: The object is initialised by its `operator new`, not by a constructor, so it must be created with
     `new` and freed with `delete`. It is not synchronised until SyncMode() is called; from then on Lock() and
     UnLock() bracket the accesses (the methods do not lock by themselves).
     | _kw_: TGXbStack, Class }}*/
class OT4XB_API TGXbStack
{
   public:
       /*{{|member_: `TGXbItem* m_pTop` | desc_: The top item (the last pushed), 0 when empty. }}*/
       TGXbItem  *  m_pTop;
       /*{{|member_: `TGXbItem* m_pBottom` | desc_: The bottom item (the last added), 0 when empty. }}*/
       TGXbItem  *  m_pBottom;
       /*{{|member_: `UINT m_nCount` | desc_: Number of items. }}*/
       UINT  m_nCount;
       /*{{|member_: `CRITICAL_SECTION* m_pcs` | desc_: The critical section created by SyncMode(), 0
          before. }}*/
       CRITICAL_SECTION *  m_pcs;
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void* operator new( unsigned int )` | desc_: Allocates in the ot4xb heap and zeroes the
          members: an empty, unsynchronised stack. }}*/
       void * operator new( unsigned int );
       /*{{|method_: `void operator delete( void* p )` | desc_: Pops and releases every remaining value,
          deletes the critical section when there is one, and frees the object. }}*/
       void operator delete( void * p);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `ContainerHandle Head( void )` | desc_: The value at the top, still owned by the stack;
          NULLCONTAINER when empty. }}*/
       ContainerHandle Head( void );
       /*{{|method_: `ContainerHandle Tail( void )` | desc_: The value at the bottom, still owned by the stack;
          NULLCONTAINER when empty. }}*/
       ContainerHandle Tail( void );
       /*{{|method_: `ContainerHandle Pop( void )` | desc_: Removes the top item and returns its value, whose
          ownership passes to the caller (release it); NULLCONTAINER when empty. }}*/
       ContainerHandle Pop( void );
       /*{{|method_: `void Push( ContainerHandle )` | desc_: Puts a value on top. The container is taken as
          it is, not copied: the stack owns it from now on. }}*/
       void Push( ContainerHandle );
       /*{{|method_: `void Add( ContainerHandle )` | desc_: Puts a value at the bottom, same ownership as
          Push(). }}*/
       void Add( ContainerHandle );
       /*{{|method_: `void StackEval( ContainerHandle conBlock, ContainerHandle conCargo )`
          | desc_: Evaluates the code block **conBlock** for every value from top to bottom with four
            parameters: the value, **conCargo**, the zero-based position and the item count. The return
            values are discarded. }}*/
       void StackEval( ContainerHandle,ContainerHandle);
       /*{{|method_: `void ReverseEval( ContainerHandle conBlock, ContainerHandle conCargo )`
          | desc_: Same as StackEval() from bottom to top. }}*/
       void ReverseEval( ContainerHandle,ContainerHandle);
       /*{{|method_: `void ToXbArray( ContainerHandle conRet, BOOL bReverse )`
          | desc_: Puts into **conRet** a new Xbase++ array with a copy of every value, top to bottom, or
            bottom to top with **bReverse**. }}*/
       void ToXbArray(ContainerHandle, BOOL );
       /*{{|method_: `UINT Count( void )` | desc_: Number of items. }}*/
       UINT Count(void){ return m_nCount; }
       /*{{|method_: `void SyncMode( void )` | desc_: Creates the critical section that Lock() and UnLock()
          use; nothing happens when it already exists. }}*/
       void SyncMode( void );
       /*{{|method_: `void Lock( void )` | desc_: Enters the critical section (no effect without SyncMode()). }}*/
       void Lock(void);
       /*{{|method_: `void UnLock( void )` | desc_: Leaves the critical section. }}*/
       void UnLock(void);
};
/*{{end-cpp-class}}*/
//----------------------------------------------------------------------------------------------------------------------
#endif // __cplusplus
//----------------------------------------------------------------------------------------------------------------------
#endif








