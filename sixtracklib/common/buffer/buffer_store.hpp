#ifndef SIXTRACKLIB_COMMON_BUFFER_BUFFER_STORE_CXX_HPP__
#define SIXTRACKLIB_COMMON_BUFFER_BUFFER_STORE_CXX_HPP__

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

namespace SIXTRL_CXX_NAMESPACE
{
    class BufferStoreBase
    {
        public:

        using role_t     = SIXTRL_CXX_NAMESPACE::buffer_store_role_t;
        using buffer_t   = SIXTRL_CXX_NAMESPACE::Buffer;
        using c_buffer_t = buffer_t::c_api_t;
        using size_type  = buffer_t::size_type;
        using flags_t    = buffer_t::flags_t;
        using status_t   = buffer_t::status_t;

        using stored_buffer_t = std::unique_ptr< buffer_t >;

        static constexpr size_type DEFAULT_BUFFER_CAPACITY =
            buffer_t::DEFAULT_BUFFER_CAPACITY;

        static constexpr flags_t DEFAULT_DATASTORE_FLAGS =
            buffer_t::DEFAULT_DATASTORE_FLAGS;

        static constexpr role_t USER_DEFINED_ROLE =
            SIXTRL_CXX_NAMESPACE::BUFFER_STORE_ROLE_USER_DEFINED;

        static constexpr role_t NO_ROLE =
            SIXTRL_CXX_NAMESPACE::BUFFER_STORE_ROLE_NONE;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN explicit BufferStoreBase(
            size_type const buffer_capacity = DEFAULT_BUFFER_CAPACITY,
            role_t const role = USER_DEFINED_ROLE,
            flags_t const buffer_flags = DEFAULT_DATASTORE_FLAGS );

        SIXTRL_HOST_FN explicit BufferStoreBase(
            buffer_t* SIXTRL_RESTRICT cxx_buffer,
            role_t const role = USER_DEFINED_ROLE,
            bool const take_ownership = false );

        SIXTRL_HOST_FN explicit BufferStoreBase(
            c_buffer_t* SIXTRL_RESTRICT c99_buffer,
            role_t const role = USER_DEFINED_ROLE,
            bool const take_ownership = false,
            bool const delete_ptr_after_move = true );

        SIXTRL_HOST_FN explicit BufferStoreBase(
            stored_buffer_t&& stored_ptr_buffer,
            role_t const role = USER_DEFINED_ROLE );

        SIXTRL_HOST_FN explicit BufferStoreBase(
            buffer_t&& cxx_buffer, role_t const role = USER_DEFINED_ROLE );

        SIXTRL_HOST_FN BufferStoreBase( BufferStoreBase const& other );
        SIXTRL_HOST_FN BufferStoreBase( BufferStoreBase&& o ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN BufferStoreBase& operator=( BufferStoreBase const& r );
        SIXTRL_HOST_FN BufferStoreBase& operator=(
            BufferStoreBase&& other ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN virtual ~BufferStoreBase() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool active() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool owns_buffer() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN role_t role() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN void clear() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_c99_buffer() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN c_buffer_t const* buffer() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN c_buffer_t* buffer() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_cxx_buffer() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN buffer_t const* ptr_cxx_buffer() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN buffer_t* ptr_cxx_buffer() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_t const& cxx_buffer() const;
        SIXTRL_HOST_FN buffer_t& cxx_buffer();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t reset(
            buffer_t::size_type const buffer_capacity,
            role_t const role = ::NS(BUFFER_STORE_ROLE_USER_DEFINED),
            buffer_t::flags_t const buffer_flags = DEFAULT_DATASTORE_FLAGS );

        SIXTRL_HOST_FN status_t reset(
            buffer_t* SIXTRL_RESTRICT cxx_buffer,
            role_t const role = ::NS(BUFFER_STORE_ROLE_USER_DEFINED),
            bool const take_ownership = false );

        SIXTRL_HOST_FN status_t reset(
            c_buffer_t* SIXTRL_RESTRICT c99_buffer,
            role_t const role = ::NS(BUFFER_STORE_ROLE_USER_DEFINED),
            bool const take_ownership = false,
            bool const delete_ptr_after_move = true );

        SIXTRL_HOST_FN status_t reset(
            stored_buffer_t&& stored_ptr_buffer,
            role_t const role = USER_DEFINED_ROLE );

        SIXTRL_HOST_FN status_t reset( buffer_t&& cxx_buffer,
            role_t const role = USER_DEFINED_ROLE );

        protected:

        SIXTRL_HOST_FN virtual void doClear();

        SIXTRL_HOST_FN virtual status_t doResetCxxBuffer(
            buffer_t* SIXTRL_RESTRICT cxx_buffer, role_t const role,
            bool const take_ownership );

        SIXTRL_HOST_FN virtual status_t doResetStoredCxxBufferByMove(
            stored_buffer_t&& stored_ptr_buffer, role_t const role );

        SIXTRL_HOST_FN virtual status_t doResetCxxBufferByMove(
            buffer_t&& cxx_buffer, role_t const role );

        SIXTRL_HOST_FN virtual status_t doResetC99Buffer(
            c_buffer_t* SIXTRL_RESTRICT c99_buffer,
            role_t const role, bool const take_ownership,
            bool const delete_ptr_after_move );

        private:

        SIXTRL_HOST_FN void doClearBaseImpl() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doResetCxxBufferBaseImpl(
            buffer_t* SIXTRL_RESTRICT cxx_buffer, role_t const role,
            bool const take_ownership );

        SIXTRL_HOST_FN status_t doResetStoredCxxBufferByMoveBaseImpl(
            stored_buffer_t&& stored_ptr_buffer, role_t const role );

        SIXTRL_HOST_FN status_t doResetCxxBufferByMoveBaseImpl(
            buffer_t&& cxx_buffer, role_t const role );

        SIXTRL_HOST_FN status_t doResetC99BufferBaseImpl(
            c_buffer_t* SIXTRL_RESTRICT c99_buffer,
            role_t const role, bool const take_ownership,
            bool const delete_ptr_after_move );

        buffer_t*                   m_ptr_cxx_buffer;
        c_buffer_t*                 m_ptr_c99_buffer;
        std::unique_ptr< buffer_t > m_own_buffer;
        role_t                      m_buffer_role;
    };

    SIXTRL_INLINE bool BufferStoreBase::active() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( ( this->m_ptr_c99_buffer == nullptr ) &&
                         ( this->m_ptr_cxx_buffer == nullptr ) &&
                         ( this->m_own_buffer.get() == nullptr ) ) ||
                       ( ( this->m_ptr_c99_buffer != nullptr ) &&
                         ( ( this->m_ptr_cxx_buffer == nullptr ) ||
                           ( this->m_ptr_cxx_buffer->getCApiPtr() ==
                             this->m_ptr_c99_buffer ) ) &&
                         ( ( this->m_own_buffer == nullptr ) ||
                           ( this->m_own_buffer.get() ==
                             this->m_ptr_cxx_buffer ) ) ) );

        return this->has_c99_buffer();
    }

    SIXTRL_INLINE bool BufferStoreBase::owns_buffer() const SIXTRL_NOEXCEPT
    {
        return ( ( this->active() ) &&
                 ( this->m_own_buffer.get() != nullptr ) );
    }

    SIXTRL_INLINE BufferStoreBase::role_t
    BufferStoreBase::role() const SIXTRL_NOEXCEPT
    {
        return this->m_buffer_role;
    }

    SIXTRL_INLINE bool BufferStoreBase::has_c99_buffer() const SIXTRL_NOEXCEPT
    {
        return ( this->m_ptr_c99_buffer != nullptr );
    }

    SIXTRL_INLINE BufferStoreBase::c_buffer_t const*
    BufferStoreBase::buffer() const SIXTRL_NOEXCEPT
    {
        return this->m_ptr_c99_buffer;
    }

    SIXTRL_INLINE BufferStoreBase::c_buffer_t*
    BufferStoreBase::buffer() SIXTRL_NOEXCEPT
    {
        return this->m_ptr_c99_buffer;
    }

    SIXTRL_INLINE bool BufferStoreBase::has_cxx_buffer() const SIXTRL_NOEXCEPT
    {
        return ( this->m_ptr_cxx_buffer != nullptr );
    }

    SIXTRL_INLINE BufferStoreBase::buffer_t const*
    BufferStoreBase::ptr_cxx_buffer() const SIXTRL_NOEXCEPT
    {
        return this->m_ptr_cxx_buffer;
    }

    SIXTRL_INLINE BufferStoreBase::buffer_t*
    BufferStoreBase::ptr_cxx_buffer() SIXTRL_NOEXCEPT
    {
        return this->m_ptr_cxx_buffer;
    }
}

extern "C" {

typedef SIXTRL_CXX_NAMESPACE::BufferStoreBase NS(BufferStoreBase);

}

#else /* defined( __cplusplus ) && !defined( _GPUCODE ) */

struct NS(BufferStoreBase);

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_BUFFER_BUFFER_STORE_CXX_HPP__ */
