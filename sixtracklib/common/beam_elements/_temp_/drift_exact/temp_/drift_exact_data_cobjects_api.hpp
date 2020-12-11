#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DRIFT_EXACT_DATA_COBJECTS_API_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DRIFT_EXACT_DATA_COBJECTS_API_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact_data.hpp"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact_data_api.hpp"
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
    SIXTRL_STATIC SIXTRL_FN cobj_type_id_t Drift_type_id() SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN cobj_type_id_t Drift_num_pointers(
        SIXTRL_BE_ARGPTR_DEC const DriftData< R, RAlign > *const
            SIXTRL_RESTRICT ptr_drift = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN cobj_type_id_t Drift_required_num_bytes(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const DriftData< R, RAlign > *const
            SIXTRL_RESTRICT ptr_drift = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN cobj_size_t Drift_required_num_slots(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const DriftData< R, RAlign > *const
            SIXTRL_RESTRICT ptr_drift = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign > const*
    Drift_const_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
            ::NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >*
    Drift_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign > const*
    Drift_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >*
    Drift_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign > const*
    Drift_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >*
    Drift_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN bool Drift_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const DriftData< R, RAlign > *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_buffer_size = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_slots = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_objects = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_pointers = nullptr ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >*
    Drift_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const DriftData< R, RAlign > *const
            ptr_orig );

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >*
    Drift_new( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer );

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(), typename... Args >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >*
    Drift_add( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer, Args&&... args );
}

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
SIXTRL_STATIC SIXTRL_FN ::NS(cobj_type_id_t)
NS(Drift_type_id)( void ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_STATIC SIXTRL_FN ::NS(cobj_type_id_t) NS(Drift_num_pointers)(
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign >
        *const SIXTRL_RESTRICT ptr_drift = nullptr ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_STATIC SIXTRL_FN ::NS(cobj_type_id_t) NS(Drift_required_num_bytes)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign >
        *const SIXTRL_RESTRICT ptr_drift = nullptr ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_STATIC SIXTRL_FN ::NS(cobj_size_t) NS(Drift_required_num_slots)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign >
        *const SIXTRL_RESTRICT ptr_drift = nullptr ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::DriftData<
    R, RAlign > const*
NS(Drift_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::DriftData<
    R, RAlign >*
NS(Drift_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::DriftData<
    R, RAlign > const*
NS(Drift_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

template< class R, ::NS(arch_size_t) RAlign =
    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::DriftData<
    R, RAlign >*
NS(Drift_from_flat_cbuffer)(
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
    SIXTRL_INLINE cobj_type_id_t Drift_type_id() SIXTRL_NOEXCEPT
    {
        return ObjDataTypeIdTraits<
            DriftData< R, RAlign >, cobj_type_id_t >::TypeId();
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN cobj_type_id_t Drift_num_pointers(
        SIXTRL_BE_ARGPTR_DEC const DriftData< R, RAlign > *const
            SIXTRL_RESTRICT ptr_drift ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs<
            DriftData< R, RAlign > >( ptr_drift );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE cobj_type_id_t Drift_required_num_bytes(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const DriftData< R, RAlign > *const
            SIXTRL_RESTRICT ptr_drift ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_bytes<
            DriftData< R, RAlign > >( slot_size, ptr_drift );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE cobj_size_t Drift_required_num_slots(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const DriftData< R, RAlign > *const
            SIXTRL_RESTRICT ptr_drift ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_slots<
            DriftData< R, RAlign > >( slot_size, ptr_drift );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign > const*
    Drift_const_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index<
            DriftData< R, RAlign > >( index_obj, slot_size );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign > const*
    Drift_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index<
            DriftData< R, RAlign > >( index_obj, slot_size );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign > const*
    Drift_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index<
            DriftData< R, RAlign > >( ::NS(CObjFlatBuffer_const_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >*
    Drift_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index< DriftData<
            R, RAlign > >( ::NS(CObjFlatBuffer_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );
    }

    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign > const*
    Drift_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return cbuffer->get_const_object<
            DriftData< R, RAlign > >( pos_in_buffer );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >*
    Drift_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return cbuffer->get_object< DriftData< R, RAlign > >( pos_in_buffer );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE bool Drift_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const DriftData< R, RAlign > *const ptr_orig,
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
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >*
    Drift_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const DriftData< R, RAlign > *const ptr_orig )
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return SIXTRL_CXX_NAMESPACE::CBufferView_add_copy_of_object_detail(
            *cbuffer, ptr_orig, nullptr, nullptr, nullptr, nullptr, false );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >*
    Drift_new( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer )
    {
        SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign > temp;
        SIXTRL_CXX_NAMESPACE::Drift_init< DriftData< R, RAlign > >(
            std::addressof( temp ) );

        return SIXTRL_CXX_NAMESPACE::Drift_add_copy(
            cbuffer, std::addressof( temp ) );
    }

    template< class R, arch_size_t RAlign, typename... Args >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign >*
    Drift_add( SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer, Args&&... args )
    {
        SIXTRL_BE_ARGPTR_DEC DriftData< R, RAlign > temp;
        SIXTRL_CXX_NAMESPACE::Drift_init< DriftData< R, RAlign > >(
            std::addressof( temp ), std::forward< Args >( args )... );

        return SIXTRL_CXX_NAMESPACE::Drift_add_copy< DriftData< R, RAlign > >(
            cbuffer, std::addressof( temp ) );
    }
}

/* Provide accessor functions in the C namespace to
 * allow writing portable kernels */

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE ::NS(cobj_type_id_t) NS(Drift_type_id)( void ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_type_id<
        SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign > >();
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE ::NS(cobj_type_id_t) NS(Drift_num_pointers)(
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign >
        *const SIXTRL_RESTRICT ptr_drift ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_num_pointers<
        SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign > >( ptr_drift );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE ::NS(cobj_type_id_t) NS(Drift_required_num_bytes)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign >
        *const SIXTRL_RESTRICT ptr_drift ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_required_num_bytes<
        SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign > >( slot_size, ptr_drift );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE ::NS(cobj_size_t) NS(Drift_required_num_slots)(
    ::NS(cobj_size_t) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign >
        *const SIXTRL_RESTRICT ptr_drift ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_required_num_slots<
        SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign > >( slot_size, ptr_drift );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::DriftData<
    R, RAlign > const*
NS(Drift_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_const_from_cobj_index<
        SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign > >( index_obj, slot_size );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign >*
NS(Drift_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_from_cobj_index<
        SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign > >( index_obj, slot_size );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::DriftData<
    R, RAlign > const*
NS(Drift_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_const_from_flat_cbuffer<
        SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign > >(
            buffer, pos_in_buffer, slot_size );
}

template< class R, ::NS(arch_size_t) RAlign >
SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign >*
Drift_from_flat_cbuffer(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer,
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Drift_from_flat_cbuffer<
        SIXTRL_CXX_NAMESPACE::DriftData< R, RAlign > >(
            buffer, pos_in_buffer, slot_size );
}

#endif /* !defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DRIFT_EXACT_DATA_API_CXX_HPP__ */
