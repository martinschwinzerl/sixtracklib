#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
        #include <cstddef>
        #include <cstdlib>
        #include <cstring>
        #include <cstdio>
        #include <memory>
        #include <map>
        #include <thread>
        #include <mutex>
        #include <stdexcept>
        #include <set>
        #include <sstream>
        #include <vector>
        #include <utility>
#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/arch_info.h"
    #include "sixtracklib/common/control/controller_base.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/stl_buffer_helper.hpp"
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/arch_info.hpp"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/node_info.hpp"
    #include "sixtracklib/common/control/node_info.h"
    #include "sixtracklib/common/control/node_set.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    using _store_t = st::NodeStore;

    constexpr _store_t::node_str_role_t   _store_t::NODE_ID_STR;
    constexpr _store_t::node_str_role_t   _store_t::NODE_UNIQUE_ID_STR;
    constexpr _store_t::arch_id_t         _store_t::ARCH_ILLEGAL;
    constexpr _store_t::platform_id_t     _store_t::ILLEGAL_PLATFORM_ID;
    constexpr _store_t::device_id_t       _store_t::ILLEGAL_DEVICE_ID;
    constexpr _store_t::node_index_t      _store_t::UNDEFINED_INDEX;
    constexpr _store_t::node_set_id_t     _store_t::ILLEGAL_NODE_SET_ID;
    constexpr _store_t::sync_id_value_t   _store_t::ILLEGAL_SYNC_ID_VALUE;
    constexpr _store_t::sync_id_value_t   _store_t::LAST_LEGAL_SYNC_ID_VALUE;

    /* --------------------------------------------------------------------- */

    NodeStore::NodeStore() :
        m_arch_to_platforms(), m_node_set_to_node_idxs(),
        m_node_set_to_sel_node_idxs(), m_node_set_to_def_node_idxs(),
        m_node_idx_to_set_ids(), m_node_idx_to_sel_set_ids(),
        m_node_idx_to_def_set_ids(), m_arch_platform_to_devices(),
        m_node_id_to_node_index(), m_stored_node_infos(), m_stored_node_sets(),
        m_sync_id( _store_t::sync_id_value_t{ 0 } ),
        m_num_node_infos( _store_t::size_type{ 0 } ),
        m_num_node_sets( _store_t::size_type{ 0 } ), m_lockable()
    {

    }

    NodeStore::NodeStore( NodeStore const& SIXTRL_RESTRICT_REF other ) :
        m_arch_to_platforms(), m_node_set_to_node_idxs(),
        m_node_set_to_sel_node_idxs(), m_node_set_to_def_node_idxs(),
        m_node_idx_to_set_ids(), m_node_idx_to_sel_set_ids(),
        m_node_idx_to_def_set_ids(), m_arch_platform_to_devices(),
        m_node_id_to_node_index(), m_stored_node_infos(), m_stored_node_sets(),
        m_sync_id( _store_t::ILLEGAL_SYNC_ID_VALUE ),
        m_num_node_infos( _store_t::size_type{ 0 } ),
        m_num_node_sets( _store_t::size_type{ 0 } ), m_lockable()
    {
        *this = other;
    }

    NodeStore::NodeStore( NodeStore&& other ) SIXTRL_NOEXCEPT :
        m_arch_to_platforms(), m_node_set_to_node_idxs(),
        m_node_set_to_sel_node_idxs(), m_node_set_to_def_node_idxs(),
        m_node_idx_to_set_ids(), m_node_idx_to_sel_set_ids(),
        m_node_idx_to_def_set_ids(), m_arch_platform_to_devices(),
        m_node_id_to_node_index(), m_stored_node_infos(), m_stored_node_sets(),
        m_sync_id( _store_t::ILLEGAL_SYNC_ID_VALUE ),
        m_num_node_infos( _store_t::size_type{ 0 } ),
        m_num_node_sets( _store_t::size_type{ 0 } ), m_lockable()
    {
        *this = std::move( other );
    }

    NodeStore& NodeStore::operator=(
        NodeStore const& SIXTRL_RESTRICT_REF other )
    {
        _store_t::lock_t const other_lock( *other.lockable() );

        if( this != &other )
        {
            _store_t::lock_t const my_lock( *this->lockable() );

            this->m_arch_to_platforms = other.m_arch_to_platforms;

            this->m_node_set_to_node_idxs     = other.m_node_set_to_node_idxs;

            this->m_node_set_to_sel_node_idxs =
                other.m_node_set_to_sel_node_idxs;

            this->m_node_set_to_def_node_idxs =
                other.m_node_set_to_def_node_idxs;

            this->m_node_idx_to_set_ids     = other.m_node_idx_to_set_ids;
            this->m_node_idx_to_sel_set_ids = other.m_node_idx_to_sel_set_ids;
            this->m_node_idx_to_def_set_ids = other.m_node_idx_to_def_set_ids;

            this->m_arch_platform_to_devices =
                other.m_arch_platform_to_devices;

            this->m_node_id_to_node_index = other.m_node_id_to_node_index;

            this->m_stored_node_infos.clear();
            if( !other.m_stored_node_infos.empty() )
            {
                this->m_stored_node_infos.reserve(
                    other.m_stored_node_infos.size() );

                auto in_it  = other.m_stored_node_infos.begin();
                auto in_end = other.m_stored_node_infos.end();

                for( ; in_it != in_end ; ++in_it )
                {
                    _store_t::ptr_stored_node_info_t ptr( nullptr );

                    if( in_it->get() != nullptr )
                    {
                        ptr.reset( new node_info_base_t( *( in_it->get() ) ) );
                    }

                    this->m_stored_node_infos.emplace_back( std::move( ptr ) );
                }

                SIXTRL_ASSERT( this->m_stored_node_infos.size() ==
                               other.m_stored_node_infos.size() );
            }

            this->m_stored_node_sets.clear();
            if( !other.m_stored_node_sets.empty() )
            {
                this->m_stored_node_sets.reserve(
                    other.m_stored_node_sets.size() );

                auto in_it  = other.m_stored_node_sets.begin();
                auto in_end = other.m_stored_node_sets.end();

                for( ; in_it != in_end ; ++in_it )
                {
                    _store_t::ptr_stored_node_set_t ptr( nullptr );

                    if( in_it->get() != nullptr )
                    {
                        ptr.reset( new node_set_base_t( *( in_it->get() ) ) );
                    }

                    this->m_stored_node_sets.emplace_back( std::move( ptr ) );
                }

                SIXTRL_ASSERT( this->m_stored_node_sets.size() ==
                               other.m_stored_node_sets.size() );
            }

            this->m_sync_id.store( other.m_sync_id.load() );

            this->m_num_node_infos = other.m_num_node_infos;
            this->m_num_node_sets  = other.m_num_node_sets;
        }

        return *this;
    }

    NodeStore& NodeStore::operator=( NodeStore&& other ) SIXTRL_NOEXCEPT
    {
        _store_t::lock_t const other_lock( *other.lockable() );

        if( this != &other )
        {
            _store_t::lock_t const my_lock( *this->lockable() );

            this->m_arch_to_platforms = std::move( other.m_arch_to_platforms );

            this->m_node_set_to_node_idxs =
                std::move( other.m_node_set_to_node_idxs );

            this->m_node_set_to_sel_node_idxs =
                std::move( other.m_node_set_to_sel_node_idxs );

            this->m_node_set_to_def_node_idxs =
                std::move( other.m_node_set_to_def_node_idxs );

            this->m_node_idx_to_set_ids =
                std::move( other.m_node_idx_to_set_ids );

            this->m_node_idx_to_sel_set_ids =
                std::move( other.m_node_idx_to_sel_set_ids );

            this->m_node_idx_to_def_set_ids =
                std::move( other.m_node_idx_to_def_set_ids );

            this->m_arch_platform_to_devices =
                std::move( other.m_arch_platform_to_devices );

            this->m_node_id_to_node_index =
                std::move( other.m_node_id_to_node_index );

            this->m_stored_node_infos = std::move( other.m_stored_node_infos );
            this->m_stored_node_sets  = std::move( other.m_stored_node_sets );

            this->m_sync_id.store( other.m_sync_id.load() );
            other.m_sync_id.store( _store_t::ILLEGAL_SYNC_ID_VALUE );

            this->m_num_node_infos    = std::move( other.m_num_node_infos );
            this->m_num_node_sets     = std::move( other.m_num_node_sets );
        }

        return *this;
    }

    NodeStore::~NodeStore() SIXTRL_NOEXCEPT
    {
        /* WARNING: the creation of a lock handle may throw, but there is no
         *          way around that. If an exception is thrown, we try to
         *          brute force the clean-up and hope for the best */
        try
        {
            _store_t::lock_t const lock( *this->lockable() );
            this->clear( lock );
        }
        catch( std::system_error const& e )
        {
            /* We should hopefully *never* end up here */
            this->doClearWithoutLocking();
            /* Crossing fingers that everything is cleaned-up! */
        };
    }

    /* --------------------------------------------------------------------- */

    bool NodeStore::hasPlatform(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id )const SIXTRL_NOEXCEPT
    {
        bool const is_available = (
            ( this->hasArchitecture( lock, arch_id ) ) &&
            ( st::Map_has_key( this->m_arch_platform_to_devices,
                    std::make_pair( arch_id, platform_id ) ) ) );

        SIXTRL_ASSERT( ( !is_available ) ||
            ( ( arch_id != _store_t::ARCH_ILLEGAL ) &&
              ( platform_id != _store_t::ILLEGAL_PLATFORM_ID ) &&
              ( this->checkLock( lock ) ) ) );

        return is_available;
    }

    _store_t::size_type NodeStore::numPlatforms(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        _store_t::size_type num_platforms = _store_t::size_type{ 0 };

        if( ( this->checkLock( lock ) ) &&
            ( this->hasArchitecture( lock, arch_id ) ) &&
            ( !this->m_arch_platform_to_devices.empty() ) )
        {
            auto it  = this->m_arch_to_platforms.begin();
            auto end = this->m_arch_to_platforms.end();

            for( ; it != end ; ++it )
            {
                if( ( it->first == arch_id ) && ( !it->second.empty() ) )
                {
                    auto plfm_it  = it->second.begin();
                    auto plfm_end = it->second.end();

                    for( ; plfm_it != plfm_end ; ++plfm_it )
                    {
                        _store_t::platform_id_t const platform_id = *plfm_it;

                        if( ( platform_id != _store_t::ILLEGAL_PLATFORM_ID ) &&
                            ( this->m_arch_platform_to_devices.find(
                                std::make_pair( arch_id, platform_id ) ) !=
                              this->m_arch_platform_to_devices.end() ) )
                        {
                            ++num_platforms;
                        }
                    }
                }
            }
        }

        return num_platforms;
    }

    /* --------------------------------------------------------------------- */

    _store_t::node_index_t NodeStore::findNodeIndex(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_id_t const& SIXTRL_RESTRICT_REF nid ) const SIXTRL_NOEXCEPT
    {
        using nidx_t = _store_t::node_index_t;
        using nid_to_nidx_map_t = _store_t::node_id_to_node_index_t;

        nid_to_nidx_map_t const& nid_nidx_map = this->m_node_id_to_node_index;
        nidx_t index = _store_t::UNDEFINED_INDEX;

        if( ( nid.valid() ) && ( this->checkLock( lock ) ) )
        {
            index = st::Map_get_value_or_default_for_key(
                nid_nidx_map, nid, _store_t::UNDEFINED_INDEX );
        }

        SIXTRL_ASSERT( ( index == _store_t::UNDEFINED_INDEX ) ||
            ( ( this->m_stored_node_infos.size() >
                static_cast< _store_t::size_type >( index ) ) &&
              ( this->m_stored_node_infos[ index ].get() != nullptr ) &&
              ( this->m_stored_node_infos[ index ]->ptrNodeStore() == this ) &&
              ( ( this->m_stored_node_infos[ index ]->nodeIndex(
                    lock ) == index ) ||
                ( this->m_stored_node_infos[ index ]->nodeIndex(
                    lock ) == _store_t::UNDEFINED_INDEX ) ) &&
              ( this->m_stored_node_infos[ index ]->nodeId() == nid ) ) );

        return index;
    }

    /* --------------------------------------------------------------------- */

    _store_t::node_index_t NodeStore::findNodeIndex(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_info_base_t const*
            SIXTRL_RESTRICT ptr_node_info ) const SIXTRL_NOEXCEPT
    {
        _store_t::node_index_t index = NodeStore::UNDEFINED_INDEX;

        if( ( ptr_node_info != nullptr ) &&
            ( ptr_node_info->ptrNodeStore() == this ) &&
            ( ptr_node_info->nodeId().valid() ) )
        {
            if( ptr_node_info->nodeIndex( lock ) == _store_t::UNDEFINED_INDEX )
            {
                index = this->findNodeIndex( lock, ptr_node_info->nodeId() );
            }
            else if( this->ptrNodeInfoBase(
                    lock, ptr_node_info->nodeIndex( lock ) ) == ptr_node_info )
            {
                index = ptr_node_info->nodeIndex( lock );
            }
        }

        return index;
    }

    /* --------------------------------------------------------------------- */

    _store_t::node_index_t NodeStore::findNodeIndex(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT str,
        _store_t::node_str_role_t const str_role ) const
    {
        using format_t  = st::node_id_str_fmt_t;
        using index_t   = _store_t::node_index_t;

        _store_t::node_index_t found_index = _store_t::UNDEFINED_INDEX;

        if( !this->checkLock( lock ) )
        {
            return found_index;
        }

        if( str_role == st::NODE_STR_ROLE_ID )
        {
            format_t const format = _store_t::node_id_t::IdentifyFormat( str );

            if( ( format == st::NODE_ID_STR_FORMAT_ARCHID ) ||
                ( format == st::NODE_ID_STR_FORMAT_ARCHSTR ) )
            {
                _store_t::node_id_t const node_id( str );

                if( ( node_id.valid() ) &&
                    ( ( node_id.archId() == arch_id ) ||
                      ( arch_id == _store_t::ARCH_ILLEGAL ) ) )
                {
                    found_index = this->findNodeIndex( node_id );
                }
            }
            else if( ( format == st::NODE_ID_STR_FORMAT_NOARCH ) &&
                     ( arch_id != _store_t::ARCH_ILLEGAL ) )
            {
                _store_t::node_id_t const node_id( arch_id, str );

                if( node_id.valid() )
                {
                    found_index = this->findNodeIndex( node_id );
                }
            }
        }
        else if( ( str_role == st::NODE_STR_ROLE_UNIQUE_ID ) &&
                 ( str != nullptr ) && ( std::strlen( str ) > 0u ) )
        {
            auto it  = this->m_stored_node_infos.begin();
            auto end = this->m_stored_node_infos.end();
            auto found_node = end;

            index_t index = index_t{ 0 };
            index_t num_found_nodes = index_t{ 0 };

            for( ; it != end ; ++it, ++index )
            {
                SIXTRL_ASSERT( it->get() != nullptr );

                if( ( ( *it )->hasUniqueIdStr() ) &&
                    ( ( *it )->uniqueIdStr().compare( str ) == 0 ) )
                {
                    if( arch_id != _store_t::ARCH_ILLEGAL )
                    {
                        if( arch_id == ( *it )->archId() )
                        {
                            found_node = it;
                            found_index = index;
                            break;
                        }
                    }
                    else if( found_node == end )
                    {
                        found_node = it;
                    }

                    ++num_found_nodes;
                }
            }

            if( ( found_index == _store_t::UNDEFINED_INDEX ) &&
                ( found_node != end ) &&
                ( arch_id == st::ARCHITECTURE_ILLEGAL ) &&
                ( num_found_nodes == index_t{ 1 } ) )
            {
                found_index = static_cast< index_t >( std::distance(
                    this->m_stored_node_infos.begin(), found_node ) );
            }
        }

        return found_index;
    }

    /* --------------------------------------------------------------------- */

    _store_t::size_type NodeStore::numNodes(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        _store_t::size_type num_nodes = _store_t::size_type{ 0 };
        auto it = this->m_arch_to_platforms.find( arch_id );

        if( ( this->checkLock( lock ) ) &&
            ( it != this->m_arch_to_platforms.end() ) &&
            ( !it->second.empty() ) )
        {
            auto arch_it  = it->second.begin();
            auto arch_end = it->second.end();

            for( ; arch_it != arch_end ; ++arch_it )
            {
                auto const arch_plfm = std::make_pair( arch_id, *arch_it );
                SIXTRL_ASSERT( st::Map_has_key(
                    this->m_arch_platform_to_devices, arch_plfm ) );

                num_nodes += st::Map_ordered_vec_size(
                    this->m_arch_platform_to_devices, arch_plfm );
            }
        }

        return num_nodes;
    }

    _store_t::size_type NodeStore::numNodes(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::arch_id_t const arch_id,
        _store_t::platform_id_t const platform_id ) const SIXTRL_NOEXCEPT
    {
        _store_t::size_type num_nodes = _store_t::size_type{ 0 };

        if( ( this->hasArchitecture( lock, arch_id ) ) &&
            ( st::Map_ordered_vec_has_value( this->m_arch_to_platforms,
                arch_id, platform_id ) ) )
        {
            SIXTRL_ASSERT( arch_id != _store_t::ARCH_ILLEGAL );
            SIXTRL_ASSERT( platform_id != _store_t::ILLEGAL_PLATFORM_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            num_nodes = st::Map_ordered_vec_size(
                this->m_arch_platform_to_devices,
                    std::make_pair( arch_id, platform_id ) );
        }

        return num_nodes;
    }

    _store_t::size_type NodeStore::numNodes(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        _store_t::size_type num_nodes = _store_t::size_type{ 0 };

        if( this->hasNodeSet( lock, node_set_id ) )
        {
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            num_nodes = st::Map_ordered_vec_size(
                this->m_node_set_to_node_idxs, node_set_id );
        }

        return num_nodes;
    }

    _store_t::size_type NodeStore::numSelectedNodes(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        _store_t::size_type num_nodes = _store_t::size_type{ 0 };

        if( this->hasNodeSet( lock, node_set_id ) )
        {
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            num_nodes = st::Map_ordered_vec_size(
                this->m_node_set_to_sel_node_idxs, node_set_id );
        }

        return num_nodes;
    }

    _store_t::size_type NodeStore::numDefaultNodes(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        _store_t::size_type num_nodes = _store_t::size_type{ 0 };

        if( this->hasNodeSet( lock, node_set_id ) )
        {
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            num_nodes = st::Map_ordered_vec_size(
                this->m_node_set_to_def_node_idxs, node_set_id );
        }

        return num_nodes;
    }

    /* --------------------------------------------------------------------- */

    bool NodeStore::isNodeAvailable(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        auto ptr_node = this->ptrNodeInfoBase( lock, index );

        SIXTRL_ASSERT( ( ptr_node == nullptr ) ||
            ( ( this->checkLock( lock ) ) &&
              ( this->m_stored_node_infos.size() > static_cast<
                _store_t::size_type >( index ) ) &&
              ( this->m_stored_node_infos[ index ].get() == ptr_node ) &&
              ( st::Map_has_key( this->m_node_idx_to_set_ids, index ) ) &&
              ( st::Map_has_key( this->m_node_idx_to_sel_set_ids, index ) ) &&
              ( st::Map_has_key( this->m_node_idx_to_def_set_ids, index ) ) &&
              ( st::Map_has_key(
                this->m_node_id_to_node_index, ptr_node->nodeId( lock ) ) ) ) );

        return ( ( ptr_node != nullptr ) &&
                 ( ptr_node->ptrNodeStore() == this ) &&
                 ( ptr_node->nodeIndex( lock ) == index ) );
    }

    _store_t::node_id_t const* NodeStore::ptrNodeId(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        NodeStore::node_info_base_t const* ptr_node_info =
            this->ptrNodeInfoBase( lock, index );

        SIXTRL_ASSERT( ( ptr_node_info == nullptr ) ||
            ( this->checkLock( lock ) ) );

        return ( ptr_node_info != nullptr )
            ? ptr_node_info->ptrNodeId() : nullptr;
    }

    _store_t::node_info_base_t const* NodeStore::ptrNodeInfoBase(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->checkLock( lock ) ) &&
                 ( index != _store_t::UNDEFINED_INDEX ) &&
                 ( this->m_stored_node_infos.size() > index ) )
            ? this->m_stored_node_infos[ index ].get() : nullptr;
    }

    _store_t::node_info_base_t* NodeStore::ptrNodeInfoBase(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index ) SIXTRL_NOEXCEPT
    {
        using ptr_t = NodeStore::node_info_base_t*;

        return const_cast< ptr_t >( static_cast< _store_t const& >( *this
            ).ptrNodeInfoBase( lock, index ) );
    }

    /* --------------------------------------------------------------------- */

    bool NodeStore::hasNodeSets(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->checkLock( lock ) ) &&
                 ( this->m_num_node_sets > _store_t::size_type{ 0 } ) );
    }

    _store_t::size_type NodeStore::numNodeSets(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? this->m_num_node_sets : _store_t::size_type{ 0 };
    }

    bool NodeStore::hasNodeSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_set_id_t const set_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( set_id != _store_t::ILLEGAL_NODE_SET_ID ) &&
                 ( this->checkLock( lock ) ) &&
                 ( static_cast< _store_t::size_type >( set_id ) <
                   this->m_stored_node_sets.size() ) &&
                (  this->m_stored_node_sets[ set_id ].get() != nullptr ) &&
                (  this->m_stored_node_sets[
                        set_id ]->ptrNodeStore() == this ) );
    }

    bool NodeStore::hasNodeSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        st::NodeSetBase& SIXTRL_RESTRICT_REF node_set ) const  SIXTRL_NOEXCEPT
    {
        bool has_node_set = false;

        using size_t = _store_t::size_type;

        if( ( this->checkLock( lock ) ) &&
            ( node_set.ptrNodeStore() == this ) )
        {
            if( ( node_set.nodeSetId() != _store_t::ILLEGAL_NODE_SET_ID ) &&
                ( static_cast< size_t >( node_set.nodeSetId() ) <
                  this->m_stored_node_sets.size() ) &&
                ( this->m_stored_node_sets[ node_set.nodeSetId() ].get() ==
                    &node_set ) )
            {
                has_node_set = true;
            }
            else if( node_set.nodeSetId() == _store_t::ILLEGAL_NODE_SET_ID )
            {
                auto it  = this->m_stored_node_sets.begin();
                auto end = this->m_stored_node_sets.end();
                _store_t::node_set_id_t node_set_id =
                    _store_t::node_set_id_t{ 0 };

                for( ; it != end ; ++it, ++node_set_id )
                {
                    if( it->get() == &node_set )
                    {
                        has_node_set = true;
                        _store_t::status_t status = node_set.setNodeSetId(
                            lock, node_set_id );

                        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
                        ( void )status;

                        break;
                    }
                }
            }
        }

        return has_node_set;
    }

    _store_t::node_set_id_t NodeStore::addNodeSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::ptr_stored_node_set_t&& ptr_node_set )
    {
        using node_set_map_t =_store_t::node_set_to_node_indices_t;
        using indices_list_t = _store_t::node_indices_list_t;
        using nset_id_t = _store_t::node_set_id_t;
        using status_t  = _store_t::status_t;

        _store_t::node_set_id_t node_set_id = _store_t::ILLEGAL_NODE_SET_ID;

        if( ( ptr_node_set.get() != nullptr ) &&
            ( ptr_node_set->ptrNodeStore() == this ) &&
            ( ptr_node_set->nodeSetId() == _store_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            node_set_map_t& nset_avail_nodes = this->m_node_set_to_node_idxs;
            node_set_map_t& nset_sel_nodes = this->m_node_set_to_sel_node_idxs;
            node_set_map_t& nset_def_nodes = this->m_node_set_to_def_node_idxs;

            SIXTRL_ASSERT( !st::Map_has_key( nset_avail_nodes, node_set_id ) );
            SIXTRL_ASSERT( !st::Map_has_key( nset_sel_nodes, node_set_id ) );
            SIXTRL_ASSERT( !st::Map_has_key( nset_def_nodes, node_set_id ) );

            nset_id_t const next_nset_id = this->m_stored_node_sets.size();
            status_t status = ptr_node_set->setNodeSetId( lock, next_nset_id );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                auto res1 = nset_avail_nodes.emplace(
                    std::make_pair( next_nset_id, indices_list_t{} ) );

                auto res2 = nset_sel_nodes.emplace(
                    std::make_pair( next_nset_id, indices_list_t{} ) );

                auto res3 = nset_def_nodes.emplace(
                    std::make_pair( next_nset_id, indices_list_t{} ) );

                status = ( ( res1.second ) && ( res2.second ) &&
                           ( res3.second ) )
                    ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                this->m_stored_node_sets.emplace_back(
                    std::move( ptr_node_set ) );

                SIXTRL_ASSERT( this->m_stored_node_sets.back().get()
                    != nullptr );

                SIXTRL_ASSERT( this->m_stored_node_sets.back()->nodeSetId() ==
                    next_nset_id );

                ++this->m_num_node_sets;
                node_set_id = next_nset_id;
            }
        }

        return node_set_id;
    }

    _store_t::status_t NodeStore::removeNodeSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_set_id_t const node_set_id ) SIXTRL_NOEXCEPT
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        st::NodeSetBase* ptr_set = this->ptrNodeSetBase( lock, node_set_id );

        if( ( ptr_set != nullptr ) &&
            ( this->m_num_node_sets > _store_t::size_type{ 0 }  ) )
        {
            status = st::ARCH_STATUS_SUCCESS;

            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( this->m_stored_node_sets.size() > static_cast<
                _store_t::size_type >( node_set_id ) );

            if( ptr_set->numNodes( lock ) > _store_t::size_type{ 0 } )
            {
                status = this->detachAllNodesFromSet( lock, node_set_id );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::Map_remove_if_ordered_vec_empty(
                    this->m_node_set_to_node_idxs, node_set_id );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::Map_remove_if_ordered_vec_empty(
                        this->m_node_set_to_sel_node_idxs, node_set_id );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::Map_remove_if_ordered_vec_empty(
                        this->m_node_set_to_def_node_idxs, node_set_id );
                }
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                this->m_stored_node_sets[ node_set_id ].reset( nullptr );
                --this->m_num_node_sets;
            }
        }

        return status;
    }

    _store_t::node_set_id_t NodeStore::nodeSetId(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        st::NodeSetBase& SIXTRL_RESTRICT_REF node_set ) const SIXTRL_NOEXCEPT
    {
        if( ( this->checkLock( lock ) ) &&
            ( this->m_num_node_sets > _store_t::size_type{ 0 } ) &&
            ( node_set.ptrNodeStore() == this ) )
        {
            _store_t::node_set_id_t node_set_id = _store_t::node_set_id_t{ 0 };

            auto it  = this->m_stored_node_sets.begin();
            auto end = this->m_stored_node_sets.end();

            for( ; it != end ; ++it, ++node_set_id )
            {
                if( it->get() == &node_set ) return node_set_id;
            }
        }

        return _store_t::ILLEGAL_NODE_SET_ID;
    }

    st::NodeSetBase* NodeStore::ptrNodeSetBase(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_set_id_t const node_set_id )  SIXTRL_NOEXCEPT
    {
        return const_cast< st::NodeSetBase* >( static_cast< _store_t const& >(
            *this ).ptrNodeSetBase( lock, node_set_id ) );
    }

    st::NodeSetBase const* NodeStore::ptrNodeSetBase(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( node_set_id != _store_t::ILLEGAL_NODE_SET_ID ) &&
                 ( this->checkLock( lock ) ) &&
                 ( this->m_stored_node_sets.size() > static_cast<
                    _store_t::size_type >( node_set_id ) ) )
            ? this->m_stored_node_sets[ node_set_id ].get() : nullptr;
    }

    st::NodeSetBase& NodeStore::nodeSetBase(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_set_id_t const node_set_id )
    {
        return const_cast< st::NodeSetBase& >( static_cast< _store_t const& >(
            *this ).nodeSetBase( lock, node_set_id ) );
    }

    st::NodeSetBase const& NodeStore::nodeSetBase(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_set_id_t const node_set_id ) const
    {
        auto ptr = this->ptrNodeSetBase( lock, node_set_id );

        if( ptr == nullptr )
        {
            throw std::runtime_error( "unable to access stored NodeSet" );
        }

        return *ptr;
    }

    /* --------------------------------------------------------------------- */

    _store_t::status_t NodeStore::attachNodeToSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const node_index,
        _store_t::node_set_id_t const node_set_id )
    {
        using node_idx_t      = _store_t::node_index_t;
        using nset_id_t       = _store_t::node_set_id_t;
        using nset_nidx_map_t = _store_t::node_set_to_node_indices_t;
        using nidx_nset_map_t = _store_t::node_index_to_node_set_ids_t;

        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        auto ptr_set  = this->ptrNodeSetBase( lock, node_set_id );
        auto ptr_node = this->ptrNodeInfoBase( lock, node_index );

        if( ( ptr_set != nullptr ) && ( ptr_node != nullptr ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( ptr_set->nodeSetId() == node_set_id );
            SIXTRL_ASSERT( ptr_set->ptrNodeStore() == this );
            SIXTRL_ASSERT( node_index != _store_t::UNDEFINED_INDEX );

            nset_nidx_map_t& nset_to_idx     = this->m_node_set_to_node_idxs;
            nset_nidx_map_t& nset_to_sel_idx = this->m_node_set_to_sel_node_idxs;
            nset_nidx_map_t& nset_to_def_idx = this->m_node_set_to_def_node_idxs;

            nidx_nset_map_t& nidx_to_nsets     = this->m_node_idx_to_set_ids;
            nidx_nset_map_t& nidx_to_sel_nsets = this->m_node_idx_to_sel_set_ids;
            nidx_nset_map_t& nidx_to_def_nsets = this->m_node_idx_to_def_set_ids;

            SIXTRL_ASSERT( st::Map_has_key( nset_to_idx, node_set_id ) );
            SIXTRL_ASSERT( st::Map_has_key( nset_to_sel_idx, node_set_id ) );
            SIXTRL_ASSERT( st::Map_has_key( nset_to_def_idx, node_set_id ) );

            SIXTRL_ASSERT( st::Map_has_key( nidx_to_nsets, node_index ) );
            SIXTRL_ASSERT( st::Map_has_key( nidx_to_sel_nsets, node_index ) );
            SIXTRL_ASSERT( st::Map_has_key( nidx_to_def_nsets, node_index ) );

            size_t const num_sets_attached =
                st::Map_ordered_vec_size( nidx_to_nsets, node_index );

            if( ( num_sets_attached < ptr_node->maxAttachementCount() ) &&
                ( !st::Map_ordered_vec_has_value(
                    nset_to_idx, node_set_id, node_index ) ) &&
                ( !st::Map_ordered_vec_has_value(
                    nidx_to_nsets, node_index, node_set_id ) ) )
            {
                SIXTRL_ASSERT( !st::Map_ordered_vec_has_value( nset_to_sel_idx,
                    node_set_id, node_index ) );

                SIXTRL_ASSERT( !st::Map_ordered_vec_has_value( nset_to_def_idx,
                    node_set_id, node_index ) );

                SIXTRL_ASSERT( !st::Map_ordered_vec_has_value( nidx_to_sel_nsets,
                    node_index, node_set_id ) );

                SIXTRL_ASSERT( !st::Map_ordered_vec_has_value( nidx_to_def_nsets,
                    node_index, node_set_id ) );

                status = st::Map_ordered_vec_insert_value( nset_to_idx,
                    node_set_id, node_index, node_idx_t{ 0 }, true );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::Map_ordered_vec_insert_value( nidx_to_nsets,
                        node_index, node_set_id, nset_id_t{ 0 }, true );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    this->registerChange( lock );
                }

                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( st::Map_ordered_vec_size( nidx_to_nsets, node_index ) ==
                      ( num_sets_attached + size_t{ 1 } ) ) );
            }
        }

        return status;
    }

    _store_t::status_t NodeStore::attachAllArchitectureNodesToSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::arch_id_t const arch_id, node_set_id_t const node_set_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->hasArchitecture( lock, arch_id ) ) &&
            ( this->hasNodeSet( lock, node_set_id ) ) )
        {
            SIXTRL_ASSERT( arch_id != _store_t::ARCH_ILLEGAL );
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );

            std::vector< node_index_t > temp_node_indices(
                this->m_num_node_infos, _store_t::UNDEFINED_INDEX );

            temp_node_indices.clear();

            auto node_it  = this->m_stored_node_infos.begin();
            auto node_end = this->m_stored_node_infos.end();
            _store_t::node_index_t node_index = _store_t::node_index_t{ 0 };

            for( ; node_it != node_end ; ++node_it, ++node_index )
            {
                if( ( node_it->get() != nullptr ) &&
                    ( ( *node_it )->archId() == arch_id ) )
                {
                    if( !this->isNodeAttachedToSet(
                            lock, node_index, node_set_id ) )
                    {
                        temp_node_indices.push_back( node_index );
                    }
                }
            }

            if( !temp_node_indices.empty() )
            {
                status = st::ARCH_STATUS_SUCCESS;

                for( auto const node_index : temp_node_indices )
                {
                    status = this->attachNodeToSet(
                        lock, node_index, node_set_id );

                    if( status != st::ARCH_STATUS_SUCCESS )
                    {
                        break;
                    }
                }
            }
        }

        return status;
    }

    _store_t::status_t NodeStore::detachNodeFromSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index,
        _store_t::node_set_id_t const node_set_id )
    {
        using nset_nidx_map_t = _store_t::node_set_to_node_indices_t;
        using nidx_nset_map_t = _store_t::node_index_to_node_set_ids_t;

        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        nset_nidx_map_t& nset_to_idx   = this->m_node_set_to_node_idxs;
        nset_nidx_map_t& nset_to_sel_idx = this->m_node_set_to_sel_node_idxs;
        nset_nidx_map_t& nset_to_def_idx = this->m_node_set_to_def_node_idxs;

        nidx_nset_map_t& nidx_to_nsets = this->m_node_idx_to_set_ids;
        nidx_nset_map_t& nidx_to_sel_nsets = this->m_node_idx_to_sel_set_ids;
        nidx_nset_map_t& nidx_to_def_nsets = this->m_node_idx_to_def_set_ids;

        if( ( this->hasNodeSet( lock, node_set_id ) ) &&
            ( this->isNodeAvailable( lock, index ) ) &&
            ( st::Map_has_key( nset_to_idx, node_set_id ) ) &&
            ( st::Map_has_key( nidx_to_nsets, index ) ) )
        {
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( index  != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto ptr_node = this->ptrNodeInfoBase( lock, index );
            SIXTRL_ASSERT( ptr_node != nullptr );
            SIXTRL_ASSERT( ptr_node->ptrNodeStore() == this );
            SIXTRL_ASSERT( ptr_node->nodeIndex( lock ) == index );
            SIXTRL_ASSERT( ptr_node->nodeId( lock ).valid() );

            if( !st::Map_has_key( this->m_node_id_to_node_index,
                            ptr_node->nodeId( lock ) ) )
            {
                return status;
            }

            auto ptr_set = this->ptrNodeSetBase( lock, node_set_id );
            SIXTRL_ASSERT( ptr_set != nullptr );
            SIXTRL_ASSERT( ptr_set->ptrNodeStore() == this );
            SIXTRL_ASSERT( ptr_set->nodeSetId() == node_set_id );

            bool const needs_set_updating =
                ( ( this->isNodeSelectedBySet( lock, index, node_set_id ) ) ||
                  ( this->isNodeDefaultForSet( lock, index, node_set_id ) ) );

            SIXTRL_ASSERT( st::Map_has_key( nset_to_sel_idx, node_set_id ) );
            SIXTRL_ASSERT( st::Map_has_key( nset_to_def_idx, node_set_id ) );

            SIXTRL_ASSERT( st::Map_has_key( nidx_to_sel_nsets, index ) );
            SIXTRL_ASSERT( st::Map_has_key( nidx_to_def_nsets, index ) );

            status = st::Map_remove_value_from_ordered_vec(
                nset_to_idx, node_set_id, index );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    nidx_to_nsets, index, node_set_id );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                this->registerChange( lock );
            }

            if( st::Map_ordered_vec_has_value(
                    nset_to_def_idx, node_set_id, index ) )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    nset_to_def_idx, node_set_id, index );
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::Map_ordered_vec_has_value(
                    nset_to_sel_idx, node_set_id, index )
                ) )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    nset_to_sel_idx, node_set_id, index );
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::Map_ordered_vec_has_value(
                    nidx_to_def_nsets, index, node_set_id ) ) )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    nidx_to_def_nsets, index, node_set_id );
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::Map_ordered_vec_has_value(
                    nidx_to_sel_nsets, index, node_set_id ) ) )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    nidx_to_sel_nsets, index, node_set_id );
            }

            if( ( needs_set_updating ) && ( st::ARCH_STATUS_SUCCESS !=
                    ptr_set->syncWithStore( lock ) ) )
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
            ( !this->isNodeAttachedToSet( lock, index, node_set_id ) ) );

        return status;
    }

    _store_t::status_t NodeStore::detachAllNodesFromSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_set_id_t const node_set_id )
    {
        using nset_nidx_map_t = _store_t::node_set_to_node_indices_t;
        using node_index_t    = _store_t::node_index_t;
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        nset_nidx_map_t& nset_to_idx = this->m_node_set_to_node_idxs;

        if( ( this->hasNodeSet( lock, node_set_id ) ) &&
            ( st::Map_has_key( nset_to_idx, node_set_id ) ) )
        {
            auto ptr_set = this->ptrNodeSetBase( lock, node_set_id );
            if( ptr_set == nullptr ) return status;

            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = nset_to_idx.find( node_set_id );
            SIXTRL_ASSERT( it != nset_to_idx.end() );

            status = st::ARCH_STATUS_SUCCESS;

            if( !it->second.empty() )
            {
                bool has_changed_set = false;
                std::vector< node_index_t > const node_indices( it->second );

                for( auto const node_index : node_indices )
                {
                    status = this->detachNodeFromSet(
                        lock, node_index, node_set_id );

                    has_changed_set |= ( status == st::ARCH_STATUS_SUCCESS );
                    if( status != st::ARCH_STATUS_SUCCESS ) break;
                }

                if( ( has_changed_set ) && ( st::ARCH_STATUS_SUCCESS !=
                        ptr_set->syncWithStore( lock ) ) )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }
        }

        SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
            ( ( st::Map_ordered_vec_empty( nset_to_idx, node_set_id ) ) &&
              ( st::Map_has_key( this->m_node_set_to_sel_node_idxs,
                    node_set_id ) ) &&
              ( st::Map_ordered_vec_empty( this->m_node_set_to_sel_node_idxs,
                    node_set_id ) ) &&
              ( st::Map_has_key( this->m_node_set_to_def_node_idxs,
                    node_set_id ) ) &&
              ( st::Map_ordered_vec_empty( this->m_node_set_to_def_node_idxs,
                    node_set_id ) ) ) );
        return status;
    }

    _store_t::status_t NodeStore::detachNodeFromAllSets(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const node_index )
    {
        using nidx_nset_map_t = _store_t::node_index_to_node_set_ids_t;
        using nset_id_t = _store_t::node_set_id_t;
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        nidx_nset_map_t& nidx_to_nsets = this->m_node_idx_to_set_ids;

        if( ( this->isNodeAvailable( lock, node_index ) ) &&
            ( st::Map_has_key( nidx_to_nsets, node_index ) ) )
        {
            SIXTRL_ASSERT( node_index != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = nidx_to_nsets.find( node_index );
            SIXTRL_ASSERT( it != nidx_to_nsets.end() );

            status = st::ARCH_STATUS_SUCCESS;

            if( !it->second.empty() )
            {
                std::vector< nset_id_t > const node_set_ids( it->second );

                for( auto const node_set_id : node_set_ids )
                {
                    status = this->detachNodeFromSet(
                        lock, node_index, node_set_id );

                    if( status != st::ARCH_STATUS_SUCCESS ) break;
                }
            }
        }

        SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
            ( ( st::Map_ordered_vec_empty( nidx_to_nsets, node_index ) ) &&
              ( st::Map_has_key( this->m_node_idx_to_sel_set_ids,
                    node_index ) ) &&
              ( st::Map_ordered_vec_empty( this->m_node_idx_to_sel_set_ids,
                    node_index ) ) &&
              ( st::Map_has_key( this->m_node_idx_to_def_set_ids,
                    node_index ) ) &&
              ( st::Map_ordered_vec_empty( this->m_node_idx_to_def_set_ids,
                    node_index ) ) ) );

        return status;
    }

    _store_t::size_type NodeStore::numSetsAttachedToNode(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index ) const
    {
        _store_t::size_type num_sets_attached = _store_t::size_type{ 0 };

        if( ( index != _store_t::UNDEFINED_INDEX ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_node_idx_to_set_ids.find( index );
            if(  it != this->m_node_idx_to_set_ids.end() )
            {
                num_sets_attached = it->second.size();
            }
        }

        return num_sets_attached;
    }

    bool NodeStore::isNodeAttachedToAnySet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index ) const
    {
        bool is_attached_to_any = false;

        if( ( index != _store_t::UNDEFINED_INDEX ) &&
            ( this->checkLock( lock ) ) )
        {
            is_attached_to_any = (
              (  st::Map_has_key( this->m_node_idx_to_set_ids, index ) ) &&
              ( !st::Map_ordered_vec_empty( this->m_node_idx_to_set_ids,
                    index ) ) );
        }

        return is_attached_to_any;
    }

    bool NodeStore::isNodeAttachedToSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index,
        _store_t::node_set_id_t const node_set_id ) const
    {
        bool is_attached_to_set = false;

        if( ( node_set_id != _store_t::ILLEGAL_NODE_SET_ID ) &&
            ( index != _store_t::UNDEFINED_INDEX ) &&
            ( this->checkLock( lock ) ) )
        {
            is_attached_to_set = st::Map_ordered_vec_has_value(
                this->m_node_idx_to_set_ids, index, node_set_id );
        }

        return is_attached_to_set;
    }

    _store_t::node_set_id_t const* NodeStore::attachedNodeSetIdsBegin(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        return ( ( index != _store_t::UNDEFINED_INDEX ) &&
                 ( this->checkLock( lock ) ) )
            ? st::Map_ordered_vec_begin( this->m_node_idx_to_set_ids, index )
            : nullptr;
    }

    _store_t::node_set_id_t const* NodeStore::attachedNodeSetIdsEnd(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        return ( ( index != _store_t::UNDEFINED_INDEX ) &&
                 ( this->checkLock( lock ) ) )
            ? st::Map_ordered_vec_end( this->m_node_idx_to_set_ids, index )
            : nullptr;
    }

    bool NodeStore::canNodeBeSelectedBySet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const node_index,
        _store_t::node_set_id_t const node_set_id,
        bool const ignore_max_limits ) const SIXTRL_NOEXCEPT
    {
        bool can_be_selected_by_set = false;

        auto ptr_node = this->ptrNodeInfoBase( lock, node_index );
        auto ptr_set  = this->ptrNodeSetBase( lock, node_set_id );

        if( ( ptr_node != nullptr ) && ( ptr_node->ptrNodeStore() == this ) &&
            ( ptr_set  != nullptr ) && ( ptr_set->ptrNodeStore() == this ) &&
            ( st::Map_ordered_vec_has_value( this->m_node_set_to_node_idxs,
                node_set_id, node_index ) ) &&
            ( st::Map_ordered_vec_has_value( this->m_node_idx_to_set_ids,
                node_index, node_set_id ) ) &&
            ( st::Map_has_key( this->m_node_idx_to_sel_set_ids,
                node_index ) ) &&
            ( !st::Map_ordered_vec_has_value( this->m_node_idx_to_sel_set_ids,
                node_index, node_set_id ) ) &&
            ( st::Map_has_key( this->m_node_set_to_sel_node_idxs,
                node_set_id ) ) &&
            ( !st::Map_ordered_vec_has_value( this->m_node_set_to_sel_node_idxs,
                node_set_id, node_index ) ) &&
            ( ( ignore_max_limits ) ||
              ( ( st::Map_ordered_vec_size( this->m_node_idx_to_sel_set_ids,
                    node_index ) < ptr_node->maxSelectionCount() ) &&
                ( st::Map_ordered_vec_size( this->m_node_set_to_sel_node_idxs,
                    node_set_id ) < ptr_set->maxNumSelectableNodes() ) ) ) )
        {
            SIXTRL_ASSERT( node_index  != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            SIXTRL_ASSERT( this->isNodeAttachedToSet(
                lock, node_index, node_set_id ) );

            SIXTRL_ASSERT( !this->isNodeSelectedBySet(
                lock, node_index, node_set_id ) );

            can_be_selected_by_set = true;
        }

        return can_be_selected_by_set;
    }

    bool NodeStore::isNodeSelectedBySet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const node_index,
        _store_t::node_set_id_t const node_set_id ) const
    {
        bool is_selected_by_set = false;

        if( ( this->isNodeAvailable( lock, node_index ) ) &&
            ( st::Map_ordered_vec_has_value( this->m_node_set_to_sel_node_idxs,
                node_set_id, node_index ) ) &&
            ( st::Map_ordered_vec_has_value( this->m_node_idx_to_sel_set_ids,
                node_index, node_set_id ) ) )
        {
            SIXTRL_ASSERT( node_index  != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( this->hasNodeSet( lock, node_set_id ) );
            SIXTRL_ASSERT( this->isNodeAttachedToSet(
                lock, node_index, node_set_id ) );

            SIXTRL_ASSERT( st::Map_ordered_vec_has_value(
                this->m_node_set_to_node_idxs, node_set_id, node_index ) );

            SIXTRL_ASSERT( st::Map_ordered_vec_has_value(
                this->m_node_idx_to_set_ids, node_index, node_set_id ) );

            is_selected_by_set = true;
        }

        return is_selected_by_set;
    }

    bool NodeStore::isNodeSelectedByAnySet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const nidx ) const
    {
        bool const is_selected_by_any = ( ( this->checkLock( lock ) ) &&
                (  st::Map_has_key( this->m_node_idx_to_set_ids, nidx ) ) &&
                ( !st::Map_ordered_vec_empty( this->m_node_idx_to_sel_set_ids,
                        nidx ) ) );

        SIXTRL_ASSERT( this->isNodeAvailable( lock, nidx ) );

        return is_selected_by_any;
    }

    _store_t::size_type NodeStore::numSelectingSetsForNode(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index ) const
    {
        using size_t = _store_t::size_type;

        size_t const num_sets_selecting = ( this->checkLock( lock ) )
            ? st::Map_ordered_vec_size( this->m_node_idx_to_sel_set_ids, index )
            : size_t{ 0 };

        SIXTRL_ASSERT( ( num_sets_selecting == size_t{ 0 } ) ||
            ( ( index != _store_t::UNDEFINED_INDEX ) &&
              ( this->hasNodeSets( lock ) ) &&
              ( this->isNodeAvailable( lock, index ) ) &&
              ( this->isNodeAttachedToAnySet( lock, index ) ) &&
              (  st::Map_has_key( this->m_node_idx_to_sel_set_ids, index ) ) &&
              ( !st::Map_ordered_vec_empty( this->m_node_idx_to_sel_set_ids,
                        index ) ) ) );

        return num_sets_selecting;
    }

    _store_t::node_set_id_t const* NodeStore::selectingNodeSetIdsBegin(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        _store_t::node_set_id_t const* ptr_begin = ( this->checkLock( lock ) )
            ? st::Map_ordered_vec_begin( this->m_node_idx_to_sel_set_ids, index )
            : nullptr;

        SIXTRL_ASSERT( ( ptr_begin == nullptr ) ||
            ( ( index != _store_t::UNDEFINED_INDEX ) &&
              ( this->hasNodeSets( lock ) ) &&
              ( this->isNodeAvailable( lock, index ) ) &&
              ( this->isNodeAttachedToAnySet( lock, index ) ) &&
              (  st::Map_has_key( this->m_node_idx_to_sel_set_ids, index ) ) &&
              ( !st::Map_ordered_vec_empty( this->m_node_idx_to_sel_set_ids,
                        index ) ) ) );

        return ptr_begin;
    }

    _store_t::node_set_id_t const* NodeStore::selectingNodeSetIdsEnd(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        _store_t::node_set_id_t const* ptr_end = ( this->checkLock( lock ) )
            ? st::Map_ordered_vec_end( this->m_node_idx_to_sel_set_ids, index )
            : nullptr;

        SIXTRL_ASSERT( ( ptr_end == nullptr ) ||
            ( ( index != _store_t::UNDEFINED_INDEX ) &&
              ( this->hasNodeSets( lock ) ) &&
              ( this->isNodeAvailable( lock, index ) ) &&
              ( this->isNodeAttachedToAnySet( lock, index ) ) &&
              (  st::Map_has_key( this->m_node_idx_to_sel_set_ids, index ) ) &&
              ( !st::Map_ordered_vec_empty( this->m_node_idx_to_sel_set_ids,
                        index ) ) ) );

        return ptr_end;
    }

    bool NodeStore::canNodeBeMadeDefaultForSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const node_index,
        _store_t::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        bool can_be_made_default = false;

        auto ptr_node = this->ptrNodeInfoBase( lock, node_index );
        auto ptr_set  = this->ptrNodeSetBase( lock, node_set_id );

        if( ( ptr_node != nullptr ) && ( ptr_node->ptrNodeStore() == this ) &&
            ( ptr_set  != nullptr ) && ( ptr_set->ptrNodeStore() == this ) &&
            ( st::Map_ordered_vec_has_value( this->m_node_set_to_node_idxs,
                node_set_id, node_index ) ) &&
            ( st::Map_ordered_vec_has_value( this->m_node_idx_to_set_ids,
                node_index, node_set_id ) ) &&
            ( st::Map_has_key( this->m_node_idx_to_def_set_ids,
                node_index ) ) &&
            ( !st::Map_ordered_vec_has_value( this->m_node_idx_to_def_set_ids,
                node_index, node_set_id ) ) &&
            ( st::Map_has_key( this->m_node_set_to_def_node_idxs,
                node_set_id ) ) &&
            ( !st::Map_ordered_vec_has_value( this->m_node_set_to_def_node_idxs,
                node_set_id, node_index ) ) &&
            (  st::Map_ordered_vec_size( this->m_node_idx_to_def_set_ids,
                node_index ) < ptr_set->maxNumDefaultNodes() ) )
        {
            SIXTRL_ASSERT( node_index  != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            SIXTRL_ASSERT( this->isNodeAttachedToSet(
                lock, node_index, node_set_id ) );

            SIXTRL_ASSERT( !this->isNodeDefaultForSet(
                lock, node_index, node_set_id ) );

            can_be_made_default = true;
        }

        return can_be_made_default;
    }

    bool NodeStore::isNodeDefaultForSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const node_index,
        _store_t::node_set_id_t const node_set_id ) const
    {
        bool const is_default_for_set = ( ( this->checkLock( lock ) ) &&
            ( st::Map_ordered_vec_has_value( this->m_node_idx_to_def_set_ids,
                node_index, node_set_id ) ) &&
            ( st::Map_ordered_vec_has_value( this->m_node_set_to_def_node_idxs,
                node_set_id, node_index ) ) );

        SIXTRL_ASSERT( ( !is_default_for_set ) ||
            ( ( node_index != _store_t::UNDEFINED_INDEX ) &&
              ( node_set_id != _store_t::ILLEGAL_NODE_SET_ID ) &&
              ( this->isNodeAvailable( lock, node_index ) ) &&
              ( this->hasNodeSet( lock, node_set_id ) ) &&
              ( this->isNodeAttachedToSet( lock, node_index, node_set_id ) ) ) );

        return is_default_for_set;
    }

    bool NodeStore::isNodeDefaultForAnySet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const node_index ) const SIXTRL_NOEXCEPT
    {
        bool const is_default_for_any = ( ( this->checkLock( lock ) ) &&
            (  this->isNodeAvailable( lock, node_index ) ) &&
            ( !st::Map_ordered_vec_empty( this->m_node_idx_to_def_set_ids,
                node_index ) ) );

        SIXTRL_ASSERT( ( !is_default_for_any ) ||
            ( node_index != _store_t::UNDEFINED_INDEX ) );

        return is_default_for_any;
    }

    _store_t::node_set_id_t const* NodeStore::defaultNodeSetIdsBegin(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const idx ) const SIXTRL_NOEXCEPT
    {
        _store_t::node_set_id_t const* ptr_begin = ( this->checkLock( lock ) )
            ? st::Map_ordered_vec_begin( this->m_node_idx_to_def_set_ids, idx )
            : nullptr;

        SIXTRL_ASSERT( ( ptr_begin == nullptr ) ||
            ( ( idx != _store_t::UNDEFINED_INDEX ) &&
              ( this->isNodeAvailable( lock, idx ) ) &&
              ( this->isNodeAttachedToAnySet( lock, idx ) ) &&
              ( this->isNodeDefaultForAnySet( lock, idx ) ) ) );

        return ptr_begin;
    }

    _store_t::node_set_id_t const* NodeStore::defaultNodeSetIdsEnd(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const idx ) const SIXTRL_NOEXCEPT
    {
        _store_t::node_set_id_t const* ptr_end = ( this->checkLock( lock ) )
            ? st::Map_ordered_vec_end( this->m_node_idx_to_def_set_ids, idx )
            : nullptr;

        SIXTRL_ASSERT( ( ptr_end == nullptr ) ||
            ( ( idx != _store_t::UNDEFINED_INDEX ) &&
              ( this->isNodeAvailable( lock, idx ) ) &&
              ( this->isNodeAttachedToAnySet( lock, idx ) ) &&
              ( this->isNodeDefaultForAnySet( lock, idx ) ) ) );

        return ptr_end;
    }

    _store_t::size_type NodeStore::numSetsHavingNodeAsDefault(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        _store_t::size_type num_sets = _store_t::size_type{ 0 };

        if( ( this->isNodeAvailable( lock, index ) ) &&
            ( st::Map_has_key( this->m_node_idx_to_def_set_ids, index ) ) )
        {
            SIXTRL_ASSERT( index != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            num_sets = st::Map_ordered_vec_size(
                this->m_node_idx_to_def_set_ids, index );

            SIXTRL_ASSERT( ( num_sets == _store_t::size_type{ 0 } ) ||
                ( ( this->numNodeSets( lock ) > _store_t::size_type{ 0 } ) &&
                  ( this->isNodeDefaultForAnySet( lock, index ) ) ) );
        }

        return num_sets;
    }

    /* --------------------------------------------------------------------- */

    _store_t::sync_id_value_t NodeStore::registerChange(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        _store_t::sync_id_value_t current_value = this->m_sync_id.load();

        if( this->checkLock( lock ) )
        {
            if( current_value < _store_t::LAST_LEGAL_SYNC_ID_VALUE )
            {
                ++this->m_sync_id;
            }
            else if( current_value != _store_t::ILLEGAL_SYNC_ID_VALUE )
            {
                this->m_sync_id.store( _store_t::sync_id_value_t{ 0 } );
            }
        }

        return current_value;
    }

    /* ===================================================================== */

    NodeStore::node_index_t NodeStore::doAddNode(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::ptr_stored_node_info_t&& ptr_node_info )
    {
        using arch_id_t = _store_t::arch_id_t;
        using platform_id_t = _store_t::platform_id_t;

        _store_t::node_index_t index = _store_t::UNDEFINED_INDEX;

        if( ( this->checkLock( lock ) ) &&
            ( ptr_node_info.get() != nullptr ) &&
            ( ( ptr_node_info->ptrNodeStore() == nullptr ) ||
              ( ptr_node_info->ptrNodeStore() == this ) ) )
        {
            _store_t::arch_platform_to_devices_t& arch_plfm_devices_map =
                    this->m_arch_platform_to_devices;

            arch_id_t     arch_id     = _store_t::ARCH_ILLEGAL;
            platform_id_t platform_id = _store_t::ILLEGAL_PLATFORM_ID;
            device_id_t   device_id   = _store_t::ILLEGAL_DEVICE_ID;
            node_index_t  current_node_index = _store_t::UNDEFINED_INDEX;
            bool new_node_id = false;

            if( ( ptr_node_info->ptrNodeStore() == nullptr ) &&
                ( ptr_node_info->nodeIndex() == _store_t::UNDEFINED_INDEX ) )
            {
                arch_id = ptr_node_info->archId();
                platform_id = ptr_node_info->platformId();
                device_id = ptr_node_info->deviceId();
                current_node_index = ptr_node_info->nodeIndex();
            }
            else if( ptr_node_info->ptrNodeStore() == this )
            {
                arch_id = ptr_node_info->archId( lock );
                platform_id = ptr_node_info->platformId( lock );
                device_id = ptr_node_info->deviceId( lock );
                current_node_index = ptr_node_info->nodeIndex( lock );
            }

            if( arch_id != _store_t::ARCH_ILLEGAL )
            {
                _store_t::status_t status = st::ARCH_STATUS_SUCCESS;

                if( !this->hasArchitecture( lock, arch_id ) )
                {
                    status = this->doAddArchitecture( lock, arch_id );
                }

                if( ( status      == st::ARCH_STATUS_SUCCESS ) &&
                    ( platform_id == _store_t::ILLEGAL_PLATFORM_ID ) &&
                    ( device_id   == _store_t::ILLEGAL_DEVICE_ID ) )
                {
                    platform_id = this->doGetNextPlatformId( lock, arch_id );

                    if( platform_id != _store_t::ILLEGAL_PLATFORM_ID )
                    {
                        status = ptr_node_info->setPlatformId(
                            lock, platform_id );
                        new_node_id = true;
                    }
                }

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( platform_id != _store_t::ILLEGAL_PLATFORM_ID ) &&
                    ( device_id   == _store_t::ILLEGAL_DEVICE_ID   ) )
                {
                    if( !this->hasPlatform( lock, arch_id, platform_id ) )
                    {
                        new_node_id = true;
                        status = this->doAddPlatform(
                            lock, arch_id, platform_id );
                    }
                }

                auto const arch_pflm = std::make_pair( arch_id, platform_id );

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( device_id == _store_t::ILLEGAL_DEVICE_ID ) &&
                    ( st::Map_has_key( arch_plfm_devices_map, arch_pflm ) ) )
                {
                    device_id = this->doGetNextDeviceId(
                        lock, arch_id, platform_id );

                    if( device_id != _store_t::ILLEGAL_DEVICE_ID )
                    {
                        new_node_id = true;
                        status = ptr_node_info->setDeviceId( lock, device_id );
                    }
                }
                else if(
                    ( !st::Map_has_key( arch_plfm_devices_map, arch_pflm ) ) &&
                    ( device_id == _store_t::ILLEGAL_DEVICE_ID ) )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }

                _store_t::node_id_t const node_id(
                    arch_id, platform_id, device_id );

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( node_id.valid() ) )
                {
                    auto it = this->m_node_id_to_node_index.find( node_id );

                    if( ( new_node_id ) &&
                        ( it == this->m_node_id_to_node_index.end() ) &&
                        ( current_node_index == _store_t::UNDEFINED_INDEX ) &&
                        ( !st::Map_ordered_vec_has_value( arch_plfm_devices_map,
                            arch_pflm, device_id ) ) )
                    {
                        index  = this->m_stored_node_infos.size();

                        status = this->doPrepareNewNodeIndex(
                            lock, node_id, index );

                        if( status == st::ARCH_STATUS_SUCCESS )
                        {
                            if( ptr_node_info->ptrNodeStore() == nullptr )
                            {
                                status = ptr_node_info->assignToNodeStore(
                                    *this );
                            }

                            SIXTRL_ASSERT( ptr_node_info->ptrNodeStore() ==
                                           this );

                            if( status == st::ARCH_STATUS_SUCCESS )
                            {
                                status = ptr_node_info->setNodeIndex(
                                    lock, index );
                            }

                            if( status == st::ARCH_STATUS_SUCCESS )
                            {
                                this->m_stored_node_infos.emplace_back(
                                    std::move( ptr_node_info ) );
                            }
                        }

                        if( status != st::ARCH_STATUS_SUCCESS )
                        {
                            index = _store_t::UNDEFINED_INDEX;
                        }
                    }
                    else if( ( !new_node_id ) &&
                        ( ptr_node_info->ptrNodeStore() == this ) &&
                        ( st::Map_ordered_vec_has_value( arch_plfm_devices_map,
                            arch_pflm, device_id ) ) &&
                        ( it != this->m_node_id_to_node_index.end() ) &&
                        ( ( ( current_node_index == _store_t::UNDEFINED_INDEX ) &&
                            ( it->second != _store_t::UNDEFINED_INDEX ) ) ||
                          ( ( current_node_index != _store_t::UNDEFINED_INDEX ) &&
                            ( it->second == current_node_index ) ) ) &&
                        ( this->m_stored_node_infos.size() > static_cast<
                            _store_t::size_type >( it->second ) ) &&
                        ( this->m_stored_node_infos[ it->second ].get() !=
                            nullptr ) &&
                        ( node_id == this->m_stored_node_infos[ it->second
                            ]->nodeId( lock ) ) )
                    {
                        SIXTRL_ASSERT( ptr_node_info.get() !=
                            this->m_stored_node_infos[ it->second ].get() );

                        status = ptr_node_info->setNodeIndex( lock, it->second );

                        if( status == st::ARCH_STATUS_SUCCESS )
                        {
                            this->m_stored_node_infos[ it->second ] = std::move(
                                ptr_node_info );

                            index = it->second;
                        }
                    }
                }
            }
        }

        return index;
    }

    _store_t::status_t NodeStore::doRemoveNode(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const idx )
    {
        using nidx_nset_map_t = _store_t::node_index_to_node_set_ids_t;

        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        auto ptr_node = this->ptrNodeInfoBase( lock, idx );

        if( ( ptr_node != nullptr ) && ( ptr_node->ptrNodeStore() == this ) &&
            ( ptr_node->nodeId( lock ).valid() ) &&
            ( ( ptr_node->nodeIndex( lock ) == idx ) ||
              ( ptr_node->nodeIndex( lock ) == _store_t::UNDEFINED_INDEX ) ) &&
            ( st::Map_has_key( this->m_node_idx_to_set_ids, idx ) ) &&
            ( st::Map_has_value_for_key( this->m_node_id_to_node_index,
                ptr_node->nodeId( lock ), idx ) ) &&
            ( this->m_num_node_infos > _store_t::size_type{ 0 }  ) )
        {
            SIXTRL_ASSERT( idx != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->checkLock( lock ) );
            status = this->detachNodeFromAllSets( lock, idx );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( ptr_node->nodeIndex( lock ) != _store_t::UNDEFINED_INDEX ) )
            {
                status = ptr_node->setNodeIndex(
                    lock, _store_t::UNDEFINED_INDEX );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                nidx_nset_map_t& nidx_nsets = this->m_node_idx_to_set_ids;
                nidx_nset_map_t& nidx_sel_nsets = this->m_node_idx_to_sel_set_ids;
                nidx_nset_map_t& nidx_def_nsets = this->m_node_idx_to_def_set_ids;

                SIXTRL_ASSERT( st::Map_has_key( nidx_nsets, idx ) );
                SIXTRL_ASSERT( st::Map_ordered_vec_empty( nidx_nsets, idx ) );
                SIXTRL_ASSERT( st::Map_has_key( nidx_sel_nsets, idx ) );
                SIXTRL_ASSERT( st::Map_ordered_vec_empty( nidx_sel_nsets, idx ) );
                SIXTRL_ASSERT( st::Map_has_key( nidx_def_nsets, idx ) );
                SIXTRL_ASSERT( st::Map_ordered_vec_empty( nidx_def_nsets, idx ) );

                nidx_sel_nsets.erase( idx );
                nidx_def_nsets.erase( idx );
                nidx_nsets.erase( idx );

                auto const arch_plfm_pair = std::make_pair(
                    ptr_node->archId( lock ), ptr_node->platformId( lock ) );

                status = st::Map_remove_value_from_ordered_vec(
                    this->m_arch_platform_to_devices, arch_plfm_pair,
                        ptr_node->deviceId( lock ) );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    this->m_node_id_to_node_index.erase(
                        ptr_node->nodeId( lock ) );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = ptr_node->detachFromNodeStore( lock );
                    this->m_stored_node_infos[ idx ].reset( nullptr );
                    ptr_node = nullptr;
                }

                this->registerChange( lock );
            }
        }

        return status;
    }

    NodeStore::status_t NodeStore::doClear(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->checkLock( lock ) )
        {
            this->doClearWithoutLocking();
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _store_t::status_t NodeStore::doMarkNodeAsSelectedBySet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index,
        _store_t::node_set_id_t const node_set_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        auto ptr_node = this->ptrNodeInfoBase( lock, index );

        if( ( ptr_node != nullptr ) &&
            ( this->hasNodeSet( lock, node_set_id ) ) &&
            ( this->isNodeAttachedToSet( lock, index, node_set_id ) ) &&
            ( !this->isNodeSelectedBySet( lock, index, node_set_id ) ) &&
            ( ptr_node->maxSelectionCount() > st::Map_ordered_vec_size(
                this->m_node_idx_to_sel_set_ids, index ) ) )
        {
            SIXTRL_ASSERT( index != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( this->isNodeAvailable( lock, index ) );

            SIXTRL_ASSERT(  st::Map_has_key(
                this->m_node_idx_to_sel_set_ids, index ) );

            SIXTRL_ASSERT( !st::Map_ordered_vec_has_value(
                this->m_node_idx_to_sel_set_ids, index, node_set_id ) );

            SIXTRL_ASSERT(  st::Map_has_key(
                this->m_node_set_to_sel_node_idxs, node_set_id ) );

            SIXTRL_ASSERT( !st::Map_ordered_vec_has_value(
                this->m_node_set_to_sel_node_idxs, node_set_id, index ) );

            status = st::Map_ordered_vec_insert_value(
                this->m_node_idx_to_sel_set_ids, index, node_set_id );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::Map_ordered_vec_insert_value(
                    this->m_node_set_to_sel_node_idxs, node_set_id, index );
            }

            this->registerChange( lock );
        }

        SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
            ( this->isNodeSelectedBySet( lock, index, node_set_id ) ) );

        return status;
    }

    _store_t::status_t NodeStore::doUnselectNodeFromSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index,
        _store_t::node_set_id_t const node_set_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->isNodeSelectedBySet( lock, index, node_set_id ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( index != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->isNodeAvailable( lock, index ) );
            SIXTRL_ASSERT( this->hasNodeSet( lock, node_set_id ) );
            SIXTRL_ASSERT( this->isNodeAttachedToSet(
                lock, index, node_set_id ) );

            SIXTRL_ASSERT( st::Map_has_key(
                this->m_node_idx_to_set_ids, index ) );

            SIXTRL_ASSERT( st::Map_has_key(
                this->m_node_idx_to_sel_set_ids, index ) );

            SIXTRL_ASSERT( st::Map_ordered_vec_has_value(
                this->m_node_idx_to_sel_set_ids, index, node_set_id ) );

            SIXTRL_ASSERT( st::Map_has_key(
                this->m_node_set_to_node_idxs, node_set_id ) );

            SIXTRL_ASSERT( st::Map_has_key(
                this->m_node_set_to_sel_node_idxs, node_set_id ) );

            SIXTRL_ASSERT( st::Map_ordered_vec_has_value(
                m_node_set_to_sel_node_idxs, node_set_id, index ) );

            status = st::Map_remove_value_from_ordered_vec(
                this->m_node_set_to_sel_node_idxs, node_set_id, index );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    this->m_node_idx_to_sel_set_ids, index, node_set_id );
            }

            this->registerChange( lock );
        }

        SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
            ( (  this->isNodeAttachedToSet( lock, index, node_set_id ) ) &&
              ( !this->isNodeSelectedBySet( lock, index, node_set_id ) ) ) );

        return status;
    }

    _store_t::status_t NodeStore::doMarkNodeAsDefaultForSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const index,
        _store_t::node_set_id_t const node_set_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        auto ptr_set = this->ptrNodeSetBase( lock, node_set_id );

        if( ( ptr_set != nullptr ) && ( ptr_set->ptrNodeStore() == this ) &&
            ( this->isNodeAvailable( lock, index ) ) &&
            ( this->isNodeAttachedToSet( lock, index, node_set_id ) ) &&
            ( !this->isNodeDefaultForSet( lock, index, node_set_id ) ) )
        {
            SIXTRL_ASSERT( index != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( this->hasNodeSet( lock, node_set_id ) );

            SIXTRL_ASSERT(  st::Map_has_key(
                this->m_node_idx_to_def_set_ids, index ) );

            SIXTRL_ASSERT( !st::Map_ordered_vec_has_value(
                this->m_node_idx_to_def_set_ids, index, node_set_id ) );

            SIXTRL_ASSERT(  st::Map_has_key(
                this->m_node_set_to_def_node_idxs, node_set_id ) );

            SIXTRL_ASSERT( !st::Map_ordered_vec_has_value(
                this->m_node_set_to_def_node_idxs, node_set_id, index ) );

            if( ptr_set->maxNumDefaultNodes() > st::Map_ordered_vec_size(
                    this->m_node_set_to_def_node_idxs, node_set_id ) )
            {
                SIXTRL_ASSERT( this->canNodeBeMadeDefaultForSet( lock,
                    index, node_set_id ) );

                status = st::Map_ordered_vec_insert_value(
                    this->m_node_idx_to_def_set_ids, index, node_set_id );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::Map_ordered_vec_insert_value(
                        this->m_node_set_to_def_node_idxs, node_set_id, index );
                }

                this->registerChange( lock );
            }
        }

        SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
            ( this->isNodeDefaultForSet( lock, index, node_set_id ) ) );

        return status;
    }

    _store_t::status_t NodeStore::doRemoveDefaultNodeFromSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const node_index,
        _store_t::node_set_id_t const node_set_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->isNodeDefaultForSet( lock, node_index, node_set_id ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( node_index != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->isNodeAvailable( lock, node_index ) );
            SIXTRL_ASSERT( this->hasNodeSet( lock, node_set_id ) );
            SIXTRL_ASSERT( this->isNodeAttachedToSet(
                lock, node_index, node_set_id ) );

            SIXTRL_ASSERT( st::Map_has_key(
                this->m_node_idx_to_set_ids, node_index ) );

            SIXTRL_ASSERT( st::Map_has_key(
                this->m_node_idx_to_def_set_ids, node_index ) );

            SIXTRL_ASSERT( st::Map_ordered_vec_has_value(
                this->m_node_idx_to_def_set_ids, node_index, node_set_id ) );

            SIXTRL_ASSERT( st::Map_has_key(
                this->m_node_set_to_node_idxs, node_set_id ) );

            SIXTRL_ASSERT( st::Map_has_key(
                this->m_node_set_to_def_node_idxs, node_set_id ) );

            SIXTRL_ASSERT( st::Map_ordered_vec_has_value(
                this->m_node_set_to_def_node_idxs, node_set_id, node_index ) );

            SIXTRL_ASSERT( st::Map_ordered_vec_size(
                this->m_node_set_to_def_node_idxs, node_set_id ) <=
                this->ptrNodeSetBase( lock, node_set_id )->maxNumDefaultNodes() );

            SIXTRL_ASSERT( st::Map_ordered_vec_size(
                this->m_node_idx_to_def_set_ids, node_index ) >
                    _store_t::size_type{ 0 } );

            status = st::Map_remove_value_from_ordered_vec(
                this->m_node_set_to_def_node_idxs, node_set_id, node_index );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    this->m_node_idx_to_def_set_ids, node_index, node_set_id );
            }

            this->registerChange( lock );
        }

        return status;
    }

    _store_t::status_t NodeStore::doUpdateNodeIdToIndexMap(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_id_t const& SIXTRL_RESTRICT_REF current_node_id,
        _store_t::node_index_t const node_index,
        _store_t::node_id_t const& SIXTRL_RESTRICT_REF new_node_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        auto ptr_node = this->ptrNodeInfoBase( lock, node_index );

        if( ( new_node_id.valid() ) &&
            ( ptr_node != nullptr ) && ( ptr_node->ptrNodeStore() == this ) &&
            ( ( ptr_node->nodeIndex( lock ) == node_index ) ||
              ( ptr_node->nodeIndex( lock ) == _store_t::UNDEFINED_INDEX ) ) &&
            ( st::Map_has_key( this->m_node_id_to_node_index,
                       ptr_node->nodeId( lock ) ) ) &&
            ( st::Map_has_value_for_key( this->m_node_id_to_node_index,
                ptr_node->nodeId( lock ), node_index ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( this->isNodeAvailable( lock, node_index ) );

            status = st::ARCH_STATUS_SUCCESS;

            if( new_node_id != current_node_id )
            {
                status = ( !st::Map_has_key( this->m_node_id_to_node_index,
                             new_node_id ) )
                    ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                   this->m_node_id_to_node_index.erase( current_node_id );

                   auto res = this->m_node_id_to_node_index.emplace(
                       std::make_pair( new_node_id, node_index ) );

                   if( !res.second )
                   {
                       status = st::ARCH_STATUS_GENERAL_FAILURE;
                   }
                }
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( ( st::Map_has_key( this->m_node_id_to_node_index,
                         new_node_id ) ) &&
                  ( st::Map_has_value_for_key( this->m_node_id_to_node_index,
                         new_node_id, node_index ) ) ) );

        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _store_t::status_t NodeStore::doAddArchitecture(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::arch_id_t const arch_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( arch_id != _store_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) &&
            ( !this->hasArchitecture( lock, arch_id ) ) )
        {
            auto res = this->m_arch_to_platforms.emplace(
                std::make_pair( arch_id, _store_t::platforms_list_t{} ) );

            if( res.second ) status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _store_t::platform_id_t NodeStore::doGetNextPlatformId(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::arch_id_t const arch_id )
    {
        _store_t::platform_id_t platform_id = _store_t::ILLEGAL_PLATFORM_ID;

        if( this->hasArchitecture( lock, arch_id ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( arch_id != _store_t::ARCH_ILLEGAL );
            SIXTRL_ASSERT( st::Map_has_key(
                this->m_arch_to_platforms, arch_id ) );

            SIXTRL_ASSERT( !st::Map_ordered_vec_has_value(
                this->m_arch_to_platforms, arch_id,
                    _store_t::ILLEGAL_PLATFORM_ID ) );

            auto it = this->m_arch_to_platforms.find( arch_id );
            SIXTRL_ASSERT( it != this->m_arch_to_platforms.end() );

            platform_id = ( it->second.empty() ) ? _store_t::platform_id_t{ 0 }
                : it->second.back() + _store_t::platform_id_t{ 1 };

            SIXTRL_ASSERT( !st::Map_ordered_vec_has_value(
                this->m_arch_to_platforms, arch_id, platform_id ) );
        }

        return platform_id;
    }

    _store_t::status_t NodeStore::doAddPlatform(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        auto const arch_platform_pair = std::make_pair( arch_id, platform_id );

        if( ( platform_id != _store_t::ILLEGAL_PLATFORM_ID ) &&
            ( this->hasArchitecture( lock, arch_id ) ) &&
            ( !st::Map_ordered_vec_has_value( this->m_arch_to_platforms,
                arch_id, platform_id ) ) &&
            ( !st::Map_has_key( this->m_arch_platform_to_devices,
                    arch_platform_pair ) ) )
        {
            status = st::Map_ordered_vec_insert_value(
                this->m_arch_to_platforms, arch_id, platform_id );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                auto res = this->m_arch_platform_to_devices.emplace(
                    std::make_pair( arch_platform_pair,
                        _store_t::devices_list_t{} ) );

                if( !res.second ) status = st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        return status;
    }

    _store_t::device_id_t NodeStore::doGetNextDeviceId(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::arch_id_t const arch_id, platform_id_t const platform_id )
    {
        _store_t::device_id_t device_id = _store_t::ILLEGAL_DEVICE_ID;

        if( ( this->hasArchitecture( lock, arch_id ) ) &&
            ( this->hasPlatform( lock, arch_id, platform_id ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( arch_id != _store_t::ARCH_ILLEGAL );
            SIXTRL_ASSERT( platform_id != _store_t::ILLEGAL_PLATFORM_ID );

            auto it = this->m_arch_platform_to_devices.find(
                std::make_pair( arch_id, platform_id ) );

            if( it != this->m_arch_platform_to_devices.end() )
            {
                SIXTRL_ASSERT( std::is_sorted(
                    it->second.begin(), it->second.end() ) );

                SIXTRL_ASSERT( !std::binary_search( it->second.begin(),
                    it->second.end(), _store_t::ILLEGAL_DEVICE_ID ) );

                device_id = ( it->second.empty() ) ? _store_t::device_id_t{ 0 }
                    : ( it->second.back() + _store_t::device_id_t{ 1 } );
            }
        }

        return device_id;
    }

    _store_t::status_t NodeStore::doPrepareNewNodeIndex(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        _store_t::node_index_t const node_index )
    {
        using nidx_nset_map_t = _store_t::node_index_to_node_set_ids_t;
        using nidxs_list_t    = _store_t::node_indices_list_t;
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        auto const arch_plfm_pair = std::make_pair(
            node_id.archId(), node_id.platformId() );

        nidx_nset_map_t& nidx_to_nsets  = this->m_node_idx_to_set_ids;
        nidx_nset_map_t& nidx_to_sel_nsets = this->m_node_idx_to_sel_set_ids;
        nidx_nset_map_t& nidx_to_def_nsets = this->m_node_idx_to_def_set_ids;

        if( ( node_id.valid() ) && ( node_index != _store_t::UNDEFINED_INDEX ) &&
            ( this->hasArchitecture( lock, node_id.archId() ) ) &&
            ( !st::Map_has_key( nidx_to_nsets, node_index ) ) &&
            ( !st::Map_has_key( nidx_to_sel_nsets, node_index ) ) &&
            ( !st::Map_has_key( nidx_to_def_nsets, node_index ) ) &&
            ( !st::Map_has_key( this->m_node_id_to_node_index, node_id ) ) &&
            (  st::Map_has_key( this->m_arch_platform_to_devices, arch_plfm_pair ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            _store_t::device_id_t const device_id = node_id.deviceId();
            SIXTRL_ASSERT( device_id != _store_t::ILLEGAL_DEVICE_ID );

            status = st::Map_ordered_vec_insert_value(
                this->m_arch_platform_to_devices, arch_plfm_pair, device_id );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                auto res1 = this->m_node_idx_to_set_ids.emplace(
                    std::make_pair( node_index, nidxs_list_t{} ) );

                auto res2 = this->m_node_idx_to_sel_set_ids.emplace(
                    std::make_pair( node_index, nidxs_list_t{} ) );

                auto res3 = this->m_node_idx_to_def_set_ids.emplace(
                    std::make_pair( node_index, nidxs_list_t{} ) );

                auto res4 = this->m_node_id_to_node_index.insert(
                    std::make_pair( node_id, node_index ) );

                if( ( !res1.second ) || ( !res2.second ) ||
                    ( !res3.second ) || ( !res4.second ) )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    void NodeStore::doClearWithoutLocking() SIXTRL_NOEXCEPT
    {
        this->m_arch_to_platforms.clear();

        this->m_node_idx_to_set_ids.clear();
        this->m_node_idx_to_sel_set_ids.clear();
        this->m_node_idx_to_def_set_ids.clear();

        this->m_node_set_to_node_idxs.clear();
        this->m_node_set_to_sel_node_idxs.clear();
        this->m_node_set_to_def_node_idxs.clear();

        this->m_node_id_to_node_index.clear();

        this->m_stored_node_infos.clear();
        this->m_stored_node_sets.clear();

        this->m_num_node_infos = _store_t::size_type{ 0 };
        this->m_num_node_sets  = _store_t::size_type{ 0 };
    }
}

#endif /* C++, Host */

/* end: sixtracklib/common/control/node_store.cpp */
