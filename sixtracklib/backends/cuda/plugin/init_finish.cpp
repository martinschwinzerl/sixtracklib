#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/plugin/init_finish.h"
    #include "sixtracklib/backends/cuda/plugin/cuda_tools.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#include <stdio.h>

void NS(Cuda_plugin_init)()
{
    printf( "HERE\r\n" );
    ::NS(Cuda_init_thread)( 0u );
}

void NS(Cuda_plugin_finish)() { return; }

