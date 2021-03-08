#ifndef SIXTRACKLIB_OPENCL_CONTROL_COMMAND_QUEUE_H__
#define SIXTRACKLIB_OPENCL_CONTROL_COMMAND_QUEUE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus )
    #include "sixtracklib/opencl/opencl.hpp"
    #include "sixtracklib/common/backends/backend_obj_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <stdexcept>
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class OclContext;

    class OclCmdQueue : public SIXTRL_CXX_NAMESPACE::BackendObjBase
    {
        public:

        using context_type = SIXTRL_CXX_NAMESPACE::OclContext;
        using options_type = SIXTRL_CXX_NAMESPACE::ocl_cmd_queue_properties_type;

        static constexpr class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_COMMAND_QUEUE_CLASS_ID;

        static constexpr class_id_type CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_COMMAND_QUEUE_CLASS_ID;

        static constexpr options_type FLAGS_NONE =
            SIXTRL_CXX_NAMESPACE::OPENCL_CMD_QUEUE_NONE_FLAGS;

        SIXTRL_HOST_FN explicit OclCmdQueue(
            context_type const& SIXTRL_RESTRICT_REF context,
            options_type const options = FLAGS_NONE );

        SIXTRL_HOST_FN OclCmdQueue( OclCmdQueue const& ) = default;
        SIXTRL_HOST_FN OclCmdQueue( OclCmdQueue&& ) = default;

        SIXTRL_HOST_FN OclCmdQueue& operator=( OclCmdQueue&& ) = default;
        SIXTRL_HOST_FN OclCmdQueue& operator=( OclCmdQueue const& ) = default;

        SIXTRL_HOST_FN virtual ~OclCmdQueue() = default;

        SIXTRL_HOST_FN status_type flush() const;
        SIXTRL_HOST_FN status_type finish() const;

        SIXTRL_HOST_FN bool execs_out_of_order() const SIXTRL_NOEXCEPT {
            return ( CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE == (
                     this->m_flags & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE ) );
        }

        SIXTRL_HOST_FN bool supports_profiling() const SIXTRL_NOEXCEPT {
            return ( ( this->m_flags & CL_QUEUE_PROFILING_ENABLE ) ==
                       CL_QUEUE_PROFILING_ENABLE );
        }

        SIXTRL_HOST_FN cl::CommandQueue const& cl_command_queue(
            ) const SIXTRL_NOEXCEPT { return this->m_cl_cmd_queue; }

        SIXTRL_HOST_FN cl::CommandQueue& cl_command_queue(
            ) SIXTRL_NOEXCEPT { return this->m_cl_cmd_queue; }

        private:

        cl::CommandQueue m_cl_cmd_queue;
        ::cl_command_queue_properties m_flags;
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::OclCmdQueue >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_COMMAND_QUEUE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_COMMAND_QUEUE_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
        SIXTRL_CXX_NAMESPACE::OPENCL_COMMAND_QUEUE_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::OclCmdQueue backend_obj_type;
    };
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::OclCmdQueue NS(OclCmdQueue);
#else  /* !defined( __cplusplus ) || defined( _GPUCODE ) */
typedef void NS(OclCmdQueue);
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_OPENCL_CONTROL_COMMAND_QUEUE_H__ */
