#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_ID_H__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_ID_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

typedef struct NS(NodeId)
{
    NS(arch_id_t)          arch_id       SIXTRL_ALIGN( 8 );
    NS(node_platform_id_t) platform_id   SIXTRL_ALIGN( 8 );
    NS(node_device_id_t)   device_id     SIXTRL_ALIGN( 8 );
}
NS(NodeId);

SIXTRL_STATIC SIXTRL_FN SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_preset)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(NodeId_init)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT ptr_node_id,
    NS(arch_id_t) const arch_id,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_FN NS(arch_status_t) NS(NodeId_from_node_id_str)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT node_id_str );

#endif /* !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN bool NS(NodeId_is_valid)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node );


SIXTRL_STATIC SIXTRL_FN NS(arch_id_t) NS(NodeId_get_arch_id)(
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

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(NodeId_set_arch_id)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(arch_id_t) const arch_id );

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

SIXTRL_STATIC SIXTRL_FN bool NS(NodeId_is_smaller_than)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs );

SIXTRL_STATIC SIXTRL_FN int NS(NodeId_compare)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs );

SIXTRL_STATIC SIXTRL_FN bool NS(NodeId_are_equal)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(NodeId_copy)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT destination,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT source );

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_preset_ext)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN  NS(arch_status_t) NS(NodeId_init_ext)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT ptr_node_id,
    NS(arch_id_t) const arch_id, NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN  bool NS(NodeId_is_valid_ext)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_id_t)
NS(NodeId_get_arch_id_ext)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN  NS(node_platform_id_t)
NS(NodeId_get_platform_id_ext)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN  NS(node_device_id_t)
NS(NodeId_get_device_id_ext)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeId_set_arch_id_ext)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(arch_id_t) const arch_id );

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
NS(NodeId_required_str_capacity_for_format)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(node_id_str_fmt_t) const format );

SIXTRL_EXTERN SIXTRL_HOST_FN  NS(arch_size_t)
NS(NodeId_required_str_capacity)(
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

SIXTRL_EXTERN SIXTRL_HOST_FN  NS(node_id_str_fmt_t)
NS(NodeId_identify_format_from_node_id_str)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT node_id_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_DATAPTR_DEC NS(NodeId)*
NS(NodeId_create)( NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_delete)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_DATAPTR_DEC NS(NodeId)*
NS(NodeId_new_detailed)( NS(arch_id_t) const arch_id,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_DATAPTR_DEC NS(NodeId)*
NS(NodeId_new_from_string)( char const* SIXTRL_RESTRICT node_id_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeId_to_node_id_str)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(arch_size_t) const output_str_capacity,
    char* SIXTRL_RESTRICT output_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeId_to_node_id_str_with_format)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(arch_size_t) const output_str_capacity,
    char* SIXTRL_RESTRICT output_str, NS(node_id_str_fmt_t) const format );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_print)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    FILE* SIXTRL_RESTRICT fp );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_print_with_format)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    FILE* SIXTRL_RESTRICT fp, NS(node_id_str_fmt_t) const format );


SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_print_out)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_print_out_with_format)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(node_id_str_fmt_t) const format );

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
    NS(arch_id_t) const arch_id, NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(NodeId)*
NS(NodeId_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeId_extract_node_id_str_from_config_str)(
    NS(arch_size_t) const node_id_str_capacity,
    char* SIXTRL_RESTRICT node_id_str,
    char const* SIXTRL_RESTRICT config_str );

#else

SIXTRL_STATIC SIXTRL_FN void NS(NodeId_print_out)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_STATIC SIXTRL_FN void NS(NodeId_print_out_with_format)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(node_id_str_fmt_t) const format );

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
    if( node_id != SIXTRL_NULLPTR )
    {
        node_id->arch_id     = SIXTRL_ARCHITECTURE_ILLEGAL;
        node_id->platform_id = SIXTRL_NODE_ILLEGAL_PLATFORM_ID;
        node_id->device_id   = SIXTRL_NODE_ILLEGAL_DEVICE_ID;
    }

    return node_id;
}

SIXTRL_INLINE NS(arch_status_t) NS(NodeId_init)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id,
    NS(arch_id_t) const arch_id, NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( node_id != SIXTRL_NULLPTR )
    {
        status  = NS(NodeId_set_arch_id)( node_id, arch_id );
        status |= NS(NodeId_set_platform_id)( node_id, platform_id );
        status |= NS(NodeId_set_device_id)( node_id, device_id );
    }

    return status;
}

SIXTRL_INLINE bool NS(NodeId_is_valid)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return (
        ( NS(NodeId_get_arch_id)( node ) != SIXTRL_ARCHITECTURE_ILLEGAL ) &&
        ( NS(NodeId_get_platform_id)( node ) !=
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
    return ( node != SIXTRL_NULLPTR )
        ? node->device_id : SIXTRL_NODE_ILLEGAL_DEVICE_ID;
}

SIXTRL_INLINE NS(arch_id_t) NS(NodeId_get_arch_id)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node )
{
   return ( node != SIXTRL_NULLPTR )
        ? node->arch_id : SIXTRL_ARCHITECTURE_ILLEGAL;
}

SIXTRL_INLINE NS(arch_status_t) NS(NodeId_set_platform_id)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_platform_id_t) const platform_id )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( node != SIXTRL_NULLPTR )
    {
        node->platform_id = platform_id;
        status = SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(NodeId_set_device_id)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_device_id_t) const device_id )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( node != SIXTRL_NULLPTR )
    {
        node->device_id = device_id;
        status = SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(NodeId_set_arch_id)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(arch_id_t) const arch_id )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( node != SIXTRL_NULLPTR ) &&
        ( ( node->arch_id == SIXTRL_ARCHITECTURE_ILLEGAL ) ||
          ( arch_id == SIXTRL_ARCHITECTURE_ILLEGAL ) ||
          ( node->arch_id == arch_id ) ) )
    {
        node->arch_id = arch_id;
        status = SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(buffer_size_t)
NS(NodeId_get_required_num_slots_on_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const slot_size )
{
    ( void )buffer;

    return NS(ManagedBuffer_get_slot_based_length)(
        sizeof( NS(NodeId) ), slot_size );
}

SIXTRL_INLINE NS(buffer_size_t)
NS(NodeId_get_required_num_dataptrs_on_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const slot_size )
{
    ( void )buffer;
    ( void )slot_size;

    return ( NS(buffer_size_t) )0u;
}

SIXTRL_INLINE void NS(NodeId_clear)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node )
{
    NS(NodeId_set_platform_id)( node, SIXTRL_NODE_ILLEGAL_PLATFORM_ID );
    NS(NodeId_set_device_id)( node, SIXTRL_NODE_ILLEGAL_DEVICE_ID );
}

SIXTRL_INLINE int NS(NodeId_compare)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs )
{
    int cmp_result = -1;

    if( ( NS(NodeId_is_valid)( lhs ) ) && ( NS(NodeId_is_valid)( rhs ) ) )
    {
        if( NS(NodeId_get_arch_id)( lhs ) == NS(NodeId_get_arch_id)( rhs ) )
        {
            cmp_result = 0;
        }
        else if( NS(NodeId_get_arch_id)( lhs ) > NS(NodeId_get_arch_id)( rhs ) )
        {
            cmp_result = -1;
        }

        if( cmp_result == 0 )
        {
            if( NS(NodeId_get_platform_id)( lhs ) >
                NS(NodeId_get_platform_id)( rhs ) )
            {
                cmp_result = +1;
            }
            else if( NS(NodeId_get_platform_id)( lhs ) <
                     NS(NodeId_get_platform_id)( rhs ) )
            {
                cmp_result = -1;
            }
        }

        if( cmp_result == 0 )
        {
            if( NS(NodeId_get_device_id)( lhs ) >
                NS(NodeId_get_device_id)( rhs ) )
            {
                cmp_result= +1;
            }
            else if( NS(NodeId_get_device_id)( lhs ) <
                     NS(NodeId_get_device_id)( rhs ) )
            {
                cmp_result = -1;
            }
        }
    }
    else if( NS(NodeId_is_valid)( lhs ) )
    {
        cmp_result = +1;
    }

    return cmp_result;
}

SIXTRL_INLINE bool NS(NodeId_is_smaller_than)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs )
{
    NS(arch_id_t) const lhs_arch = NS(NodeId_get_arch_id)( lhs );
    NS(arch_id_t) const rhs_arch = NS(NodeId_get_arch_id)( rhs );

    NS(node_platform_id_t) const lhs_platform = NS(NodeId_get_platform_id)( lhs );
    NS(node_platform_id_t) const rhs_platform = NS(NodeId_get_platform_id)( rhs );

    return ( ( lhs_arch < rhs_arch ) ||
             ( ( lhs_arch == rhs_arch ) &&
               ( lhs_platform < rhs_platform ) ) ||
             ( ( lhs_arch == rhs_arch ) &&
               ( lhs_platform == rhs_platform ) &&
               ( NS(NodeId_get_device_id)( lhs ) <
                 NS(NodeId_get_device_id)( rhs ) ) ) );
}

SIXTRL_INLINE bool NS(NodeId_are_equal)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs )
{
    return ( ( NS(NodeId_is_valid)( lhs ) ) &&
        ( ( lhs == rhs ) ||
          ( ( NS(NodeId_get_arch_id)( lhs ) ==
              NS(NodeId_get_arch_id)( rhs ) ) &&
            ( NS(NodeId_get_platform_id)( lhs ) ==
              NS(NodeId_get_platform_id)( rhs ) ) &&
            ( NS(NodeId_get_device_id)( lhs ) ==
              NS(NodeId_get_device_id)( rhs ) ) ) ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(NodeId_copy)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT destination,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT source )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_SUCCESS;

    status |= NS(NodeId_set_arch_id)(
        destination, NS(NodeId_get_arch_id)( source ) );

    status |= NS(NodeId_set_platform_id)(
        destination, NS(NodeId_get_platform_id)( source ) );

    status |= NS(NodeId_set_device_id)( destination,
        NS(NodeId_get_device_id)( source ) );

    return status;
}


#if defined( _GPUCODE )

SIXTRL_INLINE void NS(NodeId_print_out_with_format)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(node_id_str_fmt_t) const format )
{
    if( ( NS(NodeId_is_valid)( node ) ) &&
        ( format != SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL ) )
    {
        if( format == SIXTRL_NODE_ID_STR_FORMAT_NOARCH )
        {
            printf( "%ld.%ld",
                ( long int )NS(NodeId_get_platform_id)( node ),
                ( long int )NS(NodeId_get_device_id)( node ) );
        }
        else if( format == SIXTRL_NODE_ID_STR_FORMAT_ARCHID )
        {
            printf( "%ld:%ld.%ld",
                ( long int )NS(NodeId_get_arch_id)( node ),
                ( long int )NS(NodeId_get_platform_id)( node ),
                ( long int )NS(NodeId_get_device_id)( node ) );
        }
        else if( format == SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR )
        {
            SIXTRL_ARGPTR_DEC char temp_arch_str[ 16 ];

            NS(arch_status_t) const status =
                NS(ArchInfo_get_arch_string_for_arch_id)(
                    NS(NodeId_get_arch_id)( node ), 16, temp_arch_str );

            if( status == SIXTRL_ARCH_STATUS_SUCCESS )
            {
                printf( "%s:%ld.%ld", temp_arch_str,
                        ( long int )NS(NodeId_get_platform_id)( node ),
                        ( long int )NS(NodeId_get_device_id)( node ) );
            }
        }
    }
}

SIXTRL_INLINE void NS(NodeId_print_out)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    NS(NodeId_print_out_with_format)(
        node, ( NS(node_id_str_fmt_t) )SIXTRL_NODE_ID_STR_FORMAT_DEFAULT );
}

#endif /* !defined( _GPUCODE )  */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_ID_H__ */

/* end: sixtracklib/common/control/node_id.h */
