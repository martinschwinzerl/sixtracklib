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
    #include <boost/math/tools/precision.hpp>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/type_random_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    using multiprec_et_option_t =
        boost::multiprecision::expression_template_option;

    static constexpr multiprec_et_option_t DEFAULT_MULTIPREC_ET =
        boost::multiprecision::et_off;

    /* ---------------------------------------------------------------------- */
    /* Provide a template type alias for the Multi-Precision type
     * TODO: Implement a different option than using the default bin-dec
     *       boost multiprecision type ( i.e. MPFR, boost-multiprec
     *       with libquadmath, etc. as soon as a different backend is enabled!*/

    template< unsigned Digits,
        boost::multiprecision::backends::digit_base_type base =
            boost::multiprecision::backends::digit_base_2,
        class Alloc = void, class E = int, E ExpMin = E{ 0 }, E ExpMax = E{ 0 },
        multiprec_et_option_t et = DEFAULT_MULTIPREC_ET >
    using MultiPrecReal = boost::multiprecision::number<
        boost::multiprecision::cpp_bin_float<
            Digits, base, Alloc, E, ExpMin, ExpMax >, et >;


    /* Specialisations for MultiPrecReal for "common" parameters */

    template< multiprec_et_option_t et = DEFAULT_MULTIPREC_ET >
    using MultiPrecRealSingle = boost::multiprecision::number<
        boost::multiprecision::cpp_bin_float< 24,
            boost::multiprecision::backends::digit_base_2, void,
            std::int16_t, std::int16_t{ -126 }, std::int16_t{ 127 } >, et >;

    template< multiprec_et_option_t et = DEFAULT_MULTIPREC_ET >
    using MultiPrecRealDouble = boost::multiprecision::number<
        boost::multiprecision::cpp_bin_float< 53,
            boost::multiprecision::backends::digit_base_2, void,
            std::int16_t, std::int16_t{ -1022 }, std::int16_t{ 1023 } >, et >;

    template< multiprec_et_option_t et = DEFAULT_MULTIPREC_ET >
    using MultiPrecRealExtDouble = boost::multiprecision::number<
        boost::multiprecision::cpp_bin_float< 64,
            boost::multiprecision::backends::digit_base_2, void,
            std::int16_t, std::int16_t{ -16382 }, std::int16_t{ 16383 } >, et >;

    template< multiprec_et_option_t et = DEFAULT_MULTIPREC_ET >
    using MultiPrecRealQuad = boost::multiprecision::number<
        boost::multiprecision::cpp_bin_float< 113,
            boost::multiprecision::backends::digit_base_2, void,
            std::int16_t, std::int16_t{ -16382 }, std::int16_t{ 16383 } >, et >;

    template< multiprec_et_option_t et = DEFAULT_MULTIPREC_ET >
    using MultiPrecRealOct = boost::multiprecision::number<
        boost::multiprecision::cpp_bin_float< 237,
            boost::multiprecision::backends::digit_base_2, void,
            std::int32_t, std::int32_t{ -262142 }, std::int32_t{ 262143 } >,
            et >;

    /* ---------------------------------------------------------------------- */

    typedef enum
    {
        MULTIPREC_IMPL_BOOST = 0,
        MULTIPREC_IMPL_NONE  = 255
    }
    multiprec_impl_t;

    template< class MpT >
    struct MultiPrecRealTraits
    {
        static constexpr unsigned int num_digits = 0u;
        static constexpr multiprec_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::MULTIPREC_IMPL_NONE;
    };

    template< class MpT >
    constexpr unsigned int MultiPrecRealTraits< MpT >::num_digits;

    template< class MpT >
    constexpr multiprec_impl_t MultiPrecRealTraits< MpT >::implementation;

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class MpT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool MultiPrec_is_type() SIXTRL_NOEXCEPT
    {
        /* TODO: Add case for integer multiprec number */
        return MultiPrecRealTraits< MpT >::implementation !=
            SIXTRL_CXX_NAMESPACE::MULTIPREC_IMPL_NONE;
    }

    template< class MpT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    MultiPrec_is_real_type() SIXTRL_NOEXCEPT
    {
        return MultiPrecRealTraits< MpT >::implementation !=
            SIXTRL_CXX_NAMESPACE::MULTIPREC_IMPL_NONE;
    }

    template< class MpT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    MultiPrec_real_impl_boost() SIXTRL_NOEXCEPT
    {
        return MultiPrecRealTraits< MpT >::implementation ==
            SIXTRL_CXX_NAMESPACE::MULTIPREC_IMPL_BOOST;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class MpT >
    SIXTRL_STATIC SIXTRL_FN constexpr unsigned int
    MultiPrec_real_num_digits() SIXTRL_NOEXCEPT
    {
        return MultiPrecRealTraits< MpT >::num_digits;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< unsigned int N, class Alloc, class E, E ExpMin, E ExpMax,
              multiprec_et_option_t et >
    struct MultiPrecRealTraits< boost::multiprecision::number<
        boost::multiprecision::cpp_bin_float< N,
            boost::multiprecision::backends::digit_base_2,
                Alloc, E, ExpMin, ExpMax >, et > >
    {
        static constexpr unsigned int num_digits = N;
        static constexpr multiprec_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::MULTIPREC_IMPL_BOOST;
    };

    template< unsigned int N, class Alloc, class E, E ExpMin, E ExpMax,
              multiprec_et_option_t et >
    constexpr unsigned int MultiPrecRealTraits< boost::multiprecision::number<
        boost::multiprecision::cpp_bin_float< N,
            boost::multiprecision::backends::digit_base_2,
                Alloc, E, ExpMin, ExpMax >, et > >::num_digits;

    template< unsigned int N, class Alloc, class E, E ExpMin, E ExpMax,
              multiprec_et_option_t et >
    constexpr multiprec_impl_t MultiPrecRealTraits<
        boost::multiprecision::number< boost::multiprecision::cpp_bin_float< N,
            boost::multiprecision::backends::digit_base_2,
                Alloc, E, ExpMin, ExpMax >, et > >::implementation;

    /* ---------------------------------------------------------------------- */
    /* Specialize the type traits for MultiPrecReal< N >: */

    template< unsigned int N,
        boost::multiprecision::backends::digit_base_type base, class Alloc,
            class E, E ExpMin, E ExpMax, multiprec_et_option_t et >
    struct TypeMethodParamTraits<
        MultiPrecReal< N, base, Alloc, E, ExpMin, ExpMax, et > >
    {
        typedef MultiPrecReal< N, base, Alloc, E, ExpMin, ExpMax, et >
                value_type;

        typedef value_type const                        const_argument_type;
        typedef value_type                              argument_type;
        typedef value_type& SIXTRL_RESTRICT_REF         ref_argument_type;
        typedef value_type                              const_existing_type;
        typedef value_type                              existing_type;
        typedef value_type& SIXTRL_RESTRICT_REF         ref_existing_type;
        typedef value_type const*                       const_pointer;
        typedef value_type*                             pointer;
        typedef value_type&&                            rvalue_ref;
    };

    template<
        unsigned int N,
        boost::multiprecision::backends::digit_base_type base,
        class Alloc, class E, E ExpMin, E ExpMax,
        multiprec_et_option_t et, typename R >
    struct TypePerformAssignmentHelper< MultiPrecReal<
            N, base, Alloc, E, ExpMin, ExpMax, et >, R,
        typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::Types_are_assignable<
                MultiPrecReal<
            N, base, Alloc, E, ExpMin, ExpMax, et >, R >() &&
            !SIXTRL_CXX_NAMESPACE::Types_are_convertible<
                MultiPrecReal<
            N, base, Alloc, E, ExpMin, ExpMax, et >, R >() &&
            std::is_floating_point< R >::value >::type >
    {
        static SIXTRL_FN bool can_assign_test() SIXTRL_NOEXCEPT
        {
            return true;
        }

        static SIXTRL_FN constexpr bool can_assign() SIXTRL_NOEXCEPT
        {
            return true;
        }

        static SIXTRL_FN arch_status_t assign(
            SIXTRL_ARGPTR_DEC typename TypeMethodParamTraits<
                R >::ref_argument_type destination,
            SIXTRL_ARGPTR_DEC typename TypeMethodParamTraits<
                MultiPrecReal< N, base, Alloc, E, ExpMin, ExpMax, et >
                    >::const_argument_type source ) SIXTRL_NOEXCEPT
        {
            destination = source.template convert_to< R >();
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }
    };

    template< multiprec_et_option_t et >
    struct TypePerformAssignmentHelper< double, MultiPrecRealSingle< et > >
    {
        static SIXTRL_FN bool can_assign_test() SIXTRL_NOEXCEPT
        {
            return true;
        }

        static SIXTRL_FN constexpr bool can_assign() SIXTRL_NOEXCEPT
        {
            return true;
        }

        static SIXTRL_FN arch_status_t assign(
            SIXTRL_ARGPTR_DEC typename TypeMethodParamTraits<
                MultiPrecRealSingle< et > >::ref_argument_type destination,
            SIXTRL_ARGPTR_DEC TypeMethodParamTraits< double
                >::const_argument_type source ) SIXTRL_NOEXCEPT
        {
            destination = static_cast< MultiPrecRealSingle< et > >( source );
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }
    };
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_MULTIPREC_DEFINITIONS_H__ */
