#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/cuda/control/device_selector.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <mutex>
    #include <stdexcept>
    #include <thread>

    #include <cuda_runtime_api.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/cuda/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    CudaDeviceSelector::CudaDeviceSelector() :
        m_lockable(),
        m_selected_device( st::CudaDeviceSelector::ILLEGAL_CUDA_DEVICE_INDEX )
    {
        using  _this_t = st::CudaDeviceSelector;
        using status_t = _this_t::status_t;
        using lock_t   = _this_t::lock_t;

        lock_t lock( *this->lockable() );
        SIXTRL_ASSERT( this->checkLock( lock ) );

        status_t const status = this->reset( lock );

        if( status != st::ARCH_STATUS_SUCCESS )
        {
            throw std::runtime_error( "unable to init cuda device selector" );
        }

        SIXTRL_ASSERT( ( this->checkLock( lock ) ) &&
            ( ( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( this->m_selected_device !=
                    _this_t::ILLEGAL_CUDA_DEVICE_INDEX ) ) ||
              ( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( this->m_selected_device ==
                    _this_t::ILLEGAL_CUDA_DEVICE_INDEX ) ) ) );
    }
}

#endif /* end C++, Host */

/* end: sixtracklib/cuda/control/device_selector.cpp */
