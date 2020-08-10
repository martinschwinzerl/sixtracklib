if(  NOT SETUP_BACKEND_MODULES_FINISHED )
  set( SETUP_BACKEND_MODULES_FINISHED 1 )

    # TODO: Implement "enable module if dependencies are found" logic here!

    if( SIXTRACKL_ENABLE_SIMD )
        set( SIXTRACKL_ENABLE_BACKEND_SIMD 1 )
    else()
        set( SIXTRACKL_ENABLE_BACKEND_SIMD 0 )
    endif()

    if( SIXTRACKL_ENABLE_MULTIPREC )
        set( SIXTRACKL_ENABLE_BACKEND_MULTIPREC 1 )
    else()
        set( SIXTRACKL_ENABLE_BACKEND_MULTIPREC 0 )
    endif()

    if( SIXTRACKL_ENABLE_OPENMP )
        set( SIXTRACKL_ENABLE_BACKEND_OPENMP 1 )
    else()
        set( SIXTRACKL_ENABLE_BACKEND_OPENMP 0 )
    endif()

    if( SIXTRACKL_ENABLE_OPENCL )
        set( SIXTRACKL_ENABLE_BACKEND_OPENCL 1 )
    else()
        set( SIXTRACKL_ENABLE_BACKEND_OPENCL 0 )
    endif()

    if( SIXTRACKL_ENABLE_CUDA )
        set( SIXTRACKL_ENABLE_BACKEND_CUDA 1 )
    else()
        set( SIXTRACKL_ENABLE_BACKEND_CUDA 0 )
    endif()

    if( SIXTRACKL_ENABLE_CUDA_NVRTC )
        set( SIXTRACKL_ENABLE_BACKEND_CUDA_NVRTC 1 )
    else()
        set( SIXTRACKL_ENABLE_BACKEND_CUDA_NVRTC 0 )
    endif()

    set( SIXTRACKLIB_BACKENDS_STR
       "set( SIXTRACKL_ENABLE_BACKEND_SIMD       ${SIXTRACKL_ENABLE_BACKEND_SIMD} )
        set( SIXTRACKL_ENABLE_BACKEND_MULTIPREC  ${SIXTRACKL_ENABLE_BACKEND_MULTIPREC} )
        set( SIXTRACKL_ENABLE_BACKEND_OPENMP     ${SIXTRACKL_ENABLE_BACKEND_OPENMP} )
        set( SIXTRACKL_ENABLE_BACKEND_OPENCL     ${SIXTRACKL_ENABLE_BACKEND_OPENCL} )
        set( SIXTRACKL_ENABLE_BACKEND_CUDA       ${SIXTRACKL_ENABLE_BACKEND_CUDA} )
        set( SIXTRACKL_ENABLE_BACKEND_CUDA_NVRTC ${SIXTRACKL_ENABLE_BACKEND_CUDA_NVRTC} )"
    )

    mark_as_advanced( SIXTRACKLIB_MODULES_STR )

    # ------------------------------------------------------------------------

    if( SIXTRACKL_ENABLE_PYTHON )
        if( SIXTRACKL_ENABLE_SIMD )
            set( PY_SIXTRACKL_ENABLE_BACKEND_SIMD "True" )
        else()
            set( PY_SIXTRACKL_ENABLE_BACKEND_SIMD "False" )
        endif()

        if( SIXTRACKL_ENABLE_MULTIPREC )
            set( PY_SIXTRACKL_ENABLE_BACKEND_MULTIPREC "True" )
        else()
            set( PY_SIXTRACKL_ENABLE_BACKEND_MULTIPREC "False" )
        endif()

        if( SIXTRACKL_ENABLE_OPENMP )
            set( PY_SIXTRACKL_ENABLE_BACKEND_OPENMP "True" )
        else()
            set( PY_SIXTRACKL_ENABLE_BACKEND_OPENMP "False" )
        endif()

        if( SIXTRACKL_ENABLE_OPENCL )
            set( PY_SIXTRACKL_ENABLE_BACKEND_OPENCL "True" )
        else()
            set( PY_SIXTRACKL_ENABLE_BACKEND_OPENCL "False" )
        endif()

        if( SIXTRACKL_ENABLE_CUDA )
            set( PY_SIXTRACKL_ENABLE_BACKEND_CUDA "True" )
        else()
            set( PY_SIXTRACKL_ENABLE_BACKEND_CUDA "False" )
        endif()

        if( SIXTRACKL_ENABLE_CUDA_NVRTC )
            set( PY_SIXTRACKL_ENABLE_BACKEND_CUDA_NVRTC "True" )
        else()
            set( PY_SIXTRACKL_ENABLE_BACKEND_CUDA_NVRTC "False" )
        endif()

        set( PY_SIXTRACKLIB_MODULES_STR
             "SIXTRACKLIB_MODULES = { "
            "    \"simd\": ${PY_SIXTRACKL_ENABLE_BACKEND_SIMD}, "
            "    \"multiprec\": ${PY_SIXTRACKL_ENABLE_BACKEND_MULTIPREC}, "
            "    \"openmp\": ${PY_SIXTRACKL_ENABLE_BACKEND_OPENMP}, "
            "    \"opencl\": ${PY_SIXTRACKL_ENABLE_BACKEND_OPENCL}, "
            "    \"cuda\": ${PY_SIXTRACKL_ENABLE_BACKEND_CUDA}, "
            "    \"cuda_nvrtc\": ${PY_SIXTRACKL_ENABLE_BACKEND_CUDA_NVRTC} }" )

        mark_as_advanced( PY_SIXTRACKLIB_MODULES_STR )
    endif()
endif()
