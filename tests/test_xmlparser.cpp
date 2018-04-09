#include "xmlparser.h"
#include <iostream>
#include <string>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>

using namespace rapidxml;

short simpleXML(int& count)
{
    count += 1;

    rapidxml::file<> xmlfile("/responses/file[0]");
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlfile.data());

    std::string first_node = doc.first_node()->name();
    std::cout << "Name of my first node is: " << first_node << "\n";
        
    if (first_node.compare("Tove"))
    {
        std::cerr << first_node << " != Tove" << std::endl;
        return 0;
    }



    return 1;
}




