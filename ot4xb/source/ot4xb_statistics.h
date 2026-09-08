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
/*{{begin-cpp-class}}*/
/*{{cpp-class_: list_of_float_double_t
   | parent: {{ilink: <cpp-class T_ot4xb_base_with_vheap> T_ot4xb_base_with_vheap}}
   | category: c-api/classes , statistics
   | desc: A growable array of doubles with the basic statistics over it or over a slice of it: sum, mean,
     population and sample variance and standard deviation. NaN never gets in (a NaN parameter is stored
     as 0 and reported) and every operation leaves its outcome in **m_last_error**. The C API of the same
     object is the `list_of_float_double_t_*` family
     ({{ilink: <c-function list_of_float_double_t_new> list_of_float_double_t_new}}, ...).
     | _kw_: list_of_float_double_t, Class }}*/
class OT4XB_API list_of_float_double_t : public T_ot4xb_base_with_vheap
{
	public:
	/*{{|member_: `UINT m_nCapacity` | desc_: Values allocated (16, 256, 1024, 4096, 65536, then 65536
	   more each time). }}*/
	UINT          m_nCapacity;
	/*{{|member_: `UINT m_nCount` | desc_: Values stored. }}*/
	UINT          m_nCount;
	/*{{|member_: `double* m_pValues` | desc_: The values, from the heap the flags selected. }}*/
	double*       m_pValues;
	/*{{|member_: `enum list_of_float_error m_last_error` | desc_: Outcome of the last operation:
	   `e_no_error`, `e_empty_list` (a calculation over no values), `e_out_of_range` (a position past the
	   values), `e_nan_parameter` (a NaN was given and stored as 0), `e_will_produce_nan` (a sample
	   statistic over one value); `e_not_found`, `e_eof`, `e_bof` and `e_nan_found` are reserved. Codes with
	   the high bit set are errors, the others conditions. }}*/
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
	/*{{|method_: `list_of_float_double_t( vheap_flags dw = e_zero, OT4XB_VHEAP* vheap = 0 )` | desc_: An
	   empty list whose memory comes from the heap the flags select (see the parent class). }}*/
	list_of_float_double_t( vheap_flags dw = e_zero, OT4XB_VHEAP* vheap = 0 );
	/*{{|method_: `~list_of_float_double_t( void )` | desc_: Frees the values and, when owned, the heap. }}*/
	~list_of_float_double_t( void );
	// ---------------------------------------------------------------------------------
	/*{{|method_: `void Grow( UINT nMin = 0 )` | desc_: Makes room for at least **nMin** values, in the steps
	   of m_nCapacity. }}*/
	void   Grow( UINT nMin = 0);
	/*{{|method_: `double Add( double v )` | desc_: Appends **v** and returns it (0, with e_nan_parameter, for
	   a NaN). }}*/
	double Add( double v);
	/*{{|method_: `void Add( double* pv, UINT count )` | desc_: Appends **count** values. }}*/
	void   Add( double * pv , UINT count );
	/*{{|method_: `double Get( UINT pos )` | desc_: The value at the zero-based position; 0 and
	   e_out_of_range past the end. }}*/
	double Get( UINT pos);
	/*{{|method_: `double Replace( UINT pos, double v )` | desc_: Stores **v** at the position and returns the
	   previous value; 0 and e_out_of_range past the end. }}*/
	double Replace( UINT pos, double v );
	/*{{|method_: `void Replace( UINT pos, double* pv, UINT count )` | desc_: Replaces **count** values from
	   the position, stopping at the first error. }}*/
	void Replace( UINT pos, double * pv, UINT count );
	/*{{|method_: `UINT Count( UINT nSkip = 0, UINT nMax = -1 )` | desc_: Values in the slice that skips
	   **nSkip** and takes at most **nMax**: the whole list by default. }}*/
	UINT   Count( UINT nSkip = 0 , UINT nMax = -1);
	/*{{|method_: `double Insert( UINT pos, double v )` | desc_: Inserts **v** at the position, shifting the
	   rest up (the count or (UINT) -1 append); returns v, or 0 with e_out_of_range beyond the count. }}*/
	double Insert( UINT pos, double v );
	/*{{|method_: `void Insert( UINT pos, double* pv, UINT count )` | desc_: Inserts **count** values at the
	   position. }}*/
	void   Insert( UINT pos, double * pv , UINT count );
	/*{{|method_: `double Remove( UINT pos )` | desc_: Removes the value at the position, shifting the rest
	   down, and returns it; 0 with e_out_of_range past the end. }}*/
	double Remove( UINT );
	/*{{|method_: `double Pop( void )` | desc_: Removes and returns the last value; NaN when empty. }}*/
	double Pop( void );
	/*{{|method_: `double Tail( void )` | desc_: The last value, left in place; NaN when empty. }}*/
	double Tail( void );
	/*{{|method_: `void Truncate( UINT new_count = 0 )` | desc_: Cuts the list to **new_count** values. }}*/
	void   Truncate( UINT new_count = 0 );
	// ---------------------------------------------------------------------------------
	/*{{|method_: `double CalculateSum( UINT nSkip = 0, UINT nMax = (UINT) -1 )` | desc_: Sum of the slice
	   (skip **nSkip** values, take at most **nMax**); 0 and e_empty_list when the slice is empty. }}*/
	double CalculateSum( UINT nSkip = 0, UINT nMax = (UINT) -1 );
	/*{{|method_: `double CalculateMean( UINT nSkip = 0, UINT nMax = (UINT) -1 )` | desc_: Arithmetic mean of
	   the slice; 0 and e_empty_list when empty. }}*/
	double CalculateMean( UINT nSkip = 0, UINT nMax = (UINT) -1 );
	/*{{|method_: `double CalculatePopulationVariance( UINT nSkip = 0, UINT nMax = (UINT) -1 )` | desc_:
	   Variance of the slice taken as the whole population (divided by n). }}*/
	double CalculatePopulationVariance( UINT nSkip = 0, UINT nMax = (UINT) -1 );
	/*{{|method_: `double CalculateSampleVariance( UINT nSkip = 0, UINT nMax = (UINT) -1 )` | desc_: Variance
	   of the slice taken as a sample (divided by n - 1); 0 and e_will_produce_nan for a single value. }}*/
	double CalculateSampleVariance( UINT nSkip = 0, UINT nMax = (UINT) -1 );
	/*{{|method_: `double CalculatePopulationStandardDeviation( UINT nSkip = 0, UINT nMax = (UINT) -1 )`
	   | desc_: Square root of the population variance; 0 when that one reported an error. }}*/
	double CalculatePopulationStandardDeviation( UINT nSkip = 0, UINT nMax = (UINT) -1 );
	/*{{|method_: `double CalculateSampleStandardDeviation( UINT nSkip = 0, UINT nMax = (UINT) -1 )`
	   | desc_: Square root of the sample variance; 0 when that one reported an error. }}*/
	double CalculateSampleStandardDeviation( UINT nSkip = 0, UINT nMax = (UINT) -1 );
};
/*{{end-cpp-class}}*/
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

