#include "Workflow.h"

enum { step_partition, input_partition, output_partition };


workflow::Workflow::Workflow() : identifier(0) {}

std::shared_ptr<workflow::Step>
workflow::Workflow::add_step(const std::string &step_,
                             const std::vector<std::string> &ins_,
                             const std::vector<std::string> &outs_)
{
    auto step = std::make_shared<workflow::Step>(this->identifier++, step_);
    this->graph.add_vertex<step_partition>(step->identifier, step);

    for (const auto &in_ : ins_) {
        auto input = std::make_shared<workflow::Input>(this->identifier++, in_);
        step->ins[in_] = input;
        this->graph.add_vertex<input_partition>(input->identifier, input);
        this->graph.add_edge(input->identifier, step->identifier);
    }

    for (const auto &out : outs_) {
        auto output = std::make_shared<workflow::Output>(this->identifier++, out, this->graph);
        step->outs[out] = output;
        this->graph.add_vertex<output_partition>(output->identifier, output);
        this->graph.add_edge(step->identifier, output->identifier);
    }

    return step;
}

std::unordered_set<std::shared_ptr<workflow::Input>>
workflow::Workflow::get_connected_inputs(const std::shared_ptr<workflow::Step> &step) const {
    std::unordered_set<std::shared_ptr<workflow::Input>> inputs;
    for (auto input : this->graph.get_parents(step->identifier)) {
        inputs.insert(this->graph.get_vertex<input_partition>(input));
    }
    return inputs;
}

std::unordered_set<std::shared_ptr<workflow::Output>>
workflow::Workflow::get_connected_outputs(const std::shared_ptr<workflow::Step> &step) const {
    std::unordered_set<std::shared_ptr<workflow::Output>> outputs;
    for (auto output : this->graph.get_children(step->identifier)) {
        outputs.insert(this->graph.get_vertex<output_partition>(output));
    }
    return outputs;
}

std::unordered_set<std::shared_ptr<workflow::Output>>
workflow::Workflow::get_connected_outputs(const std::shared_ptr<workflow::Input> &input) const {
    std::unordered_set<std::shared_ptr<workflow::Output>> outputs;
    for (auto output : this->graph.get_parents(input->identifier)) {
        outputs.insert(this->graph.get_vertex<output_partition>(output));
    }
    return outputs;
}

std::unordered_set<std::shared_ptr<workflow::Step>>
workflow::Workflow::get_connected_steps(const std::shared_ptr<workflow::Input> &input) const {
    std::unordered_set<std::shared_ptr<workflow::Step>> steps;
    for (auto step : this->graph.get_children(input->identifier)) {
        steps.insert(this->graph.get_vertex<step_partition>(step));
    }
    return steps;
}

std::unordered_set<std::shared_ptr<workflow::Step>>
workflow::Workflow::get_connected_steps(const std::shared_ptr<workflow::Output> &output) const {
    std::unordered_set<std::shared_ptr<workflow::Step>> steps;
    for (auto step : this->graph.get_parents(output->identifier)) {
        steps.insert(this->graph.get_vertex<step_partition>(step));
    }
    return steps;
}

std::unordered_set<std::shared_ptr<workflow::Input>>
workflow::Workflow::get_connected_inputs(const std::shared_ptr<workflow::Output> &output) const {
    std::unordered_set<std::shared_ptr<workflow::Input>> inputs;
    for (auto input : this->graph.get_children(output->identifier)) {
        inputs.insert(this->graph.get_vertex<input_partition>(input));
    }
    return inputs;
}
