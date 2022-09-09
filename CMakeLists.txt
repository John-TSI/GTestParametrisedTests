cmake_minimum_required(VERSION 3.7)

if(${CMAKE_VERSION} VERSION_LESS 3.24)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.24)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ParamTests VERSION 1.0.0 LANGUAGES CXX)

set(SRC_FILES src/sorts.cpp)
add_library(sortsLib STATIC ${SRC_FILES})

# -------- main executable --------
add_executable(sorts src/main.cpp)
target_link_libraries(sorts PRIVATE sortsLib)

# -------- test executable --------
add_executable(test_sorts tests/test_sorts.cpp)
target_link_libraries(test_sorts PRIVATE sortsLib gtest_main gmock_main)


# -------- GTest --------
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()