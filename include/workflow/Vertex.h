#ifndef WORKFLOW_IVERTEX_H
#define WORKFLOW_IVERTEX_H

#include <string>


namespace workflow {

    /** @brief A unique named vertex in a workflow.
     *
     * Vertices are not permitted to be copied.
     */
    class Vertex {
    public:

        /** @brief The unique identifier of the vertex. */
        const unsigned int identifier;

        /** @brief The name of the vertex. */
        const std::string name;

        explicit Vertex(const std::string &name);
        Vertex(const Vertex &) = delete;
        Vertex &operator=(const Vertex &) = delete;
        virtual ~Vertex() = default;

        /** @brief Compare two vertices. Equivalence is determined by the unique identifier. */
        bool operator==(const Vertex &that) const;

    };
}


#endif //WORKFLOW_IVERTEX_H
