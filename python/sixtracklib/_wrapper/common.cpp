#include "python/sixtracklib/_wrapper/common.h"
#include "python/sixtracklib/_wrapper/common_belements.h"
#include "python/sixtracklib/_wrapper/common_cobjects.h"
#include "python/sixtracklib/_wrapper/common_internal.h"
#include "python/sixtracklib/_wrapper/common_particles.h"
#include "python/sixtracklib/_wrapper/init_helper.h"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace stpy = SIXTRL_CXX_NAMESPACE::python;
    }

    void InitHelper_common( stpy::InitHelper& root )
    {
        stpy::InitHelper_common_internal( root );
        stpy::InitHelper_common_cobjects( root );
        stpy::InitHelper_common_belements( root );
        stpy::InitHelper_common_particles( root );
    }

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */

