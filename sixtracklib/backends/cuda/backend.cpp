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
        using be_symb_id_t = this_t::be_symbol_id_t;
    }

    constexpr be_symb_id_t this_t::SYMBOL_ID_NODE_ID_CREATE_DEV_HANDLE;
    constexpr be_symb_id_t this_t::SYMBOL_ID_NODE_ID_GET_DEV_HANDLE;
    constexpr be_symb_id_t this_t::SYMBOL_ID_NODE_ID_SET_DEV_HANDLE;
    constexpr be_symb_id_t this_t::SYMBOL_ID_CTX_CREATE;
    constexpr be_symb_id_t this_t::SYMBOL_ID_CTX_INIT;
    constexpr be_symb_id_t this_t::SYMBOL_ID_CTX_INIT_AS_PRIMARY;
    constexpr be_symb_id_t this_t::SYMBOL_ID_CTX_INIT_AS_EXT_SHARED;
    constexpr be_symb_id_t this_t::SYMBOL_ID_CTX_DELETE;
    constexpr be_symb_id_t this_t::SYMBOL_ID_CTX_GET_NODE_ID;

    /* ********************************************************************* */

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

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* node-id: */

        status |= this->set_symbol_name( this_t::SYMBOL_ID_CREATE_NODE_ID,
            "CudaNodeId_create", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name(
            this_t::SYMBOL_ID_CREATE_NODE_ID_FROM_STRING,
            "CudaNodeId_create_from_string",
            this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name(
            this_t::SYMBOL_ID_CREATE_NODE_ID_FROM_STRING_DETAILED,
            "CudaNodeId_create_from_string_detailed",
            this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name(
            this_t::SYMBOL_ID_NODE_ID_CREATE_DEV_HANDLE,
            "CudaNodeId_create_from_device_handle",
            this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name(
            this_t::SYMBOL_ID_NODE_ID_GET_DEV_HANDLE,
            "CudaNodeId_device_handle",
            this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name(
            this_t::SYMBOL_ID_NODE_ID_SET_DEV_HANDLE,
            "CudaNodeId_set_device_handle",
            this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* node-info */

        status |= this->set_symbol_name( this_t::SYMBOL_ID_CREATE_NODE_INFO,
            "CudaNodeInfo_create", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_GET_TOTAL_NUM_NODES,
            "Cuda_num_all_nodes", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR  );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_GET_ALL_NODE_IDS,
            "Cuda_all_node_ids", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR  );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* Context */

        status |= this->set_symbol_name( this_t::SYMBOL_ID_CTX_GET_CURRENT,
            "CudaContext_current_ctx",
            this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_CTX_SET_CURRENT,
            "CudaContext_set_current_ctx",
            this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_CTX_CREATE,
            "CudaContext_create", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_CTX_DELETE,
            "Context_delete", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_CTX_INIT,
            "CudaContext_init", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_CTX_INIT_AS_PRIMARY,
            "CudaContext_init_as_primary",
            this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name(
            this_t::SYMBOL_ID_CTX_INIT_AS_EXT_SHARED,
            "CudaContext_init_as_ext_shared",
            this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

        status |= this->set_symbol_name( this_t::SYMBOL_ID_CTX_GET_NODE_ID,
            "CudaContext_node_id", this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR );

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

    /* --------------------------------------------------------------------- */

    this_t::managed_base_node_id_t this_t::create_node_id(
        st::CudaNodeId::device_handle_type const handle )
    {
        if( this->m_delete_node_id_fn == nullptr )
        {
            throw std::runtime_error( "delete_node_id_fn symbol required!" );
        }

        this_t::managed_base_node_id_t ptr_node_id{
                nullptr, this->m_delete_node_id_fn };

        if( ( this->m_node_id_create_from_dev_handle_fn != nullptr ) &&
            ( handle != st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE ) )
        {
            ptr_node_id.reset(
                this->m_node_id_create_from_dev_handle_fn( handle ) );
        }

        return ptr_node_id;
    }

    /* --------------------------------------------------------------------- */

    bool this_t::has_context(
        this_t::node_id_type const& SIXTRL_RESTRICT_REF node_id ) const
    {
        return this->has_context( node_id, this->create_lock() );
    }

    bool this_t::has_context(
        this_t::node_id_type const& SIXTRL_RESTRICT_REF node_id,
        this_t::guard_type const& SIXTRL_RESTRICT_REF
            lock ) const SIXTRL_NOEXCEPT
    {
        bool has_ctx = false;

        if( ( this->is_locked( lock ) ) && ( node_id.is_legal() ) &&
            ( this->is_ready() ) &&
            ( this->m_node_id_dev_handle_fn != nullptr ) )
        {
            auto it = this->m_context_store.find(
                this->m_node_id_dev_handle_fn(
                    st::CudaNodeId_get( &node_id ) ) );

            if( it != this->m_context_store.end() )
            {
                has_ctx = ( ( it->second.get() != nullptr ) &&
                            ( it->second->backend_id() == st::BACKEND_CUDA ) &&
                            ( it->second->is_active() ) );
            }
        }

        return has_ctx;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    this_t::managed_ctx_t this_t::init_context(
        this_t::node_id_type const& SIXTRL_RESTRICT_REF node_id,
        this_t::context_type::flags_type const create_flags ) {
        return this->init_context( node_id, create_flags,
            this->create_lock() );
    }

    this_t::managed_ctx_t this_t::init_context(
        this_t::node_id_type const& SIXTRL_RESTRICT_REF node_id,
        this_t::context_type::flags_type const create_flags,
        this_t::guard_type const& SIXTRL_RESTRICT_REF lock ) {

        if( ( this->is_ready() ) && ( node_id.is_legal() ) &&
            ( this->m_ctx_create_fn != nullptr ) &&
            ( this->m_ctx_delete_fn != nullptr ) &&
            ( this->m_ctx_init_fn   != nullptr ) &&
            ( this->m_ctx_get_node_id_fn != nullptr ) &&
            ( this->m_node_id_dev_handle_fn != nullptr ) )
        {
            ::NS(cuda_device_handle_type) const dev_handle =
                this->m_node_id_dev_handle_fn( st::CudaNodeId_get( &node_id ) );

            auto it =  this->m_context_store.find( dev_handle );
            if(  it == this->m_context_store.end() )
            {
                st::ThreadId const current_tid;
                this_t::managed_ctx_t ctx{ this->m_ctx_create_fn(
                        &current_tid ), this->m_ctx_delete_fn };

                if( st::STATUS_SUCCESS != this->m_ctx_init_fn( ctx.get(),
                        &node_id, create_flags, &lock ) ) ctx.reset();

                if( ctx.get() != nullptr )
                {
                    auto ret = this->m_context_store.emplace(
                            std::make_pair( dev_handle, ctx ) );
                    if( ret.second ) return ret.first->second;
                }

                return ctx;
            }
        }

        return this_t::managed_ctx_t{ nullptr };
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    this_t::managed_ctx_t this_t::init_context_as_primary(
        this_t::node_id_type const& SIXTRL_RESTRICT_REF node_id,
        this_t::context_type::flags_type const create_flags )
    {
        return this->init_context_as_primary( node_id, create_flags,
            this->create_lock() );
    }

    this_t::managed_ctx_t this_t::init_context_as_primary(
        this_t::node_id_type const& SIXTRL_RESTRICT_REF node_id,
        this_t::context_type::flags_type const create_flags,
        this_t::guard_type const& SIXTRL_RESTRICT_REF lock )
    {
        if( ( this->is_ready() ) && ( node_id.is_legal() ) &&
            ( this->m_ctx_create_fn != nullptr ) &&
            ( this->m_ctx_delete_fn != nullptr ) &&
            ( this->m_ctx_init_primary_fn   != nullptr ) &&
            ( this->m_ctx_get_node_id_fn    != nullptr ) &&
            ( this->m_node_id_dev_handle_fn != nullptr ) )
        {
           ::NS(cuda_device_handle_type) const dev_handle =
                this->m_node_id_dev_handle_fn( st::CudaNodeId_get( &node_id ) );

            auto it =  this->m_context_store.find( dev_handle );
            if(  it == this->m_context_store.end() )
            {
                st::ThreadId const current_tid;
                this_t::managed_ctx_t ctx{ this->m_ctx_create_fn(
                        &current_tid ), this->m_ctx_delete_fn };

                if( st::STATUS_SUCCESS != this->m_ctx_init_primary_fn(
                        ctx.get(), &node_id, create_flags, &lock ) )
                    ctx.reset();

                if( ctx.get() != nullptr )
                {
                    auto ret = this->m_context_store.emplace(
                            std::make_pair( dev_handle, ctx ) );
                    if( ret.second ) return ret.first->second;
                }

                return ctx;
            }
        }

        return this_t::managed_ctx_t{ nullptr };
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    this_t::managed_ctx_t this_t::init_context_as_ext_shared(
        this_t::context_type::ctx_handle_int_repr_type const ext_ctx_repr )
    {
        return this->init_context_as_ext_shared(
            ext_ctx_repr, this->create_lock() );
    }

    this_t::managed_ctx_t this_t::init_context_as_ext_shared(
        this_t::context_type::ctx_handle_int_repr_type const ext_ctx_repr,
        this_t::guard_type const& SIXTRL_RESTRICT_REF lock )
    {
        using int_repr_t = this_t::context_type::ctx_handle_int_repr_type;

        if( ( this->is_ready() ) && ( ext_ctx_repr != int_repr_t{ 0 } ) &&
            ( this->m_ctx_create_fn != nullptr ) &&
            ( this->m_ctx_delete_fn != nullptr ) &&
            ( this->m_ctx_init_ext_shared_fn != nullptr ) &&
            ( this->m_ctx_get_node_id_fn != nullptr ) )
        {
            st::ThreadId const current_tid;

            this_t::managed_ctx_t ctx{ this->m_ctx_create_fn(
                &current_tid ), this->m_ctx_delete_fn };

            if( ( ctx.get() != nullptr ) &&
                ( st::STATUS_SUCCESS == this->m_ctx_init_ext_shared_fn(
                    ctx.get(), ext_ctx_repr, &lock ) ) )
            {
                ::NS(BaseNodeId) const* node_id = this->m_ctx_get_node_id_fn(
                    ctx.get(), &lock );

                ::NS(cuda_device_handle_type) const dev_handle =
                    this->m_node_id_dev_handle_fn( node_id );

                auto it = this->m_context_store.find( dev_handle );
                if( it == this->m_context_store.end() )
                {
                    auto ret = this->m_context_store.emplace(
                        std::make_pair( dev_handle, ctx ) );

                    if( ret.second ) return ret.first->second;
                }
            }
        }

        return this_t::managed_ctx_t{ nullptr };
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    this_t::managed_ctx_t this_t::context(
        this_t::node_id_type const& SIXTRL_RESTRICT_REF node_id ) const {
        return this->context( node_id, this->create_lock() ); }

    this_t::managed_ctx_t this_t::context(
        this_t::node_id_type const& SIXTRL_RESTRICT_REF node_id,
        this_t::guard_type const& SIXTRL_RESTRICT_REF lock ) const {

        if( ( this->is_ready() ) && ( this->is_locked( lock ) ) &&
            ( node_id.is_legal() ) &&
            ( this->m_node_id_dev_handle_fn != nullptr ) )
        {
            ::NS(cuda_device_handle_type) const dev_handle =
                this->m_node_id_dev_handle_fn( &node_id );

            auto it = this->m_context_store.find( dev_handle );

            if( ( it != this->m_context_store.end() ) &&
                ( it->second.get() != nullptr ) &&
                ( it->second->backend_id() == st::BACKEND_CUDA ) &&
                ( it->second->is_active() ) )
            {
                return it->second;
            }
        }

        return this_t::managed_ctx_t{ nullptr };
    }

    /* --------------------------------------------------------------------- */

    bool this_t::inherit_ctx_during_init() const SIXTRL_NOEXCEPT {
        return this->m_inherit_ctx_during_init; }

    void this_t::enable_inherit_ctx_during_init() SIXTRL_NOEXCEPT {
        this->m_inherit_ctx_during_init = true; }

    void this_t::disable_inherit_ctx_during_init() SIXTRL_NOEXCEPT {
        this->m_inherit_ctx_during_init = false; }



    /* ===================================================================== */

    st_status_t this_t::do_assign_symbols()
    {
         st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( st::BaseNodeBackend::do_assign_symbols() == st::STATUS_SUCCESS ) )
        {
            SIXTRL_ASSERT( !this->is_available() );
            SIXTRL_ASSERT( !this->is_ready() );

            auto dlib_loader = this->ptr_base_dynamic_library_loader();
            if( ( dlib_loader == nullptr ) ||
                ( !dlib_loader->has_dynamic_lib_handle() ) )
            {
                return status;
            }

            status = st::STATUS_SUCCESS;
            bool const REQUIRED_SYMB = true;

            this->m_node_id_create_from_dev_handle_fn =
            dlib_loader->load_symbol<
                decltype( this->m_node_id_create_from_dev_handle_fn ) >(
                this->symbol_name( this_t::SYMBOL_ID_NODE_ID_CREATE_DEV_HANDLE ),
                    REQUIRED_SYMB );

            this->m_node_id_dev_handle_fn = dlib_loader->load_symbol< decltype(
                this->m_node_id_dev_handle_fn ) >( this->symbol_name(
                    this_t::SYMBOL_ID_NODE_ID_GET_DEV_HANDLE ), REQUIRED_SYMB );

            this->m_node_id_set_dev_handle_fn = dlib_loader->load_symbol<
                decltype( this->m_node_id_set_dev_handle_fn ) >(
                this->symbol_name(
                    this_t::SYMBOL_ID_NODE_ID_SET_DEV_HANDLE ), REQUIRED_SYMB );

            this->m_ctx_get_current_fn = dlib_loader->load_symbol< decltype(
                this->m_ctx_get_current_fn ) >( this->symbol_name(
                    this_t::SYMBOL_ID_CTX_GET_CURRENT ), REQUIRED_SYMB );

            this->m_ctx_set_current_fn = dlib_loader->load_symbol< decltype(
                this->m_ctx_set_current_fn ) >( this->symbol_name(
                    this_t::SYMBOL_ID_CTX_SET_CURRENT ), REQUIRED_SYMB );

            this->m_ctx_create_fn = dlib_loader->load_symbol< decltype(
                this->m_ctx_create_fn ) >( this->symbol_name(
                    this_t::SYMBOL_ID_CTX_CREATE ), REQUIRED_SYMB );

            this->m_ctx_delete_fn = dlib_loader->load_symbol< decltype(
                this->m_ctx_delete_fn ) >( this->symbol_name(
                    this_t::SYMBOL_ID_CTX_DELETE ), REQUIRED_SYMB );

            this->m_ctx_init_fn = dlib_loader->load_symbol< decltype(
                this->m_ctx_init_fn ) >( this->symbol_name(
                    this_t::SYMBOL_ID_CTX_INIT ), REQUIRED_SYMB );

            this->m_ctx_init_primary_fn = dlib_loader->load_symbol< decltype(
                this->m_ctx_init_primary_fn ) >( this->symbol_name(
                    this_t::SYMBOL_ID_CTX_INIT_AS_PRIMARY ), REQUIRED_SYMB );

            this->m_ctx_init_ext_shared_fn = dlib_loader->load_symbol<
                decltype( this->m_ctx_init_ext_shared_fn ) >( this->symbol_name(
                    this_t::SYMBOL_ID_CTX_INIT_AS_EXT_SHARED ), REQUIRED_SYMB );

            this->m_ctx_get_node_id_fn = dlib_loader->load_symbol<
                decltype( this->m_ctx_get_node_id_fn ) >( this->symbol_name(
                    this_t::SYMBOL_ID_CTX_GET_NODE_ID ), REQUIRED_SYMB );
        }

        return status;
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
            ( this->m_create_node_id_fn != nullptr ) &&
            ( this->m_delete_node_id_fn != nullptr ) &&
            ( this->m_create_node_id_from_str_fn != nullptr ) &&
            ( this->m_create_node_id_from_str_detail_fn != nullptr ) &&
            ( this->m_node_id_dev_handle_fn != nullptr ) &&
            ( this->m_node_id_set_dev_handle_fn != nullptr ) &&
            ( this->m_node_id_create_from_dev_handle_fn != nullptr ) &&
            ( this->m_ctx_get_current_fn != nullptr ) &&
            ( this->m_ctx_set_current_fn != nullptr ) &&
            ( this->m_ctx_create_fn != nullptr ) &&
            ( this->m_ctx_delete_fn != nullptr ) &&
            ( this->m_ctx_init_fn != nullptr ) &&
            ( this->m_ctx_init_fn != nullptr ) &&
            ( this->m_ctx_init_primary_fn != nullptr ) &&
            ( this->m_ctx_init_ext_shared_fn != nullptr ) &&
            ( this->m_ctx_get_node_id_fn != nullptr ) &&
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

                if( ( status == st::STATUS_SUCCESS ) &&
                    ( this->inherit_ctx_during_init() ) )
                {
                    SIXTRL_ASSERT(  this->m_ctx_get_current_fn != nullptr );
                    ::NS(cuda_ctx_int_repr_type) const ctx_repr =
                        this->m_ctx_get_current_fn();

                    if( ctx_repr != ::NS(cuda_ctx_int_repr_type){ 0 } )
                    {
                        this_t::guard_type const lock( this->create_lock() );
                        this->init_context_as_ext_shared( ctx_repr, lock );
                    }
                }
            }
        }

        return status;
    }

    /* ******************************************************************** */

    CudaBackend const* CudaBackend_get( const st::BaseBackend *const
            SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT
    {
        return ( ( ptr_base != nullptr ) &&
                 ( ptr_base->backend_id() == st::BACKEND_CUDA ) &&
                 ( ptr_base->has_nodes() ) )
            ? static_cast< CudaBackend const* >( ptr_base ) : nullptr;
    }

    CudaBackend* CudaBackend_get(
        st::BaseBackend* SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT
    {
        return const_cast< CudaBackend* >( st::CudaBackend_get(
            static_cast< st::BaseBackend const* >( ptr_base ) ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_EXPORT_API SIXTRL_HOST_FN CudaBackend* CudaBackend_get(
        SIXTRL_CXX_NAMESPACE::BaseBackend*
            SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT;

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

    void Cuda_shutdown_backend() {
        st::BackendsStore_global().remove_backend( st::BACKEND_CUDA );
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

void NS(Cuda_shutdown_backend)( void ) {
    SIXTRL_CXX_NAMESPACE::Cuda_shutdown_backend(); }

#endif /* C++, Host */
