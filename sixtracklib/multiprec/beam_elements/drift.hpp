#ifndef SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_DRIFT_CXX_HPP__
#define SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_DRIFT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/multiprec/definitions.h"
    #include "sixtracklib/common/beam_elements/drift.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    template< unsigned N, boost::multiprecision::backends::digit_base_type base=
            boost::multiprecision::backends::digit_base_2, class Alloc = void,
        class E = int, E ExpMin = E{ 0 }, E ExpMax = E{ 0 },
        multiprec_et_option_t et = DEFAULT_MULTIPREC_ET >
    using TMultiPrecDrift = TDrift< MultiPrecReal<
        N, base, Alloc, E, ExpMin, ExpMax, et >,
    SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecReal<
        N, base, Alloc, E, ExpMin, ExpMax, et > >() >;

    /* Specialisations for important parameter sets */

    template< multiprec_et_option_t et >
    using TSinglePrecDrift = TDrift< MultiPrecRealSingle< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealSingle< et > >() >;

    using SinglePrecDrift = TSinglePrecDrift< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TDoublePrecDrift = TDrift< MultiPrecRealDouble< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align<
            MultiPrecRealDouble< et > >() >;

    using DoublePrecDrift = TDoublePrecDrift< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TExtDoublePrecDrift = TDrift< MultiPrecRealExtDouble< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align<
            MultiPrecRealExtDouble< et > >() >;

    using ExtDoublePrecDrift = TExtDoublePrecDrift< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TQuadPrecDrift = TDrift< MultiPrecRealQuad< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealQuad< et > >() >;

    using QuadPrecDrift = TQuadPrecDrift< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TOctPrecDrift = TDrift< MultiPrecRealOct< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealOct< et > >() >;

    using OctPrecDrift = TOctPrecDrift< DEFAULT_MULTIPREC_ET >;
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_DRIFT_CXX_HPP__ */
