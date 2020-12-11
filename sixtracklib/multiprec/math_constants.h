#ifndef SIXTRACKLIB_MULTIPREC_MATH_CONSTANTS_CXX_HPP__
#define SIXTRACKLIB_MULTIPREC_MATH_CONSTANTS_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/multiprec/definitions.h"
    #include "sixtracklib/common/internal/math_constants.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <limits>
    #include <type_traits>

    #include <boost/math/constants/constants.hpp>
    #include <boost/multiprecision/cpp_bin_float.hpp>
    #include <boost/math/tools/precision.hpp>
    #include <boost/random.hpp>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< unsigned N, boost::multiprecision::backends::digit_base_type base,
        class Alloc, class E, E ExpMin, E ExpMax, multiprec_et_option_t et >
    struct MathConstHelper<
        MultiPrecReal< N, base, Alloc, E, ExpMin, ExpMax, et >, void >
    {
        using real_t = MultiPrecReal< N, base, Alloc, E, ExpMin, ExpMax, et >;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN real_t get_pi()
        {
            using boost::math::constants::pi;
            return pi< real_t >();
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN real_t get_deg2rad()
        {
            using boost::math::constants::pi;
            return pi< real_t >() / real_t{ 180 };
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN real_t get_rad2deg()
        {
            using boost::math::constants::pi;
            return real_t{ 180 } / pi< real_t >();
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN real_t get_sqrt_pi()
        {
            using boost::math::constants::pi;
            using std::sqrt;
            return sqrt( pi< real_t >() );
        }
    };
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_MULTIPREC_MATH_CONSTANTS_CXX_HPP__ */
