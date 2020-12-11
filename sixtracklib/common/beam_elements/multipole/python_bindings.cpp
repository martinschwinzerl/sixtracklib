#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/python_bindings.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <memory>
#include <string>
#include <tuple>
#include <iostream>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/beam_elements/multipole.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    void setup_common_be_multipole_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT cbuffer_obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        pybind11::class_< st::Multipole > multipole_obj( m, "Multipole" );

        st::python::setup_be_multipole_bindings_for_types< st::Multipole >(
            m, multipole_obj, cbuffer_view_obj, cbuffer_obj );
    }


} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */


#endif /* C++, Host */
