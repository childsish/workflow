#ifndef WORKFLOW_STEP_H
#define WORKFLOW_STEP_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "Vertex.h"
#include "WorkflowGraph.h"

namespace workflow {

    class Input;
    class Output;
    typedef std::unordered_map<std::string, std::shared_ptr<Input>> InputMap;
    typedef std::unordered_map<std::string, std::shared_ptr<Output>> OutputMap;

    /**
     * @brief step in a workflow
     * A single step in a workflow containing inputs and outputs. `Step` can not be created directly
     * and must be obtained via the `Workflow::add_step` member. `Steps` can be piped directly to
     * each other if they have only one output and/or input.
     */
    class Step : public Vertex {
    public:

        explicit Step(
            const std::string &name,
            const std::vector<std::string> &input_names,
            const std::vector<std::string> &output_names,
            std::shared_ptr<WorkflowGraph> graph
        );

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

        InputMap inputs;
        OutputMap outputs;

        void reject_duplicates(const std::vector<std::string> &names,
                               const std::string &source) const;

        std::vector<std::string> get_duplicates(const std::vector<std::string> &names) const;

    };
}

#endif //WORKFLOW_STEP_H
