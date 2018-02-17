#ifndef WORKFLOW_OUTPUT_H
#define WORKFLOW_OUTPUT_H

#include <memory>
#include "Vertex.h"
#include "WorkflowGraph.h"

namespace workflow {

    class Input;

    /**
     * A helper class representing output from a step. `Output` can not be created directly and must be obtained via the
     * `Step::outs` member. `Output` can be piped from to an `Input` object.
     * @brief output from a step
     */
    class Output : public Vertex {
    public:

        Output(std::string name, std::shared_ptr<WorkflowGraph> graph);

        /**
         * Connect the output of a step to the input of another.
         * @brief connect output to input
         * @param input input to connect to
         */
        void pipe(const std::shared_ptr<Input> &input);

    private:

        std::shared_ptr<WorkflowGraph> graph;

    };
}

#endif //WORKFLOW_OUTPUT_H
