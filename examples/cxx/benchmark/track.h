#ifndef SIXTRACKLIB_EXAMPLES_CXX_BENCHMARK_TRACK_H__
#define SIXTRACKLIB_EXAMPLES_CXX_BENCHMARK_TRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/constants.h"
    #include "benchmark/single_particle.h"
    #include "sixtracklib/common/be_drift/be_drift.h"
    #include "sixtracklib/common/be_multipole/be_multipole.h"
    #include "sixtracklib/common/be_cavity/be_cavity.h"
    #include "sixtracklib/common/generated/config.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer/buffer_object.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
    #include "sixtracklib/common/buffer/managed_buffer_remap.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN void NS(Drift_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT drift, 
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Multipole_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp, 
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;
    
SIXTRL_STATIC SIXTRL_FN void NS(Cavity_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT cavity, 
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;
    
SIXTRL_STATIC SIXTRL_FN void NS(Track_single_particle_limit_global)(
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;
    
/* ************************************************************************* */

SIXTRL_STATIC SIXTRL_FN void NS(Track_single_particle_dispatcher)(
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p, 
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_obj,
    bool const perform_global_aperture_check ) SIXTRL_NOEXCEPT;
    
SIXTRL_STATIC SIXTRL_FN void NS(Track_single_particle_until_turn_impl)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer_begin,
    SIXTRL_INT64_T const pset_index, 
    SIXTRL_INT64_T const particle_index,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT elements_buffer_begin,
    SIXTRL_INT64_T const until_turn, 
    SIXTRL_UINT64_T const slot_size );
    
#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_INLINE void NS(DriftExact_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT drift, 
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    
    typedef SIXTRL_REAL_T real_t;
    real_t const one_plus_delta = p->delta + ( real_t )1;
    real_t const lpzi = drift->length / sqrt( one_plus_delta * one_plus_delta 
        - ( p->px * p->px + p->py * p->py ) );

    p->x += p->px * lpzi;
    p->y += p->py * lpzi;
    
    SIXTRL_ASSERT( p->beta0 >  ( real_t )0 );
    SIXTRL_ASSERT( p->beta0 <= ( real_t )1 );
    SIXTRL_ASSERT( ( one_plus_delta * one_plus_delta ) >   
                   ( p->px * p->px + p->py * p->py ) );
    
    SIXTRL_ASSERT( sqrt( one_plus_delta * one_plus_delta - 
        ( p->px * p->px + p->py * p->py ) ) > ( real_t )0 );

    p->s += drift->length;
    p->zeta += p->rvv * drift->length - one_plus_delta * lpzi;
}

SIXTRL_INLINE void NS(Multipole_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp, 
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
        
    typedef SIXTRL_REAL_T  real_t;
    typedef SIXTRL_INT64_T index_t;

    index_t index_x = 2 * NS(Multipole_order)( mp );
    index_t index_y = index_x + 1;
    
    real_t dpx = NS(Multipole_bal)( mp, index_x );
    real_t dpy = NS(Multipole_bal)( mp, index_y );

    real_t const hxl = NS(Multipole_hxl)( mp );
    real_t const hyl = NS(Multipole_hyl)( mp );

    SIXTRL_ASSERT( p->state == ( index_t )1 );
    SIXTRL_ASSERT( p  != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );

    while( index_x > 0 )
    {
        SIXTRL_ASSERT( index_x >= TWO );
        SIXTRL_ASSERT( index_y >= TWO );

        index_x -= 2;
        index_y -= 2;

        dpx = dpx * p->x - dpy * p->y + NS(Multipole_bal)( mp, index_x );
        dpy = dpx * p->y + dpy * p->x + NS(Multipole_bal)( mp, index_y );
    }

    dpx = -p->chi * dpx;
    dpy =  p->chi * dpy;

    if( ( mp->hxl > ( real_t )0 ) || ( mp->hyl > ( real_t )0 ) || 
        ( mp->hxl < ( real_t )0 ) || ( mp->hyl < ( real_t )0 ) )
    {
        real_t const hxlx = p->x * hxl;
        real_t const hyly = p->y * hyl;

        p->zeta += p->chi * ( hyly - hxlx );
        dpx += hxl + hxl * p->delta;
        dpy -= hyl + hyl * p->delta;

        if( mp->length > ( real_t )0 )
        {
            dpx -= p->chi * NS(Multipole_bal)( mp, 0 ) * hxlx / mp->length;
            dpy += p->chi * NS(Multipole_bal)( mp, 1 ) * hyly / mp->length;
        }
    }

    p->px += dpx;
    p->py += dpy;
}

SIXTRL_INLINE void NS(Cavity_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT cavity, 
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_REAL_T real_t;
    
    real_t const phase = 
        ( SIXTRL_PI / ( real_t )180 ) * NS(Cavity_lag)( cavity ) -
        ( ( ( real_t )2 * SIXTRL_PI ) / SIXTRL_C_LIGHT ) * 
        ( p->zeta / ( p->beta0 * p->rvv ) ) * NS(Cavity_frequency)( cavity );
           
    SIXTRL_ASSERT( p->state == 1 );
    NS(SingleParticle_add_to_energy)( p, p->q0 * p->charge_ratio * 
        sin( phase ) * NS(Cavity_voltage)( cavity ) );
}

SIXTRL_INLINE void NS(Track_single_particle_limit_global)(
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    
    typedef SIXTRL_REAL_T  real_t;
    typedef SIXTRL_INT64_T index_t;

    #if defined( SIXTRL_APERTURE_X_LIMIT )
    SIXTRL_STATIC_VAR real_t const X_LIMIT = ( real_t )SIXTRL_APERTURE_X_LIMIT;
    #else /* defined( SIXTRL_APERTURE_X_LIMIT )  */
    SIXTRL_STATIC_VAR real_t const X_LIMIT = ( real_t )1;
    #endif /* defined( SIXTRL_APERTURE_X_LIMIT ) */

    #if defined( SIXTRL_APERTURE_Y_LIMIT )
    SIXTRL_STATIC_VAR real_t const Y_LIMIT = ( real_t )SIXTRL_APERTURE_Y_LIMIT;
    #else /* defined( SIXTRL_APERTURE_Y_LIMIT ) */
    SIXTRL_STATIC_VAR real_t const Y_LIMIT = ( real_t )1;
    #endif /* defined( SIXTRL_APERTURE_Y_LIMIT ) */

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );

    real_t const sign_x = ( real_t )( ( ( real_t )0 < p->x ) - 
                          ( real_t )( p->x < ( real_t )0 ) );
    
    real_t const sign_y = ( real_t )( ( ( real_t )0 < p->y ) - 
                          ( real_t )( p->y < ( real_t )0 ) );

    p->state &= ( index_t )( ( ( sign_x * p->x ) < X_LIMIT ) &
                             ( ( sign_y * p->y ) < Y_LIMIT ) );
}

/* ************************************************************************** */

SIXTRL_STATIC SIXTRL_FN void NS(Track_single_particle_dispatcher)(
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p, 
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_obj,
    bool const perform_global_aperture_check ) SIXTRL_NOEXCEPT {
    
    typedef NS(buffer_addr_t) address_t;
    typedef NS(object_type_id_t) type_id_t;
    address_t const begin_addr = NS(Object_get_begin_addr)( be_obj );

    SIXTRL_ASSERT( begin_addr != ( address_t )0u );
    SIXTRL_ASSERT( pbuffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elements_buffer != SIXTRL_NULLPTR );
    
    switch( NS(Object_get_type_id)( be_obj ) )
    {
        case NS(OBJECT_TYPE_DRIFT_EXACT):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(DriftExact) const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;

            NS(DriftExact_track_single_particle)( belem, p );

            #if !defined( SIXTRL_APERTURE_CHECK_AT_DRIFT ) || \
                ( SIXTRL_APERTURE_CHECK_AT_DRIFT == \
                    SIXTRL_GLOBAL_APERTURE_CHECK_ALWAYS )

            if( perform_global_aperture_check )
            {
                NS(Track_single_particle_limit_global)( p );
            }

            #elif defined( SIXTRL_APERTURE_CHECK_AT_DRIFT ) && \
                    ( SIXTRL_APERTURE_CHECK_AT_DRIFT == \
                    SIXTRL_GLOBAL_APERTURE_CHECK_CONDITIONAL )

            if( perform_global_aperture_check )
            {
                #if defined( SIXTRL_APERTURE_CHECK_MIN_DRIFT_LENGTH )

                if( ( belem != SIXTRL_NULLPTR ) &&
                    ( NS(DriftExact_get_length)( belem ) >=
                        ( SIXTRL_REAL_T )SIXTRL_APERTURE_CHECK_AT_DRIFT ) )
                {
                    NS(Track_single_particle_limit_global)( p );
                }

                #else

                NS(Track_single_particle_limit_global)( p );

                #endif /* defined( SIXTRL_APERTURE_CHECK_MIN_DRIFT_LENGTH ) */
            }

            #endif

            break;
        }

        case NS(OBJECT_TYPE_MULTIPOLE):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(Multipole) const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;
            NS(Multipole_track_single_particle)( belem, p );
            break;
        } 
        
        case NS(OBJECT_TYPE_CAVITY):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(Cavity) const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;
            NS(Cavity_track_single_particle)( belem, p );
            break;
        }
    };
}

void NS(Track_single_particle_until_turn_impl)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer_begin,
    SIXTRL_INT64_T const pset_index, 
    SIXTRL_INT64_T const particle_index,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT elements_buffer_begin,
    SIXTRL_INT64_T const until_turn, 
    SIXTRL_UINT64_T const slot_size ) {
    
    typedef NS(particle_num_elements_t) nelements_t;
    typedef NS(particle_index_t) index_t;
    
    typedef SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* ptr_particles_t;
    typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const*  be_iter_t;

    SIXTRL_ARGPTR_DEC NS(SingleParticle) p;
    
    NS(SingleParticle_from_particle_set)( &p, 
        NS(Particles_managed_buffer_get_particles)( 
            pbuffer_begin, pset_index, slot_size ), particle_index );

    be_iter_t belem_begin = NS(ManagedBuffer_get_const_objects_index_begin)(
        elements_buffer_begin, slot_size );

    be_iter_t belem_end = NS(ManagedBuffer_get_const_objects_index_end)(
        elements_buffer_begin, slot_size );

    index_t const start_at_element = p.at_element_id;
    
    while( ( ( until_turn > p.at_turn ) && ( p.state == 1 ) ) )
    {
        index_t next_at_element_id = start_at_element;
        be_iter_t be_it = belem_begin;

        while( ( p.state == 1 ) && ( be_it != belem_end ) )
        {
            p.at_element_id = next_at_element_id++;
            NS(Track_single_particle_dispatcher)( &p, be_it++, true );
        }

        if( p.state == 1 )
        {
            SIXTRL_ASSERT( be_it == belem_end );
            p.at_element_id = start_at_element;
            ++p.at_turn;
            p.s = ( SIXTRL_REAL_T )0;
        }        
    }
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_EXAMPLES_CXX_BENCHMARK_TRACK_H__ */
