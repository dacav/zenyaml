#include "datatypes.h"

#include <iostream> 

namespace yayaml
{
    Node::Node(const std::string& scalar)
        : getter_scalar([this, &scalar](){ return &scalar; })
    {
    }

    Node::operator const std::string&() const
    {
        if (!getter_scalar) {
            throw NodeError("Not a scalar");
        }
        return *(getter_scalar());
    }

} // namespace yayaml
