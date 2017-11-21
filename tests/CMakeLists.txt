cmake_minimum_required(VERSION 3.8)
project(test_workflow)
set(CMAKE_CXX_STANDARD 11)


add_subdirectory(googletest)

add_executable(workflow_unit_tests
        test_Workflow.cpp)
target_include_directories(workflow_unit_tests PRIVATE
        ../include
        ${gtest_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/include)
target_link_libraries(workflow_unit_tests
        gmock_main
        workflow)
add_test(workflow_unit_tests workflow_unit_tests)
