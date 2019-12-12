#ifndef SIXTRACKL_COMMON_BUFFER_BUFFER_TYPE_H__
#define SIXTRACKL_COMMON_BUFFER_BUFFER_TYPE_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
    #else /* defined( __cplusplus ) */
        #include <stddef.h>
        #include <stdlib.h>
        #include <limits.h>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/buffer/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
extern "C" {
#endif /* defined( __cplusplus ) */

typedef struct NS(Buffer)
{
    NS(buffer_addr_t)    data_addr        SIXTRL_ALIGN( 8u );
    NS(buffer_size_t)    data_size        SIXTRL_ALIGN( 8u );
    NS(buffer_size_t)    header_size      SIXTRL_ALIGN( 8u );
    NS(buffer_size_t)    data_capacity    SIXTRL_ALIGN( 8u );

    NS(buffer_size_t)    slot_length      SIXTRL_ALIGN( 8u );

    NS(buffer_addr_t)    object_addr      SIXTRL_ALIGN( 8u );
    NS(buffer_size_t)    num_objects      SIXTRL_ALIGN( 8u );

    NS(buffer_flags_t)   datastore_flags  SIXTRL_ALIGN( 8u );
    NS(buffer_addr_t)    datastore_addr   SIXTRL_ALIGN( 8u );
}
NS(Buffer);

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKL_COMMON_BUFFER_BUFFER_TYPE_H__ */
