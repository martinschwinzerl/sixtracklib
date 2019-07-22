# ----------------------------------------------------------------------------
# sixtracklib/common/architecture/CMakeLists.txt

set( SIXTRL_COMMON_ARCH_C99_HEADERS
     definitions.h
     architecture.h
)

set( SIXTRL_COMMON_ARCH_C99_SOURCES )

set( SIXTRL_COMMON_ARCH_CXX_HEADERS
    arch_data.hpp
    architecture.hpp
)

set( SIXTRL_COMMON_ARCH_CXX_SOURCES
    arch_data.cpp
    architecture.cpp
    architecture_c99.cpp
)

add_library( sixtrack_common_arch_cxx OBJECT
    ${SIXTRL_COMMON_ARCH_C99_HEADERS}
    ${SIXTRL_COMMON_ARCH_CXX_HEADERS}
    ${SIXTRL_COMMON_ARCH_CXX_SOURCES}
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

target_include_directories( sixtrack_common_arch_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_arch_cxx PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_arch_cxx
    PRIVATE ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# -----------------------------------------------------------------------------
# install :

set( SIXTRACKLIB_COMMON_ARCH_INSTALL_PATH
     "${CMAKE_INSTALL_PREFIX}/include/sixtracklib/common/architecture" )

if( SIXTRL_COMMON_ARCH_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_ARCH_C99_HEADERS}
             DESTINATION ${SIXTRACKLIB_COMMON_ARCH_INSTALL_PATH} )
endif()

if( SIXTRL_COMMON_ARCH_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_ARCH_CXX_HEADERS}
             DESTINATION ${SIXTRACKLIB_COMMON_ARCH_INSTALL_PATH} )
endif()

#endif: sixtracklib/common/architecture/CMakeLists.txt
