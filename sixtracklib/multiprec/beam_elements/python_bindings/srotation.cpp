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
#include "sixtracklib/multiprec/beam_elements/srotation.hpp"
#include "sixtracklib/common/beam_elements/srotation.hpp"
#include "sixtracklib/common/beam_elements/srotation/python_bindings.hpp"
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

    void setup_multiprec_beam_elements_srotation_python_bindings(
        py::module& SIXTRL_RESTRICT_REF m,
        py::class_< st::CBufferView >* SIXTRL_RESTRICT cbuffer_view_obj,
        py::class_< st::CBuffer >* SIXTRL_RESTRICT cbuffer_obj )
    {
        typedef st::ParticleTraits< st::SRotation >::real_t  st_real_t;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* SinglePrecSRotation: */

        py::class_< st::SinglePrecSRotation > single_prec_srotation_obj(
            m, "SinglePrecSRotation" );

        st::python::setup_be_srotation_bindings_for_types<
            st::SinglePrecSRotation >( m, single_prec_srotation_obj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_srotation_real_api_bindings<
            st::SinglePrecSRotation, st_real_t >( m, single_prec_srotation_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* DoublePrecSRotation: */

        py::class_< st::DoublePrecSRotation > double_prec_srotation_obj(
            m, "DoublePrecSRotation" );

        st::python::setup_be_srotation_bindings_for_types<
            st::DoublePrecSRotation >( m, double_prec_srotation_obj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_srotation_real_api_bindings<
            st::DoublePrecSRotation, st_real_t >( m, double_prec_srotation_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* QuadPrecSRotation: */

        py::class_< st::QuadPrecSRotation > quad_prec_srotation_obj(
            m, "QuadPrecSRotation" );

        st::python::setup_be_srotation_bindings_for_types<
            st::QuadPrecSRotation >( m, quad_prec_srotation_obj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_srotation_real_api_bindings<
            st::QuadPrecSRotation, st_real_t >( m, quad_prec_srotation_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* OctPrecSRotation: */

        py::class_< st::OctPrecSRotation > oct_prec_srotation_obj(
            m, "OctPrecSRotation" );

        st::python::setup_be_srotation_bindings_for_types<
            st::OctPrecSRotation >( m, oct_prec_srotation_obj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_srotation_real_api_bindings<
            st::OctPrecSRotation, st_real_t >( m, oct_prec_srotation_obj );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
