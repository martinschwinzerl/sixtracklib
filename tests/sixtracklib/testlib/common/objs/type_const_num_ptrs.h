#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/definitions.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_annotations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

typedef struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BUFFER_DATPTR_DEC" )
NS(TypeConstNumPtrs)
{
    NS(test_objs_real_t) a SIXTRL_ALIGN( 8 )
        SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(test_objs_size_t) num_b_values SIXTRL_ALIGN( 8 )
        SIXTRL_ANNOTATE_ELEM_FIELD_REQU_INIT
        SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(test_objs_addr_t) b_addr SIXTRL_ALIGN( 8 )
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( "num_b_values" )
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( "b" )
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( "SIXTRL_BUFFER_DATAPTR_DEC" );

    NS(test_objs_size_t) num_c_values SIXTRL_ALIGN( 8 )
        SIXTRL_ANNOTATE_ELEM_FIELD_REQU_INIT
        SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(test_objs_addr_t) c_addr SIXTRL_ALIGN( 8 )
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( "num_c_values" )
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( "c" )
        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( "SIXTRL_BUFFER_DATAPTR_DEC" );
}
NS(TypeConstNumPtrs);

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        template<> struct ObjDataTypeConstNumPtrsTraits< ::NS(TypeConstNumPtrs) >
        {
            static constexpr bool is_type = true;
            static constexpr objs_type_const_num_ptrs_impl_t implementation =
                SIXTRL_CXX_NAMESPACE::tests::OBJS_TYPE_CONST_NUM_PTRS_IMPL_DEFAULT;
        };

        template<> struct TypeConstNumPtrsTraits< ::NS(TypeConstNumPtrs) >
        {
            typedef ::NS(test_objs_real_t) real_t;

            static constexpr SIXTRL_CXX_NAMESPACE::arch_size_t real_alignment
                = SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();
        };

        typedef ::NS(TypeConstNumPtrs) CTypeConstNumPtrs;

    } /* namespace: tests */

    template<> struct ObjDataCApiTypeTraits< ::NS(TypeConstNumPtrs) >
    {
        typedef ::NS(TypeConstNumPtrs) c_api_t;
    };

} /* SIXTRL_CXX_NAMESPACE */

#endif /* C++ */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_H__ */
