#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/control/context.h"
    #include "sixtracklib/opencl/control/node_store.h"
    #include "sixtracklib/opencl/internal/helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES )  */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <stdexcept>
    #include <sstream>
#endif /* !defined( SIXTRL_NO_INCLUDES )  && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using ctx_type        = st::OclContext;
        using st_node_store_t = st::OclNodeStore;
        using ctx_key_type    = ctx_type::key_type;
        using st_node_id_t    = ctx_type::node_id_type;
        using st_status_t     = ctx_type::status_type;
        using st_size_t       = ctx_type::size_type;
        using ctx_store_type  = st::OclContextStore;
    }

    /* ********************************************************************* */

    constexpr ctx_type::class_id_type ctx_type::BASE_CLASS_ID;
    constexpr ctx_type::class_id_type ctx_type::CLASS_ID;

    constexpr ctx_type::backend_id_type
    st::BackendObjTraits< ctx_type >::BACKEND_ID;

    constexpr ctx_type::class_id_type
    st::BackendObjTraits< ctx_type >::BASE_CLASS_ID;

    constexpr ctx_type::class_id_type
    st::BackendObjTraits< ctx_type >::DERIVED_CLASS_ID;

    /* --------------------------------------------------------------------- */

    ctx_type::OclContext(
        std::shared_ptr< st_node_store_t >& SIXTRL_RESTRICT_REF node_store,
        st_node_id_t const& SIXTRL_RESTRICT_REF node_id,
        st_size_t const key_identifier ) :
        BackendObjBase( st::BACKEND_ID_OPENCL, ctx_type::BASE_CLASS_ID,
                        ctx_type::CLASS_ID ),
        m_key(), m_cl_context(), m_node_store( node_store )
    {
        auto const status = this->_init_context(
            &node_id, st_size_t{ 1 }, key_identifier );

        if( status != st::STATUS_SUCCESS ) throw std::runtime_error(
                "unable to construct context from single node_id" );
    }

    ctx_type::OclContext(
        std::shared_ptr< st_node_store_t >& SIXTRL_RESTRICT_REF node_store,
        st_node_id_t const* SIXTRL_RESTRICT node_ids_begin,
        st_size_t const num_nodes, st_size_t const key_identifier ) :
        BackendObjBase( st::BACKEND_ID_OPENCL, ctx_type::BASE_CLASS_ID,
                        ctx_type::CLASS_ID ),
        m_key(), m_cl_context(), m_node_store( node_store )
    {
        auto const status = this->_init_context(
            node_ids_begin, num_nodes, key_identifier );

        if( status != st::STATUS_SUCCESS ) throw std::runtime_error(
                "unable to construct context from node_ids pointer range" );
    }

    bool ctx_type::has_node_id( st_node_id_t const& node_id ) const SIXTRL_NOEXCEPT
    {
        bool is_found = false;

        if( ( node_id.is_legal() ) &&
            ( this->m_key.num_devices > st_size_t{ 0 } ) &&
            ( this->m_node_store.get() != nullptr ) &&
            ( this->m_node_store->has_node_id( node_id ) ) &&
            ( node_id.platform_id() == this->m_key.platform_id ) )
        {
            if( this->m_key.num_devices == st_size_t{ 1 } )
            {
                is_found = (
                    ( this->m_key.device_ids[ 0 ] == node_id.device_id() ) &&
                    ( ( !node_id.has_index() ) ||
                      ( this->m_node_indices[ 0 ] == node_id.index() ) ) );
            }
            else
            {
                st_size_t ii = st_size_t{ 0 };
                for( ; ii < this->m_key.num_devices ; ++ii )
                {
                    if( this->m_key.device_ids[ ii ] == node_id.device_id() )
                    {
                        is_found = (
                            ( !node_id.has_index() ) ||
                            ( this->m_node_indices[ 0 ] == node_id.index() ) );

                        break;
                    }
                }
            }
        }

        return is_found;
    }

    st_status_t ctx_type::cl_devices(
        std::vector< cl::Device >& SIXTRL_RESTRICT_REF cl_devices ) const
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        cl_devices.clear();

        if( ( this->m_node_store.get() != nullptr ) &&
            ( this->m_key.is_legal() ) &&
            ( this->m_key.num_devices > st_size_t{ 0 } ) &&
            ( this->m_node_store->has_platform_id( this->m_key.platform_id ) ) &&
            ( this->m_key.num_devices <=
              this->m_node_store->num_nodes( this->m_key.platform_id ) ) )
        {
            status = this->m_node_store->cl_devices( cl_devices,
                &this->m_node_indices[ 0 ], this->m_key.num_devices );
        }

        return status;
    }

    st_node_id_t ctx_type::node_id( st_size_t const id ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( !this->m_key.is_legal() ) ||
            ( ( this->m_node_store.get() != nullptr ) &&
              ( this->m_node_store->has_node_id( st_node_id_t{
                  this->m_key.platform_id, this->m_key.device_ids[ id ],
                          this->m_node_indices[ id ] } ) ) ) );

        return ( id < this->m_key.num_devices )
            ? st_node_id_t( this->m_key.platform_id,
                this->m_key.device_ids[ id ], this->m_node_indices[ id ] )
            : st_node_id_t{};
    }

    st_status_t ctx_type::node_ids(
        std::vector< node_id_type >& SIXTRL_RESTRICT_REF node_ids ) const {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        node_ids.clear();

        if( ( this->m_node_store.get() != nullptr ) &&
            ( this->m_key.is_legal() ) &&
            ( this->m_key.num_devices > st_size_t{ 0 } ) &&
            ( this->m_node_store->has_platform_id( this->m_key.platform_id ) ) &&
            ( this->m_key.num_devices <= this->m_node_store->num_nodes(
                this->m_key.platform_id ) ) )
        {
            status = this->m_node_store->node_ids( node_ids,
                &this->m_node_indices[ 0 ], this->m_key.num_devices );
        }

        return status;
    }

    st_status_t ctx_type::_init_context(
        st_node_id_t const* SIXTRL_RESTRICT node_ids_begin,
        st_size_t const num_nodes, st_size_t const key_identifier )
    {
        using pform_id_t = st_node_id_t::platform_id_type;
        using cl_ctx_prop_t = ::cl_context_properties;

        st_status_t status = st::STATUS_GENERAL_FAILURE;
        this->clear();

        if( ( this->m_node_store.get() == nullptr ) ||
            ( node_ids_begin == nullptr ) ||
            ( num_nodes == st_size_t{ 0 } ) ||
            ( num_nodes > ctx_key_type::NUM_MAX_DEVICES ) ||
            ( key_identifier == ctx_key_type::ILLEGAL_IDENTIFIER ) )
        {
            return status;
        }

        pform_id_t platform_id = st::NodeId::ILLEGAL_PLATFORM_ID;
        status = st::STATUS_SUCCESS;

        for( st_size_t ii = 0u ; ii < num_nodes ; ++ii )
        {
            if( !node_ids_begin[ ii ].is_legal() )
            {
                status = st::STATUS_GENERAL_FAILURE;
                break;
            }

            if( ii == st_size_t{ 0 } )
                platform_id = node_ids_begin[ ii ].platform_id();

            if( node_ids_begin[ ii ].platform_id() != platform_id )
            {
                status = st::STATUS_GENERAL_FAILURE;
                break;
            }

            if( !this->m_node_store->has_node_id(
                    node_ids_begin[ ii ].platform_id(),
                        node_ids_begin[ ii ].device_id() ) )
            {
                status = st::STATUS_GENERAL_FAILURE;
                break;
            }
        }

        if( ( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID ) ||
            ( !this->m_node_store->has_platform_id( platform_id ) ) ||
            (  this->m_node_store->num_nodes( platform_id ) < num_nodes ) )
        {
            status = st::STATUS_GENERAL_FAILURE;
        }

        if( status != st::STATUS_SUCCESS ) return status;

        this->m_key.num_devices = num_nodes;
        this->m_key.platform_id = platform_id;
        this->m_key.identifier  = key_identifier;

        for( st_size_t ii = 0u ; ii < num_nodes ; ++ii )
        {
            SIXTRL_ASSERT( node_ids_begin[ ii ].is_legal() );
            this->m_key.device_ids[ ii ] = node_ids_begin[ ii ].device_id();

            this->m_node_indices[ ii ] = this->m_node_store->node_index(
                node_ids_begin[ ii ].platform_id(),
                    node_ids_begin[ ii ].device_id() );
        }

        std::vector< cl::Device > cl_devs( num_nodes, cl::Device{} );
        status = this->m_node_store->cl_devices( cl_devs,
            &this->m_node_indices[ 0 ], this->m_key.num_devices );

        if( status != st::STATUS_SUCCESS )
        {
            this->clear();
            return status;
        }

        SIXTRL_ASSERT( !cl_devs.empty() );
        SIXTRL_ASSERT(  cl_devs.size() == this->m_key.num_devices );
        SIXTRL_ASSERT(  status == st::STATUS_SUCCESS );

        ::cl_int ret = CL_SUCCESS;
        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        try
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        {
            cl::Platform& cl_platform =
                this->m_node_store->cl_platform( platform_id );

            cl_ctx_prop_t ctx_props[] = {
                CL_CONTEXT_PLATFORM, ( cl_ctx_prop_t )cl_platform(), 0 };

            cl::Context new_ctx(
                cl_devs, &ctx_props[ 0 ], nullptr, nullptr, &ret );

            if( ret == CL_SUCCESS ) this->m_cl_context = std::move( new_ctx );
        }
        #if defined( CL_HPP_ENABLE_EXCEPTIONS )
        catch( cl::Error const& e )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( e.err(),
                "OclNodeStore", "GET_ALL_CL_PLATFORMS", e.what(),
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #else /* !defined( CL_HPP_ENABLE_EXCEPTIONS ) */
        if( CL_SUCCESS != ret )
        {
            st::OpenCL_ret_value_to_exception< std::runtime_error >( ret,
                "OclNodeStore", "GET_ALL_CL_PLATFORMS", "",
                    st_size_t{ __LINE__ } );
            status = st::STATUS_GENERAL_FAILURE;
        }
        #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */

        if( status != st::STATUS_SUCCESS )
        {
            this->clear();
        }

        return status;
    }

    /* ********************************************************************* */

    constexpr ctx_store_type::class_id_type ctx_store_type::BASE_CLASS_ID;
    constexpr ctx_store_type::class_id_type ctx_store_type::CLASS_ID;

    constexpr ctx_store_type::backend_id_type
    st::BackendObjTraits< ctx_store_type >::BACKEND_ID;

    constexpr ctx_store_type::class_id_type
    st::BackendObjTraits< ctx_store_type >::BASE_CLASS_ID;

    constexpr ctx_store_type::class_id_type
    st::BackendObjTraits< ctx_store_type >::DERIVED_CLASS_ID;

    ctx_store_type::OclContextStore(
        std::shared_ptr< node_store_type >& SIXTRL_RESTRICT_REF node_store ) :
        st::BackendObjBase( st::BACKEND_ID_OPENCL,
        ctx_store_type::BASE_CLASS_ID, ctx_store_type::CLASS_ID ),
        m_stored_ctx(), m_node_store( node_store ) {}

    ctx_store_type::~OclContextStore() { this->m_stored_ctx.clear(); }

    void ctx_store_type::keys(
        std::vector< ctx_key_type >& SIXTRL_RESTRICT_REF key_array,
        st_node_id_t const* node_ids_begin, st_size_t const num_nodes ) {
        key_array.clear();
        if( ( node_ids_begin != nullptr ) && ( num_nodes > st_size_t{ 0 } ) )
        {
            key_array.reserve( this->size() );

            auto it = this->m_stored_ctx.begin();
            auto end = this->m_stored_ctx.end();

            for( ; it != end ; ++it ) {
                st_size_t ii = st_size_t{ 0 };
                for( ; ii < num_nodes ; ++ii ) {
                    if( it->first.contains_node_id( node_ids_begin[ ii ] ) ) {
                        key_array.push_back( it->first );
                    }
                }
            }
        }
    }
}

#endif /* C++, Host */
