#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_DERIVED_API_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_DERIVED_API_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/cavity.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_api.h"
    #include "sixtracklib/common/internal/math_arithmetic.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* voltage */

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_add_to_voltage( SIXTRL_BE_ARGPTR_DEC CavityT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_voltage */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_subtract_from_voltage( SIXTRL_BE_ARGPTR_DEC CavityT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_voltage */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_scale_voltage( SIXTRL_BE_ARGPTR_DEC CavityT*
        SIXTRL_RESTRICT /* elem */, RealArg /* c */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_change_sign_voltage( SIXTRL_BE_ARGPTR_DEC CavityT*
        SIXTRL_RESTRICT /* elem */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_add_to_voltage( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                         RealArg d_voltage )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->voltage += d_voltage;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_subtract_from_voltage(
        SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg d_voltage )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->voltage -= d_voltage;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        arch_status_t >::type
    Cavity_scale_voltage( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg c )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->voltage *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_change_sign_voltage(
        SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->voltage = -( elem->voltage );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        arch_status_t >::type
    Cavity_add_to_voltage( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                         RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename CavityTraits< CavityT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_voltage;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_voltage, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->voltage += d_voltage;
        }

        return status;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        arch_status_t >::type
    Cavity_subtract_from_voltage(
        SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename CavityTraits< CavityT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_voltage;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_voltage, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->voltage -= d_voltage;
        }

        return status;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_scale_voltage( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename CavityTraits< CavityT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) elem->voltage *= c;
        }

        return status;
    }

    /* frequency */

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_add_to_frequency( SIXTRL_BE_ARGPTR_DEC CavityT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_frequency */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_subtract_from_frequency( SIXTRL_BE_ARGPTR_DEC CavityT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_frequency */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_scale_frequency( SIXTRL_BE_ARGPTR_DEC CavityT*
        SIXTRL_RESTRICT /* elem */, RealArg /* c */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_change_sign_frequency( SIXTRL_BE_ARGPTR_DEC CavityT*
        SIXTRL_RESTRICT /* elem */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_add_to_frequency( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                         RealArg d_frequency )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->frequency += d_frequency;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_subtract_from_frequency(
        SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg d_frequency )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->frequency -= d_frequency;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        arch_status_t >::type
    Cavity_scale_frequency( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg c )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->frequency *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_change_sign_frequency(
        SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->frequency = -( elem->frequency );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        arch_status_t >::type
    Cavity_add_to_frequency( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                         RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename CavityTraits< CavityT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_frequency;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_frequency, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->frequency += d_frequency;
        }

        return status;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        arch_status_t >::type
    Cavity_subtract_from_frequency(
        SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename CavityTraits< CavityT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_frequency;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_frequency, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->frequency -= d_frequency;
        }

        return status;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_scale_frequency( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename CavityTraits< CavityT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) elem->frequency *= c;
        }

        return status;
    }

    /* lag */

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_add_to_lag( SIXTRL_BE_ARGPTR_DEC CavityT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_lag */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_subtract_from_lag( SIXTRL_BE_ARGPTR_DEC CavityT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_lag */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_scale_lag( SIXTRL_BE_ARGPTR_DEC CavityT*
        SIXTRL_RESTRICT /* elem */, RealArg /* c */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_change_sign_lag( SIXTRL_BE_ARGPTR_DEC CavityT*
        SIXTRL_RESTRICT /* elem */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_add_to_lag( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                         RealArg d_lag )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->lag += d_lag;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_subtract_from_lag(
        SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg d_lag )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->lag -= d_lag;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        arch_status_t >::type
    Cavity_scale_lag( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg c )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->lag *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_change_sign_lag(
        SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->lag = -( elem->lag );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        arch_status_t >::type
    Cavity_add_to_lag( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                         RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename CavityTraits< CavityT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_lag;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_lag, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->lag += d_lag;
        }

        return status;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        arch_status_t >::type
    Cavity_subtract_from_lag(
        SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename CavityTraits< CavityT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_lag;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_lag, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->lag -= d_lag;
        }

        return status;
    }

    template< class CavityT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_impl_default< CavityT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename CavityTraits< CavityT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_scale_lag( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                        RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename CavityTraits< CavityT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) elem->lag *= c;
        }

        return status;
    }
}

/* voltage */

template< class CavityT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_add_to_voltage)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg d_voltage )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_add_to_voltage( elem, d_voltage );
}

template< class CavityT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_subtract_from_voltage)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg d_voltage )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_subtract_from_voltage( elem, d_voltage );
}

template< class CavityT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_scale_voltage)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_scale_voltage( elem, c );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_change_sign_voltage)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_change_sign_voltage( elem );
}

/* frequency */

template< class CavityT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_add_to_frequency)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg d_frequency )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_add_to_frequency( elem, d_frequency );
}

template< class CavityT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_subtract_from_frequency)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg d_frequency )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_subtract_from_frequency( elem, d_frequency );
}

template< class CavityT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_scale_frequency)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_scale_frequency( elem, c );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_change_sign_frequency)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_change_sign_frequency( elem );
}

/* lag */

template< class CavityT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_add_to_lag)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg d_lag )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_add_to_lag( elem, d_lag );
}

template< class CavityT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_subtract_from_lag)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg d_lag )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_subtract_from_lag( elem, d_lag );
}

template< class CavityT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_scale_lag)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_scale_lag( elem, c );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_change_sign_lag)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_change_sign_lag( elem );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* voltage */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_add_to_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_voltage ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_subtract_from_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_voltage ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_scale_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_change_sign_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

/* frequency */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_add_to_frequency)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_frequency ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_subtract_from_frequency)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_frequency ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_scale_frequency)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_change_sign_frequency)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

/* lag */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_add_to_lag)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_lag ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_subtract_from_lag)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_lag ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_scale_lag)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_change_sign_lag)(
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

/* voltage */

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_add_to_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_voltage ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->voltage += d_voltage;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_subtract_from_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_voltage ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->voltage -= d_voltage;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_scale_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->voltage *= factor;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_change_sign_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->voltage = -( elem->voltage );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* frequency */

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_add_to_frequency)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_frequency ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->frequency += d_frequency;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_subtract_from_frequency)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_frequency ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->frequency -= d_frequency;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_scale_frequency)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->frequency *= factor;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_change_sign_frequency)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->frequency = -( elem->frequency );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* lag */

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_add_to_lag)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_lag ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->lag += d_lag;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_subtract_from_lag)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_lag ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->lag -= d_lag;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_scale_lag)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->lag *= factor;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_change_sign_lag)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->lag = -( elem->lag );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_DERIVED_API_H__ */
