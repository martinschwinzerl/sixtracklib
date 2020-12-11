#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_DEFINITIONS_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef enum { BE_CAVITY_IMPL_DEFAULT = 0 } be_cavity_impl_t;

    template< class CavityT >
    struct ObjDataCavityTraits
    {
        static constexpr bool is_type = false;
        static constexpr be_cavity_impl_t implementation =
                            SIXTRL_CXX_NAMESPACE::BE_CAVITY_IMPL_DEFAULT;
    };

    template< class CavityT >
    constexpr bool ObjDataCavityTraits< CavityT >::is_type;

    template< class CavityT >
    constexpr be_cavity_impl_t ObjDataCavityTraits< CavityT >::implementation;

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool Cavity_is_type(
        SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT /* elem */
            = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataCavityTraits< CavityT >::is_type;
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool Cavity_impl_default(
        SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT /* elem */
            = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataCavityTraits< CavityT >::implementation ==
            SIXTRL_CXX_NAMESPACE::BE_CAVITY_IMPL_DEFAULT;
    }

    /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class CavityT > struct CavityTraits
    {
        typedef SIXTRL_CXX_NAMESPACE::be_real_t real_t;
        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();
    };

    template< class CavityT >
    constexpr arch_size_t CavityTraits< CavityT >::real_alignment;
}
#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_DEFINITIONS_H__ */
