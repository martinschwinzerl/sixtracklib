#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/plugin/device.h"
    #include "sixtracklib/backends/cuda/plugin/cuda_tools.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cuda.h>
    #include <cuda_runtime_api.h>
    #if defined( __cplusplus )
        #include <stdexcept>
        #include <sstream>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using this_t = st::CudaDevice;
        using base_t = st::BaseBackendObj;
        using st_platform_id_t = this_t::platform_id_t;
        using st_device_id_t = this_t::device_id_t;
    }

    this_t::CudaDevice( ::NS(NodeId) const& SIXTRL_RESTRICT_REF node_id ) :
        base_t( st::BACKEND_CUDA, st::CLASS_ID_DEVICE )
    {
        int max_num_devices = 0;

        ::CUresult const ret = ::cuDeviceGetCount( &max_num_devices );

        if( ret != ::CUDA_SUCCESS )
        {
            std::ostringstream a2str;

            a2str << "Unable to retrieve number of devices: ";
            st::CudaError_print_error_name( a2str, ret,
                "unknown_error_code" ) << ": " <<
            st::CudaError_print_error_description( a2str, ret );

            throw std::runtime_error( a2str.str() );
        }

        if( ( node_id.m_backend_id  != st::BACKEND_CUDA ) ||
            ( node_id.m_platform_id == st::NODE_ILLEGAL_PLATFORM_ID ) ||
            ( node_id.m_device_id   == st::NODE_ILLEGAL_DEVICE_ID ) ||
            ( static_cast< st_platform_id_t >( max_num_devices ) <=
              node_id.m_platform_id ) )
        {
            std::ostringstream a2str;
            a2str << "illegal node_id { "
                  << node_id.m_backend_id  << ", "
                  << node_id.m_platform_id << ", "
                  << node_id.m_device_id << " }";

            throw std::runtime_error( a2str.str() );
        }

        this->m_node_id = node_id;
        this->m_cuda_device_handle = static_cast< ::CUdevice >(
            node_id.m_platform_id );
    }


    this_t::CudaDevice( ::CUdevice const cuda_device_handle ) :
        base_t( st::BACKEND_CUDA, st::CLASS_ID_DEVICE )
    {
        int max_num_devices = 0;
        ::CUresult const ret = ::cuDeviceGetCount( &max_num_devices );

        if( ret != ::CUDA_SUCCESS )
        {
            std::ostringstream a2str;

            a2str << "Unable to retrieve number of devices: ";
            st::CudaError_print_error_name( a2str, ret,
                "unknown_error_code" ) << ": " <<
            st::CudaError_print_error_description( a2str, ret );

            throw std::runtime_error( a2str.str() );
        }

        this->m_node_id.m_backend_id  = st::BACKEND_CUDA;
        this->m_node_id.m_platform_id = static_cast<
            st_platform_id_t >( cuda_device_handle );
        this->m_node_id.m_device_id = st_device_id_t{ 0 };
    }

    this_t::CudaDevice( this_t::string_type const&
        SIXTRL_RESTRICT_REF node_id_str ) :
        base_t( st::BACKEND_CUDA, st::CLASS_ID_DEVICE )
    {

    }

    SIXTRL_HOST_FN CudaDevice(
        string_type const& SIXTRL_RESTRICT_REF node_id_str,
        node_id_str_fmt_t const node_id_str_format );

    SIXTRL_HOST_FN CudaDevice(
        platform_id_t const platform_id, device_id_t const device_id );

    SIXTRL_HOST_FN CudaDevice( CudaDevice const& ) = default;
    SIXTRL_HOST_FN CudaDevice( CudaDevice&& ) = default;

    SIXTRL_HOST_FN CudaDevice& operator=( CudaDevice const& ) = default;
    SIXTRL_HOST_FN CudaDevice& operator=( CudaDevice&& ) = default;

    SIXTRL_HOST_FN virtual ~CudaDevice() = default;

    /* ----------------------------------------------------------------- */

    SIXTRL_HOST_FN platform_id_t platform_id() const SIXTRL_NOEXCEPT;
    SIXTRL_HOST_FN device_id_t device_id() const SIXTRL_NOEXCEPT;
    SIXTRL_HOST_FN bool is_legal() const SIXTRL_NOEXCEPT
    {

    }

    SIXTRL_HOST_FN ::NS(NodeId) const&
    this_t::node_id_data() const SIXTRL_NOEXCEPT
    {
        return this->m_node_id;
    }

    SIXTRL_HOST_FN ::CUdevice
    this_t::cuda_device_handle() const SIXTRL_NOEXCEPT
    {
        return this->m_cuda_device_handle;
    }


    this_t::status_t this_t::init_cuda_device_handle_from_node_id(
        this_t::platform_id_t const platform_id,
        this_t::device_id_t const device_id )
    {
        this_t::status_t status = st::STATUS_SUCCESS;
        int max_num_devices = 0;

        ::CUresult const ret = ::cuDeviceGetCount( &max_num_devices );

        if( ret != ::CUDA_SUCCESS )
        {
            std::ostringstream a2str;

            a2str << "Unable to retrieve number of devices: ";
            st::CudaError_print_error_name( a2str, ret,
                "unknown_error_code" ) << ": " <<
            st::CudaError_print_error_description( a2str, ret );

            status = st::STATUS_GENERAL_FAILURE;
            throw std::runtime_error( a2str.str() );
        }

        if( ( platform_id == st::NODE_ILLEGAL_PLATFORM_ID ) ||
            ( device_id   == st::NODE_ILLEGAL_DEVICE_ID ) ||
            ( static_cast< st_platform_id_t >(
                max_num_devices ) <= platform_id ) )
        {
            std::ostringstream a2str;
            a2str << "illegal node_id { "
                  << platform_id << ", " << device_id << " }";

            status = st::STATUS_GENERAL_FAILURE;
            throw std::runtime_error( a2str.str() );
        }

        this->m_node_id.m_backend_id = st::BACKEND_CUDA;
        this->m_node_id.m_platform_id = platform_id;
        this->m_node_id.m_device_id = device_id;
        this->m_cuda_device_handle = static_cast< ::CUdevice >( platform_id );

        return status;
    }
}

#endif /* C++, Host */
