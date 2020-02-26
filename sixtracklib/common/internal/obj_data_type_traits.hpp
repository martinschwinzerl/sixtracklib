#ifndef SIXTRACKLIB_COMMON_INTERNAL_OBJ_DATA_TYPE_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_OBJ_DATA_TYPE_TRAITS_CXX_HPP__

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
    #include "sixtracklib/common/internal/obj_type_id_traits.hpp"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/obj_illegal_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    /* Define a mapping of a TypeId to a type */

    template< typename TypeIdT, TypeIdT type_id >
    struct ObjTypeIdDataTypeMap
    {
        typedef IllegalType value_type;
    };

    /* --------------------------------------------------------------------- */

    template< typename TypeIdT, TypeIdT type_id >
    static SIXTRL_FN constexpr bool
    ObjData_has_type_for_type_id() SIXTRL_NOEXCEPT
    {
        return
        ( SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
            TypeIdT >() != type_id ) &&
        ( !std::is_void< typename ObjTypeIdDataTypeMap< TypeIdT,
            type_id >::value_type >::value ) &&
        ( !SIXTRL_CXX_NAMESPACE::ObjData_is_specific_illegal_type<
            typename ObjTypeIdDataTypeMap< TypeIdT, type_id >::value_type >() );
    }

    /* ===================================================================== */
    /* Base TypeId traits -> this type determines the "function" of an
     * element; elements with the same base-type are supposed to be inter-
     * changable function wise (i.e. if used as backends to the Impl Facade */

    template< class E, typename TypeIdT, typename _Enabled = void >
    struct ObjDataTypeIdTraits
    {
        static SIXTRL_FN constexpr TypeIdT TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id< TypeIdT>();
        }
    };

    template< class E, typename TypeIdT >
    struct ObjDataTypeIdTraits< E, TypeIdT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >() >::type >
    {
        static SIXTRL_FN constexpr TypeIdT TypeId() SIXTRL_NOEXCEPT
        {
            return ObjDataTypeIdTraits< typename ObjDataCApiTypeTraits<
                E >::c_api_t, TypeIdT >::TypeId();
        }
    };

    /* --------------------------------------------------------------------- */
    /* Define some helper predicates and functions to work with these traits */

    template< class E, typename TypeIdT >
    static SIXTRL_FN constexpr TypeIdT ObjData_type_id() SIXTRL_NOEXCEPT
    {
        return ObjDataTypeIdTraits< E, TypeIdT >::TypeId();
    }

    template< class E, typename TypeIdT >
    static SIXTRL_FN constexpr bool ObjDataTypeId_is_illegal() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjTypeId_is_illegal< TypeIdT,
               SIXTRL_CXX_NAMESPACE::ObjData_type_id< E, TypeIdT >() >();
    }

    template< class E, typename TypeIdT >
    static SIXTRL_FN constexpr bool ObjDataTypeId_is_legal() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjTypeId_is_legal< TypeIdT,
               SIXTRL_CXX_NAMESPACE::ObjData_type_id< E, TypeIdT >() >();
    }

    /* --------------------------------------------------------------------- */

    template< class E, typename TypeIdT >
    static SIXTRL_FN constexpr bool ObjDataTypeId_is_variant() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjTypeId_is_variant< TypeIdT,
               SIXTRL_CXX_NAMESPACE::ObjData_type_id< E, TypeIdT >() >();
    }

    template< class E, typename TypeIdT >
    static SIXTRL_FN constexpr TypeIdT ObjDataTypeId_variant() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjTypeId_variant< TypeIdT,
               SIXTRL_CXX_NAMESPACE::ObjData_type_id< E, TypeIdT >() >();
    }

    template< class E, typename TypeIdT, TypeIdT variant >
    static SIXTRL_FN constexpr TypeIdT
    ObjDataTypeId_add_variant() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjTypeId_add_variant< TypeIdT,
                SIXTRL_CXX_NAMESPACE::ObjData_type_id< E, TypeIdT >(),
                    variant >();
    }

    template< class E, typename TypeIdT >
    static SIXTRL_INLINE SIXTRL_FN TypeIdT ObjDataTypeId_add_variant(
        TypeIdT const variant ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjTypeId_add_variant(
            SIXTRL_CXX_NAMESPACE::ObjData_type_id< E >(), variant );
    }

    template< class E, typename TypeIdT >
    static SIXTRL_FN constexpr TypeIdT
        ObjDataTypeId_remove_variant() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjTypeId_remove_variant< TypeIdT,
            SIXTRL_CXX_NAMESPACE::ObjData_type_id< E, TypeIdT >() >();
    }

    template< class E, typename TypeIdT >
    static SIXTRL_FN constexpr bool
    ObjData_type_traits_consistent() SIXTRL_NOEXCEPT
    {
        return ( SIXTRL_CXX_NAMESPACE::ObjTypeId_is_illegal<
            SIXTRL_CXX_NAMESPACE::ObjData_type_id< E, TypeIdT >() >() ) ||
        ( ( !std::is_void< E >::value ) &&
          ( SIXTRL_CXX_NAMESPACE::ObjData_has_type_for_type_id< E, TypeIdT >() ) &&
          ( std::is_same< typename ObjTypeIdDataTypeMap< TypeIdT,
                SIXTRL_CXX_NAMESPACE::ObjData_type_id<
                    E, TypeIdT >() >::value_type, E >::value ) );
    }
}

#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_DATA_TYPE_TRAITS_CXX_HPP__ */
