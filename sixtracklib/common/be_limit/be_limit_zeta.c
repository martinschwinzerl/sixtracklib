#include "sixtracklib/common/be_limit/be_limit_zeta.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/particles/definitions.h"
#include "sixtracklib/common/buffer.h"

SIXTRL_BE_ARGPTR_DEC NS(LimitZeta) const* NS(LimitZeta_const_from_buffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index )
{
    return NS(LimitZeta_const_from_obj_index)(
        NS(Buffer_get_const_object)( buffer, index ) );
}

SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* NS(LimitZeta_from_buffer)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const idx )
{
    return NS(LimitZeta_from_obj_index)( NS(Buffer_get_object)( buffer, idx ) );
}

NS(arch_status_t) NS(LimitZeta_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit,
    NS(buffer_size_t) const slot_size )
{
    SIXTRL_ASSERT( NS(LimitZeta_num_dataptrs)( limit ) ==
        ( NS(buffer_size_t) )0u );

    ( void )limit;
    return NS(Buffer_set_attr_arrays_for_trivial_object)(
        offsets_begin, max_num_offsets, slot_size );
}

NS(arch_status_t) NS(LimitZeta_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit,
    NS(buffer_size_t) const slot_size )
{
    SIXTRL_ASSERT( NS(LimitZeta_num_dataptrs)( limit ) ==
        ( NS(buffer_size_t) )0u );

    ( void )limit;
    return NS(Buffer_set_attr_arrays_for_trivial_object)(
        sizes_begin, max_num_sizes, slot_size );
}

NS(arch_status_t) NS(LimitZeta_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit )
{
    SIXTRL_ASSERT( NS(LimitZeta_num_dataptrs)( limit ) ==
        ( NS(buffer_size_t) )0u );

    ( void )limit;
    return NS(Buffer_set_attr_arrays_for_trivial_object)(
        counts_begin, max_num_counts, SIXTRL_BUFFER_DEFAULT_SLOT_SIZE );
}

/* ------------------------------------------------------------------------- */

bool NS(LimitZeta_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs )
{
    NS(LimitZeta) limit;
    NS(LimitZeta_preset)( &limit );

    SIXTRL_ASSERT( ( NS(buffer_size_t) )0u ==
        NS(LimitZeta_num_dataptrs)( &limit ) );
    ( void )ptr_requ_dataptrs;

    return NS(Buffer_can_add_trivial_object)( buffer, sizeof( limit ),
        ptr_requ_objects, ptr_requ_slots );
}

SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* NS(LimitZeta_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer )
{
    NS(LimitZeta) limit;
    NS(LimitZeta_preset)( &limit );

    SIXTRL_ASSERT( ( NS(buffer_size_t) )0u ==
        NS(LimitZeta_num_dataptrs)( &limit ) );

    return ( SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* )( uintptr_t
        )NS(Object_get_begin_addr)( NS(Buffer_add_trivial_object)( buffer,
            &limit, sizeof( limit ), NS(LimitZeta_type_id)( &limit ) ) );
}

SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* NS(LimitZeta_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(particle_real_t) const min_zeta, NS(particle_real_t) const max_zeta )
{
    NS(LimitZeta) limit;
    NS(LimitZeta_preset)( &limit );
    NS(LimitZeta_set_min_zeta)( &limit, min_zeta );
    NS(LimitZeta_set_max_zeta)( &limit, max_zeta );

    SIXTRL_ASSERT( ( NS(buffer_size_t) )0u ==
        NS(LimitZeta_num_dataptrs)( &limit ) );

    return ( SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* )( uintptr_t
        )NS(Object_get_begin_addr)( NS(Buffer_add_trivial_object)( buffer,
            &limit, sizeof( limit ), NS(LimitZeta_type_id)( &limit ) ) );
}

SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* NS(LimitZeta_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit )
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* )( uintptr_t
        )NS(Object_get_begin_addr)( NS(Buffer_add_trivial_object)( buffer,
            limit, sizeof( NS(LimitZeta) ), NS(LimitZeta_type_id)( limit ) ) );
}
