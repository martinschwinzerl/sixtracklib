#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/xy_shift/python_bindings.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/beam_elements/xy_shift.hpp"
#include "sixtracklib/common/internal/compiler_compability.h"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    void setup_be_xy_shift_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT cbuffer_obj )
    {
        pybind11::class_< SIXTRL_CXX_NAMESPACE::XYShift >
            xy_shift_obj( m, "XYShift" );

        SIXTRL_CXX_NAMESPACE::python::setup_be_xy_shift_bindings_for_types<
            SIXTRL_CXX_NAMESPACE::XYShift >( m, xy_shift_obj,
                 cbuffer_view_obj, cbuffer_obj );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */


#endif /* C++, Host */
