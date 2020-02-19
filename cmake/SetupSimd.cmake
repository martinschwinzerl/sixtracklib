if( NOT  SIXTRACKL_CMAKE_SETUP_SIMD_FINISHED )
    set( SIXTRACKL_CMAKE_SETUP_SIMD_FINISHED 1 )

    message( STATUS "---- Processing cmake/SetupSimd.cmake" )

    # Set the module specific variables used throughout CMakeLists.txt files
    # to generate configs, headers, etc.
    set( SIXTRACKLIB_ENABLE_MODULE_SIMD 0 )
    set( PY_SIXTRL_MODULE_VALUE "False" )

    if( SIXTRACKL_ENABLE_SIMD )
        if( NOT  SIXTRACKL_SIMD_IMPL )
            set( SIXTRACKL_SIMD_IMPL "xsimd" )
        endif()

        if( "${SIXTRACKL_SIMD_IMPL}" STREQUAL "xsimd" )
            if( NOT xsimd_FOUND )
                find_package( xsimd REQUIRED )
            endif()

            if( xsimd_FOUND )
                set( MSG "---- found xsimd version ${xsimd_VERSION} at " )
                set( MSG "${MSG} ${xsimd_INCLUDE_DIRS}/xsimd" )
                message( STATUS "${MSG}" )

                set( SIXTRACKLIB_ENABLE_MODULE_SIMD 1 )
                set( PY_SIXTRL_MODULE_VALUE "True" )
            else()
                set( SIXTRACKL_SIMD_IMPL )
            endif()
        endif()
    endif()

    # --------------------------------------------------------------------------
    # Add SIMD to the list of supported modules and track its state:

    list( APPEND SIXTRACKLIB_SUPPORTED_MODULES "SIMD" )
    list( APPEND SIXTRACKLIB_SUPPORTED_MODULES_VALUES
                 "${SIXTRACKLIB_ENABLE_MODULE_SIMD}" )

    set( SIXTRL_MODULES_INSTALL ${SIXTRL_MODULES_INSTALL}
         "set( SIXTRACKLIB_ENABLE_MODULE_SIMD ${SIXTRACKLIB_ENABLE_MODULE_SIMD} )"
    )

    if( SIXTRACKL_ENABLE_PYTHON )
        set( PY_SIXTRACKLIB_MODULES_STR ${PY_SIXTRACKLIB_MODULES_STR}
             "SIXTRACKLIB_MODULES[ \"simd\" ] = ${PY_SIXTRL_MODULE_VALUE}" )
    endif()
    unset( PY_SIXTRL_MODULE_VALUE )

endif()

#end: cmake/SetupAutoVecSIMD.cmake
