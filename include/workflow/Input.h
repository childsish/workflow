#ifndef WORKFLOW_INPUT_H
#define WORKFLOW_INPUT_H

#include <string>
#include "Connection.h"


namespace workflow {

    class Workflow;

    /** @brief Named input to a step.
     *
     * A helper class representing the input to a step. `Input` can be piped to from an `Output`
     * object.
     */
    class Input : public Connection {
    public:

        explicit Input(const std::string &name);

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
    struct hash<workflow::Input> {
        size_t operator()(const workflow::Input &input) const {
            return hash<unsigned int>()(input.identifier);
        }
    };
}


#endif //WORKFLOW_INPUT_H
