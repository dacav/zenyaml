#pragma once

#include <string>
#include <exception>
#include <memory>
#include <vector>
#include <map>

namespace zenyaml
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

            Node(NodeType);
            Node(const std::string& scalar);
            Node(const std::vector<Node>& vector);
            Node(const std::map<std::string, Node>& map);

            std::map<std::string, Node>& get_mapping() const;
            std::vector<Node>& get_sequence() const;
            std::string& get_scalar() const;

            const Node& operator[](unsigned idx) const;
            const Node& operator[](const std::string& key) const;
            const Node& operator[](const char* key) const;
            operator const std::string&() const;

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

} // namespace zenyaml
