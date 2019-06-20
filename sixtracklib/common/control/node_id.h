#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_ID_H__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_ID_H__

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

typedef struct NS(NodeId)
{
    NS(node_platform_id_t) platform_id   SIXTRL_ALIGN( 8 );
    NS(node_device_id_t)   device_id     SIXTRL_ALIGN( 8 );
}
NS(NodeId);

SIXTRL_STATIC SIXTRL_FN SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_preset)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(NodeId_init)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT ptr_node_id,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

SIXTRL_STATIC SIXTRL_FN bool NS(NodeId_is_valid)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_STATIC SIXTRL_FN NS(node_platform_id_t) NS(NodeId_get_platform_id)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_STATIC SIXTRL_FN NS(node_device_id_t) NS(NodeId_get_device_id)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(NodeId_set_platform_id)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_platform_id_t) const platform_id );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(NodeId_set_device_id)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_device_id_t) const device_id );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(NodeId_get_required_num_slots_on_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT data_begin,
    NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(NodeId_get_required_num_dataptrs_on_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT data_begin,
    NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN void NS(NodeId_clear)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node );

SIXTRL_STATIC SIXTRL_FN NS(arch_size_t) NS(NodeId_required_str_capacity)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_STATIC SIXTRL_FN int NS(NodeId_compare)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs );

SIXTRL_STATIC SIXTRL_FN bool NS(NodeId_are_equal)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(NodeId_copy)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT destination,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT source );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_preset_ext)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN  NS(arch_status_t) NS(NodeId_init_ext)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT ptr_node_id,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN  bool NS(NodeId_is_valid_ext)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN  NS(node_platform_id_t)
NS(NodeId_get_platform_id_ext)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN  NS(node_device_id_t)
NS(NodeId_get_device_id_ext)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN  NS(arch_status_t)
NS(NodeId_set_platform_id_ext)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_platform_id_t) const platform_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeId_set_device_id_ext)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_device_id_t) const device_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN  void NS(NodeId_clear_ext)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN  NS(arch_size_t)
NS(NodeId_required_str_capacity_ext)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN  int NS(NodeId_compare_ext)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs );

SIXTRL_EXTERN SIXTRL_HOST_FN  bool NS(NodeId_are_equal_ext)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs );

SIXTRL_EXTERN SIXTRL_HOST_FN  NS(arch_status_t) NS(NodeId_copy_ext)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT destination,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT source );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeId_init_from_string)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT ptr_node_id,
    char const* SIXTRL_RESTRICT node_id_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_DATAPTR_DEC NS(NodeId)*
NS(NodeId_create)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_delete)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_DATAPTR_DEC NS(NodeId)*
NS(NodeId_new)( NS(node_platform_id_t) const platform_id,
                NS(node_device_id_t) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_DATAPTR_DEC NS(NodeId)*
NS(NodeId_new_from_string)( char const* SIXTRL_RESTRICT node_id_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeId_from_node_id_str)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    char const* SIXTRL_RESTRICT node_id_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeId_to_node_id_str)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(arch_size_t) const output_str_capacity,
    char* SIXTRL_RESTRICT output_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_print)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    FILE* SIXTRL_RESTRICT fp );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeId_extract_node_id_str_from_config_str)(
    char const* SIXTRL_RESTRICT config_str, char* SIXTRL_RESTRICT node_id_str,
    NS(buffer_size_t) const max_node_id_str_len );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_print_out)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(NodeId_get_required_num_dataptrs)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(NodeId_get_required_num_dataptrs)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeId_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_dataptrs );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(NodeId)*
NS(NodeId_new)( SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(NodeId)*
NS(NodeId_add)( SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(NodeId)*
NS(NodeId_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeId_extract_node_id_str_from_config_str)(
    char* SIXTRL_RESTRICT node_id_str,
    NS(arch_size_t) const node_id_str_capacity,
    char const* SIXTRL_RESTRICT config_str );

#else

SIXTRL_STATIC SIXTRL_FN void NS(NodeId_print_out)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

#endif /* !defined( _GPUCODE )  */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

/* ========================================================================= */
/* =====             Implementation of inline functions                ===== */
/* ========================================================================= */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"

    #if !defined( _GPUCODE ) || defined( __CUDACC__ )
    #include "sixtracklib/common/buffer.h"
    #endif /* !defined( _GPUCODE ) || defined( __CUDACC__ ) */

#endif /* !defined( SIXTRL_NO_INCLUDES ) */


#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */


SIXTRL_INLINE SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_preset)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id )
{
    NS(NodeId_clear( node_id );
    return node_id;
}

SIXTRL_INLINE NS(arch_status_t) NS(NodeId_init)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( node_id != SIXTRL_NULLPTR )
    {
        status  = NS(NodeId_set_platform_id)( node_id, platform_id );
        status |= NS(NodeId_set_device_id)( node_id, device_id );
    }

    return status;
}

SIXTRL_INLINE bool NS(NodeId_is_valid)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return ( ( NS(NodeId_get_platform_id)( node ) !=
        SIXTRL_NODE_ILLEGAL_PLATFORM_ID ) &&
    ( NS(NodeId_get_device_id)( node ) !=
        SIXTRL_NODE_ILLEGAL_DEVICE_ID ) );
}

SIXTRL_INLINE NS(node_platform_id_t) NS(NodeId_get_platform_id)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return ( node != SIXTRL_NULLPTR )
        ? node->platform_id : SIXTRL_NODE_ILLEGAL_PLATFORM_ID;
}

SIXTRL_INLINE NS(node_device_id_t) NS(NodeId_get_device_id)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return ( node_id != SIXTRL_NULLPTR )
        ? node->device_id : SIXTRL_NODE_ILLEGAL_DEVICE_ID;
}

SIXTRL_INLINE NS(arch_status_t) NS(NodeId_set_platform_id)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_platform_id_t) const platform_id )
{
    if( node != SIXTRL_NULLPTR ) node->platform_id = platform_id;
}

SIXTRL_INLINE NS(arch_status_t) NS(NodeId_set_device_id)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_device_id_t) const device_id )
{
    if( node != SIXTRL_NULLPTR ) node->device_id = device_id;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(buffer_size_t)
NS(NodeId_get_required_num_slots_on_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT,
    NS(buffer_size_t) const slot_size )
{
    return NS(ManagedBuffer_get_slot_based_length)(
        sizeof( NS(NodeId) ), slot_size );
}

SIXTRL_INLINE NS(buffer_size_t)
NS(NodeId_get_required_num_dataptrs_on_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT,
    NS(buffer_size_t) const )
{
    return ( NS(buffer_size_t) )0u;
}

SIXTRL_INLINE void NS(NodeId_clear)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node )
{
    NS(NodeId_set_platform_id)( node, SIXTRL_NODE_ILLEGAL_PLATFORM_ID );
    NS(NodeId_set_device_id)( node, SIXTRL_NODE_ILLEGAL_DEVICE_ID );
}

SIXTRL_INLINE NS(arch_size_t) NS(NodeId_required_str_capacity)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    NS(arch_size_t) requ_capacity = ( NS(arch_size_t) )0u;

    if( NS(NodeId_is_valid)( node ) )
    {
        NS(node_platform_id_t) const platform_id =
            NS(NodeId_get_platform_id)( node );

        NS(node_platform_id_t) const device_id =
            NS(NodeId_get_device_id)( node );

        requ_capacity = 2u; /* . and \0 */

        if( platform_id < 10 )
        {
            requ_capacity += 1;
        }
        else if( platform_id < 100 )
        {
            requ_capacity += 2;
        }
        else if( platform_id < 1000 )
        {
            requ_capacity += 3;
        }
        else
        {
            requ_capacity += 6;
        }

        if( device_id < 10 )
        {
            requ_capacity += 1;
        }
        else if( device_id < 100 )
        {
            requ_capacity += 2;
        }
        else if( device_id < 1000 )
        {
            requ_capacity += 3;
        }
        else
        {
            requ_capacity += 6;
        }
    }

    return requ_capacity;
}

SIXTRL_INLINE int NS(NodeId_compare)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs )
{
    int cmp_result = -1;

    NS(node_platform_id_t) const lhs_platform_id =
        NS(NodeId_get_platform_id)( lhs );

    NS(node_device_id_t) const lhs_device_id =
        NS(NodeId_get_device_id)( rhs );

    NS(node_platform_id_t) const rhs_platform_id =
        NS(NodeId_get_platform_id)( rhs );

    NS(node_device_id_t) const rhs_device_id = NS(NodeId_get_device_id)( rhs );

    if( ( lhs_platform_id != SIXTRL_NODE_ILLEGAL_PLATFORM_ID ) &&
        ( lhs_device_id != SIXTRL_NODE_ILLEGAL_DEVICE_ID ) )
    {
        if( ( rhs_platform_id != SIXTRL_NODE_ILLEGAL_PLATFORM_ID ) &&
            ( rhs_device_id != SIXTRL_NODE_ILLEGAL_DEVICE_ID ) )
        {
            if( lhs_platform_id < rhs_platform_id )
            {
                cmp_result = -1;
            }
            else if( lhs_platform > rhs_platform_id )
            {
                cmp_result = +1;
            }
            else if( lhs_device_id < rhs_device_id )
            {
                cmp_result = -1;
            }
            else if( lhs_device_id > rhs_device_id )
            {
                cmp_result = +1;
            }
            else
            {
                cmp_result = 0;
            }
        }
    }
    else if( ( rhs_platform_id != SIXTRL_NODE_ILLEGAL_PLATFORM_ID ) &&
             ( rhs_platform_id != SIXTRL_NODE_ILLEGAL_DEVICE_ID ) )
    {
        cmp_result = +1;
    }

    return cmp_result;
}

SIXTRL_INLINE bool NS(NodeId_are_equal)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs )
{
    return ( ( NS(NodeId_is_valid)( lhs ) ) &&
        ( ( lhs == rhs ) ||
          ( ( NS(NodeId_get_platform_id)( lhs ) ==
              NS(NodeId_get_platform_id)( rhs ) ) &&
            ( NS(NodeId_get_device_id)( lhs ) ==
              NS(NodeId_get_device_id)( rhs ) ) ) ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(NodeId_copy)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT destination,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT source )
{
    NS(arch_status_t) status = NS(NodeId_set_platform_id)(
        destination, NS(NodeId_get_platform_id) );

    status |= NS(NodeId_set_device_id)( destination,
        NS(NodeId_get_device_id)( source ) );

    return status;
}

#if defined( _GPUCODE )

SIXTRL_INLINE void NS(NodeId_print_out)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    if( NS(NodeId_is_valid)( node ) )
    {
        printf( "%d.%d", ( int )NS(NodeId_get_platform_id)( node ),
            ( int )NS(NodeId_get_device_id)( node ) );
    }
}

#endif /* !defined( _GPUCODE )  */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_ID_H__ */

/* end: sixtracklib/common/control/node_id.h */
