#ifndef SIXTRACKLIB_COMMON_INTERNAL_BINARY_ARRAY_OBJECT_C99_H__
#define SIXTRACKLIB_COMMON_INTERNAL_BINARY_ARRAY_OBJECT_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/internal/object_type_id.h"
    #if !defined( _GPUCODE )
        #include "sixtracklib/common/buffer.h"
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN NS(object_type_id_t)
NS(BinaryArray_buffer_index_type_id)(
    const NS(Object) *const SIXTRL_RESTRICT info_obj );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(BinaryArray_value_size)( NS(object_type_id_t) const type_id );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC unsigned char const*
NS(BinaryArray_buffer_index_const_begin)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    const NS(Object) *const SIXTRL_RESTRICT info_obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC unsigned char*
NS(BinaryArray_buffer_index_begin)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT info_obj );


SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)
NS(BinaryArray_buffer_index_num_values)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    const NS(Object) *const SIXTRL_RESTRICT info_obj );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(object_type_id_t)
NS(BinaryArray_managed_buffer_type_id)( SIXTRL_BUFFER_DATAPTR_DEC
    unsigned char const* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC unsigned char const*
NS(BinaryArray_managed_buffer_const_begin)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC unsigned char*
NS(BinaryArray_managed_buffer_begin)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)
NS(BinaryArray_managed_buffer_num_values)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(BinaryArray_buffer_index_get_num_dataptrs)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT array );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(BinaryArray_buffer_index_get_num_slots)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT array,
    NS(buffer_size_t) const slot_size );

#if !defined( _GPUCODE )

SIXTRL_STATIC SIXTRL_HOST_FN NS(object_type_id_t)
NS(BinaryArray_buffer_type_id)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC unsigned char const*
NS(BinaryArray_buffer_const_begin)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC unsigned char*
NS(BinaryArray_buffer_begin)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)
NS(BinaryArray_buffer_num_values)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

SIXTRL_STATIC SIXTRL_FN bool NS(BinaryArray_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(object_type_id_t) const type_id, NS(buffer_size_t) const num_values,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_dataptrs );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC void* NS(BinaryArray_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(object_type_id_t) const type_id, NS(buffer_size_t) const num_values,

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC void* NS(BinaryArray_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(object_type_id_t) const type_id, NS(buffer_size_t) const num_values,
    SIXTRL_ARGPTR_DEC const void *const SIXTRL_RESTRICT data_begin );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC void*
NS(BinarayArray_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT orig );

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* *****          Implementation of C inline functions                   *** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */


SIXTRL_INLINE NS(object_type_id_t) NS(BinaryArray_buffer_index_type_id)(
    const NS(Object) *const SIXTRL_RESTRICT bin_array )
{
    return ( bin_array != SIXTRL_NULLPTR )
        ? NS(Object_type_id)( bin_array ) : NS(OBJECT_TYPE_NONE);
}


SIXTRL_INLINE NS(buffer_size_t) NS(BinaryArray_value_size)(
    NS(object_type_id_t) const type_id )
{
    NS(buffer_size_t) value_size = ( NS(buffer_size_t) )0u;

    switch( type_id )
    {
        case NS(OBJECT_TYPE_REAL_ARRAY):
        {
            value_size = sizeof( SIXTRL_REAL_T );
            break;
        }

        case NS(OBJECT_TYPE_FLOAT32_ARRAY):
        {
            value_size = sizeof( float );
            break;
        }

        case NS(OBJECT_TYPE_UINT64_ARRAY):
        {
            value_size = sizeof( SIXTRL_UINT64_T );
            break;
        }

        case NS(OBJECT_TYPE_INT64_ARRAY):
        {
            value_size = sizeof( SIXTRL_INT64_T );
            break;
        }

        case NS(OBJECT_TYPE_UINT32_ARRAY):
        {
            value_size = sizeof( SIXTRL_UINT32_T );
            break;
        }

        case NS(OBJECT_TYPE_INT32_ARRAY):
        {
            value_size = sizeof( SIXTRL_INT32_T );
            break;
        }

        case NS(OBJECT_TYPE_UINT16_ARRAY):
        {
            value_size = sizeof( SIXTRL_UINT16_T );
            break;
        }

        case NS(OBJECT_TYPE_INT16_ARRAY):
        {
            value_size = sizeof( SIXTRL_INT16_T );
            break;
        }

        case NS(OBJECT_TYPE_UINT8_ARRAY):
        {
            value_size = sizeof( SIXTRL_UINT8_T );
            break;
        }

        case NS(OBJECT_TYPE_INT8_ARRAY):
        {
            value_size = sizeof( SIXTRL_INT8_T );
            break;
        }

        case NS(OBJECT_TYPE_CSTRING):
        {
            value_size = sizeof( 1 );
        }

        default:
        {
            value_size = ( NS(buffer_size_t) )0u;
        }
    };

    return value_size;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC unsigned char const*
NS(BinaryArray_buffer_index_const_begin)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    const NS(Object) *const SIXTRL_RESTRICT bin_array )
{
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* begin = SIXTRL_NULLPTR;

    NS(buffer_size_t) const value_size = NS(BinaryArray_value_size)(
        NS(BinaryArray_buffer_index_type_id)( bin_array ) );

    if( ( value_size > ( NS(buffer_size_t) )0u ) &&
        ( value_size <= NS(Object_get_size)( bin_array ) ) )
    {
        begin = ( SIXTRL_BUFFER_DATAPTR_DEC unsigned char const*
            )NS(Object_get_begin_addr)( bin_array );
    }

    return begin;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC unsigned char*
NS(BinaryArray_buffer_index_begin)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT bin_array )
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC unsigned char*
        )NS(BinaryArray_buffer_index_const_begin)( bin_array );
}


SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)
NS(BinaryArray_buffer_index_num_values)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    const NS(Object) *const SIXTRL_RESTRICT bin_array )
{
    NS(buffer_size_t) num_values = ( NS(buffer_size_t) )0u;
    NS(buffer_size_t) const array_size = NS(Object_get_size)( bin_array );
    NS(buffer_size_t) const value_size = NS(BinaryArray_get_value_size)(
        NS(BinaryArray_buffer_index_type_id)( bin_array ) );

    if( ( value_size > ( NS(buffer_size_t) )0u ) &&
        ( value_size <= array_size ) )
    {
        num_values = array_size / value_size;
    }

    return num_values;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(object_type_id_t) NS(BinaryArray_managed_buffer_type_id)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(BinaryArray_buffer_index_type_id)(
        NS(ManagedBuffer_get_const_object)( buffer_begin, index, slot_size ) );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC unsigned char const*
NS(BinaryArray_managed_buffer_const_begin)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(BinaryArray_buffer_index_const_begin)(
        NS(ManagedBuffer_get_const_object)( buffer_begin, index, slot_size ) );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC unsigned char*
NS(BinaryArray_managed_buffer_begin)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(BinaryArray_buffer_index_begin)(
        NS(ManagedBuffer_get_object)( buffer_begin, index, slot_size ) );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)
NS(BinaryArray_managed_buffer_num_values)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(BinaryArray_buffer_index_num_values)(
        NS(ManagedBuffer_get_const_object)( buffer_begin, index, slot_size ) );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(buffer_size_t)
NS(BinaryArray_buffer_index_get_num_dataptrs)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT array )
{
    ( void )array;
    return ( NS(buffer_size_t) )0u;
}

SIXTRL_INLINE NS(buffer_size_t)
NS(BinaryArray_buffer_index_get_num_slots)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT array,
    NS(buffer_size_t) const slot_size )
{
    NS(buffer_size_t) num_slots = ( NS(buffer_size_t) )0u;

    NS(buffer_size_t) const array_size = NS(Object_get_size)( array );
    NS(buffer_size_t) const value_size =
        NS(BinaryArray_buffer_index_type_id)( array );

    if( ( value_size > ( NS(buffer_size_t) )0u ) &&
        ( slot_size  > ( NS(buffer_size_t) )0u ) &&
        ( array_size >= value_size ) && ( array_size >= slot_size ) &&
        ( ( array_size % slot_size ) == ( NS(buffer_size_t) )0u ) )
    {
        num_slots = array_size / slot_size;
    }

    return num_slots;
}

#if !defined( _GPUCODE )

SIXTRL_INLINE NS(object_type_id_t) NS(BinaryArray_buffer_type_id)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index )
{
    return NS(BinaryArray_buffer_index_type_id)(
        NS(Buffer_get_const_object)( buffer, index ) );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC unsigned char const*
NS(BinaryArray_buffer_const_begin)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index )
{
    return NS(BinaryArray_buffer_index_const_begin)(
        NS(Buffer_get_const_object)( buffer, index ) );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC unsigned char*
NS(BinaryArray_buffer_begin)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index )
{
    return NS(BinaryArray_buffer_index_begin)(
        NS(Buffer_get_object)( buffer, index ) );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)
NS(BinaryArray_buffer_num_values)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index )
{
    return NS(BinaryArray_buffer_index_num_values)(
        NS(Buffer_get_const_object)( buffer, index ) );
}

SIXTRL_INLINE bool NS(BinaryArray_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(object_type_id_t) const type_id, NS(buffer_size_t) const num_values,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_dataptrs )
{
    NS(buffer_size_t) const value_size = NS(BinaryArray_value_size)( type_id );
    NS(buffer_size_t) const slot_size  = NS(Buffer_get_slot_size)( buffer );
    NS(buffer_size_t) const array_size =
        NS(ManagedBuffer_get_slot_based_length)( value_size * num_values );

    NS(buffer_size_t) const num_dataptrs =
        NS(BinaryArray_buffer_index_get_num_dataptrs)( SIXTRL_NULLPTR );

    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* sizes   = SIXTRL_NULLPTR;
    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* counts  = SIXTRL_NULLPTR;

    SIXTRL_ASSERT( num_dataptrs == ( NS(buffer_size_t) )0u );
    SIXTRL_ASSERT( slot_size  > ( NS(buffer_size_t) )0u );
    SIXTRL_ASSERT( value_size > ( NS(buffer_size_t) )0u );
    SIXTRL_ASSERT( num_values > ( NS(buffer_size_t) )0u );
    SIXTRL_ASSERT( array_size >= ( num_values * value_size ) );
    SIXTRL_ASSERT( array_size >= slot_size );
    SIXTRL_ASSERT( ( array_size % slot_size ) == ( NS(buffer_size_t) )0u );

    return NS(Buffer_can_add_object)( buffer, array_size, num_dataptrs, sizes,
        counts, requ_objects, requ_slots, requ_dataptrs );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC void* NS(BinaryArray_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(object_type_id_t) const type_id, NS(buffer_size_t) const num_values )
{
    return NS(BinaryArray_add)( buffer, type_id, num_values, SIXTRL_NULLPTR );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC void* NS(BinaryArray_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(object_type_id_t) const type_id, NS(buffer_size_t) const num_values,
    SIXTRL_ARGPTR_DEC const void *const SIXTRL_RESTRICT data_begin )
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC void* ptr_array_t;

    ptr_array_t buffer_array_begin = SIXTRL_NULLPTR;
    SIXTRL_ARGPTR_DEC void const* array_begin = data_begin;

    NS(buffer_size_t) const value_size =
        NS(BinaryArray_value_size)( type_id );

    NS(buffer_size_t) const slot_size =
        NS(Buffer_get_slot_size)( buffer );

    NS(buffer_size_t) const array_size =
        NS(ManagedBuffer_get_slot_based_length)( value_size * num_values );

    NS(buffer_size_t) const num_dataptrs =
        NS(BinaryArray_buffer_index_get_num_dataptrs)( SIXTRL_NULLPTR );

    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* offsets = SIXTRL_NULLPTR;
    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* sizes   = SIXTRL_NULLPTR;
    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* counts  = SIXTRL_NULLPTR;

    SIXTRL_ASSERT( num_dataptrs == ( NS(buffer_size_t) )0u );
    SIXTRL_ASSERT( slot_size  > ( NS(buffer_size_t) )0u );
    SIXTRL_ASSERT( value_size > ( NS(buffer_size_t) )0u );
    SIXTRL_ASSERT( num_values > ( NS(buffer_size_t) )0u );
    SIXTRL_ASSERT( array_size >= ( num_values * value_size ) );
    SIXTRL_ASSERT( array_size >= slot_size );
    SIXTRL_ASSERT( ( array_size % slot_size ) == ( NS(buffer_size_t) )0u );

    if( ( data_begin == SIXTRL_NULLPTR ) &&
        ( array_size > ( NS(buffer_size_t) )0u ) )
    {
        array_begin = ( void const* )malloc( array_size );

        if( array_begin != SIXTRL_NULLPTR )
        {
            SIXTRACKLIB_SET_VALUES( unsigned char, array_begin, array_size,
                ( unsigned char )0 );
        }
    }

    buffer_array_begin = ( ptr_array_t )( uintptr_t )NS(Object_get_begin_addr)(
        NS(Buffer_add_object)( buffer, array_begin, array_size, type_id,
            num_dataptrs, offsets, sizes, counts ) );

    if( data_begin == SIXTRL_NULLPTR )
    {
        free( array_begin );
        array_begin = SIXTRL_NULLPTR;
    }

    return buffer_array_begin;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC void* NS(BinarayArray_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT orig )
{
    return NS(BinaryArray_add)( buffer,
        NS(BinaryArray_buffer_index_type_id)( orig ),
        NS(BinaryArray_buffer_index_num_values)( orig ),
        NS(BinaryArray_buffer_index_const_begin)( orig ) );
}

#endif /* !defined( _GPUCODE ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_BINARY_ARRAY_OBJECT_C99_H__*/
/* end: */
