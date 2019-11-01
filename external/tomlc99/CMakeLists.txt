# ============================================================================
# external/tomlc99/CMakeLists.txt

message( STATUS "---- processing external/tomlc99/CMakeLists.txt" )

set( TOMLC99_HEADERS toml.h )
set( TOMLC99_SOURCES toml.c )

add_library( sixtrl_tomlc99 OBJECT
            ${TOMLC99_HEADERS}
            ${TOMLC99_SOURCES} )

set_target_properties( sixtrl_tomlc99 PROPERTIES LINKER_LANGUAGE C
    C_STANDARD 99 C_STANDARD_REQUIRED ON POSITION_INDEPENDENT_CODE ON )

target_compile_options( sixtrl_tomlc99
    PRIVATE ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} "-Wno-format-truncation" )

#end: external/tomlc99/CMakeLists.txt
