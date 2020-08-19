#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/internal/thread_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using this_t = st::ThreadId;
        using thread_id_t = this_t::thread_id_type;
    }

    this_t::ThreadId() : m_thread_id( std::this_thread::get_id() ) {}

    this_t::ThreadId( thread_id_t const tid ) SIXTRL_NOEXCEPT :
        m_thread_id( tid ) {}

    thread_id_t this_t::operator()() const SIXTRL_NOEXCEPT
    {
        return this->m_thread_id;
    }

    bool this_t::is_legal() const SIXTRL_NOEXCEPT
    {
        return ( this->m_thread_id != thread_id_t{} );
    }
}
#endif /* C++, Host */
