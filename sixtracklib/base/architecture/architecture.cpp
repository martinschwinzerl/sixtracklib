#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/definitions.h"
    #include "sixtracklib/base/architecture/architecture.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUODE ) && defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <cstring>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using arch_t = st::Architecture;
        using st_arch_id_t = arch_t::arch_id_t;
        using st_status_t  = arch_t::status_t;
        using st_size_t = arch_t::size_type;
    }

    constexpr arch_t::class_variant_t arch_t::ARCHITECTURE_VARIANT_DEFAULT;
    constexpr arch_t::class_variant_t arch_t::ARCHITECTURE_VARIANT_HAS_NODES;

    bool arch_t::IS_PREDEFINED_ARCHITECTURE(
        st_arch_id_t const arch_id ) SIXTRL_NOEXCEPT
    {
        return ( ( arch_id == st::ARCHITECTURE_CPU ) ||
                 ( arch_id == st::ARCHITECTURE_OPENCL ) ||
                 ( arch_id == st::ARCHITECTURE_CUDA ) ||
                 ( arch_id == st::ARCHITECTURE_CUDA_NVRTC ) ||
                 ( arch_id == st::ARCHITECTURE_OPENMP ) );
    }

    bool arch_t::IS_PREDEFINED_ARCHITECTURE(
        std::string const& SIXTRL_RESTRICT_REF arch_str ) SIXTRL_NOEXCEPT
    {
        return arch_t::IS_PREDEFINED_ARCHITECTURE(
            arch_t::PREDEFINED_ARCHITECTURE_STR_TO_ID( arch_str ) );
    }

    st_arch_id_t arch_t::PREDEFINED_ARCHITECTURE_STR_TO_ID(
        std::string const& SIXTRL_RESTRICT_REF arch_str ) SIXTRL_NOEXCEPT
    {
        st_arch_id_t arch_id = st::ARCHITECTURE_ILLEGAL;

        if( !arch_str.empty() )
        {
            arch_id = st::ARCHITECTURE_UNDEFINED;

            if( arch_str.compare( SIXTRL_ARCHITECTURE_CPU_STR ) == 0 )
            {
                arch_id = st::ARCHITECTURE_CPU;
            }
            else if( arch_str.compare( SIXTRL_ARCHITECTURE_OPENCL_STR ) == 0 )
            {
                arch_id = st::ARCHITECTURE_OPENCL;
            }
            else if( arch_str.compare( SIXTRL_ARCHITECTURE_CUDA_STR ) == 0 )
            {
                arch_id = st::ARCHITECTURE_CUDA;
            }
            else if( arch_str.compare(
                    SIXTRL_ARCHITECTURE_CUDA_NVRTC_STR ) == 0 )
            {
                arch_id = st::ARCHITECTURE_CUDA_NVRTC;
            }
            else if( arch_str.compare( SIXTRL_ARCHITECTURE_OPENMP_STR ) == 0 )
            {
                arch_id = st::ARCHITECTURE_OPENMP;
            }
        }

        return arch_id;
    }

    std::string arch_t::PREDEFINED_ARCHITECTURE_ID_TO_STR(
        st_arch_id_t const arch_id )
    {
        switch( arch_id )
        {
            case st::ARCHITECTURE_CPU:
            {
                return std::string{ SIXTRL_ARCHITECTURE_CPU_STR };
            }

            case st::ARCHITECTURE_OPENCL:
            {
                return std::string{ SIXTRL_ARCHITECTURE_OPENCL_STR };
            }

            case st::ARCHITECTURE_CUDA:
            {
                return std::string{ SIXTRL_ARCHITECTURE_CUDA_STR };
            }

            case st::ARCHITECTURE_CUDA_NVRTC:
            {
                return std::string{ SIXTRL_ARCHITECTURE_CUDA_NVRTC_STR };
            }

            case st::ARCHITECTURE_OPENMP:
            {
                return std::string{ SIXTRL_ARCHITECTURE_OPENMP_STR };
            }

            default:
            {
                SIXTRL_ASSERT( !arch_t::IS_PREDEFINED_ARCHITECTURE( arch_id ) );
            }
        };

        return std::string{};
    }

    st_size_t arch_t::REQUIRED_STR_BUFFER_CAPACITY_FOR_PREDEFINED_ARCHITECTURE(
        st_arch_id_t const arch_id )
    {
        std::string const temp(
            arch_t::PREDEFINED_ARCHITECTURE_ID_TO_STR( arch_id ) );

        return temp.size() + st_size_t{ 1 };
    }

    st_status_t arch_t::PREDEFINED_ARCHITECTURE_ID_TO_STR(
        char* SIXTRL_RESTRICT out_buffer,
        st_size_t const out_buffer_capacity,
        st_arch_id_t const arch_id ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( out_buffer != nullptr ) &&
            ( out_buffer_capacity > st_size_t{ 1 } ) )
        {
            std::string const temp(
                arch_t::PREDEFINED_ARCHITECTURE_ID_TO_STR( arch_id ) );

            if( temp.size() < out_buffer_capacity )
            {
                std::fill( out_buffer, out_buffer + out_buffer_capacity,
                           '\0' );
                std::strncpy( out_buffer, temp.c_str(),
                              out_buffer_capacity - st_size_t{ 1 } );

                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    arch_t::Architecture( st_arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF arch_name_str,
        state_flags_t const state_flags, init_arch_fn_t init_arch_fn,
        shutdown_arch_fn_t shutdown_arch_fn ) :
        BaseArchObj( arch_id, SIXTRL_CXX_NAMESPACE::CLASS_ID_ARCHITECTURE ),
        m_arch_str(), m_init_fn( init_arch_fn ),
        m_shutdown_fn( shutdown_arch_fn ),
        #if defined( _POSIX_VERSION )
        m_plugin_handle( nullptr ),
        #elif defined( __WIN32__ ) || defined( _WIN32 )
        m_plugin_handle( nullptr ),
        #endif /* Win32 */
        m_state_flags( state_flags )
    {

    }

    arch_t::~Architecture() {
        if( ( this->m_shutdown_fn != nullptr ) && ( this->is_activated() ) )
        {
            this->m_shutdown_fn( this->arch_id(), this );
        }
    }

    st_status_t arch_t::update_undefined_arch_id(
        st_arch_id_t const arch_id ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
            ( arch_id != st::ARCHITECTURE_UNDEFINED ) &&
            ( this->arch_id() == st::ARCHITECTURE_UNDEFINED ) )
        {
            status = this->set_arch_id( arch_id );
        }

        return status;
    }

    st_status_t arch_t::update_undefined_arch_id_detailed(
        st_arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF arch_str )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
            ( arch_id != st::ARCHITECTURE_UNDEFINED ) &&
            ( this->arch_id() == st::ARCHITECTURE_UNDEFINED ) )
        {
            status = this->set_arch_id( arch_id );
            if( status == st::STATUS_SUCCESS )
            {
                this->m_arch_str = arch_str;
            }
        }

        return status;
    }

    bool arch_t::has_plugin_handle() const SIXTRL_NOEXCEPT
    {
        #if defined( _POSIX_VERSION )
        return ( this->m_plugin_handle != nullptr );
        #elif defined( __WIN32__ ) || defined( _WIN32 )
        return ( this->m_plugin_handle != nullptr );
        #else
        return false;
        #endif /* defined( _POSIX_VERSIO#freN ) */
    }

    arch_t::plugin_handle_t arch_t::plugin_handle() SIXTRL_NOEXCEPT
    {
        return this->m_plugin_handle;
    }

    bool arch_t::is_enabled() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_state_flags != st::ARCH_STATE_NONE ) &&
                 ( this->m_state_flags != st::ARCH_STATE_ERROR ) &&
                 ( this->m_state_flags &  st::ARCH_STATE_ENABLED ) ==
                   this->m_state_flags );
    }

    bool arch_t::is_activated() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_state_flags != st::ARCH_STATE_NONE ) &&
                 ( this->m_state_flags != st::ARCH_STATE_ERROR ) &&
                 ( this->m_state_flags &  st::ARCH_STATE_ACTIVATED ) ==
                   this->m_state_flags );
    }

    bool arch_t::is_available() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_state_flags != st::ARCH_STATE_NONE ) &&
                 ( this->m_state_flags != st::ARCH_STATE_ERROR ) &&
                 ( this->m_state_flags &  st::ARCH_STATE_AVAILABLE ) ==
                   this->m_state_flags );
    }

    bool arch_t::is_shutdown() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_state_flags != st::ARCH_STATE_NONE ) &&
                 ( this->m_state_flags != st::ARCH_STATE_ERROR ) &&
                 ( this->m_state_flags &  st::ARCH_STATE_SHUTDOWN ) ==
                   this->m_state_flags );
    }

    st_status_t arch_t::initialize()
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        if( ( this->m_init_fn != nullptr ) &&
            ( this->m_state_flags == st::ARCH_STATE_ENABLED ) )
        {
            arch_t::state_flags_t const new_flags =
                this->m_init_fn( this->arch_id(), this );

            if( new_flags != st::ARCH_STATE_ERROR )
            {
                this->m_state_flags = new_flags;
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    st_status_t arch_t::shutdown()
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        if( this->m_shutdown_fn != nullptr )
        {
            arch_t::state_flags_t const new_flags =
                this->m_shutdown_fn( this->arch_id(), this );

            if( new_flags != st::ARCH_STATE_ERROR )
            {
                this->m_state_flags = new_flags;
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    st_status_t arch_t::set_init_arch_fn( arch_t::init_arch_fn_t init_arch_fn )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->m_state_flags == ::NS(ARCH_STATE_NONE) ) ||
            ( this->m_state_flags == ::NS(ARCH_STATE_ENABLED) ) )
        {
            this->m_init_fn = init_arch_fn;
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    st_status_t arch_t::set_shutdown_arch_fn(
        arch_t::shutdown_arch_fn_t shutdown_arch_fn )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->m_state_flags == ::NS(ARCH_STATE_NONE) ) ||
            ( this->m_state_flags == ::NS(ARCH_STATE_ENABLED) ) )
        {
            this->m_shutdown_fn = shutdown_arch_fn;
            status = st::STATUS_SUCCESS;
        }

        return status;
    }
}
#endif /* C++, Host */
