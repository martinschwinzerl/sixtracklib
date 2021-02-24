#ifndef SIXTRACKLIB_COMMON_PARTICLES_COBJ_TYPE_IDS_H__
#define SIXTRACKLIB_COMMON_PARTICLES_COBJ_TYPE_IDS_H__

#if !defined( SIXTRL_COBJECTS_TYPE_ID_SINGLE_PARTICLE )
    #define SIXTRL_COBJECTS_TYPE_ID_SINGLE_PARTICLE 1
#endif /* !defined( SIXTRL_COBJECTS_TYPE_ID_SINGLE_PARTICLE ) */

#if !defined( SIXTRL_COBJECTS_TYPE_ID_PARTICLES_COLLECTION )
    #define SIXTRL_COBJECTS_TYPE_ID_PARTICLES_COLLECTION 2
#endif /* !defined( SIXTRL_COBJECTS_TYPE_ID_PARTICLES_COLLECTION ) */

#if !defined( SIXTRL_COBJECTS_TYPE_ID_PARTICLES_ADDR )
    #define SIXTRL_COBJECTS_TYPE_ID_PARTICLES_ADDR 3
#endif /* !defined( SIXTRL_COBJECTS_TYPE_ID_PARTICLES_ADDR ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

typedef enum NS(cobj_particles_type_ids)
{
    NS(COBJECTS_TYPE_ID_SINGLE_PARTICLE) = SIXTRL_COBJECTS_TYPE_ID_SINGLE_PARTICLE,
    NS(COBJECTS_TYPE_ID_PARTICLES_COLLECTION) = SIXTRL_COBJECTS_TYPE_ID_PARTICLES_COLLECTION,
    NS(COBJECTS_TYPE_ID_PARTICLES_ADDR) = SIXTRL_COBJECTS_TYPE_ID_PARTICLES_ADDR
}
NS(cobj_particles_type_ids);

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST ::NS(cobj_obj_id_type)
        COBJECTS_TYPE_ID_SINGLE_PARTICLE = static_cast< ::NS(cobj_obj_id_type) >(
            SIXTRL_COBJECTS_TYPE_ID_SINGLE_PARTICLE );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST ::NS(cobj_obj_id_type)
        COBJECTS_TYPE_ID_PARTICLES_COLLECTION = static_cast<
            ::NS(cobj_obj_id_type) >(
                SIXTRL_COBJECTS_TYPE_ID_PARTICLES_COLLECTION );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST ::NS(cobj_obj_id_type)
        COBJECTS_TYPE_ID_PARTICLES_ADDR = static_cast< ::NS(cobj_obj_id_type) >(
            SIXTRL_COBJECTS_TYPE_ID_PARTICLES_ADDR );

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_COBJ_TYPE_IDS_H__ */
