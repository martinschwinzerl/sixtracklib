#include "sixtracklib/common/buffer/buffer_toc.hpp"

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <map>
#include <numeric>
#include <string>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <utility>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"
#include "sixtracklib/common/internal/stl_buffer_helper.hpp"
#include "sixtracklib/common/buffer.hpp"
#include "sixtracklib/common/buffer.h"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    using _this_t = st::BufferTableOfContents;

    BufferTableOfContents::BufferTableOfContents(
        const _this_t::c_buffer_t *const SIXTRL_RESTRICT buffer ) :
        m_type_indices_map(), m_entry_list(), m_type_id_list()
    {
        if( ( buffer != nullptr ) &&
            ( !::NS(Buffer_needs_remapping)( buffer ) ) &&
            (  ::NS(Buffer_get_num_of_objects)( buffer ) >
                _this_t::size_type{ 0 } ) )
        {
            _this_t::status_t const status = this->doAppendEntriesBaseImpl(
                buffer, ::NS(Buffer_get_num_of_objects)( buffer ) );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }
    }

    BufferTableOfContents::BufferTableOfContents(
        _this_t::buffer_t const& SIXTRL_RESTRICT_REF buffer ) :
        m_type_indices_map(), m_entry_list(), m_type_id_list()
    {
        if( ( !buffer.needsRemapping() ) &&
            ( buffer.getNumObjects() > _this_t::size_type{ 0 } ) )
        {
            _this_t::status_t const status = this->doAppendEntriesBaseImpl(
                buffer.getCApiPtr(), buffer.getNumObjects() );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }
    }

    _this_t::size_type
    BufferTableOfContents::total_num_entries() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_type_indices_map.size() <=
                       this->m_entry_list.size() );

        #if defined( SIXTRL_DEBUG )
        _this_t::size_type calc_num_entries = std::accumulate(
            this->m_type_indices_map.begin(), this->m_type_indices_map.end(),
            _this_t::size_type{ 0 },
            []( _this_t::size_type const prev_sum,
                _this_t::type_indices_map_t::value_type const& value )
                -> _this_t::size_type
            {
                return prev_sum + value.second.size();
            } );

        SIXTRL_ASSERT( calc_num_entries == this->m_entry_list.size() );
        ( void )calc_num_entries;

        #endif /* defined( SIXTRL_DEBUG ) */

        return this->m_entry_list.size();
    }

    _this_t::size_type
    BufferTableOfContents::num_entry_types() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_type_id_list.size() ==
            this->m_type_indices_map.size() );

        SIXTRL_ASSERT( std::is_sorted( this->m_type_id_list.begin(),
            this->m_type_id_list.end() ) );

        SIXTRL_ASSERT( this->m_type_indices_map.size() <=
            this->m_entry_list.size() );

        return this->m_type_indices_map.size();
    }

    _this_t::type_id_t const*
    BufferTableOfContents::entry_types_begin() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_type_indices_map.empty() )
            ? this->m_type_id_list.data() : nullptr;
    }

    _this_t::type_id_t const*
    BufferTableOfContents::entry_types_end() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_type_id_list.size() ==
                       this->m_type_indices_map.size() );

        _this_t::type_id_t const* end_ptr = this->entry_types_begin();

        if( ( !this->m_type_id_list.empty() ) && (  end_ptr != nullptr ) )
        {
            std::advance( end_ptr, this->m_type_id_list.size() );
        }

        return end_ptr;
    }

    bool BufferTableOfContents::has_entries(
        _this_t::type_id_t const type_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( type_id != st::OBJECT_TYPE_INVALID ) &&
            (  st::Map_has_key( this->m_type_indices_map, type_id ) ) &&
            ( !st::Map_ordered_vec_empty(
                this->m_type_indices_map, type_id ) ) );
    }

    _this_t::size_type BufferTableOfContents::num_entries(
        _this_t::type_id_t const type_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( type_id != st::OBJECT_TYPE_INVALID ) &&
            ( st::Map_has_key( this->m_type_indices_map, type_id ) ) )
            ? st::Map_ordered_vec_size( this->m_type_indices_map, type_id )
            : _this_t::size_type{ 0 };
    }

    _this_t::size_type const* BufferTableOfContents::entry_indices_begin(
        _this_t::type_id_t const type_id ) const SIXTRL_NOEXCEPT
    {
        return st::Map_ordered_vec_begin( this->m_type_indices_map, type_id );

    }

    _this_t::size_type const* BufferTableOfContents::entry_indices_end(
        _this_t::type_id_t const type_id ) const SIXTRL_NOEXCEPT
    {
        return st::Map_ordered_vec_end( this->m_type_indices_map, type_id );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    _this_t::size_type BufferTableOfContents::entry_type_index(
        _this_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        _this_t::size_type const type_index = ( this->m_entry_list.size() > nn )
            ? this->m_entry_list[ nn ].m_type_index
            : _this_t::ILLEGAL_ENTRY_INDEX;

        SIXTRL_ASSERT( ( type_index == _this_t::ILLEGAL_ENTRY_INDEX ) ||
            ( ( nn != _this_t::ILLEGAL_ENTRY_INDEX ) &&
              ( type_index <= nn ) && ( nn < this->m_entry_list.size() ) &&
              ( this->m_entry_list[ nn ].m_type_id !=
                st::OBJECT_TYPE_INVALID ) &&
              ( st::Map_ordered_vec_has_value_at_index(
                    this->m_type_indices_map,
                    this->m_entry_list[ nn ].m_type_id,
                    this->m_entry_list[ nn ].m_type_index, nn ) ) ) );

        return type_index;
    }

    _this_t::type_id_t BufferTableOfContents::entry_type_id(
        _this_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        _this_t::type_id_t const type_id = ( this->m_entry_list.size() > nn )
            ? this->m_entry_list[ nn ].m_type_id : st::OBJECT_TYPE_INVALID;

        SIXTRL_ASSERT( ( type_id == st::OBJECT_TYPE_INVALID ) ||
              ( ( nn != _this_t::ILLEGAL_ENTRY_INDEX ) &&
                ( nn < this->m_entry_list.size() ) &&
                ( this->m_entry_list[ nn ].m_type_index !=
                  _this_t::ILLEGAL_ENTRY_INDEX ) &&
                ( st::Map_ordered_vec_has_value_at_index(
                    this->m_type_indices_map,
                    this->m_entry_list[ nn ].m_type_id,
                    this->m_entry_list[ nn ].m_type_index, nn ) ) ) );

        return type_id;
    }

   _this_t::offset_t  BufferTableOfContents::entry_offset(
        _this_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        _this_t::offset_t const offset = ( this->m_entry_list.size() > nn )
            ? this->m_entry_list[ nn ].m_offset : _this_t::ILLEGAL_ENTRY_OFFSET;

        SIXTRL_ASSERT( ( offset == _this_t::ILLEGAL_ENTRY_OFFSET ) ||
              ( ( nn != _this_t::ILLEGAL_ENTRY_INDEX ) &&
                ( nn < this->m_entry_list.size() ) &&
                ( this->m_entry_list[ nn ].m_type_id !=
                    st::OBJECT_TYPE_INVALID ) &&
                ( this->m_entry_list[ nn ].m_type_index !=
                  _this_t::ILLEGAL_ENTRY_INDEX ) &&
                ( st::Map_ordered_vec_has_value_at_index(
                    this->m_type_indices_map,
                    this->m_entry_list[ nn ].m_type_id,
                    this->m_entry_list[ nn ].m_type_index, nn ) ) ) );

        return offset;
    }

    _this_t::size_type BufferTableOfContents::entry_size(
        _this_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        _this_t::size_type const entry_size = ( this->m_entry_list.size() > nn )
            ? this->m_entry_list[ nn ].m_size : _this_t::ILLEGAL_ENTRY_SIZE;

        SIXTRL_ASSERT( ( entry_size == _this_t::ILLEGAL_ENTRY_SIZE ) ||
              ( ( nn != _this_t::ILLEGAL_ENTRY_INDEX ) &&
                ( nn < this->m_entry_list.size() ) &&
                ( this->m_entry_list[ nn ].m_type_id !=
                    st::OBJECT_TYPE_INVALID ) &&
                ( this->m_entry_list[ nn ].m_type_index !=
                  _this_t::ILLEGAL_ENTRY_INDEX ) &&
                ( st::Map_ordered_vec_has_value_at_index(
                    this->m_type_indices_map,
                    this->m_entry_list[ nn ].m_type_id,
                    this->m_entry_list[ nn ].m_type_index, nn ) ) ) );

        return entry_size;
    }

    _this_t::size_type BufferTableOfContents::entry_num_dataptrs(
        _this_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        _this_t::size_type const entry_size = ( this->m_entry_list.size() > nn )
            ? this->m_entry_list[ nn ].m_size : _this_t::ILLEGAL_NUM_DATAPTRS;

        SIXTRL_ASSERT( ( entry_size == _this_t::ILLEGAL_NUM_DATAPTRS ) ||
              ( ( nn != _this_t::ILLEGAL_ENTRY_INDEX ) &&
                ( nn < this->m_entry_list.size() ) &&
                ( this->m_entry_list[ nn ].m_type_id !=
                    st::OBJECT_TYPE_INVALID ) &&
                ( this->m_entry_list[ nn ].m_type_index !=
                  _this_t::ILLEGAL_ENTRY_INDEX ) &&
                ( st::Map_ordered_vec_has_value_at_index(
                    this->m_type_indices_map,
                    this->m_entry_list[ nn ].m_type_id,
                    this->m_entry_list[ nn ].m_type_index, nn ) ) ) );

        return entry_size;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    _this_t::size_type BufferTableOfContents::entry_index(
        _this_t::type_id_t const type_id,
        _this_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        _this_t::size_type entry_index = _this_t::ILLEGAL_ENTRY_INDEX;

        if( ( type_id != st::OBJECT_TYPE_INVALID ) &&
            ( nn != _this_t::ILLEGAL_ENTRY_INDEX ) )
        {
            auto it = this->m_type_indices_map.find( type_id );

            if( ( it != this->m_type_indices_map.end() ) &&
                ( it->second.size() > nn ) )
            {
                entry_index = it->second[ nn ];
            }

            SIXTRL_ASSERT( ( entry_index == _this_t::ILLEGAL_ENTRY_INDEX ) ||
                ( ( st::Map_has_key( this->m_type_indices_map, type_id ) ) &&
                  ( st::Map_ordered_vec_has_value_at_index(
                      this->m_type_indices_map, type_id, nn, entry_index ) ) &&
                  ( this->m_entry_list.size() > entry_index ) &&
                  ( this->m_entry_list[ entry_index ].m_type_id == type_id ) &&
                  ( this->m_entry_list[ entry_index ].m_type_index == nn ) ) );
        }

        return entry_index;
    }

   _this_t::offset_t BufferTableOfContents::entry_offset(
        _this_t::type_id_t const type_id,
        _this_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        return this->entry_offset( this->entry_index( type_id, nn ) );
    }

    _this_t::size_type BufferTableOfContents::entry_size(
        _this_t::type_id_t const type_id,
        _this_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        return this->entry_size( this->entry_index( type_id, nn ) );
    }

    _this_t::size_type BufferTableOfContents::entry_num_dataptrs(
        _this_t::type_id_t const type_id,
        _this_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        return this->entry_num_dataptrs( this->entry_index( type_id, nn ) );
    }

    /* --------------------------------------------------------------------- */

    void BufferTableOfContents::clear()
    {
        this->doClear();
    }

    _this_t::status_t BufferTableOfContents::reset(
        _this_t::buffer_t const& SIXTRL_RESTRICT_REF buffer )
    {
        this->doClear();
        return this->doAppendEntries(
            buffer.getCApiPtr(), buffer.getNumObjects() );
    }

    _this_t::status_t BufferTableOfContents::reset(
        const _this_t::c_buffer_t *const SIXTRL_RESTRICT buffer )
    {
        this->doClear();
        return this->doAppendEntries(
            buffer, ::NS(Buffer_get_num_of_objects)( buffer ) );
    }

    _this_t::status_t BufferTableOfContents::append(
        _this_t::buffer_t const& SIXTRL_RESTRICT_REF buffer,
        _this_t::size_type const num_entries_to_append )
    {
        return this->doAppendEntries(
            buffer.getCApiPtr(), num_entries_to_append );
    }

    _this_t::status_t BufferTableOfContents::append(
        const _this_t::c_buffer_t *const SIXTRL_RESTRICT buffer,
        _this_t::size_type const num_entries_to_append )
    {
        return this->doAppendEntries( buffer, num_entries_to_append );
    }

    /* --------------------------------------------------------------------- */

    bool BufferTableOfContents::has_same_layout(
        _this_t::buffer_t const& SIXTRL_RESTRICT_REF buffer )
    {
        return this->doCheckHasBufferIdenticalLayout( buffer.getCApiPtr(),
            _this_t::size_type{ 0 }, this->m_entry_list.size() );
    }

    bool BufferTableOfContents::has_same_layout(
        const _this_t::c_buffer_t *const SIXTRL_RESTRICT buffer )
    {
        return this->doCheckHasBufferIdenticalLayout( buffer,
            _this_t::size_type{ 0 }, this->m_entry_list.size() );
    }

    void BufferTableOfContents::doClear()
    {
        this->m_type_indices_map.clear();
        this->m_entry_list.clear();
        this->m_type_id_list.clear();
    }

    _this_t::status_t BufferTableOfContents::doAppendEntries(
        const _this_t::c_buffer_t *const SIXTRL_RESTRICT buffer,
        _this_t::size_type const num_entries_to_append )
    {
        return this->doAppendEntriesBaseImpl( buffer, num_entries_to_append );
    }

    _this_t::status_t BufferTableOfContents::doAppendEntriesBaseImpl(
        const _this_t::c_buffer_t *const SIXTRL_RESTRICT buffer,
        _this_t::size_type const num_entries_to_append )
    {
        using size_t    = _this_t::size_type;
        using entry_t   = _this_t::entry_t;
        using offset_t  = _this_t::offset_t;
        using type_id_t = _this_t::type_id_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        size_t const buffer_size = ::NS(Buffer_get_size)( buffer );

        if( ( num_entries_to_append > size_t{ 0 } ) && ( buffer != nullptr ) &&
            ( !::NS(Buffer_needs_remapping)( buffer ) ) &&
            ( buffer_size > size_t{ 0 } ) )
        {
            size_t const n_objects = ::NS(Buffer_get_num_of_objects)( buffer );

            offset_t const buffer_begin =
                ::NS(Buffer_get_data_begin_addr)( buffer );

            offset_t min_next_offset = offset_t{ 0 };
            size_t idx = size_t{ 0 };

            if( !this->m_entry_list.empty() )
            {
                SIXTRL_ASSERT( this->m_entry_list.back().m_type_id !=
                    st::OBJECT_TYPE_INVALID );

                SIXTRL_ASSERT( this->m_entry_list.back().m_type_index !=
                    _this_t::ILLEGAL_ENTRY_INDEX );

                SIXTRL_ASSERT( this->m_entry_list.back().m_num_dataptrs !=
                    _this_t::ILLEGAL_NUM_DATAPTRS );

                if( !this->doCheckHasBufferIdenticalLayout( buffer,
                    size_type{ 0 }, this->m_entry_list.size() ) )
                {
                    return status;
                }

                min_next_offset = this->m_entry_list.back().m_offset +
                    this->m_entry_list.back().m_size;

                idx = this->m_entry_list.size();
            }

            size_t const end_idx = idx + num_entries_to_append;

            if( ( n_objects > size_t{ 0 } ) && ( n_objects >= end_idx ) &&
                ( min_next_offset < buffer_size ) &&
                ( buffer_begin != offset_t{ 0 } ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
                for( ; idx < end_idx ; ++idx )
                {
                    ::NS(Object) const* obj =
                        ::NS(Buffer_get_const_object)( buffer, idx );

                    if( obj == nullptr )
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    type_id_t const type_id = ::NS(Object_get_type_id)( obj );

                    if( type_id != st::OBJECT_TYPE_INVALID )
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    offset_t offset = ::NS(Object_get_begin_addr)( obj );
                    offset_t const length = ::NS(Object_get_size)( obj );

                    if( offset < buffer_begin )
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    offset -= buffer_begin;

                    if( ( min_next_offset > offset ) ||
                        ( ( offset + length ) > buffer_size ) )
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    size_t entry_type_idx = _this_t::ILLEGAL_ENTRY_INDEX;
                    SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );

                    if( st::Map_has_key( this->m_type_indices_map, type_id ) )
                    {
                        SIXTRL_ASSERT( !this->m_type_id_list.empty() );
                        SIXTRL_ASSERT( st::Vector_sorted_has_value(
                            this->m_type_id_list.begin(),
                            this->m_type_id_list.end(), type_id ) );

                        SIXTRL_ASSERT( st::Map_ordered_vec_begin(
                            this->m_type_indices_map, type_id ) != nullptr );

                        entry_type_idx = st::Map_ordered_vec_size(
                            this->m_type_indices_map, type_id );

                        auto it = this->m_type_indices_map.find( type_id );

                        SIXTRL_ASSERT( it != this->m_type_indices_map.end() );
                        SIXTRL_ASSERT( std::is_sorted(
                            it->second.begin(), it->second.end() ) );

                        status = st::Vector_add_sorted( it->second, idx );

                        if( status != st::ARCH_STATUS_SUCCESS )
                        {
                            entry_type_idx = _this_t::ILLEGAL_ENTRY_INDEX;
                        }

                        SIXTRL_ASSERT(
                          ( ( status != st::ARCH_STATUS_SUCCESS ) ||
                            ( entry_type_idx ==
                                _this_t::ILLEGAL_ENTRY_INDEX ) ) &&
                          ( ( status == st::ARCH_STATUS_SUCCESS ) &&
                            ( entry_type_idx > size_t{ 0 } ) ) &&
                            ( entry_type_idx !=
                                _this_t::ILLEGAL_ENTRY_INDEX ) );
                    }
                    else
                    {
                        SIXTRL_ASSERT( ( this->m_type_id_list.empty() ) ||
                            ( !st::Vector_sorted_has_value(
                                this->m_type_id_list.begin(),
                                this->m_type_id_list.end(), type_id ) ) );

                        entry_type_idx = size_type{ 0 };

                        auto ret = this->m_type_indices_map.emplace(
                            std::make_pair( type_id,
                                _this_t::indices_list_t{ entry_type_idx } ) );

                        if( ret.second )
                        {
                            status = st::Vector_add_sorted(
                                this->m_type_id_list, type_id );
                        }
                        else
                        {
                            status = st::ARCH_STATUS_GENERAL_FAILURE;
                        }

                        if( status != st::ARCH_STATUS_SUCCESS )
                        {
                            break;
                        }
                    }

                    if( entry_type_idx != _this_t::ILLEGAL_ENTRY_INDEX )
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    this->m_entry_list.push_back( entry_t{ offset, length,
                        size_t{ 0 }, entry_type_idx, type_id } );
                }
            }
        }

        return status;
    }

    bool BufferTableOfContents::doCheckHasBufferIdenticalLayout(
        const _this_t::c_buffer_t *const SIXTRL_RESTRICT buffer,
        _this_t::size_type const begin_index,
        _this_t::size_type const end_index )
    {
        bool has_identical_layout = false;

        using size_t    = _this_t::size_type;
        using entry_t   = _this_t::entry_t;
        using offset_t  = _this_t::offset_t;
        using type_id_t = _this_t::type_id_t;

        size_t const buffer_size = ::NS(Buffer_get_size)( buffer );
        size_t const n_objects = ::NS(Buffer_get_num_of_objects)( buffer );
        offset_t const buffer_begin = ::NS(Buffer_get_data_begin_addr)( buffer );

        if( ( buffer != nullptr ) && ( begin_index < end_index ) &&
            ( end_index <= n_objects ) && ( buffer_size > size_t{ 0 } ) &&
            ( this->m_entry_list.size() >= end_index ) &&
            ( !::NS(Buffer_needs_remapping)( buffer ) ) )
        {
            has_identical_layout = true;

            for( size_t ii = begin_index ; ii < end_index ; ++ii )
            {
                ::NS(Object) const* obj =
                    ::NS(Buffer_get_const_object)( buffer, ii );

                if( obj == nullptr )
                {
                    has_identical_layout = false;
                    break;
                }

                type_id_t const type_id = ::NS(Object_get_type_id)( obj );

                if( type_id != st::OBJECT_TYPE_INVALID )
                {
                    has_identical_layout = false;
                    break;
                }

                size_t const length = ::NS(Object_get_size)( obj );
                offset_t offset = ::NS(Object_get_begin_addr)( obj );

                if( offset < buffer_begin )
                {
                    has_identical_layout = false;
                    break;
                }

                offset -= buffer_begin;
                entry_t const& entry = this->m_entry_list[ ii ];

                if( ( type_id != entry.m_type_id ) ||
                    ( offset  != entry.m_offset  ) ||
                    ( length  != entry.m_size    ) ||
                    ( entry.m_type_index > ii  ) )
                {
                    has_identical_layout = false;
                    break;
                }

                auto it = this->m_type_indices_map.find( type_id );

                if( ( it != this->m_type_indices_map.end() ) ||
                    ( it->second.empty() ) ||
                    ( it->second.size() <= entry.m_type_index ) ||
                    ( it->second[ entry.m_type_index ] != ii ) )
                {
                    has_identical_layout = false;
                    break;
                }
            }
        }

        return has_identical_layout;
    }
}

/* end: sixtracklib/common/buffer/buffer_toc.cpp */
