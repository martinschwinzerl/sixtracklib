#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_ID_H__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_ID_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_id.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_ARGPTR_DEC NS(NodeId)*
NS(NodeId_create)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_delete)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_ARGPTR_DEC NS(NodeId)*
NS(NodeId_new)( NS(node_platform_id_t) const platform_id,
                NS(node_device_id_t) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_ARGPTR_DEC NS(NodeId)*
NS(NodeId_new_from_string)( char const* SIXTRL_RESTRICT node_id_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_ARGPTR_DEC NS(NodeId)*
NS(NodeId_preset)( SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeId_is_valid)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_platform_id_t) NS(NodeId_get_platform_id)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_device_id_t) NS(NodeId_get_device_id)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_set_platform_id)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_platform_id_t) const platform_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_set_device_id)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_device_id_t) const device_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_clear)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeId_has_controllers)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(NodeId_get_num_of_controllers)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeId_is_attached_to_controller)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeId_has_node_index)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t) NS(NodeId_get_node_index)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeId_set_node_index)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeId_is_selected)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeId_is_selected_by_controller)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ControllerBase) const*
NS(NodeId_get_const_selecting_controller)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeId_set_selected_controller)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_unselect_controller)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeId_attach_to_controller)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeId_detach_from_controller)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ControllerBase) const*
NS(NodeId_get_const_controller)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(arch_size_t) const num_of_controller_in_sequence );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeId_from_node_id_str)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    char const* SIXTRL_RESTRICT node_id_str );


SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeId_to_node_id_str)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(arch_size_t) const output_str_capacity,
    char* SIXTRL_RESTRICT output_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_print)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    FILE* SIXTRL_RESTRICT fp );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_print_out)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(NodeId_required_str_capacity)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeId_to_string)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(arch_size_t) const output_str_capacity,
    char* SIXTRL_RESTRICT output_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(NodeId_compare)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeId_are_equal)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ctrl_status_t)
NS(NodeId_extract_node_id_str_from_config_str)(
    char const* SIXTRL_RESTRICT config_str, char* SIXTRL_RESTRICT node_id_str,
    NS(buffer_size_t) const max_node_id_str_len );

#endif /* !defined( _GPUCODE )  */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_ID_H__ */

/* end: sixtracklib/common/control/node_id.h */
