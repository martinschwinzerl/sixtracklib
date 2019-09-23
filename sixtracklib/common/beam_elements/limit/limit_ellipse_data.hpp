#ifndef SIXTRACKLIB_COMMON_BE_LIMIT_ELLIPSE_BE_LIMIT_ELLIPSE_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_LIMIT_ELLIPSE_BE_LIMIT_ELLIPSE_DATA_CXX_HPP__

#include <cstddef>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/track/definitions.h"
#include "sixtracklib/common/beam_elements/limit/limit_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename R, std::size_t RAlign =
        SIXTRL_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign() >
    struct LimitEllipseData
    {
        typedef R real_t;

        static SIXTRL_FN constexpr std::size_t
        RealAlignment() { return RAlign; }

        real_t a_squ   SIXTRL_ALIGN( RAlign );
        real_t b_squ   SIXTRL_ALIGN( RAlign );
        real_t a_b_squ SIXTRL_ALIGN( RAlign );
    };

    template<> struct ObjDataStoreTraits< LimitEllipseData< double, 8u > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_ELLIPSE;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout()
        {
            return true;
        }
    };

    template< class R, std::size_t RealAlign >
    struct ObjDataTrackTraits< LimitEllipseData< R, RealAlign > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_ELLIPSE;
        }
    };
}

#endif /* SIXTRACKLIB_COMMON_BE_LIMIT_ELLIPSE_BE_LIMIT_ELLIPSE_DATA_CXX_HPP__ */

/* end: sixtracklib/common/beam_elements/limit/limit_ellipse_data.hpp */
