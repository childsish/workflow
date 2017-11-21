#include "Workflow.h"

enum { step_partition, input_partition, output_partition };


workflow::Workflow::Workflow() : identifier(0) {}

// TODO: throw exception when inputs or outputs have same names
std::shared_ptr<workflow::Step>
workflow::Workflow::add_step(const std::string &step_name,
                             const std::vector<std::string> &input_names,
                             const std::vector<std::string> &output_names)
{
    std::shared_ptr<Step> step(new Step(this->identifier++, step_name));

    this->graph.add_vertex<step_partition>(step->identifier, step);
    for (const auto &input_name : input_names) {
        std::shared_ptr<Input> input(new Input(this->identifier++, input_name));
        step->_ins[input_name] = input;
        this->graph.add_vertex<input_partition>(input->identifier, input);
        this->graph.add_edge(input->identifier, step->identifier);
    }
    for (const auto &output_name : output_names) {
        std::shared_ptr<Output> output(new Output(this->identifier++, output_name, this->graph));
        step->_outs[output_name] = output;
        this->graph.add_vertex<output_partition>(output->identifier, output);
        this->graph.add_edge(step->identifier, output->identifier);
    }

    return step;
}

const std::unordered_set<std::shared_ptr<workflow::Input>>
workflow::Workflow::get_connected_inputs(const std::shared_ptr<workflow::Step> &step) const {
    std::unordered_set<std::shared_ptr<workflow::Input>> inputs;
    for (auto input : this->graph.get_parents(step->identifier)) {
        inputs.insert(this->graph.get_vertex<input_partition>(input));
    }
    return inputs;
}

const std::unordered_set<std::shared_ptr<workflow::Output>>
workflow::Workflow::get_connected_outputs(const std::shared_ptr<workflow::Step> &step) const {
    std::unordered_set<std::shared_ptr<workflow::Output>> outputs;
    for (auto output : this->graph.get_children(step->identifier)) {
        outputs.insert(this->graph.get_vertex<output_partition>(output));
    }
    return outputs;
}

const std::unordered_set<std::shared_ptr<workflow::Output>>
workflow::Workflow::get_connected_outputs(const std::shared_ptr<workflow::Input> &input) const {
    std::unordered_set<std::shared_ptr<workflow::Output>> outputs;
    for (auto output : this->graph.get_parents(input->identifier)) {
        outputs.insert(this->graph.get_vertex<output_partition>(output));
    }
    return outputs;
}

const std::unordered_set<std::shared_ptr<workflow::Step>>
workflow::Workflow::get_connected_steps(const std::shared_ptr<workflow::Input> &input) const {
    std::unordered_set<std::shared_ptr<workflow::Step>> steps;
    for (auto step : this->graph.get_children(input->identifier)) {
        steps.insert(this->graph.get_vertex<step_partition>(step));
    }
    return steps;
}

const std::unordered_set<std::shared_ptr<workflow::Step>>
workflow::Workflow::get_connected_steps(const std::shared_ptr<workflow::Output> &output) const {
    std::unordered_set<std::shared_ptr<workflow::Step>> steps;
    for (auto step : this->graph.get_parents(output->identifier)) {
        steps.insert(this->graph.get_vertex<step_partition>(step));
    }
    return steps;
}

const std::unordered_set<std::shared_ptr<workflow::Input>>
workflow::Workflow::get_connected_inputs(const std::shared_ptr<workflow::Output> &output) const {
    std::unordered_set<std::shared_ptr<workflow::Input>> inputs;
    for (auto input : this->graph.get_children(output->identifier)) {
        inputs.insert(this->graph.get_vertex<input_partition>(input));
    }
    return inputs;
}
