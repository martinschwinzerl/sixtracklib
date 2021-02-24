#ifndef SIXTRACKLIB_PYTHON_WRAPPER_CXX11_OPTIONAL_H__
#define SIXTRACKLIB_PYTHON_WRAPPER_CXX11_OPTIONAL_H__

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "python/sixtracklib/_wrapper/tl/optional.hpp"

namespace pybind11 {
namespace detail {

template< typename T >
struct type_caster< tl::optional< T > > :
    optional_caster< tl::optional< T > >{};

} /* end: namespace detail */
} /* end: namespace pybind11 */

#endif /* SIXTRACKLIB_PYTHON_WRAPPER_CXX11_OPTIONAL_H__ */
