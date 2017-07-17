#pragma once

#include <string>
#include <exception>
#include <memory>
#include <vector>
#include <map>

namespace yayaml
{
    class NodeError : public std::runtime_error
    {
        public:
            NodeError(const std::string& msg) :
                std::runtime_error(msg)
            {}
    };

    class Node
    {
        public:
            enum class NodeType
            {
                SCALAR,
                SEQUENCE,
                MAPPING,
            };

            Node(const std::string& scalar);
            Node(const std::vector<Node>& vector);
            Node(const std::map<std::string, Node>& map);

            operator const std::string&() const;
            const Node& operator[](unsigned idx) const;
            const Node& operator[](const std::string& key) const;

            Node() = default;
            Node(const Node&) = default;

        private:
            struct Storage
            {
                Storage(NodeType type);
                virtual ~Storage() = default;

                NodeType type;
            };

            friend class ScalarStorage;
            friend class SequenceStorage;
            friend class MappingStorage;

            std::shared_ptr<Storage> storage;
    };

} // namespace yayaml
