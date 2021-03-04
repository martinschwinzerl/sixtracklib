set( SIXTRL_OPENCL_CXX_HEADERS )
set( SIXTRL_OPENCL_CXX_SOURCES )

set( SIXTRL_OPENCL_C99_HEADERS default_defines.h )
set( SIXTRL_OPENCL_C99_SOURCES )

# - - - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - - - - - - - -

set( SIXTRL_OPENCL_KERNELS
     cobj_flat_buffer_remap.cl
     particle_track_until_cobj_flat_buffer.cl )

# -----------------------------------------------------------------------------
# install:

if( SIXTRL_OPENCL_C99_HEADERS )
    install( FILES ${SIXTRL_OPENCL_C99_HEADERS}
             DESTINATION "${SIXTRL_OPENCL_C99_INSTALL_PREFIX}/kernels" )
endif()

if( SIXTRL_OPENCL_CXX_HEADERS )
    install( FILES ${SIXTRL_OPENCL_CXX_HEADERS}
             DESTINATION "${SIXTRL_OPENCL_CXX_INSTALL_PREFIX}/kernels" )
endif()

if( SIXTRL_OPENCL_KERNELS )
    install( FILES ${SIXTRL_OPENCL_KERNELS}
             DESTINATION "${SIXTRL_OPENCL_C99_INSTALL_PREFIX}/kernels" )
endif()
