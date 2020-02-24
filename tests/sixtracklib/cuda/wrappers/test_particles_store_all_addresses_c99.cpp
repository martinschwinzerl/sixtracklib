#include "sixtracklib/cuda/wrappers/track_job_wrappers.h"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include <cuda_runtime_api.h>

#include "sixtracklib/testlib.h"

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/particles/particles_addr.h"
#include "sixtracklib/common/particles.h"
#include "sixtracklib/cuda/control/default_kernel_config.h"
#include "sixtracklib/cuda/control/kernel_config.h"
#include "sixtracklib/cuda/control/node_info.h"
#include "sixtracklib/cuda/controller.h"
#include "sixtracklib/cuda/argument.h"

// Particles_buffer_store_all_addresses_cuda_wrapper

TEST( C99_CudaWrappersParticlesStoreAddrTests, TestSingleParticleSetPerBuffer )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using c_buffer_t         = ::NS(Buffer);
    using cuda_ctrl_t        = ::NS(CudaController);
    using cuda_arg_t         = ::NS(CudaArgument);
    using cuda_kernel_conf_t = ::NS(CudaKernelConfig);
    using cuda_node_info_t   = ::NS(CudaNodeInfo);
    using size_t             = ::NS(buffer_size_t);
    using status_t           = ::NS(arch_status_t);
    using node_index_t       = ::NS(node_index_t);
    using kernel_id_t        = ::NS(ctrl_kernel_id_t);

    c_buffer_t* particles_buffer  = ::NS(Buffer_new)( size_t{ 0 } );
    c_buffer_t* cmp_paddr_buffer  = ::NS(Buffer_new)( size_t{ 0 } );

    SIXTRL_ASSERT( cmp_paddr_buffer != nullptr );
    SIXTRL_ASSERT( particles_buffer != nullptr );

    size_t const slot_size = ::NS(Buffer_get_slot_size)( particles_buffer );
    SIXTRL_ASSERT( slot_size > size_t{ 0 } );
    ( void )slot_size;

    size_t constexpr prng_seed = size_t{ 20190517 };

    size_t constexpr num_psets           = size_t{ 1 };
    size_t constexpr min_num_particles   = size_t{ 100 };
    size_t constexpr max_num_particles   = size_t{ 200 };

    /* Enforce that we always have  a NS(Particles) instance in this test */
    double const probabilty_to_not_particles = double{ 0.0 };

    status_t status = ::NS(TestParticlesAddr_prepare_buffers)( cmp_paddr_buffer,
        particles_buffer, num_psets, min_num_particles, max_num_particles,
            probabilty_to_not_particles, prng_seed );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(ParticlesAddr_buffer_store_all_addresses)(
        cmp_paddr_buffer, particles_buffer );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(TestParticlesAddr_verify_structure)(
        cmp_paddr_buffer, particles_buffer );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(TestParticlesAddr_verify_addresses)(
        cmp_paddr_buffer, particles_buffer );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    /* -------------------------------------------------------------------- */
    /* Init the Cuda controller and arguments for the addresses
     * and the particles */

    cuda_ctrl_t* ctrl = ::NS(CudaController_create)();
    node_index_t const num_avail_nodes =
        ::NS(Controller_get_num_available_nodes)( ctrl );

    if( num_avail_nodes > node_index_t{ 0 } )
    {
        size_t num_processed_nodes = size_t{ 0 };

        std::vector< node_index_t > available_indices(
            num_avail_nodes, cuda_ctrl_t::UNDEFINED_INDEX );

        size_t const num_retrieved_node_indices =
            ::NS(Controller_get_available_node_indices)( ctrl,
                available_indices.size(), available_indices.data() );

        ASSERT_TRUE( num_retrieved_node_indices == available_indices.size() );

        for( node_index_t const ii : available_indices )
        {
            if( ii != ::NS(Controller_get_selected_node_index)( ctrl ) )
            {
                ::NS(Controller_select_node_by_index)( ctrl, ii );
            }

            ASSERT_TRUE( ii == ::NS(Controller_get_selected_node_index)(
                ctrl ) );

            cuda_node_info_t const* ptr_node_info =
                ::NS(CudaController_get_ptr_node_info_by_index)( ctrl, ii );

            ASSERT_TRUE( ptr_node_info != nullptr );

            ::NS(NodeInfo_print_out)( ptr_node_info );

            /* ************************************************************* */

            std::string kernel_name = SIXTRL_C99_NAMESPACE_PREFIX_STR;
            kernel_name += "Particles_buffer_store_all_addresses_cuda_wrapper";

            kernel_id_t const kernel_id =
                ::NS(CudaController_add_kernel_config_detailed)( ctrl,
                    kernel_name.c_str(), size_t{ 3 }, size_t{ 1 }, size_t{ 0 },
                        size_t{ 0 }, nullptr );

            cuda_kernel_conf_t* ptr_kernel_config =
                ::NS(CudaController_get_ptr_kernel_config)( ctrl, kernel_id );

            status =
            ::NS(CudaKernelConfig_configure_fetch_particles_addresses_kernel)(
                ptr_kernel_config, ptr_node_info, num_psets, size_t{ 128 } );

            ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

            /* ************************************************************* */

            c_buffer_t* paddr_buffer = ::NS(Buffer_new)( size_t{ 0 } );
            SIXTRL_ASSERT( paddr_buffer != nullptr );

            status = ::NS(ParticlesAddr_prepare_buffer_based_on_particles_buffer)(
                paddr_buffer, particles_buffer );
            SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

            cuda_arg_t* particles_arg = ::NS(CudaArgument_new)( ctrl );
            SIXTRL_ASSERT( particles_arg != nullptr );

            cuda_arg_t* addresses_arg = ::NS(CudaArgument_new)( ctrl );
            SIXTRL_ASSERT( addresses_arg != nullptr );

            cuda_arg_t* result_register_arg = ::NS(CudaArgument_new)( ctrl );
            SIXTRL_ASSERT( result_register_arg != nullptr );

            /* ************************************************************* */

            ASSERT_TRUE( ::NS(TestParticlesAddr_prepare_ctrl_args_test)(
                ctrl, addresses_arg, paddr_buffer, particles_arg,
                    particles_buffer, result_register_arg ) );

            ::NS(Particles_buffer_store_all_addresses_cuda_wrapper)(
                ptr_kernel_config, addresses_arg, particles_arg,
                    result_register_arg );

            ASSERT_TRUE( ::NS(TestParticlesAddr_evaluate_ctrl_args_test)(
                ctrl, addresses_arg, paddr_buffer, particles_arg,
                    particles_buffer, result_register_arg ) );

            /* ************************************************************* */

            ::NS(Argument_delete)( result_register_arg );
            ::NS(Argument_delete)( addresses_arg );
            ::NS(Argument_delete)( particles_arg );

            ::NS(Buffer_delete)( paddr_buffer );

            ++num_processed_nodes;
        }

        ASSERT_TRUE( num_processed_nodes ==
            static_cast< size_t >( num_avail_nodes ) );
    }
    else
    {
        std::cout << "No cuda nodes found -> skipping test" << std::endl;
    }

    ::NS(Buffer_delete)( cmp_paddr_buffer );
    ::NS(Controller_delete)( ctrl );
}


TEST( C99_CudaWrappersParticlesStoreAddrTests, TestMultiParticleSetsPerBuffer )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using c_buffer_t         = ::NS(Buffer);
    using cuda_ctrl_t        = ::NS(CudaController);
    using cuda_arg_t         = ::NS(CudaArgument);
    using cuda_kernel_conf_t = ::NS(CudaKernelConfig);
    using cuda_node_info_t   = ::NS(CudaNodeInfo);
    using size_t             = ::NS(buffer_size_t);
    using status_t           = ::NS(arch_status_t);
    using node_index_t       = ::NS(node_index_t);
    using kernel_id_t        = ::NS(ctrl_kernel_id_t);

    c_buffer_t* particles_buffer  = ::NS(Buffer_new)( size_t{ 0 } );
    c_buffer_t* cmp_paddr_buffer  = ::NS(Buffer_new)( size_t{ 0 } );

    SIXTRL_ASSERT( cmp_paddr_buffer != nullptr );
    SIXTRL_ASSERT( particles_buffer != nullptr );

    size_t const slot_size = ::NS(Buffer_get_slot_size)( particles_buffer );
    SIXTRL_ASSERT( slot_size > size_t{ 0 } );
    ( void )slot_size;

    size_t constexpr prng_seed = size_t{ 20190517 };

    size_t constexpr num_psets           = size_t{ 2048 };
    size_t constexpr min_num_particles   = size_t{ 2 };
    size_t constexpr max_num_particles   = size_t{ 4 };

    /* Enforce that we always have  a NS(Particles) instance in this test */
    double const probabilty_to_not_particles = double{ 0.0 };

    status_t status = ::NS(TestParticlesAddr_prepare_buffers)( cmp_paddr_buffer,
        particles_buffer, num_psets, min_num_particles, max_num_particles,
            probabilty_to_not_particles, prng_seed );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(ParticlesAddr_buffer_store_all_addresses)(
        cmp_paddr_buffer, particles_buffer );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(TestParticlesAddr_verify_structure)(
        cmp_paddr_buffer, particles_buffer );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(TestParticlesAddr_verify_addresses)(
        cmp_paddr_buffer, particles_buffer );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    /* -------------------------------------------------------------------- */
    /* Init the Cuda controller and arguments for the addresses
     * and the particles */

    cuda_ctrl_t* ctrl = ::NS(CudaController_create)();
    node_index_t const num_avail_nodes =
        ::NS(Controller_get_num_available_nodes)( ctrl );

    if( num_avail_nodes > node_index_t{ 0 } )
    {
        size_t num_processed_nodes = size_t{ 0 };

        std::vector< node_index_t > available_indices(
            num_avail_nodes, cuda_ctrl_t::UNDEFINED_INDEX );

        size_t const num_retrieved_node_indices =
            ::NS(Controller_get_available_node_indices)( ctrl,
                available_indices.size(), available_indices.data() );

        ASSERT_TRUE( num_retrieved_node_indices == available_indices.size() );

        for( node_index_t const ii : available_indices )
        {
            if( ii != ::NS(Controller_get_selected_node_index)( ctrl ) )
            {
                ::NS(Controller_select_node_by_index)( ctrl, ii );
            }

            ASSERT_TRUE( ii == ::NS(Controller_get_selected_node_index)(
                ctrl ) );

            cuda_node_info_t const* ptr_node_info =
                ::NS(CudaController_get_ptr_node_info_by_index)( ctrl, ii );

            ASSERT_TRUE( ptr_node_info != nullptr );

            ::NS(NodeInfo_print_out)( ptr_node_info );

            /* ************************************************************* */

            std::string kernel_name = SIXTRL_C99_NAMESPACE_PREFIX_STR;
            kernel_name += "Particles_buffer_store_all_addresses_cuda_wrapper";

            kernel_id_t const kernel_id =
                ::NS(CudaController_add_kernel_config_detailed)( ctrl,
                    kernel_name.c_str(), size_t{ 3 }, size_t{ 1 }, size_t{ 0 },
                        size_t{ 0 }, nullptr );

            cuda_kernel_conf_t* ptr_kernel_config =
                ::NS(CudaController_get_ptr_kernel_config)( ctrl, kernel_id );

            status =
            ::NS(CudaKernelConfig_configure_fetch_particles_addresses_kernel)(
                ptr_kernel_config, ptr_node_info, num_psets, size_t{ 128 } );

            ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

            /* ************************************************************* */

            c_buffer_t* paddr_buffer = ::NS(Buffer_new)( size_t{ 0 } );
            SIXTRL_ASSERT( paddr_buffer != nullptr );

            status = ::NS(ParticlesAddr_prepare_buffer_based_on_particles_buffer)(
                paddr_buffer, particles_buffer );
            SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

            cuda_arg_t* particles_arg = ::NS(CudaArgument_new)( ctrl );
            SIXTRL_ASSERT( particles_arg != nullptr );

            cuda_arg_t* addresses_arg = ::NS(CudaArgument_new)( ctrl );
            SIXTRL_ASSERT( addresses_arg != nullptr );

            cuda_arg_t* result_register_arg = ::NS(CudaArgument_new)( ctrl );
            SIXTRL_ASSERT( result_register_arg != nullptr );

            /* ************************************************************* */

            ASSERT_TRUE( ::NS(TestParticlesAddr_prepare_ctrl_args_test)(
                ctrl, addresses_arg, paddr_buffer, particles_arg,
                    particles_buffer, result_register_arg ) );

            ::NS(Particles_buffer_store_all_addresses_cuda_wrapper)(
                ptr_kernel_config, addresses_arg, particles_arg,
                    result_register_arg );

            ASSERT_TRUE( ::NS(TestParticlesAddr_evaluate_ctrl_args_test)(
                ctrl, addresses_arg, paddr_buffer, particles_arg,
                    particles_buffer, result_register_arg ) );

            /* ************************************************************* */

            ::NS(Argument_delete)( result_register_arg );
            ::NS(Argument_delete)( addresses_arg );
            ::NS(Argument_delete)( particles_arg );

            ::NS(Buffer_delete)( paddr_buffer );

            ++num_processed_nodes;
        }

        ASSERT_TRUE( num_processed_nodes ==
            static_cast< size_t >( num_avail_nodes ) );
    }
    else
    {
        std::cout << "No cuda nodes found -> skipping test" << std::endl;
    }

    ::NS(Buffer_delete)( cmp_paddr_buffer );
    ::NS(Controller_delete)( ctrl );
}


TEST( C99_CudaWrappersParticlesStoreAddrTests,
      TestMultiParticleSetsPerBufferWithGenericObj )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using c_buffer_t         = ::NS(Buffer);
    using cuda_ctrl_t        = ::NS(CudaController);
    using cuda_arg_t         = ::NS(CudaArgument);
    using cuda_kernel_conf_t = ::NS(CudaKernelConfig);
    using cuda_node_info_t   = ::NS(CudaNodeInfo);
    using size_t             = ::NS(buffer_size_t);
    using status_t           = ::NS(arch_status_t);
    using node_index_t       = ::NS(node_index_t);
    using kernel_id_t        = ::NS(ctrl_kernel_id_t);

    c_buffer_t* particles_buffer  = ::NS(Buffer_new)( size_t{ 0 } );
    c_buffer_t* cmp_paddr_buffer  = ::NS(Buffer_new)( size_t{ 0 } );

    SIXTRL_ASSERT( cmp_paddr_buffer != nullptr );
    SIXTRL_ASSERT( particles_buffer != nullptr );

    size_t const slot_size = ::NS(Buffer_get_slot_size)( particles_buffer );
    SIXTRL_ASSERT( slot_size > size_t{ 0 } );
    ( void )slot_size;

    size_t constexpr prng_seed = size_t{ 20190517 };

    size_t constexpr num_psets           = size_t{ 2048 };
    size_t constexpr min_num_particles   = size_t{ 2 };
    size_t constexpr max_num_particles   = size_t{ 4 };

    /* Enforce that we always have  a NS(Particles) instance in this test */
    double const probabilty_to_not_particles = double{ 0.1 };

    status_t status = ::NS(TestParticlesAddr_prepare_buffers)( cmp_paddr_buffer,
        particles_buffer, num_psets, min_num_particles, max_num_particles,
            probabilty_to_not_particles, prng_seed );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(ParticlesAddr_buffer_store_all_addresses)(
        cmp_paddr_buffer, particles_buffer );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(TestParticlesAddr_verify_structure)(
        cmp_paddr_buffer, particles_buffer );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(TestParticlesAddr_verify_addresses)(
        cmp_paddr_buffer, particles_buffer );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    /* -------------------------------------------------------------------- */
    /* Init the Cuda controller and arguments for the addresses
     * and the particles */

    cuda_ctrl_t* ctrl = ::NS(CudaController_create)();
    node_index_t const num_avail_nodes =
        ::NS(Controller_get_num_available_nodes)( ctrl );

    if( num_avail_nodes > node_index_t{ 0 } )
    {
        size_t num_processed_nodes = size_t{ 0 };

        std::vector< node_index_t > available_indices(
            num_avail_nodes, cuda_ctrl_t::UNDEFINED_INDEX );

        size_t const num_retrieved_node_indices =
            ::NS(Controller_get_available_node_indices)( ctrl,
                available_indices.size(), available_indices.data() );

        ASSERT_TRUE( num_retrieved_node_indices == available_indices.size() );

        for( node_index_t const ii : available_indices )
        {
            if( ii != ::NS(Controller_get_selected_node_index)( ctrl ) )
            {
                ::NS(Controller_select_node_by_index)( ctrl, ii );
            }

            ASSERT_TRUE( ii == ::NS(Controller_get_selected_node_index)(
                ctrl ) );

            cuda_node_info_t const* ptr_node_info =
                ::NS(CudaController_get_ptr_node_info_by_index)( ctrl, ii );

            ASSERT_TRUE( ptr_node_info != nullptr );

            ::NS(NodeInfo_print_out)( ptr_node_info );

            /* ************************************************************* */

            std::string kernel_name = SIXTRL_C99_NAMESPACE_PREFIX_STR;
            kernel_name += "Particles_buffer_store_all_addresses_cuda_wrapper";

            kernel_id_t const kernel_id =
                ::NS(CudaController_add_kernel_config_detailed)( ctrl,
                    kernel_name.c_str(), size_t{ 3 }, size_t{ 1 }, size_t{ 0 },
                        size_t{ 0 }, nullptr );

            cuda_kernel_conf_t* ptr_kernel_config =
                ::NS(CudaController_get_ptr_kernel_config)( ctrl, kernel_id );

            status =
            ::NS(CudaKernelConfig_configure_fetch_particles_addresses_kernel)(
                ptr_kernel_config, ptr_node_info, num_psets, size_t{ 128 } );

            ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

            /* ************************************************************* */

            c_buffer_t* paddr_buffer = ::NS(Buffer_new)( size_t{ 0 } );
            SIXTRL_ASSERT( paddr_buffer != nullptr );

            status = ::NS(ParticlesAddr_prepare_buffer_based_on_particles_buffer)(
                paddr_buffer, particles_buffer );
            SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

            cuda_arg_t* particles_arg = ::NS(CudaArgument_new)( ctrl );
            SIXTRL_ASSERT( particles_arg != nullptr );

            cuda_arg_t* addresses_arg = ::NS(CudaArgument_new)( ctrl );
            SIXTRL_ASSERT( addresses_arg != nullptr );

            cuda_arg_t* result_register_arg = ::NS(CudaArgument_new)( ctrl );
            SIXTRL_ASSERT( result_register_arg != nullptr );

            /* ************************************************************* */

            ASSERT_TRUE( ::NS(TestParticlesAddr_prepare_ctrl_args_test)(
                ctrl, addresses_arg, paddr_buffer, particles_arg,
                    particles_buffer, result_register_arg ) );

            ::NS(Particles_buffer_store_all_addresses_cuda_wrapper)(
                ptr_kernel_config, addresses_arg, particles_arg,
                    result_register_arg );

            ASSERT_TRUE( ::NS(TestParticlesAddr_evaluate_ctrl_args_test)(
                ctrl, addresses_arg, paddr_buffer, particles_arg,
                    particles_buffer, result_register_arg ) );

            /* ************************************************************* */

            ::NS(Argument_delete)( result_register_arg );
            ::NS(Argument_delete)( addresses_arg );
            ::NS(Argument_delete)( particles_arg );

            ::NS(Buffer_delete)( paddr_buffer );

            ++num_processed_nodes;
        }

        ASSERT_TRUE( num_processed_nodes ==
            static_cast< size_t >( num_avail_nodes ) );
    }
    else
    {
        std::cout << "No cuda nodes found -> skipping test" << std::endl;
    }

    ::NS(Buffer_delete)( cmp_paddr_buffer );
    ::NS(Controller_delete)( ctrl );
}

/* end: sixtracklib/cuda/wrappers/test_particles_store_all_addresses_c99.cpp */
