#include "sixtracklib/common/buffer/buffer_store.hpp"

#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
#include <random>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/buffer/definitions.h"
#include "sixtracklib/common/buffer.hpp"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/be_drift/be_drift.h"

#include "sixtracklib/testlib.h"

TEST( C99CommonBufferBufferStoreTests, MinimalUsageTest )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using buffer_store_t = ::NS(BufferStoreBase);
    using c_buffer_t     = ::NS(Buffer);
    using buf_size_t     = ::NS(buffer_size_t);

    constexpr buf_size_t BUFFER_00_CAPACITY = buf_size_t{ 256 };
    buffer_store_t* store_00 = ::NS(BufferStoreBase_create_with_buffer)(
        BUFFER_00_CAPACITY, ::NS(BUFFER_STORE_ROLE_USER_DEFINED) );

    ASSERT_TRUE( store_00 != nullptr );
    ASSERT_TRUE( ::NS(BufferStoreBase_active)( store_00 ) );
    ASSERT_TRUE( ::NS(BufferStoreBase_owns_buffer)( store_00 ) );
    ASSERT_TRUE( ::NS(BufferStoreBase_buffer)( store_00 ) != nullptr );
    ASSERT_TRUE( ::NS(BufferStoreBase_role)( store_00 ) ==
                 ::NS(BUFFER_STORE_ROLE_USER_DEFINED_ROLE) );
    ASSERT_TRUE( ::NS(Buffer_get_capacity)( ::NS(BufferStoreBase_buffer)(
                 store_00 ) ) >= BUFFER_00_CAPACITY );

    ::NS(BufferStoreBase_clear)( store_00 );

    ASSERT_TRUE( !::NS(BufferStoreBase_active)( store_00 ) );
    ASSERT_TRUE( !::NS(BufferStoreBase_owns_buffer)( store_00 ) );
    ASSERT_TRUE(  store_00.ptr_cxx_buffer() == nullptr );
    ASSERT_TRUE( !store_00.has_c99_buffer() );
    ASSERT_TRUE(  ::NS(BufferStoreBase_buffer)( store_00 ) == nullptr );
    ASSERT_TRUE(  ::NS(BufferStoreBase_role)( store_00 ) ==
                  buffer_store_t::NO_ROLE );

    /* --------------------------------------------------------------------- */

    constexpr buf_size_t BUFFER_02_CAPACITY = buf_size_t{ 1024 };
    buffer_t* buffer_02 = ::NS(Buffer_new)( BUFFER_02_CAPACITY );
    SIXTRL_ASSERT( buffer_02 != nullptr );

    buf_size_t const prev_buffer_02_size = ::NS(Buffer_get_size)( buffer_02 );

    buffer_store_t store_02(
        buffer_02, st::BUFFER_STORE_ROLE_BEAM_ELEMENTS_BUFFER );

    ASSERT_TRUE(  ::NS(BufferStoreBase_active)( store_02 ) );
    ASSERT_TRUE( !::NS(BufferStoreBase_owns_buffer)( store_02 ) );
    ASSERT_TRUE(  ::NS(BufferStoreBase_buffer)( store_02 ) != nullptr );
    ASSERT_TRUE(  ::NS(BufferStoreBase_buffer)( store_02 ) == buffer_02 );
    ASSERT_TRUE(  ::NS(BufferStoreBase_role)( store_02 ) ==
                  st::BUFFER_STORE_ROLE_BEAM_ELEMENTS_BUFFER );

    ::NS(BufferStoreBase_clear)( store_02 );

    ::NS(Drift)* drift = ::NS(Drift_new)( buffer_02 );
    ASSERT_TRUE( drift != nullptr );
    ASSERT_TRUE( ::NS(Buffer_get_size)( buffer_02 ) > prev_buffer_02_size );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == store_02.reset( buffer_02,
        st::BUFFER_STORE_ROLE_BEAM_ELEMENTS_BUFFER, true ) );

    buffer_02 = nullptr;

    ASSERT_TRUE(  ::NS(BufferStoreBase_active)( store_02 ) );
    ASSERT_TRUE(  ::NS(BufferStoreBase_owns_buffer)( store_02 ) );
    ASSERT_TRUE(  ::NS(BufferStoreBase_buffer)( store_02 ) != nullptr );
    ASSERT_TRUE(  ::NS(BufferStoreBase_role)( store_02 ) ==
                  st::BUFFER_STORE_ROLE_BEAM_ELEMENTS_BUFFER );
}
