#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/python_bindings.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/beam_elements/cavity.hpp"
#include "sixtracklib/common/internal/compiler_compability.h"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
    }

    void setup_common_be_cavity_bindings( py::module& SIXTRL_RESTRICT_REF m,
        py::class_< st::CBufferView >* SIXTRL_RESTRICT cbuffer_view_obj,
        py::class_< st::CBuffer >* SIXTRL_RESTRICT cbuffer_obj )
    {
        py::class_< st::Cavity > cavity_obj( m, "Cavity" );
        st::python::setup_be_cavity_bindings_for_types< st::Cavity >(
            m, cavity_obj, cbuffer_view_obj, cbuffer_obj );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */


#endif /* C++, Host */
