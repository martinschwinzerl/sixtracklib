#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_BEAM_MONITOR_DATA_COBJECTS_API_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_BEAM_MONITOR_DATA_COBJECTS_API_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_data.hpp"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_data_api.hpp"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    static SIXTRL_FN cobj_type_id_t BeamMonitor_type_id() SIXTRL_NOEXCEPT;

    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    static SIXTRL_FN cobj_type_id_t BeamMonitor_num_pointers(
        SIXTRL_BE_ARGPTR_DEC const BeamMonitorData< R, I, IAlign > *const
            SIXTRL_RESTRICT ptr_beam_monitor = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    static SIXTRL_FN cobj_type_id_t BeamMonitor_required_num_bytes(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const BeamMonitorData< R, I, IAlign > *const
            SIXTRL_RESTRICT ptr_beam_monitor = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    static SIXTRL_FN cobj_size_t BeamMonitor_required_num_slots(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const BeamMonitorData< R, I, IAlign > *const
            SIXTRL_RESTRICT ptr_beam_monitor = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign > const*
    BeamMonitor_const_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign >*
    BeamMonitor_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign > const*
    BeamMonitor_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign >*
    BeamMonitor_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign > const*
    BeamMonitor_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT;

    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign >*
    BeamMonitor_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT;

    template< class R, class I, arch_size_t IAlign >
    static SIXTRL_FN bool BeamMonitor_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const BeamMonitorData< R, I, IAlign > *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_buffer_size = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_slots = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_objects = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_pointers = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, class I, arch_size_t IAlign >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign >*
    BeamMonitor_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const BeamMonitorData< R, I, IAlign > *const
            ptr_orig );

    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign >*
    BeamMonitor_new( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer );

    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(), typename... Args >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign >*
    BeamMonitor_add( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer, Args&&... args );
}

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
static SIXTRL_FN ::NS(cobj_type_id_t) NS(BeamMonitor_type_id)( void ) SIXTRL_NOEXCEPT;

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
static SIXTRL_FN ::NS(cobj_type_id_t) NS(BeamMonitor_num_pointers)(
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign >
        *const SIXTRL_RESTRICT ptr_beam_monitor = nullptr ) SIXTRL_NOEXCEPT;

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
static SIXTRL_FN ::NS(cobj_type_id_t) NS(BeamMonitor_required_num_bytes)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign >
        *const SIXTRL_RESTRICT ptr_beam_monitor = nullptr ) SIXTRL_NOEXCEPT;

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
static SIXTRL_FN ::NS(cobj_size_t) NS(BeamMonitor_required_num_slots)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign >
        *const SIXTRL_RESTRICT ptr_beam_monitor = nullptr ) SIXTRL_NOEXCEPT;

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign > const*
NS(BeamMonitor_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign >*
NS(BeamMonitor_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign > const*
NS(BeamMonitor_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign >*
NS(BeamMonitor_from_flat_cbuffer)(
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
    template< class R, class I, arch_size_t IAlign >
    SIXTRL_INLINE cobj_type_id_t BeamMonitor_type_id() SIXTRL_NOEXCEPT
    {
        return ObjDataTypeIdTraits< BeamMonitorData< R, I, IAlign >,
            cobj_type_id_t >::TypeId();
    }

    template< class R, class I, arch_size_t IAlign >
    static SIXTRL_FN cobj_type_id_t BeamMonitor_num_pointers(
        SIXTRL_BE_ARGPTR_DEC const BeamMonitorData< R, I, IAlign > *const
            SIXTRL_RESTRICT ptr_beam_monitor ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs<
            BeamMonitorData< R, I, IAlign > >( ptr_beam_monitor );
    }

    template< class R, class I, arch_size_t IAlign >
    SIXTRL_INLINE cobj_type_id_t BeamMonitor_required_num_bytes(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const BeamMonitorData< R, I, IAlign > *const
            SIXTRL_RESTRICT ptr_beam_monitor ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_bytes<
            BeamMonitorData< R, I, IAlign > >( slot_size, ptr_beam_monitor );
    }

    template< class R, class I, arch_size_t IAlign >
    SIXTRL_INLINE cobj_size_t BeamMonitor_required_num_slots(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const BeamMonitorData< R, I, IAlign > *const
            SIXTRL_RESTRICT ptr_beam_monitor ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_slots<
            BeamMonitorData< R, I, IAlign > >( slot_size, ptr_beam_monitor );
    }

    template< class R, class I, arch_size_t IAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign > const*
    BeamMonitor_const_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index<
            BeamMonitorData< R, I, IAlign > >( index_obj, slot_size );
    }

    template< class R, class I, arch_size_t IAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign > const*
    BeamMonitor_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index<
            BeamMonitorData< R, I, IAlign > >( index_obj, slot_size );
    }

    template< class R, class I, arch_size_t IAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign > const*
    BeamMonitor_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index<
            BeamMonitorData< R, I, IAlign > >( ::NS(CObjFlatBuffer_const_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );
    }

    template< class R, class I, arch_size_t IAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign >*
    BeamMonitor_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index< BeamMonitorData<
            R, I, IAlign > >( ::NS(CObjFlatBuffer_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );
    }

    template< class R, class I, arch_size_t IAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign > const*
    BeamMonitor_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return cbuffer->get_const_object<
            BeamMonitorData< R, I, IAlign > >( pos_in_buffer );
    }

    template< class R, class I, arch_size_t IAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign >*
    BeamMonitor_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return cbuffer->get_object< BeamMonitorData< R, I, IAlign > >( pos_in_buffer );
    }

    template< class R, class I, arch_size_t IAlign >
    SIXTRL_INLINE bool BeamMonitor_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const BeamMonitorData< R, I, IAlign > *const ptr_orig,
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

    template< class R, class I, arch_size_t IAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign >*
    BeamMonitor_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const BeamMonitorData< R, I, IAlign > *const ptr_orig )
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return SIXTRL_CXX_NAMESPACE::CBufferView_add_copy_of_object_detail(
            *cbuffer, ptr_orig, nullptr, nullptr, nullptr, nullptr, false );
    }

    template< class R, class I, arch_size_t IAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign >*
    BeamMonitor_new( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer )
    {
        SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign > temp;
        SIXTRL_CXX_NAMESPACE::BeamMonitor_init< BeamMonitorData< R, I, IAlign > >(
            std::addressof( temp ) );

        return SIXTRL_CXX_NAMESPACE::BeamMonitor_add_copy(
            cbuffer, std::addressof( temp ) );
    }

    template< class R, class I, arch_size_t IAlign, typename... Args >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign >*
    BeamMonitor_add( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer, Args&&... args )
    {
        SIXTRL_BE_ARGPTR_DEC BeamMonitorData< R, I, IAlign > temp;
        SIXTRL_CXX_NAMESPACE::BeamMonitor_init< BeamMonitorData< R, I, IAlign > >(
            std::addressof( temp ), std::forward< Args >( args )... );

        return SIXTRL_CXX_NAMESPACE::BeamMonitor_add_copy<
            BeamMonitorData< R, I, IAlign > >(
                cbuffer, std::addressof( temp ) );
    }
}

/* Provide accessor functions in the C namespace to
 * allow writing portable kernels */

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign >
SIXTRL_INLINE ::NS(cobj_type_id_t) NS(BeamMonitor_type_id)( void ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::BeamMonitor_type_id<
        SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign > >();
}

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign >
SIXTRL_INLINE ::NS(cobj_type_id_t) NS(BeamMonitor_num_pointers)(
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign >
        *const SIXTRL_RESTRICT ptr_beam_monitor ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::BeamMonitor_num_pointers<
        SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign > >( ptr_beam_monitor );
}

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign >
SIXTRL_INLINE ::NS(cobj_type_id_t) NS(BeamMonitor_required_num_bytes)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign >
        *const SIXTRL_RESTRICT ptr_beam_monitor ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::BeamMonitor_required_num_bytes<
        SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign > >(
            slot_size, ptr_beam_monitor );
}

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign >
SIXTRL_INLINE ::NS(cobj_size_t) NS(BeamMonitor_required_num_slots)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign >
        *const SIXTRL_RESTRICT ptr_beam_monitor ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::BeamMonitor_required_num_slots<
        SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign > >(
            slot_size, ptr_beam_monitor );
}

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::BeamMonitorData<
    R, I, IAlign > const*
NS(BeamMonitor_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::BeamMonitor_const_from_cobj_index<
        SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign > >(
            index_obj, slot_size );
}

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign >*
NS(BeamMonitor_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::BeamMonitor_from_cobj_index<
        SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign > >(
            index_obj, slot_size );
}

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::BeamMonitorData<
    R, I, IAlign > const*
NS(BeamMonitor_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::BeamMonitor_const_from_flat_cbuffer<
        SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign > >(
            buffer, pos_in_buffer, slot_size );
}

template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t IAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign >*
BeamMonitor_from_flat_cbuffer(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::BeamMonitor_from_flat_cbuffer<
        SIXTRL_CXX_NAMESPACE::BeamMonitorData< R, I, IAlign > >(
            buffer, pos_in_buffer, slot_size );
}

#endif /* !defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_BEAM_MONITOR_DATA_API_CXX_HPP__ */
