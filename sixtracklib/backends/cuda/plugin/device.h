#ifndef SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_DEVICE_H__
#define SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_DEVICE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/definitions.h"
    #include "sixtracklib_base/node/node_id.h"
    #include "sixtracklib_base/backend/backend_obj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cuda.h>
    #if defined( __cplusplus )
        #include <memory>
        #include <string>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class CudaDevice : public SIXTRL_CXX_NAMESPACE::BaseBackendObj
    {
        public:

        using c_node_id_t   = ::NS(NodeId);
        using platform_id_t = SIXTRL_CXX_NAMESPACE::node_platform_id_t;
        using device_id_t   = SIXTRL_CXX_NAMESPACE::node_device_id_t;
        using str_format_t  = SIXTRL_CXX_NAMESPACE::node_id_str_fmt_t;
        using string_type   = std::string;

        SIXTRL_HOST_FN explicit CudaDevice(
            ::NS(NodeId) const& SIXTRL_RESTRICT_REF node_id );

        SIXTRL_HOST_FN explicit CudaDevice(
            ::CUdevice const cuda_device_handle );

        SIXTRL_HOST_FN explicit CudaDevice(
            string_type const& SIXTRL_RESTRICT_REF node_id_str );

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
        SIXTRL_HOST_FN bool is_legal() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN ::NS(NodeId) const& node_id_data() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN ::CUdevice cuda_device_handle() const SIXTRL_NOEXCEPT;

        private:

        using status_t = SIXTRL_CXX_NAMESPACE::status_t;

        SIXTRL_HOST_FN status_t init_cuda_device_handle_from_node_id(
            platform_id_t const platform_id,
            device_id_t const device_id = device_id_t{ 0 } );

        ::CUdevice      m_cuda_device;
        ::NS(NodeId)    m_node_id;
    };
}

extern "C" { typedef SIXTRL_CXX_NAMESPACE::CudaDevice NS(CudaDevice); }

#elif !defined( _GPUCODE ) /* C, Host */

struct SIXTRL_EXPORT_API NS(CudaDevice);

#endif /* C++, Host */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

SIXTRL_EXPORT_API SIXTRL_HOST_FN NS(CudaDevice)*
NS(CudaDevice_create)( CUdevice const cuda_device_handle );

SIXTRL_EXPORT_API SIXTRL_HOST_FN NS(CudaDevice)*
NS(CudaDevice_create_from_platform_id_device_id)(
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

SIXTRL_EXPORT_API SIXTRL_HOST_FN NS(CudaDevice)*
NS(CudaDevice_create_from_node_id)(
    const NS(NodeId) *const SIXTRL_RESTRICT node_id ;

SIXTRL_EXPORT_API SIXTRL_HOST_FN NS(CudaDevice)*
NS(CudaDevice_create_from_string)( char const* SIXTRL_RESTRICT node_id_str );

SIXTRL_EXPORT_API SIXTRL_HOST_FN NS(CudaDevice)*
NS(CudaDevice_create_from_string_using_format)(
    char const* SIXTRL_RESTRICT node_id_str,
    NS(node_id_str_fmt_t) const format );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXPORT_API SIXTRL_HOST_FN void NS(CudaDevice_delete)(
    NS(CudaDevice)* SIXTRL_RESTRICT node_id ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_EXPORT_API SIXTRL_HOST_FN NS(node_platform_id_t)
NS(CudaDevice_platform_id)( const NS(CudaDevice) *const SIXTRL_RESTRICT
    device ) SIXTRL_NOEXCEPT;

SIXTRL_EXPORT_API SIXTRL_HOST_FN NS(node_device_id_t)
NS(CudaDevice_device_id) const SIXTRL_NOEXCEPT;

SIXTRL_EXPORT_API SIXTRL_HOST_FN bool NS(CudaDevice_is_legal)(
    const NS(CudaDevice) *const SIXTRL_RESTRICT device ) SIXTRL_NOEXCEPT;

SIXTRL_EXPORT_API SIXTRL_HOST_FN const ::NS(NodeId) *const
NS(CudaDevice_node_id_data)( const NS(CudaDevice) *const
    SIXTRL_RESTRICT device ) SIXTRL_NOEXCEPT;

SIXTRL_EXPORT_API SIXTRL_HOST_FN CUdevice NS(CudaDevice_cuda_device_handle)(
    const NS(CudaDevice) *const SIXTRL_RESTRICT device ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_DEVICE_H__ */
