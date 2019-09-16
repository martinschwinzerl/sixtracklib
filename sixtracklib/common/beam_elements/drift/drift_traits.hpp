#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_TRAITS_CXX_HPP__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< class BeObjData >
    struct DriftExactTraits
    {
        typedef typename BeObjData::real_t real_t;
    };

    template< class BeObjData >
    struct DriftTraits
    {
        typedef typename BeObjData::real_t real_t;
    };
}

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_TRAITS_CXX_HPP__ */
