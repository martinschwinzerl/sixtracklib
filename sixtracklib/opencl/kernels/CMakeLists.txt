set( OPENCL_KERNELS_INSTALL_PATH "${C99_HEADERS_INSTALL_PATH}/kernels" )
set( C99_HEADERS_INSTALL_PATH    "${C99_HEADERS_INSTALL_PATH}/kernels" )

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
             DESTINATION "${C99_HEADERS_INSTALL_PATH}/kernels" )
endif()

if( SIXTRL_OPENCL_CXX_HEADERS )
    install( FILES ${SIXTRL_OPENCL_CXX_HEADERS}
             DESTINATION "${CXX_HEADERS_INSTALL_PATH}/kernels" )
endif()

if( SIXTRL_OPENCL_KERNELS )
    install( FILES ${SIXTRL_OPENCL_KERNELS}
             DESTINATION ${OPENCL_KERNELS_INSTALL_PATH} )
endif()
