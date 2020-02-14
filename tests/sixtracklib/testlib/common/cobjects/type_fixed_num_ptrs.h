#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_FIXED_NUM_PTRS_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_FIXED_NUM_PTRS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/obj_base_class.hpp"
    #include "sixtracklib/common/cobjects/element_pointers.hpp"
    #include "sixtracklib/common/cobjects/field_offsets.hpp"
    #include "sixtracklib/common/cobjects/field_sizes.hpp"
    #include "sixtracklib/common/cobjects/field_counts.hpp"
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
    NS(cobj_address_t)  b_values        SIXTRL_ALIGN( 8 );
    SIXTRL_UINT64_T     num_c_values    SIXTRL_ALIGN( 8 );
    NS(cobj_address_t)  c_values        SIXTRL_ALIGN( 8 );
}
NS(TypeFixedNumPtrs);

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

    template<> struct CObjElemNumPointers< ::NS(TypeFixedNumPtrs) >
    {
        static constexpr cobj_size_t min_num_ptrs = cobj_size_t{ 2 };
        static constexpr cobj_size_t max_num_ptrs = cobj_size_t{ 2 };
    };

    template<> struct CObjElemFieldOffsets< ::NS(TypeFixedNumPtrs) >
    {
        static constexpr cobj_size_t offsets[] =
        {
            offsetof( ::NS(TypeFixedNumPtrs), b_values ),
            offsetof( ::NS(TypeFixedNumPtrs), c_values )
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
#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_FIXED_NUM_PTRS_H__ */

