
# ==========================================
#   Copyright (c) YEAR dynamic_static
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

include(FetchContent)

if(EXISTS "${DYNAMIC_STATIC}/dynamic_static.string/")
    FetchContent_Declare(dynamic_static.string SOURCE_DIR "${DYNAMIC_STATIC}/dynamic_static.string/")
else()
    FetchContent_Declare(
        dynamic_static.string
        GIT_REPOSITORY "https://github.com/dynamic-static/dynamic_static.string.git"
        GIT_TAG 63b0111670691790149951f68bb4b4da78dfa942
        GIT_PROGRESS TRUE
        FETCHCONTENT_UPDATES_DISCONNECTED
    )
endif()
FetchContent_MakeAvailable(dynamic_static.string)
