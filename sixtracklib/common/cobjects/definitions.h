#ifndef SIXTRACKLIB_COMMON_COBJECTS_DEFINITIONS_CXX_HPP__
#define SIXTRACKLIB_COMMON_COBJECTS_DEFINITIONS_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #if defined( __cplusplus )
        #include <type_traits>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_CBUFFER_ARGPTR_DEC )
    #define SIXTRL_CBUFFER_ARGPTR_DEC_UNDEF
    #define SIXTRL_CBUFFER_ARGPTR_DEC
#endif /* !defined( SIXTRL_CBUFFER_ARGPTR_DEC ) */

#if !defined( SIXTRL_CBUFFER_DATAPTR_DEC )
    #define SIXTRL_CBUFFER_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_DATAPTR_DEC )
        #define SIXTRL_CBUFFER_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else /* !defined( SIXTRL_DATAPTR_DEC ) */
        #define SIXTRL_CBUFFER_DATAPTR_DEC
    #endif /* defined( SIXTRL_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_CBUFFER_DATAPTR_DEC ) */

#if !defined( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC )
    #define SIXTRL_CBUFFER_OBJ_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_CBUFFER_DATAPTR_DEC )
        #define SIXTRL_CBUFFER_OBJ_ARGPTR_DEC SIXTRL_CBUFFER_DATAPTR_DEC
    #else /* !defined( SIXTRL_CBUFFER_DATAPTR_DEC ) */
        #define SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    #endif /* defined( SIXTRL_CBUFFER_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC ) */

#if !defined( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC )
    #define SIXTRL_CBUFFER_OBJ_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_CBUFFER_DATAPTR_DEC )
        #define SIXTRL_CBUFFER_OBJ_DATAPTR_DEC SIXTRL_CBUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC )
        #define SIXTRL_CBUFFER_OBJ_DATAPTR_DEC SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    #else /* !defined( SIXTRL_CBUFFER_DATAPTR_DEC ) */
        #define SIXTRL_CBUFFER_OBJ_DATAPTR_DEC
    #endif /* defined( SIXTRL_CBUFFER_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC ) */

#if !defined( SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC )
    #define SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_CBUFFER_DATAPTR_DEC )
        #define SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC SIXTRL_CBUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC )
        #define SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    #elif defined( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC )
        #define SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC SIXTRL_CBUFFER_OBJ_DATAPTR_DEC
    #else
        #define SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC
    #endif /* defined( SIXTRL_CBUFFER_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC ) */

#if !defined( SIXTRL_CBUFFER_GARBAGE_DATAPTR_DEC )
    #define SIXTRL_CBUFFER_GARBAGE_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_CBUFFER_DATAPTR_DEC )
        #define SIXTRL_CBUFFER_GARBAGE_DATAPTR_DEC SIXTRL_CBUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC )
        #define SIXTRL_CBUFFER_GARBAGE_DATAPTR_DEC SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    #elif defined( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC )
        #define SIXTRL_CBUFFER_GARBAGE_DATAPTR_DEC SIXTRL_CBUFFER_OBJ_DATAPTR_DEC
    #else
        #define SIXTRL_CBUFFER_GARBAGE_DATAPTR_DEC
    #endif /* defined( SIXTRL_CBUFFER_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_CBUFFER_GARBAGE_DATAPTR_DEC ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C"  {
#endif /* C++, Host */

typedef NS(status_type)         NS(cobj_status_type);
typedef NS(size_type)           NS(cobj_size_type);
typedef NS(address_type)        NS(cobj_addr_type);
typedef NS(address_diff_type)   NS(cobj_addr_diff_type);
typedef SIXTRL_UINT64_TYPE      NS(cobj_buffer_flags_type);
typedef SIXTRL_UINT64_TYPE      NS(cobj_obj_id_type);

typedef unsigned char NS(cobj_raw_type);
typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_raw_type)* NS(cobj_raw_pointer);
typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_raw_type) const*
        NS(cobj_raw_const_pointer);

#if !defined( SIXTRL_STORAGE_BE_COBJECTS )
    #define SIXTRL_STORAGE_BE_COBJECTS 0u
#endif /* !defined( SIXTRL_STORAGE_BE_COBJECTS ) */

#if !defined( SIXTRL_COBJECTS_STATIC_ARRAY_SIZE_LIMIT )
    #define SIXTRL_COBJECTS_STATIC_ARRAY_SIZE_LIMIT 24u
#endif /* !defined( SIXTRL_COBJECTS_STATIC_ARRAY_SIZE_LIMIT ) */

#if !defined( SIXTRL_COBJECTS_NULL_ADDRESS )
    #define SIXTRL_COBJECTS_NULL_ADDRESS SIXTRL_NULL_ADDR
#endif /* SIXTRL_COBJECTS_NULL_ADDRESS */

#if !defined( SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE )
    #define SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE SIXTRL_DEFAULT_ALIGN
#endif /* SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE */

#if !defined( SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR )
    #define SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR 0u
#endif /* SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR */

#if !defined( SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE )
    #define SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE 1u
#endif /* SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE */

#if !defined( SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE )
    #define SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE 2u
#endif /* SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE */

#if !defined( SIXTRL_CBUFFER_SECTION_ID_SLOTS )
    #define SIXTRL_CBUFFER_SECTION_ID_SLOTS 3u
#endif /* SIXTRL_CBUFFER_SECTION_ID_SLOTS */

#if !defined( SIXTRL_CBUFFER_SECTION_ID_INDICES )
    #define SIXTRL_CBUFFER_SECTION_ID_INDICES 4u
#endif /* SIXTRL_CBUFFER_SECTION_ID_INDICES */

#if !defined( SIXTRL_CBUFFER_SECTION_ID_POINTERS )
    #define SIXTRL_CBUFFER_SECTION_ID_POINTERS 5u
#endif /* SIXTRL_CBUFFER_SECTION_ID_POINTERS */

#if !defined( SIXTRL_CBUFFER_SECTION_ID_GARBAGE )
    #define SIXTRL_CBUFFER_SECTION_ID_GARBAGE 6u
#endif /* SIXTRL_CBUFFER_SECTION_ID_GARBAGE */

#if !defined( SIXTRL_CBUFFER_NUM_HEADER_ENTRIES )
    #define SIXTRL_CBUFFER_NUM_HEADER_ENTRIES 8u
#endif /* SIXTRL_CBUFFER_NUM_HEADER_ENTRIES */

#if !defined( SIXTRL_CBUFFER_DEFAULT_HEADER_SIZE )
    #define SIXTRL_CBUFFER_DEFAULT_HEADER_SIZE 64u
#endif /* SIXTRL_CBUFFER_DEFAULT_HEADER_SIZE */

#if !defined( SIXTRL_CBUFFER_DEFAULT_MIN_BUFFER_SIZE )
    #define SIXTRL_CBUFFER_DEFAULT_MIN_BUFFER_SIZE 128u
#endif /* SIXTRL_CBUFFER_MIN_LENGTH */

#if !defined( SIXTRL_COBJECTS_TYPE_ID_UNDEFINED)
    #define SIXTRL_COBJECTS_TYPE_ID_UNDEFINED 0x0
#endif /* !defined( SIXTRL_COBJECTS_TYPE_ID_UNDEFINED ) */

#if !defined( SIXTRL_COBJECTS_TYPE_ID_ILLEGAL)
    #define SIXTRL_COBJECTS_TYPE_ID_ILLEGAL 0x7fffffff
#endif /* !defined( SIXTRL_COBJECTS_TYPE_ID_ILLEGAL) */

#if !defined( SIXTRL_CBUFFER_FLAGS_NONE )
    #define SIXTRL_CBUFFER_FLAGS_NONE 0x00000000
#endif /* !defined( SIXTRL_CBUFFER_FLAGS_NONE ) */

#if !defined( SIXTRL_CBUFFER_FLAGS_ALLOW_REMAPPING )
    #define SIXTRL_CBUFFER_FLAGS_ALLOW_REMAPPING 0x00000001
#endif /* !defined( SIXTRL_CBUFFER_FLAGS_ALLOW_REMAPPING ) */

#if !defined( SIXTRL_CBUFFER_FLAGS_ALLOW_ALLOC )
    #define SIXTRL_CBUFFER_FLAGS_ALLOW_ALLOC 0x00000002
#endif /* !defined( SIXTRL_CBUFFER_FLAGS_ALLOW_ALLOC ) */

#if !defined( SIXTRL_CBUFFER_FLAGS_ALLOW_REALLOC )
    #define SIXTRL_CBUFFER_FLAGS_ALLOW_REALLOC 0x00000004
#endif /* !defined( SIXTRL_CBUFFER_FLAGS_ALLOW_REALLOC ) */

#if !defined( SIXTRL_CBUFFER_FLAGS_ALLOW_APPEND )
    #define SIXTRL_CBUFFER_FLAGS_ALLOW_APPEND 0x00000008
#endif /* !defined( SIXTRL_CBUFFER_FLAGS_ALLOW_APPEND ) */

#if !defined( SIXTRL_CBUFFER_FLAGS_STORAGE_IS_C_PTR )
    #define SIXTRL_CBUFFER_FLAGS_STORAGE_IS_C_PTR 0x01000000
#endif /* !defined( SIXTRL_CBUFFER_FLAGS_STORAGE_IS_C_PTR ) */

#if !defined( SIXTRL_CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR )
    #define SIXTRL_CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR 0x02000000
#endif /* !defined( SIXTRL_CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR ) */

#if !defined( SIXTRL_CBUFFER_FLAGS_FORCE_INIT )
    #define SIXTRL_CBUFFER_FLAGS_FORCE_INIT 0x10000000
#endif /* !defined( SIXTRL_CBUFFER_FLAGS_FORCE_INIT ) */

#if !defined( SIXTRL_CBUFFER_FLAGS_OWNS_STORED_DATA )
    #define SIXTRL_CBUFFER_FLAGS_OWNS_STORED_DATA 0x20000000
#endif /* !defined( SIXTRL_CBUFFER_FLAGS_OWNS_STORED_DATA ) */

#if !defined( SIXTRL_CBUFFER_FLAGS_SPECIAL_MEMORY )
    #define SIXTRL_CBUFFER_FLAGS_SPECIAL_MEMORY 0x40000000
#endif /* !defined( SIXTRL_CBUFFER_FLAGS_SPECIAL_MEMORY ) */

#if !defined( SIXTRL_CBUFFER_FLAGS_DEFAULT_VIEW_FLAGS )
    /* == SIXTRL_CBUFFER_FLAGS_ALLOW_REMAPPING |
     *    SIXTRL_CBUFFER_FLAGS_ALLOW_ALLOC     |
     *    SIXTRL_CBUFFER_FLAGS_ALLOW_REALLOC   |
     *    SIXTRL_CBUFFER_FLAGS_ALLOW_APPEND    |
     *    SIXTRL_CBUFFER_FLAGS_FORCE_INIT */
    #define SIXTRL_CBUFFER_FLAGS_DEFAULT_VIEW_FLAGS 0x1000000F
#endif /* !defined( SIXTRL_CBUFFER_FLAGS_DEFAULT_VIEW_FLAGS ) */

#if !defined( SIXTRL_CBUFFER_FLAGS_DEFAULT_BUFFER_FLAGS )
    /* == SIXTRL_CBUFFER_FLAGS_ALLOW_REMAPPING  |
     *    SIXTRL_CBUFFER_FLAGS_ALLOW_ALLOC      |
     *    SIXTRL_CBUFFER_FLAGS_ALLOW_REALLOC    |
     *    SIXTRL_CBUFFER_FLAGS_ALLOW_APPEND     |
     *    SIXTRL_CBUFFER_FLAGS_OWNS_STORED_DATA |
     *    SIXTRL_CBUFFER_FLAGS_STORAGE_IS_C_PTR |
     *    SIXTRL_CBUFFER_FLAGS_FORCE_INIT */
    #define SIXTRL_CBUFFER_FLAGS_DEFAULT_BUFFER_FLAGS 0x3100000F
#endif /* !defined( SIXTRL_CBUFFER_FLAGS_DEFAULT_BUFFER_FLAGS ) */

#if !defined( _GPUCODE )
    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_type)
        NS(COBJECTS_STATIC_ARRAY_SIZE_LIMIT) =
            ( NS(cobj_size_type) )SIXTRL_COBJECTS_STATIC_ARRAY_SIZE_LIMIT;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_addr_type)
        NS(COBJECTS_NULL_ADDRESS) =
            ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_type)
        NS(CBUFFER_DEFAULT_SLOT_SIZE) =
            ( NS(cobj_size_type) )SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_type)
        NS(CBUFFER_SECTION_ID_BASE_ADDR) =
            ( NS(cobj_size_type) )SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_type)
        NS(CBUFFER_SECTION_ID_BUFFER_SIZE) =
            ( NS(cobj_size_type) )SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_type)
        NS(CBUFFER_SECTION_ID_HEADER_SIZE) =
            ( NS(cobj_size_type) )SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_type)
        NS(CBUFFER_SECTION_ID_SLOTS) =
            ( NS(cobj_size_type) )SIXTRL_CBUFFER_SECTION_ID_SLOTS;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_type)
        NS(CBUFFER_SECTION_ID_OBJECTS) =
            ( NS(cobj_size_type) )SIXTRL_CBUFFER_SECTION_ID_INDICES;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_type)
        NS(CBUFFER_SECTION_ID_POINTERS) =
            ( NS(cobj_size_type) )SIXTRL_CBUFFER_SECTION_ID_POINTERS;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_type)
        NS(CBUFFER_SECTION_ID_GARBAGE) =
            ( NS(cobj_size_type) )SIXTRL_CBUFFER_SECTION_ID_GARBAGE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_type)
        NS(CBUFFER_NUM_HEADER_ENTRIES) =
            ( NS(cobj_size_type) )SIXTRL_CBUFFER_NUM_HEADER_ENTRIES;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_type)
        NS(CBUFFER_DEFAULT_HEADER_SIZE) =
            ( NS(cobj_size_type) )SIXTRL_CBUFFER_DEFAULT_HEADER_SIZE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_type)
        NS(CBUFFER_DEFAULT_MIN_BUFFER_SIZE) = ( NS(cobj_size_type)
            )SIXTRL_CBUFFER_DEFAULT_MIN_BUFFER_SIZE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_obj_id_type)
        NS(COBJECTS_TYPE_ID_UNDEFINED) = ( NS(cobj_obj_id_type)
            )SIXTRL_COBJECTS_TYPE_ID_UNDEFINED;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_obj_id_type)
        NS(COBJECTS_TYPE_ID_ILLEGAL) = ( NS(cobj_obj_id_type)
            )SIXTRL_COBJECTS_TYPE_ID_ILLEGAL;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_buffer_flags_type)
        NS(CBUFFER_FLAGS_NONE) = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_NONE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_buffer_flags_type)
        NS(CBUFFER_FLAGS_ALLOW_REMAPPING) = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_ALLOW_REMAPPING;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_buffer_flags_type)
        NS(CBUFFER_FLAGS_ALLOW_ALLOC) = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_ALLOW_ALLOC;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_buffer_flags_type)
        NS(CBUFFER_FLAGS_ALLOW_REALLOC) = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_ALLOW_REALLOC;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_buffer_flags_type)
        NS(CBUFFER_FLAGS_ALLOW_APPEND) = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_ALLOW_APPEND;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_buffer_flags_type)
        NS(CBUFFER_FLAGS_STORAGE_IS_C_PTR) = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_STORAGE_IS_C_PTR;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_buffer_flags_type)
        NS(CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR) = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_buffer_flags_type)
        NS(CBUFFER_FLAGS_FORCE_INIT) = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_FORCE_INIT;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_buffer_flags_type)
        NS(CBUFFER_FLAGS_OWNS_STORED_DATA) = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_OWNS_STORED_DATA;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_buffer_flags_type)
        NS(CBUFFER_FLAGS_SPECIAL_MEMORY) = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_SPECIAL_MEMORY;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_buffer_flags_type)
        NS(CBUFFER_FLAGS_DEFAULT_VIEW_FLAGS) = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_DEFAULT_VIEW_FLAGS;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_buffer_flags_type)
        NS(CBUFFER_FLAGS_DEFAULT_BUFFER_FLAGS) = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_DEFAULT_BUFFER_FLAGS;
#endif /* Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(cobj_obj_id_type)       cobj_obj_id_type;
    typedef ::NS(cobj_size_type)         cobj_size_type;
    typedef ::NS(cobj_addr_type)         cobj_addr_type;
    typedef ::NS(cobj_addr_diff_type)    cobj_addr_diff_type;
    typedef ::NS(cobj_buffer_flags_type) cobj_buffer_flags_type;
    typedef ::NS(cobj_status_type)       cobj_status_type;
    typedef ::NS(cobj_raw_type)          cobj_raw_type;
    typedef ::NS(cobj_raw_pointer)       cobj_raw_pointer;
    typedef ::NS(cobj_raw_const_pointer) cobj_raw_const_pointer;

    static constexpr cobj_buffer_flags_type CBUFFER_GENERIC_TYPE =
        static_cast< cobj_buffer_flags_type >( 0 );

    static constexpr cobj_addr_type COBJECTS_NULL_ADDRESS =
        static_cast< cobj_addr_type >( SIXTRL_COBJECTS_NULL_ADDRESS );

    static constexpr cobj_size_type COBJECTS_STATIC_ARRAY_SIZE_LIMIT =
        static_cast< cobj_size_type >( SIXTRL_COBJECTS_STATIC_ARRAY_SIZE_LIMIT );

    static constexpr cobj_size_type CBUFFER_DEFAULT_SLOT_SIZE =
        static_cast< cobj_size_type >( SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE );

    static constexpr cobj_size_type CBUFFER_SECTION_ID_BASE_ADDR =
        static_cast< cobj_size_type >( SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR );

    static constexpr cobj_size_type CBUFFER_SECTION_ID_BUFFER_SIZE =
        static_cast< cobj_size_type >( SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE );

    static constexpr cobj_size_type CBUFFER_SECTION_ID_HEADER_SIZE =
        static_cast< cobj_size_type >( SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE );

    static constexpr cobj_size_type CBUFFER_SECTION_ID_SLOTS =
        static_cast< cobj_size_type >( SIXTRL_CBUFFER_SECTION_ID_SLOTS );

    static constexpr cobj_size_type CBUFFER_SECTION_ID_OBJECTS =
        static_cast< cobj_size_type >( SIXTRL_CBUFFER_SECTION_ID_INDICES );

    static constexpr cobj_size_type CBUFFER_SECTION_ID_POINTERS =
        static_cast< cobj_size_type >( SIXTRL_CBUFFER_SECTION_ID_POINTERS );

    static constexpr cobj_size_type CBUFFER_SECTION_ID_GARBAGE =
        static_cast< cobj_size_type >( SIXTRL_CBUFFER_SECTION_ID_GARBAGE );

    static constexpr cobj_size_type CBUFFER_NUM_HEADER_ENTRIES =
        static_cast< cobj_size_type >( SIXTRL_CBUFFER_NUM_HEADER_ENTRIES );

    static constexpr cobj_size_type CBUFFER_DEFAULT_HEADER_SIZE =
        static_cast< cobj_size_type >( SIXTRL_CBUFFER_DEFAULT_HEADER_SIZE );

    static constexpr cobj_size_type CBUFFER_DEFAULT_MIN_BUFFER_SIZE =
        static_cast< cobj_size_type >( SIXTRL_CBUFFER_DEFAULT_MIN_BUFFER_SIZE );

    static constexpr cobj_obj_id_type COBJECTS_TYPE_ID_ILLEGAL =
        static_cast< cobj_obj_id_type >( SIXTRL_COBJECTS_TYPE_ID_ILLEGAL );

    static constexpr cobj_obj_id_type COBJECTS_TYPE_ID_UNDEFINED =
        static_cast< cobj_obj_id_type >( SIXTRL_COBJECTS_TYPE_ID_UNDEFINED );

    static constexpr cobj_obj_id_type CBUFFER_FLAGS_NONE =
        static_cast< cobj_obj_id_type >( SIXTRL_CBUFFER_FLAGS_NONE );

    static constexpr cobj_obj_id_type CBUFFER_FLAGS_ALLOW_REMAPPING =
        static_cast< cobj_obj_id_type >( SIXTRL_CBUFFER_FLAGS_ALLOW_REMAPPING );

    static constexpr cobj_obj_id_type CBUFFER_FLAGS_ALLOW_ALLOC =
        static_cast< cobj_obj_id_type >( SIXTRL_CBUFFER_FLAGS_ALLOW_ALLOC );

    static constexpr cobj_obj_id_type CBUFFER_FLAGS_ALLOW_REALLOC=
        static_cast< cobj_obj_id_type >( SIXTRL_CBUFFER_FLAGS_ALLOW_REALLOC );

    static constexpr cobj_obj_id_type CBUFFER_FLAGS_ALLOW_APPEND =
        static_cast< cobj_obj_id_type >( SIXTRL_CBUFFER_FLAGS_ALLOW_APPEND );

    static constexpr cobj_obj_id_type CBUFFER_FLAGS_STORAGE_IS_C_PTR =
        static_cast< cobj_obj_id_type >( SIXTRL_CBUFFER_FLAGS_STORAGE_IS_C_PTR );

    static constexpr cobj_obj_id_type CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR =
        static_cast< cobj_obj_id_type >(
            SIXTRL_CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR );

    static constexpr cobj_obj_id_type CBUFFER_FLAGS_FORCE_INIT =
        static_cast< cobj_obj_id_type >( SIXTRL_CBUFFER_FLAGS_FORCE_INIT );

    static constexpr cobj_obj_id_type CBUFFER_FLAGS_OWNS_STORED_DATA =
        static_cast< cobj_obj_id_type >( SIXTRL_CBUFFER_FLAGS_OWNS_STORED_DATA );

    static constexpr cobj_obj_id_type CBUFFER_FLAGS_SPECIAL_MEMORY =
        static_cast< cobj_obj_id_type >( SIXTRL_CBUFFER_FLAGS_SPECIAL_MEMORY );

    static constexpr cobj_obj_id_type CBUFFER_FLAGS_DEFAULT_VIEW_FLAGS =
        static_cast< cobj_obj_id_type >(
            SIXTRL_CBUFFER_FLAGS_DEFAULT_VIEW_FLAGS );

    static constexpr cobj_obj_id_type CBUFFER_FLAGS_DEFAULT_BUFFER_FLAGS =
        static_cast< cobj_obj_id_type >(
            SIXTRL_CBUFFER_FLAGS_DEFAULT_BUFFER_FLAGS );

} /* end: SIXTRL_CXX_NAMESPACE */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/cobj_illegal_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class E > struct CObjectsCopyArgTypeTraits
    {
        typedef typename std::decay< E >::type value_type;
        typedef SIXTRL_CBUFFER_ARGPTR_DEC value_type const* const_pointer;
        typedef SIXTRL_CBUFFER_ARGPTR_DEC value_type* pointer;

        typedef SIXTRL_CBUFFER_ARGPTR_DEC value_type const& const_reference;
        typedef SIXTRL_CBUFFER_ARGPTR_DEC value_type& reference;
    };

    template< class E > struct CObjectsStoreResultTypeTraits
    {
        typedef typename std::decay< E >::type value_type;
        typedef SIXTRL_CBUFFER_OBJ_DATAPTR_DEC value_type const* const_pointer;
        typedef SIXTRL_CBUFFER_OBJ_DATAPTR_DEC value_type* pointer;
    };

    template< class E > struct CObjectsTraits
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_ILLEGAL;
    };

    template< class E >
    constexpr cobj_obj_id_type CObjectsTraits< E >::TYPE_ID;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E > struct CObjectsNumPointersTraits
    {
        static constexpr cobj_size_type NUM_POINTERS = cobj_size_type{ 0 };
    };

    template< class E >
    constexpr cobj_size_type CObjectsNumPointersTraits< E >::NUM_POINTERS;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E > struct CObjectsTrivialHandleSizeTraits
    {
        static constexpr bool HAS_TRIVIAL_HANDLE_SIZE = true;
    };

    template< class E >
    constexpr bool CObjectsTrivialHandleSizeTraits<
        E >::HAS_TRIVIAL_HANDLE_SIZE;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E > struct CObjectsActualHandleSizeTraits
    {
        SIXTRL_FN static cobj_size_type HANDLE_SIZE(
            cobj_size_type slot_size ) SIXTRL_NOEXCEPT
        {
            if( slot_size == cobj_size_type{ 0 } )
                slot_size =  cobj_size_type{ SIXTRL_DEFAULT_ALIGN };

            SIXTRL_ASSERT( slot_size > ( cobj_size_type )0u );
            cobj_size_type const num_slots = sizeof( E ) / slot_size +
                static_cast< cobj_size_type >( sizeof( E ) % slot_size !=
                    cobj_size_type{ 0 } );

            SIXTRL_ASSERT( num_slots * slot_size >= sizeof( E ) );
            return num_slots * slot_size;
        }
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E > struct CObjectsReservedHandleSizeTraits
    {
        SIXTRL_FN static cobj_size_type HANDLE_SIZE(
            cobj_size_type slot_size ) SIXTRL_NOEXCEPT
        {
            return CObjectsActualHandleSizeTraits< E >::HANDLE_SIZE( slot_size );
        }
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E > struct CObjectsRequiredNumBytesTraits
    {
        SIXTRL_FN static cobj_size_type REQUIRED_NUM_BYTES(
            SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( ptr ),
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT
        {
            return CObjectsReservedHandleSizeTraits< E >::HANDLE_SIZE(
                slot_size );
        }
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E > struct CObjectsAttributesOffsetsTraits
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT offsets,
            cobj_size_type const max_num_offsets,
            SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( ptr ),
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef st::cobj_size_type st_size_t;
            st::cobj_status_type status = st::STATUS_GENERAL_FAILURE;
            if( ( slot_size > st_size_t{ 0 } ) && ( offsets != nullptr ) &&
                ( max_num_offsets > st_size_t{ 0 } ) ) {
                for( st_size_t ii = 0u ; ii < max_num_offsets ; ++ii ) {
                    offsets[ ii ] = st_size_t{ 0 }; }
                status = st::STATUS_SUCCESS; }
            return status;
        }
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E > struct CObjectsAttributesSizesTraits
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT sizes,
            cobj_size_type const max_num_sizes,
            SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( ptr ),
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef st::cobj_size_type st_size_t;
            st::cobj_status_type status = st::STATUS_GENERAL_FAILURE;
            if( ( slot_size > st_size_t{ 0 } ) && ( sizes != nullptr ) &&
                ( max_num_sizes > st_size_t{ 0 } ) ) {
                for( st_size_t ii = 0u ; ii < max_num_sizes ; ++ii ) {
                    sizes[ ii ] = st_size_t{ 0 }; }
                status = st::STATUS_SUCCESS; }
            return status;
        }
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class E > struct CObjectsAttributesCountsTraits
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT counts,
            cobj_size_type const max_num_counts,
            SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( ptr ),
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef st::cobj_size_type st_size_t;
            st::cobj_status_type status = st::STATUS_GENERAL_FAILURE;
            if( ( slot_size > st_size_t{ 0 } ) && ( counts != nullptr ) &&
                ( max_num_counts > st_size_t{ 0 } ) ) {
                for( st_size_t ii = 0u ; ii < max_num_counts ; ++ii ) {
                    counts[ ii ] = st_size_t{ 0 }; }
                status = st::STATUS_SUCCESS; }
            return status;
        }
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< cobj_obj_id_type TypeId > struct CObjectsIdTraits {
        typedef SIXTRL_CXX_NAMESPACE::IllegalType value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_COBJECTS_DEFINITIONS_CXX_HPP__ */
