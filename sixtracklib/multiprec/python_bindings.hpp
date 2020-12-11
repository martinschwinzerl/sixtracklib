#ifndef SIXTRACKLIB_MULTIPREC_PYTHON_BINDINGS_CXX_HPP__
#define SIXTRACKLIB_MULTIPREC_PYTHON_BINDINGS_CXX_HPP__

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#if defined( __cplusplus ) && !defined( _GPUCODE )

#include <memory>
#include <string>
#include <sstream>
#include <tuple>
#include <stdexcept>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/common/internal/compiler_attributes.h"
#include "sixtracklib/common/internal/type_store_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    template< class R >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::MultiPrec_is_real_type< R >() ||
        !SIXTRL_CXX_NAMESPACE::MultiPrec_real_impl_boost< R >(), void >::type
    setup_multiprec_real_type_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< R >& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( real_obj ) )
    {
        return;
    }

    template< class R >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::MultiPrec_is_real_type< R >() &&
        SIXTRL_CXX_NAMESPACE::MultiPrec_real_impl_boost< R >(), void >::type
    setup_multiprec_real_type_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< R >& SIXTRL_RESTRICT_REF real_obj )
    {
        namespace py = pybind11;
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef SIXTRL_REAL_T st_real_t;
        typedef st::TypeMethodParamTraits< st_real_t >::const_argument_type
                st_const_real_arg_t;
        typedef st::TypeMethodParamTraits< st_real_t >::const_existing_type
                st_const_existing_real_t;

        typedef typename st::TypeMethodParamTraits< R >::const_argument_type
                const_real_arg_t;

        typedef typename st::TypeMethodParamTraits< R >::const_existing_type
                const_real_existing_t;

        real_obj.def( py::init< st_real_t >() );
        real_obj.def( py::init< std::string >() );

        real_obj.def( py::self += py::self );
        real_obj.def( py::self +  py::self );
        real_obj.def( py::self += st_real_t() );
        real_obj.def( py::self +  st_real_t() );
        real_obj.def( st_real_t() + py::self );

        real_obj.def( py::self -= py::self );
        real_obj.def( py::self -  py::self );
        real_obj.def( py::self -= st_real_t() );
        real_obj.def( py::self -  st_real_t() );
        real_obj.def( st_real_t() - py::self );
        real_obj.def( -py::self );

        real_obj.def( py::self *= py::self );
        real_obj.def( py::self *  py::self );
        real_obj.def( py::self *= st_real_t() );
        real_obj.def( py::self *  st_real_t() );
        real_obj.def( st_real_t() * py::self );

        real_obj.def( py::self /= py::self );
        real_obj.def( py::self /  py::self );
        real_obj.def( py::self /= st_real_t() );
        real_obj.def( py::self /  st_real_t() );
        real_obj.def( st_real_t() / py::self );

        real_obj.def( "__repr__",
            []( R const& value )
            {
                std::ostringstream a2str;
                a2str << value; return a2str.str(); } );
    }

    template< class R >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::MultiPrec_is_real_type< R >() &&
        SIXTRL_CXX_NAMESPACE::MultiPrec_real_impl_boost< R >(), void >::type
    setup_multiprec_real_type_expl_conv_python_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< R >& SIXTRL_RESTRICT_REF real_obj )
    {
        namespace py = pybind11;
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef float st_real_t;
        typedef st::TypeMethodParamTraits< st_real_t >::const_argument_type
                st_const_real_arg_t;
        typedef st::TypeMethodParamTraits< st_real_t >::const_existing_type
                st_const_existing_real_t;

        typedef typename st::TypeMethodParamTraits< R >::const_argument_type
                const_real_arg_t;

        typedef typename st::TypeMethodParamTraits< R >::const_existing_type
                const_real_existing_t;

        real_obj.def( py::init< st_real_t >() );
        real_obj.def( py::init< std::string >() );

        real_obj.def( py::self += py::self );
        real_obj.def( py::self +  py::self );
        real_obj.def( py::self += st_real_t() );
        real_obj.def( py::self +  st_real_t() );
        real_obj.def( st_real_t() + py::self );

        real_obj.def( py::self -= py::self );
        real_obj.def( py::self -  py::self );
        real_obj.def( py::self -= st_real_t() );
        real_obj.def( py::self -  st_real_t() );
        real_obj.def( st_real_t() - py::self );
        real_obj.def( -py::self );

        real_obj.def( py::self *= py::self );
        real_obj.def( py::self *  py::self );
        real_obj.def( py::self *= st_real_t() );
        real_obj.def( py::self *  st_real_t() );
        real_obj.def( st_real_t() * py::self );

        real_obj.def( py::self /= py::self );
        real_obj.def( py::self /  py::self );
        real_obj.def( py::self /= st_real_t() );
        real_obj.def( py::self /  st_real_t() );
        real_obj.def( st_real_t() / py::self );

        real_obj.def( "__repr__",
            []( R const& value )
            {
                std::ostringstream a2str;
                a2str << value; return a2str.str(); } );
    }


} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */

#endif /* SIXTRACKLIB_MULTIPREC_PYTHON_BINDINGS_CXX_HPP__ */
