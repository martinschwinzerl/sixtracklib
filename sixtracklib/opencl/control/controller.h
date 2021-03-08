#ifndef SIXTRACKLIB_OPENCL_CONTROL_CONTROLLER_H__
#define SIXTRACKLIB_OPENCL_CONTROL_CONTROLLER_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/opencl/control/program_store.h"
    #include "sixtracklib/opencl/control/program_item.h"
    #include "sixtracklib/opencl/control/node_info.h"
    #include "sixtracklib/opencl/control/context.h"
    #include "sixtracklib/opencl/control/cmd_queue.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/controller.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <map>
    #include <memory>
    #include <stdexcept>
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class OclController : public SIXTRL_CXX_NAMESPACE::ControllerBase
    {
        public:

        using node_id_type       = SIXTRL_CXX_NAMESPACE::NodeId;
        using node_store_type    = SIXTRL_CXX_NAMESPACE::OclNodeStore;
        using node_info_type     = SIXTRL_CXX_NAMESPACE::OclNodeInfo;
        using program_store_type = SIXTRL_CXX_NAMESPACE::OclProgramStore;
        using kernel_id_type     = SIXTRL_CXX_NAMESPACE::ctrl_kernel_id_type;
        using cmd_queue_type     = SIXTRL_CXX_NAMESPACE::OclCmdQueue;
        using context_type       = SIXTRL_CXX_NAMESPACE::OclContext;
        using platform_id_type   = node_id_type::platform_id_type;
        using device_id_type     = node_id_type::device_id_type;
        using node_index_type    = node_id_type::index_type;

        static constexpr class_id_type CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_CONTROLLER_CLASS_ID;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN OclController(
            node_id_type const& SIXTRL_RESTRICT_REF node_id,
            context_type& SIXTRL_RESTRICT_REF context,
            std::shared_ptr< program_store_type >& SIXTRL_RESTRICT_REF prg_store );

        SIXTRL_HOST_FN OclController( OclController const& ) = default;
        SIXTRL_HOST_FN OclController( OclController&& ) = default;

        SIXTRL_HOST_FN OclController& operator=( OclController&& ) = default;

        SIXTRL_HOST_FN OclController&
        operator=( OclController const& ) = default;

        SIXTRL_HOST_FN virtual ~OclController() = default;

        SIXTRL_HOST_FN node_id_type const&
        selected_node_id() const SIXTRL_NOEXCEPT {
            return this->m_selected_node_id; }

        SIXTRL_HOST_FN cl::Device const& cl_selected_device() const;

        SIXTRL_HOST_FN size_type num_cmd_queues() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN cmd_queue_type& cmd_queue( size_type const id );
        SIXTRL_HOST_FN cmd_queue_type const& cmd_queue(
            size_type const id ) const;

        SIXTRL_HOST_FN cmd_queue_type* ptr_cmd_queue(
            size_type const id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN cmd_queue_type const* ptr_cmd_queue(
            size_type const id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN context_type& context() {
            return this->m_context; }

        SIXTRL_HOST_FN context_type const& context() const {
            return this->m_context; }

        SIXTRL_HOST_FN std::shared_ptr< program_store_type >&
        share_program_store() { return this->m_program_store; }

        SIXTRL_HOST_FN std::shared_ptr< node_store_type >&
        share_node_store() { return this->m_node_store; }

        private:

        node_id_type m_selected_node_id;

        std::vector< std::unique_ptr< cmd_queue_type > > m_cmd_queues;
        std::shared_ptr< program_store_type > m_program_store;
        std::shared_ptr< node_store_type > m_node_store;
        context_type& m_context;
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::OclController >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::CONTROLLER_BASE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_CONTROLLER_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
        SIXTRL_CXX_NAMESPACE::OPENCL_CONTROLLER_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::OclController backend_obj_type;
    };
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::OclController NS(OclController);
#else /* !defined( __cplusplus ) || defined( _GPUCODE ) */
typedef void NS(OclController);
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_OPENCL_CONTROL_CONTROLLER_H__ */
