#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/control/cmd_queue.h"
    #include "sixtracklib/opencl/control/context.h"
#endif /* !defined( SIXTRL_NO_INCLUDES )  */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <algorithm>
    #include <iostream>
    #include <iterator>
    #include <sstream>
#endif /* !defined( SIXTRL_NO_INCLUDES )  && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using queue_type = st::OclCommandQueue;
    }

    constexpr queue_type::class_id_type queue_type::BASE_CLASS_ID;
    constexpr queue_type::class_id_type queue_type::CLASS_ID;

    constexpr queue_type::backend_id_type
    st::BackendObjTraits< queue_type >::BACKEND_ID;

    constexpr queue_type::class_id_type
    st::BackendObjTraits< queue_type >::BASE_CLASS_ID;

    constexpr queue_type::class_id_type
    st::BackendObjTraits< queue_type >::DERIVED_CLASS_ID;

    /* --------------------------------------------------------------------- */

    queue_type::OclCommandQueue(
        queue_type::context_type const& SIXTRL_RESTRICT_REF context ) :
        st::MTBackendObjBase( st::BACKEND_ID_OPENCL, queue_type::BASE_CLASS_ID,
                              queue_type::CLASS_ID ),
        m_cl_command_queue()
    {
        cl::CommandQueue queue( context.cl_context() );

        auto guard = this->create_lock();
        SIXTRL_ASSERT( this->is_locked( guard ) );
        this->m_cl_command_queue = queue;
    }

    queue_type::OclCommandQueue(
        cl::Context const& SIXTRL_RESTRICT_REF context ) :
        st::MTBackendObjBase( st::BACKEND_ID_OPENCL, queue_type::BASE_CLASS_ID,
                              queue_type::CLASS_ID ),
        m_cl_command_queue( context )
    {
    }


}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
