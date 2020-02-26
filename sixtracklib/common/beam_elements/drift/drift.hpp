#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/drift/definitions.h"
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/beam_elements/drift/drift_data.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/obj_base_class.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ObjData, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    class TDriftImpl : public ObjDataStorageInterfaceBase<
        ObjData, StoreT, SIXTRL_CXX_NAMESPACE::TDriftImpl< ObjData, StoreT > >
    {
        public:
        typedef typename DriftTraits< ObjData >::real_t real_t;

        typedef typename TypeMethodParamTraits< real_t >::const_argument_type
                real_arg_t;

        typedef typename TypeMethodParamTraits< real_t >::const_existing_type
                real_const_existing_t;
    };

    /* ---------------------------------------------------------------------- */

    template< class E, store_backend_t St >
    SIXTRL_INLINE SIXTRL_FN typename TDriftImpl< E, St >::real_const_existing_t
    Drift_length( SIXTRL_BE_ARGPTR_DEC const TDriftImpl< E, St > *const
            SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( drift != SIXTRL_NULLPTR );
        return drift->length;
    }

    template< class E, store_backend_t St >
    SIXTRL_INLINE SIXTRL_FN void Drift_set_length(
        SIXTRL_BE_ARGPTR_DEC TDriftImpl< E, St >* SIXTRL_RESTRICT drift,
        typename TDriftImpl< E, St >::real_arg_t length ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( drift != SIXTRL_NULLPTR );
        drift->length = length;
    }
}

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/obj_base_class.hpp"
    #include "sixtracklib/common/beam_elements/drift/storage_cobjects.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R,
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    using TDrift = TDriftImpl< DriftData< R, RAlign >, STORAGE_BE_COBJECTS >;

    typedef TDriftImpl< CDriftEquivData, STORAGE_BE_COBJECTS > Drift;
    typedef TDriftImpl< ::NS(Drift),     STORAGE_BE_COBJECTS > CDrift;
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_CXX_HPP__ */
