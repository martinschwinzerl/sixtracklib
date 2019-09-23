#ifndef SIXTRACKLIB_COMMON_BE_LIMIT_ELLIPSE_BE_LIMIT_ELLIPSE_C99_H__
#define SIXTRACKLIB_COMMON_BE_LIMIT_ELLIPSE_BE_LIMIT_ELLIPSE_C99_H__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"
#include "sixtracklib/common/beam_elements/limit/definitions.h"

#if defined( __cplusplus )

#include "sixtracklib/common/beam_elements/limit/limit_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

extern "C" {
#endif /* defined( __cplusplus ) */

typedef NS(particle_real_t) NS(be_limit_ellipse_real_t);

typedef struct NS(LimitEllipse)
{
    NS(be_limit_ellipse_real_t) a_squ   SIXTRL_ALIGN( 8 );
    NS(be_limit_ellipse_real_t) b_squ   SIXTRL_ALIGN( 8 );
    NS(be_limit_ellipse_real_t) a_b_squ SIXTRL_ALIGN( 8 );
}
NS(LimitEllipse);

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */

#include "sixtracklib/common/beam_elements/limit_ellipse_api.h"

#if defined( __cplusplus )
extern "C" {
#endif /* defined( __cplusplus ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataStoreTraits< ::NS(LimitEllipse) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_ELLIPSE;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout() { return true; }
    };

    template<> struct ObjDataTrackTraits< ::NS(LimitEllipse) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_ELLIPSE;
        }
    };

    template<> struct LimitEllipseTraits< ::NS(LimitEllipse) >
    {
        typedef ::NS(be_limit_ellipse_real_t) real_t;
    };
}

#endif /* c++ */

#endif /* SIXTRACKLIB_COMMON_BE_LIMIT_ELLIPSE_BE_LIMIT_ELLIPSE_C99_H__ */

/* end: sixtracklib/common/beam_elements/limit/limit_ellipse.h */
