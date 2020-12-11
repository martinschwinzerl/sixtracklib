#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_API_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/srotation.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* cos_z: */

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename SRotationTraits< SRotationT >::real_t SRotation_default_cos_z(
        SIXTRL_BE_ARGPTR_DEC const SRotationT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( elem ) = SIXTRL_NULLPTR )
    {
        return typename SRotationTraits< SRotationT >::real_t{ 1 };
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
        typename SRotationTraits< SRotationT >::real_t >::type
    SRotation_cos_z( SIXTRL_BE_ARGPTR_DEC const SRotationT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::SRotation_default_cos_z< typename
            SIXTRL_CXX_NAMESPACE::SRotationTraits<
                SRotationT >::real_t >( elem );
    }

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >(),
        typename TypeMethodParamTraits< typename SRotationTraits<
            SRotationT >::real_t >::const_existing_type >::type
    SRotation_cos_z( SIXTRL_BE_ARGPTR_DEC const SRotationT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return elem->cos_z;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_set_cos_z(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
        RealArg SIXTRL_UNUSED( cos_z_value ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename SRotationTraits< SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_set_cos_z(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
        RealArg cos_z_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal<
            typename std::decay< RealArg >::type >( cos_z_value,
                typename std::decay< RealArg >::type{ -1 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal<
            typename std::decay< RealArg >::type >( cos_z_value,
                typename std::decay< RealArg >::type{ +1 } ) );

        elem->cos_z = cos_z_value;
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename SRotationTraits< SRotationT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< RealArg,
            typename SRotationTraits< SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_set_cos_z(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
        RealArg cos_z_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal<
            typename std::decay< RealArg >::type >( cos_z_value,
                typename std::decay< RealArg >::type{ -1 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal<
            typename std::decay< RealArg >::type >( cos_z_value,
                typename std::decay< RealArg >::type{ +1 } ) );

        elem->cos_z = std::move( cos_z_value );
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename SRotationTraits< SRotationT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename SRotationTraits< SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_set_cos_z(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
        RealArg cos_z_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename st::SRotationTraits< SRotationT >::real_t dst_real_t;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< src_real_t >(
            cos_z_value, src_real_t{ -1 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< src_real_t >(
            cos_z_value, src_real_t{ +1 } ) );

        return st::Types_perform_assignment< src_real_t, dst_real_t >(
            elem->cos_z, cos_z_value );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
    SRotation_set_default_cos_z( SIXTRL_BE_ARGPTR_DEC SRotationT*
        SIXTRL_RESTRICT elem )
    {
        return SIXTRL_CXX_NAMESPACE::SRotation_set_cos_z( elem,
                    SIXTRL_CXX_NAMESPACE::SRotation_default_cos_z( elem ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* sin_z: */

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename SRotationTraits< SRotationT >::real_t SRotation_default_sin_z(
        SIXTRL_BE_ARGPTR_DEC const SRotationT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( elem ) = SIXTRL_NULLPTR )
    {
        return typename SRotationTraits< SRotationT >::real_t{ 0 };
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
        typename SRotationTraits< SRotationT >::real_t >::type
    SRotation_sin_z( SIXTRL_BE_ARGPTR_DEC const SRotationT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::SRotation_is_type< SRotationT >(),
            "SRotationT required to be a s-rotation class" );

        return st::SRotation_default_sin_z< typename
            st::SRotationTraits< SRotationT >::real_t >( elem );
    }

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >(),
        typename TypeMethodParamTraits< typename SRotationTraits<
            SRotationT >::real_t >::const_existing_type >::type
    SRotation_sin_z( SIXTRL_BE_ARGPTR_DEC const SRotationT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return elem->sin_z;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_set_sin_z(
        SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
        RealArg SIXTRL_UNUSED( sin_z_value ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename SRotationTraits< SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_set_sin_z( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
                         RealArg sin_z_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal<
            typename std::decay< RealArg >::type >( sin_z_value,
                typename std::decay< RealArg >::type{ -1 } ) );

        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal<
            typename std::decay< RealArg >::type >( sin_z_value,
                typename std::decay< RealArg >::type{ +1 } ) );

        elem->sin_z = sin_z_value;
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename SRotationTraits< SRotationT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename SRotationTraits< SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_set_sin_z( SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
                         RealArg sin_z_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal<
            typename std::decay< RealArg >::type >( sin_z_value,
                typename std::decay< RealArg >::type{ -1 } ) );

        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal<
            typename std::decay< RealArg >::type >( sin_z_value,
                typename std::decay< RealArg >::type{ +1 } ) );

        elem->sin_z = std::move( sin_z_value );
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class SRotationT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_impl_default< SRotationT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename SRotationTraits< SRotationT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename SRotationTraits< SRotationT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_set_sin_z( SIXTRL_BE_ARGPTR_DEC SRotationT*
        SIXTRL_RESTRICT elem, RealArg sin_z_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename st::SRotationTraits< SRotationT >::real_t dst_real_t;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< src_real_t >(
                            sin_z_value, src_real_t{ -1 } ) );

        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< src_real_t >(
                            sin_z_value, src_real_t{ +1 } ) );

        return st::Types_perform_assignment< src_real_t, dst_real_t >(
            elem->sin_z, sin_z_value );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
    SRotation_set_default_sin_z( SIXTRL_BE_ARGPTR_DEC SRotationT*
        SIXTRL_RESTRICT elem )
    {
        return SIXTRL_CXX_NAMESPACE::SRotation_set_sin_z( elem,
                    SIXTRL_CXX_NAMESPACE::SRotation_default_sin_z( elem ) );
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* cos_z: */

template< class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::SRotationTraits< SRotationT >::real_t
NS(SRotation_default_cos_z)( SIXTRL_BE_ARGPTR_DEC const SRotationT *const
    SIXTRL_RESTRICT elem = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_default_cos_z( elem );
}

template< class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::SRotationTraits< SRotationT >::real_t
        >::const_existing_type
NS(SRotation_cos_z)( SIXTRL_BE_ARGPTR_DEC const SRotationT
    *const SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_cos_z( elem );
}

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_set_cos_z)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg cos_z_value )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_set_cos_z( elem, cos_z_value );
}

template< class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_set_default_cos_z)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_set_default_cos_z( elem );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* sin_z: */

template< class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::SRotationTraits< SRotationT >::real_t
NS(SRotation_default_sin_z)( SIXTRL_BE_ARGPTR_DEC const SRotationT *const
    SIXTRL_RESTRICT elem = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_default_sin_z( elem );
}

template< class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::SRotationTraits< SRotationT >::real_t
        >::const_existing_type
NS(SRotation_sin_z)( SIXTRL_BE_ARGPTR_DEC const SRotationT
    *const SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_sin_z( elem );
}

template< class SRotationT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_set_sin_z)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem, RealArg sin_z_value )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_set_sin_z( elem, sin_z_value );
}

template< class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_set_default_sin_z)(
    SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_set_default_sin_z( elem );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ Host */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* cos_z: */

SIXTRL_STATIC SIXTRL_FN NS(be_real_t)
NS(SRotation_default_cos_z)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(SRotation_cos_z)( SIXTRL_BE_ARGPTR_DEC
    const NS(SRotation) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_set_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const cos_z_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_set_default_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* sin_z: */

SIXTRL_STATIC SIXTRL_FN NS(be_real_t)
NS(SRotation_default_sin_z)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(SRotation_sin_z)( SIXTRL_BE_ARGPTR_DEC
    const NS(SRotation) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_set_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const sin_z_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_set_default_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ Host */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* cos_z: */

SIXTRL_INLINE NS(be_real_t) NS(SRotation_default_cos_z)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(be_real_t) )1;
}

SIXTRL_INLINE NS(be_real_t) NS(SRotation_cos_z)( SIXTRL_BE_ARGPTR_DEC
    const NS(SRotation) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return elem->cos_z;
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_set_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const cos_z_value ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( cos_z_value >= ( NS(be_real_t) )-1 );
    SIXTRL_ASSERT( cos_z_value <= ( NS(be_real_t) )+1 );

    elem->cos_z = cos_z_value;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_set_default_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->cos_z = NS(SRotation_default_cos_z)();
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* sin_z: */

SIXTRL_INLINE NS(be_real_t) NS(SRotation_default_sin_z)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(be_real_t) )1;
}

SIXTRL_INLINE NS(be_real_t) NS(SRotation_sin_z)( SIXTRL_BE_ARGPTR_DEC
    const NS(SRotation) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return elem->sin_z;
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_set_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const sin_z_value ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( sin_z_value >= ( NS(be_real_t) )-1 );
    SIXTRL_ASSERT( sin_z_value <= ( NS(be_real_t) )+1 );

    elem->sin_z = sin_z_value;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_set_default_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->sin_z = NS(SRotation_default_sin_z)();
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_API_H__ */
