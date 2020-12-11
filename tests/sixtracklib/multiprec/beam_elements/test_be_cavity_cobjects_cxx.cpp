#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/beam_elements/cavity.hpp"

#include <gtest/gtest.h>

namespace SIXTRL_CXX_NAMESPACE
{
    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::DoublePrecCavity, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Cavity delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecCavity, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Cavity delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::QuadPrecCavity, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Cavity delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::OctPrecCavity, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Cavity delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::SinglePrecCavity, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Cavity delegate_t;
    };
}

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/testlib/common/cobjects/cobjects_elem_base_test_api.hpp"

template< class CavitySetT >
class CXXMultiprecBeCavityCobjects : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXCavityTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::DoublePrecCavity,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecCavity,
        SIXTRL_CXX_NAMESPACE::QuadPrecCavity,
        SIXTRL_CXX_NAMESPACE::OctPrecCavity,
        SIXTRL_CXX_NAMESPACE::SinglePrecCavity >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecBeCavityCobjects,
                  SIXTRL_CXX_NAMESPACE::tests::CXXCavityTypes );

TYPED_TEST( CXXMultiprecBeCavityCobjects, CavitySetUnitTest )
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
