#ifndef SIXTRACKLIB_COMMON_COBJECTS_FIELD_OFFSETS_CXX_HPP__
#define SIXTRACKLIB_COMMON_COBJECTS_FIELD_OFFSETS_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus ) && !defined( _GPUCODE )
        #include <type_traits>
        #if !defined( _GPUCODE )
            #include <algorithm>
            #include <vector>
        #endif /* !defined( _GPUCODE ) */
    #endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/element_pointers.hpp"
    #include "sixtracklib/common/cobjects/c_api_helpers.hpp"
    #include "sixtracklib/common/cobjects/helper_functions.hpp"
    #include "sixtracklib/common/internal/buffer_object_defines.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
#endif /* SIXTRL_NO_INCLUDES */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_can_obtain_field_offsets() SIXTRL_NOEXCEPT
    {
        return std::is_standard_layout< E >::value;
    }

    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_has_always_same_offsets() SIXTRL_NOEXCEPT
    {
        return
            SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() ||
            SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >();
    }

    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_requires_inspection_for_offsets() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_allows_var_num_ptrs< E >();
    }

    /* ===================================================================== */

    template< class E >
    struct CObjElemFieldOffsets
    {
        static constexpr cobj_size_t offsets[ 1 ] = { cobj_size_t{ 0 } };
    };

    template< class E >
    constexpr cobj_size_t CObjElemFieldOffsets< E >::offsets[];

    /* --------------------------------------------------------------------- */

    template< class E, typename _Enabled = void >
    struct CObjElemFieldOffsetsInspector
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_offsets<
                E >(),
            "Only use sixtrack::CObjElemFieldOffsetsInspector<> with Elem "
            "types which require inspection" );

        static SIXTRL_INLINE SIXTRL_FN cobj_status_t init_field_offsets(
            SIXTRL_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT /* offsets_begin */,
            SIXTRL_ARGPTR_DEC cobj_size_t const /* max_num_offsets */,
            SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                /* ptr */ = nullptr ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::COBJECTS_STATUS_GENERAL_FAILURE;
        }
    };

    template< class E >
    struct CObjElemFieldOffsetsInspector< E, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_offsets<
            E >() >::type >
    {
        static SIXTRL_INLINE SIXTRL_FN cobj_status_t init_field_offsets(
            SIXTRL_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT offsets_begin,
            SIXTRL_ARGPTR_DEC cobj_size_t const max_num_offsets,
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
        cobj_size_t >::type CObjElem_num_available_field_offsets(
            SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
                SIXTRL_RESTRICT /* ptr */ = nullptr ) SIXTRL_NOEXCEPT
    {
        return cobj_size_t{ 0 };
    }

    template< class E >
    static SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_has_always_same_offsets< E >(),
        cobj_size_t >::type
    CObjElem_num_available_field_offsets(
            SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
                SIXTRL_RESTRICT /* ptr */ = nullptr ) SIXTRL_NOEXCEPT
    {
        return std::extent<
            decltype( CObjElemFieldOffsets< E >::offsets ) >::value;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_offsets< E >(),
        cobj_size_t >::type
    CObjElem_num_available_field_offsets(
            SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
                SIXTRL_RESTRICT ptr = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< E >( ptr );
    }

    /* --------------------------------------------------------------------- */

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN bool CObjElem_consistent_field_offset_dims(
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            ptr = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::CObjElem_num_ptrs< E >( ptr ) <=
               st::CObjElem_num_available_field_offsets< E >( ptr );
    }

    /* --------------------------------------------------------------------- */
    /* For the cases where there is a static constexpr array, provide a
     * method to return the begin address of the offsets: */

    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_has_field_offsets_begin_end_ptr() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_has_always_same_offsets< E >() &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_offsets< E >();
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t const*
    CObjElem_field_offsets_ptr_constexpr_begin() SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return ( st::ObjData_has_equivalent_c_api_type< E >() )
            ? ( st::CObjElem_field_offsets_ptr_constexpr_begin<
                    typename ObjDataCApiTypeTraits< E >::c_api_t >() )
            : ( ( st::CObjElem_has_field_offsets_begin_end_ptr< E >() )
                    ? &CObjElemFieldOffsets< E >::offsets[ 0 ] : nullptr );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t const*
    CObjElem_field_offsets_ptr_constexpr_end() SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return ( st::ObjData_has_equivalent_c_api_type< E >() )
            ? ( st::CObjElem_field_offsets_ptr_constexpr_end<
                    typename ObjDataCApiTypeTraits< E >::c_api_t >() )
            : ( ( st::CObjElem_has_field_offsets_begin_end_ptr< E >() )
                    ? st::CObjElem_field_offsets_ptr_constexpr_begin< E >() +
                      st::CObjElem_num_available_field_offsets< E >()
                    : nullptr );
    }

    /* --------------------------------------------------------------------- */
    /* Provide a method to retrieve all field offsets in one go. Depending
     * on the number and nature of dataptrs, several different cases
     * can be distinguished: */

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >(),
        SIXTRL_CXX_NAMESPACE::cobj_status_t >::type
    CObjElem_field_offsets(
        SIXTRL_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT offsets_begin,
        cobj_size_t const max_num_offsets_to_store,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            /* ptr */ = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::CObjElem_init_array_with_two_values< E >( offsets_begin,
            max_num_offsets_to_store, sizeof( E ) );

        return st::COBJECTS_STATUS_SUCCESS;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_has_field_offsets_begin_end_ptr< E >(),
        cobj_status_t >::type
    CObjElem_field_offsets(
        SIXTRL_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT offsets_begin,
        cobj_size_t const max_num_offsets_to_store,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            /* ptr */ = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( st::CObjElem_consistent_field_offset_dims< E >() );

        return st::CObjElem_init_array_as_copy_fill_remainder(
            offsets_begin, max_num_offsets_to_store,
                st::CObjElem_field_offsets_ptr_constexpr_begin< E >(),
                    st::CObjElem_max_num_ptrs< E >(), sizeof( E ) );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
       !SIXTRL_CXX_NAMESPACE::CObjElem_has_field_offsets_begin_end_ptr< E >()&&
        SIXTRL_CXX_NAMESPACE::CObjElem_has_always_same_offsets< E >(),
        cobj_status_t >::type
    CObjElem_field_offsets(
        SIXTRL_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT offsets_begin,
        cobj_size_t const max_num_offsets_to_store,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            /* ptr */ = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( st::CObjElem_consistent_field_offset_dims< E >() );

        return st::CObjElem_init_array_as_copy_fill_remainder(
            offsets_begin, max_num_offsets_to_store,
                &CObjElemFieldOffsets< E >::offsets[ 0 ],
                st::CObjElem_max_num_ptrs< E >(), sizeof( E ) );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_offsets<E>(),
        cobj_status_t >::type
    CObjElem_field_offsets(
        SIXTRL_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT offsets_begin,
        cobj_size_t const max_num_offsets_to_store,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            ptr = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        typedef st::cobj_size_t _size_t;

        static_assert( st::CObjElem_consistent_minmax_ptrs< E >(),
            "Inconsistent min/max number of dataptrs" );

        _size_t const ndataptrs = st::CObjElem_num_ptrs< E >( ptr );
        SIXTRL_ASSERT( ndataptrs <= st::CObjElem_max_num_ptrs< E >() );

        if( ndataptrs > _size_t{ 0 } )
        {
            if( ( offsets_begin != nullptr ) &&
                ( max_num_offsets_to_store > _size_t{ 0 } ) )
            {
                status = st::CObjElemFieldOffsetsInspector<
                    E >::init_field_offsets( offsets_begin,
                        max_num_offsets_to_store, ptr );

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
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
                ( max_num_offsets_to_store > st::cobj_size_t{ 0 } ) )
            {
                st::CObjElem_init_array_with_two_values(
                    offsets_begin, max_num_offsets_to_store, sizeof( E ) );
            }

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }
}

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_COBJECTS_FIELD_OFFSETS_CXX_HPP__ */
