#include "sixtracklib/common/cobjects/cbuffer_view.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/testlib.h"
#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/testlib/common/cobjects/type_no_ptrs.h"
#include "sixtracklib/testlib/common/cobjects/type_no_ptrs_init.h"
#include "sixtracklib/testlib/common/cobjects/type_const_num_ptrs.h"
#include "sixtracklib/testlib/common/cobjects/type_const_num_ptrs_init.h"

TEST( CxxCommonCObjectsCBufferViewLoadObjectsTests, BasicUsageTypeNoPtrs )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using st_size_t = st::cobj_size_t;
    using obj_t = st::tests::TypeNoPtrs;

    st_size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    st_size_t const ext_buffer_capacity = ::NS(CObjFlatBuffer_slot_based_size)(
        st_size_t{ 1 << 20 }, slot_size );

    std::vector< st::cobj_raw_t > ext_buffer(
        ext_buffer_capacity + slot_size );

    std::uintptr_t const store_addr = reinterpret_cast<
        std::uintptr_t >( ext_buffer.data() );

    std::uintptr_t const remainder = store_addr % slot_size;
    std::uintptr_t const base_addr = store_addr + ( slot_size - remainder );

    /* --------------------------------------------------------------------- */

    st::CBufferView view( base_addr, slot_size, ext_buffer_capacity );
    view.allocate();

    /* --------------------------------------------------------------------- */

    obj_t orig1;

    ASSERT_TRUE( orig1.is_convertible_to_c_api() );
    ::NS(TypeNoPtrs_preset)( orig1.as_ptr_c_api() );
    ::NS(TypeNoPtrs_set_a)(  orig1.as_ptr_c_api(), double{ 42.0 } );
    ::NS(TypeNoPtrs_set_b)(  orig1.as_ptr_c_api(), int64_t{ -42 } );
    ::NS(TypeNoPtrs_set_c)(  orig1.as_ptr_c_api(), 0, uint8_t{ 1 } );
    ::NS(TypeNoPtrs_set_c)(  orig1.as_ptr_c_api(), 1, uint8_t{ 1 } );
    ::NS(TypeNoPtrs_set_c)(  orig1.as_ptr_c_api(), 2, uint8_t{ 2 } );
    ::NS(TypeNoPtrs_set_c)(  orig1.as_ptr_c_api(), 3, uint8_t{ 3 } );
    ::NS(TypeNoPtrs_set_c)(  orig1.as_ptr_c_api(), 4, uint8_t{ 5 } );
    ::NS(TypeNoPtrs_set_c)(  orig1.as_ptr_c_api(), 5, uint8_t{ 8 } );

    obj_t ext_var;
    ASSERT_TRUE( ext_var.is_convertible_to_c_api() );
    ::NS(TypeNoPtrs_preset)( ext_var.as_ptr_c_api() );

    st_size_t required_buffer_size = st_size_t{ 0 };
    st_size_t requ_num_slots = st_size_t{ 0 };
    st_size_t requ_num_objs  = st_size_t{ 0 };
    st_size_t requ_num_ptrs  = st_size_t{ 0 };

    ASSERT_FALSE( view.can_add_copy_of_object< obj_t >(
        &orig1, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs ) );

    ASSERT_TRUE( required_buffer_size > view.size() );
    view.reallocate( requ_num_slots, requ_num_objs, requ_num_ptrs );

    obj_t* copy1 = st::CBufferView_add_copy_of_object_detail(
        view, &orig1, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs );

    ASSERT_TRUE( copy1 != nullptr );
    ASSERT_TRUE( copy1 != &orig1  );
    ASSERT_TRUE( copy1->as_ptr_data()  != orig1.as_ptr_data()  );
    ASSERT_TRUE( copy1->as_ptr_c_api() != orig1.as_ptr_c_api() );
    ASSERT_TRUE( copy1->a      == orig1.a );
    ASSERT_TRUE( copy1->b      == orig1.b );
    ASSERT_TRUE( copy1->c[ 0 ] == orig1.c[ 0 ] );
    ASSERT_TRUE( copy1->c[ 1 ] == orig1.c[ 1 ] );
    ASSERT_TRUE( copy1->c[ 2 ] == orig1.c[ 2 ] );
    ASSERT_TRUE( copy1->c[ 3 ] == orig1.c[ 3 ] );
    ASSERT_TRUE( copy1->c[ 4 ] == orig1.c[ 4 ] );
    ASSERT_TRUE( copy1->c[ 5 ] == orig1.c[ 5 ] );

    ASSERT_TRUE( &ext_var != copy1 );
    ASSERT_TRUE(  ext_var.as_ptr_data()  != copy1->as_ptr_data()  );
    ASSERT_TRUE(  ext_var.as_ptr_c_api() != copy1->as_ptr_c_api() );
    ASSERT_TRUE(  ext_var.a      != copy1->a );
    ASSERT_TRUE(  ext_var.b      != copy1->b );
    ASSERT_TRUE(  ext_var.c[ 0 ] != copy1->c[ 0 ] );
    ASSERT_TRUE(  ext_var.c[ 1 ] != copy1->c[ 1 ] );
    ASSERT_TRUE(  ext_var.c[ 2 ] != copy1->c[ 2 ] );
    ASSERT_TRUE(  ext_var.c[ 3 ] != copy1->c[ 3 ] );
    ASSERT_TRUE(  ext_var.c[ 4 ] != copy1->c[ 4 ] );
    ASSERT_TRUE(  ext_var.c[ 5 ] != copy1->c[ 5 ] );

    ASSERT_TRUE( view.load_object< obj_t >( 0, &ext_var ) ==
        st::COBJECTS_STATUS_SUCCESS );

    ASSERT_TRUE( &ext_var != copy1 );
    ASSERT_TRUE(  ext_var.as_ptr_data()  != copy1->as_ptr_data()  );
    ASSERT_TRUE(  ext_var.as_ptr_c_api() != copy1->as_ptr_c_api() );
    ASSERT_TRUE(  ext_var.a      == copy1->a );
    ASSERT_TRUE(  ext_var.b      == copy1->b );
    ASSERT_TRUE(  ext_var.c[ 0 ] == copy1->c[ 0 ] );
    ASSERT_TRUE(  ext_var.c[ 1 ] == copy1->c[ 1 ] );
    ASSERT_TRUE(  ext_var.c[ 2 ] == copy1->c[ 2 ] );
    ASSERT_TRUE(  ext_var.c[ 3 ] == copy1->c[ 3 ] );
    ASSERT_TRUE(  ext_var.c[ 4 ] == copy1->c[ 4 ] );
    ASSERT_TRUE(  ext_var.c[ 5 ] == copy1->c[ 5 ] );
}


TEST( CxxCommonCObjectsCBufferViewLoadObjectsTests, BasicUsageTypeFixedNumPtrs )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using st_size_t      = st::cobj_size_t;
    using obj_t       = ::NS(TypeFixedNumPtrs);
    using _prng_t      = std::mt19937_64;
    using _seed_t      = _prng_t::result_type;
    using _real_dist_t = std::uniform_real_distribution< double >;

    st_size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    st_size_t const ext_buffer_capacity = ::NS(CObjFlatBuffer_slot_based_size)(
        st_size_t{ 1 << 20 }, slot_size );

    std::vector< st::cobj_raw_t > ext_buffer(
        ext_buffer_capacity + slot_size );

    std::uintptr_t const store_addr = reinterpret_cast<
        std::uintptr_t >( ext_buffer.data() );

    std::uintptr_t const remainder = store_addr % slot_size;
    std::uintptr_t const base_addr = store_addr + ( slot_size - remainder );

    /* --------------------------------------------------------------------- */

    st::CBufferView view( base_addr, slot_size, ext_buffer_capacity );
    view.allocate();

    /* --------------------------------------------------------------------- */

    _prng_t prng( _seed_t{ 20200216 } );

    std::vector< double > orig1_b_values( 100 );
    std::vector< double > orig1_c_values( 255 );

    _real_dist_t b_dist( double{ -2.0 }, double{  2.0 } );
    _real_dist_t c_dist( double{  0.0 }, double{ 10.0 } );

    auto b_value_generator = std::bind( b_dist, prng );
    auto c_value_generator = std::bind( c_dist, prng );

    std::generate( orig1_b_values.begin(), orig1_b_values.end(),
                   b_value_generator );

    std::generate( orig1_c_values.begin(), orig1_c_values.end(),
                   c_value_generator );

    obj_t orig1;
    ::NS(TypeFixedNumPtrs_preset)( &orig1 );
    ::NS(TypeFixedNumPtrs_set_a)( &orig1, double{ 42.0 } );
    ::NS(TypeFixedNumPtrs_set_num_b_values)( &orig1, orig1_b_values.size() );
    ::NS(TypeFixedNumPtrs_set_num_c_values)( &orig1, orig1_c_values.size() );

    ::NS(TypeFixedNumPtrs_set_b_values_addr)( &orig1,
            reinterpret_cast< uintptr_t >( orig1_b_values.data() ) );

    ::NS(TypeFixedNumPtrs_set_c_values_addr)( &orig1,
            reinterpret_cast< uintptr_t >( orig1_c_values.data() ) );

    obj_t ext_var;
    ::NS(TypeFixedNumPtrs_preset)( &ext_var );

    st_size_t required_buffer_size = st_size_t{ 0 };
    st_size_t requ_num_slots = st_size_t{ 0 };
    st_size_t requ_num_objs  = st_size_t{ 0 };
    st_size_t requ_num_ptrs  = st_size_t{ 0 };

    ASSERT_FALSE( view.can_add_copy_of_object< obj_t >(
        &orig1, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs ) );

    ASSERT_TRUE( required_buffer_size > view.size() );
    view.reallocate( requ_num_slots, requ_num_objs, requ_num_ptrs );

    obj_t* copy1 = st::CBufferView_add_copy_of_object_detail(
        view, &orig1, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs );

    ASSERT_TRUE( copy1 != nullptr );
    ASSERT_TRUE( copy1 != &orig1  );
    ASSERT_TRUE( copy1->a             == orig1.a );
    ASSERT_TRUE( copy1->num_b_values  == orig1.num_b_values );
    ASSERT_TRUE( copy1->num_c_values  == orig1.num_c_values );
    ASSERT_TRUE( copy1->b_values_addr != 0u );
    ASSERT_TRUE( copy1->b_values_addr != orig1.b_values_addr );
    ASSERT_TRUE( copy1->c_values_addr != 0u );
    ASSERT_TRUE( copy1->c_values_addr != orig1.c_values_addr );

    ASSERT_TRUE( orig1_b_values.size() == static_cast< std::size_t >(
        std::distance(
            ::NS(TypeFixedNumPtrs_const_b_values_begin)( &orig1 ),
            ::NS(TypeFixedNumPtrs_const_b_values_end)( &orig1 ) ) ) );

    ASSERT_TRUE( orig1_b_values.size() == static_cast< std::size_t >(
        std::distance(
            ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy1 ),
            ::NS(TypeFixedNumPtrs_const_b_values_end)( copy1 ) ) ) );

    ASSERT_TRUE( std::equal(
        ::NS(TypeFixedNumPtrs_const_b_values_begin)( &orig1 ),
        ::NS(TypeFixedNumPtrs_const_b_values_end)( &orig1 ),
        ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy1 ) ) );

    ASSERT_TRUE( orig1_c_values.size() == static_cast< std::size_t >(
        std::distance(
            ::NS(TypeFixedNumPtrs_const_c_values_begin)( &orig1 ),
            ::NS(TypeFixedNumPtrs_const_c_values_end)( &orig1 ) ) ) );

    ASSERT_TRUE( orig1_c_values.size() == static_cast< std::size_t >(
        std::distance(
            ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy1 ),
            ::NS(TypeFixedNumPtrs_const_c_values_end)( copy1 ) ) ) );

    ASSERT_TRUE( std::equal(
        ::NS(TypeFixedNumPtrs_const_c_values_begin)( &orig1 ),
        ::NS(TypeFixedNumPtrs_const_c_values_end)( &orig1 ),
        ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy1 ) ) );

    ASSERT_TRUE( &ext_var != copy1 );
    ASSERT_TRUE(  ext_var.num_b_values  == 0u );
    ASSERT_TRUE(  ext_var.b_values_addr == 0u );

    ASSERT_TRUE(  ext_var.num_c_values  == 0u );
    ASSERT_TRUE(  ext_var.c_values_addr == 0u );
    ASSERT_TRUE(  ext_var.a             != copy1->a );

    /* Can't load because ext_var has no fields and no way to store the
     * data from copy1 */

    static_assert( st::CObjElem_has_const_num_ptrs< obj_t >(), "Has C-API ptrs" );

    ASSERT_TRUE( view.load_object< obj_t >( 0, &ext_var ) !=
        st::COBJECTS_STATUS_SUCCESS );

    ASSERT_TRUE( &ext_var   != copy1 );
    ASSERT_TRUE(  ext_var.a != copy1->a );

    ASSERT_TRUE(  ext_var.num_b_values  == 0u );
    ASSERT_TRUE(  ext_var.b_values_addr == 0u );
    ASSERT_TRUE(  ext_var.num_c_values  == 0u );
    ASSERT_TRUE(  ext_var.c_values_addr == 0u );

    /* Give ext_var values for num_b_values and num_c_values that match
     * but still no actual space to store the data -> load shouldn't work */

    ::NS(TypeFixedNumPtrs_set_num_b_values)( &ext_var, copy1->num_b_values );
    ::NS(TypeFixedNumPtrs_set_num_c_values)( &ext_var, copy1->num_c_values );

    ASSERT_TRUE(  ext_var.b_values_addr == 0u );
    ASSERT_TRUE(  ext_var.num_b_values  != 0u );
    ASSERT_TRUE(  ext_var.num_b_values  ==
                 ::NS(TypeFixedNumPtrs_num_b_values)( copy1 ) );


    ASSERT_TRUE(  ext_var.c_values_addr == 0u );
    ASSERT_TRUE(  ext_var.num_c_values  != 0u );
    ASSERT_TRUE(  ext_var.num_c_values  ==
                  ::NS(TypeFixedNumPtrs_num_c_values)( copy1 ) );

    ASSERT_TRUE( view.load_object< obj_t >( 0, &ext_var ) !=
        st::COBJECTS_STATUS_SUCCESS );
    ASSERT_TRUE( ext_var.a != copy1->a );

    /* Give ext_var a space for b-values and c-values but give it
     * actually too much space -> should not work */

    std::vector< double > ext_var_b_values( 2u *
        ::NS(TypeFixedNumPtrs_num_b_values)( copy1 ) );

    std::vector< double > ext_var_c_values( 2u *
        ::NS(TypeFixedNumPtrs_num_c_values)( copy1 ) );

    ::NS(TypeFixedNumPtrs_set_num_b_values)(
        &ext_var, ext_var_b_values.size() );

    ::NS(TypeFixedNumPtrs_set_num_c_values)(
        &ext_var, ext_var_c_values.size() );

    ::NS(TypeFixedNumPtrs_set_b_values_addr)( &ext_var,
        reinterpret_cast< uintptr_t >( ext_var_b_values.data() ) );

    ::NS(TypeFixedNumPtrs_set_c_values_addr)( &ext_var,
        reinterpret_cast< uintptr_t >( ext_var_c_values.data() ) );

    ASSERT_TRUE( view.load_object< obj_t >( 0, &ext_var ) !=
        st::COBJECTS_STATUS_SUCCESS );
    ASSERT_TRUE( ext_var.a != copy1->a );

    /* Keep the actual field as it is but set the num_b_values and num_c_values
     * parameters to match those of copy1 -> this should work now! */

    ::NS(TypeFixedNumPtrs_set_num_b_values)( &ext_var,
        ::NS(TypeFixedNumPtrs_num_b_values)( copy1 ) );

    ::NS(TypeFixedNumPtrs_set_num_c_values)( &ext_var,
        ::NS(TypeFixedNumPtrs_num_c_values)( copy1 ) );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_b_values_begin)(
                    copy1 ) != nullptr );
    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_b_values_begin)(
                    &ext_var ) != nullptr );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy1 ) !=
                 ::NS(TypeFixedNumPtrs_const_b_values_begin)( &ext_var ) );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_c_values_begin)(
                    copy1 ) != nullptr );

    ASSERT_TRUE(  ::NS(TypeFixedNumPtrs_const_c_values_begin)(
                    &ext_var ) != nullptr );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy1 ) !=
                 ::NS(TypeFixedNumPtrs_const_c_values_begin)( &ext_var ) );

    ASSERT_TRUE( view.load_object< obj_t >( 0, &ext_var ) ==
        st::COBJECTS_STATUS_SUCCESS );

    ASSERT_TRUE( &ext_var   != copy1 );
    ASSERT_TRUE(  ext_var.a == copy1->a );

    ASSERT_TRUE(  ::NS(TypeFixedNumPtrs_num_b_values)( &ext_var ) ==
                  ::NS(TypeFixedNumPtrs_num_b_values)( copy1 ) );

    ASSERT_TRUE(  ::NS(TypeFixedNumPtrs_num_c_values)( &ext_var ) ==
                  ::NS(TypeFixedNumPtrs_num_c_values)( copy1 ) );

    ASSERT_TRUE(  ::NS(TypeFixedNumPtrs_b_values_addr)( &ext_var ) ==
                  reinterpret_cast< uintptr_t >( ext_var_b_values.data() ) );

    ASSERT_TRUE(  ::NS(TypeFixedNumPtrs_c_values_addr)( &ext_var ) ==
                  reinterpret_cast< uintptr_t >( ext_var_c_values.data() ) );

    ASSERT_TRUE( std::equal(
        ::NS(TypeFixedNumPtrs_const_b_values_begin)( &ext_var ),
        ::NS(TypeFixedNumPtrs_const_b_values_end)( &ext_var ),
        ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy1 ) ) );

    ASSERT_TRUE( std::equal(
        ::NS(TypeFixedNumPtrs_const_c_values_begin)( &ext_var ),
        ::NS(TypeFixedNumPtrs_const_c_values_end)( &ext_var ),
        ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy1 ) ) );
}

