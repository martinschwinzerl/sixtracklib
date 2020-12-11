#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/definitions.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_annotations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{

namespace tests
{
    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
           SIXTRL_ANNOTATE_ELEM_OBJ_API_NAME( TypeConstNumPtrs )
           SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BUFFER_DATPTR_DEC" )
    TTypeConstNumPtrs
    {
        objs_real_t a SIXTRL_ALIGN( 8 )
            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        objs_size_t num_b_values SIXTRL_ALIGN( 8 )
            SIXTRL_ANNOTATE_ELEM_FIELD_REQU_INIT
            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        objs_addr_t b_addr SIXTRL_ALIGN( 8 )
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( "num_b_values" )
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( "NS(test_cobj_real_t)" )
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( "b" )
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( "SIXTRL_BUFFER_DATAPTR_DEC" );

        objs_size_t num_c_values SIXTRL_ALIGN( 8 )
            SIXTRL_ANNOTATE_ELEM_FIELD_REQU_INIT
            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        objs_addr_t c_addr SIXTRL_ALIGN( 8 )
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( "num_c_values" )
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( "NS(test_cobj_real_t)" )
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( "c" )
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( "SIXTRL_BUFFER_DATAPTR_DEC" );
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign >
    struct ObjDataTypeConstNumPtrsTraits< TTypeConstNumPtrs< R, RAlign > >
    {
        static constexpr bool is_type = true;
        static constexpr objs_type_const_num_ptrs_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::tests::OBJS_TYPE_CONST_NUM_PTRS_IMPL_DEFAULT;
    };

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign >
    constexpr bool ObjDataTypeConstNumPtrsTraits< TTypeConstNumPtrs<
        R, RAlign > >::is_type;

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign >
    constexpr objs_type_const_num_ptrs_impl_t ObjDataTypeConstNumPtrsTraits<
        TTypeConstNumPtrs< R, RAlign > >::implementation;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign >
    struct TypeConstNumPtrsTraits< TTypeConstNumPtrs< R, RAlign > >
    {
        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
            R >::value_type real_t;

        static constexpr SIXTRL_CXX_NAMESPACE::arch_size_t real_alignment
                = SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();
    };

    typedef TTypeConstNumPtrs<
        TypeConstNumPtrsTraits< ::NS(TypeConstNumPtrs) >::real_t,
        TypeConstNumPtrsTraits< ::NS(TypeConstNumPtrs) >::real_alignment >
        TypeConstNumPtrs;

    } /* namespace: tests */

    template<> struct ObjDataCApiTypeTraits<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs,
                ::NS(TypeConstNumPtrs) >(),
            "TypeConstNumPtrs and ::NS(TypeConstNumPtrs) are not "
            "equivalent C-Api types" );

        typedef ::NS(TypeConstNumPtrs) c_api_t;
    };

} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++ */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_CXX_HPP__ */
