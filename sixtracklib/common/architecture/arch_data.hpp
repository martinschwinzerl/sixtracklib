#ifndef SIXTRACKLIB_ARCHITECTURE_ARCH_DATA_CXX_HPP__
#define SIXTRACKLIB_ARCHITECTURE_ARCH_DATA_CXX_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <string>

#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/architecture/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if  defined( __cplusplus ) && !defined( _GPUCODE ) && \
    !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

namespace SIXTRL_CXX_NAMESPACE
{
    class ArchData
    {
        public:

        using arch_id_t          = ::NS(arch_id_t);
        using status_t           = ::NS(arch_status_t);
        using init_flags_t       = ::NS(arch_init_flags_t);
        using lib_handle_t       = ::NS(lib_handle_t);

        using init_arch_fn_t     = init_flags_t (*)( arch_id_t, ArchData* );
        using shutdown_arch_fn_t = init_flags_t (*)( arch_id_t, ArchData* );

        SIXTRL_HOST_FN ArchData(
            arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF arch_name_str,
            init_flags_t const init_falgs = ::NS(ARCH_INIT_STATE_NONE),
            init_arch_fn_t init_arch_fn = nullptr,
            shutdown_arch_fn_t shutdown_arch_fn = nullptr );

        SIXTRL_HOST_FN ArchData(
            arch_id_t const arch_id,
            char const* SIXTRL_RESTRICT arch_name_str,
            init_flags_t const init_falgs = ::NS(ARCH_INIT_STATE_NONE),
            init_arch_fn_t init_arch_fn = nullptr,
            shutdown_arch_fn_t shutdown_arch_fn = nullptr );

        SIXTRL_HOST_FN ArchData(
            ArchData const& SIXTRL_RESTRICT_REF ) = default;

        SIXTRL_HOST_FN ArchData( ArchData&& ) = default;

        SIXTRL_HOST_FN ArchData& operator=(
            ArchData const& SIXTRL_RESTRICT_REF ) = default;

        SIXTRL_HOST_FN ArchData& operator=( ArchData&& ) = default;

        SIXTRL_HOST_FN virtual ~ArchData();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN arch_id_t arch_id() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_handle() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN lib_handle_t lib_handle() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_init_flags(
            init_flags_t const init_flags_t ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_enabled() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_activated() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_available() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_shutdown() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN init_flags_t init_flags() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_architecture_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const&
            architecture_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN char const*
            ptr_architecture_cstr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t initialize();
        SIXTRL_HOST_FN status_t shutdown();

        /* ----------------------------------------------------------------- */

        protected:

        SIXTRL_HOST_FN status_t doSetInitArchFn(
            init_arch_fn_t init_arch_fn ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doSetShutdownArchFn(
            shutdown_arch_fn_t shutdown_arch_fn ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doSetArchStr(
            char const* SIXTRL_RESTRICT arch_str );

        private:

        std::string         m_arch_name;
        init_arch_fn_t      m_init_fn;
        shutdown_arch_fn_t  m_shutdown_fn;
        lib_handle_t        m_lib_handle;
        arch_id_t           m_arch_id;
        init_flags_t        m_init_state;
    };
}

typedef SIXTRL_CXX_NAMESPACE::ArchData NS(ArchData);

#else

struct NS(ArchData);
typedef struct NS(ArchData) NS(ArchData);

#endif /* C++, Host */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE ArchData::arch_id_t ArchData::arch_id() const SIXTRL_NOEXCEPT
    {
        return this->m_arch_id;
    }

    SIXTRL_INLINE bool ArchData::has_handle() const SIXTRL_NOEXCEPT
    {
        #if defined( _POSIX_VERSION )
        return ( this->m_lib_handle != nullptr );
        #elif defined( __WIN32__ ) || defined( _WIN32 )
        return ( this->m_lib_handle != nullptr );
        #else
        return false;
        #endif /* defined( _POSIX_VERSION ) */
    }

    SIXTRL_INLINE ArchData::lib_handle_t ArchData::lib_handle() SIXTRL_NOEXCEPT
    {
        return this->m_lib_handle;
    }

    SIXTRL_INLINE ArchData::status_t ArchData::set_init_flags(
        ArchData::init_flags_t const init_state ) SIXTRL_NOEXCEPT
    {
        this->m_init_state = init_state;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    SIXTRL_INLINE bool ArchData::is_enabled() const SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return ( ( this->m_init_state != st::ARCH_INIT_STATE_NONE ) &&
                 ( this->m_init_state != st::ARCH_INIT_STATE_ERROR ) &&
                 ( this->m_init_state &  st::ARCH_INIT_STATE_ENABLED ) ==
                   this->m_init_state );
    }

    SIXTRL_INLINE bool ArchData::is_activated() const SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return ( ( this->m_init_state != st::ARCH_INIT_STATE_NONE ) &&
                 ( this->m_init_state != st::ARCH_INIT_STATE_ERROR ) &&
                 ( this->m_init_state &  st::ARCH_INIT_STATE_ACTIVATED ) ==
                   this->m_init_state );
    }

    SIXTRL_INLINE bool ArchData::is_available() const SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return ( ( this->m_init_state != st::ARCH_INIT_STATE_NONE ) &&
                 ( this->m_init_state != st::ARCH_INIT_STATE_ERROR ) &&
                 ( this->m_init_state &  st::ARCH_INIT_STATE_AVAILABLE ) ==
                   this->m_init_state );
    }

    SIXTRL_INLINE bool ArchData::is_shutdown() const SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return ( ( this->m_init_state != st::ARCH_INIT_STATE_NONE ) &&
                 ( this->m_init_state != st::ARCH_INIT_STATE_ERROR ) &&
                 ( this->m_init_state &  st::ARCH_INIT_STATE_SHUTDOWN ) ==
                   this->m_init_state );
    }

    SIXTRL_INLINE ArchData::init_flags_t
    ArchData::init_flags() const SIXTRL_NOEXCEPT
    {
        return this->m_init_state;
    }

    SIXTRL_INLINE bool ArchData::has_architecture_str() const SIXTRL_NOEXCEPT
    {
        return !this->m_arch_name.empty();
    }

    SIXTRL_INLINE std::string const&
    ArchData::architecture_str() const SIXTRL_NOEXCEPT
    {
        return this->m_arch_name;
    }

    SIXTRL_INLINE char const*
    ArchData::ptr_architecture_cstr() const SIXTRL_NOEXCEPT
    {
        return this->m_arch_name.c_str();
    }

    SIXTRL_INLINE ArchData::status_t ArchData::doSetInitArchFn(
        ArchData::init_arch_fn_t init_arch_fn ) SIXTRL_NOEXCEPT
    {
        ArchData::status_t status = ::NS(ARCH_STATUS_GENERAL_FAILURE);

        if( ( this->m_init_state == ::NS(ARCH_INIT_STATE_NONE) ) &&
            ( this->m_init_state == ::NS(ARCH_INIT_STATE_ENABLED) ) )
        {
            this->m_init_fn = init_arch_fn;
            status = ::NS(ARCH_STATUS_SUCCESS);
        }

        return status;
    }

    SIXTRL_INLINE ArchData::status_t ArchData::doSetShutdownArchFn(
        ArchData::shutdown_arch_fn_t shutdown_arch_fn ) SIXTRL_NOEXCEPT
    {
        ArchData::status_t status = ::NS(ARCH_STATUS_GENERAL_FAILURE);

        if( ( this->m_init_state == ::NS(ARCH_INIT_STATE_NONE) ) &&
            ( this->m_init_state == ::NS(ARCH_INIT_STATE_ENABLED) ) )
        {
            this->m_shutdown_fn = shutdown_arch_fn;
            status = ::NS(ARCH_STATUS_SUCCESS);
        }

        return status;
    }
}

#endif /* C++, Host */


#endif /* SIXTRACKLIB_ARCHITECTURE_ARCH_DATA_CXX_HPP__ */

/* end: sixtracklib/common/architecture/arch_data.hpp */
