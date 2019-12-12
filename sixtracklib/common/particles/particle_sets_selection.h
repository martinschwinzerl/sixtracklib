#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SETS_SELECTION_C99_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SETS_SELECTION_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
    #if !defined( _GPUCODE )
        #include "sixtracklib/commmon/buffer.h"
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

typedef struct NS(ParticleSetsSelection)
{
    NS(buffer_size_t)   total_num_particles                 SIXTRL_ALIGN( 8 );
    NS(buffer_size_t)   total_num_particle_sets             SIXTRL_ALIGN( 8 );
    NS(buffer_size_t)   num_particles_in_sets               SIXTRL_ALIGN( 8 );
    NS(buffer_size_t)   num_active_particles_in_sets        SIXTRL_ALIGN( 8 );
    NS(buffer_size_t)   num_particle_sets                   SIXTRL_ALIGN( 8 );
    NS(buffer_addr_t)   selected_pset_indices_addr          SIXTRL_ALIGN( 8 );
    NS(buffer_addr_t)   selected_pset_particle_index_addr   SIXTRL_ALIGN( 8 );
    NS(buffer_addr_t)   selected_pset_num_particles_addr    SIXTRL_ALIGN( 8 );
}
NS(ParticleSetsSelection};

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
NS(ParticleSetsSelection_preset)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(ParticleSetsSelection)* SIXTRL_RESTRICT selection );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetsSelection_clear)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(objects_type_id_t) NS(ParticleSetsSelection_type_id)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* const
        SIXTRL_RESTRICT sel );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetsSelection_num_dataptrs)( const SIXTRL_BUFFER_DATAPTR_DEC
    NS(ParticleSetsSelection)* const SIXTRL_RESTRICT sel );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetsSelection_num_slots)( const SIXTRL_BUFFER_DATAPTR_DEC
    NS(ParticleSetsSelection)* const SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const slot_size );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetsSelection_total_num_particles)( const SIXTRL_BUFFER_DATAPTR_DEC
    NS(ParticleSetsSelection)* const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetsSelection_total_num_particle_sets)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetsSelection_num_particles_in_sets)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetsSelection_num_particle_sets)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(buffer_addr_t)
NS(ParticleSetsSelection_selected_pset_indices_addr)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t) const*
NS(ParticleSetsSelection_const_selected_pset_indices)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)*
NS(ParticleSetsSelection_selected_pset_indices)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetsSelection_selected_pset_indices_value)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const ii ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(buffer_addr_t)
NS(ParticleSetsSelection_selected_pset_particle_index_addr)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t) const*
NS(ParticleSetsSelection_const_selected_pset_particle_index)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)*
NS(ParticleSetsSelection_selected_pset_particle_index)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetsSelection_selected_pset_particle_index_value)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const ii ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(buffer_addr_t)
NS(ParticleSetsSelection_selected_pset_num_particles_addr)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t) const*
NS(ParticleSetsSelection_const_selected_pset_num_particles)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)*
NS(ParticleSetsSelection_const_selected_pset_num_particles)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetsSelection_selected_pset_num_particles_value)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const ii ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetsSelection_set_total_num_particles)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const total_num_particles ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void
NS(ParticleSetsSelection_set_total_num_particle_sets)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const total_num_particle_sets ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void
NS(ParticleSetsSelection_set_num_particles_in_sets)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const num_particles_in_sets ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetsSelection_num_particle_sets)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const num_particle_sets ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN void
NS(ParticleSetsSelection_set_selected_pset_indices_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_addr_t) const selected_pset_indices_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void
NS(ParticleSetsSelection_set_selected_pset_indices_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const ii,
    NS(buffer_size_t) const selected_pset_indices ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN void
NS(ParticleSetsSelection_set_selected_pset_particle_index_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_addr_t) const sel_pset_particle_index_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void
NS(ParticleSetsSelection_set_selected_pset_particle_index_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const ii,
    NS(buffer_size_t) const selected_pset_particle_index ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN void
NS(ParticleSetsSelection_set_selected_pset_num_particles_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_addr_t) const selected_pset_num_particles_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void
NS(ParticleSetsSelection_set_selected_pset_num_particles_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const ii,
    NS(buffer_size_t) const sel_pset_num_particles_value ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN
SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection) const*
NS(ParticleSetsSelection_const_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
NS(ParticleSetsSelection_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection) const*
NS(ParticleSetsSelection_const_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
NS(ParticleSetsSelection_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSetsSelection_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetsSelection) *const
        SIXTRL_RESTRICT sel, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSetsSelection_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetsSelection) *const
        SIXTRL_RESTRICT sel, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSetsSelection_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetsSelection) *const
        SIXTRL_RESTRICT sel );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ParticleSetsSelection_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs );

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
NS(ParticleSetsSelection_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const total_num_particle_sets );

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
NS(ParticleSetsSelection_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const total_num_particles,
    NS(buffer_size_t) const total_num_particle_sets,
    NS(buffer_size_t) const num_particles_in_sets,
    NS(buffer_size_t) const num_active_particles_in_sets,
    NS(buffer_size_t) const num_particle_sets,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* selected_pset_indices,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* selected_pset_particle_index,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* selected_pset_num_particles );

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
NS(ParticleSetsSelection_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(ParticleSetsSelection)
        *const SIXTRL_RESTRICT sel );

#endif /* !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSetsSelection_copy)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetsSelection)
        *const SIXTRL_RESTRICT src );

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* */
/* ************************************************************************* */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
NS(ParticleSetsSelection_preset)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(ParticleSetsSelection)* SIXTRL_RESTRICT selection )
{
    if( selection != SIXTRL_NULLPTR )
    {
        NS(ParticleSetsSelection_clear)( selection );
    }

    return selection;
}

SIXTRL_INLINE void NS(ParticleSetsSelection_clear)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel )
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    sel->total_num_particles                = ( NS(buffer_size_t) )0u;
    sel->total_num_particle_sets            = ( NS(buffer_size_t) )0u;
    sel->num_particles_in_sets              = ( NS(buffer_size_t) )0u;
    sel->num_active_particles_in_sets       = ( NS(buffer_size_t) )0u;
    sel->num_particle_sets                  = ( NS(buffer_size_t) )0u;
    sel->selected_pset_indices_addr         = ( NS(buffer_addr_t) )0u;
    sel->selected_pset_particle_index_addr  = ( NS(buffer_addr_t) )0u;
    sel->selected_pset_num_particles_addr   = ( NS(buffer_addr_t) )0u;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(objects_type_id_t) NS(ParticleSetsSelection_type_id)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* const
        SIXTRL_RESTRICT sel )
{
    ( void )sel;
    return NS(OBJECT_TYPE_PARTICLE_SETS_SELECTION);
}

SIXTRL_INLINE NS(buffer_size_t)
NS(ParticleSetsSelection_num_dataptrs)( const SIXTRL_BUFFER_DATAPTR_DEC
    NS(ParticleSetsSelection)* const SIXTRL_RESTRICT sel )
{
    ( void )sel;
    return ( NS(buffer_size_t) )3u;
}

SIXTRL_INLINE NS(buffer_size_t)
NS(ParticleSetsSelection_num_slots)( const SIXTRL_BUFFER_DATAPTR_DEC
    NS(ParticleSetsSelection)* const SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const slot_size )
{
    NS(buffer_size_t) num_slots = ( NS(buffer_size_t) )0u;

    NS(buffer_size_t) required_size =
        NS(ManagedBuffer_get_slot_based_length)(
            sizeof( NS(ParticleSetsSelection) ), slot_size );

    SIXTRL_ASSERT( slot_size > ( NS(buffer_size_t) )0u );

    if( sel != SIXTRL_NULLPTR )
    {
        required_size += NS(ManagedBuffer_get_slot_based_length)(
            sizeof( NS(buffer_size_t) ) * sel->total_num_particle_sets, slot_size );

        required_size += NS(ManagedBuffer_get_slot_based_length)(
            sizeof( NS(buffer_size_t) ) * sel->total_num_particle_sets, slot_size );

        required_size += NS(ManagedBuffer_get_slot_based_length)(
            sizeof( NS(buffer_size_t) ) * sel->total_num_particle_sets, slot_size );
    }

    num_slots = required_size / slot_size;

    if( ( num_slots * slot_size ) < required_size ) ++num_slots;
    SIXTRL_ASSERT( ( num_slots * slot_size ) >= required_size );

    return num_slots;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(buffer_size_t) NS(ParticleSetsSelection_total_num_particles)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* const
        SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return sel->total_num_particles;
}

SIXTRL_INLINE NS(buffer_size_t)
NS(ParticleSetsSelection_total_num_particle_sets)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return sel->total_num_particle_sets;
}

SIXTRL_INLINE NS(buffer_size_t)
NS(ParticleSetsSelection_num_particles_in_sets)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return sel->num_particles_in_sets;
}

SIXTRL_INLINE NS(buffer_size_t) NS(ParticleSetsSelection_num_particle_sets)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return sel->num_particle_sets;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(buffer_addr_t)
NS(ParticleSetsSelection_selected_pset_indices_addr)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return sel->selected_pset_indices_addr;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t) const*
NS(ParticleSetsSelection_const_selected_pset_indices)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t) const* )( uintptr_t
        )sel->selected_pset_indices_addr;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)*
NS(ParticleSetsSelection_selected_pset_indices)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)* )( uintptr_t
        )sel->selected_pset_indices_addr;
}

SIXTRL_INLINE NS(buffer_size_t)
NS(ParticleSetsSelection_selected_pset_indices_value)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const ii ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t) const* ptr_t;
    ptr_t ptr = NS(ParticleSetsSelection_const_selected_pset_indices)( sel );

    SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( sel->total_num_particle_sets > ii );
    return ptr[ ii ];
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(buffer_addr_t)
NS(ParticleSetsSelection_selected_pset_particle_index_addr)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return sel->selected_pset_particle_index_addr;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t) const*
NS(ParticleSetsSelection_const_selected_pset_particle_index)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t) const* )( uintptr_t
        )sel->selected_pset_particle_index_addr;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)*
NS(ParticleSetsSelection_selected_pset_particle_index)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)* )( uintptr_t
        )sel->selected_pset_particle_index_addr;
}

SIXTRL_INLINE NS(buffer_size_t)
NS(ParticleSetsSelection_selected_pset_particle_index_value)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel, NS(buffer_size_t) const ii ) SIXTRL_NOEXCEPT
{
    typedef ( SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t) const* ) ptr_t;
    ptr_t ptr =
        NS(ParticleSetsSelection_const_selected_pset_particle_index)( sel );

    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( sel->total_num_particle_sets > ii );
    SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );

    return ptr[ ii ];
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(buffer_addr_t)
NS(ParticleSetsSelection_selected_pset_num_particles_addr)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return sel->selected_pset_num_particles_addr;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t) const*
NS(ParticleSetsSelection_const_selected_pset_num_particles)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t) const* )( uintptr_t
        )sel->selected_pset_num_particles_addr;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)*
NS(ParticleSetsSelection_const_selected_pset_num_particles)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)* )( uintptr_t
        )sel->selected_pset_num_particles_addr;
}

SIXTRL_INLINE NS(buffer_size_t)
NS(ParticleSetsSelection_selected_pset_num_particles_value)(
    const SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        const SIXTRL_RESTRICT sel, NS(buffer_size_t) const ii ) SIXTRL_NOEXCEPT
{
    typedef ( SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t) const* ) ptr_t;
    ptr_t ptr = NS(ParticleSetsSelection_const_selected_pset_num_particles)(
        sel );

    SIXTRL_ASSERT( sel != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( sel->total_num_particle_sets > ii );
    SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );

    return ptr[ ii ];
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(ParticleSetsSelection_set_total_num_particles)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const total_num_particles ) SIXTRL_NOEXCEPT
{
    if( sel != SIXTRL_NULLPTR )
        sel->total_num_particles = total_num_particles;
}

SIXTRL_INLINE void NS(ParticleSetsSelection_set_total_num_particle_sets)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const total_num_particle_sets ) SIXTRL_NOEXCEPT
{
    if( sel != SIXTRL_NULLPTR )
        sel->total_num_particle_sets = total_num_particle_sets;
}

SIXTRL_INLINE void NS(ParticleSetsSelection_set_num_particles_in_sets)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const num_particles_in_sets ) SIXTRL_NOEXCEPT
{
    if( sel != SIXTRL_NULLPTR )
        sel->num_particles_in_sets = num_particles_in_sets;
}

SIXTRL_INLINE void NS(ParticleSetsSelection_num_particle_sets)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const num_particle_sets ) SIXTRL_NOEXCEPT
{
    if( sel != SIXTRL_NULLPTR ) sel->num_particle_sets = num_particle_sets;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE void NS(ParticleSetsSelection_set_selected_pset_indices_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_addr_t) const selected_pset_indices_addr ) SIXTRL_NOEXCEPT
{
    if( sel != SIXTRL_NULLPTR )
        sel->selected_pset_indices_addr = selected_pset_indices_addr;
}

SIXTRL_INLINE void NS(ParticleSetsSelection_set_selected_pset_indices_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const ii,
    NS(buffer_size_t) const selected_pset_indices ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)* ptr_t;
    ptr_t ptr = NS(ParticleSetsSelection_selected_pset_indices)( sel );

    if( ( ptr != SIXTRL_NULLPTR ) &&
        ( ii < NS(ParticleSetsSelection_total_num_particle_sets)( sel ) ) )
    {
        ptr[ ii ] = selected_pset_indices;
    }
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE void
NS(ParticleSetsSelection_set_selected_pset_particle_index_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_addr_t) const sel_pset_particle_index_addr ) SIXTRL_NOEXCEPT
{
    if( sel != SIXTRL_NULLPTR )
        sel->sel_pset_particle_index_addr = sel_pset_particle_index_addr;
}

SIXTRL_INLINE void
NS(ParticleSetsSelection_set_selected_pset_particle_index_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const ii,
    NS(buffer_size_t) const selected_pset_particle_index ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)* ptr_t;
    ptr_t ptr = NS(ParticleSetsSelection_selected_pset_particle_index)( sel );

    if( ( ptr != SIXTRL_NULLPTR ) &&
        ( ii < NS(ParticleSetsSelection_total_num_particle_sets)( sel ) ) )
    {
        ptr[ ii ] = selected_pset_particle_index;
    }
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE void
NS(ParticleSetsSelection_set_selected_pset_num_particles_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_addr_t) const selected_pset_num_particles_addr ) SIXTRL_NOEXCEPT
{
    if( sel != SIXTRL_NULLPTR ) sel->selected_pset_num_particles_addr =
        selected_pset_num_particles_addr;
}

SIXTRL_INLINE void
NS(ParticleSetsSelection_set_selected_pset_num_particles_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)* SIXTRL_RESTRICT sel,
    NS(buffer_size_t) const ii,
    NS(buffer_size_t) const sel_pset_num_particles_value ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(buffer_size_t)* ptr_t;
    ptr_t ptr = NS(ParticleSetsSelection_selected_pset_num_particles)( sel );

    if( ( ptr != SIXTRL_NULLPTR ) &&
        ( ii < NS(ParticleSetsSelection_total_num_particle_sets)( sel ) ) )
    {
        ptr[ ii ] = sel_pset_num_particles_value;
    }
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection) const*
NS(ParticleSetsSelection_const_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT obj )
{
    return ( ( NS(Object_get_type_id)( obj ) ==
                    NS(OBJECT_TYPE_PARTICLE_SETS_SELECTION) ) &&
             ( NS(Object_get_size)( obj ) >=
                    sizeof( NS(ParticleSetsSelection) ) ) )
        ? ( SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection) const* )(
            uintptr_t )NS(Object_get_begin_addr)( obj )
        : SIXTRL_NULLPTR;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
NS(ParticleSetsSelection_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT obj )
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
        )NS(ParticleSetsSelection_const_from_obj_index)( obj );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection) const*
NS(ParticleSetsSelection_const_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(ParticleSetsSelection_const_from_obj_index)(
        NS(ManagedBuffer_get_const_object)( buffer_begin, index, slot_size ) );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
NS(ParticleSetsSelection_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(ParticleSetsSelection_from_obj_index)(
        NS(ManagedBuffer_get_object)( buffer_begin, index, slot_size ) );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSetsSelection_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetsSelection) *const
        SIXTRL_RESTRICT sel, NS(buffer_size_t) const slot_size )
{
    typedef NS(buffer_size_t) _size_t;

    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
    SIXTRL_STATIC_VAR _size_t const ZERO = ( _size_t )0u;

    _size_t const num_dataptrs =
        NS(ParticleSetsSelection_num_dataptrs)( sel );

    if( ( offsets_begin != SIXTRL_NULLPTR ) && ( slot_size > ZERO ) &&
        ( max_num_offsets >= num_dataptrs ) )
    {
        SIXTRL_ASSERT( num_dataptrs == ( _size_t )3u );

        offsets_begin[ 0 ] = ( NS(buffer_size_t) )offsetof(
            NS(ParticleSetsSelection), selected_pset_indices_addr );

        offsets_begin[ 1 ] = ( NS(buffer_size_t) )offsetof(
            NS(ParticleSetsSelection), selected_pset_particle_index_addr );

        offsets_begin[ 2 ] = ( NS(buffer_size_t) )offsetof(
            NS(ParticleSetsSelection), selected_pset_num_particles_addr );

        if( max_num_offsets > num_dataptrs )
        {
            SIXTRACKLIB_SET_VALUES( _size_t, &offsets_begin[ num_dataptrs ],
                ( max_num_offsts - num_dataptrs ), ZERO );
        }

        status = SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSetsSelection_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetsSelection) *const
        SIXTRL_RESTRICT sel, NS(buffer_size_t) const slot_size )
{
    typedef NS(buffer_size_t) _size_t;

    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
    SIXTRL_STATIC_VAR _size_t const ZERO = ( _size_t )0u;

    _size_t const num_dataptrs =
        NS(ParticleSetsSelection_num_dataptrs)( sel );

    if( ( offsets_begin != SIXTRL_NULLPTR ) && ( slot_size > ZERO ) &&
        ( sel != SIXTRL_NULLPTR ) && ( max_num_offsets >= num_dataptrs ) )
    {
        SIXTRL_ASSERT( num_dataptrs == ( _size_t )3u );

        sizes_begin[ 0 ] = sizeof( _size_t );
        sizes_begin[ 1 ] = sizeof( _size_t );
        sizes_begin[ 2 ] = sizeof( _size_t );

        if( max_num_sizes > num_dataptrs )
        {
            SIXTRACKLIB_SET_VALUES( _size_t, &sizes_begin[ num_dataptrs ],
                ( max_num_sizes - num_dataptrs ), ZERO );
        }

        status = SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSetsSelection_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetsSelection) *const
        SIXTRL_RESTRICT sel )
{
    typedef NS(buffer_size_t) _size_t;

    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
    SIXTRL_STATIC_VAR _size_t const ZERO = ( _size_t )0u;

    _size_t const num_dataptrs =
        NS(ParticleSetsSelection_num_dataptrs)( sel );

    if( ( counts_begin != SIXTRL_NULLPTR ) && ( sel != SIXTRL_NULLPTR ) &&
        ( max_num_counts >= num_dataptrs ) )
    {
        _size_t const num_psets =
            NS(ParticleSetsSelection_total_num_particle_sets)( sel );

        SIXTRL_ASSERT( num_dataptrs == ( _size_t )3u );

        counts_begin[ 0 ] = num_psets;
        counts_begin[ 1 ] = num_psets;
        counts_begin[ 2 ] = num_psets;

        if( max_num_sizes > num_dataptrs )
        {
            SIXTRACKLIB_SET_VALUES( _size_t, &counts_begin[ num_dataptrs ],
                ( max_num_counts - num_dataptrs ), ZERO );
        }

        status = SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_SELECTION_C99_H__ */
