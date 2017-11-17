#include "Step.h"

Step::Step(unsigned int identifier_, const std::string &name_,
           graph::PartiteGraph<unsigned int, Step, Input, Output> graph_) :
    identifier(identifier_),
    name(name_),
    graph(graph_) {}

void Step::pipe(Step &that) {
    if (this->outs.size() == 1 && that.ins.size() == 1) {
        unsigned int out_id = this->outs.begin()->second.identifier;
        unsigned int in_id = this->ins.begin()->second.identifier;
        this->graph.add_edge(out_id, in_id);
    }
    else if (this->outs.empty()) {
        throw std::runtime_error("Nothing to pipe from in step " + this->name);
    }
    else if (this->outs.size() > 1) {
        throw std::runtime_error("Too many to pipe from in step " + this->name);
    }
    else if (that.ins.empty()) {
        throw std::runtime_error("Nothing to pipe to in step " + that.name);
    }
    else if (that.ins.size() > 1) {
        throw std::runtime_error("Too many to pipe to in step " + that.name);
    }
}
