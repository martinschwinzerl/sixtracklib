#ifndef SIXTRACKLIB_COMMON_COBJECTS_C_API_HELPERS_CXX_HPP__
#define SIXTRACKLIB_COMMON_COBJECTS_C_API_HELPERS_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
#endif /* SIXTRL_NO_INCLUDES */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #if !defined( _GPUCODE )
            #include <algorithm>
            #include <vector>
        #endif /* !defined( _GPUCODE ) */
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class E >
    static SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_ARGPTR_DEC
        typename ObjDataCApiTypeTraits< E >::c_api_type const*
    CObjElem_as_const_ptr_c_api( SIXTRL_BUFFER_ARGPTR_DEC const E *const
        SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT {
        return ( SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >() )
            ? reinterpret_cast< SIXTRL_BUFFER_ARGPTR_DEC
                typename ObjDataCApiTypeTraits< E >::c_api_type const* >( ptr )
            : nullptr; }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_ARGPTR_DEC
        typename ObjDataCApiTypeTraits< E >::c_api_type*
    CObjElem_as_ptr_c_api( SIXTRL_BUFFER_ARGPTR_DEC E*
        SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT {
        return const_cast< SIXTRL_BUFFER_ARGPTR_DEC typename
            ObjDataCApiTypeTraits< E >::c_api_type* >(
                SIXTRL_CXX_NAMESPACE::CObjElem_as_const_ptr_c_api< E >( ptr ) );
    }

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_COBJECTS_C_API_HELPERS_CXX_HPP__ */
