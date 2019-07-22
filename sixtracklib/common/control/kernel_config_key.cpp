#include "sixtracklib/common/control/kernel_config_key.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    void KernelConfigKey::setPurpose(
        KernelConfigKey::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        this->m_purpose = purpose;
    }

    void KernelConfigKey::setConfigStr(
        char const* SIXTRL_RESTRICT config_str )
    {
        using _this_t = st::KernelConfigKey;

        if( ( config_str != nullptr ) &&
            ( std::strlen( config_str ) > _this_t::size_type ) )
        {
            this->m_config_str = std::string{ config_str };
        }
        else
        {
            this->m_config_str.clear();
        }
    }

    /* --------------------------------------------------------------------- */

    bool KernelConfigKey::operator<( KernelConfigKey const&
        SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        bool is_smaller_than = ( this->m_node_id < rhs.m_node_id );

        if( ( !is_smaller_than ) && ( this->m_node_id == rhs.m_node_id ) )
        {
            is_smaller_than = ( this->purpose() < rhs.purpose() );

            if( ( !is_smaller_than ) && ( this->purpose() == rhs.purpose() ) )
            {
                is_smaller_than = ( this->variant() < rhs.variant() );

                if( ( !is_smaller_than ) &&
                    ( this->variant() == rhs.variant() ) &&
                    ( !rhs.m_config_str.empty() ) )
                {
                    if( this->m_config_str.empty() )
                    {
                        is_smaller_than = true;
                    }
                    else if( this->m_config_str.compare(
                        rhs.m_config_str ) < 0 )
                    {
                        is_smaller_than = true;
                    }
                }
            }
        }

        return is_smaller_than;
    }

    bool KernelConfigKey::operator==( KernelConfigKey const&
        SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        bool is_equal = (
            ( this->archId() == rhs.archId() ) &&
            ( this->platformId() == rhs.platformId() ) &&
            ( this->deviceId() == rhs.deviceId() ) &&
            ( this->purpose() == rhs.purpose() ) &&
            ( this->variant() == rhs.variant() ) );

        if( is_equal )
        {
            is_equal = ( this->m_config_str.size() == rhs.m_config_str.size() );

            if( ( is_equal ) && ( !this->m_config_str.empty() ) )
            {
                is_equal = ( 0 == this->m_config.compare( rhs.m_config_str ) );
            }
        }

        return is_equal;
    }

    int KernelConfigKey::compare( KernelConfigKey const&
        SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        int cmp_result = this->m_node_id.compare( rhs.m_node_id );

        if( cmp_result == 0 )
        {
            cmp_result = ( this->purpose() < rhs.purpose() )
                ? -1 : ( ( this->purpose() > rhs.purpose() ) ? +1 : 0 );
        }

        if( cmp_result == 0 )
        {
            cmp_result = ( this->variant() < rhs.variant() )
                ? -1 : ( ( this->variant() > rhs.variant() ) ? +1 : 0 );
        }

        if( cmp_result == 0 )
        {
            if( ( !this->m_config_str.empty() ) &&
                ( !rhs.m_config_str.empty() ) )
            {
                cmp_result = this->m_config_str.compare( rhs.m_config_str );
            }
            else if( !this->m_config_str.empty() )
            {
                cmp_result = +1;
            }
            else if( !rhs.m_config_str.empty() )
            {
                cmp_result = -1;
            }
            else
            {
                cmp_result = 0;
            }
        }

        return cmp_result;
    }

    KernelConfigKey::status_t KernelConfigKey::reset(
        KernelConfigKey::arch_id_t const arch_id,
        KernelConfigKey::purpose_t const purpose,
        KernelConfigKey::variant_t const variant,
        char const* SIXTRL_RESTRICT config_str )
    {
        using _this_t = st::KernelConfigKey;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( arch_id != _this_t::ARCH_ILLEGAL ) &&
            ( this->m_node_id.archId() != _this_t::ARCH_ILLEGAL ) )
        {
            status  = this->m_node_id.setArchId( _this_t::ARCH_ILLEGAL );
            status |= this->m_node_id.setArchId( arch_id );
        }
        else
        {
            status = this->m_node_id.setArchId( arch_id );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = this->m_node_id.setPlatformId(
                _this_t::ILLEGAL_PLATFORM_ID );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = this->m_node_id.setDeviceId( _this_t::ILLEGAL_DEVICE_ID );
        }

        this->setPurpose( purpose );
        this->setVariant( variant );
        this->setConfigStr( config_str );

        return status;
    }
}

/* end: sixtracklib/common/control/kernel_config_key.cpp */
