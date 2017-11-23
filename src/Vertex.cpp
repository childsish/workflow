/**
 * @author: Liam Childs (liam.h.childs@gmail.com)
 * @brief:
 */

#include "workflow/Vertex.h"


unsigned int workflow::Vertex::IDENTIFIER = 0;

workflow::Vertex::Vertex(std::string name_) :
    identifier(IDENTIFIER),
    name(std::move(name_))
{
    IDENTIFIER += 1;
}
