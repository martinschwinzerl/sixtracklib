#ifndef SIXTRACKLIB_COMMON_BE_CAVITY_BE_CAVITY_C99_H__
#define SIXTRACKLIB_COMMON_BE_CAVITY_BE_CAVITY_C99_H__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"

#if defined( __cplusplus )

#include "sixtracklib/common/beam_elements/cavity/cavity_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

extern "C" {
#endif /* defined( __cplusplus ) */

typedef double NS(be_cavity_real_t);

typedef struct NS(Cavity)
{
    NS(be_cavity_real_t) voltage   SIXTRL_ALIGN( 8 );
    NS(be_cavity_real_t) frequency SIXTRL_ALIGN( 8 );
    NS(be_cavity_real_t) lag       SIXTRL_ALIGN( 8 );
}
NS(Cavity);

#include "sixtracklib/common/beam_elements/cavity/cavity_api.h"

#if defined( __cplusplus )
}

namespace sixtrack_cxx
{
    template<> struct ObjDataStoreTraits< ::NS(Cavity) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_CAVITY;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout()
        {
            return true;
        }
    };

    template<> struct ObjDataTrackTraits< ::NS(Cavity) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_CAVITY;
        }
    };

    template<> struct CavityTraits< ::NS(Cavity) >
    {
        typedef ::NS(be_cavity_real_t) real_t;
    };
}

#endif /* C++ */

#endif /* SIXTRACKLIB_COMMON_BE_CAVITY_BE_CAVITY_C99_H__ */
/* end: */
