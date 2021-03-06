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

if (UNIX OR APPLE AND NOT DEFINED PREFIX)
  include (CheckIncludeFiles)
  check_include_files(syslog.h HAVE_SYSLOG_H)
  set(PREFIX /usr/local CACHE INTERNAl "nkit isntall prefix")
  if (DEFINED ENV{PREFIX})
    set(PREFIX $ENV{PREFIX} CACHE INTERNAL "nkit install prefix")
  endif()
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/nkit/detail/config.h.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/nkit/detail/config.h")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/version.cpp.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/version.cpp" @ONLY)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/nkit/version.h.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/nkit/version.h" @ONLY)

set(LOGGER_IMPL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/logger/rotate_logger.cpp)

if ((UNIX OR APPLE AND HAVE_SYSLOG_H) OR WIN32)
  set(LOGGER_IMPL_SOURCES
     ${LOGGER_IMPL_SOURCES}
     ${CMAKE_CURRENT_SOURCE_DIR}/logger/rsyslog_logger.cpp)
endif()

add_library(${PROJECT_NAME}
            STATIC
            ${CMAKE_CURRENT_SOURCE_DIR}/dynamic/dynamic.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/dynamic/dynamic_path.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/dynamic/dynamic_table.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/dynamic/dynamic_json.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/dynamic/dynamic_table_index_comparators.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tools.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/constants.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/version.cpp
            ${LOGGER_IMPL_SOURCES}
            )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/nkit
        DESTINATION ${PREFIX}/include
        PATTERN ".*" EXCLUDE
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                    GROUP_EXECUTE GROUP_READ)

#install(FILES ${CMAKE_SOURCE_DIR}/cmake_modules/FindYajl.cmake
#        ${CMAKE_SOURCE_DIR}/cmake_modules/FindNKit.cmake
#        ${CMAKE_SOURCE_DIR}/cmake_modules/AddPrecompiledHeader.cmake
#        ${CMAKE_SOURCE_DIR}/cmake_modules/Mercurial.cmake
#        ${CMAKE_SOURCE_DIR}/cmake_modules/SetupCompilerOptions.cmake
#        DESTINATION ${PREFIX}/share/cmake-2.8/Modules/nkit
#        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
#                    GROUP_EXECUTE GROUP_READ)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${PREFIX}/bin/
        LIBRARY DESTINATION ${PREFIX}/lib/
        ARCHIVE DESTINATION ${PREFIX}/lib/)
