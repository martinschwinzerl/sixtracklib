#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DEFINITIONS_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
    #if defined( __cplusplus )
        #include <type_traits>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_BE_DRIFT_TRACK_TYPE_NONE )
    #define SIXTRL_BE_DRIFT_TRACK_TYPE_NONE 0u
#endif /* !defined( SIXTRL_BE_DRIFT_TRACK_TYPE_NONE ) */

#if !defined( SIXTRL_BE_DRIFT_TRACK_TYPE_SIMPLE )
    #define SIXTRL_BE_DRIFT_TRACK_TYPE_SIMPLE 1u
#endif /* !defined( SIXTRL_BE_DRIFT_TRACK_TYPE_SIMPLE ) */

#if !defined( SIXTRL_BE_DRIFT_TRACK_TYPE_EXACT )
    #define SIXTRL_BE_DRIFT_TRACK_TYPE_EXACT 2u
#endif /* !defined( SIXTRL_BE_DRIFT_TRACK_TYPE_EXACT ) */

#if !defined( SIXTRL_BE_DRIFT_TRACK_TYPE_ILLEGAL )
    #define SIXTRL_BE_DRIFT_TRACK_TYPE_ILLEGAL 255u
#endif /* !defined( SIXTRL_BE_DRIFT_TRACK_TYPE_ILLEGAL ) */

#if !defined( SIXTRL_BE_DRIFT_TRACK_TYPE_DEFAULT )
    #define SIXTRL_BE_DRIFT_TRACK_TYPE_DEFAULT 1u
#endif /* !defined( SIXTRL_BE_DRIFT_TRACK_TYPE_DEFAULT ) */


#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

typedef SIXTRL_INT64_T NS(be_drift_track_type_t);

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(be_drift_track_type_t)
    NS(BE_DRIFT_TRACK_TYPE_NONE) = ( NS(be_drift_track_type_t)
        )SIXTRL_BE_DRIFT_TRACK_TYPE_NONE;

SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(be_drift_track_type_t)
    NS(BE_DRIFT_TRACK_TYPE_SIMPLE) = ( NS(be_drift_track_type_t)
        )SIXTRL_BE_DRIFT_TRACK_TYPE_SIMPLE;

SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(be_drift_track_type_t)
    NS(BE_DRIFT_TRACK_TYPE_EXACT) = ( NS(be_drift_track_type_t)
        )SIXTRL_BE_DRIFT_TRACK_TYPE_EXACT;

SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(be_drift_track_type_t)
    NS(BE_DRIFT_TRACK_TYPE_ILLEGAL) = ( NS(be_drift_track_type_t)
        )SIXTRL_BE_DRIFT_TRACK_TYPE_ILLEGAL;

SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(be_drift_track_type_t)
    NS(BE_DRIFT_TRACK_TYPE_DEFAULT) = ( NS(be_drift_track_type_t)
        )SIXTRL_BE_DRIFT_TRACK_TYPE_DEFAULT;

#endif /* GPUCODE */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef enum { BE_DRIFT_IMPL_DEFAULT = 0 } be_drift_impl_t;

    /* --------------------------------------------------------------------- */

    typedef NS(be_drift_track_type_t) be_drift_track_type_t;

    static constexpr be_drift_track_type_t BE_DRIFT_TRACK_TYPE_NONE =
        be_drift_track_type_t{ SIXTRL_BE_DRIFT_TRACK_TYPE_NONE };

    static constexpr be_drift_track_type_t BE_DRIFT_TRACK_TYPE_SIMPLE =
        be_drift_track_type_t{ SIXTRL_BE_DRIFT_TRACK_TYPE_SIMPLE };

    static constexpr be_drift_track_type_t BE_DRIFT_TRACK_TYPE_EXACT =
        be_drift_track_type_t{ SIXTRL_BE_DRIFT_TRACK_TYPE_EXACT };

    static constexpr be_drift_track_type_t BE_DRIFT_TRACK_TYPE_ILLEGAL =
        be_drift_track_type_t{ SIXTRL_BE_DRIFT_TRACK_TYPE_ILLEGAL };

    static constexpr be_drift_track_type_t BE_DRIFT_TRACK_TYPE_DEFAULT =
        be_drift_track_type_t{ SIXTRL_BE_DRIFT_TRACK_TYPE_DEFAULT };

    /* --------------------------------------------------------------------- */

    template< class DriftT >
    struct ObjDataDriftTraits
    {
        static constexpr bool is_type = false;
        static constexpr be_drift_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_DRIFT_IMPL_DEFAULT;
    };

    template< class DriftT >
    constexpr bool ObjDataDriftTraits< DriftT >::is_type;

    template< class DriftT >
    constexpr be_drift_impl_t ObjDataDriftTraits< DriftT >::implementation;

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool Drift_is_type(
        SIXTRL_BE_ARGPTR_DEC const DriftT *const SIXTRL_RESTRICT /* elem */
            = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataDriftTraits< typename std::decay<
            DriftT >::type >::is_type;
    }

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool Drift_impl_default(
        SIXTRL_BE_ARGPTR_DEC const DriftT *const SIXTRL_RESTRICT /* elem */
            = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataDriftTraits< typename std::decay< DriftT >::type
            >::implementation == SIXTRL_CXX_NAMESPACE::BE_DRIFT_IMPL_DEFAULT;
    }

    /* --------------------------------------------------------------------- */

    template< class DriftT > struct DriftTraits {};
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DEFINITIONS_H__ */
