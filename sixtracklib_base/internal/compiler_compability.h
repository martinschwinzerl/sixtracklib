#ifndef SIXTRACKLIB_BASE_INTERNAL_COMPILER_COMPABILITY__
#define SIXTRACKLIB_BASE_INTERNAL_COMPILER_COMPABILITY__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <iterator>
        #include <memory>
        #include <utility>
        #include <type_traits>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    #if !defined( _GPUCODE )
    template< typename T, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN std::unique_ptr< T >
    make_unique( Args&&... args )
    {
        return std::unique_ptr< T >( new T( std::forward< Args >( args )... ) );
    }
    #endif /* !defined( _GPUCODE ) */

    /* type-trait for is_iterator */

    template< typename T, typename Enabled = void >
    struct is_iterator
    {
       static constexpr bool value = false;
    };

    template< typename T >
    struct is_iterator< T, typename std::enable_if<
        !std::is_same< typename std::iterator_traits< T >::value_type,
            void>::value, void >::type >
    {
       static constexpr bool value = true;
    };

    template< typename T, typename Enabled >
    constexpr bool is_iterator< T, Enabled >::value;

}
#endif /* C++ */
#endif /* SIXTRACKLIB_BASE_INTERNAL_COMPILER_COMPABILITY__ */
