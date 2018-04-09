#include "xmlparser.h"
#include "readops.h"
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace rapidxml;


//TODO: Rewrite the loop to use recursion
void startParse(std::vector<settings>& map, std::string fileName)
{
	//Open our filestream
	std::ifstream fileStream(fileName);

	rapidxml::file<> xmlfile(fileStream);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlfile.data());

	//Now we loop through all the nodes
	rapidxml::xml_node<> *node = doc.first_node(doc.first_node()->name());

	parseXML(node);

	//DELETE: placeholder
	std::cout << map[0].price << '\n';
	return;
}


void parseXML(rapidxml::xml_node<> *node)
{
	//Might have to function this up and use recursion....
	while (node != NULL)
	{
		std::string nodeName = node->name();
		std::string nodeValue = node->value();
																	std::cout << "Node name is: " << nodeName << std::endl;
																	std::cout << "Node value is: " << nodeValue << std::endl;

		for (rapidxml::xml_attribute<> *attr = node->first_attribute();attr; attr = attr->next_attribute())
		{
			std::string atrValue = attr->value();
																	std::cout << "Node attribute is: " << atrValue << std::endl;
		}

		if (!node.first_node()->name().compare(NULL))
		{
			rapidxml::xml_node<> *childNode = node.first_node(node.first_node()->name());

			while (childNode != NULL)

		}



   		node = node->next_sibling();
	}

																	std::cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
																	std::cout << "First node has value: " << node ->value() << "\n";

	return;
}