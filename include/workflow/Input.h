#ifndef WORKFLOW_INPUT_H
#define WORKFLOW_INPUT_H

#include <string>

namespace workflow {

    class Input {
    public:

        const unsigned int identifier;
        const std::string name;

        Input(unsigned int identifier, const std::string &name);
    };
}

#endif //WORKFLOW_INPUT_H
