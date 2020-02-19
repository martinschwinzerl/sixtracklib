if( NOT  SIXTRACKL_CMAKE_SETUP_OPENMP_FINISHED )
    set( SIXTRACKL_CMAKE_SETUP_OPENMP_FINISHED 1 )

    message(STATUS "---- Processing cmake/SetupOpenMP.cmake")

    # Set the module specific variables used throughout CMakeLists.txt files
    # to generate configs, headers, etc.

    set( SIXTRACKLIB_ENABLE_MODULE_OPENMP 0 )
    set( PY_SIXTRL_MODULE_VALUE "False" )

    # --------------------------------------------------------------------------
    # Provide include directories and library directories for OpenMP, if enabled

    if( NOT  SIXTRACKL_OPENMP_C_FLAGS )
        set( SIXTRACKL_OPENMP_C_FLAGS   )
    endif()

    if( NOT  SIXTRACKL_OPENMP_CXX_FLAGS )
        set( SIXTRACKL_OPENMP_CXX_FLAGS )
    endif()

    if( NOT  SIXTRACKL_OPENMP_FORTRAN_FLAGS )
        set( SIXTRACKL_OPENMP_FORTRAN_FLAGS )
    endif()

    if( NOT  SIXTRACKL_OPENMP_EXE_LINKER_FLAGS )
        set( SIXTRACKL_OPENMP_EXE_LINKER_FLAGS )
    endif()

    if( SIXTRACKL_ENABLE_OPENMP AND NOT ( OpenMP_FOUND OR OPENMP_FOUND ) )
        find_package( OpenMP REQUIRED )

        message( STATUS "OpenMP_FOUND: ${OpenMP_FOUND}" )
        message( STATUS "OPENMP_FOUND: ${OPENMP_FOUND}" )

        if( OPENMP_FOUND AND NOT OpenMP_FOUND )
            set( OpenMP_FOUND ${OPENMP_FOUND} )
        endif()

        if( OpenMP_FOUND )

            if( OpenMP_C_FLAGS )
                set( SIXTRACKL_OPENMP_C_FLAGS ${SIXTRACKL_OPENMP_C_FLAGS}
                     ${OpenMP_C_FLAGS} )
            endif()

            if( OpenMP_CXX_FLAGS )
                set( SIXTRACKL_OPENMP_CXX_FLAGS ${SIXTRACKL_OPENMP_CXX_FLAGS}
                     ${OpenMP_CXX_FLAGS} )
            endif()

            if( OpenMP_Fortran_FLAGS )
                set( SIXTRACKL_OPENMP_FORTRAN_FLAGS ${SIXTRACKL_OPENMP_FORTRAN_FLAGS}
                     ${OpenMP_Fortran_FLAGS} )
            endif()

            set( SIXTRACKLIB_ENABLE_MODULE_OPENMP 1 )
            set( PY_SIXTRL_MODULE_VALUE "True" )
        endif()
    endif()

    # --------------------------------------------------------------------------
    # Add OpenMP to the list of supported modules and track its state:

    list( APPEND SIXTRACKLIB_SUPPORTED_MODULES "OPENMP" )
    list( APPEND SIXTRACKLIB_SUPPORTED_MODULES_VALUES
            "${SIXTRACKLIB_ENABLE_MODULE_OPENMP}" )

    set( SIXTRL_MODULES_INSTALL ${SIXTRL_MODULES_INSTALL}
         "set( SIXTRACKLIB_ENABLE_MODULE_OPENMP ${SIXTRACKLIB_ENABLE_MODULE_OPENMP} )"
    )

    if( SIXTRACKL_ENABLE_PYTHON )
        set( PY_SIXTRACKLIB_MODULES_STR ${PY_SIXTRACKLIB_MODULES_STR}
             "SIXTRACKLIB_MODULES[ \"openmp\" ] = ${PY_SIXTRL_MODULE_VALUE}" )
    endif()
    unset( PY_SIXTRL_MODULE_VALUE )

endif()
