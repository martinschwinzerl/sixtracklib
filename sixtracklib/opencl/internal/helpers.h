#ifndef SIXTRACKLIB_OPENCL_OPENCL_HELPERS_H__
#define SIXTRACKLIB_OPENCL_OPENCL_HELPERS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/opencl/control/node_info.h"
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus )
    #include "sixtracklib/opencl/opencl.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus )
    #include <vector>
    #include <sstream>
    #include <string>
#endif /* !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

// SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type) NS(OpenCL_num_all_nodes)( void );

// SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type) NS(OpenCL_num_available_nodes)(
//     char const* SIXTRL_RESTRICT filter_str,
//     char const* SIXTRL_RESTRICT env_variable_name );

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_CXX_NAMESPACE::size_type OpenCL_num_all_nodes();

    SIXTRL_CXX_NAMESPACE::size_type OpenCL_num_available_nodes(
        std::string const& SIXTRL_RESTRICT_REF filter_str = std::string{},
        std::string const& SIXTRL_RESTRICT_REF env_variable_name = std::string{}
    );

    status_type OpenCL_ret_value_to_stream(
        std::ostream& SIXTRL_RESTRICT_REF output_stream,
        ::cl_int const ret_value,
        std::string const& SIXTRL_RESTRICT_REF class_scope = std::string{},
        std::string const& SIXTRL_RESTRICT_REF method_scope = std::string{},
        std::string const& SIXTRL_RESTRICT_REF message = std::string{},
        size_type const line_number = size_type{ 0 } );


    template< class ExceptionT >
    void OpenCL_ret_value_to_exception( ::cl_int const ret_value,
        std::string const& SIXTRL_RESTRICT_REF class_scope = std::string{},
        std::string const& SIXTRL_RESTRICT_REF method_scope = std::string{},
        std::string const& SIXTRL_RESTRICT_REF message = std::string{},
        size_type const line_number = size_type{ 0 } )
    {
        std::ostringstream a2str;

        if( SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS !=
            SIXTRL_CXX_NAMESPACE::OpenCL_ret_value_to_stream(
                a2str, ret_value, class_scope, method_scope, message,
                    line_number ) )
        {
            a2str.str( "" );
            a2str << "Unknown exception for return value ret = " << ret_value;
        }

        throw ExceptionT( a2str.str() );
    }

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_OPENCL_OPENCL_HELPERS_H__ */
