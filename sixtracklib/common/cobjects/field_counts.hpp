#ifndef SIXTRACKLIB_COMMON_COBJECT_FIELD_COUNTS_CXX_HPP__
#define SIXTRACKLIB_COMMON_COBJECT_FIELD_COUNTS_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #if !defined( _GPUCODE )
            #include <vector>
        #endif /* !defined( _GPUCODE ) */
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/element_pointers.hpp"
    #include "sixtracklib/common/cobjects/helper_functions.hpp"
    #include "sixtracklib/common/cobjects/c_api_helpers.hpp"
    #include "sixtracklib/common/internal/buffer_object_defines.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
#endif /* SIXTRL_NO_INCLUDES */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class E, typename _Enabled = void >
    struct CObjElemFieldCounts
    {
        static SIXTRL_INLINE SIXTRL_FN cobj_status_t init_field_counts(
            SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT counts_begin,
            cobj_size_t const max_num_counts,
            SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                /* ptr */ = nullptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::cobj_status_t status = st::COBJECTS_STATUS_GENERAL_FAILURE;

            if( ( st::CObjElem_consistent_minmax_ptrs< E >() ) &&
                ( st::CObjElem_definitely_has_no_ptrs< E >() ) )
            {
                status = st::COBJECTS_STATUS_SUCCESS;
            }

            st::CObjElem_init_array_with_two_values(
                counts_begin, max_num_counts, st::cobj_size_t{ 0 } );

            return status;
        }
    };

    template< class E >
    struct CObjElemFieldCounts< E, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type<E>() >::type >
    {
        static SIXTRL_INLINE SIXTRL_FN cobj_status_t init_field_counts(
            SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT counts_begin,
            SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t const max_num_counts,
            SIXTRL_BUFFER_ARGPTR_DEC const E *const
                SIXTRL_RESTRICT ptr = nullptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef typename ObjDataCObjectsTypeIdTraits< E >::c_api_t c_api_t;

            return CObjElemFieldCounts< c_api_t >::init_field_counts(
                counts_begin, max_num_counts,
                    st::CObjElem_as_const_ptr_c_api< E >( ptr ) );
        }
    };

    /* ********************************************************************* */

    template< class E >
    static SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >(),
        cobj_status_t >
    CObjElem_field_counts(
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT counts_begin,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t const max_num_counts,
            SIXTRL_BUFFER_ARGPTR_DEC const E *const
                SIXTRL_RESTRICT /*ptr*/ = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::CObjElem_init_array_with_two_values(
            counts_begin, max_num_counts, st::cobj_size_t{ 0 } );

        return st::COBJECTS_STATUS_SUCCESS;
    }

    template< class E >
    static SIXTRL_FN typename std::enable_if<
         SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        ( SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >() ||
          SIXTRL_CXX_NAMESPACE::CObjElem_allows_var_num_ptrs< E >() ),
        cobj_status_t >::type
    CObjElem_field_counts(
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT counts_begin,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t const max_num_counts,
            SIXTRL_BUFFER_ARGPTR_DEC const E *const
                SIXTRL_RESTRICT ptr = nullptr ) SIXTRL_NOEXCEPT
    {
        return CObjElemFieldCounts< E >::init_field_counts(
                counts_begin, max_num_counts, ptr );
    }

}

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_COBJECT_FIELD_COUNTS_CXX_HPP__ */

