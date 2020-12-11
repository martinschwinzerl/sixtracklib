#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_BEAM_MONITOR_DATA_COBJECTS_API_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_BEAM_MONITOR_DATA_COBJECTS_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_api.h"
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
        cobj_type_id_t, SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_BEAM_MONITOR >
    {
        typedef ::NS(BeamMonitor) value_type;
    };

    template<> struct ObjDataTypeIdTraits< ::NS(BeamMonitor), cobj_type_id_t >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type< ::NS(BeamMonitor) >(),
            "NS(BeamMonitor) should be a C-API type" );

        static SIXTRL_FN constexpr cobj_type_id_t TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_BEAM_MONITOR;
        }
    };

    /* ---------------------------------------------------------------------- */

    static SIXTRL_FN cobj_type_id_t BeamMonitor_type_id() SIXTRL_NOEXCEPT;

    static SIXTRL_FN cobj_size_t BeamMonitor_num_pointers(
        SIXTRL_BE_ARGPTR_DEC const ::NS(BeamMonitor) *const
            SIXTRL_RESTRICT ptr_elem = nullptr ) SIXTRL_NOEXCEPT;

    static SIXTRL_FN cobj_size_t BeamMonitor_required_num_bytes(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const ::NS(BeamMonitor) *const SIXTRL_RESTRICT
            ptr_elem = nullptr ) SIXTRL_NOEXCEPT;

    static SIXTRL_FN cobj_size_t BeamMonitor_required_num_slots(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const ::NS(BeamMonitor) *const
            SIXTRL_RESTRICT ptr_elem = nullptr ) SIXTRL_NOEXCEPT;

    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor) const*
    BeamMonitor_const_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor)*
    BeamMonitor_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor) const*
    BeamMonitor_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor)*
    BeamMonitor_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT;

    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor) const*
    BeamMonitor_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT;

    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor)*
    BeamMonitor_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT;

    #if !defined( _GPUCODE )

    SIXTRL_EXTERN SIXTRL_HOST_FN cobj_type_id_t
        BeamMonitor_type_id_ext() SIXTRL_NOEXCEPT;

    SIXTRL_EXTERN SIXTRL_HOST_FN bool BeamMonitor_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const ::NS(BeamMonitor) *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_buffer_size = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_slots = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_objects = nullptr,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t*
            SIXTRL_RESTRICT ptr_requ_num_pointers = nullptr ) SIXTRL_NOEXCEPT;

    SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor)*
    BeamMonitor_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const ::NS(BeamMonitor) *const ptr_orig );

    SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor)*
    BeamMonitor_new( SIXTRL_BUFFER_ARGPTR_DEC CBufferView*
        SIXTRL_RESTRICT cbuffer );

    template< typename... Args >
    static SIXTRL_FN SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor)* BeamMonitor_add(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        Args&&... args );

    #endif /* !defined( _GPUCODE ) */
}
#endif /* __cplusplus */

SIXTRL_STATIC SIXTRL_FN NS(cobj_type_id_t)
    NS(BeamMonitor_type_id)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(BeamMonitor) const*
NS(BeamMonitor_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(BeamMonitor)*
NS(BeamMonitor_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(BeamMonitor) const*
NS(BeamMonitor_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(BeamMonitor)*
NS(BeamMonitor_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/element_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE cobj_type_id_t BeamMonitor_type_id() SIXTRL_NOEXCEPT
    {
        return ObjDataTypeIdTraits<
            ::NS(BeamMonitor), cobj_type_id_t >::TypeId();
    }

    SIXTRL_INLINE cobj_size_t BeamMonitor_num_pointers(
        SIXTRL_BE_ARGPTR_DEC const ::NS(BeamMonitor) *const SIXTRL_RESTRICT
            ptr_elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs<
            ::NS(BeamMonitor) >( ptr_elem );
    }

    SIXTRL_INLINE cobj_size_t BeamMonitor_required_num_bytes(
        cobj_size_t const slot_size, SIXTRL_BE_ARGPTR_DEC const
            ::NS(BeamMonitor) *const SIXTRL_RESTRICT ptr_elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_bytes<
            ::NS(BeamMonitor) >( slot_size, ptr_elem );
    }

    SIXTRL_INLINE cobj_size_t BeamMonitor_required_num_slots(
        cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const ::NS(BeamMonitor) *const
            SIXTRL_RESTRICT ptr_elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_slots<
            ::NS(BeamMonitor) >( slot_size, ptr_elem );
    }

    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor) const*
    BeamMonitor_const_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index<
            ::NS(BeamMonitor) >( index_obj, slot_size );
    }

    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor)*
    BeamMonitor_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index<
            ::NS(BeamMonitor) >( index_obj, slot_size );
    }

    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor) const*
    BeamMonitor_const_from_flat_cbuffer( SIXTRL_BUFFER_DATAPTR_DEC
            unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index<
            ::NS(BeamMonitor) >( ::NS(CObjFlatBuffer_const_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );
    }

    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor)*
    BeamMonitor_from_flat_cbuffer( SIXTRL_BUFFER_DATAPTR_DEC
            unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index<
            ::NS(BeamMonitor) >( ::NS(CObjFlatBuffer_index)( buffer,
                pos_in_buffer, slot_size ), slot_size );
    }

    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor) const*
    BeamMonitor_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return cbuffer->get_const_object< ::NS(BeamMonitor) >(
            pos_in_buffer );
    }

    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC
    ::NS(BeamMonitor)* BeamMonitor_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( cbuffer != nullptr );
        return cbuffer->get_object< ::NS(BeamMonitor) >( pos_in_buffer );
    }

    template< typename... Args >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor)* BeamMonitor_add(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        Args&&... args )
    {
        SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor) temp;
        SIXTRL_CXX_NAMESPACE::BeamMonitor_init(
            &temp, std::forward< Args >( args )... );
        return SIXTRL_CXX_NAMESPACE::BeamMonitor_add_copy( cbuffer, &temp );
    }
}
#endif /* !defined( __cplusplus ) */

/* Provide accessor functions in the C namespace to
 * allow writing portable kernels */

SIXTRL_INLINE NS(cobj_type_id_t) NS(BeamMonitor_type_id)( void ) SIXTRL_NOEXCEPT
{
    #if defined( __cplusplus )
    SIXTRL_ASSERT( ::NS(OBJECT_TYPE_BEAM_MONITOR) ==
        SIXTRL_CXX_NAMESPACE::BeamMonitor_type_id() );
    #endif /* C++ */

    return NS(OBJECT_TYPE_BEAM_MONITOR);
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(BeamMonitor) const*
NS(BeamMonitor_const_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
        NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(BeamMonitor) const* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(BeamMonitor_type_id)(),
                sizeof( NS(BeamMonitor) ), slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(BeamMonitor)*
NS(BeamMonitor_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(BeamMonitor)* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(BeamMonitor_type_id)(), sizeof( NS(BeamMonitor) ),
                slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(BeamMonitor) const*
NS(BeamMonitor_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(BeamMonitor_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, pos_in_buffer, slot_size ),
            slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(BeamMonitor)*
NS(BeamMonitor_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(BeamMonitor_from_cobj_index)( NS(CObjFlatBuffer_index)(
        buffer, pos_in_buffer, slot_size ), slot_size );
}

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_BEAM_MONITOR_DATA_COBJECTS_API_H__ */
