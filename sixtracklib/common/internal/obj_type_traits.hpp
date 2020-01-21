#ifndef SIXTRACKLIB_COMMON_INTERNAL_OBJ_TYPE_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_OBJ_TYPE_TRAITS_CXX_HPP__

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <cstdlib>
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
        typedef std::size_t size_type;

        static SIXTRL_INLINE SIXTRL_FN constexpr
        size_type StorageAlign() SIXTRL_NOEXCEPT
        {
            /* DEFAULT_ALIGN should be 8u */
            constexpr size_type DEFAULT_ALIGN =
                static_cast< size_type >( SIXTRL_ALIGN_NUM );

            return ( alignof( T ) > DEFAULT_ALIGN )
                  ?  alignof( T ) : DEFAULT_ALIGN;
        }

        static SIXTRL_INLINE SIXTRL_FN constexpr
        bool IsScalar() SIXTRL_NOEXCEPT
        {
            return true;
        }
    };

    template< typename T > static SIXTRL_INLINE SIXTRL_FN constexpr
    bool Type_is_scalar() SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::TypeStoreTraits< T >::Scalar();
    }

    template< typename T > static SIXTRL_INLINE SIXTRL_FN constexpr
    typename SIXTRL_CXX_NAMESPACE::TypeStoreTraits< T >::size_type
    Type_storage_align() SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::TypeStoreTraits< T >::StorageAlign();
    }
}

#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_TYPE_TRAITS_CXX_HPP__ */
