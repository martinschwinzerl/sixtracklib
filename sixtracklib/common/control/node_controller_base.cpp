#include "sixtracklib/common/control/node_controller_base.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/common/control/node_info.h"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{

    NodeControllerBase::node_index_t
    NodeControllerBase::numAvailableNodes( NodeControllerBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = NodeControllerBase;
        using  size_t = _this_t::size_type;
        using index_t = _this_t::node_index_t;

        index_t const num_available_nodes = (
            ( this->isSyncWithNodeStore() ) &&
            ( this->nodeStore().checkLock( lock ) ) )
                ? this->m_num_available_nodes : index_t{ 0 };

        SIXTRL_ASSERT( ( num_available_nodes == index_t{ 0 } ) ||
            ( ( this->m_available_node_indices.size() ==
                num_available_nodes ) &&
              ( this->m_available_node_ids.size() == num_available_nodes ) &&
              ( this->m_available_node_id_strings.size() ==
                num_available_nodes ) &&
              ( this->nodeStore().hasController( lock, *this ) ) &&
              ( this->nodeStore().numNodes( lock, *this ) ==
                num_available_nodes ) ) );

        return num_available_nodes;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::syncWithNodeStore(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        NodeControllerBase::status_t status =
            SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        if( this->nodeStore().checkLock( lock ) )
        {
            this->doSetIsSyncWithNodeStoreFlag( false );
            status = this->doSyncWithNodeStore( lock, this->ptrNodeStore() );

            if( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
            {
                this->doSetIsSyncWithNodeStoreFlag( true );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::addKernelConfig(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const node_index,
        NodeControllerBase::kernel_id_t const kernel_id )
    {
        using _this_t = st::NodeControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        _this_t::kernel_config_base_t const* ptr_kernel_config =
                this->kernelConfigStore().ptrKernelConfigBase( kernel_id );

        if( ( ptr_kernel_config != nullptr ) &&
            ( ptr_kernel_config->archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->nodeStore().checkLock( lock ) ) )
        {
            _this_t::node_info_base_t const* ptr_conf =
                this->nodeStore().ptrNodeInfoBase( lock, node_index );

            if( ( ptr_conf != nullptr ) &&
                ( ptr_conf->archId() == ptr_kernel_config->archId() ) )
            {
                _this_t::kernel_config_key_t const key( ptr_conf->nodeId(),
                    ptr_kernel_config->purpose(), ptr_kernel_config->variant(),
                        ptr_kernel_config->ptrConfigStr() );

                status = this->addKernelConfig( key, kernel_id );
            }
        }

        return status;
    }

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::addKernelConfig(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const node_index,
        NodeControllerBase::ptr_kernel_conf_base_t&& ptr_kernel_config )
    {
        using _this_t = st::NodeControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( ptr_kernel_config.get() != nullptr ) &&
            ( node_index != _this_t::UNDEFINED_INDEX ) &&
            ( ptr_kernel_config->archId() != _this_t::ARCH_ILLEGAL ) )
        {
            _this_t::node_info_base_t const* ptr_conf =
                this->nodeStore().ptrNodeInfoBase( lock, node_index );

            if( ( ptr_conf != nullptr ) &&
                ( ptr_conf->archId() == ptr_kernel_config->archId() ) )
            {
                _this_t::kernel_config_key_t const key( ptr_conf->nodeId(),
                    ptr_kernel_config->purpose(), ptr_kernel_config->variant(),
                        ptr_kernel_config->ptrConfigStr() );

                status = this->addKernelConfig(
                    key, std::move( ptr_kernel_config ) );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool NodeControllerBase::hasSelectedNode( NodeControllerBase::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = NodeControllerBase;

        bool const has_selected_node = (
            ( this->isSyncWithNodeStore() ) &&
            ( this->nodeStore().checkLock( lock ) ) &&
            ( this->nodeStore().hasController( lock, *this ) ) &&
            ( !this->m_available_node_indices.empty() ) &&
            ( this->m_selected_node_index != _this_t::UNDEFINED_INDEX ) &&
            (  this->m_available_node_indices.front() <=
               this->m_selected_node_index ) &&
            (  this->m_available_node_indices.back() >=
               this->m_selected_node_index ) );

        SIXTRL_ASSERT( ( !has_selected_node ) ||
            ( ( std::find( this->m_available_node_indices.begin(),
                this->m_available_node_indices.end(),
                this->m_selected_node_index ) !=
                this->m_available_node_indices.end() ) &&
              ( this->nodeStore().isNodeAttachedToController(
                    lock, this->m_selected_node_index, *this ) ) &&
              ( this->nodeStore().isNodeSelectedByController(
                    lock, this->m_selected_node_index, *this ) ) ) );

        return has_selected_node;
    }

    /* --------------------------------------------------------------------- */

    bool NodeControllerBase::hasDefaultNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::NodeControllerBase;

        bool const has_default_node = (
            ( this->isSyncWithNodeStore() ) &&
            ( this->nodeStore().checkLock( lock ) ) &&
            ( this->nodeStore().hasController( lock, *this ) ) &&
            ( !this->m_available_node_indices.empty() ) &&
            ( this->m_default_node_index != _this_t::UNDEFINED_INDEX ) &&
            (  this->m_available_node_indices.front() <=
               this->m_default_node_index ) &&
            (  this->m_available_node_indices.back() >=
               this->m_default_node_index ) );

        SIXTRL_ASSERT( ( !has_default_node ) ||
            ( ( std::find( this->m_available_node_indices.begin(),
                this->m_available_node_indices.end(),
                this->m_default_node_index ) !=
                this->m_available_node_indices.end() ) &&
              ( this->nodeStore().isNodeAttachedToController(
                    lock, this->m_default_node_index, *this ) ) ) );

        return has_default_node;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::node_index_t NodeControllerBase::nodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::arch_id_t const arch_id,
        NodeControllerBase::platform_id_t const platform_id,
        NodeControllerBase::device_id_t const device_id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = NodeControllerBase;
        using index_t = _this_t::node_index_t;

        index_t index = NodeControllerBase::UNDEFINED_INDEX;

        if( ( arch_id != _this_t::ARCH_ILLEGAL ) &&
            ( this->archId() == arch_id ) &&
            ( this->nodeStore().checkLock( lock ) ) )
        {
            index = this->nodeStore().findNodeIndex(
                lock, arch_id, platform_id, device_id );

            if( !this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) )
            {
                index = _this_t::UNDEFINED_INDEX;
            }
        }

        return index;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::changeSelectedNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const new_node_index )
    {
        using _this_t = st::NodeControllerBase;
        using index_t = _this_t::node_index_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->nodeStore().checkLock( lock ) )
        {
            return status;
        }

        index_t const initial_node_index = this->selectedNodeIndex( lock );

        bool const new_node_index_is_available =
            this->isNodeAvailable( lock, new_node_index );

        if( ( _this_t::UNDEFINED_INDEX != new_node_index ) &&
            ( _this_t::UNDEFINED_INDEX != initial_node_index ) &&
            ( initial_node_index != new_node_index ) &&
            ( new_node_index_is_available ) )
        {
            if( this->canChangeSelectedNode() )
            {
                if( !this->isNodeInitialized( lock, new_node_index ) )
                {
                    status = this->initializeNode( lock, new_node_index );
                }
                else
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( ( this->isNodeInitialized( lock, new_node_index ) ) &&
                  ( this->canChangeSelectedNode() ) ) );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->nodeStore().markNodeAsSelectedByController(
                    lock, new_node_index, *this );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->nodeStore().unselectNodeForController(
                    lock, initial_node_index, *this );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                if( this->canDirectlyChangeSelectedNode() )
                {
                    status = this->doChangeSelectedNode( lock, new_node_index );
                }
                else if( this->canUnselectNode() )
                {
                    status = this->doUnselectNode( lock, initial_node_index );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        status = this->doSelectNode( lock, new_node_index );
                    }
                }
            }
        }
        else if( ( _this_t::UNDEFINED_INDEX != new_node_index ) &&
                 ( initial_node_index == new_node_index ) &&
                 ( new_node_index_is_available ) )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::nodeIdString(
        NodeControllerBase::node_index_t const node_index,
        NodeControllerBase::size_type const node_id_str_capacity,
        char* SIXTRL_RESTRICT node_id_str ) const SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeControllerBase;
        using  size_t = _this_t::size_type;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( node_id_str != nullptr ) &&
            ( node_id_str_capacity > size_t{ 0 } ) )
        {
            std::memset( node_id_str, ( int )'\0', node_id_str_capacity );
        }

        if( ( this->isSyncWithNodeStore() ) && ( node_id_str != nullptr ) &&
            ( node_index != _this_t::UNDEFINED_INDEX ) &&
            ( static_cast< _this_t::size_type >( node_index ) <
              this->m_available_node_id_strings.size() ) &&
            ( this->m_available_node_id_strings[ node_index ].size() <=
              node_id_str_capacity ) )
        {
            size_t const len = std::min( node_id_str_capacity,
                this->m_available_node_id_strings[ node_index ].size() );

            std::memcpy( node_id_str,
                this->m_available_node_id_strings[ node_index ].data(), len );

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    void NodeControllerBase::printAvailableNodeInfos(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        st::NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );

        st::NodeControllerBase::status_t
            status = this->doPrintAvailableNodesToOutputStream( lock, output );

        SIXTRL_ASSERT( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );
        ( void )status;

        return;
    }

    /* --------------------------------------------------------------------- */

    void NodeControllerBase::printOutAvailableNodeInfos(
        ::FILE* SIXTRL_RESTRICT output ) const
    {
        std::ostringstream a2str;

        st::NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );

        if( ( output != nullptr ) && ( this->nodeStore().checkLock( lock ) ) &&
            ( SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS ==
                this->doPrintAvailableNodesToOutputStream( lock, a2str ) ) )
        {
            std::string const str_repr = a2str.str();

            int const ret = std::fprintf( output, "%s", str_repr.c_str() );
            SIXTRL_ASSERT( ret > 0 );
            ( void )ret;
        }

        return;

    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::availableNodeInfosToString(
        NodeControllerBase::size_type capacity,
        char* SIXTRL_RESTRICT node_info_str) const
    {
        using _this_t = st::NodeControllerBase;
        using size_t = _this_t::size_type;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( capacity > size_t{ 0 } ) && ( node_info_str != nullptr ) )
        {
            std::memset( node_info_str, static_cast< int >( '\0' ),
                         capacity );

            std::string const str_repr = this->availableNodeInfosToString();

            if( str_repr.size() < capacity )
            {
                std::strncpy( node_info_str, str_repr.c_str(),
                              capacity - size_t{ 1 }  );

                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::NodeControllerBase(
        NodeControllerBase::arch_id_t const arch_id,
        NodeControllerBase::kernel_config_store_base_t&
            SIXTRL_RESTRICT_REF kernel_config_store,
        NodeControllerBase::node_store_t& SIXTRL_RESTRICT_REF node_store,
        const char *const SIXTRL_RESTRICT config_str ) :
        NodeControllerBase::_controller_base_t(
            arch_id, kernel_config_store, config_str ),
        m_available_node_indices(),
        m_available_node_ids(),
        m_available_node_id_strings(),
        m_node_store( node_store ),
        m_selected_node_index( st::NodeControllerBase::UNDEFINED_INDEX ),
        m_default_node_index( st::NodeControllerBase::UNDEFINED_INDEX ),
        m_num_available_nodes( st::NodeControllerBase::size_type{ 0 } ),
        m_can_directly_change_selected_node( false ),
        m_node_change_requires_kernels( false ),
        m_can_unselect_node( false ),
        m_use_autoselect( false ),
        m_nodes_are_sync( false )
    {
        using lock_t = st::NodeControllerBase::lock_t;
        using size_t = st::NodeControllerBase::size_type;
        using status_t = st::NodeControllerBase::status_t;

        lock_t lock( *this->m_node_store.lockable() );

        if( ( this->nodeStore().hasArchitecture( lock, arch_id ) ) &&
            ( this->nodeStore().numPlatforms( lock, arch_id ) > size_t{ 0 } ) )
        {
            status_t status = this->doAttachAllArchNodes( lock );
            ( void )status;
        }
    }

    /* --------------------------------------------------------------------- */

    void NodeControllerBase::doClear()
    {
        st::NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        this->doClearNodeControllerBaseImpl( lock );
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t
    NodeControllerBase::doSyncWithNodeStore(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_store_t* SIXTRL_RESTRICT ptr_node_store )
    {
        return this->doSyncWithNodeStoreBaseImpl( lock, ptr_node_store );
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t
    NodeControllerBase::doSyncWithNodeStoreBaseImpl(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_store_t* SIXTRL_RESTRICT ptr_node_store )
    {
        using _this_t   = NodeControllerBase;
        using size_t    = _this_t::size_type;
        using index_t   = _this_t::node_index_t;
        using node_id_t = _this_t::node_id_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( !this->nodeStore().checkLock( lock ) ) ||
            ( !this->nodeStore().hasArchitecture( lock, this->archId() ) ) ||
            ( !this->nodeStore().hasController( lock, *this ) ) )
        {
            return status;
        }

        if( this->nodeStore().numNodes( lock, *this ) > size_t{ 0 } )
        {
            index_t const total_num_nodes_in_store =
                this->nodeStore().totalNumNodes( lock );

            std::vector< index_t > node_indices(
                total_num_nodes_in_store, _this_t::UNDEFINED_INDEX );

            size_t nodes_copied = size_t{ 0 };

            status = this->nodeStore().nodeIndices( lock, node_indices.begin(),
                node_indices.end(), *this, &nodes_copied );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( nodes_copied > size_t{ 0 } ) )
            {
                this->m_available_node_indices.clear();
                this->m_available_node_ids.clear();
                this->m_available_node_id_strings.clear();
                this->m_default_node_index = _this_t::UNDEFINED_INDEX;
                this->m_selected_node_index = _this_t::UNDEFINED_INDEX;
                this->m_num_available_nodes = index_t{ 0 };

                this->doSetIsSyncWithNodeStoreFlag( false );

                for( size_t ii = size_t{ 0 } ; ii < nodes_copied ; ++ii )
                {
                    index_t const index = node_indices[ ii ];

                    if( ( index == _this_t::UNDEFINED_INDEX ) ||
                        ( index > total_num_nodes_in_store ) )
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    auto ptr = this->nodeStore().ptrNodeId( lock, index );

                    if( ( ptr == nullptr ) || ( !ptr->valid() ) )
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    this->m_available_node_ids.push_back( *ptr );

                    size_t const node_id_str_len = ptr->requiredStringCapacity(
                        st::NODE_ID_STR_FORMAT_NOARCH );

                    if( node_id_str_len == size_t{ 0 } )
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    this->m_available_node_id_strings.emplace_back(
                        node_id_str_len, '\0' );

                    status = ptr->toString(
                        this->m_available_node_id_strings.back().data(),
                        this->m_available_node_id_strings.back().size() );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        this->m_available_node_indices.push_back( index );
                        this->m_available_node_ids.push_back( *ptr );
                        ++this->m_num_available_nodes;
                    }
                    else
                    {
                        this->m_available_node_id_strings.pop_back();
                        break;
                    }

                    if( this->nodeStore().isNodeSelectedByController(
                        lock, index, *this ) )
                    {
                        this->m_selected_node_index = index;
                    }
                }
            }

            if( ( this->m_num_available_nodes > index_t{ 0 } ) &&
                ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( this->m_available_node_indices.size() ==
                  this->m_num_available_nodes ) &&
                ( this->m_available_node_ids.size() ==
                  this->m_num_available_nodes ) &&
                ( this->m_available_node_id_strings.size() ==
                  this->m_num_available_nodes ) )
            {
                this->doSetIsSyncWithNodeStoreFlag( true );

                index_t const default_node_index =
                    this->doFindDefaultNodeIndex( lock );

                if( default_node_index != _this_t::UNDEFINED_INDEX )
                {
                    this->m_default_node_index = default_node_index;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::doSelectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const node_index )
    {
        using _this_t = NodeControllerBase;
        using ptr_config_t = _this_t::kernel_config_base_t*;
        using ptr_node_info_t = _this_t::node_info_base_t*;
        using key_t = _this_t::kernel_config_key_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( node_index != _this_t::UNDEFINED_INDEX ) &&
            ( this->nodeStore().checkLock( lock ) ) &&
            ( this->isSyncWithNodeStore() ) )
        {
            ptr_node_info_t ptr_base =
                this->nodeStore().ptrNodeInfoBase( lock, node_index );

            if( ( ptr_base != nullptr ) &&
                ( ptr_base->archId() != _this_t::ARCH_ILLEGAL ) &&
                ( ptr_base->archId() == this->archId() ) )
            {
                key_t const& current_key = this->remapBufferKernelConfigKey();
                key_t new_key;

                if( ( current_key.archId()  != _this_t::ARCH_ILLEGAL ) &&
                    ( current_key.purpose() ==
                        st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER ) )
                {
                    status = new_key.reset( ptr_base->nodeId(),
                        current_key.purpose(), current_key.variant(),
                            current_key.configStr() );
                }
                else if( current_key.archId() == this->archId() )
                {
                    status = new_key.reset( ptr_base->nodeId(),
                        st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER, this->variant(),
                            this->defaultKernelConfigStr().c_str() );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;

                    if( this->doPreflightCheckSelectKernelConfigByKey(
                            new_key ) )
                    {
                        if( this->kernelConfigStore().hasKernel( new_key ) )
                        {
                            status = st::ARCH_STATUS_SUCCESS;
                        }
                        else if( this->kernelConfigStore(
                            ).hasDefaultInitKernelConfigParameters( new_key ) )
                        {
                            status = this->doInitializeKernelConfigs( new_key );
                        }

                        if( status == st::ARCH_STATUS_SUCCESS )
                        {
                            status = this->doSelectRemapBufferKernelConfig(
                                new_key );
                        }
                    }
                }
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                this->m_selected_node_index = node_index;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::doChangeSelectedNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const new_selected_node_index )
    {
        using _this_t = NodeControllerBase;
        using ptr_config_t = _this_t::kernel_config_base_t*;
        using ptr_node_info_t = _this_t::node_info_base_t*;
        using key_t = _this_t::kernel_config_key_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( new_selected_node_index != _this_t::UNDEFINED_INDEX ) &&
            ( this->nodeStore().checkLock( lock ) ) &&
            ( this->isSyncWithNodeStore() ) )
        {
            ptr_node_info_t ptr_base = this->nodeStore().ptrNodeInfoBase(
                lock, new_selected_node_index );

            if( ( ptr_base != nullptr ) &&
                ( ptr_base->archId() != _this_t::ARCH_ILLEGAL ) &&
                ( ptr_base->archId() == this->archId() ) )
            {
                key_t const& current_key = this->remapCObjectBufferKernelKey();

                if( ( current_key.archId()  != _this_t::ARCH_ILLEGAL ) &&
                    ( current_key.purpose() ==
                        st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER ) )
                {
                    key_t const key( ptr_base->nodeId(), current_key.purpose(),
                               current_key.variant(), key.ptrConfigStr() );

                    status = this->selectRemapCObjectBufferKernel( key );

                }
                else if( current_key.archId() == this->archId() )
                {
                    key_t const key( ptr_base->nodeId(),
                        st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER, this->variant(),
                            this->defaultKernelConfigStr().c_str() );

                    status = this->selectRemapCObjectBufferKernel( key );
                }
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                this->m_selected_node_index = new_selected_node_index;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::doUnselectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const selected_node_index )
    {
        SIXTRL_ASSERT( this->nodeStore().checkLock( lock ) );

        ( void )lock;
        ( void )selected_node_index;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::node_index_t NodeControllerBase::doFindDefaultNodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        ( void )lock;
        return NodeControllerBase::UNDEFINED_INDEX;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::doPrintToOutputStream(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        using size_t = NodeControllerBase::size_type;
        using index_t = NodeControllerBase::node_index_t;

        NodeControllerBase::status_t status =
            ControllerBase::doPrintToOutputStream( output );

        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            output << "Available nodes : " << this->numAvailableNodes( lock )
                   << "\r\n";

            if( this->numAvailableNodes( lock ) > index_t{ 0 } )
            {
                bool first = true;
                output << "Node Id strings : ";

                for( auto const& node_id_str_buffer :
                        this->m_available_node_id_strings )
                {
                    if( ( node_id_str_buffer.data() == nullptr ) ||
                        ( std::strlen( node_id_str_buffer.data() ) == 0u ) )
                    {
                        continue;
                    }

                    if( !first )
                    {
                        output << ", ";
                    }

                    output << node_id_str_buffer.data();
                }

                output << "\r\n";

                if( ( this->hasSelectedNode( lock ) ) &&
                    ( this->ptrSelectedNodeId( lock ) != nullptr ) )
                {
                    output << "selected Node   : " <<
                           << this->ptrSelectedNodeId( lock )->toString(
                               st::NODE_ID_STR_FORMAT_NOARCH ) << "\r\n";
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t
    NodeControllerBase::doPrintAvailableNodesToOutputStream(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        NodeControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        using index_t = NodeControllerBase::node_index_t;

        if( ( this->isSyncWithNodeStore() ) &&
            ( this->nodeStore().checkLock( lock ) ) &&
            ( this->numAvailableNodes( lock ) > index_t{ 0 } ) )
        {
            auto it  = this->nodeIndicesBegin();
            auto end = this->nodeIndicesEnd();

            if( ( it != nullptr ) && ( end != nullptr ) )
            {
                status = st::ARCH_STATUS_SUCCESS;

                for( ; it != end ; ++it )
                {
                    auto ptr_node_info = this->ptrNodeInfoBase( lock, *it );

                    if( ptr_node_info != nullptr )
                    {
                        output << *ptr_node_info << "\r\n";
                    }
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::doResetKeyFromNodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::kernel_config_key_t& SIXTRL_RESTRICT_REF key,
        NodeControllerBase::node_index_t const node_index,
        NodeControllerBase::kernel_purpose_t const purpose,
        NodeControllerBase::variant_t const variant_flags,
        char const* SIXTRL_RESTRICT kernel_config_str ) const
    {
        using _this_t = st::NodeControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( node_index != _this_t::UNDEFINED_INDEX ) &&
            ( this->nodeStore().checkLock( lock ) ) )
        {
            _this_t::node_info_base_t const* ptr_node_info =
                this->ptrNodeInfoBase( lock, node_index );

            if( ptr_node_info != nullptr )
            {
                status = key.reset( ptr_node_info->nodeId(),
                           purpose, variant, kernel_config_str );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t
    NodeControllerBase::doAttachAllArchNodes(
        NodeControllerBase::lock_t const& SIXTRL_RESTRIC_REF lock )
    {
        using _this_t = NodeControllerBase;
        using status_t = _this_t::status_t;
        using size_t = _this_t::size_type;
        using node_id_t = _this_t::node_id_t;
        using index_t = _this_t::node_index_t;
        using node_id_str_buffer_t = _this_t::node_id_str_buffer_t;
        using node_info_base_t = _this_t::node_info_base_t;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->nodeStore().hasArchitecture( lock, this->archId() ) ) )
        {
            status = this->nodeStore().attachAllArchitectureNodesToController(
                lock, *this );
        }

        return status;
    }

    NodeControllerBase::status_t NodeControllerBase::doDetachAllNodes(
        NodeControllerBase::lock_t const& SIXTRL_RESTRIC_REF lock )
    {
        NodeControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->hasArchitecture( lock, this->archId() ) ) &&
            ( this->hasController( lock, *this ) ) )
        {
            status = st::ARCH_STATUS_SUCCESS;

            if( this->hasSelectedNode( lock ) )
            {
                status = this->nodeStore().unselectNodeForController( lock,
                    this->selectedNodeIndex( lock ), *this );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->nodeStore().detachAllNodesFromController(
                    lock, *this );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::doInitiallySelectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::selectNodeFn select_fn,
        char const* SIXTRL_RESTRICT config_str )
    {
        NodeControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->isSyncWithNodeStore() ) && ( select_fn != nullptr ) )
        {
            if( config_str != nullptr )
            {
                status = this->doInitiallySelectNodeByConfigStr(
                    lock, select_fn, config_str );
            }

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( this->useAutoSelect() ) && ( this->hasDefaultNode( lock ) ) )
            {
                status = this->doInitiallySelectDefaultNode( lock, select_fn );
            }
        }

        return status;
    }

    NodeControllerBase::status_t NodeControllerBase::doInitiallySelectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::selectNodeFn select_fn,
        char const* SIXTRL_RESTRICT config_str,
        NodeControllerBase::node_id_t const& SIXTRL_RESTRICT_REF node_id )
    {
        using _this_t = NodeControllerBase;
        using index_t = _this_t::node_index_t;

        NodeControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->isSyncWithNodeStore() ) && ( select_fn != nullptr ) )
        {
            if( ( node_id.valid() ) && ( node_id.archId() == this->archId() ) )
            {
                index_t node_index =
                    this->nodeStore().nodeIndex( lock, node_id );

                if( node_index != _this_t::UNDEFINED_INDEX )
                {
                    status = select_fn( lock, node_index );
                }
            }

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( config_str != nullptr ) && ( this->usesAutoSelect() ) )
            {
                status this->doInitialSelectNode( lock, select_fn, config_str );
            }
        }

        return status;
    }

    NodeControllerBase::status_t NodeControllerBase::doInitiallySelectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::selectNodeFn select_fn,
        char const* SIXTRL_RESTRICT config_str,
        NodeControllerBase::platform_id_t const platform_id,
        NodeControllerBase::device_id_t const device_id )
    {
        using _this_t = NodeControllerBase;
        using index_t = _this_t::node_index_t;

        NodeControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->isSyncWithNodeStore() ) && ( select_fn != nullptr ) )
        {
            if( ( platform_id != _this_t::ILLEGAL_PLATFORM_ID ) &&
                ( device_id   != _this_t::ILLEGAL_DEVICE_ID ) )
            {
                index_t node_index = this->nodeStore().nodeIndex(
                    lock, this->archId(), platform_id, device_id );

                if( node_index != _this_t::UNDEFINED_INDEX )
                {
                    status = select_fn( lock, node_index );
                }
            }

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( config_str != nullptr ) && ( this->usesAutoSelect() ) )
            {
                status this->doInitialSelectNode( lock, select_fn, config_str );
            }
        }

        return status;
    }

    NodeControllerBase::status_t NodeControllerBase::doInitiallySelectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::selectNodeFn select_fn,
        char const* SIXTRL_RESTRICT config_str,
        char const* SIXTRL_RESTRICT str,
        NodeControllerBase::node_str_role_t const str_role )
    {
        using _this_t = NodeControllerBase;
        using index_t = _this_t::node_index_t;

        NodeControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->isSyncWithNodeStore() ) && ( select_fn != nullptr ) )
        {
            if( ( str != nullptr ) &&
                ( std::strlen( str ) > _this_t::size_type{ 0 } ) &&
                ( ( str_role == _this_t::NODE_ID_STR ) ||
                  ( str_role == _this_t::NODE_UNIQUE_ID_STR ) ) )
            {
                index_t node_index = this->nodeStore().nodeIndex(
                    lock, this->archId(), str, str_role );

                if( node_index != _this_t::UNDEFINED_INDEX )
                {
                    status = select_fn( lock, node_index );
                }
            }

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( config_str != nullptr ) && ( this->usesAutoSelect() ) )
            {
                status this->doInitialSelectNode( lock, select_fn, config_str );
            }
        }

        return status;
    }

    NodeControllerBase::status_t NodeControllerBase::doInitiallySelectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::selectNodeFn select_fn,
        char const* SIXTRL_RESTRICT config_str,
        std::string const& SIXTRL_RESTRICT_REF str,
        NodeControllerBase::node_str_role_t const str_role )
    {
        return this->doInitiallySelectNode(
            lock, select_fn, str.c_str(), str_role );
    }

    NodeControllerBase::status_t
    NodeControllerBase::doInitiallySelectNodeByConfigStr(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::selectNodeFn select_fn,
        char const* SIXTRL_RESTRICT config_str )
    {
        using _this_t = NodeControllerBase;
        using index_t = _this_t::node_index_t;

        NodeControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->isSyncWithNodeStore() ) && ( select_fn != nullptr ) )
        {
            if( ( config_str != nullptr ) &&
                ( std::strlen( config_str ) > _this_t::size_type{ 0 } ) )
            {
                index_t node_index = _this_t::UNDEFINED_INDEX;

                std::string const node_id_str(
                    st::NodeId_extract_node_id_str_from_config_str(
                        config_str ) );

                if( !node_id_str.empty() )
                {
                    node_index = this->nodeIndex(
                        lock, node_id_str.c_str(), _this_t::NODE_ID_STR );
                }

                if( node_index == _this_t::UNDEFINED_INDEX )
                {
                    /* TODO: Properly implement searching for a node_index
                     * by unique str from a config_str; for now, interpret
                     * the config_str as a whole as the unique_str */

                    node_index = this->nodeIndex(
                        lock, config_str, _this_t::NODE_UNIQUE_ID_STR );
                }

                if( node_index != _this_t::UNDEFINED_INDEX )
                {
                    status = select_fn( lock, node_index );
                }
            }

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( this->usesAutoSelect() ) )
            {
                status = this->doInitialSelectDefaultNode( lock, select_fn );
            }
        }

        return status;
    }

    NodeControllerBase::status_t
    NodeControllerBase::doInitiallySelectDefaultNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::selectNodeFn select_fn )
    {
        using _this_t = st::NodeControllerBase;
        using index_t = _this_t::node_index_t;

        NodeControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->isSyncWithNodeStore() ) && ( select_fn != nullptr ) )
        {
            if( this->hasDefaultNode( lock ) )
            {
                index_t const node_index = this->defaultNodeIndex( lock );

                if( node_index != _this_t::UNDEFINED_INDEX )
                {
                    status = select_fn( lock, node_index );
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::doUpdateNodeStore(
        NodeControllerBase::node_store_t& SIXTRL_RESTRICT_REF node_store )
    {
        using _this_t = st::NodeControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->ptrNodeStore() == &node_store )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }
        else if( (  this->ptrNodeStore() != &node_store ) &&
                 (  this->nodeStore().lockable() != node_store.lockable() ) )
        {
            _this_t::lock_t old_store_lock( *this->nodeStore().lockable() );

            if( this->hasSelectedNode( old_store_lock ) )
            {
                return status;
            }

            if( this->isSyncWithNodeStore() )
            {
                this->doClearNodeControllerBaseImpl( lock );
            }

            if( this->nodeStore().hasController( old_store_lock, this ) )
            {
                this->doDetachAllNodes( lock );
            }

            _this_t::lock_t new_store_lock( *this->nodeStore().lockable() );

            this->m_node_store = node_store;
            old_store_lock.unlock();

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    void NodeControllerBase::doSetIsSyncWithNodeStoreFlag(
        bool const is_sync_with_node_store ) SIXTRL_NOEXCEPT
    {
        this->m_nodes_are_sync = is_sync_with_node_store;
    }

    /* --------------------------------------------------------------------- */

    bool NodeControllerBase::doCheckIfNodeIndexIsAvailableLocallyWithoutLock(
        NodeControllerBase::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::NodeControllerBase;

        bool is_node_available = false;

        if( ( index != NodeControllerBase::UNDEFINED_INDEX ) &&
            ( index >= _this_t::node_index_t{ 0 } ) &&
            ( this->isSyncWithNodeStore() ) &&
            ( static_cast< _this_t::size_type >( index ) <
              this->m_available_node_ids.size() ) &&
            ( this->m_available_node_ids[ index ].valid() ) )
        {
            is_node_available = true;
        }

        return is_node_available;
    }

    bool NodeControllerBase::doCheckIfNodeIndexIsAvailableLocally(
            NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
            NodeControllerBase::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        bool is_node_available = false;

        if( ( this->doCheckIfNodeIndexIsAvailableLocallyWithoutLock( index ) ) &&
            ( this->nodeStore().checkLock( lock ) ) &&
            ( index < this->numAvailableNodes( lock ) ) &&
            ( this->nodeStore().hasController( lock, *this ) ) &&
            ( this->isNodeAttachedToController( lock, index, *this ) ) )
        {
            is_node_available = true;
        }

        return is_node_available;
    }

    /* --------------------------------------------------------------------- */

    void NodeControllerBase::doClearNodeControllerBaseImpl(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF
            lock ) SIXTRL_NOEXCEPT
    {
        using _this_t = NodeControllerBase;
        using size_t = _this_t::size_type;

        if( this->nodeStore().checkLock( lock ) )
        {
            if( this->nodeStore().numNodes( lock, *this ) > size_t{ 0 } )
            {
                _this_t::status_t const status = this->doDetachAllNodes( lock );
                SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
                ( void )status;
            }

            this->m_available_node_indices.clear();
            this->m_available_node_ids.clear();
            this->m_available_node_id_strings.clear();

            this->m_selected_node_index = _this_t::UNDEFINED_INDEX;
            this->m_default_node_index = _this_t::UNDEFINED_INDEX;
            this->m_num_available_nodes = _this_t::node_index_t{ 0 };

            this->doSetIsSyncWithNodeStoreFlag( false );
        }

        return;
    }
}

/* end: sixtracklib/common/control/node_controller_base.cpp */
