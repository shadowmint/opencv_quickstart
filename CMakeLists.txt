# Copyright 2011 Douglas Linder
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WDMIRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required (VERSION 2.6)
project (DMI)

# CMake package modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Collect source files
file(GLOB_RECURSE SOURCES src/*.c)

# Code type
set(CMAKE_C_FLAGS "-std=c99")
set (CMAKE_OSX_DMICHITECTURES "i386")

# Debug mode?
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wimplicit-function-declaration -Wreturn-type -Wstrict-prototypes -Wextra -g")

# Deps: self
set(INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")

# Deps: math
set(EXTRA_LIBRARIES ${EXTRA_LIBRARIES} m)

# Deps: libusb (for libfreenect)
find_package(libusb-1.0 REQUIRED)
include_directories(${LIBUSB_1_INCLUDE_DIRS})

# Deps: libfreenect
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(FREENECT_LIBRARY "${PROJECT_SOURCE_DIR}/deps/libfreenect/build/lib/libfreenect.so")
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(FREENECT_LIBRARY "${PROJECT_SOURCE_DIR}/deps/libfreenect/build/lib/libfreenect.dylib")
endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(FREENECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/deps/libfreenect/include")
find_package(freenect REQUIRED)
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${FREENECT_INCLUDE_DIRS})
set(EXTRA_LIBRARIES ${EXTRA_LIBRARIES} ${FREENECT_LIBRARIES})

# Deps: libn
set(n_DIR "${PROJECT_SOURCE_DIR}/deps/libn/build/")
find_package(n REQUIRED)
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${DMI_INCLUDE_DIRS})
set(EXTRA_LIBRARIES ${EXTRA_LIBRARIES} ${DMI_SHARED_LIBRARIES})

# Deps: opengl
IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  SET(EXTRA_LIBRARIES ${EXTRA_LIBRARIES} GL GLU X11)
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
  SET (EXTRA_LIBRARIES ${EXTRA_LIBRARIES} ${OpenGL_LIBRARY})
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# Deps: glut
FIND_LIBRARY(GLUT required)
SET (EXTRA_LIBRARIES ${EXTRA_LIBRARIES} ${GLUT_LIBRARY})

# Build library
add_library (dmi SHARED ${SOURCES})
include_directories(${INCLUDE_DIRS})
target_link_libraries(dmi ${EXTRA_LIBRARIES})

# Build demo worker
add_executable(demo src/demo.c)
target_link_libraries(demo ${EXTRA_LIBRARIES})

# Export
get_property(dmi_location TARGET dmi PROPERTY LOCATION)
set(LIBRARIES "${dmi_location};${EXTRA_LIBRARIES}")
configure_file(dmiConfig.cmake.in "${CMAKE_BINDMIY_DIR}/dmiConfig.cmake")

# Test config
option(BUILD_UNIT_TESTS "Build unit tests" ON)
option(BUILD_INTEGRATION_TESTS "Build integration tests" OFF)

# Collect test files
if(BUILD_UNIT_TESTS)
  set(TESTING_ENABLED 1)
  file(GLOB_RECURSE TEST_PROJECTS tests/unit/CMakeLists*)
endif(BUILD_UNIT_TESTS)
if(BUILD_INTEGRATION_TESTS)
  set(TESTING_ENABLED 1)
  file(GLOB_RECURSE TEST_IPROJECTS tests/integration/CMakeLists*)
  set(TEST_PROJECTS "${TEST_PROJECTS};${TEST_IPROJECTS}")
endif(BUILD_INTEGRATION_TESTS)

# Build tests
if(TESTING_ENABLED)
  enable_testing()
  foreach(TEST ${TEST_PROJECTS})
    string(REGEX REPLACE "CMakeLists.txt" "" TEST_DIR ${TEST})
    add_subdirectory(${TEST_DIR})
  endforeach(TEST)
endif(TESTING_ENABLED)
