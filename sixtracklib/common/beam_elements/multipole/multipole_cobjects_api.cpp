    #if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/multipole_cobjects_api.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_api.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef ::NS(Multipole) pset_t;
    }

    constexpr cobj_size_t CObjElemNumPointers< ::NS(Multipole) >::min_num_ptrs;
    constexpr cobj_size_t CObjElemNumPointers< ::NS(Multipole) >::max_num_ptrs;
    constexpr cobj_size_t CObjElemFieldOffsets< ::NS(Multipole) >::offsets[];
    constexpr cobj_size_t CObjElemFieldSizes< ::NS(Multipole) >::sizes[];

    /* ********************************************************************** */

    ::NS(cobj_type_id_t) NS(Multipole_type_id_ext)( void ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Multipole_type_id< ::NS(Multipole) >();
    }

    bool NS(Multipole_can_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC const ::NS(CBufferView) *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(Multipole) *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_objects,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_pointers ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Multipole_can_add_copy( cbuffer,
            ptr_orig, requ_buffer_size, requ_num_slots, requ_num_objects,
                requ_num_pointers );
    }

    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Multipole)* NS(Multipole_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
        SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(Multipole) *const ptr_orig )
    {
        return SIXTRL_CXX_NAMESPACE::Multipole_add_copy( cbuffer, ptr_orig );
    }

    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Multipole)* NS(Multipole_new)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
        ::NS(be_order_t) const order )
    {
        return SIXTRL_CXX_NAMESPACE::Multipole_new<
            ::NS(Multipole) >( cbuffer, order );
    }
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
