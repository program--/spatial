cmake_minimum_required(VERSION 3.17...3.26)

project(spatial
        VERSION     0.1.0
        DESCRIPTION "Toolkit for spatial analysis and modeling"
        LANGUAGES   CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(_SPATIAL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(_SPATIAL_SOURCE_DIR  "${CMAKE_CURRENT_LIST_DIR}/src")

add_library(spatial INTERFACE)
target_compile_features(spatial INTERFACE cxx_std_14)
set_target_properties(spatial PROPERTIES CXX_EXTENSIONS OFF)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/spatial")

if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
    include(CTest)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/tests")
endif()
