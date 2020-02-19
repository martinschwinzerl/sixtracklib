if( NOT  SIXTRACKL_CMAKE_SETUP_MULTI_PRECISION_FINISHED )
    set( SIXTRACKL_CMAKE_SETUP_MULTI_PRECISION_FINISHED 1 )

    message( STATUS "---- Processing cmake/SetupMultiPrecision.cmake" )

    # Set the module specific variables used throughout CMakeLists.txt files
    # to generate configs, headers, etc.

    set( SIXTRACKLIB_ENABLE_MODULE_MULTIPREC 0 )
    set( PY_SIXTRL_MODULE_VALUE "False" )

    # --------------------------------------------------------------------------
    # Handle backends providing multiprecision support

    if( SIXTRACKL_ENABLE_MULTIPREC )
        if(  NOT SIXTRL_MULTIPREC_IMPL )
            set( SIXTRL_MULTIPREC_IMPL "boost" )
        endif()

        if( "${SIXTRL_MULTIPREC_IMPL}" STREQUAL "boost" )
            if( NOT Boost_FOUND )
                if( SIXTRACKL_BOOST_COMPONENTS )
                    find_package( Boost REQUIRED
                        COMPONENTS ${SIXTRACKL_BOOST_COMPONENTS} )
                else()
                    find_package( Boost REQUIRED )
                endif()
            endif()

            if( Boost_FOUND )
                set( SIXTRACKLIB_ENABLE_MODULE_MULTIPREC 1 )
                set( PY_SIXTRL_MODULE_VALUE "True" )
            endif()
        endif()
    endif()


    # --------------------------------------------------------------------------
    # Add MULTIPREC to the list of supported modules and track its state:

    list( APPEND SIXTRACKLIB_SUPPORTED_MODULES "MULTIPREC" )
    list( APPEND SIXTRACKLIB_SUPPORTED_MODULES_VALUES
            "${SIXTRACKLIB_ENABLE_MODULE_MULTIPREC}" )

    set( SIXTRL_MODULES_INSTALL ${SIXTRL_MODULES_INSTALL}
         "set( SIXTRACKLIB_ENABLE_MODULE_MULTIPREC ${SIXTRACKLIB_ENABLE_MODULE_MULTIPREC} )"
    )

    if( SIXTRACKL_ENABLE_PYTHON )
        set( PY_SIXTRACKLIB_MODULES_STR ${PY_SIXTRACKLIB_MODULES_STR}
             "SIXTRACKLIB_MODULES[ \"multiprec\" ] = ${PY_SIXTRL_MODULE_VALUE}" )
    endif()
    unset( PY_SIXTRL_MODULE_VALUE )
endif()

# end: cmake/SetupMultiPrecision.cmake
