#include <cstddef>
#include <cstdlib>
#include <functional>
#include <type_traits>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/common/cobjects/flat_buffer.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"

template< typename TypeT >
class CXXCommonCObjectsCBufferView : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using TypesToTest = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs,
        SIXTRL_CXX_NAMESPACE::tests::CTypeConstNumPtrs,
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs,
        SIXTRL_CXX_NAMESPACE::tests::CTypeNoPtrs >;

} /* namepsace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonCObjectsCBufferView,
                  SIXTRL_CXX_NAMESPACE::tests::TypesToTest );


TYPED_TEST( CXXCommonCObjectsCBufferView, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using obj_t         = TypeParam;
    using c99_obj_t     = typename st::ObjDataCApiTypeTraits< obj_t >::c_api_t;
    using initialiser_t = typename st::tests::CObjElemInitialiserTraits<
                            obj_t >::initialiser_t;

    using st_size_t     = st::cobj_size_t;
    using st_status_t   = st::cobj_status_t;
    using st_addr_t     = st::cobj_address_t;
    using view_t        = st::CBufferView;

    ASSERT_TRUE( st::ObjData_is_c_api_type< c99_obj_t >() );

    ASSERT_TRUE( st::CObjElem_type_id< c99_obj_t >() !=
                 st::COBJECTS_ILLEGAL_TYPE_ID );

    ASSERT_TRUE( st::CObjElem_type_id< c99_obj_t >() ==
                 st::CObjElem_type_id< obj_t >() );

    constexpr st_size_t RAW_BUFFER_SIZE = st_size_t{ 1u << 21u };
    constexpr st_size_t SLOT_SIZE = st::CBUFFER_DEFAULT_SLOT_SIZE;
    std::vector< st::cobj_raw_t > ext_buffer( RAW_BUFFER_SIZE + SLOT_SIZE );

    /* --------------------------------------------------------------------- */

    st_size_t ext_buffer_capacity = st_size_t{ 0 };
    st_addr_t const ext_buffer_addr = view_t::aligned_base_addr(
        reinterpret_cast< std::uintptr_t >( ext_buffer.data() ),
        ext_buffer.size(), SLOT_SIZE, &ext_buffer_capacity, SLOT_SIZE );

    SIXTRL_ASSERT( ext_buffer_addr != st::COBJECTS_NULL_ADDRESS );
    SIXTRL_ASSERT( ext_buffer_capacity > st_size_t{ 0 } );

    view_t view( ext_buffer_addr, SLOT_SIZE, ext_buffer_capacity );

    ASSERT_TRUE(  view.base_address() == ext_buffer_addr );
    ASSERT_TRUE(  view.slot_size() == SLOT_SIZE );
    ASSERT_TRUE(  view.p_base() != nullptr );

    st_status_t status = view.allocate();

    ASSERT_TRUE( status == st::COBJECTS_STATUS_SUCCESS );
    ASSERT_TRUE( view.size() < view.capacity() );
    ASSERT_TRUE( view.size() >= st::CBUFFER_MIN_SIZE );

    ASSERT_TRUE( view.n_slots()      == st_size_t{ 0 } );
    ASSERT_TRUE( view.n_objects()    == st_size_t{ 0 } );
    ASSERT_TRUE( view.n_pointers()   == st_size_t{ 0 } );
    ASSERT_TRUE( view.n_garbage()    == st_size_t{ 0 } );

    ASSERT_TRUE( view.max_slots()    == st_size_t{ 0 } );
    ASSERT_TRUE( view.max_objects()  == st_size_t{ 0 } );
    ASSERT_TRUE( view.max_pointers() == st_size_t{ 0 } );
    ASSERT_TRUE( view.max_garbage()  == st_size_t{ 0 } );

    /* --------------------------------------------------------------------- */

    const static st_size_t NUM_OBJS = st_size_t{ 10 } * st_size_t{ 3 };
    SIXTRL_ASSERT( NUM_OBJS % st_size_t{ 3 } == st_size_t{ 0 } );

    std::vector< obj_t > cmp_objs( NUM_OBJS, obj_t{} );
    std::vector< st_size_t > requ_num_slots;
    std::vector< st_size_t > requ_num_ptrs;
    std::vector< st_size_t > requ_num_objs;

    initialiser_t obj_init;

    for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_OBJS ; ++ii )
    {
        obj_t* obj = &cmp_objs[ ii ];
        st::arch_status_t status = obj_init.randomise( obj );
        if( status != st::ARCH_STATUS_SUCCESS ) break;

        requ_num_objs.push_back(  st::CObjElem_required_num_objects( obj ) );
        ASSERT_TRUE( requ_num_objs.back() > st_size_t{ 0 } );

        requ_num_slots.push_back( st::CObjElem_required_num_slots(
            SLOT_SIZE, obj ) );
        ASSERT_TRUE( requ_num_slots.back() > st_size_t{ 0 } );

        requ_num_ptrs.push_back( st::CObjElem_num_ptrs< obj_t >() );
    }

    SIXTRL_ASSERT( cmp_objs.size()       == NUM_OBJS );
    SIXTRL_ASSERT( requ_num_objs.size()  == NUM_OBJS );
    SIXTRL_ASSERT( requ_num_ptrs.size()  == NUM_OBJS );
    SIXTRL_ASSERT( requ_num_slots.size() == NUM_OBJS );

    /* attempt to add a copy of the first obj -> should fail, view has not
     * enough slots and objects allocated! */

    st_size_t requ_buffer_size    = st_size_t{ 0 };
    st_size_t requ_num_objs_test  = st_size_t{ 0 };
    st_size_t requ_num_slots_test = st_size_t{ 0 };
    st_size_t requ_num_ptrs_test  = st_size_t{ 0 };

    st_size_t predicted_num_objs  = std::accumulate(
        &requ_num_objs[ 0 ], &requ_num_objs[ 1 ], st_size_t{ 0 } );

    st_size_t predicted_num_slots = std::accumulate(
        &requ_num_slots[ 0 ], &requ_num_slots[ 1 ], st_size_t{ 0 } );

    st_size_t predicted_num_ptrs = std::accumulate(
        &requ_num_ptrs[ 0 ], &requ_num_ptrs[ 1 ], st_size_t{ 0 } );

    ASSERT_FALSE( view.can_add_copy_of_object< obj_t >(
        &cmp_objs[ 0 ], &requ_buffer_size, &requ_num_slots_test,
            &requ_num_objs_test, &requ_num_ptrs_test ) );

    ASSERT_TRUE( requ_buffer_size    >  st_size_t{ 0 } );
    ASSERT_TRUE( requ_buffer_size    >  view.size() );
    ASSERT_TRUE( requ_buffer_size    <  view.capacity() );
    ASSERT_TRUE( requ_num_objs_test  >  st_size_t{ 0 } );
    ASSERT_TRUE( requ_num_objs_test  == predicted_num_objs );
    ASSERT_TRUE( requ_num_slots_test == predicted_num_slots );
    ASSERT_TRUE( requ_num_ptrs_test  == predicted_num_ptrs );

    /* reserve and attempt to add, should work now */

    ASSERT_TRUE( st::COBJECTS_STATUS_SUCCESS == view.reallocate(
        requ_num_slots[ 0 ], requ_num_objs[ 0 ], requ_num_ptrs[ 0 ] ) );

    ASSERT_TRUE( view.can_add_copy_of_object< obj_t >( &cmp_objs[ 0 ] ) );

    obj_t* added_obj = st::CBufferView_add_copy_of_object_detail(
        view, &cmp_objs[ 0 ], nullptr, nullptr, nullptr, nullptr );

    ASSERT_TRUE( added_obj != nullptr );
    ASSERT_TRUE( added_obj != &cmp_objs[ 0 ] );
    ASSERT_TRUE( view.n_objects()  == predicted_num_objs );
    ASSERT_TRUE( view.n_slots()    >= predicted_num_slots );
    ASSERT_TRUE( view.n_pointers() == predicted_num_ptrs );
    ASSERT_TRUE( view.n_garbage()  == st_size_t{ 0 } );

    /* verify that the stored obj and the original are bit-by-bit identical */

    auto cmp_result = st::ObjDataComparisonHelper< obj_t, obj_t >::compare(
        added_obj, &cmp_objs[ 0 ] );

    ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );

    obj_t* retrieved_obj = view.get_object< obj_t >( 0 );

    ASSERT_TRUE( retrieved_obj != nullptr );
    ASSERT_TRUE( retrieved_obj == added_obj );
    ASSERT_TRUE( retrieved_obj != &cmp_objs[ 1 ] );

    /* attempt to add another obj -> will faile,
     * because not enough slots / ptrs / objs */

    added_obj = nullptr;
    retrieved_obj = nullptr;

    ASSERT_FALSE( view.can_add_copy_of_object< obj_t >(
        &cmp_objs[ 1 ], &requ_buffer_size, &requ_num_slots_test,
            &requ_num_objs_test, &requ_num_ptrs_test ) );

    predicted_num_objs = std::accumulate(
        &requ_num_objs[ 0 ], &requ_num_objs[ 2 ], st_size_t{ 0 } );

    predicted_num_slots = std::accumulate(
        &requ_num_slots[ 0 ], &requ_num_slots[ 2 ], st_size_t{ 0 } );

    predicted_num_ptrs = std::accumulate(
        &requ_num_ptrs[ 0 ], &requ_num_ptrs[ 2 ], st_size_t{ 0 } );

    ASSERT_FALSE( view.can_add_copy_of_object< obj_t >(
        &cmp_objs[ 1 ], &requ_buffer_size, &requ_num_slots_test,
            &requ_num_objs_test, &requ_num_ptrs_test ) );

    ASSERT_TRUE( requ_buffer_size    >= view.size() );
    ASSERT_TRUE( requ_buffer_size    <  view.capacity() );
    ASSERT_TRUE( requ_num_objs_test  == predicted_num_objs );
    ASSERT_TRUE( requ_num_slots_test == predicted_num_slots );
    ASSERT_TRUE( requ_num_ptrs_test  == predicted_num_ptrs );

    /* reserve and attempt to add second object via the "create_new" method +
     * subsequent setting of field values, should work now */

    ASSERT_TRUE( st::COBJECTS_STATUS_SUCCESS == view.reallocate(
        requ_num_slots_test, requ_num_objs_test, requ_num_ptrs_test ) );

    ASSERT_TRUE( view.can_add_copy_of_object< obj_t >( &cmp_objs[ 1 ] ) );

    added_obj = obj_init.create_new( view, &cmp_objs[ 1 ] );
    ASSERT_TRUE( added_obj != nullptr );
    ASSERT_TRUE( added_obj != &cmp_objs[ 1 ] );

    cmp_result = st::ObjDataComparisonHelper< obj_t, obj_t >::compare(
        added_obj, &cmp_objs[ 1 ] );

    ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );

    retrieved_obj = view.get_object< obj_t >( 1 );
    ASSERT_TRUE( retrieved_obj != nullptr );
    ASSERT_TRUE( retrieved_obj == added_obj );
    ASSERT_TRUE( retrieved_obj != &cmp_objs[ 1 ] );
    ASSERT_TRUE( retrieved_obj != view.get_object< obj_t >( 0 ) );

    /* Add third object via the "add" method */

    added_obj = nullptr;
    retrieved_obj = nullptr;

    predicted_num_objs = std::accumulate(
        &requ_num_objs[ 0 ], &requ_num_objs[ 3 ], st_size_t{ 0 } );

    predicted_num_slots = std::accumulate(
        &requ_num_slots[ 0 ], &requ_num_slots[ 3 ], st_size_t{ 0 } );

    predicted_num_ptrs = std::accumulate(
        &requ_num_ptrs[ 0 ], &requ_num_ptrs[ 3 ], st_size_t{ 0 } );

    ASSERT_TRUE( st::COBJECTS_STATUS_SUCCESS == view.reallocate(
        predicted_num_slots, predicted_num_objs, predicted_num_ptrs ) );

    ASSERT_TRUE( view.can_add_copy_of_object< obj_t >( &cmp_objs[ 2 ] ) );

    added_obj = obj_init.add_new( view, &cmp_objs[ 2 ] );
    ASSERT_TRUE( added_obj != nullptr );
    ASSERT_TRUE( added_obj != &cmp_objs[ 2 ] );

    cmp_result = st::ObjDataComparisonHelper< obj_t, obj_t >::compare(
        added_obj, &cmp_objs[ 2 ] );

    ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );

    retrieved_obj = view.get_object< obj_t >( 2 );
    ASSERT_TRUE( retrieved_obj != nullptr );
    ASSERT_TRUE( retrieved_obj == added_obj );
    ASSERT_TRUE( retrieved_obj != &cmp_objs[ 2 ] );
    ASSERT_TRUE( retrieved_obj != view.get_object< obj_t >( 0 ) );
    ASSERT_TRUE( retrieved_obj != view.get_object< obj_t >( 1 ) );

    /* Allocate space for all remaining objects */

    ASSERT_TRUE( st::COBJECTS_STATUS_SUCCESS == view.reallocate(
        std::accumulate( requ_num_slots.begin(), requ_num_slots.end(),
                         st_size_t{ 0 } ),
        std::accumulate( requ_num_objs.begin(), requ_num_objs.end(),
                         st_size_t{ 0 } ),
        std::accumulate( requ_num_ptrs.begin(), requ_num_ptrs.end(),
                         st_size_t{ 0 } ) ) );

    ASSERT_TRUE( ( NUM_OBJS - view.n_objects() ) % 3u == 0u );

    for( st_size_t ii = view.n_objects() ; ii < NUM_OBJS ; ++ii )
    {
        ASSERT_TRUE( view.can_add_copy_of_object( &cmp_objs[ ii ] ) );

        st_size_t const method = ii % st_size_t{ 3 };
        added_obj = nullptr;
        retrieved_obj = nullptr;

        switch( method )
        {
            case 0:
            {
                added_obj = st::CBufferView_add_copy_of_object_detail( view,
                    &cmp_objs[ ii ], nullptr, nullptr, nullptr, nullptr );

                break;
            }

            case 1:
            {
                added_obj = obj_init.create_new( view, &cmp_objs[ ii ] );
                break;
            }

            case 2:
            {
                added_obj = obj_init.add_new( view, &cmp_objs[ ii ] );
                break;
            }

            default:
            {
                /* Should never go here */
                ASSERT_TRUE( added_obj != nullptr );
            }
        };

        ASSERT_TRUE( added_obj != nullptr );
        ASSERT_TRUE( added_obj != &cmp_objs[ ii ] );

        retrieved_obj = view.get_object< obj_t >( ii );
        ASSERT_TRUE( retrieved_obj != nullptr );
        ASSERT_TRUE( retrieved_obj != &cmp_objs[ ii ] );
        ASSERT_TRUE( retrieved_obj == added_obj );
    }

    /* Compare with cmp_objs and check for consistency */

    for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_OBJS ; ++ii )
    {
        cmp_result = st::ObjDataComparisonHelper< obj_t, obj_t >::compare(
            view.get_const_object< obj_t >( ii ), &cmp_objs[ ii ] );

        ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );
    }

    /* Create a vector of empty obj's to be loaded from the buffer view */

    std::vector< obj_t > copied_objs( NUM_OBJS, obj_t{} );

    for( st_size_t ii = st_size_t{ 0 } ;  ii < NUM_OBJS ; ++ii )
    {
        obj_t* cpy = &copied_objs[ ii ];

        if( st::ObjDataConverter< obj_t, obj_t, st::STORAGE_BE_DEFAULT,
                st::STORAGE_BE_COBJECTS >::requires_prepare(
                        cpy, view.get_object< obj_t >( ii ) ) )
        {
            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == obj_init.init_for_copy(
                cpy, view.get_object< obj_t >( ii ) ) );
        }

        ASSERT_TRUE( view.can_load_object_type< obj_t >( ii, cpy ) );
        ASSERT_TRUE( view.load_object< obj_t >(
                ii, cpy ) == st::ARCH_STATUS_SUCCESS );

        cmp_result = st::ObjDataComparisonHelper< obj_t, obj_t >::compare(
            view.get_const_object< obj_t >( ii ), cpy );

        ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );

        obj_init.randomise_values( view.get_object< obj_t >( ii ) );

        cmp_result = st::ObjDataComparisonHelper< obj_t, obj_t >::compare(
            view.get_const_object< obj_t >( ii ), cpy );

        ASSERT_TRUE( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );

        ASSERT_TRUE( view.can_store_object_type< obj_t >( ii, cpy ) );
        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == view.store_object<
                        obj_t >( ii, cpy ) );

        cmp_result = st::ObjDataComparisonHelper< obj_t, obj_t >::compare(
            view.get_const_object< obj_t >( ii ), cpy );

        ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );
    }
}
