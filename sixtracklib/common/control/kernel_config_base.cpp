#include "sixtracklib/common/control/kernel_config_base.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/arch_base.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    KernelConfigBase::KernelConfigBase(
        KernelConfigBase::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT arch_str,
        KernelConfigBase::size_type const num_kernel_args,
        char const* SIXTRL_RESTRICT kernel_name_str,
        KernelConfigBase::variant_t const variant_flags,
        char const* SIXTRL_RESTRICT config_str ) :
        st::ArchBase( arch_id, arch_str, config_str ),
        m_nodes(), m_name(), m_num_kernel_args( num_kernel_args ),
        m_kernel_id( st::KernelConfigBase::ILLEGAL_KERNEL_ID ),
        m_variant_flags( variant_flags ), m_needs_update( false )
    {
        if( kernel_name_str != nullptr ) this->setName( kernel_name_str );
    }

    KernelConfigBase::KernelConfigBase(
        KernelConfigBase::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        KernelConfigBase::size_type const num_kernel_args,
        std::string const& SIXTRL_RESTRICT_REF kernel_name,
        KernelConfigBase::variant_t const variant_flags,
        std::string const& SIXTRL_RESTRICT_REF config_str ) :
        st::ArchBase( arch_id, arch_str, config_str ),
        m_nodes(), m_name( kernel_name ), m_num_kernel_args( num_kernel_args ),
        m_kernel_id( st::KernelConfigBase::ILLEGAL_KERNEL_ID ),
        m_variant_flags( variant_flags ), m_needs_update( false )
    {

    }

    /* --------------------------------------------------------------------- */

    bool KernelConfigBase::hasKernelId() const SIXTRL_NOEXCEPT
    {
        return ( this->m_kernel_id != KernelConfigBase::ILLEGAL_KERNEL_ID );
    }

    KernelConfigBase::kernel_id_t
    KernelConfigBase::kernelId() const SIXTRL_NOEXCEPT
    {
        return this->m_kernel_id;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    void KernelConfigBase::setKernelId(
        KernelConfigBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        this->m_kernel_id = kernel_id;
    }

    /* --------------------------------------------------------------------- */

    bool KernelConfigBase::hasName() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_name.empty() );
    }

    std::string const& KernelConfigBase::name() const SIXTRL_NOEXCEPT
    {
        return this->m_name;
    }

    char const* KernelConfigBase::ptrNameStr() const SIXTRL_NOEXCEPT
    {
        return this->m_name.c_str();
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    void KernelConfigBase::setName(
        std::string const& SIXTRL_RESTRICT_REF kernel_name )
    {
        this->m_name = kernel_name;
    }

    void KernelConfigBase::setName(
        char const* SIXTRL_RESTRICT kernel_name )
    {
        using size_t = KernelConfigBase::size_type;

        if( ( kernel_name != nullptr ) &&
            ( std::strlen( kernel_name ) > size_t{ 0 } ) )
        {
            this->m_name = kernel_name;
        }
        else
        {
            this->m_name.clear();
        }
    }

    /* --------------------------------------------------------------------- */

    KernelConfigBase::size_type
    KernelConfigBase::numArguments() const SIXTRL_NOEXCEPT
    {
        return this->m_num_kernel_args;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    void KernelConfigBase::setNumArguments(
        KernelConfigBase::size_type const num_kernel_args ) SIXTRL_NOEXCEPT
    {
        this->m_num_kernel_args = num_kernel_args;
    }

    /* --------------------------------------------------------------------- */

    void KernelConfigBase::clear()
    {
        this->doClear();
    }

    bool KernelConfigBase::needsUpdate() const SIXTRL_NOEXCEPT
    {
        return this->m_needs_update;
    }

    KernelConfigBase::status_t KernelConfigBase::update()
    {
        KernelConfigBase::status_t const update_status = this->doUpdate();

        if( update_status == st::ARCH_STATUS_SUCCESS )
        {
            this->doSetNeedsUpdateFlag( false );
        }

        return update_status;
    }

    /* ----------------------------------------------------------------- */

    KernelConfigBase::variant_t
    KernelConfigBase::variantFlags() const SIXTRL_NOEXCEPT
    {
        return this->m_variant_flags;
    }

    bool KernelConfigBase::areVariantFlagsSet(
        KernelConfigBase::variant_t const var_flags ) const SIXTRL_NOEXCEPT
    {
        return ( ( var_flags != st::KERNEL_CONFIG_VARIANT_NONE ) &&
                 ( var_flags == ( this->m_variant_flags & var_flags ) ) );
    }

    bool KernelConfigBase::variantDebugMode() const SIXTRL_NOEXCEPT
    {
        return this->areVariantFlagsSet( st::KERNEL_CONFIG_VARIANT_DEBUG_MODE );
    }

    bool KernelConfigBase::variantReleaseMode() const SIXTRL_NOEXCEPT
    {
        return !this->variantDebugMode() const SIXTRL_NOEXCEPT;
    }

    void KernelConfigBase::setVariantFlags(
        KernelConfigBase::variant_t const variant_flags ) SIXTRL_NOEXCEPT
    {
        this->m_variant_flags = variant_flags;
    }

    /* ----------------------------------------------------------------- */

    bool KernelConfigBase::hasNodes() const SIXTRL_NOEXCEPT
    {
        return ( this->m_nodes.empty() );
    }

    KernelConfigBase::size_type
    KernelConfigBase::numNodes() const SIXTRL_NOEXCEPT
    {
        return this->m_nodes.size();
    }

    KernelConfigBase::node_id_t const*
    KernelConfigBase::nodesBegin() const SIXTRL_NOEXCEPT
    {
        return this->m_nodes.data();
    }

    KernelConfigBase::node_id_t const*
    KernelConfigBase::nodesEnd() const SIXTRL_NOEXCEPT
    {
        KernelConfigBase::node_id_t const* end_ptr = this->nodesBegin();

        if( ( end_ptr != nullptr ) && ( this->hasNodes() ) )
        {
            std::advance( end_ptr, this->numNodes() );
        }

        return end_ptr;
    }

    KernelConfigBase::node_id_t const* KernelConfigBase::ptrNode(
        KernelConfigBase::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        KernelConfigBase::node_id_t const* ptr_node = nullptr;

        if( ( this->hasNodes() ) && ( this->numNodes() > nn ) )
        {
            ptr_node = this->nodesBegin();

            if( ptr_node != nullptr )
            {
                std::advance( ptr_node, nn );
            }
        }

        return ptr_node;
    }

    KernelConfigBase::node_id_t* KernelConfigBase::nodesBegin() SIXTRL_NOEXCEPT
    {
        return const_cast< KernelConfigBase::node_id_t* >( static_cast<
            KernelConfigBase const& >( *this ).nodesBegin() );
    }

    KernelConfigBase::node_id_t* KernelConfigBase::nodesEnd() SIXTRL_NOEXCEPT
    {
        return const_cast< KernelConfigBase::node_id_t* >( static_cast<
            KernelConfigBase const& >( *this ).nodesEnd() );
    }

    KernelConfigBase::node_id_t* KernelConfigBase::ptrNode(
        KernelConfigBase::size_type const num_node_in_list ) SIXTRL_NOEXCEPT
    {
        return const_cast< KernelConfigBase::node_id_t* >( static_cast<
            KernelConfigBase const& >( *this ).ptrNode( num_node_in_list ) );
    }

    KernelConfigBase::status_t KernelConfigBase::assignToNode(
        KernelConfigBase::node_id_t const& node )
    {
        using size_t = KernelConfigBase::size_type;

        size_t const prev_num_nodes = this->numNodes();

        SIXTRL_ASSERT( ( prev_num_nodes == size_t{ 0 } ) ||
            ( std::is_sorted( this->m_nodes.begin(), this->m_nodes.end() ) ) );

        KernelConfigBase::status_t status = this->doAssignToNode( node );

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( prev_num_nodes > size_t{ 0 } ) )
        {
            std::sort( this->m_nodes.begin(), this->m_nodes.end() );
        }

        SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
            ( ( this->hasNodes() ) && ( this->isAssignedToNode( node ) ) ) );

        return status;
    }

    bool KernelConfigBase::isAssignedToNode(
        KernelConfigBase::node_id_t const& node_id ) const SIXTRL_NOEXCEPT
    {
        return this->isAssignedToNode( node.platformId(), node.deviceId() );
    }

    bool KernelConfigBase::isAssignedToNode(
        KernelConfigBase::platform_id_t const platform_id,
        KernelConfigBase::device_id_t const device_id ) const SIXTRL_NOEXCEPT
    {
        return ( nullptr != this->doFindNodeByPlatformIdAndDeviceId(
            platform_id, device_id ) );
    }

    KernelConfigBase::status_t
    KernelConfigBase::detachFromNode( KernelConfigBase::node_id_t const& node )
    {
        return this->detachFromNode( node.platformId(), node.deviceId() );
    }

    KernelConfigBase::status_t KernelConfigBase::detachFromNode(
        KernelConfigBase::platform_id_t const platform_id,
        KernelConfigBase::device_id_t const device_id )
    {
        KernelConfigBase::status_t status =
            this->doDetachFromNode( platform_id, device_id );

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( this->hasNodes() ) )
        {
            std::sort( this->m_nodes.begin(), this->m_nodes.end() );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    void KernelConfigBase::doClear()
    {
        this->doClearBaseImpl();
    }

    void KernelConfigBase::doReset( KernelConfigBase::size_type work_items_dim,
        KernelConfigBase::size_type work_groups_dim )
    {
        this->doResetBaseImpl( work_items_dim, work_groups_dim );
    }

    KernelConfigBase::status_t KernelConfigBase::doUpdate()
    {
        KernelConfigBase::status_t const status = st::ARCH_STATUS_SUCCESS;
        return status;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigBase::status_t KernelConfigBase::doAssignToNode(
        KernelConfigBase::node_id_t const& SIXTRL_RESTRICT_REF node )
    {
        return this->doAssignToNodeBaseImpl( node );
    }

    KernelConfigBase::status_t KernelConfigBase::doDetachFromNode(
        KernelConfigBase::platform_id_t const platform_id,
        KernelConfigBase::device_id_t const device_id )
    {
        return this->doDetachFromNodeBaseImpl( platform_id, device_id );
    }

    KernelConfigBase::node_id_t const*
    KernelConfigBase::doFindNodeByPlatformIdAndDeviceId(
        KernelConfigBase::platform_id_t const plartform_id,
        KernelConfigBase::device_id_t const device_id ) const SIXTRL_NOEXCEPT
    {
        KernelConfigBase::node_id_t const* ptr_node_id = nullptr;

        if( ( this->numNodes() > KernelConfigBase::size_type{ 0 } ) &&
            ( platform_id != KernelConfigBase::ILLEGAL_PLATFORM_ID ) &&
            ( device_id != KernelConfigBase::ILLEGAL_DEVICE_ID ) )
        {
            for( KernelConfigBase::node_id_t const& node_id : this->m_nodes )
            {
                if( ( node_id.platformId() == platform_id ) &&
                    ( node_id.deviceId() == device_id ) )
                {
                    ptr_node_id = &node_id;
                    break;
                }
            }
        }

        return ptr_node_id;
    }

    KernelConfigBase::node_id_t*
    KernelConfigBase::doFindNodeByPlatformIdAndDeviceId(
        KernelConfigBase::platform_id_t const plartform_id,
        KernelConfigBase::device_id_t const device_id ) SIXTRL_NOEXCEPT
    {
        return const_cast< KernelConfigBase::node_id_t* >(
            static_cast< KernelConfigBase const& >( *this
                ).doFindNodeByPlatformIdAndDeviceId( platform_id, device_id ) );
    }

    void KernelConfigBase::doSetNeedsUpdateFlag(
        bool const needs_update ) SIXTRL_NOEXCEPT
    {
        this->m_needs_update = needs_update;
    }

    /* --------------------------------------------------------------------- */

    void KernelConfigBase::doClearBaseImpl() SIXTRL_NOEXCEPT
    {
        this->m_nodes.clear();
        this->m_name.clear();
        this->m_num_kernel_args = KernelConfigBase::size_type{ 0 };
        this->m_kernel_id = KernelConfigBase::ILLEGAL_KERNEL_ID;
        this->m_needs_update = false;
    }

    KernelConfigBase::status_t KernelConfigBase::doAssignToNodeBaseImpl(
        KernelConfigBase::node_id_t const& SIXTRL_RESTRICT_REF node )
    {
        KernelConfigBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( node.valid() ) &&
            ( nullptr == this->doFindNodeByPlatformIdAndDeviceId(
                node.platformId(), node.deviceId() ) ) )
        {
            this->m_nodes.push_back( node );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    KernelConfigBase::status_t KernelConfigBase::doDetachFromNodeBaseImpl(
        KernelConfigBase::platform_id_t const platform_id,
        KernelConfigBase::device_id_t const device_id )
    {
        KernelConfigBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( platform_id != KernelConfigBase::ILLEGAL_PLATFORM_ID ) &&
            ( device_id != KernelConfigBase::ILLEGAL_DEVICE_ID ) &&
            ( !this->m_nodes.empty() ) )
        {
            auto iter = std::find( this->m_nodes.begin(), this->m_nodes.end(),
                [&platform_id, &device_id](
                    KernelConfigBase::node_id_t const& cmp_node_id )
                {
                    return ( ( cmp_node_id.platformId() == platform_id ) &&
                             ( cmp_node_id.deviceId() == device_id ) );
                } );

            if( iter != this->m_nodes.end() )
            {
                this->m_nodes.erase( iter );
                status = st::ARCH_STATUS_SUCCESS;
            }
        }
    }

    /* --------------------------------------------------------------------- */

    void KernelConfigBase::print(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        this->doPrintToOutputStream( output );
    }

    void KernelConfigBase::print( ::FILE* SIXTRL_RESTRICT output ) const
    {
        if( output != nullptr )
        {
            std::ostringstream a2str;
            this->print( a2str );
            std::string const string_output( a2str.str() );

            if( !string_output.empty() )
            {
                int const ret = std::fprintf(
                    output, "%s", string_output.c_str() );

                SIXTRL_ASSERT( ret > int{ 0 } );
                ( void )ret;
            }
        }
    }

    void KernelConfigBase::printOut() const
    {
        this->print( std::cout );
    }

    /* --------------------------------------------------------------------- */

    void KernelConfigBase::doPrintToOutputStream(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        using size_t = KernelConfigBase::size_type;
        using node_id_t = KernelConfigBase::node_id_t;

        if( this->needsUpdate() )
        {
            output << "!!! WARNING: Preliminary values, "
                   << "call update() before using !!!\r\n\r\n";
        }

        if( this->hasName() )
        {
            output << "kernel name           : " << this->m_name << "\r\n";
        }

        output << "num kernel arguments  : "
               << this->m_num_kernel_args << "\r\n";

        size_t const nn = this->m_nodes.size();
        output << "num of attached nodes : " << nn << "\r\n";

        if( nn > size_t{ 0 } )
        {
            output << "      node id strings : ";

            for( size_t ii = size_t{ 0 } ; ii < nn ; ++ii )
            {
                if( ii > size_t{ 0 } ) output << ", ";
                output << this->m_nodes[ ii ];
            }

            output << "\r\n";
        }

        return;
    }

    /* ===================================================================== */

    std::ostream& operator<<( std::ostream& SIXTRL_RESTRICT_REF output,
        KernelConfigBase const& SIXTRL_RESTRICT_REF config )
    {
        config.print( output );
        return output;
    }
}

/* end: sixtracklib/common/control/kernel_config_base.cpp */
