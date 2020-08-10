#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/backend/dlib_loader_posix.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
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

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using base_t = st::BaseDynLibLoader;
        using this_t = st::PosixDynLibLoader;
        using st_status_t = this_t::status_t;
    }

    constexpr this_t::load_flags_t this_t::DLIB_HANDLE_LOAD_NONE;

    #if defined( _POSIX_VERSION )
    constexpr this_t::load_flags_t this_t::DLIB_HANDLE_LOAD_LAZY;
    constexpr this_t::load_flags_t this_t::DLIB_HANDLE_LOAD_NOW;
    constexpr this_t::load_flags_t this_t::DLIB_HANDLE_LOAD_LOCAL;
    constexpr this_t::load_flags_t this_t::DLIB_HANDLE_LOAD_GLOBAL;

    constexpr bool this_t::DLIB_HANDLE_LOAD_SUPPORTS_NOLOAD;
    constexpr this_t::load_flags_t this_t::DLIB_HANDLE_LOAD_NOLOAD;

    constexpr bool this_t::DLIB_HANDLE_LOAD_SUPPORTS_NODELETE;
    constexpr this_t::load_flags_t this_t::DLIB_HANDLE_LOAD_NODELETE;

    constexpr bool this_t::DLIB_HANDLE_LOAD_SUPPORTS_DEEPBIND;
    constexpr this_t::load_flags_t this_t::DLIB_HANDLE_LOAD_DEEPBIND;

    constexpr this_t::load_flags_t this_t::DLIB_HANDLE_LOAD_DEFAULT_FLAGS;
    constexpr this_t::load_flags_t this_t::DLIB_HANDLE_LOAD_ALL_FLAGS;

    /* --------------------------------------------------------------------- */

    this_t::PosixDynLibLoader(
        this_t::load_flags_t const initial_default_load_flags ) :
        st::BaseDynLibLoader( base_t::DLIB_PLATFORM_POSIX ),
        m_handle( nullptr, &this_t::CLOSE_DLIB_HANDLE ),
        m_current_load_flags( this_t::DLIB_HANDLE_LOAD_NONE ),
        m_default_load_flags( initial_default_load_flags )
    {

    }

    this_t::PosixDynLibLoader(
        this_t::fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib,
        this_t::load_flags_t const initial_default_load_flags ) :
        st::BaseDynLibLoader( path_to_dlib, base_t::DLIB_PLATFORM_POSIX ),
        m_handle( nullptr, &this_t::CLOSE_DLIB_HANDLE ),
        m_current_load_flags( this_t::DLIB_HANDLE_LOAD_NONE ),
        m_default_load_flags( initial_default_load_flags )
    {

    }

    /* --------------------------------------------------------------------- */

    this_t::const_handle_t this_t::dlib_handle() const SIXTRL_NOEXCEPT
    {
        return this->m_handle.get();
    }

    this_t::handle_t this_t::dlib_handle() SIXTRL_NOEXCEPT
    {
        return this->m_handle.get();
    }

    this_t::load_flags_t this_t::current_load_flags() const SIXTRL_NOEXCEPT
    {
        return this->m_current_load_flags;
    }

    this_t::load_flags_t this_t::default_load_flags() const SIXTRL_NOEXCEPT
    {
        return this->m_default_load_flags;
    }

    this_t::status_t this_t::set_default_load_flags(
        this_t::load_flags_t const default_load_flags ) SIXTRL_NOEXCEPT
    {
        st::status_t status = st::STATUS_GENERAL_FAILURE;
        this_t::load_flags_t const sanitized_flags =
            this_t::SANITIZE_DLIB_LOAD_FLAGS( default_load_flags );

        if( sanitized_flags != this_t::DLIB_HANDLE_LOAD_NONE )
        {
            this->m_default_load_flags = sanitized_flags;
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    st_status_t this_t::load_dynamic_library(
        this_t::load_flags_t const load_flags )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        this_t::load_flags_t const sanitized_flags =
            this_t::SANITIZE_DLIB_LOAD_FLAGS( load_flags );

        if( sanitized_flags != this_t::DLIB_HANDLE_LOAD_NONE )
        {
            this_t::load_flags_t const saved_default_flags =
                this->m_default_load_flags;

            status = this->load_dynamic_library();
            this->m_default_load_flags = saved_default_flags;
        }

        return status;
    }

    st_status_t this_t::load_dynamic_library(
        this_t::fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib,
        this_t::load_flags_t const load_flags )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        this_t::load_flags_t const sanitized_flags =
            this_t::SANITIZE_DLIB_LOAD_FLAGS( load_flags );

        if( ( sanitized_flags != this_t::DLIB_HANDLE_LOAD_NONE ) &&
            ( !path_to_dlib.empty() ) )
        {
            this_t::load_flags_t const saved_default_flags =
                this->m_default_load_flags;

            status = this->load_dynamic_library( path_to_dlib );
            this->m_default_load_flags = saved_default_flags;
        }

        return status;
    }

    /* ********************************************************************* */

    this_t::raw_symbol_t this_t::do_load_raw_symbol(
        this_t::string_type const& SIXTRL_RESTRICT_REF symbol_name,
        bool const symbol_is_required ) const
    {
        this_t::raw_symbol_t symbol = nullptr;

        if( ( this->has_dynamic_lib_handle() ) && ( !symbol_name.empty() ) )
        {
            /* reset error message */
            ::dlerror();

            symbol = ::dlsym( const_cast< handle_t >(
                this->dlib_handle() ), symbol_name.c_str() );

            char const* dlsym_error_msg = ::dlerror();

            if( ( symbol_is_required ) && ( dlsym_error_msg != nullptr ) )
            {
                typename this_t::sstream_t a2str;
                a2str << "Unable to load symbol \"" << symbol_name << "\"\r\n"
                      << "from dynamic library: \r\n"
                      << dlsym_error_msg;

                throw std::runtime_error( a2str.str() );
            }
        }

        if( ( symbol_is_required ) && ( symbol == nullptr ) )
        {
            typename this_t::sstream_t a2str;
            a2str << "Unable to load symbol \"" << symbol_name << "\" from "
                  << "dynamic library\r\n";

            throw std::runtime_error( a2str.str() );
        }

        return symbol;
    }

    st_status_t this_t::do_load_dynamic_library(
        this_t::fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib )
    {
        return this->do_load_dynamic_library_priv_impl( path_to_dlib );
    }

    st_status_t this_t::do_load_dynamic_library_priv_impl(
        this_t::fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( !path_to_dlib.empty() ) &&
            ( ( !this->has_dynamic_lib_handle() ) ||
              ( ( this->allow_dynamic_library_reload() ) &&
                ( this->path_to_dynamic_lib_str().compare(
                    path_to_dlib ) == 0 ) ) ) )
        {
            status = this->set_managed_handle( this_t::managed_handle_t(
                ::dlopen( path_to_dlib.c_str(), this->m_default_load_flags ),
                &this_t::CLOSE_DLIB_HANDLE ) );

            if( status == st::STATUS_SUCCESS )
            {
                this->update_path_to_dlib( path_to_dlib );
                this->m_current_load_flags = this->m_default_load_flags;
            }
        }

        return status;
    }

    void this_t::do_reset()
    {
        this->m_handle.reset( nullptr );
        this->m_current_load_flags = this_t::DLIB_HANDLE_LOAD_NONE;
        base_t::do_reset();
    }

    st_status_t this_t::set_managed_handle( this_t::managed_handle_t handle )
    {
        this->m_handle = std::move( handle );
        this->set_has_dlib_handle_flag( this->dlib_handle() != nullptr );
        return st::STATUS_SUCCESS;
    }
    #endif /* _POSIX_VERSION */
}
#endif /* C++, Host && defined( _POSIX_VERSION ) */
