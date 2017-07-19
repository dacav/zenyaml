#include "datatypes.h"
#include "parser.h"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Needs input file" << std::endl;
        return 1;
    }

    zenyaml::Parser parser(argv[1]);
    while (parser.has_document()) {
        zenyaml::Node node = parser.get_document();
        std::cerr << &node << std::endl;
    }

    return 0;
}
