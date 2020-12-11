#ifndef SIXTRACKLIB_COMMON_INTERNAL_OBJ_ADDR_BASED_POINTER_FIELD_H__
#define SIXTRACKLIB_COMMON_INTERNAL_OBJ_ADDR_BASED_POINTER_FIELD_H__

#if defined( __cplusplus )
#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <iterator>
    #include <memory>
    #include <vector>
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */
#endif /* C++ */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class E >
    struct ObjDataAddrPointerFieldTraits
    {
        typedef SIXTRL_CXX_NAMESPACE::arch_address_t address_t;
        static constexpr address_t DEFAULT_ADDR = address_t{ 0 };
    };

    template< class E >
    constexpr typename ObjDataAddrPointerFieldTraits< E >::address_t
        ObjDataAddrPointerFieldTraits< E >::DEFAULT_ADDR;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E >
    SIXTRL_STATIC constexpr SIXTRL_FN
    typename ObjDataAddrPointerFieldTraits< E >::address_t
    ObjData_default_field_addr( SIXTRL_ARGPTR_DEC const E *const /* obj */ =
        SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataAddrPointerFieldTraits< E >::DEFAULT_ADDR;
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
    ObjData_set_field_addr(
        typename ObjDataAddrPointerFieldTraits<
            E >::address_t& SIXTRL_RESTRICT_REF dest_field_addr,
        typename ObjDataAddrPointerFieldTraits<
            E >::address_t const new_addr_value,
        SIXTRL_ARGPTR_DEC const E *const /* obj */ = SIXTRL_NULLPTR
    ) SIXTRL_NOEXCEPT
    {
        dest_field_addr = new_addr_value;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
    ObjData_set_default_field_addr(
        typename ObjDataAddrPointerFieldTraits<
            E >::address_t& SIXTRL_RESTRICT_REF dest_field_addr,
        SIXTRL_ARGPTR_DEC const E *const /*obj*/ =
            SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        dest_field_addr = st::ObjData_default_field_addr< E >();
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* --------------------------------------------------------------------- */

    template< class E, typename FieldT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename ObjDataAddrPointerFieldTraits< E >::address_t
    ObjData_field_begin_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_adr,
        SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT /* obj */ =
            SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return field_adr;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class E, typename PtrT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !std::is_pointer< PtrT >::value, PtrT >::type
    ObjData_field_ptr_to_begin_from_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t
            const /*field_adr*/,
        SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT /* obj */ =
            SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        static_assert( std::is_pointer< PtrT >::value,
            "PtrT required to be a ptr" );
        return PtrT{};
    }

    template< class E, typename PtrT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        std::is_pointer< PtrT >::value, PtrT >::type
    ObjData_field_ptr_to_begin_from_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_adr,
        SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT /* obj */ =
            SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< PtrT >(
            static_cast< std::uintptr_t >( field_adr ) );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class E, typename FieldT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename ObjDataAddrPointerFieldTraits< E >::address_t
    ObjData_field_end_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_adr,
        arch_size_t const num_elements,
        SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT /* obj */ =
            SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return field_adr + sizeof( FieldT ) * num_elements;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class E, typename PtrT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !std::is_pointer< PtrT >::value, PtrT >::type
    ObjData_field_ptr_to_end_from_addr(
        typename ObjDataAddrPointerFieldTraits<
            E >::address_t const /*field_adr*/,
        arch_size_t const /*num_elements*/,
        SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT /* obj */ =
            SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return PtrT{};
    }


    template< class E, typename PtrT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        std::is_pointer< PtrT >::value, PtrT >::type
    ObjData_field_ptr_to_end_from_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_adr,
        arch_size_t const num_elements,
        SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT /*obj*/ =
            SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        typedef typename std::iterator_traits< PtrT >::value_type field_t;
        return reinterpret_cast< PtrT >( static_cast< std::uintptr_t >(
            field_adr + sizeof( field_t ) * num_elements ) );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class E, typename FieldT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename ObjDataAddrPointerFieldTraits< E >::address_t
    ObjData_get_field_addr_from_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_adr,
        arch_size_t const num_elements, arch_size_t const idx,
        SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT /*obj*/ =
            SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        typedef typename std::decay< FieldT >::value_type value_t;
        SIXTRL_ASSERT( field_adr != typename ObjDataAddrPointerFieldTraits<
            E >::address_t{ 0 } );

        SIXTRL_ASSERT( idx < num_elements );
        ( void )num_elements;

        return field_adr + sizeof( value_t ) * idx;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class E, typename PtrT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !std::is_pointer< PtrT >::value, PtrT >::type
    ObjData_get_field_value_from_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t
            const /*field_adr*/, arch_size_t const /* num_elements */,
        arch_size_t const /* idx */, SIXTRL_ARGPTR_DEC const E *const
            SIXTRL_RESTRICT /*obj*/ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        static_assert( std::is_pointer< PtrT >::value,
            "PtrT has to be a pointer-type!" );
        return PtrT{};
    }

    template< class E, typename PtrT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        std::is_pointer< PtrT >::value,
        typename TypeMethodParamTraits< typename std::iterator_traits<
            PtrT >::value_type >::const_existing_type >::type
    ObjData_get_field_value_from_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_adr,
        arch_size_t const num_elements, arch_size_t const idx,
        SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT /*obj*/ =
            SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        auto ptr = st::ObjData_field_ptr_to_begin_from_addr<
            E, PtrT >( field_adr );

        SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( idx < num_elements );
        ( void )num_elements;

        return ptr[ idx ];
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class E, typename PtrT, typename Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !std::is_pointer< PtrT >::value,
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ObjData_set_field_value_for_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t
            const /*field_addr*/,
        arch_size_t const /* length */, arch_size_t const /* idx */,
        Arg /* arg */, SIXTRL_ARGPTR_DEC const E *const
            SIXTRL_RESTRICT /*obj*/ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class E, typename PtrT, typename Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        std::is_pointer< PtrT >::value &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Arg,
            typename std::iterator_traits< PtrT >::value_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ObjData_set_field_value_for_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_addr,
        arch_size_t const length, arch_size_t const idx, Arg value,
        SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            /*obj*/ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        PtrT ptr = st::ObjData_field_ptr_to_begin_from_addr<
            E, PtrT >( field_addr );

        SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( idx < length );
        ptr[ idx ] = value;
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class E, typename PtrT, typename Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        std::is_pointer< PtrT >::value &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Arg,
            typename std::iterator_traits< PtrT >::value_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< Arg,
            typename std::iterator_traits< PtrT >::value_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ObjData_set_field_value_for_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_addr,
        arch_size_t const length, arch_size_t const idx, Arg value,
        SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            /*obj*/ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        PtrT ptr = st::ObjData_field_ptr_to_begin_from_addr<
            E, PtrT >( field_addr );

        SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( idx < length );
        ptr[ idx ] = std::move( value );
        return st::ARCH_STATUS_SUCCESS;
    }

    template< class E, typename PtrT, typename Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        std::is_pointer< PtrT >::value &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Arg,
            typename std::iterator_traits< PtrT >::value_type >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< Arg,
            typename std::iterator_traits< PtrT >::value_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ObjData_set_field_value_for_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_addr,
        arch_size_t const length, arch_size_t const idx, Arg value,
        SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            /*obj*/ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< Arg >::type src_val_t;
        typedef typename std::iterator_traits< PtrT >::value_type dst_val_t;

        PtrT ptr = st::ObjData_field_ptr_to_begin_from_addr<
            E, PtrT >( field_addr );

        SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( idx < length );

        return st::Types_perform_assignment< src_val_t, dst_val_t >(
            ptr[ idx ], value );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class E, typename PtrT, typename Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !std::is_pointer< PtrT >::value,
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ObjData_set_all_field_values_for_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t
            const /*field_addr*/,
        arch_size_t const /* length */, arch_size_t const /* idx */,
        Arg /* arg */, SIXTRL_ARGPTR_DEC const E *const
            SIXTRL_RESTRICT /*obj*/ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class E, typename PtrT, typename Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        std::is_pointer< PtrT >::value &&
        ( SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Arg,
            typename std::iterator_traits< PtrT >::value_type >() ||
          SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< Arg,
            typename std::iterator_traits< PtrT >::value_type >() ),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ObjData_set_all_field_values_for_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_addr,
        arch_size_t const length, Arg value, SIXTRL_ARGPTR_DEC const E
            *const SIXTRL_RESTRICT /*obj*/ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        PtrT it = st::ObjData_field_ptr_to_begin_from_addr<
            E, PtrT >( field_addr );

        PtrT end = st::ObjData_field_ptr_to_end_from_addr<
            E, PtrT >( field_addr, length );

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
        {
            for( ; it != end ; ++it ) *it = value;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    template< class E, typename PtrT, typename Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        std::is_pointer< PtrT >::value &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Arg,
            typename std::iterator_traits< PtrT >::value_type >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< Arg,
            typename std::iterator_traits< PtrT >::value_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ObjData_set_all_field_values_for_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_addr,
        arch_size_t const length, Arg value, SIXTRL_ARGPTR_DEC const E
            *const SIXTRL_RESTRICT /*obj*/ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        PtrT it = st::ObjData_field_ptr_to_begin_from_addr<
            E, PtrT >( field_addr );

        PtrT end = st::ObjData_field_ptr_to_end_from_addr<
            E, PtrT >( field_addr, length );

        if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
        {
            typedef typename std::iterator_traits< PtrT >::value_type dst_val_t;
            typedef typename std::decay< Arg >::type src_val_t;

            dst_val_t temp;
            status = st::Types_perform_assignment< src_val_t, dst_val_t >(
                temp, value );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                for( ; it != end ; ++it ) *it = temp;
            }
        }

        return status;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class E, typename PtrT, typename Iter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !std::is_pointer< PtrT >::value, arch_status_t >::type
    ObjData_set_field_values_from_range_for_addr(
        typename ObjDataAddrPointerFieldTraits<
            E >::address_t const /*field_addr*/,
        arch_size_t const /* length */, Iter /* in_begin */,
        SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            /*obj*/ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class E, typename PtrT, typename Iter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        std::is_pointer< PtrT >::value &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::iterator_traits< Iter >::value_type,
            typename std::iterator_traits< PtrT >::value_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ObjData_set_field_values_from_range_for_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_addr,
        arch_size_t const length, Iter in_it, SIXTRL_ARGPTR_DEC const E
            *const SIXTRL_RESTRICT /*obj*/ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        PtrT it = st::ObjData_field_ptr_to_begin_from_addr<
            E, PtrT >( field_addr );

        PtrT end = st::ObjData_field_ptr_to_end_from_addr<
            E, PtrT >( field_addr, length );

        if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
        {
            for( ; it != end ; ++it, ++in_it ) *it = *in_it;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    template< class E, typename PtrT, typename Iter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        std::is_pointer< PtrT >::value &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::iterator_traits< Iter >::value_type,
            typename std::iterator_traits< PtrT >::value_type >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ObjData_set_field_values_from_range_for_addr(
        typename ObjDataAddrPointerFieldTraits< E >::address_t const field_addr,
        arch_size_t const length, Iter in_it, SIXTRL_ARGPTR_DEC const E
            *const SIXTRL_RESTRICT /*obj*/ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        PtrT it = st::ObjData_field_ptr_to_begin_from_addr<
            E, PtrT >( field_addr );

        PtrT end = st::ObjData_field_ptr_to_end_from_addr<
            E, PtrT >( field_addr, length );

        if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
        {
            typedef typename std::iterator_traits< Iter >::value_type src_val_t;
            typedef typename std::iterator_traits< PtrT >::value_type dst_val_t;

            status = st::ARCH_STATUS_SUCCESS;

            while( ( status == st::ARCH_STATUS_SUCCESS ) && ( it != end ) )
            {
                status = st::Types_perform_assignment<
                    src_val_t, dst_val_t >( *it++, *in_it++ );
            }
        }

        return status;
    }
}

template< class E >
SIXTRL_STATIC constexpr SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits< E >::address_t
NS(ObjData_default_field_addr)( SIXTRL_ARGPTR_DEC const E *const obj =
    SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ObjData_default_field_addr( obj );
}

template< class E >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ObjData_set_field_addr)(
    typename SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits<
        E >::address_t& SIXTRL_RESTRICT_REF dest_field_addr,
    typename SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits<
        E >::address_t const new_addr_value,
    SIXTRL_ARGPTR_DEC const E *const obj = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ObjData_set_field_addr(
        dest_field_addr, new_addr_value, obj );
}

template< class E >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ObjData_set_default_field_addr)(
    typename SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits<
        E >::address_t& SIXTRL_RESTRICT_REF dest_field_addr,
    SIXTRL_ARGPTR_DEC const E *const obj = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ObjData_set_default_field_addr(
        dest_field_addr, obj );
}

/* ------------------------------------------------------------------------- */

template< class E, typename FieldT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits< E >::address_t
NS(ObjData_field_begin_addr)(
    typename SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits<
        E >::address_t const field_addr,
    SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT obj = SIXTRL_NULLPTR
) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ObjData_field_begin_addr( field_addr, obj );
}

template< class E, typename PtrT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN PtrT
NS(ObjData_field_ptr_to_begin_from_addr)(
    typename SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits<
        E >::address_t const field_adr, SIXTRL_ARGPTR_DEC const E *const
        SIXTRL_RESTRICT obj = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ObjData_field_ptr_to_begin_from_addr(
        field_adr, obj );
}

template< class E, typename FieldT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits< E >::address_t
NS(ObjData_field_end_addr)(
    typename SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits<
        E >::address_t const field_adr,
    SIXTRL_CXX_NAMESPACE::arch_size_t const num_elements,
    SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT obj =
        SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ObjData_field_end_addr(
        field_adr, num_elements, obj );
}

template< class E, typename PtrT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN PtrT
NS(ObjData_field_ptr_to_end_from_addr)( typename
    SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits< E >::address_t
        const field_adr, SIXTRL_CXX_NAMESPACE::arch_size_t const num_elements,
    SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT obj =
        SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ObjData_field_ptr_to_end_from_addr(
        field_adr, num_elements, obj );
}

template< class E, typename FieldT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits< E >::address_t
NS(ObjData_get_field_addr_from_addr)(
    typename SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits<
        E >::address_t const field_adr,
    SIXTRL_CXX_NAMESPACE::arch_size_t const num_elements,
    SIXTRL_CXX_NAMESPACE::arch_size_t const idx,
    SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT obj =
        SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ObjData_get_field_addr_from_addr(
        field_adr, num_elements, idx, obj );
}

template< class E, typename PtrT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN PtrT
NS(ObjData_get_field_value_from_addr)( typename
    SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits< E >::address_t
        const field_adr,
    SIXTRL_CXX_NAMESPACE::arch_size_t const num_elements,
    SIXTRL_CXX_NAMESPACE::arch_size_t const idx,
    SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT obj =
        SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ObjData_get_field_value_from_addr(
        field_adr, num_elements, idx, obj );
}

template< class E, typename PtrT, typename Arg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ObjData_set_field_value_for_addr)( typename
    SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits< E >::address_t
        const field_addr,
    SIXTRL_CXX_NAMESPACE::arch_size_t const length,
    SIXTRL_CXX_NAMESPACE::arch_size_t const idx,
    Arg arg, SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT
        obj = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ObjData_set_field_value_for_addr(
        field_addr, length, idx, arg, obj );
}

template< class E, typename PtrT, typename Arg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ObjData_set_all_field_values_for_addr)( typename
    SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits< E >::address_t
        const field_addr,
    SIXTRL_CXX_NAMESPACE::arch_size_t const length,
    SIXTRL_CXX_NAMESPACE::arch_size_t const idx,
    Arg arg, SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT obj =
        SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ObjData_set_all_field_values_for_addr(
        field_addr, length, idx, arg, obj );
}

template< class E, typename PtrT, typename Iter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ObjData_set_field_values_from_range_for_addr)(
    typename SIXTRL_CXX_NAMESPACE::ObjDataAddrPointerFieldTraits<
        E >::address_t const field_addr,
    SIXTRL_CXX_NAMESPACE::arch_size_t const length,
    Iter in_begin, SIXTRL_ARGPTR_DEC const E *const SIXTRL_RESTRICT obj =
        SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ObjData_set_field_values_from_range_for_addr(
        field_addr, length, in_begin, obj );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_address_t)
NS(ObjData_default_field_addr)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ObjData_set_field_addr)(
    SIXTRL_ARGPTR_DEC NS(arch_address_t)* SIXTRL_RESTRICT ptr_dest_field_addr,
    NS(arch_address_t) const new_addr_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ObjData_set_default_field_addr)(
    SIXTRL_ARGPTR_DEC NS(arch_address_t)* SIXTRL_RESTRICT ptr_dest_field_addr
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_address_t) NS(ObjData_field_begin_addr)(
    NS(arch_address_t) const field_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_address_t) NS(ObjData_field_end_addr)(
    NS(arch_address_t) const field_addr, NS(arch_size_t) const num_elements,
    NS(arch_size_t) const elem_size ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(arch_address_t)
NS(ObjData_default_field_addr)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(arch_address_t) )0;
}

SIXTRL_INLINE NS(arch_status_t) NS(ObjData_set_field_addr)(
    SIXTRL_ARGPTR_DEC NS(arch_address_t)* SIXTRL_RESTRICT ptr_dest_field_addr,
    NS(arch_address_t) const new_addr_value ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( ptr_dest_field_addr != SIXTRL_NULLPTR );
    *ptr_dest_field_addr = new_addr_value;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(ObjData_set_default_field_addr)(
    SIXTRL_ARGPTR_DEC NS(arch_address_t)* SIXTRL_RESTRICT ptr_dest_field_addr
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( ptr_dest_field_addr != SIXTRL_NULLPTR );
    *ptr_dest_field_addr = NS(ObjData_default_field_addr)();
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_address_t) NS(ObjData_field_begin_addr)(
    NS(arch_address_t) const field_addr ) SIXTRL_NOEXCEPT
{
    return field_addr;
}

SIXTRL_INLINE NS(arch_address_t) NS(ObjData_field_end_addr)(
    NS(arch_address_t) const field_addr, NS(arch_size_t) const num_elements,
    NS(arch_size_t) const elem_size ) SIXTRL_NOEXCEPT
{
    return ( field_addr != ( NS(arch_address_t) )0 )
        ? field_addr + num_elements * elem_size
        : field_addr;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_ADDR_BASED_POINTER_FIELD_H__ */
