#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/opencl/internal/helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus )
    #include "sixtracklib/opencl/opencl.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES )  && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <sstream>
    #include <vector>
#endif /* !defined( SIXTRL_NO_INCLUDES )  && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
    }

    st::size_type OpenCL_num_all_nodes()
    {
        return st::size_type{ 0 };
    }

    st::size_type OpenCL_num_available_nodes(
        std::string const& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( filter_str ),
        std::string const& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( env_variable_name ) )
    {
        return st::size_type{ 0 };
    }
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
