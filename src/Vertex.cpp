#include <stdexcept>
#include "workflow/Vertex.h"


unsigned int IDENTIFIER = 0;

workflow::Vertex::Vertex(std::string name_) :
    identifier(IDENTIFIER),
    name(std::move(name_))
{
    IDENTIFIER += 1;
}

bool workflow::Vertex::operator==(const workflow::Vertex &that) const {
    return this->identifier == that.identifier;
}

unsigned int workflow::Vertex::get_identifier() const {
    return this->identifier;
}

const std::string workflow::Vertex::get_name() const {
    return this->name;
}
