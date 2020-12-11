#if defined( __cplusplus ) && !defined( _GPUCODE )
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    void setup_multiprec_beam_elements_cavity_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView
            >* SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer
            >* SIXTRL_RESTRICT cbuffer_obj );

    void setup_multiprec_beam_elements_drift_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView
            >* SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer
            >* SIXTRL_RESTRICT cbuffer_obj );

    void setup_multiprec_beam_elements_multipole_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView
            >* SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer
            >* SIXTRL_RESTRICT cbuffer_obj );

    void setup_multiprec_beam_elements_srotation_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView
            >* SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer
            >* SIXTRL_RESTRICT cbuffer_obj );

    void setup_multiprec_beam_elements_xy_shift_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView
            >* SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer
            >* SIXTRL_RESTRICT cbuffer_obj );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    void setup_multiprec_beam_elements_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT cbuffer_obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        st::python::setup_multiprec_beam_elements_cavity_python_bindings(
            m, cbuffer_view_obj, cbuffer_obj );

        st::python::setup_multiprec_beam_elements_drift_python_bindings(
            m, cbuffer_view_obj, cbuffer_obj );

        st::python::setup_multiprec_beam_elements_multipole_python_bindings(
            m, cbuffer_view_obj, cbuffer_obj );

        st::python::setup_multiprec_beam_elements_srotation_python_bindings(
            m, cbuffer_view_obj, cbuffer_obj );

        st::python::setup_multiprec_beam_elements_xy_shift_python_bindings(
            m, cbuffer_view_obj, cbuffer_obj );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
