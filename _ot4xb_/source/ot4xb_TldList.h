#pragma once
#pragma pack(push , 4)
#ifdef __cplusplus
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API TLdList_Item : public T_ot4xb_base
{
   public:
   TLdList_Item * m_pPrev;
   TLdList_Item * m_pNext;
   // --------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API TLdList_Master : public T_ot4xb_base
{
   public:
   DWORD              m_dwHSize; // sizeof( TLdList_Master )
   TLdList_Item *     m_pFirst;
   TLdList_Item *     m_pLast;
   TLdList_Item *     m_pCurrent;
   DWORD              m_nItemSize;
   LONG               m_nItems;   
   LPSTR              m_pClassName;
   DWORD              m_dwClsCRC32;
   LONG               m_nRecNo;
   DWORD              m_dwStatus; // Flags: 1 BOF | 2 EOF | 4 Empty
   _PFN_TLDLIST_      m_pf_OnDestroyItem;
   _PFN_TLDLIST_      m_pf_OnCloneItem;
   _PFN_TLDLIST_      m_pf_OnDestroy;
   DWORD              m_dwpfCargo;
   // --------------------------------
   TLdList_Master(LPSTR pClsName , DWORD nItemSize);
   ~TLdList_Master(void);
   // --------------------------------
   LONG GetGhPt( void );
   // --------------------------------
   void _DestroyItem_( TLdList_Item * pItem );
   // --------------------------------
   BOOL Bof( void );
   BOOL Eof( void );
   LONG RecNo(void);
   BOOL GoTop(void);
   BOOL GoBottom( void );
   void GoBof(void);
   void GoEof( void );
   BOOL Skip( LONG nSkip );
   LONG Skipper( LONG nSkip );
   BOOL Goto( LONG nRecord );
   BOOL Append( void );
   BOOL Insert( void );
   BOOL Delete( void );
   BOOL SwapRecords( LONG n1 , LONG n2 );
   TLdList_Item * CloneItem( TLdList_Item * pSrc);
   TLdList_Item * CloneItems( LONG nItems , LONG * pnCount = 0);
   TLdList_Item * DetachItems( LONG nItems , LONG * pnCount = 0);
   LONG AttachItems( TLdList_Item * pFirst  , LONG * pnCount= 0);
   LONG StealItems( TLdList_Master * pList , LONG nItems );
   LONG MergeClone( TLdList_Master * pList );
   LONG EatList( TLdList_Master * pList);
   /*
   LONG InsertFromIStream( IStream * pStream , LONG nRecordsAtTime , HWND hNotify = 0 , UINT nMsg = 0);
   */
};
// -----------------------------------------------------------------------------------------------------------------
#endif
#pragma pack(pop)
