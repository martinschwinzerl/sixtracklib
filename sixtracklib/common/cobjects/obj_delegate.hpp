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
    #include "sixtracklib/common/cobjects/element_traits.hpp"
    #include "sixtracklib/common/internal/obj_delegate.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class E >
    static SIXTRL_FN constexpr bool CObjElem_has_delegate_type() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_has_delegate<
                    E, SIXTRL_CXX_NAMESPACE::STORAGE_BE_COBJECTS >();

    }

    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_allow_delegate_storage() SIXTRL_NOEXCEPT
    {
        return !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
                SIXTRL_CXX_NAMESPACE::CObjElem_has_delegate_type< E >() &&
                SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage<
                   typename SIXTRL_CXX_NAMESPACE::ObjDataDelegateTraits<
                       E, SIXTRL_CXX_NAMESPACE::STORAGE_BE_COBJECTS
                           >::delegate_t >();
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class E >
    static SIXTRL_FN constexpr typename std::enable_if<
        !CObjElem_allow_delegate_storage< E >(), cobj_type_id_t >::type
    CObjElem_delegate_type_id() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
            cobj_type_id_t >();
    }

    template< class E >
    static SIXTRL_FN constexpr typename std::enable_if<
        CObjElem_allow_delegate_storage< E >(), cobj_type_id_t >::type
    CObjElem_delegate_type_id() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_type_id< E >();
    }
}
#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_COBJECTS_OBJ_DELEGATE_CXX_HPP__ */
