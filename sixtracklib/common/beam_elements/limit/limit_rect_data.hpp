#ifndef SIXTRACKLIB_COMMON_BE_LIMIT_RECT_BE_LIMIT_RECT_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_LIMIT_RECT_BE_LIMIT_RECT_DATA_CXX_HPP__

#include <cstddef>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/beam_elements/limit/definitions.h"
#include "sixtracklib/common/beam_elements/limit/limit_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace SIXTRACK_CXX_NAMESPACE
{
    template< typename R, std::size_t RAlign =
        SIXTRACK_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign()>
    struct LimitRectData
    {
        typedef R real_t;

        static SIXTRL_FN constexpr std::size_t
        RealAlignment() { return RAlign; }

        real_t min_x SIXTRL_ALIGN( RAlign );
        real_t max_x SIXTRL_ALIGN( RAlign );

        real_t min_y SIXTRL_ALIGN( RAlign );
        real_t max_y SIXTRL_ALIGN( RAlign );
    };

    template<> struct ObjDataStoreTraits< LimitRectData< double, 8u > >
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

    template< class R, std::size_t RealAlign >
    struct ObjDataTrackTraits< LimitRectData< R, RealAlign > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_RECT;
        }
    };
}

#endif /* SIXTRACKLIB_COMMON_BE_LIMIT_RECT_BE_LIMIT_RECT_DATA_CXX_HPP__ */

/* end: sixtracklib/common/beam_elements/limit/limit_rect_data.hpp */
