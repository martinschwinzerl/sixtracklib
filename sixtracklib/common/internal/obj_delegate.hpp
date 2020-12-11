#ifndef SIXTRACKLIB_COMMON_INTERNAL_OBJ_DATA_DELEGATE_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_OBJ_DATA_DELEGATE_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/obj_illegal_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class E, store_backend_t StoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
              typename Enabled = void >
    struct ObjDataDelegateTraits
    {
        typedef IllegalType delegate_t;
    };

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class E, store_backend_t StoreT >
    SIXTRL_STATIC SIXTRL_FN constexpr
    bool ObjData_has_delegate() SIXTRL_NOEXCEPT
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

    /* --------------------------------------------------------------------- */
}
#endif /* C++ */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_DATA_DELEGATE_CXX_HPP__ */
