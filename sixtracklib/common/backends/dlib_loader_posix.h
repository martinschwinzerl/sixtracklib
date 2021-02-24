#ifndef SIXTRACKLIB_BACKENDS_DLIB_LOADER_POSIX_H__
#define SIXTRACKLIB_BACKENDS_DLIB_LOADER_POSIX_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/backends/definitions.h"
    #include "sixtracklib/common/backends/dlib_loader.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <memory>
        #include <sstream>
        #include <string>
    #endif /* C++ */

    #if defined( __unix__ )
        #if defined( __GNUC__ ) && !defined( _GNU_SOURCE )
            #define _GNU_SOURCE
        #endif /* Gcc */
        #include <dlfcn.h>
    #endif /* defined( __unix__ ) */

    #if defined( __unix__ ) || \
        ( defined( __APPLE__ ) && defined( __MACH__ ) )
        #include <unistd.h>
    #endif /* *nix / POSIX / Apple MacOS X or iOS */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    #if defined( _POSIX_VERSION )
    class PosixDynLibLoader : public BaseDynLibLoader
    {
        public:

        using handle_type       = void*;
        using const_handle_type = void const*;
        using load_flags_type   = SIXTRL_INT32_TYPE;

        /* ----------------------------------------------------------------- */

        static constexpr load_flags_type DLIB_HANDLE_LOAD_NONE =
            load_flags_type{ 0 };

        static constexpr load_flags_type DLIB_HANDLE_LOAD_LAZY =
            static_cast< load_flags_type >( RTLD_LAZY );

        static constexpr load_flags_type DLIB_HANDLE_LOAD_NOW =
            static_cast< load_flags_type >( RTLD_NOW );

        static constexpr load_flags_type DLIB_HANDLE_LOAD_GLOBAL =
            static_cast< load_flags_type >( RTLD_GLOBAL );

        static constexpr load_flags_type DLIB_HANDLE_LOAD_LOCAL =
            static_cast< load_flags_type >( RTLD_LOCAL );

        #if defined( RTLD_NOLOAD )
        static constexpr bool DLIB_HANDLE_LOAD_SUPPORTS_NOLOAD = true;
        static constexpr load_flags_type DLIB_HANDLE_LOAD_NOLOAD =
            static_cast< load_flags_type >( RTLD_NOLOAD );

        #else /* defined( RTLD_NOLOAD ) */
        static constexpr bool DLIB_HANDLE_LOAD_SUPPORTS_NOLOAD = false;
        static constexpr load_flags_type DLIB_HANDLE_LOAD_NOLOAD =
            load_flags_type{ 0 };

        #endif /* defined( RTLD_NOLOAD ) */

        #if defined( RTLD_NODELETE )
        static constexpr bool DLIB_HANDLE_LOAD_SUPPORTS_NODELETE = true;
        static constexpr load_flags_type DLIB_HANDLE_LOAD_NODELETE =
            static_cast< load_flags_type >( RTLD_NODELETE );

        #else /* defined( RTLD_NODELETE ) */
        static constexpr bool DLIB_HANDLE_LOAD_SUPPORTS_NODELETE = false;
        static constexpr load_flags_type DLIB_HANDLE_LOAD_NODELETE =
            load_flags_type{ 0 };

        #endif /* defined( RTLD_NODELETE ) */

        #if defined( RTLD_DEEPBIND )
        static constexpr bool DLIB_HANDLE_LOAD_SUPPORTS_DEEPBIND = true;
        static constexpr load_flags_type DLIB_HANDLE_LOAD_DEEPBIND =
                static_cast< load_flags_type >( RTLD_DEEPBIND );

        #else /* defined( RTLD_DEEPBIND ) */
        static constexpr bool DLIB_HANDLE_LOAD_SUPPORTS_DEEPBIND = false;
        static constexpr load_flags_type DLIB_HANDLE_LOAD_DEEPBIND =
                static_cast< load_flags_type >( 0 );

        #endif /* defined( RTLD_DEEPBIND ) */

        static constexpr load_flags_type DLIB_HANDLE_LOAD_DEFAULT_FLAGS =
            DLIB_HANDLE_LOAD_GLOBAL | DLIB_HANDLE_LOAD_LAZY;

        static constexpr load_flags_type DLIB_HANDLE_LOAD_ALL_FLAGS =
            DLIB_HANDLE_LOAD_GLOBAL   | DLIB_HANDLE_LOAD_LOCAL    |
            DLIB_HANDLE_LOAD_NOW      | DLIB_HANDLE_LOAD_LAZY     |
            DLIB_HANDLE_LOAD_NOLOAD   | DLIB_HANDLE_LOAD_NODELETE |
            DLIB_HANDLE_LOAD_DEEPBIND;

        /* ---------------------------------------------------------------- */

        SIXTRL_HOST_FN explicit PosixDynLibLoader(
            load_flags_type const initial_default_load_flags =
                DLIB_HANDLE_LOAD_DEFAULT_FLAGS );

        SIXTRL_HOST_FN explicit PosixDynLibLoader(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib,
            load_flags_type const initial_default_load_flags =
                DLIB_HANDLE_LOAD_DEFAULT_FLAGS );

        SIXTRL_HOST_FN PosixDynLibLoader(
            PosixDynLibLoader const& ) = delete;

        SIXTRL_HOST_FN PosixDynLibLoader(
            PosixDynLibLoader&& ) = default;

        SIXTRL_HOST_FN PosixDynLibLoader& operator=(
            PosixDynLibLoader const& ) = delete;

        SIXTRL_HOST_FN PosixDynLibLoader& operator=(
            PosixDynLibLoader&& ) = default;

        SIXTRL_HOST_FN virtual ~PosixDynLibLoader() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN const_handle_type dlib_handle() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN handle_type dlib_handle() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN load_flags_type current_load_flags() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN load_flags_type default_load_flags() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_default_load_flags(
            load_flags_type const default_load_flags ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        using BaseDynLibLoader::load_dynamic_library;

        SIXTRL_HOST_FN status_type load_dynamic_library(
            load_flags_type const load_flags );

        SIXTRL_HOST_FN status_type load_dynamic_library(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib,
            load_flags_type const load_flags );

        protected:

        using managed_handle_type = std::unique_ptr< void, void (*)( void* ) >;

        SIXTRL_STATIC SIXTRL_HOST_FN bool IS_DLIB_LOAD_FLAG_SET(
            load_flags_type const flagset,
            load_flags_type const flag ) SIXTRL_NOEXCEPT {
            using _this_type = SIXTRL_CXX_NAMESPACE::PosixDynLibLoader;
            return ( ( flag != _this_type::DLIB_HANDLE_LOAD_NONE ) &&
                     ( ( flagset & flag ) == flag ) );
        }

        SIXTRL_STATIC SIXTRL_HOST_FN load_flags_type SANITIZE_DLIB_LOAD_FLAGS(
            load_flags_type const flags ) SIXTRL_NOEXCEPT {
            using _this_type = SIXTRL_CXX_NAMESPACE::PosixDynLibLoader;
            return ( flags & _this_type::DLIB_HANDLE_LOAD_ALL_FLAGS );
        }

        SIXTRL_STATIC SIXTRL_HOST_FN bool IS_DLIB_NOLOAD_FLAG_SET(
            load_flags_type const flagset ) SIXTRL_NOEXCEPT {
            using _this_type = SIXTRL_CXX_NAMESPACE::PosixDynLibLoader;
            return ( ( ( _this_type::DLIB_HANDLE_LOAD_SUPPORTS_NOLOAD ) &&
                       ( _this_type::IS_DLIB_LOAD_FLAG_SET( flagset,
                         _this_type::DLIB_HANDLE_LOAD_NOLOAD ) ) ) );
        }

        SIXTRL_STATIC SIXTRL_HOST_FN bool IS_DLIB_NODELETE_FLAG_SET(
            load_flags_type const flagset ) SIXTRL_NOEXCEPT {
            using _this_type = SIXTRL_CXX_NAMESPACE::PosixDynLibLoader;
            return ( ( ( _this_type::DLIB_HANDLE_LOAD_SUPPORTS_NODELETE ) &&
                       ( _this_type::IS_DLIB_LOAD_FLAG_SET( flagset,
                         _this_type::DLIB_HANDLE_LOAD_NODELETE ) ) ) );
        }

        SIXTRL_STATIC SIXTRL_HOST_FN bool IS_DLIB_DEEPBINDING_FLAG_SET(
            load_flags_type const flagset ) SIXTRL_NOEXCEPT {
            using _this_type = SIXTRL_CXX_NAMESPACE::PosixDynLibLoader;
            return ( ( ( _this_type::DLIB_HANDLE_LOAD_SUPPORTS_DEEPBIND ) &&
                       ( _this_type::IS_DLIB_LOAD_FLAG_SET( flagset,
                         _this_type::DLIB_HANDLE_LOAD_DEEPBIND ) ) ) );
        }

        SIXTRL_STATIC SIXTRL_HOST_FN void CLOSE_DLIB_HANDLE( handle_type handle ){
            if( handle != nullptr )
            {
                int const ret = ::dlclose( handle );
                SIXTRL_ASSERT( ret == 0 );
                ( void )ret;
            }

            return;
        }

        SIXTRL_HOST_FN status_type do_load_dynamic_library(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib ) override;

        SIXTRL_HOST_FN raw_symbol_type do_load_raw_symbol(
            string_type const& SIXTRL_RESTRICT_REF symbol_name,
            bool const symbol_required ) const override;

        SIXTRL_HOST_FN void do_reset() override;

        SIXTRL_HOST_FN status_type set_managed_handle( managed_handle_type handle );

        private:

        SIXTRL_HOST_FN status_type do_load_dynamic_library_priv_impl(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib );

        managed_handle_type m_handle = managed_handle_type{ nullptr,
            &PosixDynLibLoader::CLOSE_DLIB_HANDLE };

        load_flags_type m_current_load_flags;
        load_flags_type m_default_load_flags;
    };

    #else /* !defined( _POSIX_VERSION ) */

    class SIXTRL_BASE_EXPORT_API PosixDynLibLoader : public BaseDynLibLoader
    {
        public:

        static_assert( 0 == 1, "Only implemented for POSIX platforms / OSes" );

        using handle_type = void*;
        using const_handle_type = void const*;
        using load_flags_type = int32_t;

        /* ----------------------------------------------------------------- */

        static constexpr load_flags_type DLIB_HANDLE_LOAD_NONE =
            load_flags_type{ 0 };

        protected:

        SIXTRL_HOST_FN status_type do_load_dynamic_library(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib ) override
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        SIXTRL_HOST_FN status_type do_load_raw_symbol(
            string_type const& SIXTRL_RESTRICT_REF symbol_name ) const override
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }
    };

    #endif /* defined( _POSIX_VERSION ) */
}
#endif /* C+, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::PosixDynLibLoader NS(PosixDynLibLoader);
#else /* defined( __cplusplus ) && !defined( _GPUCODE ) */
typedef void NS(PosixDynLibLoader);
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BACKENDS_DLIB_LOADER_POSIX_H__ */
