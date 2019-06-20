#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_id.h"
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
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"

    #if !defined( _GPUCODE ) || defined( __CUDACC__ )
        #include "sixtracklib/common/buffer.h"
    #endif /* !defined( _GPUCODE ) || defined( __CUDACC__ ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_preset_ext)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id )
{
    return NS(NodeId_preset)( node_id );
}

NS(arch_status_t) NS(NodeId_init_ext)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT ptr_node_id,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    return NS(NodeId_init)( ptr_node_id, platform_id, device_id );
}

bool NS(NodeId_is_valid_ext)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return NS(NodeId_is_valid)( node );
}

NS(node_platform_id_t) NS(NodeId_get_platform_id_ext)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return NS(NodeId_get_platform_id)( node );
}

NS(node_device_id_t) NS(NodeId_get_device_id_ext)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return NS(NodeId_get_device_id)( node );
}


NS(arch_status_t) NS(NodeId_set_platform_id_ext)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_platform_id_t) const platform_id )
{
    return NS(NodeId_set_platform_id)( node, platform_id );
}

NS(arch_status_t) NS(NodeId_set_device_id_ext)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_device_id_t) const device_id )
{
    return NS(NodeId_set_device_id)( node, device_id );
}

/* ------------------------------------------------------------------------- */

void NS(NodeId_clear_ext)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node )
{
    return NS(NodeId_clear)( node );
}

NS(arch_size_t) NS(NodeId_required_str_capacity_ext)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return NS(NodeId_required_str_capacity)( node );
}

int NS(NodeId_compare_ext)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs )
{
    return NS(NodeId_compare)( lhs, rhs );
}

bool NS(NodeId_are_equal_ext)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs )
{
    return NS(NodeId_are_equal)( lhs, rhs );
}

NS(arch_status_t) NS(NodeId_copy_ext)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT destination,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT source )
{
    return NS(NodeId_copy)( destination, source );
}

/* ------------------------------------------------------------------------- */

NS(arch_status_t) NS(NodeId_init_from_string)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    char const* SIXTRL_RESTRICT node_id_str )
{
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( node != SIXTRL_NULLPTR ) && ( node_id_str != SIXTRL_NULLPTR ) &&
        ( strlen( node_id_str ) > ( NS(buffer_size_t) )2u ) )
    {
        long int temp_platform_id = ( long int )NS(NODE_ILLEGAL_PLATFORM_ID);
        long int temp_device_id   = ( long int )NS(NODE_ILLEGAL_DEVICE_ID);

        int const ret = sscanf( node_id_str, "%ld.%ld",
                                &temp_platform_id, &temp_device_id );

        if( ( ret == 2 ) &&
            ( temp_platform_id >= 0 ) && ( temp_device_id >= 0 ) )
        {
            status =  NS(NodeId_set_platform_id)( node,
                ( NS(node_platform_id_t) )temp_platform_id );

            status |= NS(NodeId_set_device_id)( node,
                ( NS(node_device_id_t) )temp_device_id );
        }

        SIXTRL_ASSERT( ( status != NS(ARCH_STATUS_SUCCESS) ) ||
            ( NS(NodeId_is_valid)( node ) ) );
    }

    return status;
}

/* ------------------------------------------------------------------------- */

SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_create)( void )
{
    return NS(NodeId_preset)( ( NS(NodeId)* )malloc( sizeof( NS(NodeId) ) ) );
}

void NS(NodeId_delete)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id )
{
    free( node_id );
}

SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_new)(
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    SIXTRL_DATAPTR_DEC NS(NodeId)* node = NS(NodeId_create)();

    if( NS(ARCH_STATUS_SUCCESS) !=
            NS(NodeId_init)( node, platform_id, device_id ) )
    {
        NS(NodeId_delete)( node );
        node = SIXTRL_NULLPTR;
    }

    return node;
}

SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_new_from_string)(
    char const* SIXTRL_RESTRICT node_id_str )
{
    SIXTRL_DATAPTR_DEC NS(NodeId)* node = NS(NodeId_create)();

    if( NS(ARCH_STATUS_SUCCESS) !=
            NS(NodeId_init_from_string)( node, node_id_str ) )
    {
        NS(NodeId_delete)( node );
        node = SIXTRL_NULLPTR;
    }

    return node;
}

/* ------------------------------------------------------------------------- */

NS(arch_status_t) NS(NodeId_from_node_id_str)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    char const* SIXTRL_RESTRICT node_id_str )
{
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( node != SIXTRL_NULLPTR )
    {
        NS(NodeId_clear)( node );
        status = NS(NodeId_init_from_string)( node, node_id_str );
    }

    return status;
}

NS(arch_status_t) NS(NodeId_to_node_id_str)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(arch_size_t) const output_str_capacity,
    char* SIXTRL_RESTRICT output_str )
{
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    NS(arch_size_t) const requ_capacity =
        NS(NodeId_required_str_capacity)( node );

    if( ( output_str != SIXTRL_NULLPTR ) &&
        ( requ_capacity > ( NS(arch_size_t) )0u ) &&
        ( requ_capacity <= output_str_capacity ) )
    {
        int const ret = sprintf( output_str, "%ld.%ld",
            ( long int )NS(NodeId_get_platform_id)( node ),
            ( long int )NS(NodeId_get_device_id)( node ) );

        SIXTRL_ASSERT( NS(NodeId_is_valid)( node ) );

        if( ret == 2 )
        {
            status = NS(ARCH_STATUS_SUCCESS);
        }
    }

    return status;
}

/* ------------------------------------------------------------------------- */

void NS(NodeId_print)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    FILE* SIXTRL_RESTRICT fp )
{
    if( ( node != SIXTRL_NULLPTR ) && ( fp != SIXTRL_NULLPTR ) )
    {
        char temp_node_id_str[ 16 ] =
        {
            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
        };

        NS(arch_status_t) status = NS(NodeId_to_node_id_str)(
            node, 16u, &temp_node_id_str[ 0 ] );

        if( status == NS(ARCH_STATUS_SUCCESS) )
        {
            int const ret = printf( "%s", &temp_node_id_str[ 0 ] );
            SIXTRL_ASSERT( ret > 0 );
            ( void )ret;
        }
    }
}

void NS(NodeId_print_out)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    NS(NodeId_print)( node, stdout );
}

/* ------------------------------------------------------------------------- */

NS(buffer_size_t) NS(NodeId_get_required_num_dataptrs)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(NodeId_get_required_num_slots_on_managed_buffer)(
        NS(Buffer_get_data_begin)( buffer ),
        NS(Buffer_get_slot_size)( buffer ) );
}

NS(buffer_size_t) NS(NodeId_get_required_num_dataptrs)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(NodeId_get_required_num_dataptrs_on_managed_buffer)(
        NS(Buffer_get_data_begin)( buffer ),
        NS(Buffer_get_slot_size)( buffer ) );
}

bool NS(NodeId_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_dataptrs )
{
    typedef NS(buffer_size_t) buf_size_t;

    buf_size_t const num_dataptrs =
        NS(NodeId_get_required_num_dataptrs)( buffer );

    return NS(Buffer_can_add_object)( buffer, sizeof( NS(NodeId) ),
        num_dataptrs, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
        requ_objects, requ_slots, requ_dataptrs );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(NodeId)*
NS(NodeId_new)( SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer )
{
    typedef NS(NodeId) node_id_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC node_id_t* ptr_to_node_id_t;

    NS(NodeId) node_id;
    NS(NodeId_preset)( &node_id );

    NS(buffer_size_t) const num_dataptrs =
        NS(NodeId_get_required_num_dataptrs)( buffer );

    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( num_dataptrs == ( NS(buffer_size_t) )0u );

    return ( ptr_to_node_id_t )( uintptr_t )NS(Object_get_begin_addr)(
        NS(Buffer_add_object)( buffer, &node_id, sizeof( NS(NodeId) ),
            NS(OBJECT_TYPE_NODE_ID), num_dataptrs, SIXTRL_NULLPTR,
                SIXTRL_NULLPTR, SIXTRL_NULLPTR ) );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(NodeId)* NS(NodeId_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    typedef NS(NodeId) node_id_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC node_id_t* ptr_to_node_id_t;

    NS(NodeId) node_id;
    NS(NodeId_init)( &node_id, platform_id, device_id );

    NS(buffer_size_t) const num_dataptrs =
        NS(NodeId_get_required_num_dataptrs)( buffer );

    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( num_dataptrs == ( NS(buffer_size_t) )0u );

    return ( ptr_to_node_id_t )( uintptr_t )NS(Object_get_begin_addr)(
        NS(Buffer_add_object)( buffer, &node_id, sizeof( NS(NodeId) ),
            NS(OBJECT_TYPE_NODE_ID), num_dataptrs, SIXTRL_NULLPTR,
                SIXTRL_NULLPTR, SIXTRL_NULLPTR ) );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(NodeId)* NS(NodeId_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    return NS(NodeId_add)( buffer, NS(NodeId_get_platform_id)( node_id ),
                           NS(NodeId_get_device_id)( node_id ) );
}

/* end: sixtracklib/common/control/node_id.c */
