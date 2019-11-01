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
#include "sixtracklib/common/internal/stl_buffer_helper.hpp"
#include "sixtracklib/common/generated/modules.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/arch_data.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        using _this_t = st::Architectures;

        static _this_t::init_flags_t
        Architectures_default_archs_get_initial_flags(
            _this_t::arch_id_t const arch_id ) SIXTRL_NOEXCEPT;

        static _this_t::init_flags_t Architecture_dummy_init_fn(
            _this_t::arch_id_t const arch_idArchitectures,
            ArchData* SIXTRL_RESTRICT ptr_arch_data );
    }

    Architectures::status_t Architectures::init_default_architectures(

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

                if( !archs.has_arch( lock, arch_id ) )
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

    /* --------------------------------------------------------------------- */

    bool Architectures::has_arch(
        _this_t::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        bool has_arch = false;

        if( arch_id != st::ARCHITECTURE_ILLEGAL )
        {
            auto it = this->m_id_to_ptr_data_base.find( arch_id );
            has_arch = ( ( it != this->m_id_to_ptr_data_base.end() ) &&
                         ( it->second.get() != nullptr ) );
        }

        return has_arch;
    }

    bool Architectures::has_arch_str(
        _this_t::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        bool has_arch_str = false;

        if( arch_id != st::ARCHITECTURE_ILLEGAL )
        {
            auto it = this->m_id_to_ptr_data_base.find( arch_id );
            has_arch_str = ( ( it != this->m_id_to_ptr_data_base.end() ) &&
                             ( it->second.get() != nullptr ) &&
                             ( it->second->has_arch_str() ) );
        }

        return has_arch_str;
    }

    std::string const& Architectures::architecture_str(
        _this_t::arch_id_t const arch_id ) const
    {
        if( arch_id != st::ARCHITECTURE_ILLEGAL )
        {
            auto it = this->m_id_to_ptr_data_base.find( arch_id );

            if( ( it != this->m_id_to_ptr_data_base.end() ) &&
                ( it->second.get() != nullptr ) &&
                ( it->second->has_arch_str() ) )
            {
                return it->architecture_str();
            }
        }

        throw std::runtime_error( "Unable to retrieve architecture str" );
    }

    char const* Architectures::ptr_architecture_cstr(
        _this_t::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        char const* ptr_arch_cstr = nullptr;

        if( arch_id != st::ARCHITECTURE_ILLEGAL )
        {
            auto it = this->m_id_to_ptr_data_base.find( arch_id );

            if( ( it != this->m_id_to_ptr_data_base.end() ) &&
                ( it->second.get() != nullptr ) &&
                ( it->second->has_arch_str() ) )
            {
                ptr_arch_cstr = it->ptr_architecture_cstr();
            }
        }

        return ptr_arch_cstr;
    }

    /* --------------------------------------------------------------------- */

    _this_t::arch_id_t Architectures::architecture_id(
        std::string const& SIXTRL_RESTRICT_REF arch_str ) const SIXTRL_NOEXCEPT
    {
        _this_t::arch_id_t arch_id = st::ARCHITECTURE_ILLEGAL;

        if( !arch_str.empty() != nullptr )
        {
            auto it = this->m_arch_str_to_id.find( arch_str );
            if( it != this->m_arch_str_to_id.end() ) arch_id = it->second;
        }

        return arch_id;
    }

    _this_t::arch_id_t Architectures::architecture_id(
        char const* SIXTRL_RESTRICT arch_str ) const SIXTRL_NOEXCEPT
    {
        return ( arch_str != nullptr )
            ? this->architecture_id( std::string{ arch_str } )
            : st::ARCHITECTURE_ILLEGAL;
    }

    _this_t::arch_id_t Architectures::architecture_id_by_index(
        _this_t::size_type const index ) const SIXTRL_NOEXCEPT
    {
        return ( this->m_stored_arch_ids.size() > index )
            ? this->m_stored_arch_ids[ index ] : st::ARCHITECTURE_ILLEGAL;
    }

    _this_t::arch_id_t const*
    Architectures::architecture_ids_begin() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_stored_arch_ids.empty() )
            ? this->m_stored_arch_ids.data() : nullptr;
    }

    _this_t::arch_id_t const*
    Architectures::architecture_ids_end() const SIXTRL_NOEXCEPT
    {
        _this_t::arch_id_t const* ptr_end = this->architecture_ids_begin();

        if( ptr_end != nullptr )
        {
            SIXTRL_ASSERT( !this->m_stored_arch_ids.empty() );
            std::advance( ptr_end, this->m_stored_arch_ids.size() );
        }

        return ptr_end;
    }

    /* --------------------------------------------------------------------- */

    _this_t::arch_data_base_t const*
    Architectures::ptr_const_architecture_data_base(
        _this_t::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        _this_t::arch_data_base_t const* ptr_arch_data_base = nullptr;

        if( arch_id != st::ARCHITECTURE_ILLEGAL )
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

    _this_t::size_type Architectures::num_architectures() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_stored_arch_ids.size() ==
                       this->m_id_to_ptr_data_base.size() );

        return this->m_stored_arch_ids.size();
    }

    _this_t::status_t Architectures::add_architecture(
        _this_t::ptr_arch_data_base_t&& ptr_arch_data )
    {
        return this->doAddArchitecture( std::move( ptr_arch_data ) );
    }

    /* --------------------------------------------------------------------- */

    bool Architectures::has_handle(
        _this_t::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr_data_base = this->ptr_architecture_data_base( arch_id );
        return ( ( ptr_data_base != nullptr ) &&
                 ( ptr_data_base->has_handle() ) );
    }

    _this_t::lib_handle_t Architectures::lib_handle(
        _this_t::arch_id_t const arch_id )
    {
        auto ptr_data_base = this->ptr_architecture_data_base( arch_id );
        if( ptr_data_base == nullptr )
        {
            throw std::runtime_error( "unable to get architecture data" );
        }

        return ptr_data_base->lib_handle();
    }

    bool Architectures::is_enabled(
        _this_t::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr_data_base = this->ptr_architecture_data_base( arch_id );
        return ( ( ptr_data_base != nullptr ) &&
                 ( ptr_data_base->is_enabled() ) );
    }

    bool Architectures::is_activated(
        _this_t::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr_data_base = this->ptr_architecture_data_base( arch_id );
        return ( ( ptr_data_base != nullptr ) &&
                 ( ptr_data_base->is_activated() ) );
    }

    bool Architectures::is_available(
        _this_t::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr_data_base = this->ptr_architecture_data_base( arch_id );
        return ( ( ptr_data_base != nullptr ) &&
                 ( ptr_data_base->is_available() ) );
    }

    bool Architectures::is_shutdown(
        _this_t::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr_data_base = this->ptr_architecture_data_base( arch_id );
        return ( ( ptr_data_base != nullptr ) &&
                 ( ptr_data_base->is_shutdown() ) );
    }

    _this_t::init_flags_t Architectures::init_flags(
        _this_t::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr_data_base = this->ptr_architecture_data_base( arch_id );
        return ( ptr_data_base != nullptr )
            ? ptr_data_base->init_flags() : st::ARCH_INIT_STATE_ERROR;
    }

    _this_t::status_t Architectures::initialize(
        _this_t::arch_id_t const arch_id )
    {
        auto ptr_data_base = this->ptr_architecture_data_base( arch_id );
        return ( ptr_data_base != nullptr )
            ? ptr_data_base->initialize( arch_id )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    _this_t::status_t Architectures::shutdown(
        _this_t::arch_id_t const arch_id )
    {
        auto ptr_data_base = this->ptr_architecture_data_base( arch_id );
        return ( ptr_data_base != nullptr )
            ? ptr_data_base->shutdown( arch_id )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* --------------------------------------------------------------------- */

    _this_t::status_t Architectures::doAddArchitecture(
        _this_t::arch_id_t const arch_id,
        _this_t::ptr_arch_data_base_t&& ptr_arch_data_base )
    {
        return this->doAddArchitectureBaseImpl(
            arch_id, std::move( ptr_arch_data_base ) );
    }

    _this_t::status_t Architectures::doAddArchitectureBaseImpl(
        _this_t::arch_id_t const arch_id,
        _this_t::ptr_arch_data_base_t&& ptr_arch_data_base )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( ptr_arch_data_base.get() != nullptr ) &&
            ( ptr_arch_data_base->architecture_id() == arch_id ) &&
            ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
            ( arch_id != st::ARCHITECTURE_NONE ) )
        {
            SIXTRL_ASSERT( this->m_id_to_ptr_data_base.size() ==
                           this->m_stored_arch_ids.size() );

            auto it = this->m_id_to_ptr_data_base.find( arch_id );

            if( it != this->m_id_to_ptr_data_base.end() )
            {
                SIXTRL_ASSERT(
                    ( !ptr_arch_data_base->has_arch_str() ) ||
                    ( st::Map_has_value_for_key( this->m_arch_str_to_id,
                            ptr_arch_data_base->architecture_str(),
                                arch_id ) ) );

                return status;
            }

            SIXTRL_ASSERT( ( !ptr_arch_data_base->has_arch_str() ) ||
                ( !st::Map_has_key( this->m_arch_str_to_id,
                        ptr_arch_data_base->architecture_str() ) ) );

            SIXTRL_ASSERT( !st::Vector_sorted_has_value(
                this->m_stored_arch_ids, arch_id, true ) );

            status = st::ARCH_STATUS_SUCCESS;

            if( ptr_arch_data_base->has_arch_str() )
            {
                auto res = this->m_arch_str_to_id.emplace(
                    std::make_pair( ptr_arch_data_base->architecture_str(), arch_id ) );

                if( !res.second ) status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                auto res = this->m_id_to_ptr_data_base.emplace(
                    std::make_pair( arch_id, std::move(
                        ptr_arch_data_base ) ) );

                if( res.second )
                {
                    status = st::Vector_add_sorted( this->m_stored_arch_ids,
                        arch_id, _this_t::arch_id_t{ 0 }, true );
                }
                else
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( ( this->m_id_to_ptr_data_base.size() ==
                    this->m_stored_arch_ids.size() ) &&
                  ( st::Map_has_key( this->m_id_to_ptr_data_base, arch_id ) ) &&
                  ( !st::Map_has_value_for_key( this->m_id_to_ptr_data_base,
                        arch_id, != nullptr ) ) &&
                  ( std::is_sorted( this->m_stored_arch_ids.begin(),
                                    this->m_stored_arch_ids.end() ) ) ) );
        }

        return status;
    }

    namespace
    {
        _this_t::init_flags_t Architecture_dummy_init_fn(
            _this_t::arch_id_t const arch_id,
            ArchData* SIXTRL_RESTRICT ptr_arch_data )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            ( void )ptr_arch_data;

            _this_t::init_flags_t flags =
                st::Architectures_default_archs_get_initial_flags( arch_id );

            if( ( arch_id == st::ARCHITECTURE_CPU ) &&
                ( flags == st::ARCH_INIT_STATE_ENABLED ) )
            {
                flags = st::ARCH_INIT_STATE_AVAILABLE;
            }

            return flags;
        }

        _this_t::init_flags_t Architectures_default_archs_get_initial_flags(
            _this_t::arch_id_t const arch_id ) SIXTRL_NOEXCEPT
        {
            _this_t::init_flags_t init_flags = st::ARCH_INIT_STATE_NONE;

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
