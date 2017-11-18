#ifndef WORKFLOW_OUTPUT_H
#define WORKFLOW_OUTPUT_H

#include <memory>
#include <graph/PartiteGraph.h>
#include "Input.h"

namespace workflow {

    class Output;
    class Step;

    typedef graph::PartiteGraph<
            unsigned int,
            std::shared_ptr<Step>,
            std::shared_ptr<Input>,
            std::shared_ptr<Output>
    > WorkflowGraph;

    class Output {
    public:

        const unsigned int identifier;
        const std::string name;

        Output(unsigned int identifier, const std::string &name, WorkflowGraph &graph);

        void pipe(const std::shared_ptr<Input> &input);

    private:

        WorkflowGraph &graph;

    };
}

#endif //WORKFLOW_OUTPUT_H
