#ifndef SIXTRACKLIB_OPENCL_CONTROL_NODE_ID_STORE_H__
#define SIXTRACKLIB_OPENCL_CONTROL_NODE_ID_STORE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/opencl/control/node_info.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus )
    #include "sixtracklib/opencl/opencl.hpp"
    #include "sixtracklib/common/backends/backend_obj_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <algorithm>
    #include <iterator>
    #include <map>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class OclNodeStore : public SIXTRL_CXX_NAMESPACE::BackendObjBase
    {
        public:

        using node_id_type     = SIXTRL_CXX_NAMESPACE::NodeId;
        using platform_id_type = node_id_type::platform_id_type;
        using device_id_type   = node_id_type::device_id_type;
        using node_index_type  = node_id_type::index_type;
        using node_info_type   = SIXTRL_CXX_NAMESPACE::OclNodeInfo;

        static constexpr class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_NODE_STORE_CLASS_ID;

        static constexpr class_id_type CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_NODE_STORE_CLASS_ID;

        /* ----------------------------------------------------------------- */

        static SIXTRL_HOST_FN status_type GET_ALL_CL_PLATFORMS(
            std::vector< cl::Platform >& SIXTRL_RESTRICT_REF avail_platforms );

        static SIXTRL_HOST_FN status_type GET_CL_DEVICES_FOR_CL_PLATFORM(
            cl::Platform const& SIXTRL_RESTRICT_REF platform,
            std::vector< cl::Device >& SIXTRL_RESTRICT_REF avail_devices,
            ::cl_device_type const only_type_of_device = CL_DEVICE_TYPE_ALL );

        static SIXTRL_HOST_FN status_type GET_NODE_DESCRIPTION_FROM_CL_DEVICE(
            cl::Device const& SIXTRL_RESTRICT_REF cl_device,
            std::string& SIXTRL_RESTRICT_REF device_description );

        static SIXTRL_HOST_FN node_info_type CREATE_NODE_INFO_FOR_CL_DEVICE(
            cl::Platform const& SIXTRL_RESTRICT_REF cl_platform,
            cl::Device const& SIXTRL_RESTRICT_REF cl_device,
            platform_id_type const platform_id, device_id_type const device_id,
            node_index_type const node_index );

        static SIXTRL_HOST_FN status_type GET_ALL_AVAILABLE_NODES(
            std::vector< cl::Platform>& SIXTRL_RESTRICT_REF available_platforms,
            std::vector< cl::Device >&  SIXTRL_RESTRICT_REF available_devices,
            std::vector< node_id_type >*   SIXTRL_RESTRICT available_nodes_id,
            std::vector< node_info_type >* SIXTRL_RESTRICT available_nodes_info );

        static SIXTRL_HOST_FN status_type GET_ALLOWED_NODES_FROM_ENV_VARIABLE(
            char const* SIXTRL_RESTRICT env_variable_name,
            std::vector< node_id_type >& SIXTRL_RESTRICT_REF node_ids );

        static SIXTRL_HOST_FN status_type GET_AVAILABLE_NODES(
            std::vector< node_id_type >& SIXTRL_RESTRICT_REF available_nodes_id,
            std::vector< node_info_type >* SIXTRL_RESTRICT available_nodes_info,
            std::vector< cl::Device >* SIXTRL_RESTRICT ptr_available_devices,
            char const* SIXTRL_RESTRICT env_variable_name = nullptr ,
            char const* SIXTRL_RESTRICT filter_str = nullptr );

        static SIXTRL_HOST_FN status_type GET_ALLOWED_NODES_FROM_ENV_VARIABLE(
            std::vector< node_id_type >& SIXTRL_RESTRICT allowed_node_ids,
            char const* SIXTRL_RESTRICT env_variable_name = nullptr );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN OclNodeStore();

        SIXTRL_HOST_FN OclNodeStore( OclNodeStore const& ) = default;
        SIXTRL_HOST_FN OclNodeStore( OclNodeStore&& ) = default;

        SIXTRL_HOST_FN OclNodeStore& operator=( OclNodeStore const& ) = default;
        SIXTRL_HOST_FN OclNodeStore& operator=( OclNodeStore&& ) = default;

        SIXTRL_HOST_FN virtual ~OclNodeStore() = default;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN void clear() { this->do_clear(); }

        SIXTRL_HOST_FN std::vector< node_id_type > const&
        node_ids() const SIXTRL_NOEXCEPT { return this->m_node_ids; }

        SIXTRL_HOST_FN std::vector< node_info_type > const&
        node_infos() const SIXTRL_NOEXCEPT { return this->m_node_infos; }

        SIXTRL_HOST_FN bool empty() const SIXTRL_NOEXCEPT
        {
            SIXTRL_ASSERT( this->m_node_ids.size() >=
                           this->m_platform_id_to_data_map.size() );

            SIXTRL_ASSERT( this->m_node_ids.size() ==
                           this->m_node_infos.size() );

            return this->m_node_ids.empty();
        }


        SIXTRL_HOST_FN size_type num_nodes() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_nodes(
            platform_id_type const platform_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_type node_index( node_id_type const&
            SIXTRL_RESTRICT_REF node_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_type node_index(
            platform_id_type const platform_id,
            device_id_type const device_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_type const* node_indices_begin(
            platform_id_type const platform_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_type const* node_indices_end(
            platform_id_type const platform_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_platform_id(
            platform_id_type const platform_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_node_index( node_index_type const
            node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_node_id( node_id_type const&
            SIXTRL_RESTRICT_REF node_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_node_id( platform_id_type const platform_id,
            device_id_type const device_id ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN node_id_type const& node_id(
            node_index_type const node_index ) const;

        SIXTRL_HOST_FN status_type node_ids(
            std::vector< node_id_type >& SIXTRL_RESTRICT_REF node_ids,
            platform_id_type const platform_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type node_ids(
            std::vector< node_id_type >& SIXTRL_RESTRICT_REF node_ids,
            node_index_type const* SIXTRL_RESTRICT node_indices_begin,
            size_type const num_node_indices ) const SIXTRL_NOEXCEPT;

        template< typename NodeIndexIter >
        SIXTRL_HOST_FN status_type node_ids(
            std::vector< node_id_type >& SIXTRL_RESTRICT_REF node_ids,
            NodeIndexIter node_indices_begin,
            NodeIndexIter node_indices_end ) const SIXTRL_NOEXCEPT
        {
            std::vector< node_index_type > temp_node_indices(
                node_indices_begin, node_indices_end );

            return this->node_ids( node_ids, temp_node_indices.data(),
                temp_node_indices.size() );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN cl::Platform const& cl_platform(
            platform_id_type const platform_id ) const;

        SIXTRL_HOST_FN cl::Platform& cl_platform(
            platform_id_type const platform_id ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return const_cast< cl::Platform& >( static_cast<
                st::OclNodeStore const& >( *this ).cl_platform( platform_id ) );
        }

        SIXTRL_HOST_FN cl::Device const& cl_device(
            node_id_type const& SIXTRL_RESTRICT_REF node_id ) const;

        SIXTRL_HOST_FN cl::Device const& cl_device(
            platform_id_type const platform_id,
            device_id_type const device_id ) const;

        SIXTRL_HOST_FN cl::Device const& cl_device(
            node_index_type const node_index ) const;

        SIXTRL_HOST_FN cl::Device& cl_device(
            node_id_type const& SIXTRL_RESTRICT_REF node_id ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return const_cast< cl::Device& >( static_cast<
                st::OclNodeStore const& >( *this ).cl_device( node_id ) ); }

        SIXTRL_HOST_FN cl::Device& cl_device(
            platform_id_type const platform_id, device_id_type const device_id ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return const_cast< cl::Device& >( static_cast<
                st::OclNodeStore const& >( *this ).cl_device(
                    platform_id, device_id ) ); }

        SIXTRL_HOST_FN cl::Device& cl_device( node_index_type const node_index ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return const_cast< cl::Device& >( static_cast<
                st::OclNodeStore const& >( *this ).cl_device( node_index ) ); }

        SIXTRL_HOST_FN std::vector< cl::Device > const& all_cl_devices(
            platform_id_type const platform_id ) const;

        SIXTRL_HOST_FN status_type cl_devices(
            std::vector< cl::Device >& SIXTRL_RESTRICT_REF devices,
            node_index_type const* SIXTRL_RESTRICT node_indices_begin,
            size_type const num_devices ) SIXTRL_NOEXCEPT;

        template< typename NodeIndicesIter >
        SIXTRL_HOST_FN status_type cl_devices(
            std::vector< cl::Device >& SIXTRL_RESTRICT_REF devices,
            NodeIndicesIter node_indices_begin,
            NodeIndicesIter node_indices_end ) SIXTRL_NOEXCEPT
        {
            std::vector< node_index_type > temp_node_indices(
                node_indices_begin, node_indices_end );
            return this->cl_devices( devices, temp_node_indices.data(),
                temp_node_indices.size() );
        }

        protected:

        SIXTRL_HOST_FN virtual void do_clear();


        private:

        SIXTRL_HOST_FN status_type _ocl_init_all_nodes(
            ::cl_device_type const only_type_of_device = CL_DEVICE_TYPE_ALL );

        SIXTRL_HOST_FN void _ocl_clear();

        struct OclPlatformData
        {
            SIXTRL_HOST_FN OclPlatformData() = default;
            SIXTRL_HOST_FN OclPlatformData( OclPlatformData const& ) = default;
            SIXTRL_HOST_FN OclPlatformData( OclPlatformData&& ) = default;

            SIXTRL_HOST_FN OclPlatformData& operator=(
                OclPlatformData const& ) = default;

            SIXTRL_HOST_FN OclPlatformData& operator=(
                OclPlatformData&& ) = default;

            SIXTRL_HOST_FN ~OclPlatformData() = default;

            cl::Platform cl_platform = cl::Platform{};

            std::vector< cl::Device > cl_devices =
                std::vector< cl::Device >{};

            std::vector< node_index_type > node_indices =
                std::vector< node_index_type >{};
        };

        std::map< platform_id_type, OclPlatformData > m_platform_id_to_data_map;
        std::vector< node_id_type >   m_node_ids;
        std::vector< node_info_type > m_node_infos;
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::OclNodeStore >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_NODE_STORE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_NODE_STORE_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
        SIXTRL_CXX_NAMESPACE::OPENCL_NODE_STORE_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::OclNodeStore backend_obj_type;
    };
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::OclNodeStore NS(OclNodeStore);
#else  /* !defined( __cplusplus ) || defined( _GPUCODE ) */
typedef void NS(OclNodeStore);
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_OPENCL_CONTROL_NODE_ID_STORE_H__ */
