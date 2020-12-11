#ifndef SIXTRACKLIB_TESTS_SIXTRACKLIB_TESTLIB_TESTDATA_FILES_H__
#define SIXTRACKLIB_TESTS_SIXTRACKLIB_TESTLIB_TESTDATA_FILES_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/_impl/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************ */
/* ****                                                                **** */
/* ****                Path to Base Testdata Directory                 **** */
/* ****                                                                **** */
/* ************************************************************************ */

static char const NS(PATH_TO_TESTDATA_DIR)[] =
    "/home/martin/git/sixtracklib/tests/testdata";


/* ************************************************************************ */
/* ****                                                                **** */
/* ****        Tabulated values for mathematically functions           **** */
/* ****                                                                **** */
/* ************************************************************************ */

static char const NS(PATH_TO_TEST_FADDEEVA_ERRFN_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_faddeeva_errorfn_data.bin";


/* ************************************************************************ */
/* ****                                                                **** */
/* ****     Testdata for NS(Buffer) and NS(ManagedBuffer) operation    **** */
/* ****                                                                **** */
/* ************************************************************************ */

static char const NS(PATH_TO_TEST_GENERIC_OBJ_BUFFER_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_buffer_generic_obj.bin";

/* ************************************************************************ */
/* ****                                                                **** */
/* ****        Randomly Generated Tracking Test-Data Files             **** */
/* ****                                                                **** */
/* ************************************************************************ */

static char const NS(PATH_TO_TEST_TRACKING_BE_DRIFT_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_track_be_drift_data.bin";

static char const NS(PATH_TO_TEST_TRACKING_BE_DRIFTEXACT_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_track_be_driftexact_data.bin";

static char const NS(PATH_TO_TEST_TRACKING_BE_MULTIPOLE_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_track_be_multipole_data.bin";

static char const NS(PATH_TO_TEST_TRACKING_BE_XYSHIFT_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_track_be_xyshift_data.bin";

static char const NS(PATH_TO_TEST_TRACKING_BE_SROTATION_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_track_be_srotation_data.bin";

static char const NS(PATH_TO_TEST_TRACKING_BE_CAVITY_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_track_be_cavity_data.bin";


/* ************************************************************************ */
/* ****                                                                **** */
/* ****                  Real-World Datasets and Testdata              **** */
/* ****                                                                **** */
/* ************************************************************************ */

/* ------------------------------------------------------------------------ */
/* ----     LHC, Single Turn, Two Particles, No BeamBeam elements      ---- */
/* ------------------------------------------------------------------------ */

static char const NS(PATH_TO_TEST_LHC_PARTICLES_DATA_T1_P2_NO_BEAM_BEAM)[] =
    "/home/martin/git/sixtracklib/tests/testdata/lhc_particles_turn1_p2_nobeambeam.bin";

static char const NS(PATH_TO_TEST_LHC_BEAM_ELEMENTS_DATA_NO_BEAM_BEAM)[] =
    "/home/martin/git/sixtracklib/tests/testdata/lhc_beam_elements_nobeambeam.bin";

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_TESTS_SIXTRACKLIB_TESTLIB_TESTDATA_FILES_H__ */

/* end: tests/sixtracklib/testlib/testdata_files.h */
