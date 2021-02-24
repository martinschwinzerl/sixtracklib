#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/sixtracklib.h"
#include "sixtracklib/testlib.hpp"

/* ========================================================================= */
/* ====  Test flat-memory based minimal buffer implementation                */

TEST( C99CommonCObjectsFlatBufferTests, InitAndReserve )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;
    using raw_type  = st::cobj_raw_type;

    std::vector< raw_type > data_buffer( st_size_t{ 4096 }, raw_type{ 0 } );

    constexpr st_size_t const SLOTS_ID     = st::CBUFFER_SECTION_ID_SLOTS;
    constexpr st_size_t const OBJECTS_ID   = st::CBUFFER_SECTION_ID_OBJECTS;
    constexpr st_size_t const DATAPTRS_ID  = st::CBUFFER_SECTION_ID_POINTERS;
    constexpr st_size_t const GARBAGE_ID   = st::CBUFFER_SECTION_ID_GARBAGE;
    constexpr st_size_t const slot_size    = st::CBUFFER_DEFAULT_SLOT_SIZE;

    st_size_t max_num_objects              = st_size_t{ 0 };
    st_size_t max_num_slots                = st_size_t{ 0 };
    st_size_t max_num_dataptrs             = st_size_t{ 0 };
    st_size_t max_num_garbage_range        = st_size_t{ 0 };

    st::status_type status = ::NS(CObjFlatBuffer_init_empty)(
        data_buffer.data(), data_buffer.size(), slot_size );

    ASSERT_TRUE( status == st::STATUS_SUCCESS );

    st_size_type requ_buffer_size = st_size_type{ 0 };

    ASSERT_TRUE( ::NS(CObjFlatBuffer_can_allocate)( data_buffer.data(),
        data_buffer.size(), slot_size, max_num_slots, max_num_objects,
            max_num_dataptrs, max_num_garbage_range, &requ_buffer_size ) );

    ASSERT_TRUE( requ_buffer_size >= ::NS(CBuffer_min_buffer_size)( slot_size ) );

    st_size_t predicted_size = ::NS(CObjFlatBuffer_calc_required_buffer_size)(
        data_buffer.data(), max_num_slots, max_num_objects, max_num_dataptrs,
            max_num_garbage_range, slot_size );

    ASSERT_TRUE( predicted_size >= ::NS(CBuffer_min_buffer_size)( slot_size ) );
    ASSERT_TRUE( predicted_size == requ_buffer_size );

    st_size_t current_buffer_size = st_size_t{ 0 };

    status = ::NS(CObjFlatBuffer_allocate)( data_buffer.data(),
        data_buffer.size(), slot_size, max_num_slots, max_num_objects,
            max_num_dataptrs, max_num_garbage_range, &current_buffer_size );

    ASSERT_TRUE( status == st::STATUS_SUCCESS );
    ASSERT_TRUE( predicted_size == current_buffer_size );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_max_num_entities)(
        data_buffer.data(), SLOTS_ID, slot_size ) == max_num_slots );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_max_num_entities)(
        data_buffer.data(), OBJECTS_ID, slot_size ) == max_num_objects );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_max_num_entities)(
        data_buffer.data(), DATAPTRS_ID, slot_size ) == max_num_dataptrs );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_max_num_entities)(
        data_buffer.data(), GARBAGE_ID, slot_size ) == max_num_garbage_range );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), SLOTS_ID, slot_size ) == st_size_t{ 0 } );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), OBJECTS_ID, slot_size ) == st_size_t{ 0 } );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), DATAPTRS_ID, slot_size ) == st_size_t{ 0 } );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), GARBAGE_ID, slot_size ) == st_size_t{ 0 } );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_size)(
        data_buffer.data(), slot_size ) == current_buffer_size );

    /* -------------------------------------------------------------------- */

    max_num_objects       = st_size_t{ 1 };
    max_num_slots         = st_size_t{ 8 };
    max_num_dataptrs      = st_size_t{ 0 };
    max_num_garbage_range = st_size_t{ 0 };

    predicted_size = ::NS(CObjFlatBuffer_calc_required_buffer_size)(
        data_buffer.data(), max_num_slots, max_num_objects, max_num_dataptrs,
            max_num_garbage_range, slot_size );

    ASSERT_TRUE( predicted_size >  current_buffer_size );
    ASSERT_TRUE( predicted_size <= data_buffer.size()  );

    SIXTRL_ARGPTR_DEC st_size_type requ_n_slots   = st_size_type{ 0 };
    SIXTRL_ARGPTR_DEC st_size_type requ_n_objs    = st_size_type{ 0 };
    SIXTRL_ARGPTR_DEC st_size_type requ_n_ptrs    = st_size_type{ 0 };
    SIXTRL_ARGPTR_DEC st_size_type requ_n_garbage = st_size_type{ 0 };

    ASSERT_TRUE( ::NS(CObjFlatBuffer_can_reallocate)( data_buffer.data(),
        data_buffer.size(), slot_size, max_num_slots, max_num_objects,
            max_num_dataptrs, max_num_garbage_range, &requ_buffer_size,
                &requ_n_slots, &requ_n_objs, &requ_n_ptrs, &requ_n_garbage ) );

    ASSERT_TRUE( requ_buffer_size == predicted_size );
    ASSERT_TRUE( requ_n_slots     == max_num_slots );
    ASSERT_TRUE( requ_n_objs      == max_num_objects );
    ASSERT_TRUE( requ_n_ptrs      == max_num_dataptrs );
    ASSERT_TRUE( requ_n_garbage   == max_num_garbage_range );

    status = ::NS(CObjFlatBuffer_reallocate)( data_buffer.data(),
        data_buffer.size(), slot_size, max_num_slots, max_num_objects,
            max_num_dataptrs, max_num_garbage_range,
                &current_buffer_size );

    ASSERT_TRUE( status == st::STATUS_SUCCESS );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_max_num_entities)(
        data_buffer.data(), SLOTS_ID, slot_size ) == max_num_slots );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_max_num_entities)(
        data_buffer.data(), OBJECTS_ID, slot_size ) == max_num_objects );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_max_num_entities)(
        data_buffer.data(), DATAPTRS_ID, slot_size ) == max_num_dataptrs );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_max_num_entities)(
        data_buffer.data(), GARBAGE_ID, slot_size ) == max_num_garbage_range );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), SLOTS_ID, slot_size ) == st_size_t{ 0 } );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), OBJECTS_ID, slot_size ) == st_size_t{ 0 } );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), DATAPTRS_ID, slot_size ) == st_size_t{ 0 } );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), GARBAGE_ID, slot_size ) == st_size_t{ 0 } );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    using address_t = ::NS(cobj_addr_type);
    using ptr_to_addr_t = address_t*;

    std::vector< address_t > cmp_slot_values(
        max_num_slots, st::COBJECTS_NULL_ADDRESS );

    address_t cnt = address_t{ 0 };

    ptr_to_addr_t slot_it = reinterpret_cast< ptr_to_addr_t >(
        ::NS(CObjFlatBuffer_ptr_section_data_begin)(
            data_buffer.data(), SLOTS_ID, slot_size ) );

    ptr_to_addr_t slot_end = slot_it;
    std::advance( slot_end, max_num_slots );

    auto cmp_slot_it = cmp_slot_values.begin();

    for( ; slot_it != slot_end ; ++slot_it, ++cnt, ++cmp_slot_it )
    {
        *slot_it     = cnt;
        *cmp_slot_it = cnt;
    }

    ::NS(CObjFlatBuffer_set_section_num_entities)(
        data_buffer.data(), SLOTS_ID, max_num_slots, slot_size );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    using type_id_t = ::NS(cobj_obj_id_type);
    using object_t = ::NS(CObjIndex);
    using ptr_to_obj_t  = object_t*;

    std::vector< object_t > cmp_object_values( max_num_objects, object_t{} );

    ptr_to_obj_t obj_it  = reinterpret_cast< ptr_to_obj_t >(
        ::NS(CObjFlatBuffer_ptr_section_data_begin)(
            data_buffer.data(), OBJECTS_ID, slot_size ) );

    ptr_to_obj_t  obj_end = obj_it;
    std::advance( obj_end, max_num_objects );

    auto cmp_obj_it = cmp_object_values.begin();

    type_id_t  type_id = type_id_t{ 1 };
    st_size_t size = sizeof( address_t );

    for( ; obj_it != obj_end ; ++obj_it, ++type_id, ++cmp_obj_it )
    {
        ::NS(CObjIndex_preset)( obj_it );
        ::NS(CObjIndex_set_type_id)( obj_it, type_id );
        ::NS(CObjIndex_set_size)( obj_it, size );

        *cmp_obj_it = *obj_it;
    }

    ::NS(CObjFlatBuffer_set_section_num_entities)(
        data_buffer.data(), OBJECTS_ID, max_num_objects, slot_size );

    /* -------------------------------------------------------------------- */

    st_size_t cur_num_objects  = ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), OBJECTS_ID, slot_size );

    st_size_t cur_num_slots    = ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), SLOTS_ID, slot_size );

    st_size_t cur_num_dataptrs = ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), DATAPTRS_ID, slot_size );

    st_size_t cur_num_garbage_range = ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), GARBAGE_ID, slot_size );

    max_num_objects       += st_size_t{ 2 };
    max_num_slots         += st_size_t{ 8 };
    max_num_dataptrs      += st_size_t{ 4 };
    max_num_garbage_range += st_size_t{ 1 };

    predicted_size = ::NS(CObjFlatBuffer_calc_required_buffer_size)(
        data_buffer.data(), max_num_slots, max_num_objects, max_num_dataptrs,
            max_num_garbage_range, slot_size );

    ASSERT_TRUE( predicted_size > current_buffer_size );
    ASSERT_TRUE( predicted_size < data_buffer.size()  );

    status = ::NS(CObjFlatBuffer_reallocate)( data_buffer.data(),
        data_buffer.size(), slot_size, max_num_slots, max_num_objects,
            max_num_dataptrs, max_num_garbage_range, &current_buffer_size );

    ASSERT_TRUE( status == st::STATUS_SUCCESS );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_max_num_entities)(
        data_buffer.data(), SLOTS_ID, slot_size ) == max_num_slots );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_max_num_entities)(
        data_buffer.data(), OBJECTS_ID, slot_size ) == max_num_objects );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_max_num_entities)(
        data_buffer.data(), DATAPTRS_ID, slot_size ) == max_num_dataptrs );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_max_num_entities)(
        data_buffer.data(), GARBAGE_ID, slot_size ) == max_num_garbage_range );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), SLOTS_ID, slot_size ) == cur_num_slots );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), OBJECTS_ID, slot_size ) == cur_num_objects );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), DATAPTRS_ID, slot_size ) == cur_num_dataptrs );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_section_num_entities)(
        data_buffer.data(), GARBAGE_ID, slot_size ) == cur_num_garbage_range );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    slot_it = reinterpret_cast< ptr_to_addr_t >(
        ::NS(CObjFlatBuffer_ptr_section_data_begin)(
            data_buffer.data(), SLOTS_ID, slot_size ) );

    slot_end = reinterpret_cast< ptr_to_addr_t >(
        ::NS(CObjFlatBuffer_ptr_section_data_end)(
            data_buffer.data(), SLOTS_ID, slot_size ) );

    ASSERT_TRUE( std::distance( slot_it, slot_end ) ==
        static_cast< std::ptrdiff_t >(
            ::NS(CObjFlatBuffer_section_num_entities)(
                data_buffer.data(), SLOTS_ID, slot_size ) ) );

    cmp_slot_it = cmp_slot_values.begin();

    for( ; slot_it != slot_end ; ++slot_it, ++cmp_slot_it )
    {
        ASSERT_TRUE( *slot_it == *cmp_slot_it );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    obj_it  = reinterpret_cast< ptr_to_obj_t >(
        ::NS(CObjFlatBuffer_ptr_section_data_begin)(
            data_buffer.data(), OBJECTS_ID, slot_size ) );

    obj_end = reinterpret_cast< ptr_to_obj_t >(
        ::NS(CObjFlatBuffer_ptr_section_data_end)(
            data_buffer.data(), OBJECTS_ID, slot_size ) );

    ASSERT_TRUE( std::distance( obj_it, obj_end ) ==
        static_cast< std::ptrdiff_t >(
            ::NS(CObjFlatBuffer_section_num_entities)(
                data_buffer.data(), OBJECTS_ID, slot_size ) ) );

    cmp_obj_it = cmp_object_values.begin();

    for( ; obj_it != obj_end ; ++obj_it, ++type_id, ++cmp_obj_it )
    {
        ASSERT_TRUE( ::NS(CObjIndex_type_id)( obj_it ) ==
                     ::NS(CObjIndex_type_id)( &( *cmp_obj_it ) ) );

        ASSERT_TRUE( ::NS(CObjIndex_size)( obj_it ) ==
                     ::NS(CObjIndex_size)( &( *cmp_obj_it ) ) );

        ASSERT_TRUE( ::NS(CObjIndex_begin_addr)( obj_it ) ==
                     ::NS(CObjIndex_begin_addr)( &( *cmp_obj_it ) ) );
    }
}

TEST( C99CommonCObjectsFlatBufferTests, AddElements )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using raw_type  = st::cobj_raw_type;
    using prng_seed_type = std::mt19937_64::result_type;
    using real_type = ::NS(cobj_test_real_type);
    using uint_type = ::NS(cobj_test_uint64_type);

    prng_seed_type const seed = prng_seed_type{ 20210112 };
    std::mt19937_64 prng( seed );
    std::vector< ::NS(CObjTestNoPtrs) > cmp_no_ptrs;

    st::cobj_size_type const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    st::cobj_size_type const NUM_CMP_ELEMS = st::cobj_size_type{ 5 };
    st::cobj_size_type const NUM_COPIES_PER_ELEM = st::cobj_size_type{ 8 };

    st::cobj_size_type requ_n_slots = st::cobj_size_type{ 0 };
    st::cobj_size_type requ_n_objs  = st::cobj_size_type{ 0 };
    st::cobj_size_type requ_n_ptrs  = st::cobj_size_type{ 0 };

    st::status_type status = st::testlib::CObjTestNoPtrs_prepare_cmp_elements(
        cmp_no_ptrs, NUM_CMP_ELEMS, prng, slot_size, NUM_COPIES_PER_ELEM,
            &requ_n_slots, &requ_n_objs, &requ_n_ptrs );

    ASSERT_TRUE( status == st::STATUS_SUCCESS );
    ASSERT_TRUE( requ_n_slots > st::cobj_size_type{ 0 } );
    ASSERT_TRUE( requ_n_objs >= NUM_CMP_ELEMS * NUM_COPIES_PER_ELEM );
    ASSERT_TRUE( requ_n_ptrs == st::cobj_size_type{ 0 } );

    /* ---------------------------------------------------------------------- */

    std::vector< ::NS(CObjTestDataptrs) > cmp_dataptrs;
    std::vector< real_type > cmp_dataptrs_bc_data;

    st::cobj_size_type const min_b_capacity = st::cobj_size_type{ 5 };
    st::cobj_size_type const max_b_capacity = st::cobj_size_type{ 10 };
    st::cobj_size_type const min_c_capacity = st::cobj_size_type{ 8 };
    st::cobj_size_type const max_c_capacity = st::cobj_size_type{ 16 };

    status = st::testlib::CObjTestDataptrs_prepare_cmp_elements(
        cmp_dataptrs, cmp_dataptrs_bc_data, NUM_CMP_ELEMS, min_b_capacity,
            max_b_capacity, min_c_capacity, max_c_capacity, prng,
                slot_size, NUM_COPIES_PER_ELEM, &requ_n_slots, &requ_n_objs,
                    &requ_n_ptrs );

    ASSERT_TRUE( status == st::STATUS_SUCCESS );

    std::vector< raw_type > flat_buffer( 1u << 20, raw_type{ 0 } );
    st::cobj_size_type requ_buffer_size = st::cobj_size_type{ 0 };

    status = ::NS(CObjFlatBuffer_init_empty_detailed)(
        flat_buffer.data(), flat_buffer.size(), slot_size,
            requ_n_slots, requ_n_objs, requ_n_ptrs, 0u, &requ_buffer_size );

    ASSERT_TRUE( status == st::STATUS_SUCCESS );
    ASSERT_TRUE( requ_buffer_size < flat_buffer.size() );
    ASSERT_TRUE( ::NS(CObjFlatBuffer_size)( flat_buffer.data(), slot_size ) ==
                 requ_buffer_size );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_max_num_slots)(
        flat_buffer.data(), slot_size ) >= requ_n_slots );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_max_num_objects)(
        flat_buffer.data(), slot_size ) >= requ_n_objs );

    ASSERT_TRUE( ::NS(CObjFlatBuffer_max_num_pointers)(
        flat_buffer.data(), slot_size ) >= requ_n_ptrs );

    /* --------------------------------------------------------------------- */

    NS(cobj_size_type) prev_n_slots = NS(CObjFlatBuffer_num_slots)(
        flat_buffer.data(), slot_size );

    NS(cobj_size_type) prev_n_objects = NS(CObjFlatBuffer_num_objects)(
        flat_buffer.data(), slot_size );

    NS(cobj_size_type) prev_n_ptrs = NS(CObjFlatBuffer_num_pointers)(
        flat_buffer.data(), slot_size );

    NS(cobj_size_type) cur_n_slots = prev_n_slots;
    NS(cobj_size_type) cur_n_objects = prev_n_objects;
    NS(cobj_size_type) cur_n_ptrs = prev_n_ptrs;

    for( uint_type ii = 0u ; ii < NUM_CMP_ELEMS ; ++ii )
    {
        SIXTRL_CBUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex) const* no_ptrs_obj =
            ::NS(CObjFlatBuffer_add_copy_of_trivial_object)(
                flat_buffer.data(), slot_size, &cmp_no_ptrs[ ii ],
                ::NS(CObjTestNoPtrs_cobj_reserved_handle_size)( slot_size ),
                ::NS(CObjTestNoPtrs_cobj_type_id)(), true );

        ASSERT_TRUE( no_ptrs_obj != nullptr );

        ASSERT_TRUE( ::NS(CObjIndex_type_id)( no_ptrs_obj ) ==
            ::NS(CObjTestNoPtrs_cobj_type_id)() );

        ASSERT_TRUE( ::NS(CObjIndex_begin_addr)( no_ptrs_obj ) !=
            ::NS(COBJECTS_NULL_ADDRESS) );

        ASSERT_TRUE( ::NS(CObjIndex_size)( no_ptrs_obj ) ==
            ::NS(CObjTestNoPtrs_cobj_reserved_handle_size)( slot_size ) );

        cur_n_slots = ::NS(CObjFlatBuffer_num_slots)(
            flat_buffer.data(), slot_size );

        cur_n_objects = ::NS(CObjFlatBuffer_num_objects)(
            flat_buffer.data(), slot_size );

        cur_n_ptrs = ::NS(CObjFlatBuffer_num_pointers)(
            flat_buffer.data(), slot_size );

        ASSERT_TRUE( cur_n_slots == prev_n_slots +
            ( NS(CObjTestNoPtrs_cobj_reserved_handle_size)(
                slot_size ) / slot_size ) );
        ASSERT_TRUE( cur_n_objects == prev_n_objects + 1u );
        ASSERT_TRUE( cur_n_ptrs == prev_n_ptrs );

        prev_n_slots   = cur_n_slots;
        prev_n_objects = cur_n_objects;
        prev_n_ptrs    = cur_n_ptrs;

        auto added_no_ptrs_elem =
            ::NS(CObjTestNoPtrs_const_from_cobj_index)( no_ptrs_obj );

        ASSERT_TRUE( added_no_ptrs_elem != nullptr );
        ASSERT_TRUE( added_no_ptrs_elem != &cmp_no_ptrs[ ii ] );
        ASSERT_TRUE( reinterpret_cast< uintptr_t >( added_no_ptrs_elem ) ==
                     static_cast< uintptr_t >( ::NS(CObjIndex_begin_addr)(
                         no_ptrs_obj ) ) );

        ASSERT_TRUE( ::NS(CObjTestNoPtrs_compare)(
            added_no_ptrs_elem, &cmp_no_ptrs[ ii ] ) == 0 );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_ARGPTR_DEC NS(cobj_size_type) OFFSETS[ 2 ];
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) SIZES[ 2 ];
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) COUNTS[ 2 ];

        status = NS(CObjTestDataptrs_cobj_attributes_offsets)(
            &OFFSETS[ 0 ], 2u, &cmp_dataptrs[ ii ], slot_size );
        ASSERT_TRUE( status == st::STATUS_SUCCESS );

        status = NS(CObjTestDataptrs_cobj_attributes_sizes)(
            &SIZES[ 0 ], 2u, &cmp_dataptrs[ ii ], slot_size );
        ASSERT_TRUE( status == st::STATUS_SUCCESS );

        status = NS(CObjTestDataptrs_cobj_attributes_counts)(
            &COUNTS[ 0 ], 2u, &cmp_dataptrs[ ii ], slot_size );
        ASSERT_TRUE( status == st::STATUS_SUCCESS );

        SIXTRL_CBUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex) const* dataptrs_obj =
            ::NS(CObjFlatBuffer_add_copy_of_object)(
                flat_buffer.data(), slot_size, &cmp_dataptrs[ ii ],
                ::NS(CObjTestDataptrs_cobj_reserved_handle_size)( slot_size ),
                ::NS(CObjTestDataptrs_cobj_type_id)(),
                ::NS(CObjTestDataptrs_cobj_num_dataptrs)(),
                &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true );

        ASSERT_TRUE( dataptrs_obj != nullptr );

        ASSERT_TRUE( ::NS(CObjIndex_type_id)( dataptrs_obj ) ==
            ::NS(CObjTestDataptrs_cobj_type_id)() );

        ASSERT_TRUE( ::NS(CObjIndex_begin_addr)( dataptrs_obj ) !=
            ::NS(COBJECTS_NULL_ADDRESS) );

        ASSERT_TRUE( ::NS(CObjIndex_size)( dataptrs_obj ) >
            ::NS(CObjTestDataptrs_cobj_reserved_handle_size)( slot_size ) );

        cur_n_slots = ::NS(CObjFlatBuffer_num_slots)(
            flat_buffer.data(), slot_size );

        cur_n_objects = ::NS(CObjFlatBuffer_num_objects)(
            flat_buffer.data(), slot_size );

        cur_n_ptrs = ::NS(CObjFlatBuffer_num_pointers)(
            flat_buffer.data(), slot_size );

        ASSERT_TRUE( cur_n_slots > prev_n_slots + (
            NS(CObjTestDataptrs_cobj_reserved_handle_size)(
                slot_size ) / slot_size ) );
        ASSERT_TRUE( cur_n_objects == prev_n_objects + 1u );
        ASSERT_TRUE( cur_n_ptrs ==
            prev_n_ptrs + NS(CObjTestDataptrs_cobj_num_dataptrs)() );

        prev_n_slots   = cur_n_slots;
        prev_n_objects = cur_n_objects;
        prev_n_ptrs    = cur_n_ptrs;

        auto added_dataptrs_elem =
            ::NS(CObjTestDataptrs_const_from_cobj_index)( dataptrs_obj );

        ASSERT_TRUE( added_dataptrs_elem != nullptr );
        ASSERT_TRUE( added_dataptrs_elem != &cmp_dataptrs[ ii ] );
        ASSERT_TRUE( reinterpret_cast< uintptr_t >( added_dataptrs_elem ) ==
                     static_cast< uintptr_t >( ::NS(CObjIndex_begin_addr)(
                         dataptrs_obj ) ) );

        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            added_dataptrs_elem, &cmp_dataptrs[ ii ] ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        auto new_no_ptrs_elem = NS(CObjTestNoPtrs_cobj_flat_buffer_new)(
            flat_buffer.data(), slot_size );

        ASSERT_TRUE( new_no_ptrs_elem != nullptr );
        ASSERT_TRUE( new_no_ptrs_elem != &cmp_no_ptrs[ ii ] );

        cur_n_slots = ::NS(CObjFlatBuffer_num_slots)(
            flat_buffer.data(), slot_size );

        cur_n_objects = ::NS(CObjFlatBuffer_num_objects)(
            flat_buffer.data(), slot_size );

        cur_n_ptrs = ::NS(CObjFlatBuffer_num_pointers)(
            flat_buffer.data(), slot_size );

        ASSERT_TRUE( cur_n_slots == prev_n_slots +
            ( NS(CObjTestNoPtrs_cobj_reserved_handle_size)(
                slot_size ) / slot_size ) );
        ASSERT_TRUE( cur_n_objects == prev_n_objects + 1u );
        ASSERT_TRUE( cur_n_ptrs == prev_n_ptrs );

        prev_n_slots   = cur_n_slots;
        prev_n_objects = cur_n_objects;
        prev_n_ptrs    = cur_n_ptrs;

        ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CObjTestNoPtrs_copy)(
            new_no_ptrs_elem, &cmp_no_ptrs[ ii ] ) );

        ASSERT_TRUE( 0 == ::NS(CObjTestNoPtrs_compare)(
            new_no_ptrs_elem, &cmp_no_ptrs[ ii ] ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        auto new_dataptrs_elem = NS(CObjTestDataptrs_cobj_flat_buffer_new)(
            flat_buffer.data(), slot_size,
                ::NS(CObjTestDataptrs_b_capacity)( &cmp_dataptrs[ ii ] ),
                ::NS(CObjTestDataptrs_c_capacity)( &cmp_dataptrs[ ii ] ) );

        ASSERT_TRUE( new_dataptrs_elem != nullptr );
        ASSERT_TRUE( new_dataptrs_elem != &cmp_dataptrs[ ii ] );
        ASSERT_TRUE( ::NS(CObjTestDataptrs_b_capacity)( new_dataptrs_elem ) ==
                     ::NS(CObjTestDataptrs_b_capacity)( &cmp_dataptrs[ ii ] ) );
        ASSERT_TRUE( ::NS(CObjTestDataptrs_c_capacity)( new_dataptrs_elem ) ==
                     ::NS(CObjTestDataptrs_c_capacity)( &cmp_dataptrs[ ii ] ) );

        cur_n_slots = ::NS(CObjFlatBuffer_num_slots)(
            flat_buffer.data(), slot_size );

        cur_n_objects = ::NS(CObjFlatBuffer_num_objects)(
            flat_buffer.data(), slot_size );

        cur_n_ptrs = ::NS(CObjFlatBuffer_num_pointers)(
            flat_buffer.data(), slot_size );

        ASSERT_TRUE( cur_n_slots > prev_n_slots + (
            NS(CObjTestDataptrs_cobj_reserved_handle_size)(
                slot_size ) / slot_size ) );
        ASSERT_TRUE( cur_n_objects == prev_n_objects + 1u );
        ASSERT_TRUE( cur_n_ptrs ==
            prev_n_ptrs + NS(CObjTestDataptrs_cobj_num_dataptrs)() );

        prev_n_slots   = cur_n_slots;
        prev_n_objects = cur_n_objects;
        prev_n_ptrs    = cur_n_ptrs;

        ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CObjTestDataptrs_copy)(
            new_dataptrs_elem, &cmp_dataptrs[ ii ] ) );

        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            new_dataptrs_elem, &cmp_dataptrs[ ii ] ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        new_no_ptrs_elem = nullptr;
        new_no_ptrs_elem = NS(CObjTestNoPtrs_cobj_flat_buffer_add)(
            flat_buffer.data(), slot_size,
            ::NS(CObjTestNoPtrs_a)( &cmp_no_ptrs[ ii ] ),
            ::NS(CObjTestNoPtrs_b)( &cmp_no_ptrs[ ii ] ),
            ::NS(CObjTestNoPtrs_c_const_begin)( &cmp_no_ptrs[ ii ] ),
            ::NS(CObjTestNoPtrs_d)( &cmp_no_ptrs[ ii ] ) );

        ASSERT_TRUE( new_no_ptrs_elem != nullptr );
        ASSERT_TRUE( new_no_ptrs_elem != &cmp_no_ptrs[ ii ] );

        cur_n_slots = ::NS(CObjFlatBuffer_num_slots)(
            flat_buffer.data(), slot_size );

        cur_n_objects = ::NS(CObjFlatBuffer_num_objects)(
            flat_buffer.data(), slot_size );

        cur_n_ptrs = ::NS(CObjFlatBuffer_num_pointers)(
            flat_buffer.data(), slot_size );

        ASSERT_TRUE( cur_n_slots == prev_n_slots +
            ( NS(CObjTestNoPtrs_cobj_reserved_handle_size)(
                slot_size ) / slot_size ) );
        ASSERT_TRUE( cur_n_objects == prev_n_objects + 1u );
        ASSERT_TRUE( cur_n_ptrs == prev_n_ptrs );

        prev_n_slots   = cur_n_slots;
        prev_n_objects = cur_n_objects;
        prev_n_ptrs    = cur_n_ptrs;

        ASSERT_TRUE( 0 == ::NS(CObjTestNoPtrs_compare)(
            new_no_ptrs_elem, &cmp_no_ptrs[ ii ] ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        new_dataptrs_elem = nullptr;
        new_dataptrs_elem = NS(CObjTestDataptrs_cobj_flat_buffer_add)(
            flat_buffer.data(), slot_size,
                ::NS(CObjTestDataptrs_a)( &cmp_dataptrs[ ii ] ),
                ::NS(CObjTestDataptrs_b_capacity)( &cmp_dataptrs[ ii ] ),
                ::NS(CObjTestDataptrs_b_length)( &cmp_dataptrs[ ii ] ),
                reinterpret_cast< uintptr_t >(
                    ::NS(CObjTestDataptrs_b_const_begin)( &cmp_dataptrs[ ii ] ) ),
                ::NS(CObjTestDataptrs_c_capacity)( &cmp_dataptrs[ ii ] ),
                ::NS(CObjTestDataptrs_c_length)( &cmp_dataptrs[ ii ] ),
                reinterpret_cast< uintptr_t >(
                    ::NS(CObjTestDataptrs_c_const_begin)( &cmp_dataptrs[ ii ] )
                    ) );

        ASSERT_TRUE( new_dataptrs_elem != nullptr );
        ASSERT_TRUE( new_dataptrs_elem != &cmp_dataptrs[ ii ] );
        ASSERT_TRUE( ::NS(CObjTestDataptrs_b_capacity)( new_dataptrs_elem ) ==
                     ::NS(CObjTestDataptrs_b_capacity)( &cmp_dataptrs[ ii ] ) );
        ASSERT_TRUE( ::NS(CObjTestDataptrs_c_capacity)( new_dataptrs_elem ) ==
                     ::NS(CObjTestDataptrs_c_capacity)( &cmp_dataptrs[ ii ] ) );

        cur_n_slots = ::NS(CObjFlatBuffer_num_slots)(
            flat_buffer.data(), slot_size );

        cur_n_objects = ::NS(CObjFlatBuffer_num_objects)(
            flat_buffer.data(), slot_size );

        cur_n_ptrs = ::NS(CObjFlatBuffer_num_pointers)(
            flat_buffer.data(), slot_size );

        ASSERT_TRUE( cur_n_slots > prev_n_slots + (
            NS(CObjTestDataptrs_cobj_reserved_handle_size)(
                slot_size ) / slot_size ) );
        ASSERT_TRUE( cur_n_objects == prev_n_objects + 1u );
        ASSERT_TRUE( cur_n_ptrs ==
            prev_n_ptrs + NS(CObjTestDataptrs_cobj_num_dataptrs)() );

        prev_n_slots   = cur_n_slots;
        prev_n_objects = cur_n_objects;
        prev_n_ptrs    = cur_n_ptrs;

        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            new_dataptrs_elem, &cmp_dataptrs[ ii ] ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        new_no_ptrs_elem = nullptr;
        new_no_ptrs_elem = NS(CObjTestNoPtrs_cobj_flat_buffer_add_copy)(
            flat_buffer.data(), slot_size, &cmp_no_ptrs[ ii ] );

        ASSERT_TRUE( new_no_ptrs_elem != nullptr );
        ASSERT_TRUE( new_no_ptrs_elem != &cmp_no_ptrs[ ii ] );

        cur_n_slots = ::NS(CObjFlatBuffer_num_slots)(
            flat_buffer.data(), slot_size );

        cur_n_objects = ::NS(CObjFlatBuffer_num_objects)(
            flat_buffer.data(), slot_size );

        cur_n_ptrs = ::NS(CObjFlatBuffer_num_pointers)(
            flat_buffer.data(), slot_size );

        ASSERT_TRUE( cur_n_slots == prev_n_slots +
            ( NS(CObjTestNoPtrs_cobj_reserved_handle_size)(
                slot_size ) / slot_size ) );
        ASSERT_TRUE( cur_n_objects == prev_n_objects + 1u );
        ASSERT_TRUE( cur_n_ptrs == prev_n_ptrs );

        prev_n_slots   = cur_n_slots;
        prev_n_objects = cur_n_objects;
        prev_n_ptrs    = cur_n_ptrs;

        ASSERT_TRUE( 0 == ::NS(CObjTestNoPtrs_compare)(
            new_no_ptrs_elem, &cmp_no_ptrs[ ii ] ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        new_dataptrs_elem = nullptr;
        new_dataptrs_elem = NS(CObjTestDataptrs_cobj_flat_buffer_add_copy)(
            flat_buffer.data(), slot_size, &cmp_dataptrs[ ii ] );

        ASSERT_TRUE( new_dataptrs_elem != nullptr );
        ASSERT_TRUE( new_dataptrs_elem != &cmp_dataptrs[ ii ] );
        ASSERT_TRUE( ::NS(CObjTestDataptrs_b_capacity)( new_dataptrs_elem ) ==
                     ::NS(CObjTestDataptrs_b_capacity)( &cmp_dataptrs[ ii ] ) );
        ASSERT_TRUE( ::NS(CObjTestDataptrs_c_capacity)( new_dataptrs_elem ) ==
                     ::NS(CObjTestDataptrs_c_capacity)( &cmp_dataptrs[ ii ] ) );

        cur_n_slots = ::NS(CObjFlatBuffer_num_slots)(
            flat_buffer.data(), slot_size );

        cur_n_objects = ::NS(CObjFlatBuffer_num_objects)(
            flat_buffer.data(), slot_size );

        cur_n_ptrs = ::NS(CObjFlatBuffer_num_pointers)(
            flat_buffer.data(), slot_size );

        ASSERT_TRUE( cur_n_slots > prev_n_slots + (
            NS(CObjTestDataptrs_cobj_reserved_handle_size)(
                slot_size ) / slot_size ) );
        ASSERT_TRUE( cur_n_objects == prev_n_objects + 1u );
        ASSERT_TRUE( cur_n_ptrs ==
            prev_n_ptrs + NS(CObjTestDataptrs_cobj_num_dataptrs)() );

        prev_n_slots   = cur_n_slots;
        prev_n_objects = cur_n_objects;
        prev_n_ptrs    = cur_n_ptrs;

        ASSERT_TRUE( 0 == ::NS(CObjTestDataptrs_compare)(
            new_dataptrs_elem, &cmp_dataptrs[ ii ] ) );
    }

    ASSERT_TRUE( ::NS(CObjFlatBuffer_num_objects)( flat_buffer.data(),
        slot_size ) == 4 * ( cmp_no_ptrs.size() + cmp_dataptrs.size() ) );

    for( uint_type ii = 0u ; ii < NUM_CMP_ELEMS ; ++ii )
    {
        uint_type jj = 8u * ii;
        uint_type kk = jj + 1;

        ASSERT_TRUE( ::NS(CObjTestNoPtrs_compare)( &cmp_no_ptrs[ ii ],
            ::NS(CObjTestNoPtrs_const_from_cobj_flat_buffer)(
                flat_buffer.data(), jj, slot_size ) ) == 0 );

        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)( &cmp_dataptrs[ ii ],
            ::NS(CObjTestDataptrs_const_from_cobj_flat_buffer)(
                flat_buffer.data(), kk, slot_size ) ) == 0 );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        jj += 2;
        kk += 2;

        ASSERT_TRUE( ::NS(CObjTestNoPtrs_compare)( &cmp_no_ptrs[ ii ],
            ::NS(CObjTestNoPtrs_const_from_cobj_flat_buffer)(
                flat_buffer.data(), jj, slot_size ) ) == 0 );

        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)( &cmp_dataptrs[ ii ],
            ::NS(CObjTestDataptrs_const_from_cobj_flat_buffer)(
                flat_buffer.data(), kk, slot_size ) ) == 0 );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        jj += 2;
        kk += 2;

        ASSERT_TRUE( ::NS(CObjTestNoPtrs_compare)( &cmp_no_ptrs[ ii ],
            ::NS(CObjTestNoPtrs_const_from_cobj_flat_buffer)(
                flat_buffer.data(), jj, slot_size ) ) == 0 );

        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)( &cmp_dataptrs[ ii ],
            ::NS(CObjTestDataptrs_const_from_cobj_flat_buffer)(
                flat_buffer.data(), kk, slot_size ) ) == 0 );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        jj += 2;
        kk += 2;

        ASSERT_TRUE( ::NS(CObjTestNoPtrs_compare)( &cmp_no_ptrs[ ii ],
            ::NS(CObjTestNoPtrs_const_from_cobj_flat_buffer)(
                flat_buffer.data(), jj, slot_size ) ) == 0 );

        ASSERT_TRUE( ::NS(CObjTestDataptrs_compare)( &cmp_dataptrs[ ii ],
            ::NS(CObjTestDataptrs_const_from_cobj_flat_buffer)(
                flat_buffer.data(), kk, slot_size ) ) == 0 );
    }
}

