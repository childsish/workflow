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
