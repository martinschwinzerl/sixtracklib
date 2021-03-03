#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/thread_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using thread_id_type = st::ThreadId::thread_id_type;
    }

    ThreadId::ThreadId() : m_thread_id( std::this_thread::get_id() ) {}

    ThreadId::ThreadId( thread_id_type const tid ) SIXTRL_NOEXCEPT :
        m_thread_id( tid ) {}

    thread_id_type ThreadId::operator()() const SIXTRL_NOEXCEPT {
        return this->m_thread_id; }

    bool ThreadId::is_legal() const SIXTRL_NOEXCEPT {
        return ( this->m_thread_id != thread_id_type{} ); }

} /* end: namespace SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
