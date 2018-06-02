#include <stdexcept>
#include "workflow/Vertex.h"


unsigned int IDENTIFIER = 0;

workflow::Vertex::Vertex(const std::string &name) :
    identifier(IDENTIFIER),
    name(name)
{
    IDENTIFIER += 1;
}

bool workflow::Vertex::operator==(const workflow::Vertex &that) const {
    return this->identifier == that.identifier;
}
