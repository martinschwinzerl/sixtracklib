#ifndef SIXTRACKLIB_COMMON_BUFFER_DEFINITIONS_C99_H__
#define SIXTRACKLIB_COMMON_BUFFER_DEFINITIONS_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
    #else /* defined( __cplusplus ) */
        #include <stddef.h>
        #include <stdlib.h>
        #include <limits.h>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

typedef SIXTRL_UINT64_T NS(buffer_addr_t);
typedef SIXTRL_INT64_T  NS(buffer_addr_diff_t);
typedef SIXTRL_UINT64_T NS(buffer_size_t);
typedef SIXTRL_UINT64_T NS(buffer_flags_t);
typedef SIXTRL_UINT64_T NS(buffer_store_role_t);
typedef SIXTRL_UINT64_T NS(object_type_id_t);

#if !defined( SIXTRL_OBJECT_TYPE_UNDEFINED )
    #define SIXTRL_OBJECT_TYPE_UNDEFINED 0
#endif /* !defined( SIXTRL_OBJECT_TYPE_UNDEFINED ) */

#if !defined( SIXTRL_OBJECT_TYPE_FIRST_RESERVED_ID )
    #define SIXTRL_OBJECT_TYPE_FIRST_RESERVED_ID 0x40000000
#endif /* !defined( SIXTRL_OBJECT_TYPE_FIRST_RESERVED_ID ) */

#if !defined( SIXTRL_BUFFER_FLAGS_NONE )
    #define   SIXTRL_BUFFER_FLAGS_NONE                      0x00000000
#endif /* !defined( SIXTRL_BUFFER_FLAGS_NONE ) */

#if !defined( SIXTRL_BUFFER_USES_DATASTORE )
    #define   SIXTRL_BUFFER_USES_DATASTORE                  0x00000001
#endif /* !defined( SIXTRL_BUFFER_USES_DATASTORE ) */

#if !defined( SIXTRL_BUFFER_OWNS_DATASTORE )
    #define   SIXTRL_BUFFER_OWNS_DATASTORE                  0x00000002
#endif /* !defined( SIXTRL_BUFFER_OWNS_DATASTORE ) */

#if !defined( SIXTRL_BUFFER_DATASTORE_ALLOW_APPENDS )
    #define   SIXTRL_BUFFER_DATASTORE_ALLOW_APPENDS         0x00000004
#endif /* !defined( SIXTRL_BUFFER_DATASTORE_ALLOW_APPENDS ) */

#if !defined( SIXTRL_BUFFER_DATASTORE_ALLOW_CLEAR )
    #define   SIXTRL_BUFFER_DATASTORE_ALLOW_CLEAR           0x00000008
#endif /* !defined( SIXTRL_BUFFER_DATASTORE_ALLOW_CLEAR ) */

#if !defined( SIXTRL_BUFFER_DATASTORE_ALLOW_DELETES )
    #define   SIXTRL_BUFFER_DATASTORE_ALLOW_DELETES         0x00000010
#endif /* !defined( SIXTRL_BUFFER_DATASTORE_ALLOW_DELETES ) */

#if !defined( SIXTRL_BUFFER_DATASTORE_ALLOW_REMAPPING )
    #define   SIXTRL_BUFFER_DATASTORE_ALLOW_REMAPPING       0x00000020
#endif /* !defined( SIXTRL_BUFFER_DATASTORE_ALLOW_REMAPPING ) */

#if !defined( SIXTRL_BUFFER_DATASTORE_ALLOW_RESIZE )
    #define   SIXTRL_BUFFER_DATASTORE_ALLOW_RESIZE          0x00000040
#endif /* !defined( SIXTRL_BUFFER_DATASTORE_ALLOW_RESIZE ) */

#if !defined( SIXTRL_BUFFER_DATASTORE_ALLOW_RESIZE )
    #define   SIXTRL_BUFFER_DATASTORE_ALLOW_RESIZE          0x00000040
#endif /* !defined( SIXTRL_BUFFER_DATASTORE_ALLOW_RESIZE ) */

#if !defined( SIXTRL_BUFFER_DATASTORE_MEMPOOL )
    #define   SIXTRL_BUFFER_DATASTORE_MEMPOOL               0x00010000
#endif /* !defined( SIXTRL_BUFFER_DATASTORE_MEMPOOL ) */

#if !defined( SIXTRL_BUFFER_DATASTORE_OPENCL )
    #define   SIXTRL_BUFFER_DATASTORE_OPENCL                0x00020000
#endif /* !defined( SIXTRL_BUFFER_DATASTORE_OPENCL ) */

#if !defined( SIXTRL_BUFFER_DATASTORE_CUDA )
    #define   SIXTRL_BUFFER_DATASTORE_CUDA                  0x00040000
#endif /* !defined( SIXTRL_BUFFER_DATASTORE_CUDA ) */

#if !defined( SIXTRL_BUFFER_DATASTORE_SPECIAL_FLAGS_MASK )
    #define   SIXTRL_BUFFER_DATASTORE_SPECIAL_FLAGS_MASK    0xff000000
#endif /* !defined( SIXTRL_BUFFER_DATASTORE_SPECIAL_FLAGS_MASK ) */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_BUFFER_DEVELOPMENT_DEBUG_MODE )
    #define   SIXTRL_BUFFER_DEVELOPMENT_DEBUG_MODE 0x8000000000000000
#endif /* !defined( SIXTRL_BUFFER_DEVELOPMENT_DEBUG_MODE ) */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_BUFFER_DATASTORE_SPECIAL_FLAGS_BITS )
    #define   SIXTRL_BUFFER_DATASTORE_SPECIAL_FLAGS_BITS    24u
#endif /* !defined( SIXTRL_BUFFER_DATASTORE_SPECIAL_FLAGS_BITS ) */

#if !defined( SIXTRL_BUFFER_DEFAULT_SLOT_SIZE )
    #define   SIXTRL_BUFFER_DEFAULT_SLOT_SIZE               8u
#endif /* !defined( SIXTRL_BUFFER_DEFAULT_SLOT_SIZE ) */

#if !defined( SIXTRL_BUFFER_DEFAULT_HEADER_SIZE )
    #define   SIXTRL_BUFFER_DEFAULT_HEADER_SIZE             64u
#endif /* !defined( SIXTRL_BUFFER_DEFAULT_HEADER_SIZE ) */

#if !defined( SIXTRL_BUFFER_MINIMAL_LENGTH)
    #define SIXTRL_BUFFER_MINIMAL_LENGTH                   128u
#endif /* !defined( SIXTRL_BUFFER_MINIMAL_LENGTH) */

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(object_type_id_t) const NS(OBJECT_TYPE_UNDEFINED) =
    ( NS(object_type_id_t) )SIXTRL_OBJECT_TYPE_UNDEFINED;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_FIRST_RESERVED_ID) = ( NS(object_type_id_t) )0x40000000;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_MANAGED_BUFFER_HANDLE) = ( NS(object_type_id_t) )0x40000000;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR NS(buffer_flags_t) const NS(BUFFER_FLAGS_NONE) =
    ( NS(buffer_flags_t) )SIXTRL_BUFFER_FLAGS_NONE;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const NS(BUFFER_USES_DATASTORE) =
    ( NS(buffer_flags_t) )SIXTRL_BUFFER_USES_DATASTORE;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const NS(BUFFER_OWNS_DATASTORE) =
    ( NS(buffer_flags_t) )SIXTRL_BUFFER_OWNS_DATASTORE;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const NS(BUFFER_DATASTORE_ALLOW_APPENDS) =
        ( NS(buffer_flags_t) )SIXTRL_BUFFER_DATASTORE_ALLOW_APPENDS;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const NS(BUFFER_DATASTORE_ALLOW_CLEAR) =
    ( NS(buffer_flags_t) )SIXTRL_BUFFER_DATASTORE_ALLOW_CLEAR;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const NS(BUFFER_DATASTORE_ALLOW_DELETES) =
    ( NS(buffer_flags_t) )SIXTRL_BUFFER_DATASTORE_ALLOW_DELETES;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
NS(BUFFER_DATASTORE_ALLOW_REMAPPING) = ( NS(buffer_flags_t)
    )SIXTRL_BUFFER_DATASTORE_ALLOW_REMAPPING;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const NS(BUFFER_DATASTORE_ALLOW_RESIZE) =
    ( NS(buffer_flags_t) )SIXTRL_BUFFER_DATASTORE_ALLOW_RESIZE;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const NS(BUFFER_DATASTORE_MEMPOOL)
    = ( NS(buffer_flags_t) )SIXTRL_BUFFER_DATASTORE_MEMPOOL;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const NS(BUFFER_DATASTORE_OPENCL) =
    ( NS(buffer_flags_t) )SIXTRL_BUFFER_DATASTORE_OPENCL;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const NS(BUFFER_DATASTORE_CUDA) =
    ( NS(buffer_flags_t) )SIXTRL_BUFFER_DATASTORE_CUDA;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
NS(BUFFER_DATASTORE_SPECIAL_FLAGS_MASK) = ( NS(buffer_flags_t)
    )SIXTRL_BUFFER_DATASTORE_SPECIAL_FLAGS_MASK;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
NS(BUFFER_DATASTORE_SPECIAL_FLAGS_BITS) = ( NS(buffer_flags_t)
    )SIXTRL_BUFFER_DATASTORE_SPECIAL_FLAGS_BITS;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR NS(buffer_flags_t) const NS(BUFFER_DEVELOPMENT_DEBUG_MDOE) =
    ( NS(buffer_flags_t) )SIXTRL_BUFFER_DEVELOPMENT_DEBUG_MODE;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR NS(buffer_size_t)  const NS(BUFFER_DEFAULT_SLOT_SIZE) =
    ( NS(buffer_size_t) )SIXTRL_BUFFER_DEFAULT_SLOT_SIZE;

SIXTRL_STATIC_VAR NS(buffer_size_t) const NS(BUFFER_DEFAULT_HEADER_SIZE) =
    ( NS(buffer_size_t) )SIXTRL_BUFFER_DEFAULT_HEADER_SIZE;

SIXTRL_STATIC_VAR NS(buffer_size_t) const NS(BUFFER_MINIMAL_LENGTH) =
    ( NS(buffer_size_t) )SIXTRL_BUFFER_MINIMAL_LENGTH;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR NS(buffer_store_role_t) const
    NS(BUFFER_STORE_ROLE_NONE) = ( NS(buffer_store_role_t) )0u;

SIXTRL_STATIC_VAR NS(buffer_store_role_t) const
    NS(BUFFER_STORE_ROLE_PARTICLES_BUFFER) = ( NS(buffer_store_role_t) )1u;

SIXTRL_STATIC_VAR NS(buffer_store_role_t) const
    NS(BUFFER_STORE_ROLE_BEAM_ELEMENTS_BUFFER) = ( NS(buffer_store_role_t) )2u;

SIXTRL_STATIC_VAR NS(buffer_store_role_t) const
    NS(BUFFER_STORE_ROLE_OUTPUT_BUFFER) = ( NS(buffer_store_role_t) )3u;

SIXTRL_STATIC_VAR NS(buffer_store_role_t) const
    NS(BUFFER_STORE_ROLE_PARTICLES_ADDR_BUFFER) =
        ( NS(buffer_store_role_t) )4u;

SIXTRL_STATIC_VAR NS(buffer_store_role_t) const
    NS(BUFFER_STORE_ROLE_ASSIGN_ADDRESS_ITEMS_BUFFER) =
        ( NS(buffer_store_role_t) )6u;

SIXTRL_STATIC_VAR NS(buffer_store_role_t) const
    NS(BUFFER_STORE_ROLE_CONFIG_BUFFER) = ( NS(buffer_store_role_t) )7u;

SIXTRL_STATIC_VAR NS(buffer_store_role_t) const
    NS(BUFFER_STORE_ROLE_PARTICLE_STATISTICS_BUFFER) =
        ( NS(buffer_store_role_t) )8u;

SIXTRL_STATIC_VAR NS(buffer_store_role_t) const
    NS(BUFFER_STORE_ROLE_USER_DEFINED) = ( NS(buffer_store_role_t) )64u;

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}

namespace SIXTRL_CXX_NAMESPACE
{
    typedef NS(object_type_id_t) object_type_id_t;
    typedef NS(buffer_size_t)    buffer_size_t;
    typedef NS(buffer_addr_t)    buffer_addr_t;
    typedef NS(buffer_flags_t)   buffer_flags_t;

    /* --------------------------------------------------------------------- */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_UNDEFINED = static_cast< object_type_id_t >(
            SIXTRL_OBJECT_TYPE_UNDEFINED );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_FIRST_RESERVED_ID =
            static_cast< object_type_id_t >( 0x40000000 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_MANAGED_BUFFER_HANDLE =
            static_cast< object_type_id_t >( 0x40000000 );

    /* --------------------------------------------------------------------- */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_FLAGS_NONE = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_FLAGS_NONE );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_USES_DATASTORE = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_USES_DATASTORE );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_OWNS_DATASTORE = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_OWNS_DATASTORE );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_ALLOW_APPENDS = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DATASTORE_ALLOW_APPENDS );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_ALLOW_CLEAR = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DATASTORE_ALLOW_CLEAR );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_ALLOW_DELETES = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DATASTORE_ALLOW_DELETES );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_ALLOW_REMAPPING = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DATASTORE_ALLOW_REMAPPING );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_ALLOW_RESIZE = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DATASTORE_ALLOW_RESIZE );

    /* --------------------------------------------------------------------- */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_MEMPOOL = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DATASTORE_MEMPOOL );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_OPENCL = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DATASTORE_OPENCL );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_CUDA = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DATASTORE_CUDA );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_SPECIAL_FLAGS_MASK = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DATASTORE_SPECIAL_FLAGS_MASK );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_SPECIAL_FLAGS_BITS = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DATASTORE_SPECIAL_FLAGS_BITS );

    /* --------------------------------------------------------------------- */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DEVELOPMENT_DEBUG_MDOE = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DEVELOPMENT_DEBUG_MODE );

    /* --------------------------------------------------------------------- */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_size_t
        BUFFER_DEFAULT_SLOT_SIZE = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DEFAULT_SLOT_SIZE );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_size_t
        BUFFER_DEFAULT_HEADER_SIZE = static_cast< buffer_flags_t >(
            SIXTRL_BUFFER_DEFAULT_HEADER_SIZE );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_size_t
        BUFFER_MINIMAL_LENGTH = static_cast< buffer_size_t >(
            SIXTRL_BUFFER_MINIMAL_LENGTH );

    /* --------------------------------------------------------------------- */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_store_role_t
        BUFFER_STORE_ROLE_NONE = static_cast< buffer_store_role_t >(
            ::NS(BUFFER_STORE_ROLE_NONE) );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_store_role_t
        BUFFER_STORE_ROLE_PARTICLES_BUFFER = static_cast< buffer_store_role_t >(
            NS(BUFFER_STORE_ROLE_PARTICLES_BUFFER) );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_store_role_t
        BUFFER_STORE_ROLE_BEAM_ELEMENTS_BUFFER = static_cast< buffer_store_role_t >(
            NS(BUFFER_STORE_ROLE_BEAM_ELEMENTS_BUFFER) );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_store_role_t
        BUFFER_STORE_ROLE_OUTPUT_BUFFER = static_cast< buffer_store_role_t >(
            NS(BUFFER_STORE_ROLE_OUTPUT_BUFFER) );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_store_role_t
        BUFFER_STORE_ROLE_PARTICLES_ADDR_BUFFER = static_cast<
            buffer_store_role_t >( NS(BUFFER_STORE_ROLE_PARTICLES_ADDR_BUFFER) );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_store_role_t
        BUFFER_STORE_ROLE_ASSIGN_ADDRESS_ITEMS_BUFFER = static_cast<
            buffer_store_role_t >(
                NS(BUFFER_STORE_ROLE_ASSIGN_ADDRESS_ITEMS_BUFFER) );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_store_role_t
        BUFFER_STORE_ROLE_CONFIG_BUFFER = static_cast< buffer_store_role_t >(
            NS(BUFFER_STORE_ROLE_CONFIG_BUFFER) );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_store_role_t
        BUFFER_STORE_ROLE_PARTICLE_STATISTICS_BUFFER = static_cast<
            buffer_store_role_t >(
                NS(BUFFER_STORE_ROLE_PARTICLE_STATISTICS_BUFFER) );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST buffer_store_role_t
        BUFFER_STORE_ROLE_USER_DEFINED = static_cast< buffer_store_role_t >(
            NS(BUFFER_STORE_ROLE_USER_DEFINED) );
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_BUFFER_DEFINITIONS_C99_H__ */
