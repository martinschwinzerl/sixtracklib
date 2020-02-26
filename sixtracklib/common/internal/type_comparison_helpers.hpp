#ifndef SIXTRACKLIB_COMMON_INTERNAL_TYPE_COMPARISON_HELPERS_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_TYPE_COMPARISON_HELPERS_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstdlib>
    #include <stdint.h>
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename T >
    struct TypeCompLogicTypeTraits
    {
        typedef bool logic_t;
    };

    /* ********************************************************************** */

    template< class Logic >
    struct TypeCompLogicOps
    {
        typedef typename TypeMethodParamTraits< Logic >::argument_type
                logic_arg_t;

        static SIXTRL_FN bool any( logic_arg_t expr ) SIXTRL_NOEXCEPT
        {
            return ( expr ) ? true : false;
        }

        static SIXTRL_FN bool all( logic_arg_t expr ) SIXTRL_NOEXCEPT
        {
            return ( expr ) ? true : false;
        }
    };

    /* Specialization */

    template<> struct TypeCompLogicOps< bool >
    {
        typedef bool const logic_arg_t;

        static SIXTRL_INLINE SIXTRL_FN bool any(
            logic_arg_t expr ) SIXTRL_NOEXCEPT
        {
            return expr;
        }

        static SIXTRL_INLINE SIXTRL_FN bool all(
            logic_arg_t expr ) SIXTRL_NOEXCEPT
        {
            return expr;
        }
    };

    template< typename T >
    static SIXTRL_FN bool Type_comp_all(
        typename TypeMethodParamTraits< typename TypeCompLogicTypeTraits<
            T >::logic_t >::argument_type expression ) SIXTRL_NOEXCEPT
    {
        typedef typename TypeCompLogicTypeTraits< T >::logic_t _logic_t;
        return TypeCompLogicOps< _logic_t >::all( expression );
    }

    template< typename T >
    static SIXTRL_FN bool Type_comp_any(
        typename TypeMethodParamTraits< typename TypeCompLogicTypeTraits<
            T >::logic_t >::argument_type expression ) SIXTRL_NOEXCEPT
    {
        typedef typename TypeCompLogicTypeTraits< T >::logic_t _logic_t;
        return TypeCompLogicOps< _logic_t >::any( expression );
    }

    /* ********************************************************************** */

    template< typename T >
    static SIXTRL_FN constexpr bool
    TypeComp_consitent_logic_type() SIXTRL_NOEXCEPT
    {
        /* The type T and its associated logic_t type have to share the same
         * behaviour with respect to being a scalar
         *
         * TODO: Expand this to enforce cardinality -> i.e. a vector valued
         *       type neeeds a vector valued logic_t with the same dimensions,
         *       etc. */

        return
            ( ( SIXTRL_CXX_NAMESPACE::Type_is_scalar< T >() ) &&
              ( SIXTRL_CXX_NAMESPACE::Type_is_scalar<
                    typename TypeCompLogicTypeTraits< T >::logic_t >() )
            ) ||
            ( ( !SIXTRL_CXX_NAMESPACE::Type_is_scalar< T >() ) &&
              ( !SIXTRL_CXX_NAMESPACE::Type_is_scalar<
                    typename TypeCompLogicTypeTraits< T >::logic_t >() ) );
    }

    template< typename T >
    static SIXTRL_FN typename TypeCompLogicTypeTraits< T >::logic_t
    Type_comp_less(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        typedef typename TypeCompLogicTypeTraits< T >::logic_t _logic_t;
        static_assert(
            SIXTRL_CXX_NAMESPACE::TypeComp_consitent_logic_type< T >(),
            "base type T and logic type are inconsistent" );

        return _logic_t{ lhs < rhs };
    }

    template< typename T >
    static SIXTRL_FN typename TypeCompLogicTypeTraits< T >::logic_t
    Type_comp_equal(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        typedef typename TypeCompLogicTypeTraits< T >::logic_t _logic_t;
        static_assert(
            SIXTRL_CXX_NAMESPACE::TypeComp_consitent_logic_type< T >(),
            "base type T and logic type are inconsistent" );

        return _logic_t{ lhs == rhs };
    }

    template< typename T >
    static SIXTRL_FN typename TypeCompLogicTypeTraits< T >::logic_t
    Type_comp_less_or_equal(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        typedef typename TypeCompLogicTypeTraits< T >::logic_t _logic_t;
        static_assert(
            SIXTRL_CXX_NAMESPACE::TypeComp_consitent_logic_type< T >(),
            "base type T and logic type are inconsistent" );

        return _logic_t{ ( lhs < rhs ) || ( lhs == rhs ) };
    }

    template< typename T >
    static SIXTRL_FN typename TypeCompLogicTypeTraits< T >::logic_t
    Type_comp_more(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return !SIXTRL_CXX_NAMESPACE::Type_comp_less_or_equal< T >(
            lhs, rhs );
    }

    template< typename T >
    static SIXTRL_FN typename TypeCompLogicTypeTraits< T >::logic_t
    Type_comp_more_or_equal(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return !SIXTRL_CXX_NAMESPACE::Type_comp_less< T >( lhs, rhs );
    }

    template< typename T >
    static SIXTRL_FN typename TypeCompLogicTypeTraits< T >::logic_t
    Type_comp_not_equal(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return !SIXTRL_CXX_NAMESPACE::Type_comp_equal< T >( lhs, rhs );
    }

    template< typename T >
    static SIXTRL_FN typename bool Type_comp_is_close(
        TypeMethodParamTraits< T >::argument_type lhs,
        TypeMethodParamTraits< T >::argument_type rhs,
        TypeMethodParamTraits< T >::argument_type rel_tol,
        TypeMethodParamTraits< T >::argument_type abs_tol ) SIXTRL_NOEXCEPT
    {
        /* TODO: Specialize for integral types to avoid coparison warnings
         *       with signed 0 for unsigned types */

        typedef typename TypeMethodParamTraits< T >::value_type _val_t;

        _val_t diff = lhs - rhs;
        _val_t const sign_rhs  = ( _val_t{ 0 } < rhs  ) - ( rhs  - _val_t{ 0 } );
        _val_t const sign_diff = ( _val_t{ 0 } < diff ) - ( diff - _val_t{ 0 } );
        _val_t cmp_value = rhs;

        cmp_value *= sign_rhs;
        cmp_value *= rel_tol;
        cmp_value += abs_tol;
        diff      *= sign_diff;

        return SIXTRL_CXX_NAMESPACE::Type_comp_less_or_equal( diff, cmp_value );
    }

    /* ====================================================================== */

    template< typename T >
    static SIXTRL_FN bool Type_comp_all_less(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_all< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_less< T >( lhs, rhs ) );
    }

    template< typename T >
    static SIXTRL_FN bool Type_comp_any_less(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_any< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_less< T >( lhs, rhs ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

    template< typename T >
    static SIXTRL_FN bool Type_comp_all_equal(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_all< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_equal< T >( lhs, rhs ) );
    }

    template< typename T >
    static SIXTRL_FN bool Type_comp_any_equal(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_any< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_equal< T >( lhs, rhs ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

    template< typename T >
    static SIXTRL_FN bool Type_comp_all_less_or_equal(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_all< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_less_or_equal< T >( lhs, rhs ) );
    }

    template< typename T >
    static SIXTRL_FN bool Type_comp_any_less_or_equal(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_any< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_less_or_equal< T >( lhs, rhs ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

    template< typename T >
    static SIXTRL_FN bool Type_comp_all_more(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_all< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_more< T >( lhs, rhs ) );
    }

    template< typename T >
    static SIXTRL_FN bool Type_comp_any_more(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_any< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_more< T >( lhs, rhs ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

    template< typename T >
    static SIXTRL_FN bool Type_comp_all_more_or_equal(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_all< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_more_or_equal< T >( lhs, rhs ) );
    }

    template< typename T >
    static SIXTRL_FN bool Type_comp_any_more_or_equal(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_any< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_more_or_equal< T >( lhs, rhs ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

    template< typename T >
    static SIXTRL_FN bool Type_comp_all_not_equal(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_all< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_not_equal< T >( lhs, rhs ) );
    }

    template< typename T >
    static SIXTRL_FN bool Type_comp_any_not_equal(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_any< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_not_equal< T >( lhs, rhs ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

    template< typename T >
    static SIXTRL_FN bool Type_comp_all_are_close(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs,
        typename TypeMethodParamTraits< T >::argument_type rel_tol,
        typename TypeMethodParamTraits< T >::argument_type abs_tol
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_all< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_is_close< T >(
                lhs, rhs, rel_tol, abs_tol ) );
    }

    template< typename T >
    static SIXTRL_FN bool Type_comp_any_are_close(
        typename TypeMethodParamTraits< T >::argument_type lhs,
        typename TypeMethodParamTraits< T >::argument_type rhs,
        typename TypeMethodParamTraits< T >::argument_type rel_tol,
        typename TypeMethodParamTraits< T >::argument_type abs_tol
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Type_comp_any< T >(
            SIXTRL_CXX_NAMESPACE::Type_comp_is_close< T >(
                lhs, rhs, rel_tol, abs_tol ) );
    }

}
#endif /* defined( __cplusplus ) */


#endif /* SIXTRACKLIB_COMMON_INTERNAL_TYPE_COMPARISON_HELPERS_CXX_HPP__ */
