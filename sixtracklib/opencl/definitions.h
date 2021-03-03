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

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(derived_class_id_type) const NS(OPENCL_NODE_INFO_CLASS_ID)
    = ( NS(derived_class_id_type) )SIXTRL_OPENCL_NODE_INFO_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) const NS(OPENCL_CONTROLLER_CLASS_ID)
    = ( NS(derived_class_id_type) )SIXTRL_OPENCL_CONTROLLER_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) const NS(OPENCL_ARGUMENT_CLASS_ID)
    = ( NS(derived_class_id_type) )SIXTRL_OPENCL_ARGUMENT_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) const
    NS(OPENCL_RTC_PROGRAM_ITEM_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_RTC_PROGRAM_ITEM_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) const
    NS(OPENCL_PROGRAM_STORE_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_PROGRAM_STORE_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) const
    NS(OPENCL_COMMAND_QUEUE_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_COMMAND_QUEUE_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) const
    NS(OPENCL_CONTEXT_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_CONTEXT_CLASS_ID;

SIXTRL_STATIC_VAR NS(derived_class_id_type) const
    NS(OPENCL_CONTEXT_STORE_CLASS_ID) = ( NS(derived_class_id_type)
        )SIXTRL_OPENCL_CONTEXT_STORE_CLASS_ID;

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    static constexpr derived_class_id_type OPENCL_NODE_INFO_CLASS_ID =
        derived_class_id_type{ SIXTRL_OPENCL_NODE_INFO_CLASS_ID };

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

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_OPENCL_DEFINITIONS_H__ */
