if( NOT SETUP_CUDA_NVRTC_FINISHED )
    set( SETUP_CUDA_NVRTC_FINISHED 1 )

    if( SIXTRACKL_ENABLE_CUDA_NVRTC )
        if( NOT CUDAToolkit_FOUND )
            if( CMAKE_VERSION VERSION_LESS "3.17" )
                message( FATAL_ERROR "Currently, cmake >= 3.17 is required for "
                                     "SIXTRACKL_ENABLE_CUDA_NVRTC" )
            endif()

            find_package( CUDAToolkit REQUIRED VERSION 8.0 )
        endif()
    endif()
endif()
