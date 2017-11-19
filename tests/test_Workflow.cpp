#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <workflow/Workflow.h>

using ::testing::UnorderedElementsAre;


TEST(TestWorkflow, test_add_step) {
    workflow::Workflow workflow;
    auto step = workflow.add_step("step", {"input1", "input2"}, {"output1", "output2"});

    EXPECT_EQ(workflow.get_connected_inputs(step), UnorderedElementsAre("input1", "input2"));
    EXPECT_EQ(workflow.get_connected_outputs(step), UnorderedElementsAre("output1", "output2"));
    EXPECT_EQ(workflow.get_connected_steps(step->ins["input1"]), UnorderedElementsAre("step"));
    EXPECT_EQ(workflow.get_connected_steps(step->outs["output1"]), UnorderedElementsAre("step"));
}
