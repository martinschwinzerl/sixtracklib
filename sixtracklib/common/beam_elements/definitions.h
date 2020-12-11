#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DEFINITIONS_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DEFINITIONS_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"

    #if defined( __cplusplus )
        #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
        #include "sixtracklib/common/internal/obj_data_type_traits.hpp"
        #include "sixtracklib/common/internal/type_store_traits.hpp"
    #endif /* defined( __cplusplus ) */

#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __cplusplus )
    #if !defined( SIXTRL_BELEM_ADDR_TO_PTR )
        #define SIXTRL_BELEM_ADDR_TO_PTR( T, ( belem_address ) ) \
            ( T )( uintptr_t )( belem_address )
    #endif /* !defined( SIXTRL_BELEM_ADDR_TO_PTR \ */

#else /* C++ */
    #if !defined( SIXTRL_BELEM_ADDR_TO_PTR )
        #define SIXTRL_BELEM_ADDR_TO_PTR( T, belem_address ) \
            reinterpret_cast< T >( static_cast< uintptr_t >( ( belem_address ) ) )
    #endif /* !defined( SIXTRL_BELEM_ADDR_TO_PTR \ */

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
extern "C" {
#endif /* C++, Host  */

typedef SIXTRL_UINT64_T NS(be_size_t);
typedef SIXTRL_REAL_T   NS(be_real_t);
typedef SIXTRL_INT64_T  NS(be_order_t);
typedef SIXTRL_UINT64_T NS(be_address_t);
typedef SIXTRL_UINT64_T NS(belem_address_t);
typedef SIXTRL_UINT64_T NS(belem_type_id_t);


#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
}
#endif /* C++, Host  */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(be_size_t)         be_size_t;
    typedef ::NS(be_real_t)         be_real_t;
    typedef ::NS(be_order_t)        be_order_t;
    typedef ::NS(be_address_t)      be_address_t;
    typedef ::NS(belem_address_t)   belem_address_t;
    typedef ::NS(belem_type_id_t)   belem_type_id_t;

    /* --------------------------------------------------------------------- */

    template< class BeamElementT >
    struct ObjDataBeamElementsTraits
    {
        static constexpr bool is_beam_element = false;
    };

    template< class BeamElementT >
    constexpr bool ObjDataBeamElementsTraits< BeamElementT >::is_beam_element;

    template< class BeamElementT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    ObjData_is_beam_element() SIXTRL_NOEXCEPT
    {
        return ObjDataBeamElementsTraits< BeamElementT >::is_beam_element;
    }
}
#endif /* defined( __cplusplus ) */

#if !defined( SIXTRL_BE_ARGPTR_DEC )
    #define SIXTRL_BE_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC )
        #define  SIXTRL_BE_ARGPTR_DEC SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC
    #else /* defined( SIXTRL_ARGPTR_DEC ) */
        #define  SIXTRL_BE_ARGPTR_DEC
    #endif /* defined( SIXTRL_ARGPTR_DEC ) */
#endif /* !defined( SIXTRL_BE_ARGPTR_DEC ) */

#if !defined( SIXTRL_BE_DATAPTR_DEC )
    #define SIXTRL_BE_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC )
        #define  SIXTRL_BE_DATAPTR_DEC SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC
    #else /* defined( SIXTRL_DATAPTR_DEC ) */
        #define  SIXTRL_BE_DATAPTR_DEC
    #endif /* defined( SIXTRL_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_BE_DATAPTR_DEC ) */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DEFINITIONS_C99_H__ */
