#include "Input.h"
#include "Step.h"

#include "Output.h"


workflow::Output::Output(const std::string &name, std::shared_ptr<WorkflowGraph> graph) :
    workflow::Connection(name),
    graph(std::move(graph)) {}

void workflow::Output::pipe(const Input &input) {
    if (!this->graph->get_parents(input.identifier).empty()) {
        std::stringstream buffer;
        buffer << "Input " << input.name << " has already been connected to output " << this->name;
        throw std::runtime_error(buffer.str());
    }
    this->graph->add_edge(this->identifier, input.identifier);
}

void workflow::Output::pipe(const Step &step) {
    auto inputs = step.get_inputs();
    if (inputs->size() == 1) {
        this->pipe(*inputs->begin()->second);
    }
    else if (inputs->empty()) {
        throw std::runtime_error("Nothing to pipe to in step " + step.name);
    }
    else if (inputs->size() > 1) {
        throw std::runtime_error("Too many inputs to pipe to in step " + step.name);
    }
}
