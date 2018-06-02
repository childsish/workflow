/** @author: Liam Childs (liam.h.childs@gmail.com) */

#include "Connection.h"


unsigned int SYNC_GROUP = 0;

workflow::Connection::Connection(const std::string &name) :
    Vertex::Vertex(name),
    sync_group(SYNC_GROUP++) {}
