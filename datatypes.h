#pragma once

#include <string>
#include <vector>
#include <map>
#include <exception>
#include <functional>

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
            std::function<const std::string*()> getter_scalar;
            //std::function<const Node&(unsigned)> getter_sequence;
            //std::function<const Node&(std::string)> getter_mapping;
    };

} // namespace yayaml
