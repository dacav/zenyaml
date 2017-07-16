#include "datatypes.h"
#include <iostream>

int main()
{
    std::string astr = "hi";
    std::cerr << "new String " << &astr << std::endl;
    yayaml::Node n(astr);

    const std::string& lol = n;

    std::cerr << &lol << std::endl;
    std::cerr << lol << std::endl;
}
