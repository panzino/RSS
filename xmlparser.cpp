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

																							std::cout << "Name of my first node is: " << doc.first_node()->name() << "\n";

	parseXML(node);

	//DELETE: placeholder
	std::cout << map[0].price << '\n';
	return;
}


void parseXML(rapidxml::xml_node<> *node)
{
	//Keep recursing while the node is present
	while (*node->name() != 0x0)
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


		//Recurse children
		parseXML(node->first_node(node->first_node()->name()));
		
		//Recurse siblings
		parseXML(node->next_sibling());

		return;
	}

											
																	std::cout << "Reached Null Node!" << "\n";

	return;
}