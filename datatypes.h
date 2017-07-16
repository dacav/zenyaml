#pragma once

#include <string>
#include <vector>
#include <map>
#include <exception>
#include <functional>
#include <memory>

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
            //Node(const std::vector<Node>& vector);
            //Node(const std::map<std::string, Node>& map);

            //Node(const Node&);

            //const Node& operator[](unsigned idx) const;
            //const Node& operator[](const std::string& key) const;
            operator const std::string&() const;

        private:
            enum class StorageType
            {
                SCALAR
            };

            struct Storage
            {
                Storage(StorageType type);
                virtual ~Storage() = default;

                StorageType type;
            };

            template <typename T>
            struct StorageT : public Storage
            {
                StorageT(StorageType type)
                    : Storage(type)
                {
                }
                virtual T& get() = 0;
            };

            friend class ScalarStorage;

            std::unique_ptr<Storage> storage;
    };

} // namespace yayaml
