#include "Workflow.h"

enum { step_partition, input_partition, output_partition };

Step Workflow::add_step(const std::string &step_,
                        const std::vector<std::string> ins,
                        const std::vector<std::string> outs)
{
    Step step{this->identifier, step_, *this};

    this->graph.add_vertex<step_partition>(this->identifier, {this->identifier, step_});
    this->identifier += 1;

    for (auto in_ : ins) {
        Input input{this->identifier, in_};
        step.ins[in_] = input;
        this->graph.add_vertex<input_partition>(this->identifier, input);
        this->identifier += 1;
    }

    for (auto out : outs) {
        Output output{this->identifier, out};
        step.outs[out] = output;
        this->graph.add_vertex<output_partition>(this->identifier, output);
        this->identifier += 1;
    }

    return step;
}
