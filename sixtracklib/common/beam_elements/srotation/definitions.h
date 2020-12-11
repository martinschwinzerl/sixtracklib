#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_DEFINITIONS_H__

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
    typedef enum { BE_SROTATION_IMPL_DEFAULT = 0 } be_srotation_impl_t;

    template< class SRotationT >
    struct ObjDataSRotationTraits
    {
        static constexpr bool is_type = false;
        static constexpr be_srotation_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_SROTATION_IMPL_DEFAULT;
    };

    template< class SRotationT >
    constexpr bool ObjDataSRotationTraits< SRotationT >::is_type;

    template< class SRotationT >
    constexpr be_srotation_impl_t ObjDataSRotationTraits<
        SRotationT >::implementation;

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool SRotation_is_type(
        SIXTRL_BE_ARGPTR_DEC const SRotationT *const = SIXTRL_NULLPTR
    ) SIXTRL_NOEXCEPT
    {
        return ObjDataSRotationTraits< SRotationT >::is_type;
    }

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool SRotation_impl_default(
        SIXTRL_BE_ARGPTR_DEC const SRotationT *const = SIXTRL_NULLPTR
    ) SIXTRL_NOEXCEPT
    {
        return ObjDataSRotationTraits< SRotationT >::implementation ==
            SIXTRL_CXX_NAMESPACE::BE_SROTATION_IMPL_DEFAULT;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class SRotationT >
    struct SRotationTraits
    {
        typedef SIXTRL_CXX_NAMESPACE::be_real_t real_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();
    };

    template< class SRotationT >
    constexpr arch_size_t SRotationTraits< SRotationT >::real_alignment;
}
#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_DEFINITIONS_H__ */
