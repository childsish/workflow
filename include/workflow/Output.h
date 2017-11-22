#ifndef WORKFLOW_OUTPUT_H
#define WORKFLOW_OUTPUT_H

#include <memory>
#include <graph/PartiteGraph.h>
#include "Input.h"
#include "Vertex.h"

namespace workflow {

    class Output;
    class Step;
    class Workflow;

    typedef graph::PartiteGraph<
            unsigned int,
            std::shared_ptr<Step>,
            std::shared_ptr<Input>,
            std::shared_ptr<Output>
    > WorkflowGraph;

    /**
     * A helper class representing output from a step. `Output` can not be created directly and must be obtained via the
     * `Step::outs` member. `Output` can be piped from to an `Input` object.
     * @brief output from a step
     */
    class Output : public Vertex {
    public:

        /**
         * Connect the output of a step to the input of another.
         * @brief connect output to input
         * @param input input to connect to
         */
        void pipe(const std::shared_ptr<Input> &input);

    private:

        friend Workflow;

        Output(std::string name, WorkflowGraph &graph);

        WorkflowGraph &graph;

    };
}

#endif //WORKFLOW_OUTPUT_H
