#include "python/sixtracklib/_wrapper/demotrack.h"
#include "python/sixtracklib/_wrapper/tl/optional.hpp"
#include "python/sixtracklib/_wrapper/cxx11_optional.h"
#include "python/sixtracklib/_wrapper/buffer_protocol.h"
#include "python/sixtracklib/_wrapper/init_helper.h"

#if defined( SIXTRL_TESTLIB_ENABLED ) && ( SIXTRL_TESTLIB_ENABLED == 1 )
    #include "sixtracklib/testlib.h"
#endif /* defined( SIXTRL_TESTLIB_ENABLED ) */

#include <limits>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE {
namespace python {

namespace
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    namespace stpy = SIXTRL_CXX_NAMESPACE::python;
    namespace py = pybind11;
}

void InitHelper_demotrack( stpy::InitHelper& root )
{
    py::module& m = root.m;

    #if defined( SIXTRL_DEMOTRACK_ENABLED ) && ( SIXTRL_DEMOTRACK_ENABLED == 1 )
    m.def( "Demotrack_enabled", []() { return true; } );
    #else
    m.def( "Demotrack_enabled", []() { return false; } );
    #endif /* SIXTRL_DEMOTRACK_ENABLED */
}

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */
