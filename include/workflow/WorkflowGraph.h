#ifndef WORKFLOW_WORKFLOWGRAPH_H
#define WORKFLOW_WORKFLOWGRAPH_H

#include <graph/PartiteGraph.h>


namespace workflow {

    class Input;
    class Output;
    class Step;

    typedef graph::PartiteGraph<
        unsigned int,
        std::shared_ptr<Step>,
        std::shared_ptr<Input>,
        std::shared_ptr<Output>
    > WorkflowGraph;
}

#endif //WORKFLOW_WORKFLOWGRAPH_H
