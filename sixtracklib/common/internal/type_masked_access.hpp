#ifndef SIXTRACKLIB_COMMON_INTERNAL_TYPE_MASKED_ACCESS_H__
#define SIXTRACKLIB_COMMON_INTERNAL_TYPE_MASKED_ACCESS_H__

#if defined( __cplusplus )
#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstdlib>
    #include <stdint.h>
    #include <type_traits>

    #if !defined( _GPUCODE )
        #include <iterator>
        #include <string>
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename T >
    struct TypeMaskedArithmetic
    {
        typedef typename TypeMethodParamTraits<
                    T >::argument_type arg_type_t;

        typedef typename TypeCompLogicTypeTraits<
                    T >::logic_t     mask_t;

        typedef typename TypeMethodParamTraits<
                    logic_t >::const_argument_type mask_arg_t;

        template< typename ArgT >
        static SIXTRL_FN arch_status_t update_add(
            arg_type_t value, ArgT delta_value, mask_arg_t mask )
        {

        }

    };

    template< typename ValueT, typename ArgT >
    static SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Type_is_scalar< typename std::decay<
            ValueT >::type >() arch_status_t >::type
    Type_add_masked( ValueT value, ArgT arg,
        typename TypeMethodParamTraits< typename TypeCompLogicTypeTraits<
            typename std::decay< ValueT >::type >::logic_t
                >::const_argument_type mask )

}

#endif /* C++ */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_TYPE_MASKED_ACCESS_H__ */
