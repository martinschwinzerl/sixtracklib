#ifndef SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_SROTATION_CXX_HPP__
#define SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_SROTATION_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/multiprec/definitions.h"
    #include "sixtracklib/multiprec/math_constants.h"
    #include "sixtracklib/common/beam_elements/srotation.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    template< unsigned N, boost::multiprecision::backends::digit_base_type
        base = boost::multiprecision::backends::digit_base_2,
        class Alloc = void, class E = int, E ExpMin = E{ 0 },
        E ExpMax = E{ 0 }, multiprec_et_option_t et = DEFAULT_MULTIPREC_ET >
    using TMultiPrecSRotation = TSRotation< MultiPrecReal<
        N, base, Alloc, E, ExpMin, ExpMax, et > >;

    /* --------------------------------------------------------------------- */
    /* Specialisations for important parameter sets */

    template< multiprec_et_option_t et >
    using TSinglePrecSRotation = TSRotation< MultiPrecRealSingle< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealSingle< et > >() >;

    using SinglePrecSRotation = TSinglePrecSRotation< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TDoublePrecSRotation = TSRotation< MultiPrecRealDouble< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align<
            MultiPrecRealDouble< et > >() >;

    using DoublePrecSRotation = TDoublePrecSRotation< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TExtDoublePrecSRotation = TSRotation< MultiPrecRealExtDouble< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align<
            MultiPrecRealExtDouble< et > >() >;

    using ExtDoublePrecSRotation = TExtDoublePrecSRotation< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TQuadPrecSRotation = TSRotation< MultiPrecRealQuad< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealQuad< et > >() >;

    using QuadPrecSRotation = TQuadPrecSRotation< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TOctPrecSRotation = TSRotation< MultiPrecRealOct< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealOct< et > >() >;

    using OctPrecSRotation = TOctPrecSRotation< DEFAULT_MULTIPREC_ET >;

}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_SROTATION_CXX_HPP__ */
