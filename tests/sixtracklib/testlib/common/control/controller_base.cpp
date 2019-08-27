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
                SIXTRL_RESTRICT ext_kernel_conf_store,
            _this_t::kernel_set_id_t const kernel_set_id,
            char const* SIXTRL_RESTRICT config_str ) :
                st::ControllerBase( arch_id, config_str )
        {
            if( ( ext_kernel_conf_store != nullptr ) &&
                ( ext_kernel_conf_store->lockable() != nullptr ) )
            {
                _this_t::kernel_lock_t const lock(
                    *ext_kernel_conf_store->lockable() );

                if( this->doInitTestControllerBase( lock, ext_kernel_conf_store,
                        kernel_set_id ) != st::ARCH_STATUS_SUCCESS )
                {
                    throw std::runtime_error(
                        "Unable to initialize TestControllerBase" );
                }
            }
        }

        TestControllerBase::TestControllerBase(
            _this_t::arch_id_t const arch_id,
            _this_t::ptr_kernel_config_store_t&& kernel_config_store,
            _this_t::kernel_set_id_t const kernel_set_id,
            char const* SIXTRL_RESTRICT config_str ) :
            st::ControllerBase( arch_id, config_str )
        {
            if( ( kernel_config_store.get() != nullptr ) &&
                ( kernel_config_store->lockable() != nullptr ) )
            {
                _this_t::kernel_lock_t const lock(
                    *kernel_config_store->lockable() );

                if( st::ARCH_STATUS_SUCCESS != this->doInitTestControllerBase(
                    lock, std::move( kernel_config_store ), kernel_set_id ) )
                {
                    throw std::runtime_error(
                        "Unable to initialize TestControllerBase" );
                }
            }
        }

        TestControllerBase::TestControllerBase(
            _this_t::kernel_lock_t& SIXTRL_RESTRICT_REF kernel_lock,
            _this_t::arch_id_t const arch_id,
            _this_t::kernel_config_store_base_t*
                SIXTRL_RESTRICT ext_kernel_conf_store,
            _this_t::kernel_set_id_t const kernel_set_id,
            char const* SIXTRL_RESTRICT config_str ) :
                st::ControllerBase( arch_id, config_str )
        {
            if( st::ARCH_STATUS_SUCCESS != this->doInitTestControllerBase(
                    kernel_lock, ext_kernel_conf_store, kernel_set_id ) )
            {
                throw std::runtime_error(
                        "Unable to initialize TestControllerBase" );
            }
        }

        TestControllerBase::TestControllerBase(
            _this_t::kernel_lock_t& SIXTRL_RESTRICT_REF kernel_lock,
            _this_t::arch_id_t const arch_id,
            _this_t::ptr_kernel_config_store_t&& kernel_config_store,
            _this_t::kernel_set_id_t const kernel_set_id,
            char const* SIXTRL_RESTRICT config_str ) :
                st::ControllerBase( arch_id, config_str )
        {
            if( st::ARCH_STATUS_SUCCESS != this->doInitTestControllerBase(
                    kernel_lock, std::move( kernel_config_store ),
                        kernel_set_id ) )
            {
                throw std::runtime_error(
                        "Unable to initialize TestControllerBase" );
            }
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
            _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            _this_t::kernel_config_store_base_t*
                SIXTRL_RESTRICT ext_kernel_conf_store,
            _this_t::kernel_set_id_t kernel_set_id )
        {
            _this_t::status_t status = this->doInitKernelConfigStore(
                kernel_lock, ext_kernel_conf_store );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                SIXTRL_ASSERT( ext_kernel_conf_store != nullptr );
                SIXTRL_ASSERT( ext_kernel_conf_store->checkLock( kernel_lock ) );

                if( kernel_set_id == _this_t::ILLEGAL_KERNEL_SET_ID )
                {
                    std::unique_ptr< _this_t::kernel_set_base_t > ptr_set(
                        new _this_t::kernel_set_t( kernel_lock, this->archId(),
                            *ext_kernel_conf_store ) );

                    kernel_set_id = ext_kernel_conf_store->addKernelSet(
                        kernel_lock, std::move( ptr_set ) );
                }

                if( ( kernel_set_id != _this_t::ILLEGAL_KERNEL_SET_ID ) &&
                    ( ext_kernel_conf_store->hasKernelSet(
                        kernel_lock, kernel_set_id ) ) )
                {
                    status = this->doInitKernelSet( kernel_lock, kernel_set_id );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        SIXTRL_ASSERT( kernel_set_id ==
                            this->kernelSetId( kernel_lock ) );

                        status = this->doFetchOpFlagsAndSyncIdFromKernelSet(
                            kernel_lock, kernel_set_id );
                    }
                }
                else
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }

            return status;
        }

        _this_t::status_t TestControllerBase::doInitTestControllerBase(
            _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            _this_t::ptr_kernel_config_store_t&& kernel_conf_store,
            _this_t::kernel_set_id_t kernel_set_id )
        {
            _this_t::status_t status = this->doInitKernelConfigStore(
                kernel_lock, std::move( kernel_conf_store ) );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                SIXTRL_ASSERT( kernel_conf_store.get() != nullptr );
                SIXTRL_ASSERT( kernel_conf_store->checkLock( kernel_lock ) );

                if( kernel_set_id == _this_t::ILLEGAL_KERNEL_SET_ID )
                {
                    std::unique_ptr< _this_t::kernel_set_base_t > ptr_set(
                        new _this_t::kernel_set_t( kernel_lock, this->archId(),
                            *kernel_conf_store ) );

                    kernel_set_id = kernel_conf_store->addKernelSet(
                        kernel_lock, std::move( ptr_set ) );
                }

                if( ( kernel_set_id != _this_t::ILLEGAL_KERNEL_SET_ID ) &&
                    ( kernel_conf_store->hasKernelSet(
                        kernel_lock, kernel_set_id ) ) )
                {
                    status = this->doInitKernelSet(
                        kernel_lock, kernel_set_id );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        SIXTRL_ASSERT( kernel_set_id ==
                            this->kernelSetId( kernel_lock ) );

                        status = this->doFetchOpFlagsAndSyncIdFromKernelSet(
                            kernel_lock, kernel_set_id );
                    }
                }
                else
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }

            return status;
        }
    }
}

#endif /* C++, Host */

/* end: tests/sixtracklib/testlib/common/control/controller_base.cpp */
