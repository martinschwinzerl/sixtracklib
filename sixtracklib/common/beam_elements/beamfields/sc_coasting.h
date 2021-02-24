#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAMFIELDS_SC_COASTING_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAMFIELDS_SC_COASTING_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beamfields/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(SCCoasting)
{
    NS(be_real_type)  number_of_particles SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)  circumference       SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)  sigma_x             SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)  sigma_y             SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)  length              SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)  x_co                SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)  y_co                SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)  min_sigma_diff      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_flags_type) enabled         SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(SCCoasting);

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(SCCoasting_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(SCCoasting_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(SCCoasting_cobj_actual_handle_size)( NS(cobj_size_type) slot_size
    ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(SCCoasting_cobj_reserved_handle_size)( NS(cobj_size_type) slot_size
    ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(SCCoasting_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_preset)( SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc
    ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_init)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const number_of_particles,
    NS(be_real_type) const circumference,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff, bool const enabled ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_number_of_particles)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_default_number_of_particles)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_set_number_of_particles)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const number_of_particles ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_circumference)(
    SIXTRL_BE_ARGPTR_DEC  const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_default_circumference)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_set_circumference)(
    SIXTRL_BE_ARGPTR_DEC  NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const circumference ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_sigma_x)(
    SIXTRL_BE_ARGPTR_DEC  const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_default_sigma_x)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_set_sigma_x)(
    SIXTRL_BE_ARGPTR_DEC  NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const sigma_x ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_sigma_y)(
    SIXTRL_BE_ARGPTR_DEC  const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_default_sigma_y)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_set_sigma_y)(
    SIXTRL_BE_ARGPTR_DEC  NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const sigma_y ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_length)(
    SIXTRL_BE_ARGPTR_DEC  const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_default_length)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_set_length)(
    SIXTRL_BE_ARGPTR_DEC  NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const length ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_x_co)(
    SIXTRL_BE_ARGPTR_DEC  const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_default_x_co)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_set_x_co)(
    SIXTRL_BE_ARGPTR_DEC  NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const x_co ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_y_co)(
    SIXTRL_BE_ARGPTR_DEC  const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_default_y_co)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_set_y_co)(
    SIXTRL_BE_ARGPTR_DEC  NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const y_co ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_min_sigma_diff)(
    SIXTRL_BE_ARGPTR_DEC  const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SCCoasting_default_min_sigma_diff)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_set_min_sigma_diff)(
    SIXTRL_BE_ARGPTR_DEC  NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const min_sigma_diff ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN bool NS(SCCoasting_enabled)(
    SIXTRL_BE_ARGPTR_DEC  const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(SCCoasting_default_enabled)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_set_enabled)(
    SIXTRL_BE_ARGPTR_DEC  NS(SCCoasting)* SIXTRL_RESTRICT sc,
    bool const is_enabled ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const
        SIXTRL_RESTRICT source ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_sc_coasting)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) const*
NS(SCCoasting_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
    obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) const*
NS(SCCoasting_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN
SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) const* NS(SCCoasting_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(SCCoasting_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    NS(be_real_type) const number_of_particles,
    NS(be_real_type) const circumference,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff, bool const enabled )  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(SCCoasting_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cbuffer_new)( SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)*
    SIXTRL_RESTRICT buffer );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_real_type) const number_of_particles,
    NS(be_real_type) const circumference,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff, bool const enabled );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT orig );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) const*
NS(SCCoasting_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(SCCoasting_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(SCCoasting_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(SCCoasting_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(SCCoasting_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(SCCoasting_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_preset_ext)( SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
    SIXTRL_RESTRICT sc ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(SCCoasting_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(SCCoasting_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_real_type) const number_of_particles,
    NS(be_real_type) const circumference,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff, bool const enabled );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cobj_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc );

#endif /* !defined( _GPUCODE ) */
#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsStoreResultTypeTraits< ::NS(SCCoasting) >
    {
        typedef ::NS(SCCoasting) value_type;
        typedef SIXTRL_BE_ARGPTR_DEC value_type const* const_pointer;
        typedef SIXTRL_BE_ARGPTR_DEC value_type* pointer;
    };

    template<> struct CObjectsTraits< ::NS(SCCoasting) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_SC_COASTING;
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_SC_COASTING > {
            typedef ::NS(SCCoasting) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* ************************************************************************* */
/* *****          Implementation of C inline functions                   *** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(SCCoasting_cobj_type_id)() SIXTRL_NOEXCEPT
{ return ( NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_SC_COASTING; }

SIXTRL_INLINE NS(cobj_size_type) NS(SCCoasting_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(SCCoasting_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(SCCoasting) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(SCCoasting_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(SCCoasting_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(SCCoasting_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( sc ),
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return NS(SCCoasting_cobj_reserved_handle_size)( slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* NS(SCCoasting_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc ) SIXTRL_NOEXCEPT {
    if( sc != SIXTRL_NULLPTR ) NS(SCCoasting_clear)( sc );
    return sc; }

SIXTRL_INLINE NS(status_type) NS(SCCoasting_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc ) SIXTRL_NOEXCEPT {
    return NS(SCCoasting_init)( sc,
        NS(SCCoasting_default_number_of_particles)(),
        NS(SCCoasting_default_circumference)(),
        NS(SCCoasting_default_sigma_x)(), NS(SCCoasting_default_sigma_y)(),
        NS(SCCoasting_default_length)(),
        NS(SCCoasting_default_x_co)(), NS(SCCoasting_default_y_co)(),
        NS(SCCoasting_default_min_sigma_diff)(),
        NS(SCCoasting_default_enabled)() ); }

SIXTRL_INLINE NS(status_type) NS(SCCoasting_init)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const num_particles,
    NS(be_real_type) const circumference,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff, bool const is_enabled
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    status |= NS(SCCoasting_set_number_of_particles)( sc, num_particles );
    status |= NS(SCCoasting_set_circumference)( sc, circumference );
    status |= NS(SCCoasting_set_sigma_x)( sc, sigma_x );
    status |= NS(SCCoasting_set_sigma_y)( sc, sigma_y );
    status |= NS(SCCoasting_set_length)( sc, length );
    status |= NS(SCCoasting_set_x_co)( sc, x_co );
    status |= NS(SCCoasting_set_y_co)( sc, y_co );
    status |= NS(SCCoasting_set_min_sigma_diff)( sc, min_sigma_diff );
    status |= NS(SCCoasting_set_enabled)( sc, is_enabled );
    return status; }

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_number_of_particles)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( sc != SIXTRL_NULLPTR );
    return sc->number_of_particles; }

SIXTRL_INLINE NS(be_real_type)
NS(SCCoasting_default_number_of_particles)() SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(SCCoasting_set_number_of_particles)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const number_of_particles ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( sc != SIXTRL_NULLPTR ) &&
        ( number_of_particles >= ( NS(be_real_type) )0.0 ) )
    {
        sc->number_of_particles = number_of_particles;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_circumference)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( sc != SIXTRL_NULLPTR );
    return sc->circumference; }

SIXTRL_INLINE NS(be_real_type)
NS(SCCoasting_default_circumference)() SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )1.0; }

SIXTRL_INLINE NS(status_type) NS(SCCoasting_set_circumference)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const circumference ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( sc != SIXTRL_NULLPTR ) && ( circumference > ( NS(be_real_type) )0.0 ) )
    {
        sc->circumference = circumference;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_sigma_x)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( sc != SIXTRL_NULLPTR ); return sc->sigma_x; }

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_default_sigma_x)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )1.0; }

SIXTRL_INLINE NS(status_type) NS(SCCoasting_set_sigma_x)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const sigma_x ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( sc != SIXTRL_NULLPTR ) && ( sigma_x > ( NS(be_real_type) )0.0 ) )
    {
        sc->sigma_x = sigma_x;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_sigma_y)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( sc != SIXTRL_NULLPTR ); return sc->sigma_y; }

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_default_sigma_y)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )1.0; }

SIXTRL_INLINE NS(status_type) NS(SCCoasting_set_sigma_y)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const sigma_y ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( sc != SIXTRL_NULLPTR ) && ( sigma_y > ( NS(be_real_type) )0.0 ) )
    {
        sc->sigma_y = sigma_y;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( sc != SIXTRL_NULLPTR ); return sc->length; }

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_default_length)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(SCCoasting_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const length ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( sc != SIXTRL_NULLPTR ) && ( length >= ( NS(be_real_type) )0.0 ) )
    {
        sc->length = length;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_x_co)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( sc != SIXTRL_NULLPTR ); return sc->x_co; }

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_default_x_co)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(SCCoasting_set_x_co)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const x_co ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( sc != SIXTRL_NULLPTR )
    {
        sc->x_co = x_co;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_y_co)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( sc != SIXTRL_NULLPTR ); return sc->y_co; }

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_default_y_co)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(SCCoasting_set_y_co)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const y_co ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( sc != SIXTRL_NULLPTR )
    {
        sc->y_co = y_co;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_min_sigma_diff)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( sc != SIXTRL_NULLPTR ); return sc->min_sigma_diff; }

SIXTRL_INLINE NS(be_real_type) NS(SCCoasting_default_min_sigma_diff)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type)
        )SIXTRL_BE_BEAMFIELDS_DEFAULT_MIN_SIGMA_DIFF; }

SIXTRL_INLINE NS(status_type) NS(SCCoasting_set_min_sigma_diff)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc,
    NS(be_real_type) const min_sigma_diff ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( sc != SIXTRL_NULLPTR ) &&
        ( min_sigma_diff >= ( NS(be_real_type) )0.0 ) )
    {
        sc->min_sigma_diff = min_sigma_diff;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(SCCoasting_enabled)( SIXTRL_BE_ARGPTR_DEC const
    NS(SCCoasting) *const SIXTRL_RESTRICT sc ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( sc != SIXTRL_NULLPTR );
    return ( ( NS(be_flags_type) )1 == sc->enabled ); }

SIXTRL_INLINE bool NS(SCCoasting_default_enabled)() SIXTRL_NOEXCEPT {
    return true; }

SIXTRL_INLINE NS(status_type) NS(SCCoasting_set_enabled)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT sc,
    bool const is_enabled ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( sc != SIXTRL_NULLPTR )
    {
        sc->enabled = ( is_enabled )
            ? ( NS(be_flags_type) )1 : ( NS(be_flags_type) )0;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(status_type) NS(SCCoasting_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        if( dest != src ) {
            status = NS(SCCoasting_init)( dest,
                NS(SCCoasting_number_of_particles)( src ),
                NS(SCCoasting_circumference)( src ),
                NS(SCCoasting_sigma_x)( src ),
                NS(SCCoasting_sigma_y)( src ),
                NS(SCCoasting_length)( src ),
                NS(SCCoasting_x_co)( src ),
                NS(SCCoasting_y_co)( src ),
                NS(SCCoasting_min_sigma_diff)( src ),
                NS(SCCoasting_enabled)( src ) ); }
    }
    return status; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_sc_coasting)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(SCCoasting_cobj_type_id)(), NS(SCCoasting_cobj_actual_handle_size)(
            ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) const*
NS(SCCoasting_const_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_sc_coasting)( obj ) )
        ? ( SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* NS(SCCoasting_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
        )NS(SCCoasting_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) const*
NS(SCCoasting_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(SCCoasting_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* NS(SCCoasting_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(SCCoasting_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) const*
NS(SCCoasting_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(SCCoasting_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* NS(SCCoasting_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(SCCoasting_from_cobj_index)(
        NS(CBuffer_index_at)( buffer, idx ) ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(SCCoasting_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_can_add_copy_of_trivial_object)( buffer, slot_size,
        NS(SCCoasting_cobj_reserved_handle_size)( slot_size ),
            requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(SCCoasting) elem;
    NS(SCCoasting_clear)( &elem );
    return NS(SCCoasting_cobj_flat_buffer_add_copy)(
        buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(be_real_type) const number_of_particles,
    NS(be_real_type) const circumference,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff, bool const enabled ) SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(SCCoasting) elem;
    NS(status_type) const status = NS(SCCoasting_init)( &elem,
        number_of_particles, circumference, sigma_x, sigma_y, length, x_co,
            y_co, min_sigma_diff, enabled );

    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(SCCoasting_cobj_flat_buffer_add_copy)( buffer, slot_size, &elem )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT {
    return NS(SCCoasting_from_cobj_index)(
        NS(CObjFlatBuffer_add_copy_of_trivial_object)( buffer, slot_size, orig,
            NS(SCCoasting_cobj_reserved_handle_size)( slot_size ),
            NS(SCCoasting_cobj_type_id)(), false ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(SCCoasting_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(CBuffer_can_add_copy_of_trivial_object)( b,
    NS(SCCoasting_cobj_reserved_handle_size)( NS(CBuffer_slot_size)( b ) ),
        requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* NS(SCCoasting_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) elem;
    NS(SCCoasting_clear)( &elem );
    return NS(SCCoasting_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* NS(SCCoasting_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_real_type) const number_of_particles,
    NS(be_real_type) const circumference,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff, bool const enabled ) {
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) elem;
    NS(status_type) const status = NS(SCCoasting_init)( &elem,
        number_of_particles, circumference, sigma_x, sigma_y, length,
            x_co, y_co, min_sigma_diff, enabled );

    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(SCCoasting_cbuffer_add_copy)( buffer, &elem ) : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT orig ) {
    NS(cobj_size_type) const slot_size = NS(CBuffer_slot_size)( buffer );
    return NS(SCCoasting_from_cobj_index)( NS(CBuffer_add_copy_of_trivial_object)(
        buffer, orig, NS(SCCoasting_cobj_reserved_handle_size)( slot_size ),
            NS(SCCoasting_cobj_type_id)(), false ) ); }

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAMFIELDS_SC_COASTING_H__ */
