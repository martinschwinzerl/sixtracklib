#include "sixtracklib/testlib/common/control/controller_base.hpp"

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/controller_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        using _this_t = st::tests::TestControllerBase;

        TestControllerBase::TestControllerBase(
            _this_t::arch_id_t const arch_id,
            _this_t::kernel_config_store_base_t*
                SIXTRL_RESTRICT ptr_kernel_config_store,
            _this_t::kernel_set_id_t const kernel_set_id,
            char const* SIXTRL_RESTRICT config_str ) : st::ControllerBase(
                arch_id, ptr_kernel_config_store, kernel_set_id, config_str )
        {
            if( this->ptrKernelConfigStore() != nullptr )
            {
                _this_t::kernel_lock_t const lock( *this->kernelLockable() );

                _this_t::status_t const status =
                    this->doInitTestControllerBase( lock );

                SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
                ( void )status;
            }
        }

        TestControllerBase::TestControllerBase(
            _this_t::arch_id_t const arch_id,
            _this_t::ptr_kernel_config_store_t&& kernel_config_store,
            _this_t::kernel_set_id_t const kernel_set_id,
            char const* SIXTRL_RESTRICT config_str ) : st::ControllerBase(
                arch_id, std::move( kernel_config_store ),
                    kernel_set_id, config_str )
        {
            if( this->ptrKernelConfigStore() != nullptr )
            {
                _this_t::kernel_lock_t const lock( *this->kernelLockable() );

                _this_t::status_t const status =
                    this->doInitTestControllerBase( lock );

                SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
                ( void )status;
            }
        }

        TestControllerBase::TestControllerBase(
            _this_t::kernel_lock_t& SIXTRL_RESTRICT_REF lock,
            _this_t::arch_id_t const arch_id,
            _this_t::kernel_config_store_base_t*
                SIXTRL_RESTRICT ptr_kernel_config_store,
            _this_t::kernel_set_id_t const kernel_set_id,
            char const* SIXTRL_RESTRICT config_str ) : st::ControllerBase(
                lock, arch_id, ptr_kernel_config_store, kernel_set_id,
                    config_str )
        {
            _this_t::status_t const status =
                this->doInitTestControllerBase( lock );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        TestControllerBase::TestControllerBase(
            _this_t::kernel_lock_t& SIXTRL_RESTRICT_REF lock,
            _this_t::arch_id_t const arch_id,
            _this_t::ptr_kernel_config_store_t&& kernel_config_store,
            _this_t::kernel_set_id_t const kernel_set_id,
            char const* SIXTRL_RESTRICT config_str ) : st::ControllerBase(
                lock, arch_id, std::move( kernel_config_store ),
                    kernel_set_id, config_str )
        {
            _this_t::status_t const status =
                this->doInitTestControllerBase( lock );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        _this_t::status_t TestControllerBase::doSyncWithKernelSet(
            _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
        {
            _this_t::status_t status =
                st::ControllerBase::doSyncWithKernelSet( lock );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( _this_t::AreOpFlagsSet( this->doGetKernelOpFlags(),
                    st::KERNEL_OP_HAS_ALL_REQUIRED_PURPOSES |
                    st::KERNEL_OP_ALL_REQUIRED_KERNELS_AVAILABLE |
                    st::KERNEL_OP_ALL_REQUIRED_KERNELS_READY ) ) )
            {
                this->doSetReadyForSendFlag( true );
                this->doSetReadyForReceiveFlag( true );
            }

            return status;
        }

        _this_t::status_t TestControllerBase::doInitTestControllerBase(
            _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
        {
            _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( this->ptrKernelConfigStore() != nullptr ) &&
                ( this->checkKernelLock( lock ) ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
                _this_t::kernel_set_id_t kset_id = this->kernelSetId( lock );

                if( kset_id == _this_t::ILLEGAL_KERNEL_SET_ID )
                {
                    status = st::ControllerBase::doCreateKernelSet( lock );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        kset_id = this->kernelSetId( lock );
                    }
                }

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( kset_id != _this_t::ILLEGAL_KERNEL_SET_ID ) )
                {
                    status = this->doFetchOpFlagsAndSyncIdFromKernelSet(
                        lock, kset_id );
                }
            }

            return status;
        }
    }
}

#endif /* C++, Host */

/* end: tests/sixtracklib/testlib/common/control/controller_base.cpp */
