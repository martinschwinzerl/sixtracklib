#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_API_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    /* a: */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
            TypeT >::real_t >::type
    TypeConstNumPtrs_default_a( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT /*obj*/ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return typename st::tests::TypeConstNumPtrsTraits< TypeT >::real_t{ 0 };
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_default_a(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "TypeT required to be a const-num-ptrs class" );

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( obj != SIXTRL_NULLPTR )
        {
            obj->a = st::tests::TypeConstNumPtrs_default_a( obj );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
            TypeT >::real_t >::const_existing_type
    TypeConstNumPtrs_a( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "TypeT required to be a const-num-ptrs class" );

        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return obj->a;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealArg /*a_value*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT
                >::real_t >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, RealArg a_value )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        obj->a = a_value;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, RealArg a_value )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        obj->a = std::move( a_value );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
        RealArg a_value )
    {
        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
            TypeT >::real_t real_t;

        return ( obj != SIXTRL_NULLPTR )
            ? SIXTRL_CXX_NAMESPACE::Types_perform_assignment<
                src_real_t, real_t >( obj->a, a_value )
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* b: */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::tests::objs_addr_t >::type
    TypeConstNumPtrs_default_b_addr( SIXTRL_BUFFER_DATAPTR_DEC const TypeT
        *const SIXTRL_RESTRICT /*obj*/ = SIXTRL_NULLPTR )
    {
        return SIXTRL_CXX_NAMESPACE::tests::objs_addr_t{ 0 };
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_num_b_values(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT /*obj*/,
        objs_size_t const /*num_b_values*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_num_b_values(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
        objs_size_t const num_b_values ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        obj->num_b_values = num_b_values;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::tests::objs_size_t >::type
    TypeConstNumPtrs_b_length( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT /* obj */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::tests::objs_size_t{ 0 };
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t >::type
    TypeConstNumPtrs_b_length( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT obj )SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return obj->num_b_values;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::tests::objs_addr_t >::type
    TypeConstNumPtrs_b_addr( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT /* obj */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::tests::objs_addr_t{ 0 };
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::tests::objs_addr_t >::type
    TypeConstNumPtrs_b_addr( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return obj->b_addr;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    TypeConstNumPtrs_set_default_num_b_values(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        obj->num_b_values = SIXTRL_CXX_NAMESPACE::tests::objs_size_t{ 0 };
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        SIXTRL_BUFFER_DATAPTR_DEC typename
            SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
                SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT
                    >::real_t >::const_pointer >::type
    TypeConstNumPtrs_const_b_begin( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT /* obj */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_NULLPTR;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ),
        SIXTRL_BUFFER_DATAPTR_DEC typename
            SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
                SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT
                    >::real_t >::const_pointer >::type
    TypeConstNumPtrs_const_b_begin( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename st::TypeMethodParamTraits<
                    real_t >::const_pointer ptr_t;

        return reinterpret_cast< ptr_t >( static_cast< std::uintptr_t >(
            st::tests::TypeConstNumPtrs_b_addr( obj ) ) );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t >::const_pointer
    TypeConstNumPtrs_const_b_end( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        auto end_ptr = st::tests::TypeConstNumPtrs_const_b_begin( obj );
        if( end_ptr != SIXTRL_NULLPTR )
        {
            end_ptr = end_ptr + st::tests::TypeConstNumPtrs_b_length( obj );
        }

        return end_ptr;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
        SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t >::pointer
    TypeConstNumPtrs_b_begin( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename st::TypeMethodParamTraits<
                    real_t >::pointer ptr_t;

        return const_cast< ptr_t >(
            st::tests::TypeConstNumPtrs_const_b_begin( obj ) );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
        SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT >::real_t
                >::pointer
    TypeConstNumPtrs_b_end( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename st::TypeMethodParamTraits<
                    real_t >::pointer ptr_t;

        return const_cast< ptr_t >(
            st::tests::TypeConstNumPtrs_const_b_end( obj ) );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT
            >::real_t >::type
    TypeConstNumPtrs_b( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT /* obj */, objs_size_t const /* idx */ )
    {
        return typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
            TypeT >::real_t{ 0 };
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ), typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
            typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t >::const_existing_type >::type
    TypeConstNumPtrs_b( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT obj, objs_size_t const idx ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename st::TypeMethodParamTraits<
                    real_t >::const_pointer ptr_t;

        ptr_t ptr = st::tests::TypeConstNumPtrs_const_b_begin( obj );
        SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( idx < st::tests::TypeConstNumPtrs_b_length( obj ) );

        return ptr[ idx ];
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_b_addr(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT /* obj */,
        objs_addr_t const /* b_addr */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_b_addr( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, objs_addr_t const b_addr ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        obj->b_addr = b_addr;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_b_value( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, objs_size_t const /*idx*/,
        RealArg /*b_value*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_b_value( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, objs_size_t const idx, RealArg b_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        ptr_t ptr = st::tests::TypeConstNumPtrs_b_begin( obj );

        if( ( ptr != SIXTRL_NULLPTR ) &&
            ( idx < st::tests::TypeConstNumPtrs_b_length( obj ) ) )
        {
            ptr[ idx ] = b_value;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_b_value( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, objs_size_t const idx, RealArg b_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        ptr_t ptr = st::tests::TypeConstNumPtrs_b_begin( obj );

        if( ( ptr != SIXTRL_NULLPTR ) &&
            ( idx < st::tests::TypeConstNumPtrs_b_length( obj ) ) )
        {
            ptr[ idx ] = std::move( b_value );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_b_value( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, objs_size_t const idx, RealArg b_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        ptr_t ptr = st::tests::TypeConstNumPtrs_b_begin( obj );
        return ( ( ptr != SIXTRL_NULLPTR ) &&
                 ( idx < st::tests::TypeConstNumPtrs_b_length( obj ) ) )
            ? st::Types_perform_assignment< typename std::decay< RealArg
                >::type, real_t >( ptr[ idx ], b_value )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_all_b_values( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealArg /*b_value*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        ( SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() ||
          SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() ),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_all_b_values(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg b_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        ptr_t it  = st::tests::TypeConstNumPtrs_b_begin( obj );
        ptr_t end = st::tests::TypeConstNumPtrs_b_end( obj );

        if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
        {
            for( ; it != end ; ++it ) *it = b_value;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_all_b_values(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg b_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        ptr_t it  = st::tests::TypeConstNumPtrs_b_begin( obj );
        ptr_t end = st::tests::TypeConstNumPtrs_b_end( obj );

        if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
        {
            real_t b;

            if( st::ARCH_STATUS_SUCCESS == st::Types_perform_assignment<
                typename std::decay< RealArg >::type, real_t >( b, b_value ) )
            {
                for( ; it != end ; ++it ) *it = b;
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_b( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealIter /*b_value*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        ( SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::iterator_traits< RealIter >::value_type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() ||
          SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::iterator_traits< RealIter >::value_type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() ),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealIter in_it )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        ptr_t it  = st::tests::TypeConstNumPtrs_b_begin( obj );
        ptr_t end = st::tests::TypeConstNumPtrs_b_end( obj );

        if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
        {
            for( ; it != end ; ++it, ++in_it ) *it = *in_it;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::iterator_traits< RealIter >::value_type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::iterator_traits< RealIter >::value_type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealIter in_it )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        ptr_t it  = st::tests::TypeConstNumPtrs_b_begin( obj );
        ptr_t end = st::tests::TypeConstNumPtrs_b_end( obj );

        if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
        {
            typedef typename std::iterator_traits<
                RealIter >::value_type src_real_t;

            status = st::ARCH_STATUS_SUCCESS;

            while( ( status == st::ARCH_STATUS_SUCCESS ) && ( it != end ) )
            {
                status = st::Types_perform_assignment< src_real_t, real_t >(
                    *it++, *in_it++ );
            }
        }

        return status;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_default_b_addr( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /*obj*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_default_b_addr(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::tests::TypeConstNumPtrs_set_b_addr( obj,
                   st::tests::TypeConstNumPtrs_default_b_addr( obj ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* c: */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        SIXTRL_CXX_NAMESPACE::tests::objs_addr_t >::type
    TypeConstNumPtrs_default_c_addr( SIXTRL_BUFFER_DATAPTR_DEC const TypeT
        *const SIXTRL_RESTRICT /*obj*/ = SIXTRL_NULLPTR )
    {
        return SIXTRL_CXX_NAMESPACE::tests::objs_addr_t{ 0 };
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_num_c_values(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT /*obj*/,
        objs_size_t const /*num_c_values*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_num_c_values(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
        objs_size_t const num_c_values ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        obj->num_c_values = num_c_values;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    TypeConstNumPtrs_set_default_num_c_values(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        obj->num_c_values = SIXTRL_CXX_NAMESPACE::tests::objs_size_t{ 0 };
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::tests::objs_size_t >::type
    TypeConstNumPtrs_c_length( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT /* obj */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::tests::objs_size_t{ 0 };
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t >::type
    TypeConstNumPtrs_c_length( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT obj )SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return obj->num_c_values;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::tests::objs_addr_t >::type
    TypeConstNumPtrs_c_addr( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT /* obj */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::tests::objs_addr_t{ 0 };
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::tests::objs_addr_t >::type
    TypeConstNumPtrs_c_addr( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return obj->c_addr;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        SIXTRL_BUFFER_DATAPTR_DEC typename
            SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
                SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT
                    >::real_t >::const_pointer >::type
    TypeConstNumPtrs_const_c_begin( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT /* obj */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_NULLPTR;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ),
        SIXTRL_BUFFER_DATAPTR_DEC typename
            SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
                SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT
                    >::real_t >::const_pointer >::type
    TypeConstNumPtrs_const_c_begin( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename st::TypeMethodParamTraits<
                    real_t >::const_pointer ptr_t;

        return reinterpret_cast< ptr_t >( static_cast< std::uintptr_t >(
            st::tests::TypeConstNumPtrs_c_addr( obj ) ) );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t >::const_pointer
    TypeConstNumPtrs_const_c_end( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        auto end_ptr = st::tests::TypeConstNumPtrs_const_c_begin( obj );
        if( end_ptr != SIXTRL_NULLPTR )
        {
            end_ptr = end_ptr + st::tests::TypeConstNumPtrs_c_length( obj );
        }

        return end_ptr;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
        SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t >::pointer
    TypeConstNumPtrs_c_begin( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename st::TypeMethodParamTraits<
                    real_t >::pointer ptr_t;

        return const_cast< ptr_t >(
            st::tests::TypeConstNumPtrs_const_c_begin( obj ) );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
        SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t >::pointer
    TypeConstNumPtrs_c_end( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename st::TypeMethodParamTraits<
                    real_t >::pointer ptr_t;

        return const_cast< ptr_t >(
            st::tests::TypeConstNumPtrs_const_c_end( obj ) );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT
            >::real_t >::type
    TypeConstNumPtrs_c( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT /* obj */, objs_size_t const /* idx */ )
    {
        return typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
            TypeT >::real_t{ 0 };
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ), typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
            typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t >::const_existing_type >::type
    TypeConstNumPtrs_c( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT obj, objs_size_t const idx ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename st::TypeMethodParamTraits<
                    real_t >::const_pointer ptr_t;

        ptr_t ptr = st::tests::TypeConstNumPtrs_const_c_begin( obj );
        SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( idx < st::tests::TypeConstNumPtrs_c_length( obj ) );

        return ptr[ idx ];
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_c_addr(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT /* obj */,
        objs_addr_t const /* c_addr */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_c_addr( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, objs_addr_t const c_addr ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        obj->c_addr = c_addr;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_c_value( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, objs_size_t const /*idx*/,
        RealArg /*c_value*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_c_value( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, objs_size_t const idx, RealArg c_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        ptr_t ptr = st::tests::TypeConstNumPtrs_c_begin( obj );

        if( ( ptr != SIXTRL_NULLPTR ) &&
            ( idx < st::tests::TypeConstNumPtrs_c_length( obj ) ) )
        {
            ptr[ idx ] = c_value;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_c_value( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, objs_size_t const idx, RealArg c_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        ptr_t ptr = st::tests::TypeConstNumPtrs_c_begin( obj );

        if( ( ptr != SIXTRL_NULLPTR ) &&
            ( idx < st::tests::TypeConstNumPtrs_c_length( obj ) ) )
        {
            ptr[ idx ] = std::move( c_value );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_c_value( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, objs_size_t const idx, RealArg c_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        ptr_t ptr = st::tests::TypeConstNumPtrs_c_begin( obj );
        return ( ( ptr != SIXTRL_NULLPTR ) &&
                 ( idx < st::tests::TypeConstNumPtrs_c_length( obj ) ) )
            ? st::Types_perform_assignment< typename std::decay< RealArg
                >::type, real_t >( ptr[ idx ], c_value )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_all_c_values( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealArg /*c_value*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        ( SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() ||
          SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() ),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_all_c_values(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg c_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        ptr_t it  = st::tests::TypeConstNumPtrs_c_begin( obj );
        ptr_t end = st::tests::TypeConstNumPtrs_c_end( obj );

        if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
        {
            for( ; it != end ; ++it ) *it = c_value;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_all_c_values(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg c_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        ptr_t it  = st::tests::TypeConstNumPtrs_c_begin( obj );
        ptr_t end = st::tests::TypeConstNumPtrs_c_end( obj );

        if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
        {
            real_t b;

            if( st::ARCH_STATUS_SUCCESS == st::Types_perform_assignment<
                typename std::decay< RealArg >::type, real_t >( b, c_value ) )
            {
                for( ; it != end ; ++it ) *it = b;
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealIter /*c_value*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        ( SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::iterator_traits< RealIter >::value_type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() ||
          SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::iterator_traits< RealIter >::value_type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() ),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_c(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealIter in_it )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        ptr_t it  = st::tests::TypeConstNumPtrs_c_begin( obj );
        ptr_t end = st::tests::TypeConstNumPtrs_c_end( obj );

        if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
        {
            for( ; it != end ; ++it, ++in_it ) *it = *in_it;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >() ||
          SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_std_vector<
              TypeT >() ) &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::iterator_traits< RealIter >::value_type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::iterator_traits< RealIter >::value_type,
            typename TypeConstNumPtrsTraits< TypeT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_c(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealIter in_it )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename TypeConstNumPtrsTraits< TypeT >::real_t real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename
            st::TypeMethodParamTraits< real_t >::pointer ptr_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        ptr_t it  = st::tests::TypeConstNumPtrs_c_begin( obj );
        ptr_t end = st::tests::TypeConstNumPtrs_c_end( obj );

        if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
        {
            typedef typename std::iterator_traits<
                RealIter >::value_type src_real_t;

            status = st::ARCH_STATUS_SUCCESS;

            while( ( status == st::ARCH_STATUS_SUCCESS ) && ( it != end ) )
            {
                status = st::Types_perform_assignment< src_real_t, real_t >(
                    *it++, *in_it++ );
            }
        }

        return status;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_default_c_addr( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /*obj*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_set_default_c_addr(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::tests::TypeConstNumPtrs_set_c_addr( obj,
                   st::tests::TypeConstNumPtrs_default_c_addr( obj ) );
    }

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

/* a: */

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT >::real_t
NS(TypeConstNumPtrs_default_a)( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
    SIXTRL_RESTRICT obj = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_default_a( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_default_a)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_default_a( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
        TypeT >::real_t >::const_existing_type
NS(TypeConstNumPtrs_a)( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_a( obj );
}

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_a)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg a_value )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_set_a( obj, a_value );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* b: */

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_CXX_NAMESPACE::tests::objs_addr_t
NS(TypeConstNumPtrs_default_b_addr)( SIXTRL_BUFFER_DATAPTR_DEC const TypeT
    *const SIXTRL_RESTRICT obj = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_default_b_addr( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_CXX_NAMESPACE::arch_status_t NS(TypeConstNumPtrs_set_num_b_values)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const
        num_b_values ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_set_num_b_values(
        obj, num_b_values );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_default_num_b_values)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_set_default_num_b_values( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_default_b_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_set_default_b_addr( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_CXX_NAMESPACE::tests::objs_size_t NS(TypeConstNumPtrs_b_length)(
    SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const SIXTRL_RESTRICT obj )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_b_length( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_CXX_NAMESPACE::tests::objs_addr_t NS(TypeConstNumPtrs_b_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_b_addr( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT >::real_t
            >::const_pointer
NS(TypeConstNumPtrs_const_b_begin)( SIXTRL_BUFFER_DATAPTR_DEC const TypeT
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_const_b_begin( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT >::real_t
            >::const_pointer
NS(TypeConstNumPtrs_const_b_end)( SIXTRL_BUFFER_DATAPTR_DEC const TypeT
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_const_b_end( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
            TypeT >::real_t >::pointer
NS(TypeConstNumPtrs_b_begin)( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_b_begin( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
            TypeT >::real_t >::pointer
NS(TypeConstNumPtrs_b_end)( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_b_end( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT >::real_t
    >::const_existing_type
NS(TypeConstNumPtrs_b)( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
    SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const idx ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_b( obj, idx );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_b_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const b_addr ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_set_b_addr(
        obj, b_addr );
}

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_b_value)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const idx,
    RealArg b_value )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_set_b_value(
        obj, idx, b_value );
}

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_all_b_values)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const idx, RealArg b_value )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_set_all_b_values(
        obj, idx, b_value );
}

template< class TypeT, typename RealIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_b)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const idx, RealIter in_it )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_set_b(
        obj, idx, in_it );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* c: */

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_CXX_NAMESPACE::tests::objs_addr_t
NS(TypeConstNumPtrs_default_c_addr)( SIXTRL_BUFFER_DATAPTR_DEC const TypeT
    *const SIXTRL_RESTRICT obj = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_default_c_addr( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_CXX_NAMESPACE::arch_status_t NS(TypeConstNumPtrs_set_num_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const
        num_c_values ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_set_num_c_values(
        obj, num_c_values );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_default_num_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_set_default_num_c_values( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_default_c_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_set_default_c_addr( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_CXX_NAMESPACE::tests::objs_size_t NS(TypeConstNumPtrs_c_length)(
    SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const SIXTRL_RESTRICT obj )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_c_length( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_CXX_NAMESPACE::tests::objs_addr_t NS(TypeConstNumPtrs_c_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_c_addr( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT >::real_t
            >::const_pointer
NS(TypeConstNumPtrs_const_c_begin)( SIXTRL_BUFFER_DATAPTR_DEC const TypeT
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_const_c_begin( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT >::real_t
            >::const_pointer
NS(TypeConstNumPtrs_const_c_end)( SIXTRL_BUFFER_DATAPTR_DEC const TypeT
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_const_c_end( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
            TypeT >::real_t >::pointer
NS(TypeConstNumPtrs_c_begin)( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_c_begin( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
            TypeT >::real_t >::pointer
NS(TypeConstNumPtrs_c_end)( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_c_end( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
    SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits< TypeT >::real_t
    >::const_existing_type
NS(TypeConstNumPtrs_c)( SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
    SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const idx ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_c( obj, idx );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_c_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const c_addr ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_set_c_addr(
        obj, c_addr );
}

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_c_value)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const idx,
    RealArg c_value )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_set_c_value(
        obj, idx, c_value );
}

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_all_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const idx, RealArg c_value )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_set_all_c_values(
        obj, idx, c_value );
}

template< class TypeT, typename RealIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_set_c)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const idx, RealIter in_it )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_set_c(
        obj, idx, in_it );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* a: */

SIXTRL_STATIC SIXTRL_FN NS(test_objs_real_t) NS(TypeConstNumPtrs_default_a)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_set_default_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(test_objs_real_t) NS(TypeConstNumPtrs_a)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_set_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const a_value ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* b: */

SIXTRL_STATIC SIXTRL_FN NS(test_objs_addr_t)
NS(TypeConstNumPtrs_default_b_addr)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(test_objs_size_t)
NS(TypeConstNumPtrs_b_length)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(TypeConstNumPtrs_set_default_b_addr)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(TypeConstNumPtrs_set_num_b_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_size_t) const num_b_values ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(TypeConstNumPtrs_set_default_num_b_values)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(test_objs_addr_t)
NS(TypeConstNumPtrs_b_addr)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
NS(TypeConstNumPtrs_const_b_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
NS(TypeConstNumPtrs_const_b_end)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)*
NS(TypeConstNumPtrs_b_begin)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)*
NS(TypeConstNumPtrs_b_end)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(test_objs_real_t) NS(TypeConstNumPtrs_b)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT obj, NS(test_objs_size_t) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_set_b_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_addr_t) const b_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_set_b_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_size_t) const idx,
    NS(test_objs_real_t) const b_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_set_all_b_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const b_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_set_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT in_it ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* c: */

SIXTRL_STATIC SIXTRL_FN NS(test_objs_addr_t)
NS(TypeConstNumPtrs_default_c_addr)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(test_objs_size_t) NS(TypeConstNumPtrs_c_length)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(test_objs_addr_t) NS(TypeConstNumPtrs_c_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(TypeConstNumPtrs_set_default_c_addr)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(TypeConstNumPtrs_set_default_num_c_values)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_set_num_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_size_t) const num_c_values ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
NS(TypeConstNumPtrs_const_c_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
NS(TypeConstNumPtrs_const_c_end)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)*
NS(TypeConstNumPtrs_c_begin)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)*
NS(TypeConstNumPtrs_c_end)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(test_objs_real_t) NS(TypeConstNumPtrs_c)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT obj, NS(test_objs_size_t) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_set_c_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_addr_t) const c_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_set_c_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_size_t) const idx,
    NS(test_objs_real_t) const c_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_set_all_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const c_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_set_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT in_it ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* a: */

SIXTRL_INLINE  NS(test_objs_real_t)
NS(TypeConstNumPtrs_default_a)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(test_objs_real_t) )0;
}

SIXTRL_INLINE  NS(arch_status_t) NS(TypeConstNumPtrs_set_default_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a = NS(TypeConstNumPtrs_default_a)();
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE  NS(test_objs_real_t) NS(TypeConstNumPtrs_a)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->a;
}

SIXTRL_INLINE  NS(arch_status_t) NS(TypeConstNumPtrs_set_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const a_value ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a = a_value;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* b: */

SIXTRL_INLINE  NS(test_objs_addr_t)
NS(TypeConstNumPtrs_default_b_addr)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(test_objs_addr_t) )0;
}

SIXTRL_INLINE  NS(test_objs_size_t) NS(TypeConstNumPtrs_b_length)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->num_b_values;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_set_default_b_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT
{
    return NS(TypeConstNumPtrs_set_b_addr)(
        obj, NS(TypeConstNumPtrs_default_b_addr)() );
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_set_default_num_b_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->num_b_values = ( NS(test_objs_size_t) )0;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_set_num_b_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_size_t) const num_b_values ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->num_b_values = num_b_values;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE  NS(test_objs_addr_t) NS(TypeConstNumPtrs_b_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->b_addr;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
NS(TypeConstNumPtrs_const_b_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const* )(
        uintptr_t )obj->b_addr;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
NS(TypeConstNumPtrs_const_b_end)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const* ptr =
        NS(TypeConstNumPtrs_const_b_begin)( obj );

    if( ptr != SIXTRL_NULLPTR )
    {
        ptr = ptr + NS(TypeConstNumPtrs_b_length)( obj );
    }

    return ptr;
}

SIXTRL_INLINE  SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)*
NS(TypeConstNumPtrs_b_begin)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* )(
        uintptr_t )obj->b_addr;
}

SIXTRL_INLINE  SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)*
NS(TypeConstNumPtrs_b_end)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* ptr =
        NS(TypeConstNumPtrs_b_begin)( obj );

    if( ptr != SIXTRL_NULLPTR )
    {
        ptr = ptr + NS(TypeConstNumPtrs_b_length)( obj );
    }

    return ptr;
}

SIXTRL_INLINE  NS(test_objs_real_t) NS(TypeConstNumPtrs_b)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT obj, NS(test_objs_size_t) const idx ) SIXTRL_NOEXCEPT
{
    SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const* ptr =
        NS(TypeConstNumPtrs_const_b_begin)( obj );

    SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( idx < NS(TypeConstNumPtrs_b_length)( obj ) );

    return ptr[ idx ];
}

SIXTRL_INLINE  NS(arch_status_t) NS(TypeConstNumPtrs_set_b_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_addr_t) const b_addr ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->b_addr = b_addr;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE  NS(arch_status_t) NS(TypeConstNumPtrs_set_b_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_size_t) const idx,
    NS(test_objs_real_t) const b_value ) SIXTRL_NOEXCEPT

{
    SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* ptr =
        NS(TypeConstNumPtrs_b_begin)( obj );

    SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( idx < NS(TypeConstNumPtrs_b_length)( obj ) );

    ptr[ idx ] = b_value;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE  NS(arch_status_t) NS(TypeConstNumPtrs_set_all_b_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const b_value ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* it =
        NS(TypeConstNumPtrs_b_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* end =
        NS(TypeConstNumPtrs_b_begin)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it ) *it = b_value;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE  NS(arch_status_t) NS(TypeConstNumPtrs_set_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT in_it ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* it =
        NS(TypeConstNumPtrs_b_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* end =
        NS(TypeConstNumPtrs_b_begin)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( in_it != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it, ++in_it ) *it = *in_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* c: */

SIXTRL_INLINE  NS(test_objs_addr_t)
NS(TypeConstNumPtrs_default_c_addr)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(test_objs_addr_t) )0;
}

SIXTRL_INLINE  NS(test_objs_size_t)
NS(TypeConstNumPtrs_c_length)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->num_c_values;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_set_default_c_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT
{
    return NS(TypeConstNumPtrs_set_c_addr)( obj,
        NS(TypeConstNumPtrs_default_c_addr)() );
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_set_default_num_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->num_c_values = ( NS(test_objs_size_t) )0;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_set_num_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_size_t) const num_c_values ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->num_c_values = num_c_values;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE  NS(test_objs_addr_t)
NS(TypeConstNumPtrs_c_addr)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->c_addr;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
NS(TypeConstNumPtrs_const_c_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const* )(
        uintptr_t )obj->c_addr;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
NS(TypeConstNumPtrs_const_c_end)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const* ptr =
        NS(TypeConstNumPtrs_const_c_begin)( obj );

    if( ptr != SIXTRL_NULLPTR )
    {
        ptr = ptr + NS(TypeConstNumPtrs_c_length)( obj );
    }

    return ptr;
}

SIXTRL_INLINE  SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)*
NS(TypeConstNumPtrs_c_begin)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* )(
        uintptr_t )obj->c_addr;
}

SIXTRL_INLINE  SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)*
NS(TypeConstNumPtrs_c_end)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* ptr =
        NS(TypeConstNumPtrs_c_begin)( obj );

    if( ptr != SIXTRL_NULLPTR )
    {
        ptr = ptr + NS(TypeConstNumPtrs_c_length)( obj );
    }

    return ptr;
}

SIXTRL_INLINE  NS(test_objs_real_t) NS(TypeConstNumPtrs_c)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT obj, NS(test_objs_size_t) const idx ) SIXTRL_NOEXCEPT
{
    SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const* ptr =
        NS(TypeConstNumPtrs_const_c_begin)( obj );

    SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( idx < NS(TypeConstNumPtrs_c_length)( obj ) );

    return ptr[ idx ];
}

SIXTRL_INLINE  NS(arch_status_t) NS(TypeConstNumPtrs_set_c_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_addr_t) const c_addr ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->c_addr = c_addr;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE  NS(arch_status_t) NS(TypeConstNumPtrs_set_c_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_size_t) const idx,
    NS(test_objs_real_t) const c_value ) SIXTRL_NOEXCEPT
{
    SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* ptr =
        NS(TypeConstNumPtrs_c_begin)( obj );

    SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( idx < NS(TypeConstNumPtrs_c_length)( obj ) );

    ptr[ idx ] = c_value;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE  NS(arch_status_t) NS(TypeConstNumPtrs_set_all_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const c_value ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* it =
        NS(TypeConstNumPtrs_c_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* end =
        NS(TypeConstNumPtrs_c_begin)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it ) *it = c_value;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE  NS(arch_status_t) NS(TypeConstNumPtrs_set_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT in_it ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* it =
        NS(TypeConstNumPtrs_c_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* end =
        NS(TypeConstNumPtrs_c_begin)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( in_it != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it, ++in_it ) *it = *in_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_API_H__ */
