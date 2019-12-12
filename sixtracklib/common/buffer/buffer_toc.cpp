#include "sixtracklib/common/buffer/buffer_toc.hpp"

#if defined( __cplusplus ) && !defined( _GPUCODE )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <cstddef>
    #include <cstdint>
    #include <cstdlib>
    #include <map>
    #include <type_traits>
    #include <unordered_map>
    #include <utility>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer.hpp"
    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/internal/stl_buffer_helper.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    using _this_t = st::BufferToc;

    constexpr _this_t::size_type _this_t::ILLEGAL_ELEMENT_ID;

    BufferToc::BufferToc( _this_t::buffer_t const SIXTRL_RESTRICT_REF buffer ):
        m_type_ids_to_indices_map(), m_stored_type_ids()
    {
        _this_t::status_t const status =
            this->doResetBaseImpl( buffer.getCApiPtr() );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
    }

    BufferToc::BufferToc(
        const _this_t::c_buffer_t *const SIXTRL_RESTRICT buffer )
    {
        if( buffer != nullptr )
        {
            _this_t::status_t const status = this->doResetBaseImpl( buffer );
            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        }
    }

    /* ----------------------------------------------------------------- */

    bool BufferToc::has_types() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_stored_type_ids.size() ==
                       this->m_type_ids_to_indices_map.size() );

        return !this->m_stored_type_ids.empty();
    }

    _this_t::size_type BufferToc::num_types() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_stored_type_ids.size() ==
                       this->m_type_ids_to_indices_map.size() );

        return this->m_stored_type_ids.size();
    }

    _this_t::type_id_t const* BufferToc::types_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_stored_type_ids.size() ==
                       this->m_type_ids_to_indices_map.size() );

        return ( !this->m_stored_type_ids.empty() )
            ? this->m_stored_type_ids.data() : nullptr;
    }

    _this_t::type_id_t const* BufferToc::types_end() const SIXTRL_NOEXCEPT
    {
        _this_t::type_id_t const* ptr_end = this->types_begin();

        if( ptr_end != nullptr )
            std::advance( ptr_end, this->m_stored_type_ids.size() );

        return ptr_end;
    }

    _this_t::size_type BufferToc::total_num_elements() const SIXTRL_NOEXCEPT
    {
        return st::Map_ordered_vec_total_num_values(
            this->m_type_ids_to_indices_map );
    }

    /* ----------------------------------------------------------------- */

    bool BufferToc::has_type_elements(
        _this_t::type_id_t const type_id ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_stored_type_ids.size() ==
                       this->m_type_ids_to_indices_map.size() );

        return st::Vector_sorted_has_value( this->m_stored_type_ids.begin(),
            this->m_stored_type_ids.end(), type_id );
    }

    _this_t::size_type BufferToc::num_type_elements(
        _this_t::type_id_t const type_id ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_stored_type_ids.size() ==
                       this->m_type_ids_to_indices_map.size() );

        return st::Map_ordered_vec_size(
            this->m_type_ids_to_indices_map,  type_id );
    }

    _this_t::size_type const* BufferToc::type_elements_indices_begin(
        _this_t::type_id_t const type_id ) const SIXTRL_NOEXCEPT
    {
        return st::Map_ordered_vec_begin(
            this->m_type_ids_to_indices_map, type_id );
    }

    _this_t::size_type const* BufferToc::type_elements_indices_end(
        _this_t::type_id_t const type_id ) const SIXTRL_NOEXCEPT
    {
        return st::Map_ordered_vec_end(
            this->m_type_ids_to_indices_map, type_id );
    }

    _this_t::size_type BufferToc::type_element_index(
        _this_t::type_id_t const type_id, size_type const id ) const
    {
        auto it = this->m_type_ids_to_indices_map.find( type_id );

        if( it != this->m_type_ids_to_indices_map.end() )
        {
            return it->second.at( id );
        }

        return _this_t::ILLEGAL_ELEMENT_ID;
    }

    _this_t::size_type BufferToc::type_element_index_no_check(
        _this_t::type_id_t const type_id,
        _this_t::size_type const id ) const SIXTRL_NOEXCEPT
    {
        auto it = this->m_type_ids_to_indices_map.find( type_id );

        if( ( it != this->m_type_ids_to_indices_map.end() ) &&
            ( it->second.size() > id ) )
        {
            return it->second[ id ];
        }

        return _this_t::ILLEGAL_ELEMENT_ID;
    }

    /* ----------------------------------------------------------------- */

    _this_t::status_t BufferToc::reset(
        _this_t::buffer_t const& SIXTRL_RESTRICT_REF buffer )
    {
        return this->doReset( buffer.getCApiPtr() );
    }

    _this_t::status_t BufferToc::reset(
        const _this_t::c_buffer_t *const SIXTRL_RESTRICT buffer )
    {
        return this->doReset( buffer );
    }

    void BufferToc::clear()
    {
        return this->doClear();
    }

    /* ----------------------------------------------------------------- */

    bool operator==(
        st::BufferToc const& SIXTRL_RESTRICT_REF lhs,
        st::BufferToc const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
    {
        bool are_equal = std::equal( lhs.m_stored_type_ids.begin(),
            lhs.m_stored_type_ids.end(), rhs.m_stored_type_ids.begin() );

        if( are_equal )
        {
            if( &lhs != &rhs )
            {
                auto lhs_it  = lhs.m_type_ids_to_indices_map.begin();
                auto lhs_end = lhs.m_type_ids_to_indices_map.end();
                auto rhs_it  = rhs.m_type_ids_to_indices_map.begin();

                for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
                {
                    if( ( lhs_it->first != rhs_it->first ) ||
                        ( !std::equal( lhs_it->second.begin(),
                            lhs_it->second.end(), rhs_it->second.begin() ) ) )
                    {
                        are_equal = false;
                        break;
                    }
                }
            }
        }

        return are_equal;
    }

    bool operator!=(
        st::BufferToc const& SIXTRL_RESTRICT_REF lhs,
        st::BufferToc const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        return !( lhs != rhs );
    }

    void BufferToc::doClear()
    {
        this->doClearBaseImpl();
    }

    _this_t::status_t BufferToc::doReset(
        const _this_t::c_buffer_t *const SIXTRL_RESTRICT buffer )
    {
        return this->doResetBaseImpl( buffer );
    }

    void BufferToc::doClearBaseImpl() SIXTRL_NOEXCEPT
    {
        this->m_stored_type_ids.clear();
        this->m_type_ids_to_indices_map.clear();
    }

    _this_t::status_t BufferToc::doResetBaseImpl(
        const _this_t::c_buffer_t *const SIXTRL_RESTRICT buffer )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        this->m_stored_type_ids.clear();
        this->m_type_ids_to_indices_map.clear();

        if( buffer != nullptr )
        {
            _this_t::size_type const num_elements =
                ::NS(Buffer_get_num_of_objects)( buffer );

            status = st::ARCH_STATUS_SUCCESS;

            if( num_elements > _this_t::size_type{ 0 } )
            {
                _this_t::size_type ii = _this_t::size_type{ 0 };

                ::NS(Object) const* obj_it  =
                    ::NS(Buffer_get_const_object_begin)( buffer );

                ::NS(Object) const* obj_end =
                    ::NS(Buffer_get_const_object_end)( buffer );

                SIXTRL_ASSERT( obj_it != nullptr );

                for( ; obj_it != obj_end ; ++obj_end, ++ii )
                {
                    _this_t::type_id_t const type_id =
                        ::NS(Object_get_type_id)( obj_it );

                    auto it = this->m_type_ids_to_indices_map.find( type_id );

                    if( it != this->m_type_ids_to_indices_map.end() )
                    {
                        SIXTRL_ASSERT( st::Vector_sorted_has_value(
                            this->m_stored_type_ids.begin(),
                            this->m_stored_type_ids.end(), type_id ) );

                        SIXTRL_ASSERT( st::Map_has_key(
                            this->m_type_ids_to_indices_map, type_id ) );

                        SIXTRL_ASSERT( !st::Map_ordered_vec_empty(
                            this->m_type_ids_to_indices_map, type_id ) );

                        SIXTRL_ASSERT( !st::Map_ordered_vec_has_value(
                            this->m_type_ids_to_indices_map, type_id, ii ) );

                        status = st::Map_ordered_vec_insert_value(
                            this->m_type_ids_to_indices_map, type_id, ii,
                                _this_t::size_type{ 0 }, true );
                    }
                    else
                    {
                        SIXTRL_ASSERT( !st::Vector_sorted_has_value(
                            this->m_stored_type_ids.begin(),
                            this->m_stored_type_ids.end(), type_id ) );

                        SIXTRL_ASSERT( !st::Map_has_key(
                            this->m_type_ids_to_indices_map, type_id ) );

                        status = st::Vector_add_sorted(
                            this->m_stored_type_ids, type_id,
                                _this_t::type_id_t{ 0 }, true );

                        if( status == st::ARCH_STATUS_SUCCESS )
                        {
                            auto ret = this->m_type_ids_to_indices_map.emplace(
                                std::make_pair( type_id,
                                    _this_t::indices_list_t{ ii } ) );

                            if( !ret.second )
                            {
                                status = st::ARCH_STATUS_GENERAL_FAILURE;
                            }
                        }
                    }

                    if( status != st::ARCH_STATUS_SUCCESS ) break;
                }
            }
        }

        return status;
    }

    /* ********************************************************************* */

    constexpr OutputOffsetBufferToc::size_type
        OutputOffsetBufferToc::ILLEGAL_OUTPUT_OFFSET;

    OutputOffsetBufferToc::OutputOffsetBufferToc(
        OutputOffsetBufferToc::buffer_t const SIXTRL_RESTRICT_REF buffer ) :
        BufferToc( buffer ), m_type_id_to_output_offsets_map()
    {

    }

    OutputOffsetBufferToc::OutputOffsetBufferToc(
        const OutputOffsetBufferToc::c_buffer_t *const SIXTRL_RESTRICT buffer ) :
        BufferToc( buffer ), m_type_id_to_output_offsets_map()
    {

    }


    bool OutputOffsetBufferToc::has_output_offset(
        OutputOffsetBufferToc::type_id_t const type_id ) const SIXTRL_NOEXCEPT
    {
        return st::Map_has_key(
            this->m_type_id_to_output_offsets_map, type_id );
    }

    OutputOffsetBufferToc::status_t OutputOffsetBufferToc::enable_output_offset(
        OutputOffsetBufferToc::type_id_t const type_id ) SIXTRL_NOEXCEPT
    {
        using _out_toc_t = st::OutputOffsetBufferToc;
        _out_toc_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        auto it = this->m_type_id_to_output_offsets_map.find( type_id );
        if( it == this->m_type_id_to_output_offsets_map.end() )
        {
            auto ret = this->m_type_id_to_output_offsets_map.emplace(
                std::make_pair( type_id, _this_t::output_offset_list_t{} ) );

            if( ret.second )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }
        else
        {
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    OutputOffsetBufferToc::status_t
    OutputOffsetBufferToc::disable_output_offset(
        OutputOffsetBufferToc::type_id_t const type_id ) SIXTRL_NOEXCEPT
    {
        OutputOffsetBufferToc::status_t status =
            st::ARCH_STATUS_GENERAL_FAILURE;

        auto it = this->m_type_id_to_output_offsets_map.find( type_id );
        if( it != this->m_type_id_to_output_offsets_map.end() )
        {
            it->second.clear();
            this->m_type_id_to_output_offsets_map.erase( it );
            it = this->m_type_id_to_output_offsets_map.end();
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    OutputOffsetBufferToc::size_type
    OutputOffsetBufferToc::num_output_offsets(
        OutputOffsetBufferToc::type_id_t const type_id ) const SIXTRL_NOEXCEPT
    {
        return st::Map_ordered_vec_size( this->m_type_id_to_output_offsets_map,
            type_id );
    }

    OutputOffsetBufferToc::size_type const*
    OutputOffsetBufferToc::output_offsets_begin(
        OutputOffsetBufferToc::type_id_t const type_id ) const SIXTRL_NOEXCEPT
    {
        return st::Map_ordered_vec_begin( this->m_type_id_to_output_offsets_map,
            type_id );
    }

    OutputOffsetBufferToc::size_type const*
    OutputOffsetBufferToc::output_offsets_end(
        OutputOffsetBufferToc::type_id_t const type_id ) const SIXTRL_NOEXCEPT
    {
        return st::Map_ordered_vec_end( this->m_type_id_to_output_offsets_map,
            type_id );
    }

    OutputOffsetBufferToc::size_type OutputOffsetBufferToc::output_offset(
        OutputOffsetBufferToc::type_id_t const type_id,
        OutputOffsetBufferToc::size_type const index ) const SIXTRL_NOEXCEPT
    {
        auto it = this->m_type_id_to_output_offsets_map.find( type_id );

        if( ( it != this->m_type_id_to_output_offsets_map.end() ) &&
            ( it->second.size() > index ) )
        {
            return it->second[ index ];
        }

        return OutputOffsetBufferToc::ILLEGAL_OUTPUT_OFFSET;
    }

    OutputOffsetBufferToc::size_type BufferToc::output_offset_by_buffer_index(
        OutputOffsetBufferToc::type_id_t const type_id,
        OutputOffsetBufferToc::size_type const buffer_index
        ) const SIXTRL_NOEXCEPT
    {
        auto buffer_idx_begin = this->type_elements_indices_begin( type_id );
        auto buffer_idx_end   = this->type_elements_indices_end( type_id );

        if( ( buffer_idx_begin != nullptr ) && ( buffer_idx_end != nullptr ) &&
            ( this->has_output_offset( type_id ) ) )
        {
            SIXTRL_ASSERT( reinterpret_cast< uintptr_t >( buffer_idx_begin ) <=
                           reinterpret_cast< uintptr_t >( buffer_idx_end ) );

            SIXTRL_ASSERT( std::is_sorted( buffer_idx_begin, buffer_idx_end ) );

            auto idx_it = std::lower_bound( buffer_idx_begin, buffer_idx_end,
                buffer_index );

            if( idx_it != buffer_idx_end )
            {
                std::ptrdiff_t const diff = std::distance(
                    buffer_idx_begin, idx_it );
                SIXTRL_ASSERT( diff >= std::ptrdiff_t{ 0 } );

                return this->output_offset(
                    type_id, static_cast< size_type >( diff ) );
            }
        }

        return OutputOffsetBufferToc::ILLEGAL_OUTPUT_OFFSET;
    }

    OutputOffsetBufferToc::status_t OutputOffsetBufferToc::set_output_offset(
        OutputOffsetBufferToc::type_id_t const type_id,
        OutputOffsetBufferToc::size_type const index,
        OutputOffsetBufferToc::size_type const output_offset ) SIXTRL_NOEXCEPT
    {
        OutputOffsetBufferToc::status_t status =
            st::ARCH_STATUS_GENERAL_FAILURE;

        auto it = this->m_type_id_to_output_offsets_map.find( type_id );

        if( ( it != this->m_type_id_to_output_offsets_map.end() ) &&
            ( it->second.size() > index ) )
        {
            it->second[ index ] = output_offset;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    OutputOffsetBufferToc::status_t
    OutputOffsetBufferToc::set_output_offset_by_buffer_index(
        OutputOffsetBufferToc::type_id_t const type_id,
        OutputOffsetBufferToc::size_type const buffer_index,
        OutputOffsetBufferToc::size_type const output_offset ) SIXTRL_NOEXCEPT
    {
        OutputOffsetBufferToc::status_t status =
            st::ARCH_STATUS_GENERAL_FAILURE;

        auto buffer_idx_begin = this->type_elements_indices_begin( type_id );
        auto buffer_idx_end   = this->type_elements_indices_end( type_id );

        if( ( buffer_idx_begin != nullptr ) && ( buffer_idx_end != nullptr ) &&
            ( this->has_output_offset( type_id ) ) )
        {
            SIXTRL_ASSERT( reinterpret_cast< uintptr_t >( buffer_idx_begin ) <=
                           reinterpret_cast< uintptr_t >( buffer_idx_end ) );

            SIXTRL_ASSERT( std::is_sorted( buffer_idx_begin, buffer_idx_end ) );

            auto idx_it = std::lower_bound( buffer_idx_begin, buffer_idx_end,
                buffer_index );

            if( idx_it != buffer_idx_end )
            {
                std::ptrdiff_t const diff = std::distance(
                    buffer_idx_begin, idx_it );
                SIXTRL_ASSERT( diff >= std::ptrdiff_t{ 0 } );

                status = this->set_output_offset( type_id,
                    static_cast< size_type >( diff ), offset );
            }
        }

        return status;
    }

    OutputOffsetBufferToc::status_t OutputOffsetBufferToc::doReset(
        const OutputOffsetBufferToc::c_buffer_t *const SIXTRL_RESTRICT buffer )
    {
        OutputOffsetBufferToc::status_t status = _this_t::doReset( buffer );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            auto it  = this->m_type_id_to_output_offsets_map.begin();
            auto end = this->m_type_id_to_output_offsets_map.end();

            for( ; it != end ; ++it )
            {
                auto out_it =
                    this->m_type_id_to_output_offsets_map.find( it->first );

                if( out_it != this->m_type_id_to_output_offsets_map.end() )
                {
                    if( !it->second.empty() )
                    {
                        out_it->second.resize( it->second.size(),
                            OutputOffsetBufferToc::ILLEGAL_OUTPUT_OFFSET );
                    }
                    else
                    {
                        out_it->second.clear();
                    }
                }
            }
        }

        return status;
    }

    void OutputOffsetBufferToc::doClear()
    {
        _this_t::doClear();

        auto it  = this->m_type_id_to_output_offsets_map.begin();
        auto end = this->m_type_id_to_output_offsets_map.end();

        for( ; it != end ; ++it )
        {
           it->second.clear();
        }
    }

    bool operator==(
        st::OutputOffsetBufferToc const& SIXTRL_RESTRICT_REF lhs,
        st::OutputOffsetBufferToc const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT
    {
        _this_t const& lhs_base = static_cast< _this_t const& >( lhs );
        _this_t const& rhs_base = static_cast< _this_t const& >( rhs );

        bool is_equal = (
            ( lhs_base == rhs_base ) &&
            ( lhs.m_type_id_to_output_offsets_map.size() ==
              rhs.m_type_id_to_output_offsets_map.size() ) );

        if( ( is_equal ) &&
        {
            auto lhs_it  = lhs.m_type_id_to_output_offsets_map.begin();
            auto lhs_end = lhs.m_type_id_to_output_offsets_map.end();

            auto rhs_it  = rhs.m_type_id_to_output_offsets_map.begin();

            for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
            {
                if( ( lhs_it->first != rhs_it->first ) ||
                    ( lhs_it->second.size() != rhs_it->second.size() ) )
                {
                    is_equal = false;
                    break;
                }

                if( !std::equal( lhs_it->second.begin(), lhs_it->second.end(),
                                 rhs_it->second.begin() ) )
                {
                    is_equal = false;
                    break;
                }
            }
        }

        return is_equal;
    }

    bool operator!=(
        st::OutputOffsetBufferToc const& SIXTRL_RESTRICT_REF lhs,
        st::OutputOffsetBufferToc const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT
    {
        return ( lhs != rhs );
    }

    /* ********************************************************************* */

    SIXTRL_HOST_FN ParticleSetsBufferToc::ParticleSetsBufferToc(
        ParticleSetsBufferToc::buffer_t const& SIXTRL_RESTRICT_REF buffer ) :
        BufferToc( buffer ),
        m_num_particles_in_set(),
        m_begin_indices(),
        m_end_indices(),
        m_total_num_particles( ParticleSetsBufferToc::size_type{ 0 } )
    {

    }

    ParticleSetsBufferToc::ParticleSetsBufferToc( const
        ParticleSetsBufferToc::c_buffer_t *const SIXTRL_RESTRICT buffer ) :
        BufferToc( buffer ),
        m_num_particles_in_set(),
        m_begin_indices(),
        m_end_indices(),
        m_total_num_particles( ParticleSetsBufferToc::size_type{ 0 } )
    {

    }

    /* --------------------------------------------------------------------- */

    ParticleSetsBufferToc::size_type
    ParticleSetsBufferToc::num_particle_sets() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSSERT( this->m_num_particles_in_set.size() ==
                        this->m_begin_indices.size() );

        SIXTRL_ASSSERT( this->m_num_particles_in_set.size() ==
                        this->m_end_indices.size() );

        SIXTRL_ASSSERT( this->m_num_particles_in_set.size() ==
                        this->m_pset_state_buffer.getNumObjects() );

        return this->m_num_particles_in_set.size();
    }

    ParticleSetsBufferToc::size_type const*
        ParticleSetsBufferToc::num_particles_in_sets_begin()
            const SIXTRL_NOEXCEPT
    {
        return ( !this->m_num_particles_in_set.empty() )
            ? this->m_num_particles_in_set.data() : nullptr;
    }

    ParticleSetsBufferToc::size_type const*
        ParticleSetsBufferToc::num_particles_in_sets_end()
            const SIXTRL_NOEXCEPT
    {
        using _size_t = st::ParticleSetsBufferToc::size_type;
        _size_t const* ptr_end = this->num_particles_in_sets_begin();
        _size_t const num_psets = this->num_particle_sets();

        if( ( ptr_end != nullptr ) && ( num_psets > _size_t{ 0 } ) )
        {
            std::advance( ptr_end, num_psets );
        }

        return ptr_end;
    }

    ParticleSetsBufferToc::size_type const*
        ParticleSetsBufferToc::particle_set_begin_index_begin()
            const SIXTRL_NOEXCEPT
    {
        return ( !this->m_begin_indices.empty() )
            ? this->m_begin_indices.data() : nullptr;
    }

    ParticleSetsBufferToc::size_type const*
        ParticleSetsBufferToc::particle_set_begin_index_end()
            const SIXTRL_NOEXCEPT
    {
        using _size_t = st::ParticleSetsBufferToc::size_type;
        _size_t const* ptr_end = this->particle_set_begin_index_begin();
        _size_t const num_psets = this->num_particle_sets();

        if( ( ptr_end != nullptr ) && ( num_psets > _size_t{ 0 } ) )
        {
            std::advance( ptr_end, num_psets );
        }

        return ptr_end;
    }

    ParticleSetsBufferToc::size_type const*
        ParticleSetsBufferToc::particle_set_end_index_begin()
            const SIXTRL_NOEXCEPT
    {
        return ( !this->m_end_indices.empty() )
            ? this->m_end_indices.data() : nullptr;
    }

    ParticleSetsBufferToc::size_type const*
        ParticleSetsBufferToc::particle_set_end_index_end() const SIXTRL_NOEXCEPT
    {
        using _size_t = st::ParticleSetsBufferToc::size_type;
        _size_t const* ptr_end = this->particle_set_end_index_begin();
        _size_t const num_psets = this->num_particle_sets();

        if( ( ptr_end != nullptr ) && ( num_psets > _size_t{ 0 } ) )
        {
            std::advance( ptr_end, num_psets );
        }

        return ptr_end;
    }

    ParticleSetsBufferToc::size_type
    ParticleSetsBufferToc::particle_set_begin_index(
        ParticleSetsBufferToc::size_type const pset_idx ) const SIXTRL_NOEXCEPT
    {
        using _pset_toc_t = st::ParticleSetsBufferToc;
        _pset_toc_t::size_type begin_idx = _pset_toc_t::size_type{ 0 };

        if( pset_idx < this->num_particle_sets() )
        {
            begin_idx = this->m_begin_indices[ pset_idx ];
            SIXTRL_ASSERT( begin_idx <= this->m_total_num_particles );
            SIXTRL_ASSERT( begin_idx <= this->m_end_indices[ pset_idx ] );
            SIXTRL_ASSERT( this->m_end_indices[ pset_idx ] ==
                ( begin_idx + this->m_num_particles_in_set[ pset_idx ] ) );
        }

        return begin_idx;
    }

    ParticleSetsBufferToc::size_type
    ParticleSetsBufferToc::particle_set_end_index(
        ParticleSetsBufferToc::size_type const pset_idx ) const SIXTRL_NOEXCEPT
    {
        using _pset_toc_t = st::ParticleSetsBufferToc;
        _pset_toc_t::size_type end_idx = _pset_toc_t::size_type{ 0 };

        if( pset_idx < this->num_particle_sets() )
        {
            end_idx = this->m_end_indices[ pset_idx ];
            SIXTRL_ASSERT( end_idx <= this->m_total_num_particles );
            SIXTRL_ASSERT( end_idx >= this->m_begin_indices[ pset_idx ] );
            SIXTRL_ASSERT( end_idx == ( this->m_begin_indices[ pset_idx ] +
                this->m_num_particles_in_set[ pset_idx ] ) );
        }

        return end_idx;
    }

    ParticleSetsBufferToc::size_type ParticleSetsBufferToc::num_particles(
        ParticleSetsBufferToc::size_type const pset_idx ) const SIXTRL_NOEXCEPT
    {
        using _pset_toc_t = st::ParticleSetsBufferToc;
        _pset_toc_t::size_type num_particles = _pset_toc_t::size_type{ 0 };

        if( pset_idx < this->num_particle_sets() )
        {
            num_particles = this->m_num_particles_in_set[ pset_idx ];
            SIXTRL_ASSERT( num_particles <= this->m_total_num_particles );
        }

        return num_particles;
    }

    ParticleSetsBufferToc::size_type
    ParticleSetsBufferToc::total_num_particles() const SIXTRL_NOEXCEPT
    {
        return this->m_total_num_particles;
    }

    /* --------------------------------------------------------------------- */

    bool operator==(
        st::ParticleSetsBufferToc const& SIXTRL_RESTRICT_REF lhs,
        st::ParticleSetsBufferToc const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT
    {
        _this_t const& lhs_base = static_cast< _this_t const& >( lhs );
        _this_t const& rhs_base = static_cast< _this_t const& >( rhs );

        _this_t::size_type const num_particle_sets = lhs.num_particle_sets();

        bool are_equal = (
            ( lhs_base == rhs_base ) &&
            ( lhs.total_num_particles() == rhs.total_num_particles() ) &&
            ( num_particle_sets == rhs.num_particle_sets() ) );

        if( ( are_equal ) && ( num_particle_sets > _this_t::size_type{ 0 } ) )
        {
            are_equal = std::equal( lhs.num_particles_in_sets_begin(),
                                    lhs.num_particles_in_sets_end(),
                                    rhs.num_particles_in_sets_begin() );

            if( are_equal )
            {
                are_equal = std::equal( lhs.particle_set_begin_index_begin(),
                                        lhs.particle_set_begin_index_end(),
                                        rhs.particle_set_begin_index_begin() );
            }

            if( are_equal )
            {
                are_equal = std::equal( lhs.particle_set_end_index_begin(),
                                        lhs.particle_set_end_index_end(),
                                        rhs.particle_set_end_index_begin() );
            }
        }

        return are_equal;
    }

    bool operator!=(
        st::ParticleSetsBufferToc const& SIXTRL_RESTRICT_REF lhs,
        st::ParticleSetsBufferToc const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT
    {
        return ( lhs != rhs );
    }

    ParticleSetsBufferToc::status_t ParticleSetsBufferToc::doReset(
        const ParticleSetsBufferToc::c_buffer_t *const SIXTRL_RESTRICT buffer )
    {
        using pset_t = ::NS(Particles);
        using ptr_pset_t = SIXTRL_PARTICLES_ARGPTR_DEC pset_t const*;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        this->doClearParticleSetsImpl();
        status = _this_t::doReset( buffer );

        _this_t::size_type const num_objs =
            ::NS(Buffer_get_num_of_objects)( buffer );

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( num_objs > _this_t::size_type{ 0 } ) )
        {
            auto obj_it  = ::NS(Buffer_get_const_object_begin)( buffer );
            auto obj_end = ::NS(Buffer_get_const_object_end)( buffer );

            SIXTRL_ASSERT( obj_it  != nullptr );
            SIXTRL_ASSERT( obj_end != nullptr );

            this->m_num_particles_in_set.reserve( num_objs );
            this->m_begin_indices.reserve( num_objs );
            this->m_end_indices.reserve( num_objs );

            for( ; obj_it != obj_end ; ++obj_it )
            {
                if( ::NS(Object_get_type_id)( obj_it ) !=
                    st::OBJECT_TYPE_PARTICLE )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

                ptr_pset_t pset = reinterpret_cast< ptr_pset_t >(
                    reinterpret_cast< uintptr_t >( ::NS(Object_get_begin_addr)(
                        obj ) ) );

                ::NS(particle_num_elements_t) const npart =
                    ::NS(Particles_get_num_of_particles)( pset );

                if( ( npart >= ::NS(particle_num_elements_t){ 0 } ) &&
                    ( status == st::ARCH_STATUS_SUCCESS ) )
                {
                    this->m_num_particles_in_set.push_back(
                        static_cast< _this_t::size_type >( npart ) );

                    this->m_begin_indices.push_back(
                        this->m_total_num_particles );

                    this->m_total_num_particles += npart;

                    this->m_end_indices.push_back(
                        this->m_total_num_particles );
                }
            }

            if( status != st::ARCH_STATUS_SUCCESS )
            {
                _this_t::doClear();
                this->doClearParticleSetsImpl();
            }
        }

        return status;
    }

    ParticleSetsBufferToc::status_t ParticleSetsBufferToc::doClear()
    {
        _this_t::doClear();
        this->doClearParticleSetsImpl();
    }

    bool ParticleSetsBufferToc::doCheckIsCompatibleWithBuffer(
        const ParticleSetsBufferToc::c_buffer_t *const SIXTRL_RESTRICT buffer )
    {
        using pset_t = ::NS(Particles);
        using ptr_pset_t = SIXTRL_PARTICLES_ARGPTR_DEC pset_t const*;
        using _size_t = _this_t::size_type;

        bool is_compatible = _this_t::doCheckIsCompatibleWithBuffer( buffer );
        _size_t const num_psets = this->num_particle_sets();

        if( ( is_compatible ) && ( num_psets > _size_t{ 0 } ) &&
            ( ::NS(Buffer_get_num_of_objects)( buffer ) == num_psets ) )
        {
            _size_t cmp_begin_index = _size_t{ 0 };
            _size_t cmp_total_num_particles = _size_t{ 0 };

            auto obj_it  = ::NS(Buffer_get_const_object_begin)( buffer );
            auto obj_end = ::NS(Buffer_get_const_object_end)( buffer );

            SIXTRL_ASSERT( obj_it  != nullptr );
            SIXTRL_ASSERT( obj_end != nullptr );

            _size_t const* pnum_it  = this->num_particles_in_sets_begin();
            _size_t const* begin_it = this->particle_set_begin_index_begin();
            _size_t const* end_it   = this->particle_set_end_index_begin();

            SIXTRL_ASSERT( pnum_it  != nullptr );
            SIXTRL_ASSERT( begin_it != nullptr );
            SIXTRL_ASSERT( end_it   != nullptr );

            while( ( is_compatible ) && ( obj_it != obj_end ) )
            {
                is_compatible = ( ::NS(Object_get_type_id)( obj_it ) ==
                    st::OBJECT_TYPE_PARTICLE );

                if( is_compatible )
                {
                    ptr_pset_t pset = reinterpret_cast< ptr_pset_t >(
                        reinterpret_cast< uintptr_t >(
                            ::NS(Object_get_begin_addr)( obj ) ) );

                    _size_t const npart =
                        ::NS(Particles_get_num_of_particles)( pset );

                    _size_t const cmp_end_index = cmp_begin_index + npart;
                    cmp_total_num_particles += npart;

                    is_compatible = ( ( pset != nullptr ) &&
                        ( npart == *pnum_it ) &&
                        ( cmp_begin_index == *begin_it ) &&
                        ( cmp_end_index == *end_it ) );

                    if( is_compatible )
                    {
                        cmp_begin_index = cmp_end_index;
                        ++obj_it;
                        ++pnum_it;
                        ++begin_it;
                        ++end_it;
                    }
                }
            }

            if( is_compatible )
            {
                is_compatible = ( this->total_num_particles() ==
                    cmp_total_num_particles );
            }
        }

        return is_compatible;
    }

    void ParticleSetsBufferToc::doClearParticleSetsImpl() SIXTRL_NOEXCEPT
    {
        this->m_num_particles_in_set.clear();
        this->m_begin_indices.clear();
        this->m_end_indices.clear();
        this->m_total_num_particles = _this_t::size_type{ 0 };
    }
}

#endif /* endif defined( __cplusplus ) && !defined( _GPUCODE ) */
