#include "sixtracklib/backends/cuda/cuda.h"

#include <iostream>

int main()
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    auto cuda_env = st::Cuda_init_backend();

    if( ( cuda_env != nullptr ) && ( cuda_env->is_ready() ) )
    {
        std::cout << "cuda env is ready!" << std::endl;
    }

    return 0;
}
