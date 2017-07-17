#include "datatypes.h"
#include <iostream>

int main()
{
    zenyaml::Node name1("hi");
    zenyaml::Node name2("there");
    zenyaml::Node seq(std::vector<zenyaml::Node>({ name1, name2 }));
    zenyaml::Node map(std::map<std::string, zenyaml::Node>({{"foo", name1}, {"bar", seq}}));

    std::cerr << std::string(seq[0]) << ' ' << std::string(seq[1]) << std::endl;
    std::cerr << std::string(map["foo"]) << ' ' << std::string(map["bar"][1]) << std::endl;
}
