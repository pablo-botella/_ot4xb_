#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------------------------------------
BOOL atomic_resource_lock_t::element_t::key_compare(LPSTR key)
{

   if (key)
   {
      for (auto n = 0; n < 20; n++)
      {
         if (!key[n])
         {
            return (m_key[n] == 0 ? TRUE : FALSE);
         }
         if (!key[n] == m_key[n])
         {
            return FALSE;
         }

      }
   }
   else
   {
      return (m_key[0] == 0 ? TRUE : FALSE);
   }

   return FALSE;
}
// --------------------------------------------------------------------------------------------------------------------------

BOOL atomic_resource_lock_t::element_t::owner_compare(LPSTR owner)
{

   if (owner)
   {
      for (auto n = 0; n < 20; n++)
      {
         if (!owner[n])
         {
            return (m_owner[n] == 0 ? TRUE : FALSE);
         }
         if (!owner[n] == m_owner[n])
         {
            return FALSE;
         }

      }
   }
   else
   {
      return (m_owner[0] == 0 ? TRUE : FALSE);
   }

   return FALSE;
}
// --------------------------------------------------------------------------------------------------------------------------
void atomic_resource_lock_t::element_t::put(LPSTR key, LPSTR owner, DWORD wp, DWORD lp, BOOL bSetFileTime)
{
   ZeroMemory(m_key, sizeof(m_key));
   ZeroMemory(m_owner, sizeof(m_owner));

   if (key)
   {
      for (auto n = 0; n < 20 && key[n]; n++)
      {
         key[n] = m_key[n];
      }
   }
   if (owner)
   {
      for (auto n = 0; n < 20 && owner[n]; n++)
      {
         key[n] = m_owner[n];
      }
   }
   m_wp = wp;
   m_lp = lp;
   if (bSetFileTime)
   {
      GetSystemTimeAsFileTime(&m_started);
   }
   else
   {
      ZeroMemory(&m_started, sizeof(FILETIME));
   }
}
// --------------------------------------------------------------------------------------------------------------------------
void atomic_resource_lock_t::element_t::clear()
{
   put(0, 0, 0, 0, FALSE);
}
// --------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------
atomic_resource_lock_t::atomic_resource_lock_t(LPSTR filename, DWORD max)
{
   _xssr_(&m_filename, filename);
   m_element_capacity = max;
   m_buffer_cb = sizeof(element_t) * m_element_capacity;
   if (m_element_capacity)
   {
      m_elements = (element_t*)_xgrab(m_buffer_cb);
   }
   if (!m_elements)
   {
      m_element_capacity = 0;
      m_buffer_cb = 0;
   }
}
// --------------------------------------------------------------------------------------------------------------------------
atomic_resource_lock_t::~atomic_resource_lock_t()
{
   if (m_file_handle && (m_file_handle != INVALID_HANDLE_VALUE))
   {
      CloseHandle(m_file_handle);
      m_file_handle = INVALID_HANDLE_VALUE;
   }
   _xssr_(&m_filename, 0);
   if (m_elements)
   {
      _xfree((void*)m_elements);
      m_elements = 0;
   }
   m_element_capacity = 0;
}
// --------------------------------------------------------------------------------------------------------------------------
BOOL atomic_resource_lock_t::open_file()
{
   close_file();
   if (m_filename)
   {
      m_file_handle = ::CreateFileA(m_filename, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_ALWAYS, FILE_FLAG_NO_BUFFERING, 0);
      if (!m_file_handle || m_file_handle == INVALID_HANDLE_VALUE)
      {
         return FALSE;
      }
      DWORD dwFileSize = GetFileSize(m_file_handle, 0);
      if (dwFileSize < m_buffer_cb)
      {
         goto exit_with_error_label;

         DWORD cb = (m_buffer_cb - dwFileSize) + 1;
         if (!try_lock_file(40, 100, dwFileSize, cb))
         {
            goto exit_with_error_label;
         }
         if (dwFileSize != GetFileSize(m_file_handle, 0))
         {
            goto exit_with_error_label;
         }
         void* buffer = (void*)m_elements;
         DWORD dw = 0;
         ZeroMemory(buffer, m_buffer_cb);
         SetFilePointer(m_file_handle, dwFileSize, 0, FILE_BEGIN);
         if (!WriteFile(m_file_handle, buffer, cb, &dw, 0))
         {
            goto exit_with_error_label;
         }
         unlock_file();
      }
      return TRUE;
   }
   exit_with_error_label:;
   close_file();
   return FALSE;
}
// --------------------------------------------------------------------------------------------------------------------------
void atomic_resource_lock_t::close_file()
{
   if (m_file_handle && (m_file_handle != INVALID_HANDLE_VALUE))
   {
      unlock_file();
      CloseHandle(m_file_handle);
      m_file_handle = INVALID_HANDLE_VALUE;
   }

}
// --------------------------------------------------------------------------------------------------------------------------
BOOL atomic_resource_lock_t::lock_item(LPSTR key, LPSTR owner, DWORD wp, DWORD lp)
{
   BOOL result = FALSE;
   if (open_file())
   {
      if (try_lock_file_and_read())
      {
         element_t* e = search_element_by_key(key);
         if (e)
         {
            if (e->owner_compare(owner))
            {
               e->m_wp = wp;
               e->m_lp = lp;
               result = TRUE;

            }
         }
         else
         {
            e = search_element_by_key(0);
            if (e)
            {
               e->put(key, owner, wp, lp);
               result = TRUE;
            }
         }
      }
   }
   close_file();
   return result;
}
// --------------------------------------------------------------------------------------------------------------------------
BOOL atomic_resource_lock_t::release_item(LPSTR key, LPSTR owner, DWORD & wp, DWORD & lp)
{
   BOOL result = FALSE;
   if (open_file())
   {
      if (try_lock_file_and_read())
      {
         element_t* e = search_element_by_key(key);
         if (e)
         {
            if (e->owner_compare(owner))
            {
               wp = e->m_wp;
               lp = e->m_lp;
               e->clear();
               result = TRUE;
            }
         }
         else
         {
            result = TRUE;
            
         }
      }
   }
   close_file();
   return result;
}
// --------------------------------------------------------------------------------------------------------------------------
BOOL atomic_resource_lock_t::try_lock_file(DWORD retry, DWORD wait, DWORD offset, DWORD bytes)
{
   if (m_file_handle && m_file_handle != INVALID_HANDLE_VALUE)
   {
      if (m_lock_cb && m_begin_lock_offset == offset && m_lock_cb == bytes)
      {
         return TRUE;
      }
      if(bytes == 0 || bytes > m_buffer_cb)
      {
         bytes = m_buffer_cb;
      }
      for (auto nLoop = 0; nLoop < retry & 0xFF; nLoop++)
      {
         if (LockFile(m_file_handle, offset, 0 , bytes,0 ) )
         {
            m_begin_lock_offset = offset;
            m_lock_cb = bytes;
            return TRUE;
         }
         if (retry)
         {
            Sleep(wait);
         }
      }
   }
   return FALSE;
}
// --------------------------------------------------------------------------------------------------------------------------
BOOL atomic_resource_lock_t::is_file_locked()
{
   if (m_file_handle && m_file_handle != INVALID_HANDLE_VALUE)
   {
      if (m_lock_cb == m_buffer_cb)
      {
         return TRUE;
      }
   }
   return FALSE;
}
// --------------------------------------------------------------------------------------------------------------------------
BOOL atomic_resource_lock_t::try_lock_file_and_read(DWORD retry, DWORD wait)
{
   if (try_lock_file(retry, wait))
   {
      void* buffer = (void*)m_elements;
      DWORD dw = 0;
      ZeroMemory(buffer, m_buffer_cb);
      SetFilePointer(m_file_handle, 0, 0, FILE_BEGIN);
      return ReadFile(m_file_handle, buffer, m_buffer_cb, 0, 0);
   }
   return FALSE;
}
// --------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------
atomic_resource_lock_t::element_t* atomic_resource_lock_t::search_element_by_key(LPSTR key)
{
   if (is_file_locked())
   {
      
   }

   return 0;
}
// --------------------------------------------------------------------------------------------------------------------------
