#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <random>
#include <functional>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/testlib.h"
#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"

template< typename TypeT >
class CXXCommonCObjectsCBufferCreateNew : public ::testing::Test
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

TYPED_TEST_SUITE( CXXCommonCObjectsCBufferCreateNew,
                  SIXTRL_CXX_NAMESPACE::tests::TypesToTest );


TYPED_TEST( CXXCommonCObjectsCBufferCreateNew, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using obj_t         = TypeParam;
    using c99_obj_t     = typename st::ObjDataCApiTypeTraits< obj_t >::c_api_t;
    using initialiser_t = typename st::tests::CObjElemInitialiserTraits<
                            obj_t >::initialiser_t;

    using st_size_t     = st::cobj_size_t;
    using st_status_t   = st::cobj_status_t;
    using buffer_t      = st::CBuffer;

    ASSERT_TRUE( st::ObjData_is_c_api_type< c99_obj_t >() );

    ASSERT_TRUE( st::CObjElem_type_id< c99_obj_t >() !=
                 st::COBJECTS_ILLEGAL_TYPE_ID );

    ASSERT_TRUE( st::CObjElem_type_id< c99_obj_t >() ==
                 st::CObjElem_type_id< obj_t >() );

    buffer_t buffer;

    /* --------------------------------------------------------------------- */

    st_status_t status = st::COBJECTS_STATUS_SUCCESS;

    ASSERT_TRUE( buffer.p_base() != nullptr );
    ASSERT_TRUE( buffer.size() < buffer.capacity() );
    ASSERT_TRUE( buffer.size() >= st::CBUFFER_MIN_SIZE );

    ASSERT_TRUE( buffer.n_slots()      == st_size_t{ 0 } );
    ASSERT_TRUE( buffer.n_objects()    == st_size_t{ 0 } );
    ASSERT_TRUE( buffer.n_pointers()   == st_size_t{ 0 } );
    ASSERT_TRUE( buffer.n_garbage()    == st_size_t{ 0 } );

    ASSERT_TRUE( buffer.max_slots()    == st_size_t{ 0 } );
    ASSERT_TRUE( buffer.max_objects()  == st_size_t{ 0 } );
    ASSERT_TRUE( buffer.max_pointers() == st_size_t{ 0 } );
    ASSERT_TRUE( buffer.max_garbage()  == st_size_t{ 0 } );

    /* --------------------------------------------------------------------- */

    const static st_size_t NUM_OBJS = st_size_t{ 10 } * st_size_t{ 3 };
    initialiser_t obj_init;

    std::vector< st_size_t > requ_num_slots( NUM_OBJS, st_size_t{ 0 } );
    std::vector< st_size_t > requ_num_objs(  NUM_OBJS, st_size_t{ 0 } );
    std::vector< st_size_t > requ_num_ptrs(  NUM_OBJS, st_size_t{ 0 } );

    std::vector< obj_t > cmp_objs( NUM_OBJS, obj_t{} );
    for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_OBJS ; ++ii )
    {
        obj_t* obj = &cmp_objs[ ii ];
        status = st::CObjStatus_from_status( obj_init.randomise( obj ) );

        requ_num_objs[ ii ] = st::CObjElem_required_num_objects( obj );
        ASSERT_TRUE( requ_num_objs[ ii ] > st_size_t{ 0 } );

        requ_num_slots[ ii ] = st::CObjElem_required_num_slots(
            buffer.slot_size(), obj );
        ASSERT_TRUE( requ_num_slots[ ii ] > st_size_t{ 0 } );

        requ_num_ptrs[ ii ] = st::CObjElem_num_ptrs< obj_t >();
        ASSERT_TRUE( status == st::COBJECTS_STATUS_SUCCESS );
    }

    ASSERT_TRUE( std::accumulate( requ_num_objs.begin(), requ_num_objs.end(),
                    st_size_t{ 0 } ) >= NUM_OBJS );

    ASSERT_TRUE( std::accumulate( requ_num_ptrs.begin(), requ_num_ptrs.end(),
                    st_size_t{ 0 } ) >= st_size_t{ 0 } );

    ASSERT_TRUE( std::accumulate( requ_num_slots.begin(), requ_num_slots.end(),
                    st_size_t{ 0 } ) > st_size_t{ 0 } );



    /* attempt to add a copy of the first obj -> should fail, view has not
     * enough slots and objects allocated! */

    for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_OBJS ; ++ii )
    {
        st_size_t const jj = ii % st_size_t{ 3 };
        obj_t const* orig = &cmp_objs[ ii ];

        SIXTRL_BUFFER_DATAPTR_DEC obj_t* added_elem = nullptr;

        switch( jj )
        {
            case 0:
            {
                added_elem = obj_init.create_new( buffer, orig );
                break;
            }

            case 1:
            {
                added_elem = obj_init.add_new( buffer, orig );
                break;
            }

            case 2:
            {
                added_elem = buffer.add_copy< obj_t >( orig );
                break;
            }

            default:
            {
                added_elem = nullptr;
            }
        };

        ASSERT_TRUE( added_elem != nullptr );
        ASSERT_TRUE( orig != added_elem );

        SIXTRL_ASSERT( ii < requ_num_objs.size()  );
        SIXTRL_ASSERT( ii < requ_num_slots.size() );
        SIXTRL_ASSERT( ii < requ_num_ptrs.size()  );

        ASSERT_TRUE( requ_num_objs[ ii ] ==
            st::CObjElem_required_num_objects( added_elem ) );

        ASSERT_TRUE( requ_num_slots[ ii ] ==
            st::CObjElem_required_num_slots( buffer.slot_size(), added_elem ) );

        ASSERT_TRUE( requ_num_ptrs[ ii ] ==
            st::CObjElem_num_ptrs( added_elem ) );

        st_size_t const expected_num_objs = std::accumulate(
            &requ_num_objs[ 0 ], &requ_num_objs[ ii ],
             requ_num_objs[ ii ] );

        st_size_t const expected_num_slots = std::accumulate(
            &requ_num_slots[ 0 ], &requ_num_slots[ ii ],
             requ_num_slots[ ii ] );

        st_size_t const expected_num_ptrs = std::accumulate(
            &requ_num_ptrs[ 0 ], &requ_num_ptrs[ ii ],
             requ_num_ptrs[ ii ] );


        ASSERT_TRUE( buffer.n_objects()  == expected_num_objs  );
        ASSERT_TRUE( buffer.n_slots()    == expected_num_slots );
        ASSERT_TRUE( buffer.n_pointers() == expected_num_ptrs  );

        auto cmp_result = st::ObjDataComparisonHelper<
            obj_t, obj_t >::compare( added_elem, orig );

        ASSERT_TRUE( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS );
    }
}
