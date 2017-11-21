#include "Step.h"

void workflow::Step::pipe(const std::shared_ptr<workflow::Step> &target) {
    if (this->_outs.size() == 1 && target->_ins.size() == 1) {
        this->_outs.begin()->second->pipe(target->_ins.begin()->second);
    }
    else if (this->_outs.empty()) {
        throw std::runtime_error("Nothing to pipe from in step " + this->name);
    }
    else if (this->_outs.size() > 1) {
        throw std::runtime_error("Too many outputs to pipe from in step " + this->name);
    }
    else if (target->_ins.empty()) {
        throw std::runtime_error("Nothing to pipe to in step " + target->name);
    }
    else if (target->_ins.size() > 1) {
        throw std::runtime_error("Too many inputs to pipe to in step " + target->name);
    }
}

const std::shared_ptr<workflow::Input> workflow::Step::ins(const std::string &name) const {
    return this->_ins.at(name);
}

const std::shared_ptr<workflow::Output> workflow::Step::outs(const std::string &name) const {
    return this->_outs.at(name);
}

workflow::Step::Step(unsigned int identifier_, const std::string &name_) :
        identifier(identifier_),
        name(name_) {}
