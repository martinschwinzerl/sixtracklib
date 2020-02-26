#ifndef SIXTRACKLIB_COMMON_COBJECTS_OBJ_DELEGATE_CXX_HPP__
#define SIXTRACKLIB_COMMON_COBJECTS_OBJ_DELEGATE_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
            #include <algorithm>
            #include <cstdlib>
            #include <stdint.h>
            #include <limits>
            #include <type_traits>

        #if !defined( _GPUCODE )
            #include <vector>
        #endif /* !defiend( _GPUCODE ) */
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/internal/obj_delegate.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class E >
    static SIXTRL_FN constexpr bool CObjElem_has_delegate_type() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_has_delegate_type<
            E, STORAGE_BE_COBJECTS >();
    }

    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_allow_delegate_storage() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_allow_delegate_storage<
            E, STORAGE_BE_COBJECTS >();
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN constexpr cobj_type_id_t
    CObjElem_delegate_type_id() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_delegate_type_id<
            E, STORAGE_BE_COBJECTS >();
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN cobj_status_t
    CObjElem_prepare_delegate(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC typename ObjDataDelegateTraits<
            E, STORAGE_BE_COBJECTS >::delegate_t*
                SIXTRL_RESTRICT delegate_obj,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const
            SIXTRL_RESTRICT ptr_elem ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return ( st::ObjData_prepare_delegate< E, STORAGE_BE_COBJECTS >(
            delegate_obj, ptr_elem ) == st::ARCH_STATUS_SUCCESS )
                ? st::COBJECTS_STATUS_SUCCESS
                : st::COBJECTS_STATUS_GENERAL_FAILURE;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN cobj_status_t CObjElem_store_delegate(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC typename ObjDataDelegateTraits<
            E, STORAGE_BE_COBJECTS >::delegate_t*
                SIXTRL_RESTRICT delegate_obj,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const
            SIXTRL_RESTRICT ptr_elem ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return ( st::ObjData_store_delegate< E, STORAGE_BE_COBJECTS >(
            delegate_obj, ptr_elem ) == st::ARCH_STATUS_SUCCESS )
                ? st::COBJECTS_STATUS_SUCCESS
                : st::COBJECTS_STATUS_GENERAL_FAILURE;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN cobj_status_t CObjElem_load_delegate(
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_elem,
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC const typename ObjDataDelegateTraits< E,
            STORAGE_BE_COBJECTS >::delegate_t *const
                SIXTRL_RESTRICT delegate_obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return ( st::ObjData_load_delegate< E, STORAGE_BE_COBJECTS >(
            ptr_elem, delegate_obj ) == st::ARCH_STATUS_SUCCESS )
                ? st::COBJECTS_STATUS_SUCCESS
                : st::COBJECTS_STATUS_GENERAL_FAILURE;
    }
}
#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_COBJECTS_OBJ_DELEGATE_CXX_HPP__ */
