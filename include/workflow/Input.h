#ifndef WORKFLOW_INPUT_H
#define WORKFLOW_INPUT_H


#include <string>
#include "Vertex.h"

namespace workflow {

    class Workflow;

    /**
     * @brief input to a step
     * A helper class representing the input to a step. `Input` can be piped to from an `Output`
     * object.
     */
    class Input : public Vertex {
    public:

        explicit Input(std::string name);

    };
}


#endif //WORKFLOW_INPUT_H
