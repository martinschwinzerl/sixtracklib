#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_PYTHON_BYINDINGS_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_PYTHON_BYINDINGS_CXX_HPP__
/* SRotation Beam Element */

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
#include "sixtracklib/common/beam_elements/srotation.hpp"
#include "sixtracklib/common/internal/compiler_compability.h"
#include "sixtracklib/common/internal/type_store_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< E >(), void >::type
    setup_be_srotation_base_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( srotation_obj ) )
    {
        return;
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< E >(), void >::type
    setup_be_srotation_base_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF srotation_obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef typename st::SRotationTraits< E >::real_t real_t;
        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_existing_type const_real_existing_t;

        srotation_obj.def( py::init( []( const_real_arg_t cos_z,
                                         const_real_arg_t sin_z )
        {
            auto ptr_elem = st::make_unique< E >();
            if( st::ARCH_STATUS_SUCCESS !=
                st::SRotation_init( ptr_elem.get(), cos_z, sin_z ) )
            {
                ptr_elem.reset( nullptr );
            }

            return std::move( ptr_elem );
        } ),
        py::arg( "cos_z" ) = st::SRotation_default_cos_z< E >(),
        py::arg( "sin_z" ) = st::SRotation_default_sin_z< E >() );

        srotation_obj.def( py::init( []( const_real_arg_t angle_deg )
        {
            auto ptr_elem = st::make_unique< E >();
            if( st::ARCH_STATUS_SUCCESS !=
                st::SRotation_init( ptr_elem.get(), angle_deg ) )
            {
                ptr_elem.reset( nullptr );
            }

            return std::move( ptr_elem );
        } ),
        py::arg( "angle_deg" ) = real_t{ 0 } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        srotation_obj.def_property( "cos_z",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_real_existing_t
        {
            return st::SRotation_cos_z( std::addressof( elem ) );
        },
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_real_arg_t cos_z )
        {
            if( st::ARCH_STATUS_SUCCESS != st::SRotation_set_cos_z(
                    std::addressof( elem ), cos_z ) )
            {
                throw std::runtime_error(
                    "Error during st::SRotation_set_cos_z" );
            }
        } );

        srotation_obj.def_property( "sin_z",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_real_existing_t
        {
            return st::SRotation_sin_z( std::addressof( elem ) );
        },
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_real_arg_t sin_z )
        {
            if( st::ARCH_STATUS_SUCCESS != st::SRotation_set_sin_z(
                    std::addressof( elem ), sin_z ) )
            {
                throw std::runtime_error(
                    "Error during st::SRotation_set_sin_z" );
            }
        } );

        srotation_obj.def_property( "angle_deg",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_real_existing_t
        {
            return st::SRotation_angle_deg( std::addressof( elem ) );
        },
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_real_arg_t angle_deg )
        {
            return st::SRotation_update_angle_deg(
                std::addressof( elem ), angle_deg );
        } );

        srotation_obj.def_property( "angle_rad",
        []( SIXTRL_BE_ARGPTR_DEC E const& elem ) -> const_real_existing_t
        {
            return st::SRotation_angle_rad( std::addressof( elem ) );
        },
        []( SIXTRL_BE_ARGPTR_DEC E& elem, const_real_arg_t angle_rad )
        {
            return st::SRotation_update_angle_rad(
                std::addressof( elem ), angle_rad );
        } );

        srotation_obj.def( "__repr__", []( SIXTRL_BE_ARGPTR_DEC E const& elem )
        {
            std::ostringstream a2str;
            a2str << "<sixtrack::SRotation: cos_z="
                  << st::SRotation_cos_z( std::addressof( elem ) ) << "\r\n"
                  << "                      sin_z="
                  << st::SRotation_sin_z( std::addressof( elem ) ) << "\r\n"
                  << "                  angle_deg="
                  << st::SRotation_angle_deg( std::addressof( elem ) )
                  << "\r\n" << ">";
            return a2str.str(); } );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E, class RealType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< E >(), void >::type
    setup_be_srotation_real_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( srotation_obj ) )
    {
        return;
    }

    template< class E, class RealType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< E >(), void >::type
    setup_be_srotation_real_api_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF srotation_obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef typename std::decay< RealType >::type real_t;
        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        srotation_obj.def( "set_cos_z",
        []( SIXTRL_BE_ARGPTR_DEC E& SIXTRL_RESTRICT_REF elem,
            const_real_arg_t cos_z_value )
        {
            if( st::ARCH_STATUS_SUCCESS != st::SRotation_set_cos_z(
                    std::addressof( elem ), cos_z_value ) )
                throw std::runtime_error( "Error during setting cos_z" );
            return std::addressof( elem );
        }, py::arg( "cos_z" ) );

        srotation_obj.def( "set_sin_z",
        []( SIXTRL_BE_ARGPTR_DEC E& SIXTRL_RESTRICT_REF elem,
            const_real_arg_t sin_z_value )
        {
            if( st::ARCH_STATUS_SUCCESS != st::SRotation_set_sin_z(
                    std::addressof( elem ), sin_z_value ) )
                throw std::runtime_error( "Error during setting sin_z" );
            return std::addressof( elem );
        }, py::arg( "sin_z" ) );

        srotation_obj.def( "update_angle_deg",
        []( SIXTRL_BE_ARGPTR_DEC E& SIXTRL_RESTRICT_REF elem,
            const_real_arg_t angle_deg )
        {
            if( st::ARCH_STATUS_SUCCESS != st::SRotation_update_angle_deg(
                    std::addressof( elem ), angle_deg ) )
                throw std::runtime_error( "Error during setting angle (in deg)" );
            return std::addressof( elem );
        }, py::arg( "angle_deg" ) );

        srotation_obj.def( "update_angle_rad",
        []( SIXTRL_BE_ARGPTR_DEC E& SIXTRL_RESTRICT_REF elem,
            const_real_arg_t angle_rad )
        {
            if( st::ARCH_STATUS_SUCCESS != st::SRotation_update_angle_rad(
                    std::addressof( elem ), angle_rad ) )
                throw std::runtime_error( "Error during setting angle (in rad)" );
            return std::addressof( elem );
        }, py::arg( "angle_rad" ) );
    }

     /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
         !SIXTRL_CXX_NAMESPACE::SRotation_is_type< E >() ||
         !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
         void >::type
     setup_be_srotation_cobjects_direct_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( srotation_obj ),
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
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        void >::type
    setup_be_srotation_cobjects_direct_bindings(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< E >& SIXTRL_RESTRICT_REF srotation_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >&
            SIXTRL_RESTRICT_REF cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >&
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_BE_ARGPTR_DEC const E *const
            SIXTRL_UNUSED( ptr_dummy ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
        typedef typename st::SRotationTraits< E >::real_t real_t;

        typedef typename st::TypeMethodParamTraits< real_t
            >::const_argument_type const_real_arg_t;

        st::python::setup_cobjects_store_direct_base_for_type< E >(
            m, srotation_obj, cbuffer_view_obj, cbuffer_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* free methods / functions */

        srotation_obj.def_static( "create_new",
        []( SIXTRL_BUFFER_ARGPTR_DEC st::CBuffer& SIXTRL_RESTRICT_REF cbuffer )
        {
            auto ptr_elem = cbuffer.create_new< E >();
            if( ptr_elem == nullptr ) throw std::runtime_error(
                    "Unable to create srotation on cbuffer" );
            return ptr_elem;
        }, py::arg( "cbuffer" ) );

        srotation_obj.def_static( "add",
        []( SIXTRL_BUFFER_ARGPTR_DEC st::CBuffer& SIXTRL_RESTRICT_REF cbuffer,
            const_real_arg_t cos_z, const_real_arg_t sin_z )
        {
            auto ptr_elem = cbuffer.add< E >( cos_z, sin_z );
            if( ptr_elem == nullptr ) throw std::runtime_error(
                    "Unable to create srotation on cbuffer" );
            return ptr_elem;
        }, py::arg( "cbuffer" ), py::arg( "cos_z" ), py::arg( "sin_z" ) );

        srotation_obj.def_static( "add",
        [](  SIXTRL_BUFFER_ARGPTR_DEC st::CBuffer& SIXTRL_RESTRICT_REF cbuffer,
             const_real_arg_t angle_deg )
        {
            auto ptr_elem = cbuffer.add< E >( angle_deg );
            if( ptr_elem == nullptr ) throw std::runtime_error(
                    "Unable to create srotation on cbuffer" );
            return ptr_elem;
        }, py::arg( "cbuffer" ), py::arg( "angle_deg" ) );
    }

    /* --------------------------------------------------------------------- */

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(), void >::type
    setup_be_srotation_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< SRotationT >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( elem_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_view_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_obj ),
        SIXTRL_BE_ARGPTR_DEC const SRotationT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_particle_dummy ) = nullptr )
    {
        return;
    }

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(), void >::type
    setup_be_srotation_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< SRotationT >& SIXTRL_RESTRICT_REF elem_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT_REF cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_BE_ARGPTR_DEC const SRotationT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_elem_dummy ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::SRotationTraits< SRotationT >::real_t real_t;

        st::python::setup_be_srotation_base_api_bindings<
            SRotationT >( m, elem_obj );

        st::python::setup_be_srotation_real_api_bindings<
            SRotationT, real_t >( m, elem_obj );

        if( ( cbuffer_view_obj != nullptr ) && ( cbuffer_obj != nullptr ) )
        {
            st::python::setup_cobjects_load_store_for_type< SRotationT
                >( m, elem_obj, *cbuffer_view_obj, *cbuffer_obj );

            st::python::setup_be_srotation_cobjects_direct_bindings< SRotationT
                >( m, elem_obj, *cbuffer_view_obj, *cbuffer_obj );
        }
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_PYTHON_BYINDINGS_CXX_HPP__ */
