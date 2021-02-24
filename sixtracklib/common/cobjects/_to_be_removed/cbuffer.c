#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(CBuffer_delete)( SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
    SIXTRL_RESTRICT b ) {
    if( b != SIXTRL_NULLPTR ) { NS(CBuffer_free)( b ); free( b ); } }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_FN NS(cobj_status_type) NS(CBuffer_init_as_buffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size );

SIXTRL_EXTERN SIXTRL_FN NS(cobj_status_type)
NS(CBuffer_init_as_buffer_detailed)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) capacity,
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges,
    NS(cobj_size_type) const slot_size,
    NS(cobj_buffer_flags_type) const flags );

SIXTRL_EXTERN SIXTRL_FN NS(cobj_status_type)
NS(CBuffer_init_from_file)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT path_to_file ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_FN NS(cobj_status_type) NS(CBuffer_free)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* NS(CBuffer_new_as_view)(
    NS(cobj_addr_type) const base_addr, NS(cobj_size_type) const capacity );

SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* NS(CBuffer_new_as_view_detailed)(
    NS(cobj_addr_type) const base_addr, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const capacity, NS(cobj_buffer_flags_type) const flags );

SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* NS(CBuffer_new)( void );
SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* NS(CBuffer_new_with_capacity)(
    NS(cobj_size_type) const capacity );

SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* NS(CBuffer_new_detailed)(
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size,
    NS(cobj_buffer_flags_type) const flags );

SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* NS(CBuffer_new_as_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT view );

SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* NS(CBuffer_new_as_copy_detailed)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT orig,
    NS(cobj_buffer_flags_type) const flags );

SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* NS(CBuffer_new_from_file)(
    char const* SIXTRL_RESTRICT path_tofile );

SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* NS(CBuffer_new_fromfile_detailed)(
    char const* SIXTRL_RESTRICT path_tofile, NS(cobj_size_type) const slot_size,
    NS(cobj_buffer_flags_type) const flags );

SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* NS(CBuffer_new_with_structure)(
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges,
    NS(cobj_size_type) const slot_size,
    NS(cobj_buffer_flags_type) const flags );
