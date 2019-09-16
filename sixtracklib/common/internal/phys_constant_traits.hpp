#ifndef SIXTRACKLIB_COMMON_INTERNAL_PHYS_CONSTANT_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_PHYS_CONSTANT_TRAITS_CXX_HPP__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/math_constant_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename T > struct PhysConstants
    {
        typedef T real_t;

        /* Source: https://physics.nist.gov/cuu/Constants/index.html
         *         If not noted otherwise, these values correspond to the
         *         CODATA 2018 recommended values */

        static SIXTRL_FN real_t constexpr C0() SIXTRL_NOEXCEPT
        {
            return static_cast< real_t >( 299792458.0 );
        }

        static SIXTRL_FN real_t constexpr Mu0() SIXTRL_NOEXCEPT
        {
            /* Check whether using 4*pi*1e-7 would be better here */
            return static_cast< real_t >( 1.25663706212e-6 );
        }

        static SIXTRL_FN real_t constexpr Epsilon0() SIXTRL_NOEXCEPT
        {
            /* Check whether using 1 / ( c0*c0*mu0) would be better here */
            return static_cast< real_t >( 8.8541878128e-12 );
        }

        static SIXTRL_FN real_t constexpr Q0() SIXTRL_NOEXCEPT
        {
            return static_cast< real_t >( 1.602176634e-19 );
        }
    };
}

#endif /* SIXTRACKLIB_COMMON_INTERNAL_PHYS_CONSTANT_TRAITS_CXX_HPP__ */
/* end: */
