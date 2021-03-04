#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/control/controller.h"
    #include "sixtracklib/opencl/control/context.h"
    #include "sixtracklib/opencl/control/cmd_queue.h"
    #include "sixtracklib/opencl/internal/helpers.h"
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
        using ocl_ctrl_type       = st::OclController;
        using ocl_prog_store_type = ocl_ctrl_type::program_store_type;
        using ocl_context_type    = ocl_ctrl_type::context_type;
        using ocl_cmd_queue_type  = ocl_ctrl_type::cmd_queue_type;
        using st_node_id_t        = ocl_ctrl_type::node_id_type;
        using st_node_info_t      = ocl_ctrl_type::node_info_type;
        using st_status_t         = ocl_ctrl_type::status_type;
        using st_size_t           = ocl_ctrl_type::size_type;
        using st_platform_id_t    = ocl_ctrl_type::platform_id_type;
        using st_device_id_t      = ocl_ctrl_type::device_id_type;
        using st_node_index_t     = ocl_ctrl_type::node_index_type;
    }

    constexpr ocl_ctrl_type::class_id_type ocl_ctrl_type::CLASS_ID;

    constexpr ocl_ctrl_type::backend_id_type
    st::BackendObjTraits< ocl_ctrl_type >::BACKEND_ID;

    constexpr ocl_ctrl_type::class_id_type
    st::BackendObjTraits< ocl_ctrl_type >::BASE_CLASS_ID;

    constexpr ocl_ctrl_type::class_id_type
    st::BackendObjTraits< ocl_ctrl_type >::DERIVED_CLASS_ID;

    /* --------------------------------------------------------------------- */

    st_status_t ocl_ctrl_type::GET_ALL_CL_PLATFORMS(
        std::vector< cl::Platform >& SIXTRL_RESTRICT_REF avail_platforms ) {
        st_status_t status = st::STATUS_SUCCESS;

        avail_platforms.clear();

        ::cl_uint num_platforms = ::cl_uint{ 0 };
        ::cl_int ret = ::clGetPlatformIDs(
            ::cl_uint{ 0 }, nullptr, &num_platforms );

        if( ret != CL_SUCCESS )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclController", "GET_ALL_CL_PLATFORMS", "",
                    st_size_t{ __LINE__ } );

            status = st::STATUS_GENERAL_FAILURE;
        }

        if( num_platforms == ::cl_uint{ 0 } )
        {
            status = st::STATUS_GENERAL_FAILURE;
            throw std::runtime_error( "no OpenCL platforms found" );
        }

        std::vector< ::cl_platform_id > temp_platform_ids(
            num_platforms, ::cl_platform_id{} );

        ret = ::clGetPlatformIDs(
            num_platforms, temp_platform_ids.data(), nullptr );

        if( ret != CL_SUCCESS )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclController", "GET_ALL_CL_PLATFORMS", "",
                    st_size_t{ __LINE__ } );

            status = st::STATUS_GENERAL_FAILURE;
        }

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

    st_status_t ocl_ctrl_type::GET_CL_DEVICES_FOR_CL_PLATFORM(
        cl::Platform const& SIXTRL_RESTRICT_REF platform,
        std::vector< cl::Device >& SIXTRL_RESTRICT_REF avail_devices,
        ::cl_device_type const only_devices_with_type_value ) {
        st_status_t status = st::STATUS_SUCCESS;

        ::cl_platform_id const platform_id = platform();
        ::cl_uint num_devices = ::cl_uint{ 0 };

        ::cl_int ret = :: clGetDeviceIDs( platform_id,
            only_devices_with_type_value, ::cl_uint{ 0 }, nullptr, &num_devices);

        if( ( ret != CL_SUCCESS ) && ( ret != CL_DEVICE_NOT_FOUND ) )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclController", "GET_CL_DEVICES_FOR_CL_PLATFORM", "",
                    st_size_t{ __LINE__ } );

            status = st::STATUS_GENERAL_FAILURE;
        }
        else if( ret == CL_DEVICE_NOT_FOUND )
        {
            num_devices = ::cl_uint{ 0 };
        }

        if( ( num_devices > ::cl_uint{ 0 } ) && ( ret == CL_SUCCESS ) )
        {
            avail_devices.reserve( avail_devices.size() + num_devices );

            std::vector< ::cl_device_id > temp_device_ids(
                num_devices, ::cl_device_id{} );

            ret = :: clGetDeviceIDs( platform_id, only_devices_with_type_value,
                num_devices, temp_device_ids.data(), nullptr );

            if( ret == CL_SUCCESS )
            {
                for( auto const dev_id : temp_device_ids )
                {
                    avail_devices.emplace_back( dev_id, true );
                }
            }
            else
            {
                st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                    "OclController", "GET_CL_DEVICES_FOR_CL_PLATFORM", "",
                        st_size_t{ __LINE__ } );
            }
        }

        return status;
    }

    st_status_t ocl_ctrl_type::GET_NODE_DESCRIPTION_FROM_CL_DEVICE(
        cl::Device const& SIXTRL_RESTRICT_REF cl_device,
        std::string& SIXTRL_RESTRICT_REF device_description ) {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        std::ostringstream a2str;
        ::cl_uint vendor_id = ::cl_uint{ 0 };
        ::cl_int ret = cl_device.getInfo( CL_DEVICE_VENDOR_ID, &vendor_id );

        if( ret == CL_SUCCESS )
        {
            a2str << "vendor_id : " << std::hex << vendor_id << "\r\n"
                  << std::dec;
            status = st::STATUS_SUCCESS;
        }
        else
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclController", "GET_NODE_DESCRIPTION_FROM_CL_DEVICE", "",
                    st_size_t{ __LINE__ } );
        }

        if( status == st::STATUS_SUCCESS )
        {
            std::string temp;
            ret = cl_device.getInfo( CL_DEVICE_EXTENSIONS, &temp );
            if( ( ret == CL_SUCCESS ) && ( !temp.empty() ) )
            {
                a2str << "extensions: \r\n";
                std::istringstream istr( temp );
                std::copy( std::istream_iterator< std::string >( istr ),
                           std::istream_iterator< std::string >(),
                           std::ostream_iterator< std::string >(
                            a2str, ",\r\n" ) );
            }
        }

        return status;
    }

    st_node_info_t ocl_ctrl_type::CREATE_NODE_INFO_FOR_CL_DEVICE(
        cl::Platform const& SIXTRL_RESTRICT_REF platform,
        cl::Device const& SIXTRL_RESTRICT_REF device,
        st_platform_id_t const platform_id, st_device_id_t const device_id,
        st_node_index_t const node_index ) {
        std::string platform_name;
        std::string device_name;
        std::string description;

        ::cl_int ret = platform.getInfo( CL_PLATFORM_NAME, &platform_name );

        if( CL_SUCCESS == ret )
        {
            ret = device.getInfo( CL_DEVICE_NAME, &device_name );

            if( ret != CL_SUCCESS )
            {
                st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                    "OclController", "CREATE_NODE_INFO_FOR_CL_DEVICE", "",
                        st_size_t{ __LINE__ } );
            }
        }
        else
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclController", "CREATE_NODE_INFO_FOR_CL_DEVICE", "",
                    st_size_t{ __LINE__ } );
        }

        if( ocl_ctrl_type::GET_NODE_DESCRIPTION_FROM_CL_DEVICE(
                device, description ) != st::STATUS_SUCCESS )
        {
            throw std::runtime_error( "error during creating device description" );
        }

        return st_node_info_t( platform_id, device_id, platform_name,
            device_name, description );
    }

    st_status_t ocl_ctrl_type::GET_ALL_AVAILABLE_NODES(
        std::vector< cl::Platform>& SIXTRL_RESTRICT_REF available_platforms,
        std::vector< cl::Device >&  SIXTRL_RESTRICT_REF available_devices,
        std::vector< st_node_id_t >* SIXTRL_RESTRICT available_node_ids,
        std::vector< node_info_type >* SIXTRL_RESTRICT available_node_infos ) {
        available_platforms.clear();
        available_devices.clear();

        st_status_t status = ocl_ctrl_type::GET_ALL_CL_PLATFORMS(
            available_platforms );

        st_size_t ii = st_size_t{ 0 };
        st_size_t const NUM_PLATFORMS = available_platforms.size();

        std::vector< st_node_index_t > node_index_offset(
            NUM_PLATFORMS + st_size_t{ 1 }, st_node_index_t{ 0 } );

        while( ( status == st::STATUS_SUCCESS ) && ( ii < NUM_PLATFORMS ) )
        {
            node_index_offset[ ii ] = available_devices.size();

            status = ocl_ctrl_type::GET_CL_DEVICES_FOR_CL_PLATFORM(
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
                        ocl_ctrl_type::CREATE_NODE_INFO_FOR_CL_DEVICE(
                            available_platforms[ ii ],
                                available_devices[ node_index ],
                                    platform_id, device_id, node_index ) );
                }
            }
        }

        return status;
    }

    st_status_t ocl_ctrl_type::GET_ALLOWED_NODES_FROM_ENV_VARIABLE(
        char const* SIXTRL_RESTRICT env_var_name,
        std::vector< st_node_id_t >& SIXTRL_RESTRICT_REF node_ids ) {
        st::status_type status = st::STATUS_SUCCESS;

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

            status = ocl_ctrl_type::GET_ALL_AVAILABLE_NODES( all_cl_platforms,
                all_cl_devices, &node_ids, nullptr );
        }

        return status;
    }

    ocl_ctrl_type::status_type ocl_ctrl_type::GET_AVAILABLE_NODES(
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

        st::status_type status = ocl_ctrl_type::GET_ALL_AVAILABLE_NODES(
            all_cl_platforms, all_cl_devices, &all_node_ids, &all_node_infos );

        if( status == st::STATUS_SUCCESS ) {
            status = ocl_ctrl_type::GET_ALLOWED_NODES_FROM_ENV_VARIABLE(
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
                            ocl_ctrl_type::CREATE_NODE_INFO_FOR_CL_DEVICE(
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

    /* --------------------------------------------------------------------- */

    ocl_ctrl_type::OclController(
        node_id_type const& SIXTRL_RESTRICT_REF node_id,
        ocl_context_type& SIXTRL_RESTRICT_REF context,
        std::shared_ptr< ocl_prog_store_type >& SIXTRL_RESTRICT_REF prog_store ) :
        st::ControllerBase( st::BACKEND_ID_OPENCL, ocl_ctrl_type::CLASS_ID ),
        m_selected_node_id(),
        m_kernel_names(),
        m_kernel_name_to_id_map(),
        m_kernels(),
        m_cmd_queues(),
        m_program_store( nullptr ),
        m_context( context ),
        m_selected_cl_platform(),
        m_selected_cl_device()
    {
        if( !this->m_context.key().is_legal() )
        {
            throw std::runtime_error( "illegal context supplied" );
        }

        if( !node_id.is_legal() )
        {
            throw std::runtime_error( "illegal node_id supplied" );
        }

        if( !this->m_context.key().contains_node_id( node_id ) )
        {
            throw std::runtime_error( "node_id and context mismatch" );
        }

        if( prog_store.get() != nullptr )
        {
            this->m_program_store = prog_store;
        }
        else
        {
            this->m_program_store = std::make_shared< ocl_prog_store_type >();
        }

        this->m_selected_node_id = node_id;
        this->m_selected_node_id.set_index(
            this->m_context.node_index_for_node_id( node_id ) );

        this->m_cmd_queues.emplace_back(
            new ocl_cmd_queue_type( this->m_context ) );
    }

    ocl_ctrl_type::size_type ocl_ctrl_type::num_cmd_queues() const SIXTRL_NOEXCEPT
    {
        return this->m_cmd_queues.size();
    }

    ocl_cmd_queue_type* ocl_ctrl_type::ptr_cmd_queue(
        st_size_t const id ) SIXTRL_NOEXCEPT {
        return ( this->m_cmd_queues.size() > id )
            ? this->m_cmd_queues[ id ].get() : nullptr;
    }

    ocl_cmd_queue_type const* ocl_ctrl_type::ptr_cmd_queue(
        st_size_t const id ) const SIXTRL_NOEXCEPT {
        return ( this->m_cmd_queues.size() > id )
            ? this->m_cmd_queues[ id ].get() : nullptr;
    }

    ocl_cmd_queue_type& ocl_ctrl_type::cmd_queue( st_size_t const id ) {
        auto ptr = this->ptr_cmd_queue( id );

        if( ptr == nullptr )
        {
            throw std::runtime_error( "no legal cmd_queue available for id" );
        }

        return *ptr;
    }

    ocl_cmd_queue_type const& ocl_ctrl_type::cmd_queue(
        st_size_t const id ) const {
        auto ptr = this->ptr_cmd_queue( id );

        if( ptr == nullptr )
        {
            throw std::runtime_error( "no legal cmd_queue available for id" );
        }

        return *ptr;
    }

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
