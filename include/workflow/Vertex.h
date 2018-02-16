#ifndef WORKFLOW_IVERTEX_H
#define WORKFLOW_IVERTEX_H

#include <string>


namespace workflow {

    class Vertex {
    public:

        virtual ~Vertex() = default;

        bool operator==(const Vertex &that) const;

        unsigned int get_identifier() const;

        const std::string get_name() const;

    protected:

        explicit Vertex(std::string name);

    private:

        unsigned int identifier;

        std::string name;

    };
}


#endif //WORKFLOW_IVERTEX_H
