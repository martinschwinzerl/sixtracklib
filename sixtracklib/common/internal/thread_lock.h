#ifndef SIXTRACKLIB_COMMON_INTERNAL_THREAD_SCOPED_LOCK_H__
#define SIXTRACKLIB_COMMON_INTERNAL_THREAD_SCOPED_LOCK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <mutex>
    #include <thread>
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class ThreadLockable
    {
        public:

        using raw_lockable_type = std::mutex;

        SIXTRL_HOST_FN ThreadLockable() = default;
        SIXTRL_HOST_FN ThreadLockable( ThreadLockable const& ) = delete;
        SIXTRL_HOST_FN ThreadLockable( ThreadLockable&& ) = delete;

        SIXTRL_HOST_FN ThreadLockable& operator=( ThreadLockable const& ) = delete;
        SIXTRL_HOST_FN ThreadLockable& operator=( ThreadLockable&& ) = delete;

        SIXTRL_HOST_FN ~ThreadLockable() = default;

        SIXTRL_HOST_FN void lock() { this->m_lockable.lock(); }
        SIXTRL_HOST_FN bool try_lock() { return this->m_lockable.try_lock(); }
        SIXTRL_HOST_FN void unlock() {  this->m_lockable.unlock(); }

        SIXTRL_HOST_FN raw_lockable_type::native_handle_type native_handle() {
            return this->m_lockable.native_handle(); }

        SIXTRL_HOST_FN raw_lockable_type*
        ptr_raw_lockable() const SIXTRL_NOEXCEPT
        {
            return &this->m_lockable;
        }

        SIXTRL_HOST_FN raw_lockable_type& raw_lockable() const SIXTRL_NOEXCEPT
        {
            return this->m_lockable;
        }

        private:

        mutable raw_lockable_type m_lockable;
    };

    class ThreadUniqueLock
    {
        public:

        using raw_lockable_type = ThreadLockable::raw_lockable_type;
        using lockable_type = ThreadLockable;

        SIXTRL_HOST_FN ThreadUniqueLock();

        SIXTRL_HOST_FN explicit ThreadUniqueLock(
            lockable_type& SIXTRL_RESTRICT_REF lockable );

        SIXTRL_HOST_FN explicit ThreadUniqueLock(
            lockable_type* SIXTRL_RESTRICT lockable );

        template< class Arg, class... InitArgs,
            typename = typename std::enable_if<
                !std::is_same< typename std::decay< Arg >::type,
                    SIXTRL_CXX_NAMESPACE::ThreadUniqueLock >::value &&
                !std::is_same< typename std::decay< Arg >::type,
                    SIXTRL_CXX_NAMESPACE::ThreadLockable >::value,
                void >::type >
        SIXTRL_HOST_FN ThreadUniqueLock( Arg&& arg0, InitArgs&&... init_args ) :
            m_lock( std::forward< Arg >( arg0 ),
                    std::forward< InitArgs >( init_args )... )
        {

        }

        SIXTRL_HOST_FN ThreadUniqueLock( ThreadUniqueLock const& ) = delete;
        SIXTRL_HOST_FN ThreadUniqueLock& operator=(
            ThreadUniqueLock const& ) = delete;

        SIXTRL_HOST_FN ThreadUniqueLock( ThreadUniqueLock&& ) = default;
        SIXTRL_HOST_FN ThreadUniqueLock& operator=(
            ThreadUniqueLock&& ) = default;

        SIXTRL_HOST_FN ~ThreadUniqueLock() = default;

        SIXTRL_HOST_FN void unlock() { this->m_lock.unlock(); }
        SIXTRL_HOST_FN void lock() { this->m_lock.lock(); }
        SIXTRL_HOST_FN bool try_lock() { return this->m_lock.try_lock(); }

        template< class... LockArgs >
        SIXTRL_HOST_FN bool try_lock_for( LockArgs&&... args ) {
            return this->m_lock.try_lock_for(
                std::forward< LockArgs >( args )... );
        }

        template< class... LockArgs >
        SIXTRL_HOST_FN bool try_lock_until( LockArgs&&... args ) {
            return this->m_lock.try_lock_until(
                std::forward< LockArgs >( args )... );
        }

        friend SIXTRL_HOST_FN void swap(
            ThreadUniqueLock& SIXTRL_RESTRICT_REF lhs,
            ThreadUniqueLock& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            using std::swap;
            swap( lhs.m_lock, rhs.m_lock );
        }

        SIXTRL_HOST_FN raw_lockable_type* release() SIXTRL_NOEXCEPT {
            return this->m_lock.release(); }

        SIXTRL_HOST_FN raw_lockable_type* mutex() const SIXTRL_NOEXCEPT {
            return this->m_lock.mutex(); }

        SIXTRL_HOST_FN bool owns_lock() const SIXTRL_NOEXCEPT {
            return this->m_lock.owns_lock(); }

        SIXTRL_HOST_FN explicit operator bool() const SIXTRL_NOEXCEPT {
            return ( this->m_lock ) ? true : false;
        }

        private:

        using internal_lock_type = std::unique_lock< raw_lockable_type >;

        internal_lock_type m_lock;
    };
} /* ns: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                   Exported Plugin C-API :: Types                !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )

typedef SIXTRL_CXX_NAMESPACE::ThreadLockable NS(ThreadLockable);
typedef SIXTRL_CXX_NAMESPACE::ThreadUniqueLock NS(ThreadUniqueLock);

#else /* defined( _GPUCODE ) || !defined( __cplusplus ) */

typedef void NS(ThreadLockable);
typedef void NS(ThreadUniqueLock);

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                Exported Plugin C-API :: Functions               !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

SIXTRL_HOST_FN NS(ThreadLockable)* NS(TheadLockable_create)( void );
SIXTRL_HOST_FN void NS(TheadLockable_delete)( NS(ThreadLockable)* SIXTRL_RESTRICT );

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN NS(ThreadUniqueLock)*
NS(TheadUniqueLock_create)( NS(ThreadLockable)* SIXTRL_RESTRICT lockable );

SIXTRL_HOST_FN void NS(TheadUniqueLock_delete)(
    NS(ThreadUniqueLock)* SIXTRL_RESTRICT unique_lock ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_INTERNAL_THREAD_SCOPED_LOCK_H__ */
