#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MONITOR_MONITOR_COBJ_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MONITOR_MONITOR_COBJ_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/monitor/monitor.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    NS(particle_index_type) const num_stores,
    NS(particle_index_type) const start, NS(particle_index_type) const skip,
    NS(particle_index_type) const min_particle_id,
    NS(particle_index_type) const max_particle_id,
    NS(be_flags_type) const is_rolling, NS(be_flags_type) const is_turn_ordered,
    NS(be_addr_type) const out_addr )  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(particle_index_type) const num_stores,
    NS(particle_index_type) const start, NS(particle_index_type) const skip,
    NS(particle_index_type) const min_particle_id,
    NS(particle_index_type) const max_particle_id,
    NS(be_flags_type) const is_rolling, NS(be_flags_type) const is_turn_ordered,
    NS(be_addr_type) const out_addr  );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT orig );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Monitor_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(particle_index_type) const num_stores,
    NS(particle_index_type) const start, NS(particle_index_type) const skip,
    NS(particle_index_type) const min_particle_id,
    NS(particle_index_type) const max_particle_id,
    NS(be_flags_type) const is_rolling, NS(be_flags_type) const is_turn_ordered,
    NS(be_addr_type) const out_addr );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cobj_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT be_mon );

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE bool NS(Monitor_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_can_add_copy_of_trivial_object)( buffer, slot_size,
        NS(Monitor_cobj_reserved_handle_size)( slot_size ),
            requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_ARGPTR_DEC NS(Monitor) elem;
    NS(Monitor_clear)( &elem );
    return NS(Monitor_cobj_flat_buffer_add_copy)(
        buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size, NS(particle_index_type) const num_stores,
    NS(particle_index_type) const start, NS(particle_index_type) const skip,
    NS(particle_index_type) const min_particle_id,
    NS(particle_index_type) const max_particle_id,
    NS(be_flags_type) const is_rolling, NS(be_flags_type) const is_turn_ordered,
    NS(be_addr_type) const out_addr )  SIXTRL_NOEXCEPT {
    SIXTRL_BE_ARGPTR_DEC NS(Monitor) elem;
    NS(Monitor_init)( &elem, num_stores, start, skip, min_particle_id,
        max_particle_id, is_rolling, is_turn_ordered, out_addr );
    return NS(Monitor_cobj_flat_buffer_add_copy)(
        buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT {
    return NS(Monitor_from_cobj_index)(
        NS(CObjFlatBuffer_add_copy_of_trivial_object)(
            buffer, slot_size, orig,
            NS(Monitor_cobj_reserved_handle_size)( slot_size ),
            NS(Monitor_cobj_type_id)(), false ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Monitor_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(CBuffer_can_add_copy_of_trivial_object)( b,
    NS(Monitor_cobj_reserved_handle_size)( NS(CBuffer_slot_size)( b ) ),
        requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)* NS(Monitor_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    SIXTRL_BE_ARGPTR_DEC NS(Monitor) elem;
    NS(Monitor_clear)( &elem );
    return NS(Monitor_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)* NS(Monitor_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particle_index_type) const num_stores,
    NS(particle_index_type) const start, NS(particle_index_type) const skip,
    NS(particle_index_type) const min_particle_id,
    NS(particle_index_type) const max_particle_id,
    NS(be_flags_type) const is_rolling,
    NS(be_flags_type) const is_turn_ordered,
    NS(be_addr_type) const out_addr ) {
    SIXTRL_BE_ARGPTR_DEC NS(Monitor) elem;
    NS(status_type) const status = NS(Monitor_init)( &elem, num_stores,
        start, skip, min_particle_id, max_particle_id, is_rolling,
            is_turn_ordered, out_addr );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(Monitor_cbuffer_add_copy)( buffer, &elem )
        : SIXTRL_NULLPTR;
    }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT orig ) {
    NS(cobj_size_type) const slot_size = NS(CBuffer_slot_size)( buffer );
    return NS(Monitor_from_cobj_index)(
        NS(CBuffer_add_copy_of_trivial_object)( buffer, orig,
            NS(Monitor_cobj_reserved_handle_size)( slot_size ),
            NS(Monitor_cobj_type_id)(), false ) ); }

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MONITOR_MONITOR_COBJ_H__  */
