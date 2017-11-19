#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <workflow/Workflow.h>

using ::testing::UnorderedElementsAre;

MATCHER_P(Name, name, "") {
    return arg->name == name;
}

TEST(TestWorkflow, test_add_step) {
    workflow::Workflow workflow;
    auto step = workflow.add_step("step", {"input1", "input2"}, {"output1", "output2"});

    EXPECT_THAT(workflow.get_connected_inputs(step), UnorderedElementsAre(Name("input1"), Name("input2")));
    EXPECT_THAT(workflow.get_connected_outputs(step), UnorderedElementsAre(Name("output1"), Name("output2")));
    EXPECT_THAT(workflow.get_connected_steps(step->ins["input1"]), UnorderedElementsAre(Name("step")));
    EXPECT_THAT(workflow.get_connected_steps(step->outs["output1"]), UnorderedElementsAre(Name("step")));
}

TEST(TestWorkflow, test_pipe_steps_one_to_one) {
    workflow::Workflow workflow;
    auto step1 = workflow.add_step("step", {}, {"output"});
    auto step2 = workflow.add_step("step", {"input"}, {});
    step1->pipe(step2);

    EXPECT_THAT(workflow.get_connected_inputs(step1->outs["output"]), UnorderedElementsAre(Name("input")));
    EXPECT_THAT(workflow.get_connected_outputs(step2->ins["input"]), UnorderedElementsAre(Name("output")));
}
