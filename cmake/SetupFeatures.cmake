if(  NOT SETUP_SIXTRL_FEATURES_FINISHED )
    set( SETUP_SIXTRL_FEATURES_FINISHED 1 )

    if( SIXTRACKL_DEBUG_MODE )
        set( SIXTRL_DEBUG_MODE_DEFINITION "#define SIXTRL_DEBUG_MODE 1" )
    else()
        set( SIXTRL_DEBUG_MODE_DEFINITION "/* SIXTRL_DEBUG_MODE not enabled */" )
    endif()

    if( SIXTRACKL_ENABLE_AUTOVEC )
        set( SIXTRL_AUTOVECTORIZATION_FLAG "1" )
    else()
        set( SIXTRL_AUTOVECTORIZATION_FLAG "0" )
    endif()

    # --------------------------------------------------------------------------

    if( SIXTRACKL_TRACK_TLOCAL_PARTICLE_COPY )
        set( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER_FLAG "0" )
    else()
        set( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER_FLAG "1" )
    endif()

    if( SIXTRACKL_TRACK_USE_PARTICLE_S )
        set( SIXTRL_PARTICLE_USE_S_FIELD_FLAG "1" )
    else()
        set( SIXTRL_PARTICLE_USE_S_FIELD_FLAG "0" )
    endif()

    if( SIXTRACKL_TRACK_USE_PARTICLE_PSIGMA )
        set( SIXTRL_PARTICLE_USE_PSIGMA_FIELD_FLAG "1" )
    else()
        set( SIXTRL_PARTICLE_USE_PSIGMA_FIELD_FLAG "0" )
    endif()

    if( ( ${SIXTRL_USE_SINGLE_PARTICLE_ADAPTER_FLAG} EQUAL 1 ) AND
        ( ${SIXTRACKL_TRACK_USE_PARTICLE_PSIGMA} EQUAL 0 ) )
        message( WARNING
            "SIXTRACKL_TRACK_USE_PARTICLE_PSIGMA has no effect without SIXTRL_USE_SINGLE_PARTICLE_ADAPTER_FLAG" )
    endif()

    if( ( ${SIXTRL_USE_SINGLE_PARTICLE_ADAPTER_FLAG} EQUAL 1 ) AND
        ( ${SIXTRACKL_TRACK_USE_PARTICLE_S} EQUAL 0 ) )
        message( WARNING
            "SIXTRACKL_TRACK_USE_PARTICLE_S has no effect without SIXTRL_USE_SINGLE_PARTICLE_ADAPTER_FLAG" )
    endif()

    set( SIXTRL_TRACK_FEATURES_INSTALL_STR
         "set( SIXTRL_DEBUG_MODE_DEFINITION            \"${SIXTRL_DEBUG_MODE_DEFINITION}\"      )
          set( SIXTRL_AUTOVECTORIZATION_FLAG           \"${SIXTRL_AUTOVECTORIZATION_FLAG}\"     )
          set( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER_FLAG \"${SIXTRL_USE_SINGLE_PARTICLE_ADAPTER_FLAG}\" )
          set( SIXTRL_PARTICLE_USE_S_FIELD_FLAG        \"${SIXTRL_PARTICLE_USE_S_FIELD_FLAG}\"  )
          set( SIXTRL_PARTICLE_USE_PSIGMA_FIELD_FLAG   \"${SIXTRL_PARTICLE_USE_PSIGMA_FIELD_FLAG}\" ) "
    )

    # -------------------------------------------------------------------------
    # Track features setup

    set_property( CACHE SIXTRACKL_TRACK_BEAMBEAM4D
                        SIXTRACKL_TRACK_BEAMBEAM6D
                        SIXTRACKL_TRACK_SPACECHARGE
                        SIXTRACKL_TRACK_TRICUB
                  PROPERTY STRINGS enabled disabled skip )

    set( SIXTRL_TRACK_MAP_ENABLED_VALUE  "2" )
    set( SIXTRL_TRACK_MAP_SKIP_VALUE     "1" )
    set( SIXTRL_TRACK_MAP_DISABLED_VALUE "0" )

    set_property( CACHE SIXTRACKL_TRACK_BEAMBEAM4D PROPERTY HELPSTRING
        "Track over beam-beam 4D beam element [values: enabled, skip, disabled]" )

    if( SIXTRACKL_TRACK_BEAMBEAM4D )
        if( "${SIXTRACKL_TRACK_BEAMBEAM4D}" STREQUAL "skip" )
            set( SIXTRL_TRACK_BEAMBEAM4D_FLAG "${SIXTRL_TRACK_MAP_SKIP_VALUE}" )
            set( SIXTRL_TRACK_BEAMBEAM4D_FLAG_STR "skip" )
        elseif( "${SIXTRACKL_TRACK_BEAMBEAM4D}" STREQUAL "disabled" )
            set( SIXTRL_TRACK_BEAMBEAM4D_FLAG "${SIXTRL_TRACK_MAP_DISABLED_VALUE}" )
            set( SIXTRL_TRACK_BEAMBEAM4D_FLAG_STR "disabled" )
        else()
            set( SIXTRL_TRACK_BEAMBEAM4D_FLAG "${SIXTRL_TRACK_MAP_ENABLED_VALUE}" )
            set( SIXTRL_TRACK_BEAMBEAM4D_FLAG_STR "enabled" )
        endif()
    endif()

    set_property( CACHE SIXTRACKL_TRACK_BEAMBEAM6D PROPERTY HELPSTRING
        "Track over beam-beam 6D beam element [values: enabled, skip, disabled]" )

    if( SIXTRACKL_TRACK_BEAMBEAM6D )
        if( "${SIXTRACKL_TRACK_BEAMBEAM6D}" STREQUAL "skip" )
            set( SIXTRL_TRACK_BEAMBEAM6D_FLAG "${SIXTRL_TRACK_MAP_SKIP_VALUE}" )
            set( SIXTRL_TRACK_BEAMBEAM6D_FLAG_STR "skip" )
        elseif( "${SIXTRACKL_TRACK_BEAMBEAM6D}" STREQUAL "disabled" )
            set( SIXTRL_TRACK_BEAMBEAM6D_FLAG "${SIXTRL_TRACK_MAP_DISABLED_VALUE}" )
            set( SIXTRL_TRACK_BEAMBEAM6D_FLAG_STR "disabled" )
        else()
            set( SIXTRL_TRACK_BEAMBEAM6D_FLAG "${SIXTRL_TRACK_MAP_ENABLED_VALUE}" )
            set( SIXTRL_TRACK_BEAMBEAM6D_FLAG_STR "enabled" )
        endif()
    endif()

    set_property( CACHE SIXTRACKL_TRACK_SPACECHARGE PROPERTY HELPSTRING
        "Track over frozen space-charge beam element [values: enabled, skip, disabled]" )

    if( SIXTRACKL_TRACK_SPACECHARGE )
        if( "${SIXTRACKL_TRACK_SPACECHARGE}" STREQUAL "skip" )
            set( SIXTRL_TRACK_SC_FLAG "${SIXTRL_TRACK_MAP_SKIP_VALUE}" )
            set( SIXTRL_TRACK_SC_FLAG_STR "skip" )
        elseif( "${SIXTRACKL_TRACK_SPACECHARGE}" STREQUAL "disabled" )
            set( SIXTRL_TRACK_SC_FLAG "${SIXTRL_TRACK_MAP_DISABLED_VALUE}" )
            set( SIXTRL_TRACK_SC_FLAG_STR "disabled" )
        else()
            set( SIXTRL_TRACK_SC_FLAG "${SIXTRL_TRACK_MAP_ENABLED_VALUE}" )
            set( SIXTRL_TRACK_SC_FLAG_STR "enabled" )
        endif()
    endif()

    set_property( CACHE SIXTRACKL_TRACK_TRICUB PROPERTY HELPSTRING
        "Track over tri-cub interpolation beam elements [values: enabled, skip, disabled]" )

    if( SIXTRACKL_TRACK_TRICUB )
        if( "${SIXTRACKL_TRACK_TRICUB}" STREQUAL "skip" )
            set( SIXTRL_TRACK_TRICUB_FLAG "${SIXTRL_TRACK_MAP_SKIP_VALUE}" )
            set( SIXTRL_TRACK_TRICUB_FLAG_STR "skip" )
        elseif( "${SIXTRACKL_TRACK_TRICUB}" STREQUAL "disabled" )
            set( SIXTRL_TRACK_TRICUB_FLAG "${SIXTRL_TRACK_MAP_DISABLED_VALUE}" )
            set( SIXTRL_TRACK_TRICUB_FLAG_STR "disabled" )
        else()
            set( SIXTRL_TRACK_TRICUB_FLAG "${SIXTRL_TRACK_MAP_ENABLED_VALUE}" )
            set( SIXTRL_TRACK_TRICUB_FLAG_STR "enabled" )
        endif()
    endif()

    set( SIXTRL_TRACK_FEATURES_INSTALL_STR
        "${SIXTRL_TRACK_FEATURES_INSTALL_STR}
          set( SIXTRL_TRACK_MAP_ENABLED_VALUE          \"${SIXTRL_TRACK_MAP_ENABLED_VALUE}\"    )
          set( SIXTRL_TRACK_MAP_SKIP_VALUE             \"${SIXTRL_TRACK_MAP_SKIP_VALUE}\"       )
          set( SIXTRL_TRACK_MAP_DISABLED_VALUE         \"${SIXTRL_TRACK_MAP_DISABLED_VALUE}\"   )
          set( SIXTRL_TRACK_BEAMBEAM4D_FLAG            \"${SIXTRL_TRACK_BEAMBEAM4D_FLAG}\"      )
          set( SIXTRL_TRACK_BEAMBEAM4D_FLAG_STR        \"${SIXTRL_TRACK_BEAMBEAM4D_FLAG_STR}\"  )
          set( SIXTRL_TRACK_BEAMBEAM6D_FLAG            \"${SIXTRL_TRACK_BEAMBEAM4D_FLAG}\"      )
          set( SIXTRL_TRACK_BEAMBEAM6D_FLAG_STR        \"${SIXTRL_TRACK_BEAMBEAM4D_FLAG_STR}\"  )
          set( SIXTRL_TRACK_SPACECHARGE_FLAG           \"${SIXTRL_TRACK_SPACECHARGE_FLAG}\"     )
          set( SIXTRL_TRACK_SPACECHARGE_FLAG_STR       \"${SIXTRL_TRACK_SPACECHARGE_FLAG_STR}\" )
          set( SIXTRL_TRACK_TRICUB_FLAG                \"${SIXTRL_TRACK_TRICUB_FLAG}\"          )
          set( SIXTRL_TRACK_TRICUB_FLAG_STR            \"${SIXTRL_TRACK_TRICUB_FLAG_STR}\"      )" )


    # -------------------------------------------------------------------------
    # Aperture check features:

    if( DEFINED SIXTRACKL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH )
        set( SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH_VALUE
                "${SIXTRACKL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH}" )
    else()
        set( SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH_VALUE "0.0" )
    endif()

    set_property( CACHE SIXTRACKL_APERTURE_CHECK_AT_DRIFT PROPERTY HELPSTRING
        "Perform an x-y aperture check at Drift and DriftExact beam elements [values: always, conditional, never]" )

    set_property( CACHE SIXTRACKL_APERTURE_CHECK_AT_DRIFT
                  PROPERTY STRINGS always conditional never )

    set( SIXTRL_GLOBAL_APERATURE_CHECK_ALWAYS_VALUE        "2" )
    set( SIXTRL_GLOBAL_APERATURE_CHECK_CONDITIONAL_VALUE   "1" )
    set( SIXTRL_GLOBAL_APERATURE_CHECK_NEVER_VALUE         "0" )

    if( SIXTRACKL_APERTURE_CHECK_AT_DRIFT )
        if( "${SIXTRACKL_APERTURE_CHECK_AT_DRIFT}" STREQUAL "never" )
            set( SIXTRL_APERTURE_CHECK_AT_DRIFT_FLAG
                "${SIXTRL_GLOBAL_APERATURE_CHECK_NEVER_VALUE}" )
            set( SIXTRL_APERTURE_CHECK_AT_DRIFT_FLAG_STR "never" )
        elseif( "${SIXTRACKL_APERTURE_CHECK_AT_DRIFT}" STREQUAL "conditional" )
            set( SIXTRL_APERTURE_CHECK_AT_DRIFT_FLAG
                "${SIXTRL_GLOBAL_APERATURE_CHECK_CONDITIONAL_VALUE}" )
            set( SIXTRL_APERTURE_CHECK_AT_DRIFT_FLAG_STR "conditional" )
        else()
            set( SIXTRL_APERTURE_CHECK_AT_DRIFT_FLAG
                "${SIXTRL_GLOBAL_APERATURE_CHECK_ALWAYS_VALUE}" )
            set( SIXTRL_APERTURE_CHECK_AT_DRIFT_FLAG_STR "always" )
        endif()
    endif()

    set_property( CACHE SIXTRACKL_APERTURE_X_LIMIT_VALUE PROPERTY ADVANCED )
    set_property( CACHE SIXTRACKL_APERTURE_X_LIMIT_VALUE PROPERTY HELPSTRING
                  "Global aperture check limit for x [m]" )

    set_property( CACHE SIXTRACKL_APERTURE_Y_LIMIT_VALUE PROPERTY ADVANCED )
    set_property( CACHE SIXTRACKL_APERTURE_Y_LIMIT_VALUE PROPERTY HELPSTRING
                  "Global aperture check limit for y [m]" )

    set_property( CACHE SIXTRACKL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH
                  PROPERTY HELPSTRING
        "Perform conditional aperture checks for Drift and DriftExact elements with lengths larger than this [m]" )

    set_property( CACHE SIXTRACKL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH
                  PROPERTY ADVANCED )

    set( SIXTRL_APERTURE_CHECK_FEATURES_INSTALL_STR
         "set( SIXTRL_GLOBAL_APERATURE_CHECK_ALWAYS_VALUE
           \"${SIXTRL_GLOBAL_APERATURE_CHECK_ALWAYS_VALUE}\" )
          set( SIXTRL_GLOBAL_APERATURE_CHECK_ALWAYS_VALUE_STR
           \"${SIXTRL_GLOBAL_APERATURE_CHECK_ALWAYS_VALUE_STR}\" )
          set( SIXTRL_GLOBAL_APERATURE_CHECK_CONDITIONAL_VALUE
           \"${SIXTRL_GLOBAL_APERATURE_CHECK_CONDITIONAL_VALUE}\" )
          set( SIXTRL_GLOBAL_APERATURE_CHECK_NEVER_VALUE
           \"${SIXTRL_GLOBAL_APERATURE_CHECK_NEVER_VALUE}\" )
          set( SIXTRL_APERTURE_CHECK_AT_DRIFT_FLAG
           \"${SIXTRL_APERTURE_CHECK_AT_DRIFT_FLAG}\" )
          set( SIXTRACKL_APERTURE_X_LIMIT_VALUE
           \"${SIXTRACKL_APERTURE_X_LIMIT_VALUE}\" )
          set( SIXTRACKL_APERTURE_Y_LIMIT_VALUE
           \"${SIXTRACKL_APERTURE_Y_LIMIT_VALUE}\" )
          set( SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH_VALUE
           \"${SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH_VALUE}\" )
          set( SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH_STR
           \"${SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH_STR}\" )" )

    # ------------------------------------------------------------------------
    # Additional / Auxilliary Feature Settings:

    set( SIXTRL_BACKEND_DLIB_PREFIX_STR "${CMAKE_SHARED_LIBRARY_PREFIX}" )
    set( SIXTRL_BACKEND_DLIB_SUFFIX_STR "${CMAKE_SHARED_LIBRARY_SUFFIX}" )

    if( SIXTRACKL_ENABLE_DEMOTRACK )
        set( SIXTRL_TESTLIB_ENABLED_VALUE "1" )
    else()
        set( SIXTRL_TESTLIB_ENABLED_VALUE "0" )
    endif()

    if( SIXTRACKL_PYBIND_ALWAYS_BUILD_WRAPPER )
        set( SIXTRL_PYBIND_ALWAYS_BUILD_WRAPPER_VALUE "1" )
    else()
        set( SIXTRL_PYBIND_ALWAYS_BUILD_WRAPPER_VALUE "0" )
    endif()

    if( SIXTRACKL_ENABLE_DEMOTRACK )
        set( SIXTRL_DEMOTRACK_ENABLED_VALUE "1" )
    else()
        set( SIXTRL_DEMOTRACK_ENABLED_VALUE "0" )
    endif()

    set( SIXTRL_AUX_FEATURES_INSTALL_STR
        "set( SIXTRL_TESTLIB_ENABLED_VALUE \"${SIXTRL_TESTLIB_ENABLED_VALUE}\" )
         set( SIXTRL_PYBIND_ALWAYS_BUILD_WRAPPER_VALUE
          \"${SIXTRL_PYBIND_ALWAYS_BUILD_WRAPPER_VALUE}\" )
         set( SIXTRL_DEMOTRACK_ENABLED_VALUE
          \"${SIXTRL_DEMOTRACK_ENABLED_VALUE}\" )
         set( SIXTRL_BACKEND_DLIB_PREFIX_STR \"${CMAKE_SHARED_LIBRARY_PREFIX}\" )
         set( SIXTRL_BACKEND_DLIB_SUFFIX_STR \"${CMAKE_SHARED_LIBRARY_SUFFIX}\" )
          " )
endif()
