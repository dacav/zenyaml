#include "datatypes.h"
#include <iostream>

int main()
{
    yayaml::Node name1("hi");
    yayaml::Node name2("there");

    yayaml::Node seq({ name1, name2 });

    std::cerr << std::string(seq[0]) << ' ' << std::string(seq[1]) << std::endl;
}
