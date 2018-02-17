#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <workflow/Input.h>
#include <workflow/Output.h>
#include <workflow/Step.h>
#include <workflow/Workflow.h>

using ::testing::UnorderedElementsAre;

MATCHER_P(Name, name, "") {
    return arg->name == name;
}

TEST(TestWorkflow, test_add_step) {
    workflow::Workflow workflow;

    EXPECT_TRUE(workflow.get_steps().empty());

    auto step = workflow.add_step("step", {"input1", "input2"}, {"output1", "output2"});
    EXPECT_THAT(workflow.get_connected_inputs(step), UnorderedElementsAre(Name("input1"), Name("input2")));
    EXPECT_THAT(workflow.get_connected_outputs(step), UnorderedElementsAre(Name("output1"), Name("output2")));
    EXPECT_THAT(workflow.get_connected_steps(step->get_input("input1")), UnorderedElementsAre(Name("step")));
    EXPECT_THAT(workflow.get_connected_steps(step->get_output("output1")), UnorderedElementsAre(Name("step")));
    EXPECT_EQ(workflow.get_steps().size(), 1);
}

TEST(TestWorkflow, test_add_step_with_repeat_names) {
    workflow::Workflow workflow;

    EXPECT_THROW(workflow.add_step("step", {"input", "input"}, {}), std::runtime_error);
    EXPECT_THROW(workflow.add_step("step", {"input1", "input1", "input2", "input2"}, {});, std::runtime_error);
    EXPECT_THROW(workflow.add_step("step", {}, {"output", "output"}), std::runtime_error);
}

TEST(TestWorkflow, test_pipe_one_to_one) {
    workflow::Workflow workflow;
    auto step1 = workflow.add_step("step", {}, {"output"});
    auto step2 = workflow.add_step("step", {"input"}, {});

    step1->pipe(step2);

    EXPECT_THAT(workflow.get_connected_inputs(step1->get_output("output")), UnorderedElementsAre(Name("input")));
    EXPECT_THAT(workflow.get_connected_outputs(step2->get_input("input")), UnorderedElementsAre(Name("output")));
}

TEST(TestWorkflow, test_pipe_one_to_multiple) {
    workflow::Workflow workflow;
    auto step1 = workflow.add_step("step", {}, {"output"});
    auto step2 = workflow.add_step("step", {"input1", "input2"}, {});

    EXPECT_THROW(step1->pipe(step2), std::runtime_error);
}

TEST(TestWorkflow, test_pipe_multiple_to_one) {
    workflow::Workflow workflow;
    auto step1 = workflow.add_step("step", {}, {"output1", "output2"});
    auto step2 = workflow.add_step("step", {"input"}, {});

    EXPECT_THROW(step1->pipe(step2), std::runtime_error);
}

TEST(TestWorkflow, test_pipe_one_to_none) {
    workflow::Workflow workflow;
    auto step1 = workflow.add_step("step", {}, {"output"});
    auto step2 = workflow.add_step("step", {}, {});

    EXPECT_THROW(step1->pipe(step2), std::runtime_error);
}

TEST(TestWorkflow, test_pipe_none_to_one) {
    workflow::Workflow workflow;
    auto step1 = workflow.add_step("step", {}, {});
    auto step2 = workflow.add_step("step", {"input"}, {});

    EXPECT_THROW(step1->pipe(step2), std::runtime_error);
}

TEST(TestWorkflow, test_pipe_output_to_input) {
    workflow::Workflow workflow;
    auto step1 = workflow.add_step("step", {}, {"output1", "output2"});
    auto step2 = workflow.add_step("step", {"input1", "input2"}, {});

    step1->get_output("output2")->pipe(step2->get_input("input2"));

    EXPECT_THAT(workflow.get_connected_inputs(step1->get_output("output2")), UnorderedElementsAre(Name("input2")));
    EXPECT_THAT(workflow.get_connected_outputs(step2->get_input("input2")), UnorderedElementsAre(Name("output2")));
    EXPECT_TRUE(workflow.get_connected_inputs(step1->get_output("output1")).empty());
    EXPECT_TRUE(workflow.get_connected_outputs(step2->get_input("input1")).empty());
}

TEST(TestWorkflow, test_pipe_one_to_many) {
    workflow::Workflow workflow;
    auto step1 = workflow.add_step("step", {}, {"output"});
    auto step2 = workflow.add_step("step", {"input1"}, {});
    auto step3 = workflow.add_step("step", {"input2"}, {});
    auto step4 = workflow.add_step("step", {"input3"}, {});

    step1->pipe(step2);
    step1->pipe(step3);
    step1->pipe(step4);

    EXPECT_THAT(workflow.get_connected_inputs(step1->get_output("output")), UnorderedElementsAre(Name("input1"), Name("input2"), Name("input3")));
    EXPECT_THAT(workflow.get_connected_outputs(step2->get_input("input1")), UnorderedElementsAre(Name("output")));
    EXPECT_THAT(workflow.get_connected_outputs(step3->get_input("input2")), UnorderedElementsAre(Name("output")));
    EXPECT_THAT(workflow.get_connected_outputs(step4->get_input("input3")), UnorderedElementsAre(Name("output")));
}

TEST(TestWorkflow, test_pipe_repeat) {
    workflow::Workflow workflow;
    auto step1 = workflow.add_step("step", {}, {"output"});
    auto step2 = workflow.add_step("step", {"input"}, {});

    step1->pipe(step2);

    EXPECT_THROW(step1->pipe(step2), std::runtime_error);
}
