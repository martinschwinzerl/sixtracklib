#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_DATA_COBJECTS_API_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_DATA_COBJECTS_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/cavity.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_init.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjTypeIdDataTypeMap<
        cobj_type_id_t, SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_CAVITY >
    {
        typedef ::NS(Cavity) value_type;
    };

    template<> struct ObjDataTypeIdTraits< ::NS(Cavity), cobj_type_id_t >
    {
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type<
            ::NS(Cavity) >(), "NS(Cavity) should be a C-API type" );

        static SIXTRL_FN constexpr cobj_type_id_t TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_CAVITY;
        }
    };

    /* --------------------------------------------------------------------- */
    template< class CavityT >
    SIXTRL_STATIC SIXTRL_FN constexpr cobj_type_id_t Cavity_type_id(
        SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        return ObjDataTypeIdTraits< CavityT,
            SIXTRL_CXX_NAMESPACE::cobj_type_id_t >::TypeId();
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
        cobj_size_t >::type
    Cavity_num_pointers( SIXTRL_BE_ARGPTR_DEC const CavityT *const
        SIXTRL_RESTRICT /* p  */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< CavityT >();
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cobj_size_t
    Cavity_required_num_bytes( cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT
            p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_bytes< CavityT >(
            slot_size, p );
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cobj_size_t
    Cavity_required_num_slots( cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT
            p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_slots< CavityT >(
            slot_size, p );
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT const*
    Cavity_const_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
            ::NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index<
            CavityT >( index_obj, slot_size );
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT*
    Cavity_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index<
            CavityT >( index_obj, slot_size );
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BE_ARGPTR_DEC CavityT const* Cavity_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        return SIXTRL_CXX_NAMESPACE::Cavity_const_from_cobj_index< CavityT >(
            ::NS(CObjFlatBuffer_const_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT*
    Cavity_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        return SIXTRL_CXX_NAMESPACE::Cavity_from_cobj_index< CavityT >(
            ::NS(CObjFlatBuffer_index)( buffer, pos_in_buffer, slot_size ),
                slot_size );
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC
        CavityT const*
    Cavity_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? SIXTRL_CXX_NAMESPACE::Cavity_const_from_cobj_index< CavityT >(
                cbuffer->index_at( pos_in_buffer ), cbuffer->slot_size() )
            : SIXTRL_NULLPTR;
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT*
    Cavity_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? SIXTRL_CXX_NAMESPACE::Cavity_from_cobj_index< CavityT >(
                cbuffer->index_at( pos_in_buffer ), cbuffer->slot_size() )
            : SIXTRL_NULLPTR;
    }

    #if !defined( _GPUCODE )

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN bool Cavity_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const CavityT *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_buffer_size = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_num_slots = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_num_objects = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_num_pointers = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        return ( ( cbuffer != SIXTRL_NULLPTR ) &&
                 ( cbuffer->can_add_copy_of_object( ptr_orig,
                    ptr_requ_buffer_size, ptr_requ_num_slots,
                    ptr_requ_num_objects, ptr_requ_num_pointers ) ) );
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
    SIXTRL_BE_ARGPTR_DEC CavityT* Cavity_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const CavityT *const ptr_orig )
    {
        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? SIXTRL_CXX_NAMESPACE::CBufferView_add_copy_of_object_detail(
                *cbuffer, ptr_orig, nullptr, nullptr, nullptr, nullptr, false )
            : SIXTRL_NULLPTR;
    }

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
    SIXTRL_BE_ARGPTR_DEC CavityT*
    Cavity_new(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_BE_ARGPTR_DEC CavityT* added_obj = SIXTRL_NULLPTR;

        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        if( cbuffer != SIXTRL_NULLPTR )
        {
            SIXTRL_ARGPTR_DEC CavityT orig;
            st::Cavity_init( &orig );
            added_obj = st::Cavity_add_copy( cbuffer, &orig );
        }

        return added_obj;
    }

    template< class CavityT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT*
    Cavity_add(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        Args&&... args,
        SIXTRL_BE_ARGPTR_DEC const CavityT *const
            SIXTRL_RESTRICT /* p */ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_BE_ARGPTR_DEC CavityT* added_obj = SIXTRL_NULLPTR;

        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
            "Requires CavityT to be a Cavity element" );

        if( cbuffer != SIXTRL_NULLPTR )
        {
            SIXTRL_ARGPTR_DEC CavityT orig;
            st::Cavity_init( &orig, std::forward< Args >( args )... );
            added_obj = st::Cavity_add_copy( cbuffer, &orig );
        }

        return added_obj;
    }

    #endif /* !defined( _GPUCODE ) */
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_FN constexpr SIXTRL_CXX_NAMESPACE::cobj_type_id_t
NS(Cavity_type_id)( SIXTRL_BE_ARGPTR_DEC const CavityT *const
    SIXTRL_RESTRICT p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Cavity_type_id< CavityT >( p );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_FN constexpr SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(Cavity_num_pointers)( SIXTRL_BE_ARGPTR_DEC const CavityT *const
    SIXTRL_RESTRICT p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Cavity_num_pointers< CavityT >( p );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(Cavity_required_num_bytes)(
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
    SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Cavity_required_num_bytes< CavityT >(
        slot_size, p );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(Cavity_required_num_slots)(
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
    SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Cavity_required_num_slots< CavityT >(
        slot_size, p );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT const*
NS(Cavity_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Cavity_const_from_cobj_index<
        CavityT >( index_obj, slot_size );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT*
NS(Cavity_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Cavity_from_cobj_index<
        CavityT >( index_obj, slot_size );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_BE_ARGPTR_DEC CavityT const* NS(Cavity_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Cavity_const_from_flat_cbuffer< CavityT >(
        buffer, pos_in_buffer, slot_size );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT*
NS(Cavity_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Cavity_from_flat_cbuffer< CavityT >(
        buffer, pos_in_buffer, slot_size );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_BE_ARGPTR_DEC CavityT const*
NS(Cavity_const_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Cavity_const_from_cbuffer< CavityT >(
        cbuffer, pos_in_buffer );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT*
NS(Cavity_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Cavity_from_cbuffer< CavityT >(
        cbuffer, pos_in_buffer );
}

#if !defined( _GPUCODE )

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN bool NS(Cavity_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_BE_ARGPTR_DEC const CavityT *const ptr_orig,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_buffer_size = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_slots = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_objects = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_pointers = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Cavity_can_add_copy( cbuffer, ptr_orig,
        ptr_requ_buffer_size, ptr_requ_num_slots, ptr_requ_num_objects,
            ptr_requ_num_pointers );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
SIXTRL_BE_ARGPTR_DEC CavityT* NS(Cavity_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_BE_ARGPTR_DEC const CavityT *const ptr_orig )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_add_copy< CavityT >(
        cbuffer, ptr_orig );
}

template< class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC CavityT*
NS(Cavity_new)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT cbuffer )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_new< CavityT >( cbuffer );
}

template< class CavityT, typename... Args >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC CavityT*
NS(Cavity_add)( SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer, Args&&... args,
    SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_add< CavityT, Args... >(
        cbuffer, std::forward< Args >( args )..., p );
}

#endif /* !defined( _GPUCODE ) */
#endif /* __cplusplus */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(cobj_type_id_t)
NS(Cavity_type_id)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Cavity) const*
NS(Cavity_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Cavity)*
NS(Cavity_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Cavity) const*
NS(Cavity_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Cavity)*
NS(Cavity_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_type_id_t)
NS(Cavity_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Cavity_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const ptr_orig,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_pointers
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Cavity)*
NS(Cavity_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const ptr_orig );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Cavity)*
NS(Cavity_new)( SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)*
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

SIXTRL_INLINE NS(cobj_type_id_t) NS(Cavity_type_id)( void ) SIXTRL_NOEXCEPT
{
    return NS(OBJECT_TYPE_CAVITY);
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Cavity) const*
NS(Cavity_const_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
        NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(Cavity) const* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(Cavity_type_id)(), sizeof( NS(Cavity) ),
                slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Cavity)*
NS(Cavity_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(Cavity)* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(Cavity_type_id)(), sizeof( NS(Cavity) ),
                slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Cavity) const*
NS(Cavity_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(Cavity_const_from_cobj_index)( NS(CObjFlatBuffer_const_index)(
        buffer, pos_in_buffer, slot_size ), slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Cavity)*
NS(Cavity_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(Cavity_from_cobj_index)( NS(CObjFlatBuffer_index)(
        buffer, pos_in_buffer, slot_size ), slot_size );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_DATA_COBJECTS_API_H__ */