#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <ctype.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/architecture/definitions.h"
    #include "sixtracklib/common/architecture/architecture.hpp"
    #include "sixtracklib/common/architecture/architecture.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"

    #if !defined( _GPUCODE ) || defined( __CUDACC__ )
        #include "sixtracklib/common/buffer.h"
    #endif /* !defined( _GPUCODE ) || defined( __CUDACC__ ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


SIXTRL_STATIC SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeId_get_num_digits_integer)( NS(arch_size_t) const number );

SIXTRL_STATIC SIXTRL_HOST_FN bool
NS(NodeId_string_starts_with_number)( char const* SIXTRL_RESTRICT str )
{
    return ( ( str != SIXTRL_NULLPTR ) &&
             ( strlen( str ) > ( NS(arch_size_t) )0u ) &&
             ( isdigit( str[ 0 ] ) ) );
}

/* ========================================================================== */

SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_preset_ext)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id )
{
    return NS(NodeId_preset)( node_id );
}

/* ------------------------------------------------------------------------- */

NS(arch_status_t) NS(NodeId_init_ext)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT ptr_node_id,
    NS(arch_id_t) const arch_id, NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    return NS(NodeId_init)( ptr_node_id, arch_id, platform_id, device_id );
}

bool NS(NodeId_is_valid_ext)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return NS(NodeId_is_valid)( node );
}

NS(arch_id_t) NS(NodeId_get_arch_id_ext)(
    SIXTRL_DATAPTR_DEC  const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return NS(NodeId_get_arch_id)( node );
}

NS(node_platform_id_t) NS(NodeId_get_platform_id_ext)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return NS(NodeId_get_platform_id)( node );
}

NS(node_device_id_t) NS(NodeId_get_device_id_ext)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return NS(NodeId_get_device_id)( node );
}

NS(arch_status_t) NS(NodeId_set_arch_id_ext)(
    SIXTRL_DATAPTR_DEC  NS(NodeId)* SIXTRL_RESTRICT node,
    NS(arch_id_t) const arch_id  )
{
    return NS(NodeId_set_arch_id)( node, arch_id );
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
    NS(NodeId_clear)( node );
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

NS(arch_size_t) NS(NodeId_get_num_digits_integer)(
    NS(arch_size_t) const number )
{
    if( number < ( NS(arch_size_t)  )10u )
    {
        return ( NS(arch_size_t)  )1u;
    }
    else if( number < ( NS(arch_size_t) )100u )
    {
        return ( NS(arch_size_t) )2u;
    }
    else if( number < ( NS(arch_size_t) )1000u )
    {
        return ( NS(arch_size_t) )3u;
    }
    else if( number < ( NS(arch_size_t) )10000u )
    {
        return ( NS(arch_size_t) )4u;
    }
    else if( number < ( NS(arch_size_t) )100000u )
    {
        return ( NS(arch_size_t) )5u;
    }
    else if( number < ( NS(arch_size_t) )1000000u )
    {
        return ( NS(arch_size_t) )6u;
    }
    else if( number < ( NS(arch_size_t) )10000000u )
    {
        return ( NS(arch_size_t) )7u;
    }
    else if( number < ( NS(arch_size_t) )100000000u )
    {
        return ( NS(arch_size_t) )8u;
    }
    else if( number < ( NS(arch_size_t) )0xffffffff )
    {
        return ( NS(arch_size_t) )9u;
    }

    return ( NS(arch_size_t) )20u;
}


NS(arch_size_t) NS(NodeId_required_str_capacity_for_format)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(node_id_str_fmt_t) const format )
{
    NS(arch_size_t) requ_capacity = ( NS(arch_size_t) )0u;
    NS(arch_id_t) const arch_id = NS(NodeId_get_arch_id)( node );

    if( ( NS(NodeId_get_platform_id)( node ) != SIXTRL_NODE_ILLEGAL_PLATFORM_ID ) &&
        ( NS(NodeId_get_device_id)( node ) != SIXTRL_NODE_ILLEGAL_DEVICE_ID ) &&
        ( format != SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL ) )
    {
        bool const arch_id_valid = (
            ( arch_id != NS(ARCHITECTURE_ILLEGAL) ) &&
            ( arch_id != NS(ARCHITECTURE_NONE) ) );

        requ_capacity = ( NS(arch_size_t) )2u; /* . and \0 */

        NS(node_platform_id_t) const platform_id =
            NS(NodeId_get_platform_id)( node );

        NS(node_platform_id_t) const device_id =
            NS(NodeId_get_device_id)( node );

        requ_capacity += NS(NodeId_get_num_digits_integer)(
            ( NS(arch_size_t ) )platform_id );

        requ_capacity += NS(NodeId_get_num_digits_integer)(
            ( NS(arch_size_t ) )device_id );

        if( ( format == SIXTRL_NODE_ID_STR_FORMAT_ARCHID ) &&
            ( arch_id_valid ) )
        {
            requ_capacity += NS(NodeId_get_num_digits_integer)(
                ( NS(arch_size_t ) )NS(NodeId_get_arch_id)( node ) );
            ++requ_capacity;
        }
        else if( ( format == SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR ) &&
                 ( arch_id_valid ) )
        {
            if( NS(Architectures_has_arch_str)(
                    NS(Architectures_get_const_ptr)(), arch_id ) )
            {
                NS(arch_size_t) const arch_str_len = strlen(
                    NS(Architectures_get_arch_str)(
                        NS(Architectures_get_const_ptr)(), arch_id ) );

                SIXTRL_ASSERT( arch_str_len > ( NS(arch_size_t) )0u );
                requ_capacity += arch_str_len;
            }
            else
            {
                requ_capacity += 16;
            }

            ++requ_capacity; /* for : separator */
        }
        else if( format != SIXTRL_NODE_ID_STR_FORMAT_NOARCH )
        {
            requ_capacity = ( NS(arch_size_t) )0u;
        }
    }

    return requ_capacity;
}

NS(arch_size_t) NS(NodeId_required_str_capacity)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return NS(NodeId_required_str_capacity_for_format)(
        node, ( NS(node_id_str_fmt_t) )SIXTRL_NODE_ID_STR_FORMAT_DEFAULT );
}

NS(node_id_str_fmt_t) NS(NodeId_identify_format_from_node_id_str)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT node_id_str )
{
    typedef SIXTRL_ARGPTR_DEC char const* ccharptr_t;
    typedef NS(node_id_str_fmt_t) fmt_t;

    fmt_t fmt = ( fmt_t )SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL;

    NS(arch_size_t) const str_len = strlen( node_id_str );

    if( ( node_id_str != SIXTRL_NULLPTR ) &&
        ( str_len > ( NS(arch_size_t) )0u ) )

    {
        ccharptr_t end_pos = node_id_str + str_len;
        ccharptr_t dot_pos = SIXTRL_NULLPTR;
        ccharptr_t start_pos = node_id_str;

        ccharptr_t col_pos = strchr( node_id_str, ':' );

        if( col_pos != SIXTRL_NULLPTR )
        {
            start_pos = col_pos + 1;
        }

        dot_pos = strchr( start_pos, '.' );

        if( ( dot_pos != SIXTRL_NULLPTR ) &&
            ( NS(NodeId_string_starts_with_number)( dot_pos + 1 ) ) &&
            ( ( uintptr_t )dot_pos > ( uintptr_t )node_id_str ) &&
            ( ( uintptr_t )dot_pos < ( uintptr_t )end_pos ) )
        {
            if( ( col_pos == SIXTRL_NULLPTR ) &&
                ( NS(NodeId_string_starts_with_number)( node_id_str ) ) )
            {
                fmt = ( fmt_t )SIXTRL_NODE_ID_STR_FORMAT_NOARCH;
            }
            else if( ( col_pos != SIXTRL_NULLPTR ) &&
                     ( NS(NodeId_string_starts_with_number)( node_id_str ) ) )
            {
                fmt = ( fmt_t )SIXTRL_NODE_ID_STR_FORMAT_ARCHID;
            }
            else if( col_pos != SIXTRL_NULLPTR )
            {
                fmt = ( fmt_t )SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR;
            }
        }
    }

    return fmt;
}

/* ------------------------------------------------------------------------- */

NS(arch_status_t) NS(NodeId_from_node_id_str)(
    SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    char const* SIXTRL_RESTRICT node_id_str )
{
    typedef NS(arch_size_t) size_t;

    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( node != SIXTRL_NULLPTR ) && ( node_id_str != SIXTRL_NULLPTR ) &&
        ( strlen( node_id_str ) > ( size_t )0u ) )
    {
        NS(node_id_str_fmt_t) const format =
            NS(NodeId_identify_format_from_node_id_str)( node_id_str );

        switch( format )
        {
            case SIXTRL_NODE_ID_STR_FORMAT_NOARCH:
            {
                long int temp_platform_id = ( long int )-1;
                long int temp_device_id = ( long int )-1;

                int const ret = sscanf( node_id_str, "%ld.%ld",
                        &temp_platform_id, &temp_device_id );

                if( ret == 2 )
                {
                    status = NS(NodeId_set_platform_id)(
                        node, temp_platform_id );

                    if( status == NS(ARCH_STATUS_SUCCESS) )
                    {
                        status = NS(NodeId_set_device_id)(
                            node, temp_device_id );
                    }
                }

                break;
            }

            case SIXTRL_NODE_ID_STR_FORMAT_ARCHID:
            {
                long int temp_arch_id = ( long int )-1;
                long int temp_platform_id = ( long int )-1;
                long int temp_device_id = ( long int )-1;

                int const ret = sscanf( node_id_str, "%ld:%ld.%ld",
                        &temp_arch_id, &temp_platform_id, &temp_device_id );

                if( ret == 3 )
                {
                    NS(Architectures) const* architectures =
                        NS(Architectures_get_const_ptr)();

                    if( NS(Architectures_has_architecture)(
                        architectures, temp_arch_id ) )
                    {
                        status = NS(NodeId_set_arch_id)( node, temp_arch_id );

                        if( status == NS(ARCH_STATUS_SUCCESS) )
                        {
                            status = NS(NodeId_set_platform_id)(
                                node, temp_platform_id );
                        }

                        if( status == NS(ARCH_STATUS_SUCCESS) )
                        {
                            status = NS(NodeId_set_device_id)(
                                node, temp_device_id );
                        }
                    }
                }

                break;
            }

            case SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR:
            {
                NS(arch_id_t) arch_id = NS(ARCHITECTURE_ILLEGAL);

                char const* end_pos = strchr( node_id_str, '\0' );
                char const* col_pos = strchr( node_id_str, ':'  );

                if( ( col_pos != SIXTRL_NULLPTR ) &&
                    ( ( uintptr_t )col_pos < ( uintptr_t )end_pos ) )
                {
                    size_t const MAX_TEMP_ARCH_STR_LEN = ( size_t )31u;
                    char temp_arch_str[] =
                    {
                        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
                    };

                    SIXTRL_ASSERT( ( uintptr_t )node_id_str <=
                        ( uintptr_t )col_pos );

                    size_t const arch_str_len = ( ( uintptr_t )col_pos ) -
                        ( uintptr_t )node_id_str;

                    if( arch_str_len <= MAX_TEMP_ARCH_STR_LEN )
                    {
                        memcpy( &temp_arch_str[ 0 ], node_id_str,
                                arch_str_len );

                        NS(Architectures) const* architectures =
                            NS(Architectures_get_const_ptr)();

                        arch_id = NS(Architectures_get_arch_id)( architectures,
                            &temp_arch_str[ 0 ] );
                    }
                }

                if( ( col_pos != SIXTRL_NULLPTR ) &&
                    ( arch_id != NS(ARCHITECTURE_ILLEGAL) ) )
                {
                    long int temp_platform_id = ( long int )-1;
                    long int temp_device_id = ( long int )-1;

                    int const ret = sscanf( col_pos + 1u, "%ld.%ld",
                        &temp_platform_id, &temp_device_id );

                    if( ret == 2 )
                    {
                        status = NS(NodeId_set_arch_id)(
                            node, arch_id );

                        if( status == NS(ARCH_STATUS_SUCCESS) )
                        {
                            status = NS(NodeId_set_platform_id)(
                                node, temp_platform_id );
                        }

                        if( status == NS(ARCH_STATUS_SUCCESS) )
                        {
                            status = NS(NodeId_set_device_id)(
                                node, temp_device_id );
                        }
                    }
                }

                break;
            }

            default:
            {
                SIXTRL_ASSERT( format == NS(NODE_ID_STR_FORMAT_ILLEGAL) );
                status = NS(ARCH_STATUS_GENERAL_FAILURE);
            }
        };
    }

    return status;
}

SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_create)( NS(arch_id_t) const arch_id )
{
    SIXTRL_DATAPTR_DEC NS(NodeId)* node = NS(NodeId_preset)(
        ( NS(NodeId)* )malloc( sizeof( NS(NodeId) ) ) );

    NS(arch_status_t) const status = NS(NodeId_set_arch_id)( node, arch_id );
    SIXTRL_ASSERT( status == NS(ARCH_STATUS_SUCCESS) );
    ( void )status;

    return node;
}

void NS(NodeId_delete)( SIXTRL_DATAPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node )
{
    free( node );
}

SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_new_detailed)(
    NS(arch_id_t) const arch_id,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    SIXTRL_DATAPTR_DEC NS(NodeId)* node = NS(NodeId_create)( arch_id );

    NS(arch_status_t) status = NS(NodeId_set_platform_id)( node, platform_id );
    status |= NS(NodeId_set_device_id)( node, device_id );

    if( ( arch_id != NS(NodeId_get_arch_id)( node ) ) ||
        ( status != NS(ARCH_STATUS_SUCCESS) ) )
    {
        NS(NodeId_delete)( node );
        node = SIXTRL_NULLPTR;
    }

    return node;
}

SIXTRL_DATAPTR_DEC NS(NodeId)* NS(NodeId_new_from_string)(
    char const* SIXTRL_RESTRICT node_id_str )
{
    SIXTRL_DATAPTR_DEC NS(NodeId)* node =
        NS(NodeId_create)( NS(ARCHITECTURE_ILLEGAL) );

    NS(arch_status_t) const status =
        NS(NodeId_from_node_id_str)( node, node_id_str );

    if( NS(ARCH_STATUS_SUCCESS) != status )
    {
        NS(NodeId_delete)( node );
        node = SIXTRL_NULLPTR;
    }

    return node;
}

/* ------------------------------------------------------------------------- */

NS(arch_status_t) NS(NodeId_to_node_id_str)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(arch_size_t) const output_str_capacity,
    char* SIXTRL_RESTRICT output_str )
{
    return NS(NodeId_to_node_id_str_with_format)(
        node, output_str_capacity, output_str,
        NS(NODE_ID_STR_FORMAT_DEFAULT) );
}

NS(arch_status_t) NS(NodeId_to_node_id_str_with_format)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(arch_size_t) const output_str_capacity,
    char* SIXTRL_RESTRICT output_str,
    NS(node_id_str_fmt_t) const format )
{
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    NS(arch_size_t) const requ_capacity =
        NS(NodeId_required_str_capacity_for_format)( node, format );

    NS(arch_id_t) const arch_id = NS(NodeId_get_arch_id)( node );
    NS(node_device_id_t) const device_id = NS(NodeId_get_device_id)( node );
    NS(node_platform_id_t) const platform_id = NS(NodeId_get_platform_id)( node );

    if( ( output_str != SIXTRL_NULLPTR ) &&
        ( format != NS(NODE_ID_STR_FORMAT_ILLEGAL) ) &&
        ( requ_capacity > ( NS(arch_size_t) )0u ) &&
        ( requ_capacity <= output_str_capacity ) )
    {
        if( ( format == NS(NODE_ID_STR_FORMAT_NOARCH) ) &&
            ( platform_id != NS(NODE_ILLEGAL_PLATFORM_ID) ) &&
            ( device_id != NS(NODE_ILLEGAL_DEVICE_ID) ) )
        {
            int const ret = sprintf( output_str, "%ld.%ld",
                ( long int )platform_id, ( long int )device_id );

            if( ret > 0 ) status = NS(ARCH_STATUS_SUCCESS);
        }
        else if( ( format == NS(NODE_ID_STR_FORMAT_ARCHID) ) &&
                 ( NS(NodeId_is_valid)( node ) ) )
        {
            int const ret = sprintf( output_str, "%ld:%ld.%ld",
                ( long int )arch_id, ( long int )platform_id,
                    ( long int )device_id );

            if( ret > 0 ) status = NS(ARCH_STATUS_SUCCESS);
        }
        else if( ( format == NS(NODE_ID_STR_FORMAT_ARCHSTR) ) &&
                 ( NS(NodeId_is_valid)( node ) ) )
        {
            char temp_arch_str[ 16 ] =
            {
                '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
            };

            if( NS(Architectures_has_arch_str)(
                NS(Architectures_get_const_ptr)(), arch_id ) )
            {
                SIXTRL_ASSERT( NS(Architectures_get_arch_str)(
                    NS(Architectures_get_const_ptr)(), arch_id ) !=
                        SIXTRL_NULLPTR );

                strncpy( temp_arch_str, NS(Architectures_get_arch_str)(
                    NS(Architectures_get_const_ptr)(), arch_id ), 15 );

                status = NS(ARCH_STATUS_SUCCESS);
            }

            if( ( status == NS(ARCH_STATUS_SUCCESS) ) &&
                ( strlen( temp_arch_str ) > ( NS(arch_size_t) )0u ) )
            {
                int const ret = sprintf( output_str, "%s:%ld.%ld",
                    temp_arch_str, ( long int )platform_id,
                        ( long int )device_id );

                if( ret < 0 ) status = NS(ARCH_STATUS_GENERAL_FAILURE);
            }
        }
    }

    return status;
}

/* ------------------------------------------------------------------------- */

void NS(NodeId_print)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    FILE* SIXTRL_RESTRICT fp )
{
    NS(NodeId_print_with_format)( node, fp, NS(NODE_ID_STR_FORMAT_DEFAULT) );
}

void NS(NodeId_print_with_format)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    FILE* SIXTRL_RESTRICT fp, NS(node_id_str_fmt_t) const format )
{
    if( ( node != SIXTRL_NULLPTR ) && ( fp != SIXTRL_NULLPTR ) )
    {
        char temp_node_id_str[ 64 ];
        memset( temp_node_id_str, ( int )'\0', 64 );

        NS(arch_status_t) status = NS(NodeId_to_node_id_str_with_format)(
            node, 64u, &temp_node_id_str[ 0 ], format );

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
    NS(NodeId_print_with_format)(
        node, stdout, NS(NODE_ID_STR_FORMAT_DEFAULT) );
}

void NS(NodeId_print_out_with_format)(
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(node_id_str_fmt_t) const format )
{
    NS(NodeId_print_with_format)( node, stdout, format );
}

/* ------------------------------------------------------------------------- */

NS(buffer_size_t) NS(NodeId_get_required_num_slots)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(NodeId_get_required_num_slots_on_managed_buffer)(
        NS(Buffer_get_const_data_begin)( buffer ),
        NS(Buffer_get_slot_size)( buffer ) );
}

NS(buffer_size_t) NS(NodeId_get_required_num_dataptrs)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(NodeId_get_required_num_dataptrs_on_managed_buffer)(
        NS(Buffer_get_const_data_begin)( buffer ),
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
    NS(arch_id_t) const arch_id, NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    typedef NS(NodeId) node_id_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC node_id_t* ptr_to_node_id_t;

    NS(NodeId) node_id;
    NS(NodeId_init)( &node_id, arch_id, platform_id, device_id );

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
    SIXTRL_DATAPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return NS(NodeId_add)( buffer,
        NS(NodeId_get_arch_id)( node ), NS(NodeId_get_platform_id)( node ),
            NS(NodeId_get_device_id)( node ) );
}


NS(arch_status_t) NS(NodeId_extract_node_id_str_from_config_str)(
    NS(arch_size_t) const capacity, char* SIXTRL_RESTRICT node_id_str,
    char const* SIXTRL_RESTRICT config_str )
{
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( node_id_str != SIXTRL_NULLPTR ) &&
        ( capacity > ( NS(arch_size_t) )0u ) &&
        ( config_str != SIXTRL_NULLPTR ) )
    {
        NS(node_id_str_fmt_t) format = NS(NODE_ID_STR_FORMAT_ILLEGAL);

        char const* config_str_begin_pos = config_str;
        char const* begin_pos = SIXTRL_NULLPTR;
        char const* end_pos = SIXTRL_NULLPTR;

        NS(arch_size_t) const config_str_len = strlen( config_str );
        char const* config_str_end_pos = config_str + config_str_len;

        while( ( config_str_begin_pos != config_str_end_pos ) &&
               ( isspace( *config_str_begin_pos ) ) )
        {
            ++config_str_begin_pos;
        }

        if( config_str_begin_pos == config_str_end_pos )
        {
            return status;
        }

        format = NS(NodeId_identify_format_from_node_id_str)(
                config_str_begin_pos );

        if( format != NS(NODE_ID_STR_FORMAT_ILLEGAL) )
        {
            char const* semicolon_pos = strchr( config_str, ';' );
            char const* eostring_pos = strchr( config_str, '\0' );

            SIXTRL_ASSERT( eostring_pos != SIXTRL_NULLPTR );

            if( ( semicolon_pos != SIXTRL_NULLPTR ) &&
                ( eostring_pos != SIXTRL_NULLPTR ) &&
                ( ( uintptr_t )semicolon_pos < ( uintptr_t )eostring_pos ) )
            {
                end_pos = semicolon_pos;
            }
            else if( eostring_pos != SIXTRL_NULLPTR )
            {
                end_pos = eostring_pos;
            }

            if( ( config_str_begin_pos != SIXTRL_NULLPTR ) &&
                ( end_pos != SIXTRL_NULLPTR ) )
            {
                char const* it = config_str_begin_pos;

                while( ( it != end_pos ) &&
                       ( !isspace( *it ) ) && ( isprint( *it ) ) )
                {
                    ++it;
                }

                if( it != end_pos )
                {
                    end_pos = it;
                }

                begin_pos = config_str_begin_pos;
            }
        }

        if( ( begin_pos != SIXTRL_NULLPTR ) && ( end_pos != SIXTRL_NULLPTR ) &&
            ( ( uintptr_t )begin_pos < ( uintptr_t )end_pos ) )
        {
            NS(arch_size_t) const len = end_pos - begin_pos;

            if( len < capacity )
            {
                memcpy( node_id_str, begin_pos, len );
                memset( node_id_str + len, '\0', capacity - len );
                status = NS(ARCH_STATUS_SUCCESS);
            }
        }
    }

    return status;
}

/* end: sixtracklib/common/control/node_id.c */
