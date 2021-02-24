#ifndef SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_COMMON_COBJECTS_H__
#define SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_COMMON_COBJECTS_H__

#include "sixtracklib/sixtracklib.h"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    struct InitHelper;

    SIXTRL_HOST_FN void InitHelper_common_cobjects( InitHelper& root );

    SIXTRL_HOST_FN void InitHelper_common_cobjects_cobj_index( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_cobjects_cobj_garbage_range( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_cobjects_cbuffer_view( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_cobjects_cbuffer( InitHelper& root );
}
}

#endif /* SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_COMMON_COBJECTS_H__ */
