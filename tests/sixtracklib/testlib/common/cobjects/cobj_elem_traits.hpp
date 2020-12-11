#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_ELEM_TRAITS_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_ELEM_TRAITS_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    template< class E, typename Enabled = void >
    struct CObjElemInitialiserTraits
    {
        typedef void initialiser_t;
    };

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_ELEM_TRAITS_CXX_HPP__ */
