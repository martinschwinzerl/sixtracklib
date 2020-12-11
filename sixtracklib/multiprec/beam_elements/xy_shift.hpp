#ifndef SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_CAVITY_CAVITY_CXX_HPP__
#define SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_CAVITY_CAVITY_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/multiprec/definitions.h"
    #include "sixtracklib/common/beam_elements/xy_shift.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    template< unsigned N, boost::multiprecision::backends::digit_base_type
        base = boost::multiprecision::backends::digit_base_2,
        class Alloc = void, class E = int, E ExpMin = E{ 0 },
        E ExpMax = E{ 0 }, multiprec_et_option_t et = DEFAULT_MULTIPREC_ET >
    using TMultiPrecXYShift = TXYShift< MultiPrecReal<
        N, base, Alloc, E, ExpMin, ExpMax, et > >;

    /* --------------------------------------------------------------------- */
    /* Specialisations for important parameter sets */

    template< multiprec_et_option_t et >
    using TSinglePrecXYShift = TXYShift< MultiPrecRealSingle< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealSingle< et > >() >;

    using SinglePrecXYShift = TSinglePrecXYShift< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TDoublePrecXYShift = TXYShift< MultiPrecRealDouble< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align<
            MultiPrecRealDouble< et > >() >;

    using DoublePrecXYShift = TDoublePrecXYShift< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TExtDoublePrecXYShift = TXYShift< MultiPrecRealExtDouble< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align<
            MultiPrecRealExtDouble< et > >() >;

    using ExtDoublePrecXYShift = TExtDoublePrecXYShift< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TQuadPrecXYShift = TXYShift< MultiPrecRealQuad< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealQuad< et > >() >;

    using QuadPrecXYShift = TQuadPrecXYShift< DEFAULT_MULTIPREC_ET >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et >
    using TOctPrecXYShift = TXYShift< MultiPrecRealOct< et >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealOct< et > >() >;

    using OctPrecXYShift = TOctPrecXYShift< DEFAULT_MULTIPREC_ET >;

}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_CAVITY_CAVITY_CXX_HPP__ */
