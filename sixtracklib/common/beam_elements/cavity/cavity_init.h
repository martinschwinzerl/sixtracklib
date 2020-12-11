#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_INIT_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_INIT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/cavity.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_api.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT*
    Cavity_preset( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Cavity_is_type< CavityT >(),
            "CavityT required to be a cavity class" );

        if( elem != SIXTRL_NULLPTR )
        {
            st::arch_status_t const status =
                SIXTRL_CXX_NAMESPACE::Cavity_set_default_voltage( elem ) |
                SIXTRL_CXX_NAMESPACE::Cavity_set_default_frequency( elem ) |
                SIXTRL_CXX_NAMESPACE::Cavity_set_default_lag( elem );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        return elem;
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    Cavity_init( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
    {
        return SIXTRL_CXX_NAMESPACE::Cavity_set_default_voltage( elem ) |
               SIXTRL_CXX_NAMESPACE::Cavity_set_default_frequency( elem ) |
               SIXTRL_CXX_NAMESPACE::Cavity_set_default_lag( elem );
    }

    template< class CavityT, typename VoltageArg, typename FrequArg,
             typename LagArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    Cavity_init_detailed( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
        VoltageArg voltage, FrequArg frequency, LagArg lag )
    {
        return SIXTRL_CXX_NAMESPACE::Cavity_set_voltage( elem, voltage ) |
               SIXTRL_CXX_NAMESPACE::Cavity_set_frequency( elem, frequency ) |
               SIXTRL_CXX_NAMESPACE::Cavity_set_lag( elem, lag );
    }

    template< class CavityT, typename VoltageArg, typename FrequArg,
              typename LagArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    Cavity_init( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
        VoltageArg voltage, FrequArg frequency, LagArg lag )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::Cavity_init_detailed( elem, voltage, frequency, lag );
    }

    /* ********************************************************************* */

    template< class CavityT, store_backend_t StoreT >
    struct ObjDataInitialiser< CavityT, StoreT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(), void >::type >
    {
        SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT*  preset(
            SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Cavity_preset( obj );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t init(
            SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT obj,
            Args&&... init_args )
        {
            return SIXTRL_CXX_NAMESPACE::Cavity_init(
                obj, std::forward< Args >( init_args )... );
        }
    };
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT*
NS(Cavity_preset)( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_preset( elem );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_init)( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_init( elem );
}

template< class CavityT, typename VoltageArg, typename FrequArg,
         typename LagArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
    VoltageArg voltage, FrequArg frequency, LagArg lag )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_init_detailed(
        elem, voltage, frequency, lag );
}

template< class CavityT, typename VoltageArg, typename FrequArg,
          typename LagArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_init)( SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
    VoltageArg voltage, FrequArg frequency, LagArg lag )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_init_detailed(
        elem, voltage, frequency, lag );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Cavity)* NS(Cavity_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_init)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const voltage, NS(be_real_t) const frequency,
    NS(be_real_t) const lag ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */


SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Cavity)* NS(Cavity_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    if( elem != SIXTRL_NULLPTR )
    {
        NS(arch_status_t) const status =
            NS(Cavity_set_default_voltage)( elem ) |
            NS(Cavity_set_default_frequency)( elem ) |
            NS(Cavity_set_default_lag)( elem );

        SIXTRL_ASSERT( status == ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    return elem;
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_init)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return NS(Cavity_set_default_voltage)( elem ) |
           NS(Cavity_set_default_frequency)( elem ) |
           NS(Cavity_set_default_lag)( elem );
}

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const voltage, NS(be_real_t) const frequency,
    NS(be_real_t) const lag ) SIXTRL_NOEXCEPT
{
    return NS(Cavity_set_voltage)( elem, voltage ) |
           NS(Cavity_set_frequency)( elem, frequency ) |
           NS(Cavity_set_lag)( elem, lag );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_INIT_H__ */
