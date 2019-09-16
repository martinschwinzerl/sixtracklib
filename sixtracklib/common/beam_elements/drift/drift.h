#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_C99_H__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"
#include "sixtracklib/common/beam_elements/drift/definitions.h"

#if defined( __cplusplus )

#include "sixtracklib/common/beam_elements/drift/drift_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

extern "C" {
#endif /* defined( __cplusplus ) */

typedef struct NS(Drift)
{
    NS(be_drift_real_t) length SIXTRL_ALIGN( 8 ); /* [m] */
}
NS(Drift);

#if defined( __cplusplus )
}
#endif /* C++ */

#include "sixtracklib/common/beam_elements/drift/drift_api.h"

#if !defined( __cplusplus ) && ( !defined( _GPUCODE ) )

namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataStoreTraits< ::NS(Drift) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout() { return true; }
    };

    template<> struct ObjDataTrackTraits< ::NS(Drift) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT;
        }
    };

    template<> struct DriftTraits< ::NS(Drift) >
    {
        typedef ::NS(be_drift_real_t) real_t;
    };
}

#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_C99_H__ */

/* end: cxx/common/particles/track_particle.h */
