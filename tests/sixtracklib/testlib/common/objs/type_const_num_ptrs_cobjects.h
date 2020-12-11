#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_COBJECTS_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_COBJECTS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/objs_traits.hpp"
    #include "sixtracklib/testlib/common/objs/objs_initialiser_base.hpp"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs.hpp"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_api.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_init.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_convert.h"
    #include "sixtracklib/testlib/common/cobjects/cobj_elem_traits.hpp"
    #include "sixtracklib/testlib/common/cobjects/cobjects_initialiser_base.hpp"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/element_traits.hpp"
    #include "sixtracklib/common/cobjects/field_offsets.hpp"
    #include "sixtracklib/common/cobjects/field_sizes.hpp"
    #include "sixtracklib/common/cobjects/field_counts.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        static constexpr SIXTRL_CXX_NAMESPACE::cobj_type_id_t
            OBJECT_TYPE_TEST_COBJ_CONST_NUM_PTRS =
                SIXTRL_CXX_NAMESPACE::cobj_type_id_t{ 10001 };

    } /* namespace: tests */

    /* --------------------------------------------------------------------- */

    template<> struct ObjTypeIdDataTypeMap< cobj_type_id_t,
        SIXTRL_CXX_NAMESPACE::tests::OBJECT_TYPE_TEST_COBJ_CONST_NUM_PTRS >
    {
        typedef ::NS(TypeConstNumPtrs) value_type;
    };

    template<> struct ObjDataTypeIdTraits<
        ::NS(TypeConstNumPtrs), cobj_type_id_t >
    {
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type<
                ::NS(TypeConstNumPtrs) >(),
            "NS(TypeConstNumPtrs) should be a C-API type" );

        static SIXTRL_FN constexpr cobj_type_id_t TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::tests::OBJECT_TYPE_TEST_COBJ_CONST_NUM_PTRS;
        }
    };

    template<> struct CObjElemNumPointers< ::NS(TypeConstNumPtrs) >
    {
        static constexpr cobj_size_t min_num_ptrs = cobj_size_t{ 2 };
        static constexpr cobj_size_t max_num_ptrs = cobj_size_t{ 2 };
    };

    template<> struct CObjElemFieldOffsets< ::NS(TypeConstNumPtrs) >
    {
        static constexpr cobj_size_t offsets[ 2 ] =
        {
            offsetof( ::NS(TypeConstNumPtrs), b_addr ),
            offsetof( ::NS(TypeConstNumPtrs), c_addr )
        };
    };

    template<> struct CObjElemFieldSizes< ::NS(TypeConstNumPtrs) >
    {
        typedef typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
            ::NS(TypeConstNumPtrs) >::real_t real_t;

        static constexpr cobj_size_t sizes[ 2 ] =
        {
            sizeof( real_t ), sizeof( real_t )
        };
    };

    template<> struct CObjElemFieldCounts< ::NS(TypeConstNumPtrs), void >
    {
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cobj_status_t init_field_counts(
            SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT counts_begin,
            cobj_size_t const max_num_counts,
            SIXTRL_BUFFER_ARGPTR_DEC const ::NS(TypeConstNumPtrs) *const obj )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::cobj_status_t status = st::COBJECTS_STATUS_GENERAL_FAILURE;

            if( ( obj != SIXTRL_NULLPTR ) &&
                ( counts_begin != SIXTRL_NULLPTR ) &&
                ( max_num_counts >= st::CObjElem_num_ptrs<
                    ::NS(TypeConstNumPtrs) >() ) )
            {
                counts_begin[ 0 ] = st::tests::TypeConstNumPtrs_b_length( obj );
                counts_begin[ 1 ] = st::tests::TypeConstNumPtrs_c_length( obj );

                if( max_num_counts > cobj_size_t{ 2 } )
                {
                    std::fill( counts_begin + 2, counts_begin + max_num_counts,
                               cobj_size_t{ 0 } );
                }

                status = st::COBJECTS_STATUS_SUCCESS;
            }

            return status;
        }
    };

    /* --------------------------------------------------------------------- */

//     template< class R, arch_size_t RAlign >
//     struct CObjElemNumPointers<
//         SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs< R, RAlign > >
//     {
//         static constexpr cobj_size_t min_num_ptrs = cobj_size_t{ 2 };
//         static constexpr cobj_size_t max_num_ptrs = cobj_size_t{ 2 };
//     };

//     template< class R, arch_size_t RAlign >
//     struct CObjElemFieldOffsets<
//         SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs< R, RAlign > >
//     {
//         typedef SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs< R, RAlign >
//                 elem_t;
//
//         static constexpr cobj_size_t offsets[ 2 ] =
//         {
//             offsetof( elem_t, b_addr ), offsetof( elem_t, c_addr )
//         };
//     };
//
//     template< class R, arch_size_t RAlign >
//     struct CObjElemFieldSizes< SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs<
//         R, RAlign > >
//     {
//         typedef SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs<
//                 R, RAlign > elem_t;
//
//         typedef typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
//                 elem_t >::real_t real_t;
//
//         static constexpr cobj_size_t sizes[ 2 ] =
//         {
//             sizeof( real_t ), sizeof( real_t )
//         };
//     };
//
//     template< class R, arch_size_t RAlign >
//     struct CObjElemFieldCounts< SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs<
//         R, RAlign >, void >
//     {
//         typedef SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs< R, RAlign >
//                 elem_t;
//
//         SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cobj_status_t init_field_counts(
//             SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT counts_begin,
//             cobj_size_t const max_num_counts, const elem_t *const obj )
//         {
//             namespace st = SIXTRL_CXX_NAMESPACE;
//             st::cobj_status_t status = st::COBJECTS_STATUS_GENERAL_FAILURE;
//
//             if( ( obj != SIXTRL_NULLPTR ) &&
//                 ( counts_begin != SIXTRL_NULLPTR ) &&
//                 ( max_num_counts >= st::CObjElem_num_ptrs< elem_t >() ) )
//             {
//                 counts_begin[ 0 ] = st::tests::TypeConstNumPtrs_b_length( obj );
//                 counts_begin[ 1 ] = st::tests::TypeConstNumPtrs_c_length( obj );
//
//                 if( max_num_counts > cobj_size_t{ 2 } )
//                 {
//                     std::fill( counts_begin + 2, counts_begin + max_num_counts,
//                                cobj_size_t{ 0 } );
//                 }
//
//                 status = st::COBJECTS_STATUS_SUCCESS;
//             }
//
//             return status;
//         }
//     };

} /* namespace: SIXTRL_CXX_NAMESPACE */

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    template< class TypeT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::cobj_type_id_t >::type
    TypeConstNumPtrs_type_id(
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
            SIXTRL_CXX_NAMESPACE::cobj_type_id_t >();
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::cobj_type_id_t >::type
    TypeConstNumPtrs_type_id(
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataTypeIdTraits< TypeT,
            SIXTRL_CXX_NAMESPACE::cobj_type_id_t >::TypeId();
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::cobj_size_t >::type
    TypeConstNumPtrs_num_pointers( SIXTRL_BUFFER_DATAPTR_DEC  const TypeT
        *const SIXTRL_RESTRICT /* p  */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< TypeT >();
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
    TypeConstNumPtrs_required_num_bytes(
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeT *const SIXTRL_RESTRICT
            p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "Requires TypeT to be a type const-num-ptrs element" );
        return st::CObjElem_required_num_bytes< TypeT >( slot_size, p );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
    TypeConstNumPtrs_required_num_slots(
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeT *const SIXTRL_RESTRICT
            p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "Requires TypeT to be a type const-num-ptrs element" );
        return st::CObjElem_required_num_slots< TypeT >( slot_size, p );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BUFFER_DATAPTR_DEC  TypeT const*
    TypeConstNumPtrs_const_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
            ::NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "Requires TypeT to be a type const-num-ptrs element" );
        return st::CObjElem_const_from_cobj_index< TypeT >(
            index_obj, slot_size );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  TypeT*
    TypeConstNumPtrs_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "Requires TypeT to be a type const-num-ptrs element" );
        return st::CObjElem_from_cobj_index< TypeT >(
            index_obj, slot_size );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BUFFER_DATAPTR_DEC  TypeT const*
    TypeConstNumPtrs_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "Requires TypeT to be a type const-num-ptrs element" );

        return st::tests::TypeConstNumPtrs_const_from_cobj_index< TypeT >(
            ::NS(CObjFlatBuffer_const_index)( buffer, pos_in_buffer,
                slot_size ), slot_size );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BUFFER_DATAPTR_DEC  TypeT* TypeConstNumPtrs_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "Requires TypeT to be a type const-num-ptrs element" );
        return st::tests::TypeConstNumPtrs_from_cobj_index< TypeT >(
            ::NS(CObjFlatBuffer_index)( buffer, pos_in_buffer, slot_size ),
                slot_size );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BUFFER_DATAPTR_DEC TypeT const*
    TypeConstNumPtrs_const_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "Requires TypeT to be a type const-num-ptrs element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? st::tests::TypeConstNumPtrs_const_from_cobj_index< TypeT >(
                cbuffer->index_at( pos_in_buffer ), cbuffer->slot_size() )
            : SIXTRL_NULLPTR;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BUFFER_DATAPTR_DEC  TypeT* TypeConstNumPtrs_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "Requires TypeT to be a type const-num-ptrs element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? st::tests::TypeConstNumPtrs_from_cobj_index< TypeT >(
                cbuffer->index_at( pos_in_buffer ), cbuffer->slot_size() )
            : SIXTRL_NULLPTR;
    }

    #if !defined( _GPUCODE )

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN bool
    TypeConstNumPtrs_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeT *const ptr_orig,
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
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "Requires TypeT to be a type const-num-ptrs element" );

        return ( ( cbuffer != SIXTRL_NULLPTR ) &&
                 ( cbuffer->can_add_copy_of_object( ptr_orig,
                    ptr_requ_buffer_size, ptr_requ_num_slots,
                    ptr_requ_num_objects, ptr_requ_num_pointers ) ) );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
    SIXTRL_BUFFER_DATAPTR_DEC  TypeT* TypeConstNumPtrs_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BUFFER_DATAPTR_DEC  const TypeT *const ptr_orig )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        static_assert(
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "Requires TypeT to be a type const-num-ptrs element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? SIXTRL_CXX_NAMESPACE::CBufferView_add_copy_of_object_detail(
                *cbuffer, ptr_orig, nullptr, nullptr, nullptr, nullptr, false )
            : SIXTRL_NULLPTR;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC TypeT*
    TypeConstNumPtrs_new(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_b_values,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_c_values,
        SIXTRL_BUFFER_ARGPTR_DEC const TypeT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* added_obj = SIXTRL_NULLPTR;

        static_assert(
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "Requires TypeT to be a type const-num-ptrs element" );

        if( cbuffer != SIXTRL_NULLPTR )
        {
            SIXTRL_BUFFER_ARGPTR_DEC TypeT orig;

            if( st::ARCH_STATUS_SUCCESS == st::CObjElem_init(
                    &orig, num_b_values, num_c_values ) )
            {
                added_obj = st::tests::TypeConstNumPtrs_add_copy(
                    cbuffer, &orig );
            }
        }

        return added_obj;
    }

    template< class TypeT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC TypeT*
    TypeConstNumPtrs_add(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        Args&&... args,
        SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_BUFFER_DATAPTR_DEC  TypeT* added_obj = SIXTRL_NULLPTR;

        static_assert(
            st::tests::TypeConstNumPtrs_is_type< TypeT >(),
            "Requires TypeT to be a type const-num-ptrs element" );

        if( cbuffer != SIXTRL_NULLPTR )
        {
            SIXTRL_BUFFER_ARGPTR_DEC TypeT orig;

            if( st::ARCH_STATUS_SUCCESS == st::CObjElem_init(
                    &orig, std::forward< Args >( args )... ) )
            {
                added_obj = st::tests::TypeConstNumPtrs_add_copy(
                    cbuffer, &orig );
            }
        }

        return added_obj;
    }

    /* --------------------------------------------------------------------- */

    template< class TypeConstNumPtrsT >
    struct CObjElemInitialiserTraits< TypeConstNumPtrsT,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
                TypeConstNumPtrsT >() &&
            SIXTRL_CXX_NAMESPACE::CObjElem_type_id< TypeConstNumPtrsT >() !=
                SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
                    SIXTRL_CXX_NAMESPACE::cobj_type_id_t >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsInitialiser<
            TypeConstNumPtrsT > initialiser_t;
    };

    #endif /* !defined( _GPUCODE ) */

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

template< class TypeT >
SIXTRL_STATIC SIXTRL_FN constexpr SIXTRL_CXX_NAMESPACE::cobj_type_id_t
NS(TypeConstNumPtrs_type_id)( SIXTRL_BUFFER_DATAPTR_DEC  const TypeT *const
    SIXTRL_RESTRICT p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_type_id< TypeT >( p );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_FN constexpr SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(TypeConstNumPtrs_num_pointers)( SIXTRL_BUFFER_DATAPTR_DEC  const TypeT
    *const SIXTRL_RESTRICT p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_num_pointers<
        TypeT >( p );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(TypeConstNumPtrs_required_num_bytes)(
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
    SIXTRL_BUFFER_DATAPTR_DEC  const TypeT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_required_num_bytes<
        TypeT >( slot_size, p );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(TypeConstNumPtrs_required_num_slots)(
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
    SIXTRL_BUFFER_DATAPTR_DEC  const TypeT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_required_num_slots<
        TypeT >( slot_size, p );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_BUFFER_DATAPTR_DEC  TypeT const*
NS(TypeConstNumPtrs_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_const_from_cobj_index<
        TypeT >( index_obj, slot_size );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  TypeT*
NS(TypeConstNumPtrs_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_from_cobj_index<
        TypeT >( index_obj, slot_size );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_BUFFER_DATAPTR_DEC TypeT const*
NS(TypeConstNumPtrs_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_const_from_flat_cbuffer<
        TypeT >( buffer, pos_in_buffer, slot_size );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC TypeT*
NS(TypeConstNumPtrs_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_from_flat_cbuffer<
        TypeT >( buffer, pos_in_buffer, slot_size );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_BUFFER_DATAPTR_DEC TypeT const* NS(TypeConstNumPtrs_const_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_const_from_cbuffer<
        TypeT >( cbuffer, pos_in_buffer );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC TypeT*
NS(TypeConstNumPtrs_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_from_cbuffer<
        TypeT >( cbuffer, pos_in_buffer );
}

#if !defined( _GPUCODE )

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN bool
NS(TypeConstNumPtrs_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_BUFFER_DATAPTR_DEC  const TypeT *const ptr_orig,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_buffer_size = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_slots = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_objects = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_pointers = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_can_add_copy( cbuffer,
        ptr_orig, ptr_requ_buffer_size, ptr_requ_num_slots,
            ptr_requ_num_objects, ptr_requ_num_pointers );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
SIXTRL_BUFFER_DATAPTR_DEC TypeT* NS(TypeConstNumPtrs_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_BUFFER_DATAPTR_DEC  const TypeT *const ptr_orig )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_add_copy<
        TypeT >( cbuffer, ptr_orig );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
SIXTRL_BUFFER_DATAPTR_DEC TypeT*
NS(TypeConstNumPtrs_new)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT cbuffer,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_b_values,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_c_values )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_new< TypeT >(
        cbuffer, num_b_values, num_c_values );
}

template< class TypeT, typename... Args >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC TypeT*
NS(TypeConstNumPtrs_add)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    Args&&... args,
    SIXTRL_BUFFER_DATAPTR_DEC const TypeT *const
        SIXTRL_RESTRICT p = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_add< TypeT, Args... >(
        cbuffer, std::forward< Args >( args )..., p );
}

#endif /* !defined( _GPUCODE ) */
#endif /* __cplusplus */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(cobj_type_id_t)
NS(TypeConstNumPtrs_type_id)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeConstNumPtrs) const*
NS(TypeConstNumPtrs_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeConstNumPtrs)*
NS(TypeConstNumPtrs_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeConstNumPtrs) const*
NS(TypeConstNumPtrs_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeConstNumPtrs)*
NS(TypeConstNumPtrs_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_type_id_t)
NS(TypeConstNumPtrs_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TypeConstNumPtrs_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_BUFFER_DATAPTR_DEC  const NS(TypeConstNumPtrs) *const ptr_orig,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_pointers
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeConstNumPtrs)*
NS(TypeConstNumPtrs_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
    SIXTRL_BUFFER_DATAPTR_DEC  const NS(TypeConstNumPtrs) *const ptr_orig );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeConstNumPtrs)*
NS(TypeConstNumPtrs_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
    NS(test_objs_size_t) const num_b_values,
    NS(test_objs_size_t) const num_c_values );

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

SIXTRL_INLINE NS(cobj_type_id_t)
NS(TypeConstNumPtrs_type_id)( void ) SIXTRL_NOEXCEPT
{
    return NS(OBJECT_TYPE_DRIFT);
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeConstNumPtrs) const*
NS(TypeConstNumPtrs_const_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
        NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeConstNumPtrs) const* )(
        uintptr_t )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(TypeConstNumPtrs_type_id)(),
                sizeof( NS(TypeConstNumPtrs) ), slot_size );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeConstNumPtrs)*
NS(TypeConstNumPtrs_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeConstNumPtrs)* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(TypeConstNumPtrs_type_id)(),
                sizeof( NS(TypeConstNumPtrs) ), slot_size );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeConstNumPtrs) const*
NS(TypeConstNumPtrs_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(TypeConstNumPtrs_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, pos_in_buffer, slot_size ),
            slot_size );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC  NS(TypeConstNumPtrs)*
NS(TypeConstNumPtrs_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(TypeConstNumPtrs_from_cobj_index)( NS(CObjFlatBuffer_index)(
        buffer, pos_in_buffer, slot_size ), slot_size );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_COBJECTS_H__ */
