#ifndef WORKFLOW_VERTEX_H
#define WORKFLOW_VERTEX_H


#include <string>

namespace workflow {

    class Vertex {
    public:

        const unsigned int identifier;
        const std::string name;

    protected:

        explicit Vertex(std::string name);

    private:

        static unsigned int IDENTIFIER;

    };
}


#endif //WORKFLOW_VERTEX_H
