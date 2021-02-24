#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/backends/dlib_loader_posix.h"
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
        using base_type   = st::BaseDynLibLoader;
        using _this_type  = st::PosixDynLibLoader;
        using st_status_type = _this_type::status_type;
    }

    constexpr _this_type::load_flags_type _this_type::DLIB_HANDLE_LOAD_NONE;

    #if defined( _POSIX_VERSION )
    constexpr _this_type::load_flags_type _this_type::DLIB_HANDLE_LOAD_LAZY;
    constexpr _this_type::load_flags_type _this_type::DLIB_HANDLE_LOAD_NOW;
    constexpr _this_type::load_flags_type _this_type::DLIB_HANDLE_LOAD_LOCAL;
    constexpr _this_type::load_flags_type _this_type::DLIB_HANDLE_LOAD_GLOBAL;

    constexpr bool _this_type::DLIB_HANDLE_LOAD_SUPPORTS_NOLOAD;
    constexpr _this_type::load_flags_type _this_type::DLIB_HANDLE_LOAD_NOLOAD;

    constexpr bool _this_type::DLIB_HANDLE_LOAD_SUPPORTS_NODELETE;
    constexpr _this_type::load_flags_type _this_type::DLIB_HANDLE_LOAD_NODELETE;

    constexpr bool _this_type::DLIB_HANDLE_LOAD_SUPPORTS_DEEPBIND;
    constexpr _this_type::load_flags_type _this_type::DLIB_HANDLE_LOAD_DEEPBIND;

    constexpr _this_type::load_flags_type _this_type::DLIB_HANDLE_LOAD_DEFAULT_FLAGS;
    constexpr _this_type::load_flags_type _this_type::DLIB_HANDLE_LOAD_ALL_FLAGS;

    /* --------------------------------------------------------------------- */

    _this_type::PosixDynLibLoader(
        _this_type::load_flags_type const initial_default_load_flags ) :
        st::BaseDynLibLoader( base_type::POSIX_PLATFORM ),
        m_handle( nullptr, &_this_type::CLOSE_DLIB_HANDLE ),
        m_current_load_flags( _this_type::DLIB_HANDLE_LOAD_NONE ),
        m_default_load_flags( initial_default_load_flags )
    {

    }

    _this_type::PosixDynLibLoader(
        _this_type::fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib,
        _this_type::load_flags_type const initial_default_load_flags ) :
        st::BaseDynLibLoader( path_to_dlib, base_type::POSIX_PLATFORM ),
        m_handle( nullptr, &_this_type::CLOSE_DLIB_HANDLE ),
        m_current_load_flags( _this_type::DLIB_HANDLE_LOAD_NONE ),
        m_default_load_flags( initial_default_load_flags )
    {

    }

    /* --------------------------------------------------------------------- */

    _this_type::const_handle_type _this_type::dlib_handle() const SIXTRL_NOEXCEPT
    {
        return this->m_handle.get();
    }

    _this_type::handle_type _this_type::dlib_handle() SIXTRL_NOEXCEPT
    {
        return this->m_handle.get();
    }

    _this_type::load_flags_type _this_type::current_load_flags() const SIXTRL_NOEXCEPT
    {
        return this->m_current_load_flags;
    }

    _this_type::load_flags_type _this_type::default_load_flags() const SIXTRL_NOEXCEPT
    {
        return this->m_default_load_flags;
    }

    st_status_type _this_type::set_default_load_flags(
        _this_type::load_flags_type const default_load_flags ) SIXTRL_NOEXCEPT
    {
        st::status_type status = st::STATUS_GENERAL_FAILURE;
        _this_type::load_flags_type const sanitized_flags =
            _this_type::SANITIZE_DLIB_LOAD_FLAGS( default_load_flags );

        if( sanitized_flags != _this_type::DLIB_HANDLE_LOAD_NONE )
        {
            this->m_default_load_flags = sanitized_flags;
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    st_status_type _this_type::load_dynamic_library(
        _this_type::load_flags_type const load_flags )
    {
        st_status_type status = st::STATUS_GENERAL_FAILURE;
        _this_type::load_flags_type const sanitized_flags =
            _this_type::SANITIZE_DLIB_LOAD_FLAGS( load_flags );

        if( sanitized_flags != _this_type::DLIB_HANDLE_LOAD_NONE )
        {
            _this_type::load_flags_type const saved_default_flags =
                this->m_default_load_flags;

            status = this->load_dynamic_library();
            this->m_default_load_flags = saved_default_flags;
        }

        return status;
    }

    st_status_type _this_type::load_dynamic_library(
        _this_type::fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib,
        _this_type::load_flags_type const load_flags )
    {
        st_status_type status = st::STATUS_GENERAL_FAILURE;
        _this_type::load_flags_type const sanitized_flags =
            _this_type::SANITIZE_DLIB_LOAD_FLAGS( load_flags );

        if( ( sanitized_flags != _this_type::DLIB_HANDLE_LOAD_NONE ) &&
            ( !path_to_dlib.empty() ) )
        {
            _this_type::load_flags_type const saved_default_flags =
                this->m_default_load_flags;

            status = this->load_dynamic_library( path_to_dlib );
            this->m_default_load_flags = saved_default_flags;
        }

        return status;
    }

    /* ********************************************************************* */

    _this_type::raw_symbol_type _this_type::do_load_raw_symbol(
        _this_type::string_type const& SIXTRL_RESTRICT_REF symbol_name,
        bool const symbol_is_required ) const
    {
        _this_type::raw_symbol_type symbol = nullptr;

        if( ( this->has_dynamic_lib_handle() ) && ( !symbol_name.empty() ) )
        {
            /* reset error message */
            ::dlerror();

            symbol = ::dlsym( const_cast< _this_type::handle_type >(
                this->dlib_handle() ), symbol_name.c_str() );

            char const* dlsym_error_msg = ::dlerror();

            if( ( symbol_is_required ) && ( dlsym_error_msg != nullptr ) )
            {
                typename _this_type::sstream_type a2str;
                a2str << "Unable to load symbol \"" << symbol_name << "\"\r\n"
                      << "from dynamic library: \r\n"
                      << dlsym_error_msg;

                throw std::runtime_error( a2str.str() );
            }
        }

        if( ( symbol_is_required ) && ( symbol == nullptr ) )
        {
            typename _this_type::sstream_type a2str;
            a2str << "Unable to load symbol \"" << symbol_name << "\" from "
                  << "dynamic library\r\n";

            throw std::runtime_error( a2str.str() );
        }

        return symbol;
    }

    st_status_type _this_type::do_load_dynamic_library(
        _this_type::fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib )
    {
        return this->do_load_dynamic_library_priv_impl( path_to_dlib );
    }

    st_status_type _this_type::do_load_dynamic_library_priv_impl(
        _this_type::fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib )
    {
        st_status_type status = st::STATUS_GENERAL_FAILURE;

        if( ( !path_to_dlib.empty() ) &&
            ( ( !this->has_dynamic_lib_handle() ) ||
              ( ( this->allow_dynamic_library_reload() ) &&
                ( this->path_to_dynamic_lib_str().compare(
                    path_to_dlib ) == 0 ) ) ) )
        {
            status = this->set_managed_handle( _this_type::managed_handle_type(
                ::dlopen( path_to_dlib.c_str(), this->m_default_load_flags ),
                &_this_type::CLOSE_DLIB_HANDLE ) );

            if( status == st::STATUS_SUCCESS )
            {
                this->update_path_to_dlib( path_to_dlib );
                this->m_current_load_flags = this->m_default_load_flags;
            }
        }

        return status;
    }

    void _this_type::do_reset()
    {
        this->m_handle.reset( nullptr );
        this->m_current_load_flags = _this_type::DLIB_HANDLE_LOAD_NONE;
        base_type::do_reset();
    }

    st_status_type _this_type::set_managed_handle(
        _this_type::managed_handle_type handle )
    {
        this->m_handle = std::move( handle );
        this->set_has_dlib_handle_flag( this->dlib_handle() != nullptr );
        return st::STATUS_SUCCESS;
    }
    #endif /* _POSIX_VERSION */
}
#endif /* C++, Host && defined( _POSIX_VERSION ) */
