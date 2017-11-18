#include "Output.h"

workflow::Output::Output(unsigned int identifier_, const std::string &name_, WorkflowGraph &graph_) :
        identifier(identifier_),
        name(name_),
        graph(graph_) {}

void workflow::Output::pipe(const std::shared_ptr<Input> &input) {
    this->graph.add_edge(this->identifier, input->identifier);
}
