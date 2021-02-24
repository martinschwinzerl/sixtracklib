#ifndef SIXTRACKLIB_COMMON_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/generated/namespace.h"
    #include "sixtracklib/common/internal/namespace_defines.h"
    #include "sixtracklib/common/backends/definitions.h"
    #include "sixtracklib/common/backends/compiler_compability.h"
    #include "sixtracklib/common/backends/helper_methods.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_STATUS_SUCCESS )
    #define SIXTRL_STATUS_SUCCESS 0u
#endif /* !defined( SIXTRL_STATUS_SUCCESS ) */

#if !defined( SIXTRL_STATUS_GENERAL_FAILURE )
    #define SIXTRL_STATUS_GENERAL_FAILURE 1u
#endif /* !defined( SIXTRL_STATUS_GENERAL_FAILURE ) */

typedef SIXTRL_INT32_TYPE  NS(status_type);
typedef SIXTRL_SIZE_TYPE   NS(size_type);
typedef SIXTRL_UINT64_TYPE NS(address_type);
typedef SIXTRL_INT64_TYPE  NS(address_diff_type);

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(status_type) const NS(STATUS_SUCCESS) =
    ( NS(status_type) )SIXTRL_STATUS_SUCCESS;

SIXTRL_STATIC_VAR NS(status_type) const NS(STATUS_GENERAL_FAILURE) =
    ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

SIXTRL_STATIC_VAR NS(size_type) const NS(DEFAULT_ALIGN) =
    ( NS(size_type) )SIXTRL_DEFAULT_ALIGN;

#else /* defined( _GPUCODE ) */

typedef enum NS(status_values_e)
{
    NS(STATUS_SUCCESS) = SIXTRL_STATUS_SUCCESS,
    NS(STATUS_GENERAL_FAILURE) = SIXTRL_STATUS_GENERAL_FAILURE
}
NS(status_values_type);

typedef enum NS(default_align_value_e)
{
    NS(DEFAULT_ALIGN) = SIXTRL_DEFAULT_ALIGN
}
NS(default_align_value_type);

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(status_type)       status_type;
    typedef ::NS(size_type)         size_type;
    typedef ::NS(address_type)      address_type;
    typedef ::NS(address_diff_type) address_diff_type;

    #if !defined( _GPUCODE )
    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST status_type STATUS_SUCCESS =
        static_cast< status_type >( SIXTRL_STATUS_SUCCESS );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST status_type
        STATUS_GENERAL_FAILURE = static_cast< status_type >(
            SIXTRL_STATUS_GENERAL_FAILURE );

    #endif /* defined( _GPUCODE ) */
} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_DEFINITIONS_H__ */
