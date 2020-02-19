if( NOT  SIXTRACKL_CMAKE_SETUP_CPU_FLAGS_FINISHED )
    set( SIXTRACKL_CMAKE_SETUP_CPU_FLAGS_FINISHED 1 )

    message( STATUS "---- Processing cmake/SetupCpuFlags.cmake" )

    #TODO: Handle other compilers / conventions than gcc -> there has to be a
    #      way to handle this in a more generic fashion

    if( SIXTRACKL_CPU_ARCH MATCHES "avx2" )
        message( STATUS "------ Optimizing for AVX2 architecture" )
        set( SIXTRACKLIB_CPU_FLAGS ${SIXTRACKLIB_CPU_FLAGS} -mavx2 )

    elseif( SIXTRACKL_CPU_ARCH MATCHES "avx" )
        message( STATUS "------ Optimizing for AVX architecture" )
        set( SIXTRACKLIB_CPU_FLAGS ${SIXTRACKLIB_CPU_FLAGS} -mavx )

    elseif( SIXTRACKL_CPU_ARCH MATCHES "sse2" )
        message( STATUS "------ Optimizing for SSE2 architecture" )
        set( SIXTRACKLIB_CPU_FLAGS ${SIXTRACKLIB_CPU_FLAGS} -msse2  )

    elseif( SIXTRACKL_CPU_ARCH MATCHES "native" )
        message( STATUS "------ Optimizing for native environment of the CPU" )
        set( SIXTRACKLIB_CPU_FLAGS ${SIXTRACKLIB_CPU_FLAGS} -march=native  )
    endif()

endif()
