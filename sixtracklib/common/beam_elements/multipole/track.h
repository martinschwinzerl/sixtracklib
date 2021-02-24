#ifndef SIXTRACKL_COMMON_BEAM_ELEMENTS_MULTIPOLE_TRACK_C99_HEADER_H__
#define SIXTRACKL_COMMON_BEAM_ELEMENTS_MULTIPOLE_TRACK_C99_HEADER_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN void NS(Multipole_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )
SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Multipole_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;
#endif /* !defined( _GPUCODE ) */

/* ========================================================================= */
/* =====        Implementation of Inline functions and methods         ===== */
/* ========================================================================= */

SIXTRL_INLINE void NS(Multipole_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type)  real_type;
    typedef NS(particle_index_type) index_type;

    index_type index_y = 2 * NS(Multipole_order)( mp );
    index_type index_x = index_y++;

    real_type d_px = NS(Multipole_bal)( mp, index_x );
    real_type d_py = NS(Multipole_bal)( mp, index_y );

    real_type hxl = NS(Multipole_hxl)( mp );
    real_type hyl = NS(Multipole_hyl)( mp );

    while( index_x > 0 ) {
        real_type const z_re = d_px * NS(Particle_x)( p ) -
                               d_py * NS(Particle_y)( p );
        real_type const z_im = d_px * NS(Particle_y)( p ) +
                               d_py * NS(Particle_x)( p );
        index_x -= 2;
        index_y -= 2;
        d_px = NS(Multipole_bal)( mp, index_x ) + z_re;
        d_py = NS(Multipole_bal)( mp, index_y ) + z_im; }

    d_px *= -NS(Particle_chi)( p );
    d_py *=  NS(Particle_chi)( p );

    if( ( hxl > ( NS(be_real_type) )0. ) || ( hyl > ( NS(be_real_type) )0. ) ||
        ( hxl < ( NS(be_real_type) )0. ) || ( hyl < ( NS(be_real_type) )0. ) ) {

        real_type const length = NS(Multipole_length)( mp );
        d_px += hxl + hxl * NS(Particle_delta)( p );
        d_py -= hyl + hyl * NS(Particle_delta)( p );

        hxl *= NS(Particle_x)( p );
        hyl *= NS(Particle_y)( p );

        NS(Particle_add_to_zeta)( p, NS(Particle_chi)( p ) * ( hyl - hxl ) );

        if( length > ( NS(be_real_type) )0. ) {
            hxl  /= length;
            d_px -= NS(Particle_chi)( p ) * NS(Multipole_bal)( mp, 0 ) * hxl;
            hyl  /= length;
            d_py += NS(Particle_chi)( p ) * NS(Multipole_bal)( mp, 1 ) * hyl; } }

    NS(Particle_add_to_px)( p, d_px );
    NS(Particle_add_to_py)( p, d_py ); }

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKL_COMMON_BEAM_ELEMENTS_MULTIPOLE_TRACK_C99_HEADER_H__ */
