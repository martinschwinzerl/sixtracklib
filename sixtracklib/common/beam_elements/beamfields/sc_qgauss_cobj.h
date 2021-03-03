#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAMFILEDS_SC_QGAUSS_COBJ_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAMFILEDS_SC_QGAUSS_COBJ_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/beamfields/sc_qgauss.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

SIXTRL_STATIC SIXTRL_FN bool NS(SCQGaussProfile_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    NS(be_real_type) const number_of_particles,
    NS(be_real_type) const bunchlength_rms,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff,
    NS(be_real_type) const q_param, bool const enabled )  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(SCQGaussProfile_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cbuffer_new)( SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)*
    SIXTRL_RESTRICT buffer );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_real_type) const number_of_particles,
    NS(be_real_type) const bunchlength_rms,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff,
    NS(be_real_type) const q_param, bool const enabled );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT orig );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(SCQGaussProfile_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_real_type) const number_of_particles,
    NS(be_real_type) const bunchlength_rms,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff,
    NS(be_real_type) const q_param, bool const enabled );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cobj_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT sc );

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

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(SCQGaussProfile_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_can_add_copy_of_trivial_object)( buffer, slot_size,
        NS(SCQGaussProfile_cobj_reserved_handle_size)( slot_size ),
            requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile) elem;
    NS(SCQGaussProfile_clear)( &elem );
    return NS(SCQGaussProfile_cobj_flat_buffer_add_copy)(
        buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(be_real_type) const number_of_particles,
    NS(be_real_type) const bunchlength_rms,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff,
    NS(be_real_type) const q_param, bool const enabled ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile) elem;
    NS(status_type) const status = NS(SCQGaussProfile_init)( &elem,
        number_of_particles, bunchlength_rms, sigma_x, sigma_y, length, x_co,
            y_co, min_sigma_diff, q_param, enabled );

    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(SCQGaussProfile_cobj_flat_buffer_add_copy)( buffer, slot_size, &elem )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT {
    return NS(SCQGaussProfile_from_cobj_index)(
        NS(CObjFlatBuffer_add_copy_of_trivial_object)( buffer, slot_size, orig,
            NS(SCQGaussProfile_cobj_reserved_handle_size)( slot_size ),
            NS(SCQGaussProfile_cobj_type_id)(), false ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(SCQGaussProfile_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(CBuffer_can_add_copy_of_trivial_object)( b,
    NS(SCQGaussProfile_cobj_reserved_handle_size)( NS(CBuffer_slot_size)( b ) ),
        requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile) elem;
    NS(SCQGaussProfile_clear)( &elem );
    return NS(SCQGaussProfile_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_real_type) const number_of_particles,
    NS(be_real_type) const bunchlength_rms,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff,
    NS(be_real_type) const q_param, bool const enabled ) {
    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile) elem;
    NS(status_type) const status = NS(SCQGaussProfile_init)( &elem,
        number_of_particles, bunchlength_rms, sigma_x, sigma_y, length,
            x_co, y_co, min_sigma_diff, q_param, enabled );

    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(SCQGaussProfile_cbuffer_add_copy)( buffer, &elem ) : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT orig ) {
    NS(cobj_size_type) const slot_size = NS(CBuffer_slot_size)( buffer );
    return NS(SCQGaussProfile_from_cobj_index)( NS(CBuffer_add_copy_of_trivial_object)(
        buffer, orig, NS(SCQGaussProfile_cobj_reserved_handle_size)( slot_size ),
            NS(SCQGaussProfile_cobj_type_id)(), false ) ); }

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAMFILEDS_SC_QGAUSS_COBJ_H__  */
