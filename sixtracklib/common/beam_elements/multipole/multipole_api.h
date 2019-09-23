#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_API_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_API_C99_H__


#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/definitions.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #if !defined( _GPUCODE )
        #include "sixtracklib/common/buffer.h"
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __cplusplus )
extern "C" {
#endif /* !defined( __cplusplus )  */

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Multipole_get_num_dataptrs)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Multipole_get_num_slots)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const slot_size );

SIXTRL_FN SIXTRL_STATIC SIXTRL_BE_ARGPTR_DEC NS(Multipole)* NS(Multipole_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC NS(multipole_real_t) NS(Multipole_get_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC NS(multipole_real_t) NS(Multipole_get_hxl)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC NS(multipole_real_t) NS(Multipole_get_hyl)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC NS(multipole_order_t) NS(Multipole_get_order)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Multipole_get_bal_size)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t) const*
NS(Multipole_get_const_bal)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t)*
NS(Multipole_get_bal)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC NS(multipole_real_t) NS(Multipole_get_bal_value)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const index );

SIXTRL_FN SIXTRL_STATIC NS(multipole_real_t) NS(Multipole_get_knl_value)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const index );

SIXTRL_FN SIXTRL_STATIC NS(multipole_real_t) NS(Multipole_get_ksl_value)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const index );

SIXTRL_FN SIXTRL_STATIC void NS(Multipole_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(multipole_real_t) const length );

SIXTRL_FN SIXTRL_STATIC void NS(Multipole_set_hxl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(multipole_real_t) const length );

SIXTRL_FN SIXTRL_STATIC void NS(Multipole_set_hyl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(multipole_real_t) const length );

SIXTRL_FN SIXTRL_STATIC void NS(Multipole_set_order)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(multipole_order_t) const order );

SIXTRL_FN SIXTRL_STATIC void NS(Multipole_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC void NS(Multipole_set_bal)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    SIXTRL_BE_ARGPTR_DEC NS(multipole_real_t) const* SIXTRL_RESTRICT bal );

SIXTRL_FN SIXTRL_STATIC void NS(Multipole_set_knl)(
    SIXTRL_BE_DATAPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t) const* SIXTRL_RESTRICT knl );

SIXTRL_FN SIXTRL_STATIC void NS(Multipole_set_ksl)(
    SIXTRL_BE_DATAPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t) const* SIXTRL_RESTRICT ksl );

SIXTRL_FN SIXTRL_STATIC void NS(Multipole_assign_bal)(
    SIXTRL_BE_DATAPTR_DEC  NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(multipole_order_t) const order,
    SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t)* SIXTRL_RESTRICT bal );

SIXTRL_FN SIXTRL_STATIC void NS(Multipole_set_bal_value)(
    SIXTRL_BE_DATAPTR_DEC  NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const index, NS(multipole_real_t) const bal );

SIXTRL_FN SIXTRL_STATIC void NS(Multipole_set_knl_value)(
    SIXTRL_BE_DATAPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const index,
    NS(multipole_real_t) const knl_i );

SIXTRL_FN SIXTRL_STATIC void NS(Multipole_set_ksl_value)(
    SIXTRL_BE_DATAPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const index,
    NS(multipole_real_t) const ksl_i );

SIXTRL_FN SIXTRL_STATIC int NS(Multipole_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT src );

SIXTRL_FN SIXTRL_STATIC int NS(Multipole_compare_values)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs );

SIXTRL_FN SIXTRL_STATIC int NS(Multipole_compare_values_with_treshold)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs,
    NS(multipole_real_t) const treshold );

#if !defined( _GPUCODE )

SIXTRL_FN SIXTRL_STATIC bool NS(Multipole_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(multipole_order_t) const order,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_dataptrs );

SIXTRL_FN SIXTRL_STATIC SIXTRL_BUFFER_DATAPTR_DEC NS(Multipole)*
NS(Multipole_new)( SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(multipole_order_t) const order );

SIXTRL_FN SIXTRL_STATIC SIXTRL_BUFFER_DATAPTR_DEC NS(Multipole)*
NS(Multipole_add)( SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(multipole_order_t) const order,
    SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t) const* SIXTRL_RESTRICT bal,
    NS(multipole_real_t)  const length,
    NS(multipole_real_t)  const hxl,
    NS(multipole_real_t)  const hyl );

SIXTRL_FN SIXTRL_STATIC SIXTRL_BUFFER_DATAPTR_DEC NS(Multipole)*
NS(Multipole_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole );

#endif /* !defined( _GPUCODE ) */

/* ========================================================================= */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* */
/* *****          Implementation of C inline functions                   *** */
/* ************************************************************************* */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(buffer_size_t) NS(Multipole_get_num_dataptrs)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole )
{
    typedef NS(multipole_order_t)   mp_order_t;
    typedef NS(buffer_size_t)       buf_size_t;

    return ( ( multipole != SIXTRL_NULLPTR ) &&
             ( multipole->order >= ( mp_order_t )0 ) )
        ? ( buf_size_t )1u : ( buf_size_t )0u;
}

SIXTRL_INLINE NS(buffer_size_t) NS(Multipole_get_num_slots)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(buffer_size_t) const slot_size )
{
    typedef NS(buffer_size_t) buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;

    buf_size_t requ_num_slots =  NS(ManagedBuffer_get_slot_based_length)(
            sizeof( NS(Multipole) ), slot_size );

    if( ( requ_num_slots > ZERO ) && ( slot_size > ZERO ) )
    {
        buf_size_t const bal_size = NS(Multipole_get_bal_size)( mp );

        SIXTRL_ASSERT(
            ( NS(Multipole_get_num_dataptrs)( mp ) == ( buf_size_t )1u ) ||
            ( ( NS(Multipole_get_num_dataptrs)( mp ) == ZERO ) &&
              ( NS(Multipole_get_order)( mp ) <
              ( NS(multipole_order_t) )0u ) ) );

        SIXTRL_ASSERT( ( requ_num_slots % slot_size ) == ZERO );
        SIXTRL_ASSERT( ( bal_size % 2u ) == ZERO );

        if( bal_size > ZERO )
        {
            requ_num_slots += NS(ManagedBuffer_get_slot_based_length)(
                bal_size * sizeof( SIXTRL_REAL_T ), slot_size );
        }

        SIXTRL_ASSERT( ZERO == ( requ_num_slots % slot_size ) );
        SIXTRL_ASSERT( requ_num_slots >= slot_size );

        requ_num_slots /= slot_size;
    }

    return requ_num_slots;
}

SIXTRL_INLINE int NS(Multipole_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT src )
{
    int success = -1;

    NS(multipole_order_t) const order = NS(Multipole_get_order)( src );

    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) &&
        ( NS(Multipole_get_order)( dest ) == order ) )
    {
        NS(Multipole_set_length)( dest, NS(Multipole_get_length)( src ) );
        NS(Multipole_set_hxl)( dest, NS(Multipole_get_hxl)( src ) );
        NS(Multipole_set_hyl)( dest, NS(Multipole_get_hyl)( src ) );

        if( order >= ( NS(multipole_order_t) )0u )
        {
            SIXTRL_ASSERT( NS(Multipole_get_bal)( dest )     != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( NS(Multipole_get_const_bal)( src) != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( NS(Multipole_get_bal_size)( dest ) ==
                           NS(Multipole_get_bal_size)( src  ) );

            SIXTRACKLIB_COPY_VALUES( SIXTRL_REAL_T,
                 NS(Multipole_get_bal)( dest ),
                 NS(Multipole_get_const_bal)( src ),
                 NS(Multipole_get_bal_size)( src ) );
        }

        success = 0;
    }

    return success;
}


SIXTRL_FN SIXTRL_STATIC NS(multipole_order_t) NS(_calculate_factorial)(
    NS(multipole_order_t) const n )
{
    NS(multipole_order_t) result = 1;
    NS(multipole_order_t) ii     = 1;

    for( ; ii <= n ; ++ii )
    {
        result *= ii;
    }

    return result;
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole)* NS(Multipole_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole )
{
    typedef NS(multipole_order_t) mp_order_t;
    SIXTRL_STATIC_VAR mp_order_t DEFAULT_ORDER = ( mp_order_t )-1;

    NS(Multipole_assign_bal)( multipole, DEFAULT_ORDER, SIXTRL_NULLPTR );
    NS(Multipole_clear)( multipole );

    return multipole;
}

SIXTRL_INLINE NS(multipole_real_t) NS(Multipole_get_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole )
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    return multipole->length;
}

SIXTRL_INLINE NS(multipole_real_t) NS(Multipole_get_hxl)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole )
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    return multipole->hxl;
}

SIXTRL_INLINE NS(multipole_real_t) NS(Multipole_get_hyl)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole )
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    return multipole->hyl;
}

SIXTRL_INLINE NS(multipole_order_t) NS(Multipole_get_order)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole )
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    return multipole->order;
}

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t) const*
NS(Multipole_get_const_bal)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole )
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );

    SIXTRL_ASSERT(
        ( ( NS(Multipole_get_order)( multipole ) >= 0 ) &&
            ( multipole->bal_addr != 0u ) ) ||
          ( ( NS(Multipole_get_order)( multipole ) < 0 ) &&
            ( multipole->bal_addr == 0u ) ) );

    return multipole->bal;
}

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t)* NS(Multipole_get_bal)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole )
{
    typedef SIXTRL_BE_DATAPTR_DEC  NS(multipole_real_t)* ptr_ptr_bal_t;
    return ( ptr_ptr_bal_t )NS(Multipole_get_const_bal)( multipole );
}

SIXTRL_INLINE NS(multipole_real_t) NS(Multipole_get_bal_value)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const index )
{
    typedef SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t) const* ptr_to_bal_t;

    ptr_to_bal_t bal = NS(Multipole_get_const_bal)( multipole );

    SIXTRL_ASSERT( bal != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( index < NS(Multipole_get_bal_size)( multipole ) );

    return bal[ index ];
}

SIXTRL_INLINE NS(buffer_size_t) NS(Multipole_get_bal_size)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole )
{
    return ( multipole != SIXTRL_NULLPTR )
        ?  ( ( multipole->order >= ( NS(multipole_order_t ) )0 )
                ? ( ( NS(buffer_size_t) )( 2 * multipole->order + 2 ) )
                : ( ( NS(buffer_size_t) )0u ) )
        :  ( ( NS(buffer_size_t) )0u );
}


SIXTRL_INLINE NS(multipole_real_t) NS(Multipole_get_knl_value)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const index )
{
    typedef NS(buffer_size_t) buf_size_t;
    buf_size_t const bal_index = ( buf_size_t )2u * index;

    return NS(Multipole_get_bal_value)( multipole, bal_index ) *
           NS(_calculate_factorial)( index );
}

SIXTRL_INLINE NS(multipole_real_t) NS(Multipole_get_ksl_value)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const index )
{
    typedef NS(buffer_size_t) buf_size_t;
    buf_size_t const bal_index = ( buf_size_t )2u * index + ( buf_size_t )1u;

    return NS(Multipole_get_bal_value)( multipole, bal_index ) *
           NS(_calculate_factorial)( index );
}

SIXTRL_INLINE void NS(Multipole_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(multipole_real_t) const length )
{
    if( multipole != SIXTRL_NULLPTR ) multipole->length = length;
    return;
}

SIXTRL_INLINE void NS(Multipole_set_hxl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(multipole_real_t) const hxl )
{
    if( multipole != SIXTRL_NULLPTR ) multipole->hxl = hxl;
    return;
}

SIXTRL_INLINE void NS(Multipole_set_hyl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(multipole_real_t) const hyl )
{
    if( multipole != SIXTRL_NULLPTR ) multipole->hyl = hyl;
    return;
}

SIXTRL_INLINE void NS(Multipole_set_order)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(multipole_order_t) const order )
{
    #if !defined( NDEBUG ) && !defined( _GPUCODE )
    SIXTRL_STATIC_VAR NS(multipole_order_t) const
        INV_ORDER = ( NS(multipole_order_t) )-1;

    SIXTRL_ASSERT( order >= INV_ORDER );
    #endif /* !defined( NDEBUG ) && !defined( _GPUCODE ) */

    if( multipole != SIXTRL_NULLPTR ) multipole->order = order;
    return;
}

SIXTRL_INLINE void NS(Multipole_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole )
{
    typedef NS(buffer_size_t)    buf_size_t;
    typedef NS(multipole_real_t) mp_real_t;

    buf_size_t const bal_size = NS(Multipole_get_bal_size)( multipole );

    NS(Multipole_set_length)( multipole, ( mp_real_t )0 );
    NS(Multipole_set_hxl)( multipole,    ( mp_real_t )0 );
    NS(Multipole_set_hyl)( multipole,    ( mp_real_t )0 );

    if( bal_size > ( buf_size_t )0 )
    {
        SIXTRL_STATIC_VAR mp_real_t const ZERO = ( mp_real_t )0;

        SIXTRL_BE_DATAPTR_DEC mp_real_t* bal_begin =
            NS(Multipole_get_bal)( multipole );

        SIXTRACKLIB_SET_VALUES( mp_real_t, bal_begin, bal_size, ZERO );
    }

    return;
}

SIXTRL_INLINE void NS(Multipole_set_bal)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    SIXTRL_BE_ARGPTR_DEC NS(multipole_real_t) const* SIXTRL_RESTRICT bal )
{
    NS(buffer_size_t) const bal_size = NS(Multipole_get_bal_size)( multipole );

    SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t)* dest =
        NS(Multipole_get_bal)( multipole );

    SIXTRACKLIB_COPY_VALUES( NS(multipole_real_t), dest, bal, bal_size );

    return;
}

SIXTRL_INLINE void NS(Multipole_set_knl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    SIXTRL_BE_ARGPTR_DEC NS(multipole_real_t) const* SIXTRL_RESTRICT knl )
{
    NS(multipole_order_t) const order = NS(Multipole_get_order)( multipole );

    SIXTRL_BE_ARGPTR_DEC NS(multipole_real_t)* bal =
        NS(Multipole_get_bal)( multipole );

    if( ( order >= 0 ) &&
        ( bal != SIXTRL_NULLPTR ) &&
        ( knl != SIXTRL_NULLPTR ) )
    {
        bal[ 0 ] = knl[ 0 ];

        if( order > 0 )
        {
            NS(multipole_order_t)    ii = 1;
            NS(buffer_size_t) jj = ( NS(buffer_size_t) )2u;
            NS(multipole_real_t)   fact = ( NS(multipole_real_t) )1;

            for( ; ii <= order ; jj += 2u,
                    fact *= ( NS(multipole_real_t) )ii++ )
            {
                SIXTRL_ASSERT( fact > ( NS(multipole_real_t) )0 );
                bal[ jj ] = knl[ ii ] / fact;
            }
        }
    }

    return;
}

SIXTRL_INLINE void NS(Multipole_set_ksl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    SIXTRL_BE_ARGPTR_DEC NS(multipole_real_t) const* SIXTRL_RESTRICT ksl )
{
    NS(multipole_order_t) const order = NS(Multipole_get_order)( multipole );

    SIXTRL_BE_ARGPTR_DEC NS(multipole_real_t)* bal =
        NS(Multipole_get_bal)( multipole );

    if( ( order >= 0 ) &&
        ( bal != SIXTRL_NULLPTR ) && ( ksl != SIXTRL_NULLPTR ) )
    {
        bal[ 1 ] = ksl[ 0 ];

        if( order > 0 )
        {
            NS(multipole_order_t)    ii = 1;
            NS(buffer_size_t) jj = ( NS(buffer_size_t) )3u;
            NS(multipole_real_t)   fact = ( NS(multipole_real_t) )1;

            for( ; ii <= order ; jj += 2u,
                    fact *= ( NS(multipole_real_t) )ii++ )
            {
                SIXTRL_ASSERT( fact > ( NS(multipole_real_t) )0 );
                bal[ jj ] = ksl[ ii ] / fact;
            }
        }
    }

    return;
}

SIXTRL_INLINE void NS(Multipole_assign_bal)(
    SIXTRL_BE_ARGPTR_DEC  NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(multipole_order_t) const order,
    SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t)* SIXTRL_RESTRICT bal_ptr )
{
    typedef NS(multipole_order_t) mp_order_t;
    SIXTRL_STATIC_VAR mp_order_t const ZERO_ORDER = ( mp_order_t )0;

    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );

    if( ( multipole != SIXTRL_NULLPTR ) &&
        ( ( ( order <  ZERO_ORDER ) && ( bal_ptr == SIXTRL_NULLPTR ) ) ||
          ( ( order >= ZERO_ORDER ) && ( bal_ptr != SIXTRL_NULLPTR ) ) ) )
    {
        multipole->order = order;
        multipole->bal_addr = ( uintptr_t )bal_ptr;
    }

    return;
}

SIXTRL_INLINE void NS(Multipole_set_bal_value)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const index, NS(multipole_real_t) const bal_value )
{
    typedef NS(multipole_real_t)                mp_real_t;
    typedef NS(buffer_size_t)                   buf_size_t;
    typedef SIXTRL_BE_DATAPTR_DEC mp_real_t*    ptr_to_bal_t;

    ptr_to_bal_t bal          = NS(Multipole_get_bal)( multipole );
    buf_size_t const bal_size = NS(Multipole_get_bal_size)( multipole );

    if( ( bal_size > index ) && ( bal != SIXTRL_NULLPTR ) )
    {
        bal[ index ] = bal_value;
    }

    return;
}

SIXTRL_INLINE void NS(Multipole_set_knl_value)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const index,
    NS(multipole_real_t)  const knl_value )
{
    NS(multipole_real_t) const bal_value = knl_value / (
        ( NS(multipole_real_t) )NS(_calculate_factorial)( index ) );

    NS(Multipole_set_bal_value)( multipole, 2u * index, bal_value );
    return;
}

SIXTRL_INLINE void NS(Multipole_set_ksl_value)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(buffer_size_t) const index,
    NS(multipole_real_t) const ksl_value )
{
    NS(multipole_real_t) const bal_value = ksl_value / (
        ( NS(multipole_real_t) )NS(_calculate_factorial)( index ) );

    NS(Multipole_set_bal_value)( multipole, 2u * index + 1u, bal_value );
    return;
}

SIXTRL_INLINE int NS(Multipole_compare_values)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs )
{
    int compare_value = -1;

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        compare_value = 0;

        if( NS(Multipole_get_order)( lhs ) >
            NS(Multipole_get_order)( rhs ) )
        {
            compare_value = +1;
        }
        else if( NS(Multipole_get_order)( lhs ) <
                 NS(Multipole_get_order)( rhs ) )
        {
            compare_value = -1;
        }

        if( compare_value == 0 )
        {
            if( NS(Multipole_get_length)( lhs ) >
                NS(Multipole_get_length)( rhs ) )
            {
                compare_value = +1;
            }
            else if( NS(Multipole_get_length)( lhs ) <
                     NS(Multipole_get_length)( rhs ) )
            {
                compare_value = -1;
            }
        }

        if( compare_value == 0 )
        {
            if( NS(Multipole_get_hxl)( lhs ) >
                NS(Multipole_get_hxl)( rhs ) )
            {
                compare_value = +1;
            }
            else if( NS(Multipole_get_hxl)( lhs ) <
                     NS(Multipole_get_hxl)( rhs ) )
            {
                compare_value = -1;
            }
        }

        if( compare_value == 0 )
        {
            if( NS(Multipole_get_hyl)( lhs ) >
                NS(Multipole_get_hyl)( rhs ) )
            {
                compare_value = +1;
            }
            else if( NS(Multipole_get_hyl)( lhs ) <
                     NS(Multipole_get_hyl)( rhs ) )
            {
                compare_value = -1;
            }
        }

        if( ( compare_value == 0 ) &&
            ( NS(Multipole_get_order)( lhs ) > 0 ) )
        {
            SIXTRL_ASSERT( NS(Multipole_get_const_bal)( lhs ) != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( NS(Multipole_get_const_bal)( rhs ) != SIXTRL_NULLPTR );

            SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t) const* lhs_it =
                NS(Multipole_get_const_bal)( lhs );

            SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t) const* lhs_end =
                lhs_it + NS(Multipole_get_bal_size)( lhs );

            SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t) const* rhs_it =
                NS(Multipole_get_const_bal)( rhs );

            for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
            {
                if( *lhs_it > *rhs_it )
                {
                    compare_value = +1;
                }
                else if( *lhs_it < *rhs_it )
                {
                    compare_value = -1;
                }

                break;
            }
        }
    }
    else if( rhs != SIXTRL_NULLPTR )
    {
        compare_value = +1;
    }

    return compare_value;
}

SIXTRL_INLINE int NS(Multipole_compare_values_with_treshold)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs,
    NS(multipole_real_t) const treshold )
{
    typedef NS(multipole_real_t) real_t;

    SIXTRL_STATIC_VAR real_t const ZERO = ( real_t )0.0;

    int compare_value = -1;

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( treshold > ZERO ) )
    {
        compare_value = 0;

        if( NS(Multipole_get_order)( lhs ) >
            NS(Multipole_get_order)( rhs ) )
        {
            compare_value = +1;
        }
        else if( NS(Multipole_get_order)( lhs ) <
                 NS(Multipole_get_order)( rhs ) )
        {
            compare_value = -1;
        }

        if( compare_value == 0 )
        {
            real_t const diff = NS(Multipole_get_length)( lhs ) -
                                NS(Multipole_get_length)( rhs );

            real_t const abs_diff = ( diff > ZERO ) ? diff : -diff;

            if( abs_diff > treshold )
            {
                if( diff > ZERO )
                {
                    compare_value = +1;
                }
                else if( diff < ZERO )
                {
                    compare_value = -1;
                }
            }
        }

        if( compare_value == 0 )
        {
            real_t const diff = NS(Multipole_get_hxl)( lhs ) -
                                NS(Multipole_get_hxl)( rhs );

            real_t const abs_diff = ( diff > ZERO ) ? diff : -diff;

            if( abs_diff > treshold )
            {
                if( diff > ZERO )
                {
                    compare_value = +1;
                }
                else if( diff < ZERO )
                {
                    compare_value = -1;
                }
            }
        }

        if( compare_value == 0 )
        {
            real_t const diff = NS(Multipole_get_hyl)( lhs ) -
                                NS(Multipole_get_hyl)( rhs );

            real_t const abs_diff = ( diff > ZERO ) ? diff : -diff;

            if( abs_diff > treshold )
            {
                if( diff > ZERO )
                {
                    compare_value = +1;
                }
                else if( diff < ZERO )
                {
                    compare_value = -1;
                }
            }
        }

        if( ( compare_value == 0 ) &&
            ( NS(Multipole_get_order)( lhs ) > 0 ) )
        {
            SIXTRL_ASSERT( NS(Multipole_get_const_bal)( lhs ) != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( NS(Multipole_get_const_bal)( rhs ) != SIXTRL_NULLPTR );

            SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t) const* lhs_it =
                NS(Multipole_get_const_bal)( lhs );

            SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t) const* lhs_end =
                lhs_it + NS(Multipole_get_bal_size)( lhs );

            SIXTRL_BE_DATAPTR_DEC NS(multipole_real_t) const* rhs_it =
                NS(Multipole_get_const_bal)( rhs );

            for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
            {
                real_t const diff = *lhs_it - *rhs_it;
                real_t const abs_diff = ( diff > ZERO ) ? diff : -diff;

                if( abs_diff > treshold )
                {
                    if( diff > ZERO )
                    {
                        compare_value = +1;
                    }
                    else if( diff < ZERO )
                    {
                        compare_value = -1;
                    }

                    break;
                }
            }
        }
    }
    else if( ( rhs != SIXTRL_NULLPTR ) && ( treshold > ZERO ) )
    {
        compare_value = +1;
    }

    return compare_value;
}

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_API_C99_H__ */

/* end: sixtracklib/common/beam_elements/multipole/multipole_api.h */
