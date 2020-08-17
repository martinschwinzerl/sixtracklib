#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/backend/backend_obj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using this_t = st::BaseBackendObj;
        using st_backend_id_t = this_t::backend_id_t;
        using st_class_id_t = this_t::class_id_t;
        using st_class_variant_t = this_t::class_variant_t;
        using st_status_t = this_t::status_type;
    }

    this_t::BaseBackendObj(
        st_backend_id_t const backend_id, st_class_id_t const class_id,
        st_class_variant_t const var ) SIXTRL_NOEXCEPT :
        m_backend_id( backend_id ), m_class_id( class_id ),
        m_class_variant_flags( var ) {}


    st_backend_id_t this_t::backend_id() const SIXTRL_NOEXCEPT {
        return this->m_backend_id; }

    st_class_id_t this_t::class_id() const SIXTRL_NOEXCEPT {
        return this->m_class_id; }

    st_class_variant_t this_t::class_variant_flags() const SIXTRL_NOEXCEPT {
        return this->m_class_variant_flags; }

    bool this_t::is_class_variant(
        st_class_variant_t const flags ) const SIXTRL_NOEXCEPT
    {
        return ( ( flags != st_class_variant_t{ 0 } ) &&
                 ( ( this->m_class_variant_flags & flags ) == flags ) );
    }

    st_status_t BaseBackendObj::set_backend_id(
        BaseBackendObj::backend_id_t const backend_id ) SIXTRL_NOEXCEPT
    {
        this->m_backend_id = backend_id;
        return st::STATUS_SUCCESS;
    }

    st_status_t BaseBackendObj::set_class_id(
        BaseBackendObj::class_id_t const class_id ) SIXTRL_NOEXCEPT
    {
        this->m_class_id = class_id;
        return st::STATUS_SUCCESS;
    }

    st_status_t BaseBackendObj::set_class_variant(
        BaseBackendObj::class_variant_t const class_variant ) SIXTRL_NOEXCEPT
    {
        this->m_class_variant_flags = class_variant;
        return st::STATUS_SUCCESS;
    }
}
#endif /* C++ */
