#ifndef SIXTRACKLIB_BASE_COBJECTS_FIELD_OFFSETS_H__
#define SIXTRACKLIB_BASE_COBJECTS_FIELD_OFFSETS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/definitions.h"
    #include "sixtracklib_base/cobjects/element_pointers.h"
    #include "sixtracklib_base/cobjects/c_api_helpers.h"
    #include "sixtracklib_base/cobjects/helper_functions.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
    #include "sixtracklib_base/internal/obj_store_traits.h"
#endif /* SIXTRL_NO_INCLUDES */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <type_traits>
        #include <vector>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class E > static  SIXTRL_FN constexpr bool
    CObjElem_can_obtain_field_offsets() SIXTRL_NOEXCEPT
    {
        return std::is_standard_layout< E >::value;
    }

    template< class E > static  SIXTRL_FN constexpr bool
    CObjElem_has_always_same_offsets() SIXTRL_NOEXCEPT
    {
        return
            SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() ||
            SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >();
    }

    template< class E > static  SIXTRL_FN constexpr bool
    CObjElem_requires_inspection_for_offsets() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_allows_var_num_ptrs< E >();
    }

    /* ===================================================================== */

    template< class E > struct CObjElemFieldOffsets
    {
        typedef SIXTRL_CXX_NAMESPACE::size_t size_type;
        static constexpr size_type offsets[ 1 ] = { size_type{ 0 } };
    };

    template< class E >
    constexpr SIXTRL_CXX_NAMESPACE::size_t CObjElemFieldOffsets< E >::offsets[];

    /* --------------------------------------------------------------------- */

    template< class E, typename _Enabled = void >
    struct CObjElemFieldOffsetsInspector
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_offsets<
                E >(),
            "Only use sixtrack::CObjElemFieldOffsetsInspector<> with Elem "
            "types which require inspection" );

        static SIXTRL_INLINE SIXTRL_FN status_t init_field_offsets(
            SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT
                SIXTRL_UNUSED( offsets_begin ),
            SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t const
                SIXTRL_UNUSED( max_num_offsets ),
            SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }
    };

    template< class E > struct CObjElemFieldOffsetsInspector< E,
        typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_offsets<
            E >() >::type >
    {
        static SIXTRL_INLINE SIXTRL_FN status_t init_field_offsets(
            SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
                SIXTRL_RESTRICT offsets_begin,
            SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t const max_num_offsets,
            SIXTRL_BUFFER_ARGPTR_DEC const E *const
                SIXTRL_RESTRICT ptr = nullptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef typename ObjDataCObjectsTypeIdTraits< E >::c_api_t c_api_t;

            return CObjElemFieldOffsetsInspector<
                c_api_t >::init_field_offsets( offsets_begin, max_num_offsets,
                    st::CObjElem_as_const_ptr_c_api< E >( ptr ) );
        }
    };

    /* --------------------------------------------------------------------- */

    template< class E >
    static SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type
    CObjElem_num_available_field_offsets(
            SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
                SIXTRL_RESTRICT SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::size_t{ 0 };
    }

    template< class E > static SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_has_always_same_offsets< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type
    CObjElem_num_available_field_offsets( SIXTRL_BUFFER_OBJ_DATAPTR_DEC const
        E *const SIXTRL_RESTRICT SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        return std::extent<
            decltype( CObjElemFieldOffsets< E >::offsets ) >::value;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_offsets< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type
    CObjElem_num_available_field_offsets(
            SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
                SIXTRL_RESTRICT ptr = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< E >( ptr );
    }

    /* --------------------------------------------------------------------- */

    template< class E > static SIXTRL_INLINE SIXTRL_FN bool
    CObjElem_consistent_field_offset_dims( SIXTRL_BUFFER_ARGPTR_DEC const E
        *const SIXTRL_RESTRICT ptr = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::CObjElem_num_ptrs< E >( ptr ) <=
               st::CObjElem_num_available_field_offsets< E >( ptr );
    }

    /* --------------------------------------------------------------------- */
    /* Provide a method to retrieve all field offsets in one go. Depending
     * on the number and nature of dataptrs, several different cases
     * can be distinguished: */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_field_offsets(
        SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT
            offsets_begin,
        SIXTRL_CXX_NAMESPACE::size_t const max_num_offsets_to_store,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::CObjElem_init_array_with_two_values( offsets_begin,
            max_num_offsets_to_store, sizeof( E ) );

        return st::STATUS_SUCCESS;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_field_offsets( SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT offsets_begin,
        SIXTRL_CXX_NAMESPACE::size_t const max_num_offsets_to_store,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT SIXTRL_UNUSED(
            ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        typedef typename ObjDataCApiTypeTraits< E >::c_api_t c_api_t;

        namespace st = SIXTRL_CXX_NAMESPACE;
        st::CObjElem_init_array_with_two_values( offsets_begin,
            max_num_offsets_to_store, sizeof( c_api_t ) );

        return st::STATUS_SUCCESS;
    }

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_has_always_same_offsets< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_field_offsets(
        SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT
            offsets_begin,
        SIXTRL_CXX_NAMESPACE::size_t const max_num_offsets_to_store,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT SIXTRL_UNUSED(
            ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( st::CObjElem_consistent_field_offset_dims< E >() );

        return st::CObjElem_init_array_as_copy_fill_remainder(
            offsets_begin, max_num_offsets_to_store,
                &CObjElemFieldOffsets< E >::offsets[ 0 ],
                    st::CObjElem_max_num_ptrs< E >(), sizeof( E ) );
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_has_always_same_offsets< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_field_offsets(
        SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT offsets_begin,
        SIXTRL_CXX_NAMESPACE::size_t const max_num_offsets_to_store,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            /* ptr */ = nullptr ) SIXTRL_NOEXCEPT
    {
        typedef typename ObjDataCApiTypeTraits< E >::c_api_t c_api_t;
        return SIXTRL_CXX_NAMESPACE::CObjElem_field_offsets< c_api_t >(
            offsets_begin, max_num_offsets_to_store, nullptr );
    }

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_offsets<E>(),
        status_t >::type
    CObjElem_field_offsets(
        SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT offsets_begin,
        SIXTRL_CXX_NAMESPACE::size_t const max_num_offsets_to_store,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            ptr = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::status_t status = st::STATUS_GENERAL_FAILURE;
        static_assert( st::CObjElem_consistent_minmax_ptrs< E >(),
            "Inconsistent min/max number of dataptrs" );

        st::size_t const ndataptrs = st::CObjElem_num_ptrs< E >( ptr );
        SIXTRL_ASSERT( ndataptrs <= st::CObjElem_max_num_ptrs< E >() );

        if( ndataptrs > st::size_t{ 0 } )
        {
            if( ( offsets_begin != nullptr ) &&
                ( max_num_offsets_to_store > st::size_t{ 0 } ) )
            {
                status = st::CObjElemFieldOffsetsInspector<
                    E >::init_field_offsets( offsets_begin,
                        max_num_offsets_to_store, ptr );

                if( ( status == st::STATUS_SUCCESS ) &&
                    ( max_num_offsets_to_store > ndataptrs ) )
                {
                    st::CObjElem_init_array_with_two_values(
                        offsets_begin + ndataptrs,
                        max_num_offsets_to_store - ndataptrs, sizeof( E ) );
                }
            }
        }
        else
        {
            if( ( offsets_begin != nullptr ) &&
                ( max_num_offsets_to_store > st::size_t{ 0 } ) )
            {
                st::CObjElem_init_array_with_two_values(
                    offsets_begin, max_num_offsets_to_store, sizeof( E ) );
            }

            status = st::STATUS_SUCCESS;
        }

        return status;
    }
}

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_BASE_COBJECTS_FIELD_OFFSETS_H__ */
