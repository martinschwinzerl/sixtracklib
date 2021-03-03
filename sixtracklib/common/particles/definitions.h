#ifndef SIXTRACKLIB_COMMON_PARTICLES_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_PARTICLES_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/particles/cobj_type_ids_undef.h"
    #include "sixtracklib/common/particles/cobj_type_ids.h"
    #include "sixtracklib/common/generated/config.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_PARTICLE_ARGPTR_DEC )
    #define   SIXTRL_PARTICLE_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_CBUFFER_ARGPTR_DEC )
        #define  SIXTRL_PARTICLE_ARGPTR_DEC SIXTRL_CBUFFER_ARGPTR_DEC
    #elif defined( SIXTRL_ARGPTR_DEC )
        #define  SIXTRL_PARTICLE_ARGPTR_DEC SIXTRL_ARGPTR_DEC
    #else
        #define  SIXTRL_PARTICLE_ARGPTR_DEC
    #endif
#endif /* SIXTRL_PARTICLE_ARGPTR_DEC */

#if !defined( SIXTRL_PARTICLE_DATAPTR_DEC )
    #define   SIXTRL_PARTICLE_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_CBUFFER_DATAPTR_DEC )
        #define  SIXTRL_PARTICLE_DATAPTR_DEC SIXTRL_CBUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_PARTICLE_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else
        #define  SIXTRL_PARTICLE_DATAPTR_DEC
    #endif
#endif /* SIXTRL_PARTICLE_DATAPTR_DEC */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

#if !defined( SIXTRL_PARTICLES_ARGPTR_DEC )
    #define   SIXTRL_PARTICLES_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_CBUFFER_DATAPTR_DEC )
        #define  SIXTRL_PARTICLES_ARGPTR_DEC SIXTRL_CBUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_PARTICLES_ARGPTR_DEC SIXTRL_DATAPTR_DEC
    #else
        #define  SIXTRL_PARTICLES_ARGPTR_DEC
    #endif
#endif /* SIXTRL_PARTICLES_ARGPTR_DEC */

#if !defined( SIXTRL_PARTICLES_DATAPTR_DEC )
    #define   SIXTRL_PARTICLES_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_CBUFFER_DATAPTR_DEC )
        #define  SIXTRL_PARTICLES_DATAPTR_DEC SIXTRL_CBUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_PARTICLES_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else
        #define  SIXTRL_PARTICLES_DATAPTR_DEC
    #endif
#endif /* SIXTRL_PARTICLES_DATAPTR_DEC */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

#if !defined( SIXTRL_PARTICLES_ADDR_ARGPTR_DEC )
    #define SIXTRL_PARTICLES_ADDR_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_CBUFFER_DATAPTR_DEC )
        #define SIXTRL_PARTICLES_ADDR_ARGPTR_DEC SIXTRL_CBUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC )
        #define SIXTRL_PARTICLES_ADDR_ARGPTR_DEC SIXTRL_DATAPTR_DEC
    #else
        #define SIXTRL_PARTICLES_ADDR_ARGPTR_DEC
    #endif /* defined( SIXTRL_CBUFFER_DATAPTR_DEC ) */
#endif /* SIXTRL_PARTICLE_SET_DATAPTR_DEC */

#if !defined( SIXTRL_PARTICLES_ADDR_DATAPTR_DEC )
    #define SIXTRL_PARTICLES_ADDR_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_CBUFFER_DATAPTR_DEC )
        #define SIXTRL_PARTICLES_ADDR_DATAPTR_DEC SIXTRL_CBUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC )
        #define SIXTRL_PARTICLES_ADDR_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else
        #define SIXTRL_PARTICLES_ADDR_DATAPTR_DEC
    #endif /* defined( SIXTRL_CBUFFER_DATAPTR_DEC ) */
#endif /* SIXTRL_PARTICLES_SET_DATAPTR_DEC */

/* -------------------------------------------------------------------------- */

#if !defined( SIXTRL_PARTICLE_MIN_LEGAL_ID )
    #define SIXTRL_PARTICLE_MIN_LEGAL_ID  0
#endif /* !defined( SIXTRL_PARTICLE_MIN_LEGAL_ID ) */

#if !defined( SIXTRL_PARTICLE_MAX_LEGAL_ID )
    #define SIXTRL_PARTICLE_MAX_LEGAL_ID 9223372036854775806
#endif /* !defined( SIXTRL_PARTICLE_MAX_LEGAL_ID ) */

#if !defined( SIXTRL_PARTICLE_ILLEGAL_ID )
    #define SIXTRL_PARTICLE_ILLEGAL_ID 9223372036854775807
#endif /* !defined( SIXTRL_PARTICLE_ILLEGAL_ID ) */

#if !defined( SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT )
    #define SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT 0
#endif /* !defined( SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) */

#if !defined( SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT )
    #define SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT 9223372036854775806
#endif /* !defined( SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT ) */

#if !defined( SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT )
    #define SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT 9223372036854775807
#endif /* !defined( SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT ) */

#if !defined( SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN )
    #define SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN 0
#endif /* !defined( SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN ) */

#if !defined( SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN )
    #define SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN 9223372036854775806
#endif /* !defined( SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN ) */

#if !defined( SIXTRL_PARTICLE_ILLEGAL_AT_TURN )
    #define SIXTRL_PARTICLE_ILLEGAL_AT_TURN  9223372036854775807
#endif /* !defined( SIXTRL_PARTICLE_ILLEGAL_AT_TURN ) */

/* -------------------------------------------------------------------------- */

#if !defined( SIXTRL_COBJECTS_TYPE_ID_PARTICLES )
    #define SIXTRL_COBJECTS_TYPE_ID_PARTICLES \
        ( SIXTRL_COBJECTS_TYPE_ID_MINIMUM + 2 )
#endif /* !defined( SIXTRL_COBJECTS_TYPE_ID_PARTICLES ) */

#if !defined( SIXTRL_PARTICLES_NUM_REAL_DATAPTRS )
    #define SIXTRL_PARTICLES_NUM_REAL_DATAPTRS 17
#endif /* !defined( SIXTRL_PARTICLES_NUM_REAL_DATAPTRS ) */

#if !defined( SIXTRL_PARTICLES_NUM_INDEX_DATAPTRS )
    #define SIXTRL_PARTICLES_NUM_INDEX_DATAPTRS 4
#endif /* !defined( SIXTRL_PARTICLES_NUM_INDEX_DATAPTRS ) */

#if !defined( SIXTRL_PARTICLES_NUM_DATAPTRS )
    #define SIXTRL_PARTICLES_NUM_DATAPTRS 21
#endif /* !defined( SIXTRL_PARTICLES_NUM_DATAPTRS ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host  */

typedef SIXTRL_INT64_TYPE     NS(particle_index_type);
typedef SIXTRL_REAL_TYPE      NS(particle_real_type);
typedef SIXTRL_INT64_TYPE     NS(particles_num_type);
typedef NS(address_type)      NS(particles_addr_type);
typedef NS(address_diff_type) NS(particles_addr_diff_type);

typedef SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_real_type)*
        NS(particles_real_pointer);

typedef SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_real_type) const*
        NS(particles_real_const_pointer);

typedef SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_index_type)*
        NS(particles_index_pointer);

typedef SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_index_type) const*
        NS(particles_index_const_pointer);

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(size_type) const
    NS(PARTICLES_NUM_INDEX_DATAPTRS) = ( NS(size_type) )4u;

SIXTRL_STATIC_VAR NS(size_type) const
    NS(PARTICLES_NUM_REAL_DATAPTRS) = ( NS(size_type) )17u;

SIXTRL_STATIC_VAR NS(size_type) const
    NS(PARTICLES_NUM_DATAPTRS) = ( NS(size_type) )21u;

#else /* defined( _GPUCODE ) */

typedef enum
{
    NS(PARTICLES_NUM_INDEX_DATAPTRS) = 4,
    NS(PARTICLES_NUM_REAL_DATAPTRS)  = 17,
    NS(PARTICLES_NUM_DATAPTRS)       = 21
}
NS(ParticlesGlobalConstantsEnum);

#endif /* !defined( _GPUCODE ) */

typedef enum
{
    NS(PARTICLE_INIT_MODE_CHARGE0_MASS0_BETA0) = 0,
    NS(PARTICLE_INIT_MODE_CHARGE0_MASS0_GAMMA0) = 1,
    NS(PARTICLE_INIT_MODE_CHARGE0_MASS0_P0C) = 2,
    NS(PARTICLE_INIT_MODE_DEFAULT) = 0
}
NS(ParticleInitModeEnum);

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host  */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(particle_index_type)           particle_index_type;
    typedef ::NS(particle_real_type)            particle_real_type;
    typedef ::NS(particles_num_type)            particles_num_type;

    typedef ::NS(particles_real_pointer)        particles_real_pointer;
    typedef ::NS(particles_real_const_pointer)  particles_real_const_pointer;

    typedef ::NS(particles_index_pointer)       particles_index_ptr_t;
    typedef ::NS(particles_index_const_pointer) particles_index_const_ptr_t;
    typedef ::NS(particles_addr_type)           particles_addr_type;
    typedef ::NS(particles_addr_diff_type)      particles_addr_diff_type;

    /* --------------------------------------------------------------------- */

    #if !defined( _GPUCODE )
    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST ::NS(size_type)
        PARTICLES_NUM_INDEX_DATAPTRS = static_cast< ::NS(size_type) >(
            ::NS(PARTICLES_NUM_INDEX_DATAPTRS) );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST ::NS(size_type)
        PARTICLES_NUM_REAL_DATAPTRS = static_cast< ::NS(size_type) >(
            ::NS(PARTICLES_NUM_REAL_DATAPTRS) );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST ::NS(size_type)
        PARTICLES_NUM_DATAPTRS = static_cast< ::NS(size_type) >(
            ::NS(PARTICLES_NUM_DATAPTRS) );
    #endif /* Host */
}
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_DEFINITIONS_H__ */
