#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_FIXED_NUM_PTRS_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_FIXED_NUM_PTRS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/objs/definitions.h"
    #include "sixtracklib/common/objs/obj_base_class.hpp"
    #include "sixtracklib/common/objs/element_pointers.hpp"
    #include "sixtracklib/common/objs/field_offsets.hpp"
    #include "sixtracklib/common/objs/field_sizes.hpp"
    #include "sixtracklib/common/objs/field_counts.hpp"
    #include "sixtracklib/common/internal/obj_data_type_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"

    #include "sixtracklib/testlib/common/cobjects/type_no_ptrs.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

typedef enum { NS(TESTS_OBJECT_TYPE_FIXED_NUM_PTRS) = 10001 }
NS(TypeFixedNumPtrsTypeId);

typedef struct NS(TypeFixedNumPtrs)
{
    SIXTRL_REAL_T       a               SIXTRL_ALIGN( 8 );
    SIXTRL_UINT64_T     num_b_values    SIXTRL_ALIGN( 8 );
    NS(cobj_address_t)  b_values_addr   SIXTRL_ALIGN( 8 );
    SIXTRL_UINT64_T     num_c_values    SIXTRL_ALIGN( 8 );
    NS(cobj_address_t)  c_values_addr   SIXTRL_ALIGN( 8 );
}
NS(TypeFixedNumPtrs);

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)*
NS(TypeFixedNumPtrs_preset)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_T NS(TypeFixedNumPtrs_a)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_UINT64_T NS(TypeFixedNumPtrs_num_b_values)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_UINT64_T NS(TypeFixedNumPtrs_num_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t) NS(TypeFixedNumPtrs_b_values_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t) NS(TypeFixedNumPtrs_c_values_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(TypeFixedNumPtrs_set_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_REAL_T const a ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(TypeFixedNumPtrs_set_num_b_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_UINT64_T const num_b_values ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(TypeFixedNumPtrs_set_num_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_UINT64_T const num_c_values ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(TypeFixedNumPtrs_set_b_values_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    NS(cobj_address_t) const b_values_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(TypeFixedNumPtrs_set_c_values_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    NS(cobj_address_t) const c_values_addr ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
NS(TypeFixedNumPtrs_const_b_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeFixedNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
NS(TypeFixedNumPtrs_const_b_values_end)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeFixedNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
NS(TypeFixedNumPtrs_b_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
NS(TypeFixedNumPtrs_b_values_end)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
NS(TypeFixedNumPtrs_const_c_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeFixedNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
NS(TypeFixedNumPtrs_const_c_values_end)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeFixedNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
NS(TypeFixedNumPtrs_c_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
NS(TypeFixedNumPtrs_c_values_end)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_T NS(TypeFixedNumPtrs_b_value)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj, SIXTRL_UINT64_T const ii ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_T NS(TypeFixedNumPtrs_c_value)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj, SIXTRL_UINT64_T const ii ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(TypeFixedNumPtrs_set_b_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)*SIXTRL_RESTRICT obj,
    SIXTRL_UINT64_T const ii, SIXTRL_REAL_T const b_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(TypeFixedNumPtrs_set_c_value)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_UINT64_T const ii, SIXTRL_REAL_T const c_value ) SIXTRL_NOEXCEPT;

/*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
NS(TypeFixedNumPtrs_const_c_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeFixedNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
NS(TypeFixedNumPtrs_const_c_values_end)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeFixedNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
NS(TypeFixedNumPtrs_c_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
NS(TypeFixedNumPtrs_c_values_end)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    static constexpr cobj_type_id_t TESTS_OBJECT_TYPE_FIXED_NUM_PTRS =
        static_cast< cobj_type_id_t >( NS(TESTS_OBJECT_TYPE_FIXED_NUM_PTRS) );

    template<>
    struct ObjTypeIdDataTypeMap<
        cobj_type_id_t, TESTS_OBJECT_TYPE_FIXED_NUM_PTRS >
    {
        typedef ::NS(TypeFixedNumPtrs) value_type;
    };

    template<>
    struct ObjDataTypeIdTraits< ::NS(TypeFixedNumPtrs), cobj_type_id_t >
    {
        static SIXTRL_FN constexpr cobj_type_id_t TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::TESTS_OBJECT_TYPE_FIXED_NUM_PTRS;
        }
    };

    template<>
    struct ObjDataCApiTypeTraits< ::NS(TypeFixedNumPtrs) >
    {
        typedef ::NS(TypeFixedNumPtrs) c_api_t;
    };

    template<> struct CObjElemNumPointers< ::NS(TypeFixedNumPtrs), void >
    {
        static constexpr cobj_size_t min_num_ptrs = cobj_size_t{ 2 };
        static constexpr cobj_size_t max_num_ptrs = cobj_size_t{ 2 };
    };

    template<> struct CObjElemFieldOffsets< ::NS(TypeFixedNumPtrs) >
    {
        static constexpr cobj_size_t offsets[] =
        {
            offsetof( ::NS(TypeFixedNumPtrs), b_values_addr ),
            offsetof( ::NS(TypeFixedNumPtrs), c_values_addr )
        };
    };

    template<> struct CObjElemFieldSizes< ::NS(TypeFixedNumPtrs) >
    {
        static constexpr cobj_size_t sizes[] =
        {
            sizeof( SIXTRL_REAL_T ), sizeof( SIXTRL_REAL_T )

        };
    };

    template<> struct CObjElemFieldCounts< ::NS(TypeFixedNumPtrs) >
    {
        static SIXTRL_INLINE SIXTRL_FN cobj_status_t init_field_counts(
            SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT counts_begin,
            cobj_size_t const max_num_counts,
            SIXTRL_BUFFER_ARGPTR_DEC const ::NS(TypeFixedNumPtrs) *const
                SIXTRL_RESTRICT ptr_elem = nullptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef cobj_size_t _size_t;
            cobj_status_t status = st::COBJECTS_STATUS_GENERAL_FAILURE;

            if( ptr_elem != nullptr )
            {
                SIXTRL_BUFFER_ARGPTR_DEC _size_t const counts[] =
                    { ptr_elem->num_b_values, ptr_elem->num_c_values };

                status = st::CObjElem_init_array_as_copy_fill_remainder(
                    counts_begin, max_num_counts, &counts[ 0 ],
                        st::CObjElem_num_ptrs< ::NS(TypeFixedNumPtrs) >(
                            ptr_elem ), _size_t{ 0 } );
            }

            return status;
        }
    };
}

#endif /* __cplusplus */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)*
NS(TypeFixedNumPtrs_preset)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    if( obj != SIXTRL_NULLPTR )
    {
        NS(TypeFixedNumPtrs_set_a)( obj, ( SIXTRL_REAL_T )0.0 );
        NS(TypeFixedNumPtrs_set_num_b_values)( obj, ( SIXTRL_UINT64_T )0 );
        NS(TypeFixedNumPtrs_set_b_values_addr)( obj, ( NS(cobj_address_t) )0 );
        NS(TypeFixedNumPtrs_set_num_c_values)( obj, ( SIXTRL_UINT64_T )0 );
        NS(TypeFixedNumPtrs_set_c_values_addr)( obj, ( NS(cobj_address_t) )0 );
    }

    return obj;
}

SIXTRL_INLINE SIXTRL_REAL_T NS(TypeFixedNumPtrs_a)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(TypeFixedNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->a;
}

SIXTRL_INLINE SIXTRL_UINT64_T NS(TypeFixedNumPtrs_num_b_values)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->num_b_values;
}

SIXTRL_INLINE SIXTRL_UINT64_T NS(TypeFixedNumPtrs_num_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->num_c_values;
}

SIXTRL_INLINE NS(cobj_address_t) NS(TypeFixedNumPtrs_b_values_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->b_values_addr;
}

SIXTRL_INLINE NS(cobj_address_t) NS(TypeFixedNumPtrs_c_values_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->c_values_addr;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(TypeFixedNumPtrs_set_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_REAL_T const a ) SIXTRL_NOEXCEPT
{
    if( obj != SIXTRL_NULLPTR ) obj->a = a;
}

SIXTRL_INLINE void NS(TypeFixedNumPtrs_set_num_b_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_UINT64_T const num_b_values ) SIXTRL_NOEXCEPT
{
    if( obj != SIXTRL_NULLPTR ) obj->num_b_values = num_b_values;
}

SIXTRL_INLINE void NS(TypeFixedNumPtrs_set_num_c_values)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_UINT64_T const num_c_values ) SIXTRL_NOEXCEPT
{
    if( obj != SIXTRL_NULLPTR ) obj->num_c_values = num_c_values;
}

SIXTRL_INLINE void NS(TypeFixedNumPtrs_set_b_values_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    NS(cobj_address_t) const b_values_addr ) SIXTRL_NOEXCEPT
{
    if( obj != SIXTRL_NULLPTR ) obj->b_values_addr = b_values_addr;
}

SIXTRL_INLINE void NS(TypeFixedNumPtrs_set_c_values_addr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    NS(cobj_address_t) const c_values_addr ) SIXTRL_NOEXCEPT
{
    if( obj != SIXTRL_NULLPTR ) obj->c_values_addr = c_values_addr;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
NS(TypeFixedNumPtrs_const_b_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeFixedNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return ( SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const* )( uintptr_t
        )NS(TypeFixedNumPtrs_b_values_addr)( obj );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
NS(TypeFixedNumPtrs_const_b_values_end)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeFixedNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const* ptr_end =
        NS(TypeFixedNumPtrs_const_b_values_begin)( obj );

    if( ptr_end != SIXTRL_NULLPTR )
    {
        ptr_end = ptr_end +  NS(TypeFixedNumPtrs_num_b_values)( obj );
    }

    return ptr_end;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
NS(TypeFixedNumPtrs_b_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
        )NS(TypeFixedNumPtrs_const_b_values_begin)( obj );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
NS(TypeFixedNumPtrs_b_values_end)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
        )NS(TypeFixedNumPtrs_const_b_values_end)( obj );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
NS(TypeFixedNumPtrs_const_c_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeFixedNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return ( SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const* )( uintptr_t
        )NS(TypeFixedNumPtrs_c_values_addr)( obj );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const*
NS(TypeFixedNumPtrs_const_c_values_end)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TypeFixedNumPtrs) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const* ptr_end =
        NS(TypeFixedNumPtrs_const_c_values_begin)( obj );

    if( ptr_end != SIXTRL_NULLPTR )
    {
        ptr_end = ptr_end +  NS(TypeFixedNumPtrs_num_c_values)( obj );
    }

    return ptr_end;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
NS(TypeFixedNumPtrs_c_values_begin)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
        )NS(TypeFixedNumPtrs_const_c_values_begin)( obj );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
NS(TypeFixedNumPtrs_c_values_end)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*
        )NS(TypeFixedNumPtrs_const_c_values_end)( obj );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_REAL_T NS(TypeFixedNumPtrs_b_value)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj, SIXTRL_UINT64_T const ii ) SIXTRL_NOEXCEPT
{
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const* ptr_begin =
        NS(TypeFixedNumPtrs_const_b_values_begin)( obj );

    return ( ( ptr_begin != SIXTRL_NULLPTR ) &&
             ( NS(TypeFixedNumPtrs_num_b_values)( obj ) > ii ) )
        ? ptr_begin[ ii ] : ( SIXTRL_REAL_T )0.0;
}

SIXTRL_INLINE SIXTRL_REAL_T NS(TypeFixedNumPtrs_c_value)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeFixedNumPtrs) *const
        SIXTRL_RESTRICT obj, SIXTRL_UINT64_T const ii ) SIXTRL_NOEXCEPT
{
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T const* ptr_begin =
        NS(TypeFixedNumPtrs_const_c_values_begin)( obj );

    return ( ( ptr_begin != SIXTRL_NULLPTR ) &&
             ( NS(TypeFixedNumPtrs_num_c_values)( obj ) > ii ) )
        ? ptr_begin[ ii ] : ( SIXTRL_REAL_T )0.0;
}

SIXTRL_INLINE void NS(TypeFixedNumPtrs_set_b_value)( SIXTRL_BUFFER_DATAPTR_DEC
        NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_UINT64_T const ii, SIXTRL_REAL_T const b_value ) SIXTRL_NOEXCEPT
{
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* ptr_begin =
        NS(TypeFixedNumPtrs_b_values_begin)( obj );

    if( ( ptr_begin != SIXTRL_NULLPTR ) &&
        ( NS(TypeFixedNumPtrs_num_b_values)( obj ) > ii ) )
    {
        ptr_begin[ ii ] = b_value;
    }
}

SIXTRL_INLINE void NS(TypeFixedNumPtrs_set_c_value)( SIXTRL_BUFFER_DATAPTR_DEC
        NS(TypeFixedNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_UINT64_T const ii, SIXTRL_REAL_T const c_value ) SIXTRL_NOEXCEPT
{
    SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T* ptr_begin =
        NS(TypeFixedNumPtrs_c_values_begin)( obj );

    if( ( ptr_begin != SIXTRL_NULLPTR ) &&
        ( NS(TypeFixedNumPtrs_num_c_values)( obj ) > ii ) )
    {
        ptr_begin[ ii ] = c_value;
    }
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_FIXED_NUM_PTRS_H__ */

