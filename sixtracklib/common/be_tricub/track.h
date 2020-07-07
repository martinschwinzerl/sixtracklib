#ifndef SIXTRACKLIB_COMMON_BE_TRICUB_TRACK_C99_H__
#define SIXTRACKLIB_COMMON_BE_TRICUB_TRACK_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/particles.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(TriCub);

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(Track_particle_tricub)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    SIXTRL_BE_ARGPTR_DEC const struct NS(TriCub) *const SIXTRL_RESTRICT tricub );

SIXTRL_STATIC SIXTRL_FN void NS(tricub_construct_b_vector)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TriCubData) *const SIXTRL_RESTRICT tricub_data,
    NS(be_tricub_int_t) const ix, NS(be_tricub_int_t) const iy, NS(be_tricub_int_t) const iz, 
    SIXTRL_ARGPTR_DEC NS(be_tricub_real_t)* SIXTRL_RESTRICT b_vector);

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */
/* =====        Implementation of Inline functions and methods         ===== */
/* ========================================================================= */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <math.h>
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/constants.h"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/be_tricub/be_tricub.h"
    #include "sixtracklib/common/be_tricub/coefficients.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(track_status_t) NS(Track_particle_tricub)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    SIXTRL_BE_ARGPTR_DEC const struct NS(TriCub) *const SIXTRL_RESTRICT tricub )
{
    typedef NS(be_tricub_real_t) real_t;
    typedef NS(be_tricub_int_t)  int_t;

    SIXTRL_BUFFER_DATAPTR_DEC NS(TriCubData) const* tricub_data =
        NS(TriCub_const_data)( tricub );

    real_t const length = NS(TriCub_length)( tricub );
    
    real_t const x_shift = NS(TriCub_x_shift)( tricub );
    real_t const y_shift = NS(TriCub_y_shift)( tricub );
    real_t const z_shift = NS(TriCub_tau_shift)( tricub );

    // method = 1 -> Finite Differences for derivatives (Do not use)
    // method = 2 -> Exact derivatives
    // method = 3 -> Exact derivatives and mirrored in X, Y
                 
    real_t const inv_dx = 1./( NS(TriCubData_dx)( tricub_data ) );
    real_t const inv_dy = 1./( NS(TriCubData_dy)( tricub_data ) );
    real_t const inv_dz = 1./( NS(TriCubData_dz)( tricub_data ) );

    real_t const x0 = NS(TriCubData_x0)( tricub_data );
    real_t const y0 = NS(TriCubData_y0)( tricub_data );
    real_t const z0 = NS(TriCubData_z0)( tricub_data );

    real_t const zeta  = NS(Particles_get_zeta_value)( particles, ii );
    real_t const rvv   = NS(Particles_get_rvv_value)( particles, ii );
    real_t const beta0 = NS(Particles_get_beta0_value)( particles, ii );

    real_t const x = NS(Particles_get_x_value)( particles, ii );
    real_t const y = NS(Particles_get_y_value)( particles, ii );
    real_t const z = zeta / ( beta0 * rvv);

    real_t const fx = ( (x - x_shift) - x0 ) * inv_dx;
    real_t const fy = ( (y - y_shift) - y0 ) * inv_dy;
    real_t const fz = ( (z - z_shift) - z0 ) * inv_dz;

    real_t const sign_x = ( NS(TriCubData_mirror_x)( tricub_data ) == 1 && fx < 0.0 ) ? -1. : 1.;
    real_t const sign_y = ( NS(TriCubData_mirror_y)( tricub_data ) == 1 && fy < 0.0 ) ? -1. : 1.;
    real_t const sign_z = ( NS(TriCubData_mirror_z)( tricub_data ) == 1 && fz < 0.0 ) ? -1. : 1.;

    real_t const sfx = sign_x * fx;
    real_t const sfy = sign_y * fy;
    real_t const sfz = sign_z * fz;
                 
    real_t const ixf = floor(sfx);
    real_t const iyf = floor(sfy);
    real_t const izf = floor(sfz);

    int_t const ix = (int_t)ixf;
    int_t const iy = (int_t)iyf;
    int_t const iz = (int_t)izf;

    real_t const xn = sfx - ixf;
    real_t const yn = sfy - iyf;
    real_t const zn = sfz - izf;

    // const int_t inside_box = 
    //   ( ( ( ix < 0 || ix > NS(TriCubData_nx)( tricub_data ) - 2 )   ||
    //       ( iy < 0 || iy > NS(TriCubData_ny)( tricub_data ) - 2 ) ) ||
    //       ( iz < 0 || iz > NS(TriCubData_nz)( tricub_data ) - 2 ) ) ? 0 : 1;

    // SIXTRL_ASSERT( inside_box == 1 );
    // Check that coordinates are inside bounding box
    SIXTRL_ASSERT( ix >= 0 && ix <= NS(TriCubData_nx)( tricub_data ) - 2 );
    SIXTRL_ASSERT( iy >= 0 && iy <= NS(TriCubData_ny)( tricub_data ) - 2 ); 
    SIXTRL_ASSERT( iz >= 0 && iz <= NS(TriCubData_nz)( tricub_data ) - 2 );
    // =========================================================================
    
    real_t b_vector[64];
    NS(tricub_construct_b_vector)(tricub_data, ix, iy, iz, b_vector);

    real_t coefs[64];
    NS(tricub_construct_coefs)(b_vector, coefs);

    real_t x_power[4];
    real_t y_power[4];
    real_t z_power[4];
    
    x_power[0] = 1.;
    y_power[0] = 1.;
    z_power[0] = 1.;

    x_power[1] = xn;
    y_power[1] = yn;
    z_power[1] = zn;

    x_power[2] = xn * xn;
    y_power[2] = yn * yn;
    z_power[2] = zn * zn;

    x_power[3] = x_power[2] * xn;
    y_power[3] = y_power[2] * yn;
    z_power[3] = z_power[2] * zn;

    real_t kick_px = 0.;
    for( int i = 1; i < 4; i++ )
    {
        for( int j = 0; j < 4; j++ )
        {
            for( int k = 0; k < 4; k++ )
            {
                kick_px += i * ( ( ( coefs[i + 4 * j + 16 * k] * x_power[i-1] ) 
                            * y_power[j] ) * z_power[k] ) ;
            }
        }
    }
    kick_px *= ( length * inv_dx );
    kick_px *= -sign_x;
    kick_px -= NS(TriCub_dipolar_kick_px)( tricub );

    real_t kick_py = 0.;
    for( int i = 0; i < 4; i++ )
    {
        for( int j = 1; j < 4; j++ )
        {
            for( int k = 0; k < 4; k++ )
            {
                kick_py += j * ( ( ( coefs[i + 4 * j + 16 * k] * x_power[i] ) 
                            * y_power[j-1] ) * z_power[k] ) ;
            }
        }
    }
    kick_py *= ( length * inv_dy );
    kick_py *= -sign_y;
    kick_py -= NS(TriCub_dipolar_kick_py)( tricub );

    real_t kick_ptau = 0.;
    for( int i = 0; i < 4; i++ )
    {
        for( int j = 0; j < 4; j++ )
        {
            for( int k = 1; k < 4; k++ )
            {
                kick_ptau += k * ( ( ( coefs[i + 4 * j + 16 * k] * x_power[i] ) 
                            * y_power[j] ) * z_power[k-1] ) ;
            }
        }
    }
    kick_ptau *= ( length * inv_dz );
    kick_ptau *= -sign_z;
    kick_ptau -= NS(TriCub_dipolar_kick_ptau)( tricub );

    real_t const q = NS(Particles_get_q0_value)( particles, ii ) * 
                     NS(Particles_get_charge_ratio_value)( particles, ii );
    real_t const p0c = NS(Particles_get_p0c_value)( particles, ii );
    real_t const energy_kick = q * ( p0c * kick_ptau );

    NS(Particles_add_to_px_value)( particles, ii, kick_px );
    NS(Particles_add_to_py_value)( particles, ii, kick_py );
    NS(Particles_add_to_energy_value)( particles, ii, energy_kick );


    /* how to mark a particle in a particle set as lost */
    /*
    NS(Particles_mark_as_lost_value)( particles, ii );
    */

    ( void )particles;
    ( void )ii;
    //( void )lookup_table_begin;
    //( void )lookup_table_size;

    return SIXTRL_TRACK_SUCCESS;
}

SIXTRL_INLINE void NS(tricub_construct_b_vector)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TriCubData) *const SIXTRL_RESTRICT tricub_data,
    NS(be_tricub_int_t) const ix, NS(be_tricub_int_t) const iy, NS(be_tricub_int_t) const iz, 
    SIXTRL_ARGPTR_DEC NS(be_tricub_real_t)* SIXTRL_RESTRICT b_vector)
{

    SIXTRL_BUFFER_DATAPTR_DEC NS(be_tricub_real_t) const* lookup_table_begin =
        NS(TriCubData_const_table_begin)( tricub_data );

    //NS(be_tricub_int_t) const lookup_table_size = NS(TriCubData_table_size)( tricub_data );
    NS(be_tricub_int_t) const nx = NS(TriCubData_nx)( tricub_data );
    NS(be_tricub_int_t) const ny = NS(TriCubData_ny)( tricub_data );
    // NS(be_tricub_int_t) const nz = NS(TriCubData_nz)( tricub_data );

    // NS(be_tricub_real_t) const dx = NS(TriCubData_dx)( tricub_data );
    // NS(be_tricub_real_t) const dy = NS(TriCubData_dy)( tricub_data );
    // NS(be_tricub_real_t) const dz = NS(TriCubData_dz)( tricub_data );

    // NS(be_tricub_real_t) const scale[8] = { 1., dx, dy, dz, 
    //                                       dx * dy, dx * dz, dy * dz, 
    //                                       (dx * dy) * dz };
    //
    for(int l = 0; l < 8; l++)
    {
        b_vector[8 * l    ] = lookup_table_begin[ l + 8 * ( (ix  ) + nx * ( (iy  ) + ny * ( (iz  ) ) ) ) ];
        b_vector[8 * l + 1] = lookup_table_begin[ l + 8 * ( (ix+1) + nx * ( (iy  ) + ny * ( (iz  ) ) ) ) ];
        b_vector[8 * l + 2] = lookup_table_begin[ l + 8 * ( (ix  ) + nx * ( (iy+1) + ny * ( (iz  ) ) ) ) ];
        b_vector[8 * l + 3] = lookup_table_begin[ l + 8 * ( (ix+1) + nx * ( (iy+1) + ny * ( (iz  ) ) ) ) ];
        b_vector[8 * l + 4] = lookup_table_begin[ l + 8 * ( (ix  ) + nx * ( (iy  ) + ny * ( (iz+1) ) ) ) ];
        b_vector[8 * l + 5] = lookup_table_begin[ l + 8 * ( (ix+1) + nx * ( (iy  ) + ny * ( (iz+1) ) ) ) ];
        b_vector[8 * l + 6] = lookup_table_begin[ l + 8 * ( (ix  ) + nx * ( (iy+1) + ny * ( (iz+1) ) ) ) ];
        b_vector[8 * l + 7] = lookup_table_begin[ l + 8 * ( (ix+1) + nx * ( (iy+1) + ny * ( (iz+1) ) ) ) ];
        //b_vector[8 * l    ] = lookup_table_begin[ (ix  ) + nx * ( (iy  ) + ny * ( (iz  ) + nz * l) ) ] * scale[l];
        //b_vector[8 * l + 1] = lookup_table_begin[ (ix+1) + nx * ( (iy  ) + ny * ( (iz  ) + nz * l) ) ] * scale[l];
        //b_vector[8 * l + 2] = lookup_table_begin[ (ix  ) + nx * ( (iy+1) + ny * ( (iz  ) + nz * l) ) ] * scale[l];
        //b_vector[8 * l + 3] = lookup_table_begin[ (ix+1) + nx * ( (iy+1) + ny * ( (iz  ) + nz * l) ) ] * scale[l];
        //b_vector[8 * l + 4] = lookup_table_begin[ (ix  ) + nx * ( (iy  ) + ny * ( (iz+1) + nz * l) ) ] * scale[l];
        //b_vector[8 * l + 5] = lookup_table_begin[ (ix+1) + nx * ( (iy  ) + ny * ( (iz+1) + nz * l) ) ] * scale[l];
        //b_vector[8 * l + 6] = lookup_table_begin[ (ix  ) + nx * ( (iy+1) + ny * ( (iz+1) + nz * l) ) ] * scale[l];
        //b_vector[8 * l + 7] = lookup_table_begin[ (ix+1) + nx * ( (iy+1) + ny * ( (iz+1) + nz * l) ) ] * scale[l];
    }

    return;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BE_TRICUB_TRACK_C99_H__ */

/*end: sixtracklib/common/be_tricub/track.h */
