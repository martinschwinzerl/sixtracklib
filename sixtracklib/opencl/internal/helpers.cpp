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
                case CL_DEVICE_NOT_FOUND: {
                    output_str << "CL_DEVICE_NOT_FOUND"; break; }

                case CL_DEVICE_NOT_AVAILABLE: {
                    output_str << "CL_DEVICE_NOT_AVAILABLE"; break; }

                case CL_COMPILER_NOT_AVAILABLE: {
                    output_str << "CL_COMPILER_NOT_AVAILABLE"; break; }

                case CL_MEM_OBJECT_ALLOCATION_FAILURE: {
                    output_str << "CL_MEM_OBJECT_ALLOCATION_FAILURE"; break; }

                case CL_OUT_OF_RESOURCES: {
                    output_str << "CL_OUT_OF_RESOURCES"; break; }

                case CL_OUT_OF_HOST_MEMORY: {
                    output_str << "CL_OUT_OF_HOST_MEMORY"; break; }

                case CL_PROFILING_INFO_NOT_AVAILABLE: {
                    output_str << "CL_PROFILING_INFO_NOT_AVAILABLE"; break; }

                case CL_MEM_COPY_OVERLAP: {
                    output_str << "CL_MEM_COPY_OVERLAP"; break; }

                case CL_IMAGE_FORMAT_MISMATCH: {
                    output_str << "CL_IMAGE_FORMAT_MISMATCH"; break; }

                case CL_IMAGE_FORMAT_NOT_SUPPORTED: {
                    output_str << "CL_IMAGE_FORMAT_NOT_SUPPORTED"; break; }

                case CL_BUILD_PROGRAM_FAILURE: {
                    output_str << "CL_BUILD_PROGRAM_FAILURE"; break; }

                case CL_MAP_FAILURE: { output_str << "CL_MAP_FAILURE"; break; }

                #ifdef CL_VERSION_1_1

                case CL_MISALIGNED_SUB_BUFFER_OFFSET: {
                    output_str << "CL_MISALIGNED_SUB_BUFFER_OFFSET"; break; }

                case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST: {
                    output_str << "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
                    break; }

                #endif

                #ifdef CL_VERSION_1_2
                case CL_COMPILE_PROGRAM_FAILURE: {
                    output_str << "CL_COMPILE_PROGRAM_FAILURE"; break; }

                case CL_LINKER_NOT_AVAILABLE: {
                    output_str << "CL_LINKER_NOT_AVAILABLE"; break; }

                case CL_LINK_PROGRAM_FAILURE: {
                    output_str << "CL_LINK_PROGRAM_FAILURE"; break; }

                case CL_DEVICE_PARTITION_FAILED: {
                    output_str << "CL_DEVICE_PARTITION_FAILED"; break; }

                case CL_KERNEL_ARG_INFO_NOT_AVAILABLE: {
                    output_str << "CL_KERNEL_ARG_INFO_NOT_AVAILABLE"; break; }

                #endif

                case CL_INVALID_VALUE: {
                    output_str << "CL_INVALID_VALUE"; break; }

                case CL_INVALID_DEVICE_TYPE: {
                    output_str << "CL_INVALID_DEVICE_TYPE"; break; }

                case CL_INVALID_PLATFORM: {
                    output_str << "CL_INVALID_PLATFORM"; break; }

                case CL_INVALID_DEVICE: {
                    output_str << "CL_INVALID_DEVICE"; break; }

                case CL_INVALID_CONTEXT: {
                    output_str << "CL_INVALID_CONTEXT"; break; }

                case CL_INVALID_QUEUE_PROPERTIES: {
                    output_str << "CL_INVALID_QUEUE_PROPERTIES"; break; }

                case CL_INVALID_COMMAND_QUEUE: {
                    output_str << "CL_INVALID_COMMAND_QUEUE"; break; }

                case CL_INVALID_HOST_PTR: {
                    output_str << "CL_INVALID_HOST_PTR"; break; }

                case CL_INVALID_MEM_OBJECT: {
                    output_str << "CL_INVALID_MEM_OBJECT"; break; }

                case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR: {
                    output_str << "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR"; break; }

                case CL_INVALID_IMAGE_SIZE: {
                    output_str << "CL_INVALID_IMAGE_SIZE"; break; }

                case CL_INVALID_SAMPLER: {
                    output_str << "CL_INVALID_SAMPLER"; break; }

                case CL_INVALID_BINARY: {
                    output_str << "CL_INVALID_BINARY"; break; }

                case CL_INVALID_BUILD_OPTIONS: {
                    output_str << "CL_INVALID_BUILD_OPTIONS"; break; }

                case CL_INVALID_PROGRAM: {
                    output_str << "CL_INVALID_PROGRAM"; break; }

                case CL_INVALID_PROGRAM_EXECUTABLE: {
                    output_str << "CL_INVALID_PROGRAM_EXECUTABLE"; break; }

                case CL_INVALID_KERNEL_NAME: {
                    output_str << "CL_INVALID_KERNEL_NAME"; break; }

                case CL_INVALID_KERNEL_DEFINITION: {
                    output_str << "CL_INVALID_KERNEL_DEFINITION"; break; }

                case CL_INVALID_KERNEL: {
                    output_str << "CL_INVALID_KERNEL"; break; }

                case CL_INVALID_ARG_INDEX: {
                    output_str << "CL_INVALID_ARG_INDEX"; break; }

                case CL_INVALID_ARG_VALUE: {
                    output_str << "CL_INVALID_ARG_VALUE"; break; }

                case CL_INVALID_ARG_SIZE: {
                    output_str << "CL_INVALID_ARG_SIZE"; break; }

                case CL_INVALID_KERNEL_ARGS: {
                    output_str << "CL_INVALID_KERNEL_ARGS"; break; }

                case CL_INVALID_WORK_DIMENSION: {
                    output_str << "CL_INVALID_WORK_DIMENSION"; break; }

                case CL_INVALID_WORK_GROUP_SIZE: {
                    output_str << "CL_INVALID_WORK_GROUP_SIZE"; break; }

                case CL_INVALID_WORK_ITEM_SIZE: {
                    output_str << "CL_INVALID_WORK_ITEM_SIZE"; break; }

                case CL_INVALID_GLOBAL_OFFSET: {
                    output_str << "CL_INVALID_GLOBAL_OFFSET"; break; }

                case CL_INVALID_EVENT_WAIT_LIST: {
                    output_str << "CL_INVALID_EVENT_WAIT_LIST"; break; }

                case CL_INVALID_EVENT: {
                    output_str << "CL_INVALID_EVENT"; break; }

                case CL_INVALID_OPERATION: {
                    output_str << "CL_INVALID_OPERATION"; break; }

                case CL_INVALID_GL_OBJECT: {
                    output_str << "CL_INVALID_GL_OBJECT"; break; }

                case CL_INVALID_BUFFER_SIZE: {
                    output_str << "CL_INVALID_BUFFER_SIZE"; break; }

                case CL_INVALID_MIP_LEVEL: {
                    output_str << "CL_INVALID_MIP_LEVEL"; break; }

                case CL_INVALID_GLOBAL_WORK_SIZE: {
                    output_str << "CL_INVALID_GLOBAL_WORK_SIZE"; break; }

                #ifdef CL_VERSION_1_1
                case CL_INVALID_PROPERTY: {
                    output_str << "CL_INVALID_PROPERTY"; break; }
                #endif

                #ifdef CL_VERSION_1_2
                case CL_INVALID_IMAGE_DESCRIPTOR: {
                    output_str << "CL_INVALID_IMAGE_DESCRIPTOR"; break; }

                case CL_INVALID_COMPILER_OPTIONS: {
                    output_str << "CL_INVALID_COMPILER_OPTIONS"; break; }

                case CL_INVALID_LINKER_OPTIONS: {
                    output_str << "CL_INVALID_LINKER_OPTIONS"; break; }

                case CL_INVALID_DEVICE_PARTITION_COUNT: {
                    output_str << "CL_INVALID_DEVICE_PARTITION_COUNT"; break; }
                #endif

                #ifdef CL_VERSION_2_0
                case CL_INVALID_PIPE_SIZE: {
                    output_str << "CL_INVALID_PIPE_SIZE"; break; }

                case CL_INVALID_DEVICE_QUEUE: {
                    output_str << "CL_INVALID_DEVICE_QUEUE"; break; }
                #endif

                #ifdef CL_VERSION_2_2
                case CL_INVALID_SPEC_ID: {
                    output_str << "CL_INVALID_SPEC_ID"; break; }
                case CL_MAX_SIZE_RESTRICTION_EXCEEDED: {
                    output_str << "CL_MAX_SIZE_RESTRICTION_EXCEEDED"; break; }
                #endif

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
