
#if 0
#pragma once
class OT4XB_API atomic_resource_lock_t : public T_ot4xb_base
{
   public:
   // -----------------------------------------------------------------
   class element_t
   {
      public:
      char m_key[24]   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      char m_owner[24] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
      FILETIME m_started = 0;
      DWORD m_wp = 0;
      DWORD m_lp = 0;
      BOOL key_compare(LPSTR key);
      BOOL owner_compare(LPSTR owner);
      void put(LPSTR key, LPSTR owner, DWORD wp, DWORD lp,BOOL bSetFileTime = TRUE);
      void clear();

   };
   DWORD m_buffer_cb = 0;
   DWORD m_element_capacity = 0;
   element_t* m_elements = 0;
   LPSTR m_filename = 0;
   HANDLE m_file_handle = INVALID_HANDLE_VALUE;
   DWORD m_begin_lock_offset = INVALID_FILE_SIZE;
   DWORD m_lock_cb = 0;

   // -----------------------------------------------------------------
   atomic_resource_lock_t(LPSTR filename, DWORD max = 4096);
   ~atomic_resource_lock_t();
   BOOL open_file();
   void close_file();
   BOOL lock_item(LPSTR key, LPSTR owner, DWORD wp, DWORD lp);
   BOOL release_item(LPSTR key, LPSTR owner, DWORD & wp, DWORD & lp);
   BOOL try_lock_file(DWORD retry = 20, DWORD wait = 200, DWORD offset = 0, DWORD bytes = -1 );
   BOOL is_file_locked();
   BOOL try_lock_file_and_read(DWORD retry = 20, DWORD wait = 200); 
   element_t * search_element_by_key(LPSTR key);
   void unlock_file();
};
#endif