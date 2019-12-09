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
        st::BufferToc const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
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
}

#endif /* endif defined( __cplusplus ) && !defined( _GPUCODE ) */
