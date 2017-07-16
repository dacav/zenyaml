#pragma once

#include <string>
#include <exception>
#include <memory>
#include <vector>

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
            Node(const std::string& scalar);
            Node(const std::vector<Node>& vector);

            operator const std::string&() const;
            const Node& operator[](unsigned idx) const;

            Node(const Node&) = default;

        private:
            enum class StorageType
            {
                SCALAR,
                SEQUENCE,
            };

            struct Storage
            {
                Storage(StorageType type);
                virtual ~Storage() = default;

                StorageType type;
            };

            friend class ScalarStorage;
            friend class SequenceStorage;

            std::shared_ptr<Storage> storage;
    };

} // namespace yayaml
