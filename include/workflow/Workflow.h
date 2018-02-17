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

    /**
     * A workflow is a collection of steps with interconnected inputs and outputs. This class facilitates the
     * construction of the topology of a workflow by allowing the user to create steps and directly connecting the
     * outputs to inputs.
     * @brief a workflow
     */
    class Workflow {
    public:

        Workflow();

        /**
         * Add a step to the workflow and get a helper class to connect multiple steps together. Steps are permitted to
         * have the same names, but their inputs and outputs must be unique.
         * @brief add step and get connection helper
         * @param step name of the step
         * @param ins names of the inputs
         * @param outs names of the outputs
         * @return helper for piping steps together
         */
        std::shared_ptr<Step>
        add_step(const std::string &step,
                 const std::vector<std::string> &ins,
                 const std::vector<std::string> &outs);

        const WorkflowGraph::FirstPartition<0> &get_steps() const;

        const std::unordered_set<std::shared_ptr<Input>>
        get_connected_inputs(const std::shared_ptr<Step> &step) const;

        const std::unordered_set<std::shared_ptr<Output>>
        get_connected_outputs(const std::shared_ptr<Step> &step) const;

        const std::unordered_set<std::shared_ptr<Output>>
        get_connected_outputs(const std::shared_ptr<Input> &input) const;

        const std::unordered_set<std::shared_ptr<Step>>
        get_connected_steps(const std::shared_ptr<Input> &input) const;

        const std::unordered_set<std::shared_ptr<Step>>
        get_connected_steps(const std::shared_ptr<Output> &output) const;

        const std::unordered_set<std::shared_ptr<Input>>
        get_connected_inputs(const std::shared_ptr<Output> &output) const;

    private:

        std::shared_ptr<WorkflowGraph> graph;

    };
}

#endif //WORKFLOW_WORKFLOW_H
