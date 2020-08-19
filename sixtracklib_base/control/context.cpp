#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/control/context.h"
    #include "sixtracklib_base/backend/backend.h"
    #include "sixtracklib_base/backend/backends_store.h"
    #include "sixtracklib_base/internal/class_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <stdexcept>
    #include <sstream>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using base_ctx_t  = SIXTRL_CXX_NAMESPACE::BaseContext;
        using st_size_t   = base_ctx_t::size_type;
        using st_status_t = base_ctx_t::status_t;

        using mt_ctx_t    = SIXTRL_CXX_NAMESPACE::BaseMTShareableContext;
        using guard_t     = mt_ctx_t::guard_type;
        using thread_id_t = mt_ctx_t::thread_id_type;
    }

    constexpr base_ctx_t::class_variant_t base_ctx_t::CTX_VARIANT_DEFAULT;
    constexpr base_ctx_t::class_variant_t base_ctx_t::CTX_VARIANT_MT_SHAREABLE;

    /* ********************************************************************* */
    /* ******                        BaseContext                     ******* */
    /* ********************************************************************* */

    base_ctx_t::~BaseContext() {}

    /* --------------------------------------------------------------------- */

    bool base_ctx_t::is_mt_shareable_context() const SIXTRL_NOEXCEPT {
        return this->is_class_variant( base_ctx_t::CTX_VARIANT_MT_SHAREABLE );}

    st::BaseMTShareableContext const*
    base_ctx_t::as_mt_shareable_context() const SIXTRL_NOEXCEPT
    {
        return ( this->is_mt_shareable_context() )
            ? static_cast< st::BaseMTShareableContext const* >( this )
            : nullptr;
    }

    st::BaseMTShareableContext *
    base_ctx_t::as_mt_shareable_context() SIXTRL_NOEXCEPT
    {
        return const_cast< st::BaseMTShareableContext *  >( static_cast<
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

    bool base_ctx_t::is_active() const
    {
        return this->m_is_active.load();
    }

    /* --------------------------------------------------------------------- */

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
        this->m_is_active.store( false );
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
        this->m_is_active.store( false );
    }

    base_ctx_t::BaseContext( BaseContext const& other ) :
        m_ptr_base_backend( other.m_ptr_base_backend )
    {
        this->m_is_active.store( other.m_is_active.load() );
    }

    base_ctx_t::BaseContext( BaseContext&& other ) :
        m_is_active( other.m_is_active.load() ),
        m_ptr_base_backend( std::move( other.m_ptr_base_backend ) )
    {
        other.m_is_active.store( false );
        other.m_ptr_base_backend = nullptr;
    }

    base_ctx_t& base_ctx_t::operator=( BaseContext const& rhs )
    {
        if( &rhs != this )
        {
            this->m_ptr_base_backend = rhs.m_ptr_base_backend;
            this->m_is_active.store( rhs.m_is_active.load() );
        }

        return *this;
    }

    base_ctx_t& base_ctx_t::operator=( BaseContext&& rhs )
    {
        if( &rhs != this )
        {
            this->m_ptr_base_backend = std::move( rhs.m_ptr_base_backend );
            this->m_is_active.store( rhs.m_is_active.load() );
            rhs.m_is_active.store( false );
            rhs.m_ptr_base_backend = nullptr;
        }

        return *this;
    }

    void base_ctx_t::update_is_active( bool const is_active_flag )
    {
        this->m_is_active.store( is_active_flag );
    }

    /* ********************************************************************* */
    /* *******               BaseMTShareableContext                   ****** */
    /* ********************************************************************* */

    thread_id_t mt_ctx_t::owned_by() const {
        guard_t const lock( this->base_backend().create_lock() );
        return this->owned_by( lock );
    }

    thread_id_t const& mt_ctx_t::owned_by( guard_t const& SIXTRL_RESTRICT_REF
        lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->base_backend().is_locked( lock ) );
        return this->m_owner_thread_id;
    }

    /* --------------------------------------------------------------------- */

    st_size_t mt_ctx_t::num_attached_threads() const
    {
        guard_t const lock( this->base_backend().create_lock() );
        return this->num_attached_threads( lock );
    }

    st_size_t mt_ctx_t::num_attached_threads(
        guard_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        st_size_t num_attached_threads = st_size_t{ 0 };

        if( ( this->base_backend().is_ready() ) &&
            ( this->base_backend().is_locked( lock ) ) )
        {
            SIXTRL_ASSERT( std::is_sorted( this->m_attached_threads.begin(),
                this->m_attached_threads.end() ) );

            SIXTRL_ASSERT( !std::binary_search(
                this->m_attached_threads.begin(),
                this->m_attached_threads.end(), thread_id_t{} ) );

            SIXTRL_ASSERT( this->m_attached_threads.size() <=
                this->base_backend().num_associated_threads( lock ) );

            SIXTRL_ASSERT( std::all_of( this->m_attached_threads.begin(),
                this->m_attached_threads.end(),
                [this, &lock]( thread_id_t const& tid ) -> bool {
                    return this->base_backend().is_associated_with_thread(
                        tid, lock ); }
            ) );

            num_attached_threads = this->m_attached_threads.size();
        }

        return num_attached_threads;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool mt_ctx_t::is_attached(
        thread_id_t const& SIXTRL_RESTRICT_REF tid ) const
    {
        guard_t const lock( this->base_backend().create_lock() );
        return this->is_attached( tid, lock );
    }

    bool mt_ctx_t::is_attached(
        thread_id_t const& SIXTRL_RESTRICT_REF tid,
        guard_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        bool is_assoc_with_tid = tid.is_legal();

        if( ( is_assoc_with_tid ) && ( this->base_backend().is_ready() ) &&
            ( this->base_backend().is_associated_with_thread( tid, lock ) ) )
        {
            SIXTRL_ASSERT( std::is_sorted( this->m_attached_threads.begin(),
                this->m_attached_threads.end() ) );

            SIXTRL_ASSERT( !std::binary_search(
                this->m_attached_threads.begin(),
                this->m_attached_threads.end(), thread_id_t{} ) );

            SIXTRL_ASSERT( this->m_attached_threads.size() <=
                this->base_backend().num_associated_threads( lock ) );

            SIXTRL_ASSERT( std::all_of( this->m_attached_threads.begin(),
                this->m_attached_threads.end(),
                [this, &lock]( mt_ctx_t::thread_id_type const tid ) -> bool {
                    return this->base_backend().is_associated_with_thread(
                        tid, lock ); } ) );

            is_assoc_with_tid = std::binary_search(
                this->m_attached_threads.begin(),
                this->m_attached_threads.end(), tid );
        }

        return is_assoc_with_tid;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    thread_id_t const* mt_ctx_t::attached_thread_ids_begin(
        guard_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->num_attached_threads( lock ) > st_size_t{ 0 } )
            ? this->m_attached_threads.data() : nullptr;
    }

    thread_id_t const* mt_ctx_t::attached_thread_ids_end(
        guard_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        auto end_ptr = this->attached_thread_ids_begin( lock );
        if( end_ptr != nullptr )
        {
            std::advance( end_ptr, this->num_attached_threads( lock ) );
        }

        return end_ptr;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t mt_ctx_t::attach_thread(
        thread_id_t const& SIXTRL_RESTRICT_REF tid )
    {
        guard_t lock( this->base_backend().create_lock() );
        return this->attach_thread( tid, lock );
    }

    st_status_t mt_ctx_t::attach_thread(
        thread_id_t const& SIXTRL_RESTRICT_REF tid,
        guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->base_backend().is_associated_with_thread( tid, lock ) ) &&
            ( !this->is_attached( tid, lock ) ) )
        {
            SIXTRL_ASSERT( tid.is_legal() );
            status = this->do_attach_thread( tid, lock );
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t mt_ctx_t::detach_thread(
        thread_id_t const& SIXTRL_RESTRICT_REF tid )
    {
        guard_t const lock( this->base_backend().create_lock() );
        return this->detach_thread( tid, lock );
    }

    st_status_t mt_ctx_t::detach_thread(
        thread_id_t const& SIXTRL_RESTRICT_REF tid,
        guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        return ( this->is_attached( tid, lock ) )
            ? this->do_detach_thread( tid, lock ) : st::STATUS_GENERAL_FAILURE;
    }

    /* ===================================================================== */

    mt_ctx_t::BaseMTShareableContext(
        mt_ctx_t::base_backend_t& SIXTRL_RESTRICT backend,
        thread_id_t const& SIXTRL_RESTRICT_REF tid ) :
        base_ctx_t( backend ), m_attached_threads(), m_owner_thread_id( tid )
    {
        this->set_class_variant(
            this->class_variant_flags() |
            base_ctx_t::CTX_VARIANT_MT_SHAREABLE );
    }

    mt_ctx_t::BaseMTShareableContext(
        mt_ctx_t::backend_id_t const backend_id,
        thread_id_t const& SIXTRL_RESTRICT_REF tid ) :
        base_ctx_t( backend_id ), m_attached_threads(),
        m_owner_thread_id( tid )
    {
        this->set_class_variant(
            this->class_variant_flags() |
            base_ctx_t::CTX_VARIANT_MT_SHAREABLE );
    }

    /* --------------------------------------------------------------------- */

    st_status_t mt_ctx_t::do_attach_thread(
        thread_id_t const& SIXTRL_RESTRICT_REF tid,
        guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        return this->do_attach_thread_mt_impl( tid, lock );
    }

    st_status_t mt_ctx_t::do_detach_thread(
        thread_id_t const& SIXTRL_RESTRICT_REF tid,
        guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        return this->do_detach_thread_mt_impl( tid, lock );
    }

    st_status_t mt_ctx_t::do_attach_thread_mt_impl(
        thread_id_t const& SIXTRL_RESTRICT_REF tid,
        guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( (  this->base_backend().is_ready() ) &&
            (  this->base_backend().backend_id() == this->backend_id() ) &&
            (  this->base_backend().is_locked( lock ) ) &&
            ( !this->base_backend().is_associated_with_thread( tid, lock ) ) )
        {
            SIXTRL_ASSERT( std::is_sorted( this->m_attached_threads.begin(),
                this->m_attached_threads.end() ) );

            SIXTRL_ASSERT( !std::binary_search(
                this->m_attached_threads.begin(),
                this->m_attached_threads.end(), tid ) );

            SIXTRL_ASSERT( !std::binary_search(
                this->m_attached_threads.begin(),
                this->m_attached_threads.end(), thread_id_t{} ) );

            this->m_attached_threads.push_back( tid );
            std::sort( this->m_attached_threads.begin(),
                       this->m_attached_threads.end() );

            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    st_status_t mt_ctx_t::do_detach_thread_mt_impl(
        thread_id_t const& SIXTRL_RESTRICT_REF tid,
        guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( this->is_attached( tid, lock ) )
        {
            SIXTRL_ASSERT( this->base_backend().is_ready() );
            SIXTRL_ASSERT( this->base_backend().is_locked( lock ) );
            SIXTRL_ASSERT( this->base_backend().backend_id() ==
                           this->backend_id() );

            SIXTRL_ASSERT( this->base_backend(
                ).is_associated_with_thread( tid, lock ) );

            SIXTRL_ASSERT( std::is_sorted(
                this->m_attached_threads.begin(),
                this->m_attached_threads.end() ) );

            SIXTRL_ASSERT( std::binary_search(
                this->m_attached_threads.begin(),
                this->m_attached_threads.end(), tid ) );

            SIXTRL_ASSERT( !std::binary_search(
                this->m_attached_threads.begin(),
                this->m_attached_threads.end(), thread_id_t{} ) );

            SIXTRL_ASSERT( this->num_attached_threads( lock ) > st_size_t{ 0 } );

            auto range = std::equal_range(
                this->m_attached_threads.begin(),
                this->m_attached_threads.end(), tid );

            SIXTRL_ASSERT( range.first != this->m_attached_threads.end() );
            SIXTRL_ASSERT( range.first != range.second );

            this->m_attached_threads.erase( range.first, range.second );

            SIXTRL_ASSERT( std::is_sorted(
                this->m_attached_threads.begin(),
                this->m_attached_threads.end() ) );

            SIXTRL_ASSERT( !std::binary_search(
                this->m_attached_threads.begin(),
                this->m_attached_threads.end(), tid ) );

            SIXTRL_ASSERT( !std::binary_search(
                this->m_attached_threads.begin(),
                this->m_attached_threads.end(), thread_id_t{} ) );

            status = st::STATUS_SUCCESS;
        }

        return status;
    }
} /* ns: SIXTRL_CXX_NAMESPACE */

/* ************************************************************************* */

void NS(Context_delete)(
    ::NS(BaseContext)* SIXTRL_RESTRICT ctx ) SIXTRL_NOEXCEPT
{
    delete ctx;
}

#endif /* C++, Host */
