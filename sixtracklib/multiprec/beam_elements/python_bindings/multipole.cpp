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
#include "sixtracklib/multiprec/beam_elements/multipole.hpp"
#include "sixtracklib/common/beam_elements/multipole.hpp"
#include "sixtracklib/common/beam_elements/multipole/python_bindings.hpp"
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

    void setup_multiprec_beam_elements_multipole_python_bindings(
        py::module& SIXTRL_RESTRICT_REF m,
        py::class_< st::CBufferView >* SIXTRL_RESTRICT cbuffer_view_obj,
        py::class_< st::CBuffer >* SIXTRL_RESTRICT cbuffer_obj )
    {
        typedef st::ParticleTraits< st::Multipole >::real_t  st_real_t;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* SinglePrecMultipole: */

        py::class_< st::SinglePrecMultipole > single_prec_multipoleobj(
            m, "SinglePrecMultipole" );

        st::python::setup_be_multipole_bindings_for_types<
            st::SinglePrecMultipole >( m, single_prec_multipoleobj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_multipole_real_api_bindings<
            st::SinglePrecMultipole, st_real_t >( m, single_prec_multipoleobj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* DoublePrecMultipole: */

        py::class_< st::DoublePrecMultipole > double_prec_multipoleobj(
            m, "DoublePrecMultipole" );

        st::python::setup_be_multipole_bindings_for_types<
            st::DoublePrecMultipole >( m, double_prec_multipoleobj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_multipole_real_api_bindings<
            st::DoublePrecMultipole, st_real_t >( m, double_prec_multipoleobj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* QuadPrecMultipole: */

        py::class_< st::QuadPrecMultipole > quad_prec_multipoleobj(
            m, "QuadPrecMultipole" );

        st::python::setup_be_multipole_bindings_for_types<
            st::QuadPrecMultipole >( m, quad_prec_multipoleobj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_multipole_real_api_bindings<
            st::QuadPrecMultipole, st_real_t >( m, quad_prec_multipoleobj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* OctPrecMultipole: */

        py::class_< st::OctPrecMultipole > oct_prec_multipoleobj(
            m, "OctPrecMultipole" );

        st::python::setup_be_multipole_bindings_for_types<
            st::OctPrecMultipole >( m, oct_prec_multipoleobj,
                cbuffer_view_obj, cbuffer_obj );

        st::python::setup_be_multipole_real_api_bindings<
            st::OctPrecMultipole, st_real_t >( m, oct_prec_multipoleobj );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
