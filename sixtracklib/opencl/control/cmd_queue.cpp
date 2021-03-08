#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/control/cmd_queue.h"
    #include "sixtracklib/opencl/control/context.h"
    #include "sixtracklib/opencl/internal/helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES )  */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <algorithm>
    #include <iostream>
    #include <iterator>
    #include <sstream>
#endif /* !defined( SIXTRL_NO_INCLUDES )  && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using queue_type   = st::OclCmdQueue;
        using st_status_t  = queue_type::status_type;
        using context_type = queue_type::context_type;
    }

    constexpr queue_type::class_id_type queue_type::BASE_CLASS_ID;
    constexpr queue_type::class_id_type queue_type::CLASS_ID;

    constexpr queue_type::backend_id_type
    st::BackendObjTraits< queue_type >::BACKEND_ID;

    constexpr queue_type::class_id_type
    st::BackendObjTraits< queue_type >::BASE_CLASS_ID;

    constexpr queue_type::class_id_type
    st::BackendObjTraits< queue_type >::DERIVED_CLASS_ID;

    /* --------------------------------------------------------------------- */

    queue_type::OclCmdQueue(
        context_type const& SIXTRL_RESTRICT_REF context,
        options_type const flags ) :
        st::BackendObjBase( st::BACKEND_ID_OPENCL,
            queue_type::BASE_CLASS_ID, queue_type::CLASS_ID ),
        m_cl_cmd_queue(), m_flags()
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        if( ( flags & st::OPENCL_CMD_QUEUE_SUPPORTS_OUT_OF_ORDER_EXEC ) ==
              st::OPENCL_CMD_QUEUE_SUPPORTS_OUT_OF_ORDER_EXEC )
        {
            this->m_flags |= CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE;
        }

        if( ( flags & st::OPENCL_CMD_QUEUE_SUPPORTS_PROFILING ) ==
              st::OPENCL_CMD_QUEUE_SUPPORTS_PROFILING )
        {
            this->m_flags |= CL_QUEUE_PROFILING_ENABLE;
        }

        #if defined( CL_VERSION_2_0  )

        if( ( flags & st::OPENCL_CMD_QUEUE_ON_DEVICE ) ==
              st::OPENCL_CMD_QUEUE_ON_DEVICE )
        {
            this->m_flags |= CL_QUEUE_ON_DEVICE;
        }

        if( ( flags & st::OPENCL_CMD_QUEUE_DEFAULT_DEVICE_QUEUE ) ==
              st::OPENCL_CMD_QUEUE_DEFAULT_DEVICE_QUEUE )
        {
            this->m_flags |= CL_QUEUE_ON_DEVICE_DEFAULT;
        }

        #endif /* CL_VERSION_2_0 */

        ::cl_int ret = CL_SUCCESS;

        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        try
        #endif /* CL_HPP_ENABLE_EXCEPTIONS */
        {
            cl::CommandQueue queue( context.cl_context(), this->m_flags, &ret );

            this->m_cl_cmd_queue = std::move( queue );
        }
        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        catch( cl::Error const& e )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >(
                e.err(), "ClCmdQueue", "ClCmdQueue", e.what(),
                    st::size_type{ __LINE__ } );
        }
        #else /* !CL_HPP_ENABLE_EXCEPTIONS */
        if( ret != CL_SUCCESS )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "ClCmdQueue", "ClCmdQueue", "unable to construct queue",
                    st::size_type{ __LINE__ } );
        }
        #endif /* CL_HPP_ENABLE_EXCEPTIONS */
    }

    st_status_t queue_type::flush() const
    {
        ::cl_int ret = CL_SUCCESS;

        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        try
        #endif /* CL_HPP_ENABLE_EXCEPTIONS */
        {
            ret = this->m_cl_cmd_queue.flush();
        }
        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        catch( cl::Error const& e )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >(
                e.err(), "ClCmdQueue", "flush", e.what(),
                    st::size_type{ __LINE__ } );
        }
        #else /* !CL_HPP_ENABLE_EXCEPTIONS */
        if( ret != CL_SUCCESS )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "ClCmdQueue", "flush", "", st::size_type{ __LINE__ } );
        }
        #endif /* CL_HPP_ENABLE_EXCEPTIONS */

        return ( ret == CL_SUCCESS )
            ? st::STATUS_SUCCESS : st::STATUS_GENERAL_FAILURE;
    }

    st_status_t queue_type::finish() const
    {
        ::cl_int ret = CL_SUCCESS;

        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        try
        #endif /* CL_HPP_ENABLE_EXCEPTIONS */
        {
            ret = this->m_cl_cmd_queue.finish();
        }
        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        catch( cl::Error const& e )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >(
                e.err(), "ClCmdQueue", "finish", e.what(),
                    st::size_type{ __LINE__ } );
        }
        #else /* !CL_HPP_ENABLE_EXCEPTIONS */
        if( ret != CL_SUCCESS )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "ClCmdQueue", "finish", "", st::size_type{ __LINE__ } );
        }
        #endif /* CL_HPP_ENABLE_EXCEPTIONS */

        return ( ret == CL_SUCCESS )
            ? st::STATUS_SUCCESS : st::STATUS_GENERAL_FAILURE;
    }
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
