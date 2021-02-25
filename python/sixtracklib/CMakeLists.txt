message( STATUS "---- processing python/CMakeLists.txt" )

set( SIXTRL_PY_WRAPPER_HEADERS
    _wrapper/tl/optional.hpp
    _wrapper/cxx11_optional.h
    _wrapper/buffer_protocol.h
    _wrapper/init_helper.h
    _wrapper/testlib.h
    _wrapper/demotrack.h
    _wrapper/common.h
    _wrapper/common_belements.h
    _wrapper/common_cobjects.h
    _wrapper/common_internal.h
    _wrapper/common_particles.h
)

set( SIXTRL_PY_WRAPPER_SOURCES
    _wrapper/sixtracklib_wrapper.cpp
    _wrapper/buffer_protocol.cpp
    _wrapper/init_helper.cpp
    _wrapper/testlib.cpp
    _wrapper/demotrack.cpp
    _wrapper/common.cpp
    _wrapper/common_belements.cpp
    _wrapper/common_cobjects.cpp
    _wrapper/common_internal.cpp
    _wrapper/common_particles.cpp )

if( SIXTRACKL_PYBIND_ALWAYS_BUILD_WRAPPER OR SKBUILD )
    pybind11_add_module( _wrapper MODULE THIN_LTO OPT_SIZE
        ${SIXTRL_PY_WRAPPER_HEADERS} ${SIXTRL_PY_WRAPPER_SOURCES} )

    target_include_directories( _wrapper
        PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

    target_link_libraries( _wrapper PRIVATE sixtrack_static )

    install( TARGETS _wrapper LIBRARY DESTINATION . )
endif()
