#include <zenyaml/parser.h>

#include <cerrno>
#include <cstring>
#include <cassert>

namespace
{
    using namespace zenyaml;

    struct EventWrapper
    {
        EventWrapper(yaml_parser_t& parser)
        {
            if (!yaml_parser_parse(&parser, &event)) {
                throw ParserError("Bad document format. I've no idea why.");
            }
        }

        ~EventWrapper()
        {
            yaml_event_delete(&event);
        }

        yaml_event_t event;
    };

    class SequenceScanner
    {
        SequenceScanner(yaml_parser_t& p)
            : parser(p)
        {
        }

        yaml_parser_t& parser;
    };

}

namespace zenyaml
{

    Parser::Parser(const std::string& filepath)
        : infile(fopen(filepath.c_str(), "r"), fclose)
        , more(false)
    {
        yaml_parser_initialize(&parser);
        if (infile.get() == nullptr) {
            throw ParserError(
                std::string("Unable to open file: ")
                + strerror(errno)
            );
        }
        yaml_parser_set_encoding(&parser, YAML_ANY_ENCODING);
        yaml_parser_set_input_file(&parser, infile.get());

        stream_begin();
        if (document_next()) {
            more = true;
        }
    }

    Parser::~Parser()
    {
        yaml_parser_delete(&parser);
    }

    void Parser::stream_begin()
    {
        EventWrapper ewr(parser);

        if (ewr.event.type != YAML_STREAM_START_EVENT) {
            throw ParserError(
                "Unexpected YAML status in stream_begin: "
                + std::to_string(ewr.event.type)
            );
        }
    }

    bool Parser::document_next()
    {
        EventWrapper ewr(parser);
        switch (ewr.event.type)
        {
            case YAML_DOCUMENT_START_EVENT:
                return true;
                break;
            case YAML_STREAM_END_EVENT:
                return false;
                break;
            default:
                throw ParserError(
                    "Unexpected YAML status in document_next: "
                    + std::to_string(ewr.event.type)
                );
        }
    }


    bool Parser::has_document() const
    {
        return more;
    }

    void Parser::scalar_parse(yaml_event_t& event)
    {
        stack.emplace((const char*)(event.data.scalar.value));
    }

    void Parser::sequence_parse(yaml_event_t& event)
    {
        stack.emplace(Node::NodeType::SEQUENCE);
        Node& node = stack.top();

        bool sequence_done = false;
        while (!sequence_done) {
            EventWrapper ewr(parser);

            switch (ewr.event.type) {
                case YAML_SEQUENCE_END_EVENT:
                    sequence_done = true;
                    break;

                case YAML_SCALAR_EVENT:
                    scalar_parse(ewr.event);
                    break;

                case YAML_SEQUENCE_START_EVENT:
                    sequence_parse(ewr.event);
                    break;

                case YAML_MAPPING_START_EVENT:
                    mapping_parse(ewr.event);
                    break;

                default:
                    throw ParserError(
                        "Unexpected YAML status in document_next: "
                        + std::to_string(ewr.event.type)
                    );
            }

            if (!sequence_done) {
                node.get_sequence().push_back(stack.top());
                stack.pop();
            }
        }
    }

    void Parser::mapping_parse(yaml_event_t& event)
    {
        stack.emplace(Node::NodeType::MAPPING);
        Node& node = stack.top();

        bool mapping_done = false;
        bool got_key = false;
        bool got_value = false;
        std::string key;

        while (!mapping_done) {
            EventWrapper ewr(parser);

            switch (ewr.event.type) {
                case YAML_MAPPING_END_EVENT:
                    mapping_done = true;
                    break;

                case YAML_SCALAR_EVENT:
                    if (!got_key) {
                        got_key = true;
                        key = (const char*)ewr.event.data.scalar.value;
                    }
                    else {
                        got_value = true;
                        scalar_parse(ewr.event);
                    }
                    break;

                case YAML_SEQUENCE_START_EVENT:
                    if (!got_key) {
                        throw ParserError("Got sequence start, but no key");
                    }
                    got_value = true;
                    sequence_parse(ewr.event);
                    break;

                case YAML_MAPPING_START_EVENT:
                    if (!got_key) {
                        throw ParserError("Got sequence start, but no key");
                    }
                    got_value = true;
                    mapping_parse(ewr.event);
                    break;

                default:
                    throw ParserError(
                        "Unexpected YAML status in document_next: "
                        + std::to_string(ewr.event.type)
                    );
            }

            if (got_value && !got_key) { // read !(got_value => got_key)
                throw ParserError("I have a value without a key?");
            }

            if (!mapping_done && got_key && got_value) {
                got_key = got_value = false;
                node.get_mapping()[key] = stack.top();
                stack.pop();
            }
        }
    }

    Node Parser::get_document()
    {
        if (!more) {
            throw ParserError("No more documents");
        }

        bool document_ready = 0;
        while (!document_ready) {
            EventWrapper ewr(parser);

            int unexpid =0;
            switch (ewr.event.type) {
                case YAML_DOCUMENT_END_EVENT:
                    if (stack.size() > 1) {
                        throw ParserError(
                            "Unexpected truncation: stack size is "
                            + std::to_string(stack.size())
                        );
                    }
                    document_ready = true;
                    break;

                case YAML_ALIAS_EVENT:
                    throw ParserError("How do I handle alias?");
                    break;

                case YAML_SCALAR_EVENT:
                    scalar_parse(ewr.event);
                    break;

                case YAML_SEQUENCE_START_EVENT:
                    sequence_parse(ewr.event);
                    break;

                case YAML_MAPPING_START_EVENT:
                    mapping_parse(ewr.event);
                    break;

                case YAML_STREAM_END_EVENT:
                case YAML_NO_EVENT:
                case YAML_STREAM_START_EVENT:
                case YAML_DOCUMENT_START_EVENT:
                case YAML_SEQUENCE_END_EVENT:
                case YAML_MAPPING_END_EVENT:
                default:
                    throw ParserError(
                        "Unexpected YAML status in get_document: "
                        + std::to_string(ewr.event.type)
                    );
            }
        }

        assert(stack.size() == 1);
        Node root = stack.top();
        stack.pop();
        more = document_next();
        return root;
    }

} // namespace zenyaml
