if(  NOT SETUP_CXX_FINISHED )
    set( SETUP_CXX_FINISHED 1 )

    message( STATUS "---- Processing cmake/SetupCxx.cmake" )

    # --------------------------------------------------------------------------
    # Prepare default cxx compiler flags

    set( SIXTRACKLIB_CXX_FLAGS )
    if( SIXTRACKL_DEFAULT_CXX_FLAGS )
        string( REPLACE " " ";" SIXTRACKLIB_CXX_FLAGS
                ${SIXTRACKL_DEFAULT_CXX_FLAGS} )
    endif()

    # --------------------------------------------------------------------------
    # Setup C99 namespace

    if( NOT SIXTRACKL_CXX_NAMESPACE )
        set( SIXTRACKL_CXX_NAMESPACE "sixtrack" )
    endif()

    set( SIXTRACKL_CXX_NAMESPACE_PREFIX "${SIXTRACKL_CXX_NAMESPACE}" )

    list( APPEND SIXTRACKLIB_NAMESPACE_FLAGS
          "SIXTRL_NAMESPACE=${SIXTRACKL_CXX_NAMESPACE}" )

    if( SIXTRACKL_ENABLE_PYTHON )
        set( PY_SIXTRL_CXX_NAMESPACE_STR "${SIXTRACKL_CXX_NAMESPACE}" )
        mark_as_advanced( PY_SIXTRL_CXX_NAMESPACE_STR )

        set( PY_SIXTRL_CXX_NAMESPACE_PREFIX "${SIXTRACKL_CXX_NAMESPACE_PREFIX}" )
        mark_as_advanced( PY_SIXTRL_CXX_NAMESPACE_PREFIX )
    endif()
endif()
