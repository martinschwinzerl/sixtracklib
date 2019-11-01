if( NOT  SIXTRACKL_CMAKE_SETUP_LLVM_FINISHED )
    set( SIXTRACKL_CMAKE_SETUP_LLVM_FINISHED 1 )

    message( STATUS "---- Processing cmake/SetupLLVM.cmake" )

    if( NOT  SIXTRACKL_LLVM_INCLUDE_DIRS )
        set( SIXTRACKL_LLVM_INCLUDE_DIRS )
    endif()

    if( NOT  SIXTRACKL_LLVM_LIBRARY_DIRS )
        set( SIXTRACKL_LLVM_LIBRARY_DIRS )
    endif()

    if( NOT  SIXTRACKL_LLVM_DEFINITIONS )
        set( SIXTRACKL_LLVM_DEFINITIONS )
    endif()

    if( SIXTRACKL_BUILD_CODEGENERATORS )
        if( NOT LLVM_FOUND )
            find_package( LLVM REQUIRED CONFIG )

            message( STATUS "------ Found LLVM ${LLVM_PACKAGE_VERSION}" )
            message( STATUS "------ Using LLVMConfig.cmake in ${LLVM_DIR}" )

            set( SIXTRACKL_LLVM_DEFINITIONS ${LLVM_DEFINITIONS} )
            set( SIXTRACKL_LLVM_LIBRARY_DIRS ${LLVM_LIBRARY_DIRS} )
            set( SIXTRACKL_LLVM_INCLUDE_DIRS ${LLVM_INCLUDE_DIRS} )
        endif()
    endif()
endif()

# end: cmake/SetupLLVM.cmake
