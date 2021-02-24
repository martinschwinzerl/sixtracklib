add_test( NAME Python_Common_BeamElements_Multipole
          COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_multipole.py
          WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )

add_test( NAME Python_Common_BeamElements_Demotrack
          COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_demotrack.py ${CMAKE_SOURCE_DIR}/tests/testdata
          WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
