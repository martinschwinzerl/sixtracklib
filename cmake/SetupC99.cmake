if(  NOT SETUP_C99_FINISHED )
    set( SETUP_C99_FINISHED 1 )

    message( STATUS "---- Processing cmake/SetupC99.cmake" )

    # --------------------------------------------------------------------------
    # Prepare default c99 compiler flags

    set( SIXTRACKLIB_C99_FLAGS )

    if( SIXTRACKL_DEFAULT_C99_FLAGS )
        string( REPLACE " " ";"
                SIXTRACKLIB_C99_FLAGS ${SIXTRACKL_DEFAULT_C99_FLAGS} )
    endif()

    # --------------------------------------------------------------------------
    # Setup C99 namespace

    if( NOT SIXTRACKL_C_NAMESPACE_PREFIX )
        set( SIXTRACKL_C_NAMESPACE_PREFIX "st_" )
    endif()

    list( APPEND SIXTRACKLIB_NAMESPACE_FLAGS
          "__NAMESPACE=${SIXTRACKL_C_NAMESPACE_PREFIX}" )

    set( SIXTRACKL_C_NAMESPACE_STR ${SIXTRACKL_C_NAMESPACE_PREFIX} )

    if( SIXTRACKL_ENABLE_PYTHON )
        set( PY_SIXTRL_C99_NAMESPACE_STR "${SIXTRACKL_C_NAMESPACE_STR}" )
        mark_as_advanced( PY_SIXTRL_C99_NAMESPACE_STR )

        set( PY_SIXTRL_C99_NAMESPACE_PREFIX_STR "${SIXTRACKL_C_NAMESPACE_PREFIX}" )
        mark_as_advanced( PY_SIXTRL_C99_NAMESPACE_PREFIX_STR )
    endif()
endif()
