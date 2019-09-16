#ifndef SIXTRACKLIB_COMMON_BE_DIPOLE_EDGE_BE_DIPOLE_EDGE_C99_H__
#define SIXTRACKLIB_COMMON_BE_DIPOLE_EDGE_BE_DIPOLE_EDGE_C99_H__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"

#if defined( __cplusplus )

#include "sixtracklib/common/be/dipedge/dipedge_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

extern "C" {
#endif /* defined( __cplusplus ) */

typedef double NS(be_dipedge_real_t);

typedef struct NS(DipoleEdge)
{
    NS(be_dipedge_real_t) r21 SIXTRL_ALIGN( 8 );
    NS(be_dipedge_real_t) r43 SIXTRL_ALIGN( 8 );
}
NS(DipoleEdge);

#if defined( __cplusplus )
}
#endif /* C++ */

#include "sixtracklib/common/beam_elements/dipedge/dipedge_api.h"

#if defined( __cplusplus ) && !defined( _GPUCODE )

namespace sixtrack_cxx
{
    template<> struct ObjDataStoreTraits< ::NS(DipoleEdge) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DIPEDGE;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout()
        {
            return true;
        }
    };

    template<> struct ObjDataTrackTraits< ::NS(DipoleEdge) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DIPEDGE;
        }
    };

    template<> struct DipoleEdgeTraits< ::NS(DipoleEdge) >
    {
        typedef ::NS(be_dipedge_real_t)   real_t;
    };
}

#endif /* c++ */

#endif /* SIXTRACKLIB_COMMON_BE_DIPOLE_EDGE_BE_DIPOLE_EDGE_C99_H__ */
/* end: */
