#ifndef SIXTRACKLIB_BASE_BACKEND_DYNAMIC_LIBRARY_LOADER_H__
#define SIXTRACKLIB_BASE_BACKEND_DYNAMIC_LIBRARY_LOADER_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <sstream>
        #include <string>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class PosixDynLibLoader;

    class BaseDynLibLoader
    {
        public:

        using size_type        = SIXTRL_CXX_NAMESPACE::size_type;
        using status_type      = SIXTRL_CXX_NAMESPACE::status_type;
        using platform_type       = SIXTRL_CXX_NAMESPACE::dlib_platform_type;
        using raw_symbol_type     = void*; /* This should work anywhere */

        /* TODO: Typedef / idef this in case we have to use an OS
         *       where the filesystem strings positively *have* to be
         *       wchar_t based (i.e. win32 with native wstring_t paths) */

        using string_type         = std::string;
        using string_char_type    = string_type::value_type;
        using sstream_type        = std::stringstream;

        using fs_string_type      = string_type;
        using fs_string_char_type = string_char_type;
        using fs_sstream_type     = sstream_type;

        /* ----------------------------------------------------------------- */

        static constexpr platform_type UNDEFINED_PLATFORM =
            SIXTRL_CXX_NAMESPACE::DLIB_PLATFORM_UNDEFINED;

        static constexpr platform_type POSIX_PLATFORM =
            SIXTRL_CXX_NAMESPACE::DLIB_PLATFORM_POSIX;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual ~BaseDynLibLoader() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN PosixDynLibLoader const*
        as_posix_loader() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN PosixDynLibLoader* as_posix_loader() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN dlib_platform_type dlib_platform() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_posix() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool has_path_to_dynamic_lib() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN fs_string_type const& path_to_dynamic_lib_str(
            ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN fs_string_char_type const* path_to_dynamic_lib(
            ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_dynamic_lib_handle() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_path_to_dlib(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void reset();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool allow_dynamic_library_reload() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type load_dynamic_library();
        SIXTRL_HOST_FN status_type load_dynamic_library(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN raw_symbol_type load_raw_symbol(
            string_type const& SIXTRL_RESTRICT_REF symbol_name,
            bool const symbol_is_required = true ) const;

        template< typename SymbFnT >
        SIXTRL_HOST_FN SymbFnT load_symbol(
            string_type const& SIXTRL_RESTRICT_REF symbol_name,
            bool const symbol_is_required ) const
        {
            #if __cplusplus >= 201103L
            return reinterpret_cast< SymbFnT >(
                this->do_load_raw_symbol( symbol_name, symbol_is_required ) );
            #else /* earlier than C++11 */
            return ( SymbFnT )this->do_load_raw_symbol(
                symbol_name, symbol_is_required );
            #endif /* C++11 */
        }

        protected:

        SIXTRL_HOST_FN explicit BaseDynLibLoader(
            dlib_platform_type const platform,
            bool const allow_reload = false,
            bool const has_dlib_handle = false ) :
            m_path_to_dlib(), m_dlib_platform( platform ),
            m_allow_reload( allow_reload ),
            m_has_handle( has_dlib_handle ) {}

        SIXTRL_HOST_FN BaseDynLibLoader(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib,
            dlib_platform_type const platform,
            bool const allow_reload = false,
            bool const has_dlib_handle = false ) :
            m_path_to_dlib( path_to_dlib ),
            m_dlib_platform( platform ),
            m_allow_reload( allow_reload ),
            m_has_handle( has_dlib_handle ) {}

        SIXTRL_HOST_FN BaseDynLibLoader(
            BaseDynLibLoader const& ) = delete;

        SIXTRL_HOST_FN BaseDynLibLoader(
            BaseDynLibLoader&& ) = default;

        SIXTRL_HOST_FN BaseDynLibLoader& operator=(
            BaseDynLibLoader const& ) = delete;

        SIXTRL_HOST_FN BaseDynLibLoader& operator=(
            BaseDynLibLoader&& ) = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual status_type do_load_dynamic_library(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib ) = 0;

        SIXTRL_HOST_FN virtual raw_symbol_type do_load_raw_symbol(
            string_type const& SIXTRL_RESTRICT_REF symbol_name,
            bool const symbol_is_required ) const = 0;

        SIXTRL_HOST_FN virtual void do_reset();

        SIXTRL_HOST_FN void set_has_dlib_handle_flag(
            bool const has_handle ) SIXTRL_NOEXCEPT {
            this->m_has_handle = has_handle; }

        SIXTRL_HOST_FN void set_allow_reload_flag(
            bool const allow_reload ) SIXTRL_NOEXCEPT {
            this->m_allow_reload = allow_reload; }

        SIXTRL_HOST_FN void update_path_to_dlib(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib ) {
            this->m_path_to_dlib = path_to_dlib;
        }

        private:

        fs_string_type      m_path_to_dlib;
        dlib_platform_type  m_dlib_platform;
        bool m_allow_reload = false;
        bool m_has_handle   = false;
    };
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::BaseDynLibLoader NS(BaseDynLibLoader);
#else
typedef void NS(BaseDynLibLoader);
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_BACKEND_DYNAMIC_LIBRARY_LOADER_H__ */
