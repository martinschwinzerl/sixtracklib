#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/file_tools.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( _BSD_SOURCE ) || ( _XOPEN_SOURCE >= 500 ) || \
               ( _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED ) || \
               ( _POSIX_C_SOURCE >= 200112L )
        #include <sys/types.h>
        #include <sys/stat.h>
        #include <unistd.h>
    #elif defined( WIN32     ) || defined( _WIN32 ) || \
          defined( __WIN32__ ) || defined( __NT__ )
        #include <syst/types.h>
        #include <sys/stat.h>
    #else
        #include <cstdio>
        #include <cstring>
    #endif /* stat64 on *nix */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( _BSD_SOURCE ) || ( _XOPEN_SOURCE >= 500 ) || \
           ( _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED ) || \
           ( _POSIX_C_SOURCE >= 200112L )

::NS(size_type) NS(File_num_bytes_or_minimum)(
    char const* SIXTRL_RESTRICT path_to_file,
    ::NS(size_type) const min_num_bytes ) {
    ::NS(size_type) num_bytes = ::NS(size_type){ 0 };
    struct ::stat64 fs;
    if( ::stat64( path_to_file, &fs ) == 0 )
    {
        num_bytes = static_cast< ::NS(size_type) >( fs.st_size );
        if( num_bytes < min_num_bytes ) num_bytes = min_num_bytes;
    }

    return num_bytes;
}

#elif defined( WIN32 )     || defined( _WIN32 ) || \
      defined( __WIN32__ ) || defined( __NT__ )

::NS(size_type) NS(File_num_bytes_or_minimum)(
    char const* SIXTRL_RESTRICT path_to_file,
    ::NS(size_type) const min_num_bytes ) {
    ::NS(size_type) num_bytes = ::NS(size_type){ 0 };
    struct ::_stati64 fs;
    if( ::_stati64( path_to_file, &fs ) == 0 )
    {
        num_bytes = static_cast< ::NS(size_type) >( fs.st_size );
        if( num_bytes < min_num_bytes ) num_bytes = min_num_bytes;
    }
    return num_bytes;
}

#else /* fallback implementation */

::NS(size_type) NS(File_num_bytes_or_minimum)(
    char const* SIXTRL_RESTRICT path_to_file,
    ::NS(size_type) const min_num_bytes ) {
    ::NS(size_type) num_bytes = ::NS(size_type){ 0 };
    ::FILE* fp = std::fopen( path_to_file, "rb" );
    if( fp != nullptr )
    {
        std::fseek( fp, 0, SEEK_END );
        auto sz_end = std::ftell( fp );
        std::fseek( fp, 0, SEEK_SET );
        auto sz_begin = std::ftell( fp );
        std::fclose( fp );
        fp = nullptr;

        num_bytes = static_cast< ::NS(size_type) >( sz_end - sz_begin );
        if( num_bytes < min_num_bytes ) num_bytes = min_num_bytes;
    }
    return num_bytes;
}

#endif /* stat64 on *nix */

::NS(size_type) NS(File_num_bytes)( char const* SIXTRL_RESTRICT path_to_file ) {
    return NS(File_num_bytes_or_minimum)( path_to_file, 0u ); }

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace { namespace st = SIXTRL_CXX_NAMESPACE; }

    st::size_type File_num_bytes(
        char const* SIXTRL_RESTRICT path_to_file,
        st::size_type const min_num_bytes ) {
        return ::NS(File_num_bytes_or_minimum)( path_to_file, min_num_bytes ); }

    st::size_type File_num_bytes(
        std::string const& SIXTRL_RESTRICT_REF path_to_file,
        st::size_type const min_num_bytes ) {
        return ::NS(File_num_bytes_or_minimum)(
            path_to_file.c_str(), min_num_bytes ); }

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
