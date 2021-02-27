#ifndef SIXTRACKLIB_COMMON_TRACK_TRACK_H__
#define SIXTRACKLIB_COMMON_TRACK_TRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(TrackConfig);

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(Track_particle_beam_element_from_cobj_index)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj,
    NS(size_type) const obj_index, bool increment_index_and_at_element,
    SIXTRL_TRACK_ARGPTR_DEC const struct NS(TrackConfig) *const
        SIXTRL_RESTRICT config ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(Track_particle_over_line_or_until_end_of_turn_cobj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT b,
    NS(size_type) obj_index, NS(size_type) const end_obj_index,
    SIXTRL_TRACK_ARGPTR_DEC const struct NS(TrackConfig) *const
        SIXTRL_RESTRICT config ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(Track_particle_until_turn_eot_marker_cobj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) const until_turn,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const*
        SIXTRL_RESTRICT lattice_indices_begin,
    NS(size_type) const end_of_turn_marker_index,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element,
    SIXTRL_TRACK_ARGPTR_DEC const struct NS(TrackConfig) *const
        SIXTRL_RESTRICT config ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/track/track_config.h"
    #include "sixtracklib/common/beam_elements/all_beam_elements.h"
    #include "sixtracklib/common/beam_elements/end_tracking/end_tracking.h"
    #include "sixtracklib/common/beam_elements/all_tracking_maps.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/generated/config.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(size_type) NS(Track_particle_beam_element_from_cobj_index)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj,
    NS(size_type) const obj_index, bool increment_index_and_at_element,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    st_size_t next_obj_index = obj_index;
    SIXTRL_ASSERT( obj_index != ( st_size_t )SIXTRL_TRACK_ILLEGAL_OBJ_INDEX );

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particle_is_active)( p ) );
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(CObjIndex_begin_addr)( obj ) !=
        ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS );


    switch( NS(CObjIndex_type_id)( obj ) )
    {
        case NS(COBJECTS_TYPE_ID_CAVITY):
        {
            NS(Cavity_track_particle)( p,
                NS(Cavity_const_from_cobj_index)( obj ) );
            break;
        }

        case NS(COBJECTS_TYPE_ID_DIPOLE_EDGE):
        {
            NS(DipoleEdge_track_particle)( p,
                NS(DipoleEdge_const_from_cobj_index)( obj ) );
            break;
        }

        case NS(COBJECTS_TYPE_ID_DRIFT):
        {
            NS(Drift_track_particle)( p,
                NS(Drift_const_from_cobj_index)( obj ) );

            #if defined( SIXTRL_APERTURE_CHECK_AT_DRIFT ) && \
                       ( SIXTRL_APERTURE_CHECK_AT_DRIFT == \
                         SIXTRL_GLOBAL_APERTURE_CHECK_ALWAYS )

                NS(LimitGlobal_track_particle)( p );
                ( void )config;

            #elif defined( SIXTRL_APERTURE_CHECK_AT_DRIFT ) && \
                         ( SIXTRL_APERTURE_CHECK_AT_DRIFT == \
                           SIXTRL_GLOBAL_APERTURE_CHECK_CONDITIONAL )

                #if defined( SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH )
                if( NS(Drift_length)( NS(Drift_const_from_cobj_index)(
                        obj ) ) >= ( NS(be_real_type)
                            )SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH )
                {
                    NS(LimitGlobal_track_particle)( p );
                }
                #else
                if( NS(Drift_length)( NS(Drift_const_from_cobj_index)(
                        obj ) ) >= ( NS(be_real_type) )0.0 )
                {
                    NS(LimitGlobal_track_particle)( p );
                }
                #endif /* defined( SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH ) */
                ( void )config;
            #elif defined( SIXTRL_APERTURE_CHECK_AT_DRIFT ) && \
                         ( SIXTRL_APERTURE_CHECK_AT_DRIFT ==  \
                           SIXTRL_GLOBAL_APERTURE_CHECK_NEVER )
                ( void )config;
            #else
                if( ( config != SIXTRL_NULLPTR ) &&
                    ( NS(Particle_is_active)( p ) ) )
                {
                    if( ( NS(TrackConfig_always_check_aperture_at_drift)(
                            config ) ) ||
                        ( ( NS(TrackConfig_conditional_check_aperture_at_drift)(
                            config ) ) &&
                          ( NS(TrackConfig_check_min_drift_length)( config ) <=
                            NS(Drift_length)(
                                NS(Drift_const_from_cobj_index)( obj ) ) ) ) )
                    {
                        SIXTRL_ASSERT( NS(TrackConfig_is_consistent)( config ) );
                        NS(LimitGlobal_track_particle_detailed)( p,
                            NS(TrackConfig_x_min)( config ),
                            NS(TrackConfig_x_max)( config ),
                            NS(TrackConfig_y_min)( config ),
                            NS(TrackConfig_y_max)( config ) );
                    }
                }
            #endif /* Aperture check */
            increment_index_and_at_element &= NS(Particle_is_active)( p );
            break;
        }

        case NS(COBJECTS_TYPE_ID_DRIFT_EXACT):
        {
            NS(DriftExact_track_particle)( p,
                NS(DriftExact_const_from_cobj_index)( obj ) );

            #if defined( SIXTRL_APERTURE_CHECK_AT_DRIFT ) && \
                       ( SIXTRL_APERTURE_CHECK_AT_DRIFT == \
                         SIXTRL_GLOBAL_APERTURE_CHECK_ALWAYS )

                NS(LimitGlobal_track_particle)( p );
                ( void )config;

            #elif defined( SIXTRL_APERTURE_CHECK_AT_DRIFT ) && \
                         ( SIXTRL_APERTURE_CHECK_AT_DRIFT == \
                           SIXTRL_GLOBAL_APERTURE_CHECK_CONDITIONAL )

                #if defined( SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH )
                if( NS(DriftExact_length)( NS(DriftExact_const_from_cobj_index)(
                        obj ) ) >= ( NS(be_real_type)
                            )SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH )
                {
                    NS(LimitGlobal_track_particle)( p );
                }
                #else
                if( NS(DriftExact_length)( NS(DriftExact_const_from_cobj_index)(
                        obj ) ) >= ( NS(be_real_type) )0.0 )
                {
                    NS(LimitGlobal_track_particle)( p );
                }
                #endif /* defined( SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH ) */
                ( void )config;
            #elif defined( SIXTRL_APERTURE_CHECK_AT_DRIFT ) && \
                         ( SIXTRL_APERTURE_CHECK_AT_DRIFT ==  \
                           SIXTRL_GLOBAL_APERTURE_CHECK_NEVER )
                ( void )config;
            #else
                if( ( config != SIXTRL_NULLPTR ) &&
                    ( NS(Particle_is_active)( p ) ) )
                {
                    if( ( NS(TrackConfig_always_check_aperture_at_drift)(
                            config ) ) ||
                        ( ( NS(TrackConfig_conditional_check_aperture_at_drift)(
                            config ) ) &&
                          ( NS(TrackConfig_check_min_drift_length)( config ) <=
                            NS(DriftExact_length)(
                                NS(DriftExact_const_from_cobj_index)( obj ) ) ) ) )
                    {
                        SIXTRL_ASSERT( NS(TrackConfig_is_consistent)( config ) );
                        NS(LimitGlobal_track_particle_detailed)( p,
                            NS(TrackConfig_x_min)( config ),
                            NS(TrackConfig_x_max)( config ),
                            NS(TrackConfig_y_min)( config ),
                            NS(TrackConfig_y_max)( config ) );
                    }
                }
            #endif /* Aperture check */
            increment_index_and_at_element &= NS(Particle_is_active)( p );
            break;
        }

        case NS(COBJECTS_TYPE_ID_END_TRACKING):
        {
            SIXTRL_BE_ARGPTR_DEC NS(EndTracking) const* elem =
                NS(EndTracking_const_from_cobj_index)( obj );

            SIXTRL_ASSERT( NS(Particle_is_active)( p ) );
            SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
            increment_index_and_at_element = false;
            next_obj_index = ( st_size_t )SIXTRL_TRACK_ILLEGAL_OBJ_INDEX;

            if( NS(EndTracking_ends_turn)( elem ) )
            {
                next_obj_index = NS(EndTracking_next_buffer_idx)( elem );

                NS(Particle_finish_turn)( p,
                    NS(EndTracking_next_at_element)( elem ) );
            }
            else if( NS(EndTracking_next_buffer_idx)( elem ) > obj_index )
            {
                next_obj_index = NS(EndTracking_next_buffer_idx)( elem );
                NS(Particle_set_at_element)( p,
                    NS(EndTracking_next_at_element)( elem ) );
            }

            break;
        }

        case NS(COBJECTS_TYPE_ID_LIMIT_RECT):
        {
            NS(LimitRect_track_particle)( p,
                NS(LimitRect_const_from_cobj_index)( obj ) );
            increment_index_and_at_element &= NS(Particle_is_active)( p );
            break;
        }

        case NS(COBJECTS_TYPE_ID_LIMIT_ELLIPSE):
        {
            NS(LimitEllipse_track_particle)( p,
                NS(LimitEllipse_const_from_cobj_index)( obj ) );
            increment_index_and_at_element &= NS(Particle_is_active)( p );
            break;
        }

        case NS(COBJECTS_TYPE_ID_LIMIT_RECT_ELLIPSE):
        {
            NS(LimitRectEllipse_track_particle)( p,
                NS(LimitRectEllipse_const_from_cobj_index)( obj ) );
            increment_index_and_at_element &= NS(Particle_is_active)( p );
            break;
        }

        case NS(COBJECTS_TYPE_ID_MULTIPOLE):
        {
            NS(Multipole_track_particle)( p,
                NS(Multipole_const_from_cobj_index)( obj ) );
            break;
        }

        case NS(COBJECTS_TYPE_ID_MONITOR):
        {
            NS(Monitor_track_particle)( p,
                NS(Monitor_const_from_cobj_index)( obj ) );
            break;
        }

        case NS(COBJECTS_TYPE_ID_RF_MULTIPOLE):
        {
            NS(RFMultipole_track_particle)( p,
                NS(RFMultipole_const_from_cobj_index)( obj ) );
            break;
        }

        case NS(COBJECTS_TYPE_ID_SROTATION):
        {
            NS(SRotation_track_particle)( p,
                NS(SRotation_const_from_cobj_index)( obj ) );
            break;
        }

        case NS(COBJECTS_TYPE_ID_XY_SHIFT):
        {
            NS(XYShift_track_particle)( p,
                NS(XYShift_const_from_cobj_index)( obj ) );
            break;
        }

        #if defined( SIXTRL_TRACK_SPACECHARGE ) && \
                   ( SIXTRL_TRACK_SPACECHARGE == SIXTRL_TRACK_MAP_ENABLED )

        case NS(COBJECTS_TYPE_ID_SC_COASTING):
        {
            NS(SCCoasting_track_particle)( p,
                NS(SCCoasting_const_from_cobj_index)( obj ) );
            break;
        }

        case NS(COBJECTS_TYPE_ID_SC_QGAUSSIAN_PROFILE):
        {
            NS(SCQGaussProfile_track_particle)( p,
                NS(SCQGaussProfile_const_from_cobj_index)( obj ) );
            break;
        }

        #elif defined( SIXTRL_TRACK_SPACECHARGE ) && \
                     ( SIXTRL_TRACK_SPACECHARGE == SIXTRL_TRACK_MAP_SKIP )

        case NS(COBJECTS_TYPE_ID_SC_COASTING): { break; }
        case NS(COBJECTS_TYPE_ID_SC_QGAUSSIAN_PROFILE): { break; }

        #else

        case NS(COBJECTS_TYPE_ID_SC_COASTING): {
            NS(Particle_mark_as_lost)( p );
            increment_index_and_at_element = false;
            break; }

        case NS(COBJECTS_TYPE_ID_SC_QGAUSSIAN_PROFILE): {
            Particle_mark_as_lost
            increment_index_and_at_element = false;
            break; }

        #endif /* SIXTRL_TRACK_SPACECHARGE */

        default:
        {
            next_obj_index = ( st_size_t )SIXTRL_TRACK_ILLEGAL_OBJ_INDEX;
            increment_index_and_at_element = false;
        }
    };

    if( increment_index_and_at_element )
    {
        SIXTRL_ASSERT( NS(Particle_is_active)( p ) );
        NS(Particle_increment_at_element)( p );
        ++next_obj_index;
    }

    return next_obj_index;
}

SIXTRL_INLINE NS(size_type)
NS(Track_particle_over_line_or_until_end_of_turn_cobj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT begin,
    NS(size_type) obj_index, NS(size_type) const end_obj_index,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT
{
    NS(particle_index_type) const current_turn = NS(Particle_at_turn)( p );

    SIXTRL_ASSERT( begin != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( obj_index <= end_obj_index );
    SIXTRL_ASSERT( end_obj_index < (
        NS(size_type) )SIXTRL_TRACK_ILLEGAL_OBJ_INDEX );

    SIXTRL_ASSERT( NS(Particle_at_turn)( p ) >=
        ( NS(particle_index_type) )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN );

    SIXTRL_ASSERT( NS(Particle_at_turn)( p ) <=
        ( NS(particle_index_type) )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN );

    while( ( NS(Particle_is_active)( p ) ) && ( obj_index < end_obj_index ) &&
           ( NS(Particle_at_turn)( p ) == current_turn ) )
    {
        obj_index = NS(Track_particle_beam_element_from_cobj_index)(
            p, &begin[ obj_index ], obj_index, true, config );
    }

    return obj_index;
}

SIXTRL_INLINE NS(size_type) NS(Track_particle_until_turn_eot_marker_cobj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) const until_turn,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT lattice,
    NS(size_type) const eot_mk_index, NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT
{
    NS(size_type) obj_index = line_start_index;

    SIXTRL_ASSERT( NS(Particle_is_active)( p ) );
    SIXTRL_ASSERT( lattice != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( line_start_index <= eot_mk_index );
    SIXTRL_ASSERT( NS(CObjIndex_is_end_tracking)( &lattice[ eot_mk_index ] ) );

    SIXTRL_ASSERT( NS(EndTracking_lattice_contains_no_illegal_markers_cobj)(
        lattice, eot_mk_index + 1, line_start_index, line_start_at_element ) );

    SIXTRL_ASSERT( NS(EndTracking_is_legal_eot_marker_in_lattice_cobj)(
        NS(EndTracking_const_from_cobj_index)( &lattice[ eot_mk_index ] ),
            eot_mk_index, eot_mk_index + 1u, line_start_index,
                line_start_at_element ) );

    SIXTRL_ASSERT( until_turn <= ( NS(particle_index_type)
                        )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN );

    SIXTRL_ASSERT( until_turn >= ( NS(particle_index_type)
                        )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN );

    SIXTRL_ASSERT( NS(Particle_at_turn)( p ) >= ( NS(particle_index_type)
                        )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN );

    SIXTRL_ASSERT( NS(Particle_at_turn)( p ) <= ( NS(particle_index_type)
                        )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN );

    SIXTRL_ASSERT( NS(Particle_at_element)( p ) >= (
        ( ( NS(particle_index_type) )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) +
          ( NS(particle_index_type) )line_start_at_element ) );

    SIXTRL_ASSERT( line_start_at_element < (
        ( ( NS(particle_index_type) )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT ) -
        ( ( NS(particle_index_type) )eot_mk_index ) ) );

    obj_index += ( NS(size_type) )(
        NS(Particle_at_element)( p ) - line_start_at_element );

    while( ( NS(Particle_at_turn)( p ) < until_turn ) &&
           ( NS(Particle_is_active)( p ) ) )
    {
        SIXTRL_ASSERT( obj_index <= eot_mk_index );
        SIXTRL_ASSERT( obj_index >= line_start_index );
        SIXTRL_ASSERT( NS(Particle_at_element)( p ) >= line_start_at_element );

        obj_index = NS(Track_particle_beam_element_from_cobj_index)(
            p, &lattice[ obj_index ], obj_index, true, config );
    }

    return obj_index;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_TRACK_TRACK_H__ */
