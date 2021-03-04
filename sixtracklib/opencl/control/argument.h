#ifndef SIXTRACKLIB_OPENCL_CONTROL_ARGUMENT_H__
#define SIXTRACKLIB_OPENCL_CONTROL_ARGUMENT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/common/control/argument.h"
    #include "sixtracklib/opencl/control/context.h"
    #include "sixtracklib/opencl/control/cmd_queue.h"
    #include "sixtracklib/opencl/control/controller.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus )
    #include "sixtracklib/opencl/opencl.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <memory>
    #include <stdexcept>
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class OclArgument : public SIXTRL_CXX_NAMESPACE::ArgumentBase
    {
        public:

        using controller_type = SIXTRL_CXX_NAMESPACE::OclController;
        using context_type = SIXTRL_CXX_NAMESPACE::OclContext;

        static constexpr class_id_type CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_ARGUMENT_CLASS_ID;

        SIXTRL_HOST_FN explicit OclArgument(
            context_type& SIXTRL_RESTRICT_REF context );

        SIXTRL_HOST_FN OclArgument(
            ::NS(CBuffer)* SIXTRL_RESTRICT cbuffer,
            controller_type& SIXTRL_RESTRICT_REF controller );


        SIXTRL_HOST_FN OclArgument( OclArgument const& ) = delete;
        SIXTRL_HOST_FN OclArgument( OclArgument&& ) = default;

        SIXTRL_HOST_FN OclArgument& operator=( OclArgument const& ) = delete;
        SIXTRL_HOST_FN OclArgument& operator=( OclArgument&& ) = default;

        SIXTRL_HOST_FN virtual ~OclArgument() = default;

        using SIXTRL_CXX_NAMESPACE::ArgumentBase::push;
        using SIXTRL_CXX_NAMESPACE::ArgumentBase::collect;


        SIXTRL_HOST_FN cl::Buffer const& cl_buffer() const SIXTRL_NOEXCEPT {
            return this->m_cl_buffer; };

        SIXTRL_HOST_FN cl::Buffer& cl_buffer() SIXTRL_NOEXCEPT {
            return this->m_cl_buffer; }

        protected:

        SIXTRL_HOST_FN status_type _init_from_cbuffer(
            ::NS(CBuffer)* SIXTRL_RESTRICT cbuffer );


        private:

        cl::Buffer       m_cl_buffer;
        context_type&    m_context;
        controller_type* m_ptr_controller   = nullptr;
        size_type        m_push_queue_id    = size_type{ 0 };
        size_type        m_collect_queue_id = size_type{ 0 };
        size_type        m_kernel_queue_id  = size_type{ 0 };
        size_type        m_cl_buffer_size   = size_type{ 0 };
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::OclArgument >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::ARGUMENT_BASE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_ARGUMENT_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE,
        SIXTRL_CXX_NAMESPACE::OPENCL_ARGUMENT_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::OclArgument backend_obj_type;
    };

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::OclArgument NS(OclArgument);
#else /* defined( __cplusplus ) && !defined( _GPUCODE ) */
typedef void NS(OclArgument);
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_OPENCL_CONTROL_ARGUMENT_H__ */
