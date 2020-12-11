#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_API_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_API_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
    #endif /* !defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/cavity.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* voltage: */

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename CavityTraits< CavityT >::real_t Cavity_default_voltage(
        SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT
            /* elem */ = SIXTRL_NULLPTR )
    {
        return typename CavityTraits< CavityT >::real_t{ 0 };
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
        typename CavityTraits< CavityT >::real_t >::type
    Cavity_voltage( SIXTRL_BE_ARGPTR_DEC const CavityT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Cavity_is_type< CavityT >(),
            "CavityT required to be a cavity class" );

        return st::Cavity_default_voltage< typename
            st::CavityTraits< CavityT >::real_t >( elem );
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
        typename TypeMethodParamTraits< typename CavityTraits<
            CavityT >::real_t >::const_existing_type >::type
    Cavity_voltage( SIXTRL_BE_ARGPTR_DEC const CavityT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return elem->voltage;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_set_voltage( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT /*elem*/,
                        RealArg /* voltage_value */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_set_voltage( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg voltage_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->voltage = voltage_value;
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_set_voltage( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg voltage_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->voltage = std::move( voltage_value );
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_set_voltage( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg voltage_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename st::CavityTraits< CavityT >::real_t dst_real_t;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return st::Types_perform_assignment< src_real_t, dst_real_t >(
            elem->voltage, voltage_value );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
    Cavity_set_default_voltage(
        SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
    {
        return SIXTRL_CXX_NAMESPACE::Cavity_set_voltage( elem,
                    SIXTRL_CXX_NAMESPACE::Cavity_default_voltage( elem ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* frequency: */

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename CavityTraits< CavityT >::real_t Cavity_default_frequency(
        SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT
            /* elem */ = SIXTRL_NULLPTR )
    {
        return typename CavityTraits< CavityT >::real_t{ 0 };
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
        typename CavityTraits< CavityT >::real_t >::type
    Cavity_frequency( SIXTRL_BE_ARGPTR_DEC const CavityT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Cavity_is_type< CavityT >(),
            "CavityT required to be a cavity class" );

        return st::Cavity_default_frequency< typename
            st::CavityTraits< CavityT >::real_t >( elem );
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
        typename TypeMethodParamTraits< typename CavityTraits<
            CavityT >::real_t >::const_existing_type >::type
    Cavity_frequency( SIXTRL_BE_ARGPTR_DEC const CavityT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return elem->frequency;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_set_frequency( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT /*elem*/,
                        RealArg /* frequency_value */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_set_frequency( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg frequency_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal<
            typename std::decay< RealArg >::type >( frequency_value,
                typename std::decay< RealArg >::type{ 0 } ) );
        elem->frequency = frequency_value;
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_set_frequency( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg frequency_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal<
            typename std::decay< RealArg >::type >( frequency_value,
                typename std::decay< RealArg >::type{ 0 } ) );
        elem->frequency = std::move( frequency_value );
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_set_frequency( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg frequency_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename st::CavityTraits< CavityT >::real_t dst_real_t;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< src_real_t >(
                frequency_value, src_real_t{ 0 } ) );

        return st::Types_perform_assignment< src_real_t, dst_real_t >(
            elem->frequency, frequency_value );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
    Cavity_set_default_frequency(
        SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
    {
        return SIXTRL_CXX_NAMESPACE::Cavity_set_frequency( elem,
                    SIXTRL_CXX_NAMESPACE::Cavity_default_frequency( elem ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* lag: */

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename CavityTraits< CavityT >::real_t Cavity_default_lag(
        SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT
            /* elem */ = SIXTRL_NULLPTR )
    {
        return typename CavityTraits< CavityT >::real_t{ 0 };
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
        typename CavityTraits< CavityT >::real_t >::type
    Cavity_lag( SIXTRL_BE_ARGPTR_DEC const CavityT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::Cavity_default_lag< typename
            st::CavityTraits< CavityT >::real_t >( elem );
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >(),
        typename TypeMethodParamTraits< typename CavityTraits<
            CavityT >::real_t >::const_existing_type >::type
    Cavity_lag( SIXTRL_BE_ARGPTR_DEC const CavityT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return elem->lag;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_set_lag( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT /*elem*/,
                        RealArg /* lag_value */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_set_lag( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg lag_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->lag = lag_value;
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_set_lag( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg lag_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->lag = std::move( lag_value );
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_set_lag( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg lag_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename st::CavityTraits< CavityT >::real_t dst_real_t;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return st::Types_perform_assignment< src_real_t, dst_real_t >(
            elem->lag, lag_value );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
    Cavity_set_default_lag( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
    {
        return SIXTRL_CXX_NAMESPACE::Cavity_set_lag( elem,
                    SIXTRL_CXX_NAMESPACE::Cavity_default_lag( elem ) );
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* voltage: */

template< class CavityT > SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::CavityTraits< CavityT >::real_t
NS(Cavity_default_voltage)( SIXTRL_BE_ARGPTR_DEC const CavityT *const
    SIXTRL_RESTRICT elem = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_default_voltage( elem );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::CavityTraits< CavityT >::real_t
        >::const_existing_type
NS(Cavity_voltage)( SIXTRL_BE_ARGPTR_DEC const CavityT *const
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_CXX_NAMESPACE::Cavity_voltage( elem );
}

template< class CavityT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_set_voltage)( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg voltage_value )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_set_voltage( elem, voltage_value );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_set_default_voltage)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_set_default_voltage( elem );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* frequency: */

template< class CavityT > SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::CavityTraits< CavityT >::real_t
NS(Cavity_default_frequency)( SIXTRL_BE_ARGPTR_DEC const CavityT *const
    SIXTRL_RESTRICT elem = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_default_frequency( elem );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::CavityTraits< CavityT >::real_t
        >::const_existing_type
NS(Cavity_frequency)( SIXTRL_BE_ARGPTR_DEC const CavityT *const
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_CXX_NAMESPACE::Cavity_frequency( elem );
}

template< class CavityT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_set_frequency)( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                          RealArg frequency_value )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_set_frequency( elem, frequency_value );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_set_default_frequency)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_set_default_frequency( elem );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* lag: */

template< class CavityT > SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::CavityTraits< CavityT >::real_t
NS(Cavity_default_lag)( SIXTRL_BE_ARGPTR_DEC const CavityT *const
    SIXTRL_RESTRICT elem = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_default_lag( elem );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::CavityTraits< CavityT >::real_t
        >::const_existing_type
NS(Cavity_lag)( SIXTRL_BE_ARGPTR_DEC const CavityT *const
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_CXX_NAMESPACE::Cavity_lag( elem );
}

template< class CavityT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_set_lag)( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg lag_value )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_set_lag( elem, lag_value );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_set_default_lag)( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_set_default_lag( elem );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* voltage: */

SIXTRL_STATIC SIXTRL_FN NS(be_real_t)
NS(Cavity_default_voltage)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(Cavity_voltage)( SIXTRL_BE_ARGPTR_DEC
    const NS(Cavity) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_set_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const voltage_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_set_default_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* frequency: */

SIXTRL_STATIC SIXTRL_FN NS(be_real_t)
NS(Cavity_default_frequency)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(Cavity_frequency)(
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_set_frequency)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const frequency_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_set_default_frequency)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* lag: */

SIXTRL_STATIC SIXTRL_FN NS(be_real_t)
NS(Cavity_default_lag)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(Cavity_lag)( SIXTRL_BE_ARGPTR_DEC
    const NS(Cavity) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_set_lag)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const lag_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_set_default_lag)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* voltage: */

SIXTRL_INLINE NS(be_real_t) NS(Cavity_default_voltage)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(be_real_t) )0;
}

SIXTRL_INLINE NS(be_real_t) NS(Cavity_voltage)( SIXTRL_BE_ARGPTR_DEC
    const NS(Cavity) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return elem->voltage;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_set_voltage)( SIXTRL_BE_ARGPTR_DEC
        NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const voltage_value ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->voltage = voltage_value;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_set_default_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return NS(Cavity_set_voltage)( elem, NS(Cavity_default_voltage)() );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* frequency: */

SIXTRL_INLINE NS(be_real_t) NS(Cavity_default_frequency)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(be_real_t) )0;
}

SIXTRL_INLINE NS(be_real_t) NS(Cavity_frequency)( SIXTRL_BE_ARGPTR_DEC
    const NS(Cavity) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return elem->frequency;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_set_frequency)( SIXTRL_BE_ARGPTR_DEC
        NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const frequency_value ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->frequency = frequency_value;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_set_default_frequency)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return NS(Cavity_set_frequency)( elem, NS(Cavity_default_frequency)() );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* lag: */

SIXTRL_INLINE NS(be_real_t) NS(Cavity_default_lag)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(be_real_t) )0;
}

SIXTRL_INLINE NS(be_real_t) NS(Cavity_lag)( SIXTRL_BE_ARGPTR_DEC
    const NS(Cavity) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return elem->lag;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_set_lag)( SIXTRL_BE_ARGPTR_DEC
        NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const lag_value ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->lag = lag_value;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_set_default_lag)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return NS(Cavity_set_lag)( elem, NS(Cavity_default_lag)() );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_API_H__ */
