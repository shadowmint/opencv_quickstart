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

# Cocoa for sdl on osx
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  find_library(COCOA_LIBRARY Cocoa)
  set (EXTRA_LIBRARIES ${EXTRA_LIBRARIES} ${COCOA_LIBRARY})
endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# mingw for windows <3
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set (EXTRA_LIBRARIES ${EXTRA_LIBRARIES} mingw32)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

# Set library extension
set(PROJECT_LIB_EXT "dll.a")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(PROJECT_LIB_EXT "dylib")
endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# Deps: sdl
set(LIBSDL_LIBRARY "${LIBSDL_LIBRARY};${PROJECT_SOURCE_DIR}/deps/libsdl/build/.libs/libSDLmain.a")
set(LIBSDL_LIBRARY "${LIBSDL_LIBRARY};${PROJECT_SOURCE_DIR}/deps/libsdl/build/.libs/libSDL.${PROJECT_LIB_EXT}")
set(LIBSDL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/deps/libsdl/include;${PROJECT_SOURCE_DIR}/deps/libsdl/build/x86/include/")
find_package(LIBSDL REQUIRED)
set (EXTRA_LIBRARIES ${EXTRA_LIBRARIES} ${LIBSDL_LIBRARY})
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${LIBSDL_INCLUDE_DIRS})

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
configure_file(dmiConfig.cmake.in "${CMAKE_BINARY_DIR}/dmiConfig.cmake")

# Test config
option(BUILD_UNIT_TESTS "Build unit tests" ON)
option(BUILD_INTEGRATION_TESTS "Build integration tests" OFF)

# Collect test files
if(BUILD_UNIT_TESTS)
  set(TESTING_ENABLED 1)
  file(GLOB_RECURSE TEST_PROJECTS tests/CMakeLists*)
endif(BUILD_UNIT_TESTS)

# Build tests
if(TESTING_ENABLED)
  enable_testing()
  foreach(TEST ${TEST_PROJECTS})
    string(REGEX REPLACE "CMakeLists.txt" "" TEST_DIR ${TEST})
    add_subdirectory(${TEST_DIR})
  endforeach(TEST)
endif(TESTING_ENABLED)
