#ifndef SIXTRACKLIB_COMMON_BE_DRIFT_DRIFT_EXACT_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_DRIFT_DRIFT_EXACT_DATA_CXX_HPP__

#include <cstdlib>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"
#include "sixtracklib/common/beam_elements/drift/definitions.h"

#include "sixtracklib/common/beam_elements/drift/drift_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, std::size_t RAlign =
        SIXTRL_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign() >
    struct DriftExactData
    {
        typedef R real_t;

        static SIXTRL_FN constexpr std::size_t
        RealAlignment() { return RAlign; }

        real_t length SIXTRL_ALIGN( RAlign );
    };

    template<> struct ObjDataStoreTraits< DriftExactData< double > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT_EXACT;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout() { return true; }
    };

    template< class R, std::size_t RealAlign >
    struct ObjDataTrackTraits< DriftExactData< R, RealAlign > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT_EXACT;
        }
    };
}

#endif /* SIXTRACKLIB_COMMON_BE_DRIFT_DRIFT_EXACT_DATA_CXX_HPP__ */
/* end: */
