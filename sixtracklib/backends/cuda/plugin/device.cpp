#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/plugin/device.h"
    #include "sixtracklib/backends/cuda/plugin/node.h"
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

    this_t::platform_id_t this_t::platform_id() const SIXTRL_NOEXCEPT
    {
        return this->m_node_id.m_platform_id;
    }

    this_t::device_id_t this_t::device_id() const SIXTRL_NOEXCEPT
    {
        return this->m_node_id.m_device_id;
    }

    bool this_t::is_legal() const SIXTRL_NOEXCEPT
    {
        return ( ( this->backend_id() == st::BACKEND_CUDA ) &&
                 ( this->platform_id() != st::NODE_ILLEGAL_PLATFORM_ID ) &&
                 ( this->device_id() != st::NODE_ILLEGAL_DEVICE_ID ) );
    }

    ::NS(NodeId) const& this_t::node_id_data() const SIXTRL_NOEXCEPT
    {
        return this->m_node_id;
    }

    ::CUdevice this_t::cuda_handle() const SIXTRL_NOEXCEPT
    {
        return this->m_cuda_device;
    }

    void this_t::reset() SIXTRL_NOEXCEPT
    {
        this->m_node_id.m_platform_id = st::NODE_ILLEGAL_PLATFORM_ID;
        this->m_node_id.m_device_id = st::NODE_ILLEGAL_DEVICE_ID;
        this->m_cuda_device = this_t::ILLEGAL_DEVICE_HANDLE;
    }

    this_t::status_t this_t::init( this_t::platform_id_t const platform_id,
        this_t::device_id_t const device_id )
    {
        this_t::status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( platform_id != st::NODE_ILLEGAL_PLATFORM_ID ) &&
            ( device_id != st::NODE_ILLEGAL_DEVICE_ID ) &&
            ( platform_id >= this_t::platform_id_t{ 0 } ) &&
            ( static_cast< this_t::platform_id_t >(
                st::CudaNodeInfo::NUM_ALL_NODES() ) > platform_id ) )
        {
            this->m_node_id.m_backend_id = st::BACKEND_CUDA;
            this->m_node_id.m_platform_id = platform_id;
            this->m_node_id.m_device_id = device_id;
            this->m_cuda_device = static_cast< ::CUdevice >( platform_id );

            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    this_t::status_t this_t::init( this_t::c_node_id_t const& node_id )
    {
        return ( node_id.m_backend_id == st::BACKEND_CUDA )
            ? this->init( node_id.m_platform_id, node_id.m_device_id )
            : st::STATUS_GENERAL_FAILURE;
    }

    this_t::status_t this_t::init( const this_t::c_node_id_t *const node_id )
    {
        return ( ( node_id != nullptr ) &&
                 ( node_id->m_backend_id == st::BACKEND_CUDA ) )
            ? this->init( node_id->m_platform_id, node_id->m_device_id )
            : st::STATUS_GENERAL_FAILURE;
    }

    this_t::status_t this_t::init(
        st::NodeId const& SIXTRL_RESTRICT_REF node_id )
    {
        return ( node_id.backend_id() == st::BACKEND_CUDA )
            ? this->init( node_id.platform_id(), node_id.device_id() )
            : st::STATUS_GENERAL_FAILURE;
    }

    this_t::status_t this_t::init(
        this_t::string_type const& SIXTRL_RESTRICT_REF node_id_str )
    {
        st::NodeId temp;
        return this->init( node_id_str,
            temp.find_device_string_format( node_id_str ) );
    }

    this_t::status_t this_t::init(
        this_t::string_type const& SIXTRL_RESTRICT_REF node_id_str,
        this_t::str_format_t node_id_str_format )
    {
        st::NodeId node_id( node_id_str, node_id_str_format );

        if( ( node_id_str_format == st::NODE_ID_STR_FORMAT_NOBACKEND ) &&
            ( node_id.backend_id() == st::BACKEND_UNDEFINED ) )
        {
            node_id.set_backend_id( st::BACKEND_CUDA );
        }

        return ( node_id.backend_id() == st::BACKEND_CUDA )
            ? this->init( node_id.platform_id(), node_id.device_id() )
            : st::STATUS_GENERAL_FAILURE;
    }

    this_t::status_t this_t::init( ::CUdevice const cuda_device_handle )
    {
        st::status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( cuda_device_handle != this_t::ILLEGAL_DEVICE_HANDLE ) &&
            ( cuda_device_handle >= ::CUdevice{ 0 } ) &&
            ( cuda_device_handle < static_cast< ::CUdevice >(
                st::CudaNodeInfo::NUM_ALL_NODES() ) ) )
        {
            this->m_cuda_device = cuda_device_handle;
            this->m_node_id.m_backend_id = st::BACKEND_CUDA;
            this->m_node_id.m_platform_id = static_cast<
                this_t::platform_id_t >( cuda_device_handle );
            this->m_node_id.m_device_id = this_t::device_id_t{ 0 };
            status = st::STATUS_SUCCESS;
        }

        return status;
    }
}


::NS(CudaDevice)* NS(CudaDevice_create)( ::CUdevice const cuda_handle )
{
    return new SIXTRL_CXX_NAMESPACE::CudaDevice( cuda_handle );
}

::NS(CudaDevice)* NS(CudaDevice_create_from_platform_id_device_id)(
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    return new SIXTRL_CXX_NAMESPACE::CudaDevice( platform_id, device_id );
}

::NS(CudaDevice)* NS(CudaDevice_create_from_node_id)(
    const NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    return new SIXTRL_CXX_NAMESPACE::CudaDevice( node_id  );
}

::NS(CudaDevice)* NS(CudaDevice_create_from_string)(
    char const* SIXTRL_RESTRICT node_id_str )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return ( ( node_id_str != nullptr ) &&
             ( std::strlen( node_id_str ) > st::size_t{ 0 } ) )
        ? new st::CudaDevice( node_id_str ) : nullptr;
}

::NS(CudaDevice)* NS(CudaDevice_create_from_string_using_format)(
    char const* SIXTRL_RESTRICT node_id_str,
    NS(node_id_str_fmt_t) const format )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return ( ( node_id_str != nullptr ) &&
             ( std::strlen( node_id_str ) > st::size_t{ 0 } ) )
        ? new st::CudaDevice( node_id_str, format ) : nullptr;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void NS(CudaDevice_delete)(
    ::NS(CudaDevice)* SIXTRL_RESTRICT dev ) SIXTRL_NOEXCEPT { delete dev; }

/* ------------------------------------------------------------------------- */

::NS(node_platform_id_t) NS(CudaDevice_platform_id)(
    const ::NS(CudaDevice) *const SIXTRL_RESTRICT device ) SIXTRL_NOEXCEPT {
    return ( device != nullptr )
        ? device->platform_id() : ::NS(NODE_ILLEGAL_PLATFORM_ID);
}

::NS(node_device_id_t) NS(CudaDevice_device_id)(
    const ::NS(CudaDevice) *const SIXTRL_RESTRICT device ) SIXTRL_NOEXCEPT {
    return ( device != nullptr )
        ? device->device_id() : SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;
}

bool NS(CudaDevice_is_legal)( const ::NS(CudaDevice) *const
    SIXTRL_RESTRICT device ) SIXTRL_NOEXCEPT {
    return ( ( device != nullptr ) && ( device->is_legal() ) );
}

const ::NS(NodeId) *const NS(CudaDevice_node_id)(
    const ::NS(CudaDevice) *const SIXTRL_RESTRICT device ) SIXTRL_NOEXCEPT {
    return ( device != nullptr ) ? &device->node_id_data() : nullptr;
}

::CUdevice NS(CudaDevice_cuda_handle)(
    const ::NS(CudaDevice) *const SIXTRL_RESTRICT device ) SIXTRL_NOEXCEPT {
    return ( device != nullptr ) ? device->cuda_handle() : ::CUdevice{ -1 };
}

#endif /* C++, Host */
