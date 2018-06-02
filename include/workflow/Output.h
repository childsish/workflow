#ifndef WORKFLOW_OUTPUT_H
#define WORKFLOW_OUTPUT_H

#include <memory>
#include "Connection.h"
#include "WorkflowGraph.h"


namespace workflow {

    class Input;

    /** @brief Named output from a step.
     *
     * A helper class representing output from a step. `Output` can be piped to an `Input` object.
     */
    class Output : public Connection {
    public:

        Output(const std::string &name, std::shared_ptr<WorkflowGraph> graph);

        /** @brief Connect the output of a step to the input of another. */
        void pipe(const Input &input);

    private:

        std::shared_ptr<WorkflowGraph> graph;

    };
}

namespace std {

    /** @brief Hash object for hashing inputs.
     *
     * For example:
     * @code
     * std::unsorted_map<std::shared_ptr<Input>, std::shared_ptr<Queue>> inputs;
     * Workflow workflow;
     * std::shared_ptr<Step> step = workflow.add_step("step_name", {"input"}, {"output"});
     * jobs[step.get_inputs("input")] = std::make_shared<Queue>();
     * @endcode
     */
    template <>
    struct hash<workflow::Output> {
        size_t operator()(const workflow::Output &output) const {
            return hash<unsigned int>()(output.identifier);
        }
    };
}


#endif //WORKFLOW_OUTPUT_H
