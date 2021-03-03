#ifndef SIXTRACKLIB_COMMON_INTERNAL_THREAD_ID_H__
#define SIXTRACKLIB_COMMON_INTERNAL_THREAD_ID_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <thread>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class ThreadId
    {
        public:

        using thread_id_type = std::thread::id;

        SIXTRL_HOST_FN static ThreadId ILLEGAL_TYPE() {
            return ThreadId{ thread_id_type{} }; }

        SIXTRL_HOST_FN ThreadId();
        SIXTRL_HOST_FN ThreadId( thread_id_type const tid ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN ThreadId( ThreadId const& ) = default;
        SIXTRL_HOST_FN ThreadId( ThreadId&& ) = default;

        SIXTRL_HOST_FN ThreadId& operator=( ThreadId const& ) = default;
        SIXTRL_HOST_FN ThreadId& operator=( ThreadId&& ) = default;

        SIXTRL_HOST_FN ~ThreadId() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN thread_id_type operator()() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_legal() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN friend bool operator==(
            ThreadId const& SIXTRL_RESTRICT_REF lhs,
            ThreadId const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            return lhs.m_thread_id == rhs.m_thread_id;
        }

        SIXTRL_HOST_FN friend bool operator!=(
            ThreadId const& SIXTRL_RESTRICT_REF lhs,
            ThreadId const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            return lhs.m_thread_id != rhs.m_thread_id;
        }

        SIXTRL_HOST_FN friend bool operator<(
            ThreadId const& SIXTRL_RESTRICT_REF lhs,
            ThreadId const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            return lhs.m_thread_id < rhs.m_thread_id;
        }

        SIXTRL_HOST_FN friend bool operator<=(
            ThreadId const& SIXTRL_RESTRICT_REF lhs,
            ThreadId const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            return lhs.m_thread_id <= rhs.m_thread_id;
        }

        SIXTRL_HOST_FN friend bool operator>(
            ThreadId const& SIXTRL_RESTRICT_REF lhs,
            ThreadId const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            return lhs.m_thread_id > rhs.m_thread_id;
        }

        SIXTRL_HOST_FN friend bool operator>=(
            ThreadId const& SIXTRL_RESTRICT_REF lhs,
            ThreadId const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            return lhs.m_thread_id >= rhs.m_thread_id;
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN friend bool operator==(
            ThreadId const& SIXTRL_RESTRICT_REF lhs,
            thread_id_type const rhs ) SIXTRL_NOEXCEPT
        {
            return lhs.m_thread_id == rhs;
        }

        SIXTRL_HOST_FN friend bool operator!=(
            ThreadId const& SIXTRL_RESTRICT_REF lhs,
            thread_id_type const rhs ) SIXTRL_NOEXCEPT
        {
            return lhs.m_thread_id != rhs;
        }

        SIXTRL_HOST_FN friend bool operator<(
            ThreadId const& SIXTRL_RESTRICT_REF lhs,
            thread_id_type const rhs ) SIXTRL_NOEXCEPT
        {
            return lhs.m_thread_id < rhs;
        }

        SIXTRL_HOST_FN friend bool operator<=(
            ThreadId const& SIXTRL_RESTRICT_REF lhs,
            thread_id_type const rhs ) SIXTRL_NOEXCEPT
        {
            return lhs.m_thread_id <= rhs;
        }

        SIXTRL_HOST_FN friend bool operator>(
            ThreadId const& SIXTRL_RESTRICT_REF lhs,
            thread_id_type const rhs ) SIXTRL_NOEXCEPT
        {
            return lhs.m_thread_id > rhs;
        }

        SIXTRL_HOST_FN friend bool operator>=(
            ThreadId const& SIXTRL_RESTRICT_REF lhs,
            thread_id_type const rhs ) SIXTRL_NOEXCEPT
        {
            return lhs.m_thread_id >= rhs;
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN friend bool operator==( thread_id_type const lhs,
            ThreadId const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            return lhs == rhs.m_thread_id;
        }

        SIXTRL_HOST_FN friend bool operator!=( thread_id_type const lhs,
            ThreadId const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            return lhs != rhs.m_thread_id;
        }

        SIXTRL_HOST_FN friend bool operator<( thread_id_type const lhs,
            ThreadId const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            return lhs < rhs.m_thread_id;
        }

        SIXTRL_HOST_FN friend bool operator<=( thread_id_type const lhs,
            ThreadId const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            return lhs <= rhs.m_thread_id;
        }

        SIXTRL_HOST_FN friend bool operator>( thread_id_type const lhs,
            ThreadId const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            return lhs > rhs.m_thread_id;
        }

        SIXTRL_HOST_FN friend bool operator>=( thread_id_type const lhs,
            ThreadId const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            return lhs >= rhs.m_thread_id;;
        }

        private:

        thread_id_type m_thread_id;
    };
} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::ThreadId NS(ThreadId);
#else /* !defined( __cplusplus ) || defined( _GPUCODE ) */
typedef void NS(ThreadId);
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_INTERNAL_THREAD_ID_H__ */
