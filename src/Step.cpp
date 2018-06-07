#include <iterator>
#include "Input.h"
#include "Output.h"

#include "Step.h"


workflow::Step::Step(
    const std::string &name,
    const std::vector<std::string> &input_names,
    const std::vector<std::string> &output_names,
    std::shared_ptr<workflow::WorkflowGraph> graph
) :
    workflow::Vertex(name),
    priority(0),
    sync_group(0),
    inputs(std::make_shared<ConnectionMap>()),
    outputs(std::make_shared<ConnectionMap>())
{
    this->reject_duplicates(input_names, "input");
    this->reject_duplicates(output_names, "output");

    auto &tmp = *this->inputs;
    for (auto input_name : input_names) {
        this->inputs->emplace(input_name, std::make_shared<Input>(input_name));
    }
    for (auto output_name : output_names) {
        this->outputs->emplace(output_name, std::make_shared<Output>(output_name, graph));
    }
}

void workflow::Step::pipe(const std::shared_ptr<workflow::Step> &target) {
    if (this->outputs->size() == 1 && target->inputs->size() == 1) {
        auto output = std::static_pointer_cast<Output>(this->outputs->begin()->second);
        auto input = std::static_pointer_cast<Input>(target->inputs->begin()->second);
        output->pipe(*input);
    }
    else if (this->outputs->empty()) {
        throw std::runtime_error("Nothing to pipe from in step " + this->name);
    }
    else if (this->outputs->size() > 1) {
        throw std::runtime_error("Too many outputs to pipe from in step " + this->name);
    }
    else if (target->inputs->empty()) {
        throw std::runtime_error("Nothing to pipe to in step " + target->name);
    }
    else if (target->inputs->size() > 1) {
        throw std::runtime_error("Too many inputs to pipe to in step " + target->name);
    }
}

unsigned int workflow::Step::get_priority() const {
    return this->priority;
}

void workflow::Step::set_priority(unsigned int priority) {
    this->priority = priority;
}


void workflow::Step::synchronise_inputs(const std::vector<std::string> &input_names) {
    for (const auto &name : input_names) {
        this->inputs->at(name)->sync_group = this->sync_group;
    }
    this->sync_group += 1;
}

void workflow::Step::synchronise_outputs(const std::vector<std::string> &output_names) {
    for (const auto &name : output_names) {
        this->outputs->at(name)->sync_group = this->sync_group;
    }
    this->sync_group += 1;
}

bool workflow::Step::is_synchronous() const {
    return this->sync_group > 0;
}

std::shared_ptr<workflow::ConnectionMap> workflow::Step::get_inputs() const {
    return this->inputs;
}

std::shared_ptr<workflow::ConnectionMap> workflow::Step::get_outputs() const {
    return this->outputs;
}

void workflow::Step::reject_duplicates(
    const std::vector<std::string> &names,
    const std::string &source
) const {
    auto duplicated = this->get_duplicates(names);
    if (!duplicated.empty()) {
        std::stringstream buffer;
        buffer << "Duplicate " << source << " names: ";
        std::copy(duplicated.begin(), duplicated.end(), std::ostream_iterator<std::string>(buffer, ", "));
        buffer.seekp(-2, std::ios::end);
        buffer << ".";
        throw std::runtime_error(buffer.str().erase(buffer.str().size() - 1));
    }
}

std::vector<std::string> workflow::Step::get_duplicates(const std::vector<std::string> &names) const {
    std::vector<std::string> duplicates;
    std::unordered_set<std::string> visited;
    for (const auto &name : names) {
        if (visited.find(name) != visited.end()) {
            duplicates.push_back(name);
        }
        visited.insert(name);
    }
    return duplicates;
}
