#include "python/sixtracklib/_wrapper/common_particles.h"

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/particles/definitions.h"
#include "sixtracklib/common/particles/particle.h"
#include "sixtracklib/common/particles/particles.h"
#include "sixtracklib/common/particles/particles_addr.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "python/sixtracklib/_wrapper/cxx11_optional.h"
#include "python/sixtracklib/_wrapper/buffer_protocol.h"
#include "python/sixtracklib/_wrapper/tl/optional.hpp"
#include "python/sixtracklib/_wrapper/init_helper.h"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    namespace
    {
        namespace py   = pybind11;
        namespace st   = SIXTRL_CXX_NAMESPACE;
        namespace stpy = SIXTRL_CXX_NAMESPACE::python;
    }

    void InitHelper_common_particles( stpy::InitHelper& root )
    {
        stpy::InitHelper_common_particles_single_particle( root );
        stpy::InitHelper_common_particles_particles( root );
        stpy::InitHelper_common_particles_particles_addr( root );

        stpy::InitHelper_common_particles_demotrack( root );
    }

    void InitHelper_common_particles_single_particle( stpy::InitHelper& root )
    {
        using particle_t        = ::NS(SingleParticle);
        using particle_set_t    = ::NS(Particles);
        using real_type         = ::NS(particle_real_type);
        using index_type        = ::NS(particle_index_type);
        using size_type         = ::NS(cobj_size_type);
        using npart_type        = ::NS(particles_num_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.single_particle_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            real_type  const x,       real_type  const y,
            real_type  const px,      real_type  const py,
            real_type  const zeta,    real_type  const delta,
            index_type const state,   index_type const at_element,
            index_type const at_turn, index_type const id,
            real_type  const psigma,  real_type  const rpp,
            real_type  const rvv,     real_type  const chi,
            real_type  const charge_ratio,
            real_type  const charge0, real_type  const mass0,
            real_type  const beta0,   real_type  const gamma0,
            real_type  const p0c,     real_type  const s ) {
            return std::unique_ptr< particle_t, py::nodelete >(
                ::NS(Particle_cbuffer_add)( cbuffer.as_c_api(),
                    x, y, px, py, zeta, delta, state, at_element, at_turn, id,
                        psigma, rpp, rvv, chi, charge_ratio, charge0, mass0,
                            beta0, gamma0, p0c, s ) );
            } ),
            "default constructor, stored instance on a CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "x" ) = ::NS(Particle_default_x)(),
            py::arg( "y" ) = ::NS(Particle_default_y)(),
            py::arg( "px" ) = ::NS(Particle_default_px)(),
            py::arg( "py" ) = ::NS(Particle_default_py)(),
            py::arg( "zeta" ) = ::NS(Particle_default_zeta)(),
            py::arg( "delta" ) = ::NS(Particle_default_delta)(),
            py::arg( "state" ) = ::NS(Particle_default_state)(),
            py::arg( "at_element" ) = ::NS(Particle_default_at_element)(),
            py::arg( "at_turn" ) = ::NS(Particle_default_at_turn)(),
            py::arg( "id" ) = ::NS(Particle_default_id)(),
            py::arg( "psigma" ) = ::NS(Particle_default_psigma)(),
            py::arg( "rpp" ) = ::NS(Particle_default_rpp)(),
            py::arg( "rvv" ) = ::NS(Particle_default_rvv)(),
            py::arg( "chi" ) = ::NS(Particle_default_chi)(),
            py::arg( "charge_ratio" ) = ::NS(Particle_default_charge_ratio)(),
            py::arg( "charge0" ) = ::NS(Particle_default_charge0)(),
            py::arg( "mass0" ) = ::NS(Particle_default_mass0)(),
            py::arg( "beta0" ) = ::NS(Particle_default_beta0)(),
            py::arg( "gamma0" ) = ::NS(Particle_default_gamma0)(),
            py::arg( "p0c" ) = ::NS(Particle_default_p0c)(),
            py::arg( "s" ) = ::NS(Particle_default_s)() );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& view, size_type const pos_in_buffer )
                -> SIXTRL_PARTICLE_ARGPTR_DEC particle_t* {
                return ::NS(Particle_from_cbuffer)(
                    view.as_c_api(), pos_in_buffer ); },
            py::return_value_policy::reference,
            "get instance of CParticle from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW",
            []( cbuffer_view_type& view ) ->
                SIXTRL_PARTICLE_ARGPTR_DEC particle_t*
            { return ::NS(Particle_cbuffer_new)( view.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CParticle instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD", []( cbuffer_view_type& view,
            real_type  const x,       real_type  const y,
            real_type  const px,      real_type  const py,
            real_type  const zeta,    real_type  const delta,
            index_type const state,   index_type const at_element,
            index_type const at_turn, index_type const id,
            real_type  const psigma,  real_type  const rpp,
            real_type  const rvv,     real_type  const chi,
            real_type  const charge_ratio,
            real_type  const charge0, real_type  const mass0,
            real_type  const beta0,   real_type  const gamma0,
            real_type  const p0c,     real_type  const s ) ->
                SIXTRL_PARTICLE_ARGPTR_DEC particle_t*
            {
                return ::NS(Particle_cbuffer_add)( view.as_c_api(),
                    x, y, px, py, zeta, delta, state, at_element, at_turn, id,
                        psigma, rpp, rvv, chi, charge_ratio, charge0, mass0, beta0,
                            gamma0, p0c, s );
            },
            py::return_value_policy::reference,
            "append a fully parameterised CParticle instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "x" ) = ::NS(Particle_default_x)(),
            py::arg( "y" ) = ::NS(Particle_default_y)(),
            py::arg( "px" ) = ::NS(Particle_default_px)(),
            py::arg( "py" ) = ::NS(Particle_default_py)(),
            py::arg( "zeta" ) = ::NS(Particle_default_zeta)(),
            py::arg( "delta" ) = ::NS(Particle_default_delta)(),
            py::arg( "state" ) = ::NS(Particle_default_state)(),
            py::arg( "at_element" ) = ::NS(Particle_default_at_element)(),
            py::arg( "at_turn" ) = ::NS(Particle_default_at_turn)(),
            py::arg( "id" ) = ::NS(Particle_default_id)(),
            py::arg( "psigma" ) = ::NS(Particle_default_psigma)(),
            py::arg( "rpp" ) = ::NS(Particle_default_rpp)(),
            py::arg( "rvv" ) = ::NS(Particle_default_rvv)(),
            py::arg( "chi" ) = ::NS(Particle_default_chi)(),
            py::arg( "charge_ratio" ) = ::NS(Particle_default_charge_ratio)(),
            py::arg( "charge0" ) = ::NS(Particle_default_charge0)(),
            py::arg( "mass0" ) = ::NS(Particle_default_mass0)(),
            py::arg( "beta0" ) = ::NS(Particle_default_beta0)(),
            py::arg( "gamma0" ) = ::NS(Particle_default_gamma0)(),
            py::arg( "p0c" ) = ::NS(Particle_default_p0c)(),
            py::arg( "s" ) = ::NS(Particle_default_s)() );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& view, particle_t const& p ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC particle_t*
            {
                return ::NS(Particle_cbuffer_add_copy)( view.as_c_api(), &p );
            },
            py::return_value_policy::reference,
            "append a copy of the CParticle instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( particle_t const& p, cbuffer_view_type& view ) ->
                SIXTRL_PARTICLE_ARGPTR_DEC particle_t*
            {
                return ::NS(Particle_cbuffer_add_copy)( view.as_c_api(), &p );
            },
            py::return_value_policy::reference,
            "append a copy of the calling CParticle instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* ------------------------------------------------------------------ */

        obj.def_property( "x",
            []( particle_t const& self ) {
                return ::NS(Particle_x)( &self ); },
            []( particle_t& self, real_type const x ) {
                ::NS(Particle_set_x)( &self, x ); } );

        obj.def_property( "y",
            []( particle_t const& self ) {
                return ::NS(Particle_y)( &self ); },
            []( particle_t& self, real_type const y ) {
                ::NS(Particle_set_y)( &self, y ); } );

        obj.def_property( "px",
            []( particle_t const& self ) {
                return ::NS(Particle_px)( &self ); },
            []( particle_t& self, real_type const px ) {
                ::NS(Particle_set_px)( &self, px ); } );

        obj.def_property( "py",
            []( particle_t const& self ) {
                return ::NS(Particle_py)( &self ); },
            []( particle_t& self, real_type const py ) {
                ::NS(Particle_set_py)( &self, py ); } );

        obj.def_property( "zeta",
            []( particle_t const& self ) {
                return ::NS(Particle_zeta)( &self ); },
            []( particle_t& self, real_type const zeta ) {
                ::NS(Particle_set_zeta)( &self, zeta ); } );

        obj.def_property( "delta",
            []( particle_t const& self ) {
                return ::NS(Particle_delta)( &self ); },
            []( particle_t& self, real_type const delta ) {
                ::NS(Particle_set_delta)( &self, delta ); } );

        obj.def_property( "psigma",
            []( particle_t const& self ) {
                return ::NS(Particle_psigma)( &self ); },
            []( particle_t& self, real_type const psigma ) {
                NS(Particle_set_psigma)( &self, psigma ); } );

        obj.def_property( "rpp",
            []( particle_t const& self ) {
                return ::NS(Particle_rpp)( &self ); },
            []( particle_t& self, real_type const rpp ) {
                ::NS(Particle_set_rpp)( &self, rpp ); } );

        obj.def_property( "rvv",
            []( particle_t const& self ) {
                return ::NS(Particle_rvv)( &self ); },
            []( particle_t& self, real_type const rvv ) {
                ::NS(Particle_set_rvv)( &self, rvv ); } );

        obj.def_property( "chi",
            []( particle_t const& self ) {
                return ::NS(Particle_chi)( &self ); },
            []( particle_t& self, real_type const chi ) {
                ::NS(Particle_set_chi)( &self, chi ); } );

        obj.def_property( "charge_ratio",
            []( particle_t const& self ) {
                return ::NS(Particle_charge_ratio)( &self ); },
            []( particle_t& self, real_type const charge_ratio ) {
                ::NS(Particle_set_charge_ratio)( &self, charge_ratio ); } );

        obj.def_property( "mass0",
            []( particle_t const& self ) {
                return ::NS(Particle_mass0)( &self ); },
            []( particle_t& self, real_type const mass0 ) {
                ::NS(Particle_set_mass0)( &self, mass0 ); } );

        obj.def_property( "charge0",
            []( particle_t const& self ) {
                return ::NS(Particle_charge0)( &self ); },
            []( particle_t& self, real_type const charge0 ) {
                ::NS(Particle_set_charge0)( &self, charge0 ); } );

        obj.def_property( "beta0",
            []( particle_t const& self ) {
                return ::NS(Particle_beta0)( &self ); },
            []( particle_t& self, real_type const beta0 ) {
                ::NS(Particle_set_beta0)( &self, beta0 ); } );

        obj.def_property( "gamma0",
            []( particle_t const& self ) {
                return ::NS(Particle_gamma0)( &self ); },
            []( particle_t& self, real_type const gamma0 ) {
                ::NS(Particle_set_gamma0)( &self, gamma0 ); } );

        obj.def_property( "p0c",
            []( particle_t const& self ) {
                return ::NS(Particle_p0c)( &self ); },
            []( particle_t& self, real_type const p0c ) {
                ::NS(Particle_set_p0c)( &self, p0c ); } );

        obj.def_property( "s",
            []( particle_t const& self ) {
                return ::NS(Particle_s)( &self ); },
            []( particle_t& self, real_type const s ) {
                ::NS(Particle_set_s)( &self, s ); } );

        obj.def_property( "state",
            []( particle_t const& self ) {
                return ::NS(Particle_state)( &self ); },
            []( particle_t& self, index_type const state ) {
                ::NS(Particle_set_state)( &self, state ); } );

        obj.def_property_readonly( "is_active", []( particle_t const& self ) {
            return ::NS(Particle_is_active)( &self ); } );

        obj.def_property_readonly( "is_lost", []( particle_t const& self ) {
            return ::NS(Particle_is_lost)( &self ); } );

        obj.def_property_readonly( "is_not_lost", []( particle_t const& self ) {
            return !::NS(Particle_is_lost)( &self ); } );

        obj.def( "update_delta", []( particle_t& self, real_type const delta ) {
            return ::NS(Particle_update_delta)( &self, delta ); } );

        obj.def( "mark_as_lost", []( particle_t& self ) {
            ::NS(Particle_mark_as_lost)( &self ); } );

        obj.def( "keep_active_if_not_lost",
            []( particle_t& self, index_type const new_state ) {
            ::NS(Particle_keep_active_if_not_lost)( &self, new_state ); } );

        obj.def_property( "at_element",
            []( particle_t const& self ) {
                return ::NS(Particle_at_element)( &self ); },
            []( particle_t& self, real_type const at_element ) {
                ::NS(Particle_set_at_element)( &self, at_element ); } );

        obj.def( "increment_at_element", []( particle_t& self ) {
            ::NS(Particle_increment_at_element)( &self ); } );

        obj.def_property( "at_turn",
            []( particle_t const& self ) {
                return ::NS(Particle_at_turn)( &self ); },
            []( particle_t& self, real_type const at_turn ) {
                ::NS(Particle_set_at_turn)( &self, at_turn ); } );

        obj.def( "finish_turn",
            []( particle_t& self, index_type const start_at_element ) {
            ::NS(Particle_finish_turn)( &self, start_at_element ); } );

        obj.def_property( "id",
            []( particle_t const& self ) {
                return ::NS(Particle_id)( &self ); },
            []( particle_t& self, real_type const id ) {
                ::NS(Particle_set_id)( &self, id ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "tau",
            []( particle_t const& self ) {
                return ::NS(Particle_tau)( &self ); },
            []( particle_t& self, real_type const tau ) {
                ::NS(Particle_update_tau)( &self, tau ); } );

        obj.def_property( "ptau",
            []( particle_t const& self ) {
                return ::NS(Particle_ptau)( &self ); },
            []( particle_t& self, real_type const ptau ) {
                ::NS(Particle_update_ptau)( &self, ptau ); } );

        obj.def_property( "sigma",
            []( particle_t const& self ) {
                return ::NS(Particle_sigma)( &self ); },
            []( particle_t& self, real_type const sigma ) {
                ::NS(Particle_set_sigma)( &self, sigma ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly( "charge", []( particle_t const& self ) {
            return ::NS(Particle_charge)( &self ); } );

        obj.def_property_readonly( "mass", []( particle_t const& self ) {
            return ::NS(Particle_mass)( &self ); } );

        obj.def_property_readonly( "mass_ratio", []( particle_t const& self ) {
            return ::NS(Particle_mass_ratio)( &self ); } );

        obj.def_property_readonly( "energy0", []( particle_t const& self ) {
            return ::NS(Particle_energy0)( &self ); } );

        obj.def_property( "energy",
            []( particle_t const& self ) {
                return ::NS(Particle_energy)( &self ); },
            []( particle_t& self, real_type const energy ) {
                ::NS(Particle_update_energy)( &self, energy ); } );

        obj.def( "add_to_energy",
            []( particle_t& self, real_type const d_energy ) {
                ::NS(Particle_add_to_energy)( &self, d_energy ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(Particle_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(Particle_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(Particle_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(Particle_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( particle_t const& self, size_type const slot_size ) {
                return ::NS(Particle_cobj_required_num_bytes)(
                    &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( particle_t& self ) {
            ::NS(Particle_clear)( &self ); } );

        obj.def( "init", []( particle_t& self,
            real_type  const x,       real_type  const y,
            real_type  const px,      real_type  const py,
            real_type  const zeta,    real_type  const delta,
            index_type const state,   index_type const at_element,
            index_type const at_turn, index_type const id,
            real_type  const psigma,  real_type  const rpp,
            real_type  const rvv,     real_type  const chi,
            real_type  const charge_ratio,
            real_type  const charge0, real_type const mass0,
            real_type  const beta0,   real_type const gamma0,
            real_type  const p0c,     real_type const s ) {
            return ::NS(Particle_init)( &self, x, y, px, py, zeta, delta, state,
                at_element, at_turn, id, psigma, rpp, rvv, chi, charge_ratio,
                    charge0, mass0, beta0, gamma0, p0c, s ); },
            "Init single particle with scalar values",
            py::arg( "x" ), py::arg( "y" ), py::arg( "px" ), py::arg( "py" ),
            py::arg( "zeta" ), py::arg( "delta" ), py::arg( "state" ),
            py::arg( "at_element" ), py::arg( "at_turn" ), py::arg( "id" ),
            py::arg( "psigma" )       = ::NS(Particle_default_psigma)(),
            py::arg( "rpp" )          = ::NS(Particle_default_rpp)(),
            py::arg( "rvv" )          = ::NS(Particle_default_rvv)(),
            py::arg( "chi" )          = ::NS(Particle_default_chi)(),
            py::arg( "charge_ratio" ) = ::NS(Particle_default_charge_ratio)(),
            py::arg( "charge0" )      = ::NS(Particle_default_charge0)(),
            py::arg( "mass0" )        = ::NS(Particle_default_mass0)(),
            py::arg( "beta0" )        = ::NS(Particle_default_beta0)(),
            py::arg( "gamma0" )       = ::NS(Particle_default_gamma0)(),
            py::arg( "p0c" )          = ::NS(Particle_default_p0c)(),
            py::arg( "s" )            = ::NS(Particle_default_s)() );

        obj.def( "from_particles",
            []( particle_t& self, particle_set_t const& pset,
                npart_type const idx )
            {
                return ::NS(Particles_to_single_particle)( &pset, idx, &self );
            },
            "Copy the contents of a particle-set to the calling "
            "single particle instance",
            py::arg( "pset" ), py::arg( "idx" ) );

        obj.def( "to_particles",
            []( particle_t const& self, particle_set_t& pset,
                npart_type const idx )
            {
                return ::NS(Particles_from_single_particle)( &pset, idx, &self );
            },
            "Copy the contents of the calling single particle to an entry in "
            "the particle-set",
            py::arg( "pset" ), py::arg( "idx" ) );

    }

    void InitHelper_common_particles_particles( stpy::InitHelper& root )
    {
        using particle_t     = ::NS(SingleParticle);
        using particle_set_t = ::NS(Particles);
        using real_type      = ::NS(particle_real_type);
        using index_type     = ::NS(particle_index_type);
        using size_type      = ::NS(cobj_size_type);
        using npart_type     = ::NS(particles_num_type);
        using addr_type      = ::NS(address_type);

        using real_adapter_type  = stpy::RealBufferAdapter;
        using index_adapter_type = stpy::Int64BufferAdapter;

        using cbuffer_view_type  = st::CBufferView;

        using py_array_real_t = py::array_t<
            real_type, py::array::c_style | py::array::forcecast >;

        using py_array_index_t = py::array_t<
            index_type, py::array::c_style | py::array::forcecast >;

        auto& obj = root.particles_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            npart_type max_num_particles,
            real_type const charge0, real_type const mass0,
            real_type const beta0, real_type const gamma0,
            real_type const p0c,
            real_type const s, real_type const x, real_type const y,
            real_type const px, real_type const py, real_type const zeta,
            real_type const psigma, real_type const delta,
            real_type const rpp, real_type const rvv, real_type const chi,
            real_type const charge_ratio, index_type start_id,
            index_type const at_element, index_type const at_turn,
            index_type const state, npart_type num_particles,
            index_type id_stride )
        {
            if( ( max_num_particles < npart_type{ 0 } ) &&
                ( num_particles >= npart_type{ 0 } ) )
            {
                max_num_particles = num_particles;
            }
            else if( ( max_num_particles >= npart_type{ 0 } ) &&
                        ( num_particles < npart_type{ 0 } ) )
            {
                num_particles = max_num_particles;
            }
            else if( ( max_num_particles < npart_type{ 0 } ) &&
                        ( num_particles < npart_type{ 0 } ) )
            {
                max_num_particles = npart_type{ 0 };
                num_particles = npart_type{ 0 };
            }

            std::unique_ptr< particle_set_t, py::nodelete > created_obj(
                ::NS(Particles_cbuffer_add)( cbuffer.as_c_api(),
                    max_num_particles, num_particles,
                    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                    nullptr, nullptr, nullptr, nullptr, nullptr,
                    nullptr, nullptr, nullptr, nullptr ) );

            if( ( created_obj.get() != nullptr ) &&
                ( num_particles > npart_type{ 0 } ) )
            {
                particle_set_t* pset = created_obj.get();

                if( start_id < index_type{ SIXTRL_PARTICLE_MIN_LEGAL_ID } )
                    start_id = index_type{ SIXTRL_PARTICLE_MIN_LEGAL_ID };

                index_type id = start_id;

                if( id_stride < index_type{ 1 } )
                    id_stride = index_type{ 1 };

                for( npart_type ii = 0 ; ii < num_particles ;
                        ++ii, id += id_stride )
                {
                    ::NS(Particles_set_charge0)( pset, ii, charge0 );
                    ::NS(Particles_set_mass0)( pset, ii, mass0 );
                    ::NS(Particles_set_beta0)( pset, ii, beta0 );
                    ::NS(Particles_set_gamma0)( pset, ii, gamma0 );
                    ::NS(Particles_set_p0c)( pset, ii, p0c );
                    ::NS(Particles_set_s)( pset, ii, s );
                    ::NS(Particles_set_x)( pset, ii, x );
                    ::NS(Particles_set_y)( pset, ii, y );
                    ::NS(Particles_set_px)( pset, ii, px );
                    ::NS(Particles_set_py)( pset, ii, py );
                    ::NS(Particles_set_zeta)( pset, ii, zeta );
                    ::NS(Particles_set_psigma)( pset, ii, psigma );
                    ::NS(Particles_set_delta)( pset, ii, delta );
                    ::NS(Particles_set_rpp)( pset, ii, rpp );
                    ::NS(Particles_set_rvv)( pset, ii, rvv );
                    ::NS(Particles_set_chi)( pset, ii, chi );
                    ::NS(Particles_set_charge_ratio)( pset, ii, charge_ratio );
                    ::NS(Particles_set_id)( pset, ii, id );
                    ::NS(Particles_set_at_element)( pset, ii, at_element );
                    ::NS(Particles_set_at_turn)( pset, ii, at_turn );
                    ::NS(Particles_set_at_element)( pset, ii, at_element );
                    ::NS(Particles_set_state)( pset, ii, state );
                }
            }

            return std::move( created_obj ); } ),
            "default constructor, stored on a CBufferView!",
            py::arg( "cbuffer" ),
            py::arg( "max_num_particles" ),
            py::arg( "charge0" ) = ::NS(Particles_default_charge0)(),
            py::arg( "mass0" ) = ::NS(Particles_default_mass0)(),
            py::arg( "beta0" ) = ::NS(Particles_default_beta0)(),
            py::arg( "gamma0" ) = ::NS(Particles_default_gamma0)(),
            py::arg( "p0c" ) = ::NS(Particles_default_p0c)(),
            py::arg( "s" ) = ::NS(Particles_default_s)(),
            py::arg( "x" ) = ::NS(Particles_default_x)(),
            py::arg( "y" ) = ::NS(Particles_default_y)(),
            py::arg( "px" ) = ::NS(Particles_default_px)(),
            py::arg( "py" ) = ::NS(Particles_default_py)(),
            py::arg( "zeta" ) = ::NS(Particles_default_zeta)(),
            py::arg( "psigma" ) = ::NS(Particles_default_psigma)(),
            py::arg( "delta" ) = ::NS(Particles_default_delta)(),
            py::arg( "rpp" ) = ::NS(Particles_default_rpp)(),
            py::arg( "rvv" ) = ::NS(Particles_default_rvv)(),
            py::arg( "chi" ) = ::NS(Particles_default_chi)(),
            py::arg( "charge_ratio" ) = ::NS(Particles_default_charge_ratio)(),
            py::arg( "start_id" ) = index_type{ SIXTRL_PARTICLE_MIN_LEGAL_ID },
            py::arg( "at_element" ) = ::NS(Particles_default_at_element)(),
            py::arg( "at_turn" ) = ::NS(Particles_default_at_turn)(),
            py::arg( "state" ) = ::NS(Particles_default_state)(),
            py::arg( "num_particles" ) = npart_type{ -1 },
            py::arg( "id_stride" ) = index_type{ 1 } );

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            tl::optional< py_array_real_t  > charge0,
            tl::optional< py_array_real_t  > mass0,
            tl::optional< py_array_real_t  > beta0,
            tl::optional< py_array_real_t  > gamma0,
            tl::optional< py_array_real_t  > p0c,
            tl::optional< py_array_real_t  > s,
            tl::optional< py_array_real_t  > x,
            tl::optional< py_array_real_t  > y,
            tl::optional< py_array_real_t  > px,
            tl::optional< py_array_real_t  > py,
            tl::optional< py_array_real_t  > zeta,
            tl::optional< py_array_real_t  > psigma,
            tl::optional< py_array_real_t  > delta,
            tl::optional< py_array_real_t  > rpp,
            tl::optional< py_array_real_t  > rvv,
            tl::optional< py_array_real_t  > chi,
            tl::optional< py_array_real_t  > charge_ratio,
            tl::optional< py_array_index_t > id,
            tl::optional< py_array_index_t > at_element,
            tl::optional< py_array_index_t > at_turn,
            tl::optional< py_array_index_t > state,
            npart_type max_num_particles, npart_type num_particles ) {

            using real_cptr_t  = SIXTRL_PARTICLES_DATAPTR_DEC real_type const*;
            using index_cptr_t = SIXTRL_PARTICLES_DATAPTR_DEC index_type const*;

            size_type field_lengths[ 21 ] = {
                stpy::PyArray_length_1d< real_type  >( charge0 ),
                stpy::PyArray_length_1d< real_type  >( mass0 ),
                stpy::PyArray_length_1d< real_type  >( beta0 ),
                stpy::PyArray_length_1d< real_type  >( gamma0 ),
                stpy::PyArray_length_1d< real_type  >( p0c ),
                stpy::PyArray_length_1d< real_type  >( s ),
                stpy::PyArray_length_1d< real_type  >( x ),
                stpy::PyArray_length_1d< real_type  >( y ),
                stpy::PyArray_length_1d< real_type  >( px ),
                stpy::PyArray_length_1d< real_type  >( py ),
                stpy::PyArray_length_1d< real_type  >( zeta ),
                stpy::PyArray_length_1d< real_type  >( psigma ),
                stpy::PyArray_length_1d< real_type  >( delta ),
                stpy::PyArray_length_1d< real_type  >( rpp ),
                stpy::PyArray_length_1d< real_type  >( rvv ),
                stpy::PyArray_length_1d< real_type  >( chi ),
                stpy::PyArray_length_1d< real_type  >( charge_ratio ),
                stpy::PyArray_length_1d< index_type >( id ),
                stpy::PyArray_length_1d< index_type >( at_element ),
                stpy::PyArray_length_1d< index_type >( at_turn ),
                stpy::PyArray_length_1d< index_type >( state )
            };

            size_type min_field_length = static_cast< npart_type >(
                *std::max_element( &field_lengths[ 0 ], &field_lengths[ 21 ] ) );

            npart_type const max_field_length =
                static_cast< npart_type >( max_field_length );

            for( size_type ii = size_type{ 0 } ; ii < 21u ; ++ii ) {
                if( field_lengths[ ii ] == size_type{ 0 } ) continue;
                if( min_field_length > field_lengths[ ii ] )
                    min_field_length = field_lengths[ ii ]; }

            if( num_particles < static_cast< npart_type >( min_field_length ) )
                num_particles = static_cast< npart_type >( min_field_length );

            if( max_num_particles < num_particles )
                max_num_particles = num_particles;

            size_type const nn = ( max_num_particles > npart_type{ 0 } )
                ? static_cast< size_type >( max_num_particles )
                : size_type{ 0 };

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            std::unique_ptr< std::vector< real_type > > dummy_real_ptrs[ 17 ] =
            {
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr }
            };

            real_cptr_t const real_fields[ 17 ] = {
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( charge0, nn, field_lengths[ 0 ],
                        dummy_real_ptrs[ 0 ], ::NS(Particle_default_charge0)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( mass0, nn, field_lengths[ 1 ],
                        dummy_real_ptrs[ 1 ], ::NS(Particle_default_mass0)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( beta0, nn, field_lengths[ 2 ],
                        dummy_real_ptrs[ 2 ], ::NS(Particle_default_beta0)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( gamma0, nn, field_lengths[ 3 ],
                        dummy_real_ptrs[ 3 ], ::NS(Particle_default_gamma0)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( p0c, nn, field_lengths[ 4 ],
                        dummy_real_ptrs[ 4 ], ::NS(Particle_default_p0c)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( s, nn, field_lengths[ 5 ],
                        dummy_real_ptrs[ 5 ], ::NS(Particle_default_s)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( x, nn, field_lengths[ 6 ],
                        dummy_real_ptrs[ 6 ], ::NS(Particle_default_x)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( y, nn, field_lengths[ 7 ],
                        dummy_real_ptrs[ 7 ], ::NS(Particle_default_y)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( px, nn, field_lengths[ 8 ],
                        dummy_real_ptrs[ 8 ], ::NS(Particle_default_px)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( py, nn, field_lengths[ 9 ],
                        dummy_real_ptrs[ 9 ], ::NS(Particle_default_py)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( zeta, nn, field_lengths[ 10 ],
                        dummy_real_ptrs[ 10 ], ::NS(Particle_default_zeta)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( psigma, nn, field_lengths[ 11 ],
                        dummy_real_ptrs[ 11 ], ::NS(Particle_default_psigma)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( delta, nn, field_lengths[ 12 ],
                        dummy_real_ptrs[ 12 ], ::NS(Particle_default_delta)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( rpp, nn, field_lengths[ 13 ],
                        dummy_real_ptrs[ 13 ], ::NS(Particle_default_rpp)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( rvv, nn, field_lengths[ 14 ],
                        dummy_real_ptrs[ 14 ], ::NS(Particle_default_rvv)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( chi, nn, field_lengths[ 15 ],
                        dummy_real_ptrs[ 15 ], ::NS(Particle_default_chi)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( charge_ratio, nn, field_lengths[ 16 ],
                        dummy_real_ptrs[ 16 ],
                            ::NS(Particle_default_charge_ratio)() ) };

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            std::unique_ptr< std::vector< index_type > > dummy_index_ptrs[ 4 ] =
            {
                std::unique_ptr< std::vector< index_type > >{ nullptr },
                std::unique_ptr< std::vector< index_type > >{ nullptr },
                std::unique_ptr< std::vector< index_type > >{ nullptr },
                std::unique_ptr< std::vector< index_type > >{ nullptr }
            };

            index_cptr_t index_fields[ 4 ] = {
                stpy::PyArray_stable_base_pointer_1d< index_type, size_type,
                    index_cptr_t >( id, nn, field_lengths[ 17 ],
                        dummy_index_ptrs[ 0 ], ::NS(Particle_default_id)() ),
                stpy::PyArray_stable_base_pointer_1d< index_type, size_type,
                    index_cptr_t >( at_element, nn, field_lengths[ 18 ],
                        dummy_index_ptrs[ 1 ], ::NS(Particle_default_at_element)() ),
                stpy::PyArray_stable_base_pointer_1d< index_type, size_type,
                    index_cptr_t >( at_turn, nn, field_lengths[ 19 ],
                        dummy_index_ptrs[ 2 ], ::NS(Particle_default_at_turn)() ),
                stpy::PyArray_stable_base_pointer_1d< index_type, size_type,
                    index_cptr_t >( id, nn, field_lengths[ 20 ],
                        dummy_index_ptrs[ 3 ], ::NS(Particle_default_state)() )
            };

            return std::unique_ptr< particle_set_t, py::nodelete >(
                ::NS(Particles_cbuffer_add)( cbuffer.as_c_api(),
                    max_num_particles, num_particles,
                    real_fields[  0 ], real_fields[  1 ], real_fields[  2 ],
                    real_fields[  3 ], real_fields[  4 ], real_fields[  5 ],
                    real_fields[  6 ], real_fields[  7 ], real_fields[  9 ],
                    real_fields[ 10 ], real_fields[ 11 ], real_fields[ 12 ],
                    real_fields[ 13 ], real_fields[ 13 ], real_fields[ 14 ],
                    real_fields[ 15 ], real_fields[ 16 ],
                    index_fields[ 0 ], index_fields[ 1 ],
                    index_fields[ 2 ], index_fields[ 3 ] ) ); } ),
            "construct a Particles instance on a cbuffer instance",
            py::arg( "cbuffer" ), py::arg( "charge0" ), py::arg( "mass0" ),
            py::arg( "beta0" ),   py::arg( "gamma0"  ), py::arg( "p0c" ),
            py::arg( "s" ),       py::arg( "x" ),       py::arg( "y" ),
            py::arg( "px" ),      py::arg( "py" ),      py::arg( "zeta" ),
            py::arg( "psigma" ),  py::arg( "delta" ),   py::arg( "rpp" ),
            py::arg( "rvv" ),     py::arg( "chi" ),     py::arg( "charge_ratio" ),
            py::arg( "id" ),      py::arg( "at_element" ),
            py::arg( "at_turn" ), py::arg( "state" ),
            py::arg( "max_num_particles" ) = npart_type{ 0 },
            py::arg( "num_particles" ) = npart_type{ -1 } );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& view, size_type const pos_in_buffer )
                -> SIXTRL_PARTICLES_ARGPTR_DEC particle_set_t* {
                return ::NS(Particles_from_cbuffer)(
                    view.as_c_api(), pos_in_buffer ); },
            py::return_value_policy::reference,
            "get instance of CParticles from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW",
            []( cbuffer_view_type& view, npart_type const max_num_particles )
                -> SIXTRL_PARTICLES_ARGPTR_DEC particle_set_t*
            { return ::NS(Particles_cbuffer_new)(
                view.as_c_api(), max_num_particles ); },
            py::return_value_policy::reference,
            "append a new CParticles instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ), py::arg( "max_num_particles" ) );

        obj.def_static( "ADD", []( cbuffer_view_type& cbuffer,
            tl::optional< py_array_real_t  > charge0,
            tl::optional< py_array_real_t  > mass0,
            tl::optional< py_array_real_t  > beta0,
            tl::optional< py_array_real_t  > gamma0,
            tl::optional< py_array_real_t  > p0c,
            tl::optional< py_array_real_t  > s,
            tl::optional< py_array_real_t  > x,
            tl::optional< py_array_real_t  > y,
            tl::optional< py_array_real_t  > px,
            tl::optional< py_array_real_t  > py,
            tl::optional< py_array_real_t  > zeta,
            tl::optional< py_array_real_t  > psigma,
            tl::optional< py_array_real_t  > delta,
            tl::optional< py_array_real_t  > rpp,
            tl::optional< py_array_real_t  > rvv,
            tl::optional< py_array_real_t  > chi,
            tl::optional< py_array_real_t  > charge_ratio,
            tl::optional< py_array_index_t > id,
            tl::optional< py_array_index_t > at_element,
            tl::optional< py_array_index_t > at_turn,
            tl::optional< py_array_index_t > state,
            npart_type max_num_particles, npart_type num_particles ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC particle_set_t* {

            using real_cptr_t  =
                SIXTRL_PARTICLES_DATAPTR_DEC real_type const*;

            using index_cptr_t =
                SIXTRL_PARTICLES_DATAPTR_DEC index_type const*;

            size_type field_lengths[ 21 ] = {
                stpy::PyArray_length_1d< real_type  >( charge0 ),
                stpy::PyArray_length_1d< real_type  >( mass0 ),
                stpy::PyArray_length_1d< real_type  >( beta0 ),
                stpy::PyArray_length_1d< real_type  >( gamma0 ),
                stpy::PyArray_length_1d< real_type  >( p0c ),
                stpy::PyArray_length_1d< real_type  >( s ),
                stpy::PyArray_length_1d< real_type  >( x ),
                stpy::PyArray_length_1d< real_type  >( y ),
                stpy::PyArray_length_1d< real_type  >( px ),
                stpy::PyArray_length_1d< real_type  >( py ),
                stpy::PyArray_length_1d< real_type  >( zeta ),
                stpy::PyArray_length_1d< real_type  >( psigma ),
                stpy::PyArray_length_1d< real_type  >( delta ),
                stpy::PyArray_length_1d< real_type  >( rpp ),
                stpy::PyArray_length_1d< real_type  >( rvv ),
                stpy::PyArray_length_1d< real_type  >( chi ),
                stpy::PyArray_length_1d< real_type  >( charge_ratio ),
                stpy::PyArray_length_1d< index_type >( id ),
                stpy::PyArray_length_1d< index_type >( at_element ),
                stpy::PyArray_length_1d< index_type >( at_turn ),
                stpy::PyArray_length_1d< index_type >( state )
            };

            size_type min_field_length = static_cast< npart_type >(
                *std::max_element( &field_lengths[ 0 ], &field_lengths[ 21 ] ) );

            npart_type const max_field_length =
                static_cast< npart_type >( max_field_length );

            for( size_type ii = size_type{ 0 } ; ii < 21u ; ++ii ) {
                if( field_lengths[ ii ] == size_type{ 0 } ) continue;
                if( min_field_length > field_lengths[ ii ] )
                    min_field_length = field_lengths[ ii ]; }

            if( num_particles < static_cast< npart_type >( min_field_length ) )
                num_particles = static_cast< npart_type >( min_field_length );

            if( max_num_particles < num_particles )
                max_num_particles = num_particles;

            size_type const nn = ( max_num_particles > npart_type{ 0 } )
                ? static_cast< size_type >( max_num_particles )
                : size_type{ 0 };

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            std::unique_ptr< std::vector< real_type > > dummy_real_ptrs[ 17 ] =
            {
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr },
                std::unique_ptr< std::vector< real_type > >{ nullptr }
            };

            real_cptr_t real_fields[ 17 ] = {
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( charge0, nn, field_lengths[ 0 ],
                        dummy_real_ptrs[ 0 ], ::NS(Particle_default_charge0)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( mass0, nn, field_lengths[ 1 ],
                        dummy_real_ptrs[ 1 ], ::NS(Particle_default_mass0)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( beta0, nn, field_lengths[ 2 ],
                        dummy_real_ptrs[ 2 ], ::NS(Particle_default_beta0)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( gamma0, nn, field_lengths[ 3 ],
                        dummy_real_ptrs[ 3 ], ::NS(Particle_default_gamma0)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( p0c, nn, field_lengths[ 4 ],
                        dummy_real_ptrs[ 4 ], ::NS(Particle_default_p0c)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( s, nn, field_lengths[ 5 ],
                        dummy_real_ptrs[ 5 ], ::NS(Particle_default_s)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( x, nn, field_lengths[ 6 ],
                        dummy_real_ptrs[ 6 ], ::NS(Particle_default_x)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( y, nn, field_lengths[ 7 ],
                        dummy_real_ptrs[ 7 ], ::NS(Particle_default_y)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( px, nn, field_lengths[ 8 ],
                        dummy_real_ptrs[ 8 ], ::NS(Particle_default_px)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( py, nn, field_lengths[ 9 ],
                        dummy_real_ptrs[ 9 ], ::NS(Particle_default_py)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( zeta, nn, field_lengths[ 10 ],
                        dummy_real_ptrs[ 10 ], ::NS(Particle_default_zeta)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( psigma, nn, field_lengths[ 11 ],
                        dummy_real_ptrs[ 11 ], ::NS(Particle_default_psigma)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( delta, nn, field_lengths[ 12 ],
                        dummy_real_ptrs[ 12 ], ::NS(Particle_default_delta)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( rpp, nn, field_lengths[ 13 ],
                        dummy_real_ptrs[ 13 ], ::NS(Particle_default_rpp)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( rvv, nn, field_lengths[ 14 ],
                        dummy_real_ptrs[ 14 ], ::NS(Particle_default_rvv)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( chi, nn, field_lengths[ 15 ],
                        dummy_real_ptrs[ 15 ], ::NS(Particle_default_chi)() ),
                stpy::PyArray_stable_base_pointer_1d< real_type, size_type,
                    real_cptr_t >( charge_ratio, nn, field_lengths[ 16 ],
                        dummy_real_ptrs[ 16 ],
                            ::NS(Particle_default_charge_ratio)() ) };

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            std::unique_ptr< std::vector< index_type > > dummy_index_ptrs[ 4 ] =
            {
                std::unique_ptr< std::vector< index_type > >{ nullptr },
                std::unique_ptr< std::vector< index_type > >{ nullptr },
                std::unique_ptr< std::vector< index_type > >{ nullptr },
                std::unique_ptr< std::vector< index_type > >{ nullptr }
            };

            index_cptr_t index_fields[ 4 ] = {
                stpy::PyArray_stable_base_pointer_1d< index_type, size_type,
                    index_cptr_t >( id, nn, field_lengths[ 17 ],
                        dummy_index_ptrs[ 0 ], ::NS(Particle_default_id)() ),
                stpy::PyArray_stable_base_pointer_1d< index_type, size_type,
                    index_cptr_t >( at_element, nn, field_lengths[ 18 ],
                        dummy_index_ptrs[ 1 ], ::NS(Particle_default_at_element)() ),
                stpy::PyArray_stable_base_pointer_1d< index_type, size_type,
                    index_cptr_t >( at_turn, nn, field_lengths[ 19 ],
                        dummy_index_ptrs[ 2 ], ::NS(Particle_default_at_turn)() ),
                stpy::PyArray_stable_base_pointer_1d< index_type, size_type,
                    index_cptr_t >( id, nn, field_lengths[ 20 ],
                        dummy_index_ptrs[ 3 ], ::NS(Particle_default_state)() )
            };

            return ::NS(Particles_cbuffer_add)( cbuffer.as_c_api(),
                max_num_particles, num_particles,
                real_fields[  0 ], real_fields[  1 ], real_fields[  2 ],
                real_fields[  3 ], real_fields[  4 ], real_fields[  5 ],
                real_fields[  6 ], real_fields[  7 ], real_fields[  9 ],
                real_fields[ 10 ], real_fields[ 11 ], real_fields[ 12 ],
                real_fields[ 13 ], real_fields[ 13 ], real_fields[ 14 ],
                real_fields[ 15 ], real_fields[ 16 ],
                index_fields[ 0 ], index_fields[ 1 ],
                index_fields[ 2 ], index_fields[ 3 ] ); },
            py::return_value_policy::reference,
            "construct a Particles instance on a cbuffer instance",
            py::arg( "cbuffer" ),
            py::arg( "charge0" ) = tl::optional< py_array_real_t >(),
            py::arg( "mass0" ) = tl::optional< py_array_real_t >(),
            py::arg( "beta0" ) = tl::optional< py_array_real_t >(),
            py::arg( "gamma0" ) = tl::optional< py_array_real_t >(),
            py::arg( "p0c" ) = tl::optional< py_array_real_t >(),
            py::arg( "s" ) = tl::optional< py_array_real_t >(),
            py::arg( "x" ) = tl::optional< py_array_real_t >(),
            py::arg( "y" ) = tl::optional< py_array_real_t >(),
            py::arg( "px" ) = tl::optional< py_array_real_t >(),
            py::arg( "py" ) = tl::optional< py_array_real_t >(),
            py::arg( "zeta" ) = tl::optional< py_array_real_t >(),
            py::arg( "psigma" ) = tl::optional< py_array_real_t >(),
            py::arg( "delta" ) = tl::optional< py_array_real_t >(),
            py::arg( "rpp" ) = tl::optional< py_array_real_t >(),
            py::arg( "rvv" ) = tl::optional< py_array_real_t >(),
            py::arg( "chi" ) = tl::optional< py_array_real_t >(),
            py::arg( "charge_ratio" ) = tl::optional< py_array_real_t >(),
            py::arg( "id" ) = tl::optional< py_array_index_t >(),
            py::arg( "at_element" ) = tl::optional< py_array_index_t >(),
            py::arg( "at_turn" ) = tl::optional< py_array_index_t >(),
            py::arg( "state" ) = tl::optional< py_array_index_t >(),
            py::arg( "max_num_particles" ) = npart_type{ 0 },
            py::arg( "num_particles" ) = npart_type{ -1 } );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& view, particle_set_t const& pset ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC particle_set_t*
            {
                return ::NS(Particles_cbuffer_add_copy)(
                    view.as_c_api(), &pset );
            },
            py::return_value_policy::reference,
            "append a copy of the CParticles instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( particle_set_t const& pset, cbuffer_view_type& view ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC particle_set_t*
            {
                return ::NS(Particles_cbuffer_add_copy)(
                    view.as_c_api(), &pset );
            },
            py::return_value_policy::reference,
            "append a copy of the calling CParticles instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* ----------------------------------------------------------------- */

        obj.def_property_readonly( "max_num_particles",
            []( particle_set_t const& pset ) -> npart_type {
                return ::NS(Particles_max_num_particles)( &pset ); } );

        obj.def_property_readonly( "num_particles",
            []( particle_set_t const& pset ) -> npart_type {
                return ::NS(Particles_num_particles)( &pset ); } );

        obj.def( "set_max_num_particles",
            []( particle_set_t& pset, npart_type const max_num_particles ) {
                ::NS(Particles_set_max_num_particles)(
                    &pset, max_num_particles ); } );

        obj.def( "set_num_particles",
            []( particle_set_t& pset, npart_type const num_particles ) {
                ::NS(Particles_set_num_particles)(
                    &pset, num_particles ); } );

        /* ----------------------------------------------------------------- */

        obj.def( "x", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_x_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move, "access all x values as a buffer" );

        obj.def( "x", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_x)( &self, idx ); } );

        obj.def( "set_x",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_x)( &self, idx, value ); } );

        obj.def_property_readonly( "x_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_x_addr)( &self ); } );

        obj.def_property_readonly( "set_x_addr",
            []( particle_set_t& self, addr_type const x_addr ) {
            ::NS(Particles_set_x_addr)( &self, x_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "y", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_y_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move, "access all y values as a buffer" );

        obj.def( "y", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_y)( &self, idx ); } );

        obj.def( "set_y",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_y)( &self, idx, value ); } );

        obj.def_property_readonly( "y_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_y_addr)( &self ); } );

        obj.def_property_readonly( "set_y_addr",
            []( particle_set_t& self, addr_type const y_addr ) {
            ::NS(Particles_set_y_addr)( &self, y_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "px", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_px_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move, "access all px values as a buffer" );

        obj.def( "px", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_px)( &self, idx ); } );

        obj.def( "set_px",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_px)( &self, idx, value ); } );

        obj.def_property_readonly( "px_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_px_addr)( &self ); } );

        obj.def_property_readonly( "set_px_addr",
            []( particle_set_t& self, addr_type const px_addr ) {
            ::NS(Particles_set_px_addr)( &self, px_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "py", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_py_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move, "access all py values as a buffer" );

        obj.def( "py", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_py)( &self, idx ); } );

        obj.def( "set_py",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_py)( &self, idx, value ); } );

        obj.def_property_readonly( "py_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_py_addr)( &self ); } );

        obj.def_property_readonly( "set_py_addr",
            []( particle_set_t& self, addr_type const py_addr ) {
            ::NS(Particles_set_py_addr)( &self, py_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "zeta", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_zeta_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move, "access all zeta values as a buffer" );

        obj.def( "zeta", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_zeta)( &self, idx ); } );

        obj.def( "set_zeta",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_zeta)( &self, idx, value ); } );

        obj.def_property_readonly( "zeta_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_zeta_addr)( &self ); } );

        obj.def_property_readonly( "set_zeta_addr",
            []( particle_set_t& self, addr_type const zeta_addr ) {
            ::NS(Particles_set_zeta_addr)( &self, zeta_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "delta", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_delta_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move,
            "access all delta values as a buffer" );

        obj.def( "delta", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_delta)( &self, idx ); } );

        obj.def( "set_delta",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_delta)( &self, idx, value ); } );

        obj.def( "update_delta",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_update_delta)( &self, idx, value ); } );

        obj.def_property_readonly( "delta_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_delta_addr)( &self ); } );

        obj.def_property_readonly( "set_delta_addr",
            []( particle_set_t& self, addr_type const delta_addr ) {
            ::NS(Particles_set_delta_addr)( &self, delta_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "psigma", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_psigma_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move,
            "access all psigma values as a buffer" );

        obj.def( "psigma", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_psigma)( &self, idx ); } );

        obj.def( "set_psigma",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_psigma)( &self, idx, value ); } );

        obj.def( "update_psigma",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_update_psigma)( &self, idx, value ); } );

        obj.def_property_readonly( "psigma_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_psigma_addr)( &self ); } );

        obj.def_property_readonly( "set_psigma_addr",
            []( particle_set_t& self, addr_type const psigma_addr ) {
            ::NS(Particles_set_psigma_addr)( &self, psigma_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "rpp", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_rpp_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move, "access all rpp values as a buffer" );

        obj.def( "rpp", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_rpp)( &self, idx ); } );

        obj.def( "set_rpp",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_rpp)( &self, idx, value ); } );

        obj.def_property_readonly( "rpp_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_rpp_addr)( &self ); } );

        obj.def_property_readonly( "set_rpp_addr",
            []( particle_set_t& self, addr_type const rpp_addr ) {
            ::NS(Particles_set_rpp_addr)( &self, rpp_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "rvv", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_rvv_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move, "access all rvv values as a buffer" );

        obj.def( "rvv", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_rvv)( &self, idx ); } );

        obj.def( "set_rvv",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_rvv)( &self, idx, value ); } );

        obj.def_property_readonly( "rvv_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_rvv_addr)( &self ); } );

        obj.def_property_readonly( "set_rvv_addr",
            []( particle_set_t& self, addr_type const rvv_addr ) {
            ::NS(Particles_set_rvv_addr)( &self, rvv_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "chi", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_chi_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move, "access all chi values as a buffer" );

        obj.def( "chi", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_chi)( &self, idx ); } );

        obj.def( "set_chi",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_chi)( &self, idx, value ); } );

        obj.def_property_readonly( "chi_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_chi_addr)( &self ); } );

        obj.def_property_readonly( "set_chi_addr",
            []( particle_set_t& self, addr_type const chi_addr ) {
            ::NS(Particles_set_chi_addr)( &self, chi_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "charge_ratio",
            []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_charge_ratio_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move,
            "access all charge_ratio values as a buffer" );

        obj.def( "charge_ratio",
            []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_charge_ratio)( &self, idx ); } );

        obj.def( "set_charge_ratio",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_charge_ratio)( &self, idx, value ); } );

        obj.def_property_readonly( "charge_ratio_addr",
            []( particle_set_t const& self ) {
            return ::NS(Particles_charge_ratio_addr)( &self ); } );

        obj.def_property_readonly( "set_charge_ratio_addr",
            []( particle_set_t& self, addr_type const charge_ratio_addr ) {
            ::NS(Particles_set_charge_ratio_addr)(
                &self, charge_ratio_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "s", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_s_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move, "access all s values as a buffer" );

        obj.def( "s", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_s)( &self, idx ); } );

        obj.def( "set_s",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_s)( &self, idx, value ); } );

        obj.def_property_readonly( "s_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_s_addr)( &self ); } );

        obj.def_property_readonly( "set_s_addr",
            []( particle_set_t& self, addr_type const s_addr ) {
            ::NS(Particles_set_s_addr)( &self, s_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "charge0", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_charge0_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move,
            "access all charge0 values as a buffer" );

        obj.def( "charge0",
            []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_charge0)( &self, idx ); } );

        obj.def( "set_charge0",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_charge0)( &self, idx, value ); } );

        obj.def_property_readonly( "charge0_addr",
            []( particle_set_t const& self ) {
            return ::NS(Particles_charge0_addr)( &self ); } );

        obj.def_property_readonly( "set_charge0_addr",
            []( particle_set_t& self, addr_type const charge0_addr ) {
            ::NS(Particles_set_charge0_addr)( &self, charge0_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "mass0", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_mass0_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move,
            "access all mass0 values as a buffer" );

        obj.def( "mass0",
            []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_mass0)( &self, idx ); } );

        obj.def( "set_mass0",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_mass0)( &self, idx, value ); } );

        obj.def_property_readonly( "mass0_addr",
            []( particle_set_t const& self ) {
            return ::NS(Particles_mass0_addr)( &self ); } );

        obj.def_property_readonly( "set_mass0_addr",
            []( particle_set_t& self, addr_type const mass0_addr ) {
            ::NS(Particles_set_mass0_addr)( &self, mass0_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "beta0", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_beta0_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move,
            "access all beta0 values as a buffer" );

        obj.def( "beta0",
            []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_beta0)( &self, idx ); } );

        obj.def( "set_beta0",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_beta0)( &self, idx, value ); } );

        obj.def_property_readonly( "beta0_addr",
            []( particle_set_t const& self ) {
            return ::NS(Particles_beta0_addr)( &self ); } );

        obj.def_property_readonly( "set_beta0_addr",
            []( particle_set_t& self, addr_type const beta0_addr ) {
            ::NS(Particles_set_beta0_addr)( &self, beta0_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "gamma0", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_gamma0_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move,
            "access all gamma0 values as a buffer" );

        obj.def( "gamma0", []( particle_set_t const& self,
            npart_type const idx ) { return ::NS(Particles_gamma0)(
                &self, idx ); } );

        obj.def( "set_gamma0",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_gamma0)( &self, idx, value ); } );

        obj.def_property_readonly( "gamma0_addr",
            []( particle_set_t const& self ) {
            return ::NS(Particles_gamma0_addr)( &self ); } );

        obj.def_property_readonly( "set_gamma0_addr",
            []( particle_set_t& self, addr_type const gamma0_addr ) {
            ::NS(Particles_set_gamma0_addr)( &self, gamma0_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "p0c", []( particle_set_t& self ) -> real_adapter_type {
            return real_adapter_type( ::NS(Particles_p0c_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move, "access all p0c values as a buffer" );

        obj.def( "p0c", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_p0c)( &self, idx ); } );

        obj.def( "set_p0c",
            []( particle_set_t& self, npart_type const idx,
                real_type const value )
            { ::NS(Particles_set_p0c)( &self, idx, value ); } );

        obj.def_property_readonly( "p0c_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_p0c_addr)( &self ); } );

        obj.def_property_readonly( "set_p0c_addr",
            []( particle_set_t& self, addr_type const p0c_addr ) {
            ::NS(Particles_set_p0c_addr)( &self, p0c_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "state", []( particle_set_t& self ) -> index_adapter_type {
            return index_adapter_type( ::NS(Particles_state_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move,
            "access all state values as a buffer" );

        obj.def( "state",
            []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_state)( &self, idx ); } );

        obj.def( "is_active",
            []( particle_set_t const& self, npart_type const idx ) {
                return ::NS(Particles_is_active)( &self, idx ); } );

        obj.def( "is_lost",
            []( particle_set_t const& self, npart_type const idx ) {
                return ::NS(Particles_is_lost)( &self, idx ); } );

        obj.def( "is_not_lost",
            []( particle_set_t const& self, npart_type const idx ) {
                return ::NS(Particles_is_not_lost)( &self, idx ); } );

        obj.def_property_readonly( "num_active",
            []( particle_set_t const& self, npart_type const idx ) {
                return ::NS(Particles_num_active_particles)( &self ); } );

        obj.def_property_readonly( "num_lost",
            []( particle_set_t const& self, npart_type const idx ) {
                return ::NS(Particles_num_active_particles)( &self ); } );

        obj.def( "set_state",
            []( particle_set_t& self, npart_type const idx,
                index_type const value )
            { ::NS(Particles_set_state)( &self, idx, value ); } );

        obj.def( "mark_as_lost",
            []( particle_set_t& self, npart_type const idx )
            { ::NS(Particles_mark_as_lost)( &self, idx ); } );

        obj.def( "keep_active_if_not_lost",
            []( particle_set_t& self, npart_type const idx )
            { ::NS(Particles_keep_active_if_not_lost)( &self, idx ); } );

        obj.def_property_readonly( "state_addr",
            []( particle_set_t const& self ) {
            return ::NS(Particles_state_addr)( &self ); } );

        obj.def_property_readonly( "set_state_addr",
            []( particle_set_t& self, addr_type const state_addr ) {
            ::NS(Particles_set_state_addr)( &self, state_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "at_element",
            []( particle_set_t& self ) -> index_adapter_type {
            return index_adapter_type( ::NS(Particles_at_element_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move,
            "access all at_element values as a buffer" );

        obj.def( "at_element",
            []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_at_element)( &self, idx ); } );

        obj.def( "set_at_element",
            []( particle_set_t& self, npart_type const idx,
                index_type const value )
            { ::NS(Particles_set_at_element)( &self, idx, value ); } );

        obj.def( "increment_at_element",
            []( particle_set_t& self, npart_type const idx ) {
                ::NS(Particles_increment_at_element)( &self, idx ); } );

        obj.def_property_readonly( "at_element_addr",
        []( particle_set_t const& self ) {
            return ::NS(Particles_at_element_addr)( &self ); } );

        obj.def_property_readonly( "set_at_element_addr",
            []( particle_set_t& self, addr_type const at_element_addr ) {
            ::NS(Particles_set_at_element_addr)(
                &self, at_element_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "at_turn", []( particle_set_t& self ) -> index_adapter_type {
            return index_adapter_type( ::NS(Particles_at_turn_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move, "access all at_turn values as a buffer" );

        obj.def( "at_turn", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_at_turn)( &self, idx ); } );

        obj.def( "increment_at_turn",
            []( particle_set_t& self, npart_type const idx ) {
                ::NS(Particles_increment_at_turn)( &self, idx ); } );

        obj.def( "finish_turn",
            []( particle_set_t& self, npart_type const idx,
                index_type const start_at_element ) {
                ::NS(Particles_finish_turn)( &self, idx, start_at_element ); },
            "increment turn and reset the at_element indicator to start_at_element",
            py::arg( "idx" ), py::arg( "start_at_element" ) =
                ::NS(Particles_default_at_element)() );

        obj.def( "set_at_turn",
            []( particle_set_t& self, npart_type const idx,
                index_type const value )
            { ::NS(Particles_set_at_turn)( &self, idx, value ); } );

        obj.def_property_readonly( "at_turn_addr",
            []( particle_set_t const& self ) {
            return ::NS(Particles_at_turn_addr)( &self ); } );

        obj.def_property_readonly( "set_at_turn_addr",
            []( particle_set_t& self, addr_type const at_turn_addr ) {
            ::NS(Particles_set_at_turn_addr)( &self, at_turn_addr ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "id", []( particle_set_t& self ) -> index_adapter_type {
            return index_adapter_type( ::NS(Particles_id_addr)( &self ),
                ::NS(Particles_max_num_particles)( &self ) ); },
            py::return_value_policy::move, "access all id values as a buffer" );

        obj.def( "id", []( particle_set_t const& self, npart_type const idx ) {
            return ::NS(Particles_id)( &self, idx ); } );

        obj.def( "set_id",
            []( particle_set_t& self, npart_type const idx,
                index_type const value )
            { ::NS(Particles_set_id)( &self, idx, value ); } );

        obj.def_property_readonly( "id_addr", []( particle_set_t const& self ) {
            return ::NS(Particles_id_addr)( &self ); } );

        obj.def_property_readonly( "set_id_addr",
            []( particle_set_t& self, addr_type const id_addr ) {
            ::NS(Particles_set_id_addr)( &self, id_addr ); } );

        /* ----------------------------------------------------------------- */

        obj.def( "mass_ratio",
        []( particle_set_t const& pset, npart_type const idx ) {
            return ::NS(Particles_mass_ratio)( &pset, idx ); } );

        obj.def( "mass", []( particle_set_t const& pset, npart_type const idx )
        { return ::NS(Particles_mass)( &pset, idx ); } );

        obj.def( "charge", []( particle_set_t const& pset, npart_type const idx )
        { return ::NS(Particles_charge)( &pset, idx ); } );

        obj.def( "tau", []( particle_set_t const& pset, npart_type const idx )
        { return ::NS(Particles_tau)( &pset, idx ); } );

        obj.def( "update_tau",
            []( particle_set_t& pset, npart_type const idx,
                real_type const tau_value ) {
                ::NS(Particles_update_tau)( &pset, idx, tau_value ); } );

        obj.def( "ptau", []( particle_set_t const& pset, npart_type const idx )
        { return ::NS(Particles_ptau)( &pset, idx ); } );

        obj.def( "update_ptau",
            []( particle_set_t& pset, npart_type const idx,
                real_type const ptau_value ) {
                ::NS(Particles_update_ptau)( &pset, idx, ptau_value ); } );

        obj.def( "sigma", []( particle_set_t const& pset, npart_type const idx )
        { return ::NS(Particles_sigma)( &pset, idx ); } );

        obj.def( "update_sigma",
            []( particle_set_t& pset, npart_type const idx,
                real_type const sigma_value ) {
                ::NS(Particles_update_sigma)( &pset, idx, sigma_value ); } );

        obj.def( "energy0",
            []( particle_set_t const& pset, npart_type const idx ) {
                ::NS(Particles_energy0)( &pset, idx ); } );

        obj.def( "energy",
            []( particle_set_t const& pset, npart_type const idx ) {
                ::NS(Particles_energy)( &pset, idx ); } );

        obj.def( "update_energy",
            []( particle_set_t& pset, npart_type const idx,
                real_type const energy_value ) {
                ::NS(Particles_update_energy)( &pset, idx, energy_value ); } );

        obj.def( "add_to_energy",
            []( particle_set_t& pset, npart_type const idx,
                real_type const d_energy ) {
                ::NS(Particles_add_to_energy)( &pset, idx, d_energy ); } );

        /* ----------------------------------------------------------------- */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(Particles_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(Particles_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(Particles_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(Particles_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( particle_set_t const& self, size_type const slot_size ) {
            return ::NS(Particles_cobj_required_num_bytes)(
                &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "from_particle",
            []( particle_set_t& self, npart_type const idx,
                particle_t const& p ) {
                return ::NS(Particles_from_single_particle)( &self, idx, &p ); },
            "Copy the contents of a single particle to an entry in the calling "
            "particles instance", py::arg( "idx" ), py::arg( "p" ) );

        obj.def( "to_particles",
            []( particle_set_t const& self, npart_type const idx,
                particle_t& p ) {
                return ::NS(Particles_to_single_particle)( &self, idx, &p ); },
            "Copy the contents of the calling single particle to an entry in "
            "the particle-set", py::arg( "idx" ), py::arg( "p" ) );

        obj.def( "copy_single",
            []( particle_set_t& dest, npart_type const dest_idx,
                particle_set_t const& src, npart_type const src_idx ) {
            return ::NS(Particles_copy_single)(
                &dest, dest_idx, &src, src_idx ); },
            "Copy single entry of a particle set to a single entry in the "
            "calling particle set",
            py::arg( "idx" ), py::arg( "source" ), py::arg( "source_idx" ) );

        obj.def( "copy_range",
            []( particle_set_t& dest, npart_type const dest_start_idx,
                particle_set_t const& src,
                npart_type const src_start_idx, npart_type const src_end_idx,
                npart_type const stride ) {
            return ::NS(Particles_copy_range)( &dest, &src,
                src_start_idx, src_end_idx, dest_start_idx, stride ); },
            "Copy a range of entries of a particle set to a the "
            "calling particle set starting with a given dest index. "
            "The stride is the same in both instances",
            py::arg( "idx" ), py::arg( "source" ),
            py::arg( "source_start_idx" ), py::arg( "source_end_idx" ),
            py::arg( "stride" ) = size_type{ 1 } );

        obj.def( "copy",
            []( particle_set_t& dest, particle_set_t const& src ) {
            return ::NS(Particles_copy)( &dest, &src ); },
            "Copy all entries of a particle set to the calling instance",
            py::arg( "source" ) );
    }

    void InitHelper_common_particles_particles_addr( stpy::InitHelper& root ) {
        using particle_set_t    = ::NS(Particles);
        using paddr_type        = ::NS(ParticlesAddr);
        using real_type         = ::NS(particle_real_type);
        using index_type        = ::NS(particle_index_type);
        using size_type         = ::NS(cobj_size_type);
        using npart_type        = ::NS(particles_num_type);
        using addr_type         = ::NS(address_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.particles_addr_type;


        obj.def( py::init( []( cbuffer_view_type& view,
            npart_type const max_num_particles,
            addr_type  const charge0_addr, addr_type const mass0_addr,
            addr_type  const beta0_addr,   addr_type const gamma0_addr,
            addr_type  const p0c_addr,
            addr_type  const s_addr,       addr_type const x_addr,
            addr_type  const y_addr,       addr_type const px_addr,
            addr_type  const py_addr,      addr_type const zeta_addr,
            addr_type  const psigma_addr,  addr_type const delta_addr,
            addr_type  const rpp_addr,     addr_type const rvv_addr,
            addr_type  const chi_addr,     addr_type const charge_ratio_addr,
            addr_type  const id_addr,      addr_type const at_element_addr,
            addr_type  const at_turn_addr, addr_type const state_addr )
        {
            return std::unique_ptr< paddr_type, py::nodelete >(
                ::NS(ParticlesAddr_cbuffer_add)( view.as_c_api(),
                    max_num_particles, charge0_addr, mass0_addr, beta0_addr,
                        gamma0_addr, p0c_addr, s_addr, x_addr, y_addr, px_addr,
                            py_addr, zeta_addr, psigma_addr, delta_addr,
                                rpp_addr, rvv_addr, chi_addr, charge_ratio_addr,
                                    id_addr, at_element_addr, at_turn_addr,
                                        state_addr ) );
        } ),
        "default constructor, not stored on a CBufferView!",
        py::arg( "cbuffer" ),
        py::arg( "max_num_particles" ) = npart_type{ 0 },
        py::arg( "charge0_addr" )      = st::COBJECTS_NULL_ADDRESS,
        py::arg( "mass0_addr" )        = st::COBJECTS_NULL_ADDRESS,
        py::arg( "beta0_addr" )        = st::COBJECTS_NULL_ADDRESS,
        py::arg( "gamma0_addr" )       = st::COBJECTS_NULL_ADDRESS,
        py::arg( "p0c_addr" )          = st::COBJECTS_NULL_ADDRESS,
        py::arg( "s_addr" )            = st::COBJECTS_NULL_ADDRESS,
        py::arg( "x_addr" )            = st::COBJECTS_NULL_ADDRESS,
        py::arg( "y_addr" )            = st::COBJECTS_NULL_ADDRESS,
        py::arg( "px_addr" )           = st::COBJECTS_NULL_ADDRESS,
        py::arg( "py_addr" )           = st::COBJECTS_NULL_ADDRESS,
        py::arg( "zeta_addr" )         = st::COBJECTS_NULL_ADDRESS,
        py::arg( "psigma_addr" )       = st::COBJECTS_NULL_ADDRESS,
        py::arg( "delta_addr" )        = st::COBJECTS_NULL_ADDRESS,
        py::arg( "rpp_addr" )          = st::COBJECTS_NULL_ADDRESS,
        py::arg( "rvv_addr" )          = st::COBJECTS_NULL_ADDRESS,
        py::arg( "chi_addr" )          = st::COBJECTS_NULL_ADDRESS,
        py::arg( "charge_ratio_addr" ) = st::COBJECTS_NULL_ADDRESS,
        py::arg( "id_addr" )           = st::COBJECTS_NULL_ADDRESS,
        py::arg( "at_element_addr" )   = st::COBJECTS_NULL_ADDRESS,
        py::arg( "at_turn_addr" )      = st::COBJECTS_NULL_ADDRESS,
        py::arg( "state_addr" )        = st::COBJECTS_NULL_ADDRESS );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& view, size_type const pos_in_buffer )
                -> SIXTRL_PARTICLES_ADDR_ARGPTR_DEC paddr_type* {
                return ::NS(ParticlesAddr_from_cbuffer)(
                    view.as_c_api(), pos_in_buffer ); },
            py::return_value_policy::reference,
            "get instance of CParticlesAddr from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW",
            []( cbuffer_view_type& view )
                -> SIXTRL_PARTICLES_ADDR_ARGPTR_DEC paddr_type*
            { return ::NS(ParticlesAddr_cbuffer_new)( view.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CParticlesAddr instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD", []( cbuffer_view_type& view,
            npart_type const max_num_particles,
            addr_type  const charge0_addr, addr_type const mass0_addr,
            addr_type  const beta0_addr,   addr_type const gamma0_addr,
            addr_type  const p0c_addr,
            addr_type  const s_addr,       addr_type const x_addr,
            addr_type  const y_addr,       addr_type const px_addr,
            addr_type  const py_addr,      addr_type const zeta_addr,
            addr_type  const psigma_addr,  addr_type const delta_addr,
            addr_type  const rpp_addr,     addr_type const rvv_addr,
            addr_type  const chi_addr,     addr_type const charge_ratio_addr,
            addr_type  const id_addr,      addr_type const at_element_addr,
            addr_type  const at_turn_addr, addr_type const state_addr ) ->
                SIXTRL_PARTICLES_ADDR_ARGPTR_DEC paddr_type*
            {
                return ::NS(ParticlesAddr_cbuffer_add)( view.as_c_api(),
                    max_num_particles, charge0_addr, mass0_addr, beta0_addr,
                        gamma0_addr, p0c_addr, s_addr, x_addr, y_addr, px_addr,
                            py_addr, zeta_addr, psigma_addr, delta_addr,
                                rpp_addr, rvv_addr, chi_addr, charge_ratio_addr,
                                    id_addr, at_element_addr, at_turn_addr,
                                        state_addr );
            },
            py::return_value_policy::reference,
            "append a fully parameterised CParticlesAddr instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "max_num_particles" ) = npart_type{ 0 },
            py::arg( "charge0_addr" )      = st::COBJECTS_NULL_ADDRESS,
            py::arg( "mass0_addr" )        = st::COBJECTS_NULL_ADDRESS,
            py::arg( "beta0_addr" )        = st::COBJECTS_NULL_ADDRESS,
            py::arg( "gamma0_addr" )       = st::COBJECTS_NULL_ADDRESS,
            py::arg( "p0c_addr" )          = st::COBJECTS_NULL_ADDRESS,
            py::arg( "s_addr" )            = st::COBJECTS_NULL_ADDRESS,
            py::arg( "x_addr" )            = st::COBJECTS_NULL_ADDRESS,
            py::arg( "y_addr" )            = st::COBJECTS_NULL_ADDRESS,
            py::arg( "px_addr" )           = st::COBJECTS_NULL_ADDRESS,
            py::arg( "py_addr" )           = st::COBJECTS_NULL_ADDRESS,
            py::arg( "zeta_addr" )         = st::COBJECTS_NULL_ADDRESS,
            py::arg( "psigma_addr" )       = st::COBJECTS_NULL_ADDRESS,
            py::arg( "delta_addr" )        = st::COBJECTS_NULL_ADDRESS,
            py::arg( "rpp_addr" )          = st::COBJECTS_NULL_ADDRESS,
            py::arg( "rvv_addr" )          = st::COBJECTS_NULL_ADDRESS,
            py::arg( "chi_addr" )          = st::COBJECTS_NULL_ADDRESS,
            py::arg( "charge_ratio_addr" ) = st::COBJECTS_NULL_ADDRESS,
            py::arg( "id_addr" )           = st::COBJECTS_NULL_ADDRESS,
            py::arg( "at_element_addr" )   = st::COBJECTS_NULL_ADDRESS,
            py::arg( "at_turn_addr" )      = st::COBJECTS_NULL_ADDRESS,
            py::arg( "state_addr" )        = st::COBJECTS_NULL_ADDRESS );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& view, paddr_type const& paddr ) ->
                SIXTRL_PARTICLES_ADDR_ARGPTR_DEC paddr_type*
            {
                return ::NS(ParticlesAddr_cbuffer_add_copy)(
                    view.as_c_api(), &paddr );
            },
            py::return_value_policy::reference,
            "append a copy of the CParticlesAddr instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( paddr_type const& paddr, cbuffer_view_type& view ) ->
                SIXTRL_PARTICLES_ADDR_ARGPTR_DEC paddr_type*
            {
                return ::NS(ParticlesAddr_cbuffer_add_copy)(
                    view.as_c_api(), &paddr );
            },
            py::return_value_policy::reference,
            "append a copy of the calling CParticlesAddr instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* ----------------------------------------------------------------- */

        obj.def_property( "max_num_particles",
            []( paddr_type const& paddr ) {
                return paddr.max_num_particles; },
            []( paddr_type& paddr, npart_type const max_num_particles ) {
                paddr.max_num_particles = max_num_particles; } );

        obj.def_property( "x_addr",
            []( paddr_type const& paddr ) { return paddr.x_addr; },
            []( paddr_type& paddr, addr_type const x_addr ) {
                paddr.x_addr = x_addr; } );

        obj.def_property( "y_addr",
            []( paddr_type const& paddr ) { return paddr.y_addr; },
            []( paddr_type& paddr, addr_type const y_addr ) {
                paddr.y_addr = y_addr; } );

        obj.def_property( "px_addr",
            []( paddr_type const& paddr ) { return paddr.px_addr; },
            []( paddr_type& paddr, addr_type const px_addr ) {
                paddr.px_addr = px_addr; } );

        obj.def_property( "py_addr",
            []( paddr_type const& paddr ) { return paddr.py_addr; },
            []( paddr_type& paddr, addr_type const py_addr ) {
                paddr.py_addr = py_addr; } );

        obj.def_property( "zeta_addr",
            []( paddr_type const& paddr ) { return paddr.zeta_addr; },
            []( paddr_type& paddr, addr_type const zeta_addr ) {
                paddr.zeta_addr = zeta_addr; } );

        obj.def_property( "delta_addr",
            []( paddr_type const& paddr ) { return paddr.delta_addr; },
            []( paddr_type& paddr, addr_type const delta_addr ) {
                paddr.delta_addr = delta_addr; } );

        obj.def_property( "psigma_addr",
            []( paddr_type const& paddr ) { return paddr.psigma_addr; },
            []( paddr_type& paddr, addr_type const psigma_addr ) {
                paddr.psigma_addr = psigma_addr; } );

        obj.def_property( "rpp_addr",
            []( paddr_type const& paddr ) { return paddr.rpp_addr; },
            []( paddr_type& paddr, addr_type const rpp_addr ) {
                paddr.rpp_addr = rpp_addr; } );

        obj.def_property( "rvv_addr",
            []( paddr_type const& paddr ) { return paddr.rvv_addr; },
            []( paddr_type& paddr, addr_type const rvv_addr ) {
                paddr.rvv_addr = rvv_addr; } );

        obj.def_property( "chi_addr",
            []( paddr_type const& paddr ) { return paddr.chi_addr; },
            []( paddr_type& paddr, addr_type const chi_addr ) {
                paddr.chi_addr = chi_addr; } );

        obj.def_property( "charge_ratio_addr",
            []( paddr_type const& paddr ) { return paddr.charge_ratio_addr; },
            []( paddr_type& paddr, addr_type const charge_ratio_addr ) {
                paddr.charge_ratio_addr = charge_ratio_addr; } );

        obj.def_property( "state_addr",
            []( paddr_type const& paddr ) { return paddr.state_addr; },
            []( paddr_type& paddr, addr_type const state_addr ) {
                paddr.state_addr = state_addr; } );

        obj.def_property( "at_element_addr",
            []( paddr_type const& paddr ) { return paddr.at_element_addr; },
            []( paddr_type& paddr, addr_type const at_element_addr ) {
                paddr.at_element_addr = at_element_addr; } );

        obj.def_property( "at_turn_addr",
            []( paddr_type const& paddr ) { return paddr.at_turn_addr; },
            []( paddr_type& paddr, addr_type const at_turn_addr ) {
                paddr.at_turn_addr = at_turn_addr; } );

        obj.def_property( "id_addr",
            []( paddr_type const& paddr ) { return paddr.id_addr; },
            []( paddr_type& paddr, addr_type const id_addr ) {
                paddr.id_addr = id_addr; } );

        /* ----------------------------------------------------------------- */

        obj.def( "from_particles",
            []( paddr_type& paddr, particle_set_t const& pset )
            {
                ::NS(ParticlesAddr_assign_from_particles)( &paddr, &pset );
            },
            "assigns addresses to calling instance from a CParticles instance"
        );

        /* ----------------------------------------------------------------- */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) {
                return ::NS(ParticlesAddr_cobj_type_id)(); } );
        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) {
                return ::NS(ParticlesAddr_cobj_num_dataptrs)(); } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(ParticlesAddr_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(ParticlesAddr_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( paddr_type const& self, size_type const slot_size ) {
            return ::NS(ParticlesAddr_cobj_required_num_bytes)(
                &self, slot_size ); } );
    }

    void InitHelper_common_particles_demotrack( stpy::InitHelper& root )
    {
        using dt_particle_type  = ::NS(DemotrackParticle);
        using particle_type     = ::NS(Particle);
        using particle_set_type = ::NS(Particles);
        using npart_type        = ::NS(particles_num_type);
        using size_type         = ::NS(size_type);
        using status_type       = ::NS(status_type);
        using uint_type         = SIXTRL_UINT64_TYPE;
        using real_type         = ::NS(particle_real_type);
//         using cbuffer_view_type = st::CBufferView;

        using py_array_dt_particle_t = py::array_t<
            dt_particle_type, py::array::c_style | py::array::forcecast >;

        #if defined( SIXTRL_DEMOTRACK_ENABLED ) && \
                   ( SIXTRL_DEMOTRACK_ENABLED == 1 )

        auto& obj = root.demotrack_particle_type;

        obj.def( py::init( [](
            real_type  const x,       real_type  const px,
            real_type  const y,       real_type  const py,
            real_type  const zeta,    real_type  const delta,
            real_type  const rpp,     real_type  const rvv,
            real_type  const psigma,  real_type  const chi,
            real_type  const charge_ratio,
            real_type  const charge0, real_type  const mass0,
            real_type  const beta0,   real_type  const gamma0,
            real_type  const p0c,
            uint_type const state,    uint_type const at_element,
            ::NS(particle_index_type) const at_turn, uint_type const id ){
            return std::unique_ptr< dt_particle_type >( new dt_particle_type{
                x, px, y, py, zeta, delta, rpp, rvv, psigma, chi, charge_ratio,
                    charge0, mass0, beta0, gamma0, p0c, state, at_element,
                        at_turn, id } ); } ),
            "default constructor",
            py::arg( "x" ) = ::NS(Particle_default_x)(),
            py::arg( "px" ) = ::NS(Particle_default_px)(),
            py::arg( "y" ) = ::NS(Particle_default_y)(),
            py::arg( "py" ) = ::NS(Particle_default_py)(),
            py::arg( "zeta" ) = ::NS(Particle_default_zeta)(),
            py::arg( "delta" ) = ::NS(Particle_default_delta)(),
            py::arg( "rpp" ) = ::NS(Particle_default_rpp)(),
            py::arg( "rvv" ) = ::NS(Particle_default_rvv)(),
            py::arg( "psigma" ) = ::NS(Particle_default_psigma)(),
            py::arg( "chi" ) = ::NS(Particle_default_chi)(),
            py::arg( "charge_ratio" ) = ::NS(Particle_default_charge_ratio)(),
            py::arg( "charge0" ) = ::NS(Particle_default_charge0)(),
            py::arg( "mass0" ) = ::NS(Particle_default_mass0)(),
            py::arg( "beta0" ) = ::NS(Particle_default_beta0)(),
            py::arg( "gamma0" ) = ::NS(Particle_default_gamma0)(),
            py::arg( "p0c" ) = ::NS(Particle_default_p0c)(),
            py::arg( "state" ) = uint_type{ 1 },
            py::arg( "at_element" ) = uint_type{ 0 },
            py::arg( "at_turn" ) = ::NS(Particle_default_at_turn)(),
            py::arg( "id" ) = uint_type{ 0 } );

        obj.def_static( "CREATE_ARRAY",
            []( size_type const nn, bool clear_data ) -> py_array_dt_particle_t
            {
                if( nn == st::size_type{ 0 } )
                    throw std::runtime_error( "num_particles == 0" );

                std::vector< dt_particle_type >* ptr_temp_buffer =
                    new std::vector< dt_particle_type >( nn, dt_particle_type{} );

                SIXTRL_ASSERT( ptr_temp_buffer != nullptr );

                if( clear_data )
                {
                    st::status_type status = st::STATUS_SUCCESS;

                    for( auto& p : *ptr_temp_buffer )
                    {
                        status |= ::NS(Demotrack_particle_clear)( &p );
                    }

                    if( status != st::STATUS_SUCCESS )
                    {
                        throw std::runtime_error(
                            "error while clearing allocated data" );
                    }
                }

                py::capsule do_delete_when_no_longer_needed(
                    ptr_temp_buffer, []( void* ptr )
                    {
                        auto ptr_to_del = reinterpret_cast<
                            std::vector< dt_particle_type >* >( ptr );
                        delete ptr_to_del;
                    } );

                return py_array_dt_particle_t( nn, ptr_temp_buffer->data(),
                        do_delete_when_no_longer_needed );

            }, py::arg( "num_particles" ), py::arg( "clear_data" ) = false );

        obj.def( "to_cobjects",
            []( dt_particle_type const& self, particle_type& other )
                -> status_type
            { return ::NS(Demotrack_particle_to_single_particle)(
                &self, &other ); },
            "Copy data to cobjects single-particle instance" );

        obj.def( "to_cobjects",
            []( dt_particle_type const& self, particle_set_type& other,
                npart_type const idx ) -> status_type
            { return ::NS(Demotrack_particle_to_particles)(
                &self, &other, idx ); },
            "Copy data to cobjects particles instance at position index" );

        obj.def( "from_cobjects",
            []( dt_particle_type& self, particle_type const& other )
                -> status_type
            { return ::NS(Demotrack_particle_from_single_particle)(
                &self, &other ); },
            "Copy data to cobjects single-particle instance" );

        obj.def( "from_cobjects",
            []( dt_particle_type& self, particle_set_type const& other,
                npart_type const idx ) -> status_type
            { return ::NS(Demotrack_particle_from_particles)(
                &self, &other, idx ); },
            "Copy data to cobjects particles instance at position index" );

        obj.def( "from_array",
            []( dt_particle_type& self,
                tl::optional< py_array_dt_particle_t > in_array,
                npart_type const pos_in_buffer ) -> status_type {

                if( !in_array.has_value() ) return st::STATUS_GENERAL_FAILURE;
                py::buffer_info info = in_array.value().request();
                if( info.ndim != py::ssize_t{ 1 } )
                    throw std::runtime_error( "ndim != 1" );
                if( info.shape[ 0 ] <= pos_in_buffer )
                    throw std::runtime_error( "shape[ 0 ] <= pos_in_buffer" );

                auto ptr_obj = reinterpret_cast< SIXTRL_PARTICLE_ARGPTR_DEC
                    dt_particle_type const* >( reinterpret_cast< uintptr_t >(
                        info.ptr ) );

                if( ptr_obj == nullptr )
                    throw std::runtime_error( "ptr_obj == nullptr" );

                self = ptr_obj[ pos_in_buffer ];
                return st::STATUS_SUCCESS; },
            "assign contents of item stored at index in the buffer to the "
            "calling instance" );

        obj.def( "to_array",
            []( dt_particle_type const& self,
                tl::optional< py_array_dt_particle_t > in_array,
                npart_type const pos_in_buffer ) -> status_type {

                if( !in_array.has_value() ) return st::STATUS_GENERAL_FAILURE;
                py::buffer_info info = in_array.value().request();
                if( info.ndim != py::ssize_t{ 1 } )
                    throw std::runtime_error( "ndim != 1" );
                if( info.shape[ 0 ] <= pos_in_buffer )
                    throw std::runtime_error( "shape[ 0 ] <= pos_in_buffer" );

                auto ptr_obj = reinterpret_cast< SIXTRL_PARTICLE_ARGPTR_DEC
                    dt_particle_type* >( reinterpret_cast< uintptr_t >(
                        info.ptr ) );

                if( ptr_obj == nullptr )
                    throw std::runtime_error( "ptr_obj == nullptr" );

                ptr_obj[ pos_in_buffer ] = self;
                return st::STATUS_SUCCESS; },
            "assign contents of calling instance to item stored at index in "
            "the buffer" );

        obj.def_property( "x",
            []( dt_particle_type const& self ) -> real_type {
                return self.x; },
            []( dt_particle_type& self, real_type const x_value ) {
                self.x = x_value; } );

        obj.def_property( "px",
            []( dt_particle_type const& self ) -> real_type {
                return self.px; },
            []( dt_particle_type& self, real_type const px_value ) {
                self.px = px_value; } );

        obj.def_property( "y",
            []( dt_particle_type const& self ) -> real_type {
                return self.y; },
            []( dt_particle_type& self, real_type const y_value ) {
                self.y = y_value; } );

        obj.def_property( "py",
            []( dt_particle_type const& self ) -> real_type {
                return self.py; },
            []( dt_particle_type& self, real_type const py_value ) {
                self.py = py_value; } );

        obj.def_property( "zeta",
            []( dt_particle_type const& self ) -> real_type {
                return self.zeta; },
            []( dt_particle_type& self, real_type const zeta_value ) {
                self.zeta = zeta_value; } );

        obj.def_property( "delta",
            []( dt_particle_type const& self ) -> real_type {
                return self.delta; },
            []( dt_particle_type& self, real_type const delta_value ) {
                self.delta = delta_value; } );

        obj.def_property( "rpp",
            []( dt_particle_type const& self ) -> real_type {
                return self.rpp; },
            []( dt_particle_type& self, real_type const rpp_value ) {
                self.rpp = rpp_value; } );

        obj.def_property( "rvv",
            []( dt_particle_type const& self ) -> real_type {
                return self.rvv; },
            []( dt_particle_type& self, real_type const rvv_value ) {
                self.rvv = rvv_value; } );

        obj.def_property( "psigma",
            []( dt_particle_type const& self ) -> real_type {
                return self.psigma; },
            []( dt_particle_type& self, real_type const psigma_value ) {
                self.psigma = psigma_value; } );

        obj.def_property( "chi",
            []( dt_particle_type const& self ) -> real_type {
                return self.chi; },
            []( dt_particle_type& self, real_type const chi_value ) {
                self.chi = chi_value; } );

        obj.def_property( "charge_ratio",
            []( dt_particle_type const& self ) -> real_type {
                return self.charge_ratio; },
            []( dt_particle_type& self, real_type const charge_ratio_value ) {
                self.charge_ratio = charge_ratio_value; } );

        obj.def_property( "charge0",
            []( dt_particle_type const& self ) -> real_type {
                return self.charge0; },
            []( dt_particle_type& self, real_type const charge0_value ) {
                self.charge0 = charge0_value; } );

        obj.def_property( "mass0",
            []( dt_particle_type const& self ) -> real_type {
                return self.mass0; },
            []( dt_particle_type& self, real_type const mass0_value ) {
                self.mass0 = mass0_value; } );

        obj.def_property( "beta0",
            []( dt_particle_type const& self ) -> real_type {
                return self.beta0; },
            []( dt_particle_type& self, real_type const beta0_value ) {
                self.beta0 = beta0_value; } );

        obj.def_property( "gamma0",
            []( dt_particle_type const& self ) -> real_type {
                return self.gamma0; },
            []( dt_particle_type& self, real_type const gamma0_value ) {
                self.gamma0 = gamma0_value; } );

        obj.def_property( "p0c",
            []( dt_particle_type const& self ) -> real_type {
                return self.p0c; },
            []( dt_particle_type& self, real_type const p0c_value ) {
                self.p0c = p0c_value; } );

        obj.def_property( "state",
            []( dt_particle_type const& self ) -> uint_type {
                return self.state; },
            []( dt_particle_type& self, uint_type const state_value ) {
                self.state = state_value; } );

        obj.def_property( "at_element",
            []( dt_particle_type const& self ) -> uint_type {
                return self.at_element; },
            []( dt_particle_type& self, uint_type const at_element_value ) {
                self.at_element = at_element_value; } );

        obj.def_property( "at_turn",
            []( dt_particle_type const& self ) -> ::NS(particle_index_type) {
                return self.at_turn; },
            []( dt_particle_type& self,
                ::NS(particle_index_type) const at_turn_value ) {
                self.at_turn = at_turn_value; } );

        obj.def_property( "id",
            []( dt_particle_type const& self ) -> uint_type {
                return self.id; },
            []( dt_particle_type& self, uint_type const id_value ) {
                self.id = id_value; } );

        obj.def( "clear", []( dt_particle_type& self ) -> status_type
            { return ::NS(Demotrack_particle_clear)( &self ); } );

        #endif /* defined( SIXTRL_DEMOTRACK_ENABLED ) */
    }

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */
