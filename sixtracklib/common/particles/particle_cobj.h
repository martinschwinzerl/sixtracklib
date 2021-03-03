#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_COBJ_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_COBJ_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    NS(particle_real_type)  const x,       NS(particle_real_type)  const y,
    NS(particle_real_type)  const px,      NS(particle_real_type)  const py,
    NS(particle_real_type)  const zeta,    NS(particle_real_type)  const delta,
    NS(particle_index_type) const state,
    NS(particle_index_type) const at_element,
    NS(particle_index_type) const at_turn, NS(particle_index_type) const id,
    NS(particle_real_type)  const psigma,  NS(particle_real_type)  const rpp,
    NS(particle_real_type)  const rvv,     NS(particle_real_type)  const chi,
    NS(particle_real_type)  const charge_ratio,
    NS(particle_real_type)  const charge0, NS(particle_real_type)  const mass0,
    NS(particle_real_type)  const beta0,   NS(particle_real_type)  const gamma0,
    NS(particle_real_type)  const p0c,     NS(particle_real_type)  const s
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(particle_real_type)  const x,       NS(particle_real_type)  const y,
    NS(particle_real_type)  const px,      NS(particle_real_type)  const py,
    NS(particle_real_type)  const zeta,    NS(particle_real_type)  const delta,
    NS(particle_index_type) const state,
    NS(particle_index_type) const at_element,
    NS(particle_index_type) const at_turn, NS(particle_index_type) const id,
    NS(particle_real_type)  const psigma,  NS(particle_real_type)  const rpp,
    NS(particle_real_type)  const rvv,     NS(particle_real_type)  const chi,
    NS(particle_real_type)  const charge_ratio,
    NS(particle_real_type)  const charge0, NS(particle_real_type)  const mass0,
    NS(particle_real_type)  const beta0,   NS(particle_real_type)  const gamma0,
    NS(particle_real_type)  const p0c,     NS(particle_real_type)  const s );


SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT orig );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Particle_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cbuffer_new_ext)( SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)*
    SIXTRL_RESTRICT buffer ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particle_real_type)  const x,       NS(particle_real_type)  const y,
    NS(particle_real_type)  const px,      NS(particle_real_type)  const py,
    NS(particle_real_type)  const zeta,    NS(particle_real_type)  const delta,
    NS(particle_index_type) const state,   NS(particle_index_type) const at_element,
    NS(particle_index_type) const at_turn, NS(particle_index_type) const id,
    NS(particle_real_type)  const psigma,  NS(particle_real_type)  const rpp,
    NS(particle_real_type)  const rvv,     NS(particle_real_type)  const chi,
    NS(particle_real_type)  const charge_ratio,
    NS(particle_real_type)  const charge0, NS(particle_real_type)  const mass0,
    NS(particle_real_type)  const beta0,   NS(particle_real_type)  const gamma0,
    NS(particle_real_type)  const p0c,     NS(particle_real_type)  const s
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT;

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

SIXTRL_INLINE bool NS(Particle_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT {
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return NS(CObjFlatBuffer_can_add_copy_of_trivial_object)( buffer, slot_size,
        NS(Particle_cobj_reserved_handle_size)( slot_size ), requ_buffer_size,
            requ_objects, requ_slots, requ_dataptrs );

    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    ( void )buffer;
    ( void )slot_size;
    ( void )requ_buffer_size;
    ( void )requ_slots;
    ( void )requ_objects;
    ( void )requ_dataptrs;
    return false;

    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) p;
    NS(Particle_clear)( &p );
    return NS(Particle_cobj_flat_buffer_add_copy)( buffer, slot_size, &p );
}

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particle_real_type)  const x,       NS(particle_real_type)  const y,
    NS(particle_real_type)  const px,      NS(particle_real_type)  const py,
    NS(particle_real_type)  const zeta,    NS(particle_real_type)  const delta,
    NS(particle_index_type) const state,
    NS(particle_index_type) const at_element,
    NS(particle_index_type) const at_turn, NS(particle_index_type) const id,
    NS(particle_real_type)  const psigma,  NS(particle_real_type)  const rpp,
    NS(particle_real_type)  const rvv,     NS(particle_real_type)  const chi,
    NS(particle_real_type)  const charge_ratio,
    NS(particle_real_type)  const charge0, NS(particle_real_type)  const mass0,
    NS(particle_real_type)  const beta0,   NS(particle_real_type)  const gamma0,
    NS(particle_real_type)  const p0c,
    NS(particle_real_type)  const s )  SIXTRL_NOEXCEPT {
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) p;
    NS(Particle_init)( &p, x, y, px, py, zeta, delta, state, at_element,
                       at_turn, id, psigma, rpp, rvv, chi, charge_ratio,
                       charge0, mass0, beta0, gamma0, p0c, s );
    return NS(Particle_cobj_flat_buffer_add_copy)( buffer, slot_size, &p );
}

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* added_elem = SIXTRL_NULLPTR;
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                (  SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )

    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* OFFSETS = SIXTRL_NULLPTR;
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIZES   = SIXTRL_NULLPTR;
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* COUNTS  = SIXTRL_NULLPTR;
    SIXTRL_ASSERT( NS(Particle_cobj_num_dataptrs)() == ( NS(size_type) )0u );
    added_elem = ( SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* )( uintptr_t
        )NS(CObjIndex_begin_addr)(
            NS(CObjFlatBuffer_add_copy_of_object_detailed)( buffer, slot_size, p,
                NS(Particle_cobj_reserved_handle_size)( slot_size ),
                NS(Particle_cobj_actual_handle_size)( slot_size ),
                NS(Particle_cobj_type_id)(), NS(Particle_cobj_num_dataptrs)(),
                OFFSETS, SIZES, COUNTS, true ) );

    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    ( void )buffer;
    ( void )slot_size;
    ( void )p;

    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return added_elem; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(Particle_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT {
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    typedef NS(cobj_size_type) st_size_t;
    st_size_t const slot_size = NS(CBuffer_slot_size)( buffer );
    SIXTRL_ASSERT( NS(Particle_cobj_num_dataptrs)() == ( st_size_t )0u );
    return NS(CBuffer_can_add_copy_of_trivial_object)( buffer,
        NS(Particle_cobj_reserved_handle_size)( slot_size ),
            requ_buffer_size, requ_slots, requ_objects, requ_dataptrs ); }

    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    ( void )buffer;
    ( void )requ_buffer_size;
    ( void )requ_slots;
    ( void )requ_objects;
    ( void )requ_dataptrs;
    return false; }

    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)* NS(Particle_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(Particle) p;
    NS(Particle_clear)( &p );
    return NS(Particle_cbuffer_add_copy)( b, &p ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)* NS(Particle_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particle_real_type)  const x,       NS(particle_real_type)  const y,
    NS(particle_real_type)  const px,      NS(particle_real_type)  const py,
    NS(particle_real_type)  const zeta,    NS(particle_real_type)  const delta,
    NS(particle_index_type) const state,
    NS(particle_index_type) const at_element,
    NS(particle_index_type) const at_turn, NS(particle_index_type) const id,
    NS(particle_real_type)  const psigma,  NS(particle_real_type)  const rpp,
    NS(particle_real_type)  const rvv,     NS(particle_real_type)  const chi,
    NS(particle_real_type)  const charge_ratio,
    NS(particle_real_type)  const charge0, NS(particle_real_type)  const mass0,
    NS(particle_real_type)  const beta0,   NS(particle_real_type)  const gamma0,
    NS(particle_real_type)  const p0c,     NS(particle_real_type)  const s ) {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(Particle) p;
    NS(Particle_init)( &p, x, y, px, py, zeta, delta, state, at_element,
                       at_turn, id, psigma, rpp, rvv, chi, charge_ratio,
                       charge0, mass0, beta0, gamma0, p0c, s );
    return NS(Particle_cbuffer_add_copy)( buffer, &p ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT orig ){
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    NS(cobj_size_type) const slot_size = NS(CBuffer_slot_size)( buffer );
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* OFFSETS = SIXTRL_NULLPTR;
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIZES   = SIXTRL_NULLPTR;
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* COUNTS  = SIXTRL_NULLPTR;
    SIXTRL_ASSERT( NS(Particle_cobj_num_dataptrs)() == ( NS(cobj_size_type) )0 );

    return ( SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* )( uintptr_t
        )NS(CObjIndex_begin_addr)( NS(CBuffer_add_copy_of_object_detailed)(
            buffer, orig, NS(Particle_cobj_reserved_handle_size)( slot_size ),
            NS(Particle_cobj_actual_handle_size)( slot_size ),
            NS(Particle_cobj_type_id)(), NS(Particle_cobj_num_dataptrs)(),
            OFFSETS, SIZES, COUNTS, true ) ); }

    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    ( void )buffer;
    ( void )orig;
    return SIXTRL_NULLPTR; }

    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_COBJ_H__ */
