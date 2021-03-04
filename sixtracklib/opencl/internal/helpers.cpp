#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/opencl/internal/helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus )
    #include "sixtracklib/opencl/opencl.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES )  && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <sstream>
    #include <stdexcept>
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

    st::status_type OpenCL_ret_value_to_stream(
        std::ostream& SIXTRL_RESTRICT_REF output_str,
        ::cl_int const ret_value,
        std::string const& SIXTRL_RESTRICT_REF class_scope,
        std::string const& SIXTRL_RESTRICT_REF method_scope,
        std::string const& SIXTRL_RESTRICT_REF message,
        size_type const line_number )
    {
        st::status_type status = st::STATUS_GENERAL_FAILURE;

        if( !class_scope.empty() )
        {
            output_str << class_scope;

            if( !method_scope.empty() )
            {
                output_str << "::";
            }
        }

        if( !method_scope.empty() )
        {
            output_str << method_scope;

            if( line_number > st::size_type{ 0 } )
            {
                output_str << "(line=" << line_number << ")";
            }

            output_str << ": ";
        }

        if( ret_value != CL_SUCCESS )
        {
            status = st::STATUS_SUCCESS;

            switch( ret_value )
            {
                case CL_INVALID_CONTEXT: {
                    output_str << "CL_INVALID_CONTEXT";
                    break;
                }

                case CL_INVALID_VALUE: {
                    output_str << "CL_INVALID_VALUE";
                    break;
                }

                case CL_INVALID_BUFFER_SIZE: {
                    output_str << "CL_INVALID_BUFFER_SIZE";
                    break;
                }

                case CL_INVALID_HOST_PTR: {
                    output_str << "CL_INVALID_HOST_PTR";
                    break;
                }

                case CL_MEM_OBJECT_ALLOCATION_FAILURE: {
                    output_str << "CL_MEM_OBJECT_ALLOCATION_FAILURE";
                    break;
                }

                case CL_OUT_OF_RESOURCES: {
                    output_str << "CL_OUT_OF_RESOURCES";
                    break;
                }

                case CL_OUT_OF_HOST_MEMORY: {
                    output_str << "CL_OUT_OF_HOST_MEMORY";
                    break;
                }

                case CL_INVALID_PLATFORM: {
                    output_str << "CL_INVALID_PLATFORM";
                    break;
                }

                case CL_INVALID_DEVICE: {
                    output_str << "CL_INVALID_DEVICE";
                    break;
                }
                case CL_INVALID_PROGRAM_EXECUTABLE: {
                    output_str << "CL_INVALID_PROGRAM_EXECUTABLE";
                    break; }

                case CL_INVALID_KERNEL: {
                    output_str << "CL_INVALID_KERNEL";
                    break;
                }

                case CL_INVALID_KERNEL_NAME: {
                    output_str << "CL_INVALID_KERNEL_NAME";
                    break; }

                case CL_INVALID_KERNEL_DEFINITION: {
                    output_str << "CL_INVALID_KERNEL_DEFINITION";
                    break; }

                case CL_INVALID_ARG_INDEX: {
                    output_str << "CL_INVALID_ARG_INDEX";
                    break; }

                case CL_INVALID_ARG_SIZE: {
                    output_str << "CL_INVALID_ARG_SIZE";
                    break; }

                case CL_INVALID_ARG_VALUE: {
                    output_str << "CL_INVALID_ARG_VALUE";
                    break; }

                case CL_KERNEL_ARG_INFO_NOT_AVAILABLE: {
                    output_str << "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";
                    break; }

                case CL_INVALID_MEM_OBJECT: {
                    output_str << "CL_INVALID_MEM_OBJECT";
                    break; }

                case CL_INVALID_SAMPLER: {
                    output_str << "CL_INVALID_SAMPLER";
                    break; }

                default:
                {
                    output_str << ret_value << " (unknown)";
                }
            };
        }

        if( ( status == st::STATUS_SUCCESS ) && ( !message.empty() ) )
        {
            output_str << "\r\n" << "-> " << message;
        }

        return status;
    }
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
