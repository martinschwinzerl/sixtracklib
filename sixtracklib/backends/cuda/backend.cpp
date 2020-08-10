#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/backend.h"
    #include "sixtracklib/backends/cuda/dlib.h"
    #include "sixtracklib/backends/cuda/plugin/cuda_tools.h"
    #include "sixtracklib/backends/cuda/plugin/node.h"
    #include "sixtracklib_base/generated/namespace.h"
    #include "sixtracklib_base/backend/backends_store.h"
    #include "sixtracklib_base/backend/dlib_loader.h"
    #include "sixtracklib_base/backend/dlib_loader_posix.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <toml.hpp>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using this_t = st::CudaBackend;
        using base_t = st::BaseNodeBackend;
        using st_status_t = this_t::status_t;
    }

    this_t::CudaBackend() :
        base_t( st::BACKEND_CUDA, SIXTRL_BACKEND_CUDA_STR )
    {
        /* ------------------------------------------------------------------ */
        /* build path to dynamic library plugin */
        this_t::fs_sstream_t a2str;

        #if defined( SIXTRL_CUDA_PLUGIN_PATH_PREFIX )
        a2str << SIXTRL_CUDA_PLUGIN_PATH_PREFIX;
        #endif /* defined( SIXTRL_CUDA_PLUGIN_PATH_PREFIX ) */

        #if defined( SIXTRL_CUDA_PLUGIN_FILENAME )
        a2str << SIXTRL_CUDA_PLUGIN_FILENAME;
        #else /* !defined( SIXTRL_CUDA_PLUGIN_FILENAME ) */
        a2str << "libsixtrack_cuda.so";
        #endif /* defined( SIXTRL_CUDA_PLUGIN_FILENAME ) */

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* Initilize the dynamic library loader */
        /* TODO: Handle platforms / OSes different than POSIX */

        #if defined( _POSIX_VERSION )
        this->dynamic_library_loader().reset(
            new st::PosixDynLibLoader( a2str.str() ) );

        SIXTRL_ASSERT(  this->dynamic_library_loader().get() != nullptr );
        SIXTRL_ASSERT(  this->ptr_base_dynamic_library_loader() != nullptr );
        SIXTRL_ASSERT(  this->ptr_base_dynamic_library_loader(
                            )->has_path_to_dynamic_lib() );
        SIXTRL_ASSERT(  this->has_dynamic_library_loader() );
        SIXTRL_ASSERT( !this->has_dynamic_library_handle() );
        #endif /* _POSIX_VERSION */

        /* ------------------------------------------------------------------ */
        /* assign symbol names to all required and optional symbols */

        st_status_t status = st::STATUS_SUCCESS;

        status |= this->set_symbol_name( this_t::SYMBOL_ID_INIT_BACKEND,
            "Cuda_plugin_init", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_SHUTDOWN_BACKEND,
            "Cuda_plugin_finish", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_CREATE_NODE_INFO,
            "CudaNodeInfo_create", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_DELETE_NODE_INFO,
            "CudaNodeInfo_delete", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_GET_TOTAL_NUM_NODES,
            "Cuda_num_all_nodes", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR  );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_GET_ALL_NODE_IDS,
            "Cuda_all_node_ids", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR  );

        /* ------------------------------------------------------------------ */

        #if defined( SIXTRL_CUDA_ALLOWED_DEVICES_ENV_VARIABLE )
        if( ( SIXTRL_CUDA_ALLOWED_DEVICES_ENV_VARIABLE != nullptr ) &&
            ( std::strlen( SIXTRL_CUDA_ALLOWED_DEVICES_ENV_VARIABLE ) >
                st_size_t{ 0 } ) )
        {
            this->set_allowed_node_ids_env_var_name(
                SIXTRL_CUDA_ALLOWED_DEVICES_ENV_VARIABLE );
        }
        #endif /* defined( SIXTRL_CUDA_ALLOWED_DEVICES_ENV_VARIABLE ) */
    }

    st_status_t this_t::do_make_ready()
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        st_size_t const total_nnodes =
            ( this->m_get_total_num_nodes_fn != nullptr )
                ? this->m_get_total_num_nodes_fn() : st_size_t{ 0 };

        if( ( this->is_available() ) &&
            ( this->has_nodes() ) && ( this->has_dynamic_library_loader() ) &&
            ( total_nnodes > st_size_t{ 0 } ) &&
            ( this->m_get_all_node_ids_fn != nullptr ) &&
            ( this->m_create_node_info_fn != nullptr ) &&
            ( this->m_delete_node_info_fn != nullptr ) &&
            ( base_t::do_make_ready() == st::STATUS_SUCCESS ) )
        {
            SIXTRL_ASSERT( this->backend_id() != st::BACKEND_ILLEGAL );
            SIXTRL_ASSERT( this->backend_id() != st::BACKEND_UNDEFINED );

            std::vector< ::NS(NodeId) > node_ids_to_test( total_nnodes,
                this_t::c_node_id_t{ st::BACKEND_ILLEGAL,
                st::NODE_ILLEGAL_PLATFORM_ID, st::NODE_ILLEGAL_DEVICE_ID } );

            st_size_t const nnodes = this->m_get_all_node_ids_fn(
                node_ids_to_test.data(), node_ids_to_test.size() );
            SIXTRL_ASSERT( nnodes <= total_nnodes );

            if( nnodes > st_size_t{ 0 } )
            {
                for( auto const& t : node_ids_to_test )
                {
                    this_t::platform_id_t const platform_id = t.m_platform_id;
                    this_t::device_id_t const device_id = t.m_device_id;

                    if( ( t.m_backend_id != this->backend_id() ) ||
                        ( platform_id == st::NODE_ILLEGAL_PLATFORM_ID ) ||
                        ( device_id == st::NODE_ILLEGAL_DEVICE_ID ) )
                    {
                        continue;
                    }

                    /* Check if t is in list of allowed nodes or
                    * if the list is empty */
                    if( ( this->limits_allowed_node_ids() ) &&
                        ( std::find( this->allowed_c_node_ids_begin(),
                                    this->allowed_c_node_ids_end(), t ) ==
                                    this->allowed_c_node_ids_end() ) )
                    {
                        continue;
                    }

                    status = this->add_available_node_info(
                        this->create_node_info( platform_id, device_id ) );

                    if( status != st::STATUS_SUCCESS )
                    {
                        status = this->remove_available_node_info( t );
                    }

                    if( status != st::STATUS_SUCCESS ) break;
                }

                if( status == st::STATUS_SUCCESS )
                {
                    status = this->rebuild_internal_lists();
                }

                if( ( status == st::STATUS_SUCCESS ) &&
                    ( this->num_available_nodes() == st_size_t{ 0 } ) )
                {
                    status = st::STATUS_GENERAL_FAILURE;
                }
            }
        }

        return status;
    }

    /* ******************************************************************** */

    CudaBackend* Cuda_init_backend()
    {
        CudaBackend* cuda_backend = nullptr;
        st::BackendsStore& be_store = st::BackendsStore_global();

        if( ( ( be_store.has_backend( st::BACKEND_CUDA ) ) ||
              ( st::STATUS_SUCCESS == be_store.add_backend(
                std::unique_ptr< CudaBackend >( new CudaBackend ) ) ) ) &&
            ( be_store.init_backend( st::BACKEND_CUDA ) ==
                st::STATUS_SUCCESS ) )
        {
            auto temp_be = be_store.backend( st::BACKEND_CUDA );
            if( temp_be != nullptr )
            {
                SIXTRL_ASSERT( temp_be->backend_id() == st::BACKEND_CUDA );
                SIXTRL_ASSERT( temp_be->has_dynamic_library_loader() );
                SIXTRL_ASSERT( temp_be->has_nodes() );
                cuda_backend = static_cast< CudaBackend* >( temp_be );
            }
        }

        return cuda_backend;
    }

    CudaBackend* Cuda_init_backend_with_config_file(
        CudaBackend::fs_string_type const& SIXTRL_RESTRICT_REF path_to_conf )
    {
        CudaBackend* cuda_backend = nullptr;
        st::BackendsStore& be_store = st::BackendsStore_global();

        if( ( ( be_store.has_backend( st::BACKEND_CUDA ) ) ||
              ( st::STATUS_SUCCESS == be_store.add_backend(
                std::unique_ptr< CudaBackend >( new CudaBackend ) ) ) ) &&
            ( be_store.init_backend_with_config_file(
                st::BACKEND_CUDA, path_to_conf ) == st::STATUS_SUCCESS ) )
        {
            auto temp_be = be_store.backend( st::BACKEND_CUDA );
            if( temp_be != nullptr )
            {
                SIXTRL_ASSERT( temp_be->backend_id() == st::BACKEND_CUDA );
                SIXTRL_ASSERT( temp_be->has_dynamic_library_loader() );
                SIXTRL_ASSERT( temp_be->has_nodes() );
                cuda_backend = static_cast< CudaBackend* >( temp_be );
            }
        }

        return cuda_backend;
    }

    CudaBackend* Cuda_init_backend_with_config_string(
        CudaBackend::string_type const& SIXTRL_RESTRICT_REF config_string )
    {
        CudaBackend* cuda_backend = nullptr;
        st::BackendsStore& be_store = st::BackendsStore_global();

        if( ( ( be_store.has_backend( st::BACKEND_CUDA ) ) ||
              ( st::STATUS_SUCCESS == be_store.add_backend(
                std::unique_ptr< CudaBackend >( new CudaBackend ) ) ) ) &&
            ( be_store.init_backend_with_config( st::BACKEND_CUDA,
                config_string ) == st::STATUS_SUCCESS ) )
        {
            auto temp_be = be_store.backend( st::BACKEND_CUDA );
            if( temp_be != nullptr )
            {
                SIXTRL_ASSERT( temp_be->backend_id() == st::BACKEND_CUDA );
                SIXTRL_ASSERT( temp_be->has_dynamic_library_loader() );
                SIXTRL_ASSERT( temp_be->has_nodes() );
                cuda_backend = static_cast< CudaBackend* >( temp_be );
            }
        }

        return cuda_backend;
    }

} /* ns: SIXTRL_CXX_NAMESPACE */

::NS(CudaBackend)* NS(Cuda_init_backend)( void ) {
    return SIXTRL_CXX_NAMESPACE::Cuda_init_backend(); }

NS(CudaBackend)* NS(Cuda_init_backend_with_config_file)(
    char const* SIXTRL_RESTRICT path_to_conf ) {
    return ( path_to_conf != nullptr )
        ? SIXTRL_CXX_NAMESPACE::Cuda_init_backend_with_config_file(
            path_to_conf )
        : SIXTRL_CXX_NAMESPACE::Cuda_init_backend();
}

SIXTRL_EXPORT_API SIXTRL_HOST_FN
NS(CudaBackend)* NS(Cuda_init_backend_with_config_string)(
    char const* SIXTRL_RESTRICT config_string ) {
    return ( config_string != nullptr )
        ? SIXTRL_CXX_NAMESPACE::Cuda_init_backend_with_config_string(
            config_string )
        : SIXTRL_CXX_NAMESPACE::Cuda_init_backend();
}

#endif /* C++, Host */
