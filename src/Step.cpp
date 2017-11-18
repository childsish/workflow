#include "Step.h"

workflow::Step::Step(unsigned int identifier_, const std::string &name_) :
    identifier(identifier_),
    name(name_) {}

void workflow::Step::pipe(const std::shared_ptr<workflow::Step> &that) {
    if (this->outs.size() == 1 && that->ins.size() == 1) {
        this->outs.begin()->second->pipe(that->ins.begin()->second);
    }
    else if (this->outs.empty()) {
        throw std::runtime_error("Nothing to pipe from in step " + this->name);
    }
    else if (this->outs.size() > 1) {
        throw std::runtime_error("Too many outputs to pipe from in step " + this->name);
    }
    else if (that->ins.empty()) {
        throw std::runtime_error("Nothing to pipe to in step " + that->name);
    }
    else if (that->ins.size() > 1) {
        throw std::runtime_error("Too many inputs to pipe to in step " + that->name);
    }
}
