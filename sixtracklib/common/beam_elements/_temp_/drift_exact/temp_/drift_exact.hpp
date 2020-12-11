#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/drift_exact/definitions.h"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact.h"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact_api.h"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact_data.hpp"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact_data_api.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/obj_base_class.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ObjData, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    class TDriftExactImpl : public ObjDataStorageInterfaceBase<
        ObjData, StoreT, SIXTRL_CXX_NAMESPACE::TDriftExactImpl<
            ObjData, StoreT > >
    {
        public:
        typedef typename DriftExactTraits< ObjData >::real_t real_t;

        template< typename... Args >
        SIXTRL_FN void init( Args&&... args )
        {
            SIXTRL_CXX_NAMESPACE::DriftExact_init(
                this->as_ptr_data(), std::forward< Args >( args )... );
        }

        template< class LengthArg >
        SIXTRL_FN void set_length( LengthArg length ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::DriftExact_set_length(
                this->as_ptr_data(), length );
        }
    };
}

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/obj_base_class.hpp"
    #include "sixtracklib/common/beam_elements/drift/drift_cobjects_api.h"
    #include "sixtracklib/common/beam_elements/drift/drift_data_cobjects_api.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R,
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    using TDriftExact = TDriftExactImpl< DriftExactData< R, RAlign >, STORAGE_BE_COBJECTS >;

    typedef TDriftExactImpl< CDriftExactEquivData, STORAGE_BE_COBJECTS > DriftExact;
    typedef TDriftExactImpl< ::NS(DriftExact),     STORAGE_BE_COBJECTS > CDriftExact;
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_CXX_HPP__ */
