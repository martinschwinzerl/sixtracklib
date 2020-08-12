#ifndef SIXTRACKLIB_BASE_COBJECTS_FIELD_SIZES_H__
#define SIXTRACKLIB_BASE_COBJECTS_FIELD_SIZES_H__

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
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* ===================================================================== */
    /* There might be cases where the type of a dataptr field depends on
     * the state of the instance. This, however, will definitely be an
     * exception, most types are determined at the Elem type level.
     *
     * Still, provide a Traits struct to handle this but set the
     * default value to not use this degree of freedom */

    template< class Elem > struct CObjElemFieldTypeSizeTraits
    {
        static SIXTRL_FN constexpr bool HasFixedSize() SIXTRL_NOEXCEPT
        {
            return true;
        }
    };

    template< class E > static SIXTRL_FN constexpr
    bool CObjElem_has_always_same_sizes() SIXTRL_NOEXCEPT
    {
        return
            SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() ||
            ( SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >() &&
              SIXTRL_CXX_NAMESPACE::CObjElemFieldTypeSizeTraits <
                E >::HasFixedSize() );
    }

    template< class E > static SIXTRL_FN constexpr
    bool CObjElem_requires_inspection_for_sizes() SIXTRL_NOEXCEPT
    {
        return
               SIXTRL_CXX_NAMESPACE::CObjElem_allows_var_num_ptrs< E >() ||
            (  SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >() &&
              !SIXTRL_CXX_NAMESPACE::CObjElemFieldTypeSizeTraits <
                E >::HasFixedSize() );
    }

    /* --------------------------------------------------------------------- */

    template< class E > struct CObjElemFieldSizes
    {
        typedef SIXTRL_CXX_NAMESPACE::size_t size_type;

        /* The provided default implementation for sizes is intended
         * as a "template" on which the proper specialization can be based;
         * Ensure, that the number of entries in the sizes[] is actually
         * as large or larger than sixtrack::CObjElem_max_num_ptrs<>() */
        static constexpr size_type sizes[ 1 ] = { size_type{ 0 } };
    };

    template< class E > constexpr SIXTRL_CXX_NAMESPACE::size_t
    CObjElemFieldSizes< E >::sizes[];

    /* --------------------------------------------------------------------- */

    template< class E, typename _Enabled = void >
    struct CObjElemFieldSizesInspector
    {
        static_assert(
        SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_sizes< E >(),
        "Only use sixtrack::CObjElemFieldSizesInspector<> with Elem types "
        "which require inspection" );

        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::status_t
        init_field_sizes(
            SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT
                SIXTRL_UNUSED( sizes_begin ),
            SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t const
                SIXTRL_UNUSED( max_num_sizes ),
            SIXTRL_BUFFER_ARGPTR_DEC const E *const  SIXTRL_RESTRICT
                SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }
    };

    template< class E > struct CObjElemFieldSizesInspector< E,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >() &&
            SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_sizes< E >()
        >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::status_t status_type;
        typedef SIXTRL_CXX_NAMESPACE::size_t size_type;

        static SIXTRL_INLINE SIXTRL_FN status_type init_field_offsets(
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT sizes_begin,
            SIXTRL_ARGPTR_DEC size_type const max_num_sizes,
            SIXTRL_BUFFER_ARGPTR_DEC const E *const
                SIXTRL_RESTRICT ptr = nullptr ) SIXTRL_NOEXCEPT
        {
            typedef typename ObjDataCObjectsTypeIdTraits< E >::c_api_t c_api_t;
            return CObjElemFieldSizesInspector< c_api_t >::init_field_sizes(
                sizes_begin, max_num_sizes,
                SIXTRL_CXX_NAMESPACE::CObjElem_as_const_ptr_c_api< E >( ptr ) );
        }
    };

    /* --------------------------------------------------------------------- */

    template< class E > static SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type
    CObjElem_num_available_field_sizes(
            SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::size_t{ 0 };
    }

    template< class E > static SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
         SIXTRL_CXX_NAMESPACE::CObjElem_has_always_same_sizes< E >(),
         SIXTRL_CXX_NAMESPACE::size_t >::type
    CObjElem_num_available_field_sizes(
            SIXTRL_BUFFER_ARGPTR_DEC const E *const
                SIXTRL_RESTRICT SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        return std::extent< decltype( CObjElemFieldSizes< E >::sizes )>::value;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
         SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_sizes< E >(),
         SIXTRL_CXX_NAMESPACE::size_t >::type
     CObjElem_num_available_field_sizes( SIXTRL_BUFFER_ARGPTR_DEC const E *const
                SIXTRL_RESTRICT ptr = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< E >( ptr );
    }

    /* --------------------------------------------------------------------- */

    template< class E > static SIXTRL_INLINE SIXTRL_FN bool
    CObjElem_consistent_field_size_dims( SIXTRL_BUFFER_ARGPTR_DEC const E *const
        SIXTRL_RESTRICT ptr = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::CObjElem_num_ptrs< E >( ptr ) <=
               st::CObjElem_num_available_field_sizes< E >( ptr );
    }

    /* --------------------------------------------------------------------- */
    /* Provide a method to retrieve all field sizes in one go. Depending
     * on the number and nature of dataptrs, several different cases
     * can be distinguished: */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_consistent_minmax_ptrs< E >(),
         SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_field_sizes(
        SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT sizes_begin,
        SIXTRL_CXX_NAMESPACE::size_t const max_num_sizes_to_get,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const  SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::CObjElem_init_array_with_two_values( sizes_begin,
            max_num_sizes_to_get, st::size_t{ 0 } );

        return st::STATUS_GENERAL_FAILURE;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_consistent_minmax_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_field_sizes(
        SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT sizes_begin,
        SIXTRL_CXX_NAMESPACE::size_t const max_num_sizes_to_get,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const  SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        SIXTRL_CXX_NAMESPACE::CObjElem_init_array_with_two_values( sizes_begin,
            max_num_sizes_to_get, SIXTRL_CXX_NAMESPACE::size_t{ 0 } );
        return SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_consistent_minmax_ptrs< E >() &&
       !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_has_always_same_sizes< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_field_sizes(
        SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT sizes_begin,
        SIXTRL_CXX_NAMESPACE::size_t const max_num_sizes_to_get,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const  SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::CObjElem_consistent_field_size_dims< E >(),
            "Inconsistent field sizes" );

        return st::CObjElem_init_array_as_copy_fill_remainder( sizes_begin,
            max_num_sizes_to_get, &CObjElemFieldSizes< E >::sizes[ 0 ],
                st::CObjElem_max_num_ptrs< E >(), st::size_t{ 0 } );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN
    typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_consistent_minmax_ptrs< E >() &&
       !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_has_always_same_sizes< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_field_sizes(
        SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT sizes_begin,
        SIXTRL_CXX_NAMESPACE::size_t const max_num_sizes_to_get,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const  SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        typedef typename ObjDataCApiTypeTraits< E >::c_api_t c_api_t;
        return SIXTRL_CXX_NAMESPACE::CObjElem_field_sizes< c_api_t >(
            sizes_begin, max_num_sizes_to_get, nullptr );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN
    typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_consistent_minmax_ptrs< E >() &&
       !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_sizes< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_field_sizes(
        SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT sizes_begin,
        SIXTRL_CXX_NAMESPACE::size_t const max_num_sizes_to_get,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const  SIXTRL_RESTRICT
            ptr = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::status_t status = st::STATUS_GENERAL_FAILURE;

        st::size_t const ndataptrs = st::CObjElem_num_ptrs< E >( ptr );
        SIXTRL_ASSERT( ndataptrs <= st::CObjElem_max_num_ptrs< E >() );
        SIXTRL_ASSERT( st::CObjElem_consistent_field_size_dims< E >( ptr ) );

        if( ndataptrs > st::size_t{ 0 } )
        {
            if( ( sizes_begin != nullptr ) &&
                ( max_num_sizes_to_get > st::size_t{ 0 } ) )
            {
                status = st::CObjElemFieldSizesInspector< E>::init_field_sizes(
                    sizes_begin, max_num_sizes_to_get, ptr );

                if( ( status == st::STATUS_SUCCESS ) &&
                    ( max_num_sizes_to_get > ndataptrs ) )
                {
                    st::CObjElem_init_array_with_two_values(
                        sizes_begin + ndataptrs,
                        max_num_sizes_to_get - ndataptrs, st::size_t{ 0 } );
                }
            }
        }
        else
        {
            if( ( sizes_begin != nullptr ) &&
                ( max_num_sizes_to_get > st::size_t{ 0 } ) )
            {
                st::CObjElem_init_array_as_copy_fill_remainder( sizes_begin,
                    max_num_sizes_to_get, &CObjElemFieldSizes< E >::sizes[ 0 ],
                        st::CObjElem_max_num_ptrs< E >(), st::size_t{ 0 } );
            }

            status = st::STATUS_SUCCESS;
        }

        return status;
    }
}

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_BASE_COBJECTS_FIELD_SIZES_H__ */
