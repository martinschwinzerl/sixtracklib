#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_DATA_CXX_HPP__

#include <cstddef>

#include "sixtracklib/common/definitions.h"

#include "sixtracklib/common/beam_elements/cavity/cavity_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/internal/math_constant_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename R, std::size_t RAlign =
        SIXTRL_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign() >
    struct CavityData
    {
        typedef R real_t;

        static SIXTRL_FN constexpr std::size_t
        RealAlignment() { return RAlign; }

        real_t  voltage     SIXTRL_ALIGN( RAlign );
        real_t  frequency   SIXTRL_ALIGN( RAlign );
        real_t  lag         SIXTRL_ALIGN( RAlign );
    };

    template<>
    struct ObjDataStoreTraits< CavityData< double > >
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

    template< class R, std::size_t RealAlign >
    struct ObjDataTrackTraits< CavityData< R, RealAlign > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_CAVITY;
        }
    };
}

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_DATA_CXX_HPP__ */
/* end: */
