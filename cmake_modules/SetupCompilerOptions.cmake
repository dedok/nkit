#   Copyright 2014 Vasiliy Soshnikov (dedok.mad@gmail.com)
#                  Boris T. Darchiev (boris.darchiev@gmail.com)
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

cmake_minimum_required(VERSION 2.8)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU"
    OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    ###
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if((GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
        set(HAVE_STD_CXX_11 1
            CACHE INTERNAL "have std c++ 1 support")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()

    set(CFLAGS_COMMON
      "-Wall -Wextra -Werror")# -Wno-ignored-qualifiers -Wfatal-errors")

    set(CFLAGS_REL      "-O3 ${CFLAGS_COMMON} -DNDEBUG")
    set(CFLAGS_DBG      "-O0 -ggdb3 ${CFLAGS_COMMON} -DDEBUG")
    set(CFLAGS_DBGREL   "-O2 -g ${CFLAGS_COMMON} -DNDEBUG")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS_DEBUG
                      "${CMAKE_C_FLAGS_DEBUG} ${CFLAGS_DBG}")
    set(CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} ${CFLAGS_DBG}")
    set(CMAKE_C_FLAGS_RELEASE
        "${CMAKE_C_FLAGS_RELEASE} ${CFLAGS_REL}")
    set(CMAKE_CXX_FLAGS_RELEASE
        "${CMAKE_CXX_FLAGS_RELEASE} ${CFLAGS_REL}")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO
        "${CMAKE_C_FLAGS_RELEASE} ${CFLAGS_DBGREL}")
    set(CMAKE_CXX_FLAGS_RELWITHDEBUGINFO
        "${CMAKE_CXX_FLAGS_RELWITHDEBUGINFO} ${CFLAGS_DBGREL}")
else()
  ## TODO add checks for other compilers
  set(HAVE_STD_CXX_11 1
        CACHE INTERNAL "have std c++ 1 support")
endif()

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, using Release as default")
    set(CMAKE_BUILD_TYPE "Release")
endif()
