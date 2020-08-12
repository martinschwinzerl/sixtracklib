#ifndef SIXTRACKLIB_BASE_COBJECTS_FIELD_COUNTS_H__
#define SIXTRACKLIB_BASE_COBJECTS_FIELD_COUNTS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/definitions.h"
    #include "sixtracklib_base/cobjects/element_pointers.h"
    #include "sixtracklib_base/cobjects/helper_functions.h"
    #include "sixtracklib_base/cobjects/c_api_helpers.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
    #include "sixtracklib_base/internal/obj_store_traits.h"
#endif /* SIXTRL_NO_INCLUDES */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <vector>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class E, typename _Enabled = void > struct CObjElemFieldCounts
    {
        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::status_t
        init_field_counts( SIXTRL_BUFFER_ARGPTR_DEC
                SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT counts_begin,
            SIXTRL_CXX_NAMESPACE::size_t const max_num_counts,
            SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::CObjElem_init_array_with_two_values(
                counts_begin, max_num_counts, st::size_t{ 0 } );

            return ( ( st::CObjElem_consistent_minmax_ptrs< E >() ) &&
                     ( st::CObjElem_definitely_has_no_ptrs< E >() ) )
                   ? st::STATUS_SUCCESS : st::STATUS_GENERAL_FAILURE;
        }
    };

    template< class E >
    struct CObjElemFieldCounts< E, typename
        std::enable_if< SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type<
            E >() >::type >
    {
        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::status_t
        init_field_counts(
            SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
                SIXTRL_RESTRICT counts_begin,
            SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t const
                max_num_counts,
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

    template< class E > static SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >
    CObjElem_field_counts(
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT counts_begin,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t
            const max_num_counts,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::CObjElem_init_array_with_two_values(
            counts_begin, max_num_counts, st::size_t{ 0 } );

        return st::STATUS_SUCCESS;
    }

    template< class E > static SIXTRL_FN typename std::enable_if<
         SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        ( SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >() ||
          SIXTRL_CXX_NAMESPACE::CObjElem_allows_var_num_ptrs< E >() ),
          SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_field_counts(
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT counts_begin,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t
            const max_num_counts,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr =
            nullptr ) SIXTRL_NOEXCEPT
    {
        return CObjElemFieldCounts< E >::init_field_counts(
                counts_begin, max_num_counts, ptr );
    }
}

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_BASE_COBJECTS_FIELD_COUNTS_H__ */
