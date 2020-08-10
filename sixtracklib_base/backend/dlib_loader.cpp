#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/backend/dlib_loader.h"
    #include "sixtracklib_base/backend/dlib_loader_posix.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdexcept>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using base_t = st::BaseDynLibLoader;
        using posix_handle_t = st::PosixDynLibLoader;
        using st_status_t = base_t::status_t;
    }

    constexpr base_t::dlib_platform_t base_t::DLIB_PLATFORM_UNDEFINED;
    constexpr base_t::dlib_platform_t base_t::DLIB_PLATFORM_POSIX;

    /* --------------------------------------------------------------------- */

    posix_handle_t const* base_t::as_posix_dlib_loader() const SIXTRL_NOEXCEPT
    {
        return ( this->m_dlib_platform == base_t::DLIB_PLATFORM_POSIX )
            ? static_cast< posix_handle_t const* >( this ) : nullptr;
    }

    posix_handle_t* base_t::as_posix_dlib_loader() SIXTRL_NOEXCEPT
    {
        return const_cast< posix_handle_t* >( static_cast< base_t const& >(
            *this ).as_posix_dlib_loader() );
    }

    /* --------------------------------------------------------------------- */

    base_t::dlib_platform_t base_t::dlib_platform() const SIXTRL_NOEXCEPT {
        return this->m_dlib_platform; }

    bool base_t::is_posix() const SIXTRL_NOEXCEPT {
        return ( this->m_dlib_platform == DLIB_PLATFORM_POSIX ); }

    bool base_t::has_path_to_dynamic_lib() const SIXTRL_NOEXCEPT {
        return !this->m_path_to_dlib.empty(); }

    base_t::fs_string_type const& base_t::path_to_dynamic_lib_str(
        ) const SIXTRL_NOEXCEPT { return this->m_path_to_dlib; }

    base_t::fs_string_char_t const* base_t::path_to_dynamic_lib(
        ) const SIXTRL_NOEXCEPT { return this->m_path_to_dlib.c_str(); }

    bool base_t::has_dynamic_lib_handle() const SIXTRL_NOEXCEPT {
        return this->m_has_handle; }

    void base_t::reset() { this->do_reset(); }

    bool base_t::allow_dynamic_library_reload() const SIXTRL_NOEXCEPT {
        return this->m_allow_reload; }

    st_status_t base_t::load_dynamic_library()
    {
        return this->load_dynamic_library( this->m_path_to_dlib );
    }

    st_status_t base_t::load_dynamic_library(
        base_t::fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( !path_to_dlib.empty() ) &&
            ( this->m_dlib_platform != base_t::DLIB_PLATFORM_UNDEFINED ) )
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

    base_t::raw_symbol_t base_t::load_raw_symbol(
        base_t::string_type const& SIXTRL_RESTRICT_REF symbol_name,
        bool const symbol_is_required ) const
    {
        return this->do_load_raw_symbol( symbol_name, symbol_is_required );
    }

    /* ********************************************************************* */

    void base_t::do_reset() { this->m_has_handle = false; }

    st_status_t base_t::set_path_to_dlib(
        base_t::fs_string_type const& SIXTRL_RESTRICT_REF path_to_dlib )
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
