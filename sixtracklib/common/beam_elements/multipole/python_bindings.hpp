#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_PYTHON_BYINDINGS_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_PYTHON_BYINDINGS_CXX_HPP__
/* Multipole Beam Element */

#if defined( __cplusplus ) && !defined( _GPUCODE )

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <algorithm>
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
#include "sixtracklib/common/beam_elements/multipole.hpp"
#include "sixtracklib/common/internal/compiler_compability.h"
#include "sixtracklib/common/internal/type_store_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Multipole_is_type< E >(), void >::type
    setup_be_multipole_base_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( elem ) )
    {
        return;
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< E >(), void >::type
    setup_be_multipole_base_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef typename st::MultipoleTraits< E >::real_t  real_t;
        typedef typename st::MultipoleTraits< E >::order_t order_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_existing_type const_real_existing_t;

        typedef typename st::TypeMethodParamTraits<
                    order_t >::const_argument_type const_order_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    order_t >::const_existing_type const_order_existing_t;

        static_assert( st::Multipole_is_type< E >(),
                       "E required to be a multipole class" );

        elem.def( py::init(
        []( const_order_arg_t order, const_real_arg_t length,
            const_real_arg_t hxl, const_real_arg_t hyl,
            const_order_arg_t bal_capacity,
            st::be_address_t const bal_addr )
        {
            std::unique_ptr< E > ptr_elem( new E );

            if( st::ARCH_STATUS_SUCCESS != st::Multipole_init( ptr_elem.get(),
                order, length, hxl, hyl, bal_addr, bal_capacity ) )
            {
                ptr_elem.reset( nullptr );
            }
            return std::move( ptr_elem ); }
        ),
        py::arg( "order" ),
        py::arg( "length" ) = st::Multipole_default_length< E >(),
        py::arg( "hxl" ) = st::Multipole_default_hxl< E >(),
        py::arg( "hyl" ) = st::Multipole_default_hyl< E >(),
        py::arg( "bal_capacity" ) = order_t{ 0 },
        py::arg( "bal_addr" ) = st::be_address_t{ 0 } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        elem.def_property( "order",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem )
        -> const_order_existing_t
        {
            return st::Multipole_order( std::addressof( elem ) );
        },
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_order_arg_t order )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_order(
                std::addressof( elem ), order ) ) throw std::runtime_error(
                    "Error during st::Multipole_set_order" );
        } );

        elem.def_property_readonly( "max_order",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_order_existing_t
        {
            return st::Multipole_max_order( std::addressof( elem ) );
        } );

        elem.def_property_readonly( "bal_length",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> order_t
        {
            return st::Multipole_bal_length( std::addressof( elem ) );
        } );

        elem.def_property_readonly( "bal_capacity",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_order_existing_t
        {
            return st::Multipole_bal_capacity( std::addressof( elem ) );
        } );

        elem.def_property( "length",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_real_existing_t
        {
            return st::Multipole_length( std::addressof( elem ) );
        },
        []( E& elem, const_real_arg_t length )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_length(
                    std::addressof( elem ), length ) )
            {
                throw std::runtime_error(
                    "Error during st::Multipole_set_length" );
            }
        } );

        elem.def_property( "hxl",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_real_existing_t
        {
            return st::Multipole_hxl( std::addressof( elem ) );
        },
        []( E& elem, const_real_arg_t hxl )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_hxl(
                    std::addressof( elem ), hxl ) )
            {
                throw std::runtime_error(
                    "Error during st::Multipole_set_hxl" );
            }
        } );

        elem.def_property( "hyl",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_real_existing_t
        {
            return st::Multipole_hyl( std::addressof( elem ) );
        },
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_real_arg_t hyl )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_hyl(
                    std::addressof( elem ), hyl ) )
            {
                throw std::runtime_error(
                    "Error during st::Multipole_set_hyl" );
            } } );

        elem.def_property( "bal_addr",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> st::be_address_t
        {
            return st::Multipole_bal_addr( std::addressof( elem ) );
        },
        []( SIXTRL_BE_ARGPTR_DEC E& elem, st::be_address_t const bal_addr )
        {
            if( st::ARCH_STATUS_SUCCESS == st::Multipole_set_bal_addr(
                std::addressof( elem ), bal_addr ) )
                throw std::runtime_error( "Unable to set bal_addr of multipole" );
            return std::addressof( elem );
        }
        );

        elem.def( "__getitem__",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem, const_order_arg_t ii ) ->
            const_real_existing_t
        {
            auto ptr_elem = std::addressof( elem );

            if( ( ii < order_t{ 0 } ) ||
                ( ii >= st::Multipole_bal_length( ptr_elem ) ) )
            {
                std::ostringstream a2str;
                a2str << "illegal bal_index=" << ii << ", bal_length="
                      << st::Multipole_bal_length( ptr_elem );
                throw std::runtime_error( a2str.str() );
            }

            return st::Multipole_bal( ptr_elem, ii );
        }, py::arg( "bal_index" ) );

        elem.def( "knl",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem,
            const_order_arg_t ii ) -> real_t
        {
            auto ptr_elem = std::addressof( elem );
            if( ( ii < order_t{ 0 } ) ||
                ( ii > st::Multipole_order( ptr_elem ) ) )
            {
                std::ostringstream a2str;
                a2str << "illegal knl_index=" << ii
                      << ", order=" << st::Multipole_order( ptr_elem );
                throw std::runtime_error( a2str.str() );
            }

            return st::Multipole_knl( ptr_elem, ii );
        }, py::arg( "knl_index" ) );


        elem.def( "ksl",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem,
            const_order_arg_t ii ) -> real_t
        {
            auto ptr_elem = std::addressof( elem );
            if( ( ii < order_t{ 0 } ) ||
                ( ii > st::Multipole_order( ptr_elem ) ) )
            {
                std::ostringstream a2str;
                a2str << "illegal ksl_index=" << ii
                      << ", order=" << st::Multipole_order( ptr_elem );
                throw std::runtime_error( a2str.str() );
            }

            return st::Multipole_ksl( ptr_elem, ii );
        }, py::arg( "ksl_index" ) );

        elem.def( "__repr__",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem )
        {
            auto ptr_elem = std::addressof( elem );

            std::ostringstream a2str;
            a2str << "<sixtrack::Multipole: order="
                  << st::Multipole_order( ptr_elem ) << "\r\n"
                  << "                     length="
                  << st::Multipole_length( ptr_elem )
                  << "                        hxl="
                  << st::Multipole_hxl( ptr_elem )
                  << "                        hyl="
                  << st::Multipole_hyl( ptr_elem )
                  << "                        bal=[";

            auto it  = st::Multipole_const_bal_begin( ptr_elem );
            auto end = st::Multipole_const_bal_end( ptr_elem );
            for( ; it != end ; ++it ) a2str << *it << ", ";

             a2str << "]\r\n"
                   << "              bal_capacity="
                   << st::Multipole_bal_length( ptr_elem ) << "\r\n>";
            return a2str.str();
        } );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E, class RealType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Multipole_is_type< E >(), void >::type
    setup_be_multipole_real_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( multipole_obj ) )
    {
        return;
    }

    template< class E, class RealType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< E >(), void >::type
    setup_be_multipole_real_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF multipole_obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef typename std::decay< RealType >::type real_t;
        typedef typename st::TypeMethodParamTraits<
            real_t >::const_argument_type const_real_arg_t;

        typedef typename st::MultipoleTraits< E >::order_t order_t;
        typedef typename st::TypeMethodParamTraits<
            order_t >::const_argument_type const_order_arg_t;

        multipole_obj.def( "set_length",
        []( SIXTRL_BE_ARGPTR_DEC E& mp, const_real_arg_t length )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_length(
                std::addressof( mp ), length ) )
                throw std::runtime_error(
                    "Error during running st::Multipole_set_length" );
            return std::addressof( mp ); }, py::arg( "length" ) );

        multipole_obj.def( "set_hxl",
        []( SIXTRL_BE_ARGPTR_DEC E& mp, const_real_arg_t hxl )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_hxl(
                std::addressof( mp ), hxl ) )
                throw std::runtime_error(
                    "Error during running st::Multipole_set_hxl" );
            return std::addressof( mp ); }, py::arg( "hxl" ) );

        multipole_obj.def( "set_hyl",
        []( SIXTRL_BE_ARGPTR_DEC E& mp, const_real_arg_t hyl )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_hyl(
                std::addressof( mp ), hyl ) )
                throw std::runtime_error(
                    "Error during running st::Multipole_set_hyl" );
            return std::addressof( mp ); }, py::arg( "hyl" ) );

        multipole_obj.def( "set_bal_value",
        []( SIXTRL_BE_ARGPTR_DEC E& mp, const_order_arg_t idx,
            const_real_arg_t bal_value )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_bal_value(
                std::addressof( mp ), idx, bal_value ) )
                throw std::runtime_error(
                    "Error during running st::Multipole_set_bal_value" );
            return std::addressof( mp );
        }, py::arg( "bal_idx" ), py::arg( "bal_value" ) );

        multipole_obj.def( "__setitem__",
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_order_arg_t ii,
            const_real_arg_t bal_value )
        {
            auto ptr_elem = std::addressof( elem );

            if( ( ii < order_t{ 0 } ) ||
                ( ii >= st::Multipole_bal_length( ptr_elem ) ) )
            {
                std::ostringstream a2str;
                a2str << "illegal bal_index=" << ii << ", bal_length="
                      << st::Multipole_bal_length( ptr_elem );
                throw std::runtime_error( a2str.str() );
            }

            st::Multipole_set_bal_value( ptr_elem, ii, bal_value );
        }, py::arg( "bal_idx" ), py::arg( "bal_value" ) );

        multipole_obj.def( "set_all_bal",
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_real_arg_t bal_value )
        {
            auto ptr_elem = std::addressof( elem );
            if( st::ARCH_STATUS_SUCCESS !=
                st::Multipole_set_all_bal_values( ptr_elem, bal_value ) )
            {
                throw std::runtime_error(
                    "Error during st::Multipole_set_all_bal_values()" );
            }

            return ptr_elem; }, py::arg( "bal_value" ) );

        multipole_obj.def( "set_knl",
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_order_arg_t ii,
            const_real_arg_t knl_value )
        {
            auto ptr_elem = std::addressof( elem );
            if( ( ii < order_t{ 0 } ) ||
                ( ii > st::Multipole_order( ptr_elem ) ) )
            {
                std::ostringstream a2str;
                a2str << "illegal knl_index=" << ii
                      << ", order=" << st::Multipole_order( ptr_elem );
                throw std::runtime_error( a2str.str() );
            }

            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_knl_value(
                    ptr_elem, ii, knl_value ) )
            {
                throw std::runtime_error(
                    "error during st::Multipole_set_knl_value" );
            }

            return ptr_elem;
        }, py::arg( "knl_index" ), py::arg( "knl_value" ) );

        multipole_obj.def( "set_all_knl",
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_real_arg_t knl_value )
        {
            auto ptr_elem = std::addressof( elem );
            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_all_knl_values(
                ptr_elem, knl_value ) )
            {
                std::ostringstream a2str;
                a2str << "error during setting "
                      << "st::Multipole_set_all_knl_values";
                throw std::runtime_error( a2str.str() );
            }

            return ptr_elem;
        }, py::arg( "knl_value" ) );

        multipole_obj.def( "set_ksl",
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_order_arg_t ii,
            const_real_arg_t ksl_value )
        {
            auto ptr_elem = std::addressof( elem );
            if( ( ii < order_t{ 0 } ) ||
                ( ii > st::Multipole_order( ptr_elem ) ) )
            {
                std::ostringstream a2str;
                a2str << "illegal ksl_index=" << ii
                      << ", order=" << st::Multipole_order( ptr_elem );
                throw std::runtime_error( a2str.str() );
            }

            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_ksl_value(
                    ptr_elem, ii, ksl_value ) )
            {
                throw std::runtime_error(
                    "error during st::Multipole_set_ksl_value" );
            }

            return ptr_elem;
        }, py::arg( "ksl_index" ), py::arg( "ksl_value" ) );

        multipole_obj.def( "set_all_ksl",
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_real_arg_t ksl_value )
        {
            auto ptr_elem = std::addressof( elem );
            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_all_ksl_values(
                ptr_elem, ksl_value ) )
            {
                std::ostringstream a2str;
                a2str << "error during setting "
                      << "st::Multipole_set_all_ksl_values";
                throw std::runtime_error( a2str.str() );
            }

            return ptr_elem;
        }, py::arg( "ksl_value" ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
         !SIXTRL_CXX_NAMESPACE::Multipole_is_type< E >() ||
         !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
         void >::type
     setup_be_multipole_cobjects_direct_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( elem_obj ),
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
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        void >::type
    setup_be_multipole_cobjects_direct_bindings(
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
        typedef typename st::MultipoleTraits< E >::real_t real_t;

        typedef typename st::TypeMethodParamTraits< real_t
            >::const_argument_type const_real_arg_t;

        typedef typename st::MultipoleTraits< E >::order_t order_t;

        typedef typename st::TypeMethodParamTraits< order_t
            >::const_argument_type const_order_arg_t;

        st::python::setup_cobjects_store_direct_base_for_type< E >(
            m, elem_obj, cbuffer_view_obj, cbuffer_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* free methods / functions */

        typedef st::CBuffer cbuffer_t;

        elem_obj.def_static( "create_new",
        []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& SIXTRL_RESTRICT_REF cbuffer,
            const_order_arg_t order, const_order_arg_t bal_capacity )
        {
            auto ptr_elem = cbuffer.create_new< E >( order, bal_capacity );
            if( ptr_elem == nullptr ) throw std::runtime_error(
                    "Unable to create multipole on cbuffer" );
            return py::cast( ptr_elem );
        }, py::arg( "cbuffer" ), py::arg( "order" ),
           py::arg( "bal_capacity" ) = order_t{ 2 } );

        elem_obj.def_static( "add",
        []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& cbuffer,
            const_order_arg_t order, const_real_arg_t length,
            const_real_arg_t hxl, const_real_arg_t hyl,
            const_order_arg_t bal_capacity, st::be_address_t const bal_addr )
            {
                auto ptr_elem = cbuffer.add< E >( order, length, hxl, hyl,
                    bal_addr, bal_capacity );

                if( ptr_elem == nullptr ) throw std::runtime_error(
                        "Unable to create multipole on cbuffer" );

                return ptr_elem;
            },
            py::arg( "cbuffer" ), py::arg( "order" ),
            py::arg( "length" ) = st::Multipole_default_length< E >(),
            py::arg( "hxl" ) = st::Multipole_default_hxl< E >(),
            py::arg( "hyl" ) = st::Multipole_default_hyl< E >(),
            py::arg( "bal_capacity" ) = order_t{ 0 },
            py::arg( "bal_addr" ) = st::be_address_t{ 0 } );

        elem_obj.def_static( "add",
        []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& cbuffer,
            const_order_arg_t order, const_real_arg_t length,
            const_real_arg_t hxl, const_real_arg_t hyl,
            py::array_t< real_t, py::array::c_style |
                         py::array::forcecast > bal_values,
            const_order_arg_t bal_capacity )
            {
                 py::buffer_info bal_values_info = bal_values.request();

                 if( bal_values_info.ndim != 1 )
                 {
                     throw std::runtime_error(
                         "bal_values array is required to be a 1d array" );
                 }

                auto ptr_elem = cbuffer.add< E >( order, length, hxl, hyl,
                    st::be_address_t{ 0 }, bal_capacity );

                if( ptr_elem == nullptr ) throw std::runtime_error(
                        "Unable to create multipole on cbuffer" );

                std::size_t num_in_bal_values = bal_values.size();

                if( ( st::Multipole_order( ptr_elem ) < order_t{ 0 } ) ||
                    ( st::Multipole_const_bal_begin( ptr_elem ) == nullptr ) ||
                    ( ( num_in_bal_values % std::size_t{ 2 } ) !=
                        std::size_t{ 0 } ) )
                {
                    throw std::runtime_error( "illegal multipole configuration" );
                }

                if( ( ptr_elem != nullptr ) &&
                    ( st::Multipole_order( ptr_elem ) >= order_t{ 0 } ) &&
                    ( st::Multipole_const_bal_begin( ptr_elem ) == nullptr ) &&
                    ( num_in_bal_values % std::size_t{ 2 } ==
                      std::size_t{ 0 } ) )
                {
                    std::size_t const cur_num_bal_values = static_cast<
                        std::size_t >( st::Multipole_bal_length( ptr_elem ) );

                    if( num_in_bal_values >= cur_num_bal_values )
                        num_in_bal_values  = cur_num_bal_values;

                    st::arch_status_t status = st::ARCH_STATUS_SUCCESS;
                    std::size_t ii = std::size_t{ 0 };

                    while( ( ii < num_in_bal_values ) &&
                           ( status == st::ARCH_STATUS_SUCCESS ) )
                    {
                        status = st::Multipole_set_bal_value(
                            ptr_elem, ii, bal_values.data( ii ) );
                    }

                    if( st::ARCH_STATUS_SUCCESS != status )
                    {
                        throw std::runtime_error(
                            "Error during setting the bal values" );
                    }
                }

                return ptr_elem;
            },
            py::arg( "cbuffer" ), py::arg( "order" ),
            py::arg( "length" ) = st::Multipole_default_length< E >(),
            py::arg( "hxl" ) = st::Multipole_default_hxl< E >(),
            py::arg( "hyl" ) = st::Multipole_default_hyl< E >(),
            py::arg( "bal_values" ) = py::array_t< real_t,
                              py::array::c_style | py::array::forcecast >{},
            py::arg( "bal_capacity" ) = order_t{ 0 } );

        elem_obj.def_static( "add", []( cbuffer_t& cbuffer,
            py::array_t< real_t, py::array::c_style |
                         py::array::forcecast > knl_values,
            py::array_t< real_t, py::array::c_style |
                         py::array::forcecast > ksl_values,
            const_real_arg_t length, const_real_arg_t hxl, const_real_arg_t hyl,
            const_order_arg_t bal_capacity )
            {
                py::buffer_info knl_values_info = knl_values.request();
                py::buffer_info ksl_values_info = ksl_values.request();

                if( knl_values_info.ndim != 1 )
                {
                    throw std::runtime_error(
                        "knl_values array is required to be a 1d array" );
                }

                if( ksl_values_info.ndim != 1 )
                {
                    throw std::runtime_error(
                        "ksl_values array is required to be a 1d array" );
                }

                order_t const knl_size = knl_values.size();
                order_t const ksl_size = ksl_values.size();
                order_t const bal_size = ( knl_size >= ksl_size )
                    ? knl_size : ksl_size;

                order_t const order = ( bal_size > order_t{ 0 } )
                    ? bal_size - order_t{ 1 } : order_t{ 0 };

                auto ptr_elem = cbuffer.add< E >( order, length, hxl, hyl,
                    st::be_address_t{ 0 }, bal_capacity );

                if( ptr_elem == nullptr ) throw std::runtime_error(
                        "Unable to create multipole on cbuffer" );

                if( ( st::Multipole_order( ptr_elem ) < order_t{ 0 } ) ||
                    ( st::Multipole_const_bal_begin( ptr_elem ) == nullptr ) )
                {
                    throw std::runtime_error( "illegal multipole configuration" );
                }

                if( ( ptr_elem != nullptr ) &&
                    ( st::Multipole_order( ptr_elem ) == order ) &&
                    ( st::Multipole_const_bal_begin( ptr_elem ) == nullptr ) )
                {
                    st::arch_status_t status = st::Multipole_set_all_bal_values(
                        ptr_elem, real_t{ 0 } );

                    order_t ii = order_t{ 0 };

                    while( ( ii < knl_size ) &&
                           ( status == st::ARCH_STATUS_SUCCESS ) )
                    {
                        status = st::Multipole_set_knl_value(
                            ptr_elem, ii, knl_values.data( ii ) );
                    }

                    ii = order_t{ 0 };

                    while( ( ii < ksl_size ) &&
                           ( status == st::ARCH_STATUS_SUCCESS ) )
                    {
                        status = st::Multipole_set_ksl_value(
                            ptr_elem, ii, ksl_values.data( ii ) );
                    }

                    if( st::ARCH_STATUS_SUCCESS != status )
                    {
                        throw std::runtime_error(
                            "Error during setting the bal values" );
                    }
                }

                return ptr_elem;
            },
            py::arg( "cbuffer" ),
            py::arg( "knl_values" ) = py::array_t< real_t,
                              py::array::c_style | py::array::forcecast >{},
            py::arg( "ksl_values" ) = py::array_t< real_t,
                              py::array::c_style | py::array::forcecast >{},
            py::arg( "length" ) = st::Multipole_default_length< E >(),
            py::arg( "hxl" ) = st::Multipole_default_hxl< E >(),
            py::arg( "hyl" ) = st::Multipole_default_hyl< E >(),
            py::arg( "bal_capacity" ) = order_t{ 0 } );
    }

    /* --------------------------------------------------------------------- */

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(), void >::type
    setup_be_multipole_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< MultipoleT >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( elem_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_view_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_obj ),
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_particle_dummy ) = nullptr )
    {
        return;
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(), void >::type
    setup_be_multipole_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< MultipoleT >& SIXTRL_RESTRICT_REF elem_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT_REF cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_elem_dummy ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::MultipoleTraits< MultipoleT >::real_t real_t;

        st::python::setup_be_multipole_base_api_bindings<
            MultipoleT >( m, elem_obj );

        st::python::setup_be_multipole_real_api_bindings<
            MultipoleT, real_t >( m, elem_obj );

        if( ( cbuffer_view_obj != nullptr ) && ( cbuffer_obj != nullptr ) )
        {
            st::python::setup_cobjects_load_store_for_type< MultipoleT
                >( m, elem_obj, *cbuffer_view_obj, *cbuffer_obj );

            st::python::setup_be_multipole_cobjects_direct_bindings< MultipoleT
                >( m, elem_obj, *cbuffer_view_obj, *cbuffer_obj );
        }
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */



#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_PYTHON_BYINDINGS_CXX_HPP__ */
