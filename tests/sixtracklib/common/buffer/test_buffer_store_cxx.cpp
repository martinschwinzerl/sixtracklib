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

TEST( CXXCommonBufferBufferStoreTests, MinimalUsageTest )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using buffer_store_t = st::BufferStoreBase;
    using buffer_t       = buffer_store_t::buffer_t;
    using c_buffer_t     = buffer_store_t::c_buffer_t;
    using buf_size_t     = buffer_store_t::size_type;

    constexpr buf_size_t BUFFER_00_CAPACITY = buf_size_t{ 256 };
    buffer_store_t store_00( BUFFER_00_CAPACITY );

    ASSERT_TRUE( store_00.active() );
    ASSERT_TRUE( store_00.owns_buffer() );
    ASSERT_TRUE( store_00.has_cxx_buffer() );
    ASSERT_TRUE( store_00.ptr_cxx_buffer() != nullptr );
    ASSERT_TRUE( store_00.ptr_cxx_buffer()->capacity() >= BUFFER_00_CAPACITY );
    ASSERT_TRUE( store_00.has_c99_buffer() );
    ASSERT_TRUE( store_00.buffer() != nullptr );
    ASSERT_TRUE( store_00.role() == buffer_store_t::USER_DEFINED_ROLE );
    ASSERT_TRUE( ::NS(Buffer_get_capacity)( store_00.buffer() ) >=
                 BUFFER_00_CAPACITY );

    store_00.clear();

    ASSERT_TRUE( !store_00.active() );
    ASSERT_TRUE( !store_00.owns_buffer() );
    ASSERT_TRUE( !store_00.has_cxx_buffer() );
    ASSERT_TRUE(  store_00.ptr_cxx_buffer() == nullptr );
    ASSERT_TRUE( !store_00.has_c99_buffer() );
    ASSERT_TRUE(  store_00.buffer() == nullptr );
    ASSERT_TRUE(  store_00.role() == buffer_store_t::NO_ROLE );

    /* --------------------------------------------------------------------- */

    constexpr buf_size_t BUFFER_01_CAPACITY = buf_size_t{ 512 };
    buffer_t buffer_01( buf_size_t{ 512 } );

    buffer_store_t store_01_not_owning(
        &buffer_01, st::BUFFER_STORE_ROLE_PARTICLES_BUFFER );

    ASSERT_TRUE(  store_01_not_owning.active() );
    ASSERT_TRUE( !store_01_not_owning.owns_buffer() );
    ASSERT_TRUE(  store_01_not_owning.has_cxx_buffer() );
    ASSERT_TRUE(  store_01_not_owning.ptr_cxx_buffer() != nullptr );
    ASSERT_TRUE(  store_01_not_owning.ptr_cxx_buffer() == &buffer_01 );
    ASSERT_TRUE(  store_01_not_owning.has_c99_buffer() );
    ASSERT_TRUE(  store_01_not_owning.buffer() != nullptr );
    ASSERT_TRUE(  store_01_not_owning.buffer() == buffer_01.getCApiPtr() );
    ASSERT_TRUE(  store_01_not_owning.role() ==
                  st::BUFFER_STORE_ROLE_PARTICLES_BUFFER );

    buffer_store_t store_01_c99_not_owning(
        buffer_01.getCApiPtr(), st::BUFFER_STORE_ROLE_PARTICLES_BUFFER );

    ASSERT_TRUE(  store_01_c99_not_owning.active() );
    ASSERT_TRUE( !store_01_c99_not_owning.owns_buffer() );
    ASSERT_TRUE( !store_01_c99_not_owning.has_cxx_buffer() );
    ASSERT_TRUE(  store_01_c99_not_owning.ptr_cxx_buffer() == nullptr );
    ASSERT_TRUE(  store_01_c99_not_owning.has_c99_buffer() );
    ASSERT_TRUE(  store_01_c99_not_owning.buffer() != nullptr );
    ASSERT_TRUE(  store_01_c99_not_owning.buffer() == buffer_01.getCApiPtr() );
    ASSERT_TRUE(  store_01_c99_not_owning.role() ==
                  st::BUFFER_STORE_ROLE_PARTICLES_BUFFER );

    buffer_store_t store_01( std::move( buffer_01 ),
        st::BUFFER_STORE_ROLE_PARTICLES_BUFFER );

    ASSERT_TRUE(  store_01.active() );
    ASSERT_TRUE(  store_01.owns_buffer() );
    ASSERT_TRUE(  store_01.has_cxx_buffer() );
    ASSERT_TRUE(  store_01.ptr_cxx_buffer() != nullptr );
    ASSERT_TRUE(  store_01.has_c99_buffer() );
    ASSERT_TRUE(  store_01.buffer() != nullptr );
    ASSERT_TRUE(  store_01.role() == st::BUFFER_STORE_ROLE_PARTICLES_BUFFER );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == store_01_not_owning.reset(
                    store_01.ptr_cxx_buffer(), store_01.role() ) );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == store_01_c99_not_owning.reset(
                    store_01.buffer(), store_01.role() ) );

    /* --------------------------------------------------------------------- */

    constexpr buf_size_t BUFFER_02_CAPACITY = buf_size_t{ 1024 };
    buffer_t* buffer_02 = ::NS(Buffer_new)( BUFFER_02_CAPACITY );
    SIXTRL_ASSERT( buffer_02 != nullptr );

    buf_size_t const prev_buffer_02_size = ::NS(Buffer_get_size)( buffer_02 );

    buffer_store_t store_02(
        buffer_02, st::BUFFER_STORE_ROLE_BEAM_ELEMENTS_BUFFER );

    ASSERT_TRUE(  store_02.active() );
    ASSERT_TRUE( !store_02.owns_buffer() );
    ASSERT_TRUE( !store_02.has_cxx_buffer() );
    ASSERT_TRUE(  store_02.ptr_cxx_buffer() == nullptr );
    ASSERT_TRUE(  store_02.has_c99_buffer() );
    ASSERT_TRUE(  store_02.buffer() != nullptr );
    ASSERT_TRUE(  store_02.buffer() == buffer_02 );
    ASSERT_TRUE(  store_02.role() ==
                  st::BUFFER_STORE_ROLE_BEAM_ELEMENTS_BUFFER );

    store_02.clear();

    ::NS(Drift)* drift = ::NS(Drift_new)( buffer_02 );
    ASSERT_TRUE( drift != nullptr );
    ASSERT_TRUE( ::NS(Buffer_get_size)( buffer_02 ) > prev_buffer_02_size );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == store_02.reset( buffer_02,
        st::BUFFER_STORE_ROLE_BEAM_ELEMENTS_BUFFER, true ) );

    buffer_02 = nullptr;

    ASSERT_TRUE(  store_02.active() );
    ASSERT_TRUE(  store_02.owns_buffer() );
    ASSERT_TRUE(  store_02.has_cxx_buffer() );
    ASSERT_TRUE(  store_02.ptr_cxx_buffer() != nullptr );
    ASSERT_TRUE(  store_02.has_c99_buffer() );
    ASSERT_TRUE(  store_02.buffer() != nullptr );
    ASSERT_TRUE(  store_02.role() ==
                  st::BUFFER_STORE_ROLE_BEAM_ELEMENTS_BUFFER );

    /* --------------------------------------------------------------------- */

    constexpr buf_size_t BUFFER_03_CAPACITY = buf_size_t{ 2048 };

    std::unique_ptr< buffer_t > ptr_buffer_03(
        new buffer_t( BUFFER_03_CAPACITY ) );

    ASSERT_TRUE( ptr_buffer_03.get() != nullptr );
    ASSERT_TRUE( ptr_buffer_03->capacity() >= BUFFER_03_CAPACITY );

    buffer_t* weak_buffer_03_ptr = ptr_buffer_03.get();
    SIXTRL_ASSERT( weak_buffer_03_ptr != nullptr );

    buffer_store_t store_03( std::move( ptr_buffer_03 ),
            st::BUFFER_STORE_ROLE_CONFIG_BUFFER );

    ASSERT_TRUE(  store_03.active() );
    ASSERT_TRUE(  store_03.owns_buffer() );
    ASSERT_TRUE(  store_03.has_cxx_buffer() );
    ASSERT_TRUE(  store_03.ptr_cxx_buffer() != nullptr );
    ASSERT_TRUE(  store_03.ptr_cxx_buffer() == weak_buffer_03_ptr );
    ASSERT_TRUE(  store_03.has_c99_buffer() );
    ASSERT_TRUE(  store_03.buffer() != nullptr );
    ASSERT_TRUE(  store_03.buffer() == weak_buffer_03_ptr->getCApiPtr() );
    ASSERT_TRUE(  store_03.role() ==
                  st::BUFFER_STORE_ROLE_BEAM_ELEMENTS_BUFFER );
}
