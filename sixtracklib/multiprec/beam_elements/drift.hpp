#ifndef SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_DRIFT_CXX_HPP__
#define SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_DRIFT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/multiprec/definitions.h"
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/beam_elements/drift/drift.hpp"
    #include "sixtracklib/common/beam_elements/drift/convert_cobjects.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

namespace SIXTRL_CXX_NAMESPACE
{
    template< unsigned int BinDigits >
    using MPDriftData = DriftData< MultiPrecReal< BinDigits >,
        SIXTRL_CXX_NAMESPACE::Type_storage_align<
            MultiPrecReal< BinDigits > >() >;

    template< unsigned int BinDigits >
    using MultiPrecDrift = TDriftImpl<
        MPDriftData< BinDigits >, STORAGE_BE_COBJECTS >;
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_MULTIPREC_BEAM_ELEMENTS_DRIFT_CXX_HPP__ */
