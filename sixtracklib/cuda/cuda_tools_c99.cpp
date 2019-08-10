#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/cuda/cuda_tools.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <memory>
    #include <mutex>
    #include <thread>
    #include <utility>

    #include <cuda_runtime_api.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_info.hpp"
    #include "sixtracklib/common/control/node_store.hpp"
    #include "sixtracklib/cuda/control/node_info.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_store.h"
    #include "sixtracklib/cuda/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(arch_status_t) NS(Cuda_init)( ::NS(NodeStore)* SIXTRL_RESTRICT store )
{
    using node_store_t = st::NodeStore;
    using lock_t = node_store_t::lock_t;
    using node_info_base_t = st::NodeInfoBase;
    using size_t = node_store_t::size_type;

    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;
    static constexpr ::NS(arch_id_t) ARCH_ID = st::ARCHITECTURE_CUDA;

    node_store_t& node_store = ( store != nullptr )
        ? *store : St::NodeStore_get();

    if( store == nullptr ) return status;

    lock_t lock( node_store.lockable() );

    if( node_store.checkLock( lock ) )
    {
        bool const has_cuda_arch = store->hasArchitecture( lock, ARCH_ID );

        if( !has_cuda_arch )
        {
            /* TODO: implement dlopen / dlsym and LoadLibrary based
             * loading of cuda shared libraries here if needed here */
        }

        int temp_num_devices = int{ -1 };
        ::cudaError_t err = ::cudaGetNumDevices( &temp_num_devices );

        if( err != ::cudaSuccess ) return status;

        size_t const num_devices = ( temp_num_devices >= int{ 0 } )
            ? static_cast< size_t >( temp_num_devices ) : size_t{ 0 };

        if( num_devices > size_t{ 0 } )
        {
            size_t const num_stored_cuda_platforms = ( has_cuda_arch )
                ? store->numPlatforms( lock, ARCH_ID ) : size_t{ 0 };

            if( num_devices != num_stored_cuda_platforms )
            {
                status = st::ARCH_STATUS_SUCCESS;

                for( int ii = int{ 0 } ; ii < temp_num_devices ; ++ii )
                {
                    if( !store->hasPlatform( lock, ARCH_ID, ii ) )
                    {
                        status = store->addNode( lock,
                            st::CudaNodeInfo::MakeCudaNodeInfo(
                                lock, ii, &node_store ) );

                        if( status != st::ARCH_STATUS_SUCCESS ) break;
                    }
                }
            }
            else
            {
                /* We assume that if the number of nodes is identical that the
                * nodes themselves are also in sync. Since we can only use a
                * numerical id to query state from the CUDA API, this seems the
                * only reasonable thing to do unless you throw away all the
                * nodes all the time you call this function (which is
                * problematic on its own).
                *
                * WARNING: Be careful if the nodes change dynamically and if
                * so, consider discarding nodes explicitly externally from this
                * function so that re-running it will pick up the missing nodes
                */

                status = st::ARCH_STATUS_SUCCESS;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( ( store->hasArchitecture( lock, ARCH_ID ) ) &&
                  ( store->numPlatforms( lock, ARCH_ID ) == num_devices ) ) );
        }
    }

    return status;
}

/* end: sixtracklib/sixtracklib/cuda/cuda_tools_c99.cpp */
