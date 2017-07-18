#include "datatypes.h" 
#include <iostream> 
#include <cassert>

namespace zenyaml
{
    Node::Storage::Storage(NodeType t)
        : type(t)
    {
    }


    struct ScalarStorage : public Node::Storage
    {
        std::string string;

        ScalarStorage(const std::string& s)
            : Node::Storage(Node::NodeType::SCALAR)
            , string(s)
        { }
    };

    struct SequenceStorage : public Node::Storage
    {
        std::vector<Node> sequence;

        SequenceStorage(const std::vector<Node>& v)
            : Node::Storage(Node::NodeType::SEQUENCE)
            , sequence(v)
        { }

    };

    struct MappingStorage : public Node::Storage
    {
        std::map<std::string, Node> mapping;

        MappingStorage(const std::map<std::string, Node>& m)
            : Node::Storage(Node::NodeType::MAPPING)
            , mapping(m)
        { }
    };


    Node::Node(const std::string& scalar)
        : storage(std::make_shared<ScalarStorage>(scalar))
    {
    }

    Node::Node(const std::vector<Node>& vector)
        : storage(std::make_shared<SequenceStorage>(vector))
    {
    }

    Node::Node(const std::map<std::string, Node>& map)
        : storage(std::make_shared<MappingStorage>(map))
    {
    }

    Node::operator const std::string&() const
    {
        if (storage->type != Node::NodeType::SCALAR) {
            throw NodeError("Not a scalar");
        }

        ScalarStorage& s = dynamic_cast<ScalarStorage&>(*storage.get());
        return s.string;
    }

    const Node& Node::operator[](unsigned idx) const
    {
        if (storage->type != Node::NodeType::SEQUENCE) {
            throw NodeError("Not a sequence");
        }
        SequenceStorage& s = dynamic_cast<SequenceStorage&>(*storage.get());
        return s.sequence[idx];
    }

    const Node& Node::operator[](const std::string& key) const
    {
        if (storage->type != Node::NodeType::MAPPING) {
            throw NodeError("Not a mapping");
        }
        MappingStorage& s = dynamic_cast<MappingStorage&>(*storage.get());
        return s.mapping[key];
    }

} // namespace zenyaml
