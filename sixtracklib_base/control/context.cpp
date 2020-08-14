#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/control/context.h"
    #include "sixtracklib_base/backend/backend.h"
    #include "sixtracklib_base/backend/backends_store.h"
    #include "sixtracklib_base/internal/class_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdexcept>
    #include <sstream>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using base_ctx_t = st::BaseContext;
        using mt_ctx_t = st::BaseMTSharableContext;
    }

    constexpr base_ctx_t::class_variant_t base_ctx_t::CTX_VARIANT_DEFAULT;
    constexpr base_ctx_t::class_variant_t base_ctx_t::CTX_VARIANT_MT_SHAREABLE;

    /* ********************************************************************* */

    base_ctx_t::~BaseContext() {}

    /* --------------------------------------------------------------------- */

    bool base_ctx_t::is_mt_shareable_context() const SIXTRL_NOEXCEPT {
        return this->is_class_variant( base_ctx_t::CTX_VARIANT_MT_SHAREABLE );}
    }

    mt_ctx_t const* base_ctx_t::as_mt_shareable_context() const SIXTRL_NOEXCEPT
    {
        return ( this->is_mt_shareable_context() )
            ? static_cast< mt_ctx_t const* >( this ) : nullptr;
    }

    mt_ctx_t* base_ctx_t::as_mt_shareable_context() SIXTRL_NOEXCEPT
    {
        return const_cast< mt_ctx_t*  >( static_cast<
            base_ctx_t const& >( *this ).as_mt_shareable_context() );
    }

    /* --------------------------------------------------------------------- */

    base_ctx_t::base_backend_t& base_ctx_t::base_backend() SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_ptr_base_backend != nullptr );
        return *this->m_ptr_base_backend;
    }

    base_ctx_t::base_backend_t const&
    base_ctx_t::base_backend() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_ptr_base_backend != nullptr );
        return *this->m_ptr_base_backend;
    }

    base_ctx_t::BaseContext(
        base_ctx_t::base_backend_t& SIXTRL_RESTRICT backend ) :
        st::BaseBackendObj( backend.backend_id(), st::CLASS_ID_CONTEXT ),
        m_ptr_base_backend( nullptr )
    {
        if( ( backend.backend_id() == st::BACKEND_ILLEGAL ) ||
            ( backend.backend_id() == st::BACKEND_UNDEFINED ) )
        {
            throw std::runtime_error( "illegal / undefined backend" );
        }

        if( !backend.is_ready() )
        {
            std::ostringstream a2str;
            a2str << "Backend backend_id = " << backend.backend_id() << " "
                  << "is required to be fully initialized "
                  << "before using it to construct a context";
            throw std::runtime_error( a2str.str() );
        }

        SIXTRL_ASSERT( backend.is_available() );
        this->m_ptr_base_backend = &backend;
    }

    base_ctx_t::BaseContext( base_ctx_t::backend_id_t const backend_id ) :
        st::BaseBackendObj( backend_id, st::CLASS_ID_CONTEXT ),
        m_ptr_base_backend( nullptr )
    {
        if( ( backend_id == st::BACKEND_ILLEGAL ) ||
            ( backend_id == st::BACKEND_UNDEFINED ) )
        {
            throw std::runtime_error( "illegal / undefined backend" );
        }

        st::BackendsStore& be_store = st::BackendsStore_global();
        base_ctx_t::base_backend_t* backend = be_store.backend( backend_id );

        if( backend == nullptr )
        {
            std::ostringstream a2str;
            a2str << "backend with id = " << backend_id
                  << " is not available from global backends store";
            throw std::runtime_error( a2str.str() );
        }

        if( !backend->is_ready() )
        {
            std::ostringstream a2str;
            a2str << "Backend backend_id = " << backend_id << " "
                  << "is required to be fully initialized "
                  << "before using it to construct a context";
            throw std::runtime_error( a2str.str() );
        }

        SIXTRL_ASSERT( backend->is_available() );
        this->m_ptr_base_backend = backend;
    }

    /* ===================================================================== */


}
#endif /* C++, Host */
