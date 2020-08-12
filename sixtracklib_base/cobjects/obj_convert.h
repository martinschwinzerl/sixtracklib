#ifndef SIXTRACKLIB_BASE_COBJECTS_OBJ_CONVERT_H__
#define SIXTRACKLIB_BASE_COBJECTS_OBJ_CONVERT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/definitions.h"
    #include "sixtracklib_base/internal/obj_convert.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class Source, class Dest >
    static SIXTRL_FN constexpr bool CObjElem_allow_conversion() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion< Source, Dest,
            STORAGE_BE_COBJECTS, STORAGE_BE_COBJECTS >();
    }

    template< class Source, class Dest >
    static SIXTRL_FN constexpr bool CObjElem_not_allow_conversion() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_not_allow_conversion< Source, Dest,
            STORAGE_BE_COBJECTS, STORAGE_BE_COBJECTS >();
    }
}

#endif /* C++ */
#endif /* SIXTRACKLIB_BASE_COBJECTS_OBJ_CONVERT_H__ */
