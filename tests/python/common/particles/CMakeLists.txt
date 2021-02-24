add_test( NAME Python_Common_Particles_SingleParticle
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_single_particle.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )

add_test( NAME Python_Common_Particles_Particles
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_particles.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )

add_test( NAME Python_Common_Particles_Demotrack
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_demotrack.py ${CMAKE_SOURCE_DIR}/tests/testdata
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )

