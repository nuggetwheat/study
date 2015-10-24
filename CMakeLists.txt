#
# Copyright (C) 2007-2015 Hypertable, Inc.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 3
# of the License, or any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.
#

project(STUDY)

# cmake behavior compatibility
cmake_minimum_required(VERSION 2.8)
mark_as_advanced(CMAKE_BACKWARDS_COMPATIBILITY)

# saner control structure syntax
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

if (COMMAND cmake_policy)
  # we prefer the more strict behavior, to find out more:
  # cmake --help-policy CMP0003
  cmake_policy(SET CMP0003 NEW)
endif ()

# Something nice for GUI like ccmake
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Options: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

#uname -p says i386, but we know better when its x86 apple
if (APPLE AND "${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "i386")
    SET(CMAKE_SYSTEM_PROCESSOR "x86_64")
endif ()

#detect 32 or 64 bit compiler
if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(i.86|x86|x86_64)$")
    include(CheckTypeSize)
    check_type_size("void*" SIZEOF_VOID_P BUILTIN_TYPES_ONLY)
    if (${SIZEOF_VOID_P} EQUAL 8)
        set(CMAKE_SYSTEM_PROCESSOR_x86 64)
    else ()
        set(CMAKE_SYSTEM_PROCESSOR_x86 32)
    endif ()
endif ()

# install directory prefix
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/opt/study"
      CACHE PATH "installation directory prefix" FORCE)
endif ()

# Enable testing
enable_testing()

# gcc warning settings
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  if (${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-long-long -pthreads")
    SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-long-long -pthreads")
  else (${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-long-long")
    SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-long-long")
  endif (${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
endif ()

# C flags
SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_LARGEFILE_SOURCE")
SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64")
SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_REENTRANT")
SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

# C++ flags
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_LARGEFILE_SOURCE")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FILE_OFFSET_BITS=64")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_REENTRANT")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (ASAN)
  SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
  SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer")
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
endif ()
 
# Disable dynamic library build
set (BUILD_SHARED_LIBS OFF)

# Locate required packages
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Verison install directory
set(INSTALL_DIR ${CMAKE_INSTALL_PREFIX})

find_package(Threads REQUIRED)
message(STATUS "Use thread library: ${CMAKE_THREAD_LIBS_INIT}")
find_package(Boost REQUIRED)

if (APPLE)
   SET (CMAKE_EXE_LINKER_FLAGS "-framework IOKit -framework CoreFoundation")
endif ()

# include directories
include_directories(src/cc ${Boost_INCLUDE_DIRS})

if (GCC_VERSION MATCHES "^([4-9]|[1-9][0-9]+)\\.")
  SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-variadic-macros")
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-variadic-macros")
  # turn off deprecated feature warnings for gcc 4.3+
  if (GCC_VERSION MATCHES "^([4-9]|[1-9][0-9]+)\\.([3-9]|[1-9][0-9]+)")
    SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated")
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
  endif ()
elseif (GCC_VERSION MATCHES "^([4-9]|[1-9][0-9]+)\\.")
  message(STATUS "Ancient gcc detected, hope it finishes despite warnings...")
endif ()

# sub-project directories
add_subdirectory(src)

# Maven Repository
if (NOT MAVEN_REPOSITORY)
   SET (MAVEN_REPOSITORY "~/.m2/repository")
endif ()

