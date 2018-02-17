#ifndef WORKFLOW_OUTPUT_H
#define WORKFLOW_OUTPUT_H

#include <memory>
#include "Vertex.h"
#include "WorkflowGraph.h"


namespace workflow {

    class Input;

    /** @brief Named output from a step.
     *
     * A helper class representing output from a step. `Output` can be piped to an `Input` object.
     */
    class Output : public Vertex {
    public:

        Output(std::string name, std::shared_ptr<WorkflowGraph> graph);

        /** @brief Connect the output of a step to the input of another. */
        void pipe(const std::shared_ptr<Input> &input);

    private:

        std::shared_ptr<WorkflowGraph> graph;

    };
}

#endif //WORKFLOW_OUTPUT_H
