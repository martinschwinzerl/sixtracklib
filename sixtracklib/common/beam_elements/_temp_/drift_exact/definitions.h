#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DEFINITIONS_H__

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
    template< class DriftExactT >
    struct ObjDataDriftExactTraits
    {
        static constexpr bool is_drift_exact = false;
    };

    template< class DriftExactT >
    constexpr bool ObjDataDriftExactTraits< DriftExactT >::is_drift_exact;

    template< class DriftExactT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool ObjData_is_drift_exact(
        SIXTRL_BE_ARGPTR_DEC const DriftExactT *const SIXTRL_RESTRICT /* elem */
            = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataDriftExactTraits< DriftExactT >::is_drift_exact;
    }

    /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class DriftExactT > struct DriftExactTraits
    {
        typedef SIXTRL_CXX_NAMESPACE::be_real_t real_t;
        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();
    };

    template< class DriftExactT >
    constexpr arch_size_t DriftExactTraits< DriftExactT >::real_alignment;
}
#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DEFINITIONS_H__ */
