#ifndef SIXTRACKLIB_COMMON_INTERNAL_MATH_CONSTANT_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_MATH_CONSTANT_TRAITS_CXX_HPP__

#include "sixtracklib/common/definitions.h"

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename T >
    struct MathConstants
    {
        typedef T real_t;

        static SIXTRL_FN real_t constexpr Zero() SIXTRL_NOEXCEPT
        {
            return static_cast< real_t >( 0 );
        }

        static SIXTRL_FN real_t constexpr One() SIXTRL_NOEXCEPT
        {
            return static_cast< real_t >( 1 );
        }

        static SIXTRL_FN real_t constexpr Two() SIXTRL_NOEXCEPT
        {
            return static_cast< real_t >( 2 );
        }

        static SIXTRL_FN real_t constexpr OneHalf() SIXTRL_NOEXCEPT
        {
            return static_cast< real_t >( 0.5 );
        }

        static SIXTRL_FN real_t constexpr Pi() SIXTRL_NOEXCEPT
        {
            return static_cast< real_t >(
                3.1415926535897932384626433832795028841971693993751 );
        }

        static SIXTRL_FN real_t constexpr SqrtPi() SIXTRL_NOEXCEPT
        {
            return static_cast< real_t >(
                1.7724538509055160272981674833411451827975494561224 );
        }

        static SIXTRL_FN real_t constexpr Deg2Rad() SIXTRL_NOEXCEPT
        {
            return static_cast< real_t >(
                0.0174532925199432957692369076848861271344287188854 );
        }

        static SIXTRL_FN real_t constexpr Rad2Deg() SIXTRL_NOEXCEPT
        {
            return static_cast< real_t >(
                57.29577951308232087679815481410517033240547246656442 );
        }
    };
}

#endif /* SIXTRACKLIB_COMMON_INTERNAL_MATH_CONSTANT_TRAITS_CXX_HPP__ */
/* end: */
