
# ==========================================
#   Copyright (c) 2022 dynamic_static
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(dynamic_static.thread-pool)

################################################################################
# Link libraries
set(external "${CMAKE_CURRENT_LIST_DIR}/external/")
string(REPLACE "\\" "/" DYNAMIC_STATIC "$ENV{DYNAMIC_STATIC}")
include("${external}/dynamic_static.build.cmake")
include("${external}/dynamic_static.time.cmake")

################################################################################
# Target
set(includeDirectory "${CMAKE_CURRENT_LIST_DIR}/include/")
dst_add_interface_library(
    target ${CMAKE_PROJECT_NAME}
    includeDirectories "${includeDirectory}"
    includeFiles "${includeDirectory}/dynamic_static/thread-pool.hpp"
)

################################################################################
# Tests
set(testsPath "${CMAKE_CURRENT_LIST_DIR}/tests/")
dst_add_target_test(
    target ${CMAKE_PROJECT_NAME}
    linkLibraries dynamic_static.time
    sourceFiles "${testsPath}/thread-pool.tests.cpp"
)
