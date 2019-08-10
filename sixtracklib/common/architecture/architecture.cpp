#include "sixtracklib/common/architecture/architecture.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/generated/modules.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/arch_data.hpp"

#include "sixtracklib/common/architecture/arch_data.hpp"

namespace  st = SIXTRL_CXX_NAMESPACE;
using _this_t = st::Architectures;

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        static Architectures::init_flags_t
        Architectures_default_archs_get_initial_flags(
            Architectures::arch_id_t const arch_id ) SIXTRL_NOEXCEPT;

        static Architectures::init_flags_t Architecture_dummy_init_fn(
            Architectures::arch_id_t const arch_idArchitectures,
            ArchData* SIXTRL_RESTRICT ptr_arch_data );
    }

    Architectures::status_t Architectures::InitDefaultArchitectures(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures& SIXTRL_RESTRICT_REF archs )
    {
        using init_flags_t = _this_t::init_flags_t;
        using arch_id_t    = _this_t::arch_id_t;
        using size_t       = _this_t::size_type;
        using data_base_t  = _this_t::arch_data_base_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        status = st::ARCH_STATUS_SUCCESS;

        if( archs.checkLock( lock ) )
        {
            constexpr size_t NUM_DEFAULT_ARCHITECTURES = size_t{ 3 };

            constexpr arch_id_t DEFAULT_ARCH_IDS[ NUM_DEFAULT_ARCHITECTURES ] =
            {
                st::ARCHITECTURE_CPU, st::ARCHITECTURE_OPENCL,
                st::ARCHITECTURE_CUDA
            };

            constexpr char DEFAULT_ARCH_STRS[ NUM_DEFAULT_ARCHITECTURES ][ 8 ] =
            {
                { 'c',  'p',  'u',  '\0', '\0', '\0', '\0', '\0'  },
                { 'o',  'p',  'e',  'n',  'c',  'l',  '\0', '\0'  },
                { 'c',  'u',  'd',  'a',  '\0', '\0', '\0', '\0'  }
            };

            status = st::ARCH_STATUS_SUCCESS;

            for( size_t ii = 0u ; ii < NUM_DEFAULT_ARCHITECTURES ; ++ii )
            {
                arch_id_t const arch_id = DEFAULT_ARCH_IDS[ ii ];
                init_flags_t const init_flags =
                    st::Architectures_default_archs_get_initial_flags( arch_id );

                if( !archs.hasArchitecture( lock, arch_id ) )
                {
                    std::unique_ptr< data_base_t > ptr( new data_base_t(
                        arch_id, DEFAULT_ARCH_STRS[ ii ], init_flags,
                            &st::Architecture_dummy_init_fn ) );

                    status = archs.addArchitecture( lock, std::move( ptr ) );

                    if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                        ( archs.isEnabled( lock, arch_id ) ) )
                    {
                        status = archs.initialize( lock, arch_id );
                    }
                }

                if( status != st::ARCH_STATUS_SUCCESS ) break;
            }
        }

        return status;
    }


    bool Architectures::hasArchitecture(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        bool has_arch = false;

        if( ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
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
        char const* SIXTRL_RESTRICT arch_str ) const SIXTRL_NOEXCEPT
    {
        _this_t::arch_id_t arch_id = st::ARCHITECTURE_ILLEGAL;

        if( ( arch_str != nullptr ) && ( this->checkLock( lock ) ) )
        {
            auto it = this->m_arch_str_to_id.find( arch_str );
            if( it != this->m_arch_str_to_id.end() ) arch_id = it->second;
        }

        return arch_id;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool Architectures::hasArchStr(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        _this_t::arch_data_base_t const* ptr_arch_data_base =
            this->ptrArchDataBase( lock, arch_id );

        return ( ( ptr_arch_data_base != nullptr ) &&
                 ( ptr_arch_data_base->hasArchStr() ) );
    }

    std::string const& Architectures::archStr(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const
    {
        _this_t::arch_data_base_t const* ptr_arch_data_base =
            this->ptrArchDataBase( lock, arch_id );

        if( ptr_arch_data_base == nullptr )
        {
            throw std::runtime_error( "arch data base not available" );
        }

        return ptr_arch_data_base->archStr();
    }

    char const* Architectures::ptrArchStr(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        _this_t::arch_data_base_t const* ptr_arch_data_base =
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
                ptr_arch_data_base = it->second.get();
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
        using arch_id_t = _this_t::arch_id_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( ptr_arch_data_base.get() != nullptr ) &&
            ( ptr_arch_data_base->archId() == arch_id ) &&
            ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
            ( arch_id != st::ARCHITECTURE_NONE ) &&
            (  this->checkLock( lock ) ) )
        {
            SIXTRL_ASSERT( this->m_id_to_ptr_data_base.size() ==
                           this->m_stored_arch_ids.size() );

            SIXTRL_ASSERT( std::is_sorted( this->m_stored_arch_ids.begin(),
                this->m_stored_arch_ids.end() ) );

            auto it = this->m_id_to_ptr_data_base.find( arch_id );

            if( it != this->m_id_to_ptr_data_base.end() )
            {
                SIXTRL_ASSERT( ( !ptr_arch_data_base->hasArchStr() ) ||
                    ( ( ( this->m_arch_str_to_id.find(
                            ptr_arch_data_base->archStr() ) !=
                                this->m_arch_str_to_id.end() ) &&
                        ( this->m_arch_str_to_id.find(
                            ptr_arch_data_base->archStr() )->second
                                == arch_id ) ) ) );

                return status;
            }

            SIXTRL_ASSERT( ( !ptr_arch_data_base->hasArchStr() ) ||
                ( this->m_arch_str_to_id.find( ptr_arch_data_base->archStr() )
                    == this->m_arch_str_to_id.end() ) );

            SIXTRL_ASSERT( !std::binary_search( this->m_stored_arch_ids.begin(),
                this->m_stored_arch_ids.end(), arch_id ) );

            status = st::ARCH_STATUS_SUCCESS;

            if( ptr_arch_data_base->hasArchStr() )
            {
                auto res = this->m_arch_str_to_id.emplace(
                    std::make_pair( ptr_arch_data_base->archStr(), arch_id ) );

                if( !res.second ) status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                auto res = this->m_id_to_ptr_data_base.emplace(
                    std::make_pair( arch_id, std::move(
                        ptr_arch_data_base ) ) );

                if( res.second )
                {
                    arch_id_t const last_arch_id =
                        ( !this->m_stored_arch_ids.empty() )
                            ? this->m_stored_arch_ids.back() : arch_id_t{ 0 };

                    this->m_stored_arch_ids.push_back( arch_id );

                    if( last_arch_id > arch_id )
                    {
                        std::sort( this->m_stored_arch_ids.begin(),
                                   this->m_stored_arch_ids.end() );
                    }
                }
                else
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( ( this->m_id_to_ptr_data_base.size() ==
                    this->m_stored_arch_ids.size() ) &&
                  ( this->m_id_to_ptr_data_base.find( arch_id ) !=
                    this->m_id_to_ptr_data_base.end() ) &&
                  ( this->m_id_to_ptr_data_base.find(
                    arch_id )->second.get() != nullptr ) &&
                  ( std::is_sorted( this->m_stored_arch_ids.begin(),
                                    this->m_stored_arch_ids.end() ) ) ) );
        }

        return status;
    }

    namespace
    {
        Architectures::init_flags_t Architecture_dummy_init_fn(
            Architectures::arch_id_t const arch_id,
            ArchData* SIXTRL_RESTRICT ptr_arch_data )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            ( void )ptr_arch_data;

            Architectures::init_flags_t flags =
                st::Architectures_default_archs_get_initial_flags( arch_id );

            if( ( arch_id == st::ARCHITECTURE_CPU ) &&
                ( flags == st::ARCH_INIT_STATE_ENABLED ) )
            {
                flags = st::ARCH_INIT_STATE_AVAILABLE;
            }

            return flags;
        }

        Architectures::init_flags_t
        Architectures_default_archs_get_initial_flags(
            Architectures::arch_id_t const arch_id ) SIXTRL_NOEXCEPT
        {
            Architectures::init_flags_t init_flags = st::ARCH_INIT_STATE_NONE;

            switch( arch_id )
            {
                case st::ARCHITECTURE_CPU:
                {
                    init_flags = st::ARCH_INIT_STATE_ENABLED;
                    break;
                }

                case st::ARCHITECTURE_OPENCL:
                {
                    #if defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
                                 SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1

                    init_flags = st::ARCH_INIT_STATE_ENABLED;
                    #endif /* OpenCL */
                    break;
                }

                case st::ARCHITECTURE_CUDA:
                {
                    #if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
                                 SIXTRACKLIB_ENABLE_MODULE_CUDA == 1

                    init_flags = st::ARCH_INIT_STATE_ENABLED;
                    #endif /* OpenCL */
                    break;
                }

                default:
                {
                    init_flags = st::ARCH_INIT_STATE_ERROR;
                }
            };

            return init_flags;
        }
    }
}

/* end: sixtracklib/common/architecture/architecture.cpp */
