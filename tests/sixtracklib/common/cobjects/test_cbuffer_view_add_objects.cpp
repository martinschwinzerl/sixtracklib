#include "sixtracklib/common/cobjects/cbuffer_view.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/testlib.h"
#include "sixtracklib/testlib/common/cobjects/type_no_ptrs.h"
#include "sixtracklib/testlib/common/cobjects/type_fixed_num_ptrs.h"

TEST( CxxCommonCObjectsCBufferViewAddObjectsTests, BasicUsage )
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

