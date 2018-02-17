#include "Workflow.h"


enum { step_partition, input_partition, output_partition };

std::shared_ptr<workflow::Step>
workflow::Workflow::add_step(const std::string &step_name,
                             const std::vector<std::string> &input_names,
                             const std::vector<std::string> &output_names)
{
    std::shared_ptr<Step> step = std::make_shared<Step>(
        step_name,
        input_names,
        output_names,
        this->graph
    );
    this->graph->add_vertex<step_partition>(step->identifier, step);
    for (const auto &item : step->get_inputs()) {
        this->graph->add_vertex<input_partition>(item.second->identifier, item.second);
        this->graph->add_edge(item.second->identifier, step->identifier);
    }
    for (const auto &item : step->get_outputs()) {
        this->graph->add_vertex<output_partition>(item.second->identifier, item.second);
        this->graph->add_edge(step->identifier, item.second->identifier);
    }

    return step;
}

const workflow::WorkflowGraph::FirstPartition<0> &workflow::Workflow::get_steps() const {
    return this->graph->get_partition<0>();
}

const std::unordered_set<std::shared_ptr<workflow::Input>>
workflow::Workflow::get_connected_inputs(const std::shared_ptr<workflow::Step> &step) const {
    std::unordered_set<std::shared_ptr<workflow::Input>> inputs;
    for (const auto &input : this->graph->get_parents(step->identifier)) {
        inputs.insert(this->graph->get_vertex<input_partition>(input));
    }
    return inputs;
}

const std::unordered_set<std::shared_ptr<workflow::Output>>
workflow::Workflow::get_connected_outputs(const std::shared_ptr<workflow::Step> &step) const {
    std::unordered_set<std::shared_ptr<workflow::Output>> outputs;
    for (const auto &output : this->graph->get_children(step->identifier)) {
        outputs.insert(this->graph->get_vertex<output_partition>(output));
    }
    return outputs;
}

const std::unordered_set<std::shared_ptr<workflow::Output>>
workflow::Workflow::get_connected_outputs(const std::shared_ptr<workflow::Input> &input) const {
    std::unordered_set<std::shared_ptr<workflow::Output>> outputs;
    for (const auto &output : this->graph->get_parents(input->identifier)) {
        outputs.insert(this->graph->get_vertex<output_partition>(output));
    }
    return outputs;
}

const std::unordered_set<std::shared_ptr<workflow::Step>>
workflow::Workflow::get_connected_steps(const std::shared_ptr<workflow::Input> &input) const {
    std::unordered_set<std::shared_ptr<workflow::Step>> steps;
    for (const auto &step : this->graph->get_children(input->identifier)) {
        steps.insert(this->graph->get_vertex<step_partition>(step));
    }
    return steps;
}

const std::unordered_set<std::shared_ptr<workflow::Step>>
workflow::Workflow::get_connected_steps(const std::shared_ptr<workflow::Output> &output) const {
    std::unordered_set<std::shared_ptr<workflow::Step>> steps;
    for (const auto &step : this->graph->get_parents(output->identifier)) {
        steps.insert(this->graph->get_vertex<step_partition>(step));
    }
    return steps;
}

const std::unordered_set<std::shared_ptr<workflow::Input>>
workflow::Workflow::get_connected_inputs(const std::shared_ptr<workflow::Output> &output) const {
    std::unordered_set<std::shared_ptr<workflow::Input>> inputs;
    for (const auto &input : this->graph->get_children(output->identifier)) {
        inputs.insert(this->graph->get_vertex<input_partition>(input));
    }
    return inputs;
}
