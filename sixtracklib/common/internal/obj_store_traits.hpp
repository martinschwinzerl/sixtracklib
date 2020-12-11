#ifndef SIXTRACKLIB_COMMON_INTERNAL_OBJ_STORE_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_OBJ_STORE_TRAITS_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <cstdlib>
    #include <stdint.h>
    #include <limits>
    #include <type_traits>

    #if !defined( _GPUCODE )
        #include <vector>
    #endif /* !defiend( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/obj_type_id_traits.hpp"
    #include "sixtracklib/common/internal/obj_data_type_traits.hpp"
    #include "sixtracklib/common/internal/obj_illegal_type.h"

#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#endif /* __cplusplus */

typedef SIXTRL_UINT32_T NS(store_backend_t);

#if !defined( SIXTRL_STORAGE_BE_NONE )
    #define SIXTRL_STORAGE_BE_NONE 0u
#endif /* !defined( SIXTRL_STORAGE_BE_NONE ) */

#if !defined( SIXTRL_STORAGE_BE_COBJECTS )
    #define SIXTRL_STORAGE_BE_COBJECTS 1u
#endif /* !defined( SIXTRL_STORAGE_BE_COBJECTS ) */

#if !defined( SIXTRL_STORAGE_BE_ILLEGAL )
    #define SIXTRL_STORAGE_BE_ILLEGAL 0xffffffff
#endif /* !defined( SIXTRL_STORAGE_BE_ILLEGAL ) */

#if !defined( SIXTRL_STORAGE_BE_DEFAULT )
    #define SIXTRL_STORAGE_BE_DEFAULT SIXTRL_STORAGE_BE_NONE
#endif /* SIXTRL_STORAGE_BE_DEFAULT */

#if !defined( _GPUCODE )
    SIXTRL_STATIC_VAR NS(store_backend_t) const NS(STORAGE_BE_NONE) =
        ( NS(store_backend_t) )SIXTRL_STORAGE_BE_NONE;

    SIXTRL_STATIC_VAR NS(store_backend_t) const NS(STORAGE_BE_COBJECTS) =
        ( NS(store_backend_t) )SIXTRL_STORAGE_BE_COBJECTS;

    SIXTRL_STATIC_VAR NS(store_backend_t) const NS(STORAGE_BE_ILLEGAL) =
        ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL;

    SIXTRL_STATIC_VAR NS(store_backend_t) const NS(STORAGE_BE_DEFAULT) =
        ( NS(store_backend_t) ) SIXTRL_STORAGE_BE_DEFAULT;
#endif /* Host */

#if defined( __cplusplus )

/* ************************************************************************* */
/* Here we define and outline the metaprogramming framework handling
 * different storage options. The actual implementation is mostly
 * delegated to these different backends with only common predicates
 * and unspecialized traits and helper classes being defined here */
/* ************************************************************************* */

namespace SIXTRL_CXX_NAMESPACE
{
    /* ===================================================================== */
    /* Define some basic properties of ObjClass which hold true across
     * different storage backends: */

    /* --------------------------------------------------------------------- *
     * A) ObjData instances can be (safely) memcopied / mem-moved, with the
     * copy retaining the whole state of the instance
     * TODO: implement segway towards using bit_cast< starting with C++20! */

    template< class E >
    static SIXTRL_FN constexpr bool ObjData_can_be_memcopied() SIXTRL_NOEXCEPT
    {
        return !std::is_void< E >::value &&
               !SIXTRL_CXX_NAMESPACE::ObjData_is_specific_illegal_type< E >() &&
               std::is_trivially_copyable< E >::value &&
               std::is_standard_layout< E >::value;
    }

    /* ===================================================================== */
    /* Storage Type - we may support different modes of storage in the       */
    /*                so better be prepared. For the moment though, only
     *                CObjects based storage is supported */

    typedef ::NS(store_backend_t) store_backend_t;

    static constexpr store_backend_t STORAGE_BE_COBJECTS =
        static_cast< store_backend_t >( SIXTRL_STORAGE_BE_COBJECTS );

    static constexpr store_backend_t STORAGE_BE_ILLEGAL =
        static_cast< store_backend_t >( SIXTRL_STORAGE_BE_ILLEGAL );

    static constexpr store_backend_t STORAGE_BE_DEFAULT =
        static_cast< store_backend_t >( SIXTRL_STORAGE_BE_DEFAULT );

    template< store_backend_t StoreT >
    struct StorageBackendTraits
    {
        typedef int32_t type_id_t;
    };

    /* ********************************************************************* */

    template< class E, store_backend_t StoreT = STORAGE_BE_DEFAULT,
              typename Enabled = void >
    struct ObjDataInitialiser
    {
        SIXTRL_STATIC SIXTRL_FN void preset(
            SIXTRL_ARGPTR_DEC E* SIXTRL_RESTRICT /* obj */ ) SIXTRL_NOEXCEPT
        {
            return;
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_FN constexpr arch_status_t init(
            SIXTRL_ARGPTR_DEC E* SIXTRL_RESTRICT /* obj */,
            Args&&... /* args */ ) SIXTRL_NOEXCEPT
        {
            return ( StoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL )
                ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
                : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }
    };

    /* ===================================================================== */
    /* Direct storage means, that the storage backend can handle the
     * element just fine(TM) and needs no further input. Depending on the
     * backend, this can mean totally different things and is thus left to the
     * implementers of backends.
     *
     * Hence, we provide here only a generic template that refuses by default
     * all storage - override for different storage backends, as needed! */

    template< class ObjData, store_backend_t StoreT >
    struct ObjDataDirectStorageTraits
    {
        static SIXTRL_FN constexpr bool CanStore() SIXTRL_NOEXCEPT
        {
            return false;
        }
    };

    /* Provide a predicate for checking whether a given ObjData can be
     * stored in a given storage backend */

    template< class E, store_backend_t StoreT >
    static SIXTRL_FN constexpr
    bool ObjData_allow_direct_storage() SIXTRL_NOEXCEPT
    {
        return (
        ( StoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
        ( SIXTRL_CXX_NAMESPACE::ObjDataTypeId_is_legal< E,
                typename StorageBackendTraits< StoreT >::type_id_t >() ) &&
        ( !SIXTRL_CXX_NAMESPACE::ObjData_is_specific_illegal_type< E >() ) &&
        ( SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type< E >() ||
          SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >() ) );
    }
}

#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_STORE_TRAITS_CXX_HPP__ */
