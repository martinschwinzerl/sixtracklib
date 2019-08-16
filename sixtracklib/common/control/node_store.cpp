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
    #include "sixtracklib/common/control/controller_base.hpp"
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
        m_arch_platform_to_platform_name(),
        m_arch_platform_name_to_platform_id(),
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
        m_arch_platform_to_platform_name(),
        m_arch_platform_name_to_platform_id(),
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
        m_arch_platform_to_platform_name(),
        m_arch_platform_name_to_platform_id(),
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

            this->m_arch_platform_to_platform_name =
                other.m_arch_platform_to_platform_name;

            this->m_arch_platform_name_to_platform_id =
                other.m_arch_platform_name_to_platform_id;

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

            this->m_arch_platform_to_platform_name =
                std::move( other.m_arch_platform_to_platform_name );

            this->m_arch_platform_name_to_platform_id =
                std::move( other.m_arch_platform_name_to_platform_id );

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

    bool NodeStore::hasPlatform(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF name ) const SIXTRL_NOEXCEPT
    {
        return this->hasPlatform( lock, arch_id,
            this->platformIdByName( lock, arch_id, name ) );
    }

    bool NodeStore::hasPlatformName(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::arch_id_t const arch_id,
        _store_t::platform_id_t const platform_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasPlatform( lock, arch_id, platform_id ) ) &&
                 ( st::Map_has_key( this->m_arch_platform_to_platform_name,
                    std::make_pair( arch_id, platform_id ) ) ) );
    }

    std::string const& NodeStore::platformNameByPlatformId(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id,
        _store_t::platform_id_t const platform_id ) const
    {
        if( !this->checkLock( lock ) )
        {
            throw std::runtime_error( "lock handle is not properly locked" );
        }

        auto it = this->m_arch_platform_to_platform_name.end();

        if( this->hasPlatform( lock, arch_id, platform_id ) )
        {
            it = this->m_arch_platform_to_platform_name.find(
                std::make_pair( arch_id, platform_id ) );
        }

        if( it == this->m_arch_platform_to_platform_name.end() )
        {
            throw std::runtime_error( "no platform name alias available" );
        }

        return it->second;
    }

    char const* NodeStore::ptrPlatformNameByPlatformId(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::arch_id_t const arch_id,
        _store_t::platform_id_t const platform_id ) const SIXTRL_NOEXCEPT
    {
        char const* ptr_platform_name = nullptr;

        if( this->hasPlatform( lock, arch_id, platform_id ) )
        {
            auto it = this->m_arch_platform_to_platform_name.find(
                std::make_pair( arch_id, platform_id ) );

            if( it != this->m_arch_platform_to_platform_name.end() )
            {
                ptr_platform_name = it->second.c_str();
            }
        }

        return ptr_platform_name;
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

    NodeStore::platform_id_t NodeStore::platformIdByName(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF
            platform_name ) const SIXTRL_NOEXCEPT
    {
        _store_t::platform_id_t platform_id = _store_t::ILLEGAL_PLATFORM_ID;

        if( ( this->hasArchitecture( lock, arch_id ) ) &&
            ( !platform_name.empty() ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = this->m_arch_platform_name_to_platform_id.find(
                std::make_pair( arch_id, platform_name ) );

            if( it != this->m_arch_platform_name_to_platform_id.end() )
            {
                platform_id = it->second;

                if( platform_id != _store_t::ILLEGAL_PLATFORM_ID )
                {
                    auto name_it = this->m_arch_platform_to_platform_name.find(
                        std::make_pair( arch_id, platform_id ) );

                    if( name_it != this->m_arch_platform_to_platform_name.end() )
                    {
                        if( name_it->second.compare( platform_name ) != 0 )
                        {
                            platform_id = _store_t::ILLEGAL_PLATFORM_ID;
                        }
                    }
                }
            }
        }

        return platform_id;
    }

    _store_t::status_t NodeStore::addPlatformNameMapping(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->hasArchitecture( lock, arch_id ) ) &&
            ( platform_id != NodeStore::ILLEGAL_PLATFORM_ID ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto name_it = this->m_arch_platform_to_platform_name.find(
                std::make_pair( arch_id, platform_id ) );

            if( name_it != this->m_arch_platform_to_platform_name.end() )
            {
                std::string const old_platform_name = name_it->second;

                auto pid_it = this->m_arch_platform_name_to_platform_id.find(
                    std::make_pair( arch_id, old_platform_name ) );

                if( pid_it != this->m_arch_platform_name_to_platform_id.end() )
                {
                    this->m_arch_platform_name_to_platform_id.erase( pid_it );

                    if( !platform_name.empty() )
                    {
                        name_it->second = platform_name;
                        auto arch_platform_name =
                            std::make_pair( arch_id, platform_name );

                        auto res =
                        this->m_arch_platform_name_to_platform_id.emplace(
                            std::make_pair( arch_platform_name, platform_id ) );

                        if( res.second )
                        {
                            status = st::ARCH_STATUS_SUCCESS;
                        }
                    }
                    else
                    {
                        this->m_arch_platform_to_platform_name.erase( name_it );
                        status = st::ARCH_STATUS_SUCCESS;
                    }
                }
            }
            else if( !platform_name.empty() )
            {
                /* Have not found a (archid,platformid) -> name mapping;
                 * verify that there is also no inverse mapping! */

                auto temp_it = this->m_arch_platform_name_to_platform_id.begin();
                auto temp_end = this->m_arch_platform_name_to_platform_id.end();
                auto found_entry = temp_end;

                for( ; temp_it != temp_end ; ++temp_it )
                {
                    if( ( temp_it->first.first == arch_id ) &&
                        ( temp_it->second == platform_id ) )
                    {
                        found_entry = temp_it;
                    }
                }

                if( found_entry == temp_end )
                {
                    /* Nothing found, so it's safe to insert the mappings */

                    auto res1 = this->m_arch_platform_to_platform_name.insert(
                        std::make_pair( std::make_pair( arch_id, platform_id ),
                            platform_name ) );

                    auto res2 =
                    this->m_arch_platform_name_to_platform_id.insert(
                        std::make_pair( std::make_pair( arch_id, platform_name),
                                        platform_id ) );

                    if( ( res2.second ) && ( res1.second ) )
                    {
                        status = st::ARCH_STATUS_SUCCESS;
                    }
                }
            }
        }

        return status;
    }

    _store_t::status_t NodeStore::addPlatformNameMapping(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        char const* SIXTRL_RESTRICT platform_name )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( arch_id != _store_t::ARCH_ILLEGAL ) &&
            ( platform_id != _store_t::ILLEGAL_PLATFORM_ID ) &&
            ( platform_name != nullptr ) &&
            ( this->checkLock( lock ) ) &&
            ( this->hasArchitecture( lock, arch_id ) ) &&
            ( this->hasPlatform( lock, arch_id, platform_id ) ) )
        {
            auto const arch_plfm_name = std::make_pair(
                arch_id, std::string{ platform_name } );

            if( st::Map_has_value_for_key(
                    this->m_arch_platform_name_to_platform_id,
                        arch_plfm_name, platform_id ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
            else
            {
                auto res = this->m_arch_platform_name_to_platform_id.insert(
                    std::make_pair( arch_plfm_name, platform_id ) );

                if( res.second ) status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
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

        if( this->hasArchitecture( lock, arch_id ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            num_nodes = st::Map_ordered_vec_size(
                this->m_arch_to_platforms, arch_id );
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
        using size_t = _store_t::size_type;
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
        using node_idx_map_t = _store_t::node_index_to_node_set_ids_t;

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

            if( ( !st::Map_ordered_vec_has_value(
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
            }
        }

        return status;
    }

    _store_t::status_t NodeStore::attachAllArchitectureNodesToSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::arch_id_t const arch_id, node_set_id_t const node_set_id )
    {
        using size_t = _store_t::size_type;
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
        _store_t::node_index_t const node_index,
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
            ( this->isNodeAvailable( lock, node_index ) ) &&
            ( st::Map_has_key( nset_to_idx, node_set_id ) ) &&
            ( st::Map_has_key( nidx_to_nsets, node_index ) ) )
        {
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( node_index  != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto ptr_node = this->ptrNodeInfoBase( lock, node_index );
            SIXTRL_ASSERT( ptr_node != nullptr );
            SIXTRL_ASSERT( ptr_node->ptrNodeStore() == this );
            SIXTRL_ASSERT( ptr_node->nodeIndex( lock ) == node_index );
            SIXTRL_ASSERT( ptr_node->nodeId( lock ).valid() );

            if( !st::Map_has_key( this->m_node_id_to_node_index,
                            ptr_node->nodeId( lock ) ) )
            {
                return status;
            }

            SIXTRL_ASSERT( st::Map_has_key( nset_to_sel_idx, node_set_id ) );
            SIXTRL_ASSERT( st::Map_has_key( nset_to_def_idx, node_set_id ) );

            SIXTRL_ASSERT( st::Map_has_key( nidx_to_sel_nsets, node_index ) );
            SIXTRL_ASSERT( st::Map_has_key( nidx_to_def_nsets, node_index ) );

            status = st::Map_remove_value_from_ordered_vec(
                nset_to_idx, node_set_id, node_index );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    nidx_to_nsets, node_index, node_set_id );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                this->registerChange( lock );
            }

            if( st::Map_ordered_vec_has_value(
                    nset_to_def_idx, node_set_id, node_index ) )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    nset_to_def_idx, node_set_id, node_index );
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::Map_ordered_vec_has_value(
                    nset_to_sel_idx, node_set_id, node_index )
                ) )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    nset_to_sel_idx, node_set_id, node_index );
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::Map_ordered_vec_has_value(
                    nidx_to_def_nsets, node_index, node_set_id ) ) )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    nidx_to_def_nsets, node_index, node_set_id );
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::Map_ordered_vec_has_value(
                    nidx_to_sel_nsets, node_index, node_set_id ) ) )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    nidx_to_sel_nsets, node_index, node_set_id );
            }
        }

        SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
            ( !this->isNodeAttachedToSet( lock, node_index, node_set_id ) ) );

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
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = nset_to_idx.find( node_set_id );
            SIXTRL_ASSERT( it != nset_to_idx.end() );

            status = st::ARCH_STATUS_SUCCESS;

            if( !it->second.empty() )
            {
                std::vector< node_index_t > const node_indices( it->second );

                for( auto const node_index : node_indices )
                {
                    status = this->detachNodeFromSet(
                        lock, node_index, node_set_id );

                    if( status != st::ARCH_STATUS_SUCCESS )
                    {
                        break;
                    }
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

                    if( status != st::ARCH_STATUS_SUCCESS )
                    {
                        break;
                    }
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
        _store_t::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        bool can_be_selected_by_set = false;

        auto ptr_node = this->ptrNodeInfoBase( lock, node_index );
        auto ptr_set  = this->ptrNodeSetBase( lock, node_set_id );

        if( ( ptr_node != nullptr ) && ( ptr_node->ptrNodeStore() == this ) &&
            ( ptr_set  != nullptr ) && ( ptr_set->ptrNodeStore() == this ) &&
            ( st::Map_ordered_vec_has_value( this->m_node_set_to_node_idxs,
                node_set_id, node_index ) ) &&
            ( st::Map_ordered_vec_has_value( this->m_node_idx_to_set_ids,
                node_index, node_set_id ) ) )
        {
            SIXTRL_ASSERT( node_index  != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = this->m_node_idx_to_sel_set_ids.find( node_index );
            if( ( it != this->m_node_idx_to_sel_set_ids.end() ) &&
                ( it->second.size() < ptr_node->maxSelectionCount() ) )
            {
                can_be_selected_by_set = true;
            }
        }

        return can_be_selected_by_set;
    }

    bool NodeStore::isNodeSelectedBySet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const node_index,
        _store_t::node_set_id_t const node_set_id )
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
                this->m_node_set_to_def_node_idxs, node_set_id, node_index ) );

            SIXTRL_ASSERT( st::Map_ordered_vec_has_value(
                this->m_node_idx_to_set_ids, node_index, node_set_id ) );

            is_selected_by_set = true;
        }

        return is_selected_by_set;
    }

    bool NodeStore::isNodeSelectedByAnySet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const node_index ) const
    {
        bool const is_selected_by_any = ( ( this->checkLock( lock ) ) &&
                ( st::Map_has_key( this->m_node_idx_to_set_ids, node_index ) ) &&
                ( st::Map_ordered_vec_empty( this->m_node_idx_to_set_ids,
                        node_index ) ) );

        SIXTRL_ASSERT( this->isNodeAvailable( lock, node_index ) );

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
            ( this->isNodeAvailable( lock, node_index ) ) &&
            ( st::Map_ordered_vec_empty( this->m_node_idx_to_def_set_ids,
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
        using index_t = _store_t::node_index_t;
        using node_id_t = _store_t::node_id_t;
        using arch_id_t = _store_t::arch_id_t;
        using platform_id_t = _store_t::platform_id_t;

        _store_t::node_index_t index = _store_t::UNDEFINED_INDEX;

        if( ( this->checkLock( lock ) ) &&
            ( ptr_node_info.get() != nullptr ) &&
            ( ( ptr_node_info->ptrNodeStore() == nullptr ) ||
              ( ptr_node_info->ptrNodeStore() == this ) ) &&
            ( ptr_node_info->archId() != node_id_t::ARCH_ILLEGAL ) &&
            ( ptr_node_info->deviceId() == node_id_t::ILLEGAL_DEVICE_ID ) )
        {
            bool is_existing_platform = false;
            arch_id_t const arch_id = ptr_node_info->archId();
            platform_id_t platform_id = ptr_node_info->platformId();
            bool const has_platform_name = ptr_node_info->hasPlatformName();
            device_id_t device_id = node_id_t::ILLEGAL_DEVICE_ID;

            _store_t::status_t status =
                ( !this->hasArchitecture( lock, arch_id ) )
                    ? this->doAddArchitecture( lock, arch_id )
                    : st::ARCH_STATUS_SUCCESS;

            if( st::ARCH_STATUS_SUCCESS == status )
            {
                SIXTRL_ASSERT( this->hasArchitecture( lock, arch_id ) );

                if( ( platform_id == _store_t::ILLEGAL_PLATFORM_ID ) &&
                    ( has_platform_name ) )
                {
                    platform_id = this->platformIdByName(
                        lock, arch_id, ptr_node_info->platformName() );

                    if( platform_id != _store_t::ILLEGAL_PLATFORM_ID )
                    {
                        is_existing_platform = true;
                    }
                }

                if( platform_id == _store_t::ILLEGAL_PLATFORM_ID )
                {
                    platform_id = this->doGetNextPlatformId( lock, arch_id );
                    status = this->doAddPlatform( lock, arch_id, platform_id );
                }
            }

            if( ( st::ARCH_STATUS_SUCCESS == status ) &&
                ( this->hasPlatform( lock, arch_id, platform_id ) ) )
            {
                device_id = this->doGetNextDeviceId(
                    lock, arch_id, platform_id );

                if( device_id != _store_t::ILLEGAL_DEVICE_ID )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }

            if(  st::ARCH_STATUS_SUCCESS == status )
            {
                if( ( platform_id != _store_t::ILLEGAL_PLATFORM_ID ) &&
                    ( device_id != _store_t::ILLEGAL_DEVICE_ID ) )
                {
                    SIXTRL_ASSERT(
                        ( platform_id == ptr_node_info->platformId() ) ||
                        ( ptr_node_info->platformId() ==
                            _store_t::ILLEGAL_PLATFORM_ID ) );

                    status = ptr_node_info->setDeviceId( device_id );

                    if( platform_id != ptr_node_info->platformId() )
                    {
                        status |= ptr_node_info->setPlatformId( platform_id );
                    }
                }

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( !ptr_node_info->nodeId().valid() ) )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }

            if( st::ARCH_STATUS_SUCCESS == status )
            {
                index = this->m_stored_node_infos.size();

                status = this->doPrepareNewNodeIndex( lock,
                    ptr_node_info->nodeId(), index );

                if( ( st::ARCH_STATUS_SUCCESS== status ) &&
                    ( platform_id != _store_t::ILLEGAL_PLATFORM_ID ) &&
                    ( !is_existing_platform ) && ( has_platform_name ) )
                {
                    status = this->addPlatformNameMapping( lock, arch_id,
                        platform_id, ptr_node_info->platformName() );
                }

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( ptr_node_info->ptrNodeStore() == nullptr ) )
                {
                    status = ptr_node_info->assignToNodeStore( *this );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        status = ptr_node_info->setNodeIndex( lock, index );
                    }
                }

                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( ( ptr_node_info->ptrNodeStore() == this ) &&
                      ( ptr_node_info->nodeIndex( lock ) == index ) ) );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    this->m_stored_node_infos.emplace_back(
                        std::move( ptr_node_info ) );
                }
            }
        }
        else if( ( this->checkLock( lock ) ) &&
            ( ptr_node_info.get() != nullptr ) &&
            ( ptr_node_info->nodeId().valid() ) )
        {
            arch_id_t const arch_id = ptr_node_info->archId();
            SIXTRL_ASSERT( arch_id == ptr_node_info->archId() );

            index_t current_index = this->findNodeIndex(
                ptr_node_info->nodeId() );

            status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( current_index != node_id_t::UNDEFINED_INDEX )
            {
                status = st::ARCH_STATUS_SUCCESS;

                if( ptr_node_info->hasPlatformName() )
                {
                    auto it = this->m_arch_platform_to_platform_name.find(
                        std::make_pair( ptr_node_info->archId(),
                            ptr_node_info->platformId() ) );

                    if( it != this->m_arch_platform_to_platform_name.end() )
                    {
                        if( 0 != ptr_node_info->platformName().compare(
                                it->second ) )
                        {
                            status = this->addPlatformNameMapping(
                                lock, ptr_node_info->archId(),
                                    ptr_node_info->platformId(),
                                        ptr_node_info->platformName() );
                        }
                    }
                }
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( current_index != NodeStore::UNDEFINED_INDEX ) )
            {
                index = current_index;
            }
        }

        return index;
    }

    _store_t::status_t NodeStore::doRemoveNode(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const idx )
    {
        using nset_id_t = _store_t::node_set_id_t;
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

                if( ptr_node->detachFromNodeStore() == st::ARCH_STATUS_SUCCESS )
                {
                    this->m_node_id_to_node_index.erase( ptr_node->nodeId() );
                    this->m_stored_node_infos[ idx ].reset( nullptr );
                }
                else
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
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
            ( ptr_node->maxSelectionCount() < st::Map_ordered_vec_size(
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
        _store_t::node_index_t const node_index,
        _store_t::node_set_id_t const node_set_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->isNodeSelectedBySet( lock, node_index, node_set_id ) )
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
                this->m_node_idx_to_sel_set_ids, node_index ) );

            SIXTRL_ASSERT( st::Map_ordered_vec_has_value(
                this->m_node_idx_to_sel_set_ids, node_index, node_set_id ) );

            SIXTRL_ASSERT( st::Map_has_key(
                this->m_node_set_to_node_idxs, node_set_id ) );

            SIXTRL_ASSERT( st::Map_has_key(
                this->m_node_set_to_sel_node_idxs, node_set_id ) );

            SIXTRL_ASSERT( st::Map_ordered_vec_has_value(
                m_node_set_to_sel_node_idxs, node_set_id, node_index ) );

            status = st::Map_remove_value_from_ordered_vec(
                this->m_node_set_to_sel_node_idxs, node_set_id, node_index );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::Map_remove_value_from_ordered_vec(
                    this->m_node_idx_to_sel_set_ids, node_index, node_set_id );
            }

            this->registerChange( lock );
        }

        SIXTRL_ASSERT( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( ( this->isNodeAttachedToSet( lock, node_index, node_set_id ) ) &&
              ( this->isNodeSelectedBySet( lock, node_index, node_set_id ) ) ) );

        return status;
    }

    _store_t::status_t NodeStore::doMarkNodeAsDefaultForSet(
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
            ( ptr_node->maxSelectionCount() < st::Map_ordered_vec_size(
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

    _store_t::status_t NodeStore::doRemoveDefaultNodeFromSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::node_index_t const node_index,
        _store_t::node_set_id_t const node_set_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        auto ptr_set  = this->ptrNodeSetBase( lock, node_set_id );
        auto ptr_node = this->ptrNodeInfoBase( lock, node_index );

        if( ( ptr_node != nullptr ) && ( ptr_set != nullptr ) &&
            ( this->m_node_idx_to_set_ids.find( node_index ) !=
              this->m_node_idx_to_set_ids.end() ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( node_index  != _store_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( node_set_id != _store_t::ILLEGAL_NODE_SET_ID );

            _store_t::node_index_to_node_set_ids_t::iterator it =
                this->m_node_idx_to_def_set_ids.find( node_index );

            if( (  it != this->m_node_idx_to_def_set_ids.end() ) &&
                ( !it->second.empty() ) )
            {
                SIXTRL_ASSERT( std::is_sorted(
                    it->second.begin(), it->second.end() ) );

                auto temp_it = std::lower_bound( it->second.begin(),
                    it->second.end(), node_set_id );

                if( temp_it != it->second.end() )
                {
                    it->second.erase( temp_it );
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
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

            auto it = this->m_arch_to_platforms.find( arch_id );
            if( it != this->m_arch_to_platforms.end() )
            {
                SIXTRL_ASSERT( std::is_sorted( it->second.begin(),
                    it->second.end() ) );

                SIXTRL_ASSERT( !std::binary_search( it->second.begin(),
                    it->second.end(), _store_t::ILLEGAL_PLATFORM_ID ) );

                platform_id = ( it->second.empty() )
                    ? _store_t::platform_id_t{ 0 }
                    : it->second.back() + _store_t::platform_id_t{ 1 };
            }
        }

        return platform_id;
    }

    _store_t::status_t NodeStore::doAddPlatform(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( arch_id != _store_t::ARCH_ILLEGAL ) &&
            ( platform_id != _store_t::ILLEGAL_PLATFORM_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            auto arch_it = this->m_arch_to_platforms.find( arch_id );

            if( arch_it == this->m_arch_to_platforms.end() )
            {
                return status;
            }

            SIXTRL_ASSERT( std::is_sorted( arch_it->second.begin(),
                arch_it->second.end() ) );

            if( std::binary_search( arch_it->second.begin(),
                arch_it->second.end(), platform_id ) )
            {
                return status;
            }

            auto const arch_platform_pair =
                std::make_pair( arch_id, platform_id );

            SIXTRL_ASSERT( this->m_arch_platform_to_devices.end() ==
                this->m_arch_platform_to_devices.find( arch_platform_pair ) );

            SIXTRL_ASSERT( !std::binary_search( arch_it.second.begin(),
                arch_it->second.end(), _store_t::ILLEGAL_PLATFORM_ID ) );

            _store_t::platform_id_t const prev_back =
                ( !arch_it->second.empty() )
                    ? arch_it->second.back() : _store_t::platform_id_t{ 0 };

            arch_it->second.push_back( platform_id );

            if( prev_back > platform_id )
            {
                std::sort( arch_it->second.begin(), arch_it->second.end() );
            }

            auto res = this->m_arch_platform_to_devices.emplace(
                std::make_pair( arch_platform_pair,
                    _store_t::devices_list_t{} ) );

            if( res.second ) status = st::ARCH_STATUS_SUCCESS;
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
                    it->second.end(), _store_t::ILLEGAL_DEVICE_ID ) ) );

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
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( node_id.valid() ) && ( index != _store_t::UNDEFINED_INDEX ) &&
            ( this->hasPlatform( lock, node_id.archId(),
                node_id.platformId() ) ) )
        {
            auto arch_platform_pair = std::make_pair(
                node_id.archId(), node_id.platformId() );

            SIXTRL_ASSERT( this->m_node_id_to_node_index.find( node_id ) ==
                           this->m_node_id_to_node_index.end() );

            SIXTRL_ASSERT( this->m_arch_platform_to_devices.end() ==
                this->m_arch_platform_to_devices.find( arch_platform_pair ) );

            SIXTRL_ASSERT( this->m_node_idx_to_set_ids.end() ==
                this->m_node_idx_to_set_ids.find( node_index ) );

            SIXTRL_ASSERT( this->m_node_idx_to_sel_set_ids.end() ==
                this->m_node_idx_to_sel_set_ids.find( node_index ) );

            SIXTRL_ASSERT( this->m_node_idx_to_def_set_ids.end() ==
                this->m_node_idx_to_def_set_ids.find( node_index ) );

            auto arch_platform_it = this->m_arch_platform_to_devices.find(
                arch_platform_pair );

            if( arch_platform_it == this->m_arch_platform_to_devices.end() )
            {
                auto res = this->m_arch_platform_to_devices.emplace(
                    std::make_pair( arch_platform_pair,
                        _store_t::devices_list_t{ node_id.deviceId() } ) );

                if( res.second ) status = st::ARCH_STATUS_SUCCESS;
            }
            else
            {
                SIXTRL_ASSERT( std::is_sorted( arch_platform_it->second.begin(),
                    arch_platform_it->second.end() ) );

                if( !std::binary_search( arch_platform_it->second.begin(),
                        arch_platform_it->second.begin(), device_id ) )
                {
                    SIXTRL_ASSERT( !std::binary_search(
                        arch_platform_it->second.begin(),
                        arch_platform_it->second.end(),
                        _this_t::ILLEGAL_DEVICE_ID ) );

                    _store_t::device_id_t const prev_back =
                        ( !arch_platform_it->second.empty() )
                            ? arch_platform_it->second.back()
                            : _store_t_device_id_t{ 0 };

                    arch_platform_it->second.push_back( device_id );

                    if( prev_back > device_id )
                    {
                        std::sort( arch_platform_it->second.begin(),
                                   arch_platform_it->second.end() );
                    }

                    status = st::ARCH_STATUS_SUCCESS;
                }
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;

                auto res1 = this->m_node_idx_to_set_ids.emplace(
                std::make_pair( node_index, _store_t::node_indices_list_t{} ) );

                auto res2 = this->m_node_idx_to_sel_set_ids.emplace(
                std::make_pair( node_index, _store_t::node_indices_list_t{} ) );

                auto res3 = this->m_node_idx_to_def_set_ids.emplace(
                std::make_pair( node_index, _store_t::node_indices_list_t{} ) );

                auto res4 = this->m_node_id_to_node_index.insert(
                    std::make_pair( node_id, node_index ) );

                if( ( res1.second ) && ( res2.second ) && ( res3.second ) &&
                    ( res4.second ) )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    void NodeStore::doClearWithoutLocking() SIXTRL_NOEXCEPT
    {
        this->m_stored_node_infos.clear();
        this->m_stored_node_sets.clear();

        this->m_arch_to_platforms.clear();
        this->m_node_idx_to_set_ids.clear();
        this->m_node_idx_to_sel_set_ids.clear();
        this->m_node_idx_to_def_set_ids.clear();
        this->m_node_id_to_node_index.clear();

        this->m_num_node_infos = _store_t::size_type{ 0 };
        this->m_num_node_sets  = _store_t::size_type{ 0 };
    }
}

#endif /* C++, Host */

/* end: sixtracklib/common/control/node_store.cpp */
