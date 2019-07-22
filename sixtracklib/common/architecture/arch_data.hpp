#ifndef SIXTRACKLIB_ARCHITECTURE_ARCH_DATA_CXX_HPP__
#define SIXTRACKLIB_ARCHITECTURE_ARCH_DATA_CXX_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <string>

    #if defined( __unix__ ) || ( defined( __APPLE__ ) && defined( __MACH__ ) )
        #include <unistd.h>
    #endif /* include unistd.h */

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

        using arch_id_t          = SIXTRL_CXX_NAMESPACE::arch_id_t;
        using status_t           = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using init_flags_t       = SIXTRL_CXX_NAMESPACE::arch_init_flags_t;

        #if defined( _POSIX_VERSION )
        using lib_handle_t       = void*;
        using const_lib_handle_t = void const*;
        #elif defined( __WIN32__ ) || defined( _WIN32 )
        using lib_handle_t       = ::HMODULE;
        using const_lib_handle_t = ::HMODULE const;
        #endif /* Select lib_handle_t type depending on OS/Environment */

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

        SIXTRL_HOST_FN ArchData( ArchData const& SIXTRL_RESTRICT_REF ) = default;

        SIXTRL_HOST_FN ArchData( ArchData&& ) = default;

        SIXTRL_HOST_FN ArchData& operator=(
            ArchData const& SIXTRL_RESTRICT_REF ) = default;

        SIXTRL_HOST_FN ArchData& operator=( ArchData&& ) = default;

        SIXTRL_HOST_FN virtual ~ArchData();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN arch_id_t archId() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasHandle() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN lib_handle_t libHandle() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setInitFlags(
            init_flags_t const init_flags_t ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isEnabled() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool isActivated() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool isAvailable() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool isShutdown() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN init_flags_t initFlags() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasArchStr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& archStr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrArchStr() const SIXTRL_NOEXCEPT;

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

typedef void NS(ArchData);

#endif /* C++, Host */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE bool ArchData::hasHandle() const SIXTRL_NOEXCEPT
    {
        #if defined( _POSIX_VERSION )
        return ( this->m_lib_handle != nullptr );
        #elif defined( __WIN32__ ) || defined( _WIN32 )
        return ( this->m_lib_handle != nullptr );
        #else
        return false;
        #endif /* defined( _POSIX_VERSION ) */
    }

    SIXTRL_INLINE ArchData::lib_handle_t ArchData::libHandle() SIXTRL_NOEXCEPT
    {
        return this->m_lib_handle;
    }

    SIXTRL_INLINE ArchData::status_t ArchData::setInitFlags(
        ArchData::init_flags_t const init_state ) SIXTRL_NOEXCEPT
    {
        this->m_init_state = init_state;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    SIXTRL_INLINE bool ArchData::isEnabled() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_init_state & ::NS(ARCH_INIT_STATE_ENABLED) ) ==
            this->m_init_state );
    }

    SIXTRL_INLINE bool ArchData::isActivated() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_init_state & ::NS(ARCH_INIT_STATE_ACTIVATED) ) ==
            this->m_init_state );
    }

    SIXTRL_INLINE bool ArchData::isAvailable() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_init_state & ::NS(ARCH_INIT_STATE_AVAILABLE) ) ==
            this->m_init_state );
    }

    SIXTRL_INLINE bool ArchData::isShutdown() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_init_state & ::NS(ARCH_INIT_STATE_SHUTDOWN) ) ==
            this->m_init_state );
    }

    SIXTRL_INLINE ArchData::init_flags_t
    ArchData::initFlags() const SIXTRL_NOEXCEPT
    {
        return this->m_init_state;
    }

    SIXTRL_INLINE bool ArchData::hasArchStr() const SIXTRL_NOEXCEPT
    {
        return !this->m_arch_name.empty();
    }

    SIXTRL_INLINE std::string const& ArchData::archStr() const SIXTRL_NOEXCEPT
    {
        return this->m_arch_name;
    }

    SIXTRL_INLINE char const* ArchData::ptrArchStr() const SIXTRL_NOEXCEPT
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
