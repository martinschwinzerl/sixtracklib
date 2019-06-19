#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_ID_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_ID_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <cstdio>
    #include <cstring>
    #include <map>
    #include <string>
    #include <ostream>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/controller_base.hpp"
    #include "sixtracklib/common/buffer/buffer_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

typedef struct NS(NodePlatformNodeIdPair)
{
    NS(node_platform_id_t) platform_id   SIXTRL_ALIGN( 8 );
    NS(node_device_id_t)   device_id     SIXTRL_ALIGN( 8 );
};


#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

namespace SIXTRL_CXX_NAMESPACE
{
    class NodeId
    {
        public:

        using arch_info_t = SIXTRL_CXX_NAMESPACE::ArchInfo;
        using arch_id_t = arch_info_t::arch_id_t;
        using size_type = SIXTRL_CXX_NAMESPACE::ctrl_size_t;
        using status_t = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using platform_id_t = SIXTRL_CXX_NAMESPACE::platform_id_t;
        using device_id_t = SIXTRL_CXX_NAMESPACE::device_id_t;
        using node_index_t = SIXTRL_CXX_NAMESPACE::node_index_t;
        using controller_base_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        using platform_device_pair_t = ::NS(NodePlatformNodeIdPair);

        static SIXTRL_CONSTEXPR_OR_CONST platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PATFORM_ID;

        static SIXTRL_CONSTEXPR_OR_CONST device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static SIXTRL_CONSTEXPR_OR_CONST node_index_t UNDEFINED_INDEX =
            SIXTRL_CXX_NAMESPACE::NODE_UNDEFINED_INDEX;

        SIXTRL_FN explicit NodeId(
            platform_id_t const platform_id = ILLEGAL_PLATFORM_ID,
            device_id_t const device_id = ILLEGAL_DEVICE_ID );

        SIXTRL_FN explicit NodeId(
            std::string const& SIXTRL_RESTRICT_REF id_str );

        SIXTRL_FN explicit NodeId( const char *const SIXTRL_RESTRICT id_str );

        SIXTRL_FN NodeId( NodeId const& other ) = default;
        SIXTRL_FN NodeId( NodeId&& other ) = default;

        SIXTRL_FN NodeId& operator=( NodeId const& rhs ) = default;
        SIXTRL_FN NodeId& operator=( NodeId&& rhs ) = default;

        SIXTRL_FN virtual ~NodeId() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN bool valid() const SIXTRL_NOEXCEPT;

        SIXTRL_FN platform_id_t platformId() const SIXTRL_NOEXCEPT;
        SIXTRL_FN device_id_t   deviceId() const SIXTRL_NOEXCEPT;

        SIXTRL_FN status_t setPlatformId(
            platform_id_t const id ) SIXTRL_NOEXCEPT;

        SIXTRL_FN status_t setDeviceId(
            device_id_t const id ) SIXTRL_NOEXCEPT;

        SIXTRL_FN platform_device_pair_t const&
        platformDeviceIdPair() const SIXTRL_NOEXCEPT;

        SIXTRL_FN platform_device_pair_t&
        platformDeviceIdPair() SIXTRL_NOEXCEPT;

        SIXTRL_FN platform_device_pair_t const*
        ptrPlatformDeviceIdPair() const SIXTRL_NOEXCEPT;

        SIXTRL_FN platform_device_pair_t*
        ptrPlatformDeviceIdPair() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasControllers() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type numControllers() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isAttachedToController( controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasNodeIndex( controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex( controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setNodeIndex(
            controller_base_t const& SIXTRL_RESTRICT_REF ctrl,
            node_index_t const node_index ) SIXTRL_RESTRICT;

        SIXTRL_HOST_FN bool isSelected() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSelectedByController( controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isDefault() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isDefaultForController( controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN controller_base_t const*
        ptrSelectingController() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setPtrSelectedController(
            controller_base_t const* SIXTRL_RESTRICT ptr_ctrl ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setSelectedController(
            controller_base_t const& SIXTRL_RESTRICT_REF ctrl ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t resetSelectingController() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t attachToController(
            controller_base_t const& SIXTRL_RESTRICT_REF ctrl,
            node_index_t const node_index = UNDEFINED_INDEX );

        SIXTRL_HOST_FN status_t detachFromController( controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN controller_base_t const* ptrController(
            size_type const num_of_controller_in_list ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t fromNodeIdStr(
            std::string const& SIXTRL_RESTRICT_REF id_str ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t fromNodeIdStr(
            const char *const SIXTRL_RESTRICT id_str ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string toNodeIdStr() const;

        SIXTRL_HOST_FN status_t toNodeIdStr(
            std::ostream& SIXTRL_RESTRICT_REF a2str ) const;

        SIXTRL_FN status_t toNodeIdStr( char* SIXTRL_RESTRICT node_id_str,
            size_type const node_id_str_capacity ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasArchIds() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type numArchIds() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_id_t const* archIdsBegin() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN arch_id_t const* archIdsEnd() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numControllers(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void print( std::ostream& SIXTRL_RESTRICT_REF os );
        SIXTRL_HOST_FN void print( ::FILE* SIXTRL_RESTRICT fp );
        SIXTRL_HOST_FN void printOut();

        SIXTRL_HOST_FN size_type requiredStringCapacity() const;
        SIXTRL_HOST_FN std::string toString() const;
        SIXTRL_HOST_FN status_t toString( size_type out_str_capacity,
                char* SIXTRL_RESTRICT output_str ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN bool operator<(
            NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_FN void clear() SIXTRL_NOEXCEPT;

        private:

        using ptr_ctrl_to_node_index_map_t =
            std::map< controller_base_t const*, node_index_t >;

        using ptr_ctrl_list_t   = std::vector< controller_base_t const* >;
        using arch_id_counter_t = std::map< arch_id_t, size_type >;
        using arch_id_list_t    = std::vector< arch_id_t >;

        ptr_ctrl_to_node_index_map_t  m_ptr_ctrl_to_node_index_map;
        ptr_ctrl_list_t               m_available_on_controllers;
        arch_id_counter_t             m_arch_ids_counter;
        arch_id_list_t                m_arch_ids_list;
        platform_device_pair_t        m_platform_device_pair;
        controller_base_t*            m_ptr_selected_by_controller;
    };

    SIXTRL_HOST_FN std::ostream& operator<<(
        std::ostream& SIXTRL_RESTRICT_REF output,
        SIXTRL_CXX_NAMESPACE::NodeId const& SIXTRL_RESTRICT_REF node_id );

    SIXTRL_HOST_FN int compareNodeIds(
        SIXTRL_CXX_NAMESPACE::NodeId const& SIXTRL_RESTRICT_REF lhs,
        SIXTRL_CXX_NAMESPACE::NodeId const& SIXTRL_RESTRICT_REF rhs );

    SIXTRL_STATIC SIXTRL_HOST_FN std::string
    NodeId_extract_node_id_str_from_config_str(
        std::string const& SIXTRL_RESTRICT_REF config_str );

    SIXTRL_STATIC SIXTRL_HOST_FN std::string
    NodeId_extract_node_id_str_from_config_str(
        char const* SIXTRL_RESTRICT config_str );
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* c++ */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

typedef SIXTRL_CXX_NAMESPACE::NodeId  NS(NodeId);

#else  /* !C++, Host */

typedef void NS(NodeId);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* c++ */

/* ************************************************************************* */
/* ******  Implementation of inline and template member functions    ******* */
/* ************************************************************************* */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <cstring>
    #include <regex>
    #include <utility>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE std::string NodeId_extract_node_id_str_from_config_str(
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        using SIXTRL_CXX_NAMESPACE::NodeId_extract_node_id_str_from_config_str;
        return NodeId_extract_node_id_str_from_config_str( config_str.c_str());
    }

    SIXTRL_INLINE std::string NodeId_extract_node_id_str_from_config_str(
        char const* SIXTRL_RESTRICT config_str )
    {
        if( ( config_str != nullptr ) &&
            ( std::strlen( config_str ) > std::size_t{ 0 } ) )
        {
            /*
            std::regex re(
                        "device_id_str[:blank:]*=[:blank:]*"
                              "([:digit:]+.[:digit:]+)[A-Za-z0-9_\\-#=:;., \t]*|"
                        "^[A-Za-z0-9_\\-#=;.:, \t]*([:digit:]+.[:digit:]+);|"
                        "([:digit:]+.[:digit:]+)" );*/

            std::regex re( "\\s*([0-9]+\\.[0-9]+)[\\sA-Za-z0-9#\\;]*" );
            std::cmatch matches;

            std::regex_match( config_str, matches, re );

            if( ( matches.ready() ) && ( !matches.empty() ) )
            {
                return std::string{ matches[ matches.size() - 1 ] };
            }
        }

        return std::string{ "" };
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_ID_HPP__ */

/* end: sixtracklib/common/control/node_id.hpp */
