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
#include "sixtracklib/multiprec/beam_elements/xy_shift.hpp"
#include "sixtracklib/common/beam_elements/xy_shift.hpp"
#include "sixtracklib/common/beam_elements/xy_shift/python_bindings.hpp"
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

    void setup_multiprec_beam_elements_xy_shift_python_bindings(
        py::module& SIXTRL_RESTRICT_REF m,
        py::class_< st::CBufferView >* SIXTRL_RESTRICT cbuffer_view_obj,
        py::class_< st::CBuffer >* SIXTRL_RESTRICT cbuffer_obj )
    {
        typedef st::ParticleTraits< st::XYShift >::real_t  st_real_t;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* SinglePrecXYShift: */

        py::class_< st::SinglePrecXYShift > single_prec_xy_shift_obj(
            m, "SinglePrecXYShift" );

        st::python::setup_be_xy_shift_bindings_for_types<
            st::SinglePrecXYShift >( m, single_prec_xy_shift_obj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_xy_shift_real_api_bindings<
            st::SinglePrecXYShift, st_real_t >( m, single_prec_xy_shift_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* DoublePrecXYShift: */

        py::class_< st::DoublePrecXYShift > double_prec_xy_shift_obj(
            m, "DoublePrecXYShift" );

        st::python::setup_be_xy_shift_bindings_for_types<
            st::DoublePrecXYShift >( m, double_prec_xy_shift_obj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_xy_shift_real_api_bindings<
            st::DoublePrecXYShift, st_real_t >( m, double_prec_xy_shift_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* QuadPrecXYShift: */

        py::class_< st::QuadPrecXYShift > quad_prec_xy_shift_obj(
            m, "QuadPrecXYShift" );

        st::python::setup_be_xy_shift_bindings_for_types<
            st::QuadPrecXYShift >( m, quad_prec_xy_shift_obj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_xy_shift_real_api_bindings<
            st::QuadPrecXYShift, st_real_t >( m, quad_prec_xy_shift_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* OctPrecXYShift: */

        py::class_< st::OctPrecXYShift > oct_prec_xy_shift_obj(
            m, "OctPrecXYShift" );

        st::python::setup_be_xy_shift_bindings_for_types<
            st::OctPrecXYShift >( m, oct_prec_xy_shift_obj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_xy_shift_real_api_bindings<
            st::OctPrecXYShift, st_real_t >( m, oct_prec_xy_shift_obj );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
