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

        ScalarStorage(const std::string& s = "")
            : Node::Storage(Node::NodeType::SCALAR)
            , string(s)
        { }
    };

    struct SequenceStorage : public Node::Storage
    {
        std::vector<Node> sequence;

        SequenceStorage(const std::vector<Node>& v = {})
            : Node::Storage(Node::NodeType::SEQUENCE)
            , sequence(v)
        { }

    };

    struct MappingStorage : public Node::Storage
    {
        std::map<std::string, Node> mapping;

        MappingStorage(const std::map<std::string, Node>& m = {})
            : Node::Storage(Node::NodeType::MAPPING)
            , mapping(m)
        { }
    };

    Node::Node(NodeType t)
        : storage(nullptr)
    {
        switch (t) {
            case NodeType::SCALAR:
                storage = std::make_shared<ScalarStorage>();
                break;
            case NodeType::SEQUENCE:
                storage = std::make_shared<SequenceStorage>();
                break;
            case NodeType::MAPPING:
                storage = std::make_shared<MappingStorage>();
                break;
            default:
                assert(false);
        }
    }

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

    std::string& Node::get_scalar()
    {
        if (storage->type != Node::NodeType::SCALAR) {
            throw NodeError("Not a scalar");
        }
        return dynamic_cast<ScalarStorage&>(*storage.get()).string;
    }

    std::vector<Node>& Node::get_sequence()
    {
        if (storage->type != Node::NodeType::SEQUENCE) {
            throw NodeError("Not a sequence");
        }
        return dynamic_cast<SequenceStorage&>(*storage.get()).sequence;
    }

    std::map<std::string, Node>& Node::get_mapping()
    {
        if (storage->type != Node::NodeType::MAPPING) {
            throw NodeError("Not a mapping");
        }
        return dynamic_cast<MappingStorage&>(*storage.get()).mapping;
    }

} // namespace zenyaml
