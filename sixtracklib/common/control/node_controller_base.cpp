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

    NodeControllerBase::status_t NodeControllerBase::initializeNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const node_index )
    {
        NodeControllerBase::status_t status =
            SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        SIXTRL_ASSERT( this->nodeStore().checkLock( lock ) );

        if( ( node_index != NodeControllerBase::UNDEFINED_INDEX ) &&
            ( this->isNodeAvailable( lock, node_index ) ) )
        {
            status = this->doInitializeNode( lock, node_index );
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
                    lock, this->m_selected_node_index, this ) ) &&
              ( this->nodeStore().isNodeSelectedByController(
                    lock, this->m_selected_node_index, this ) ) ) );

        return has_selected_node;
    }

    /* --------------------------------------------------------------------- */

    bool NodeControllerBase::hasDefaultNode() const SIXTRL_NOEXCEPT
    {
        using _this_t = NodeControllerBase;

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
                    lock, this->m_default_node_index, this ) ) ) );

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
                lock, platform_id, device_id );

            if( !this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) )
            {
                index = _this_t::UNDEFINED_INDEX;
            }
        }

        return index;
    }

    /* --------------------------------------------------------------------- */

    void NodeControllerBase::printAvailableNodeInfos(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );

        NodeControllerBase::status_t
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

        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );

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
        using size_t = NodeControllerBase::size_type;

        if( ( capacity > size_t{ 0 } ) && ( node_info_str != nullptr ) )
        {
            std::memset( node_info_str, static_cast< int >( '\0' ),
                         capacity );

            std::string const str_repr = this->availableNodeInfosToString();

            if( str_repr.size() < capacity )
            {
                std::strncpy( node_info_str, str_repr.c_str(),
                              capacity - size_t{ 1 }  );

                status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    void NodeControllerBase::doClear()
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        this->doClearNodeControllerBaseImpl( lock );
    }

    /* --------------------------------------------------------------------- */

    bool NodeControllerBase::doCheckIsNodeInitialized(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const index )
    {
        ( void )lock;
        ( void )index;

        return false;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::doInitializeNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const index )
    {
        ( void )lock;
        ( void )index;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::doSyncWithNodeStore(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_store_t* SIXTRL_RESTRICT ptr_node_store )
    {
        using _this_t   = NodeControllerBase;
        using size_t    = _this_t::size_type;
        using index_t   = _this_t::node_index_t;
        using node_id_t = _this_t::node_id_t;

        NodeControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( !this->nodeStore().checkLock( lock ) ) ||
            ( !this->nodeStore().hasArchitecture( lock, this->archId() ) ) ||
            ( !this->nodestore().hasController( lock, *this ) ) )
        {
            return status;
        }

        if( this->nodeStore().numNodes( lock, *this ) > size_t{ 0 } )
        {
            index_t const total_num_nodes_in_store =
                this->nodeStore().totalNumNodes( lock );

            std::vector< index_t > temp_node_indices(
                total_num_nodes_in_store, _this_t::UNDEFINED_INDEX );

            size_t nodes_copied = size_t{ 0 };

            status = this->nodeStore().nodeIndices(
                lock, temp_node_indices.begin(), temp_node_indices.end(),
                    *this, &nodes_copied );

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
                    index_t const index = temp_node_indices[ ii ];

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
                        this->m_available_node_id_strings.back().size(),
                        this->m_available_node_id_strings.back().data() );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        this->m_available_node_indices.push_back( index );
                        this->m_available_node_ids.pus_back( *ptr );
                        ++this->m_num_available_nodes:.back()
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
        ( void )lock;
        ( void )node_index;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::doChangeSelectedNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const new_selected_node_index )
    {
        ( void )lock;
        ( void )new_selected_node_index;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::doUnselectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const selected_node_index )
    {
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

        using index_t = NodeControllerBase::node_index_t{ 0 };

        if( this->numAvailableNodes( lock ) >
            NodeControllerBase::index_t{ 0 } )
        {
            status = st::ARCH_STATUS_SUCCESS:

            auto it  = this->nodeIndicesBegin( lock );
            auto end = this->nodeIndicesEnd( lock );

            SIXTRL_ASSERT( it != nullptr );

            for( ; it != end ; ++it )
            {
                auto ptr_node_info = this->ptrNodeInfoBase( lock, *it );

                if( ptr_node_info != nullptr )
                {
                    output << *ptr_node_info << "\r\n";
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::status_t NodeControllerBase::doAttachAllArchNodes(
        NodeControllerBase::lock_t const& SIXTRL_RESTRIC_REF lock )
    {
        NodeControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

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

    void NodeControllerBase::doSetIsSyncWithNodeStoreFlag(
        bool const is_sync_with_node_store ) SIXTRL_NOEXCEPT
    {
        this->m_nodes_are_sync = is_sync_with_node_store;
    }

    /* --------------------------------------------------------------------- */

    bool NodeControllerBase::doCheckIfNodeIndexIsAvailableLocally(
            NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
            NodeControllerBase::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        bool is_node_available = false;

        if( ( index != NodeControllerBase::UNDEFINED_INDEX ) &&
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
