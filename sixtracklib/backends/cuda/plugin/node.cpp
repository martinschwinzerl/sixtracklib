#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/plugin/node.h"
    #include "sixtracklib/backends/cuda/dlib.h"
    #include "sixtracklib/backends/cuda/plugin/cuda_tools.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cuda.h>
    #include <cuda_runtime_api.h>

    #if defined( __cplusplus )
        #include <iomanip>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if  defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
            ( SIXTRACKL_ENABLE_BACKEND_CUDA == 1 )

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using node_id_t         = st::CudaNodeId;
        using st_platform_id_t  = node_id_t::platform_id_t;

        using ninfo_t           = st::CudaNodeInfo;
        using st_size_t         = ninfo_t::size_type;
        using string_t          = ninfo_t::string_type;
        using st_status_t       = ninfo_t::status_t;
        using c_node_id_t       = ::NS(NodeId);
    }

    /* ********************************************************************* */
    /* ********                     CudaNodeId                      ******** */
    /* ********************************************************************* */

    st_size_t node_id_t::NUM_ALL_NODES()
    {
        int temp_num_devices = 0;
        SIXTRL_CUDA_DRIVER_API_CALL(
            ::cuDeviceGetCount, ( &temp_num_devices ) );

        SIXTRL_ASSERT( temp_num_devices >= 0 );
        return static_cast< st_size_t >( temp_num_devices );
    }

    st_size_t node_id_t::GET_ALL_NODE_IDS(
        ::NS(NodeId)* SIXTRL_RESTRICT node_ids_begin,
        st_size_t const max_num_node_ids )
    {
        st_size_t num_node_ids_added = st_size_t{ 0 };
        if( node_ids_begin == nullptr ) return num_node_ids_added;

        st_size_t const num_devices = node_id_t::NUM_ALL_NODES();
        if( num_devices > 0 )
        {
            st_size_t const nn = ( num_devices <= max_num_node_ids )
                ? num_devices : max_num_node_ids;

            for( st_size_t ii = st_size_t{ 0 } ; ii < nn ; ++ii )
            {
                SIXTRL_ASSERT( ii >= num_node_ids_added );

                ::CUdevice device;
                ::CUresult const ret = ::cuDeviceGet(
                    &device, static_cast< int >( ii ) );
                if( ret != ::CUDA_SUCCESS ) continue;

                node_ids_begin[ num_node_ids_added ].m_backend_id =
                    st::BACKEND_CUDA;

                node_ids_begin[ num_node_ids_added ].m_platform_id = ii;
                node_ids_begin[ num_node_ids_added ].m_device_id =
                    ninfo_t::device_id_t{ 0 };

                ++num_node_ids_added;
            }
        }

        if( num_node_ids_added < max_num_node_ids )
        {
            st_size_t ii = num_node_ids_added;

            for(  ; ii < max_num_node_ids ; ++ii )
            {
                node_ids_begin[ ii ].m_backend_id = st::BACKEND_ILLEGAL;
                node_ids_begin[ ii ].m_platform_id =
                    st::NODE_ILLEGAL_PLATFORM_ID;
                node_ids_begin[ ii ].m_device_id = st::NODE_ILLEGAL_DEVICE_ID;
            }
        }

        return num_node_ids_added;
    }

    /* ===================================================================== */

    constexpr node_id_t::device_handle_type
        node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE;

    /* --------------------------------------------------------------------- */

    node_id_t::CudaNodeId(
        node_id_t::device_handle_type const cuda_device_handle ) :
        st::NodeId( st::BACKEND_CUDA ),
        m_handle( node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE )
    {
        st_status_t const status =
            this->set_device_handle( cuda_device_handle );
        if( status != st::STATUS_SUCCESS ) st::NodeId::do_clear();
    }

    node_id_t::CudaNodeId( node_id_t::platform_id_t const platform_id,
        node_id_t::device_id_t const device_id  ) :
        st::NodeId( st::BACKEND_CUDA ),
        m_handle( node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE )
    {
        using dev_handle_t = node_id_t::device_handle_type;

        if( ( platform_id != st::NODE_ILLEGAL_PLATFORM_ID ) &&
            ( device_id == device_id_t{ 0 } ) )
        {
            dev_handle_t const cuda_dev_handle =
                static_cast< dev_handle_t >( platform_id );

            if( ( cuda_dev_handle != node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
                ( cuda_dev_handle >= dev_handle_t{ 0 } ) &&
                ( cuda_dev_handle < static_cast< dev_handle_t >(
                    node_id_t::NUM_ALL_NODES() ) ) )
            {
                this->as_c_node_id().m_platform_id = platform_id;
                this->as_c_node_id().m_device_id = device_id;
            }
        }
    }

    node_id_t::CudaNodeId( ::NS(NodeId) const& SIXTRL_RESTRICT_REF node_id ) :
        st::NodeId( st::BACKEND_CUDA ),
        m_handle( node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE )
    {
        using dev_handle_t = node_id_t::device_handle_type;

        if( ( ( node_id.m_backend_id == st::BACKEND_CUDA ) ||
              ( node_id.m_backend_id == st::BACKEND_UNDEFINED ) ) &&
            ( node_id.m_platform_id != st::NODE_ILLEGAL_PLATFORM_ID ) &&
            ( node_id.m_device_id == device_id_t{ 0 } ) )
        {
            dev_handle_t const cuda_dev_handle =
                static_cast< dev_handle_t >( node_id.m_platform_id );

            if( ( cuda_dev_handle != node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
                ( cuda_dev_handle >= dev_handle_t{ 0 } ) &&
                ( cuda_dev_handle < static_cast< dev_handle_t >(
                    node_id_t::NUM_ALL_NODES() ) ) )
            {
                this->as_c_node_id().m_platform_id = node_id.m_platform_id;
                this->as_c_node_id().m_device_id = node_id.m_device_id;
            }
        }
    }

    node_id_t::CudaNodeId( const ::NS(NodeId) *const SIXTRL_RESTRICT node_id ) :
        st::NodeId( st::BACKEND_CUDA ),
        m_handle( node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE )
    {
        using dev_handle_t = node_id_t::device_handle_type;

        if( ( node_id != nullptr ) &&
            ( ( node_id->m_backend_id == st::BACKEND_CUDA ) ||
              ( node_id->m_backend_id == st::BACKEND_UNDEFINED ) ) &&
            ( node_id->m_platform_id != st::NODE_ILLEGAL_PLATFORM_ID ) &&
            ( node_id->m_device_id == device_id_t{ 0 } ) )
        {
            dev_handle_t const cuda_dev_handle =
                static_cast< dev_handle_t >( node_id->m_platform_id );

            if( ( cuda_dev_handle != node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
                ( cuda_dev_handle >= dev_handle_t{ 0 } ) &&
                ( cuda_dev_handle < static_cast< dev_handle_t >(
                    node_id_t::NUM_ALL_NODES() ) ) )
            {
                this->as_c_node_id().m_platform_id = node_id->m_platform_id;
                this->as_c_node_id().m_device_id = node_id->m_device_id;
            }
        }
    }

    node_id_t::CudaNodeId(
        node_id_t::string_type const& SIXTRL_RESTRICT_REF node_id_str ) :
        st::NodeId( st::BACKEND_CUDA ),
        m_handle( node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE )
    {
        st::status_t const status = node_id_t::do_parse_device_str_cuda(
            node_id_str, this->find_device_string_format( node_id_str ) );

        if( status == st::STATUS_SUCCESS )
        {
            SIXTRL_ASSERT( this->backend_id() == st::BACKEND_CUDA );
            SIXTRL_ASSERT( this->device_id() != st::NODE_ILLEGAL_DEVICE_ID );

            if( ( this->platform_id() != st::NODE_ILLEGAL_PLATFORM_ID ) &&
                ( this->platform_id() >= st_platform_id_t{ 0 } ) &&
                ( this->platform_id() <  static_cast< st_platform_id_t >(
                    node_id_t::NUM_ALL_NODES() ) ) )
            {
                this->m_handle = this->platform_id();
            }
            else
            {
                st::NodeId::do_clear();
            }
        }
    }

    node_id_t::CudaNodeId(
        node_id_t::string_type const& SIXTRL_RESTRICT_REF node_id_str,
        node_id_t::str_format_t const node_id_str_format ) :
            st::NodeId( st::BACKEND_CUDA ),
            m_handle( node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE )
        {
            st::status_t const status = node_id_t::do_parse_device_str_cuda(
                node_id_str, node_id_str_format );

            if( status == st::STATUS_SUCCESS )
            {
                SIXTRL_ASSERT( this->backend_id() == st::BACKEND_CUDA );
                SIXTRL_ASSERT( this->device_id() != st::NODE_ILLEGAL_DEVICE_ID );

                if( ( this->platform_id() != st::NODE_ILLEGAL_PLATFORM_ID ) &&
                    ( this->platform_id() >= st_platform_id_t{ 0 } ) &&
                    ( this->platform_id() <  static_cast< st_platform_id_t >(
                        node_id_t::NUM_ALL_NODES() ) ) )
                {
                    this->m_handle = this->platform_id();
                }
                else
                {
                    st::NodeId::do_clear();
                }
            }
        }

    /* --------------------------------------------------------------------- */

    node_id_t::device_handle_type
    node_id_t::device_handle() const SIXTRL_NOEXCEPT
    {
        return this->m_handle;
    }

    st_status_t node_id_t::set_device_handle(
        node_id_t::device_handle_type const device_handle )
    {
        using dev_handle_t = node_id_t::device_handle_type;
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( device_handle != node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
            ( device_handle >= dev_handle_t{ 0 } ) &&
            ( device_handle < static_cast< dev_handle_t >(
                node_id_t::NUM_ALL_NODES() ) ) )
        {
            this->as_c_node_id().m_platform_id = device_handle;
            this->as_c_node_id().m_device_id = node_id_t::device_id_t{ 0 };
            this->m_handle = device_handle;
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    void node_id_t::do_clear() {
        this->m_handle = node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE;
        st::NodeId::do_clear();
    }

    st_status_t node_id_t::do_parse_device_str(
        node_id_t::string_type const& SIXTRL_RESTRICT_REF device_str,
        node_id_t::str_format_t const device_str_format )
    {
        return node_id_t::do_parse_device_str_cuda(
            device_str, device_str_format );
    }

    /* --------------------------------------------------------------------- */

    st_status_t node_id_t::do_parse_device_str_cuda(
        node_id_t::string_type const& SIXTRL_RESTRICT_REF device_str,
        node_id_t::str_format_t const device_str_format )
    {
        st_status_t status = st::NodeId::do_parse_device_str(
            device_str, device_str_format );

        if( ( status == st::STATUS_SUCCESS ) &&
            ( this->backend_id() == st::BACKEND_UNDEFINED ) )
        {
            this->as_c_node_id().m_backend_id = st::BACKEND_CUDA;
        }

        if( ( status == st::STATUS_SUCCESS ) &&
            ( this->backend_id() == st::BACKEND_CUDA ) &&
            ( this->platform_id() != st::NODE_ILLEGAL_PLATFORM_ID ) &&
            ( this->platform_id() >= st_platform_id_t{ 0 } ) &&
            ( this->platform_id() < static_cast< st_platform_id_t >(
                node_id_t::NUM_ALL_NODES() ) ) )
        {
            this->m_handle = static_cast< node_id_t::device_handle_type >(
                this->platform_id() );
        }
        else
        {
            st::NodeId::do_clear();
            this->m_handle = node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE;
        }

        return status;
    }

    /* ********************************************************************* */
    /* ********                     CudaNodeInfo                    ******** */
    /* ********************************************************************* */

    constexpr st_size_t ninfo_t::CU_COMPUTE_MODE_DEFAULT;
    constexpr st_size_t ninfo_t::CU_COMPUTE_MODE_PROHIBITED;
    constexpr st_size_t ninfo_t::CU_COMPUTE_MODE_EXCLUSIVE_PROCESS;

    /* ===================================================================== */

    ninfo_t::CudaNodeInfo(
        st::CudaNodeId const& SIXTRL_RESTRICT_REF cuda_node_id )  :
            SIXTRL_CXX_NAMESPACE::BaseNodeInfo(
                SIXTRL_CXX_NAMESPACE::BACKEND_CUDA )
    {
        std::unique_ptr< st::CudaNodeId > temp_node_id;

        if( cuda_node_id.backend_id() != st::BACKEND_CUDA )
        {
            temp_node_id.reset( new st::CudaNodeId(
                cuda_node_id.platform_id(), cuda_node_id.device_id() ) );
        }

        if( temp_node_id.get() == nullptr )
        {
            throw std::runtime_error( "unable to construct a CudaNodeId"
                " from constructor parameters" );
        }

        st_status_t status = this->get_device_properties(
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

    st::CudaNodeId const* ninfo_t::ptr_cuda_device() const SIXTRL_NOEXCEPT
    {
        return ( ( this->backend_id() == st::BACKEND_CUDA ) &&
                 ( this->base_node_id() != nullptr ) &&
                 ( this->base_node_id()->backend_id() == st::BACKEND_CUDA ) )
            ? static_cast< st::CudaNodeId const* >( this->base_node_id() )
            : nullptr;
    }

    st::CudaNodeId const& ninfo_t::cuda_device() const
    {
        st::CudaNodeId const* ptr = this->ptr_cuda_device();

        if( ptr == nullptr )
        {
            throw std::runtime_error( "illegal CudaNodeId for CudaNodeInfo" );
        }

        return *ptr;
    }

    /* --------------------------------------------------------------------- */

    st_size_t ninfo_t::max_block_dim_x() const SIXTRL_NOEXCEPT {
        return this->m_max_block_dim[ 0 ]; }

    st_size_t ninfo_t::max_block_dim_y() const SIXTRL_NOEXCEPT {
        return this->m_max_block_dim[ 1 ]; }

    st_size_t ninfo_t::max_block_dim_z() const SIXTRL_NOEXCEPT {
        return this->m_max_block_dim[ 2 ]; }

    st_size_t ninfo_t::max_grid_dim_x() const SIXTRL_NOEXCEPT {
        return this->m_max_grid_dim[ 0 ]; }

    st_size_t ninfo_t::max_grid_dim_y() const SIXTRL_NOEXCEPT {
        return this->m_max_grid_dim[ 1 ]; }

    st_size_t ninfo_t::max_grid_dim_z() const SIXTRL_NOEXCEPT {
        return this->m_max_grid_dim[ 2 ]; }

    st_size_t ninfo_t::max_blocks_per_multiprocessor() const SIXTRL_NOEXCEPT {
        return this->m_max_blocks_per_mp; }

    st_size_t ninfo_t::max_threads_per_block() const SIXTRL_NOEXCEPT {
        return this->m_max_threads_per_block; }

    st_size_t ninfo_t::max_threads_per_multiprocessor() const SIXTRL_NOEXCEPT {
        return this->m_max_threads_per_mp; }

    st_size_t ninfo_t::max_shared_mem_per_block() const SIXTRL_NOEXCEPT {
        return this->m_max_shared_mem_per_block; }

    st_size_t ninfo_t::reserved_shared_mem_per_block() const SIXTRL_NOEXCEPT {
        return this->m_reserved_shared_mem_per_block; }

    st_size_t ninfo_t::max_shared_mem_per_multiprocessor() const SIXTRL_NOEXCEPT{
        return this->m_max_shared_mem_per_mp; }

    st_size_t ninfo_t::max_registers_per_block() const SIXTRL_NOEXCEPT {
        return this->m_max_i32_registers_per_block; }

    st_size_t ninfo_t::max_registers_per_multiprocessor() const SIXTRL_NOEXCEPT {
        return this->m_max_i32_registers_per_mp; }

    st_size_t ninfo_t::total_memory() const SIXTRL_NOEXCEPT {
        return this->m_total_memory; }

    st_size_t ninfo_t::total_const_memory() const SIXTRL_NOEXCEPT {
        return this->m_total_const_memory; }

    st_size_t ninfo_t::clock_rate_khz() const SIXTRL_NOEXCEPT {
        return this->m_clock_rate_khz; }

    st_size_t ninfo_t::memory_clock_rate_khz() const SIXTRL_NOEXCEPT {
        return this->m_memory_clock_rate_khz; }

    st_size_t ninfo_t::global_memory_bus_width() const SIXTRL_NOEXCEPT {
        return this->m_global_memory_bus_width; }

    st_size_t ninfo_t::max_pitch() const SIXTRL_NOEXCEPT {
            return this->m_max_pitch; }

    st_size_t ninfo_t::texture_alignment() const SIXTRL_NOEXCEPT {
        return this->m_texture_alignment; }

    st_size_t ninfo_t::texture_pitch_alignment() const SIXTRL_NOEXCEPT {
        return this->m_texture_pitch_alignment; }

    st_size_t ninfo_t::compute_capability_major() const SIXTRL_NOEXCEPT {
        return this->m_compute_capability_major; }

    st_size_t ninfo_t::compute_capability_minor() const SIXTRL_NOEXCEPT {
        return this->m_compute_capability_minor; }

    st_size_t ninfo_t::compute_capability() const SIXTRL_NOEXCEPT {
        return this->m_compute_capability_minor + st_size_t{ 10 } *
            this->m_compute_capability_major; }

    st_size_t ninfo_t::warp_size() const SIXTRL_NOEXCEPT {
        return this->m_warp_size; }

    st_size_t ninfo_t::single_to_double_perf_ratio() const SIXTRL_NOEXCEPT {
        return this->m_single_to_double_perf_ratio; }

    st_size_t ninfo_t::multiprocessor_count() const SIXTRL_NOEXCEPT {
        return this->m_mp_count; }

    st_size_t ninfo_t::l2_cache_size() const SIXTRL_NOEXCEPT {
        return this->m_l2_cache_size; }

    st_size_t ninfo_t::max_persisting_l2_cache_size() const SIXTRL_NOEXCEPT {
        return this->m_max_persisting_l2_cache_size; }

    st_size_t ninfo_t::multi_gpu_board_group_id() const SIXTRL_NOEXCEPT {
        return this->m_multi_gpu_board_group_id; }

    st_size_t ninfo_t::compute_mode() const SIXTRL_NOEXCEPT {
        return this->m_compute_mode; }

    bool ninfo_t::is_in_default_compute_mode() const SIXTRL_NOEXCEPT {
        return this->m_compute_mode == ninfo_t::CU_COMPUTE_MODE_DEFAULT; }

    bool ninfo_t::is_in_prohibited_compute_mode() const SIXTRL_NOEXCEPT {
        return this->m_compute_mode == ninfo_t::CU_COMPUTE_MODE_PROHIBITED; }

    bool ninfo_t::is_in_exclusive_process_compute_mode() const SIXTRL_NOEXCEPT {
        return ( this->m_compute_mode ==
                 ninfo_t::CU_COMPUTE_MODE_EXCLUSIVE_PROCESS );
    }

    bool ninfo_t::has_kernel_exec_timeout() const SIXTRL_NOEXCEPT {
        return this->m_has_kernel_exec_timeout; }

    bool ninfo_t::uses_tcc_driver() const SIXTRL_NOEXCEPT {
        return this->m_uses_tcc_driver; }

    bool ninfo_t::is_integrated() const SIXTRL_NOEXCEPT {
        return this->m_is_integrated; }

    bool ninfo_t::is_on_multi_gpu_board() const SIXTRL_NOEXCEPT {
        return this->m_is_on_multi_gpu_board; }

    bool ninfo_t::supports_overlap_mem_xfer_kernel_exec() const SIXTRL_NOEXCEPT {
        return this->m_supports_overlap_mem_xfer_kernel_exec; }

    bool ninfo_t::can_map_host_memory() const SIXTRL_NOEXCEPT {
        return this->m_can_map_host_mem; }

    bool ninfo_t::supports_pageable_mem_access() const SIXTRL_NOEXCEPT {
        return this->m_supports_pageable_mem_access; }

    bool ninfo_t::supports_pageable_mem_access_via_host_page_tables(
        ) const SIXTRL_NOEXCEPT {
        return this->m_supports_pageable_mem_access_via_host_page_tables; }

    bool ninfo_t::supports_concurrent_managed_mem_access() const SIXTRL_NOEXCEPT
    {
        return this->m_supports_concurrent_managed_mem_access;
    }

    bool ninfo_t::supports_ecc() const SIXTRL_NOEXCEPT {
        return this->m_supports_ecc; }

    bool ninfo_t::supports_concurrent_kernel_exec() const SIXTRL_NOEXCEPT {
        return this->m_supports_concurrent_kernel_exec; }

    bool ninfo_t::supports_compute_preemption() const SIXTRL_NOEXCEPT {
        return this->m_supports_compute_preemption; }

    bool ninfo_t::supports_global_l1_caching() const SIXTRL_NOEXCEPT {
        return this->m_supports_global_l1_cache; }

    bool ninfo_t::supports_local_l1_caching() const SIXTRL_NOEXCEPT {
        return this->m_supports_local_l1_cache; }

    bool ninfo_t::supports_host_native_atomics() const SIXTRL_NOEXCEPT {
        return this->m_supports_host_native_atomic; }

    bool ninfo_t::supports_unified_addressing() const SIXTRL_NOEXCEPT {
        return this->m_supports_unified_addressing; }

    bool ninfo_t::supports_generic_compression() const SIXTRL_NOEXCEPT {
        return this->m_supports_generic_compression; }

    bool ninfo_t::supports_virtual_address_management() const SIXTRL_NOEXCEPT {
        return this->m_supports_virtual_address_management; }

    bool
    ninfo_t::supports_direct_managed_mem_accesss_from_host() const SIXTRL_NOEXCEPT
    {
        return this->m_supports_direct_managed_mem_accesss_from_host;
    }

    bool ninfo_t::can_use_host_ptr_for_registered_mem() const SIXTRL_NOEXCEPT {
        return this->m_can_use_host_ptr_for_registered_mem; }

    void ninfo_t::do_print_extended_section(
        std::ostream& SIXTRL_RESTRICT_REF ostr,
        ninfo_t::print_flags_t const flags ) const
    {
        st::BaseNodeInfo::do_print_extended_section( ostr, flags );

        ostr << "compute capability     : "
             << this->m_compute_capability_major << "."
             << this->m_compute_capability_minor << "\r\n"
             << "total memory           : "
             << this->m_total_memory << " Bytes\r\n"
             << "warp size              : "
             << this->m_warp_size << "\r\n"
             << "max block dims         : [ "
             << std::setw( 8 ) << this->m_max_block_dim[ 0 ] << ", "
             << std::setw( 8 ) << this->m_max_block_dim[ 1 ] << ", "
             << std::setw( 8 ) << this->m_max_block_dim[ 2 ] << " ]\r\n"
             << "max grid dims          : [ "
             << std::setw( 8 ) << this->m_max_grid_dim[ 0 ] << ", "
             << std::setw( 8 ) << this->m_max_grid_dim[ 1 ] << ", "
             << std::setw( 8 ) << this->m_max_grid_dim[ 2 ] << " ]\r\n"
             << "max threads per block  : "
             << this->m_max_threads_per_block << "\r\n";
    }

    void ninfo_t::clear_device_properties() SIXTRL_NOEXCEPT
    {
        this->set_platform_name( "" );
        this->set_device_name( "" );
        this->set_description( "" );

        this->m_max_block_dim[ 0 ] = this->m_max_block_dim[ 1 ] =
        this->m_max_block_dim[ 2 ] = size_type{ 0 };

        this->m_max_grid_dim[ 0 ] = this->m_max_grid_dim[ 1 ] =
        this->m_max_grid_dim[ 2 ] = size_type{ 0 };

        this->m_compute_capability_major = size_type{ 0 };
        this->m_compute_capability_minor = size_type{ 0 };
        this->m_warp_size = size_type{ 0 };
        this->m_mp_count = size_type{ 0 };
        this->m_total_memory = size_type{ 0 };

        this->m_max_blocks_per_mp = size_type{ 0 };
        this->m_max_threads_per_block = size_type{ 0 };
        this->m_max_threads_per_mp = size_type{ 0 };
        this->m_max_shared_mem_per_block = size_type{ 0 };
        this->m_reserved_shared_mem_per_block = size_type{ 0 };
        this->m_max_shared_mem_per_mp = size_type{ 0 };
        this->m_max_i32_registers_per_block = size_type{ 0 };
        this->m_max_i32_registers_per_mp = size_type{ 0 };
        this->m_total_const_memory = size_type{ 0 };
        this->m_clock_rate_khz = size_type{ 0 };
        this->m_memory_clock_rate_khz = size_type{ 0 };
        this->m_global_memory_bus_width = size_type{ 0 };
        this->m_max_pitch = size_type{ 0 };
        this->m_texture_alignment = size_type{ 0 };
        this->m_texture_pitch_alignment = size_type{ 0 };
        this->m_single_to_double_perf_ratio = size_type{ 0 };
        this->m_l2_cache_size = size_type{ 0 };
        this->m_max_persisting_l2_cache_size = size_type{ 0 };
        this->m_compute_mode = size_type{ 0 };
        this->m_multi_gpu_board_group_id = size_type{ 0 };

        this->m_has_kernel_exec_timeout = false;
        this->m_uses_tcc_driver = false;
        this->m_is_integrated = false;
        this->m_is_on_multi_gpu_board = false;
        this->m_can_map_host_mem= false;
        this->m_supports_ecc = false;
        this->m_supports_overlap_mem_xfer_kernel_exec = false;
        this->m_supports_concurrent_kernel_exec = false;
        this->m_supports_concurrent_managed_mem_access = false;
        this->m_supports_pageable_mem_access = false;
        this->m_supports_pageable_mem_access_via_host_page_tables = false;
        this->m_supports_managed_mem = false;
        this->m_supports_compute_preemption = false;
        this->m_supports_global_l1_cache = false;
        this->m_supports_local_l1_cache = false;
        this->m_supports_host_native_atomic = false;
        this->m_supports_unified_addressing = false;
        this->m_supports_generic_compression = false;
        this->m_supports_virtual_address_management = false;
        this->m_supports_direct_managed_mem_accesss_from_host = false;
        this->m_can_use_host_ptr_for_registered_mem = false;
    }

    st_status_t ninfo_t::get_device_properties(
        ninfo_t::platform_id_t const platform_id,
        ninfo_t::device_id_t const device_id )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        #if defined( CUDART_VERSION ) && ( CUDART_VERSION >= 7050 )
        if( ( platform_id == st::NODE_ILLEGAL_PLATFORM_ID ) ||
            ( device_id == st::NODE_ILLEGAL_DEVICE_ID ) ||
            ( static_cast< st_size_t >( platform_id ) >=
              st::CudaNodeId::NUM_ALL_NODES() ) )
        {
            return status;
        }

        /* NOTE: Check whether this is general enough? */
        if( device_id != ninfo_t::device_id_t{ 0 } ) return status;

        int cuda_driver_version = 0;
        ::CUresult ret = ::cuDriverGetVersion( &cuda_driver_version );
        if( ret != ::CUDA_SUCCESS ) return ::NS(Cuda_curesult_to_status)( ret );

        constexpr st_size_t TEMP_STRING_CAPACITY =
            st_size_t{ 128 };

        constexpr st_size_t MAX_TEMP_STRING_LEN =
            TEMP_STRING_CAPACITY - st_size_t{ 1 };

        char temp_string[ TEMP_STRING_CAPACITY ];
        std::memset( &temp_string[ 0 ], ( int )'\0', TEMP_STRING_CAPACITY );
        int cnt = std::snprintf( temp_string, MAX_TEMP_STRING_LEN,
            "CUDA v%d.%d driver API [%d]", ( int )( CUDART_VERSION / 1000 ),
                ( int )( ( CUDART_VERSION % 100 ) / 10 ), cuda_driver_version );
        if( cnt >= MAX_TEMP_STRING_LEN ) return st::STATUS_GENERAL_FAILURE;

        ::CUdevice device;
        status = this->set_platform_name( temp_string );
        if( status == st::STATUS_SUCCESS )
        {
            ret = ::cuDeviceGet( &device, static_cast< int >( platform_id ) );
            status = ::NS(Cuda_curesult_to_status)( ret );
        }

        if( status == st::STATUS_SUCCESS )
        {
            status = st::STATUS_GENERAL_FAILURE;
            std::memset( temp_string, ( int )'\0', TEMP_STRING_CAPACITY );
            ret = ::cuDeviceGetName( temp_string, MAX_TEMP_STRING_LEN, device );

            if( ret == ::CUDA_SUCCESS )
            {
                status = this->set_device_name( temp_string );
            }
        }

        /* m_compute_capability_major */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MAJOR, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_compute_capability_major = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_compute_capability_minor */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MINOR, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_compute_capability_minor = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_warp_size */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_WARP_SIZE, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_warp_size = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_mp_count */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_mp_count = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_total_memory: */
        if( status == st::STATUS_SUCCESS )
        {
            status = st::STATUS_GENERAL_FAILURE;
            ::size_t total_mem_size = ::size_t{ 0 };
            ret = ::cuDeviceTotalMem( &total_mem_size, device );

            if( ret == ::CUDA_SUCCESS )
            {
                this->m_total_memory = total_mem_size;
                status = st::STATUS_SUCCESS;
            }
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* m_max_block_dim: */

        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_X, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_block_dim[ 0 ] = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Y, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_block_dim[ 1 ] = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Z, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_block_dim[ 2 ] = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* m_max_grid_dim: */

        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_X, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_grid_dim[ 0 ] = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Y, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_block_dim[ 1 ] = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Z, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_block_dim[ 2 ] = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_total_const_memory */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_TOTAL_CONSTANT_MEMORY, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_total_const_memory = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_clock_rate_khz */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_CLOCK_RATE, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_clock_rate_khz = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_memory_clock_rate_khz */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_memory_clock_rate_khz = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_global_memory_bus_width */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_GLOBAL_MEMORY_BUS_WIDTH, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_memory_clock_rate_khz = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_max_pitch */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_PITCH, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_pitch = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_texture_alignment */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_texture_alignment = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_texture_pitch_alignment */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_TEXTURE_PITCH_ALIGNMENT, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_texture_pitch_alignment = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        #if CUDART_VERSION >= 11000

        /* m_max_blocks_per_mp: */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_BLOCKS_PER_MULTIPROCESSOR:,
                device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_blocks_per_mp = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_reserved_shared_mem_per_block: */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_RESERVED_SHARED_MEMORY_PER_BLOCK:,
                device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_reserved_shared_mem_per_block = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_max_persisting_l2_cache_size */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_PERSISTING_L2_CACHE_SIZE, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_persisting_l2_cache_size = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_generic_compression */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_GENERIC_COMPRESSION_SUPPORTED, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_generic_compression = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_virtual_address_management */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_VIRTUAL_ADDRESS_MANAGEMENT_SUPPORTED,
                    device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_unified_addressing = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        #endif /* cuda 11.0 */

         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        #if CUDART_VERSION >= 10000

        /* m_supports_pageable_mem_access_via_host_page_tables: */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
            ::CU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS_USES_HOST_PAGE_TABLES,
                device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_pageable_mem_access_via_host_page_tables =
                    ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_direct_managed_mem_accesss_from_host: */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_DIRECT_MANAGED_MEM_ACCESS_FROM_HOST,
                    device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_direct_managed_mem_accesss_from_host =
                    ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        #endif /* cuda 10.0 */

        #if CUDART_VERSION >= 8000
        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        /* m_max_threads_per_block: */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_BLOCK, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_threads_per_block = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_max_threads_per_mp: */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_MULTIPROCESSOR, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_threads_per_mp = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_max_shared_mem_per_block: */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_shared_mem_per_block = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_max_shared_mem_per_mp: */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_MULTIPROCESSOR,
                    device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_shared_mem_per_block = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_max_i32_registers_per_block: */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_BLOCK, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_i32_registers_per_block = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_max_i32_registers_per_mp: */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_MULTIPROCESSOR,
                    device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_max_i32_registers_per_mp = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_single_to_double_perf_ratio */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_SINGLE_TO_DOUBLE_PRECISION_PERF_RATIO,
                    device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_single_to_double_perf_ratio = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_l2_cache_size */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_L2_CACHE_SIZE, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_l2_cache_size = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_compute_mode */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_COMPUTE_MODE, device );
            if( ret == ::CUDA_SUCCESS )
            {
                st_size_t const compute_mode = static_cast< st_size_t >( temp );

                if( ( compute_mode == ninfo_t::CU_COMPUTE_MODE_DEFAULT ) ||
                    ( compute_mode == ninfo_t::CU_COMPUTE_MODE_PROHIBITED ) ||
                    ( compute_mode ==
                        ninfo_t::CU_COMPUTE_MODE_EXCLUSIVE_PROCESS ) )
                {
                    this->m_compute_mode = compute_mode;
                    status = st::STATUS_SUCCESS;
                }
            }
        }

        /* m_multi_gpu_board_group_id */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MULTI_GPU_BOARD_GROUP_ID, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_multi_gpu_board_group_id = temp;
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_has_kernel_exec_timeout */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_KERNEL_EXEC_TIMEOUT, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_has_kernel_exec_timeout = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_uses_tcc_driver */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_TCC_DRIVER, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_uses_tcc_driver = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_is_integrated */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_INTEGRATED, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_is_integrated = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_is_on_multi_gpu_board */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MULTI_GPU_BOARD, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_is_on_multi_gpu_board = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_can_map_host_mem */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_CAN_MAP_HOST_MEMORY, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_can_map_host_mem = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_ecc */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_ECC_ENABLED, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_ecc = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_overlap_mem_xfer_kernel_exec */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_GPU_OVERLAP, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_overlap_mem_xfer_kernel_exec = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_concurrent_kernel_exec */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_CONCURRENT_KERNELS, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_concurrent_kernel_exec = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_concurrent_managed_mem_access */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_concurrent_managed_mem_access = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_pageable_mem_access */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_pageable_mem_access = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_managed_mem */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_MANAGED_MEMORY, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_managed_mem = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_compute_preemption */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_COMPUTE_PREEMPTION_SUPPORTED, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_compute_preemption = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_global_l1_cache */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_GLOBAL_L1_CACHE_SUPPORTED, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_global_l1_cache = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_local_l1_cache */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_LOCAL_L1_CACHE_SUPPORTED, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_local_l1_cache = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_host_native_atomic */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_HOST_NATIVE_ATOMIC_SUPPORTED, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_host_native_atomic = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_supports_unified_addressing */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING, device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_supports_unified_addressing = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        /* m_can_use_host_ptr_for_registered_mem */
        if( status == st::STATUS_SUCCESS )
        {
            int temp = 0;
            status = st::STATUS_GENERAL_FAILURE;
            ret = ::cuDeviceGetAttribute( &temp,
                ::CU_DEVICE_ATTRIBUTE_CAN_USE_HOST_POINTER_FOR_REGISTERED_MEM,
                    device );
            if( ret == ::CUDA_SUCCESS )
            {
                this->m_can_use_host_ptr_for_registered_mem = ( temp == 1 );
                status = st::STATUS_SUCCESS;
            }
        }

        #endif /* Cuda 8.0 */

        #endif /* CUDART_VERSION suitable */
        return status;
    }
} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* SIXTRACKL_ENABLE_BACKEND_CUDA */

#if defined( SIXTRL_CUDA_PLUGIN_BUILT ) && ( SIXTRL_CUDA_PLUGIN_BUILT == 1 )

::NS(size_t) NS(Cuda_num_all_nodes)( void )
{
    return SIXTRL_CXX_NAMESPACE::CudaNodeId::NUM_ALL_NODES();
}

::NS(size_t) NS(Cuda_all_node_ids)(
    ::NS(NodeId)* SIXTRL_RESTRICT node_ids_begin,
    ::NS(size_t) const max_num_node_ids )
{
    return SIXTRL_CXX_NAMESPACE::CudaNodeId::GET_ALL_NODE_IDS(
        node_ids_begin, max_num_node_ids );
}

::NS(BaseNodeId)* NS(CudaNodeId_create)(
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    return new SIXTRL_CXX_NAMESPACE::CudaNodeId( platform_id, device_id );
}

::NS(BaseNodeId)* NS(CudaNodeId_create_from_device_handle)(
    ::NS(cuda_device_handle_type) const cuda_dev_handle )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    std::unique_ptr< ::NS(BaseNodeId) > temp{ nullptr };

    if( cuda_dev_handle != st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE )
    {
        temp.reset( new st::CudaNodeId( cuda_dev_handle ) );

        if( ( temp.get() != nullptr ) &&
            ( ( temp->platform_id() != st::BACKEND_CUDA ) ||
              ( !temp->is_legal() ) ||
              ( st::CudaNodeId_get( temp.get() )->device_handle() !=
                st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE ) ) )
        {
            temp.reset();
        }
    }

    return temp.release();
}

::NS(BaseNodeId)* NS(CudaNodeId_create_from_string)(
    char const* SIXTRL_RESTRICT node_id_str )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    std::unique_ptr< ::NS(BaseNodeId) > temp{ nullptr };

    if( ( node_id_str != nullptr ) &&
        ( std::strlen( node_id_str ) > st_size_t{ 0 } ) )
    {
        temp.reset( new SIXTRL_CXX_NAMESPACE::CudaNodeId( node_id_str ) );

        if( ( temp.get() != nullptr ) &&
            ( ( temp->backend_id() != st::BACKEND_CUDA ) ||
              ( !temp->is_legal() ) ) )
        {
            temp.reset();
        }
    }

    return temp.release();
}

::NS(BaseNodeId)* NS(CudaNodeId_create_from_string_detailed)(
    char const* SIXTRL_RESTRICT node_id_str,
    ::NS(node_id_str_fmt_t) const format )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    std::unique_ptr< ::NS(CudaNodeId) > temp{ nullptr };

    if( ( node_id_str != nullptr ) &&
        ( std::strlen( node_id_str ) > st_size_t{ 0 } ) )
    {
        temp.reset( new st::CudaNodeId( node_id_str, format ) );

        if( ( temp.get() != nullptr ) &&
            ( ( temp->backend_id() != st::BACKEND_CUDA ) ||
              ( !temp->is_legal() ) ) )
        {
            temp.reset();
        }
    }

    return temp.release();
}

::NS(cuda_device_handle_type) NS(CudaNodeId_device_handle)(
    const ::NS(BaseNodeId) *const SIXTRL_RESTRICT node_id ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::CudaNodeId const* cuda_node_id = st::CudaNodeId_get( node_id );

    return ( cuda_node_id != nullptr )
        ? cuda_node_id->device_handle()
        : st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE;
}

::NS(status_t) NS(CudaNodeId_set_device_handle)(
    ::NS(BaseNodeId)* SIXTRL_RESTRICT node_id,
    ::NS(cuda_device_handle_type) const device_handle )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::CudaNodeId* cuda_node_id = st::CudaNodeId_get( node_id );

    return ( cuda_node_id != nullptr )
        ? cuda_node_id->set_device_handle( device_handle )
        : st::STATUS_GENERAL_FAILURE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(BaseNodeInfo)* NS(CudaNodeInfo_create)(
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    return new SIXTRL_CXX_NAMESPACE::CudaNodeInfo( platform_id, device_id );
}

#else /* !SIXTRL_CUDA_PLUGIN_BUILT */

::NS(size_t) NS(Cuda_num_all_nodes)( void )
{
    return ::NS(size_t){ 0 };
}

::NS(size_t) NS(Cuda_all_node_ids)(
    ::NS(NodeId)* SIXTRL_RESTRICT SIXTRL_UNUSED( node_ids_begin ),
    ::NS(size_t) const SIXTRL_UNUSED( max_num_node_ids ) )
{
    return ::NS(size_t){ 0 };
}

::NS(BaseNodeId)* NS(CudaNodeId_create)(
    ::NS(node_platform_id_t) const SIXTRL_UNUSED( platform_id ),
    ::NS(node_device_id_t) const SIXTRL_UNUSED( device_id ) )
{
    return nullptr;
}

::NS(BaseNodeId)* NS(CudaNodeId_create_from_device_handle)(
    ::NS(cuda_device_handle_type) const SIXTRL_UNUSED( cuda_dev_handle ) )
{
    return nullptr;
}

::NS(BaseNodeId)* NS(CudaNodeId_create_from_string)(
    char const* SIXTRL_RESTRICT SIXTRL_UNUSED( node_id_str ) )
{
    return nullptr;
}

::NS(BaseNodeId)* NS(CudaNodeId_create_from_string_detailed)(
    char const* SIXTRL_RESTRICT SIXTRL_UNUSED( node_id_str ),
    ::NS(node_id_str_fmt_t) const SIXTRL_UNUSED( format ) )
{
    return nullptr;
}

::NS(BaseNodeInfo)* NS(CudaNodeInfo_create)(
    ::NS(node_platform_id_t) const SIXTRL_UNUSED( platform_id ),
    ::NS(node_device_id_t) const SIXTRL_UNUSED( device_id ) )
{
    return nullptr;
}

#endif /* SIXTRL_CUDA_PLUGIN_BUILT */
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
