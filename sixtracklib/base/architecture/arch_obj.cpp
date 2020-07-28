#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/architecture/arch_obj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
    }

    BaseArchObj::status_t BaseArchObj::set_arch_id(
        BaseArchObj::arch_id_t const arch_id ) SIXTRL_NOEXCEPT
    {
        this->m_arch_id = arch_id;
        return st::STATUS_SUCCESS;
    }

    BaseArchObj::status_t BaseArchObj::set_class_id(
        BaseArchObj::class_id_t const class_id ) SIXTRL_NOEXCEPT
    {
        this->m_class_id = class_id;
        return st::STATUS_SUCCESS;
    }

    BaseArchObj::status_t BaseArchObj::set_class_variant(
        BaseArchObj::class_variant_t const class_variant ) SIXTRL_NOEXCEPT
    {
        this->m_class_variant_flags = class_variant;
        return st::STATUS_SUCCESS;
    }
}
#endif /* C++ */
