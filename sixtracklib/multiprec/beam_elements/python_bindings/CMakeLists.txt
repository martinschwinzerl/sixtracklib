if( SIXTRACKL_ENABLE_PYTHON AND pybind11_FOUND )
    add_library( sixtrack_py_multiprec_beam_elements OBJECT
                 python_bindings.cpp
                 cavity.cpp
                 drift.cpp
                 multipole.cpp
                 srotation.cpp
                 xy_shift.cpp
    )

    target_include_directories( sixtrack_py_multiprec_beam_elements PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

    set_target_properties( sixtrack_py_multiprec_beam_elements PROPERTIES
        LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
        CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

    target_link_libraries( sixtrack_py_multiprec_beam_elements
        PRIVATE pybind11::module )

    if( Boost_FOUND )
        target_link_libraries( sixtrack_py_multiprec_beam_elements
            PRIVATE Boost::boost )
    endif()

    set( SIXTRACKLIB_PYTHON_BINDINGS_LIBS ${SIXTRACKLIB_PYTHON_BINDINGS_LIBS}
         $<TARGET_OBJECTS:sixtrack_py_multiprec_beam_elements>
         CACHE STRING "" FORCE )
endif()
