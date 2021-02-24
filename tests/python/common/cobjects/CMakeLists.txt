add_test( NAME Python_Common_CObjects_CBuffer
          COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_cbuffer.py
          WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )

add_test( NAME Python_Common_CObjects_Numpy_Adapter
          COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_cobjects_numpy.py
          WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
