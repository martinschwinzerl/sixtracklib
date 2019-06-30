#include "sixtracklib/common/control/node_info.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <sstream>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_id.hpp"
#include "sixtracklib/common/control/arch_info.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    NodeInfoBase::NodeInfoBase(
        NodeInfoBase::arch_id_t const arch_id,
        const char *const SIXTRL_RESTRICT arch_str,
        const char *const SIXTRL_RESTRICT platform_name,
        const char *const SIXTRL_RESTRICT device_name,
        const char *const SIXTRL_RESTRICT description,
        NodeInfoBase::platform_id_t const platform_id,
        NodeInfoBase::device_id_t const device_id ) :
            st::ArchInfo( arch_id, arch_str ),
            m_platform_name(), m_device_name(), m_description(), m_unique_id(),
            m_max_selection_cnt( NodeInfoBase::DEFAULT_MAX_SELECTION_COUNTER ),
            m_node_id( arch_id, platform_id, device_id )
    {
        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
    }

    NodeInfoBase::NodeInfoBase(
        NodeInfoBase::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        std::string const& SIXTRL_RESTRICT_REF platform_name,
        std::string const& SIXTRL_RESTRICT_REF device_name,
        std::string const& SIXTRL_RESTRICT_REF description,
        NodeInfoBase::platform_id_t const platform_id,
        NodeInfoBase::device_id_t const device_id ) :
            st::ArchInfo( arch_id, arch_str ),
            m_platform_name(), m_device_name(), m_description(), m_unique_id(),
            m_max_selection_cnt( NodeInfoBase::DEFAULT_MAX_SELECTION_COUNTER ),
            m_node_id( arch_id, platform_id, device_id )
    {
        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
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

    bool NodeInfoBase::isAttachedToAnyController() const
    {
        NodeInfoBase::node_index_t const node_index =
            st::NodeStore_get().findNodeIndex( this );

        return ( ( node_index != NodeStore::UNDEFINED_INDEX ) &&
                 ( st::NodeStore_get().isNodeAttachedToAnyController(
                    node_index ) ) );
    }

    NodeInfoBase::size_type NodeInfoBase::numAttachedControllers() const
    {
        NodeInfoBase::node_index_t const index =
            st::NodeStore_get().findNodeIndex( this );

        return ( ( index != NodeStore::UNDEFINED_INDEX ) &&
            ( st::NodeStore_get().numControllersAttachedToNode( index ) ) );
    }

    bool NodeInfoBase::isAttachedTo( NodeInfoBase::controller_base_t const&
        SIXTRL_RESTRICT controller ) const
    {
        NodeInfoBase::node_index_t const index =
            st::NodeStore_get().findNodeIndex( this );

        return ( ( index != NodeStore::UNDEFINED_INDEX ) &&
            ( st::NodeStore_get().isNodeAttachedToController(
                index, controller ) ) );
    }

    bool NodeInfoBase::isSelected() const
    {
        NodeInfoBase::node_index_t const index =
            st::NodeStore_get().findNodeIndex( this );

        return ( ( index != NodeStore::UNDEFINED_INDEX ) &&
            (
    }

    bool NodeInfoBase::isSelectedBy( NodeInfoBase::controller_base_t const&
        SIXTRL_RESTRICT controller ) const
    {

    }

    NodeInfoBase::size_type NodeInfoBase::numSelectingControllers() const
    {

    }

    /* --------------------------------------------------------------------- */

    NodeInfoBase::size_type NodeInfoBase::requiredOutStringLength(
        NodeInfoBase::controller_base_t const* SIXTRL_RESTRICT ctrl ) const
    {
        return this->toString( ctrl ).size() + NodeInfoBase::size_type{ 1 };
    }

    void NodeInfoBase::print( ::FILE* SIXTRL_RESTRICT output,
        NodeInfoBase::controller_base_t const* SIXTRL_RESTRICT ctrl ) const
    {
        if( output != nullptr )
        {
            std::string const str_repr = this->toStrig( ptr_controller );

            if( !str_repr.empty() )
            {
                int const ret = std::fprintf( output, "%s", str_repr.c_str() );
                SIXTRL_ASSERT( ret > 0 );
                ( void )ret;
            }
        }
    }

    void NodeInfoBase::printOut(
        NodeInfoBase::controller_base_t const* SIXTRL_RESTRICT ctrl ) const
    {
        this->print( stdout, ctrl );
    }


    std::string NodeInfoBase::toString(
        NodeInfoBase::controller_base_t const* SIXTRL_RESTRICT ctrl ) const
    {
        std::ostringstream a2str;
        if( this->doPrintToOutputStream( a2str, ctrl ) !=
                st::ARCH_STATUS_SUCCESS ) a2tr.str( "" );
        return a2str.str();
    }


    NodeInfoBase::status_t NodeInfoBase::toString(
        NodeInfoBase::size_type const out_str_capacity,
        char* SIXTRL_RESTRICT out_str,
        NodeInfoBase::controller_base_t const* ctrl ) const
    {
        using size_t = NodeInfoBase::size_type;

        NodeInfoBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( out_str != nullptr ) && ( out_str_capacity > size_t{ 0 } ) )
        {
            std::string const str_repr = this->toString( ctrl );

            if( ( !str_repr.empty() ) ( str_repr.size() < out_str_capacity ) )
            {
                std::strncpy( out_str, str_repr.c_str(),
                              out_str_capacity - size_t{ 1 } );

                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    std::ostream& operator<<( std::ostream& SIXTRL_RESTRICT_REF output,
        NodeInfoBase const& SIXTRL_RESTRICT_REF node_info )
    {
        node_info.doPrintToOutputStream( output, nullptr );
        return output;
    }

    /* --------------------------------------------------------------------- */

    NodeInfoBase::status_t NodeInfoBase::doPrintToOutputStream(
        std::ostream& SIXTRL_RESTRICT_REF output,
        NodeInfoBase::controller_base_t const* ptr_ctrl ) const
    {
        using size_t       = NodeInfoBase::size_type;
        using status_t     = NodeInfoBase::status_t;
        using node_ctrl_t  = st::NodeContollerBase;
        using node_store_t = st::NodeStore;
        using nindex_t     = st::NodeStore::nindex_t;
        using node_id_t    = st::NodeStore::node_id_t;

        NodeInfoBase::status_t status = st::ARCH_STATUS_SUCCESS;

        char temp_node_id_str[ 32 ] =
        {
            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
        };

        status_t status = this->nodeId().toString(
            32, temp_node_id_str, st::NODE_ID_STR_NOARCH );

        node_store_t const& node_store = st::NodeStore_get();
        node_index_t const nindex = node_store.findNodeIndex( this->nodeId() );

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( nindex == node_id_t::UNDEFINED_INDEX ) )
        {
            status = st::ARCH_STATUS_GENERAL_FAILURE;
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            size_t num_selecting_ctrls = size_t{ 0 };
            bool is_attached_to_ctrl = false;

            node_ctrl_t ptr_node_ctrl = st::asNodeController( ptr_ctrl );

            output << "Node            : " << temp_node_id_str;

            if( ptr_node_ctrl != nullptr )
            {
                is_attached_to_ctrl = this->isAttachedTo( *ptr_node_ctrl );
            }

            if( ( ptr_ctrl != nullptr ) && ( is_attached_to_ctrl ) )
            {
                if( ptr_ctrl->hasName() )
                {
                    output << " attached to " << ptr_ctrl->name();
                }

                if( ptr_node_ctrl->isDefaultNode( nindex ) )
                {
                    output << " [ DEFAULT ]";
                }

                if( ptr_node_ctrl->isSelectedBy( *ptr_ctrl ) )
                {
                    num_selecting_ctrls =
                        ptr_node_ctrl->numSelectingControllers();

                    output << " [ SELECTED ]";
                }
            }

            output << "\r\nArchitecture    : " << this->archId();

            if( this->hasArchStr() )
            {
               output << "( " << this->archStr() << " )";
            }

            output << "\r\nNum Controllers : "
                   << node_store.numControllersAttachedToNode( nindex )
                   << "\r\nSelected by     : "
                   << num_selecting_ctrls << " / "
                   << this->maxSelectionCount() << " Controllers\r\n";

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


    void NodeInfoBase::doSetMaxSelectionCount(
        NodeInfoBase::size_type const max_selection_count ) SIXTRL_NOEXCEPT
    {
        this->m_max_selection_cnt = max_selection_count;
    }
}

/* end: sixtracklib/common/control/node_info.cpp */
