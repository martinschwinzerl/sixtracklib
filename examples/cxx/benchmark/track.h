#ifndef SIXTRACKLIB_EXAMPLES_CXX_BENCHMARK_TRACK_H__
#define SIXTRACKLIB_EXAMPLES_CXX_BENCHMARK_TRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/constants.h"
    #include "benchmark/single_particle.h"
    #include "sixtracklib/common/be_drift/be_drift.h"
    #include "sixtracklib/common/be_multipole/be_multipole.h"
    #include "sixtracklib/common/be_cavity/be_cavity.h"
    #include "sixtracklib/common/be_srotation/be_srotation.h"
    #include "sixtracklib/common/be_xyshift/be_xyshift.h"
    #include "sixtracklib/common/be_limit/be_limit_rect.h"
    #include "sixtracklib/common/be_limit/be_limit_ellipse.h"
    #include "sixtracklib/common/be_limit/be_limit_rect_ellipse.h"
    #include "sixtracklib/common/be_dipedge/be_dipedge.h"
    #include "sixtracklib/common/be_beamfields/be_beamfields.h"
    #include "sixtracklib/common/generated/config.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/internal/physics_constants.h"
    #include "sixtracklib/common/buffer/buffer_object.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
    #include "sixtracklib/common/buffer/managed_buffer_remap.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN void NS(Drift_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT drift,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(DriftExact_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT drift,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Multipole_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Cavity_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT cavity,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(SRotation_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(XYShift_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(DipoleEdge_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(DipoleEdge) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(LimitRect_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(LimitEllipse_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(LimitRectEllipse_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(SCCoasting_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT elem,
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

SIXTRL_INLINE void NS(Drift_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT drift,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_REAL_T real_t;
    real_t const xp = p->px * p->rpp;
    real_t const yp = p->py * p->rpp;

    SIXTRL_ASSERT( p->beta0 >  ( real_t )0. );
    SIXTRL_ASSERT( p->beta0 <= ( real_t )1. );

    p->x    += drift->length * xp;
    p->y    += drift->length * yp;
    p->zeta += drift->length * ( p->rvv - ( real_t )1.0 +
        ( real_t )0.5 * ( xp * xp + yp * yp ) );
}

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

    if( ( mp->hxl > ( real_t )0. ) || ( mp->hyl > ( real_t )0. ) ||
        ( mp->hxl < ( real_t )0. ) || ( mp->hyl < ( real_t )0. ) )
    {
        real_t const hxlx = p->x * mp->hxl;
        real_t const hyly = p->y * mp->hyl;

        p->zeta += p->chi * ( hyly - hxlx );
        dpx += mp->hxl + mp->hxl * p->delta;
        dpy -= mp->hyl + mp->hyl * p->delta;

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

SIXTRL_INLINE void NS(SRotation_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_REAL_T real_t;
    real_t const y_hat  = p->y  * elem->cos_z - p->x  * elem->sin_z;
    real_t const py_hat = p->py * elem->cos_z - p->px * elem->sin_z;

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );

    p->x  = p->x  * elem->cos_z + p->y  * elem->sin_z;
    p->y  = y_hat;

    p->px = p->px * elem->cos_z + p->py * elem->sin_z;
    p->py = py_hat;
}

SIXTRL_INLINE void NS(XYShift_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    p->x -= elem->dx;
    p->y -= elem->dy;
}

SIXTRL_INLINE void NS(DipoleEdge_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(DipoleEdge) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    p->px += p->x * elem->r21;
    p->py += p->y * elem->r43;
}

SIXTRL_INLINE void NS(LimitRect_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_UINT64_T ustate_t;
    ustate_t new_state = ( ( p != SIXTRL_NULLPTR ) && ( p->state == 1 ) )
        ? ( ustate_t )1 : ( ustate_t )0;
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );

    new_state &= ( ustate_t )(
        ( p->x >= elem->min_x ) && ( p->x <= elem->max_x ) &&
        ( p->y >= elem->min_y ) && ( p->y <= elem->max_y ) );

    p->state = ( NS(particle_index_t) )new_state;
}

SIXTRL_INLINE void NS(LimitEllipse_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_UINT64_T ustate_t;
    ustate_t new_state = ( ( p != SIXTRL_NULLPTR ) && ( p->state == 1 ) )
        ? ( ustate_t )1 : ( ustate_t )0;
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    new_state &= ( ustate_t )( elem->a_b_squ >=
        ( elem->b_squ * p->x * p->x + elem->a_squ * p->y * p->y ) );
    p->state = ( NS(particle_index_t) )new_state;
}

SIXTRL_INLINE void NS(LimitRectEllipse_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_UINT64_T ustate_t;
    ustate_t new_state = ( ( p != SIXTRL_NULLPTR ) && ( p->state == 1 ) )
        ? ( ustate_t )1 : ( ustate_t )0;
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    new_state &= ( ustate_t )(
        ( p->x <= elem->max_x ) && ( p->x >= -elem->max_x ) &&
        ( p->y <= elem->max_y ) && ( p->y >= -elem->max_y ) &&
        ( elem->a_squ_b_squ >= ( elem->b_squ * p->x * p->x +
                                 elem->a_squ * p->y * p->y ) ) );
    p->state = ( NS(particle_index_t) )new_state; }

SIXTRL_INLINE void NS(SCCoasting_track_single_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT elem,
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_REAL_T real_t;
    SIXTRL_ARGPTR_DEC real_t Ex;
    SIXTRL_ARGPTR_DEC real_t Ey;
    SIXTRL_ARGPTR_DEC real_t Gx;
    SIXTRL_ARGPTR_DEC real_t Gy;

    real_t fact_kick = elem->number_of_particles * elem->length * p->chi *
        p->charge_ratio * p->charge0 * p->charge0 * NS(PhysConst_charge0_si)() *
            NS(PhysConst_charge0_si)() * ( ( real_t )1. - p->beta0 * p->beta0 );

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elem->circumference > ( real_t )0. );
    SIXTRL_ASSERT( p->beta0 > ( real_t )0. );
    SIXTRL_ASSERT( p->beta0 < ( real_t )1. );

    fact_kick /= elem->circumference * NS(PhysConst_charge0_si)() *
        p->p0c * p->beta0 * p->rvv;

    NS(get_Ex_Ey_Gx_Gy_gauss)( p->x - elem->x_co, p->y - elem->y_co,
        elem->sigma_x, elem->sigma_y, elem->min_sigma_diff, ( int )1,
            &Ex, &Ey, &Gx, &Gy );

    p->px += fact_kick * Ex;
    p->py += fact_kick * Ey;
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
        case NS(OBJECT_TYPE_DRIFT):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(Drift) const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;
            NS(Drift_track_single_particle)( belem, p );
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
                    ( NS(Drift_get_length)( belem ) >=
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

        case NS(OBJECT_TYPE_SROTATION):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(SRotation) const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;
            NS(SRotation_track_single_particle)( belem, p );
            break;
        }

        case NS(OBJECT_TYPE_XYSHIFT):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(XYShift) const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;
            NS(XYShift_track_single_particle)( belem, p );
            break;
        }

        case NS(OBJECT_TYPE_LIMIT_RECT):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(LimitRect) const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;
            NS(LimitRect_track_single_particle)( belem, p );
            break;
        }

        case NS(OBJECT_TYPE_LIMIT_ELLIPSE):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(LimitEllipse) const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;
            NS(LimitEllipse_track_single_particle)( belem, p );
            break;
        }

        case NS(OBJECT_TYPE_LIMIT_RECT_ELLIPSE):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse) const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;
            NS(LimitRectEllipse_track_single_particle)( belem, p );
            break;
        }

        case NS(OBJECT_TYPE_LIMIT_DIPEDGE):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(DipoleEdge) const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;
            NS(DipoleEdge_track_single_particle)( belem, p );
            break;
        }

        #if defined( SIXTRL_TRACK_SPACECHARGE ) && ( SIXTRL_TRACK_SPACECHARGE == 2 )
        case NS(OBJECT_TYPE_SC_COASTING):
        {
            typedef SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;
            NS(SCCoasting_track_single_particle)( belem, p );
            break;
        }
        #endif /* defined( SIXTRL_TRACK_SPACECHARGE ) && ( SIXTRL_TRACK_SPACECHARGE == 2 ) */

        default:
        {
            p->state = 0;
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

    NS(SingleParticle_to_particle_set)(
        NS(Particles_managed_buffer_get_particles)(
            pbuffer_begin, pset_index, slot_size ), particle_index, &p );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_EXAMPLES_CXX_BENCHMARK_TRACK_H__ */
