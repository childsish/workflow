#ifndef WORKFLOW_STEP_H
#define WORKFLOW_STEP_H

#include <memory>
#include "Input.h"
#include "Output.h"
#include "Vertex.h"

namespace workflow {

    class Workflow;
    typedef std::unordered_map<std::string, std::shared_ptr<Input>> InputMap;
    typedef std::unordered_map<std::string, std::shared_ptr<Output>> OutputMap;

    /**
     * A single step in a workflow containing inputs and outputs. `Step` can not be created directly and must be
     * obtained via the `Workflow::add_step` member. `Steps` can be piped directly to each other if they have only one
     * output and/or input.
     * @brief step in a workflow
     */
    class Step : public Vertex {
    public:

        /**
         * Pipe the single output of this step to the single input of another. If there are multiple outputs or inputs,
         * then an exception will be thrown.
         * @brief connect output to another steps' input
         * @param target step with single input
         */
        void pipe(const std::shared_ptr<Step> &target);

        /**
         * Getters for the inputs and outputs connected to the step
         * @brief get named inputs and outputs
         * @param name name of the input/output to get
         * @return input/output object
         */
        const InputMap &get_inputs() const;
        const std::shared_ptr<Input> get_inputs(const std::string &name) const;
        const OutputMap &get_outputs() const;
        const std::shared_ptr<Output> get_outputs(const std::string &name) const;

    private:

        friend Workflow;

        InputMap inputs;
        OutputMap outputs;

        explicit Step(std::string name);

    };
}

#endif //WORKFLOW_STEP_H
