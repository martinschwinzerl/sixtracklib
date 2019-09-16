#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DIPOLE_EDGE_DIPOLE_EDGE_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DIPOLE_EDGE_DIPOLE_EDGE_DATA_CXX_HPP__

#include <cstddef>

#include "sixtracklib/sixtracklib.hpp"
#include "sixtracklib/common/beam_elements/dipedge/dipedge_traits.hpp"
#include "sixtracklib/common/beam_elements/dipedge/dipedge.h"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename R, std::size_t RAlign =
        SIXTRL_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign()>
    struct BeDipoleEdgeData
    {
        typedef R real_t;

        static SIXTRL_FN constexpr std::size_t
        RealAlignment() { return RAlign; }

        real_t r21 SIXTRL_ALIGN( RAlign );
        real_t r43 SIXTRL_ALIGN( RAlign );
    };

    template<> struct ObjDataStoreTraits< BeDipoleEdgeData< double, 8u > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DIPEDGE;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout() { return true; }
    };

    template< class R, std::size_t RealAlign >
    struct ObjDataTrackTraits< BeDipoleEdgeData< R, RealAlign > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DIPEDGE;
        }
    };
}

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DIPOLE_EDGE_DIPOLE_EDGE_DATA_CXX_HPP__ */
/* end: */
