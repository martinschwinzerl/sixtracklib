#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/backends/mt_backend_obj_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using mt_base_type = st::MTBackendObjBase;
        using mt_ext_base_type = st::MTBackendObjBaseExtLockable;
        using guard_t = mt_base_type::guard_type;
        using lock_t  = mt_base_type::lockable_type;
    }

    lock_t* mt_base_type::ptr_lockable() const SIXTRL_NOEXCEPT {
        return &this->m_lockable; }

    lock_t& mt_base_type::lockable() const SIXTRL_NOEXCEPT {
        return this->m_lockable; }

    guard_t mt_base_type::create_lock() const {
        return guard_t{ this->m_lockable }; }

    bool mt_base_type::is_locked( guard_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT {
        return ( ( this->ptr_lockable() != nullptr ) &&
                 ( lock.mutex() == this->m_lockable.ptr_raw_lockable() ) &&
                 ( lock.owns_lock() ) );
    }

    lock_t* mt_ext_base_type::ptr_lockable() const SIXTRL_NOEXCEPT {
        return &this->m_ext_lockable; }

    lock_t& mt_ext_base_type::lockable() const SIXTRL_NOEXCEPT {
        return this->m_ext_lockable; }

    guard_t mt_ext_base_type::create_lock() const {
        return guard_t{ this->m_ext_lockable }; }

    bool mt_ext_base_type::is_locked( guard_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT {
        return ( ( this->ptr_lockable() != nullptr ) &&
                 ( lock.mutex() == this->m_ext_lockable.ptr_raw_lockable() ) &&
                 ( lock.owns_lock() ) );
    }

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
