#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/be_beamfields/interpol_1d.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE )

SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear) const*
NS(Interpol1DLinear_const_from_buffer)(
    SIXTRL_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index )
{
    return NS(Interpol1DLinear_const_from_obj_index)(
        NS(Buffer_get_const_object)( buffer, index ) );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_from_buffer)(
    SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index )
{
    return NS(Interpol1DLinear_from_obj_index)(
        NS(Buffer_get_object)( buffer, index ) );
}

/* ------------------------------------------------------------------------- */

bool NS(Interpol1DLinear_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(interpol_1d_int_t) const num_values,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs )
{
    typedef NS(buffer_size_t) buf_size_t;

    bool can_be_added = false;
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    NS(Interpol1DLinear) interpol;
    buf_size_t const num_dataptrs = NS(TriCubData_num_dataptrs)( &interpol );
    buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

    buf_size_t sizes[]  = { ( buf_size_t )0u };
    buf_size_t counts[] = { ( buf_size_t )0u };

    SIXTRL_ASSERT( num_dataptrs == ( buf_size_t )1u );

    NS(TriCubData_preset)( &interpol );
    NS(TriCubData_set_num_values)( &interpol, num_values );

    status = NS(Interpol1DLinear_attributes_sizes)(
        &sizes[ 0 ], ( buf_size_t )1u, &interpol, slot_size );

    if( status == NS(ARCH_STATUS_SUCCESS) )
    {
        status = NS(Interpol1DLinear_attributes_counts)(
            &counts[ 0 ], ( buf_size_t )1u, &interpol );
    }

    if( status == NS(ARCH_STATUS_SUCCESS) )
    {
        can_be_added = NS(Buffer_can_add_object)( buffer,
            sizeof( NS(Interpol1DLinear) ), num_dataptrs, sizes, counts,
                ptr_requ_objects, ptr_requ_slots, ptr_requ_dataptrs );
    }

    return can_be_added;
}

SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* NS(Interpol1DLinear_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(interpol_1d_int_t) const num_values )
{
    typedef NS(buffer_size_t) buf_size_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* ptr_interpol_t;
    ptr_interpol_t interpol = SIXTRL_NULLPTR;
    NS(arch_size_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    NS(Interpol1DLinear) temp_interpol;
    buf_size_t const num_dataptrs =
        NS(TriCubData_num_dataptrs)( &temp_interpol );

    buf_size_t offsets[] = { ( buf_size_t )0u };
    buf_size_t sizes[]   = { ( buf_size_t )0u };
    buf_size_t counts[]  = { ( buf_size_t )0u };
    buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

    SIXTRL_ASSERT( num_dataptrs == ( buf_size_t )1u );

    NS(Interpol1DLinear_preset)( &temp_interpol );
    NS(Interpol1DLinear_set_num_values)( &temp_interpol, num_values );

    status = NS(Interpol1DLinear_attributes_offsets)(
        &offsets[ 0 ], ( buf_size_t )1u ), &temp_interpol, slot_size );

    if( status == NS(ARCH_STATUS_SUCCESS) )
    {
        status = NS(Interpol1DLinear_attributes_counts)(
            &counts[ 0 ], ( buf_size_t )1u ), &temp_interpol );
    }

    if( status == NS(ARCH_STATUS_SUCCESS) )
    {
        status = NS(Interpol1DLinear_attributes_sizes)(
            &sizes[ 0 ], ( buf_size_t )1u ), &temp_interpol, slot_size );
    }

    if( status == NS(ARCH_STATUS_SUCCESS) )
    {
        NS(object_type_id_t) const type_id =
            NS(Interpol1DLinear_type_id)( &temp_interpol );

        interpol = ( ptr_interpol_t )( uintptr_t )NS(Object_get_begin_addr)(
            NS(Buffer_add_object)( buffer, &temp_interpol,
                sizeof( temp_interpol ), type_id, num_dataptrs, &offsets[ 0 ],
                    &sizes[ 0 ], &counts[ 0 ] ) );
    }

    return interpol;
}

SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* NS(Interpol1DLinear_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values,
    NS(buffer_addr_t) const values_begin_addr )
{
    typedef NS(buffer_size_t) buf_size_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* ptr_interpol_t;
    ptr_interpol_t interpol = SIXTRL_NULLPTR;
    NS(arch_size_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    NS(Interpol1DLinear) temp_interpol;
    buf_size_t const num_dataptrs =
        NS(TriCubData_num_dataptrs)( &temp_interpol );

    buf_size_t offsets[] = { ( buf_size_t )0u };
    buf_size_t sizes[]   = { ( buf_size_t )0u };
    buf_size_t counts[]  = { ( buf_size_t )0u };
    buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

    SIXTRL_ASSERT( num_dataptrs == ( buf_size_t )1u );

    NS(Interpol1DLinear_preset)( &temp_interpol );
    NS(Interpol1DLinear_set_t0)( &temp_interpol, t0 );
    NS(Interpol1DLinear_set_dt)( &temp_interpol, dt );
    NS(Interpol1DLinear_set_num_values)( &temp_interpol, num_values );
    NS(Interpol1DLinear_set_value_begin_addr)(
        &temp_interpol, valuges_begin_addr );

    status = NS(Interpol1DLinear_attributes_offsets)(
        &offsets[ 0 ], ( buf_size_t )1u ), &temp_interpol, slot_size );

    if( status == NS(ARCH_STATUS_SUCCESS) )
    {
        status = NS(Interpol1DLinear_attributes_counts)(
            &counts[ 0 ], ( buf_size_t )1u ), &temp_interpol );
    }

    if( status == NS(ARCH_STATUS_SUCCESS) )
    {
        status = NS(Interpol1DLinear_attributes_sizes)(
            &sizes[ 0 ], ( buf_size_t )1u ), &temp_interpol, slot_size );
    }

    if( status == NS(ARCH_STATUS_SUCCESS) )
    {
        NS(object_type_id_t) const type_id =
            NS(Interpol1DLinear_type_id)( &temp_interpol );

        interpol = ( ptr_interpol_t )( uintptr_t )NS(Object_get_begin_addr)(
            NS(Buffer_add_object)( buffer, &temp_interpol,
                sizeof( temp_interpol ), type_id, num_dataptrs, &offsets[ 0 ],
                    &sizes[ 0 ], &counts[ 0 ] ) );
    }

    return interpol;
}

NS(Interpol1DLinear)* NS(Interpol1DLinear_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol )
{
    return ( interpol != SIXTRL_NULLPTR )
        ? NS(Interpol1DLinear_add)( buffer,
            NS(Interpol1DLinear_t0)( interpol ),
            NS(Interpol1DLinear_dt)( interpol ),
            NS(Interpol1DLinear_num_values)( interpol ),
            NS(Interpol1DLinear_values_begin_addr)( interpol ) )
        : SIXTRL_NULLPTR;
}

/* ------------------------------------------------------------------------- */

SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
NS(Interpol1DLinear_preset_ext)( SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)*
    SIXTRL_RESTRICT interpol )
{
    return NS(Interpol1DLinear_preset)( interpol );
}


void NS(Interpol1DLinear_clear_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol )
{
    NS(Interpol1D_clear)( interpol );
}

/* ------------------------------------------------------------------------- */

NS(object_type_id_t) NS(Interpol1DLinear_type_id_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol )
{
    return NS(Interpol1DLinear_type_id)( interpol );
}


NS(buffer_size_t) NS(Interpol1DLinear_num_dataptrs_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol )
{
    return NS(Interpol1DLinear_num_dataptrs)( interpol );
}


NS(buffer_size_t) NS(Interpol1DLinear_num_slots_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol,
    NS(buffer_size_t) const slot_size )
{
    return NS(Interpol1DLinear_num_slots)( interpol, slot_size );
}

/* ------------------------------------------------------------------------- */

NS(interpol_1d_real_t) NS(Interpol1DLinear_t0_ext)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol )
{
    return NS(Interpol1DLinear_t0)( interpol );
}


NS(interpol_1d_real_t) NS(Interpol1DLinear_dt_ext)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol )
{
    return NS(Interpol1DLinear_dt)( interpol );
}


NS(interpol_1d_int_t) NS(Interpol1DLinear_num_values_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol )
{
    return NS(Interpol1DLinear_num_values)( interpol );
}

NS(buffer_addr_t) NS(Interpol1DLinear_values_begin_addr_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(Interpol1DLinear) *const
        SIXTRL_RESTRICT interpol )
{
    return NS(Interpol1DLinear_values_begin_addr)( interpol );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t) const*
NS(Interpol1DLinear_const_values_begin_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol )
{
    return NS(Interpol1DLinear_const_values_begin)( interpol );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(interpol_1d_real_t)*
NS(Interpol1DLinear_values_begin_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol )
{
    return NS(Interpol1DLinear_values_begin)( interpol );
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

bool NS(Interpol1DLinear_is_in_range_ext)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t )
{
    return NS(Interpol1DLinear_is_in_range)( interpol, t );
}

NS(interpol_1d_int_t) NS(Interpol1DLinear_lower_abscissa_index_ext)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t )
{
    return NS(Interpol1DLinear_lower_abscissa_index)( interpol, t );
}

NS(interpol_1d_real_t) NS(Interpol1DLinear_floor_abscissa_ext)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t )
{
    return NS(Interpol1DLinear_floor_abscissa)( interpol, t );
}

NS(interpol_1d_real_t) NS(Interpol1DLinear_ceil_abscissa_ext)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t )
{
    return NS(Interpol1DLinear_ceil_abscissa)( interpol, t );
}

NS(interpol_1d_real_t) NS(Interpol1DLinear_evaluate_ext)(
    NS(Interpol1DLinear) *const SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t )
{
    return NS(Interpol1DLinear_evaluate)( interpol, t );
}

/* ------------------------------------------------------------------------- */

void NS(Interpol1DLinear_set_t0_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const t0 )
{
    NS(Interpol1DLinear_set_t0)( interpol, t0 );
}

void NS(Interpol1DLinear_set_dt_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_real_t) const dt )
{
    NS(Interpol1DLinear_set_dt)( interpol, dt );
}

void NS(Interpol1DLinear_set_num_values_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(interpol_1d_int_t) const num_values )
{
    NS(Interpol1DLinear_set_num_values)( interpol, num_values );
}

void NS(Interpol1DLinear_set_value_begin_addr_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(Interpol1DLinear)* SIXTRL_RESTRICT interpol,
    NS(buffer_addr_t) const value_begin_addr )
{
    NS(Interpol1DLinear_set_value_begin_addr)( interpol, value_begin_addr );
}

#endif /* !defined( _GPUCODE ) */
