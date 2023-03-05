cmake_minimum_required(VERSION 3.0.0)
project(matrixLib VERSION 1.0.0 LANGUAGES CXX)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Doxygen REQUIRED)
set(DOXYGEN_EXECUTABLE ${DOXYGEN_EXECUTABLE})

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fsanitize=address -fprofile-arcs -ftest-coverage")
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# Library target
add_library(matrixLib INTERFACE)
target_include_directories(matrixLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set example sources
set(EXAMPLE_SOURCES
    example/example.cpp
    # add other example source files here
)

# Create example executable target
add_executable(matrixLibExample ${EXAMPLE_SOURCES})
target_link_libraries(matrixLibExample PRIVATE matrixLib)

# Set test sources
set(TEST_SOURCES
    test/test_matrixLib.cpp
    # add other test source files here
)

# Create test executable target
include(CTest)
enable_testing()

add_executable(matrixLibTest ${TEST_SOURCES})
target_link_libraries(matrixLibTest PRIVATE matrixLib)

# Add test cases using CTest
add_test(matrixLibUnitTests matrixLibTest)

# Generate the Doxygen configuration file from the template
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

# Add a custom target to generate the Doxygen documentation
add_custom_target(
    doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
)

# Add the target to the default build target
add_dependencies(${PROJECT_NAME} doc)