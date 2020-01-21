#ifndef SIXTRACKLIB_COMMON_PARTICLE_PARTICLE_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLE_PARTICLE_DATA_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/internal/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/obj_type_traits.hpp"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/buffer.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class real_t, class index_t,
        std::size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(),
        std::size_t IAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    struct ParticleData
    {
        real_t  x             SIXTRL_ALIGN( RAlign );
        real_t  px            SIXTRL_ALIGN( RAlign );
        real_t  y             SIXTRL_ALIGN( RAlign );
        real_t  py            SIXTRL_ALIGN( RAlign );
        real_t  zeta          SIXTRL_ALIGN( RAlign );
        real_t  delta         SIXTRL_ALIGN( RAlign );
        real_t  psigma        SIXTRL_ALIGN( RAlign );

        index_t state         SIXTRL_ALIGN( IAlign );
        index_t at_element    SIXTRL_ALIGN( IAlign );
        index_t at_turn       SIXTRL_ALIGN( IAlign );
        index_t id            SIXTRL_ALIGN( IAlign );

        real_t  s             SIXTRL_ALIGN( RAlign );
        real_t  rvv           SIXTRL_ALIGN( RAlign );
        real_t  rpp           SIXTRL_ALIGN( RAlign );
        real_t  chi           SIXTRL_ALIGN( RAlign );
        real_t  charge_ratio  SIXTRL_ALIGN( RAlign );

        real_t  charge0       SIXTRL_ALIGN( RAlign );
        real_t  mass0         SIXTRL_ALIGN( RAlign );
        real_t  beta0         SIXTRL_ALIGN( RAlign );
        real_t  gamma0        SIXTRL_ALIGN( RAlign );
        real_t  pc0           SIXTRL_ALIGN( RAlign );
    };

    /* ------------------------------------------------------------------------------ */

    template< class R, class I, std::size_t RAlign, std::size_t IAlign >
    struct ParticleTraits< ParticleData< R, I, RAlign, IAlign > >
    {
        typedef SIXTRL_CXX_NAMESPACE::buffer_size_t size_type;
        typedef R                       real_t;
        typedef real_t const&           real_ret_t;
        typedef real_t const&           real_arg_t;

        typedef I                       index_t;
        typedef index_t const&          index_ret_t;
        typedef index_t const&          index_arg_t;

        static SIXTRL_FN constexpr size_type RealAlignment() SIXTRL_NOEXCEPT
        {
            return static_cast< size_type >( RAlign );
        }

        static SIXTRL_FN constexpr size_type IndexAlignment() SIXTRL_NOEXCEPT
        {
            return static_cast< size_type >( IAlign );
        }
    };

    /* ------------------------------------------------------------------------------ */

    template<> struct ObjDataStoreTraits< ParticleData< ::NS(particle_real_t),
        ::NS(particle_index_t), std::size_t{ 8 }, std::size_t{ 8 } > >
    {
        typedef SIXTRL_CXX_NAMESPACE::object_type_id_t type_id_t;

        static SIXTRL_FN constexpr type_id_t ObjTypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_PARTICLES;
        }
    };

    template<> struct ObjDataStoreCApiTraits< ParticleData< ::NS(particle_real_t),
        ::NS(particle_index_t), std::size_t{ 8 }, std::size_t{ 8 } > >
    {
        typedef ::NS(Particle) c_api_t;
    };

    template<> struct ParticleTraits< ParticleData< ::NS(particle_real_t),
        ::NS(particle_index_t), std::size_t{ 8 }, std::size_t{ 8 } > >
    {
        typedef SIXTRL_CXX_NAMESPACE::buffer_size_t size_type;
        typedef R                       real_t;
        typedef real_t                  real_ret_t;
        typedef real_t const            real_arg_t;

        typedef I                       index_t;
        typedef index_t                 index_ret_t;
        typedef index_t const           index_arg_t;

        static SIXTRL_FN constexpr size_type RealAlignment() SIXTRL_NOEXCEPT
        {
            return static_cast< size_type >( 8u );
        }

        static SIXTRL_FN constexpr size_type IndexAlignment() SIXTRL_NOEXCEPT
        {
            return static_cast< size_type >( 8u );
        }
    };
}

#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_PARTICLE_PARTICLE_DATA_CXX_HPP__ */
