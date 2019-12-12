#include "sixtracklib/common/buffer/buffer_toc.h"

#if defined( __cplusplus ) && !defined( _GPUCODE )

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(BufferToc)* NS(BufferToc_create)( void )
{
    return new st::BufferToc;
}

::NS(BufferToc)* NS(BufferToc_new)(
    const ::NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return new st::BufferToc( buffer );
}

void NS(BufferToc_delete)( ::NS(BufferToc)* SIXTRL_RESTRICT buffer_toc )
{
    delete buffer_toc;
}

/* ------------------------------------------------------------------------- */

bool NS(BufferToc_has_types)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT
{
    return ( ( buffer_toc != nullptr ) && ( buffer_toc->has_types() ) );
}

::NS(buffer_size_t) NS(BufferToc_num_types)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->num_types() : st::buffer_size_t{ 0 };
}

::NS(object_type_id_t) const* NS(BufferToc_types_begin)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr ) ? buffer_toc->types_begin() : nullptr;
}

::NS(object_type_id_t) const* NS(BufferToc_types_end)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr ) ? buffer_toc->types_end() : nullptr;
}

/* ------------------------------------------------------------------------- */

::NS(buffer_size_t) NS(BufferToc_total_num_elements)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->total_num_elements() : ::NS(buffer_size_t){ 0 };
}

bool NS(BufferToc_has_type_elements)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( ( buffer_toc != nullptr ) &&
             ( buffer_toc->has_type_elements( type_id ) ) );
}

::NS(buffer_size_t) NS(BufferToc_num_type_elements)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->num_type_elements( type_id ) : st::buffer_size_t{ 0 };
}

::NS(buffer_size_t) const* NS(BufferToc_type_elements_indices_begin)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->type_elements_indices_begin( type_id ) : nullptr;
}

::NS(buffer_size_t) const* NS(BufferToc_type_elements_indices_end)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->type_elements_indices_end( type_id ) : nullptr;
}


::NS(buffer_size_t) NS(BufferToc_type_element_index)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id, NS(buffer_size_t) const id )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->type_element_index( type_id, id )
        : st::BufferToc::ILLEGAL_ELEMENT_ID;
}

::NS(buffer_size_t) NS(BufferToc_type_element_index_no_check)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id, NS(buffer_size_t) const id )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->type_element_index_no_check( type_id, id )
        : st::BufferToc::ILLEGAL_ELEMENT_ID;
}

/* ------------------------------------------------------------------------- */

::NS(arch_status_t) NS(BufferToc_reset)(
    ::NS(BufferToc)* SIXTRL_RESTRICT buffer_toc,
    const ::NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->reset( buffer ) : st::ARCH_STATUS_GENERAL_FAILURE;
}

void NS(BufferToc_clear)( void )
{
    if( buffer_toc != nullptr ) buffer_toc->clear();
}

/* ----------------------------------------------------------------- */

bool NS(BufferToc_are_equal)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT lhs,
    const ::NS(BufferToc) *const SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT
{
    if( ( lhs != nullptr ) && ( rhs != nullptr ) )
    {
        return ( *lhs == *rhs );
    }

    return false;
}

bool NS(BufferToc_are_not_equal)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT lhs,
    const ::NS(BufferToc) *const SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT
{
    if( ( lhs != nullptr ) && ( rhs != nullptr ) )
    {
        return ( *lhs != *rhs );
    }

    return false;
}

/* ========================================================================= */

::NS(OutputOffsetBufferToc)* NS(OutputOffsetBufferToc_create)( void )
{
    return new st::OutputOffsetBufferToc;
}

::NS(OutputOffsetBufferToc)* NS(OutputOffsetBufferToc_new)(
    const ::NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return new st::OutputOffsetBufferToc( buffer );
}

void NS(OutputOffsetBufferToc_delete)(
    ::NS(OutputOffsetBufferToc)* SIXTRL_RESTRICT buffer_toc )
{
    delete buffer_toc;
}

/* ------------------------------------------------------------------------- */

bool NS(OutputOffsetBufferToc_has_output_offset)(
    const ::NS(OutputOffsetBufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) const SIXTRL_NOEXCEPT
{
    return ( ( buffer_toc != nullptr ) &&
             ( buffer_toc->has_output_offset( type_id ) ) );
}

::NS(arch_status_t) NS(OutputOffsetBufferToc_enable_output_offset)(
    ::NS(OutputOffsetBufferToc)* SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->enable_output_offset( type_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(OutputOffsetBufferToc_disable_output_offset)(
    ::NS(OutputOffsetBufferToc)* SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->disable_output_offset( type_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(buffer_size_t) NS(OutputOffsetBufferToc_num_output_offsets)(
    const ::NS(OutputOffsetBufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->num_output_offsets( type_id )
        : ::NS(buffer_size_t){ 0 };
}

::NS(buffer_size_t) const* NS(OutputOffsetBufferToc_output_offsets_begin)(
    const ::NS(OutputOffsetBufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->output_offsets_begin( type_id ) : nullptr;
}

::NS(buffer_size_t) const* NS(OutputOffsetBufferToc_output_offsets_end)(
    const ::NS(OutputOffsetBufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->output_offsets_end( type_id ) : nullptr;
}

::NS(buffer_size_t) NS(OutputOffsetBufferToc_output_offset)(
    const ::NS(OutputOffsetBufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id,
    ::NS(buffer_size_t) const index ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->output_offset( type_id, index )
        : st::OutputOffsetBufferToc::ILLEGAL_OUTPUT_OFFSET;
}

::NS(buffer_size_t)
NS(OutputOffsetBufferToc_output_offset_by_buffer_index)(
    const ::NS(OutputOffsetBufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id,
    ::NS(buffer_size_t) const buffer_index ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->output_offset_by_buffer_index( type_id, buffer_index )
        : st::OutputOffsetBufferToc::ILLEGAL_OUTPUT_OFFSET;
}

::NS(arch_status_t) NS(OutputOffsetBufferToc_set_output_offset)(
    ::NS(OutputOffsetBufferToc)* SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id,
    ::NS(buffer_size_t) const index,
    ::NS(buffer_size_t) const output_offset ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->set_output_offset( type_id, index, output_offset )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(OutputOffsetBufferToc_set_output_offset_by_buffer_index)(
    ::NS(OutputOffsetBufferToc)* SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id,
    ::NS(buffer_size_t) const buffer_index,
    ::NS(buffer_size_t) const output_offset ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->set_output_offset_by_buffer_index(
            type_id, buffer_index, output_offset )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

bool NS(OutputOffsetBufferToc_are_equal)(
    const NS(OutputOffsetBufferToc) *const SIXTRL_RESTRICT lhs,
    const NS(OutputOffsetBufferToc) *const SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT
{
    if( ( lhs != nullptr ) && ( rhs != nullptr ) )
    {
        return ( *lhs == *rhs );
    }

    return false;
}

bool NS(OutputOffsetBufferToc_are_not_equal)(
    const NS(OutputOffsetBufferToc) *const SIXTRL_RESTRICT lhs,
    const NS(OutputOffsetBufferToc) *const SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT
{
    if( ( lhs != nullptr ) && ( rhs != nullptr ) )
    {
        return ( *lhs != *rhs );
    }

    return false;
}

/* ========================================================================= */

::NS(ParticleSetsBufferToc)* NS(ParticleSetsBufferToc_create)( void )
{
    return new st::ParticleSetsBufferToc;
}

::NS(ParticleSetsBufferToc)* NS(ParticleSetsBufferToc_new)(
    const ::NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return new st::ParticleSetsBufferToc( buffer );
}

void NS(ParticleSetsBufferToc_delete)(
    ::NS(ParticleSetsBufferToc)* SIXTRL_RESTRICT buffer_toc )
{
    delete buffer_toc;
}

/* ------------------------------------------------------------------------- */

::NS(buffer_size_t) NS(ParticleSetsBufferToc_num_particle_sets)(
    const NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc ) SIXTRL_NOEXCEPT
{
    return ( toc != nullptr )
        ? toc->num_particle_sets() : ::NS(buffer_size_t){ 0 };
}

::NS(buffer_size_t) const* NS(ParticleSetsBufferToc_num_particles_in_sets_begin(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc ) SIXTRL_NOEXCEPT
{
    return ( toc != nullptr ) ? toc->num_particle_sets_begin() : nullptr;
}

::NS(buffer_size_t) const* NS(ParticleSetsBufferToc_num_particles_in_sets_end(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc ) SIXTRL_NOEXCEPT
{
    return ( toc != nullptr ) ? toc->num_patricle_sets_end() : nullptr;
}

::NS(buffer_size_t) const* NS(ParticleSetsBufferToc_particle_set_begin_index_begin(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc ) SIXTRL_NOEXCEPT
{
    return ( toc != nullptr ) ? toc->particle_set_begin_index_begin() : nullptr;
}

::NS(buffer_size_t) const* NS(ParticleSetsBufferToc_particle_set_begin_index_end(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc ) SIXTRL_NOEXCEPT
{
    return ( toc != nullptr ) ? toc->particle_set_begin_index_end() : nullptr;
}

::NS(buffer_size_t) const* NS(ParticleSetsBufferToc_particle_set_end_index_begin(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc ) SIXTRL_NOEXCEPT
{
    return ( toc != nullptr ) ? toc->particle_set_end_index_begin() : nullptr;
}

::NS(buffer_size_t) const* NS(ParticleSetsBufferToc_particle_set_end_index_end(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc ) SIXTRL_NOEXCEPT
{
    return ( toc != nullptr ) ? toc->particle_set_end_index_end() : nullptr;
}

::NS(buffer_size_t) NS(ParticleSetsBufferToc_particle_set_begin_index)(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc,
    ::NS(buffer_size_t) const pset_index ) SIXTRL_NOEXCEPT
{
    return ( toc != nullptr )
        ? toc->particle_set_begin_index( pset_index )
        : ::NS(buffer_size_t){ 0 };
}

::NS(buffer_size_t) NS(ParticleSetsBufferToc_particle_set_end_index)(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc,
    ::NS(buffer_size_t) const pset_index ) SIXTRL_NOEXCEPT
{
    return ( toc != nullptr )
        ? toc->particle_set_end_index( pset_index ) : ::NS(buffer_size_t){ 0 };
}

::NS(buffer_size_t) NS(ParticleSetsBufferToc_num_particles)(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc,
    ::NS(buffer_size_t) const pset_index ) SIXTRL_NOEXCEPT
{
    return ( toc != nullptr )
        ? toc->num_particles( pset_index ) : ::NS(buffer_size_t){ 0 };
}

::NS(buffer_size_t) NS(ParticleSetsBufferToc_total_num_particles)(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc ) SIXTRL_NOEXCEPT
{
    return ( toc != nullptr )
        ? toc->total_num_particles() : ::NS(buffer_size_t){ 0 };
}

/* ------------------------------------------------------------------------- */

::NS(ParticleSetState) const* NS(ParticleSetsBufferToc_particle_set_state)(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc,
    ::NS(buffer_size_t) const pset_index ) SIXTRL_NOEXCEPT
{
    return ( toc != nullptr ) ? toc->particle_set_state( pset_index ) : nullptr;
}

::NS(ParticleSetState) const*
NS(ParticleSetsBufferToc_global_particle_set_state)(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT toc )
{
    return ( toc != nullptr ) ? &toc->global_particle_set_state() : nullptr;
}

bool NS(ParticleSetsBufferToc_are_equal)(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT lhs,
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT
{
    if( ( lhs != nullptr ) && ( rhs != nullptr ) )
    {
        return ( *lhs == *rhs );
    }

    return false;
}

bool NS(ParticleSetsBufferToc_are_not_equal)(
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT lhs,
    const ::NS(ParticleSetsBufferToc) *const SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT
{
    if( ( lhs != nullptr ) && ( rhs != nullptr ) )
    {
        return ( *lhs != *rhs );
    }

    return false;
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
