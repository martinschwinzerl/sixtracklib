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
#include "sixtracklib/multiprec/beam_elements/drift.hpp"
#include "sixtracklib/common/beam_elements/drift.hpp"
#include "sixtracklib/common/beam_elements/drift/python_bindings.hpp"
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

    void setup_multiprec_beam_elements_drift_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< st::CBufferView >* SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< st::CBuffer >* SIXTRL_RESTRICT cbuffer_obj )
    {
        typedef st::ParticleTraits< st::Drift >::real_t st_real_t;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* SinglePrecDrift: */

        pybind11::class_< st::SinglePrecDrift > single_prec_drift_obj(
            m, "SinglePrecDrift" );

        st::python::setup_be_drift_bindings_for_types< st::SinglePrecDrift >(
            m, single_prec_drift_obj, cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_drift_real_api_bindings<
            st::SinglePrecDrift, st_real_t >( m, single_prec_drift_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* DoublePrecDrift: */

        pybind11::class_< st::DoublePrecDrift > double_prec_drift_obj(
            m, "DoublePrecDrift" );

        st::python::setup_be_drift_bindings_for_types< st::DoublePrecDrift >(
            m, double_prec_drift_obj, cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_drift_real_api_bindings<
            st::DoublePrecDrift, st_real_t >( m, double_prec_drift_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* QuadPrecDrift: */

        pybind11::class_< st::QuadPrecDrift > quad_prec_drift_obj(
            m, "QuadPrecDrift" );

        st::python::setup_be_drift_bindings_for_types< st::QuadPrecDrift >(
            m, quad_prec_drift_obj, cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_drift_real_api_bindings<
            st::QuadPrecDrift, st_real_t >( m, quad_prec_drift_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* OctPrecDrift: */

        py::class_< st::OctPrecDrift > oct_prec_drift_obj( m, "OctPrecDrift" );

        st::python::setup_be_drift_bindings_for_types< st::OctPrecDrift >(
            m, oct_prec_drift_obj, cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_drift_real_api_bindings<
            st::OctPrecDrift, st_real_t >( m, oct_prec_drift_obj );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
