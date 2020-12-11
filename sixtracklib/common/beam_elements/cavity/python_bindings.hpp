#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_PYTHON_BYINDINGS_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_PYTHON_BYINDINGS_CXX_HPP__
/* Cavity Beam Element */

#if defined( __cplusplus ) && !defined( _GPUCODE )

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <memory>
#include <string>
#include <sstream>
#include <tuple>
#include <iostream>
#include <stdexcept>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/cobjects/python_bindings.hpp"
#include "sixtracklib/common/beam_elements/cavity.hpp"
#include "sixtracklib/common/internal/compiler_compability.h"
#include "sixtracklib/common/internal/type_store_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< E >(), void >::type
    setup_be_cavity_base_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( elem ) )
    {
        return;
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< E >(), void >::type
    setup_be_cavity_base_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef typename st::CavityTraits< E >::real_t real_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_existing_type const_real_existing_t;

        elem.def( py::init(
        []( const_real_arg_t voltage, const_real_arg_t frequency,
            const_real_arg_t lag )
        {
            auto ptr_elem = st::make_unique< E >();
            if( st::ARCH_STATUS_SUCCESS != st::Cavity_init( ptr_elem.get(),
                voltage, frequency, lag ) )
            {
                ptr_elem.reset( nullptr );
            }

            return std::move( ptr_elem );
        } ),
        py::arg( "voltage" ) = st::Cavity_default_voltage< E >(),
        py::arg( "frequency" ) = st::Cavity_default_frequency< E >(),
        py::arg( "lag" ) = st::Cavity_default_lag< E >() );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        elem.def_property( "voltage",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_real_existing_t
        {
            return st::Cavity_voltage( std::addressof( elem ) );
        },
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_real_arg_t voltage )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Cavity_set_voltage(
                    std::addressof( elem ), voltage ) )
            {
                throw std::runtime_error(
                    "Error during st::Cavity_set_voltage" );
            }
        } );

        elem.def_property( "frequency",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_real_existing_t
        {
            return st::Cavity_frequency( std::addressof( elem ) );
        },
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_real_arg_t frequency )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Cavity_set_frequency(
                    std::addressof( elem ), frequency ) )
            {
                throw std::runtime_error(
                    "Error during st::Cavity_set_frequency" );
            }
        } );

        elem.def_property( "lag",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_real_existing_t
        {
            return st::Cavity_lag( std::addressof( elem ) );
        },
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_real_arg_t lag )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Cavity_set_lag(
                    std::addressof( elem ), lag ) )
            {
                throw std::runtime_error(
                    "error during st::cavity_set_lag" );
            }
        } );

        elem.def( "__repr__", []( SIXTRL_BE_ARGPTR_DEC E const& elem )
        {
            std::ostringstream a2str;
            a2str << "<sixtrack::Cavity: voltage="
                  << st::Cavity_voltage( std::addressof( elem ) ) << "\r\n"
                  << "                 frequency="
                  << st::Cavity_frequency( std::addressof( elem ) )
                  << "\r\n"
                  << "                       lag="
                  << st::Cavity_lag( std::addressof( elem ) )
                  << ">";

            return a2str.str(); } );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E, class RealType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< E >(), void >::type
    setup_be_cavity_real_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( cavity_obj ) )
    {
        return;
    }

    template< class E, class RealType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< E >(), void >::type
    setup_be_cavity_real_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF cavity_obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef typename std::decay< RealType >::type real_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        cavity_obj.def( "set_voltage",
        []( SIXTRL_BE_ARGPTR_DEC E& SIXTRL_RESTRICT_REF elem,
            const_real_arg_t voltage )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Cavity_set_voltage(
                std::addressof( elem ), voltage ) )
                throw std::runtime_error( "Error during set voltage" );
            return std::addressof( elem );
        }, py::arg( "voltage" ) );

        cavity_obj.def( "set_frequency",
        []( SIXTRL_BE_ARGPTR_DEC E& SIXTRL_RESTRICT_REF elem,
            const_real_arg_t frequency )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Cavity_set_frequency(
                std::addressof( elem ), frequency ) )
                throw std::runtime_error( "Error during set frequency" );
            return std::addressof( elem );
        }, py::arg( "frequency" ) );

        cavity_obj.def( "set_lag",
        []( SIXTRL_BE_ARGPTR_DEC E& SIXTRL_RESTRICT_REF elem,
            const_real_arg_t lag )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Cavity_set_lag(
                std::addressof( elem ), lag ) )
                throw std::runtime_error( "Error during set lag" );
            return std::addressof( elem );
        }, py::arg( "lag" ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
         !SIXTRL_CXX_NAMESPACE::Cavity_is_type< E >() ||
         !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
         void >::type
     setup_be_cavity_cobjects_direct_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cavity_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_view_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_obj ),
        SIXTRL_BE_ARGPTR_DEC const E *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_dummy ) = nullptr )
     {
         return;
     }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        void >::type
    setup_be_cavity_cobjects_direct_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< E >& SIXTRL_RESTRICT_REF elem_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >&
            SIXTRL_RESTRICT_REF cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >&
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_BE_ARGPTR_DEC const E *const
            SIXTRL_UNUSED( ptr_dummy ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
        typedef typename st::CavityTraits< E >::real_t real_t;

        typedef typename st::TypeMethodParamTraits< real_t
            >::const_argument_type const_real_arg_t;

        st::python::setup_cobjects_store_direct_base_for_type< E >(
            m, elem_obj, cbuffer_view_obj, cbuffer_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* free methods / functions */

        typedef st::CBuffer cbuffer_t;

        elem_obj.def_static( "create_new",
        []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& SIXTRL_RESTRICT_REF cbuffer )
        {
            auto ptr_elem = cbuffer.create_new< E >();
            if( ptr_elem == nullptr ) throw std::runtime_error(
                    "Unable to create cavity on cbuffer" );
            return py::cast( ptr_elem );
        }, py::arg( "cbuffer" ) );

        elem_obj.def_static( "add",
        []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& cbuffer,
            const_real_arg_t voltage, const_real_arg_t frequency,
            const_real_arg_t lag )
            {
                auto ptr_elem = cbuffer.add< E >( voltage, frequency, lag );
                if( ptr_elem == nullptr ) throw std::runtime_error(
                        "Unable to create cavity on cbuffer" );

                return ptr_elem;
            },
            py::arg( "cbuffer" ), py::arg( "voltage" ),
            py::arg( "frequency" ), py::arg( "lag" ) );
    }

    /* --------------------------------------------------------------------- */

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(), void >::type
    setup_be_cavity_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< CavityT >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( elem_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_view_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_obj ),
        SIXTRL_BE_ARGPTR_DEC const CavityT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_particle_dummy ) = nullptr )
    {
        return;
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(), void >::type
    setup_be_cavity_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< CavityT >& SIXTRL_RESTRICT_REF elem_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT_REF cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_BE_ARGPTR_DEC const CavityT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_elem_dummy ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::CavityTraits< CavityT >::real_t real_t;

        st::python::setup_be_cavity_base_api_bindings<
            CavityT >( m, elem_obj );

        st::python::setup_be_cavity_real_api_bindings<
            CavityT, real_t >( m, elem_obj );

        if( ( cbuffer_view_obj != nullptr ) && ( cbuffer_obj != nullptr ) )
        {
            st::python::setup_cobjects_load_store_for_type< CavityT
                >( m, elem_obj, *cbuffer_view_obj, *cbuffer_obj );

            st::python::setup_be_cavity_cobjects_direct_bindings< CavityT
                >( m, elem_obj, *cbuffer_view_obj, *cbuffer_obj );
        }
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_PYTHON_BYINDINGS_CXX_HPP__ */
