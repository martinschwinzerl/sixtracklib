#include "sixtracklib/common/control/node_info.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <sstream>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_store.hpp"
#include "sixtracklib/common/control/node_set.hpp"

namespace  st = SIXTRL_CXX_NAMESPACE;
using _info_t = st::NodeInfoBase;

namespace SIXTRL_CXX_NAMESPACE
{
    constexpr _info_t::arch_id_t     _info_t::ARCH_ILLEGAL;
    constexpr _info_t::platform_id_t _info_t::ILLEGAL_PLATFORM_ID;
    constexpr _info_t::device_id_t   _info_t::ILLEGAL_DEVICE_ID;
    constexpr _info_t::node_index_t  _info_t::UNDEFINED_INDEX;
    constexpr _info_t::node_set_id_t _info_t::ILLEGAL_NODE_SET_ID;
    constexpr _info_t::size_type     _info_t::DEFAULT_MAX_SELECTION_COUNTER;

    /* ********************************************************************* */

    NodeInfoBase::NodeInfoBase(
        NodeInfoBase::arch_id_t const arch_id,
        const char *const SIXTRL_RESTRICT platform_name,
        const char *const SIXTRL_RESTRICT device_name,
        const char *const SIXTRL_RESTRICT description,
        _info_t::platform_id_t const platform_id,
        _info_t::device_id_t const device_id,
        st::NodeStore* SIXTRL_RESTRICT ptr_node_store ) :
            st::ArchInfo( arch_id ),
            m_node_id( arch_id, platform_id, device_id ),
            m_platform_name(), m_device_name(), m_description(), m_unique_id(),
            m_ptr_node_store( ptr_node_store ),
            m_max_selection_cnt( _info_t::DEFAULT_MAX_SELECTION_COUNTER ),
            m_node_index_in_store( _info_t::UNDEFINED_INDEX )
    {
        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
    }

    NodeInfoBase::NodeInfoBase(
        _info_t::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        const char *const SIXTRL_RESTRICT platform_name,
        const char *const SIXTRL_RESTRICT device_name,
        const char *const SIXTRL_RESTRICT description,
        st::NodeStore* SIXTRL_RESTRICT ptr_node_store ) :
            st::ArchInfo( node_id.archId() ),
            m_node_id( node_id ),
            m_platform_name(), m_device_name(), m_description(), m_unique_id(),
            m_ptr_node_store( ptr_node_store ),
            m_max_selection_cnt( _info_t::DEFAULT_MAX_SELECTION_COUNTER ),
            m_node_index_in_store( _info_t::UNDEFINED_INDEX )
    {
        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
    }

    NodeInfoBase::NodeInfoBase(
        const NodeInfoBase::c_node_id_t *const SIXTRL_RESTRICT ptr_node_id,
        const char *const SIXTRL_RESTRICT platform_name,
        const char *const SIXTRL_RESTRICT device_name,
        const char *const SIXTRL_RESTRICT description,
        st::NodeStore* SIXTRL_RESTRICT ptr_node_store ) :
            st::ArchInfo( ::NS(NodeId_get_arch_id)( ptr_node_id ) ),
            m_node_id( ::NS(NodeId_get_arch_id)( ptr_node_id ),
                ::NS(NodeId_get_platform_id)( ptr_node_id ),
                ::NS(NodeId_get_device_id)( ptr_node_id ) ),
            m_platform_name(), m_device_name(), m_description(), m_unique_id(),
            m_ptr_node_store( ptr_node_store ),
            m_max_selection_cnt( _info_t::DEFAULT_MAX_SELECTION_COUNTER ),
            m_node_index_in_store( _info_t::UNDEFINED_INDEX )
    {
        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
    }

    NodeInfoBase::NodeInfoBase(
        _info_t::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name,
        std::string const& SIXTRL_RESTRICT_REF device_name,
        std::string const& SIXTRL_RESTRICT_REF description,
        _info_t::platform_id_t const platform_id,
        _info_t::device_id_t const device_id,
        st::NodeStore* SIXTRL_RESTRICT ptr_node_store ) :
            st::ArchInfo( arch_id ),
            m_node_id( arch_id, platform_id, device_id ),
            m_platform_name(), m_device_name(), m_description(), m_unique_id(),
            m_ptr_node_store( ptr_node_store ),
            m_max_selection_cnt( NodeInfoBase::DEFAULT_MAX_SELECTION_COUNTER ),
            m_node_index_in_store( _info_t::UNDEFINED_INDEX )
    {
        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
    }

    NodeInfoBase::NodeInfoBase(
        _info_t::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name,
        std::string const& SIXTRL_RESTRICT_REF device_name,
        std::string const& SIXTRL_RESTRICT_REF description,
        st::NodeStore* SIXTRL_RESTRICT ptr_node_store ) :
            st::ArchInfo( node_id.archId() ),
            m_node_id( node_id ),
            m_platform_name(), m_device_name(), m_description(), m_unique_id(),
            m_ptr_node_store( ptr_node_store ),
            m_max_selection_cnt( _info_t::DEFAULT_MAX_SELECTION_COUNTER ),
            m_node_index_in_store( _info_t::UNDEFINED_INDEX )
    {
        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
    }

    NodeInfoBase::NodeInfoBase(
        const _info_t::c_node_id_t *const SIXTRL_RESTRICT ptr_node_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name,
        std::string const& SIXTRL_RESTRICT_REF device_name,
        std::string const& SIXTRL_RESTRICT_REF description,
        st::NodeStore* SIXTRL_RESTRICT ptr_node_store ) :
            st::ArchInfo( ::NS(NodeId_get_arch_id)( ptr_node_id ) ),
            m_node_id( ::NS(NodeId_get_arch_id)( ptr_node_id ),
                ::NS(NodeId_get_platform_id)( ptr_node_id ),
                ::NS(NodeId_get_device_id)( ptr_node_id ) ),
            m_platform_name(), m_device_name(), m_description(), m_unique_id(),
            m_ptr_node_store( ptr_node_store ),
            m_max_selection_cnt( _info_t::DEFAULT_MAX_SELECTION_COUNTER ),
            m_node_index_in_store( _info_t::UNDEFINED_INDEX )
    {
        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
    }

    /* --------------------------------------------------------------------- */

    st::NodeStore const& NodeInfoBase::nodeStore() const
    {
        if( this->m_ptr_node_store == nullptr )
        {
            throw std::runtime_error( "not managed by NodeStore instance" );
        }

        return *this->m_ptr_node_store;
    }

    _info_t::status_t NodeInfoBase::assignToNodeStore(
        st::NodeStore& SIXTRL_RESTRICT_REF store )
    {
        _info_t::status_t status = st::ARCH_STATUS_SUCCESS;

        if( this->m_ptr_node_store == nullptr )
        {
            this->m_ptr_node_store = &store;
        }
        else if( this->m_ptr_node_store != nullptr )
        {
            status = st::ARCH_STATUS_GENERAL_FAILURE;
        }

        SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
            ( this->m_ptr_node_store == &store ) );

        return status;
    }

    /* --------------------------------------------------------------------- */

    _info_t::node_id_t const& NodeInfoBase::nodeId(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        if( this->ptrNodeStore() != nullptr )
        {
            this->checkLockOrThrowOnError( lock );
        }

        return this->m_node_id;
    }

    _info_t::node_id_t const* NodeInfoBase::ptrNodeId(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->ptrNodeStore() != nullptr ) ||
                 ( this->checkLock( lock ) ) ) ? &this->m_node_id : nullptr;
    }

    _info_t::c_node_id_t const* NodeInfoBase::ptrCNodeId(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->ptrNodeStore() != nullptr ) ||
                 ( this->checkLock( lock ) ) )
            ? this->m_node_id.getCApiPtr() : nullptr;
    }

    _info_t::platform_id_t NodeInfoBase::platformId(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->ptrNodeStore() != nullptr ) ||
                 ( this->checkLock( lock ) ) )
            ? this->m_node_id.platformId() : _info_t::ILLEGAL_PLATFORM_ID;
    }

    _info_t::device_id_t NodeInfoBase::deviceId(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->ptrNodeStore() != nullptr ) ||
                 ( this->checkLock( lock ) ) )
            ? this->m_node_id.deviceId() : _info_t::ILLEGAL_DEVICE_ID;
    }

    _info_t::status_t NodeInfoBase::setPlatformId(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _info_t::platform_id_t const platform_id )
    {
        _info_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _info_t::platform_id_t const saved_platform_id =
                    this->m_node_id.platformId();

        if( ( this->ptrNodeStore() == nullptr ) &&
            ( this->m_node_index_in_store == _info_t::UNDEFINED_INDEX ) )
        {
            status = this->m_node_id.setPlatformId( platform_id );
        }
        else if( this->checkLock( lock ) )
        {
            SIXTRL_ASSERT( this->ptrNodeStore() != nullptr );

            if( this->m_node_index_in_store != _info_t::UNDEFINED_INDEX )
            {
                status = this->m_node_id.setPlatformId( platform_id );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = this->ptrNodeStore()->doUpdateNodeId(
                        lock, this->m_node_index_in_store, this->m_node_id );
                }
            }
            else
            {
                status = this->m_node_id.setPlatformId( platform_id );
            }
        }

        if( status != st::ARCH_STATUS_SUCCESS )
        {
            this->m_node_id.setPlatformId( saved_platform_id );
        }

        return status;
    }

    _info_t::status_t NodeInfoBase::setDeviceId(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _info_t::device_id_t const device_id )
    {
        _info_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _info_t::device_id_t const saved_device_id = this->m_node_id.deviceId();

        if( ( this->ptrNodeStore() == nullptr ) &&
            ( this->m_node_index_in_store == _info_t::UNDEFINED_INDEX ) )
        {
            status = this->m_node_id.setDeviceId( device_id );
        }
        else if( this->checkLock( lock ) )
        {
            SIXTRL_ASSERT( this->ptrNodeStore() != nullptr );

            if( this->m_node_index_in_store != _info_t::UNDEFINED_INDEX )
            {
                status = this->m_node_id.setDeviceId( device_id );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = this->ptrNodeStore()->doUpdateNodeId(
                        lock, this->m_node_index_in_store, this->m_node_id );
                }
            }
            else
            {
                status = this->m_node_id.setDeviceId( device_id );
            }
        }

        if( status != st::ARCH_STATUS_SUCCESS )
        {
            this->m_node_id.setDeviceId( saved_device_id );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _info_t::node_index_t NodeInfoBase::nodeIndex(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? this->m_node_index_in_store : _info_t::UNDEFINED_INDEX;
    }

    _info_t::status_t NodeInfoBase::setNodeIndex(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _info_t::node_index_t const node_index )
    {
        _info_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->checkLock( lock ) )
        {
            if( ( ( this->m_node_index_in_store == _info_t::UNDEFINED_INDEX ) &&
                  ( node_index != _info_t::UNDEFINED_INDEX ) ) ||
                ( ( this->m_node_index_in_store != _info_t::UNDEFINED_INDEX ) &&
                  ( node_index == _info_t::UNDEFINED_INDEX ) ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    void NodeInfoBase::setPlatformName(
        const char *const SIXTRL_RESTRICT platform_name )
    {
        if( ( platform_name != nullptr ) &&
            ( std::strlen( platform_name ) > NodeInfoBase::size_type{ 0 } ) )
        {
            this->m_platform_name = platform_name;
        }
        else
        {
            this->m_platform_name.clear();
        }
    }

    void NodeInfoBase::setDeviceName(
        const char *const SIXTRL_RESTRICT device_name )
    {
        if( ( device_name != nullptr ) &&
            ( std::strlen( device_name ) > NodeInfoBase::size_type{ 0 } ) )
        {
            this->m_device_name = device_name;
        }
        else
        {
            this->m_device_name.clear();
        }
    }

    void NodeInfoBase::setDescription(
        const char *const SIXTRL_RESTRICT description )
    {
        if( ( description != nullptr ) &&
            ( std::strlen( description ) > NodeInfoBase::size_type{ 0 } ) )
        {
            this->m_description = description;
        }
        else
        {
            this->m_description.clear();
        }
    }

    /* --------------------------------------------------------------------- */

    bool NodeInfoBase::isAttachedToAnySet( NodeInfoBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        bool is_attached_to_any = false;

        if( ( this->checkLock( lock ) ) &&
            ( this->m_node_index_in_store != _info_t::UNDEFINED_INDEX ) &&
            ( this->m_max_attachement_cnt > _info_t::size_type{ 0 } ) &&
            ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->isNodeAttachedToAnySet( lock,
                    this->m_node_index_in_store ) ) &&
            ( this->m_ptr_node_store->ptrNodeInfoBase( lock,
                    this->m_node_index_in_store ) == this ) )
        {
            is_attached_to_any = true;
        }

        return is_attached_to_any;
    }

    _info_t::size_type NodeInfoBase::numAttachedSets( _info_t::lock_t
        const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        _info_t::size_type num_attached_sets = _info_t::size_type{ 0 };

        if( ( this->checkLock( lock ) ) &&
            ( this->m_node_index_in_store != _info_t::UNDEFINED_INDEX ) &&
            ( this->m_max_attachement_cnt > _info_t::size_type{ 0 } ) &&
            ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->ptrNodeInfoBase( lock,
                    this->m_node_index_in_store ) == this ) )
        {
            num_attached_sets = this->m_ptr_node_store->numSetsAttachedToNode(
                lock, this->m_node_index_in_store );
        }

        return num_attached_sets;
    }

    bool NodeInfoBase::isAttachedToSet(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _info_t::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        bool is_attached_to_set = false;

        if( ( node_set_id != _info_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->checkLock( lock ) ) &&
            ( this->m_node_index_in_store != _info_t::UNDEFINED_INDEX ) &&
            ( this->m_max_attachement_cnt > _info_t::size_type{ 0 } ) &&
            ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->ptrNodeInfoBase( lock,
                    this->m_node_index_in_store ) == this ) )
        {
            is_attached_to_set = this->m_ptr_node_store->isNodeAttachedToSet(
                lock, this->m_node_index_in_store, node_set_id );
        }

        return is_attached_to_set;
    }

    /* --------------------------------------------------------------------- */

    bool NodeInfoBase::isSelectedByAnySet(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        bool is_selected_by_any = false;

        if( ( this->checkLock( lock ) ) &&
            ( this->isAttachedToAnySet( lock ) ) &&
            ( this->m_max_selection_cnt > _info_t::size_type{ 0 } ) &&
            ( this->m_ptr_node_store->isNodeSelectedByAnySet( lock,
                    this->m_node_index_in_store ) ) )
        {
            is_selected_by_any = true;
        }

        return is_selected_by_any;
    }

    _info_t::size_type NodeInfoBase::numSelectionCount(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        _info_t::size_type num_selected_sets = _info_t::size_type{ 0 };

        if( ( this->checkLock( lock ) ) &&
            ( this->isAttachedToAnySet( lock ) ) &&
            ( this->m_max_selection_cnt > _info_t::size_type{ 0 } ) )
        {
            num_selected_sets = this->m_ptr_node_store->numSelectingSetsForNode(
                lock, this->m_node_index_in_store );
        }

        return num_selected_sets;
    }

    bool NodeInfoBase::isSelectedBySet(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _info_t::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        bool is_selected_by_set = false;

        if( ( this->checkLock( lock ) ) &&
            ( this->isAttachedToAnySet( lock ) ) &&
            ( this->m_max_selection_cnt > _info_t::size_type{ 0 } ) &&
            ( this->m_ptr_node_store->isNodeSelectedBySet( lock,
                    this->m_node_index_in_store, node_set_id ) ) )
        {
            is_selected_by_set = true;
        }

        return is_selected_by_set;
    }

    bool NodeInfoBase::isDefaultForSet(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _info_t::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        bool is_selected_by_set = false;

        if( ( this->checkLock( lock ) ) &&
            ( this->isAttachedToAnySet( lock ) ) &&
            ( this->m_ptr_node_store->isNodeDefaultForSet( lock,
                    this->m_node_index_in_store, node_set_id ) ) )
        {
            is_selected_by_set = true;
        }

        return is_selected_by_set;
    }

    /* --------------------------------------------------------------------- */

    NodeInfoBase::size_type NodeInfoBase::requiredOutStringLength(
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        _info_t::size_type requ_out_str_len = _info_t::size_type{ 0 };

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _info_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            requ_out_str_len = this->requiredOutStringLength(
                lock, node_set_id );
        }
        else
        {
            _info_t::lock_t lock;
            requ_out_str_len =
                this->requiredOutStringLength( lock, node_set_id );
        }

        return requ_out_str_len;

    }

    void NodeInfoBase::print(
        std::ostream& SIXTRL_RESTRICT_REF output,
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _info_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            this->print( lock, output, node_set_id );
        }
        else
        {
            _info_t::lock_t lock;
            this->print( lock, output, node_set_id );
        }
    }

    void NodeInfoBase::print( ::FILE* SIXTRL_RESTRICT output,
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _info_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            this->print( lock, output, node_set_id );
        }
        else
        {
            _info_t::lock_t lock;
            this->print( lock, output, node_set_id );
        }
    }

    void NodeInfoBase::printOut(
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _info_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            this->print( lock, std::cout, node_set_id );
        }
        else
        {
            _info_t::lock_t lock;
            this->print( lock, std::cout, node_set_id );
        }
    }

    std::string NodeInfoBase::toString(
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _info_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            return this->toString( lock, node_set_id );
        }

        _info_t::lock_t lock;
        return this->toString( lock, node_set_id );
    }

    NodeInfoBase::status_t NodeInfoBase::toString(
        NodeInfoBase::size_type const out_str_capacity,
        char* SIXTRL_RESTRICT out_str,
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        _info_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _info_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            status = this->toString(
                lock, out_str_capacity, out_str, node_set_id );
        }
        else
        {
            _info_t::lock_t lock;
            status = this->toString(
                lock, out_str_capacity, out_str, node_set_id );
        }

        return status;
    }

    std::ostream& operator<<(
        std::ostream& SIXTRL_RESTRICT_REF output,
        SIXTRL_CXX_NAMESPACE::NodeInfoBase const& SIXTRL_RESTRICT_REF info )
    {
        info.print( output );
        return output;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    NodeInfoBase::size_type NodeInfoBase::requiredOutStringLength(
        NodeInfoBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        std::ostringstream a2str;
        this->doPrintToOutputStream( lock, a2str, node_set_id );
        return a2str.str().size() + _info_t::size_type{ 1 };
    }

    void NodeInfoBase::print(
        NodeInfoBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::ostream& SIXTRL_RESTRICT_REF output,
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        _info_t::status_t status = this->doPrintToOutputStream(
            lock, output, node_set_id );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;

        return;
    }

    void NodeInfoBase::print(
        NodeInfoBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        ::FILE* SIXTRL_RESTRICT output,
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        if( output != nullptr )
        {
            std::ostringstream a2str;
            _info_t::status_t status = this->doPrintToOutputStream(
                lock, a2str, node_set_id );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                std::string const temp_str( a2str.str() );

                int const ret = std::fprintf( output, "%s", temp_str.c_str() );
                SIXTRL_ASSERT( ret > 0 );
                ( void )ret;
            }
        }
    }

    void NodeInfoBase::printOut(
        NodeInfoBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        this->print( lock, std::cout, node_set_id );
    }

    std::string NodeInfoBase::toString(
        NodeInfoBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        std::ostringstream a2str;

        if( this->doPrintToOutputStream( lock, a2str, node_set_id ) ==
            st::ARCH_STATUS_SUCCESS )
        {
            return a2str.str();
        }

        return std::string{};
    }

    NodeInfoBase::status_t NodeInfoBase::toString(
        NodeInfoBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeInfoBase::size_type const out_str_capacity,
        char* SIXTRL_RESTRICT out_str,
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        _info_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( out_str_capacity > _info_t::size_type{ 0 } ) &&
            ( out_str != nullptr ) )
        {
            std::fill( out_str, out_str + out_str_capacity, char{ '\0' } );
            std::ostringstream a2str;

            status = this->doPrintToOutputStream( lock, a2str, node_set_id );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                std::string const temp_str( a2str.str() );

                if( ( !temp_str.empty() ) &&
                    ( temp_str.size() < out_str_capacity ) )
                {
                    std::strncpy( out_str, temp_str.c_str(), temp_str.size() );
                }
                else
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }
        }

        return status;
    }


    /* --------------------------------------------------------------------- */

    _info_t::status_t NodeInfoBase::doPrintToOutputStream(
        _info_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::ostream& SIXTRL_RESTRICT_REF output,
        _info_t::node_set_id_t const node_set_id ) const
    {
        using size_t = _info_t::size_type;

        char temp_node_id_str[ 32 ] =
        {
            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
        };

        _info_t::status_t status = this->nodeId().toString(
            temp_node_id_str, 32, st::NODE_ID_STR_FORMAT_NOARCH );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            bool has_node_store = false;
            bool is_attached_to_any = false;
            bool is_attached_to_set = false;
            bool is_selected_by_set = false;
            bool is_default_node_for_set = false;

            if( ( this->m_ptr_node_store != nullptr ) &&
                ( this->checkLock( lock ) ) &&
                ( this->m_node_index_in_store != _info_t::UNDEFINED_INDEX ) )
            {
                has_node_store = true;

                is_attached_to_any = this->isAttachedToAnySet( lock );

                if( is_attached_to_any )
                {
                    if( node_set_id != _info_t::ILLEGAL_NODE_SET_ID )
                    {
                        is_attached_to_set = this->isAttachedToSet(
                            lock, node_set_id );

                        is_selected_by_set = this->isSelectedBySet(
                            lock, node_set_id );

                        is_default_node_for_set = this->isDefaultForSet(
                                lock, node_set_id );
                    }
                }
            }

            output << "Node            : " << temp_node_id_str;

            if( is_default_node_for_set )
            {
                SIXTRL_ASSERT( this->m_ptr_node_store != nullptr );
                SIXTRL_ASSERT( this->checkLock( lock ) );
                SIXTRL_ASSERT( node_set_id != _info_t::ILLEGAL_NODE_SET_ID );
                output << " [ DEFAULT ]";
            }

            if( is_selected_by_set )
            {
                SIXTRL_ASSERT( this->m_ptr_node_store != nullptr );
                SIXTRL_ASSERT( this->checkLock( lock ) );
                SIXTRL_ASSERT( node_set_id != _info_t::ILLEGAL_NODE_SET_ID );
                output << " [ SELECTED ]";
            }

            output << "\r\n";

            if( is_attached_to_any )
            {
                SIXTRL_ASSERT( this->m_ptr_node_store != nullptr );
                SIXTRL_ASSERT( this->checkLock( lock ) );

                output << " attached to    : [ ";

                auto set_it  =
                    this->m_ptr_node_store->attachedNodeSetIdsBegin(
                        lock, this->m_node_index_in_store );

                auto set_end =
                    this->m_ptr_node_store->attachedNodeSetIdsEnd(
                        lock, this->m_node_index_in_store );

                bool first = true;
                std::ptrdiff_t num_sets = std::distance( set_it, set_end );
                SIXTRL_ASSERT( num_sets > std::ptrdiff_t{ 0 } );

                for( ; set_it != set_end ; ++set_it )
                {
                    if( first )
                    {
                        first = false;
                    }
                    else
                    {
                        output << ", ";
                    }

                    if( ( !is_attached_to_set ) ||
                        ( num_sets == std::ptrdiff_t{ 1 } ) ||
                        ( node_set_id == _info_t::ILLEGAL_NODE_SET_ID ) ||
                        ( *set_it != node_set_id ) )
                    {
                        output << *set_it;
                    }
                    else
                    {
                        output << "(" << *set_it << ")";
                    }
                }

                output << " ]\r\n";

                if( this->m_ptr_node_store->isNodeSelectedByAnySet( lock,
                        this->m_node_index_in_store ) )
                {
                    output << " selected by    : [ ";

                    auto set_it  =
                        this->m_ptr_node_store->selectingNodeSetIdsBegin(
                            lock, this->m_node_index_in_store );

                    auto set_end =
                        this->m_ptr_node_store->selectingNodeSetIdsEnd(
                            lock, this->m_node_index_in_store );

                    bool first = true;
                    num_sets = std::distance( set_it, set_end );

                    for( ; set_it != set_end ; ++set_it )
                    {
                        if( first )
                        {
                            first = false;
                        }
                        else
                        {
                            output << ", ";
                        }

                        if( ( !is_selected_by_set ) ||
                            ( num_sets == std::ptrdiff_t{ 1 } ) ||
                            ( node_set_id == _info_t::ILLEGAL_NODE_SET_ID ) ||
                            ( *set_it != node_set_id ) )
                        {
                            output << *set_it;
                        }
                        else
                        {
                            output << "(" << *set_it << ")";
                        }
                    }

                    output << " ]\r\n";
                }
            }

            output << "\r\nArchitecture    : " << this->archId();

            if( this->hasArchStr() )
            {
               output << "( " << this->archStr() << " )";
            }

            if( this->hasPlatformName() )
            {
                output << "Platform        : "
                       << this->platformName() << "\r\n";
            }

            if( this->hasDeviceName() )
            {
                output << "Device          : "
                       << this->deviceName() << "\r\n";
            }

            if( this->hasDescription() )
            {
                output << "Description     : "
                       << this->description() << "\r\n";
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    void NodeInfoBase::doSetUniqueIdStr(
            char const* SIXTRL_RESTRICT_REF unique_id_str )
    {
        if( ( unique_id_str != nullptr ) &&
            ( std::strlen( unique_id_str ) > NodeInfoBase::size_type{ 0 } ) )
        {
            this->m_unique_id = unique_id_str;
        }
        else
        {
            this->m_unique_id.clear();
        }
    }

    void NodeInfoBase::doSetMaxAttachementCount(
        NodeInfoBase::size_type const max_attachement_count ) SIXTRL_NOEXCEPT
    {
        this->m_max_attachement_cnt = max_attachement_count;
    }

    void NodeInfoBase::doSetMaxSelectionCount(
        NodeInfoBase::size_type const max_selection_count ) SIXTRL_NOEXCEPT
    {
        this->m_max_selection_cnt = max_selection_count;
    }
}

/* end: sixtracklib/common/control/node_info.cpp */
