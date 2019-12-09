#include "sixtracklib/common/internal/track_job_base.h"

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <cstddef>
        #include <cstdint>
        #include <cstdlib>
        #include <iostream>
        #include <memory>
        #include <numeric>
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
    #include "sixtracklib/common/buffer/assign_address_item.h"
    #include "sixtracklib/common/buffer/assign_address_item_kernel_impl.h"
    #include "sixtracklib/common/buffer/buffer_toc.hpp"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/beam_elements.h"
    #include "sixtracklib/common/be_monitor/be_monitor.h"
    #include "sixtracklib/common/be_monitor/output_buffer.h"
    #include "sixtracklib/common/output/elem_by_elem_config.h"
    #include "sixtracklib/common/output/output_buffer.h"
    #include "sixtracklib/common/particles/particles_addr.h"
    #include "sixtracklib/common/internal/stl_buffer_helper.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace st = SIXTRL_CXX_NAMESPACE;
namespace SIXTRL_CXX_NAMESPACE
{
    using _store_t  = SIXTRL_CXX_NAMESPACE::TrackJobBufferStoreBase;

    _store_t::size_type constexpr _store_t::DEFAULT_BUFFER_CAPACITY;
    _store_t::flags_t   constexpr _store_t::DEFAULT_DATASTORE_FLAGS;

    TrackJobBufferStoreBase::TrackJobBufferStoreBase(
        _store_t::size_type const buffer_capacity,
        _store_t::flags_t const buffer_flags ) :
        m_ptr_cxx_buffer( nullptr ), m_ptr_c99_buffer( nullptr ),
        m_own_buffer( nullptr )
    {
        this->reset( buffer_capacity, buffer_flags );
    }

    TrackJobBufferStoreBase::TrackJobBufferStoreBase(
        _store_t::buffer_t* SIXTRL_RESTRICT cxx_buffer,
        bool const take_ownership ) :
        m_ptr_cxx_buffer( nullptr ), m_ptr_c99_buffer( nullptr ),
        m_own_buffer( nullptr )
    {
        this->reset( cxx_buffer, take_ownership );
    }

    TrackJobBufferStoreBase::TrackJobBufferStoreBase(
        _store_t::c_buffer_t* SIXTRL_RESTRICT c99_buffer,
        bool const take_ownership, bool const delete_ptr_after_move ) :
        m_ptr_cxx_buffer( nullptr ), m_ptr_c99_buffer( nullptr ),
        m_own_buffer( nullptr )
    {
        this->reset( c99_buffer, take_ownership, delete_ptr_after_move );
    }

    TrackJobBufferStoreBase::TrackJobBufferStoreBase(
        std::unique_ptr< _store_t::buffer_t >&& stored_ptr_buffer ) :
        m_ptr_cxx_buffer( nullptr ), m_ptr_c99_buffer( nullptr ),
        m_own_buffer( nullptr )
    {
        this->reset( std::move( stored_ptr_buffer ) );
    }

    TrackJobBufferStoreBase::TrackJobBufferStoreBase(
        _store_t::buffer_t&& cxx_buffer ) :
        m_ptr_cxx_buffer( nullptr ), m_ptr_c99_buffer( nullptr ),
        m_own_buffer( nullptr )
    {
        this->reset( std::move( cxx_buffer ) );
    }

    TrackJobBufferStoreBase::TrackJobBufferStoreBase(
        TrackJobBufferStoreBase const& other ) :
        m_ptr_cxx_buffer( nullptr ), m_ptr_c99_buffer( nullptr ),
        m_own_buffer( nullptr )
    {
        if( other.owns_buffer() )
        {
            SIXTRL_ASSERT( other.m_own_buffer.get() != nullptr );
            this->m_own_buffer.reset(
                new st::Buffer( *other.m_own_buffer.get() ) );

            this->m_ptr_cxx_buffer = this->m_own_buffer.get();
            this->m_ptr_c99_buffer = this->m_own_buffer->getCApiPtr();
        }
        else
        {
            this->m_ptr_cxx_buffer = other.m_ptr_cxx_buffer;
            this->m_ptr_c99_buffer = other.m_ptr_c99_buffer;
        }
    }

    TrackJobBufferStoreBase::TrackJobBufferStoreBase(
        TrackJobBufferStoreBase&& other ) SIXTRL_NOEXCEPT:
        m_ptr_cxx_buffer( std::move( other.m_ptr_cxx_buffer ) ),
        m_ptr_c99_buffer( std::move( other.m_ptr_c99_buffer ) ),
        m_own_buffer( std::move( other.m_own_buffer ) )
    {
        if( other.owns_buffer() )
        {
            SIXTRL_ASSERT( other.m_own_buffer.get() != nullptr );
            this->m_own_buffer.reset(
                new st::Buffer( *other.m_own_buffer.get() ) );

            this->m_ptr_cxx_buffer = this->m_own_buffer.get();
            this->m_ptr_c99_buffer = this->m_own_buffer->getCApiPtr();
        }
        else
        {
            this->m_ptr_cxx_buffer = other.m_ptr_cxx_buffer;
            this->m_ptr_c99_buffer = other.m_ptr_c99_buffer;
        }
    }

    TrackJobBufferStoreBase& TrackJobBufferStoreBase::operator=(
        TrackJobBufferStoreBase const& rhs )
    {
        if( this != &rhs )
        {
            if( rhs.owns_buffer() )
            {
                SIXTRL_ASSERT( rhs.m_own_buffer.get() != nullptr );

                this->m_own_buffer.reset(
                    new st::Buffer( *rhs.m_own_buffer.get() ) );

                this->m_ptr_cxx_buffer = this->m_own_buffer.get();
                this->m_ptr_c99_buffer = this->m_own_buffer->getCApiPtr();
            }
            else
            {
                this->m_ptr_cxx_buffer = rhs.m_ptr_cxx_buffer;
                this->m_ptr_c99_buffer = rhs.m_ptr_c99_buffer;
            }
        }

        return *this;
    }

    TrackJobBufferStoreBase&
    TrackJobBufferStoreBase::operator=( TrackJobBufferStoreBase&& rhs ) SIXTRL_NOEXCEPT
    {
        if( this != &rhs )
        {
            this->m_own_buffer = std::move( rhs.m_own_buffer );
            this->m_ptr_cxx_buffer = std::move( rhs.m_ptr_cxx_buffer );
            this->m_ptr_c99_buffer = std::move( rhs.m_ptr_c99_buffer );
        }

        return *this;
    }

    bool TrackJobBufferStoreBase::active() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( ( this->m_ptr_c99_buffer == nullptr ) &&
                ( this->m_ptr_cxx_buffer == nullptr ) &&
                ( this->m_own_buffer.get() == nullptr ) ) ||
            ( ( this->m_ptr_c99_buffer != nullptr ) &&
                ( ( this->m_ptr_cxx_buffer == nullptr ) ||
                ( this->m_ptr_cxx_buffer->getCApiPtr() ==
                    this->m_ptr_c99_buffer ) ) &&
                ( ( this->m_own_buffer == nullptr ) ||
                ( this->m_own_buffer.get() ==
                    this->m_ptr_cxx_buffer ) ) ) );

        return ( this->m_ptr_c99_buffer != nullptr );
    }

    bool TrackJobBufferStoreBase::owns_buffer() const SIXTRL_NOEXCEPT
    {
        return ( ( this->active() ) &&
                 ( this->m_own_buffer.get() != nullptr ) );
    }

    _store_t::c_buffer_t const*
    TrackJobBufferStoreBase::ptr_buffer() const SIXTRL_NOEXCEPT
    {
        return this->m_ptr_c99_buffer;
    }

    _store_t::c_buffer_t* TrackJobBufferStoreBase::ptr_buffer() SIXTRL_NOEXCEPT
    {
        return this->m_ptr_c99_buffer;
    }

    _store_t::buffer_t const*
    TrackJobBufferStoreBase::ptr_cxx_buffer() const SIXTRL_NOEXCEPT
    {
        return this->m_ptr_cxx_buffer;
    }

    _store_t::buffer_t* TrackJobBufferStoreBase::ptr_cxx_buffer() SIXTRL_NOEXCEPT
    {
        return this->m_ptr_cxx_buffer;
    }

    void TrackJobBufferStoreBase::clear() SIXTRL_NOEXCEPT
    {
        this->m_ptr_cxx_buffer = nullptr;
        this->m_ptr_c99_buffer = nullptr;
        this->m_own_buffer.reset( nullptr );
    }

    void TrackJobBufferStoreBase::reset(
        _store_t::size_type const buffer_capacity,
        _store_t::flags_t const buffer_flags )
    {
        this->m_own_buffer.reset(
            new _store_t::buffer_t( buffer_capacity, buffer_flags ) );

        if( this->m_own_buffer.get() != nullptr )
        {
            this->m_ptr_cxx_buffer = this->m_own_buffer.get();
            this->m_ptr_c99_buffer = this->m_own_buffer->getCApiPtr();

            if( this->m_ptr_c99_buffer != nullptr )
            {
                this->m_buffer_toc.reset( this->m_ptr_c99_buffer );
            }
        }
        else
        {
            this->m_ptr_cxx_buffer = nullptr;
            this->m_ptr_c99_buffer = nullptr;
        }
    }

    void TrackJobBufferStoreBase::reset(
        _store_t::buffer_t* SIXTRL_RESTRICT cxx_buffer,
        bool const take_ownership )
    {
        if( ( cxx_buffer != nullptr ) &&
            ( this->m_ptr_cxx_buffer != cxx_buffer ) )
        {
            this->m_ptr_cxx_buffer = cxx_buffer;
            this->m_ptr_c99_buffer = cxx_buffer->getCApiPtr();

            if( take_ownership )
            {
                this->m_own_buffer.reset( cxx_buffer );
            }
            else if( this->m_own_buffer.get() != nullptr )
            {
                this->m_own_buffer.reset( nullptr );
            }

            if( this->m_ptr_c99_buffer != nullptr )
            {
                this->m_buffer_toc.reset( this->m_ptr_c99_buffer );
            }
        }
    }

    void TrackJobBufferStoreBase::reset(
        _store_t::c_buffer_t* SIXTRL_RESTRICT c99_buffer,
        bool const take_ownership, bool const delete_ptr_after_move )
    {
        using buffer_t = _store_t::buffer_t;

        if( ( c99_buffer != nullptr ) &&
            ( this->m_ptr_c99_buffer != c99_buffer ) )
        {
            if( take_ownership )
            {
                this->m_own_buffer =
                buffer_t::MAKE_FROM_CBUFFER_AND_TAKE_OWNERSHIP(
                    c99_buffer, delete_ptr_after_move );

                this->m_ptr_cxx_buffer = this->m_own_buffer.get();

                if( this->m_own_buffer.get() != nullptr )
                {
                    this->m_ptr_c99_buffer = this->m_own_buffer->getCApiPtr();
                }

                if( this->m_ptr_c99_buffer != nullptr )
                {
                    this->m_buffer_toc.reset( this->m_ptr_c99_buffer );
                }
            }
            else
            {
                this->m_ptr_c99_buffer = c99_buffer;
                this->m_ptr_cxx_buffer = nullptr;
                this->m_own_buffer.reset( nullptr );
            }
        }
    }

    void TrackJobBufferStoreBase::reset( std::unique_ptr<
        _store_t::buffer_t >&& stored_ptr_buffer )
    {
        this->m_own_buffer = std::move( stored_ptr_buffer );
        this->m_ptr_cxx_buffer = this->m_own_buffer.get();

        this->m_ptr_c99_buffer = ( this->m_own_buffer.get() != nullptr )
            ? this->m_own_buffer->getCApiPtr() : nullptr;

        if( this->m_ptr_c99_buffer != nullptr )
        {
            this->m_buffer_toc.reset( this->m_ptr_c99_buffer );
        }
    }

    void TrackJobBufferStoreBase::reset( _store_t::buffer_t&& cxx_buffer )
    {
        if( &cxx_buffer != this->m_ptr_cxx_buffer )
        {
            this->m_own_buffer.reset(
                new _store_t::buffer_t( std::move( cxx_buffer ) ) );

            this->m_ptr_cxx_buffer = this->m_own_buffer.get();
            SIXTRL_ASSERT( this->m_own_buffer.get() != nullptr );
            this->m_ptr_c99_buffer = this->m_own_buffer->getCApiPtr();

            if( this->m_ptr_c99_buffer != nullptr )
            {
                this->m_buffer_toc.reset( this->m_ptr_c99_buffer );
            }
        }
    }

    _store_t::buffer_toc_t const&
    TrackJobBufferStoreBase::table_of_contents() const SIXTRL_NOEXCEPT
    {
        return this->m_buffer_toc;
    }

    _store_t::buffer_toc_t const*
    TrackJobBufferStoreBase::ptr_table_of_contents() const SIXTRL_NOEXCEPT
    {
        return &this->m_buffer_toc;
    }

    /* ********************************************************************* */

    using _this_t      = st::TrackJobBase;
    using _size_t      = _this_t::size_type;
    using _status_t    = _this_t::status_t;
    using _pindex_t    = _pindex_t;
    using _elem_conf_t = _this_t::elem_by_elem_config_t;

    constexpr _this_t::size_type        _this_t::ILLEGAL_BUFFER_ID;
    constexpr _this_t::config_id_t      _this_t::ILLEGAL_CONFIG_ID;
    constexpr _this_t::size_type        _this_t::ILLEGAL_OUTPUT_BUFFER_OFFSET;
    constexpr _this_t::particle_index_t _this_t::ILLEGAL_UNTIL_TURN;

    void TrackJobBase::COPY_PTR_BUFFER(
        _this_t::ptr_buffer_t& SIXTRL_RESTRICT_REF dest_ptr_buffer,
        _this_t::ptr_buffer_t const& SIXTRL_RESTRICT_REF src_ptr_buffer )
    {
        if( src_ptr_buffer.get() != nullptr )
        {
            dest_ptr_buffer.reset(
                new _this_t::buffer_t( *src_ptr_buffer.get() ) );
        }
        else
        {
            dest_ptr_buffer.reset( nullptr );
        }
    }

    /* --------------------------------------------------------------------- */

    _size_t TrackJobBase::DefaultNumParticleSetIndices() SIXTRL_NOEXCEPT
    {
        return st::TRACK_JOB_DEFAULT_NUM_PARTICLE_SETS;
    }

    _size_t const*
    TrackJobBase::DefaultParticleSetIndicesBegin() SIXTRL_NOEXCEPT
    {
        _size_t const* ptr = &st::TRACK_JOB_DEFAULT_PARTICLE_SET_INDICES[ 0 ];
        return ptr;
    }

    _size_t const* TrackJobBase::DefaultParticleSetIndicesEnd() SIXTRL_NOEXCEPT
    {
        _size_t const* end_ptr = TrackJobBase::DefaultParticleSetIndicesBegin();
        std::advance( end_ptr, st::TRACK_JOB_DEFAULT_NUM_PARTICLE_SETS );
        return end_ptr;
    }

    void TrackJobBase::clear()
    {
        this->doClear();
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBase::collect()
    {
        this->doCollect( this->m_collect_flags );
    }

    void TrackJobBase::collect( _this_t::collect_flag_t const flags )
    {
        this->doCollect( flags & st::TRACK_JOB_COLLECT_ALL );
    }

    void TrackJobBase::collect_particles()
    {
        this->doCollect( st::TRACK_JOB_IO_PARTICLES );
    }


    void TrackJobBase::collect_beam_elements()
    {
        this->doCollect( st::TRACK_JOB_IO_BEAM_ELEMENTS );
    }

    void TrackJobBase::collect_output()
    {
        this->doCollect( st::TRACK_JOB_IO_OUTPUT );
    }

    void TrackJobBase::enable_collect_particles()  SIXTRL_NOEXCEPT
    {
        this->m_collect_flags |= st::TRACK_JOB_IO_PARTICLES;
    }

    void TrackJobBase::disable_collect_patricles() SIXTRL_NOEXCEPT
    {
        this->m_collect_flags = TrackJobBase::UnsetCollectFlag(
            this->m_collect_flags, st::TRACK_JOB_IO_PARTICLES );
    }

    bool TrackJobBase::is_collecting_particles() const SIXTRL_NOEXCEPT
    {
        return TrackJobBase::IsCollectFlagSet( this->m_collect_flags,
            st::TRACK_JOB_IO_PARTICLES );
    }

    void TrackJobBase::enable_collect_beam_elements()  SIXTRL_NOEXCEPT
    {
        this->m_collect_flags |= st::TRACK_JOB_IO_BEAM_ELEMENTS;
    }

    void TrackJobBase::disable_collect_beam_elements() SIXTRL_NOEXCEPT
    {
        this->m_collect_flags = TrackJobBase::UnsetCollectFlag(
            this->m_collect_flags, st::TRACK_JOB_IO_BEAM_ELEMENTS );
    }

    bool TrackJobBase::is_collecting_beam_elements() const SIXTRL_NOEXCEPT
    {
        return TrackJobBase::IsCollectFlagSet( this->m_collect_flags,
                st::TRACK_JOB_IO_BEAM_ELEMENTS );
    }

    void TrackJobBase::enable_collect_output()  SIXTRL_NOEXCEPT
    {
        this->m_collect_flags |= st::TRACK_JOB_IO_OUTPUT;
    }

    void TrackJobBase::disable_collect_output() SIXTRL_NOEXCEPT
    {
        this->m_collect_flags = TrackJobBase::UnsetCollectFlag(
            this->m_collect_flags, st::TRACK_JOB_IO_OUTPUT );
    }

    bool TrackJobBase::is_collecting_output() const SIXTRL_NOEXCEPT
    {
        return TrackJobBase::IsCollectFlagSet( this->m_collect_flags,
                st::TRACK_JOB_IO_OUTPUT );
    }

    _this_t::collect_flag_t TrackJobBase::collect_flags() const SIXTRL_NOEXCEPT
    {
        return this->m_collect_flags;
    }

    void TrackJobBase::set_collect_flags(
        _this_t::collect_flag_t const flags ) SIXTRL_NOEXCEPT
    {
        this->m_collect_flags = ( flags & st::TRACK_JOB_COLLECT_ALL );
    }

    bool TrackJobBase::requires_collecting() const SIXTRL_NOEXCEPT
    {
        return this->m_requires_collect;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBase::push( _this_t::push_flag_t const flags )
    {
        this->doPush( flags );
    }

    void TrackJobBase::push_particles()
    {
        this->doPush( st::TRACK_JOB_IO_PARTICLES );
    }

    void TrackJobBase::push_beam_elements()
    {
        this->doPush( st::TRACK_JOB_IO_BEAM_ELEMENTS );
    }

    void TrackJobBase::push_output()
    {
        this->doPush( st::TRACK_JOB_IO_OUTPUT );
    }

    /* --------------------------------------------------------------------- */

    _this_t::track_status_t TrackJobBase::track_until( _size_t const until_turn )
    {
        return this->doTrackUntilTurn( until_turn );
    }

    _this_t::track_status_t TrackJobBase::track_elem_by_elem(
        _size_t const until_turn )
    {
        return this->doTrackElemByElem( until_turn );
    }

    _this_t::track_status_t TrackJobBase::track_line(
        _size_t const beam_elements_begin_index,
        _size_t const beam_elements_end_index, bool const finish_turn )
    {
        return this->doTrackLine(
            beam_elements_begin_index, beam_elements_end_index, finish_turn );
    }

    bool TrackJobBase::reset(
        _this_t::buffer_t& SIXTRL_RESTRICT_REF particles_buffer,
        _this_t::buffer_t& SIXTRL_RESTRICT_REF be_buffer,
        _this_t::buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        _size_t const until_turn_elem_by_elem )
    {
        using c_buffer_t = _this_t::c_buffer_t;
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

            if( ( ptr_out != nullptr ) && ( this->has_output_buffer() ) )
            {
                this->doSetPtrOutputBuffer( ptr_output_buffer );
            }
        }

        return success;
    }

    bool TrackJobBase::reset(
        _this_t::buffer_t& SIXTRL_RESTRICT_REF particles_buffer,
        _size_t const particle_set_index,
        _this_t::buffer_t& SIXTRL_RESTRICT_REF be_buffer,
        _this_t::buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        _size_t const until_turn_elem_by_elem )
    {
        using size_t = _size_t;

        size_t particle_set_indices[] = { size_t{ 0 } };
        particle_set_indices[ 0 ] = particle_set_index;

        return TrackJobBase::reset( particles_buffer,
            &particle_set_indices[ 0 ], &particle_set_indices[ 1 ], be_buffer,
                ptr_output_buffer, until_turn_elem_by_elem );
    }

    bool TrackJobBase::reset(
        _this_t::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        _this_t::c_buffer_t* SIXTRL_RESTRICT be_buffer,
        _this_t::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        _size_t const until_turn_elem_by_elem )
    {
        this->doClear();

        bool const success = this->doReset( particles_buffer, be_buffer,
                ptr_output_buffer, until_turn_elem_by_elem );

        if( success )
        {
            this->doSetPtrCParticleBuffer( particles_buffer );
            this->doSetPtrCBeamElementsBuffer( be_buffer );

            if( ( ptr_output_buffer != nullptr ) && ( this->has_output_buffer() ) )
            {
                this->doSetPtrCOutputBuffer( ptr_output_buffer );
            }
        }

        return success;
    }

    bool TrackJobBase::reset(
        _this_t::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        _size_t const particle_set_index,
        _this_t::c_buffer_t* SIXTRL_RESTRICT be_buffer,
        _this_t::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        _size_t const until_turn_elem_by_elem )
    {
        return TrackJobBase::reset( particles_buffer,
            _size_t{ 1 }, &particle_set_index, be_buffer,
                ptr_output_buffer, until_turn_elem_by_elem );
    }

    bool TrackJobBase::reset(
        _this_t::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        _size_t const num_particle_sets,
        _size_t const* SIXTRL_RESTRICT
            particle_set_indices_begin,
        _this_t::c_buffer_t* SIXTRL_RESTRICT be_buffer,
        _this_t::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        _size_t const until_turn_elem_by_elem )
    {
        _size_t const* particle_set_indices_end =
            particle_set_indices_begin;

        if( ( particle_set_indices_end != nullptr ) &&
            ( num_particle_sets > _size_t{ 0 } ) )
        {
            std::advance( particle_set_indices_end, num_particle_sets );
        }

        return this->reset( particles_buffer,
            particle_set_indices_begin, particle_set_indices_end,
            be_buffer, ptr_output_buffer, until_turn_elem_by_elem );
    }

    bool TrackJobBase::select_particle_set( _size_t const particle_set_index )
    {
        using buffer_t   = _this_t::buffer_t;
        using c_buffer_t = _this_t::c_buffer_t;
        using size_t = _size_t;

        bool success = false;

        buffer_t*   ptr_particles_buffer   = this->ptr_output_cxx_buffer();
        buffer_t*   ptr_beam_elem_buffer   = this->ptr_beam_elements_cxx_buffer();

        c_buffer_t* ptr_c_particles_buffer = this->particles_buffer();
        c_buffer_t* ptr_c_beam_elem_buffer = this->beam_elements_buffer();

        if( ( ptr_c_particles_buffer != nullptr ) &&
            ( !::NS(Buffer_needs_remapping)( ptr_c_particles_buffer ) ) &&
            ( static_cast< size_t >( ::NS(Buffer_get_num_of_objects)(
                ptr_c_particles_buffer ) ) > particle_set_index ) &&
            ( ptr_c_beam_elem_buffer != nullptr ) &&
            ( !::NS(Buffer_needs_remapping)( ptr_c_beam_elem_buffer ) ) )
        {
            buffer_t* ptr_output_buffer = nullptr;
            c_buffer_t* ptr_c_output_buffer = nullptr;

            if( ( this->has_output_buffer() ) && ( !this->ownsOutputBuffer() ) )
            {
                ptr_output_buffer   = this->ptr_output_cxx_buffer();
                ptr_c_output_buffer = this->output_buffer();

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

    bool TrackJobBase::assign_output_buffer(
        _this_t::buffer_t& SIXTRL_RESTRICT_REF output_buffer )
    {
        bool success = false;

        if( this->doAssignNewOutputBuffer( output_buffer.getCApiPtr() ) )
        {
            if( this->has_output_buffer() )
            {
                SIXTRL_ASSERT( output_buffer.getCApiPtr() ==
                    this->output_buffer() );

                this->doSetPtrOutputBuffer( &output_buffer );
            }

            success = true;
        }

        return success;
    }

    bool TrackJobBase::assign_output_buffer(
        _this_t::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer )
    {
        return this->doAssignNewOutputBuffer( ptr_output_buffer );
    }

    /* --------------------------------------------------------------------- */

    _this_t::arch_id_t TrackJobBase::arch_id() const SIXTRL_NOEXCEPT
    {
        return this->m_arch_id;
    }

    std::string const& TrackJobBase::arch_str() const SIXTRL_NOEXCEPT
    {
        return this->m_arch_str;
    }

    char const* TrackJobBase::arch_cstr() const SIXTRL_NOEXCEPT
    {
        return this->m_arch_str.c_str();
    }

    bool TrackJobBase::has_node_id_str() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_node_id_str.empty() );
    }

    std::string const& TrackJobBase::node_id_str() const SIXTRL_NOEXCEPT
    {
        return this->m_node_id_str;
    }

    char const* TrackJobBase::node_id_cstr() const SIXTRL_NOEXCEPT
    {
        return this->m_node_id_str.c_str();
    }

    bool TrackJobBase::has_config_str() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_config_str.empty() );
    }

    std::string const& TrackJobBase::config_str() const SIXTRL_NOEXCEPT
    {
        return this->m_config_str;
    }

    char const* TrackJobBase::config_cstr() const SIXTRL_NOEXCEPT
    {
        return this->m_config_str.c_str();
    }

    /* --------------------------------------------------------------------- */

    _size_t TrackJobBase::num_particle_sets() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_num_particles_in_sets.size() ==
                       this->m_particle_set_indices.size() );

        return this->m_particle_set_indices.size();
    }

    _size_t const* TrackJobBase::particle_set_indices_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_num_particles_in_sets.size() ==
                       this->m_particle_set_indices.size() );

        return this->m_particle_set_indices.data();
    }

    _size_t const* TrackJobBase::particle_set_indices_end() const SIXTRL_NOEXCEPT
    {
        _size_t const* end_ptr = this->particle_set_indices_begin();
        SIXTRL_ASSERT( end_ptr != nullptr );
        std::advance( end_ptr, this->num_particle_sets() );
        return end_ptr;
    }

    _size_t TrackJobBase::particle_set_index( _size_t const n ) const
    {
        SIXTRL_ASSERT( this->m_num_particles_in_sets.size() ==
                       this->m_particle_set_indices.size() );

        return this->m_particle_set_indices.at( n );
    }

    _size_t const*
    TrackJobBase::num_particles_in_sets_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_num_particles_in_sets.size() ==
                       this->m_particle_set_indices.size() );

        return this->m_num_particles_in_sets.data();
    }

    _size_t const*
    TrackJobBase::num_particles_in_sets_end() const SIXTRL_NOEXCEPT
    {
        _size_t const* end_ptr = this->num_particles_in_sets_begin();
        SIXTRL_ASSERT( end_ptr != nullptr );
        std::advance( end_ptr, this->num_particle_sets() );
        return end_ptr;
    }

    _size_t TrackJobBase::num_particles_in_set( _size_t const n ) const
    {
        SIXTRL_ASSERT( this->m_num_particles_in_sets.size() ==
                       this->m_particle_set_indices.size() );

        return this->m_num_particles_in_sets.at( n );
    }

    _size_t TrackJobBase::total_num_particles_in_sets() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_num_particles_in_sets.size() ==
                       this->m_particle_set_indices.size() );

        return this->m_total_num_particles_in_sets;
    }

    /* --------------------------------------------------------------------- */

    _pindex_t TrackJobBase::min_particle_id() const SIXTRL_NOEXCEPT
    {
        return this->m_min_particle_id;
    }

    _pindex_t TrackJobBase::max_particle_id() const SIXTRL_NOEXCEPT
    {
        return this->m_max_particle_id;
    }

    _pindex_t TrackJobBase::min_element_id()  const SIXTRL_NOEXCEPT
    {
        return this->m_min_element_id;
    }

    _pindex_t TrackJobBase::max_element_id()  const SIXTRL_NOEXCEPT
    {
        return this->m_max_element_id;
    }

    _pindex_t TrackJobBase::min_initial_turn_id() const SIXTRL_NOEXCEPT
    {
        return this->m_min_initial_turn_id;
    }

    _pindex_t TrackJobBase::max_initial_turn_id() const SIXTRL_NOEXCEPT
    {
        return this->m_max_initial_turn_id;
    }

    /* --------------------------------------------------------------------- */

    _this_t::buffer_t* TrackJobBase::ptr_particles_cxx_buffer() SIXTRL_NOEXCEPT
    {
        return const_cast< _this_t::buffer_t* >( static_cast< _this_t const& >(
            *this ).ptr_particles_cxx_buffer() );
    }

    _this_t::buffer_t const*
    TrackJobBase::ptr_particles_cxx_buffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_particles_buffer == nullptr ) ||
            ( this->m_ptr_particles_buffer->getCApiPtr() ==
              this->m_ptr_c_particles_buffer ) );

        return this->m_ptr_particles_buffer;
    }

    _this_t::buffer_t const& TrackJobBase::particles_cxx_buffer() const
    {
        if( this->ptr_particles_cxx_buffer() == nullptr )
        {
            throw std::runtime_error( "no c++ particles buffer available" );
        }

        return *this->ptr_particles_cxx_buffer();
    }

    _this_t::buffer_t& TrackJobBase::particles_cxx_buffer()
    {
        return const_cast< _this_t::buffer_t& >( static_cast< _this_t const& >(
            *this ).particles_cxx_buffer() );
    }

    _this_t::c_buffer_t* TrackJobBase::particles_buffer() SIXTRL_NOEXCEPT
    {
        return const_cast< _this_t::c_buffer_t* >( static_cast<
            _this_t const& >( *this ).particles_buffer() );
    }

    _this_t::c_buffer_t const*
    TrackJobBase::particles_buffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_particles_buffer == nullptr ) ||
            ( this->m_ptr_particles_buffer->getCApiPtr() ==
              this->m_ptr_c_particles_buffer ) );

        return this->m_ptr_c_particles_buffer;
    }

    _this_t::buffer_toc_t const&
    TrackJobBase::particles_buffer_toc() const SIXTRL_NOEXCEPT
    {
        return this->m_particles_buffer_toc;
    }

    _this_t::buffer_toc_t const*
    TrackJobBase::ptr_particles_buffer_toc() const SIXTRL_NOEXCEPT
    {
        return &this->m_particles_buffer_toc;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    _this_t::buffer_t*
    TrackJobBase::ptr_beam_elements_cxx_buffer() SIXTRL_NOEXCEPT
    {
        return const_cast< _this_t::buffer_t* >( static_cast< _this_t const& >(
            *this ).ptr_beam_elements_cxx_buffer() );
    }

    _this_t::buffer_t const*
    TrackJobBase::ptr_beam_elements_cxx_buffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_beam_elem_buffer == nullptr ) ||
            ( this->m_ptr_beam_elem_buffer->getCApiPtr() ==
              this->m_ptr_c_beam_elem_buffer ) );

        return this->m_ptr_beam_elem_buffer;
    }

    _this_t::buffer_t const& TrackJobBase::beam_elements_cxx_buffer() const
    {
        if( this->ptr_beam_elements_cxx_buffer() == nullptr )
        {
            throw std::runtime_error( "no c++ beam elements buffer available" );
        }

        return *this->ptr_beam_elements_cxx_buffer();
    }

    _this_t::buffer_t& TrackJobBase::beam_elements_cxx_buffer()
    {
        return const_cast< _this_t::buffer_t& >( static_cast< _this_t const& >(
            *this ).beam_elements_cxx_buffer() );
    }

    _this_t::c_buffer_t* TrackJobBase::beam_elements_buffer() SIXTRL_NOEXCEPT
    {
        return const_cast< _this_t::c_buffer_t* >( static_cast<
            _this_t const& >( *this ).beam_elements_buffer() );
    }

    _this_t::c_buffer_t const*
    TrackJobBase::beam_elements_buffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_beam_elem_buffer == nullptr ) ||
            ( this->m_ptr_beam_elem_buffer->getCApiPtr() ==
              this->m_ptr_c_beam_elem_buffer ) );

        return this->m_ptr_c_beam_elem_buffer;
    }

    _this_t::buffer_toc_t const&
    TrackJobBase::beam_elements_buffer_toc() const SIXTRL_NOEXCEPT
    {
        return this->m_beam_elements_buffer_toc;
    }

    _this_t::buffer_toc_t const*
    TrackJobBase::ptr_beam_elements_buffer_toc() const SIXTRL_NOEXCEPT
    {
        return &this->m_beam_elements_buffer_toc;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobBase::can_fetch_particles_addr() const SIXTRL_NOEXCEPT
    {
        return false;
    }

    bool TrackJobBase::has_particles_addr() const SIXTRL_NOEXCEPT
    {
        return false;
    }

    _this_t::status_t TrackJobBase::fetch_particles_addr()
    {
        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    _this_t::status_t TrackJobBase::clear_all_particles_addr()
    {
        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    _this_t::status_t TrackJobBase::clear_particles_addr(
        _this_t::size_type const )
    {
        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    _this_t::particles_addr_t const* TrackJobBase::particles_addr(
        _this_t::size_type const ) const SIXTRL_NOEXCEPT
    {
        return nullptr;
    }

    _this_t::buffer_t const*
    TrackJobBase::ptr_particles_addr_buffer() const SIXTRL_NOEXCEPT
    {
        return nullptr;
    }

    _this_t::c_buffer_t const*
    TrackJobBase::ptr_particles_addr_cbuffer() const SIXTRL_NOEXCEPT
    {
        return nullptr;
    }

    /* ----------------------------------------------------------------- */

    _this_t::assign_item_t* TrackJobBase::add_assign_address_item(
        _this_t::assign_item_t const& SIXTRL_RESTRICT_REF assign_item_to_add )
    {
        _this_t::assign_item_t* item = nullptr;

        if( assign_item_to_add.valid() )
        {
            _this_t::assign_item_key_t const key =
            _this_t::assign_item_key_t{
                assign_item_to_add.getDestBufferId(),
                assign_item_to_add.getSrcBufferId() };

            _this_t::size_type item_index =
                std::numeric_limits< _this_t::size_type >::max();

            _this_t::status_t const status = this->doAddAssignAddressItem(
                assign_item_to_add, &item_index );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                item = this->doGetAssignAddressItem( key, item_index );
            }
        }

        return item;
    }

    _this_t::assign_item_t* TrackJobBase::add_assign_address_item(
        _this_t::object_type_id_t const dest_type_id,
        _this_t::size_type const dest_buffer_id,
        _this_t::size_type const dest_elem_index,
        _this_t::size_type const dest_pointer_offset,
        _this_t::object_type_id_t const src_type_id,
        _this_t::size_type const src_buffer_id,
        _this_t::size_type const src_elem_index,
        _this_t::size_type const src_pointer_offset )
    {
        return this->add_assign_address_item( _this_t::assign_item_t{
            dest_type_id, dest_buffer_id, dest_elem_index, dest_pointer_offset,
            src_type_id, src_buffer_id, src_elem_index, src_pointer_offset } );
    }

    _this_t::status_t TrackJobBase::remove_assign_address_item(
        _this_t::assign_item_t const& SIXTRL_RESTRICT_REF item_to_remove )
    {
        _this_t::assign_item_key_t const key =
        _this_t::assign_item_key_t{
            item_to_remove.getDestBufferId(),
            item_to_remove.getSrcBufferId() };

        _this_t::size_type const item_index =
            this->doFindAssingAddressItem( item_to_remove );

        return this->doRemoveAssignAddressItem( key, item_index );
    }

    _this_t::status_t TrackJobBase::remove_assign_address_item(
        _this_t::assign_item_key_t const& SIXTRL_RESTRICT_REF key,
        _this_t::size_type const index_of_item_to_remove )
    {
        return this->doRemoveAssignAddressItem( key, index_of_item_to_remove );
    }

    bool TrackJobBase::has_assign_address_item( _this_t::assign_item_t const&
        SIXTRL_RESTRICT_REF assign_item ) const SIXTRL_NOEXCEPT
    {
        _this_t::size_type const item_index =
            this->doFindAssingAddressItem( assign_item );

        return ( item_index < this->num_assign_items(
            assign_item.getDestBufferId(), assign_item.getSrcBufferId() ) );
    }

    bool TrackJobBase::has_assign_address_item(
        _this_t::object_type_id_t const dest_type_id,
        _this_t::size_type const dest_buffer_id,
        _this_t::size_type const dest_elem_index,
        _this_t::size_type const dest_pointer_offset,
        _this_t::object_type_id_t const src_type_id,
        _this_t::size_type const src_buffer_id,
        _this_t::size_type const src_elem_index,
        _this_t::size_type const src_pointer_offset ) const SIXTRL_NOEXCEPT
    {
        return this->has_assign_address_item( _this_t::assign_item_t{
            dest_type_id, dest_buffer_id, dest_elem_index, dest_pointer_offset,
            src_type_id, src_buffer_id, src_elem_index, src_pointer_offset } );
    }

    _this_t::size_type TrackJobBase::index_of_assign_address_item(
        _this_t::assign_item_t const& SIXTRL_RESTRICT_REF
            assign_item ) const SIXTRL_NOEXCEPT
    {
        return this->doFindAssingAddressItem( assign_item );
    }

    _this_t::size_type TrackJobBase::index_of_assign_address_item(
        _this_t::object_type_id_t const dest_type_id,
        _this_t::size_type const dest_buffer_id,
        _this_t::size_type const dest_elem_index,
        _this_t::size_type const dest_pointer_offset,
        _this_t::object_type_id_t const src_type_id,
        _this_t::size_type const src_buffer_id,
        _this_t::size_type const src_elem_index,
        _this_t::size_type const src_pointer_offset ) const SIXTRL_NOEXCEPT
    {
        return this->doFindAssingAddressItem( _this_t::assign_item_t{
            dest_type_id, dest_buffer_id, dest_elem_index, dest_pointer_offset,
            src_type_id, src_buffer_id, src_elem_index, src_pointer_offset } );
    }

    bool TrackJobBase::has_assign_items(
        _this_t::size_type const dest_buffer_id,
        _this_t::size_type const src_buffer_id ) const SIXTRL_NOEXCEPT
    {
        return ( this->num_assign_items( dest_buffer_id, src_buffer_id ) >
                    _this_t::size_type{ 0 } );
    }

    _this_t::size_type TrackJobBase::num_assign_items(
        _this_t::size_type const dest_buffer_id,
        _this_t::size_type const src_buffer_id ) const SIXTRL_NOEXCEPT
    {
        _this_t::size_type num_items = _this_t::size_type{ 0 };

        auto it = this->m_assign_address_items.find(
            _this_t::assign_item_key_t{ dest_buffer_id, src_buffer_id } );

        if( it != this->m_assign_address_items.end() )
        {
            num_items = it->second.getNumObjects();
        }

        return num_items;
    }

    _this_t::size_type
    TrackJobBase::num_distinct_available_assign_address_items_dest_src_pairs()
        const SIXTRL_NOEXCEPT
    {
        return this->m_assign_item_keys.size();
    }

    _this_t::size_type TrackJobBase::available_assign_address_items_dest_src_pairs(
        _this_t::size_type const max_num_pairs,
        _this_t::assign_item_key_t* pairs_begin ) const SIXTRL_NOEXCEPT
    {
        using size_t = _this_t::size_type;
        size_t num_pairs = size_t{ 0 };

        if( ( max_num_pairs > size_t{ 0 } ) && ( pairs_begin != nullptr ) &&
            ( !this->m_assign_address_items.empty() ) )
        {
            _this_t::assign_item_key_t* pairs_end = pairs_begin;
            std::advance( pairs_end, max_num_pairs );

            num_pairs = this->available_assign_address_items_dest_src_pairs(
                pairs_begin, pairs_end );
        }

        return num_pairs;
    }

    _this_t::c_buffer_t* TrackJobBase::buffer_by_buffer_id(
        _this_t::size_type const buffer_id ) SIXTRL_NOEXCEPT
    {
        using ptr_t = _this_t::c_buffer_t*;
        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).buffer_by_buffer_id( buffer_id ) );
    }

    _this_t::c_buffer_t const* TrackJobBase::buffer_by_buffer_id(
        _this_t::size_type const buffer_id ) const SIXTRL_NOEXCEPT
    {
        _this_t::c_buffer_t const* ptr_buffer = nullptr;

        switch( buffer_id )
        {
            case st::ARCH_PARTICLES_BUFFER_ID:
            {
                ptr_buffer = this->particles_buffer();
                break;
            }

            case st::ARCH_BEAM_ELEMENTS_BUFFER_ID:
            {
                ptr_buffer = this->beam_elements_buffer();
                break;
            }

            case st::ARCH_OUTPUT_BUFFER_ID:
            {
                ptr_buffer = this->output_buffer();
                break;
            }

            case st::ARCH_ELEM_BY_ELEM_CONFIG_BUFFER_ID:
            {
                ptr_buffer = this->m_my_config_buffer.get();
                break;
            }

            case st::ARCH_PARTICLE_ADDR_BUFFER_ID:
            {
                ptr_buffer = this->m_particles_addr_buffer.get();
                break;
            }

            default:
            {
                if( ( buffer_id >= st::ARCH_MIN_USER_DEFINED_BUFFER_ID ) &&
                    ( buffer_id <= st::ARCH_MAX_USER_DEFINED_BUFFER_ID ) )
                {
                    ptr_buffer = this->ptr_stored_buffer( buffer_id );
                }
            }
        };

        return ptr_buffer;
    }

    bool TrackJobBase::is_buffer_by_buffer_id(
        _this_t::size_type const buffer_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( buffer_id == st::ARCH_PARTICLES_BUFFER_ID ) ||
                 ( buffer_id == st::ARCH_BEAM_ELEMENTS_BUFFER_ID ) ||
                 ( buffer_id == st::ARCH_OUTPUT_BUFFER_ID ) ||
                 ( buffer_id == st::ARCH_ELEM_BY_ELEM_CONFIG_BUFFER_ID ) ||
                 ( buffer_id == st::ARCH_PARTICLE_ADDR_BUFFER_ID ) ||
                 ( ( buffer_id >= st::ARCH_MIN_USER_DEFINED_BUFFER_ID ) &&
                   ( buffer_id <= st::ARCH_MAX_USER_DEFINED_BUFFER_ID ) ) );
    }

    bool TrackJobBase::is_raw_memory_by_buffer_id(
        _this_t::size_type const buffer_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( buffer_id != st::ARCH_ILLEGAL_BUFFER_ID ) &&
                 ( !this->is_buffer_by_buffer_id( buffer_id ) ) );
    }

    SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(Object) const*
    TrackJobBase::assign_items_begin(
        _this_t::size_type const dest_buffer_id,
        _this_t::size_type const src_buffer_id ) const SIXTRL_NOEXCEPT
    {
        auto it = this->m_assign_address_items.find(
            _this_t::assign_item_key_t{ dest_buffer_id, src_buffer_id } );

        return ( it != this->m_assign_address_items.end() )
            ? ::NS(Buffer_get_const_objects_begin)( it->second.getCApiPtr() )
            : nullptr;
    }

    SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(Object) const*
    TrackJobBase::assign_items_end(
        _this_t::size_type const dest_buffer_id,
        _this_t::size_type const src_buffer_id ) const SIXTRL_NOEXCEPT
    {
        auto it = this->m_assign_address_items.find(
            _this_t::assign_item_key_t{ dest_buffer_id, src_buffer_id } );

        return ( it != this->m_assign_address_items.end() )
            ? ::NS(Buffer_get_const_objects_begin)( it->second.getCApiPtr() )
            : nullptr;
    }

    _this_t::assign_item_key_t const*
    TrackJobBase::assign_item_dest_src_begin() const SIXTRL_NOEXCEPT
    {
        return this->m_assign_item_keys.data();
    }

    _this_t::assign_item_key_t const*
    TrackJobBase::assign_item_dest_src_end() const SIXTRL_NOEXCEPT
    {
        _this_t::assign_item_key_t const* end_ptr =
            this->assign_item_dest_src_begin();

        if( ( end_ptr != nullptr ) && ( this->m_assign_item_keys.empty() ) )
        {
            std::advance( end_ptr, this->m_assign_address_items.size() );
        }

        return end_ptr;
    }

    _this_t::size_type
    TrackJobBase::total_num_assign_items() const SIXTRL_NOEXCEPT
    {
        using size_t = _this_t::size_type;
        size_t total_num_items = size_t{ 0 };

        auto it = this->m_assign_address_items.begin();
        auto end = this->m_assign_address_items.end();

        for( ; it != end ; ++it ) total_num_items += it->second.getNumObjects();
        return total_num_items;
    }

    _this_t::assign_item_t const* TrackJobBase::ptr_assign_address_item(
        _this_t::assign_item_t const& SIXTRL_RESTRICT_REF
            assign_address_item ) const SIXTRL_NOEXCEPT
    {
        _this_t::size_type const assign_item_idx =
            this->doFindAssingAddressItem( assign_address_item );

        return this->doGetAssignAddressItem( _this_t::assign_item_key_t{
                assign_address_item.getDestBufferId(),
                assign_address_item.getSrcBufferId() }, assign_item_idx );
    }


    _this_t::assign_item_t const* TrackJobBase::ptr_assign_address_item(
        _this_t::size_type const dest_buffer_id,
        _this_t::size_type const src_buffer_id,
        _this_t::size_type const assign_item_index ) const SIXTRL_NOEXCEPT
    {
        return this->doGetAssignAddressItem(
            _this_t::assign_item_key_t{ dest_buffer_id, src_buffer_id },
                assign_item_index );
    }

    _this_t::assign_item_t const* TrackJobBase::ptr_assign_address_item(
        _this_t::object_type_id_t const dest_type_id,
        _this_t::size_type const dest_buffer_id,
        _this_t::size_type const dest_elem_index,
        _this_t::size_type const dest_pointer_offset,
        _this_t::object_type_id_t const src_type_id,
        _this_t::size_type const src_buffer_id,
        _this_t::size_type const src_elem_index,
        _this_t::size_type const src_pointer_offset ) const SIXTRL_NOEXCEPT
    {
        return this->ptr_assign_address_item(
            _this_t::assign_item_t{ dest_type_id, dest_buffer_id,
                dest_elem_index, dest_pointer_offset, src_type_id,
                    src_buffer_id, src_elem_index, src_pointer_offset } );
    }

    _this_t::status_t TrackJobBase::commit_address_assignments()
    {
        return this->doCommitAddressAssignments();
    }

    _this_t::status_t TrackJobBase::assign_all_addresses()
    {
        _this_t::status_t status = st::ARCH_STATUS_SUCCESS;

        auto it = this->m_assign_address_items.begin();
        auto end = this->m_assign_address_items.end();

        for( ; it != end ; ++it )
        {
            status = this->doPerformAddressAssignments( it->first );
            if( status != st::ARCH_STATUS_SUCCESS ) break;
        }

        return status;
    }

    _this_t::status_t TrackJobBase::assign_addresses(
        _this_t::size_type const dest_buffer_id,
        _this_t::size_type const src_buffer_id )
    {
        return this->doPerformAddressAssignments(
            _this_t::assign_item_key_t{ dest_buffer_id, src_buffer_id } );
    }

    /* ---------------------------------------------------------------- */

    _size_t TrackJobBase::stored_buffers_capacity() const SIXTRL_NOEXCEPT
    {
        return this->m_stored_buffers.capacity();
    }

    _this_t::status_t TrackJobBase::reserve_stored_buffers_capacity(
        _size_t const capacity )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( capacity < this->m_stored_buffers.capacity() )
        {
            this->m_stored_buffers.reserve( capacity );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    bool TrackJobBase::has_stored_buffers() const SIXTRL_NOEXCEPT
    {
        return ( this->num_stored_buffers() > _this_t::size_type{ 0 } );
    }

    _this_t::size_type TrackJobBase::num_stored_buffers() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( std::count_if( this->m_stored_buffers.begin(),
            this->m_stored_buffers.end(),
            []( _this_t::buffer_store_t const& s) { return s.active(); } ) ==
            static_cast< std::ptrdiff_t >( this->m_num_stored_buffers ) );

        SIXTRL_ASSERT( this->m_stored_buffers.size() >=
                       this->m_num_stored_buffers );

        return this->m_num_stored_buffers;
    }

    _this_t::size_type TrackJobBase::min_stored_buffer_id() const SIXTRL_NOEXCEPT
    {
        return ( this->has_stored_buffers() )
            ? st::ARCH_MIN_USER_DEFINED_BUFFER_ID : st::ARCH_ILLEGAL_BUFFER_ID;
    }

    _this_t::size_type TrackJobBase::max_stored_buffer_id() const SIXTRL_NOEXCEPT
    {
        _this_t::size_type max_stored_buffers_id = this->min_stored_buffer_id();

        if( max_stored_buffers_id != st::ARCH_ILLEGAL_BUFFER_ID )
        {
            SIXTRL_ASSERT( this->m_stored_buffers.size() >= _size_t{ 1 } );
            max_stored_buffers_id += this->m_stored_buffers.size();
            max_stored_buffers_id -= _this_t::size_type{ 1 };
        }

        return max_stored_buffers_id;
    }

    bool TrackJobBase::owns_stored_buffer(
        _this_t::size_type const buffer_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr_buffer_store = this->doGetPtrBufferStore( buffer_id );
        return ( ( ptr_buffer_store != nullptr ) &&
                 ( ptr_buffer_store->owns_buffer() ) );
    }

    _this_t::status_t TrackJobBase::remove_stored_buffer(
        _this_t::size_type const buffer_index )
    {
        return this->doRemoveStoredBuffer( buffer_index );
    }

    _this_t::buffer_t& TrackJobBase::stored_cxx_buffer(
        _this_t::size_type const buffer_id )
    {
        return const_cast< _this_t::buffer_t& >( static_cast< _this_t const& >(
            *this ).stored_cxx_buffer( buffer_id ) );
    }

    _this_t::buffer_t const& TrackJobBase::stored_cxx_buffer(
        _this_t::size_type const buffer_id ) const
    {
        _this_t::buffer_t const* ptr_buffer =
            this->ptr_stored_cxx_buffer( buffer_id );

        if( ptr_buffer == nullptr )
        {
            throw std::runtime_error(
                "stored buffer does not have a c++ representation" );
        }

        return *ptr_buffer;
    }

    _this_t::buffer_t* TrackJobBase::ptr_stored_cxx_buffer(
        _this_t::size_type const buffer_id ) SIXTRL_NOEXCEPT
    {
        return const_cast< _this_t::buffer_t* >( static_cast< _this_t const& >(
            *this ).ptr_stored_cxx_buffer( buffer_id ) );
    }

    _this_t::buffer_t const* TrackJobBase::ptr_stored_cxx_buffer(
        _this_t::size_type const buffer_id ) const SIXTRL_NOEXCEPT
    {
        _this_t::buffer_store_t const* ptr_stored_buffer =
            this->doGetPtrBufferStore( buffer_id );

        return ( ptr_stored_buffer != nullptr )
            ? ptr_stored_buffer->ptr_cxx_buffer() : nullptr;
    }

    _this_t::c_buffer_t* TrackJobBase::ptr_stored_buffer(
        _this_t::size_type const buffer_id ) SIXTRL_NOEXCEPT
    {
        return const_cast< _this_t::c_buffer_t* >( static_cast<
            _this_t const& >( *this ).ptr_stored_buffer( buffer_id ) );
    }

    _this_t::c_buffer_t const* TrackJobBase::ptr_stored_buffer(
        _this_t::size_type const buffer_id ) const SIXTRL_NOEXCEPT
    {
        _this_t::buffer_store_t const* ptr_stored_buffer =
            this->doGetPtrBufferStore( buffer_id );

        return ( ptr_stored_buffer != nullptr )
            ? ptr_stored_buffer->ptr_buffer() : nullptr;
    }

    _this_t::status_t TrackJobBase::push_stored_buffer(
        _this_t::size_type const buffer_id )
    {
        return this->doPushStoredBuffer( buffer_id );
    }

    _this_t::status_t TrackJobBase::collect_stored_buffer(
        _this_t::size_type const buffer_id )
    {
        return this->doCollectStoredBuffer( buffer_id );
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobBase::has_output_buffer() const SIXTRL_NOEXCEPT
    {
        return ( this->output_buffer() != nullptr );
    }

    bool TrackJobBase::owns_output_buffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_my_output_buffer.get() == nullptr ) ||
            ( ( this->m_my_output_buffer.get() ==
                this->m_ptr_output_buffer ) &&
              ( this->m_my_output_buffer->getCApiPtr() ==
                this->m_ptr_c_output_buffer ) ) );

        return ( ( this->ptr_output_cxx_buffer() != nullptr ) &&
                 ( this->m_my_output_buffer.get() != nullptr ) );
    }

    _this_t::buffer_t* TrackJobBase::ptr_output_cxx_buffer() SIXTRL_NOEXCEPT
    {
        using ptr_t   = _this_t::buffer_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).ptr_output_cxx_buffer() );
    }

    _this_t::buffer_t* TrackJobBase::ptr_output_cxx_buffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_output_buffer == nullptr ) ||
            ( this->m_ptr_output_buffer->getCApiPtr() ==
              this->m_ptr_c_output_buffer ) );

        return this->m_ptr_output_buffer;
    }

    _this_t::c_buffer_t* TrackJobBase::output_buffer() SIXTRL_NOEXCEPT
    {
        using ptr_t   = _this_t::c_buffer_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).output_buffer() );
    }

    _this_t::c_buffer_t const*
    TrackJobBase::output_buffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_output_buffer == nullptr ) ||
            ( this->m_ptr_output_buffer->getCApiPtr() ==
              this->m_ptr_c_output_buffer ) );

        return this->m_ptr_c_output_buffer;
    }

    _this_t::buffer_t const& TrackJobBase::output_buffer() const
    {
        if( this->ptr_output_cxx_buffer() == nullptr )
        {
            throw std::runtime_error( "no c++ output buffer available" );
        }

        return *this->ptr_output_cxx_buffer();
    }

    _this_t::buffer_t& TrackJobBase::output_buffer()
    {
        return const_cast< _this_t::buffer_t& >( static_cast< _this_t const& >(
            *this ).output_buffer() );
    }

    _this_t::buffer_toc_t const&
    TrackJobBase::output_buffer_toc() const SIXTRL_NOEXCEPT
    {
        return this->m_output_buffer_toc;
    }

    _this_t::buffer_toc_t const*
    TrackJobBase::ptr_output_buffer_toc() const SIXTRL_NOEXCEPT
    {
        return &this->m_output_buffer_toc;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobBase::has_config_buffer() const SIXTRL_NOEXCEPT
    {
        return ( this->m_my_config_buffer.get() != nullptr );
    }

    bool TrackJobBase::has_config_entry(
        _this_t::config_id_t const config_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( config_id != _this_t::ILLEGAL_CONFIG_ID ) &&
                 ( this->m_my_config_buffer.get() != nullptr ) &&
                 ( this->m_my_config_buffer->getNumObjects() > config_id ) );
    }

    _this_t::c_buffer_t const*
    TrackJobBase::config_buffer() const SIXTRL_NOEXCEPT
    {
        return ( this->m_my_config_buffer.get() != nullptr )
            ? this->m_my_config_buffer->getCApiPtr() : nullptr;
    }

    _this_t::c_buffer_t* TrackJobBase::config_buffer() SIXTRL_NOEXCEPT
    {
        return ( this->m_my_config_buffer.get() != nullptr )
            ? this->m_my_config_buffer->getCApiPtr() : nullptr;
    }

    _this_t::buffer_t const*
    TrackJobBase::ptr_config_cxx_buffer() const SIXTRL_NOEXCEPT
    {
        return this->m_my_config_buffer.get();
    }

    _this_t::buffer_t* TrackJobBase::ptr_config_cxx_buffer() SIXTRL_NOEXCEPT
    {
        return this->m_my_config_buffer.get();
    }

    _this_t::buffer_t const& TrackJobBase::config_cxx_buffer() const
    {
        if( this->m_my_config_buffer.get() == nullptr )
        {
            throw std::runtime_error( "no config_buffer available" );
        }

        return *this->m_my_config_buffer.get();
    }

    _this_t::buffer_t& TrackJobBase::config_cxx_buffer()
    {
        return const_cast< _this_t::buffer_t&  >(
            static_cast< _this_t const& >( *this ).config_cxx_buffer() );
    }

    _this_t::buffer_toc_t const&
    TrackJobBase::config_buffer_toc() const SIXTRL_NOEXCEPT
    {
        return this->m_config_buffer_toc;
    }

    _this_t::buffer_toc_t const*
    TrackJobBase::ptr_config_buffer_toc() const SIXTRL_NOEXCEPT
    {
        return &this->m_config_buffer_toc;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBase::bool TrackJobBase::has_beam_monitors() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_beam_monitor_output_offsets.size() ==
            this->m_beam_elements_buffer_toc.num_type_elements(
                st::OBJECT_TYPE_BEAM_MONITOR ) );

        return !this->m_beam_elements_buffer_toc.has_type_elements(
            st::OBJECT_TYPE_BEAM_MONITOR );
    }

    bool TrackJobBase::has_beam_monitor_output() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_beam_monitor_output_offsets.size() ==
            this->m_beam_elements_buffer_toc.num_type_elements(
                st::OBJECT_TYPE_BEAM_MONITOR ) );

        bool has_beam_monitor_output = false;

        if( ( !this->m_beam_monitor_output_offsets.empty() ) &&
            ( this->has_output_buffer() ) )
        {
            _this_t::size_type const num_output_buffer_stores =
                ::NS(Buffer_get_num_of_objects)( this->output_buffer() );

            has_beam_monitor_output = true;

            for( auto const out_offset : this->m_beam_monitor_output_offsets )
            {
                if( out_offset >= num_output_buffer_stores )
                {
                    has_beam_monitor_output = false;
                    break;
                }
            }
        }

        return has_beam_monitor_output;
    }

    _this_t::size_type TrackJobBase::num_beam_monitors() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_beam_monitor_output_offsets.size() ==
            this->m_beam_elements_buffer_toc.num_type_elements(
                st::OBJECT_TYPE_BEAM_MONITOR ) );

        return this->m_beam_monitor_output_offsets.size();
    }

    _this_t::size_type const*
    TrackJobBase::beam_monitor_indices_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_beam_monitor_output_offsets.size() ==
            this->m_beam_elements_buffer_toc.num_type_elements(
                st::OBJECT_TYPE_BEAM_MONITOR ) );

        return ( !this->m_beam_monitor_indices.empty() )
            ? this->m_beam_elements_buffer_toc.type_elements_indices_begin(
                st::OBJECT_TYPE_BEAM_MONITOR ) : nullptr;
    }

    _this_t::size_type const*
    TrackJobBase::beam_monitor_indices_end() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_beam_monitor_output_offsets.size() ==
            this->m_beam_elements_buffer_toc.num_type_elements(
                st::OBJECT_TYPE_BEAM_MONITOR ) );

        return ( !this->m_beam_monitor_indices.empty() )
            ? this->m_beam_elements_buffer_toc.type_elements_indices_end(
                st::OBJECT_TYPE_BEAM_MONITOR ) : nullptr;
    }

    _this_t::size_type const*
    TrackJobBase::beam_monitor_output_offsets_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_beam_monitor_output_offsets.size() ==
            this->m_beam_elements_buffer_toc.num_type_elements(
                st::OBJECT_TYPE_BEAM_MONITOR ) );

        return ( !this->m_beam_monitor_output_offsets.empty() )
            ? this->m_beam_monitor_output_offsets.data() : nullptr;
    }

    _this_t::size_type const*
    TrackJobBase::beam_monitor_output_offsets_end() const SIXTRL_NOEXCEPT
    {
        _this_t::size_type const* end_ptr =
            this->beam_monitor_output_offsets_begin();

        if( end_ptr != nullptr )
        {
            std::advance( end_ptr,
                this->beam_monitor_output_offsets_begin.size() );
        }

        return end_ptr;
    }

    _this_t::size_type TrackJobBase::beam_monitor_index(
        _this_t::size_type const idx ) const
    {
        return this->m_beam_monitor_indices.at( idx );
    }

    _this_t::size_type TrackJobBase::min_beam_monitor_output_offset() const
    {
        SIXTRL_ASSERT( this->m_beam_monitor_output_offsets.size() ==
            this->m_beam_elements_buffer_toc.num_type_elements(
                st::OBJECT_TYPE_BEAM_MONITOR ) );

        if( this->m_beam_monitor_output_offsets.empty() )
        {
            throw std::runtime_error(
                "no beam monitor output offsets defined" );
        }

        auto it = std::min_element(
            this->m_beam_monitor_output_offsets.begin(),
            this->m_beam_monitor_output_offsets.end() );

        SIXTRL_ASSERT( it != this->m_beam_monitor_output_offsets.end() );
        return *it;
    }

    _this_t::size_type TrackJobBase::max_beam_monitor_output_offset() const
    {
        SIXTRL_ASSERT( this->m_beam_monitor_output_offsets.size() ==
            this->m_beam_elements_buffer_toc.num_type_elements(
                st::OBJECT_TYPE_BEAM_MONITOR ) );

        if( this->m_beam_monitor_output_offsets.empty() )
        {
            throw std::runtime_error(
                "no beam monitor output offsets defined" );
        }

        auto it = std::min_element(
            this->m_beam_monitor_output_offsets.begin(),
            this->m_beam_monitor_output_offsets.end() );

        SIXTRL_ASSERT( it != this->m_beam_monitor_output_offsets.end() );
        return *it;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobBase::has_elem_by_elem_configs() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_elem_by_elem_output_offsets.size() ==
            this->m_config_buffer_toc.num_type_elements(
                st::OBJECT_TYPE_BEAM_MONITOR ) );

        return ( (  this->ptr_config_cxx_buffer() != nullptr ) &&
                 ( !this->m_elem_by_elem_config_ids.empty() )
                 (  this->ptr_config_cxx_buffer()->getNumObjects() >
                    this->m_elem_by_elem_config_ids.front() ) );
    }

    bool TrackJobBase::has_elem_by_elem_output() const SIXTRL_NOEXCEPT
    {
        bool has_elem_by_elem_output = false;

        SIXTRL_ASSERT( this->m_elem_by_elem_output_offsets.size() ==
            this->m_config_buffer_toc.num_type_elements(
                st::OBJECT_TYPE_BEAM_MONITOR ) );

        if( ( !this->m_elem_by_elem_output_offsets.empty() ) &&
            ( this->has_output_buffer() ) )
        {
            _this_t::size_type const num_output_buffer_stores =
                ::NS(Buffer_get_num_of_objects)( this->output_buffer() );

            has_elem_by_elem_output = true;

            for( auto const out_offset : this->m_elem_by_elem_output_offset )
            {
                if( out_offset >= num_output_buffer_stores )
                {
                    has_elem_by_elem_output = false;
                    break;
                }
            }
        }

        return has_elem_by_elem_output;
    }

    _this_t::size_type
    TrackJobBase::num_elem_by_elem_configs() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_elem_by_elem_config_ids.size() ==
                       this->m_elem_by_elem_output_offset.size() );

        return this->m_elem_by_elem_config_ids.size();
    }

    _this_t::config_id_t const*
    TrackJobBase::elem_by_elem_config_ids_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_elem_by_elem_config_ids.size() ==
                       this->m_elem_by_elem_output_offset.size() );

        return ( !this->m_elem_by_elem_config_ids.empty() )
            ? this->m_elem_by_elem_config_ids.data() : nullptr;
    }

    _this_t::config_id_t const*
    TrackJobBase::elem_by_elem_config_ids_end() const SIXTRL_NOEXCEPT
    {
        _this_t::config_id_t const* end_ptr =
            this->elem_by_elem_config_ids_begin();

        if( end_ptr != nullptr )
        {
            std::advance( end_ptr, this->m_elem_by_elem_config_ids.size() );
        }

        return end_ptr;
    }

    _this_t::size_type const*
    TrackJobBase::elem_by_elem_output_offsets_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_elem_by_elem_config_ids.size() ==
                       this->m_elem_by_elem_output_offset.size() );

        return ( !this->m_elem_by_elem_output_offset.empty() )
            ? this->m_elem_by_elem_output_offset.data() : nullptr;
    }

    _this_t::size_type const*
    TrackJobBase::elem_by_elem_output_offsets_end() const SIXTRL_NOEXCEPT
    {
        _this_t::config_id_t const* end_ptr =
            this->elem_by_elem_output_offsets_begin();

        if( end_ptr != nullptr )
        {
            std::advance( end_ptr, this->m_elem_by_elem_output_offset.size() );
        }

        return end_ptr;
    }

    _this_t::config_id_t TrackJobBase::elem_by_elem_config_id(
        _this_t::size_type const idx ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_elem_by_elem_config_ids.size() ==
                       this->m_elem_by_elem_output_offset.size() );

        return ( this->m_elem_by_elem_config_ids.size() > idx )
            ? this->m_elem_by_elem_config_ids[ idx ]
            : _this_t::ILLEGAL_CONFIG_ID;
    }

    _elem_conf_t const* TrackJobBase::elem_by_elem_config_by_id(
        _this_t::config_id_t const conf_id ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_elem_by_elem_config_ids.size() ==
                       this->m_elem_by_elem_output_offset.size() );

        _elem_conf_t const* ptr = (
            ( conf_id != _this_t::ILLEGAL_CONFIG_ID ) &&
            ( this->ptr_config_cxx_buffer() != nullptr ) &&
            ( this->ptr_config_cxx_buffer()->getNumObjects() > conf_id ) )
                ? this->ptr_config_cxx_buffer()->get< _elem_conf_t >( conf_id )
                : nullptr;

        SIXTRL_ASSERT( ( ptr == nullptr ) ||
            ( std::find( this->m_elem_by_elem_config_ids.begin(),
                this->m_elem_by_elem_config_ids.end(), conf_id ) !=
                    this->m_elem_by_elem_config_ids.end() ) );

        return ptr;
    }

    _this_t::elem_by_elem_config_t* TrackJobBase::elem_by_elem_config_by_id(
        TrackJobBase::config_id_t const conf_id ) const SIXTRL_NOEXCEPT
    {
        return const_cast< _elem_conf_t* >( static_cast< _this_t const& >(
            *this ).elem_by_elem_config_by_id( conf_id ) );
    }

    _pindex_t TrackJobBase::until_turn_elem_by_elem_by_id(
        _this_t::config_id_t const elem_by_elem_conf_id ) const SIXTRL_NOEXCEPT
    {
        return ::NS(ElemByElemConfig_get_until_turn_elem_by_elem)(
            this->elem_by_elem_config_by_id( elem_by_elem_conf_id ) );
    }

    _size_t TrackJobBase::num_elem_by_elem_turns_by_id(
        _this_t::config_id_t const elem_by_elem_conf_id ) const SIXTRL_NOEXCEPT
    {
        return ::NS(ElemByElemConfig_get_num_turns_elem_by_elem)(
            this->elem_by_elem_config_by_id( elem_by_elem_conf_id ) );
    }

    _size_t TrackJobBase::elem_by_elem_output_offset_by_id(
        _this_t::config_id_t const conf_id ) const SIXTRL_NOEXCEPT
    {
        _size_t output_offset = _this_t::ILLEGAL_OUTPUT_BUFFER_OFFSET;

        SIXTRL_ASSERT( this->m_elem_by_elem_config_ids.size() ==
                       this->m_elem_by_elem_output_offset.size() );

        auto it = std::find( this->m_elem_by_elem_config_ids.begin(),
                             this->m_elem_by_elem_config_ids.end(), conf_id );

        if( it != this->m_elem_by_elem_config_ids.end() )
        {
            std::ptrdiff_t const dist = std::distance(
                this->m_elem_by_elem_config_ids.begin(), it );

            if( dist >= std::ptrdiff_t{ 0 } )
            {
                _size_t const ii = static_cast< _size_t >( dist );
                SIXTRL_ASSERT( this->m_elem_by_elem_config_ids[ ii ] == conf_id );
                output_offset = this->m_elem_by_elem_output_offset[ ii ];
            }
        }

        return output_offset;
    }

    bool TrackJobBase::default_elem_by_elem_rolling() const SIXTRL_NOEXCEPT
    {
        return this->m_default_elem_by_elem_rolling;
    }

    void TrackJobBase::set_default_elem_by_elem_rolling(
        bool is_rolling ) SIXTRL_NOEXCEPT
    {
        this->m_default_elem_by_elem_rolling = is_rolling;
    }

    _this_t::elem_by_elem_order_t
    TrackJobBase::default_elem_by_elem_config_order() const SIXTRL_NOEXCEPT
    {
        return this->m_default_elem_by_elem_order;
    }

    void TrackJobBase::set_default_elem_by_elem_config_order(
        _this_t::elem_by_elem_order_t const elem_by_elem_order ) SIXTRL_NOEXCEPT
    {
        this->m_default_elem_by_elem_order = elem_by_elem_order;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    _elem_conf_t const* TrackJobBase::elem_by_elem_config() const SIXTRL_NOEXCEPT
    {
        return ( (  this->has_elem_by_elem_configs() ) &&
                 ( !this->m_elem_by_elem_config_ids.empty() ) )
            ? return this->elem_by_elem_config_by_id(
                this->m_elem_by_elem_config_ids.front() )
            : nullptr;
    }

    _elem_conf_t* TrackJobBase::elem_by_elem_config() SIXTRL_NOEXCEPT
    {
        return const_cast< _elem_conf_t* >( static_cast< _this_t const& >(
            *this ).elem_by_elem_config() );
    }

    _size_t TrackJobBase::elem_by_elem_output_offset() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_elem_by_elem_config_ids.empty() )
            ? this->elem_by_elem_output_offset_by_id(
                this->m_elem_by_elem_config_ids.front() )
            : _this_t::ILLEGAL_OUTPUT_BUFFER_OFFSET;
    }

    _pindex_t TrackJobBase::until_turn_elem_by_elem() const SIXTRL_NOEXCEPT
    {
        return ::NS(ElemByElemConfig_get_until_turn_elem_by_elem)(
            this->elem_by_elem_config() );
    }

    _size_t TrackJobBase::num_elem_by_elem_turns() const SIXTRL_NOEXCEPT
    {
        return ::NS(ElemByElemConfig_get_num_turns_elem_by_elem)(
            this->elem_by_elem_config() );
    }

    /* --------------------------------------------------------------------- */

    TrackJobBase::TrackJobBase(
        const char *const SIXTRL_RESTRICT type_str,
        arch_id_t const type_id ) :
        m_assign_address_items(),
        m_arch_str(),
        m_node_id_str(),
        m_config_str(),
        m_particle_set_indices(),
        m_num_particles_in_sets(),
        m_stored_buffers(),
        m_assign_item_keys(),
        m_beam_monitor_indices(),
        m_beam_monitor_output_offsets(),
        m_elem_by_elem_config_ids(),
        m_elem_by_elem_output_offsets(),
        m_my_output_buffer( nullptr ),
        m_my_config_buffer( nullptr ),
        m_particles_addr_buffer( nullptr ),
        m_ptr_particles_buffer( nullptr ),
        m_ptr_beam_elem_buffer( nullptr ),
        m_ptr_output_buffer( nullptr ),
        m_ptr_c_particles_buffer( nullptr ),
        m_ptr_c_beam_elem_buffer( nullptr ),
        m_ptr_c_output_buffer( nullptr ),
        m_total_num_particles_in_sets( _size_t{ 0 } ),
        m_num_stored_buffers( _size_t{ 0 } ),
        m_arch_id( type_id ),
        m_default_elem_by_elem_order( ::NS(ELEM_BY_ELEM_ORDER_DEFAULT) ),
        m_min_particle_id( _pindex_t{ 0 } ),
        m_max_particle_id( _pindex_t{ 0 } ),
        m_min_element_id( _pindex_t{ 0 } ),
        m_max_element_id( _pindex_t{ 0 } ),
        m_min_initial_turn_id( _pindex_t{ 0 } ),
        m_max_initial_turn_id( _pindex_t{ 0 } ),
        m_collect_flags( st::TRACK_JOB_IO_DEFAULT_FLAGS ),
        m_requires_collect( true ),
        m_default_elem_by_elem_rolling( true ),
        m_debug_mode( false )
    {
        if( type_str != nullptr ) this->m_arch_str = type_str;

        this->doInitDefaultParticleSetIndices();
        this->doInitDefaultBeamMonitorIndices();
        this->doPrepareConfigStructuresBaseImpl();
    }

    TrackJobBase::TrackJobBase( TrackJobBase const& other ) :
        m_assign_address_items( other.m_assign_address_items ),
        m_arch_str( other.m_arch_str ),
        m_node_id_str( other.m_arch_str ),
        m_config_str( other.m_config_str ),
        m_particle_set_indices( other.m_particle_set_indices ),
        m_num_particles_in_sets( other.m_num_particles_in_sets ),
        m_stored_buffers( other.m_stored_buffers ),
        m_assign_item_keys( other.m_assign_item_keys ),
        m_beam_monitor_indices( other.m_beam_monitor_indices ),
        m_beam_monitor_output_offsets( other.m_beam_monitor_output_offsets ),
        m_elem_by_elem_config_ids( other.m_elem_by_elem_config_ids ),
        m_elem_by_elem_output_offsets( other.m_elem_by_elem_output_offsets ),
        m_my_output_buffer( nullptr ),
        m_my_config_buffer( nullptr ),
        m_particles_addr_buffer( nullptr ),
        m_ptr_particles_buffer( other.m_ptr_particles_buffer  ),
        m_ptr_beam_elem_buffer( other.m_ptr_beam_elem_buffer ),
        m_ptr_output_buffer( nullptr ),
        m_ptr_c_particles_buffer( other.m_ptr_c_particles_buffer ),
        m_ptr_c_beam_elem_buffer( other.m_ptr_c_beam_elem_buffer ),
        m_ptr_c_output_buffer( nullptr ),
        m_total_num_particles_in_sets( other.m_total_num_particles_in_sets ),
        m_num_stored_buffers( other.m_num_stored_buffers ),
        m_arch_id( other.m_arch_id ),
        m_default_elem_by_elem_order( other.m_default_elem_by_elem_order ),
        m_min_particle_id( other.m_min_particle_id ),
        m_max_particle_id( other.m_max_particle_id ),
        m_min_element_id( other.m_min_element_id ),
        m_max_element_id( other.m_max_element_id ),
        m_min_initial_turn_id( other.m_min_initial_turn_id ),
        m_max_initial_turn_id( other.m_max_initial_turn_id ),
        m_collect_flags( other.m_collect_flags ),
        m_requires_collect( other.m_requires_collect ),
        m_default_elem_by_elem_rolling( other.m_default_elem_by_elem_rolling ),
        m_debug_mode( other.m_debug_mode )
    {
        if( other.ownsOutputBuffer() )
        {
            _this_t::COPY_PTR_BUFFER(
                this->m_my_output_buffer, other.m_my_output_buffer );

            this->m_ptr_output_buffer = this->m_my_output_buffer.get();
            if( this->m_ptr_output_buffer != nullptr )
            {
                this->m_ptr_c_output_buffer =
                    this->m_ptr_output_buffer->getCApiPtr();
            }
        }

        _this_t::COPY_PTR_BUFFER(
            this->m_my_config_buffer, other.m_my_config_buffer );

        _this_t::COPY_PTR_BUFFER(
            this->m_particles_addr_buffer, other.m_particles_addr_buffer );
    }

    TrackJobBase::TrackJobBase(
        TrackJobBase&& o ) SIXTRL_NOEXCEPT :
        m_assign_address_items( std::move( o.m_assign_address_items ) ),
        m_arch_str( std::move( o.m_arch_str ) ),
        m_node_id_str( std::move( o.m_arch_str ) ),
        m_config_str( std::move( o.m_config_str ) ),
        m_particle_set_indices( std::move( o.m_particle_set_indices ) ),
        m_num_particles_in_sets( std::move( o.m_num_particles_in_sets ) ),
        m_stored_buffers( std::move( o.m_stored_buffers ) ),
        m_assign_item_keys( std::move( o.m_assign_item_keys ) ),
        m_beam_monitor_indices( std::move( o.m_beam_monitor_indices ) ),
        m_beam_monitor_output_offsets(
            std::move( o.m_beam_monitor_output_offsets ) ),
        m_elem_by_elem_config_ids( std::move( o.m_elem_by_elem_config_ids ) ),
        m_elem_by_elem_output_offsets(
            std::move( o.m_elem_by_elem_output_offsets ) ),
        m_my_output_buffer( std::move( o.m_my_output_buffer ) ),
        m_my_config_buffer( std::move( o.m_my_config_buffer ) ),
        m_particles_addr_buffer( std::move( o.m_particles_addr_buffer ) ),
        m_ptr_particles_buffer( std::move( o.m_ptr_particles_buffer  ) ),
        m_ptr_beam_elem_buffer( std::move( o.m_ptr_beam_elem_buffer ) ),
        m_ptr_output_buffer( std::move( o.m_ptr_output_buffer ) ),
        m_ptr_c_particles_buffer( std::move( o.m_ptr_c_particles_buffer ) ),
        m_ptr_c_beam_elem_buffer( std::move( o.m_ptr_c_beam_elem_buffer ) ),
        m_ptr_c_output_buffer( std::move( o.m_ptr_c_output_buffer ) ),
        m_total_num_particles_in_sets( std::move(
            o.m_total_num_particles_in_sets ) ),
        m_num_stored_buffers( std::move( o.m_num_stored_buffers ) ),
        m_arch_id( std::move( o.m_arch_id ) ),
        m_default_elem_by_elem_order( std::move(
            o.m_default_elem_by_elem_order ) ),
        m_min_particle_id( std::move( o.m_min_particle_id ) ),
        m_max_particle_id( std::move( o.m_max_particle_id ) ),
        m_min_element_id( std::move( o.m_min_element_id ) ),
        m_max_element_id( std::move( o.m_max_element_id ) ),
        m_min_initial_turn_id( std::move( o.m_min_initial_turn_id ) ),
        m_max_initial_turn_id( std::move( o.m_max_initial_turn_id ) ),
        m_collect_flags( std::move( o.m_collect_flags ) ),
        m_requires_collect( std::move( o.m_requires_collect ) ),
        m_default_elem_by_elem_rolling( std::move(
            o.m_default_elem_by_elem_rolling ) ),
        m_debug_mode( std::move( o.m_debug_mode ) )
    {
        o.m_arch_str.clear();
        o.m_node_id_str.clear();
        o.m_config_str.clear();

        o.doClearBaseImpl();
    }

    TrackJobBase& TrackJobBase::operator=(
        TrackJobBase const& rhs )
    {
        if( this != &rhs )
        {
            this->m_assign_address_items        = rhs.m_assign_address_items;
            this->m_arch_str                    = rhs.m_arch_str;
            this->m_node_id_str               = rhs.m_arch_str;
            this->m_config_str                  = rhs.m_config_str;
            this->m_particle_set_indices        = rhs.m_particle_set_indices;
            this->m_num_particles_in_sets       = rhs.m_num_particles_in_sets;
            this->m_beam_monitor_indices        = rhs.m_beam_monitor_indices;
            this->m_ptr_particles_buffer        = rhs.m_ptr_particles_buffer;
            this->m_ptr_beam_elem_buffer        = rhs.m_ptr_beam_elem_buffer;
            this->m_ptr_c_particles_buffer      = rhs.m_ptr_c_particles_buffer;
            this->m_ptr_c_beam_elem_buffer      = rhs.m_ptr_c_beam_elem_buffer;

            this->m_total_num_particles_in_sets =
                rhs.m_total_num_particles_in_sets;

            this->m_num_stored_buffers         = rhs.m_num_stored_buffers;
            this->m_assign_item_keys           = rhs.m_assign_item_keys;

            this->m_beam_monitor_indices =
                rhs.m_beam_monitor_indices;

            this->m_beam_monitor_output_offsets =
                rhs.m_beam_monitor_output_offsets;

            this->m_elem_by_elem_config_ids =
                rhs.m_elem_by_elem_config_ids;

            this->m_elem_by_elem_output_offsets =
                rhs.m_elem_by_elem_output_offsets;

            this->m_default_elem_by_elem_order =
                rhs.m_default_elem_by_elem_order;

            this->m_arch_id                    = rhs.m_arch_id;
            this->m_min_particle_id            = rhs.m_min_particle_id;
            this->m_max_particle_id            = rhs.m_max_particle_id;
            this->m_min_element_id             = rhs.m_min_element_id;
            this->m_max_element_id             = rhs.m_max_element_id;
            this->m_min_initial_turn_id        = rhs.m_min_initial_turn_id;
            this->m_max_initial_turn_id        = rhs.m_max_initial_turn_id;

            this->m_default_elem_by_elem_rolling =
                rhs.m_default_elem_by_elem_rolling;

            this->m_requires_collect        = rhs.m_requires_collect;
            this->m_collect_flags           = rhs.m_collect_flags;
            this->m_stored_buffers          = rhs.m_stored_buffers;

            if( rhs.ownsOutputBuffer() )
            {
                _this_t::COPY_PTR_BUFFER(
                    this->m_my_output_buffer, rhs.m_my_output_buffer );

               this->m_ptr_output_buffer = this->m_my_output_buffer.get();
               if( this->m_ptr_output_buffer != nullptr )
               {
                   this->m_ptr_c_output_buffer =
                    this->m_ptr_output_buffer->getCApiPtr();
               }
            }
            else
            {
                this->m_ptr_output_buffer   = rhs.m_ptr_output_buffer;
                this->m_ptr_c_output_buffer = rhs.m_ptr_c_output_buffer;
            }

            _this_t::COPY_PTR_BUFFER(
                this->m_my_config_buffer, rhs.m_my_config_buffer );

            _this_t::COPY_PTR_BUFFER(
                this->m_particles_addr_buffer, rhs.m_particles_addr_buffer );

            this->m_debug_mode = rhs.m_debug_mode;
        }

        return *this;
    }

    TrackJobBase& TrackJobBase::operator=(
        TrackJobBase&& rhs ) SIXTRL_NOEXCEPT
    {
        if( this != &rhs )
        {
            this->m_assign_address_items =
                std::move( rhs.m_assign_address_items );

            this->m_arch_str         = std::move( rhs.m_arch_str );
            this->m_node_id_str    = std::move( rhs.m_arch_str );
            this->m_config_str       = std::move( rhs.m_config_str );

            this->m_particle_set_indices =
                std::move( rhs.m_particle_set_indices );

            this->m_num_particles_in_sets =
                std::move( rhs.m_num_particles_in_sets );

            this->m_stored_buffers   = std::move( rhs.m_stored_buffers );
            this->m_assign_item_keys = std::move( rhs.m_assign_item_keys );

            this->m_beam_monitor_indices =
                std::move( rhs.m_beam_monitor_indices );

            this->m_beam_monitor_output_offsets =
                std::move( rhs.m_beam_monitor_output_offsets );

            this->m_elem_by_elem_config_ids =
                std::move( rhs.m_elem_by_elem_config_ids );

            this->m_elem_by_elem_output_offsets =
                std::move( rhs.m_elem_by_elem_output_offsets );

            this->m_my_output_buffer = std::move( rhs.m_my_output_buffer );

            this->m_my_config_buffer =
                std::move( rhs.m_my_config_buffer );

            this->m_particles_addr_buffer =
                std::move( rhs.m_particles_addr_buffer );

            this->m_assign_address_items =
                std::move( rhs.m_assign_address_items );

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

            this->m_total_num_particles_in_sets =
                std::move( rhs.m_total_num_particles_in_sets );

            this->m_num_stored_buffers =
                std::move( rhs.m_num_stored_buffers );

            this->m_arch_id = std::move( rhs.m_arch_id );

            this->m_default_elem_by_elem_order =
                std::move( rhs.m_default_elem_by_elem_order );

            this->m_min_particle_id     = std::move( rhs.m_min_particle_id );
            this->m_max_particle_id     = std::move( rhs.m_max_particle_id );
            this->m_min_element_id      = std::move( rhs.m_min_element_id  );
            this->m_max_element_id      = std::move( rhs.m_max_element_id  );
            this->m_min_initial_turn_id = std::move( rhs.m_min_initial_turn_id);
            this->m_max_initial_turn_id = std::move( rhs.m_max_initial_turn_id);

            this->m_requires_collect = std::move( rhs.m_requires_collect );
            this->m_collect_flags = std::move( rhs.m_collect_flags );

            this->m_default_elem_by_elem_rolling =
                std::move( rhs.m_default_elem_by_elem_rolling );

            this->m_debug_mode = std::move( rhs.m_debug_mode );

            rhs.m_arch_str.clear();
            rhs.m_node_id_str.clear();
            rhs.m_config_str.clear();

            rhs.m_arch_id = _this_t::arch_id_t{ 0 };
            rhs.doClearBaseImpl();
        }

        return *this;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBase::doClear()
    {
        this->doClearBaseImpl();
    }

    void TrackJobBase::doCollect( collect_flag_t const ) {}
    void TrackJobBase::doPush( push_flag_t const ) {}

    _this_t::track_status_t TrackJobBase::doTrackUntilTurn( size_type const )
    {
        return _this_t::track_status_t{ -1 };
    }

    _this_t::track_status_t TrackJobBase::doTrackElemByElem( size_type const )
    {
        return _this_t::track_status_t{ -1 };
    }

    _this_t::track_status_t
    TrackJobBase::doTrackLine( size_type const, size_type const, bool const )
    {
        return _this_t::track_status_t{ -1 };
    }

    /* --------------------------------------------------------------------- */

    _this_t::status_t TrackJobBase::doPrepareConfigStructures()
    {
        return this->doPrepareConfigStructuresBaseImpl();
    }

    bool TrackJobBase::doPrepareParticlesStructures(
        _this_t::c_buffer_t* SIXTRL_RESTRICT pb )
    {
        bool success = false;

        using size_t    = _size_t;
        using p_index_t = _pindex_t;

        SIXTRL_STATIC_VAR size_t const ZERO = size_t{ 0 };
        SIXTRL_STATIC_VAR size_t const ONE  = size_t{ 1 };

        size_t const nn = this->num_particle_sets();
        size_t const num_psets = ::NS(Buffer_get_num_of_objects)( pb );

        if( ( pb != nullptr ) && ( ( nn > ZERO ) || ( nn == ZERO ) ) &&
            ( !::NS(Buffer_needs_remapping)( pb ) ) && ( num_psets >= nn ) )
        {
            int ret = int{ -1 };

            size_t const first_index = ( nn > ZERO )
                ? this->particle_set_index( ZERO ) : ZERO;

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
                    pb, nn, this->particle_set_indices_begin(),
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

            if( success )
            {
                if( this->m_particles_addr_buffer.get() == nullptr )
                {
                    _this_t::ptr_buffer_t particles_addr_buffer(
                        new _this_t::buffer_t );

                    this->doUpdateStoredParticlesAddrBuffer(
                        std::move( particles_addr_buffer ) );
                }

                if( this->m_particles_addr_buffer.get() != nullptr )
                {
                    success = ( st::ARCH_STATUS_SUCCESS ==
                    ::NS(ParticlesAddr_prepare_buffer_based_on_particles_buffer)(
                        this->m_particles_addr_buffer->getCApiPtr(), pb ) );
                }
            }
        }

        return success;
    }

    bool TrackJobBase::doPrepareBeamElementsStructures(
        _this_t::c_buffer_t* SIXTRL_RESTRICT belems )
    {
        bool success = false;

        using size_t        = _size_t;
        using p_index_t     = _pindex_t;
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
            p_index_t min_elem_id = this->min_element_id();
            p_index_t max_elem_id = this->max_element_id();

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
                ( this->particles_buffer() != nullptr ) &&
                ( this->min_particle_id() <= this->max_particle_id() ) )
            {
                auto it  = this->beamMonitorIndicesBegin();
                auto end = this->beamMonitorIndicesEnd();

                p_index_t const min_part_id = this->min_particle_id();
                p_index_t const max_part_id = this->max_particle_id();

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
        _this_t::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        _this_t::c_buffer_t* SIXTRL_RESTRICT beam_elements_buffer,
        _this_t::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        _size_t const until_turn_elem_by_elem )
    {
        bool success = false;

        using size_t                    = _size_t;
        using c_buffer_t                = _this_t::c_buffer_t;
        using buf_size_t                = ::NS(buffer_size_t);
        using elem_by_elem_config_t     = _this_t::elem_by_elem_config_t;
        using ptr_output_buffer_t       = _this_t::ptr_buffer_t;
        using par_index_t               = _pindex_t;

        ( void )particles_buffer;

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
            if( !this->has_output_buffer() )
            {
                SIXTRL_ASSERT( !this->ownsOutputBuffer() );
                _this_t::ptr_buffer_t managed_output_buffer(
                    new _this_t::buffer_t );

                SIXTRL_ASSERT(  managed_output_buffer.get() != nullptr );
                output_buffer = managed_output_buffer.get()->getCApiPtr();
                SIXTRL_ASSERT( output_buffer != nullptr );

                this->doUpdateStoredOutputBuffer(
                    std::move( managed_output_buffer ) );

                SIXTRL_ASSERT( managed_output_buffer.get() == nullptr );
                SIXTRL_ASSERT( this->ownsOutputBuffer() );
                SIXTRL_ASSERT( this->output_buffer() == output_buffer );
            }
            else
            {
                output_buffer = this->output_buffer();
            }

            SIXTRL_ASSERT( this->has_output_buffer() );
        }
        else
        {
            if( !this->has_output_buffer() )
            {
                this->doSetPtrCOutputBuffer( output_buffer );
            }
            else if( !this->ownsOutputBuffer() )
            {
                this->doSetPtrCOutputBuffer( output_buffer );
            }
            else if( ( this->ownsOutputBuffer() ) &&
                     ( this->output_buffer() != nullptr ) &&
                     ( this->output_buffer() != output_buffer ) )
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
                this->min_particle_id(), this->max_particle_id(),
                this->min_element_id(),  this->max_element_id(),
                this->min_initial_turn_id(), this->max_initial_turn_id(),
                until_turn_elem_by_elem,
                &elem_by_elem_out_idx_offset, &be_monitor_out_idx_offset,
                &max_elem_by_elem_turn_id );

            if( this->m_my_config_buffer.get() == nullptr )
            {
                _this_t::ptr_buffer_t elem_by_elem_buffer(
                    new _this_t::buffer_t );

                this->doUpdateStoredConfigBuffer(
                    std::move( elem_by_elem_buffer ) );
            }
            else
            {
                this->m_my_config_buffer->reset();
            }

            SIXTRL_ASSERT( this->m_my_config_buffer.get() != nullptr );
            SIXTRL_ASSERT( this->m_my_config_buffer->getNumObjects() ==
                           _this_t::size_type{ 0 } );

            if( ( this->has_config_buffer() ) &&
                ( ret == 0 ) && ( until_turn_elem_by_elem > ZERO ) &&
                ( this->min_initial_turn_id() >= par_index_t{ 0 } ) &&
                ( max_elem_by_elem_turn_id >= this->min_initial_turn_id() ) &&
                ( until_turn_elem_by_elem > static_cast< buf_size_t >(
                    this->min_initial_turn_id() ) ) )
            {
                elem_by_elem_config_t* conf = nullptr;

                if( this->has_elem_by_elem_configs() )
                {
                    SIXTRL_ASSERT( !this->m_until_turn_elem_by_elem.empty() );
                    SIXTRL_ASSERT( !this->m_elem_by_elem_output_offsets.empty() );

                    this->m_elem_by_elem_output_offsets.front() =
                        _this_t::ILLEGAL_OUTPUT_BUFFER_OFFSET;

                    conf = ::NS(ElemByElemConfig_preset)(
                        this->elem_by_elem_config() );
                }
                else
                {
                    SIXTRL_ASSERT( this->m_until_turn_elem_by_elem.empty() );
                    SIXTRL_ASSERT( this->m_elem_by_elem_output_offsets.empty() );

                    _this_t::config_id_t const elem_by_elem_config_id =
                        this->config_cxx_buffer().getNumObjects();

                    this->m_elem_by_elem_output_offsets.push_back(
                        _this_t::ILLEGAL_OUTPUT_BUFFER_OFFSET );

                    conf = ::NS(ElemByElemConfig_preset)(
                        ::NS(ElemByElemConfig_new)( this->config_buffer() );
                }

                if( conf != nullptr )
                {
                    SIXTRL_ASSERT( !this->m_until_turn_elem_by_elem.empty() );
                    SIXTRL_ASSERT( !this->m_elem_by_elem_output_offsets.empty() );
                    SIXTRL_ASSERT(  this->m_until_turn_elem_by_elem.front() ==
                                    until_turn_elem_by_elem );
                    SIXTRL_ASSERT(  this->m_elem_by_elem_output_offset.front()
                                    == _this_t::ILLEGAL_OUTPUT_BUFFER_OFFSET );

                    ret = ::NS(ElemByElemConfig_init_detailed)( conf,
                        this->default_elem_by_elem_order(),
                        this->min_particle_id(), this->max_particle_id(),
                        this->min_element_id(),  this->max_element_id(),
                        this->min_initial_turn_id(), max_elem_by_elem_turn_id,
                        this->default_is_elem_by_elem_config_rolling() );
                }
            }
            else if( ret == 0 )
            {
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
        _this_t::c_buffer_t* SIXTRL_RESTRICT beam_elem_buffer,
        _this_t::c_buffer_t* SIXTRL_RESTRICT output_buffer,
        _pindex_t const min_turn_id,
        _this_t::size_type const output_buffer_offset_index )
    {
        bool success = false;

        this->doSetBeamMonitorOutputEnabledFlag( false );

        if( ( output_buffer != nullptr ) && ( beam_elem_buffer != nullptr ) &&
            ( this->numBeamMonitors() > _this_t::size_type{ 0 } ) &&
            ( min_turn_id >= _pindex_t{ 0 } ) &&
            ( ::NS(Buffer_get_num_of_objects)( output_buffer ) >
              output_buffer_offset_index ) )
        {
            if( !this->debugMode() )
            {
                success = ( st::ARCH_STATUS_SUCCESS ==
                    ::NS(BeamMonitor_assign_output_buffer_from_offset)(
                        beam_elem_buffer, output_buffer, min_turn_id,
                            output_buffer_offset_index ) );
            }
            else
            {
                st::arch_debugging_t status_flags =
                    st::ARCH_DEBUGGING_GENERAL_FAILURE;

                SIXTRL_ASSERT( ::NS(Buffer_get_slot_size)( output_buffer ) ==
                    ::NS(Buffer_get_slot_size)( beam_elem_buffer ) );

                success = ( st::ARCH_STATUS_SUCCESS ==
                    NS(BeamMonitor_assign_output_buffer_from_offset_debug)(
                        beam_elem_buffer, output_buffer, min_turn_id,
                            output_buffer_offset_index, &status_flags ) );

                if( success )
                {
                    success = ( st::ARCH_STATUS_SUCCESS ==
                        ::NS(DebugReg_get_stored_arch_status)( status_flags ) );
                }
            }

            if( success )
            {
                this->doSetBeamMonitorOutputEnabledFlag( true );
            }
        }

        return success;
    }

    bool TrackJobBase::doAssignOutputBufferToElemByElemConfig(
        _this_t::elem_by_elem_config_t* SIXTRL_RESTRICT elem_by_elem_config,
        _this_t::c_buffer_t* SIXTRL_RESTRICT output_buffer,
        _this_t::size_type const output_buffer_offset_index )
    {
        bool success = false;

        if( ( elem_by_elem_config != nullptr ) && ( output_buffer != nullptr ) &&
            ( ::NS(Buffer_get_num_of_objects)( output_buffer ) >
                output_buffer_offset_index ) )
        {
            this->doSetElemByElemOutputEnabledFlag( false );

            if( this->debugMode() )
            {
                success = ( st::ARCH_STATUS_SUCCESS ==
                    ::NS(ElemByElemConfig_assign_output_buffer)(
                        elem_by_elem_config, output_buffer,
                            output_buffer_offset_index ) );
            }
            else
            {
                st::arch_debugging_t status_flags =
                    st::ARCH_DEBUGGING_GENERAL_FAILURE;

                success = ( st::ARCH_STATUS_SUCCESS ==
                    ::NS(ElemByElemConfig_assign_output_buffer_debug)(
                        elem_by_elem_config, output_buffer,
                            output_buffer_offset_index, &status_flags ) );

                if( success )
                {
                    success = ( st::ARCH_STATUS_SUCCESS ==
                        ::NS(DebugReg_get_stored_arch_status)( status_flags ) );
                }
            }

            if( success )
            {
                this->doSetElemByElemOutputEnabledFlag( true );
            }
        }

        return success;
    }

    bool TrackJobBase::doReset(
        _this_t::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        _this_t::c_buffer_t* SIXTRL_RESTRICT beam_elem_buffer,
        _this_t::c_buffer_t* SIXTRL_RESTRICT output_buffer,
        _size_t const until_turn_elem_by_elem )
    {
        using output_buffer_flag_t = _this_t::output_buffer_flag_t;

        bool success = this->doPrepareParticlesStructures( particles_buffer );

        if( success )
        {
            success = this->doPrepareBeamElementsStructures( beam_elem_buffer );
        }

        if( success )
        {
            this->doSetPtrCParticleBuffer( particles_buffer );
            this->doSetPtrCBeamElementsBuffer( beam_elem_buffer );

            output_buffer_flag_t const out_buffer_flags =
            ::NS(OutputBuffer_required_for_tracking_of_particle_sets)(
                particles_buffer, this->num_particle_sets(),
                    this->particle_set_indices_begin(), beam_elem_buffer,
                        until_turn_elem_by_elem );

            bool const requires_output_buffer =
                ::NS(OutputBuffer_requires_output_buffer)( out_buffer_flags );

            if( requires_output_buffer )
            {
                success = this->doPrepareOutputStructures( particles_buffer,
                    beam_elem_buffer, output_buffer, until_turn_elem_by_elem );
            }

            if( ( success ) && ( this->has_output_buffer() ) &&
                ( requires_output_buffer ) )
            {
                if( ::NS(OutputBuffer_requires_elem_by_elem_output)(
                        out_buffer_flags ) )
                {
                    success = this->doAssignOutputBufferToElemByElemConfig(
                        this->ptrElemByElemConfig(), this->output_buffer(),
                            this->elemByElemOutputBufferOffset() );
                }

                if( ( success ) &&
                    ( ::NS(OutputBuffer_requires_beam_monitor_output)(
                        out_buffer_flags ) ) )
                {
                    success = this->doAssignOutputBufferToBeamMonitors(
                        beam_elem_buffer, this->output_buffer(),
                        this->min_initial_turn_id(),
                        this->beamMonitorsOutputBufferOffset() );
                }
            }

            if( ( success ) && ( output_buffer != nullptr ) &&
                ( !this->has_output_buffer() ) )
            {
                this->doSetPtrCOutputBuffer( output_buffer );
            }
        }

        return success;
    }

    bool TrackJobBase::doAssignNewOutputBuffer(
        _this_t::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer )
    {
        bool success = false;
        using flags_t = _this_t::output_buffer_flag_t;

        flags_t const flags =
        ::NS(OutputBuffer_required_for_tracking_of_particle_sets)(
            this->particles_buffer(), this->num_particle_sets(),
                this->particle_set_indices_begin(),
                this->beam_elements_buffer(), this->numElemByElemTurns() );

        bool const requires_output_buffer =
            ::NS(OutputBuffer_requires_output_buffer)( flags );

        if( requires_output_buffer )
        {
            success = this->doPrepareOutputStructures(
                this->particles_buffer(), this->beam_elements_buffer(),
                ptr_output_buffer, this->numElemByElemTurns() );
        }

        if( ( success ) && ( requires_output_buffer ) &&
            ( this->has_output_buffer() ) )
        {
            if( ( ::NS(OutputBuffer_requires_beam_monitor_output)( flags ) ) &&
                ( this->hasBeamMonitorOutput() ) )
            {
                success = this->doAssignOutputBufferToBeamMonitors(
                    this->beam_elements_buffer(), this->output_buffer(),
                    this->min_initial_turn_id(),
                    this->beamMonitorsOutputBufferOffset() );
            }

            if( ( success ) &&
                ( ::NS(OutputBuffer_requires_elem_by_elem_output)( flags ) ) &&
                ( this->hasElemByElemOutput() ) )
            {
                success = this->doAssignOutputBufferToElemByElemConfig(
                    this->ptrElemByElemConfig(), this->output_buffer(),
                    this->elemByElemOutputBufferOffset() );
            }
        }

        return success;
    }

    _this_t::size_type TrackJobBase::doAddStoredBuffer(
        _this_t::buffer_store_t&& buffer_store_handle )
    {
        _this_t::size_type buffer_index = st::ARCH_MIN_USER_DEFINED_BUFFER_ID +
            this->m_stored_buffers.size();

        _this_t::c_buffer_t* ptr_cbuffer_null = nullptr;

        if( buffer_store_handle.active() )
        {
            ++this->m_num_stored_buffers;
        }

        this->m_stored_buffers.emplace_back( ptr_cbuffer_null, false );
        this->m_stored_buffers.back() = std::move( buffer_store_handle );

        return buffer_index;
    }

    _this_t::status_t TrackJobBase::doRemoveStoredBuffer(
        _this_t::size_type const buffer_index )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _size_t const min_buffer_id = this->min_stored_buffer_id();
        _size_t const max_buffer_id_plus_one =
            min_buffer_id + this->m_stored_buffers.size();

        if( ( min_buffer_id != st::ARCH_ILLEGAL_BUFFER_ID ) &&
            ( buffer_index != st::ARCH_ILLEGAL_BUFFER_ID ) &&
            ( buffer_index >= min_buffer_id ) &&
            ( buffer_index < max_buffer_id_plus_one ) )
        {
            _size_t const ii = buffer_index - min_buffer_id;

            if( this->m_stored_buffers[ ii ].active() )
            {
                SIXTRL_ASSERT( this->m_num_stored_buffers > _size_t{ 0 } );
                this->m_stored_buffers[ ii ].clear();
                --this->m_num_stored_buffers;
            }

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _this_t::status_t TrackJobBase::doPushStoredBuffer(
        _this_t::size_type const buffer_id )
    {
        _this_t::buffer_store_t const* ptr_stored_buffer =
            this->doGetPtrBufferStore( buffer_id );

        return ( ptr_stored_buffer != nullptr )
            ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    _this_t::status_t TrackJobBase::doCollectStoredBuffer(
        _this_t::size_type const buffer_id )
    {
        _this_t::buffer_store_t const* ptr_stored_buffer =
            this->doGetPtrBufferStore( buffer_id );

        return ( ptr_stored_buffer != nullptr )
            ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    _this_t::status_t TrackJobBase::doAddAssignAddressItem(
        _this_t::assign_item_t const& SIXTRL_RESTRICT_REF assign_item,
        _this_t::size_type* SIXTRL_RESTRICT ptr_item_index )
    {
        using size_t = _this_t::size_type;
        using buffer_t = _this_t::buffer_t;
        using key_t = _this_t::assign_item_key_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        size_t item_index = std::numeric_limits< size_t >::max();

        if( assign_item.valid() )
        {
            key_t const key = key_t{ assign_item.getDestBufferId(),
                                     assign_item.getSrcBufferId() };

            auto it = this->m_assign_address_items.find( key );

            if( it == this->m_assign_address_items.end() )
            {
                auto cmp_key_fn = []( key_t const& SIXTRL_RESTRICT_REF lhs,
                                      key_t const& SIXTRL_RESTRICT_REF rhs )
                {
                    return ( ( lhs.dest_buffer_id < rhs.dest_buffer_id ) ||
                             ( ( lhs.dest_buffer_id == rhs.dest_buffer_id ) &&
                               ( lhs.src_buffer_id < rhs.src_buffer_id ) ) );
                };

                SIXTRL_ASSERT( std::is_sorted( this->m_assign_item_keys.begin(),
                    this->m_assign_item_keys.end(), cmp_key_fn ) );

                SIXTRL_ASSERT( !std::binary_search(
                    this->m_assign_item_keys.begin(),
                    this->m_assign_item_keys.end(), key, cmp_key_fn ) );

                SIXTRL_ASSERT( this->m_assign_address_items.size() ==
                               this->m_assign_item_keys.size() );

                bool const keys_need_sorting = !(
                    ( this->m_assign_item_keys.empty() ) ||
                    ( cmp_key_fn( this->m_assign_item_keys.back(), key ) ) );

                this->m_assign_item_keys.push_back( key );

                if( keys_need_sorting )
                {
                    std::sort( this->m_assign_item_keys.begin(),
                               this->m_assign_item_keys.end(), cmp_key_fn );
                }

                buffer_t buffer;

                auto ret = this->m_assign_address_items.emplace(
                    std::make_pair( key, std::move( buffer ) ) );

                if( ret.second )
                {
                    buffer_t& buffer = ret.first->second;
                    SIXTRL_ASSERT( buffer.getNumObjects() == size_t{ 0 } );

                    item_index = buffer.getNumObjects();

                    ::NS(AssignAddressItem)* item =
                        ::NS(AssignAddressItem_add_copy)( buffer.getCApiPtr(),
                            assign_item.getCApiPtr() );

                    if( ( item != nullptr ) &&
                        ( buffer.getNumObjects() > item_index ) )
                    {
                        status = st::ARCH_STATUS_SUCCESS;
                    }
                }
            }
            else
            {
                item_index = this->doFindAssingAddressItem( assign_item );

                if( item_index < it->second.getNumObjects() )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
                else
                {
                    item_index = it->second.getNumObjects();

                    ::NS(AssignAddressItem)* item =
                        ::NS(AssignAddressItem_add_copy)(
                            it->second.getCApiPtr(), assign_item.getCApiPtr() );

                    if( ( item != nullptr ) &&
                        ( item_index < it->second.getNumObjects() ) )
                    {
                        status = st::ARCH_STATUS_SUCCESS;
                    }
                }
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( ptr_item_index != nullptr ) )
            {
                *ptr_item_index = item_index;
            }
        }

        return status;
    }

    _this_t::status_t TrackJobBase::doRemoveAssignAddressItem(
        _this_t::assign_item_key_t const& SIXTRL_RESTRICT_REF key,
        _this_t::size_type const index_of_item_to_remove )
    {
        using size_t = _this_t::size_type;
        using item_t = _this_t::assign_item_t;
        using key_t  = _this_t::assign_item_key_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        auto it = this->m_assign_address_items.find( key );

        auto cmp_key_fn = []( key_t const& SIXTRL_RESTRICT_REF lhs,
                              key_t const& SIXTRL_RESTRICT_REF rhs )
        {
            return ( ( lhs.dest_buffer_id < rhs.dest_buffer_id ) ||
                     ( ( lhs.dest_buffer_id == rhs.dest_buffer_id ) &&
                       ( lhs.src_buffer_id < rhs.src_buffer_id ) ) );
        };

        SIXTRL_ASSERT( std::is_sorted( this->m_assign_item_keys.begin(),
                this->m_assign_item_keys.end(), cmp_key_fn ) );

        if( ( it != this->m_assign_address_items.end() ) &&
            ( it->second.getNumObjects() > index_of_item_to_remove ) )
        {
            buffer_t& current_buffer = it->second;
            buffer_t new_buffer( current_buffer.getNumObjects(),
                                 current_buffer.getNumSlots(),
                                 current_buffer.getNumDataptrs(),
                                 current_buffer.getNumGarbageRanges(),
                                 current_buffer.getFlags() );

            size_t const nn = current_buffer.getNumObjects();
            status = st::ARCH_STATUS_SUCCESS;

            SIXTRL_ASSERT( std::binary_search( this->m_assign_item_keys.begin(),
                this->m_assign_item_keys.end(), key, cmp_key_fn ) );

            SIXTRL_ASSERT( this->m_assign_address_items.size() ==
                           this->m_assign_item_keys.size() );

            for( size_t ii = size_t{ 0 } ; ii < nn ; ++ii )
            {
                if( ii == index_of_item_to_remove ) continue;
                item_t const* in_item = current_buffer.get< item_t >( ii );

                if( in_item == nullptr )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

                ::NS(AssignAddressItem)* copied_item =
                    ::NS(AssignAddressItem_add_copy)(
                        current_buffer.getCApiPtr(), in_item->getCApiPtr() );

                if( copied_item == nullptr )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                using std::swap;
                swap( it->second, new_buffer );
            }
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            it = this->m_assign_address_items.find( key );

            if( it->second.getNumObjects() == size_t{ 0 } )
            {
                this->m_assign_address_items.erase( key );

                auto key_it = std::lower_bound(
                    this->m_assign_item_keys.begin(),
                    this->m_assign_item_keys.end(), key, cmp_key_fn );

                SIXTRL_ASSERT( key_it != this->m_assign_item_keys.end() );
                this->m_assign_item_keys.erase( key_it );
            }
        }

        return status;
    }

    _this_t::status_t TrackJobBase::doPerformAddressAssignments(
        _this_t::assign_item_key_t const& SIXTRL_RESTRICT_REF key )
    {
        using size_t = _this_t::size_type;
        using c_buffer_t = _this_t::c_buffer_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        size_t const dest_buffer_id = key.dest_buffer_id;
        c_buffer_t* dest_buffer = this->buffer_by_buffer_id( dest_buffer_id );

        size_t const src_buffer_id = key.src_buffer_id;
        c_buffer_t const* src_buffer =
            this->buffer_by_buffer_id( src_buffer_id );

        auto it = this->m_assign_address_items.find( key );

        if( ( it != this->m_assign_address_items.end() ) &&
            ( dest_buffer != nullptr ) && ( src_buffer != nullptr ) )
        {
            unsigned char* dest_buffer_begin =
            ::NS(Buffer_get_data_begin)( dest_buffer );

            unsigned char const* src_buffer_begin =
                ::NS(Buffer_get_const_data_begin)( src_buffer );

            size_t const dest_slot_size =
                ( this->is_buffer_by_buffer_id( dest_buffer_id ) )
                    ? ::NS(Buffer_get_slot_size)( dest_buffer ) : size_t{ 0 };

            size_t const src_slot_size =
                ( this->is_buffer_by_buffer_id( src_buffer_id ) )
                    ? ::NS(Buffer_get_slot_size)( src_buffer ) : size_t{ 0 };

            SIXTRL_ASSERT( dest_buffer_begin != nullptr );
            SIXTRL_ASSERT( src_buffer_begin  != nullptr );

            status = ::NS(AssignAddressItem_perform_address_assignment_kernel_impl)(
                it->second.dataBegin< unsigned char const* >(),
                it->second.getSlotSize(), size_t{ 0 }, size_t{ 1 },
                dest_buffer_begin, dest_slot_size, dest_buffer_id,
                src_buffer_begin, src_slot_size, src_buffer_id );
        }

        return status;
    }

    _this_t::status_t TrackJobBase::doRebuildAssignItemsBufferArg()
    {
        return st::ARCH_STATUS_SUCCESS;
    }

    _this_t::status_t TrackJobBase::doCommitAddressAssignments()
    {
        return st::ARCH_STATUS_SUCCESS;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBase::doParseConfigStr(
        const char *const SIXTRL_RESTRICT config_str )
    {
        this->doParseConfigStrBaseImpl( config_str );
    }

    void TrackJobBase::doSetDeviceIdStr(
        const char *const SIXTRL_RESTRICT device_id_str )
    {
        if( device_id_str != nullptr )
        {
            this->m_node_id_str = device_id_str;
        }
        else
        {
            this->m_node_id_str.clear();
        }
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
    }

    void TrackJobBase::doSetPtrParticleBuffer(
        _this_t::buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
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
    }

    void TrackJobBase::doSetPtrCParticleBuffer(
        _this_t::c_buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ( this->m_ptr_particles_buffer   != nullptr ) &&
            ( this->m_ptr_c_particles_buffer ==
              this->m_ptr_particles_buffer->getCApiPtr() ) &&
            ( this->m_ptr_particles_buffer->getCApiPtr() != ptr_buffer ) )
        {
            this->m_ptr_particles_buffer = nullptr;
        }

        this->m_ptr_c_particles_buffer = ptr_buffer;
    }

    void TrackJobBase::doSetPtrBeamElementsBuffer(
        _this_t::buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
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
    }

    void TrackJobBase::doSetPtrCBeamElementsBuffer(
        _this_t::c_buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ( this->m_ptr_beam_elem_buffer != nullptr ) &&
            ( this->m_ptr_c_beam_elem_buffer ==
              this->m_ptr_beam_elem_buffer->getCApiPtr() ) &&
            ( this->m_ptr_beam_elem_buffer->getCApiPtr() != ptr_buffer ) )
        {
            this->m_ptr_beam_elem_buffer = nullptr;
        }

        this->m_ptr_c_beam_elem_buffer = ptr_buffer;
    }

    void TrackJobBase::doSetPtrOutputBuffer(
        _this_t::buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
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
    }

    void TrackJobBase::doSetPtrCOutputBuffer(
        _this_t::c_buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ( this->m_ptr_output_buffer != nullptr ) &&
            ( this->m_ptr_c_output_buffer ==
              this->m_ptr_output_buffer->getCApiPtr() ) &&
            ( this->m_ptr_output_buffer->getCApiPtr() != ptr_buffer ) )
        {
            this->m_ptr_output_buffer = nullptr;
        }

        this->m_ptr_c_output_buffer = ptr_buffer;
    }

    void TrackJobBase::doSetBeamMonitorOutputBufferOffset(
        _size_t const output_buffer_offset ) SIXTRL_NOEXCEPT
    {
        this->m_be_mon_output_buffer_offset = output_buffer_offset;
    }

    void TrackJobBase::doSetUntilTurnElemByElem(
        _pindex_t const
            until_turn_elem_by_elem ) SIXTRL_NOEXCEPT
    {
        this->m_until_turn_elem_by_elem = until_turn_elem_by_elem;
    }

    void TrackJobBase::doSetElemByElemOutputIndexOffset(
        _size_t const elem_by_elem_output_offset ) SIXTRL_NOEXCEPT
    {
        this->m_elem_by_elem_output_offset = elem_by_elem_output_offset;
    }

    void TrackJobBase::doSetRequiresCollectFlag(
        bool const requires_collect_flag ) SIXTRL_NOEXCEPT
    {
        this->m_requires_collect = requires_collect_flag;
    }

    void TrackJobBase::doSetBeamMonitorOutputEnabledFlag(
        bool const has_beam_monitor_output ) SIXTRL_NOEXCEPT
    {
        this->m_has_beam_monitor_output = has_beam_monitor_output;
    }

    void TrackJobBase::doSetElemByElemOutputEnabledFlag(
        bool const elem_by_elem_flag ) SIXTRL_NOEXCEPT
    {
        this->m_has_elem_by_elem_output = elem_by_elem_flag;
    }

    void TrackJobBase::doInitDefaultParticleSetIndices()
    {
        this->m_particle_set_indices.clear();
        this->m_particle_set_indices.push_back( _size_t{ 0 } );

        this->m_num_particles_in_sets.clear();
        this->m_num_particles_in_sets.push_back( _size_t{ 0 } );
    }

    void TrackJobBase::doInitDefaultBeamMonitorIndices()
    {
        this->m_beam_monitor_indices.clear();
    }

    void TrackJobBase::doSetMinParticleId(
        _pindex_t const min_particle_id ) SIXTRL_NOEXCEPT
    {
        this->m_min_particle_id = min_particle_id;
    }

    void TrackJobBase::doSetMaxParticleId(
        _pindex_t const max_particle_id ) SIXTRL_NOEXCEPT
    {
        this->m_max_particle_id = max_particle_id;
    }

    void TrackJobBase::doSetMinElementId(
        _pindex_t const min_element_id ) SIXTRL_NOEXCEPT
    {
        this->m_min_element_id = min_element_id;
    }

    void TrackJobBase::doSetMaxElementId(
        _pindex_t const max_element_id ) SIXTRL_NOEXCEPT
    {
        this->m_max_element_id = max_element_id;
    }

    void TrackJobBase::doSetMinInitialTurnId(
        _pindex_t const min_turn_id ) SIXTRL_NOEXCEPT
    {
        this->m_min_initial_turn_id = min_turn_id;
    }

    void TrackJobBase::doSetMaxInitialTurnId(
        _pindex_t const max_turn_id ) SIXTRL_NOEXCEPT
    {
        this->m_max_initial_turn_id = max_turn_id;
    }

    void TrackJobBase::doUpdateStoredOutputBuffer(
        _this_t::ptr_buffer_t&& ptr_output_buffer ) SIXTRL_NOEXCEPT
    {
        this->doSetPtrOutputBuffer( ptr_output_buffer.get() );
        this->m_my_output_buffer = std::move( ptr_output_buffer );
    }

    void TrackJobBase::doUpdateStoredParticlesAddrBuffer(
        _this_t::ptr_buffer_t&& ptr_particles_addr_buffer ) SIXTRL_NOEXCEPT
    {
        this->m_particles_addr_buffer = std::move( ptr_particles_addr_buffer );
    }

    _this_t::buffer_store_t* TrackJobBase::doGetPtrBufferStore(
        _this_t::size_type const buffer_id ) SIXTRL_NOEXCEPT
    {
        return const_cast< _this_t::buffer_store_t* >( static_cast<
            _this_t const& >( *this ).doGetPtrBufferStore( buffer_id ) );
    }

    _this_t::buffer_store_t const* TrackJobBase::doGetPtrBufferStore(
        _this_t::size_type const buffer_id ) const SIXTRL_NOEXCEPT
    {
        _this_t::buffer_store_t const* ptr_buffer_store = nullptr;

        _size_t const min_buffer_id = this->min_stored_buffer_id();
        _size_t const max_buffer_id_plus_one =
            min_buffer_id + this->m_stored_buffers.size();

        if( ( min_buffer_id != st::ARCH_ILLEGAL_BUFFER_ID ) &&
            ( buffer_id != st::ARCH_ILLEGAL_BUFFER_ID ) &&
            ( buffer_id >= min_buffer_id ) &&
            ( buffer_id <  max_buffer_id_plus_one ) )
        {
            SIXTRL_ASSERT( this->doGetStoredBufferSize() >=
                           this->m_num_stored_buffers );

            ptr_buffer_store = &this->m_stored_buffers[
                buffer_id - min_buffer_id ];
        }

        return ptr_buffer_store;
    }

    _this_t::size_type
    TrackJobBase::doGetStoredBufferSize() const SIXTRL_NOEXCEPT
    {
        return this->m_stored_buffers.size();
    }

    _this_t::size_type TrackJobBase::doFindAssingAddressItem(
        _this_t::assign_item_t const& SIXTRL_RESTRICT_REF
            item_to_search ) const SIXTRL_NOEXCEPT
    {
        using size_t = _this_t::size_type;
        using item_t = _this_t::assign_item_t;
        using key_t  = _this_t::assign_item_key_t;

        size_t index = std::numeric_limits< size_t >::max();

        key_t const key = key_t{ item_to_search.getDestBufferId(),
                                 item_to_search.getSrcBufferId() };

        auto it = this->m_assign_address_items.find( key );

        SIXTRL_ASSERT( this->m_assign_address_items.size() ==
                       this->m_assign_item_keys.size() );

        if( it != this->m_assign_address_items.end() )
        {
            auto cmp_key_fn = []( key_t const& SIXTRL_RESTRICT_REF lhs,
                                  key_t const& SIXTRL_RESTRICT_REF rhs )
            {
                return ( ( lhs.dest_buffer_id < rhs.dest_buffer_id ) ||
                         ( ( lhs.dest_buffer_id == rhs.dest_buffer_id ) &&
                           ( lhs.src_buffer_id < rhs.src_buffer_id ) ) );
            };

            SIXTRL_ASSERT( std::is_sorted( this->m_assign_item_keys.begin(),
                this->m_assign_item_keys.end(), cmp_key_fn ) );

            SIXTRL_ASSERT( std::binary_search( this->m_assign_item_keys.begin(),
                this->m_assign_item_keys.end(), key, cmp_key_fn ) );

            ( void )cmp_key_fn;

            size_t const nn = it->second.getNumObjects();
            ::NS(AssignAddressItem) const* ptr_item_to_search =
                item_to_search.getCApiPtr();

            for( size_t ii = size_t{ 0 } ; ii < nn ; ++ii )
            {
                _this_t::assign_item_t const* item =
                    it->second.get< item_t >( ii );

                if( ( item != nullptr ) &&
                    ( ::NS(AssignAddressItem_are_equal)(
                        item->getCApiPtr(), ptr_item_to_search ) ) )
                {
                    index = ii;
                    break;
                }
            }

            if( index > nn ) index = nn;
        }

        return index;
    }

    _this_t::assign_item_t const* TrackJobBase::doGetAssignAddressItem(
        _this_t::assign_item_key_t const& SIXTRL_RESTRICT_REF key,
        _this_t::size_type const item_index ) const SIXTRL_NOEXCEPT
    {
        using item_t = _this_t::assign_item_t;
        item_t const* ptr_found_item = nullptr;

        auto it = this->m_assign_address_items.find( key );

        if( ( it != this->m_assign_address_items.end() ) &&
            ( it->second.getNumObjects() > item_index ) )
        {
            ptr_found_item = it->second.get< item_t >( item_index );
        }

        return ptr_found_item;
    }

    _this_t::assign_item_t* TrackJobBase::doGetAssignAddressItem(
        _this_t::assign_item_key_t const& SIXTRL_RESTRICT_REF key,
        _this_t::size_type const item_index ) SIXTRL_NOEXCEPT
    {
        using ptr_t = _this_t::assign_item_t*;
        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).doGetAssignAddressItem( key, item_index ) );
    }

    _this_t::c_buffer_t* TrackJobBase::doGetPtrAssignAddressItemsBuffer(
        _this_t::assign_item_key_t const& SIXTRL_RESTRICT_REF
            key ) SIXTRL_NOEXCEPT
    {
        _this_t::c_buffer_t* ptr_assign_address_items_buffer = nullptr;
        auto it = this->m_assign_address_items.find( key );

        if( it != this->m_assign_address_items.end() )
        {
            ptr_assign_address_items_buffer = it->second.getCApiPtr();
        }

        return ptr_assign_address_items_buffer;
    }

    void TrackJobBase::doClearBaseImpl() SIXTRL_NOEXCEPT
    {
        this->doInitDefaultParticleSetIndices();
        this->doInitDefaultBeamMonitorIndices();


        this->m_my_output_buffer.reset( nullptr );
        this->m_stored_buffers.clear();
        this->m_assign_address_items.clear();
        this->m_particles_addr_buffer.reset( nullptr );

        if( this->has_config_buffer() )
        {
            this->config_cxx_buffer().reset();
        }

        this->m_ptr_particles_buffer         = nullptr;
        this->m_ptr_beam_elem_buffer         = nullptr;
        this->m_ptr_output_buffer            = nullptr;

        this->m_ptr_c_particles_buffer       = nullptr;
        this->m_ptr_c_beam_elem_buffer       = nullptr;
        this->m_ptr_c_output_buffer          = nullptr;

        this->m_be_mon_output_buffer_offset  = _size_t{ 0 };
        this->m_elem_by_elem_output_offset   = _size_t{ 0 };
        this->m_default_elem_by_elem_order   = ::NS(ELEM_BY_ELEM_ORDER_DEFAULT);
        this->m_num_stored_buffers           = _size_t{ 0 };

        ::NS(Particles_init_min_max_attributes_for_find)(
            &this->m_min_particle_id, &this->m_max_particle_id,
            &this->m_min_element_id,  &this->m_max_element_id,
            &this->m_min_initial_turn_id,
            &this->m_max_initial_turn_id );

        this->m_until_turn_elem_by_elem      = _size_t{ 0 };

        this->m_default_elem_by_elem_rolling = true;
        this->m_has_beam_monitor_output      = false;
        this->m_has_elem_by_elem_output      = false;
    }

    void TrackJobBase::doParseConfigStrBaseImpl(
        const char *const SIXTRL_RESTRICT config_str )
    {
        ( void )config_str;
    }

    _this_t::status_t TrackJobBase::doPrepareConfigStructuresBaseImpl()
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _this_t::ptr_buffer_t config_buffer_to_store( new buffer_t );

        if( config_buffer_to_store.get() != nullptr )
        {
            this->doUpdateStoredConfigBuffer(
                std::move( config_buffer_to_store ) );

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    void TrackJobBase::doUpdateStoredConfigBuffer(
        _this_t::ptr_buffer_t&& ptr_elem_by_elem_buffer ) SIXTRL_NOEXCEPT
    {
        this->m_my_config_buffer = std::move( ptr_elem_by_elem_buffer );
    }
}

#endif /* defined( __cplusplus ) */
/* end: sixtracklib/common/internal/track_job_base.cpp */
