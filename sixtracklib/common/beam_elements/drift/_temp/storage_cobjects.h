#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_STORAGE_COBJECTS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_STORAGE_COBJECTS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/beam_elements/drift/definitions.h"
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/element_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjTypeIdDataTypeMap<
        cobj_type_id_t, SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT >
    {
        typedef ::NS(Drift) value_type;
    };

    template<> struct ObjDataTypeIdTraits< ::NS(Drift), cobj_type_id_t >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type< ::NS(Drift) >(),
            "NS(Drift) should be a C-API type" );

        static SIXTRL_FN constexpr cobj_type_id_t TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT;
        }
    };
}

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

struct CObjIndex;

SIXTRL_STATIC SIXTRL_FN NS(cobj_type_id_t) NS(Drift_type_id)( void );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Drift) const*
NS(Drift_const_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
    struct NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Drift)*
NS(Drift_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    struct NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Drift) const*
NS(Drift_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Drift)*
NS(Drift_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;


#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_type_id_t)
    NS(Drift_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_t)
    NS(Drift_num_pointers)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_t) NS(Drift_required_num_bytes)(
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_t) NS(Drift_required_num_slots)(
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_BE_ARGPTR_DEC NS(Drift) const* NS(Drift_const_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Drift_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const
        SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Drift) *const
        SIXTRL_RESTRICT orig ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Drift_can_add_copy_detailed)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const SIXTRL_RESTRICT buf,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT orig,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)*
        SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_ptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT buffer,
    NS(be_real_t) const length );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT orig );

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

SIXTRL_INLINE NS(cobj_type_id_t) NS(Drift_type_id)( void )
{
    #if !defined( __cplusplus )
    return ::NS(OBJECT_TYPE_DRIFT);
    #else
    return SIXTRL_CXX_NAMESPACE::CObjElem_type_id< ::NS(Drift) >();
    #endif /* __cplusplus */
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Drift) const*
NS(Drift_const_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
        NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(Drift) const* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(Drift_type_id)(), sizeof( NS(Drift) ), slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(Drift)* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(Drift_type_id)(), sizeof( NS(Drift) ), slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Drift) const*
NS(Drift_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(Drift) const* )( uintptr_t
        )NS(CObjFlatBuffer_index_begin_addr_by_pos_in_buffer_filter_by_type_info)(
            buffer, pos_in_buffer, NS(Drift_type_id)(), sizeof( NS(Drift) ),
                slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(Drift)* )( uintptr_t
        )NS(CObjFlatBuffer_index_begin_addr_by_pos_in_buffer_filter_by_type_info)(
            buffer, pos_in_buffer, NS(Drift_type_id)(), sizeof( NS(Drift) ),
                slot_size );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_STORAGE_COBJECTS_H__ */
