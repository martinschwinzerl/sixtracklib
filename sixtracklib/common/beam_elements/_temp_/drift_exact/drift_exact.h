#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift_exact/definitions.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_annotations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

typedef struct
SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
NS(DriftExact)
{
    NS(be_real_t) length SIXTRL_ALIGN( 8 )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
}
NS(DriftExact);

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataBeamElementsTraits< ::NS(DriftExact) >
    {
        static constexpr bool is_beam_element = true;
    };

    template<> struct ObjDataDriftExactTraits< ::NS(DriftExact) >
    {
        static constexpr bool is_drift_exact = true;
    };

    template<> struct DriftExactTraits< ::NS(DriftExact) >
    {
        typedef ::NS(be_real_t) real_t;
        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();
    };

    template<> struct ObjDataCApiTypeTraits< ::NS(DriftExact) >
    {
        typedef ::NS(DriftExact) c_api_t;
    };

    typedef ::NS(DriftExact) CDriftExact;
}
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_C99_H__ */
