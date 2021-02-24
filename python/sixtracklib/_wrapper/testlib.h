#ifndef SIXTRACKLIB_PYTHON_WRAPPER_TESTLIB_H__
#define SIXTRACKLIB_PYTHON_WRAPPER_TESTLIB_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE {
namespace python {

struct InitHelper;

SIXTRL_HOST_FN void InitHelper_testlib( InitHelper& root );


SIXTRL_HOST_FN void InitHelper_testlib_cobj_test_no_ptrs( InitHelper& root );
SIXTRL_HOST_FN void InitHelper_testlib_cobj_test_dataptrs( InitHelper& root );

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */

#endif /* SIXTRACKLIB_PYTHON_WRAPPER_TESTLIB_H__ */
