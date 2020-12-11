#if defined( __cplusplus ) && !defined( _GPUCODE )
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/particles/particle_unit.hpp"
#include "sixtracklib/multiprec/particles/particle_set.hpp"
#include "sixtracklib/common/particle.hpp"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/particles/python_bindings.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
    }

    void setup_multiprec_particles_python_bindings(
        py::module& SIXTRL_RESTRICT_REF m,
        py::class_< st::CBufferView >* SIXTRL_RESTRICT cbuffer_view_obj,
        py::class_< st::CBuffer >* SIXTRL_RESTRICT cbuffer_obj )
    {
        typedef st::ParticleTraits< st::Particle >::real_t  st_real_t;
        typedef st::ParticleTraits< st::Particle >::index_t st_index_t;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* SinglePrecParticle: */

        py::class_< st::SinglePrecParticle > single_prec_particle_obj(
                    m, "SinglePrecParticle" );

        py::class_< st::SinglePrecParticleSet > single_prec_particle_set_obj(
                    m, "SinglePrecParticleSet" );

        st::python::init_particle_unit_particle_set_bindings_for_types<
            st::SinglePrecParticle, st::SinglePrecParticleSet >(
                m, single_prec_particle_obj, single_prec_particle_set_obj,
                    cbuffer_view_obj, cbuffer_obj );

        st::python::init_particle_unit_additional_real_api<
            st::SinglePrecParticle, st_real_t >( m, single_prec_particle_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* DoublePrecParticle: */

        py::class_< st::DoublePrecParticle > double_prec_particle_obj(
                    m, "DoublePrecParticle" );

        py::class_< st::DoublePrecParticleSet > double_prec_particle_set_obj(
                    m, "DoublePrecParticleSet" );

        st::python::init_particle_unit_particle_set_bindings_for_types<
            st::DoublePrecParticle, st::DoublePrecParticleSet >(
                m, double_prec_particle_obj, double_prec_particle_set_obj,
                    cbuffer_view_obj, cbuffer_obj );

        st::python::init_particle_unit_additional_real_api<
            st::DoublePrecParticle, st_real_t >( m, double_prec_particle_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* QuadPrecParticle: */

        py::class_< st::QuadPrecParticle > quad_prec_particle_obj(
                m, "QuadPrecParticle" );

        py::class_< st::QuadPrecParticleSet > quad_prec_particle_set_obj(
                m, "QuadPrecParticleSet" );

        st::python::init_particle_unit_particle_set_bindings_for_types<
            st::QuadPrecParticle, st::QuadPrecParticleSet >(
                m, quad_prec_particle_obj, quad_prec_particle_set_obj,
                    cbuffer_view_obj, cbuffer_obj );

        st::python::init_particle_unit_additional_real_api<
            st::QuadPrecParticle, st_real_t >( m, quad_prec_particle_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* OctPrecParticle: */

        py::class_< st::OctPrecParticle > oct_prec_particle_obj(
                m, "OctPrecParticle" );

        py::class_< st::OctPrecParticleSet > oct_prec_particle_set_obj(
                m, "OctPrecParticleSet" );

        st::python::init_particle_unit_particle_set_bindings_for_types<
            st::OctPrecParticle, st::OctPrecParticleSet >(
                m, oct_prec_particle_obj, oct_prec_particle_set_obj,
                    cbuffer_view_obj, cbuffer_obj );

        st::python::init_particle_unit_additional_real_api<
            st::OctPrecParticle, st_real_t >( m, oct_prec_particle_obj );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
