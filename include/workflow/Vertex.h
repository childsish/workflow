#ifndef WORKFLOW_IVERTEX_H
#define WORKFLOW_IVERTEX_H

#include <string>


namespace workflow {

    /** @brief A unique vertex in a workflow. */
    class Vertex {
    public:

        const unsigned int identifier;
        const std::string name;

        explicit Vertex(std::string name);
        Vertex(const Vertex &) = delete;
        Vertex &operator=(const Vertex &) = delete;
        virtual ~Vertex() = default;


        /** @brief Compare two vertices. Equivalence is determined by the unique identifier. */
        bool operator==(const Vertex &that) const;

    };
}


#endif //WORKFLOW_IVERTEX_H
