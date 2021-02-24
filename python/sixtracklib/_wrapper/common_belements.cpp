#include "python/sixtracklib/_wrapper/common_belements.h"

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/generated/config.h"
#include "sixtracklib/common/beam_elements/definitions.h"
#include "sixtracklib/common/beam_elements/all_beam_elements.h"
#include "sixtracklib/common/beam_elements/all_tracking_maps.h"

#if defined( SIXTRL_DEMOTRACK_ENABLED ) && ( SIXTRL_DEMOTRACK_ENABLED == 1 )
#include "sixtracklib/common/beam_elements/demotrack.h"
#endif /* SIXTRL_DEMOTRACK_ENABLED */

#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/internal/math_factorial.h"
#include "sixtracklib/common/particles/definitions.h"
#include "sixtracklib/common/particles/particles.h"
#include "sixtracklib/common/particles/particles_addr.h"

#include <sstream>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include "python/sixtracklib/_wrapper/cxx11_optional.h"
#include "python/sixtracklib/_wrapper/buffer_protocol.h"
#include "python/sixtracklib/_wrapper/init_helper.h"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    namespace
    {
        namespace py   = pybind11;
        namespace st   = SIXTRL_CXX_NAMESPACE;
        namespace stpy = SIXTRL_CXX_NAMESPACE::python;
    }

    void InitHelper_common_belements( stpy::InitHelper& root )
    {
        using size_type = st::size_type;
        using real_type = st::be_real_type;

        stpy::InitHelper_common_belements_sc_coasting( root );
        stpy::InitHelper_common_belements_sc_qgauss( root );
        stpy::InitHelper_common_belements_cavity( root );
        stpy::InitHelper_common_belements_dipedge( root );
        stpy::InitHelper_common_belements_drift( root );
        stpy::InitHelper_common_belements_drift_exact( root );
        stpy::InitHelper_common_belements_end_tracking( root );
        stpy::InitHelper_common_belements_limit_rect( root );
        stpy::InitHelper_common_belements_limit_ellipse( root );
        stpy::InitHelper_common_belements_limit_rect_ellipse( root );
        stpy::InitHelper_common_belements_monitor( root );
        stpy::InitHelper_common_belements_multipole( root );
        stpy::InitHelper_common_belements_rf_multipole( root );
        stpy::InitHelper_common_belements_srotation( root );
        stpy::InitHelper_common_belements_xyshift( root );

        stpy::InitHelper_common_belements_demotrack( root );
    }

    void InitHelper_common_belements_sc_coasting( stpy::InitHelper& root )
    {
        using elem_type = ::NS(SCCoasting);
        using real_type = ::NS(be_real_type);
        using size_type = ::NS(cobj_size_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.be_sc_coasting_type;

        obj.def( py::init( [](
            cbuffer_view_type& cbuffer, real_type const number_of_particles,
            real_type const circumference,
            real_type const sigma_x, real_type const sigma_y,
            real_type const length, real_type const x_co, real_type const y_co,
            real_type const min_sigma_diff, bool const is_enabled )
        {
            return std::unique_ptr< ::NS(SCCoasting), py::nodelete >(
                ::NS(SCCoasting_cbuffer_add)( cbuffer.as_c_api(),
                    number_of_particles, circumference, sigma_x, sigma_y,
                        length, x_co, y_co, min_sigma_diff, is_enabled ) );
        } ), "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ),
        py::arg( "number_of_particles" ) =
            ::NS(SCCoasting_default_number_of_particles)(),
        py::arg( "circumference" ) = ::NS(SCCoasting_default_circumference)(),
        py::arg( "sigma_x" ) = ::NS(SCCoasting_default_sigma_x)(),
        py::arg( "sigma_y" ) = ::NS(SCCoasting_default_sigma_y)(),
        py::arg( "length"  ) = ::NS(SCCoasting_default_length)(),
        py::arg( "x_co" ) = ::NS(SCCoasting_default_x_co)(),
        py::arg( "y_co" ) = ::NS(SCCoasting_default_y_co)(),
        py::arg( "min_sigma_diff" ) = ::NS(SCCoasting_default_min_sigma_diff)(),
        py::arg( "enabled" ) = true );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(SCCoasting_from_cbuffer)( cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CSCCoasting from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC elem_type*
            { return ::NS(SCCoasting_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CSCCoasting instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD",
            []( cbuffer_view_type& cbuffer,
                real_type const number_of_particles,
                real_type const circumference,
                real_type const sigma_x, real_type const sigma_y,
                real_type const length,
                real_type const x_co, real_type const y_co,
                real_type const min_sigma_diff, bool const is_enabled ) ->
                SIXTRL_BE_ARGPTR_DEC elem_type* {
                return ::NS(SCCoasting_cbuffer_add)( cbuffer.as_c_api(),
                    number_of_particles, circumference, sigma_x, sigma_y,
                        length, x_co, y_co, min_sigma_diff, is_enabled ); },
            py::return_value_policy::reference,
            "append a fully parameterised CSCCoasting instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "number_of_particles" ) =
                ::NS(SCCoasting_default_number_of_particles)(),
            py::arg( "circumference" ) = ::NS(SCCoasting_default_circumference)(),
            py::arg( "sigma_x" ) = ::NS(SCCoasting_default_sigma_x)(),
            py::arg( "sigma_y" ) = ::NS(SCCoasting_default_sigma_y)(),
            py::arg( "length"  ) = ::NS(SCCoasting_default_length)(),
            py::arg( "x_co" ) = ::NS(SCCoasting_default_x_co)(),
            py::arg( "y_co" ) = ::NS(SCCoasting_default_y_co)(),
            py::arg( "min_sigma_diff" ) =
                ::NS(SCCoasting_default_min_sigma_diff)(),
            py::arg( "enabled" ) = true );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, elem_type const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC elem_type*
            {
                return ::NS(SCCoasting_cbuffer_add_copy)( cbuffer.as_c_api(), &elem );
            },
            py::return_value_policy::reference,
            "append a copy of the CSCCoasting instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( elem_type const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC elem_type*
            {
                return ::NS(SCCoasting_cbuffer_add_copy)( cbuffer.as_c_api(), &self );
            },
            py::return_value_policy::reference,
            "append a copy of the calling CSCCoasting instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "number_of_particles",
            []( elem_type const& self ) {
                return ::NS(SCCoasting_number_of_particles)( &self ); },
            []( elem_type& self, real_type const v ) {
                return ::NS(SCCoasting_set_number_of_particles)( &self, v ); } );

        obj.def_property( "circumference",
            []( elem_type const& self ) {
                return ::NS(SCCoasting_circumference)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCCoasting_set_circumference)( &self, value ); } );

        obj.def_property( "sigma_x",
            []( elem_type const& self ) {
                return ::NS(SCCoasting_sigma_x)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCCoasting_set_sigma_x)( &self, value ); } );

        obj.def_property( "sigma_y",
            []( elem_type const& self ) {
                return ::NS(SCCoasting_sigma_y)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCCoasting_set_sigma_y)( &self, value ); } );

        obj.def_property( "length",
            []( elem_type const& self ) {
                return ::NS(SCCoasting_length)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCCoasting_set_length)( &self, value ); } );

        obj.def_property( "x_co",
            []( elem_type const& self ) {
                return ::NS(SCCoasting_x_co)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCCoasting_set_x_co)( &self, value ); } );

        obj.def_property( "y_co",
            []( elem_type const& self ) {
                return ::NS(SCCoasting_y_co)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCCoasting_set_y_co)( &self, value ); } );

        obj.def_property( "min_sigma_diff",
            []( elem_type const& self ) {
                return ::NS(SCCoasting_min_sigma_diff)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCCoasting_set_min_sigma_diff)( &self, value ); } );

        obj.def_property( "enabled",
            []( elem_type const& self ) {
                return ::NS(SCCoasting_enabled)( &self ); },
            []( elem_type& self, bool const value ) {
                return ::NS(SCCoasting_set_enabled)( &self, value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(SCCoasting_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(SCCoasting_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(SCCoasting_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(SCCoasting_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( elem_type const& self, size_type const slot_size ) {
            return ::NS(SCCoasting_cobj_required_num_bytes)( &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( elem_type& self ) {
            ::NS(SCCoasting_clear)( &self ); } );

        obj.def( "init", []( elem_type& self,
            real_type const number_of_particles,
            real_type const circumference,
            real_type const sigma_x, real_type const sigma_y,
            real_type const length,
            real_type const x_co, real_type const y_co,
            real_type const min_sigma_diff, bool const is_enabled ) {
            return ::NS(SCCoasting_init)( &self, number_of_particles,
                    circumference, sigma_x, sigma_y, length, x_co, y_co,
                        min_sigma_diff, is_enabled ); },
            "initialise a given CSCCoasting instance with a set of parameters",
            py::arg( "number_of_particles" ) =
                ::NS(SCCoasting_default_number_of_particles)(),
            py::arg( "circumference" ) = ::NS(SCCoasting_default_circumference)(),
            py::arg( "sigma_x" ) = ::NS(SCCoasting_default_sigma_x)(),
            py::arg( "sigma_y" ) = ::NS(SCCoasting_default_sigma_y)(),
            py::arg( "length"  ) = ::NS(SCCoasting_default_length)(),
            py::arg( "x_co" ) = ::NS(SCCoasting_default_x_co)(),
            py::arg( "y_co" ) = ::NS(SCCoasting_default_y_co)(),
            py::arg( "min_sigma_diff" ) =
                ::NS(SCCoasting_default_min_sigma_diff)(),
            py::arg( "enabled" ) = true );
    }

    void InitHelper_common_belements_sc_qgauss( stpy::InitHelper& root )
    {
        using elem_type = ::NS(SCQGaussProfile);
        using real_type = ::NS(be_real_type);
        using size_type = ::NS(cobj_size_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.be_sc_qgauss_type;

        obj.def( py::init( [](
            cbuffer_view_type& cbuffer, real_type const number_of_particles,
            real_type const bunchlength_rms,
            real_type const sigma_x, real_type const sigma_y,
            real_type const length, real_type const x_co, real_type const y_co,
            real_type const min_sigma_diff,
            real_type const q_param, bool const is_enabled )
        {
            return std::unique_ptr< ::NS(SCQGaussProfile), py::nodelete >(
                ::NS(SCQGaussProfile_cbuffer_add)( cbuffer.as_c_api(),
                    number_of_particles, bunchlength_rms, sigma_x, sigma_y,
                        length, x_co, y_co, min_sigma_diff, q_param,
                            is_enabled ) );
        } ), "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ),
        py::arg( "number_of_particles" ) =
            ::NS(SCQGaussProfile_default_number_of_particles)(),
        py::arg( "bunchlength_rms" ) = ::NS(SCQGaussProfile_default_bunchlength_rms)(),
        py::arg( "sigma_x" ) = ::NS(SCQGaussProfile_default_sigma_x)(),
        py::arg( "sigma_y" ) = ::NS(SCQGaussProfile_default_sigma_y)(),
        py::arg( "length"  ) = ::NS(SCQGaussProfile_default_length)(),
        py::arg( "x_co" ) = ::NS(SCQGaussProfile_default_x_co)(),
        py::arg( "y_co" ) = ::NS(SCQGaussProfile_default_y_co)(),
        py::arg( "min_sigma_diff" ) =
            ::NS(SCQGaussProfile_default_min_sigma_diff)(),
        py::arg( "q_param" ) = ::NS(SCQGaussProfile_default_q_param)(),
        py::arg( "enabled" ) = true );

        /* ----------------------------------------------------------------- */

        obj.def_static( "QGAUSS_SQRT_BETA",
            []( real_type const sigma ) -> real_type {
                return ::NS(Math_q_gauss_sqrt_beta_from_gauss_sigma)( sigma ); },
            "Calculate the Q-Gaussian equivalent to the standard deviation",
            py::arg( "sigma" ) = real_type{ 1. } );

        obj.def_static( "QGAUSS_CQ",
            []( real_type const q_param ) -> real_type {
                return ::NS(Math_q_gauss_cq)( q_param ); },
            "Calculate the cq parameter for QGaussian distribution",
            py::arg( "q" ) = real_type{ 1. } );

        obj.def_static( "QGAUSS",
            []( real_type const x, real_type const q,
                tl::optional< real_type > opt_sqrt_beta,
                tl::optional< real_type > opt_cq ) -> real_type
            {
                real_type const sqrt_beta = ( opt_sqrt_beta.has_value() )
                    ? opt_sqrt_beta.value()
                    : ::NS(Math_q_gauss_sqrt_beta_from_gauss_sigma)( 1.0 );

                real_type const cq = ( opt_cq.has_value() )
                    ? opt_cq.value() : ::NS(Math_q_gauss_cq)( q );

                return ::NS(Math_q_gauss)( x, q, sqrt_beta, cq );
            },
            "Calculate the Q-Gaussian distribution value at position x",
            py::arg( "x" ), py::arg( "q" ),
            py::arg( "sqrt_beta" ) = tl::optional< real_type >(),
            py::arg( "cq" ) = tl::optional< real_type >() );

        obj.def( "qgauss",
            []( elem_type const& self, real_type const x ) -> real_type {
                return ::NS(Math_q_gauss)( x,
                    ::NS(SCQGaussProfile_q_param)( &self ),
                    ::NS(Math_q_gauss_sqrt_beta_from_gauss_sigma)(
                        ::NS(SCQGaussProfile_bunchlength_rms)( &self ) ),
                    ::NS(SCQGaussProfile_cq)( &self ) ); },
            "calculate the q-gaussian distribution at position x for the stored parameters",
            py::arg( "x" ) );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(SCQGaussProfile_from_cbuffer)(
                cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CSCQGaussProfile from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC elem_type*
            { return ::NS(SCQGaussProfile_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CSCQGaussProfile instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD",
            []( cbuffer_view_type& cbuffer,
                real_type const number_of_particles,
                real_type const bunchlength_rms,
                real_type const sigma_x, real_type const sigma_y,
                real_type const length,
                real_type const x_co, real_type const y_co,
                real_type const min_sigma_diff,
                real_type const q_param, bool const is_enabled ) ->
                SIXTRL_BE_ARGPTR_DEC elem_type* {
                return ::NS(SCQGaussProfile_cbuffer_add)( cbuffer.as_c_api(),
                    number_of_particles, bunchlength_rms, sigma_x, sigma_y,
                        length, x_co, y_co, min_sigma_diff, q_param,
                            is_enabled ); },
            py::return_value_policy::reference,
            "append a fully parameterised CSCQGaussProfile instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "number_of_particles" ) =
                ::NS(SCQGaussProfile_default_number_of_particles)(),
            py::arg( "bunchlength_rms" ) = ::NS(SCQGaussProfile_default_bunchlength_rms)(),
            py::arg( "sigma_x" ) = ::NS(SCQGaussProfile_default_sigma_x)(),
            py::arg( "sigma_y" ) = ::NS(SCQGaussProfile_default_sigma_y)(),
            py::arg( "length"  ) = ::NS(SCQGaussProfile_default_length)(),
            py::arg( "x_co" ) = ::NS(SCQGaussProfile_default_x_co)(),
            py::arg( "y_co" ) = ::NS(SCQGaussProfile_default_y_co)(),
            py::arg( "min_sigma_diff" ) =
                ::NS(SCQGaussProfile_default_min_sigma_diff)(),
            py::arg( "q_param" ) = ::NS(SCQGaussProfile_default_q_param)(),
            py::arg( "enabled" ) = true );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, elem_type const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC elem_type*
            {
                return ::NS(SCQGaussProfile_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &elem );
            },
            py::return_value_policy::reference,
            "append a copy of the CSCQGaussProfile instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( elem_type const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC elem_type*
            {
                return ::NS(SCQGaussProfile_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &self );
            },
            py::return_value_policy::reference,
            "append a copy of the calling CSCQGaussProfile instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "number_of_particles",
            []( elem_type const& self ) {
                return ::NS(SCQGaussProfile_number_of_particles)( &self ); },
            []( elem_type& self, real_type const v ) {
                return ::NS(SCQGaussProfile_set_number_of_particles)(
                    &self, v ); } );

        obj.def_property( "bunchlength_rms",
            []( elem_type const& self ) {
                return ::NS(SCQGaussProfile_bunchlength_rms)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCQGaussProfile_set_bunchlength_rms)(
                    &self, value ); } );

        obj.def_property( "sigma_x",
            []( elem_type const& self ) {
                return ::NS(SCQGaussProfile_sigma_x)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCQGaussProfile_set_sigma_x)( &self, value ); } );

        obj.def_property( "sigma_y",
            []( elem_type const& self ) {
                return ::NS(SCQGaussProfile_sigma_y)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCQGaussProfile_set_sigma_y)( &self, value ); } );

        obj.def_property( "length",
            []( elem_type const& self ) {
                return ::NS(SCQGaussProfile_length)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCQGaussProfile_set_length)( &self, value ); } );

        obj.def_property( "x_co",
            []( elem_type const& self ) {
                return ::NS(SCQGaussProfile_x_co)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCQGaussProfile_set_x_co)( &self, value ); } );

        obj.def_property( "y_co",
            []( elem_type const& self ) {
                return ::NS(SCQGaussProfile_y_co)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCQGaussProfile_set_y_co)( &self, value ); } );

        obj.def_property( "min_sigma_diff",
            []( elem_type const& self ) {
                return ::NS(SCQGaussProfile_min_sigma_diff)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCQGaussProfile_set_min_sigma_diff)(
                    &self, value ); } );

        obj.def_property( "q_param",
            []( elem_type const& self ) {
                return ::NS(SCQGaussProfile_q_param)( &self ); },
            []( elem_type& self, real_type const value ) {
                return ::NS(SCQGaussProfile_set_q_param)( &self, value ); } );

        obj.def_property_readonly( "cq",
            []( elem_type const& self ) {
                return ::NS(SCQGaussProfile_cq)( &self ); } );

        obj.def_property( "enabled",
            []( elem_type const& self ) {
                return ::NS(SCQGaussProfile_enabled)( &self ); },
            []( elem_type& self, bool const value ) {
                return ::NS(SCQGaussProfile_set_enabled)( &self, value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(SCQGaussProfile_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(SCQGaussProfile_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(SCQGaussProfile_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(SCQGaussProfile_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( elem_type const& self, size_type const slot_size ) {
            return ::NS(SCQGaussProfile_cobj_required_num_bytes)(
                &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( elem_type& self ) {
            ::NS(SCQGaussProfile_clear)( &self ); } );

        obj.def( "init", []( elem_type& self,
            real_type const number_of_particles,
            real_type const bunchlength_rms,
            real_type const sigma_x, real_type const sigma_y,
            real_type const length,
            real_type const x_co, real_type const y_co,
            real_type const min_sigma_diff, real_type const q_param,
            bool const is_enabled ) {
            return ::NS(SCQGaussProfile_init)( &self, number_of_particles,
                    bunchlength_rms, sigma_x, sigma_y, length, x_co, y_co,
                        min_sigma_diff, q_param, is_enabled ); },
            "initialise a given CSCQGaussProfile instance with a set of parameters",
            py::arg( "number_of_particles" ) =
                ::NS(SCQGaussProfile_default_number_of_particles)(),
            py::arg( "bunchlength_rms" ) =
                ::NS(SCQGaussProfile_default_bunchlength_rms)(),
            py::arg( "sigma_x" ) = ::NS(SCQGaussProfile_default_sigma_x)(),
            py::arg( "sigma_y" ) = ::NS(SCQGaussProfile_default_sigma_y)(),
            py::arg( "length"  ) = ::NS(SCQGaussProfile_default_length)(),
            py::arg( "x_co" ) = ::NS(SCQGaussProfile_default_x_co)(),
            py::arg( "y_co" ) = ::NS(SCQGaussProfile_default_y_co)(),
            py::arg( "min_sigma_diff" ) =
                ::NS(SCQGaussProfile_default_min_sigma_diff)(),
            py::arg( "q_param" ) = ::NS(SCQGaussProfile_default_q_param)(),
            py::arg( "enabled" ) = true );
    }

    void InitHelper_common_belements_cavity( stpy::InitHelper& root )
    {
        using cavity_t          = ::NS(Cavity);
        using real_type         = ::NS(be_real_type);
        using size_type         = ::NS(cobj_size_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.be_cavity_type;

        obj.def( py::init( [](
            cbuffer_view_type& cbuffer, real_type const voltage,
            real_type const frequency, real_type  const lag )
        {
            return std::unique_ptr< ::NS(Cavity), py::nodelete >(
                ::NS(Cavity_cbuffer_add)( cbuffer.as_c_api(),
                    voltage, frequency, lag ) );
        } ),
        "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ),
        py::arg( "voltage" ) = ::NS(Cavity_default_voltage)(),
        py::arg( "frequency" ) = ::NS(Cavity_default_frequency)(),
        py::arg( "lag" ) = ::NS(Cavity_default_lag)() );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(Cavity_from_cbuffer)( cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CCavity from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC cavity_t*
            { return ::NS(Cavity_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CCavity instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD",
            []( cbuffer_view_type& cbuffer, real_type const voltage,
            real_type const frequency, real_type const lag ) ->
                SIXTRL_BE_ARGPTR_DEC cavity_t* {
                return ::NS(Cavity_cbuffer_add)( cbuffer.as_c_api(),voltage,
                    frequency, lag ); },
            py::return_value_policy::reference,
            "append a fully parameterised CCavity instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "voltage" ) = ::NS(Cavity_default_voltage)(),
            py::arg( "frequency" ) = ::NS(Cavity_default_frequency)(),
            py::arg( "lag" ) = ::NS(Cavity_default_lag)() );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, cavity_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC cavity_t*
            {
                return ::NS(Cavity_cbuffer_add_copy)( cbuffer.as_c_api(), &elem );
            },
            py::return_value_policy::reference,
            "append a copy of the CCavity instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( cavity_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC cavity_t*
            {
                return ::NS(Cavity_cbuffer_add_copy)( cbuffer.as_c_api(), &self );
            },
            py::return_value_policy::reference,
            "append a copy of the calling CCavity instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "voltage",
            []( cavity_t const& self ) { return ::NS(Cavity_voltage)( &self ); },
            []( cavity_t& self, real_type const v ) {
                ::NS(Cavity_set_voltage)( &self, v ); } );

        obj.def_property( "frequency",
            []( cavity_t const& self ) { return ::NS(Cavity_frequency)( &self ); },
            []( cavity_t& self, real_type const value ) {
                ::NS(Cavity_set_frequency)( &self, value ); } );

        obj.def_property( "lag",
            []( cavity_t const& self ) { return ::NS(Cavity_lag)( &self ); },
            []( cavity_t& self, real_type const value ) {
                ::NS(Cavity_set_lag)( &self, value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(Cavity_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(Cavity_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(Cavity_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(Cavity_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( cavity_t const& self, size_type const slot_size ) {
            return ::NS(Cavity_cobj_required_num_bytes)( &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( cavity_t& self ) {
            ::NS(Cavity_clear)( &self ); } );

        obj.def( "init", []( cavity_t& self, real_type const voltage,
                real_type const frequency, real_type const lag ) {
            return ::NS(Cavity_init)( &self, voltage, frequency, lag ); },
            "initialise a given CCavity instance with a set of parameters",
            py::arg( "voltage" ) = ::NS(Cavity_default_voltage)(),
            py::arg( "frequency" ) = ::NS(Cavity_default_frequency)(),
            py::arg( "lag" ) = ::NS(Cavity_default_lag)() );
    }

    void InitHelper_common_belements_dipedge( stpy::InitHelper& root )
    {
        using dipedge_t         = ::NS(DipoleEdge);
        using real_type         = ::NS(be_real_type);
        using size_type         = ::NS(cobj_size_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.be_dipedge_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            real_type const r21, real_type const r43 )
        {
            return std::unique_ptr< dipedge_t, py::nodelete >(
                ::NS(DipoleEdge_cbuffer_add)( cbuffer.as_c_api(), r21, r43 ) );
        } ),
        "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ),
        py::arg( "r21" ) = ::NS(DipoleEdge_default_r21)(),
        py::arg( "r43" ) = ::NS(DipoleEdge_default_r43)() );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(DipoleEdge_from_cbuffer)( cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CDipoleEdge from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC dipedge_t*
            { return ::NS(DipoleEdge_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CDipoleEdge instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD",
            []( cbuffer_view_type& cbuffer,
                real_type const r21, real_type const r43 ) ->
                SIXTRL_BE_ARGPTR_DEC dipedge_t* {
                return ::NS(DipoleEdge_cbuffer_add)( cbuffer.as_c_api(),r21, r43 ); },
            py::return_value_policy::reference,
            "append a fully parameterised CDipoleEdge instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "r21" ) = ::NS(DipoleEdge_default_r21)(),
            py::arg( "r43" ) = ::NS(DipoleEdge_default_r43)() );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, dipedge_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC dipedge_t*
            {
                return ::NS(DipoleEdge_cbuffer_add_copy)( cbuffer.as_c_api(), &elem );
            },
            py::return_value_policy::reference,
            "append a copy of the CDipoleEdge instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( dipedge_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC dipedge_t*
            {
                return ::NS(DipoleEdge_cbuffer_add_copy)( cbuffer.as_c_api(), &self );
            },
            py::return_value_policy::reference,
            "append a copy of the calling CDipoleEdge instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "r21",
            []( dipedge_t const& self ) { return ::NS(DipoleEdge_r21)( &self ); },
            []( dipedge_t& self, real_type const v ) {
                ::NS(DipoleEdge_set_r21)( &self, v ); } );

        obj.def_property( "r43",
            []( dipedge_t const& self ) { return ::NS(DipoleEdge_r43)( &self ); },
            []( dipedge_t& self, real_type const value ) {
                ::NS(DipoleEdge_set_r43)( &self, value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(DipoleEdge_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(DipoleEdge_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(DipoleEdge_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(DipoleEdge_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( dipedge_t const& self, size_type const slot_size ) {
            return ::NS(DipoleEdge_cobj_required_num_bytes)( &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( dipedge_t& self ) {
            ::NS(DipoleEdge_clear)( &self ); } );

        obj.def( "init", []( dipedge_t& self, real_type const r21,
                real_type const r43 ) {
            return ::NS(DipoleEdge_init)( &self, r21, r43 ); },
            "initialise a given CDipoleEdge instance with a set of parameters",
            py::arg( "r21" ) = ::NS(DipoleEdge_default_r21)(),
            py::arg( "r43" ) = ::NS(DipoleEdge_default_r43)() );
    }

    void InitHelper_common_belements_drift( stpy::InitHelper& root )
    {
        using drift_t           = ::NS(Drift);
        using real_type         = ::NS(be_real_type);
        using size_type         = ::NS(cobj_size_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.be_drift_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer, real_type const L ) {
            return std::unique_ptr< drift_t, py::nodelete >(
                ::NS(Drift_cbuffer_add)( cbuffer.as_c_api(), L ) ); } ),
        "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ),
        py::arg( "length" ) = ::NS(Drift_default_length)() );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(Drift_from_cbuffer)( cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CDrift from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC drift_t*
            { return ::NS(Drift_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CDrift instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD",
            []( cbuffer_view_type& cbuffer, real_type const length ) ->
                SIXTRL_BE_ARGPTR_DEC drift_t* {
                return ::NS(Drift_cbuffer_add)( cbuffer.as_c_api(), length ); },
            py::return_value_policy::reference,
            "append a fully parameterised CDrift instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "length" ) = ::NS(Drift_default_length)() );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, drift_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC drift_t*
            {
                return ::NS(Drift_cbuffer_add_copy)( cbuffer.as_c_api(), &elem );
            },
            py::return_value_policy::reference,
            "append a copy of the CDrift instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( drift_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC drift_t*
            {
                return ::NS(Drift_cbuffer_add_copy)( cbuffer.as_c_api(), &self );
            },
            py::return_value_policy::reference,
            "append a copy of the calling CDrift instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "length",
            []( drift_t const& self ) { return ::NS(Drift_length)( &self ); },
            []( drift_t& self, real_type const v ) {
                ::NS(Drift_set_length)( &self, v ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(Drift_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(Drift_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(Drift_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(Drift_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( drift_t const& self, size_type const slot_size ) {
            return ::NS(Drift_cobj_required_num_bytes)( &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( drift_t& self ) {
            ::NS(Drift_clear)( &self ); } );

        obj.def( "init", []( drift_t& self, real_type const length ) {
            return ::NS(Drift_init)( &self, length ); },
            "initialise a given CDrift instance with a set of parameters",
            py::arg( "length" ) = ::NS(Drift_default_length)() );
    }

    void InitHelper_common_belements_drift_exact( stpy::InitHelper& root )
    {
        using drift_exact_t     = ::NS(DriftExact);
        using real_type         = ::NS(be_real_type);
        using size_type         = ::NS(cobj_size_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.be_drift_exact_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer, real_type const L ) {
            return std::unique_ptr< drift_exact_t, py::nodelete >(
                ::NS(DriftExact_cbuffer_add)( cbuffer.as_c_api(), L ) ); } ),
        "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ),
        py::arg( "length" ) = ::NS(DriftExact_default_length)() );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(DriftExact_from_cbuffer)( cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CDriftExact from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC drift_exact_t*
            { return ::NS(DriftExact_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CDriftExact instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD",
            []( cbuffer_view_type& cbuffer, real_type const length ) ->
                SIXTRL_BE_ARGPTR_DEC drift_exact_t* {
                return ::NS(DriftExact_cbuffer_add)( cbuffer.as_c_api(), length ); },
            py::return_value_policy::reference,
            "append a fully parameterised CDriftExact instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "length" ) = ::NS(DriftExact_default_length)() );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, drift_exact_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC drift_exact_t*
            {
                return ::NS(DriftExact_cbuffer_add_copy)( cbuffer.as_c_api(), &elem );
            },
            py::return_value_policy::reference,
            "append a copy of the CDriftExact instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( drift_exact_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC drift_exact_t*
            {
                return ::NS(DriftExact_cbuffer_add_copy)( cbuffer.as_c_api(), &self );
            },
            py::return_value_policy::reference,
            "append a copy of the calling CDriftExact instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "length",
            []( drift_exact_t const& self ) { return ::NS(DriftExact_length)( &self ); },
            []( drift_exact_t& self, real_type const v ) {
                ::NS(DriftExact_set_length)( &self, v ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(DriftExact_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(DriftExact_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(DriftExact_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(DriftExact_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( drift_exact_t const& self, size_type const slot_size ) {
            return ::NS(DriftExact_cobj_required_num_bytes)( &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( drift_exact_t& self ) {
            ::NS(DriftExact_clear)( &self ); } );

        obj.def( "init", []( drift_exact_t& self, real_type const length ) {
            return ::NS(DriftExact_init)( &self, length ); },
            "initialise a given CDriftExact instance with a set of parameters",
            py::arg( "length" ) = ::NS(DriftExact_default_length)() );
    }

    void InitHelper_common_belements_end_tracking( stpy::InitHelper& root )
    {
        using end_tracking_t    = ::NS(EndTracking);
        using index_type        = ::NS(particle_index_type);
        using size_type         = ::NS(cobj_size_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.be_end_tracking_type;

        obj.def( py::init( [](
            cbuffer_view_type& cbuffer, index_type const next_at_element,
            size_type const next_buffer_idx, bool const ends_turn )
        {
            return std::unique_ptr< end_tracking_t, py::nodelete >(
                ::NS(EndTracking_cbuffer_add)( cbuffer.as_c_api(),
                    next_at_element, next_buffer_idx, ends_turn ) ); } ),
        "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ),
        py::arg( "next_at_element" ) = ::NS(EndTracking_default_next_at_element)(),
        py::arg( "next_buffer_idx" ) = ::NS(EndTracking_default_next_buffer_idx)(),
        py::arg( "ends_turn" ) = ::NS(EndTracking_default_ends_turn)() );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(EndTracking_from_cbuffer)( cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CEndTracking from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC end_tracking_t*
            { return ::NS(EndTracking_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CEndTracking instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD",
            []( cbuffer_view_type& cbuffer, index_type const next_at_element,
            size_type const next_buffer_idx, bool const ends_turn ) ->
                SIXTRL_BE_ARGPTR_DEC end_tracking_t* {
                return ::NS(EndTracking_cbuffer_add)( cbuffer.as_c_api(),
                    next_at_element, next_buffer_idx, ends_turn ); },
            py::return_value_policy::reference,
            "append a fully parameterised CEndTracking instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "next_at_element" ) = ::NS(EndTracking_default_next_at_element)(),
            py::arg( "next_buffer_idx" ) = ::NS(EndTracking_default_next_buffer_idx)(),
            py::arg( "ends_turn" ) = ::NS(EndTracking_default_ends_turn)() );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, end_tracking_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC end_tracking_t*
            {
                return ::NS(EndTracking_cbuffer_add_copy)( cbuffer.as_c_api(), &elem );
            },
            py::return_value_policy::reference,
            "append a copy of the CEndTracking instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( end_tracking_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC end_tracking_t*
            {
                return ::NS(EndTracking_cbuffer_add_copy)( cbuffer.as_c_api(), &self );
            },
            py::return_value_policy::reference,
            "append a copy of the calling CEndTracking instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "next_at_element",
            []( end_tracking_t const& self ) {
                 return ::NS(EndTracking_next_at_element)( &self ); },
            []( end_tracking_t& self, index_type const v ) {
                ::NS(EndTracking_set_next_at_element)( &self, v ); } );

        obj.def_property( "next_buffer_idx",
            []( end_tracking_t const& self ) {
                return ::NS(EndTracking_next_buffer_idx)( &self ); },
            []( end_tracking_t& self, size_type const value ) {
                ::NS(EndTracking_set_next_buffer_idx)( &self, value ); } );

        obj.def_property( "ends_turn",
            []( end_tracking_t const& self ) {
                return ::NS(EndTracking_ends_turn)( &self ); },
            []( end_tracking_t& self, bool const value ) {
                ::NS(EndTracking_set_ends_turn)( &self, value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(EndTracking_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(EndTracking_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(EndTracking_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(EndTracking_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( end_tracking_t const& self, size_type const slot_size ) {
            return ::NS(EndTracking_cobj_required_num_bytes)( &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( end_tracking_t& self ) {
            ::NS(EndTracking_clear)( &self ); } );

        obj.def( "init", []( end_tracking_t& self,
                index_type const next_at_element,
                size_type const next_buffer_idx, bool const ends_turn ) {
            return ::NS(EndTracking_init)( &self,
                next_at_element, next_buffer_idx, ends_turn ); },
            "initialise a given CEndTracking instance with a set of parameters",
            py::arg( "next_at_element" ) = ::NS(EndTracking_default_next_at_element)(),
            py::arg( "next_buffer_idx" ) = ::NS(EndTracking_default_next_buffer_idx)(),
            py::arg( "ends_turn" ) = ::NS(EndTracking_default_ends_turn)() );
    }

    void InitHelper_common_belements_limit_rect( stpy::InitHelper& root )
     {
        using limit_rect_t      = ::NS(LimitRect);
        using real_type         = ::NS(be_real_type);
        using size_type         = ::NS(cobj_size_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.be_limit_rect_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            real_type const x_min, real_type const x_max,
            real_type const y_min, real_type const y_max ) {
            return std::unique_ptr< limit_rect_t, py::nodelete >(
                ::NS(LimitRect_cbuffer_add)( cbuffer.as_c_api(),
                    x_min, x_max, y_min, y_max ) ); } ),
        "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ),
        py::arg( "x_min" ) = ::NS(LimitRect_default_x_min)(),
        py::arg( "x_max" ) = ::NS(LimitRect_default_x_max)(),
        py::arg( "y_min" ) = ::NS(LimitRect_default_y_min)(),
        py::arg( "y_max" ) = ::NS(LimitRect_default_y_max)() );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(LimitRect_from_cbuffer)( cbuffer.as_c_api(),
                pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CLimitRect from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC limit_rect_t*
            { return ::NS(LimitRect_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CLimitRect instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD", []( cbuffer_view_type& cbuffer,
            real_type const x_min, real_type const x_max,
            real_type const y_min, real_type const y_max ) ->
                SIXTRL_BE_ARGPTR_DEC limit_rect_t* {
                return ::NS(LimitRect_cbuffer_add)( cbuffer.as_c_api(),x_min,
                    x_max, y_min, y_max ); },
            py::return_value_policy::reference,
            "append a fully parameterised CLimitRect instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "x_min" ) = ::NS(LimitRect_default_x_min)(),
            py::arg( "x_max" ) = ::NS(LimitRect_default_x_max)(),
            py::arg( "y_min" ) = ::NS(LimitRect_default_y_min)(),
            py::arg( "y_max" ) = ::NS(LimitRect_default_y_max)() );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, limit_rect_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC limit_rect_t*
            {
                return ::NS(LimitRect_cbuffer_add_copy)( cbuffer.as_c_api(), &elem );
            },
            py::return_value_policy::reference,
            "append a copy of the CLimitRect instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( limit_rect_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC limit_rect_t*
            {
                return ::NS(LimitRect_cbuffer_add_copy)( cbuffer.as_c_api(), &self );
            },
            py::return_value_policy::reference,
            "append a copy of the calling CLimitRect instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "x_min",
            []( limit_rect_t const& self ) {
                return ::NS(LimitRect_x_min)( &self ); },
            []( limit_rect_t& self, real_type const v ) {
                ::NS(LimitRect_set_x_min)( &self, v ); } );

        obj.def_property( "x_max",
            []( limit_rect_t const& self ) {
                return ::NS(LimitRect_x_max)( &self ); },
            []( limit_rect_t& self, real_type const value ) {
                ::NS(LimitRect_set_x_max)( &self, value ); } );

        obj.def_property( "y_min",
            []( limit_rect_t const& self ) {
                return ::NS(LimitRect_y_min)( &self ); },
            []( limit_rect_t& self, real_type const value ) {
                ::NS(LimitRect_set_y_min)( &self, value ); } );

        obj.def_property( "y_max",
            []( limit_rect_t const& self ) {
                 return ::NS(LimitRect_y_max)( &self ); },
            []( limit_rect_t& self, real_type const value ) {
                ::NS(LimitRect_set_y_max)( &self, value ); } );

        obj.def_property_readonly( "is_consistent",
            []( limit_rect_t const& self ){
                return ::NS(LimitRect_is_consistent)( &self ); } );

        obj.def( "update", []( limit_rect_t& self ){
            return ::NS(LimitRect_update)( &self ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(LimitRect_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(LimitRect_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(LimitRect_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(LimitRect_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( limit_rect_t const& self, size_type const slot_size ) {
            return ::NS(LimitRect_cobj_required_num_bytes)( &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( limit_rect_t& self ) {
            ::NS(LimitRect_clear)( &self ); } );

        obj.def( "init", []( limit_rect_t& self,
                real_type const x_min, real_type const x_max,
                real_type const y_min, real_type const y_max ) {
            return ::NS(LimitRect_init)( &self, x_min, x_max, y_min, y_max ); },
            "initialise a given CLimitRect instance with a set of parameters",
            py::arg( "x_min" ) = ::NS(LimitRect_default_x_min)(),
            py::arg( "x_max" ) = ::NS(LimitRect_default_x_max)(),
            py::arg( "y_min" ) = ::NS(LimitRect_default_y_min)(),
            py::arg( "y_max" ) = ::NS(LimitRect_default_y_max)() );
    }

    void InitHelper_common_belements_limit_ellipse( stpy::InitHelper& root )
    {
        using limit_ellipse_t   = ::NS(LimitEllipse);
        using real_type         = ::NS(be_real_type);
        using size_type         = ::NS(cobj_size_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.be_limit_ellipse_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer, real_type const a_squ,
            real_type const b_squ ) {
            return std::unique_ptr< limit_ellipse_t, py::nodelete >(
                ::NS(LimitEllipse_cbuffer_add)( cbuffer.as_c_api(),
                    a_squ, b_squ ) ); } ),
        "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ),
        py::arg( "a_squ" ) = ::NS(LimitEllipse_default_a_squ)(),
        py::arg( "b_squ" ) = ::NS(LimitEllipse_default_b_squ)() );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(LimitEllipse_from_cbuffer)( cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CLimitEllipse from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC limit_ellipse_t*
            { return ::NS(LimitEllipse_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CLimitEllipse instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD", []( cbuffer_view_type& cbuffer,
            real_type const a_squ, real_type const b_squ ) ->
                SIXTRL_BE_ARGPTR_DEC limit_ellipse_t* {
                return ::NS(LimitEllipse_cbuffer_add)(
                    cbuffer.as_c_api(),a_squ, b_squ ); },
            py::return_value_policy::reference,
            "append a fully parameterised CLimitEllipse instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "a_squ" ) = ::NS(LimitEllipse_default_a_squ)(),
            py::arg( "b_squ" ) = ::NS(LimitEllipse_default_b_squ)() );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, limit_ellipse_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC limit_ellipse_t* {
                return ::NS(LimitEllipse_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &elem ); },
            py::return_value_policy::reference,
            "append a copy of the CLimitEllipse instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( limit_ellipse_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC limit_ellipse_t* {
                return ::NS(LimitEllipse_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &self ); },
            py::return_value_policy::reference,
            "append a copy of the calling CLimitEllipse instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "a_squ",
            []( limit_ellipse_t const& self ) {
                return ::NS(LimitEllipse_a_squ)( &self ); },
            []( limit_ellipse_t& self, real_type const v ) {
                ::NS(LimitEllipse_set_a_squ)( &self, v ); } );

        obj.def_property( "b_squ",
            []( limit_ellipse_t const& self ) {
                return ::NS(LimitEllipse_b_squ)( &self ); },
            []( limit_ellipse_t& self, real_type const value ) {
                ::NS(LimitEllipse_set_b_squ)( &self, value ); } );

        obj.def_property_readonly( "a_b_squ",
            []( limit_ellipse_t const& self ) {
                return ::NS(LimitEllipse_a_b_squ)( &self ); } );

        obj.def_property_readonly( "is_consistent",
            []( limit_ellipse_t const& self ){
                return ::NS(LimitEllipse_is_consistent)( &self ); } );

        obj.def( "update", []( limit_ellipse_t& self ){
            return ::NS(LimitEllipse_update)( &self ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) {
                return ::NS(LimitEllipse_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) {
                return ::NS(LimitEllipse_cobj_num_dataptrs)(); } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(LimitEllipse_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(LimitEllipse_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( limit_ellipse_t const& self, size_type const slot_size ) {
            return ::NS(LimitEllipse_cobj_required_num_bytes)(
                &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( limit_ellipse_t& self ) {
            ::NS(LimitEllipse_clear)( &self ); } );

        obj.def( "init", []( limit_ellipse_t& self,
                real_type const a_squ, real_type const b_squ ) {
            return ::NS(LimitEllipse_init)( &self, a_squ, b_squ ); },
            "initialise a given CLimitEllipse instance with a set of parameters",
            py::arg( "a_squ" ) = ::NS(LimitEllipse_default_a_squ)(),
            py::arg( "b_squ" ) = ::NS(LimitEllipse_default_b_squ)() );
    }

    void InitHelper_common_belements_limit_rect_ellipse( stpy::InitHelper& root )
    {
        using limit_rect_ellipse_t  = ::NS(LimitRectEllipse);
        using real_type             = ::NS(be_real_type);
        using size_type             = ::NS(cobj_size_type);
        using cbuffer_view_type     = st::CBufferView;

        auto& obj = root.be_limit_rect_ellipse_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            real_type const x_max, real_type const y_max,
            real_type const a_squ, real_type const b_squ ) {
            return std::unique_ptr< limit_rect_ellipse_t, py::nodelete >(
                ::NS(LimitRectEllipse_cbuffer_add)( cbuffer.as_c_api(), x_max,
                    y_max, a_squ, b_squ ) ); } ),
        "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ),
        py::arg( "x_max" ) = ::NS(LimitRectEllipse_default_x_max)(),
        py::arg( "y_max" ) = ::NS(LimitRectEllipse_default_y_max)(),
        py::arg( "a_squ" ) = ::NS(LimitRectEllipse_default_a_squ)(),
        py::arg( "b_squ" ) = ::NS(LimitRectEllipse_default_b_squ)() );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(LimitRectEllipse_from_cbuffer)(
                cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CLimitRectEllipse from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC limit_rect_ellipse_t*
            { return ::NS(LimitRectEllipse_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CLimitRectEllipse instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD", []( cbuffer_view_type& cbuffer,
            real_type const x_max, real_type const y_max,
            real_type const a_squ, real_type const b_squ ) ->
                SIXTRL_BE_ARGPTR_DEC limit_rect_ellipse_t* {
                return ::NS(LimitRectEllipse_cbuffer_add)(
                    cbuffer.as_c_api(),x_max, y_max, a_squ, b_squ ); },
            py::return_value_policy::reference,
            "append a fully parameterised CLimitRectEllipse instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "x_max" ) = ::NS(LimitRectEllipse_default_x_max)(),
            py::arg( "y_max" ) = ::NS(LimitRectEllipse_default_y_max)(),
            py::arg( "a_squ" ) = ::NS(LimitRectEllipse_default_a_squ)(),
            py::arg( "b_squ" ) = ::NS(LimitRectEllipse_default_b_squ)() );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, limit_rect_ellipse_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC limit_rect_ellipse_t* {
                return ::NS(LimitRectEllipse_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &elem ); },
            py::return_value_policy::reference,
            "append a copy of the CLimitRectEllipse instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( limit_rect_ellipse_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC limit_rect_ellipse_t* {
                return ::NS(LimitRectEllipse_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &self ); },
            py::return_value_policy::reference,
            "append a copy of the calling CLimitRectEllipse instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "x_max",
            []( limit_rect_ellipse_t const& self ) {
                return ::NS(LimitRectEllipse_x_max)( &self ); },
            []( limit_rect_ellipse_t& self, real_type const v ) {
                ::NS(LimitRectEllipse_set_x_max)( &self, v ); } );

        obj.def_property( "y_max",
            []( limit_rect_ellipse_t const& self ) {
                return ::NS(LimitRectEllipse_y_max)( &self ); },
            []( limit_rect_ellipse_t& self, real_type const value ) {
                ::NS(LimitRectEllipse_set_y_max)( &self, value ); } );

        obj.def_property( "a_squ",
            []( limit_rect_ellipse_t const& self ) {
                return ::NS(LimitRectEllipse_a_squ)( &self ); },
            []( limit_rect_ellipse_t& self, real_type const value ) {
                ::NS(LimitRectEllipse_set_a_squ)( &self, value ); } );

        obj.def_property( "b_squ",
            []( limit_rect_ellipse_t const& self ) {
                return ::NS(LimitRectEllipse_b_squ)( &self ); },
            []( limit_rect_ellipse_t& self, real_type const value ) {
                ::NS(LimitRectEllipse_set_b_squ)( &self, value ); } );

        obj.def_property_readonly( "a_b_squ",
            []( limit_rect_ellipse_t const& self ) {
                return ::NS(LimitRectEllipse_a_b_squ)( &self ); } );

        obj.def_property_readonly( "is_consistent",
            []( limit_rect_ellipse_t const& self ){
                return ::NS(LimitRectEllipse_is_consistent)( &self ); } );

        obj.def( "update", []( limit_rect_ellipse_t& self ){
            return ::NS(LimitRectEllipse_update)( &self ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) {
                return ::NS(LimitRectEllipse_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) {
                return ::NS(LimitRectEllipse_cobj_num_dataptrs)(); } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(LimitRectEllipse_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(LimitRectEllipse_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( limit_rect_ellipse_t const& self, size_type const slot_size ) {
            return ::NS(LimitRectEllipse_cobj_required_num_bytes)(
                &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( limit_rect_ellipse_t& self ) {
            ::NS(LimitRectEllipse_clear)( &self ); } );

        obj.def( "init", []( limit_rect_ellipse_t& self,
                real_type const x_max, real_type const y_max,
                real_type const a_squ, real_type const b_squ ) {
            return ::NS(LimitRectEllipse_init)(
                &self, x_max, y_max, a_squ, b_squ ); },
            "initialise a given CLimitRectEllipse instance with a set of parameters",
            py::arg( "x_max" ) = ::NS(LimitRectEllipse_default_x_max)(),
            py::arg( "y_max" ) = ::NS(LimitRectEllipse_default_y_max)(),
            py::arg( "a_squ" ) = ::NS(LimitRectEllipse_default_a_squ)(),
            py::arg( "b_squ" ) = ::NS(LimitRectEllipse_default_b_squ)() );
    }

    void InitHelper_common_belements_monitor( stpy::InitHelper& root )
    {
        using monitor_t         = ::NS(Monitor);
        using index_type        = ::NS(particle_index_type);
        using size_type         = ::NS(cobj_size_type);
        using addr_type         = ::NS(address_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.be_monitor_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            index_type const num_stores, index_type const start,
            index_type const skip, index_type const min_particle_id,
            index_type const max_particle_id, bool const is_rolling,
            bool const is_turn_ordered, addr_type const out_addr ) {
            return std::unique_ptr< monitor_t, py::nodelete >(
                ::NS(Monitor_cbuffer_add)( cbuffer.as_c_api(), num_stores,
                    start, skip, min_particle_id, max_particle_id, is_rolling,
                        is_turn_ordered, out_addr ) ); } ),
        "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ),
        py::arg( "num_stores" ) = ::NS(Monitor_default_num_stores)(),
        py::arg( "start" ) = ::NS(Monitor_default_start)(),
        py::arg( "skip" ) = ::NS(Monitor_default_skip)(),
        py::arg( "min_particle_id" ) = ::NS(Monitor_default_min_particle_id)(),
        py::arg( "max_particle_id" ) = ::NS(Monitor_default_max_particle_id)(),
        py::arg( "is_rolling" ) = ::NS(Monitor_default_is_rolling)(),
        py::arg( "is_turn_ordered" ) = ::NS(Monitor_default_is_turn_ordered)(),
        py::arg( "out_addr" ) = st::COBJECTS_NULL_ADDRESS );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(Monitor_from_cbuffer)( cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CMonitor from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC monitor_t*
            { return ::NS(Monitor_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CMonitor instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD", []( cbuffer_view_type& cbuffer,
            index_type const num_stores, index_type const start,
            index_type const skip, index_type const min_particle_id,
            index_type const max_particle_id, bool const is_rolling,
            bool const is_turn_ordered, addr_type const out_addr ) ->
                SIXTRL_BE_ARGPTR_DEC monitor_t* {
                return ::NS(Monitor_cbuffer_add)( cbuffer.as_c_api(), num_stores,
                    start, skip, min_particle_id, max_particle_id, is_rolling,
                        is_turn_ordered, out_addr ); },
            py::return_value_policy::reference,
            "append a fully parameterised CMonitor instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "num_stores" ) = ::NS(Monitor_default_num_stores)(),
            py::arg( "start" ) = ::NS(Monitor_default_start)(),
            py::arg( "skip" ) = ::NS(Monitor_default_skip)(),
            py::arg( "min_particle_id" ) = ::NS(Monitor_default_min_particle_id)(),
            py::arg( "max_particle_id" ) = ::NS(Monitor_default_max_particle_id)(),
            py::arg( "is_rolling" ) = ::NS(Monitor_default_is_rolling)(),
            py::arg( "is_turn_ordered" ) = ::NS(Monitor_default_is_turn_ordered)(),
            py::arg( "out_addr" ) = st::COBJECTS_NULL_ADDRESS );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, monitor_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC monitor_t* {
                return ::NS(Monitor_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &elem ); },
            py::return_value_policy::reference,
            "append a copy of the CMonitor instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( monitor_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC monitor_t* {
                return ::NS(Monitor_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &self ); },
            py::return_value_policy::reference,
            "append a copy of the calling CMonitor instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "num_stores",
            []( monitor_t const& self ) {
                return ::NS(Monitor_num_stores)( &self ); },
            []( monitor_t& self, index_type const num_stores ) {
                ::NS(Monitor_set_num_stores)( &self, num_stores ); } );

        obj.def_property( "start",
            []( monitor_t const& self ) {
                return ::NS(Monitor_start)( &self ); },
            []( monitor_t& self, index_type const start ) {
                ::NS(Monitor_set_start)( &self, start ); } );

        obj.def_property( "skip",
            []( monitor_t const& self ) {
                return ::NS(Monitor_skip)( &self ); },
            []( monitor_t& self, index_type const skip ) {
                ::NS(Monitor_set_skip)( &self, skip ); } );

        obj.def_property( "min_particle_id",
            []( monitor_t const& self ) {
                return ::NS(Monitor_min_particle_id)( &self ); },
            []( monitor_t& self, index_type const min_particle_id ) {
                ::NS(Monitor_set_min_particle_id)( &self, min_particle_id ); } );

        obj.def_property( "max_particle_id",
            []( monitor_t const& self ) {
                return ::NS(Monitor_max_particle_id)( &self ); },
            []( monitor_t& self, index_type const max_particle_id ) {
                ::NS(Monitor_set_max_particle_id)( &self, max_particle_id ); } );

        obj.def_property( "is_rolling",
            []( monitor_t const& self ) {
                return ::NS(Monitor_is_rolling)( &self ); },
            []( monitor_t& self, bool const is_rolling ) {
                ::NS(Monitor_set_is_rolling)( &self, is_rolling ); } );

        obj.def_property( "is_turn_ordered",
            []( monitor_t const& self ) {
                return ::NS(Monitor_is_rolling)( &self ); },
            []( monitor_t& self, bool const is_turn_ordered ) {
                ::NS(Monitor_set_is_rolling)( &self, is_turn_ordered ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(Monitor_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(Monitor_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(Monitor_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(Monitor_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( monitor_t const& self, size_type const slot_size ) {
            return ::NS(Monitor_cobj_required_num_bytes)( &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( monitor_t& self ) {
            ::NS(Monitor_clear)( &self ); } );

        obj.def( "init", []( monitor_t& self,
                index_type const num_stores, index_type const start,
                index_type const skip, index_type const min_particle_id,
                index_type const max_particle_id, bool const is_rolling,
                bool const is_turn_ordered, addr_type const out_addr ) {
            return ::NS(Monitor_init)( &self, num_stores, start, skip,
                min_particle_id, max_particle_id, is_rolling, is_turn_ordered,
                    out_addr ); },
            "initialise a given CMonitor instance with a set of parameters",
            py::arg( "num_stores" ) = ::NS(Monitor_default_num_stores)(),
            py::arg( "start" ) = ::NS(Monitor_default_start)(),
            py::arg( "skip" ) = ::NS(Monitor_default_skip)(),
            py::arg( "min_particle_id" ) = ::NS(Monitor_default_min_particle_id)(),
            py::arg( "max_particle_id" ) = ::NS(Monitor_default_max_particle_id)(),
            py::arg( "is_rolling" ) = ::NS(Monitor_default_is_rolling)(),
            py::arg( "is_turn_ordered" ) = ::NS(Monitor_default_is_turn_ordered)(),
            py::arg( "out_addr" ) = st::COBJECTS_NULL_ADDRESS );
    }

    void InitHelper_common_belements_multipole( stpy::InitHelper& root )
    {
        using multipole_t        = ::NS(Multipole);
        using real_type          = ::NS(be_real_type);
        using order_type         = ::NS(be_order_type);
        using size_type          = ::NS(cobj_size_type);
        using addr_type          = ::NS(address_type);
        using cbuffer_view_type  = st::CBufferView;
        using real_adapter_type  = stpy::RealBufferAdapter;
        using py_array_real_t    = py::array_t<
            real_type, py::array::c_style | py::array::forcecast >;

        auto& obj = root.be_multipole_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            order_type max_order, real_type const length,
            real_type const hxl, real_type const hyl, order_type order )
            {
                if( ( max_order <  order_type{ 0 } ) &&
                    ( order     >= order_type{ 0 } ) )
                {
                    max_order = order;
                }
                else if( ( max_order >= order_type{ 0 } ) &&
                         ( order     <  order_type{ 0 } ) )
                {
                    order = max_order;
                }
                else if( ( max_order < order_type{ 0 } ) &&
                         ( order     < order_type{ 0 } ) )
                {
                    max_order = order_type{ 0 };
                    order = order_type{ 0 };
                }

                return std::unique_ptr< multipole_t, py::nodelete >(
                    ::NS(Multipole_cbuffer_add)( cbuffer.as_c_api(), max_order,
                    order, length, hxl, hyl, st::COBJECTS_NULL_ADDRESS ) ); } ),
            "default constructor, store on a CBufferView!",
            py::arg( "cbuffer" ),
            py::arg( "max_order" ) = order_type{ 0 },
            py::arg( "length" ) = ::NS(Multipole_default_length)(),
            py::arg( "hxl" ) = ::NS(Multipole_default_hxl)(),
            py::arg( "hyl" ) = ::NS(Multipole_default_hyl)(),
            py::arg( "order" ) = order_type{ -1 } );


        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            real_type const length, real_type const hxl, real_type const hyl,
            tl::optional< py_array_real_t > bal_values,
            order_type order ) {

            size_type bal_capacity = stpy::PyArray_length_1d<
                real_type >( bal_values );

            if( ( order >= order_type{ 0 } ) &&
                ( bal_capacity < static_cast< size_type >( 2 * order + 2 ) ) )
                bal_capacity = static_cast< size_type >( 2 * order + 2 );

            auto bal_begin = stpy::PyArray_base_pointer_1d<
                real_type >( bal_values );

            auto const bal_addr = stpy::PyArray_base_addr_1d<
                real_type >( bal_values );

            if( ( bal_capacity % 2 ) != size_type{ 0 } )
                throw std::runtime_error( "( bal_capacity % 2 ) != 0" );

            if( bal_capacity < size_type{ 2 } )
                throw std::runtime_error( "bal_capacity < 2" );

            order_type const max_order = static_cast< order_type >(
                ( bal_capacity - size_type{ 2 } ) >> size_type{ 1 } );

            if( bal_begin != nullptr )
            {
                real_type const EPS = std::numeric_limits<
                    real_type >::epsilon();

                order_type non_zero_order = order_type{ 0 };

                for( size_type ii = 0u ; ii < bal_capacity ; ++ii )
                {
                    real_type const abs_bal = (
                        bal_begin[ ii ] > real_type{ 0.} )
                            ? bal_begin[ ii ] : -bal_begin[ ii ];

                    if( abs_bal > EPS )
                    {
                        order_type const bal_order = ( ii - ( ii % 2u ) ) >> 1u;

                        if( non_zero_order < bal_order )
                        {
                            non_zero_order = bal_order;
                        }
                    }
                }

                if( ( non_zero_order > order ) || ( order > max_order ) )
                {
                    order = non_zero_order;
                }
            }
            else if( ( order < order_type{ 0 } ) || ( order > max_order ) )
            {
                order = max_order;
            }

            return std::unique_ptr< multipole_t, py::nodelete >(
                ::NS(Multipole_cbuffer_add)( cbuffer.as_c_api(), max_order,
                    order, length, hxl, hyl, bal_addr ) ); } ),
            "constructor to store on a CBufferView!",
            py::arg( "cbuffer" ),
            py::arg( "length" ) = ::NS(Multipole_default_length)(),
            py::arg( "hxl" )    = ::NS(Multipole_default_hxl)(),
            py::arg( "hyl" )    = ::NS(Multipole_default_hyl)(),
            py::arg( "bal_values" ) = tl::optional< py_array_real_t >(),
            py::arg( "order" ) = order_type{ -1 } );

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            real_type const length, real_type const hxl, real_type const hyl,
            tl::optional< py_array_real_t > knl,
            tl::optional< py_array_real_t > ksl, order_type order )
        {
            real_type const EPS = std::numeric_limits< real_type >::epsilon();

            size_type const knl_length =
                stpy::PyArray_length_1d< real_type >( knl );

            size_type const ksl_length =
                stpy::PyArray_length_1d< real_type >( ksl );

            size_type const max_order_plus_one = static_cast< order_type >(
                std::max( size_type{ 1 }, std::max( knl_length, ksl_length ) ) );

            order_type max_order = max_order_plus_one - order_type{ 1 };
            if( ( order >= order_type{ 0 } ) && ( max_order < order ) )
                max_order = order;

            real_type const* knl_begin = stpy::PyArray_base_pointer_1d<
                real_type, real_type const* >( knl );

            real_type const* ksl_begin = stpy::PyArray_base_pointer_1d<
                real_type, real_type const* >( ksl );

            std::vector< real_type > bal_values(
                size_type{ 2 } * max_order_plus_one, real_type{ 0 } );

            if( knl_begin != nullptr )
            {
                for( size_type ii = 0u ; ii < knl_length ; ++ii )
                {
                    bal_values[ 2 * ii + 0 ] = knl_begin[ ii ] *
                        NS(Math_inv_factorial)( ii );
                }
            }

            if( ksl_begin != nullptr )
            {
                for( size_type ii = 0u ; ii < ksl_length ; ++ii )
                {
                    bal_values[ 2 * ii + 1 ] = ksl_begin[ ii ] *
                        NS(Math_inv_factorial)( ii );
                }
            }

            if( bal_values.size() > size_type{ 0 } )
            {
                real_type const EPS = std::numeric_limits<
                    real_type >::epsilon();

                order_type non_zero_order = order_type{ 0 };
                size_type const bal_capacity = bal_values.size();

                for( size_type ii = 0u ; ii < bal_capacity ; ++ii )
                {
                    real_type const abs_bal = (
                        bal_values[ ii ] > real_type{ 0.} )
                            ? bal_values[ ii ] : -bal_values[ ii ];

                    if( abs_bal > EPS )
                    {
                        order_type const bal_order = ( ii - ( ii % 2u ) ) >> 1u;

                        if( non_zero_order < bal_order )
                        {
                            non_zero_order = bal_order;
                        }
                    }
                }

                if( ( non_zero_order > order ) || ( order > max_order ) )
                {
                    order = non_zero_order;
                }
            }
            else if( ( order < order_type{ 0 } ) || ( order > max_order ) )
            {
                order = max_order;
            }

            addr_type const bal_addr = static_cast< addr_type >(
                reinterpret_cast< uintptr_t >( bal_values.data() ) );

            return std::unique_ptr< multipole_t, py::nodelete >(
                ::NS(Multipole_cbuffer_add)( cbuffer.as_c_api(), max_order,
                    order, length, hxl, hyl, bal_addr ) ); } ),
            "constructor using knl and ksl values to store on a CBufferView!",
            py::arg( "cbuffer" ), py::arg( "length" ),
            py::arg( "hxl" ), py::arg( "hyl" ),
            py::arg( "knl" ), py::arg( "ksl" ),
            py::arg( "order" ) = order_type{ -1 } );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(Multipole_from_cbuffer)(
                cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CMultipole from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer,
            order_type const max_order ) -> SIXTRL_BE_ARGPTR_DEC multipole_t*
            { return ::NS(Multipole_cbuffer_new)(
                    cbuffer.as_c_api(), max_order ); },
            py::return_value_policy::reference,
            "append a new CMultipole instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ), py::arg( "max_order" ) );

        obj.def_static( "ADD", [](cbuffer_view_type& cbuffer,
            real_type const length, real_type const hxl, real_type const hyl,
            tl::optional< py_array_real_t > bal_values, order_type order )
        {
            size_type bal_capacity = stpy::PyArray_length_1d<
                real_type >( bal_values );

            if( ( order >= order_type{ 0 } ) &&
                ( bal_capacity < static_cast< size_type >( 2 * order + 2 ) ) )
                bal_capacity = static_cast< size_type >( 2 * order + 2 );

            auto bal_begin = stpy::PyArray_base_pointer_1d<
                real_type >( bal_values );

            auto const bal_addr = stpy::PyArray_base_addr_1d<
                real_type >( bal_values );

            if( ( bal_capacity % 2 ) != size_type{ 0 } )
                throw std::runtime_error( "( bal_capacity % 2 ) != 0" );

            if( bal_capacity < size_type{ 2 } )
                throw std::runtime_error( "bal_capacity < 2" );

            order_type const max_order = static_cast< order_type >(
                ( bal_capacity - size_type{ 2 } ) >> size_type{ 1 } );

            if( bal_begin != nullptr )
            {
                real_type const EPS = std::numeric_limits<
                    real_type >::epsilon();

                order_type non_zero_order = order_type{ 0 };

                for( size_type ii = 0u ; ii < bal_capacity ; ++ii )
                {
                    real_type const abs_bal = (
                        bal_begin[ ii ] > real_type{ 0.} )
                            ? bal_begin[ ii ] : -bal_begin[ ii ];

                    if( abs_bal > EPS )
                    {
                        order_type const bal_order = ( ii - ( ii % 2u ) ) >> 1u;

                        if( non_zero_order < bal_order )
                        {
                            non_zero_order = bal_order;
                        }
                    }
                }

                if( ( non_zero_order > order ) || ( order > max_order ) )
                {
                    order = non_zero_order;
                }
            }
            else if( ( order < order_type{ 0 } ) || ( order > max_order ) )
            {
                order = max_order;
            }

            return ::NS(Multipole_cbuffer_add)( cbuffer.as_c_api(), max_order,
                order, length, hxl, hyl, bal_addr ); },
        py::return_value_policy::reference,
        "add instance using knl and ksl values to a CBufferView!",
        py::arg( "cbuffer" ), py::arg( "length" ), py::arg( "hxl" ),
        py::arg( "hyl" ), py::arg( "bal_values" ),
        py::arg( "order" ) = order_type{ -1 } );

        obj.def_static( "ADD", [](cbuffer_view_type& cbuffer,
            real_type const length, real_type const hxl, real_type const hyl,
            tl::optional< py_array_real_t > knl,
            tl::optional< py_array_real_t > ksl, order_type order )
            {
                real_type const EPS = std::numeric_limits<
                    real_type >::epsilon();

                size_type const knl_length =
                    stpy::PyArray_length_1d< real_type >( knl );

                size_type const ksl_length =
                    stpy::PyArray_length_1d< real_type >( ksl );

                size_type const max_order_plus_one = static_cast< order_type >(
                    std::max( size_type{ 1 }, std::max(
                        knl_length, ksl_length ) ) );

                order_type max_order = max_order_plus_one - order_type{ 1 };
                if( ( order >= order_type{ 0 } ) && ( max_order < order ) )
                    max_order = order;

                real_type const* knl_begin = stpy::PyArray_base_pointer_1d<
                    real_type >( knl );

                real_type const* ksl_begin = stpy::PyArray_base_pointer_1d<
                    real_type >( ksl );

                std::vector< real_type > bal_values(
                    size_type{ 2 } * max_order_plus_one, real_type{ 0 } );

                if( knl_begin != nullptr )
                {
                    for( size_type ii = 0u ; ii < knl_length ; ++ii )
                    {
                        bal_values[ 2 * ii + 0 ] = knl_begin[ ii ] *
                            NS(Math_inv_factorial)( ii );
                    }
                }

                if( ksl_begin != nullptr )
                {
                    for( size_type ii = 0u ; ii < ksl_length ; ++ii )
                    {
                        bal_values[ 2 * ii + 1 ] = ksl_begin[ ii ] *
                            NS(Math_inv_factorial)( ii );
                    }
                }

                if( bal_values.size() > size_type{ 0 } )
                {
                    real_type const EPS = std::numeric_limits<
                        real_type >::epsilon();

                    order_type non_zero_order = order_type{ 0 };
                    size_type const bal_capacity = bal_values.size();

                    for( size_type ii = 0u ; ii < bal_capacity ; ++ii )
                    {
                        real_type const abs_bal = (
                            bal_values[ ii ] > real_type{ 0.} )
                                ? bal_values[ ii ] : -bal_values[ ii ];

                        if( abs_bal > EPS )
                        {
                            order_type const bal_order =
                                ( ii - ( ii % 2u ) ) >> 1u;

                            if( non_zero_order < bal_order )
                            {
                                non_zero_order = bal_order;
                            }
                        }
                    }

                    if( ( non_zero_order > order ) || ( order > max_order ) )
                    {
                        order = non_zero_order;
                    }
                }
                else if( ( order < order_type{ 0 } ) || ( order > max_order ) )
                {
                    order = max_order;
                }

                addr_type const bal_addr = static_cast< addr_type >(
                    reinterpret_cast< uintptr_t >( bal_values.data() ) );

                return ::NS(Multipole_cbuffer_add)( cbuffer.as_c_api(), max_order,
                    order, length, hxl, hyl, bal_addr );
            }, py::return_value_policy::reference,
            "add instance using knl and ksl values to a CBufferView!",
            py::arg( "cbuffer" ), py::arg( "length" ), py::arg( "hxl" ),
            py::arg( "hyl" ), py::arg( "knl" ), py::arg( "ksl" ),
            py::arg( "order" ) = order_type{ -1 } );

        obj.def_static( "ADD_COPY", [](
            cbuffer_view_type& cbuffer, multipole_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC multipole_t* {
                return ::NS(Multipole_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &elem ); },
            py::return_value_policy::reference,
            "append a copy of the CMultipole instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( multipole_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC multipole_t* {
                return ::NS(Multipole_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &self ); },
            py::return_value_policy::reference,
            "append a copy of the calling CMultipole instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "max_order",
            []( multipole_t const& self ) {
                return ::NS(Multipole_max_order)( &self ); },
            []( multipole_t& self, order_type const max_order ) {
                return ::NS(Multipole_set_max_order)( &self, max_order ); } );

        obj.def_property_readonly( "bal_capacity", []( multipole_t const& self ){
            return ::NS(Multipole_bal_capacity)( &self ); } );

        obj.def_property( "order",
            []( multipole_t const& self ) {
                return ::NS(Multipole_order)( &self ); },
            []( multipole_t& self, order_type const order ) {
                return ::NS(Multipole_set_order)( &self, order ); } );

        obj.def_property_readonly( "bal_length", []( multipole_t const& self ){
                return ::NS(Multipole_bal_length)( &self ); } );

        obj.def_property( "length",
            []( multipole_t const& self ) {
                return ::NS(Multipole_length)( &self ); },
            []( multipole_t& self, real_type const v ) {
                return ::NS(Multipole_set_length)( &self, v ); } );

        obj.def_property( "hxl",
            []( multipole_t const& self ) {
                return ::NS(Multipole_hxl)( &self ); },
            []( multipole_t& self, real_type const value ) {
                return ::NS(Multipole_set_hxl)( &self, value ); } );

        obj.def_property( "hyl",
            []( multipole_t const& self ) {
                return ::NS(Multipole_hyl)( &self ); },
            []( multipole_t& self, real_type const value ) {
                return ::NS(Multipole_set_hyl)( &self, value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly( "bal_addr", []( multipole_t const& self ) {
                return ::NS(Multipole_bal_addr)( &self ); } );

        obj.def( "bal", []( multipole_t const& self, size_type const idx ) {
                return ::NS(Multipole_bal)( &self, idx ); } );

        obj.def( "bal", []( multipole_t& self ) ->real_adapter_type {
            return real_adapter_type( ::NS(Multipole_bal_addr)( &self ),
                ::NS(Multipole_bal_capacity)( &self ) ); },
            py::return_value_policy::move, "access all bal values as a buffer" );

        obj.def( "set_bal", []( multipole_t& self, size_type const idx,
            real_type const bal_value ) {
            return ::NS(Multipole_set_bal_value)( &self, idx, bal_value ); } );

        obj.def( "set_bal", []( multipole_t& self, real_type const bal_value ){
            return ::NS(Multipole_set_all_bal_values)( &self, bal_value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "knl", []( multipole_t const& self, size_type const idx ) {
                return ::NS(Multipole_knl)( &self, idx ); } );

        obj.def( "set_knl", []( multipole_t& self, size_type const idx,
            real_type const knl_value ) {
            return ::NS(Multipole_set_knl_value)( &self, idx, knl_value ); } );

        obj.def( "set_knl", []( multipole_t& self, real_type const knl_value ) {
            return ::NS(Multipole_set_all_knl_values)( &self, knl_value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "ksl", []( multipole_t const& self, size_type const idx ) {
                return ::NS(Multipole_ksl)( &self, idx ); } );

        obj.def( "set_ksl", []( multipole_t& self, size_type const idx,
            real_type const ksl_value ) {
            return ::NS(Multipole_set_ksl_value)( &self, idx, ksl_value ); } );

        obj.def( "set_ksl", []( multipole_t& self, real_type const ksl_value ) {
            return ::NS(Multipole_set_all_ksl_values)( &self, ksl_value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(Multipole_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(Multipole_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(Multipole_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(Multipole_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( multipole_t const& self, size_type const slot_size ) {
            return ::NS(Multipole_cobj_required_num_bytes)( &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( multipole_t& self ) {
            ::NS(Multipole_clear)( &self ); } );

        obj.def( "init", []( multipole_t& self, order_type max_order,
                real_type const length, real_type const hxl,
                real_type const hyl, addr_type const bal_addr,
                order_type order )
        {
            if( ( max_order < order_type{ 0 } ) &&
                ( order >= order_type{ 0 } ) )
            {
                max_order = order;
            }
            else if( ( max_order >= order_type{ 0 } ) &&
                        ( order < order_type{ 0 } ) )
            {
                order = max_order;
            }
            else if( ( max_order < order_type{ 0 } ) &&
                        ( order < order_type{ 0 } ) )
            {
                max_order = order_type{ 0 };
                order = order_type{ 0 };
            }

            return ::NS(Multipole_init)(
                &self, max_order, order, length, hxl, hyl, bal_addr ); },
            "initialise a given CMultipole instance with a set of parameters",
            py::arg( "max_order" ),
            py::arg( "length" ),
            py::arg( "hxl" ),
            py::arg( "hyl" ),
            py::arg( "bal_addr" ) = st::COBJECTS_NULL_ADDRESS,
            py::arg( "order" ) = order_type{ -1 } );
    }

    void InitHelper_common_belements_rf_multipole( stpy::InitHelper& root )
    {
        using rf_multipole_t     = ::NS(RFMultipole);
        using real_type          = ::NS(be_real_type);
        using order_type         = ::NS(be_order_type);
        using size_type          = ::NS(cobj_size_type);
        using addr_type          = ::NS(address_type);
        using cbuffer_view_type  = st::CBufferView;
        using real_adapter_type  = stpy::RealBufferAdapter;
        using py_array_real_t    = py::array_t<
            real_type, py::array::c_style | py::array::forcecast >;

        auto& obj = root.be_rf_multipole_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer, order_type max_order,
            real_type const voltage, real_type const frequency,
            real_type const lag, order_type order )
            {
                if( ( max_order <  order_type{ 0 } ) &&
                    ( order     >= order_type{ 0 } ) )
                {
                    max_order = order;
                }
                else if( ( max_order >= order_type{ 0 } ) &&
                         ( order     <  order_type{ 0 } ) )
                {
                    order = max_order;
                }
                else if( ( max_order < order_type{ 0 } ) &&
                         ( order     < order_type{ 0 } ) )
                {
                    order = order_type{ 0 };
                    max_order = order_type{ 0 };
                }

                addr_type const bal_addr   = st::COBJECTS_NULL_ADDRESS;
                addr_type const phase_addr = st::COBJECTS_NULL_ADDRESS;

                return std::unique_ptr< rf_multipole_t, py::nodelete >(
                    ::NS(RFMultipole_cbuffer_add)( cbuffer.as_c_api(), max_order,
                    order, voltage, frequency, lag, bal_addr, phase_addr ) ); }
            ), "default constructor to store on a CBufferView!",
            py::arg( "cbuffer" ),
            py::arg( "max_order" ) = order_type{ 0 },
            py::arg( "voltage" ) = ::NS(RFMultipole_default_voltage)(),
            py::arg( "frequency" ) = ::NS(RFMultipole_default_frequency)(),
            py::arg( "lag" ) = ::NS(RFMultipole_default_lag)(),
            py::arg( "order" ) = order_type{ -1 } );

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            real_type const voltage, real_type const frequency,
            real_type const lag,
            tl::optional< py_array_real_t > bal_values,
            tl::optional< py_array_real_t > phase_values,
            order_type order )
        {
            if( order < order_type{ 0 } ) order = order_type{ 0 };

            size_type bal_length =
                stpy::PyArray_length_1d< real_type >( bal_values );

            size_type phase_length =
                stpy::PyArray_length_1d< real_type >( phase_values );

            size_type const capacity = std::max(
                std::max( bal_length, phase_length ),
                static_cast< size_type >( 2 * order + 2 ) );

            if( capacity < size_type{ 2 } )
                throw std::runtime_error( "capacity < 2" );

            if( ( capacity % size_type{ 2 } ) != size_type{ 0 } )
                throw std::runtime_error(
                    "( capacity % size_type{ 2 } ) != size_type{ 0 }" );

            order_type max_order = std::max( order,
                static_cast< order_type >( ( capacity - 2 ) >> 1 ) );

            std::unique_ptr< std::vector< real_type > > dummy_bal_vals( nullptr );
            addr_type const bal_addr = stpy::PyArray_stable_base_addr_1d<
                real_type, size_type >( bal_values, capacity, bal_length,
                    dummy_bal_vals, real_type{ 0.0 } );

            std::unique_ptr< std::vector< real_type > > dummy_phases( nullptr );
            addr_type const phase_addr = stpy::PyArray_stable_base_addr_1d<
                real_type, size_type >( phase_values, capacity, phase_length,
                    dummy_phases, real_type{ 0.0 } );

            return std::unique_ptr< rf_multipole_t, py::nodelete >(
                ::NS(RFMultipole_cbuffer_add)( cbuffer.as_c_api(), max_order,
                    order, voltage, frequency, lag, bal_addr, phase_addr ) ); }
            ), "constructor to store on a CBufferView!",
            py::arg( "cbuffer" ), py::arg( "voltage" ), py::arg( "frequency" ),
            py::arg( "lag" ), py::arg( "bal_values" ), py::arg( "phase_values" ),
            py::arg( "order" ) = order_type{ -1 } );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(RFMultipole_from_cbuffer)( cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CRFMultipole from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer,
            order_type const max_order ) -> SIXTRL_BE_ARGPTR_DEC rf_multipole_t*
            { return ::NS(RFMultipole_cbuffer_new)(
                    cbuffer.as_c_api(), max_order ); },
            py::return_value_policy::reference,
            "append a new CRFMultipole instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ), py::arg( "max_order" ) );

        obj.def_static( "ADD", []( cbuffer_view_type& cbuffer,
            real_type const voltage, real_type const frequency,
            real_type const lag,
            tl::optional< py_array_real_t > bal_values,
            tl::optional< py_array_real_t > phase_values,
            order_type order ) -> SIXTRL_BE_ARGPTR_DEC rf_multipole_t*
            {
                if( order < order_type{ 0 } ) order = order_type{ 0 };

                size_type bal_length =
                    stpy::PyArray_length_1d< real_type >( bal_values );

                size_type phase_length =
                    stpy::PyArray_length_1d< real_type >( phase_values );

                size_type const capacity = std::max(
                    std::max( bal_length, phase_length ),
                    static_cast< size_type >( 2 * order + 2 ) );

                if( capacity < size_type{ 2 } )
                    throw std::runtime_error( "capacity < 2" );

                if( ( capacity % size_type{ 2 } ) != size_type{ 0 } )
                    throw std::runtime_error(
                        "( capacity % size_type{ 2 } ) != size_type{ 0 }" );

                order_type max_order = std::max( order,
                    static_cast< order_type >( ( capacity - 2 ) >> 1 ) );

                std::unique_ptr< std::vector< real_type > > dummy_bals( nullptr );
                addr_type const bal_addr = stpy::PyArray_stable_base_addr_1d<
                    real_type, size_type >( bal_values, capacity, bal_length,
                        dummy_bals, real_type{ 0.0 } );

                std::unique_ptr< std::vector< real_type > > dummy_phases( nullptr );
                addr_type const phase_addr = stpy::PyArray_stable_base_addr_1d<
                    real_type, size_type >( phase_values, capacity, phase_length,
                        dummy_phases, real_type{ 0.0 } );

                return ::NS(RFMultipole_cbuffer_add)( cbuffer.as_c_api(),
                    max_order, order, voltage, frequency, lag,
                        bal_addr, phase_addr ); },
            py::return_value_policy::reference,
            "append a fully parameterised CRFMultipole instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ), py::arg( "voltage" ), py::arg( "frequency" ),
            py::arg( "lag" ), py::arg( "bal_values" ),
            py::arg( "phase_values" ), py::arg( "order" ) = order_type{ -1 } );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, rf_multipole_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC rf_multipole_t* {
                return ::NS(RFMultipole_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &elem ); },
            py::return_value_policy::reference,
            "append a copy of the CRFMultipole instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( rf_multipole_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC rf_multipole_t* {
                return ::NS(RFMultipole_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &self ); },
            py::return_value_policy::reference,
            "append a copy of the calling CRFMultipole instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "max_order",
            []( rf_multipole_t const& self ) {
                return ::NS(RFMultipole_max_order)( &self ); },
            []( rf_multipole_t& self, order_type const max_order ) {
                return ::NS(RFMultipole_set_max_order)( &self, max_order ); } );

        obj.def_property_readonly( "bal_capacity", []( rf_multipole_t const& self ){
            return ::NS(RFMultipole_bal_capacity)( &self ); } );

        obj.def_property_readonly( "phase_capacity",
            []( rf_multipole_t const& self ){
                return ::NS(RFMultipole_phase_capacity)( &self ); } );

        obj.def_property( "order",
            []( rf_multipole_t const& self ) {
                return ::NS(RFMultipole_order)( &self ); },
            []( rf_multipole_t& self, order_type const order ) {
                return ::NS(RFMultipole_set_order)( &self, order ); } );

        obj.def_property_readonly( "bal_length", []( rf_multipole_t const& self ){
                return ::NS(RFMultipole_bal_length)( &self ); } );

        obj.def_property_readonly( "phase_length",
            []( rf_multipole_t const& self ){
                return ::NS(RFMultipole_phase_length)( &self ); } );

        obj.def_property( "voltage",
            []( rf_multipole_t const& self ) {
                return ::NS(RFMultipole_voltage)( &self ); },
            []( rf_multipole_t& self, real_type const voltage ) {
                return ::NS(RFMultipole_set_voltage)( &self, voltage ); } );

        obj.def_property( "frequency",
            []( rf_multipole_t const& self ) {
                return ::NS(RFMultipole_frequency)( &self ); },
            []( rf_multipole_t& self, real_type const frequency ) {
                return ::NS(RFMultipole_set_frequency)( &self, frequency ); } );

        obj.def_property( "lag",
            []( rf_multipole_t const& self ) {
                return ::NS(RFMultipole_lag)( &self ); },
            []( rf_multipole_t& self, real_type const lag ) {
                return ::NS(RFMultipole_set_lag)( &self, lag ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly( "bal_addr", []( rf_multipole_t const& self ) {
                return ::NS(RFMultipole_bal_addr)( &self ); } );

        obj.def( "bal", []( rf_multipole_t const& self, size_type const idx ) {
                return ::NS(RFMultipole_bal)( &self, idx ); } );

        obj.def( "bal", []( rf_multipole_t& self ) ->real_adapter_type {
            return real_adapter_type( ::NS(RFMultipole_bal_addr)( &self ),
                ::NS(RFMultipole_bal_capacity)( &self ) ); },
            py::return_value_policy::move, "access all bal values as a buffer" );

        obj.def( "set_bal", []( rf_multipole_t& self, size_type const idx,
            real_type const bal_value ) {
            return ::NS(RFMultipole_set_bal_value)( &self, idx, bal_value ); } );

        obj.def( "set_bal", []( rf_multipole_t& self, real_type const bal_value ){
            return ::NS(RFMultipole_set_all_bal_values)( &self, bal_value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "knl", []( rf_multipole_t const& self, size_type const idx ) {
                return ::NS(RFMultipole_knl)( &self, idx ); } );

        obj.def( "set_knl", []( rf_multipole_t& self, size_type const idx,
            real_type const knl_value ) {
            return ::NS(RFMultipole_set_knl_value)( &self, idx, knl_value ); } );

        obj.def( "set_knl",
            []( rf_multipole_t& self, real_type const knl_value ) {
            return ::NS(RFMultipole_set_all_knl_values)( &self, knl_value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "ksl", []( rf_multipole_t const& self, size_type const idx ) {
                return ::NS(RFMultipole_ksl)( &self, idx ); } );

        obj.def( "set_ksl", []( rf_multipole_t& self, size_type const idx,
            real_type const ksl_value ) {
            return ::NS(RFMultipole_set_ksl_value)( &self, idx, ksl_value ); } );

        obj.def( "set_ksl",
            []( rf_multipole_t& self, real_type const ksl_value ) {
            return ::NS(RFMultipole_set_all_ksl_values)( &self, ksl_value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly( "phase_addr",
            []( rf_multipole_t const& self ) {
                return ::NS(RFMultipole_phase_addr)( &self ); } );

        obj.def( "phase", []( rf_multipole_t const& self, size_type const idx ) {
                return ::NS(RFMultipole_phase)( &self, idx ); } );

        obj.def( "phase", []( rf_multipole_t& self ) ->real_adapter_type {
            return real_adapter_type( ::NS(RFMultipole_phase_addr)( &self ),
                ::NS(RFMultipole_phase_capacity)( &self ) ); },
            py::return_value_policy::move,
            "access all phase values as a buffer" );

        obj.def( "set_phase", []( rf_multipole_t& self, size_type const idx,
            real_type const phase_value ) {
            return ::NS(RFMultipole_set_phase_value)(
                &self, idx, phase_value ); } );

        obj.def( "set_phase",
                 []( rf_multipole_t& self, real_type const phase_value ){
                    return ::NS(RFMultipole_set_all_phase_values)(
                        &self, phase_value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "phase_n", []( rf_multipole_t const& self, size_type const idx ) {
                return ::NS(RFMultipole_phase_n)( &self, idx ); } );

        obj.def( "set_phase_n", []( rf_multipole_t& self, size_type const idx,
            real_type const phase_n_value ) {
            return ::NS(RFMultipole_set_phase_n_value)(
                &self, idx, phase_n_value ); } );

        obj.def( "set_phase_n", []( rf_multipole_t& self, real_type const phase_n_value ) {
            return ::NS(RFMultipole_set_all_phase_n_values)( &self, phase_n_value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "phase_s", []( rf_multipole_t const& self, size_type const idx ) {
                return ::NS(RFMultipole_phase_s)( &self, idx ); } );

        obj.def( "set_phase_s", []( rf_multipole_t& self, size_type const idx,
            real_type const phase_s_value ) {
            return ::NS(RFMultipole_set_phase_s_value)(
                &self, idx, phase_s_value ); } );

        obj.def( "set_phase_s",
            []( rf_multipole_t& self, real_type const phase_s_value ) {
            return ::NS(RFMultipole_set_all_phase_s_values)(
                &self, phase_s_value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(RFMultipole_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(RFMultipole_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(RFMultipole_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(RFMultipole_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( rf_multipole_t const& self, size_type const slot_size ) {
            return ::NS(RFMultipole_cobj_required_num_bytes)( &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( rf_multipole_t& self ) {
            ::NS(RFMultipole_clear)( &self ); } );

        obj.def( "init", []( rf_multipole_t& self, order_type max_order,
                real_type const voltage, real_type const frequency,
                real_type const lag, addr_type const bal_addr,
                addr_type const phase_addr, order_type order )
        {
            if( ( max_order < order_type{ 0 } ) &&
                ( order >= order_type{ 0 } ) )
            {
                max_order = order;
            }
            else if( ( max_order >= order_type{ 0 } ) &&
                        ( order < order_type{ 0 } ) )
            {
                order = max_order;
            }
            else if( ( max_order < order_type{ 0 } ) &&
                        ( order < order_type{ 0 } ) )
            {
                max_order = order_type{ 0 };
                order = order_type{ 0 };
            }

            return ::NS(RFMultipole_init)( &self, max_order, order, voltage,
                frequency, lag, bal_addr, phase_addr ); },
            "initialise a given CRFMultipole instance with a set of parameters",
            py::arg( "max_order" ),
            py::arg( "voltage" ),
            py::arg( "frequency" ),
            py::arg( "lag" ),
            py::arg( "bal_addr" ) = st::COBJECTS_NULL_ADDRESS,
            py::arg( "phase_addr" ) = st::COBJECTS_NULL_ADDRESS,
            py::arg( "order" ) = order_type{ -1 } );
    }

    void InitHelper_common_belements_srotation( stpy::InitHelper& root )
    {
        using srotation_t       = ::NS(SRotation);
        using real_type         = ::NS(be_real_type);
        using size_type         = ::NS(cobj_size_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.be_srotation_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            real_type const cos_z, real_type const sin_z ) {
            return std::unique_ptr< srotation_t, py::nodelete >(
                ::NS(SRotation_cbuffer_add)( cbuffer.as_c_api(), cos_z,
                    sin_z ) ); } ),
        "parameterised constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ), py::arg( "cos_z" ), py::arg( "sin_z" ) );

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            real_type const angle_rad ) {
            return std::unique_ptr< srotation_t, py::nodelete >(
                ::NS(SRotation_cbuffer_add)( cbuffer.as_c_api(),
                    ::NS(cos)( angle_rad ), ::NS(sin)( angle_rad ) ) ); } ),
        "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ), py::arg( "angle_rad" ) = real_type{ 0. } );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(SRotation_from_cbuffer)( cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CSRotation from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC srotation_t*
            { return ::NS(SRotation_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CSRotation instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD", []( cbuffer_view_type& cbuffer,
            real_type const cos_z, real_type const sin_z ) ->
                SIXTRL_BE_ARGPTR_DEC srotation_t* {
                return ::NS(SRotation_cbuffer_add)(
                    cbuffer.as_c_api(), cos_z, sin_z ); },
            py::return_value_policy::reference,
            "append a fully parameterised CSRotation instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "cos_z" ) = ::NS(SRotation_default_cos_z)(),
            py::arg( "sin_z" ) = ::NS(SRotation_default_sin_z)() );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, srotation_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC srotation_t* {
                return ::NS(SRotation_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &elem ); },
            py::return_value_policy::reference,
            "append a copy of the CSRotation instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( srotation_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC srotation_t* {
                return ::NS(SRotation_cbuffer_add_copy)(
                    cbuffer.as_c_api(), &self ); },
            py::return_value_policy::reference,
            "append a copy of the calling CSRotation instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "cos_z",
            []( srotation_t const& self ) {
                return ::NS(SRotation_cos_z)( &self ); },
            []( srotation_t& self, real_type const v ) {
                ::NS(SRotation_set_cos_z)( &self, v ); } );

        obj.def_property( "sin_z",
            []( srotation_t const& self ) {
                return ::NS(SRotation_sin_z)( &self ); },
            []( srotation_t& self, real_type const value ) {
                ::NS(SRotation_set_sin_z)( &self, value ); } );

        obj.def_property( "angle",
            []( srotation_t const& self ) {
                return ::NS(SRotation_angle)( &self ); },
            []( srotation_t& self, real_type const angle ) {
                ::NS(SRotation_set_angle)( &self, angle ); } );

        obj.def_property( "angle_deg",
            []( srotation_t const& self ) {
                return ::NS(SRotation_angle_deg)( &self ); },
            []( srotation_t& self, real_type const angle_deg ) {
                ::NS(SRotation_set_angle_deg)( &self, angle_deg ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(SRotation_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(SRotation_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(SRotation_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(SRotation_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( srotation_t const& self, size_type const slot_size ) {
            return ::NS(SRotation_cobj_required_num_bytes)( &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( srotation_t& self ) {
            ::NS(SRotation_clear)( &self ); } );

        obj.def( "init", []( srotation_t& self,
                real_type const cos_z, real_type const sin_z ) {
            return ::NS(SRotation_init)( &self, cos_z, sin_z ); },
            "initialise a given CSRotation instance with a set of parameters",
            py::arg( "cos_z" ) = ::NS(SRotation_default_cos_z)(),
            py::arg( "sin_z" ) = ::NS(SRotation_default_sin_z)() );
    }

    void InitHelper_common_belements_xyshift( stpy::InitHelper& root )
    {
        using xyshift_t          = ::NS(XYShift);
        using real_type         = ::NS(be_real_type);
        using size_type         = ::NS(cobj_size_type);
        using cbuffer_view_type = st::CBufferView;

        auto& obj = root.be_xyshift_type;

        obj.def( py::init( []( cbuffer_view_type& cbuffer,
            real_type const dx, real_type const dy ) {
            return std::unique_ptr< xyshift_t, py::nodelete >(
                ::NS(XYShift_cbuffer_add)( cbuffer.as_c_api(), dx, dy ) ); } ),
        "default constructor, store instance on a CBufferView/CBuffer",
        py::arg( "cbuffer" ),
        py::arg( "dx" ) = ::NS(XYShift_default_dx)(),
        py::arg( "dy" ) = ::NS(XYShift_default_dy)() );

        /* ----------------------------------------------------------------- */

        obj.def_static( "GET",
            []( cbuffer_view_type& cbuffer, size_type const pos_in_buf ) {
            return ::NS(XYShift_from_cbuffer)( cbuffer.as_c_api(), pos_in_buf ); },
            py::return_value_policy::reference,
            "get instance of CXYShift from a CBufferView at pos_in_buffer",
            py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

        obj.def_static( "CREATE_NEW", []( cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC xyshift_t*
            { return ::NS(XYShift_cbuffer_new)( cbuffer.as_c_api() ); },
            py::return_value_policy::reference,
            "append a new CXYShift instance to a CBufferView/CBuffer",
            py::arg( "cbuffer" ) );

        obj.def_static( "ADD", []( cbuffer_view_type& cbuffer,
            real_type const dx, real_type const dy ) ->
            SIXTRL_BE_ARGPTR_DEC xyshift_t* {
                return ::NS(XYShift_cbuffer_add)( cbuffer.as_c_api(),dx, dy ); },
            py::return_value_policy::reference,
            "append a fully parameterised CXYShift instance to a "
            "CBufferView/CBuffer",
            py::arg( "cbuffer" ),
            py::arg( "dx" ) = ::NS(XYShift_default_dx)(),
            py::arg( "dy" ) = ::NS(XYShift_default_dy)() );

        obj.def_static( "ADD_COPY",
            []( cbuffer_view_type& cbuffer, xyshift_t const& elem ) ->
                SIXTRL_PARTICLES_ARGPTR_DEC xyshift_t* {
                return ::NS(XYShift_cbuffer_add_copy)( cbuffer.as_c_api(), &elem );
            }, py::return_value_policy::reference,
            "append a copy of the CXYShift instance provided to the "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ), py::arg( "original" ) );

        obj.def( "copy_to_cbuffer",
            []( xyshift_t const& self, cbuffer_view_type& cbuffer ) ->
                SIXTRL_BE_ARGPTR_DEC xyshift_t* {
                return ::NS(XYShift_cbuffer_add_copy)( cbuffer.as_c_api(), &self );
            }, py::return_value_policy::reference,
            "append a copy of the calling CXYShift instance to a "
            "CBufferView/CBuffer instance",
            py::arg( "cbuffer" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property( "dx",
            []( xyshift_t const& self ) {
                return ::NS(XYShift_dx)( &self ); },
            []( xyshift_t& self, real_type const v ) {
                ::NS(XYShift_set_dx)( &self, v ); } );

        obj.def_property( "dy",
            []( xyshift_t const& self ) {
                return ::NS(XYShift_dy)( &self ); },
            []( xyshift_t& self, real_type const value ) {
                ::NS(XYShift_set_dy)( &self, value ); } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def_property_readonly_static( "COBJ_TYPE_ID",
            []( py::object /* */ ) { return ::NS(XYShift_cobj_type_id)(); } );

        obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
            []( py::object /* */ ) { return ::NS(XYShift_cobj_num_dataptrs)();
        } );

        obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(XYShift_cobj_actual_handle_size)( slot_size ); },
            "Calculate the actual handle size of the type in bytes "
            "for a given slot size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
            []( size_type const slot_size ) {
            return ::NS(XYShift_cobj_reserved_handle_size)( slot_size ); },
            "Calculate the reserved handle size of the type in bytes "
            "for a given slot size. For most types, this should be identical "
            "to the actual handle size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def( "cobj_required_num_bytes",
            []( xyshift_t const& self, size_type const slot_size ) {
            return ::NS(XYShift_cobj_required_num_bytes)( &self, slot_size ); },
            "Calculate the required total number of bytes to store the calling "
            "instance in a CBufferView/CBuffer for a given slot_size",
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        /* ------------------------------------------------------------------ */

        obj.def( "clear", []( xyshift_t& self ) {
            ::NS(XYShift_clear)( &self ); } );

        obj.def( "init", []( xyshift_t& self,
            real_type const dx, real_type const dy ) {
            return ::NS(XYShift_init)( &self, dx, dy ); },
            "initialise a given CXYShift instance with a set of parameters",
            py::arg( "dx" ) = ::NS(XYShift_default_dx)(),
            py::arg( "dy" ) = ::NS(XYShift_default_dy)() );
    }

    void InitHelper_common_belements_demotrack( stpy::InitHelper& root )
    {
        using real_type = ::NS(be_real_type);
        using size_type = ::NS(cobj_size_type);
        using cbuffer_view_type = st::CBufferView;

        using py_array_real_t = py::array_t< real_type, py::array::c_style |
                                    py::array::forcecast >;

        #if defined( SIXTRL_DEMOTRACK_ENABLED ) && \
                   ( SIXTRL_DEMOTRACK_ENABLED == 1 )

        root.m.def( "Demotrack_belems_requ_num_slots",
            []( st::CBufferView const& cbuffer ) -> size_type {
            return ::NS(Demotrack_belems_requ_num_slots_for_cobj_index_range)(
                    ::NS(CBuffer_const_objects_begin)( cbuffer.as_c_api() ),
                    ::NS(CBuffer_const_objects_end)( cbuffer.as_c_api() ) ); },
            "calculate the number of required slots for storing the whole "
            "cbuffer in a demotrack flat array" );

        root.m.def( "Demotrack_belems_requ_num_slots",
            []( int const dt_type_id ) -> size_type {
            return ::NS(Demotrack_belems_requ_num_slots_for_type_id)(
                static_cast< ::NS(demotrack_belement_type) >( dt_type_id ) ); },
            "get the num of slots required for a given demotrack type id" );

        root.m.def( "Demotrack_belems_can_convert",
            []( st::CBufferView const& cbuffer ) -> bool {
                return ::NS(Demotrack_belems_can_convert_cobj_index_range)(
                    ::NS(CBuffer_const_objects_begin)( cbuffer.as_c_api() ),
                    ::NS(CBuffer_const_objects_end)( cbuffer.as_c_api() ) ); } );

        root.m.def( "Demotrack_belems_num_stored_objects",
            []( tl::optional< py_array_real_t > flat_buffer_arg ) -> size_type {
                return ::NS(Demotrack_belems_num_stored_objects)(
                    stpy::PyArray_base_pointer_1d< real_type, real_type const* >(
                        flat_buffer_arg ),
                    stpy::PyArray_length_1d< real_type >( flat_buffer_arg ) ); },
            "Get the num of stored demotrack beam elements in flat buffer. "
            "In case of an error / problem, 0 is returned" );

        root.m.def( "Demotrack_belems_type_id",
            []( tl::optional< py_array_real_t > flat_buffer_arg,
                size_type const cur_slot_idx ) -> int {
                return ::NS(Demotrack_belems_type_id_from_storage)(
                    stpy::PyArray_base_pointer_1d< real_type, real_type const*
                        >( flat_buffer_arg ),
                    stpy::PyArray_length_1d< real_type >( flat_buffer_arg ),
                    cur_slot_idx ); },
            "retrieve the demotrack type id at the slot_idx location, \r\n"
            "returns st_DEMOTRACK_BEAM_ELEMENT_UNKNOWN == 0 in case of "
            "problems or unknown elements",
            py::arg( "demotrack_array" ), py::arg( "slot_idx" ) );

        root.m.def( "Demotrack_belems_convert",
            []( st::CBufferView const& cbuffer ) -> py::array_t< real_type >
            {
                if( cbuffer.num_objects() < st::size_type{ 0 } )
                {
                    throw std::runtime_error( "cbuffer empty" );
                }

                if( !::NS(Demotrack_belems_can_convert_cobj_index_range)(
                      ::NS(CBuffer_const_objects_begin)( cbuffer.as_c_api() ),
                      ::NS(CBuffer_const_objects_end)( cbuffer.as_c_api() ) ) )
                {
                    throw std::runtime_error(
                        "can't convert cbuffer to demotrack flat "
                        "be_real_type array" );
                }

                st::size_type const requ_num_slots =
                    ::NS(Demotrack_belems_requ_num_slots_for_cobj_index_range)(
                        ::NS(CBuffer_const_objects_begin)( cbuffer.as_c_api() ),
                        ::NS(CBuffer_const_objects_end)( cbuffer.as_c_api() ) );

                SIXTRL_ASSERT( requ_num_slots > st::size_type{ 0 } );

                std::vector< real_type >* ptr_temp_buffer =
                    new std::vector< real_type >( requ_num_slots, real_type{ 0.0 } );

                SIXTRL_ASSERT( ptr_temp_buffer != nullptr );

                st::size_type const cmp_num_slots =
                    st::TDemotrack_belems_cobj_index_range_to_flat_buffer(
                        *ptr_temp_buffer,
                        ::NS(CBuffer_const_objects_begin)( cbuffer.as_c_api() ),
                        ::NS(CBuffer_const_objects_end)( cbuffer.as_c_api() ) );

                if( ( cmp_num_slots != requ_num_slots ) ||
                    ( ptr_temp_buffer->size() != requ_num_slots ) )
                {
                    throw std::runtime_error(
                        "discrepancy between returned and predicted num slots" );
                }

                py::capsule do_delete_when_no_longer_needed(
                    ptr_temp_buffer, []( void* ptr )
                    {
                        auto ptr_to_del = reinterpret_cast<
                            std::vector< real_type >* >( ptr );
                        delete ptr_to_del;
                    } );

                return py_array_real_t( requ_num_slots, ptr_temp_buffer->data(),
                                        do_delete_when_no_longer_needed );
            } );

        #else  /* SIXTRL_DEMOTRACK_ENABLED */

        root.m.def( "Demotrack_belems_requ_num_slots",
            []( st::CBufferView const& SIXTRL_UNUSED( cbuffer ) ) -> size_type {
                throw std::runtime_error( "demotrack support disabled" );
                return size_type{ 0 }; } );

        root.m.def( "Demotrack_belems_requ_num_slots",
            []( int const dt_type_id ) -> size_type {
                throw std::runtime_error( "demotrack support disabled" );
                return size_type{ 0 }; } );

        root.m.def( "Demotrack_belems_can_convert",
            []( st::CBufferView const& cbuffer ) -> bool {
                throw std::runtime_error( "demotrack support disabled" );
                return false; } );

        root.m.def( "Demotrack_belems_num_stored_objects",
            []( tl::optional< py_array_real_t > flat_buffer_arg ) -> size_type {
                throw std::runtime_error( "demotrack support disabled" );
                return size_type{ 0 }; } );

        root.m.def( "Demotrack_belems_type_id",
            []( tl::optional< py_array_real_t > flat_buffer_arg,
                size_type const cur_slot_idx ) -> int
            {
                throw std::runtime_error( "demotrack support disabled" );
                return ::NS(DEMOTRACK_BEAM_ELEMENT_UNKNOWN); } );

        root.m_def( "Demotrack_belems_convert",
            []( st::CBufferView const& cbuffer ) {
                throw std::runtime_error( "demotrack support disabled" );
                return nullptr; } );

        #endif /* SIXTRL_DEMOTRACK_ENABLED */
    }
}
}
