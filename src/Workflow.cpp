#include "Workflow.h"

#include <iterator>


enum { step_partition, input_partition, output_partition };


std::shared_ptr<workflow::Step>
workflow::Workflow::add_step(const std::string &step_name,
                             const std::vector<std::string> &input_names,
                             const std::vector<std::string> &output_names)
{
    this->reject_duplicates(input_names, "input");
    this->reject_duplicates(output_names, "output");

    std::shared_ptr<Step> step(new Step(step_name));
    this->graph.add_vertex<step_partition>(step->identifier, step);
    for (const auto &input_name : input_names) {
        std::shared_ptr<Input> input(new Input(input_name));
        step->inputs[input_name] = input;
        this->graph.add_vertex<input_partition>(input->identifier, input);
        this->graph.add_edge(input->identifier, step->identifier);
    }
    for (const auto &output_name : output_names) {
        std::shared_ptr<Output> output(new Output(output_name, this->graph));
        step->outputs[output_name] = output;
        this->graph.add_vertex<output_partition>(output->identifier, output);
        this->graph.add_edge(step->identifier, output->identifier);
    }

    return step;
}

const workflow::WorkflowGraph::FirstPartition<0> &workflow::Workflow::get_steps() const {
    return this->graph.get_partition<0>();
}

const std::unordered_set<std::shared_ptr<workflow::Input>>
workflow::Workflow::get_connected_inputs(const std::shared_ptr<workflow::Step> &step) const {
    std::unordered_set<std::shared_ptr<workflow::Input>> inputs;
    for (const auto &input : this->graph.get_parents(step->identifier)) {
        inputs.insert(this->graph.get_vertex<input_partition>(input));
    }
    return inputs;
}

const std::unordered_set<std::shared_ptr<workflow::Output>>
workflow::Workflow::get_connected_outputs(const std::shared_ptr<workflow::Step> &step) const {
    std::unordered_set<std::shared_ptr<workflow::Output>> outputs;
    for (const auto &output : this->graph.get_children(step->identifier)) {
        outputs.insert(this->graph.get_vertex<output_partition>(output));
    }
    return outputs;
}

const std::unordered_set<std::shared_ptr<workflow::Output>>
workflow::Workflow::get_connected_outputs(const std::shared_ptr<workflow::Input> &input) const {
    std::unordered_set<std::shared_ptr<workflow::Output>> outputs;
    for (const auto &output : this->graph.get_parents(input->identifier)) {
        outputs.insert(this->graph.get_vertex<output_partition>(output));
    }
    return outputs;
}

const std::unordered_set<std::shared_ptr<workflow::Step>>
workflow::Workflow::get_connected_steps(const std::shared_ptr<workflow::Input> &input) const {
    std::unordered_set<std::shared_ptr<workflow::Step>> steps;
    for (const auto &step : this->graph.get_children(input->identifier)) {
        steps.insert(this->graph.get_vertex<step_partition>(step));
    }
    return steps;
}

const std::unordered_set<std::shared_ptr<workflow::Step>>
workflow::Workflow::get_connected_steps(const std::shared_ptr<workflow::Output> &output) const {
    std::unordered_set<std::shared_ptr<workflow::Step>> steps;
    for (const auto &step : this->graph.get_parents(output->identifier)) {
        steps.insert(this->graph.get_vertex<step_partition>(step));
    }
    return steps;
}

const std::unordered_set<std::shared_ptr<workflow::Input>>
workflow::Workflow::get_connected_inputs(const std::shared_ptr<workflow::Output> &output) const {
    std::unordered_set<std::shared_ptr<workflow::Input>> inputs;
    for (const auto &input : this->graph.get_children(output->identifier)) {
        inputs.insert(this->graph.get_vertex<input_partition>(input));
    }
    return inputs;
}

void workflow::Workflow::reject_duplicates(const std::vector<std::string> &names, const std::string &source) const {
    auto duplicated = this->get_duplicates(names);
    if (!duplicated.empty()) {
        std::stringstream buffer;
        buffer << "Duplicate " << source << " names: ";
        std::copy(duplicated.begin(), duplicated.end(), std::ostream_iterator<std::string>(buffer, ", "));
        buffer.seekp(-2, std::ios::end);
        buffer << ".";
        throw std::runtime_error(buffer.str().erase(buffer.str().size() - 1));
    }
}

std::vector<std::string> workflow::Workflow::get_duplicates(const std::vector<std::string> &names) const {
    std::vector<std::string> duplicates;
    std::unordered_set<std::string> visited;
    for (const auto &name : names) {
        if (visited.find(name) != visited.end()) {
            duplicates.push_back(name);
        }
        visited.insert(name);
    }
    return duplicates;
}
