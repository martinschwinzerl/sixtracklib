#ifndef SIXTRACKLIB_COMMON_INTERNAL_OBJ_ILLEGAL_TYPE_H__
#define SIXTRACKLIB_COMMON_INTERNAL_OBJ_ILLEGAL_TYPE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    struct IllegalType{};

    template< class E >
    static SIXTRL_FN constexpr bool
    ObjData_is_specific_illegal_type() SIXTRL_NOEXCEPT
    {
        return std::is_same< typename std::decay< E >::type,
                             IllegalType >::value;
    }
}

#if !defined( _GPUCODE )
extern "C" {
#endif /* !defined( _GPUCODE ) */

typedef SIXTRL_CXX_NAMESPACE::IllegalType NS(IllegalType);

#if !defined( _GPUCODE )
}
#endif /* !defined( _GPUCODE ) */

#else /* defined( __cplusplus ) */

struct NS(IllegalType);

#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_ILLEGAL_TYPE_H__ */
