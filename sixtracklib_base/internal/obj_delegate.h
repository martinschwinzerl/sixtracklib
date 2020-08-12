#ifndef SIXTRACKLIB_BASE_INTERNAL_OBJ_DELEGATE_H__
#define SIXTRACKLIB_BASE_INTERNAL_OBJ_DELEGATE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/definitions.h"
    #include "sixtracklib_base/internal/obj_store_traits.h"
    #include "sixtracklib_base/internal/obj_illegal_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class E, store_backend_t StoreT =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename Enabled = void >
    struct  ObjDataDelegateTraits
    {
        typedef IllegalType delegate_t;
    };

    template< class E, store_backend_t StoreT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool ObjData_has_delegate() SIXTRL_NOEXCEPT
    {
        return !SIXTRL_CXX_NAMESPACE::ObjData_is_specific_illegal_type<
            typename ObjDataDelegateTraits< E, StoreT >::delegate_t >();
    }

    template< class E, store_backend_t StoreT >
    SIXTRL_STATIC SIXTRL_FN constexpr
    bool ObjData_has_not_delegate() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_is_specific_illegal_type<
            typename ObjDataDelegateTraits< E, StoreT >::delegate_t >();
    }
}
#endif /* C++ */
#endif /* SIXTRACKLIB_BASE_INTERNAL_OBJ_DELEGATE_H__ */
