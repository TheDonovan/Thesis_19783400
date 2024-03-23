#
# Copyright (c) 2022 Circuit Dojo LLC
#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 3.13.4)

# Determine the build type
if (NOT BUILD_TYPE)
  set(BUILD_TYPE debug)
endif()

# Print out build type
message(STATUS "Build type: ${BUILD_TYPE} 🚀")

# Define configuration files.
list(APPEND CONF_FILE
  ${CMAKE_CURRENT_SOURCE_DIR}/conf/prj.conf
  ${CMAKE_CURRENT_SOURCE_DIR}/conf/${BUILD_TYPE}.conf
  )

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(thesis-trial)

target_sources(app PRIVATE src/main.c)
