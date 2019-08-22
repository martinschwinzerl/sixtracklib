#include "sixtracklib/testlib/common/control/node_info.hpp"
#include "sixtracklib/common/control/node_info.hpp"
#include "sixtracklib/common/control/node_store.hpp"

#include <cstddef>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <sstream>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/control/definitions.h"

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _info_t = st::tests::TestNodeInfo;

        TestNodeInfo::TestNodeInfo( _info_t::arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name,
            std::string const& SIXTRL_RESTRICT_REF device_name,
            std::string const& SIXTRL_RESTRICT_REF description,
            _info_t::platform_id_t const platform_id,
            _info_t::device_id_t const device_id,
            st::NodeStore* SIXTRL_RESTRICT ptr_node_store ) :
            st::NodeInfoBase( arch_id, platform_name, device_name, description,
                              platform_id, device_id, ptr_node_store )
        {

        }

        TestNodeInfo::TestNodeInfo( _info_t::arch_id_t const arch_id,
            char const* SIXTRL_RESTRICT platform_name,
            char const* SIXTRL_RESTRICT device_name,
            char const* SIXTRL_RESTRICT description,
            _info_t::platform_id_t const platform_id,
            _info_t::device_id_t const device_id,
            st::NodeStore* SIXTRL_RESTRICT ptr_node_store ) :
            st::NodeInfoBase( arch_id, platform_name, device_name, description,
                              platform_id, device_id, ptr_node_store )
        {

        }

        void TestNodeInfo::setMaxAttachementCnt(
            _info_t::size_type const max_attach_cnt ) SIXTRL_NOEXCEPT
        {
            this->doSetMaxAttachementCount( max_attach_cnt );
        }

        void TestNodeInfo::setMaxSelectionCount(
            _info_t::size_type const max_selection_cnt ) SIXTRL_NOEXCEPT
        {
            this->doSetMaxSelectionCount( max_selection_cnt );
        }

        /* ----------------------------------------------------------------- */

        st::arch_status_t TestNodeInfo_add_to_node_store(
            st::NodeStore& SIXTRL_RESTRICT_REF store,
            st::arch_size_t const num_nodes,
            st::arch_id_t const* arch_ids_begin,
            st::node_platform_id_t const* platform_ids_begin,
            st::arch_size_t const* max_atachment_cnt_begin,
            st::arch_size_t const* max_selection_cnt_begin,
            st::node_index_t* node_indices_begin )
        {
            namespace st_test = SIXTRL_CXX_NAMESPACE::tests;

            using size_t = st::arch_size_t;
            using arch_id_t = st::arch_id_t;
            using info_base_t = st::NodeInfoBase;
            using node_index_t = st::node_index_t;
            using platform_id_t = st::node_platform_id_t;
            using store_t = st::NodeStore;

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( num_nodes > size_t{ 0 } ) && ( arch_ids_begin != nullptr ) &&
                ( platform_ids_begin != nullptr ) &&
                ( max_atachment_cnt_begin != nullptr ) &&
                ( max_selection_cnt_begin  != nullptr ) )
            {
                std::ostringstream a2str;
                arch_id_t const* arch_id_it  = arch_ids_begin;
                arch_id_t const* arch_id_end = arch_id_it;
                std::advance( arch_id_end, num_nodes );

                platform_id_t const* plfm_id_it = platform_ids_begin;
                size_t const* max_attach_it = max_atachment_cnt_begin;
                size_t const* max_select_it = max_selection_cnt_begin;
                node_index_t* node_idx_it   = node_indices_begin;

                status = st::ARCH_STATUS_SUCCESS;

                for( ; arch_id_it != arch_id_end ; ++arch_id_it, ++plfm_id_it,
                        ++max_attach_it, ++max_select_it )
                {
                    std::unique_ptr< info_base_t > ptr_node( new
                        st_test::TestNodeInfo( *arch_id_it, nullptr, nullptr,
                            nullptr, *plfm_id_it, store_t::ILLEGAL_DEVICE_ID,
                                &store ) );

                    node_index_t const node_index =
                        store.addNode( std::move( ptr_node ) );

                    if( node_index == store_t::UNDEFINED_INDEX )
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    auto ptr_node_info = static_cast< st_test::TestNodeInfo* >(
                        store.ptrNodeInfoBase( node_index ) );

                    if( ( ptr_node.get() != nullptr ) ||
                        ( ptr_node_info  == nullptr ) )
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    if( node_idx_it != nullptr )
                    {
                        *node_idx_it++ = node_index;
                    }

                    ptr_node_info->setMaxAttachementCnt( *max_attach_it );
                    ptr_node_info->setMaxSelectionCount( *max_select_it );

                    a2str << "platform name " << std::setfill( '0' )
                          << std::setw( 3 ) << *arch_id_it << ":"
                          << std::setw( 4 ) << ptr_node_info->platformId()
                          << "." << std::setw( 4 ) << ptr_node_info->deviceId();

                    ptr_node_info->setPlatformName( a2str.str() );
                    a2str.str( "" );

                    a2str << "device name " << std::setfill( '0' )
                          << std::setw( 3 ) << *arch_id_it << ":"
                          << std::setw( 4 ) << ptr_node_info->platformId()
                          << "." << std::setw( 4 ) << ptr_node_info->deviceId();

                    ptr_node_info->setDeviceName( a2str.str() );
                    a2str.str( "" );

                    a2str << "description " << std::setfill( '0' )
                          << std::setw( 3 ) << *arch_id_it << ":"
                          << std::setw( 4 ) << ptr_node_info->platformId()
                          << "." << std::setw( 4 ) << ptr_node_info->deviceId();

                    ptr_node_info->setDescription( a2str.str() );
                }
            }

            return status;
        }
    }
}

/* end: tests/sixtracklib/testlib/common/control/node_info.cpp */
