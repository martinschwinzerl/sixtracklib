#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DEFINITIONS_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DEFINITIONS_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"

    #if !defined( __cplusplus )
        #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
        #include "sixtracklib/common/internal/obj_data_type_traits.hpp"
        #include "sixtracklib/common/internal/type_store_traits.hpp"
    #endif /* !defined( __cplusplus ) */

#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
extern "C" {
#endif /* C++, Host  */

typedef SIXTRL_REAL_T   NS(be_real_t);
typedef SIXTRL_INT64_T  NS(be_order_t);
typedef SIXTRL_UINT64_T NS(be_address_t);

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
}
#endif /* C++, Host  */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(be_real_t)     be_real_t;
    typedef ::NS(be_order_t)    be_order_t;
    typedef ::NS(be_address_t)  be_address_t;
}

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DEFINITIONS_C99_H__ */
