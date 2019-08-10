#ifndef SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_STORE_CXX_HPP__
#define SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_STORE_CXX_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/kernel_config_key.hpp"
    #include "sixtracklib/common/control/kernel_config_store.hpp"
    #include "sixtracklib/cuda/control/kernel_config.hpp"
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class CudaKernelConfigStore :
        public SIXTRL_CXX_NAMESPACE::KernelConfigStore
    {
        private:

        using _base_config_store_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;

        public:

        using kernel_config_t = SIXTRL_CXX_NAMESPACE::CudaKernelConfig;

        SIXTRL_HOST_FN  CudaKernelConfigStore() = default;

        SIXTRL_HOST_FN CudaKernelConfigStore(
            CudaKernelConfigStore const& SIXTRL_RESTRICT_REF store ) = default;

        SIXTRL_HOST_FN CudaKernelConfigStore(
            CudaKernelConfigStore&& store ) = default;

        SIXTRL_HOST_FN CudaKernelConfigStore& operator=(
            CudaKernelConfigStore const& SIXTRL_RESTRICT_REF rhs ) = default;

        SIXTRL_HOST_FN CudaKernelConfigStore& operator=(
            CudaKernelConfigStore&& rhs ) = default;

        SIXTRL_HOST_FN virtual ~CudaKernelConfigStore() = default;

        /* ----------------------------------------------------------------- */

        template< typename Args... >
        SIXTRL_HOST_FN kernel_config_t const*
        ptrKernelConfig( Args&&... args ) const;

        template< typename Args... >
        SIXTRL_HOST_FN kernel_config_t* ptrKernelConfig( Args&&... args );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< typename Args... >
        SIXTRL_HOST_FN kernel_config_t const* ptrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_RESTRICT_REF;

        template< typename Args... >
        SIXTRL_HOST_FN kernel_config_t* ptrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args )  SIXTRL_RESTRICT_REF;

        /* ----------------------------------------------------------------- */

        protected:

        SIXTRL_HOST_FN virtual kernel_id_t doInitKernelConfig(
            lock_t cont& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args,
            char const* SIXTRL_RESTRICT name ) override;

        SIXTRL_HOST_FN virtual kernel_id_t doAddKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            ptr_kernel_config_t&& ptr_kernel_config ) override;

        SIXTRL_HOST_FN virtual status_t doConfigureRemapBufferKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id );

        SIXTRL_HOST_FN virtual status_t doConfigureTrackKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            c_buffer_t const* SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            size_type const total_num_particles_in_sets ) override;

        SIXTRL_HOST_FN virtual status_t
        doConfigureFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            size_type const num_objs_in_particle_buffer ) override;

        SIXTRL_HOST_FN virtual status_t
        doConfigureAssignOutputBeamMonitorKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            size_type const num_beam_monitors ) override;

        SIXTRL_HOST_FN virtual status_t
        doConfigureAssignOutputElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id ) override;

        private:

        SIXTRL_HOST_FN status_t doInitDefaultKernelConfigInitParams(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key );
    };

    CudaKernelConfigStore& CudaKernelConfigStore_get();
    CudaKernelConfigStore const& CudaKernelConfigStore_get_const();

    CudaKernelConfigStore* CudaKernelConfigStore_get_ptr();
    const CudaKernelConfigStore *const CudaKernelConfigStore_get_ptr_const();
}

extern "C" {

using SIXTRL_CXX_NAMESPACE::CudaKernelConfigStore   NS(CudaKernelConfigStore);

}

#else /* C++ Host */

typedef void NS(CudaKernelConfigStore);

#endif /* C++ Host */



#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE CudaKernelConfigStore& CudaKernelConfigStore_get()
    {
        static CudaKernelConfigStore store;
        return store;
    }

    SIXTRL_INLINE CudaKernelConfigStore const&
        CudaKernelConfigStore_get_const()
    {
        return SIXTRL_CXX_NAMESPACE::CudaKernelConfigStore_get();
    }

    SIXTRL_INLINE CudaKernelConfigStore* CudaKernelConfigStore_get_ptr()
    {
        return &SIXTRL_CXX_NAMESPACE::CudaKernelConfigStore_get();
    }

    SIXTRL_INLINE const CudaKernelConfigStore *const
        CudaKernelConfigStore_get_ptr_const()
    {
        return SIXTRL_CXX_NAMESPACE::CudaKernelConfigStore_get_ptr();
    }

    /* --------------------------------------------------------------------- */


    template< typename Args... >
    CudaKernelConfigStore::kernel_config_t const*
    CudaKernelConfigStore::ptrKernelConfig( Args&&... args ) const
    {
        CudaKernelConfigStore::lock_t lock( *this->lockable() );
        return this->ptrKernelConfig( lock, std::forward< Args >( args )... );
    }

    template< typename Args... >
    CudaKernelConfigStore::kernel_config_t*
    CudaKernelConfigStore::ptrKernelConfig( Args&&... args )
    {
        CudaKernelConfigStore::lock_t lock( *this->lockable() );
        return this->ptrKernelConfig( lock, std::forward< Args >( args )... );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< typename Args... >
    CudaKernelConfigStore::kernel_config_t const*
    CudaKernelConfigStore::ptrKernelConfig(
        CudaKernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args ) const SIXTRL_RESTRICT_REF
    {
        using _this_t = CudaKernelConfigStore;

        _this_t::kernel_config_base_t const* ptr_base =
            this->ptrKernelConfigBase( lock, std::forward< Args >( args )... );

        return ( ptr_base != nullptr )
            ? ptr_base->asDerivedKernelConfig< _this_t::kernel_config_t >(
                st::ARCHITECTURE_CUDA ) : nullptr;
    }

    template< typename Args... >
    CudaKernelConfigStore::kernel_config_t*
    CudaKernelConfigStore::ptrKernelConfig(
        CudaKernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args )  SIXTRL_RESTRICT_REF
    {
        using _this_t = CudaKernelConfigStore;

        _this_t::kernel_config_base_t* ptr_base =
            this->ptrKernelConfigBase( lock, std::forward< Args >( args )... );

        return ( ptr_base != nullptr )
            ? ptr_base->asDerivedKernelConfig< _this_t::kernel_config_t >(
                st::ARCHITECTURE_CUDA ) : nullptr;
    }
}

#endif /* C++ Host */

#endif /* SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_STORE_CXX_HPP__ */

/* end: sixtracklib/cuda/control/kernel_config_store.hpp */
