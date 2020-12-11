#ifndef SIXTRACKLIB_COMMON_INTERNAL_MATH_ARITHMETIC_H__
#define SIXTRACKLIB_COMMON_INTERNAL_MATH_ARITHMETIC_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cmath>
        #include <iterator>
        #include <type_traits>
    #endif /* __cplusplus */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/type_store_traits.hpp"
//     #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< typename LhsT, typename RhsT = LhsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::decay< RhsT >::type, typename TypeMethodParamTraits<
                LhsT >::const_argument_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_add_to(
        typename TypeMethodParamTraits< LhsT >::ref_argument_type lhs,
        typename TypeMethodParamTraits< RhsT >::const_argument_type rhs
    ) SIXTRL_NOEXCEPT
    {
        lhs += rhs;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< typename LhsT, typename RhsT = LhsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::decay< RhsT >::type, typename TypeMethodParamTraits<
                LhsT >::const_argument_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_add_to(
        typename TypeMethodParamTraits< LhsT >::ref_argument_type lhs,
        typename TypeMethodParamTraits< RhsT >::const_argument_type rhs
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeMethodParamTraits< LhsT >::value_type lhs_real_t;
        typedef typename TypeMethodParamTraits< LhsT >::value_type rhs_real_t;

        lhs_real_t arg;
        st::arch_status_t status = st::Types_perform_assignment<
            rhs_real_t, lhs_real_t >( arg, rhs );

        if( status == st::ARCH_STATUS_SUCCESS ) lhs += arg;
        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< typename LhsIter, typename RhsIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::iterator_traits< RhsIter >::value_type,
            typename std::iterator_traits< LhsIter >::value_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_add_to( LhsIter lhs_it, LhsIter lhs_end, RhsIter rhs_it )
    {
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
        {
            *lhs_it += *rhs_it;
        }

        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< typename LhsIter, typename RhsIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::iterator_traits< RhsIter >::value_type,
            typename std::iterator_traits< LhsIter >::value_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_add_to( LhsIter lhs_it, LhsIter lhs_end, RhsIter rhs_it )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::iterator_traits< LhsIter >::value_type lhs_val_t;
        typedef typename std::iterator_traits< LhsIter >::value_type rhs_val_t;

        st::arch_status_t status = st::ARCH_STATUS_SUCCESS;
        lhs_val_t temp;

        while( ( status == st::ARCH_STATUS_SUCCESS ) &&
               ( lhs_it != lhs_end ) )
        {
            status = st::Types_perform_assignment< rhs_val_t, lhs_val_t >(
                temp, *rhs_it++ );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                *lhs_it++ += temp;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    template< typename LhsT, typename RhsT = LhsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::decay< RhsT >::type, typename TypeMethodParamTraits<
                LhsT >::const_argument_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_subtract_from(
        typename TypeMethodParamTraits< LhsT >::ref_argument_type lhs,
        typename TypeMethodParamTraits< RhsT >::const_argument_type rhs
    ) SIXTRL_NOEXCEPT
    {
        lhs -= rhs;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< typename LhsT, typename RhsT = LhsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::decay< RhsT >::type, typename TypeMethodParamTraits<
                LhsT >::const_argument_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_subtract_from(
        typename TypeMethodParamTraits< LhsT >::ref_argument_type lhs,
        typename TypeMethodParamTraits< RhsT >::const_argument_type rhs
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeMethodParamTraits< LhsT >::value_type lhs_real_t;
        typedef typename TypeMethodParamTraits< LhsT >::value_type rhs_real_t;

        lhs_real_t arg;
        st::arch_status_t status = st::Types_perform_assignment<
            rhs_real_t, lhs_real_t >( arg, rhs );

        if( status == st::ARCH_STATUS_SUCCESS ) lhs -= arg;
        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< typename LhsIter, typename RhsIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::iterator_traits< RhsIter >::value_type,
            typename std::iterator_traits< LhsIter >::value_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_subtract_from(
        LhsIter lhs_it, LhsIter lhs_end, RhsIter rhs_it )
    {
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
        {
            *lhs_it -= *rhs_it;
        }

        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< typename LhsIter, typename RhsIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::iterator_traits< RhsIter >::value_type,
            typename std::iterator_traits< LhsIter >::value_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_subtract_from(
        LhsIter lhs_it, LhsIter lhs_end, RhsIter rhs_it )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::iterator_traits< LhsIter >::value_type lhs_val_t;
        typedef typename std::iterator_traits< RhsIter >::value_type rhs_val_t;

        st::arch_status_t status = st::ARCH_STATUS_SUCCESS;
        lhs_val_t temp;

        while( ( status == st::ARCH_STATUS_SUCCESS ) &&
               ( lhs_it != lhs_end ) )
        {
            status = st::Types_perform_assignment< rhs_val_t, lhs_val_t >(
                temp, *rhs_it++ );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                *lhs_it++ -= temp;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    template< typename LhsT, typename RhsT = LhsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::decay< RhsT >::type, typename TypeMethodParamTraits<
                LhsT >::const_argument_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_scale(
        typename TypeMethodParamTraits< LhsT >::ref_argument_type lhs,
        typename TypeMethodParamTraits< RhsT >::const_argument_type rhs
    ) SIXTRL_NOEXCEPT
    {
        lhs *= rhs;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< typename LhsT, typename RhsT = LhsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::decay< RhsT >::type, typename TypeMethodParamTraits<
                LhsT >::const_argument_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_scale(
        typename TypeMethodParamTraits< LhsT >::ref_argument_type lhs,
        typename TypeMethodParamTraits< RhsT >::const_argument_type rhs
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeMethodParamTraits< LhsT >::value_type lhs_real_t;
        typedef typename TypeMethodParamTraits< LhsT >::value_type rhs_real_t;

        lhs_real_t arg;
        st::arch_status_t status = st::Types_perform_assignment<
            rhs_real_t, lhs_real_t >( arg, rhs );

        if( status == st::ARCH_STATUS_SUCCESS ) lhs *= arg;
        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< typename LhsIter, typename RhsIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::iterator_traits< RhsIter >::value_type,
            typename std::iterator_traits< LhsIter >::value_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_scale(
        LhsIter lhs_it, LhsIter lhs_end, RhsIter rhs_it )
    {
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
        {
            *lhs_it *= *rhs_it;
        }

        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< typename LhsIter, typename RhsIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::iterator_traits< RhsIter >::value_type,
            typename std::iterator_traits< LhsIter >::value_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_scale(
        LhsIter lhs_it, LhsIter lhs_end, RhsIter rhs_it )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::iterator_traits< LhsIter >::value_type lhs_val_t;
        typedef typename std::iterator_traits< RhsIter >::value_type rhs_val_t;

        st::arch_status_t status = st::ARCH_STATUS_SUCCESS;
        lhs_val_t temp;

        while( ( status == st::ARCH_STATUS_SUCCESS ) &&
               ( lhs_it != lhs_end ) )
        {
            status = st::Types_perform_assignment< rhs_val_t, lhs_val_t >(
                temp, *rhs_it++ );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                *lhs_it++ *= temp;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    template< typename T >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !TypeStoreTraits< T >::is_signed,
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_change_sign( typename TypeMethodParamTraits<
        T >::ref_argument_type /* lhs */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }


    template< typename T >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        TypeStoreTraits< T >::is_signed,
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_change_sign( typename TypeMethodParamTraits<
        T >::ref_argument_type lhs ) SIXTRL_NOEXCEPT
    {
        lhs = -lhs;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< typename Iter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !TypeStoreTraits< typename std::iterator_traits< Iter >::value_type
            >::is_signed, SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_change_sign( Iter /*it*/, Iter /*end*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< typename Iter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        TypeStoreTraits< typename std::iterator_traits< Iter >::value_type
            >::is_signed, SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Math_arithmetic_change_sign( Iter it, Iter end ) SIXTRL_NOEXCEPT
    {
        for( ; it != end ; ++it )
        {
            *it = -( *it );
        }

        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* --------------------------------------------------------------------- */
}
#endif /* C++ */


#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Math_arithmetic_add_to_real_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const* SIXTRL_RESTRICT delta_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Math_arithmetic_add_to_int64_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T const* SIXTRL_RESTRICT delta_begin
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Math_arithmetic_subtract_from_real_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const* SIXTRL_RESTRICT delta_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Math_arithmetic_subtract_from_int64_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T const* SIXTRL_RESTRICT delta_begin
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Math_arithmetic_scale_real_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const* SIXTRL_RESTRICT delta_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Math_arithmetic_scale_int64_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T const* SIXTRL_RESTRICT delta_begin
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Math_arithmetic_change_sign_for_real_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT begin,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Math_arithmetic_change_sign_for_int64_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT begin,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(arch_status_t) NS(Math_arithmetic_add_to_real_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT lhs_it,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
        SIXTRL_RESTRICT delta_it ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( lhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) &&
        ( delta_it != SIXTRL_NULLPTR ) && ( lhs_it != delta_it ) )
    {
        for( ; lhs_it != lhs_end ; ++lhs_it, ++delta_it ) *lhs_it += *delta_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t)
NS(Math_arithmetic_add_to_int64_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT lhs_it,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T const*
        SIXTRL_RESTRICT delta_it ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( lhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) &&
        ( delta_it != SIXTRL_NULLPTR ) && ( lhs_it != delta_it ) )
    {
        for( ; lhs_it != lhs_end ; ++lhs_it, ++delta_it ) *lhs_it += *delta_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(arch_status_t) NS(Math_arithmetic_subtract_from_real_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT lhs_it,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
        SIXTRL_RESTRICT delta_it ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( lhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) &&
        ( delta_it != SIXTRL_NULLPTR ) && ( lhs_it != delta_it ) )
    {
        for( ; lhs_it != lhs_end ; ++lhs_it, ++delta_it ) *lhs_it -= *delta_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t)
NS(Math_arithmetic_subtract_from_int64_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT lhs_it,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T const*
        SIXTRL_RESTRICT delta_it ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( lhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) &&
        ( delta_it != SIXTRL_NULLPTR ) && ( lhs_it != delta_it ) )
    {
        for( ; lhs_it != lhs_end ; ++lhs_it, ++delta_it ) *lhs_it -= *delta_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(arch_status_t)
NS(Math_arithmetic_scale_real_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT lhs_it,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
        SIXTRL_RESTRICT delta_it ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( lhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) &&
        ( delta_it != SIXTRL_NULLPTR ) && ( lhs_it != delta_it ) )
    {
        for( ; lhs_it != lhs_end ; ++lhs_it, ++delta_it ) *lhs_it *= *delta_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t)
NS(Math_arithmetic_scale_int64_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT lhs_it,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T const*
        SIXTRL_RESTRICT delta_it ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( lhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) &&
        ( delta_it != SIXTRL_NULLPTR ) && ( lhs_it != delta_it ) )
    {
        for( ; lhs_it != lhs_end ; ++lhs_it, ++delta_it ) *lhs_it *= *delta_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(arch_status_t) NS(Math_arithmetic_change_sign_for_real_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT it,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT end
    ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it ) *it = -( *it );
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(Math_arithmetic_change_sign_for_int64_ranges)(
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* SIXTRL_RESTRICT it,
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T*
        SIXTRL_RESTRICT end ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it ) *it = -( *it );
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */


#endif /* SIXTRACKLIB_COMMON_INTERNAL_MATH_ARITHMETIC_H__ */
