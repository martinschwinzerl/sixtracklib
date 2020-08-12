#ifndef SIXTRACKLIB_BASE_COBJECTS_GARBAGE_RANGE_H__
#define SIXTRACKLIB_BASE_COBJECTS_GARBAGE_RANGE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if !defined( __cplusplus )
        #include <stdbool.h>
        #include <stddef.h>
        #include <stdint.h>
        #include <stdlib.h>
        #include <limits.h>
    #else /* C++ */
        #include <cstddef>
        #include <cstdint>
        #include <limits>
    #endif /* C / C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

typedef struct NS(CObjGarbageRange)
{
    NS(cobj_address_t) begin_addr  SIXTRL_ALIGN( 8u );
    NS(cobj_address_t) size        SIXTRL_ALIGN( 8u );
}
NS(CObjGarbageRange);

typedef SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC NS(CObjGarbageRange)*
        NS(ptr_cobj_garbage_t);

typedef SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC NS(CObjGarbageRange) const*
        NS(ptr_const_cobj_garbage_t);

SIXTRL_STATIC SIXTRL_FN NS(ptr_cobj_garbage_t) NS(CObjGarbageRange_preset)(
    NS(ptr_cobj_garbage_t) SIXTRL_RESTRICT garbage_range ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t) NS(CObjGarbageRange_begin_addr)(
    SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC const NS(CObjGarbageRange) *const
        SIXTRL_RESTRICT garbage_range ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjGarbageRange_size)(
    SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC const NS(CObjGarbageRange) *const
        SIXTRL_RESTRICT garbage_range ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CObjGarbageRange_set_begin_addr)(
    NS(ptr_cobj_garbage_t) SIXTRL_RESTRICT garbage_range,
    NS(cobj_address_t) const begin_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CObjGarbageRange_set_size)(
    NS(ptr_cobj_garbage_t) SIXTRL_RESTRICT garbage_range,
    NS(cobj_size_t) const range_size ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
/* ||||||||||            implementation of inline methods          ||||||||| */
/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(ptr_cobj_garbage_t) NS(CObjGarbageRange_preset)(
    NS(ptr_cobj_garbage_t) SIXTRL_RESTRICT garbage_range ) SIXTRL_NOEXCEPT
{
    if( garbage_range != SIXTRL_NULLPTR )
    {
        NS(CObjGarbageRange_set_begin_addr)( garbage_range, 0 );
        NS(CObjGarbageRange_set_size)( garbage_range, 0u );
    }

    return garbage_range;
}

SIXTRL_INLINE NS(cobj_address_t) NS(CObjGarbageRange_begin_addr)(
    SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC const NS(CObjGarbageRange) *const
        SIXTRL_RESTRICT garbage_range ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( garbage_range != SIXTRL_NULLPTR );
    return garbage_range->begin_addr;
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjGarbageRange_size)(
    SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC const NS(CObjGarbageRange) *const
        SIXTRL_RESTRICT garbage_range ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( garbage_range != SIXTRL_NULLPTR );
    return garbage_range->size;
}

SIXTRL_INLINE void NS(CObjGarbageRange_set_begin_addr)(
    NS(ptr_cobj_garbage_t) SIXTRL_RESTRICT garbage_range,
    NS(cobj_address_t) const begin_addr ) SIXTRL_NOEXCEPT
{
    if( garbage_range != SIXTRL_NULLPTR )
        garbage_range->begin_addr = begin_addr;
}

SIXTRL_INLINE void NS(CObjGarbageRange_set_size)(
    NS(ptr_cobj_garbage_t) SIXTRL_RESTRICT garbage_range,
    NS(cobj_size_t) const range_size ) SIXTRL_NOEXCEPT
{
    if( garbage_range != SIXTRL_NULLPTR ) garbage_range->size = range_size;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_BASE_COBJECTS_GARBAGE_RANGE_H__ */
