#include "sixtracklib/opencl/internal/base_context.h"

#if !defined( __CUDACC__ )

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <fstream>
#include <iterator>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/generated/path.h"
#include "sixtracklib/common/context/compute_arch.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/debug_register.h"

#include "sixtracklib/opencl/cl.h"
#include "sixtracklib/opencl/argument.h"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        using _this_t = st::clContextBase;
    }

    ClContextBase::kernel_arg_type_t const ClContextBase::ARG_TYPE_NONE =
        ClContextBase::kernel_arg_type_t{ 0x00000000 };

    ClContextBase::kernel_arg_type_t const ClContextBase::ARG_TYPE_VALUE =
        ClContextBase::kernel_arg_type_t{ 0x00000001 };

    ClContextBase::kernel_arg_type_t const ClContextBase::ARG_TYPE_RAW_PTR =
        ClContextBase::kernel_arg_type_t{ 0x00000002 };

    ClContextBase::kernel_arg_type_t const ClContextBase::ARG_TYPE_INVALID =
        ClContextBase::kernel_arg_type_t{ 0xffffffff };

    ClContextBase::ClContextBase(
        const char *const SIXTRL_RESTRICT config_str ) :
        m_cl_programs(),
        m_cl_kernels(),
        m_cl_buffers(),
        m_available_nodes_id(),
        m_available_nodes_info(),
        m_available_devices(),
        m_program_data(),
        m_kernel_data(),
        m_default_program_path_prefix( ::NS(PATH_TO_BASE_DIR) ),
        m_default_compile_options(),
        m_config_str(),
        m_cl_context(),
        m_cl_queue(),
        m_cl_status_flag_buffer(),
        m_remap_program_id( ClContextBase::program_id_t{ -1 } ),
        m_remap_kernel_id( ClContextBase::kernel_id_t{ -1 } ),
        m_selected_node_index( int64_t{ -1 } ),
        m_default_kernel_arg( uint64_t{ 0 } ),
        m_debug_mode( false )
    {
        _this_t::UpdateAvailableNodes(
            this->m_available_nodes_id, this->m_available_nodes_info,
            this->m_available_devices );

        SIXTRL_ASSERT( this->m_available_nodes_id.size() ==
                       this->m_available_nodes_info.size() );

        this->doInitDefaultProgramsBaseImpl();

        this->doSetConfigStr( config_str );

        if( this->configStr() != nullptr )
        {
            this->doParseConfigStringBaseImpl( this->configStr() );
        }

        this->m_default_program_path_prefix += "sixtracklib/opencl/kernels/";
    }

    ClContextBase::ClContextBase(
        ClContextBase::size_type const node_index,
        const char *const SIXTRL_RESTRICT config_str ) :
        m_cl_programs(),
        m_cl_kernels(),
        m_cl_buffers(),
        m_available_nodes_id(),
        m_available_nodes_info(),
        m_available_devices(),
        m_program_data(),
        m_kernel_data(),
        m_default_program_path_prefix( ::NS(PATH_TO_BASE_DIR) ),
        m_default_compile_options(),
        m_config_str(),
        m_cl_context(),
        m_cl_queue(),
        m_cl_status_flag_buffer(),
        m_remap_program_id( ClContextBase::program_id_t{ -1 } ),
        m_remap_kernel_id( ClContextBase::kernel_id_t{ -1 } ),
        m_selected_node_index( int64_t{ -1 } ),
        m_default_kernel_arg( uint64_t{ 0 } ),
        m_debug_mode( false )
    {
        _this_t::UpdateAvailableNodes(
            this->m_available_nodes_id, this->m_available_nodes_info,
            this->m_available_devices );

        this->doSetConfigStr( config_str );

        if( this->configStr() != nullptr )
        {
            this->doParseConfigStringBaseImpl( this->configStr() );
        }

        SIXTRL_ASSERT( this->m_available_nodes_id.size() ==
                       this->m_available_nodes_info.size() );

        SIXTRL_ASSERT( this->m_available_devices.size() ==
                       this->m_available_nodes_id.size() );

        this->doInitDefaultProgramsBaseImpl();

        if( ( node_index < this->numAvailableNodes() ) &&
            ( this->doSelectNodeBaseImpl( node_index ) ) )
        {
            this->doInitDefaultKernels();
        }

        this->m_default_program_path_prefix += "sixtracklib/opencl/kernels/";
    }

    ClContextBase::ClContextBase(
        ClContextBase::node_id_t const node_id,
        const char *const SIXTRL_RESTRICT config_str ) :
        m_cl_programs(),
        m_cl_kernels(),
        m_cl_buffers(),
        m_available_nodes_id(),
        m_available_nodes_info(),
        m_available_devices(),
        m_program_data(),
        m_kernel_data(),
        m_default_program_path_prefix( ::NS(PATH_TO_BASE_DIR) ),
        m_default_compile_options(),
        m_config_str(),
        m_cl_context(),
        m_cl_queue(),
        m_cl_status_flag_buffer(),
        m_remap_program_id( ClContextBase::program_id_t{ -1 } ),
        m_remap_kernel_id( ClContextBase::kernel_id_t{ -1 } ),
        m_selected_node_index( int64_t{ -1 } ),
        m_default_kernel_arg( uint64_t{ 0 } ),
        m_debug_mode( false )
    {
        _this_t::UpdateAvailableNodes(
            this->m_available_nodes_id, this->m_available_nodes_info,
            this->m_available_devices );

        SIXTRL_ASSERT( this->m_available_nodes_id.size() ==
                       this->m_available_nodes_info.size() );

        SIXTRL_ASSERT( this->m_available_devices.size() ==
                       this->m_available_nodes_id.size() );

        this->doSetConfigStr( config_str );

        if( this->configStr() != nullptr )
        {
            this->doParseConfigStringBaseImpl( this->configStr() );
        }

        this->doInitDefaultProgramsBaseImpl();

        size_type const node_index = this->findAvailableNodesIndex(
            NS(ComputeNodeId_get_platform_id)( &node_id ),
            NS(ComputeNodeId_get_device_id)( &node_id ) );

        if( ( node_index < this->numAvailableNodes() ) &&
            ( this->doSelectNodeBaseImpl( node_index ) ) )
        {
            this->doInitDefaultKernels();
        }

        this->m_default_program_path_prefix += "sixtracklib/opencl/kernels/";
    }

    ClContextBase::ClContextBase(
        char const* node_id_str,
        const char *const SIXTRL_RESTRICT config_str ) :
        m_cl_programs(),
        m_cl_kernels(),
        m_cl_buffers(),
        m_available_nodes_id(),
        m_available_nodes_info(),
        m_available_devices(),
        m_program_data(),
        m_kernel_data(),
        m_default_program_path_prefix( ::NS(PATH_TO_BASE_DIR) ),
        m_default_compile_options(),
        m_config_str(),
        m_cl_context(),
        m_cl_queue(),
        m_cl_status_flag_buffer(),
        m_remap_program_id( ClContextBase::program_id_t{ -1 } ),
        m_remap_kernel_id( ClContextBase::kernel_id_t{ -1 } ),
        m_selected_node_index( int64_t{ -1 } ),
        m_default_kernel_arg( uint64_t{ 0 } ),
        m_debug_mode( false )
    {
        _this_t::UpdateAvailableNodes(
            this->m_available_nodes_id, this->m_available_nodes_info,
            this->m_available_devices );

        SIXTRL_ASSERT( this->m_available_nodes_id.size() ==
                       this->m_available_nodes_info.size() );

        SIXTRL_ASSERT( this->m_available_devices.size() ==
                       this->m_available_nodes_id.size() );

        this->doSetConfigStr( config_str );

        if( this->configStr() != nullptr )
        {
            this->doParseConfigStringBaseImpl( this->configStr() );
        }

        this->doInitDefaultProgramsBaseImpl();

        size_type const node_index =
            this->findAvailableNodesIndex( node_id_str );

        if( ( node_index < this->numAvailableNodes() ) &&
            ( this->doSelectNodeBaseImpl( node_index ) ) )
        {
            this->doInitDefaultKernels();
        }

        this->m_default_program_path_prefix += "sixtracklib/opencl/kernels/";
    }

    ClContextBase::ClContextBase(
        ClContextBase::platform_id_t const platform_idx,
        ClContextBase::device_id_t const device_idx,
        const char *const SIXTRL_RESTRICT config_str ) :
        m_cl_programs(),
        m_cl_kernels(),
        m_cl_buffers(),
        m_available_nodes_id(),
        m_available_nodes_info(),
        m_available_devices(),
        m_program_data(),
        m_kernel_data(),
        m_default_program_path_prefix( ::NS(PATH_TO_BASE_DIR) ),
        m_default_compile_options(),
        m_config_str(),
        m_cl_context(),
        m_cl_queue(),
        m_cl_status_flag_buffer(),
        m_remap_program_id( ClContextBase::program_id_t{ -1 } ),
        m_remap_kernel_id( ClContextBase::kernel_id_t{ -1 } ),
        m_selected_node_index( int64_t{ -1 } ),
        m_default_kernel_arg( uint64_t{ 0 } ),
        m_debug_mode( false )
    {
        _this_t::UpdateAvailableNodes(
            this->m_available_nodes_id, this->m_available_nodes_info,
            this->m_available_devices );

        SIXTRL_ASSERT( this->m_available_nodes_id.size() ==
                       this->m_available_nodes_info.size() );

        SIXTRL_ASSERT( this->m_available_devices.size() ==
                       this->m_available_nodes_id.size() );

        this->doSetConfigStr( config_str );

        if( this->configStr() != nullptr )
        {
            this->doParseConfigStringBaseImpl( this->configStr() );
        }

        this->doInitDefaultProgramsBaseImpl();

        size_type const node_index =
            this->findAvailableNodesIndex( platform_idx, device_idx );

        if( ( node_index < this->numAvailableNodes() ) &&
            ( this->doSelectNodeBaseImpl( node_index ) ) )
        {
            this->doInitDefaultKernels();
        }

        this->m_default_program_path_prefix += "sixtracklib/opencl/kernels/";
    }

    ClContextBase::~ClContextBase() SIXTRL_NOEXCEPT
    {
        if( !this->m_available_nodes_info.empty() )
        {
            for( auto& nodes_info : this->m_available_nodes_info )
            {
                NS(ComputeNodeInfo_free)( &nodes_info );
            }

            this->m_available_nodes_info.clear();
        }
    }

    cl::Buffer const&
    ClContextBase::internalSuccessFlagBuffer() const SIXTRL_NOEXCEPT
    {
        return this->m_cl_status_flag_buffer;
    }

    cl::Buffer& ClContextBase::internalSuccessFlagBuffer() SIXTRL_NOEXCEPT
    {
        return this->m_cl_status_flag_buffer;
    }

    ClContextBase::size_type
    ClContextBase::numAvailableNodes() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_available_nodes_id.size() ==
                       this->m_available_nodes_info.size() );

        return this->m_available_nodes_id.size();
    }

    ClContextBase::node_info_t const*
    ClContextBase::availableNodesInfoBegin() const SIXTRL_NOEXCEPT
    {
        return this->m_available_nodes_info.data();
    }

    ClContextBase::node_info_t const*
    ClContextBase::availableNodesInfoEnd()   const SIXTRL_NOEXCEPT
    {
        ClContextBase::node_info_t const* ptr_end =
            this->availableNodesInfoBegin();

        if( ptr_end != nullptr )
        {
            std::advance( ptr_end, this->numAvailableNodes() );
        }

        return ptr_end;
    }

    ClContextBase::node_info_t const*
    ClContextBase::defaultNodeInfo() const SIXTRL_NOEXCEPT
    {
        return this->availableNodesInfoBegin();
    }

    ClContextBase::node_id_t
    ClContextBase::defaultNodeId() const SIXTRL_NOEXCEPT
    {
        NS(ComputeNodeId) default_node_id;

        ClContextBase::node_info_t const*
            default_node_info = this->defaultNodeInfo();

        NS(ComputeNodeId_preset)( &default_node_id );

        if( default_node_info != nullptr )
        {
            default_node_id = default_node_info->id;
        }

        return default_node_id;
    }

    bool ClContextBase::isNodeIndexAvailable(
         ClContextBase::size_type const node_index ) const SIXTRL_RESTRICT
    {
        return ( node_index < this->numAvailableNodes() );
    }

    bool ClContextBase::isNodeIdAvailable(
        ClContextBase::node_id_t const node_id ) const SIXTRL_NOEXCEPT
    {
        platform_id_t const platform_index =
            NS(ComputeNodeId_get_platform_id)( &node_id );

        device_id_t const device_index =
            NS(ComputeNodeId_get_device_id)( &node_id );

        return ( this->numAvailableNodes() >
                 this->findAvailableNodesIndex( platform_index, device_index ) );
    }

    bool ClContextBase::isNodeIdAvailable(
        ClContextBase::platform_id_t const platform_index,
        ClContextBase::device_id_t  const device_index ) const SIXTRL_NOEXCEPT
    {
        return ( this->numAvailableNodes() >
                 this->findAvailableNodesIndex( platform_index, device_index ) );
    }

    bool ClContextBase::isNodeIdAvailable(
        char const* node_id_str ) const SIXTRL_NOEXCEPT
    {
        return ( this->numAvailableNodes() >
                 this->findAvailableNodesIndex( node_id_str ) );
    }

    bool ClContextBase::isDefaultNode(
        char const* node_id_str ) const SIXTRL_NOEXCEPT
    {
        node_id_t const default_node_id = this->defaultNodeId();

        return ( NS(ComputeNodeId_are_equal)(
            this->ptrAvailableNodesId( node_id_str ), &default_node_id ) );
    }

    bool ClContextBase::isDefaultNode(
        ClContextBase::node_id_t const node_id ) const SIXTRL_NOEXCEPT
    {
        node_id_t const default_node_id = this->defaultNodeId();
        return ( NS(ComputeNodeId_are_equal)( &node_id, &default_node_id ) );
    }

    bool ClContextBase::isDefaultNode(
        ClContextBase::size_type const node_index ) const SIXTRL_NOEXCEPT
    {
        node_id_t const default_node_id = this->defaultNodeId();

        return ( NS(ComputeNodeId_are_equal)(
            this->ptrAvailableNodesId( node_index ), &default_node_id ) );
    }

    bool ClContextBase::isDefaultNode(
        ClContextBase::platform_id_t const platform_index,
        ClContextBase::device_id_t const device_index ) const SIXTRL_NOEXCEPT
    {
        node_id_t const default_node_id = this->defaultNodeId();

        return ( NS(ComputeNodeId_are_equal)(
            this->ptrAvailableNodesId( platform_index, device_index ),
                                       &default_node_id ) );
    }

    ClContextBase::node_id_t const* ClContextBase::ptrAvailableNodesId(
        ClContextBase::size_type const index ) const SIXTRL_NOEXCEPT
    {
        return ( index < this->numAvailableNodes() )
               ? &this->m_available_nodes_id[ index ] : nullptr;
    }

    ClContextBase::node_id_t const* ClContextBase::ptrAvailableNodesId(
        ClContextBase::platform_id_t const platform_index,
        ClContextBase::device_id_t   const device_index ) const SIXTRL_NOEXCEPT
    {
        size_type const index =
            this->findAvailableNodesIndex( platform_index, device_index );

        return ( index < this->numAvailableNodes() )
               ? &this->m_available_nodes_id[ index ] : nullptr;
    }

    ClContextBase::node_id_t const* ClContextBase::ptrAvailableNodesId(
        char const* SIXTRL_RESTRICT node_id_str ) const SIXTRL_NOEXCEPT
    {
        size_type const index = this->findAvailableNodesIndex( node_id_str );

        return ( index < this->numAvailableNodes() )
               ? &this->m_available_nodes_id[ index ] : nullptr;
    }

    ClContextBase::node_info_t const*
    ClContextBase::ptrAvailableNodesInfo(
        size_type const index ) const SIXTRL_NOEXCEPT
    {
        return ( index < this->numAvailableNodes() )
               ? &this->m_available_nodes_info[ index ] : nullptr;
    }

    ClContextBase::node_info_t const*
    ClContextBase::ptrAvailableNodesInfo(
        char const* SIXTRL_RESTRICT node_id_str ) const SIXTRL_NOEXCEPT
    {
        size_type const index = this->findAvailableNodesIndex( node_id_str );

        return ( index < this->numAvailableNodes() )
               ? &this->m_available_nodes_info[ index ] : nullptr;
    }

    ClContextBase::node_info_t const*
    ClContextBase::ptrAvailableNodesInfo(
        ClContextBase::node_id_t const node_id ) const SIXTRL_NOEXCEPT
    {
        size_type const index = this->findAvailableNodesIndex(
                                    NS(ComputeNodeId_get_platform_id)( &node_id ),
                                    NS(ComputeNodeId_get_device_id)( &node_id ) );

        return ( index < this->numAvailableNodes() )
               ? &this->m_available_nodes_info[ index ] : nullptr;
    }

    bool ClContextBase::hasSelectedNode() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_selected_node_index >= 0 ) &&
                 ( this->numAvailableNodes() > static_cast< size_type >(
                       this->m_selected_node_index ) ) );
    }

    cl::Device const* ClContextBase::selectedNodeDevice() const SIXTRL_NOEXCEPT
    {
        cl::Device const* ptr_selected_device = nullptr;

        if( this->hasSelectedNode() )
        {
            SIXTRL_ASSERT( this->numAvailableNodes() > size_type{ 0 } );
            SIXTRL_ASSERT( this->m_available_devices.size() ==
                           this->numAvailableNodes() );

            ptr_selected_device =
                &this->m_available_devices[ this->m_selected_node_index ];

        }

        return ptr_selected_device;
    }

    cl::Device* ClContextBase::selectedNodeDevice() SIXTRL_NOEXCEPT
    {
        return const_cast< cl::Device* >(
            static_cast< ClContextBase const& >( *this ).selectedNodeDevice() );
    }

    ClContextBase::node_id_t const*
    ClContextBase::ptrSelectedNodeId() const SIXTRL_NOEXCEPT
    {
        return this->ptrAvailableNodesId( static_cast< size_type >(
            this->m_selected_node_index ) );
    }

    ClContextBase::node_info_t const*
    ClContextBase::ptrSelectedNodeInfo() const SIXTRL_NOEXCEPT
    {
        return this->ptrAvailableNodesInfo( static_cast< size_type >(
            this->m_selected_node_index ) );
    }

    ClContextBase::size_type
    ClContextBase::selectedNodeIndex() const SIXTRL_NOEXCEPT
    {
        using size_t = ClContextBase::size_type;

        return ( this->hasSelectedNode() )
            ? static_cast< size_t >( this->m_selected_node_index )
            : this->numAvailableNodes();
    }

    std::string ClContextBase::selectedNodeIdStr() const SIXTRL_NOEXCEPT
    {
        char node_id_str[ 32 ];
        std::memset( &node_id_str[ 0 ], ( int )'\0', 32 );

        if( this->selectedNodeIdStr( &node_id_str[ 0 ], 32 ) )
        {
            return std::string( node_id_str );
        }

        return std::string{ "" };
    }

    bool ClContextBase::selectedNodeIdStr( char* SIXTRL_RESTRICT node_id_str,
        ClContextBase::size_type const max_str_length ) const SIXTRL_NOEXCEPT
    {
        return ( 0 == NS(ComputeNodeId_to_string)(
            this->ptrSelectedNodeId(), node_id_str, max_str_length ) );
    }

    bool ClContextBase::selectNode( size_type const node_index )
    {
        bool success = false;

        if( this->doSelectNode( node_index ) )
        {
            success = this->doInitDefaultKernels();
        }

        return success;
    }

    bool ClContextBase::selectNode( node_id_t const node_id )
    {
        bool success = false;

        platform_id_t const platform_idx =
            NS(ComputeNodeId_get_platform_id)( &node_id );

        device_id_t const device_idx =
            NS(ComputeNodeId_get_device_id)( &node_id );

        if( this->doSelectNode( this->findAvailableNodesIndex(
                platform_idx, device_idx ) ) )
        {
            success = this->doInitDefaultKernels();
        }

        return success;
    }

    bool ClContextBase::selectNode(
         ClContextBase::platform_id_t const platform_idx,
         ClContextBase::device_id_t   const device_idx )
    {
        bool success = false;

        if( this->doSelectNode( this->findAvailableNodesIndex(
                platform_idx, device_idx ) ) )
        {
            success = this->doInitDefaultKernels();
        }

        return success;
    }

    bool ClContextBase::selectNode( char const* node_id_str )
    {
        bool success = false;

        if( this->doSelectNode( this->findAvailableNodesIndex( node_id_str ) ) )
        {
            success = this->doInitDefaultKernels();
        }

        return success;
    }

    bool ClContextBase::doSelectNode( size_type const node_index )
    {
        return this->doSelectNodeBaseImpl( node_index );
    }

    void ClContextBase::doSetConfigStr(
        const char *const SIXTRL_RESTRICT config_str )
    {
        if( ( config_str != nullptr ) &&
            ( std::strlen( config_str ) > ClContextBase::size_type{ 0 } ) )
        {
            this->m_config_str = std::string{ config_str };
        }
        else
        {
            this->m_config_str.clear();
        }

        return;
    }

    bool ClContextBase::doSelectNodeBaseImpl( size_type const index )
    {
        bool success = false;

        if( ( !this->hasSelectedNode() ) &&
            ( index < this->numAvailableNodes() ) )
        {
            SIXTRL_ASSERT( this->m_cl_programs.empty() );
            SIXTRL_ASSERT( this->m_selected_node_index < int64_t{ 0 } );
            SIXTRL_ASSERT( this->m_available_devices.size() ==
                           this->numAvailableNodes() );

            cl::Device  device  = this->m_available_devices[ index ];
            cl::Context context( device );
            cl::CommandQueue queue( context, device,
                                    CL_QUEUE_PROFILING_ENABLE );

            this->m_cl_status_flag_buffer = cl::Buffer(
                context, CL_MEM_READ_WRITE,
                    sizeof( _this_t::status_flag_t ), nullptr );

            _this_t::status_flag_t init_success_flag =
                st::ARCH_DEBUGGING_REGISTER_EMPTY;

            cl_int cl_ret = queue.enqueueWriteBuffer(
                this->m_cl_status_flag_buffer, true, _this_t::size_type{ 0 },
                sizeof( init_success_flag ), &init_success_flag );

            success = ( cl_ret == CL_SUCCESS );

            if( success )
            {
                this->m_cl_context = context;
                this->m_cl_queue   = queue;

                this->m_cl_programs.clear();
                this->m_cl_kernels.clear();
                this->m_kernel_data.clear();

                this->m_selected_node_index = index;
            }

            if( ( success ) && ( !this->m_program_data.empty() ) )
            {
                for( auto& program_data : this->m_program_data )
                {
                    program_data.m_kernels.clear();
                    program_data.m_compiled = false;
                    program_data.m_compile_report.clear();

                    this->m_cl_programs.emplace_back(
                        this->m_cl_context, program_data.m_source_code );

                    SIXTRL_ASSERT( this->m_cl_programs.size() <=
                                   this->m_program_data.size() );

                    success &= this->doCompileProgramBaseImpl(
                        this->m_cl_programs.back(), program_data );
                }
            }
        }

        return success;
    }

    void ClContextBase::printNodesInfo() const SIXTRL_NOEXCEPT
    {
        if( this->numAvailableNodes() > size_type{ 0 } )
        {
            node_id_t const default_node_id = this->defaultNodeId();

            auto node_it  = this->availableNodesInfoBegin();
            auto node_end = this->availableNodesInfoEnd();

            for( ; node_it != node_end ; ++node_it )
            {
                ::NS(ComputeNodeInfo_print_out)( node_it, &default_node_id );
            }
        }
        else
        {
            printf( "No OpenCL Devices found\r\n" );
        }

        return;
    }

    char const* ClContextBase::configStr() const SIXTRL_NOEXCEPT
    {
        return this->m_config_str.c_str();
    }

    void ClContextBase::clear()
    {
        this->doClear();
        this->doInitDefaultPrograms();
        return;
    }

    void ClContextBase::setDefaultCompileOptions(
        std::string const& compile_options_str )
    {
        this->setDefaultCompileOptions( compile_options_str.c_str() );
        return;
    }


    void ClContextBase::setDefaultCompileOptions( char const* compile_options_str )
    {
        SIXTRL_ASSERT( compile_options_str != nullptr );
        this->m_default_compile_options = compile_options_str;
        return;
    }

    char const* ClContextBase::defaultCompileOptions() const SIXTRL_NOEXCEPT
    {
        return this->m_default_compile_options.c_str();
    }

    ClContextBase::program_id_t
    ClContextBase::addProgramCode( std::string const& source_code )
    {
        return this->addProgramCode( source_code.c_str(),
                                     this->defaultCompileOptions() );
    }

    ClContextBase::program_id_t
    ClContextBase::addProgramCode( char const* source_code )
    {
        return this->addProgramCode( source_code,
                                     this->defaultCompileOptions() );
    }

    ClContextBase::program_id_t
    ClContextBase::addProgramCode(
        std::string const& source_code, std::string const& compile_options )
    {
        program_id_t program_id = program_id_t { -1 };

        if( !source_code.empty() )
        {
            program_id = this->m_program_data.size();

            this->m_program_data.emplace_back();
            this->m_program_data.back().m_source_code = source_code;
            this->m_program_data.back().m_compile_options = compile_options;

            if( this->hasSelectedNode() )
            {
                this->m_cl_programs.emplace_back(
                    this->m_cl_context, source_code );

                SIXTRL_ASSERT( this->m_cl_programs.size() ==
                               this->m_program_data.size() );

                this->doCompileProgram(
                    this->m_cl_programs.back(), this->m_program_data.back() );
            }
            else
            {
                this->m_program_data.back().m_compiled = false;
                SIXTRL_ASSERT( this->m_cl_programs.empty() );
            }
        }

        return program_id;
    }

    ClContextBase::program_id_t
    ClContextBase::addProgramCode(
        char const* source_code, char const* compile_options )
    {
        std::string const str_source_code( ( source_code != nullptr )
                                           ? std::string( source_code ) : std::string() );

        std::string const str_compile_options( ( compile_options != nullptr )
                                               ? std::string( compile_options )
                                               : this->m_default_compile_options );

        return this->addProgramCode( str_source_code, str_compile_options );
    }

    ClContextBase::program_id_t
    ClContextBase::addProgramFile( std::string const& path_to_program )
    {
        return this->addProgramFile(
                   path_to_program, this->m_default_compile_options );
    }

    ClContextBase::program_id_t
    ClContextBase::addProgramFile( char const* path_to_program )
    {
        return ( path_to_program != nullptr )
               ? this->addProgramFile( std::string( path_to_program ) )
               : program_id_t { -1 };
    }

    ClContextBase::program_id_t
    ClContextBase::addProgramFile(
        std::string const& path_to_program, std::string const& compile_options )
    {
        std::fstream kernel_file( path_to_program, std::ios::in );

        if( kernel_file.is_open() )
        {
            std::string const source_code(
                ( std::istreambuf_iterator< char >( kernel_file ) ),
                std::istreambuf_iterator< char >() );

            if( !source_code.empty() )
            {
                program_id_t program_id = this->addProgramCode(
                                              source_code, compile_options );

                if( program_id >= program_id_t { 0 } )
                {
                    this->m_program_data[ program_id ].m_file_path =
                        path_to_program;
                }

                return program_id;
            }
        }

        return program_id_t{ -1 };
    }

    ClContextBase::program_id_t
    ClContextBase::addProgramFile(
        char const* path_to_program, char const* compile_options )
    {
        std::string options_str = ( compile_options != nullptr )
                                  ? std::string( compile_options )
                                  : this->m_default_compile_options;

        return ( path_to_program != nullptr )
               ? this->addProgramFile( std::string( path_to_program ), options_str )
               : program_id_t { -1 };
    }

    bool ClContextBase::compileProgram(
        ClContextBase::program_id_t const program_id )
    {
        bool success = false;

        if( ( this->hasSelectedNode() ) &&
            ( program_id >= program_id_t{ 0 } ) &&
            ( static_cast< size_type >( program_id ) <
              this->m_program_data.size() ) &&
            ( this->m_cl_programs.size() ==
              this->m_program_data.size() ) )
        {
            success = this->doCompileProgram(
                this->m_cl_programs[ program_id ],
                this->m_program_data[ program_id ] );
        }

        return success;
    }

    char const* ClContextBase::programSourceCode(
        ClContextBase::program_id_t const program_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( program_id >= program_id_t{ 0 } ) &&
                 ( this->m_program_data.size() >
                   static_cast< size_type >( program_id ) ) )
            ? this->m_program_data[ program_id ].m_source_code.c_str()
            : nullptr;
    }

    bool ClContextBase::programHasFilePath(
         ClContextBase::program_id_t const program_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( program_id >= program_id_t{ 0 } ) &&
                 ( this->m_program_data.size() >
                   static_cast< size_type >( program_id ) ) &&
                 ( !this->m_program_data[ program_id ].m_file_path.empty() ) );
    }

    char const* ClContextBase::programPathToFile(
        ClContextBase::program_id_t const program_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( program_id >= program_id_t{ 0 } ) &&
                 ( this->m_program_data.size() >
                   static_cast< size_type >( program_id ) ) )
            ? this->m_program_data[ program_id ].m_file_path.c_str()
            : nullptr;
    }

    char const* ClContextBase::programCompileOptions(
        ClContextBase::program_id_t const program_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( program_id >= program_id_t{ 0 } ) &&
                 ( this->m_program_data.size() >
                   static_cast< size_type >( program_id ) ) )
            ? this->m_program_data[ program_id ].m_compile_options.c_str()
            : nullptr;
    }

    char const* ClContextBase::programCompileReport(
        ClContextBase::program_id_t const program_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( program_id >= program_id_t{ 0 } ) &&
                 ( this->m_program_data.size() >
                   static_cast< size_type >( program_id ) ) )
            ? this->m_program_data[ program_id ].m_compile_report.c_str()
            : nullptr;
    }

    bool ClContextBase::isProgramCompiled(
        ClContextBase::program_id_t const program_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( program_id >= program_id_t{ 0 } ) &&
                 ( this->m_program_data.size() >
                   static_cast< size_type >( program_id ) ) )
            ? this->m_program_data[ program_id ].m_compiled : false;
    }

    ClContextBase::size_type
    ClContextBase::numAvailablePrograms() const SIXTRL_NOEXCEPT
    {
        return this->m_program_data.size();
    }

    ClContextBase::kernel_id_t ClContextBase::enableKernel(
        std::string const& kernel_name,
        ClContextBase::program_id_t const program_id )
    {
        return this->enableKernel( kernel_name.c_str(), program_id );
    }

    ClContextBase::kernel_id_t
    ClContextBase::enableKernel(
        char const* kernel_name, program_id_t const program_id )
    {
        kernel_id_t kernel_id = kernel_id_t{ -1 };

        if( ( this->hasSelectedNode() ) && ( kernel_name != nullptr  ) &&
            ( std::strlen( kernel_name ) > 0u ) &&
            ( program_id >= program_id_t { 0 } ) &&
            ( static_cast< size_type >( program_id ) <
                this->m_cl_programs.size() ) )
        {
            SIXTRL_ASSERT( this->m_cl_programs.size() ==
                           this->m_program_data.size() );

            program_data_t& program_data = this->m_program_data[ program_id ];

            bool add_kernel = false;
            bool program_compiled = this->isProgramCompiled( program_id );

            if( !program_compiled )
            {
                add_kernel = program_compiled =
                    this->compileProgram( program_id );
            }

            if( ( !add_kernel ) && ( program_compiled ) )
            {
                add_kernel = true;

                auto it  = program_data.m_kernels.begin();
                auto end = program_data.m_kernels.end();

                kernel_id_t const num_kernels = this->m_cl_kernels.size();

                SIXTRL_ASSERT( this->m_cl_kernels.size() ==
                               this->m_kernel_data.size() );

                for( ; it != end ; ++it )
                {
                    kernel_id_t const test_kernel_id = *it;

                    if( (  test_kernel_id >= kernel_id_t{ 0 } ) &&
                        (  test_kernel_id <  num_kernels ) &&
                        ( !this->m_kernel_data[ test_kernel_id
                            ].m_kernel_name.empty() ) &&
                        (  this->m_kernel_data[ test_kernel_id
                            ].m_kernel_name.compare( kernel_name ) == 0 ) )
                    {
                        add_kernel = false;
                        break;
                    }
                }
            }

            if( ( add_kernel ) && ( program_compiled ) )
            {
                size_type const num_kernels_so_far = this->m_cl_kernels.size();

                kernel_id = static_cast< kernel_id_t >( num_kernels_so_far );
                SIXTRL_ASSERT( this->m_kernel_data.size() == num_kernels_so_far );
                SIXTRL_ASSERT( kernel_id >= kernel_id_t{ 0 } );

                cl::Kernel kernel(
                    this->m_cl_programs[ program_id ], kernel_name );

                this->m_cl_kernels.push_back( kernel );
                this->m_kernel_data.emplace_back();

                this->m_kernel_data.back().m_kernel_name = kernel_name;
                this->m_kernel_data.back().m_program_id  = program_id;

                cl::Device& selected_device = this->m_available_devices.at(
                    this->m_selected_node_index );

                size_type const num_kernel_args =
                    kernel.getInfo< CL_KERNEL_NUM_ARGS >();

                size_type const max_work_group_size = kernel.getWorkGroupInfo<
                    CL_KERNEL_WORK_GROUP_SIZE >( selected_device );

                size_type const pref_work_group_size = kernel.getWorkGroupInfo<
                    CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE >(
                        selected_device );

                size_type const loc_mem_size = kernel.getWorkGroupInfo<
                    CL_KERNEL_LOCAL_MEM_SIZE >( selected_device );

                SIXTRL_ASSERT( num_kernel_args  >= size_type{  0 } );
                SIXTRL_ASSERT( num_kernel_args  <  size_type{ 32 } );
                SIXTRL_ASSERT( pref_work_group_size > size_type{ 0 } );
                SIXTRL_ASSERT( max_work_group_size  >= pref_work_group_size );
                SIXTRL_ASSERT( max_work_group_size  <= size_type{ 65535 } );

                this->m_kernel_data.back().resetArguments( num_kernel_args );

                this->m_kernel_data.back().m_work_group_size = size_type{ 0 };

                this->m_kernel_data.back().m_max_work_group_size =
                    max_work_group_size;

                this->m_kernel_data.back().m_preferred_work_group_multiple =
                    pref_work_group_size;

                this->m_kernel_data.back().m_local_mem_size = loc_mem_size;
                program_data.m_kernels.push_back( kernel_id );
            }
        }

        return kernel_id;
    }

    ClContextBase::kernel_id_t ClContextBase::findKernelByName(
        char const* SIXTRL_RESTRICT kernel_name ) const SIXTRL_NOEXCEPT
    {
        kernel_id_t kernel_id = kernel_id_t{ -1 };

        SIXTRL_ASSERT( this->m_kernel_data.size() ==
                       this->m_cl_kernels.size() );

        if( ( !this->m_kernel_data.empty() ) && ( kernel_name != nullptr ) &&
            ( std::strlen( kernel_name ) > 0u ) )
        {
            kernel_id_t const num_kernels = this->m_kernel_data.size();
            kernel_id_t cmp_kernel_id = kernel_id_t{ 0 };

            for( ; cmp_kernel_id < num_kernels ; ++cmp_kernel_id )
            {
                kernel_data_t const& kernel_data =
                    this->m_kernel_data[ cmp_kernel_id ];

                program_id_t const kernel_program_id =
                    kernel_data.m_program_id;

                if( ( kernel_program_id < program_id_t{ 0 } ) ||
                    ( static_cast< size_type >( kernel_program_id ) >=
                      this->numAvailablePrograms() ) )
                {
                    continue;
                }

                if( 0 == kernel_data.m_kernel_name.compare( kernel_name ) )
                {
                    kernel_id = cmp_kernel_id;
                    break;
                }
            }
        }

        return kernel_id;
    }

    bool ClContextBase::hasRemappingProgram() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_remap_program_id >= program_id_t{ 0 } ) &&
                 ( static_cast< size_type >( this->m_remap_program_id ) <
                   this->numAvailablePrograms() ) );
    }

    ClContextBase::program_id_t
    ClContextBase::remappingProgramId() const SIXTRL_NOEXCEPT
    {
        return ( this->hasRemappingProgram() )
            ? this->m_remap_program_id : program_id_t{ -1 };
    }

    bool ClContextBase::hasRemappingKernel() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasSelectedNode() ) &&
                 ( this->m_remap_kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( this->m_remap_kernel_id ) <
                   this->m_cl_kernels.size() ) );
    }

    char const* ClContextBase::kernelFunctionName(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_cl_kernels.size() ==
                       this->m_kernel_data.size() );

        return ( ( this->hasSelectedNode() ) &&
                 ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->m_kernel_data.size() ) )
            ? this->m_kernel_data[ kernel_id ].m_kernel_name.c_str()
            : nullptr;
    }

    ClContextBase::size_type ClContextBase::kernelLocalMemSize(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_cl_kernels.size() ==
                       this->m_kernel_data.size() );

        return ( ( this->hasSelectedNode() ) &&
                 ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->m_kernel_data.size() ) )
            ? this->m_kernel_data[ kernel_id ].m_local_mem_size
            : size_type{ 0 };
    }

    ClContextBase::size_type ClContextBase::kernelNumArgs(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_cl_kernels.size() ==
                       this->m_kernel_data.size() );

        return ( ( this->hasSelectedNode() ) &&
                 ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->m_kernel_data.size() ) )
            ? this->m_kernel_data[ kernel_id ].m_num_args
            : size_type{ 0 };
    }

    ClContextBase::size_type ClContextBase::kernelWorkGroupSize(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_cl_kernels.size() ==
                       this->m_kernel_data.size() );

        size_type work_group_size = size_type{ 0 };

        if( ( this->hasSelectedNode() ) && ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( kernel_id ) < this->m_kernel_data.size() ) )
        {
            kernel_data_t const& kernel_data = this->m_kernel_data[ kernel_id ];

            work_group_size = std::min( kernel_data.m_work_group_size,
                                        kernel_data.m_max_work_group_size );
        }

        return work_group_size;
    }

    ClContextBase::size_type ClContextBase::kernelMaxWorkGroupSize(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_cl_kernels.size() ==
                       this->m_kernel_data.size() );

        return ( ( this->hasSelectedNode() ) &&
                 ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->m_kernel_data.size() ) )
            ? this->m_kernel_data[ kernel_id ].m_max_work_group_size
            : size_type{ 0 };
    }

    bool ClContextBase::setKernelWorkGroupSize(
        ClContextBase::kernel_id_t const kernel_id,
        ClContextBase::size_type work_group_size ) SIXTRL_NOEXCEPT
    {
        bool success = false;

        if( ( this->hasSelectedNode() ) &&
            ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( kernel_id ) < this->m_kernel_data.size() ) )
        {
            if( this->m_kernel_data[ kernel_id ].m_max_work_group_size >=
                work_group_size )
            {
                this->m_kernel_data[ kernel_id ].m_work_group_size =
                    work_group_size;

                success = true;
            }
        }

        return success;
    }

    ClContextBase::size_type ClContextBase::kernelPreferredWorkGroupSizeMultiple(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_cl_kernels.size() ==
                       this->m_kernel_data.size() );

        return ( ( this->hasSelectedNode() ) &&
                 ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->m_kernel_data.size() ) )
            ? this->m_kernel_data[ kernel_id ].m_preferred_work_group_multiple
            : size_type{ 0 };
    }

    ClContextBase::program_id_t ClContextBase::programIdByKernelId(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_cl_kernels.size() ==
                       this->m_kernel_data.size() );

        return ( ( this->hasSelectedNode() ) &&
                 ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->m_kernel_data.size() ) )
            ? this->m_kernel_data[ kernel_id ].m_program_id
            : program_id_t{ -1 };
    }

    ClContextBase::size_type ClContextBase::kernelExecCounter(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->numAvailableKernels() ) )
            ? this->m_kernel_data[ kernel_id ].m_exec_count
            : size_type{ 0 };
    }

    ClArgument* ClContextBase::ptrKernelArgument(
        ClContextBase::kernel_id_t const kernel_id,
        ClContextBase::size_type const arg_index ) SIXTRL_NOEXCEPT
    {
        using _this_t = ClContextBase;
        using   ptr_t = ClArgument*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).ptrKernelArgument( kernel_id, arg_index ) );
    }

    ClArgument const* ClContextBase::ptrKernelArgument(
        ClContextBase::kernel_id_t const kernel_id,
        ClContextBase::size_type const arg_index ) const SIXTRL_NOEXCEPT
    {
        ClArgument const* ptr_arg = nullptr;

        if( ( kernel_id >= kernel_id_t{ 0 } ) && ( static_cast< size_type >(
              kernel_id ) < this->numAvailableKernels() ) )
        {
            kernel_data_t const& kernel_data = this->m_kernel_data[ kernel_id ];

            if( kernel_data.m_num_args > arg_index )
            {
                SIXTRL_ASSERT( kernel_data.m_arguments.size() > arg_index );
                ptr_arg = kernel_data.m_arguments[ arg_index ];
            }
        }

        return ptr_arg;
    }

    ClContextBase::kernel_arg_type_t ClContextBase::kernelArgumentType(
        ClContextBase::kernel_id_t const kernel_id,
        ClContextBase::size_type const arg_index) const SIXTRL_NOEXCEPT
    {
        return ( ( static_cast< size_t >( kernel_id ) <
                   this->m_kernel_data.size() ) &&
                 ( arg_index < this->m_kernel_data[ kernel_id ].m_num_args ) )
            ? this->m_kernel_data[ kernel_id ].m_arg_types[ arg_index ]
            : SIXTRL_CXX_NAMESPACE::ClContextBase::ARG_TYPE_INVALID;
    }

    void ClContextBase::assignKernelArgument(
        ClContextBase::kernel_id_t const kernel_id,
        ClContextBase::size_type const index,
        ClArgument& SIXTRL_RESTRICT_REF arg )
    {
        SIXTRL_ASSERT( arg.context() == this );
        SIXTRL_ASSERT( arg.size() > ClContextBase::size_type{ 0 } );

        this->m_kernel_data.at( kernel_id ).setKernelArg(
            ClContextBase::kernel_data_t::ARG_TYPE_CL_ARGUMENT, index, &arg );

        cl::Kernel* kernel = this->openClKernel( kernel_id );
        if( kernel != nullptr ) kernel->setArg( index, arg.openClBuffer() );

    }

    void ClContextBase::assignKernelArgumentClBuffer(
            ClContextBase::kernel_id_t const kernel_id,
            ClContextBase::size_type const arg_index,
            cl::Buffer& SIXTRL_RESTRICT_REF cl_buffer_arg )
    {
        using _this_t = ClContextBase;
        this->m_kernel_data.at( kernel_id ).setKernelArg(
            _this_t::kernel_data_t::ARG_TYPE_CL_BUFFER, arg_index, nullptr );

        cl::Kernel* kernel = this->openClKernel( kernel_id );
        if( kernel != nullptr ) kernel->setArg( arg_index, cl_buffer_arg );
    }

    void ClContextBase::resetKernelArguments(
        ClContextBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        if( ( kernel_id >= kernel_id_t{ 0 } ) && ( static_cast< size_type >(
              kernel_id ) < this->numAvailableKernels() ) )
        {
            cl::Kernel* kernel = this->openClKernel( kernel_id );

            kernel_data_t& kernel_data = this->m_kernel_data[ kernel_id ];
            size_type const nn = kernel_data.m_num_args;

            SIXTRL_ASSERT( ( kernel_data.m_arguments.empty() ) ||
                           ( kernel_data.m_arguments.size() >= nn ) );

            if( ( kernel != nullptr ) &&
                ( !kernel_data.m_arguments.empty() ) && ( nn > size_type{ 0 } ) )
            {
                for( size_type ii = 0 ; ii < nn ; ++ii )
                {
                    if( kernel_data.m_arguments[ ii ] != nullptr )
                    {
                        kernel->setArg( ii, this->m_default_kernel_arg );
                    }
                }
            }

            kernel_data.resetArguments( nn );
        }

        return;
    }

    void ClContextBase::resetSingleKernelArgument(
        ClContextBase::kernel_id_t const kernel_id,
        ClContextBase::size_type const arg_index ) SIXTRL_NOEXCEPT
    {
        using _this_t = ClContextBase;

        cl::Kernel* kernel = this->openClKernel( kernel_id );
        if( kernel != nullptr ) kernel->setArg(
                arg_index, this->m_default_kernel_arg );

        this->m_kernel_data.at( kernel_id ).setKernelArg(
            _this_t::ARG_TYPE_NONE, arg_index, nullptr );
    }

    ClContextBase::size_type ClContextBase::calculateKernelNumWorkItems(
        ClContextBase::kernel_id_t const kernel_id,
        ClContextBase::size_type const min_num_work_items ) const SIXTRL_NOEXCEPT
    {
        size_type num_threads = min_num_work_items;
        size_type work_group_size = this->kernelWorkGroupSize( kernel_id );

        if( work_group_size == size_type{ 0 } )
        {
            work_group_size =
                this->kernelPreferredWorkGroupSizeMultiple( kernel_id );
        }

        if( work_group_size > size_type{ 0 } )
        {
            size_type const num_blocks = min_num_work_items / work_group_size;
            num_threads = num_blocks * work_group_size;

            if( num_threads < min_num_work_items )
            {
                num_threads += work_group_size;
            }
        }

        return num_threads;
    }

    bool ClContextBase::runKernel(
        ClContextBase::kernel_id_t const kernel_id,
        ClContextBase::size_type min_num_work_items )
    {
        return this->runKernel( kernel_id, min_num_work_items,
                         this->kernelWorkGroupSize( kernel_id ) );
    }

    bool ClContextBase::runKernel(
        ClContextBase::kernel_id_t const kernel_id,
        ClContextBase::size_type const min_num_work_items,
        ClContextBase::size_type work_group_size )
    {
        bool success = false;

        cl::Kernel* kernel = this->openClKernel( kernel_id );
        cl::CommandQueue* ptr_queue = this->openClQueue();

        if( ( kernel != nullptr ) && ( ptr_queue != nullptr ) )
        {
            size_type num_work_items = min_num_work_items;
            cl::NDRange local_size = cl::NullRange;

            if( work_group_size != size_type{ 0 } )
            {
                size_type const num_blocks =
                    ( min_num_work_items + work_group_size - 1 ) / work_group_size;

                num_work_items = num_blocks * work_group_size;
                SIXTRL_ASSERT( num_work_items >= min_num_work_items );
                local_size  = cl::NDRange( work_group_size );
            }

            cl::Event run_event;

            cl_ulong run_when_queued    = cl_ulong{ 0 };
            cl_ulong run_when_submitted = cl_ulong{ 0 };
            cl_ulong run_when_started   = cl_ulong{ 0 };
            cl_ulong run_when_ended     = cl_ulong{ 0 };

            cl_int cl_ret = ptr_queue->enqueueNDRangeKernel( *kernel,
                cl::NullRange, cl::NDRange( num_work_items ),
                    local_size, nullptr, &run_event );

            cl_ret |= ptr_queue->flush();
            run_event.wait();

            success = ( cl_ret == CL_SUCCESS );

            cl_ret  = run_event.getProfilingInfo< cl_ulong >(
                CL_PROFILING_COMMAND_QUEUED, &run_when_queued );

            cl_ret |= run_event.getProfilingInfo< cl_ulong >(
                CL_PROFILING_COMMAND_SUBMIT, &run_when_submitted );

            cl_ret |= run_event.getProfilingInfo< cl_ulong >(
                CL_PROFILING_COMMAND_START, &run_when_started );

            cl_ret |= run_event.getProfilingInfo< cl_ulong >(
                CL_PROFILING_COMMAND_END, &run_when_ended );

            if( cl_ret == CL_SUCCESS )
            {
                double const last_event_time = ( run_when_ended >= run_when_started )
                    ? ( double{ 1e-9 } * static_cast< double >(
                        run_when_ended - run_when_started ) )
                    : double{ 0 };

                this->addKernelExecTime(    last_event_time, kernel_id );
                this->setLastWorkGroupSize( work_group_size, kernel_id );
                this->setLastNumWorkItems(  num_work_items,  kernel_id );
            }
        }

        return success;
    }

    double ClContextBase::lastExecTime(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->numAvailableKernels() ) )
            ? this->m_kernel_data[ kernel_id ].m_last_exec_time : double{ 0 };
    }

    double ClContextBase::minExecTime(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->numAvailableKernels() ) )
            ? this->m_kernel_data[ kernel_id ].m_min_exec_time : double{ 0 };
    }

    double ClContextBase::maxExecTime(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->numAvailableKernels() ) )
            ? this->m_kernel_data[ kernel_id ].m_max_exec_time : double{ 0 };
    }

    double ClContextBase::avgExecTime(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->numAvailableKernels() ) )
            ? this->m_kernel_data[ kernel_id ].avgExecTime() : double{ 0 };
    }

    ClContextBase::size_type ClContextBase::lastExecWorkGroupSize(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->numAvailableKernels() ) )
            ? this->m_kernel_data[ kernel_id ].m_last_work_group_size
            : size_type{ 0 };
    }

    ClContextBase::size_type ClContextBase::lastExecNumWorkItems(
        ClContextBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( kernel_id ) <
                   this->numAvailableKernels() ) )
            ? this->m_kernel_data[ kernel_id ].m_last_num_of_threads
            : size_type{ 0 };
    }

    void ClContextBase::resetKernelExecTiming(
         ClContextBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        if( ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( kernel_id ) <
              this->numAvailableKernels() ) )
        {
            this->m_kernel_data[ kernel_id ].resetTiming();
        }

        return;
    }

    void ClContextBase::addKernelExecTime( double const time,
        ClContextBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        if( ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( kernel_id ) <
              this->numAvailableKernels() ) )
        {
            this->m_kernel_data[ kernel_id ].addExecTime( time );
        }

        return;
    }

    ClContextBase::kernel_id_t
    ClContextBase::remappingKernelId() const SIXTRL_NOEXCEPT
    {
        return ( this->hasRemappingKernel() )
            ? this->m_remap_kernel_id : kernel_id_t{ -1 };
    }

    bool ClContextBase::setRemappingKernelId(
        ClContextBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        bool success = false;

        if( ( this->hasSelectedNode() ) &&
            ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( kernel_id ) <
              this->m_cl_kernels.size() ) &&
            ( this->m_kernel_data[ kernel_id ].m_program_id >=
              program_id_t{ 0 } ) &&
            ( static_cast< size_type >(
                this->m_kernel_data[ kernel_id ].m_program_id ) <
                this->numAvailablePrograms() ) )
        {
            this->m_remap_kernel_id = kernel_id;
            this->m_remap_program_id =
                this->m_kernel_data[ kernel_id ].m_program_id;

            success = true;
        }

        return success;
    }

    ClContextBase::size_type
    ClContextBase::numAvailableKernels() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_cl_kernels.size() ==
                       this->m_kernel_data.size() );

        return this->m_cl_kernels.size();
    }

    cl::Program* ClContextBase::openClProgram(
        ClContextBase::program_id_t const program_id ) SIXTRL_NOEXCEPT
    {
        return ( ( program_id >= program_id_t{ 0 } ) &&
        ( this->m_cl_programs.size() >
            static_cast< size_type >( program_id ) ) )
        ? &this->m_cl_programs[ program_id ] : nullptr;
    }

    cl::Kernel* ClContextBase::openClKernel(
        ClContextBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        return ( ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( this->m_cl_kernels.size() > static_cast< size_type >( kernel_id ) ) )
            ? &this->m_cl_kernels[ kernel_id ] : nullptr;
    }

    cl::CommandQueue* ClContextBase::openClQueue() SIXTRL_NOEXCEPT
    {
        return &this->m_cl_queue;
    }

    cl::Context* ClContextBase::openClContext() SIXTRL_NOEXCEPT
    {
        return &this->m_cl_context;
    }

    bool ClContextBase::debug_mode() const  SIXTRL_NOEXCEPT
    {
        return this->m_debug_mode;
    }

    void ClContextBase::enable_debug_mode()  SIXTRL_NOEXCEPT
    {
        if( ( !this->debug_mode() ) && ( !this->hasSelectedNode() ) )
        {
            this->m_debug_mode = true;
            this->clear();
            this->doInitDefaultPrograms();
        }

        return;
    }

    void ClContextBase::disable_debug_mode() SIXTRL_NOEXCEPT
    {
        if( ( this->debug_mode() ) && ( !this->hasSelectedNode() ) )
        {
            this->m_debug_mode = false;
            this->clear();
            this->doInitDefaultPrograms();
        }

        return;
    }

    std::string const&
    ClContextBase::default_program_path_prefix() const SIXTRL_NOEXCEPT
    {
        return this->m_default_program_path_prefix;
    }

    char const*
    ClContextBase::ptr_default_program_path_prefix() const SIXTRL_NOEXCEPT
    {
        return this->m_default_program_path_prefix.c_str();
    }

    void ClContextBase::set_default_program_path_prefix(
        std::string const& SIXTRL_RESTRICT_REF path_prefix )
    {
        this->m_default_program_path_prefix = path_prefix;
    }

    void ClContextBase::set_default_program_path_prefix(
        char const* SIXTRL_RESTRICT path_prefix )
    {
        if( ( path_prefix != nullptr ) &&
            ( std::strlen( path_prefix ) > std::size_t{ 0 } ) )
        {
            this->m_default_program_path_prefix = path_prefix;
        }
        else
        {
            this->m_default_program_path_prefix.clear();
        }
    }

    /* --------------------------------------------------------------------- */

    ClContextBase::kernel_data_list_t const&
    ClContextBase::kernelData() const SIXTRL_NOEXCEPT
    {
        return this->m_kernel_data;
    }

    ClContextBase::program_data_list_t const&
    ClContextBase::programData() const SIXTRL_NOEXCEPT
    {
        return this->m_program_data;
    }

    void ClContextBase::setLastWorkGroupSize(
         ClContextBase::size_type const work_group_size,
         ClContextBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        if( ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( kernel_id ) <
              this->numAvailableKernels() ) )
        {
            this->m_kernel_data[ kernel_id ].m_last_work_group_size =
                work_group_size;
        }

        return;
    }

    void ClContextBase::setLastNumWorkItems(
         ClContextBase::size_type const num_work_items,
         ClContextBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        if( ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( kernel_id ) <
              this->numAvailableKernels() ) )
        {
            this->m_kernel_data[ kernel_id ].m_last_num_of_threads =
                num_work_items;
        }

        return;
    }

    ClContextBase::size_type
    ClContextBase::findAvailableNodesIndex(
        ClContextBase::platform_id_t const platform_index,
        ClContextBase::device_id_t const device_index ) const SIXTRL_NOEXCEPT
    {
        size_type index = this->numAvailableNodes();

        if( ( platform_index >= platform_id_t { 0 } ) &&
                ( device_index   >= device_id_t { 0 } ) )
        {
            index = size_type { 0 };

            for( auto const& cmp_node_id : this->m_available_nodes_id )
            {
                if( ( platform_index ==
                        NS(ComputeNodeId_get_platform_id)( &cmp_node_id ) ) &&
                        ( device_index ==
                          NS(ComputeNodeId_get_device_id)( &cmp_node_id ) ) )
                {
                    break;
                }

                ++index;
            }
        }

        SIXTRL_ASSERT( index <= this->numAvailableNodes() );

        return index;
    }

    ClContextBase::size_type
    ClContextBase::findAvailableNodesIndex(
        char const* node_id_str ) const SIXTRL_NOEXCEPT
    {
        if( ( node_id_str != nullptr ) && ( std::strlen( node_id_str ) >= 3u ) )
        {
            int temp_platform_index = -1;
            int temp_device_index   = -1;

            int const cnt = std::sscanf( node_id_str, "%d.%d",
                                         &temp_platform_index, &temp_device_index );

            if( cnt == 2 )
            {
                return this->findAvailableNodesIndex(
                           static_cast< platform_id_t >( temp_platform_index ),
                           static_cast< device_id_t   >( temp_device_index ) );
            }
        }

        return this->numAvailableNodes();
    }



    void ClContextBase::doParseConfigString(
        const char *const SIXTRL_RESTRICT config_str )
    {
        this->doParseConfigStringBaseImpl( config_str );
        return;
    }

    void ClContextBase::doParseConfigStringBaseImpl(
        const char *const SIXTRL_RESTRICT config_str )
    {
        ( void )config_str;
        return;
    }

    void ClContextBase::doClear()
    {
        this->doClearBaseImpl();
        return;
    }

    void ClContextBase::doClearBaseImpl() SIXTRL_NOEXCEPT
    {
        cl::CommandQueue dummy_queue;
        cl::Context dummy_context;
        cl::Buffer  dummy_success_flag;

        this->m_cl_programs.clear();
        this->m_program_data.clear();

        this->m_cl_kernels.clear();
        this->m_kernel_data.clear();

        this->m_cl_queue              = dummy_queue;
        this->m_cl_context            = dummy_context;
        this->m_cl_status_flag_buffer = dummy_success_flag;
        this->m_selected_node_index   = int64_t{ -1 };
        this->m_remap_kernel_id       = kernel_id_t{ -1 };

        return;
    }

    bool ClContextBase::doInitDefaultPrograms()
    {
        return this->doInitDefaultProgramsBaseImpl();
    }

    bool ClContextBase::doInitDefaultProgramsBaseImpl()
    {
        bool success = false;

        std::string path_to_remap_kernel_program(
            this->m_default_program_path_prefix );

        if( !this->debugMode() )
        {
            path_to_remap_kernel_program += "managed_buffer_remap.cl";
        }
        else
        {
            path_to_remap_kernel_program += "managed_buffer_remap_debug.cl";
        }

        std::string remap_program_compile_options = "-D_GPUCODE=1";
        remap_program_compile_options += " -DSIXTRL_BUFFER_ARGPTR_DEC=__private";
        remap_program_compile_options += " -DSIXTRL_BUFFER_DATAPTR_DEC=__global";
        #if !defined( SIXTRL_DISABLE_BEAM_BEAM )
        remap_program_compile_options += " -DSIXTRL_DISABLE_BEAM_BEAM=1";
        #endif /* !defined( SIXTRL_DISABLE_BEAM_BEAM ) */
        remap_program_compile_options += " -I";
        remap_program_compile_options += NS(PATH_TO_SIXTRL_INCLUDE_DIR);

        program_id_t const remap_program_id = this->addProgramFile(
            path_to_remap_kernel_program, remap_program_compile_options );

        if( remap_program_id >= program_id_t{ 0 } )
        {
            this->m_remap_program_id = remap_program_id;
            success = true;
        }

        return success;
    }

    bool ClContextBase::doInitDefaultKernels()
    {
        return this->doInitDefaultKernelsBaseImpl();
    }

    bool ClContextBase::doInitDefaultKernelsBaseImpl()
    {
        bool success = false;

        if( this->hasSelectedNode() )
        {
            if( ( this->m_remap_program_id >= program_id_t{ 0 } ) &&
                ( static_cast< size_type >( this->m_remap_program_id ) <
                  this->numAvailablePrograms() ) )
            {
                std::string kernel_name( SIXTRL_C99_NAMESPACE_PREFIX_STR );

                if( !this->debugMode() )
                {
                    kernel_name += "ManagedBuffer_remap_opencl";
                }
                else
                {
                    kernel_name += "ManagedBuffer_remap_debug_opencl";
                }

                kernel_id_t const remap_kernel_id = this->enableKernel(
                    kernel_name.c_str(), this->m_remap_program_id );

                if( remap_kernel_id >= kernel_id_t{ 0 } )
                {
                    success = this->setRemappingKernelId( remap_kernel_id );
                }
            }
        }

        return success;
    }

    bool ClContextBase::doCompileProgram(
         cl::Program& cl_program, ClContextBase::program_data_t& program_data )
    {
        return this->doCompileProgramBaseImpl( cl_program, program_data );
    }

    bool ClContextBase::doCompileProgramBaseImpl(
         cl::Program& cl_program, ClContextBase::program_data_t& program_data )
    {
        bool success = false;

        if( (  this->hasSelectedNode() ) &&
            ( !program_data.m_compiled ) &&
            (  program_data.m_kernels.empty() ) &&
            ( !program_data.m_compile_options.empty() ) )
        {
            auto& build_device =
                this->m_available_devices.at( this->m_selected_node_index );

            cl_int ret = cl_program.build( program_data.m_compile_options.c_str() );

            cl_build_status const build_status =
                cl_program.getBuildInfo< CL_PROGRAM_BUILD_STATUS >( build_device );

            if( ( build_status != CL_BUILD_NONE ) || ( ret == CL_SUCCESS ) )
            {
                program_data.m_compile_report =
                    cl_program.getBuildInfo< CL_PROGRAM_BUILD_LOG >( build_device );

                if( !program_data.m_compile_report.empty() )
                {
                    program_data.m_compile_report.erase(
                        std::find_if(
                            program_data.m_compile_report.rbegin(),
                            program_data.m_compile_report.rend(),
                            []( int ch ){ return !std::isspace( ch ); } ).base(),
                            program_data.m_compile_report.end() );
                }

                if( !program_data.m_compile_report.empty() )
                {
                    program_data.m_compile_report.erase(
                        program_data.m_compile_report.begin(),
                        std::find_if(
                            program_data.m_compile_report.begin(),
                            program_data.m_compile_report.end(),
                            []( int ch ){ return !std::isspace( ch ); } ) );
                }

                if( ( !program_data.m_compile_report.empty() ) &&
                    (  program_data.m_compile_report.size() == size_type{ 1 } ) &&
                    (  program_data.m_compile_report[ 0 ] == '\0' ) )
                {
                    program_data.m_compile_report.clear();
                }
            }

            if( build_status == CL_BUILD_SUCCESS )
            {
                success = program_data.m_compiled = true;
            }
            else if( build_status == CL_BUILD_ERROR )
            {
                SIXTRL_ASSERT( this->m_selected_node_index >= 0 );
                SIXTRL_ASSERT( this->m_available_devices.size() ==
                               this->numAvailableNodes() );

                program_data.m_compiled = false;
            }
            else
            {
                SIXTRL_ASSERT( build_status == CL_BUILD_NONE );
                program_data.m_compiled = false;
                program_data.m_compile_report.clear();
            }

            #if !defined( NDEBUG )

            if( ( !program_data.m_compile_report.empty() ) ||
                ( !program_data.m_compiled ) )
            #else /* defined( NDEBUG ) */

            if( ( this->debugMode() ) &&
                ( ( !program_data.m_compile_report.empty() ) ||
                  ( !program_data.m_compiled ) ) )
            #endif /* !defined( NDEBUG ) */
            {
                std::cout << "program_name    : "
                          << program_data.m_file_path << "\r\n"
                          << "compiled        : "
                          << std::boolalpha   << program_data.m_compiled
                          << std::noboolalpha << "\r\n"
                          << "compile options : "
                          << program_data.m_compile_options << "\r\n"
                          << "compile report  : " << "\r\n"
                          << program_data.m_compile_report
                          << std::endl;
            }
        }

        return success;
    }

    void ClContextBase::UpdateAvailableNodes(
        std::vector< ClContextBase::node_id_t>& available_nodes_id,
        std::vector< ClContextBase::node_info_t >& available_nodes_info,
        std::vector< cl::Device >& available_devices,
        const char *const filter_str )
    {
        ( void )filter_str;

        platform_id_t platform_index = 0;
        device_id_t   device_index   = 0;

        std::vector< cl::Device > devices;
        std::vector< cl::Platform > platforms;

        available_nodes_id.clear();
        available_nodes_info.clear();
        available_devices.clear();

        platforms.clear();
        platforms.reserve( 10 );

        devices.clear();
        devices.reserve( 100 );

        cl::Platform::get( &platforms );

        for( auto const& platform : platforms )
        {
            devices.clear();
            device_index = 0;

            std::string platform_name = platform.getInfo< CL_PLATFORM_NAME >();

            #if defined( SIXTRL_OPENCL_CXX_ENABLES_HOST_EXCEPTIONS ) && \
                SIXTRL_OPENCL_CXX_ENABLES_HOST_EXCEPTIONS == 1
            try
            {
            #endif /* OpenCL 1.x C++ Host Exceptions enabled */

            platform.getDevices( CL_DEVICE_TYPE_ALL, &devices );

            #if defined( SIXTRL_OPENCL_CXX_ENABLES_HOST_EXCEPTIONS ) && \
                SIXTRL_OPENCL_CXX_ENABLES_HOST_EXCEPTIONS == 1
            }
            catch( cl::Error const& e )
            {
                #if !defined( NDEBUG )
                std::cerr << "Error while probing devices for platform "
                          << platform_name << " --> skipping"
                          << std::endl;
                #endif /* !defined( NDEBUG ) */
            }
            #endif /* OpenCL 1.x C++ Host Exceptions enabled */

            bool added_at_least_one_device = false;

            for( auto const& device : devices )
            {
                std::string name;
                std::string description;

                cl_int ret = device.getInfo( CL_DEVICE_NAME, &name );
                ret |= device.getInfo( CL_DEVICE_EXTENSIONS, &description );

                available_nodes_id.push_back( node_id_t {} );
                node_id_t* ptr_node_id = &available_nodes_id.back();

                NS(ComputeNodeId_set_platform_id)( ptr_node_id, platform_index );
                NS(ComputeNodeId_set_device_id)( ptr_node_id, device_index++ );

                available_nodes_info.push_back( node_info_t {} );
                node_info_t* ptr_node_info = &available_nodes_info.back();
                NS(ComputeNodeInfo_preset)( ptr_node_info );

                std::string arch( "opencl" );

                if( nullptr != NS(ComputeNodeInfo_reserve)(
                            ptr_node_info, arch.size(), platform_name.size(),
                            name.size(), description.size() ) )
                {
                    ptr_node_info->id = *ptr_node_id;

                    std::strncpy( ptr_node_info->arch, arch.c_str(), arch.size() );
                    std::strncpy( ptr_node_info->name, name.c_str(), name.size() );

                    if( !platform_name.empty() )
                    {
                        std::strncpy( ptr_node_info->platform,
                                      platform_name.c_str(), platform_name.size() );
                    }

                    if( !description.empty() )
                    {
                        std::strncpy( ptr_node_info->description,
                                      description.c_str(), description.size() );
                    }
                }

                added_at_least_one_device = true;
                available_devices.push_back( device );
            }

            if( added_at_least_one_device )
            {
                ++platform_index;
            }
        }

        return;
    }
}

/* ------------------------------------------------------------------------- */
/* -----             Implementation of C Wrapper functions              ---- */
/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN NS(ClContextBase)* NS(ClContextBase_create)()
{
    NS(ClContextBase)* ptr_base_ctx = new SIXTRL_CXX_NAMESPACE::ClContextBase;
    return ptr_base_ctx;
}

SIXTRL_HOST_FN NS(context_size_t) NS(ClContextBase_get_num_available_nodes)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr )
        ? ctx->numAvailableNodes() : NS(context_size_t){ 0 };
}

SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(ClContextBase_get_available_nodes_info_begin)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr )
        ? ctx->availableNodesInfoBegin() : nullptr;

}

SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(ClContextBase_get_available_nodes_info_end)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr )
        ? ctx->availableNodesInfoEnd() : nullptr;
}

SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(ClContextBase_get_default_node_info)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT context )
{
    return ( context != nullptr ) ? context->defaultNodeInfo() : nullptr;
}

SIXTRL_HOST_FN NS(context_node_id_t)
NS(ClContextBase_get_default_node_id)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT context )
{
    SIXTRL_CXX_NAMESPACE::ClContextBase::node_id_t default_node_id;
    NS(ComputeNodeId_preset)( &default_node_id );

    NS(context_node_info_t) const* default_node_info =
        NS(ClContextBase_get_default_node_info)( context );

    if( default_node_info != nullptr )
    {
        default_node_id = default_node_info->id;
    }

    return default_node_id;
}

SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(ClContextBase_get_available_node_info_by_index)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_size_t) const node_index )
{
    return ( ctx != nullptr )
        ? ctx->ptrAvailableNodesInfo( node_index ) : nullptr;
}

SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(ClContextBase_get_available_node_info_by_node_id)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx,
    const NS(context_node_id_t) *const SIXTRL_RESTRICT node_id )
{
    return ( ( ctx != nullptr ) && ( node_id != nullptr ) )
        ? ctx->ptrAvailableNodesInfo( *node_id ) : nullptr;
}

SIXTRL_HOST_FN bool NS(ClContextBase_is_node_id_available)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx,
    const NS(context_node_id_t) *const SIXTRL_RESTRICT node_id )
{
    return ( ( ctx != nullptr ) && ( node_id != nullptr ) &&
             ( ctx->isNodeIdAvailable( *node_id ) ) );
}

SIXTRL_HOST_FN bool NS(ClContextBase_is_node_id_str_available)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx,
    char const* SIXTRL_RESTRICT node_id_str )
{
    return ( ( ctx != nullptr ) && ( node_id_str != nullptr ) &&
             ( ctx->isNodeIdAvailable( node_id_str ) ) );
}

SIXTRL_HOST_FN bool NS(ClContextBase_is_node_index_available)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_size_t) const node_index )
{
    return ( ctx != nullptr )
        ? ctx->isNodeIndexAvailable( node_index ) : false;
}

SIXTRL_HOST_FN bool NS(ClContextBase_is_platform_device_tuple_available)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx,
    NS(comp_node_id_num_t) const platform_idx,
    NS(comp_node_id_num_t) const device_idx )
{
    return ( ctx != nullptr )
        ? ctx->isNodeIdAvailable( platform_idx, device_idx ) : false;
}

SIXTRL_HOST_FN bool NS(ClContextBase_is_node_id_default_node)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx,
    const NS(context_node_id_t) *const SIXTRL_RESTRICT node_id )
{
    return ( ( ctx != nullptr ) && ( node_id != nullptr ) )
        ? ctx->isDefaultNode( *node_id ) : false;
}

SIXTRL_HOST_FN bool NS(ClContextBase_is_node_id_str_default_node)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx,
    char const* SIXTRL_RESTRICT node_id_str )
{
    return ( ctx != nullptr ) ? ctx->isDefaultNode( node_id_str ) : false;
}

SIXTRL_HOST_FN bool NS(ClContextBase_is_platform_device_tuple_default_node)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx,
    NS(comp_node_id_num_t) const platform_idx,
    NS(comp_node_id_num_t) const device_idx )
{
    return ( ctx != nullptr )
        ? ctx->isDefaultNode( platform_idx, device_idx ) : false;
}

SIXTRL_HOST_FN bool NS(ClContextBase_is_node_index_default_node)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_size_t) const node_index )
{
    return ( ctx != nullptr ) ? ctx->isDefaultNode( node_index ) : false;
}

SIXTRL_HOST_FN bool NS(ClContextBase_has_selected_node)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->hasSelectedNode() : false;
}

SIXTRL_HOST_FN cl_device_id NS(ClContextBase_get_selected_node_device)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    cl::Device const* ptr_device = ( ctx != nullptr )
        ? ctx->selectedNodeDevice() : nullptr;

    if( ptr_device != nullptr )
    {
        return ptr_device->operator()();
    }

    return cl_device_id{};
}

SIXTRL_HOST_FN NS(context_node_info_t) const* NS(ClContextBase_get_selected_node_info)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->ptrSelectedNodeInfo() : nullptr;
}

SIXTRL_HOST_FN NS(context_node_id_t) const* NS(ClContextBase_get_selected_node_id)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->ptrSelectedNodeId() : nullptr;
}

SIXTRL_HOST_FN NS(context_size_t) NS(ClContextBase_get_selected_node_index)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    using size_type = NS(context_size_t);
    using limits_t  = std::numeric_limits< size_type >;

    return ( ctx != nullptr ) ? ctx->selectedNodeIndex() : limits_t::max();
}

SIXTRL_HOST_FN bool NS(ClContextBase_get_selected_node_id_str)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx,
    char* SIXTRL_RESTRICT node_id_str, NS(context_size_t) const max_length )
{
    return ( ctx != nullptr )
        ? ctx->selectedNodeIdStr( node_id_str, max_length ) : false;
}

SIXTRL_HOST_FN void NS(ClContextBase_print_nodes_info)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    if( ctx != nullptr )
    {
        ctx->printNodesInfo();
    }

    return;
}

SIXTRL_HOST_FN void NS(ClContextBase_clear)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx )
{
    if( ctx != nullptr ) ctx->clear();
    return;
}

SIXTRL_HOST_FN bool NS(ClContextBase_select_node)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx,
    char const* SIXTRL_RESTRICT node_id_str )
{
    return ( ctx != nullptr ) ? ctx->selectNode( node_id_str ) : false;
}

SIXTRL_HOST_FN bool NS(ClContextBase_select_node_by_node_id)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx,
    const NS(context_node_id_t) *const SIXTRL_RESTRICT node_id )
{
    return ( ctx != nullptr ) ? ctx->selectNode( *node_id ) : false;
}

SIXTRL_HOST_FN bool NS(ClContextBase_select_node_by_index)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx,
    NS(context_size_t) const index )
{
    return ( ctx != nullptr ) ? ctx->selectNode( index ) : false;
}

SIXTRL_HOST_FN NS(ClContextBase)*
NS(ClContextBase_new_on_selected_node_id_str)(
    char const* SIXTRL_RESTRICT node_id_str )
{
    NS(ClContextBase)* ctx = NS(ClContextBase_create)();

    if( ctx != nullptr )
    {
        using node_id_t = NS(ClContextBase)::node_id_t;
        node_id_t const* ptr_node_id = ctx->ptrAvailableNodesId( node_id_str );

        if( ( ptr_node_id == nullptr ) || ( !ctx->selectNode( *ptr_node_id ) ) )
        {
            delete ctx;
            ctx = nullptr;
        }
    }

    return ctx;
}

SIXTRL_HOST_FN NS(ClContextBase)*
NS(ClContextBase_new_on_selected_node_id)(
    const NS(context_node_id_t) *const node_id )
{
    NS(ClContextBase)* ctx = nullptr;

    if( ( node_id != nullptr ) &&
        ( NS(ComputeNodeId_is_valid)( node_id ) ) )
    {
        ctx = new SIXTRL_CXX_NAMESPACE::ClContextBase( *node_id );

        if( ( ctx != nullptr ) && ( !ctx->hasSelectedNode() ) )
        {
           delete ctx;
           ctx = nullptr;
        }
    }
    else
    {
        ctx = NS(ClContextBase_create)();

        if( ctx != nullptr )
        {
            NS(context_node_id_t) const default_node =
                NS(ClContextBase_get_default_node_id)( ctx );

            if( 0 != NS(ClContextBase_select_node_by_node_id)(
                    ctx, &default_node ) )
            {
                delete ctx;
                ctx = nullptr;
            }
        }
    }

    return ctx;
}

SIXTRL_HOST_FN NS(ClContextBase)* NS(ClContextBase_new)()
{
    return NS(ClContextBase_new_on_selected_node_id)( nullptr );
}

SIXTRL_HOST_FN NS(context_size_t) NS(ClContextBase_get_num_available_programs)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr )
        ? ctx->numAvailablePrograms() : ( NS(context_size_t) )0u;
}

SIXTRL_HOST_FN int NS(ClContextBase_add_program_file)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx,
    char const* SIXTRL_RESTRICT path_to_program_file,
    char const* SIXTRL_RESTRICT compile_options )
{
    return ( ctx != nullptr )
        ? ctx->addProgramFile( path_to_program_file, compile_options )
        : -1;
}

SIXTRL_HOST_FN bool NS(ClContextBase_compile_program)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx, int const program_id )
{
    return ( ctx != nullptr ) ? ctx->compileProgram( program_id ) : false;
}

SIXTRL_HOST_FN char const* NS(ClContextBase_get_program_source_code)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const program_id )
{
    return ( ctx != nullptr ) ? ctx->programSourceCode( program_id ) : nullptr;
}

SIXTRL_HOST_FN bool NS(ClContextBase_has_program_file_path)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const program_id )
{
    return ( ctx != nullptr ) ? ctx->programHasFilePath( program_id ) : false;
}

SIXTRL_HOST_FN char const* NS(ClContextBase_get_program_path_to_file)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const program_id )
{
    return ( ctx != nullptr ) ? ctx->programPathToFile( program_id ) : nullptr;
}

SIXTRL_HOST_FN char const* NS(ClContextBase_get_program_compile_options)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const program_id )
{
    return ( ctx != nullptr )
        ? ctx->programCompileOptions( program_id ) : nullptr;
}

SIXTRL_HOST_FN char const* NS(ClContextBase_get_program_compile_report)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const program_id )
{
    return ( ctx != nullptr )
        ? ctx->programCompileReport( program_id ) : nullptr;
}

SIXTRL_HOST_FN bool NS(ClContextBase_is_program_compiled)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const program_id )
{
    return ( ctx != nullptr ) ? ctx->isProgramCompiled( program_id ) : false;
}

SIXTRL_HOST_FN int NS(ClContextBase_enable_kernel)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx,
    char const* kernel_name,
    int const program_id )
{
    return ( ctx != nullptr )
        ? ctx->enableKernel( kernel_name, program_id ) : -1;
}

SIXTRL_HOST_FN NS(context_size_t) NS(ClContextBase_get_num_available_kernels)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr )
        ? ctx->numAvailableKernels() : ( NS(context_size_t) )0u;
}


SIXTRL_HOST_FN int NS(ClContextBase_find_kernel_id_by_name)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx,
    char const* SIXTRL_RESTRICT kernel_name )
{
    return ( ctx != nullptr ) ? ctx->findKernelByName( kernel_name ) : -1;
}


SIXTRL_HOST_FN char const* NS(ClContextBase_get_kernel_function_name)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr ) ? ctx->kernelFunctionName( kernel_id ) : nullptr;
}

SIXTRL_HOST_FN NS(context_size_t) NS(ClContextBase_get_kernel_local_mem_size)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->kernelLocalMemSize( kernel_id ) : NS(context_size_t){ 0 };
}

SIXTRL_HOST_FN NS(context_size_t) NS(ClContextBase_get_kernel_num_args)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->kernelNumArgs( kernel_id )
        : NS(context_size_t){ 0 };
}

SIXTRL_HOST_FN NS(context_size_t) NS(ClContextBase_get_kernel_work_group_size)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->kernelWorkGroupSize( kernel_id ) : NS(context_size_t){ 0 };
}

SIXTRL_HOST_FN NS(context_size_t) NS(ClContextBase_get_kernel_max_work_group_size)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->kernelMaxWorkGroupSize( kernel_id ) : NS(context_size_t){ 0 };
}

SIXTRL_HOST_FN bool NS(ClContextBase_set_kernel_work_group_size)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx, int const kernel_id,
    NS(context_size_t) const work_group_size )
{
    return ( ctx != nullptr )
        ? ctx->setKernelWorkGroupSize( kernel_id, work_group_size )
        : false;
}

SIXTRL_HOST_FN NS(context_size_t)
NS(ClContextBase_get_kernel_preferred_work_group_size_multiple)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->kernelPreferredWorkGroupSizeMultiple( kernel_id )
        : NS(context_size_t){ 0 };
}

SIXTRL_HOST_FN NS(context_size_t) NS(ClContextBase_get_kernel_exec_counter)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->kernelExecCounter( kernel_id ) : NS(context_size_t){ 0 };
}

SIXTRL_HOST_FN NS(ClArgument)* NS(ClContextBase_get_ptr_kernel_argument)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx, int const kernel_id,
    NS(context_size_t) const arg_index ) SIXTRL_NOEXCEPT
{
    return ( ctx != nullptr )
        ? ctx->ptrKernelArgument( kernel_id, arg_index ) : nullptr;
}

SIXTRL_HOST_FN NS(kernel_arg_type_t) NS(ClContextBase_get_kernel_argument_type)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx, int const kernel_id,
    NS(context_size_t) const arg_index ) SIXTRL_NOEXCEPT
{
    return ( ctx != nullptr ) ? ctx->kernelArgumentType( kernel_id, arg_index )
        : SIXTRL_CXX_NAMESPACE::ClContextBase::ARG_TYPE_INVALID;
}

SIXTRL_HOST_FN NS(ClArgument) const*
NS(ClContextBase_get_const_ptr_kernel_argument)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id,
    NS(context_size_t) const arg_index ) SIXTRL_NOEXCEPT
{
    return ( ctx != nullptr )
        ? ctx->ptrKernelArgument( kernel_id, arg_index ) : nullptr;
}

SIXTRL_HOST_FN void NS(ClContextBase_assign_kernel_argument)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx, int const kernel_id,
    NS(context_size_t) const arg_index,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_arg )
{
    if( ( ctx != nullptr ) && ( ptr_arg != nullptr ) )
    {
        ctx->assignKernelArgument( kernel_id, arg_index, *ptr_arg );
    }

    return;
}

SIXTRL_HOST_FN void NS(ClContextBase_reset_kernel_arguments)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx, int const kernel_id ) SIXTRL_NOEXCEPT
{
    if( ctx != nullptr ) ctx->resetKernelArguments( kernel_id );
    return;
}

SIXTRL_HOST_FN void NS(ClContextBase_reset_single_kernel_argument)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx, int const kernel_id,
    NS(context_size_t) const arg_index ) SIXTRL_NOEXCEPT
{
    if( ctx != nullptr ) ctx->resetSingleKernelArgument( kernel_id, arg_index );
    return;
}

SIXTRL_HOST_FN void NS(ClContextBase_assign_kernel_argument_ptr)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx, int const kernel_id,
    NS(context_size_t) const arg_index,
    void* SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT
{
    if( ctx != nullptr ) ctx->assignKernelArgumentPtr(
        kernel_id, arg_index, ptr );

    return;
}

SIXTRL_HOST_FN void NS(ClContextBase_assign_kernel_argument_value)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx, int const kernel_id,
    NS(context_size_t) const arg_index, void* SIXTRL_RESTRICT arg_data,
    NS(context_size_t) const arg_data_size ) SIXTRL_NOEXCEPT
{
    if( arg_index < NS(ClContextBase_get_kernel_num_args)( ctx, kernel_id ) )
    {
        cl_kernel kernel = NS(ClContextBase_get_kernel)( ctx, kernel_id );
        cl_int ret = CL_SUCCESS;

        NS(ClContextBase_reset_single_kernel_argument)(
            ctx, kernel_id, arg_index );

        ret = clSetKernelArg( kernel, arg_index, arg_data_size, arg_data );
        SIXTRL_ASSERT( ret == CL_SUCCESS );
        ( void )ret;
    }

    return;
}

SIXTRL_HOST_FN NS(context_size_t)
NS(ClContextBase_calculate_kernel_num_work_items)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx,
    int const kernel_id, NS(context_size_t) const min_num_work_items )
{
    return ( ctx != nullptr )
        ? ctx->calculateKernelNumWorkItems( kernel_id, min_num_work_items )
        : SIXTRL_CXX_NAMESPACE::ClContextBase::size_type{ 0 };
}

SIXTRL_HOST_FN bool NS(ClContextBase_run_kernel)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx,
    int const kernel_id, NS(context_size_t) num_work_items )
{
    return ( ctx != nullptr )
        ? ctx->runKernel( kernel_id, num_work_items ) : false;
}

SIXTRL_HOST_FN bool NS(ClContextBase_run_kernel_wgsize)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx, int const kernel_id,
    NS(context_size_t) const num_work_items,
    NS(context_size_t) const work_group_size )
{
    return ( ctx != nullptr )
        ? ctx->runKernel( kernel_id, num_work_items, work_group_size )
        : false;
}

SIXTRL_HOST_FN double NS(ClContextBase_get_last_exec_time)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr ) ? ctx->lastExecTime( kernel_id ) : double{ 0 };
}

SIXTRL_HOST_FN double NS(ClContextBase_get_min_exec_time)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr ) ? ctx->minExecTime( kernel_id ) : double{ 0 };
}

SIXTRL_HOST_FN double NS(ClContextBase_get_max_exec_time)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr ) ? ctx->maxExecTime( kernel_id ) : double{ 0 };
}

SIXTRL_HOST_FN double NS(ClContextBase_get_avg_exec_time)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr ) ? ctx->avgExecTime( kernel_id ) : double{ 0 };
}

SIXTRL_HOST_FN NS(context_size_t) NS(ClContextBase_get_last_exec_work_group_size)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr ) ? ctx->lastExecWorkGroupSize( kernel_id )
        : NS(context_size_t){ 0 };
}

SIXTRL_HOST_FN NS(context_size_t) NS(ClContextBase_get_last_exec_num_work_items)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr ) ? ctx->lastExecNumWorkItems( kernel_id )
        : NS(context_size_t){ 0 };
}

SIXTRL_HOST_FN void NS(ClContextBase_reset_kernel_exec_timing)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx, int const kernel_id )
{
    if( ctx != nullptr ) ctx->resetKernelExecTiming( kernel_id );
    return;
}

SIXTRL_HOST_FN int NS(ClContextBase_get_program_id_by_kernel_id)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->programIdByKernelId( kernel_id ) : int{ -1 };
}

SIXTRL_HOST_FN bool NS(ClContextBase_has_remapping_program)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->hasRemappingProgram() : false;
}

SIXTRL_HOST_FN int NS(ClContextBase_get_remapping_program_id)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->remappingProgramId() : -1;
}

SIXTRL_HOST_FN bool NS(ClContextBase_has_remapping_kernel)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->hasRemappingKernel() : false;
}

SIXTRL_HOST_FN int NS(ClContextBase_get_remapping_kernel_id)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->remappingKernelId() : -1;
}

SIXTRL_HOST_FN bool NS(ClContextBase_set_remapping_kernel_id)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr ) ? ctx->setRemappingKernelId( kernel_id ) : false;
}

SIXTRL_HOST_FN cl_program NS(ClContextBase_get_program)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx,
    int const program_id )
{
    cl::Program* ptr_program = ( ctx != nullptr )
        ? ctx->openClProgram( program_id ) : nullptr;

    if( ptr_program != nullptr )
    {
        return ptr_program->operator()();
    }

    return cl_program{};
}

SIXTRL_HOST_FN cl_kernel NS(ClContextBase_get_kernel)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx,
    int const kernel_id )
{
    cl::Kernel* ptr_kernel = ( ctx != nullptr )
        ? ctx->openClKernel( kernel_id ) : nullptr;

    if( ptr_kernel != nullptr )
    {
        return ptr_kernel->operator()();
    }

    return cl_kernel{};
}

SIXTRL_HOST_FN cl_command_queue NS(ClContextBase_get_queue)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx )
{
    cl::CommandQueue* ptr_queue = ( ctx != nullptr )
        ? ctx->openClQueue() : nullptr;

    if( ptr_queue != nullptr )
    {
        return ptr_queue->operator()();
    }

    return cl_command_queue{};
}

SIXTRL_HOST_FN cl_context NS(ClContextBase_get_opencl_context)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx )
{
    cl::Context* ptr_context = ( ctx != nullptr )
        ? ctx->openClContext() : nullptr;

    if( ptr_context != nullptr )
    {
        ptr_context->operator()();
    }

    return cl_context{};
}


SIXTRL_HOST_FN void NS(ClContextBase_delete)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx )
{
    delete ctx;
    return;
}

SIXTRL_HOST_FN bool NS(ClContextBase_is_debug_mode_enabled)(
    const NS(ClContextBase) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->debugMode() : false;
}

SIXTRL_HOST_FN void NS(ClContextBase_enable_debug_mode)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx )
{
    if( ctx != nullptr ) ctx->enableDebugMode();
    return;
}

SIXTRL_HOST_FN void NS(ClContextBase_disable_debug_mode)(
    NS(ClContextBase)* SIXTRL_RESTRICT ctx )
{
    if( ctx != nullptr ) ctx->disableDebugMode();
    return;
}

#endif /* !defined( __CUDACC__ )  */

/* end: sixtracklib/opencl/internal/cl_context_base.cpp */


