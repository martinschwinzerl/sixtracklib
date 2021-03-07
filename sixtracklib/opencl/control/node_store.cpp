#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/control/node_store.h"
    #include "sixtracklib/opencl/control/node_info.h"
    #include "sixtracklib/opencl/internal/helpers.h"
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES )  */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <algorithm>
    #include <iostream>
    #include <iterator>
    #include <regex>
    #include <sstream>
#endif /* !defined( SIXTRL_NO_INCLUDES )  && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using ocl_node_store_type = st::OclNodeStore;
        using st_node_id_t        = ocl_node_store_type::node_id_type;
        using st_node_info_t      = ocl_node_store_type::node_info_type;
        using st_size_t           = ocl_node_store_type::size_type;
        using st_status_t         = ocl_node_store_type::status_type;
        using st_node_index_t     = st_node_id_t::index_type;
        using st_platform_id_t    = st_node_id_t::platform_id_type;
        using st_device_id_t      = st_node_id_t::device_id_type;
    }

    constexpr ocl_node_store_type::class_id_type
              ocl_node_store_type::CLASS_ID;

    constexpr ocl_node_store_type::class_id_type
              ocl_node_store_type::BASE_CLASS_ID;

    constexpr ocl_node_store_type::backend_id_type
    st::BackendObjTraits< ocl_node_store_type >::BACKEND_ID;

    constexpr ocl_node_store_type::class_id_type
    st::BackendObjTraits< ocl_node_store_type >::BASE_CLASS_ID;

    constexpr ocl_node_store_type::class_id_type
    st::BackendObjTraits< ocl_node_store_type >::DERIVED_CLASS_ID;

    /* ********************************************************************* */

    st_status_t ocl_node_store_type::GET_ALL_CL_PLATFORMS(
        std::vector< cl::Platform >& SIXTRL_RESTRICT_REF avail_platforms ) {
        st_status_t status = st::STATUS_SUCCESS;

        avail_platforms.clear();
        ::cl_uint num_platforms = ::cl_uint{ 0 };
        ::cl_int ret = CL_SUCCESS;

//         #if defined( CL_HPP_ENABLE_EXCEPTIONS )
//         try
//         #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        {
            ret = ::clGetPlatformIDs( ::cl_uint{ 0 }, nullptr, &num_platforms );
            if( ret != CL_SUCCESS ) num_platforms = ::cl_uint{ 0 };
        }
//         #if defined( CL_HPP_ENABLE_EXCEPTIONS )
//         catch( cl::Error const& e )
//         {
//             st::OpenCL_ret_value_to_exception< std::runtime_error >( e.err(),
//                 "OclNodeStore", "GET_ALL_CL_PLATFORMS", e.what(),
//                     st_size_t{ __LINE__ } );
//             status = st::STATUS_GENERAL_FAILURE;
//         }
//         #else /* !defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        if( CL_SUCCESS != ret )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclNodeStore", "GET_ALL_CL_PLATFORMS", "",
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
//         #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */

        if( num_platforms == ::cl_uint{ 0 } ) return status;
        std::vector< ::cl_platform_id > temp_platform_ids(
            num_platforms, ::cl_platform_id{} );

//         #if defined( CL_HPP_ENABLE_EXCEPTIONS )
//         try
//         #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        {
            ret = ::clGetPlatformIDs( num_platforms,
                temp_platform_ids.data(), nullptr );
        }
//         #if defined( CL_HPP_ENABLE_EXCEPTIONS )
//         catch( cl::Error const& e )
//         {
//             st::OpenCL_ret_value_to_exception< std::runtime_error >( e.err(),
//                 "OclController", "GET_ALL_CL_PLATFORMS", e.what(),
//                     st_size_t{ __LINE__ } );
//
//             status = st::STATUS_GENERAL_FAILURE;
//         }
//         #else /* !defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        if( ret != CL_SUCCESS )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclController", "GET_ALL_CL_PLATFORMS", "",
                    st_size_t{ __LINE__ } );

            status = st::STATUS_GENERAL_FAILURE;
        }
//         #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */

        if( ( num_platforms > ::cl_uint{ 0 } ) &&
            ( status == st::STATUS_SUCCESS ) )
        {
            avail_platforms.reserve( num_platforms );

            for( auto const pid : temp_platform_ids )
            {
                avail_platforms.emplace_back( pid, true );
            }
        }

        return status;
    }

    st_status_t ocl_node_store_type::GET_CL_DEVICES_FOR_CL_PLATFORM(
        cl::Platform const& SIXTRL_RESTRICT_REF platform,
        std::vector< cl::Device >& SIXTRL_RESTRICT_REF devices,
        ::cl_device_type const only_devices_with_type_value )
    {
        st_status_t status = st::STATUS_SUCCESS;

        ::cl_platform_id const platform_id = platform();
        ::cl_uint num_devices = ::cl_uint{ 0 };
        ::cl_int ret = CL_SUCCESS;

        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        try
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        {
            ret = ::clGetDeviceIDs( platform_id, only_devices_with_type_value,
                ::cl_uint{ 0 }, nullptr, &num_devices );
            if( ret != CL_SUCCESS ) num_devices = ::cl_uint{ 0 };
        }
        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        catch( cl::Error const& e )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( e.err(),
                "OclNodeStore", "GET_CL_DEVICES_FOR_CL_PLATFORM", e.what(),
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #else /* !defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        if( CL_SUCCESS != ret )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclNodeStore", "GET_CL_DEVICES_FOR_CL_PLATFORM", "",
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */

        if( status != st::STATUS_SUCCESS ) return status;

        std::vector< ::cl_device_id > temp_device_ids(
            num_devices, ::cl_device_id{} );

        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        try
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        {
            ret = ::clGetDeviceIDs( platform_id, only_devices_with_type_value,
                num_devices, temp_device_ids.data(), nullptr );
            if( CL_SUCCESS != ret ) status = st::STATUS_GENERAL_FAILURE;
        }
        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        catch( cl::Error const& e )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( e.err(),
                "OclNodeStore", "GET_CL_DEVICES_FOR_CL_PLATFORM", e.what(),
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #else /* !defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        if( CL_SUCCESS != ret )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclNodeStore", "GET_CL_DEVICES_FOR_CL_PLATFORM", "",
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */

        if( ( num_devices >= ::cl_uint{ 0 } ) && ( ret == CL_SUCCESS ) &&
            ( status == st::STATUS_SUCCESS ) )
        {
            devices.reserve( devices.size() + num_devices );

            for( auto const dev_id : temp_device_ids )
                devices.emplace_back( dev_id, true );
        }

        return status;
    }

    st_status_t ocl_node_store_type::GET_NODE_DESCRIPTION_FROM_CL_DEVICE(
        cl::Device const& SIXTRL_RESTRICT_REF cl_device,
        std::string& SIXTRL_RESTRICT_REF device_description ) {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        device_description.clear();

        std::ostringstream a2str;
        ::cl_uint vendor_id = ::cl_uint{ 0 };
        ::cl_int ret = CL_SUCCESS;

        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        try
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        {
            ret = cl_device.getInfo( CL_DEVICE_VENDOR_ID, &vendor_id );
            status = st::STATUS_SUCCESS;
        }
        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        catch( cl::Error const& e )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( e.err(),
                "OclNodeStore", "GET_NODE_DESCRIPTION_FROM_CL_DEVICE", e.what(),
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #else /* !defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        if( CL_SUCCESS != ret )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclNodeStore", "GET_NODE_DESCRIPTION_FROM_CL_DEVICE", "",
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */

        if( ret != CL_SUCCESS ) status = st::STATUS_GENERAL_FAILURE;
        if( status != st::STATUS_SUCCESS ) return status;

        a2str << "vendor_id : " << std::hex << vendor_id << "\r\n" << std::dec;

        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        try
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        {
            std::string temp;
            ret = cl_device.getInfo( CL_DEVICE_EXTENSIONS, &temp );
            if( ( ret == CL_SUCCESS ) && ( !temp.empty() ) )
            {
                std::istringstream istr( temp );

                a2str << "extensions: \r\n";
                std::copy( std::istream_iterator< std::string >( istr ),
                           std::istream_iterator< std::string >(),
                           std::ostream_iterator< std::string >(
                            a2str, ",\r\n" ) );
            }
            else if( ret != CL_SUCCESS )
            {
                status = st::STATUS_GENERAL_FAILURE;
            }
        }
        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        catch( cl::Error const& e )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( e.err(),
                "OclNodeStore", "GET_NODE_DESCRIPTION_FROM_CL_DEVICE", e.what(),
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #else /* !defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        if( CL_SUCCESS != ret )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclNodeStore", "GET_NODE_DESCRIPTION_FROM_CL_DEVICE", "",
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */

        if( ret != CL_SUCCESS ) status = st::STATUS_GENERAL_FAILURE;
        if( status == st::STATUS_SUCCESS ) device_description = a2str.str();

        return status;
    }

    st_node_info_t ocl_node_store_type::CREATE_NODE_INFO_FOR_CL_DEVICE(
        cl::Platform const& SIXTRL_RESTRICT_REF platform,
        cl::Device const& SIXTRL_RESTRICT_REF device,
        st_platform_id_t const platform_id, st_device_id_t const device_id,
        st_node_index_t const node_index )
    {
        st_status_t status = st::STATUS_SUCCESS;

        std::string platform_name;
        std::string device_name;
        std::string description;
        ::cl_int ret = CL_SUCCESS;

        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        try
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        {
            ret = platform.getInfo( CL_PLATFORM_NAME, &platform_name );
        }
        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        catch( cl::Error const& e )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( e.err(),
                "OclNodeStore", "CREATE_NODE_INFO_FOR_CL_DEVICE", e.what(),
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #else /* !defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        if( CL_SUCCESS != ret )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclNodeStore", "CREATE_NODE_INFO_FOR_CL_DEVICE", "",
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */

        if( ret != CL_SUCCESS ) status = st::STATUS_GENERAL_FAILURE;
        if( status != st::STATUS_SUCCESS ) return st_node_info_t{};

        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        try
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        {
            ret = device.getInfo( CL_DEVICE_NAME, &device_name );
        }
        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        catch( cl::Error const& e )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( e.err(),
                "OclNodeStore", "CREATE_NODE_INFO_FOR_CL_DEVICE", e.what(),
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #else /* !defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        if( CL_SUCCESS != ret )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclNodeStore", "CREATE_NODE_INFO_FOR_CL_DEVICE", "",
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */

        if( ret != CL_SUCCESS ) status = st::STATUS_GENERAL_FAILURE;
        if( status != st::STATUS_SUCCESS ) return st_node_info_t{};

        status = ocl_node_store_type::GET_NODE_DESCRIPTION_FROM_CL_DEVICE(
            device, description );

        return ( status == st::STATUS_SUCCESS )
            ? st_node_info_t( platform_id, device_id, platform_name,
                              device_name, description )
            : st_node_info_t{};
    }

    st_status_t ocl_node_store_type::GET_ALL_AVAILABLE_NODES(
        std::vector< cl::Platform>& SIXTRL_RESTRICT_REF available_platforms,
        std::vector< cl::Device >&  SIXTRL_RESTRICT_REF available_devices,
        std::vector< st_node_id_t >* SIXTRL_RESTRICT available_node_ids,
        std::vector< node_info_type >* SIXTRL_RESTRICT available_node_infos ) {
        available_platforms.clear();
        available_devices.clear();

        st_status_t status = ocl_node_store_type::GET_ALL_CL_PLATFORMS(
            available_platforms );

        st_size_t ii = st_size_t{ 0 };
        st_size_t const NUM_PLATFORMS = available_platforms.size();

        std::vector< st_node_index_t > node_index_offset(
            NUM_PLATFORMS + st_size_t{ 1 }, st_node_index_t{ 0 } );

        while( ( status == st::STATUS_SUCCESS ) && ( ii < NUM_PLATFORMS ) )
        {
            node_index_offset[ ii ] = available_devices.size();

            status = ocl_node_store_type::GET_CL_DEVICES_FOR_CL_PLATFORM(
                available_platforms[ ii++ ], available_devices,
                    CL_DEVICE_TYPE_ALL );
        }

        node_index_offset[ NUM_PLATFORMS ] = available_devices.size();

        if( status != st::STATUS_SUCCESS ) return status;

        if( available_node_ids != nullptr )
        {
            available_node_ids->clear();
            available_node_ids->reserve( available_devices.size() );
        }

        if( available_node_infos != nullptr )
        {
            available_node_infos->clear();
            available_node_infos->reserve( available_devices.size() );
        }

        st_platform_id_t platform_id = st_platform_id_t{ 0 };

        for( st_size_t ii = 0u ; ii < NUM_PLATFORMS ; ++ii, ++platform_id )
        {
            st_device_id_t device_id = st_device_id_t{ 0 };
            st_node_index_t node_index = node_index_offset[ ii ];
            st_node_index_t node_index_end = node_index_offset[ ii + 1u ];

            for( ; node_index < node_index_end ; ++node_index, ++device_id )
            {
                if( available_node_ids != nullptr )
                {
                    SIXTRL_ASSERT( available_node_ids->size() == static_cast<
                        st_size_t >( node_index ) );

                    available_node_ids->emplace_back(
                        platform_id, device_id, node_index );
                }

                if( available_node_infos != nullptr )
                {
                    SIXTRL_ASSERT( available_node_infos->size() == static_cast<
                        st_size_t >( node_index ) );

                    available_node_infos->push_back(
                        ocl_node_store_type::CREATE_NODE_INFO_FOR_CL_DEVICE(
                            available_platforms[ ii ],
                                available_devices[ node_index ],
                                    platform_id, device_id, node_index ) );
                }
            }
        }

        return status;
    }

    st_status_t ocl_node_store_type::GET_ALLOWED_NODES_FROM_ENV_VARIABLE(
        char const* SIXTRL_RESTRICT env_var_name,
        std::vector< st_node_id_t >& SIXTRL_RESTRICT_REF node_ids ) {
        st_status_t status = st::STATUS_SUCCESS;

        node_ids.clear();
        char const* env_var_begin = nullptr;

        if( ( env_var_name != nullptr ) &&
            ( std::strlen( env_var_name ) > st::size_type{ 0 } ) )
        {
            env_var_begin = std::getenv( env_var_name );
        }
        else
        {
            env_var_begin = std::getenv( "SIXTRACKLIB_DEVICES" );
        }

        if( ( env_var_begin != nullptr ) &&
            ( std::strlen( env_var_begin ) > 0u ) )
        {
            std::string const in_str = env_var_begin;
            std::regex const regex_str( "\\s*,\\s*|\\s*;\\s*" );

            std::vector< std::string > const token_list(
                std::sregex_token_iterator( in_str.begin(), in_str.end(),
                    regex_str, -1 ),
                std::sregex_token_iterator() );

            for( auto const& token : token_list )
            {
                st::backend_id_type backend_id = st::BACKEND_ID_NONE;
                node_id_type::str_format_type const node_id_str_fmt =
                    node_id_type::GET_STR_FORMAT_TYPE( token, &backend_id );

                if( ( node_id_str_fmt == st::NODE_ID_STR_FORMAT_MINIMAL ) ||
                    ( ( node_id_str_fmt == st::NODE_ID_STR_FORMAT_BACKEND_ID ) &&
                      ( backend_id == st::BACKEND_ID_OPENCL ) ) ||
                    ( ( node_id_str_fmt == st::NODE_ID_STR_FORMAT_BACKEND_STR ) ||
                      ( backend_id == st::BACKEND_ID_OPENCL ) ) )
                {
                    node_ids.push_back(
                        node_id_type( token, node_id_str_fmt, nullptr ) );
                }
                else
                {
                    node_ids.clear();
                    status = st::STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }

        if( ( node_ids.empty() ) && ( status == st::STATUS_SUCCESS ) )
        {
            std::vector< cl::Platform > all_cl_platforms;
            std::vector< cl::Device > all_cl_devices;

            status = ocl_node_store_type::GET_ALL_AVAILABLE_NODES( all_cl_platforms,
                all_cl_devices, &node_ids, nullptr );
        }

        return status;
    }

    st_status_t ocl_node_store_type::GET_AVAILABLE_NODES(
        std::vector< st_node_id_t >& SIXTRL_RESTRICT_REF available_node_ids,
        std::vector< st_node_info_t >* SIXTRL_RESTRICT available_node_infos,
        std::vector< cl::Device >* SIXTRL_RESTRICT cl_devices,
        char const* SIXTRL_RESTRICT env_variable_name,
        char const* SIXTRL_RESTRICT SIXTRL_UNUSED( filter_str ) ) {
        available_node_ids.clear();
        if( available_node_infos != nullptr ) available_node_infos->clear();
        if( cl_devices != nullptr ) cl_devices->clear();

        std::vector< cl::Platform   > all_cl_platforms;
        std::vector< cl::Device     > all_cl_devices;
        std::vector< st_node_id_t   > all_node_ids;
        std::vector< st_node_info_t > all_node_infos;
        std::vector< st_node_id_t   > allowed_node_ids;

        st_status_t status = ocl_node_store_type::GET_ALL_AVAILABLE_NODES(
            all_cl_platforms, all_cl_devices, &all_node_ids, &all_node_infos );

        if( status == st::STATUS_SUCCESS ) {
            status = ocl_node_store_type::GET_ALLOWED_NODES_FROM_ENV_VARIABLE(
                env_variable_name, allowed_node_ids ); }

        if( status == st::STATUS_SUCCESS )
        {
            SIXTRL_ASSERT( all_cl_devices.size() == all_node_ids.size() );
            SIXTRL_ASSERT( all_cl_devices.size() == all_node_infos.size() );
            SIXTRL_ASSERT( allowed_node_ids.size() <= all_node_ids.size() );

            st_size_t const NN = all_node_ids.size();
            st_size_t const NUM_ALLOWED = allowed_node_ids.size();

            for( st_size_t ii = st_size_t{ 0 } ; ii < NN ; ++ii )
            {
                bool is_node_allowed = false;
                st_node_id_t& try_node_id = all_node_ids[ ii ];

                for( st_size_t jj = st_size_t{ 0 } ; jj < NUM_ALLOWED ; ++jj )
                {
                    if( try_node_id.compare( allowed_node_ids[ jj ], false ) == 0 )
                    {
                        is_node_allowed = true;
                        break;
                    }
                }

                if( is_node_allowed )
                {
                    try_node_id.set_index( static_cast< st_node_index_t >(
                        available_node_ids.size() ) );

                    SIXTRL_ASSERT( all_cl_devices.size() >
                                   available_node_ids.size() );

                    SIXTRL_ASSERT( all_cl_platforms.size() > static_cast<
                        st_size_t >( try_node_id.platform_id() ) );

                    available_node_ids.push_back( try_node_id );

                    if( available_node_infos != nullptr )
                    {
                        available_node_infos->push_back(
                            ocl_node_store_type::CREATE_NODE_INFO_FOR_CL_DEVICE(
                                all_cl_platforms[ try_node_id.platform_id() ],
                                all_cl_devices[ try_node_id.index() ],
                                try_node_id.platform_id(),
                                try_node_id.device_id(), try_node_id.index() ) );
                    }

                    if( cl_devices != nullptr ) cl_devices->emplace_back(
                        all_cl_devices[ try_node_id.index() ](), true );

                    SIXTRL_ASSERT( ( available_node_infos == nullptr ) ||
                        ( available_node_infos->size() ==
                            available_node_ids.size() ) );

                    SIXTRL_ASSERT( ( cl_devices == nullptr ) ||
                        ( cl_devices->size() == available_node_ids.size() ) );
                }
            }
        }

        return status;
    }

    /* ********************************************************************* */

    OclNodeStore::OclNodeStore() : st::BackendObjBase( st::BACKEND_ID_OPENCL,
        ocl_node_store_type::BASE_CLASS_ID, ocl_node_store_type::CLASS_ID ),
        m_platform_id_to_data_map(), m_node_ids(), m_node_infos()
    {
        st_status_t const status = this->_ocl_init_all_nodes();
        if( status != st::STATUS_SUCCESS )
            throw std::runtime_error( "unable to get cl::Platforms" );
    }

    st_size_t OclNodeStore::num_nodes() const SIXTRL_NOEXCEPT {
        return this->m_node_ids.size(); }

    st_size_t OclNodeStore::num_nodes(
        st_platform_id_t const pform_id ) const SIXTRL_NOEXCEPT {
        st_size_t num_nodes = st_size_t{ 0 };
        if( ( pform_id != st::NodeId::ILLEGAL_PLATFORM_ID ) &&
            ( !this->m_platform_id_to_data_map.empty() ) )
        {
            auto it = this->m_platform_id_to_data_map.find( pform_id );

            if( it != this->m_platform_id_to_data_map.end() )
            {
                SIXTRL_ASSERT( it->second.cl_devices.size() ==
                               it->second.node_indices.size() );

                num_nodes = it->second.cl_devices.size();
            }
        }
        return num_nodes;
    }

    st_node_index_t OclNodeStore::node_index( st_node_id_t const&
        SIXTRL_RESTRICT_REF node_id ) const SIXTRL_NOEXCEPT {
        return ( node_id.is_legal() )
            ? this->node_index( node_id.platform_id(), node_id.device_id() )
            : st::NodeId::ILLEGAL_INDEX; }

    st_node_index_t OclNodeStore::node_index( st_platform_id_t const platform_id,
        st_device_id_t const device_id ) const SIXTRL_NOEXCEPT {
        st_node_index_t node_idx = st::NodeId::ILLEGAL_INDEX;
        if( ( platform_id != st::NodeId::ILLEGAL_PLATFORM_ID ) &&
            ( device_id != st::NodeId::ILLEGAL_DEVICE_ID ) )
        {
            auto it = this->m_platform_id_to_data_map.find( platform_id );
            if( ( it != this->m_platform_id_to_data_map.end() ) &&
                ( static_cast< st_size_t >( device_id ) <
                  it->second.node_indices.size() ) )
            {
                SIXTRL_ASSERT( it->second.node_indices.size() ==
                               it->second.cl_devices.size() );

                node_idx = it->second.node_indices[ device_id ];

                SIXTRL_ASSERT( node_idx != st::NodeId::ILLEGAL_INDEX );
                SIXTRL_ASSERT( node_idx >= st_node_index_t{ 0 } );

                SIXTRL_ASSERT( this->m_node_ids.size() ==
                               this->m_node_infos.size() );

                SIXTRL_ASSERT( static_cast< st_size_t >( node_idx ) <
                               this->m_node_ids.size() );

                SIXTRL_ASSERT( this->m_node_ids[ node_idx ].has_index() );
                SIXTRL_ASSERT( this->m_node_ids[ node_idx ].index() == node_idx );

                SIXTRL_ASSERT( this->m_node_ids[ node_idx ].platform_id() ==
                               platform_id );

                SIXTRL_ASSERT( this->m_node_ids[ node_idx ].device_id() ==
                               device_id );
            }
        }
        return node_idx;
    }

    st_node_index_t const* OclNodeStore::node_indices_begin(
        st_platform_id_t const platform_id ) const SIXTRL_NOEXCEPT {
        st_node_index_t const* begin = nullptr;
        if( ( platform_id != st::NodeId::ILLEGAL_PLATFORM_ID ) &&
            ( !this->m_platform_id_to_data_map.empty() ) )
        {
            auto it = this->m_platform_id_to_data_map.find( platform_id );
            if( it != this->m_platform_id_to_data_map.end() )
            {
                SIXTRL_ASSERT( it->second.node_indices.size() ==
                               it->second.cl_devices.size() );

                begin = it->second.node_indices.data();
            }
        }
        return begin;
    }

    st_node_index_t const* OclNodeStore::node_indices_end(
        st_platform_id_t const platform_id ) const SIXTRL_NOEXCEPT {
        st_node_index_t const* ptr = this->node_indices_begin( platform_id );
        if( ptr != nullptr ) ptr = ptr + this->num_nodes( platform_id );
        return ptr;
    }

    bool OclNodeStore::has_platform_id(
        st_platform_id_t const platform_id ) const SIXTRL_NOEXCEPT {
        bool has_platform_id = false;
        if( ( platform_id != st::NodeId::ILLEGAL_PLATFORM_ID ) &&
            ( !this->m_platform_id_to_data_map.empty() ) &&
            ( !this->m_node_ids.empty() ) && ( !this->m_node_infos.empty() ) )
        {
            SIXTRL_ASSERT( this->m_node_ids.size() ==
                           this->m_node_infos.size() );

            auto it = this->m_platform_id_to_data_map.find(
                platform_id );

            has_platform_id = (
                ( it != this->m_platform_id_to_data_map.end() ) &&
                ( !it->second.node_indices.empty() ) );
        }
        return has_platform_id;
    }

    bool OclNodeStore::has_node_index(
        st_node_index_t const node_idx ) const SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( this->m_node_ids.size() == this->m_node_infos.size() );
        return ( ( node_idx != st::NodeId::ILLEGAL_INDEX ) &&
            ( node_idx >= st_node_index_t{ 0 } ) &&
            ( static_cast< st_size_t >( node_idx ) < this->m_node_ids.size() ) );
    }

    bool OclNodeStore::has_node_id( st_node_id_t const& SIXTRL_RESTRICT_REF
        node_id ) const SIXTRL_NOEXCEPT {
        return this->has_node_id( node_id.platform_id(), node_id.device_id() );
    }

    bool OclNodeStore::has_node_id( st_platform_id_t const platform_id,
        st_device_id_t const device_id ) const SIXTRL_NOEXCEPT {
        st_node_index_t const node_idx =
            this->node_index( platform_id, device_id );

        return ( ( this->has_node_index( node_idx ) ) &&
                 ( this->m_node_ids.size() == this->m_node_infos.size() ) &&
                 ( this->m_node_ids[ node_idx ].platform_id() == platform_id ) &&
                 ( this->m_node_ids[ node_idx ].device_id() == device_id ) &&
                 ( this->m_node_ids[ node_idx ].has_index() ) &&
                 ( this->m_node_ids[ node_idx ].index() == node_idx ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_node_id_t const& OclNodeStore::node_id(
        st_node_index_t const node_index ) const {
        if( ( node_index < st_node_index_t{ 0 } ) ||
            ( node_index == st::NodeId::ILLEGAL_INDEX ) )
            throw std::runtime_error( "node_index is illegal" );

        if( static_cast< st_size_t >( node_index ) >= this->m_node_ids.size() )
            throw std::runtime_error( "node_index out of bounds" );

        SIXTRL_ASSERT( this->m_node_ids.size() == this->m_node_ids.size() );
        SIXTRL_ASSERT( this->m_node_ids[ node_index ].has_index() );
        SIXTRL_ASSERT( this->m_node_ids[ node_index ].index() == node_index );
        SIXTRL_ASSERT( node_index == this->node_index(
            this->m_node_ids[ node_index ].platform_id(),
            this->m_node_ids[ node_index ].device_id() ) );

        return this->m_node_ids[ node_index ];
    }

    st_status_t OclNodeStore::node_ids(
        std::vector< st_node_id_t >& SIXTRL_RESTRICT_REF node_ids,
        st_platform_id_t const platform_id ) const SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        node_ids.clear();

        auto node_idx_it = this->node_indices_begin( platform_id );
        auto node_idx_end = this->node_indices_end( platform_id );

        if( ( node_idx_it != nullptr ) && ( node_idx_end != nullptr ) &&
            ( platform_id != st::NodeId::ILLEGAL_PLATFORM_ID ) )
        {
            status = st::STATUS_SUCCESS;

            SIXTRL_ASSERT( this->m_node_ids.size() ==
                           this->m_node_infos.size() );

            SIXTRL_ASSERT( reinterpret_cast< uintptr_t >( node_idx_it ) <=
                           reinterpret_cast< uintptr_t >( node_idx_end ) );

            for( ; node_idx_it != node_idx_end ; ++node_idx_it )
            {
                if( ( *node_idx_it == st::NodeId::ILLEGAL_INDEX ) ||
                    ( *node_idx_it < static_cast< st_node_index_t >( 0 ) ) ||
                    ( static_cast< st_size_t >( *node_idx_it ) >=
                      this->m_node_ids.size() ) )
                {
                    status = st::STATUS_GENERAL_FAILURE;
                    break;
                }

                if( ( !this->m_node_ids[ *node_idx_it ].is_legal() ) ||
                    ( !this->m_node_ids[ *node_idx_it ].has_index() )||
                    (  this->m_node_ids[ *node_idx_it ].index() ==
                       *node_idx_it ) ||
                    (  this->m_node_ids[ *node_idx_it ].platform_id() !=
                       platform_id ) )
                {
                    status = st::STATUS_GENERAL_FAILURE;
                    break;
                }

                node_ids.push_back( this->m_node_ids[ *node_idx_it ] );
            }
        }

        return status;
    }

    st_status_t OclNodeStore::node_ids(
        std::vector< st_node_id_t >& SIXTRL_RESTRICT_REF node_ids,
        st_node_index_t const* SIXTRL_RESTRICT node_indices_begin,
        st_size_t const num_node_indices ) const SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        node_ids.clear();

        if( ( node_indices_begin != nullptr ) &&
            ( num_node_indices > st_size_t{ 0 } ) )
        {
            status = st::STATUS_SUCCESS;

            SIXTRL_ASSERT( this->m_node_ids.size() ==
                           this->m_node_infos.size() );

            for( st_size_t ii = st_size_t{ 0 } ; ii < num_node_indices ; ++ii )
            {
                st_node_index_t const node_index = node_indices_begin[ ii ];

                if( ( node_index == st::NodeId::ILLEGAL_INDEX ) ||
                    ( node_index < static_cast< st_node_index_t >( 0 ) ) ||
                    ( static_cast< st_size_t >( node_index ) >=
                      this->m_node_ids.size() ) )
                {
                    status = st::STATUS_GENERAL_FAILURE;
                    break;
                }

                if( ( !this->m_node_ids[ node_index ].is_legal() ) ||
                    ( !this->m_node_ids[ node_index ].has_index() )||
                    (  this->m_node_ids[ node_index ].index() == node_index ) )
                {
                    status = st::STATUS_GENERAL_FAILURE;
                    break;
                }

                node_ids.push_back( this->m_node_ids[ node_index ] );
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    cl::Platform const& OclNodeStore::cl_platform(
        st_platform_id_t const platform_id ) const {
        if( ( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID ) ||
            ( this->m_platform_id_to_data_map.empty() ) )
            throw std::runtime_error( "illegal or not stored platform id" );

        SIXTRL_ASSERT( this->m_node_ids.size() == this->m_node_infos.size() );
        auto it = this->m_platform_id_to_data_map.find( platform_id );

        if( it == this->m_platform_id_to_data_map.end() )
            throw std::runtime_error( "platform not available" );

        SIXTRL_ASSERT( it->second.node_indices.size() ==
                       it->second.cl_devices.size() );

        return it->second.cl_platform;
    }

    cl::Device const& OclNodeStore::cl_device(
        st_node_id_t const& SIXTRL_RESTRICT_REF node_id ) const {
        return this->cl_device( node_id.platform_id(), node_id.device_id() );
    }

    cl::Device const& OclNodeStore::cl_device(
        st_platform_id_t const platform_id, st_device_id_t const device_id ) const
    {
        if( ( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID ) ||
            ( device_id == st::NodeId::ILLEGAL_DEVICE_ID ) )
            throw std::runtime_error( "illegal node_id" );

        if( this->m_platform_id_to_data_map.empty() )
            throw std::runtime_error( "no nodes stored" );

        auto it = this->m_platform_id_to_data_map.find( platform_id );

        if( it == this->m_platform_id_to_data_map.end() )
            throw std::runtime_error( "node_id not stored" );

        SIXTRL_ASSERT( this->m_node_ids.size() == this->m_node_infos.size() );
        SIXTRL_ASSERT( it->second.node_indices.size() ==
                       it->second.cl_devices.size() );

        if( ( device_id < st_device_id_t{ 0 } ) ||
            ( static_cast< st_size_t >( device_id ) >=
              it->second.cl_devices.size() ) )
            throw std::runtime_error( "node_id has illegal device_id" );

        SIXTRL_ASSERT( it->second.node_indices[ device_id ] !=
                       st::NodeId::ILLEGAL_INDEX );

        SIXTRL_ASSERT( it->second.node_indices[ device_id ] >=
                       st_node_index_t{ 0 } );

        SIXTRL_ASSERT( static_cast< st_size_t >( it->second.node_indices[
            device_id ] ) < this->m_node_ids.size() );

        SIXTRL_ASSERT( this->m_node_ids[ it->second.node_indices[ device_id ]
            ].platform_id() == platform_id );

        SIXTRL_ASSERT( this->m_node_ids[ it->second.node_indices[ device_id ]
            ].device_id() == device_id );

        SIXTRL_ASSERT( this->m_node_ids[ it->second.node_indices[
            device_id ] ].has_index()  );

        SIXTRL_ASSERT( it->second.node_indices[ device_id ] ==
            this->m_node_ids[ it->second.node_indices[ device_id ] ].index() );

        return it->second.cl_devices[ device_id ];
    }

    cl::Device const& OclNodeStore::cl_device(
        st_node_index_t const node_index ) const {

        if( ( node_index < st_node_index_t{ 0 } ) ||
            ( node_index == st::NodeId::ILLEGAL_INDEX ) )
            throw std::runtime_error( "node_index is illegal" );

        if( static_cast< st_size_t >( node_index ) >= this->m_node_ids.size() )
            throw std::runtime_error( "node_index out of bounds" );

        return this->cl_device( this->m_node_ids[ node_index ].platform_id(),
                                this->m_node_ids[ node_index ].device_id() );
    }

    std::vector< cl::Device > const&
    OclNodeStore::all_cl_devices( st_platform_id_t const platform_id ) const
    {
        if( ( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID ) ||
            ( this->m_platform_id_to_data_map.empty() ) )
            throw std::runtime_error( "illegal or not stored platform id" );

        SIXTRL_ASSERT( this->m_node_ids.size() == this->m_node_infos.size() );
        auto it = this->m_platform_id_to_data_map.find( platform_id );

        if( it == this->m_platform_id_to_data_map.end() )
            throw std::runtime_error( "platform not available" );

        SIXTRL_ASSERT( it->second.node_indices.size() ==
                       it->second.cl_devices.size() );

        return it->second.cl_devices;
    }

    st_status_t OclNodeStore::cl_devices(
        std::vector< cl::Device >& SIXTRL_RESTRICT_REF devices,
        st_node_index_t const* SIXTRL_RESTRICT node_indices_begin,
        st_size_t const num_devices ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        devices.clear();
        if( ( node_indices_begin != nullptr ) &&
            ( num_devices > st_size_t{ 0 } ) )
        {
            status = st::STATUS_SUCCESS;

            for( st_size_t ii = 0u ; ii < num_devices ; ++ii )
            {
                devices.push_back( cl::Device{} );
                devices.back() = this->cl_device( node_indices_begin[ ii ] );
            }
        }
        return status;
    }

    void OclNodeStore::do_clear() { this->_ocl_clear(); }

    void OclNodeStore::_ocl_clear() {
        this->m_platform_id_to_data_map.clear();
        this->m_node_ids.clear();
        this->m_node_infos.clear();
    }

    st_status_t OclNodeStore::_ocl_init_all_nodes(
        ::cl_device_type const only_type_of_device )
    {
        using store_type = st::OclNodeStore;
        std::vector< cl::Platform > all_cl_platforms;
        st_status_t status = store_type::GET_ALL_CL_PLATFORMS( all_cl_platforms );

        if( status != st::STATUS_SUCCESS )
            throw std::runtime_error( "unable to retrieve all platforms" );

        st_platform_id_t platform_id = 0;
        st_node_index_t node_index = st_node_index_t{ 0 };
        st_size_t num_stored_devices = st_size_t{ 0 };

        for( auto& cl_pform : all_cl_platforms )
        {
            store_type::OclPlatformData data;

            status = store_type::GET_CL_DEVICES_FOR_CL_PLATFORM(
                cl_pform, data.cl_devices, only_type_of_device );

            if( status != st::STATUS_SUCCESS ) break;
            if( data.cl_devices.empty() ) continue;

            st_device_id_t device_id = st_device_id_t{ 0 };
            st_size_t const NUM_DEVICES = data.cl_devices.size();

            for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_DEVICES ; ++ii )
            {
                data.node_indices.push_back( node_index );

                this->m_node_ids.emplace_back(
                    platform_id, device_id, node_index );

                this->m_node_infos.push_back(
                    store_type::CREATE_NODE_INFO_FOR_CL_DEVICE( cl_pform,
                        data.cl_devices[ ii ], platform_id, device_id++,
                            node_index++ ) );
            }

            num_stored_devices += data.node_indices.size();

            if( ( num_stored_devices != this->m_node_ids.size()   ) ||
                ( num_stored_devices != this->m_node_infos.size() ) )
            {
                status = st::STATUS_GENERAL_FAILURE;
                break;
            }

            auto ret = this->m_platform_id_to_data_map.emplace(
                std::make_pair( platform_id++, store_type::OclPlatformData{} ) );

            if( !ret.second )
            {
                status = st::STATUS_GENERAL_FAILURE;
                break;
            }

            data.cl_platform = std::move( cl_pform );

            auto it = ret.first;
            it->second = std::move( data );
        }

        return status;
    }
}
#endif /* C++, Host */
