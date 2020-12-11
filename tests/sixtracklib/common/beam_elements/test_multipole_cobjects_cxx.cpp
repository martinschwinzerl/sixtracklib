#include "sixtracklib/common/beam_elements/multipole.hpp"

#include <cstdint>
#include <limits>
#include <random>
#include <vector>

#include <gtest/gtest.h>

namespace SIXTRL_CXX_NAMESPACE
{
    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TMultipole< long double, int64_t >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Multipole delegate_t;
    };

    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TMultipole< float, int64_t >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Multipole delegate_t;
    };

    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TVectorMultipole< double, int64_t >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Multipole delegate_t;
    };

    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TVectorMultipole< float, int64_t >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Multipole delegate_t;
    };

    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TVectorMultipole< long double, int64_t >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Multipole delegate_t;
    };
}

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/testlib/common/cobjects/cobjects_elem_base_test_api.hpp"

template< class MultipoleSetT >
class CXXCommonBeMultipoleCObjects : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using LongDblMultipole =
        SIXTRL_CXX_NAMESPACE::TMultipole< long double, int64_t >;

    using SinglePrecMultipole =
        SIXTRL_CXX_NAMESPACE::TMultipole< float, int64_t >;

    using SingleVecMultipole =
        SIXTRL_CXX_NAMESPACE::TVectorMultipole< float, int64_t >;

    using DoubleVecMultipole =
        SIXTRL_CXX_NAMESPACE::TVectorMultipole< double, int64_t >;

    using LongDblVecMultipole =
        SIXTRL_CXX_NAMESPACE::TVectorMultipole< long double, int64_t >;

    using CXXMultipoleTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::Multipole,
        SIXTRL_CXX_NAMESPACE::CMultipole,
        LongDblMultipole,
        SinglePrecMultipole,
        DoubleVecMultipole,
        SingleVecMultipole,
        LongDblVecMultipole >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeMultipoleCObjects,
                  SIXTRL_CXX_NAMESPACE::tests::CXXMultipoleTypes );

TYPED_TEST( CXXCommonBeMultipoleCObjects, MultipoleSetUnitTest )
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
