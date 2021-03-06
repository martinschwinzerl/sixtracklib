#include "sixtracklib/opencl/context.h"

#if !defined( __CUDACC__ )

#include <chrono>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/generated/path.h"
#include "sixtracklib/common/context/compute_arch.h"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/particles.h"
#include "sixtracklib/common/output/elem_by_elem_config.h"
#include "sixtracklib/opencl/internal/base_context.h"

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    ClContext::ClContext( const char *const SIXTRL_RESTRICT config_str ) :
        ClContextBase( config_str ),
        m_elem_by_elem_config_buffer(),
        m_particle_set_indices(),
        m_particle_set_num_particles(),
        m_particle_set_index_begins(),
        m_total_num_particles( ClContext::size_type{ 0 } ),
        m_track_until_turn_program_id( ClContext::program_id_t{ -1 } ),
        m_track_single_turn_program_id( ClContext::program_id_t{ -1 } ),
        m_track_elem_by_elem_program_id( ClContext::program_id_t{ -1 } ),
        m_track_line_program_id( ClContext::program_id_t{ -1 } ),
        m_assign_be_mon_out_buffer_program_id( ClContext::program_id_t{ -1 } ),
        m_clear_be_mon_program_id( ClContext::program_id_t{ -1 } ),
        m_track_single_turn_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_track_elem_by_elem_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_track_line_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_assign_be_mon_out_buffer_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_clear_be_mon_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_use_optimized_tracking( true ),
        m_enable_beam_beam( true )
    {
        this->doResetParticleSetIndices();
        this->doInitDefaultProgramsPrivImpl();
    }

    ClContext::ClContext( ClContext::size_type const node_index,
                          const char *const SIXTRL_RESTRICT config_str ) :
        ClContextBase( config_str ),
        m_elem_by_elem_config_buffer(),
        m_particle_set_indices(),
        m_particle_set_num_particles(),
        m_particle_set_index_begins(),
        m_total_num_particles( ClContext::size_type{ 0 } ),
        m_track_until_turn_program_id( ClContext::program_id_t{ -1 } ),
        m_track_single_turn_program_id( ClContext::program_id_t{ -1 } ),
        m_track_elem_by_elem_program_id( ClContext::program_id_t{ -1 } ),
        m_track_line_program_id( ClContext::program_id_t{ -1 } ),
        m_assign_be_mon_out_buffer_program_id( ClContext::program_id_t{ -1 } ),
        m_clear_be_mon_program_id( ClContext::program_id_t{ -1 } ),
        m_track_single_turn_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_track_elem_by_elem_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_track_line_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_assign_be_mon_out_buffer_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_clear_be_mon_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_use_optimized_tracking( true ),
        m_enable_beam_beam( true )
    {
        this->doResetParticleSetIndices();

        if( config_str != nullptr )
        {
            this->doSetConfigStr( config_str );
            ClContextBase::doParseConfigString( this->configStr() );
        }

        this->doInitDefaultProgramsPrivImpl();

        if( ( node_index < this->numAvailableNodes() ) &&
            ( ClContextBase::doSelectNode( node_index ) ) &&
            ( this->doSelectNodePrivImpl( node_index ) ) )
        {
            ClContextBase::doInitDefaultKernels();
            this->doInitDefaultKernelsPrivImpl();
        }
    }

    ClContext::ClContext( ClContext::node_id_t const node_id,
                          const char *const SIXTRL_RESTRICT config_str ) :
        ClContextBase( config_str ),
        m_elem_by_elem_config_buffer(),
        m_particle_set_indices(),
        m_particle_set_num_particles(),
        m_particle_set_index_begins(),
        m_total_num_particles( ClContext::size_type{ 0 } ),
        m_track_until_turn_program_id( ClContext::program_id_t{ -1 } ),
        m_track_single_turn_program_id( ClContext::program_id_t{ -1 } ),
        m_track_elem_by_elem_program_id( ClContext::program_id_t{ -1 } ),
        m_track_line_program_id( ClContext::program_id_t{ -1 } ),
        m_assign_be_mon_out_buffer_program_id( ClContext::program_id_t{ -1 } ),
        m_clear_be_mon_program_id( ClContext::program_id_t{ -1 } ),
        m_track_single_turn_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_track_elem_by_elem_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_track_line_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_assign_be_mon_out_buffer_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_clear_be_mon_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_use_optimized_tracking( true ),
        m_enable_beam_beam( true )
    {
        using base_t = ClContextBase;
        using size_t = base_t::size_type;

        this->doResetParticleSetIndices();
        this->doInitDefaultProgramsPrivImpl();

        size_t const node_index = this->findAvailableNodesIndex(
            NS(ComputeNodeId_get_platform_id)( &node_id ),
            NS(ComputeNodeId_get_device_id)( &node_id ) );

        if( ( node_index < this->numAvailableNodes() ) &&
            ( base_t::doSelectNode( node_index ) ) &&
            ( this->doSelectNodePrivImpl( node_index ) ) )
        {
            base_t::doInitDefaultKernels();
            this->doInitDefaultKernelsPrivImpl();
        }
    }

    ClContext::ClContext( char const* node_id_str,
                          const char *const SIXTRL_RESTRICT config_str ) :
        ClContextBase( config_str ),
        m_elem_by_elem_config_buffer(),
        m_particle_set_indices(),
        m_particle_set_num_particles(),
        m_particle_set_index_begins(),
        m_total_num_particles( ClContext::size_type{ 0 } ),
        m_track_until_turn_program_id( ClContext::program_id_t{ -1 } ),
        m_track_single_turn_program_id( ClContext::program_id_t{ -1 } ),
        m_track_elem_by_elem_program_id( ClContext::program_id_t{ -1 } ),
        m_track_line_program_id( ClContext::program_id_t{ -1 } ),
        m_assign_be_mon_out_buffer_program_id( ClContext::program_id_t{ -1 } ),
        m_clear_be_mon_program_id( ClContext::program_id_t{ -1 } ),
        m_track_single_turn_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_track_elem_by_elem_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_track_line_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_assign_be_mon_out_buffer_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_clear_be_mon_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_use_optimized_tracking( true ),
        m_enable_beam_beam( true )
    {
        using base_t = ClContextBase;
        using size_t = base_t::size_type;

        this->doResetParticleSetIndices();
        this->doInitDefaultProgramsPrivImpl();

        size_t node_index = this->findAvailableNodesIndex( node_id_str );

        if( node_index >= this->numAvailableNodes() )
        {
            node_id_t const default_node_id = this->defaultNodeId();

            platform_id_t const platform_index =
                NS(ComputeNodeId_get_platform_id)( &default_node_id );

            device_id_t const device_index =
                NS(ComputeNodeId_get_device_id)( &default_node_id );

            node_index = this->findAvailableNodesIndex(
                platform_index, device_index );
        }

        if( ( node_index < this->numAvailableNodes() ) &&
            ( base_t::doSelectNode( node_index ) ) &&
            ( this->doSelectNodePrivImpl( node_index ) ) )
        {
            base_t::doInitDefaultKernels();
            this->doInitDefaultKernelsPrivImpl();
        }
    }

    ClContext::ClContext(
        ClContext::platform_id_t const platform_idx,
        ClContext::device_id_t const device_idx,
        const char *const SIXTRL_RESTRICT config_str ) :
        ClContextBase( config_str ),
        m_elem_by_elem_config_buffer(),
        m_particle_set_indices(),
        m_particle_set_num_particles(),
        m_particle_set_index_begins(),
        m_total_num_particles( ClContext::size_type{ 0 } ),
        m_track_until_turn_program_id( ClContext::program_id_t{ -1 } ),
        m_track_single_turn_program_id( ClContext::program_id_t{ -1 } ),
        m_track_elem_by_elem_program_id( ClContext::program_id_t{ -1 } ),
        m_track_line_program_id( ClContext::program_id_t{ -1 } ),
        m_assign_be_mon_out_buffer_program_id( ClContext::program_id_t{ -1 } ),
        m_clear_be_mon_program_id( ClContext::program_id_t{ -1 } ),
        m_track_single_turn_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_track_elem_by_elem_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_track_line_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_assign_be_mon_out_buffer_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_clear_be_mon_kernel_id( ClContext::kernel_id_t{ -1 } ),
        m_use_optimized_tracking( true ),
        m_enable_beam_beam( true )
    {
        using base_t = ClContextBase;
        using size_t = base_t::size_type;

        this->doResetParticleSetIndices();
        this->doInitDefaultProgramsPrivImpl();

        size_t const node_index =
            this->findAvailableNodesIndex( platform_idx, device_idx );

        if( ( node_index < this->numAvailableNodes() ) &&
            ( base_t::doSelectNode( node_index ) ) &&
            ( this->doSelectNodePrivImpl( node_index ) ) )
        {
            base_t::doInitDefaultKernels();
            this->doInitDefaultKernelsPrivImpl();
        }
    }

    ClContext::~ClContext() SIXTRL_NOEXCEPT
    {

    }

    bool ClContext::assignParticleArg(
        ClArgument& SIXTRL_RESTRICT_REF particles_arg,
        ClContext::size_type const particle_set_index )
    {
        using size_t = ClContext::size_type;

        size_t pset_indices[] = { size_t{ 0 }, size_t{ 0 } };
        pset_indices[ 0 ] = particle_set_index;
        pset_indices[ 1 ] = particle_set_index;

        return this->assignParticleArg(
            particles_arg, &pset_indices[ 0 ], &pset_indices[ 1 ] );
    }

    bool ClContext::assignBeamElementsArg(
        ClArgument& SIXTRL_RESTRICT_REF beam_elem_arg )
    {
        bool success = false;

        using size_t      = ClContext::size_type;
        using kernel_id_t = ClContext::kernel_id_t;

        ::NS(Buffer)* beam_elem_buffer = beam_elem_arg.ptrCObjectBuffer();

        if( ( beam_elem_arg.usesCObjectBuffer() ) &&
            ( beam_elem_buffer != nullptr ) &&
            ( !NS(Buffer_needs_remapping)( beam_elem_buffer ) ) )
        {
            success = true;

            if( this->hasTrackingKernel() )
            {
                kernel_id_t const kernel_id = this->trackingKernelId();
                success &= ( this->kernelNumArgs( kernel_id ) >= size_t{3u} );
                this->assignKernelArgument( kernel_id, 1u, beam_elem_arg );
            }

            if( this->hasElementByElementTrackingKernel() )
            {
                kernel_id_t const kernel_id =
                    this->elementByElementTrackingKernelId();

                success &= ( this->kernelNumArgs( kernel_id ) >= size_t{6u} );
                this->assignKernelArgument( kernel_id, 1u, beam_elem_arg );
            }

            if( this->hasSingleTurnTrackingKernel() )
            {
                kernel_id_t const kernel_id =
                    this->singleTurnTackingKernelId();

                success &= ( this->kernelNumArgs( kernel_id ) >= size_t{3u} );
                this->assignKernelArgument( kernel_id, 1u, beam_elem_arg );
            }


            if( this->hasLineTrackingKernel() )
            {
                kernel_id_t const kernel_id = this->lineTrackingKernelId();
                success &= ( this->kernelNumArgs( kernel_id ) >= size_t{ 6u } );
                this->assignKernelArgument( kernel_id, 2u, beam_elem_arg );
            }

            if( this->hasAssignBeamMonitorIoBufferKernel() )
            {
                kernel_id_t const kernel_id =
                    this->assignBeamMonitorIoBufferKernelId();

                success &= ( this->kernelNumArgs( kernel_id ) >= size_t{4u} );

                this->assignKernelArgument( kernel_id, 0u, beam_elem_arg );
            }
        }

        return success;
    }

    bool ClContext::assignOutputBufferArg(
        ClArgument& SIXTRL_RESTRICT_REF out_buffer_arg )
    {
        bool success = false;

        using size_t      = ClContext::size_type;
        using kernel_id_t = ClContext::kernel_id_t;

        ::NS(Buffer)* out_buffer = out_buffer_arg.ptrCObjectBuffer();

        if( ( out_buffer_arg.usesCObjectBuffer() ) &&
            ( out_buffer != nullptr ) &&
            ( !NS(Buffer_needs_remapping)( out_buffer ) ) )
        {
            success = true;

            if( this->hasElementByElementTrackingKernel() )
            {
                kernel_id_t const kernel_id =
                    this->elementByElementTrackingKernelId();

                success &= ( this->kernelNumArgs( kernel_id ) >= size_t{6u} );
                this->assignKernelArgument( kernel_id, 2u, out_buffer_arg );
            }

            if( this->hasAssignBeamMonitorIoBufferKernel() )
            {
                kernel_id_t const kernel_id =
                    this->assignBeamMonitorIoBufferKernelId();

                success &= ( this->kernelNumArgs( kernel_id ) >= size_t{4u} );

                this->assignKernelArgument( kernel_id, 1u, out_buffer_arg );
            }
        }

        return success;
    }

    bool ClContext::assignElemByElemConfigBuffer( ClContext::cl_buffer_t&
        SIXTRL_RESTRICT_REF cl_elem_by_elem_config_buffer )
    {
        bool success = true;

        using size_t      = ClContext::size_type;
        using kernel_id_t = ClContext::kernel_id_t;

        if( this->hasElementByElementTrackingKernel() )
        {
            kernel_id_t const kernel_id =
                this->elementByElementTrackingKernelId();

            success = ( this->kernelNumArgs( kernel_id ) >= size_t{ 6u } );
            this->assignKernelArgumentClBuffer( kernel_id, 3u,
                cl_elem_by_elem_config_buffer );
        }

        return success;
    }

    bool ClContext::assignElemByElemBufferOffset(
        ClContext::size_type const elem_by_elem_out_offset )
    {
        bool success = true;

        using size_t      = ClContext::size_type;
        using kernel_id_t = ClContext::kernel_id_t;

        if( this->hasElementByElementTrackingKernel() )
        {
            kernel_id_t const kernel_id =
                this->elementByElementTrackingKernelId();

            success = ( this->kernelNumArgs( kernel_id ) >= size_t{ 6u } );
            this->assignKernelArgumentValue(
                kernel_id, 5u, elem_by_elem_out_offset );
        }

        return success;
    }

    bool ClContext::assignSuccessFlagBuffer(
        ClContext::cl_buffer_t& SIXTRL_RESTRICT_REF cl_success_flag_buffer )
    {
        bool success = true;

        using size_t      = ClContext::size_type;
        using kernel_id_t = ClContext::kernel_id_t;

        if( this->hasTrackingKernel() )
        {
            kernel_id_t const kernel_id  = this->trackingKernelId();
            size_t const num_kernel_args = this->kernelNumArgs( kernel_id );
            success &= ( num_kernel_args >= size_t{ 3u } );

            if( num_kernel_args > 3u )
            {
                this->assignKernelArgumentClBuffer(
                    kernel_id, 3u, cl_success_flag_buffer );
            }
        }

        if( this->hasElementByElementTrackingKernel() )
        {
            kernel_id_t const kernel_id =
                this->elementByElementTrackingKernelId();

            size_t const num_kernel_args = this->kernelNumArgs( kernel_id );
            success &= ( num_kernel_args >= size_t{ 6u } );

            if( num_kernel_args > 6u )
            {
                this->assignKernelArgumentClBuffer(
                    kernel_id, 6u, cl_success_flag_buffer );
            }
        }

        if( this->hasSingleTurnTrackingKernel() )
        {
            kernel_id_t const kernel_id = this->singleTurnTackingKernelId();
            size_t const num_kernel_args = this->kernelNumArgs( kernel_id );
            success &= ( num_kernel_args >= size_t{ 3u } );

            if( num_kernel_args > 3u )
            {
                this->assignKernelArgumentClBuffer(
                    kernel_id, 3u, cl_success_flag_buffer );
            }
        }

        if( this->hasLineTrackingKernel() )
        {
            kernel_id_t const kernel_id = this->lineTrackingKernelId();
            success &= ( this->kernelNumArgs( kernel_id ) >= 6u );

            if( this->kernelNumArgs( kernel_id ) > 6u )
            {
                this->assignKernelArgumentClBuffer(
                    kernel_id, 6u, cl_success_flag_buffer );
            }
        }

        if( this->hasAssignBeamMonitorIoBufferKernel() )
        {
            kernel_id_t const kernel_id =
                this->assignBeamMonitorIoBufferKernelId();

            size_t const num_kernel_args = this->kernelNumArgs( kernel_id );
            success &= ( num_kernel_args >= size_t{ 4u } );

            if( num_kernel_args > 4u )
            {
                this->assignKernelArgumentClBuffer(
                    kernel_id, 4u, cl_success_flag_buffer );
            }
        }

        return success;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool ClContext::hasTrackingKernel() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasSelectedNode() ) &&
                 ( this->m_track_until_turn_kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( this->m_track_until_turn_kernel_id ) <
                   this->numAvailableKernels() ) );
    }

    ClContext::kernel_id_t ClContext::trackingKernelId() const SIXTRL_NOEXCEPT
    {
        return ( this->hasTrackingKernel() )
            ? this->m_track_until_turn_kernel_id : kernel_id_t{ - 1 };
    }

    bool ClContext::setTrackingKernelId(
        ClContext::kernel_id_t const kernel_id )
    {
        bool success = false;

        if( ( this->hasSelectedNode() ) &&
            ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( kernel_id ) <
              this->numAvailableKernels() ) )
        {
            program_id_t const tracking_program_id =
                this->programIdByKernelId( kernel_id );

            if( ( tracking_program_id >= program_id_t{ 0 } ) &&
                ( static_cast< size_type >( tracking_program_id ) <
                  this->numAvailablePrograms() ) )
            {
                this->m_track_until_turn_kernel_id  = kernel_id;
                this->m_track_until_turn_program_id = tracking_program_id;
                success = true;
            }
        }

        return success;
    }

    int ClContext::track( ClContext::num_turns_t const turn )
    {
        int success = -1;

        if( this->hasTrackingKernel() )
        {
            success = this->track( turn, this->trackingKernelId() );
        }

        return success;

    }

    int ClContext::track( ClContext::num_turns_t const turn,
                          ClContext::kernel_id_t const track_kernel_id )
    {
        int success = -1;

        using size_t = ClContextBase::size_type;

        if( ( this->hasSelectedNode() ) &&
            ( track_kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_t >( track_kernel_id ) <
                this->numAvailableKernels() ) )
        {
            SIXTRL_ASSERT( this->m_particle_set_indices.size() == size_t{1} );
            SIXTRL_ASSERT( this->m_particle_set_num_particles.size() ==
                           this->m_particle_set_indices.size() );
            SIXTRL_ASSERT( this->m_particle_set_index_begins.size() ==
                           this->m_particle_set_indices.size() );

            size_t pset_idx = this->m_particle_set_indices[ size_t{ 0 } ];

            size_t const num_particles =
                this->m_particle_set_num_particles[ pset_idx ];

            int64_t const turn_arg = static_cast< int64_t >( turn );
            this->assignKernelArgumentValue( track_kernel_id, 2u, turn_arg );

            success = ( this->runKernel( track_kernel_id, num_particles,
                this->lastExecWorkGroupSize( track_kernel_id ) ) ) ? 0 : -1;
        }

        return success;
    }

    int ClContext::track( ClArgument& SIXTRL_RESTRICT_REF particles_arg,
        ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
        ClContext::num_turns_t const turn )
    {
        SIXTRL_ASSERT( ( this->hasSelectedNode() ) &&
                       ( this->hasTrackingKernel() ) );

        return this->track( particles_arg, beam_elements_arg, turn,
                            this->trackingKernelId() );
    }

    int ClContext::track( ClArgument& particles_arg,
                          ClArgument& beam_elements_arg,
                          ClContext::num_turns_t const until_turn,
                          ClContext::kernel_id_t const track_kernel_id )
    {
        int success = -1;

        using size_t = ClContextBase::size_type;

        SIXTRL_ASSERT( this->hasSelectedNode() );
        SIXTRL_ASSERT( ( track_kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_t >( track_kernel_id ) <
                this->numAvailableKernels() ) );

        SIXTRL_ASSERT( beam_elements_arg.usesCObjectBuffer() );
        SIXTRL_ASSERT( beam_elements_arg.ptrCObjectBuffer() != nullptr );

        SIXTRL_ASSERT( particles_arg.usesCObjectBuffer() );
        SIXTRL_ASSERT( particles_arg.ptrCObjectBuffer() != nullptr );

        size_t const pset_idx = size_t{ 0 };

        success = ( this->doUpdateParticleSetIndices(
            &pset_idx, &pset_idx + size_t{ 1 },
                particles_arg.ptrCObjectBuffer() ) ) ? 0 : -1;

        size_t const npart = this->m_particle_set_num_particles[ pset_idx ];
        SIXTRL_ASSERT( npart > size_t{ 0 } );

        int64_t const until_turn_arg = static_cast< int64_t >( until_turn );
        size_t const num_kernel_args = this->kernelNumArgs( track_kernel_id );
        SIXTRL_ASSERT( num_kernel_args >= 3u );

        this->assignKernelArgument( track_kernel_id, 0u, particles_arg );
        this->assignKernelArgument( track_kernel_id, 1u, beam_elements_arg );
        this->assignKernelArgumentValue( track_kernel_id, 2u, until_turn_arg );

        if( num_kernel_args > 3u )
        {
            this->assignKernelArgumentClBuffer(
                track_kernel_id, 3u, this->internalSuccessFlagBuffer() );
        }

        success = ( this->runKernel( track_kernel_id, npart ) ) ? 0 : -1;

        if( ( success == 0 ) && ( num_kernel_args > 3u ) )
        {
            cl::CommandQueue* ptr_queue = this->openClQueue();
            SIXTRL_ASSERT( ptr_queue != nullptr );

            int32_t success_flag = int32_t{ -1 };
            cl_int cl_ret = ptr_queue->enqueueReadBuffer(
                this->internalSuccessFlagBuffer(), CL_TRUE, 0,
                sizeof( success_flag ), &success_flag );

            if( cl_ret == CL_SUCCESS )
            {
                success = ( int )success_flag;
            }

            ptr_queue->finish();
        }

        return success;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool ClContext::hasLineTrackingKernel() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasSelectedNode() ) &&
            ( this->m_track_line_kernel_id >= kernel_id_t{ 0 } ) &&
                ( static_cast< size_type >( this->m_track_line_kernel_id ) <
                    this->numAvailableKernels() ) );
    }

    ClContext::kernel_id_t
    ClContext::lineTrackingKernelId() const SIXTRL_NOEXCEPT
    {
        return ( this->hasTrackingKernel() )
            ? this->m_track_line_kernel_id : ClContext::kernel_id_t{ -1 };
    }

    bool ClContext::setTrackLineKernelId(
        ClContext::kernel_id_t const kernel_id )
    {
        bool success = false;

        if( ( this->hasSelectedNode() ) &&
            ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( kernel_id ) <
              this->numAvailableKernels() ) )
        {
            program_id_t const program_id =
                this->programIdByKernelId( kernel_id );

            if( ( program_id >= program_id_t{ 0 } ) &&
                ( static_cast< size_type >( program_id ) <
                    this->numAvailablePrograms() ) )
            {
                this->m_track_line_kernel_id  = kernel_id;
                this->m_track_line_program_id = program_id;
                success = true;
            }
        }

        return success;
    }

    int ClContext::trackLine(
        ClContext::size_type const line_begin_idx,
        ClContext::size_type const line_end_idx, bool const finish_turn )
    {
        return this->trackLine( line_begin_idx, line_end_idx,
            finish_turn, this->m_track_line_kernel_id );
    }

    int ClContext::trackLine(
        ClContext::size_type const line_begin_idx, size_type line_end_idx,
        bool const finish_turn, kernel_id_t const kernel_id )
    {
        int status = int{ -1 };
        using size_t = ClContextBase::size_type;

        if( ( this->hasSelectedNode() ) && ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_t >( kernel_id ) <=
                this->numAvailableKernels() ) )
        {
            SIXTRL_ASSERT( this->m_particle_set_indices.size() == size_t{1} );
            SIXTRL_ASSERT( this->m_particle_set_num_particles.size() ==
                           this->m_particle_set_indices.size() );
            SIXTRL_ASSERT( this->m_particle_set_index_begins.size() ==
                           this->m_particle_set_indices.size() );

            uint64_t pset_idx = this->m_particle_set_indices[ size_t{ 0 } ];

            size_t const num_particles =
                this->m_particle_set_num_particles[ pset_idx ];

            uint64_t const finish_turn_value = ( finish_turn )
                ? uint64_t{ 1 } : uint64_t{ 0 };

            this->assignKernelArgumentValue( kernel_id, 1u, pset_idx );
            this->assignKernelArgumentValue( kernel_id, 3u, line_begin_idx );
            this->assignKernelArgumentValue( kernel_id, 4u, line_end_idx );
            this->assignKernelArgumentValue( kernel_id, 5u, finish_turn_value );

            size_t const grsize = this->lastExecWorkGroupSize( kernel_id );
            status = ( this->runKernel( kernel_id, num_particles, grsize ) )
                ? 0 : -1;
        }

        return status;
    }

    int ClContext::trackLine(
        ClArgument& SIXTRL_RESTRICT_REF particles_arg,
        ClContext::size_type const particle_set_index,
        ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
        ClContext::size_type const line_begin_idx,
        ClContext::size_type const line_end_idx,
        bool const finish_turn )
    {
        return this->trackLine( particles_arg, particle_set_index,
            beam_elements_arg, line_begin_idx, line_end_idx, finish_turn,
                this->m_track_line_kernel_id );
    }

    int ClContext::trackLine(
        ClArgument& SIXTRL_RESTRICT_REF particles_arg,
        ClContext::size_type const particle_set_index,
        ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
        ClContext::size_type const line_begin_idx,
        ClContext::size_type const line_end_idx,
        bool const finish_turn, ClContext::kernel_id_t const kernel_id )
    {
        int success = -1;
        using size_t = ClContextBase::size_type;

        SIXTRL_ASSERT( this->hasSelectedNode() );
        SIXTRL_ASSERT( ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( kernel_id ) <
                this->numAvailableKernels() ) );

        SIXTRL_ASSERT( particles_arg.usesCObjectBuffer() );
        SIXTRL_ASSERT( particles_arg.ptrCObjectBuffer() != nullptr );
        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)(
            particles_arg.ptrCObjectBuffer() ) );

        size_t const pset_idx = size_t{ 0 };

        success = ( this->doUpdateParticleSetIndices(
            &pset_idx, &pset_idx + size_t{ 1 },
                particles_arg.ptrCObjectBuffer() ) ) ? 0 : -1;

        size_t const npart = this->m_particle_set_num_particles[ pset_idx ];
        SIXTRL_ASSERT( npart > size_t{ 0 } );

        SIXTRL_ASSERT( beam_elements_arg.usesCObjectBuffer() );
        SIXTRL_ASSERT( beam_elements_arg.ptrCObjectBuffer() != nullptr );
        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)(
            beam_elements_arg.ptrCObjectBuffer() ) );

        size_type const num_kernel_args = this->kernelNumArgs( kernel_id );
        SIXTRL_ASSERT(  num_kernel_args >= 6u );

        uint64_t const finish_turn_value = ( finish_turn )
            ? uint64_t{ 1 } : uint64_t{ 0 };

        this->assignKernelArgument( kernel_id, 0u, particles_arg );
        this->assignKernelArgumentValue( kernel_id, 1u, particle_set_index );
        this->assignKernelArgument( kernel_id, 2u, beam_elements_arg );
        this->assignKernelArgumentValue( kernel_id, 3u, line_begin_idx );
        this->assignKernelArgumentValue( kernel_id, 4u, line_end_idx );
        this->assignKernelArgumentValue( kernel_id, 5u, finish_turn_value );

        if( num_kernel_args > 6u )
        {
            this->assignKernelArgumentClBuffer( kernel_id, 6u,
                this->internalSuccessFlagBuffer() );
        }

        success = ( this->runKernel( kernel_id, npart ) ) ? 0 : -1;

        if( ( success == 0 ) && ( num_kernel_args > 6u ) )
        {
            cl::CommandQueue* ptr_queue = this->openClQueue();
            SIXTRL_ASSERT( ptr_queue != nullptr );

            int32_t success_flag = int32_t{ -1 };
            cl_int cl_ret = ptr_queue->enqueueReadBuffer(
                this->internalSuccessFlagBuffer(), CL_TRUE, 0,
                sizeof( success_flag ), &success_flag );

            if( cl_ret == CL_SUCCESS )
            {
                success = ( int )success_flag;
            }

            ptr_queue->finish();
        }

        return success;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool ClContext::hasSingleTurnTrackingKernel() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasSelectedNode() ) &&
                 ( this->m_track_single_turn_kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >(
                     this->m_track_single_turn_kernel_id ) <
                         this->numAvailableKernels() ) );
    }

    ClContext::kernel_id_t
    ClContext::singleTurnTackingKernelId() const SIXTRL_NOEXCEPT
    {
        return ( this->hasSingleTurnTrackingKernel() )
            ? this->m_track_single_turn_kernel_id : kernel_id_t{ -1 };
    }

    bool ClContext::setSingleTurnTrackingKernelId(
         ClContext::kernel_id_t const track_kernel_id )
    {
        bool success = false;

        if( ( this->hasSelectedNode() ) &&
            ( track_kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( track_kernel_id ) <
              this->numAvailableKernels() ) )
        {
            program_id_t const tracking_program_id =
                this->programIdByKernelId( track_kernel_id );

            if( ( tracking_program_id >= program_id_t{ 0 } ) &&
                ( static_cast< size_type >( tracking_program_id ) <
                  this->numAvailablePrograms() ) )
            {
                this->m_track_single_turn_kernel_id  = track_kernel_id;
                this->m_track_single_turn_program_id = tracking_program_id;
                success = true;
            }
        }

        return success;
    }

    int ClContext::trackSingleTurn()
    {
        return ( this->hasSingleTurnTrackingKernel() )
            ? this->trackSingleTurn( this->singleTurnTackingKernelId() )
            : -1;
    }

    int ClContext::trackSingleTurn(
        ClContext::kernel_id_t const track_kernel_id )
    {
        using size_t = ClContextBase::size_type;

        SIXTRL_ASSERT( this->m_particle_set_indices.size() == size_t{ 1 } );
        SIXTRL_ASSERT( this->m_particle_set_num_particles.size() ==
                       this->m_particle_set_indices.size() );
        SIXTRL_ASSERT( this->m_particle_set_index_begins.size() ==
                       this->m_particle_set_indices.size() );

        size_t const pset_idx = this->m_particle_set_indices[ size_t{ 0 } ];
        size_t const num_particles =
            this->m_particle_set_num_particles[ pset_idx ];

        return ( this->runKernel( track_kernel_id,
            num_particles, this->lastExecWorkGroupSize( track_kernel_id ) ) )
                ? 0 : -1;
    }

    int ClContext::trackSingleTurn(
        ClArgument& SIXTRL_RESTRICT_REF particles_arg,
        ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg )
    {
        return ( this->hasSingleTurnTrackingKernel() )
            ? this->trackSingleTurn( particles_arg, beam_elements_arg,
                                     this->singleTurnTackingKernelId() )
            : -1;
    }

    int ClContext::trackSingleTurn(
        ClArgument& particles_arg, ClArgument& beam_elements_arg,
        ClContext::kernel_id_t const kernel_id )
    {
        int success = -1;

        using size_t = ClContextBase::size_type;

        SIXTRL_ASSERT( this->hasSelectedNode() );
        SIXTRL_ASSERT( ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_t >( kernel_id ) <
              this->numAvailableKernels() ) );

        SIXTRL_ASSERT( particles_arg.usesCObjectBuffer() );
        SIXTRL_ASSERT( particles_arg.ptrCObjectBuffer() != nullptr );
        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)(
            particles_arg.ptrCObjectBuffer() ) );

        size_t const pset_idx = size_t{ 0 };

        success = ( this->doUpdateParticleSetIndices(
            &pset_idx, &pset_idx + size_t{ 1 },
                particles_arg.ptrCObjectBuffer() ) ) ? 0 : -1;

        size_t const npart = this->m_particle_set_num_particles[ pset_idx ];
        SIXTRL_ASSERT( npart > size_t{ 0 } );

        SIXTRL_ASSERT( beam_elements_arg.usesCObjectBuffer() );
        SIXTRL_ASSERT( beam_elements_arg.ptrCObjectBuffer() != nullptr );
        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)(
            beam_elements_arg.ptrCObjectBuffer() ) );

        size_t const num_kernel_args = this->kernelNumArgs( kernel_id );
        SIXTRL_ASSERT(  num_kernel_args >= 3u );

        SIXTRL_ASSERT( this->m_particle_set_indices.size() == size_t{ 1 } );
        SIXTRL_ASSERT( this->m_particle_set_num_particles.size() ==
                       this->m_particle_set_indices.size() );
        SIXTRL_ASSERT( this->m_particle_set_index_begins.size() ==
                       this->m_particle_set_indices.size() );

        int64_t increment_turn = int64_t{ 0 };

        this->assignKernelArgument( kernel_id, 0u, particles_arg );
        this->assignKernelArgument( kernel_id, 1u, beam_elements_arg );
        this->assignKernelArgumentValue( kernel_id, 2u, increment_turn );

        if( num_kernel_args > 3u )
        {
            this->assignKernelArgumentClBuffer(
                kernel_id, 3u, this->internalSuccessFlagBuffer() );
        }

        success = ( this->runKernel( kernel_id, npart ) ) ? 0 : -1;

        if( ( success == 0 ) && ( num_kernel_args > 3u ) )
        {
            cl::CommandQueue* ptr_queue = this->openClQueue();
            SIXTRL_ASSERT( ptr_queue != nullptr );

            int32_t success_flag = int32_t{ -1 };
            cl_int cl_ret = ptr_queue->enqueueReadBuffer(
                this->internalSuccessFlagBuffer(), CL_TRUE, 0,
                sizeof( success_flag ), &success_flag );

            if( cl_ret == CL_SUCCESS )
            {
                success = ( int )success_flag;
            }

            ptr_queue->finish();
        }

        return success;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool ClContext::hasElementByElementTrackingKernel() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasSelectedNode() ) &&
                 ( this->m_track_elem_by_elem_kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >(
                     this->m_track_elem_by_elem_kernel_id ) <
                         this->numAvailableKernels() ) );
    }

    ClContext::kernel_id_t
    ClContext::elementByElementTrackingKernelId() const SIXTRL_NOEXCEPT
    {
        return ( this->hasElementByElementTrackingKernel() )
            ? this->m_track_elem_by_elem_kernel_id : kernel_id_t{ -1 };
    }

    bool ClContext::setElementByElementTrackingKernelId(
        ClContext::kernel_id_t const track_kernel_id )
    {
        bool success = false;

        if( ( this->hasSelectedNode() ) &&
            ( track_kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( track_kernel_id ) <
              this->numAvailableKernels() ) )
        {
            program_id_t const tracking_program_id =
                this->programIdByKernelId( track_kernel_id );

            if( ( tracking_program_id >= program_id_t{ 0 } ) &&
                ( static_cast< size_type >( tracking_program_id ) <
                  this->numAvailablePrograms() ) )
            {
                this->m_track_elem_by_elem_kernel_id  = track_kernel_id;
                this->m_track_elem_by_elem_program_id = tracking_program_id;
                success = true;
            }
        }

        return success;
    }

    int ClContext::trackElementByElement(
        ClContext::size_type const until_turn,
        ClContext::size_type const out_buffer_index_offset )
    {
        return ( this->hasElementByElementTrackingKernel() )
            ? this->trackElementByElement( until_turn, out_buffer_index_offset,
                this->elementByElementTrackingKernelId() ) : -1;
    }

    int ClContext::trackElementByElement(
        ClContext::size_type const until_turn,
        ClContext::size_type const out_buffer_index_offset,
        ClContext::kernel_id_t const kernel_id )
    {
        if( this->hasElementByElementTrackingKernel() )
        {
            using size_t = ClContextBase::size_type;

            SIXTRL_ASSERT( this->m_particle_set_indices.size() == size_t{1} );
            SIXTRL_ASSERT( this->m_particle_set_num_particles.size() ==
                           this->m_particle_set_indices.size() );
            SIXTRL_ASSERT( this->m_particle_set_index_begins.size() ==
                           this->m_particle_set_indices.size() );

            size_t const pset_idx = this->m_particle_set_indices[ size_t{0} ];
            size_t const num_particles =
                this->m_particle_set_num_particles[ pset_idx ];

            this->assignKernelArgumentValue(
                kernel_id, 3u, out_buffer_index_offset );

            if( this->runKernel( kernel_id,
                num_particles, this->lastExecWorkGroupSize( kernel_id ) ) )
            {
                return 0;
            }
        }

        return -1;
    }

    int ClContext::trackElementByElement(
        ClArgument& SIXTRL_RESTRICT_REF particles_arg,
        ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
        ClArgument& SIXTRL_RESTRICT_REF elem_by_elem_buffer,
        ClContext::size_type const until_turn,
        ClContext::size_type out_buffer_index_offset )
    {
        return this->trackElementByElement( particles_arg, beam_elements_arg,
            elem_by_elem_buffer, until_turn, out_buffer_index_offset,
                this->elementByElementTrackingKernelId() );
    }

    int ClContext::trackElementByElement(
        ClArgument& SIXTRL_RESTRICT_REF particles_arg,
        ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
        ClArgument& SIXTRL_RESTRICT_REF elem_by_elem_buffer_arg,
        ClContext::size_type const until_turn,
        ClContext::size_type const out_buffer_index_offset,
        ClContext::kernel_id_t const kernel_id )
    {
        int success = -1;

        using index_t = ::NS(particle_index_t);
        using size_t  = ClContextBase::size_type;

        SIXTRL_ASSERT( this->hasSelectedNode() );
        SIXTRL_ASSERT( ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_t >( kernel_id ) <
              this->numAvailableKernels() ) );

        SIXTRL_ASSERT( particles_arg.usesCObjectBuffer() );
        SIXTRL_ASSERT( particles_arg.ptrCObjectBuffer() != nullptr );
        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)(
            particles_arg.ptrCObjectBuffer() ) );

        SIXTRL_ASSERT( beam_elements_arg.usesCObjectBuffer() );
        SIXTRL_ASSERT( beam_elements_arg.ptrCObjectBuffer() != nullptr );
        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)(
            beam_elements_arg.ptrCObjectBuffer() ) );

        SIXTRL_ASSERT( elem_by_elem_buffer_arg.usesCObjectBuffer() );
        SIXTRL_ASSERT( elem_by_elem_buffer_arg.ptrCObjectBuffer() != nullptr );
        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)(
            elem_by_elem_buffer_arg.ptrCObjectBuffer() ) );

        cl::CommandQueue* ptr_queue = this->openClQueue();
        SIXTRL_ASSERT( ptr_queue != nullptr );

        size_type const num_kernel_args = this->kernelNumArgs( kernel_id );
        SIXTRL_ASSERT(  num_kernel_args >= 6u );

        SIXTRL_ASSERT( particles_arg.usesCObjectBuffer() );
        SIXTRL_ASSERT( particles_arg.ptrCObjectBuffer() != nullptr );
        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)(
            particles_arg.ptrCObjectBuffer() ) );

        size_t const pset_idx = size_t{ 0 };

        success = ( this->doUpdateParticleSetIndices(
            &pset_idx, &pset_idx + size_t{ 1 },
                particles_arg.ptrCObjectBuffer() ) ) ? 0 : -1;

        size_t const npart = this->m_particle_set_num_particles[ pset_idx ];
        SIXTRL_ASSERT( npart > size_t{ 0 } );

        NS(Particles) const* particles =
            NS(Particles_buffer_get_const_particles)(
                particles_arg.ptrCObjectBuffer(), pset_idx );

        index_t min_particle_id = std::numeric_limits< index_t >::max();
        index_t max_particle_id = std::numeric_limits< index_t >::min();

        index_t min_element_id  = index_t{ 0 };
        index_t max_element_id  = NS(Buffer_get_num_of_objects)(
            beam_elements_arg.ptrCObjectBuffer() );

        index_t min_turn = index_t{ 0 };
        index_t max_turn = index_t{ 0 };

        if( ( max_element_id > min_element_id ) &&
            ( max_element_id > index_t{ 0 } ) )
        {
            --max_element_id;
        }

        success = NS(Particles_get_min_max_particle_id)(
            particles, &min_particle_id, &max_particle_id );

        success |= NS(Particles_get_min_max_at_turn_value)(
            particles, &min_turn, &max_turn );

        if( static_cast< index_t >( until_turn ) >
                ( max_turn + index_t{ 1 } ) )
        {
            max_turn = static_cast< index_t >( until_turn ) - index_t{ 1 };
        }

        NS(ElemByElemConfig) elem_by_elem_config;
        NS(ElemByElemConfig_preset)( &elem_by_elem_config );

        success |= NS(ElemByElemConfig_init_detailed)( &elem_by_elem_config,
            NS(ELEM_BY_ELEM_ORDER_DEFAULT), min_particle_id, max_particle_id,
            min_element_id, max_element_id, min_turn, max_turn, true );

        if( success != 0 ) return success;

        cl_int ret = ptr_queue->enqueueWriteBuffer(
            this->m_elem_by_elem_config_buffer, CL_TRUE, size_type{ 0 },
            sizeof( elem_by_elem_config ), &elem_by_elem_config );

        if( ret != CL_SUCCESS )
        {
            success = -2;
            return success;
        }

        this->assignKernelArgument( kernel_id, 0u, particles_arg );
        this->assignKernelArgument( kernel_id, 1u, beam_elements_arg );

        this->assignKernelArgument( kernel_id, 2u, elem_by_elem_buffer_arg );

        this->assignKernelArgumentClBuffer(
            kernel_id, 3u, this->m_elem_by_elem_config_buffer );

        this->assignKernelArgumentValue( kernel_id, 4u, until_turn );

        this->assignKernelArgumentValue(
            kernel_id, 5u, out_buffer_index_offset );

        if( num_kernel_args > 6u )
        {
            this->assignKernelArgumentClBuffer(
                kernel_id, 6u, this->internalSuccessFlagBuffer() );
        }

        success = ( this->runKernel( kernel_id, npart ) ) ? 0 : -1;

        if( ( success == 0 ) && ( num_kernel_args > 6u ) )
        {
            int32_t success_flag = int32_t{ -1 };
            cl_int cl_ret = ptr_queue->enqueueReadBuffer(
                this->internalSuccessFlagBuffer(), CL_TRUE, 0,
                sizeof( success_flag ), &success_flag );

            if( cl_ret == CL_SUCCESS )
            {
                success = ( int )success_flag;
            }

            ptr_queue->finish();
        }

        return success;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool ClContext::hasAssignBeamMonitorIoBufferKernel() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasSelectedNode() ) &&
            ( this->m_assign_be_mon_out_buffer_kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >(
                this->m_assign_be_mon_out_buffer_kernel_id ) <
                this->numAvailableKernels() ) );
    }

    ClContext::kernel_id_t const
    ClContext::assignBeamMonitorIoBufferKernelId() const SIXTRL_NOEXCEPT
    {
        return ( this->hasAssignBeamMonitorIoBufferKernel() )
            ? this->m_assign_be_mon_out_buffer_kernel_id : kernel_id_t{ -1 };
    }

    bool ClContext::setAssignBeamMonitorIoBufferKernelId(
        ClContext::kernel_id_t const track_kernel_id )
    {
        bool success = false;

        if( ( this->hasSelectedNode() ) &&
            ( track_kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( track_kernel_id ) <
              this->numAvailableKernels() ) )
        {
            program_id_t const tracking_program_id =
                this->programIdByKernelId( track_kernel_id );

            if( ( tracking_program_id >= program_id_t{ 0 } ) &&
                ( static_cast< size_type >( tracking_program_id ) <
                  this->numAvailablePrograms() ) )
            {
                this->m_assign_be_mon_out_buffer_kernel_id  = track_kernel_id;
                this->m_assign_be_mon_out_buffer_program_id = tracking_program_id;
                success = true;
            }
        }

        return success;
    }

    int ClContext::assignBeamMonitorIoBuffer(
        ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
        ClArgument& SIXTRL_RESTRICT_REF out_buffer_arg,
        ClContext::size_type const min_turn_id,
        ClContext::size_type const out_particle_block_offset  )
    {
        int success = -1;

        kernel_id_t const kernel_id = this->assignBeamMonitorIoBufferKernelId();
        kernel_id_t const max_kernel_id = this->numAvailableKernels();

        if( ( kernel_id >= kernel_id_t{ 0 } ) && ( kernel_id <  max_kernel_id ) )
        {
            success = this->assignBeamMonitorIoBuffer( beam_elements_arg,
                out_buffer_arg, min_turn_id, out_particle_block_offset, kernel_id );
        }

        return success;
    }

    int ClContext::assignBeamMonitorIoBuffer(
        ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
        ClArgument& SIXTRL_RESTRICT_REF out_buffer_arg,
        ClContext::size_type const min_turn_id,
        ClContext::size_type const out_particle_block_offset,
        ClContext::kernel_id_t const assign_kernel_id )
    {
        int success = -1;

        SIXTRL_ASSERT( this->hasSelectedNode() );
        SIXTRL_ASSERT( ( assign_kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( assign_kernel_id ) <
              this->numAvailableKernels() ) );

        SIXTRL_ASSERT( beam_elements_arg.usesCObjectBuffer() );
        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)(
            beam_elements_arg.ptrCObjectBuffer() ) );

        SIXTRL_ASSERT( out_buffer_arg.usesCObjectBuffer() );
        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)(
            out_buffer_arg.ptrCObjectBuffer() ) );

        size_type const num_kernel_args = this->kernelNumArgs( assign_kernel_id );
        SIXTRL_ASSERT(  num_kernel_args >= 4u );

        int64_t const min_turn_id_arg = static_cast< int64_t >( min_turn_id );

        this->assignKernelArgument( assign_kernel_id, 0u, beam_elements_arg );
        this->assignKernelArgument( assign_kernel_id, 1u, out_buffer_arg );

        this->assignKernelArgumentValue(
            assign_kernel_id, 2u, min_turn_id_arg );

        this->assignKernelArgumentValue(
            assign_kernel_id, 3u, out_particle_block_offset );

        if( num_kernel_args > 4u )
        {
            this->assignKernelArgumentClBuffer(
                assign_kernel_id, 4u, this->internalSuccessFlagBuffer() );
        }

        success = ( this->runKernel( assign_kernel_id,
                this->kernelPreferredWorkGroupSizeMultiple( assign_kernel_id ) ) )
            ? 0 : -1;

        if( ( success == 0 ) && ( num_kernel_args > 3u ) )
        {
            cl::CommandQueue* ptr_queue = this->openClQueue();
            SIXTRL_ASSERT( ptr_queue != nullptr );

            int32_t success_flag = int32_t{ -26 };
            cl_int cl_ret = ptr_queue->enqueueReadBuffer(
                this->internalSuccessFlagBuffer(), CL_TRUE, 0,
                sizeof( success_flag ), &success_flag );

            if( cl_ret == CL_SUCCESS )
            {
                success = ( int )success_flag;
            }

            ptr_queue->finish();
        }

        return success;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool ClContext::hasClearBeamMonitorIoBufferAssignmentKernel() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasSelectedNode() ) &&
            ( this->m_clear_be_mon_kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >(
                this->m_clear_be_mon_kernel_id ) < this->numAvailableKernels() ) );
    }

    ClContext::kernel_id_t
    ClContext::clearBeamMonitorIoBufferAssignmentKernelId() const SIXTRL_NOEXCEPT
    {
        return ( this->hasClearBeamMonitorIoBufferAssignmentKernel() )
            ? this->m_clear_be_mon_kernel_id : kernel_id_t{ -1 };
    }

    bool ClContext::setClearBeamMonitorIoBufferAssignmentKernelId(
        ClContext::kernel_id_t const clear_assign_kernel_id )
    {
        bool success = false;

        if( ( this->hasSelectedNode() ) &&
            ( clear_assign_kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( clear_assign_kernel_id ) <
              this->numAvailableKernels() ) )
        {
            program_id_t const clear_assign_program_id =
                this->programIdByKernelId( clear_assign_kernel_id );

            if( ( clear_assign_program_id >= program_id_t{ 0 } ) &&
                ( static_cast< size_type >( clear_assign_program_id ) <
                  this->numAvailablePrograms() ) )
            {
                this->m_clear_be_mon_kernel_id  = clear_assign_kernel_id;
                this->m_clear_be_mon_program_id = clear_assign_program_id;
                success = true;
            }
        }

        return success;
    }

    int ClContext::clearBeamMonitorIoBufferAssignment(
        ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg )
    {
        return ( this->hasClearBeamMonitorIoBufferAssignmentKernel() )
            ? this->clearBeamMonitorIoBufferAssignment(
                beam_elements_arg, this->m_clear_be_mon_kernel_id )
            : -1;

    }

    int ClContext::clearBeamMonitorIoBufferAssignment(
        ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
        ClContext::kernel_id_t const clear_assign_kernel_id )
    {
        int success = -1;

        SIXTRL_ASSERT( this->hasSelectedNode() );
        SIXTRL_ASSERT( ( clear_assign_kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( clear_assign_kernel_id ) <
              this->numAvailableKernels() ) );

        SIXTRL_ASSERT( beam_elements_arg.usesCObjectBuffer() );
        NS(Buffer)* beam_elements_buffer = beam_elements_arg.ptrCObjectBuffer();
        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)( beam_elements_buffer ) );

        size_type const num_kernel_args = this->kernelNumArgs( clear_assign_kernel_id );
        SIXTRL_ASSERT(  num_kernel_args >= 1u );

        size_type const num_beam_elements = NS(Buffer_get_num_of_objects)(
            beam_elements_buffer );

        this->assignKernelArgument( clear_assign_kernel_id, 0u, beam_elements_arg );

        if( num_kernel_args >= 2u )
        {
            this->assignKernelArgumentClBuffer(
                clear_assign_kernel_id, 1u, this->internalSuccessFlagBuffer() );
        }

        success = ( this->runKernel(
            clear_assign_kernel_id, num_beam_elements ) ) ? 0 : -1;

        if( ( success == 0 ) && ( num_kernel_args > 1u ) )
        {
            cl::CommandQueue* ptr_queue = this->openClQueue();
            SIXTRL_ASSERT( ptr_queue != nullptr );

            int32_t success_flag = int32_t{ -1 };
            cl_int cl_ret = ptr_queue->enqueueReadBuffer(
                this->internalSuccessFlagBuffer(), CL_TRUE, 0,
                sizeof( success_flag ), &success_flag );

            if( cl_ret == CL_SUCCESS )
            {
                success = ( int )success_flag;
            }

            ptr_queue->finish();
        }

        return success;
    }

    /* --------------------------------------------------------------------- */

    bool ClContext::useOptimizedTrackingByDefault() const SIXTRL_NOEXCEPT
    {
        return this->m_use_optimized_tracking;
    }

    void ClContext::enableOptimizedtrackingByDefault()
    {
        if( ( !this->useOptimizedTrackingByDefault() ) &&
            ( !this->hasSelectedNode() ) )
        {
            this->clear();
            this->m_use_optimized_tracking = true;
            this->doInitDefaultPrograms();
            this->doInitDefaultKernels();
        }

        return;
    }

    void ClContext::disableOptimizedTrackingByDefault()
    {
        if( ( this->useOptimizedTrackingByDefault() ) &&
            ( !this->hasSelectedNode() ) )
        {
            this->clear();

            this->m_use_optimized_tracking = false;
            this->doInitDefaultPrograms();
            this->doInitDefaultKernels();
        }

        return;
    }

    bool ClContext::isBeamBeamTrackingEnabled() const SIXTRL_NOEXCEPT
    {
        return this->m_enable_beam_beam;
    }

    void ClContext::enableBeamBeamTracking()
    {
        if( ( !this->isBeamBeamTrackingEnabled() ) &&
            ( !this->hasSelectedNode() ) )
        {
            this->clear();

            this->m_enable_beam_beam = true;
            this->doInitDefaultPrograms();
            this->doInitDefaultKernels();
        }

        return;
    }

    void ClContext::disableBeamBeamTracking()
    {
        if( (  this->isBeamBeamTrackingEnabled() ) &&
            ( !this->hasSelectedNode() ) )
        {
            this->clear();

             this->m_enable_beam_beam = false;
            this->doInitDefaultPrograms();
            this->doInitDefaultKernels();
        }

        return;
    }

    void ClContext::doResetParticleSetIndices(
        ClContext::size_type const num_particles )
    {
        using size_t = ClContext::size_type;

        this->m_particle_set_indices.clear();
        this->m_particle_set_indices.push_back( size_t{ 0 } );

        this->m_particle_set_index_begins.clear();
        this->m_particle_set_index_begins.push_back( size_t{ 0 } );

        this->m_particle_set_num_particles.clear();
        this->m_particle_set_num_particles.push_back( num_particles );

        this->m_total_num_particles = num_particles;

        return;
    }


    bool ClContext::doInitDefaultPrograms()
    {
        return ( ( ClContextBase::doInitDefaultPrograms() ) &&
                 ( this->doInitDefaultProgramsPrivImpl() ) );
    }

    bool ClContext::doInitDefaultKernels()
    {
        return ( ( ClContextBase::doInitDefaultKernels() ) &&
                 ( this->doInitDefaultKernelsPrivImpl() ) );
    }

    bool ClContext::doSelectNode( ClContext::size_type const node_index )
    {
        return ( ( ClContextBase::doSelectNode( node_index ) ) &&
                 ( this->doSelectNodePrivImpl( node_index ) ) );
    }

    void ClContext::doClear()
    {
        ClContextBase::doClear();
        this->doClearPrivImpl();

        return;
    }

    bool ClContext::doInitDefaultProgramsPrivImpl()
    {
        bool success = false;

        std::string path_to_kernel_dir( NS(PATH_TO_BASE_DIR) );
        path_to_kernel_dir += "sixtracklib/opencl/kernels/";

        std::string path_to_particles_track_prog     = path_to_kernel_dir;
        std::string path_to_particles_track_opt_prog = path_to_kernel_dir;
        std::string path_to_assign_out_buffer_prog    = path_to_kernel_dir;

        if( !this->debugMode() )
        {
            path_to_particles_track_prog     +=
                "track_particles.cl";

            path_to_particles_track_opt_prog +=
                "track_particles_optimized_priv_particles.cl";

            path_to_assign_out_buffer_prog    +=
                "be_monitors_assign_out_buffer.cl";
        }
        else
        {
            path_to_particles_track_prog     +=
                "track_particles_debug.cl";

            path_to_particles_track_opt_prog +=
                "track_particles_optimized_priv_particles_debug.cl";

            path_to_assign_out_buffer_prog    +=
                "be_monitors_assign_out_buffer_debug.cl";
        }

        std::string track_compile_options = "-D_GPUCODE=1";
        track_compile_options += " -DSIXTRL_BUFFER_ARGPTR_DEC=__private";
        track_compile_options += " -DSIXTRL_BUFFER_DATAPTR_DEC=__global";
        track_compile_options += " -DSIXTRL_PARTICLE_ARGPTR_DEC=__global";
        track_compile_options += " -DSIXTRL_PARTICLE_DATAPTR_DEC=__global";

        if( !this->isBeamBeamTrackingEnabled() )
        {
            track_compile_options += " -DSIXTRL_DISABLE_BEAM_BEAM=1";
        }

        track_compile_options += " -I";
        track_compile_options += NS(PATH_TO_SIXTRL_INCLUDE_DIR);

        std::string track_optimized_compile_options = "-D_GPUCODE=1";
        track_optimized_compile_options += " -DSIXTRL_BUFFER_ARGPTR_DEC=__private";
        track_optimized_compile_options += " -DSIXTRL_BUFFER_DATAPTR_DEC=__global";
        track_optimized_compile_options += " -DSIXTRL_PARTICLE_ARGPTR_DEC=__private";
        track_optimized_compile_options += " -DSIXTRL_PARTICLE_DATAPTR_DEC=__private";

        if( !this->isBeamBeamTrackingEnabled() )
        {
            track_optimized_compile_options += " -DSIXTRL_DISABLE_BEAM_BEAM=1";
        }

        track_optimized_compile_options += " -I";
        track_optimized_compile_options += NS(PATH_TO_SIXTRL_INCLUDE_DIR);

        std::string assign_out_buffer_compile_options = " -D_GPUCODE=1";
        assign_out_buffer_compile_options += " -DSIXTRL_BUFFER_ARGPTR_DEC=__private";
        assign_out_buffer_compile_options += " -DSIXTRL_BUFFER_DATAPTR_DEC=__global";
        assign_out_buffer_compile_options += " -DSIXTRL_PARTICLE_ARGPTR_DEC=__global";
        assign_out_buffer_compile_options += " -DSIXTRL_PARTICLE_DATAPTR_DEC=__global";
        assign_out_buffer_compile_options += " -I";
        assign_out_buffer_compile_options += NS(PATH_TO_SIXTRL_INCLUDE_DIR);

        program_id_t const track_program_id = this->addProgramFile(
            path_to_particles_track_prog, track_compile_options );

        program_id_t const track_optimized_program_id = this->addProgramFile(
            path_to_particles_track_opt_prog, track_optimized_compile_options );

        program_id_t const out_buffer_program_id = this->addProgramFile(
            path_to_assign_out_buffer_prog, assign_out_buffer_compile_options );

        if( ( track_program_id            >= program_id_t{ 0 } ) &&
            ( track_optimized_program_id  >= program_id_t{ 0 } ) &&
            ( out_buffer_program_id        >= program_id_t{ 0 } ) )
        {
            if( !this->useOptimizedTrackingByDefault() )
            {
                this->m_track_until_turn_program_id   = track_program_id;
                this->m_track_single_turn_program_id  = track_program_id;
                this->m_track_elem_by_elem_program_id = track_program_id;
                this->m_track_line_program_id         = track_program_id;
            }
            else
            {
                this->m_track_until_turn_program_id   = track_optimized_program_id;
                this->m_track_single_turn_program_id  = track_optimized_program_id;
                this->m_track_elem_by_elem_program_id = track_optimized_program_id;
                this->m_track_line_program_id         = track_optimized_program_id;
            }

            this->m_assign_be_mon_out_buffer_program_id = out_buffer_program_id;
            this->m_clear_be_mon_program_id            = out_buffer_program_id;

            success = true;
        }

        return success;
    }

    bool ClContext::doInitDefaultKernelsPrivImpl()
    {
        bool success = false;

        if( this->hasSelectedNode() )
        {
            program_id_t const max_program_id = static_cast< program_id_t >(
                this->numAvailablePrograms() );

            if( ( this->m_track_until_turn_program_id >= program_id_t{ 0 } ) &&
                ( this->m_track_until_turn_program_id <  max_program_id ) )
            {
                std::string kernel_name( SIXTRL_C99_NAMESPACE_PREFIX_STR );
                kernel_name += "Track_particles_until_turn";

                if( this->useOptimizedTrackingByDefault() )
                {
                    kernel_name += "_opt_pp";
                }

                if( this->debugMode() )
                {
                    kernel_name += "_debug";
                }

                kernel_name += "_opencl";

                kernel_id_t const kernel_id = this->enableKernel(
                    kernel_name.c_str(), this->m_track_until_turn_program_id );

                if( kernel_id >= kernel_id_t{ 0 } )
                {
                    success = this->setTrackingKernelId( kernel_id );
                }
            }

            if( ( success ) &&
                ( this->m_track_single_turn_program_id >= program_id_t{ 0 } ) &&
                ( this->m_track_single_turn_program_id <  max_program_id ) )
            {
                std::string kernel_name( SIXTRL_C99_NAMESPACE_PREFIX_STR );
                kernel_name += "Track_particles_single_turn";

                if( this->useOptimizedTrackingByDefault() )
                {
                    kernel_name += "_opt_pp";
                }

                if( this->debugMode() )
                {
                    kernel_name += "_debug";
                }

                kernel_name += "_opencl";

                kernel_id_t const kernel_id = this->enableKernel(
                    kernel_name.c_str(), this->m_track_single_turn_program_id );

                if( kernel_id >= kernel_id_t{ 0 } )
                {
                    success = this->setSingleTurnTrackingKernelId( kernel_id );
                }
            }

            if( ( success ) &&
                ( this->m_track_elem_by_elem_program_id >= program_id_t{ 0 } ) &&
                ( this->m_track_elem_by_elem_program_id <  max_program_id ) )
            {
                std::string kernel_name( SIXTRL_C99_NAMESPACE_PREFIX_STR );
                kernel_name += "Track_particles_elem_by_elem";

                if( this->useOptimizedTrackingByDefault() )
                {
                    kernel_name += "_opt_pp";
                }

                if( this->debugMode() )
                {
                    kernel_name += "_debug";
                }

                kernel_name += "_opencl";

                kernel_id_t const kernel_id = this->enableKernel(
                    kernel_name.c_str(), this->m_track_elem_by_elem_program_id );

                if( kernel_id >= kernel_id_t{ 0 } )
                {
                    success = this->setElementByElementTrackingKernelId( kernel_id );
                }
            }

            if( ( success ) &&
                ( this->m_track_line_program_id >= program_id_t{ 0 } ) &&
                ( this->m_track_line_program_id <  max_program_id ) )
            {
                std::string kernel_name( SIXTRL_C99_NAMESPACE_PREFIX_STR );
                kernel_name += "Track_particles_line";

                if( this->useOptimizedTrackingByDefault() )
                {
                    kernel_name += "_opt_pp";
                }

                if( this->debugMode() )
                {
                    kernel_name += "_debug";
                }

                kernel_name += "_opencl";

                kernel_id_t const kernel_id = this->enableKernel(
                    kernel_name.c_str(), this->m_track_line_program_id );

                if( kernel_id >= kernel_id_t{ 0 } )
                {
                    success = this->setTrackLineKernelId( kernel_id );
                }
            }

            if( ( success ) &&
                ( this->m_assign_be_mon_out_buffer_program_id >= program_id_t{ 0 } ) &&
                ( this->m_assign_be_mon_out_buffer_program_id <  max_program_id ) )
            {
                std::string kernel_name( SIXTRL_C99_NAMESPACE_PREFIX_STR );
                kernel_name += "BeamMonitor_assign_out_buffer_from_offset";

                if( this->debugMode() )
                {
                    kernel_name += "_debug";
                }

                kernel_name += "_opencl";

                kernel_id_t const kernel_id = this->enableKernel(
                    kernel_name.c_str(), this->m_assign_be_mon_out_buffer_program_id );

                if( kernel_id >= kernel_id_t{ 0 } )
                {
                    success = this->setAssignBeamMonitorIoBufferKernelId( kernel_id );
                }
            }

            if( ( success ) &&
                ( this->m_clear_be_mon_program_id >= program_id_t{ 0 } ) &&
                ( this->m_clear_be_mon_program_id <  max_program_id ) )
            {
                std::string kernel_name( SIXTRL_C99_NAMESPACE_PREFIX_STR );
                kernel_name += "BeamMonitor_clear_all_line_obj";

                if( this->debugMode() )
                {
                    kernel_name += "_debug";
                }

                kernel_name += "_opencl";

                kernel_id_t const kernel_id = this->enableKernel(
                    kernel_name.c_str(), this->m_clear_be_mon_program_id );

                if( kernel_id >= kernel_id_t{ 0 } )
                {
                    success = this->setClearBeamMonitorIoBufferAssignmentKernelId(
                        kernel_id );
                }
            }
        }

        return success;
    }

    bool ClContext::doSelectNodePrivImpl(
         ClContext::size_type const node_index )
    {
        bool success = false;

        using config_t = ::NS(ElemByElemConfig);

        if( ( this->hasSelectedNode() ) &&
            ( this->selectedNodeIndex() == node_index ) )
        {
            cl::Context* ptr_context = this->openClContext();

            if( ptr_context != nullptr )
            {
                this->m_elem_by_elem_config_buffer = cl::Buffer( *ptr_context,
                     CL_MEM_READ_WRITE, sizeof( config_t ), nullptr );

                success = true;
            }
        }

        return success;
    }

    void ClContext::doClearPrivImpl()
    {
        cl::Buffer dummy_buffer;
        this->m_elem_by_elem_config_buffer = dummy_buffer;

        return;
    }
}

#endif /* defined( __cplusplus ) */

/* ========================================================================= */

NS(ClContext)* NS(ClContext_create)()
{
    return new SIXTRL_CXX_NAMESPACE::ClContext;
}

NS(ClContext)* NS(ClContext_new)( const char* node_id_str )
{
    return new SIXTRL_CXX_NAMESPACE::ClContext( node_id_str, nullptr );
}

void NS(ClContext_delete)( NS(ClContext)* SIXTRL_RESTRICT ctx )
{
    delete ctx;
}

void NS(ClContext_clear)( NS(ClContext)* SIXTRL_RESTRICT ctx )
{
    if( ctx != nullptr ) ctx->clear();
    return;
}

bool NS(ClContext_has_tracking_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->hasTrackingKernel() : false;
}


int NS(ClContext_get_tracking_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->trackingKernelId() : -1;
}

bool NS(ClContext_set_tracking_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const tracking_kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->setTrackingKernelId( tracking_kernel_id ) : false;
}

/* ------------------------------------------------------------------------- */

int NS(ClContext_continue_tracking)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(context_num_turns_t) const until_turn )
{
    return ( ctx != nullptr ) ? ctx->track( until_turn ) : -1;
}

int NS(ClContext_continue_tracking_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const track_kernel_id,
    NS(context_num_turns_t) const until_turn )
{
    return ( ctx != nullptr ) ? ctx->track( until_turn, track_kernel_id ) : -1;
}

int NS(ClContext_track)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(context_num_turns_t) const until_turn )
{
    return ( ( ctx != nullptr ) && ( ptr_particles_arg != nullptr ) &&
             ( ptr_beam_elements_arg != nullptr ) )
        ? ctx->track( *ptr_particles_arg, *ptr_beam_elements_arg, until_turn )
        : -1;
}

int NS(ClContext_track_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(context_num_turns_t) const until_turn, int const tracking_kernel_id )
{
    return ( ( ctx != nullptr ) && ( ptr_particles_arg != nullptr ) &&
             ( ptr_beam_elements_arg != nullptr ) )
        ? ctx->track( *ptr_particles_arg,
                      *ptr_beam_elements_arg, until_turn, tracking_kernel_id )
        : -1;
}

/* ------------------------------------------------------------------------- */

bool NS(ClContext_has_line_tracking_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->hasLineTrackingKernel() : false;
}

int NS(ClContext_get_line_tracking_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    SIXTRL_ASSERT( ctx != nullptr );
    return ctx->lineTrackingKernelId();
}

bool NS(ClContext_set_line_tracking_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr ) ? ctx->setTrackLineKernelId( kernel_id ) : false;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

int NS(ClContext_continue_line_tracking)( NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(buffer_size_t) const line_begin_idx,
    NS(buffer_size_t) const line_end_idx, bool const finish_turn )
{
    SIXTRL_ASSERT( ctx != nullptr );
    return ctx->trackLine( line_begin_idx, line_end_idx, finish_turn,
        ctx->lineTrackingKernelId() );
}

int NS(ClContext_continue_line_tracking_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(buffer_size_t) const line_begin_idx,
    NS(buffer_size_t) const line_end_idx,
    bool const finish_turn, int const line_tracking_kernel_id )
{
    SIXTRL_ASSERT( ctx != nullptr );
    return ctx->trackLine( line_begin_idx, line_end_idx, finish_turn,
                           line_tracking_kernel_id );
}

int NS(ClContext_track_line)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(buffer_size_t) const particle_set_index,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(buffer_size_t) const line_begin_idx,
    NS(buffer_size_t) const line_end_idx, bool const finish_turn )
{
    SIXTRL_ASSERT( ctx != nullptr );
    SIXTRL_ASSERT( ptr_particles_arg != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_beam_elements_arg != SIXTRL_NULLPTR );
    return ctx->trackLine( *ptr_particles_arg, particle_set_index,
        *ptr_beam_elements_arg, line_begin_idx, line_end_idx, finish_turn,
            ctx->lineTrackingKernelId() );
}

int NS(ClContext_track_line_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(buffer_size_t) const particle_set_index,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(buffer_size_t) const line_begin_idx,
    NS(buffer_size_t) const line_end_idx, bool const finish_turn,
    int const line_tracking_kernel_id )
{
    SIXTRL_ASSERT( ctx != nullptr );
    SIXTRL_ASSERT( ctx != nullptr );
    SIXTRL_ASSERT( ptr_particles_arg != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_beam_elements_arg != SIXTRL_NULLPTR );

    return ctx->trackLine( *ptr_particles_arg, particle_set_index,
        *ptr_beam_elements_arg, line_begin_idx, line_end_idx, finish_turn,
            line_tracking_kernel_id );
}


/* ------------------------------------------------------------------------- */

bool NS(ClContext_has_single_turn_tracking_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->hasSingleTurnTrackingKernel() : false;
}

int NS(ClContext_get_single_turn_tracking_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->singleTurnTackingKernelId() : -1;
}

bool NS(ClContext_set_single_turn_tracking_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const tracking_kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->setSingleTurnTrackingKernelId( tracking_kernel_id ) : false;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

int NS(ClContext_continue_tracking_single_turn)(
    NS(ClContext)* SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->trackSingleTurn() : -1;
}

int NS(ClContext_continue_tracking_single_turn_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const kernel_id )
{
    return ( ctx != nullptr ) ? ctx->trackSingleTurn( kernel_id ) : -1;
}

int NS(ClContext_track_single_turn)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg )
{
    return ( ( ctx != nullptr ) && ( ptr_particles_arg != nullptr ) &&
             ( ptr_beam_elements_arg != nullptr ) )
        ? ctx->trackSingleTurn( *ptr_particles_arg, *ptr_beam_elements_arg )
        : -1;
}

int NS(ClContext_track_single_turn_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    int const tracking_kernel_id )
{
    return ( ( ctx != nullptr ) && ( ptr_particles_arg != nullptr ) &&
             ( ptr_beam_elements_arg != nullptr ) )
        ? ctx->trackSingleTurn( *ptr_particles_arg, *ptr_beam_elements_arg,
                                 tracking_kernel_id ) : -1;
}

/* ------------------------------------------------------------------------- */

bool NS(ClContext_has_element_by_element_tracking_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->hasElementByElementTrackingKernel() : false;
}

int NS(ClContext_get_element_by_element_tracking_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return (ctx != nullptr ) ? ctx->elementByElementTrackingKernelId() : -1;
}

bool NS(ClContext_set_element_by_element_tracking_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const tracking_kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->setElementByElementTrackingKernelId( tracking_kernel_id )
        : false;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

int NS(ClContext_continue_tracking_element_by_element)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(buffer_size_t) const until_turn,
    NS(buffer_size_t) const out_buffer_index_offset )
{
    return ( ctx != nullptr )
        ? ctx->trackElementByElement( until_turn, out_buffer_index_offset )
        : -1;
}

int NS(ClContext_continue_tracking_element_by_element_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(buffer_size_t) const until_turn,
    NS(buffer_size_t) const out_buffer_index_offset,
    int const kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->trackElementByElement(
            until_turn, out_buffer_index_offset, kernel_id )
        : -1;
}

int NS(ClContext_track_element_by_element)(
    NS(ClContext)*  SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_elem_by_elem_buffer_arg,
    NS(buffer_size_t) const until_turn,
    NS(buffer_size_t) const out_buffer_index_offset )
{
    return ( ( ctx != nullptr ) && ( ptr_particles_arg != nullptr ) &&
             ( ptr_beam_elements_arg != nullptr ) &&
             ( ptr_elem_by_elem_buffer_arg != nullptr ) )
        ? ctx->trackElementByElement( *ptr_particles_arg, *ptr_beam_elements_arg,
                                      *ptr_elem_by_elem_buffer_arg,
                                      until_turn, out_buffer_index_offset )
        : -1;
}

int NS(ClContext_track_element_by_element_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_elem_by_elem_buffer_arg,
    NS(buffer_size_t) const out_buffer_index_offset,
    NS(buffer_size_t) const until_turn,
    int const tracking_kernel_id )
{
    return ( ( ctx != nullptr ) && ( ptr_particles_arg != nullptr ) &&
             ( ptr_beam_elements_arg != nullptr ) &&
             ( ptr_elem_by_elem_buffer_arg != nullptr ) )
        ? ctx->trackElementByElement( *ptr_particles_arg, *ptr_beam_elements_arg,
                                      *ptr_elem_by_elem_buffer_arg,
                                      until_turn, out_buffer_index_offset,
                                      tracking_kernel_id )
        : -1;
}

/* ------------------------------------------------------------------------- */

bool NS(ClContext_has_assign_beam_monitor_out_buffer_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return (ctx != nullptr ) ? ctx->hasAssignBeamMonitorIoBufferKernel() : false;
}

int NS(ClContext_get_assign_beam_monitor_out_buffer_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->assignBeamMonitorIoBufferKernelId() : -1;
}

bool NS(ClContext_set_assign_beam_monitor_out_buffer_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const assign_kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->setAssignBeamMonitorIoBufferKernelId( assign_kernel_id )
        : false;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

int NS(ClContext_assign_beam_monitor_out_buffer)(
    NS(ClContext)*  SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_out_buffer_arg,
    NS(buffer_size_t) const min_turn_id,
    NS(buffer_size_t) const out_particle_block_offset )
{
    return ( ( ctx != nullptr ) && ( ptr_beam_elements_arg != nullptr ) &&
             ( ptr_out_buffer_arg != nullptr ) )
        ? ctx->assignBeamMonitorIoBuffer( *ptr_beam_elements_arg,
            *ptr_out_buffer_arg, min_turn_id, out_particle_block_offset )
        : -1;
}

int NS(ClContext_assign_beam_monitor_out_buffer_with_kernel_id)(
    NS(ClContext)*  SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_out_buffer_arg,
    NS(buffer_size_t) const min_turn_id,
    NS(buffer_size_t) const out_particle_block_offset,
    int const assign_kernel_id )
{
    return ( ( ctx != nullptr ) && ( ptr_beam_elements_arg != nullptr ) &&
             ( ptr_out_buffer_arg != nullptr ) )
        ? ctx->assignBeamMonitorIoBuffer( *ptr_beam_elements_arg,
            *ptr_out_buffer_arg, min_turn_id, out_particle_block_offset,
                assign_kernel_id )
        : -1;
}

bool NS(ClContext_has_clear_beam_monitor_out_assignment_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr )
        ? ctx->hasClearBeamMonitorIoBufferAssignmentKernel()
        : false;
}

int NS(ClContext_get_clear_beam_monitor_out_assignment_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return (ctx != nullptr )
        ? ctx->clearBeamMonitorIoBufferAssignmentKernelId() : -1;
}

bool NS(ClContext_set_clear_beam_monitor_out_assignment_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const kernel_id )
{
    bool success = false;

    if( ctx != nullptr )
    {
        success = ctx->setClearBeamMonitorIoBufferAssignmentKernelId( kernel_id );
    }

    return success;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

int NS(ClContext_clear_beam_monitor_out_assignment)(
    NS(ClContext)*  SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT beam_elements_arg )
{
    return ( ( ctx != nullptr ) && ( beam_elements_arg != nullptr ) )
        ? ctx->clearBeamMonitorIoBufferAssignment( *beam_elements_arg )
        : -1;
}

int NS(ClContext_clear_beam_monitor_out_assignment_with_kernel)(
    NS(ClContext)*  SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT beam_elements_arg,
    int const kernel_id )
{
    return ( ( ctx != nullptr ) && ( beam_elements_arg != nullptr ) )
        ? ctx->clearBeamMonitorIoBufferAssignment(
            *beam_elements_arg, kernel_id )
        : -1;
}

/* ------------------------------------------------------------------------- */

bool NS(ClContext_uses_optimized_tracking_by_default)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->useOptimizedTrackingByDefault() : false;
}

void NS(ClContext_enable_optimized_tracking_by_default)(
    NS(ClContext)* SIXTRL_RESTRICT ctx )
{
    if( ctx != nullptr ) ctx->enableOptimizedtrackingByDefault();
    return;
}

void NS(ClContext_disable_optimized_tracking_by_default)(
    NS(ClContext)* SIXTRL_RESTRICT ctx )
{
    if( ctx != nullptr ) ctx->disableOptimizedTrackingByDefault();
    return;
}

/* ------------------------------------------------------------------------- */

bool NS(ClContext_is_beam_beam_tracking_enabled)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->isBeamBeamTrackingEnabled() : false;
}


void NS(ClContext_enable_beam_beam_tracking)(
    NS(ClContext)* SIXTRL_RESTRICT ctx )
{
    if( ctx != nullptr )
    {
        ctx->enableBeamBeamTracking();
    }

    return;
}

void NS(ClContext_disable_beam_beam_tracking)(
    NS(ClContext)* SIXTRL_RESTRICT ctx )
{
    if( ctx != nullptr )
    {
        ctx->disableBeamBeamTracking();
    }

    return;
}

#endif /* !defined( __CUDACC__ ) */

/* end: sixtracklib/opencl/internal/context.cpp */
