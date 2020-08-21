#ifndef SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_NODE_H__
#define SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_NODE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/definitions.h"
    #include "sixtracklib/backends/cuda/dlib.h"
    #include "sixtracklib_base/node/node_id.h"
    #include "sixtracklib_base/node/node_info.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
        ( SIXTRACKL_ENABLE_BACKEND_CUDA == 1 )
        #include <cuda.h>
    #endif /* defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) */

    #if defined( __cplusplus )
        #include <type_traits>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
    ( SIXTRACKL_ENABLE_BACKEND_CUDA == 1 )

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* ********************************************************************* */
    /* ********                     CudaNodeId                      ******** */
    /* ********************************************************************* */

    class SIXTRL_EXPORT_API CudaNodeId :
        public SIXTRL_CXX_NAMESPACE::NodeId
    {
        public:

        typedef ::CUdevice device_handle_type;

        SIXTRL_STATIC SIXTRL_HOST_FN size_type NUM_ALL_NODES();

        SIXTRL_STATIC SIXTRL_HOST_FN size_type GET_ALL_NODE_IDS(
            ::NS(NodeId)* SIXTRL_RESTRICT node_ids_begin,
            size_type const max_num_node_ids );

        /* ***************************************************************** */

        static_assert( std::is_integral< ::CUdevice >::value &&
                       std::is_signed< ::CUdevice >::value,
                       "CUdevice required to be a signed integer type" );

        static constexpr device_handle_type ILLEGAL_CUDA_DEVICE_HANDLE =
            device_handle_type{ -1 };

        SIXTRL_HOST_FN explicit CudaNodeId(
            device_handle_type const cuda_device_handle =
                ILLEGAL_CUDA_DEVICE_HANDLE );

        SIXTRL_HOST_FN explicit CudaNodeId(
            platform_id_t const platform_id, device_id_t const device_id );

        SIXTRL_HOST_FN explicit CudaNodeId(
            ::NS(NodeId) const& SIXTRL_RESTRICT_REF node_id );

        SIXTRL_HOST_FN explicit CudaNodeId(
            const ::NS(NodeId) *const SIXTRL_RESTRICT node_id );

        SIXTRL_HOST_FN explicit CudaNodeId(
            string_type const& SIXTRL_RESTRICT_REF node_id_str );

        SIXTRL_HOST_FN CudaNodeId(
            string_type const& SIXTRL_RESTRICT_REF node_id_str,
            str_format_t const node_id_str_format );

        /* ---------------------------------------------------------------- */

        SIXTRL_HOST_FN device_handle_type
        device_handle() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_device_handle(
            device_handle_type const device_handle );

        protected:

        SIXTRL_HOST_FN void do_clear() override;

        SIXTRL_HOST_FN status_t do_parse_device_str(
            string_type const& SIXTRL_RESTRICT_REF device_str,
            str_format_t const device_str_format ) override;

        private:

        using dummy_method_param_t = enum{ DUMMY_PARAM };

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* Use these methods to shadow some API from the base type: */

        SIXTRL_HOST_FN status_t set_backend_id(
            backend_id_t const SIXTRL_UNUSED( backend_id ),
            dummy_method_param_t const SIXTRL_UNUSED( dummy ) ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        SIXTRL_HOST_FN status_t set_platform_id(
            platform_id_t const SIXTRL_UNUSED( platform_id ),
            dummy_method_param_t const SIXTRL_UNUSED( dummy ) ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        SIXTRL_HOST_FN status_t set_device_id(
            device_id_t const SIXTRL_UNUSED( device_id ),
            dummy_method_param_t const SIXTRL_UNUSED( dummy ) ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        SIXTRL_HOST_FN status_t do_parse_device_str_cuda(
            string_type const& SIXTRL_RESTRICT_REF device_str,
            str_format_t const device_str_format );

        ::CUdevice m_handle;
    };

    SIXTRL_STATIC SIXTRL_HOST_FN bool NodeId_is_cuda_node_id(
        const SIXTRL_CXX_NAMESPACE::NodeId *const SIXTRL_RESTRICT
            ptr_base ) SIXTRL_NOEXCEPT;

    SIXTRL_STATIC SIXTRL_HOST_FN CudaNodeId const* CudaNodeId_get(
        const SIXTRL_CXX_NAMESPACE::NodeId *const SIXTRL_RESTRICT
            ptr_base ) SIXTRL_NOEXCEPT;

    SIXTRL_STATIC SIXTRL_HOST_FN CudaNodeId* CudaNodeId_get(
        SIXTRL_CXX_NAMESPACE::NodeId* SIXTRL_RESTRICT
            ptr_base ) SIXTRL_NOEXCEPT;

    /* ********************************************************************* */
    /* ********                     CudaNodeInfo                    ******** */
    /* ********************************************************************* */

    class SIXTRL_EXPORT_API CudaNodeInfo :
        public SIXTRL_CXX_NAMESPACE::BaseNodeInfo
    {
        public:

        static constexpr size_type CU_COMPUTE_MODE_DEFAULT = size_type{ 0 };
        static constexpr size_type CU_COMPUTE_MODE_PROHIBITED = size_type{ 2 };
        static constexpr size_type CU_COMPUTE_MODE_EXCLUSIVE_PROCESS =
            size_type{ 3 };

        /* ================================================================= */

        template< class FirstArg, class... InitArgs, typename =
            typename std::enable_if<
                !std::is_same< typename std::decay< FirstArg >::type ,
                    CudaNodeInfo >::value &&
                !std::is_same< typename std::decay< FirstArg >::type,
                    CudaNodeId >::value, void >::type >
        SIXTRL_HOST_FN explicit CudaNodeInfo(
            FirstArg&& arg0, InitArgs&&... init_args ) :
            SIXTRL_CXX_NAMESPACE::BaseNodeInfo(
                SIXTRL_CXX_NAMESPACE::BACKEND_CUDA )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using this_t = st::CudaNodeInfo;

            std::unique_ptr< st::CudaNodeId > temp_node_id(
                new st::CudaNodeId( std::forward< FirstArg >( arg0 ),
                    std::forward< InitArgs >( init_args )... ) );

            if( temp_node_id.get() == nullptr )
            {
                throw std::runtime_error( "unable to construct a CudaNodeId"
                    " from constructor parameters" );
            }

            this_t::status_t status = this->get_device_properties(
                temp_node_id->platform_id(), temp_node_id->device_id() );

            if( status == st::STATUS_SUCCESS )
            {
                status = this->update_stored_node_id(
                    std::move( temp_node_id ) );
            }

            if( status != st::STATUS_SUCCESS )
            {
                this->update_stored_node_id( std::unique_ptr< st::NodeId >{} );
                this->clear_device_properties();
                this->set_platform_id( st::NODE_ILLEGAL_PLATFORM_ID );
                this->set_device_id( st::NODE_ILLEGAL_DEVICE_ID );
            }
        }

        SIXTRL_HOST_FN CudaNodeInfo(
            CudaNodeId const& SIXTRL_RESTRICT_REF cuda_node_id );

        SIXTRL_HOST_FN CudaNodeInfo( CudaNodeInfo const& ) = default;
        SIXTRL_HOST_FN CudaNodeInfo( CudaNodeInfo&& ) = default;
        SIXTRL_HOST_FN CudaNodeInfo& operator=( CudaNodeInfo const& ) = default;
        SIXTRL_HOST_FN CudaNodeInfo& operator=( CudaNodeInfo&& ) = default;
        SIXTRL_HOST_FN virtual ~CudaNodeInfo() = default;

        SIXTRL_HOST_FN CudaNodeId const*
        ptr_cuda_device() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN CudaNodeId const& cuda_device() const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type max_block_dim_x() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type max_block_dim_y() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type max_block_dim_z() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type max_grid_dim_x() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type max_grid_dim_y() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type max_grid_dim_z() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        max_blocks_per_multiprocessor() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type max_threads_per_block() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        max_threads_per_multiprocessor() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        max_shared_mem_per_block() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        reserved_shared_mem_per_block() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        max_shared_mem_per_multiprocessor() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        max_registers_per_block() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        max_registers_per_multiprocessor() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type total_memory() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type total_const_memory() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type clock_rate_khz() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type memory_clock_rate_khz() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        global_memory_bus_width() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type max_pitch() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type texture_alignment() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        texture_pitch_alignment() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        compute_capability_major() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        compute_capability_minor() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type compute_capability() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type warp_size() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        single_to_double_perf_ratio() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type multiprocessor_count() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type l2_cache_size() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        max_persisting_l2_cache_size() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        multi_gpu_board_group_id() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type compute_mode() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_in_default_compute_mode() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        is_in_prohibited_compute_mode() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        is_in_exclusive_process_compute_mode() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_kernel_exec_timeout() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool uses_tcc_driver() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_integrated() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_on_multi_gpu_board() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        supports_overlap_mem_xfer_kernel_exec() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool can_map_host_memory() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        supports_pageable_mem_access() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        supports_pageable_mem_access_via_host_page_tables() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN
        bool supports_concurrent_managed_mem_access() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool supports_ecc() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        supports_concurrent_kernel_exec() const SIXTRL_NOEXCEPT;


        SIXTRL_HOST_FN bool supports_compute_preemption() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool supports_global_l1_caching() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool supports_local_l1_caching() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        supports_host_native_atomics() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool supports_unified_addressing() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        supports_generic_compression() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        supports_virtual_address_management() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        supports_direct_managed_mem_accesss_from_host() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN
        bool can_use_host_ptr_for_registered_mem() const SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN void do_print_extended_section(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            print_flags_t const flags ) const override;

        private:

        SIXTRL_HOST_FN void clear_device_properties() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_t get_device_properties(
            platform_id_t const platform_id, device_id_t const device_id );

        size_type m_max_block_dim[ 3 ] = { 0u, 0u, 0u };
        size_type m_max_grid_dim[ 3 ] = { 0u, 0u, 0u };
        size_type m_compute_capability_major = size_type{ 0 };
        size_type m_compute_capability_minor = size_type{ 0 };
        size_type m_warp_size = size_type{ 0 };
        size_type m_mp_count = size_type{ 0 };
        size_type m_max_blocks_per_mp = size_type{ 0 };
        size_type m_max_threads_per_block = size_type{ 0 };
        size_type m_max_threads_per_mp = size_type{ 0 };
        size_type m_max_shared_mem_per_block = size_type{ 0 };
        size_type m_reserved_shared_mem_per_block = size_type{ 0 };
        size_type m_max_shared_mem_per_mp = size_type{ 0 };
        size_type m_max_i32_registers_per_block = size_type{ 0 };
        size_type m_max_i32_registers_per_mp = size_type{ 0 };
        size_type m_total_memory = size_type{ 0 };
        size_type m_total_const_memory = size_type{ 0 };
        size_type m_clock_rate_khz = size_type{ 0 };
        size_type m_memory_clock_rate_khz = size_type{ 0 };
        size_type m_global_memory_bus_width = size_type{ 0 };
        size_type m_max_pitch = size_type{ 0 };
        size_type m_texture_alignment = size_type{ 0 };
        size_type m_texture_pitch_alignment = size_type{ 0 };
        size_type m_single_to_double_perf_ratio = size_type{ 0 };
        size_type m_l2_cache_size = size_type{ 0 };
        size_type m_max_persisting_l2_cache_size = size_type{ 0 };
        size_type m_compute_mode = size_type{ 0 };
        size_type m_multi_gpu_board_group_id = size_type{ 0 };

        bool m_has_kernel_exec_timeout = false;
        bool m_uses_tcc_driver = false;
        bool m_is_integrated = false;
        bool m_is_on_multi_gpu_board = false;
        bool m_can_map_host_mem = false;
        bool m_supports_ecc = false;
        bool m_supports_overlap_mem_xfer_kernel_exec = false;
        bool m_supports_concurrent_kernel_exec = false;
        bool m_supports_concurrent_managed_mem_access = false;
        bool m_supports_pageable_mem_access = false;
        bool m_supports_pageable_mem_access_via_host_page_tables = false;
        bool m_supports_managed_mem = false;
        bool m_supports_compute_preemption = false;
        bool m_supports_global_l1_cache = false;
        bool m_supports_local_l1_cache = false;
        bool m_supports_host_native_atomic = false;
        bool m_supports_unified_addressing = false;
        bool m_supports_generic_compression = false;
        bool m_supports_virtual_address_management = false;
        bool m_supports_direct_managed_mem_accesss_from_host = false;
        bool m_can_use_host_ptr_for_registered_mem = false;
    };

    SIXTRL_STATIC SIXTRL_HOST_FN bool NodeInfo_is_cuda_node_info(
        const SIXTRL_CXX_NAMESPACE::BaseNodeInfo *const SIXTRL_RESTRICT
            ptr_base ) SIXTRL_NOEXCEPT;

    SIXTRL_STATIC SIXTRL_HOST_FN CudaNodeInfo const* CudaNodeInfo_get(
        const SIXTRL_CXX_NAMESPACE::BaseNodeInfo *const SIXTRL_RESTRICT
            ptr_base ) SIXTRL_NOEXCEPT;

    SIXTRL_STATIC SIXTRL_HOST_FN CudaNodeInfo* CudaNodeInfo_get(
        SIXTRL_CXX_NAMESPACE::BaseNodeInfo* SIXTRL_RESTRICT
            ptr_base ) SIXTRL_NOEXCEPT;

} /* ns: SIXTRL_CXX_NAMESPACE */


namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE bool NodeId_is_cuda_node_id( const
        SIXTRL_CXX_NAMESPACE::NodeId *const
            SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT {
        return (  ( ptr_base != nullptr ) && ( ptr_base->backend_id() ==
            SIXTRL_CXX_NAMESPACE::BACKEND_CUDA ) ); }

    SIXTRL_INLINE CudaNodeId const* CudaNodeId_get(
        const SIXTRL_CXX_NAMESPACE::NodeId *const SIXTRL_RESTRICT
            ptr_base ) SIXTRL_NOEXCEPT {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( st::NodeId_is_cuda_node_id( ptr_base ) )
            ? static_cast< st::CudaNodeId const* >( ptr_base ) : nullptr; }

    SIXTRL_INLINE CudaNodeId* CudaNodeId_get(
        SIXTRL_CXX_NAMESPACE::NodeId* SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( st::NodeId_is_cuda_node_id( ptr_base ) )
            ? static_cast< st::CudaNodeId* >( ptr_base ) : nullptr; }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeInfo_is_cuda_node_info(
        const SIXTRL_CXX_NAMESPACE::BaseNodeInfo *const SIXTRL_RESTRICT
            ptr_base ) SIXTRL_NOEXCEPT {
        return ( ( ptr_base != nullptr ) && ( ptr_base->backend_id() ==
            SIXTRL_CXX_NAMESPACE::BACKEND_CUDA ) ); }

    SIXTRL_INLINE CudaNodeInfo const* CudaNodeInfo_get(
        const SIXTRL_CXX_NAMESPACE::BaseNodeInfo *const SIXTRL_RESTRICT
            ptr_base ) SIXTRL_NOEXCEPT {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( st::NodeInfo_is_cuda_node_info( ptr_base ) )
            ? static_cast< st::CudaNodeInfo const* >( ptr_base ) : nullptr;
    }

    SIXTRL_INLINE CudaNodeInfo* CudaNodeInfo_get(
        SIXTRL_CXX_NAMESPACE::BaseNodeInfo* SIXTRL_RESTRICT
            ptr_base ) SIXTRL_NOEXCEPT {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( st::NodeInfo_is_cuda_node_info( ptr_base ) )
            ? static_cast< st::CudaNodeInfo* >( ptr_base ) : nullptr;
    }

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */
#endif /* SIXTRACKL_ENABLE_BACKEND_CUDA */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

SIXTRL_EXPORT_API SIXTRL_HOST_FN NS(size_t) NS(Cuda_num_all_nodes)( void );

SIXTRL_EXPORT_API SIXTRL_HOST_FN NS(size_t) NS(Cuda_all_node_ids)(
    NS(NodeId)* SIXTRL_RESTRICT node_ids_begin,
    NS(size_t) const max_num_node_ids );

SIXTRL_EXPORT_API SIXTRL_HOST_FN NS(CudaNodeInfo)*
NS(CudaNodeInfo_create)( NS(node_platform_id_t) const platform_id,
                         NS(node_device_id_t) const device_id );

SIXTRL_EXPORT_API SIXTRL_HOST_FN void NS(CudaNodeInfo_delete)(
    NS(CudaNodeInfo)* SIXTRL_RESTRICT node_info );

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_NODE_H__ */
