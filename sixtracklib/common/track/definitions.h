#ifndef SIXTRACKLIB_COMMON_TRACK_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_TRACK_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/track/cobj_type_ids_undef.h"
    #include "sixtracklib/common/track/cobj_type_ids.h"
    #include "sixtracklib/common/generated/config.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_TRACK_ARGPTR_DEC )
    #define SIXTRL_TRACK_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC )
        #define  SIXTRL_TRACK_ARGPTR_DEC SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC
    #elif defined( SIXTRL_ARGPTR_DEC )
        #define  SIXTRL_TRACK_ARGPTR_DEC SIXTRL_ARGPTR_DEC
    #else /* defined( SIXTRL_ARGPTR_DEC ) */
        #define  SIXTRL_TRACK_ARGPTR_DEC
    #endif /* defined( SIXTRL_ARGPTR_DEC ) */
#endif /* !defined( SIXTRL_TRACK_ARGPTR_DEC ) */

#if !defined( SIXTRL_TRACK_DATAPTR_DEC )
    #define SIXTRL_TRACK_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC )
        #define  SIXTRL_TRACK_ARGPTR_DEC SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_TRACK_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else /* defined( SIXTRL_DATAPTR_DEC ) */
        #define  SIXTRL_TRACK_DATAPTR_DEC
    #endif /* defined( SIXTRL_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_TRACK_DATAPTR_DEC ) */

#if !defined( SIXTRL_TRACK_ILLEGAL_OBJ_INDEX )
    #define SIXTRL_TRACK_ILLEGAL_OBJ_INDEX 0x7FFFFFFFFFFFFFFE
#endif /* !defined( SIXTRL_TRACK_ILLEGAL_OBJ_INDEX ) */

#if !defined( SIXTRL_TRACK_SUCCESS )
    #define SIXTRL_TRACK_SUCCESS 0
#endif /* !defined( SIXTRL_TRACK_SUCCESS ) */

#if !defined( SIXTRL_TRACK_STATUS_GENERAL_FAILURE )
    #define SIXTRL_TRACK_STATUS_GENERAL_FAILURE -1
#endif /* !defined( SIXTRL_TRACK_STATUS_GENERAL_FAILURE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && ( !defined( _GPUCODE ) */

typedef SIXTRL_UINT64_TYPE      NS(track_flags_type);
typedef SIXTRL_INT32_TYPE       NS(track_status_t);

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(size_type) const NS(TRACK_ILLEGAL_OBJ_INDEX) =
    ( NS(size_type) )SIXTRL_TRACK_ILLEGAL_OBJ_INDEX;


typedef SIXTRL_UINT16_TYPE      NS(track_job_io_flag_t);
typedef SIXTRL_UINT16_TYPE      NS(track_job_clear_flag_t);

typedef NS(cobj_size_type)      NS(track_job_size_t);
typedef SIXTRL_INT64_TYPE       NS(track_job_type_t);
typedef NS(track_job_io_flag_t) NS(track_job_collect_flag_t);
typedef NS(track_job_io_flag_t) NS(track_job_push_flag_t);

/* ------------------------------------------------------------------------- */



SIXTRL_STATIC_VAR NS(track_status_t) const
    NS(TRACK_SUCCESS) = ( NS(track_status_t) )0u;

SIXTRL_STATIC_VAR NS(track_status_t) const
    NS(TRACK_STATUS_GENERAL_FAILURE) = ( NS(track_status_t) )-1;

SIXTRL_STATIC_VAR NS(track_job_io_flag_t) const
    NS(TRACK_JOB_IO_NONE) = ( NS(track_job_io_flag_t) )0x00;

SIXTRL_STATIC_VAR NS(track_job_io_flag_t) const
    NS(TRACK_JOB_IO_PARTICLES) = ( NS(track_job_io_flag_t) )0x01;

SIXTRL_STATIC_VAR NS(track_job_io_flag_t) const
    NS(TRACK_JOB_IO_BEAM_ELEMENTS) = ( NS(track_job_io_flag_t) )0x02;

SIXTRL_STATIC_VAR NS(track_job_io_flag_t) const
    NS(TRACK_JOB_IO_OUTPUT) = ( NS(track_job_io_flag_t) )0x04;

SIXTRL_STATIC_VAR NS(track_job_io_flag_t) const
    NS(TRACK_JOB_IO_DEBUG_REGISTER) = ( NS(track_job_io_flag_t) )0x08;

SIXTRL_STATIC_VAR NS(track_job_io_flag_t) const
    NS(TRACK_JOB_IO_PARTICLES_ADDR) = ( NS(track_job_io_flag_t) )0x10;

SIXTRL_STATIC_VAR NS(track_job_io_flag_t) const NS(TRACK_JOB_COLLECT_ALL) =
    ( NS(track_job_io_flag_t) )0x1f;

SIXTRL_STATIC_VAR NS(track_job_io_flag_t) const NS(TRACK_JOB_PUSH_ALL) =
    ( NS(track_job_push_flag_t) )0x0f;

SIXTRL_STATIC_VAR NS(track_job_io_flag_t) const
    NS(TRACK_JOB_COLLECT_DEFAULT_FLAGS) = ( NS(track_job_io_flag_t) )0x05;

SIXTRL_STATIC_VAR NS(track_job_io_flag_t) const
    NS(TRACK_JOB_PUSH_DEFAULT_FLAGS) = ( NS(track_job_io_flag_t) )0x02;

SIXTRL_STATIC_VAR NS(track_job_size_t) const
    NS(TRACK_JOB_DEFAULT_NUM_PARTICLE_SETS) = ( NS(track_job_size_t) )1u;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR NS(track_job_clear_flag_t) const
    NS(TRACK_JOB_CLEAR_PARTICLE_STRUCTURES) =
        ( NS(track_job_clear_flag_t) )0x01;

SIXTRL_STATIC_VAR NS(track_job_clear_flag_t) const
    NS(TRACK_JOB_CLEAR_BEAM_ELEMENT_STRUCTURES) =
        ( NS(track_job_clear_flag_t) )0x02;

SIXTRL_STATIC_VAR NS(track_job_clear_flag_t) const
    NS(TRACK_JOB_CLEAR_OUTPUT_STRUCTURES) =
        ( NS(track_job_clear_flag_t) )0x04;

SIXTRL_STATIC_VAR NS(track_job_clear_flag_t) const
    NS(TRACK_JOB_CLEAR_CONTROLLER) = ( NS(track_job_clear_flag_t) )0x08;

SIXTRL_STATIC_VAR NS(track_job_clear_flag_t) const
    NS(TRACK_JOB_CLEAR_DEFAULT_KERNELS) = ( NS(track_job_clear_flag_t) )0x10;


SIXTRL_STATIC_VAR NS(track_job_clear_flag_t) const
    NS(TRACK_JOB_DEFAULT_CLEAR_FLAGS) = ( NS(track_job_clear_flag_t) )0x07;

SIXTRL_STATIC_VAR NS(track_job_clear_flag_t) const
    NS(TRACK_JOB_CLEAR_ALL_FLAGS) = ( NS(track_job_clear_flag_t) )0x1f;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR NS(track_job_size_t) const
    NS(TRACK_JOB_DEFAULT_PARTICLE_SET_INDICES)[] = { 0u };

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && ( !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(track_status_t) track_status_t;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_status_t
        TRACK_SUCCESS = static_cast< track_status_t >( 0 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_status_t
        TRACK_STATUS_GENERAL_FAILURE = static_cast< track_status_t >( -1 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST ::NS(size_type)
        TRACK_ILLEGAL_OBJ_INDEX = ::NS(size_type){
            SIXTRL_TRACK_ILLEGAL_OBJ_INDEX };
}
#endif /* defined( __cplusplus )  */


#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(track_job_io_flag_t)       track_job_io_flag_t;
    typedef ::NS(track_job_io_flag_t)       track_job_collect_flag_t;
    typedef ::NS(track_job_io_flag_t)       track_job_push_flag_t;
    typedef ::NS(track_job_clear_flag_t)    track_job_clear_flag_t;

    typedef ::NS(track_job_size_t)          track_job_size_t;
    typedef ::NS(track_job_type_t)          track_job_type_t;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_io_flag_t
        TRACK_JOB_IO_NONE = static_cast< track_job_io_flag_t >( 0 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_io_flag_t
        TRACK_JOB_IO_PARTICLES = static_cast< track_job_io_flag_t >( 1 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_io_flag_t
        TRACK_JOB_IO_BEAM_ELEMENTS = static_cast< track_job_io_flag_t >( 2 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_io_flag_t
        TRACK_JOB_IO_OUTPUT = static_cast< track_job_io_flag_t >( 4 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_io_flag_t
        TRACK_JOB_IO_DEBUG_REGISTER = static_cast< track_job_io_flag_t >( 8 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_io_flag_t
        TRACK_JOB_IO_PARTICLES_ADDR = static_cast< track_job_io_flag_t >( 16 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_io_flag_t
        TRACK_JOB_COLLECT_ALL = static_cast< track_job_io_flag_t >( 31 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_io_flag_t
        TRACK_JOB_PUSH_ALL = static_cast< track_job_io_flag_t >( 15 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_io_flag_t
        TRACK_JOB_IO_DEFAULT_FLAGS = static_cast< track_job_io_flag_t >( 5 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_io_flag_t
        TRACK_JOB_PUSH_DEFAULT_FLAGS = static_cast< track_job_io_flag_t >( 2 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_size_t
        TRACK_JOB_DEFAULT_NUM_PARTICLE_SETS =
            static_cast< track_job_collect_flag_t >( 1 );

    /* --------------------------------------------------------------------- */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_clear_flag_t
        TRACK_JOB_CLEAR_PARTICLE_STRUCTURES =
            static_cast< track_job_clear_flag_t >( 0x01 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_clear_flag_t
        TRACK_JOB_CLEAR_BEAM_ELEMENT_STRUCTURES =
            static_cast< track_job_clear_flag_t >( 0x02 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_clear_flag_t
        TRACK_JOB_CLEAR_OUTPUT_STRUCTURES =
            static_cast< track_job_clear_flag_t >( 0x04 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_clear_flag_t
        TRACK_JOB_CLEAR_CONTROLLER =
            static_cast< track_job_clear_flag_t >( 0x08 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_clear_flag_t
        TRACK_JOB_CLEAR_DEFAULT_KERNELS =
            static_cast< track_job_clear_flag_t >( 0x10 );


    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_clear_flag_t
        TRACK_JOB_DEFAULT_CLEAR_FLAGS =
            static_cast< track_job_clear_flag_t >( 0x07 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_clear_flag_t
        TRACK_JOB_CLEAR_ALL_FLAGS =
            static_cast< track_job_clear_flag_t >( 0x1f );

    /* --------------------------------------------------------------------- */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST track_job_size_t
        TRACK_JOB_DEFAULT_PARTICLE_SET_INDICES[] = { ( track_job_size_t )0u };
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_TRACK_DEFINITIONS_H__ */
/* end: sixtracklib/common/track/definitions.h */
