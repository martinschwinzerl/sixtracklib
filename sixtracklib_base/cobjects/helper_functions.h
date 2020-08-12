#ifndef SIXTRACKLIB_BASE_COBJECTS_HELPER_FUNCTIONS_H__
#define SIXTRACKLIB_BASE_COBJECTS_HELPER_FUNCTIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/definitions.h"
    #include "sixtracklib_base/cobjects/index_object.h"
#endif /* SIXTRL_NO_INCLUDES */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< typename T > static SIXTRL_INLINE SIXTRL_FN status_t
    CObjElem_init_array_with_two_values(
        SIXTRL_ARGPTR_DEC T* SIXTRL_RESTRICT dest_begin,
        SIXTRL_CXX_NAMESPACE::size_t const max_dest_begin_values,
        T const& SIXTRL_RESTRICT_REF first_value,
        T const& SIXTRL_RESTRICT_REF second_value = T{},
        SIXTRL_CXX_NAMESPACE::size_t const num_second_values =
            SIXTRL_CXX_NAMESPACE::size_t{ 0 } ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( dest_begin != nullptr ) &&
            ( max_dest_begin_values > st::size_t{ 0 } ) )
        {
            if( ( num_second_values == st::size_t{ 0 } ) ||
                ( first_value == second_value ) )
            {
                for( st::size_t ii = st::size_t{ 0 } ;
                    ii < max_dest_begin_values ; ++ii )
                {
                    dest_begin[ ii ] = first_value;
                }
            }
            else
            {
                st::size_t const num_first_values =
                    ( max_dest_begin_values > num_second_values )
                        ? max_dest_begin_values - num_second_values
                        : st::size_t{ 0 };

                st::size_t ii = st::size_t{ 0 };

                for( ; ii < num_first_values ; ++ii )
                {
                    dest_begin[ ii ] = first_value;
                }

                for( ; ii < max_dest_begin_values ; ++ii )
                {
                    dest_begin[ ii ] = second_value;
                }
            }

            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    template< typename T >
    static SIXTRL_INLINE SIXTRL_FN status_t
    CObjElem_init_array_as_copy_fill_remainder(
        SIXTRL_ARGPTR_DEC T* SIXTRL_RESTRICT dest_begin,
        SIXTRL_CXX_NAMESPACE::size_t const max_dest_begin_values,
        SIXTRL_ARGPTR_DEC T const* SIXTRL_RESTRICT orig_values,
        SIXTRL_CXX_NAMESPACE::size_t const num_orig_values,
        T const& SIXTRL_RESTRICT_REF fill_value ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( dest_begin != nullptr ) && ( orig_values != nullptr ) &&
            ( dest_begin != orig_values ) &&
            ( max_dest_begin_values >= num_orig_values ) )
        {
            st::size_t ii = st::size_t{ 0 };

            for( ; ii < num_orig_values ; ++ii )
            {
                dest_begin[ ii ] = orig_values[ ii ];
            }

            for( ; ii < max_dest_begin_values ; ++ii )
            {
                dest_begin[ ii ] = fill_value;
            }

            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    template< typename LhsIter, typename RhsIter >
    static SIXTRL_INLINE SIXTRL_FN bool CObjElem_arrays_are_equal(
        LhsIter lhs_it,  LhsIter lhs_end, RhsIter rhs_it ) SIXTRL_NOEXCEPT
    {
        #if !defined( _GPUCODE )
        return std::equal( lhs_it, lhs_end, rhs_it );
        #else

        bool ranges_are_equal = ( *lhs_it++ == *rhs_it++ );

        while( ( ranges_are_equal ) && ( lhs_it != lhs_end ) )
        {
            ranges_are_equal = ( *lhs_it++ == *rhs_it++ );


        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
        {
            if( *lhs_it != *rhs_it )
            {
                ranges_are_equal = false;
                break;
            }
        }

        return ranges_are_equal;
        #endif /* _GPUCODE */
    }

    template< typename Iter >
    static SIXTRL_INLINE SIXTRL_FN bool CObjElem_array_is_sorted(
        Iter it, Iter end ) SIXTRL_NOEXCEPT
    {
        #if !defined( _GPUCODE )
        return std::is_sorted( it, end );

        #else
        bool are_sorted = ( it == end );

        if( !are_sorted )
        {
            Iter prev_it = it++;
            are_sorted = true

            while( ( are_sorted ) && ( it != end ) )
            {
                are_sorted = ( *prev_it <= *it );
                prev_it = it++;
            }
        }

        return are_sorted;
        #endif /* _GPUCODE */
    }
}

#endif /* C++ */
#endif /* SIXTRACKLIB_BASE_COBJECTS_HELPER_FUNCTIONS_H__ */
