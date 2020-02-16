#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_STORAGE_COBJECTS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_STORAGE_COBJECTS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/beam_elements/multipole/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/element_traits.hpp"
    #include "sixtracklib/common/cobjects/element_pointers.hpp"
    #include "sixtracklib/common/cobjects/field_offsets.hpp"
    #include "sixtracklib/common/cobjects/field_sizes.hpp"
    #include "sixtracklib/common/cobjects/field_counts.hpp"
    #include "sixtracklib/common/cobjects/helper_functions.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjTypeIdDataTypeMap<
        cobj_type_id_t, SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_MULTIPOLE >
    {
        typedef ::NS(Multipole) value_type;
    };

    template<> struct ObjDataTypeIdTraits< ::NS(Multipole), cobj_type_id_t >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type< ::NS(Multipole) >(),
            "NS(Multipole) should be a C-API type" );

        static SIXTRL_FN constexpr cobj_type_id_t TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_MULTIPOLE;
        }
    };

    /* --------------------------------------------------------------------- */
    /* Layout parameters: num dataptrs, offsets, sizes, counts */
    /* num pointers: */

    template<> struct CObjElemNumPointers< ::NS(Multipole), void >
    {
        static constexpr cobj_size_t min_num_ptrs = cobj_size_t{ 1 };
        static constexpr cobj_size_t max_num_ptrs = cobj_size_t{ 1 };
    };

    constexpr cobj_size_t CObjElemNumPointers<
        ::NS(Multipole), void >::min_num_ptrs;

    constexpr cobj_size_t CObjElemNumPointers<
        ::NS(Multipole), void >::max_num_ptrs;

    /* pointer offsets */

    template<> struct CObjElemFieldOffsets< ::NS(Multipole) >
    {
        static constexpr cobj_size_t offsets[ 1 ] =
        {
            offsetof( ::NS(Multipole), bal_addr )
        };
    };

    constexpr cobj_size_t CObjElemFieldOffsets< ::NS(Multipole) >::offsets[];

    /* pointer element sizes */

    template<> struct CObjElemFieldSizes< ::NS(Multipole) >
    {
        static constexpr cobj_size_t sizes[ 1 ] = { sizeof( be_real_t ) };
    };

    constexpr cobj_size_t CObjElemFieldSizes< ::NS(Multipole) >::sizes[];

    /* pointer element counts */

    template<>
    struct CObjElemFieldCounts< ::NS(Multipole), void >
    {
        static SIXTRL_INLINE SIXTRL_FN cobj_status_t init_field_counts(
            SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT counts_begin,
            SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t const max_num_counts,
            SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT
                ptr = nullptr ) SIXTRL_NOEXCEPT
        {
            cobj_status_t status =
                SIXTRL_CXX_NAMESPACE::COBJECTS_STATUS_GENERAL_FAILURE;

            if( ( counts_begin != nullptr ) &&
                ( max_num_counts > cobj_size_t{ 0 } ) && ( ptr != nullptr ) &&
                ( ptr->order >= 0 ) )
            {
                cobj_size_t const num_bal_values = static_cast< cobj_size_t >(
                    2 * ptr->order + 2 );

                status =
                SIXTRL_CXX_NAMESPACE::CObjElem_init_array_with_two_values(
                    counts_begin, max_num_counts, num_bal_values,
                        cobj_size_t{ 0 }, max_num_counts - 1 );
            }

            return status;
        }
    };
}

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

struct CObjIndex;

SIXTRL_STATIC SIXTRL_FN NS(cobj_type_id_t) NS(Multipole_type_id)( void );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
    struct NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    struct NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;


#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_type_id_t)
    NS(Multipole_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_t)
    NS(Multipole_num_pointers)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_t) NS(Multipole_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_t) NS(Multipole_required_num_slots)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_BE_ARGPTR_DEC NS(Multipole) const* NS(Multipole_const_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_BE_ARGPTR_DEC NS(Multipole)* NS(Multipole_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Multipole_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const
        SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Multipole) *const
        SIXTRL_RESTRICT orig ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Multipole_can_add_copy_detailed)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const SIXTRL_RESTRICT buf,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT orig,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)*
        SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_ptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT buffer,
    NS(be_order_t) const order );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT buffer,
    NS(be_order_t) const order, NS(be_real_t) const length,
    NS(be_real_t) const hxl, NS(be_real_t) const hyl,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_t) const* SIXTRL_RESTRICT bal_values );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT orig );

#endif /* _GPUCODE */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */


/* ************************************************************************* */
/* *****     Implementations of inline methods and functions          ****** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(cobj_type_id_t) NS(Multipole_type_id)( void )
{
    #if !defined( __cplusplus )
    return ::NS(OBJECT_TYPE_MULTIPOLE);
    #else
    return SIXTRL_CXX_NAMESPACE::CObjElem_type_id< ::NS(Multipole) >();
    #endif /* __cplusplus */
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
        NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(Multipole) const* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)( index_obj,
            NS(Multipole_type_id)(), sizeof( NS(Multipole) ), slot_size );
}

SIXTRL_INLINE NS(Multipole)* NS(Multipole_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(Multipole)* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)( index_obj,
            NS(Multipole_type_id)(), sizeof( NS(Multipole) ), slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(Multipole) const* )( uintptr_t
        )NS(CObjFlatBuffer_index_begin_addr_by_pos_in_buffer_filter_by_type_info)(
            buffer, pos_in_buffer, NS(Multipole_type_id)(), sizeof( NS(Multipole) ),
                slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(Multipole)* )( uintptr_t
        )NS(CObjFlatBuffer_index_begin_addr_by_pos_in_buffer_filter_by_type_info)(
            buffer, pos_in_buffer, NS(Multipole_type_id)(), sizeof( NS(Multipole) ),
                slot_size );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_STORAGE_COBJECTS_H__ */
