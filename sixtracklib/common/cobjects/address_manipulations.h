#ifndef SIXTRACKLIB_COMMON_COBJECTS_ADDRESS_MANIPULATIONS_C99_H__
#define SIXTRACKLIB_COMMON_COBJECTS_ADDRESS_MANIPULATIONS_C99_H__

#if !defined(  SIXTRL_NO_SYSTEM_INCLUDES )
    #if !defined( __cplusplus )
        #include <stdbool.h>
        #include <stddef.h>
        #include <stdlib.h>
        #include <limits.h>
    #else
        #include <cstddef>
        #include <cstdlib>
    #endif /* C++ */
#endif /* !defined(  SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* SIXTRL_NO_INCLUDES */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_diff_t)
NS(CObjFlatBuffer_limit_offset_max)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_diff_t)
    NS(CObjFlatBuffer_limit_offset_min)( void ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_check_addr_arithmetic)(
    NS(cobj_address_t) const addr,
    NS(cobj_address_diff_t) const offset,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_perform_addr_shift)(
    NS(cobj_address_t) const addr,
    NS(cobj_address_diff_t) const offset,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* !defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
/* ||||||||||            implementation of inline methods          ||||||||| */
/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

#if !defined(  SIXTRL_NO_SYSTEM_INCLUDES )
    #if !defined( __cplusplus )
        #include <stdbool.h>
        #include <stddef.h>
        #include <stdlib.h>
        #include <limits.h>
    #else
        #include <cstddef>
        #include <cstdlib>
        #if !defined( _GPUCODE )
            #include <limits>
        #endif /* !defined( _GPUCODE ) */
    #endif /* C++ */
#endif /* !defined(  SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cobj_address_diff_t)
    NS(CObjFlatBuffer_limit_offset_max)() SIXTRL_NOEXCEPT
{
    #if defined( _GPUCODE )
        #if defined( __OPENCL_VERSION__ )

            SIXTRL_ASSERT( sizeof( NS(cobj_address_diff_t) >=
                           sizeof( ptr_to_raw_t ) ) );

            return ( NS(cobj_address_diff_t) )LONG_MAX;

        #elif defined( __CUDACC__ )

            SIXTRL_ASSERT( sizeof( NS(cobj_address_diff_t) ) >=
                           sizeof( long long int ) );

            return ( NS(cobj_address_diff_t) )9223372036854775807L;
        #else
            return ( NS(cobj_address_diff_t) )9223372036854775807L;

        #endif /* defined( __OPENCL_VERSION__ ) */
    #elif defined( __cplusplus )
        typedef NS(cobj_address_diff_t) addr_diff_t;

        SIXTRL_ASSERT( std::numeric_limits< addr_diff_t >::digits >= 63u );
        SIXTRL_ASSERT( std::numeric_limits< addr_diff_t >::is_signed  );
        SIXTRL_ASSERT( std::numeric_limits< addr_diff_t >::is_integer );

        #if defined( __CUDA_ARCH__ )

        return ( NS(cobj_address_diff_t) )9223372036854775807L;

        #else  /* defined( __CUDA_ARCH__ ) */

        return std::numeric_limits< addr_diff_t >::max();

        #endif /* defined( __CUDA_ARCH__ ) */

    #else
        SIXTRL_ASSERT( sizeof( NS(cobj_address_diff_t) ) >=
                       sizeof( long long int ) );

        return ( NS(cobj_address_diff_t) )LLONG_MAX;

    #endif /* defined( _GPUCODE ) */
}

SIXTRL_INLINE NS(cobj_address_diff_t)
    NS(CObjFlatBuffer_limit_offset_min)() SIXTRL_NOEXCEPT
{
    #if defined( _GPUCODE )
         #if defined( __OPENCL_VERSION__ )  && \
             defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
             ( SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1 )

            SIXTRL_ASSERT( sizeof( NS(cobj_address_diff_t) >=
                           sizeof( ptr_to_raw_t ) ) );

            return ( NS(cobj_address_diff_t ) )LONG_MIN;

        #elif defined( __CUDACC__ )  && \
              defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
              ( SIXTRACKLIB_ENABLE_MODULE_CUDA == 1 )

            SIXTRL_ASSERT( sizeof( NS(cobj_address_diff_t) ) >=
                           sizeof( long long int ) );

            return ( NS(cobj_address_diff_t) )-9223372036854775807L;
        #else

            return ( NS(cobj_address_diff_t) )-9223372036854775807L;

        #endif /* defined( __OPENCL_VERSION__ ) */
    #elif defined( __cplusplus )
        typedef NS(cobj_address_diff_t) addr_diff_t;

        SIXTRL_ASSERT( std::numeric_limits< addr_diff_t >::digits >= 63u );
        SIXTRL_ASSERT( std::numeric_limits< addr_diff_t >::is_signed  );
        SIXTRL_ASSERT( std::numeric_limits< addr_diff_t >::is_integer );

        #if defined( __CUDA_ARCH__ )

        return ( NS(cobj_address_diff_t) )-9223372036854775807L;

        #else /* defined( __CUDA_ARCH__ ) */

        return std::numeric_limits< addr_diff_t >::min();

        #endif /* defined( __CUDA_ARCH__ ) */

    #else
        SIXTRL_ASSERT( sizeof( NS(cobj_address_diff_t) ) >=
                       sizeof( long long int ) );

        return ( NS(cobj_address_diff_t) )LLONG_MIN;

    #endif /* defined( _GPUCODE ) */
}


SIXTRL_INLINE bool NS(CObjFlatBuffer_check_addr_arithmetic)(
    NS(cobj_address_t) const addr,
    NS(cobj_address_diff_t) const offset,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_address_t)       address_t;
    typedef NS(cobj_address_diff_t)  addr_diff_t;

    SIXTRL_ASSERT( sizeof( address_t ) == sizeof( addr_diff_t) );
    SIXTRL_ASSERT( sizeof( address_t ) >= 8u );
    SIXTRL_ASSERT( slot_size > 0u );

    addr_diff_t const LIMIT_OFFSET_MAX =
        NS(CObjFlatBuffer_limit_offset_max)();

    return (
        ( addr != ( address_t )0u ) && ( ( addr % slot_size ) == 0u ) &&
        ( ( ( offset >= 0 ) &&
            ( ( ( ( address_t )offset ) % slot_size ) == 0u ) &&
            ( ( LIMIT_OFFSET_MAX - ( address_t )offset ) >= addr ) ) ||
          ( ( offset <  0 ) &&
            ( ( ( ( address_t )-offset ) % slot_size ) == 0u ) &&
            ( addr >= ( address_t )-offset ) ) ) );
}

SIXTRL_INLINE NS(cobj_address_t) NS(CObjFlatBuffer_perform_addr_shift)(
    NS(cobj_address_t) const addr,
    NS(cobj_address_diff_t) const offset,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( NS(CObjFlatBuffer_check_addr_arithmetic)(
        addr, offset, slot_size) );

    #if !defined( NDEBUG )
    ( void )slot_size;
    #endif /* !defined( NDEBUG ) */

    return addr + offset;
}

#if defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_COBJECTS_ADDRESS_MANIPULATIONS_C99_H__ */
