#include "sixtracklib/common/internal/track_job_base.h"

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <cstddef>
        #include <cstdint>
        #include <cstdlib>
        #include <memory>
        #include <string>
        #include <vector>
    #else /* !defined( __cplusplus ) */
        #include <stdbool.h>
        #include <stddef.h>
        #include <stdint.h>
        #include <stdlib.h>
        #include <limits.h>
    #endif /* !defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/track/definitions.h"

    #if defined( __cplusplus )
        #include "sixtracklib/common/buffer.hpp"
    #endif /* defined( __cplusplus ) */

    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/beam_elements.h"
    #include "sixtracklib/common/be_monitor/be_monitor.h"
    #include "sixtracklib/common/be_monitor/output_buffer.h"
    #include "sixtracklib/common/output/elem_by_elem_config.h"
    #include "sixtracklib/common/output/output_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    TrackJobBase::size_type
    TrackJobBase::DefaultNumParticleSetIndices() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TRACK_JOB_DEFAULT_NUM_PARTICLE_SETS;
    }

    TrackJobBase::size_type const*
    TrackJobBase::DefaultParticleSetIndicesBegin() SIXTRL_NOEXCEPT
    {
        TrackJobBase::size_type const* ptr =
            &SIXTRL_CXX_NAMESPACE::TRACK_JOB_DEFAULT_PARTICLE_SET_INDICES[ 0 ];
        return ptr;
    }

    TrackJobBase::size_type const*
    TrackJobBase::DefaultParticleSetIndicesEnd() SIXTRL_NOEXCEPT
    {
        TrackJobBase::size_type const* end_ptr =
            TrackJobBase::DefaultParticleSetIndicesBegin();

        std::advance( end_ptr,
            SIXTRL_CXX_NAMESPACE::TRACK_JOB_DEFAULT_NUM_PARTICLE_SETS );

        return end_ptr;
    }

    void TrackJobBase::clear()
    {
        this->doClear();
        return;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBase::collect()
    {
        this->doCollect( this->m_collect_flags );
    }

    void TrackJobBase::collect( TrackJobBase::collect_flag_t const flags )
    {
        this->doCollect( flags & SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_ALL );
    }

    void TrackJobBase::collectParticles()
    {
        this->doCollect( SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_PARTICLES );
    }


    void TrackJobBase::collectBeamElements()
    {
        this->doCollect(
            SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_BEAM_ELEMENTS );
    }

    void TrackJobBase::collectOutput()
    {
        this->doCollect( SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_OUTPUT );
    }

    void TrackJobBase::enableCollectParticles()  SIXTRL_NOEXCEPT
    {
        this->m_collect_flags |=
            SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_PARTICLES;
    }

    void TrackJobBase::disableCollectParticles() SIXTRL_NOEXCEPT
    {
        this->m_collect_flags = TrackJobBase::UnsetCollectFlag(
            this->m_collect_flags,
            SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_PARTICLES );
    }

    bool TrackJobBase::isCollectingParticles() const SIXTRL_NOEXCEPT
    {
        return TrackJobBase::IsCollectFlagSet( this->m_collect_flags,
            SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_PARTICLES );
    }

    void TrackJobBase::enableCollectBeamElements()  SIXTRL_NOEXCEPT
    {
        this->m_collect_flags |=
            SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_BEAM_ELEMENTS;
    }

    void TrackJobBase::disableCollectBeamElements() SIXTRL_NOEXCEPT
    {
        this->m_collect_flags = TrackJobBase::UnsetCollectFlag(
            this->m_collect_flags,
            SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_BEAM_ELEMENTS );
    }

    bool TrackJobBase::isCollectingBeamElements() const SIXTRL_NOEXCEPT
    {
        return TrackJobBase::IsCollectFlagSet( this->m_collect_flags,
                SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_BEAM_ELEMENTS );
    }

    void TrackJobBase::enableCollectOutput()  SIXTRL_NOEXCEPT
    {
        this->m_collect_flags |=
            SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_OUTPUT;
    }

    void TrackJobBase::disableCollectOutput() SIXTRL_NOEXCEPT
    {
        this->m_collect_flags = TrackJobBase::UnsetCollectFlag(
            this->m_collect_flags,
            SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_OUTPUT );
    }

    bool TrackJobBase::isCollectingOutput() const SIXTRL_NOEXCEPT
    {
        return TrackJobBase::IsCollectFlagSet( this->m_collect_flags,
                SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_OUTPUT );
    }

    TrackJobBase::collect_flag_t
    TrackJobBase::collectFlags() const SIXTRL_NOEXCEPT
    {
        return this->m_collect_flags;
    }

    void TrackJobBase::setCollectFlags( TrackJobBase::collect_flag_t
        const flags ) SIXTRL_NOEXCEPT
    {
        this->m_collect_flags = ( flags &
            SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_ALL );
    }

    bool TrackJobBase::requiresCollecting() const SIXTRL_NOEXCEPT
    {
        return this->m_requires_collect;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBase::track_status_t TrackJobBase::track(
        TrackJobBase::size_type const until_turn )
    {
        return this->doTrackUntilTurn( until_turn );
    }

    TrackJobBase::track_status_t TrackJobBase::trackElemByElem(
        TrackJobBase::size_type const until_turn )
    {
        return this->doTrackElemByElem( until_turn );
    }

    TrackJobBase::track_status_t TrackJobBase::trackLine(
        TrackJobBase::size_type const beam_elements_begin_index,
        TrackJobBase::size_type const beam_elements_end_index,
        bool const finish_turn )
    {
        return this->doTrackLine(
            beam_elements_begin_index, beam_elements_end_index, finish_turn );
    }

    bool TrackJobBase::reset(
        TrackJobBase::buffer_t& SIXTRL_RESTRICT_REF particles_buffer,
        TrackJobBase::buffer_t& SIXTRL_RESTRICT_REF be_buffer,
        TrackJobBase::buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        TrackJobBase::size_type const until_turn_elem_by_elem )
    {
        using c_buffer_t = TrackJobBase::c_buffer_t;

        this->doClear();

        c_buffer_t* ptr_pb  = particles_buffer.getCApiPtr();
        c_buffer_t* ptr_eb  = be_buffer.getCApiPtr();
        c_buffer_t* ptr_out = ( ptr_output_buffer != nullptr ) ?
            ptr_output_buffer->getCApiPtr() : nullptr;

        bool const success = this->doReset(
            ptr_pb, ptr_eb, ptr_out, until_turn_elem_by_elem );

        if( success )
        {
            this->doSetPtrParticleBuffer( &particles_buffer );
            this->doSetPtrBeamElementsBuffer( &be_buffer );

            if( ( ptr_out != nullptr ) && ( this->hasOutputBuffer() ) )
            {
                this->doSetPtrOutputBuffer( ptr_output_buffer );
            }
        }

        return success;
    }

    bool TrackJobBase::reset(
        TrackJobBase::buffer_t& SIXTRL_RESTRICT_REF particles_buffer,
        TrackJobBase::size_type const particle_set_index,
        TrackJobBase::buffer_t& SIXTRL_RESTRICT_REF be_buffer,
        TrackJobBase::buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        TrackJobBase::size_type const until_turn_elem_by_elem )
    {
        using size_t = TrackJobBase::size_type;

        size_t particle_set_indices[] = { size_t{ 0 } };
        particle_set_indices[ 0 ] = particle_set_index;

        return TrackJobBase::reset( particles_buffer,
            &particle_set_indices[ 0 ], &particle_set_indices[ 1 ], be_buffer,
                ptr_output_buffer, until_turn_elem_by_elem );
    }

    bool TrackJobBase::reset(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT be_buffer,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        TrackJobBase::size_type const until_turn_elem_by_elem )
    {
        this->doClear();

        bool const success = this->doReset( particles_buffer, be_buffer,
                ptr_output_buffer, until_turn_elem_by_elem );

        if( success )
        {
            this->doSetPtrCParticleBuffer( particles_buffer );
            this->doSetPtrCBeamElementsBuffer( be_buffer );

            if( ( ptr_output_buffer != nullptr ) && ( this->hasOutputBuffer() ) )
            {
                this->doSetPtrCOutputBuffer( ptr_output_buffer );
            }
        }

        return success;
    }

    bool TrackJobBase::reset(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        TrackJobBase::size_type const particle_set_index,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT be_buffer,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        TrackJobBase::size_type const until_turn_elem_by_elem )
    {
        return TrackJobBase::reset( particles_buffer,
            TrackJobBase::size_type{ 1 }, &particle_set_index, be_buffer,
                ptr_output_buffer, until_turn_elem_by_elem );
    }

    bool TrackJobBase::reset(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        TrackJobBase::size_type const num_particle_sets,
        TrackJobBase::size_type const* SIXTRL_RESTRICT
            particle_set_indices_begin,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT be_buffer,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        TrackJobBase::size_type const until_turn_elem_by_elem )
    {
        TrackJobBase::size_type const* particle_set_indices_end =
            particle_set_indices_begin;

        if( ( particle_set_indices_end != nullptr ) &&
            ( num_particle_sets > TrackJobBase::size_type{ 0 } ) )
        {
            std::advance( particle_set_indices_end, num_particle_sets );
        }

        return this->reset( particles_buffer,
            particle_set_indices_begin, particle_set_indices_end,
            be_buffer, ptr_output_buffer, until_turn_elem_by_elem );
    }

    bool TrackJobBase::selectParticleSet(
        TrackJobBase::size_type const particle_set_index )
    {
        using buffer_t   = TrackJobBase::buffer_t;
        using c_buffer_t = TrackJobBase::c_buffer_t;
        using size_t = TrackJobBase::size_type;

        bool success = false;

        buffer_t*   ptr_particles_buffer   = this->ptrOutputBuffer();
        buffer_t*   ptr_beam_elem_buffer   = this->ptrBeamElementsBuffer();

        c_buffer_t* ptr_c_particles_buffer = this->ptrCParticlesBuffer();
        c_buffer_t* ptr_c_beam_elem_buffer = this->ptrCBeamElementsBuffer();

        if( ( ptr_c_particles_buffer != nullptr ) &&
            ( !::NS(Buffer_needs_remapping)( ptr_c_particles_buffer ) ) &&
            ( static_cast< size_t >( ::NS(Buffer_get_num_of_objects)(
                ptr_c_particles_buffer ) ) > particle_set_index ) &&
            ( ptr_c_beam_elem_buffer != nullptr ) &&
            ( !::NS(Buffer_needs_remapping)( ptr_c_beam_elem_buffer ) ) )
        {
            buffer_t* ptr_output_buffer = nullptr;
            c_buffer_t* ptr_c_output_buffer = nullptr;

            if( ( this->hasOutputBuffer() ) && ( !this->ownsOutputBuffer() ) )
            {
                ptr_output_buffer   = this->ptrOutputBuffer();
                ptr_c_output_buffer = this->ptrCOutputBuffer();

                SIXTRL_ASSERT( ::NS(Buffer_needs_remapping)(
                    ptr_c_output_buffer ) );
            }

            if( ( ptr_particles_buffer != nullptr ) &&
                ( ptr_beam_elem_buffer != nullptr ) )
            {
                SIXTRL_ASSERT(
                    ( ( ptr_output_buffer != nullptr ) &&
                      ( ptr_c_output_buffer != nullptr ) ) ||
                    ( ( ptr_output_buffer == nullptr ) &&
                      ( ptr_c_output_buffer == nullptr ) ) );

                SIXTRL_ASSERT(
                    ( ptr_particles_buffer->getCApiPtr() ==
                      ptr_c_particles_buffer ) &&
                    ( ptr_beam_elem_buffer->getCApiPtr() ==
                      ptr_c_beam_elem_buffer ) );

                if( ptr_c_output_buffer != nullptr )
                {
                    ::NS(Buffer_clear)( ptr_c_output_buffer, true );
                }

                size_t particle_set_indices[ 1 ] = { size_t{ 0 } };
                particle_set_indices[ 0 ] = particle_set_index;

                success = this->reset( *ptr_particles_buffer,
                    &particle_set_indices[ 0 ], &particle_set_indices[ 1 ],
                        *ptr_beam_elem_buffer, ptr_output_buffer,
                            this->untilTurnElemByElem() );
            }
            else if( ( ptr_c_particles_buffer != nullptr ) &&
                     ( ptr_c_beam_elem_buffer != nullptr ) )
            {
                if( ptr_c_output_buffer != nullptr )
                {
                    ::NS(Buffer_clear)( ptr_c_output_buffer, true );
                }

                success = this->reset( ptr_c_particles_buffer, size_t{ 1 },
                    &particle_set_index, ptr_c_beam_elem_buffer,
                        ptr_c_output_buffer, this->untilTurnElemByElem() );
            }
        }

        return success;
    }

    bool TrackJobBase::assignOutputBuffer(
        TrackJobBase::buffer_t& SIXTRL_RESTRICT_REF output_buffer )
    {
        bool success = false;

        if( this->doAssignNewOutputBuffer( output_buffer.getCApiPtr() ) )
        {
            if( this->hasOutputBuffer() )
            {
                SIXTRL_ASSERT( output_buffer.getCApiPtr() ==
                    this->ptrCOutputBuffer() );

                this->doSetPtrOutputBuffer( &output_buffer );
            }

            success = true;
        }

        return success;
    }

    bool TrackJobBase::assignOutputBuffer(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer )
    {
        return this->doAssignNewOutputBuffer( ptr_output_buffer );
    }

    /* --------------------------------------------------------------------- */

    TrackJobBase::type_t
    TrackJobBase::type() const SIXTRL_NOEXCEPT
    {
        return this->m_type_id;
    }

    std::string const&
    TrackJobBase::typeStr() const SIXTRL_NOEXCEPT
    {
        return this->m_type_str;
    }

    char const* TrackJobBase::ptrTypeStr() const SIXTRL_NOEXCEPT
    {
        return this->m_type_str.c_str();
    }

    bool TrackJobBase::hasDeviceIdStr() const SIXTRL_RESTRICT
    {
        return ( !this->m_device_id_str.empty() );
    }

    std::string const&
    TrackJobBase::deviceIdStr() const SIXTRL_NOEXCEPT
    {
        return this->m_device_id_str;
    }

    char const*
    TrackJobBase::ptrDeviceIdStr() const SIXTRL_NOEXCEPT
    {
        return this->m_device_id_str.c_str();
    }

    bool
    TrackJobBase::hasConfigStr() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_config_str.empty() );
    }

    std::string const&
    TrackJobBase::configStr()   const SIXTRL_NOEXCEPT
    {
        return this->m_config_str;
    }

    char const*
    TrackJobBase::ptrConfigStr() const SIXTRL_NOEXCEPT
    {
        return this->m_config_str.c_str();
    }

    /* --------------------------------------------------------------------- */

    TrackJobBase::size_type
    TrackJobBase::numParticleSets() const SIXTRL_NOEXCEPT
    {
        return this->m_particle_set_indices.size();
    }

    TrackJobBase::size_type const*
    TrackJobBase::particleSetIndicesBegin() const SIXTRL_NOEXCEPT
    {
        return this->m_particle_set_indices.data();
    }

    TrackJobBase::size_type const*
    TrackJobBase::particleSetIndicesEnd() const SIXTRL_NOEXCEPT
    {
        TrackJobBase::size_type const* end_ptr =
            this->particleSetIndicesBegin();

        SIXTRL_ASSERT( end_ptr != nullptr );
        std::advance( end_ptr, this->numParticleSets() );

        return end_ptr;
    }

    TrackJobBase::size_type TrackJobBase::particleSetIndex(
        TrackJobBase::size_type const n ) const
    {
        return this->m_particle_set_indices.at( n );
    }

    /* --------------------------------------------------------------------- */

    TrackJobBase::particle_index_t
    TrackJobBase::minParticleId() const SIXTRL_NOEXCEPT
    {
        return this->m_min_particle_id;
    }

    TrackJobBase::particle_index_t
    TrackJobBase::maxParticleId() const SIXTRL_NOEXCEPT
    {
        return this->m_max_particle_id;
    }

    TrackJobBase::particle_index_t
    TrackJobBase::minElementId()  const SIXTRL_NOEXCEPT
    {
        return this->m_min_element_id;
    }

    TrackJobBase::particle_index_t
    TrackJobBase::maxElementId()  const SIXTRL_NOEXCEPT
    {
        return this->m_max_element_id;
    }

    TrackJobBase::particle_index_t
    TrackJobBase::minInitialTurnId() const SIXTRL_NOEXCEPT
    {
        return this->m_min_initial_turn_id;
    }

    TrackJobBase::particle_index_t
    TrackJobBase::maxInitialTurnId() const SIXTRL_NOEXCEPT
    {
        return this->m_max_initial_turn_id;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBase::buffer_t*
    TrackJobBase::ptrParticlesBuffer() SIXTRL_NOEXCEPT
    {
        using _this_t = TrackJobBase;
        using ptr_t   = _this_t::buffer_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).ptrParticlesBuffer() );
    }

    TrackJobBase::buffer_t const*
    TrackJobBase::ptrParticlesBuffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_particles_buffer == nullptr ) ||
            ( this->m_ptr_particles_buffer->getCApiPtr() ==
              this->m_ptr_c_particles_buffer ) );

        return this->m_ptr_particles_buffer;
    }

    TrackJobBase::c_buffer_t*
    TrackJobBase::ptrCParticlesBuffer() SIXTRL_NOEXCEPT
    {
        using _this_t = TrackJobBase;
        using ptr_t   = _this_t::c_buffer_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).ptrCParticlesBuffer() );
    }

    TrackJobBase::c_buffer_t const*
    TrackJobBase::ptrCParticlesBuffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_particles_buffer == nullptr ) ||
            ( this->m_ptr_particles_buffer->getCApiPtr() ==
              this->m_ptr_c_particles_buffer ) );

        return this->m_ptr_c_particles_buffer;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBase::buffer_t*
    TrackJobBase::ptrBeamElementsBuffer() SIXTRL_NOEXCEPT
    {
        using _this_t = TrackJobBase;
        using ptr_t   = _this_t::buffer_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).ptrBeamElementsBuffer() );
    }

    TrackJobBase::buffer_t const*
    TrackJobBase::ptrBeamElementsBuffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_beam_elem_buffer == nullptr ) ||
            ( this->m_ptr_beam_elem_buffer->getCApiPtr() ==
              this->m_ptr_c_beam_elem_buffer ) );

        return this->m_ptr_beam_elem_buffer;
    }

    TrackJobBase::c_buffer_t*
    TrackJobBase::ptrCBeamElementsBuffer() SIXTRL_NOEXCEPT
    {
        using _this_t = TrackJobBase;
        using ptr_t   = _this_t::c_buffer_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).ptrCBeamElementsBuffer() );
    }

    TrackJobBase::c_buffer_t const*
    TrackJobBase::ptrCBeamElementsBuffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_beam_elem_buffer == nullptr ) ||
            ( this->m_ptr_beam_elem_buffer->getCApiPtr() ==
              this->m_ptr_c_beam_elem_buffer ) );

        return this->m_ptr_c_beam_elem_buffer;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobBase::hasOutputBuffer() const SIXTRL_NOEXCEPT
    {
        return ( this->ptrCOutputBuffer() != nullptr );
    }

    bool TrackJobBase::ownsOutputBuffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_my_output_buffer.get() == nullptr ) ||
            ( ( this->m_my_output_buffer.get() ==
                this->m_ptr_output_buffer ) &&
              ( this->m_my_output_buffer->getCApiPtr() ==
                this->m_ptr_c_output_buffer ) ) );

        return ( ( this->ptrOutputBuffer() != nullptr ) &&
                 ( this->m_my_output_buffer.get() != nullptr ) );
    }

    bool
    TrackJobBase::hasElemByElemOutput() const SIXTRL_NOEXCEPT
    {
        return this->m_has_elem_by_elem_output;
    }

    bool
    TrackJobBase::hasBeamMonitorOutput() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            (  !this->m_has_beam_monitor_output ) ||
            ( ( this->m_has_beam_monitor_output ) &&
              ( this->m_ptr_c_output_buffer != nullptr ) ) );

        return this->m_has_beam_monitor_output;
    }

    TrackJobBase::size_type
    TrackJobBase::beamMonitorsOutputBufferOffset() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( ( this->hasOutputBuffer() ) &&
              ( ::NS(Buffer_get_size)( this->ptrCOutputBuffer() ) >
                this->m_be_mon_output_buffer_offset ) ) ||
            ( this->m_be_mon_output_buffer_offset ==
                TrackJobBase::size_type{ 0 } ) );

        return this->m_be_mon_output_buffer_offset;
    }

    TrackJobBase::size_type
    TrackJobBase::elemByElemOutputBufferOffset() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( ( this->hasOutputBuffer() ) &&
              ( ::NS(Buffer_get_size)( this->ptrCOutputBuffer() ) >
                this->m_elem_by_elem_output_offset ) ) ||
            ( this->m_elem_by_elem_output_offset ==
                TrackJobBase::size_type{ 0 } ) );

        return this->m_elem_by_elem_output_offset;
    }

    TrackJobBase::particle_index_t
    TrackJobBase::untilTurnElemByElem() const SIXTRL_NOEXCEPT
    {
        return this->m_until_turn_elem_by_elem;
    }

    TrackJobBase::size_type
    TrackJobBase::numElemByElemTurns() const SIXTRL_NOEXCEPT
    {
        using index_t = TrackJobBase::particle_index_t;
        using size_t  = TrackJobBase::size_type;

        if( ( this->m_until_turn_elem_by_elem > this->m_min_initial_turn_id ) &&
            ( this->m_min_initial_turn_id >= index_t{ 0 } ) )
        {
            return static_cast< size_t >( this->m_until_turn_elem_by_elem -
                this->m_min_initial_turn_id );
        }

        return size_t{ 0 };
    }

    TrackJobBase::buffer_t*
    TrackJobBase::ptrOutputBuffer() SIXTRL_RESTRICT
    {
        using _this_t = TrackJobBase;
        using ptr_t   = _this_t::buffer_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).ptrOutputBuffer() );
    }

    TrackJobBase::buffer_t*
    TrackJobBase::ptrOutputBuffer() const SIXTRL_RESTRICT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_output_buffer == nullptr ) ||
            ( this->m_ptr_output_buffer->getCApiPtr() ==
              this->m_ptr_c_output_buffer ) );

        return this->m_ptr_output_buffer;
    }

    TrackJobBase::c_buffer_t*
    TrackJobBase::ptrCOutputBuffer() SIXTRL_RESTRICT
    {
        using _this_t = TrackJobBase;
        using ptr_t   = _this_t::c_buffer_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).ptrCOutputBuffer() );
    }

    TrackJobBase::c_buffer_t const*
    TrackJobBase::ptrCOutputBuffer() const SIXTRL_RESTRICT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_output_buffer == nullptr ) ||
            ( this->m_ptr_output_buffer->getCApiPtr() ==
              this->m_ptr_c_output_buffer ) );

        return this->m_ptr_c_output_buffer;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobBase::hasBeamMonitors() const SIXTRL_NOEXCEPT
    {
        return !this->m_beam_monitor_indices.empty();
    }

    TrackJobBase::size_type
    TrackJobBase::numBeamMonitors() const SIXTRL_NOEXCEPT
    {
        return this->m_beam_monitor_indices.size();
    }


    TrackJobBase::size_type const*
    TrackJobBase::beamMonitorIndicesBegin() const SIXTRL_NOEXCEPT
    {
        return this->m_beam_monitor_indices.data();
    }

    TrackJobBase::size_type const*
    TrackJobBase::beamMonitorIndicesEnd() const SIXTRL_NOEXCEPT
    {
        TrackJobBase::size_type const* end_ptr =
            this->beamMonitorIndicesBegin();

        if( end_ptr != nullptr )
        {
            std::advance( end_ptr, this->numBeamMonitors() );
        }

        return end_ptr;
    }

    TrackJobBase::size_type
    TrackJobBase::beamMonitorIndex( TrackJobBase::size_type const n ) const
    {
        return this->m_beam_monitor_indices.at( n );
    }

    /* --------------------------------------------------------------------- */

    bool
    TrackJobBase::hasElemByElemConfig() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_my_elem_by_elem_config.get() == nullptr ) ||
            ( this->m_ptr_c_output_buffer != nullptr ) );

        return ( ::NS(ElemByElemConfig_is_active)(
            this->m_my_elem_by_elem_config.get() ) );
    }

    TrackJobBase::elem_by_elem_config_t*
    TrackJobBase::ptrElemByElemConfig() SIXTRL_NOEXCEPT
    {
        using _this_t = TrackJobBase;
        using  ptr_t  = _this_t::elem_by_elem_config_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).ptrElemByElemConfig() );
    }

    TrackJobBase::elem_by_elem_order_t
    TrackJobBase::elemByElemOrder() const SIXTRL_NOEXCEPT
    {
        return ::NS(ElemByElemConfig_get_order)(
            this->m_my_elem_by_elem_config.get() );
    }

    TrackJobBase::elem_by_elem_order_t
    TrackJobBase::defaultElemByElemOrder() const SIXTRL_NOEXCEPT
    {
        return this->m_default_elem_by_elem_order;
    }

    void TrackJobBase::setDefaultElemByElemOrder(
        TrackJobBase::elem_by_elem_order_t const order ) SIXTRL_NOEXCEPT
    {
        this->m_default_elem_by_elem_order = order;
        return;
    }

    TrackJobBase::elem_by_elem_config_t const*
    TrackJobBase::ptrElemByElemConfig() const SIXTRL_NOEXCEPT
    {
        return this->m_my_elem_by_elem_config.get();
    }

    bool
    TrackJobBase::elemByElemRolling() const SIXTRL_NOEXCEPT
    {
        return ::NS(ElemByElemConfig_is_rolling)(
            this->ptrElemByElemConfig() );
    }

    bool
    TrackJobBase::defaultElemByElemRolling() const SIXTRL_NOEXCEPT
    {
        return this->m_default_elem_by_elem_rolling;
    }

    void TrackJobBase::setDefaultElemByElemRolling(
        bool is_rolling ) SIXTRL_NOEXCEPT
    {
        this->m_default_elem_by_elem_rolling = is_rolling;
        return;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBase::TrackJobBase(
        const char *const SIXTRL_RESTRICT type_str,
        track_job_type_t const type_id ) :
        m_type_str(),
        m_device_id_str(),
        m_config_str(),
        m_particle_set_indices(),
        m_beam_monitor_indices(),
        m_my_output_buffer( nullptr ),
        m_my_elem_by_elem_config( nullptr ),
        m_ptr_particles_buffer( nullptr ),
        m_ptr_beam_elem_buffer( nullptr ),
        m_ptr_output_buffer( nullptr ),
        m_ptr_c_particles_buffer( nullptr ),
        m_ptr_c_beam_elem_buffer( nullptr ),
        m_ptr_c_output_buffer( nullptr ),
        m_be_mon_output_buffer_offset( TrackJobBase::size_type{ 0 } ),
        m_elem_by_elem_output_offset( TrackJobBase::size_type{ 0 } ),
        m_type_id( type_id ),
        m_default_elem_by_elem_order( ::NS(ELEM_BY_ELEM_ORDER_DEFAULT) ),
        m_min_particle_id( TrackJobBase::particle_index_t{ 0 } ),
        m_max_particle_id( TrackJobBase::particle_index_t{ 0 } ),
        m_min_element_id( TrackJobBase::particle_index_t{ 0 } ),
        m_max_element_id( TrackJobBase::particle_index_t{ 0 } ),
        m_min_initial_turn_id( TrackJobBase::particle_index_t{ 0 } ),
        m_max_initial_turn_id( TrackJobBase::particle_index_t{ 0 } ),
        m_until_turn_elem_by_elem( TrackJobBase::size_type{ 0 } ),
        m_collect_flags(
            SIXTRL_CXX_NAMESPACE::TRACK_JOB_COLLECT_DEFAULT_FLAGS ),
        m_requires_collect( true ),
        m_default_elem_by_elem_rolling( true ),
        m_has_beam_monitor_output( false ),
        m_has_elem_by_elem_output( false )
    {
        if( type_str != nullptr )
        {
            this->m_type_str = type_str;
        }

        this->doInitDefaultParticleSetIndices();
        this->doInitDefaultBeamMonitorIndices();
    }

    TrackJobBase::TrackJobBase( TrackJobBase const& other ) :
        m_type_str( other.m_type_str ),
        m_device_id_str( other.m_type_str ),
        m_config_str( other.m_config_str ),
        m_particle_set_indices( other.m_particle_set_indices ),
        m_beam_monitor_indices( other.m_beam_monitor_indices ),
        m_my_output_buffer( nullptr  ),
        m_my_elem_by_elem_config( nullptr ),
        m_ptr_particles_buffer( other.m_ptr_particles_buffer  ),
        m_ptr_beam_elem_buffer( other.m_ptr_beam_elem_buffer ),
        m_ptr_output_buffer( nullptr ),
        m_ptr_c_particles_buffer( other.m_ptr_c_particles_buffer ),
        m_ptr_c_beam_elem_buffer( other.m_ptr_c_beam_elem_buffer ),
        m_ptr_c_output_buffer( nullptr ),
        m_be_mon_output_buffer_offset( other.m_be_mon_output_buffer_offset ),
        m_elem_by_elem_output_offset( other.m_elem_by_elem_output_offset ),
        m_type_id( other.m_type_id ),
        m_default_elem_by_elem_order( other.m_default_elem_by_elem_order ),
        m_min_particle_id( other.m_min_particle_id ),
        m_max_particle_id( other.m_max_particle_id ),
        m_min_element_id( other.m_min_element_id ),
        m_max_element_id( other.m_max_element_id ),
        m_min_initial_turn_id( other.m_min_initial_turn_id ),
        m_max_initial_turn_id( other.m_max_initial_turn_id ),
        m_until_turn_elem_by_elem( other.m_until_turn_elem_by_elem ),
        m_collect_flags( other.m_collect_flags ),
        m_requires_collect( other.m_requires_collect ),
        m_default_elem_by_elem_rolling( other.m_default_elem_by_elem_rolling ),
        m_has_beam_monitor_output( other.m_has_beam_monitor_output ),
        m_has_elem_by_elem_output( other.m_has_elem_by_elem_output )
    {
        using elem_by_elem_config_t = TrackJobBase::elem_by_elem_config_t;

        if( other.ownsOutputBuffer() )
        {

        }

        if( other.m_my_elem_by_elem_config.get() != nullptr )
        {
            this->m_my_elem_by_elem_config.reset(
                new elem_by_elem_config_t );

            *this->m_my_elem_by_elem_config =  *other.ptrElemByElemConfig();
        }
    }

    TrackJobBase::TrackJobBase(
        TrackJobBase&& o ) SIXTRL_NOEXCEPT :
        m_type_str( std::move( o.m_type_str ) ),
        m_device_id_str( std::move( o.m_type_str ) ),
        m_config_str( std::move( o.m_config_str ) ),
        m_particle_set_indices( std::move( o.m_particle_set_indices ) ),
        m_beam_monitor_indices( std::move( o.m_beam_monitor_indices ) ),
        m_my_output_buffer( std::move( o.m_my_output_buffer ) ),
        m_my_elem_by_elem_config( std::move( o.m_my_elem_by_elem_config ) ),
        m_ptr_particles_buffer( std::move( o.m_ptr_particles_buffer  ) ),
        m_ptr_beam_elem_buffer( std::move( o.m_ptr_beam_elem_buffer ) ),
        m_ptr_output_buffer( std::move( o.m_ptr_output_buffer ) ),
        m_ptr_c_particles_buffer( std::move( o.m_ptr_c_particles_buffer ) ),
        m_ptr_c_beam_elem_buffer( std::move( o.m_ptr_c_beam_elem_buffer ) ),
        m_ptr_c_output_buffer( std::move( o.m_ptr_c_output_buffer ) ),
        m_be_mon_output_buffer_offset( std::move(
            o.m_be_mon_output_buffer_offset ) ),
        m_elem_by_elem_output_offset( std::move(
            o.m_elem_by_elem_output_offset ) ),
        m_type_id( std::move( o.m_type_id ) ),
        m_default_elem_by_elem_order( std::move(
            o.m_default_elem_by_elem_order ) ),
        m_min_particle_id( std::move( o.m_min_particle_id ) ),
        m_max_particle_id( std::move( o.m_max_particle_id ) ),
        m_min_element_id( std::move( o.m_min_element_id ) ),
        m_max_element_id( std::move( o.m_max_element_id ) ),
        m_min_initial_turn_id( std::move( o.m_min_initial_turn_id ) ),
        m_max_initial_turn_id( std::move( o.m_max_initial_turn_id ) ),
        m_until_turn_elem_by_elem( std::move( o.m_until_turn_elem_by_elem ) ),
        m_collect_flags( std::move( o.m_collect_flags ) ),
        m_requires_collect( std::move( o.m_requires_collect ) ),
        m_default_elem_by_elem_rolling( std::move(
            o.m_default_elem_by_elem_rolling ) ),
        m_has_beam_monitor_output( std::move( o.m_has_beam_monitor_output ) ),
        m_has_elem_by_elem_output( std::move( o.m_has_elem_by_elem_output ) )
    {
        o.m_type_str.clear();
        o.m_device_id_str.clear();
        o.m_config_str.clear();

        o.doClearBaseImpl();
    }

    TrackJobBase& TrackJobBase::operator=(
        TrackJobBase const& rhs )
    {
        if( this != &rhs )
        {
            this->m_type_str                    = rhs.m_type_str;
            this->m_device_id_str               = rhs.m_type_str;
            this->m_config_str                  = rhs.m_config_str;
            this->m_particle_set_indices        = rhs.m_particle_set_indices;
            this->m_beam_monitor_indices        = rhs.m_beam_monitor_indices;
            this->m_ptr_particles_buffer        = rhs.m_ptr_particles_buffer;
            this->m_ptr_beam_elem_buffer        = rhs.m_ptr_beam_elem_buffer;
            this->m_ptr_c_particles_buffer      = rhs.m_ptr_c_particles_buffer;
            this->m_ptr_c_beam_elem_buffer      = rhs.m_ptr_c_beam_elem_buffer;

            this->m_be_mon_output_buffer_offset =
                rhs.m_be_mon_output_buffer_offset;

            this->m_type_id                    = rhs.m_type_id;

            this->m_elem_by_elem_output_offset =
                rhs.m_elem_by_elem_output_offset;

            this->m_default_elem_by_elem_order =
                rhs.m_default_elem_by_elem_order;

            this->m_min_particle_id            = rhs.m_min_particle_id;
            this->m_max_particle_id            = rhs.m_max_particle_id;
            this->m_min_element_id             = rhs.m_min_element_id;
            this->m_max_element_id             = rhs.m_max_element_id;
            this->m_min_initial_turn_id        = rhs.m_min_initial_turn_id;
            this->m_max_initial_turn_id        = rhs.m_max_initial_turn_id;
            this->m_until_turn_elem_by_elem    = rhs.m_until_turn_elem_by_elem;

            this->m_default_elem_by_elem_rolling =
                rhs.m_default_elem_by_elem_rolling;

            this->m_has_beam_monitor_output = rhs.m_has_beam_monitor_output;
            this->m_has_elem_by_elem_output = rhs.m_has_elem_by_elem_output;
            this->m_requires_collect        = rhs.m_requires_collect;
            this->m_collect_flags           = rhs.m_collect_flags;

            if( rhs.ownsOutputBuffer() )
            {
               this->m_ptr_output_buffer    = nullptr;
               this->m_ptr_c_output_buffer  = nullptr;
            }
            else
            {
                this->m_ptr_output_buffer   = rhs.m_ptr_output_buffer;
                this->m_ptr_c_output_buffer = rhs.m_ptr_c_output_buffer;
            }

            if( rhs.m_my_elem_by_elem_config.get() != nullptr )
            {
                this->m_my_elem_by_elem_config.reset(
                    new elem_by_elem_config_t );

                *this->m_my_elem_by_elem_config =  *rhs.ptrElemByElemConfig();
            }
            else
            {
                this->m_my_elem_by_elem_config.reset( nullptr );
            }
        }

        return *this;
    }

    TrackJobBase& TrackJobBase::operator=(
        TrackJobBase&& rhs ) SIXTRL_NOEXCEPT
    {
        if( this != &rhs )
        {
            this->m_type_str         = std::move( rhs.m_type_str );
            this->m_device_id_str    = std::move( rhs.m_type_str );
            this->m_config_str       = std::move( rhs.m_config_str );

            this->m_particle_set_indices = std::move( rhs.m_particle_set_indices );
            this->m_beam_monitor_indices = std::move( rhs.m_beam_monitor_indices );

            this->m_my_output_buffer = std::move( rhs.m_my_output_buffer );

            this->m_my_elem_by_elem_config =
                std::move( rhs.m_my_elem_by_elem_config );

            this->m_ptr_particles_buffer =
                std::move( rhs.m_ptr_particles_buffer );

            this->m_ptr_beam_elem_buffer =
                std::move( rhs.m_ptr_beam_elem_buffer );

            this->m_ptr_output_buffer = std::move( rhs.m_ptr_output_buffer );

            this->m_ptr_c_particles_buffer =
                std::move( rhs.m_ptr_c_particles_buffer );

            this->m_ptr_c_beam_elem_buffer =
                std::move( rhs.m_ptr_c_beam_elem_buffer );

            this->m_ptr_c_output_buffer =
                std::move( rhs.m_ptr_c_output_buffer );

            this->m_be_mon_output_buffer_offset =
                std::move( rhs.m_be_mon_output_buffer_offset );

            this->m_elem_by_elem_output_offset =
                std::move( rhs.m_elem_by_elem_output_offset );


            this->m_type_id = std::move( rhs.m_type_id );

            this->m_default_elem_by_elem_order =
                std::move( rhs.m_default_elem_by_elem_order );

            this->m_min_particle_id     = std::move( rhs.m_min_particle_id );
            this->m_max_particle_id     = std::move( rhs.m_max_particle_id );
            this->m_min_element_id      = std::move( rhs.m_min_element_id  );
            this->m_max_element_id      = std::move( rhs.m_max_element_id  );
            this->m_min_initial_turn_id = std::move( rhs.m_min_initial_turn_id);
            this->m_max_initial_turn_id = std::move( rhs.m_max_initial_turn_id);

            this->m_until_turn_elem_by_elem =
                std::move( rhs.m_until_turn_elem_by_elem );

            this->m_requires_collect = std::move( rhs.m_requires_collect );
            this->m_collect_flags = std::move( rhs.m_collect_flags );

            this->m_default_elem_by_elem_rolling =
                std::move( rhs.m_default_elem_by_elem_rolling );

            this->m_has_beam_monitor_output =
                std::move( rhs.m_has_beam_monitor_output );

            this->m_has_elem_by_elem_output =
                std::move( rhs.m_has_elem_by_elem_output );

            rhs.m_type_str.clear();
            rhs.m_device_id_str.clear();
            rhs.m_config_str.clear();

            rhs.m_type_id = type_t{ 0 };
            rhs.doClearBaseImpl();
        }

        return *this;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBase::doClear()
    {
        this->doClearBaseImpl();
        return;
    }

    void TrackJobBase::doCollect( collect_flag_t const )
    {
        return;
    }

    TrackJobBase::track_status_t
    TrackJobBase::doTrackUntilTurn( size_type const )
    {
        return TrackJobBase::track_status_t{ -1 };
    }

    TrackJobBase::track_status_t
    TrackJobBase::doTrackElemByElem( size_type const )
    {
        return TrackJobBase::track_status_t{ -1 };
    }

    TrackJobBase::track_status_t
    TrackJobBase::doTrackLine( size_type const, size_type const, bool const )
    {
        return TrackJobBase::track_status_t{ -1 };
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobBase::doPrepareParticlesStructures(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT pb )
    {
        bool success = false;

        using size_t    = TrackJobBase::size_type;
        using p_index_t = TrackJobBase::particle_index_t;

        SIXTRL_STATIC_VAR size_t const ZERO = size_t{ 0 };
        SIXTRL_STATIC_VAR size_t const ONE  = size_t{ 1 };

        size_t const nn = this->numParticleSets();
        size_t const num_psets = ::NS(Buffer_get_num_of_objects)( pb );

        if( ( pb != nullptr ) && ( ( nn > ZERO ) || ( nn == ZERO ) ) &&
            ( !::NS(Buffer_needs_remapping)( pb ) ) && ( num_psets >= nn ) )
        {
            int ret = int{ -1 };

            size_t const first_index = ( nn > ZERO )
                ? this->particleSetIndex( ZERO ) : ZERO;

            p_index_t min_part_id, max_part_id, min_elem_id, max_elem_id,
                      min_turn_id, max_turn_id;

            if( ( nn <= ONE ) && ( first_index == ZERO ) )
            {
                ret = ::NS(Particles_get_min_max_attributes)(
                        ::NS(Particles_buffer_get_const_particles)( pb, ZERO ),
                        &min_part_id, &max_part_id, &min_elem_id, &max_elem_id,
                        &min_turn_id, &max_turn_id );
            }
            else if( nn > ZERO )
            {
                ret =
                ::NS(Particles_buffer_get_min_max_attributes_of_particles_set)(
                    pb, nn, this->particleSetIndicesBegin(),
                    &min_part_id, &max_part_id, &min_elem_id, &max_elem_id,
                    &min_turn_id, &max_turn_id );
            }

            if( ret == int{ 0 } )
            {
                this->doSetMinParticleId( min_part_id );
                this->doSetMaxParticleId( max_part_id );

                this->doSetMinElementId( min_elem_id );
                this->doSetMaxElementId( max_elem_id );

                this->doSetMinInitialTurnId( min_turn_id );
                this->doSetMaxInitialTurnId( max_turn_id );

                success = true;
            }
        }

        return success;
    }

    bool TrackJobBase::doPrepareBeamElementsStructures(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT belems )
    {
        bool success = false;

        using size_t        = TrackJobBase::size_type;
        using p_index_t     = TrackJobBase::particle_index_t;
        using buf_size_t    = ::NS(buffer_size_t);
        using obj_ptr_t     = SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(Object)*;
        using ptr_t         = SIXTRL_BE_ARGPTR_DEC NS(BeamMonitor)*;

        SIXTRL_STATIC_VAR size_t const ZERO = size_t{ 0 };
        SIXTRL_STATIC_VAR uintptr_t const UZERO = uintptr_t{ 0 };

        if( ( belems != nullptr ) &&
            ( !::NS(Buffer_needs_remapping)( belems ) ) &&
            ( ::NS(Buffer_get_num_of_objects)( belems ) > ZERO ) &&
            ( ::NS(BeamElements_is_beam_elements_buffer)( belems ) ) )
        {
            int ret = -1;

            p_index_t const start_be_id = p_index_t{ 0 };
            buf_size_t  num_e_by_e_objs = buf_size_t{ 0 };
            p_index_t min_elem_id = this->minElementId();
            p_index_t max_elem_id = this->maxElementId();

            ret = ::NS(ElemByElemConfig_find_min_max_element_id_from_buffer)(
                belems, &min_elem_id, &max_elem_id, &num_e_by_e_objs,
                    start_be_id );

            if( ret == 0 )
            {
                buf_size_t num_be_monitors = buf_size_t{ 0 };
                std::vector< size_t > be_mon_indices( num_e_by_e_objs, ZERO );

                ret = ::NS(BeamMonitor_get_beam_monitor_indices_from_buffer)(
                    belems, be_mon_indices.size(), be_mon_indices.data(),
                        &num_be_monitors );

                SIXTRL_ASSERT( num_be_monitors <= be_mon_indices.size() );

                auto ind_end = be_mon_indices.begin();

                if( num_be_monitors > buf_size_t{ 0 } )
                {
                    std::advance( ind_end, num_be_monitors );
                }

                this->doSetBeamMonitorIndices( be_mon_indices.begin(), ind_end );
                SIXTRL_ASSERT( num_be_monitors == this->numBeamMonitors() );

                this->doSetMinElementId( min_elem_id );
                this->doSetMaxElementId( max_elem_id );
            }

            success = ( ret == 0 );

            if( ( success ) && ( this->numBeamMonitors() > ZERO ) &&
                ( this->ptrCParticlesBuffer() != nullptr ) &&
                ( this->minParticleId() <= this->maxParticleId() ) )
            {
                auto it  = this->beamMonitorIndicesBegin();
                auto end = this->beamMonitorIndicesEnd();

                p_index_t const min_part_id = this->minParticleId();
                p_index_t const max_part_id = this->maxParticleId();

                for( ; it != end ; ++it )
                {
                    obj_ptr_t obj = ::NS(Buffer_get_object)( belems, *it );
                    uintptr_t const addr = static_cast< uintptr_t >(
                        ::NS(Object_get_begin_addr)( obj ) );

                    if( ( obj != nullptr ) && ( addr != UZERO ) &&
                        ( ::NS(Object_get_type_id)( obj ) ==
                          ::NS(OBJECT_TYPE_BEAM_MONITOR) ) )
                    {
                        ptr_t m = reinterpret_cast< ptr_t >( addr );
                        ::NS(BeamMonitor_set_min_particle_id)( m, min_part_id );
                        ::NS(BeamMonitor_set_max_particle_id)( m, max_part_id );
                    }
                    else
                    {
                        success = false;
                        break;
                    }
                }
            }
        }

        return success;
    }

    bool TrackJobBase::doPrepareOutputStructures(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT beam_elements_buffer,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        TrackJobBase::size_type const until_turn_elem_by_elem )
    {
        bool success = false;

        using size_t                    = TrackJobBase::size_type;
        using buffer_t                  = TrackJobBase::buffer_t;
        using c_buffer_t                = TrackJobBase::c_buffer_t;
        using buf_size_t                = ::NS(buffer_size_t);
        using elem_by_elem_config_t     = TrackJobBase::elem_by_elem_config_t;
        using ptr_output_buffer_t       = TrackJobBase::ptr_output_buffer_t;
        using par_index_t               = TrackJobBase::particle_index_t;

        using ptr_elem_by_elem_config_t =
            TrackJobBase::ptr_elem_by_elem_config_t;

        SIXTRL_ASSERT( particles_buffer != nullptr );
        SIXTRL_ASSERT( !::NS(Buffer_needs_remapping)( particles_buffer ) );

        SIXTRL_ASSERT( ( ::NS(Buffer_get_num_of_objects)( particles_buffer ) ==
            size_t{ 0 } ) || ( ::NS(Buffer_is_particles_buffer)(
                particles_buffer ) ) );

        SIXTRL_ASSERT( beam_elements_buffer != nullptr );
        SIXTRL_ASSERT( !::NS(Buffer_needs_remapping)( beam_elements_buffer ) );

        SIXTRL_ASSERT( ::NS(Buffer_get_num_of_objects)( beam_elements_buffer )
            > size_t{ 0 } );

        SIXTRL_ASSERT( ::NS(BeamElements_is_beam_elements_buffer)(
            beam_elements_buffer ) );

        c_buffer_t* output_buffer = ptr_output_buffer;

        if( output_buffer == nullptr )
        {
            if( !this->hasOutputBuffer() )
            {
                SIXTRL_ASSERT( !this->ownsOutputBuffer() );
                ptr_output_buffer_t managed_output_buffer( new buffer_t );

                SIXTRL_ASSERT(  managed_output_buffer.get() != nullptr );
                output_buffer = managed_output_buffer.get()->getCApiPtr();
                SIXTRL_ASSERT( output_buffer != nullptr );

                this->doUpdateStoredOutputBuffer(
                    std::move( managed_output_buffer ) );

                SIXTRL_ASSERT( managed_output_buffer.get() == nullptr );
                SIXTRL_ASSERT( this->ownsOutputBuffer() );
                SIXTRL_ASSERT( this->ptrCOutputBuffer() == output_buffer );
            }
            else
            {
                output_buffer = this->ptrCOutputBuffer();
            }

            SIXTRL_ASSERT( this->hasOutputBuffer() );
        }
        else
        {
            if( !this->hasOutputBuffer() )
            {
                this->doSetPtrCOutputBuffer( output_buffer );
            }
            else if( !this->ownsOutputBuffer() )
            {
                this->doSetPtrCOutputBuffer( output_buffer );
            }
            else if( ( this->ownsOutputBuffer() ) &&
                     ( this->ptrCOutputBuffer() != nullptr ) &&
                     ( this->ptrCOutputBuffer() != output_buffer ) )
            {
                ptr_output_buffer_t dummy( nullptr );
                this->doUpdateStoredOutputBuffer( std::move( dummy ) );
                this->doSetPtrCOutputBuffer( output_buffer );
            }
            else
            {
                return success;
            }
        }

        if( output_buffer != nullptr )
        {
            SIXTRL_STATIC_VAR const size_t ZERO = size_t{ 0 };
            SIXTRL_ASSERT( !::NS(Buffer_needs_remapping)( output_buffer ) );

            SIXTRL_ASSERT(
                ( ::NS(Buffer_get_num_of_objects)( output_buffer ) == ZERO )||
                ( ::NS(Buffer_is_particles_buffer)( output_buffer ) ) );

            buf_size_t  elem_by_elem_out_idx_offset = buf_size_t{ 0 };
            buf_size_t  be_monitor_out_idx_offset   = buf_size_t{ 0 };
            par_index_t max_elem_by_elem_turn_id    = par_index_t{ 0 };

            int ret = ::NS(OutputBuffer_prepare_detailed)(
                beam_elements_buffer, output_buffer,
                this->minParticleId(), this->maxParticleId(),
                this->minElementId(),  this->maxElementId(),
                this->minInitialTurnId(), this->maxInitialTurnId(),
                until_turn_elem_by_elem,
                &elem_by_elem_out_idx_offset, &be_monitor_out_idx_offset,
                &max_elem_by_elem_turn_id );

            if( ( ret == 0 ) && ( until_turn_elem_by_elem > ZERO ) &&
                ( this->minInitialTurnId() >= par_index_t{ 0 } ) &&
                ( max_elem_by_elem_turn_id >= this->minInitialTurnId() ) &&
                ( until_turn_elem_by_elem > static_cast< buf_size_t >(
                    this->minInitialTurnId() ) ) )
            {
                ptr_elem_by_elem_config_t conf( new elem_by_elem_config_t );
                ::NS(ElemByElemConfig_preset)( conf.get() );

                ret = ::NS(ElemByElemConfig_init_detailed)(
                    conf.get(), this->defaultElemByElemOrder(),
                    this->minParticleId(), this->maxParticleId(),
                    this->minElementId(),  this->maxElementId(),
                    this->minInitialTurnId(), max_elem_by_elem_turn_id,
                    this->defaultElemByElemRolling() );

                if( ret == 0 )
                {
                    this->doUpdateStoredElemByElemConfig( std::move( conf ) );
                    this->doSetUntilTurnElemByElem(
                        until_turn_elem_by_elem );

                    SIXTRL_ASSERT( this->hasElemByElemConfig() );
                }
            }
            else if( ret == 0 )
            {
                ptr_elem_by_elem_config_t dummy( nullptr );
                this->doUpdateStoredElemByElemConfig( std::move( dummy ) );
                this->doSetUntilTurnElemByElem( ZERO );

                ret = ( !this->hasElemByElemConfig() ) ? 0 : -1;
            }

            if( ret == 0 )
            {
                this->doSetBeamMonitorOutputBufferOffset(
                    be_monitor_out_idx_offset );

                this->doSetElemByElemOutputIndexOffset(
                    elem_by_elem_out_idx_offset );
            }

            success = ( ret == 0 );
        }

        return success;
    }

    bool TrackJobBase::doAssignOutputBufferToBeamMonitors(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT beam_elem_buffer,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT output_buffer )
    {
        using size_t   = TrackJobBase::size_type;
        using config_t = TrackJobBase::elem_by_elem_config_t;

        size_t const num_be_monitors  = this->numBeamMonitors();
        size_t const be_mon_offset    = this->beamMonitorsOutputBufferOffset();
        size_t const elem_elem_offset = this->elemByElemOutputBufferOffset();
        config_t* elem_conf = this->ptrElemByElemConfig();

        size_t const num_out_objects  =
            ::NS(Buffer_get_num_of_objects)( output_buffer );

        bool success = false;

        if( ( output_buffer != nullptr ) && ( beam_elem_buffer != nullptr ) )
        {
            this->doSetBeamMonitorOutputEnabledFlag( false );
            this->doSetElemByElemOutputEnabledFlag( false );

            success = true;

            if( elem_conf != nullptr )
            {
                success = false;

                if( ( elem_elem_offset < num_out_objects ) &&
                    ( ( ( num_be_monitors == size_t{ 0 } ) &&
                        ( be_mon_offset >= elem_elem_offset ) ) ||
                      ( ( num_be_monitors > size_t{ 0 } ) &&
                        ( be_mon_offset >  elem_elem_offset ) ) ) &&
                    ( 0 == ::NS(ElemByElemConfig_assign_output_buffer)(
                        elem_conf, output_buffer, elem_elem_offset ) ) )
                {
                    this->doSetElemByElemOutputEnabledFlag( true );
                    success = true;
                }
            }

            if( ( success ) && ( num_be_monitors > size_t{ 0 } ) )
            {
                success = false;

                if( ( be_mon_offset < num_out_objects ) &&
                    ( ( ( elem_conf == nullptr ) &&
                        ( elem_elem_offset <= be_mon_offset ) ) ||
                      ( ( elem_conf != nullptr ) &&
                        ( elem_elem_offset < be_mon_offset ) ) ) &&
                    ( 0 == ::NS(BeamMonitor_assign_output_buffer_from_offset)(
                        beam_elem_buffer, output_buffer,
                        this->minInitialTurnId(), be_mon_offset ) ) )
                {
                    this->doSetBeamMonitorOutputEnabledFlag( true );
                    success = true;
                }
            }
        }

        return success;
    }

    bool TrackJobBase::doReset(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT beam_elem_buffer,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT output_buffer,
        TrackJobBase::size_type const until_turn_elem_by_elem )
    {
        bool success = false;

        if( ( this->doPrepareParticlesStructures( particles_buffer ) ) &&
            ( this->doPrepareBeamElementsStructures( beam_elem_buffer ) ) )
        {
            success = true;

            bool const requ_buffer =
            ::NS(OutputBuffer_required_for_tracking_of_particle_sets)(
                particles_buffer, this->numParticleSets(),
                    this->particleSetIndicesBegin(), beam_elem_buffer,
                        until_turn_elem_by_elem, nullptr );

            if( requ_buffer )
            {
                success = this->doPrepareOutputStructures( particles_buffer,
                    beam_elem_buffer, output_buffer, until_turn_elem_by_elem );
            }

            if( ( success ) && ( this->hasOutputBuffer() ) && ( requ_buffer ) )
            {
                success = this->doAssignOutputBufferToBeamMonitors(
                    beam_elem_buffer, this->ptrCOutputBuffer() );
            }

            if( ( success ) && ( output_buffer != nullptr ) &&
                ( !this->ownsOutputBuffer() ) )
            {
                this->doSetPtrCOutputBuffer( output_buffer );
            }
        }

        return success;
    }

    bool TrackJobBase::doAssignNewOutputBuffer(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer )
    {
        bool success = false;

        using _this_t = TrackJobBase;
        using flags_t = _this_t::output_buffer_flag_t;

        flags_t const flags =
            ::NS(OutputBuffer_required_for_tracking_of_particle_sets)(
            this->ptrCParticlesBuffer(), this->numParticleSets(),
                this->particleSetIndicesBegin(), this->ptrCBeamElementsBuffer(),
                    this->numElemByElemTurns(), nullptr );

        bool const requires_output_buffer =
            ::NS(OutputBuffer_requires_output_buffer)( flags );

        if( requires_output_buffer )
        {
            success = this->doPrepareOutputStructures(
                this->ptrCParticlesBuffer(), this->ptrCBeamElementsBuffer(),
                ptr_output_buffer, this->numElemByElemTurns() );
        }

        if( ( success ) &&
            ( ::NS(OutputBuffer_requires_beam_monitor_output)( flags ) ) &&
            ( this->hasOutputBuffer() ) && ( this->hasBeamMonitorOutput() ) )
        {
            success = this->doAssignOutputBufferToBeamMonitors(
                this->ptrCBeamElementsBuffer(), this->ptrCOutputBuffer() );
        }

        return success;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBase::doParseConfigStr(
        const char *const SIXTRL_RESTRICT config_str )
    {
        this->doParseConfigStrBaseImpl( config_str );
        return;
    }

    void TrackJobBase::doSetDeviceIdStr(
        const char *const SIXTRL_RESTRICT device_id_str )
    {
        if( device_id_str != nullptr )
        {
            this->m_device_id_str = device_id_str;
        }
        else
        {
            this->m_device_id_str.clear();
        }

        return;
    }

    void TrackJobBase::doSetConfigStr(
        const char *const SIXTRL_RESTRICT config_str )
    {
        if( config_str != nullptr )
        {
            this->m_config_str = config_str;
        }
        else
        {
            this->m_config_str.clear();
        }

        return;
    }

    void TrackJobBase::doSetPtrParticleBuffer(
        TrackJobBase::buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ptr_buffer != nullptr )
        {
            this->m_ptr_c_particles_buffer = ptr_buffer->getCApiPtr();
        }
        else if( ( this->m_ptr_particles_buffer != nullptr ) &&
                 ( this->m_ptr_c_particles_buffer ==
                   this->m_ptr_particles_buffer->getCApiPtr() ) )
        {
            this->m_ptr_c_particles_buffer = nullptr;
        }

        this->m_ptr_particles_buffer = ptr_buffer;
        return;
    }

    void TrackJobBase::doSetPtrCParticleBuffer(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ( this->m_ptr_particles_buffer   != nullptr ) &&
            ( this->m_ptr_c_particles_buffer ==
              this->m_ptr_particles_buffer->getCApiPtr() ) &&
            ( this->m_ptr_particles_buffer->getCApiPtr() != ptr_buffer ) )
        {
            this->m_ptr_particles_buffer = nullptr;
        }

        this->m_ptr_c_particles_buffer = ptr_buffer;
        return;
    }

    void TrackJobBase::doSetPtrBeamElementsBuffer(
        TrackJobBase::buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ptr_buffer != nullptr )
        {
            this->m_ptr_c_beam_elem_buffer = ptr_buffer->getCApiPtr();
        }
        else if( ( this->m_ptr_beam_elem_buffer != nullptr ) &&
                 ( this->m_ptr_c_beam_elem_buffer ==
                   this->m_ptr_beam_elem_buffer->getCApiPtr() ) )
        {
            this->m_ptr_c_beam_elem_buffer = nullptr;
        }

        this->m_ptr_beam_elem_buffer = ptr_buffer;
        return;
    }

    void TrackJobBase::doSetPtrCBeamElementsBuffer(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ( this->m_ptr_beam_elem_buffer != nullptr ) &&
            ( this->m_ptr_c_beam_elem_buffer ==
              this->m_ptr_beam_elem_buffer->getCApiPtr() ) &&
            ( this->m_ptr_beam_elem_buffer->getCApiPtr() != ptr_buffer ) )
        {
            this->m_ptr_beam_elem_buffer = nullptr;
        }

        this->m_ptr_c_beam_elem_buffer = ptr_buffer;
        return;
    }

    void TrackJobBase::doSetPtrOutputBuffer(
        TrackJobBase::buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ptr_buffer != nullptr )
        {
            this->m_ptr_c_output_buffer = ptr_buffer->getCApiPtr();
        }
        else if( ( this->m_ptr_output_buffer != nullptr ) &&
                 ( this->m_ptr_c_output_buffer ==
                   this->m_ptr_output_buffer->getCApiPtr() ) )
        {
            this->m_ptr_c_output_buffer = nullptr;
        }

        this->m_ptr_output_buffer = ptr_buffer;
        return;
    }

    void TrackJobBase::doSetPtrCOutputBuffer(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ( this->m_ptr_output_buffer != nullptr ) &&
            ( this->m_ptr_c_output_buffer ==
              this->m_ptr_output_buffer->getCApiPtr() ) &&
            ( this->m_ptr_output_buffer->getCApiPtr() != ptr_buffer ) )
        {
            this->m_ptr_output_buffer = nullptr;
        }

        this->m_ptr_c_output_buffer = ptr_buffer;
        return;
    }

    void TrackJobBase::doSetBeamMonitorOutputBufferOffset(
        TrackJobBase::size_type const output_buffer_offset ) SIXTRL_NOEXCEPT
    {
        this->m_be_mon_output_buffer_offset = output_buffer_offset;
        return;
    }

    void TrackJobBase::doSetUntilTurnElemByElem(
        TrackJobBase::particle_index_t const
            until_turn_elem_by_elem ) SIXTRL_NOEXCEPT
    {
        this->m_until_turn_elem_by_elem = until_turn_elem_by_elem;
        return;
    }

    void TrackJobBase::doSetElemByElemOutputIndexOffset(
        TrackJobBase::size_type const elem_by_elem_output_offset ) SIXTRL_NOEXCEPT
    {
        this->m_elem_by_elem_output_offset = elem_by_elem_output_offset;
        return;
    }

    void TrackJobBase::doSetRequiresCollectFlag(
        bool const requires_collect_flag ) SIXTRL_NOEXCEPT
    {
        this->m_requires_collect = requires_collect_flag;
        return;
    }

    void TrackJobBase::doSetBeamMonitorOutputEnabledFlag(
        bool const has_beam_monitor_output ) SIXTRL_NOEXCEPT
    {
        this->m_has_beam_monitor_output = has_beam_monitor_output;
        return;
    }

    void TrackJobBase::doSetElemByElemOutputEnabledFlag(
        bool const elem_by_elem_flag ) SIXTRL_NOEXCEPT
    {
        this->m_has_elem_by_elem_output = elem_by_elem_flag;
        return;
    }

    void TrackJobBase::doInitDefaultParticleSetIndices()
    {
        this->m_particle_set_indices.clear();
        this->m_particle_set_indices.push_back( TrackJobBase::size_type{ 0 } );

        return;
    }

    void TrackJobBase::doInitDefaultBeamMonitorIndices()
    {
        this->m_beam_monitor_indices.clear();
        return;
    }

    void TrackJobBase::doSetMinParticleId(
        TrackJobBase::particle_index_t const min_particle_id ) SIXTRL_NOEXCEPT
    {
        this->m_min_particle_id = min_particle_id;
    }

    void TrackJobBase::doSetMaxParticleId(
        TrackJobBase::particle_index_t const max_particle_id ) SIXTRL_NOEXCEPT
    {
        this->m_max_particle_id = max_particle_id;
    }

    void TrackJobBase::doSetMinElementId(
        TrackJobBase::particle_index_t const min_element_id ) SIXTRL_NOEXCEPT
    {
        this->m_min_element_id = min_element_id;
        return;
    }

    void TrackJobBase::doSetMaxElementId(
        TrackJobBase::particle_index_t const max_element_id ) SIXTRL_NOEXCEPT
    {
        this->m_max_element_id = max_element_id;
        return;
    }

    void TrackJobBase::doSetMinInitialTurnId(
        TrackJobBase::particle_index_t const min_turn_id ) SIXTRL_NOEXCEPT
    {
        this->m_min_initial_turn_id = min_turn_id;
        return;
    }

    void TrackJobBase::doSetMaxInitialTurnId(
        TrackJobBase::particle_index_t const max_turn_id ) SIXTRL_NOEXCEPT
    {
        this->m_max_initial_turn_id = max_turn_id;
        return;
    }

    void TrackJobBase::doUpdateStoredOutputBuffer(
        TrackJobBase::ptr_output_buffer_t&& ptr_output_buffer ) SIXTRL_NOEXCEPT
    {
        this->doSetPtrOutputBuffer( ptr_output_buffer.get() );
        this->m_my_output_buffer = std::move( ptr_output_buffer );
        return;
    }

    void TrackJobBase::doUpdateStoredElemByElemConfig(
        TrackJobBase::ptr_elem_by_elem_config_t&& ptr_config ) SIXTRL_NOEXCEPT
    {
        this->m_my_elem_by_elem_config = std::move( ptr_config );
        return;
    }

    void TrackJobBase::doClearBaseImpl() SIXTRL_NOEXCEPT
    {
        this->doInitDefaultParticleSetIndices();
        this->doInitDefaultBeamMonitorIndices();

        this->m_my_output_buffer.reset( nullptr );
        this->m_my_elem_by_elem_config.reset( nullptr );

        this->m_ptr_particles_buffer         = nullptr;
        this->m_ptr_beam_elem_buffer         = nullptr;
        this->m_ptr_output_buffer            = nullptr;

        this->m_ptr_c_particles_buffer       = nullptr;
        this->m_ptr_c_beam_elem_buffer       = nullptr;
        this->m_ptr_c_output_buffer          = nullptr;

        this->m_be_mon_output_buffer_offset  = TrackJobBase::size_type{ 0 };
        this->m_elem_by_elem_output_offset   = TrackJobBase::size_type{ 0 };
        this->m_default_elem_by_elem_order   = ::NS(ELEM_BY_ELEM_ORDER_DEFAULT);

        ::NS(Particles_init_min_max_attributes_for_find)(
            &this->m_min_particle_id, &this->m_max_particle_id,
            &this->m_min_element_id,  &this->m_max_element_id,
            &this->m_min_initial_turn_id,
            &this->m_max_initial_turn_id );

        this->m_until_turn_elem_by_elem      = TrackJobBase::size_type{ 0 };

        this->m_default_elem_by_elem_rolling = true;
        this->m_has_beam_monitor_output      = false;
        this->m_has_elem_by_elem_output      = false;

        return;
    }

    void TrackJobBase::doParseConfigStrBaseImpl(
        const char *const SIXTRL_RESTRICT config_str )
    {
        ( void )config_str;
        return;
    }
}

#endif /* defined( __cplusplus ) */

/* end: sixtracklib/common/internal/track_job_base.cpp */
