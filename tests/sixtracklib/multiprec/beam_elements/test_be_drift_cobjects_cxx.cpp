#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/beam_elements/drift.hpp"

#include <gtest/gtest.h>

namespace SIXTRL_CXX_NAMESPACE
{
    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::DoublePrecDrift, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Drift delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecDrift, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Drift delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits< SIXTRL_CXX_NAMESPACE::QuadPrecDrift, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Drift delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits< SIXTRL_CXX_NAMESPACE::OctPrecDrift, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Drift delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits< SIXTRL_CXX_NAMESPACE::SinglePrecDrift, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Drift delegate_t;
    };
}

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/testlib/common/cobjects/cobjects_elem_base_test_api.hpp"

template< class DriftSetT >
class CXXMultiprecBeDriftCobjects : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXDriftTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::DoublePrecDrift,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecDrift,
        SIXTRL_CXX_NAMESPACE::QuadPrecDrift,
        SIXTRL_CXX_NAMESPACE::OctPrecDrift,
        SIXTRL_CXX_NAMESPACE::SinglePrecDrift >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecBeDriftCobjects,
                  SIXTRL_CXX_NAMESPACE::tests::CXXDriftTypes );

TYPED_TEST( CXXMultiprecBeDriftCobjects, DriftSetUnitTest )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    typedef TypeParam obj_t;

    if( st::CObjElem_allow_direct_storage< obj_t >() )
    {
        st::arch_status_t const status =
            st::tests::CObjElem_test_direct_storage_view_buffer< obj_t >(
                st::arch_size_t{ 100 } );
        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }
    else if( st::CObjElem_allow_delegate_storage< obj_t >() )
    {
        st::arch_status_t const status =
            st::tests::CObjElem_test_delegate_storage_view_buffer< obj_t >(
                st::arch_size_t{ 100 } );
        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }
    else
    {
        ASSERT_TRUE( st::CObjElem_allow_direct_storage< obj_t >() ||
                     st::CObjElem_allow_delegate_storage< obj_t >() );
    }
}
