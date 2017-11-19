#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <workflow/Input.h>
#include <workflow/Output.h>

using ::testing::UnorderedElementsAre;

enum { step_partition, input_partition, output_partition };

TEST(OutputTest, test_pipe_to_one) {
    workflow::WorkflowGraph graph;
    auto output = std::make_shared<workflow::Output>(0, "output", graph);
    auto input = std::make_shared<workflow::Input>(1, "input");
    graph.add_vertex<output_partition>(output->identifier, output);
    graph.add_vertex<input_partition>(input->identifier, input);

    output->pipe(input);

    EXPECT_THAT(graph.get_children(0), UnorderedElementsAre(1));
}

TEST(OutputTest, test_pipe_to_many) {
    workflow::WorkflowGraph graph;
    auto output = std::make_shared<workflow::Output>(0, "output", graph);
    auto input1 = std::make_shared<workflow::Input>(1, "input1");
    auto input2 = std::make_shared<workflow::Input>(2, "input2");
    auto input3 = std::make_shared<workflow::Input>(3, "input3");
    graph.add_vertex<output_partition>(output->identifier, output);
    graph.add_vertex<input_partition>(input1->identifier, input1);
    graph.add_vertex<input_partition>(input2->identifier, input2);
    graph.add_vertex<input_partition>(input3->identifier, input3);

    output->pipe(input1);
    output->pipe(input2);
    output->pipe(input3);

    EXPECT_THAT(graph.get_children(0), UnorderedElementsAre(1, 2, 3));
}

TEST(OutputTest, test_pipe_to_connected_input) {
    workflow::WorkflowGraph graph;
    auto output1 = std::make_shared<workflow::Output>(0, "output1", graph);
    auto output2 = std::make_shared<workflow::Output>(1, "output2", graph);
    auto input = std::make_shared<workflow::Input>(2, "input");
    graph.add_vertex<output_partition>(output1->identifier, output1);
    graph.add_vertex<output_partition>(output2->identifier, output2);
    graph.add_vertex<input_partition>(input->identifier, input);

    output1->pipe(input);

    EXPECT_THROW(output1->pipe(input), std::runtime_error);
    EXPECT_THROW(output2->pipe(input), std::runtime_error);
}
