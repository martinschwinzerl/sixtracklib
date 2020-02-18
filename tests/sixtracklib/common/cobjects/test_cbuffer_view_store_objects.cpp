#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <random>
#include <vector>
#include <typeinfo>

#include <gtest/gtest.h>

#include "sixtracklib/testlib.h"
#include "sixtracklib/testlib/common/cobjects/type_no_ptrs.h"
#include "sixtracklib/testlib/common/cobjects/type_fixed_num_ptrs.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"

TEST( CxxCommonCObjectsCBufferViewStoreObjectsTests, BasicUsageTypeNoPtrs )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using _size_t = st::cobj_size_t;
    using _obj_t  = st::tests::TypeNoPtrs;

    _size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    _size_t const ext_buffer_capacity = ::NS(CObjFlatBuffer_slot_based_size)(
        _size_t{ 1 << 20 }, slot_size );

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

    _obj_t orig;

    ASSERT_TRUE( orig.is_convertible_to_c_api() );
    ::NS(TypeNoPtrs_preset)( orig.as_ptr_c_api() );

    _size_t required_buffer_size = _size_t{ 0 };
    _size_t requ_num_slots = _size_t{ 0 };
    _size_t requ_num_objs  = _size_t{ 0 };
    _size_t requ_num_ptrs  = _size_t{ 0 };

    ASSERT_FALSE( view.can_add_copy_of_object< _obj_t >(
        &orig, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs ) );

    ASSERT_TRUE( required_buffer_size > view.size() );
    view.reallocate( requ_num_slots, requ_num_objs, requ_num_ptrs );

    _obj_t* cpy_obj = st::CBufferView_add_copy_of_object_detail(
        view, &orig, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs );

    ASSERT_TRUE( cpy_obj != nullptr );
    ASSERT_TRUE( cpy_obj != &orig  );
    ASSERT_TRUE( cpy_obj->as_ptr_data()  != orig.as_ptr_data()  );
    ASSERT_TRUE( cpy_obj->as_ptr_c_api() != orig.as_ptr_c_api() );
    ASSERT_TRUE( cpy_obj->a      == orig.a );
    ASSERT_TRUE( cpy_obj->b      == orig.b );
    ASSERT_TRUE( cpy_obj->c[ 0 ] == orig.c[ 0 ] );
    ASSERT_TRUE( cpy_obj->c[ 1 ] == orig.c[ 1 ] );
    ASSERT_TRUE( cpy_obj->c[ 2 ] == orig.c[ 2 ] );
    ASSERT_TRUE( cpy_obj->c[ 3 ] == orig.c[ 3 ] );
    ASSERT_TRUE( cpy_obj->c[ 4 ] == orig.c[ 4 ] );
    ASSERT_TRUE( cpy_obj->c[ 5 ] == orig.c[ 5 ] );

    _obj_t ext_var;
    ASSERT_TRUE( ext_var.is_convertible_to_c_api() );
    ::NS(TypeNoPtrs_preset)( ext_var.as_ptr_c_api() );
    ::NS(TypeNoPtrs_set_a)(  ext_var.as_ptr_c_api(), double{ 42.0 } );
    ::NS(TypeNoPtrs_set_b)(  ext_var.as_ptr_c_api(), int64_t{ -42 } );
    ::NS(TypeNoPtrs_set_c)(  ext_var.as_ptr_c_api(), 0, uint8_t{ 1 } );
    ::NS(TypeNoPtrs_set_c)(  ext_var.as_ptr_c_api(), 1, uint8_t{ 1 } );
    ::NS(TypeNoPtrs_set_c)(  ext_var.as_ptr_c_api(), 2, uint8_t{ 2 } );
    ::NS(TypeNoPtrs_set_c)(  ext_var.as_ptr_c_api(), 3, uint8_t{ 3 } );
    ::NS(TypeNoPtrs_set_c)(  ext_var.as_ptr_c_api(), 4, uint8_t{ 5 } );
    ::NS(TypeNoPtrs_set_c)(  ext_var.as_ptr_c_api(), 5, uint8_t{ 8 } );

    ASSERT_TRUE( &ext_var != cpy_obj );
    ASSERT_TRUE(  ext_var.as_ptr_data()  != cpy_obj->as_ptr_data()  );
    ASSERT_TRUE(  ext_var.as_ptr_c_api() != cpy_obj->as_ptr_c_api() );
    ASSERT_TRUE(  ext_var.a      != cpy_obj->a );
    ASSERT_TRUE(  ext_var.b      != cpy_obj->b );
    ASSERT_TRUE(  ext_var.c[ 0 ] != cpy_obj->c[ 0 ] );
    ASSERT_TRUE(  ext_var.c[ 1 ] != cpy_obj->c[ 1 ] );
    ASSERT_TRUE(  ext_var.c[ 2 ] != cpy_obj->c[ 2 ] );
    ASSERT_TRUE(  ext_var.c[ 3 ] != cpy_obj->c[ 3 ] );
    ASSERT_TRUE(  ext_var.c[ 4 ] != cpy_obj->c[ 4 ] );
    ASSERT_TRUE(  ext_var.c[ 5 ] != cpy_obj->c[ 5 ] );

    ASSERT_TRUE( view.store_object< _obj_t >( 0, &ext_var ) ==
        st::COBJECTS_STATUS_SUCCESS );

    ASSERT_TRUE( &ext_var != cpy_obj );
    ASSERT_TRUE(  ext_var.as_ptr_data()  != cpy_obj->as_ptr_data()  );
    ASSERT_TRUE(  ext_var.as_ptr_c_api() != cpy_obj->as_ptr_c_api() );
    ASSERT_TRUE(  ext_var.a      == cpy_obj->a );
    ASSERT_TRUE(  ext_var.b      == cpy_obj->b );
    ASSERT_TRUE(  ext_var.c[ 0 ] == cpy_obj->c[ 0 ] );
    ASSERT_TRUE(  ext_var.c[ 1 ] == cpy_obj->c[ 1 ] );
    ASSERT_TRUE(  ext_var.c[ 2 ] == cpy_obj->c[ 2 ] );
    ASSERT_TRUE(  ext_var.c[ 3 ] == cpy_obj->c[ 3 ] );
    ASSERT_TRUE(  ext_var.c[ 4 ] == cpy_obj->c[ 4 ] );
    ASSERT_TRUE(  ext_var.c[ 5 ] == cpy_obj->c[ 5 ] );

    ASSERT_TRUE( cpy_obj != nullptr );
    ASSERT_TRUE( cpy_obj != &orig  );
    ASSERT_TRUE( cpy_obj->as_ptr_data()  != orig.as_ptr_data()  );
    ASSERT_TRUE( cpy_obj->as_ptr_c_api() != orig.as_ptr_c_api() );
    ASSERT_TRUE( cpy_obj->a      != orig.a );
    ASSERT_TRUE( cpy_obj->b      != orig.b );
    ASSERT_TRUE( cpy_obj->c[ 0 ] != orig.c[ 0 ] );
    ASSERT_TRUE( cpy_obj->c[ 1 ] != orig.c[ 1 ] );
    ASSERT_TRUE( cpy_obj->c[ 2 ] != orig.c[ 2 ] );
    ASSERT_TRUE( cpy_obj->c[ 3 ] != orig.c[ 3 ] );
    ASSERT_TRUE( cpy_obj->c[ 4 ] != orig.c[ 4 ] );
    ASSERT_TRUE( cpy_obj->c[ 5 ] != orig.c[ 5 ] );
}


TEST( CxxCommonCObjectsCBufferViewStoreObjectsTests, BasicUsageTypeFixedNumPtrs )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using _size_t      = st::cobj_size_t;
    using _obj_t       = ::NS(TypeFixedNumPtrs);
    using _prng_t      = std::mt19937_64;
    using _seed_t      = _prng_t::result_type;
    using _real_dist_t = std::uniform_real_distribution< double >;

    _size_t const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    _size_t const ext_buffer_capacity = ::NS(CObjFlatBuffer_slot_based_size)(
        _size_t{ 1 << 20 }, slot_size );

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

    constexpr _size_t NUM_B_VALUES = _size_t{ 100 };
    constexpr _size_t NUM_C_VALUES = _size_t{ 255 };

    _obj_t orig;
    ::NS(TypeFixedNumPtrs_preset)( &orig );
    ::NS(TypeFixedNumPtrs_set_num_b_values)( &orig, NUM_B_VALUES );
    ::NS(TypeFixedNumPtrs_set_num_c_values)( &orig, NUM_C_VALUES );

    _size_t required_buffer_size = _size_t{ 0 };
    _size_t requ_num_slots = _size_t{ 0 };
    _size_t requ_num_objs  = _size_t{ 0 };
    _size_t requ_num_ptrs  = _size_t{ 0 };

    ASSERT_FALSE( view.can_add_copy_of_object< _obj_t >(
        &orig, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs ) );

    ASSERT_TRUE( required_buffer_size > view.size() );
    view.reallocate( requ_num_slots, requ_num_objs, requ_num_ptrs );

    _obj_t* cpy_obj = st::CBufferView_add_copy_of_object_detail(
        view, &orig, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs );

    ASSERT_TRUE( cpy_obj != nullptr );
    ASSERT_TRUE( cpy_obj != &orig  );
    ASSERT_TRUE( cpy_obj == view.get_object< _obj_t >( 0 ) );
    ASSERT_TRUE( cpy_obj->a             == orig.a );
    ASSERT_TRUE( cpy_obj->num_b_values  == orig.num_b_values );
    ASSERT_TRUE( cpy_obj->num_b_values  == NUM_B_VALUES );
    ASSERT_TRUE( cpy_obj->num_c_values  == orig.num_c_values );
    ASSERT_TRUE( cpy_obj->num_c_values  == NUM_C_VALUES );
    ASSERT_TRUE( cpy_obj->b_values_addr != 0u );
    ASSERT_TRUE( cpy_obj->b_values_addr != orig.b_values_addr );
    ASSERT_TRUE( cpy_obj->c_values_addr != 0u );
    ASSERT_TRUE( cpy_obj->c_values_addr != orig.c_values_addr );

    uintptr_t const cpy_obj_b_addr = cpy_obj->b_values_addr;
    uintptr_t const cpy_obj_c_addr = cpy_obj->c_values_addr;

    _obj_t ext_var;
    ::NS(TypeFixedNumPtrs_preset)( &ext_var );
    ::NS(TypeFixedNumPtrs_set_a)( &ext_var, double{ 42.0 } );

    ASSERT_TRUE( &ext_var != cpy_obj );
    ASSERT_TRUE(  ext_var.num_b_values  == 0u );
    ASSERT_TRUE(  ext_var.b_values_addr == 0u );

    ASSERT_TRUE(  ext_var.num_c_values  == 0u );
    ASSERT_TRUE(  ext_var.c_values_addr == 0u );
    ASSERT_TRUE(  ext_var.a             != cpy_obj->a );

    /* Can't store because ext_var has no fields and does not match the
     * layout of cpy_obj */

    ASSERT_TRUE( view.store_object< _obj_t >( 0, &ext_var ) !=
        st::COBJECTS_STATUS_SUCCESS );

    ASSERT_TRUE( &ext_var   != cpy_obj );
    ASSERT_TRUE(  ext_var.a != cpy_obj->a );

    ASSERT_TRUE(  cpy_obj->num_b_values  == NUM_B_VALUES );
    ASSERT_TRUE(  cpy_obj->num_c_values  == NUM_C_VALUES );
    ASSERT_TRUE(  cpy_obj->b_values_addr == cpy_obj_b_addr );
    ASSERT_TRUE(  cpy_obj->c_values_addr == cpy_obj_c_addr );

    /* Give ext_var values for num_b_values and num_c_values that match
     * but still no actual space to store the data -> load shouldn't work */

    ::NS(TypeFixedNumPtrs_set_num_b_values)( &ext_var, NUM_B_VALUES );
    ::NS(TypeFixedNumPtrs_set_num_c_values)( &ext_var, NUM_C_VALUES );

    ASSERT_TRUE(  ext_var.b_values_addr == 0u );
    ASSERT_TRUE(  ext_var.num_b_values  != 0u );
    ASSERT_TRUE(  ext_var.num_b_values  == cpy_obj->num_b_values );
    ASSERT_TRUE(  ext_var.c_values_addr == 0u );
    ASSERT_TRUE(  ext_var.num_c_values  != 0u );
    ASSERT_TRUE(  ext_var.num_c_values  == cpy_obj->num_c_values );

    ASSERT_TRUE( view.store_object< _obj_t >( 0, &ext_var ) !=
        st::COBJECTS_STATUS_SUCCESS );

    ASSERT_TRUE( ext_var.a  != cpy_obj->a );
    ASSERT_TRUE( &ext_var   != cpy_obj );
    ASSERT_TRUE(  ext_var.a != cpy_obj->a );

    ASSERT_TRUE(  cpy_obj->num_b_values  == NUM_B_VALUES );
    ASSERT_TRUE(  cpy_obj->num_c_values  == NUM_C_VALUES );
    ASSERT_TRUE(  cpy_obj->b_values_addr == cpy_obj_b_addr );
    ASSERT_TRUE(  cpy_obj->c_values_addr == cpy_obj_c_addr );

    /* Give ext_var a space for b-values and c-values but give it
     * actually too much space -> should not work */

    std::vector< double > ext_b_values( 2u * NUM_B_VALUES );
    std::vector< double > ext_c_values( 2u * NUM_C_VALUES );

    _real_dist_t b_dist( double{ -2.0 }, double{  2.0 } );
    _real_dist_t c_dist( double{  0.0 }, double{ 10.0 } );

    auto b_value_generator = std::bind( b_dist, prng );
    auto c_value_generator = std::bind( c_dist, prng );

    std::generate( ext_b_values.begin(), ext_b_values.end(),
                   b_value_generator );

    std::generate( ext_c_values.begin(), ext_c_values.end(),
                   c_value_generator );

    ::NS(TypeFixedNumPtrs_set_num_b_values)( &ext_var, ext_b_values.size() );
    ::NS(TypeFixedNumPtrs_set_num_c_values)( &ext_var, ext_c_values.size() );

    ::NS(TypeFixedNumPtrs_set_b_values_addr)( &ext_var,
        reinterpret_cast< uintptr_t >( ext_b_values.data() ) );

    ::NS(TypeFixedNumPtrs_set_c_values_addr)( &ext_var,
        reinterpret_cast< uintptr_t >( ext_c_values.data() ) );

    ASSERT_TRUE( view.store_object< _obj_t >( 0, &ext_var ) !=
        st::COBJECTS_STATUS_SUCCESS );

    ASSERT_TRUE(  cpy_obj->a != ext_var.a );
    ASSERT_TRUE(  cpy_obj->num_b_values  == NUM_B_VALUES );
    ASSERT_TRUE(  cpy_obj->num_c_values  == NUM_C_VALUES );
    ASSERT_TRUE(  cpy_obj->b_values_addr == cpy_obj_b_addr );
    ASSERT_TRUE(  cpy_obj->c_values_addr == cpy_obj_c_addr );

    /* Keep the actual field as it is but set the num_b_values and num_c_values
     * parameters to match those of cpy_obj -> this should work now! */

    ext_b_values.resize( NUM_B_VALUES );
    ext_c_values.resize( NUM_C_VALUES );

    std::generate( ext_b_values.begin(), ext_b_values.end(),
                   b_value_generator );

    std::generate( ext_c_values.begin(), ext_c_values.end(),
                   c_value_generator );

    ::NS(TypeFixedNumPtrs_set_num_b_values)( &ext_var, ext_b_values.size() );
    ::NS(TypeFixedNumPtrs_set_num_c_values)( &ext_var, ext_c_values.size() );

    ::NS(TypeFixedNumPtrs_set_b_values_addr)( &ext_var,
        reinterpret_cast< uintptr_t >( ext_b_values.data() ) );

    ::NS(TypeFixedNumPtrs_set_c_values_addr)( &ext_var,
        reinterpret_cast< uintptr_t >( ext_c_values.data() ) );

    ASSERT_TRUE( cpy_obj->num_b_values == ext_var.num_b_values );
    ASSERT_TRUE( cpy_obj->num_c_values == ext_var.num_c_values );

    ASSERT_TRUE( view.store_object< _obj_t >( 0, &ext_var ) ==
        st::COBJECTS_STATUS_SUCCESS );

    ASSERT_TRUE(  cpy_obj->a == ext_var.a );
    ASSERT_TRUE(  cpy_obj->num_b_values  == NUM_B_VALUES );
    ASSERT_TRUE(  cpy_obj->num_c_values  == NUM_C_VALUES );
    ASSERT_TRUE(  cpy_obj->b_values_addr == cpy_obj_b_addr );
    ASSERT_TRUE(  cpy_obj->c_values_addr == cpy_obj_c_addr );
    ASSERT_TRUE(  ext_var.b_values_addr  != cpy_obj_b_addr );
    ASSERT_TRUE(  ext_var.b_values_addr  ==
                    reinterpret_cast< uintptr_t >( ext_b_values.data() ) );
    ASSERT_TRUE(  ext_var.c_values_addr  != cpy_obj_c_addr );
    ASSERT_TRUE(  ext_var.c_values_addr  ==
                    reinterpret_cast< uintptr_t >( ext_c_values.data() ) );

    ASSERT_TRUE( std::equal(
        ::NS(TypeFixedNumPtrs_const_b_values_begin)( cpy_obj ),
        ::NS(TypeFixedNumPtrs_const_b_values_end)( cpy_obj ),
        ::NS(TypeFixedNumPtrs_const_b_values_begin)( &ext_var ) ) );

    ASSERT_TRUE( std::equal(
        ::NS(TypeFixedNumPtrs_const_c_values_begin)( cpy_obj ),
        ::NS(TypeFixedNumPtrs_const_c_values_end)( cpy_obj ),
        ::NS(TypeFixedNumPtrs_const_c_values_begin)( &ext_var ) ) );
}

