#ifndef SIXTRACKLIB_BASE_BACKEND_DYNAMIC_LIBRARY_LOADER_H__
#define SIXTRACKLIB_BASE_BACKEND_DYNAMIC_LIBRARY_LOADER_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/backend/definitions.h"
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

    class SIXTRL_BASE_EXPORT_API BaseDynLibLoader
    {
        public:

        using size_type        = SIXTRL_CXX_NAMESPACE::size_t;
        using status_t         = SIXTRL_CXX_NAMESPACE::status_t;

        /* TODO: Typedef / idef this in case we have to use an OS
         *       where the filesystem strings positively *have* to be
         *       wchar_t based (i.e. win32 with native wstring_t paths) */

        using string_type      = std::string;
        using string_char_t    = string_type::value_type;
        using sstream_t        = std::stringstream;

        using fs_string_type   = string_type;
        using fs_string_char_t = string_char_t;
        using fs_sstream_t     = sstream_t;

        using dlib_platform_t  = uint64_t;
        using raw_symbol_t     = void*; /* This should work anywhere */

        /* ----------------------------------------------------------------- */

        static constexpr dlib_platform_t DLIB_PLATFORM_UNDEFINED =
            dlib_platform_t{ 0 };

        static constexpr dlib_platform_t DLIB_PLATFORM_POSIX =
            dlib_platform_t{ 1 };

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual ~BaseDynLibLoader() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN PosixDynLibLoader const*
        as_posix_dlib_loader() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN PosixDynLibLoader*
        as_posix_dlib_loader() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN dlib_platform_t dlib_platform() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_posix() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_path_to_dynamic_lib() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN fs_string_type const& path_to_dynamic_lib_str(
            ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN fs_string_char_t const* path_to_dynamic_lib(
            ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_dynamic_lib_handle() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_path_to_dlib(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void reset();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool
        allow_dynamic_library_reload() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t load_dynamic_library();

        SIXTRL_HOST_FN status_t load_dynamic_library(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN raw_symbol_t load_raw_symbol(
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
            dlib_platform_t const platform,
            bool const allow_reload = false,
            bool const has_dlib_handle = false ) :
            m_path_to_dlib(), m_dlib_platform( platform ),
            m_allow_reload( allow_reload ),
            m_has_handle( has_dlib_handle ) {}

        SIXTRL_HOST_FN BaseDynLibLoader(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib,
            dlib_platform_t const platform,
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

        SIXTRL_HOST_FN virtual status_t do_load_dynamic_library(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib ) = 0;

        SIXTRL_HOST_FN virtual raw_symbol_t do_load_raw_symbol(
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

        fs_string_type m_path_to_dlib;
        dlib_platform_t m_dlib_platform;
        bool m_allow_reload = false;
        bool m_has_handle = false;
    };
}

extern "C"
{
    typedef SIXTRL_CXX_NAMESPACE::BaseDynLibLoader NS(BaseDynLibLoader);
}

#else

struct BaseDynLibLoader;

#endif /* C++, Host */

#endif /* SIXTRACKLIB_BASE_BACKEND_DYNAMIC_LIBRARY_BACKEND_MIXIN_HPP__ */
