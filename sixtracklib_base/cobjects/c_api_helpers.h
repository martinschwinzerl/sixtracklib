#ifndef SIXTRACKLIB_BASE_COBJECTS_C_API_HELPRS_H__
#define SIXTRACKLIB_BASE_COBJECTS_C_API_HELPRS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/definitions.h"
    #include "sixtracklib_base/internal/obj_c_api_traits.h"
#endif /* SIXTRL_NO_INCLUDES */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <type_traits>
        #include <vector>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class E > static SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BUFFER_ARGPTR_DEC typename ObjDataCApiTypeTraits< E >::c_api_t const*
    CObjElem_as_const_ptr_c_api( SIXTRL_BUFFER_ARGPTR_DEC const
        E *const SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ObjDataCApiTypeTraits< E >::c_api_t _c_api_t;
        typedef SIXTRL_BUFFER_ARGPTR_DEC _c_api_t const* _ptr_c_api_t;

        return ( st::ObjData_has_equivalent_c_api_type< E >() )
            ? reinterpret_cast< _ptr_c_api_t >( ptr ) : nullptr;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BUFFER_ARGPTR_DEC typename ObjDataCApiTypeTraits< E >::c_api_t*
    CObjElem_as_ptr_c_api(
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ObjDataCApiTypeTraits< E >::c_api_t _c_api_t;
        typedef SIXTRL_BUFFER_ARGPTR_DEC _c_api_t* _ptr_c_api_t;

        return const_cast< _ptr_c_api_t >(
            st::CObjElem_as_const_ptr_c_api< E >( ptr ) );
    }

}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_BASE_COBJECTS_C_API_HELPRS_H__ */
