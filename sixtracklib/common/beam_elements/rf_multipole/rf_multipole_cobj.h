#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_RF_MULTIPOLE_RF_MULTIPOLE_COBJ_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_RF_MULTIPOLE_RF_MULTIPOLE_COBJ_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/rf_multipole/rf_multipole.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

/* SIXTRL_CBUFFER_OBJ_DATAPTR_DEC */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(RFMultipole_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_cobj_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT offsets,
    NS(size_type) const max_num_offsets,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_cobj_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT counts,
    NS(size_type) const max_num_counts,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_cobj_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT sizes,
    NS(size_type) const max_num_sizes,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(RFMultipole_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size, NS(be_order_type) const max_order,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size, NS(be_order_type) const max_order
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    NS(be_order_type) const max_order, NS(be_order_type) const order,
    NS(be_real_type) const voltage, NS(be_real_type) const frequency,
    NS(be_real_type) const lag, NS(be_addr_type) const bal_addr,
    NS(be_addr_type) const phase_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(RFMultipole_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(be_order_type) const max_order,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cbuffer_new)( SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)*
    SIXTRL_RESTRICT buffer, NS(be_order_type) const max_order );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_order_type) const max_order, NS(be_order_type) const order,
    NS(be_real_type) const voltage, NS(be_real_type) const frequency,
    NS(be_real_type) const lag, NS(be_addr_type) const bal_addr,
    NS(be_addr_type) const phase_addr  );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT orig );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(RFMultipole_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(RFMultipole_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(be_order_type) const max_order,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_order_type) const max_order );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_order_type) const max_order, NS(be_order_type) const order,
    NS(be_real_type) const voltage, NS(be_real_type) const frequency,
    NS(be_real_type) const lag, NS(be_addr_type) const bal_addr,
    NS(be_addr_type) const phase_addr  );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cobj_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp );

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

SIXTRL_INLINE NS(cobj_size_type) NS(RFMultipole_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_t;
    st_size_t num_bytes = ( st_size_t )0u;

    if( slot_size == ( st_size_t )0u )
        slot_size =  ( st_size_t )SIXTRL_DEFAULT_ALIGN;

    SIXTRL_ARGPTR_DEC st_size_t SIZES[ 2 ];
    SIXTRL_ARGPTR_DEC st_size_t COUNTS[ 2 ];

    NS(status_type) status = NS(RFMultipole_cobj_attributes_sizes)( &SIZES[ 0 ],
        NS(RFMultipole_cobj_num_dataptrs)(), mp, slot_size );

    if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        status = NS(RFMultipole_cobj_attributes_counts)( &COUNTS[ 0 ],
            NS(RFMultipole_cobj_num_dataptrs)(), mp, slot_size );

    if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        num_bytes = NS(CObjFlatBuffer_predict_required_num_bytes)(
            NS(RFMultipole_cobj_reserved_handle_size)( slot_size ),
            NS(RFMultipole_cobj_num_dataptrs)(),
            &SIZES[ 0 ], &COUNTS[ 0 ], slot_size );

    return num_bytes; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(status_type) NS(RFMultipole_cobj_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT offsets,
    NS(size_type) const max_num_offsets,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(RFMultipole_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;
    if( ( mp != SIXTRL_NULLPTR ) && ( offsets != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_offsets >= ndataptrs ) &&
        ( ndataptrs == ( ( st_size_t )1u ) ) ) {
        NS(be_size_type) const initial_offset =
            ( st_size_t )2 * NS(CObjFlatBuffer_slot_based_size)( sizeof(
                NS(be_order_type) ), slot_size ) +
            ( st_size_t )3 * NS(CObjFlatBuffer_slot_based_size)( sizeof(
                NS(be_real_type) ), slot_size );
        offsets[ ii++ ] = initial_offset;
        offsets[ ii++ ] = initial_offset + NS(CObjFlatBuffer_slot_based_size)(
            sizeof( NS(be_addr_type) ), slot_size );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

    if( ( offsets != SIXTRL_NULLPTR ) &&
        ( max_num_offsets > ( st_size_t )0u ) && ( ii < max_num_offsets ) ) {
        while( ii < max_num_offsets ) { offsets[ ii++ ] = ( st_size_t )0u; } }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_cobj_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT counts,
    NS(size_type) const max_num_counts,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(RFMultipole_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;
    if( ( mp != SIXTRL_NULLPTR ) && ( counts != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_counts >= ndataptrs ) &&
        ( ndataptrs == ( ( st_size_t )1u ) ) ) {
        counts[ ii++ ] = NS(RFMultipole_bal_capacity)( mp );
        counts[ ii++ ] = NS(RFMultipole_phase_capacity)( mp );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

    if( ( counts != SIXTRL_NULLPTR ) &&
        ( max_num_counts > ( st_size_t )0u ) && ( ii < max_num_counts ) ) {
        while( ii < max_num_counts ) { counts[ ii++ ] = ( st_size_t )0u; } }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_cobj_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT sizes,
    NS(size_type) const max_num_sizes,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(RFMultipole_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;
    if( ( mp != SIXTRL_NULLPTR ) && ( sizes != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_sizes >= ndataptrs ) &&
        ( ndataptrs == ( ( st_size_t )1u ) ) ) {
        sizes[ ii++ ] = sizeof( NS(be_real_type) );
        sizes[ ii++ ] = sizeof( NS(be_real_type) );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

    if( ( sizes != SIXTRL_NULLPTR ) &&
        ( max_num_sizes > ( st_size_t )0u ) && ( ii < max_num_sizes ) ) {
        while( ii < max_num_sizes ) { sizes[ ii++ ] = ( st_size_t )0u; } }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(RFMultipole_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size, NS(be_order_type) const max_order,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT {
    bool can_be_added = false;
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole) mp;
    NS(status_type) status = NS(RFMultipole_init)( &mp, max_order, max_order,
        NS(RFMultipole_default_voltage)(), NS(RFMultipole_default_frequency)(),
            NS(RFMultipole_default_lag)(), NS(RFMultipole_default_bal_addr)(),
                NS(RFMultipole_default_phase_addr)() );

    if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
        ( NS(RFMultipole_cobj_num_dataptrs)() == ( NS(cobj_size_type) )2u ) &&
        ( slot_size > ( NS(cobj_size_type) )0u ) &&
        ( NS(RFMultipole_max_order)( &mp ) >= ( NS(be_order_type) )0u ) &&
        ( NS(RFMultipole_order)( &mp ) >= ( NS(be_order_type) )0u ) &&
        ( NS(RFMultipole_max_order)( &mp ) >= NS(RFMultipole_order)( &mp ) ) ) {
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) SIZES[ 2 ];
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) COUNTS[ 2 ];

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(RFMultipole_cobj_attributes_sizes)( &SIZES[ 0 ],
                NS(RFMultipole_cobj_num_dataptrs)(), &mp, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(RFMultipole_cobj_attributes_counts)( &COUNTS[ 0 ],
                NS(RFMultipole_cobj_num_dataptrs)(), &mp, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            can_be_added = NS(CObjFlatBuffer_can_add_copy_of_object)(
                buffer, slot_size,
                NS(RFMultipole_cobj_reserved_handle_size)( slot_size ),
                NS(RFMultipole_cobj_num_dataptrs)(),
                &SIZES[ 0 ], &COUNTS[ 0 ], requ_buffer_size, requ_n_slots,
                requ_n_objects, requ_n_dataptrs ); }
    }
    return can_be_added; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size, NS(be_order_type) const max_order
) SIXTRL_NOEXCEPT {
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole) mp;
    NS(status_type) status = NS(RFMultipole_init)( &mp, max_order, max_order,
        NS(RFMultipole_default_voltage)(), NS(RFMultipole_default_frequency)(),
            NS(RFMultipole_default_lag)(), NS(RFMultipole_default_bal_addr)(),
                NS(RFMultipole_default_phase_addr)() );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(RFMultipole_cobj_flat_buffer_add_copy)( buffer, slot_size, &mp )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size, NS(be_order_type) const max_order,
    NS(be_order_type) const order, NS(be_real_type) const voltage,
    NS(be_real_type) const frequency, NS(be_real_type) const lag,
    NS(be_addr_type) const bal_addr, NS(be_addr_type) const phase_addr
) SIXTRL_NOEXCEPT {
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole) mp;
    NS(status_type) status = NS(RFMultipole_init)(
        &mp, max_order, order, voltage, frequency, lag, bal_addr, phase_addr );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(RFMultipole_cobj_flat_buffer_add_copy)( buffer, slot_size, &mp )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_DATAPTR_DEC NS(RFMultipole)* ptr_added_elem = SIXTRL_NULLPTR;
    if( ( NS(RFMultipole_cobj_num_dataptrs)() == ( NS(cobj_size_type) )2u ) &&
        ( slot_size > ( NS(cobj_size_type) )0u ) &&
        ( NS(RFMultipole_max_order)( orig ) >= ( NS(be_order_type) )0u ) &&
        ( NS(RFMultipole_order)( orig ) >= ( NS(be_order_type) )0u ) &&
        ( NS(RFMultipole_order)( orig ) <= NS(RFMultipole_max_order)( orig ) ) )
    {
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) OFFSETS[ 2 ];
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) SIZES[ 2 ];
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) COUNTS[ 2 ];

        NS(status_type) status = NS(RFMultipole_cobj_attributes_sizes)(
            &SIZES[ 0 ], NS(RFMultipole_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(RFMultipole_cobj_attributes_counts)( &COUNTS[ 0 ],
                NS(RFMultipole_cobj_num_dataptrs)(), orig, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(RFMultipole_cobj_attributes_offsets)( &OFFSETS[ 0 ],
                NS(RFMultipole_cobj_num_dataptrs)(), orig, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            ptr_added_elem = NS(RFMultipole_from_cobj_index)(
                NS(CObjFlatBuffer_add_copy_of_object)( buffer, slot_size, orig,
                    NS(RFMultipole_cobj_reserved_handle_size)( slot_size ),
                    NS(RFMultipole_cobj_type_id)(),
                    NS(RFMultipole_cobj_num_dataptrs)(),
                    &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );
        }
    }
    return ptr_added_elem; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(RFMultipole_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(be_order_type) const max_order,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(RFMultipole_cobj_flat_buffer_can_be_added)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ), max_order,
        requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_order_type) const max_order ) {
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole) mp;
    NS(status_type) status = NS(RFMultipole_init)( &mp, max_order, max_order,
        NS(RFMultipole_default_voltage)(), NS(RFMultipole_default_frequency)(),
            NS(RFMultipole_default_lag)(), NS(RFMultipole_default_bal_addr)(),
                NS(RFMultipole_default_phase_addr)() );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(RFMultipole_cbuffer_add_copy)( buffer, &mp ) : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_order_type) const max_order, NS(be_order_type) const order,
    NS(be_real_type) const voltage, NS(be_real_type) const frequency,
    NS(be_real_type) const lag, NS(be_addr_type) const bal_addr,
    NS(be_addr_type) const phase_addr ) {
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole) mp;
    NS(status_type) status = NS(RFMultipole_init)(
        &mp, max_order, order, voltage, frequency, lag, bal_addr, phase_addr );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(RFMultipole_cbuffer_add_copy)( buffer, &mp ) : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT orig ) {
    SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)* ptr_added_elem = SIXTRL_NULLPTR;

    if( ( NS(RFMultipole_cobj_num_dataptrs)() == ( NS(cobj_size_type) )2u ) &&
        ( NS(RFMultipole_max_order)( orig ) >= ( NS(be_order_type) )0u ) &&
        ( NS(RFMultipole_order)( orig ) >= ( NS(be_order_type) )0u ) &&
        ( NS(RFMultipole_order)( orig ) <= NS(RFMultipole_max_order)( orig ) ) )
    {
        NS(cobj_size_type) const slot_size = NS(CBuffer_slot_size)( buffer );
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) OFFSETS[ 2 ];
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) SIZES[ 2 ];
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) COUNTS[ 2 ];

        NS(status_type) status = NS(RFMultipole_cobj_attributes_sizes)(
            &SIZES[ 0 ], NS(RFMultipole_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(RFMultipole_cobj_attributes_counts)( &COUNTS[ 0 ],
                NS(RFMultipole_cobj_num_dataptrs)(), orig, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(RFMultipole_cobj_attributes_offsets)( &OFFSETS[ 0 ],
                NS(RFMultipole_cobj_num_dataptrs)(), orig, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            ptr_added_elem = NS(RFMultipole_from_cobj_index)(
                NS(CBuffer_add_copy_of_object)( buffer, orig,
                    NS(RFMultipole_cobj_reserved_handle_size)( slot_size ),
                    NS(RFMultipole_cobj_type_id)(),
                    NS(RFMultipole_cobj_num_dataptrs)(),
                    &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );
        }
    }
    return ptr_added_elem; }

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_RF_MULTIPOLE_RF_MULTIPOLE_COBJ_H__  */
