#ifndef SIXTRACKLIB_OPENCL_KERNELS_DEFAULT_DEFINES_H__
#define SIXTRACKLIB_OPENCL_KERNELS_DEFAULT_DEFINES_H__

#if defined( __OPENCL_C_VERSION__ )
    #if !defined( _GPUCODE )
        #define _GPUCODE 1
    #endif /* !defined( _GPUCODE ) */

    #if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
        #define SIXTRL_NO_SYSTEM_INCLUDES 1
    #endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

    /* --------------------------------------------------------------------- */
    /* common: */

    #if !defined( SIXTRL_ARGPTR_DEC )
        #define SIXTRL_ARGPTR_DEC __private
    #endif /* !defined( SIXTRL_ARGPTR_DEC ) */

    #if !defined( SIXTRL_DATAPTR_DEC )
        #define SIXTRL_DATAPTR_DEC __global
    #endif /* !defined( SIXTRL_DATAPTR_DEC ) */

    /* --------------------------------------------------------------------- */
    /* cobjects: */

    #if !defined( SIXTRL_CBUFFER_ARGPTR_DEC )
        #define SIXTRL_CBUFFER_ARGPTR_DEC __private
    #endif /* !defined( SIXTRL_CBUFFER_ARGPTR_DEC ) */

    #if !defined( SIXTRL_CBUFFER_DATAPTR_DEC )
        #define SIXTRL_CBUFFER_DATAPTR_DEC __global
    #endif /* !defined( SIXTRL_CBUFFER_DATAPTR_DEC ) */

    #if !defined( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC )
        #define SIXTRL_CBUFFER_OBJ_ARGPTR_DEC __global
    #endif /* !defined( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC ) */

    #if !defined( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC )
        #define SIXTRL_CBUFFER_OBJ_DATAPTR_DEC __global
    #endif /* !defined( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC ) */

    #if !defined( SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC )
        #define SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC __global
    #endif /* !defined( SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC ) */

    #if !defined( SIXTRL_CBUFFER_GARBAGE_DATAPTR_DEC )
        #define SIXTRL_CBUFFER_GARBAGE_DATAPTR_DEC __global
    #endif /* !defined( SIXTRL_CBUFFER_GARBAGE_DATAPTR_DEC ) */

    /* --------------------------------------------------------------------- */
    /* beam_elements: */

    #if !defined( SIXTRL_BE_ARGPTR_DEC )
        #define SIXTRL_BE_ARGPTR_DEC __global
    #endif /* !defined( SIXTRL_BE_ARGPTR_DEC ) */

    #if !defined( SIXTRL_BE_DATAPTR_DEC )
        #define SIXTRL_BE_DATAPTR_DEC __global
    #endif /* !defined( SIXTRL_BE_DATAPTR_DEC ) */

    /* --------------------------------------------------------------------- */
    /* particless: */

    #if !defined( SIXTRL_PARTICLE_ARGPTR_DEC )
        #define SIXTRL_PARTICLE_ARGPTR_DEC __private
    #endif /* !defined( SIXTRL_PARTICLE_ARGPTR_DEC ) */

    #if !defined( SIXTRL_PARTICLE_DATAPTR_DEC )
        #define SIXTRL_PARTICLE_DATAPTR_DEC __private
    #endif /* !defined( SIXTRL_PARTICLE_DATAPTR_DEC ) */

    #if !defined( SIXTRL_PARTICLES_ARGPTR_DEC )
        #define SIXTRL_PARTICLES_ARGPTR_DEC __global
    #endif /* !defined( SIXTRL_PARTICLES_ARGPTR_DEC ) */

    #if !defined( SIXTRL_PARTICLES_DATAPTR_DEC )
        #define SIXTRL_PARTICLES_DATAPTR_DEC __global
    #endif /* !defined( SIXTRL_PARTICLES_DATAPTR_DEC ) */

    #if !defined( SIXTRL_PARTICLES_ADDR_ARGPTR_DEC )
        #define SIXTRL_PARTICLES_ARGPTR_DEC __global
    #endif /* !defined( SIXTRL_PARTICLES_ADDR_ARGPTR_DEC ) */

    #if !defined( SIXTRL_PARTICLES_ADDR_DATAPTR_DEC )
        #define SIXTRL_PARTICLES_ADDR_DATAPTR_DEC __global
    #endif /* !defined( SIXTRL_PARTICLES_ADDR_DATAPTR_DEC ) */

    /* --------------------------------------------------------------------- */
    /* track: */

    #if !defined( SIXTRL_TRACK_ARGPTR_DEC )
        #define SIXTRL_TRACK_ARGPTR_DEC __global
    #endif /* !defined( SIXTRL_TRACK_ARGPTR_DEC ) */

    #if !defined( SIXTRL_TRACK_DATAPTR_DEC )
        #define SIXTRL_TRACK_DATAPTR_DEC __global
    #endif /* !defined( SIXTRL_TRACK_DATAPTR_DEC ) */

#endif /* __OPENCL_C_VERSION__ */
#endif /* SIXTRACKLIB_OPENCL_KERNELS_DEFAULT_DEFINES_H__ */
