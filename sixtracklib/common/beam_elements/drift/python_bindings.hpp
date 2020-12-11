#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_PYTHON_BYINDINGS_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_PYTHON_BYINDINGS_CXX_HPP__
/* Drift Beam Element */

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
#include "sixtracklib/common/beam_elements/drift.hpp"
#include "sixtracklib/common/internal/compiler_compability.h"
#include "sixtracklib/common/internal/type_store_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    namespace
    {
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN void Drift_track_type_to_str(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            SIXTRL_CXX_NAMESPACE::be_drift_track_type_t const track_type )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            switch( track_type )
            {
                case st::BE_DRIFT_TRACK_TYPE_SIMPLE:
                {
                    ostr << "simple";
                    break;
                }

                case st::BE_DRIFT_TRACK_TYPE_EXACT:
                {
                    ostr << "exact";
                    break;
                }

                default:
                {
                    ostr << "illegal/unknown";
                }
            };
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_CXX_NAMESPACE::be_drift_track_type_t Drift_str_to_track_type(
            std::string const& SIXTRL_RESTRICT_REF track_type_str )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::be_drift_track_type_t track_type =
                st::BE_DRIFT_TRACK_TYPE_ILLEGAL;

            if( track_type_str.compare( "default" ) == 0 )
            {
                track_type = st::BE_DRIFT_TRACK_TYPE_DEFAULT;
            }
            else if( track_type_str.compare( "simple" ) == 0 )
            {
                track_type = st::BE_DRIFT_TRACK_TYPE_SIMPLE;
            }
            else if( track_type_str.compare( "exact" ) == 0 )
            {
                track_type = st::BE_DRIFT_TRACK_TYPE_EXACT;
            }

            return track_type;
        }
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Drift_is_type< E >(), void >::type
    setup_be_drift_base_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( elem_obj ) )
    {
        return;
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< E >(), void >::type
    setup_be_drift_base_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< E >& SIXTRL_RESTRICT_REF elem_obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
        typedef SIXTRL_BE_ARGPTR_DEC E elem_t;
        typedef typename st::DriftTraits< E >::real_t real_t;
        typedef st::be_drift_track_type_t track_type_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_existing_type const_real_existing_t;

        static_assert( st::Drift_is_type< E >(),
                       "E required to be a drift class" );

        elem_obj.def( py::init(
        []( const_real_arg_t length, track_type_t const track_type )
        {
            auto ptr_elem = st::make_unique< E >();
            if( st::ARCH_STATUS_SUCCESS !=
                    st::Drift_init( ptr_elem.get(), length, track_type ) )
            {
                ptr_elem.reset( nullptr );
            }

            return std::move( ptr_elem );
        } ), py::arg( "length" ), py::arg( "track_type" ) );

        elem_obj.def( py::init(
        []( const_real_arg_t length, std::string const& track_type_str )
        {
            auto ptr_elem = st::make_unique< E >();
            if( st::ARCH_STATUS_SUCCESS !=
                st::Drift_init( ptr_elem.get(), length,
                    st::python::Drift_str_to_track_type( track_type_str ) ) )
            {
                ptr_elem.reset( nullptr );
            }
            return std::move( ptr_elem ); }
        ),
        py::arg( "length" ) = st::Drift_default_length< E >(),
        py::arg( "track_type" ) = "default" );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        elem_obj.def_property( "length",
        []( elem_t const& elem ) -> const_real_existing_t
        {
            return st::Drift_length( std::addressof( elem ) );
        },
        []( elem_t& elem, const_real_arg_t length )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Drift_set_length(
                    std::addressof( elem ), length ) )
            {
                throw std::runtime_error(
                    "Error during st::Drift_set_length" );
            }
        } );

        elem_obj.def_property( "track_type",
        []( elem_t const& elem ) -> track_type_t
        {
            return st::Drift_track_type( std::addressof( elem ) );
        },
        []( Drift& elem, track_type_t const track_type )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Drift_set_track_type(
                    std::addressof( elem ), track_type ) )
            {
                throw std::runtime_error(
                    "Error during st::Drift_set_track_type" );
            }
        } );

        elem_obj.def_property( "track_type_str",
        []( elem_t const& elem ) -> std::string
        {
            std::ostringstream a2str;
            st::python::Drift_track_type_to_str(
                a2str, st::Drift_track_type( std::addressof( elem ) ) );
            return a2str.str();
        },
        []( Drift& elem, std::string const& track_type_str )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Drift_set_track_type(
                    std::addressof( elem ),
                st::python::Drift_str_to_track_type( track_type_str ) ) )
            {
                throw std::runtime_error(
                    "Error during st::Drift_set_track_type from str" );
            }
        } );

        elem_obj.def( "__repr__",
        []( elem_t const& elem )
        {
            std::ostringstream a2str;
            a2str << "<sixtrack::Drift: length="
                  << st::Drift_length( std::addressof( elem ) )
                  << ", track_type=";

            st::python::Drift_track_type_to_str( a2str,
                st::Drift_track_type( std::addressof( elem ) ) );

            a2str << ">";
            return a2str.str();
        } );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E, class RealType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Drift_is_type< E >(), void >::type
    setup_be_drift_real_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( drift_obj ) )
    {
        return;
    }

    template< class E, class RealType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< E >(), void >::type
    setup_be_drift_real_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF drift_obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
        typedef typename std::decay< RealType >::type real_t;

        typedef typename st::TypeMethodParamTraits<
            real_t >::const_argument_type const_real_arg_t;

        drift_obj.def( "set_length",
            []( SIXTRL_BE_ARGPTR_DEC E& drift, const_real_arg_t length )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Drift_set_length(
                    std::addressof( drift ), length ) )
                    throw std::runtime_error(
                        "Error during running st::Drift_set_length" );
                return std::addressof( drift );
            }, py::arg( "length" ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
         !SIXTRL_CXX_NAMESPACE::Drift_is_type< E >() ||
         !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
         void >::type
     init_be_drift_cobjects_direct_for_type(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF elem_obj,
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
        SIXTRL_CXX_NAMESPACE::Drift_is_type< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        void >::type
    init_be_drift_cobjects_direct_for_type(
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

        typedef SIXTRL_BE_ARGPTR_DEC E elem_t;
        typedef st::be_drift_track_type_t track_type_t;
        typedef typename st::DriftTraits< E >::real_t real_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_existing_type const_real_existing_t;

        st::python::setup_cobjects_store_direct_base_for_type< E >(
            m, elem_obj, cbuffer_view_obj, cbuffer_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* free methods / functions */

        typedef st::CBufferView cbuffer_view_t;
        typedef st::CBuffer cbuffer_t;

        elem_obj.def_static( "create_new",
        []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& SIXTRL_RESTRICT_REF cbuffer )
        {
            elem_t* ptr_elem = cbuffer.create_new< E >();
            if( ptr_elem == nullptr ) throw std::runtime_error(
                    "Unable to create drift on cbuffer" );
            return py::cast( ptr_elem );
        }, py::arg( "cbuffer" ) );

        elem_obj.def_static( "add",
        []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& SIXTRL_RESTRICT_REF cbuffer,
            const_real_arg_t length, std::string const& track_type_str )
        {
            elem_t* ptr_elem = cbuffer.add< E >( length,
                st::python::Drift_str_to_track_type( track_type_str ) );
            if( ptr_elem == nullptr ) throw std::runtime_error(
                    "Unable to create drift on cbuffer" );
            return py::cast( ptr_elem );
        }, py::arg( "cbuffer" ), py::arg( "length" ),
           py::arg( "track_type" ) = "default" );

        elem_obj.def_static( "add",
        []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& SIXTRL_RESTRICT_REF cbuffer,
            const_real_arg_t length, track_type_t const track_type )
        {
            elem_t* ptr_elem = cbuffer.add< E >( length, track_type );
            if( ptr_elem == nullptr ) throw std::runtime_error(
                "Unable to create drift on cbuffer" );
            return py::cast( ptr_elem );
        }, py::arg( "cbuffer" ), py::arg( "length" ), py::arg( "track_type" ) );
    }

    /* --------------------------------------------------------------------- */

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(), void >::type
    setup_be_drift_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< DriftT >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( elem_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_view_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_obj ),
        SIXTRL_BE_ARGPTR_DEC const DriftT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_particle_dummy ) = nullptr )
    {
        return;
    }

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(), void >::type
    setup_be_drift_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< DriftT >& SIXTRL_RESTRICT_REF elem_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT_REF cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_BE_ARGPTR_DEC const DriftT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_elem_dummy ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::DriftTraits< DriftT >::real_t real_t;
        st::python::setup_be_drift_base_api_bindings< DriftT >( m, elem_obj );
        st::python::setup_be_drift_real_api_bindings<
            DriftT, real_t >( m, elem_obj );

        if( ( cbuffer_view_obj != nullptr ) && ( cbuffer_obj != nullptr ) )
        {
            st::python::setup_cobjects_load_store_for_type< DriftT
                >( m, elem_obj, *cbuffer_view_obj, *cbuffer_obj );

            st::python::init_be_drift_cobjects_direct_for_type< DriftT
                >( m, elem_obj, *cbuffer_view_obj, *cbuffer_obj );
        }
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */



#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_PYTHON_BYINDINGS_CXX_HPP__ */
