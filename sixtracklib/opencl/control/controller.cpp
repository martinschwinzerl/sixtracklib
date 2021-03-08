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

    ocl_ctrl_type::OclController(
        node_id_type const& SIXTRL_RESTRICT_REF node_id,
        ocl_context_type& SIXTRL_RESTRICT_REF context,
        std::shared_ptr< ocl_prog_store_type >& SIXTRL_RESTRICT_REF prog_store ) :
        st::ControllerBase( st::BACKEND_ID_OPENCL, ocl_ctrl_type::CLASS_ID ),
        m_selected_node_id(),
        m_cmd_queues(),
        m_program_store( nullptr ),
        m_node_store( context.shared_node_store() ),
        m_context( context )
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
            this->m_node_store->node_index( node_id ) );

        this->m_cmd_queues.emplace_back(
            new ocl_cmd_queue_type( this->m_context ) );
    }

    cl::Device const& ocl_ctrl_type::cl_selected_device() const {
        if( this->m_node_store.get() == nullptr )
            throw std::runtime_error( "no node store available" );
        return this->m_node_store->cl_device( this->m_selected_node_id ); }

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

    ocl_cmd_queue_type& ocl_ctrl_type::cmd_queue( st_size_t const id )
    {
        auto ptr = this->ptr_cmd_queue( id );
        if( ptr == nullptr ) throw std::runtime_error(
            "no legal cmd_queue available for id" );
        return *ptr;
    }

    ocl_cmd_queue_type const& ocl_ctrl_type::cmd_queue(
        st_size_t const id ) const
    {
        auto ptr = this->ptr_cmd_queue( id );
        if( ptr == nullptr ) throw std::runtime_error(
            "no legal cmd_queue available for id" );
        return *ptr;
    }

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
