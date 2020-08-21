#include "sixtracklib/backends/cuda/cuda.h"
#include "sixtracklib_base/backend/backends_store.h"

#include <iostream>

int main()
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    auto cuda_env = st::Cuda_init_backend();

    if( ( cuda_env != nullptr ) && ( cuda_env->is_ready() ) &&
        ( cuda_env->num_available_nodes() > 0u ) )
    {
        auto gpu = cuda_env->create_node_id( "cuda:0.0" );
        if( !gpu )
        {
            std::cout << "info: unable to find node" << std::endl;
            return 0;
        }

        if( !cuda_env->has_context( *gpu ) ) cuda_env->init_context( *gpu );
        auto ctx = cuda_env->context( *gpu );

        if( ( !ctx ) || ( !ctx->is_active() ) )
        {
            std::cout << "info: unable to create a context" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cout << "info: no suitable cuda environment found -> stopping"
                  << std::endl;
    }

    st::Cuda_shutdown_backend();
    return 0;
}
