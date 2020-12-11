#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_INIT_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_INIT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/drift_api.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftT*
    Drift_preset( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        if( elem != SIXTRL_NULLPTR )
        {
            st::arch_status_t status = st::Drift_set_default_length( elem );
            status |= st::Drift_set_default_track_type( elem );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        return elem;
    }

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t Drift_init(
        SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem )
    {
        return SIXTRL_CXX_NAMESPACE::Drift_set_default_length( elem ) |
               SIXTRL_CXX_NAMESPACE::Drift_set_default_track_type( elem );
    }

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t Drift_init_detailed(
        SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
        RealArg length, be_drift_track_type_t const track_type =
            SIXTRL_CXX_NAMESPACE::BE_DRIFT_TRACK_TYPE_SIMPLE )
    {
        return SIXTRL_CXX_NAMESPACE::Drift_set_length( elem, length ) |
               SIXTRL_CXX_NAMESPACE::Drift_set_track_type( elem, track_type );
    }

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t Drift_init(
        SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
        RealArg length, be_drift_track_type_t const track_type =
            SIXTRL_CXX_NAMESPACE::BE_DRIFT_TRACK_TYPE_SIMPLE )
    {
        return SIXTRL_CXX_NAMESPACE::Drift_init_detailed(
            elem, length, track_type );
    }

} /* namespace: SIXTRL_CXX_NAMESPACE */

 template< class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftT*
NS(Drift_preset)( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Drift_preset( elem );
}

template< class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Drift_init)( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Drift_init( elem );
}

template< class DriftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Drift_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem, RealArg length,
    SIXTRL_CXX_NAMESPACE::be_drift_track_type_t const track_type =
        SIXTRL_CXX_NAMESPACE::BE_DRIFT_TRACK_TYPE_SIMPLE )
{
    return SIXTRL_CXX_NAMESPACE::Drift_init_detailed(
        elem, length, track_type );
}

template< class DriftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Drift_init)( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
    RealArg length, SIXTRL_CXX_NAMESPACE::be_drift_track_type_t const
        track_type = SIXTRL_CXX_NAMESPACE::BE_DRIFT_TRACK_TYPE_SIMPLE )
{
    return SIXTRL_CXX_NAMESPACE::Drift_init_detailed(
        elem, length, track_type );
}

#endif /* C++ */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/beam_elements/drift/drift.hpp"
    #include "sixtracklib/common/beam_elements/drift/drift_api.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* ********************************************************************* */
    /* ::NS(Drift) */

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataInitialiser< ::NS(Drift), StoreT >
    {
        SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC ::NS(Drift)* preset(
            SIXTRL_BE_ARGPTR_DEC ::NS(Drift)* SIXTRL_RESTRICT obj
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Drift_preset( obj );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t init(
            SIXTRL_BE_ARGPTR_DEC ::NS(Drift)* SIXTRL_RESTRICT obj,
            Args&&... init_args )
        {
            return SIXTRL_CXX_NAMESPACE::Drift_init(
                obj, std::forward< Args >( init_args )... );
        }
    };

    /* ********************************************************************* */
    /* ::NS(Drift) */

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataInitialiser<
        SIXTRL_CXX_NAMESPACE::TDrift< R, RAlign >, StoreT >
    {
        SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC
            SIXTRL_CXX_NAMESPACE::TDrift< R, RAlign >*
        preset( SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::TDrift< R, RAlign >*
                SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Drift_preset( obj );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        init( SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::TDrift<
            R, RAlign >* SIXTRL_RESTRICT obj, Args&&... init_args )
        {
            return SIXTRL_CXX_NAMESPACE::Drift_init(
                obj, std::forward< Args >( init_args )... );
        }
    };

} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Drift_init)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Drift_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const length,
    NS(be_drift_track_type_t) const track_type ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    if( elem != SIXTRL_NULLPTR )
    {
        NS(arch_status_t) status = NS(Drift_set_default_length)( elem );
        status |= NS(Drift_set_default_track_type)( elem );

        SIXTRL_ASSERT( status == ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    return elem;
}

SIXTRL_INLINE NS(arch_status_t) NS(Drift_init)( SIXTRL_BE_ARGPTR_DEC NS(Drift)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return NS(Drift_set_default_length)( elem );
}

SIXTRL_INLINE NS(arch_status_t) NS(Drift_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const length,
    NS(be_drift_track_type_t) const track_type ) SIXTRL_NOEXCEPT
{
    return NS(Drift_set_length)( elem, length ) |
           NS(Drift_set_track_type)( elem, track_type );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_INIT_H__ */
