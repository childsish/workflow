cmake_minimum_required(VERSION 3.8)
project(workflow)
set(CMAKE_CXX_STANDARD 11)


# Options

option(WORKFLOW_BUILD_TESTS "Enable/Disable unit tests for workflow library." on)


# Add graph library

set(GRAPH_BUILD_TESTS off CACHE BOOL "Disable graph library unit tests.")
add_subdirectory(lib/graph)


# Add workflow library

add_library(workflow
        include/workflow/WorkflowGraph.h
        src/Vertex.cpp include/workflow/Vertex.h
        src/Input.cpp include/workflow/Input.h
        src/Output.cpp include/workflow/Output.h
        src/Step.cpp include/workflow/Step.h
        src/Workflow.cpp include/workflow/Workflow.h)
target_include_directories(workflow PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        include/workflow)
target_link_libraries(workflow
        graph)

if (WORKFLOW_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
