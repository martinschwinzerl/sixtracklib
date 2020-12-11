#ifndef SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_CAVITY_CAVITY_CXX_HPP__
#define SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_CAVITY_CAVITY_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/multiprec/definitions.h"
    #include "sixtracklib/common/beam_elements/cavity.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    template< unsigned N, boost::multiprecision::backends::digit_base_type
        base = boost::multiprecision::backends::digit_base_2,
        class Alloc = void, class E = int, E ExpMin = E{ 0 },
        E ExpMax = E{ 0 }, multiprec_et_option_t et = DEFAULT_MULTIPREC_ET >
    using TMultiPrecCavity = TCavity< MultiPrecReal<
        N, base, Alloc, E, ExpMin, ExpMax, et > >;

    /* --------------------------------------------------------------------- */
    /* Specialisations for important parameter sets */

    template< multiprec_et_option_t et >
    using TSinglePrecCavity = TCavity< MultiPrecRealSingle< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealSingle< et > >() >;

    using SinglePrecCavity = TSinglePrecCavity< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TDoublePrecCavity = TCavity< MultiPrecRealDouble< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align<
            MultiPrecRealDouble< et > >() >;

    using DoublePrecCavity = TDoublePrecCavity< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TExtDoublePrecCavity = TCavity< MultiPrecRealExtDouble< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align<
            MultiPrecRealExtDouble< et > >() >;

    using ExtDoublePrecCavity = TExtDoublePrecCavity< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TQuadPrecCavity = TCavity< MultiPrecRealQuad< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealQuad< et > >() >;

    using QuadPrecCavity = TQuadPrecCavity< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TOctPrecCavity = TCavity< MultiPrecRealOct< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealOct< et > >() >;

    using OctPrecCavity = TOctPrecCavity< DEFAULT_MULTIPREC_ET >;

}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_CAVITY_CAVITY_CXX_HPP__ */
