#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_DEFINITIONS_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/beam_elements/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef enum
    {
        BE_MULTIPOLE_IMPL_DEFAULT = 0,
        BE_MULTIPOLE_IMPL_STD_VECTOR = 1
    }
    be_multipole_impl_t;

    template< class MultipoleT >
    struct ObjDataMultipoleTraits
    {
        static constexpr bool is_type = false;
        static constexpr be_multipole_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_MULTIPOLE_IMPL_DEFAULT;
    };

    template< class MultipoleT >
    constexpr bool ObjDataMultipoleTraits< MultipoleT >::is_type;

    template< class MultipoleT >
    constexpr be_multipole_impl_t ObjDataMultipoleTraits<
        MultipoleT >::implementation;

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool Multipole_is_type(
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT
            /* elem */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataMultipoleTraits< MultipoleT >::is_type;
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool Multipole_impl_default(
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT
            /* elem */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataMultipoleTraits< MultipoleT >::implementation ==
            SIXTRL_CXX_NAMESPACE::BE_MULTIPOLE_IMPL_DEFAULT;
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr
    bool Multipole_impl_std_vector(
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT
            /* elem */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataMultipoleTraits< MultipoleT >::implementation ==
            SIXTRL_CXX_NAMESPACE::BE_MULTIPOLE_IMPL_STD_VECTOR;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class MultipoleT >
    struct MultipoleTraits
    {
        typedef SIXTRL_CXX_NAMESPACE::be_real_t  real_t;
        typedef SIXTRL_CXX_NAMESPACE::be_order_t order_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

        static constexpr arch_size_t order_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< order_t >();
    };
}
#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_DEFINITIONS_H__ */
