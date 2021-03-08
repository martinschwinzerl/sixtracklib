set( SIXTRL_OPENCL_CXX_HEADERS )
set( SIXTRL_OPENCL_CXX_SOURCES )

set( SIXTRL_OPENCL_C99_HEADERS )
set( SIXTRL_OPENCL_C99_SOURCES )

# =============================================================================
# Generate *_defines.h from template:
set( SIXTRL_NO_SYSTEM_INCLUDES_VALUE 1 )

# -----------------------------------------------------------------------------
# default_defines.h -> OpenCL 1.2, regular operation:

set( SIXTRL_ARGPTR_DEC_VALUE  "__private" )
set( SIXTRL_DATAPTR_DEC_VALUE "__global"  )
set( SIXTRL_CBUFFER_ARGPTR_DEC_VALUE "__private" )
set( SIXTRL_CBUFFER_DATAPTR_DEC_VALUE "__global" )
set( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC_VALUE "__global" )
set( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC_VALUE "__global" )
set( SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC_VALUE "__global" )
set( SIXTRL_CBUFFER_GARBAGE_DATAPTR_DEC_VALUE "__global" )

set( SIXTRL_BE_ARGPTR_DEC_VALUE "__global" )
set( SIXTRL_BE_DATAPTR_DEC_VALUE "__global" )

set( SIXTRL_PARTICLE_ARGPTR_DEC_VALUE "__private" )
set( SIXTRL_PARTICLE_DATAPTR_DEC_VALUE "__private" )
set( SIXTRL_PARTICLES_ARGPTR_DEC_VALUE "__global" )
set( SIXTRL_PARTICLES_DATAPTR_DEC_VALUE "__global" )
set( SIXTRL_PARTICLES_ADDR_ARGPTR_DEC_VALUE "__global" )
set( SIXTRL_PARTICLES_ADDR_DATAPTR_DEC_VALUE "__global" )

set( SIXTRL_TRACK_ARGPTR_DEC_VALUE "__global" )
set( SIXTRL_TRACK_DATAPTR_DEC_VALUE "__global" )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/defines.h.template
                ${CMAKE_CURRENT_SOURCE_DIR}/default_defines.h @ONLY )

set( SIXTRL_OPENCL_C99_HEADERS ${SIXTRL_OPENCL_C99_HEADERS} default_defines.h )

# -----------------------------------------------------------------------------
# add_cobj_elem_defines.h -> OpenCL 1.2, create / build cobjects buffers
# NOTE: THIS DOES NOT WORK FOR ANYTHING ELSE, ONLY USE IN SUCH DEDICATED KERNELS!

set( SIXTRL_ARGPTR_DEC_VALUE  "__private" )
set( SIXTRL_DATAPTR_DEC_VALUE "__global"  )
set( SIXTRL_CBUFFER_ARGPTR_DEC_VALUE "__private" )
set( SIXTRL_CBUFFER_DATAPTR_DEC_VALUE "__global" )
set( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC_VALUE "__global" )
set( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC_VALUE "__global" )
set( SIXTRL_CBUFFER_GARBAGE_ARGPTR_DEC_VALUE "__global" )
set( SIXTRL_CBUFFER_GARBAGE_DATAPTR_DEC_VALUE "__global" )

set( SIXTRL_BE_ARGPTR_DEC_VALUE "__private" )
set( SIXTRL_BE_DATAPTR_DEC_VALUE "__global" )

set( SIXTRL_PARTICLE_ARGPTR_DEC_VALUE "__private" )
set( SIXTRL_PARTICLE_DATAPTR_DEC_VALUE "__private" )
set( SIXTRL_PARTICLES_ARGPTR_DEC_VALUE "__private" )
set( SIXTRL_PARTICLES_DATAPTR_DEC_VALUE "__global" )
set( SIXTRL_PARTICLES_ADDR_ARGPTR_DEC_VALUE "__private" )
set( SIXTRL_PARTICLES_ADDR_DATAPTR_DEC_VALUE "__global" )

set( SIXTRL_TRACK_ARGPTR_DEC_VALUE "__private" )
set( SIXTRL_TRACK_DATAPTR_DEC_VALUE "__global" )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/defines.h.template
                ${CMAKE_CURRENT_SOURCE_DIR}/add_cobj_elem_defines.h @ONLY )

set( SIXTRL_OPENCL_C99_HEADERS ${SIXTRL_OPENCL_C99_HEADERS}
     add_cobj_elem_defines.h )

# =============================================================================

set( SIXTRL_OPENCL_KERNELS
     cobj_flat_buffer_remap.cl
     particle_track_until_cobj_flat_buffer.cl )

# =============================================================================
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
