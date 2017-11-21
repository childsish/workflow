#ifndef WORKFLOW_INPUT_H
#define WORKFLOW_INPUT_H

#include <string>

namespace workflow {

    class Workflow;

    /**
     * A helper class representing the input to a step. `Input` can not be created directly and must be obtained via the
     * `Step::ins` member. `Input` can be piped to from an `Output` object.
     * @brief input to a step
     */
    class Input {
    public:

        const unsigned int identifier;
        const std::string name;

        Input(const Input &) = delete;
        Input &operator=(const Input &) = delete;

    private:

        friend Workflow;

        Input(unsigned int identifier, const std::string &name);

    };
}

#endif //WORKFLOW_INPUT_H
