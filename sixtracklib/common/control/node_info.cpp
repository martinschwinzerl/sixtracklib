#include "sixtracklib/common/control/node_info.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>
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
        st::ArchInfo( arch_id, arch_str ), m_platform_name(),
        m_device_name(), m_description(), m_ptr_node_id( nullptr ),
        m_ptr_stored_node_id( new st::NodeId( platform_id, device_id ) )
    {
        if( this->m_ptr_stored_node_id.get() != nullptr )
        {
            this->doSetPtrNodeId( this->m_ptr_stored_node_id.get() );
        }

        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
    }

    NodeInfoBase::NodeInfoBase(
        NodeInfoBase::arch_info_t const* SIXTRL_RESTRICT ptr_arch_info,
        NodeInfoBase::node_id_t* SIXTRL_RESTRICT ptr_node_id,
        const char *const SIXTRL_RESTRICT platform_name,
        const char *const SIXTRL_RESTRICT device_name,
        const char *const SIXTRL_RESTRICT description ) :
        st::ArchInfo( ), m_platform_name(), m_device_name(), m_description(),
        m_ptr_node_id( ptr_node_id ), m_ptr_stored_node_id( nullptr )
    {
        if( ptr_arch_info != nullptr )
        {
            ArchInfo::operator=( *ptr_arch_info );
        }

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
        std::string const& SIXTRL_RESTRICT_REF description ):
        st::ArchInfo( arch_id, arch_str ), m_platform_name(),
        m_device_name(), m_description(), m_ptr_node_id( nullptr ),
        m_ptr_stored_node_id( new st::NodeId( platform_id, device_id ) )
    {
        if( this->m_ptr_stored_node_id.get() != nullptr )
        {
            this->doSetPtrNodeId( this->m_ptr_stored_node_id.get() );
        }

        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
    }


    NodeInfoBase::NodeInfoBase(
        NodeInfoBase::arch_info_t const& SIXTRL_RESTRICT_REF arch_info,
        NodeInfoBase::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name,
        std::string const& SIXTRL_RESTRICT_REF device_name,
        std::string const& SIXTRL_RESTRICT_REF description ) :
        st::ArchInfo( arch_info ),
        m_platform_name(), m_device_name(), m_description(),
        m_ptr_node_id( ptr_node_id ), m_ptr_stored_node_id( nullptr )
    {
        this->setPlatformName( platform_name );
        this->setDeviceName( device_name );
        this->setDescription( description );
    }

    /* --------------------------------------------------------------------- */

    bool NodeInfoBase::ownsNodeId() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_ptr_stored_node_id.get() != nullptr ) &&
                 ( this->m_ptr_stored_node_id.get() == this->m_ptr_node_id ) );
    }

    bool NodeInfoBase::hasNodeId()  const SIXTRL_NOEXCEPT
    {
        return ( this->m_ptr_node_id != nullptr );
    }

    NodeInfoBase::node_id_t const& NodeInfoBase::nodeId() const
    {
        if( this->hasNodeId() )
        {
            throw std::runtime_error(
                "NodeInfo* instance has no NodeId member" );
        }

        return this->m_node_id;
    }

    NodeInfoBase::node_id_t& NodeInfoBase::nodeId()
    {
        return const_cast< NodeInfoBase::node_id_t& >( static_cast<
            NodeInfoBase const& >( *this ).nodeId() );
    }

    NodeInfoBase::node_id_t const*
    NodeInfoBase::ptrNodeId() const SIXTRL_NOEXCEPT
    {
        return this->m_ptr_node_id;
    }

    NodeInfoBase::node_id_t* NodeInfoBase::ptrNodeId() SIXTRL_NOEXCEPT
    {
        return this->m_ptr_node_id;
    }

    NodeInfoBase::platform_id_t NodeInfoBase::platformId() const SIXTRL_NOEXCEPT
    {
        return ( this->m_ptr_node_id != nullptr )
            ? this->m_ptr_node_id->platformId()
            : st::NodeInfoBase::ILLEGAL_PLATFORM_ID;
    }

    void NodeInfoBase::setPlatformId(
        NodeInfoBase::platform_id_t const platform_id ) SIXTRL_NOEXCEPT
    {
        NodeInfoBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasNodeId() )
        {
            status = this->m_ptr_node_id->setPlatformId( platform_id );
        }

        return status;
    }

    NodeInfoBase::device_id_t NodeInfoBase::deviceId() const SIXTRL_NOEXCEPT
    {
        return ( this->m_ptr_node_id != nullptr )
            ? this->m_ptr_node_id->deviceId()
            : st::NodeInfoBase::ILLEGAL_DEVICE_ID;
    }

    NodeInfoBase::status_t NodeInfoBase::setDeviceId(
        NodeInfoBase::device_id_t const device_id ) SIXTRL_NOEXCEPT
    {
        NodeInfoBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasNodeId() )
        {
            status = this->m_ptr_node_id->setDeviceId( device_id );
        }

        return status;
    }

    NodeInfoBase::platform_device_pair_t const&
    NodeInfoBase::platformDeviceIdPair() const
    {
        return this->nodeId().platformDeviceIdPair();
    }

    NodeInfoBase::platform_device_pair_t& NodeInfoBase::platformDeviceIdPair()
    {
        return this->nodeId().platformDeviceIdPair();
    }

    NodeInfoBase::platform_device_pair_t const*
    NodeInfoBase::ptrPlatformDeviceIdPair() const SIXTRL_NOEXCEPT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->ptrPlatformDeviceIdPair() : nullptr;
    }

    NodeInfoBase::platform_device_pair_t&
    NodeInfoBase::ptrPlatformDeviceIdPair() SIXTRL_NOEXCEPT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->ptrPlatformDeviceIdPair() : nullptr;
    }

    /* ----------------------------------------------------------------- */

    bool NodeInfoBase::hasControllers() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasNodeId() ) &&
                 ( this->ptrNodeId()->hasControllers() ) );
    }

    NodeInfoBase::size_type
    NodeInfoBase::numControllers() const SIXTRL_NOEXCEPT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->numControllers()
            : NodeInfoBase::size_type{ 0 };
    }

    bool NodeInfoBase::isAttachedToController( NodeInfoBase::controller_base_t
        const& SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasNodeId() ) &&
                 ( this->ptrNodeId()->isAttachedToController( ctrl ) ) );
    }

    bool NodeInfoBase::hasNodeIndex( NodeInfoBase::controller_base_t const&
        SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasNodeId() ) &&
                 ( this->ptrNodeId()->hasNodeIndex( ctrl ) ) );
    }

    NodeInfoBase::node_index_t NodeInfoBase::nodeIndex(
        NodeInfoBase::controller_base_t const& SIXTRL_RESTRICT_REF
            ctrl ) const SIXTRL_NOEXCEPT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->nodeIndex( ctrl )
            : st::NodeInfoBase::UNDEFINED_INDEX;
    }

    NodeInfoBase::status_t NodeInfoBase::setNodeIndex(
        NodeInfoBase::controller_base_t const& SIXTRL_RESTRICT_REF ctrl,
        NodeInfoBase::node_index_t const node_index ) SIXTRL_RESTRICT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->setNodeIndex( ctrl, node_index )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    bool NodeInfoBase::isSelected() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasNodeId() ) && ( this->ptrNodeId()->isSelected() ) );
    }

    bool NodeInfoBase::isSelectedByController( controller_base_t const&
        SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasNodeId() ) &&
                 ( this->ptrNodeId()->isSelectedByController( ctrl ) ) );
    }

    bool NodeInfoBase::isDefault() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasNodeId() ) && ( this->isDefault() ) );
    }

    bool NodeInfoBase::isDefaultForController( controller_base_t const&
        SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasNodeId() ) &&
                 ( this->ptrNodeId()->isDefaultForController( ctrl ) ) );
    }

    NodeInfoBase::controller_base_t const*
    NodeInfoBase::ptrSelectingController() const SIXTRL_NOEXCEPT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->ptrSelectingController() : nullptr;
    }

    NodeInfoBase::status_t NodeInfoBase::setPtrSelectedController(
        NodeInfoBase::controller_base_t const*
            SIXTRL_RESTRICT ptr_ctrl ) SIXTRL_NOEXCEPT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->setPtrSelectedController( ptr_ctrl )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    NodeInfoBase::status_t NodeInfoBase::setSelectedController(
        NodeInfoBase::controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) SIXTRL_NOEXCEPT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->setSelectedController( ctrl )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    NodeInfoBase::status_t
    NodeInfoBase::resetSelectingController() SIXTRL_NOEXCEPT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->resetSelectingController()
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    NodeInfoBase::status_t NodeInfoBase::attachToController(
        NodeInfoBase::controller_base_t const& SIXTRL_RESTRICT_REF ctrl,
        NodeInfoBase::node_index_t const node_index = UNDEFINED_INDEX )
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->attachToController( ctrl, node_index )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    NodeInfoBase::status_t NodeInfoBase::detachFromController(
        NodeInfoBase::controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) SIXTRL_NOEXCEPT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->detachFromController( ctrl )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    NodeInfoBase::controller_base_t const*
    NodeInfoBase::controllersBegin() const SIXTRL_NOEXCEPT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->controllersBegin() : nullptr;
    }

    NodeInfoBase::controller_base_t const*
    NodeInfoBase::controllersEnd() const SIXTRL_NOEXCEPT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->controllersEnd() : nullptr;
    }

    NodeInfoBase::controller_base_t const* ptrController(
        NodeInfoBase::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        return ( this->hasNodeId() )
            ? this->ptrNodeId()->ptrController( nn ) : nullptr;
    }

    /* --------------------------------------------------------------------- */

    bool NodeInfoBase::hasPlatformName() const SIXTRL_NOEXCEPT
    {
        return !this->m_platform_name.empty();
    }

    std::string const& NodeInfoBase::platformName() const SIXTRL_NOEXCEPT
    {
        return this->m_platform_name;
    }

    char const* NodeInfoBase::ptrPlatformNameStr() const SIXTRL_NOEXCEPT
    {
        return this->m_platform_name.c_str();
    }

    void NodeInfoBase::setPlatformName(
        std::string const& SIXTRL_RESTRICT_REF platform_name )
    {
        this->m_platform_name = platform_name;
    }

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

    bool NodeInfoBase::hasDeviceName() const SIXTRL_NOEXCEPT
    {
        return !this->m_device_name.empty();
    }

    std::string const& NodeInfoBase::deviceName() const SIXTRL_NOEXCEPT
    {
        return this->m_device_name;
    }

    char const* NodeInfoBase::ptrDeviceNameStr() const SIXTRL_NOEXCEPT
    {
        return this->m_device_name.c_str();
    }

    void NodeInfoBase::setDeviceName(
        std::string const& SIXTRL_RESTRICT_REF device_name )
    {
        this->m_device_name = device_name;
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

    bool NodeInfoBase::hasDescription() const SIXTRL_NOEXCEPT
    {
        return !this->m_description.empty();
    }

    std::string const& NodeInfoBase::description() const SIXTRL_NOEXCEPT
    {
        return this->m_description;
    }

    char const* NodeInfoBase::ptrDescriptionStr() const SIXTRL_NOEXCEPT
    {
        return this->m_description.c_str();
    }

    void NodeInfoBase::setDescription(
        std::string const& SIXTRL_RESTRICT_REF description )
    {
        this->m_description = description;
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



    /* --------------------------------------------------------------------- */

    std::ostream& operator<<( std::ostream& SIXTRL_RESTRICT_REF output,
        NodeInfoBase const& SIXTRL_RESTRICT_REF node_info )
    {
        node_info.doPrintToOutputStream( output, nullptr );
        return output;
    }

    void NodeInfoBase::print( ::FILE* SIXTRL_RESTRICT output,
        NodeInfoBase::controller_base_t const* ptr_ctrl ) const
    {
        if( output != nullptr )
        {
            std::ostringstream a2str;
            this->doPrintToOutputStream( a2str, ptr_ctrl );
            std::string const str( a2str.str() );
            const int ret = std::fprintf( output, "%s", str.c_str() );
            SIXTRL_ASSERT( ret >= 0 );
            ( void )ret;
        }

        return;
    }

    void NodeInfoBase::printOut(
        NodeInfoBase::controller_base_t const* ptr_ctrl ) const
    {
        this->print( ::stdout, ptr_ctrl );
    }


    NodeInfoBase::size_type
    NodeInfoBase::requiredOutStringLength(
        NodeInfoBase::controller_base_t const* ptr_ctrl ) const
    {
        std::ostringstream a2str;
        this->doPrintToOutputStream( a2str, ptr_ctrl );
        return a2str.str().size(); /* TODO: Find a more efficient method! */
    }

    std::string NodeInfoBase::toString(
        NodeInfoBase::controller_base_t const* ptr_ctrl ) const
    {
        std::ostringstream a2str;
        this->doPrintToOutputStream( a2str, ptr_ctrl );

        return a2str.str();
    }

    NodeInfoBase::status_t NodeInfoBase::toString(
        NodeInfoBase::size_type const out_str_capacity,
        char* SIXTRL_RESTRICT out_str,
        NodeInfoBase::controller_base_t const* ptr_ctrl ) const
    {
        using size_t = NodeInfoBase::size_type;

        NodeInfoBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( out_str_capacity > size_t{ 0 } ) && ( out_str != nullptr ) )
        {
            std::memset( out_str, ( int )'\0', out_str_capacity );

            std::ostringstream a2str;
            this->doPrintToOutputStream( a2str, ptr_ctrl );
            std::string const temp_str = a2str.str();

            if( !temp_str.empty() )
            {
                std::strncpy( out_str, temp_str.c_str(),
                              out_str_capacity - size_t{ 1 } );

                if( out_str_capacity >= temp_str.size() )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    void NodeInfoBase::doPrintToOutputStream(
        std::ostream& SIXTRL_RESTRICT_REF output,
        NodeInfoBase::controller_base_t const* ptr_ctrl ) const
    {
        using size_t = NodeInfoBase::size_type;

        if( ( this->hasNodeId() ) && ( this->numControllers() > size_t{ 0 } ) )
        {
            if( ptr_ctrl == nullptr )
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
            else if( !this->ptrNodeId()->isAttachedToController( *ptr_ctrl ) )
            {
                ptr_ctrl = nullptr;
            }
        }

        if( this->hasNodeId() )
        {
            output << "Node            : "
                   << this->ptrNodeId()->toNodeIdStr();

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

        output << "\r\nArchitecture    : id = " << this->archId();

        if( this->hasArchStr() )
        {
            output << " " << this->archStr();
        }

        output << "\r\n";

        if( this->hasPlatformName() )
        {
            output << "Platform        : " << this->platformName() << "\r\n";
        }

        if( this->hasDeviceName() )
        {
            output << "Device          : " << this->deviceName() << "\r\n";
        }

        if( this->hasDescription() )
        {
            output << "Description     : " << this->description() << "\r\n";
        }

        return;
    }

    void NodeInfoBase::doUpdateStoredNodeId(
        NodeInfoBase::stored_node_id_t&& ptr_node_id ) SIXTRL_NOEXCEPT
    {
        this->m_ptr_stored_node_id = std::move( ptr_node_id );
    }

    NodeInfoBase::status_t NodeInfoBase::doSetPtrNodeId(
        NodeInfoBase::node_id_t* SIXTRL_RESTRICT ptr_node_id ) SIXTRL_NOEXCEPT
    {
        NodeInfoBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->m_ptr_stored_node_id.get() != nullptr ) &&
            ( ptr_node_id == this->m_ptr_stored_node_id.get() ) )
        {
            this->m_ptr_node_id = ptr_node_id;
            status = st::ARCH_STATUS_SUCCESS;
        }
        else if( ( this->m_ptr_stored_node_id.get() == nullptr ) &&
                 ( this->m_ptr_node_id != nullptr ) &&
                 ( ptr_node_id == nullptr ) )
        {
            this->m_ptr_node_id = ptr_node_id;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }
}

/* end: sixtracklib/common/control/node_info.cpp */
