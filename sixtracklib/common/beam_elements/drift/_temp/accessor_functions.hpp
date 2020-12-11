#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_ACCESSOR_FUNCTOINS_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_ACCESSOR_FUNCTOINS_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/beam_elements/drift/drift_data.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class RAlign >
    static SIXTRL_INLINE SIXTRL_FN auto Drift_length( const SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign > *const
        SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT ->
        typename TypeMethodParamTraits< typename DriftTraits<
            DriftData< R, RAlign > >::real_t >::const_existing_type
    {
        SIXTRL_ASSERT( drift != nullptr );
        return drift->length;
    }

    template< class R, class RAlign, class LArg >
    static SIXTRL_INLINE SIXTRL_FN void Drift_set_length(
        SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >* SIXTRL_RESTRICT drift,
        LArg length ) SIXTRL_NOEXCEPT
    {
        typedef typename typename std::decay< LArg >::type length_t;
        typedef typename DriftTraits< DriftData< R, RAlign > >::real_t real_t;

        SIXTRL_ASSERT( drift != nullptr );
        SIXTRL_CXX_NAMESPACE::Types_perform_assignment< length_t, real_t >(
            drift->length, length );
    }

    template< class R, class RAlign >
    static SIXTRL_INLINE SIXTRL_FN void Drift_init(
        SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >* SIXTRL_RESTRICT drift )
    {
        typedef typename DriftTraits< DriftData< R, RAlign > >::real_t real_t;
        SIXTRL_ASSERT( drift != nullptr );
        drift->length = real_t{};
    }

    template< class R, class RAlign, class LArg >
    static SIXTRL_INLINE SIXTRL_FN void Drift_init(
        SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >* SIXTRL_RESTRICT drift,
        LArg length )
    {
        typedef typename DriftTraits< DriftData< R, RAlign > >::real_t real_t;
        typedef typename std::decay< LArg >::type length_base_t;

        SIXTRL_ASSERT( drift != nullptr );
        SIXTRL_CXX_NAMESPACE::Type_perform_assignment< length_base_t, real_t >(
            length, drift->length );
    }

    /* Provide alternatives for passing the DriftData using pass-by-reference */

    template< class R, class RAlign >
    static SIXTRL_INLINE SIXTRL_FN auto Drift_length( SIXTRL_BE_ARGPTR_DEC
        DriftData< R, RAlign > const& SIXTRL_RESTRICT_REF drift ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Drift_length( std::addressof( drift ) );
    }

    template< class R, class RAlign, class LArg >
    static SIXTRL_INLINE SIXTRL_FN void Drift_set_length(
        SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >& SIXTRL_RESTRICT_REF drift,
        LArg length ) SIXTRL_NOEXCEPT
    {
        SIXTRL_CXX_NAMESPACE::Drift_set_length(
            std::addressof( drift ), length );
    }

    template< class R, class RAlign >
    static SIXTRL_INLINE SIXTRL_FN void Drift_init(
        SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >& SIXTRL_RESTRICT drift )
    {
        SIXTRL_CXX_NAMESPACE::Drift_init( std::addressof( drift ) );
    }

    template< class R, class RAlign, class LArg >
    static SIXTRL_INLINE SIXTRL_FN void Drift_init(
        SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >& SIXTRL_RESTRICT drift,
        LArg length )
    {
        SIXTRL_CXX_NAMESPACE::Drift_init( std::addressof( drift ), length );
    }
}
#endif /* !defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_ACCESSOR_FUNCTOINS_CXX_HPP__ */
