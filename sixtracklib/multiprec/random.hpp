#ifndef SIXTRACKLIB_MULTIPREC_RANDOM_CXX_HPP__
#define SIXTRACKLIB_MULTIPREC_RANDOM_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/multiprec/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <limits>
    #include <type_traits>

    #include <boost/multiprecision/cpp_bin_float.hpp>
    #include <boost/math/tools/precision.hpp>
    #include <boost/random.hpp>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/type_random_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class MpT >
    struct TypeRandomTraits< MpT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::MultiPrec_is_real_type< MpT >() &&
        SIXTRL_CXX_NAMESPACE::MultiPrec_real_impl_boost< MpT >(),
        void >::type >
    {
        typedef MpT value_type;
        typedef unsigned long default_prng_seed_t;

        typedef boost::random::independent_bits_engine<
            boost::random::mt19937, std::numeric_limits< value_type >::digits,
            boost::multiprecision::cpp_int > default_prng_t;

        typedef boost::random::uniform_real_distribution< MpT > uniform_dist_t;
        typedef boost::random::normal_distribution< MpT > normal_dist_t;

        static constexpr bool has_uniform_dist = true;
        static constexpr bool has_normal_dist  = true;
    };

    template< class MpT >
    constexpr bool TypeRandomTraits< MpT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::MultiPrec_is_real_type< MpT >() &&
        SIXTRL_CXX_NAMESPACE::MultiPrec_real_impl_boost< MpT >(),
        void >::type >::has_uniform_dist;

    template< class MpT >
    constexpr bool TypeRandomTraits< MpT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::MultiPrec_is_real_type< MpT >() &&
        SIXTRL_CXX_NAMESPACE::MultiPrec_real_impl_boost< MpT >(),
        void >::type >::has_normal_dist;
}

#endif /* C++, Host */
#endif /* SIXTRACKLIB_MULTIPREC_RANDOM_CXX_HPP__ */

