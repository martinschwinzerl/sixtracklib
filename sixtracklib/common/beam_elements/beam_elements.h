#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_ELEMENTS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_ELEMENTS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/all_beam_elements.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

/* ========================================================================= */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_beam_element)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(BeamElements_cobj_calc_buffer_parameters_for_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_dataptrs,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(BeamElements_copy_for_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)* SIXTRL_RESTRICT dest,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT source ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(BeamElements_clear_object)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool
NS(BeamElements_all_beam_elements_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool
NS(BeamElements_all_beam_elements_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(BeamElements_all_beam_elements_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT buffer ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(BeamElements_num_beam_elements_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(BeamElements_num_beam_elements_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(BeamElements_num_beam_elements_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT buffer ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(BeamElements_cobj_calc_buffer_parameters_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_dataptrs,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(BeamElements_cobj_calc_buffer_parameters_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_dataptrs,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(BeamElements_cobj_calc_buffer_parameters_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer)
        *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_dataptrs
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(CObjIndex_is_beam_element_ext)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */
#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */
/* =====            Implementation of inline functions                ====== */
/* ========================================================================= */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE bool NS(CObjIndex_is_beam_element)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    bool is_beam_element = false;

    if( obj != SIXTRL_NULLPTR )
    {
        switch( NS(CObjIndex_type_id)( obj ) )
        {
            case NS(COBJECTS_TYPE_ID_CAVITY):
            case NS(COBJECTS_TYPE_ID_DIPOLE_EDGE):
            case NS(COBJECTS_TYPE_ID_DRIFT):
            case NS(COBJECTS_TYPE_ID_DRIFT_EXACT):
            case NS(COBJECTS_TYPE_ID_END_TRACKING):
            case NS(COBJECTS_TYPE_ID_MONITOR):
            case NS(COBJECTS_TYPE_ID_MULTIPOLE):
            case NS(COBJECTS_TYPE_ID_LIMIT_RECT):
            case NS(COBJECTS_TYPE_ID_LIMIT_ELLIPSE):
            case NS(COBJECTS_TYPE_ID_LIMIT_RECT_ELLIPSE):
            case NS(COBJECTS_TYPE_ID_RF_MULTIPOLE):
            case NS(COBJECTS_TYPE_ID_SROTATION):
            case NS(COBJECTS_TYPE_ID_XY_SHIFT):
            {
                is_beam_element = true;
                break;
            }

            #if !defined( SIXTRL_DISABLE_BEAM_BEAM )

            case NS(COBJECTS_TYPE_ID_BEAM_BEAM_4D):
            case NS(COBJECTS_TYPE_ID_BEAM_BEAM_6D):
            case NS(COBJECTS_TYPE_ID_SC_COASTING):
            case NS(COBJECTS_TYPE_ID_SC_QGAUSSIAN_PROFILE):
            case NS(COBJECTS_TYPE_ID_SC_INTERPOLATED_PROFILE):
            {
                is_beam_element = true;
                break;
            }

            #endif /* !defined( SIXTRL_DISABLE_BEAM_BEAM ) */

            #if !defined( SIXTRL_DISABLE_TRICUB )

            case NS(COBJECTS_TYPE_ID_TRICUB):
            {
                is_beam_element = true;
                break;
            }

            #endif /* !defined( SIXTRL_DISABLE_TRICUB ) */

            default:
            {
                is_beam_element = false;
            }
        };
    }

    return is_beam_element;
}

SIXTRL_INLINE NS(status_type)
NS(BeamElements_cobj_calc_buffer_parameters_for_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_n_objs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_n_ptrs,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( obj != SIXTRL_NULLPTR ) && ( slot_size > ( NS(cobj_size_type) )0 ) )
    {
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) n_slots = ( NS(cobj_size_type) )0;
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) n_objs  = ( NS(cobj_size_type) )0;
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) n_ptrs  = ( NS(cobj_size_type) )0;

        switch( NS(CObjIndex_type_id)( obj ) )
        {
            case NS(COBJECTS_TYPE_ID_CAVITY):
            {
                if( NS(CObjIndex_is_cavity)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(Cavity_cobj_num_dataptrs)();
                    n_slots = NS(Cavity_cobj_required_num_bytes)(
                        NS(Cavity_const_from_cobj_index)( obj ), slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
                break;
            }

            case NS(COBJECTS_TYPE_ID_DIPOLE_EDGE):
            {
                if( NS(CObjIndex_is_dipole_edge)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(DipoleEdge_cobj_num_dataptrs)();
                    n_slots = NS(DipoleEdge_cobj_required_num_bytes)(
                        NS(DipoleEdge_const_from_cobj_index)( obj ), slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

                break;
            }

            case NS(COBJECTS_TYPE_ID_DRIFT):
            {
                if( NS(CObjIndex_is_drift)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(Drift_cobj_num_dataptrs)();
                    n_slots = NS(Drift_cobj_required_num_bytes)(
                        NS(Drift_const_from_cobj_index)( obj ), slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

                break;
            }

            case NS(COBJECTS_TYPE_ID_DRIFT_EXACT):
            {
                if( NS(CObjIndex_is_drift_exact)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(DriftExact_cobj_num_dataptrs)();
                    n_slots = NS(DriftExact_cobj_required_num_bytes)(
                        NS(DriftExact_const_from_cobj_index)( obj ), slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

                break;
            }

            case NS(COBJECTS_TYPE_ID_END_TRACKING):
            {
                if( NS(CObjIndex_is_end_tracking)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(EndTracking_cobj_num_dataptrs)();
                    n_slots = NS(EndTracking_cobj_required_num_bytes)(
                        NS(EndTracking_const_from_cobj_index)( obj ), slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

                break;
            }

            case NS(COBJECTS_TYPE_ID_MONITOR):
            {
                if( NS(CObjIndex_is_monitor)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(Monitor_cobj_num_dataptrs)();
                    n_slots = NS(Monitor_cobj_required_num_bytes)(
                        NS(Monitor_const_from_cobj_index)( obj ), slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

                break;
            }

            case NS(COBJECTS_TYPE_ID_MULTIPOLE):
            {
                if( NS(CObjIndex_is_multipole)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(Multipole_cobj_num_dataptrs)();
                    n_slots = NS(Multipole_cobj_required_num_bytes)(
                        NS(Multipole_const_from_cobj_index)( obj ), slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

                break;
            }

            case NS(COBJECTS_TYPE_ID_LIMIT_RECT):
            {
                if( NS(CObjIndex_is_limit_rect)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(LimitRect_cobj_num_dataptrs)();
                    n_slots = NS(LimitRect_cobj_required_num_bytes)(
                        NS(LimitRect_const_from_cobj_index)( obj ), slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

                break;
            }

            case NS(COBJECTS_TYPE_ID_LIMIT_ELLIPSE):
            {
                if( NS(CObjIndex_is_limit_ellipse)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(LimitEllipse_cobj_num_dataptrs)();
                    n_slots = NS(LimitEllipse_cobj_required_num_bytes)(
                        NS(LimitEllipse_const_from_cobj_index)(
                            obj ), slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

                break;
            }

            case NS(COBJECTS_TYPE_ID_LIMIT_RECT_ELLIPSE):
            {
                if( NS(CObjIndex_is_limit_rect_ellipse)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(LimitRectEllipse_cobj_num_dataptrs)();
                    n_slots = NS(LimitRectEllipse_cobj_required_num_bytes)(
                        NS(LimitRectEllipse_const_from_cobj_index)( obj ),
                            slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

                break;
            }

            case NS(COBJECTS_TYPE_ID_RF_MULTIPOLE):
            {
                if( NS(CObjIndex_is_rf_multipole)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(RFMultipole_cobj_num_dataptrs)();
                    n_slots = NS(RFMultipole_cobj_required_num_bytes)(
                        NS(RFMultipole_const_from_cobj_index)( obj ), slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

                break;
            }

            case NS(COBJECTS_TYPE_ID_SROTATION):
            {
                if( NS(CObjIndex_is_srotation)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(SRotation_cobj_num_dataptrs)();
                    n_slots = NS(SRotation_cobj_required_num_bytes)(
                        NS(SRotation_const_from_cobj_index)( obj ), slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

                break;
            }

            case NS(COBJECTS_TYPE_ID_XY_SHIFT):
            {
                if( NS(CObjIndex_is_xy_shift)( obj ) ) {
                    ++n_objs;
                    n_ptrs = NS(XYShift_cobj_num_dataptrs)();
                    n_slots = NS(XYShift_cobj_required_num_bytes)(
                        NS(XYShift_const_from_cobj_index)( obj ), slot_size );
                    n_slots /= slot_size;
                    status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

                break;
            }

            default:
            {
                status= ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
            }
        };

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            if(  ptr_n_slots != SIXTRL_NULLPTR ) *ptr_n_slots += n_slots;
            if(  ptr_n_objs  != SIXTRL_NULLPTR ) *ptr_n_objs += n_objs;
            if(  ptr_n_ptrs  != SIXTRL_NULLPTR ) *ptr_n_ptrs += n_ptrs; }
    }

    return status;
}

SIXTRL_INLINE NS(status_type) NS(BeamElements_copy_for_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT dest,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) &&
        ( dest != src ) &&
        ( NS(CObjIndex_type_id)( dest ) == NS(CObjIndex_type_id)( src ) ) &&
        ( NS(CObjIndex_begin_addr)( dest ) != NS(CObjIndex_begin_addr)( src ) ) )
    {
        switch( NS(CObjIndex_type_id)( dest ) )
        {
            case NS(COBJECTS_TYPE_ID_CAVITY):
            {
                if( ( NS(CObjIndex_is_cavity)( dest ) ) &&
                    ( NS(CObjIndex_is_cavity)( src  ) ) )
                    status = NS(Cavity_copy)(
                        NS(Cavity_from_cobj_index)( dest ),
                        NS(Cavity_const_from_cobj_index)( src ) );

                break;
            }

            case NS(COBJECTS_TYPE_ID_DIPOLE_EDGE):
            {
                if( ( NS(CObjIndex_is_dipole_edge)( dest ) ) &&
                    ( NS(CObjIndex_is_dipole_edge)( src  ) ) )
                    status = NS(DipoleEdge_copy)(
                        NS(DipoleEdge_from_cobj_index)( dest ),
                        NS(DipoleEdge_const_from_cobj_index)( src ) );

                break;
            }

            case NS(COBJECTS_TYPE_ID_DRIFT):
            {
                if( ( NS(CObjIndex_is_drift)( dest ) ) &&
                    ( NS(CObjIndex_is_drift)( src  ) ) )
                    status = NS(Drift_copy)(
                        NS(Drift_from_cobj_index)( dest ),
                        NS(Drift_const_from_cobj_index)( src ) );

                break;
            }

            case NS(COBJECTS_TYPE_ID_DRIFT_EXACT):
            {
                if( ( NS(CObjIndex_is_drift_exact)( dest ) ) &&
                    ( NS(CObjIndex_is_drift_exact)( src  ) ) )
                    status = NS(DriftExact_copy)(
                        NS(DriftExact_from_cobj_index)( dest ),
                        NS(DriftExact_const_from_cobj_index)( src ) );

                break;
            }

            case NS(COBJECTS_TYPE_ID_END_TRACKING):
            {
                if( ( NS(CObjIndex_is_end_tracking)( dest ) ) &&
                    ( NS(CObjIndex_is_end_tracking)( src  ) ) )
                    status = NS(EndTracking_copy)(
                        NS(EndTracking_from_cobj_index)( dest ),
                        NS(EndTracking_const_from_cobj_index)( src ) );

                break;
            }

            case NS(COBJECTS_TYPE_ID_MONITOR):
            {
                if( ( NS(CObjIndex_is_monitor)( dest ) ) &&
                    ( NS(CObjIndex_is_monitor)( src  ) ) )
                    status = NS(Monitor_copy)(
                        NS(Monitor_from_cobj_index)( dest ),
                        NS(Monitor_const_from_cobj_index)( src ) );

                break;
            }

            case NS(COBJECTS_TYPE_ID_MULTIPOLE):
            {
                if( ( NS(CObjIndex_is_multipole)( dest ) ) &&
                    ( NS(CObjIndex_is_multipole)( src  ) ) )
                    status = NS(Multipole_copy)(
                        NS(Multipole_from_cobj_index)( dest ),
                        NS(Multipole_const_from_cobj_index)( src ) );

                break;
            }

            case NS(COBJECTS_TYPE_ID_LIMIT_RECT):
            {
                if( ( NS(CObjIndex_is_limit_rect)( dest ) ) &&
                    ( NS(CObjIndex_is_limit_rect)( src  ) ) )
                    status = NS(LimitRect_copy)(
                        NS(LimitRect_from_cobj_index)( dest ),
                        NS(LimitRect_const_from_cobj_index)( src ) );

                break;
            }

            case NS(COBJECTS_TYPE_ID_LIMIT_ELLIPSE):
            {
                if( ( NS(CObjIndex_is_limit_ellipse)( dest ) ) &&
                    ( NS(CObjIndex_is_limit_ellipse)( src  ) ) )
                    status = NS(LimitEllipse_copy)(
                        NS(LimitEllipse_from_cobj_index)( dest ),
                        NS(LimitEllipse_const_from_cobj_index)( src ) );

                break;
            }

            case NS(COBJECTS_TYPE_ID_LIMIT_RECT_ELLIPSE):
            {
                if( ( NS(CObjIndex_is_limit_rect_ellipse)( dest ) ) &&
                    ( NS(CObjIndex_is_limit_rect_ellipse)( src  ) ) )
                    status = NS(LimitRectEllipse_copy)(
                        NS(LimitRectEllipse_from_cobj_index)( dest ),
                        NS(LimitRectEllipse_const_from_cobj_index)( src ) );

                break;
            }

            case NS(COBJECTS_TYPE_ID_RF_MULTIPOLE):
            {
                if( ( NS(CObjIndex_is_rf_multipole)( dest ) ) &&
                    ( NS(CObjIndex_is_rf_multipole)( src  ) ) )
                    status = NS(RFMultipole_copy)(
                        NS(RFMultipole_from_cobj_index)( dest ),
                        NS(RFMultipole_const_from_cobj_index)( src ) );

                break;
            }

            case NS(COBJECTS_TYPE_ID_SROTATION):
            {
                if( ( NS(CObjIndex_is_srotation)( dest ) ) &&
                    ( NS(CObjIndex_is_srotation)( src  ) ) )
                    status = NS(SRotation_copy)(
                        NS(SRotation_from_cobj_index)( dest ),
                        NS(SRotation_const_from_cobj_index)( src ) );

                break;
            }

            case NS(COBJECTS_TYPE_ID_XY_SHIFT):
            {
                if( ( NS(CObjIndex_is_xy_shift)( dest ) ) &&
                    ( NS(CObjIndex_is_xy_shift)( src  ) ) )
                    status = NS(XYShift_copy)(
                        NS(XYShift_from_cobj_index)( dest ),
                        NS(XYShift_const_from_cobj_index)( src ) );

                break;
            }

            default:
            {
                status= ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
            }
        };
    }

    return status;
}

SIXTRL_INLINE NS(status_type) NS(BeamElements_clear_object)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( obj != SIXTRL_NULLPTR )
    {
        switch( NS(CObjIndex_type_id)( obj ) )
        {
            case NS(COBJECTS_TYPE_ID_CAVITY):
            {
                if( NS(CObjIndex_is_cavity)( obj ) )
                    status = NS(Cavity_clear)(
                        NS(Cavity_from_cobj_index)( obj ) );
                break;
            }

            case NS(COBJECTS_TYPE_ID_DIPOLE_EDGE):
            {
                if( NS(CObjIndex_is_dipole_edge)( obj ) )
                    status = NS(DipoleEdge_clear)(
                        NS(DipoleEdge_from_cobj_index)( obj ) );
                break;
            }

            case NS(COBJECTS_TYPE_ID_DRIFT):
            {
                if( NS(CObjIndex_is_drift)( obj ) )
                    status = NS(Drift_clear)(
                        NS(Drift_from_cobj_index)( obj ) );
                break;
            }

            case NS(COBJECTS_TYPE_ID_DRIFT_EXACT):
            {
                if( NS(CObjIndex_is_drift_exact)( obj ) )
                    status = NS(DriftExact_clear)(
                        NS(DriftExact_from_cobj_index)( obj ) );
                break;
            }

            case NS(COBJECTS_TYPE_ID_END_TRACKING):
            {
                if( NS(CObjIndex_is_end_tracking)( obj ) )
                    status = NS(EndTracking_clear)(
                        NS(EndTracking_from_cobj_index)( obj ) );
                break;
            }

            case NS(COBJECTS_TYPE_ID_MONITOR):
            {
                if( NS(CObjIndex_is_monitor)( obj ) )
                    status = NS(Monitor_clear)(
                        NS(Monitor_from_cobj_index)( obj ) );
                break;
            }

            case NS(COBJECTS_TYPE_ID_MULTIPOLE):
            {
                if( NS(CObjIndex_is_multipole)( obj ) )
                    status = NS(Multipole_clear)(
                        NS(Multipole_from_cobj_index)( obj ) );
                break;
            }

            case NS(COBJECTS_TYPE_ID_LIMIT_RECT):
            {
                if( NS(CObjIndex_is_limit_rect)( obj ) )
                    status = NS(LimitRect_clear)(
                        NS(LimitRect_from_cobj_index)( obj ) );
                break;
            }

            case NS(COBJECTS_TYPE_ID_LIMIT_ELLIPSE):
            {
                if( NS(CObjIndex_is_limit_ellipse)( obj ) )
                    status = NS(LimitEllipse_clear)(
                        NS(LimitEllipse_from_cobj_index)( obj ) );
                break;
            }

            case NS(COBJECTS_TYPE_ID_LIMIT_RECT_ELLIPSE):
            {
                if( NS(CObjIndex_is_limit_rect_ellipse)( obj ) )
                    status = NS(LimitRectEllipse_clear)(
                        NS(LimitRectEllipse_from_cobj_index)( obj ) );
                break;
            }

            case NS(COBJECTS_TYPE_ID_RF_MULTIPOLE):
            {
                if( NS(CObjIndex_is_rf_multipole)( obj ) )
                    status = NS(RFMultipole_clear)(
                        NS(RFMultipole_from_cobj_index)( obj ) );
                break;
            }

            case NS(COBJECTS_TYPE_ID_SROTATION):
            {
                if( NS(CObjIndex_is_srotation)( obj ) )
                    status = NS(SRotation_clear)(
                        NS(SRotation_from_cobj_index)( obj ) );
                break;
            }

            case NS(COBJECTS_TYPE_ID_XY_SHIFT):
            {
                if( NS(CObjIndex_is_xy_shift)( obj ) )
                    status = NS(XYShift_clear)(
                        NS(XYShift_from_cobj_index)( obj ) );
                break;
            }

            default:
            {
                status= ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
            }
        };
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(BeamElements_all_beam_elements_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT {
    bool are_all_beam_elements = true;
    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) ) {
        SIXTRL_ASSERT( ( uintptr_t )it <= ( uintptr_t )end );
        while( ( it != end ) && ( are_all_beam_elements ) ) {
            are_all_beam_elements &= NS(CObjIndex_is_beam_element)( it++ ); }
    }
    return are_all_beam_elements; }

SIXTRL_INLINE bool NS(BeamElements_all_beam_elements_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(BeamElements_all_beam_elements_in_cobj_index_range)(
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ) ); }

SIXTRL_INLINE bool NS(BeamElements_all_beam_elements_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer
) SIXTRL_NOEXCEPT { return NS(BeamElements_all_beam_elements_in_cobj_index_range)(
        NS(CBuffer_const_objects_begin)( buffer ),
        NS(CBuffer_const_objects_end)( buffer ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(size_type)
NS(BeamElements_num_beam_elements_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT {
    NS(size_type) num_beam_elements = ( NS(size_type) )0u;
    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) ) {
        SIXTRL_ASSERT( ( uintptr_t )it < ( uintptr_t )end );
        for( ; it != end ; ++it )
        {
            if( NS(CObjIndex_is_beam_element)( it ) ) ++num_beam_elements;
        }
    }
    return num_beam_elements; }

SIXTRL_INLINE NS(size_type)
NS(BeamElements_num_beam_elements_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(BeamElements_num_beam_elements_in_cobj_index_range)(
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ) ); }

SIXTRL_INLINE NS(size_type) NS(BeamElements_num_beam_elements_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer
) SIXTRL_NOEXCEPT {
    return NS(BeamElements_num_beam_elements_in_cobj_index_range)(
        NS(CBuffer_const_objects_begin)( buffer ),
        NS(CBuffer_const_objects_end)( buffer ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(status_type)
NS(BeamElements_cobj_calc_buffer_parameters_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_dataptrs,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) ) {
        SIXTRL_ASSERT( ( uintptr_t )it < ( uintptr_t )end );
        while( ( it != end ) &&
               ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) )
        {
            status = NS(BeamElements_cobj_calc_buffer_parameters_for_cobj_index)(
                it++, n_slots, n_objects, n_dataptrs, slot_size );
        }
    } return status; }

SIXTRL_INLINE NS(status_type)
NS(BeamElements_cobj_calc_buffer_parameters_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_dataptrs,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(BeamElements_cobj_calc_buffer_parameters_in_cobj_index_range)(
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ),
        n_slots, n_objects, n_dataptrs, slot_size ); }

SIXTRL_INLINE NS(status_type)
NS(BeamElements_cobj_calc_buffer_parameters_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT n_dataptrs
) SIXTRL_NOEXCEPT {
    return NS(BeamElements_cobj_calc_buffer_parameters_in_cobj_index_range)(
        NS(CBuffer_const_objects_begin)( buffer ),
        NS(CBuffer_const_objects_end)( buffer ),
        n_slots, n_objects, n_dataptrs, NS(CBuffer_slot_size)( buffer ) ); }

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_H__ */
