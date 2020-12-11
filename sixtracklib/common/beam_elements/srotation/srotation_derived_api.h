#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_DERIVED_API_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_DERIVED_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/srotation.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation_api.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* --------------------------------------------------------------------- */
    /* angle: */

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
        typename SRotationTraits< SRotationT >::real_t >::type
    SRotation_angle_rad( SIXTRL_BE_ARGPTR_DEC const SRotationT *const
        SIXTRL_RESTRICT /* elem */ ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::SRotation_is_type< SRotationT >(),
            "SRotationT required to be a s-rotation class" );

        return typename SRotationTraits< SRotationT >::real_t{ 0 };
    }

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
        typename SRotationTraits< SRotationT >::real_t >::type
    SRotation_angle_rad( SIXTRL_BE_ARGPTR_DEC const SRotationT *const
        SIXTRL_RESTRICT elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename SRotationTraits< SRotationT >::real_t real_t;
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );

        return st::atan2< real_t >( elem->sin_z, elem->cos_z );
    }

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename SRotationTraits<
        SRotationT >::real_t
    SRotation_angle_deg( SIXTRL_BE_ARGPTR_DEC const SRotationT *const
        SIXTRL_RESTRICT elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename SRotationTraits< SRotationT >::real_t real_t;
        return st::MathConst_rad2deg< real_t >() *
               st::SRotation_angle_rad( elem );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_update_angle_rad(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT /*elem*/,
        RealArg /* angle_rad */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::decay< RealArg >::type, typename SRotationTraits<
                 SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_update_angle_rad(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
        RealArg angle_rad ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename SRotationTraits< SRotationT >::real_t real_t;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->cos_z = st::cos< real_t >( angle_rad );
        elem->sin_z = st::sin< real_t >( angle_rad );
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename std::decay< RealArg >::type, typename SRotationTraits<
                 SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_update_angle_rad(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
        RealArg in_angle_rad ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            typedef typename std::decay< RealArg >::type src_real_t;
            typedef typename SRotationTraits< SRotationT >::real_t real_t;

            real_t angle_rad;
            status = st::Types_perform_assignment< src_real_t, real_t >(
                angle_rad, in_angle_rad );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                elem->cos_z = st::cos< real_t >( angle_rad );
                elem->sin_z = st::sin< real_t >( angle_rad );
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    SRotation_update_angle_deg(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg angle )
    {
        typedef typename std::decay< RealArg >::type real_angle_t;
        return SIXTRL_CXX_NAMESPACE::SRotation_update_angle_rad( elem,
            SIXTRL_CXX_NAMESPACE::MathConst_deg2rad< real_angle_t >() * angle );
    }

    /* --------------------------------------------------------------------- */
    /* cos_z */

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_add_to_cos_z( SIXTRL_BE_ARGPTR_DEC SRotationT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_cos_z */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_subtract_from_cos_z( SIXTRL_BE_ARGPTR_DEC SRotationT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_cos_z */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_scale_cos_z( SIXTRL_BE_ARGPTR_DEC SRotationT*
        SIXTRL_RESTRICT /* elem */, RealArg /* c */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_change_sign_cos_z( SIXTRL_BE_ARGPTR_DEC SRotationT*
        SIXTRL_RESTRICT /* elem */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename SRotationTraits< SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_add_to_cos_z( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
                         RealArg d_cos_z )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->cos_z += d_cos_z;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename SRotationTraits< SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_subtract_from_cos_z(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg d_cos_z )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->cos_z -= d_cos_z;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename SRotationTraits< SRotationT >::real_t >(),
        arch_status_t >::type
    SRotation_scale_cos_z( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
                        RealArg c )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->cos_z *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_change_sign_cos_z(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->cos_z = -( elem->cos_z );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename SRotationTraits< SRotationT >::real_t >(),
        arch_status_t >::type
    SRotation_add_to_cos_z( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
                         RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename SRotationTraits< SRotationT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_cos_z;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_cos_z, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->cos_z += d_cos_z;
        }

        return status;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename SRotationTraits< SRotationT >::real_t >(),
        arch_status_t >::type
    SRotation_subtract_from_cos_z(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename SRotationTraits< SRotationT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_cos_z;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_cos_z, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->cos_z -= d_cos_z;
        }

        return status;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename SRotationTraits< SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_scale_cos_z( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
                        RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename SRotationTraits< SRotationT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) elem->cos_z *= c;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* sin_z */

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_add_to_sin_z( SIXTRL_BE_ARGPTR_DEC SRotationT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_sin_z */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_subtract_from_sin_z( SIXTRL_BE_ARGPTR_DEC SRotationT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_sin_z */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_scale_sin_z( SIXTRL_BE_ARGPTR_DEC SRotationT*
        SIXTRL_RESTRICT /* elem */, RealArg /* c */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_change_sign_sin_z( SIXTRL_BE_ARGPTR_DEC SRotationT*
        SIXTRL_RESTRICT /* elem */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename SRotationTraits< SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_add_to_sin_z( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
                         RealArg d_sin_z )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->sin_z += d_sin_z;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename SRotationTraits< SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_subtract_from_sin_z(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg d_sin_z )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->sin_z -= d_sin_z;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename SRotationTraits< SRotationT >::real_t >(),
        arch_status_t >::type
    SRotation_scale_sin_z( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
                        RealArg c )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->sin_z *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_change_sign_sin_z(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->sin_z = -( elem->sin_z );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename SRotationTraits< SRotationT >::real_t >(),
        arch_status_t >::type
    SRotation_add_to_sin_z( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
                         RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename SRotationTraits< SRotationT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_sin_z;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_sin_z, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->sin_z += d_sin_z;
        }

        return status;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename SRotationTraits< SRotationT >::real_t >(),
        arch_status_t >::type
    SRotation_subtract_from_sin_z(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename SRotationTraits< SRotationT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_sin_z;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_sin_z, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->sin_z -= d_sin_z;
        }

        return status;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename SRotationTraits< SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_scale_sin_z( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
                        RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename SRotationTraits< SRotationT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) elem->sin_z *= c;
        }

        return status;
    }
}

template< class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::SRotationTraits< SRotationT >::real_t
NS(SRotation_angle_rad)( SIXTRL_BE_ARGPTR_DEC const SRotationT *const
    SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_angle_rad( elem );
}

template< class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::SRotationTraits< SRotationT >::real_t
NS(SRotation_angle_deg)( SIXTRL_BE_ARGPTR_DEC const SRotationT *const
    SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_angle_deg( elem );
}

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::SRotationTraits< SRotationT >::real_t
NS(SRotation_update_angle_rad)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg angle_rad )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_update_angle_rad( elem, angle_rad );
}

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::SRotationTraits< SRotationT >::real_t
NS(SRotation_update_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg angle_deg )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_update_angle_rad( elem, angle_deg );
}

/* cos_z */

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_add_to_cos_z)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg d_cos_z )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_add_to_cos_z( elem, d_cos_z );
}

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_subtract_from_cos_z)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg d_cos_z )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_subtract_from_cos_z( elem, d_cos_z );
}

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_scale_cos_z)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_scale_cos_z( elem, c );
}

template< class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_change_sign_cos_z)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_change_sign_cos_z( elem );
}

/* sin_z */

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_add_to_sin_z)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg d_sin_z )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_add_to_sin_z( elem, d_sin_z );
}

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_subtract_from_sin_z)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg d_sin_z )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_subtract_from_sin_z( elem, d_sin_z );
}

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_scale_sin_z)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_scale_sin_z( elem, c );
}

template< class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_change_sign_sin_z)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_change_sign_sin_z( elem );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(SRotation_angle_rad)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_update_angle_rad)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const angle_rad ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(SRotation_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_update_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const angle_deg ) SIXTRL_NOEXCEPT;

/* cos_z */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_add_to_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_cos_z ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_subtract_from_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_cos_z ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_scale_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_change_sign_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

/* sin_z */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_add_to_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_sin_z ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_subtract_from_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_sin_z ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_scale_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_change_sign_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(be_real_t) NS(SRotation_angle_rad)( SIXTRL_BE_ARGPTR_DEC const
    NS(SRotation) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return NS(atan2)( elem->sin_z, elem->cos_z );
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_update_angle_rad)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const angle_rad ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( elem != SIXTRL_NULLPTR )
    {
        elem->cos_z = NS(cos)( angle_rad );
        elem->sin_z = NS(sin)( angle_rad );
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(be_real_t) NS(SRotation_angle_deg)( SIXTRL_BE_ARGPTR_DEC const
    NS(SRotation) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return NS(MathConst_rad2deg)() * NS(SRotation_angle_rad)( elem );
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_update_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const angle_deg ) SIXTRL_NOEXCEPT
{
    return NS(SRotation_update_angle_rad)(
        elem, NS(MathConst_deg2rad)() * angle_deg );
}

/* cos_z */

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_add_to_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_cos_z ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->cos_z += d_cos_z;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_subtract_from_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_cos_z ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->cos_z -= d_cos_z;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_scale_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->cos_z *= factor;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_change_sign_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->cos_z = -( elem->cos_z );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* sin_z */

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_add_to_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_sin_z ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->sin_z += d_sin_z;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_subtract_from_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_sin_z ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->sin_z -= d_sin_z;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_scale_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->sin_z *= factor;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_change_sign_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->sin_z = -( elem->sin_z );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_DERIVED_API_H__ */
