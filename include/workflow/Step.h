#ifndef WORKFLOW_STEP_H
#define WORKFLOW_STEP_H

#include "Workflow.h"

class Workflow;

class Step {
public:

    Step(unsigned int identifier, const std::string &name, graph::PartiteGraph<unsigned int, Step, Input, Output> graph);

    const std::string name;
    std::unordered_map<std::string, Input> ins;
    std::unordered_map<std::string, Output> outs;

    void pipe(Step &that);

private:

    unsigned int identifier;

    graph::PartiteGraph<unsigned int, Step, Input, Output> &graph;

};

#endif //WORKFLOW_STEP_H
