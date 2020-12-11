#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_DERIVED_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_DERIVED_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/particles/particle_set_api.h"
    #include "sixtracklib/common/particles/particle_unit_api.h"
    #include "sixtracklib/common/particles/particle_unit_derived_api.h"
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* setup particle_id */

    template< class ParticleSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_setup_particle_ids(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT /*pset*/,
        typename TypeMethodParamTraits< typename ParticleSetTraits<
            ParticleSetT >::index_t >::const_argument_type /*min_particle_id*/ =
                typename ParticleSetTraits< ParticleSetT >::index_t{ 0 },
        bool const /*only_active_particles*/ = false ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >() &&
        SIXTRL_CXX_NAMESPACE::Type_is_scalar< typename ParticleSetTraits<
            ParticleSetT >::index_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_setup_particle_ids(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT pset,
        typename TypeMethodParamTraits< typename ParticleTraits<
            ParticleSetT >::index_t >::const_argument_type min_particle_id =
                typename ParticleSetTraits< ParticleSetT >::index_t{ 0 },
        bool const only_active_particles = false ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ParticleSetTraits< ParticleSetT >::index_t index_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( ( pset != SIXTRL_NULLPTR ) && ( min_particle_id >= index_t{ 0 } ) &&
            ( st::ParticleSet_num_particles( pset ) >
              st::particle_num_elements_t{ 0 } ) )
        {
            auto state_it = st::ParticleSet_const_state_begin( pset );
            auto id_it  = st::ParticleSet_particle_id_begin( pset );
            auto id_end = st::ParticleSet_particle_id_end( pset );

            SIXTRL_ASSERT( state_it != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( id_it != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( reinterpret_cast< std::uintptr_t >( id_it ) >=
                           reinterpret_cast< std::uintptr_t >( id_end ) );

            index_t next_particle_id = min_particle_id;

            for( ; id_it != id_end ; ++id_it, ++state_it )
            {
                if( ( !only_active_particles ) ||
                    ( *state_it == index_t{ 1 } ) )
                {
                    *id_it = next_particle_id++;
                }
            }

            if( next_particle_id > min_particle_id )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }
}

/* setup particle_id */

template< class ParticleSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ParticleSet_setup_particle_ids)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT pset,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::ParticleTraits< ParticleSetT >::index_t
            >::const_argument_type min_particle_id = typename
                SIXTRL_CXX_NAMESPACE::ParticleSetTraits< ParticleSetT
                    >::index_t{ 0 },
    bool const only_active_particles = false ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_setup_particle_ids(
        pset, min_particle_id, only_active_particles );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSet_setup_particle_ids)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_index_t) const min_particle_id,
    bool const only_active_particles ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_setup_particle_ids)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_index_t) const min_particle_id,
    bool const only_active_particles ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    typedef NS(particle_index_t) index_t;

    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( pset != SIXTRL_NULLPTR ) && ( min_particle_id >= ( index_t )0 ) &&
        ( NS(ParticleSet_num_particles)( pset ) >
            ( NS(particle_num_elements_t) )0 ) )
    {
        index_t next_particle_id = min_particle_id;
        SIXTRL_PARTICLE_SET_DATAPTR_DEC index_t const* state_it =
            NS(ParticleSet_const_state_begin)( pset );

        SIXTRL_PARTICLE_SET_DATAPTR_DEC index_t* id_it =
            NS(ParticleSet_particle_id_begin)( pset );

        SIXTRL_PARTICLE_SET_DATAPTR_DEC index_t* id_end =
            NS(ParticleSet_particle_id_end)( pset );

        SIXTRL_ASSERT( state_it != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( id_it    != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( ( ( uintptr_t )id_it ) >= ( uintptr_t )( id_end ) );

        for( ; id_it != id_end ; ++id_it, ++state_it )
        {
            if( ( !only_active_particles ) || ( *state_it == ( index_t )1 ) )
            {
                *id_it = next_particle_id++;
            }
        }

        if( next_particle_id > min_particle_id )
        {
            status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
        }
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_DERIVED_H__ */
