#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/beam_elements/multipole.hpp"
#include "sixtracklib/common/internal/obj_delegate.hpp"

#include <gtest/gtest.h>

namespace SIXTRL_CXX_NAMESPACE
{
    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::DoublePrecMultipole, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Multipole delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecMultipole, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Multipole delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits< SIXTRL_CXX_NAMESPACE::QuadPrecMultipole, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Multipole delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits< SIXTRL_CXX_NAMESPACE::OctPrecMultipole, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Multipole delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits< SIXTRL_CXX_NAMESPACE::SinglePrecMultipole, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Multipole delegate_t;
    };
}

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/testlib/common/cobjects/cobjects_elem_base_test_api.hpp"

template< class MultipoleSetT >
class CXXMultiprecBeMultipoleCobjects : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXMultipoleTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::DoublePrecMultipole,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecMultipole,
        SIXTRL_CXX_NAMESPACE::QuadPrecMultipole,
        SIXTRL_CXX_NAMESPACE::OctPrecMultipole,
        SIXTRL_CXX_NAMESPACE::SinglePrecMultipole >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecBeMultipoleCobjects,
                  SIXTRL_CXX_NAMESPACE::tests::CXXMultipoleTypes );

TYPED_TEST( CXXMultiprecBeMultipoleCobjects, MultipoleSetUnitTest )
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
