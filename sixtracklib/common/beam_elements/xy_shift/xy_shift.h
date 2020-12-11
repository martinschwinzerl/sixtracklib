#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/xy_shift/definitions.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_annotations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

typedef struct
SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
NS(XYShift)
{
    NS(be_real_t) dx SIXTRL_ALIGN( 8 )
                     SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(be_real_t) dy SIXTRL_ALIGN( 8 )
                     SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
}
NS(XYShift);

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataBeamElementsTraits< ::NS(XYShift) >
    {
        static constexpr bool is_beam_element = true;
    };

    template<> struct ObjDataXYShiftTraits< ::NS(XYShift) >
    {
        static constexpr bool is_type = true;
        static constexpr be_xy_shift_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_XY_SHIFT_IMPL_DEFAULT;
    };

    template<> struct XYShiftTraits< ::NS(XYShift) >
    {
        typedef SIXTRL_CXX_NAMESPACE::be_real_t real_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();
    };

    template<> struct ObjDataCApiTypeTraits< ::NS(XYShift) >
    {
        typedef ::NS(XYShift) c_api_t;
    };

    typedef ::NS(XYShift) CXYShift;
}
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_H__ */
