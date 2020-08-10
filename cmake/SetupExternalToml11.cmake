if( NOT  SETUP_EXTERNAL_TOML11_FINISHED )
    set( SETUP_EXTERNAL_TOML11_FINISHED 1 )

    message( STATUS "---- processing cmake/SetupExternalToml11.cmake" )

    if( NOT toml11_FOUND )
        find_package( toml11 QUIET )
    endif()

    if( NOT toml11_FOUND )
        include( FetchContent )
        set( toml11_BUILD_TEST OFF CACHE INTERNAL "" )
        mark_as_advanced( toml11_BUILD_TEST )
        if( NOT SIXTRACKL_REQUIRE_OFFLINE_BUILD )
            FetchContent_Declare( toml11
                GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
                GIT_TAG v3.5.0 )
        else()
            message( STATUS "------ toml11: requiring offline build!" )
            FetchContent_Declare( toml11
                GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
                GIT_TAG v3.5.0
                FETCHCONTENT_FULLY_DISCONNECTED ON )
        endif()

        FetchContent_GetProperties( toml11 )
        if( NOT toml11_POPULATED )
            FetchContent_Populate( toml11 )
            add_subdirectory( ${toml11_SOURCE_DIR} ${toml11_BINARY_DIR} )
        endif()

        if( NOT toml11_POPULATED )
            message( FATAL_ERROR "unable to download/fetch toml11" )
        endif()
    endif()
endif()
