#include "sixtracklib/common/control/arch_base.hpp"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <regex>
#include <string>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/debug_register.h"
#include "sixtracklib/common/control/arch_info.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    ArchBase::ArchBase( ArchBase::arch_id_t const arch_id,
        const char *const SIXTRL_RESTRICT config_str ) :
        st::ArchInfo( arch_id ), m_config_str()
    {
        this->doUpdateStoredConfigStr( config_str );
    }

    ArchBase::ArchBase( ArchBase::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT config_str ) :
        st::ArchInfo( arch_id ), m_config_str( config_str )
    {

    }

    bool ArchBase::doParseConfigStr(
        const char *const SIXTRL_RESTRICT config_str )
    {
        return this->doParseConfigStrArchBase( config_str );
    }

    void ArchBase::doUpdateStoredConfigStr(
        const char *const SIXTRL_RESTRICT config_str )
    {
        if( ( config_str != nullptr ) &&
            ( std::strlen( config_str ) > ArchBase::size_type{ 0 } ) )
        {
            this->m_config_str = config_str;
        }
        else
        {
            this->m_config_str.clear();
        }
    }

    /* ********************************************************************* */

    ArchDebugBase::ArchDebugBase( ArchDebugBase::arch_id_t const arch_id,
        ArchDebugBase::variant_t const variant,
        const char *const SIXTRL_RESTRICT config_str ) :
        st::ArchDebugBase::_arch_base_t( variant, arch_id, config_str ),
        m_local_debug_register( st::ARCH_DEBUGGING_REGISTER_EMPTY )
    {

    }

    ArchDebugBase::ArchDebugBase(
        ArchDebugBase::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF config_str ) :
        st::ArchDebugBase::_arch_base_t(
            st::ArchDebugBase::DEFAULT_VARIANT, arch_id, config_str ),
        m_local_debug_register( st::ARCH_DEBUGGING_REGISTER_EMPTY )
    {

    }

    ArchDebugBase::ArchDebugBase( ArchDebugBase::arch_id_t const arch_id,
        ArchDebugBase::variant_t const variant,
        std::string const& SIXTRL_RESTRICT_REF config_str ) :
        st::ArchDebugBase::_arch_base_t( variant, arch_id, config_str ),
        m_local_debug_register( st::ARCH_DEBUGGING_REGISTER_EMPTY )
    {

    }

    /* --------------------------------------------------------------------- */

    ArchDebugBase::status_t
    ArchDebugBase::doSwitchDebugMode( bool const enable_debug_mode )
    {
        using _this_t = st::ArchDebugBase;
        using variant_t = _this_t::variant_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        bool const current_debug_state = this->variantDebugMode();

        if( enable_debug_mode )
        {
            if( !current_debug_state )
            {
                variant_t const new_flags = _this_t::AddVariantFlags(
                    this->variant(), _this_t::VARIANT_DEBUG );

                status = this->doChangeVariantFlags( new_flags );
            }
            else
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }
        else
        {
            if( !current_debug_state )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
            else
            {
                variant_t const new_flags = _this_t::RemoveVariantFlags(
                    this->variant(), _this_t::VARIANT_DEBUG );

                status = this->doChangeVariantFlags( new_flags );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    ArchDebugBase::status_t ArchDebugBase::doChangeVariantFlags(
        ArchDebugBase::variant_t const variant_flags )
    {
        st::ArchDebugBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->variant() != variant_flags )
        {
            this->doSetVariantFlags( variant_flags );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    ArchDebugBase::status_t ArchDebugBase::evaluateDebugRegisterAfterUse()
    {
        ArchDebugBase::status_t status = this->doFetchDebugRegister(
            this->doGetPtrLocalDebugRegister() );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            if( ::NS(DebugReg_has_status_flags_set)(
                    *this->doGetPtrLocalDebugRegister() ) )
            {
                status = ::NS(DebugReg_get_stored_arch_status)(
                    *this->doGetPtrLocalDebugRegister() );
            }
            else if( ::NS(DebugReg_has_any_flags_set)(
                *this->doGetPtrLocalDebugRegister() ) )
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    ArchDebugBase::status_t ArchDebugBase::doSetDebugRegister(
        ArchDebugBase::debug_register_t const debug_register )
    {
        ArchDebugBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->doGetPtrLocalDebugRegister() != nullptr )
        {
            *this->doGetPtrLocalDebugRegister() = debug_register;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    ArchDebugBase::status_t ArchDebugBase::doFetchDebugRegister(
        ArchDebugBase::debug_register_t* SIXTRL_RESTRICT ptr_debug_register )
    {
        ArchDebugBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ptr_debug_register != nullptr )
        {
            if( ptr_debug_register != this->doGetPtrLocalDebugRegister() )
            {
                *ptr_debug_register = *this->doGetPtrLocalDebugRegister();
            }

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }
}

/* end: sixtracklib/common/control/arch_base.cpp */
