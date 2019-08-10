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
    using _conf_t = st::KernelConfigBase;

    constexpr _conf_t::size_type        _conf_t::DEFAULT_NUM_KERNEL_ARGUMENTS;
    constexpr _conf_t::purpose_t        _conf_t::DEFAULT_KERNEL_PURPOSE;
    constexpr _conf_t::variant_t        _conf_t::DEFAULT_KERNEL_VARIANT;
    constexpr _conf_t::argument_set_t   _conf_t::DEFAULT_ARGUMENT_SET;
    constexpr _conf_t::kernel_set_id_t  _conf_t::ILLEGAL_KERNEL_SET_ID;
    constexpr _conf_t::size_type _conf_t::DEFAULT_MAX_NUM_ATTACHED_KERNEL_SETS;

    KernelConfigBase::KernelConfigBase(
        _conf_t::arch_id_t const arch_id,
        _conf_t::size_type const num_kernel_args,
        _conf_t::purpose_t const purpose,
        _conf_t::variant_t const variant_flags,
        char const* SIXTRL_RESTRICT kernel_name_str,
        char const* SIXTRL_RESTRICT config_str ) :
        _conf_t::_arch_base_t( variant_flags, arch_id, config_str ),
        m_name(), m_kernel_set_ids(),
        m_num_kernel_args( num_kernel_args ),
        m_max_attached_kernel_ids(
            _conf_t::DEFAULT_MAX_NUM_ATTACHED_KERNEL_SETS ),
        m_purpose( purpose ),
        m_argument_set( _conf_t::DEFAULT_ARGUMENT_SET ),
        m_needs_update( false ),
        m_perform_auto_update( false )
    {
        this->m_kernel_set_ids.reserve( this->m_max_attached_kernel_ids );
        if( kernel_name_str != nullptr ) this->setName( kernel_name_str );
    }

    KernelConfigBase::KernelConfigBase(
        _conf_t::key_t const& SIXTRL_RESTRICT_REF key,
        _conf_t::size_type const num_kernel_args,
        char const* SIXTRL_RESTRICT kernel_name_str ) :
        KernelConfigBase::_arch_base_t(
            key.variant(), key.archId(), key.ptrConfigStr() ),
        m_name(), m_kernel_set_ids(),
        m_num_kernel_args( num_kernel_args ),
        m_max_attached_kernel_ids(
            _conf_t::DEFAULT_MAX_NUM_ATTACHED_KERNEL_SETS ),
        m_purpose( key.purpose() ),
        m_argument_set( key.argumentSet() ),
        m_needs_update( false ),
        m_perform_auto_update( false )
    {
        this->m_kernel_set_ids.reserve( this->m_max_attached_kernel_ids );
        if( kernel_name_str != nullptr ) this->setName( kernel_name_str );
    }

    KernelConfigBase::KernelConfigBase(
        _conf_t::arch_id_t const arch_id,
        _conf_t::size_type const num_kernel_args,
        _conf_t::purpose_t const purpose,
        _conf_t::variant_t const variant_flags,
        std::string const& SIXTRL_RESTRICT_REF kernel_name_str,
        std::string const& SIXTRL_RESTRICT_REF config_str ) :
        _conf_t::_arch_base_t( variant_flags, arch_id, config_str ),
        m_name( kernel_name_str ), m_kernel_set_ids(),
        m_num_kernel_args( num_kernel_args ),
        m_max_attached_kernel_ids(
            _conf_t::DEFAULT_MAX_NUM_ATTACHED_KERNEL_SETS ),
        m_purpose( purpose ),
        m_argument_set( _conf_t::DEFAULT_ARGUMENT_SET ),
        m_needs_update( false ),
        m_perform_auto_update( false )
    {
        this->m_kernel_set_ids.reserve( this->m_max_attached_kernel_ids );
    }

    KernelConfigBase::KernelConfigBase(
        _conf_t::key_t const& SIXTRL_RESTRICT_REF key,
        _conf_t::size_type const num_kernel_args,
        std::string const& SIXTRL_RESTRICT_REF kernel_name_str ) :
        KernelConfigBase::_arch_base_t(
            key.variant(), key.archId(), key.ptrConfigStr() ),
        m_name( kernel_name_str ), m_kernel_set_ids(),
        m_num_kernel_args( num_kernel_args ),
        m_max_attached_kernel_ids(
            _conf_t::DEFAULT_MAX_NUM_ATTACHED_KERNEL_SETS ),
        m_purpose( key.purpose() ),
        m_argument_set( key.argumentSet() ),
        m_needs_update( false ),
        m_perform_auto_update( false )
    {
        this->m_kernel_set_ids.reserve( this->m_max_attached_kernel_ids );
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
        KernelConfigBase::size_type const num_kernel_args )
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

    _conf_t::status_t KernelConfigBase::attachToSet(
        _conf_t::kernel_set_id_t const kernel_set_id )
    {
        _conf_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_set_id != _conf_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( this->maxNumAttachedSets() > this->numAttachedSets() ) &&
            ( !this->isAttachedToSet( kernel_set_id ) ) )
        {
            _conf_t::kernel_set_id_t const last =
                ( this->m_kernel_set_ids.empty() )
                    ? _conf_t::kernel_set_id_t{ 0 }
                    : this->m_kernel_set_ids.back();

            this->m_kernel_set_ids.push_back( kernel_set_id );

            if( last > kernel_set_id )
            {
                std::sort( this->m_kernel_set_ids.begin(),
                           this->m_kernel_set_ids.end() );
            }

            SIXTRL_ASSERT( std::is_sorted( this->m_kernel_set_ids.begin(),
                this->m_kernel_set_ids.end() ) );

            SIXTRL_ASSERT( this->maxNumAttachedSets() >=
                           this->numAttachedSets() );

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _conf_t::status_t KernelConfigBase::detachFromSet(
            kernel_set_id_t const kernel_set_id )
    {
        _conf_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_set_id != _conf_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( !this->m_kernel_set_ids.empty() ) )
        {
            SIXTRL_ASSERT( this->maxNumAttachedSets() >=
                           this->numAttachedSets() );

            SIXTRL_ASSERT( std::is_sorted( this->m_kernel_set_ids.begin(),
                           this->m_kernel_set_ids.end() ) );

            auto it = std::lower_bound( this->m_kernel_set_ids.begin(),
                this->m_kernel_set_ids.end(), kernel_set_id );

            if( it != this->m_kernel_set_ids.end() )
            {
                this->m_kernel_set_ids.erase( it );
                status = st::ARCH_STATUS_SUCCESS;
            }
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
        _conf_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->doParseConfigStr( config_str ) )
        {
            status = this->doSetNeedsUpdate();
        }
        else if( ( config_str != nullptr ) &&
                 ( std::strlen( config_str ) > _conf_t::size_type{ 0 } ) )
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
        this->m_kernel_set_ids.clear();
        this->m_num_kernel_args = _conf_t::size_type{ 0 };
        this->m_purpose = st::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;
        this->m_argument_set = _conf_t::DEFAULT_ARGUMENT_SET;
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
                int const ret = std::fprintf( output, "%s", temp_str.c_str() );
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
        KernelConfigBase const& SIXTRL_RESTRICT_REF kernel_config_base )
    {
        kernel_config_base.print( output );
        return output;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigBase::status_t KernelConfigBase::doPrintToOutputStream(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        _conf_t::status_t status = st::ARCH_STATUS_SUCCESS;

        if( this->needsUpdate() )
        {
            output << "!!! WARNING: Preliminary values, "
                   << "call update() before using !!!\r\n\r\n";
        }

        output << "\r\nArchitecture          : id = " << this->archId();
        if( this->hasArchStr() ) output << " " << this->archStr();

        output << "\r\nNumber Kernel Args    : "
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

        if( this->variantFlags() > st::ARCH_VARIANT_NONE )
        {
            output << "Variant Flags         : " << std::setw( 6 )
                   << this->variantFlags() << "\r\n";
        }

        output << "Argument Set          : " << this->argumentSet() << "\r\n";

        if( this->isAttachedToAnySets() )
        {
            output << "Num attached sets     : " << std::setw( 6 )
                   << this->numAttachedSets()
                   << "\r\nAttached set ids      : [ ";

            bool first = true;

            for( auto const kernel_set_id : this->m_kernel_set_ids )
            {
                if( !first ) output << ", ";
                output << kernel_set_id;
            }

            output << " ]\r\n";
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

    void KernelConfigBase::doSetMaxNumAttachedKernelSets(
        KernelConfigBase::size_type const max_num_attached_kernel_sets )
    {
        this->m_max_attached_kernel_ids = max_num_attached_kernel_sets;

        if( this->m_kernel_set_ids.capacity() < max_num_attached_kernel_sets )
        {
            this->m_kernel_set_ids.reserve( max_num_attached_kernel_sets );
        }
    }
}

/* end: sixtracklib/common/control/kernel_config_base.cpp */
