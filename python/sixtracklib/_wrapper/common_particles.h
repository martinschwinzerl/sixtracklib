#ifndef SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_PARTICLES_H__
#define SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_PARTICLES_H__

#include "sixtracklib/common/definitions.h"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    struct InitHelper;

    SIXTRL_HOST_FN void InitHelper_common_particles( InitHelper& root );

    SIXTRL_HOST_FN void InitHelper_common_particles_single_particle( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_particles_particles( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_common_particles_particles_addr( InitHelper& root );

    SIXTRL_HOST_FN void InitHelper_common_particles_demotrack( InitHelper& root );

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */

#endif /* SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_PARTICLES_H__ */
