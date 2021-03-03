#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/kernels/default_defines.h"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

__kernel void NS(CObjFlatBuffer_remap_opencl)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    SIXTRL_UINT64_TYPE const slot_size )
{
    if( ( NS(cobj_size_type) )0u == ( NS(cobj_size_type) )get_global_id( 0 ) )
    {
        SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
        SIXTRL_ASSERT( NS(CObjFlatBuffer_has_cbuffer_structure)(
            buffer, 0u, slot_size ) );

        NS(status_type) const status = NS(CObjFlatBuffer_remap)(
            buffer, slot_size );

        SIXTRL_ASSERT( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS );
        ( void )status;
    }
}
