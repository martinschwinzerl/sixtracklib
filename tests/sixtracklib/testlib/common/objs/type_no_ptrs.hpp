#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/definitions.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        template< class R, class I, class U,
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(),
        arch_size_t IAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< I >(),
        arch_size_t UAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< U >() >
        struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
        SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BUFFER_DATPTR_DEC" )
        TTypeNoPtrs
        {
            R a      SIXTRL_ALIGN( RAlign )
                     SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

            I b      SIXTRL_ALIGN( IAlign )
                     SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

            U c[ 6 ] SIXTRL_ALIGN( UAlign )
                     SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
        };

        /* ***************************************************************** */
        /* Specializations for TTypeNoPtrs: */
        /* ***************************************************************** */

        template< class R, class I, class U,
                  SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t IAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t UAlign >
        struct ObjDataNoPtrTypeTraits<
            TTypeNoPtrs< R, I, U, RAlign, IAlign, UAlign > >
        {
            static constexpr bool is_type = true;
            static constexpr objs_type_no_ptrs_impl_t implementation =
                SIXTRL_CXX_NAMESPACE::tests::OBJS_TYPE_NO_PTRS_IMPL_DEFAULT;
        };

        template< class R, class I, class U,
                  SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t IAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t UAlign >
        constexpr bool ObjDataNoPtrTypeTraits<
            TTypeNoPtrs< R, I, U, RAlign, IAlign, UAlign > >::is_type;

        template< class R, class I, class U,
                  SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t IAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t UAlign >
        constexpr objs_type_no_ptrs_impl_t ObjDataNoPtrTypeTraits<
            TTypeNoPtrs< R, I, U, RAlign, IAlign, UAlign > >::implementation;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< class R, class I, class U,
                  SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t IAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t UAlign >
        struct TypeNoPtrsTraits<
            TTypeNoPtrs< R, I, U, RAlign, IAlign, UAlign > >
        {
            typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                R >::value_type real_t;

            typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                I >::value_type int_t;

            typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                U >::value_type uchar_t;

            static constexpr SIXTRL_CXX_NAMESPACE::arch_size_t
                real_alignment = RAlign;

            static constexpr SIXTRL_CXX_NAMESPACE::arch_size_t
                int_alignment = IAlign;

            static constexpr SIXTRL_CXX_NAMESPACE::arch_size_t
                uchar_alignment = UAlign;
        };

        template< class R, class I, class U,
                  SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t IAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t UAlign >
        constexpr SIXTRL_CXX_NAMESPACE::arch_size_t TypeNoPtrsTraits<
            TTypeNoPtrs< R, I, U, RAlign, IAlign, UAlign > >::real_alignment;

        template< class R, class I, class U,
                  SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t IAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t UAlign >
        constexpr SIXTRL_CXX_NAMESPACE::arch_size_t TypeNoPtrsTraits<
            TTypeNoPtrs< R, I, U, RAlign, IAlign, UAlign > >::int_alignment;

        template< class R, class I, class U,
                  SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t IAlign,
                  SIXTRL_CXX_NAMESPACE::arch_size_t UAlign >
        constexpr SIXTRL_CXX_NAMESPACE::arch_size_t TypeNoPtrsTraits<
            TTypeNoPtrs< R, I, U, RAlign, IAlign, UAlign > >::uchar_alignment;

        /* ***************************************************************** */
        /* Create an equivalency between the ::NS(TTypeNoPtrs) type and the
         * corresponding specialization of the TTypeNoPtrs template */
        /* ***************************************************************** */

        typedef TTypeNoPtrs<
            TypeNoPtrsTraits< ::NS(TypeNoPtrs) >::real_t,
            TypeNoPtrsTraits< ::NS(TypeNoPtrs) >::int_t,
            TypeNoPtrsTraits< ::NS(TypeNoPtrs) >::uchar_t,
            TypeNoPtrsTraits< ::NS(TypeNoPtrs) >::real_alignment,
            TypeNoPtrsTraits< ::NS(TypeNoPtrs) >::int_alignment,
            TypeNoPtrsTraits< ::NS(TypeNoPtrs) >::uchar_alignment > TypeNoPtrs;

    } /* tests */

    template<> struct ObjDataCApiTypeTraits<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs, ::NS(TypeNoPtrs) >(),
            "TypeNoPtrs and ::NS(TypeNoPtrs) are not equivalent C-Api types" );

        typedef ::NS(TypeNoPtrs) c_api_t;
    };

} /* SIXTRL_CXX_NAMESPACE */

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_CXX_HPP__ */
