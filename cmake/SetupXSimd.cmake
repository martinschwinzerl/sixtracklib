if( NOT  SIXTRACKL_CMAKE_SETUP_XSIMD_FINISHED   )
    set( SIXTRACKL_CMAKE_SETUP_XSIMD_FINISHED 1 )

    message( STATUS "---- Processing cmake/SetupXSimd.cmake" )

    # --------------------------------------------------------------------------
    # Provide include directories and library directories for Cuda, if enabled

    if( NOT  SIXTRACKL_CUDA_INCLUDE_DIRS )
        set( SIXTRACKL_CUDA_INCLUDE_DIRS   )
    endif()

    if( NOT  SIXTRACKL_CUDA_LIBRARIES )
        set( SIXTRACKL_CUDA_LIBRARIES )
    endif()

    if( NOT  SIXTRACKL_CUDA_VERSION_STR )
        set( SIXTRACKL_CUDA_VERSION_STR "" )
    endif()

    get_property( SIXTRACKL_ENABLED_LANGS GLOBAL PROPERTY ENABLED_LANGUAGES )

    if( SIXTRACKL_ENABLE_CUDA AND SIXTRACKL_ENABLED_LANGS MATCHES "CUDA" )
        set( SIXTRACKL_CUDA_INCLUDE_DIRS ${SIXTRACKL_CUDA_INCLUDE_DIRS}
             ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES} )

        if( CMAKE_CUDA_COMPILER_VERSION )
            set( SIXTRACKL_CUDA_VERSION_STR "${CMAKE_CUDA_COMPILER_VERSION}" )
        endif()

        find_library( CUDART_LIBRARY cudart
            ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES} )

        if( CUDART_LIBRARY )
            set( SIXTRACKL_CUDA_LIBRARIES
               ${SIXTRACKL_CUDA_LIBRARIES} ${CUDART_LIBRARY} )
        else()
            set( SRC_LIB_DIR ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES} )
            message( WARNING "------ Unable to find libcudart in ${SRC_LIB_DIR}" )
            unset( SRC_LIB_DIR )
        endif()

    elseif( SIXTRACKL_ENABLE_CUDA )

        if( NOT CUDA_FOUND )
            find_package( CUDA REQUIRED )
        endif()

        if( CUDA_FOUND )
            set( SIXTRACKL_CUDA_INCLUDE_DIRS ${SIXTRACKL_CUDA_INCLUDE_DIRS}
                 ${CUDA_INCLUDE_DIRS} )

            set( SIXTRACKL_CUDA_LIBRARIES ${SIXTRACKL_CUDA_LIBRARIES}
                 ${CUDA_LIBRARIES} )

            set( SIXTRACKL_CUDA_VERSION_STR ${SIXTRACKL_CUDA_VERSION_STR}
                 ${CUDA_VERSION_STRING} )
        else()
            message( WARNING "------ Unable to find cuda environment" )
        endif()

    endif()

    # --------------------------------------------------------------------------
    # Add CUDA to the list of supported modules and track its state:

    list( APPEND SIXTRACKLIB_SUPPORTED_MODULES "CUDA" )

    if( SIXTRACKL_ENABLE_CUDA )
        list( APPEND SIXTRACKLIB_SUPPORTED_MODULES_VALUES "1" )
    else()
        list( APPEND SIXTRACKLIB_SUPPORTED_MODULES_VALUES "0" )
    endif()
endif()

#end: sixtracklib/cmake/SetupOpenCL.cmake
