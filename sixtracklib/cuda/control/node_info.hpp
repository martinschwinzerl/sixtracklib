#ifndef SIXTRACKLIB_CUDA_CONTROL_NODE_INFO_HPP__
#define SIXTRACKLIB_CUDA_CONTROL_NODE_INFO_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <cstring>
    #include <cstdio>

    #include <cuda_runtime_api.h>

#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_info.h"
    #include "sixtracklib/cuda/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_info.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class CudaNodeInfo : public SIXTRL_CXX_NAMESPACE::NodeInfoBase
    {
        private:

        using _base_node_info_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;

        public:

        using node_id_t     = _base_node_info_t::node_id_t;
        using platform_id_t = _base_node_info_t::platform_id_t;
        using device_id_t   = _base_node_info_t::device_id_t;
        using node_index_t  = _base_node_info_t::node_index_t;
        using size_type     = _base_node_info_t::size_type;
        using arch_info_t   = _base_node_info_t::arch_info_t;
        using arch_id_t     = _base_node_info_t::arch_id_t;

        using cuda_dev_index_t = int;

        static SIXTRL_CONSTEXPR_OR_CONST cuda_dev_index_t
            ILLEGAL_DEV_INDEX = cuda_dev_index_t{ -1 };

        static SIXTRL_CONSTEXPR_OR_CONST size_type DEFAULT_WARP_SIZE =
                SIXTRL_CXX_NAMESPACE::ARCH_CUDA_DEFAULT_WARP_SIZE;

        SIXTRL_HOST_FN explicit CudaNodeInfo(
            cuda_dev_index_t const cuda_dev_index = ILLEGAL_DEV_INDEX );

        SIXTRL_HOST_FN CudaNodeInfo(
            cuda_dev_index_t const cuda_dev_index,
            ::cudaDeviceProp const& cuda_device_properties,
            platform_id_t const platform_id = node_id_t::ILLEGAL_PLATFORM_ID,
            device_id_t const device_id = node_id_t::ILLEGAL_DEVICE_ID,
            node_index_t const node_index = node_id_t::UNDEFINED_INDEX,
            bool const is_default_node = false,
            bool const is_selected_node = false );


        SIXTRL_HOST_FN CudaNodeInfo( CudaNodeInfo const& other ) = default;
        SIXTRL_HOST_FN CudaNodeInfo( CudaNodeInfo&& other ) = default;

        SIXTRL_HOST_FN CudaNodeInfo& operator=( CudaNodeInfo&& rhs ) = default;

        SIXTRL_HOST_FN CudaNodeInfo& operator=(
            CudaNodeInfo const& rhs ) = default;

        SIXTRL_HOST_FN virtual ~CudaNodeInfo() = default;

        SIXTRL_HOST_FN bool hasPciBusId() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& pciBusId() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrPciBusIdStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN ::cudaDeviceProp const&
        cudaDeviceProperties() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN ::cudaDeviceProp const*
        ptrCudaDeviceProperties() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasCudaDeviceIndex() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN cuda_dev_index_t cudaDeviceIndex() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setCudaDeviceIndex(
            cuda_dev_index_t const index ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type warpSize() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type computeCapability() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type numMultiprocessors() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type maxThreadsPerBlock() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        maxThreadsPerMultiprocessor() const SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN virtual status_t doPrintToOutputStream(
            std::ostream& SIXTRL_RESTRICT_REF output,
            controller_base_t const* SIXTRL_RESTRICT ptr_ctrl ) const override;

        private:
        ::cudaDeviceProp    m_cu_device_properties;
        cuda_dev_index_t    m_cu_device_index;
    };

    SIXTRL_HOST_FN CudaNodeInfo const* NodeInfo_as_cuda_node_info(
        SIXTRL_CXX_NAMESPACE::NodeInfoBase const*
            SIXTRL_RESTRICT ptr_info ) SIXTRL_NOEXCEPT;

    SIXTRL_HOST_FN CudaNodeInfo* NodeInfo_as_cuda_node_info(
        SIXTRL_CXX_NAMESPACE::NodeInfoBase*
            SIXTRL_RESTRICT ptr_info ) SIXTRL_NOEXCEPT;
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

typedef SIXTRL_CXX_NAMESPACE::CudaNodeInfo NS(CudaNodeInfo);

#else /* C++, Host */

typedef void NS(CudaNodeInfo);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE bool CudaNodeInfo::hasPciBusId() const SIXTRL_NOEXCEPT
    {
        return this->hasUniqueIdStr();
    }

    SIXTRL_INLINE std::string const&
    CudaNodeInfo::pciBusId() const SIXTRL_NOEXCEPT
    {
        return this->uniqueIdStr();
    }

    SIXTRL_INLINE char const*
    CudaNodeInfo::ptrPciBusIdStr() const SIXTRL_NOEXCEPT
    {
        return this->ptrUniqueIdStr();
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE ::cudaDeviceProp const&
    CudaNodeInfo::cudaDeviceProperties() const SIXTRL_NOEXCEPT
    {
        return this->m_cu_device_properties;
    }

    SIXTRL_INLINE ::cudaDeviceProp const*
    CudaNodeInfo::ptrCudaDeviceProperties() const SIXTRL_NOEXCEPT
    {
        return &this->m_cu_device_properties;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool CudaNodeInfo::hasCudaDeviceIndex() const SIXTRL_NOEXCEPT
    {
        return ( this->m_cu_device_index != CudaNodeInfo::ILLEGAL_DEV_INDEX );
    }

    SIXTRL_INLINE CudaNodeInfo::cuda_dev_index_t
    CudaNodeInfo::cudaDeviceIndex() const SIXTRL_NOEXCEPT
    {
        return this->m_cu_device_index;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CudaNodeInfo::size_type
    CudaNodeInfo::warpSize() const SIXTRL_NOEXCEPT
    {
        return static_cast< CudaNodeInfo::size_type >(
            this->m_cu_device_properties.warpSize );
    }

    SIXTRL_INLINE CudaNodeInfo::size_type
    CudaNodeInfo::computeCapability() const SIXTRL_NOEXCEPT
    {
        using size_t = st::CudaNodeInfo::size_type;

        size_t compute_capability = this->m_cu_device_properties.major;
        compute_capability *= size_t{ 10 };
        compute_capability += this->m_cu_device_properties.minor;

        return compute_capability;
    }

    SIXTRL_INLINE CudaNodeInfo::size_type
    CudaNodeInfo::numMultiprocessors() const SIXTRL_NOEXCEPT
    {
        return static_cast< CudaNodeInfo::size_type >(
            this->m_cu_device_properties.multiProcessorCount );
    }

    SIXTRL_INLINE CudaNodeInfo::size_type
    CudaNodeInfo::maxThreadsPerBlock() const SIXTRL_NOEXCEPT
    {
        return static_cast< CudaNodeInfo::size_type >(
            this->m_cu_device_properties.maxThreadsPerBlock );
    }

    SIXTRL_INLINE CudaNodeInfo::size_type
    CudaNodeInfo::maxThreadsPerMultiprocessor() const SIXTRL_NOEXCEPT
    {
        return static_cast< CudaNodeInfo::size_type >(
            this->m_cu_device_properties.maxThreadsPerMultiProcessor );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::CudaNodeInfo const*
    NodeInfo_as_cuda_node_info(
        SIXTRL_CXX_NAMESPACE::NodeInfoBase const*
            SIXTRL_RESTRICT node_info_base ) SIXTRL_NOEXCEPT
    {
        using cuda_node_info_t = SIXTRL_CXX_NAMESPACE::CudaNodeInfo;

        return ( node_info_base != nullptr )
            ? node_info_base->asDerivedNodeInfo< cuda_node_info_t >(
                SIXTRL_CXX_NAMESPACE::ARCHITECTURE_CUDA )
            : nullptr;
    }

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::CudaNodeInfo*
    NodeInfo_as_cuda_node_info(
        SIXTRL_CXX_NAMESPACE::NodeInfoBase*
            SIXTRL_RESTRICT node_info_base ) SIXTRL_NOEXCEPT
    {
        SIXTRL_CXX_NAMESPACE::NodeInfoBase const* c_ptr = node_info_base;

        return const_cast< SIXTRL_CXX_NAMESPACE::CudaNodeInfo* >(
            NodeInfo_as_cuda_node_info( c_ptr ) );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_CUDA_CONTROL_NODE_INFO_HPP__ */

/* end : sixtracklib/cuda/control/node_info.hpp */
