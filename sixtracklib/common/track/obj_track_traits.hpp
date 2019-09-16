#ifndef SIXTRACKLIB_COMMON_TRACK_OBJ_TRACK_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_TRACK_OBJ_TRACK_TRAITS_CXX_HPP__

#include <type_traits>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"
#include "sixtracklib/common/track/definitions.h"

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ObjData > struct ObjDataTrackTraits
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_INVALID;
        }
    };

    template< class ObjData >
    SIXTRL_FN constexpr bool ObjData_can_be_tracked() SIXTRL_NOEXCEPT
    {
        return ( SIXTRL_CXX_NAMESPACE::ObjDataTrackTraits<
            ObjData >::ObjTypeId() !=
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_INVALID );
    }

    template< class PData, class BeData,
              SIXTRL_CXX_NAMESPACE::object_type_id_t OBJECT_ID >
    SIXTRL_FN constexpr bool CanBeTrackedAsParticlesOverObjectId()
    {
        return ( ( ObjDataTrackTraits< PData >::ObjTypeId() ==
                   SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_PARTICLE ) &&
                 ( ObjDataTrackTraits< BeData >::ObjTypeId() == OBJECT_ID ) );
    };

    template< class PData, class BeData,
        SIXTRL_CXX_NAMESPACE::object_type_id_t OBJECT_ID >
    using track_result_t = std::enable_if<
        SIXTRL_CXX_NAMESPACE::CanBeTrackedAsParticlesOverObjectId<
        PData, BeData, OBJECT_ID >(), SIXTRL_CXX_NAMESPACE::track_status_t >;
}

#endif /* SIXTRACKLIB_COMMON_TRACK_OBJ_TRACK_TRAITS_CXX_HPP__ */
/* end: sixtracklib/common/track/obj_track_traits.hpp */
