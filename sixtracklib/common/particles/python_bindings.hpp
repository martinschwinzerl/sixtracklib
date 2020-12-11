#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_PARTICLES_PYTHON_BYINDINGS_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_PARTICLES_PYTHON_BYINDINGS_CXX_HPP__
/* Particle Beam Element */

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
#include "sixtracklib/common/particle.hpp"
#include "sixtracklib/common/internal/compiler_compability.h"
#include "sixtracklib/common/internal/type_store_traits.hpp"
#include "sixtracklib/common/cobjects/python_bindings.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
    void init_particle_unit_for_type(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< E >& SIXTRL_RESTRICT_REF particle )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
        typedef SIXTRL_PARTICLE_ARGPTR_DEC E particle_t;
        typedef typename st::ParticleTraits< E >::real_t  real_t;
        typedef typename st::ParticleTraits< E >::index_t index_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_existing_type const_real_existing_t;

        typedef typename st::TypeMethodParamTraits<
                    index_t >::const_argument_type const_index_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    index_t >::const_existing_type const_index_existing_t;

        static_assert( st::Particle_is_type< E >(),
                       "E required to be a particle class" );

        particle.def( py::init( [](
            const_real_arg_t x, const_real_arg_t px,
            const_real_arg_t y, const_real_arg_t py,
            const_real_arg_t zeta, const_real_arg_t delta,
            const_index_arg_t state, const_index_arg_t at_element,
            const_index_arg_t at_turn, const_index_arg_t id,
            const_real_arg_t psigma, const_real_arg_t rpp,
            const_real_arg_t rvv, const_real_arg_t chi,
            const_real_arg_t charge_ratio, const_real_arg_t charge0,
            const_real_arg_t mass0, const_real_arg_t beta0,
            const_real_arg_t gamma0, const_real_arg_t pc0,
            const_real_arg_t s )
        {
            auto ptr_particle = st::make_unique< E >();
            if( st::ARCH_STATUS_SUCCESS !=
                st::Particle_init( ptr_particle.get(), x, px, y, py, zeta,
                    delta, state, at_element, at_turn, id, psigma, rpp, rvv,
                        chi, charge_ratio, charge0, mass0, beta0, gamma0, pc0,
                            s ) )
            {
                ptr_particle.reset( nullptr );
            }

            return std::move( ptr_particle );
        } ),
        py::arg( "x" ) = st::Particle_default_x< E >(),
        py::arg( "px" ) = st::Particle_default_px< E >(),
        py::arg( "y" ) = st::Particle_default_y< E >(),
        py::arg( "py" ) = st::Particle_default_py< E >(),
        py::arg( "zeta" ) = st::Particle_default_zeta< E >(),
        py::arg( "delta" ) = st::Particle_default_delta< E >(),
        py::arg( "state" ) = st::Particle_default_state< E >(),
        py::arg( "at_element" ) = st::Particle_default_at_element< E >(),
        py::arg( "at_turn" ) = st::Particle_default_at_turn< E >(),
        py::arg( "id" ) = st::Particle_default_id< E >(),
        py::arg( "psigma" ) = st::Particle_default_psigma< E >(),
        py::arg( "rpp" ) = st::Particle_default_rpp< E >(),
        py::arg( "rvv" ) = st::Particle_default_rvv< E >(),
        py::arg( "chi" ) = st::Particle_default_chi< E >(),
        py::arg( "charge_ratio" ) = st::Particle_default_charge_ratio< E >(),
        py::arg( "charge0" ) = st::Particle_default_charge0< E >(),
        py::arg( "mass0" ) = st::Particle_default_mass0< E >(),
        py::arg( "beta0" ) = st::Particle_default_beta0< E >(),
        py::arg( "gamma0" ) = st::Particle_default_gamma0< E >(),
        py::arg( "pc0" ) = st::Particle_default_pc0< E >(),
        py::arg( "s" ) = st::Particle_default_s< E >() );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        particle.def_property( "x",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_x( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t x )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_x(
                        std::addressof( particle ), x ) )
                    throw std::runtime_error( "Error during st::Particle_set_x" );
            } );

        particle.def_property( "px",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_px( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t px )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_px(
                        std::addressof( particle ), px ) )
                    throw std::runtime_error(
                        "Error during st::Particle_set_px" );
            } );

        particle.def_property( "y",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_y( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t y )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_y(
                        std::addressof( particle ), y ) )
                    throw std::runtime_error(
                        "Error during st::Particle_set_y" );
            } );

        particle.def_property( "py",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_py( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t py )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_py(
                        std::addressof( particle ), py ) )
                    throw std::runtime_error(
                        "Error during st::Particle_set_py" );
            } );

        particle.def_property( "zeta",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_zeta( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t zeta )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_update_zeta(
                        std::addressof( particle ), zeta ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_update_zeta" );
                }
            } );

        particle.def( "set_zeta",
            []( particle_t& particle, const_real_arg_t zeta )
            {
                if( st::ARCH_STATUS_SUCCESS == st::Particle_set_zeta(
                    std::addressof( particle ), zeta ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_zeta" );
                }

                return std::addressof( particle );
            }, py::arg( "zeta" ) );

        particle.def_property( "sigma",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_sigma( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t sigma )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_update_sigma(
                        std::addressof( particle ), sigma ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_update_sigma" );
                }
            } );

        particle.def_property( "tau",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_tau( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t tau )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_update_tau(
                        std::addressof( particle ), tau ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_update_tau" );
                }
            } );

        particle.def_property( "delta",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_delta( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t delta )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_update_delta(
                        std::addressof( particle ), delta ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_update_delta" );
                }
            } );

        particle.def( "set_delta",
            []( particle_t& particle, const_real_arg_t delta )
            {
                if( st::ARCH_STATUS_SUCCESS == st::Particle_set_delta(
                    std::addressof( particle ), delta ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_delta" );
                }

                return std::addressof( particle );
            }, py::arg( "delta" ) );

        particle.def_property( "psigma",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_psigma( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t psigma )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_update_psigma(
                            std::addressof( particle ), psigma ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_update_psigma" );
                }
            } );

        particle.def( "set_psigma",
            []( particle_t& particle, const_real_arg_t psigma )
            {
                if( st::ARCH_STATUS_SUCCESS == st::Particle_set_psigma(
                    std::addressof( particle ), psigma ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_psigma" );
                }

                return std::addressof( particle );
            }, py::arg( "psigma" ) );

        particle.def_property( "ptau",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_ptau( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t ptau )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_update_ptau(
                        std::addressof( particle ), ptau ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_ptau" );
                }
            } );

        particle.def_property( "rpp",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_rpp( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t rpp )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_rpp(
                        std::addressof( particle ), rpp ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_rpp" );
                }
            } );

        particle.def_property( "rvv",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_rvv( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t rvv )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_rvv(
                        std::addressof( particle ), rvv ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_rvv" );
                }
            } );

        particle.def_property( "chi",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_chi( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t chi )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_chi(
                        std::addressof( particle ), chi ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_chi" );
                }
            } );

        particle.def_property( "charge_ratio",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_charge_ratio( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t charge_ratio )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_charge_ratio(
                        std::addressof( particle ), charge_ratio ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_charge_ratio" );
                }
            } );

        particle.def_property_readonly( "mass_ratio",
            []( particle_t const& particle ) -> real_t
            {
                return st::Particle_mass_ratio( std::addressof( particle ) );
            } );

        particle.def_property_readonly( "mass",
            []( particle_t const& particle ) -> real_t
            {
                return st::Particle_mass( std::addressof( particle ) );
            } );

        particle.def_property_readonly( "charge",
            []( particle_t const& particle ) -> real_t
            {
                return st::Particle_charge( std::addressof( particle ) );
            } );

        particle.def_property_readonly( "energy0",
            []( particle_t const& particle ) -> real_t
            {
                return st::Particle_energy0( std::addressof( particle ) );
            } );

        particle.def_property( "energy",
            []( particle_t const& particle ) -> real_t
            {
                return st::Particle_energy( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t new_energy )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_update_energy(
                        std::addressof( particle ), new_energy ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_update_energy" );
                }
            } );

        particle.def( "add_to_energy",
            []( particle_t& particle, const_real_arg_t delta_energy )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_add_to_energy(
                        std::addressof( particle ), delta_energy ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_add_to_energy" );
                }

                return std::addressof( particle );
            } );

        particle.def_property_readonly( "beta",
            []( particle_t const& particle ) -> real_t
            {
                return st::Particle_beta( std::addressof( particle ) );
            } );

        particle.def_property( "charge0",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_charge0( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t charge0 )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_charge0(
                        std::addressof( particle ), charge0 ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_charge0" );
                }
            } );

        particle.def_property( "mass0",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_mass0( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t mass0 )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_mass0(
                        std::addressof( particle ), mass0 ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_mass0" );
                }
            } );

        particle.def_property( "beta0",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_beta0( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t beta0 )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_beta0(
                        std::addressof( particle ), beta0 ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_beta0" );
                }
            } );

        particle.def_property( "gamma0",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_gamma0( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t gamma0 )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_gamma0(
                        std::addressof( particle ), gamma0 ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_gamma0" );
                }
            } );

        particle.def_property( "pc0",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_pc0( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t pc0 )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_pc0(
                        std::addressof( particle ), pc0 ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_pc0" );
                }
            } );

        particle.def_property( "s",
            []( particle_t const& particle ) -> const_real_existing_t
            {
                return st::Particle_s( std::addressof( particle ) );
            },
            []( particle_t& particle, const_real_arg_t s )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_s(
                        std::addressof( particle ), s ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_s" );
                }
            } );

        particle.def_property( "state",
            []( particle_t const& particle ) -> const_index_existing_t
            {
                return st::Particle_state( std::addressof( particle ) );
            },
            []( particle_t& particle, const_index_arg_t state )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_state(
                        std::addressof( particle ), state ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_state" );
                }
            } );

        particle.def_property( "at_element",
            []( particle_t const& particle ) -> const_index_existing_t
            {
                return st::Particle_at_element( std::addressof( particle ) );
            },
            []( particle_t& particle, const_index_arg_t at_element )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_at_element(
                        std::addressof( particle ), at_element ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_at_element" );
                }
            } );

        particle.def_property( "at_turn",
            []( particle_t const& particle ) -> const_index_existing_t
            {
                return st::Particle_at_turn( std::addressof( particle ) );
            },
            []( particle_t& particle, const_index_arg_t at_turn )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_at_turn(
                        std::addressof( particle ), at_turn ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_at_turn" );
                }
            } );

        particle.def_property( "id",
            []( particle_t const& particle ) -> const_index_existing_t
            {
                return st::Particle_id( std::addressof( particle ) );
            },
            []( particle_t& particle, const_index_arg_t id )
            {
                if( st::ARCH_STATUS_SUCCESS != st::Particle_set_id(
                        std::addressof( particle ), id ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_set_id" );
                }
            } );

        particle.def_property_readonly( "is_lost",
            []( particle_t const& particle ) -> bool
            {
                return st::Particle_is_lost( std::addressof( particle ) );
            } );

        particle.def_property_readonly( "is_not_lost",
            []( particle_t const& particle ) -> bool
            {
                return st::Particle_is_not_lost( std::addressof( particle ) );
            } );

        particle.def_property_readonly( "has_any_lost",
            []( particle_t const& particle ) -> bool
            {
                return st::Particle_has_any_lost( std::addressof( particle ) );
            } );

        particle.def_property_readonly( "has_any_not_lost",
            []( particle_t const& particle ) -> bool
            {
                return st::Particle_has_any_not_lost(
                    std::addressof( particle ) );
            } );

        particle.def( "mark_as_lost", []( particle_t& particle )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::Particle_mark_as_lost( std::addressof( particle ) ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_mark_as_lost" );
                }

                return std::addressof( particle );
            } );

        particle.def( "update_state_if_not_lost",
            []( particle_t& particle, const_index_arg_t new_state )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::Particle_update_state_if_not_lost(
                        std::addressof( particle ), new_state ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_update_state_if_not_lost" );
                }

                return std::addressof( particle );
            } );

        particle.def( "increment_at_element", []( particle_t& particle )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::Particle_increment_at_element(
                        std::addressof( particle ) ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_increment_at_element" );
                }

                return std::addressof( particle );
            } );

        particle.def( "increment_at_turn",
            []( particle_t& particle, const_index_arg_t at_element,
                const_real_arg_t s )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::Particle_increment_at_turn_detailed(
                        std::addressof( particle ), at_element, s ) )
                {
                    throw std::runtime_error(
                        "Error during st::Particle_increment_at_turn_detailed" );
                }

                return std::addressof( particle );
            },
            py::arg( "at_element" ) = index_t{ 0 },
            py::arg( "s" ) = real_t{ 0 } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        particle.def( "__repr__", []( particle_t const& particle )
            {
                auto ptr = std::addressof( particle );
                std::ostringstream a2str;
                a2str << "<sixtrack::Particle: x="
                      << st::Particle_x( ptr ) << "\r\n"
                      << "                    px="
                      << st::Particle_px( ptr ) << "\r\n"
                      << "                     y="
                      << st::Particle_y( ptr ) << "\r\n"
                      << "                    py="
                      << st::Particle_py( ptr ) << "\r\n"
                      << "                  zeta="
                      << st::Particle_zeta( ptr ) << "\r\n"
                      << "                 delta="
                      << st::Particle_delta( ptr ) << "\r\n"
                      << "                 state="
                      << st::Particle_state( ptr ) << "\r\n"
                      << "            at_element="
                      << st::Particle_at_element( ptr ) << "\r\n"
                      << "               at_turn="
                      << st::Particle_at_turn( ptr ) << "\r\n"
                      << "                    id="
                      << st::Particle_id( ptr ) << "\r\n"
                      << "                psigma="
                      << st::Particle_psigma( ptr ) << "\r\n"
                      << "                   rpp="
                      << st::Particle_rpp( ptr ) << "\r\n"
                      << "                   rvv="
                      << st::Particle_rvv( ptr ) << "\r\n"
                      << "                   chi="
                      << st::Particle_chi( ptr ) << "\r\n"
                      << "          charge_ratio="
                      << st::Particle_charge_ratio( ptr ) << "\r\n"
                      << "               charge0="
                      << st::Particle_charge0( ptr ) << "\r\n"
                      << "                 mass0="
                      << st::Particle_mass0( ptr ) << "\r\n"
                      << "                 beta0="
                      << st::Particle_beta0( ptr ) << "\r\n"
                      << "                gamma0="
                      << st::Particle_gamma0( ptr ) << "\r\n"
                      << "                   pc0="
                      << st::Particle_pc0( ptr ) << "\r\n"
                      << "                     s="
                      << st::Particle_s( ptr ) << "\r\n>";
                return a2str.str(); } );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E, class RealType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< E >(), void >::type
    init_particle_unit_additional_real_api(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( particle_obj ) )
    {
        return;
    }

    template< class E, class RealType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< E >(), void >::type
    init_particle_unit_additional_real_api(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF particle_obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef typename std::decay< RealType >::type real_t;
        typedef typename TypeMethodParamTraits< real_t >::const_argument_type
                const_real_arg_t;

        particle_obj.def( "set_x",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t x )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_x(
                std::addressof( p ), x ) ) throw std::runtime_error(
                    "Error during st::Particle_set_x" );
            return std::addressof( p );
        }, py::arg( "x" ) );

        particle_obj.def( "set_px",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t px )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_px(
                std::addressof( p ), px ) ) throw std::runtime_error(
                    "Error during st::Particle_set_px" );
            return std::addressof( p );
        }, py::arg( "px" ) );

        particle_obj.def( "set_y",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t y )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_y(
                std::addressof( p ), y ) ) throw std::runtime_error(
                    "Error during st::Particle_set_y" );
            return std::addressof( p );
        }, py::arg( "y" ) );

        particle_obj.def( "set_py",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t py )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_py(
                std::addressof( p ), py ) ) throw std::runtime_error(
                    "Error during st::Particle_set_py" );
            return std::addressof( p );
        }, py::arg( "py" ) );

        particle_obj.def( "set_zeta",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t zeta )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_zeta(
                std::addressof( p ), zeta ) ) throw std::runtime_error(
                    "Error during st::Particle_set_zeta" );
            return std::addressof( p );
        }, py::arg( "zeta" ) );

        particle_obj.def( "set_delta",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t delta )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_delta(
                std::addressof( p ), delta ) ) throw std::runtime_error(
                    "Error during st::Particle_set_delta" );
            return std::addressof( p );
        }, py::arg( "delta" ) );

        particle_obj.def( "set_rpp",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t rpp )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_rpp(
                std::addressof( p ), rpp ) ) throw std::runtime_error(
                    "Error during st::Particle_set_rpp" );
            return std::addressof( p );
        }, py::arg( "rpp" ) );

        particle_obj.def( "set_rvv",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t rvv )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_rvv(
                std::addressof( p ), rvv ) ) throw std::runtime_error(
                    "Error during st::Particle_set_rvv" );
            return std::addressof( p );
        }, py::arg( "rvv" ) );

        particle_obj.def( "set_chi",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t chi )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_chi(
                std::addressof( p ), chi ) ) throw std::runtime_error(
                    "Error during st::Particle_set_chi" );
            return std::addressof( p );
        }, py::arg( "chi" ) );

        particle_obj.def( "set_charge_ratio",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t charge_ratio )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_charge_ratio(
                std::addressof( p ), charge_ratio ) ) throw std::runtime_error(
                    "Error during st::Particle_set_charge_ratio" );
            return std::addressof( p );
        }, py::arg( "charge_ratio" ) );

        particle_obj.def( "set_charge0",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t charge0 )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_charge0(
                std::addressof( p ), charge0 ) ) throw std::runtime_error(
                    "Error during st::Particle_set_charge0" );
            return std::addressof( p );
        }, py::arg( "charge0" ) );

        particle_obj.def( "set_mass0",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t mass0 )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_mass0(
                std::addressof( p ), mass0 ) ) throw std::runtime_error(
                    "Error during st::Particle_set_mass0" );
            return std::addressof( p );
        }, py::arg( "mass0" ) );

        particle_obj.def( "set_beta0",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t beta0 )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_beta0(
                std::addressof( p ), beta0 ) ) throw std::runtime_error(
                    "Error during st::Particle_set_beta0" );
            return std::addressof( p );
        }, py::arg( "beta0" ) );

        particle_obj.def( "set_gamma0",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t gamma0 )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_gamma0(
                std::addressof( p ), gamma0 ) ) throw std::runtime_error(
                    "Error during st::Particle_set_gamma0" );
            return std::addressof( p );
        }, py::arg( "gamma0" ) );

        particle_obj.def( "set_pc0",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t pc0 )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_pc0(
                std::addressof( p ), pc0 ) ) throw std::runtime_error(
                    "Error during st::Particle_set_pc0" );
            return std::addressof( p );
        }, py::arg( "pc0" ) );

        particle_obj.def( "set_s",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t s )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_s(
                std::addressof( p ), s ) ) throw std::runtime_error(
                    "Error during st::Particle_set_s" );
            return std::addressof( p );
        }, py::arg( "s" ) );

        particle_obj.def( "update_zeta",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t zeta )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_zeta(
                std::addressof( p ), zeta ) ) throw std::runtime_error(
                    "Error during st::Particle_update_zeta" );
            return std::addressof( p );
        }, py::arg( "zeta" ) );

        particle_obj.def( "update_delta",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t delta )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_delta(
                std::addressof( p ), delta ) ) throw std::runtime_error(
                    "Error during st::Particle_update_delta" );
            return std::addressof( p );
        }, py::arg( "delta" ) );

        particle_obj.def( "update_tau",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t tau )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_update_tau(
                std::addressof( p ), tau ) ) throw std::runtime_error(
                    "Error during st::Particle_update_tau" );
            return std::addressof( p );
        }, py::arg( "tau" ) );

        particle_obj.def( "update_ptau",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t ptau )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_update_ptau(
                std::addressof( p ), ptau ) ) throw std::runtime_error(
                    "Error during st::Particle_update_ptau" );
            return std::addressof( p );
        }, py::arg( "ptau" ) );

        particle_obj.def( "update_sigma",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t sigma )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_update_sigma(
                std::addressof( p ), sigma ) ) throw std::runtime_error(
                    "Error during st::Particle_update_sigma" );
            return std::addressof( p );
        }, py::arg( "sigma" ) );

        particle_obj.def( "update_psigma",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_real_arg_t psigma )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_update_psigma(
                std::addressof( p ), psigma ) ) throw std::runtime_error(
                    "Error during st::Particle_update_psigma" );
            return std::addressof( p );
        }, py::arg( "psigma" ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E, class IndexType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< E >(), void >::type
    init_particle_unit_additional_index_api(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( particle_obj ) )
    {
        return;
    }

    template< class E, class IndexType >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< E >(), void >::type
    init_particle_unit_additional_index_api(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF particle_obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef typename std::decay< IndexType >::type index_t;
        typedef typename TypeMethodParamTraits< index_t >::const_argument_type
                const_index_arg_t;

        particle_obj.def( "set_state",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_index_arg_t state )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_state(
                std::addressof( p ), state ) ) throw std::runtime_error(
                    "Error during st::Particle_set_state" );
            return std::addressof( p );
        }, py::arg( "state" ) );

        particle_obj.def( "set_at_element",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_index_arg_t at_element )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_at_element(
                std::addressof( p ), at_element ) ) throw std::runtime_error(
                    "Error during st::Particle_set_at_element" );
            return std::addressof( p );
        }, py::arg( "at_element" ) );

        particle_obj.def( "set_at_turn",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_index_arg_t at_turn )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_at_turn(
                std::addressof( p ), at_turn ) ) throw std::runtime_error(
                    "Error during st::Particle_set_at_turn" );
            return std::addressof( p );
        }, py::arg( "at_turn" ) );

        particle_obj.def( "set_id",
        []( SIXTRL_PARTICLE_ARGPTR_DEC E& p, const_index_arg_t id )
        {
            if( st::ARCH_STATUS_SUCCESS != st::Particle_set_id(
                std::addressof( p ), id ) ) throw std::runtime_error(
                    "Error during st::Particle_set_id" );
            return std::addressof( p );
        }, py::arg( "id" ) );
    }

    /* --------------------------------------------------------------------- */

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::Particle_is_type< E >() ||
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        void >::type
    init_particle_unit_cobjects_direct_for_type(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( particle ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_view_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_obj ),
        SIXTRL_PARTICLE_ARGPTR_DEC const E *const
            SIXTRL_UNUSED( ptr_dummy ) = nullptr )
    {
        return;
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        void >::type
    init_particle_unit_cobjects_direct_for_type(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< E >& SIXTRL_RESTRICT_REF particle_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >&
            SIXTRL_RESTRICT_REF cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >&
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_PARTICLE_ARGPTR_DEC const E *const
            SIXTRL_UNUSED( ptr_dummy ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef SIXTRL_PARTICLE_ARGPTR_DEC E particle_t;
        typedef typename st::ParticleTraits< E >::real_t  real_t;
        typedef typename st::ParticleTraits< E >::index_t index_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_existing_type const_real_existing_t;

        typedef typename st::TypeMethodParamTraits<
                    index_t >::const_argument_type const_index_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    index_t >::const_existing_type const_index_existing_t;

        st::python::setup_cobjects_store_direct_base_for_type< E >(
            m, particle_obj, cbuffer_view_obj, cbuffer_obj );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* free methods / functions */

        typedef st::CBufferView cbuffer_view_t;
        typedef st::CBuffer cbuffer_t;

        particle_obj.def_static( "create_new",
        []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& SIXTRL_RESTRICT_REF cbuffer )
        {
            particle_t* ptr_particle = cbuffer.create_new< E >();
            if( ptr_particle == nullptr ) throw std::runtime_error(
                    "Unable to create particle on cbuffer" );
            return ptr_particle;
        }, py::arg( "cbuffer" ) );

        particle_obj.def_static( "add",
        []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& SIXTRL_RESTRICT_REF cbuffer,
            const_real_arg_t x, const_real_arg_t px,
            const_real_arg_t y, const_real_arg_t py,
            const_real_arg_t zeta, const_real_arg_t delta,
            const_index_arg_t state, const_index_arg_t at_element,
            const_index_arg_t at_turn, const_index_arg_t id,
            const_real_arg_t psigma, const_real_arg_t rpp,
            const_real_arg_t rvv, const_real_arg_t chi,
            const_real_arg_t charge_ratio, const_real_arg_t charge0,
            const_real_arg_t mass0, const_real_arg_t beta0,
            const_real_arg_t gamma0, const_real_arg_t pc0,
            const_real_arg_t s )
        {
            particle_t* ptr = cbuffer.add< E >( x, px, y, py, zeta, delta,
                state, at_element, at_turn, id, psigma, rpp, rvv, chi,
                    charge_ratio, charge0, mass0, beta0, gamma0, pc0, s );
            if( ptr == nullptr ) throw std::runtime_error(
                    "Unable to create particle on cbuffer" );
            return ptr;
        },
        py::arg( "cbuffer" ), py::arg( "x" ), py::arg( "px" ),
        py::arg( "y" ), py::arg( "py" ), py::arg( "zeta" ),
        py::arg( "delta" ), py::arg( "state" ), py::arg( "at_element" ),
        py::arg( "at_turn" ), py::arg( "id" ), py::arg( "psigma" ),
        py::arg( "rpp" ), py::arg( "rvv" ), py::arg( "chi" ),
        py::arg( "charge_ratio" ), py::arg( "charge0" ), py::arg( "mass0" ),
        py::arg( "beta0" ), py::arg( "gamma0" ), py::arg( "pc0" ),
        py::arg( "s" ) );
    }

    /* ********************************************************************* */

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN void init_particle_set_for_type(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< E >& SIXTRL_RESTRICT_REF pset )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
        typedef SIXTRL_PARTICLE_ARGPTR_DEC E particle_set_t;
        typedef typename st::ParticleSetTraits< E >::real_t  real_t;
        typedef typename st::ParticleSetTraits< E >::index_t index_t;
        typedef st::particle_num_elements_t num_elems_t;
        typedef st::particle_addr_t address_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_existing_type const_real_existing_t;

        typedef typename st::TypeMethodParamTraits<
                    index_t >::const_argument_type const_index_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    index_t >::const_existing_type const_index_existing_t;

        static_assert( st::ParticleSet_is_type< E >(),
                       "E required to be a ParticleSet class " );

        pset.def( py::init( []( num_elems_t const num_particles,
            num_elems_t const capacity )
        {
            auto pset = st::make_unique< E >();
            st::ParticleSet_preset( pset.get() );

            if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_init(
                    pset.get(), num_particles, capacity ) )
            {
                pset.reset( nullptr );
            }

            return std::move( pset );
        } ),
        py::arg( "num_particles" ), py::arg( "capacity" ) = num_elems_t{ 0 } );


        pset.def( py::init( [](
            num_elems_t const num_particles,
            address_t const x_addr, address_t const px_addr,
            address_t const y_addr, address_t const py_addr,
            address_t const zeta_addr, address_t const delta_addr,
            address_t const state_addr, address_t const at_element_addr,
            address_t const at_turn_addr, address_t const particle_id_addr,
            address_t const psigma_addr, address_t const rpp_addr,
            address_t const rvv_addr, address_t const chi_addr,
            address_t const charge_ratio_addr, address_t const charge0_addr,
            address_t const mass0_addr, address_t const beta0_addr,
            address_t const gamma0_addr, address_t const pc0_addr,
            address_t const s_addr, num_elems_t const capacity )
        {
            auto pset = st::make_unique< E >();
            st::ParticleSet_preset( pset.get() );

            if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_init(
                    pset.get(), num_particles, x_addr, px_addr, y_addr, py_addr,
                    zeta_addr, delta_addr, state_addr, at_element_addr,
                    at_turn_addr, particle_id_addr, psigma_addr, rpp_addr,
                    rvv_addr, chi_addr, charge_ratio_addr, charge0_addr,
                    mass0_addr, beta0_addr, gamma0_addr, pc0_addr, s_addr,
                    capacity ) )
            {
                pset.reset( nullptr );
            }

            return std::move( pset );
        } ),
        py::arg( "num_particles" ), py::arg( "x_addr" ), py::arg( "px_addr" ),
        py::arg( "y_addr" ), py::arg( "py_addr" ), py::arg( "zeta_addr" ),
        py::arg( "delta_addr" ), py::arg( "state_addr" ),
        py::arg( "at_element_addr" ), py::arg( "at_turn_addr" ),
        py::arg( "particle_id_addr" ), py::arg( "psigma_addr" ),
        py::arg( "rpp_addr" ), py::arg( "rvv_addr" ), py::arg( "chi_addr" ),
        py::arg( "charge_ratio_addr" ), py::arg( "charge0_addr" ),
        py::arg( "mass0_addr" ), py::arg( "beta0_addr" ),
        py::arg( "gamma0_addr" ), py::arg( "pc0_addr" ), py::arg( "s_addr" ),
        py::arg( "capacity" ) = num_elems_t{ 0 } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "num_particles",
           []( particle_set_t const& pset ) -> num_elems_t
           {
               return st::ParticleSet_num_particles( std::addressof( pset ) );
           },
           []( particle_set_t& pset, num_elems_t const num_particles )
           {
               if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_num_particles( std::addressof(
                        pset ), num_particles ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_num_particles" );
                }
           }
        );

        pset.def_property( "capacity",
           []( particle_set_t const& pset ) -> num_elems_t
           {
               return st::ParticleSet_capacity( std::addressof( pset ) );
           },
           []( particle_set_t& pset, num_elems_t const capacity )
           {
               if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_capacity( std::addressof(
                        pset ), capacity ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_capacity" );
                }
           }
        );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "x_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_x_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const x_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_x_addr( std::addressof(
                        pset ), x_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_x_addr" );
                }
            } );

        pset.def( "x",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_x( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_x",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t x_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_x_value(
                        std::addressof( pset ), idx, x_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_x" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "x_value" ) );

        pset.def( "set_all_x",
            []( particle_set_t& pset, const_real_arg_t x_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_x_values( std::addressof(
                        pset ), x_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_x_values" );
                }

                return std::addressof( pset );
            }, py::arg( "x_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "px_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_px_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const px_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_px_addr( std::addressof(
                        pset ), px_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_px_addr" );
                }
            } );

        pset.def( "px",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_px( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_px",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t px_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_px_value(
                        std::addressof( pset ), idx, px_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_px" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "px_value" ) );

        pset.def( "set_all_px",
            []( particle_set_t& pset, const_real_arg_t px_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_px_values( std::addressof(
                        pset ), px_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_px_values" );
                }

                return std::addressof( pset );
            }, py::arg( "px_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "y_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_y_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const y_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_y_addr( std::addressof(
                        pset ), y_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_y_addr" );
                }
            } );

        pset.def( "y",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_y( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_y",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t y_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_y_value(
                        std::addressof( pset ), idx, y_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_y" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "y_value" ) );

        pset.def( "set_all_y",
            []( particle_set_t& pset, const_real_arg_t y_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_y_values( std::addressof(
                        pset ), y_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_y_values" );
                }

                return std::addressof( pset );
            }, py::arg( "y_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "py_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_py_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const py_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_py_addr( std::addressof(
                        pset ), py_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_py_addr" );
                }
            } );

        pset.def( "py",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_py( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_py",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t py_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_py_value(
                        std::addressof( pset ), idx, py_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_py" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "py_value" ) );

        pset.def( "set_all_py",
            []( particle_set_t& pset, const_real_arg_t py_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_py_values( std::addressof(
                        pset ), py_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_py_values" );
                }

                return std::addressof( pset );
            }, py::arg( "py_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "zeta_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_zeta_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const zeta_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_zeta_addr( std::addressof(
                        pset ), zeta_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_zeta_addr" );
                }
            } );

        pset.def( "zeta",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_zeta( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_zeta",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t zeta_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_zeta_value(
                        std::addressof( pset ), idx, zeta_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_zeta" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "zeta_value" ) );

        pset.def( "set_all_zeta",
            []( particle_set_t& pset, const_real_arg_t zeta_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_zeta_values( std::addressof(
                        pset ), zeta_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_zeta_values" );
                }

                return std::addressof( pset );
            }, py::arg( "zeta_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "delta_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_delta_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const delta_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_delta_addr( std::addressof(
                        pset ), delta_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_delta_addr" );
                }
            } );

        pset.def( "delta",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_delta( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_delta",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t delta_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_delta_value(
                        std::addressof( pset ), idx, delta_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_delta" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "delta_value" ) );

        pset.def( "set_all_delta",
            []( particle_set_t& pset, const_real_arg_t delta_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_delta_values( std::addressof(
                        pset ), delta_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_delta_values" );
                }

                return std::addressof( pset );
            }, py::arg( "delta_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "state_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_state_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const state_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_state_addr( std::addressof(
                        pset ), state_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_state_addr" );
                }
            } );

        pset.def( "state",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_index_existing_t
            {
                return st::ParticleSet_state( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_state",
            []( particle_set_t& pset, num_elems_t const idx,
                const_index_arg_t state_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_state_value(
                        std::addressof( pset ), idx, state_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_state" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "state_value" ) );

        pset.def( "set_all_state",
            []( particle_set_t& pset, const_index_arg_t state_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_state_values( std::addressof(
                        pset ), state_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_state_values" );
                }

                return std::addressof( pset );
            }, py::arg( "state_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "at_element_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_at_element_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const at_element_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_at_element_addr( std::addressof(
                        pset ), at_element_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_at_element_addr" );
                }
            } );

        pset.def( "at_element",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_index_existing_t
            {
                return st::ParticleSet_at_element( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_at_element",
            []( particle_set_t& pset, num_elems_t const idx,
                const_index_arg_t at_element_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_at_element_value( std::addressof(
                        pset ), idx, at_element_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_at_element" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "at_element_value" ) );

        pset.def( "set_all_at_element",
            []( particle_set_t& pset, const_index_arg_t at_element_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_at_element_values( std::addressof(
                        pset ), at_element_value ) )
                {
                    throw std::runtime_error( "Error during "
                        "st::ParticleSet_set_all_at_element_values" );
                }

                return std::addressof( pset );
            }, py::arg( "at_element_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "at_turn_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_at_turn_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const at_turn_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_at_turn_addr( std::addressof(
                        pset ), at_turn_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_at_turn_addr" );
                }
            } );

        pset.def( "at_turn",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_index_existing_t
            {
                return st::ParticleSet_at_turn( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_at_turn",
            []( particle_set_t& pset, num_elems_t const idx,
                const_index_arg_t at_turn_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_at_turn_value( std::addressof( pset ),
                        idx, at_turn_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_at_turn" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "at_turn_value" ) );

        pset.def( "set_all_at_turn",
            []( particle_set_t& pset, const_index_arg_t at_turn_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_at_turn_values( std::addressof(
                        pset ), at_turn_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_at_turn_values" );
                }

                return std::addressof( pset );
            }, py::arg( "at_turn_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "particle_id_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_particle_id_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const particle_id_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_particle_id_addr( std::addressof(
                        pset ), particle_id_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_particle_id_addr" );
                }
            } );

        pset.def( "particle_id",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_index_existing_t
            {
                return st::ParticleSet_particle_id(
                    std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_particle_id",
            []( particle_set_t& pset, num_elems_t const idx,
                const_index_arg_t particle_id_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_particle_id_value( std::addressof(
                        pset ), idx, particle_id_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_particle_id" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "particle_id_value" ) );

        pset.def( "set_all_particle_id",
            []( particle_set_t& pset, const_index_arg_t particle_id_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_particle_id_values( std::addressof(
                        pset ), particle_id_value ) )
                {
                    throw std::runtime_error( "Error during "
                        "st::ParticleSet_set_all_particle_id_values" );
                }

                return std::addressof( pset );
            }, py::arg( "particle_id_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "psigma_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_psigma_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const psigma_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_psigma_addr( std::addressof(
                        pset ), psigma_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_psigma_addr" );
                }
            } );

        pset.def( "psigma",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_psigma( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_psigma",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t psigma_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_psigma_value(
                        std::addressof( pset ), idx, psigma_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_psigma" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "psigma_value" ) );

        pset.def( "set_all_psigma",
            []( particle_set_t& pset, const_real_arg_t psigma_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_psigma_values( std::addressof(
                        pset ), psigma_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_psigma_values" );
                }

                return std::addressof( pset );
            }, py::arg( "psigma_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "rpp_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_rpp_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const rpp_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_rpp_addr( std::addressof(
                        pset ), rpp_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_rpp_addr" );
                }
            } );

        pset.def( "rpp",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_rpp( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_rpp",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t rpp_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_rpp_value(
                        std::addressof( pset ), idx, rpp_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_rpp" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "rpp_value" ) );

        pset.def( "set_all_rpp",
            []( particle_set_t& pset, const_real_arg_t rpp_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_rpp_values( std::addressof(
                        pset ), rpp_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_rpp_values" );
                }

                return std::addressof( pset );
            }, py::arg( "rpp_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "rvv_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_rvv_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const rvv_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_rvv_addr( std::addressof(
                        pset ), rvv_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_rvv_addr" );
                }
            } );

        pset.def( "rvv",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_rvv( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_rvv",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t rvv_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_rvv_value(
                        std::addressof( pset ), idx, rvv_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_rvv" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "rvv_value" ) );

        pset.def( "set_all_rvv",
            []( particle_set_t& pset, const_real_arg_t rvv_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_rvv_values( std::addressof(
                        pset ), rvv_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_rvv_values" );
                }

                return std::addressof( pset );
            }, py::arg( "rvv_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "chi_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_chi_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const chi_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_chi_addr( std::addressof(
                        pset ), chi_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_chi_addr" );
                }
            } );

        pset.def( "chi",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_chi( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_chi",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t chi_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_chi_value(
                        std::addressof( pset ), idx, chi_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_chi" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "chi_value" ) );

        pset.def( "set_all_chi",
            []( particle_set_t& pset, const_real_arg_t chi_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_chi_values( std::addressof(
                        pset ), chi_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_chi_values" );
                }

                return std::addressof( pset );
            }, py::arg( "chi_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "charge_ratio_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_charge_ratio_addr(
                    std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const charge_ratio_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_charge_ratio_addr( std::addressof(
                        pset ), charge_ratio_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_charge_ratio_addr" );
                }
            } );

        pset.def( "charge_ratio",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_charge_ratio( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_charge_ratio",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t charge_ratio_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_charge_ratio_value(
                        std::addressof( pset ), idx, charge_ratio_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_charge_ratio" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "charge_ratio_value" ) );

        pset.def( "set_all_charge_ratio",
            []( particle_set_t& pset, const_real_arg_t charge_ratio_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_charge_ratio_values( std::addressof(
                        pset ), charge_ratio_value ) )
                {
                    throw std::runtime_error( "Error during "
                        "st::ParticleSet_set_all_charge_ratio_values" );
                }

                return std::addressof( pset );
            }, py::arg( "charge_ratio_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "charge0_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_charge0_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const charge0_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_charge0_addr( std::addressof(
                        pset ), charge0_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_charge0_addr" );
                }
            } );

        pset.def( "charge0",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_charge0( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_charge0",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t charge0_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_charge0_value(
                        std::addressof( pset ), idx, charge0_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_charge0" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "charge0_value" ) );

        pset.def( "set_all_charge0",
            []( particle_set_t& pset, const_real_arg_t charge0_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_charge0_values( std::addressof(
                        pset ), charge0_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_charge0_values" );
                }

                return std::addressof( pset );
            }, py::arg( "charge0_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "mass0_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_mass0_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const mass0_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_mass0_addr( std::addressof(
                        pset ), mass0_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_mass0_addr" );
                }
            } );

        pset.def( "mass0",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_mass0( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_mass0",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t mass0_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_mass0_value(
                        std::addressof( pset ), idx, mass0_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_mass0" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "mass0_value" ) );

        pset.def( "set_all_mass0",
            []( particle_set_t& pset, const_real_arg_t mass0_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_mass0_values( std::addressof(
                        pset ), mass0_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_mass0_values" );
                }

                return std::addressof( pset );
            }, py::arg( "mass0_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "beta0_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_beta0_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const beta0_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_beta0_addr( std::addressof(
                        pset ), beta0_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_beta0_addr" );
                }
            } );

        pset.def( "beta0",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_beta0( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_beta0",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t beta0_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_beta0_value(
                        std::addressof( pset ), idx, beta0_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_beta0" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "beta0_value" ) );

        pset.def( "set_all_beta0",
            []( particle_set_t& pset, const_real_arg_t beta0_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_beta0_values( std::addressof(
                        pset ), beta0_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_beta0_values" );
                }

                return std::addressof( pset );
            }, py::arg( "beta0_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "gamma0_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_gamma0_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const gamma0_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_gamma0_addr( std::addressof(
                        pset ), gamma0_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_gamma0_addr" );
                }
            } );

        pset.def( "gamma0",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_gamma0( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_gamma0",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t gamma0_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_gamma0_value(
                        std::addressof( pset ), idx, gamma0_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_gamma0" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "gamma0_value" ) );

        pset.def( "set_all_gamma0",
            []( particle_set_t& pset, const_real_arg_t gamma0_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_gamma0_values( std::addressof(
                        pset ), gamma0_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_gamma0_values" );
                }

                return std::addressof( pset );
            }, py::arg( "gamma0_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "pc0_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_pc0_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const pc0_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_pc0_addr( std::addressof(
                        pset ), pc0_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_pc0_addr" );
                }
            } );

        pset.def( "pc0",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_pc0( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_pc0",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t pc0_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_pc0_value(
                        std::addressof( pset ), idx, pc0_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_pc0" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "pc0_value" ) );

        pset.def( "set_all_pc0",
            []( particle_set_t& pset, const_real_arg_t pc0_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_pc0_values( std::addressof(
                        pset ), pc0_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_pc0_values" );
                }

                return std::addressof( pset );
            }, py::arg( "pc0_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def_property( "s_addr",
            []( particle_set_t const& pset ) -> address_t
            {
                return st::ParticleSet_s_addr( std::addressof( pset ) );
            },
            []( particle_set_t& pset, address_t const s_addr )
            {
                if( st::ARCH_STATUS_SUCCESS ==
                    st::ParticleSet_set_s_addr( std::addressof(
                        pset ), s_addr ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_s_addr" );
                }
            } );

        pset.def( "s",
            []( particle_set_t const& pset, num_elems_t const idx ) ->
            const_real_existing_t
            {
                return st::ParticleSet_s( std::addressof( pset ), idx );
            }, py::arg( "idx" ) );

        pset.def( "set_s",
            []( particle_set_t& pset, num_elems_t const idx,
                const_real_arg_t s_value )
            {
                if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_set_s_value(
                        std::addressof( pset ), idx, s_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_s" );
                }

                return std::addressof( pset );
            }, py::arg( "idx" ), py::arg( "s_value" ) );

        pset.def( "set_all_s",
            []( particle_set_t& pset, const_real_arg_t s_value )
            {
                if( st::ARCH_STATUS_SUCCESS !=
                    st::ParticleSet_set_all_s_values( std::addressof(
                        pset ), s_value ) )
                {
                    throw std::runtime_error(
                        "Error during st::ParticleSet_set_all_s_values" );
                }

                return std::addressof( pset );
            }, py::arg( "s_value" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        pset.def( "__repr__", []( particle_set_t const& pset )
            {
                auto ptr = std::addressof( pset );
                std::ostringstream a2str;
                a2str << "<sixtrack::ParticleSet: num_particles="
                      << st::ParticleSet_num_particles( ptr ) << ", "
                      << "capacity="
                      << st::ParticleSet_capacity( ptr ) << ">";
                return a2str.str(); } );
    }

    /* --------------------------------------------------------------------- */

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
         !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< E >() ||
         !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
         void >::type
     init_particle_set_cobjects_direct_for_type(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF particle,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_view_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_obj ),
        SIXTRL_PARTICLE_ARGPTR_DEC const E *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_dummy ) = nullptr )
     {
         return;
     }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(), void >::type
    init_particle_set_cobjects_direct_for_type(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< E >& SIXTRL_RESTRICT_REF pset_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >&
            SIXTRL_RESTRICT_REF cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >&
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_PARTICLE_ARGPTR_DEC const E *const
            SIXTRL_UNUSED( ptr_dummy ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
        typedef SIXTRL_PARTICLE_ARGPTR_DEC E particle_set_t;
        typedef typename st::ParticleTraits< E >::real_t real_t;
        typedef st::particle_num_elements_t num_elems_t;
        typedef st::particle_addr_t address_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_argument_type const_real_arg_t;

        typedef typename st::TypeMethodParamTraits<
                    real_t >::const_existing_type const_real_existing_t;

        st::python::setup_cobjects_store_direct_base_for_type< E >(
            m, pset_obj, cbuffer_view_obj, cbuffer_obj );

        typedef st::CBufferView cbuffer_view_t;
        typedef st::CBuffer cbuffer_t;

        pset_obj.def_static( "create_new",
        []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& cbuffer,
            num_elems_t const num_particles, num_elems_t const capacity )
        {
            particle_set_t* pset =
                cbuffer.create_new< E >( num_particles, capacity );

            if( pset == nullptr ) throw std::runtime_error(
                "Unable to create particle set on cbuffer" );
            return pset;
        }, py::arg( "cbuffer" ), py::arg( "num_particles" ),
               py::arg( "capacity" ) = num_elems_t{ 0 } );

        pset_obj.def_static( "add",
        []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& SIXTRL_RESTRICT_REF cbuffer,
            num_elems_t const num_particles,
            address_t const x_addr, address_t const px_addr,
            address_t const y_addr, address_t const py_addr,
            address_t const zeta_addr, address_t const delta_addr,
            address_t const state_addr, address_t const at_element_addr,
            address_t const at_turn_addr, address_t const particle_id_addr,
            address_t const psigma_addr, address_t const rpp_addr,
            address_t const rvv_addr, address_t const chi_addr,
            address_t const charge_ratio_addr, address_t const charge0_addr,
            address_t const mass0_addr, address_t const beta0_addr,
            address_t const gamma0_addr, address_t const pc0_addr,
            address_t const s_addr, num_elems_t const capacity )
        {
            particle_set_t* pset = cbuffer.add< E >(
                    num_particles, x_addr, px_addr, y_addr, py_addr,
                    zeta_addr, delta_addr, state_addr, at_element_addr,
                    at_turn_addr, particle_id_addr, psigma_addr, rpp_addr,
                    rvv_addr, chi_addr, charge_ratio_addr, charge0_addr,
                    mass0_addr, beta0_addr, gamma0_addr, pc0_addr, s_addr,
                    capacity );

            if( pset == nullptr ) throw std::runtime_error(
                    "Unable to create particle set on cbuffer" );

            return pset;
        },
        py::arg( "cbuffer" ),
        py::arg( "num_particles" ), py::arg( "x_addr" ), py::arg( "px_addr" ),
        py::arg( "y_addr" ), py::arg( "py_addr" ), py::arg( "zeta_addr" ),
        py::arg( "delta_addr" ), py::arg( "state_addr" ),
        py::arg( "at_element_addr" ), py::arg( "at_turn_addr" ),
        py::arg( "particle_id_addr" ), py::arg( "psigma_addr" ),
        py::arg( "rpp_addr" ), py::arg( "rvv_addr" ), py::arg( "chi_addr" ),
        py::arg( "charge_ratio_addr" ), py::arg( "charge0_addr" ),
        py::arg( "mass0_addr" ), py::arg( "beta0_addr" ),
        py::arg( "gamma0_addr" ), py::arg( "pc0_addr" ), py::arg( "s_addr" ),
        py::arg( "capacity" ) = num_elems_t{ 0 } );
    }

    /* --------------------------------------------------------------------- */

    template< class ParticleSetT, class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
         !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >() ||
         !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(), void >::type
     init_particle_set_particle_unit_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< ParticleSetT >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( pset_obj ),
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_pset_dummy ) = nullptr,
        SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_particle_dummy ) = nullptr )
     {
         return;
     }

    template< class ParticleSetT, class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(), void >::type
    init_particle_set_particle_unit_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< ParticleSetT >& SIXTRL_RESTRICT_REF pset_obj,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const
            SIXTRL_UNUSED( ptr_pset ) = nullptr,
        SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
            SIXTRL_UNUSED( ptr_particle ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT particle_set_t;
        typedef SIXTRL_PARTICLE_ARGPTR_DEC ParticleT particle_t;
        typedef st::particle_num_elements_t num_elems_t;

        pset_obj.def( "store_to_particle",
          []( particle_set_t const& pset, particle_t& p, num_elems_t const idx )
          {
              if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_store_to_particle(
                  std::addressof( pset ), std::addressof( p ), idx ) )
                  throw std::runtime_error( "unable to store from particle set"
                      "to particle" );

                  return std::addressof( pset );
          }, py::arg( "particle" ), py::arg( "index" ) );

        pset_obj.def( "load_from_particle",
          []( particle_set_t& pset, particle_t const& p, num_elems_t const idx )
          {
              if( st::ARCH_STATUS_SUCCESS != st::ParticleSet_load_from_particle(
                  std::addressof( pset ), std::addressof( p ), idx ) )
                  throw std::runtime_error( "unable to store from particle set"
                      "to particle" );
                  return std::addressof( pset );
          }, py::arg( "particle" ), py::arg( "index" ) );
    }

    /* --------------------------------------------------------------------- */

    template< class ParticleT, class ParticleSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() ||
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >(),
        void >::type
    init_particle_unit_particle_set_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< ParticleT >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( particles_obj ),
        pybind11::class_< ParticleSetT >& SIXTRL_RESTRICT_REF
            SIXTRL_UNUSED( pset_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_view_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_obj ),
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_pset_dummy ) = nullptr,
        SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_particle_dummy ) = nullptr )
    {
        return;
    }

    template< class ParticleT, class ParticleSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >(),
        void >::type
    init_particle_unit_particle_set_bindings_for_types(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< ParticleT >& SIXTRL_RESTRICT_REF particle_obj,
        pybind11::class_< ParticleSetT >& SIXTRL_RESTRICT_REF pset_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >*
            SIXTRL_RESTRICT_REF cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >*
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_pset_dummy ) = nullptr,
        SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_particle_dummy ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef typename st::ObjDataDelegateTraits< ParticleT,
            st::STORAGE_BE_DEFAULT >::delegate_t DelegateParticleDefaultT;

        typedef typename st::ObjDataDelegateTraits< ParticleT,
            st::STORAGE_BE_COBJECTS >::delegate_t DelegateParticleCObjT;

        st::python::init_particle_unit_for_type< ParticleT >( m, particle_obj );
        st::python::init_particle_set_for_type< ParticleSetT >( m, pset_obj );

        st::python::init_particle_set_particle_unit_for_types<
            ParticleSetT, ParticleT >( m, pset_obj );

        if( ( st::Particle_is_type< DelegateParticleDefaultT >() ) &&
            ( !std::is_same< DelegateParticleDefaultT, ParticleT >::value ) )
        {
            st::python::init_particle_set_particle_unit_for_types<
                ParticleSetT, DelegateParticleDefaultT >( m, pset_obj );
        }

        if( ( st::Particle_is_type< DelegateParticleCObjT >() ) &&
            ( !std::is_same< DelegateParticleCObjT, ParticleT >::value ) )
        {
            st::python::init_particle_set_particle_unit_for_types<
                ParticleSetT, DelegateParticleCObjT >( m, pset_obj );
        }

        if( ( cbuffer_view_obj != nullptr ) && ( cbuffer_obj != nullptr ) )
        {
            st::python::setup_cobjects_load_store_for_type< ParticleT
                >( m, particle_obj, *cbuffer_view_obj, *cbuffer_obj );

            st::python::init_particle_unit_cobjects_direct_for_type< ParticleT
                >( m, particle_obj, *cbuffer_view_obj, *cbuffer_obj );

            st::python::setup_cobjects_load_store_for_type< ParticleSetT
                >( m, pset_obj, *cbuffer_view_obj, *cbuffer_obj );

            st::python::init_particle_set_cobjects_direct_for_type< ParticleSetT
                >( m, pset_obj, *cbuffer_view_obj, *cbuffer_obj );
        }
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_PARTICLES_PYTHON_BYINDINGS_CXX_HPP__ */
