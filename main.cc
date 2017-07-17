#include "datatypes.h"
#include <iostream>

int main()
{
    yayaml::Node name1("hi");
    yayaml::Node name2("there");
    yayaml::Node seq(std::vector<yayaml::Node>({ name1, name2 }));
    yayaml::Node map(std::map<std::string, yayaml::Node>({{"foo", name1}, {"bar", seq}}));

    std::cerr << std::string(seq[0]) << ' ' << std::string(seq[1]) << std::endl;
    std::cerr << std::string(map["foo"]) << ' ' << std::string(map["bar"][1]) << std::endl;
}
