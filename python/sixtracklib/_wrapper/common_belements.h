#ifndef SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_BELEMENTS_H__
#define SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_BELEMENTS_H__

#include "sixtracklib/common/definitions.h"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    struct InitHelper;

    SIXTRL_HOST_FN void InitHelper_common_belements( InitHelper& root );

    SIXTRL_HOST_FN void InitHelper_common_belements_sc_coasting( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_sc_qgauss( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_cavity( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_dipedge( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_drift( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_drift_exact( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_end_tracking( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_limit_rect( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_limit_ellipse( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_limit_rect_ellipse( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_monitor( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_multipole( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_rf_multipole( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_srotation( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_belements_xyshift( InitHelper& root );

    SIXTRL_HOST_FN void InitHelper_common_belements_demotrack( InitHelper& root );

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */

#endif /* SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_BELEMENTS_H__ */
