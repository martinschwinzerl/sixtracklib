#ifndef SIXTRACKLIB_COMMON_COBJECTS_COBJ_INDEX_OBJECT_C99_H__
#define SIXTRACKLIB_COMMON_COBJECTS_COBJ_INDEX_OBJECT_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/buffer_object_defines.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

typedef struct NS(CObjIndex)
{
    NS(cobj_address_t) begin_addr  SIXTRL_ALIGN( 8u );
    NS(cobj_type_id_t) type_id     SIXTRL_ALIGN( 8u );
    NS(cobj_size_t)    size        SIXTRL_ALIGN( 8u );
}
NS(CObjIndex);

typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* NS(ptr_cobj_index_t);
typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const*
        NS(ptr_const_cobj_index_t);

typedef SIXTRL_BUFFER_OBJ_DATAPTR_DEC NS(cobj_raw_t)*
        NS(ptr_cobj_index_data_t);

typedef SIXTRL_BUFFER_OBJ_DATAPTR_DEC NS(cobj_raw_t) const*
        NS(ptr_const_cobj_index_data_t);

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(CObjIndex)                     CObjIndex;
    typedef ::NS(ptr_cobj_index_t)              ptr_cobj_index_t;
    typedef ::NS(ptr_const_cobj_index_t)        ptr_const_cobj_index_t;
    typedef ::NS(ptr_cobj_index_data_t)         ptr_cobj_index_data_t;
    typedef ::NS(ptr_const_cobj_index_data_t)   ptr_const_cobj_index_data_t;
}
#endif /* defined( __cplusplus ) */

/* ========================================================================= */

SIXTRL_STATIC SIXTRL_FN NS(ptr_cobj_index_t) NS(CObjIndex_preset)(
    NS(ptr_cobj_index_t) SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t) NS(CObjIndex_begin_addr)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT
        index_obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CObjIndex_set_begin_addr)(
    NS(ptr_cobj_index_t) SIXTRL_RESTRICT index_obj,
    NS(cobj_address_t) const begin_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN  NS(cobj_type_id_t) NS(CObjIndex_type_id)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CObjIndex_set_type_id)(
    NS(ptr_cobj_index_t) SIXTRL_RESTRICT index_obj,
    NS(cobj_type_id_t) const type_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN  NS(cobj_size_t) NS(CObjIndex_size)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN  void NS(CObjIndex_set_size)(
    NS(ptr_cobj_index_t) SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjIndex_begin_addr_filter_by_type_info)(
    NS(ptr_const_cobj_index_t) SIXTRL_RESTRICT index_obj,
    NS(cobj_type_id_t) const required_type_id,
    NS(cobj_size_t) const min_size,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(ptr_const_cobj_index_data_t)
NS(CObjIndex_ptr_const_begin)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
    NS(CObjIndex) *const SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(ptr_cobj_index_data_t) NS(CObjIndex_ptr_begin)(
    NS(ptr_cobj_index_t) SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CObjIndex_set_ptr_begin)(
    NS(ptr_cobj_index_t) SIXTRL_RESTRICT index_obj,
    NS(ptr_cobj_index_data_t) SIXTRL_RESTRICT begin_ptr ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(CObjIndex_print_slots)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT
        index_obj, NS(cobj_size_t) const num_slots_to_print );

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* *
 * *****         Implementation of inline functions and methods        ***** *
 * ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/address_manipulations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(ptr_cobj_index_t) NS(CObjIndex_preset)(
    NS(ptr_cobj_index_t) SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT
{
    if( index_obj != SIXTRL_NULLPTR )
    {
        NS(CObjIndex_set_begin_addr)( index_obj, 0u );
        NS(CObjIndex_set_type_id)( index_obj, 0u );
        NS(CObjIndex_set_size)( index_obj, 0u );
    }

    return index_obj;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_address_t) NS(CObjIndex_begin_addr)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( index_obj != SIXTRL_NULLPTR );

    SIXTRL_ASSERT(
        ( sizeof( NS(cobj_raw_t) const* ) >= sizeof( NS(cobj_address_t) ) ) ||
        ( ( sizeof( NS(cobj_raw_t) const* ) == 4u ) &&
          ( sizeof( NS(cobj_address_t) ) == 8u ) &&
          ( NS(cobj_address_t) )NS(CObjFlatBuffer_limit_offset_max)() >
                index_obj->begin_addr ) );

    return index_obj->begin_addr;
}

SIXTRL_INLINE void NS(CObjIndex_set_begin_addr)(
    NS(ptr_cobj_index_t) SIXTRL_RESTRICT index_obj,
    NS(cobj_address_t) const begin_addr ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT(
        ( sizeof( NS(cobj_raw_t) const* ) >= sizeof( NS(cobj_address_t) ) ) ||
        ( ( sizeof( NS(cobj_raw_t) const* ) == 4u ) &&
          ( sizeof( NS(cobj_address_t) ) == 8u ) &&
          ( ( NS(cobj_address_t)  )NS(CObjFlatBuffer_limit_offset_max)() >
              begin_addr ) ) );

    if( index_obj != SIXTRL_NULLPTR ) index_obj->begin_addr = begin_addr;
}

SIXTRL_INLINE NS(cobj_type_id_t) NS(CObjIndex_type_id)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( index_obj != SIXTRL_NULLPTR );
    return index_obj->type_id;
}

SIXTRL_INLINE void NS(CObjIndex_set_type_id)(
    NS(ptr_cobj_index_t) SIXTRL_RESTRICT index_obj,
    NS(cobj_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    if( index_obj != SIXTRL_NULLPTR ) index_obj->type_id = type_id;
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjIndex_size)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( index_obj != SIXTRL_NULLPTR );
    return index_obj->size;
}

SIXTRL_INLINE void NS(CObjIndex_set_size)(
    NS(ptr_cobj_index_t) SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const size ) SIXTRL_NOEXCEPT
{
    if( index_obj != SIXTRL_NULLPTR ) index_obj->size = size;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_address_t) NS(CObjIndex_begin_addr_filter_by_type_info)(
    NS(ptr_const_cobj_index_t) SIXTRL_RESTRICT index_obj,
    NS(cobj_type_id_t) const required_type_id,
    NS(cobj_size_t) const min_size,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t) _size_t;

    return ( ( index_obj != SIXTRL_NULLPTR ) &&
             ( required_type_id != SIXTRL_COBJECTS_ILLEGAL_TYPE_ID ) &&
             ( required_type_id == NS(CObjIndex_type_id)( index_obj ) ) &&
             ( min_size <= NS(CObjIndex_size)( index_obj ) ) &&
             ( slot_size > ( _size_t )0u ) &&
             ( NS(CObjIndex_size)( index_obj ) % slot_size == ( _size_t )0u ) )
        ? NS(CObjIndex_begin_addr)( index_obj )
        : ( NS(cobj_address_t) )SIXTRL_COBJECTS_NULL_ADDRESS;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(ptr_const_cobj_index_data_t) NS(CObjIndex_ptr_const_begin)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT
{
    return ( NS(ptr_const_cobj_index_data_t) )( uintptr_t
        )NS(CObjIndex_begin_addr)( index_obj );
}

SIXTRL_INLINE NS(ptr_cobj_index_data_t) NS(CObjIndex_ptr_begin)(
    NS(ptr_cobj_index_t) SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT
{
    return ( NS(ptr_cobj_index_data_t)
        )NS(CObjIndex_ptr_const_begin)( index_obj );
}

SIXTRL_INLINE void NS(CObjIndex_set_ptr_begin)(
    NS(ptr_cobj_index_t) SIXTRL_RESTRICT index_obj,
    NS(ptr_cobj_index_data_t) SIXTRL_RESTRICT begin_ptr ) SIXTRL_NOEXCEPT
{
    NS(CObjIndex_set_begin_addr)( index_obj,
            ( NS(cobj_address_t) )( uintptr_t )begin_ptr );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(CObjIndex_print_slots)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const num_slots_to_print )
{
    typedef NS(cobj_address_t)    address_t;
    typedef NS(cobj_size_t)       buf_size_t;
    typedef NS(cobj_type_id_t)    type_id_t;
    typedef SIXTRL_BUFFER_OBJ_DATAPTR_DEC address_t const*  ptr_addr_t;

    type_id_t const type_id = NS(CObjIndex_type_id)( index_obj );

    buf_size_t const slot_size = ( buf_size_t )8u;
    buf_size_t const obj_size  = NS(CObjIndex_size)( index_obj );
    buf_size_t const num_slots = obj_size / slot_size;
    ptr_addr_t ptr_slots = ( ptr_addr_t )NS(CObjIndex_begin_addr)( index_obj );

    buf_size_t ii = ( buf_size_t )0u;
    buf_size_t nn = num_slots;

    if( ( num_slots_to_print > ( buf_size_t )0u ) &&
        ( num_slots_to_print < num_slots ) )
    {
        nn = num_slots_to_print;
    }

    printf( "type_id            : %8d\r\n", ( int )type_id );
    printf( "obj size           : %8d\r\n", ( int )obj_size );
    printf( "num_slots          : %8d\r\n", ( int )num_slots );
    printf( "num_slots to print : %8d\r\n", ( int )nn );

    for( ; ii < nn ; ++ii )
    {
        if( ii < 21 )
        {
            printf( "slot_id = %8lu | slot addr = %20lu | slot_value = %20lu\r\n",
                ( unsigned long )ii,
                ( unsigned long )&ptr_slots[ ii ],
                ( unsigned long )ptr_slots[ ii ] );
        }
        else
        {
            printf( "slot_id = %8lu | slot addr = %20lu | slot_value = %+19.12f\r\n",
                ( unsigned long )ii,
                ( unsigned long )&ptr_slots[ ii ],
                *( ( SIXTRL_BUFFER_OBJ_DATAPTR_DEC double const* )&ptr_slots[ ii ] ) );
        }
    }

    return;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_COBJECTS_COBJ_INDEX_OBJECT_C99_H__ */
