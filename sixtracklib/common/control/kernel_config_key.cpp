#include "sixtracklib/common/control/kernel_config_key.hpp"

#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/common/control/node_id.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;
using _this_t = st::KernelConfigKey;

namespace SIXTRL_CXX_NAMESPACE
{
    constexpr _this_t::platform_id_t  _this_t::ILLEGAL_PLATFORM_ID;
    constexpr _this_t::device_id_t    _this_t::ILLEGAL_DEVICE_ID;
    constexpr _this_t::purpose_t      _this_t::UNSPECIFIED_PURPOSE;
    constexpr _this_t::arch_id_t      _this_t::ARCH_ILLEGAL;
    constexpr _this_t::argument_set_t _this_t::DEFAULT_ARGUMENT_SET;


    void KernelConfigKey::setNodeId( KernelConfigKey::node_id_t const&
        SIXTRL_RESTRICT_REF node_id ) SIXTRL_NOEXCEPT
    {
        this->m_node_id = node_id;
    }

    void KernelConfigKey::setNodeId( const KernelConfigKey::c_node_id_t *const
        SIXTRL_RESTRICT ptr_node_id ) SIXTRL_NOEXCEPT
    {
        if( ( ptr_node_id != nullptr ) &&
            ( ptr_node_id != this->m_node_id.getCApiPtr() ) )
        {
            this->m_node_id = *( st::asCxxNodeId( ptr_node_id ) );
        }
    }

    void KernelConfigKey::setPlatformAndDeviceId(
        KernelConfigKey::platform_id_t const platform_id,
        KernelConfigKey::device_id_t const device_id ) SIXTRL_NOEXCEPT
    {
        this->m_node_id.setPlatformId( platform_id );
        this->m_node_id.setDeviceId( device_id );
    }

    void KernelConfigKey::setConfigStr(
        char const* SIXTRL_RESTRICT config_str )
    {
        if( ( config_str != nullptr ) &&
            ( std::strlen( config_str ) > _this_t::size_type{ 0 } ) )
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
        bool last_compare_equal = false;
        bool is_smaller_than = ( this->archId() < rhs.archId() );

        if( ( !is_smaller_than ) && ( this->archId() == rhs.archId() ) )
        {
            is_smaller_than = ( this->platformId() < rhs.platformId() );

            if( ( !is_smaller_than ) &&
                ( this->platformId() == rhs.platformId() ) )
            {
                is_smaller_than = ( this->deviceId() < rhs.deviceId() );

                if( !is_smaller_than )
                {
                    last_compare_equal = ( this->deviceId() == rhs.deviceId() );
                }
            }
        }

        if( ( !is_smaller_than ) && ( last_compare_equal ) )
        {
            is_smaller_than = ( this->purpose() < rhs.purpose() );

            if( ( !is_smaller_than ) && ( this->purpose() == rhs.purpose() ) )
            {
                is_smaller_than = ( this->variant() < rhs.variant() );

                if( !is_smaller_than )
                {
                    last_compare_equal = ( this->variant() == rhs.variant() );
                }
            }
        }

        if( ( !is_smaller_than ) && ( last_compare_equal ) )
        {
            is_smaller_than = ( this->m_config_str < rhs.m_config_str );

            if( ( !is_smaller_than ) &&
                ( this->m_config_str == rhs.m_config_str ) )
            {
                is_smaller_than = ( this->m_argument_set < rhs.m_argument_set );
            }
        }

        return is_smaller_than;
    }

    bool KernelConfigKey::isEqualExceptPurpose( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        bool is_equal = (
            ( this->archId() == rhs.archId() ) &&
            ( this->platformId() == rhs.platformId() ) &&
            ( this->deviceId() == rhs.deviceId() ) &&
            ( this->variant() == rhs.variant() ) &&
            ( this->argumentSet() == rhs.argumentSet() ) );

        if( is_equal )
        {
            is_equal = ( this->m_config_str.size() == rhs.m_config_str.size() );

            if( ( is_equal ) && ( !this->m_config_str.empty() ) )
            {
                is_equal = ( 0 == this->m_config_str.compare(
                    rhs.m_config_str ) );
            }
        }

        return is_equal;
    }

    int KernelConfigKey::compare( KernelConfigKey const&
        SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        int cmp_result = ( this->archId() < rhs.archId() )
            ? -1 : ( ( this->archId() > rhs.archId() ) ? +1 : 0 );

        if( cmp_result == 0 )
        {
            cmp_result = ( this->platformId() < rhs.platformId() )
                ? -1 : ( ( this->platformId() > rhs.platformId() ) ? +1 : 0 );
        }

        if( cmp_result == 0 )
        {
            cmp_result = ( this->deviceId() < rhs.deviceId() )
                ? -1 : ( ( this->deviceId() > rhs.deviceId() ) ? +1 : 0 );
        }

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

        if( cmp_result == 0 )
        {
            cmp_result = ( this->argumentSet() < rhs.argumentSet() )
                ? -1 : ( ( this->argumentSet() > rhs.argumentSet() ) ? +1 : 0 );
        }

        return cmp_result;
    }

    _this_t::status_t KernelConfigKey::reset(
        _this_t::arch_id_t const arch_id,
        _this_t::purpose_t const purpose,
        _this_t::variant_t const variant,
        _this_t::argument_set_t const argument_set,
        char const* SIXTRL_RESTRICT config_str )
    {
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
        this->setArgumentSet( argument_set );
        this->setConfigStr( config_str );

        return status;
    }

    _this_t::status_t KernelConfigKey::reset(
        const ::NS(NodeId) *const SIXTRL_RESTRICT ptr_node_id,
        _this_t::purpose_t const purpose,
        _this_t::variant_t const variant,
        _this_t::argument_set_t const argument_set,
        char const* SIXTRL_RESTRICT config_str )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _this_t::node_id_t const* ptr_cxx = st::asCxxNodeId( ptr_node_id );

        if( ptr_cxx != nullptr )
        {
            status = this->reset( *ptr_cxx, purpose, variant,
                                  argument_set, config_str );
        }

        return status;
    }
}

/* end: sixtracklib/common/control/kernel_config_key.cpp */
