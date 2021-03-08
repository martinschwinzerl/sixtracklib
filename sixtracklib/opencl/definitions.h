#ifndef SIXTRACKLIB_OPENCL_DEFINITIONS_H__
#define SIXTRACKLIB_OPENCL_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/backends/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_OPENCL_NODE_INFO_CLASS_ID )
    #define SIXTRL_OPENCL_NODE_INFO_CLASS_ID 201
#endif /* !defined( SIXTRL_OPENCL_NODE_INFO_CLASS_ID ) */

#if !defined( SIXTRL_OPENCL_NODE_STORE_CLASS_ID )
    #define SIXTRL_OPENCL_NODE_STORE_CLASS_ID 212
#endif /* !defined( SIXTRL_OPENCL_NODE_STORE_CLASS_ID ) */

#if !defined( SIXTRL_OPENCL_CONTROLLER_CLASS_ID )
    #define SIXTRL_OPENCL_CONTROLLER_CLASS_ID 202
#endif /* !defined( SIXTRL_OPENCL_CONTROLLER_CLASS_ID ) */

#if !defined( SIXTRL_OPENCL_ARGUMENT_CLASS_ID )
    #define SIXTRL_OPENCL_ARGUMENT_CLASS_ID 203
#endif /* !defined( SIXTRL_OPENCL_ARGUMENT_CLASS_ID ) */

#if !defined( SIXTRL_OPENCL_RTC_PROGRAM_ITEM_CLASS_ID )
    #define SIXTRL_OPENCL_RTC_PROGRAM_ITEM_CLASS_ID 204
#endif /* !defined( SIXTRL_OPENCL_RTC_PROGRAM_ITEM_CLASS_ID ) */

#if !defined( SIXTRL_OPENCL_PROGRAM_STORE_CLASS_ID )
    #define SIXTRL_OPENCL_PROGRAM_STORE_CLASS_ID 205
#endif /* !defined( SIXTRL_OPENCL_PROGRAM_STORE_CLASS_ID ) */

#if !defined( SIXTRL_OPENCL_COMMAND_QUEUE_CLASS_ID )
    #define SIXTRL_OPENCL_COMMAND_QUEUE_CLASS_ID 206
#endif /* !defined( SIXTRL_OPENCL_COMMAND_QUEUE_CLASS_ID ) */

#if !defined( SIXTRL_OPENCL_CONTEXT_CLASS_ID )
    #define SIXTRL_OPENCL_CONTEXT_CLASS_ID 207
#endif /* !defined( SIXTRL_OPENCL_CONTEXT_CLASS_ID ) */

#if !defined( SIXTRL_OPENCL_CONTEXT_STORE_CLASS_ID )
    #define SIXTRL_OPENCL_CONTEXT_STORE_CLASS_ID 208
#endif /* !defined( SIXTRL_OPENCL_CONTEXT_STORE_CLASS_ID ) */

#if !defined( SIXTRL_OPENCL_KERNEL_ITEM_CLASS_ID )
    #define SIXTRL_OPENCL_KERNEL_ITEM_CLASS_ID 209
#endif /* !defined( SIXTRL_OPENCL_KERNEL_ITEM_CLASS_ID ) */

#if !defined( SIXTRL_OPENCL_KERNEL_STORE_CLASS_ID )
    #define SIXTRL_OPENCL_KERNEL_STORE_CLASS_ID 210
#endif /* !defined( SIXTRL_OPENCL_KERNEL_STORE_CLASS_ID ) */

#if !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_CLASS_ID )
    #define SIXTRL_OPENCL_PROGRAM_CONFIG_CLASS_ID 211
#endif /* !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_CLASS_ID ) */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_OPENCL_CMD_QUEUE_NONE_FLAGS )
    #define SIXTRL_OPENCL_CMD_QUEUE_NONE_FLAGS 0x0000
#endif /* SIXTRL_OPENCL_CMD_QUEUE_NONE_FLAGS */

#if !defined( SIXTRL_OPENCL_CMD_QUEUE_SUPPORTS_PROFILING )
    #define SIXTRL_OPENCL_CMD_QUEUE_SUPPORTS_PROFILING 0x0001
#endif /* SIXTRL_OPENCL_CMD_QUEUE_SUPPORTS_PROFILING */

#if !defined( SIXTRL_OPENCL_CMD_QUEUE_SUPPORTS_OUT_OF_ORDER_EXEC )
    #define SIXTRL_OPENCL_CMD_QUEUE_SUPPORTS_OUT_OF_ORDER_EXEC 0x0002
#endif /* SIXTRL_OPENCL_CMD_QUEUE_SUPPORTS_OUT_OF_ORDER_EXEC */

#if !defined( SIXTRL_OPENCL_CMD_QUEUE_ON_DEVICE )
    #define SIXTRL_OPENCL_CMD_QUEUE_ON_DEVICE 0x0004
#endif /* SIXTRL_OPENCL_CMD_QUEUE_ON_DEVICE */

#if !defined( SIXTRL_OPENCL_CMD_QUEUE_DEFAULT_DEVICE_QUEUE )
    #define SIXTRL_OPENCL_CMD_QUEUE_DEFAULT_DEVICE_QUEUE 0x0008
#endif /* SIXTRL_OPENCL_CMD_QUEUE_DEFAULT_DEVICE_QUEUE */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_NOT_FOUND )
    #define SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_NOT_FOUND 0x0000
#endif /* !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_NOT_FOUND ) */

#if !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_EXACT )
    #define SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_EXACT 0x0001
#endif /* !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_EXACT ) */

#if !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_CONTEXT )
    #define SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_CONTEXT 0x0002
#endif /* !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_CONTEXT ) */

#if !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_PLATFORM )
    #define SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_PLATFORM 0x0003
#endif /* !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_PLATFORM ) */

#if !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_PROGRAM )
    #define SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_PROGRAM 0x0004
#endif /* !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_PROGRAM ) */

#if !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_GLOBAL )
    #define SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_GLOBAL 0x0005
#endif /* !defined( SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_GLOBAL ) */

/* ========================================================================= */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

typedef SIXTRL_UINT16_TYPE NS(ocl_cmd_queue_properties_type);
typedef SIXTRL_UINT16_TYPE NS(ocl_buffer_properties_type);
typedef SIXTRL_UINT16_TYPE NS(ocl_program_config_source_type);

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(derived_class_id_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_NODE_INFO_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_NODE_INFO_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_NODE_STORE_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_NODE_STORE_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_CONTROLLER_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_CONTROLLER_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_ARGUMENT_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_ARGUMENT_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_RTC_PROGRAM_ITEM_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_RTC_PROGRAM_ITEM_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_PROGRAM_STORE_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_PROGRAM_STORE_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_COMMAND_QUEUE_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_COMMAND_QUEUE_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_CONTEXT_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_CONTEXT_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_CONTEXT_STORE_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_CONTEXT_STORE_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_KERNEL_ITEM_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_KERNEL_ITEM_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_KERNEL_STORE_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_KERNEL_STORE_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_PROGRAM_CONFIG_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_PROGRAM_CONFIG_CLASS_ID;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR NS(ocl_cmd_queue_properties_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_CMD_QUEUE_NONE_FLAGS) = ( NS(ocl_cmd_queue_properties_type)
        )SIXTRL_OPENCL_CMD_QUEUE_NONE_FLAGS;

SIXTRL_STATIC_VAR NS(ocl_cmd_queue_properties_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_CMD_QUEUE_SUPPORTS_PROFILING) = ( NS(ocl_cmd_queue_properties_type)
        )SIXTRL_OPENCL_CMD_QUEUE_SUPPORTS_PROFILING;

SIXTRL_STATIC_VAR NS(ocl_cmd_queue_properties_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_CMD_QUEUE_SUPPORTS_OUT_OF_ORDER_EXEC) = (
        NS(ocl_cmd_queue_properties_type)
            )SIXTRL_OPENCL_CMD_QUEUE_SUPPORTS_OUT_OF_ORDER_EXEC;

SIXTRL_STATIC_VAR NS(ocl_cmd_queue_properties_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_CMD_QUEUE_ON_DEVICE) = ( NS(ocl_cmd_queue_properties_type)
        )SIXTRL_OPENCL_CMD_QUEUE_ON_DEVICE;

SIXTRL_STATIC_VAR NS(ocl_cmd_queue_properties_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_CMD_QUEUE_DEFAULT_DEVICE_QUEUE) = (
        NS(ocl_cmd_queue_properties_type)
            )SIXTRL_OPENCL_CMD_QUEUE_DEFAULT_DEVICE_QUEUE;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR NS(ocl_program_config_source_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_PROGRAM_CONFIG_SOURCE_NOT_FOUND) = (
        NS(ocl_program_config_source_type)
            )SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_NOT_FOUND;

SIXTRL_STATIC_VAR NS(ocl_program_config_source_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_PROGRAM_CONFIG_SOURCE_EXACT) = ( NS(ocl_program_config_source_type)
        )SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_EXACT;

SIXTRL_STATIC_VAR NS(ocl_program_config_source_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_PROGRAM_CONFIG_SOURCE_CONTEXT) = (
        NS(ocl_program_config_source_type)
            )SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_CONTEXT;

SIXTRL_STATIC_VAR NS(ocl_program_config_source_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_PROGRAM_CONFIG_SOURCE_PLATFORM) = (
        NS(ocl_program_config_source_type)
            )SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_PLATFORM;

SIXTRL_STATIC_VAR NS(ocl_program_config_source_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_PROGRAM_CONFIG_SOURCE_PROGRAM) = (
        NS(ocl_program_config_source_type)
            )SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_PROGRAM;

SIXTRL_STATIC_VAR NS(ocl_program_config_source_type) SIXTRL_CONSTEXPR_OR_CONST
    NS(OPENCL_PROGRAM_CONFIG_SOURCE_GLOBAL) = (
        NS(ocl_program_config_source_type)
            )SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_GLOBAL;

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(ocl_cmd_queue_properties_type)  ocl_cmd_queue_properties_type;
    typedef ::NS(ocl_buffer_properties_type)     ocl_buffer_properties_type;
    typedef ::NS(ocl_program_config_source_type) ocl_program_config_source_type;

    static constexpr derived_class_id_type OPENCL_NODE_INFO_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_NODE_INFO_CLASS_ID };

    static constexpr derived_class_id_type OPENCL_NODE_STORE_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_NODE_STORE_CLASS_ID };

    static constexpr derived_class_id_type OPENCL_CONTROLLER_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_CONTROLLER_CLASS_ID };

    static constexpr derived_class_id_type OPENCL_ARGUMENT_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_ARGUMENT_CLASS_ID };

    static constexpr derived_class_id_type OPENCL_RTC_PROGRAM_ITEM_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_RTC_PROGRAM_ITEM_CLASS_ID };

    static constexpr derived_class_id_type OPENCL_PROGRAM_STORE_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_PROGRAM_STORE_CLASS_ID };

    static constexpr derived_class_id_type OPENCL_COMMAND_QUEUE_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_COMMAND_QUEUE_CLASS_ID };

    static constexpr derived_class_id_type OPENCL_CONTEXT_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_CONTEXT_CLASS_ID };

    static constexpr derived_class_id_type OPENCL_CONTEXT_STORE_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_CONTEXT_STORE_CLASS_ID };

    static constexpr derived_class_id_type OPENCL_KERNEL_ITEM_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_KERNEL_ITEM_CLASS_ID};

    static constexpr derived_class_id_type OPENCL_KERNEL_STORE_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_KERNEL_STORE_CLASS_ID };

    static constexpr derived_class_id_type OPENCL_PROGRAM_CONFIG_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_PROGRAM_CONFIG_CLASS_ID };

    /* ------------------------------------------------------------------------- */

    static constexpr ocl_cmd_queue_properties_type
        OPENCL_CMD_QUEUE_NONE_FLAGS = ocl_cmd_queue_properties_type{
                SIXTRL_OPENCL_CMD_QUEUE_NONE_FLAGS };

    static constexpr ocl_cmd_queue_properties_type
        OPENCL_CMD_QUEUE_SUPPORTS_PROFILING = ocl_cmd_queue_properties_type{
            SIXTRL_OPENCL_CMD_QUEUE_SUPPORTS_PROFILING };

    static constexpr ocl_cmd_queue_properties_type
        OPENCL_CMD_QUEUE_SUPPORTS_OUT_OF_ORDER_EXEC =
            ocl_cmd_queue_properties_type{
                SIXTRL_OPENCL_CMD_QUEUE_SUPPORTS_OUT_OF_ORDER_EXEC };

    static constexpr ocl_cmd_queue_properties_type OPENCL_CMD_QUEUE_ON_DEVICE =
        ocl_cmd_queue_properties_type{ SIXTRL_OPENCL_CMD_QUEUE_ON_DEVICE };

    static constexpr ocl_cmd_queue_properties_type
        OPENCL_CMD_QUEUE_DEFAULT_DEVICE_QUEUE = ocl_cmd_queue_properties_type{
            SIXTRL_OPENCL_CMD_QUEUE_DEFAULT_DEVICE_QUEUE };


    /* --------------------------------------------------------------------- */

    static constexpr ocl_program_config_source_type
        OPENCL_PROGRAM_CONFIG_SOURCE_NOT_FOUND = ocl_program_config_source_type{
            SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_NOT_FOUND };

    static constexpr ocl_program_config_source_type
        OPENCL_PROGRAM_CONFIG_SOURCE_EXACT = ocl_program_config_source_type{
            SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_EXACT };

    static constexpr ocl_program_config_source_type
        OPENCL_PROGRAM_CONFIG_SOURCE_CONTEXT = ocl_program_config_source_type{
            SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_CONTEXT };

    static constexpr ocl_program_config_source_type
        OPENCL_PROGRAM_CONFIG_SOURCE_PLATFORM = ocl_program_config_source_type{
            SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_PLATFORM };

    static constexpr ocl_program_config_source_type
        OPENCL_PROGRAM_CONFIG_SOURCE_PROGRAM = ocl_program_config_source_type{
            SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_PROGRAM };

    static constexpr ocl_program_config_source_type
        OPENCL_PROGRAM_CONFIG_SOURCE_GLOBAL = ocl_program_config_source_type{
            SIXTRL_OPENCL_PROGRAM_CONFIG_SOURCE_GLOBAL };


} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_OPENCL_DEFINITIONS_H__ */
