//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
// ---------------------------------------------------------------------------
#ifdef _OT4XB_API_
#ifdef __cplusplus
// ---------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
class TXbClsGwstItem
{
   public:
       DWORD              m_dwNameCrc32;
       DWORD              m_dwShift;
       DWORD              m_dwSize;
       WORD               m_wChildPos;
       WORD               m_wGwstType;
       DWORD              m_dwPos;
       ContainerHandle    m_conClass;
       TXbClsGwstItem *   m_pNext;
       // ---------------------------------------------------------------------------------
       void * operator new( unsigned int n);
       void operator delete( void * p);
};
//-----------------------------------------------------------------------------------------------------------------------
class TXbClsMItem
{
   public:
       ContainerHandle m_conName;
       ULONG           m_nFlags;
       ContainerHandle m_conBlock;
       BOOL            m_bSetGet;
       TXbClsMItem *   m_pNext;
       // ---------------------------------------------------------------------------------
       void * operator new( unsigned int n);
       void operator delete( void * p);
};
// -----------------------------------------------------------------------------------------------------------------
class TXbClsVItem
{
   public:
       ContainerHandle m_conName;
       ULONG           m_nFlags;
       TXbClsVItem *   m_pNext;
       // ---------------------------------------------------------------------------------
       void * operator new( unsigned int);
       void operator delete( void * p);
};
// -----------------------------------------------------------------------------------------------------------------
class TXbClsPItem
{
   public:
       ContainerHandle m_cono;
       TXbClsPItem *   m_pNext;
       // ---------------------------------------------------------------------------------
       void * operator new( unsigned int);
       void operator delete( void * p);
};
// -----------------------------------------------------------------------------------------------------------------
#endif
#endif