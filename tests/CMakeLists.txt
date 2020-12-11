# sixtracklib/tests/CMakeLists.txt

# testdata and generators for the testdata:
add_subdirectory( testdata )

# Unit tests for the C/C++ version of the library
add_subdirectory( sixtracklib )

# Unit tests for the python bindings, if enabled
if( SIXTRACKL_ENABLE_PYTHON )
    add_subdirectory( python )
endif()

# Enable benchmarking tests
if( SIXTRACKL_ENABLE_TIMING_TESTS )
    add_subdirectory( benchmark )
endif()

# Enable tests of the code generation library
if( SIXTRACKL_BUILD_CODE_GENERATOR )
    add_subdirectory( libcodegen )
endif()
