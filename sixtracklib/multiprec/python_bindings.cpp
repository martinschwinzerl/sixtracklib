#if defined( __cplusplus ) && !defined( _GPUCODE )

#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/python_bindings.hpp"

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
    void setup_multiprec_beam_elements_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT cbuffer_obj );

    void setup_multiprec_particles_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT cbuffer_obj );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    void setup_multiprec_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT cbuffer_obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef st::MultiPrecRealSingle<> mp_real_single_t;
        typedef st::MultiPrecRealDouble<> mp_real_double_t;
        typedef st::MultiPrecRealQuad<>   mp_real_quad_t;
        typedef st::MultiPrecRealOct<>    mp_real_oct_t;

        py::class_< mp_real_single_t > mp_real_single_obj(
            m, "MultiPrecRealSingle" );

        st::python::setup_multiprec_real_type_expl_conv_python_bindings<
            mp_real_single_t >( m, mp_real_single_obj );

        py::class_< mp_real_double_t > mp_real_double_obj(
            m, "MultiPrecRealDouble" );

        st::python::setup_multiprec_real_type_python_bindings<
            mp_real_double_t >( m, mp_real_double_obj );

        py::class_< mp_real_quad_t > mp_real_quad_obj(
            m, "MultiPrecRealQuad" );

        st::python::setup_multiprec_real_type_python_bindings<
            mp_real_quad_t >( m, mp_real_quad_obj );

        py::class_< mp_real_oct_t > mp_real_oct_obj(
            m, "MultiPrecRealOct" );

        st::python::setup_multiprec_real_type_python_bindings<
            mp_real_oct_t >( m, mp_real_oct_obj );


        st::python::setup_multiprec_beam_elements_python_bindings(
            m, cbuffer_view_obj, cbuffer_obj );

        st::python::setup_multiprec_particles_python_bindings(
            m, cbuffer_view_obj, cbuffer_obj );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
