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
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#endif /* __cplusplus */

typedef SIXTRL_UINT32_T NS(store_backend_t);

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

    template< class ObjData >
    static SIXTRL_FN constexpr bool ObjData_can_be_memcopied() SIXTRL_NOEXCEPT
    {
        return ( ( !std::is_void< ObjData >::value ) &&
            (  std::is_trivially_copyable< ObjData >::value ) &&
            (  std::is_standard_layout< ObjData >::value ) );
    }

    /* ===================================================================== */
    /* Storage Type - we may support different modes of storage in the       */
    /*                so better be prepared. For the moment though, only
     *                CObjects based storage is supported */

    typedef ::NS(store_backend_t) store_backend_t;

    static constexpr store_backend_t STORAGE_BE_ILLEGAL =
        static_cast< store_backend_t >( 0xffffffff );

    template< store_backend_t StoreT >
    struct StorageBackendTraits
    {
        typedef int32_t type_id_t;
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

    template< class ObjData, store_backend_t StoreT >
    static SIXTRL_FN constexpr
    bool ObjData_allow_direct_storage() SIXTRL_NOEXCEPT
    {
        return (
            ( SIXTRL_CXX_NAMESPACE::ObjDataTypeId_is_legal< ObjData,
                typename StorageBackendTraits< StoreT >::type_id_t >() ) &&
            ( ObjDataDirectStorageTraits< ObjData, StoreT >::CanStore() ) );
    }

    /* ===================================================================== */
    /* For some storage types and ObjClass-es, it might not be possible to
     * directly store the ObjClass but a Delegate (i.e. a helper class that
     * can capture the whole state of ObjData in a way that is suitable for
     * storage on a given backend) might be available .
     *
     * Again, not only do suitable target class types for such a conversion
     * depend on the Storage backend, it's obviously also pretty dependent on
     * the ObjData -> hence we again leave this to the implementers of specific
     * ObjData / StoreT combinations*/

    template< class ObjData, store_backend_t StoreT >
    struct ObjDataDelegateStorageTraits
    {
        /* NOTE: The only thing that needs to be specialized is this type
         *       alias. We ensure ObjData and Delegate to allow direct
         *       storage. If ObjData == Delegate, this ensures that
         *       Delegates do not allow storage of types that can not
         *       be stored themselves. */

        typedef ObjData Delegate;
    };

    template< class ObjData, store_backend_t StoreT >
    static SIXTRL_FN constexpr bool
    ObjData_has_delegate_type_defined() SIXTRL_NOEXCEPT
    {
        return (
            ( !std::is_void< typename std::decay< ObjData >::type >::value ) &&
            ( !std::is_same<
                typename std::decay< typename ObjDataDelegateStorageTraits<
                    ObjData, StoreT >::Delegate >::type,
                typename std::decay< ObjData >::type >::value ) );
    }

    /* Provide a predicate for checking whether a given ObjData can be
     * stored via a delegate in a given storage backend;
     * NOTE: ObjData_allow_direct_storage<>() excludes
     *       ObjData_allow_delegate_storage<>(), i.e. they can not be
     *       true at the same time (but can both be false, obviously) */

    template< class ObjData, store_backend_t StoreT >
    static SIXTRL_FN constexpr
    bool ObjData_allow_delegate_storage() SIXTRL_NOEXCEPT
    {
        return (
            ( SIXTRL_CXX_NAMESPACE::ObjTypeId_is_legal< ObjData,
                    typename StorageBackendTraits< StoreT >::type_id_t >() ) &&
            ( !SIXTRL_CXX_NAMESPACE::ObjData_allow_direct_storage<
                    ObjData, StoreT >() ) &&
            (  SIXTRL_CXX_NAMESPACE::ObjData_has_delegate_type_defined<
                    ObjData, StoreT >() ) &&
            (  SIXTRL_CXX_NAMESPACE::ObjData_allow_direct_storage<
                    typename StorageBackendTraits< StoreT >::type_id_t,
                    StoreT >() ) );
    }

    /* For some storage backends, we have to prepare the delegate
     * before actually performing the conversion. While this can be
     * integrated into the FromDelegate / ToDelegate methods in the
     * ObjDataDelegateConverter below, it is possible for some
     * storage backends (again: CObjects) to pre-create this
     * prepare functions for a wide-range of cases. In order to
     * avoid the needless creation of boilerplate code in the specialization
     * of ObjDataDelegateConverter, we split the preparation out into the
     * following class;
     * NOTE the _Enabled typedef, preparing for SFINAE assisted
     *          specialization! */

    template< class ObjData, store_backend_t StoreT, typename _Enabled = void >
    struct ObjDataDelegatePrepareConvToDelegate
    {
        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        Prepare( typename ObjDataDelegateStorageTraits<
            ObjData, StoreT >::Delegate* SIXTRL_RESTRICT ptr_destination,
            const ObjData *const SIXTRL_RESTRICT ptr_source )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            static_assert( st::ObjData_has_delegate_type_defined<
                ObjData, StoreT >(), "Only works for Delegated Types!" );

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( ptr_destination != nullptr ) && ( ptr_source != nullptr ) )
            {
                /* Actually perform the conversion in your specialized
                 * implementation! */

                /* ptr_source ........ ObjData, original element */
                /* ptr_destination ... Delegate, to be stored */

                status = st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }
    };

    /* In order to go from a type to it's delegate or back again,
     * we have to provide a "converter". In order for this to work,
     * it is crucial to specialize this struct for each pair of
     * ObjData, Delegate. It depends on the storage backend even
     * though would not need to, for consistency reasons */

    template< class ObjData, store_backend_t StoreT >
    struct ObjDataDelegateConverter
    {
        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        ToDelegate( typename ObjDataDelegateStorageTraits<
            ObjData, StoreT >::Delegate* SIXTRL_RESTRICT ptr_destination,
            const ObjData *const SIXTRL_RESTRICT ptr_source )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            static_assert( st::ObjData_has_delegate_type_defined<
                ObjData, StoreT >(), "Only works for Delegated Types!" );

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( ptr_destination != nullptr ) && ( ptr_source != nullptr ) )
            {
                /* Actually perform the conversion in your specialized
                 * implementation! */

                /* ptr_source ........ ObjData, original element */
                /* ptr_destination ... Delegate, to be stored */

                status = st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }

        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        FromDelegate( ObjData* SIXTRL_RESTRICT ptr_destination,
            const typename ObjDataDelegateStorageTraits<
                ObjData, StoreT >::Delegate *const SIXTRL_RESTRICT ptr_source )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            static_assert( st::ObjData_has_delegate_type_defined<
                ObjData, StoreT >(), "Only works for Delegated Types!" );

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( ptr_destination != nullptr ) && ( ptr_source != nullptr ) )
            {
                /* Actually perform the conversion in your specialized
                 * implementation! */

                /* ptr_destination ... ObjData, to be restored from data */
                /* ptr_source ........ Delegate, stored element */

                status = st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }
    };

    /* -------------------------------------------------------------------- */
}

#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_STORE_TRAITS_CXX_HPP__ */
