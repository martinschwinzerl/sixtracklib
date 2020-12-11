#ifndef SIXTRACKLIB_COMMON_INTERNAL_TYPE_RANDOM_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_TYPE_RANDOM_TRAITS_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstdint>
        #include <random>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< typename T, typename Enabled = void >
    struct TypeRandomTraits
    {
        typedef void default_prng_t;
        typedef void default_prng_seed_t;
        typedef void uniform_dist_t;
        typedef void normal_dist_t;

        static constexpr bool has_uniform_dist = false;
        static constexpr bool has_normal_dist  = false;
    };

} /* namespace: SIXTRL_CXX_NAMESPACE */

#if !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    /* -------------------------------------------------------------------- */
    /* Specialization for built-in types: */

    template< typename T >
    struct TypeRandomTraits< T, typename std::enable_if<
        std::is_same< double, T >::value ||
        std::is_same< long double, T >::value ||
        std::is_same< float, T >::value, void >::type >
    {
        typedef T value_type;
        typedef std::mt19937_64 default_prng_t;
        typedef std::mt19937_64::result_type default_prng_seed_t;
        typedef std::uniform_real_distribution< T > uniform_dist_t;
        typedef std::normal_distribution< T > normal_dist_t;

        static constexpr bool has_uniform_dist = true;
        static constexpr bool has_normal_dist  = true;
    };

    template< typename T >
    struct TypeRandomTraits< T, typename std::enable_if<
        std::is_same<   int8_t, T >::value ||
        std::is_same<  uint8_t, T >::value ||
        std::is_same<  int16_t, T >::value ||
        std::is_same< uint16_t, T >::value ||
        std::is_same<  int32_t, T >::value ||
        std::is_same< uint32_t, T >::value ||
        std::is_same<  int64_t, T >::value ||
        std::is_same< uint64_t, T >::value, void >::type >
    {
        typedef T value_type;
        typedef std::mt19937_64 default_prng_t;
        typedef std::mt19937_64::result_type default_prng_seed_t;
        typedef std::uniform_int_distribution< T > uniform_dist_t;
        typedef void normal_dist_t;

        static constexpr bool has_uniform_dist = true;
        static constexpr bool has_normal_dist  = false;
    };

} /* namespace: SIXTRL_CXX_NAMESPACE */
#endif /* !defined( _GPUCODE ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename T, typename Enabled >
    constexpr bool TypeRandomTraits< T, Enabled >::has_uniform_dist;

    template< typename T, typename Enabled >
    constexpr bool TypeRandomTraits< T, Enabled >::has_normal_dist;
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_INTERNAL_TYPE_RANDOM_TRAITS_CXX_HPP__ */
