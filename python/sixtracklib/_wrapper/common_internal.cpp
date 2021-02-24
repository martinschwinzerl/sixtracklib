#include "python/sixtracklib/_wrapper/common_internal.h"
#include "python/sixtracklib/_wrapper/init_helper.h"

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/math_factorial.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace SIXTRL_CXX_NAMESPACE {
namespace python {
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace stpy = SIXTRL_CXX_NAMESPACE::python;
        namespace py = pybind11;
    }

    void InitHelper_common_internal( stpy::InitHelper& root )
    {
        stpy::InitHelper_common_internal_math_factorial( root );
    }

    void InitHelper_common_internal_math_factorial( stpy::InitHelper& root )
    {
        py::module& m = root.m;

        using uint_type = SIXTRL_UINT64_TYPE;
        using real_type = SIXTRL_REAL_TYPE;


        m.def( stpy::Add_c99_ns( "Math_factorial" ).c_str(),
               []( uint_type const nn ) -> real_type {
                    return ::NS(Math_factorial)( nn ); } );

        m.def( stpy::Add_c99_ns( "Math_inv_factorial" ).c_str(),
               []( uint_type const nn ) -> real_type {
                    return ::NS(Math_inv_factorial)( nn ); } );
    }

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */
