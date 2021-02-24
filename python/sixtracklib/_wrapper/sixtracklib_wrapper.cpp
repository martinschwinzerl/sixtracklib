#include "sixtracklib/sixtracklib.hpp"
#include "sixtracklib/sixtracklib.h"

#include "python/sixtracklib/_wrapper/init_helper.h"

#include <memory>
#include <string>
#include <utility>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

PYBIND11_MODULE( _wrapper, m )
{
    namespace py = pybind11;
    m.attr( "__name__" ) = "sixtracklib._wrapper";

    #if defined( SIXTRL_DEMOTRACK_ENABLED ) && \
               ( SIXTRL_DEMOTRACK_ENABLED == 1 )

    PYBIND11_NUMPY_DTYPE( ::NS(DemotrackParticle),
        x, px, y, py, zeta, delta, rpp, rvv, psigma, chi, charge_ratio,
            charge0, mass0, beta0, gamma0, p0c, state, at_element, at_turn, id );

    #endif /* SIXTRL_DEMOTRACK_ENABLED */

    SIXTRL_CXX_NAMESPACE::python::InitHelper sixtracklib_defs( m );
    sixtracklib_defs.init();
}
