#ifndef SIXTRACKLIB_COMMON_COBJECTS_OBJ_CONVERT_CXX_HPP__
#define SIXTRACKLIB_COMMON_COBJECTS_OBJ_CONVERT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/internal/obj_convert.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

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

#endif /* SIXTRACKLIB_COMMON_COBJECTS_OBJ_CONVERT_CXX_HPP__ */
