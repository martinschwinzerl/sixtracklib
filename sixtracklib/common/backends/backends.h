#ifndef SIXTRACKLIB_COMMON_BACKENDS_BACKENDS_H__
#define SIXTRACKLIB_COMMON_BACKENDS_BACKENDS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/backends/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <string>
    #include <ostream>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && !defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && !defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Backends_is_enabled_by_string)(
    char const* SIXTRL_RESTRICT backend_str ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Backends_is_enabled)(
    NS(backend_id_type) const id ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(Backends_string_by_id)(
    char* SIXTRL_RESTRICT backend_str, NS(size_type) const backend_str_capacity
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(backend_id_type) NS(Backends_id_by_string)(
    char const* SIXTRL_RESTRICT backend_str ) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    bool Backends_is_enabled(
        SIXTRL_CXX_NAMESPACE::backend_id_type const id ) SIXTRL_NOEXCEPT;

    bool Backends_is_enabled(
        std::string const& SIXTRL_RESTRICT_REF backend_str );

    std::ostream& Backends_string_to_stream( std::ostream& ostr,
        SIXTRL_CXX_NAMESPACE::backend_id_type const id );

    std::string Backends_string_by_id(
        SIXTRL_CXX_NAMESPACE::backend_id_type const id );

    SIXTRL_CXX_NAMESPACE::backend_id_type Backends_id_by_string(
        std::string const& SIXTRL_RESTRICT_REF backend_str ) SIXTRL_NOEXCEPT;

    std::string Backends_backend_id_regex( bool const only_enabled = false );
    std::string Backends_backend_str_regex( bool const only_enabled = false );
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BACKENDS_BACKENDS_H__ */
