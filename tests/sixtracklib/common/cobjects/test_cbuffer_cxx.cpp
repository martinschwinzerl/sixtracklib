#include "sixtracklib/common/cobjects/cbuffer.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <random>
#include <functional>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/testlib.h"
#include "sixtracklib/testlib/common/objs.hpp"

TEST( CXXCommonCObjectsCBuffer, ConstructionReserveRemap )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    typedef st::CBuffer cbuffer_t;
    typedef cbuffer_t::size_type st_size_t;

    cbuffer_t buffer;

    ASSERT_TRUE(  buffer.p_base_begin() != nullptr );
    ASSERT_TRUE(  buffer.size() >= cbuffer_t::BUFFER_MINIMAL_SIZE );
    ASSERT_TRUE(  buffer.capacity() >= buffer.size() );

    ASSERT_TRUE( !buffer.needs_remapping() );
    ASSERT_TRUE(  buffer.allow_remap() );
    ASSERT_TRUE(  buffer.allow_allocate() );
    ASSERT_TRUE(  buffer.allow_realloc() );

    ASSERT_TRUE(  buffer.n_objects()    == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.n_slots()      == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.n_pointers()   == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.n_garbage()    == st_size_t{ 0 } );

    ASSERT_TRUE(  buffer.max_objects()  == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.max_slots()    == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.max_pointers() == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.max_garbage()  == st_size_t{ 0 } );

    /* --------------------------------------------------------------------- */

    st_size_t current_buffer_size     = buffer.size();
    st_size_t current_buffer_capacity = buffer.capacity();

    st_size_t target_buffer_capacity  =
        current_buffer_capacity * st_size_t{ 2 };

    ASSERT_TRUE( buffer.reserve(
        target_buffer_capacity ) == st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE( buffer.size() == current_buffer_size );
    ASSERT_TRUE( buffer.capacity() >= target_buffer_capacity );

    ASSERT_TRUE(  buffer.n_objects()    == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.n_slots()      == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.n_pointers()   == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.n_garbage()    == st_size_t{ 0 } );

    ASSERT_TRUE(  buffer.max_objects()  == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.max_slots()    == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.max_pointers() == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.max_garbage()  == st_size_t{ 0 } );

    current_buffer_capacity = buffer.capacity();
    current_buffer_size = buffer.size();

    /* --------------------------------------------------------------------- */

    st_size_t target_max_num_slots    = st_size_t{ 100 };
    st_size_t target_max_num_objs     = st_size_t{ 5 };
    st_size_t target_max_num_pointers = st_size_t{ 10 };
    st_size_t target_max_num_garbage  = st_size_t{ 5 };

    ASSERT_FALSE( buffer.can_allocate(
        target_max_num_slots, target_max_num_objs, target_max_num_pointers,
            target_max_num_garbage ) );

    ASSERT_TRUE( buffer.reserve( target_max_num_slots, target_max_num_objs,
        target_max_num_pointers, target_max_num_garbage
        ) == st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE(  buffer.capacity() > current_buffer_capacity );
    ASSERT_TRUE(  buffer.size()     > current_buffer_size );

    ASSERT_TRUE(  buffer.n_objects()    == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.n_slots()      == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.n_pointers()   == st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.n_garbage()    == st_size_t{ 0 } );

    ASSERT_TRUE(  buffer.max_objects()  >= target_max_num_objs );
    ASSERT_TRUE(  buffer.max_slots()    >= target_max_num_slots );
    ASSERT_TRUE(  buffer.max_pointers() >= target_max_num_pointers );
    ASSERT_TRUE(  buffer.max_garbage()  >= target_max_num_garbage );
}
