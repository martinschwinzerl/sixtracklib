#ifndef SIXTRACKLIB_COMMON_BE_LIMIT_BE_LIMIT_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_LIMIT_BE_LIMIT_TRAITS_CXX_HPP__

namespace sixtrack_cxx
{
    template< class BeObjData >
    struct LimitRectTraits
    {
        typedef typename BeObjData::real_t real_t;
    };

    template< class BeObjData >
    struct LimitEllipseTraits
    {
        typedef typename BeObjData::real_t real_t;
    };
}

#endif /* SIXTRACKLIB_COMMON_BE_LIMIT_BE_LIMIT_TRAITS_CXX_HPP__ */

/* end: sixtracklib/common/beam_elements/limit/limit_traits.hpp */
