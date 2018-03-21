#pragma once

#include <yaml.h>

#include <string>
#include <stack>
#include <cstdio>
#include <stdexcept>

#include "datatypes.h"

namespace zenyaml
{
    struct ParserError : public std::runtime_error
    {
        ParserError(const std::string& msg) : std::runtime_error(msg) {}
    };

    class Parser
    {
        public:
            Parser(const std::string& path);
            ~Parser();

            bool has_document() const;
            Node get_document();

        private:
            yaml_parser_t parser;
            std::unique_ptr<FILE, int(*)(FILE*)> infile;

            void stream_begin();
            void document_scan();
            bool document_next();

            void scalar_parse(yaml_event_t&);
            void sequence_parse(yaml_event_t&);
            void mapping_parse(yaml_event_t&);

            std::stack<Node> stack;
            bool more;
    };

} // namespace zenyaml
