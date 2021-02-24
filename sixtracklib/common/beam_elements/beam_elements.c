#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beam_elements.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

bool NS(CObjIndex_is_beam_element_ext)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
        return NS(CObjIndex_is_beam_element)( obj ); }

