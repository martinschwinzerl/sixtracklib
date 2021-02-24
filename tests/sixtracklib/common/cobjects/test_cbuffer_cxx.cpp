#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cmath>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/testlib.hpp"

/* ************************************************************************* */

TEST( CXXCommonCObjectsCBuffer, InitAsViewOnExistingFlatBuffer )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using view_type = st::CBufferView;
    using raw_type  = view_type::raw_type;
    using st_size_t = view_type::size_type;

    st_size_t const slot_size = view_type::DEFAULT_SLOT_SIZE;

    std::vector< raw_type > too_small_data_buffer(
        view_type::MIN_BUFFER_SIZE( slot_size ) - st_size_t{ 1u },
        raw_type{ 0 } );

    std::vector< raw_type > flat_buffer(
        st_size_t{ 1 } << st_size_t{ 20 }, raw_type{ 0 } );

    view_type view_too_small( reinterpret_cast< uintptr_t >(
        too_small_data_buffer.data() ), too_small_data_buffer.size(),
            slot_size );

    ASSERT_TRUE(  view_too_small.base_address() == view_type::NULL_ADDRESS );
    ASSERT_TRUE(  view_too_small.capacity() == st_size_t{ 0 } );
    ASSERT_FALSE( view_too_small.allow_remap() );
    ASSERT_FALSE( view_too_small.allow_allocate() );
    ASSERT_FALSE( view_too_small.allow_realloc() );
    ASSERT_FALSE( view_too_small.allow_remap() );
    ASSERT_FALSE( view_too_small.owns_stored_data() );

    view_type view( reinterpret_cast< uintptr_t >(
        flat_buffer.data() ), flat_buffer.size(), slot_size );

    ASSERT_TRUE( view.base_address() != view_type::NULL_ADDRESS );
    ASSERT_TRUE(  view.p_const_base() != nullptr );
    ASSERT_TRUE(  view.capacity() > view_type::MIN_BUFFER_SIZE( slot_size ) );
    ASSERT_TRUE(  view.capacity() <= flat_buffer.size() );
    ASSERT_TRUE(  view.size() == view_type::MIN_BUFFER_SIZE( slot_size ) );
    ASSERT_TRUE(  view.allow_remap() );
    ASSERT_TRUE(  view.allow_allocate() );
    ASSERT_TRUE(  view.allow_append() );
    ASSERT_FALSE( view.owns_stored_data() );
}

TEST( CXXCommonCObjectsCBuffer, InitAsBufferMinCapacity )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using buffer_type = st::CBuffer;
    using st_size_t = buffer_type::size_type;

    st_size_t const slot_size = buffer_type::DEFAULT_SLOT_SIZE;

    buffer_type buffer;

    ASSERT_TRUE(  buffer.base_address() != buffer_type::NULL_ADDRESS );
    ASSERT_TRUE(  buffer.p_const_base() != nullptr );
    ASSERT_TRUE(  buffer.capacity() >=
                  buffer_type::MIN_BUFFER_SIZE( slot_size ) );
    ASSERT_TRUE(  buffer.size() ==
                  buffer_type::MIN_BUFFER_SIZE( slot_size ) );
    ASSERT_TRUE(  buffer.allow_remap() );
    ASSERT_TRUE(  buffer.allow_allocate() );
    ASSERT_TRUE(  buffer.allow_append() );
    ASSERT_TRUE(  buffer.owns_stored_data() );
}

TEST( CXXCommonCObjectsCBuffer, InitAsBufferWithCapacity )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using buffer_type = st::CBuffer;
    using st_size_t = buffer_type::size_type;

    st_size_t const slot_size = buffer_type::DEFAULT_SLOT_SIZE;
    st_size_t const requ_capacity = st_size_t{ 1 } << st_size_t{ 20 };
    ASSERT_TRUE( requ_capacity > buffer_type::MIN_BUFFER_SIZE( slot_size ) );

    buffer_type buffer( requ_capacity );

    ASSERT_TRUE(  buffer.base_address() != buffer_type::NULL_ADDRESS );
    ASSERT_TRUE(  buffer.p_const_base() != nullptr );
    ASSERT_TRUE(  buffer.capacity() >= requ_capacity );
    ASSERT_TRUE(  buffer.size() ==
                  buffer_type::MIN_BUFFER_SIZE( slot_size ) );
    ASSERT_TRUE(  buffer.allow_remap() );
    ASSERT_TRUE(  buffer.allow_allocate() );
    ASSERT_TRUE(  buffer.allow_append() );
    ASSERT_TRUE(  buffer.owns_stored_data() );
}

TEST( CXXCommonCObjectsCBuffer, InitViewAndBufferAddElementsReserveCompare )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using view_type   = st::CBufferView;
    using buffer_type = st::CBuffer;
    using st_size_t   = view_type::size_type;
    using raw_type    = view_type::raw_type;
    using real_type   = ::NS(cobj_test_real_type);
    using uint_type   = ::NS(cobj_test_uint64_type);
    using int_type    = ::NS(cobj_test_int64_type);

    using prng_seed_type = std::mt19937_64::result_type;

    static_assert( st::CObjects_has_legal_id< ::NS(CObjTestNoPtrs) >(),
        "::NS(CObjTestNoPtrs) required to be a legal cobjects type" );

    static_assert( st::CObjects_has_legal_id< ::NS(CObjTestDataptrs) >(),
        "::NS(CObjTestDataptrs) required to be a legal cobjects type" );

    ASSERT_TRUE( st::CObjects_type_id< ::NS(CObjTestNoPtrs) >() ==
                 ::NS(CObjTestNoPtrs_cobj_type_id)() );

    /* --------------------------------------------------------------------- */

    std::vector< raw_type > flat_buffer(
        st_size_t{ 1 } << st_size_t{ 20 }, raw_type{ 0 } );

    view_type view( reinterpret_cast< uintptr_t >( flat_buffer.data() ),
                    flat_buffer.size() );

    st_size_t const slot_size = view.slot_size();

    ASSERT_TRUE(  view.p_const_base() != nullptr );
    ASSERT_TRUE(  view.base_address() % slot_size == st_size_t{ 0 } );
    ASSERT_TRUE( !view.needs_remapping() );
    ASSERT_TRUE(  view.capacity() == flat_buffer.size() );
    ASSERT_TRUE(  view.size() == view_type::MIN_BUFFER_SIZE( slot_size ) );

    st_size_t prev_n_slots = view.num_slots();
    st_size_t prev_n_objs  = view.num_objects();
    st_size_t prev_n_ptrs  = view.num_pointers();

    ASSERT_TRUE( view.num_slots()    == st_size_t{ 0 } );
    ASSERT_TRUE( view.num_objects()  == st_size_t{ 0 } );
    ASSERT_TRUE( view.num_pointers() == st_size_t{ 0 } );
    ASSERT_TRUE( view.num_garbage()  == st_size_t{ 0 } );

    ASSERT_TRUE( view.max_slots()    == st_size_t{ 0 } );
    ASSERT_TRUE( view.max_objects()  == st_size_t{ 0 } );
    ASSERT_TRUE( view.max_pointers() == st_size_t{ 0 } );
    ASSERT_TRUE( view.max_garbage()  == st_size_t{ 0 } );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    buffer_type buffer;

    ASSERT_TRUE(  buffer.slot_size() > st_size_t{ 0 } );
    ASSERT_TRUE(  buffer.slot_size() == slot_size );
    ASSERT_TRUE(  buffer.p_const_base() != nullptr );
    ASSERT_TRUE(  buffer.base_address() % slot_size == st_size_t{ 0 } );

    ASSERT_TRUE( !buffer.needs_remapping() );
    ASSERT_TRUE(  buffer.size() >= buffer_type::MIN_BUFFER_SIZE( slot_size ) );

    prev_n_slots = buffer.num_slots();
    prev_n_objs  = buffer.num_objects();
    prev_n_ptrs  = buffer.num_pointers();

    ASSERT_TRUE( buffer.num_slots()    == st_size_t{ 0 } );
    ASSERT_TRUE( buffer.num_objects()  == st_size_t{ 0 } );
    ASSERT_TRUE( buffer.num_pointers() == st_size_t{ 0 } );
    ASSERT_TRUE( buffer.num_garbage()  == st_size_t{ 0 } );

    ASSERT_TRUE( buffer.max_slots()    == st_size_t{ 0 } );
    ASSERT_TRUE( buffer.max_objects()  == st_size_t{ 0 } );
    ASSERT_TRUE( buffer.max_pointers() == st_size_t{ 0 } );
    ASSERT_TRUE( buffer.max_garbage()  == st_size_t{ 0 } );

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

    prev_n_slots = view.num_slots();
    prev_n_objs  = view.num_objects();
    prev_n_ptrs  = view.num_pointers();

    st_size_t n_slots = prev_n_slots;
    st_size_t n_objs  = prev_n_objs;
    st_size_t n_ptrs  = prev_n_ptrs;

    for( uint_type ii = 0u ; ii < NUM_CMP_ELEMENTS ; ii += 2u )
    {
        for( uint_type jj = 0u, kk = ii ; jj < 2 ; ++jj, ++kk )
        {
            cmp_no_ptrs_obj[ kk ].a = static_cast< real_type >( kk );

            auto noptrs_obj_view = view.add_copy< ::NS(CObjTestNoPtrs) >(
                cmp_no_ptrs_obj[ kk ] );

            ASSERT_TRUE( noptrs_obj_view != nullptr );
            ASSERT_TRUE( noptrs_obj_view != &cmp_no_ptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestNoPtrs_compare)(
                &cmp_no_ptrs_obj[ kk ], noptrs_obj_view ) );

            n_slots = view.num_slots();
            n_objs  = view.num_objects();
            n_ptrs  = view.num_pointers();

            ASSERT_TRUE( prev_n_objs + st_size_t{ 1 } == n_objs );
            ASSERT_TRUE( prev_n_ptrs + ::NS(CObjTestNoPtrs_cobj_num_dataptrs)()
                         == n_ptrs );
            ASSERT_TRUE( n_slots == prev_n_slots + (
                ::NS(CObjTestNoPtrs_cobj_required_num_bytes)( noptrs_obj_view,
                    slot_size ) / slot_size ) );

            ASSERT_TRUE( view.max_slots() >= n_slots );
            ASSERT_TRUE( view.max_objects() >= n_objs );
            ASSERT_TRUE( view.max_pointers() >= n_ptrs );

            auto noptrs_obj_buffer = buffer.add_copy< ::NS(CObjTestNoPtrs) >(
                cmp_no_ptrs_obj[ kk ] );

            ASSERT_TRUE( noptrs_obj_buffer != nullptr );
            ASSERT_TRUE( noptrs_obj_buffer != noptrs_obj_view );
            ASSERT_TRUE( noptrs_obj_buffer != &cmp_no_ptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestNoPtrs_compare)(
                            &cmp_no_ptrs_obj[ kk ], noptrs_obj_buffer ) );

            ASSERT_TRUE( n_slots == buffer.num_slots() );
            ASSERT_TRUE( n_objs  == buffer.num_objects() );
            ASSERT_TRUE( n_ptrs  == buffer.num_pointers() );

            prev_n_slots = n_slots;
            prev_n_objs  = n_objs;
            prev_n_ptrs  = n_ptrs;
        }

        for( uint_type jj = 0u, kk = ii ; jj < 2 ; ++jj, ++kk )
        {
            cmp_dataptrs_obj[ kk ].a = static_cast< real_type >( kk );
            auto dataptrs_obj_view = view.add_copy< ::NS(CObjTestDataptrs) >(
                cmp_dataptrs_obj[ kk ] );
            ASSERT_TRUE( dataptrs_obj_view != nullptr );
            ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
                            &cmp_dataptrs_obj[ kk ], dataptrs_obj_view ) );

            n_slots = view.num_slots();
            n_objs  = view.num_objects();
            n_ptrs  = view.num_pointers();

            ASSERT_TRUE( prev_n_objs + st_size_t{ 1 } == n_objs );
            ASSERT_TRUE( prev_n_ptrs + ::NS(CObjTestDataptrs_cobj_num_dataptrs)()
                         == n_ptrs );
            ASSERT_TRUE( n_slots == prev_n_slots + (
                ::NS(CObjTestDataptrs_cobj_required_num_bytes)(
                    dataptrs_obj_view, slot_size ) / slot_size ) );

            auto dataptrs_obj_buffer = buffer.add_copy< ::NS(CObjTestDataptrs) >(
                cmp_dataptrs_obj[ kk ] );
            ASSERT_TRUE( dataptrs_obj_buffer != nullptr );
            ASSERT_TRUE( dataptrs_obj_buffer != dataptrs_obj_view );
            ASSERT_TRUE( dataptrs_obj_buffer != &cmp_dataptrs_obj[ kk ] );

            ASSERT_TRUE( n_slots == buffer.num_slots() );
            ASSERT_TRUE( n_objs  == buffer.num_objects() );
            ASSERT_TRUE( n_ptrs  == buffer.num_pointers() );
            ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
                            &cmp_dataptrs_obj[ kk ], dataptrs_obj_buffer ) );

            prev_n_slots = n_slots;
            prev_n_objs  = n_objs;
            prev_n_ptrs  = n_ptrs;
        }
    }

    ASSERT_TRUE( view.num_objects() == 2 * NUM_CMP_ELEMENTS );
    ASSERT_TRUE( buffer.num_objects() == 2 * NUM_CMP_ELEMENTS );

    /* --------------------------------------------------------------------- */

    n_objs = view.num_objects();

    for( st_size_t ii = st_size_t{ 0 } ; ii < n_objs ; ++ii )
    {
        st_size_t const jj = ii % st_size_t{ 4 };

        if( jj < st_size_t{ 2 } )
        {
            auto noptrs_obj_view = view.get_const_object<
                ::NS(CObjTestNoPtrs) >( ii );

            ASSERT_TRUE( noptrs_obj_view != nullptr );
            st_size_t kk = static_cast< st_size_t >( noptrs_obj_view->a );

            ASSERT_TRUE( kk < cmp_no_ptrs_obj.size() );
            ASSERT_TRUE( noptrs_obj_view != &cmp_no_ptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestNoPtrs_compare)(
                            &cmp_no_ptrs_obj[ kk ], noptrs_obj_view ) );

            auto noptrs_obj_buffer = ::NS(CObjTestNoPtrs_const_from_cbuffer)(
                buffer.as_c_api(), ii );

            ASSERT_TRUE( noptrs_obj_buffer != nullptr );
            ASSERT_TRUE( noptrs_obj_buffer != noptrs_obj_view );
            ASSERT_TRUE( noptrs_obj_buffer != &cmp_no_ptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestNoPtrs_compare)(
                noptrs_obj_buffer, noptrs_obj_view ) );
        }
        else
        {
            auto dataptrs_obj_view = view.get_const_object<
                ::NS(CObjTestDataptrs) >( ii );

            ASSERT_TRUE( dataptrs_obj_view != nullptr );
            st_size_t kk = static_cast< st_size_t >( dataptrs_obj_view->a );

            ASSERT_TRUE( kk < cmp_dataptrs_obj.size() );
            ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
                            &cmp_dataptrs_obj[ kk ], dataptrs_obj_view ) );

            auto dataptrs_obj_buffer = ::NS(CObjTestDataptrs_const_from_cbuffer)(
                buffer.as_c_api(), ii );

            ASSERT_TRUE( dataptrs_obj_buffer != nullptr );
            ASSERT_TRUE( dataptrs_obj_buffer != dataptrs_obj_view );
            ASSERT_TRUE( dataptrs_obj_buffer != &cmp_dataptrs_obj[ kk ] );
            ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
                dataptrs_obj_buffer, dataptrs_obj_view ) );
        }
    }
}

TEST( CXXCommonCObjectsCBuffer, InitAsViewNotEnoughCapacity )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using view_type   = st::CBufferView;
    using st_size_t   = view_type::size_type;
    using raw_type    = view_type::raw_type;
    using real_type   = ::NS(cobj_test_real_type);
    using uint_type   = ::NS(cobj_test_uint64_type);
    using int_type    = ::NS(cobj_test_int64_type);

    using prng_seed_type = std::mt19937_64::result_type;

    static_assert( st::CObjects_has_legal_id< ::NS(CObjTestDataptrs) >(),
        "::NS(CObjTestDataptrs) required to be a legal cobjects type" );

    ASSERT_TRUE( st::CObjects_type_id< ::NS(CObjTestDataptrs) >() ==
                 ::NS(CObjTestDataptrs_cobj_type_id)() );

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

    ASSERT_TRUE( requ_capacity > view_type::MIN_BUFFER_SIZE( slot_size ) );

    /* --------------------------------------------------------------------- */

    std::vector< raw_type > flat_buffer( requ_capacity, raw_type{ 0 } );

    st::CBufferView view( reinterpret_cast< uintptr_t >(
        flat_buffer.data() ), flat_buffer.size(), slot_size );

    ASSERT_TRUE( view.capacity() >= requ_capacity );
    ASSERT_TRUE( view.capacity() <  requ_capacity + slot_size );

    /* --------------------------------------------------------------------- */

    typedef typename st::CObjectsStoreResultTypeTraits<
        ::NS(CObjTestDataptrs) >::pointer dataptrs_obj_pointer;

    typedef typename st::CObjectsStoreResultTypeTraits<
        ::NS(CObjTestDataptrs) >::const_pointer dataptrs_obj_const_pointer;

    uint_type ii = 0u;

    for( ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        cmp_dataptrs_obj[ ii ].a = static_cast< real_type >( ii );
        dataptrs_obj_pointer dataptrs_obj_view = nullptr;

        if( ( ii % 2u ) == 0u )
        {
            dataptrs_obj_view = ::NS(CObjTestDataptrs_cbuffer_add_copy)(
                view.as_c_api(), &cmp_dataptrs_obj[ ii ] );
        }
        else
        {
            dataptrs_obj_view = view.add_copy< ::NS(CObjTestDataptrs) >(
                cmp_dataptrs_obj[ ii ] );
        }

        ASSERT_TRUE( dataptrs_obj_view != nullptr );
        ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ ii ] );
        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            &cmp_dataptrs_obj[ ii ], dataptrs_obj_view ) );
    }

    for( ; ii < NUM_ELEM_TO_ADD ; ++ii )
    {
        cmp_dataptrs_obj[ ii ].a = static_cast< real_type >( ii );

        dataptrs_obj_pointer dataptrs_obj_view = nullptr;

        if( ( ii % 2u ) == 0u )
        {
            dataptrs_obj_view = ::NS(CObjTestDataptrs_cbuffer_add_copy)(
                view.as_c_api(), &cmp_dataptrs_obj[ ii ] );
        }
        else
        {
            dataptrs_obj_view = view.add_copy< ::NS(CObjTestDataptrs) >(
                cmp_dataptrs_obj[ ii ] );
        }

        ASSERT_TRUE( dataptrs_obj_view == nullptr );
    }

    ASSERT_TRUE( view.num_objects() == NUM_CMP_ELEMENTS );

    for( ii = 0u ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        dataptrs_obj_const_pointer dataptrs_obj_view = nullptr;

        if( ( ii % 2u ) == 0u )
        {
            dataptrs_obj_view = ::NS(CObjTestDataptrs_const_from_cbuffer)(
                view.as_c_api(), ii );
        }
        else
        {
            dataptrs_obj_view = view.get_const_object<
                ::NS(CObjTestDataptrs) >( ii );
        }

        ASSERT_TRUE( dataptrs_obj_view != nullptr );
        st_size_t kk = static_cast< st_size_t >( dataptrs_obj_view->a );

        ASSERT_TRUE( kk < cmp_dataptrs_obj.size() );
        ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ kk ] );
        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            &cmp_dataptrs_obj[ kk ], dataptrs_obj_view ) );
    }
}

TEST( CXXCommonCObjectsCBuffer,
      InitViewAddElementsRemapToAddrToFileFromFileBuffer )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using view_type   = st::CBufferView;
    using st_size_t   = view_type::size_type;
    using raw_type    = view_type::raw_type;
    using real_type   = ::NS(cobj_test_real_type);
    using uint_type   = ::NS(cobj_test_uint64_type);
    using int_type    = ::NS(cobj_test_int64_type);

    using prng_seed_type = std::mt19937_64::result_type;

    static_assert( st::CObjects_has_legal_id< ::NS(CObjTestDataptrs) >(),
        "::NS(CObjTestDataptrs) required to be a legal cobjects type" );

    ASSERT_TRUE( st::CObjects_type_id< ::NS(CObjTestDataptrs) >() ==
                 ::NS(CObjTestDataptrs_cobj_type_id)() );

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

    ASSERT_TRUE( requ_capacity > view_type::MIN_BUFFER_SIZE( slot_size ) );

    /* --------------------------------------------------------------------- */

    std::vector< raw_type > flat_buffer( requ_capacity, raw_type{ 0 } );

    st::CBufferView view( reinterpret_cast< uintptr_t >( flat_buffer.data() ),
        flat_buffer.size(), slot_size );

    ASSERT_TRUE( view.capacity() >= requ_capacity );
    ASSERT_TRUE( view.capacity() <  requ_capacity + slot_size );

    /* --------------------------------------------------------------------- */

    typedef typename st::CObjectsStoreResultTypeTraits<
        ::NS(CObjTestDataptrs) >::pointer dataptrs_obj_pointer;

    typedef typename st::CObjectsStoreResultTypeTraits<
        ::NS(CObjTestDataptrs) >::const_pointer dataptrs_obj_const_pointer;

    uint_type ii = 0u;

    for( ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        cmp_dataptrs_obj[ ii ].a = static_cast< real_type >( ii );

        dataptrs_obj_pointer dataptrs_obj_view = nullptr;

        if( ( ii % 2 ) == 0u )
        {
            dataptrs_obj_view = ::NS(CObjTestDataptrs_cbuffer_add_copy)(
                view.as_c_api(), &cmp_dataptrs_obj[ ii ] );
        }
        else
        {
            dataptrs_obj_view = view.add_copy< ::NS(CObjTestDataptrs) >(
                cmp_dataptrs_obj[ ii ] );
        }

        ASSERT_TRUE( dataptrs_obj_view != nullptr );
        ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ ii ] );
        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            &cmp_dataptrs_obj[ ii ], dataptrs_obj_view ) );
    }

    ASSERT_TRUE( view.num_objects() == NUM_CMP_ELEMENTS );

    for( ii = 0u ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        dataptrs_obj_const_pointer dataptrs_obj_view = nullptr;

        if( ( ii % 2u ) == 0u )
        {
            dataptrs_obj_view = ::NS(CObjTestDataptrs_const_from_cbuffer)(
                view.as_c_api(), ii );
        }
        else
        {
            dataptrs_obj_view = view.get_const_object<
                ::NS(CObjTestDataptrs) >( ii );
        }

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
        ( view.base_address() != st::cobj_addr_type{ 0x1000 } )
        ? st::cobj_addr_type{ 0x1000 } : st::cobj_addr_type{ 0x2000 };

    ASSERT_TRUE( st::STATUS_SUCCESS == st::CBuffer_to_file_normalised(
        view, PATH_TO_BINARY_FILE, NORM_BASE_ADDR ) );

    ASSERT_TRUE( !view.needs_remapping() );
    ASSERT_TRUE( view.num_objects() == NUM_CMP_ELEMENTS );

    st::CBuffer buffer1( PATH_TO_BINARY_FILE );

    ASSERT_TRUE( buffer1.size() == view.size() );

    ASSERT_TRUE( buffer1.num_slots() ==
                 view.num_slots() );

    ASSERT_TRUE( buffer1.num_objects() ==
                 view.num_objects() );

    ASSERT_TRUE( buffer1.num_pointers() ==
                 view.num_pointers() );

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

        auto dataptrs_obj_buffer1 = buffer1.get_object<
            ::NS(CObjTestDataptrs) >( ii );

        ASSERT_TRUE( dataptrs_obj_buffer1 != nullptr );
        ASSERT_TRUE( dataptrs_obj_buffer1 != dataptrs_obj_view );
        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            dataptrs_obj_buffer1, dataptrs_obj_view ) );
    }

    /* Modify the first element in buffer1 so that it is different from the
     * first element in the binary dump and the view */

    ASSERT_TRUE( ::NS(CObjTestDataptrs_a)( view.get_object<
        ::NS(CObjTestDataptrs) >( 0 ) ) != real_type{ 42.} );

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CObjTestDataptrs_set_a)(
        buffer1.get_object< ::NS(CObjTestDataptrs) >( 0 ), real_type{ 42. } ) );

    ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
        buffer1.get_const_object< ::NS(CObjTestDataptrs) >( 0 ),
        view.get_const_object< ::NS(CObjTestDataptrs) >( 0 ) ) != 0 );

    /* --------------------------------------------------------------------- */
    /* create a new minimal buffer and then in a second step load the binary
     * dump -> should be identical to the view */

    st::CBuffer buffer2;

    ASSERT_TRUE( st::STATUS_SUCCESS == st::CBuffer_from_file(
        buffer2, PATH_TO_BINARY_FILE ) );

    ASSERT_TRUE( buffer2.size() == view.size() );

    ASSERT_TRUE( buffer2.num_slots() ==
                 view.num_slots() );

    ASSERT_TRUE( buffer2.num_objects() ==
                 view.num_objects() );

    ASSERT_TRUE( buffer2.num_pointers() ==
                 view.num_pointers() );

    for( ii = 0u ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            view.get_const_object< ::NS(CObjTestDataptrs) >( ii ),
            buffer2.get_const_object< ::NS(CObjTestDataptrs) >( ii ) ) == 0 );
    }

    /* re-init buffer1 from the binary dump -> should be identical again */

    ASSERT_TRUE( st::STATUS_SUCCESS ==
                 buffer1.from_file( PATH_TO_BINARY_FILE ) );

    for( ii = 0u ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            view.get_const_object< ::NS(CObjTestDataptrs) >( ii ),
            buffer1.get_const_object< ::NS(CObjTestDataptrs) >( ii ) ) == 0 );

        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            view.get_const_object< ::NS(CObjTestDataptrs) >( ii ),
            buffer2.get_const_object< ::NS(CObjTestDataptrs) >( ii ) ) == 0 );
    }
}

TEST( CXXCommonCObjectsCBuffer,
      InitViewAddElementsCreateViewAndBufferAsCopiesCompare )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using view_type   = st::CBufferView;
    using st_size_t   = view_type::size_type;
    using raw_type    = view_type::raw_type;
    using real_type   = ::NS(cobj_test_real_type);
    using uint_type   = ::NS(cobj_test_uint64_type);
    using int_type    = ::NS(cobj_test_int64_type);

    using prng_seed_type = std::mt19937_64::result_type;

    static_assert( st::CObjects_has_legal_id< ::NS(CObjTestDataptrs) >(),
        "::NS(CObjTestDataptrs) required to be a legal cobjects type" );

    ASSERT_TRUE( st::CObjects_type_id< ::NS(CObjTestDataptrs) >() ==
                 ::NS(CObjTestDataptrs_cobj_type_id)() );

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
        requ_n_slots, requ_n_objs, requ_n_ptrs, st_size_t { 0 }, slot_size );

    ASSERT_TRUE( requ_capacity > st::CBufferView::MIN_BUFFER_SIZE( slot_size ) );

    /* --------------------------------------------------------------------- */

    std::vector< raw_type > flat_buffer( requ_capacity, raw_type{ 0 } );

    st::CBufferView view( reinterpret_cast< uintptr_t >(
        flat_buffer.data() ), flat_buffer.size(), slot_size );

    ASSERT_TRUE( view.capacity() >= requ_capacity );
    ASSERT_TRUE( view.capacity() <  requ_capacity + slot_size );

    /* --------------------------------------------------------------------- */

    uint_type ii = 0u;

    for( ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        cmp_dataptrs_obj[ ii ].a = static_cast< real_type >( ii );
        auto dataptrs_obj_view = view.add_copy< ::NS(CObjTestDataptrs) >(
            cmp_dataptrs_obj[ ii ] );

        ASSERT_TRUE( dataptrs_obj_view != nullptr );
        ASSERT_TRUE( dataptrs_obj_view != &cmp_dataptrs_obj[ ii ] );
        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            &cmp_dataptrs_obj[ ii ], dataptrs_obj_view ) );
    }

    ASSERT_TRUE( view.num_objects() == NUM_CMP_ELEMENTS );

    for( ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            view.get_object< ::NS(CObjTestDataptrs) >( ii ),
            &cmp_dataptrs_obj[ ii ] ) == 0 );
    }

    /* Create a buffer as a copy */

    st::CBuffer buffer;
    buffer = view;

    ASSERT_TRUE( !buffer.needs_remapping() );
    ASSERT_TRUE( buffer.slot_size() == view.slot_size() );

    ASSERT_TRUE( buffer.size() == view.size() );
    ASSERT_TRUE( buffer.p_const_base() != nullptr );
    ASSERT_TRUE( buffer.p_const_base() != view.p_const_base() );
    ASSERT_TRUE( buffer.capacity() >= view.size() );

    ASSERT_TRUE( buffer.num_slots() == view.num_slots() );
    ASSERT_TRUE( buffer.num_objects() == view.num_objects() );
    ASSERT_TRUE( buffer.num_pointers() == view.num_pointers() );

    /* Create a view as a copy */

    std::vector< raw_type > copy_flat_buffer(
        flat_buffer.size(), raw_type{ 0 } );

    st::CBufferView view_cpy( reinterpret_cast< uintptr_t >(
        copy_flat_buffer.data() ), copy_flat_buffer.size(), slot_size );

    view_cpy = view;

    ASSERT_TRUE( !view_cpy.needs_remapping() );
    ASSERT_TRUE( view_cpy.slot_size() == view.slot_size() );
    ASSERT_TRUE( view_cpy.size() == view.size() );
    ASSERT_TRUE( view_cpy.p_const_base() != nullptr );
    ASSERT_TRUE( view_cpy.p_const_base() != view.p_const_base() );
    ASSERT_TRUE( view_cpy.capacity() >= view.size() );
    ASSERT_TRUE( view_cpy.num_slots() == view.num_slots() );
    ASSERT_TRUE( view_cpy.num_objects() == view.num_objects() );
    ASSERT_TRUE( view_cpy.num_pointers() == view.num_pointers() );

    for( ; ii < NUM_CMP_ELEMENTS ; ++ii )
    {
        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            ::NS(CObjTestDataptrs_const_from_cbuffer)( view.as_c_api(), ii ),
            &cmp_dataptrs_obj[ ii ] ) == 0 );

        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            view_cpy.get_object< ::NS(CObjTestDataptrs) >( ii ),
            &cmp_dataptrs_obj[ ii ] ) == 0 );

        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)(
            buffer.get_object< ::NS(CObjTestDataptrs) >( ii ),
            &cmp_dataptrs_obj[ ii ] ) == 0 );
    }
}
