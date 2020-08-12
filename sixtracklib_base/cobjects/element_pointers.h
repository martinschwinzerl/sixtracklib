#ifndef SIXTRACKLIB_BASE_COBJECTS_ELEM_POINTERS_H__
#define SIXTRACKLIB_BASE_COBJECTS_ELEM_POINTERS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/definitions.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
    #include "sixtracklib_base/internal/obj_store_traits.h"
    #include "sixtracklib_base/internal/obj_c_api_traits.h"
    #include "sixtracklib_base/internal/obj_data_type_traits.h"
#endif /* SIXTRL_NO_INCLUDES */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* ===================================================================== */
    /* Provide a class that stores the maximum and minimum number of
     * dataptrs that an instance of ELem may contribute to a CObjects buffer
     *
     * Note: for min < max, the user will have to rely on a specialized
     *       helper class that does the actual run-time introspection */

    template< class Elem, typename _Enabled = void > struct CObjElemNumPointers
    {
        typedef  SIXTRL_CXX_NAMESPACE::size_t size_type;

        static constexpr size_type min_num_ptrs = size_type{ 0 };
        static constexpr size_type max_num_ptrs = size_type{ 0 };
    };

    template< class Elem, typename _Enabled >
    constexpr  SIXTRL_CXX_NAMESPACE::size_t
    CObjElemNumPointers< Elem, _Enabled >::min_num_ptrs;

    template< class Elem, typename _Enabled >
    constexpr  SIXTRL_CXX_NAMESPACE::size_t
    CObjElemNumPointers< Elem, _Enabled >::max_num_ptrs;

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E > struct CObjElemNumPointers< E, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type<E>() >::type >
    {
        typedef  SIXTRL_CXX_NAMESPACE::size_t size_type;

        static constexpr size_type min_num_ptrs =
            CObjElemNumPointers< typename ObjDataCApiTypeTraits<
                E >::c_api_t >::min_num_ptrs;

        static constexpr size_type max_num_ptrs =
            CObjElemNumPointers< typename ObjDataCApiTypeTraits<
                E >::c_api_t >::max_num_ptrs;
    };

    template< class E >
    constexpr  SIXTRL_CXX_NAMESPACE::size_t
    CObjElemNumPointers< E, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type<E>()
            >::type >::min_num_ptrs;

    template< class E >
    constexpr  SIXTRL_CXX_NAMESPACE::size_t
    CObjElemNumPointers< E, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type<E>()
            >::type >::max_num_ptrs;

    /* --------------------------------------------------------------------- */
    /* Convenience accessor and consistency check functions */

    template< class E > static SIXTRL_FN constexpr SIXTRL_CXX_NAMESPACE::size_t
    CObjElem_min_num_ptrs() SIXTRL_NOEXCEPT
    {
        return CObjElemNumPointers< E >::min_num_ptrs;
    }

    template< class E > static SIXTRL_FN constexpr SIXTRL_CXX_NAMESPACE::size_t
    CObjElem_max_num_ptrs() SIXTRL_NOEXCEPT
    {
        return CObjElemNumPointers< E >::max_num_ptrs;
    }

    template< class E > static SIXTRL_FN constexpr bool
    CObjElem_few_enough_ptrs_for_static_array() SIXTRL_NOEXCEPT
    {
        return ( SIXTRL_CXX_NAMESPACE::CObjElem_max_num_ptrs< E >() <=
                 SIXTRL_CXX_NAMESPACE::COBJECTS_STATIC_ARRAY_SIZE_LIMIT );
    }

    template< class E > static SIXTRL_FN constexpr bool
    CObjElem_too_many_ptrs_for_static_array() SIXTRL_NOEXCEPT
    {
        return ( SIXTRL_CXX_NAMESPACE::CObjElem_max_num_ptrs< E >() >
                 SIXTRL_CXX_NAMESPACE::COBJECTS_STATIC_ARRAY_SIZE_LIMIT );
    }

    template< class E > static SIXTRL_FN constexpr bool
    CObjElem_consistent_minmax_ptrs() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_max_num_ptrs< E >() >=
               SIXTRL_CXX_NAMESPACE::CObjElem_min_num_ptrs< E >();
    }

    /* --------------------------------------------------------------------- */
    /* Provide a helper struct which can be specialized for an E to
     * get the number of dataptrs from an instance of Elem.
     *
     * NOTE This is only used in situations where
     *      min_num_ptrs != max_num_ptrs, so it is safe to provide a
     *      general implementation here that returns the max_num_ptrs
     *      (which is always correct unless it's Inconsistent -> check that
     *       in a static_assert below) and rely on the user to specialize this
     *       helper for the cases where it's actually needed
     */

    template< class E > struct CObjElemNumPointersInspector
    {
        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::size_t num_ptrs(
            const E *const SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_elem )
                = nullptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::CObjElem_consistent_minmax_ptrs< E >(),
                           "Inconsistent min/max num dataptrs!" );

            return st::CObjElem_max_num_ptrs< E >();
        }
    };

    /* --------------------------------------------------------------------- */
    /* Predicates to distinguish between classes of E by their number of
     * defined dataptrs -> use these in any SFINAE related
     * if constexpr / std::enable_if clauses! See the CObjElem_num_ptrs()
     * function below for an example on how to do this! */

    template< class E > static SIXTRL_FN constexpr bool
        CObjElem_definitely_has_no_ptrs() SIXTRL_NOEXCEPT
    {
        return
        ( SIXTRL_CXX_NAMESPACE::CObjElem_consistent_minmax_ptrs< E >() ) &&
        ( SIXTRL_CXX_NAMESPACE::CObjElem_max_num_ptrs< E >() ==
           SIXTRL_CXX_NAMESPACE::size_t{ 0 } );
    }

    template< class E > static SIXTRL_FN constexpr bool
    CObjElem_allows_ptrs() SIXTRL_NOEXCEPT
    {
        return
        ( SIXTRL_CXX_NAMESPACE::CObjElem_consistent_minmax_ptrs< E >() ) &&
        ( SIXTRL_CXX_NAMESPACE::CObjElem_max_num_ptrs< E >() >
           SIXTRL_CXX_NAMESPACE::size_t{ 0 } );
    }

    template< class E > static SIXTRL_FN constexpr bool
    CObjElem_definitely_has_ptrs() SIXTRL_NOEXCEPT
    {
        return
        ( SIXTRL_CXX_NAMESPACE::CObjElem_consistent_minmax_ptrs< E >() ) &&
        ( SIXTRL_CXX_NAMESPACE::CObjElem_min_num_ptrs< E >() >
           SIXTRL_CXX_NAMESPACE::size_t{ 0 } );
    }

    template< class E > static SIXTRL_FN constexpr bool
    CObjElem_has_const_num_ptrs() SIXTRL_NOEXCEPT
    {
        return
            ( SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_ptrs< E >()) &&
            ( SIXTRL_CXX_NAMESPACE::CObjElem_min_num_ptrs< E >() ==
              SIXTRL_CXX_NAMESPACE::CObjElem_max_num_ptrs< E >() );
    }

    template< class E > static SIXTRL_FN constexpr bool
    CObjElem_allows_var_num_ptrs() SIXTRL_NOEXCEPT
    {
        return ( SIXTRL_CXX_NAMESPACE::CObjElem_min_num_ptrs< E >() <
                 SIXTRL_CXX_NAMESPACE::CObjElem_max_num_ptrs< E >() );
    }

    template< class E > static SIXTRL_FN constexpr bool
    CObjElem_definitely_has_var_num_ptrs() SIXTRL_NOEXCEPT
    {
        return
        ( SIXTRL_CXX_NAMESPACE::CObjElem_allows_var_num_ptrs< E >() ) &&
        ( SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_ptrs< E >() );
    }

    /* ==================================================================== */
    /* Provide a catch-all CObjElem_num_ptrs implementation which
     * is specialized to the different scenarios using the predicates
     * from above */

    template< class E > static SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type
    CObjElem_num_ptrs( SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
        SIXTRL_UNUSED( ptr_elem ) = nullptr ) SIXTRL_NOEXCEPT
    {
        return  SIXTRL_CXX_NAMESPACE::size_t{ 0 };
    }

    template< class E > static SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type
    CObjElem_num_ptrs( SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
        SIXTRL_UNUSED( ptr_elem ) = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_max_num_ptrs< E >();
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allows_var_num_ptrs< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type
    CObjElem_num_ptrs( SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
         ptr_elem = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_CXX_NAMESPACE::size_t num_ptrs =
            st::CObjElemNumPointersInspector< E >::num_ptrs( ptr_elem );

        if( num_ptrs > st::CObjElem_max_num_ptrs< E >() )
        {
            num_ptrs = st::CObjElem_max_num_ptrs< E >();
        }
        else if( ( st::CObjElem_min_num_ptrs< E >() > st::size_t{ 0 } ) &&
                 ( num_ptrs < st::CObjElem_min_num_ptrs< E >() ) )
        {
            num_ptrs = st::CObjElem_min_num_ptrs< E >();
        }

        return num_ptrs;
    }

    /* this ones is for cases where the min/max number of dataptrs is
     * not consistent -> should never happen but it's nice to provide a
     * meaningful error message */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_consistent_minmax_ptrs< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type
    CObjElem_num_ptrs( SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
        SIXTRL_UNUSED( ptr_elem ) = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::CObjElem_consistent_minmax_ptrs< E >(),
            "Inconsistent min/max number of dataptrs" );

        /* Will never execute because of the static_assert, but still
         * provide a sensible return statement, just in case */
        return st::CObjElem_min_num_ptrs< E >();
    }

    /* ===================================================================== */
    /* Provides methods to check whether a given dataptr index is legal or
     * not */

    template< class E, SIXTRL_CXX_NAMESPACE::size_t Idx >
    static SIXTRL_FN constexpr typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_consistent_minmax_ptrs< E >() ||
        SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >(), bool >::type
    CObjElem_dataptr_index_legal( SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_elem ) = nullptr ) SIXTRL_NOEXCEPT
    {
        return false;
    }

    template< class E, SIXTRL_CXX_NAMESPACE::size_t Idx >
    static SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >(), bool >::type
    CObjElem_dataptr_index_legal( SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_elem ) = nullptr
    ) SIXTRL_NOEXCEPT
    {
        return
            SIXTRL_CXX_NAMESPACE::CObjElem_consistent_minmax_ptrs< E >() &&
            ( SIXTRL_CXX_NAMESPACE::CObjElem_max_num_ptrs< E >() >  Idx );
    }

    template< class E, SIXTRL_CXX_NAMESPACE::size_t Idx >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allows_var_num_ptrs< E >(), bool >::type
    CObjElem_dataptr_index_legal( SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
            SIXTRL_RESTRICT ptr_elem = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return ( ( ptr_elem != nullptr ) &&
            ( st::CObjElem_consistent_minmax_ptrs< E >() ) &&
            ( st::CObjElem_max_num_ptrs< E >() >  Idx ) &&
            ( st::CObjElem_num_ptrs< E >( ptr_elem ) > Idx ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E, SIXTRL_CXX_NAMESPACE::size_t Idx >
    static SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() ||
        SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >(), bool >::type
    CObjElem_dataptr_index_illegal( SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_elem ) = nullptr
    ) SIXTRL_NOEXCEPT
    {
        return !SIXTRL_CXX_NAMESPACE::CObjElem_dataptr_index_legal< E, Idx >();
    }

    /* --------------------------------------------------------------------- */
    /* Idx parameter supplied via argument list rather th. as template param */

    template< class E >
    static SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_consistent_minmax_ptrs< E >() ||
         SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >(),
         bool >::type
    CObjElem_dataptr_index_legal(
        SIXTRL_CXX_NAMESPACE::size_t const SIXTRL_UNUSED( idx ),
        SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        return false;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
         SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >(), bool >::type
    CObjElem_dataptr_index_legal( SIXTRL_CXX_NAMESPACE::size_t const idx,
        SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr_elem ) = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::CObjElem_consistent_minmax_ptrs< E >(), "" );
        return ( st::CObjElem_max_num_ptrs< E >() > idx );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
    SIXTRL_CXX_NAMESPACE::CObjElem_allows_var_num_ptrs< E >(), bool >::type
    CObjElem_dataptr_index_legal( SIXTRL_CXX_NAMESPACE::size_t const idx,
        SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const SIXTRL_RESTRICT
            ptr_elem = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::CObjElem_consistent_minmax_ptrs< E >(), "" );

        return ( ( st::CObjElem_max_num_ptrs< E >() > idx ) &&
                 ( st::CObjElem_num_ptrs< E >( ptr_elem ) > idx ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E > static SIXTRL_INLINE SIXTRL_FN bool
    CObjElem_dataptr_index_illegal( SIXTRL_CXX_NAMESPACE::size_t const idx,
        SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const SIXTRL_RESTRICT ptr
    ) SIXTRL_NOEXCEPT
    {
        return !SIXTRL_CXX_NAMESPACE::CObjElem_dataptr_index_legal( idx, ptr );
    }
}

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_BASE_COBJECTS_ELEM_POINTERS_H__ */
