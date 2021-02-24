#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cmath>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/cobjects/cbuffer.h"
#include "sixtracklib/testlib.hpp"

/* ************************************************************************* */

TEST( C99CommonCObjectsCBuffer, InitAsViewOnExistingFlatBuffer )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using raw_type = ::NS(cobj_raw_type);
    using st_size_t = ::NS(cobj_size_type);

    st_size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;

    std::vector< raw_type > too_small_data_buffer(
        ::NS(CBuffer_min_buffer_size)( slot_size ) - st_size_t{ 1u },
            raw_type{ 0 } );

    std::vector< raw_type > data_buffer(
        st_size_t{ 1 } << st_size_t{ 20 }, raw_type{ 0 } );

    ::NS(CBuffer) view;
    ::NS(CBuffer_preset)( &view );

    st::status_type status = ::NS(CBuffer_init_as_view)(
        &view, reinterpret_cast< uintptr_t >( too_small_data_buffer.data() ),
            too_small_data_buffer.size() );

    ASSERT_TRUE( status != st::STATUS_SUCCESS );
    ASSERT_TRUE( ::NS(CBuffer_base_address)( &view ) ==
                 st::COBJECTS_NULL_ADDRESS );
    ASSERT_TRUE( ::NS(CBuffer_capacity)( &view ) == st_size_t{ 0 } );

    ASSERT_FALSE( ::NS(CBuffer_allow_remap)( &view ) );
    ASSERT_FALSE( ::NS(CBuffer_allow_allocate)( &view ) );
    ASSERT_FALSE( ::NS(CBuffer_allow_append)( &view ) );
    ASSERT_FALSE( ::NS(CBuffer_owns_stored_data)( &view ) );

    ::NS(CBuffer_preset)( &view );

    status = ::NS(CBuffer_init_as_view)( &view, reinterpret_cast< uintptr_t >(
        data_buffer.data() ), data_buffer.size() );

    ASSERT_TRUE( status == st::STATUS_SUCCESS );
    ASSERT_TRUE(  ::NS(CBuffer_base_address)( &view ) !=
                       st::COBJECTS_NULL_ADDRESS );
    ASSERT_TRUE(  ::NS(CBuffer_p_const_base)( &view ) != nullptr );
    ASSERT_TRUE(  ::NS(CBuffer_capacity)( &view ) >
                  ::NS(CBuffer_min_buffer_size)( slot_size ) );
    ASSERT_TRUE(  ::NS(CBuffer_capacity)( &view ) <= data_buffer.size() );
    ASSERT_TRUE(  ::NS(CBuffer_size)( &view ) ==
                  ::NS(CBuffer_min_buffer_size)( slot_size ) );

    ASSERT_TRUE(  ::NS(CBuffer_allow_remap)( &view ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_allocate)( &view ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_append)( &view ) );
    ASSERT_FALSE( ::NS(CBuffer_owns_stored_data)( &view ) );
}

TEST( C99CommonCObjectsCBuffer, NewAsViewOnExistingFlatBuffer )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using raw_type = st::cobj_raw_type;
    using st_size_t = st::cobj_size_type;

    st_size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    std::vector< raw_type > data_buffer( st_size_t{ 1 } << st_size_t{ 20 } );

    ::NS(CBuffer)* view = ::NS(CBuffer_new_as_view)(
        reinterpret_cast< uintptr_t >( data_buffer.data() ),
            data_buffer.size() );

    ASSERT_TRUE(  view != nullptr );
    ASSERT_TRUE(  ::NS(CBuffer_slot_size)( view ) > st_size_t{ 0 } );
    ASSERT_TRUE(  ::NS(CBuffer_size)( view ) ==
                  ::NS(CBuffer_min_buffer_size)( slot_size ) );
    ASSERT_TRUE(  ::NS(CBuffer_capacity)( view ) >=
                  ::NS(CBuffer_min_buffer_size)( slot_size ) );
    ASSERT_TRUE(  ::NS(CBuffer_capacity)( view ) <= data_buffer.size() );
    ASSERT_TRUE(  ::NS(CBuffer_p_const_base)( view ) != nullptr );
    ASSERT_TRUE(  ::NS(CBuffer_allow_remap)( view ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_allocate)( view ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_append)( view ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_realloc)( view ) );
    ASSERT_FALSE( ::NS(CBuffer_owns_stored_data)( view ) );

    ::NS(CBuffer_delete)( view );
    view = nullptr;
}

TEST( C99CommonCObjectsCBuffer, InitAsBufferMinCapacity )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;

    st_size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) buffer;

    ::NS(CBuffer_preset)( &buffer );
    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CBuffer_init_as_buffer)(
        &buffer, ::NS(CBuffer_min_buffer_size)( slot_size ) ) );

    ASSERT_TRUE(  ::NS(CBuffer_slot_size)( &buffer ) == slot_size );
    ASSERT_TRUE(  ::NS(CBuffer_size)( &buffer ) ==
                  ::NS(CBuffer_min_buffer_size)( slot_size ) );
    ASSERT_TRUE(  ::NS(CBuffer_capacity)( &buffer ) >=
                  ::NS(CBuffer_min_buffer_size)( slot_size ) );
    ASSERT_TRUE(  ::NS(CBuffer_p_const_base)( &buffer ) != nullptr );
    ASSERT_TRUE(  ::NS(CBuffer_allow_remap)( &buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_allocate)( &buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_append)( &buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_realloc)( &buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_owns_stored_data)( &buffer ) );

    ::NS(CBuffer_free)( &buffer );
}

TEST( C99CommonCObjectsCBuffer, NewAsBufferMinCapacity )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;

    st_size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* buffer = ::NS(CBuffer_new)();

    ASSERT_TRUE(  buffer != nullptr );
    ASSERT_TRUE(  ::NS(CBuffer_slot_size)( buffer ) == slot_size );
    ASSERT_TRUE(  ::NS(CBuffer_size)( buffer ) ==
                  ::NS(CBuffer_min_buffer_size)( slot_size ) );
    ASSERT_TRUE(  ::NS(CBuffer_capacity)( buffer ) >=
                  ::NS(CBuffer_min_buffer_size)( slot_size ) );
    ASSERT_TRUE(  ::NS(CBuffer_p_const_base)( buffer ) != nullptr );
    ASSERT_TRUE(  ::NS(CBuffer_allow_remap)( buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_allocate)( buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_append)( buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_realloc)( buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_owns_stored_data)( buffer ) );

    ::NS(CBuffer_delete)( buffer );
}

TEST( C99CommonCObjectsCBuffer, InitAsBufferWithCapacity )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;

    st_size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    st_size_t const requ_capacity = st_size_t{ 1 } << st_size_t{ 20 };
    ASSERT_TRUE( requ_capacity > ::NS(CBuffer_min_buffer_size)( slot_size ) );

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) buffer;

    ::NS(CBuffer_preset)( &buffer );
    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CBuffer_init_as_buffer)(
        &buffer, requ_capacity ) );

    ASSERT_TRUE(  ::NS(CBuffer_slot_size)( &buffer ) == slot_size );
    ASSERT_TRUE(  ::NS(CBuffer_size)( &buffer ) >=
                  ::NS(CBuffer_min_buffer_size)( slot_size ) );
    ASSERT_TRUE(  ::NS(CBuffer_capacity)( &buffer ) >= requ_capacity );
    ASSERT_TRUE(  ::NS(CBuffer_p_const_base)( &buffer ) != nullptr );
    ASSERT_TRUE(  ::NS(CBuffer_allow_remap)( &buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_allocate)( &buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_append)( &buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_realloc)( &buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_owns_stored_data)( &buffer ) );

    ::NS(CBuffer_free)( &buffer );
}

TEST( C99CommonCObjectsCBuffer, NewAsBufferWithCapacity )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;

    st_size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    st_size_t const requ_capacity = st_size_t{ 1 } << st_size_t{ 20 };
    ASSERT_TRUE( requ_capacity > ::NS(CBuffer_min_buffer_size)( slot_size ) );

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* buffer =
        ::NS(CBuffer_new_with_capacity)( requ_capacity );

    ASSERT_TRUE(  buffer != nullptr );
    ASSERT_TRUE(  ::NS(CBuffer_slot_size)( buffer ) == slot_size );
    ASSERT_TRUE(  ::NS(CBuffer_size)( buffer ) >=
                  ::NS(CBuffer_min_buffer_size)( slot_size ) );
    ASSERT_TRUE(  ::NS(CBuffer_capacity)( buffer ) >= requ_capacity );
    ASSERT_TRUE(  ::NS(CBuffer_p_const_base)( buffer ) != nullptr );
    ASSERT_TRUE(  ::NS(CBuffer_allow_remap)( buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_allocate)( buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_append)( buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_allow_realloc)( buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_owns_stored_data)( buffer ) );

    ::NS(CBuffer_delete)( buffer );
}


TEST( C99CommonCObjectsCBuffer, InitViewAndBufferAddElementsReserveCompare )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;
    using raw_type  = st::cobj_raw_type;
    using real_type = ::NS(cobj_test_real_type);
    using uint_type = ::NS(cobj_test_uint64_type);
    using int_type  = ::NS(cobj_test_int64_type);
    using prng_seed_type = std::mt19937_64::result_type;

    /* --------------------------------------------------------------------- */

    std::vector< raw_type > flat_buffer(
        st_size_t{ 1 } << st_size_t{ 20 }, raw_type{ 0 } );

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) view;
    ::NS(CBuffer_preset)( &view );

    st_size_t const slot_size = ::NS(CBuffer_slot_size)( &view );

    ::NS(CBuffer_init_as_view)( &view, reinterpret_cast< uintptr_t >(
        flat_buffer.data() ), flat_buffer.size() );

    ASSERT_TRUE(  ::NS(CBuffer_p_const_base)( &view ) != nullptr );
    ASSERT_TRUE(  ::NS(CBuffer_base_address)( &view ) % slot_size ==
                  st_size_t{ 0 } );

    ASSERT_TRUE( !::NS(CBuffer_needs_remapping)( &view ) );
    ASSERT_TRUE(  ::NS(CBuffer_capacity)( &view ) == flat_buffer.size() );
    ASSERT_TRUE(  ::NS(CBuffer_size)( &view ) == ::NS(CBuffer_min_buffer_size)(
                    ::NS(CBuffer_slot_size)( &view ) ) );

    st_size_t prev_n_slots = ::NS(CBuffer_num_slots)( &view );
    st_size_t prev_n_objs  = ::NS(CBuffer_num_objects)( &view );
    st_size_t prev_n_ptrs  = ::NS(CBuffer_num_pointers)( &view );

    ASSERT_TRUE( ::NS(CBuffer_num_slots)(    &view ) == st_size_t{ 0 } );
    ASSERT_TRUE( ::NS(CBuffer_num_objects)(  &view ) == st_size_t{ 0 } );
    ASSERT_TRUE( ::NS(CBuffer_num_pointers)( &view ) == st_size_t{ 0 } );
    ASSERT_TRUE( ::NS(CBuffer_num_garbage)(  &view ) == st_size_t{ 0 } );

    ASSERT_TRUE( ::NS(CBuffer_max_slots)(    &view ) == st_size_t{ 0 } );
    ASSERT_TRUE( ::NS(CBuffer_max_objects)(  &view ) == st_size_t{ 0 } );
    ASSERT_TRUE( ::NS(CBuffer_max_pointers)( &view ) == st_size_t{ 0 } );
    ASSERT_TRUE( ::NS(CBuffer_max_garbage)(  &view ) == st_size_t{ 0 } );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* buffer = ::NS(CBuffer_new)();

    ASSERT_TRUE(  buffer != nullptr );
    ASSERT_TRUE(  ::NS(CBuffer_slot_size)( buffer ) > st_size_t{ 0 } );
    ASSERT_TRUE(  ::NS(CBuffer_p_const_base)( buffer ) != nullptr );
    ASSERT_TRUE(  ::NS(CBuffer_base_address)( buffer ) % slot_size ==
                  st_size_t{ 0 } );

    ASSERT_TRUE( !::NS(CBuffer_needs_remapping)( buffer ) );
    ASSERT_TRUE(  ::NS(CBuffer_size)( buffer ) >= ::NS(CBuffer_min_buffer_size)(
                    ::NS(CBuffer_slot_size)( buffer ) ) );

    prev_n_slots = ::NS(CBuffer_num_slots)( buffer );
    prev_n_objs  = ::NS(CBuffer_num_objects)( buffer );
    prev_n_ptrs  = ::NS(CBuffer_num_pointers)( buffer );

    ASSERT_TRUE( ::NS(CBuffer_num_slots)(    buffer ) == st_size_t{ 0 } );
    ASSERT_TRUE( ::NS(CBuffer_num_objects)(  buffer ) == st_size_t{ 0 } );
    ASSERT_TRUE( ::NS(CBuffer_num_pointers)( buffer ) == st_size_t{ 0 } );
    ASSERT_TRUE( ::NS(CBuffer_num_garbage)(  buffer ) == st_size_t{ 0 } );

    ASSERT_TRUE( ::NS(CBuffer_max_slots)(    buffer ) == st_size_t{ 0 } );
    ASSERT_TRUE( ::NS(CBuffer_max_objects)(  buffer ) == st_size_t{ 0 } );
    ASSERT_TRUE( ::NS(CBuffer_max_pointers)( buffer ) == st_size_t{ 0 } );
    ASSERT_TRUE( ::NS(CBuffer_max_garbage)(  buffer ) == st_size_t{ 0 } );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    constexpr uint_type NUM_CMP_ELEMENTS = uint_type{ 64 };
    constexpr uint_type NO_PTRS_C_LENGTH = uint_type{  6 };
    constexpr uint_type MIN_B_LENGTH     = uint_type{  5 };
    constexpr uint_type MAX_B_LENGTH     = uint_type{ 10 };
    constexpr uint_type MIN_C_LENGTH     = uint_type{  2 };
    constexpr uint_type MAX_C_LENGTH     = uint_type{ 16 };

    std::uniform_real_distribution< real_type > a_dist( -5.0, 5.0 );
    std::uniform_real_distribution< real_type > vec_dist( -42.0, +42.0 );
    std::uniform_int_distribution< uint_type >  u64_dist( 10, 100 );
    std::uniform_int_distribution< int_type >   i64_dist( -100, -2 );

    std::uniform_int_distribution< uint_type > b_length_dist(
        MIN_B_LENGTH, MAX_B_LENGTH );

    std::uniform_int_distribution< uint_type > c_length_dist(
        MIN_C_LENGTH, MAX_C_LENGTH );

    std::mt19937_64 prng( prng_seed_type{ 20210201 } );

    std::vector< ::NS(CObjTestNoPtrs) > cmp_no_ptrs_obj;
    cmp_no_ptrs_obj.reserve( NUM_CMP_ELEMENTS );

    std::vector< ::NS(CObjTestDataptrs) > cmp_dataptrs_obj;
    cmp_dataptrs_obj.reserve( NUM_CMP_ELEMENTS );

    std::vector< real_type > no_ptrs_c_values(
        NUM_CMP_ELEMENTS * NO_PTRS_C_LENGTH, real_type{ 0. } );

    for( auto& v : no_ptrs_c_values ) v = vec_dist( prng );

    std::vector< real_type > dataptrs_b_values(
        NUM_CMP_ELEMENTS * MAX_B_LENGTH, real_type{ 0. } );

    for( auto& v : dataptrs_b_values ) v = vec_dist( prng );

    std::vector< real_type > dataptrs_c_values(
        NUM_CMP_ELEMENTS * MAX_C_LENGTH, real_type{ 0. } );

    for( auto& v : dataptrs_c_values ) v = vec_dist( prng );

    uint_type no_ptrs_c_offset  = uint_type{ 0 };
    uint_type dataptrs_b_offset = uint_type{ 0 };
    uint_type dataptrs_c_offset = uint_type{ 0 };

    /* ---------------------------------------------------------------------- */

    for( uint_type ii = 0u ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        cmp_no_ptrs_obj.push_back( ::NS(CObjTestNoPtrs){} );

        ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CObjTestNoPtrs_set_a)(
            &cmp_no_ptrs_obj.back(), a_dist( prng ) ) );

        ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CObjTestNoPtrs_set_b)(
            &cmp_no_ptrs_obj.back(), u64_dist( prng ) ) );

        uint_type const NN = ::NS(CObjTestNoPtrs_c_length)(
            &( cmp_no_ptrs_obj.back() ) );

        for( uint_type jj = 0u ; jj < NN ; ++jj )
        {
            ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CObjTestNoPtrs_set_c)(
                &cmp_no_ptrs_obj.back(), jj, u64_dist( prng ) ) );
        }

        ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CObjTestNoPtrs_set_d)(
            &cmp_no_ptrs_obj.back(), i64_dist( prng ) ) );

        no_ptrs_c_offset += NN;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        uint_type const b_capacity = b_length_dist( prng );
        uint_type b_length = b_length_dist( prng );
        if( b_length > b_capacity ) b_length = b_capacity;

        uint_type const c_capacity = c_length_dist( prng );
        uint_type c_length = c_length_dist( prng );
        if( c_length > c_capacity ) c_length = c_capacity;

        cmp_dataptrs_obj.push_back( ::NS(CObjTestDataptrs){ a_dist( prng ),
            b_capacity, b_length, reinterpret_cast< uintptr_t >(
                &dataptrs_b_values[ dataptrs_b_offset ] ),
            c_capacity, c_length, reinterpret_cast< uintptr_t >(
                &dataptrs_c_values[ dataptrs_c_offset ] ) } );

        dataptrs_b_offset += b_capacity;
        dataptrs_c_offset += c_capacity;
    }

    /* ---------------------------------------------------------------------- */

    prev_n_slots = ::NS(CBuffer_num_slots)( &view );
    prev_n_objs  = ::NS(CBuffer_num_objects)( &view );
    prev_n_ptrs  = ::NS(CBuffer_num_pointers)( &view );

    st_size_t n_slots = prev_n_slots;
    st_size_t n_objs  = prev_n_objs;
    st_size_t n_ptrs  = prev_n_ptrs;

    for( uint_type ii = 0u ; ii < NUM_CMP_ELEMENTS ; ii += 2u )
    {
        for( uint_type jj = 0u, kk = ii ; jj < 2 ; ++jj, ++kk )
        {
            cmp_no_ptrs_obj[ kk ].a = static_cast< real_type >( kk );

            auto noptrs_obj_view = ::NS(CObjTestNoPtrs_cbuffer_add_copy)(
                &view, &cmp_no_ptrs_obj[ kk ] );

            ASSERT_TRUE( noptrs_obj_view != nullptr );
            ASSERT_TRUE( noptrs_obj_view != &cmp_no_ptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestNoPtrs_compare)(
                            &cmp_no_ptrs_obj[ kk ], noptrs_obj_view ) );

            n_slots = ::NS(CBuffer_num_slots)( &view );
            n_objs  = ::NS(CBuffer_num_objects)( &view );
            n_ptrs  = ::NS(CBuffer_num_pointers)( &view );

            ASSERT_TRUE( prev_n_objs + st_size_t{ 1 } == n_objs );
            ASSERT_TRUE( prev_n_ptrs + ::NS(CObjTestNoPtrs_cobj_num_dataptrs)()
                         == n_ptrs );
            ASSERT_TRUE( n_slots == prev_n_slots + (
                ::NS(CObjTestNoPtrs_cobj_required_num_bytes)( noptrs_obj_view,
                    slot_size ) / slot_size ) );

            ASSERT_TRUE( ::NS(CBuffer_max_slots)( &view ) >= n_slots );
            ASSERT_TRUE( ::NS(CBuffer_max_objects)( &view ) >= n_objs );
            ASSERT_TRUE( ::NS(CBuffer_max_pointers)( &view ) >= n_ptrs );

            auto noptrs_obj_buffer = ::NS(CObjTestNoPtrs_cbuffer_add_copy)(
                buffer, &cmp_no_ptrs_obj[ kk ] );

            ASSERT_TRUE( noptrs_obj_buffer != nullptr );
            ASSERT_TRUE( noptrs_obj_buffer != noptrs_obj_view );
            ASSERT_TRUE( noptrs_obj_buffer != &cmp_no_ptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestNoPtrs_compare)(
                            &cmp_no_ptrs_obj[ kk ], noptrs_obj_buffer ) );

            ASSERT_TRUE( n_slots == ::NS(CBuffer_num_slots)( buffer ) );
            ASSERT_TRUE( n_objs  == ::NS(CBuffer_num_objects)( buffer ) );
            ASSERT_TRUE( n_ptrs  == ::NS(CBuffer_num_pointers)( buffer ) );

            prev_n_slots = n_slots;
            prev_n_objs  = n_objs;
            prev_n_ptrs  = n_ptrs;
        }

        for( uint_type jj = 0u, kk = ii ; jj < 2 ; ++jj, ++kk )
        {
            cmp_dataptrs_obj[ kk ].a = static_cast< real_type >( kk );

            auto dataptrs_obj_view = ::NS(CObjTestDataptrs_cbuffer_add_copy)(
                &view, &cmp_dataptrs_obj[ kk ] );

            ASSERT_TRUE( dataptrs_obj_view != nullptr );
            ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
                            &cmp_dataptrs_obj[ kk ], dataptrs_obj_view ) );

            n_slots = ::NS(CBuffer_num_slots)( &view );
            n_objs  = ::NS(CBuffer_num_objects)( &view );
            n_ptrs  = ::NS(CBuffer_num_pointers)( &view );

            ASSERT_TRUE( prev_n_objs + st_size_t{ 1 } == n_objs );
            ASSERT_TRUE( prev_n_ptrs + ::NS(CObjTestDataptrs_cobj_num_dataptrs)()
                         == n_ptrs );
            ASSERT_TRUE( n_slots == prev_n_slots + (
                ::NS(CObjTestDataptrs_cobj_required_num_bytes)(
                    dataptrs_obj_view, slot_size ) / slot_size ) );

            auto dataptrs_obj_buffer = ::NS(CObjTestDataptrs_cbuffer_add_copy)(
                buffer, &cmp_dataptrs_obj[ kk ] );

            ASSERT_TRUE( dataptrs_obj_buffer != nullptr );
            ASSERT_TRUE( dataptrs_obj_buffer != dataptrs_obj_view );
            ASSERT_TRUE( dataptrs_obj_buffer != &cmp_dataptrs_obj[ kk ] );

            ASSERT_TRUE( n_slots == ::NS(CBuffer_num_slots)( buffer ) );
            ASSERT_TRUE( n_objs  == ::NS(CBuffer_num_objects)( buffer ) );
            ASSERT_TRUE( n_ptrs  == ::NS(CBuffer_num_pointers)( buffer ) );
            ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
                            &cmp_dataptrs_obj[ kk ], dataptrs_obj_buffer ) );

            prev_n_slots = n_slots;
            prev_n_objs  = n_objs;
            prev_n_ptrs  = n_ptrs;
        }
    }

    ASSERT_TRUE( ::NS(CBuffer_num_objects)( &view  ) == 2 * NUM_CMP_ELEMENTS );
    ASSERT_TRUE( ::NS(CBuffer_num_objects)( buffer ) == 2 * NUM_CMP_ELEMENTS );

    /* --------------------------------------------------------------------- */

    n_objs = ::NS(CBuffer_num_objects)( &view );

    for( st_size_t ii = st_size_t{ 0 } ; ii < n_objs ; ++ii )
    {
        st_size_t const jj = ii % st_size_t{ 4 };

        if( jj < st_size_t{ 2 } )
        {
            auto noptrs_obj_view = ::NS(CObjTestNoPtrs_const_from_cbuffer)(
                &view, ii );

            ASSERT_TRUE( noptrs_obj_view != nullptr );
            st_size_t kk = static_cast< st_size_t >( noptrs_obj_view->a );

            ASSERT_TRUE( kk < cmp_no_ptrs_obj.size() );
            ASSERT_TRUE( noptrs_obj_view != &cmp_no_ptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestNoPtrs_compare)(
                            &cmp_no_ptrs_obj[ kk ], noptrs_obj_view ) );

            auto noptrs_obj_buffer = ::NS(CObjTestNoPtrs_const_from_cbuffer)(
                buffer, ii );

            ASSERT_TRUE( noptrs_obj_buffer != nullptr );
            ASSERT_TRUE( noptrs_obj_buffer != noptrs_obj_view );
            ASSERT_TRUE( noptrs_obj_buffer != &cmp_no_ptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestNoPtrs_compare)(
                noptrs_obj_buffer, noptrs_obj_view ) );
        }
        else
        {
            auto dataptrs_obj_view = ::NS(CObjTestDataptrs_const_from_cbuffer)(
                &view, ii );

            ASSERT_TRUE( dataptrs_obj_view != nullptr );
            st_size_t kk = static_cast< st_size_t >( dataptrs_obj_view->a );

            ASSERT_TRUE( kk < cmp_dataptrs_obj.size() );
            ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
                            &cmp_dataptrs_obj[ kk ], dataptrs_obj_view ) );

            auto dataptrs_obj_buffer = ::NS(CObjTestDataptrs_const_from_cbuffer)(
                buffer, ii );

            ASSERT_TRUE( dataptrs_obj_buffer != nullptr );
            ASSERT_TRUE( dataptrs_obj_buffer != dataptrs_obj_view );
            ASSERT_TRUE( dataptrs_obj_buffer != &cmp_dataptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
                dataptrs_obj_buffer, dataptrs_obj_view ) );
        }
    }

    ::NS(CBuffer_delete)( buffer );
    ::NS(CBuffer_free)( &view );
}

TEST( C99CommonCObjectsCBuffer, InitAsViewNotEnoughCapacity )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;
    using raw_type  = st::cobj_raw_type;
    using real_type = ::NS(cobj_test_real_type);
    using uint_type = ::NS(cobj_test_uint64_type);
    using int_type  = ::NS(cobj_test_int64_type);
    using prng_seed_type = std::mt19937_64::result_type;

    /* --------------------------------------------------------------------- */

    st_size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    ASSERT_TRUE( slot_size > st_size_t{ 0 } );

    constexpr uint_type NUM_CMP_ELEMENTS = uint_type{ 64 };
    constexpr uint_type NUM_ELEM_TO_ADD  = NUM_CMP_ELEMENTS * uint_type{ 2 };
    constexpr uint_type MIN_B_LENGTH     = uint_type{  5 };
    constexpr uint_type MAX_B_LENGTH     = uint_type{ 10 };
    constexpr uint_type MIN_C_LENGTH     = uint_type{  2 };
    constexpr uint_type MAX_C_LENGTH     = uint_type{ 16 };

    std::uniform_real_distribution< real_type > a_dist( -5.0, 5.0 );
    std::uniform_real_distribution< real_type > vec_dist( -42.0, +42.0 );
    std::uniform_int_distribution< uint_type >  u64_dist( 10, 100 );
    std::uniform_int_distribution< int_type >   i64_dist( -100, -2 );

    std::uniform_int_distribution< uint_type > b_length_dist(
        MIN_B_LENGTH, MAX_B_LENGTH );

    std::uniform_int_distribution< uint_type > c_length_dist(
        MIN_C_LENGTH, MAX_C_LENGTH );

    std::mt19937_64 prng( prng_seed_type{ 20210201 } );

    std::vector< ::NS(CObjTestNoPtrs) > cmp_no_ptrs_obj;
    cmp_no_ptrs_obj.reserve( NUM_ELEM_TO_ADD );

    std::vector< ::NS(CObjTestDataptrs) > cmp_dataptrs_obj;
    cmp_dataptrs_obj.reserve( NUM_ELEM_TO_ADD );

    std::vector< real_type > dataptrs_b_values(
        NUM_ELEM_TO_ADD * MAX_B_LENGTH, real_type{ 0. } );

    for( auto& v : dataptrs_b_values ) v = vec_dist( prng );

    std::vector< real_type > dataptrs_c_values(
        NUM_ELEM_TO_ADD * MAX_C_LENGTH, real_type{ 0. } );

    for( auto& v : dataptrs_c_values ) v = vec_dist( prng );

    uint_type dataptrs_b_offset = uint_type{ 0 };
    uint_type dataptrs_c_offset = uint_type{ 0 };

    st_size_t requ_n_slots = st_size_t{ 0 };
    st_size_t requ_n_objs  = NUM_CMP_ELEMENTS;
    st_size_t requ_n_ptrs  = NUM_CMP_ELEMENTS *
        ::NS(CObjTestDataptrs_cobj_num_dataptrs)();

    /* ---------------------------------------------------------------------- */

    for( uint_type ii = 0u ; ii < NUM_ELEM_TO_ADD ; ++ii )
    {
        uint_type const b_capacity = b_length_dist( prng );
        uint_type b_length = b_length_dist( prng );
        if( b_length > b_capacity ) b_length = b_capacity;

        uint_type const c_capacity = c_length_dist( prng );
        uint_type c_length = c_length_dist( prng );
        if( c_length > c_capacity ) c_length = c_capacity;

        cmp_dataptrs_obj.push_back( ::NS(CObjTestDataptrs){ a_dist( prng ),
            b_capacity, b_length, reinterpret_cast< uintptr_t >(
                &dataptrs_b_values[ dataptrs_b_offset ] ),
            c_capacity, c_length, reinterpret_cast< uintptr_t >(
                &dataptrs_c_values[ dataptrs_c_offset ] ) } );

        dataptrs_b_offset += b_capacity;
        dataptrs_c_offset += c_capacity;

        if( ii < NUM_CMP_ELEMENTS )
        {
            requ_n_slots += ::NS(CObjTestDataptrs_cobj_required_num_bytes)(
                &cmp_dataptrs_obj.back(), slot_size ) / slot_size;
        }
    }

    ASSERT_TRUE( ( ::NS(CObjTestDataptrs_cobj_reserved_handle_size)( slot_size
        ) / slot_size ) < requ_n_slots );

    st_size_t requ_capacity = ::NS(CObjFlatBuffer_predict_required_buffer_size)(
        requ_n_slots, requ_n_objs, requ_n_ptrs, st_size_t{ 0 }, slot_size );

    ASSERT_TRUE( requ_capacity > ::NS(CBuffer_min_buffer_size)( slot_size ) );

    /* --------------------------------------------------------------------- */

    std::vector< raw_type > flat_buffer( requ_capacity, raw_type{ 0 } );

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) view;
    ::NS(CBuffer_preset)( &view );

    ::NS(CBuffer_init_as_view)( &view, reinterpret_cast< uintptr_t >(
        flat_buffer.data() ), flat_buffer.size() );

    ASSERT_TRUE( ::NS(CBuffer_capacity)( &view ) >= requ_capacity );
    ASSERT_TRUE( ::NS(CBuffer_capacity)( &view ) <  requ_capacity + slot_size );

    /* --------------------------------------------------------------------- */

    uint_type ii = 0u;

    for( ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        cmp_dataptrs_obj[ ii ].a = static_cast< real_type >( ii );
        auto dataptrs_obj_view = ::NS(CObjTestDataptrs_cbuffer_add_copy)(
            &view, &cmp_dataptrs_obj[ ii ] );

        ASSERT_TRUE( dataptrs_obj_view != nullptr );
        ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ ii ] );
        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            &cmp_dataptrs_obj[ ii ], dataptrs_obj_view ) );
    }

    for( ; ii < NUM_ELEM_TO_ADD ; ++ii )
    {
        cmp_dataptrs_obj[ ii ].a = static_cast< real_type >( ii );
        auto dataptrs_obj_view = ::NS(CObjTestDataptrs_cbuffer_add_copy)(
            &view, &cmp_dataptrs_obj[ ii ] );

        ASSERT_TRUE( dataptrs_obj_view == nullptr );
    }

    ASSERT_TRUE( ::NS(CBuffer_num_objects)( &view ) == NUM_CMP_ELEMENTS );

    for( ii = 0u ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        auto dataptrs_obj_view =
            ::NS(CObjTestDataptrs_const_from_cbuffer)( &view, ii );

        ASSERT_TRUE( dataptrs_obj_view != nullptr );
        st_size_t kk = static_cast< st_size_t >( dataptrs_obj_view->a );

        ASSERT_TRUE( kk < cmp_dataptrs_obj.size() );
        ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ kk ] );
        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            &cmp_dataptrs_obj[ kk ], dataptrs_obj_view ) );
    }
}

TEST( C99CommonCObjectsCBuffer,
      InitViewAddElementsRemapToAddrToFileFromFileBuffer )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;
    using raw_type  = st::cobj_raw_type;
    using real_type = ::NS(cobj_test_real_type);
    using uint_type = ::NS(cobj_test_uint64_type);
    using int_type  = ::NS(cobj_test_int64_type);
    using prng_seed_type = std::mt19937_64::result_type;

    /* --------------------------------------------------------------------- */

    st_size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    ASSERT_TRUE( slot_size > st_size_t{ 0 } );

    constexpr uint_type NUM_CMP_ELEMENTS = uint_type{ 64 };
    constexpr uint_type MIN_B_LENGTH     = uint_type{  5 };
    constexpr uint_type MAX_B_LENGTH     = uint_type{ 10 };
    constexpr uint_type MIN_C_LENGTH     = uint_type{  2 };
    constexpr uint_type MAX_C_LENGTH     = uint_type{ 16 };

    std::uniform_real_distribution< real_type > a_dist( -5.0, 5.0 );
    std::uniform_real_distribution< real_type > vec_dist( -42.0, +42.0 );
    std::uniform_int_distribution< uint_type >  u64_dist( 10, 100 );
    std::uniform_int_distribution< int_type >   i64_dist( -100, -2 );

    std::uniform_int_distribution< uint_type > b_length_dist(
        MIN_B_LENGTH, MAX_B_LENGTH );

    std::uniform_int_distribution< uint_type > c_length_dist(
        MIN_C_LENGTH, MAX_C_LENGTH );

    std::mt19937_64 prng( prng_seed_type{ 20210201 } );

    std::vector< ::NS(CObjTestNoPtrs) > cmp_no_ptrs_obj;
    cmp_no_ptrs_obj.reserve( NUM_CMP_ELEMENTS );

    std::vector< ::NS(CObjTestDataptrs) > cmp_dataptrs_obj;
    cmp_dataptrs_obj.reserve( NUM_CMP_ELEMENTS );

    std::vector< real_type > dataptrs_b_values(
        NUM_CMP_ELEMENTS * MAX_B_LENGTH, real_type{ 0. } );

    for( auto& v : dataptrs_b_values ) v = vec_dist( prng );

    std::vector< real_type > dataptrs_c_values(
        NUM_CMP_ELEMENTS * MAX_C_LENGTH, real_type{ 0. } );

    for( auto& v : dataptrs_c_values ) v = vec_dist( prng );

    uint_type dataptrs_b_offset = uint_type{ 0 };
    uint_type dataptrs_c_offset = uint_type{ 0 };

    st_size_t requ_n_slots = st_size_t{ 0 };
    st_size_t requ_n_objs  = NUM_CMP_ELEMENTS;
    st_size_t requ_n_ptrs  = NUM_CMP_ELEMENTS *
        ::NS(CObjTestDataptrs_cobj_num_dataptrs)();

    /* ---------------------------------------------------------------------- */

    for( uint_type ii = 0u ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        uint_type const b_capacity = b_length_dist( prng );
        uint_type b_length = b_length_dist( prng );
        if( b_length > b_capacity ) b_length = b_capacity;

        uint_type const c_capacity = c_length_dist( prng );
        uint_type c_length = c_length_dist( prng );
        if( c_length > c_capacity ) c_length = c_capacity;

        cmp_dataptrs_obj.push_back( ::NS(CObjTestDataptrs){ a_dist( prng ),
            b_capacity, b_length, reinterpret_cast< uintptr_t >(
                &dataptrs_b_values[ dataptrs_b_offset ] ),
            c_capacity, c_length, reinterpret_cast< uintptr_t >(
                &dataptrs_c_values[ dataptrs_c_offset ] ) } );

        dataptrs_b_offset += b_capacity;
        dataptrs_c_offset += c_capacity;

        requ_n_slots += ::NS(CObjTestDataptrs_cobj_required_num_bytes)(
            &cmp_dataptrs_obj.back(), slot_size ) / slot_size;
    }

    ASSERT_TRUE( ( ::NS(CObjTestDataptrs_cobj_reserved_handle_size)( slot_size
        ) / slot_size ) < requ_n_slots );

    st_size_t requ_capacity = ::NS(CObjFlatBuffer_predict_required_buffer_size)(
        requ_n_slots, requ_n_objs, requ_n_ptrs, st_size_t{ 0 }, slot_size );

    ASSERT_TRUE( requ_capacity > ::NS(CBuffer_min_buffer_size)( slot_size ) );

    /* --------------------------------------------------------------------- */

    std::vector< raw_type > flat_buffer( requ_capacity, raw_type{ 0 } );

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) view;
    ::NS(CBuffer_preset)( &view );

    ::NS(CBuffer_init_as_view)( &view, reinterpret_cast< uintptr_t >(
        flat_buffer.data() ), flat_buffer.size() );

    ASSERT_TRUE( ::NS(CBuffer_capacity)( &view ) >= requ_capacity );
    ASSERT_TRUE( ::NS(CBuffer_capacity)( &view ) <  requ_capacity + slot_size );

    /* --------------------------------------------------------------------- */

    uint_type ii = 0u;

    for( ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        cmp_dataptrs_obj[ ii ].a = static_cast< real_type >( ii );
        auto dataptrs_obj_view = ::NS(CObjTestDataptrs_cbuffer_add_copy)(
            &view, &cmp_dataptrs_obj[ ii ] );

        ASSERT_TRUE( dataptrs_obj_view != nullptr );
        ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ ii ] );
        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            &cmp_dataptrs_obj[ ii ], dataptrs_obj_view ) );
    }

    ASSERT_TRUE( ::NS(CBuffer_num_objects)( &view ) == NUM_CMP_ELEMENTS );

    for( ii = 0u ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        auto dataptrs_obj_view =
            ::NS(CObjTestDataptrs_const_from_cbuffer)( &view, ii );

        ASSERT_TRUE( dataptrs_obj_view != nullptr );
        st_size_t kk = static_cast< st_size_t >( dataptrs_obj_view->a );

        ASSERT_TRUE( kk < cmp_dataptrs_obj.size() );
        ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ kk ] );
        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            &cmp_dataptrs_obj[ kk ], dataptrs_obj_view ) );
    }

    std::string const PATH_TO_BINARY_FILE = std::string{
        "./cobj_test_dataptrs_view_normalised.bin" };

    st::cobj_addr_type const NORM_BASE_ADDR =
        ( ::NS(CBuffer_base_address)( &view ) != st::cobj_addr_type{ 0x1000 } )
        ? st::cobj_addr_type{ 0x1000 } : st::cobj_addr_type{ 0x2000 };

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CBuffer_to_file_normalised)(
        &view, PATH_TO_BINARY_FILE.c_str(), NORM_BASE_ADDR ) );

    ASSERT_TRUE( !::NS(CBuffer_needs_remapping)( &view ) );
    ASSERT_TRUE( ::NS(CBuffer_num_objects)( &view ) == NUM_CMP_ELEMENTS );

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* buffer1 =
        ::NS(CBuffer_new_from_file)( PATH_TO_BINARY_FILE.c_str() );

    ASSERT_TRUE( buffer1 != SIXTRL_NULLPTR );
    ASSERT_TRUE( ::NS(CBuffer_size)( buffer1 ) == ::NS(CBuffer_size)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_num_slots)( buffer1 ) ==
                 ::NS(CBuffer_num_slots)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_num_objects)( buffer1 ) ==
                 ::NS(CBuffer_num_objects)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_num_pointers)( buffer1 ) ==
                 ::NS(CBuffer_num_pointers)( &view ) );

    for( ii = 0u ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        auto dataptrs_obj_view =
            ::NS(CObjTestDataptrs_const_from_cbuffer)( &view, ii );

        ASSERT_TRUE( dataptrs_obj_view != nullptr );
        st_size_t kk = static_cast< st_size_t >( dataptrs_obj_view->a );

        ASSERT_TRUE( kk < cmp_dataptrs_obj.size() );
        ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ kk ] );
        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            &cmp_dataptrs_obj[ kk ], dataptrs_obj_view ) );

        auto dataptrs_obj_buffer1 =
            ::NS(CObjTestDataptrs_const_from_cbuffer)( buffer1, ii );

        ASSERT_TRUE( dataptrs_obj_buffer1 != nullptr );
        ASSERT_TRUE( dataptrs_obj_buffer1 != dataptrs_obj_view );
        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            dataptrs_obj_buffer1, dataptrs_obj_view ) );
    }

    /* Modify the first element in buffer1 so that it is different from the
     * first element in the binary dump and the view */

    ASSERT_TRUE( ::NS(CObjTestDataptrs_a)(
        ::NS(CObjTestDataptrs_const_from_cbuffer)( &view, 0 ) ) !=
            real_type{ 42.} );

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CObjTestDataptrs_set_a)(
        ::NS(CObjTestDataptrs_from_cbuffer)( buffer1, 0 ), real_type{ 42. } ) );

    ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
        ::NS(CObjTestDataptrs_const_from_cbuffer)( buffer1, 0 ),
        ::NS(CObjTestDataptrs_const_from_cbuffer)( &view, 0 ) ) != 0 );

    /* --------------------------------------------------------------------- */
    /* create a new minimal buffer and then in a second step load the binary
     * dump -> should be identical to the view */

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* buffer2 = ::NS(CBuffer_new)();
    ASSERT_TRUE( buffer2 != nullptr );
    ASSERT_TRUE( buffer2 != buffer1 );

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CBuffer_init_from_file)(
        buffer2, PATH_TO_BINARY_FILE.c_str() ) );

    ASSERT_TRUE( buffer2 != SIXTRL_NULLPTR );
    ASSERT_TRUE( ::NS(CBuffer_size)( buffer2 ) == ::NS(CBuffer_size)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_num_slots)( buffer2 ) ==
                 ::NS(CBuffer_num_slots)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_num_objects)( buffer2 ) ==
                 ::NS(CBuffer_num_objects)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_num_pointers)( buffer2 ) ==
                 ::NS(CBuffer_num_pointers)( &view ) );

    for( ii = 0u ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            ::NS(CObjTestDataptrs_const_from_cbuffer)( &view, ii ),
            ::NS(CObjTestDataptrs_const_from_cbuffer)( buffer2, ii ) ) == 0 );
    }

    /* re-init buffer1 from the binary dump -> should be identical again */

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CBuffer_init_from_file)(
        buffer1, PATH_TO_BINARY_FILE.c_str() ) );

    for( ii = 0u ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            ::NS(CObjTestDataptrs_const_from_cbuffer)( buffer1, ii ),
            ::NS(CObjTestDataptrs_const_from_cbuffer)( &view, ii ) ) == 0 );

        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            ::NS(CObjTestDataptrs_const_from_cbuffer)( buffer1, ii ),
            ::NS(CObjTestDataptrs_const_from_cbuffer)( buffer2, ii ) ) == 0 );
    }

    ::NS(CBuffer_delete)( buffer1 );
    ::NS(CBuffer_delete)( buffer2 );
}

TEST( C99CommonCObjectsCBuffer,
      InitViewAddElementsCreateViewAndBufferAsCopiesCompare )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;
    using raw_type  = st::cobj_raw_type;
    using real_type = ::NS(cobj_test_real_type);
    using uint_type = ::NS(cobj_test_uint64_type);
    using int_type  = ::NS(cobj_test_int64_type);
    using prng_seed_type = std::mt19937_64::result_type;

    /* --------------------------------------------------------------------- */

    st_size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    ASSERT_TRUE( slot_size > st_size_t{ 0 } );

    constexpr uint_type NUM_CMP_ELEMENTS = uint_type{ 64 };
    constexpr uint_type MIN_B_LENGTH     = uint_type{  5 };
    constexpr uint_type MAX_B_LENGTH     = uint_type{ 10 };
    constexpr uint_type MIN_C_LENGTH     = uint_type{  2 };
    constexpr uint_type MAX_C_LENGTH     = uint_type{ 16 };

    std::uniform_real_distribution< real_type > a_dist( -5.0, 5.0 );
    std::uniform_real_distribution< real_type > vec_dist( -42.0, +42.0 );
    std::uniform_int_distribution< uint_type >  u64_dist( 10, 100 );
    std::uniform_int_distribution< int_type >   i64_dist( -100, -2 );

    std::uniform_int_distribution< uint_type > b_length_dist(
        MIN_B_LENGTH, MAX_B_LENGTH );

    std::uniform_int_distribution< uint_type > c_length_dist(
        MIN_C_LENGTH, MAX_C_LENGTH );

    std::mt19937_64 prng( prng_seed_type{ 20210201 } );

    std::vector< ::NS(CObjTestNoPtrs) > cmp_no_ptrs_obj;
    cmp_no_ptrs_obj.reserve( NUM_CMP_ELEMENTS );

    std::vector< ::NS(CObjTestDataptrs) > cmp_dataptrs_obj;
    cmp_dataptrs_obj.reserve( NUM_CMP_ELEMENTS );

    std::vector< real_type > dataptrs_b_values(
        NUM_CMP_ELEMENTS * MAX_B_LENGTH, real_type{ 0. } );

    for( auto& v : dataptrs_b_values ) v = vec_dist( prng );

    std::vector< real_type > dataptrs_c_values(
        NUM_CMP_ELEMENTS * MAX_C_LENGTH, real_type{ 0. } );

    for( auto& v : dataptrs_c_values ) v = vec_dist( prng );

    uint_type dataptrs_b_offset = uint_type{ 0 };
    uint_type dataptrs_c_offset = uint_type{ 0 };

    st_size_t requ_n_slots = st_size_t{ 0 };
    st_size_t requ_n_objs  = NUM_CMP_ELEMENTS;
    st_size_t requ_n_ptrs  = NUM_CMP_ELEMENTS *
        ::NS(CObjTestDataptrs_cobj_num_dataptrs)();

    /* ---------------------------------------------------------------------- */

    for( uint_type ii = 0u ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        uint_type const b_capacity = b_length_dist( prng );
        uint_type b_length = b_length_dist( prng );
        if( b_length > b_capacity ) b_length = b_capacity;

        uint_type const c_capacity = c_length_dist( prng );
        uint_type c_length = c_length_dist( prng );
        if( c_length > c_capacity ) c_length = c_capacity;

        cmp_dataptrs_obj.push_back( ::NS(CObjTestDataptrs){ a_dist( prng ),
            b_capacity, b_length, reinterpret_cast< uintptr_t >(
                &dataptrs_b_values[ dataptrs_b_offset ] ),
            c_capacity, c_length, reinterpret_cast< uintptr_t >(
                &dataptrs_c_values[ dataptrs_c_offset ] ) } );

        dataptrs_b_offset += b_capacity;
        dataptrs_c_offset += c_capacity;

        requ_n_slots += ::NS(CObjTestDataptrs_cobj_required_num_bytes)(
            &cmp_dataptrs_obj.back(), slot_size ) / slot_size;
    }

    ASSERT_TRUE( ( ::NS(CObjTestDataptrs_cobj_reserved_handle_size)( slot_size
        ) / slot_size ) < requ_n_slots );

    st_size_t requ_capacity = ::NS(CObjFlatBuffer_predict_required_buffer_size)(
        requ_n_slots, requ_n_objs, requ_n_ptrs, st_size_t{ 0 }, slot_size );

    ASSERT_TRUE( requ_capacity > ::NS(CBuffer_min_buffer_size)( slot_size ) );

    /* --------------------------------------------------------------------- */

    std::vector< raw_type > flat_buffer( requ_capacity, raw_type{ 0 } );

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) view;
    ::NS(CBuffer_preset)( &view );

    ::NS(CBuffer_init_as_view)( &view, reinterpret_cast< uintptr_t >(
        flat_buffer.data() ), flat_buffer.size() );

    ASSERT_TRUE( ::NS(CBuffer_capacity)( &view ) >= requ_capacity );
    ASSERT_TRUE( ::NS(CBuffer_capacity)( &view ) <  requ_capacity + slot_size );

    /* --------------------------------------------------------------------- */

    uint_type ii = 0u;

    for( ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        cmp_dataptrs_obj[ ii ].a = static_cast< real_type >( ii );
        auto dataptrs_obj_view = ::NS(CObjTestDataptrs_cbuffer_add_copy)(
            &view, &cmp_dataptrs_obj[ ii ] );

        ASSERT_TRUE( dataptrs_obj_view != nullptr );
        ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ ii ] );
        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            &cmp_dataptrs_obj[ ii ], dataptrs_obj_view ) );
    }

    ASSERT_TRUE( ::NS(CBuffer_num_objects)( &view ) == NUM_CMP_ELEMENTS );

    for( ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            ::NS(CObjTestDataptrs_const_from_cbuffer)( &view, ii ),
            &cmp_dataptrs_obj[ ii ] ) == 0 );
    }

    /* Create a buffer as a copy */

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* buffer =
        ::NS(CBuffer_new_as_copy)( &view );

    ASSERT_TRUE( buffer != nullptr );
    ASSERT_TRUE( !::NS(CBuffer_needs_remapping)( buffer ) );
    ASSERT_TRUE( ::NS(CBuffer_slot_size)( buffer ) ==
                 ::NS(CBuffer_slot_size)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_size)( buffer ) == ::NS(CBuffer_size)( &view ) );
    ASSERT_TRUE( ::NS(CBuffer_p_const_base)( buffer ) != nullptr );
    ASSERT_TRUE( ::NS(CBuffer_p_const_base)( buffer ) !=
                 ::NS(CBuffer_p_const_base)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_capacity)( buffer ) >=
                 ::NS(CBuffer_size)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_num_slots)( buffer ) ==
                 ::NS(CBuffer_num_slots)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_num_objects)( buffer ) ==
                 ::NS(CBuffer_num_objects)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_num_pointers)( buffer ) ==
                 ::NS(CBuffer_num_pointers)( &view ) );

    /* Create a view as a copy */

    std::vector< raw_type > copy_flat_buffer(
        flat_buffer.size(), raw_type{ 0 } );

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) view_cpy;
    ::NS(CBuffer_preset)( &view_cpy );
    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CBuffer_init_as_view)(
        &view_cpy, reinterpret_cast< uintptr_t >( copy_flat_buffer.data() ),
            copy_flat_buffer.size() ) );

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CBuffer_init_as_copy_of_cbuffer)(
        &view_cpy, &view ) );

    ASSERT_TRUE( !::NS(CBuffer_needs_remapping)( &view_cpy ) );
    ASSERT_TRUE( ::NS(CBuffer_slot_size)( &view_cpy ) ==
                 ::NS(CBuffer_slot_size)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_size)( &view_cpy ) == ::NS(CBuffer_size)( &view ) );
    ASSERT_TRUE( ::NS(CBuffer_p_const_base)( &view_cpy ) != nullptr );
    ASSERT_TRUE( ::NS(CBuffer_p_const_base)( &view_cpy ) !=
                 ::NS(CBuffer_p_const_base)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_capacity)( &view_cpy ) >=
                 ::NS(CBuffer_size)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_num_slots)( &view_cpy ) ==
                 ::NS(CBuffer_num_slots)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_num_objects)( &view_cpy ) ==
                 ::NS(CBuffer_num_objects)( &view ) );

    ASSERT_TRUE( ::NS(CBuffer_num_pointers)( &view_cpy ) ==
                 ::NS(CBuffer_num_pointers)( &view ) );


    for( ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            ::NS(CObjTestDataptrs_const_from_cbuffer)( &view, ii ),
            &cmp_dataptrs_obj[ ii ] ) == 0 );

        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            ::NS(CObjTestDataptrs_const_from_cbuffer)( &view_cpy, ii ),
            &cmp_dataptrs_obj[ ii ] ) == 0 );

        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            ::NS(CObjTestDataptrs_const_from_cbuffer)( buffer, ii ),
            &cmp_dataptrs_obj[ ii ] ) == 0 );
    }

    ::NS(CBuffer_delete)( buffer );
}
