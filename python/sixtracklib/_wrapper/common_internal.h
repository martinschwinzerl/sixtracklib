#ifndef SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_INTERNAL_H__
#define SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_INTERNAL_H__

#include "sixtracklib/common/definitions.h"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    struct InitHelper;

    SIXTRL_HOST_FN void InitHelper_common_internal( InitHelper& root );

    SIXTRL_HOST_FN void InitHelper_common_internal_math_factorial( InitHelper& root );

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */

#endif /* SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_INTERNAL_H__ */
