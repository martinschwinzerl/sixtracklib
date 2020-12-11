#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_API_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/testlib/common/objs/definitions.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs.h"
    #include "sixtracklib/common/internal/obj_addr_based_pointer_field.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    /* --------------------------------------------------------------------- */
    /* a: */

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(),
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT >::real_t
                >::value_type >::type
    TypeNoPtrs_default_a( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
        SIXTRL_RESTRICT /*obj*/ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return typename st::TypeMethodParamTraits< typename
            st::tests::TypeNoPtrsTraits< TypeNoPtrsT >::real_t
                >::value_type{ 0 };
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_default_a( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
        SIXTRL_RESTRICT obj = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "TypeNoPtrsT required to be a TypeNoPtrsT class" );

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( obj != SIXTRL_NULLPTR )
        {
            obj->a = st::tests::TypeNoPtrs_default_a< TypeNoPtrsT >();
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT >::real_t
            >::const_existing_type
    TypeNoPtrs_a( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "TypeNoPtrsT is required to be a TypeNoPtrsT class" );

        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return obj->a;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeNoPtrsT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_a(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT /* obj */,
        RealArg /*a_value*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class TypeNoPtrsT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT
                >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_a(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
        RealArg a_value )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        obj->a = a_value;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class TypeNoPtrsT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeNoPtrsT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeNoPtrsT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_a(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
        RealArg a_value )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        obj->a = std::move( a_value );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class TypeNoPtrsT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeNoPtrsT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeNoPtrsT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_a(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
        RealArg a_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
            TypeNoPtrsT >::real_t real_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( obj != SIXTRL_NULLPTR )
        {
            status = st::Types_perform_assignment<
                src_real_t, real_t >( obj->a, a_value );
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* b: */

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(),
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
            typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT
                >::int_t >::value_type >::type
    TypeNoPtrs_default_b( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
        SIXTRL_RESTRICT /*obj*/ = SIXTRL_NULLPTR )
    {
        return typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT
                >::int_t >::value_type{ 0 };
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_default_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "TypeNoPtrsT required to be a TypeNoPtrsT class" );

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( obj != SIXTRL_NULLPTR )
        {
            obj->b = st::tests::TypeNoPtrs_default_b( obj );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT >::int_t
            >::const_existing_type
    TypeNoPtrs_b( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "TypeNoPtrsT is required to be a TypeNoPtrsT class" );

        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return obj->b;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeNoPtrsT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT /* obj */,
        RealArg /*b_value*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class TypeNoPtrsT, typename IntArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< IntArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeNoPtrsT >::int_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
        IntArg b_value )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        obj->b = b_value;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class TypeNoPtrsT, typename IntArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< IntArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeNoPtrsT >::int_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< IntArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeNoPtrsT >::int_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
        IntArg b_value )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        obj->b = std::move( b_value );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class TypeNoPtrsT, typename IntArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< IntArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeNoPtrsT >::int_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< IntArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeNoPtrsT >::int_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
        IntArg b_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        typedef typename std::decay< IntArg >::type src_int_t;
        typedef typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
            TypeNoPtrsT >::int_t int_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( obj != SIXTRL_NULLPTR )
        {
            status = st::Types_perform_assignment<
                src_int_t, int_t >( obj->b, b_value );
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* c: */

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_size_t
    TypeNoPtrs_c_length( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT
        *const SIXTRL_RESTRICT /* obj */ ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "TypeNoPtrsT is required to be a TypeNoPtrsT class" );
        return st::arch_size_t{ 6 };
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_address_t
    TypeNoPtrs_c_addr( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return static_cast< SIXTRL_CXX_NAMESPACE::arch_address_t >(
            reinterpret_cast< std::uintptr_t >( &obj->c[ 0 ] ) );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(),
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
            typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT
                >::uchar_t >::value_type >::type
    TypeNoPtrs_default_c( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
        SIXTRL_RESTRICT /* obj */ = SIXTRL_NULLPTR )
    {
        return typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT
                >::uchar_t >::value_type{ 0 };
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_default_c(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::tests::TypeNoPtrsTraits<
            TypeNoPtrsT >::uchar_t uchar_t;

        typedef typename SIXTRL_BUFFER_DATAPTR_DEC st::TypeMethodParamTraits<
                    uchar_t >::pointer ptr_t;

        typedef typename st::TypeMethodParamTraits<
                    uchar_t >::const_argument_type uchar_arg_t;

        return st::ObjData_set_all_field_values_for_addr< TypeNoPtrsT, ptr_t,
            uchar_arg_t >( st::tests::TypeNoPtrs_c_addr( obj ),
                st::tests::TypeNoPtrs_c_length( obj ),
                    st::tests::TypeNoPtrs_default_c( obj ) );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT >::uchar_t
            >::const_existing_type
    TypeNoPtrs_c(
        SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const SIXTRL_RESTRICT obj,
        SIXTRL_CXX_NAMESPACE::arch_size_t const idx ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename SIXTRL_BUFFER_DATAPTR_DEC st::TypeMethodParamTraits<
            typename st::tests::TypeNoPtrsTraits< TypeNoPtrsT >::uchar_t
                >::const_pointer ptr_t;

        return st::ObjData_get_field_value_from_addr< TypeNoPtrsT, ptr_t >(
            st::tests::TypeNoPtrs_c_addr( obj ),
            st::tests::TypeNoPtrs_c_length( obj ), idx );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
        SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeNoPtrsT >::uchar_t >::const_pointer
    TypeNoPtrs_const_c_begin( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT
        *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename SIXTRL_BUFFER_DATAPTR_DEC st::TypeMethodParamTraits<
            typename st::tests::TypeNoPtrsTraits< TypeNoPtrsT >::uchar_t
                >::const_pointer ptr_t;

        return st::ObjData_field_ptr_to_begin_from_addr< TypeNoPtrsT, ptr_t >(
            st::tests::TypeNoPtrs_c_addr( obj ) );
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT >::uchar_t
            >::const_pointer
    TypeNoPtrs_const_c_end( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT
        *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename SIXTRL_BUFFER_DATAPTR_DEC st::TypeMethodParamTraits<
            typename st::tests::TypeNoPtrsTraits< TypeNoPtrsT >::uchar_t
                >::const_pointer ptr_t;

        return st::ObjData_field_ptr_to_end_from_addr< TypeNoPtrsT, ptr_t >(
            st::tests::TypeNoPtrs_c_addr( obj ),
                st::tests::TypeNoPtrs_c_length( obj ) );
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
        SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeNoPtrsT >::uchar_t >::pointer
    TypeNoPtrs_c_begin( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename SIXTRL_BUFFER_DATAPTR_DEC st::TypeMethodParamTraits<
            typename st::tests::TypeNoPtrsTraits< TypeNoPtrsT >::uchar_t
                >::pointer ptr_t;

        return st::ObjData_field_ptr_to_begin_from_addr< TypeNoPtrsT, ptr_t >(
            st::tests::TypeNoPtrs_c_addr( obj ) );
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
        SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT
                >::uchar_t >::pointer
    TypeNoPtrs_c_end( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename SIXTRL_BUFFER_DATAPTR_DEC st::TypeMethodParamTraits<
            typename st::tests::TypeNoPtrsTraits< TypeNoPtrsT >::uchar_t
                >::pointer ptr_t;

        return st::ObjData_field_ptr_to_end_from_addr< TypeNoPtrsT, ptr_t >(
            st::tests::TypeNoPtrs_c_addr( obj ),
                st::tests::TypeNoPtrs_c_length( obj ) );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeNoPtrsT, typename UCharArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_c_value(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT /*obj*/,
        arch_size_t const /*idx*/, UCharArg /*c_value*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeNoPtrsT, typename UCharArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_c_value(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
        SIXTRL_CXX_NAMESPACE::arch_size_t const idx, UCharArg c_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename SIXTRL_BUFFER_DATAPTR_DEC st::TypeMethodParamTraits<
            typename st::tests::TypeNoPtrsTraits< TypeNoPtrsT >::uchar_t
                >::pointer ptr_t;

        return st::ObjData_set_field_value_for_addr<
            TypeNoPtrsT, ptr_t, UCharArg >( st::tests::TypeNoPtrs_c_addr( obj ),
                st::tests::TypeNoPtrs_c_length( obj ), idx, c_value );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeNoPtrsT, typename UCharArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_all_c_values( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
        SIXTRL_RESTRICT /*obj*/, UCharArg /*c_value*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeNoPtrsT, typename UCharArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_all_c_values(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
        UCharArg c_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename SIXTRL_BUFFER_DATAPTR_DEC st::TypeMethodParamTraits<
            typename st::tests::TypeNoPtrsTraits< TypeNoPtrsT >::uchar_t
                >::pointer ptr_t;

        return st::ObjData_set_all_field_values_for_addr<
            TypeNoPtrsT, ptr_t, UCharArg >( st::tests::TypeNoPtrs_c_addr( obj ),
                st::tests::TypeNoPtrs_c_length( obj ), c_value );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeNoPtrsT, typename UCharIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_c(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT /*obj*/,
        UCharIter /*c_begin*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeNoPtrsT, typename UCharIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_set_c(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
        UCharIter c_values_begin )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename SIXTRL_BUFFER_DATAPTR_DEC st::TypeMethodParamTraits<
            typename st::tests::TypeNoPtrsTraits< TypeNoPtrsT >::uchar_t
                >::pointer ptr_t;

        return st::ObjData_set_field_values_from_range_for_addr<
            TypeNoPtrsT, ptr_t, UCharIter >( st::tests::TypeNoPtrs_c_addr( obj ),
                st::tests::TypeNoPtrs_c_length( obj ), c_values_begin );
    }
}
}

/* a: */

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT >::real_t
        >::value_type
NS(TypeNoPtrs_default_a)( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
    SIXTRL_RESTRICT obj = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_default_a( obj );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_set_default_a)( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
    SIXTRL_RESTRICT obj = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_default_a( obj );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT >::real_t
        >::const_existing_type
NS(TypeNoPtrs_a)( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_a( obj );
}

template< class TypeNoPtrsT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_set_a)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
    RealArg a_value )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_set_a( obj, a_value );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* b: */

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT >::int_t
        >::value_type
NS(TypeNoPtrs_default_b)( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
    SIXTRL_RESTRICT obj = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_default_b( obj );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_set_default_b)( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
    SIXTRL_RESTRICT obj = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_set_default_b( obj );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT >::int_t
        >::const_existing_type
NS(TypeNoPtrs_b)( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_b( obj );
}

template< class TypeNoPtrsT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_set_b)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj, RealArg b )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_set_b( obj, b );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* c: */

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT >::uchar_t
        >::value_type
NS(TypeNoPtrs_default_c)( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
    SIXTRL_RESTRICT obj = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_default_c( obj );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_set_default_c)( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
    SIXTRL_RESTRICT obj = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_set_default_c( obj );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_address_t
NS(TypeNoPtrs_c_addr)( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_c_addr( obj );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_size_t
NS(TypeNoPtrs_c_length)( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_c_length( obj );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeNoPtrsT >::uchar_t
        >::const_existing_type
NS(TypeNoPtrs_c)( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
        SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::arch_size_t const idx ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_c( obj, idx );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
            TypeNoPtrsT >::uchar_t >::const_pointer
NS(TypeNoPtrs_const_c_begin)( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_const_c_begin( obj );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
            TypeNoPtrsT >::uchar_t >::const_pointer
NS(TypeNoPtrs_const_c_end)( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_const_c_end( obj );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
            TypeNoPtrsT >::uchar_t >::pointer
NS(TypeNoPtrs_c_begin)( SIXTRL_BUFFER_DATAPTR_DEC
    TypeNoPtrsT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_c_begin( obj );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
            TypeNoPtrsT >::uchar_t >::pointer
NS(TypeNoPtrs_c_end)( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_const_c_end( obj );
}

template< class TypeNoPtrsT, typename UCharArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_set_c_value)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::arch_size_t const idx, UCharArg c_value )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_set_c_value(
        obj, idx, c_value );
}

template< class TypeNoPtrsT, typename UCharArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_set_all_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::arch_size_t const idx, UCharArg c_value )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_set_all_c_values(
        obj, idx, c_value );
}

template< class TypeNoPtrsT, typename UCharIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_set_c)( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
    SIXTRL_RESTRICT obj, UCharIter c_values_begin )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeNoPtrs_set_c( obj, c_values_begin );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* ------------------------------------------------------------------------- */
/* a: */

SIXTRL_STATIC SIXTRL_FN NS(test_objs_real_t) NS(TypeNoPtrs_default_a)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(TypeNoPtrs_set_default_a)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(test_objs_real_t)
NS(TypeNoPtrs_a)( SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_set_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const a ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* b: */

SIXTRL_STATIC SIXTRL_FN NS(test_objs_int_t) NS(TypeNoPtrs_default_b)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(TypeNoPtrs_set_default_b)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(test_objs_int_t)
NS(TypeNoPtrs_b)( SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_set_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_int_t) const b ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* c: */

SIXTRL_STATIC SIXTRL_FN NS(test_objs_uchar_t) NS(TypeNoPtrs_default_c)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(TypeNoPtrs_set_default_c)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_address_t) NS(TypeNoPtrs_c_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_size_t)
NS(TypeNoPtrs_c_length)( SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs)
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(test_objs_uchar_t) NS(TypeNoPtrs_c)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT obj,
    NS(arch_size_t) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const*
NS(TypeNoPtrs_const_c_begin)( SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs)
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const*
NS(TypeNoPtrs_const_c_end)( SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs)
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t)*
NS(TypeNoPtrs_c_begin)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t)*
NS(TypeNoPtrs_c_end)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_set_c_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(arch_size_t) const idx, NS(test_objs_uchar_t) const c_value
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_set_all_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_uchar_t) const c_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_set_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const*
        SIXTRL_RESTRICT c_values_begin ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* ------------------------------------------------------------------------- */
/* a: */

SIXTRL_INLINE NS(test_objs_real_t) NS(TypeNoPtrs_default_a)(
    void ) SIXTRL_NOEXCEPT
{
    return ( NS(test_objs_real_t) )0;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_set_default_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a = NS(TypeNoPtrs_default_a)();
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(test_objs_real_t) NS(TypeNoPtrs_a)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(TypeNoPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->a;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_set_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const a ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a = a;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* b: */

SIXTRL_INLINE NS(test_objs_int_t) NS(TypeNoPtrs_default_b)(
    void ) SIXTRL_NOEXCEPT
{
    return ( NS(test_objs_int_t) )0;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_set_default_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->b = NS(TypeNoPtrs_default_b)();
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(test_objs_int_t) NS(TypeNoPtrs_b)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(TypeNoPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->b;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_set_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_int_t) const b ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->b = b;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* c: */

SIXTRL_INLINE NS(test_objs_uchar_t) NS(TypeNoPtrs_default_c)(
    void ) SIXTRL_NOEXCEPT
{
    return ( NS(test_objs_uchar_t) )0;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_set_default_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    NS(arch_size_t) ii = ( NS(arch_size_t) )0u;
    NS(arch_size_t) const nn = NS(TypeNoPtrs_c_length)( obj );

    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );

    for( ; ii < nn ; ++ii )
    {
        obj->c[ ii ] = NS(TypeNoPtrs_default_c)();
    }

    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_address_t) NS(TypeNoPtrs_c_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return ( NS(arch_address_t) )( uintptr_t )&obj->c[ 0 ];

}

SIXTRL_INLINE NS(arch_size_t) NS(TypeNoPtrs_c_length)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(TypeNoPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    ( void )obj;
    return ( NS(arch_size_t) )6u;
}

SIXTRL_INLINE NS(test_objs_uchar_t) NS(TypeNoPtrs_c)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT obj,
    NS(arch_size_t) const idx ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( idx < NS(TypeNoPtrs_c_length)( obj ) );
    return obj->c[ idx ];
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const*
NS(TypeNoPtrs_const_c_begin)( SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs)
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return &obj->c[ 0 ];
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const*
NS(TypeNoPtrs_const_c_end)( SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs)
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return &obj->c[ NS(TypeNoPtrs_c_length)( obj ) ];
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t)*
NS(TypeNoPtrs_c_begin)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return &obj->c[ 0 ];
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t)*
NS(TypeNoPtrs_c_end)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return &obj->c[ NS(TypeNoPtrs_c_length)( obj ) ];
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_set_c_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(arch_size_t) const idx,
    NS(test_objs_uchar_t) const c_value ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    if( idx < NS(TypeNoPtrs_c_length)( obj ) )
    {
        obj->c[ idx ] = c_value;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_set_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const*
        SIXTRL_RESTRICT c_values_it ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t)* uchar_it_t;
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    uchar_it_t it  = NS(TypeNoPtrs_c_begin)( obj );
    uchar_it_t end = NS(TypeNoPtrs_c_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( c_values_it != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it, ++c_values_it ) *it = *c_values_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_set_all_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_uchar_t) const c_value ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t)* uchar_it_t;
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    uchar_it_t it  = NS(TypeNoPtrs_c_begin)( obj );
    uchar_it_t end = NS(TypeNoPtrs_c_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it ) *it = c_value;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_API_H__ */
