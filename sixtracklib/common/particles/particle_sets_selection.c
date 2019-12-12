#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_sets_selection.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

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

bool NS(ParticleSetsSelection_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs )
{

}

SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
NS(ParticleSetsSelection_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer )
{

}

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
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* selected_pset_num_particles )
{

}

SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetsSelection)*
NS(ParticleSetsSelection_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(ParticleSetsSelection)
        *const SIXTRL_RESTRICT sel )
{

}
