#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_API_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* --------------------------------------------------------------------- */
    /* length */

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
        SIXTRL_CXX_NAMESPACE::be_real_t >::type
    Drift_default_length( SIXTRL_BE_ARGPTR_DEC const DriftT *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( elem ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::be_real_t{ 0 };
    }

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
        typename TypeMethodParamTraits< typename DriftTraits<
            DriftT >::real_t >::value_type >::type
    Drift_default_length( SIXTRL_BE_ARGPTR_DEC const DriftT *const
        SIXTRL_RESTRICT /*elem*/ = SIXTRL_NULLPTR )
    {
        return typename TypeMethodParamTraits< typename DriftTraits< DriftT
            >::real_t >::value_type{ 0 };
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
        SIXTRL_CXX_NAMESPACE::be_real_t >::type
    Drift_length( SIXTRL_BE_ARGPTR_DEC const DriftT *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( elem ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Drift_default_length< DriftT >();
    }

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
        typename TypeMethodParamTraits< typename DriftTraits<
            DriftT >::real_t >::const_existing_type >::type
    Drift_length( SIXTRL_BE_ARGPTR_DEC const DriftT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return elem->length;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_set_length(
        SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
        RealArg SIXTRL_UNUSED( length ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< RealArg,
            typename DriftTraits< DriftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_set_length( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
                      RealArg length )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->length = length;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< RealArg,
            typename DriftTraits< DriftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_set_length( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
                      RealArg length )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->length = std::move( length );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >() &&
        ( !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< RealArg,
                typename DriftTraits< DriftT >::real_t >() &&
          !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< RealArg,
                typename DriftTraits< DriftT >::real_t >() ),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_set_length( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
                      RealArg length )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename DriftTraits< DriftT >::real_t dst_real_t;

        if( elem != SIXTRL_NULLPTR )
        {
            status = st::Types_perform_assignment< src_real_t, dst_real_t >(
                elem->length, length );
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    Drift_set_default_length( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::Drift_set_length( elem, st::Drift_default_length( elem ) );
    }

    /* --------------------------------------------------------------------- */
    /* track_type */

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_CXX_NAMESPACE::be_drift_track_type_t
    Drift_default_track_type( SIXTRL_BE_ARGPTR_DEC const DriftT *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( elem ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::BE_DRIFT_TRACK_TYPE_DEFAULT;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
        SIXTRL_CXX_NAMESPACE::be_drift_track_type_t >::type
    Drift_track_type( SIXTRL_BE_ARGPTR_DEC const DriftT *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( elem ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::BE_DRIFT_TRACK_TYPE_DEFAULT;
    }

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
        SIXTRL_CXX_NAMESPACE::be_drift_track_type_t >::type
    Drift_track_type( SIXTRL_BE_ARGPTR_DEC const DriftT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return elem->track_type;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_set_track_type(
        SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
        SIXTRL_CXX_NAMESPACE::be_drift_track_type_t const SIXTRL_UNUSED(
            track_type ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_set_track_type( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
        SIXTRL_CXX_NAMESPACE::be_drift_track_type_t
            const track_type ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( elem != SIXTRL_NULLPTR ) &&
            ( ( track_type == st::BE_DRIFT_TRACK_TYPE_SIMPLE  ) ||
              ( track_type == st::BE_DRIFT_TRACK_TYPE_EXACT   ) ||
              ( track_type == st::BE_DRIFT_TRACK_TYPE_NONE    ) ||
              ( track_type == st::BE_DRIFT_TRACK_TYPE_ILLEGAL ) ) )
        {
            elem->track_type = track_type;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    Drift_set_default_track_type(
        SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::Drift_set_track_type(
                    elem, st::Drift_default_track_type( elem ) );
    }
}

/* ------------------------------------------------------------------------- */
/* length */

template< class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::be_real_t
NS(Drift_default_length)( SIXTRL_BE_ARGPTR_DEC const DriftT *const
    SIXTRL_RESTRICT elem = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_default_length( elem );
}

template< class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::DriftTraits< DriftT >::real_t >::const_existing_type
NS(Drift_length)( SIXTRL_BE_ARGPTR_DEC const DriftT *const
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_length( elem );
}

template< class DriftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Drift_set_length)( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
                      RealArg length )
{
    return SIXTRL_CXX_NAMESPACE::Drift_set_length( elem, length );
}

template< class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Drift_set_default_length)(
    SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Drift_set_default_length( elem );
}

/* ------------------------------------------------------------------------- */
/* track_type */

template< class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_CXX_NAMESPACE::be_drift_track_type_t
NS(Drift_default_track_type)( SIXTRL_BE_ARGPTR_DEC const DriftT *const
    SIXTRL_RESTRICT elem = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_default_track_type( elem );;
}

template< class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_CXX_NAMESPACE::be_drift_track_type_t
NS(Drift_track_type)( SIXTRL_BE_ARGPTR_DEC const DriftT *const
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_track_type( elem );
}

template< class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Drift_set_track_type)(
    SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
    SIXTRL_CXX_NAMESPACE::be_drift_track_type_t
        const track_type ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_set_track_type( elem, track_type );
}

template< class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Drift_set_default_track_type)(
    SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Drift_set_default_length( elem );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* ------------------------------------------------------------------------- */
/* length */

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(Drift_default_length)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(Drift_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Drift_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const length ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Drift_set_default_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* track_type */

SIXTRL_STATIC SIXTRL_FN NS(be_drift_track_type_t)
NS(Drift_default_track_type)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_drift_track_type_t) NS(Drift_track_type)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Drift_set_track_type)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem,
    NS(be_drift_track_type_t) const track_type ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Drift_set_default_track_type)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* ------------------------------------------------------------------------- */
/* length */

SIXTRL_INLINE NS(be_real_t) NS(Drift_default_length)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(be_real_t) )0;
}

SIXTRL_INLINE NS(be_real_t) NS(Drift_length)( SIXTRL_BE_ARGPTR_DEC const
    NS(Drift) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return elem->length;
}

SIXTRL_INLINE NS(arch_status_t) NS(Drift_set_length)( SIXTRL_BE_ARGPTR_DEC
    NS(Drift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const length ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->length = length;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Drift_set_default_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return NS(Drift_set_length)( elem, NS(Drift_default_length)() );
}

/* ------------------------------------------------------------------------- */
/* track_type */

SIXTRL_INLINE NS(be_drift_track_type_t) NS(Drift_default_track_type)(
    void ) SIXTRL_NOEXCEPT
{
    return ( NS(be_drift_track_type_t) )SIXTRL_BE_DRIFT_TRACK_TYPE_DEFAULT;
}

SIXTRL_INLINE NS(be_drift_track_type_t) NS(Drift_track_type)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return elem->track_type;
}

SIXTRL_INLINE NS(arch_status_t) NS(Drift_set_track_type)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem,
    NS(be_drift_track_type_t) const track_type ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( elem != SIXTRL_NULLPTR ) &&
        ( ( track_type == ( NS(be_drift_track_type_t)
                )SIXTRL_BE_DRIFT_TRACK_TYPE_SIMPLE ) ||
          ( track_type == ( NS(be_drift_track_type_t)
                )SIXTRL_BE_DRIFT_TRACK_TYPE_EXACT ) ||
          ( track_type == ( NS(be_drift_track_type_t)
                )SIXTRL_BE_DRIFT_TRACK_TYPE_NONE ) ||
          ( track_type == ( NS(be_drift_track_type_t)
                )SIXTRL_BE_DRIFT_TRACK_TYPE_ILLEGAL ) ) )
    {
        elem->track_type = track_type;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(Drift_set_default_track_type)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)*
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return NS(Drift_set_track_type)( elem, NS(Drift_default_track_type)() );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_API_H__ */
