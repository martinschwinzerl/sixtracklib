#ifndef SIXTRACKLIB_COMMON_BACKENDS_HELPER_METHODS_H__
#define SIXTRACKLIB_COMMON_BACKENDS_HELPER_METHODS_H__

#if !defined( SIXTRL_NO_INCLUDE )
    #include "sixtracklib/common/backends/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDE ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDE )
    #if defined( __cplusplus )
        #if !defined( _GPUCODE )
            #include <algorithm>
        #endif /* !defined( _GPUCODE ) */
        #include <cstddef>
        #include <cstdlib>
        #include <cstring>
    #else
        #include <stddef.h>
        #include <stdlib.h>
        #include <string.h>
    #endif /* __cplusplus */
    #include <stdint.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDE ) */

#if !defined( SIXTRACKLIB_COPY_VALUES )
    #if defined( _GPUCODE )
        #if defined( __CUDA_ARCH__ )
            #define SIXTRACKLIB_COPY_VALUES( T, destination, source, n ) \
            memcpy( ( destination ), ( source ), sizeof( T ) * ( n ) )
        #elif defined( __CUDACC__ ) || defined( __NVCC__ )
            #define SIXTRACKLIB_COPY_VALUES( T, destination, source, n ) \
            memcpy( ( destination ), ( source ), sizeof( T ) * ( n ) )
        #else
            #define SIXTRACKLIB_COPY_VALUES( T, destination, source, n ) \
            do \
            {  \
                SIXTRL_INT64_T ii = ( SIXTRL_INT64_T )0; \
                for( ; ii < ( n ) ; ++ii ) \
                {   \
                    *( ( destination ) + ii ) = *( ( source ) + ii );\
                }   \
            }  \
            while( 0 )

        #endif /* defined( __CUDA_ARCH__ ) */
    #elif !defined( _GPUCODE ) && defined( __cplusplus )
        #define SIXTRACKLIB_COPY_VALUES( T, destination, source, n ) \
            std::memcpy( ( destination ), ( source ), sizeof( T ) * ( n ) )
    #else /* defined( _GPUCODE ) */
        #define SIXTRACKLIB_COPY_VALUES( T, destination, source, n ) \
        memcpy( ( destination ), ( source ), sizeof( T ) * ( n ) )

    #endif /* defined( _GPUCODE ) */
#endif /* !defined( SIXTRACKLIB_COPY_VALUES ) */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRACKLIB_MOVE_VALUES )
    #if defined( _GPUCODE )
        #define SIXTRACKLIB_MOVE_VALUES( T, destination, source, n ) \
        do \
        {  \
           if( ( ( uintptr_t )( source ) ) < ( ( uintptr_t )( destination ) ) ) \
           {    \
                SIXTRL_INT64_T const end_idx = ( SIXTRL_INT64_T )-1; \
                SIXTRL_INT64_T ii = ( SIXTRL_INT64_T )( n ) - end_idx; \
                \
                for( ; ii > end_idx ; --ii ) \
                {   \
                    *( ( destination ) + ii ) = *( ( source ) + ii ); \
                }   \
           }    \
           else \
           {    \
                SIXTRL_INT64_T ii = ( SIXTRL_INT64_T )0; \
                \
                for( ; ii < ( n ) ; ++ii ) \
                {   \
                    *( ( destination ) + ii ) = *( ( source ) + ii ); \
                }   \
           }    \
        }  \
        while( 0 )

    #else /* defined( _GPUCODE ) */

        #if defined( __CUDACC__ )
            #define SIXTRACKLIB_MOVE_VALUES( T, destination, source, n ) \
            do \
            {  \
               if( ( ( uintptr_t )( source ) ) < ( ( uintptr_t )( destination ) ) ) \
               {    \
                    SIXTRL_INT64_T const end_idx = ( SIXTRL_INT64_T )-1; \
                    SIXTRL_INT64_T ii = ( SIXTRL_INT64_T )( n ) - end_idx; \
                    \
                    for( ; ii > end_idx ; --ii ) \
                    {   \
                        *( ( destination ) + ii ) = *( ( source ) + ii ); \
                    }   \
               }    \
               else \
               {    \
                    SIXTRL_INT64_T ii = ( SIXTRL_INT64_T )0; \
                    \
                    for( ; ii < ( n ) ; ++ii ) \
                    {   \
                        *( ( destination ) + ii ) = *( ( source ) + ii ); \
                    }   \
               }    \
            }  \
            while( 0 )

        #else
            #define SIXTRACKLIB_MOVE_VALUES( T, destination, source, n ) \
                memmove( ( destination ), ( source ), sizeof( T ) * ( n ) )

        #endif /* CUDA Host side code */

    #endif /* defined( _GPUCODE ) */

#endif /* !defined( SIXTRACKLIB_MOVE_VALUES ) */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRACKLIB_SET_VALUES )
    #if defined( _GPUCODE )
        #define SIXTRACKLIB_SET_VALUES( T, destination, n, value ) \
        do \
        {  \
           SIXTRL_INT64_T ii = ( SIXTRL_INT64_T )0; \
           SIXTRL_INT64_T const end_idx = ( SIXTRL_INT64_T )( n ); \
           \
           for( ; ii < end_idx ; ++ii ) \
           {  \
              *( ( destination ) + ii ) = value; \
           }  \
        }  \
        while( 0 )

    #else /* defined( _GPUCODE ) */
        #define SIXTRACKLIB_SET_VALUES( T, destination, n, value ) \
        memset( ( destination ), ( value ), sizeof( T ) * ( n ) )

    #endif /* defined( _GPUCODE ) */
#endif /* !defined( SIXTRACKLIB_SET_VALUES ) */
#endif /* SIXTRACKLIB_COMMON_BACKENDS_HELPER_METHODS_H__ */
