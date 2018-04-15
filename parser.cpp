#include "parser.h"
#include "readops.h"
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

using namespace rapidxml;


//TODO: Rewrite the loop to use recursion
void parse::startParse(std::vector<settings>& map, std::string fileName)
{
	//Set price global variable
	std::cout << map[0].price << std::endl;

	price = 80;
	betterPrice = false;

	//Open our filestream
	std::ifstream fileStream(fileName);

	rapidxml::file<> xmlfile(fileStream);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlfile.data());

	//Now we loop through all the nodes
	rapidxml::xml_node<> *node = doc.first_node(doc.first_node()->name());

																							std::cout << "Name of my first node is: " << doc.first_node()->name() << "\n";

	parseXML(node);

	if (betterPrice == true)
		std::cout << "A better price has been found!" << std::endl;
	else
		std::cout << "No better price" << std::endl;


	return;
}


void parse::parseXML(rapidxml::xml_node<> *node)
{
	if (betterPrice == true)
		return;

	//Keep recursing while the node is present
	while (*node->name() != 0x0)
	{
		std::string nodeValue = node->value();
		regexPriceFind(nodeValue);

		for (rapidxml::xml_attribute<> *attr = node->first_attribute();attr; attr = attr->next_attribute())
		{
			std::string atrValue = attr->value();
			regexPriceFind(atrValue);
																	std::cout << "Node attribute is: " << atrValue << std::endl;
		}


		//Recurse children
		if (node->first_node()->name() != 0x0)
			parseXML(node->first_node(node->first_node()->name()));
		
		//Recurse siblings
		if (node->next_sibling() != 0x0)
			parseXML(node->next_sibling());

		return;
	}

											
																	std::cout << "Reached Null Node!" << "\n";

	return;
}


void parse::regexPriceFind(std::string& str)
{
	//Find price in our string using regex
	//As long as the dollar tag is present we can identify price
	//REMEMBER: to double backslashes, a single backslash is an esc. char
	std::smatch matchPrice;
	bool present = std::regex_search(str, matchPrice, std::regex("\\$\\d+"));

	if (present == false)
		return;

	//Convert match to number
	std::string stringmPrice = matchPrice.str();
	stringmPrice.erase(0,1);
	int foundPrice = atoi(stringmPrice.c_str());

	if (foundPrice < price)
	{
		betterPrice = true;
		return;
	}

	return;
}