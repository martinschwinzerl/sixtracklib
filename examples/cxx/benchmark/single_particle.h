#ifndef SINGLE_PARTICLE_H__
#define SINGLE_PARTICLE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

typedef struct NS(SingleParticle)
{
    SIXTRL_REAL_T q0            SIXTRL_ALIGN( 8 ); /* C */
    SIXTRL_REAL_T mass0         SIXTRL_ALIGN( 8 ); /* eV */
    SIXTRL_REAL_T beta0         SIXTRL_ALIGN( 8 ); /* nounit */
    SIXTRL_REAL_T gamma0        SIXTRL_ALIGN( 8 ); /* nounit */
    SIXTRL_REAL_T p0c           SIXTRL_ALIGN( 8 ); /* eV */

    SIXTRL_REAL_T s             SIXTRL_ALIGN( 8 ); /* [m] */
    SIXTRL_REAL_T x             SIXTRL_ALIGN( 8 ); /* [m] */
    SIXTRL_REAL_T y             SIXTRL_ALIGN( 8 ); /* [m] */
    SIXTRL_REAL_T px            SIXTRL_ALIGN( 8 ); /* Px/P0 */
    SIXTRL_REAL_T py            SIXTRL_ALIGN( 8 ); /* Py/P0 */
    SIXTRL_REAL_T zeta          SIXTRL_ALIGN( 8 ); /* */

    SIXTRL_REAL_T psigma        SIXTRL_ALIGN( 8 ); /* (E-E0) / (beta0 P0c) conjugate of sigma */
    SIXTRL_REAL_T delta         SIXTRL_ALIGN( 8 ); /* P/P0-1 = 1/rpp-1 */
    SIXTRL_REAL_T rpp           SIXTRL_ALIGN( 8 ); /* ratio P0 /P */
    SIXTRL_REAL_T rvv           SIXTRL_ALIGN( 8 ); /* ratio beta / beta0 */
    SIXTRL_REAL_T chi           SIXTRL_ALIGN( 8 ); /* q/q0 * m/m0  */
    SIXTRL_REAL_T charge_ratio  SIXTRL_ALIGN( 8 ); /* ratio q/q0 */

    SIXTRL_INT64_T particle_id   SIXTRL_ALIGN( 8 );
    SIXTRL_INT64_T at_element_id SIXTRL_ALIGN( 8 );
    SIXTRL_INT64_T at_turn       SIXTRL_ALIGN( 8 );
    SIXTRL_INT64_T state         SIXTRL_ALIGN( 8 );
}
NS(SingleParticle);

SIXTRL_STATIC SIXTRL_FN void NS(SingleParticle_from_particle_set)(
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset, 
    SIXTRL_INT64_T const pindex ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(SingleParticle_to_particle_set)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT pset, 
    SIXTRL_INT64_T const pindex, 
    SIXTRL_ARGPTR_DEC const NS(SingleParticle) *const 
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;
    
#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */


#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
    
SIXTRL_INLINE void NS(SingleParticle_from_particle_set)(
    SIXTRL_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset, 
    SIXTRL_INT64_T const pindex ) SIXTRL_NOEXCEPT {
        
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( pindex < NS(Particles_get_num_of_particles)( pset ) );
    
    p->q0            = NS(Particles_get_q0_value)( pset, pindex );    
    p->mass0         = NS(Particles_get_mass0_value)( pset, pindex );
    p->beta0         = NS(Particles_get_beta0_value)( pset, pindex ); 
    p->gamma0        = NS(Particles_get_gamma0_value)( pset, pindex );
    p->p0c           = NS(Particles_get_p0c_value)( pset, pindex );   

    p->s             = NS(Particles_get_s_value)( pset, pindex );   
    p->x             = NS(Particles_get_x_value)( pset, pindex );   
    p->y             = NS(Particles_get_y_value)( pset, pindex );   
    p->px            = NS(Particles_get_px_value)( pset, pindex );  
    p->py            = NS(Particles_get_py_value)( pset, pindex );  
    p->zeta          = NS(Particles_get_zeta_value)( pset, pindex );

    p->psigma        = NS(Particles_get_psigma_value)( pset, pindex );      
    p->delta         = NS(Particles_get_delta_value)( pset, pindex );       
    p->rpp           = NS(Particles_get_rpp_value)( pset, pindex );        
    p->rvv           = NS(Particles_get_rvv_value)( pset, pindex );         
    p->chi           = NS(Particles_get_chi_value)( pset, pindex );         
    p->charge_ratio  = NS(Particles_get_charge_ratio_value)( pset, pindex );

    p->particle_id   = NS(Particles_get_particle_id_value)( pset, pindex );  
    p->at_element_id = NS(Particles_get_at_element_id_value)( pset, pindex );
    p->at_turn       = NS(Particles_get_at_turn_value)( pset, pindex );      
    p->state         = NS(Particles_get_state_value)( pset, pindex );        
}

SIXTRL_INLINE void NS(SingleParticle_to_particle_set)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT pset, 
    SIXTRL_INT64_T const pindex, 
    SIXTRL_ARGPTR_DEC const NS(SingleParticle) *const 
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( pindex < NS(Particles_get_num_of_particles)( pset ) );
    
    NS(Particles_set_q0_value)( pset, pindex, p->q0 );    
    NS(Particles_set_mass0_value)( pset, pindex, p->mass0 );
    NS(Particles_set_beta0_value)( pset, pindex, p->beta0 ); 
    NS(Particles_set_gamma0_value)( pset, pindex, p->gamma0 );
    NS(Particles_set_p0c_value)( pset, pindex, p->p0c );   

    NS(Particles_set_s_value)( pset, pindex, p->s );   
    NS(Particles_set_x_value)( pset, pindex, p->x );   
    NS(Particles_set_y_value)( pset, pindex, p->y );   
    NS(Particles_set_px_value)( pset, pindex, p->px );  
    NS(Particles_set_py_value)( pset, pindex, p->py );  
    NS(Particles_set_zeta_value)( pset, pindex, p->zeta );

    NS(Particles_set_psigma_value)( pset, pindex, p->psigma );      
    NS(Particles_set_delta_value)( pset, pindex, p->delta );       
    NS(Particles_set_rpp_value)( pset, pindex, p->rpp );        
    NS(Particles_set_rvv_value)( pset, pindex, p->rvv );         
    NS(Particles_set_chi_value)( pset, pindex, p->chi );         
    NS(Particles_set_charge_ratio_value)( pset, pindex, p->charge_ratio );

    NS(Particles_set_particle_id_value)( pset, pindex, p->particle_id );  
    NS(Particles_set_at_element_id_value)( pset, pindex, p->at_element_id );
    NS(Particles_set_at_turn_value)( pset, pindex, p->at_turn );      
    NS(Particles_set_state_value)( pset, pindex, p->state );
}
    
#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
    
#endif /* SINGLE_PARTICLE_H__ */
