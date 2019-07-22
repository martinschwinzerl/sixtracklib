#ifndef SIXTRACKLIB_COMMON_CONTROL_CONTROLLER_BASE_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_CONTROLLER_BASE_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <cstdio>
    #include <stdexcept>
    #include <ostream>
    #include <string>
    #include <sstream>
    #include <memory>
    #include <tuple>
    #include <unordered_set>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/arch_base.h"
    #include "sixtracklib/common/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/buffer.hpp"
    #include "sixtracklib/common/control/arch_base.hpp"
    #include "sixtracklib/common/control/kernel_config_key.hpp"
    #include "sixtracklib/common/control/kernel_config_base.hpp"
    #include "sixtracklib/common/control/kernel_config_store.hpp"
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class ArgumentBase;

    class ControllerBase : public SIXTRL_CXX_NAMESPACE::ArchDebugBase
    {
        private:

        using _base_arch_obj_t = SIXTRL_CXX_NAMESPACE::ArchDebugBase;

        public:

        using arch_id_t            = _base_arch_obj_t::arch_id_t;
        using status_t             = _base_arch_obj_t::status_t;
        using debug_register_t     = _base_arch_obj_t::debug_register_t;
        using buffer_t             = SIXTRL_CXX_NAMESPACE::Buffer;

        using c_buffer_t           = buffer_t::c_api_t;
        using size_type            = buffer_t::size_type;
        using kernel_config_base_t = SIXTRL_CXX_NAMESPACE::KernelConfigBase;
        using kernel_id_t          = kernel_config_base_t::kernel_id_t;
        using kernel_config_key_t  = kernel_config_base_t::key_t;
        using kernel_purpose_t     = kernel_config_base_t::purpose_t;

        using arg_base_ref_t       = ArgumentBase&;
        using ptr_arg_base_t       = ArgumentBase*;
        using ptr_const_arg_base_t = ArgumentBase const*;

        using ptr_kernel_conf_base_t =
            std::unique_ptr< kernel_config_base_t >;

        using perform_remap_flag_t =
            SIXTRL_CXX_NAMESPACE::ctrl_perform_remap_flag_t;

        using kernel_config_store_base_t =
            SIXTRL_CXX_NAMESPACE::KernelConfigStore;

        /* ----------------------------------------------------------------- */

        static SIXTRL_CONSTEXPR_OR_CONST arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static SIXTRL_CONSTEXPR_OR_CONST arch_id_t NO_ARCH_ID =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_NONE;

        static SIXTRL_CONSTEXPR_OR_CONST kernel_id_t ILLEGAL_KERNEL_ID =
            SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_KERNEL_ID;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool usesNodes() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN void clear();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasName() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& name() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrNameStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setName(
            std::string const& SIXTRL_RESTRICT_REF name );

        SIXTRL_HOST_FN void setName( char const* SIXTRL_RESTRICT name );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasDefaultKernelConfigStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const&
            defaultKernelConfigStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN char const*
            ptrDefaultKernelConfigStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setDefaultKernelConfigStr(
            std::string const& SIXTRL_RESTRICT_REF default_kernel_config_str );

        SIXTRL_HOST_FN void setDefaultKernelConfigStr(
            char const* SIXTRL_RESTRICT default_kernel_config_str );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool readyForRunningKernel() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool readyForSend()          const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool readyForReceive()       const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool readyForRemap()         const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t send( ptr_arg_base_t SIXTRL_RESTRICT dest,
            void const* SIXTRL_RESTRICT source, size_type const src_length );

        SIXTRL_HOST_FN status_t send( ptr_arg_base_t SIXTRL_RESTRICT dest,
            const c_buffer_t *const SIXTRL_RESTRICT source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_REMAP );

        SIXTRL_HOST_FN status_t send( ptr_arg_base_t SIXTRL_RESTRICT dest,
            buffer_t const& SIXTRL_RESTRICT_REF source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_REMAP );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t receive( void* SIXTRL_RESTRICT destination,
            size_type const destination_capacity,
            ptr_arg_base_t SIXTRL_RESTRICT source );

        SIXTRL_HOST_FN status_t receive( c_buffer_t* SIXTRL_RESTRICT dest,
            ptr_arg_base_t SIXTRL_RESTRICT source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_REMAP );

        SIXTRL_HOST_FN status_t receive( buffer_t& SIXTRL_RESTRICT_REF dest,
            ptr_arg_base_t SIXTRL_RESTRICT source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_REMAP );

        /* ================================================================= */

        SIXTRL_HOST_FN size_type numKernels() const;
        SIXTRL_HOST_FN size_type numKeys( kernel_id_t const kernel_id ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< typename... Args >
        SIXTRL_HOST_FN bool hasKernel( Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN kernel_id_t kernelId( Args&&... args ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< typename... Args >
        SIXTRL_HOST_FN kernel_config_base_t const*
        ptrKernelConfigBase( Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN kernel_config_base_t*
        ptrKernelConfigBase( Args&&... args );

        SIXTRL_HOST_FN kernel_config_base_t const* ptrKernelConfigBase(
            kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_base_t* ptrKernelConfigBase(
            kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN kernel_id_t addKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            ptr_kernel_conf_base_t&& ptr_kernel_config );

        SIXTRL_HOST_FN status_t addKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            kernel_id_t const kernel_config_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasRemapBufferKernel() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_id_t
        remapBufferKernelConfigId() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_key_t const&
        remapBufferKernelConfigKey() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool kernelHasName(
            kernel_id_t const id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const& kernelName(
            kernel_id_t const kernel_id ) const;

        SIXTRL_HOST_FN char const* ptrKernelNameStr(
            kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT;

        /* ================================================================= */

        SIXTRL_HOST_FN status_t remap( ptr_arg_base_t SIXTRL_RESTRICT arg );

        SIXTRL_HOST_FN status_t remap(
            arg_base_ref_t SIXTRL_RESTRICT_REF arg );

        SIXTRL_HOST_FN bool isRemapped( ptr_arg_base_t SIXTRL_RESTRICT arg );

        SIXTRL_HOST_FN bool isRemapped(
            arg_base_ref_t SIXTRL_RESTRICT_REF arg );

        /* ================================================================= */

        SIXTRL_HOST_FN status_t setActiveVariantFlags( variant_t const var );

        /* ================================================================= */

        SIXTRL_HOST_FN void print(
            std::ostream& SIXTRL_RESTRICT_REF output ) const;

        SIXTRL_HOST_FN void print(
            ::FILE* SIXTRL_RESTRICT output ) const;

        SIXTRL_HOST_FN void printOut() const;

        /* ================================================================= */

        SIXTRL_HOST_FN virtual ~ControllerBase() = default;

        template< class Derived >
        SIXTRL_HOST_FN Derived const* asDerivedController(
            arch_id_t const requ_arch_id,
            bool const exact_match_required = false ) const SIXTRL_NOEXCEPT;

        template< class Derived >
        SIXTRL_HOST_FN Derived* asDerivedController(
            arch_id_t const requ_arch_id,
            bool const exact_match_required = false ) SIXTRL_NOEXCEPT;

        /* ================================================================= */

        SIXTRL_HOST_FN kernel_config_store_base_t const&
        kernelConfigStore() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_store_base_t&
        kernelConfigStore() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_store_base_t const*
        ptrKernelConfigStore() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_store_base_t*
        ptrKernelConfigStore() SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN explicit ControllerBase(
            arch_id_t const arch_id,
            const char *const SIXTRL_RESTRICT arch_str,
            kernel_config_store_base_t& SIXTRL_RESTRICT_REF kernel_config_store,
            const char *const SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN ControllerBase( ControllerBase const& other ) = default;
        SIXTRL_HOST_FN ControllerBase( ControllerBase&& other ) = default;

        SIXTRL_HOST_FN ControllerBase&
        operator=( ControllerBase const& rhs ) = default;

        SIXTRL_HOST_FN ControllerBase&
        operator=( ControllerBase&& rhs ) = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual void doClear();

        SIXTRL_HOST_FN virtual status_t doChangeVariantFlags(
            variant_t const new_variant_flags ) override;

        SIXTRL_HOST_FN virtual status_t doSelectKernelConfigByKey(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF new_key,
            kernel_id_t* SIXTRL_RESTRICT ptr_kernel_id_to_change,
            kernel_config_key_t* SIXTRL_RESTRICT ptr_key_to_change );

        SIXTRL_HOST_FN virtual status_t doUnselectKernelConfig(
            kernel_id_t& SIXTRL_RESTRICT_REF kernel_id_to_unselect,
            kernel_config_key_t* SIXTRL_RESTRICT ptr_key_to_unselect );

        SIXTRL_HOST_FN virtual bool doCheckAreKernelConfigsInitialized(
            kernel_config_key_t& SIXTRL_RESTRICT_REF input_key ) const;

        SIXTRL_HOST_FN virtual status_t doInitializeKernelConfigs(
            kernel_config_key_t& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN virtual status_t doSend(
            ptr_arg_base_t SIXTRL_RESTRICT destination,
            const void *const SIXTRL_RESTRICT source,
            size_type const source_length );

        SIXTRL_HOST_FN virtual status_t doReceive(
            void* SIXTRL_RESTRICT destination, size_type const dest_capacity,
            ptr_arg_base_t SIXTRL_RESTRICT source );

        SIXTRL_HOST_FN virtual status_t doRemapCObjectsBufferArg(
            ptr_arg_base_t SIXTRL_RESTRICT arg );

        SIXTRL_HOST_FN virtual bool doIsCObjectsBufferArgRemapped(
            ptr_arg_base_t SIXTRL_RESTRICT arg,
            status_t* SIXTRL_RESTRICT ptr_status );

        SIXTRL_HOST_FN virtual status_t doPrintToOutputStream(
            std::ostream& SIXTRL_RESTRICT_REF output ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool doPreflightCheckSelectKernelConfigByKey(
            ControllerBase::kernel_config_key_t const&
                SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN  bool doCheckSelectKernelConfigByKeyOk(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            kernel_config_base_t const* SIXTRL_RESTRICT ptr_conf ) const;

        SIXTRL_HOST_FN kernel_config_key_t*
        doGetPtrRemapBufferKernelConfigKey() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_id_t*
        doGetPtrRemapBufferKernelConfigId() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doSelectRemapBufferKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN status_t doSetRemapBufferKernelConfigKey(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN status_t doSetRemapBufferKernelConfigId(
            kernel_id_t const kernel_config_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t doUpdateKernelConfigStore(
            kernel_config_store_base_t& SIXTRL_RESTRICT_REF store );

        SIXTRL_HOST_FN void doSetUsesNodesFlag(
            bool const flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetReadyForRunningKernelsFlag(
            bool const flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetReadyForSendFlag(
            bool const flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetReadyForReceiveFlag(
            bool const flag ) SIXTRL_NOEXCEPT;

        private:

        kernel_config_key_t         m_remap_kernel_key;
        std::string                 m_name;
        std::string                 m_default_kernel_config_str;
        kernel_config_store_base_t& m_kernel_config_store;
        size_type                   m_num_kernels;
        kernel_id_t                 m_remap_kernel_id;

        bool                        m_uses_nodes;
        bool                        m_ready_for_running_kernels;
        bool                        m_ready_for_send;
        bool                        m_ready_for_receive;
    };

    SIXTRL_HOST_FN std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF output,
            ControllerBase const& SIXTRL_RESTRICT_REF ctrl );
}
#endif /* C++, host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

typedef SIXTRL_CXX_NAMESPACE::ControllerBase NS(ControllerBase);

#else /* C++, host */

typedef void NS(ControllerBase);

#endif /* C++, host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE bool ControllerBase::usesNodes() const SIXTRL_NOEXCEPT
    {
        return this->m_uses_nodes;
    }

    SIXTRL_INLINE void ControllerBase::clear()
    {
        this->doClear();
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool ControllerBase::hasName() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_name.empty() );
    }

    SIXTRL_INLINE std::string const&
    ControllerBase::name() const SIXTRL_NOEXCEPT
    {
        return this->m_name;
    }

    SIXTRL_INLINE char const*
    ControllerBase::ptrNameStr() const SIXTRL_NOEXCEPT
    {
        return ( this->hasName() ) ? this->m_name.c_str() : nullptr;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    ControllerBase::hasDefaultKernelConfigStr() const SIXTRL_NOEXCEPT
    {
        return !this->m_default_kernel_config_str.empty();
    }

    SIXTRL_INLINE std::string const&
    ControllerBase::defaultKernelConfigStr() const SIXTRL_NOEXCEPT
    {
        return this->m_default_kernel_config_str;
    }

    SIXTRL_INLINE char const*
    ControllerBase::ptrDefaultKernelConfigStr() const SIXTRL_NOEXCEPT
    {
        return ( this->hasDefaultKernelConfigStr() )
            ? this->m_default_kernel_config_str.c_str() : nullptr;
    }

    SIXTRL_INLINE void ControllerBase::setDefaultKernelConfigStr(
            std::string const& SIXTRL_RESTRICT_REF kernel_config_str )
    {
        this->m_default_kernel_config_str = kernel_config_str;
    }

    SIXTRL_INLINE void ControllerBase::setDefaultKernelConfigStr(
        char const* SIXTRL_RESTRICT kernel_config_str )
    {
        if( ( kernel_config_str != nullptr ) &&
            ( std::strlen( kernel_config_str ) >
                ControllerBase::size_type{ 0 } ) )
        {
            this->m_default_kernel_config_str = kernel_config_str;
        }
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool ControllerBase::readyForSend() const SIXTRL_NOEXCEPT
    {
        return this->m_ready_for_send;
    }

    SIXTRL_INLINE bool ControllerBase::readyForReceive() const SIXTRL_NOEXCEPT
    {
        return this->m_ready_for_receive;
    }

    SIXTRL_INLINE bool
    ControllerBase::readyForRunningKernel() const SIXTRL_NOEXCEPT
    {
        return this->m_ready_for_running_kernels;
    }

    SIXTRL_INLINE bool ControllerBase::readyForRemap() const SIXTRL_NOEXCEPT
    {
        return ( ( this->readyForRunningKernel() ) &&
                 ( this->hasRemapBufferKernel() ) );
    }

    /* --------------------------------------------------------------------- */

    template< typename... Args >
    bool ControllerBase::hasKernel( Args&&... args ) const
    {
        return this->kernelConfigStore().hasKernel(
            std::forward< Args >( args )... );
    }

    template< typename... Args >
    ControllerBase::kernel_id_t ControllerBase::kernelId( Args&&... args ) const
    {
        return this->kernelConfigStore().kernelId(
            std::forward< Args >( args )... );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE ControllerBase::kernel_id_t ControllerBase::addKernelConfig(
        ControllerBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        ControllerBase::ptr_kernel_conf_base_t&& ptr_kernel_config )
    {
        return this->kernelConfigStore().addKernelConfig(
            key, std::move( ptr_kernel_config ) );
    }

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::addKernelConfig(
        ControllerBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        ControllerBase::kernel_id_t const kernel_config_id )
    {
        return this->kernelConfigStore().addKernelConfig(
            key, kernel_config_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool ControllerBase::isRemapped(
        ControllerBase::arg_base_ref_t SIXTRL_RESTRICT_REF arg )
    {
        return this->isRemapped( &arg );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE ControllerBase::size_type
    ControllerBase::numKernels() const
    {
        return this->kernelConfigStore().numStoredKernels();
    }

    SIXTRL_INLINE ControllerBase::size_type ControllerBase::numKeys(
        ControllerBase::kernel_id_t const kernel_id ) const
    {
        return this->kernelConfigStore().numKeys( kernel_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    ControllerBase::hasRemapBufferKernel() const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;

        _this_t::kernel_config_key_t const& key =
            this->remapBufferKernelConfigKey();

        _this_t::kernel_id_t const kernel_config_id =
            this->remapBufferKernelConfigId();

        return ( ( key.valid() ) && ( key.purpose() ==
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER ) &&
            ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE ControllerBase::kernel_id_t
    ControllerBase::remapBufferKernelConfigId() const SIXTRL_NOEXCEPT
    {
        return this->m_remap_kernel_id;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE ControllerBase::kernel_config_key_t const&
        ControllerBase::remapBufferKernelConfigKey() const SIXTRL_NOEXCEPT
    {
        return this->m_remap_kernel_key;
    }

    /* --------------------------------------------------------------------- */

    template< typename... Args >
    ControllerBase::kernel_config_base_t const*
    ControllerBase::ptrKernelConfigBase( Args&&... args ) const
    {
        return this->kernelConfigStore().ptrKernelConfigBase(
            std::forward< Args >( args )... );
    }

    template< typename... Args >
    ControllerBase::kernel_config_base_t*
    ControllerBase::ptrKernelConfigBase( Args&&... args )
    {
        return this->kernelConfigStore().ptrKernelConfigBase(
            std::forward< Args >( args )... );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE ControllerBase::kernel_config_base_t const*
    ControllerBase::ptrKernelConfigBase(
        ControllerBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        return this->kernelConfigStore().ptrKernelConfigBase( kernel_id );
    }

    SIXTRL_INLINE ControllerBase::kernel_config_base_t*
    ControllerBase::ptrKernelConfigBase(
        ControllerBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        return this->kernelConfigStore().ptrKernelConfigBase( kernel_id );
    }

    /* ===================================================================== */

    SIXTRL_INLINE ControllerBase::status_t
    ControllerBase::setActiveVariantFlags(
        ControllerBase::variant_t const new_variant_flags )
    {
        return this->doChangeVariantFlags( new_variant_flags );
    }

    /* ===================================================================== */

    SIXTRL_INLINE void ControllerBase::print(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        this->doPrintToOutputStream( output );
    }

    SIXTRL_INLINE void ControllerBase::print(
        ::FILE* SIXTRL_RESTRICT output ) const
    {
        if( output != nullptr )
        {
            std::ostringstream a2str;
            this->print( a2str );

            std::string const temp_str( a2str.str() );
            int ret = std::fprintf( output, "%s", temp_str.c_str() );
            SIXTRL_ASSERT( ret > 0 );
            ( void )ret;
        }
    }

    SIXTRL_INLINE void ControllerBase::printOut() const
    {
        this->print( ::stdout );
    }

    SIXTRL_INLINE std::ostream& operator<<(
        std::ostream& SIXTRL_RESTRICT_REF output,
        SIXTRL_CXX_NAMESPACE::ControllerBase const& SIXTRL_RESTRICT_REF ctrl )
    {
        ctrl.print( output );
        return output;
    }

    /* ===================================================================== */

    template< class Derived > Derived const*
    ControllerBase::asDerivedController(
        ControllerBase::arch_id_t const requ_arch_id,
        bool const exact_match_required ) const SIXTRL_NOEXCEPT
    {
        Derived const* ptr_derived = nullptr;

        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;

        static_assert( std::is_base_of< _this_t, Derived >::value,
                       "asDerivedController< Derived > requires Dervied to be "
                       "derived from SIXTRL_CXX_NAMESPACE::ControllerBase" );

        if( ( ( !exact_match_required ) &&
              ( this->isArchCompatibleWith( requ_arch_id ) ) ) ||
            ( this->isArchIdenticalTo( requ_arch_id ) ) )
        {
            ptr_derived = static_cast< Derived const* >( this );
        }

        return ptr_derived;
    }

    template< class Derived > Derived* ControllerBase::asDerivedController(
        ControllerBase::arch_id_t const requ_arch_id,
        bool const exact_match_required ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;

        return const_cast< Derived* >( static_cast< _this_t const& >(
            *this ).asDerivedController< Derived >(
                requ_arch_id, exact_match_required ) );
    }

    /* ===================================================================== */

    SIXTRL_INLINE ControllerBase::kernel_config_store_base_t const&
    ControllerBase::kernelConfigStore() const SIXTRL_NOEXCEPT
    {
        return this->m_kernel_config_store;
    }

    SIXTRL_INLINE ControllerBase::kernel_config_store_base_t&
    ControllerBase::kernelConfigStore() SIXTRL_NOEXCEPT
    {
        return this->m_kernel_config_store;
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE ControllerBase::kernel_config_store_base_t const*
    ControllerBase::ptrKernelConfigStore() const SIXTRL_NOEXCEPT
    {
        return &this->m_kernel_config_store;
    }

    SIXTRL_INLINE ControllerBase::kernel_config_store_base_t*
    ControllerBase::ptrKernelConfigStore() SIXTRL_NOEXCEPT
    {
        return &this->m_kernel_config_store;
    }

    /* ===================================================================== */

    SIXTRL_INLINE ControllerBase::kernel_config_key_t*
    ControllerBase::doGetPtrRemapBufferKernelConfigKey() SIXTRL_NOEXCEPT
    {
        return &this->m_remap_kernel_key;
    }

    SIXTRL_INLINE ControllerBase::kernel_id_t*
    ControllerBase::doGetPtrRemapBufferKernelConfigId() SIXTRL_NOEXCEPT
    {
        return &this->m_remap_kernel_id;
    }

    SIXTRL_INLINE ControllerBase::status_t
    ControllerBase::doSelectRemapBufferKernelConfig(
        ControllerBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return ( key.purpose() == st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER )
            ? this->doSelectKernelConfigByKey( key,
                this->doGetPtrRemapBufferKernelConfigId(),
                this->doGetPtrRemapBufferKernelConfigKey() )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_CONTROLLER_BASE_HPP__ */

/* end: sixtracklib/common/control/controller_base.hpp */
