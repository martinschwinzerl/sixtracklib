#include "sixtracklib/common/cobjects/cbuffer_view.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/testlib.h"
#include "sixtracklib/testlib/common/cobjects/type_no_ptrs.h"
#include "sixtracklib/testlib/common/cobjects/type_fixed_num_ptrs.h"

TEST( CxxCommonCObjectsCBufferViewAddObjectsTests, BasicUsageTypeNoPtrs )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using _size_t   = st::cobj_size_t;
    using _status_t = st::cobj_status_t;
    using _obj1_t   = st::tests::TypeNoPtrs;

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

    ASSERT_TRUE(  view.base_address() == base_addr );
    ASSERT_TRUE(  view.slot_size() == slot_size );
    ASSERT_TRUE(  view.p_base() != nullptr );

    _status_t status = view.allocate();

    ASSERT_TRUE( status == st::COBJECTS_STATUS_SUCCESS );
    ASSERT_TRUE( view.size() < view.capacity() );
    ASSERT_TRUE( view.size() >= st::CBUFFER_MIN_SIZE );

    ASSERT_TRUE( view.n_slots()      == _size_t{ 0 } );
    ASSERT_TRUE( view.n_objects()    == _size_t{ 0 } );
    ASSERT_TRUE( view.n_pointers()   == _size_t{ 0 } );
    ASSERT_TRUE( view.n_garbage()    == _size_t{ 0 } );

    ASSERT_TRUE( view.max_slots()    == _size_t{ 0 } );
    ASSERT_TRUE( view.max_objects()  == _size_t{ 0 } );
    ASSERT_TRUE( view.max_pointers() == _size_t{ 0 } );
    ASSERT_TRUE( view.max_garbage()  == _size_t{ 0 } );

    /* --------------------------------------------------------------------- */

    _size_t required_buffer_size = _size_t{ 0 };
    _size_t requ_num_slots = _size_t{ 0 };
    _size_t requ_num_objs  = _size_t{ 0 };
    _size_t requ_num_ptrs  = _size_t{ 0 };

    ASSERT_FALSE( view.can_add_copy_of_object< _obj1_t >(
        nullptr, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs ) );

    ASSERT_TRUE( required_buffer_size > view.size() );
    ASSERT_TRUE( requ_num_objs  == _size_t{ 1 } );
    ASSERT_TRUE( requ_num_ptrs  == _size_t{ 0 } );
    ASSERT_TRUE( requ_num_slots >  _size_t{ 0 } );
    ASSERT_TRUE( requ_num_slots == st::CObjElem_required_num_slots< _obj1_t >(
        view.slot_size() ) );

    ASSERT_TRUE( st::COBJECTS_STATUS_SUCCESS == view.reallocate(
                        requ_num_slots, requ_num_objs, requ_num_ptrs ) );

    ASSERT_TRUE( view.size() >= required_buffer_size );
    ASSERT_TRUE( view.max_slots()    >= requ_num_slots );
    ASSERT_TRUE( view.max_objects()  >= requ_num_objs  );
    ASSERT_TRUE( view.max_pointers() >= requ_num_ptrs  );

    ASSERT_TRUE( view.can_add_copy_of_object< _obj1_t >( nullptr ) );

    _obj1_t orig;
    std::memset( &orig, ( int )0, sizeof( orig ) );

    orig.a      = 42.0;
    orig.b      = 7;
    orig.c[ 0 ] = 1;
    orig.c[ 1 ] = 1;
    orig.c[ 2 ] = 2;
    orig.c[ 3 ] = 3;
    orig.c[ 4 ] = 5;
    orig.c[ 5 ] = 8;

    _obj1_t* copy = st::CBufferView_add_copy_of_object_detail(
        view, &orig, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs );

    ASSERT_TRUE( copy != nullptr );
    ASSERT_TRUE( view.n_objects()  == _size_t{ 1 } );
    ASSERT_TRUE( view.n_slots()    == view.max_slots()    );
    ASSERT_TRUE( view.n_objects()  == view.max_objects()  );
    ASSERT_TRUE( view.n_pointers() == view.max_pointers() );

    ASSERT_TRUE( copy != &orig );
    ASSERT_TRUE( std::memcmp( &orig, copy, sizeof( orig ) ) == 0 );
    ASSERT_TRUE( view.get_object< _obj1_t >( 0u ) == copy );

    orig.a *= 2.0;
    orig.b -= 5.0;

    for( _size_t ii = 0u ; ii < 6u ; ++ii ) orig.c[ ii ] += uint8_t{ 36 };

    ASSERT_FALSE( view.can_add_copy_of_object( &orig, &required_buffer_size,
        &requ_num_slots, &requ_num_objs, &requ_num_ptrs ) );

    ASSERT_TRUE( required_buffer_size > view.size() );
    ASSERT_TRUE( requ_num_objs  == _size_t{ 2 } );
    ASSERT_TRUE( requ_num_ptrs  == _size_t{ 0 } );
    ASSERT_TRUE( requ_num_slots >  _size_t{ 0 } );
    ASSERT_TRUE( requ_num_slots == _size_t{ 2 } *
        st::CObjElem_required_num_slots< _obj1_t >( view.slot_size(), &orig ) );

    ASSERT_TRUE( st::COBJECTS_STATUS_SUCCESS == view.reallocate(
            requ_num_slots, requ_num_objs, requ_num_ptrs ) );

    ASSERT_TRUE( view.size() >= required_buffer_size );
    ASSERT_TRUE( view.max_slots()    >= requ_num_slots );
    ASSERT_TRUE( view.max_objects()  >= requ_num_objs  );
    ASSERT_TRUE( view.max_pointers() >= requ_num_ptrs  );

    _obj1_t* copy2 = st::CBufferView_add_copy_of_object_detail(
        view, &orig, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs );

    ASSERT_TRUE( copy != nullptr );
    ASSERT_TRUE( view.n_objects()  == _size_t{ 2 } );
    ASSERT_TRUE( view.n_slots()    == view.max_slots()    );
    ASSERT_TRUE( view.n_objects()  == view.max_objects()  );
    ASSERT_TRUE( view.n_pointers() == view.max_pointers() );

    ASSERT_TRUE( copy  != &orig );
    ASSERT_TRUE( copy2 != &orig );
    ASSERT_TRUE( copy2 != copy  );
    ASSERT_TRUE( std::memcmp( &orig, copy2, sizeof( orig ) ) == 0 );
    ASSERT_TRUE( std::memcmp( &orig, copy,  sizeof( orig ) ) != 0 );
    ASSERT_TRUE( std::memcmp( copy,  copy2, sizeof( orig ) ) != 0 );
    ASSERT_TRUE( view.get_object< _obj1_t >( 0u ) == copy  );
    ASSERT_TRUE( view.get_object< _obj1_t >( 1u ) == copy2 );
}

TEST( CxxCommonCObjectsCBufferViewAddObjectsTests, BasicUsageTypeFixedNumPtrs )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using _size_t      = st::cobj_size_t;
    using _status_t    = st::cobj_status_t;
    using _obj2_t      = ::NS(TypeFixedNumPtrs);

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

    ASSERT_TRUE(  view.base_address() == base_addr );
    ASSERT_TRUE(  view.slot_size() == slot_size );
    ASSERT_TRUE(  view.p_base() != nullptr );

    _status_t status = view.allocate();

    ASSERT_TRUE( status == st::COBJECTS_STATUS_SUCCESS );
    ASSERT_TRUE( view.size() < view.capacity() );
    ASSERT_TRUE( view.size() >= st::CBUFFER_MIN_SIZE );

    ASSERT_TRUE( view.n_slots()      == _size_t{ 0 } );
    ASSERT_TRUE( view.n_objects()    == _size_t{ 0 } );
    ASSERT_TRUE( view.n_pointers()   == _size_t{ 0 } );
    ASSERT_TRUE( view.n_garbage()    == _size_t{ 0 } );

    ASSERT_TRUE( view.max_slots()    == _size_t{ 0 } );
    ASSERT_TRUE( view.max_objects()  == _size_t{ 0 } );
    ASSERT_TRUE( view.max_pointers() == _size_t{ 0 } );
    ASSERT_TRUE( view.max_garbage()  == _size_t{ 0 } );

    /* --------------------------------------------------------------------- */

    _obj2_t orig1;
    ::NS(TypeFixedNumPtrs_preset)( &orig1 );
    ::NS(TypeFixedNumPtrs_set_a)( &orig1, double{ 42.0 } );
    ::NS(TypeFixedNumPtrs_set_num_b_values)( &orig1, _size_t{ 100 } );
    ::NS(TypeFixedNumPtrs_set_num_c_values)( &orig1, _size_t{ 1000 } );

    _size_t required_buffer_size = _size_t{ 0 };
    _size_t requ_num_slots = _size_t{ 0 };
    _size_t requ_num_objs  = _size_t{ 0 };
    _size_t requ_num_ptrs  = _size_t{ 0 };

    ASSERT_FALSE( view.can_add_copy_of_object< _obj2_t >(
        &orig1, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs ) );

    ASSERT_TRUE( required_buffer_size > view.size() );
    ASSERT_TRUE( requ_num_objs  == _size_t{ 1 } );
    ASSERT_TRUE( requ_num_ptrs  == _size_t{ 2 } );
    ASSERT_TRUE( requ_num_slots >  _size_t{ 0 } );
    ASSERT_TRUE( requ_num_slots == st::CObjElem_required_num_slots< _obj2_t >(
        view.slot_size(), &orig1 ) );

    ASSERT_TRUE( st::COBJECTS_STATUS_SUCCESS == view.reallocate(
                        requ_num_slots, requ_num_objs, requ_num_ptrs ) );

    ASSERT_TRUE( view.size() >= required_buffer_size );
    ASSERT_TRUE( view.max_slots()    >= requ_num_slots );
    ASSERT_TRUE( view.max_objects()  >= requ_num_objs  );
    ASSERT_TRUE( view.max_pointers() >= requ_num_ptrs  );

    ASSERT_TRUE( view.can_add_copy_of_object< _obj2_t >( &orig1 ) );

    _obj2_t* copy1 = st::CBufferView_add_copy_of_object_detail(
        view, &orig1, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs );

    ASSERT_TRUE( copy1 != nullptr );
    ASSERT_TRUE( copy1 != &orig1  );
    ASSERT_TRUE( view.n_objects()  == _size_t{ 1 } );
    ASSERT_TRUE( view.n_slots()    == view.max_slots()    );
    ASSERT_TRUE( view.n_objects()  == view.max_objects()  );
    ASSERT_TRUE( view.n_pointers() == view.max_pointers() );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_a)( copy1 ) ==
                 ::NS(TypeFixedNumPtrs_a)( &orig1) );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_num_b_values)( copy1 ) ==
                 ::NS(TypeFixedNumPtrs_num_b_values)( &orig1 ) );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_num_c_values)( copy1 ) ==
                 ::NS(TypeFixedNumPtrs_num_c_values)( &orig1 ) );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy1 ) !=
                 nullptr );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy1 ) !=
                 nullptr );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_b_values_end)( copy1 ) !=
                 nullptr );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_c_values_end)( copy1 ) !=
                 nullptr );

    ASSERT_TRUE( static_cast< SIXTRL_UINT64_T >( std::distance(
                    ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy1 ),
                    ::NS(TypeFixedNumPtrs_const_b_values_end)( copy1 ) ) ) ==
                 ::NS(TypeFixedNumPtrs_num_b_values)( copy1 ) );

    ASSERT_TRUE( static_cast< SIXTRL_UINT64_T >( std::distance(
                    ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy1 ),
                    ::NS(TypeFixedNumPtrs_const_c_values_end)( copy1 ) ) ) ==
                 ::NS(TypeFixedNumPtrs_num_c_values)( copy1 ) );

    _prng_t prng( _seed_t{ 20200214 } );

    _real_dist_t b_dist( double{ -1.0 }, double{ 1.0 } );
    _real_dist_t c_dist( double{  0.0 }, double{ 100.0 } );

    std::vector< double > copy1_b_values(
        ::NS(TypeFixedNumPtrs_num_b_values( copy1 ) ) );

    std::vector< double > copy1_c_values(
        ::NS(TypeFixedNumPtrs_num_c_values( copy1 ) ) );

    for( _size_t ii = 0 ; ii < copy1_b_values.size() ; ++ii )
    {
        double const b_value = b_dist( prng );
        copy1_b_values[ ii ] = b_value;
        ::NS(TypeFixedNumPtrs_set_b_value)( copy1, ii, b_value );
    }

    for( _size_t ii = 0 ; ii < copy1_c_values.size() ; ++ii )
    {
        double const c_value = c_dist( prng );
        copy1_c_values[ ii ] = c_value;
        ::NS(TypeFixedNumPtrs_set_c_value)( copy1, ii, c_value );
    }

    ASSERT_TRUE( std::equal( copy1_b_values.begin(), copy1_b_values.end(),
            ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy1 ) ) );

    ASSERT_TRUE( std::equal( copy1_c_values.begin(), copy1_c_values.end(),
            ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy1 ) ) );

    _obj2_t orig2;
    ::NS(TypeFixedNumPtrs_preset)( &orig2 );
    ::NS(TypeFixedNumPtrs_set_a)( &orig2, double{ 137.0 } );

    std::vector< double > orig2_b_values( 42 );
    std::vector< double > orig2_c_values( 255 );

    for( _size_t ii = 0 ; ii < orig2_b_values.size() ; ++ii )
    {
        double const b_value = b_dist( prng );
        orig2_b_values[ ii ] = b_value;
    }

    for( _size_t ii = 0 ; ii < orig2_c_values.size() ; ++ii )
    {
        double const c_value = c_dist( prng );
        orig2_c_values[ ii ] = c_value;
    }

    ::NS(TypeFixedNumPtrs_set_num_b_values)( &orig2, orig2_b_values.size() );
    ::NS(TypeFixedNumPtrs_set_b_values_addr)( &orig2,
        reinterpret_cast< uintptr_t >( orig2_b_values.data() ) );

    ::NS(TypeFixedNumPtrs_set_num_c_values)( &orig2, orig2_c_values.size() );
    ::NS(TypeFixedNumPtrs_set_c_values_addr)( &orig2,
        reinterpret_cast< uintptr_t >( orig2_c_values.data() ) );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    required_buffer_size = _size_t{ 0 };
    requ_num_slots = _size_t{ 0 };
    requ_num_objs  = _size_t{ 0 };
    requ_num_ptrs  = _size_t{ 0 };

    ASSERT_FALSE( view.can_add_copy_of_object< _obj2_t >(
        &orig2, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs ) );

    ASSERT_TRUE( required_buffer_size > view.size() );
    ASSERT_TRUE( requ_num_objs  == _size_t{ 2 } );
    ASSERT_TRUE( requ_num_ptrs  == _size_t{ 4 } );
    ASSERT_TRUE( requ_num_slots >  _size_t{ 0 } );
    ASSERT_TRUE( requ_num_slots ==
        ( st::CObjElem_required_num_slots< _obj2_t >( slot_size, &orig1 ) +
          st::CObjElem_required_num_slots< _obj2_t >( slot_size, &orig2 ) ) );

    ASSERT_TRUE( st::COBJECTS_STATUS_SUCCESS == view.reallocate(
                        requ_num_slots, requ_num_objs, requ_num_ptrs ) );

    ASSERT_TRUE( view.size() >= required_buffer_size );
    ASSERT_TRUE( view.max_slots()    >= requ_num_slots );
    ASSERT_TRUE( view.max_objects()  >= requ_num_objs  );
    ASSERT_TRUE( view.max_pointers() >= requ_num_ptrs  );

    ASSERT_TRUE( view.can_add_copy_of_object< _obj2_t >( &orig2 ) );

    _obj2_t* copy2 = st::CBufferView_add_copy_of_object_detail(
        view, &orig2, &required_buffer_size, &requ_num_slots,
            &requ_num_objs, &requ_num_ptrs );

    ASSERT_TRUE( copy2 != nullptr );
    ASSERT_TRUE( copy2 != &orig2  );

    ASSERT_TRUE( copy1 == view.get_object< _obj2_t >( 0 ) );
    ASSERT_TRUE( copy2 != copy1  );

    ASSERT_TRUE( view.n_objects()  == _size_t{ 2 } );
    ASSERT_TRUE( view.n_slots()    == view.max_slots()    );
    ASSERT_TRUE( view.n_objects()  == view.max_objects()  );
    ASSERT_TRUE( view.n_pointers() == view.max_pointers() );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_a)( copy2 ) ==
                 ::NS(TypeFixedNumPtrs_a)( &orig2 ) );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_num_b_values)( copy2 ) ==
                 ::NS(TypeFixedNumPtrs_num_b_values)( &orig2 ) );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_num_c_values)( copy2 ) ==
                 ::NS(TypeFixedNumPtrs_num_c_values)( &orig2 ) );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy2 ) !=
                 nullptr );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy2 ) !=
                 ::NS(TypeFixedNumPtrs_const_b_values_begin)( &orig2 ) );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy2 ) !=
                 nullptr );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy2 ) !=
                 ::NS(TypeFixedNumPtrs_const_c_values_begin)( &orig2 ) );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_b_values_end)( copy2 ) !=
                 nullptr );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_b_values_end)( copy2 ) !=
                 ::NS(TypeFixedNumPtrs_const_b_values_end)( &orig2 ) );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_c_values_end)( copy2 ) !=
                 nullptr );

    ASSERT_TRUE( ::NS(TypeFixedNumPtrs_const_c_values_end)( copy2 ) !=
                 ::NS(TypeFixedNumPtrs_const_c_values_end)( &orig2 ) );

    ASSERT_TRUE( static_cast< SIXTRL_UINT64_T >( std::distance(
                    ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy2 ),
                    ::NS(TypeFixedNumPtrs_const_b_values_end)( copy2 ) ) ) ==
                 ::NS(TypeFixedNumPtrs_num_b_values)( &orig2 ) );

    ASSERT_TRUE( static_cast< SIXTRL_UINT64_T >( std::distance(
                    ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy2 ),
                    ::NS(TypeFixedNumPtrs_const_c_values_end)( copy2 ) ) ) ==
                 ::NS(TypeFixedNumPtrs_num_c_values)( &orig2 ) );

    ASSERT_TRUE( std::equal(
                    ::NS(TypeFixedNumPtrs_const_b_values_begin)( &orig2 ),
                    ::NS(TypeFixedNumPtrs_const_b_values_end)( &orig2 ),
                    ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy2 ) ) );

    ASSERT_TRUE( std::equal(
                    ::NS(TypeFixedNumPtrs_const_c_values_begin)( &orig2 ),
                    ::NS(TypeFixedNumPtrs_const_c_values_end)( &orig2 ),
                    ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy2 ) ) );

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    ASSERT_TRUE( static_cast< SIXTRL_UINT64_T >( std::distance(
                    ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy1 ),
                    ::NS(TypeFixedNumPtrs_const_b_values_end)( copy1 ) ) ) ==
                 ::NS(TypeFixedNumPtrs_num_b_values)( copy1 ) );

    ASSERT_TRUE( static_cast< SIXTRL_UINT64_T >( std::distance(
                    ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy1 ),
                    ::NS(TypeFixedNumPtrs_const_c_values_end)( copy1 ) ) ) ==
                 ::NS(TypeFixedNumPtrs_num_c_values)( copy1 ) );

    ASSERT_TRUE( std::equal( copy1_b_values.begin(), copy1_b_values.end(),
                    ::NS(TypeFixedNumPtrs_const_b_values_begin)( copy1 ) ) );

    ASSERT_TRUE( std::equal( copy1_c_values.begin(), copy1_c_values.end(),
                    ::NS(TypeFixedNumPtrs_const_c_values_begin)( copy1 ) ) );
}
