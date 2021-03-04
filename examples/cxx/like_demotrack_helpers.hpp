#ifndef SIXTRACKLIB_EXAMPLES_CXX_LIKE_DEMOTRACK_HELPERS_HPP__
#define SIXTRACKLIB_EXAMPLES_CXX_LIKE_DEMOTRACK_HELPERS_HPP__

#include "sixtracklib/sixtracklib.hpp"

namespace SIXTRL_CXX_NAMESPACE {
namespace examples {

SIXTRL_CXX_NAMESPACE::status_type Prepare_particle_data_cobj(
    SIXTRL_CXX_NAMESPACE::CBufferView const& in_pbuffer,
    SIXTRL_CXX_NAMESPACE::CBufferView& out_pbuffer,
    SIXTRL_CXX_NAMESPACE::particles_num_type const num_particles,
    SIXTRL_CXX_NAMESPACE::cobj_size_type* ptr_out_pset_idx = nullptr )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using npart_type = st::particles_num_type;
    st::status_type status = st::STATUS_GENERAL_FAILURE;

    ::NS(Particles) const* in_pset =
        ::NS(Particles_const_from_cbuffer)( in_pbuffer.as_c_api(), 0 );

    npart_type const in_nparticles = ::NS(Particles_num_particles)( in_pset );

    if( ( num_particles > npart_type{ 0 } ) &&
        ( in_pset != nullptr ) && ( in_nparticles > npart_type{ 0 } ) )
    {
        st::cobj_size_type const out_pset_idx = out_pbuffer.num_objects();
        ::NS(Particles)* out_pset = ::NS(Particles_cbuffer_new)(
            out_pbuffer.as_c_api(), num_particles );

        if( ( out_pset != nullptr ) &&
            ( ::NS(Particles_num_particles)( out_pset ) == num_particles ) )
        {
            status = st::STATUS_SUCCESS;

            for( npart_type ii = npart_type{ 0 } ; ii < num_particles ; ++ii )
            {
                npart_type const jj = ii % in_nparticles;
                status |= ::NS(Particles_copy_single)( out_pset, ii, in_pset, jj );
            }

            if( ( status == st::STATUS_SUCCESS ) &&
                ( ptr_out_pset_idx != nullptr ) )
            {
                *ptr_out_pset_idx = out_pset_idx;
            }
        }
    }

    return status;
}

SIXTRL_CXX_NAMESPACE::status_type Prepare_lattice_data_cobj(
    SIXTRL_CXX_NAMESPACE::CBufferView& lattice_buffer,
    SIXTRL_CXX_NAMESPACE::size_type* ptr_eot_marker_index )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return ::NS(EndTracking_terminate_lattice_with_eot_marker_cbuffer)(
        lattice_buffer.as_c_api(), st::size_type{ 0 },
            st::particle_index_type{ 0 }, ptr_eot_marker_index );
}


} /* end: namespace examples */
} /* end: namespace SIXTRL_CXX_NAMESPACE */

#endif /* SIXTRACKLIB_EXAMPLES_CXX_LIKE_DEMOTRACK_HELPERS_HPP__ */
