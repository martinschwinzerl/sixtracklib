if( NOT  SIXTRACKL_CMAKE_SETUP_AUTOVEC_SIMD_FINISHED )
    set( SIXTRACKL_CMAKE_SETUP_AUTOVEC_SIMD_FINISHED 1 )

    message( STATUS "---- Processing cmake/SetupAutoVecSimd.cmake" )

    # Set the module specific variables used throughout CMakeLists.txt files
    # to generate configs, headers, etc.

    set( SIXTRACKLIB_ENABLE_MODULE_AUTOVEC_SIMD 0 )
    set( PY_SIXTRL_MODULE_VALUE "False" )

    if( SIXTRACKL_ENABLE_AUTOVEC_SIMD )
        #TODO: Handle this in a more generic fashion for compilers different
        #      than gcc

        if( CMAKE_C_COMPILER_ID STREQUAL "GNU" )
            set( SIXTRACKLIB_CPU_FLAGS ${SIXTRACKLIB_CPU_FLAGS}
                 -ftree-vectorize -ftree-vectorizer-verbose=6
                 -fopt-info-loop
                 -fno-fast-math
                 --param vect-max-version-for-alias-checks=150 )
        endif()

        set( SIXTRACKLIB_ENABLE_MODULE_AUTOVEC_SIMD 1 )
        set( PY_SIXTRL_MODULE_VALUE "True" )
    endif()

    # --------------------------------------------------------------------------
    # Add AUTOVEC_SIMD to the list of supported modules and track its state:

    list( APPEND SIXTRACKLIB_SUPPORTED_MODULES "AUTOVEC_SIMD" )
    list( APPEND SIXTRACKLIB_SUPPORTED_MODULES_VALUES
          "${SIXTRACKLIB_ENABLE_MODULE_AUTOVEC_SIMD}" )

    set( SIXTRL_MODULES_INSTALL ${SIXTRL_MODULES_INSTALL}
         "set( SIXTRACKLIB_ENABLE_MODULE_AUTOVEC_SIMD ${SIXTRACKLIB_ENABLE_MODULE_AUTOVEC_SIMD} )"
    )

    if( SIXTRACKL_ENABLE_PYTHON )
        set( PY_SIXTRACKLIB_MODULES_STR ${PY_SIXTRACKLIB_MODULES_STR}
             "SIXTRACKLIB_MODULES[ \"autovec_simd\" ] = ${PY_SIXTRL_MODULE_VALUE}" )
    endif()
    unset( PY_SIXTRL_MODULE_VALUE )

endif()

#end: cmake/SetupAutoVecSimd.cmake
