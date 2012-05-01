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
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Depend on parent project
include(${PROJECT_BINARY_DIR}/dmiConfig.cmake)

# Unique name for this test
set(TEST_NAME "test-template")
set(TEST_DEPS ${DMI_LIBRARIES})
set(TEST_INCS ${DMI_INCLUDE_DIRS})

# Debug mode?
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-Wall")

# Code type
set(CMAKE_C_FLAGS "-std=c99")

# Test source
file(GLOB_RECURSE SOURCES "*.c")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Depend on parent
include_directories(${TEST_INCS})

# Build target
add_executable(${TEST_NAME} ${SOURCES})
target_link_libraries(${TEST_NAME} ${TEST_DEPS})
add_test(${TEST_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME})
