#include "Input.h"
#include "Output.h"
#include "Step.h"

#include "Workflow.h"


enum { step_partition, input_partition, output_partition };

workflow::Workflow::Workflow() :
    graph(std::make_shared<WorkflowGraph>()) {}

std::shared_ptr<workflow::Step> workflow::Workflow::add_step(
    const std::string &step_name,
    const std::vector<std::string> &input_names,
    const std::vector<std::string> &output_names)
{
    auto step = std::make_shared<Step>(
        step_name,
        input_names,
        output_names,
        this->graph
    );
    this->graph->add_vertex<step_partition>(step->identifier, step);
    for (const auto &item : *step->get_inputs()) {
        const auto &input = std::static_pointer_cast<Input>(item.second);
        this->graph->add_vertex<input_partition>(input->identifier, input);
        this->graph->add_edge(input->identifier, step->identifier);
    }
    for (const auto &item : *step->get_outputs()) {
        const auto &output = std::static_pointer_cast<Output>(item.second);
        this->graph->add_vertex<output_partition>(output->identifier, output);
        this->graph->add_edge(step->identifier, output->identifier);
    }

    return step;
}

const workflow::WorkflowGraph::FirstPartition<0> &workflow::Workflow::get_steps() const {
    return this->graph->get_partition<0>();
}

std::unordered_set<std::shared_ptr<workflow::Step>>
workflow::Workflow::get_parents(const Step &step) const {
    std::unordered_set<std::shared_ptr<workflow::Step>> parents;
    for (const auto &input : this->graph->get_parents(step.identifier)) {
        for (const auto &parent : this->graph->get_parents(input)) {
            parents.insert(this->graph->get_vertex<step_partition>(parent));
        }
    }
    return parents;
}

std::unordered_set<std::shared_ptr<workflow::Step>>
workflow::Workflow::get_children(const Step &step) const {
    std::unordered_set<std::shared_ptr<workflow::Step>> children;
    for (const auto &output : this->graph->get_children(step.identifier)) {
        for (const auto &child : this->graph->get_children(output)) {
            children.insert(this->graph->get_vertex<step_partition>(child));
        }
    }
    return children;
}

std::unordered_set<std::shared_ptr<workflow::Input>>
workflow::Workflow::get_connected_inputs(const Step &step) const {
    std::unordered_set<std::shared_ptr<workflow::Input>> inputs;
    for (const auto &input : this->graph->get_parents(step.identifier)) {
        inputs.insert(this->graph->get_vertex<input_partition>(input));
    }
    return inputs;
}

std::unordered_set<std::shared_ptr<workflow::Output>>
workflow::Workflow::get_connected_outputs(const Step &step) const {
    std::unordered_set<std::shared_ptr<workflow::Output>> outputs;
    for (const auto &output : this->graph->get_children(step.identifier)) {
        outputs.insert(this->graph->get_vertex<output_partition>(output));
    }
    return outputs;
}

std::unordered_set<std::shared_ptr<workflow::Output>>
workflow::Workflow::get_connected_outputs(const Input &input) const {
    std::unordered_set<std::shared_ptr<workflow::Output>> outputs;
    for (const auto &output : this->graph->get_parents(input.identifier)) {
        outputs.insert(this->graph->get_vertex<output_partition>(output));
    }
    return outputs;
}

const std::shared_ptr<workflow::Step> &
workflow::Workflow::get_connected_step(const Input &input) const {
    auto steps = this->graph->get_children(input.identifier);
    if (steps.size() != 1) {
        throw std::runtime_error("Step for input is missing");
    }
    return this->graph->get_vertex<step_partition>(*steps.begin());
}

const std::shared_ptr<workflow::Step> &
workflow::Workflow::get_connected_step(const Output &output) const {
    auto steps = this->graph->get_parents(output.identifier);
    if (steps.size() != 1) {
        throw std::runtime_error("Step for output is missing");
    }
    return this->graph->get_vertex<step_partition>(*steps.begin());
}

const std::unordered_set<std::shared_ptr<workflow::Input>>
workflow::Workflow::get_connected_inputs(const workflow::Output &output) const {
    std::unordered_set<std::shared_ptr<workflow::Input>> inputs;
    for (const auto &input : this->graph->get_children(output.identifier)) {
        inputs.insert(this->graph->get_vertex<input_partition>(input));
    }
    return inputs;
}
