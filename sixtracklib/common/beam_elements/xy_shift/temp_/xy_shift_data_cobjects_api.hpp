#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_DATA_COBJECTS_API_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_DATA_COBJECTS_API_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_data.hpp"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_data_api.hpp"
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
    SIXTRL_STATIC SIXTRL_FN cobj_type_id_t XYShift_type_id() SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN cobj_type_id_t XYShift_num_pointers(
        SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const
            SIXTRL_RESTRICT elem = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN cobj_type_id_t XYShift_required_num_bytes(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const
            SIXTRL_RESTRICT elem = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN cobj_size_t XYShift_required_num_slots(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const
            SIXTRL_RESTRICT elem = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > const*
    XYShift_const_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > const*
    XYShift_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > const*
    XYShift_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN bool XYShift_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_buffer_size = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_slots = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_objects = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_pointers = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_add_copy( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const
            ptr_orig );

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_new( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer );

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(), typename... Args >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_add( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer, Args&&... args );
}

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
SIXTRL_STATIC SIXTRL_FN ::NS(cobj_type_id_t) NS(XYShift_type_id)( void ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_STATIC SIXTRL_FN ::NS(cobj_type_id_t) NS(XYShift_num_pointers)(
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign >
        *const SIXTRL_RESTRICT elem = nullptr ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_STATIC SIXTRL_FN ::NS(cobj_type_id_t) NS(XYShift_required_num_bytes)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign >
        *const SIXTRL_RESTRICT elem = nullptr ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_STATIC SIXTRL_FN ::NS(cobj_size_t) NS(XYShift_required_num_slots)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign >
        *const SIXTRL_RESTRICT elem = nullptr ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::XYShiftData<
    R, RAlign > const*
NS(XYShift_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::XYShiftData<
    R, RAlign >*
NS(XYShift_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::XYShiftData<
    R, RAlign > const*
NS(XYShift_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::XYShiftData<
    R, RAlign >*
NS(XYShift_from_flat_cbuffer)(
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
    SIXTRL_INLINE cobj_type_id_t XYShift_type_id() SIXTRL_NOEXCEPT
    {
        return ObjDataTypeIdTraits<
            XYShiftData< R, RAlign >, cobj_type_id_t >::TypeId();
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN cobj_type_id_t XYShift_num_pointers(
        SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const
            SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs<
            XYShiftData< R, RAlign > >( elem );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE cobj_type_id_t XYShift_required_num_bytes(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const
            SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_bytes<
            XYShiftData< R, RAlign > >( slot_size, elem );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE cobj_size_t XYShift_required_num_slots(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const
            SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_slots<
            XYShiftData< R, RAlign > >( slot_size, elem );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > const*
    XYShift_const_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index<
            XYShiftData< R, RAlign > >( index_obj, slot_size );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > const*
    XYShift_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index<
            XYShiftData< R, RAlign > >( index_obj, slot_size );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > const*
    XYShift_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index<
            XYShiftData< R, RAlign > >( ::NS(CObjFlatBuffer_const_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index< XYShiftData<
            R, RAlign > >( ::NS(CObjFlatBuffer_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );
    }

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > const*
    XYShift_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return cbuffer->get_const_object<
            XYShiftData< R, RAlign > >( pos_in_buffer );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return cbuffer->get_object< XYShiftData< R, RAlign > >( pos_in_buffer );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE bool XYShift_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const ptr_orig,
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
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const ptr_orig )
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return SIXTRL_CXX_NAMESPACE::CBufferView_add_copy_of_object_detail(
            *cbuffer, ptr_orig, nullptr, nullptr, nullptr, nullptr, false );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_new( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer )
    {
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > temp;
        SIXTRL_CXX_NAMESPACE::XYShift_init< XYShiftData< R, RAlign > >(
            std::addressof( temp ) );

        return SIXTRL_CXX_NAMESPACE::XYShift_add_copy(
            cbuffer, std::addressof( temp ) );
    }

    template< class R, arch_size_t RAlign, typename... Args >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_add( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer, Args&&... args )
    {
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > temp;
        SIXTRL_CXX_NAMESPACE::XYShift_init< XYShiftData< R, RAlign > >(
            std::addressof( temp ), std::forward< Args >( args )... );

        return SIXTRL_CXX_NAMESPACE::XYShift_add_copy< XYShiftData< R, RAlign > >(
            cbuffer, std::addressof( temp ) );
    }
}

/* Provide accessor functions in the C namespace to
 * allow writing portable kernels */

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE ::NS(cobj_type_id_t) NS(XYShift_type_id)( void ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_type_id<
        SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign > >();
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE ::NS(cobj_type_id_t) NS(XYShift_num_pointers)(
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign >
        *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_num_pointers<
        SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign > >( elem );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE ::NS(cobj_type_id_t) NS(XYShift_required_num_bytes)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign >
        *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_required_num_bytes<
        SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign > >( slot_size, elem );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE ::NS(cobj_size_t) NS(XYShift_required_num_slots)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign >
        *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_required_num_slots<
        SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign > >( slot_size, elem );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::XYShiftData<
    R, RAlign > const*
NS(XYShift_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_const_from_cobj_index<
        SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign > >( index_obj, slot_size );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign >*
NS(XYShift_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_from_cobj_index<
        SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign > >( index_obj, slot_size );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::XYShiftData<
    R, RAlign > const*
NS(XYShift_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_const_from_flat_cbuffer<
        SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign > >(
            buffer, pos_in_buffer, slot_size );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign >*
XYShift_from_flat_cbuffer(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_from_flat_cbuffer<
        SIXTRL_CXX_NAMESPACE::XYShiftData< R, RAlign > >(
            buffer, pos_in_buffer, slot_size );
}

#endif /* !defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_DATA_API_CXX_HPP__ */
