#include "sixtracklib/common/architecture/architecture.hpp"

#include <cstddef>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/arch_data.hpp"

#include "sixtracklib/common/architecture/arch_data.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    bool Architectures::hasArchitecture(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {


        bool has_arch = false;

        if( ( arch_id != _this_t::ARCHITECTURE_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_id_to_ptr_data_base.find( arch_id );

            has_arch = ( ( it != this->m_id_to_ptr_data_base.end() ) &&
                         ( it->second.get() != nullptr ) );
        }

        return has_arch;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    Architectures::arch_id_t Architectures::archId(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::char const* SIXTRL_RESTRICT arch_str ) const SIXTRL_NOEXCEPT
    {
        st::Architectures::arch_id_t arch_id = st::ARCHITECTURE_ILLEGAL;

        if( ( arch_str != nullptr ) && ( this->checkLock( lock ) ) )
        {
            auto it = this->m_arch_str_to_id_map_t.find( arch_str );

            if( it != this->m_arch_str_to_id_map_t.end() )
            {
                arch_id = it->second;
            }
        }

        return arch_id;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool Architectures::hasArchStr(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        st::Architectures::arch_data_base_t const* ptr_arch_data_base =
            this->ptrArchDataBase( lock, arch_id );

        return ( ( ptr_arch_data_base != nullptr ) &&
                 ( ptr_arch_data_base->hasArchStr() ) );
    }

    std::string const& Architectures::archStr(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const
    {
        st::Architectures::arch_data_base_t const* ptr_arch_data_base =
            this->ptrArchDataBase( lock, arch_id );

        return ( ( ptr_arch_data_base != nullptr ) &&
                 ( ptr_arch_data_base->hasArchStr() ) )
            ? ptr_arch_data_base->archStr() : std::string{};
    }

    char const* Architectures::ptrArchStr(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        st::Architectures::arch_data_base_t const* ptr_arch_data_base =
            this->ptrArchDataBase( lock, arch_id );

        return ( ( ptr_arch_data_base != nullptr ) &&
                 ( ptr_arch_data_base->hasArchStr() ) )
            ? ptr_arch_data_base->ptrArchStr() : nullptr;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    Architectures::arch_data_base_t const*
    Architectures::ptrArchDataBase(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::Architectures;

        _this_t::arch_data_base_t const* ptr_arch_data_base = nullptr;

        if( ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_id_to_ptr_data_base.find( arch_id );

            if( it != this->m_id_to_ptr_data_base.end() )
            {
                ptr_arch_data_base = ptr_arch_data_base->second.get();
            }
        }

        return ptr_arch_data_base;
    }

    /* --------------------------------------------------------------------- */

    Architectures::status_t Architectures::doAddArchitecture(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id,
        Architectures::ptr_arch_data_base_t&& ptr_arch_data_base )
    {
        return this->doAddArchitectureBaseImpl(
            lock, arch_id, std::move( ptr_arch_data_base ) );
    }

    Architectures::status_t Architectures::doAddArchitectureBaseImpl(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id,
        Architectures::ptr_arch_data_base_t&& ptr_arch_data_base )
    {
        using _this_t = st::Architectures;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
            ( ptr_arch_data_base.get() != nullptr ) &&
            ( ptr_arch_data_base->archId() == arch_id ) &&
            ( !this->hasArchitecture( lock, arch_id ) ) )
        {
            if( ptr_arch_data_base->hasArchStr() )
            {
                if( this->hasArchitecture(
                        lock, ptr_arch_data_base->archStr() ) )
                {
                    return status;
                }

                auto res = this->m_arch_str_to_id_map_t.emplace(
                    std::make_pair( ptr_arch_data_base->archStr(), arch_id ) );

                if( res.second )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
            else
            {
               status = st::ARCH_STATUS_SUCCESS;
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                auto res = this->m_id_to_ptr_data_base.emplace(
                    std::make_pair( arch_id, std::move(
                        ptr_arch_data_base ) ) );

                if( !res.second )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }
        }

        return status;
    }
}

/* end: sixtracklib/common/architecture/architecture.cpp */
