# ============================================================================
# tools/codegenerators/libcodegen/CMakeLists.txt

message( STATUS
         "---- processing tools/codegenerators/libcodegen/CMakeLists.txt" )

# if( NOT LLVM_FOUND )
#     message( FATAL_ERROR "---- LLVM not found!" )
# endif()

# set( SIXTRL_LIBCODEGEN_LLVM_LIBRARIES ${SIXTRL_LIBCODEGEN_LLVM_LIBRARIES}
#      clangFrontend clangSerialization clangDriver clangTooling clangParse
#      clangSema clangAnalysis clangRewriteFrontend clangRewrite clangEdit
#      clangAST clangLex clangBasic clangASTMatchers )

# ============================================================================

set( SIXTRL_LIBCODEGEN_HEADERS
    cxx_to_c99_config.hpp
)

set( SIXTRL_LIBCODEGEN_SOURCES
    cxx_to_c99_config.cpp
)

add_library( sixtrl_codegen
    ${SIXTRL_LIBCODEGEN_HEADERS}
    ${SIXTRL_LIBCODEGEN_SOURCES} )

target_include_directories( sixtrl_codegen PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tools/codegenerators>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/sixtracklib>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

target_link_libraries( sixtrl_codegen
    $<TARGET_OBJECTS:sixtrl_tomlc99> sixtrack )

set_target_properties( sixtrl_codegen PROPERTIES
    CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON POSITION_INDEPENDENT_CODE ON )

target_compile_options( sixtrl_codegen PRIVATE ${SIXTRACKLIB_CPU_FLAGS})




#end: tools/codegenerators/libcodegen/CMakeLists.txt
