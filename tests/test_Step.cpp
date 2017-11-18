#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <workflow/Input.h>
#include <workflow/Output.h>
#include <workflow/Step.h>

using ::testing::UnorderedElementsAre;

enum { step_partition, input_partition, output_partition };

TEST(StepTest, test_pipe_one_to_one) {
    unsigned int identifier = 0;
    workflow::WorkflowGraph graph;
    auto step1 = std::make_shared<workflow::Step>(identifier++, "step1");
    auto step2 = std::make_shared<workflow::Step>(identifier++, "step2");
    auto output1_1 = std::make_shared<workflow::Output>(identifier++, "output1_1", graph);
    auto input2_1 = std::make_shared<workflow::Input>(identifier++, "input2_1");
    step1->outs[output1_1->name] = output1_1;
    step2->ins[input2_1->name] = input2_1;
    graph.add_vertex<step_partition>(step1->identifier, step1);
    graph.add_vertex<step_partition>(step2->identifier, step2);
    graph.add_vertex<output_partition>(output1_1->identifier, output1_1);
    graph.add_vertex<input_partition>(input2_1->identifier, input2_1);

    step1->pipe(step2);

    EXPECT_THAT(graph.get_children(2), UnorderedElementsAre(3));
}

TEST(StepTest, test_pipe_one_to_many) {
    unsigned int identifier = 0;
    workflow::WorkflowGraph graph;
    auto step1 = std::make_shared<workflow::Step>(identifier++, "step1");
    auto step2 = std::make_shared<workflow::Step>(identifier++, "step2");
    auto output1_1 = std::make_shared<workflow::Output>(identifier++, "output1_1", graph);
    auto input2_1 = std::make_shared<workflow::Input>(identifier++, "input2_1");
    auto input2_2 = std::make_shared<workflow::Input>(identifier++, "input2_2");
    step1->outs[output1_1->name] = output1_1;
    step2->ins[input2_1->name] = input2_1;
    step2->ins[input2_2->name] = input2_2;
    graph.add_vertex<step_partition>(step1->identifier, step1);
    graph.add_vertex<step_partition>(step2->identifier, step2);
    graph.add_vertex<output_partition>(output1_1->identifier, output1_1);
    graph.add_vertex<input_partition>(input2_1->identifier, input2_1);
    graph.add_vertex<input_partition>(input2_2->identifier, input2_2);

    EXPECT_THROW(step1->pipe(step2), std::runtime_error);
}

TEST(StepTest, test_pipe_many_to_one) {
    unsigned int identifier = 0;
    workflow::WorkflowGraph graph;
    auto step1 = std::make_shared<workflow::Step>(identifier++, "step1");
    auto step2 = std::make_shared<workflow::Step>(identifier++, "step2");
    auto output1_1 = std::make_shared<workflow::Output>(identifier++, "output1_1", graph);
    auto output1_2 = std::make_shared<workflow::Output>(identifier++, "output1_2", graph);
    auto input2_1 = std::make_shared<workflow::Input>(identifier++, "input2_1");
    step1->outs[output1_1->name] = output1_1;
    step1->outs[output1_2->name] = output1_2;
    step2->ins[input2_1->name] = input2_1;
    graph.add_vertex<step_partition>(step1->identifier, step1);
    graph.add_vertex<step_partition>(step2->identifier, step2);
    graph.add_vertex<output_partition>(output1_1->identifier, output1_1);
    graph.add_vertex<output_partition>(output1_2->identifier, output1_2);
    graph.add_vertex<input_partition>(input2_1->identifier, input2_1);

    EXPECT_THROW(step1->pipe(step2), std::runtime_error);
}
TEST(StepTest, test_pipe_one_to_none) {
    unsigned int identifier = 0;
    workflow::WorkflowGraph graph;
    auto step1 = std::make_shared<workflow::Step>(identifier++, "step1");
    auto step2 = std::make_shared<workflow::Step>(identifier++, "step2");
    auto output1_1 = std::make_shared<workflow::Output>(identifier++, "output1_1", graph);
    step1->outs[output1_1->name] = output1_1;
    graph.add_vertex<step_partition>(step1->identifier, step1);
    graph.add_vertex<step_partition>(step2->identifier, step2);
    graph.add_vertex<output_partition>(output1_1->identifier, output1_1);

    EXPECT_THROW(step1->pipe(step2), std::runtime_error);
}

TEST(StepTest, test_pipe_none_to_one) {
    unsigned int identifier = 0;
    workflow::WorkflowGraph graph;
    auto step1 = std::make_shared<workflow::Step>(identifier++, "step1");
    auto step2 = std::make_shared<workflow::Step>(identifier++, "step2");
    auto input2_1 = std::make_shared<workflow::Input>(identifier++, "input2_1");
    step2->ins[input2_1->name] = input2_1;
    graph.add_vertex<step_partition>(step1->identifier, step1);
    graph.add_vertex<step_partition>(step2->identifier, step2);
    graph.add_vertex<input_partition>(input2_1->identifier, input2_1);

    EXPECT_THROW(step1->pipe(step2), std::runtime_error);
}
