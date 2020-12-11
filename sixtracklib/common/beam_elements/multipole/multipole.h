#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/definitions.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_annotations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

typedef struct
SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
NS(Multipole)
{
    NS(be_order_t)   order    SIXTRL_ALIGN( 8 )
        SIXTRL_ANNOTATE_ELEM_FIELD_REQU_INIT
        SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(be_real_t)    length   SIXTRL_ALIGN( 8 )
        SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(be_real_t)    hxl      SIXTRL_ALIGN( 8 )
        SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(be_real_t)    hyl      SIXTRL_ALIGN( 8 )
        SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(be_address_t) bal_addr SIXTRL_ALIGN( 8 )
        SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 )
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( bal )
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( "SIXTRL_BE_DATAPTR_DEC" )
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(be_real_t) )
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( capacity );

    NS(be_order_t) bal_capacity SIXTRL_ALIGN( 8 )
        SIXTRL_ANNOTATE_ELEM_FIELD_CONST
        SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 2 );
}
NS(Multipole);

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataBeamElementsTraits< ::NS(Multipole) >
    {
        static constexpr bool is_beam_element = true;
    };

    template<> struct ObjDataMultipoleTraits< ::NS(Multipole) >
    {
        static constexpr bool is_type = true;
        static constexpr be_multipole_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_MULTIPOLE_IMPL_DEFAULT;
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template<> struct MultipoleTraits< ::NS(Multipole) >
    {
        typedef ::NS(be_real_t)     real_t;
        typedef ::NS(be_order_t)    order_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

        static constexpr arch_size_t order_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< order_t >();
    };

    template<> struct ObjDataCApiTypeTraits< ::NS(Multipole) >
    {
        typedef ::NS(Multipole) c_api_t;
    };

    typedef ::NS(Multipole) CMultipole;
}
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_H__ */
