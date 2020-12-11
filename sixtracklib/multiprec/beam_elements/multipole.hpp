#ifndef SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_MULTIPOLE_CXX_HPP__
#define SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_MULTIPOLE_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <memory>
    #include <utility>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/multiprec/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_vector.hpp"
    #include "sixtracklib/common/beam_elements/multipole/multipole_api.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_derived_api.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_init.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_convert.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    template< unsigned N, class O, boost::multiprecision::backends::digit_base_type base=
            boost::multiprecision::backends::digit_base_2, class Alloc = void,
        class E = int, E ExpMin = E{ 0 }, E ExpMax = E{ 0 },
        multiprec_et_option_t et = DEFAULT_MULTIPREC_ET,
        class MpAlloc = std::allocator< MultiPrecReal<
            N, base, Alloc, E, ExpMin, ExpMax, et > > >
    using TMultiPrecMultipole = TVectorMultipole< MultiPrecReal<
        N, base, Alloc, E, ExpMin, ExpMax, et >, O,
    SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecReal<
        N, base, Alloc, E, ExpMin, ExpMax, et > >(),
    SIXTRL_CXX_NAMESPACE::Type_storage_align< O >(), MpAlloc >;

    /* Specialisations for important parameter sets */

    template< multiprec_et_option_t et, class O >
    using TSinglePrecMultipole = TVectorMultipole<
        MultiPrecRealSingle< et >, O >;

    using SinglePrecMultipole = TVectorMultipole<
        MultiPrecRealSingle< DEFAULT_MULTIPREC_ET >,
        SIXTRL_CXX_NAMESPACE::be_order_t >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et, class O >
    using TDoublePrecMultipole = TVectorMultipole<
        MultiPrecRealDouble< et >, O >;

    using DoublePrecMultipole = TVectorMultipole<
        MultiPrecRealDouble< DEFAULT_MULTIPREC_ET >,
        SIXTRL_CXX_NAMESPACE::be_order_t >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et, class O >
    using TExtDoublePrecMultipole = TVectorMultipole<
        MultiPrecRealExtDouble< et >, O >;

    using ExtDoublePrecMultipole = TVectorMultipole<
        MultiPrecRealExtDouble< DEFAULT_MULTIPREC_ET >,
        SIXTRL_CXX_NAMESPACE::be_order_t >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et, class O >
    using TQuadPrecMultipole = TVectorMultipole<
        MultiPrecRealQuad< et >, O >;

    using QuadPrecMultipole = TVectorMultipole<
        MultiPrecRealQuad< DEFAULT_MULTIPREC_ET >,
        SIXTRL_CXX_NAMESPACE::be_order_t >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< multiprec_et_option_t et, class O >
    using TOctPrecMultipole = TVectorMultipole<
        MultiPrecRealOct< et >, O >;

    using OctPrecMultipole = TVectorMultipole<
        MultiPrecRealOct< DEFAULT_MULTIPREC_ET >,
        SIXTRL_CXX_NAMESPACE::be_order_t >;

}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_MULTIPOLE_CXX_HPP__ */
