#if defined( __cplusplus ) && !defined( _GPUCODE )

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <memory>
#include <string>
#include <sstream>
#include <tuple>
#include <stdexcept>

#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/beam_elements/cavity.hpp"
#include "sixtracklib/common/beam_elements/cavity.hpp"
#include "sixtracklib/common/beam_elements/cavity/python_bindings.hpp"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/internal/compiler_attributes.h"
#include "sixtracklib/common/internal/type_store_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
    }

    void setup_multiprec_beam_elements_cavity_python_bindings(
        py::module& SIXTRL_RESTRICT_REF m,
        py::class_< st::CBufferView >* SIXTRL_RESTRICT cbuffer_view_obj,
        py::class_< st::CBuffer >* SIXTRL_RESTRICT cbuffer_obj )
    {
        typedef st::ParticleTraits< st::Cavity >::real_t  st_real_t;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* SinglePrecCavity: */

        py::class_< st::SinglePrecCavity > single_prec_cavity_obj(
            m, "SinglePrecCavity" );

        st::python::setup_be_cavity_bindings_for_types<
            st::SinglePrecCavity >( m, single_prec_cavity_obj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_cavity_real_api_bindings<
            st::SinglePrecCavity, st_real_t >( m, single_prec_cavity_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* DoublePrecCavity: */

        py::class_< st::DoublePrecCavity > double_prec_cavity_obj(
            m, "DoublePrecCavity" );

        st::python::setup_be_cavity_bindings_for_types<
            st::DoublePrecCavity >( m, double_prec_cavity_obj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_cavity_real_api_bindings<
            st::DoublePrecCavity, st_real_t >( m, double_prec_cavity_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* QuadPrecCavity: */

        py::class_< st::QuadPrecCavity > quad_prec_cavity_obj(
            m, "QuadPrecCavity" );

        st::python::setup_be_cavity_bindings_for_types<
            st::QuadPrecCavity >( m, quad_prec_cavity_obj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_cavity_real_api_bindings<
            st::QuadPrecCavity, st_real_t >( m, quad_prec_cavity_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* OctPrecCavity: */

        py::class_< st::OctPrecCavity > oct_prec_cavity_obj(
            m, "OctPrecCavity" );

        st::python::setup_be_cavity_bindings_for_types<
            st::OctPrecCavity >( m, oct_prec_cavity_obj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_cavity_real_api_bindings<
            st::OctPrecCavity, st_real_t >( m, oct_prec_cavity_obj );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
