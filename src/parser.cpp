//////////// PURPOSE //////////////////////
//This file is designed to parse the 
//    xml file from the RSS feed
//    to see if any items have a better price

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

bool parse::startParse(int priceIn, bool verbose)
{
	//Set price variable
	price = priceIn;
	betterPrice = false;

	//Open our filestream
	std::ifstream fileStream("../responses/output.xml");

	rapidxml::file<> xmlfile(fileStream);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlfile.data());

	//Now we loop through all the nodes
	rapidxml::xml_node<> *node = doc.first_node(doc.first_node()->name());

	if (verbose)
		std::cout << "Name of my first node is: " << doc.first_node()->name() << "\n";

	parseXML(node, verbose);

	if (betterPrice == true)
	{
		if (verbose)
			std::cout << "A better price has been found!" << "\n";

		return true;
	}
	else
	{
		if (verbose)
			std::cout << "No better price" << "\n";

		return false;
	}
}


void parse::parseXML(rapidxml::xml_node<> *node, bool verbose)
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

			if (verbose)
				std::cout << "Node attribute is: " << atrValue << "\n";
		}


		//Recurse children
		if (node->first_node()->name() != 0x0)
			parseXML(node->first_node(node->first_node()->name()), verbose);
		
		//Recurse siblings
		if (node->next_sibling() != 0x0)
			parseXML(node->next_sibling(), verbose);

		return;
	}

	if (verbose)						
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
