//////////// PURPOSE //////////////////////
//This file is designed to parse the 
//    xml file from the RSS feed
//    to see if any items have a better price


//Version 3.0: Insitituted vector<string> to loop through results


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



void parse::loadHTML()
{
	//Get list of possible places price might be located in the HTML document
	std::ifstream inputFile ("../http_search_list.txt");

	while (inputFile >> helper)
	{
		inputFile >> helper;
		whitelist.emplace_back(helper);
	}

	inputFile.close();

	return;
}


bool parse::startParse(const char* extension, int priceIn, bool verbose)
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
	rapidxml::xml_node<> *node = doc.first_node();

	if (verbose)
		std::cout << "Name of my first node is: " << doc.first_node()->name() << '\n';

	///////////////////////HTML CODE///////////////////////////////////////
	//We need a different behavior for native XML and HTML converted to XML
	parseXML(node, verbose);
	//////////////////////////////////////////////////////////////////////


	if (betterPrice == true)
	{
		if (verbose)
			std::cout << "A better price has been found!" << '\n';

		return true;
	}
	else
	{
		if (verbose)
			std::cout << "No better price" << '\n';

		return false;
	}

	//Always free the document and memory pool
	doc.clear();
}


void parse::parseXML(rapidxml::xml_node<> *node, bool verbose)
{
	//Keep recursing while the node is present
	while (*node->name() != 0x0)
	{
		value.clear();

		//Node name doesn't matter here...
		value.emplace_back(node->value());

		//Unfortunately I'm using goto to keep it similar to below case
		//    where goto is mandatory to break the loop
		//    because I'd rather keep this as one function

		//We must loop through all the attributes
		for (rapidxml::xml_attribute<> *attr = node->first_attribute();attr; attr = attr->next_attribute())
		{
			value.emplace_back(attr->value());
		}

		regexPriceFind();

		if (betterPrice == true)
			return;

		//Recurse children
		// '0' is requred because rapidXML will occassionally interpret NULL as 0
		if (node->first_node() != 0x0 || node->first_node() != 0)
			parseXML(node->first_node(), verbose);
		
		//Recurse siblings
		// '0' is requred because rapidXML will occassionally interpret NULL as 0	
		if (node->next_sibling() != 0x0 || node->next_sibling() != 0)
			parseXML(node->next_sibling(), verbose);

		return;
	}

	if (verbose)						
		std::cout << "Reached Null Node!" << "\n";

	return;
}


bool parse::regexPriceFind()
{

	//Find price in our string using regex
	//As long as the dollar tag is present we can identify price
	//REMEMBER: to double backslashes, a single backslash is an esc. char
	for (short i = 0; i < value.size(); ++i)
	{
		for (short j = 0; j < whitelist.size(); ++j)
		{
			if (value[i].compare(whitelist[i]));
			{
				std::smatch matchPrice;
				present = std::regex_search(value[i], matchPrice, std::regex("\\$\\d+"));

				//If no number is present we don't need to compare the number
				if (present == false)
					return false;

				//Convert match to number
				helper = matchPrice.str();
				helper.erase(0,1);
				foundPrice = atoi(helper.c_str());

				if (foundPrice < price)
				{
					betterPrice = true;
					return true;
				}
			}
		}
	}

	return false;
}
