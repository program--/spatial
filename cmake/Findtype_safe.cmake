include(FetchContent)

FetchContent_Declare(
    type_safe
    GIT_REPOSITORY https://github.com/foonathan/type_safe.git
    GIT_TAG        v0.2.3
)

FetchContent_MakeAvailable(type_safe)
