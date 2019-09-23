#ifndef SIXTRACKLIB_COMMON_BE_SROTATION_BE_SROTATION_C99_H__
#define SIXTRACKLIB_COMMON_BE_SROTATION_BE_SROTATION_C99_H__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/track/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"

#if defined( __cplusplus )

#include "sixtracklib/common/beam_elements/srotation/definitions.hpp"
#include "sixtracklib/common/beam_elements/srotation/srotation_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

extern "C" {
#endif /* defined( __cplusplus ) */

typedef struct NS(SRotation)
{
    NS(be_srotation_real_t) cos_z SIXTRL_ALIGN( 8 );
    NS(be_srotation_real_t) sin_z SIXTRL_ALIGN( 8 );
}
NS(SRotation);

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */

#include "sixtracklib/common/beam_elements/srotation/srotation_api.h"

#if defined( __cplusplus )

namespace sixtrack_cxx
{
    template<> struct ObjDataStoreTraits< ::NS(SRotation) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_SROTATION;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout() { return true; }
    };

    template<> struct ObjDataTrackTraits< ::NS(SRotation) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_SROTATION;
        }
    };

    template<> struct SRotationTraits< ::NS(SRotation) >
    {
        typedef ::NS(be_srotation_real_t) real_t;
    };
}

#endif /* c++ */

#endif /* SIXTRACKLIB_COMMON_BE_SROTATION_BE_SROTATION_C99_H__ */
/* end: sixtracklib/common/beam_elements/srotation/srotation.h */
