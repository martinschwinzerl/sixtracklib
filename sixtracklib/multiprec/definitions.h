#ifndef SIXTRACKLIB_MULTIPREC_DEFINITIONS_H__
#define SIXTRACKLIB_MULTIPREC_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <boost/multiprecision/cpp_bin_float.hpp>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    /* ---------------------------------------------------------------------- */
    /* Provide a template type alias for the Multi-Precision type
     * TODO: Implement a different option than using the default bin-dec
     *       boost multiprecision type ( i.e. MPFR, boost-multiprec
     *       with libquadmath, etc. as soon as a different backend is enabled!*/

    template< unsigned BinDigits >
    using MultiPrecReal = boost::multiprecision::number<
        boost::multiprecision::cpp_bin_float< BinDigits > >;

    /* ---------------------------------------------------------------------- */
    /* Specialize the type traits for MultiPrecReal< N >: */

    template< unsigned int BinDigits >
    struct TypeMethodParamTraits< MultiPrecReal< BinDigits > >
    {
        typedef MultiPrecReal< BinDigits >              value_type;
        typedef value_type& SIXTRL_RESTRICT_REF         argument_type;
        typedef value_type const& SIXTRL_RESTRICT_REF   const_argument_type;
        typedef value_type& SIXTRL_RESTRICT_REF         ref_argument_type;
        typedef value_type const&                       const_existing_type;
        typedef value_type&                             existing_type;
    };
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_MULTIPREC_DEFINITIONS_H__ */
