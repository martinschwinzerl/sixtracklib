if(  NOT SETUP_PYTHON_FINISHED )
    set( SETUP_PYTHON_FINISHED 1 )

    message( STATUS "---- Processing cmake/SetupPython.cmake" )

    # --------------------------------------------------------------------------
    # Add Python to the list of supported bindings / languages

    list( APPEND SIXTRACKLIB_SUPPORTED_BINDINGS "PYTHON" )

    if( SIXTRACKL_ENABLE_PYTHON )
        list( APPEND SIXTRACKLIB_SUPPORTED_BINDINGS_VALUES "1" )
    else()
        list( APPEND SIXTRACKLIB_SUPPORTED_BINDINGS_VALUES "0" )
    endif()

    # ==========================================================================

    if( NOT  Python_ADDITIONAL_VERSIONS )
        set( Python_ADDITIONAL_VERSIONS 3.8 3.7 3.6 3 )
    endif()

    if( SIXTRACKL_ENABLE_PYTHON AND NOT PYTHONINTERP_FOUND )
        find_package( PythonInterp REQUIRED )
    endif()

    if( SIXTRACKL_ENABLE_PYTHON AND NOT PYTHONLIBS_FOUND )
        find_package( PythonLibs REQUIRED )
    endif()

    if( SIXTRACKL_ENABLE_PYTHON AND NOT pybind11_FOUND )
        find_package( pybind11 )

        if( NOT pybind11_FOUND AND NOT SIXTRACKL_REQUIRE_OFFLINE_BUILD )
            set( EXT_PYBIND11_IN_DIR "${CMAKE_SOURCE_DIR}/cmake/" )
            set( EXT_PYBIND11_TMPL "" )

            set( EXT_PYBIND11_IN_FILE "${CMAKE_SOURCE_DIR}/cmake/SetupPybind11CMakeLists.txt.in" )
            set( EXT_PYBIND11_OUT_DIR "${CMAKE_BINARY_DIR}/ext_pybind11" )
            set( EXT_PYBIND11_INSTALL_DIR "${EXT_PYBIND11_OUT_DIR}/install/" )
            set( EXT_PYBIND11_OUT     "${EXT_PYBIND11_OUT_DIR}/CMakeLists.txt"  )

            configure_file( ${EXT_PYBIND11_IN_FILE} ${EXT_PYBIND11_OUT} @ONLY )
            message( STATUS "Attempt downloading and building pybind11 ... " )

            execute_process(
                COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXT_PYBIND11_OUT_DIR} )

            if( NOT result )
                message( STATUS "Successfully run cmake for external pybind11" )
            else()
                message( FATAL_ERROR "Cmake for external pybind11 failed: ${result}" )
            endif()

            execute_process(
                COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXT_PYBIND11_OUT_DIR} )

            if( NOT result )
                message( STATUS "Successfully completed building external pybind11" )
            else()
                message( FATAL_ERROR "Building for external pybind11 failed: ${result}" )
            endif()

            set( pybind11_DIR ${EXT_PYBIND11_INSTALL_DIR}/share/cmake/pybind11 )
            find_package( pybind11 REQUIRED CONFIG )

        elseif( SIXTRACKL_REQUIRE_OFFLINE_BUILD )
            message( FATAL_ERROR
                     "No system-wide pybind11 installation "
                     "found and offline installation required\r\n"
                     "set pybind11_ROOT in Settings.cmake "
                     "to pick up pybind11 at a specific location" )
        endif()
    endif()

    if(  NOT PY_SIXTRACKLIB_MODULES_STR )
        set( PY_SIXTRACKLIB_MODULES_STR "SIXTRACKLIB_MODULES = {}" )
    endif()

endif()
