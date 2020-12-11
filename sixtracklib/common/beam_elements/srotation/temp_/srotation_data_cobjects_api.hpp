#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_DATA_COBJECTS_API_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_DATA_COBJECTS_API_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/srotation_data.hpp"
    #include "sixtracklib/common/beam_elements/srotation/srotation_data_api.hpp"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    static SIXTRL_FN cobj_type_id_t SRotation_type_id() SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    static SIXTRL_FN cobj_type_id_t SRotation_num_pointers(
        SIXTRL_BE_ARGPTR_DEC const SRotationData< R, RAlign > *const
            SIXTRL_RESTRICT elem = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    static SIXTRL_FN cobj_type_id_t SRotation_required_num_bytes(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const SRotationData< R, RAlign > *const
            SIXTRL_RESTRICT elem = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    static SIXTRL_FN cobj_size_t SRotation_required_num_slots(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const SRotationData< R, RAlign > *const
            SIXTRL_RESTRICT elem = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign > const*
    SRotation_const_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign >*
    SRotation_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign > const*
    SRotation_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign >*
    SRotation_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign > const*
    SRotation_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign >*
    SRotation_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    static SIXTRL_FN bool SRotation_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const SRotationData< R, RAlign > *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_buffer_size = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_slots = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_objects = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_pointers = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign >*
    SRotation_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const SRotationData< R, RAlign > *const
            ptr_orig );

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign >*
    SRotation_new( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer );

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(), typename... Args >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign >*
    SRotation_add( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer, Args&&... args );
}

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
static SIXTRL_FN ::NS(cobj_type_id_t) NS(SRotation_type_id)( void ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign >
static SIXTRL_FN ::NS(cobj_type_id_t) NS(SRotation_num_pointers)(
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign >
        *const SIXTRL_RESTRICT elem = nullptr ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign >
static SIXTRL_FN ::NS(cobj_type_id_t) NS(SRotation_required_num_bytes)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign >
        *const SIXTRL_RESTRICT elem = nullptr ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign >
static SIXTRL_FN ::NS(cobj_size_t) NS(SRotation_required_num_slots)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign >
        *const SIXTRL_RESTRICT elem = nullptr ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::SRotationData<
    R, RAlign > const*
NS(SRotation_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::SRotationData<
    R, RAlign >*
NS(SRotation_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::SRotationData<
    R, RAlign > const*
NS(SRotation_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::SRotationData<
    R, RAlign >*
NS(SRotation_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/element_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE cobj_type_id_t SRotation_type_id() SIXTRL_NOEXCEPT
    {
        return ObjDataTypeIdTraits<
            SRotationData< R, RAlign >, cobj_type_id_t >::TypeId();
    }

    template< class R, arch_size_t RAlign >
    static SIXTRL_FN cobj_type_id_t SRotation_num_pointers(
        SIXTRL_BE_ARGPTR_DEC const SRotationData< R, RAlign > *const
            SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs<
            SRotationData< R, RAlign > >( elem );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE cobj_type_id_t SRotation_required_num_bytes(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const SRotationData< R, RAlign > *const
            SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_bytes<
            SRotationData< R, RAlign > >( slot_size, elem );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE cobj_size_t SRotation_required_num_slots(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const SRotationData< R, RAlign > *const
            SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_slots<
            SRotationData< R, RAlign > >( slot_size, elem );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign > const*
    SRotation_const_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index<
            SRotationData< R, RAlign > >( index_obj, slot_size );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign > const*
    SRotation_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index<
            SRotationData< R, RAlign > >( index_obj, slot_size );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign > const*
    SRotation_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index<
            SRotationData< R, RAlign > >( ::NS(CObjFlatBuffer_const_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign >*
    SRotation_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index< SRotationData<
            R, RAlign > >( ::NS(CObjFlatBuffer_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );
    }

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign > const*
    SRotation_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return cbuffer->get_const_object<
            SRotationData< R, RAlign > >( pos_in_buffer );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign >*
    SRotation_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return cbuffer->get_object< SRotationData< R, RAlign > >( pos_in_buffer );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE bool SRotation_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const SRotationData< R, RAlign > *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_buffer_size ,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_objects,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_pointers
    ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return cbuffer->can_add_copy_of_object( ptr_orig, requ_buffer_size,
            requ_num_slots, requ_num_objects, requ_num_pointers );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign >*
    SRotation_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const SRotationData< R, RAlign > *const ptr_orig )
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return SIXTRL_CXX_NAMESPACE::CBufferView_add_copy_of_object_detail(
            *cbuffer, ptr_orig, nullptr, nullptr, nullptr, nullptr, false );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign >*
    SRotation_new( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer )
    {
        SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign > temp;
        SIXTRL_CXX_NAMESPACE::SRotation_init< SRotationData< R, RAlign > >(
            std::addressof( temp ) );

        return SIXTRL_CXX_NAMESPACE::SRotation_add_copy(
            cbuffer, std::addressof( temp ) );
    }

    template< class R, arch_size_t RAlign, typename... Args >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign >*
    SRotation_add( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer, Args&&... args )
    {
        SIXTRL_BE_ARGPTR_DEC SRotationData< R, RAlign > temp;
        SIXTRL_CXX_NAMESPACE::SRotation_init< SRotationData< R, RAlign > >(
            std::addressof( temp ), std::forward< Args >( args )... );

        return SIXTRL_CXX_NAMESPACE::SRotation_add_copy< SRotationData< R, RAlign > >(
            cbuffer, std::addressof( temp ) );
    }
}

/* Provide accessor functions in the C namespace to
 * allow writing portable kernels */

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE ::NS(cobj_type_id_t) NS(SRotation_type_id)( void ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_type_id<
        SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign > >();
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE ::NS(cobj_type_id_t) NS(SRotation_num_pointers)(
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign >
        *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_num_pointers<
        SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign > >( elem );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE ::NS(cobj_type_id_t) NS(SRotation_required_num_bytes)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign >
        *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_required_num_bytes<
        SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign > >( slot_size, elem );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE ::NS(cobj_size_t) NS(SRotation_required_num_slots)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign >
        *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_required_num_slots<
        SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign > >( slot_size, elem );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::SRotationData<
    R, RAlign > const*
NS(SRotation_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_const_from_cobj_index<
        SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign > >( index_obj, slot_size );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign >*
NS(SRotation_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_from_cobj_index<
        SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign > >( index_obj, slot_size );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::SRotationData<
    R, RAlign > const*
NS(SRotation_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_const_from_flat_cbuffer<
        SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign > >(
            buffer, pos_in_buffer, slot_size );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign >*
SRotation_from_flat_cbuffer(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_from_flat_cbuffer<
        SIXTRL_CXX_NAMESPACE::SRotationData< R, RAlign > >(
            buffer, pos_in_buffer, slot_size );
}

#endif /* !defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_DATA_API_CXX_HPP__ */
