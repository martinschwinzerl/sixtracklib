add_test( NAME Python_Common_Internal_MathFactorial
          COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_math_factorial.py
          WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
