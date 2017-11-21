#ifndef WORKFLOW_STEP_H
#define WORKFLOW_STEP_H

#include <memory>
#include "Input.h"
#include "Output.h"

namespace workflow {

    class Workflow;

    /**
     * A single step in a workflow containing inputs and outputs. `Step` can not be created directly and must be
     * obtained via the `Workflow::add_step` member. `Steps` can be piped directly to each other if they have only one
     * output and/or input.
     * @brief step in a workflow
     */
    class Step {
    public:

        const unsigned int identifier;
        const std::string name;

        std::unordered_map<std::string, std::shared_ptr<Input>> ins;
        std::unordered_map<std::string, std::shared_ptr<Output>> outs;

        /**
         * Pipe the single output of this step to the single input of another. If there are multiple outputs or inputs,
         * then an exception will be thrown.
         * @brief connect output to another steps' input
         * @param target step with single input
         */
        void pipe(const std::shared_ptr<Step> &target);

    private:

        friend Workflow;

        Step(unsigned int identifier, const std::string &name);

    };
}

#endif //WORKFLOW_STEP_H
