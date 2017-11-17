cmake_minimum_required(VERSION 3.8)
project(workflow)
set(CMAKE_CXX_STANDARD 11)


# Add graph library

set(GRAPH_BUILD_TESTS off CACHE BOOL "Disable graph library unit tests.")
add_subdirectory(lib/graph)


# Add workflow library

add_library(workflow
        src/Step.cpp include/workflow/Step.h
        src/Workflow.cpp include/workflow/Workflow.h)
target_include_directories(workflow PRIVATE
        include/workflow)
target_link_libraries(workflow
        graph)
