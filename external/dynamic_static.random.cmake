
# ==========================================
#   Copyright (c) YEAR dynamic_static
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

include(FetchContent)

if(EXISTS "${DYNAMIC_STATIC}/dynamic_static.random/")
    FetchContent_Declare(dynamic_static.random SOURCE_DIR "${DYNAMIC_STATIC}/dynamic_static.random/")
else()
    FetchContent_Declare(
        dynamic_static.random
        GIT_REPOSITORY "https://github.com/dynamic-static/dynamic_static.random.git"
        GIT_TAG 60ba456a83321d5f7bcff2a71ec701578188cd4b
        GIT_PROGRESS TRUE
        FETCHCONTENT_UPDATES_DISCONNECTED
    )
endif()
FetchContent_MakeAvailable(dynamic_static.random)
