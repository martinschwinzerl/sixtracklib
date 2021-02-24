#ifndef SIXTRACKLIB_COMMON_COBJECTS_ADDRESS_MANIPULATIONS_C99_H__
#define SIXTRACKLIB_COMMON_COBJECTS_ADDRESS_MANIPULATIONS_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* SIXTRL_NO_INCLUDES */

#if !defined(  SIXTRL_NO_SYSTEM_INCLUDES )
    #if !defined( __cplusplus )
        #include <limits.h>
    #else /* C++ */
        #include <limits>
    #endif /* C++ */
#endif /* !defined(  SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( _cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_diff_type)
NS(CObjFlatBuffer_limit_offset_max)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_diff_type)
    NS(CObjFlatBuffer_limit_offset_min)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_check_addr_arithmetic)(
    NS(cobj_addr_type) const addr,
    NS(cobj_addr_diff_type) const offset,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CObjFlatBuffer_perform_addr_shift)(
    NS(cobj_addr_type) const addr,
    NS(cobj_addr_diff_type) const offset,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( _cplusplus ) && !defined( _GPUCODE ) */

/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
/* ||||||||||            implementation of inline methods          ||||||||| */
/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( _cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_INLINE NS(cobj_addr_diff_type)
    NS(CObjFlatBuffer_limit_offset_max)() SIXTRL_NOEXCEPT
{
    #if defined( _GPUCODE )
        #if defined( __OPENCL_VERSION__ )

            SIXTRL_ASSERT( sizeof( NS(cobj_addr_diff_type) >=
                           sizeof( ptr_to_raw_t ) ) );

            return ( NS(cobj_addr_diff_type) )LONG_MAX;

        #elif defined( __CUDACC__ )

            SIXTRL_ASSERT( sizeof( NS(cobj_addr_diff_type) ) >=
                           sizeof( long long int ) );

            return ( NS(cobj_addr_diff_type) )9223372036854775807L;
        #else
            return ( NS(cobj_addr_diff_type) )9223372036854775807L;

        #endif /* defined( __OPENCL_VERSION__ ) */
    #elif defined( __cplusplus )
        typedef NS(cobj_addr_diff_type) addr_diff_t;

        SIXTRL_ASSERT( std::numeric_limits< addr_diff_t >::digits >= 63u );
        SIXTRL_ASSERT( std::numeric_limits< addr_diff_t >::is_signed  );
        SIXTRL_ASSERT( std::numeric_limits< addr_diff_t >::is_integer );

        #if defined( __CUDA_ARCH__ )

        return ( NS(cobj_addr_diff_type) )9223372036854775807L;

        #else  /* defined( __CUDA_ARCH__ ) */

        return std::numeric_limits< addr_diff_t >::max();

        #endif /* defined( __CUDA_ARCH__ ) */

    #else
        SIXTRL_ASSERT( sizeof( NS(cobj_addr_diff_type) ) >=
                       sizeof( long long int ) );

        return ( NS(cobj_addr_diff_type) )LLONG_MAX;

    #endif /* defined( _GPUCODE ) */
}

SIXTRL_INLINE NS(cobj_addr_diff_type)
    NS(CObjFlatBuffer_limit_offset_min)() SIXTRL_NOEXCEPT
{
    #if defined( _GPUCODE )
         #if defined( __OPENCL_VERSION__ )  && \
             defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
             ( SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1 )

            SIXTRL_ASSERT( sizeof( NS(cobj_addr_diff_type) >=
                           sizeof( ptr_to_raw_t ) ) );

            return ( NS(cobj_addr_diff_type ) )LONG_MIN;

        #elif defined( __CUDACC__ )  && \
              defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
              ( SIXTRACKLIB_ENABLE_MODULE_CUDA == 1 )

            SIXTRL_ASSERT( sizeof( NS(cobj_addr_diff_type) ) >=
                           sizeof( long long int ) );

            return ( NS(cobj_addr_diff_type) )-9223372036854775807L;
        #else

            return ( NS(cobj_addr_diff_type) )-9223372036854775807L;

        #endif /* defined( __OPENCL_VERSION__ ) */
    #elif defined( __cplusplus )
        typedef NS(cobj_addr_diff_type) addr_diff_t;

        SIXTRL_ASSERT( std::numeric_limits< addr_diff_t >::digits >= 63u );
        SIXTRL_ASSERT( std::numeric_limits< addr_diff_t >::is_signed  );
        SIXTRL_ASSERT( std::numeric_limits< addr_diff_t >::is_integer );

        #if defined( __CUDA_ARCH__ )

        return ( NS(cobj_addr_diff_type) )-9223372036854775807L;

        #else /* defined( __CUDA_ARCH__ ) */

        return std::numeric_limits< addr_diff_t >::min();

        #endif /* defined( __CUDA_ARCH__ ) */

    #else
        SIXTRL_ASSERT( sizeof( NS(cobj_addr_diff_type) ) >=
                       sizeof( long long int ) );

        return ( NS(cobj_addr_diff_type) )LLONG_MIN;

    #endif /* defined( _GPUCODE ) */
}

SIXTRL_INLINE bool NS(CObjFlatBuffer_check_addr_arithmetic)(
    NS(cobj_addr_type) const addr, NS(cobj_addr_diff_type) const offset,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > 0u );
    SIXTRL_ASSERT( sizeof( NS(cobj_addr_type) ) >= 8u );
    SIXTRL_ASSERT( sizeof( NS(cobj_addr_type) ) ==
                   sizeof( NS(cobj_addr_diff_type) ) );
    return (
        ( addr != ( NS(cobj_addr_type) )0u ) &&
        ( ( addr % slot_size ) == 0u ) &&
        ( ( ( offset >= 0 ) &&
            ( ( ( ( NS(cobj_addr_type) )offset ) % slot_size ) == 0u ) &&
            ( ( NS(CObjFlatBuffer_limit_offset_max)() -
                ( NS(cobj_addr_type) )offset ) >= addr ) ) ||
          ( ( offset <  0 ) &&
            ( ( ( ( NS(cobj_addr_type) )-offset ) % slot_size ) == 0u ) &&
            ( addr >= ( NS(cobj_addr_type) )-offset ) ) ) ); }

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_perform_addr_shift)(
    NS(cobj_addr_type) const addr,
    NS(cobj_addr_diff_type) const offset,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( NS(CObjFlatBuffer_check_addr_arithmetic)(
        addr, offset, slot_size) );
    ( void )slot_size;
    return addr + offset;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_COMMON_COBJECTS_ADDRESS_MANIPULATIONS_C99_H__ */
