#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/definitions.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_annotations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

typedef struct
SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
NS(SRotation)
{
    NS(be_real_t) cos_z SIXTRL_ALIGN( 8 )
                  SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

    NS(be_real_t) sin_z SIXTRL_ALIGN( 8 )
                  SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
}
NS(SRotation);

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* ************************************************************************* */
/* Specializations for NS(SRotation): */
/* ************************************************************************* */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataBeamElementsTraits< ::NS(SRotation) >
    {
        static constexpr bool is_beam_element = true;
    };

    template<> struct ObjDataSRotationTraits< ::NS(SRotation) >
    {
        static constexpr bool is_type = true;
        static constexpr be_srotation_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_SROTATION_IMPL_DEFAULT;
    };

    template<> struct SRotationTraits< ::NS(SRotation) >
    {
        typedef ::NS(be_real_t) real_t;
        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< be_real_t >();
    };

    template<> struct ObjDataCApiTypeTraits< ::NS(SRotation) >
    {
        typedef ::NS(SRotation) c_api_t;
    };

    typedef ::NS(SRotation) CSRotation;
}
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_H__ */
