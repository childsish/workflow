/** @author: Liam Childs (liam.h.childs@gmail.com) */

#ifndef MIMO_CONNECTION_H
#define MIMO_CONNECTION_H

#include "Vertex.h"


namespace workflow {
    class Connection : public Vertex {
    public:

        unsigned int sync_group;

        explicit Connection(const std::string &name);

        virtual ~Connection() = default;

    };
}


#endif //MIMO_CONNECTION_H
