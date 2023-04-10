//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#pragma once
#pragma pack(push , 4)
#ifdef __cplusplus
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API list_of_float_double_t : public T_ot4xb_base_with_vheap
{
	public:
	UINT          m_nCapacity;
	UINT          m_nCount;
	double*       m_pValues;
	enum list_of_float_error
	{
		e_no_error         = 0x00000000,
		e_not_found        = 0x00000001,
		e_empty_list       = 0x00000002,
		e_eof              = 0x00000004,
		e_bof              = 0x00000008,
		e_out_of_range     = 0x80000010,
		e_nan_found        = 0x80000012,
		e_nan_parameter    = 0x80000014,
		e_will_produce_nan = 0x80000018

	} m_last_error;
	// ---------------------------------------------------------------------------------
	list_of_float_double_t( vheap_flags dw = e_zero, OT4XB_VHEAP* vheap = 0 );
	~list_of_float_double_t( void );
	// ---------------------------------------------------------------------------------
	void   Grow( UINT nMin = 0);
	double Add( double v);
	void   Add( double * pv , UINT count );
	double Get( UINT pos);
	double Replace( UINT pos, double v );
	void Replace( UINT pos, double * pv, UINT count );
	UINT   Count( UINT nSkip = 0 , UINT nMax = -1);
	double Insert( UINT pos, double v );
	void   Insert( UINT pos, double * pv , UINT count );
	double Remove( UINT );
	double Pop( void );
	double Tail( void );
	void   Truncate( UINT new_count = 0 ); 
	// ---------------------------------------------------------------------------------
	double CalculateSum( UINT nSkip = 0, UINT nMax = (UINT) -1 );
	double CalculateMean( UINT nSkip = 0, UINT nMax = (UINT) -1 );
	double CalculatePopulationVariance( UINT nSkip = 0, UINT nMax = (UINT) -1 );
	double CalculateSampleVariance( UINT nSkip = 0, UINT nMax = (UINT) -1 );
	double CalculatePopulationStandardDeviation( UINT nSkip = 0, UINT nMax = (UINT) -1 );
	double CalculateSampleStandardDeviation( UINT nSkip = 0, UINT nMax = (UINT) -1 );
};
// -----------------------------------------------------------------------------------------------------------------
BEGIN_EXTERN_C
// --------------------------------------------------------------------------
OT4XB_API void* list_of_float_double_t_new( DWORD flags = 0, void* vheap = 0);
OT4XB_API void  list_of_float_double_t_destroy( void* ls );
// --------------------------------------------------------------------------
OT4XB_API DWORD list_of_float_double_t_get_last_error( void* ls );
// --------------------------------------------------------------------------
OT4XB_API void* list_of_float_double_t_alloc_bytes( void* ls, UINT nBytes );
OT4XB_API void  list_of_float_double_t_free_bytes( void* ls, void* p );
// -----------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------
OT4XB_API void   list_of_float_double_t_grow( void* ls , UINT nMin);
OT4XB_API double list_of_float_double_t_add( void* ls, double v);
OT4XB_API void   list_of_float_double_t_add_list( void* ls, double * pv , UINT count);
OT4XB_API double list_of_float_double_t_get( void* ls, DWORD n );
OT4XB_API double list_of_float_double_t_replace( void* ls, DWORD n, double v );
OT4XB_API void   list_of_float_double_t_replace_list( void* ls, DWORD pos, double * pv, UINT count );
OT4XB_API DWORD  list_of_float_double_t_count( void* ls , UINT nSkip = 0, UINT nMax = (UINT) -1 );
OT4XB_API double list_of_float_double_t_insert( void* ls, DWORD pos, double v );
OT4XB_API void   list_of_float_double_t_insert_list( void* ls, DWORD pos , double * pv, UINT count );
OT4XB_API double list_of_float_double_t_remove( void* ls, DWORD n );
OT4XB_API double list_of_float_double_t_pop( void* ls );
OT4XB_API void   list_of_float_double_t_truncate( void* ls, UINT new_count );
// ---------------------------------------------------------------------------
OT4XB_API double list_of_float_double_t_calculate_sum( void* ls, UINT nSkip = 0, UINT nMax = (UINT) -1 );
OT4XB_API double list_of_float_double_t_calculate_mean( void* ls, UINT nSkip = 0, UINT nMax = (UINT) -1 );
OT4XB_API double list_of_float_double_t_calculate_population_variance( void* ls, UINT nSkip = 0, UINT nMax = (UINT) -1 );
OT4XB_API double list_of_float_double_t_calculate_sample_variance( void* ls, UINT nSkip = 0, UINT nMax = (UINT) -1 );
OT4XB_API double list_of_float_double_t_calculate_population_standard_deviation( void* ls, UINT nSkip = 0, UINT nMax = (UINT) -1 );
OT4XB_API double list_of_float_double_t_calculate_sample_standard_deviation( void* ls, UINT nSkip = 0, UINT nMax = (UINT) -1 );
// ---------------------------------------------------------------------------
END_EXTERN_C
// -----------------------------------------------------------------------------------------------------------------
#endif
#pragma pack(pop)

