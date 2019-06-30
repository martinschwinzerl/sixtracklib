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
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/node_info_base.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/arch_info.hpp"
    #include "sixtracklib/common/control/controller_base.hpp"
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/node_info_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    NodeStore::size_type NodeStore::numArchitectures( NodeStore::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using status_t = NodeStore::status_t;
        using size_t = NodeStore::size_type;

        size_t num_architectures = size_t{ 0 };

        if( ( this->checkLock( lock ) ) &&
            ( !this->m_arch_to_platforms.empty() ) )
        {
            SIXTRL_ASSERT( this->m_arch_to_platforms.size() ==
                           this->m_arch_to_ctrls.size() );

            num_architectures = this->m_arch_to_platforms.size();
        }

        return num_architectures;
    }

    bool NodeStore::hasArchitecture(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock
        NodeStore::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        bool const is_available = (
            ( arch_id != NodeStore::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) &&
            ( this->m_arch_to_platforms.find( arch_id ) !=
              this->m_arch_to_platforms.end() ) );

        SIXTRL_ASSERT( is_available == ( this->m_arch_to_ctrls.find( arch_id )
            != this->m_arch_to_ctrls.end() ) );

        return is_available;
    }

    NodeStore::status_t NodeStore::doAddArchitecture(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id )
    {
        using _this_t = NodeStore;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( arch_id != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) &&
            ( !this->hasArchitecture( lock, arch_id ) ) )
        {
            SIXTRL_ASSERT( this->m_arch_to_ctrls.size() ==
                           this->m_arch_to_platforms.size() );

            auto res1 = this->m_arch_to_ctrls.emplace(
                std::make_pair( arch_id, _this_t::ptr_ctrls_set_t{} ) );

            auto res2 = this->m_arch_to_platforms.emplace(
                std::make_pair( arch_id, _this_t::platforms_set_t{} ) );

            if( ( res1.second ) && ( res2.second ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    NodeStore::platform_id_t NodeStore::doGetNextPlatformId(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id )
    {
        using platform_id_t = NodeStore::platform_id_t;

        NodeStore::platform_id_t platform_id = NodeStore::ILLEGAL_PLATFORM_ID;

        if( this->hasArchitecture( lock, arch_id ) )
        {
            auto it = this->m_arch_to_platforms.find( arch_id );

            if( it != this->m_arch_to_platforms.end() )
            {
                if( it->second.empty() )
                {
                    platform_id = platform_id_t{ 0 };
                }
                else
                {
                    platform_id = *it->second.rbegin();

                    if( platform_id != NodeStore::ILLEGAL_PLATFORM_ID )
                    {
                        platform_id += platform_id_t{ 1 };
                    }
                }
            }
        }

        return platform_id;
    }

    /* --------------------------------------------------------------------- */

    bool NodeStore::hasPlatform(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id )const SIXTRL_NOEXCEPT
    {
        bool is_available = false;

        if( ( this->hasArchitecture( lock, arch_id ) ) &&
            ( platform_id != NodeStore::ILLEGAL_PLATFORM_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            is_available = (
                this->m_arch_platform_to_devices.find( std::make_pair(
                    arch_id, platform_id ) ) !=
                this->m_arch_platform_to_devices.end() );
        }

        return is_available;
    }

    bool NodeStore::hasPlatform(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF name ) const SIXTRL_NOEXCEPT
    {
        return this->hasPlatform( lock, arch_id,
            this->platformIdByName( lock, name ) );
    }

    NodeStore::size_type NodeStore::numPlatforms(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        using status_t = NodeStore::status_t;
        using size_t = NodeStore::size_type;
        using platform_id_t = NodeStore::platform_id_t;

        size_t num_platforms = size_t{ 0 };

        if( ( this->checkLock( lock ) ) &&
            ( this->hasArchitecture( lock, arch_id ) ) &&
            ( !this->m_arch_platform_to_devices.empty() )
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
                        platform_id_t const platform_id = *plfm_it;

                        if( ( platform_id != NodeStore::ILLEGAL_PLATFORM_ID ) &&
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
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF
            platform_name ) const SIXTRL_NOEXCEPT
    {
        using platform_id_t = NodeStore::platform_id_t;

        platform_id_t platform_id = NodeStore::ILLEGAL_PLATFORM_ID;

        if( ( this->hasArchitecture( lock, arch_id ) ) &&
            ( !platform_name.empty() ) && ( this->checkLock( lock ) ) )
        {
            auto it = this->m_arch_platform_name_to_platform_id.find(
                std::make_pair( arch_id, platform_name ) );

            if( it != this->m_arch_platform_name_to_platform_id.end() )
            {
                platform_id = it->second;

                if( platform_id != NodeStore::ILLEGAL_PLATFORM_ID )
                {
                    auto name_it = this->m_arch_platform_to_platform_name.find(
                        std::make_pair( arch_id, platform_id ) );

                    if( ( this->m_arch_platform_to_platform_name.end() ==
                          name_it ) ||
                        ( ( this->m_arch_platform_to_platform_name.end() !=
                            name_it ) && ( name_it->second != platform_id ) ) )
                    {
                        /* Should never get here */
                        platform_id = NodeStore::ILLEGAL_PLATFORM_ID;
                    }
                }
            }
        }

        return platform_id;
    }

    NodeStore::status_t NodeStore::addPlatformNameMapping(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name )
    {
        NodeStore::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->hasArchitecture( lock, arch_id ) ) &&
            ( platform_id != NodeStore::ILLEGAL_PLATFORM_ID ) )
        {
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
                        found_entry = it;
                    }
                }

                if( found_entry == end )
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

    NodeStore::status_t NodeStore::addPlatformNameMapping(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        char const* SIXTRL_RESTRICT platform_name )
    {
        std::string temp_platform_name( "" );

        if( ( platform_name != nullptr ) &&
            ( std::strlen( platform_name ) > NodeStore::size_type{ 0 } ) )
        {
            temp_platform_name = platform_name;
        }

        return this->addPlatformNameMapping(
            lock, arch_id, platform_id, platform_name );
    }



    NodeStore::status_t NodeStore::doAddPlatform(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id )
    {
        NodeStore::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( arch_id != NodeStore::ARCH_ILLEGAL ) &&
            ( platform_id != NodeStore::ILLEGAL_PLATFORM_ID ) &&
            ( this->hasArchitecture( lock, arch_id ) ) &&
            ( !this->hasPlatform( lock, arch_id, platform_id ) ) )
        {
            auto res = this->m_arch_platform_to_devices.emplace(
                std::make_pair( arch_id, platform_id ) );

            if( res.second )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    NodeStore::device_id_t NodeStore::doGetNextDeviceId(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id )
    {
        using device_id_t = NodeStore::device_id_t;
        device_id_t device_id = NodeStore::ILLEGAL_DEVICE_ID;

        if( ( this->hasArchitecture( lock, arch_id ) ) &&
            ( this->hasPlatform( lock, arch_id, platform_id ) ) )
        {
            auto arch_platform_pair = std::make_pair( arch_id, platform_id );

            auto it = this->m_arch_platform_to_devices.find(
                arch_platform_pair );

            if( it != this->m_arch_platform_to_devices.end() )
            {
                if( it->second.empty() )
                {
                    device_id = device_id_t{ 0 };
                }
                else
                {
                    device_id = *it->second.rbegin();

                    if( device_id != NodeStore::ILLEGAL_DEVICE_ID )
                    {
                        device_id += device_id_t{ 1 };
                    }
                }
            }
        }

        return device_id;
    }

    /* --------------------------------------------------------------------- */

    NodeStore::status_t NodeStore::doPrepareNewNodeIndex(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        NodeStore::node_index_t const index )
    {
        using status_t = NodeStore::status_t;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( node_id.valid() ) &&
            ( index != NodeStore::UNDEFINED_INDEX ) &&
            ( this->hasPlatform( lock, node_id.archId(),
                node_id.platformId() ) ) )
        {
            SIXTRL_ASSERT( this->m_node_id_to_node_index.find( node_id ) ==
                           this->m_node_id_to_node_index.end() );

            SIXTRL_ASSERT( this->m_arch_platform_to_devices.end() ==
                this->m_arch_platform_to_devices.find(
                    node_id.archId(), node_id.platformId() ) );

            SIXTRL_ASSERT( this->m_node_index_to_attached_ctrls.end() ==
                this->m_node_index_to_attached_ctrls.find( index ) );

            SIXTRL_ASSERT( this->m_node_index_to_selecting_ctrls.end() ==
                this->m_node_index_to_selecting_ctrls.find( index ) );

            auto res1 = this->m_arch_platform_to_devices.emplace(
                std::make_pair( std::make_pair( node_id.archId(),
                    nodeId.platformId() ), nodeId().deviceId() ) );

            auto res2 = this->m_node_index_to_attached_ctrls.emplace(
                std::make_pair( index, NodeStore::ptr_ctrls_set_t ) );

            auto res3 = this->m_node_index_to_selecting_ctrls.emplace(
                std::make_pair( index, NodeStore::ptr_ctrls_set_t ) );

            auto res4 = this->m_node_id_to_node_index.insert(
                std::make_pair( node_id, index ) );

            if( ( res1.second ) && ( res2.second ) && ( res3.second ) &&
                ( res4.second ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeStore::size_type NodeStore::numControllers( NodeStore::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        NodeStore::size_type num_ctrls = NodeStore::size_type{ 0 };

        if( this->checkLock( lock ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it  = this->m_arch_to_ctrls.begin();
            auto end = this->m_arch_to_ctrls.end();

            for( ; it != end ; ++it )
            {
                SIXTRL_ASSERT( it->first != NodeStore::ARCH_ILLEGAL );
                SIXTRL_ASSERT( this->hasArchitecture( lock, it->first ) );

                if( !it->second.empty() )
                {
                    num_ctrls += it->second.size();
                }
            }

            SIXTRL_ASSERT( num_ctrls == this->m_ctrl_to_node_indices.size() );
        }

        return num_ctrls;
    }


    bool NodeStore::hasController(
        NodeStore::controller_base_t const& controller, NodeStore::lock_t
            const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        bool has_controller = false;

        if( controller.archId() != NodeStore::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            auto ctrl_it = this->m_ctrl_to_node_indices.find( &controller );
            auto arch_it = this->m_arch_to_ctrls.find( controller.archId() );

            if( (  ctrl_it != this->m_ctrl_to_node_indices.end() ) &&
                (  arch_it != this->m_arch_to_ctrls.end() ) &&
                ( !arch_it->second.empty() ) &&
                (  arch_it->second.find( &controller ) !=
                   arch_it->second.end() ) )
            {
                has_controller = true;
            }
        }

        return has_controller;
    }

    NodeStore::size_type NodeStore::numControllers(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        NodeStore::size_type num_ctrls = NodeStore::size_type{ 0 };

        if( this->hasArchitecture( lock, arch_id ) )
        {
            auto it = this->m_arch_to_ctrls.find( arch_id );

            if( ( it != this->m_arch_to_ctrls.end() ) &&
                ( !it->second.empty() ) )
            {
                num_ctrls = it->second.size();
            }
        }

        return num_ctrls;
    }

    NodeStore::status_t NodeStore::doAddController(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::controller_base_t& SIXTRL_RESTRICT_REF controller )
    {
        using _this_t = NodeStore;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( (  controller.archId() != _this_t::ARCH_ILLEGAL ) &&
            (  this->hasArchitecture( lock, controller.archId() ) ) &&
            ( !this->hasController( lock, controller ) ) &&
            ( this->checkLock( lock ) ) )
        {
            auto arch_it = this->m_arch_to_ctrls.find( controller.archId() );
            auto ctrl_it = this->m_ctrl_to_node_indices.find( &controller );

            if( ( arch_it != this->m_arch_to_ctrls.end() ) &&
                ( ctrl_it == this->m_ctrl_to_node_indices.end() ) )
            {
                auto res1 = arch_it->second.insert( &controller );
                auto res2 = this->m_ctrl_to_node_indices.emplace(
                    std::make_pair( &controller, NodeStore::nindices_set_t{} ) );

                if( ( res1.second ) && ( res2.second ) )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeStore::NodeStore() :
        m_arch_to_platforms(),
        m_arch_to_ctrls(),
        m_arch_platform_to_devices(),
        m_arch_platform_to_platform_name(),
        m_arch_platform_name_to_platform_id(),
        m_node_id_to_node_index(),
        m_ctrl_to_node_indices(),
        m_node_index_to_attached_ctrls(),
        m_node_index_to_selecting_ctrls(),
        m_stored_node_infos(),
        m_lockable()
    {

    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_id_t const&
            SIXTRL_RESTRICT_REF node_id ) const SIXTRL_NOEXCEPT
    {
        NodeStore::node_index_t index = NodeStore::node_id_t::UNDEFINED_INDEX;

        if( ( node_id.valid() ) && ( this->checkLock( lock ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            auto it = this->m_node_id_to_node_index.find( node_id );

            if( ( it != this->m_node_id_to_node_index.end() ) &&
                ( it->second != NodeStore::
            {
                index = it->second;

                SIXTRL_ASSERT( this->m_stored_node_infos.size() > index );
                SIXTRL_ASSERT( this->m_stored_node_infos[ index ].get() !=
                               nullptr );

                SIXTRL_ASSERT( this->m_stored_node_infos[ index ]->archId()
                                == node_id.archId() );

                SIXTRL_ASSERT( this->m_stored_node_infos[ index ]->platformId()
                                == node_id.platformId() );

                SIXTRL_ASSERT( this->m_stored_node_infos[ index ]->deviceId()
                                == node_id.deviceId() );
            }
        }

        return index;
    }

    NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_info_base_t const*
            SIXTRL_RESTRICT ptr_node_info ) const SIXTRL_NOEXCEPT
    {
        NodeStore::node_index_t index = NodeStore::UNDEFINED_INDEX;

        if( ( ptr_node_info != nullptr ) && ( this->checkLock( lock ) ) )
        {
            NodeStore::node_index_t found_index =
                this->findNodeIndex( lock, ptr_node_info->nodeId() );

            if( ( found_index != NodeStore::UNDEFINED_INDEX ) &&
                ( this->m_stored_node_infos.size() > found_index ) &&
                ( this->m_stored_node_infos[ index ].get() == ptr_node_info ) )
            {
                index = found_index;
            }
        }

        return index;
    }

    NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT str ) const SIXTRL_NOEXCEPT
    {
        NodeStore::node_index_t found_index = NodeStore::UNDEFINED_INDEX;

        if( ( str != nullptr ) && ( std::strlen( str ) > 0u ) &&
            ( this->checkLock( lock ) ) )
        {
            format_t const format = node_id_t::IdentifyFormat( str );

            if( ( format == st::SIXTRL_NODE_ID_STR_FORMAT_ARCHID ) ||
                ( format == st::SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR ) )
            {
                node_id_t node_id( str );

                if( node_id.valid() )
                {
                    found_index = this->findNodeIndex( node_id );
                }
            }
            else if( ( format == st::SIXTRL_NODE_ID_STR_FORMAT_NOARCH ) &&
                     ( arch_id != st::ARCHITECTURE_ILLEGAL ) )
            {
                node_id_t node_id( arch_id, node_id::ILLEGAL_PLATFORM_ID,
                                   node_id::ILLEGAL_DEVICE_ID );

                if( ( st::ARCH_STATUS_SUCCESS == node_id.fromString( str ) ) &&
                    ( node_id.valid() ) )
                {
                    found_index = this->findNodeIndex( node_id );
                }
            }

            if( found_index == node_id_t::UNDEFINED_INDEX )
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
                        if( arch_id != st::ARCHITECTURE_ILLEGAL )
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

                if( ( found_index == node_id_t::UNDEFINED_INDEX ) &&
                    ( found_node != end ) &&
                    ( arch_id == st::ARCHITECTURE_ILLEGAL ) &&
                    ( num_found_nodes == index_t{ 1 } ) )
                {
                    found_index = static_cast< index_t >(
                        std::distance( this->storedNodeInfoBegin( lock ),
                                       found_node ) );
                }
            }
        }

        return found_index;
    }

    /* -------------------------------------------------------------------- */

    bool NodeStore::isNodeAvailable(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index ) const SIXTRL_RESTRICT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return ( this->ptrNodeInfoBase( lock, index ) != nullptr );
    }

    NodeStore::node_id_t const* NodeStore::ptrNodeId(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );

        NodeStore::node_info_base_t const* ptr_node_info =
            this->ptrNodeInfoBase( lock, index );

        return ( ptr_node_info != nullptr )
            ? ptr_node_info->ptrNodeId() : nullptr;
    }

    NodeStore::node_info_base_t const* NodeStore::ptrNodeInfoBase(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );

        return ( ( index != NodeStore::node_id_t::UNDEFINED_INDEX ) &&
                 ( this->m_stored_node_infos.size() > index ) )
            ? this->m_stored_node_infos[ index ].get() : nullptr;
    }


    NodeStore::node_info_base_t* NodeStore::ptrNodeInfoBase(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index ) SIXTRL_NOEXCEPT
    {
        using _this_t = NodeStore;
        using ptr_t = NodeStore::node_info_base_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >( *this
            ).ptrNodeInfoBase( lock, index ) );
    }

    /* --------------------------------------------------------------------- */

    NodeStore::node_index_t NodeStore::addNode(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::ptr_stored_node_info_t&& ptr_stored_node_info )
    {
        return this->doAddNode( lock, std::move( ptr_stored_node_info ) );
    }

    NodeStore::status_t NodeStore::attachNodeToController(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index,
        NodeStore::controller_base_t& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::status_t status = st::ARCH_STATUS_SUCCESS;

        if( !this->hasController( lock, &controller ) )
        {
            status = this->doAddController( lock, &controller );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            return this->doAttachNodeToController( lock, index, controller );
        }

        return status;
    }

    NodeStore::status_t NodeStore::detachNodeFromController(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        return this->doDetachNodeFromController( lock, index, controller );
    }

    NodeStore::status_t NodeStore::detachNodeFromAllControllers(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index ) const
    {
        using size_t = NodeStore::size_type;

        NodeStore::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        auto node_it = this->m_node_index_to_attached_ctrls.find( index );

        if( node_it != this->m_node_index_to_attached_ctrls.end() )
        {
            std::vector< NodeStore::controller_base_t const* >
                temp_ctrls( node_it->second.begin(), node_it->second.end() );

            size_t num_detached_ctrls = size_t{ 0 };

            if( temp_ctrls.empty() )
            {
                for( auto ptr_ctrl : temp_ctrls )
                {
                    status = ( ptr_ctrl != nullptr )
                        ? this->doDetachNodeFromController(
                            lock, index, *ptr_ctrl )
                        : st::ARCH_STATUS_GENERAL_FAILURE;

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        ++num_detached_ctrls;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                status = st::ARCH_STATUS_SUCCESS;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( !this->isNodeAttachedToAnyController( lock, index ) ) );
        }

        return status;
    }

    NodeStore::size_type NodeStore::numControllersAttachedToNode(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        using size_t = NodeStore::size_type;
        size_t num_attached_ctrls = size_t{ 0 };

        if( this->isNodeAvailable( lock, index ) )
        {
            auto it = this->m_node_index_to_attached_ctrls.find( index );

            if( ( it != this->m_node_index_to_attached_ctrls.end() ) &&
                ( !it->second.empty() ) )
            {
                num_attached_ctrls = it->second.size();
            }
        }

        return num_attached_ctrls;
    }

    bool NodeStore::isNodeAttachedToAnyController(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        bool is_attached_to_any = false;

        if( this->isNodeAvailable( lock, index ) )
        {
            auto it = this->m_node_index_to_attached_ctrls.find( index );

            if( it != this->m_node_index_to_attached_ctrls.end() )
            {
                is_attached_to_any = !it->second.empty();
            }
        }

        return is_attached_to_any;
    }

    bool NodeStore::isNodeAttachedToController(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index, controller_base_t const&
            SIXTRL_RESTRICT_REF controller ) const SIXTRL_NOEXCEPT
    {
        bool is_attached = false;

        if( ( this->isNodeAvailable( lock, index ) ) &&
            ( this->hasController( lock, &controller ) ) )
        {
            SIXTRL_ASSERT( this->ptrNodeInfoBase( index ) != nullptr );

            auto it = this->m_node_index_to_attached_ctrls.find( index );

            if( it != this->m_node_index_to_attached_ctrls.end() )
            {
                is_attached = ( ( it->second.empty() ) &&
                    ( it->second.find( &controller ) != it->second.end() ) );
            }
        }

        return is_attached;
    }

    NodeStore::status_t NodeStore::markNodeAsSelectedByController(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        return this->doSelectNodeByController( lock, index, controller );
    }

    NodeStore::status_t NodeStore::unselectNodeForController(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        return this->doUnselectNodeForController( lock, index, controller );
    }


    bool NodeStore::isNodeSelectedByController(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF ctrl ) const
    {
        bool is_selected_by = false;

        if( ( this->isNodeAvailable( lock, index ) ) &&
            ( this->hasController( lock, ctrl ) ) &&
            ( this->isNodeAttachedToController( lock, index, ctrl ) ) )
        {
            auto it = this->m_node_index_to_selecting_ctrls.find( index );
            SIXTRL_ASSERT( it !=  );

            if( ( it != this->m_node_index_to_selecting_ctrls.end() ) &&
                ( !it->second.empty() ) &&
                (  it->second.find( &ctrl ) != it->second.end() ) )
            {
                is_selected_by = true;
            }
        }

        return is_selected_by;
    }

    bool NodeStore::isNodeSelectedByAnyController(
        NodeStore::node_index_t const node_index ) const
    {
        bool has_selecting_ctrls = false;

        if( this->isNodeAvailable( lock, index ) )
        {
            auto it = this->m_node_index_to_selecting_ctrls.find( index );
            SIXTRL_ASSERT( it !=  );

            if( ( it != this->m_node_index_to_selecting_ctrls.end() ) &&
                ( !it->second.empty() ) )
            {
                has_selecting_ctrls = true;
            }
        }

        return has_selecting_ctrls;
    }

    NodeStore::size_type NodeStore::numSelectingControllersForNode(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index ) const
    {
        using size_t = NodeStore::size_type;

        size_t num_selecting_ctrls = size_t{ 0 };

        if( ( this->isNodeAvailable( lock, index ) )
        {
            auto it = this->m_node_index_to_selecting_ctrls.find( index );

            if( it != this->m_node_index_to_selecting_ctrls.end() )
            {
                num_selecting_ctrls = it->second.size();
            }

            SIXTRL_ASSERT( ( num_selecting_ctrls == size_t{ 0 } ) ||
                ( ( this->numControllersAttachedToNode( lock, index ) <=
                    num_selecting_ctrls ) &&
                  ( this->ptrNodeInfoBase( lock, index ) != nullptr ) &&
                  ( this->ptrNodeInfoBase( lock, index )->maxSelectionCount()
                    >= this->numControllersAttachedToNode( lock, index ) ) ) );
        }

        return num_selecting_ctrls;
    }

    /* ===================================================================== */

    NodeStore::node_index_t NodeStore::doAddNode(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::ptr_stored_node_info_t&& ptr_node_info )
    {
        using index_t = NodeStore::node_index_t;
        using node_id_t = NodeStore::node_id_t;
        using arch_id_t = NodeStore::arch_id_t;
        using platform_id_t = NodeStore::platform_id_t;

        index_t index = node_id_t::UNDEFINED_INDEX;

        if( ( this->checkLock( lock ) ) &&
            ( ptr_node_info.get() != nullptr ) &&
            ( ptr_node_info.archId() != node_id_t::ARCH_ILLEGAL ) &&
            ( ptr_node_info->deviceId() == node_id_t::ILLEGAL_DEVICE_ID ) )
        {
            bool is_existing_platform = false;
            arch_id_t const arch_id = ptr_node_info->archId();
            platform_id_t platform_id = ptr_node_info->platformId();
            bool const has_platform_name = ptr_node_info->hasPlatformName();
            device_id_t device_id = node_id_t::ILLEGAL_DEVICE_ID;

            NodeStore::status_t status =
                ( !this->hasArchitecture( lock, arch_id ) )
                    ? this->doAddArchitecture( lock, arch_id )
                    : st::ARCH_STATUS_SUCCESS;

            if( st::ARCH_STATUS_SUCCESS == status )
            {
                SIXTRL_ASSERT( this->hasArchitecture( lock, arch_id ) );

                if( ( platform_id == NodeStore::ILLEGAL_PLATFORM_ID ) &&
                    ( has_platform_name ) )
                {
                    platform_id = this->platformIdByName(
                        lock, ptr_node_info->platformName() );

                    if( platform_id != NodeStore::ILLEGAL_PLATFORM_ID )
                    {
                        is_existing_platform = true;
                    }
                }

                if( platform_id == NodeStore::ILLEGAL_PLATFORM_ID )
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

                if( device_id != NodeStore::ILLEGAL_DEVICE_ID )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }

            if(  st::ARCH_STATUS_SUCCESS == status )
            {
                if( ( platform_id != NodeStore::ILLEGAL_PLATFORM_ID ) &&
                    ( device_id != NodeStore::ILLEGAL_DEVICE_ID ) )
                {
                    SIXTRL_ASSERT(
                        ( platform_id == ptr_node_info->platformId() ) ||
                        ( ptr_node_info->platformId() ==
                            NodeStore::ILLEGAL_PLATFORM_ID ) );

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
                    ( platform_id != NodeStore::ILLEGAL_PLATFORM_ID ) &&
                    ( !is_existing_platform ) && ( has_platform_name ) )
                {
                    status = this->addPlatformNameMapping( lock, arch_id,
                        platform_id, ptr_node_info->platformName() );
                }

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

        return node_index;
    }

    NodeStore::status_t NodeStore::doAttachNodeToController(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index,
        NodeStore::controller_base_t& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        NodeStore::controller_base_t const* ptr_ctrl = &controller;

        if( ( index != NodeStore::UNDEFINED_INDEX ) &&
            ( this->isNodeAvailable( lock, index ) ) &&
            ( this->hasController( lock, &controller ) ) )
        {
            auto ptr_node_info = this->ptrNodeInfoBase( lock, index );
            auto node_it = this->m_node_index_to_attached_ctrls.find( index );

            if( ( node_it != this->m_node_index_to_attached_ctrls.end() ) &&
                ( ptr_node_info != nullptr ) &&
                ( ptr_node_info->isArchCompatibleWith( ptr_ctrl->archId() ) ) )
            {
                auto ctrl_it = this->m_ctrl_to_node_indices.find( ptr_ctrl );
                SIXTRL_ASSERT( ctrl_it != this->m_ctrl_to_node_indices.end() );

                SIXTRL_ASSERT( ( node_it->second.empty() ) ||
                    ( node_it->second.find( ptr_ctrl ) ==
                      node_it->second.end() ) );

                if( ( ctrl_it->second.empty() ) ||
                    ( ctrl_it->second.find( index ) == ctrl_it->second.end() ) )
                {
                    auto res1 = ctrl_it->second.insert( index );
                    auto res2 = node_it->second.insert( ptr_ctrl );

                    if( ( res1.second ) && ( res2.second ) )
                    {
                        status = st::ARCH_STATUS_SUCCESS;
                    }
            }
        }

        return status;
    }

    NodeStore::status_t NodeStore::doDetachNodeFromController(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        NodeStore::controller_base_t const* ptr_ctrl = &controller;

        if( ( this->isAttachedToController(  lock, index, ptr_ctrl ) ) &&
            ( !this->isSelectedByController( lock, index, ptr_ctrl ) ) )
        {
            status = st::ARCH_STATUS_SUCCESS;

            auto ctrl_it = this->m_ctrl_to_node_indices.find( ptr_ctrl );
            SIXTRL_ASSERT( ctrl_it != this->m_ctrl_to_node_indices.end() )
            SIXTRL_ASSERT( !ctrl_it->second.empty() );
            SIXTRL_ASSERT(  ctrl_it->second.find( index ) !=
                            ctrl_it->second.end() );

            auto node_it = this->m_node_index_to_attached_ctrls.find( index );
            SIXTRL_ASSERT( this->m_node_index_to_attached_ctrls.end() != node_it );
            SIXTRL_ASSERT( !node_it->second.empty() );
            SIXTRL_ASSERT(  node_it->second.find( ptr_ctrl ) !=
                            node_it->second.end() );

            ctrl_it->second.erase( index );
            node_it->second.erase( ptr_ctrl );

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    NodeStore::status_t NodeStore::doSelectNodeByController(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        NodeIndex::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        NodeStore::controller_base_t const* ptr_ctrl = &controller;

        if( (  this->isNodeAvailable( lock, index ) ) &&
            (  this->isAttachedToController( lock, index, ptr_ctrl ) ) &&
            ( !this->isSelectedByController( lock, index, ptr_ctrl ) ) )
        {
            auto ptr_node_info = this->ptrNodeInfoBase( lock, index );
            auto sel_it = this->m_node_index_to_selecting_ctrls.find( index );

            if( ( this->m_node_index_to_selecting_ctrls.end() != sel_it ) &&
                ( ptr_node_info != nullptr ) &&
                ( ptr_node_info->isArchCompatibleWith( ptr_ctrl->archId() )) &&
                ( ptr_node_info->maxSelectionCount() > sel_it->second.size() ) )
            {
                auto res = this->m_node_index_to_selecting_ctrls.insert(
                    ptr_ctrl );

                if( res.second )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    NodeStore::status_t NodeStore::doUnselectNodeForController(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        NodeIndex::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        NodeStore::controller_base_t const* ptr_ctrl = &controller;

        if( (  this->isNodeAvailable( lock, index ) ) &&
            (  this->isAttachedToController( lock, index, ptr_ctrl ) ) &&
            (  this->isSelectedByController( lock, index, ptr_ctrl ) ) )
        {
            auto sel_it = this->m_node_index_to_selecting_ctrls.find( index );

            if( this->m_node_index_to_selecting_ctrls.end() != sel_it )
            {
                SIXTRL_ASSERT( sel_it->second.empty() );
                SIXTRL_ASSERT( sel_it->second.find(
                    ptr_ctrl ) != sel_it->second.end() );

                sel_it->second.erase( ptr_ctrl );

                if( sel_it->second.find( ptr_ctrl ) == sel_it->second.end() )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    NodeStore::status_t NodeStore::doRebuild(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        return ( this->checkLock( lock ) )
            ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    NodeStore::status_t NodeStore::doClear(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        NodeStore::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->checkLock( lock ) )
        {
            this->m_arch_to_platforms.clear();
            this->m_arch_to_ctrls.clear();
            this->m_arch_platform_to_devices.clear();
            this->m_arch_platform_to_platform_name.clear();
            this->m_arch_platform_name_to_platform_id.clear();
            this->m_node_id_to_node_index.clear();

            this->m_node_index_to_selecting_ctrls.clear();
            this->m_node_index_to_attached_ctrls.clear();
            this->m_ctrl_to_node_indices.clear();

            this->m_stored_node_infos.clear();
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }
}

/* end: sixtracklib/common/control/node_store.cpp */
