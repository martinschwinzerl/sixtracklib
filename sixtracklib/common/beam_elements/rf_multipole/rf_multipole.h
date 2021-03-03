#ifndef SIXTRACKL_COMMON_BE_RFMULTIPOLE_BE_RFMULTIPOLE_C99_H__
#define SIXTRACKL_COMMON_BE_RFMULTIPOLE_BE_RFMULTIPOLE_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(RFMultipole)
{
    NS(be_order_type)  max_order    SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_order_type)  order        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)   voltage      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)   frequency    SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)   lag          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_addr_type)   bal_addr     SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_addr_type)   phase_addr   SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(RFMultipole);

SIXTRL_STATIC SIXTRL_FN NS(be_order_type) NS(RFMultipole_max_order)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_order_type)
NS(RFMultipole_default_max_order)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_max_order)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_order_type) const max_order ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(RFMultipole_phase_capacity)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(RFMultipole_bal_capacity)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(RFMultipole_set_bal_capacity)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const bal_capacity ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(RFMultipole_set_phase_capacity)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const phase_capacity ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_order_type) NS(RFMultipole_order)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_order_type) NS(RFMultipole_default_order)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_order)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_order_type) const order ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(RFMultipole_bal_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(RFMultipole_phase_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(RFMultipole_set_bal_length)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const bal_length ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(RFMultipole_set_phase_length)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const phase_length ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_voltage)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_default_voltage)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const voltage ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_frequency)(
    SIXTRL_BE_ARGPTR_DEC  const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_default_frequency)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_frequency)(
    SIXTRL_BE_ARGPTR_DEC  NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const frequency ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_lag)(
    SIXTRL_BE_ARGPTR_DEC  const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_default_lag)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_lag)(
    SIXTRL_BE_ARGPTR_DEC  NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const lag ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_addr_type) NS(RFMultipole_bal_addr)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const
        SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_addr_type) NS(RFMultipole_default_bal_addr)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_bal_addr)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_addr_type) const bal_addr ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(RFMultipole_const_bal_begin)( SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole)
    *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(RFMultipole_const_bal_end)( SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole)
    *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(RFMultipole_const_reserved_bal_end)( SIXTRL_BE_ARGPTR_DEC const
    NS(RFMultipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(RFMultipole_bal_begin)( SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(RFMultipole_bal_end)( SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(RFMultipole_reserved_bal_end)( SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_bal)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const bal_index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_default_bal_value)(
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_bal_value)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const idx, NS(be_real_type) const value
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_bal)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT bal_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_all_bal_values)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const value ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_knl)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(be_order_type) const knl_index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_default_knl_value)(
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_knl_value)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const idx, NS(be_real_type) const value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_knl)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT knl_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_all_knl_values)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const knl_value ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_ksl)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(be_order_type) const ksl_index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_default_ksl_value)(
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_ksl_value)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const idx, NS(be_real_type) const value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_ksl)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT ksl_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_all_ksl_values)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const ksl_value ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_addr_type) NS(RFMultipole_phase_addr)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_addr_type) NS(RFMultipole_default_phase_addr)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_phase_addr)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_addr_type) const phase_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(RFMultipole_const_phase_begin)( SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole)
    *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(RFMultipole_const_phase_end)( SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole)
    *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(RFMultipole_const_reserved_phase_end)( SIXTRL_BE_ARGPTR_DEC const
    NS(RFMultipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(RFMultipole_phase_begin)( SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(RFMultipole_phase_end)( SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(RFMultipole_reserved_phase_end)( SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_phase)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const phase_index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type)
NS(RFMultipole_default_phase_value)() SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_phase_value)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const idx, NS(be_real_type) const value
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_phase)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT phase_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_all_phase_values)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const value ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_phase_n)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(be_order_type) const phase_n_index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN  NS(be_real_type)
NS(RFMultipole_default_phase_n_value)() SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_phase_n_value)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const idx, NS(be_real_type) const value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_phase_n)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT phase_n_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_all_phase_n_values)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const phase_n_value ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(RFMultipole_phase_s)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(be_order_type) const phase_s_index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type)
NS(RFMultipole_default_phase_s_value)() SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_phase_s_value)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const idx, NS(be_real_type) const value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_phase_s)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT phase_s_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_set_all_phase_s_values)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const phase_s_value ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(RFMultipole_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(RFMultipole_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(RFMultipole_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(RFMultipole_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
NS(RFMultipole_preset)( SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_init)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_order_type) const max_order, NS(be_order_type) const order,
    NS(be_real_type) const voltage, NS(be_real_type) const frequency,
    NS(be_real_type) const lag, NS(be_addr_type) const bal_addr,
    NS(be_addr_type) const phase_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(RFMultipole_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const
        SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_rf_multipole)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole) const*
NS(RFMultipole_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct
    NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole) const*
NS(RFMultipole_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole) const*
NS(RFMultipole_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole) const*
NS(RFMultipole_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(RFMultipole_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(RFMultipole_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(RFMultipole_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(RFMultipole_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
NS(RFMultipole_preset_ext)( SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(RFMultipole_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */
#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE )
    #include "sixtracklib/common/beam_elements/rf_multipole/rf_multipole_cobj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsTraits< ::NS(RFMultipole) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_RF_MULTIPOLE;
    };

    template<> struct CObjectsNumPointersTraits< ::NS(RFMultipole) >
    {
        static constexpr cobj_size_type NUM_POINTERS =
            SIXTRL_CXX_NAMESPACE::cobj_size_type{ 2u };
    };

    template<> struct CObjectsActualHandleSizeTraits< ::NS(RFMultipole) >
    {
        SIXTRL_FN static cobj_size_type HANDLE_SIZE(
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(RFMultipole_cobj_actual_handle_size)( slot_size ); }
    };

    template<> struct CObjectsReservedHandleSizeTraits< ::NS(RFMultipole) >
    {
        SIXTRL_FN static cobj_size_type HANDLE_SIZE(
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(RFMultipole_cobj_reserved_handle_size)( slot_size ); }
    };

    template<> struct CObjectsRequiredNumBytesTraits< ::NS(RFMultipole) >
    {
        SIXTRL_FN static cobj_size_type REQUIRED_NUM_BYTES(
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(RFMultipole) *const
                SIXTRL_RESTRICT pset,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(RFMultipole_cobj_required_num_bytes)(
                pset, slot_size ); }
    };

    template<> struct CObjectsAttributesOffsetsTraits< ::NS(RFMultipole) >
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT offsets,
            cobj_size_type const max_num_offsets,
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(RFMultipole) *const
                SIXTRL_RESTRICT mp,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(RFMultipole_cobj_attributes_offsets)( offsets,
                max_num_offsets, mp, slot_size ); }
    };

    template<> struct CObjectsAttributesSizesTraits< ::NS(RFMultipole) >
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT sizes,
            cobj_size_type const max_num_sizes,
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(RFMultipole) *const
                SIXTRL_RESTRICT mp,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(RFMultipole_cobj_attributes_sizes)(
                sizes, max_num_sizes, mp, slot_size ); }
    };

    template<> struct CObjectsAttributesCountsTraits< ::NS(RFMultipole) >
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT counts,
            cobj_size_type const max_num_counts,
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(RFMultipole) *const
                SIXTRL_RESTRICT mp,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(RFMultipole_cobj_attributes_counts)(
                counts, max_num_counts, mp, slot_size ); }
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_RF_MULTIPOLE > {
            typedef ::NS(RFMultipole) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/internal/math_factorial.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(be_order_type) NS(RFMultipole_max_order)( SIXTRL_BE_ARGPTR_DEC
    const NS(RFMultipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    return mp->max_order; }

SIXTRL_INLINE NS(be_order_type) NS(RFMultipole_default_max_order)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_order_type) )0; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_max_order)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_order_type) const max_order ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( max_order >= ( NS(be_order_type) )0u ) && ( mp != SIXTRL_NULLPTR ) &&
        ( NS(RFMultipole_order)( mp ) <= max_order ) ) {
        mp->max_order = max_order;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(be_size_type) NS(RFMultipole_bal_capacity)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT {
    return ( ( NS(be_order_type) )mp->max_order >= ( NS(be_order_type) )0u )
        ? ( NS(be_size_type) )( 2 * mp->max_order + 2 )
        : ( NS(be_size_type) )0u; }

SIXTRL_INLINE NS(be_size_type) NS(RFMultipole_set_bal_capacity)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const bal_capacity ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( bal_capacity >= ( NS(be_size_type) )0u ) &&
        ( mp != SIXTRL_NULLPTR ) && ( bal_capacity >= ( NS(be_size_type) )2u ) )
    {
        NS(be_order_type) const max_order =
            ( NS(be_order_type) )( ( bal_capacity - 2u ) >> 1u );
        status = NS(RFMultipole_set_max_order)( mp, max_order );
    }
    return status; }

SIXTRL_INLINE NS(be_size_type) NS(RFMultipole_phase_capacity)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT { return NS(RFMultipole_bal_capacity)( mp ); }

SIXTRL_INLINE NS(be_size_type) NS(RFMultipole_set_phase_capacity)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const phase_capacity ) SIXTRL_NOEXCEPT {
        return NS(RFMultipole_set_bal_capacity)( mp, phase_capacity ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_order_type) NS(RFMultipole_order)( SIXTRL_BE_ARGPTR_DEC const
    NS(RFMultipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); return mp->order; }

SIXTRL_INLINE NS(be_order_type) NS(RFMultipole_default_order)() SIXTRL_NOEXCEPT {
    return ( NS(be_order_type) )0u; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_order)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_order_type) const order ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( order >= ( NS(be_order_type) )0u ) && ( mp != SIXTRL_NULLPTR ) &&
        ( ( NS(RFMultipole_max_order)( mp ) >= order ) ||
          ( NS(RFMultipole_max_order)( mp ) == ( NS(be_order_type) )0u ) ) ) {
        mp->order = order;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(be_size_type) NS(RFMultipole_bal_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( NS(RFMultipole_order)( mp ) >= ( NS(be_order_type) )0u );
    return ( NS(be_size_type) )( 2 * NS(RFMultipole_order)( mp ) + 2 ); }

SIXTRL_INLINE NS(be_size_type) NS(RFMultipole_set_bal_length)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const bal_length ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( bal_length >= ( NS(be_size_type) )0u ) &&
        ( mp != SIXTRL_NULLPTR ) && ( bal_length >= ( NS(be_size_type) )2u ) ) {
        NS(be_order_type) const order = ( NS(be_order_type) )(
            ( bal_length - 2u ) >> 1 );
        status = NS(RFMultipole_set_order)( mp, order ); }
    return status; }

SIXTRL_INLINE NS(be_size_type) NS(RFMultipole_phase_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT { return NS(RFMultipole_bal_length)( mp ); }

SIXTRL_INLINE NS(be_size_type) NS(RFMultipole_set_phase_length)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const phase_length ) SIXTRL_NOEXCEPT {
        return NS(RFMultipole_set_bal_length)( mp, phase_length ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_voltage)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); return mp->voltage; }

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_default_voltage)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_voltage)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const voltage ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    mp->voltage = voltage;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_frequency)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    return mp->frequency; }

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_default_frequency)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_frequency)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const frequency ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    mp->frequency = frequency;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_lag)( SIXTRL_BE_ARGPTR_DEC const
    NS(RFMultipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); return mp->lag; }

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_default_lag)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_lag)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const lag ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    mp->lag = lag;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_addr_type) NS(RFMultipole_bal_addr)( SIXTRL_BE_ARGPTR_DEC
    const NS(RFMultipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); return mp->bal_addr; }

SIXTRL_INLINE NS(be_addr_type) NS(RFMultipole_default_bal_addr)(
    ) SIXTRL_NOEXCEPT { return  ( NS(be_addr_type) )SIXTRL_NULL_ADDR; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_bal_addr)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_addr_type) const bal_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); mp->bal_addr = bal_addr;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(RFMultipole_const_bal_begin)( SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole)
        *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* )( uintptr_t
        )NS(RFMultipole_bal_addr)( mp ); }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(RFMultipole_const_bal_end)( SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* ptr_end =
        NS(RFMultipole_const_bal_begin)( mp );
    if( ptr_end != SIXTRL_NULLPTR ) {
        ptr_end = ptr_end + NS(RFMultipole_bal_length)( mp ); }
    return ptr_end; }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(RFMultipole_const_reserved_bal_end)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT {
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* ptr_end =
        NS(RFMultipole_const_bal_begin)( mp );
    if( ptr_end != SIXTRL_NULLPTR ) {
        ptr_end = ptr_end + NS(RFMultipole_bal_capacity)( mp ); }
    return ptr_end; }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* NS(RFMultipole_bal_begin)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
        )NS(RFMultipole_const_bal_begin)( mp ); }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* NS(RFMultipole_bal_end)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
        )NS(RFMultipole_const_bal_end)( mp ); }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(RFMultipole_reserved_bal_end)( SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
        )NS(RFMultipole_const_reserved_bal_end)( mp ); }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_bal)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const bal_index ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* ptr_begin =
        NS(RFMultipole_const_bal_begin)( mp );
    SIXTRL_ASSERT( ptr_begin != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( bal_index < NS(RFMultipole_bal_length)( mp ) );
    return ptr_begin[ bal_index ]; }

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_default_bal_value)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_bal_value)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const idx, NS(be_real_type) const val ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal = NS(RFMultipole_bal_begin)( mp );
    if( ( bal != SIXTRL_NULLPTR ) && ( idx < NS(RFMultipole_bal_length)( mp ) ) )
    {
        bal[ idx ] = val;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_bal)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT in_bal_it
) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_it = NS(RFMultipole_bal_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_it  != SIXTRL_NULLPTR ) &&
        ( in_bal_it != SIXTRL_NULLPTR ) ) {
        bal_iterator_type bal_end = bal_it + NS(RFMultipole_bal_length)( mp );
        for( ; bal_it != bal_end ; ++bal_it, ++in_bal_it ) *bal_it = *in_bal_it;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_all_bal_values)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const value ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_it  = NS(RFMultipole_bal_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_it  != SIXTRL_NULLPTR ) ) {
        bal_iterator_type bal_end = bal_it + NS(RFMultipole_bal_length)( mp );
        for( ; bal_it != bal_end ; ++bal_it ) *bal_it = value;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_knl)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(be_order_type) const knl_index ) SIXTRL_NOEXCEPT {
    NS(be_size_type) const idx = ( NS(be_size_type) )( 2 * knl_index );
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( knl_index >= ( NS(be_order_type) )0 );
    SIXTRL_ASSERT( knl_index <= NS(RFMultipole_order)( mp ) );
    SIXTRL_ASSERT( idx < NS(RFMultipole_bal_length)( mp ) );
    return NS(RFMultipole_bal)( mp, idx ) * NS(Math_factorial)( knl_index ); }

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_default_knl_value)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_knl_value)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const k_idx, NS(be_real_type) const knl_value
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal = NS(RFMultipole_bal_begin)( mp );
    NS(be_size_type) const bal_index = ( NS(be_size_type) )( 2 * k_idx );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal != SIXTRL_NULLPTR ) &&
        ( bal_index < NS(RFMultipole_bal_length)( mp ) ) ) {
        bal[ bal_index ] = knl_value / NS(Math_factorial)( k_idx );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_knl)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT knl_begin
) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_values = NS(RFMultipole_bal_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_values != SIXTRL_NULLPTR ) &&
        ( knl_begin != SIXTRL_NULLPTR ) ) {
        NS(be_size_type) const nn = NS(RFMultipole_bal_length)( mp );
        NS(be_order_type) k_idx = ( NS(be_order_type) )0;
        NS(be_size_type) ii = ( NS(be_size_type) )0;
        for( ; ii < nn ; ii += 2u, ++k_idx )
            bal_values[ ii ] = knl_begin[ k_idx ] / NS(Math_factorial)( k_idx );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_all_knl_values)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const knl_value ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_values = NS(RFMultipole_bal_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_values != SIXTRL_NULLPTR ) ) {
        NS(be_size_type) const nn = NS(RFMultipole_bal_length)( mp );
        NS(be_order_type) k_idx = ( NS(be_order_type) )0;
        NS(be_size_type) ii = ( NS(be_size_type) )0;
        for( ; ii < nn ; ii += 2u, ++k_idx )
            bal_values[ ii ] = knl_value / NS(Math_factorial)( k_idx );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_ksl)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(be_order_type) const ksl_index ) SIXTRL_NOEXCEPT {
    NS(be_size_type) const idx = ( NS(be_size_type) )( 2 * ksl_index + 1 );
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ksl_index >= ( NS(be_order_type) )0 );
    SIXTRL_ASSERT( ksl_index <= NS(RFMultipole_order)( mp ) );
    return NS(RFMultipole_bal)( mp, idx ) * NS(Math_factorial)( ksl_index ); }

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_default_ksl_value)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_ksl_value)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const k_idx, NS(be_real_type) const ksl_value
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal = NS(RFMultipole_bal_begin)( mp );
    NS(be_size_type) const bal_index = ( NS(be_size_type) )( 2 * k_idx + 1 );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal != SIXTRL_NULLPTR ) &&
        ( bal_index < NS(RFMultipole_bal_length)( mp ) ) ) {
        bal[ bal_index ] = ksl_value / NS(Math_factorial)( k_idx );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_ksl)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT ksl_begin
) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_values = NS(RFMultipole_bal_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_values != SIXTRL_NULLPTR ) &&
        ( ksl_begin != SIXTRL_NULLPTR ) ) {
        NS(be_size_type) const nn = NS(RFMultipole_bal_length)( mp );
        NS(be_order_type) k_idx = ( NS(be_order_type) )0;
        NS(be_size_type) ii = ( NS(be_size_type) )1;
        for( ; ii < nn ; ii += 2u, ++k_idx )
            bal_values[ ii ] = ksl_begin[ k_idx ] / NS(Math_factorial)( k_idx );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_all_ksl_values)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const ksl_value ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_values = NS(RFMultipole_bal_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_values != SIXTRL_NULLPTR ) ) {
        NS(be_size_type) const nn = NS(RFMultipole_bal_length)( mp );
        NS(be_order_type) k_idx = ( NS(be_order_type) )0;
        NS(be_size_type) ii = ( NS(be_size_type) )1;
        for( ; ii < nn ; ii += 2u, ++k_idx )
            bal_values[ ii ] = ksl_value / NS(Math_factorial)( k_idx );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(be_addr_type) NS(RFMultipole_phase_addr)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    return mp->phase_addr; }

SIXTRL_INLINE NS(be_addr_type) NS(RFMultipole_default_phase_addr)(
) SIXTRL_NOEXCEPT { return ( NS(be_addr_type) )SIXTRL_NULL_ADDR; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_phase_addr)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_addr_type) const phase_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); mp->phase_addr = phase_addr;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  */

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(RFMultipole_const_phase_begin)( SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole)
    *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* )( uintptr_t
        )NS(RFMultipole_phase_addr)( mp ); }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(RFMultipole_const_phase_end)( SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole)
    *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* p =
        NS(RFMultipole_const_phase_begin)( mp );
    if( p != SIXTRL_NULLPTR ) { p = p + NS(RFMultipole_phase_length)( mp ); }
    return p; }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(RFMultipole_const_reserved_phase_end)( SIXTRL_BE_ARGPTR_DEC const
    NS(RFMultipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* p =
        NS(RFMultipole_const_phase_begin)( mp );
    if( p != SIXTRL_NULLPTR ) { p = p + NS(RFMultipole_phase_capacity)( mp ); }
    return p; }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(RFMultipole_phase_begin)( SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* )( uintptr_t
        )NS(RFMultipole_phase_addr)( mp ); }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(RFMultipole_phase_end)( SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* p =
        NS(RFMultipole_phase_begin)( mp );
    if( p != SIXTRL_NULLPTR ) { p = p + NS(RFMultipole_phase_length)( mp ); }
    return p; }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(RFMultipole_reserved_phase_end)( SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* p =
        NS(RFMultipole_phase_begin)( mp );
    if( p != SIXTRL_NULLPTR ) { p = p + NS(RFMultipole_phase_capacity)( mp ); }
    return p; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  */

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_phase)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const bal_index ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* ptr_begin =
        NS(RFMultipole_const_phase_begin)( mp );
    SIXTRL_ASSERT( ptr_begin != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( bal_index < NS(RFMultipole_phase_length)( mp ) );
    return ptr_begin[ bal_index ]; }

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_default_phase_value)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_phase_value)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const idx, NS(be_real_type) const val ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal =
        NS(RFMultipole_phase_begin)( mp );
    if( ( bal != SIXTRL_NULLPTR ) &&
        ( idx < NS(RFMultipole_phase_length)( mp ) ) ) {
        bal[ idx ] = val;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_phase)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT in_phase_it
) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_it = NS(RFMultipole_phase_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_it  != SIXTRL_NULLPTR ) &&
        ( in_phase_it != SIXTRL_NULLPTR ) ) {
        bal_iterator_type bal_end = bal_it + NS(RFMultipole_phase_length)( mp );
        for( ; bal_it != bal_end ; ++bal_it, ++in_phase_it )
            *bal_it = *in_phase_it;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_all_phase_values)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const value ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_it  = NS(RFMultipole_phase_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_it  != SIXTRL_NULLPTR ) ) {
        bal_iterator_type bal_end = bal_it + NS(RFMultipole_phase_length)( mp );
        for( ; bal_it != bal_end ; ++bal_it ) *bal_it = value;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_phase_n)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(be_order_type) const phase_n_index ) SIXTRL_NOEXCEPT {
    NS(be_size_type) const idx = ( NS(be_size_type) )( 2 * phase_n_index );
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( phase_n_index >= ( NS(be_order_type) )0 );
    SIXTRL_ASSERT( phase_n_index <= NS(RFMultipole_order)( mp ) );
    SIXTRL_ASSERT( idx < NS(RFMultipole_phase_length)( mp ) );
    return NS(RFMultipole_phase)( mp, idx ); }

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_default_phase_n_value)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_phase_n_value)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const k_idx, NS(be_real_type) const phase_n_value
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal =
        NS(RFMultipole_phase_begin)( mp );
    NS(be_size_type) const bal_index = ( NS(be_size_type) )( 2 * k_idx );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal != SIXTRL_NULLPTR ) &&
        ( bal_index < NS(RFMultipole_phase_length)( mp ) ) ) {
        bal[ bal_index ] = phase_n_value;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_phase_n)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT phase_n_begin
) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_values = NS(RFMultipole_phase_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_values != SIXTRL_NULLPTR ) &&
        ( phase_n_begin != SIXTRL_NULLPTR ) ) {
        NS(be_size_type) const nn = NS(RFMultipole_phase_length)( mp );
        NS(be_order_type) k_idx = ( NS(be_order_type) )0;
        NS(be_size_type) ii = ( NS(be_size_type) )0;
        for( ; ii < nn ; ii += 2u, ++k_idx )
            bal_values[ ii ] = phase_n_begin[ k_idx ];
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_all_phase_n_values)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const phase_n_value ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_values = NS(RFMultipole_phase_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_values != SIXTRL_NULLPTR ) ) {
        NS(be_size_type) const nn = NS(RFMultipole_phase_length)( mp );
        NS(be_order_type) k_idx = ( NS(be_order_type) )0;
        NS(be_size_type) ii = ( NS(be_size_type) )0;
        for( ; ii < nn ; ii += 2u, ++k_idx ) bal_values[ ii ] = phase_n_value;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_phase_s)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(be_order_type) const phase_s_index ) SIXTRL_NOEXCEPT {
    NS(be_size_type) const idx = ( NS(be_size_type) )( 2 * phase_s_index + 1 );
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( phase_s_index >= ( NS(be_order_type) )0 );
    SIXTRL_ASSERT( phase_s_index <= NS(RFMultipole_order)( mp ) );
    return NS(RFMultipole_phase)( mp, idx ); }

SIXTRL_INLINE NS(be_real_type) NS(RFMultipole_default_phase_s_value)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_phase_s_value)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const k_idx, NS(be_real_type) const phase_s_value
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal =
        NS(RFMultipole_phase_begin)( mp );
    NS(be_size_type) const bal_index = ( NS(be_size_type) )( 2 * k_idx + 1 );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal != SIXTRL_NULLPTR ) &&
        ( bal_index < NS(RFMultipole_phase_length)( mp ) ) ) {
        bal[ bal_index ] = phase_s_value ;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_phase_s)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT phase_s_begin
) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_values = NS(RFMultipole_phase_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_values != SIXTRL_NULLPTR ) &&
        ( phase_s_begin != SIXTRL_NULLPTR ) ) {
        NS(be_size_type) const nn = NS(RFMultipole_phase_length)( mp );
        NS(be_order_type) k_idx = ( NS(be_order_type) )0;
        NS(be_size_type) ii = ( NS(be_size_type) )1;
        for( ; ii < nn ; ii += 2u, ++k_idx )
            bal_values[ ii ] = phase_s_begin[ k_idx ];
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_set_all_phase_s_values)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const phase_s_value ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_values = NS(RFMultipole_phase_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_values != SIXTRL_NULLPTR ) ) {
        NS(be_size_type) const nn = NS(RFMultipole_phase_length)( mp );
        NS(be_order_type) k_idx = ( NS(be_order_type) )0;
        NS(be_size_type) ii = ( NS(be_size_type) )1;
        for( ; ii < nn ; ii += 2u, ++k_idx )
            bal_values[ ii ] = phase_s_value;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(RFMultipole_cobj_type_id)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_obj_id_type)
        )SIXTRL_COBJECTS_TYPE_ID_RF_MULTIPOLE; }

SIXTRL_INLINE NS(cobj_size_type) NS(RFMultipole_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )2u; }

SIXTRL_INLINE NS(cobj_size_type) NS(RFMultipole_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(RFMultipole) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(RFMultipole_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(RFMultipole_cobj_actual_handle_size)( slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* NS(RFMultipole_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    if( mp != SIXTRL_NULLPTR ) NS(RFMultipole_clear)( mp );
    return mp; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_init)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp,
    NS(be_order_type) const max_order, NS(be_order_type) const order,
    NS(be_real_type) const voltage, NS(be_real_type) const frequency,
    NS(be_real_type) const lag, NS(be_addr_type) const bal_addr,
    NS(be_addr_type) const phase_addr ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( mp != SIXTRL_NULLPTR ) && ( max_order >= ( NS(be_order_type) )0u ) &&
        ( order >= ( NS(be_order_type) )0u ) && ( max_order >= order ) ) {
        mp->max_order = max_order;
        status = NS(RFMultipole_set_order)( mp, order ) |
                 NS(RFMultipole_set_voltage)( mp, voltage ) |
                 NS(RFMultipole_set_frequency)( mp, frequency ) |
                 NS(RFMultipole_set_lag)( mp, lag ) |
                 NS(RFMultipole_set_bal_addr)( mp, bal_addr ) |
                 NS(RFMultipole_set_phase_addr)( mp, phase_addr ); }
    return status; }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    return NS(RFMultipole_init)( mp, NS(RFMultipole_default_max_order)(),
        NS(RFMultipole_default_order)(), NS(RFMultipole_default_voltage)(),
            NS(RFMultipole_default_frequency)(), NS(RFMultipole_default_lag)(),
                NS(RFMultipole_default_bal_addr)(),
                    NS(RFMultipole_default_phase_addr)() ); }

SIXTRL_INLINE NS(status_type) NS(RFMultipole_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) ) {
        if( ( src != dst ) &&
            ( NS(RFMultipole_order)( src ) >=
              NS(RFMultipole_max_order)( dst ) ) ) {
            status = NS(RFMultipole_set_order)(
                dst, NS(RFMultipole_order)( src ) );
            status |= NS(RFMultipole_set_voltage)(
                dst, NS(RFMultipole_voltage)( src ) );
            status |= NS(RFMultipole_set_frequency)(
                dst, NS(RFMultipole_frequency)( src ) );
            status |= NS(RFMultipole_set_lag)(
                dst, NS(RFMultipole_lag)( src ) );
            status |= NS(RFMultipole_set_bal)(
                dst, NS(RFMultipole_const_bal_begin)( src ) );
            status |= NS(RFMultipole_set_phase)(
                dst, NS(RFMultipole_const_phase_begin)( src ) ); }
        else if( src == dst ) {
            status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    } return status; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_rf_multipole)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjIndex_is_consistent_with_type)( obj,
    NS(RFMultipole_cobj_type_id)(), NS(RFMultipole_cobj_actual_handle_size)(
        ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole) const*
NS(RFMultipole_const_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return ( NS(CObjIndex_is_rf_multipole)( obj ) )
        ? ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
        )NS(RFMultipole_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole) const*
NS(RFMultipole_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(RFMultipole_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(RFMultipole_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole) const*
NS(RFMultipole_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(RFMultipole_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(RFMultipole)*
NS(RFMultipole_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(RFMultipole_from_cobj_index)( NS(CBuffer_index_at)( b, idx ) ); }

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKL_COMMON_BE_RFMULTIPOLE_BE_RFMULTIPOLE_C99_H__ */
