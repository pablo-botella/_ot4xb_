#pragma once
#pragma pack(push , 4)
#ifdef __cplusplus
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TLdList_Item
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , container/list
   | desc: The header of a record of a {{ilink: <cpp-class TLdList_Master> TLdList_Master}}: the two links,
     followed in memory by the record's own data. A record is a block of the list's item size, zero-filled
     when created, that starts with this header; the list never looks past it.
     | _kw_: TLdList_Item, Class }}*/
class OT4XB_API TLdList_Item : public T_ot4xb_base
{
   public:
   /*{{|member_: `TLdList_Item* m_pPrev` | desc_: The previous record, 0 for the first. }}*/
   TLdList_Item * m_pPrev;
   /*{{|member_: `TLdList_Item* m_pNext` | desc_: The next record, 0 for the last. }}*/
   TLdList_Item * m_pNext;
   // --------------------------------
};
/*{{end-cpp-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TLdList_Master
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , container/list
   | desc: A doubly linked list of fixed-size records navigated like a work area: a current record, a record
     number, BOF and EOF, Skip(), Goto(), Append(), Insert() and Delete(). It is the engine of the Xbase++
     class TLdList and its GWST-mapped records: the records are blocks of **m_nItemSize** bytes starting with
     a {{ilink: <cpp-class TLdList_Item> TLdList_Item}} header, and GetGhPt() gives the address of the
     current-record pointer, which is what the Xbase++ side keeps in its helper pointer to read and write
     the fields of the current record in place. Three optional callbacks let the owner dispose of a record's
     own resources, fix up a cloned record, and clean up when the list dies. Whole runs of records can be
     cloned, detached and attached between lists without copying.
     | _kw_: TLdList_Master, Class }}*/
class OT4XB_API TLdList_Master : public T_ot4xb_base
{
   public:
   /*{{|member_: `DWORD m_dwHSize` | desc_: sizeof( TLdList_Master ), a version check for the Xbase++ side. }}*/
   DWORD              m_dwHSize; // sizeof( TLdList_Master )
   /*{{|member_: `TLdList_Item* m_pFirst` | desc_: First record, 0 when empty. }}*/
   TLdList_Item *     m_pFirst;
   /*{{|member_: `TLdList_Item* m_pLast` | desc_: Last record, 0 when empty. }}*/
   TLdList_Item *     m_pLast;
   /*{{|member_: `TLdList_Item* m_pCurrent` | desc_: Current record, 0 at BOF, EOF or when empty. }}*/
   TLdList_Item *     m_pCurrent;
   /*{{|member_: `DWORD m_nItemSize` | desc_: Bytes of one record, header included. }}*/
   DWORD              m_nItemSize;
   /*{{|member_: `LONG m_nItems` | desc_: Number of records. }}*/
   LONG               m_nItems;
   /*{{|member_: `LPSTR m_pClassName` | desc_: Name of the Xbase++ class of the records (a copy), 0 when
      none was given. }}*/
   LPSTR              m_pClassName;
   /*{{|member_: `DWORD m_dwClsCRC32` | desc_: The GWST name CRC of that class name. }}*/
   DWORD              m_dwClsCRC32;
   /*{{|member_: `LONG m_nRecNo` | desc_: Number of the current record, 1-based. }}*/
   LONG               m_nRecNo;
   /*{{|member_: `DWORD m_dwStatus` | desc_: Flags: 1 BOF, 2 EOF, 4 empty (an empty list has all three). }}*/
   DWORD              m_dwStatus; // Flags: 1 BOF | 2 EOF | 4 Empty
   /*{{|member_: `_PFN_TLDLIST_ m_pf_OnDestroyItem` | desc_: `LONG __stdcall fn( DWORD* pCargo, void* pItem, void* )`,
      called before a record is freed, to release what the record owns. 0 when not needed. }}*/
   _PFN_TLDLIST_      m_pf_OnDestroyItem;
   /*{{|member_: `_PFN_TLDLIST_ m_pf_OnCloneItem` | desc_: `LONG __stdcall fn( DWORD* pCargo, void* pSrc, void* pDst )`,
      called after a record has been copied byte by byte, to duplicate what the copy must not share. }}*/
   _PFN_TLDLIST_      m_pf_OnCloneItem;
   /*{{|member_: `_PFN_TLDLIST_ m_pf_OnDestroy` | desc_: `LONG __stdcall fn( DWORD* pCargo, void*, void* )`,
      called when the list itself is destroyed, after its records. }}*/
   _PFN_TLDLIST_      m_pf_OnDestroy;
   /*{{|member_: `DWORD m_dwpfCargo` | desc_: The cargo the callbacks receive by address. }}*/
   DWORD              m_dwpfCargo;
   // --------------------------------
   /*{{|method_: `TLdList_Master( LPSTR pClsName, DWORD nItemSize )` | desc_: An empty list of records of
      **nItemSize** bytes, remembering the class name and its CRC. The callbacks and the cargo are set by the
      owner afterwards. }}*/
   TLdList_Master(LPSTR pClsName , DWORD nItemSize);
   /*{{|method_: `~TLdList_Master( void )` | desc_: Destroys every record (callback included), calls the
      destroy callback of the list and frees the class name. }}*/
   ~TLdList_Master(void);
   // --------------------------------
   /*{{|method_: `LONG GetGhPt( void )` | desc_: The address of **m_pCurrent**, for the GWST helper pointer:
      through it the Xbase++ object always sees the current record, whichever it is. }}*/
   LONG GetGhPt( void );
   // --------------------------------
   /*{{|method_: `void _DestroyItem_( TLdList_Item* pItem )` | desc_: Runs the destroy-item callback and
      frees the record. }}*/
   void _DestroyItem_( TLdList_Item * pItem );
   // --------------------------------
   /*{{|method_: `BOOL Bof( void )` | desc_: Positioned before the first record. }}*/
   BOOL Bof( void );
   /*{{|method_: `BOOL Eof( void )` | desc_: Positioned after the last record. }}*/
   BOOL Eof( void );
   /*{{|method_: `LONG RecNo( void )` | desc_: The current record number: 0 at BOF or on an empty list, the
      count plus one at EOF. }}*/
   LONG RecNo(void);
   /*{{|method_: `BOOL GoTop( void )` | desc_: Goes to the first record; FALSE on an empty list. }}*/
   BOOL GoTop(void);
   /*{{|method_: `BOOL GoBottom( void )` | desc_: Goes to the last record; FALSE on an empty list. }}*/
   BOOL GoBottom( void );
   /*{{|method_: `void GoBof( void )` | desc_: Positions before the first record (no current record). }}*/
   void GoBof(void);
   /*{{|method_: `void GoEof( void )` | desc_: Positions after the last record (no current record). }}*/
   void GoEof( void );
   /*{{|method_: `BOOL Skip( LONG nSkip )` | desc_: Moves **nSkip** records (negative: backwards). TRUE when
      the whole move was possible; otherwise the list is left at EOF or BOF and FALSE returned. }}*/
   BOOL Skip( LONG nSkip );
   /*{{|method_: `LONG Skipper( LONG nSkip )` | desc_: The move behind Skip(): from BOF or EOF it first goes
      to the first or last record, then moves as far as it can and returns the records actually moved. }}*/
   LONG Skipper( LONG nSkip );
   /*{{|method_: `BOOL Goto( LONG nRecord )` | desc_: Goes to record **nRecord** by the shortest walk from the
      current position or from either end. A number below 1 leaves the list at BOF, one past the count at
      EOF, both returning FALSE. }}*/
   BOOL Goto( LONG nRecord );
   /*{{|method_: `BOOL Append( void )` | desc_: Adds a new zero-filled record at the end and makes it
      current. }}*/
   BOOL Append( void );
   /*{{|method_: `BOOL Insert( void )` | desc_: Adds a new zero-filled record before the current one (at the
      end when at EOF, at the start when at BOF) and makes it current. }}*/
   BOOL Insert( void );
   /*{{|method_: `BOOL Delete( void )` | desc_: Destroys the current record; the next one (or the last, when
      it was the last) becomes current. FALSE at BOF or EOF. }}*/
   BOOL Delete( void );
   /*{{|method_: `BOOL SwapRecords( LONG n1, LONG n2 )` | desc_: Exchanges the positions of two records,
      keeping the current record number. FALSE when a number is out of range. }}*/
   BOOL SwapRecords( LONG n1 , LONG n2 );
   /*{{|method_: `TLdList_Item* CloneItem( TLdList_Item* pSrc )` | desc_: A new unlinked copy of a record
      (bytes copied, then the clone callback); 0 for a null source. }}*/
   TLdList_Item * CloneItem( TLdList_Item * pSrc);
   /*{{|method_: `TLdList_Item* CloneItems( LONG nItems, LONG* pnCount = 0 )` | desc_: A new linked run of
      copies: **nItems** records from the current one, or the whole list with -1. Their number comes back
      in **pnCount**. Nothing is cloned from BOF or EOF unless the whole list is asked for. }}*/
   TLdList_Item * CloneItems( LONG nItems , LONG * pnCount = 0);
   /*{{|method_: `TLdList_Item* DetachItems( LONG nItems, LONG* pnCount = 0 )` | desc_: Unlinks **nItems**
      records from the current one (the whole list with -1) and returns them as a run, their number in
      **pnCount**; the list closes the gap and the record after the run becomes current. }}*/
   TLdList_Item * DetachItems( LONG nItems , LONG * pnCount = 0);
   /*{{|method_: `LONG AttachItems( TLdList_Item* pFirst, LONG* pnCount = 0 )` | desc_: Links a run of records
      (from CloneItems() or DetachItems() of a list with the same record layout) after the current one, at
      the start when at BOF, at the end when at EOF. Returns their number. }}*/
   LONG AttachItems( TLdList_Item * pFirst  , LONG * pnCount= 0);
   /*{{|method_: `LONG StealItems( TLdList_Master* pList, LONG nItems )` | desc_: DetachItems() from
      **pList** and AttachItems() here. }}*/
   LONG StealItems( TLdList_Master * pList , LONG nItems );
   /*{{|method_: `LONG MergeClone( TLdList_Master* pList )` | desc_: Attaches a clone of the whole of
      **pList**. }}*/
   LONG MergeClone( TLdList_Master * pList );
   /*{{|method_: `LONG EatList( TLdList_Master* pList )` | desc_: Steals every record of **pList**, which is
      left empty. }}*/
   LONG EatList( TLdList_Master * pList);
   /*
   LONG InsertFromIStream( IStream * pStream , LONG nRecordsAtTime , HWND hNotify = 0 , UINT nMsg = 0);
   */
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
#endif
#pragma pack(pop)
