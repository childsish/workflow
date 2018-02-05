#include "Step.h"

void workflow::Step::pipe(const std::shared_ptr<workflow::Step> &target) {
    if (this->outputs.size() == 1 && target->inputs.size() == 1) {
        this->outputs.begin()->second->pipe(target->inputs.begin()->second);
    }
    else if (this->outputs.empty()) {
        throw std::runtime_error("Nothing to pipe from in step " + this->name);
    }
    else if (this->outputs.size() > 1) {
        throw std::runtime_error("Too many outputs to pipe from in step " + this->name);
    }
    else if (target->inputs.empty()) {
        throw std::runtime_error("Nothing to pipe to in step " + target->name);
    }
    else if (target->inputs.size() > 1) {
        throw std::runtime_error("Too many inputs to pipe to in step " + target->name);
    }
}

const workflow::InputMap &workflow::Step::get_inputs() const {
    return this->inputs;
}

const std::shared_ptr<workflow::Input> workflow::Step::get_inputs(const std::string &name) const {
    return this->inputs.at(name);
}

const workflow::OutputMap &workflow::Step::get_outputs() const {
    return this->outputs;
}

const std::shared_ptr<workflow::Output> workflow::Step::get_outputs(const std::string &name) const {
    return this->outputs.at(name);
}

workflow::Step::Step(std::string name) :
        workflow::Vertex(std::move(name)) {}
