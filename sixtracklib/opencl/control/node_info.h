#ifndef SIXTRACKLIB_OPENCL_CONTROL_NODE_INFO_H__
#define SIXTRACKLIB_OPENCL_CONTROL_NODE_INFO_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/node_info.h"
    #include "sixtracklib/common/control/program_item.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class OclNodeInfo : public SIXTRL_CXX_NAMESPACE::NodeInfoBase
    {
        public:

        static constexpr class_id_type CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_NODE_INFO_CLASS_ID;

        SIXTRL_HOST_FN OclNodeInfo(
            platform_id_type const platform_id = node_id_type::ILLEGAL_PLATFORM_ID,
            device_id_type const device_id = node_id_type::ILLEGAL_DEVICE_ID,
            std::string const& platform_name = std::string{},
            std::string const& device_name = std::string{},
            std::string const& description = std::string{},
            node_index_type const node_index = node_id_type::ILLEGAL_INDEX ) :
            NodeInfoBase( SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL, CLASS_ID,
                platform_id, device_id, platform_name, device_name, description,
                    node_index )
        {
        }

        SIXTRL_HOST_FN OclNodeInfo( OclNodeInfo const& ) = default;
        SIXTRL_HOST_FN OclNodeInfo( OclNodeInfo&& ) = default;

        SIXTRL_HOST_FN OclNodeInfo& operator=( OclNodeInfo const& ) = default;
        SIXTRL_HOST_FN OclNodeInfo& operator=( OclNodeInfo&& ) = default;

        SIXTRL_HOST_FN virtual ~OclNodeInfo() = default;
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::OclNodeInfo >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::NODE_INFO_BASE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_NODE_INFO_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
        SIXTRL_CXX_NAMESPACE::OPENCL_NODE_INFO_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::OclNodeInfo backend_obj_type;
    };

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* SIXTRACKLIB_OPENCL_CONTROL_NODE_INFO_H__ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::OclNodeInfo NS(OclNodeInfo);
#else /* !defined( __cplusplus ) || defined( _GPUCODE ) */
typedef void NS(OclNodeInfo);
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_OPENCL_CONTROL_NODE_INFO_H__ */
