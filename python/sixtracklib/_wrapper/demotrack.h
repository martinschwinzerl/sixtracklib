#ifndef SIXTRACKLIB_PYTHON_WRAPPER_DEMOTRACK_H__
#define SIXTRACKLIB_PYTHON_WRAPPER_DEMOTRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/particles/demotrack.h"
    #include "sixtracklib/common/beam_elements/demotrack.h"

    #include "sixtracklib/testlib.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE {
namespace python {

struct InitHelper;

SIXTRL_HOST_FN void InitHelper_demotrack( InitHelper& root );

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */
#endif /* SIXTRACKLIB_PYTHON_WRAPPER_DEMOTRACK_H__ */
