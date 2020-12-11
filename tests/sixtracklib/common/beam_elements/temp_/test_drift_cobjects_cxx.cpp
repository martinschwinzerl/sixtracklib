#include "sixtracklib/common/beam_elements/drift.hpp"

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"

template< typename DriftT >
class CXXCommonBeDriftCObjects : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXDriftTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::Drift, SIXTRL_CXX_NAMESPACE::CDrift >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeDriftCObjects,
                  SIXTRL_CXX_NAMESPACE::tests::CXXDriftTypes );

TYPED_TEST( CXXCommonBeDriftCObjects, BasicUsage )
{
    namespace st = sixtrack;
    typedef TypeParam obj_t;
    typedef typename st::tests::CObjElemInitialiserTraits< obj_t >::initialiser_t
            obj_initialiser_t;

    typedef st::arch_size_t st_size_t;
    typedef st::CBufferView cbuffer_view_t;
    typedef cbuffer_view_t::address_t st_addr_t;
    typedef st::CBuffer cbuffer_t;
    typedef cbuffer_view_t::raw_t st_raw_data_t;

    static_assert( st::CObjElem_allow_direct_storage< obj_t >(),
                   "requires direct storage" );

    constexpr st_size_t NUM_OBJS = st_size_t{ 1000 };
    constexpr st_size_t SLOT_SIZE = cbuffer_view_t::DEFAULT_SLOT_SIZE;

    std::vector< st_size_t > requ_num_objs(  NUM_OBJS, st_size_t{ 0 } );
    std::vector< st_size_t > requ_num_slots( NUM_OBJS, st_size_t{ 0 } );
    std::vector< st_size_t > requ_num_ptrs(  NUM_OBJS, st_size_t{ 0 } );

    obj_initialiser_t obj_init;
    std::vector< obj_t > cmp_obj( NUM_OBJS, obj_t{} );

    for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_OBJS ; ++ii )
    {
        obj_t* obj = std::addressof( cmp_obj[ ii ] );
        SIXTRL_ASSERT( obj != nullptr );

        ASSERT_TRUE( obj_init.randomise( obj ) == st::ARCH_STATUS_SUCCESS );

        requ_num_objs[ ii ] = st::CObjElem_required_num_objects( obj );
        ASSERT_TRUE( requ_num_objs[ ii ] > st_size_t{ 0 } );

        requ_num_slots[ ii ] = st::CObjElem_required_num_slots( SLOT_SIZE, obj );
        ASSERT_TRUE( requ_num_slots[ ii ] > st_size_t{ 0 } );

        requ_num_ptrs[ ii ] = st::CObjElem_num_ptrs< obj_t >();
    }

    st_size_t const max_num_objs = std::accumulate(
        requ_num_objs.begin(), requ_num_objs.end(), st_size_t{ 0 } );

    st_size_t const max_num_slots = std::accumulate(
        requ_num_slots.begin(), requ_num_slots.end(), st_size_t{ 0 } );

    st_size_t const max_num_ptrs = std::accumulate(
        requ_num_ptrs.begin(), requ_num_ptrs.end(), st_size_t{ 0 } );

    st_size_t const requ_buffer_size = cbuffer_view_t::required_buffer_length(
        max_num_slots, max_num_objs, max_num_ptrs, st_size_t{ 0 }, SLOT_SIZE );

    SIXTRL_ASSERT( max_num_objs  >= NUM_OBJS );
    SIXTRL_ASSERT( max_num_slots > st_size_t{ 0 } );
    SIXTRL_ASSERT( requ_buffer_size > st_size_t{ 0 } );

    std::vector< st_raw_data_t > view_raw_buffer( requ_buffer_size + SLOT_SIZE );
    st_size_t view_capacity = st_size_t{ 0 };
    st_addr_t const view_begin_addr = cbuffer_view_t::aligned_base_addr(
        reinterpret_cast< std::uintptr_t >( view_raw_buffer.data() ),
        view_raw_buffer.size(), st::Type_storage_align< obj_t >(),
            &view_capacity, SLOT_SIZE );

    SIXTRL_ASSERT( view_begin_addr != cbuffer_view_t::NULL_ADDRESS );
    SIXTRL_ASSERT( view_capacity >= requ_buffer_size );

    cbuffer_view_t view( view_begin_addr, SLOT_SIZE, view_capacity );

    SIXTRL_ASSERT( view.capacity() >= requ_buffer_size );
    SIXTRL_ASSERT( view.can_allocate(
        max_num_slots, max_num_objs, max_num_ptrs, st_size_t{ 0 } ) );

    ASSERT_TRUE( st::COBJECTS_STATUS_SUCCESS == view.allocate(
        max_num_slots, max_num_objs, max_num_ptrs, st_size_t{ 0 } ) );

    SIXTRL_ASSERT( view.max_slots()    >= max_num_slots );
    SIXTRL_ASSERT( view.max_objects()  >= max_num_objs );
    SIXTRL_ASSERT( view.max_pointers() >= max_num_ptrs );

    cbuffer_t buffer;

    for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_OBJS ; ++ii )
    {
        st_size_t const jj = ii % st_size_t{ 3 };
        obj_t const* orig = std::addressof( cmp_obj[ ii ] );
        SIXTRL_ASSERT( orig != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( ii < requ_num_objs.size()  );
        SIXTRL_ASSERT( ii < requ_num_slots.size() );
        SIXTRL_ASSERT( ii < requ_num_ptrs.size()  );

        obj_t* added_elem_v = nullptr;
        obj_t* added_elem_b = nullptr;

        switch( jj )
        {
            case 0:
            {
                added_elem_v = obj_init.create_new( view, orig );
                added_elem_b = obj_init.create_new( buffer, orig );
                break;
            }

            case 1:
            {
                added_elem_v = obj_init.add_new( view, orig );
                added_elem_b = obj_init.add_new( buffer, orig );
                break;
            }

            case 2:
            {
                added_elem_v = st::CBufferView_add_copy_of_object_detail(
                    view, orig, nullptr, nullptr, nullptr, nullptr );

                added_elem_b = buffer.add_copy( orig );
                break;
            }

            default:
            {
                added_elem_v = nullptr;
                added_elem_b = nullptr;
            }
        };

        ASSERT_TRUE( added_elem_v != nullptr );
        ASSERT_TRUE( added_elem_v != orig    );

        ASSERT_TRUE( added_elem_b != nullptr );
        ASSERT_TRUE( added_elem_b != orig    );

        ASSERT_TRUE( requ_num_objs[ ii ] ==
            st::CObjElem_required_num_objects( added_elem_v ) );

        ASSERT_TRUE( requ_num_slots[ ii ] ==
            st::CObjElem_required_num_slots( SLOT_SIZE, added_elem_v ) );

        ASSERT_TRUE( requ_num_ptrs[ ii ] ==
            st::CObjElem_num_ptrs( added_elem_v ) );

        ASSERT_TRUE( requ_num_objs[ ii ] ==
            st::CObjElem_required_num_objects( added_elem_b ) );

        ASSERT_TRUE( requ_num_slots[ ii ] ==
            st::CObjElem_required_num_slots( SLOT_SIZE, added_elem_b ) );

        ASSERT_TRUE( requ_num_ptrs[ ii ] ==
            st::CObjElem_num_ptrs( added_elem_b ) );

        auto cmp_result = st::ObjDataComparisonHelper<
            obj_t, obj_t >::compare( added_elem_v, orig );

        ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );

        obj_init.randomise_values( added_elem_v );

        cmp_result = st::ObjDataComparisonHelper<
            obj_t, obj_t >::compare( added_elem_v, orig );

        ASSERT_TRUE( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );

        ASSERT_TRUE( st::COBJECTS_STATUS_SUCCESS ==
            buffer.store_object< obj_t >( ii, added_elem_v ) );

        cmp_result = st::ObjDataComparisonHelper<
            obj_t, obj_t >::compare( added_elem_v, added_elem_b );

        ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );

        ASSERT_TRUE( st::COBJECTS_STATUS_SUCCESS ==
            view.store_object< obj_t >( ii, orig ) );

        cmp_result = st::ObjDataComparisonHelper<
            obj_t, obj_t >::compare( added_elem_v, orig );

        ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );

        ASSERT_TRUE( st::COBJECTS_STATUS_SUCCESS ==
            view.load_object< obj_t >( ii, added_elem_b ) );

        cmp_result = st::ObjDataComparisonHelper<
            obj_t, obj_t >::compare( added_elem_b, orig );

        ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );

        cmp_result = st::ObjDataComparisonHelper<
            obj_t, obj_t >::compare( added_elem_b, added_elem_v );

        ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );
    }

    for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_OBJS ; ++ii )
    {
        obj_t const* orig = std::addressof( cmp_obj[ ii ] );
        obj_t const* added_elem_v = view.get_object< obj_t >( ii );
        obj_t const* added_elem_b = buffer.get_object< obj_t >( ii );

        ASSERT_TRUE( added_elem_v != nullptr );
        ASSERT_TRUE( added_elem_b != nullptr );
        ASSERT_TRUE( added_elem_v != added_elem_b );
        ASSERT_TRUE( added_elem_v != orig );
        ASSERT_TRUE( added_elem_b != orig );

        auto cmp_result = st::ObjDataComparisonHelper<
            obj_t, obj_t >::compare( added_elem_v, orig );

        ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );

        cmp_result = st::ObjDataComparisonHelper<
            obj_t, obj_t >::compare( added_elem_b, orig );

        ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );

        cmp_result = st::ObjDataComparisonHelper<
            obj_t, obj_t >::compare( added_elem_v, added_elem_b );

        ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );
    }
}
