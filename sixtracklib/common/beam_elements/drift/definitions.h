#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DEFINITIONS_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class DriftDataObj >
    struct DriftTraits
    {
        typedef be_real_t real_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< be_real_t >();
    };

    template< class DriftDataObj >
    constexpr arch_size_t DriftTraits< DriftDataObj >::real_alignment;
}
#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DEFINITIONS_H__ */
