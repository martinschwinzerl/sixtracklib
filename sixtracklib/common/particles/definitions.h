#ifndef SIXTRACKLIB_COMMON_PARTICLES_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_PARTICLES_DEFINITIONS_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/buffer/buffer_type.h"

    #if defined( __cplusplus )
        #include "sixtracklib/common/internal/obj_store_traits.hpp"
        #include "sixtracklib/common/internal/type_store_traits.hpp"
        #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_PARTICLE_ARGPTR_DEC )
    #define   SIXTRL_PARTICLE_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_DEC )
        #define  SIXTRL_PARTICLE_ARGPTR_DEC SIXTRL_BUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_PARTICLE_ARGPTR_DEC SIXTRL_DATAPTR_DEC
    #else
        #define  SIXTRL_PARTICLE_ARGPTR_DEC
    #endif
#endif /* SIXTRL_PARTICLE_ARGPTR_DEC */

#if !defined( SIXTRL_PARTICLE_DATAPTR_DEC )
    #define   SIXTRL_PARTICLE_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_DEC )
        #define  SIXTRL_PARTICLE_DATAPTR_DEC SIXTRL_BUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_PARTICLE_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else
        #define  SIXTRL_PARTICLE_DATAPTR_DEC
    #endif
#endif /* SIXTRL_PARTICLE_DATAPTR_DEC */

#if !defined( SIXTRL_PARTICLE_SET_ARGPTR_DEC )
    #define   SIXTRL_PARTICLE_SET_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_DEC )
        #define  SIXTRL_PARTICLE_SET_ARGPTR_DEC SIXTRL_BUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_PARTICLE_SET_ARGPTR_DEC SIXTRL_DATAPTR_DEC
    #else
        #define  SIXTRL_PARTICLE_SET_ARGPTR_DEC
    #endif
#endif /* SIXTRL_PARTICLE_ARGPTR_DEC */

#if !defined( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
    #define   SIXTRL_PARTICLE_SET_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_DEC )
        #define  SIXTRL_PARTICLE_SET_DATAPTR_DEC SIXTRL_BUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_PARTICLE_SET_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else
        #define  SIXTRL_PARTICLE_SET_DATAPTR_DEC
    #endif
#endif /* SIXTRL_PARTICLE_SET_DATAPTR_DEC */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host  */

/* ========================================================================= */

typedef SIXTRL_INT64_T  NS(particle_index_t);
typedef SIXTRL_REAL_T   NS(particle_real_t);
typedef SIXTRL_INT64_T  NS(particle_num_elements_t);
typedef SIXTRL_UINT64_T NS(particle_addr_t);

typedef SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t)*
        NS(particle_real_ptr_t);

typedef SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        NS(particle_real_const_ptr_t);

typedef SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_index_t)*
        NS(particle_index_ptr_t);

typedef SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_index_t) const*
        NS(particle_index_const_ptr_t);

typedef enum
{
    NS(PARTICLE_INIT_CHARGE0_MASS0_BETA0)  = 1,
    NS(PARTICLE_INIT_CHARGE0_MASS0_GAMMA0) = 2,
    NS(PARTICLE_INIT_CHARGE0_MASS0_PC0)    = 3
}
NS(particle_init_flag_t);

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(buffer_size_t) const
    NS(PARTICLES_NUM_INDEX_DATAPTRS) = ( NS(buffer_size_t) )4u;

SIXTRL_STATIC_VAR NS(buffer_size_t) const
    NS(PARTICLES_NUM_REAL_DATAPTRS) = ( NS(buffer_size_t) )17u;

SIXTRL_STATIC_VAR NS(buffer_size_t) const
    NS(PARTICLES_NUM_DATAPTRS) = ( NS(buffer_size_t) )21u;

#else /* defined( _GPUCODE ) */

typedef enum
{
    NS(PARTICLES_NUM_INDEX_DATAPTRS) = 4,
    NS(PARTICLES_NUM_REAL_DATAPTRS)  = 17,
    NS(PARTICLES_NUM_DATAPTRS)       = 21
}
NS(ParticlesGlobalConstantsEnum);

#endif /* !defined( _GPUCODE ) */


#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(particle_index_t)              particle_index_t;
    typedef ::NS(particle_real_t)               particle_real_t;
    typedef ::NS(particle_num_elements_t)       particle_num_elements_t;
    typedef ::NS(particle_addr_t)               particle_addr_t;

    typedef ::NS(particle_real_ptr_t)           particle_real_ptr_t;
    typedef ::NS(particle_real_const_ptr_t)     particle_real_const_ptr_t;

    typedef ::NS(particle_index_ptr_t)          particle_index_ptr_t;
    typedef ::NS(particle_index_const_ptr_t)    particle_index_const_ptr_t;
    typedef ::NS(particle_init_flag_t)          particle_init_flag_t;

    /* --------------------------------------------------------------------- */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST ::NS(buffer_size_t)
        PARTICLES_NUM_INDEX_DATAPTRS = static_cast< ::NS(buffer_size_t) >(
            ::NS(PARTICLES_NUM_INDEX_DATAPTRS) );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST ::NS(buffer_size_t)
        PARTICLES_NUM_REAL_DATAPTRS = static_cast< ::NS(buffer_size_t) >(
            ::NS(PARTICLES_NUM_REAL_DATAPTRS) );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST ::NS(buffer_size_t)
        PARTICLES_NUM_DATAPTRS = static_cast< ::NS(buffer_size_t) >(
            ::NS(PARTICLES_NUM_DATAPTRS) );

    /* --------------------------------------------------------------------- */

    typedef enum { PARTICLE_UNIT_IMPL_DEFAULT = 0 } particle_unit_impl_t;

    template< class ParticleT >
    struct ObjDataParticleTraits
    {
        static constexpr bool is_type = false;
        static constexpr particle_unit_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::PARTICLE_UNIT_IMPL_DEFAULT;
    };

    template< class ParticleT >
    constexpr bool ObjDataParticleTraits< ParticleT >::is_type;

    template< class ParticleT >
    constexpr particle_unit_impl_t ObjDataParticleTraits<
        ParticleT >::implementation;

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool Particle_is_type() SIXTRL_NOEXCEPT
    {
        return ObjDataParticleTraits< ParticleT >::is_type;
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_FN constexpr particle_unit_impl_t
    Particle_impl() SIXTRL_NOEXCEPT
    {
        return ObjDataParticleTraits< ParticleT >::implementation;
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    Particle_impl_default() SIXTRL_NOEXCEPT
    {
        return ( ObjDataParticleTraits< ParticleT >::implementation ==
                 SIXTRL_CXX_NAMESPACE::PARTICLE_UNIT_IMPL_DEFAULT );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT >
    struct ParticleTraits
    {
        typedef SIXTRL_CXX_NAMESPACE::particle_real_t         real_t;
        typedef SIXTRL_CXX_NAMESPACE::particle_index_t        index_t;
        typedef SIXTRL_CXX_NAMESPACE::particle_num_elements_t num_elements_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

        static constexpr arch_size_t index_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< index_t >();

        static constexpr num_elements_t num_particles = num_elements_t{ 1 };
    };

    template< class ParticleT >
    constexpr arch_size_t ParticleTraits< ParticleT >::real_alignment;

    template< class ParticleT >
    constexpr arch_size_t ParticleTraits< ParticleT >::index_alignment;

    template< class ParticleT >
    constexpr particle_num_elements_t ParticleTraits<
        ParticleT >::num_particles;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool Particle_is_scalar() SIXTRL_NOEXCEPT
    {
        return ( SIXTRL_CXX_NAMESPACE::ParticleTraits<
            ParticleT >::num_particles == 1u );
    }

    /* ********************************************************************* */

    typedef enum
    {
        PARTICLE_SET_IMPL_DEFAULT    = 0,
        PARTICLE_SET_IMPL_STD_VECTOR = 1
    }
    particle_set_impl_t;

    template< class PSetT > struct ObjDataParticleSetTraits
    {
        static constexpr bool is_type = false;
        static constexpr particle_set_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::PARTICLE_SET_IMPL_DEFAULT;
    };

    template< class PSetT >
    constexpr bool ObjDataParticleSetTraits< PSetT >::is_type;

    template< class PSetT >
    constexpr particle_set_impl_t ObjDataParticleSetTraits<
        PSetT >::implementation;


    template< class PSetT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool ParticleSet_is_type() SIXTRL_NOEXCEPT
    {
        return ObjDataParticleSetTraits< PSetT >::is_type;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_FN constexpr particle_set_impl_t
    ParticleSet_impl() SIXTRL_NOEXCEPT
    {
        return ObjDataParticleSetTraits< PSetT >::implementation;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    ParticleSet_impl_default() SIXTRL_NOEXCEPT
    {
        return ( SIXTRL_CXX_NAMESPACE::PARTICLE_SET_IMPL_DEFAULT ==
                 ObjDataParticleSetTraits< PSetT >::implementation );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    ParticleSet_impl_std_vector() SIXTRL_NOEXCEPT
    {
        return ( SIXTRL_CXX_NAMESPACE::PARTICLE_SET_IMPL_STD_VECTOR ==
                 ObjDataParticleSetTraits< PSetT >::implementation );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    ParticleSet_impl_has_field_addr() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ParticleSet_impl_default< PSetT >() ||
               SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >();
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleSetT >
    struct ParticleSetTraits
    {
        typedef SIXTRL_CXX_NAMESPACE::particle_real_t  real_t;
        typedef SIXTRL_CXX_NAMESPACE::particle_index_t index_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

        static constexpr arch_size_t index_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< index_t >();

        static constexpr arch_size_t addr_alignment = arch_size_t{ 8 };
    };

    template< class ParticleSetT >
    constexpr arch_size_t ParticleSetTraits< ParticleSetT >::real_alignment;

    template< class ParticleSetT >
    constexpr arch_size_t ParticleSetTraits< ParticleSetT >::index_alignment;

    template< class ParticleSetT >
    constexpr arch_size_t ParticleSetTraits< ParticleSetT >::addr_alignment;
}
#endif /* C++  */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_DEFINITIONS_H__ */

/* end: sixtracklib/common/particles/definitions.h */
