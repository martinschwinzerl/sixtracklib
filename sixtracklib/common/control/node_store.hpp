#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_CXX_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_CXX_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )
#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
        #include <cstddef>
        #include <cstdlib>
        #include <cstring>
        #include <cstdio>
        #include <map>
        #include <vector>
#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/arch_info.h"
    #include "sixtracklib/common/control/controller_base.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/node_info_base.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/arch_info.hpp"
    #include "sixtracklib/common/control/controller_base.hpp"
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/node_info_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    struct NodeStoreImpl
    {
        using status_t                = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using size_type               = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using node_info_base_t        = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        using node_id_t               = SIXTRL_CXX_NAMESPACE::NodeId;
        using arch_info_t             = SIXTRL_CXX_NAMESPACE::ArchInfo;
        using arch_id_t               = arch_info_t::arch_id_t;
        using platform_id_t           = node_id_t::platform_id_t;
        using device_id_t             = node_id_t::device_id_t;
        using platform_device_pair_t  = node_id_t::platform_device_pair_t;
        using controll_base_t         = node_id_t::control_base_t;
        using ptr_node_info_base_t    = std::unique_ptr< node_info_base_t >;
        using ptr_node_infos_buffer_t = std::vector< ptr_node_id_t >;
        using arch_id_counter_t       = std::map< arch_id_t, size_type >;



    };

}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) && \
         !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ ) */



#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_CXX_HPP__ */

/* end: sixtracklib/common/control/node_store.hpp */
