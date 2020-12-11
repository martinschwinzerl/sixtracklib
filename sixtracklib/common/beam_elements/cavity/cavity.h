#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/definitions.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_annotations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

typedef struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
NS(Cavity)
{
    NS(be_real_t) voltage   SIXTRL_ALIGN( 8 )
                            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(be_real_t) frequency SIXTRL_ALIGN( 8 )
                            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(be_real_t) lag       SIXTRL_ALIGN( 8 )
                            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
}
NS(Cavity);

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataBeamElementsTraits< ::NS(Cavity) >
    {
        static constexpr bool is_beam_element = true;
    };

    template<> struct ObjDataCavityTraits< ::NS(Cavity) >
    {
        static constexpr bool is_type = true;
        static constexpr be_cavity_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_CAVITY_IMPL_DEFAULT;
    };

    template<> struct CavityTraits< ::NS(Cavity) >
    {
        typedef ::NS(be_real_t) real_t;
        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();
    };

    template<> struct ObjDataCApiTypeTraits< ::NS(Cavity) >
    {
        typedef ::NS(Cavity) c_api_t;
    };

    typedef ::NS(Cavity) CCavity;
}
#endif /* C++ */

/* ------------------------------------------------------------------------- */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_H__ */
