#ifndef SIXTRACKLIB_TESTS_TESTLIB_IMPL_GENERIC_OBJECT_TYPE_H__
#define SIXTRACKLIB_TESTS_TESTLIB_IMPL_GENERIC_OBJECT_TYPE_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>
    #if !defined( _GPUCODE )
        #include <stdio.h>
    #endif /* !defined( _GPUCODE ) */
    #include <limits.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/_impl/definitions.h"
    #include "sixtracklib/common/impl/buffer_type.h"
    #include "sixtracklib/testlib/impl/generic_obj_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE )

SIXTRL_FN SIXTRL_STATIC void NS(GenericObj_fprint)(
    FILE* SIXTRL_RESTRICT fp,
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj)
        *const SIXTRL_RESTRICT gen_obj );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GENOBJ_DATAPTR_DEC NS(GenericObj)*
NS(GenericObj_new)( SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(object_type_id_t) const type_id,
    NS(buffer_size_t) const num_d_values,
    NS(buffer_size_t) const num_e_values );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GENOBJ_DATAPTR_DEC NS(GenericObj)*
NS(GenericObj_add)( SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(object_type_id_t) const type_id,
    NS(buffer_size_t) const num_d_values,
    NS(buffer_size_t) const num_e_values,
    SIXTRL_INT32_T const a_value, SIXTRL_REAL_T const b_value,
    SIXTRL_GENOBJ_ARGPTR_DEC  SIXTRL_REAL_T const* SIXTRL_RESTRICT c_values,
    SIXTRL_GENOBJ_DATAPTR_DEC SIXTRL_UINT8_T* SIXTRL_RESTRICT d_values,
    SIXTRL_GENOBJ_DATAPTR_DEC SIXTRL_REAL_T*  SIXTRL_RESTRICT e_values );

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE )
#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/testlib/impl/generic_obj_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */
#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE )

SIXTRL_INLINE void NS(GenericObj_fprint)( FILE* SIXTRL_RESTRICT fp,
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj)
        *const SIXTRL_RESTRICT gen_obj )
{
    typedef SIXTRL_UINT64_T u64_t;
    SIXTRL_STATIC_VAR u64_t const ZERO_N = ( u64_t )0u;

    if( ( fp != SIXTRL_NULLPTR ) && ( gen_obj != SIXTRL_NULLPTR ) )
    {
        fprintf( fp,
                "NS(GenericObj) : type_id      = %16d\r\n"
                "NS(GenericObj) : a            = %16d\r\n"
                "NS(GenericObj) : b            = %16.8f\r\n"
                "NS(GenericObj) : c            = "
                "[ %16.8f, %16.8f, %16.8f, %16.8f ]\r\n"
                "NS(GenericObj) : num_d_values = %16d\r\n"
                "NS(GenericObj) : d            = ",
                ( int )gen_obj->type_id, ( int )gen_obj->a, gen_obj->b,
                gen_obj->c[ 0 ], gen_obj->c[ 1 ], gen_obj->c[ 2 ],
                gen_obj->c[ 3 ], ( int )gen_obj->num_d_values );

        if( gen_obj->d != SIXTRL_NULLPTR )
        {
            if( gen_obj->num_d_values > ZERO_N )
            {
                u64_t jj = ZERO_N;
                u64_t ii = jj++;
                u64_t const nn = ( u64_t )gen_obj->num_d_values;

                fprintf( fp, "[ " );

                for( ; ii < nn ; ++ii, ++jj )
                {
                    if( jj < nn )
                    {
                        fprintf( fp, "%16d , ", ( int )gen_obj->d[ ii ] );
                    }
                    else
                    {
                        fprintf( fp, "%16d ]", ( int )gen_obj->d[ ii ] );
                    }
                }
            }
            else
            {
                fprintf( fp, "[ ]" );
            }
        }
        else
        {
            fprintf( fp, "0x00000000" );
        }

        fprintf( fp,
                 "\r\n"
                 "NS(GenericObj) : num_e_values = %16d\r\n"
                 "NS(GenericObj) : e            = ",
                ( int )gen_obj->num_e_values );

        if( gen_obj->e != SIXTRL_NULLPTR )
        {
            if( gen_obj->num_e_values > ZERO_N )
            {
                u64_t jj = ZERO_N;
                u64_t ii = jj++;
                u64_t const nn = ( u64_t )gen_obj->num_e_values;

                fprintf( fp, "[ " );

                for( ; ii < nn ; ++ii, ++jj )
                {
                    if( jj < nn )
                    {
                        fprintf( fp, "%16.8f , ", gen_obj->e[ ii ] );
                    }
                    else
                    {
                        fprintf( fp, "%16.8f ]", gen_obj->e[ ii ] );
                    }
                }
            }
            else
            {
                fprintf( fp, "[ ]" );
            }
        }
        else
        {
            fprintf( fp, "0x00000000" );
        }

        fprintf( fp, "\r\n\r\n" );
    }

    return;
}

SIXTRL_INLINE SIXTRL_GENOBJ_DATAPTR_DEC NS(GenericObj)* NS(GenericObj_new)(
    SIXTRL_ARGPTR_DEC struct NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(object_type_id_t) const type_id,
    NS(buffer_size_t)    const num_d_values,
    NS(buffer_size_t)    const num_e_values )
{
    typedef NS(buffer_size_t)                           buf_size_t;
    typedef SIXTRL_GENOBJ_DATAPTR_DEC NS(GenericObj)*   ptr_obj_t;

    ptr_obj_t ptr_gen_obj  = SIXTRL_NULLPTR;

    if( buffer != SIXTRL_NULLPTR )
    {
        SIXTRL_STATIC_VAR unsigned char const ZERO = ( unsigned char )0;
        SIXTRL_STATIC_VAR buf_size_t const ZERO_SIZE = ( buf_size_t )0u;

        buf_size_t num_dataptrs = ( buf_size_t )0u;

        /* TODO: Find out what to do if SIXTRL_ARGPTR_DEC is for example
         *       in OpenCL __global -> then we can't set them locally! */

        buf_size_t offsets[]    = { ZERO_SIZE, ZERO_SIZE };
        buf_size_t sizes[]      = { ZERO_SIZE, ZERO_SIZE };
        buf_size_t counts[]     = { ZERO_SIZE, ZERO_SIZE };

        NS(GenericObj) temp;
        SIXTRACKLIB_SET_VALUES( unsigned char, &temp, sizeof( temp ), ZERO );
        NS(GenericObj_preset)( &temp );

        temp.type_id      = type_id;
        temp.num_d_values = num_d_values;
        temp.num_e_values = num_e_values;

        num_dataptrs = NS(GenericObj_get_num_dataptrs)( &temp );
        SIXTRL_ASSERT( num_dataptrs <= ( buf_size_t )2u );

        if( num_dataptrs == ( buf_size_t )2u )
        {
            SIXTRL_ASSERT( num_d_values > ZERO_SIZE );
            SIXTRL_ASSERT( num_e_values > ZERO_SIZE );

            offsets[ 0 ] = offsetof( NS(GenericObj), d );
            offsets[ 1 ] = offsetof( NS(GenericObj), e );

            sizes[ 0 ]   = sizeof( SIXTRL_UINT8_T );
            sizes[ 1 ]   = sizeof( SIXTRL_REAL_T  );

            counts[ 0 ]  = num_d_values;
            counts[ 1 ]  = num_e_values;
        }
        else if( num_dataptrs == ( buf_size_t )1u )
        {
            SIXTRL_ASSERT(
                ( ( num_d_values >  ZERO_SIZE ) &&
                  ( num_e_values == ZERO_SIZE ) ) ||
                ( ( num_d_values == ZERO_SIZE ) &&
                  ( num_e_values >  ZERO_SIZE ) ) );

            if( num_d_values > ZERO_SIZE )
            {
                offsets[ 0 ] = offsetof( NS(GenericObj), d );
                sizes[ 0 ]   = sizeof( SIXTRL_UINT8_T );
                counts[ 0 ]  = num_d_values;
            }
            else
            {
                offsets[ 0 ] = offsetof( NS(GenericObj), e );
                sizes[ 0 ]   = sizeof( SIXTRL_REAL_T );
                counts[ 0 ]  = num_e_values;
            }
        }

        if( num_dataptrs > ZERO_SIZE )
        {
            ptr_gen_obj = ( ptr_obj_t )( uintptr_t )NS(Object_get_begin_addr)(
                NS(Buffer_add_object)( buffer, &temp, sizeof( temp ), type_id,
                    num_dataptrs, offsets, sizes, counts ) );
        }
        else
        {
            ptr_gen_obj = ( ptr_obj_t )( uintptr_t )NS(Object_get_begin_addr)(
                NS(Buffer_add_object)( buffer, &temp, sizeof( temp ), type_id,
                    ZERO_SIZE, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
                        SIXTRL_NULLPTR ) );
        }
    }

    return ptr_gen_obj;
}

SIXTRL_INLINE SIXTRL_GENOBJ_DATAPTR_DEC NS(GenericObj)* NS(GenericObj_add)(
    SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(object_type_id_t) const type_id,
    NS(buffer_size_t) const num_d_values,
    NS(buffer_size_t) const num_e_values,
    SIXTRL_INT32_T const a_value, SIXTRL_REAL_T const b_value,
    SIXTRL_GENOBJ_ARGPTR_DEC  SIXTRL_REAL_T const* SIXTRL_RESTRICT c_values,
    SIXTRL_GENOBJ_DATAPTR_DEC SIXTRL_UINT8_T* SIXTRL_RESTRICT d_values,
    SIXTRL_GENOBJ_DATAPTR_DEC SIXTRL_REAL_T*  SIXTRL_RESTRICT e_values )
{
    typedef NS(buffer_size_t)                           buf_size_t;
    typedef SIXTRL_GENOBJ_DATAPTR_DEC NS(GenericObj)*   ptr_obj_t;

    ptr_obj_t ptr_gen_obj  = SIXTRL_NULLPTR;

    if( buffer != SIXTRL_NULLPTR )
    {
        SIXTRL_STATIC_VAR unsigned char const ZERO = ( unsigned char )0;
        SIXTRL_STATIC_VAR buf_size_t const ZERO_SIZE = ( buf_size_t )0u;

        buf_size_t num_dataptrs = ( buf_size_t )0u;

        /* TODO: Find out what to do if SIXTRL_ARGPTR_DEC is for example
         *       in OpenCL __global -> then we can't set them locally! */

        buf_size_t offsets[]    = { ZERO_SIZE, ZERO_SIZE };
        buf_size_t sizes[]      = { ZERO_SIZE, ZERO_SIZE };
        buf_size_t counts[]     = { ZERO_SIZE, ZERO_SIZE };

        NS(GenericObj) temp;
        SIXTRACKLIB_SET_VALUES( unsigned char, &temp, sizeof( temp ), ZERO );

        temp.type_id = type_id;
        temp.a       = a_value;
        temp.b       = b_value;

        SIXTRACKLIB_COPY_VALUES( SIXTRL_REAL_T, &temp.c[ 0 ], c_values, 4u );

        temp.num_d_values = num_d_values;
        temp.d            = d_values;
        temp.num_e_values = num_e_values;
        temp.e            = e_values;

        num_dataptrs = NS(GenericObj_get_num_dataptrs)( &temp );
        SIXTRL_ASSERT( num_dataptrs <= ( buf_size_t )2u );

        if( num_dataptrs == ( buf_size_t )2u )
        {
            SIXTRL_ASSERT( num_d_values > ZERO_SIZE );
            SIXTRL_ASSERT( num_e_values > ZERO_SIZE );

            offsets[ 0 ] = offsetof( NS(GenericObj), d );
            offsets[ 1 ] = offsetof( NS(GenericObj), e );

            sizes[ 0 ]   = sizeof( SIXTRL_UINT8_T );
            sizes[ 1 ]   = sizeof( SIXTRL_REAL_T  );

            counts[ 0 ]  = num_d_values;
            counts[ 1 ]  = num_e_values;
        }
        else if( num_dataptrs == ( buf_size_t )1u )
        {
            SIXTRL_ASSERT(
                ( ( num_d_values >  ZERO_SIZE ) &&
                  ( num_e_values == ZERO_SIZE ) &&
                  ( e_values     == SIXTRL_NULLPTR ) ) ||
                ( ( num_d_values == ZERO_SIZE ) &&
                  ( num_e_values >  ZERO_SIZE ) &&
                  ( d_values     == SIXTRL_NULLPTR ) ) );

            if( num_d_values > ZERO_SIZE )
            {
                offsets[ 0 ] = offsetof( NS(GenericObj), d );
                sizes[ 0 ]   = sizeof( SIXTRL_UINT8_T );
                counts[ 0 ]  = num_d_values;
            }
            else
            {
                offsets[ 0 ] = offsetof( NS(GenericObj), e );
                sizes[ 0 ]   = sizeof( SIXTRL_REAL_T );
                counts[ 0 ]  = num_e_values;
            }
        }

        if( num_dataptrs > ZERO_SIZE )
        {
            ptr_gen_obj = ( ptr_obj_t )( uintptr_t )NS(Object_get_begin_addr)(
                NS(Buffer_add_object)( buffer, &temp, sizeof( temp ), type_id,
                    num_dataptrs, offsets, sizes, counts ) );
        }
        else
        {
            ptr_gen_obj = ( ptr_obj_t )( uintptr_t )NS(Object_get_begin_addr)(
                NS(Buffer_add_object)( buffer, &temp, sizeof( temp ), type_id,
                    ZERO_SIZE, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
                        SIXTRL_NULLPTR ) );
        }
    }

    return ptr_gen_obj;
}

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_TESTS_TESTLIB_IMPL_GENERIC_OBJECT_TYPE_H__ */

/* end: tests/sixtracklib/testlib/generic_buffer_obj.h */
