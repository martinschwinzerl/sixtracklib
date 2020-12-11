#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/definitions.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_annotations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

typedef struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" ) NS(Drift)
{
    NS(be_real_t)               length SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(be_drift_track_type_t)   track_type SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE(
                                    SIXTRL_BE_DRIFT_TRACK_TYPE_SIMPLE );
}
NS(Drift);

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataBeamElementsTraits< ::NS(Drift) >
    {
        static constexpr bool is_beam_element = true;
    };

    template<> struct ObjDataDriftTraits< ::NS(Drift) >
    {
        static constexpr bool is_type = true;
        static constexpr be_drift_impl_t implementation =
                            SIXTRL_CXX_NAMESPACE::BE_DRIFT_IMPL_DEFAULT;
    };

    template<> struct DriftTraits< ::NS(Drift) >
    {
        typedef be_real_t real_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();
    };

    template<> struct ObjDataCApiTypeTraits< ::NS(Drift) >
    {
        typedef ::NS(Drift) c_api_t;
    };

    typedef ::NS(Drift) CDrift;
}
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_H__ */
