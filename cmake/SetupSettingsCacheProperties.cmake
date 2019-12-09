if(  NOT SETUP_CACHE_PROPERTIES_FINISHED )
    set( SETUP_CACHE_PROPERTIES_FINISHED 1 )

    # ==========================================================================
    # SixTrackLib Features :

    set_property( CACHE SIXTRACKL_TRACK_BEAM_BEAM_4D_MAP
        PROPERTY HELPSTRING "Enable tracking beam-beam-4D map" )

    set_property( CACHE SIXTRACKL_TRACK_BEAM_BEAM_6D_MAP
        PROPERTY HELPSTRING "Enable tracking beam-beam-6D map" )

    set_property( CACHE SIXTRACKL_TRACK_SPACE_CHARGE_COASTING_MAP
        PROPERTY HELPSTRING "Enable tracking coasting space-charge maps" )

    set_property( CACHE SIXTRACKL_TRACK_SPACE_CHARGE_BUNCHED_MAP
        PROPERTY HELPSTRING "Enable tracking bunched  space-charge maps" )

    set_property( CACHE SIXTRACKL_TRACK_TRICUB_MAP
        PROPERTY HELPSTRING "Enable tracking be_tricub maps" )


    set_property( CACHE SIXTRACKL_TRACK_BEAM_BEAM_4D_MAP
                        SIXTRACKL_TRACK_BEAM_BEAM_6D_MAP
                        SIXTRACKL_TRACK_SPACE_CHARGE_COASTING_MAP
                        SIXTRACKL_TRACK_SPACE_CHARGE_BUNCHED_MAP
                        SIXTRACKL_TRACK_TRICUB_MAP
        PROPERTY STRINGS enabled skip disabled runtime_check )

    # ==========================================================================
    # Global limit check :

    set_property( CACHE SIXTRACKL_GLOBAL_LIMIT_RECT_CHECK
        PROPERTY HELPSTRING "Enable global LimitRect check" )

    set_property( CACHE SIXTRACKL_GLOBAL_LIMIT_RECT_CHECK
        PROPERTY STRINGS enabled disabled runtime_check )


    set_property( CACHE SIXTRACKL_GLOBAL_LIMIT_RECT_MIN_X
        PROPERTY HELPSTRING "Global LimitRect check after min_x [m]" )

    set_property( CACHE SIXTRACKL_GLOBAL_LIMIT_RECT_MAX_X
        PROPERTY HELPSTRING "Global LimitRect check after max_x [m]" )

    set_property( CACHE SIXTRACKL_GLOBAL_LIMIT_RECT_MIN_Y
        PROPERTY HELPSTRING "Global LimitRect check after min_y [m]" )

    set_property( CACHE SIXTRACKL_GLOBAL_LIMIT_RECT_MAX_Y
        PROPERTY HELPSTRING "Global LimitRect check after max_y [m]" )

    set_property( CACHE SIXTRACKL_GLOBAL_LIMIT_RECT_MIN_LENGTH
        PROPERTY HELPSTRING "Global LimitRect check min length  [m]" )

endif()
