#ifndef SIXTRACKLIB_TESTS_TESTLIB_GENERIC_BUFFER_H__
#define SIXTRACKLIB_TESTS_TESTLIB_GENERIC_BUFFER_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>

    #if !defined( _GPUCODE )
        #include <stdio.h>
    #endif /* !defined( _GPUCODE ) */

    #include <stdlib.h>
    #include <string.h>
    #include <limits.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/_impl/definitions.h"
    #include "sixtracklib/common/impl/buffer_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_GENOBJ_ARGPTR_DEC )
    #define SIXTRL_GENOBJ_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_ARGPTR_DEC )
        #define SIXTRL_GENOBJ_ARGPTR_DEC SIXTRL_ARGPTR_DEC
    #else
        #define SIXTRL_GENOBJ_ARGPTR_DEC
    #endif /* defined( SIXTRL_ARGPTR_DEC ) */
#endif /* !defined( SIXTRL_GENOBJ_ARGPTR_DEC ) */

#if !defined( SIXTRL_GENOBJ_DATAPTR_DEC )
    #define SIXTRL_GENOBJ_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_DATAPTR_DEC )
        #define SIXTRL_GENOBJ_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else
        #define SIXTRL_GENOBJ_DATAPTR_DEC
    #endif /* defined( SIXTRL_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_GENOBJ_DATAPTR_DEC ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

typedef struct NS(GenericObj)
{
    NS(object_type_id_t) type_id                         SIXTRL_ALIGN( 8u );
    SIXTRL_INT32_T a                                     SIXTRL_ALIGN( 8u );
    SIXTRL_REAL_T b                                      SIXTRL_ALIGN( 8u );
    SIXTRL_REAL_T c[ 4 ]                                 SIXTRL_ALIGN( 8u );

    SIXTRL_UINT64_T num_d_values                         SIXTRL_ALIGN( 8u );
    SIXTRL_GENOBJ_DATAPTR_DEC SIXTRL_UINT8_T*
        SIXTRL_RESTRICT d                                SIXTRL_ALIGN( 8u );

    SIXTRL_UINT64_T num_e_values                         SIXTRL_ALIGN( 8u );
    SIXTRL_GENOBJ_DATAPTR_DEC SIXTRL_REAL_T*
        SIXTRL_RESTRICT e                                SIXTRL_ALIGN( 8u );
}
NS(GenericObj);

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(GenericObj_get_num_dataptrs)(
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const gen_obj );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GENOBJ_ARGPTR_DEC struct NS(GenericObj)*
    NS(GenericObj_preset)( SIXTRL_GENOBJ_ARGPTR_DEC
        NS(GenericObj)* SIXTRL_RESTRICT gen_obj );

SIXTRL_FN SIXTRL_STATIC bool NS(GenericObj_has_same_structure)(
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT lhs,
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT rhs );

SIXTRL_FN SIXTRL_STATIC int NS(GenericObj_compare)(
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT lhs,
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT rhs );

SIXTRL_FN SIXTRL_STATIC int NS(GenericObj_compare_with_treshold)(
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT lhs,
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT rhs,
    SIXTRL_REAL_T const treshold );

SIXTRL_FN SIXTRL_STATIC void NS(GenericObj_print)(
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT obj );

SIXTRL_FN SIXTRL_STATIC void NS(GenericObj_copy)(
    SIXTRL_GENOBJ_ARGPTR_DEC NS(GenericObj)* SIXTRL_RESTRICT destination,
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const
        SIXTRL_RESTRICT source );

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* *
 * ******         Implementation of inline functions                   ***** *
 * ************************************************************************* */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE  NS(buffer_size_t) NS(GenericObj_get_num_dataptrs)(
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const gen_obj )
{
    typedef NS(buffer_size_t) buf_size_t;

    NS(buffer_size_t) num_dataptrs = ( NS(buffer_size_t) )0;

    if( gen_obj != SIXTRL_NULLPTR )
    {
        if( ( gen_obj->d != SIXTRL_NULLPTR ) ||
            ( gen_obj->num_d_values > ( buf_size_t )0u ) )
        {
            ++num_dataptrs;
        }

        if( ( gen_obj->e != SIXTRL_NULLPTR ) ||
            ( gen_obj->num_e_values > ( buf_size_t )0u ) )
        {
            ++num_dataptrs;
        }
    }

    return num_dataptrs;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE  SIXTRL_GENOBJ_ARGPTR_DEC NS(GenericObj)*
    NS(GenericObj_preset)( SIXTRL_GENOBJ_ARGPTR_DEC
        NS(GenericObj)* SIXTRL_RESTRICT gen_obj )
{
    if( gen_obj != SIXTRL_NULLPTR )
    {
        gen_obj->a = ( SIXTRL_INT32_T )0u;
        gen_obj->b = ( SIXTRL_REAL_T )0.0;

        gen_obj->c[ 0 ] = gen_obj->c[ 1 ] =
        gen_obj->c[ 2 ] = gen_obj->c[ 3 ] = ( SIXTRL_REAL_T )0.0;

        gen_obj->d = SIXTRL_NULLPTR;
        gen_obj->num_d_values = ( SIXTRL_UINT64_T )0;

        gen_obj->e = SIXTRL_NULLPTR;
        gen_obj->num_e_values = ( SIXTRL_UINT64_T )0;
    }

    return gen_obj;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE  bool NS(GenericObj_has_same_structure)(
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT lhs,
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT rhs )
{
    bool has_same_structure = (
        ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( lhs->num_d_values == rhs->num_d_values ) &&
        ( lhs->num_e_values == rhs->num_e_values ) &&
        ( ( lhs->d != rhs->d ) ||
          ( ( lhs->d == SIXTRL_NULLPTR ) && ( rhs->d == SIXTRL_NULLPTR ) ) ) &&
        ( ( lhs->e != rhs->e ) ||
          ( ( lhs->e == SIXTRL_NULLPTR ) && ( rhs->e == SIXTRL_NULLPTR ) ) ) );

    return has_same_structure;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE  int NS(GenericObj_compare)(
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT lhs,
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT rhs )
{
    int compare = -1;

    if( NS(GenericObj_has_same_structure)( lhs, rhs ) )
    {
        SIXTRL_STATIC_VAR SIXTRL_UINT64_T const ZERO = ( SIXTRL_UINT64_T )0;

        compare = ( lhs->type_id == rhs->type_id )
            ? 0 : ( ( lhs->type_id >  rhs->type_id ) ? +1 : -1 );

        if( compare == 0 )
        {
            compare = ( lhs->a == rhs->a )
                ? 0 : ( ( lhs->a > rhs->a ) ? +1 : -1 );
        }

        if( compare == 0 )
        {
            compare = ( lhs->b > rhs->b )
                ? +1 : ( ( lhs->b < rhs->b ) ? -1 : 0 );
        }

        if( compare == 0 )
        {
            SIXTRL_UINT64_T ii = ZERO;

            for( ; ii < 4u ; ++ii )
            {
                if( lhs->c[ ii ] > rhs->c[ ii ] )
                {
                    compare = +1;
                    break;
                }
                else if( lhs->c[ ii ] < rhs->c[ ii ] )
                {
                    compare = -1;
                    break;
                }
            }
        }

        if( ( compare == 0 ) && ( lhs->num_d_values > ZERO ) &&
            ( lhs->d != SIXTRL_NULLPTR ) )
        {
            SIXTRL_UINT64_T ii = ZERO;
            SIXTRL_UINT64_T const num_d = lhs->num_d_values;

            SIXTRL_ASSERT( rhs->d != lhs->d );
            SIXTRL_ASSERT( rhs->d != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( rhs->num_d_values == num_d );

            for( ; ii < num_d ; ++ii )
            {
                if( lhs->d[ ii ] != rhs->d[ ii ] )
                {
                    compare = ( lhs->d[ ii ] > rhs->d[ ii ] ) ? +1 : -1;
                    break;
                }
            }
        }

        if( ( compare == 0 ) && ( lhs->num_e_values > ZERO ) &&
            ( lhs->e != SIXTRL_NULLPTR ) )
        {
            SIXTRL_UINT64_T ii = ZERO;
            SIXTRL_UINT64_T const num_e = lhs->num_e_values;

            SIXTRL_ASSERT( rhs->e != lhs->e );
            SIXTRL_ASSERT( rhs->e != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( rhs->num_e_values == num_e );

            for( ; ii < num_e ; ++ii )
            {
                if( lhs->e[ ii ] > rhs->e[ ii ] )
                {
                    compare = +1;
                    break;
                }
                else if( lhs->d[ ii ] < rhs->d[ ii ] )
                {
                    compare = -1;
                    break;
                }
            }
        }
    }

    return compare;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE  int NS(GenericObj_compare_with_treshold)(
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT lhs,
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const SIXTRL_RESTRICT rhs,
    SIXTRL_REAL_T const treshold )
{
    int compare = -1;

    typedef SIXTRL_REAL_T   real_t;
    typedef SIXTRL_UINT64_T u64_t;

    SIXTRL_STATIC_VAR u64_t  const ZERO      = ( u64_t  )0;
    SIXTRL_STATIC_VAR real_t const ZERO_REAL = ( real_t )0.0;

    if( ( NS(GenericObj_has_same_structure)( lhs, rhs ) ) &&
        ( treshold >= ZERO_REAL ) )
    {
        compare = ( lhs->type_id == rhs->type_id )
            ? 0 : ( ( lhs->type_id >  rhs->type_id ) ? +1 : -1 );

        if( compare == 0 )
        {
            compare = ( lhs->a == rhs->a )
                ? 0 : ( ( lhs->a > rhs->a ) ? +1 : -1 );
        }

        if( compare == 0 )
        {
            SIXTRL_REAL_T const diff = lhs->b - rhs->b;
            SIXTRL_REAL_T const abs_diff = ( diff >= ZERO_REAL ) ? diff : -diff;

            compare = ( abs_diff < treshold )
                ?  0 : ( ( diff > ZERO_REAL ) ? +1 : -1 );
        }

        if( compare == 0 )
        {
            SIXTRL_UINT64_T ii = ZERO;

            for( ; ii < 4u ; ++ii )
            {
                SIXTRL_REAL_T const diff = lhs->c[ ii ] - rhs->c[ ii ];
                SIXTRL_REAL_T const abs_diff =
                    ( diff >= ZERO_REAL ) ? diff : -diff;

                if( abs_diff >= treshold )
                {
                    compare = ( diff >= ZERO_REAL ) ? +1 : -1;
                    break;
                }
            }
        }

        if( ( compare == 0 ) && ( lhs->num_d_values > ZERO ) &&
            ( lhs->d != SIXTRL_NULLPTR ) )
        {
            SIXTRL_UINT64_T ii = ZERO;
            SIXTRL_UINT64_T const num_d = lhs->num_d_values;

            SIXTRL_ASSERT( rhs->d != lhs->d );
            SIXTRL_ASSERT( rhs->d != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( rhs->num_d_values == num_d );

            for( ; ii < num_d ; ++ii )
            {
                if( lhs->d[ ii ] != rhs->d[ ii ] )
                {
                    compare = ( lhs->d[ ii ] > rhs->d[ ii ] ) ? +1 : -1;
                    break;
                }
            }
        }

        if( ( compare == 0 ) && ( lhs->num_e_values > ZERO ) &&
            ( lhs->e != SIXTRL_NULLPTR ) )
        {
            SIXTRL_UINT64_T ii = ZERO;
            SIXTRL_UINT64_T const num_e = lhs->num_e_values;

            SIXTRL_ASSERT( rhs->e != lhs->e );
            SIXTRL_ASSERT( rhs->e != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( rhs->num_e_values == num_e );

            for( ; ii < num_e ; ++ii )
            {
                SIXTRL_REAL_T const diff = lhs->e[ ii ] - rhs->e[ ii ];
                SIXTRL_REAL_T const abs_diff =
                    ( diff >= ZERO_REAL ) ? diff : -diff;

                if( abs_diff >= treshold )
                {
                    compare = ( diff > ZERO_REAL ) ? +1 : -1;
                    break;
                }
            }
        }
    }

    return compare;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE  void NS(GenericObj_print)(
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj)
        *const SIXTRL_RESTRICT gen_obj )
{
    typedef SIXTRL_UINT64_T u64_t;
    SIXTRL_STATIC_VAR u64_t const ZERO_N = ( u64_t )0u;

    if( gen_obj != SIXTRL_NULLPTR )
    {
        printf( "NS(GenericObj) : type_id      = %16d\r\n"
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

                printf( "[ " );

                for( ; ii < nn ; ++ii, ++jj )
                {
                    if( jj < nn )
                    {
                        printf( "%16d , ", ( int )gen_obj->d[ ii ] );
                    }
                    else
                    {
                        printf( "%16d ]", ( int )gen_obj->d[ ii ] );
                    }
                }
            }
            else
            {
                printf( "[ ]" );
            }
        }
        else
        {
            printf( "0x00000000" );
        }

        printf( "\r\n"
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

                printf( "[ " );

                for( ; ii < nn ; ++ii, ++jj )
                {
                    if( jj < nn )
                    {
                        printf( "%16.8f , ", gen_obj->e[ ii ] );
                    }
                    else
                    {
                        printf( "%16.8f ]", gen_obj->e[ ii ] );
                    }
                }
            }
            else
            {
                printf( "[ ]" );
            }
        }
        else
        {
            printf( "0x00000000" );
        }

        printf( "\r\n\r\n" );
    }

    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(GenericObj_copy)( SIXTRL_GENOBJ_ARGPTR_DEC
    NS(GenericObj)* SIXTRL_RESTRICT destination,
    SIXTRL_GENOBJ_ARGPTR_DEC const NS(GenericObj) *const
        SIXTRL_RESTRICT source )
{
    if( ( source != SIXTRL_NULLPTR ) &&
        ( destination != SIXTRL_NULLPTR ) &&
        ( source->num_d_values == destination->num_e_values ) &&
        ( source->num_e_values == destination->num_e_values ) )
    {
        destination->type_id = source->type_id;
        destination->a       = source->a;
        destination->b       = source->b;

        SIXTRACKLIB_COPY_VALUES(
            SIXTRL_REAL_T, &destination->c[ 0 ], &source->c[ 0 ], 4u );

        if( ( source->d != SIXTRL_NULLPTR ) &&
            ( source->num_d_values > ( NS(buffer_size_t) )0u ) )
        {
            SIXTRL_ASSERT( destination->d != SIXTRL_NULLPTR );

            SIXTRACKLIB_COPY_VALUES( SIXTRL_UINT8_T,
                destination->d, source->d, source->num_d_values );
        }

        if( ( source->e != SIXTRL_NULLPTR ) &&
            ( source->num_e_values > ( NS(buffer_size_t) )0u ) )
        {
            SIXTRL_ASSERT( destination->e != SIXTRL_NULLPTR );

            SIXTRACKLIB_COPY_VALUES( SIXTRL_REAL_T,
                destination->e, source->e, source->num_e_values );
        }
    }

    return;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_TESTS_TESTLIB_GENERIC_BUFFER_H__ */

/* end: tests/sixtracklib/testlib/generic_buffer_obj.h */
