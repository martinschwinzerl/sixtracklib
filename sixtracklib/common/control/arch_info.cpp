#include "sixtracklib/common/control/arch_info.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"
#include "sixtracklib/common/control/definitions.h"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    ArchInfo::status_t ArchInfo_sanitize_arch_str(
        std::string& SIXTRL_RESTRICT_REF arch_str )
    {
        st::ArchInfo::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !arch_str.empty() )
        {
            std::transform( arch_str.begin(), arch_str.end(), arch_str.begin(),
                            ::tolower );

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    ArchInfo::status_t ArchInfo_sanitize_arch_str(
        char* SIXTRL_RESTRICT arch_str,
        st::arch_size_t const arch_str_capacity )
    {
        st::ArchInfo::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( arch_str != nullptr ) &&
            ( arch_str_capacity > size_t{ 0 } ) )
        {
            std::transform( arch_str, arch_str + arch_str_capacity,
                            arch_str, ::tolower );

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    ArchInfo::ArchInfo( ArchInfo::arch_id_t const arch_id ) :
        m_arch_str(), m_arch_id( st::ARCHITECTURE_ILLEGAL )
    {
        st::arch_status_t const status = this->doSetArchId( arch_id );
        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    ArchInfo::arch_id_t ArchInfo::archId() const SIXTRL_NOEXCEPT
    {
        return this->m_arch_id;
    }

    bool ArchInfo::hasArchStr() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_arch_str.empty() );
    }

    std::string const& ArchInfo::archStr() const SIXTRL_NOEXCEPT
    {
        return this->m_arch_str;
    }

    char const* ArchInfo::ptrArchStr() const SIXTRL_NOEXCEPT
    {
        return this->m_arch_str.c_str();
    }

    bool ArchInfo::isArchCompatibleWith(
        ArchInfo::arch_id_t const other_arch_id ) const SIXTRL_NOEXCEPT
    {
        return this->isArchIdenticalTo( other_arch_id );
    }

    bool ArchInfo::isArchCompatibleWith(
        ArchInfo const& SIXTRL_RESTRICT other ) const SIXTRL_NOEXCEPT
    {
        return this->isArchCompatibleWith( other.archId() );
    }

    bool ArchInfo::isArchIdenticalTo(
         ArchInfo::arch_id_t const other_arch_id ) const SIXTRL_NOEXCEPT
    {
        return ( this->archId() == other_arch_id );
    }

    bool ArchInfo::isArchIdenticalTo(
            ArchInfo const& SIXTRL_RESTRICT rhs ) const SIXTRL_NOEXCEPT
    {
        return this->isArchIdenticalTo( rhs.archId() );
    }

    ArchInfo::status_t ArchInfo::reset( ArchInfo::arch_id_t const arch_id )
    {
        return this->doSetArchId( arch_id );
    }

    ArchInfo::status_t ArchInfo::reset()
    {
        this->m_arch_str.clear();
        this->m_arch_id = st::ARCHITECTURE_ILLEGAL;
        return st::ARCH_STATUS_SUCCESS;
    }

    ArchInfo::status_t ArchInfo::doSetArchId( ArchInfo::arch_id_t const aid )
    {
        using lock_t = st::Architectures::lock_t;
        st::ArchInfo::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( aid == this->m_arch_id )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }
        else if( aid == st::ARCHITECTURE_NONE )
        {
            this->m_arch_str.clear();
            this->m_arch_id = aid;

            status = st::ARCH_STATUS_SUCCESS;
        }
        else
        {
            lock_t const lock( *st::Architectures_get().lockable() );

            if( ( aid != st::ARCHITECTURE_ILLEGAL ) &&
                ( st::Architectures_get_const().hasArchitecture( lock, aid ) ) &&
                ( st::Architectures_get_const().hasArchStr( lock, aid ) ) )
            {
                this->m_arch_id  = aid;
                this->m_arch_str = st::Architectures_get().archStr( lock, aid );
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }
}

/* end: sixtracklib/common/control/arch_info.cpp */
