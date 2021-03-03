#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLES_COBJ_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLES_COBJ_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/particles/particles.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_cobj_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT offsets,
    NS(size_type) const max_num_offsets,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_cobj_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT counts,
    NS(size_type) const max_num_counts,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_cobj_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT sizes,
    NS(size_type) const max_num_sizes,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(Particles_cobj_required_num_bytes)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(Particles_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN bool NS(Particles_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(particles_num_type) const max_num_particles,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
);

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles) const*
NS(Particles_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Particles_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(particles_num_type) const max_num_particles,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p );

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

SIXTRL_INLINE NS(status_type) NS(Particles_cobj_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT offsets,
    NS(size_type) const max_num_offsets,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(Particles_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;
    if( ( p != SIXTRL_NULLPTR ) && ( offsets != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_offsets >= ndataptrs ) &&
        ( ndataptrs == ( st_size_t )SIXTRL_PARTICLES_NUM_DATAPTRS ) ) {

        st_size_t const first_offset = ( st_size_t )2 *
            NS(CObjFlatBuffer_slot_based_size)( sizeof( NS(particles_num_type) ),
                slot_size );

        st_size_t const addr_field_extent = NS(CObjFlatBuffer_slot_based_size)(
            sizeof( NS(particles_addr_type) ), slot_size );

        for( ; ii < ndataptrs ; ++ii )
            offsets[ ii ] = first_offset + ii * addr_field_extent;

        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

    if( ( offsets != SIXTRL_NULLPTR ) &&
        ( max_num_offsets > ( st_size_t )0u ) && ( ii < max_num_offsets ) ) {
        while( ii < max_num_offsets ) { offsets[ ii++ ] = ( st_size_t )0u; } }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Particles_cobj_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT counts,
    NS(size_type) const max_num_counts,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(Particles_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;

    if( ( p != SIXTRL_NULLPTR ) && ( counts != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_counts >= ndataptrs ) )
    {
        NS(particles_num_type) const npart_i =
            NS(Particles_max_num_particles)( p );

        st_size_t const npart = ( npart_i >= 0 )
            ? ( st_size_t )npart_i : ( st_size_t )0u;

        if( ndataptrs == ( st_size_t )SIXTRL_PARTICLES_NUM_DATAPTRS ) {
            for( ; ii < ndataptrs ; ++ii ){ counts[ ii ] = npart; }
            status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    }

    if( ( counts != SIXTRL_NULLPTR ) && ( ii < max_num_counts ) &&
        ( max_num_counts > ( st_size_t )0u ) ) {
        while( ii < max_num_counts ){ counts[ ii++ ] = ( st_size_t )0; } }

    return status; }


SIXTRL_INLINE NS(status_type) NS(Particles_cobj_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT sizes,
    NS(size_type) const max_num_sizes,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(Particles_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;

    if( ( p != SIXTRL_NULLPTR ) && ( sizes != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_sizes >= ndataptrs ) ) {
        st_size_t const NPTRS_REAL = ( st_size_t
            )SIXTRL_PARTICLES_NUM_REAL_DATAPTRS;

        st_size_t const NPTRS_INDEX = (
            st_size_t )SIXTRL_PARTICLES_NUM_INDEX_DATAPTRS;

        if( ndataptrs == ( NPTRS_REAL + NPTRS_INDEX ) ) {
            st_size_t const real_size = sizeof( NS(particle_real_type) );
            st_size_t const index_size = sizeof( NS(particle_index_type) );
            st_size_t jj = ( st_size_t )0u;
            for( ; ii < NPTRS_REAL  ; ++ii ) { sizes[ ii ] = real_size; }
            for( ; jj < NPTRS_INDEX ; ++jj, ++ii ) { sizes[ ii ] = index_size; }
            status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    }

    if( ( sizes != SIXTRL_NULLPTR ) &&
        ( max_num_sizes >= ( st_size_t )0 ) && ( ii < max_num_sizes ) ) {
        for( ; ii < max_num_sizes ; ++ii ) { sizes[ ii ] = ( st_size_t )0u; } }

    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(cobj_size_type) NS(Particles_cobj_required_num_bytes)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {

    NS(cobj_size_type) num_bytes = ( NS(cobj_size_type) )0u;
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) SIZES[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) COUNTS[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_ASSERT( NS(Particles_cobj_num_dataptrs)() ==
                   ( NS(cobj_size_type) )SIXTRL_PARTICLES_NUM_DATAPTRS );
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;

    status = NS(Particles_cobj_attributes_sizes)(
        &SIZES[ 0 ], NS(Particles_cobj_num_dataptrs)(), pset, slot_size );

    if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        status = NS(Particles_cobj_attributes_counts)(
            &COUNTS[ 0 ], NS(Particles_cobj_num_dataptrs)(), pset, slot_size );

    if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        num_bytes = NS(CObjFlatBuffer_predict_required_num_bytes)(
            NS(Particles_cobj_reserved_handle_size)( slot_size ),
            NS(Particles_cobj_num_dataptrs)(),
            &SIZES[ 0 ], &COUNTS[ 0 ], slot_size );

    return num_bytes; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE bool NS(Particles_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT b,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_t;
    bool can_be_added = false;
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) pset;
    NS(Particles_clear)( &pset );
    NS(Particles_set_max_num_particles)( &pset, max_num_particles );
    NS(Particles_set_num_particles)( &pset, max_num_particles );

    if( ( max_num_particles >= ( NS(particles_num_type) )0u ) &&
        ( b != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_t )0u ) ) {
        SIXTRL_ARGPTR_DEC st_size_t SIZES[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
        SIXTRL_ARGPTR_DEC st_size_t COUNTS[ SIXTRL_PARTICLES_NUM_DATAPTRS ];

        NS(cobj_status_type) status = NS(Particles_cobj_attributes_sizes)(
            &SIZES[ 0 ], NS(Particles_cobj_num_dataptrs)(), &pset, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(Particles_cobj_attributes_counts)( &COUNTS[ 0 ],
                NS(Particles_cobj_num_dataptrs)(), &pset, slot_size );

        SIXTRL_ASSERT( NS(Particles_cobj_num_dataptrs)() ==
            ( st_size_t )SIXTRL_PARTICLES_NUM_DATAPTRS );

        can_be_added = NS(CObjFlatBuffer_can_add_copy_of_object)( b, slot_size,
            NS(Particles_cobj_reserved_handle_size)( slot_size ),
            NS(Particles_cobj_num_dataptrs)(), &SIZES[ 0 ], &COUNTS[ 0 ],
            requ_buffer_size, requ_slots, requ_objects, requ_dataptrs ); }

    return can_be_added; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles ) SIXTRL_NOEXCEPT {
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) pset;
    NS(Particles_clear)( &pset );
    NS(Particles_set_max_num_particles)( &pset, max_num_particles );
    NS(Particles_set_num_particles)( &pset, max_num_particles );
    return NS(Particles_cobj_flat_buffer_add_copy)( buffer, slot_size, &pset );
}

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr ) SIXTRL_NOEXCEPT {
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) pset;
    NS(Particles_init_with_pointers)( &pset, max_num_particles, num_particles,
        charge0_ptr, mass0_ptr, beta0_ptr, gamma0_ptr, p0c_ptr, s_ptr, x_ptr,
            y_ptr, px_ptr, py_ptr, zeta_ptr, psigma_ptr, delta_ptr, rpp_ptr,
                rvv_ptr, chi_ptr, charge_ratio_ptr, id_ptr, at_element_ptr,
                    at_turn_ptr, state_ptr );
    return NS(Particles_cobj_flat_buffer_add_copy)( buffer, slot_size, &pset );
}

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_t;
    SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)* ptr_added_elem = SIXTRL_NULLPTR;
    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_t )0u ) ) {
        SIXTRL_ARGPTR_DEC st_size_t OFFSETS[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
        SIXTRL_ARGPTR_DEC st_size_t SIZES[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
        SIXTRL_ARGPTR_DEC st_size_t COUNTS[ SIXTRL_PARTICLES_NUM_DATAPTRS ];

        NS(cobj_status_type) status = NS(Particles_cobj_attributes_offsets)(
            &OFFSETS[ 0 ], NS(Particles_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(Particles_cobj_attributes_sizes)( &SIZES[ 0 ],
                NS(Particles_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(Particles_cobj_attributes_counts)( &COUNTS[ 0 ],
                NS(Particles_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS ) {
            SIXTRL_ASSERT( NS(Particles_cobj_num_dataptrs)() ==
                ( st_size_t )SIXTRL_PARTICLES_NUM_DATAPTRS );

            ptr_added_elem = NS(Particles_from_cobj_index)(
                NS(CObjFlatBuffer_add_copy_of_object)( buffer, slot_size, orig,
                    NS(Particles_cobj_reserved_handle_size)( slot_size ),
                    NS(Particles_cobj_type_id)(),
                    NS(Particles_cobj_num_dataptrs)(),
                    &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) ); }
    }
    return ptr_added_elem; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE bool NS(Particles_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT { return NS(Particles_cobj_flat_buffer_can_be_added)(
    NS(CBuffer_p_const_base)( buffer ), NS(CBuffer_slot_size)( buffer ),
        max_num_particles, requ_buffer_size, requ_slots, requ_objects,
            requ_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles ) {
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) pset;
    NS(Particles_clear)( &pset );
    NS(Particles_set_max_num_particles)( &pset, max_num_particles );
    NS(Particles_set_num_particles)( &pset, max_num_particles );
    return NS(Particles_cbuffer_add_copy)( buffer, &pset ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr ) {
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) pset;
    NS(Particles_init_with_pointers)( &pset, max_num_particles, num_particles,
        charge0_ptr, mass0_ptr, beta0_ptr, gamma0_ptr, p0c_ptr,
            s_ptr, x_ptr, y_ptr, px_ptr, py_ptr, zeta_ptr, psigma_ptr, delta_ptr,
                rpp_ptr, rvv_ptr, chi_ptr, charge_ratio_ptr, id_ptr,
                    at_element_ptr, at_turn_ptr, state_ptr );
    return NS(Particles_cbuffer_add_copy)( buffer, &pset ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(Particles_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT orig )
{
    typedef NS(cobj_size_type) st_size_t;
    SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)* ptr_added_elem = SIXTRL_NULLPTR;

    if( buffer != SIXTRL_NULLPTR ) {
        st_size_t const slot_size = NS(CBuffer_slot_size)( buffer );
        SIXTRL_ARGPTR_DEC st_size_t OFFSETS[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
        SIXTRL_ARGPTR_DEC st_size_t SIZES[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
        SIXTRL_ARGPTR_DEC st_size_t COUNTS[ SIXTRL_PARTICLES_NUM_DATAPTRS ];

        NS(cobj_status_type) status = NS(Particles_cobj_attributes_offsets)(
            &OFFSETS[ 0 ], NS(Particles_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(Particles_cobj_attributes_sizes)( &SIZES[ 0 ],
                NS(Particles_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(Particles_cobj_attributes_counts)( &COUNTS[ 0 ],
                NS(Particles_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS ) {
            SIXTRL_ASSERT( NS(Particles_cobj_num_dataptrs)() == (
                st_size_t )SIXTRL_PARTICLES_NUM_DATAPTRS );
            ptr_added_elem = NS(Particles_from_cobj_index)(
                NS(CBuffer_add_copy_of_object)( buffer, orig,
                    NS(Particles_cobj_reserved_handle_size)( slot_size ),
                    NS(Particles_cobj_type_id)(),
                    NS(Particles_cobj_num_dataptrs)(),
                    &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) ); }
    }
    return ptr_added_elem; }

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLES_COBJ_H__ */
