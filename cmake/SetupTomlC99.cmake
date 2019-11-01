if( NOT SIXTRACKL_CMAKE_SETUP_TOMLC99_FETCH_TOMLC99_FROM_GITHUB_FINISHED )
   set( SIXTRACKL_CMAKE_SETUP_TOMLC99_FETCH_TOMLC99_FROM_GITHUB_FINISHED 1 )

   message( STATUS "---- processing cmake/SetupTomlC99.cmake")

    if( NOT SIXTRACKL_REQUIRE_OFFLINE_BUILD )

        set( TomlC99_UPDATED 0 )
        set( TomlC99_SYNC 0 )
        message( STATUS "------ attempting to fetch tomlc99 library")

        if( NOT Git_FOUND )
            find_package( Git )
        endif()

        if( Git_FOUND )
            set( TOMLC99_GIT_REPOSITORY "https://github.com/cktan/tomlc99.git" )
            set( TOMLC99_GIT_BRANCH "master" )

            set( EXT_TOMLC99_DIR "${CMAKE_BINARY_DIR}/ext_tomlc99" )
            set( TomlC99_REMOTE_REF_HEADS_MASTER )
            set( TomlC99_LOCAL_REF_HEADS_MASTER )

            execute_process(
                COMMAND ${GIT_EXECUTABLE} ls-remote ${TOMLC99_GIT_REPOSITORY} ${TOMLC99_GIT_BRANCH}
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                OUTPUT_VARIABLE TomlC99_REMOTE_REF_HEADS_MASTER
                RESULT_VARIABLE TomlC99_RESULT
                ERROR_VARIABLE  TomlC99_ERROR )

            if( NOT ( ${TomlC99_RESULT} EQUAL 0 ) AND TomlC99_ERROR )
                message( STATUS "------ Error git ls-remote: ${TomlC99_ERROR}" )
            endif()

            string( SUBSTRING "${TomlC99_REMOTE_REF_HEADS_MASTER}" 0 40
                    TomlC99_REMOTE_REF_HEADS_MASTER )

            if( EXISTS ${EXT_TOMLC99_DIR} )
                execute_process(
                    COMMAND ${GIT_EXECUTABLE} show-ref refs/heads/master
                    WORKING_DIRECTORY ${EXT_TOMLC99_DIR}
                    OUTPUT_VARIABLE TomlC99_LOCAL_REF_HEADS_MASTER
                    RESULT_VARIABLE TomlC99_RESULT
                    ERROR_VARIABLE  TomlC99_ERROR )

                if( NOT ( ${TomlC99_RESULT} EQUAL 0 ) AND TomlC99_LOCAL_REF_HEADS_MASTER )
                    message( STATUS "------ Error git show-ref refs/heads/master: ${TomlC99_ERROR}" )
                endif()

                string( SUBSTRING "${TomlC99_LOCAL_REF_HEADS_MASTER}" 0 40
                        TomlC99_LOCAL_REF_HEADS_MASTER )

                string( COMPARE NOTEQUAL "${TomlC99_REMOTE_REF_HEADS_MASTER}"
                        "${TomlC99_LOCAL_REF_HEADS_MASTER}" REFS_NOT_EQUAL )

                if( REFS_NOT_EQUAL )

                    # Remote head has changed -> we have to fetch & Merge
                    message( STATUS "------ Remote: ${TomlC99_REMOTE_REF_HEADS_MASTER}" )
                    message( STATUS "------ Local : ${TomlC99_REMOTE_REF_HEADS_MASTER}" )
                    message( STATUS "------ Attempting to fetch & merge from remote ... " )

                    execute_process(
                        COMMAND ${GIT_EXECUTABLE} fetch origin
                        WORKING_DIRECTORY ${EXT_TOMLC99_DIR}
                        OUTPUT_VARIABLE TomlC99_OUTPUT
                        RESULT_VARIABLE TomlC99_RESULT
                        ERROR_VARIABLE  TomlC99_ERROR )

                    if( NOT ( ${TomlC99_RESULT} EQUAL 0 ) AND TomlC99_OUTPUT )
                        message( STATUS "------ Output git fetch origin: ${TomlC99_OUTPUT}" )
                    endif()

                    execute_process(
                        COMMAND ${GIT_EXECUTABLE} checkout ${TOMLC99_GIT_BRANCH}
                        WORKING_DIRECTORY ${EXT_TOMLC99_DIR}
                        OUTPUT_VARIABLE TomlC99_OUTPUT
                        RESULT_VARIABLE TomlC99_RESULT
                        ERROR_VARIABLE  TomlC99_ERROR )

                    if( NOT ( ${TomlC99_RESULT} EQUAL 0 ) AND TomlC99_OUTPUT )
                        message( STATUS "------ Output git checkout ${TOMLC99_GIT_BRANCH}: ${TomlC99_OUTPUT}" )
                    endif()

                    execute_process(
                        COMMAND ${GIT_EXECUTABLE} merge --ff-only origin/${TOMLC99_GIT_BRANCH}
                        WORKING_DIRECTORY ${EXT_TOMLC99_DIR}
                        OUTPUT_VARIABLE TomlC99_OUTPUT
                        RESULT_VARIABLE TomlC99_RESULT
                        ERROR_VARIABLE  TomlC99_ERROR )

                    if( NOT ( ${TomlC99_RESULT} EQUAL 0 ) AND TomlC99_OUTPUT )
                        message( STATUS "------ Output git merge --ff-only ${TOMLC99_GIT_BRANCH}: ${TomlC99_OUTPUT}" )
                    endif()

                    set( TomlC99_UPDATED 1 )
                endif()
            else()
                message( STATUS "------ Attempting to clone remote git repository ... " )

                execute_process(
                    COMMAND ${GIT_EXECUTABLE} clone ${TOMLC99_GIT_REPOSITORY} ${EXT_TOMLC99_DIR}
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                    OUTPUT_VARIABLE TomlC99_OUTPUT
                    RESULT_VARIABLE TomlC99_RESULT
                    ERROR_VARIABLE  TomlC99_ERROR )

                if( NOT ( ${TomlC99_RESULT} EQUAL 0 ) AND TomlC99_OUTPUT )
                    message( STATUS "------ Output git clone: ${TomlC99_OUTPUT}" )
                endif()

                execute_process(
                    COMMAND ${GIT_EXECUTABLE} checkout ${TOMLC99_GIT_BRANCH}
                    WORKING_DIRECTORY ${EXT_TOMLC99_DIR}
                    OUTPUT_VARIABLE TomlC99_OUTPUT
                    RESULT_VARIABLE TomlC99_RESULT
                    ERROR_VARIABLE  TomlC99_ERROR )

                if( NOT ( ${TomlC99_RESULT} EQUAL 0 ) AND TomlC99_OUTPUT )
                    message( STATUS "------ Output git checkout ${TOMLC99_GIT_BRANCH}: ${TomlC99_OUTPUT}" )
                endif()

                execute_process(
                    COMMAND ${GIT_EXECUTABLE} show-ref refs/heads/master
                    WORKING_DIRECTORY ${EXT_TOMLC99_DIR}
                    OUTPUT_VARIABLE TomlC99_LOCAL_REF_HEADS_MASTER
                    RESULT_VARIABLE TomlC99_RESULT
                    ERROR_VARIABLE  TomlC99_ERROR )

                if( NOT ( ${TomlC99_RESULT} EQUAL 0 ) AND TomlC99_LOCAL_REF_HEADS_MASTER )
                    message( STATUS "------ Error git show-ref refs/heads/master: ${TomlC99_ERROR}" )
                endif()

                string( SUBSTRING "${TomlC99_LOCAL_REF_HEADS_MASTER}" 0 40
                        TomlC99_LOCAL_REF_HEADS_MASTER )

                set( TomlC99_UPDATED 1 )
            endif()

            string( COMPARE EQUAL "${TomlC99_REMOTE_REF_HEADS_MASTER}"
                    "${TomlC99_LOCAL_REF_HEADS_MASTER}" REFS_EQUAL )

            if( REFS_EQUAL )
                set( TomlC99_SYNC 1 )
            endif()

            if( ${TomlC99_UPDATED} EQUAL 1 )
                if( EXISTS "${EXT_TOMLC99_DIR}/toml.h"  AND
                    EXISTS "${EXT_TOMLC99_DIR}/toml.c"  AND
                    EXISTS "${EXT_TOMLC99_DIR}/LICENSE" AND
                    EXISTS "${EXT_TOMLC99_DIR}/README.md" )

                    set( OUT_DIR "${CMAKE_SOURCE_DIR}/external/tomlc99" )

                    configure_file( "${EXT_TOMLC99_DIR}/toml.h" "${OUT_DIR}/toml.h"
                                    COPYONLY )

                    configure_file( "${EXT_TOMLC99_DIR}/toml.c" "${OUT_DIR}/toml.c"
                                    COPYONLY )

                    configure_file( "${EXT_TOMLC99_DIR}/LICENSE" "${OUT_DIR}/LICENSE"
                                    COPYONLY )

                    configure_file( "${EXT_TOMLC99_DIR}/README.md"
                                    "${OUT_DIR}/README.md" COPYONLY )

                    set( TomlC99_SYNC 1 )
                endif()
            endif()
        else()
            message( STATUS "------ downloading of tomlc99 requires git " )
            message( STATUS "------ unable to continue automatically" )
        endif()
    endif()

    if( ${TomlC99_SYNC} EQUAL 1 )
        if( ${TomlC99_UPDATED} EQUAL 1 )
            message( STATUS "------ successfully synced from remote repository" )
        else()
            message( STATUS "------ was already sync with remote repository" )
        endif()
    else()
        if( ${TomlC99_UPDATED} EQUAL 1 )
            message( WARNING "------ performed update but unable to successfully sync" )
        endif()
        message( STATUS  "------- unable to update tomlc99 from upstream" )

        set( MSG "------- download the latest toml.h and toml.c from the " )
        set( MSG "${MSG} repository (hint: try ${TOMLC99_GIT_REPOSITORY}) or " )
        set( MSG "${MSG} rely on the existing files in " )
        set( MSG "${MSG} ${CMAKE_SOURCE_DIR}/external/tomlc99" )
        message( STATUS "${MSG} " )
    endif()
endif()
