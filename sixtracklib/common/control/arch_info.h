#ifndef SIXTRACKLIB_COMMON_CONTROL_ARCH_INFO_H__
#define SIXTRACKLIB_COMMON_CONTROL_ARCH_INFO_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/arch_info.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

SIXTRL_STATIC SIXTRL_FN bool NS(ArchInfo_is_arch_id_valid)(
    NS(arch_id_t) const arch_id );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ArchInfo_get_arch_string_for_arch_id)( NS(arch_id_t) const arch_id,
    NS(arch_size_t) const arch_str_capacity,
    SIXTRL_ARGPTR_DEC char* SIXTRL_RESTRICT arch_str_begin );

SIXTRL_STATIC SIXTRL_FN NS(arch_id_t) NS(ArchInfo_get_arch_id_from_arch_str)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT arch_str );

SIXTRL_STATIC SIXTRL_FN NS(arch_size_t) NS(ArchInfo_string_length)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT arch_str );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ArchInfo_string_fill)(
    SIXTRL_ARGPTR_DEC char* SIXTRL_RESTRICT arch_str_begin,
    NS(arch_size_t) const arch_str_capacity,
    char const fill_char );

SIXTRL_STATIC SIXTRL_FN SIXTRL_ARGPTR_DEC char const*
NS(ArchInfo_string_find_next_char)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT haystack,
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT start_pos,
    char const needle, NS(arch_size_t) const max_chars_to_search );

SIXTRL_STATIC SIXTRL_FN SIXTRL_ARGPTR_DEC char const*
NS(ArchInfo_string_find_next_str)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT haystack,
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT start_pos,
    SIXTRL_ARGPTR_DEC char const* needle,
    NS(arch_size_t) const max_chars_to_search );

SIXTRL_STATIC SIXTRL_FN bool NS(ArchInfo_string_starts_with_number)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT str );


SIXTRL_STATIC SIXTRL_FN int NS(ArchInfo_string_compare)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT lhs_str,
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT rhs_str,
    NS(arch_size_t) const max_cmp_characters );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ArchInfo_string_copy)(
    SIXTRL_ARGPTR_DEC char* SIXTRL_RESTRICT destination,
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT source,
    NS(arch_size_t) const destination_capacity );

SIXTRL_STATIC SIXTRL_FN NS(arch_size_t) NS(ArchInfo_string_to_uint)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT str_begin,
    NS(arch_size_t) const max_chars_to_parse, NS(arch_size_t) const base,
    SIXTRL_ARGPTR_DEC NS(arch_status_t)* SIXTRL_RESTRICT ptr_arch_status );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_ARGPTR_DEC NS(ArchInfo)*
NS(ArchInfo_preset)(
    SIXTRL_ARGPTR_DEC NS(ArchInfo)* SIXTRL_RESTRICT arch_info );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_ARGPTR_DEC NS(ArchInfo)*
NS(ArchInfo_create)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_ARGPTR_DEC NS(ArchInfo)* NS(ArchInfo_new)(
    NS(arch_id_t) const arch_id, char const* SIXTRL_RESTRICT arch_str );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(ArchInfo_delete)(
    SIXTRL_ARGPTR_DEC NS(ArchInfo)* SIXTRL_RESTRICT arch_info );


SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_id_t) NS(ArchInfo_get_arch_id)(
    SIXTRL_ARGPTR_DEC const NS(ArchInfo) *const SIXTRL_RESTRICT arch_info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ArchInfo_has_arch_string)(
    SIXTRL_ARGPTR_DEC const NS(ArchInfo) *const SIXTRL_RESTRICT arch_info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(ArchInfo_get_arch_string)(
    SIXTRL_ARGPTR_DEC const NS(ArchInfo) *const SIXTRL_RESTRICT arch_info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ArchInfo_is_compatible_with)(
    SIXTRL_ARGPTR_DEC const NS(ArchInfo) *const SIXTRL_RESTRICT arch_info,
    SIXTRL_ARGPTR_DEC const NS(ArchInfo) *const SIXTRL_RESTRICT other );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ArchInfo_is_compatible_with_arch_id)(
    SIXTRL_ARGPTR_DEC const NS(ArchInfo) *const SIXTRL_RESTRICT arch_info,
    NS(arch_id_t) const other_arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ArchInfo_is_identical_to)(
    SIXTRL_ARGPTR_DEC const NS(ArchInfo) *const SIXTRL_RESTRICT arch_info,
    SIXTRL_ARGPTR_DEC const NS(ArchInfo) *const SIXTRL_RESTRICT other );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ArchInfo_is_identical_to_arch_id)(
    SIXTRL_ARGPTR_DEC const NS(ArchInfo) *const SIXTRL_RESTRICT arch_info,
    NS(arch_id_t) const other_arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(ArchInfo_reset)(
    SIXTRL_ARGPTR_DEC NS(ArchInfo)* SIXTRL_RESTRICT arch_info,
    NS(arch_id_t) const arch_id, char const* SIXTRL_RESTRICT arch_str );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(ArchInfo_reset_to_initial_values)(
    SIXTRL_ARGPTR_DEC NS(ArchInfo)* SIXTRL_RESTRICT arch_info );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ctrl_status_t)
NS(ArchBase_sanitize_arch_str_inplace)( char* SIXTRL_RESTRICT arch_str,
    NS(buffer_size_t) const arch_str_capacity );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ctrl_status_t)
NS(ArchInfo_sanitize_arch_str)( const char *const SIXTRL_RESTRICT arch_str,
    char* SIXTRL_RESTRICT sanitized_arch_str,
    NS(buffer_size_t) const sanitized_arch_str_capacity );

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */



#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

SIXTRL_INLINE bool NS(ArchInfo_is_arch_id_valid)(
    NS(arch_id_t) const arch_id )
{
    return ( ( arch_id == SIXTRL_ARCHITECTURE_CPU ) ||
             ( arch_id == SIXTRL_ARCHITECTURE_OPENCL ) ||
             ( arch_id == SIXTRL_ARCHITECTURE_CUDA ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(ArchInfo_get_arch_string_for_arch_id)(
    NS(arch_id_t) const arch_id,
    NS(arch_size_t) const arch_str_capacity,
    SIXTRL_ARGPTR_DEC char* SIXTRL_RESTRICT arch_str_begin )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( arch_str_begin != SIXTRL_NULLPTR ) &&
        ( arch_str_capacity > ( NS(arch_size_t) )0u ) )
    {
        status = NS(ArchInfo_string_fill)(
            arch_str_begin, arch_str_capacity, '\0' );

        if( status == SIXTRL_ARCH_STATUS_SUCCESS )
        {
            switch( arch_id )
            {
                case SIXTRL_ARCHITECTURE_CPU:
                {
                    SIXTRL_ASSERT( NS(ArchInfo_string_length)(
                        SIXTRL_ARCHITECTURE_CPU_STR ) < arch_str_capacity );

                    status = NS(ArchInfo_string_copy)( arch_str_begin,
                        SIXTRL_ARCHITECTURE_CPU_STR, arch_str_capacity );

                    break;
                }

                case SIXTRL_ARCHITECTURE_OPENCL:
                {
                    SIXTRL_ASSERT( NS(ArchInfo_string_length)(
                        SIXTRL_ARCHITECTURE_OPENCL_STR) < arch_str_capacity );

                    status = NS(ArchInfo_string_copy)( arch_str_begin,
                        SIXTRL_ARCHITECTURE_OPENCL_STR, arch_str_capacity );

                    break;
                }

                case SIXTRL_ARCHITECTURE_CUDA:
                {
                    SIXTRL_ASSERT( NS(ArchInfo_string_length)(
                        SIXTRL_ARCHITECTURE_CUDA_STR) < arch_str_capacity );

                    status = NS(ArchInfo_string_copy)( arch_str_begin,
                        SIXTRL_ARCHITECTURE_CUDA_STR, arch_str_capacity );

                    break;
                }

                default:
                {
                    status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
                }
            };
        }
    }

    return status;
}

SIXTRL_INLINE NS(arch_id_t) NS(ArchInfo_get_arch_id_from_arch_str)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT arch_str )
{
    NS(arch_id_t) arch_id = SIXTRL_ARCHITECTURE_ILLEGAL;
    NS(arch_size_t) const arch_str_capacity = ( NS(arch_size_t) )16u;
    NS(arch_size_t) str_length = ( NS(arch_size_t) )0u;

    SIXTRL_ARGPTR_DEC char temp_arch_str[ 16 ];

    NS(arch_status_t) status = NS(ArchInfo_string_copy)(
        temp_arch_str, SIXTRL_ARCHITECTURE_CPU_STR, arch_str_capacity );

    if( status == SIXTRL_ARCH_STATUS_SUCCESS )
    {
        str_length = NS(ArchInfo_string_length)( temp_arch_str );
        SIXTRL_ASSERT( str_length > ( NS(arch_size_t ) )0u );
        SIXTRL_ASSERT( str_length < arch_str_capacity );

        if( 0 == NS(ArchInfo_string_compare)(
                arch_str, temp_arch_str, str_length ) )
        {
            arch_id = ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_CPU;
        }
    }

    if( ( arch_id == arch_id = ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_ILLEGAL ) &&
        ( status == SIXTRL_ARCH_STATUS_SUCCESS ) )
    {
        status = NS(ArchInfo_string_copy)(
            temp_arch_str, SIXTRL_ARCHITECTURE_OPENCL_STR, arch_str_capacity );
        SIXTRL_ASSERT( status == SIXTRL_ARCH_STATUS_SUCCESS );

        str_length = NS(ArchInfo_string_length)( temp_arch_str );
        SIXTRL_ASSERT( str_length > ( NS(arch_size_t) )0u );
        SIXTRL_ASSERT( str_length < arch_str_capacity );

        if( 0 == NS(ArchInfo_string_compare)(
                arch_str, temp_arch_str, str_length ) )
        {
            arch_id = arch_id = ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_OPENCL;
        }
    }

    if( ( arch_id == arch_id = ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_ILLEGAL ) &&
        ( status == SIXTRL_ARCH_STATUS_SUCCESS ) )
    {
        status = NS(ArchInfo_string_copy)(
            temp_arch_str, SIXTRL_ARCHITECTURE_CUDA_STR, arch_str_capacity );
        SIXTRL_ASSERT( status == SIXTRL_ARCH_STATUS_SUCCESS );

        str_length = NS(ArchInfo_string_length)( temp_arch_str );
        SIXTRL_ASSERT( str_length > ( NS(arch_size_t) )0u );
        SIXTRL_ASSERT( str_length < arch_str_capacity );

        if( 0 == NS(ArchInfo_string_compare)(
                arch_str, temp_arch_str, str_length ) )
        {
            arch_id = arch_id = ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_CUDA;
        }
    }

    if( status != SIXTRL_ARCH_STATUS_SUCCESS )
    {
        arch_id = arch_id = ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_ILLEGAL;
    }

    return arch_id;
}

SIXTRL_INLINE NS(arch_size_t) NS(ArchInfo_string_length)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT arch_str )
{
    NS(arch_size_t) str_length = ( NS(arch_size_t) )0u;

    if( arch_str != SIXTRL_NULLPTR )
    {
        SIXTRL_ARGPTR_DEC char const* it = arch_str;

        while( ( it != SIXTRL_NULLPTR ) && ( *it != '\0' ) )
        {
            ++str_length;
        }
    }

    return str_length;
}

SIXTRL_INLINE int NS(ArchInfo_string_compare)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT lhs_str,
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT rhs_str,
    NS(arch_size_t) const max_cmp_characters )
{
    int cmp_result = -1;

    if( ( lhs_str != SIXTRL_NULLPTR ) && ( rhs_str != SIXTRL_NULLPTR ) &&
        ( max_cmp_characters > ( NS(arch_size_t) )0u ) )
    {
        SIXTRL_ARGPTR_DEC char const* lhs_it  = lhs_str;
        SIXTRL_ARGPTR_DEC char const* lhs_end = SIXTRL_NULLPTR;
        SIXTRL_ARGPTR_DEC char const* rhs_it  = rhs_str;

        NS(arch_size_t) const lhs_len = NS(ArchInfo_string_length)( lhs_str );
        NS(arch_size_t) const rhs_len = NS(ArchInfo_string_length)( rhs_str );

        NS(arch_size_t) cmp_len = ( lhs_len <= rhs_len ) ? lhs_len : rhs_len;

        if( cmp_len > max_cmp_characters )
        {
            cmp_len = max_cmp_characters;
        }

        lhs_end = lhs_it + cmp_len;
        cmp_result = 0;

        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
        {
            if( ( *lhs_it != '\0' ) && ( *rhs_it != '\0' ) )
            {
                int const lhs_val = ( int )*lhs_it;
                int const rhs_val = ( int )*rhs_it;

                if( lhs_val != rhs_val )
                {
                    cmp_value = ( lhs_val > rhs_val ) ? -1 : +1;
                    break;
                }
            }
            else if( *lhs_it == '\0' )
            {
                cmp_result = -1;
                break;
            }
            else if( *rhs_it == '\0' )
            {
                cmp_result = +1;
                break;
            }
            else
            {
                /* Should never get here */
                cmp_result = -1;
                break;
            }
        }
    }
    else if( ( rhs_str != SIXTRL_NULLPTR ) &&
             ( max_cmp_characters > ( NS(arch_size_t) )0u ) )
    {
        cmp_result = +1;
    }

    return cmp_result;
}

SIXTRL_INLINE NS(arch_status_t) NS(ArchInfo_string_copy)(
    SIXTRL_ARGPTR_DEC char* SIXTRL_RESTRICT destination,
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT source,
    NS(arch_size_t) const destination_capacity )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
    NS(arch_size_t) const src_len = NS(ArchInfo_string_length)( source );

    if( ( source != SIXTRL_NULLPTR ) && ( destination != SIXTRL_NULLPTR ) &&
        ( destination != source ) && ( src_len < destination ) &&
        ( src_len > ( NS(arch_size_t) )0u ) )
    {
        SIXTRACKLIB_COPY_VALUES( char, destination, source, src_len );
        SIXTRACKLIB_SET_VALUES( char, destination + src_len,
                                destination_capacity - src_len, '\0' );

        status = SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}


SIXTRL_INLINE NS(arch_status_t) NS(ArchInfo_string_fill)(
    SIXTRL_ARGPTR_DEC char* SIXTRL_RESTRICT arch_str_begin,
    NS(arch_size_t) const arch_str_capacity, char const fill_char )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( arch_str_begin != SIXTRL_NULLPTR ) &&
        ( arch_str_capacity > ( NS(arch_size_t) )0u ) )
    {
        SIXTRL_ARGPTR_DEC char* ch_it = arch_str_begin;
        SIXTRL_ARGPTR_DEC char* const ch_end = ch_it + arch_str_capacity;

        for( ; ch_it != ch_end ; ++ch_it )
        {
            *ch_it = fill_char;
        }

        status = SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE SIXTRL_ARGPTR_DEC char const* NS(ArchInfo_string_find_next_char)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT haystack,
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT start_pos,
    char const needle, NS(arch_size_t) const max_chars_to_search )
{
    SIXTRL_ARGPTR_DEC char const* pos = SIXTRL_NULLPTR;

    if( ( haystack != SIXTRL_NULLPTR ) &&
        ( max_chars_to_search > ( NS(arch_size_t) )0u ) &&
        ( NS(ArchInfo_string_length)( haystack ) <= max_chars_to_search ) )
    {
        SIXtRL_ARGPTR_DEC end_pos = haystack + max_chars_to_search;

        if( start_pos == SIXTRL_NULLPTR )
        {
            start_pos = haystack;
        }

        if( ( ( uintptr_t )haystack > ( uintptr_t )start_pos ) ||
            ( ( uintptr_t )start_pos >= ( uintptr_t )end_pos ) )
        {
            return pos;
        }

        while( start_pos != end_pos )
        {
            if( *start_pos == '\0' ) break;
            if( *start_pos == needle )
            {
                pos = start_pos;
                break;
            }

            ++start_pos;
        }
    }

    return pos;
}

SIXTRL_INLINE SIXTRL_ARGPTR_DEC char const* NS(ArchInfo_string_find_next_str)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT haystack,
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT start_pos,
    SIXTRL_ARGPTR_DEC char const* needle,
    NS(arch_size_t) const max_chars_to_search )
{
    SIXTRL_ARGPTR_DEC char const* pos = SIXTRL_NULLPTR;
    NS(arch_size_t) const needle_len = NS(ArchInfo_string_length)( needle );

    if( ( needle_len > ( NS(arch_size_t) )0u ) &&
        ( needle_len <= max_chars_to_search ) &&
        ( haystack != SIXTRL_NULLPTR ) && ( needle != SIXTRL_NULLPTR ) )
    {
        SIXTRL_ARGPTR_DEC char const* end_pos = haystack + max_chars_to_search;

        char const needle_begin = *needle;

        do
        {
            pos = NS(ArchInfo_string_find_next_char)( haystack, start_pos,
                needle_begin, max_chars_to_search );

            if( pos != SIXTRL_NULLPTR )
            {
                if( ( uintptr_t )( pos + needle_len ) < ( uintptr_t )end_pos )
                {
                    if( 0 == NS(ArchInfo_string_compare)(
                            pos, needle, needle_len ) )
                    {
                        break;
                    }
                    else if( ( uintptr_t )( pos + 1 ) != ( uintptr_t )end_pos )
                    {
                        start_pos = pos + 1;
                        pos = SIXTRL_NULLPTR;
                    }
                    else
                    {
                        pos = SIXTRL_NULLPTR;
                        break;
                    }
                }
            }
        }
        while( pos != SIXTRL_NULLPTR );
    }

    return pos;
}

SIXTRL_INLINE bool NS(ArchInfo_string_starts_with_number)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT str )
{
    bool starts_with_number = false;

    if( str != SIXTRL_NULLPTR )
    {
        NS(arch_size_t) const str_len = NS(ArchInfo_string_length)( str );

        SIXTRL_ARGPTR_DEC char const* it = str;
        SIXTRL_ARGPTR_DEC char const* end = str + str_len;

        while( it != end )
        {
            char const c = *it;

            if( ( c == '+'  ) || ( c == '-'  ) || ( c == ' '  ) ||
                ( c == '\t' ) || ( c == '\r' ) || ( c == '\n' ) )
            {
                ++it;
            }
            else
            {
                if( ( c == '0' ) || ( c == '1' ) || ( c == '2' ) ||
                    ( c == '3' ) || ( c == '4' ) || ( c == '5' ) ||
                    ( c == '6' ) || ( c == '7' ) || ( c == '8' ) ||
                    ( c == '9' ) )
                {
                    starts_with_number = true;
                }

                break;
            }
        }

    }

    return starts_with_number;
}

NS(arch_size_t) NS(ArchInfo_string_to_uint)(
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT str_begin,
    NS(arch_size_t) const max_chars_to_parse, NS(arch_size_t) const base,
    SIXTRL_ARGPTR_DEC NS(arch_status_t)* SIXTRL_RESTRICT ptr_status )
{
    NS(arch_size_t) result = ( NS(arch_size_t) )0u;
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( str_begin != SIXTRL_NULLPTR ) &&
        ( max_chars_to_parse > ( NS(arch_size_t) )0u ) &&
        ( max_chars_to_parse <= NS(ArchInfo_string_length)( str_begin ) ) &&
        ( base > ( NS(arch_size_t) )0u ) )
    {
        SIXTRL_ARGPTR_DEC char const* it = str_begin;
        SIXTRL_ARGPTR_DEC char const* begin_pos = SIXTRL_NULLPTR;
        SIXTRL_ARGPTR_DEC char const* end_pos = it + max_chars_to_parse;

        NS(arch_size_t) multiplier = ( NS(arch_size_t) )0u;
        NS(arch_size_t) num_digits = ( NS(arch_size_t) )0u;

        /*TODO: IMplement for other bases!!! */
        SIXTRL_ASSERT( ( base == ( NS(arch_size_t) )10u ) ||
                       ( base == ( NS(arch_size_t) )8u ) ||
                       ( base == ( NS(arch_size_t) )2u ) );

        for( ; it != end_pos ; ++it )
        {
            char const c = *it;

            if( ( begin_pos == SIXTRL_NULLPTR ) &&
                ( ( c == '+'  ) || ( c == ' '  ) ||
                  ( c == '\t' ) || ( c == '\r' ) || ( c == '\n' ) ) )
            {
                continue;
            }

            if( ( c == '0' ) || ( c == '1' ) || ( c == '2' ) || ( c == '3' ) ||
                ( c == '4' ) || ( c == '5' ) || ( c == '6' ) || ( c == '7' ) ||
                ( c == '8' ) || ( c == '9' ) )
            {
                if( begin_pos == SIXTRL_NULLPTR )
                {
                    begin_pos = it;
                    multiplier = ( NS(arch_size_t) )1u;
                }
                else
                {
                    multiplier *= base;
                }

                ++num_digits;
            }
            else
            {
                break;
            }
        }

        if( ( num_digits > ( NS(arch_size_t) )0u ) &&
            ( begin_pos != SIXTRL_NULLPTR ) )

        {
            SIXTRL_ASSERT( multiplier > ( NS(arch_size_t) )0u );
            SIXTRL_ASSERT( ( uintptr_t )end_pos >=
                           ( uintptr_t )( begin_pos + num_digits ) );

            it = begin_pos;
            end_pos = it + num_digits;

            status = SIXTRL_ARCH_STATUS_SUCCESS;

            for( ; it != end_pos ; ++it )
            {
                int const dist = ( int )( *it - '0' );

                if( ( base == ( NS(arch_size_t) )10u ) &&
                    ( dist >= 0 ) && ( dist < ( int )base ) )
                {
                    result += multiplier * ( NS(arch_size_t) )dist;
                    multiplier /= base;
                }
                else
                {
                    status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }
            }

            if( status != SIXTRL_ARCH_STATUS_SUCCESS )
            {
                result = ( NS(arch_size_t) )0u;
            }
        }
    }

    if( ptr_status != SIXTRL_NULLPTR )
    {
        *ptr_status |= status;
    }

    return result;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

#endif /* SIXTRACKLIB_COMMON_CONTROL_ARCH_INFO_H__ */

/* end: sixtracklib/common/control/arch_info.h */
