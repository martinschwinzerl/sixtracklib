#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/internal/thread_lock.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using ulock_t = st::ThreadUniqueLock;
    }

    ulock_t::ThreadUniqueLock() : m_lock() {}

    ulock_t::ThreadUniqueLock(
        ulock_t::lockable_type& SIXTRL_RESTRICT_REF lockable ) :
        m_lock( lockable.raw_lockable() ) {}


    ulock_t::ThreadUniqueLock( lockable_type* SIXTRL_RESTRICT_REF lockable ) :
        m_lock()
    {
        if( lockable != nullptr )
        {
            this->m_lock = ulock_t::internal_lock_type(
                lockable->raw_lockable() );
        }
    }
}


::NS(ThreadLockable)* NS(TheadLockable_create)( void ) {
    return new SIXTRL_CXX_NAMESPACE::ThreadLockable; }

void NS(TheadLockable_delete)( ::NS(ThreadLockable)* SIXTRL_RESTRICT lock ) {
    delete lock; }


::NS(ThreadUniqueLock)* NS(TheadUniqueLock_create)(
    ::NS(ThreadLockable)* SIXTRL_RESTRICT_REF lockable ) {
    return new SIXTRL_CXX_NAMESPACE::ThreadUniqueLock( lockable );
}

void NS(ThreadUniqueLock_delete)(
    ::NS(ThreadUniqueLock)* SIXTRL_RESTRICT ptr_lock ) SIXTRL_NOEXCEPT {
    delete ptr_lock; }

#endif /* C++, Host */
