#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/backends/dlib_loader.h"
    #include "sixtracklib/common/backends/dlib_loader_posix.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdexcept>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st            = SIXTRL_CXX_NAMESPACE;
        using base_type         = st::BaseDynLibLoader;
        using posix_handle_type = st::PosixDynLibLoader;
        using st_status_t       = base_type::status_type;
    }

    constexpr base_type::platform_type base_type::UNDEFINED_PLATFORM;
    constexpr base_type::platform_type base_type::POSIX_PLATFORM;

    /* --------------------------------------------------------------------- */

    posix_handle_type const* base_type::as_posix_loader() const SIXTRL_NOEXCEPT
    {
        return ( this->m_dlib_platform == base_type::POSIX_PLATFORM )
            ? static_cast< posix_handle_type const* >( this ) : nullptr;
    }

    posix_handle_type* base_type::as_posix_loader() SIXTRL_NOEXCEPT
    {
        return const_cast< posix_handle_type* >(
            static_cast< base_type const& >( *this ).as_posix_loader() );
    }

    /* --------------------------------------------------------------------- */

    base_type::platform_type base_type::dlib_platform() const SIXTRL_NOEXCEPT {
        return this->m_dlib_platform; }

    bool base_type::is_posix() const SIXTRL_NOEXCEPT {
        return ( this->m_dlib_platform == POSIX_PLATFORM ); }

    bool base_type::has_path_to_dynamic_lib() const SIXTRL_NOEXCEPT {
        return !this->m_path_to_dlib.empty(); }

    base_type::fs_string_type const& base_type::path_to_dynamic_lib_str(
        ) const SIXTRL_NOEXCEPT { return this->m_path_to_dlib; }

    base_type::fs_string_char_type const* base_type::path_to_dynamic_lib(
        ) const SIXTRL_NOEXCEPT { return this->m_path_to_dlib.c_str(); }

    bool base_type::has_dynamic_lib_handle() const SIXTRL_NOEXCEPT {
        return this->m_has_handle; }

    void base_type::reset() { this->do_reset(); }

    bool base_type::allow_dynamic_library_reload() const SIXTRL_NOEXCEPT {
        return this->m_allow_reload; }

    st_status_t base_type::load_dynamic_library()
    {
        return this->load_dynamic_library( this->m_path_to_dlib );
    }

    st_status_t base_type::load_dynamic_library(
        base_type::fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( !path_to_dlib.empty() ) &&
            ( this->m_dlib_platform != base_type::UNDEFINED_PLATFORM ) )
        {
            if( ( !this->has_dynamic_lib_handle() ) ||
                ( ( this->allow_dynamic_library_reload() ) ) )
            {
                status = this->do_load_dynamic_library( path_to_dlib );

                if( status == st::STATUS_SUCCESS )
                {
                    this->m_path_to_dlib = path_to_dlib;
                    this->m_has_handle = true;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    base_type::raw_symbol_type base_type::load_raw_symbol(
        base_type::string_type const& SIXTRL_RESTRICT_REF symbol_name,
        bool const symbol_is_required ) const
    {
        return this->do_load_raw_symbol( symbol_name, symbol_is_required );
    }

    /* ********************************************************************* */

    void base_type::do_reset() { this->m_has_handle = false; }

    st_status_t base_type::set_path_to_dlib(
        base_type::fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( !this->has_dynamic_lib_handle() )
        {
            this->update_path_to_dlib( path_to_dlib );
            status = st::STATUS_SUCCESS;
        }

        return status;
    }
}

#endif /* C++, Host */
