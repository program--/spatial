
find_package(doctest REQUIRED)
include(doctest)

function(spatial_add_test TEST_NAME)
    set(multiValueArgs OBJECTS LINKS)
    cmake_parse_arguments ("SPATIAL_TEST" "" "" "${multiValueArgs}" ${ARGN})
    list                  (REMOVE_DUPLICATES SPATIAL_TEST_LINKS)
    add_executable        (${TEST_NAME} runner.cpp ${SPATIAL_TEST_OBJECTS})
    target_link_libraries (${TEST_NAME} PUBLIC doctest::doctest ${SPATIAL_TEST_LINKS})
    set_target_properties (${TEST_NAME} PROPERTIES FOLDER tests)
    doctest_discover_tests(${TEST_NAME})
endfunction()

spatial_add_test(test_raster
    OBJECTS
        test_raster.cpp
    LINKS
        spatial::raster)
