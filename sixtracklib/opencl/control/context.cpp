#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/control/context.h"
    #include "sixtracklib/opencl/control/controller.h"
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
        using ctx_type       = st::OclContext;
        using ctx_key_type   = ctx_type::key_type;
        using st_node_id_t   = ctx_type::node_id_type;
        using st_status_t    = ctx_type::status_type;
        using st_size_t      = ctx_type::size_type;
        using ctx_store_type = st::OclContextStore;
        using st_guard_t     = ctx_store_type::guard_type;
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

    ctx_type::OclContext( st_node_id_t const& SIXTRL_RESTRICT_REF node_id,
        st_size_t const key_identifier ) :
        BackendObjBase( st::BACKEND_ID_OPENCL, ctx_type::BASE_CLASS_ID,
                        ctx_type::CLASS_ID ),
        m_key(), m_cl_devices( ctx_key_type::NUM_MAX_DEVICES, cl::Device{} ),
        m_cl_context()
    {
        auto const status = this->_init_context(
            &node_id, st_size_t{ 1 }, key_identifier );

        if( status != st::STATUS_SUCCESS ) throw std::runtime_error(
                "unable to construct context from single node_id" );
    }

    ctx_type::OclContext(
        st_node_id_t const* SIXTRL_RESTRICT node_ids_begin,
        st_size_t const num_node_ids, st_size_t const key_identifier ) :
        BackendObjBase( st::BACKEND_ID_OPENCL, ctx_type::BASE_CLASS_ID,
                        ctx_type::CLASS_ID ),
        m_key(), m_cl_devices( ctx_key_type::NUM_MAX_DEVICES, cl::Device{} ),
        m_cl_context()
    {
        auto const status = this->_init_context(
            node_ids_begin, num_node_ids, key_identifier );

        if( status != st::STATUS_SUCCESS ) throw std::runtime_error(
                "unable to construct context from node_ids pointer range" );
    }

    bool ctx_type::has_node_id( st_node_id_t const& node_id ) const SIXTRL_NOEXCEPT
    {
        bool is_found = false;

        if( ( node_id.is_legal() ) &&
            ( this->m_key.num_devices > st_size_t{ 0 } ) &&
            ( node_id.platform_id() == this->m_key.platform_id ) )
        {
            if( this->m_key.num_devices == st_size_t{ 1 } )
            {
                is_found = ( this->m_key.device_ids[ 0 ] == node_id.device_id() );
            }
            else
            {
                st_size_t ii = st_size_t{ 0 };
                for( ; ii < this->m_key.num_devices ; ++ii )
                {
                    if( this->m_key.device_ids[ ii ] == node_id.device_id() )
                    {
                        is_found = true;
                        break;
                    }
                }
            }
        }

        return is_found;
    }

    st_node_id_t ctx_type::node_id( st_size_t const id ) const SIXTRL_NOEXCEPT
    {
        return ( id < this->m_key.num_devices )
            ? st_node_id_t( this->m_key.platform_id,
                this->m_key.device_ids[ id ], this->m_node_indices[ id ] )
            : st_node_id_t{};
    }

    st_status_t ctx_type::node_ids(
        std::vector< node_id_type >& SIXTRL_RESTRICT_REF node_ids )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        node_ids.clear();

        if( ( this->m_key.num_devices == this->m_cl_devices.size() ) &&
            ( this->m_key.num_devices <  ctx_key_type::NUM_MAX_DEVICES ) )
        {
            node_ids.reserve( this->m_key.num_devices );

            st_size_t ii = st_size_t{ 0 };
            for( ; ii < this->m_key.num_devices ; ++ii )
            {
                node_ids.emplace_back( this->m_key.platform_id,
                                       this->m_key.device_ids[ ii ],
                                       this->m_node_indices[ ii ] );
            }

            SIXTRL_ASSERT( std::adjacent_find(
                node_ids.begin(), node_ids.end(),
                []( node_id_type const& lhs, node_id_type const& rhs ) -> bool
                { return ( lhs.compare( rhs, false ) == 0 ); } ) ==
                    node_ids.end() );

            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    std::vector< cl::Device > const& ctx_type::cl_devices() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_cl_devices.size() == this->m_key.num_devices );
        return this->m_cl_devices;
    }

    st_status_t ctx_type::_init_context(
        st_node_id_t const* SIXTRL_RESTRICT node_ids_begin,
        st_size_t const num_node_ids, st_size_t const key_identifier )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        this->clear();

        if( ( node_ids_begin != nullptr ) &&
            ( key_identifier != ctx_key_type::ILLEGAL_IDENTIFIER ) &&
            ( num_node_ids < ctx_key_type::NUM_MAX_DEVICES ) )
        {
            std::vector< ctx_type::node_id_type > all_node_ids;
            std::vector< cl::Device > all_cl_devices;

            status = st::OclController::GET_AVAILABLE_NODES( all_node_ids,
                nullptr, &all_cl_devices, nullptr );

            if( status != st::STATUS_SUCCESS ) return status;

            if( ( all_node_ids.empty() ) ||
                ( !std::is_sorted( all_node_ids.begin(), all_node_ids.end() ) ) )
            {
                this->clear();
                return st::STATUS_GENERAL_FAILURE;
            }

            if( node_ids_begin[ 0 ].platform_id() ==
                st_node_id_t::ILLEGAL_PLATFORM_ID )
            {
                this->clear();
                return st::STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( status == st::STATUS_SUCCESS );
            this->m_key.platform_id = node_ids_begin[ 0 ].platform_id();

            for( st_size_t ii = st_size_t{ 1 }; ii < num_node_ids ; ++ii )
            {
                if( node_ids_begin[ ii - 1 ].compare( node_ids_begin[ ii ] )
                        >= ::NS(cmp_result_type{ 0 } ) )
                {
                    status = st::STATUS_GENERAL_FAILURE;
                    break;
                }

                if( node_ids_begin[ ii ].platform_id() !=
                    this->m_key.platform_id )
                {
                    status = st::STATUS_GENERAL_FAILURE;
                    break;
                }
            }

            if( status != st::STATUS_SUCCESS )
            {
                this->clear();
                return status;
            }

            st_size_t const N_ALL_NODES = all_node_ids.size();

            for( st_size_t ii = 0u ; ii < num_node_ids ; ++ii )
            {
                for( st_size_t jj = st_size_t{ 0 }; jj < N_ALL_NODES ; ++jj )
                {
                    if( 0 == node_ids_begin[ ii ].compare(
                            all_node_ids[ jj ], false ) )
                    {
                        this->m_cl_devices.push_back(
                            cl::Device( all_cl_devices[ jj ](), true ) );
                        this->m_node_indices[ this->m_key.num_devices ] = jj;
                        this->m_key.device_ids[ this->m_key.num_devices++ ] =
                            all_node_ids[ jj ].device_id();

                        break;
                    }
                }
            }

            if( status != st::STATUS_SUCCESS )
            {
                this->clear();
                return status;
            }

            if( ( this->m_key.num_devices == st_size_t{ 0 } ) ||
                ( this->m_cl_devices.size() != this->m_key.num_devices ) )
            {
                this->clear();
                return st::STATUS_GENERAL_FAILURE;
            }

            cl::Context new_ctx( this->m_cl_devices );
            this->m_key.identifier = key_identifier;
            this->m_cl_context = new_ctx;
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

    ctx_store_type::OclContextStore() :
        st::MTBackendObjBase( st::BACKEND_ID_OPENCL,
        ctx_store_type::BASE_CLASS_ID, ctx_store_type::CLASS_ID ),
        m_stored_ctx()
    {

    }

    ctx_store_type::~OclContextStore() {
        auto const guard = this->create_lock();
        this->m_stored_ctx.clear();
    }

    void ctx_store_type::keys(
        std::vector< ctx_key_type >& SIXTRL_RESTRICT_REF key_array,
        st_node_id_t const* node_ids_begin, st_size_t const num_node_ids,
        st_guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        key_array.clear();

        if( ( this->is_locked( lock ) ) &&
            ( node_ids_begin != nullptr ) && ( num_node_ids > st_size_t{ 0 } ) )
        {
            key_array.reserve( this->size( lock ) );

            auto it = this->m_stored_ctx.begin();
            auto end = this->m_stored_ctx.end();

            for( ; it != end ; ++it )
            {
                st_size_t ii = st_size_t{ 0 };
                for( ; ii < num_node_ids ; ++ii )
                {
                    if( it->first.contains_node_id( node_ids_begin[ ii ] ) )
                    {
                        key_array.push_back( it->first );
                    }
                }
            }
        }
    }
}

#endif /* C++, Host */
