#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_INIT_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_INIT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/srotation_api.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation_derived_api.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SRotationT*
    SRotation_preset( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::SRotation_is_type< SRotationT >(),
            "SRotationT required to be a s-rotation class" );

        if( elem != SIXTRL_NULLPTR )
        {
            st::arch_status_t status  = st::SRotation_set_default_cos_z( elem );
            status |= st::SRotation_set_default_sin_z( elem );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        return elem;
    }

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    SRotation_init( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::SRotation_set_default_cos_z( elem ) |
               st::SRotation_set_default_sin_z( elem );
    }

    template< class SRotationT, typename CosZArg, typename SinZArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    SRotation_init_detailed(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
        CosZArg cos_z_value, SinZArg sin_z_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::SRotation_set_cos_z( elem, cos_z_value ) |
               st::SRotation_set_sin_z( elem, sin_z_value );
    }

    template< class SRotationT, typename CosZArg, typename SinZArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    SRotation_init( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
        CosZArg cos_z_value, SinZArg sin_z_value )
    {
        return SIXTRL_CXX_NAMESPACE::SRotation_init_detailed(
            elem, cos_z_value, sin_z_value );
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    SRotation_init_angle_rad( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT
        elem, RealArg angle_rad )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return st::SRotation_update_angle_rad( elem, angle_rad );
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    SRotation_init_angle_deg( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT
        elem, RealArg angle_deg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return st::SRotation_update_angle_deg( elem, angle_deg );
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    SRotation_init( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT
        elem, RealArg angle_deg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return st::SRotation_update_angle_deg( elem, angle_deg );
    }

    /* ********************************************************************* */

    template< class SRotationT, store_backend_t StoreT >
    struct ObjDataInitialiser< SRotationT, StoreT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(), void >::type >
    {
        SIXTRL_STATIC SIXTRL_FN void preset( SIXTRL_BE_ARGPTR_DEC SRotationT*
            SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::SRotation_preset( obj );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t init(
            SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT obj,
            Args&&... init_args )
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_init(
                obj, std::forward< Args >( init_args )... );
        }
    };
}

template< class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SRotationT*
NS(SRotation_preset)( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_preset( elem );
}

template< class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_init)( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_init( elem );
}

template< class SRotationT, typename CosZArg, typename SinZArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
    CosZArg cos_z_value, SinZArg sin_z_value )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_init_detailed(
        elem, cos_z_value, sin_z_value );
}

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_init_angle_rad)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg angle_rad )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_init_angle_rad( elem, angle_rad );
}

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_init_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg angle_deg )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_init_angle_deg( elem, angle_deg );
}

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_init)( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
                    RealArg angle_deg )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_init_angle_deg( elem, angle_deg );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(SRotation)*
NS(SRotation_preset)( SIXTRL_BE_ARGPTR_DEC NS(SRotation)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_init)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const cos_z_value,
    NS(be_real_t) const sin_z_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_init_angle_rad)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const angle_rad ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_init_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const angle_deg ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SRotation)* NS(SRotation_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    if( elem != SIXTRL_NULLPTR )
    {
        NS(SRotation_set_default_cos_z)( elem );
        NS(SRotation_set_default_sin_z)( elem );
    }

    return elem;
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_init)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return NS(SRotation_set_default_cos_z)( elem ) |
           NS(SRotation_set_default_sin_z)( elem );
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const cos_z_value,
    NS(be_real_t) const sin_z_value ) SIXTRL_NOEXCEPT
{
    return NS(SRotation_set_cos_z)( elem, cos_z_value ) |
           NS(SRotation_set_sin_z)( elem, sin_z_value );
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_init_angle_rad)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const angle_rad ) SIXTRL_NOEXCEPT
{
    return NS(SRotation_update_angle_rad)( elem, angle_rad );
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_init_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const angle_deg ) SIXTRL_NOEXCEPT
{
    return NS(SRotation_update_angle_deg)( elem, angle_deg );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_INIT_H__ */
