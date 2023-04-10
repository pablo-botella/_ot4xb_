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
	else if ( nCapacity < 4096 ) { nCapacity = 65536; }
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
		for ( n = pos; n < m_nCount; n++ )
		{
			m_pValues[n+m_nCount] = m_pValues[n];
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
	for ( n = 0 ; n < count; n++ )
	{
      result += m_pValues[n];
	}
	return result / ((double) count );
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
		result += m_pValues[n];
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
OT4XB_API void* list_of_float_double_t_new( DWORD flags, void* vheap )
{
	list_of_float_double_t * ls = new list_of_float_double_t( ( list_of_float_double_t::vheap_flags ) flags, (OT4XB_VHEAP*) vheap );
	return (void*) ls;
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API void  list_of_float_double_t_destroy( void* ls )
{
	delete static_cast<list_of_float_double_t *>( ls );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD  list_of_float_double_t_get_last_error( void* ls )
{
	return static_cast<DWORD>( static_cast<list_of_float_double_t *>( ls )->m_last_error );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API void* list_of_float_double_t_alloc_bytes( void* ls, UINT nBytes )
{
	return static_cast<list_of_float_double_t *>( ls )->alloc_bytes( nBytes );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API void  list_of_float_double_t_free_bytes( void* ls, void* p )
{
	static_cast<list_of_float_double_t *>( ls )->free_bytes( p );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API void   list_of_float_double_t_grow( void* ls, UINT nMin )
{
	static_cast<list_of_float_double_t *>( ls )->Grow( nMin );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_add( void* ls, double v )
{
	return static_cast<list_of_float_double_t *>( ls )->Add( v );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API void   list_of_float_double_t_add_list( void* ls, double * pv, UINT count )
{
	static_cast<list_of_float_double_t *>( ls )->Add( pv, count );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_get( void* ls, DWORD n )
{
	return static_cast<list_of_float_double_t *>( ls )->Get( n );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_replace( void* ls, DWORD n, double v )
{
	return static_cast<list_of_float_double_t *>( ls )->Replace( n, v );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API void list_of_float_double_t_replace_list( void* ls, DWORD pos, double * pv, UINT count )
{
	static_cast<list_of_float_double_t *>( ls )->Replace( pos,pv,count  );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD  list_of_float_double_t_count( void* ls, UINT nSkip , UINT nMax )
{
	return static_cast<list_of_float_double_t *>( ls )->Count( nSkip, nMax );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_insert( void* ls, DWORD pos, double v )
{
	return static_cast<list_of_float_double_t *>( ls )->Insert( pos, v );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API void   list_of_float_double_t_insert_list( void* ls, DWORD pos, double * pv, UINT count )
{
	static_cast<list_of_float_double_t *>( ls )->Insert( pos, pv, count );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_remove( void* ls, DWORD n )
{
	return static_cast<list_of_float_double_t *>( ls )->Remove( n );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_pop( void* ls )
{
	return static_cast<list_of_float_double_t *>( ls )->Pop();
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API void   list_of_float_double_t_truncate( void* ls, UINT new_count )
{
	static_cast<list_of_float_double_t *>( ls )->Truncate( new_count );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_calculate_sum( void* ls, UINT nSkip, UINT nMax )
{
	return static_cast<list_of_float_double_t *>( ls )->CalculateSum( nSkip, nMax );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_calculate_mean( void* ls, UINT nSkip , UINT nMax )
{
	return static_cast<list_of_float_double_t *>( ls )->CalculateMean( nSkip, nMax );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_calculate_population_variance( void* ls, UINT nSkip, UINT nMax  )
{
	return static_cast<list_of_float_double_t *>( ls )->CalculatePopulationVariance( nSkip, nMax );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_calculate_sample_variance( void* ls, UINT nSkip , UINT nMax )
{
	return static_cast<list_of_float_double_t *>( ls )->CalculateSampleVariance( nSkip, nMax );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_calculate_population_standard_deviation( void* ls, UINT nSkip , UINT nMax )
{
	return static_cast<list_of_float_double_t *>( ls )->CalculatePopulationStandardDeviation( nSkip, nMax );
}
// ---------------------------------------------------------------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_calculate_sample_standard_deviation( void* ls, UINT nSkip, UINT nMax )
{
	return static_cast<list_of_float_double_t *>( ls )->CalculateSampleStandardDeviation( nSkip, nMax );
}
// ---------------------------------------------------------------------------------------------------------------------------------
