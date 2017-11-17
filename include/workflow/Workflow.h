#ifndef WORKFLOW_WORKFLOW_H
#define WORKFLOW_WORKFLOW_H

#include <string>
#include <vector>
#include <graph/PartiteGraph.h>
#include "Step.h"

class Workflow {
public:

    Step add_step(const std::string &step, const std::vector<std::string> ins, const std::vector<std::string> outs);

    std::unordered_set<Input> get_connected_inputs(const Step &step) const;

    std::unordered_set<Output> get_connected_outputs(const Step &step) const;

    std::unordered_set<Output> get_connected_outputs(const Input &input) const;

    std::unordered_set<Step> get_connected_steps(const Input &input) const;

    std::unordered_set<Step> get_connected_steps(const Output &output) const;

    std::unordered_set<Input> get_connected_input(const Output &output) const;

private:

    unsigned int identifier;

    graph::PartiteGraph<unsigned int, Step, Input, Output> graph;

    void connect_step_input(const Step &step, const Input &input);

    void connect_step_output(const Step &step, const Output &output);

    void connect_input_output(const Input &input, const Output &output);

};


#endif //WORKFLOW_WORKFLOW_H
