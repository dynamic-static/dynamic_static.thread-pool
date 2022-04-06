
# ==========================================
#   Copyright (c) YEAR dynamic_static
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

include(FetchContent)

if(EXISTS "${DYNAMIC_STATIC}/dynamic_static.time/")
    FetchContent_Declare(dynamic_static.time SOURCE_DIR "${DYNAMIC_STATIC}/dynamic_static.time/")
else()
    FetchContent_Declare(
        dynamic_static.time
        GIT_REPOSITORY "https://github.com/dynamic-static/dynamic_static.time.git"
        GIT_TAG 5c7e744a7cbcd91709df7f1ef5986b58e8c92b99
        GIT_PROGRESS TRUE
        FETCHCONTENT_UPDATES_DISCONNECTED
    )
endif()
FetchContent_MakeAvailable(dynamic_static.time)
