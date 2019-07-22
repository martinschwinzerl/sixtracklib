#include "sixtracklib/architecture/arch_state_base.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string>

#if defined( __unix__ ) || ( defined( __APPLE__ ) && defined( __MACH__ ) )
    #include <unistd.h>
#endif /* include unistd.h */

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    ArchData::ArchData(
        ArchData::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF arch_name_str,
        ArchData::init_flags_t const arch_init_flags,
        ArchData::init_arch_fn_t init_arch_fn,
        ArchData::shutdown_arch_fn_t shutdown_arch_fn ) :
        m_arch_id( arch_id ), m_arch_name( arch_name_str ),
        m_init_fn( init_arch_fn ), m_shutdown_fn( shutdown_arch_fn ),
        #if defined( _POSIX_VERSION )
        m_lib_handle( nullptr ),
        #elif defined( __WIN32__ ) || defined( _WIN32 )
        m_lib_handle( nullptr ),
        #else
        m_lib_handle(),
        #endif
        m_arch_id( arch_id ),
        m_init_state( arch_init_flags )
    {

    }

    ArchData::ArchData(
        ArchData::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT arch_name_str,
        ArchData::init_flags_t const arch_init_flags,
        ArchData::init_arch_fn_t init_arch_fn,
        ArchData::shutdown_arch_fn_t shutdown_arch_fn ) :
        m_arch_id( arch_id ), m_arch_name(), m_init_fn( init_arch_fn ),
        m_shutdown_fn( shutdown_arch_fn ),
        #if defined( _POSIX_VERSION )
        m_lib_handle( nullptr ),
        #elif defined( __WIN32__ ) || defined( _WIN32 )
        m_lib_handle( nullptr ),
        #else
        m_lib_handle(),
        #endif
        m_arch_id( st::ARCHITECTURE_NONE ),
        m_init_state( arch_init_flags )
    {
        this->doSetArchStr( arch_name_str );
    }

    ArchData::~ArchData()
    {
        if( ( this->m_shutdown_fn != nullptr ) && ( this->isActivated() ) )
        {
            this->m_shutdown_fn( this->archId(), this );
        }
    }

    /* ----------------------------------------------------------------- */

    ArchData::status_t ArchData::initialize()
    {
        using _this_t = st::ArchData;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->m_init_fn != nullptr ) &&
            ( this->m_init_state == st::ARCH_INIT_STATE_ENABLED ) )
        {
            _this_t::init_flags_t const new_flags = this->m_init_fn(
                this->archId(), this );

            if( new_flags != st::ARCH_INIT_STATE_ERROR )
            {
                this->m_init_state( new_flags );
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    ArchData::status_t ArchData::shutdown()
    {
        using _this_t = st::ArchData;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->m_shutdown_fn != nullptr )
        {
            _this_t::init_flags_t const new_flags = this->m_shutdown_fn(
                this->archId(), this );

            if( new_flags != st::ARCH_INIT_STATE_ERROR )
            {
                this->m_init_state( new_flags );
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* ----------------------------------------------------------------- */

    ArchData::status_t ArchData::doSetArchStr(
        char const* SIXTRL_RESTRICT arch_str )
    {
        ArchData::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->m_init_state == st::ARCH_INIT_STATE_ENABLED ) ||
            ( this->m_init_state == st::ARCH_INIT_STATE_NONE ) )
        {
            status = st::ARCH_STATUS_SUCCESS:

            if( ( arch_str != nullptr ) &&
                ( std::strlen( arch_str ) > std::size_t{ 0 } ) )
            {
                this->m_arch_str = arch_str;
            }
            else
            {
                this->m_arch_str.clear();
            }
        }

        return st::ARCH_STATUS_SUCCESS;
    }
}

/* end: sixtracklib/common/architecture/arch_state_base.cpp */
