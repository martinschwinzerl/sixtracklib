#ifndef SIXTRACKLIB_COMMON_COBJECTS_GARBAGE_RANGE_C99_H__
#define SIXTRACKLIB_COMMON_COBJECTS_GARBAGE_RANGE_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(CObjGarbageRange) {
    NS(cobj_addr_type) begin_addr  SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(cobj_addr_type) size        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); }
NS(CObjGarbageRange);

typedef SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC NS(CObjGarbageRange)*
        NS(cobj_garbage_range_pointer);

typedef SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC NS(CObjGarbageRange) const*
        NS(cobj_garbage_range_const_pointer);

SIXTRL_STATIC SIXTRL_FN NS(cobj_garbage_range_pointer)
NS(CObjGarbageRange_preset)( NS(cobj_garbage_range_pointer) SIXTRL_RESTRICT
    garbage_range ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CObjGarbageRange_begin_addr)(
    NS(cobj_garbage_range_const_pointer) const SIXTRL_RESTRICT garbage_range
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjGarbageRange_size)(
    NS(cobj_garbage_range_const_pointer) const SIXTRL_RESTRICT garbage_range
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CObjGarbageRange_set_begin_addr)(
    NS(cobj_garbage_range_pointer) SIXTRL_RESTRICT garbage_range,
    NS(cobj_addr_type) const begin_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CObjGarbageRange_set_size)(
    NS(cobj_garbage_range_pointer) SIXTRL_RESTRICT garbage_range,
    NS(cobj_size_type) const range_size ) SIXTRL_NOEXCEPT;

/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
/* ||||||||||            implementation of inline methods          ||||||||| */
/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

SIXTRL_INLINE NS(cobj_garbage_range_pointer) NS(CObjGarbageRange_preset)(
    NS(cobj_garbage_range_pointer) SIXTRL_RESTRICT garbage_range ) SIXTRL_NOEXCEPT
{
    if( garbage_range != SIXTRL_NULLPTR )
    {
        NS(CObjGarbageRange_set_begin_addr)( garbage_range, 0 );
        NS(CObjGarbageRange_set_size)( garbage_range, 0u );
    }

    return garbage_range;
}

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjGarbageRange_begin_addr)(
    NS(cobj_garbage_range_const_pointer) const
        SIXTRL_RESTRICT garbage_range ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( garbage_range != SIXTRL_NULLPTR );
    return garbage_range->begin_addr;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjGarbageRange_size)(
    NS(cobj_garbage_range_const_pointer) const
        SIXTRL_RESTRICT garbage_range ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( garbage_range != SIXTRL_NULLPTR );
    return garbage_range->size;
}

SIXTRL_INLINE void NS(CObjGarbageRange_set_begin_addr)(
    NS(cobj_garbage_range_pointer) SIXTRL_RESTRICT garbage_range,
    NS(cobj_addr_type) const begin_addr ) SIXTRL_NOEXCEPT
{
    if( garbage_range != SIXTRL_NULLPTR )
        garbage_range->begin_addr = begin_addr;
}

SIXTRL_INLINE void NS(CObjGarbageRange_set_size)(
    NS(cobj_garbage_range_pointer) SIXTRL_RESTRICT garbage_range,
    NS(cobj_size_type) const range_size ) SIXTRL_NOEXCEPT
{
    if( garbage_range != SIXTRL_NULLPTR ) garbage_range->size = range_size;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_COBJECTS_GARBAGE_RANGE_C99_H__ */
