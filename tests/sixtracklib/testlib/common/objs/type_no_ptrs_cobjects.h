#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_COBJECTS_API_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_COBJECTS_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/objs_traits.hpp"
    #include "sixtracklib/testlib/common/objs/objs_initialiser_base.hpp"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_api.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_init.h"
    #include "sixtracklib/testlib/common/cobjects/cobj_elem_traits.hpp"
    #include "sixtracklib/testlib/common/cobjects/cobjects_initialiser_base.hpp"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        static constexpr SIXTRL_CXX_NAMESPACE::cobj_type_id_t
            OBJECT_TYPE_TEST_COBJ_NO_PTRS =
                SIXTRL_CXX_NAMESPACE::cobj_type_id_t{ 10000 };

    } /* namespace: tests */

    template<> struct ObjTypeIdDataTypeMap< cobj_type_id_t,
        SIXTRL_CXX_NAMESPACE::tests::OBJECT_TYPE_TEST_COBJ_NO_PTRS >
    {
        typedef ::NS(TypeNoPtrs) value_type;
    };

    template<> struct ObjDataTypeIdTraits< ::NS(TypeNoPtrs), cobj_type_id_t >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type< ::NS(TypeNoPtrs) >(),
            "NS(TypeNoPtrs) should be a C-API type" );

        static SIXTRL_FN constexpr cobj_type_id_t TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::tests::OBJECT_TYPE_TEST_COBJ_NO_PTRS;
        }
    };

    /* --------------------------------------------------------------------- */

namespace tests
{
    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::cobj_type_id_t >::type
    TypeNoPtrs_type_id(
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
            SIXTRL_CXX_NAMESPACE::cobj_type_id_t >();
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::cobj_type_id_t >::type
    TypeNoPtrs_type_id(
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataTypeIdTraits< TypeNoPtrsT,
            SIXTRL_CXX_NAMESPACE::cobj_type_id_t >::TypeId();
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
            TypeNoPtrsT >(), SIXTRL_CXX_NAMESPACE::cobj_size_t >::type
    TypeNoPtrs_num_pointers( SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const
        SIXTRL_RESTRICT /* p  */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< TypeNoPtrsT >();
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
    TypeNoPtrs_required_num_bytes(
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const SIXTRL_RESTRICT
            p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "Requires TypeNoPtrsT to be a TypeNoPtrs element" );
        return st::CObjElem_required_num_bytes< TypeNoPtrsT >( slot_size, p );
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
    TypeNoPtrs_required_num_slots(
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const SIXTRL_RESTRICT
            p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "Requires TypeNoPtrsT to be a TypeNoPtrs element" );
        return st::CObjElem_required_num_slots< TypeNoPtrsT >( slot_size, p );
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  TypeNoPtrsT const*
    TypeNoPtrs_const_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
            ::NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "Requires TypeNoPtrsT to be a TypeNoPtrs element" );
        return st::CObjElem_const_from_cobj_index< TypeNoPtrsT >(
            index_obj, slot_size );
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  TypeNoPtrsT*
    TypeNoPtrs_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "Requires TypeNoPtrsT to be a TypeNoPtrs element" );
        return st::CObjElem_from_cobj_index< TypeNoPtrsT >(
            index_obj, slot_size );
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BUFFER_DATAPTR_DEC  TypeNoPtrsT const*
    TypeNoPtrs_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "Requires TypeNoPtrsT to be a TypeNoPtrs element" );

        return st::tests::TypeNoPtrs_const_from_cobj_index< TypeNoPtrsT >(
            ::NS(CObjFlatBuffer_const_index)( buffer, pos_in_buffer,
                slot_size ), slot_size );
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BUFFER_DATAPTR_DEC  TypeNoPtrsT* TypeNoPtrs_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "Requires TypeNoPtrsT to be a TypeNoPtrs element" );
        return st::tests::TypeNoPtrs_from_cobj_index< TypeNoPtrsT >(
            ::NS(CObjFlatBuffer_index)( buffer, pos_in_buffer, slot_size ),
                slot_size );
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT const*
    TypeNoPtrs_const_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "Requires TypeNoPtrsT to be a TypeNoPtrs element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? st::tests::TypeNoPtrs_const_from_cobj_index< TypeNoPtrsT >(
                cbuffer->index_at( pos_in_buffer ), cbuffer->slot_size() )
            : SIXTRL_NULLPTR;
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BUFFER_DATAPTR_DEC  TypeNoPtrsT* TypeNoPtrs_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "Requires TypeNoPtrsT to be a TypeNoPtrs element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? st::tests::TypeNoPtrs_from_cobj_index< TypeNoPtrsT >(
                cbuffer->index_at( pos_in_buffer ), cbuffer->slot_size() )
            : SIXTRL_NULLPTR;
    }

    #if !defined( _GPUCODE )

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN bool TypeNoPtrs_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_buffer_size = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_num_slots = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_num_objects = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_num_pointers = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "Requires TypeNoPtrsT to be a TypeNoPtrs element" );

        return ( ( cbuffer != SIXTRL_NULLPTR ) &&
                 ( cbuffer->can_add_copy_of_object( ptr_orig,
                    ptr_requ_buffer_size, ptr_requ_num_slots,
                    ptr_requ_num_objects, ptr_requ_num_pointers ) ) );
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
    SIXTRL_BUFFER_DATAPTR_DEC  TypeNoPtrsT* TypeNoPtrs_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const ptr_orig )
    {
        static_assert( SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "Requires TypeNoPtrsT to be a TypeNoPtrs element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? SIXTRL_CXX_NAMESPACE::CBufferView_add_copy_of_object_detail(
                *cbuffer, ptr_orig, nullptr, nullptr, nullptr, nullptr, false )
            : SIXTRL_NULLPTR;
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
    SIXTRL_BUFFER_DATAPTR_DEC  TypeNoPtrsT*
    TypeNoPtrs_new(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_BUFFER_DATAPTR_DEC  TypeNoPtrsT* added_obj = SIXTRL_NULLPTR;

        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "Requires TypeNoPtrsT to be a TypeNoPtrs element" );

        if( cbuffer != SIXTRL_NULLPTR )
        {
            SIXTRL_BUFFER_ARGPTR_DEC TypeNoPtrsT orig;

            if( st::ARCH_STATUS_SUCCESS == st::CObjElem_init<
                    TypeNoPtrsT >( &orig ) )
            {
                added_obj = st::tests::TypeNoPtrs_add_copy( cbuffer, &orig );
            }
        }

        return added_obj;
    }

    template< class TypeNoPtrsT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
    TypeNoPtrs_add(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        Args&&... args,
        SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_BUFFER_DATAPTR_DEC  TypeNoPtrsT* added_obj = SIXTRL_NULLPTR;

        static_assert(
            st::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
            "Requires TypeNoPtrsT to be a TypeNoPtrs element" );

        if( cbuffer != SIXTRL_NULLPTR )
        {
            SIXTRL_BUFFER_ARGPTR_DEC TypeNoPtrsT orig;

            if( st::ARCH_STATUS_SUCCESS == st::CObjElem_init< TypeNoPtrsT
                    >( &orig, std::forward< Args >( args )... ) )
            {
                added_obj = st::tests::TypeNoPtrs_add_copy( cbuffer, &orig );
            }
        }

        return added_obj;
    }

    /* --------------------------------------------------------------------- */

    template< class TypeNoPtrsT >
    struct CObjElemInitialiserTraits< TypeNoPtrsT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeNoPtrsT >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_type_id< TypeNoPtrsT >() !=
            SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
                SIXTRL_CXX_NAMESPACE::cobj_type_id_t >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsInitialiser< TypeNoPtrsT >
                initialiser_t;
    };

    #endif /* !defined( _GPUCODE ) */

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_FN constexpr SIXTRL_CXX_NAMESPACE::cobj_type_id_t
NS(TypeNoPtrs_type_id)( SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const
    SIXTRL_RESTRICT p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_type_id< TypeNoPtrsT >( p );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_FN constexpr SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(TypeNoPtrs_num_pointers)( SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const
    SIXTRL_RESTRICT p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_num_pointers<
        TypeNoPtrsT >( p );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(TypeNoPtrs_required_num_bytes)(
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
    SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_required_num_bytes<
        TypeNoPtrsT >( slot_size, p );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(TypeNoPtrs_required_num_slots)(
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
    SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_required_num_slots<
        TypeNoPtrsT >( slot_size, p );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_BUFFER_DATAPTR_DEC  TypeNoPtrsT const*
NS(TypeNoPtrs_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_const_from_cobj_index<
        TypeNoPtrsT >( index_obj, slot_size );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  TypeNoPtrsT*
NS(TypeNoPtrs_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_from_cobj_index<
        TypeNoPtrsT >( index_obj, slot_size );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT const*
NS(TypeNoPtrs_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_const_from_flat_cbuffer<
        TypeNoPtrsT >( buffer, pos_in_buffer, slot_size );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
NS(TypeNoPtrs_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_from_flat_cbuffer<
        TypeNoPtrsT >( buffer, pos_in_buffer, slot_size );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT const* NS(TypeNoPtrs_const_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_const_from_cbuffer<
        TypeNoPtrsT >( cbuffer, pos_in_buffer );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
NS(TypeNoPtrs_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_from_cbuffer<
        TypeNoPtrsT >( cbuffer, pos_in_buffer );
}

#if !defined( _GPUCODE )

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN bool NS(TypeNoPtrs_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const ptr_orig,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_buffer_size = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_slots = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_objects = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_pointers = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeNoPtrs_can_add_copy( cbuffer, ptr_orig,
        ptr_requ_buffer_size, ptr_requ_num_slots, ptr_requ_num_objects,
            ptr_requ_num_pointers );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* NS(TypeNoPtrs_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_BUFFER_DATAPTR_DEC  const TypeNoPtrsT *const ptr_orig )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeNoPtrs_add_copy< TypeNoPtrsT >( cbuffer, ptr_orig );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
NS(TypeNoPtrs_new)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT cbuffer )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeNoPtrs_new< TypeNoPtrsT >( cbuffer );
}

template< class TypeNoPtrsT, typename... Args >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
NS(TypeNoPtrs_add)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    Args&&... args,
    SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT *const
        SIXTRL_RESTRICT p = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_add< TypeNoPtrsT, Args... >(
        cbuffer, std::forward< Args >( args )..., p );
}

#endif /* !defined( _GPUCODE ) */
#endif /* __cplusplus */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(cobj_type_id_t)
NS(TypeNoPtrs_type_id)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeNoPtrs) const*
NS(TypeNoPtrs_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeNoPtrs)*
NS(TypeNoPtrs_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeNoPtrs) const*
NS(TypeNoPtrs_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeNoPtrs)*
NS(TypeNoPtrs_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_type_id_t)
NS(TypeNoPtrs_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TypeNoPtrs_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_BUFFER_DATAPTR_DEC  const NS(TypeNoPtrs) *const ptr_orig,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_pointers
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeNoPtrs)*
NS(TypeNoPtrs_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
    SIXTRL_BUFFER_DATAPTR_DEC  const NS(TypeNoPtrs) *const ptr_orig );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeNoPtrs)*
NS(TypeNoPtrs_new)( SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)*
    SIXTRL_RESTRICT cbuffer );

#endif /* _GPUCODE */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(cobj_type_id_t) NS(TypeNoPtrs_type_id)( void ) SIXTRL_NOEXCEPT
{
    return NS(OBJECT_TYPE_DRIFT);
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeNoPtrs) const*
NS(TypeNoPtrs_const_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
        NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeNoPtrs) const* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(TypeNoPtrs_type_id)(), sizeof( NS(TypeNoPtrs) ),
                slot_size );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeNoPtrs)*
NS(TypeNoPtrs_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeNoPtrs)* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(TypeNoPtrs_type_id)(), sizeof( NS(TypeNoPtrs) ),
                slot_size );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeNoPtrs) const*
NS(TypeNoPtrs_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(TypeNoPtrs_const_from_cobj_index)( NS(CObjFlatBuffer_const_index)(
        buffer, pos_in_buffer, slot_size ), slot_size );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeNoPtrs)*
NS(TypeNoPtrs_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(TypeNoPtrs_from_cobj_index)( NS(CObjFlatBuffer_index)(
        buffer, pos_in_buffer, slot_size ), slot_size );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_COBJECTS_API_H__ */
