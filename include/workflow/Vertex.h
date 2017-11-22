#ifndef WORKFLOW_VERTEX_H
#define WORKFLOW_VERTEX_H


#include <string>

namespace workflow {

    class Vertex {
    public:

        const unsigned int identifier;
        const std::string name;

    protected:

        explicit Vertex(std::string name_) :
                identifier(IDENTIFIER),
                name(std::move(name_)) {
            IDENTIFIER += 1;
        }

    private:

        static unsigned int IDENTIFIER;

    };
}

unsigned int workflow::Vertex::IDENTIFIER = 0;

#endif //WORKFLOW_VERTEX_H
