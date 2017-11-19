#include "Output.h"

workflow::Output::Output(unsigned int identifier_, const std::string &name_, WorkflowGraph &graph_) :
        identifier(identifier_),
        name(name_),
        graph(graph_) {}

void workflow::Output::pipe(const std::shared_ptr<Input> &input) {
    if (this->graph.get_parents(input->identifier).size() > 0) {
        std::stringstream buffer;
        buffer << "Input " << input->name << " has already been connected to output " << this->name;
        throw std::runtime_error(buffer.str());
    }
    this->graph.add_edge(this->identifier, input->identifier);
}
