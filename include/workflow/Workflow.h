#ifndef WORKFLOW_WORKFLOW_H
#define WORKFLOW_WORKFLOW_H

#include <memory>
#include <string>
#include <vector>
#include <graph/PartiteGraph.h>
#include "Input.h"
#include "Output.h"
#include "Step.h"

namespace workflow {

    typedef graph::PartiteGraph<
            unsigned int,
            std::shared_ptr<Step>,
            std::shared_ptr<Input>,
            std::shared_ptr<Output>
    > WorkflowGraph;

    class Workflow {
    public:

        std::shared_ptr<Step> add_step(const std::string &step, const std::vector<std::string> &ins, const std::vector<std::string> &outs);

        std::unordered_set<std::shared_ptr<Input>> get_connected_inputs(const std::shared_ptr<Step> &step) const;

        std::unordered_set<std::shared_ptr<Output>> get_connected_outputs(const std::shared_ptr<Step> &step) const;

        std::unordered_set<std::shared_ptr<Output>> get_connected_outputs(const std::shared_ptr<Input> &input) const;

        std::unordered_set<std::shared_ptr<Step>> get_connected_steps(const std::shared_ptr<Input> &input) const;

        std::unordered_set<std::shared_ptr<Step>> get_connected_steps(const std::shared_ptr<Output> &output) const;

        std::unordered_set<std::shared_ptr<Input>> get_connected_input(const std::shared_ptr<Output> &output) const;

    private:

        unsigned int identifier;

        WorkflowGraph graph;

    };
}

#endif //WORKFLOW_WORKFLOW_H
