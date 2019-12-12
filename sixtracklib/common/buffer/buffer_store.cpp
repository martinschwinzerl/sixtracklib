#include "sixtracklib/common/buffer/buffer_store.hpp"

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <cstddef>
        #include <cstdint>
        #include <cstdlib>
        #include <memory>
    #else /* !defined( __cplusplus ) */
        #include <stdbool.h>
        #include <stddef.h>
        #include <stdint.h>
        #include <stdlib.h>
    #endif /* !defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"

    #if defined( __cplusplus )
        #include "sixtracklib/common/buffer.hpp"
    #endif /* defined( __cplusplus ) */

    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/buffer/buffer_toc.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    using _this_t = st::BufferStoreBase;

    _this_t::size_type constexpr _this_t::DEFAULT_BUFFER_CAPACITY;
    _this_t::flags_t   constexpr _this_t::DEFAULT_DATASTORE_FLAGS;
    _this_t::role_t    constexpr _this_t::USER_DEFINED_ROLE;
    _this_t::role_t    constexpr _this_t::NO_ROLE;

    /* ********************************************************************* */

    BufferStoreBase::BufferStoreBase( _this_t::size_type const buffer_capacity,
        _this_t::role_t const role, _this_t::flags_t const buffer_flags ) :
        m_ptr_cxx_buffer( nullptr ), m_ptr_c99_buffer( nullptr ),
        m_own_buffer( nullptr ), m_buffer_role( _this_t::USER_DEFINED_ROLE )
    {
        _this_t::stored_buffer_t ptr_new_buffer( new _this_t::buffer_t(
            buffer_capacity, role, buffer_flags ) );

        _this_t::status_t const status =
            this->doResetStoredCxxBufferByMoveBaseImpl(
                std::move( ptr_new_buffer ), role );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    BufferStoreBase::BufferStoreBase(
        _this_t::buffer_t* SIXTRL_RESTRICT cxx_buffer,
        _this_t::role_t const role, bool const take_ownership ) :
        m_ptr_cxx_buffer( nullptr ), m_ptr_c99_buffer( nullptr ),
        m_own_buffer( nullptr ), m_buffer_role( _this_t::USER_DEFINED_ROLE )
    {
        _this_t::status_t const status = this->doResetCxxBufferBaseImpl(
            cxx_buffer, role, take_ownership );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    BufferStoreBase::BufferStoreBase(
        _this_t::c_buffer_t* SIXTRL_RESTRICT c99_buffer,
        _this_t::role_t const role, bool const take_ownership,
        bool const delete_after_move ) :
        m_ptr_cxx_buffer( nullptr ), m_ptr_c99_buffer( nullptr ),
        m_own_buffer( nullptr ), m_buffer_role( _this_t::USER_DEFINED_ROLE )
    {
        _this_t::status_t const status = this->doResetC99BufferBaseImpl(
            c99_buffer, role, take_ownership, delete_after_move );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    BufferStoreBase::BufferStoreBase(
        _this_t::stored_buffer_t&& stored_ptr_buffer,
        _this_t::role_t const role ) :
        m_ptr_cxx_buffer( nullptr ), m_ptr_c99_buffer( nullptr ),
        m_own_buffer( nullptr ), m_buffer_role( _this_t::USER_DEFINED_ROLE )
    {
        _this_t::status_t const status =
            this->doResetStoredCxxBufferByMoveBaseImpl(
                std::move( stored_ptr_buffer ), role );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    BufferStoreBase::BufferStoreBase( _this_t::buffer_t&& cxx_buffer,
        _this_t::role_t const role ) :
        m_ptr_cxx_buffer( nullptr ), m_ptr_c99_buffer( nullptr ),
        m_own_buffer( nullptr ), m_buffer_role( _this_t::USER_DEFINED_ROLE )
    {
        _this_t::status_t const status = this->doResetCxxBufferByMoveBaseImpl(
            std::move( cxx_buffer ), role );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    BufferStoreBase::BufferStoreBase(
        BufferStoreBase const& other ) :
        m_ptr_cxx_buffer( nullptr ), m_ptr_c99_buffer( nullptr ),
        m_own_buffer( nullptr ), m_buffer_role( other.m_buffer_role )
    {
        if( other.owns_buffer() )
        {
            SIXTRL_ASSERT( other.m_own_buffer.get() != nullptr );
            this->m_own_buffer.reset(
                new st::Buffer( *other.m_own_buffer.get() ) );

            this->m_ptr_cxx_buffer = this->m_own_buffer.get();
            this->m_ptr_c99_buffer = this->m_own_buffer->getCApiPtr();
        }
        else
        {
            this->m_own_buffer.reset( nullptr );
            this->m_ptr_cxx_buffer = other.m_ptr_cxx_buffer;
            this->m_ptr_c99_buffer = other.m_ptr_c99_buffer;
        }
    }

    BufferStoreBase::BufferStoreBase(
        BufferStoreBase&& other ) SIXTRL_NOEXCEPT:
        m_ptr_cxx_buffer( std::move( other.m_ptr_cxx_buffer ) ),
        m_ptr_c99_buffer( std::move( other.m_ptr_c99_buffer ) ),
        m_own_buffer( std::move( other.m_own_buffer ) ),
        m_buffer_role( std::move( other.m_buffer_role ) )
    {
        if( other.owns_buffer() )
        {
            SIXTRL_ASSERT( other.m_own_buffer.get() != nullptr );
            this->m_own_buffer.reset(
                new st::Buffer( *other.m_own_buffer.get() ) );

            this->m_ptr_cxx_buffer = this->m_own_buffer.get();
            this->m_ptr_c99_buffer = this->m_own_buffer->getCApiPtr();
        }
        else
        {
            this->m_own_buffer.reset( nullptr );
            this->m_ptr_cxx_buffer =  other.m_ptr_cxx_buffer;
            this->m_ptr_c99_buffer =  other.m_ptr_c99_buffer;
        }
    }

    BufferStoreBase& BufferStoreBase::operator=(
        BufferStoreBase const& rhs )
    {
        if( this != &rhs )
        {
            if( rhs.owns_buffer() )
            {
                SIXTRL_ASSERT( rhs.m_own_buffer.get() != nullptr );

                this->m_own_buffer.reset(
                    new st::Buffer( *rhs.m_own_buffer.get() ) );

                this->m_ptr_cxx_buffer = this->m_own_buffer.get();
                this->m_ptr_c99_buffer = this->m_own_buffer->getCApiPtr();
            }
            else
            {
                this->m_own_buffer.reset( nullptr );
                this->m_ptr_cxx_buffer = rhs.m_ptr_cxx_buffer;
                this->m_ptr_c99_buffer = rhs.m_ptr_c99_buffer;
            }

            this->m_buffer_role = rhs.m_buffer_role;
        }

        return *this;
    }

    BufferStoreBase& BufferStoreBase::operator=(
        BufferStoreBase&& rhs ) SIXTRL_NOEXCEPT
    {
        if( this != &rhs )
        {
            this->m_own_buffer     = std::move( rhs.m_own_buffer );
            this->m_ptr_cxx_buffer = std::move( rhs.m_ptr_cxx_buffer );
            this->m_ptr_c99_buffer = std::move( rhs.m_ptr_c99_buffer );
            this->m_buffer_role    = std::move( rhs.m_buffer_role );
        }

        return *this;
    }

    _this_t::buffer_t const& BufferStoreBase::cxx_buffer() const SIXTRL_NOEXCEPT
    {
        if( this->m_ptr_cxx_buffer == nullptr )
        {
            throw std::runtime_error( "doesn't have c++ buffer" );
        }

        return *this->m_ptr_cxx_buffer;
    }

    _this_t::buffer_t& BufferStoreBase::cxx_buffer() SIXTRL_NOEXCEPT
    {
        return const_cast< _this_t::buffer_t& >( static_cast< _this_t const& >(
            *this ).cxx_buffer() );
    }

    void BufferStoreBase::clear() SIXTRL_NOEXCEPT
    {
        this->doClear();
    }

    _this_t::status_t BufferStoreBase::reset(
        _this_t::size_type const buffer_capacity,
        _this_t::role_t const role, _this_t::flags_t const buffer_flags )
    {
        _this_t::stored_buffer_t new_buffer( new _this_t::buffer_t(
            buffer_capacity, buffer_flags ) );

        return this->doResetStoredCxxBufferByMove(
            std::move( new_buffer ), role );
    }

    _this_t::status_t BufferStoreBase::reset(
        _this_t::buffer_t* SIXTRL_RESTRICT cxx_buffer,
        _this_t::role_t const role, bool const take_ownership )
    {
        return this->doResetCxxBuffer( cxx_buffer, role, take_ownership );
    }

    _this_t::status_t BufferStoreBase::reset(
        _this_t::c_buffer_t* SIXTRL_RESTRICT _buffer,
        _this_t::role_t const role, bool const take_ownership,
            bool const delete_ptr_after_move )
    {
        return this->doResetC99Buffer(
            _buffer, role, take_ownership, delete_ptr_after_move );
    }

    _this_t::status_t BufferStoreBase::reset(
        _this_t::stored_buffer_t&& stored_ptr_buffer,
        _this_t::role_t const role )
    {
        return this->doResetStoredCxxBufferByMove(
            std::move( stored_ptr_buffer ), role );
    }

    _this_t::status_t BufferStoreBase::reset(
        _this_t::buffer_t&& _buffer, _this_t::role_t const role )
    {
        return this->doResetCxxBufferByMove( std::move( cxx_buffer ), role );
    }

    /* --------------------------------------------------------------------- */

    void BufferStoreBase::doClear()
    {
        this->doClearBaseImpl();
    }

    _this_t::status_t BufferStoreBase::doResetCxxBuffer(
        _this_t::buffer_t* SIXTRL_RESTRICT cxx_buffer,
        _this_t::role_t const role, bool const take_ownership )
    {
        return this->doResetCxxBufferBaseImpl(
            cxx_buffer, role, take_ownership );
    }

    _this_t::status_t BufferStoreBase::doResetStoredCxxBufferByMove(
        _this_t::stored_buffer_t&& stored_ptr_buffer,
        _this_t::role_t const role )
    {
        return this->doResetStoredCxxBufferByMoveBaseImpl(
            std::move( stored_ptr_buffer ), role );
    }

    _this_t::status_t BufferStoreBase::doResetCxxBufferByMove(
        _this_t::buffer_t&& cxx_buffer, _this_t::role_t const role )
    {
        return this->doResetCxxBufferByMoveBaseImpl(
            std::move( cxx_buffer ), role );
    }

    _this_t::status_t BufferStoreBase::doResetC99Buffer(
        _this_t::c_buffer_t* SIXTRL_RESTRICT c99_buffer,
        _this_t::role_t const role, bool const take_ownership,
        bool const delete_ptr_after_move )
    {
        return this->doResetC99BufferBaseImpl(
            c99_buffer, role, take_ownership, delete_ptr_after_move );
    }

    /* --------------------------------------------------------------------- */

    void BufferStoreBase::doClearBaseImpl() SIXTRL_NOEXCEPT
    {
        this->m_ptr_cxx_buffer = nullptr;
        this->m_ptr_c99_buffer = nullptr;
        this->m_own_buffer.reset( nullptr );
        this->m_buffer_role = _this_t::NO_ROLE;
    }

    _this_t::status_t BufferStoreBase::doResetCxxBufferBaseImpl(
        _this_t::buffer_t* SIXTRL_RESTRICT _buffer, _this_t::role_t const role,
            bool const take_ownership )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( _buffer != nullptr ) && ( this->m_ptr_cxx_buffer != _buffer ) )
        {
            this->m_ptr_cxx_buffer = _buffer;
            this->m_ptr_c99_buffer = _buffer->getCApiPtr();

            if( take_ownership )
            {
                this->m_own_buffer.reset( _buffer );
            }
            else if( this->m_own_buffer.get() != nullptr )
            {
                this->m_own_buffer.reset( nullptr );
            }

            status = st::ARCH_STATUS_SUCCESS;
        }
        else if( ( _buffer != nullptr ) && ( role == this->m_buffer_role ) &&
                 ( _buffer == this->m_ptr_cxx_buffer ) )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _this_t::status_t BufferStoreBase::doResetStoredCxxBufferByMoveBaseImpl(
        _this_t::stored_buffer_t&& stored_ptr_buffer,
        _this_t::role_t const role )
    {
        this->m_own_buffer = std::move( stored_ptr_buffer );
        this->m_ptr_cxx_buffer = this->m_own_buffer.get();

        this->m_ptr_c99_buffer = ( this->m_own_buffer.get() != nullptr )
            ? this->m_own_buffer->getCApiPtr() : nullptr;

        this->m_buffer_role = role;
        return st::ARCH_STATUS_SUCCESS;
    }

    _this_t::status_t BufferStoreBase::doResetCxxBufferByMoveBaseImpl(
        _this_t::buffer_t&& cxx_buffer, _this_t::role_t const role )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( &cxx_buffer != this->m_ptr_cxx_buffer )
        {
            this->m_own_buffer.reset( new _this_t::buffer_t(
                std::move( cxx_buffer ) ) );

            this->m_ptr_cxx_buffer = this->m_own_buffer.get();
            SIXTRL_ASSERT( this->m_own_buffer.get() != nullptr );

            this->m_ptr_c99_buffer = this->m_own_buffer->getCApiPtr();
            this->m_buffer_role = role;

            status = st::ARCH_STATUS_SUCCESS;
        }
        else if( ( &cxx_buffer == this->m_ptr_cxx_buffer ) &&
                 ( role == this->m_buffer_role ) )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _this_t::status_t BufferStoreBase::doResetC99BufferBaseImpl(
        _this_t::c_buffer_t* SIXTRL_RESTRICT _buffer,
        _this_t::role_t const role, bool const take_ownership,
        bool const delete_after_move )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        using buffer_t = _this_t::buffer_t;

        if( ( _buffer != nullptr ) && ( this->m_ptr_c99_buffer != _buffer ) )
        {
            if( take_ownership )
            {
                this->m_own_buffer =
                buffer_t::MAKE_FROM_CBUFFER_AND_TAKE_OWNERSHIP(
                    _buffer, delete_after_move );

                this->m_ptr_cxx_buffer = this->m_own_buffer.get();

                if( this->m_own_buffer.get() != nullptr )
                {
                    this->m_ptr_c99_buffer = this->m_own_buffer->getCApiPtr();
                }

                if( this->m_ptr_c99_buffer != nullptr )
                {
                    this->m_buffer_toc.reset( this->m_ptr_c99_buffer );
                }
            }
            else
            {
                this->m_ptr_c99_buffer = c99_buffer;
                this->m_ptr_cxx_buffer = nullptr;
                this->m_own_buffer.reset( nullptr );
            }

            this->m_buffer_role = role;
            status = st::ARCH_STATUS_SUCCESS;
        }
        else if( ( _buffer != nullptr ) && ( this->m_buffer_role == role ) &&
                 ( this->m_ptr_c99_buffer == _buffer ) )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
