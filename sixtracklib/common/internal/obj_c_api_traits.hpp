#ifndef SIXTRACKLIB_COMMON_INTERNAL_OBJ_C_API_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_OBJ_C_API_TRAITS_CXX_HPP__

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <cstdlib>
    #include <limits>
    #include <type_traits>

    #if !defined( _GPUCODE )
        #include <vector>
    #endif /* !defiend( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    /* --------------------------------------------------------------------- */
    /* Provide a predicate to check whether a given ObjData is itself a
     * suitable C-API type: */

    template< class E >
    static SIXTRL_FN constexpr bool ObjData_is_c_api_type() SIXTRL_NOEXCEPT
    {
        return (
            ( !std::is_void< typename std::decay< E >::type >::value ) &&
            (  std::is_trivial< typename std::decay< E >::type >::value ) &&
            (  std::is_standard_layout<
                    typename std::decay< E >::type >::value ) );
    }

    template< class ObjData >
    static SIXTRL_FN constexpr bool ObjData_is_not_c_api_type() SIXTRL_NOEXCEPT
    {
        return !SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type< ObjData >();
    }

    /* --------------------------------------------------------------------- */
    /* We distinguish between the fully templated C++ API and the C API
     * for elements / objects. Some internal combination of template params for
     * ObjData can lead to an internal representation which can safely be
     * reinterpreted as the C-API structs. This is quite helpful if one wants
     * to pass instances of C++ objects to API working with the C structs.
     *
     * We provide some infrastructore to safely mark those ObjClass classes
     * that can work in such a context */

    /* By default, we do not assume a proper C-API mapping. Having void as
     * a C-API pointer is actually rather convenient */

    template< class ObjData >
    struct ObjDataCApiTypeTraits
    {
        typedef void c_api_t;
    };

    /* --------------------------------------------------------------------- */
    /* Provide predicates to handle C-API related questions */

    template< class ObjData >
    static SIXTRL_FN constexpr bool ObjData_has_c_api_type() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type< typename
                ObjDataCApiTypeTraits< ObjData >::c_api_t >();
    }

    template< class E >
    static SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type<
            typename ObjDataCApiTypeTraits< E >::c_api_t >(),
        SIXTRL_CXX_NAMESPACE::arch_size_t >::type
    ObjData_sizeof_c_api_type(
        const E *const /* ptr */ = nullptr ) SIXTRL_NOEXCEPT
    {
        return sizeof( typename ObjDataCApiTypeTraits< E >::c_api_t );
    }

    template< class E >
    static SIXTRL_FN constexpr typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type<
            typename ObjDataCApiTypeTraits< E >::c_api_t >(),
        SIXTRL_CXX_NAMESPACE::arch_size_t >::type
    ObjData_sizeof_c_api_type(
        const E *const /* ptr */ = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::arch_size_t{ 0 };
    }

    template< class E >
    static SIXTRL_FN constexpr bool
    ObjData_can_have_equivalent_c_api_type() SIXTRL_NOEXCEPT
    {
        return
           !std::is_void< typename std::decay< E >::type >::value &&
            std::is_standard_layout< typename std::decay< E >::type >::value &&
            std::is_trivially_copyable< typename std::decay< E >::type>::value;
    }

    template< class E, class CApiT >
    static SIXTRL_FN constexpr bool
    ObjData_can_be_equivalent_to_c_api_type() SIXTRL_NOEXCEPT
    {
        return
        SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type< CApiT >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_can_have_equivalent_c_api_type< E >() &&
        ( sizeof( E ) == sizeof( CApiT ) ) &&
        ( SIXTRL_CXX_NAMESPACE::Type_storage_align< E >() ==
          SIXTRL_CXX_NAMESPACE::Type_storage_align< CApiT >() );
    }


    template< class E >
    static SIXTRL_FN constexpr bool
    ObjData_has_equivalent_c_api_type() SIXTRL_NOEXCEPT
    {
        return
            ( SIXTRL_CXX_NAMESPACE::ObjData_can_have_equivalent_c_api_type<
                E >() ) &&
            ( SIXTRL_CXX_NAMESPACE::ObjData_sizeof_c_api_type< E >() >
              SIXTRL_CXX_NAMESPACE::arch_size_t{ 0 } ) &&
            ( SIXTRL_CXX_NAMESPACE::ObjData_sizeof_c_api_type< E >() ==
              sizeof( E ) ) &&
            ( !std::is_same< typename std::decay< E >::type,
                typename ObjDataCApiTypeTraits< typename std::decay< E
                    >::type >::c_api_t >::value );
    }

    template< class ObjData > static SIXTRL_FN constexpr bool
    ObjData_can_bitcast_to_c_api() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type<
            ObjData >();
    }

    /* --------------------------------------------------------------------- */
    /* Provide functions that can "bit_cast" an ObjData pointer to/from a
     * c_api pointer *iff* the type supports this behaviour.
     *
     * NOTE: casting between pointers incurs restrictions due to alising
     *       rules, this implementation is most likely not correct ->
     *       comments and feedback welcome! */

    template< class ObjData >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< ObjData >(),
        void const* >::type ObjData_bitcast_to_const_c_api( const ObjData
            *const SIXTRL_RESTRICT /* ptr_obj */ ) SIXTRL_NOEXCEPT
    {
        return nullptr;
    }

    template< class ObjData >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< ObjData >(),
        ObjData const* >::type ObjData_bitcast_from_const_c_api(
            void const* SIXTRL_RESTRICT /* ptr_c_api_obj */ ) SIXTRL_NOEXCEPT
    {
        return nullptr;
    }


    template< class ObjData >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< ObjData >(),
        typename ObjDataCApiTypeTraits< ObjData >::c_api_t const* >::type
    ObjData_bitcast_to_const_c_api(
        const ObjData *const SIXTRL_RESTRICT ptr_obj ) SIXTRL_NOEXCEPT
    {
        typedef typename ObjDataCApiTypeTraits< ObjData >::c_api_t const*
                _ptr_c_api_t;

        return reinterpret_cast< _ptr_c_api_t >( reinterpret_cast< uintptr_t
            >( ptr_obj ) );
    }

    template< class ObjData >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< ObjData >(),
        ObjData const* >::type ObjData_bitcast_from_const_c_api(
            typename ObjDataCApiTypeTraits< ObjData >::c_api_t const*
                SIXTRL_RESTRICT ptr_c_api_obj ) SIXTRL_NOEXCEPT
    {
        typedef ObjData const* _ptr_cxx_api_t;

        return reinterpret_cast< _ptr_cxx_api_t >( reinterpret_cast< uintptr_t
            >( ptr_c_api_obj ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class ObjData >
    static SIXTRL_INLINE SIXTRL_FN
        typename ObjDataCApiTypeTraits< ObjData >::c_api_t*
    ObjData_bitcast_to_c_api( ObjData* SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::ObjDataCApiTypeTraits< ObjData > _traits_t;
        typedef typename _traits_t::c_api_t _c_api_t;

        return const_cast< _c_api_t* >( st::ObjData_bitcast_to_const_c_api<
            ObjData >( ptr ) );
    }

    template< class ObjData >
    static SIXTRL_INLINE SIXTRL_FN ObjData*
    ObjData_bitcast_from_c_api( typename ObjDataCApiTypeTraits<
        ObjData >::c_api_t* SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return const_cast< ObjData* >(
            st::ObjData_bitcast_from_const_c_api< ObjData >( ptr ) );
    }
}

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_C_API_TRAITS_CXX_HPP__ */
