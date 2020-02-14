#ifndef SIXTRACKLIB_COMMON_INTERNAL_TYPE_STORE_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_TYPE_STORE_TRAITS_CXX_HPP__

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstdlib>
    #include <stdint.h>
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename T >
    struct TypeStoreTraits
    {
        typedef T           value_type;
        typedef T const&    const_reference;
        typedef T const*    const_pointer;
        typedef T&          reference;
        typedef T*          pointer;
    };

    template< typename T >
    struct TypeMethodParamTraits
    {
        typedef T           value_type;
        typedef T const&    argument_type;
        typedef T const&    const_existing_type;
        typedef T&          existing_type;
    };

    template< typename T >
    struct TypeScalarTraits
    {
        static SIXTRL_FN constexpr bool IsScalar() SIXTRL_NOEXCEPT
        {
            return true;
        }
    };

    template< typename T >
    struct TypeStorageAlignTraits
    {
        static SIXTRL_FN constexpr SIXTRL_CXX_NAMESPACE::arch_size_t
        Alignment() SIXTRL_NOEXCEPT
        {
            #if !defined( SIXTRL_ALIGN_NUM )
                #define SIXTRL_ALIGN_NUM_UNDEF
                #define SIXTRL_ALIGN_NUM 8
            #endif /* SIXTRL_ALIGN_NUM  */

            return ( alignof( T ) <= SIXTRL_ALIGN_NUM )
                ? static_cast< SIXTRL_CXX_NAMESPACE::arch_size_t >(
                    SIXTRL_ALIGN_NUM )
                : static_cast< SIXTRL_CXX_NAMESPACE::arch_size_t >(
                    ( ( alignof( T ) / SIXTRL_ALIGN_NUM ) +
                      ( ( ( alignof( T ) % SIXTRL_ALIGN_NUM ) == 0u ) ? 0 : 1 )
                    ) * SIXTRL_ALIGN_NUM );

            #if defined( SIXTRL_ALIGN_NUM_UNDEF )
                #undef SIXTRL_ALIGN_NUM
                #undef SIXTRL_ALIGN_NUM_UNDEF
            #endif  /* defined( SIXTRL_ALIGN_NUM_UNDEF ) */
        }
    };

    /* --------------------------------------------------------------------- */
    /* Convenience functions: */

    template< typename T >
    static SIXTRL_INLINE SIXTRL_FN constexpr
    bool Type_is_scalar() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeScalarTraits< T >::IsScalar();
    }

    template< typename T >
    static SIXTRL_FN constexpr
    SIXTRL_CXX_NAMESPACE::arch_size_t Type_storage_align() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeStorageAlignTraits< T >::Alignment();
    }

    /* ********************************************************************* */
    /* Specializations: */
    /* ********************************************************************* */

    /* --------------------------------------------------------------------- */
    /* double: */

    template<> struct TypeMethodParamTraits< double >
    {
        typedef double               value_type;
        typedef value_type const     argument_type;
        typedef value_type           const_existing_type;
        typedef value_type&          existing_type;
    };

    /* --------------------------------------------------------------------- */
    /* float: */

    template<> struct TypeMethodParamTraits< float >
    {
        typedef float                value_type;
        typedef value_type const     argument_type;
        typedef value_type           const_existing_type;
        typedef value_type&          existing_type;
    };

    /* --------------------------------------------------------------------- */
    /* uint64: */

    template<> struct TypeMethodParamTraits< uint64_t >
    {
        typedef uint64_t             value_type;
        typedef value_type const     argument_type;
        typedef value_type           const_existing_type;
        typedef value_type&          existing_type;
    };

    /* --------------------------------------------------------------------- */
    /* int64: */

    template<> struct TypeMethodParamTraits< int64_t >
    {
        typedef int64_t              value_type;
        typedef value_type const     argument_type;
        typedef value_type           const_existing_type;
        typedef value_type&          existing_type;
    };

    /* --------------------------------------------------------------------- */
    /* uint32: */

    template<> struct TypeMethodParamTraits< uint32_t >
    {
        typedef uint32_t             value_type;
        typedef value_type const     argument_type;
        typedef value_type           const_existing_type;
        typedef value_type&          existing_type;
    };

    /* --------------------------------------------------------------------- */
    /* int32: */

    template<> struct TypeMethodParamTraits< int32_t >
    {
        typedef int32_t              value_type;
        typedef value_type const     argument_type;
        typedef value_type           const_existing_type;
        typedef value_type&          existing_type;
    };

    /* --------------------------------------------------------------------- */
    /* uint16_t: */

    template<> struct TypeMethodParamTraits< uint16_t >
    {
        typedef uint16_t             value_type;
        typedef value_type const     argument_type;
        typedef value_type           const_existing_type;
        typedef value_type&          existing_type;
    };

    /* --------------------------------------------------------------------- */
    /* int16_t: */

    template<> struct TypeMethodParamTraits< int16_t >
    {
        typedef int16_t              value_type;
        typedef value_type const     argument_type;
        typedef value_type           const_existing_type;
        typedef value_type&          existing_type;
    };

    /* --------------------------------------------------------------------- */
    /* uint8_t: */

    template<> struct TypeMethodParamTraits< uint8_t >
    {
        typedef uint8_t              value_type;
        typedef value_type const     argument_type;
        typedef value_type           const_existing_type;
        typedef value_type&          existing_type;
    };

    /* --------------------------------------------------------------------- */
    /* int8_t: */

    template<> struct TypeMethodParamTraits< int8_t >
    {
        typedef int8_t               value_type;
        typedef value_type const     argument_type;
        typedef value_type           const_existing_type;
        typedef value_type&          existing_type;
    };

}

#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_TYPE_STORE_TRAITS_CXX_HPP__ */
