#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_PYTHON_BYINDINGS_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_PYTHON_BYINDINGS_CXX_HPP__
/* XYShift Beam Element */

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
#include "sixtracklib/common/beam_elements/xy_shift.hpp"
#include "sixtracklib/common/internal/compiler_compability.h"
#include "sixtracklib/common/internal/type_store_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< E >(), void >::type
    setup_be_xy_shift_base_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( elem ) )
    {
        return;
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< E >(), void >::type
    setup_be_xy_shift_base_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef typename st::XYShiftTraits< E >::real_t real_t;
        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_existing_type const_real_existing_t;

        static_assert( st::XYShift_is_type< E >(),
                       "E required to be a xy_shift class" );

        elem.def( py::init( []( const_real_arg_t dx, const_real_arg_t dy )
        {
            auto ptr_elem = st::make_unique< E >();
            if( st::ARCH_STATUS_SUCCESS !=
                st::XYShift_init( ptr_elem.get(), dx, dy ) )
            {
                ptr_elem.reset( nullptr );
            }

            return std::move( ptr_elem );
        } ),
        py::arg( "dx" ) = st::XYShift_default_dx< E >(),
        py::arg( "dy" ) = st::XYShift_default_dy< E >() );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        elem.def_property( "dx",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_real_existing_t
        {
            return st::XYShift_dx( std::addressof( elem ) );
        },
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_real_arg_t dx )
        {
            if( st::ARCH_STATUS_SUCCESS != st::XYShift_set_dx(
                    std::addressof( elem ), dx ) )
            {
                throw std::runtime_error(
                    "Error during st::XYShift_set_dx" );
            }
        } );

        elem.def_property( "dy",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_real_existing_t
        {
            return st::XYShift_dy( std::addressof( elem ) );
        },
        []( XYShift& elem, const_real_arg_t dy )
        {
            if( st::ARCH_STATUS_SUCCESS != st::XYShift_set_dy(
                    std::addressof( elem ), dy ) )
            {
                throw std::runtime_error(
                    "Error during st::XYShift_set_dy" );
            }
        } );

        elem.def( "__repr__", []( SIXTRL_BE_ARGPTR_DEC E const& elem )
        {
            std::ostringstream a2str;
            a2str << "<sixtrack::XYShift: dx="
                  << st::XYShift_dx( std::addressof( elem ) ) << "\r\n"
                  << "                    dy="
                  << st::XYShift_dy( std::addressof( elem ) ) << "\r\n"
                  << ">";
            return a2str.str(); } );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E, class RealType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< E >(), void >::type
    setup_be_xy_shift_real_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( xy_shift_obj ) )
    {
        return;
    }

    template< class E, class RealType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< E >(), void >::type
    setup_be_xy_shift_real_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF xy_shift_obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef typename std::decay< RealType >::type real_t;
        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        xy_shift_obj.def( "set_dx",
        []( SIXTRL_BE_ARGPTR_DEC E& SIXTRL_RESTRICT_REF elem,
            const_real_arg_t dx )
        {
            if( st::ARCH_STATUS_SUCCESS != st::XYShift_set_dx(
                std::addressof( elem ), dx ) )
                throw std::runtime_error( "Error during set dx" );
            return std::addressof( elem );
        }, py::arg( "dx" ) );

        xy_shift_obj.def( "set_dy",
        []( SIXTRL_BE_ARGPTR_DEC E& SIXTRL_RESTRICT_REF elem,
            const_real_arg_t dy )
        {
            if( st::ARCH_STATUS_SUCCESS != st::XYShift_set_dy(
                std::addressof( elem ), dy ) )
                throw std::runtime_error( "Error during set dy" );
            return std::addressof( elem );
        }, py::arg( "dy" ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
         !SIXTRL_CXX_NAMESPACE::XYShift_is_type< E >() ||
         !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
         void >::type
     setup_be_xy_shift_cobjects_direct_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( xy_shift_obj ),
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
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        void >::type
    setup_be_xy_shift_cobjects_direct_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< E >& SIXTRL_RESTRICT_REF xy_shift_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >&
            SIXTRL_RESTRICT_REF cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >&
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_BE_ARGPTR_DEC const E *const
            SIXTRL_UNUSED( ptr_dummy ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
        typedef typename st::XYShiftTraits< E >::real_t real_t;

        typedef typename st::TypeMethodParamTraits< real_t
            >::const_argument_type const_real_arg_t;

        st::python::setup_cobjects_store_direct_base_for_type< E >(
            m, xy_shift_obj, cbuffer_view_obj, cbuffer_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* free methods / functions */

        xy_shift_obj.def_static( "create_new",
        []( SIXTRL_BUFFER_ARGPTR_DEC st::CBuffer& cbuffer )
        {
            auto ptr_elem = cbuffer.create_new< E >();
            if( ptr_elem == nullptr ) throw std::runtime_error(
                    "Unable to create xy_shift on cbuffer" );
            return ptr_elem;
        }, py::arg( "cbuffer" ) );

        xy_shift_obj.def_static( "add",
        []( SIXTRL_BUFFER_ARGPTR_DEC st::CBuffer& cbuffer,
            const_real_arg_t dx, const_real_arg_t dy )
        {
            auto ptr_elem = cbuffer.add< E >( dx, dy );
            if( ptr_elem == nullptr ) throw std::runtime_error(
                "Unable to create xy_shift on cbuffer" );
            return ptr_elem;
        }, py::arg( "cbuffer" ), py::arg( "dx" ), py::arg( "dy" ) );

    }

    /* --------------------------------------------------------------------- */

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(), void >::type
    setup_be_xy_shift_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< XYShiftT >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( elem_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_view_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_obj ),
        SIXTRL_BE_ARGPTR_DEC const XYShiftT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_particle_dummy ) = nullptr )
    {
        return;
    }

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(), void >::type
    setup_be_xy_shift_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< XYShiftT >& SIXTRL_RESTRICT_REF elem_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT_REF cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_BE_ARGPTR_DEC const XYShiftT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_elem_dummy ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::XYShiftTraits< XYShiftT >::real_t real_t;

        st::python::setup_be_xy_shift_base_api_bindings<
            XYShiftT >( m, elem_obj );

        st::python::setup_be_xy_shift_real_api_bindings<
            XYShiftT, real_t >( m, elem_obj );

        if( ( cbuffer_view_obj != nullptr ) && ( cbuffer_obj != nullptr ) )
        {
            st::python::setup_cobjects_load_store_for_type< XYShiftT
                >( m, elem_obj, *cbuffer_view_obj, *cbuffer_obj );

            st::python::setup_be_xy_shift_cobjects_direct_bindings< XYShiftT
                >( m, elem_obj, *cbuffer_view_obj, *cbuffer_obj );
        }
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_PYTHON_BYINDINGS_CXX_HPP__ */
