#ifndef WORKFLOW_STEP_H
#define WORKFLOW_STEP_H

#include <memory>
#include "Input.h"
#include "Output.h"

namespace workflow {

    class Step {
    public:

        const unsigned int identifier;
        const std::string name;

        Step(unsigned int identifier, const std::string &name);

        std::unordered_map<std::string, std::shared_ptr<Input>> ins;
        std::unordered_map<std::string, std::shared_ptr<Output>> outs;

        void pipe(const std::shared_ptr<Step> &that);

    };
}

#endif //WORKFLOW_STEP_H
