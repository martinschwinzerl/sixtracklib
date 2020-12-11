#if defined( __cplusplus ) && !defined( _GPUCODE )

#include "sixtracklib/common/particles/python_bindings.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/internal/compiler_compability.h"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
    }

    void setup_common_particles_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< st::CBufferView >* SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< st::CBuffer >* SIXTRL_RESTRICT cbuffer_obj )
    {
        pybind11::class_< st::Particle > particle_obj( m, "Particle" );
        pybind11::class_< st::ParticleSet > particle_set_obj( m, "ParticleSet" );

        st::python::init_particle_unit_particle_set_bindings_for_types<
            st::Particle, st::ParticleSet >( m, particle_obj, particle_set_obj,
                cbuffer_view_obj, cbuffer_obj );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
