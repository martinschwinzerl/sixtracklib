#ifndef SIXTRACKLIB_COMMON_BE_SROTATION_BE_SROTATION_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_SROTATION_BE_SROTATION_DATA_CXX_HPP__

#include <cstddef>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/beam_elements/srotation/definitions.h"
#include "sixtracklib/common/beam_elements/srotation/srotation_traits.hpp"
#include "sixtracklib/common/internal/math_constant_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename R, std::size_t RAlign =
        SIXTRL_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign()>
    struct SRotationData
    {
        typedef R real_t;

        static SIXTRL_FN constexpr std::size_t
        RealAlignment() { return RAlign; }

        real_t  cos_z SIXTRL_ALIGN( RAlign );
        real_t  sin_z SIXTRL_ALIGN( RAlign );
    };

    template<> struct ObjDataStoreTraits< SRotationData< double, 8u > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_SROTATION;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout() { return true; }
    };

    template< class R, std::size_t RealAlign >
    struct ObjDataTrackTraits< SRotationData< R, RealAlign > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_SROTATION;
        }
    };
}

#endif /* SIXTRACKLIB_COMMON_BE_SROTATION_BE_SROTATION_DATA_CXX_HPP__ */
/* end: sixtracklib/common/beam_elements/srotation/srotation_data.hpp */
