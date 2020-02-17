#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/definitions.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

typedef struct NS(Drift)
{
    NS(be_real_t) length SIXTRL_ALIGN( 8 );
}
NS(Drift);

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(Drift_length)( SIXTRL_BE_ARGPTR_DEC
    const NS(Drift) *const SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Drift_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT drift,
    NS(be_real_t) const length ) SIXTRL_NOEXCEPT;

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataCApiTypeTraits< ::NS(Drift) >
    {
        typedef ::NS(Drift) c_api_t;
    };
}
#endif /* C++ */

/* ------------------------------------------------------------------------- */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(be_real_t) NS(Drift_length)( SIXTRL_BE_ARGPTR_DEC const
    NS(Drift) *const SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( drift != SIXTRL_NULLPTR );
    return drift->length;
}

SIXTRL_INLINE void NS(Drift_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT drift,
    NS(be_real_t) const length ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( drift != SIXTRL_NULLPTR );
    drift->length = length;
}

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_C99_H__ */
