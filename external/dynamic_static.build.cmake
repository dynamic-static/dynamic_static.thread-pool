
# ==========================================
#   Copyright (c) YEAR dynamic_static
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

include(FetchContent)

if(EXISTS "${DYNAMIC_STATIC}/dynamic_static.build/")
    FetchContent_Declare(dynamic_static.build SOURCE_DIR "${DYNAMIC_STATIC}/dynamic_static.build/")
else()
    FetchContent_Declare(
        dynamic_static.build
        GIT_REPOSITORY "https://github.com/dynamic-static/dynamic_static.build.git"
        GIT_TAG d43db5c7e0788b1e34883aa5fdaaf24a8435e5d9
        GIT_PROGRESS TRUE
        FETCHCONTENT_UPDATES_DISCONNECTED
    )
endif()
FetchContent_MakeAvailable(dynamic_static.build)
include("${dynamic_static.build_SOURCE_DIR}/dynamic_static.build.cmake")
