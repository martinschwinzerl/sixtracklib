#ifndef SIXTRACKLIB_COMMON_BE_BEAM_FIELDS_INTERPOL_1D_C99_H__
#define SIXTRACKLIB_COMMON_BE_BEAM_FIELDS_INTERPOL_1D_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <math.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

typedef SIXTRL_REAL_T  NS(interpol_1d_real_t);
typedef SIXTRL_INT64_T NS(interpol_1d_int_t);

/* ************************************************************************* */

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t) NS(Interpol1D_abscissa_t_end)(
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values );

SIXTRL_STATIC SIXTRL_FN bool NS(Interpol1D_abscissa_value_is_in_range)(
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values, NS(interpol_1d_real_t) const t );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_int_t)
NS(Interpol1D_abscissa_lower_index)(
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values, NS(interpol_1d_real_t) const t );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1D_abscissa_floor_value)(
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values, NS(interpol_1d_real_t) const t );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1D_abscissa_ceil_value)(
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values, NS(interpol_1d_real_t) const t );

/* ************************************************************************* */

typedef struct NS(Interpol1DLinear)
{
    NS(interpol_1d_real_t) t0                SIXTRL_ALIGN( 8 );
    NS(interpol_1d_real_t) dt                SIXTRL_ALIGN( 8 );
    NS(interpol_1d_int_t)  num_values        SIXTRL_ALIGN( 8 );
    NS(buffer_addr_t)      values_begin_addr SIXTRL_ALIGN( 8 );
}
NS(Interpol1DLinear);

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_preset)( SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
    SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DLinear_clear)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(object_type_id_t)
NS(Interpol1DLinear_type_id)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(Interpol1DLinear_num_dataptrs)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(Interpol1DLinear_num_slots)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(buffer_size_t) const slot_size );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DLinear_t0)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DLinear_t_end)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DLinear_dt)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_int_t)
NS(Interpol1DLinear_num_values)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(buffer_addr_t)
NS(Interpol1DLinear_values_begin_addr)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t) const*
NS(Interpol1DLinear_const_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t)*
NS(Interpol1DLinear_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN bool NS(Interpol1DLinear_is_in_range)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_int_t)
NS(Interpol1DLinear_lower_abscissa_index)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DLinear_floor_abscissa)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DLinear_ceil_abscissa)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DLinear_evaluate)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DLinear_set_t0)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t0 );

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DLinear_set_dt)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const dt );

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DLinear_set_num_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_int_t) const num_values );

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DLinear_set_values_begin_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(buffer_addr_t) const values_begin_addr );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear) const*
NS(Interpol1DLinear_const_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_from_obj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    NS(Object)* SIXTRL_RESTRICT obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear) const*
NS(Interpol1DLinear_const_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Interpol1DLinear_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear)
        *const SIXTRL_RESTRICT interpol, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Interpol1DLinear_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear)
        *const SIXTRL_RESTRICT interpol, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Interpol1DLinear_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear)
        *const SIXTRL_RESTRICT interpol );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear) const*
NS(Interpol1DLinear_const_from_buffer)(
    SIXTRL_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_from_buffer)(
    SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Interpol1DLinear_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(interpol_1d_int_t) const num_values,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(interpol_1d_int_t) const num_values );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values,
    NS(buffer_addr_t) const values_begin_addr );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol );

#endif /* defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Interpol1DLinear_copy)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear)
        *const SIXTRL_RESTRICT source );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_preset_ext)( SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
    SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Interpol1DLinear_clear_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(object_type_id_t)
NS(Interpol1DLinear_type_id_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(Interpol1DLinear_num_dataptrs_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(Interpol1DLinear_num_slots_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(buffer_size_t) const slot_size );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_real_t)
NS(Interpol1DLinear_t0_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_real_t)
NS(Interpol1DLinear_dt_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_int_t)
NS(Interpol1DLinear_num_values_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_addr_t)
NS(Interpol1DLinear_values_begin_addr_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t) const*
NS(Interpol1DLinear_const_values_begin_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t)*
NS(Interpol1DLinear_values_begin_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Interpol1DLinear_is_in_range_ext)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_int_t)
NS(Interpol1DLinear_lower_abscissa_index_ext)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_real_t)
NS(Interpol1DLinear_floor_abscissa_ext)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_real_t)
NS(Interpol1DLinear_ceil_abscissa_ext)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_real_t)
NS(Interpol1DLinear_evaluate_ext)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Interpol1DLinear_set_t0_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t0 );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Interpol1DLinear_set_dt_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const dt );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Interpol1DLinear_set_num_values_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_int_t) const num_values );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Interpol1DLinear_set_values_begin_addr_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(buffer_addr_t) const values_begin_addr );

#endif /* !defined( _GPUCODE ) */

/* ========================================================================= */

typedef SIXTRL_UINT64_T NS(cubic_boundary_type_t);

#if !defined( SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_NATURAL )
    #define SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_NATURAL 0
#endif /* !defined( SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_NATURAL ) */

#if !defined( SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_IMPLICIT )
    #define SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_IMPLICIT 1
#endif /* !defined( SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_IMPLICIT ) */

#if !defined( SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_CLAMPED )
    #define SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_CLAMPED 2
#endif /* !defined( SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_CLAMPED ) */

#if !defined( SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_NOT_A_KNOT )
    #define SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_NOT_A_KNOT 3
#endif /* !defined( SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_NOT_A_KNOT ) */

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(cubic_boundary_type_t) const
    NS(INTERPOL_1D_CUBIC_BOUNDARY_NATURAL) = ( NS(cubic_boundary_type_t)
        )SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_NATURAL;

SIXTRL_STATIC_VAR NS(cubic_boundary_type_t) const
    NS(INTERPOL_1D_CUBIC_BOUNDARY_IMPLICIT) = ( NS(cubic_boundary_type_t)
        )SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_IMPLICIT;

SIXTRL_STATIC_VAR NS(cubic_boundary_type_t) const
    NS(INTERPOL_1D_CUBIC_BOUNDARY_CLAMPED) = ( NS(cubic_boundary_type_t)
        )SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_CLAMPED;

SIXTRL_STATIC_VAR NS(cubic_boundary_type_t) const
    NS(INTERPOL_1D_CUBIC_BOUNDARY_NOT_A_KNOT) = ( NS(cubic_boundary_type_t)
        )SIXTRL_INTERPOL_1D_CUBIC_BOUNDARY_NOT_A_KNOT;

#endif /* !defined( _GPUCODE ) */

typedef struct NS(Interpol1DCubic)
{
    NS(interpol_1d_real_t)      t0                   SIXTRL_ALIGN( 8 );
    NS(interpol_1d_real_t)      dt                   SIXTRL_ALIGN( 8 );
    NS(interpol_1d_int_t)       num_values           SIXTRL_ALIGN( 8 );
    NS(cubic_boundary_type_t)   begin_boundary_type  SIXTRL_ALIGN( 8 );
    NS(interpol_1d_real_t)      begin_boundary_param SIXTRL_ALIGN( 8 );
    NS(cubic_boundary_type_t)   end_boundary_type    SIXTRL_ALIGN( 8 );
    NS(interpol_1d_real_t)      end_boundary_param   SIXTRL_ALIGN( 8 );
    NS(buffer_addr_t)           values_begin_addr    SIXTRL_ALIGN( 8 );
    NS(buffer_addr_t)           derivs_begin_addr    SIXTRL_ALIGN( 8 );
}
NS(Interpol1DCubic);

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)*
NS(Interpol1DCubic_preset)( SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)*
    SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DCubic_clear)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(object_type_id_t)
NS(Interpol1DCubic_type_id)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(Interpol1DCubic_num_dataptrs)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(Interpol1DCubic_num_slots)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol,
    NS(buffer_size_t) const slot_size );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_t0)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_t_end)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_dt)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_int_t)
NS(Interpol1DCubic_num_values)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );


SIXTRL_STATIC SIXTRL_FN NS(cubic_boundary_type_t)
NS(Interpol1DCubic_begin_boundary_type)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_begin_boundary_param)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );


SIXTRL_STATIC SIXTRL_FN NS(cubic_boundary_type_t)
NS(Interpol1DCubic_end_boundary_type)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_end_boundary_param)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );


SIXTRL_STATIC SIXTRL_FN NS(buffer_addr_t)
NS(Interpol1DCubic_values_begin_addr)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t) const*
NS(Interpol1DCubic_const_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t)*
NS(Interpol1DCubic_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );


SIXTRL_STATIC SIXTRL_FN NS(buffer_addr_t)
NS(Interpol1DCubic_derivatives_begin_addr)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t) const*
NS(Interpol1DCubic_const_derivatives_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t)*
NS(Interpol1DCubic_derivatives_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN bool NS(Interpol1DCubic_is_in_range)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DCubic) *const
        SIXTRL_RESTRICT interpol, NS(interpol_1d_real_t) const t );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_int_t)
NS(Interpol1DCubic_lower_abscissa_index)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DCubic) *const
        SIXTRL_RESTRICT interpol, NS(interpol_1d_real_t) const t );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_floor_abscissa)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DCubic) *const
        SIXTRL_RESTRICT interpol, NS(interpol_1d_real_t) const t );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_ceil_abscissa)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DCubic) *const
        SIXTRL_RESTRICT interpol, NS(interpol_1d_real_t) const t );

SIXTRL_STATIC SIXTRL_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_evaluate)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DCubic) *const
        SIXTRL_RESTRICT interpol, NS(interpol_1d_real_t) const t );

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Interpol1DCubic_init)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_int_t) const num_values,
    SIXTRL_ARGPTR_DEC NS(interpol_1d_real_t) const* SIXTRL_RESTRICT

#endif /* !defined( _GPUCODE ) */

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DCubic_set_t0)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t0 );

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DCubic_set_dt)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const dt );

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DCubic_set_num_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_int_t) const num_values );


SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DCubic_set_values_begin_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(buffer_addr_t) const values_begin_addr );

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DCubic_set_derivatives_begin_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(buffer_addr_t) const derivatives_begin_addr );


SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DCubic_set_begin_boundary_param)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const begin_boundary_param );

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DCubic_set_begin_boundary_type)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(cubic_boundary_type_t) const begin_boundary_type );

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DCubic_set_end_boundary_param)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const end_boundary_param );

SIXTRL_STATIC SIXTRL_FN void NS(Interpol1DCubic_set_end_boundary_type)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(cubic_boundary_type_t) const end_boundary_type );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic) const*
NS(Interpol1DCubic_const_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)*
NS(Interpol1DCubic_from_obj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    NS(Object)* SIXTRL_RESTRICT obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic) const*
NS(Interpol1DCubic_const_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)*
NS(Interpol1DCubic_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Interpol1DCubic_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DCubic)
        *const SIXTRL_RESTRICT interpol, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Interpol1DCubic_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DCubic)
        *const SIXTRL_RESTRICT interpol, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Interpol1DCubic_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DCubic)
        *const SIXTRL_RESTRICT interpol );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic) const*
NS(Interpol1DCubic_const_from_buffer)(
    SIXTRL_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)*
NS(Interpol1DCubic_from_buffer)(
    SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Interpol1DCubic_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(interpol_1d_int_t) const num_values,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)*
NS(Interpol1DCubic_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(interpol_1d_int_t) const num_values );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)*
NS(Interpol1DCubic_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values,
    NS(buffer_addr_t) const values_begin_addr );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)*
NS(Interpol1DCubic_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC const NS(Interpol1DCubic) *const
        SIXTRL_RESTRICT interpol );

#endif /* defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Interpol1DCubic_copy)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DCubic)
        *const SIXTRL_RESTRICT source );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)*
NS(Interpol1DCubic_preset_ext)( SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)*
    SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Interpol1DCubic_clear_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(object_type_id_t)
NS(Interpol1DCubic_type_id_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(Interpol1DCubic_num_dataptrs_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(Interpol1DCubic_num_slots_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol,
    NS(buffer_size_t) const slot_size );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_t0_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_dt_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_int_t)
NS(Interpol1DCubic_num_values_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_addr_t)
NS(Interpol1DCubic_values_begin_addr_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t) const*
NS(Interpol1DCubic_const_values_begin_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t)*
NS(Interpol1DCubic_values_begin_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Interpol1DCubic_is_in_range_ext)(
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_int_t)
NS(Interpol1DCubic_lower_abscissa_index_ext)(
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_floor_abscissa_ext)(
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_ceil_abscissa_ext)(
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(interpol_1d_real_t)
NS(Interpol1DCubic_evaluate_ext)(
    NS(Interpol1DCubic) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Interpol1DCubic_set_t0_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t0 );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Interpol1DCubic_set_dt_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const dt );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Interpol1DCubic_set_num_values_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_int_t) const num_values );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Interpol1DCubic_set_values_begin_addr_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DCubic)* SIXTRL_RESTRICT interpol,
    NS(buffer_addr_t) const values_begin_addr );

#endif /* !defined( _GPUCODE ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */


#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(interpol_1d_real_t) NS(Interpol1D_abscissa_t_end)(
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values )
{
    return t0 + ( NS(interpol_1d_real_t) )num_values * dt;
}

SIXTRL_INLINE bool NS(Interpol1D_abscissa_value_is_in_range)(
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values, NS(interpol_1d_real_t) const t )
{
    return ( ( t0 <= t ) &&
             ( NS(Interpol1D_abscissa_t_end)( t0, dt, num_values ) >= t ) );
}

SIXTRL_INLINE NS(interpol_1d_int_t) NS(Interpol1D_abscissa_lower_index)(
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values, NS(interpol_1d_real_t) const t )
{
    SIXTRL_ASSERT( t0 <= t );
    SIXTRL_ASSERT( dt > ( NS(interpol_1d_real_t) )0.0 );
    SIXTRL_ASSERT( ( t0 + ( NS(interpol_1d_real_t) )num_values * dt ) >= t );

    return ( NS(interpol_1d_int_t) )( ( t - t0 ) / dt );
}

SIXTRL_INLINE NS(interpol_1d_real_t) NS(Interpol1D_abscissa_floor_value)(
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values, NS(interpol_1d_real_t) const t )
{
    typedef NS(interpol_1d_real_t) real_t;

    SIXTRL_ASSERT( t0 <= t );
    SIXTRL_ASSERT( dt > ( real_t )0.0 );

    return t0 + dt * ( real_t )NS(Interpol1D_abscissa_lower_index)(
        t0, dt, num_values, t );
}

SIXTRL_INLINE NS(interpol_1d_real_t) NS(Interpol1D_abscissa_ceil_value)(
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values, NS(interpol_1d_real_t) const t )
{
    typedef NS(interpol_1d_real_t) real_t;

    SIXTRL_ASSERT( t0 <= t );
    SIXTRL_ASSERT( dt > ( real_t )0.0 );

    return t0 + dt + dt * ( real_t )NS(Interpol1D_abscissa_lower_index)(
        t0, dt, num_values, t );
}

/* ************************************************************************* */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_preset)( SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
    SIXTRL_RESTRICT interpol )
{
    typedef NS(interpol_1d_real_t) real_t;

    if( interpol != SIXTRL_NULLPTR )
    {
        NS(Interpol1DLinear_set_t0)( interpol, ( real_t )0.0 );
        NS(Interpol1DLinear_set_dt)( interpol, ( real_t )1.0 );
        NS(Interpol1DLinear_set_num_values)( interpol, 0 );
        NS(Interpol1DLinear_set_values_begin_addr)(
            interpol, ( NS(buffer_addr_t) )0u );
    }

    return interpol;
}

SIXTRL_INLINE void NS(Interpol1DLinear_clear)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol )
{
    typedef NS(interpol_1d_real_t) real_t;
    typedef NS(interpol_1d_int_t)  int_t;

    SIXTRL_STATIC_VAR real_t const ZERO = ( real_t )0.0;

    if( interpol != SIXTRL_NULLPTR )
    {
        int_t const nn = NS(Interpol1DLinear_num_values)( interpol );
        SIXTRL_BUFFER_DATAPTR_DEC real_t* ptr_values_begin =
            NS(Interpol1DLinear_values_begin)( interpol );

        NS(Interpol1DLinear_set_dt)( interpol, ZERO );

        if( ( nn > ( int_t )0 ) && ( ptr_values_begin != SIXTRL_NULLPTR ) )
        {
            SIXTRACKLIB_SET_VALUES( real_t, ptr_values_begin, nn, ZERO );
        }
    }
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(object_type_id_t) NS(Interpol1DLinear_type_id)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol )
{
    ( void )interpol;
    return NS(OBJECT_TYPE_INTERPOL_1D_LINEAR);
}

SIXTRL_INLINE NS(buffer_size_t) NS(Interpol1DLinear_num_dataptrs)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol )
{
    ( void )interpol;
    return ( NS(buffer_size_t) )1u;
}

SIXTRL_INLINE NS(buffer_size_t) NS(Interpol1DLinear_num_slots)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol,
    NS(buffer_size_t) const slot_size )
{
    typedef NS(buffer_size_t) buf_size_t;
    buf_size_t num_slots = ( buf_size_t )0u;

    if( ( interpol != SIXTRL_NULLPTR ) && ( slot_size > ( buf_size_t )0u ) )
    {
        buf_size_t interp_size = NS(ManagedBuffer_get_slot_based_length)(
            sizeof( NS(Interpol1DLinear) ), slot_size );

        data_size += NS(ManagedBuffer_get_slot_based_length)(
            sizeof( NS(interpol_1d_real_t) ) *
                NS(Interpol1DLinear_num_values)( interpol ), slot_size );

        num_slots = data_size / slot_size;

        if( ( num_slots * slot_size ) < data_size ) ++num_slots;
        SIXTRL_ASSERT( ( num_slots * slot_size ) >= data_size );
    }

    return num_slots;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(interpol_1d_real_t) NS(Interpol1DLinear_t0)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol )
{
    SIXTRL_ASSERT( interpol != SIXTRL_NULLPTR );
    return interpol->t0;
}

SIXTRL_INLINE NS(interpol_1d_real_t) NS(Interpol1DLinear_t_end)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol )
{
    typedef NS(interpol_1d_real_t) real_t;

    SIXTRL_ASSERT( interpol != SIXTRL_NULLPTR );
    return NS(Interpol1DLinear_t0)( interpol ) +
        ( real_t )NS(Interpol1DLinear_num_values)( interpol ) *
            NS(Interpol1DLinear_dt)( interpol );
}

SIXTRL_INLINE NS(interpol_1d_real_t) NS(Interpol1DLinear_dt)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol )
{
    SIXTRL_ASSERT( interpol != SIXTRL_NULLPTR );
    return interpol->dt;
}

SIXTRL_INLINE NS(interpol_1d_int_t) NS(Interpol1DLinear_num_values)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol )
{
    SIXTRL_ASSERT( interpol != SIXTRL_NULLPTR );
    return interpol->num_values;
}

SIXTRL_INLINE NS(buffer_addr_t) NS(Interpol1DLinear_values_begin_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol )
{
    SIXTRL_ASSERT( interpol != SIXTRL_NULLPTR );
    return interpol->values_begin_addr;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t) const*
NS(Interpol1DLinear_const_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol )
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t) const* )(
        uintptr_t )NS(Interpol1DLinear_values_begin_addr)( interpol );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t)*
NS(Interpol1DLinear_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol )
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t)* )(
        uintptr_t )NS(Interpol1DLinear_values_begin_addr)( interpol );
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE bool NS(Interpol1DLinear_is_in_range)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t )
{
    return NS(Interpol1D_abscissa_value_is_in_range)(
        NS(Interpol1DLinear_t0)( interpol ),
        NS(Interpol1DLinear_dt)( interpol ),
        NS(Interpol1DLinear_num_values)( interpol ), t );
}

SIXTRL_INLINE NS(interpol_1d_int_t) NS(Interpol1DLinear_lower_abscissa_index)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t )
{
    return NS(Interpol1D_abscissa_lower_index)(
        NS(Interpol1DLinear_t0)( interpol ),
        NS(Interpol1DLinear_dt)( interpol ),
        NS(Interpol1DLinear_num_values)( interpol ), t );
}

SIXTRL_INLINE NS(interpol_1d_real_t) NS(Interpol1DLinear_floor_abscissa)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t )
{
    return NS(Interpol1D_abscissa_floor_value)(
        NS(Interpol1DLinear_t0)( interpol ),
        NS(Interpol1DLinear_dt)( interpol ),
        NS(Interpol1DLinear_num_values)( interpol ), t );
}

SIXTRL_INLINE NS(interpol_1d_real_t) NS(Interpol1DLinear_ceil_abscissa)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t )
{
    return NS(Interpol1D_abscissa_ceil_value)(
        NS(Interpol1DLinear_t0)( interpol ),
        NS(Interpol1DLinear_dt)( interpol ),
        NS(Interpol1DLinear_num_values)( interpol ), t );
}

SIXTRL_INLINE NS(interpol_1d_real_t) NS(Interpol1DLinear_evaluate)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t )
{
    typedef NS(interpol_1d_real_t) real_t;

    real_t const t0 = NS(Interpol1DLinear_t0)( interpol );
    real_t const dt = NS(Interpol1DLinear_dt)( interpol );

    NS(interpol_1d_int_t) const idx = NS(Interpol1D_abscissa_lower_index)(
        t0, dt, NS(Interpol1DLinear_num_values)( interpol ), t );

    real_t const t_min = t0 + dt * ( real_t )idx;

    SIXTRL_BUFFER_DATAPTR_DEC real_t const* ptr_values_begin =
        NS(Interpol1DLinear_const_values_begin)( interpol );

    SIXTRL_ASSERT( idx >= ( NS(interpol_1d_int_t) )0 );
    SIXTRL_ASSERT( idx < NS(Interpol1DLinear_num_values)( interpol ) );
    SIXTRL_ASSERT( dt > ( real_t )0.0 );
    SIXTRL_ASSERT( t_min <= t );
    SIXTRL_ASSERT( t <= ( t_min + dt ) );
    SIXTRL_ASSERT( ptr_values_begin != SIXTRL_NULLPTR );

    return ( ( t - t_min ) * ( ptr_values_begin[ idx + 1 ] -
                               ptr_values_begin[ idx ] ) ) / dt;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(Interpol1DLinear_set_t0)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t0 )
{
    if( interpol != SIXTRL_NULLPTR ) interpol->t0 = t0;
}

SIXTRL_INLINE void NS(Interpol1DLinear_set_dt)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const dt )
{
    if( interpol != SIXTRL_NULLPTR ) interpol->dt = dt;
}

SIXTRL_INLINE void NS(Interpol1DLinear_set_num_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_int_t) const num_values )
{
    if( interpol != SIXTRL_NULLPTR ) interpol->num_values = num_values;
}

SIXTRL_INLINE void NS(Interpol1DLinear_set_values_begin_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(buffer_addr_t) const values_begin_addr )
{
    if( interpol != SIXTRL_NULLPTR )
        interpol->values_begin_addr = values_begin_addr;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear) const*
NS(Interpol1DLinear_const_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT obj )
{
    return ( ( obj != SIXTRL_NULLPTR ) &&
             ( NS(Object_get_type_id)( obj ) ==
                 NS(OBJECT_TYPE_INTERPOL_1D_LINEAR) ) &&
             ( NS(Object_get_size)( obj ) >= sizeof( NS(Interpol1DLinear) ) ) )
        ? ( SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear) const* )(
                uintptr_t )NS(Object_get_begin_addr)( obj )
        : SIXTRL_NULLPTR;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_from_obj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    NS(Object)* SIXTRL_RESTRICT obj )
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
        )NS(Interpol1DLinear_const_from_obj_index)( obj );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear) const*
NS(Interpol1DLinear_const_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(Interpol1DLinear_const_from_obj_index)(
        NS(ManagedBuffer_get_const_object)( buffer, index, slot_size ) );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(Interpol1DLinear_from_obj_index)(
        NS(ManagedBuffer_get_object)( buffer, index, slot_size ) );
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(arch_status_t) NS(Interpol1DLinear_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear)
        *const SIXTRL_RESTRICT interpol, NS(buffer_size_t) const slot_size )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    ( void )interpol;

    if( ( offsets_begin != SIXTRL_NULLPTR ) &&
        ( max_num_offsets >= ( NS(buffer_size_t) )1 ) &&
        ( slot_size > ( NS(buffer_size_t) )0u ) )
    {
        offsets_begin[ 0 ] = ( NS(buffer_size_t) )offsetof(
            NS(Interpol1DLinear), values_begin_addr );

        status = SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(Interpol1DLinear_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear)
        *const SIXTRL_RESTRICT interpol, NS(buffer_size_t) const slot_size )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    ( void )interpol;

    if( ( sizes_begin != SIXTRL_NULLPTR ) &&
        ( max_num_sizes >= ( NS(buffer_size_t) )1 ) &&
        ( slot_size > ( NS(buffer_size_t) )0u ) )
    {
        sizes_begin[ 0 ] = sizeof( NS(interpol_1d_real_t) );
        status = SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(Interpol1DLinear_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear)
        *const SIXTRL_RESTRICT interpol )
{
    typedef NS(interpol_1d_int_t) int_t;

    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    ( void )interpol;

    if( ( sizes_begin != SIXTRL_NULLPTR ) &&
        ( max_num_sizes >= ( NS(buffer_size_t) )1 ) &&
        ( interpol != SIXTRL_NULLPTR ) )
    {
        int_t const num_values = NS(Interpol1DLinear_num_values)( interpol );

        counts_begin[ 0 ] = ( num_values >= ( int_t )0 )
            ? ( NS(buffer_size_t) )num_values : ( NS(buffer_size_t) )0u;

        status = SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BE_BEAM_FIELDS_INTERPOL_1D_C99_H__ */
