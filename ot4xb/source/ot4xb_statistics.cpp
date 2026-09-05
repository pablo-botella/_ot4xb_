//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <search.h>
// -----------------------------------------------------------------------------------------------------------------
list_of_float_double_t::list_of_float_double_t( vheap_flags dw, OT4XB_VHEAP* vheap ) 
{
	m_nCapacity = 0;
	m_nCount    = 0;
	m_pValues   = 0;
	m_last_error = e_no_error;
	vheap_on_init( dw, vheap );
}
// -----------------------------------------------------------------------------------------------------------------
list_of_float_double_t::~list_of_float_double_t( void ) 
{ 
	m_last_error = e_no_error;
	if ( m_pValues != 0 )
	{
		free_bytes( (void *) m_pValues );
	}
	m_pValues = 0;
	vheap_on_destroy();
}
// -----------------------------------------------------------------------------------------------------------------
void   list_of_float_double_t::Grow( UINT nMin )
{
	m_last_error = e_no_error;
	UINT     nCapacity = max( m_nCapacity, nMin );
	double*  pValues;
	
	if ( nCapacity < 16 ) {		nCapacity = 16; 	    }
	else if ( nCapacity < 256 ) { nCapacity = 256;   }
	else if ( nCapacity < 1024 ) { nCapacity = 1024; }
	else if ( nCapacity < 4096 ) { nCapacity = 4096; }
	else if ( nCapacity < 65536 ) { nCapacity = 65536; }
	else { nCapacity += 65536; }
	
	if ( nCapacity > m_nCapacity )
	{
		pValues = (double *) alloc_bytes( nCapacity * sizeof( double ) );
		if ( m_pValues != 0 )
		{
			UINT i;
			for ( i = 0; i < m_nCount; i++ ) pValues[i] = m_pValues[i];
			free_bytes( (void*) m_pValues );
		}
		m_pValues = pValues;
		m_nCapacity = nCapacity;
	}
}
// -----------------------------------------------------------------------------------------------------------------
double list_of_float_double_t::Add( double v ) 
{ 
	m_last_error = e_no_error;
	if( isnan(v) )
	{
		m_last_error = e_nan_parameter;
		v = 0.0000;
	}
	if ( m_nCapacity <= m_nCount ) Grow();
   m_pValues[m_nCount] = v;
	m_nCount++;
	return v;
}
// -----------------------------------------------------------------------------------------------------------------
void list_of_float_double_t::Add( double * pv, UINT count )
{
	if ( pv && count )
	{
		UINT n;
		Grow( m_nCount + count + 1 );
		for ( n = 0; n < count; n++ )
		{
			Add( pv[n] );
		}
	}
}
// -----------------------------------------------------------------------------------------------------------------
void list_of_float_double_t::Insert( UINT pos, double * pv, UINT count )
{
	
	if ( pv && count )
	{
		if( (pos == (UINT) -1 ) || m_nCount == 0)
		{
			Add( pv, count );
			return;
		}
		if ( pos > m_nCount )
		{
			m_last_error = e_out_of_range;
			return;
		}
		Grow( m_nCount + count + 1 );

		UINT n;
		for ( n = m_nCount; n > pos; n-- ) // top-down: shift by count without overlapping
		{
			m_pValues[n + count - 1] = m_pValues[n - 1];
		}
		for ( n = 0; n < count; n++ )
		{
			m_pValues[pos + n] = pv[n];
		}
		m_nCount += count;
	}
}
// -----------------------------------------------------------------------------------------------------------------
double list_of_float_double_t::Get( UINT pos ) 
{ 
	m_last_error = e_no_error; 
	if ( pos < m_nCount ) { return m_pValues[pos]; }
	m_last_error = e_out_of_range;
	return 0.0000;
}
// -----------------------------------------------------------------------------------------------------------------
double list_of_float_double_t::Replace( UINT pos , double v )
{ 
	m_last_error = e_no_error;
	if ( isnan( v ) )
	{
		m_last_error = e_nan_parameter;
		v = 0.0000;
	}
	if ( pos <  m_nCount )
	{
		double vOld = m_pValues[pos];
		m_pValues[pos] = v;
		return vOld;
	}
	m_last_error = e_out_of_range;
	return 0.0000;
}
// -----------------------------------------------------------------------------------------------------------------
void list_of_float_double_t::Replace( UINT pos, double * pv, UINT count )
{
	m_last_error = e_no_error;
	if ( pv && count )
	{
		UINT n;
		for ( n = 0; (n < count) && (m_last_error == e_no_error); n++ )
		{
			Replace( pos + n, pv[n]);
		}
	}
}
// -----------------------------------------------------------------------------------------------------------------
UINT   list_of_float_double_t::Count( UINT nSkip, UINT nMax )
{
	UINT start = min( nSkip, m_nCount );
	UINT count = min( ( m_nCount - start ), nMax );
	m_last_error = e_no_error;
	return count; 
}
// -----------------------------------------------------------------------------------------------------------------
double list_of_float_double_t::Insert( UINT nPos, double v ) 
{ 																				  
	UINT n;
	m_last_error = e_no_error;
	if ( isnan( v ) )
	{
		m_last_error = e_nan_parameter;
		v = 0.0000;
	}
	if ( nPos == (UINT) -1 ) 
	{
		return Add( v ); 
	}
	if ( nPos > m_nCount ) 
	{
		m_last_error = e_out_of_range;
		return 0.0000;
	}
	if ( m_nCount == 0 ) { return Add( v ); }
	if ( m_nCapacity <= m_nCount ) { Grow(); }
	for ( n = m_nCount; n > nPos; n-- ) { m_pValues[n] = m_pValues[( n - 1 )]; }
	m_pValues[nPos] = v;
	m_nCount++;			
	return v;
}
// -----------------------------------------------------------------------------------------------------------------
double list_of_float_double_t::Remove( UINT nPos ) 
{ 
	UINT n;
	double  v;
	m_last_error = e_no_error;
	if ( nPos >= m_nCount )
	{
		m_last_error = e_out_of_range;
		return 0.0000;
	}
	if ( m_nCount == 0 ) 
	{
		m_last_error = e_empty_list;
		return 0.0000;
	}
	v = m_pValues[nPos];
	m_nCount--;
	for ( n = nPos; n < m_nCount; n++ ) m_pValues[n] = m_pValues[( n + 1 )];
	m_pValues[m_nCount] = 0.0000;
	return v;
}
// -----------------------------------------------------------------------------------------------------------------
double list_of_float_double_t::Pop( void ) 
{ 
	m_last_error = e_no_error;
	if ( m_nCount ) { return Remove( m_nCount - 1 ); }
	return nan("");
}
// -----------------------------------------------------------------------------------------------------------------
double list_of_float_double_t::Tail( void ) 
{ 
	m_last_error = e_no_error;
	if ( m_nCount ) { return m_pValues[( m_nCount - 1 )]; }
	return nan("");
}
// -----------------------------------------------------------------------------------------------------------------
void   list_of_float_double_t::Truncate( UINT new_count  ) 
{ 
	m_last_error = e_no_error;
	if ( new_count < m_nCount )
	{
		UINT n;
		for ( n = new_count; n < m_nCount; n++ ) { m_pValues[n] = 0; }
		m_nCount = new_count;
	}
}
// -----------------------------------------------------------------------------------------------------------------
double list_of_float_double_t::CalculateSum( UINT nSkip, UINT nMax )
{
	double result = 0.0000;
	UINT start = min( nSkip, m_nCount );
	UINT count = min( ( m_nCount - start ) , nMax );
	UINT n;
	m_last_error = e_no_error;
	if ( !count )
	{
		m_last_error = e_empty_list;
		return 0.0000;
	}
	for ( n = 0 ; n < count; n++ )
	{
      result += m_pValues[n + start];
	}
	return result;
}
//------------------------------------------------------------------------------------------------------------------------------
double list_of_float_double_t::CalculateMean( UINT nSkip, UINT nMax )
{
	double result = 0.0000;
	UINT start = min( nSkip, m_nCount );
	UINT count = min( ( m_nCount - start ), nMax );
	UINT n;
	m_last_error = e_no_error;
	if ( !count )
	{
		m_last_error = e_empty_list;
		return 0.0000;
	}
	for ( n = 0; n < count; n++ )
	{
		result += m_pValues[n + start];
	}
	return result / ( (double) count );
}
//------------------------------------------------------------------------------------------------------------------------------
double list_of_float_double_t::CalculatePopulationVariance( UINT nSkip, UINT nMax )
{
	double nd = 0.0000;
	UINT start = min( nSkip, m_nCount );
	UINT count = min( ( m_nCount - start ), nMax );
	UINT n;
	double mean;
	if ( !count )
	{
		m_last_error = e_empty_list;
		return 0.0000;
	}
	mean = CalculateMean( nSkip, nMax ); //  also set the last error
	for ( n = 0; n < count; n++ )
	{
		nd += ( m_pValues[n + start] - mean ) * ( m_pValues[n + start] - mean );
	}

	return nd / (double) count;
}
//------------------------------------------------------------------------------------------------------------------------------
double list_of_float_double_t::CalculateSampleVariance( UINT nSkip, UINT nMax )
{
	double nd = 0.0000;
	UINT start = min( nSkip, m_nCount );
	UINT count = min( ( m_nCount - start ), nMax );
	UINT n;
	double mean;
	if ( !count )
	{
		m_last_error = e_empty_list;
		return 0.0000;
	}
	if ( count  == 1)
	{
		m_last_error = e_will_produce_nan;
		return 0.0000;
	}
	
	mean = CalculateMean( nSkip, nMax ); //  also set the last error
	for ( n = 0; n < count; n++ )
	{
		nd += ( m_pValues[n + start] - mean) * ( m_pValues[n + start] - mean );
	}

	return nd / (double)(count-1);
}
//------------------------------------------------------------------------------------------------------------------------------

double list_of_float_double_t::CalculatePopulationStandardDeviation( UINT nSkip, UINT nMax )
{
	double v = CalculatePopulationVariance( nSkip, nMax );
	if ( m_last_error )
	{
			return 0.000;
	}
	return sqrt(v);
}
//------------------------------------------------------------------------------------------------------------------------------

double list_of_float_double_t::CalculateSampleStandardDeviation( UINT nSkip, UINT nMax )
{
	double v = CalculateSampleVariance( nSkip, nMax );
	if ( m_last_error )
	{
		return 0.000;
	}
	return sqrt( v );
}
//------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_new
            | syntax_: `void * list_of_float_double_t_new( DWORD flags, void * vheap )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_new
            | _kw_: double list, statistics, create, vheap
   }}*/
/*{{|desc: Creates a new empty list of double values with simple statistics support and returns its handle.
      With flags 0 the value buffer is allocated from the Xbase++ runtime memory manager. flags takes
      vheap_flags bits (ot4xb_cpp_exported.h): 0x800 uses the vheap parameter, 0x100 creates a private heap
      owned by the list, 0x200 destroys the used heap together with the list.
    | params:
    - `flags` DWORD - vheap_flags combination; 0 uses the Xbase++ runtime memory manager.
    - `vheap` void * - OT4XB_VHEAP pointer used when flags contains 0x800; with NULL a private heap is
      created and destroyed with the list.

    Returns void * - Opaque list handle for all the other list_of_float_double_t_* functions. }}*/
OT4XB_API void* list_of_float_double_t_new( DWORD flags, void* vheap )
{
	list_of_float_double_t * ls = new list_of_float_double_t( ( list_of_float_double_t::vheap_flags ) flags, (OT4XB_VHEAP*) vheap );
	return (void*) ls;
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_destroy
            | syntax_: `void list_of_float_double_t_destroy( void * ls )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_destroy
            | _kw_: double list, statistics, destroy
   }}*/
/*{{|desc: Destroys a list created with list_of_float_double_t_new() and releases its value buffer. A
      private heap owned by the list is destroyed with it.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().

    Returns void }}*/
OT4XB_API void  list_of_float_double_t_destroy( void* ls )
{
	delete static_cast<list_of_float_double_t *>( ls );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_get_last_error
            | syntax_: `DWORD list_of_float_double_t_get_last_error( void * ls )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_get_last_error
            | _kw_: double list, last error, error code
   }}*/
/*{{|desc: Returns the error code set by the last operation on the list.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().

    Returns DWORD - 0 when the last operation succeeded, else a list_of_float_error code declared in
      ot4xb_statistics.h (out of range, empty list, NaN parameter, will produce NaN). }}*/
OT4XB_API DWORD  list_of_float_double_t_get_last_error( void* ls )
{
	return static_cast<DWORD>( static_cast<list_of_float_double_t *>( ls )->m_last_error );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_alloc_bytes
            | syntax_: `void * list_of_float_double_t_alloc_bytes( void * ls, UINT nBytes )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_alloc_bytes
            | _kw_: double list, allocate, list heap
   }}*/
/*{{|desc: Allocates a raw byte block from the same memory source the list uses for its values: the custom
      heap when the list has one, else the Xbase++ runtime memory manager.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `nBytes` UINT - Number of bytes to allocate.

    Returns void * - Pointer to the allocated block; release it with list_of_float_double_t_free_bytes(). }}*/
OT4XB_API void* list_of_float_double_t_alloc_bytes( void* ls, UINT nBytes )
{
	return static_cast<list_of_float_double_t *>( ls )->alloc_bytes( nBytes );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_free_bytes
            | syntax_: `void list_of_float_double_t_free_bytes( void * ls, void * p )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_free_bytes
            | _kw_: double list, free, list heap
   }}*/
/*{{|desc: Releases a byte block allocated with list_of_float_double_t_alloc_bytes() on the same list.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `p` void * - Pointer returned by list_of_float_double_t_alloc_bytes().

    Returns void }}*/
OT4XB_API void  list_of_float_double_t_free_bytes( void* ls, void* p )
{
	static_cast<list_of_float_double_t *>( ls )->free_bytes( p );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_grow
            | syntax_: `void list_of_float_double_t_grow( void * ls, UINT nMin )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_grow
            | _kw_: double list, capacity, grow, reserve
   }}*/
/*{{|desc: Grows the value buffer, rounding up to the next internal capacity step of at least nMin values.
      Stored values and the count are kept; the buffer never shrinks, and every call moves the
      capacity at least one step up, even when nMin is already satisfied.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `nMin` UINT - Minimum capacity, in values, the list must be able to hold.

    Returns void }}*/
OT4XB_API void   list_of_float_double_t_grow( void* ls, UINT nMin )
{
	static_cast<list_of_float_double_t *>( ls )->Grow( nMin );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_add
            | syntax_: `double list_of_float_double_t_add( void * ls, double v )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_add
            | _kw_: double list, append value, push
   }}*/
/*{{|desc: Appends a value at the end of the list, growing the buffer when needed.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `v` double - Value to append. NaN is stored as 0 and sets last error e_nan_parameter.

    Returns double - The value actually stored: v, or 0 when v was NaN. }}*/
OT4XB_API double list_of_float_double_t_add( void* ls, double v )
{
	return static_cast<list_of_float_double_t *>( ls )->Add( v );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_add_list
            | syntax_: `void list_of_float_double_t_add_list( void * ls, double * pv, UINT count )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_add_list
            | _kw_: double list, append values, C array
   }}*/
/*{{|desc: Appends count values taken from a C array of double at the end of the list.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `pv` double * - Source array holding the values to append. NaN entries are stored as 0 and set
      last error e_nan_parameter.
    - `count` UINT - Number of values to append; with 0 or a NULL pv nothing happens.

    Returns void }}*/
OT4XB_API void   list_of_float_double_t_add_list( void* ls, double * pv, UINT count )
{
	static_cast<list_of_float_double_t *>( ls )->Add( pv, count );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_get
            | syntax_: `double list_of_float_double_t_get( void * ls, DWORD n )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_get
            | _kw_: double list, get value, position
   }}*/
/*{{|desc: Returns the value stored at a zero based position of the list.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `n` DWORD - Zero based position of the value.

    Returns double - Stored value, or 0 with last error e_out_of_range when n is past the last value. }}*/
OT4XB_API double list_of_float_double_t_get( void* ls, DWORD n )
{
	return static_cast<list_of_float_double_t *>( ls )->Get( n );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_replace
            | syntax_: `double list_of_float_double_t_replace( void * ls, DWORD n, double v )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_replace
            | _kw_: double list, replace value, position
   }}*/
/*{{|desc: Overwrites the value at a zero based position of the list and returns the value it replaced.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `n` DWORD - Zero based position of the value to overwrite.
    - `v` double - New value. NaN is stored as 0 and sets last error e_nan_parameter.

    Returns double - Previous value at that position, or 0 with last error e_out_of_range when n is past
      the last value. }}*/
OT4XB_API double list_of_float_double_t_replace( void* ls, DWORD n, double v )
{
	return static_cast<list_of_float_double_t *>( ls )->Replace( n, v );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_replace_list
            | syntax_: `void list_of_float_double_t_replace_list( void * ls, DWORD pos, double * pv, UINT count )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_replace_list
            | _kw_: double list, replace values, C array
   }}*/
/*{{|desc: Overwrites count values starting at a zero based position with the values of a C array of
      double. It never extends the list, and it stops at the first failed value: a position past the
      end (last error e_out_of_range) or a NaN entry, stored as 0 (last error e_nan_parameter).
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `pos` DWORD - Zero based position of the first value to overwrite.
    - `pv` double * - Source array holding the new values.
    - `count` UINT - Number of values to overwrite; with 0 or a NULL pv nothing happens.

    Returns void }}*/
OT4XB_API void list_of_float_double_t_replace_list( void* ls, DWORD pos, double * pv, UINT count )
{
	static_cast<list_of_float_double_t *>( ls )->Replace( pos,pv,count  );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_count
            | syntax_: `DWORD list_of_float_double_t_count( void * ls, UINT nSkip, UINT nMax )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_count
            | _kw_: double list, count, range, skip max
   }}*/
/*{{|desc: Returns the number of values in the range of the list selected by nSkip and nMax.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `nSkip` UINT - Number of values to skip from the start of the list.
    - `nMax` UINT - Maximum number of values to count after the skip; (UINT) -1 counts all of them.

    Returns DWORD - Number of values in the range; the total count when nSkip is 0 and nMax is (UINT) -1. }}*/
OT4XB_API DWORD  list_of_float_double_t_count( void* ls, UINT nSkip , UINT nMax )
{
	return static_cast<list_of_float_double_t *>( ls )->Count( nSkip, nMax );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_insert
            | syntax_: `double list_of_float_double_t_insert( void * ls, DWORD pos, double v )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_insert
            | _kw_: double list, insert value, position
   }}*/
/*{{|desc: Inserts a value at a zero based position of the list, shifting the following values one place
      up. With pos (DWORD) -1, or equal to the count, the value is appended at the end.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `pos` DWORD - Zero based position for the new value; greater than the count sets last error
      e_out_of_range.
    - `v` double - Value to insert. NaN is stored as 0 and sets last error e_nan_parameter.

    Returns double - The value actually stored, or 0 when pos is out of range. }}*/
OT4XB_API double list_of_float_double_t_insert( void* ls, DWORD pos, double v )
{
	return static_cast<list_of_float_double_t *>( ls )->Insert( pos, v );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_insert_list
            | syntax_: `void list_of_float_double_t_insert_list( void * ls, DWORD pos, double * pv, UINT count )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_insert_list
            | _kw_: double list, insert values, C array
   }}*/
/*{{|desc: Inserts count values taken from a C array of double at a zero based position of the list,
      shifting the following values count places up. With pos (DWORD) -1, or on an empty list, the
      values are appended at the end and NaN entries become 0 (last error e_nan_parameter); any
      other position copies the values as given, without the NaN check.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `pos` DWORD - Zero based position for the first new value; greater than the count sets last
      error e_out_of_range.
    - `pv` double * - Source array holding the values to insert.
    - `count` UINT - Number of values to insert; with 0 or a NULL pv nothing happens.

    Returns void }}*/
OT4XB_API void   list_of_float_double_t_insert_list( void* ls, DWORD pos, double * pv, UINT count )
{
	static_cast<list_of_float_double_t *>( ls )->Insert( pos, pv, count );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_remove
            | syntax_: `double list_of_float_double_t_remove( void * ls, DWORD n )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_remove
            | _kw_: double list, remove value, position
   }}*/
/*{{|desc: Removes the value at a zero based position of the list, shifting the following values one place
      down, and returns the removed value.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `n` DWORD - Zero based position of the value to remove.

    Returns double - Removed value, or 0 with last error e_out_of_range when n is past the last value. }}*/
OT4XB_API double list_of_float_double_t_remove( void* ls, DWORD n )
{
	return static_cast<list_of_float_double_t *>( ls )->Remove( n );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_pop
            | syntax_: `double list_of_float_double_t_pop( void * ls )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_pop
            | _kw_: double list, pop, last value
   }}*/
/*{{|desc: Removes the last value of the list and returns it.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().

    Returns double - Removed value; NaN on an empty list, which is not flagged as an error. }}*/
OT4XB_API double list_of_float_double_t_pop( void* ls )
{
	return static_cast<list_of_float_double_t *>( ls )->Pop();
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_truncate
            | syntax_: `void list_of_float_double_t_truncate( void * ls, UINT new_count )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_truncate
            | _kw_: double list, truncate, cut, count
   }}*/
/*{{|desc: Cuts the list down to new_count values, discarding the values past that point. It does nothing
      when the list is already that size or shorter, and the allocated capacity is kept.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `new_count` UINT - Number of values to keep.

    Returns void }}*/
OT4XB_API void   list_of_float_double_t_truncate( void* ls, UINT new_count )
{
	static_cast<list_of_float_double_t *>( ls )->Truncate( new_count );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_calculate_sum
            | syntax_: `double list_of_float_double_t_calculate_sum( void * ls, UINT nSkip, UINT nMax )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_calculate_sum
            | _kw_: statistics, sum, total, double list
   }}*/
/*{{|desc: Returns the sum of the range of the list selected by nSkip and nMax.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `nSkip` UINT - Number of values to skip from the start of the list.
    - `nMax` UINT - Maximum number of values to use after the skip; (UINT) -1 uses all of them.

    Returns double - Sum of the selected values, or 0 with last error e_empty_list on an empty range. }}*/
OT4XB_API double list_of_float_double_t_calculate_sum( void* ls, UINT nSkip, UINT nMax )
{
	return static_cast<list_of_float_double_t *>( ls )->CalculateSum( nSkip, nMax );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_calculate_mean
            | syntax_: `double list_of_float_double_t_calculate_mean( void * ls, UINT nSkip, UINT nMax )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_calculate_mean
            | _kw_: statistics, mean, average, double list
   }}*/
/*{{|desc: Returns the arithmetic mean of the range of the list selected by nSkip and nMax.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `nSkip` UINT - Number of values to skip from the start of the list.
    - `nMax` UINT - Maximum number of values to use after the skip; (UINT) -1 uses all of them.

    Returns double - Mean of the selected values, or 0 with last error e_empty_list on an empty range. }}*/
OT4XB_API double list_of_float_double_t_calculate_mean( void* ls, UINT nSkip , UINT nMax )
{
	return static_cast<list_of_float_double_t *>( ls )->CalculateMean( nSkip, nMax );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_calculate_population_variance
            | syntax_: `double list_of_float_double_t_calculate_population_variance( void * ls, UINT nSkip, UINT nMax )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_calculate_population_variance
            | _kw_: statistics, variance, population, double list
   }}*/
/*{{|desc: Returns the population variance (divisor N) of the range of the list selected by nSkip and nMax.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `nSkip` UINT - Number of values to skip from the start of the list.
    - `nMax` UINT - Maximum number of values to use after the skip; (UINT) -1 uses all of them.

    Returns double - Population variance, or 0 with last error e_empty_list on an empty range. }}*/
OT4XB_API double list_of_float_double_t_calculate_population_variance( void* ls, UINT nSkip, UINT nMax  )
{
	return static_cast<list_of_float_double_t *>( ls )->CalculatePopulationVariance( nSkip, nMax );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_calculate_sample_variance
            | syntax_: `double list_of_float_double_t_calculate_sample_variance( void * ls, UINT nSkip, UINT nMax )`
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_calculate_sample_variance
            | _kw_: statistics, variance, sample, N-1, double list
   }}*/
/*{{|desc: Returns the sample variance (divisor N - 1) of the range of the list selected by nSkip and nMax.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `nSkip` UINT - Number of values to skip from the start of the list.
    - `nMax` UINT - Maximum number of values to use after the skip; (UINT) -1 uses all of them.

    Returns double - Sample variance, or 0 with last error e_empty_list on an empty range or
      e_will_produce_nan when the range holds a single value. }}*/
OT4XB_API double list_of_float_double_t_calculate_sample_variance( void* ls, UINT nSkip , UINT nMax )
{
	return static_cast<list_of_float_double_t *>( ls )->CalculateSampleVariance( nSkip, nMax );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_calculate_population_standard_deviation
            | syntax_: ```
                 double list_of_float_double_t_calculate_population_standard_deviation( void * ls, UINT nSkip, UINT nMax )
              ```
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_calculate_population_standard_deviation
            | _kw_: statistics, standard deviation, population, stddev
   }}*/
/*{{|desc: Returns the population standard deviation of the range of the list selected by nSkip and nMax.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `nSkip` UINT - Number of values to skip from the start of the list.
    - `nMax` UINT - Maximum number of values to use after the skip; (UINT) -1 uses all of them.

    Returns double - Population standard deviation, or 0 with last error e_empty_list on an empty range. }}*/
OT4XB_API double list_of_float_double_t_calculate_population_standard_deviation( void* ls, UINT nSkip , UINT nMax )
{
	return static_cast<list_of_float_double_t *>( ls )->CalculatePopulationStandardDeviation( nSkip, nMax );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: list_of_float_double_t_calculate_sample_standard_deviation
            | syntax_: ```
                 double list_of_float_double_t_calculate_sample_standard_deviation( void * ls, UINT nSkip, UINT nMax )
              ```
            | category: statistics
            | header: ot4xb_statistics.h
            | mangled-name: list_of_float_double_t_calculate_sample_standard_deviation
            | _kw_: statistics, standard deviation, sample, stddev, N-1
   }}*/
/*{{|desc: Returns the sample standard deviation of the range of the list selected by nSkip and nMax.
    | params:
    - `ls` void * - List handle returned by list_of_float_double_t_new().
    - `nSkip` UINT - Number of values to skip from the start of the list.
    - `nMax` UINT - Maximum number of values to use after the skip; (UINT) -1 uses all of them.

    Returns double - Sample standard deviation, or 0 with last error e_empty_list on an empty range or
      e_will_produce_nan when the range holds a single value. }}*/
OT4XB_API double list_of_float_double_t_calculate_sample_standard_deviation( void* ls, UINT nSkip, UINT nMax )
{
	return static_cast<list_of_float_double_t *>( ls )->CalculateSampleStandardDeviation( nSkip, nMax );
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------
