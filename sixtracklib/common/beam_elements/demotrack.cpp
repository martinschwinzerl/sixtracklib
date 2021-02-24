#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/demotrack.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <fstream>
    #include <memory>
    #include <string>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

::NS(size_type) NS(Demotrack_belems_cobj_index_range_to_flat_buffer_real)(
    ::NS(size_type) max_num_buffer_elements,
    ::NS(be_real_type)* SIXTRL_RESTRICT data_buffer_begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* end )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using real_type = ::NS(be_real_type);
    ::NS(size_type) num_slots =
        ::NS(Demotrack_belems_requ_num_slots_for_cobj_index_range)( begin, end );

    if( ( num_slots > ::NS(size_type){ 0 } ) &&
        ( num_slots <= max_num_buffer_elements ) &&
        ( data_buffer_begin != nullptr ) )
    {
        std::vector< real_type > temp( num_slots, real_type{ 0.0 } );
        temp.clear();

        st::TDemotrack_belems_cobj_index_range_to_flat_buffer( temp, begin, end );

        if( temp.size() == num_slots )
        {
            std::copy( temp.begin(), temp.end(), data_buffer_begin );
        }
        else
        {
            num_slots = ::NS(size_type){ 0 };
        }
    }

    return num_slots;
}

::NS(size_type) NS(Demotrack_belems_cbuffer_to_flat_buffer_real)(
    NS(size_type) max_num_buffer_elements,
    ::NS(be_real_type)* SIXTRL_RESTRICT data_buffer_begin,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const
        SIXTRL_RESTRICT cobj_buffer )
{
    return ::NS(Demotrack_belems_cobj_index_range_to_flat_buffer_real)(
        max_num_buffer_elements, data_buffer_begin,
        ::NS(CBuffer_const_objects_begin)( cobj_buffer ),
        ::NS(CBuffer_const_objects_end)( cobj_buffer ) );
}
