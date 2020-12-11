#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_TRACK_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_TRACK_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if !defined( __cplusplus )
        #include <stddef.h>
        #include <stdint.h>
        #include <stdlib.h>
    #else /* !defined( __cplusplus ) */
        #include <cstddef>
        #include <cstdint>
        #include <cstdlib>
        #include <type_traits>
    #endif /* !defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/track/track_config.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleT, class BeamElementT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ObjData_is_particle< ParticleT >() ||
        !SIXTRL_CXX_NAMESPACE::ObjData_is_beam_element< BeamElementT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    Track_particle_beam_element(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT /* p */,
        SIXTRL_BE_ARGPTR_DEC const BeamElementT *const SIXTRL_RESTRICT /* elem */,
        SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* SIXTRL_RESTRICT config )
    {
        return SIXTRL_CXX_NAMESPACE::TRACK_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, class BeamElementT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_is_particle< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_is_drift< BeamElementT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    Track_particle_beam_element(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const BeamElementT *const SIXTRL_RESTRICT elem,
        SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* SIXTRL_RESTRICT config )
    {
        return SIXTRL_CXX_NAMESPACE::Drift_track( p, elem, track_config );
    }

    template< class ParticleT, class BeamElementT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_is_particle< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_is_drift_exact< BeamElementT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    Track_particle_beam_element(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const BeamElementT *const SIXTRL_RESTRICT elem,
        SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* SIXTRL_RESTRICT config )
    {
        return SIXTRL_CXX_NAMESPACE::DriftExact_track( p, elem, track_config );
    }

    template< class ParticleT, class BeamElementT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_is_particle< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_is_multipole< BeamElementT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    Track_particle_beam_element(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const BeamElementT *const SIXTRL_RESTRICT elem,
        SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* SIXTRL_RESTRICT config )
    {
        return SIXTRL_CXX_NAMESPACE::Multipole_track( p, elem, track_config );
    }

    template< class ParticleT, class BeamElementT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_is_particle< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_is_cavity< BeamElementT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    Track_particle_beam_element(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const BeamElementT *const SIXTRL_RESTRICT elem,
        SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* SIXTRL_RESTRICT config )
    {
        return SIXTRL_CXX_NAMESPACE::Cavity_track( p, elem, track_config );
    }

    template< class ParticleT, class BeamElementT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_is_particle< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_is_xy_shift< BeamElementT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    Track_particle_beam_element(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const BeamElementT *const SIXTRL_RESTRICT elem,
        SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* SIXTRL_RESTRICT config )
    {
        return SIXTRL_CXX_NAMESPACE::XYShift_track( p, elem, track_config );
    }

    template< class ParticleT, class BeamElementT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_is_particle< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_is_srotation< BeamElementT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    Track_particle_beam_element(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const BeamElementT *const SIXTRL_RESTRICT elem,
        SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* SIXTRL_RESTRICT config )
    {
        return SIXTRL_CXX_NAMESPACE::SRotation_track( p, elem, track_config );
    }
}

template< class ParticleT, class BeamElementT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::track_status_t
NS(Track_particle_beam_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const BeamElementT *const SIXTRL_RESTRICT elem,
    SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* SIXTRL_RESTRICT config )
{
    return SIXTRL_CXX_NAMESPACE::Track_particle_beam_element( p, elem, config );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

struct NS(Particle);

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(Track_particle_beam_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC struct NS(Particle)* SIXTRL_RESTRICT particle,
    NS(belem_type_id_t) const belem_type_id,
    NS(belem_address_t) const belem_begin_addr,
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
            SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* ************************************************************************* */
/* ****                        Implementation                           **** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/beam_elements/drift/track.h"
    #include "sixtracklib/common/beam_elements/drift_exact/track.h"
    #include "sixtracklib/common/beam_elements/cavity/track.h"
    #include "sixtracklib/common/beam_elements/multipole/track.h"
    #include "sixtracklib/common/beam_elements/srotation/track.h"
    #include "sixtracklib/common/beam_elements/xy_shift/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE )
extern "C" {
#endif /* !defined( _GPUCODE ) */

SIXTRL_INLINE NS(track_status_t) NS(Track_particle_beam_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT particle,
    NS(belem_type_id) const type_id,
    NS(belem_address_t) const belem_begin_addr,
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
        SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT
{
    NS(track_status_t) success = SIXTRL_TRACK_GENERAL_FAILURE;
    if( belem_begin_addr == ( NS(belem_address_t) )0u ) return success;

    switch( type_id )
    {
        case NS(OBJECT_TYPE_DRIFT):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(Drift) const* ptr_belem_t;
            ptr_belem_t belem = SIXTRL_BELEM_ADDR_TO_PTR(
                ptr_belem_t, belem_begin_addr );

            success = NS(Drift_track)( particle, belem, track_config );
            break;
        }

        case NS(OBJECT_TYPE_DRIFT_EXACT):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(DriftExact) const* ptr_belem_t;
            ptr_belem_t belem = SIXTRL_BELEM_ADDR_TO_PTR(
                ptr_belem_t, belem_begin_addr );

            success = NS(DriftExact_track)( particle, belem, track_config );
            break;
        }

        case NS(OBJECT_TYPE_MULTIPOLE):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(Multipole) const* ptr_belem_t;
            ptr_belem_t belem = SIXTRL_BELEM_ADDR_TO_PTR(
                ptr_belem_t, belem_begin_addr );

            success = NS(Multipole_track)( particle, belem, track_config );
            break;
        }

        case NS(OBJECT_TYPE_CAVITY):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(Cavity) const* ptr_belem_t;
            ptr_belem_t belem = SIXTRL_BELEM_ADDR_TO_PTR(
                ptr_belem_t, belem_begin_addr );

            success = NS(Cavity_track)( particle, belem, track_config );
            break;
        }

        case NS(OBJECT_TYPE_SROTATION):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(SRotation) const* ptr_belem_t;
            ptr_belem_t belem = SIXTRL_BELEM_ADDR_TO_PTR(
                ptr_belem_t, belem_begin_addr );

            success = NS(SRotation_track)( particle, belem, track_config );
            break;
        }

        case NS(OBJECT_TYPE_XYSHIFT):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(XYShift) const* ptr_belem_t;
            ptr_belem_t belem = SIXTRL_BELEM_ADDR_TO_PTR(
                ptr_belem_t, belem_begin_addr );

            success = NS(XYShift_track)( particle, belem, track_config );
            break;
        }

        default:
        {
            SIXTRL_ASSERT( type_id != NS(OBJECT_TYPE_DRIFT) );
            SIXTRL_ASSERT( type_id != NS(OBJECT_TYPE_DRIFT_EXACT) );
            SIXTRL_ASSERT( type_id != NS(OBJECT_TYPE_MULTIPOLE) );
            SIXTRL_ASSERT( type_id != NS(OBJECT_TYPE_CAVITY) );
            SIXTRL_ASSERT( type_id != NS(OBJECT_TYPE_SROTATION) );
            SIXTRL_ASSERT( type_id != NS(OBJECT_TYPE_XYSHIFT) );

            success = SIXTRL_TRACK_GENERAL_FAILURE;
        }
    };

    return success;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_TRACK_H__ */
