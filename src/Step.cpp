#include <iterator>
#include "Input.h"
#include "Output.h"

#include "Step.h"


workflow::Step::Step(
    const std::string &name,
    const std::vector<std::string> &input_names,
    const std::vector<std::string> &output_names,
    std::shared_ptr<WorkflowGraph> graph
) :
    workflow::Vertex(std::move(name))
{
    this->reject_duplicates(input_names, "input");
    this->reject_duplicates(output_names, "output");

    for (const auto &input_name : input_names) {
        this->inputs[input_name] = std::make_shared<Input>(input_name);
    }
    for (const auto &output_name : output_names) {
        this->outputs[output_name] = std::make_shared<Output>(output_name, graph);
    }
}

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

const std::shared_ptr<workflow::Input> workflow::Step::get_input(const std::string &name) const {
    return this->inputs.at(name);
}

const workflow::OutputMap &workflow::Step::get_outputs() const {
    return this->outputs;
}

const std::shared_ptr<workflow::Output> workflow::Step::get_output(const std::string &name) const {
    return this->outputs.at(name);
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
