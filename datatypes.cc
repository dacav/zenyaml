#include "datatypes.h" 
#include <iostream> 
#include <cassert>

namespace yayaml
{
    struct ScalarStorage : public Node::Storage
    {
        std::string string;

        ScalarStorage(const std::string& s)
            : Node::Storage(Node::StorageType::SCALAR)
            , string(s)
        { }
    };

    Node::Storage::Storage(StorageType t)
        : type(t)
    {
    }

    Node::Node(const std::string& scalar)
        : storage(new ScalarStorage(scalar))
    {
    }

    Node::operator const std::string&() const
    {
        if (storage->type != Node::StorageType::SCALAR) {
            throw NodeError("Not a scalar");
        }

        ScalarStorage& s = dynamic_cast<ScalarStorage&>(*storage.get());
        return s.string;
    }

} // namespace yayaml
