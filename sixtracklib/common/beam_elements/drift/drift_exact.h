#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_EXACT_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_EXACT_C99_H__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"
#include "sixtracklib/common/beam_elements/drift/definitions.h"

#if defined( __cplusplus )

#include "sixtracklib/common/beam_elements/drift/drift_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

extern "C" {
#endif /* defined( __cplusplus ) */

typedef struct NS(DriftExact)
{
    NS(be_drift_real_t) length SIXTRL_ALIGN( 8 ); /* [m] */
}
NS(DriftExact);

#if defined( __cplusplus )
}
#endif /* C++, Host */

#include "sixtracklib/common/beam_elements/drift/drift_exact_api.h"

#if defined( __cplusplus ) && !defined( _GPUCODE )

namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataStoreTraits< ::NS(DriftExact) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT_EXACT;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout() { return true; }
    };

    template<> struct ObjDataTrackTraits< ::NS(DriftExact) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT_EXACT;
        }
    };

    template<> struct DriftExactTraits< ::NS(DriftExact) >
    {
        typedef ::NS(be_drift_real_t) real_t;
    };
}

#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_EXACT_DATA_C99_H__ */

/* end: sixtracklib/common/beam_elements/drift/drift_exact.h */
