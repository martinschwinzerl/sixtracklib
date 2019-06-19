#include "sixtracklib/common/control/node_id.h"

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <ostream>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/control_base.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    NodeId::NodeId(
        NodeId::platform_id_t const platform_id,
        NodeId::device_id_t const device_id,
        NodeId::index_t const node_index ) SIXTRL_NOEXCEPT :
        m_ptr_ctrl_to_node_index_map(),
        m_available_on_controllers(),
        m_platform_device_pair(),
        m_ptr_selected_by_controller( nullptr )
    {
        this->setPlatformId( platform_id );
        this->setDeviceId( device_id );
    }

    NodeId::NodeId( std::string const& SIXTRL_RESTRICT_REF id_str ) :
        m_ptr_ctrl_to_node_index_map(),
        m_available_on_controllers(),
        m_platform_device_pair(),
        m_ptr_selected_by_controller( nullptr )
    {
        if( st::ARCH_STATUS_SUCCESS == this->fromString( id_str ) )
        {
            this->setPlatformId( NodeId::ILLEGAL_PLATFORM_ID );
            this->setDeviceId( NodeId::ILLEGAL_DEVICE_ID );
        }
    }

    NodeId::NodeId( const char *const SIXTRL_RESTRICT id_str ) :
        m_ptr_ctrl_to_node_index_map(),
        m_available_on_controllers(),
        m_platform_device_pair(),
        m_ptr_selected_by_controller( nullptr )
    {
        if( st::ARCH_STATUS_SUCCESS == this->fromString( id_str ) )
        {
            this->setPlatformId( NodeId::ILLEGAL_PLATFORM_ID );
            this->setDeviceId( NodeId::ILLEGAL_DEVICE_ID );
        }
    }

    bool NodeId::valid() const SIXTRL_NOEXCEPT
    {
        return ( ( this->platformId() != NodeId::ILLEGAL_PLATFORM_ID ) &&
                 ( this->deviceId() != NodeId::ILLEGAL_DEVICE_ID ) );
    }

    NodeId::platform_id_t NodeId::platformId() const SIXTRL_NOEXCEPT
    {
        return this->m_platform_device_pair.platform_id;
    }

    NodeId::device_id_t NodeId::deviceId() const SIXTRL_NOEXCEPT
    {
        return this->m_platform_device_pair.device_id;
    }

    NodeId::status_t NodeId::setPlatformId(
        NodeId::platform_id_t const platform_id ) SIXTRL_NOEXCEPT
    {
        this->m_platform_device_pair.platform_id = id;
    }

    NodeId::status_t NodeId::setDeviceId(
        NodeId::device_id_t const device_id ) SIXTRL_NOEXCEPT
    {
        this->m_platform_device_pair.device_id = id;
    }

    NodeId::platform_device_pair_t const&
    NodeId::platformDeviceIdPair() const SIXTRL_NOEXCEPT
    {
        return this->m_platform_device_pair;
    }

    NodeId::platform_device_pair_t&
    NodeId::platformDeviceIdPair SIXTRL_NOEXCEPT
    {
        return this->m_platform_device_pair;
    }

    NodeId::platform_device_pair_t const*
    NodeId::ptrPlatformDeviceIdPair() const SIXTRL_NOEXCEPT
    {
        return &this->m_platform_device_pair;
    }

    NodeId::platform_device_pair_t*
    NodeId::ptrPlatformDeviceIdPair() SIXTRL_NOEXCEPT
    {
        return &this->m_platform_device_pair;
    }

    /* --------------------------------------------------------------------- */

    bool NodeId::hasControllers() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_ptr_ctrl_to_node_index_map.empty() ==
                       this->m_available_on_controllers.empty() );

        return !this->m_available_on_controllers.empty();
    }

    NodeId::size_type NodeId::numControllers() const SIXTRL_NOEXCEPT
    {
        using size_t = NodeId::size_type;

        size_t const num_of_ctrls = this->m_available_on_controllers.size();

        SIXTRL_ASSERT(
            ( ( num_of_ctrls == size_t{ 0 } ) &&
             ( this->m_ptr_ctrl_to_node_index_map.empty() ) &&
             ( this->m_available_on_controllers.empty() ) ) ||
           ( ( !this->m_ptr_ctrl_to_node_index_map.empty() ) &&
             ( !this->m_available_on_controllers.empty() ) &&
             (  this->m_ptr_ctrl_to_node_index_map.size() == num_of_ctrls ) ) );

        return num_of_ctrls;
    }

    bool NodeId::isAttachedToController( NodeId::controller_base_t const&
        SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT
    {
        NodeId::controller_base_t const* ptr_ctrl = &ctrl;

        bool const is_attached_to_controller = (
            ( cltr != nullptr ) &&
            ( !this->m_ptr_ctrl_to_node_index_map.empty() ) &&
            (  this->m_ptr_ctrl_to_node_index_map.find( ptr_ctrl ) !=
               this->m_ptr_ctrl_to_node_index_map.end() ) );

        SIXTRL_ASSERT( ( !is_attached_to_controller ) ||
            ( ( !this->m_available_on_controllers.empty() ) &&
              (  std::find( this->m_available_on_controllers.begin(),
                    this->m_available_on_controllers.end(),
                    [&ptr_ctrl]( NodeId::controller_base_t const* ptr_cmp_ctrl )
                    {
                        return ( ptr_cmp_ctrl == ptr_ctrl );
                    } ) ) ) );

        return is_attached_to_controller;
    }

    bool NodeId::hasNodeIndex( NodeId::controller_base_t const&
        SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT
    {
        return ( this->nodeIndex( ctrl ) != NodeId::UNDEFINED_INDEX );
    }

    NodeId::node_index_t NodeId::nodeIndex( NodeId::controller_base_t const&
        SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT
    {
        NodeId::node_index_t node_index = NodeId::UNDEFINED_INDEX;

        if( !this->m_ptr_ctrl_to_node_index_map.empty() )
        {
            auto it = this->m_ptr_ctrl_to_node_index_map.find( &ctrl );

            if( it != this->m_ptr_ctrl_to_node_index_map.end() )
            {
                node_index = it->second;
            }
        }

        return node_index;
    }

    NodeId::status_t NodeId::setNodeIndex(
        NodeId::controller_base_t const& SIXTRL_RESTRICT_REF ctrl,
        NodeId::node_index_t const node_index ) SIXTRL_RESTRICT
    {
        NodeId::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->m_ptr_ctrl_to_node_index_map.empty() )
        {
            auto it = this->m_ptr_ctrl_to_node_index_map.find( &ctrl );

            if( it != this->m_ptr_ctrl_to_node_index_map.end() )
            {
                SIXTRL_ASSERT( std::find(
                    this->m_available_on_controllers.begin(),
                    this->m_available_on_controllers.end(),
                    [&ctrl]( NodeId::controller_base_t const* ptr_cmp_ctrl )
                    { return ( ptr_cmp_ctrl == &ctrl ); } ) !=
                        this->m_available_on_controllers.end() );

                it->second = node_index;
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    bool NodeId::isSelected() const SIXTRL_NOEXCEPT
    {
        return ( this->m_ptr_selected_by_controller != nullptr );
    }

    bool NodeId::isSelectedByController( NodeId::controller_base_t const&
        SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->isAttachedToController( &ctrl ) ) &&
                 ( this->m_ptr_selected_by_controller == &ctrl ) );
    }

    bool NodeId::isDefault() const SIXTRL_NOEXCEPT
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

    bool NodeId::isDefaultForController( NodeId::controller_base_t const&
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

    NodeId::controller_base_t const*
    NodeId::ptrSelectingController() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_selected_by_controller == nullptr ) ||
            ( this->isAttachedToController(
                *this->m_ptr_selected_by_controller ) ) );

        return this->m_ptr_selected_by_controller;
    }

    NodeId::status_t
    NodeId::setPtrSelectedController( NodeId::controller_base_t const*
        SIXTRL_RESTRICT ctrl ) SIXTRL_NOEXCEPT
    {
        NodeId::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

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

    NodeId::status_t NodeId::setSelectedController( NodeId::controller_base_t
        const& SIXTRL_RESTRICT_REF ctrl ) SIXTRL_NOEXCEPT
    {
        return this->setPtrSelectedController( &ctrl );
    }

    NodeId::status_t NodeId::resetSelectingController() SIXTRL_NOEXCEPT
    {
        return this->setPtrSelectedController( nullptr );
    }

    NodeId::status_t NodeId::attachToController(
        NodeId::controller_base_t const& SIXTRL_RESTRICT_REF ctrl,
        NodeId::node_index_t const node_index )
    {
        NodeId::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->m_ptr_ctrl_to_node_index_map.empty() )
        {
            auto it = this->m_ptr_ctrl_to_node_index_map.find( &ctrl );

            if( it == this->m_ptr_ctrl_to_node_index_map.end() )
            {
                auto ret = this->m_ptr_ctrl_to_node_index_map.emplace(
                    std::make_pair( &ctrl, node_index ) );

                if( ret.second )
                {
                    SIXTRL_ASSERT( std::find(
                        this->m_available_on_controllers.begin(),
                        this->m_available_on_controllers.end(),
                        [&ctrl]( NodeId::controller_base_t const* ptr_cmp_ctrl )
                        {
                            return ptr_cmp_ctrl == &ctrl;
                        } ) == this->m_available_on_controllers.end() );

                    this->m_available_on_controllers.push_back( &ctrl );

                    std::sort( this->m_available_on_controllers.begin(),
                               this->m_available_on_controllers.end() );

                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
            else if( it->second != node_index )
            {
                SIXTRL_ASSERT( std::find(
                    this->m_available_on_controllers.begin(),
                    this->m_available_on_controllers.end(),
                    [&ctrl]( NodeId::controller_base_t const* ptr_cmp_ctrl )
                    {
                        return ptr_cmp_ctrl == &ctrl;
                    } ) != this->m_available_on_controllers.end() );

                it->second = node_index;
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    NodeId::status_t NodeId::detachFromController( NodeId::controller_base_t
        const& SIXTRL_RESTRICT_REF ctrl ) SIXTRL_NOEXCEPT
    {
        NodeId::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

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

            auto vec_it = std::find( this->m_available_on_controllers.begin(),
                this->m_available_on_controllers.end(),
                [&ctrl]( NodeId::controller_base_t const* ptr_cmp_ctrl )
                {
                    return ( ptr_cmp_ctrl == &ctrl );
                } );

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

    NodeId::controller_base_t const*
    NodeId::ptrController( NodeId::size_type const
        num_of_controller_in_list ) const SIXTRL_NOEXCEPT
    {
        NodeId::controller_base_t const* ptr_ctrl = nullptr;

        if( ( !this->m_available_on_controllers.empty() ) &&
            ( num_of_controller_in_list < this->numControllers() ) )
        {
            ptr_ctrl = this->m_available_on_controllers[
                num_of_controller_in_list ];
        }

        return ptr_ctrl;
    }

    /* ----------------------------------------------------------------- */

    NodeId::status_t NodeId::fromNodeIdStr(
        std::string const& SIXTRL_RESTRICT_REF node_id_str ) SIXTRL_NOEXCEPT
    {
        return this->fromNodeIdStr( node_id_str.c_str() );
    }

    NodeId::status_t NodeId::fromNodeIdStr(
        const char *const SIXTRL_RESTRICT node_id_str ) SIXTRL_NOEXCEPT
    {
        using platform_id_t = NodeId::platform_id_t;
        using device_id_t   = NodeId::device_id_t;
        using size_t = NodeId::size_type;

        NodeId::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( node_id_str != nullptr ) &&
            ( std::strlen( node_id_str ) > size_t{ 0 } ) )
        {
            long long int temp_platform_id = NodeId::ILLEGAL_PLATFORM_ID;
            long long int temp_device_id   = NodeId::ILLEGAL_DEVICE_ID;

            int const ret = std::sscanf( id_str, "%lld.%lld",
                &temp_platform_id, &temp_device_id );

            if( ret == int{ 2 }  )
            {
                platform_id_t const platform_id =
                    static_cast< platform_id_t >( temp_platform_id );

                device_id_t const device_id =
                    static_cast< device_id_t >( temp_device_id );

                if( ( platform_id != NodeId::ILLEGAL_PLATFORM_ID ) &&
                    ( device_id   != NodeId::ILLEGAL_DEVICE_ID ) )
                {
                    this->setPlatformId( platform_id );
                    this->setDeviceId( device_id );

                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    std::string NodeId::toNodeIdStr() const
    {
        std::ostringstream a2str.str( "" );
        NodeId::status_t const status = this->doNodeIdStr( a2str );

        return ( status == st::ARCH_STATUS_SUCCESS )
            ? a2str.str() : std::string{};
    }

    NodeId::status_t NodeId::toNodeIdStr(
        std::ostream& SIXTRL_RESTRICT_REF a2str ) const
    {
        NodeId::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->valid() )
        {
            a2str << this->platformId() << "." << this->deviceId();
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    NodeId::status_t NodeId::toNodeIdStr( char* SIXTRL_RESTRICT node_id_str,
        NodeId::size_type const node_id_str_capacity ) const
    {
        NodeId::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        using size_t = NodeId::size_type;

        if( ( node_id_str != nullptr ) &&
            ( node_id_str_capacity > size_t{ 0 } ) )
        {
            std::memset( node_id_str, static_cast< int >( '\0' ),
                         node_id_str_capacity );

            if( this->valid() )
            {
                std::string const temp_str = this->toNodeIdStr();

                if( ( !temp_str.empty() ) &&
                    ( temp_str.size() < node_id_str_capacity ) )
                {
                    std::copy( temp_str.begin(), temp_str.end(), node_id_str );
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    /* ----------------------------------------------------------------- */

    void NodeId::print( std::ostream& SIXTRL_RESTRICT_REF os )
    {
        os << this->toNodeIdStr();

        if( this->isSelected() )
        {
            os << " [SELECTED]";
        }

        os << "\r\nnum of controllers : " << this->numControllers() << "\r\n";
    }

    void NodeId::print( ::FILE* SIXTRL_RESTRICT fp )
    {
        if( fp != nullptr )
        {
            std::string const temp_str( this->toString() );
            std::fprintf( fp, "%s", temp_str.c_str() );
        }
    }

    void NodeId::printOut()
    {
        this->print( std::cout );
    }

    NodeId::size_type NodeId::requiredStringCapacity() const
    {
        std::string const temp_str( this->toString() );
        return temp_str.size() + NodeId::size_type{ 1 };
    }

    std::string NodeId::toString() const
    {
        std::ostringstream a2str;
        this->print( a2str );
        return a2str.str();
    }

    NodeId::status_t NodeId::toString( NodeId::size_type out_str_capacity,
            char* SIXTRL_RESTRICT output_str ) const
    {
        NodeId::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( out_str_capacity > NodeId::size_type{ 0 } ) &&
            ( output_str != nullptr ) )
        {
            std::memset( output_str, static_cast< int >( '\0' ),
                         out_str_capacity );

            std::ostringstream a2str;
            this->print( a2str );

            std::string const temp_str( a2str.str() );

            if( ( !temp_str.empty() ) &&
                ( temp_str.size() < out_str_capacity ) )
            {
                std::copy( temp_str.begin(), temp_str.end(),
                           output_str );

                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool NodeId::operator<(
        NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->platformId() < rhs.platformId() ) ||
                 ( ( this->platformId() == rhs.platformId() ) &&
                   ( this->deviceId() < rhs.deviceId() ) ) );
    }

    void NodeId::clear() SIXTRL_NOEXCEPT
    {
        this->m_platform_device_pair.platform_id = NodeId::ILLEGAL_PLATFORM_ID;
        this->m_platform_device_pair.device_id   = NodeId::ILLEGAL_DEVICE_ID;

        this->m_ptr_selected_by_controller = nullptr;
        this->m_available_on_controllers.clear();
        this->m_ptr_ctrl_to_node_index_map.clear();
    }

    std::ostream& operator<<( std::ostream& SIXTRL_RESTRICT_REF output,
        st::NodeId const& SIXTRL_RESTRICT_REF node_id )
    {
        node_id.print( output );
        return output;
    }

    int compareNodeIds( st::NodeId const& SIXTRL_RESTRICT_REF lhs,
                        st::NodeId const& SIXTRL_RESTRICT_REF rhs )
    {
        return ( lhs < rhs ) ? -1 : ( rhs < lhs ) ? +1 : 0;
    }
}

/* end: sixtracklib/common/control/node_id.cpp */
