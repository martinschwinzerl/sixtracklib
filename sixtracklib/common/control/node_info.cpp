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
        NodeInfoBase::platform_id_t const platform_id,
        NodeInfoBase::device_id_t const device_id,
        const char *const SIXTRL_RESTRICT platform_name,
        const char *const SIXTRL_RESTRICT device_name,
        const char *const SIXTRL_RESTRICT description  ) :
        st::ArchInfo( arch_id, arch_str ),
        m_ptr_ctrl_to_node_index_map(), m_platform_name(), m_device_name(),
        m_description(), m_unique_id(), m_node_id( platform_id, device_id ),
        m_ptr_selected_by_controller( nullptr )
    {
        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
    }

    NodeInfoBase::NodeInfoBase(
        NodeInfoBase::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        NodeInfoBase::platform_id_t const platform_id,
        NodeInfoBase::device_id_t const device_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name,
        std::string const& SIXTRL_RESTRICT_REF device_name,
        std::string const& SIXTRL_RESTRICT_REF description ) :
        st::ArchInfo( arch_id, arch_str ),
        m_ptr_ctrl_to_node_index_map(), m_platform_name(), m_device_name(),
        m_description(), m_unique_id(), m_node_id( platform_id, device_id ),
        m_ptr_selected_by_controller( nullptr )
    {
        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
    }

    /* --------------------------------------------------------------------- */

    bool NodeInfoBase::isAttachedToController( NodeInfoBase::controller_base_t
        const& SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT
    {
        using ptr_ctrl_t = NodeInfoBase::controller_base_t const*;

        bool const is_attached_to_controller = (
            ( cltr != nullptr ) &&
            ( !this->m_ptr_ctrl_to_node_index_map.empty() ) &&
            (  this->m_ptr_ctrl_to_node_index_map.find( ptr_ctrl ) !=
               this->m_ptr_ctrl_to_node_index_map.end() ) );

        SIXTRL_ASSERT( ( !is_attached_to_controller ) ||
            ( ( !this->m_available_on_controllers.empty() ) &&
              (  std::find( this->m_available_on_controllers.begin(),
                    this->m_available_on_controllers.end(),
                    [&ctrl]( ptr_ctrl_t ptr_cmp_ctrl ) {
                        return ( ptr_cmp_ctrl == &ctrl ); } ) ) ) );

        return is_attached_to_controller;
    }

    bool NodeInfoBase::hasNodeIndex( NodeInfoBase::controller_base_t const&
        SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT
    {
        return ( this->getNodeIndex( ctrl ) != NodeInfoBase::UNDEFINED_INDEX );
    }

    NodeInfoBase::node_index_t NodeInfoBase::nodeIndex(
        NodeInfoBase::controller_base_t const& SIXTRL_RESTRICT_REF
            ctrl ) const SIXTRL_NOEXCEPT
    {
        NodeInfoBase::node_index_t node_index = NodeInfoBase::UNDEFINED_INDEX;

        if( this->hasControllers() )
        {
            NodeInfoBase::controller_base_t const* ptr_ctrl = &ctrl;

            auto it = this->m_ptr_ctrl_to_node_index_map.find( ptr_ctrl );

            if( it != this->m_ptr_ctrl_to_node_index_map.end() )
            {
                node_index = it->second;
            }
        }

        SIXTRL_ASSERT( ( node_index == NodeInfoBase::UNDEFINED_INDEX ) ||
            ( ( this->isAttachedToController( ctrl ) ) &&
              ( st::asNodeController( ptr_ctrl ) != nullptr ) &&
              ( st::asNodeController( ptr_ctrl )->isNodeAvailable(
                  node_index ) ) ) );

        return node_index;
    }

    NodeInfoBase::status_t NodeInfoBase::setNodeIndex(
        NodeInfoBase::controller_base_t const& SIXTRL_RESTRICT_REF ctrl,
        NodeInfoBase::node_index_t const node_index ) SIXTRL_RESTRICT
    {
        NodeInfoBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        st::NodeControllerBase const* ptr_ctrl = st::asNodeController(
            &ctrl );

        if( ( ptr_ctrl != nullptr ) &&
            ( this->isAttachedToController( &ctrl ) ) )
        {
            it = this->m_ptr_ctrl_to_node_index_map.find( &ctrl );

            if( it != this->m_ptr_ctrl_to_node_index_map.end() )
            {
                it->second = node_index;
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    bool NodeInfoBase::isSelectedByController( controller_base_t const&
        SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->isAttachedToController( &ctrl ) ) &&
                 ( this->m_ptr_selected_by_controller == &ctrl ) );
    }

    bool NodeInfoBase::isDefault() const SIXTRL_NOEXCEPT
    {
        bool is_default = false;

        if( this->numControllers() > 0 )
        {
            for( auto ptr_ctrl : this->m_available_on_controllers )
            {
                if( ptr_ctrl == nullptr ) break;

                if( this->isDefaultForController( *ptr_ctrl ) )
                {
                    is_default = true;
                    break;
                }
            }
        }

        return is_default;
    }

    bool NodeInfoBase::isDefaultForController( controller_base_t const&
        SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT
    {
        using base_ctrl_t = st::NodeId::controller_base_t:
        using node_ctrl_t = st::NodeControllerBase;

        bool is_default = false;

        base_ctrl_t const* ptr_ctrl = &ctrl;
        node_ctrl_t const* ptr_node_ctrl = st::asNodeController( ptr_ctrl );

        if( ( ptr_node_ctrl != nullptr ) &&
            ( ptr_node_ctrl->hasDefaultNode() ) &&
            ( ptr_node_ctrl->ptrDefaultNode() != nullptr ) &&
            ( ptr_node_ctrl->ptrDefaultNode()->platformId() ==
                this->platformId() ) &&
            ( ptr_node_ctrl->ptrDefaultNode()->deviceId() ==
                this->deviceId() ) &&
            ( this->isAttachedToController( ptr_base_ctrl ) ) )
        {
            is_default = true;
        }

        return is_default;
    }

    NodeInfoBase::status_t NodeInfoBase::setPtrSelectedController(
        NodeInfoBase::controller_base_t const*
            SIXTRL_RESTRICT ptr_ctrl ) SIXTRL_NOEXCEPT
    {
        NodeInfoBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ctrl != nullptr )
        {
            if( this->isAttachedToController( *ctrl ) )
            {
                if( ctrl != this->m_ptr_selected_by_controller )
                {
                    this->m_ptr_selected_by_controller = ctrl;
                }

                status = st::ARCH_STATUS_SUCCESS;
            }
        }
        else if( this->m_ptr_selected_by_controller != nullptr )
        {
            this->m_ptr_selected_by_controller = nullptr;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    NodeInfoBase::status_t NodeInfoBase::attachToController(
        NodeInfoBase::controller_base_t const& SIXTRL_RESTRICT_REF ctrl,
        NodeInfoBase::node_index_t const node_index )
    {
        using ptr_ctrl_t = NodeInfoBase::controller_base_t const*;

        NodeInfoBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->m_ptr_ctrl_to_node_index_map.empty() )
        {
            auto it = this->m_ptr_ctrl_to_node_index_map.find( &ctrl );
            if( it == this->m_ptr_ctrl_to_node_index_map.end() )
            {
                auto ret = this->m_ptr_ctrl_to_node_index_map.emplace(
                    std::make_pair( &ctrl, node_index ) );

                if( ret.second )
                {
                    SIXTRL_ASSERT( this->controllerNumberInList( ctrl ) >=
                                   this->numControllers() );

                    this->m_available_on_controllers.push_back( &ctrl );
                    std::sort( this->m_available_on_controllers.begin(),
                               this->m_available_on_controllers.end() );

                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
            else if( it->second != node_index )
            {
                SIXTRL_ASSERT( this->controllerNumberInList( ctrl ) <
                    this->numControllers() );

                it->second = node_index;
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    NodeInfoBase::status_t NodeInfoBase::detachFromController(
        NodeInfoBase::controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) SIXTRL_NOEXCEPT
    {
        NodeInfoBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->isAttachedToController( &ctrl ) )
        {
            SIXTRL_ASSERT( !this->m_ptr_ctrl_to_node_index_map.empty() );
            SIXTRL_ASSERT( !this->m_available_on_controllers.empty() );

            SIXTRL_ASSERT(  this->m_ptr_ctrl_to_node_index_map.size() ==
                            this->m_available_on_controllers.size() );

            if( this->m_ptr_selected_by_controller == &ctrl )
            {
                this->resetSelectingController();
            }

            auto map_it = this->m_ptr_ctrl_to_node_index_map.find( &ctrl );
            SIXTRL_ASSERT( map_it != this->m_ptr_ctrl_to_node_index_map.end() );

            this->m_ptr_ctrl_to_node_index_map.erase( map_it );

            auto vec_it = this->m_available_on_controllers.begin();
            NodeInfoBase::size_type const nn =
                this->controllerNumberInList( ctrl );

            if( nn < this->numControllers() )
            {
                std::advance( vec_it, nn );
            }
            else
            {
                vec_it = this->m_available_on_controllers.end();
            }

            SIXTRL_ASSERT( vec_it != this->m_available_on_controllers.end() );

            this->m_available_on_controllers.erase( vec_it );

            SIXTRL_ASSERT( this->m_available_on_controllers.size() ==
                           this->m_ptr_ctrl_to_node_index_map.size() );

            if( !this->m_available_on_controllers.empty() )
            {
                std::sort( this->m_available_on_controllers.begin(),
                           this->m_available_on_controllers.end() );
            }

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;

    }

    NodeInfoBase::size_type NodeInfoBase::controllerNumberInList(
        NodeInfoBase::controller_base_t const& SIXTRL_RESTRICT_REF ctrl
        ) const SIXTRL_NOEXCEPT
    {
        using size_t = NodeInfoBase::size_type;

        NodeInfoBase::size_type num_entry_in_list =
            std::numeric_limits< size_t >::max();

        SIXTRL_ASSERT( num_entry_in_list > this->numControllers() );

        if( this->isAttachedToController( &ctrl ) )
        {
            num_entry_in_list = size_t{ 0 };

            for( auto ptr_ctrl : this->m_available_on_controllers )
            {
                if( ptr_ctrl == &ctrl )
                {
                    break;
                }

                ++num_entry_in_list;
            }

            SIXTRL_ASSERT( ( num_entry_in_list == this->numControllers() ) ||
                ( this->m_available_on_controllers[ num_entry_in_list ] ==
                  &ctrl ) );

            if( num_entry_in_list >= this->numControllers() )
            {
                num_entry_in_list = this->std::numeric_limits< size_t >::max();
            }
        }

        return num_entry_in_list;
    }

    NodeInfoBase::controller_base_t const*
    NodeInfoBase::ptrMostRelevantController() const SIXTRL_NOEXCEPT
    {
        NodeInfoBase::controller_base_t const* ptr_ctrl = nullptr;

        if( ( this->hasNodeId() ) && ( this->numControllers() > size_t{ 0 } ) )
        {
            if( this->ptrNodeId()->isSelected() )
            {
                ptr_ctrl = this->nodeIdPtr()->ptrSelectingController();
            }
            else
            {
                size_t const nn = this->numControllers();

                for( size_t ii = size_t{ 0 } ; ii < nn ; ++ii )
                {
                    NodeInfoBase::controller_base_t const* it =
                        this->ptrNodeId()->ptrController( ii );

                    if( ( it != nullptr ) && ( this->ptrNodeId(
                            )->isDefaultForController( *it ) ) )
                    {
                        ptr_ctrl = it;
                        break;
                    }
                }
            }

            if( ptr_ctrl == nullptr )
            {
                ptr_ctrl = this->ptrNodeId()->ptrController( size_t{ 0 } );
            }
        }

        return ptr_ctrl;
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

    NodeInfoBase::size_type NodeInfoBase::requiredOutStringLength(
        NodeInfoBase::controller_base_t const* SIXTRL_RESTRICT ptr_ctrl ) const
    {
        return this->toString( ptr_ctrl ).size() +
            NodeInfoBase::size_type{ 1 };
    }


    void NodeInfoBase::print( ::FILE* SIXTRL_RESTRICT output,
        NodeInfoBase::controller_base_t const*
            SIXTRL_RESTRICT ptr_controller ) const
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


    void NodeInfoBase::printOut( NodeInfoBase::controller_base_t const*
        SIXTRL_RESTRICT ptr_controller ) const
    {
        this->print( stdout, ptr_controller );
    }


    std::string NodeInfoBase::toString( NodeInfoBase::controller_base_t const*
        SIXTRL_RESTRICT ptr_controller ) const
    {
        std::ostringstream a2str;

        st::arch_status_t status = this->doPrintToOutputStream(
            a2str, ptr_controller );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            return a2str.str();
        }

        return std::string{};
    }


    NodeInfoBase::status_t NodeInfoBase::toString(
        NodeInfoBase::size_type const out_str_capacity,
        char* SIXTRL_RESTRICT out_str, NodeInfoBase::controller_base_t const*
            SIXTRL_RESTRICT ptr_controller ) const
    {
        using size_t = NodeInfoBase::size_type;

        NodeInfoBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( out_str != nullptr ) && ( out_str_capacity > size_t{ 0 } ) )
        {
            std::string const str_repr = this->toString( ptr_controller );

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
        node_info.doPrintToOutputStream(
            output, this->ptrMostRelevantController() );

        return output;
    }

    /* --------------------------------------------------------------------- */

    NodeInfoBase::status_t NodeInfoBase::doPrintToOutputStream(
        std::ostream& SIXTRL_RESTRICT_REF output,
        NodeInfoBase::controller_base_t const* ptr_ctrl ) const
    {
        using size_t = NodeInfoBase::size_type;

        NodeInfoBase::status_t status = st::ARCH_STATUS_SUCCESS;

        if( ptr_ctrl != nullptr )
        {
            if( this->isAttachedToController( ptr_ctrl ) )
            {
                output << "Node            : "
                       << this->ptrNodeId()->toString();

                if( ( ptr_ctrl != nullptr ) &&
                    ( this->ptrNodeId()->isSelectedByController( ptr_ctrl ) ) )
                {
                    output << " [SELECTED]";
                }

                if( ( ptr_ctrl != nullptr ) &&
                    ( this->ptrNodeId()->isDefaultForController( ptr_ctrl ) ) )
                {
                    output << " [DEFAULT]";
                }

                output << "\r\n";

                if( this->ptrNodeId()->numControllers() > size_t{ 0 } )
                {
                    output << "num controllers : "
                           << this->ptrNodeId()->numControllers() << "\r\n";
                }
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            output << "\r\nArchitecture    : id = "
                   << this->archId();

            if( this->hasArchStr() )
            {
                output << " " << this->archStr();
            }

            output << "\r\n";

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
}

/* end: sixtracklib/common/control/node_info.cpp */
