#ifndef SIXTRACKLIB_OPENCL_INTERNAL_SUCCESS_FLAG_H__
#define SIXTRACKLIB_OPENCL_INTERNAL_SUCCESS_FLAG_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __OPENCL_VERSION__ )

    #if defined( cl_khr_int64_extended_atomics )
        #pragma OPENCL EXTENSION cl_khr_int64_extended_atomics : enable
    #endif /* cl_khr_int64_extended_atomics */

    SIXTRL_STATIC SIXTRL_DEVICE_FN
    void NS(OpenCl1x_collect_status_flag_value)(
        SIXTRL_DATAPTR_DEC NS(arch_debugging_t)* SIXTRL_RESTRICT ptr_status_flag,
        NS(arch_debugging_t) const local_status_flag )
    {
        if( ( ptr_success_flag   != SIXTRL_NULLPTR ) &&
            ( local_success_flag != ( NS(arch_debugging_t) )0u ) )
        {
            #if  defined( cl_khr_int64_extended_atomics )

                atom_or( ptr_success_flag, local_success_flag );

            #else /* No atomics available -> or-ing bit-flags should be
                     almost safe, so let's hope for the best */

            *ptr_status_flag |= local_status_flag;

            #endif /* !defined( cl_khr_int32_extended_atomics ) */
        }
    }
#endif /* defined( __OPENCL_VERSION__ ) */

#endif /* SIXTRACKLIB_OPENCL_INTERNAL_SUCCESS_FLAG_H__ */
/* end: sixtracklib/opencl/internal/success_flag.h */

