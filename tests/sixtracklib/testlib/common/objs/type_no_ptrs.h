#ifndef SIXTRACKLIB_TESTLIB_COMMON_OBJS_TYPE_NO_PTRS_H__
#define SIXTRACKLIB_TESTLIB_COMMON_OBJS_TYPE_NO_PTRS_H__

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
NS(TypeNoPtrs)
{
    NS(test_objs_real_t)  a      SIXTRL_ALIGN( 8 )
                                 SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(test_objs_int_t)   b      SIXTRL_ALIGN( 8 )
                                 SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(test_objs_uchar_t) c[ 6 ] SIXTRL_ALIGN( 8 )
                                 SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
}
NS(TypeNoPtrs);

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        template<> struct ObjDataNoPtrTypeTraits< ::NS(TypeNoPtrs) >
        {
            static constexpr bool is_type = true;
            static constexpr objs_type_no_ptrs_impl_t implementation =
                SIXTRL_CXX_NAMESPACE::tests::OBJS_TYPE_NO_PTRS_IMPL_DEFAULT;
        };

        template<> struct TypeNoPtrsTraits< ::NS(TypeNoPtrs) >
        {
            typedef SIXTRL_CXX_NAMESPACE::tests::objs_real_t    real_t;
            typedef SIXTRL_CXX_NAMESPACE::tests::objs_int_t     int_t;
            typedef SIXTRL_CXX_NAMESPACE::tests::objs_uchar_t   uchar_t;

            static constexpr SIXTRL_CXX_NAMESPACE::arch_size_t real_alignment
                = SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

            static constexpr SIXTRL_CXX_NAMESPACE::arch_size_t int_alignment
                = SIXTRL_CXX_NAMESPACE::Type_storage_align< int_t >();

            static constexpr SIXTRL_CXX_NAMESPACE::arch_size_t uchar_alignment
                = SIXTRL_CXX_NAMESPACE::Type_storage_align< uchar_t >();
        };

        typedef ::NS(TypeNoPtrs) CTypeNoPtrs;

    } /*tests */

    template<> struct ObjDataCApiTypeTraits< ::NS(TypeNoPtrs) >
    {
        typedef ::NS(TypeNoPtrs) c_api_t;
    };

} /* SIXTRL_CXX_NAMESPACE */

#endif /* C++ */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_OBJS_TYPE_NO_PTRS_H__ */
