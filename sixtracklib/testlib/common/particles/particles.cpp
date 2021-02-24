#if !defined( SIXTRL_NO_INLCUDES )
    #include "sixtracklib/testlib/common/particles/particles.h"
    #include "sixtracklib/testlib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INLCUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <iostream>
    #include <iomanip>
    #include <sstream>
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE {
namespace testlib {

std::ostream& Particles_to_stream(
    std::ostream& SIXTRL_RESTRICT_REF ostr,
    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(Particles) const& SIXTRL_RESTRICT_REF pset,
    ::NS(particles_num_type) const index )
{
    if( ::NS(Particles_num_particles)( &pset ) > index )
    {
        ostr << "index        = " << std::setw( 24 ) << index << "\r\n";
        ostr << "x            = " << std::setw( 24 )
             << ::NS(Particles_x)( &pset, index )
             << "\r\npx           = " << std::setw( 24 )
             << ::NS(Particles_px)( &pset, index )
             << "\r\ny            = " << std::setw( 24 )
             << ::NS(Particles_y)( &pset, index )
             << "\r\npy           = " << std::setw( 24 )
             << ::NS(Particles_py)( &pset, index )
             << "\r\nzeta         = " << std::setw( 24 )
             << ::NS(Particles_zeta)( &pset, index )
             << "\r\ndelta        = " << std::setw( 24 )
             << ::NS(Particles_delta)( &pset, index )
             << "\r\nstate        = " << std::setw( 24 )
             << ::NS(Particles_state)( &pset, index )
             << "\r\nat_element   = " << std::setw( 24 )
             << ::NS(Particles_at_element)( &pset, index )
             << "\r\nat_turn      = " << std::setw( 24 )
             << ::NS(Particles_at_turn)( &pset, index )
             << "\r\nid           = " << std::setw( 24 )
             << ::NS(Particles_id)( &pset, index )
             << "\r\npsigma       = " << std::setw( 24 )
             << ::NS(Particles_psigma)( &pset, index )
             << "\r\nrpp          = " << std::setw( 24 )
             << ::NS(Particles_rpp)( &pset, index )
             << "\r\nrvv          = " << std::setw( 24 )
             << ::NS(Particles_rvv)( &pset, index )
             << "\r\nchi          = " << std::setw( 24 )
             << ::NS(Particles_chi)( &pset, index )
             << "\r\ncharge_ratio = " << std::setw( 24 )
             << ::NS(Particles_charge_ratio)( &pset, index )
             << "\r\ncharge0      = " << std::setw( 24 )
             << ::NS(Particles_charge0)( &pset, index )
             << "\r\nmass0        = " << std::setw( 24 )
             << ::NS(Particles_mass0)( &pset, index )
             << "\r\nbeta0        = " << std::setw( 24 )
             << ::NS(Particles_beta0)( &pset, index )
             << "\r\ngamma0       = " << std::setw( 24 )
             << ::NS(Particles_gamma0)( &pset, index )
             << "\r\np0c          = " << std::setw( 24 )
             << ::NS(Particles_p0c)( &pset, index )
             << "\r\ns            = " << std::setw( 24 )
             << ::NS(Particles_s)( &pset, index )
             << "\r\n";
    }

    return ostr;
}

std::ostream& Particles_diff_to_stream(
    std::ostream& SIXTRL_RESTRICT_REF ostr,
    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(Particles) const& SIXTRL_RESTRICT_REF lhs,
    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(Particles) const& SIXTRL_RESTRICT_REF rhs,
    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(Particles) const& SIXTRL_RESTRICT_REF diff,
    ::NS(particles_num_type) const index )
{
    if( ( &lhs != &rhs ) && ( &lhs != &diff ) && ( &diff != &rhs ) &&
        ( index >= ::NS(particles_num_type){ 0 } ) &&
        ( index < ::NS(Particles_num_particles)( &lhs  ) ) &&
        ( index < ::NS(Particles_num_particles)( &rhs  ) ) &&
        ( index < ::NS(Particles_num_particles)( &diff ) ) )
    {
        auto const saved_stream_precision = ostr.precision();
        ostr.precision( 16 );

        ostr    << std::setw( 24 ) << "index" << " = " << index << "\r\n"
                << std::setw( 24 ) << "field" << " | "
                << std::setw( 24 ) << "lhs" << " - "
                << std::setw( 24 ) << "rhs" << " = "
                << std::setw( 24 ) << "diff" << "\r\n"
                << std::setw( 24 ) << "x" << " | "
                << std::setw( 24 ) << ::NS(Particles_x)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_x)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_x)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "y" << " | "
                << std::setw( 24 ) << ::NS(Particles_y)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_y)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_y)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "px" << " | "
                << std::setw( 24 ) << ::NS(Particles_px)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_px)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_px)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "py" << " | "
                << std::setw( 24 ) << ::NS(Particles_py)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_py)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_py)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "zeta" << " | "
                << std::setw( 24 ) << ::NS(Particles_zeta)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_zeta)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_zeta)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "delta" << " | "
                << std::setw( 24 ) << ::NS(Particles_delta)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_delta)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_delta)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "state" << " | "
                << std::setw( 24 ) << ::NS(Particles_state)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_state)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_state)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "at_element" << " | "
                << std::setw( 24 ) << ::NS(Particles_at_element)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_at_element)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_at_element)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "at_turn" << " | "
                << std::setw( 24 ) << ::NS(Particles_at_turn)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_at_turn)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_at_turn)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "id" << " | "
                << std::setw( 24 ) << ::NS(Particles_id)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_id)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_id)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "psigma" << " | "
                << std::setw( 24 ) << ::NS(Particles_psigma)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_psigma)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_psigma)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "rpp" << " | "
                << std::setw( 24 ) << ::NS(Particles_rpp)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_rpp)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_rpp)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "rvv" << " | "
                << std::setw( 24 ) << ::NS(Particles_rvv)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_rvv)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_rvv)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "chi" << " | "
                << std::setw( 24 ) << ::NS(Particles_chi)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_chi)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_chi)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "charge_ratio" << " | "
                << std::setw( 24 ) << ::NS(Particles_charge_ratio)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_charge_ratio)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_charge_ratio)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "charge0" << " | "
                << std::setw( 24 ) << ::NS(Particles_charge0)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_charge0)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_charge0)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "mass0" << " | "
                << std::setw( 24 ) << ::NS(Particles_mass0)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_mass0)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_mass0)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "beta0" << " | "
                << std::setw( 24 ) << ::NS(Particles_beta0)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_beta0)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_beta0)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "gamma0" << " | "
                << std::setw( 24 ) << ::NS(Particles_gamma0)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_gamma0)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_gamma0)( &diff, index )
                << "\r\n"
                << std::setw( 24 ) << "p0c" << " | "
                << std::setw( 24 ) << ::NS(Particles_p0c)( &lhs, index )
                << std::setw( 27 ) << ::NS(Particles_p0c)( &rhs, index )
                << std::setw( 27 ) << ::NS(Particles_p0c)( &diff, index )
                << "\r\n";

        ostr.precision( saved_stream_precision );
    }

    return ostr;
}

} /* end: namespace testlib */
} /* end: namespace SIXTRL_CXX_NAMESPACE */


void NS(Particles_print)(
    SIXTRL_PARTICLES_ARGPTR_DEC const ::NS(Particles) *const SIXTRL_RESTRICT pset,
    ::NS(particles_num_type) const index ) {
    if( pset != nullptr )
    {
        SIXTRL_CXX_NAMESPACE::testlib::Particles_to_stream(
            std::cout, *pset, index );
    }
}

void NS(Particles_print_difference)(
    SIXTRL_PARTICLES_ARGPTR_DEC const ::NS(Particles) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const ::NS(Particles) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const ::NS(Particles) *const SIXTRL_RESTRICT diff,
    ::NS(particles_num_type) const index )
{
    if( ( lhs != nullptr ) && ( rhs != nullptr ) && ( diff != nullptr ) &&
        ( lhs != rhs ) && ( lhs != diff ) && ( rhs != diff ) &&
        ( index >= ::NS(particles_num_type){ 0 } ) &&
        ( index < ::NS(Particles_num_particles)( lhs ) ) &&
        ( index < ::NS(Particles_num_particles)( rhs ) ) &&
        ( index < ::NS(Particles_num_particles)( diff ) ) )
    {
        SIXTRL_CXX_NAMESPACE::testlib::Particles_diff_to_stream(
            std::cout, *lhs, *rhs, *diff, index );
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void NS(Particles_fprint)( ::FILE* SIXTRL_RESTRICT fp,
    SIXTRL_PARTICLES_ARGPTR_DEC const ::NS(Particles) *const SIXTRL_RESTRICT pset,
    ::NS(particles_num_type) const index ) {
    if( ( pset != nullptr ) && ( fp != nullptr ) )
    {
        std::ostringstream a2str;
        SIXTRL_CXX_NAMESPACE::testlib::Particles_to_stream( a2str, *pset, index );
        std::fprintf( fp, "%s", a2str.str().c_str() );
    }
}

void NS(Particles_fprint_difference)( ::FILE* SIXTRL_RESTRICT fp,
    SIXTRL_PARTICLES_ARGPTR_DEC const ::NS(Particles) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const ::NS(Particles) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const ::NS(Particles) *const SIXTRL_RESTRICT diff,
    ::NS(particles_num_type) const index )
{
    if( ( lhs != nullptr ) && ( rhs != nullptr ) && ( diff != nullptr ) &&
        ( lhs != rhs ) && ( lhs != diff ) && ( rhs != diff ) &&
        ( fp != nullptr )  && ( fp != nullptr ) &&
        ( index >= ::NS(particles_num_type){ 0 } ) &&
        ( index < ::NS(Particles_num_particles)( lhs ) ) &&
        ( index < ::NS(Particles_num_particles)( rhs ) ) &&
        ( index < ::NS(Particles_num_particles)( diff ) ) )
    {
        std::ostringstream a2str;
        SIXTRL_CXX_NAMESPACE::testlib::Particles_diff_to_stream(
            a2str, *lhs, *rhs, *diff, index );
        std::fprintf( fp, "%s", a2str.str().c_str() );
    }
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
