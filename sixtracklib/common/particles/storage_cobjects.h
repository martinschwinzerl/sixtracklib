#ifndef SIXTRACKLIB_COMMON_PARTICLES_STORAGE_COBJECTS_H__
#define SIXTRACKLIB_COMMON_PARTICLES_STORAGE_COBJECTS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/element_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjTypeIdDataTypeMap<
        cobj_type_id_t, SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_PARTICLE >
    {
        typedef ::NS(Particle) value_type;
    };

    template<> struct ObjDataTypeIdTraits< ::NS(Particle), cobj_type_id_t >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type< ::NS(Particle) >(),
            "NS(Particle) should be a C-API type" );

        static SIXTRL_FN constexpr cobj_type_id_t TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_PARTICLE;
        }
    };
}

#endif /* defined( __cplusplus ) */


#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

struct CObjIndex;

SIXTRL_STATIC SIXTRL_FN NS(cobj_type_id_t) NS(Particle_type_id)( void );

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) const*
NS(Particle_const_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
    struct NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
NS(Particle_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    struct NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) const*
NS(Particle_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
NS(Particle_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;


#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_type_id_t)
    NS(Particle_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_t)
    NS(Particle_num_pointers)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_t) NS(Particle_required_num_bytes)(
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_t) NS(Particle_required_num_slots)(
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) const* NS(Particle_const_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* NS(Particle_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Particle_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const
        SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT orig ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Particle_can_add_copy_detailed)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const SIXTRL_RESTRICT buf,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT orig,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)*
        SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_ptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
NS(Particle_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
NS(Particle_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT buffer,
    NS(particle_real_t)  const x,        NS(particle_real_t) const px,
    NS(particle_real_t)  const y,        NS(particle_real_t) const py,
    NS(particle_real_t)  const zeta,     NS(particle_real_t) const delta,
    NS(particle_real_t)  const psigma,
    NS(particle_index_t) const state,    NS(particle_index_t) const at_element,
    NS(particle_index_t) const at_turn,  NS(particle_index_t) const id,
    NS(particle_real_t)  const s,        NS(particle_real_t)  const rvv,
    NS(particle_real_t)  const rpp,      NS(particle_real_t)  const chi,
    NS(particle_real_t)  const charge_ratio,
    NS(particle_real_t)  const charge0,  NS(particle_real_t)  const mass0,
    NS(particle_real_t)  const beta0,    NS(particle_real_t)  const gamma0,
    NS(particle_real_t)  const pc0 );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
NS(Particle_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT orig );

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

SIXTRL_INLINE NS(cobj_type_id_t) NS(Particle_type_id)( void )
{
    #if !defined( __cplusplus )
    return ::NS(OBJECT_TYPE_PARTICLE);
    #else
    return SIXTRL_CXX_NAMESPACE::CObjElem_type_id< ::NS(Particle) >();
    #endif /* __cplusplus */
}

SIXTRL_INLINE SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) const*
NS(Particle_const_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
        NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) const* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(Particle_type_id)(), sizeof( NS(Particle) ), slot_size );
}

SIXTRL_INLINE SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* NS(Particle_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(Particle_type_id)(), sizeof( NS(Particle) ), slot_size );
}

SIXTRL_INLINE SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) const*
NS(Particle_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) const* )( uintptr_t
        )NS(CObjFlatBuffer_index_begin_addr_by_pos_in_buffer_filter_by_type_info)(
            buffer, pos_in_buffer, NS(Particle_type_id)(), sizeof( NS(Particle) ),
                slot_size );
}

SIXTRL_INLINE SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* NS(Particle_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* )( uintptr_t
        )NS(CObjFlatBuffer_index_begin_addr_by_pos_in_buffer_filter_by_type_info)(
            buffer, pos_in_buffer, NS(Particle_type_id)(), sizeof( NS(Particle) ),
                slot_size );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_STORAGE_COBJECTS_H__ */
