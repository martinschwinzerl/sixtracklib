#ifndef SIXTRACKLIB_COMMON_INTERNAL_FILE_TOOLS_H__
#define SIXTRACKLIB_COMMON_INTERNAL_FILE_TOOLS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <string>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type) NS(File_num_bytes_or_minimum)(
    char const* SIXTRL_RESTRICT path_to_file,
    NS(size_type) const minimum_num_bytes );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type) NS(File_num_bytes)(
    char const* SIXTRL_RESTRICT path_to_file );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_CXX_NAMESPACE::size_type File_num_bytes(
        char const* SIXTRL_RESTRICT path_to_file,
        SIXTRL_CXX_NAMESPACE::size_type const min_num_bytes =
            SIXTRL_CXX_NAMESPACE::size_type{ 0 } );

    SIXTRL_CXX_NAMESPACE::size_type File_num_bytes(
        std::string const& SIXTRL_RESTRICT_REF path_to_file,
        SIXTRL_CXX_NAMESPACE::size_type const min_num_bytes =
            SIXTRL_CXX_NAMESPACE::size_type{ 0 } );

} /* ns: SIXTRL_CXX_NAMESPACE */

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_INTERNAL_FILE_TOOLS_H__ */
