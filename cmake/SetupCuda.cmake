if( NOT  SIXTRACKL_CMAKE_SETUP_CUDA_FINISHED   )
    set( SIXTRACKL_CMAKE_SETUP_CUDA_FINISHED 1 )

    message( STATUS "---- Processing cmake/SetupCuda.cmake" )

    # Set the module specific variables used throughout CMakeLists.txt files
    # to generate configs, headers, etc.

    set( SIXTRACKLIB_ENABLE_MODULE_CUDA 0 )
    set( PY_SIXTRL_MODULE_VALUE "False" )

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

            set( SIXTRACKLIB_ENABLE_MODULE_CUDA 1 )
            set( PY_SIXTRL_MODULE_VALUE "True" )
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

            set( SIXTRACKLIB_ENABLE_MODULE_CUDA 1 )
            set( PY_SIXTRL_MODULE_VALUE "True" )
        else()
            message( WARNING "------ Unable to find cuda environment" )
        endif()

    endif()

    # --------------------------------------------------------------------------
    # Add CUDA to the list of supported modules and track its state:

    list( APPEND SIXTRACKLIB_SUPPORTED_MODULES "CUDA" )
    list( APPEND SIXTRACKLIB_SUPPORTED_MODULES_VALUES
            "${SIXTRACKLIB_ENABLE_MODULE_CUDA}" )

    set( SIXTRL_MODULES_INSTALL ${SIXTRL_MODULES_INSTALL}
         "set( SIXTRACKLIB_ENABLE_MODULE_CUDA ${SIXTRACKLIB_ENABLE_MODULE_CUDA} )"
    )

    if( SIXTRACKL_ENABLE_PYTHON )
        set( PY_SIXTRACKLIB_MODULES_STR ${PY_SIXTRACKLIB_MODULES_STR}
             "SIXTRACKLIB_MODULES[ \"cuda\" ] = ${PY_SIXTRL_MODULE_VALUE}" )
    endif()
    unset( PY_SIXTRL_MODULE_VALUE )
endif()

#end: sixtracklib/cmake/SetupOpenCL.cmake
