file( GLOB ALL_DEMO_TOML_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
      LIST_DIRECTORIES false "demo*.toml" )

foreach( TOML_FILE ${ALL_DEMO_TOML_FILES} )
    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/${TOML_FILE}
                    ${CMAKE_CURRENT_BINARY_DIR}/${TOML_FILE} COPYONLY )
endforeach()

add_executable( like_demotrack_opencl_cxx like_demotrack_opencl.cpp )
target_link_libraries( like_demotrack_opencl_cxx sixtrack_test sixtrack )
