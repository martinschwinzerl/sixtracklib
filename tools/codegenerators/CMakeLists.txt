# ============================================================================
# tools/codegenerators/CMakeLists.txt

message( STATUS "---- processing tools/codegenerators/CMakeLists.txt" )

add_subdirectory( libcodegen )

# ----------------------------------------------------------------------------
# create_c99_from_cxx:

set( SIXTRL_CODEGEN_CREATE_C99_FROM_CXX_HEADERS )
set( SIXTRL_CODEGEN_CREATE_C99_FROM_CXX_SOURCES create_c99_from_cxx.cpp )

add_executable( create_c99_from_cxx
    ${SIXTRL_CODEGEN_CREATE_C99_FROM_CXX_HEADERS}
    ${SIXTRL_CODEGEN_CREATE_C99_FROM_CXX_SOURCES} )

set_target_properties( create_c99_from_cxx PROPERTIES
    CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

target_include_directories( create_c99_from_cxx
    PRIVATE ${SIXTRACKL_LLVM_INCLUDE_DIRS} )

set_property( TARGET create_c99_from_cxx
    APPEND PROPERTY COMPILE_OPTIONS ${SIXTRACKL_LLVM_DEFINITIONS} )

set_property( TARGET create_c99_from_cxx
    APPEND PROPERTY LINK_DIRECTORIES ${SIXTRACKL_LLVM_LIBRARY_DIRS} )

target_link_libraries( create_c99_from_cxx PRIVATE sixtrl_codegen )

#end: tools/codegenerators/CMakeLists.txt
