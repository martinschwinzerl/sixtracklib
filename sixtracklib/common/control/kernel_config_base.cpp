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
        KernelConfigBase::purpose_t const purpose,
        KernelConfigBase::variant_t const variant_flags,
        char const* SIXTRL_RESTRICT kernel_name_str,
        char const* SIXTRL_RESTRICT config_str ) :
        KernelConfigBase::_arch_base_t(
            variant_flags, arch_id, arch_str, config_str ),
        m_name(), m_num_kernel_args( num_kernel_args ),
        m_kernel_purpose( purpose ),
        m_needs_update( false ),
        m_perform_auto_update( false )
    {
        if( kernel_name_str != nullptr ) this->setName( kernel_name_str );
    }

    KernelConfigBase::KernelConfigBase(
        KernelConfigBase::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        KernelConfigBase::size_type const num_kernel_args,
        KernelConfigBase::purpose_t const purpose,
        KernelConfigBase::variant_t const variant_flags,
        std::string const& SIXTRL_RESTRICT_REF kernel_name,
        std::string const& SIXTRL_RESTRICT_REF config_str ) :
        KernelConfigBase::_arch_base_t(
            variant_flags, arch_id, arch_str, config_str ),
        m_name( kernel_name ), m_num_kernel_args( num_kernel_args ),
        m_kernel_purpose( purpose ),
        m_needs_update( false ),
        m_perform_auto_update( false )
    {

    }

    /* --------------------------------------------------------------------- */

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

    KernelConfigBase::status_t KernelConfigBase::setNumArguments(
        KernelConfigBase::size_type const num_kernel_args ) SIXTRL_NOEXCEPT
    {
        KernelConfigBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->m_num_kernel_args == num_kernel_args )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }
        else
        {
            this->m_num_kernel_args = num_kernel_args;
            status = this->doSetNeedsUpdate();
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigBase::status_t KernelConfigBase::update()
    {
        KernelConfigBase::status_t const update_status = this->doUpdate();

        if( update_status == st::ARCH_STATUS_SUCCESS )
        {
            this->doSetNeedsUpdateFlag( false );
        }

        return update_status;
    }

    /* --------------------------------------------------------------------- */

    void KernelConfigBase::doSetPurpose(
        KernelConfigBase::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        this->m_purpose = purpose;
        return st::ARCH_STATUS_SUCCESS;
    }

    void KernelConfigBase::doSetNeedsUpdateFlag(
        bool const needs_update ) SIXTRL_NOEXCEPT
    {
        this->m_needs_update = needs_update;
    }

    void KernelConfigBase::doSetPerformsAutoUpdatesFlag(
        bool const perform_auto_update ) SIXTRL_NOEXCEPT
    {
        this->m_perform_auto_update = perform_auto_update;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigBase::status_t KernelConfigBase::updateConfigStr(
        char const* SIXTRL_RESTRICT config_str )
    {
        using  _this_t = st::KernelConfigBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->doParseConfigStr( config_str.c_str() ) )
        {
            status = this->doSetNeedsUpdate();
        }
        else if( ( config_str != nullptr ) &&
                 ( std::strlen( config_str ) > _this_t::size_type{ 0 } ) )
        {
            this->doUpdateStoredConfigStr( config_str );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    void KernelConfigBase::doClearBaseImpl() SIXTRL_NOEXCEPT
    {
        this->doSetVariantFlags( st::ARCH_VARIANT_NONE );

        this->m_name.clear();
        this->m_num_kernel_args = KernelConfigBase::size_type{ 0 };
        this->m_kernel_purpose = st::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;
        this->m_needs_update = false;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigBase::size_type
    KernelConfigBase::requiredOutStringLength() const
    {
        return this->toString().size() + KernelConfigBase::size_type{ 1 };
    }

    std::string KernelConfigBase::toString() const
    {
        std::ostringstream a2str;
        KernelConfigBase::status_t const status =
            this->doPrintToOutputStream( a2str );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            return a2str.str();
        }

        return std::string{};
    }

    KernelConfigBase::status_t KernelConfigBase::toString(
        KernelConfigBase::size_type const out_str_capacity,
        char* SIXTRL_RESTRICT out_str ) const
    {
        using size_t = KernelConfigBase::size_type;

        KernelConfigBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( out_str != nullptr ) && ( out_str_capacity > size_t{ 0 } ) )
        {
            std::memset( out_str, static_cast< int >( '\0' ),
                         out_str_capacity );

            std::string const temp_str = this->toString();

            if( ( !temp_str.empty() ) &&
                ( temp_str.size() < out_str_capacity ) )
            {
                std::strncpy( out_str, temp_str.c_str(),
                              out_str_capacity - size_t{ 1 } );

                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

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

            KernelConfigBase::status_t const status =
                this->doPrintToOutputStream( a2str );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                std::string const temp_str = a2str.str();
                int const ret = std::fprintf( fp, "%s", temp_str.c_str() );
                SIXTRL_ASSERT( ret >= 0 );
                ( void )ret;
            }
        }

        return;
    }

    void KernelConfigBase::printOut() const
    {
        this->print( std::cout );
    }

    std::ostream& operator<<( std::ostream& SIXTRL_RESTRICT_REF output,
        NodeInfoBase const& SIXTRL_RESTRICT_REF node_info )
    {
        node_info.print( output );
        return output;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigBase::status_t KernelConfigBase::doPrintToOutputStream(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        using size_t = KernelConfigBase::size_type;
        using node_id_t = KernelConfigBase::node_id_t;

        KernelConfigBase::status_t status = st::ARCH_STATUS_SUCCESS;

        if( this->needsUpdate() )
        {
            output << "!!! WARNING: Preliminary values, "
                   << "call update() before using !!!\r\n\r\n";
        }

        output << "\r\nArchitecture          : id = " << this->archId();
        if( this->hasArchStr() ) output << " " << this->archStr();

        output << "Number Kernel Args    : "
               << this->numArguments() << "\r\n";

        if( this->hasSpecifiedPurpose() )
        {
            output << "Kernel Purpose        : "
                   << std::setw( 6 ) << this->m_purpose << " (";

            switch( this->m_purpose )
            {
                case st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER:
                {
                    output << "remap buffer kernel)\r\n";
                    break;
                }

                case st::KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES:
                {
                    output << "fetch particle addresses kernel)\r\n";
                    break;
                }

                case st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN:
                {
                    output << "track until turn kernel)\r\n";
                    break;
                }

                case st::KERNEL_CONFIG_PURPOSE_TRACK_ELEM_BY_ELEM:
                {
                    output << "track elem by elem kernel)\r\n";
                    break;
                }

                case st::KERNEL_CONFIG_PURPOSE_TRACK_LINE:
                {
                    output << "track line kernel)\r\n";
                    break;
                }

                case st::KERNEL_CONFIG_PURPOSE_ASSIGN_BEAM_MONITOR_OUTPUT:
                {
                    output << "assign beam monitor output kerel)\r\n";
                    break;
                }

                case st::KERNEL_CONFIG_PURPOSE_ASSIGN_ELEM_BY_ELEM_OUTPUT:
                {
                    output << "assign elem by elem output kernel)\r\n";
                    break;
                }

                default:
                {
                    output << "userdefined kernel)\r\n";
                }
            };
        }
        else
        {
            output << "Kernel Purpose        : "
                   << std::setw( 6 ) << this->m_purpose
                   << " (unspecified)\r\n";
        }

        if( this->variantDebugMode() )
        {
            output << "Variant               : debug\r\n";
        }
        else if( this->variantReleaseMode() )
        {
            output << "Variant               : release\r\n";
        }

        if( this->variantFlags() > st::KERNEL_CONFIG_VARIANT_NONE )
        {
            output << "Variant Flags         : " << std::setw( 6 )
                   << this->variantFlags() << "\r\n";
        }

        if( this->hasName() )
        {
            output << "Kernel name           : " << this->m_name << "\r\n";
        }

        if( this->hasConfigStr() )
        {
            output << "Kernel config string  : "
                   << this->configStr() << "\r\n";
        }

        return status;
    }

    void KernelConfigBase::doClear()
    {
        this->doClearBaseImpl();
    }

    KernelConfigBase::status_t KernelConfigBase::doUpdate()
    {
        KernelConfigBase::status_t const status = st::ARCH_STATUS_SUCCESS;
        return status;
    }

    KernelConfigBase::status_t KernelConfigBase::doSetNeedsUpdate()
    {
        KernelConfigBase::status_t status = st::ARCH_STATUS_SUCCESS;

        if( this->performsAutoUpdate() )
        {
            status = this->doUpdate();

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                this->doSetNeedsUpdateFlag( false );
            }
        }
        else
        {
            this->doSetNeedsUpdateFlag( true );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

}

/* end: sixtracklib/common/control/kernel_config_base.cpp */
