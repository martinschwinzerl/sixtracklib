#ifndef SIXTRACKLIB_COMMON_CONTROL_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_CONTROL_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/architecture/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

typedef SIXTRL_UINT32_T             NS(arch_kernel_id_t);
typedef SIXTRL_UINT64_T             NS(arch_variant_flags_t);

typedef NS(arch_status_t)           NS(ctrl_status_t);
typedef NS(arch_size_t)             NS(ctrl_size_t);
typedef NS(arch_kernel_id_t)        NS(ctrl_kernel_id_t);

typedef NS(arch_variant_flags_t)    NS(kernel_variant_t);
typedef SIXTRL_UINT32_T             NS(kernel_purpose_t);
typedef SIXTRL_UINT64_T             NS(kernel_argument_set_t);
typedef SIXTRL_UINT64_T             NS(kernel_op_flags_t);
typedef SIXTRL_UINT32_T             NS(kernel_set_id_t);

typedef SIXTRL_INT64_T              NS(node_platform_id_t);
typedef SIXTRL_INT64_T              NS(node_device_id_t);
typedef SIXTRL_UINT32_T             NS(node_index_t);
typedef SIXTRL_UINT16_T             NS(node_id_str_fmt_t);
typedef SIXTRL_UINT8_T              NS(node_str_role_t);
typedef SIXTRL_UINT32_T             NS(node_set_id_t);

typedef enum NS(ctrl_perform_remap_flag_e)
{
    NS(CTRL_PERFORM_REMAP) = 0,
    NS(CTRL_PERFORM_NO_REMAP) = 1
}
NS(ctrl_perform_remap_flag_t);

#if !defined( SIXTRL_NODE_ILLEGAL_PLATFORM_ID )
    #define SIXTRL_NODE_ILLEGAL_PLATFORM_ID -1
#endif /* !defined( SIXTRL_NODE_ILLEGAL_PLATFORM_ID ) */

#if !defined( SIXTRL_NODE_ILLEGAL_DEVICE_ID )
    #define SIXTRL_NODE_ILLEGAL_DEVICE_ID -1
#endif /* !defined( SIXTRL_NODE_ILLEGAL_DEVICE_ID ) */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_ARCH_DEBUGGING_REGISTER_EMPTY )
    #define SIXTRL_ARCH_DEBUGGING_REGISTER_EMPTY 0
#endif /* SIXTRL_ARCH_DEBUGGING_REGISTER_EMPTY */

#if !defined( SIXTRL_ARCH_DEBUGGING_MIN_FLAG )
    #define SIXTRL_ARCH_DEBUGGING_MIN_FLAG 0x0000000100000000
#endif /* !defined( SIXTRL_ARCH_DEBUGGING_MIN_FLAG ) */

#if !defined( SIXTRL_ARCH_DEBUGGING_MAX_FLAG )
    #define SIXTRL_ARCH_DEBUGGING_MAX_FLAG 0x8000000000000000
#endif /* !defined( SIXTRL_ARCH_DEBUGGING_MAX_FLAG ) */

#if !defined( SIXTRL_ARCH_DEBUGGING_STATUS_BITMASK )
    #define SIXTRL_ARCH_DEBUGGING_STATUS_BITMASK 0x00000000ffffffff
#endif /* !defined( SIXTRL_ARCH_DEBUGGING_STATUS_BITMASK ) */

#if !defined( SIXTRL_ARCH_DEBUGGING_STATUS_INV_BITMASK )
    #define SIXTRL_ARCH_DEBUGGING_STATUS_INV_BITMASK 0xffffffff00000000
#endif /* !defined( SIXTRL_ARCH_DEBUGGING_STATUS_INV_BITMASK ) */

#if !defined( SIXTRL_ARCH_DEBUGGING_STATUS_MAX_FLAG )
    #define SIXTRL_ARCH_DEBUGGING_STATUS_MAX_FLAG 0x80000000
#endif /* !defined( SIXTRL_ARCH_DEBUGGING_STATUS_MAX_FLAG ) */

#if !defined( SIXTRL_ARCH_DEBUGGING_GENERAL_FAILURE )
    #define SIXTRL_ARCH_DEBUGGING_GENERAL_FAILURE 0xFFFFFFFF00000000
#endif /* !defined( SIXTRL_ARCH_DEBUGGING_GENERAL_FAILURE ) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_NOARCH)
    #define SIXTRL_NODE_ID_STR_FORMAT_NOARCH 0
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_NOARCH) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_ARCHID)
    #define SIXTRL_NODE_ID_STR_FORMAT_ARCHID 1
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_ARCHID) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR)
    #define SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR 2
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_DEFAULT)
    #define SIXTRL_NODE_ID_STR_FORMAT_DEFAULT 0
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_DEFAULT) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL)
    #define SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL 0xffff
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL) */


#if !defined( _GPUCODE )

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(arch_debugging_t) const
    NS(ARCH_DEBUGGING_REGISTER_EMPTY) =
        ( NS(arch_debugging_t) )SIXTRL_ARCH_DEBUGGING_REGISTER_EMPTY;

SIXTRL_STATIC_VAR NS(arch_debugging_t) const
    NS(ARCH_DEBUGGING_MIN_FLAG) =
        ( NS(arch_debugging_t) )SIXTRL_ARCH_DEBUGGING_MIN_FLAG;

SIXTRL_STATIC_VAR NS(arch_debugging_t) const
    NS(ARCH_DEBUGGING_MAX_FLAG) =
        ( NS(arch_debugging_t) )SIXTRL_ARCH_DEBUGGING_MAX_FLAG;

SIXTRL_STATIC_VAR NS(arch_debugging_t) const
    NS(ARCH_DEBUGGING_STATUS_BITMASK) =
        ( NS(arch_debugging_t) )SIXTRL_ARCH_DEBUGGING_STATUS_BITMASK;

SIXTRL_STATIC_VAR NS(arch_debugging_t) const
    NS(ARCH_DEBUGGING_STATUS_MAX_FLAG) = ( NS(arch_debugging_t)
        )SIXTRL_ARCH_DEBUGGING_STATUS_MAX_FLAG;

SIXTRL_STATIC_VAR NS(arch_debugging_t) const
    NS(ARCH_DEBUGGING_GENERAL_FAILURE) =
        ( NS(arch_debugging_t) )SIXTRL_ARCH_DEBUGGING_GENERAL_FAILURE;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(arch_kernel_id_t) const
    NS(ARCH_ILLEGAL_KERNEL_ID) = ( NS(arch_kernel_id_t) )0xFFFFFFFF;

SIXTRL_STATIC_VAR NS(arch_kernel_id_t) const
    NS(ARCH_ILLEGAL_KERNEL_CONFIG_ID) = ( NS(arch_kernel_id_t) )0xFFFFFFFF;

SIXTRL_STATIC_VAR NS(kernel_set_id_t) const
    NS(ARCH_ILLEGAL_KERNEL_SET_ID) = ( NS(kernel_set_id_t) )0xFFFFFFFF;

SIXTRL_STATIC_VAR NS(arch_variant_flags_t) const
    NS(ARCH_VARIANT_NONE) = ( NS(arch_variant_flags_t) )0;

SIXTRL_STATIC_VAR NS(arch_variant_flags_t) const
    NS(ARCH_VARIANT_DEBUG) = ( NS(arch_variant_flags_t) )0x8000000000000000;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(kernel_purpose_t) const
    NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER) = ( NS(kernel_purpose_t) )0u;

SIXTRL_STATIC_VAR NS(kernel_purpose_t) const
    NS(KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES) =
        ( NS(kernel_purpose_t) )1u;

SIXTRL_STATIC_VAR NS(kernel_purpose_t) const
    NS(KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN) = ( NS(kernel_purpose_t) )2u;

SIXTRL_STATIC_VAR NS(kernel_purpose_t) const
    NS(KERNEL_CONFIG_PURPOSE_TRACK_ELEM_BY_ELEM) = ( NS(kernel_purpose_t) )3u;

SIXTRL_STATIC_VAR NS(kernel_purpose_t) const
    NS(KERNEL_CONFIG_PURPOSE_TRACK_LINE) = ( NS(kernel_purpose_t) )4u;

SIXTRL_STATIC_VAR NS(kernel_purpose_t) const
    NS(KERNEL_CONFIG_PURPOSE_ASSIGN_BEAM_MONITOR_OUTPUT) =
        ( NS(kernel_purpose_t) )5u;

SIXTRL_STATIC_VAR NS(kernel_purpose_t) const
    NS(KERNEL_CONFIG_PURPOSE_ASSIGN_ELEM_BY_ELEM_OUTPUT) =
        ( NS(kernel_purpose_t) )6u;

SIXTRL_STATIC_VAR NS(kernel_purpose_t) const
    NS(KERNEL_CONFIG_PURPOSE_MAX_PREDEFINED_ID) =
        ( NS(kernel_purpose_t) )6u;

SIXTRL_STATIC_VAR NS(kernel_purpose_t) const
    NS(KERNEL_CONFIG_PURPOSE_MAX_RESERVED) = ( NS(kernel_purpose_t) )1022u;

SIXTRL_STATIC_VAR NS(kernel_purpose_t) const
    NS(KERNEL_CONFIG_PURPOSE_UNSPECIFIED) = ( NS(kernel_purpose_t) )1023u;

SIXTRL_STATIC_VAR NS(kernel_purpose_t) const
    NS(KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID) =
        ( NS(kernel_purpose_t) )1024u;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(node_set_id_t) const NS(NODE_ILLEGAL_NODE_SET_ID) =
    ( NS(node_set_id_t) )0xFFFFFFFF;

SIXTRL_STATIC_VAR NS(node_platform_id_t) const NS(NODE_ILLEGAL_PLATFORM_ID) =
    ( NS(node_platform_id_t) )SIXTRL_NODE_ILLEGAL_PLATFORM_ID;

SIXTRL_STATIC_VAR NS(node_device_id_t) const NS(NODE_ILLEGAL_DEVICE_ID) =
    ( NS(node_device_id_t) )SIXTRL_NODE_ILLEGAL_DEVICE_ID;

SIXTRL_STATIC_VAR NS(node_index_t) const NS(NODE_UNDEFINED_INDEX) =
    ( NS(node_index_t) )0xFFFFFFFF;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(node_id_str_fmt_t) const NS(NODE_ID_STR_FORMAT_NOARCH) =
    ( NS(node_id_str_fmt_t) )SIXTRL_NODE_ID_STR_FORMAT_NOARCH;

SIXTRL_STATIC_VAR NS(node_id_str_fmt_t) const NS(NODE_ID_STR_FORMAT_ARCHID) =
    ( NS(node_id_str_fmt_t) )SIXTRL_NODE_ID_STR_FORMAT_ARCHID;

SIXTRL_STATIC_VAR NS(node_id_str_fmt_t) const NS(NODE_ID_STR_FORMAT_ARCHSTR) =
    ( NS(node_id_str_fmt_t) )SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR;

SIXTRL_STATIC_VAR NS(node_id_str_fmt_t) const NS(NODE_ID_STR_FORMAT_DEFAULT) =
    ( NS(node_id_str_fmt_t) )SIXTRL_NODE_ID_STR_FORMAT_DEFAULT;

SIXTRL_STATIC_VAR NS(node_id_str_fmt_t) const NS(NODE_ID_STR_FORMAT_ILLEGAL) =
    ( NS(node_id_str_fmt_t) )SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(node_str_role_t) const NS(NODE_STR_ROLE_ID) =
    ( NS(node_str_role_t) )0u;

SIXTRL_STATIC_VAR NS(node_str_role_t) const NS(NODE_STR_ROLE_UNIQUE_ID) =
    ( NS(node_str_role_t) )1u;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(kernel_argument_set_t) const
    NS(DEFAULT_KERNEL_ARGUMENT_SET) = ( NS(kernel_argument_set_t) )0u;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(kernel_set_id_t) const
    NS(ILLEGAL_KERNEL_SET_ID) = ( NS(kernel_set_id_t) )0u;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(kernel_op_flags_t) const NS(KERNEL_OP_FLAGS_NONE) =
    ( NS(kernel_op_flags_t) )0u;

SIXTRL_STATIC_VAR NS(kernel_op_flags_t) const
NS(KERNEL_OP_CTRL_HAS_REQUIRED_PURPOSES) = ( NS(kernel_op_flags_t) )0x00000001;

SIXTRL_STATIC_VAR NS(kernel_op_flags_t) const
NS(KERNEL_OP_CTRL_KERNELS_AVAILABLE) = ( NS(kernel_op_flags_t) )0x00000002;

SIXTRL_STATIC_VAR NS(kernel_op_flags_t) const
NS(KERNEL_OP_CTRL_KERNELS_READY) = ( NS(kernel_op_flags_t) )0x00000004;

SIXTRL_STATIC_VAR NS(kernel_op_flags_t) const
NS(KERNEL_OP_CTRL_READY_TO_SEND) = ( NS(kernel_op_flags_t) )0x00000008;

SIXTRL_STATIC_VAR NS(kernel_op_flags_t) const
NS(KERNEL_OP_CTRL_READY_TO_RECEIVE) = ( NS(kernel_op_flags_t) )0x00000010;


SIXTRL_STATIC_VAR NS(kernel_op_flags_t) const
NS(KERNEL_OP_TRACK_JOB_HAS_REQUIRED_PURPOSES) =
    ( NS(kernel_op_flags_t) )0x00000100;

SIXTRL_STATIC_VAR NS(kernel_op_flags_t) const
NS(KERNEL_OP_TRACK_JOB_KERNELS_AVAILABLE) =
    ( NS(kernel_op_flags_t) )0x00000200;

SIXTRL_STATIC_VAR NS(kernel_op_flags_t) const
NS(KERNEL_OP_TRACK_JOB_KERNELS_READY) =
    ( NS(kernel_op_flags_t) )0x00000400;


SIXTRL_STATIC_VAR NS(kernel_op_flags_t) const
NS(KERNEL_OP_HAS_ALL_REQUIRED_PURPOSES) =
    ( NS(kernel_op_flags_t) )0x00010000;

SIXTRL_STATIC_VAR NS(kernel_op_flags_t) const
NS(KERNEL_OP_ALL_REQUIRED_KERNELS_AVAILABLE) =
    ( NS(kernel_op_flags_t) )0x00020000;

SIXTRL_STATIC_VAR NS(kernel_op_flags_t) const
NS(KERNEL_OP_ALL_REQUIRED_KERNELS_READY) =
    ( NS(kernel_op_flags_t) )0x00040000;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}

namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(ctrl_status_t)          ctrl_status_t;
    typedef ::NS(ctrl_size_t)            ctrl_size_t;
    typedef ::NS(ctrl_kernel_id_t)       ctrl_kernel_id_t;
    typedef ::NS(kernel_variant_t)       kernel_variant_t;
    typedef ::NS(kernel_purpose_t)       kernel_purpose_t;
    typedef ::NS(kernel_argument_set_t)  kernel_argument_set_t;
    typedef ::NS(kernel_set_id_t)        kernel_set_id_t;
    typedef ::NS(kernel_op_flags_t)      kernel_op_flags_t;

    typedef ::NS(arch_status_t)          arch_status_t;
    typedef ::NS(arch_id_t)              arch_id_t;
    typedef ::NS(arch_size_t)            arch_size_t;
    typedef ::NS(arch_debugging_t)       arch_debugging_t;
    typedef ::NS(arch_kernel_id_t)       arch_kernel_id_t;
    typedef ::NS(arch_variant_flags_t)   arch_variant_flags_t;

    typedef ::NS(node_platform_id_t)     node_platform_id_t;
    typedef ::NS(node_device_id_t)       node_device_id_t;
    typedef ::NS(node_index_t)           node_index_t;
    typedef ::NS(node_id_str_fmt_t)      node_id_str_fmt_t;
    typedef ::NS(node_str_role_t)        node_str_role_t;
    typedef ::NS(node_set_id_t)          node_set_id_t;

    typedef enum
    {
        CTRL_PERFORM_REMAP = ::NS(CTRL_PERFORM_REMAP),
        CTRL_PERFORM_NO_REMAP = ::NS(CTRL_PERFORM_NO_REMAP)
    }
    ctrl_perform_remap_flag_t;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_debugging_t
        ARCH_DEBUGGING_REGISTER_EMPTY = static_cast< arch_debugging_t >( 0 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_debugging_t
        ARCH_DEBUGGING_MIN_FLAG = static_cast< arch_debugging_t >(
            SIXTRL_ARCH_DEBUGGING_MIN_FLAG );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_debugging_t
        ARCH_DEBUGGING_MAX_FLAG = static_cast< arch_debugging_t >(
            SIXTRL_ARCH_DEBUGGING_MAX_FLAG );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_debugging_t
        ARCH_DEBUGGING_STATUS_BITMASK = static_cast< arch_debugging_t >(
            SIXTRL_ARCH_DEBUGGING_STATUS_BITMASK );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_debugging_t
        ARCH_DEBUGGING_STATUS_MAX_FLAG = static_cast< arch_debugging_t >(
            SIXTRL_ARCH_DEBUGGING_STATUS_MAX_FLAG );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_debugging_t
        ARCH_DEBUGGING_GENERAL_FAILURE = static_cast< arch_debugging_t >(
            SIXTRL_ARCH_DEBUGGING_GENERAL_FAILURE );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_kernel_id_t
        ARCH_ILLEGAL_KERNEL_ID = static_cast< arch_kernel_id_t >( 0xFFFFFFFF );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_kernel_id_t
        ARCH_ILLEGAL_KERNEL_CONFIG_ID =
            static_cast< arch_kernel_id_t >( 0xFFFFFFFF );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_set_id_t
        ARCH_ILLEGAL_KERNEL_SET_ID =
            static_cast< kernel_set_id_t >( 0xFFFFFFFF );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_variant_flags_t
        ARCH_VARIANT_NONE = static_cast< arch_variant_flags_t >( 0 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_variant_flags_t
        ARCH_VARIANT_DEBUG = static_cast< arch_variant_flags_t >(
            0x8000000000000000 );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t
        KERNEL_CONFIG_PURPOSE_REMAP_BUFFER =
            static_cast< kernel_purpose_t >( 0 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t
        KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES  =
            static_cast< kernel_purpose_t >( 1 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t
        KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN =
            static_cast< kernel_purpose_t >( 2 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t
        KERNEL_CONFIG_PURPOSE_TRACK_ELEM_BY_ELEM =
            static_cast< kernel_purpose_t >( 3 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t
        KERNEL_CONFIG_PURPOSE_TRACK_LINE =
            static_cast< kernel_purpose_t >( 4 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t
        KERNEL_CONFIG_PURPOSE_ASSIGN_BEAM_MONITOR_OUTPUT =
            static_cast< kernel_purpose_t >( 5 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t
        KERNEL_CONFIG_PURPOSE_ASSIGN_ELEM_BY_ELEM_OUTPUT =
             static_cast< kernel_purpose_t >( 6 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t
        KERNEL_CONFIG_PURPOSE_MAX_PREDEFINED_ID =
            KERNEL_CONFIG_PURPOSE_ASSIGN_ELEM_BY_ELEM_OUTPUT;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t
        KERNEL_CONFIG_PURPOSE_MAX_RESERVED =
            static_cast< kernel_purpose_t >( 1022 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t
        KERNEL_CONFIG_PURPOSE_UNSPECIFIED =
            static_cast< kernel_purpose_t >( 1023 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t
        KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID =
            static_cast< kernel_purpose_t >( 1024 );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_set_id_t
        NODE_ILLEGAL_NODE_SET_ID = static_cast< node_set_id_t >( 0xFFFFFFFF );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_platform_id_t
        NODE_ILLEGAL_PLATFORM_ID = static_cast< node_platform_id_t >( -1 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_device_id_t
        NODE_ILLEGAL_DEVICE_ID = static_cast< node_device_id_t >( -1 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_index_t
        NODE_UNDEFINED_INDEX = static_cast< node_index_t >( 0xFFFFFFFF );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_id_str_fmt_t
        NODE_ID_STR_FORMAT_NOARCH = static_cast< node_id_str_fmt_t >(
            SIXTRL_NODE_ID_STR_FORMAT_NOARCH );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_id_str_fmt_t
        NODE_ID_STR_FORMAT_ARCHID = static_cast< node_id_str_fmt_t >(
            SIXTRL_NODE_ID_STR_FORMAT_ARCHID );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_id_str_fmt_t
        NODE_ID_STR_FORMAT_ARCHSTR = static_cast< node_id_str_fmt_t >(
            SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_id_str_fmt_t
        NODE_ID_STR_FORMAT_ILLEGAL = static_cast< node_id_str_fmt_t >(
            SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_id_str_fmt_t
        NODE_ID_STR_FORMAT_DEFAULT = static_cast< node_id_str_fmt_t >(
            SIXTRL_NODE_ID_STR_FORMAT_DEFAULT );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_str_role_t
        NODE_STR_ROLE_ID = static_cast< node_str_role_t >( 0u );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_str_role_t
        NODE_STR_ROLE_UNIQUE_ID = static_cast< node_str_role_t >( 1u );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_argument_set_t
        DEFAULT_KERNEL_ARGUMENT_SET = static_cast< kernel_argument_set_t >( 0u );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_set_id_t
        ILLEGAL_KERNEL_SET_ID = static_cast< kernel_set_id_t >( 0xFFFFFFFF );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_op_flags_t
        KERNEL_OP_FLAGS_NONE = static_cast< kernel_op_flags_t >( 0x00 );


    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_op_flags_t
        KERNEL_OP_CTRL_HAS_REQUIRED_PURPOSES =
            static_cast< kernel_op_flags_t >( 0x0001 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_op_flags_t
        KERNEL_OP_CTRL_KERNELS_AVAILABLE =
            static_cast< kernel_op_flags_t >( 0x0002 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_op_flags_t
        KERNEL_OP_CTRL_KERNELS_READY =
            static_cast< kernel_op_flags_t >( 0x0004 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_op_flags_t
        KERNEL_OP_CTRL_READY_TO_SEND =
            static_cast< kernel_op_flags_t >( 0x0008 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_op_flags_t
        KERNEL_OP_CTRL_READY_TO_RECEIVE =
            static_cast< kernel_op_flags_t >( 0x0010 );


    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_op_flags_t
        KERNEL_OP_TRACK_JOB_HAS_REQUIRED_PURPOSES =
            static_cast< kernel_op_flags_t >( 0x0100 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_op_flags_t
        KERNEL_OP_TRACK_JOB_KERNELS_AVAILABLE =
            static_cast< kernel_op_flags_t >( 0x0200 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_op_flags_t
        KERNEL_OP_TRACK_JOB_KERNELS_READY =
            static_cast< kernel_op_flags_t >( 0x0400 );


    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_op_flags_t
        KERNEL_OP_HAS_ALL_REQUIRED_PURPOSES =
            static_cast< kernel_op_flags_t >( 0x00010000 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_op_flags_t
        KERNEL_OP_ALL_REQUIRED_KERNELS_AVAILABLE =
            static_cast< kernel_op_flags_t >( 0x00020000 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST kernel_op_flags_t
        KERNEL_OP_ALL_REQUIRED_KERNELS_READY =
            static_cast< kernel_op_flags_t >( 0x00040000 );

    /* --------------------------------------------------------------------- */
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_DEFINITIONS_H__ */

/* end: sixtracklib/common/control/definitions.h */
