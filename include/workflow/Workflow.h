#ifndef WORKFLOW_WORKFLOW_H
#define WORKFLOW_WORKFLOW_H

#include <memory>
#include <string>
#include <vector>
#include "Input.h"
#include "Output.h"
#include "Step.h"
#include "WorkflowGraph.h"

namespace workflow {

    /** @brief A workflow designed to allow modelling of multiple input and multiple output steps.
     *
     * A workflow is a collection of steps with interconnected inputs and outputs. This class
     * facilitates the construction of the topology of a workflow by allowing the user to create
     * steps and directly connecting the outputs to inputs.
     */
    class Workflow {
    public:

        Workflow();

        /** @brief Add step and get connection helper.
         *
         * Add a step to the workflow and get a helper class to connect multiple steps together. Steps are permitted to
         * have the same names, but their inputs and outputs must be unique for the step.
         * @param step_name The name of the step.
         * @param input_names The names of the inputs.
         * @param output_names The names of the outputs.
         * @return A helper/identifier for piping steps together.
         */
        std::shared_ptr<Step> add_step(const std::string &step_name,
                                       const std::vector<std::string> &input_names,
                                       const std::vector<std::string> &output_names);

        /** @brief Get the steps from the workflow. */
        const WorkflowGraph::FirstPartition<0> &get_steps() const;

        /** @brief Get the parent steps of the specified step. */
        std::unordered_set<std::shared_ptr<Step>>
        get_parents(const Step &step) const;

        /** @brief Get the child steps of the specified step. */
        std::unordered_set<std::shared_ptr<Step>>
        get_children(const Step &step) const;

        /** @brief Get the inputs to a specific step. */
        std::unordered_set<std::shared_ptr<Input>>
        get_connected_inputs(const Step &step) const;

        /** @brief Get the outputs from a specific step. */
        std::unordered_set<std::shared_ptr<Output>>
        get_connected_outputs(const Step &step) const;

        /** @brief Get the outputs connected to an input. */
        std::unordered_set<std::shared_ptr<Output>>
        get_connected_outputs(const Input &input) const;

        /** @brief Get the step for an input . */
        const std::shared_ptr<Step> &
        get_connected_step(const Input &input) const;

        /** @brief Get the step for an output. */
        const std::shared_ptr<Step> &
        get_connected_step(const Output &output) const;

        /** @brief Get the inputs connected to an output. */
        const std::unordered_set<std::shared_ptr<Input>>
        get_connected_inputs(const Output &output) const;

    private:

        std::shared_ptr<WorkflowGraph> graph;

    };
}

#endif //WORKFLOW_WORKFLOW_H
