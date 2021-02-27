#ifndef SIXTRACKLIB_COMMON_COBJECTS_COBJ_INDEX_OBJECT_C99_H__
#define SIXTRACKLIB_COMMON_COBJECTS_COBJ_INDEX_OBJECT_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdio.h>
    #include <string.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(CObjIndex)
{
    NS(cobj_addr_type)   begin_addr  SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(cobj_obj_id_type) type_id     SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(cobj_size_type)   size        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(CObjIndex);

typedef SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* NS(cobj_obj_index_pointer);
typedef SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const*
        NS(cobj_obj_index_const_pointer);

typedef SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(cobj_raw_type)*
        NS(cobj_obj_index_data_pointer);

typedef SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(cobj_raw_type) const*
        NS(cobj_obj_index_data_const_pointer);

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(CObjIndex)                    CObjIndex;
    typedef ::NS(cobj_obj_index_pointer)       cobj_obj_index_pointer;
    typedef ::NS(cobj_obj_index_const_pointer) cobj_obj_index_const_pointer;
    typedef ::NS(cobj_obj_index_data_pointer)  cobj_obj_index_data_pointer;

    typedef ::NS(cobj_obj_index_data_const_pointer)
            cobj_obj_index_data_const_pointer;
}
#endif /* defined( __cplusplus ) */

/* ========================================================================= */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_index_pointer) NS(CObjIndex_preset)(
    NS(cobj_obj_index_pointer) SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CObjIndex_begin_addr)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT
        index_obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CObjIndex_set_begin_addr)(
    NS(cobj_obj_index_pointer) SIXTRL_RESTRICT index_obj,
    NS(cobj_addr_type) const begin_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN  NS(cobj_obj_id_type) NS(CObjIndex_type_id)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CObjIndex_set_type_id)(
    NS(cobj_obj_index_pointer) SIXTRL_RESTRICT index_obj,
    NS(cobj_obj_id_type) const type_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN  NS(cobj_size_type) NS(CObjIndex_size)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN  void NS(CObjIndex_set_size)(
    NS(cobj_obj_index_pointer) SIXTRL_RESTRICT index_obj,
    NS(cobj_size_type) const size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_consistent_with_type)(
    NS(cobj_obj_index_const_pointer) SIXTRL_RESTRICT index_obj,
    NS(cobj_obj_id_type) const required_type_id,
    NS(cobj_size_type) const min_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjIndex_begin_addr_filter_by_type_info)(
    NS(cobj_obj_index_const_pointer) SIXTRL_RESTRICT index_obj,
    NS(cobj_obj_id_type) const required_type_id,
    NS(cobj_size_type) const min_size,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_index_data_const_pointer)
NS(CObjIndex_ptr_const_begin)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const
    NS(CObjIndex) *const SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_index_data_pointer) NS(CObjIndex_ptr_begin)(
    NS(cobj_obj_index_pointer) SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CObjIndex_set_ptr_begin)(
    NS(cobj_obj_index_pointer) SIXTRL_RESTRICT index_obj,
    NS(cobj_obj_index_data_pointer) SIXTRL_RESTRICT begin_ptr ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(CObjIndex_print_slots)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT
        index_obj, NS(cobj_size_type) const num_slots_to_print );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(CObjIndex_fprint_slots)(
    FILE* SIXTRL_RESTRICT fp,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT
        index_obj, NS(cobj_size_type) const num_slots_to_print );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(CObjIndex_is_consistent_with_type_ext)(
    NS(cobj_obj_index_const_pointer) SIXTRL_RESTRICT index_obj,
    NS(cobj_obj_id_type) const required_type_id,
    NS(cobj_size_type) const min_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_addr_type)
NS(CObjIndex_begin_addr_filter_by_type_info_ext)(
    NS(cobj_obj_index_const_pointer) SIXTRL_RESTRICT index_obj,
    NS(cobj_obj_id_type) const required_type_id,
    NS(cobj_size_type) const min_size,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* *
 * *****         Implementation of inline functions and methods        ***** *
 * ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/address_manipulations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && !defined( _GPUCODE )
    #if !defined( __cplusplus )
        #include <stdio.h>
    #else /* C */
        #include <cstdio>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cobj_obj_index_pointer) NS(CObjIndex_preset)(
    NS(cobj_obj_index_pointer) SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT {
    if( index_obj != SIXTRL_NULLPTR ) {
        NS(CObjIndex_set_begin_addr)( index_obj, 0u );
        NS(CObjIndex_set_type_id)( index_obj, 0u );
        NS(CObjIndex_set_size)( index_obj, 0u ); }
    return index_obj; }

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjIndex_begin_addr)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( index_obj != SIXTRL_NULLPTR );
    SIXTRL_ASSERT(
        ( sizeof( NS(cobj_raw_type) const* ) >= sizeof( NS(cobj_addr_type) ) ) ||
        ( ( sizeof( NS(cobj_raw_type) const* ) == 4u ) &&
          ( sizeof( NS(cobj_addr_type) ) == 8u ) &&
          ( NS(cobj_addr_type) )NS(CObjFlatBuffer_limit_offset_max)() >
                index_obj->begin_addr ) );
    return index_obj->begin_addr; }

SIXTRL_INLINE void NS(CObjIndex_set_begin_addr)(
    NS(cobj_obj_index_pointer) SIXTRL_RESTRICT index_obj,
    NS(cobj_addr_type) const begin_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT(
        ( sizeof( NS(cobj_raw_type) const* ) >= sizeof( NS(cobj_addr_type) ) ) ||
        ( ( sizeof( NS(cobj_raw_type) const* ) == 4u ) &&
          ( sizeof( NS(cobj_addr_type) ) == 8u ) &&
          ( ( NS(cobj_addr_type)  )NS(CObjFlatBuffer_limit_offset_max)() >
              begin_addr ) ) );
    if( index_obj != SIXTRL_NULLPTR ) index_obj->begin_addr = begin_addr; }

SIXTRL_INLINE NS(cobj_obj_id_type) NS(CObjIndex_type_id)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( index_obj != SIXTRL_NULLPTR );
    return index_obj->type_id; }

SIXTRL_INLINE void NS(CObjIndex_set_type_id)(
    NS(cobj_obj_index_pointer) SIXTRL_RESTRICT index_obj,
    NS(cobj_obj_id_type) const type_id ) SIXTRL_NOEXCEPT {
    if( index_obj != SIXTRL_NULLPTR ) index_obj->type_id = type_id; }

SIXTRL_INLINE NS(cobj_size_type) NS(CObjIndex_size)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( index_obj != SIXTRL_NULLPTR );
    return index_obj->size; }

SIXTRL_INLINE void NS(CObjIndex_set_size)(
    NS(cobj_obj_index_pointer) SIXTRL_RESTRICT index_obj,
    NS(cobj_size_type) const size ) SIXTRL_NOEXCEPT {
    if( index_obj != SIXTRL_NULLPTR ) index_obj->size = size; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_consistent_with_type)(
    NS(cobj_obj_index_const_pointer) SIXTRL_RESTRICT obj,
    NS(cobj_obj_id_type) const requ_type_id,
    NS(cobj_size_type) const min_size ) SIXTRL_NOEXCEPT {
    #if !defined( SIXTRL_DEBUG_MODE )
    SIXTRL_ASSERT( requ_type_id != (
        NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_ILLEGAL );
    SIXTRL_ASSERT( requ_type_id != (
        NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_UNDEFINED );
    SIXTRL_ASSERT( min_size > ( NS(cobj_size_type) )0u );
    SIXTRL_ASSERT( ( obj == SIXTRL_NULLPTR ) ||
                   ( requ_type_id != NS(CObjIndex_type_id)( obj ) ) ||
                   ( min_size <= NS(CObjIndex_size)( obj ) ) );
    ( void )min_size;
    return ( ( obj != SIXTRL_NULLPTR ) &&
             ( NS(CObjIndex_type_id)( obj ) == requ_type_id ) );
    #else /* defined( SIXTRL_DEBUG_MODE ) */
    return ( ( obj != SIXTRL_NULLPTR ) &&
             ( requ_type_id != ( NS(cobj_obj_id_type)
                 )SIXTRL_COBJECTS_TYPE_ID_ILLEGAL ) &&
             ( requ_type_id != ( NS(cobj_obj_id_type)
                 )SIXTRL_COBJECTS_TYPE_ID_UNDEFINED ) &&
             ( NS(CObjIndex_type_id)( obj ) == requ_type_id ) &&
             ( NS(CObjIndex_size)( obj ) >= min_size ) );
    #endif /* !defined( SIXTRL_DEBUG_MODE ) */
}

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjIndex_begin_addr_filter_by_type_info)(
    NS(cobj_obj_index_const_pointer) SIXTRL_RESTRICT obj,
    NS(cobj_obj_id_type) const type_id, NS(cobj_size_type) const min_size,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return ( ( NS(CObjIndex_is_consistent_with_type)(obj,type_id,min_size) ) &&
             ( slot_size > ( NS(cobj_size_type) )0u ) &&
             ( NS(CObjIndex_size)( obj ) % slot_size == (
                NS(cobj_size_type) )0u ) )
    ? NS(CObjIndex_begin_addr)( obj ) : ( NS(cobj_addr_type) )SIXTRL_NULL_ADDR;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_obj_index_data_const_pointer)
NS(CObjIndex_ptr_const_begin)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const
    NS(CObjIndex) *const SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_obj_index_data_const_pointer) )( uintptr_t
        )NS(CObjIndex_begin_addr)( index_obj ); }

SIXTRL_INLINE NS(cobj_obj_index_data_pointer) NS(CObjIndex_ptr_begin)(
    NS(cobj_obj_index_pointer) SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_obj_index_data_pointer) )NS(CObjIndex_ptr_const_begin)(
        index_obj ); }

SIXTRL_INLINE void NS(CObjIndex_set_ptr_begin)(
    NS(cobj_obj_index_pointer) SIXTRL_RESTRICT index_obj,
    NS(cobj_obj_index_data_pointer) SIXTRL_RESTRICT begin_ptr ) SIXTRL_NOEXCEPT {
    NS(CObjIndex_set_begin_addr)( index_obj, ( NS(cobj_addr_type) )(
        uintptr_t )begin_ptr ); }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(CObjIndex_print_slots)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj, NS(cobj_size_type) const num_slots_to_print )
{
    typedef NS(cobj_addr_type) st_addr_type;
    typedef NS(cobj_size_type) st_size_type;
    typedef NS(cobj_obj_id_type) st_obj_id_type;
    typedef SIXTRL_CBUFFER_OBJ_DATAPTR_DEC st_addr_type const* addr_pointer_type;

    st_obj_id_type const type_id = NS(CObjIndex_type_id)( index_obj );
    st_size_type const slot_size = ( st_size_type
        )SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE;

    st_size_type const obj_size  = NS(CObjIndex_size)( index_obj );
    st_size_type const num_slots = obj_size / slot_size;
    addr_pointer_type ptr_slots  = ( addr_pointer_type )( uintptr_t
        )NS(CObjIndex_begin_addr)( index_obj );

    st_size_type ii = ( st_size_type )0u;
    st_size_type nn = num_slots;

    if( ( num_slots_to_print > ( st_size_type )0u ) &&
        ( num_slots_to_print < num_slots ) ) {
        nn = num_slots_to_print; }

    printf( "type_id            : %8d\r\n", ( int )type_id );
    printf( "obj size           : %8d\r\n", ( int )obj_size );
    printf( "num_slots          : %8d\r\n", ( int )num_slots );
    printf( "num_slots to print : %8d\r\n", ( int )nn );

    for( ; ii < nn ; ++ii )
    {
        if( ii < ( st_size_type )21u )
        {
            printf( "slot_id = %8lu | slot addr = %20lu "
                    "| slot_value = %20lu\r\n",
                    ( unsigned long )ii, ( unsigned long )&ptr_slots[ ii ],
                    ( unsigned long )ptr_slots[ ii ] );
        }
        else
        {
            printf( "slot_id = %8lu | slot addr = %20lu "
                    "| slot_value = %+19.12f\r\n",
                    ( unsigned long )ii, ( unsigned long )&ptr_slots[ ii ],
                    *( ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC double const*
                        )&ptr_slots[ ii ] ) );
        }
    }
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ------------------------------------------------------------------------- */

#if defined( __cplusplus )
#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/cobj_type_traits.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(CObjIndex) CObjIndex;

    template< class E >
    SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
         typename CObjectsStoreResultTypeTraits< E >::const_pointer >::type
    CObjIndex_to_elem(
        ::NS(cobj_obj_index_const_pointer) const
            SIXTRL_RESTRICT SIXTRL_UNUSED( obj ),
        ::NS(cobj_size_type) const SIXTRL_UNUSED( slot_size ) =
            ::NS(cobj_size_type){ SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE },
        typename CObjectsCopyArgTypeTraits< E >::const_pointer SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT {
        return nullptr; }

    template< class E >
    SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
         SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
         typename CObjectsStoreResultTypeTraits< E >::const_pointer >::type
    CObjIndex_to_elem(
        ::NS(cobj_obj_index_const_pointer) const SIXTRL_RESTRICT obj,
        ::NS(cobj_size_type) const slot_size = ::NS(cobj_size_type){
            SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE },
        typename CObjectsCopyArgTypeTraits< E >::const_pointer SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::CObjectsStoreResultTypeTraits< E >::const_pointer
                result_type;
        return ( ::NS(CObjIndex_is_consistent_with_type)( obj,
            st::CObjects_type_id< E >(),
            st::CObjects_reserved_handle_size< E >( slot_size ) ) )
            ? reinterpret_cast< result_type >( static_cast< uintptr_t >(
                ::NS(CObjIndex_begin_addr)( obj ) ) )
            : nullptr; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E >
    SIXTRL_FN SIXTRL_INLINE
    typename CObjectsStoreResultTypeTraits< E >::const_pointer
    CObjIndex_to_const_elem(
        ::NS(cobj_obj_index_pointer) const SIXTRL_RESTRICT obj,
        ::NS(cobj_size_type) const slot_size = ::NS(cobj_size_type){
            SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE },
        typename CObjectsCopyArgTypeTraits< E >::const_pointer SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjIndex_to_elem< E >(
            static_cast< ::NS(cobj_obj_index_const_pointer) >( obj ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E >
    SIXTRL_FN SIXTRL_INLINE typename CObjectsStoreResultTypeTraits< E >::pointer
    CObjIndex_to_elem(
        ::NS(cobj_obj_index_pointer) SIXTRL_RESTRICT obj,
        ::NS(cobj_size_type) const slot_size = ::NS(cobj_size_type){
            SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE },
        typename CObjectsCopyArgTypeTraits< E >::const_pointer SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::CObjectsStoreResultTypeTraits< E >::pointer
                result_type;

        return const_cast< result_type >( st::CObjIndex_to_elem< E >(
            static_cast< ::NS(cobj_obj_index_const_pointer) >( obj ) ) );
    }

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */


#endif /* SIXTRACKLIB_COMMON_COBJECTS_COBJ_INDEX_OBJECT_C99_H__ */
