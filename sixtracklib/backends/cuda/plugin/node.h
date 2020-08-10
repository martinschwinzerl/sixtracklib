#ifndef SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_NODE_H__
#define SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_NODE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/definitions.h"
    #include "sixtracklib_base/node/node_id.h"
    #include "sixtracklib_base/node/node_info.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class SIXTRL_EXPORT_API CudaNodeInfo :
        public SIXTRL_CXX_NAMESPACE::BaseNodeInfo
    {
        public:

        static constexpr size_type CU_COMPUTE_MODE_DEFAULT = size_type{ 0 };
        static constexpr size_type CU_COMPUTE_MODE_PROHIBITED = size_type{ 2 };
        static constexpr size_type CU_COMPUTE_MODE_EXCLUSIVE_PROCESS =
            size_type{ 3 };

        SIXTRL_STATIC SIXTRL_HOST_FN size_type NUM_ALL_NODES();

        SIXTRL_STATIC SIXTRL_HOST_FN size_type GET_ALL_NODE_IDS(
            ::NS(NodeId)* SIXTRL_RESTRICT node_ids_begin,
            size_type const max_num_node_ids );

        /*SIXTRL_HOST_FN size_type GET_NODE_IDS(
            ::NS(NodeId)* SIXTRL_RESTRICT node_ids_begin,
            size_type const max_num_node_ids,
            size_type const skip_first_num_nodes = size_type{ 0 },
            string_type const& SIXTRL_RESTRICT_REF
                env_variable_name = string_type{ "SIXTRACKLIB_DEVICES" },
            string_type const& SIXTRL_RESTRICT_REF
                config_string = string_type{} );*/

        /* ================================================================= */

        SIXTRL_HOST_FN explicit CudaNodeInfo( platform_id_t const platform_id,
            device_id_t const device_id = device_id_t{ 0 } );

        SIXTRL_HOST_FN CudaNodeInfo( CudaNodeInfo const& ) = default;
        SIXTRL_HOST_FN CudaNodeInfo( CudaNodeInfo&& ) = default;
        SIXTRL_HOST_FN CudaNodeInfo& operator=( CudaNodeInfo const& ) = default;
        SIXTRL_HOST_FN CudaNodeInfo& operator=( CudaNodeInfo&& ) = default;
        SIXTRL_HOST_FN virtual ~CudaNodeInfo() = default;

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
}

extern "C" { typedef SIXTRL_CXX_NAMESPACE::CudaNodeInfo NS(CudaNodeInfo); }

#elif !defined( _GPUCODE )

struct NS(CudaNodeInfo);

#endif /* C++ */

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
