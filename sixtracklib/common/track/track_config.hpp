#ifndef SIXTRACKLIB_COMMON_TRACK_TRACK_CONFIG_CXX_HPP__
#define SIXTRACKLIB_COMMON_TRACK_TRACK_CONFIG_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstdint>
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/track/track_config.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE )

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_HOST_FN std::string TrackConfig_compiler_options(
        const ::NS(TrackConfig) *const SIXTRL_RESTRICT config,
        std::string const& SIXTRL_RESTRICT_REF option_prefix );

    SIXTRL_HOST_FN uint64_t TrackConfig_convert_double_to_uint64_bitmask(
        double x, double const multiplicator, uint64_t const num_bits,
        bool can_be_negative ) SIXTRL_NOEXCEPT;

    SIXTRL_HOST_FN double TrackConfig_convert_uint64_bitmask_to_double(
        uint64_t bitmask, uint64_t const num_bits,
        double const multiplicator, bool can_be_negative ) SIXTRL_NOEXCEPT;
}

#endif /* __cplusplus */
#endif /* !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_TRACK_TRACK_CONFIG_CXX_HPP__ */
