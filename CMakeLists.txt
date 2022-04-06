
# ==========================================
#   Copyright (c) YEAR dynamic_static
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(dynamic_static.placeholder)

################################################################################
# Link libraries
set(external "${CMAKE_CURRENT_LIST_DIR}/external/")
string(REPLACE "\\" "/" DYNAMIC_STATIC "$ENV{DYNAMIC_STATIC}")
include("${external}/dynamic_static.build.cmake")
include("${external}/dynamic_static.random.cmake")
include("${external}/dynamic_static.string.cmake")
include("${external}/dynamic_static.time.cmake")
list(APPEND linkLibraries
    dynamic_static.random
    dynamic_static.string
    dynamic_static.time
)

################################################################################
# Include directories
set(includeDirectory "${CMAKE_CURRENT_LIST_DIR}/include/")
list(APPEND includeDirectories
    "${includeDirectory}/"
)

################################################################################
# Include files
set(includePath "${includeDirectory}/dynamic_static/")
list(APPEND includeFiles
    "${includePath}/placeholder.hpp"
)

################################################################################
# Source files
set(sourcePath "${CMAKE_CURRENT_LIST_DIR}/source/dynamic_static/")
list(APPEND sourceFiles
    "${sourcePath}/placeholder.cpp"
)

################################################################################
# Target
dst_add_static_library(
    target ${CMAKE_PROJECT_NAME}
    linkLibraries "${linkLibraries}"
    includeDirectories "${includeDirectories}"
    includeFiles "${includeFiles}"
    sourceFiles "${sourceFiles}"
)

################################################################################
# Tests
set(testsPath "${CMAKE_CURRENT_LIST_DIR}/tests/")
dst_add_target_test(
    target ${CMAKE_PROJECT_NAME}
    sourceFiles "${testsPath}/placeholder.tests.cpp"
)
