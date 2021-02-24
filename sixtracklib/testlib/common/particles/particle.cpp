#if !defined( SIXTRL_NO_INLCUDES )
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

std::ostream& Particle_to_stream(
    std::ostream& SIXTRL_RESTRICT_REF ostr,
    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle) const& SIXTRL_RESTRICT_REF p )
{
    auto const saved_stream_precision = ostr.precision();
    ostr.precision( 16 );
    ostr << "x            = " << std::setw( 24 ) << ::NS(Particle_x)( &p )
         << "\r\npx           = " << std::setw( 24 ) << ::NS(Particle_px)( &p )
         << "\r\ny            = " << std::setw( 24 ) << ::NS(Particle_y)( &p )
         << "\r\npy           = " << std::setw( 24 ) << ::NS(Particle_py)( &p )
         << "\r\nzeta         = " << std::setw( 24 ) << ::NS(Particle_zeta)( &p )
         << "\r\ndelta        = " << std::setw( 24 )
         << ::NS(Particle_delta)( &p )
         << "\r\nstate        = " << std::setw( 24 )
         << ::NS(Particle_state)( &p )
         << "\r\nat_element   = " << std::setw( 24 )
         << ::NS(Particle_at_element)( &p )
         << "\r\nat_turn      = " << std::setw( 24 )
         << ::NS(Particle_at_turn)( &p )
         << "\r\nid           = " << std::setw( 24 ) << ::NS(Particle_id)( &p )
         << "\r\npsigma       = " << std::setw( 24 )
         << ::NS(Particle_psigma)( &p )
         << "\r\nrpp          = " << std::setw( 24 ) << ::NS(Particle_rpp)( &p )
         << "\r\nrvv          = " << std::setw( 24 ) << ::NS(Particle_rvv)( &p )
         << "\r\nchi          = " << std::setw( 24 ) << ::NS(Particle_chi)( &p )
         << "\r\ncharge_ratio = " << std::setw( 24 )
         << ::NS(Particle_charge_ratio)( &p )
         << "\r\ncharge0      = " << std::setw( 24 )
         << ::NS(Particle_charge0)( &p )
         << "\r\nmass0        = " << std::setw( 24 )
         << ::NS(Particle_mass0)( &p )
         << "\r\nbeta0        = " << std::setw( 24 )
         << ::NS(Particle_beta0)( &p )
         << "\r\ngamma0       = " << std::setw( 24 )
         << ::NS(Particle_gamma0)( &p )
         << "\r\np0c          = " << std::setw( 24 ) << ::NS(Particle_p0c)( &p )
         << "\r\ns            = " << std::setw( 24 ) << ::NS(Particle_s)( &p )
         << "\r\n";

    ostr.precision( saved_stream_precision );
    return ostr;
}

std::ostream& Particle_diff_to_stream(
    std::ostream& SIXTRL_RESTRICT_REF ostr,
    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle) const& SIXTRL_RESTRICT_REF lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle) const& SIXTRL_RESTRICT_REF rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle) const& SIXTRL_RESTRICT_REF diff )
{
    auto const saved_stream_precision = ostr.precision();
    ostr.precision( 16 );

    ostr    << std::setw( 20 ) << "field" << " | "
            << std::setw( 20 ) << "lhs" << " - "
            << std::setw( 20 ) << "rhs" << " = "
            << std::setw( 20 ) << "diff" << "\r\n"
            << std::setw( 20 ) << "x" << " | "
            << std::setw( 20 ) << lhs.x
            << std::setw( 23 ) << rhs.x
            << std::setw( 23 ) << diff.x
            << "\r\n"
            << std::setw( 20 ) << "y" << " | "
            << std::setw( 20 ) << lhs.y
            << std::setw( 23 ) << rhs.y
            << std::setw( 23 ) << diff.y
            << "\r\n"
            << std::setw( 20 ) << "px" << " | "
            << std::setw( 20 ) << lhs.px
            << std::setw( 23 ) << rhs.px
            << std::setw( 23 ) << diff.px
            << "\r\n"
            << std::setw( 20 ) << "py" << " | "
            << std::setw( 20 ) << lhs.py
            << std::setw( 23 ) << rhs.py
            << std::setw( 23 ) << diff.py
            << "\r\n"
            << std::setw( 20 ) << "zeta" << " | "
            << std::setw( 20 ) << lhs.zeta
            << std::setw( 23 ) << rhs.zeta
            << std::setw( 23 ) << diff.zeta
            << "\r\n"
            << std::setw( 20 ) << "delta" << " | "
            << std::setw( 20 ) << lhs.delta
            << std::setw( 23 ) << rhs.delta
            << std::setw( 23 ) << diff.delta
            << "\r\n"
            << std::setw( 20 ) << "state" << " | "
            << std::setw( 20 ) << lhs.state
            << std::setw( 23 ) << rhs.state
            << std::setw( 23 ) << diff.state
            << "\r\n"
            << std::setw( 20 ) << "at_element" << " | "
            << std::setw( 20 ) << lhs.at_element
            << std::setw( 23 ) << rhs.at_element
            << std::setw( 23 ) << diff.at_element
            << "\r\n"
            << std::setw( 20 ) << "at_turn" << " | "
            << std::setw( 20 ) << lhs.at_turn
            << std::setw( 23 ) << rhs.at_turn
            << std::setw( 23 ) << diff.at_turn
            << "\r\n"
            << std::setw( 20 ) << "id" << " | "
            << std::setw( 20 ) << lhs.id
            << std::setw( 23 ) << rhs.id
            << std::setw( 23 ) << diff.id
            << "\r\n"
            << std::setw( 20 ) << "psigma" << " | "
            << std::setw( 20 ) << lhs.psigma
            << std::setw( 23 ) << rhs.psigma
            << std::setw( 23 ) << diff.psigma
            << "\r\n"
            << std::setw( 20 ) << "rpp" << " | "
            << std::setw( 20 ) << lhs.rpp
            << std::setw( 23 ) << rhs.rpp
            << std::setw( 23 ) << diff.rpp
            << "\r\n"
            << std::setw( 20 ) << "rvv" << " | "
            << std::setw( 20 ) << lhs.rvv
            << std::setw( 23 ) << rhs.rvv
            << std::setw( 23 ) << diff.rvv
            << "\r\n"
            << std::setw( 20 ) << "chi" << " | "
            << std::setw( 20 ) << lhs.chi
            << std::setw( 23 ) << rhs.chi
            << std::setw( 23 ) << diff.chi
            << "\r\n"
            << std::setw( 20 ) << "charge_ratio" << " | "
            << std::setw( 20 ) << lhs.charge_ratio
            << std::setw( 23 ) << rhs.charge_ratio
            << std::setw( 23 ) << diff.charge_ratio
            << "\r\n"
            << std::setw( 20 ) << "charge0" << " | "
            << std::setw( 20 ) << lhs.charge0
            << std::setw( 23 ) << rhs.charge0
            << std::setw( 23 ) << diff.charge0
            << "\r\n"
            << std::setw( 20 ) << "mass0" << " | "
            << std::setw( 20 ) << lhs.mass0
            << std::setw( 23 ) << rhs.mass0
            << std::setw( 23 ) << diff.mass0
            << "\r\n"
            << std::setw( 20 ) << "beta0" << " | "
            << std::setw( 20 ) << lhs.beta0
            << std::setw( 23 ) << rhs.beta0
            << std::setw( 23 ) << diff.beta0
            << "\r\n"
            << std::setw( 20 ) << "gamma0" << " | "
            << std::setw( 20 ) << lhs.gamma0
            << std::setw( 23 ) << rhs.gamma0
            << std::setw( 23 ) << diff.gamma0
            << "\r\n"
            << std::setw( 20 ) << "p0c" << " | "
            << std::setw( 20 ) << lhs.p0c
            << std::setw( 23 ) << rhs.p0c
            << std::setw( 23 ) << diff.p0c << "\r\n";

    ostr.precision( saved_stream_precision );
    return ostr;
}

} /* end: namespace testlib */
} /* end: namespace SIXTRL_CXX_NAMESPACE */


void NS(Particle_print)( SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(Particle)
    *const SIXTRL_RESTRICT p ) {
    if( p != nullptr )
    {
        SIXTRL_CXX_NAMESPACE::testlib::Particle_to_stream( std::cout, *p );
    }
}

void NS(Particle_print_difference)(
    SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(Particle) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(Particle) *const SIXTRL_RESTRICT diff )
{
    if( ( lhs != nullptr ) && ( rhs != nullptr ) && ( diff != nullptr ) &&
        ( lhs != rhs ) && ( lhs != diff ) && ( rhs != diff ) )
    {
        SIXTRL_CXX_NAMESPACE::testlib::Particle_diff_to_stream(
            std::cout, *lhs, *rhs, *diff );
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void NS(Particle_fprint)( ::FILE* SIXTRL_RESTRICT fp,
    SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(Particle) *const SIXTRL_RESTRICT p ) {
    if( ( p != nullptr ) && ( fp != nullptr ) )
    {
        std::ostringstream a2str;
        SIXTRL_CXX_NAMESPACE::testlib::Particle_to_stream( a2str, *p );
        std::fprintf( fp, "%s", a2str.str().c_str() );
    }
}

void NS(Particle_fprint_difference)( ::FILE* SIXTRL_RESTRICT fp,
    SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(Particle) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(Particle) *const SIXTRL_RESTRICT diff )
{
    if( ( lhs != nullptr ) && ( rhs != nullptr ) && ( diff != nullptr ) &&
        ( lhs != rhs ) && ( lhs != diff ) && ( rhs != diff ) &&
        ( fp != nullptr ) )
    {
        std::ostringstream a2str;
        SIXTRL_CXX_NAMESPACE::testlib::Particle_diff_to_stream(
            a2str, *lhs, *rhs, *diff );
        std::fprintf( fp, "%s", a2str.str().c_str() );
    }
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
