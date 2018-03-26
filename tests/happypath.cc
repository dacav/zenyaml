#include <zenyaml/zenyaml.h>

#include <cassert>
#include <iostream>

using namespace zenyaml;

int main()
{
    char buffer[] =
        "scalar: 1024\n"
        "list:\n"
        "  - foo\n"
        "  - bar\n"
        "map:\n"
        "  key1: value1\n"
        "  key2:\n"
        "   - value2\n"
        "   - value3\n"
        "  key3:\n"
        "    key4: value5\n"
        "    key6: value7\n"
    ;

    FILE* infile = fmemopen(buffer, sizeof(buffer) - 1, "r");

    Parser parser(infile);
    Node root = parser.get_document();

    std::cerr << root << std::endl;
}
