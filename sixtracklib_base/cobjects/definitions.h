#ifndef SIXTRACKLIB_BASE_COBJECTS_DEFINITIONS_H__
#define SIXTRACKLIB_BASE_COBJECTS_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/definitions.h"
    #include "sixtracklib_base/internal/obj_type_id_traits.h"
    #include "sixtracklib_base/internal/obj_store_traits.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_ARGPTR_DEC )
    #define SIXTRL_ARGPTR_DEC_UNDEF
    #define SIXTRL_ARGPTR_DEC
#endif /* defined( SIXTRL_ARGPTR_DEC ) */

#if !defined( SIXTRL_DATAPTR_DEC )
    #define SIXTRL_DATAPTR_DEC_UNDEF
    #define SIXTRL_DATAPTR_DEC
#endif /* defined( SIXTRL_DATAPTR_DEC ) */

#if !defined( SIXTRL_BUFFER_ARGPTR_DEC )
    #define   SIXTRL_BUFFER_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_ARGPTR_DEC )
        #define  SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_ARGPTR_DEC
    #else
        #define SIXTRL_BUFFER_ARGPTR_DEC
    #endif /* defined( SIXTRL_ARGPTR_DEC ) */
#endif /* !defined( SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC ) */

#if !defined( SIXTRL_BUFFER_DATAPTR_DEC )
    #define SIXTRL_BUFFER_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else /* !defined( SIXTRL_DATAPTR_DEC ) */
        #define  SIXTRL_BUFFER_DATAPTR_DEC
    #endif /* defined( SIXTRL_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_BUFFER_DATAPTR_DEC ) */


#if !defined( SIXTRL_BUFFER_OBJ_ARGPTR_DEC )
    #define SIXTRL_BUFFER_OBJ_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_DEC )
        #define  SIXTRL_BUFFER_OBJ_ARGPTR_DEC SIXTRL_BUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_ARGPTR_DEC ) /* defined( SIXTRL_ARGPTR_DEC ) */
        #define  SIXTRL_BUFFER_OBJ_ARGPTR_DEC SIXTRL_DATAPTR_DEC
    #else /* !defined( SIXTRL_ARGPTR_DEC ) */
        #define  SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    #endif /* defined( SIXTRL_ARGPTR_DEC ) */
#endif /* !defined( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ) */

#if !defined( SIXTRL_BUFFER_OBJ_DATAPTR_DEC )
    #define SIXTRL_BUFFER_OBJ_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_DEC )
        #define  SIXTRL_BUFFER_OBJ_DATAPTR_DEC SIXTRL_BUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC ) /* defined( SIXTRL_DATAPTR_DEC ) */
        #define  SIXTRL_BUFFER_OBJ_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else /* !defined( SIXTRL_DATAPTR_DEC ) */
        #define  SIXTRL_BUFFER_OBJ_DATAPTR_DEC
    #endif /* defined( SIXTRL_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_BUFFER_OBJ_DATAPTR_DEC ) */

#if !defined( SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC )
    #define SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_DEC )
        #define  SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC SIXTRL_BUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_ARGPTR_DEC )
        #define  SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC SIXTRL_DATAPTR_DEC
    #else /* !defined( SIXTRL_ARGPTR_DEC ) */
        #define SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC
    #endif /* defined( SIXTRL_ARGPTR_DEC ) */
#endif /* !defined( SIXTRL_BUFFER_GARBAGE_ARGPTR_DEC ) */

#if !defined( SIXTRL_BUFFER_GARBAGE_DATAPTR_DEC )
    #define SIXTRL_BUFFER_GARBAGE_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_DEC )
        #define  SIXTRL_BUFFER_GARBAGE_DATAPTR_DEC SIXTRL_BUFFER_DATAPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_BUFFER_GARBAGE_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else /* !defined( SIXTRL_DATAPTR_DEC ) */
        #define SIXTRL_BUFFER_GARBAGE_DATAPTR_DEC
    #endif /* defined( SIXTRL_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_BUFFER_GARBAGE_DATAPTR_DEC ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C"  {
#endif /* C++, Host */

typedef SIXTRL_INT32_T  NS(cobj_type_id_t);
typedef NS(size_t)      NS(cobj_size_t);
typedef SIXTRL_UINT64_T NS(cobj_address_t);
typedef SIXTRL_INT64_T  NS(cobj_address_diff_t);
typedef SIXTRL_UINT64_T NS(cobj_buffer_flags_t);
typedef unsigned char   NS(cobj_raw_t);

typedef SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)*
        NS(ptr_raw_buffer_data_t);

typedef SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const*
        NS(ptr_const_raw_buffer_data_t);

#if !defined( SIXTRL_STORAGE_BE_COBJECTS )
    #define SIXTRL_STORAGE_BE_COBJECTS 0u
#endif /* !defined( SIXTRL_STORAGE_BE_COBJECTS ) */

#if !defined( SIXTRL_COBJECTS_STATIC_ARRAY_SIZE_LIMIT )
    #define SIXTRL_COBJECTS_STATIC_ARRAY_SIZE_LIMIT 24u
#endif /* !defined( SIXTRL_COBJECTS_STATIC_ARRAY_SIZE_LIMIT ) */

#if !defined( SIXTRL_COBJECTS_NULL_ADDRESS )
    #define SIXTRL_COBJECTS_NULL_ADDRESS 0u
#endif /* SIXTRL_COBJECTS_NULL_ADDRESS */

#if !defined( SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE )
    #define SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE 8u
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

#if !defined( SIXTRL_CBUFFER_MIN_SIZE )
    #define SIXTRL_CBUFFER_MIN_SIZE 128u
#endif /* SIXTRL_CBUFFER_MIN_LENGTH */

#if !defined( SIXTRL_COBJECTS_ILLEGAL_TYPE_ID)
    #define SIXTRL_COBJECTS_ILLEGAL_TYPE_ID 0x7fffffff
#endif /* !defined( SIXTRL_COBJECTS_ILLEGAL_TYPE_ID) */

#if !defined( _GPUCODE )
    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_t)
        NS(COBJECTS_STATIC_ARRAY_SIZE_LIMIT) =
            ( NS(cobj_size_t) )SIXTRL_COBJECTS_STATIC_ARRAY_SIZE_LIMIT;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_address_t)
        NS(COBJECTS_NULL_ADDRESS) =
            ( NS(cobj_address_t) )SIXTRL_COBJECTS_NULL_ADDRESS;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_t)
        NS(CBUFFER_DEFAULT_SLOT_SIZE) =
            ( NS(cobj_size_t) )SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_t)
        NS(CBUFFER_SECTION_ID_BASE_ADDR) =
            ( NS(cobj_size_t) )SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_t)
        NS(CBUFFER_SECTION_ID_BUFFER_SIZE) =
            ( NS(cobj_size_t) )SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_t)
        NS(CBUFFER_SECTION_ID_HEADER_SIZE) =
            ( NS(cobj_size_t) )SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_t)
        NS(CBUFFER_SECTION_ID_SLOTS) =
            ( NS(cobj_size_t) )SIXTRL_CBUFFER_SECTION_ID_SLOTS;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_t)
        NS(CBUFFER_SECTION_ID_OBJECTS) =
            ( NS(cobj_size_t) )SIXTRL_CBUFFER_SECTION_ID_INDICES;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_t)
        NS(CBUFFER_SECTION_ID_POINTERS) =
            ( NS(cobj_size_t) )SIXTRL_CBUFFER_SECTION_ID_POINTERS;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_t)
        NS(CBUFFER_SECTION_ID_GARBAGE) =
            ( NS(cobj_size_t) )SIXTRL_CBUFFER_SECTION_ID_GARBAGE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_t)
        NS(CBUFFER_NUM_HEADER_ENTRIES) =
            ( NS(cobj_size_t) )SIXTRL_CBUFFER_NUM_HEADER_ENTRIES;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_t)
        NS(CBUFFER_DEFAULT_HEADER_SIZE) =
            ( NS(cobj_size_t) )SIXTRL_CBUFFER_DEFAULT_HEADER_SIZE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_size_t)
        NS(CBUFFER_MIN_SIZE) = ( NS(cobj_size_t) )SIXTRL_CBUFFER_MIN_SIZE;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_type_id_t)
        NS(COBJECTS_ILLEGAL_TYPE_ID) =
            ( NS(cobj_type_id_t) )SIXTRL_COBJECTS_ILLEGAL_TYPE_ID;
#endif /* Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(cobj_type_id_t)        cobj_type_id_t;
    typedef ::NS(cobj_address_t)        cobj_address_t;
    typedef ::NS(cobj_address_diff_t)   cobj_address_diff_t;
    typedef ::NS(cobj_buffer_flags_t)   cobj_buffer_flags_t;
    typedef ::NS(cobj_raw_t)            cobj_raw_t;

    static constexpr cobj_buffer_flags_t CBUFFER_GENERIC_TYPE =
        static_cast< cobj_buffer_flags_t >( 0 );

    static constexpr cobj_address_t COBJECTS_NULL_ADDRESS =
        static_cast< cobj_address_t >( SIXTRL_COBJECTS_NULL_ADDRESS );

    static constexpr SIXTRL_CXX_NAMESPACE::size_t
    COBJECTS_STATIC_ARRAY_SIZE_LIMIT = static_cast< SIXTRL_CXX_NAMESPACE::size_t
        >( SIXTRL_COBJECTS_STATIC_ARRAY_SIZE_LIMIT );

    static constexpr SIXTRL_CXX_NAMESPACE::size_t CBUFFER_DEFAULT_SLOT_SIZE =
        static_cast< SIXTRL_CXX_NAMESPACE::size_t >(
            SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE );

    static constexpr SIXTRL_CXX_NAMESPACE::size_t CBUFFER_SECTION_ID_BASE_ADDR =
        static_cast< SIXTRL_CXX_NAMESPACE::size_t >(
            SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR );

    static constexpr SIXTRL_CXX_NAMESPACE::size_t
        CBUFFER_SECTION_ID_BUFFER_SIZE = static_cast<
            SIXTRL_CXX_NAMESPACE::size_t >(
                SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE );

    static constexpr SIXTRL_CXX_NAMESPACE::size_t
        CBUFFER_SECTION_ID_HEADER_SIZE = static_cast<
            SIXTRL_CXX_NAMESPACE::size_t >(
                SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE );

    static constexpr SIXTRL_CXX_NAMESPACE::size_t CBUFFER_SECTION_ID_SLOTS =
        static_cast< SIXTRL_CXX_NAMESPACE::size_t >(
            SIXTRL_CBUFFER_SECTION_ID_SLOTS );

    static constexpr SIXTRL_CXX_NAMESPACE::size_t CBUFFER_SECTION_ID_OBJECTS =
        static_cast< SIXTRL_CXX_NAMESPACE::size_t >(
            SIXTRL_CBUFFER_SECTION_ID_INDICES );

    static constexpr SIXTRL_CXX_NAMESPACE::size_t CBUFFER_SECTION_ID_POINTERS =
        static_cast< SIXTRL_CXX_NAMESPACE::size_t >(
            SIXTRL_CBUFFER_SECTION_ID_POINTERS );

    static constexpr SIXTRL_CXX_NAMESPACE::size_t CBUFFER_SECTION_ID_GARBAGE =
        static_cast< SIXTRL_CXX_NAMESPACE::size_t >(
            SIXTRL_CBUFFER_SECTION_ID_GARBAGE );

    static constexpr SIXTRL_CXX_NAMESPACE::size_t CBUFFER_NUM_HEADER_ENTRIES =
        static_cast< SIXTRL_CXX_NAMESPACE::size_t >(
            SIXTRL_CBUFFER_NUM_HEADER_ENTRIES );

    static constexpr SIXTRL_CXX_NAMESPACE::size_t CBUFFER_DEFAULT_HEADER_SIZE =
        static_cast< SIXTRL_CXX_NAMESPACE::size_t >(
            SIXTRL_CBUFFER_DEFAULT_HEADER_SIZE );

    static constexpr SIXTRL_CXX_NAMESPACE::size_t CBUFFER_MIN_SIZE =
        static_cast< SIXTRL_CXX_NAMESPACE::size_t >( SIXTRL_CBUFFER_MIN_SIZE );

    static constexpr cobj_type_id_t COBJECTS_ILLEGAL_TYPE_ID =
        static_cast< cobj_type_id_t >( SIXTRL_COBJECTS_ILLEGAL_TYPE_ID );

    /* ===================================================================== */
    /* Specialization of StorageBackendTraits<> for CObjects Back-End: */

    template<> struct StorageBackendTraits< STORAGE_BE_COBJECTS >
    {
        typedef SIXTRL_CXX_NAMESPACE::cobj_type_id_t type_id_t;
    };

    static_assert(
        SIXTRL_CXX_NAMESPACE::COBJECTS_ILLEGAL_TYPE_ID ==
        SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id< cobj_type_id_t >(),
        "Illegal Type IDs between type-traits and preprocessor "
        "macros have to agree" );

    template< class ObjData > using ObjDataCObjectsTypeIdTraits =
        SIXTRL_CXX_NAMESPACE::ObjDataTypeIdTraits<
            ObjData, cobj_type_id_t >;
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_BASE_COBJECTS_DEFINITIONS_H__ */
