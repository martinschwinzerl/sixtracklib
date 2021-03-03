#ifndef SIXTRACKLIB_OPENCL_CONTROL_COMMAND_QUEUE_H__
#define SIXTRACKLIB_OPENCL_CONTROL_COMMAND_QUEUE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus )
    #include "sixtracklib/opencl/opencl.hpp"
    #include "sixtracklib/common/backends/mt_backend_obj_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <stdexcept>
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class OclContext;

    class OclCommandQueue : public SIXTRL_CXX_NAMESPACE::MTBackendObjBase
    {
        public:

        using context_type = SIXTRL_CXX_NAMESPACE::OclContext;

        static constexpr class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_COMMAND_QUEUE_CLASS_ID;

        static constexpr class_id_type CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_COMMAND_QUEUE_CLASS_ID;


        SIXTRL_HOST_FN explicit OclCommandQueue(
            context_type const& SIXTRL_RESTRICT_REF context );

        SIXTRL_HOST_FN explicit OclCommandQueue(
            cl::Context const& SIXTRL_RESTRICT_REF context );

        SIXTRL_HOST_FN OclCommandQueue( OclCommandQueue const& ) = delete;
        SIXTRL_HOST_FN OclCommandQueue( OclCommandQueue&& ) = delete;

        SIXTRL_HOST_FN OclCommandQueue& operator=( OclCommandQueue&& ) = delete;
        SIXTRL_HOST_FN OclCommandQueue& operator=(
            OclCommandQueue const& ) = delete;

        SIXTRL_HOST_FN virtual ~OclCommandQueue() = default;

        SIXTRL_HOST_FN status_type flush(
            guard_type const& SIXTRL_RESTRICT_REF guard ) const {
            if( !this->is_locked( guard ) ) throw std::runtime_error(
                    "cl_command_queue const: illegal lock" );
            return ( CL_SUCCESS == this->m_cl_command_queue.flush() )
                ? SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS
                : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        SIXTRL_HOST_FN status_type flush() const {
            return this->flush( this->create_lock() ); }

        SIXTRL_HOST_FN status_type finish(
            guard_type const& SIXTRL_RESTRICT_REF guard ) const {
            if( !this->is_locked( guard ) ) throw std::runtime_error(
                    "cl_command_queue const: illegal lock" );
            return ( CL_SUCCESS == this->m_cl_command_queue.finish() )
                ? SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS
                : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

        SIXTRL_HOST_FN status_type finish() const {
            return this->finish( this->create_lock() ); }

        SIXTRL_HOST_FN cl::CommandQueue const& cl_command_queue(
            guard_type const& SIXTRL_RESTRICT_REF guard ) const {
            if( !this->is_locked( guard ) ) throw std::runtime_error(
                    "cl_command_queue const: illegal lock" );
            return this->m_cl_command_queue;
        }

        SIXTRL_HOST_FN cl::CommandQueue& cl_command_queue(
            guard_type const& SIXTRL_RESTRICT_REF guard ) {
            if( !this->is_locked( guard ) ) throw std::runtime_error(
                    "cl_command_queue: illegal lock" );
            return this->m_cl_command_queue;
        }

        private:

        cl::CommandQueue m_cl_command_queue;
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::OclCommandQueue >
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
        typedef SIXTRL_CXX_NAMESPACE::OclCommandQueue backend_obj_type;
    };
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::OclCommandQueue NS(OclCommandQueue);
#else  /* !defined( __cplusplus ) || defined( _GPUCODE ) */
typedef void NS(OclCommandQueue);
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_OPENCL_CONTROL_COMMAND_QUEUE_H__ */
