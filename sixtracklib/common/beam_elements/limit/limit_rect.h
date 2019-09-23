#ifndef SIXTRACKLIB_COMMON_BE_LIMIT_RECT_BE_LIMIT_RECT_C99_H__
#define SIXTRACKLIB_COMMON_BE_LIMIT_RECT_BE_LIMIT_RECT_C99_H__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/beam_elements/limit/definitions"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"

#if defined( __cplusplus )

#include "sixtracklib/common/beam_limits/limit/limit_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

extern "C" {
#endif /* defined( __cplusplus ) */

typedef NS(particle_real_t) NS(be_limit_rect_real_t);

typedef struct NS(LimitRect)
{
    NS(be_limit_rect_real_t) min_x SIXTRL_ALIGN( 8 );
    NS(be_limit_rect_real_t) max_x SIXTRL_ALIGN( 8 );

    NS(be_limit_rect_real_t) min_y SIXTRL_ALIGN( 8 );
    NS(be_limit_rect_real_t) max_y SIXTRL_ALIGN( 8 );
}
NS(LimitRect);

#if defined( __cplusplus )
}
#endif /* */

#include "sixtracklib/common/beam_elements/limit/limit_rect_api.h"

/* ------------------------------------------------------------------------- */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataStoreTraits< ::NS(LimitRect) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_RECT;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout()
        {
            return true;
        }
    };

    template<> struct ObjDataTrackTraits< ::NS(LimitRect) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_RECT;
        }
    };

    template<> struct LimitRectTraits< ::NS(LimitRect) >
    {
        typedef ::NS(be_limit_rect_real_t)   real_t;
    };
}

#endif /* c++ */

#endif /* SIXTRACKLIB_COMMON_BE_LIMIT_RECT_BE_LIMIT_RECT_C99_H__ */

/* end: /common/beam_elements/limit/limit_rect.h */
