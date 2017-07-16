#include "datatypes.h" 
#include <iostream> 
#include <cassert>
#include <vector>
#include <map>

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

    struct SequenceStorage : public Node::Storage
    {
        std::vector<Node> sequence;

        SequenceStorage(const std::vector<Node>& v)
            : Node::Storage(Node::StorageType::SEQUENCE)
            , sequence(v)
        { }

    };

    Node::Storage::Storage(StorageType t)
        : type(t)
    {
    }

    Node::Node(const std::string& scalar)
        : storage(std::make_shared<ScalarStorage>(scalar))
    {
    }

    Node::Node(const std::vector<Node>& vector)
        : storage(std::make_shared<SequenceStorage>(vector))
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

    const Node& Node::operator[](unsigned idx) const
    {
        if (storage->type != Node::StorageType::SEQUENCE) {
            throw NodeError("Not a sequence");
        }
        SequenceStorage& s = dynamic_cast<SequenceStorage&>(*storage.get());
        return s.sequence[idx];
    }

} // namespace yayaml
