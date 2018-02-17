#include "Input.h"
#include "Step.h"

#include "Output.h"


workflow::Output::Output(std::string name, std::shared_ptr<WorkflowGraph> graph_) :
    workflow::Vertex(std::move(name)),
    graph(graph_) {}

void workflow::Output::pipe(const std::shared_ptr<Input> &input) {
    if (!this->graph->get_parents(input->identifier).empty()) {
        std::stringstream buffer;
        buffer << "Input " << input->name << " has already been connected to output " << this->name;
        throw std::runtime_error(buffer.str());
    }
    this->graph->add_edge(this->identifier, input->identifier);
}
