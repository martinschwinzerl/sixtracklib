#ifndef SIXTRACKLIB_COMMON_CONTROL_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_CONTROL_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/backends/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES )  */

#if !defined( SIXTRL_NODE_PLATFORM_ID_ILLEGAL )
    #define SIXTRL_NODE_PLATFORM_ID_ILLEGAL -1
#endif /* !defined( SIXTRL_NODE_PLATFORM_ID_ILLEGAL ) */

#if !defined( SIXTRL_NODE_DEVICE_ID_ILLEGAL )
    #define SIXTRL_NODE_DEVICE_ID_ILLEGAL -1
#endif /* !defined( SIXTRL_NODE_DEVICE_ID_ILLEGAL ) */

#if !defined( SIXTRL_NODE_INDEX_ILLEGAL )
    #define SIXTRL_NODE_INDEX_ILLEGAL -1
#endif /* !defined( SIXTRL_NODE_INDEX_ILLEGAL ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( SIXTRL_NODE_INFO_BASE_CLASS_ID )
    #define SIXTRL_NODE_INFO_BASE_CLASS_ID 100
#endif /* !defined( SIXTRL_NODE_INFO_BASE_CLASS_ID ) */

#if !defined( SIXTRL_CONTROLLER_BASE_CLASS_ID )
    #define SIXTRL_CONTROLLER_BASE_CLASS_ID 101
#endif /* !defined( SIXTRL_CONTROLLER_BASE_CLASS_ID ) */

#if !defined( SIXTRL_ARGUMENT_BASE_CLASS_ID )
    #define SIXTRL_ARGUMENT_BASE_CLASS_ID 102
#endif /* !defined( SIXTRL_ARGUMENT_BASE_CLASS_ID ) */

#if !defined( SIXTRL_PROGRAM_ITEM_BASE_CLASS_ID )
    #define SIXTRL_PROGRAM_ITEM_BASE_CLASS_ID 103
#endif /* !defined( SIXTRL_PROGRAM_ITEM_BASE_CLASS_ID ) */

#if !defined( SIXTRL_PROGRAM_STORE_BASE_CLASS_ID )
    #define SIXTRL_PROGRAM_STORE_BASE_CLASS_ID 105
#endif /* !defined( SIXTRL_PROGRAM_STORE_BASE_CLASS_ID ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_MINIMAL)
    #define SIXTRL_NODE_ID_STR_FORMAT_MINIMAL 0
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_MINIMAL) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_BACKEND_ID)
    #define SIXTRL_NODE_ID_STR_FORMAT_BACKEND_ID 1
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_BACKEND_ID) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_BACKEND_STR)
    #define SIXTRL_NODE_ID_STR_FORMAT_BACKEND_STR 2
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_BACKEND_STR) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_DEFAULT)
    #define SIXTRL_NODE_ID_STR_FORMAT_DEFAULT 0
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_DEFAULT) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_AUTO)
    #define SIXTRL_NODE_ID_STR_FORMAT_AUTO 3
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_AUTO ) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL)
    #define SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL 0xffff
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( SIXTRL_CONTROLLER_PROGRAM_ID_ILLEGAL )
    #define SIXTRL_CONTROLLER_PROGRAM_ID_ILLEGAL -1
#endif /* !defined( SIXTRL_CONTROLLER_PROGRAM_ID_ILLEGAL ) */

#if !defined( SIXTRL_CONTROLLER_KERNEL_ID_ILLEGAL )
    #define SIXTRL_CONTROLLER_KERNEL_ID_ILLEGAL -1
#endif /* !defined( SIXTRL_CONTROLLER_KERNEL_ID_ILLEGAL ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( SIXTRL_ARGUMENT_HOLDS_CBUFFER )
    #define SIXTRL_ARGUMENT_HOLDS_CBUFFER 0
#endif /* !defined( SIXTRL_ARGUMENT_HOLDS_CBUFFER ) */

#if !defined( SIXTRL_ARGUMENT_HOLDS_VALUE )
    #define SIXTRL_ARGUMENT_HOLDS_VALUE 1
#endif /* !defined( SIXTRL_ARGUMENT_HOLDS_VALUE ) */

#if !defined( SIXTRL_ARGUMENT_HOLDS_WEAK_POINTER )
    #define SIXTRL_ARGUMENT_HOLDS_WEAK_POINTER 2
#endif /* !defined( SIXTRL_ARGUMENT_HOLDS_WEAK_POINTER ) */

#if !defined( SIXTRL_ARGUMENT_HOLDS_POINTER )
    #define SIXTRL_ARGUMENT_HOLDS_POINTER 3
#endif /* !defined( SIXTRL_ARGUMENT_HOLDS_POINTER ) */

#if !defined( SIXTRL_ARGUMENT_HOLDS_NONE )
    #define SIXTRL_ARGUMENT_HOLDS_NONE 4
#endif /* !defined( SIXTRL_ARGUMENT_HOLDS_NONE ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( SIXTRL_ARGUMENT_MAPS_TO_DEFAULT )
    #define SIXTRL_ARGUMENT_MAPS_TO_DEFAULT 0
#endif /* !defined( SIXTRL_ARGUMENT_MAPS_TO_DEFAULT ) */

#if !defined( SIXTRL_ARGUMENT_MAPS_TO_NONE )
    #define SIXTRL_ARGUMENT_MAPS_TO_NONE 5
#endif /* !defined( SIXTRL_ARGUMENT_MAPS_TO_NONE ) */

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

typedef SIXTRL_INT64_TYPE  NS(node_platform_id_type);
typedef SIXTRL_INT64_TYPE  NS(node_device_id_type);
typedef SIXTRL_INT64_TYPE  NS(node_index_type);
typedef SIXTRL_UINT16_TYPE NS(node_id_str_fmt_type);

typedef SIXTRL_INT64_TYPE  NS(ctrl_program_id_type);
typedef SIXTRL_INT64_TYPE  NS(ctrl_kernel_id_type);

typedef SIXTRL_UINT64_TYPE NS(ctrl_arg_hold_id_type);
typedef SIXTRL_UINT64_TYPE NS(ctrl_arg_mapsto_id_type);

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(node_platform_id_type) const NS(NODE_PLATFORM_ID_ILLEGAL) =
    ( NS(node_platform_id_type) )SIXTRL_NODE_PLATFORM_ID_ILLEGAL;

SIXTRL_STATIC_VAR NS(node_device_id_type) const NS(NODE_DEVICE_ID_ILLEGAL) =
    ( NS(node_platform_id_type) )SIXTRL_NODE_PLATFORM_ID_ILLEGAL;

SIXTRL_STATIC_VAR NS(node_index_type) const NS(NODE_INDEX_ILLEGAL) =
    ( NS(node_index_type) )SIXTRL_NODE_INDEX_ILLEGAL;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(node_id_str_fmt_type) const
NS(NODE_ID_STR_FORMAT_MINIMAL) = ( NS(node_id_str_fmt_type)
    )SIXTRL_NODE_ID_STR_FORMAT_MINIMAL;

SIXTRL_STATIC_VAR NS(node_id_str_fmt_type) const
NS(NODE_ID_STR_FORMAT_BACKEND_ID) = ( NS(node_id_str_fmt_type)
    )SIXTRL_NODE_ID_STR_FORMAT_BACKEND_ID;

SIXTRL_STATIC_VAR NS(node_id_str_fmt_type) const
NS(NODE_ID_STR_FORMAT_BACKEND_STR) = ( NS(node_id_str_fmt_type)
    )SIXTRL_NODE_ID_STR_FORMAT_BACKEND_STR;

SIXTRL_STATIC_VAR NS(node_id_str_fmt_type) const
NS(NODE_ID_STR_FORMAT_DEFAULT) = ( NS(node_id_str_fmt_type)
    )SIXTRL_NODE_ID_STR_FORMAT_DEFAULT;

SIXTRL_STATIC_VAR NS(node_id_str_fmt_type) const
NS(NODE_ID_STR_FORMAT_AUTO) = ( NS(node_id_str_fmt_type)
    )SIXTRL_NODE_ID_STR_FORMAT_AUTO;

SIXTRL_STATIC_VAR NS(node_id_str_fmt_type) const
NS(NODE_ID_STR_FORMAT_ILLEGAL) = ( NS(node_id_str_fmt_type)
    )SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(ctrl_program_id_type) const
    NS(CONTROLLER_PROGRAM_ID_ILLEGAL) = ( NS(ctrl_program_id_type)
        )SIXTRL_CONTROLLER_PROGRAM_ID_ILLEGAL;

SIXTRL_STATIC_VAR NS(ctrl_program_id_type) const
    NS(CONTROLLER_KERNEL_ID_ILLEGAL) = ( NS(ctrl_kernel_id_type)
        )SIXTRL_CONTROLLER_KERNEL_ID_ILLEGAL;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(ctrl_arg_hold_id_type) const NS(ARGUMENT_HOLDS_NONE) = (
    NS(ctrl_arg_hold_id_type) )SIXTRL_ARGUMENT_HOLDS_NONE;

SIXTRL_STATIC_VAR NS(ctrl_arg_hold_id_type) const NS(ARGUMENT_HOLDS_VALUE) = (
    NS(ctrl_arg_hold_id_type) )SIXTRL_ARGUMENT_HOLDS_VALUE;

SIXTRL_STATIC_VAR NS(ctrl_arg_hold_id_type) const
NS(SIXTRL_ARGUMENT_HOLDS_WEAK_POINTER) = ( NS(ctrl_arg_hold_id_type)
    )SIXTRL_ARGUMENT_HOLDS_WEAK_POINTER;

SIXTRL_STATIC_VAR NS(ctrl_arg_hold_id_type) const
NS(SIXTRL_ARGUMENT_HOLDS_POINTER) = ( NS(ctrl_arg_hold_id_type)
    )SIXTRL_ARGUMENT_HOLDS_POINTER;

SIXTRL_STATIC_VAR NS(ctrl_arg_hold_id_type) const
NS(SIXTRL_ARGUMENT_HOLDS_CBUFFER) = ( NS(ctrl_arg_hold_id_type)
    )SIXTRL_ARGUMENT_HOLDS_CBUFFER;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(ctrl_arg_mapsto_id_type) const NS(ARGUMENT_MAPS_TO_DEFAULT)
    = ( NS(ctrl_arg_mapsto_id_type) )SIXTRL_ARGUMENT_MAPS_TO_DEFAULT;

SIXTRL_STATIC_VAR NS(ctrl_arg_mapsto_id_type) const NS(ARGUMENT_MAPS_TO_NONE) =
    ( NS(ctrl_arg_mapsto_id_type) )SIXTRL_ARGUMENT_MAPS_TO_NONE;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(derived_class_id_type) const NS(NODE_INFO_BASE_CLASS_ID) =
    ( NS(derived_class_id_type) )SIXTRL_NODE_INFO_BASE_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) const NS(CONTROLLER_BASE_CLASS_ID) =
    ( NS(derived_class_id_type) )SIXTRL_CONTROLLER_BASE_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) const NS(ARGUMENT_BASE_CLASS_ID) =
    ( NS(derived_class_id_type) )SIXTRL_ARGUMENT_BASE_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) const NS(PROGRAM_ITEM_BASE_CLASS_ID)
    = ( NS(derived_class_id_type) )SIXTRL_PROGRAM_ITEM_BASE_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) const NS(PROGRAM_STORE_BASE_CLASS_ID)
    = ( NS(derived_class_id_type) )SIXTRL_PROGRAM_STORE_BASE_CLASS_ID;

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(node_platform_id_type)   node_platform_id_type;
    typedef ::NS(node_device_id_type)     node_device_id_type;
    typedef ::NS(node_id_str_fmt_type)    node_id_str_fmt_type;
    typedef ::NS(node_index_type)         node_index_type;

    typedef ::NS(ctrl_arg_hold_id_type)   ctrl_arg_hold_id_type;
    typedef ::NS(ctrl_arg_mapsto_id_type) ctrl_arg_mapsto_id_type;

    typedef ::NS(ctrl_program_id_type)    ctrl_program_id_type;
    typedef ::NS(ctrl_kernel_id_type)     ctrl_kernel_id_type;

    #if !defined( _GPUCODE )

    static constexpr node_platform_id_type NODE_PLATFORM_ID_ILLEGAL =
        node_platform_id_type{ SIXTRL_NODE_PLATFORM_ID_ILLEGAL };

    static constexpr node_platform_id_type NODE_DEVICE_ID_ILLEGAL =
        node_platform_id_type{ SIXTRL_NODE_DEVICE_ID_ILLEGAL };

    static constexpr node_index_type NODE_INDEX_ILLEGAL =
        node_index_type{ SIXTRL_NODE_INDEX_ILLEGAL };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    static constexpr node_id_str_fmt_type NODE_ID_STR_FORMAT_MINIMAL =
        node_id_str_fmt_type{ SIXTRL_NODE_ID_STR_FORMAT_MINIMAL };

    static constexpr node_id_str_fmt_type NODE_ID_STR_FORMAT_BACKEND_ID =
        node_id_str_fmt_type{ SIXTRL_NODE_ID_STR_FORMAT_BACKEND_ID };

    static constexpr node_id_str_fmt_type NODE_ID_STR_FORMAT_BACKEND_STR =
        node_id_str_fmt_type{ SIXTRL_NODE_ID_STR_FORMAT_BACKEND_STR };

    static constexpr node_id_str_fmt_type NODE_ID_STR_FORMAT_DEFAULT =
        node_id_str_fmt_type{ SIXTRL_NODE_ID_STR_FORMAT_DEFAULT };

    static constexpr node_id_str_fmt_type NODE_ID_STR_FORMAT_AUTO =
        node_id_str_fmt_type{ SIXTRL_NODE_ID_STR_FORMAT_AUTO };

    static constexpr node_id_str_fmt_type NODE_ID_STR_FORMAT_ILLEGAL =
        node_id_str_fmt_type{ SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    static constexpr ctrl_program_id_type CONTROLLER_PROGRAM_ID_ILLEGAL =
        ctrl_program_id_type{ SIXTRL_CONTROLLER_PROGRAM_ID_ILLEGAL };

    static constexpr ctrl_program_id_type CONTROLLER_KERNEL_ID_ILLEGAL =
        ctrl_program_id_type{ SIXTRL_CONTROLLER_KERNEL_ID_ILLEGAL };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    static constexpr ctrl_arg_hold_id_type ARGUMENT_HOLDS_NONE =
        ctrl_arg_hold_id_type{ SIXTRL_ARGUMENT_HOLDS_NONE };

    static constexpr ctrl_arg_hold_id_type ARGUMENT_HOLDS_VALUE =
        ctrl_arg_hold_id_type{ SIXTRL_ARGUMENT_HOLDS_VALUE };

    static constexpr ctrl_arg_hold_id_type ARGUMENT_HOLDS_WEAK_POINTER =
        ctrl_arg_hold_id_type{ SIXTRL_ARGUMENT_HOLDS_WEAK_POINTER };

    static constexpr ctrl_arg_hold_id_type ARGUMENT_HOLDS_POINTER =
        ctrl_arg_hold_id_type{ SIXTRL_ARGUMENT_HOLDS_POINTER };

    static constexpr ctrl_arg_hold_id_type ARGUMENT_HOLDS_CBUFFER =
        ctrl_arg_hold_id_type{ SIXTRL_ARGUMENT_HOLDS_CBUFFER };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    static constexpr ctrl_arg_mapsto_id_type ARGUMENT_MAPS_TO_DEFAULT =
        ctrl_arg_mapsto_id_type{ SIXTRL_ARGUMENT_MAPS_TO_DEFAULT };

    static constexpr ctrl_arg_mapsto_id_type ARGUMENT_MAPS_TO_NONE =
        ctrl_arg_mapsto_id_type{ SIXTRL_ARGUMENT_MAPS_TO_NONE };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    static constexpr derived_class_id_type NODE_INFO_BASE_CLASS_ID =
        derived_class_id_type{ SIXTRL_NODE_INFO_BASE_CLASS_ID };

    static constexpr derived_class_id_type CONTROLLER_BASE_CLASS_ID =
        derived_class_id_type{ SIXTRL_CONTROLLER_BASE_CLASS_ID };

    static constexpr derived_class_id_type ARGUMENT_BASE_CLASS_ID =
        derived_class_id_type{ SIXTRL_ARGUMENT_BASE_CLASS_ID };

    static constexpr derived_class_id_type PROGRAM_ITEM_BASE_CLASS_ID =
        derived_class_id_type{ SIXTRL_PROGRAM_ITEM_BASE_CLASS_ID };

    static constexpr derived_class_id_type PROGRAM_STORE_BASE_CLASS_ID =
        derived_class_id_type{ SIXTRL_PROGRAM_STORE_BASE_CLASS_ID };

    #endif /* !defined( _GPUCODE ) */
} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* C++ */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_CONTROL_DEFINITIONS_H__ */
