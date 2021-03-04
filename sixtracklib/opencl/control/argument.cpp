#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/control/argument.h"
    #include "sixtracklib/opencl/control/controller.h"
    #include "sixtracklib/opencl/control/context.h"
    #include "sixtracklib/opencl/control/cmd_queue.h"
    #include "sixtracklib/opencl/internal/helpers.h"
    #include "sixtracklib/common/control/argument.h"
#endif /* !defined( SIXTRL_NO_INCLUDES )  */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <iostream>
    #include <stdexcept>
    #include <sstream>
#endif /* !defined( SIXTRL_NO_INCLUDES )  && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using ocl_arg_type        = st::OclArgument;
        using base_arg_type       = st::ArgumentBase;
        using ocl_ctrl_type       = st::OclController;
        using ocl_prog_store_type = ocl_ctrl_type::program_store_type;
        using ocl_context_type    = ocl_ctrl_type::context_type;
        using ocl_cmd_queue_type  = ocl_ctrl_type::cmd_queue_type;
        using st_node_id_t        = ocl_ctrl_type::node_id_type;
        using st_node_info_t      = ocl_ctrl_type::node_info_type;
        using st_status_t         = ocl_ctrl_type::status_type;
        using st_size_t           = ocl_ctrl_type::size_type;
        using st_platform_id_t    = ocl_ctrl_type::platform_id_type;
        using st_device_id_t      = ocl_ctrl_type::device_id_type;
        using st_node_index_t     = ocl_ctrl_type::node_index_type;
    }

    OclArgument::OclArgument( ocl_context_type& context ) :
        st::ArgumentBase( st::BACKEND_ID_OPENCL, ocl_arg_type::CLASS_ID ),
        m_cl_buffer(), m_context( context ) {}

    OclArgument::OclArgument(
        ::NS(CBuffer)* SIXTRL_RESTRICT cbuffer,
        ocl_ctrl_type& SIXTRL_RESTRICT_REF controller ) :
        st::ArgumentBase( st::BACKEND_ID_OPENCL, ocl_arg_type::CLASS_ID ),
        m_cl_buffer(), m_context( controller.context() ),
        m_ptr_controller( &controller )
    {
        if( cbuffer != nullptr )
        {
            st_status_t const status = this->_init_from_cbuffer( cbuffer );
            SIXTRL_ASSERT( status == st::STATUS_SUCCESS );
            ( void )status;
        }
    }

    st_status_t OclArgument::_init_from_cbuffer(
        ::NS(CBuffer)* SIXTRL_RESTRICT_REF cbuffer )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( cbuffer != nullptr ) && ( this->m_context.key().is_legal() ) &&
            ( this->m_ptr_controller != nullptr ) &&
            ( &( this->m_ptr_controller->context() ) == &this->m_context ) &&
            ( ::NS(CBuffer_size)( cbuffer ) >
              st::CBufferView::MIN_BUFFER_SIZE(
                ::NS(CBuffer_slot_size)( cbuffer ) ) ) )
        {
            st_size_t const requ_size = ::NS(CBuffer_size)( cbuffer );
            st_size_t const n_queues = this->m_ptr_controller->num_cmd_queues();

            if( ( n_queues <= this->m_push_queue_id ) ||
                ( this->m_ptr_controller->ptr_cmd_queue(
                    this->m_push_queue_id ) == nullptr ) ||
                ( n_queues <= this->m_kernel_queue_id ) ||
                ( this->m_ptr_controller->ptr_cmd_queue(
                    this->m_kernel_queue_id ) == nullptr ) )
            {
                return status;
            }

            ::cl_int ret = CL_SUCCESS;

            #if defined( SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG ) && \
                         SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG == 1
            try
            {
            #endif /* OpenCL 1.x C++ Host Exceptions enabled */

            cl::Buffer b( this->m_context.cl_context(),
                CL_MEM_READ_WRITE, requ_size, nullptr, &ret );

            this->m_cl_buffer = std::move( b );

            #if defined( SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG ) && \
                         SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG == 1
            }
            catch( cl::Error& e )
            {
                ret = e.err();
                st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                    "OclRtcProgramItem", "_init_from_cbuffer", e.what(),
                        st_size_t{ __LINE__ } );
            }
            #endif /* OpenCL 1.x C++ Host Exceptions enabled */

            if( ret == CL_SUCCESS )
            {
                status = st::STATUS_SUCCESS;
            }
            else
            {
                st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                    "OclRtcProgramItem", "_init_from_cbuffer",
                        "error during allocation of buffer",
                            st_size_t{ __LINE__ } );
            }

            if( status != st::STATUS_SUCCESS ) return status;

            #if defined( SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG ) && \
                        SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG == 1
            try
            {
            #endif /* OpenCL 1.x C++ Host Exceptions enabled */

                auto& q = this->m_ptr_controller->cmd_queue( this->m_push_queue_id );
                auto const lock = q.create_lock();
                ret = q.cl_command_queue( lock ).enqueueWriteBuffer(
                    this->m_cl_buffer, true, ::size_t{ 0 }, requ_size,
                        ::NS(CBuffer_p_const_base_begin)( cbuffer ) );

            #if defined( SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG ) && \
                         SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG == 1
            }
            catch( cl::Error& e )
            {
                status = st::STATUS_GENERAL_FAILURE;

                ret = e.err();
                st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                    "OclRtcProgramItem", "_init_from_cbuffer", e.what(),
                        st_size_t{ __LINE__ } );
            }
            #endif /* OpenCL 1.x C++ Host Exceptions enabled */

            if( ret != CL_SUCCESS )
            {
                st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                    "OclRtcProgramItem", "_init_from_cbuffer",
                        "error during push of cbuffer to device side",
                            st_size_t{ __LINE__ } );
            }
        }

        return status;
    }


}
#endif /* C++, Host */
